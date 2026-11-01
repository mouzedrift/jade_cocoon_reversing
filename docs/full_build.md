# Full build (C + generated assembly)

`python build.py` only compiles the decompiled C, so function addresses differ from the
original and a function can only be checked on its own (`scripts/check_match.py`).

`scripts/full_build.py` builds the whole game-code area (0x80010000 - 0x8004D924) instead:

* functions marked `// Matched` **and** verified by `check_match.py` are compiled from C,
* every other function is generated from the original executable by `scripts/gen_asm.py` and
  pulled in as inline `asm()` (this is the "INCLUDE_ASM" idea - it goes through `CC1PSX` and
  `ASPSX` like any C function, no new tools needed),
* everything is emitted in address order, so each function lands at its real address,
* the link script puts `.text` first (like the original) and defines library / overlay
  functions that are only referenced by address.

```
python build.py                                # builds the C and is used to find the matching functions
python scripts/full_build.py SLUS_008.54      # writes build_psyq/full.exe and compares it with the original
```

Status when this was written: 62504 of 63049 words identical. All 545 remaining differences are
`lui`/load/store immediates in C functions that point at globals - the data sections
(`.rdata`, `.data`, `.bss`) are not laid out like the original yet. Every generated assembly
function, and every `jal`/branch, is already identical.

## Notes

* The generated assembly can be assembled and linked on its own: all 935 symbols of the game
  code area reproduce the original bytes exactly (0 differing words), so the assembler syntax
  emitted by `gen_asm.py` is trustworthy. Files given to `ASPSX` directly need CRLF line endings
  (text that goes through `CC1PSX` does not).
* The symbol list is incomplete: a "matched" function can be shorter than its symbol span
  because the bytes behind it are another function without a symbol (`sub_8001C2FC` is one).
  `full_build.py` keeps those bytes as raw words behind the C function (`<name>_tail`).
* Generated assembly is not committed (it comes from the game executable); `full_build.py`
  produces it on the fly.

## Next steps

* Match the data layout: define `.rdata`/`.data`/`.bss` in the order of the original (per TU, see
  `translation_units.md`) so the remaining 545 words fall into place and the exe can be checked by hash.
* Overlays (e.g. `NAME.BIN`) can use the same approach: extract the overlay, generate its assembly
  with a different base address (overlays are loaded at 0x800A05A0 / 0x800A4088 / ...), link with
  `psylink` at that address.
