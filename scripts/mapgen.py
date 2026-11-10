"""Writes the source of a map's code (src/maps/NAME.c) from the functions already decompiled in other maps.

Most maps are built from the same functions (the same machine code, only their own addresses differ) with
their own data. Every function of a map with a source file that compiles to the original's code is a
template: a function of another map with the same code (up to the addresses of the map's own functions and
data) gets the template's C, with the map's names (NAME_ADDRESS) moved to its own addresses. The map's data
is written from what the code and the data point to (the types the templates use, then the fields of those
types: an event table's scripts, minions, models, effects, ...); what nothing points to is written as plain
arrays.

usage: mapgen.py [--force] [--iso ISO.bin] [--report] [NAME...]
  NAME: maps to write (default: every map whose functions all have a template and no source yet);
  --force: also write over an existing source; --report: only list the functions without a template
  (by how many maps need them)
"""
import argparse
import collections
import glob
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import mapcode
import overlays as ov

REPO = ov.REPO
B = mapcode.MAP_CODE
MAPS = os.path.join(REPO, "src", "maps")

# ---------------------------------------------------------------------------------------------------------
# machine code


LO_OPS = {9, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x28, 0x29, 0x2A, 0x2B, 0x2E, 0x32, 0x3A}
WRITES_RT = {8, 9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26}


