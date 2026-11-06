# Building the whole executable

The executable is built from one C file per translation unit (`config/tus.txt`, `src/<tu>.c`).
Functions that are not decompiled yet are pulled in with `INCLUDE_ASM(name)`, data that is not
decompiled yet with `INCLUDE_DATA(name)`; both include assembly generated from your own copy of the
executable, so nothing derived from the game is committed (`asm/` is git-ignored).

```
python scripts/split.py SLUS_008.54      # once (and when symbol_addrs.txt / config/ change): writes asm/
python build.py                          # builds build_psyq/jade_cocoon.exe
python scripts/exe_diff.py SLUS_008.54   # word-by-word comparison with the original
python scripts/sym_diff.py               # symbols that are not at their original address (layout drift)
python scripts/check_match.py SLUS_008.54 --all   # every "// Matched" function against the original
```

## Result

Everything the linker places is identical to the original: 126464 of 126464 words (code, `.rdata`,
`.data`, `.bss`), all 3516 symbols at their original address (library code and data linked from the
PSY-Q 4.4 objects), every game function compiled from C.
What is not reproduced: the executable header's size field and the 250 KB of trailing bss/garbage
after the linked image (7 non-zero bytes at 0x800A05A0..0x800C9E88), so the file hash differs.

## How it hangs together

* `asm/f/<symbol>.s` code, `asm/d/<symbol>.s` data symbol (each owns the bytes up to the next symbol).
* The PSY-Q libraries are linked from the real 4.4 objects (see below); library code is not decompiled.
* TU bounds: `config/tus.txt`. Anchors (`__FILE__` strings) name main/common/effect/sound/cd/event; the
  others are inferred from `.rdata` references and named by address - rename them when you know better.
  Splitting a real TU into pieces does not change the output, only organisation.
* Data of a TU = chunks listed in the TU file in address order (owner = smallest TU that references
  anything at or after the symbol). It can be wrong for `.data`/`.bss` globals; moving an `INCLUDE_DATA`
  line to another TU file keeps the output identical as long as the per-section order is kept.
* Symbols named after an address (`dword_8007CB78`) that are not in `symbol_addrs.txt` are picked up from
  the C sources and become aliases / split points.

## PSY-Q libraries

`config/lib_objs.txt` is the link order of the library part: `LIB MODULE` lines are modules of
`libs/psyq4.4/LIB/*.LIB` (build.py extracts them to `build_psyq/libobj/`), `asm ADDR SIZE [SECTION ADDR
SIZE ...]` lines are code that is no 4.4 module and stays assembly from the executable (`asm/lib/text_ADDR.s`):
`strchr`/`strrchr` (the game's copy has less alignment padding) and `MCXDSR` (see bsshead). (The game code at
0x8004D924..0x8004DDC8 that used to be such a piece is the end of `ftg_draw.c` now.) 312 modules, everything else is
`asm`. `scripts/lib_match.py SLUS_008.54` finds the modules again (`--write` rewrites the file).

Two things psylink 2.73 does differently from the linker the game was built with, worked around in build.py:

* With common (`.comm`) symbols in the link it aligns every `.bss` contribution to 8 bytes, the game's
  `.bss` is packed. The commons of the modules are therefore defined by build.py itself, behind their
  module (`config/lib_commons.txt`, addresses read from the code that uses them by
  `lib_match.py --commons`), and the `.bss` of each module is put on 8 bytes with a pad piece.
* A group starts on 8 bytes, the `.bss` of the game starts at 0x8008B484 right behind the library `.data`.
  The last 4 bytes of `MCXDSR`'s `.data` (zero) are a `.bss` piece in front of the game (`bsshead`).

Library symbols get the names the objects export (no `sub_` names); names in `symbol_addrs.txt` for library
addresses the objects don't export (statics, data inside a module) become `equ`s.

## Rules when decompiling

