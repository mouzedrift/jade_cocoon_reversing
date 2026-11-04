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
| `D:/WORK/PSUS/EVENT.C` | 0x80074BA4 | `CreateEventList_800435B4` .. `FreeEventList_80043A5C` | full path, built outside the usual setup |

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

## PSY-Q objects between the game TUs

A line `obj NAME ADDR` in config/tus.txt links libs/psyq4.4/LIB/NAME as is at that point of the link order. The
SN start-up 2MBYTE.OBJ (`__main`, `__SN_ENTRY_POINT`, the `_ramsize` words; it reads the game's `_stacksize`) sits
at 0x80010474 between `system` and `party`. Its 4-byte .sbss (the start-up's saved ra) is why .sbss is linked into
the data group: the game's only .sdata word (gpBase_8008B484 in main.c, the gp base) comes first, then that word,
where the start-up's bss clear begins; config/lib_objs.txt pads the .bss on both ends (bsshead / bsstail) to the
8-byte bounds the original's commons gave it.

## File names of the inferred TUs

Only the six anchors above have their original file names. The other TUs were first named
`tu_<first address>`; they now carry descriptive names chosen from their contents (config/tus.txt
gives the link order and start address; config/renames.txt maps the old names, so re-running
scripts/apply_renames.py fixes `#include "tu_XXXXXXXX.h"` lines in older branches):

| file | was | contents |
| --- | --- | --- |
| party.c | tu_80010228 | system shutdown/events, minion and item roster getters, model task driver |
| unit_stats.c | tu_80010B90 | battle strings, level-up/exp math, unit stat adjustment, model-fuse steps, spore task |
| battle_damage.c | tu_80013358 | damage formula, item use on a unit |
| effect_data.c | tu_80014954 | most of the executable's .data, effect-object spawn and update tasks |
| effect_light.c | tu_80016BF4 | point-light flashes, glow models, radial sprite bursts |
| effect_model.c | tu_800174F8 | morphing/scaling effect models, MDEC effect, effect-target helpers |
| effect_cmd.c | tu_80018430 | effect request dispatch (hit flags/variants, effect rows), battle command actions |
| minion_init.c | tu_80018E5C | species name strings, minion init (stats, skills, magic, rank) |
| engine.c | tu_80019BF0 | game-data lookup tables, scene light and fade, display/OT, pad and button config, actor API |
| model.c | tu_8001EA48 | actor script/animation/draw, FTG/model/effect file loading, map/area streaming tasks |
| tim.c | tu_80028C60 | room-load callback, TIM parse/load, sprite/poly setup, HSV and tint VRAM ops |
| menu_draw.c | tu_8002A1BC | reverb setup, text lists, UI windows, portraits |
| menu_window.c | tu_8002AAF0 | menu item window frames, text boxes, button help bar |
| element_grid.c | tu_8002B228 | 2x2 element icon grid |
| ui_gauge.c | tu_8002B2A4 | element icons, scroll arrows, gauge bars |
| ui_sprites.c | tu_8002BE10 | UI TIY sprite loading, numbers, item/magic lists |
| ability_menu.c | tu_8002CE28 | ability list and icons, party target select |
| family_tree.c | tu_8002D738 | rank names, target-list filter, minion family tree |
| status_panel.c | tu_8002DA3C | unit status panel: stat deltas, element chart, stat grid |
| unit_gauges.c | tu_8002ECE0 | HP/MP gauges, unit status window, status ailment icons |
| party_window.c | tu_8002F6F8 | party slot windows, Levant stats, text drawing |
| sound_seq.c | tu_80030D00 | SEP/VAB play/stop/fade, SFX, battle music |
| skill_anim.c | tu_80031870 | skill slot to animation index |
| skills.c | tu_800318C8 | ability action table, learned checks, MP cost, ability names |
| unit_query.c | tu_80031A94 | PolyFT4 scale/rotate/flip helpers, UnitStatus/Minion getters, usability checks |
| msg_window.c | tu_80034068 | message windows, item-received window |
| camera.c | tu_80036528 | pad vibration, camera tasks (battle intro, orbit, spline, zoom, follow, shake) |
| cdread.c | tu_8003C6C8 | DATA.001 reader, CdSeek/CdRead, loading icon |
| cursor.c | tu_8003CF88 | "next" prompt and cursor hand sprites |
| pad_text.c | tu_8003D198 | pad helpers, grid cursor, text window typing/drawing/measuring |
| font.c | tu_8003E884 | character widths, DrawText/DrawColorText |
| util.c | tu_8003EF74 | number/text encoding, font setters, list/pool heap, mem copy, GameLoop |
| display_mode.c | tu_80040658 | SetDisplayMode |
| boot.c | tu_80040718 | game defaults, public TIY/FTG load, copyright screen, intro movies |
| movie.c | tu_80040C8C | MDEC/STR movie playback, ExecOverlay |
| winframe.c | tu_80041E68 | window frame drawing and its edge/shade tables |
| skel_draw.c | tu_80043AF8 | event entry alloc, billboards, rotated sprites, skeleton draw/blend |
| ftg_draw.c | tu_8004B0A8 | FTG polygon drawers, GTE light/camera setup, anim frame accessors |
