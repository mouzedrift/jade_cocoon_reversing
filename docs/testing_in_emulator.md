# Testing in the emulator

Two ways to find out what a struct field means at run time in PCSX-Redux:

1. **Lua watches** (`scripts/pcsx-redux/pcsx.lua`). No rebuild needed. Break on a function or a write
   and print registers and struct fields while the game keeps running. Start with this one.
2. **Rebuilt code on a patched disc** (`scripts/patch_disc.py`). Changed overlays and/or the
   executable go into a copy of the disc image. `DEBUG_PRINTF` prints to the TTY. See the
   limits below before you add code.

## Lua watches

Breakpoints need the debugger and the interpreter: Configuration > Emulation, turn on "Enable
debugger" and turn off the dynarec. You can also start with `-debugger -interpreter`. Then load the
script:

```
pcsx-redux -iso "Jade Cocoon (USA).cue" -debugger -interpreter -dofile scripts/pcsx-redux/pcsx.lua -run
```

You can also load it from the Lua console: `Support.extra.dofile("…/scripts/pcsx-redux/pcsx.lua")`.
The script tracks which overlay is loaded at each load address ("Overlay Observer" window, plus a
log line on every `LoadOverlay_80020BF8`). It also adds these functions, which you call from the
Lua console:

```lua
-- print a0..a3/ra and fields of the struct a0 points to, every 60th call, only while BATTLE is loaded
watch{ addr = 0x800BC90C, overlay = "BATTLE.BIN", every = 60, arg = "a0",
       fields = { {"f0", 0x0, "u32"}, {"x_4", 0x4, "s16"}, {"name_10", 0x10, "str"} } }

watch{ addr = 0x8003C7CC, name = "DATA_GetFile", pause = true }   -- pause on the hit
watchWrite{ addr = 0x8008B4D8, size = 2, name = "display.x" }      -- pc/ra of every write
dumpStruct(0x8008B4D8, { {"x", 0, "s16"}, {"y", 2, "s16"} })
hexdump(0x8008B4D8, 64)
print(u32(0x80075AA0), s16(0x8008B4D8), str(0x800A05A4))
clearWatches()
```

Field types are `u8 s8 u16 s16 u32 s32 ptr str`. A watch can also take `filter = function(ptr) return
ptr == 0x800F1234 end` to follow one object. Several overlays share a load address, so set
`overlay` on any watch inside an overlay. Otherwise it fires for whatever code is loaded there.

## Patching the disc image

Build what you want to test, then patch a copy of the image. The input image is never written:

```
export PATH=/home/snake/dev/mgsvenv/bin:$PATH
python scripts/overlays.py BATTLE "Jade Cocoon (USA).bin" SLUS_008.54   # -> build_psyq/BATTLE.BIN
python build.py                                                         # -> build_psyq/jade_cocoon.exe

python scripts/patch_disc.py "Jade Cocoon (USA).bin" BATTLE            # one overlay
python scripts/patch_disc.py "Jade Cocoon (USA).bin" BATTLE MENU --exe # + the rebuilt exe as SLUS_008.54
python scripts/patch_disc.py "Jade Cocoon (USA).bin" --all --exe       # everything in build_psyq/
python scripts/patch_disc.py "Jade Cocoon (USA).bin" MENU=my_menu.bin -o /tmp/x.bin
```

The default output is `build_psyq/jade_cocoon_patched.bin`, with a `.cue` next to it. Open the `.cue`
in PCSX-Redux.

* An overlay is found through the executable's file table (0x80075AA0, positions relative to
  DATA.001), the same way `extract()` in `scripts/overlays.py` finds it.
* An overlay that fits in its original slot (its sector count × 2048) is written in place. If its
  byte size changes, the file table entry is updated, so SLUS_008.54 is rewritten too. Without
  `--exe`, only the table in the disc's own executable changes.
* A bigger overlay cannot grow in place: the next file follows directly, and DATA.001 is followed by
  VOICE.XA. It goes to new sectors appended to the end of the image. Its table entry is pointed
  there, and the volume size in the PVD is updated. DATA.001's directory entry stays as it is; the
  game reaches the file only through the table. The tool warns when an overlay now loads past its
  original end, because the memory there may belong to something else. For example, MENU at
  0x800B66C0 ends 16 bytes before CONFIG/EQUIP at 0x800C29D0.
* EDC/ECC are recomputed for every rewritten MODE2 Form1 sector. Sectors whose data does not change
  are not touched. `--selftest` checks the EDC/ECC code against the original sectors.
* The rebuilt executable is laid over the original file. The original is longer: it has 250 KB of
  trailing bss/garbage and a bigger `t_size`. That bigger `t_size` is kept, so a matching build
  gives an identical file. An executable bigger than the original file is refused.

Check: `patch_disc.py <iso> --all --exe` with matching builds gives an image that is byte-identical
to the input (`cmp`).

## DEBUG_PRINTF (TTY output)

`src/debug_tty.h`:

```c
#include "debug_tty.h"
...
DEBUG_PRINTF(("hp=%d obj=%08x\n", p->hp, (int)p));   /* double parentheses */
```

The macro does nothing unless you build with `JC_DEFINES=DEBUG_TTY`. `build.py` and
`scripts/overlays.py` turn each word of `JC_DEFINES` into a `-D`, and with it unset the commands are
exactly the matching ones:

```
JC_DEFINES=DEBUG_TTY python scripts/overlays.py BATTLE <iso> SLUS_008.54
```

With it set, `DEBUG_PRINTF` calls the BIOS printf (A0 function 3Fh), which writes through the BIOS
putchar. PCSX-Redux shows that output in its log/TTY output. If nothing appears, check the BIOS
TTY/printf logging setting. The call goes through a 3-word stub in `.data` (`li $t2,0xA0; jr $t2;
li $t1,0x3F`), because C cannot set `$t1`. The game's own `printf` (LIBC2, at 0x8004E328) is not
used: its putchar buffers 32 characters before writing. The BIOS printf supports `%d %u %x %c %s`
and widths, but not floats.

**Limit: only a change that moves nothing runs correctly.** The assembly generated for the parts
that are not decompiled uses numbers for addresses in the image (`j` to non-symbol targets,
`lui`/`addiu` address pairs, pointer tables in `.word` data). Adding a print grows `.rdata` (the
format string) and `.text`, so everything behind it moves, and those references still point at the
old places. That holds for overlays and even more for the executable, which every overlay calls
into at fixed addresses. `scripts/overlays.py` warns when that happens:

```
TITLE.BIN: warning: 52 symbols moved (first sub_800A08C8 0x800A08C8 -> 0x800A08E4): ...
```

So for now, use the Lua watches to look at values. Rebuilt code on the disc is good for experiments
that keep the size, such as changing a constant, swapping a branch, or replacing a function body
with one of exactly the same size. `DEBUG_PRINTF` becomes usable once `gen_asm.py` emits symbolic
references for addresses inside the image.
