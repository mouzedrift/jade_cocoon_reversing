# Full build (C + generated assembly)

`python build.py` only compiles the decompiled C, so function addresses differ from the
original and a function can only be checked on its own (`scripts/check_match.py`).

`scripts/full_build.py` builds a whole image instead - the game code of the executable
(0x80010000 - 0x8004D924) or an overlay:

* functions marked `// Matched` are compiled from C,
* every other function is generated from the original image by `scripts/gen_asm.py` and pulled in
  as inline `asm()` (the "INCLUDE_ASM" idea - it goes through `CC1PSX` and `ASPSX` like any C
  function, no new tools needed),
* everything is emitted in address order, so each function lands at its real address,
* a C function that does not reproduce the original bytes in the linked image is replaced by
  its assembly and the image is rebuilt, so "Matched" is always checked against the real layout.

```
python scripts/full_build.py SLUS_008.54                               # build_psyq/full.exe
python scripts/overlays.py NAME "Jade Cocoon (USA).bin" SLUS_008.54    # build_psyq/NAME.BIN
```

## What the numbers mean

Global data is **not** pinned to its original address (`--pin-data` does that, but then data layout
mistakes are hidden, so it is off by default). Symbols that are not defined anywhere (library code,
other images, overlay data that is not in C yet) have to be given their original address by the
link script, since the libraries are not relinked here.

Executable, when this was written: 62543 of 63049 words identical; the other 506 words are all
`lui`/load/store immediates in C functions that point at a global - i.e. the only thing missing for an
identical game-code area is the layout of `.rdata`/`.data`/`.bss`. 0 words differ for any other reason.

NAME.BIN: 1471 of 1471 words identical (18 of its 24 functions are still assembly).

## Notes

* All 935 symbols of the game-code area reproduce the original bytes when assembled from the
  generated assembly alone, so the syntax emitted by `gen_asm.py` is trustworthy. Files given to
  `ASPSX` directly need CRLF line endings (text that goes through `CC1PSX` does not).
* The symbol list is incomplete (e.g. `sub_8001C2FC` covers a function without a symbol), such
  functions simply stay assembly until the symbol is added.
* Generated assembly is not committed (it comes from the game); the scripts produce it on the fly.
  `overlays/<name>.sym` only holds addresses.
* Overlay function boundaries are guessed (`overlays.py --discover`): call targets, code after
  `jr $ra`, pointer tables - never splitting a function that a branch or `j` crosses.

## Next steps

* Lay out the data sections like the original (per TU, see `translation_units.md`).
* More overlays: add the overlay to `LOAD_ADDRESSES` in `overlays.py` if needed and run it.
* Teach `permute.py` about overlays.
