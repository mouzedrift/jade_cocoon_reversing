#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "STDLIB.H"
#include "STDIO.H"
#include "LIBPAD.H"
#include "LIBSND.H"
#include "LIBMCX.H"
#include "LIBPRESS.H"
#include "LIBETC.H"
#include "LIBMCRD.H"
#include "sound.h"
#include "data_decls.h"

INCLUDE_DATA(dword_800741EC);

INCLUDE_ASM(sub_8002BE10);
INCLUDE_ASM(sub_8002BEC8);
INCLUDE_ASM(sub_8002BF74);
// Matched
void sub_8002BFCC(int a0, int a1)
{
    sub_80028E74(&loadedOverlayMaybe_8008D620, 0, &dword_8008D3F4, a1, 1);
    dword_8008B4E8 = 1;
}
INCLUDE_ASM(FreeActiveOverlay_8002C014);
INCLUDE_ASM(sub_8002C06C);
INCLUDE_ASM(sub_8002C100);
INCLUDE_ASM(sub_8002C290);
INCLUDE_ASM(sub_8002C414);
#if 0
void sub_8002C5D0(int a0)
{
}
#endif
INCLUDE_ASM(sub_8002C5D0);
// Matched
unsigned int sub_8002C64C(void)
{
    return (unsigned int)(frameCount_8008D3FC * stru_8008B4D8.field_4) >> 1;
}
INCLUDE_ASM(sub_8002C670);
INCLUDE_ASM(sub_8002C6DC);
INCLUDE_ASM(sub_8002C728);
INCLUDE_ASM(sub_8002CAC8);
