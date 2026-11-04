#!/usr/bin/env python3
"""
Generate C definitions (with initialisers from the original executable) for the INCLUDE_DATA symbols of a TU.

  python scripts/gendata.py SLUS_008.54 TU [SYMBOL ...] [--write]

TU is a source file of src/ without .c (main, tu_80019BF0, ...). Without SYMBOL every INCLUDE_DATA line of the TU
is converted (the .bss ones always all together: the compiler emits uninitialised variables at the end of the
file, behind everything that is still INCLUDE_DATA). Build first: the types come from the TU's preprocessed
source (build_psyq/TU.preproc): a symbol that is declared there (extern in a header) is defined with that type,
otherwise the type is guessed from the bytes and the IDA name prefix (strings, pointer tables, byte_/word_/dword_).
Pointers become references to the symbol they point at.

Prints the definitions, and the extern declarations that are missing for the TU's header. --write replaces the
INCLUDE_DATA lines in src/TU.c.

.rdata becomes const, .bss uses BSS (common.h): an uninitialised global would be a common symbol, and psylink
aligns all .bss to 8 bytes when there are commons (see docs/full_build.md).
"""
import bisect
import os
import re
import struct
import sys

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from layout import *  # noqa: E402,F401,F403
import split  # noqa: E402

import pycparser  # noqa: E402
from pycparser import c_ast  # noqa: E402


class GenError(Exception):
    pass


# ---------------------------------------------------------------- preprocessed source -> pycparser AST
def _skip_quoted(t, i):
    q = t[i]
    j = i + 1
    while t[j] != q:
        j += 2 if t[j] == "\\" else 1
    return j + 1


def strip_bodies(t):
    """function bodies -> ';' (they may hold GTE asm that pycparser can't read; only declarations matter)"""
    out = []
    i, n, depth, last = 0, len(t), 0, ""
    while i < n:
        c = t[i]
        if c in "\"'":
            j = _skip_quoted(t, i)
            out.append(t[i:j])
            i, last = j, c
            continue
        if c == "{" and depth == 0 and last == ")":
            d, j = 0, i
            while True:
                ch = t[j]
                if ch in "\"'":
                    j = _skip_quoted(t, j)
                    continue
                if ch == "{":
                    d += 1
                elif ch == "}":
                    d -= 1
                    if d == 0:
                        break
                j += 1
            out.append(";")
            i, last = j + 1, ";"
            continue
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
        out.append(c)
        if not c.isspace():
            last = c
        i += 1
    return "".join(out)


def strip_attributes(t):
    out = []
    i = 0
    while True:
        j = t.find("__attribute__", i)
        if j < 0:
            out.append(t[i:])
            return "".join(out)
        out.append(t[i:j])
        k, d = t.index("(", j), 0
        while True:
            if t[k] == "(":
                d += 1
            elif t[k] == ")":
                d -= 1
                if d == 0:
                    break
            k += 1
        i = k + 1


def parse_preproc(path, extra=""):
    text = open(path, encoding="latin1").read() + "\n" + extra
    text = "\n".join(l for l in text.split("\n") if not l.startswith("#"))
    text = strip_bodies(text)
    text = re.sub(r"__asm__\s*\((?:[^;])*?\)\s*;", ";", text)
    text = strip_attributes(text)
    text = re.sub(r"\b(__inline__|__inline|inline|__extension__)\b", "", text)
    text = re.sub(r"\b__const\b", "const", text)
    text = re.sub(r"\b__volatile__\b", "volatile", text)
    text = re.sub(r"\b__signed__\b", "signed", text)
    return pycparser.CParser().parse(text, path)


# ---------------------------------------------------------------- types
class T:
    """kind: int / ptr / array / struct / union / func; int: size, signed; ptr: to; array: of, n (None = []);
    struct/union: members [(name, T, offset, bitpos, bitsize)], size, align, tag"""

    def __init__(self, kind, **kw):
        self.kind = kind
        self.__dict__.update(kw)

    def size(self):
        if self.kind == "int":
            return self.nbytes
        if self.kind == "ptr":
            return 4
        if self.kind == "array":
            if self.n is None:
                raise GenError("size of an incomplete array")
            return self.n * self.of.size()
        if self.kind in ("struct", "union"):
            return self.ssize
        raise GenError("size of " + self.kind)

    def align(self):
        if self.kind == "int":
            return self.nbytes
        if self.kind == "ptr":
            return 4
        if self.kind == "array":
            return self.of.align()
        if self.kind in ("struct", "union"):
            return self.salign
        return 4


INTS = {"char": (1, False), "signed char": (1, True), "unsigned char": (1, False), "short": (2, True),
        "short int": (2, True), "signed short": (2, True), "unsigned short": (2, False), "unsigned short int": (2, False),
        "int": (4, True), "signed int": (4, True), "signed": (4, True), "unsigned int": (4, False), "unsigned": (4, False),
        "long": (4, True), "long int": (4, True), "unsigned long": (4, False), "unsigned long int": (4, False),
        "long long": (8, True), "unsigned long long": (8, False), "float": (4, None), "double": (8, None)}


def type_str(node):
    """C text of a type node as an abstract declarator (no names): 'int (*)(Foo *, int)'"""
    import copy
    from pycparser import c_generator
    n = copy.deepcopy(node)

    def strip(x):
        if isinstance(x, c_ast.TypeDecl):
            x.declname = None
        for _, c in x.children():
            strip(c)
    strip(n)
    return c_generator.CGenerator().visit(c_ast.Typename(None, [], None, n))


class PtrT(T):
    """a pointer; the type it points at is resolved when needed (structs that point at themselves)"""

    def __init__(self, types, node, pnode=None):
        T.__init__(self, "ptr")
        self._types, self._node, self._to = types, node, None
        self.pnode = pnode      # the PtrDecl
        self.cast = type_str(pnode) if pnode is not None else None   # the type as a cast would name it

    @property
    def to(self):
        if self._to is None:
            self._to = self._types._lazy(self._node)
        return self._to