def words(data):
    return list(struct.unpack("<%dI" % (len(data) // 4), data[:len(data) // 4 * 4]))


def split(code):
    """(first code word, end of code word, [function start words]) of a map's code"""
    ws = words(code)
    first = next(i for i, w in enumerate(ws) if (w >> 16) == 0x27BD and (w & 0x8000))
    jrs = [i for i, w in enumerate(ws) if w == 0x03E00008]
    last = jrs[-1] + 2
    starts = [first]
    for j in jrs:
        k = j + 2
        while k < last and ws[k] == 0:
            k += 1
        if k < last:
            starts.append(k)
    targets = set()
    for i in range(first, last):
        w = ws[i]
        op = w >> 26
        if op in (1, 4, 5, 6, 7):
            targets.add(i + 1 + (((w & 0xFFFF) ^ 0x8000) - 0x8000))
        if op == 2:
            targets.add(((((B + i * 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)) - B) >> 2)
    return first, last, sorted(set(s for s in starts if s not in targets))


def relocs(ws, base, lo_addr, hi_addr):
    """the map addresses a function's words use: [(word index, address)] for every lui / its low half / jal / j
    (a lui gets the address of its first low half)"""
    out = []
    hi = {}
    pending = {}
    for i, w in enumerate(ws):
        op = w >> 26
        rt = (w >> 16) & 31
        rs = (w >> 21) & 31
        if op in (2, 3):
            t = (base & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
            if lo_addr <= t < hi_addr:
                out.append((i, t))
            continue
        if op == 0xF:
            v = (w & 0xFFFF) << 16
            if lo_addr - 0x8000 <= v < hi_addr + 0x8000:
                hi[rt] = (i, v)
                pending[rt] = True
            else:
                hi.pop(rt, None)
            continue
        if op in LO_OPS and rs in hi:
            h, v = hi[rs]
            a = (v + ((w & 0xFFFF) ^ 0x8000) - 0x8000) & 0xFFFFFFFF
            if lo_addr <= a < hi_addr:
                if pending.pop(rs, False):
                    out.append((h, a))
                out.append((i, a))
            if op in WRITES_RT:
                hi.pop(rt, None)
            continue
        dst = None
        if op == 0 and (w & 0x3F) not in (8, 0x18, 0x19, 0x1A, 0x1B, 0x11, 0x13):
            dst = (w >> 11) & 31
        elif op in WRITES_RT:
            dst = rt
        if dst is not None:
            hi.pop(dst, None)
    return out


def shape(ws, base, lo_addr, hi_addr):
    """a function's words with the map addresses taken out"""
    out = list(ws)
    for i, _ in relocs(ws, base, lo_addr, hi_addr):
        op = out[i] >> 26
        out[i] &= 0xFC000000 if op in (2, 3) else 0xFFFF0000
    return tuple(out)


_LOOSE = {}


def is_li(w):
    """addiu rt, $zero, imm (a small constant)"""
    return (w >> 26) == 9 and ((w >> 21) & 31) == 0


def loose(key):
    """a shape with its small constants (li) taken out: a template for the same code with other numbers"""
    return tuple(w & 0xFFFF0000 if is_li(w) else w for w in key)


def li_value(w):
    return ((w & 0xFFFF) ^ 0x8000) - 0x8000


def constants_text(body, consts):
    """a template's C with its constants changed ({old: (new, how many times the code has it)}); None if one
    is not written exactly that many times (then which one to change is not clear)"""
    def number(v, like):
        return ("-" if v < 0 else "") + ("0x%X" % abs(v) if like.startswith("0x") else "%d" % abs(v))
    for old, (new, count) in consts.items():
        pat = r"(?<![\w.])%s(%d|0x%X)(?![\w.])" % ("-" if old < 0 else "(?<!-)", abs(old), abs(old))
        if len(re.findall(pat, body)) != count:
            return None
        body = re.sub(pat, lambda m: number(new, m.group(1)), body)
    return body


# ---------------------------------------------------------------------------------------------------------
# what the hand written (or written) maps have: templates


class Exemplar:
    """a map with a source file, built: its functions are templates for the same code in other maps (exact: the
    function compiles to the original's code)"""

    def __init__(self, name):
        self.name = name
        self.src = "".join(open(f).read() for f in mapcode.source_files(name))
        built = open(os.path.join(ov.BUILD, "maps", name + ".SBH"), "rb").read()
        self.built = built[4:4 + struct.unpack("<I", built[:4])[0]]
        orig = open(os.path.join(ov.BUILD, "maps", name + ".orig"), "rb").read()
        self.orig = orig[4:4 + struct.unpack("<I", orig[:4])[0]]
        self.end = B + len(self.orig)
        mp = open(os.path.join(ov.BUILD, "map_%s.map" % name), newline=None).read()
        self.built_addr = {n: int(a, 16) for a, n in re.findall(r"^ ([0-9A-F]{8})  (\w+_800[BC][0-9A-F]{4})$", mp, re.M)}
        self.sizes = {}
        for k in range(len(mapcode.source_files(name))):
            self.sizes.update(asm_sizes(open(os.path.join(ov.BUILD, "map_%s%s.o" % (name, "_%d" % (k + 1) if k else ""))).read()))
        self.decls = declarations(self.src)
        self.funcs = functions(self.src)
        self.helpers = helpers(self.src)
        # the original's names (they carry its addresses)
        self.by_addr = sorted((int(n[-8:], 16), n) for n in set(self.decls) | set(self.funcs))
        first, last, starts = split(self.orig)
        bounds = {}
        for k, st in enumerate(starts):
            e = starts[k + 1] if k + 1 < len(starts) else last
            bounds[B + st * 4] = e - st
        bnames = sorted((a, n) for n, a in self.built_addr.items())
        bnext = {n: (bnames[k + 1][0] if k + 1 < len(bnames) else B + len(self.built)) for k, (a, n) in enumerate(bnames)}
        self.templates = {}  # orig shape -> (name, orig address, orig words, exact)
        for n in self.funcs:
            if n.startswith("fn_"):
                continue  # not decompiled yet
            oa = int(n[-8:], 16)
            if oa not in bounds or n not in self.built_addr:
                continue
            ows = words(self.orig[oa - B:oa - B + bounds[oa] * 4])
            while len(ows) > 2 and ows[-1] == 0 and ows[-3] != 0x03E00008:
                ows.pop()
            ba = self.built_addr[n]
            bws = words(self.built[ba - B:bnext[n] - B])[:len(ows)]
            key = shape(ows, oa, B, self.end)
            exact = len(bws) == len(ows) and shape(bws, ba, B, B + len(self.built)) == key
            self.templates[key] = (n, oa, ows, exact)

    def resolve(self, a):
        """(name, offset) of an original's address, None for what the functions make (their constants)"""
        for sa, n in reversed(self.by_addr):
            if sa <= a:
                if n in self.funcs or a - sa < self.sizes.get(n, 1 << 30):
                    return n, a - sa
                return None
        return None


def asm_sizes(asm):
    """{label: bytes} of the data labels of cc1's output"""
    sizes = {}
    cur = None
    for line in asm.split("\n"):
        m = re.match(r"^([\w$.]+):", line)
        if m:
            cur = m.group(1)
            sizes[cur] = 0
            continue
        f = line.split(None, 1)
        if not f or cur is None:
            continue
        d = f[0]
        if d in (".text", ".data", ".rdata", ".bss", ".section"):
            cur = None
        elif d == ".word":
            sizes[cur] += 4 * (f[1].count(",") + 1)
        elif d == ".half":
            sizes[cur] += 2 * (f[1].count(",") + 1)
        elif d == ".byte":
            sizes[cur] += f[1].count(",") + 1
        elif d == ".space":
            sizes[cur] += int(f[1], 0)
        elif d in (".ascii", ".asciiz"):
            s = f[1].strip()[1:-1]
            sizes[cur] += len(re.sub(r"\\([0-7]{1,3}|.)", "x", s)) + (d == ".asciiz")
    return sizes


DECL = re.compile(r"^((?:const )?)([A-Za-z_]\w*(?: \*+|\*+ | )\**)\s*(\w+_800[BC][0-9A-F]{4})((?:\[\w*\])*)\s*(=|;)", re.M)


def declarations(src):
    """{name: (const, type, dims)} of a source's data (const: 'const ' or '')"""
    out = {}
    for m in DECL.finditer(src):
        out.setdefault(m.group(3), (m.group(1), m.group(2).strip(), m.group(4)))
    return out


FUNC = re.compile(r"^([A-Za-z_][\w \*]*?\b(\w+_800[BC][0-9A-F]{4})\(([^;{]*?)\))\n\{\n.*?^\}\n", re.M | re.S)


def functions(src):
    """{name: (prototype, text)}"""
    return {m.group(2): (m.group(1) + ";", m.group(0)) for m in FUNC.finditer(src)}


def helpers(src):
    """{name: text} of a source's static inline functions"""
    return {m.group(1): m.group(0) for m in
            re.finditer(r"^(?:/\*[^\n]*\*/\n)?static inline [\w \*]*?\b(\w+)\([^;{]*\)\n\{\n.*?^\}\n", src, re.M | re.S)}


def load_exemplars(skip=()):
    out = []
    for p in sorted(glob.glob(os.path.join(MAPS, "*.c"))):
        name = os.path.basename(p)[:-2]
        if name in skip or not os.path.exists(os.path.join(ov.BUILD, "map_%s.map" % name)):
            continue
        if open(p).read().startswith(GENERATED):
            continue  # its functions are other maps'
        out.append(Exemplar(name))
    return out


def base_name(n):
    return n[:-9]


# ---------------------------------------------------------------------------------------------------------
# data types (as src/maps/map.h has them): fields (name, kind, count); kinds: i8 u8 i16 u16 i32 u32,
# ptr:TYPE (a pointer to TYPE's data; fn: a function; str: a string), ref (an int that holds an address)

TYPES = {
    "MapEvent": [("areas_0", "i32", 1), ("type_4", "i32", 1), ("data_8", "ptr:event", 1), ("size_C", "i32", 1),
                 ("run_10", "ptr:fn", 1)],
    "MapInstr": [("op_0", "i32", 1), ("a_4", "i32", 1), ("b_8", "i32", 1), ("c_C", "ref", 1)],
    "MapVoice": [("id_0", "u8", 1), ("sub_1", "u8", 1), ("xa_2", "i16", 3)],
    "MapMinion": [("model_0", "ptr:MapActorModel", 1), ("species_4", "ptr:MapMinionSpecies", 1), ("pos_8", "i32", 3),
                  ("rotY_14", "i16", 1), ("pad_16", "i16", 1), ("anim_18", "i32", 1), ("f1C", "i32", 1),
                  ("flags_20", "u32", 1)],
    "MapMinionSpecies": [("species_0", "i32", 1), ("level_4", "i32", 1)],
    "MapActorModel": [("name_0", "ptr:str", 1), ("modelId_4", "i32", 1), ("bones_8", "ptr:short", 1),
                      ("baseScale_C", "ptr:int", 1), ("boneScale_10", "ptr:SVECTOR", 1), ("ftgs_14", "ptr:int", 1),
                      ("blendDiv_18", "i32", 1), ("script_1C", "ptr:ActorScriptCmd*", 1), ("f20", "i32", 1),
                      ("f24", "i32", 1), ("sel_28", "i16", 1), ("f2A", "i16", 1)],
    "MapFx": [("type_0", "i16", 1), ("id_2", "i16", 1), ("pos_4", "i32", 3), ("rot_10", "i16", 3), ("pad_16", "i16", 1),
              ("length_18", "i16", 1), ("delay_1A", "i16", 1), ("runs_1C", "i16", 1), ("first_1E", "i16", 1),
              ("restart_20", "i16", 1), ("last_22", "i16", 1), ("arg_24", "i16", 1), ("pad_26", "i16", 1),
              ("place_28", "ptr:fn", 1)],
    "MapFxInits": [("init", "ptr:fn", 5)],
    "MapWarp": [("pos_0", "i32", 3), ("rotY_C", "i16", 1), ("idle_E", "i16", 1), ("point_10", "i16", 1), ("map_12", "i16", 3)],
    "MapChest": [("flag_0", "i32", 1), ("item_4", "i32", 1), ("kind_8", "i32", 1), ("flags_C", "u32", 1),
                 ("point_10", "i32", 1), ("pos_14", "i32", 3), ("rotY_20", "i32", 1), ("text_24", "ptr:text", 1),
                 ("text_28", "ptr:text", 1), ("f2C", "i32", 6), ("ftg_44", "i16", 2)],
    "MapGate": [("valuable_0", "i32", 1), ("pos_4", "i32", 3), ("rotY_10", "i16", 1), ("pad_12", "i16", 1),
                ("dest_14", "i32", 3), ("destRotY_20", "u16", 1), ("pad_22", "i16", 1), ("point_24", "i16", 1),
                ("entrance_26", "i16", 1)],
    "MapGateMusic": [("track", "i32", 4)],
    "MapSavePoint": [("pos_0", "i32", 3), ("name_C", "ptr:str", 1)],
    "MapExitSpot": [("entrance_0", "i32", 1), ("vars_4", "i32", 1), ("flag_8", "i32", 1), ("point_C", "i32", 1),
                    ("pos_10", "i32", 3), ("rotY_1C", "i32", 1)],
    "MapMovie": [("movie_0", "i32", 1), ("music_4", "i32", 1)],
    "MapTileDoor": [("flag_0", "i32", 1), ("layer_4", "i16", 1), ("sfx_6", "i16", 1), ("seq_8", "u8", 8)],
    "MapLockPoint": [("point_0", "i32", 1), ("pos_4", "i32", 3), ("arg_10", "ptr:text", 1), ("open_14", "i32", 1)],
    "MapLock": [("points_0", "ptr:MapLockPoint", 1), ("flag_4", "i32", 1), ("valuable_8", "i32", 1),
                ("script_C", "ptr:MapInstr", 1), ("script_10", "ptr:MapInstr", 1), ("f14", "ptr:", 1), ("f18", "i32", 1)],
    "MapFadeBars": [("top_0", "i16", 4), ("bottom_8", "i16", 4), ("frames_10", "i32", 1)],
    "MapSpritePoint": [("pos_0", "i32", 3), ("start_C", "i32", 1)],
    "MapSpritePoint*": [("", "ptr:MapSpritePoint", 1)],
    "MapGateSpot": [("valuable_0", "i32", 1), ("point_4", "i32", 1), ("pos_8", "i32", 3), ("dest_14", "i32", 3),
                    ("rotY_20", "i32", 1), ("music_24", "i32", 1), ("fx_28", "ptr:MapFx", 2), ("mapVar_30", "i16", 1),
                    ("value_32", "i16", 1)],
    "MapGateReturn": [("var_0", "i32", 1), ("fx_4", "ptr:MapFx", 1)],
    "MapFxModels": [("id_0", "i32", 1), ("pos_4", "i32", 3), ("rot_10", "i16", 3), ("pad_16", "i16", 1),
                    ("id_18", "i32", 1), ("f1C", "i32", 3)],
    "MapSwitch": [("flag_0", "i32", 1), ("mode_4", "i32", 1), ("point_8", "i32", 1), ("pos_C", "i32", 3)],
    "MapWallFlag": [("flag_0", "i32", 1), ("kind_4", "i16", 1), ("wall_6", "i16", 1)],
    "MapEffectSpot": [("flag_0", "i32", 1), ("point_4", "i32", 1), ("pos_8", "i32", 3), ("dest_14", "i32", 3),
                      ("rotY_20", "i32", 1), ("fx_24", "ptr:MapFx", 2)],
    "MapFtgAnim": [("first_0", "i16", 1), ("last_2", "i16", 1), ("speed_4", "i16", 1), ("pad_6", "i16", 1),
                   ("rots_8", "ptr:SVECTOR", 1)],
    "MapRgb": [("r", "u8", 1), ("g", "u8", 1), ("b", "u8", 1), ("pad", "u8", 1)],
    "SVECTOR": [("vx", "i16", 1), ("vy", "i16", 1), ("vz", "i16", 1), ("pad", "i16", 1)],
    "ActorScriptCmd*": [("", "ptr:ActorScriptCmd", 1)],
    "ActorScriptCmd": [("op_0", "u8", 1), ("len_1", "u8", 1), ("frame_2", "i16", 1), ("field_4", "i16", 1),
                       ("arg_6", "i16", 1), ("field_8", "i16", 1), ("arg_A", "i16", 1)],
    "int": [("", "ref", 1)],
    "short": [("", "i16", 1)],
    "unsigned char": [("", "u8", 1)],
}
# the C type a "ptr:" field points to (where it is not void*)
POINTEE = {"str": "const char", "short": "short", "int": "int", "SVECTOR": "SVECTOR", "ActorScriptCmd*": "ActorScriptCmd*",
           "ActorScriptCmd": "ActorScriptCmd", "MapActorModel": "MapActorModel", "MapMinionSpecies": "MapMinionSpecies",
           "MapLockPoint": "MapLockPoint", "MapInstr": "MapInstr", "MapSpritePoint": "MapSpritePoint"}
KIND_SIZE = {"i8": 1, "u8": 1, "i16": 2, "u16": 2, "i32": 4, "u32": 4, "ref": 4}
# the data of an event by its init function (MapEvent.run_10) or its type (MapEvent.type_4)
EVENT_DATA = {"MinionInit": "MapMinion", "FxInit": "MapFx", "Warp": "MapWarp", "ChestInit": "MapChest", 8: "MapInstr",
              "GateInit": "MapGate", "SavePointInit": "MapSavePoint", "FtgAnimInit": "MapFtgAnim",
              0xB: "MapVoice", "ExitSpotInit": "MapExitSpot", "MoviePlayerInit": "MapMovie",
              "TileDoorInit": "MapTileDoor", "EffectSpotInit": "MapEffectSpot",
              "SwitchInit": "MapSwitch", "WallFlagsInit": "MapWallFlag", "LockInit": "MapLock",
              "FadeBarsInit": "MapFadeBars", "SpriteTrailInit": "MapSpritePoint*",
              "GateSpotInit": "MapGateSpot", "GateReturnInit": "MapGateReturn",
              "FxModelsInit": "MapFxModels"}
# what an event script instruction's address operand (MapInstr.c_C) is, by its op (not 0x2E/0x2F, EvCmdSetEntityState:
# an entity's data, whatever its type; typing it MapEvent broke the layout on PC)
INSTR_DATA = {0x11: "MapEvent", 0x4B: "MapFx", 0x13: "int", 0x5A: "int", 0x60: "int"}
TYPE_NAME = {"MapEvent": "event", "MapInstr": "script", "MapVoice": "voices", "MapMinion": "minion",
             "MapMinionSpecies": "species", "MapActorModel": "model", "MapFx": "effects", "SVECTOR": "boneScale",
             "ActorScriptCmd*": "script", "ActorScriptCmd": "anim", "int": "data", "short": "bones",
             "unsigned char": "bytes", "str": "str", "MapFxInits": "fxInits", "MapWarp": "warp", "MapChest": "chest", "MapGate": "gate", "MapSavePoint": "savePoint", "MapFtgAnim": "ftgAnim",
             "text": "text"}


def type_size(t):
    if t not in TYPES:
        return None
    n = 0
    for _, k, c in TYPES[t]:
        s = KIND_SIZE.get(k, 4)
        n = (n + s - 1) // s * s + s * c
    return (n + max(type_align(t), 1) - 1) // type_align(t) * type_align(t)


def type_align(t):
    return max(KIND_SIZE.get(k, 4) for _, k, _ in TYPES[t])


# ---------------------------------------------------------------------------------------------------------
# a map's source


class MapSource:
    def __init__(self, name, data, templates):
        self.name = name
        size = struct.unpack("<I", data[:4])[0]
        self.code = data[4:4 + size]
        self.end = B + len(self.code)
        self.first, self.last, self.starts = split(self.code)
        self.rdata_end = B + self.first * 4
        self.text_end = B + self.last * 4
        self.ws = words(self.code)
        self.templates = templates
        self.missing = []  # (address, shape) of the functions without a template
        self.syms = {}  # address -> name
        self.types = {}  # address -> (const, type, dims)
        self.funcs = {}  # address -> (exemplar, template name, words); exemplar None: no template (a stub)
        self.renames = {}  # (exemplar name, name) -> address
        self.anon = set()  # starts of what the functions make themselves (their constants, jump tables)
        self.anon_owner = {}  # anon -> the function that makes it
        self.stub_refs = []  # what the functions without a template use
        self.inexact = []  # functions whose template does not compile to the original's code yet
        self.const_bodies = {}  # address -> its template's C with the constants of this map's code
        if id(templates) not in _LOOSE:
            _LOOSE.clear()
            _LOOSE[id(templates)] = lt = {}
            for k, cands in templates.items():
                lt.setdefault(loose(k), []).extend(cands)
        self.loose_templates = _LOOSE[id(templates)]
        self.scalars = set()  # objects that are not arrays (pointers to them take &)
        self.ctypes = {}  # address -> the C type it is written as (an array's: its element's)

    def match(self):
        """the template of each function, the names of what they use"""
        bounds = []
        for k, s in enumerate(self.starts):
            e = self.starts[k + 1] if k + 1 < len(self.starts) else self.last
            while e - 2 > s and self.ws[e - 1] == 0 and self.ws[e - 3] != 0x03E00008:
                e -= 1
            bounds.append((B + s * 4, self.ws[s:e]))
        chosen = {}
        for a, ws in bounds:
            key = shape(ws, a, B, self.end)
            cands = self.templates.get(key)
            if not cands:
                cands, body = self.loose_template(key)
                if cands:
                    self.const_bodies[a] = body
            if not cands:
                self.missing.append((a, key))
                self.funcs[a] = (None, None, ws)
                self.stub_refs += [ai for _, ai in relocs(ws, a, B, self.end)]
                continue
            chosen[a] = cands
            self.funcs[a] = (cands[0][0], cands[0][1][0], ws)
        # names from what the functions use (a function that several templates have: the one its callers name)
        for a, cands in chosen.items():
            ex, (tn, ta, tws, exact) = cands[0]
            mine = relocs(self.funcs[a][2], a, B, self.end)
            theirs = relocs(tws, ta, B, ex.end)
            for (i, ai), (j, ae) in zip(mine, theirs):
                assert i == j, (self.name, hex(a))
                r = ex.resolve(ae)
                if r is None:
                    self.anon.add(ai)
                    self.anon_owner.setdefault(ai, a)
                    continue
                n, off = r
                self.renames[(ex.name, n)] = ai - off
                self.name_sym(ai - off, base_name(n), None if n in ex.funcs else ex.decls.get(n))
        for a, cands in chosen.items():
            pick = cands[0]
            if a in self.syms:
                pick = next((c for c in cands if base_name(c[1][0]) == base_name(self.syms[a])), pick)
            ex, (tn, ta, tws, exact) = pick
            self.funcs[a] = (ex, tn, self.funcs[a][2])
            self.name_sym(a, base_name(tn), None)
            if not exact:
                self.inexact.append(a)
        for a, (ex, tn, ws) in self.funcs.items():
            if ex is None:
                self.syms.setdefault(a, "fn_%08X" % a)
        return not self.missing

    def loose_template(self, key):
        """templates of the same code with other small constants whose C says which numbers to change"""
        out = []
        for ex, t in self.loose_templates.get(loose(key), []):
            tn, ta, tws, exact = t
            tkey = shape(tws, ta, B, ex.end)
            consts = {}
            ok = True
            for mine, theirs in zip(key, tkey):
                if mine != theirs:
                    old, new = li_value(theirs), li_value(mine)
                    if consts.get(old, (new, 0))[0] != new:
                        ok = False
                    consts[old] = (new, consts.get(old, (new, 0))[1] + 1)
            same = collections.Counter(li_value(w) for w, m in zip(tkey, key) if is_li(w) and w == m)
            if not ok or any(old in same for old in consts):
                continue
            body = constants_text(ex.funcs[tn][1], consts)
            if body is not None:
                return [(ex, (tn, ta, tws, exact))], body
        return None, None

    def name_sym(self, a, base, decl):
        if a not in self.syms or self.syms[a].startswith(("fn_", "data_", "unknown_")):
            self.syms[a] = "%s_%08X" % (base, a)
        if decl and a not in self.types:
            self.types[a] = decl

    def is_func(self, a):
        return a in self.funcs

    def in_data(self, a):
        return B <= a < self.rdata_end or self.text_end <= a < self.end

    # --- data ---
    def discover(self):
        """every address the data holds is the start of something (jump tables: of the function's own)"""
        for v in self.stub_refs:
            if self.in_data(v) and v not in self.syms:
                self.syms[v] = "data_%08X" % v
        for v in (B, self.text_end):
            if v < self.end and v not in self.anon:
                self.syms.setdefault(v, "unknown_%08X" % v)
        for lo, hi in ((B, self.rdata_end), (self.text_end, self.end)):
            for a in range(lo, hi, 4):
                v = self.word(a)
                if self.in_data(v) and v not in self.syms:
                    self.syms[v] = "data_%08X" % v
                elif self.rdata_end <= v < self.text_end and v not in self.funcs:
                    # a jump table: from the first word into the code
                    if not (self.rdata_end <= self.word(a - 4) < self.text_end and self.word(a - 4) not in self.funcs):
                        self.anon.add(a)
                        self.anon_owner.setdefault(a, max(f for f in self.funcs if f <= v))

    def walk(self):
        """types of what the code's data points to, from the fields of the types the code uses"""
        work = list(self.types)
        seen = set()
        while work:
            a = work.pop()
            if a in seen:
                continue
            seen.add(a)
            t = self.types[a][1].replace(" *", "*")
            if t not in TYPES:
                continue
            for elem, fields in self.elements(a, t):
                for (fname, kind, cnt), (fa, vals) in zip(TYPES[t], fields):
                    if not (kind.startswith("ptr") or kind == "ref"):
                        continue
                    for v in vals:
                        if not self.in_data(v):
                            continue
                        sub = kind[4:] if kind.startswith("ptr") else None
                        if t == "MapEvent" and fname == "data_8":
                            sub = EVENT_DATA.get(self.ev_kind(elem))
                        elif t == "MapInstr":
                            sub = INSTR_DATA.get(self.word(elem))
                        if sub in (None, "fn") or v in self.types:
                            continue
                        self.syms[v] = "%s_%08X" % (TYPE_NAME.get(sub, "data"), v)
                        self.types[v] = ("const " if v < self.rdata_end else "", sub, "" if sub == "str" else None)
                        work.append(v)
            # what follows a list (that nothing points to)
            if t in LIST_END:
                es = self.elements(a, t)
                after = es[-1][0] + type_size(t)
                if after < a + self.extent(a):
                    self.syms.setdefault(after, "unknown_%08X" % after)

    def ev_kind(self, elem):
        init = self.word(elem + 0x10)
        if init in self.funcs and self.funcs[init][1]:
            k = base_name(self.funcs[init][1])
            if k in EVENT_DATA:
                return k
        return self.word(elem + 4)

    def word(self, a):
        return struct.unpack("<I", self.code[a - B:a - B + 4])[0] if B <= a <= self.end - 4 else 0

    def value(self, a, kind):
        fmt = {"i8": "<b", "u8": "<B", "i16": "<h", "u16": "<H", "i32": "<i", "u32": "<I"}.get(kind, "<I")
        n = struct.calcsize(fmt)
        o = a - B
        return struct.unpack(fmt, self.code[o:o + n])[0] if 0 <= o and o + n <= len(self.code) else 0

    def starts_sorted(self):
        return sorted(set(x for x in self.syms if not self.is_func(x)) | self.anon)

    def extent(self, a):
        """bytes up to the next object (or the end of the section)"""
        lim = self.rdata_end if a < self.rdata_end else self.end
        nxt = [x for x in self.starts_sorted() if a < x < lim]
        return (nxt[0] if nxt else lim) - a

    def elements(self, a, t):
        """[(address, [(field address, [values])])] of the t's at a (up to the next object or a list's end)"""
        size = type_size(t)
        n = max(1, self.extent(a) // size)
        out = []
        for k in range(n):
            e = a + k * size
            fields = []
            off = 0
            for fname, kind, cnt in TYPES[t]:
                s = KIND_SIZE.get(kind, 4)
                off = (off + s - 1) // s * s
                fields.append((e + off, [self.value(e + off + s * i, kind) for i in range(cnt)]))
                off += s * cnt
            out.append((e, fields))
            if t in LIST_END and LIST_END[t](self, e):
                break
        return out

    def objects(self):
        """(address, size) of what the source defines"""
        # a single typed object with bytes behind it (padding before a jump table): those on their own
        for a in sorted(self.syms):
            d = self.types.get(a)
            if d and d[2] == "" and d[1] in TYPES and not self.is_func(a):
                ts = type_size(d[1])
                if self.extent(a) > ts and (a + ts) not in self.syms and (a + ts) not in self.anon:
                    self.syms[a + ts] = "pad_%08X" % (a + ts)
        out = []
        for a in self.starts_sorted():
            if a in self.anon:
                continue
            out.append((a, self.extent(a)))
        return out

    # --- writing ---
    def ref(self, v, as_int):
        """an address as C: a name, NULL (None) or an address inside something"""
        if v == 0 or not (B <= v < self.end):
            return None
        if v in self.syms:
            n = self.syms[v]
            if as_int:
                return "MAP_REF(%s)" % n
            if self.is_func(v) and self.funcs[v][0] is None:
                return "(void*)" + n  # not decompiled yet (int fn())
            return n if (self.is_func(v) or self.is_array(v)) else "&" + n
        return None

    def is_array(self, a):
        return a not in self.scalars

    def num(self, v):
        if -10 < v < 10:
            return str(v)
        return ("-0x%X" % -v) if v < 0 else ("0x%X" % v)

    def field_text(self, kind, v):
        if kind.startswith("ptr") or kind == "ref":
            r = self.ref(v, kind == "ref")
            if r is not None:
                # a field that points to a type, at what is written as something else (an untyped array)
                want = POINTEE.get(kind[4:]) if kind.startswith("ptr") else None
                have = self.ctypes.get(v)
                if want and have and have.replace("const ", "") != want.replace("const ", ""):
                    return "(%s*)%s" % (want, r)
                return r
            if v == 0:
                return "0"
            if kind == "ref":
                return self.num(struct.unpack("<i", struct.pack("<I", v))[0])
            ext = external_name(v)
            if ext:
                return ext
            return "(void*)0x%X" % v
        return self.num(v)

    def struct_text(self, t, fields):
        parts = []
        for (fname, kind, cnt), (fa, vals) in zip(TYPES[t], fields):
            txt = [self.field_text(kind, v) for v in vals]
            if fname == "run_10":
                parts.append("{ %s }" % txt[0])
            elif cnt > 1:
                parts.append("{ %s }" % ", ".join(txt))
            else:
                parts += txt
        if len(TYPES[t]) == 1 and not TYPES[t][0][0]:
            return parts[0]
        return "{ %s }" % ", ".join(parts)

    def object_text(self, a, size):
        """(declaration, definition) of the object at a"""
        decl, defn = self.object_text_(a, size)
        m = re.match(r"extern (?:const )?(.*?) ?\**\w+(\[\d*\])?;$", decl)
        self.ctypes[a] = re.match(r"extern ((?:const )?[\w ]*?\**) ?\w+(\[\d*\])*;$", decl).group(1).strip()
        return decl, defn

    def object_text_(self, a, size):
        n = self.syms[a]
        const, t, dims = self.types.get(a, ("const " if a < self.rdata_end else "", None, None))
        t = t.replace(" *", "*") if t else None
        raw = self.code[a - B:a - B + size]
        if t == "str" or (t is None and looks_string(raw)):
            s = raw.split(b"\0")[0]
            if raw[len(s):].strip(b"\0") == b"":
                c = "const " if a < self.rdata_end else ""  # .data after the code is not read-only
                return ("extern %schar %s[%d];" % (c, n, size), '%schar %s[%d] = "%s";' % (c, n, size, c_string(s)))
        if t in TYPES and size >= type_size(t):
            es = self.elements(a, t)
            used = len(es) * type_size(t)
            rest = raw[used:]
            if not rest.strip(b"\0") and (len(rest) < 4 or (used % 4 == 0 and len(rest) % type_size(t) == 0)):
                ctype = t
                items = [self.struct_text(t, f) for _, f in es]
                if not dims and len(es) == 1 and not rest:
                    self.scalars.add(a)
                    return ("extern %s%s %s;" % (const, ctype, n), "%s%s %s = %s;" % (const, ctype, n, items[0]))
                if len(TYPES[t]) == 1 and not TYPES[t][0][0]:
                    body = "".join("    %s,\n" % ", ".join(items[i:i + 8]) for i in range(0, len(items), 8))
                else:
                    body = "".join("    %s,\n" % x for x in items)
                return ("extern %s%s %s[%d];" % (const, ctype, n, len(es) + (len(rest) // type_size(t))),
                        "%s%s %s[%d] = {\n%s};" % (const, ctype, n, len(es) + (len(rest) // type_size(t)), body))
        # untyped: words (addresses as MAP_REF), halves or bytes
        if a % 4 == 0 and size % 4 == 0:
            vals = [self.word(a + i) for i in range(0, size, 4)]
            items = [self.ref(v, True) or self.num(struct.unpack("<i", struct.pack("<I", v))[0]) for v in vals]
            ctype = "int"
        elif a % 2 == 0 and size % 2 == 0:
            items = [self.num(self.value(a + i, "i16")) for i in range(0, size, 2)]
            ctype = "short"
        else:
            items = [self.num(self.value(a + i, "u8")) for i in range(size)]
            ctype = "unsigned char"
        lines = []
        for i in range(0, len(items), 8):
            lines.append("    " + ", ".join(items[i:i + 8]) + ",")
        return ("extern %s%s %s[%d];" % (const, ctype, n, len(items)),
                "%s%s %s[%d] = {\n%s\n};" % (const, ctype, n, len(items), "\n".join(lines)))

    def write(self):
        protos = []
        bodies = []
        helpers_done = set()
        objs = self.objects()
        for a, size in objs:
            self.object_text(a, size)  # which are arrays
        decls = {a: self.object_text(a, size) for a, size in objs}
        # read-only data behind the functions' own constants: in the code's object (cc1psx puts a definition's
        # data where the source has it), before the function that makes the next constant
        anon_rdata = sorted(x for x in self.anon if x < self.rdata_end)
        in_code = {}
        for a, size in objs:
            if anon_rdata and anon_rdata[0] < a < self.rdata_end:
                nxt = [x for x in anon_rdata if x > a]
                in_code.setdefault(self.anon_owner.get(nxt[0]) if nxt else None, []).append(a)
        for a in sorted(self.funcs):
            ex, tn, ws = self.funcs[a]
            for d in in_code.get(a, []):
                bodies.append(decls[d][1] + "\n")
            if ex is None:
                n = self.syms[a]
                protos.append("int %s();" % n)
                bodies.append("/* TODO: not decompiled yet (%d words) */\nint %s()\n{\n    return 0;\n}\n" % (len(ws), n))
                continue
            ren = self.rename_map(ex)
            ren[tn] = self.syms[a]
            proto, body = ex.funcs[tn]
            body = self.const_bodies.get(a, body)
            protos.append(rename(proto, ren))
            body = rename(body, ren)
            for h, htext in ex.helpers.items():
                if h not in helpers_done and re.search(r"\b%s\(" % h, body):
                    bodies.append(rename(htext, ren))
                    helpers_done.add(h)
            if a in self.inexact:
                body = "/* NONMATCHING: %s's C does not compile to its code yet */\n" % tn + body
            bodies.append(body)
        for d in in_code.get(None, []):
            bodies.append(decls[d][1] + "\n")
        code_data = set(x for v in in_code.values() for x in v)
        head = [GENERATED, '#include "maps/map.h"', ""] + protos + [""] + [decls[a][0] for a, _ in objs] + [""]
        # the data: .data first (its definitions in order), then .rdata (named data before the functions' constants)
        data = head + [decls[a][1] for a, _ in objs if a >= self.text_end]
        data += [decls[a][1] for a, _ in objs if a < self.text_end and a not in code_data]
        return "\n".join(data) + "\n", "\n".join(head + bodies)

    def rename_map(self, ex):
        out = {}
        for a, (e, tn, ws) in self.funcs.items():
            if e is ex:
                out[tn] = self.syms[a]
        for (exn, n), a in self.renames.items():
            if exn == ex.name:
                out[n] = self.syms[a]
        return out


LIST_END = {
    "MapEvent": lambda m, e: m.value(e + 4, "i32") == 0x12,
    "MapFx": lambda m, e: m.value(e, "i16") == 5,
    "MapVoice": lambda m, e: m.value(e + 2, "i16") == -1,
    "MapWallFlag": lambda m, e: m.value(e + 4, "i16") == 2,
    "MapLockPoint": lambda m, e: m.value(e + 16, "i32") == 0,
    "MapSpritePoint": lambda m, e: m.value(e + 12, "i32") < 0,
}


def looks_string(raw):
    s = raw.split(b"\0")[0]
    return len(s) > 0 and raw[len(s):].strip(b"\0") == b"" and all(c >= 0x20 or c in (9, 10) for c in s)



_EXTERNAL = None


def external_name(v):
    """an address in the executable or GAME (what map data points to there) as C: its name (and offset), if
    the map sources can see the name"""
    global _EXTERNAL
    if _EXTERNAL is None:
        syms = {}
        for a, n in re.findall(r"^ ([0-9A-F]{8})  (\w+)$", open(os.path.join(ov.BUILD, "jade_cocoon.map"), newline=None).read(), re.M):
            syms.setdefault(int(a, 16), n)
        for line in open(os.path.join(REPO, "overlays", "game.sym")):
            m = re.match(r"(\w+)=0x([0-9a-f]+);", line)
            if m:
                syms.setdefault(int(m.group(2), 16), m.group(1))
        # the names map.h declares (a map's preprocessed source)
        pre = glob.glob(os.path.join(ov.BUILD, "map_*.preproc"))
        seen = set(re.findall(r"\b\w+\b", open(pre[0]).read())) if pre else set()
        _EXTERNAL = (sorted(syms), syms, seen)
    keys, syms, seen = _EXTERNAL
    import bisect
    i = bisect.bisect_right(keys, v) - 1
    if i < 0 or not (0x80010000 <= v < B):
        return None
    a = keys[i]
    n = syms[a]
    if n not in seen or v - a >= 0x1000:
        return None
    return "(void*)&%s" % n if v == a else "(void*)((char*)&%s + 0x%X)" % (n, v - a)


def rename(text, ren):
    if not ren:
        return text
    pat = re.compile(r"\b(%s)\b" % "|".join(re.escape(k) for k in sorted(ren, key=len, reverse=True)))
    return pat.sub(lambda m: ren[m.group(1)], text)


def c_string(s):
    out = []
    for i, c in enumerate(s):
        if c == 0x22 or c == 0x5C:
            out.append("\\" + chr(c))
        elif 0x20 <= c < 0x7F:
            # a hex escape takes the hex digits after it
            if out and out[-1].startswith("\\x") and chr(c) in "0123456789abcdefABCDEF":
                out.append('""')
            out.append(chr(c))
        elif c == 10:
            out.append("\\n")
        else:
            out.append("\\x%02x" % c)
    return "".join(out)


# ---------------------------------------------------------------------------------------------------------


GENERATED = "/* generated by scripts/mapgen.py (delete this line to edit the file by hand) */"


def all_maps():
    return sorted(mapcode.map_files())


def main(argv):
    p = argparse.ArgumentParser()
    p.add_argument("--force", action="store_true")
    p.add_argument("--iso", default="orig")
    p.add_argument("--report", action="store_true")
    p.add_argument("--partial", action="store_true", help="write maps with functions without a template (as stubs)")
    p.add_argument("names", nargs="*")
    a = p.parse_args(argv)
    exe = open(os.path.join(ov.BUILD, "jade_cocoon.exe"), "rb").read()[0x800:]
    exemplars = load_exemplars()
    templates = {}  # shape -> [(exemplar, template)], the exact ones first
    for ex in exemplars:
        for k, v in ex.templates.items():
            templates.setdefault(k, []).append((ex, v))
    for k in templates:
        templates[k].sort(key=lambda c: not c[1][3])
    have = set(mapcode.sources())
    names = a.names or all_maps()
    missing = collections.Counter()
    first_seen = {}
    wrote = 0
    for name in names:
        path = os.path.join(ov.BUILD, "maps", name + ".orig")
        if a.iso == "orig" and not os.path.exists(path):
            continue
        data = mapcode.original(name, a.iso, exe)
        if struct.unpack("<I", data[:4])[0] <= 8:
            continue
        m = MapSource(name, data, templates)
        ok = m.match()
        for addr, key in m.missing:
            missing[key] += 1
            first_seen.setdefault(key, (name, addr, len(key)))
        if a.report or (not ok and not a.partial):
            continue
        path = os.path.join(MAPS, name + ".c")
        if name in have and not a.force and not open(path).read().startswith(GENERATED):
            continue
        m.discover()
        m.walk()
        data_text, code_text = m.write()
        os.makedirs(os.path.join(MAPS, "data"), exist_ok=True)
        open(os.path.join(MAPS, "data", name + ".c"), "w").write(data_text)
        open(path, "w").write(code_text)
        wrote += 1
        print("wrote src/maps/%s.c" % name)
    if missing:
        print("%d functions without a template (%d different):" % (sum(missing.values()), len(missing)))
        for key, n in missing.most_common(40 if a.report else 10):
            nm, addr, size = first_seen[key]
            print("  %3d maps  %4d words  first in %s at %08X" % (n, size, nm, addr))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
