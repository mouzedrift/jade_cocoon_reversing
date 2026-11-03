// SOUNDTST.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"

INCLUDE_OVERLAY_ASM(soundtst, dword_800A05A0);

// Matched
extern char name_800AA340[];
int sub_800A51AC()
{
    sub_8001C290();
    DrawIntroMovie_8001AF64(name_800AA340);
    return 6;
}

extern void sub_800A5238();
void sub_800A51D8(int* a, short* b)
{
    b[3] = 0x7F;
    b[4] = 0x32;
    b[0] = 0;
    b[1] = 0;
    b[2] = 0;
    b[5] = 0;
    a[2] = (int)sub_800A5238;
    FreeSound_80030D00((int)&stru_80091D40);
    LoadSound_80030A84(0x1B, &stru_80091CE0);
}

INCLUDE_OVERLAY_ASM(soundtst, sub_800A5238);

INCLUDE_OVERLAY_ASM(soundtst, dword_800A57D4);