class Types:
    def __init__(self, ast):
        self.typedefs = {}
        self.tags = {}      # ('struct', tag) -> c_ast.Struct with decls
        self.enums = {}     # enumerator -> value
        self.decls = {}     # name -> c_ast.Decl (externs / definitions of variables)
        self.funcs = set()  # declared functions
        self.funcnodes = {}  # name -> FuncDecl
        self.cache = {}
        for ext in ast.ext:
            self._collect(ext)
            if isinstance(ext, c_ast.Typedef):
                self.typedefs[ext.name] = ext.type
            elif isinstance(ext, c_ast.Decl) and ext.name:
                if isinstance(ext.type, c_ast.FuncDecl):
                    self.funcs.add(ext.name)
                    self.funcnodes.setdefault(ext.name, ext.type)
                else:
                    self.decls[ext.name] = ext
            elif isinstance(ext, c_ast.FuncDef):
                self.funcs.add(ext.decl.name)
                self.funcnodes[ext.decl.name] = ext.decl.type

    def _collect(self, node):
        if isinstance(node, (c_ast.Struct, c_ast.Union)) and node.decls is not None and node.name:
            self.tags[("struct" if isinstance(node, c_ast.Struct) else "union", node.name)] = node
        if isinstance(node, c_ast.Enum) and node.values is not None:
            v = -1
            for e in node.values.enumerators:
                v = self.const(e.value) if e.value is not None else v + 1
                self.enums[e.name] = v
        for _, c in node.children():
            self._collect(c)

    def const(self, e):
        if isinstance(e, c_ast.Constant):
            s = e.value.rstrip("uUlL")
            if e.type == "char":
                return ord(eval(s))
            return int(s, 0) if not re.match(r"^0\d", s) else int(s, 8)
        if isinstance(e, c_ast.ID):
            return self.enums[e.name]
        if isinstance(e, c_ast.UnaryOp):
            if e.op == "sizeof":
                return self.resolve(e.expr.type if isinstance(e.expr, c_ast.Typename) else e.expr).size()
            v = self.const(e.expr)
            return {"-": -v, "+": v, "~": ~v, "!": int(not v)}[e.op]
        if isinstance(e, c_ast.BinaryOp):
            a, b = self.const(e.left), self.const(e.right)
            return {"+": a + b, "-": a - b, "*": a * b, "/": int(a / b), "%": a % b, "<<": a << b, ">>": a >> b,
                    "|": a | b, "&": a & b, "^": a ^ b}[e.op]
        if isinstance(e, c_ast.Cast):
            return self.const(e.expr)
        if isinstance(e, c_ast.TernaryOp):
            return self.const(e.iftrue) if self.const(e.cond) else self.const(e.iffalse)
        raise GenError("constant " + type(e).__name__)

    def resolve(self, node):
        if isinstance(node, c_ast.TypeDecl):
            return self.resolve(node.type)
        if isinstance(node, c_ast.Typename):
            return self.resolve(node.type)
        if isinstance(node, c_ast.IdentifierType):
            names = " ".join(n for n in node.names)
            if names in INTS:
                n, s = INTS[names]
                if s is None:
                    raise GenError("floating point")
                return T("int", nbytes=n, signed=s)
            if len(node.names) == 1 and node.names[0] in self.typedefs:
                r = self.resolve(self.typedefs[node.names[0]])
                if r.kind == "ptr":
                    r.cast = node.names[0]
                return r
            if names == "void":
                return T("void")
            raise GenError("type " + names)
        if isinstance(node, c_ast.PtrDecl):
            return PtrT(self, node.type, node)
        if isinstance(node, c_ast.ArrayDecl):
            return T("array", of=self.resolve(node.type), n=self.const(node.dim) if node.dim is not None else None)
        if isinstance(node, c_ast.FuncDecl):
            return T("func")
        if isinstance(node, c_ast.Enum):
            return T("int", nbytes=4, signed=True)
        if isinstance(node, (c_ast.Struct, c_ast.Union)):
            kind = "struct" if isinstance(node, c_ast.Struct) else "union"
            if node.decls is None:
                if (kind, node.name) not in self.tags:
                    raise GenError("incomplete %s %s" % (kind, node.name))
                node = self.tags[(kind, node.name)]
            key = id(node)
            if key not in self.cache:
                self.cache[key] = self._layout(kind, node)
            return self.cache[key]
        raise GenError("type node " + type(node).__name__)

    def _lazy(self, node):
        try:
            return self.resolve(node)
        except GenError:
            return T("opaque")

    def _layout(self, kind, node):
        members = []
        off = 0          # in bits
        size = 0
        align = 1
        for d in node.decls:
            t = self.resolve(d.type)
            a = t.align()
            if d.bitsize is not None:
                bits = self.const(d.bitsize)
                unit = t.size() * 8
                if kind == "union":
                    pos = 0
                elif bits == 0:
                    off = (off + unit - 1) // unit * unit
                    continue
                else:
                    if off // unit != (off + bits - 1) // unit:
                        off = (off + unit - 1) // unit * unit
                    pos = off
                if d.name:
                    members.append((d.name, t, pos // unit * t.size(), pos % unit, bits))
                align = max(align, a)
                if kind == "union":
                    size = max(size, (bits + 7) // 8)
                else:
                    off = pos + bits
                continue
            align = max(align, a)
            if kind == "union":
                members.append((d.name, t, 0, None, None))
                size = max(size, t.size())
            else:
                off = (off + a * 8 - 1) // (a * 8) * (a * 8)
                if t.kind == "array" and t.n is None:
                    t = T("array", of=t.of, n=0)
                members.append((d.name, t, off // 8, None, None))
                off += t.size() * 8
        if kind == "struct":
            size = (off + 7) // 8
        size = (size + align - 1) // align * align
        return T(kind, members=members, ssize=size, salign=align, tag=node.name)


# ---------------------------------------------------------------- symbols
class Syms:
    def __init__(self, exe):
        self.exe = exe
        syms = split.load_symbols()
        have = {a for a, _ in syms}
        import io
        import contextlib
        with contextlib.redirect_stdout(io.StringIO()):
            extra = split.c_data_names({n for _, n in syms}, have)
        self.addr = {n: a for a, n in syms}
        for n, a in extra.items():
            self.addr[n] = a
        by = {}
        for n, a in self.addr.items():
            by.setdefault(a, []).append(n)
        self.by_addr = by
        self.sorted = sorted(by)

    def rd(self, addr, n):
        off = addr - BASE
        return self.exe[off:off + n]

    def add(self, name, addr):
        if name in self.addr:
            return
        self.addr[name] = addr
        if addr not in self.by_addr:
            bisect.insort(self.sorted, addr)
            self.by_addr[addr] = []
        self.by_addr[addr].insert(0, name)

    def at(self, addr):
        """(start, names) of the symbol addr is in"""
        i = bisect.bisect_right(self.sorted, addr) - 1
        if i < 0:
            return None
        return self.sorted[i], self.by_addr[self.sorted[i]]


def chunk_info(name):
    s = open(os.path.join(REPO, "asm", "d", name + ".s")).read()
    sec = re.search(r"\t\.section\t(\S+)", s).group(1)
    size = sum(int(x) for x in re.findall(r"\t\.space\t(\d+)", s))
    for l in re.findall(r"\t\.word\t(.*)", s):
        size += 4 * len(l.split(","))
    for l in re.findall(r"\t\.byte\t(.*)", s):
        size += len(l.split(","))
    return sec, size


def in_image(v):
    return BASE <= v < BSS_END


# ---------------------------------------------------------------- initialisers
def literal(b):
    s = ""
    prev_oct = False
    for c in b:
        ch = chr(c)
        if ch == '"':
            s += '\\"'
        elif ch == "\\":
            s += "\\\\"
        elif c == 10:
            s += "\\n"
        elif c == 9:
            s += "\\t"
        elif 32 <= c < 127 and not (prev_oct and ch in "01234567"):
            s += ch
        else:
            s += "\\%03o" % c
            prev_oct = True
            continue
        prev_oct = False
    return '"' + s + '"'


def is_text(b):
    if not b:
        return False
    i = 0
    while i < len(b):
        c = b[i]
        if 32 <= c < 127 or c in (9, 10):
            i += 1
        elif 0x81 <= c <= 0x9F or 0xE0 <= c <= 0xEF:    # Shift-JIS lead byte
            if i + 1 >= len(b) or not (0x40 <= b[i + 1] <= 0xFC and b[i + 1] != 0x7F):
                return False
            i += 2
        else:
            return False
    return True


def intstr(v, t=None):
    if -256 < v < 256:
        return str(v)
    if v < 0 and t is not None and v < -0x1000:
        return "0x%X" % (v & ((1 << (8 * t.nbytes)) - 1))
    return ("-0x%X" % -v) if v < 0 else ("0x%X" % v)


class Gen:
    def __init__(self, syms, types, defined=()):
        self.syms = syms
        self.types = types
        self.refs = set()
        self.protos = {}             # functions the initialisers use that nobody declares: FuncDecl or None
        self.arrays = set(defined)   # names that are arrays (no & needed)
        self.local = {}              # name -> T of the objects being defined here

    def type_of(self, name):
        if name in self.local:
            return self.local[name]
        d = self.types.decls.get(name)
        if d is None:
            # not declared here: a string (in another TU) is a char array
            p = os.path.join(REPO, "asm", "d", name + ".s")
            if name in self.syms.addr and os.path.exists(p):
                sec, size = chunk_info(name)
                if sec != ".bss":
                    parts = split_strings(self.syms.rd(self.syms.addr[name], size))
                    if parts and parts[0][1] is not None:
                        return T("array", of=U8, n=len(parts[0][1]) + 1)
            return None
        try:
            return self.types.resolve(d.type)
        except GenError:
            return None

    def ref(self, v, t):
        """pointer value v as a C expression for a pointer of type t (T ptr)"""
        if v == 0:
            return "0"
        hit = self.syms.at(v)
        target = t.to if t is not None and t.kind == "ptr" else None
        if not in_image(v) and v in self.syms.by_addr and target is not None and target.kind == "func":
            name = self.syms.by_addr[v][0]      # an overlay's function
            self.refs.add(name)
            if name not in self.types.funcnodes:
                self.protos[name] = t.pnode.type if getattr(t, "pnode", None) is not None else None
            return name
        if hit is None or not in_image(v):
            raise GenError("pointer %08X outside the image" % v)
        a, names = hit
        name = names[0]
        for n in names:
            if n in self.local or n in self.types.decls or n in self.types.funcs:
                name = n
                break
        self.refs.add(name)
        is_code = BASE <= a < GAME_TEXT_END or GAME_TEXT_END <= a < LIB_TEXT_END
        target = t.to if t is not None and t.kind == "ptr" else None
        if is_code:
            if a == v:
                if target is not None and target.kind == "func":
                    fn = self.types.funcnodes.get(name)
                    if getattr(t, "pnode", None) is not None and t.cast and (
                            fn is None or type_str(c_ast.PtrDecl([], fn)) != type_str(t.pnode)):
                        if fn is None:
                            self.protos[name] = t.pnode.type
                        return "(%s)%s" % (t.cast, name)
                    if fn is None:
                        self.protos[name] = None
                    return name
                return "(void *)%s" % name
            return "(void *)((char *)%s + %d)" % (name, v - a)
        nt = self.type_of(name)
        is_arr = nt is not None and nt.kind == "array"
        base = name if is_arr else "&" + name
        if a == v:
            if nt is not None and target is not None and nt.kind == "array" and self.same(nt.of, target):
                return name
            if nt is not None and target is not None and self.same(nt, target):
                return base
            return "(void *)%s" % base
        off = v - a
        if is_arr and nt.of.kind not in ("void", "opaque", "func"):
            es = nt.of.size()
            if es and off % es == 0 and (nt.n is None or off // es <= nt.n):
                e = "&%s[%d]" % (name, off // es)
                if target is not None and self.same(nt.of, target):
                    return e
                return "(void *)" + e
        if nt is not None and nt.kind in ("struct",) and target is not None:
            for mn, mt, mo, bp, bs in nt.members:
                if mo == off and bp is None and self.same(mt, target):
                    return "&%s.%s" % (name, mn)
        return "(void *)((char *)%s + %d)" % (base, off)

    @staticmethod
    def same(a, b):
        if a is b:
            return True
        if a.kind != b.kind:
            return False
        if a.kind == "int":
            return a.nbytes == b.nbytes and a.signed == b.signed
        if a.kind == "ptr":
            return Gen.same(a.to, b.to) if a.to.kind != "opaque" and b.to.kind != "opaque" else False
        if a.kind in ("struct", "union"):
            return a.tag == b.tag and a.tag is not None and a.ssize == b.ssize
        if a.kind == "array":
            return a.n == b.n and Gen.same(a.of, b.of)
        return a.kind in ("void", "func")

    def value(self, addr, t, indent):
        k = t.kind
        if k == "int":
            v = int.from_bytes(self.syms.rd(addr, t.nbytes), "little", signed=t.signed)
            return intstr(v, t)
        if k == "ptr":
            return self.ref(struct.unpack("<I", self.syms.rd(addr, 4))[0], t)
        if k == "array":
            if t.of.kind == "int" and t.of.nbytes == 1:
                b = self.syms.rd(addr, t.n)
                z = b.rstrip(b"\0")
                if getattr(t, "is_str", False):
                    return literal(z)
                if b"\0" not in z and is_text(z) and (any(c >= 0x80 for c in z) or
                                                       sum(chr(c).isalnum() for c in z) * 2 >= len(z) >= 2):
                    return literal(z)
                while len(b) > 1 and b[-1] == 0:
                    b = b[:-1]
                return "{ " + ", ".join(str(int.from_bytes(bytes([c]), "little", signed=t.of.signed)) for c in b) + " }"
            es = t.of.size()
            items = [self.value(addr + i * es, t.of, indent + "    ") for i in range(t.n)]
            while len(items) > 1 and self.zero(addr + (len(items) - 1) * es, es):
                items.pop()
            if t.of.kind in ("struct", "union", "array") and len(items) > 1:
                return "{\n" + "".join("%s    %s,\n" % (indent, x) for x in items) + indent + "}"
            if len(items) > 8 and t.of.kind in ("int", "ptr"):
                per = 8 if t.of.kind == "int" else 4
                lines = [", ".join(items[i:i + per]) for i in range(0, len(items), per)]
                return "{\n" + "".join("%s    %s,\n" % (indent, l) for l in lines) + indent + "}"
            return "{ " + ", ".join(items) + " }"
        if k in ("struct", "union"):
            parts = []
            covered = bytearray(t.size())
            for mn, mt, mo, bp, bs in t.members:
                if bp is not None:
                    word = int.from_bytes(self.syms.rd(addr + mo, mt.size()), "little")
                    v = (word >> bp) & ((1 << bs) - 1)
                    if mt.signed and v >> (bs - 1):
                        v -= 1 << bs
                    parts.append(intstr(v))
                    for bit in range(bp, bp + bs):
                        covered[mo + bit // 8] = 1
                else:
                    parts.append(self.value(addr + mo, mt, indent + "    "))
                    for i in range(mt.size()):
                        covered[mo + i] = 1
                if k == "union":
                    break
            b = self.syms.rd(addr, t.size())
            for i in range(len(b)):
                if b[i] and not covered[i]:
                    raise GenError("non-zero padding at +0x%X in %s %s" % (i, k, t.tag))
            while len(parts) > 1 and parts[-1] in ("0", "{ 0 }", '""'):
                parts.pop()
            s = "{ " + ", ".join(parts) + " }"
            if len(s) > 110:
                s = "{\n" + "".join("%s    %s,\n" % (indent, p) for p in parts) + indent + "}"
            return s
        raise GenError("value of " + k)

    def zero(self, addr, n):
        return not any(self.syms.rd(addr, n))


# ---------------------------------------------------------------- C declarations
def decl_text(node, name):
    """the declarator of name with the type of a pycparser type node (as the header declares it)"""
    from pycparser import c_generator
    d = c_ast.Decl(name, [], [], [], [], node, None, None)
    return c_generator.CGenerator().visit(d)


def node_is_const(t):
    while isinstance(t, c_ast.ArrayDecl):
        t = t.type
    return "const" in (getattr(t, "quals", None) or [])


def named(node, name):
    """a copy of a function type node with name as the declared name"""
    import copy
    n = copy.deepcopy(node)
    x = n
    while not isinstance(x, c_ast.TypeDecl):
        x = x.type
    x.declname = name
    return n


def const_decl(decl, name):
    """const for the object itself: 'char x[]' -> 'const char x[]', 'char *x[3]' -> 'char *const x[3]'"""
    m = re.search(r"\b%s\b" % re.escape(name), decl)
    head, tail = decl[:m.start()], decl[m.end():]
    if "(" in head:      # function pointer (table): void (*x[3])() -> void (*const x[3])()
        i = head.rindex("*")
        return head[:i + 1] + "const " + head[i + 1:].lstrip() + name + tail
    if head.rstrip().endswith("*"):
        return head.rstrip() + "const " + name + tail
    if re.match(r"\s*(extern\s+)?const\b", decl):
        return decl
    return "const " + decl


def unconst(decl, name):
    return re.sub(r"\bconst\s+", "", decl)


def sized(decl, name, n):
    """'T x[]' -> 'T x[n]'"""
    return re.sub(r"\b(%s\s*)\[\]" % re.escape(name), r"\g<1>[%d]" % n, decl, count=1)


# ---------------------------------------------------------------- strings
FULLWIDTH = {}
for _i in range(26):
    FULLWIDTH[0x8260 + _i] = chr(65 + _i)
    FULLWIDTH[0x8281 + _i] = chr(97 + _i)
for _i in range(10):
    FULLWIDTH[0x824F + _i] = chr(48 + _i)
FULLWIDTH[0x8140] = " "
for _c, _a in ((0x8143, ","), (0x8144, "."), (0x8146, ":"), (0x8147, ";"), (0x8148, "?"), (0x8149, "!"), (0x815E, "/"),
               (0x8169, "("), (0x816A, ")"), (0x817B, "+"), (0x817C, "-"), (0x8193, "%"), (0x8196, "*"), (0x8197, "@"),
               (0x8181, "="), (0x8183, "<"), (0x8184, ">"), (0x8194, "#"), (0x8195, "&"), (0x8166, "'"), (0x8168, '"')):
    FULLWIDTH[_c] = _a


def ascii_name(s):
    """an IDA-like name for a string: aAssertionFaile"""
    words = re.findall(r"[A-Za-z0-9]+", s)
    n = "".join(w[:1].upper() + w[1:] for w in words)
    return ("a" + n)[:16] if n else None


def sjis_ascii(b):
    """fullwidth latin Shift-JIS as ASCII (None if there is other text in it)"""
    out = ""
    i = 0
    while i < len(b):
        if b[i] < 0x80:
            out += chr(b[i])
            i += 1
            continue
        c = (b[i] << 8) | b[i + 1]
        if c not in FULLWIDTH:
            return None
        out += FULLWIDTH[c]
        i += 2
    return out


def string_comment(b):
    if all(c < 0x80 for c in b):
        return None
    a = sjis_ascii(b)
    if a is not None:
        return a
    try:
        return b.decode("shift_jis")
    except UnicodeDecodeError:
        return None


def split_strings(b, rest=False):
    """offsets and bytes of the strings a blob is made of (each on 4 bytes, zero padded), zero words as None;
    None if it is not only strings. With rest, a blob that starts with strings may end with other words:
    they come last as (offset, False)."""
    out = []
    pos = 0
    n = len(b)

    def stop():
        if rest and pos % 4 == 0 and any(s for _, s in out) and n % 4 == 0:
            while out and out[-1][1] is None:   # zero words in front of the rest belong to it
                out.pop()
            return out + [(out[-1][0] + ((len(out[-1][1]) + 4) & ~3), False)]
        return None
    while pos < n:
        if pos % 4 == 0 and pos + 4 <= n and b[pos:pos + 4] == b"\0\0\0\0":
            out.append((pos, None))
            pos += 4
            continue
        if pos % 4 == 0 and not any(b[pos:]):
            break
        e = b.find(b"\0", pos)
        if e < 0:
            return stop()
        s = b[pos:e]
        if not is_text(s) or len(s) < 2:
            return stop()
        nxt = min((e + 4) & ~3, n)
        if any(b[e:nxt]):
            return stop()
        out.append((pos, s))
        pos = nxt
    if not any(s for _, s in out):
        return None
    return out


# ---------------------------------------------------------------- guessing types
I32 = T("int", nbytes=4, signed=True)
U8 = T("int", nbytes=1, signed=False)
S16 = T("int", nbytes=2, signed=True)


def guess(syms, name, addr, size, sec, gen):
    """[(name, addr, declarator, T, comment)] for a symbol nobody declared"""
    b = syms.rd(addr, size)
    if sec != ".bss" and addr % 4 == 0:
        parts = split_strings(b, rest=True)
        if parts is not None and sec == ".data" and not all(
                s is None or s is False or any(c >= 0x80 for c in s) or
                (len(s) >= 4 and sum(chr(c).isalnum() or c in b" .,:!?%-'" for c in s) * 4 >= len(s) * 3)
                for _, s in parts):
            parts = None
        if parts is not None and (len(parts) > 1 or parts[0][1] is not None):
            out = []
            for off, s in parts:
                a = addr + off
                if s is False:
                    out += guess(syms, "dword_%08X" % a, a, size - off, sec, gen)
                    continue
                if off == 0:
                    n = name
                elif s is None:
                    n = "dword_%08X" % a
                else:
                    an = ascii_name(s.decode("latin1")) if all(c < 0x80 for c in s) else None
                    if an is None:
                        a2 = sjis_ascii(s)
                        an = ascii_name(a2) if a2 else None
                    n = "%s_%08X" % (an or "asc", a)
                if s is None:
                    out.append((n, a, "int %s" % n, I32, None))
                else:
                    out.append((n, a, "char %s[]" % n, T("array", of=U8, n=len(s) + 1, is_str=True), string_comment(s)))
            return out
    if sec != ".bss" and addr % 4 == 0 and size % 4 == 0 and not name.startswith(("word_", "byte_")):
        ws = struct.unpack("<%dI" % (size // 4), b)
        nz = [w for w in ws if w]
        if nz and all(in_image(w) and syms.at(w) for w in nz):
            code = [w for w in nz if BASE <= w < LIB_TEXT_END]
            if len(code) == len(nz) and all(syms.at(w)[0] == w for w in nz):
                return [(name, addr, "void (*%s[%d])()" % (name, len(ws)),
                         T("array", of=T("ptr", to=T("func")), n=len(ws)), None)]
            if not code:
                def is_str(w):
                    a, ns = syms.at(w)
                    t = gen.type_of(ns[0]) if a == w else None
                    return t is not None and t.kind == "array" and t.of.kind == "int" and t.of.nbytes == 1
                if all(is_str(w) for w in nz):
                    ro = all(RDATA_START <= w < RDATA_GAME_END for w in nz)
                    return [(name, addr, "%schar *%s[%d]" % ("const " if ro else "", name, len(ws)),
                             T("array", of=T("ptr", to=U8), n=len(ws)), None)]
                return [(name, addr, "void *%s[%d]" % (name, len(ws)),
                         T("array", of=T("ptr", to=T("void")), n=len(ws)), None)]
    if name.startswith("byte_") or addr % 2 or size % 2:
        t, cn = U8, "unsigned char"
    elif name.startswith("word_") or addr % 4 or size % 4:
        t, cn = S16, "short"
    else:
        t, cn = I32, "int"
    n = size // t.size()
    if n == 1:
        return [(name, addr, "%s %s" % (cn, name), t, None)]
    if addr % 4:
        # an array would go on 4 bytes: one variable per element
        es = t.size()
        return [(name if k == 0 else "%s_%08X" % ("byte" if es == 1 else "word", addr + k * es), addr + k * es,
                 "%s %s" % (cn, name if k == 0 else "%s_%08X" % ("byte" if es == 1 else "word", addr + k * es)), t, None)
                for k in range(n)]
    return [(name, addr, "%s %s[%d]" % (cn, name, n), T("array", of=t, n=n), None)]


# ---------------------------------------------------------------- main
def tu_data(tu):
    text = open(os.path.join(REPO, "src", tu + ".c")).read()
    return re.findall(r"^INCLUDE_DATA\((\w+)\);", text, re.M)


class Def:
    def __init__(self, head, name, addr, sec, t, decl, declared, comment=None):
        self.head = head          # the INCLUDE_DATA line it replaces
        self.name, self.addr, self.sec, self.t = name, addr, sec, t
        self.decl = decl          # declarator text, without const
        self.declared = declared  # an extern exists
        self.comment = comment
        self.text = None
        self.refs = set()


C_WORDS = {"extern", "const", "volatile", "unsigned", "signed", "char", "short", "int", "long", "void", "struct",
           "union", "enum", "float", "double"}


def foreign_externs(tu, names, types):
    """{name: (path, line)}: externs of names that this TU doesn't see (in another TU's .c, or a header it doesn't
    include) and whose type this TU knows"""
    out = {}
    own = os.path.join(REPO, "src", tu + ".c")
    for n in names:
        if n in types.decls:
            continue
        for path, line in find_extern(n):
            if path == own or os.sep + "overlays" + os.sep in path:
                continue
            decl = line.split("//")[0].strip()
            words = re.findall(r"[A-Za-z_]\w*", re.split(r"\b%s\b" % re.escape(n), decl)[0])
            ok = True
            for i, w in enumerate(words):
                if w in C_WORDS or w in types.typedefs:
                    continue
                if i and words[i - 1] in ("struct", "union") and (words[i - 1], w) in types.tags:
                    continue
                ok = False
            if ok:
                out[n] = (path, line)
                break
            print("// %s: the extern in %s has a type this TU doesn't know: %s" % (n, os.path.basename(path),
                                                                                  line.strip()))
    return out


def header_defining(tname):
    """the header (name relative to src/) that defines typedef tname, None if it is not a project header's"""
    r1 = re.compile(r"^\s*}\s*%s\s*;" % re.escape(tname))
    r2 = re.compile(r"^\s*typedef\b[^;]*\b%s\s*(\)|;)" % re.escape(tname))
    for p, l in src_lines():
        if p.endswith(".h") and tname in l and (r1.match(l) or r2.match(l)):
            return os.path.relpath(p, os.path.join(REPO, "src"))
    return None


def add_includes(path, headers):
    """#include the headers in path (behind its last #include) unless it has them; True if it changed"""
    text = open(path).read()
    add = "".join('#include "%s"\n' % h for h in headers if '#include "%s"' % h not in text
                  and os.path.basename(path) != h)
    if not add:
        return False
    incs = list(re.finditer(r'^#include .*\n', text, re.M))
    k = incs[-1].end() if incs else text.index("\n", text.index("#define")) + 1
    open(path, "w").write(text[:k] + add + text[k:])
    return True


def include_declaring_headers(tu, secs=None):
    """#include the headers that declare this TU's INCLUDE_DATA symbols (their types are what the definitions use);
    rebuilds the preprocessed source if that changed anything"""
    names = tu_data(tu)
    hs = []
    for n in names:
        if secs and chunk_info(n)[0] not in secs:
            continue
        for p, _ in find_extern(n):
            h = os.path.relpath(p, os.path.join(REPO, "src"))
            if p.endswith(".h") and h != os.path.basename(header_for(tu)) and h not in hs and \
                    not h.startswith("overlays"):
                hs.append(h)
            break
    c = os.path.join(REPO, "src", tu + ".c")
    if add_includes(c, hs):
        print("// included", " ".join(hs))
        import subprocess
        subprocess.check_call(["ninja", os.path.join(REPO, "build_psyq", tu + ".preproc")], cwd=REPO,
                              stdout=subprocess.DEVNULL)


def generate(exe, tu, only=None, secs=None):
    syms = Syms(exe)
    pre = os.path.join(REPO, "build_psyq", tu + ".preproc")
    types = Types(parse_preproc(pre))
    names = tu_data(tu)
    info = {n: chunk_info(n) for n in names}
    # externs other files have for this TU's data: their types, and they move to this TU's header (see main)
    adopted = foreign_externs(tu, names, types)
    if adopted:
        try:
            types = Types(parse_preproc(pre, "".join(l.split("//")[0].strip() + "\n" for _, l in adopted.values())))
        except Exception as e:  # noqa: BLE001
            print("// foreign externs don't parse here (%s): %s" % (e, " ".join(adopted)))
            adopted = {}
    types.adopted = adopted
    if only:
        sel = set(only)
        if any(info[n][0] == ".bss" for n in sel if n in info):
            sel |= {n for n in names if info[n][0] == ".bss"}
        todo = [n for n in names if n in sel]
    else:
        todo = list(names)
    if secs:
        todo = [n for n in todo if info[n][0] in secs]
    gen = Gen(syms, types)
    errors = {}
    defs = []
    absorbed = {}       # name -> head that covers it
    i = 0
    while i < len(todo):
        n = todo[i]
        i += 1
        sec, size = info[n]
        addr = syms.addr.get(n)
        try:
            if addr is None:
                raise GenError("no address")
            # another name of the symbol (an alias the C code declared) is the one to define
            dn = n
            if n not in types.decls:
                alias = [x for x in syms.by_addr.get(addr, []) if x in types.decls and x != n]
                if alias:
                    dn = alias[0]
            d = types.decls.get(dn)
            t = types.resolve(d.type) if d is not None else None
            char_decl = t is not None and t.kind == "array" and t.n is None and t.of.kind == "int" and t.of.nbytes == 1
            if d is None or char_decl:
                g = guess(syms, dn, addr, size, sec, gen)
                if char_decl and not g[0][2].startswith("char"):
                    g = None
                if g is not None:
                    for k, (gn, ga, gd, gt, gc) in enumerate(g):
                        defs.append(Def(n, gn, ga, sec, gt, decl_text(d.type, gn) if (k == 0 and d is not None) else gd,
                                        k == 0 and d is not None, gc))
                        gen.local[gn] = gt
                        syms.add(gn, ga)
                    continue
            decl = decl_text(d.type, dn)
            if t.kind == "array" and t.n is None:
                es = t.of.size()
                # a following symbol that can't be an object of its own (not on 4 bytes) is more of the array
                while (i < len(todo) and syms.addr.get(todo[i]) == addr + size and info[todo[i]][0] == sec and
                       (addr + size) % 4 and todo[i] not in types.decls):
                    absorbed[todo[i]] = n
                    size += info[todo[i]][1]
                    i += 1
                t = T("array", of=t.of, n=size // es)
                decl = sized(decl, dn, t.n)
            # a type larger than the symbol takes the following symbols (if they are INCLUDE_DATA here too)
            end = addr + size
            while t.size() > end - addr:
                if i >= len(todo) or syms.addr.get(todo[i]) != end or info[todo[i]][0] != sec:
                    raise GenError("type is %d bytes, the symbol %d" % (t.size(), size))
                if todo[i] in types.decls:
                    raise GenError("type is %d bytes and covers %s, which is declared too" % (t.size(), todo[i]))
                absorbed[todo[i]] = n
                end += info[todo[i]][1]
                i += 1
            size = end - addr
            defs.append(Def(n, dn, addr, sec, t, unconst(decl, dn), True))
            gen.local[dn] = t
            # bytes behind the declared object (up to the next symbol) that are more than alignment padding:
            # objects of their own
            ra = (addr + t.size() + 3) & ~3
            if end - ra >= 4:
                if sec != ".bss" and any(syms.rd(addr + t.size(), ra - addr - t.size())):
                    raise GenError("non-zero bytes behind the %d byte object" % t.size())
                for gn, ga, gd, gt, gc in guess(syms, "dword_%08X" % ra, ra, end - ra, sec, gen):
                    defs.append(Def(n, gn, ga, sec, gt, gd, False, gc))
                    gen.local[gn] = gt
                    syms.add(gn, ga)
        except GenError as e:
            errors[n] = str(e)
    for df in defs:
        n, t = df.name, df.t
        try:
            nxt = [x for x in defs if x.sec == df.sec and x.addr > df.addr]
            if (df.addr % t.align()) or (t.kind in ("array", "struct", "union") and df.addr % 4):
                raise GenError("address %08X is not aligned for its type" % df.addr)
            decl = const_decl(df.decl, n) if df.sec == ".rdata" else df.decl
            gen.refs = set()
            df.refs = gen.refs
            if df.sec == ".bss":
                df.text = "%s BSS;" % decl
            else:
                init = gen.value(df.addr, t, "")
                df.text = "%s = %s;" % (decl, init)
            if df.comment:
                df.text += " // %s" % df.comment
        except GenError as e:
            errors[df.head] = "%s: %s" % (n, e)
    # sizes: every byte of the replaced chunks must be produced (objects + alignment padding of the next one)
    by_head = {}
    for df in defs:
        by_head.setdefault(df.head, []).append(df)
    for h, ds in by_head.items():
        if h in errors:
            continue
        sec, size = info[h]
        a0 = syms.addr[h]
        end = a0 + size + sum(info[x][1] for x, hh in absorbed.items() if hh == h)
        last = ds[-1]
        tail = end - (last.addr + last.t.size())
        if tail < 0 or tail >= 4 or (sec != ".bss" and any(syms.rd(last.addr + last.t.size(), tail))):
            errors[h] = "objects end at %08X, the symbol at %08X" % (last.addr + last.t.size(), end)
    return todo, defs, absorbed, errors, types, syms, gen


_SRC_LINES = None


def src_lines():
    """(path, line) of every line of src/ (headers first), read once"""
    global _SRC_LINES
    if _SRC_LINES is None:
        _SRC_LINES = []
        files = []
        for root, _, fs in os.walk(os.path.join(REPO, "src")):
            files += [os.path.join(root, f) for f in fs if f.endswith((".h", ".c"))]
        files.sort(key=lambda p: (not p.endswith(".h"), p))
        for p in files:
            for line in open(p, encoding="latin1"):
                _SRC_LINES.append((p, line))
    return _SRC_LINES


def find_extern(name):
    """(path, line text) of the extern declarations of name in src/ (headers first)"""
    r = re.compile(r"\s*extern\b[^;]*?[\s*(]%s\s*[\[);]" % re.escape(name))
    return [(p, l) for p, l in src_lines() if name in l and r.match(l)]


def find_proto(name):
    r = re.compile(r"\b%s\s*\(" % re.escape(name))
    return [(p, l) for p, l in src_lines() if p.endswith(".h") and name in l and r.search(l) and l.rstrip().endswith(";")]


def header_for(tu):
    # src/common.h is the macro header everything includes
    return os.path.join(REPO, "src", ("common_tu" if tu == "common" else tu) + ".h")


def add_externs(tu, lines):
    path = header_for(tu)
    guard = "_%s_H_" % os.path.basename(path)[:-2].upper()
    if not os.path.exists(path):
        open(path, "w").write("#ifndef %s\n#define %s\n\n#endif\n" % (guard, guard))
        c = os.path.join(REPO, "src", tu + ".c")
        text = open(c).read()
        incs = list(re.finditer(r'^#include .*\n', text, re.M))
        k = incs[-1].end()
        text = text[:k] + '#include "%s"\n' % os.path.basename(path) + text[k:]
        open(c, "w").write(text)
    text = open(path).read()
    k = text.rindex("#endif")
    text = text[:k].rstrip("\n") + "\n\n" + "\n".join(lines) + "\n\n" + text[k:]
    open(path, "w").write(text)


def main(argv):
    args = [a for a in argv if not a.startswith("--")]
    secs = [a.split("=", 1)[1] for a in argv if a.startswith("--sec=")]
    exe = open(args[0], "rb").read()[0x800:]
    tu = args[1]
    if "--write" in argv:
        include_declaring_headers(tu, secs)
        global _SRC_LINES
        _SRC_LINES = None
    todo, defs, absorbed, errors, types, syms, gen = generate(exe, tu, args[2:] or None, secs)
    ok = [d for d in defs if d.head not in errors]
    # an INCLUDE_DATA that stays between C definitions of its section would leave the compiler in the wrong
    # section (the included assembly switches sections behind its back): nothing behind it is written
    for sec in (".rdata", ".data"):
        bad = [syms.addr[n] for n in todo if n in errors and n in syms.addr and chunk_info(n)[0] == sec]
        if bad:
            cut = min(bad)
            heads = {d.head for d in ok if d.sec == sec and d.addr > cut}
            drop = [d for d in ok if d.head in heads]
            if drop:
                print("// %d %s definitions behind %08X are left out" % (len(drop), sec, cut))
                ok = [d for d in ok if d not in drop]
    for n in todo:
        if n in errors:
            print("// %s: %s" % (n, errors[n]))
    for d in ok:
        print(d.text)
    new_ext = []
    const_fix = []
    moves = []      # (path, line): externs in other files that move to this TU's header
    hdr_incs = []   # headers this TU's header needs for them
    inc_here = set()
    for d in ok:
        if d.name in types.adopted:
            path, line = types.adopted[d.name]
            if path.endswith(".c"):
                decl = line.split("//")[0].strip().rstrip(";")[len("extern"):].strip()
                if d.sec == ".rdata":
                    decl = const_decl(decl, d.name)
                new_ext.append("extern %s;" % decl)
                moves.append((path, line))
                for w in re.findall(r"[A-Za-z_]\w*", re.split(r"\b%s\b" % re.escape(d.name), decl)[0]):
                    if w in types.typedefs:
                        h = header_defining(w)
                        if h and h not in hdr_incs:
                            hdr_incs.append(h)
            else:
                inc_here.add(os.path.relpath(path, os.path.join(REPO, "src")))
            continue
        if not d.declared:
            ext = "extern %s;" % (const_decl(d.decl, d.name) if d.sec == ".rdata" else d.decl)
            new_ext.append(ext)
        elif d.sec == ".rdata" and not node_is_const(types.decls[d.name].type):
            const_fix.append(d.name)
    print("\n// new externs (%s.h):" % tu)
    for e in new_ext:
        print(e)
    if const_fix:
        print("// externs made const:", " ".join(const_fix))
    # symbols the initialisers use that this TU doesn't see: include the header that declares them
    local = {d.name for d in ok}
    includes = set()
    for d in ok:
        for r in sorted(d.refs):
            if r in local or r in types.decls or r in types.funcs:
                continue
            hs = [p for p, _ in find_extern(r) if p.endswith(".h")]
            if not hs:
                hs = [p for p, _ in find_proto(r)]
            if hs:
                includes.add(os.path.relpath(hs[0], os.path.join(REPO, "src")))
            else:
                print("// %s uses %s, which nothing declares" % (d.name, r))
    # functions nobody declares: a prototype in the header of the TU that has them (from its definition if it is C)
    protos = {}
    tus = split.load_tus()
    parsed = {}
    for name, fnode in sorted(gen.protos.items()):
        if find_proto(name):
            continue
        a = syms.addr[name]
        owner = [n for n, start in tus if start <= a][-1] if a < GAME_TEXT_END else tu
        if owner not in parsed:
            parsed[owner] = Types(parse_preproc(os.path.join(REPO, "build_psyq", owner + ".preproc"))) if owner != tu else types
        node = parsed[owner].funcnodes.get(name, fnode)
        text = ("%s;" % decl_text(named(node, name), name)) if node is not None else "void %s();" % name
        protos.setdefault(owner, []).append(text)
        if owner != tu:
            includes.add(os.path.basename(header_for(owner)))
    for owner, lines in protos.items():
        print("// prototypes for %s:" % os.path.basename(header_for(owner)), " ".join(lines))
    includes |= inc_here
    for h in sorted(includes):
        print('// #include "%s"' % h)
    for path, line in moves:
        print("// moves here from %s: %s" % (os.path.basename(path), line.strip()))
    if "--write" in argv:
        path = os.path.join(REPO, "src", tu + ".c")
        text = open(path).read()
        heads = {}
        for d in ok:
            heads.setdefault(d.head, []).append(d.text)
        for h, texts in heads.items():
            text = text.replace("INCLUDE_DATA(%s);" % h, "\n".join(texts), 1)
            for x, hh in absorbed.items():
                if hh == h:
                    text = re.sub(r"^INCLUDE_DATA\(%s\);[^\n]*\n" % x, "", text, count=1, flags=re.M)
        open(path, "w").write(text)
        for n in const_fix:
            for p, line in find_extern(n):
                src = open(p).read()
                decl = line.strip().rstrip(";")
                fixed = const_decl(decl[len("extern"):].strip(), n)
                src = src.replace(line, line.replace(decl, "extern " + fixed), 1)
                open(p, "w").write(src)
        if new_ext:
            add_externs(tu, new_ext)
            add_includes(header_for(tu), hdr_incs)
        for mpath, line in moves:
            src = open(mpath).read().replace(line, "", 1)
            inc = '#include "%s"' % os.path.basename(header_for(tu))
            if inc not in src:
                incs = list(re.finditer(r'^#include .*\n', src, re.M))
                k = incs[-1].end()
                src = src[:k] + inc + "\n" + src[k:]
            open(mpath, "w").write(src)
        for owner, lines in protos.items():
            add_externs(owner, lines)
        if includes:
            c = os.path.join(REPO, "src", tu + ".c")
            text = open(c).read()
            incs = list(re.finditer(r'^#include .*\n', text, re.M))
            k = incs[-1].end()
            add = "".join('#include "%s"\n' % h for h in sorted(includes) if '#include "%s"' % h not in text)
            open(c, "w").write(text[:k] + add + text[k:])
        print("wrote %s: %d definitions" % (path, len(ok)))


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
