// PIERCE.BIN: linked for 0x800C6F40, and its calls into the executable land inside functions
// (0x80027724 is in sub_80027708): it was built against an older executable and looks unused.
#include "common.h"
#include "funcs.h"
#include "globals.h"

INCLUDE_OVERLAY_ASM(pierce, dword_800C6F40);

INCLUDE_OVERLAY_ASM(pierce, sub_800C6F58);
INCLUDE_OVERLAY_ASM(pierce, jpt_800C6F44);

INCLUDE_OVERLAY_ASM(pierce, sub_800C7124);
