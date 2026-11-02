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
`.data`, `.bss`), all 2682 symbols at their original address, 305 functions compiled from C.
What is not reproduced: the executable header's size field and the 250 KB of trailing bss/garbage
after the linked image (7 non-zero bytes at 0x800A05A0..0x800C9E88), so the file hash differs.

## How it hangs together

* `asm/f/<symbol>.s` code, `asm/d/<symbol>.s` data symbol (each owns the bytes up to the next symbol),
  `asm/lib/*` the PSY-Q library part as raw blobs (library code is not decompiled; it is only there so
  the data of the game lands at its real address). The libs are not linked from the `.lib` files.
* TU bounds: `config/tus.txt`. Anchors (`__FILE__` strings) name main/common/effect/sound/cd/event; the
  others are inferred from `.rdata` references and named by address - rename them when you know better.
  Splitting a real TU into pieces does not change the output, only organisation.
* Data of a TU = chunks listed in the TU file in address order (owner = smallest TU that references
  anything at or after the symbol). It can be wrong for `.data`/`.bss` globals; moving an `INCLUDE_DATA`
  line to another TU file keeps the output identical as long as the per-section order is kept.
* Symbols named after an address (`dword_8007CB78`) that are not in `symbol_addrs.txt` are picked up from
  the C sources and become aliases / split points.

## Rules when decompiling

* Never define data in C that is also in `asm/d`: remove its `INCLUDE_DATA` line, or keep the C object
  smaller than the symbol and list the rest in `config/c_data.txt` (becomes `<name>_tail`).
  A function must not emit its own `.rdata` (string literals, switch tables) next to the asm copy:
  reference the existing symbol (`printf(aAssertionFaile_0, aSoundC, 631)`), or for switch tables
  truncate the asm chunk (`config/c_rodata.txt`) so the compiler's table replaces it.
* A symbol span larger than the compiled function means a hidden function follows: add it to
  `symbol_addrs.txt` (`sub_8001C314`, `sub_800403A8` were found like this).
* `sym_diff.py` shows the first symbol that drifts: the one before it has the wrong size.

## Overlays

`python scripts/overlays.py NAME <iso>.bin SLUS_008.54 [--discover] [--init-src]` extracts the overlay
from the disc, finds its functions (`overlays/<name>.sym`), writes `asm/overlays/<name>/*.s` and builds
`src/overlays/<name>.c` (`INCLUDE_OVERLAY_ASM(name, sym)` for functions not decompiled yet) into
`build_psyq/NAME.BIN`. `scripts/ovl_diff.py NAME` lists the functions that differ.

## Hash check

`python scripts/verify.py SLUS_008.54 <iso>.bin` builds the executable and every overlay and compares the
SHA-1 of each built image with the original (and with `config/hashes.txt`; `--update` rewrites that file).
Currently OK: exe image (the linked part, without the trailing bss) and NAME.BIN.

### Switch statements in overlays

The data in front of an overlay's code (strings, jump tables) is linked as `.rdata`, behind a one word header
that goes to `.sdata` (so the compiler's `.align 3` for a table counts from the end of the header, as in the
original). A switch compiled by cc1psx emits its jump table into `.rdata`, so the original table has to be
cut out of the data blob and the compiler's copy has to land in the same place:

    python scripts/carve.py NAME sub_XXXXXXXX     # after an overlays.py run

adds `jpt_<table>` and `dword_<rest>` symbols to `overlays/<name>.sym` and puts their `INCLUDE_OVERLAY_ASM`
lines behind the function (build stays identical). Write the function in C and delete the `jpt_` line: the
table comes from the compiler, `dword_<rest>` (kept behind the function) holds the data that followed it.
Case labels may sit inside nested blocks (`case 0:` inside the `if` that cases 1, 2 and 4 share) - the table
entries show which instruction each case enters.
