// SOUNDTST.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

INCLUDE_OVERLAY_ASM(soundtst, dword_800A05A0);

// Matched
extern char name_800AA340[];
int sub_800A51AC()
{
    sub_8001C290();
    DrawIntroMovie_8001AF64(name_800AA340);
    return 6;
}

INCLUDE_OVERLAY_ASM(soundtst, sub_800A51D8);

INCLUDE_OVERLAY_ASM(soundtst, sub_800A5238);

INCLUDE_OVERLAY_ASM(soundtst, dword_800A57D4);
