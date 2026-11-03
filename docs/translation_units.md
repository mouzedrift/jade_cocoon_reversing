# Translation unit boundaries

There is no symbol/debug info for the game code, so TU boundaries have to be inferred.
Linker order is ascending address, and each TU's `.rdata`/`.data`/`.bss` is laid out contiguously
in that same order, so a function's data references tell you which TU it lives in.

## Anchors (hard evidence)

The `assert()` macro embeds `__FILE__`, and those strings sit in `.rdata` in TU order:

| `__FILE__` string | rodata addr | code that references it | notes |
| --- | --- | --- | --- |
| `MAIN.C` | 0x80071B58 | `InitGame_80010110` (0x80010110) | already `main.c` |
| `COMMON.C` | 0x80071F8C | `sub_80012BB0`, `sub_80013228` | |
| `EFFECT.C` | 0x80072128 | `sub_800148F4` | |
| `SOUND.C` | 0x80074474 | `LoadSoundSeqFromBuffer_800304D0`, `LoadSoundFromBuffer_800307B4`, `LoadSound_80030A84` | already `sound.c` |
| `CD.C` | 0x800748D4 | `cdRomEventErrorHandler_8003BBAC`, `AssertFileRequestQueueEmpty_8003C684` | |
| `D:/WORK/PSUS/EVENT.C` | 0x80074BA4 | `sub_800435B4` .. `sub_80043A5C` | full path, built outside the usual setup |

Rodata references rise monotonically with function address across the whole game area
(see `scripts/tu_hints.py`), which confirms the TUs are laid out in address order and gives the
ordering `MAIN < COMMON < EFFECT < ... < SOUND < ... < CD < ... < EVENT`.

## Rough ranges

Boundaries can only be placed between the anchors, not exactly:

| TU | code range (approx.) | evidence |
| --- | --- | --- |
| MAIN.C | 0x80010000 - 0x80011xxx | `main`, `InitGame`; rodata 0x80071B18-0x80071B60 |
| COMMON.C | contains 0x80012BB0 - 0x80013228 | rodata 0x80071F08-0x80072078 |
| EFFECT.C | contains 0x800148F4; probably 0x80013C28 - ~0x800184DC | rodata 0x800720E8+; shares bss 0x8008D3F8 / 0x8008D534 |
| SOUND.C | contains 0x800304D0 - 0x80030C94 | rodata 0x8007444C-0x80074474 |
| CD.C | contains 0x8003BBAC - 0x8003C684 | rodata 0x800748AC-0x800748E0 |
| EVENT.C | contains 0x800435B4 - 0x80043A5C | rodata 0x80074BA4 |

Other signals seen so far:

* 0x8001CD34 - 0x8001D128 is a run of table accessors (`if (idx >= N) return 0; return &table[idx]`),
  all reading `.data` tables at 0x8007CB78-0x8007D914. Almost certainly one TU's worth of
  static data tables (monsters/skills/items - not yet identified).
* `.bss` references to 0x8008D3F8 and 0x8008D534 cluster in 0x800148A0-0x800184DC.
* Functions in between anchors (e.g. 0x80019xxx-0x8002Fxxx) have no file name string, so their
  TU can only be bracketed by neighbouring anchors.

## Ideas for tightening the bounds

* `.rdata` strings from one TU are contiguous: group the rodata strings by first referencing
  function and look for jumps in the reference sequence.
* `.data`/`.bss` locals (non-shared symbols) must appear in the same order as the code that uses them.
* Jump tables (`switch`) are emitted into the owning TU's `.rdata`.
* `scripts/tu_hints.py SLUS_008.54` lists these references per function.

Note: the build does not track header dependencies; use `python build.py -r` after editing a `.h`.