* Never define data in C that is also in `asm/d`: remove its `INCLUDE_DATA` line, or keep the C object
  smaller than the symbol and list the rest in `config/c_data.txt` (becomes `<name>_tail`).
  A function must not emit its own `.rdata` (string literals, switch tables) next to the asm copy:
  reference the existing symbol (`printf(aAssertionFaile_0, aSoundC, 631)`), or for switch tables
  truncate the asm chunk (`config/c_rodata.txt`) so the compiler's table replaces it.
* A symbol span larger than the compiled function means a hidden function follows: add it to
  `symbol_addrs.txt` (`sub_8001C314`, `CopyHalfwords_800403A8` were found like this).
* `sym_diff.py` shows the first symbol that drifts: the one before it has the wrong size.

## Data in C

The executable's data is C: each TU file defines its `.rdata` (`const`), `.data` and `.bss` in address order, with
the externs in the TU's header (no `INCLUDE_DATA` is left).

* Jump tables of functions that are still assembly are C too: `gen_asm.jump_targets()` finds the words of the data
  that point into the middle of a function and `emit_function()` puts a global label `jtgt_XXXXXXXX`
  (`gen_asm.jump_label`) at each of those instructions of the generated asm (split.py, overlays.py). The table is
  then an array of those labels, `void* const jpt_8007486C[6] = { jtgt_80035F2C, ... };`, with
  `extern char jtgt_80035F2C[];` and the table's extern in the TU's header. A zero word in front of such a table
  (the original table's `.align 3`) is `const int dword_80074818 = 0;`; a zero word behind it that is the next
  (compiled) table's alignment is left out, the compiler pads.
* When the function is written in C, its switch emits the table: delete the C table, its `jtgt_` externs and the
  zero word in front of it (the compiler's `.align 3` puts it back). A `jtgt_` name that is left over no longer
  links (the label is gone with the asm).

* `python scripts/gendata.py SLUS_008.54 TU [--sec=.rdata|.data|.bss] [--write]` turns a TU's `INCLUDE_DATA` lines
  into definitions with initialisers from the executable. The type is the one the code declares (the TU's
  preprocessed source, or an extern in another file, which then moves to the TU's header), else it is guessed from
  the bytes (strings, pointer tables, `byte_`/`word_`/`dword_`); pointers become references to their symbols.
* `.bss` variables are `T name BSS = 0;` (`= { 0 }` for aggregates, `BSS` is in `common.h`): without the zero
  initialiser a variable that the file also declares `extern` becomes a common symbol, and psylink aligns all
  `.bss` to 8 bytes once there are commons. With it the compiler puts the variable in place, into `.bss`.
* An `INCLUDE_DATA` must not stay between C definitions of the same section: the included assembly switches
  sections without the compiler knowing, so the next C definition lands in `.text`.
* Names the code has for a place inside a C object (`playerYan_8008B594` is `saveData_8008B570.inv_24`) are link
  time equates of their address: `config/aliases.txt` (build.py).
* `scripts/regendata.py SLUS_008.54 TU NAME... --gen` turns definitions back into `INCLUDE_DATA` and generates
  them again (after their declared type changed).
* Which TU a `.data`/`.bss` symbol belongs to: `scripts/data_owners.py` (the first TU whose code uses it, in link
  order) moves `INCLUDE_DATA` lines; main.c keeps the big `.bss` run that code all over the game uses.

## Overlays

`python scripts/overlays.py NAME <iso>.bin SLUS_008.54 [--discover] [--init-src]` extracts the overlay
from the disc, finds its functions (`overlays/<name>.sym`), writes `asm/overlays/<name>/*.s` and builds
`src/overlays/<name>.c` (`INCLUDE_OVERLAY_ASM(name, sym)` for functions not decompiled yet) into
`build_psyq/NAME.BIN`. `scripts/ovl_diff.py NAME` lists the functions that differ.

PSY-Q library modules inside an overlay (LOAD carries LIBMCRD.LIB's LIBMCRD, USERFUNC and BIOS) are linked from
the 4.4 .LIB like the executable's: `config/ovl_lib_objs.txt` gives the modules and where their sections start.
The overlay's symbols in those ranges get no asm, the C source must not include them, and the overlay's own .bss
(`gamebss=`) is assembled as .bss so that it lands between the modules' .data and .bss. The modules' references
into the executable's library code are resolved from `build_psyq/jade_cocoon.map` (build the executable first).

## Hash check

`python scripts/verify.py SLUS_008.54 <iso>.bin` builds the executable and every overlay and compares the
SHA-1 of each built image with the original (and with `config/hashes.txt`; `--update` rewrites that file).
Currently OK: exe image (the linked part, without the trailing bss) and NAME.BIN.

### Data of an overlay in C

The overlays' data is C like the executable's, with the externs in `src/overlays/<name>.h`:

    python scripts/ovldata.py split NAME <iso>.bin SLUS_008.54 --write   # blobs -> symbols (.sym + source lines)
    python scripts/overlays.py NAME <iso>.bin SLUS_008.54                # asm of the new symbols, preprocessed source
    python scripts/ovldata.py gen NAME <iso>.bin SLUS_008.54 --write     # INCLUDE_OVERLAY_ASM data lines -> C
    python scripts/ovldata.py regen NAME <iso>.bin SLUS_008.54 SYMBOL... # again, after a type changed

`split` cuts the data blobs at the places the code builds with lui/addiu or lui/load/store (also through an index
added to the high part), the pointers in the data and the address names of the C source; strings get IDA-like
names. `gen` (scripts/ovlgen.py, on top of gendata.py) types a symbol by the overlay's declaration, by a typed pointer
that points at it, or from its bytes; ints that hold a symbol's address and numbers in pointer members are written
as casts. Symbols of an overlay's .sym file that are data but have no data prefix are marked `// data`
(`gen_asm.overlay_data_names`). The first word (in front of `.rdata`) is `int x SDATA = n;` (`common.h`).

Jump tables of functions that are still assembly are arrays of `jtgt_` labels as in the executable (see Data in C;
the link of an overlay gives no `equ` to `jtgt_` names, they come from the asm). What stays assembly: a definition that would sit behind assembly that follows a
C definition of the same section with no function in between (the compiler would not switch back from the section
the assembly ends in; ovlgen keeps the smaller side as assembly). Struct initialisers follow the struct: after a
layout change, `regen` them.

### Switch statements in overlays

The data in front of an overlay's code (strings, jump tables) is linked as `.rdata`, behind a one word header
that goes to `.sdata` (so the compiler's `.align 3` for a table counts from the end of the header, as in the
original). A switch compiled by cc1psx emits its jump table into `.rdata`, so the original table has to be
cut out of the data blob and the compiler's copy has to land in the same place:

    python scripts/carve.py NAME sub_XXXXXXXX     # after an overlays.py run

adds `jpt_<table>` and `dword_<rest>` symbols to `overlays/<name>.sym` and puts their `INCLUDE_OVERLAY_ASM`
lines behind the function (build stays identical); while the function stays assembly, turn the `jpt_` line into
the C label table (Data in C). Write the function in C and delete the table (and its `jtgt_` externs): the table comes from
the compiler, `dword_<rest>` (kept behind the function) holds the data that followed it.
Case labels may sit inside nested blocks (`case 0:` inside the `if` that cases 1, 2 and 4 share) - the table
entries show which instruction each case enters.

### Overlays built from several source files

Like the executable, an overlay was linked from several objects, and each object's `.rdata` starts where the
previous one ended, so the compiler's `.align 3` for a jump table counts from that object's start. A table that
sits 4 bytes off from where a single source file puts it marks a file boundary. The overlay is then
`src/overlays/<name>.c`, `<name>_2.c`, `<name>_3.c`, ... (linked in that order, declarations shared in
`<name>.h`):

    python scripts/ovl_split_tu.py NAME TEXT:RDATA [TEXT:RDATA ...]

starts a new file at the function at TEXT, with its `.rdata` from RDATA (GAME: `800A55B0:800A061C
800A5804:800A0660`, EVENTFNC: `800BCB3C:800B6D98`). The text boundaries are only known to be at or before
the first function that uses the file's `.rdata`.
