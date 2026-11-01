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
extern void sub_8003BC84(int* a);
// Matched
void sub_8002BF74(void)
{
    int s[8];
    dword_8008B4E8 = 0;
    s[0] = 0x29;
    s[1] = 0x3B;
    s[2] = 0;
    s[3] = 0;
    s[4] = 0;
    s[5] = 0;
    s[6] = 0;
    s[7] = (int)sub_8002BFCC;
    sub_8003BC84(s);
}
// Matched
void sub_8002BFCC(int a0, int a1)
{
    sub_80028E74(&loadedOverlayMaybe_8008D620, 0, &dword_8008D3F4, a1, 1);
    dword_8008B4E8 = 1;
}
// Matched
void FreeActiveOverlay_8002C014(void)
{
    if (loadedOverlayMaybe_8008D620)
    {
        free3_8003FC6C((void*)loadedOverlayMaybe_8008D620);
        loadedOverlayMaybe_8008D620 = 0;
    }
    if (dword_8008D3F4)
    {
        free3_8003FC6C((void*)dword_8008D3F4);
        dword_8008D3F4 = 0;
    }
}
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
// Matched
int sub_8002C670(char* base, int a1, int a2, short idx, short a4)
{
    char* p = base + idx * 4;
    if (p[0xde] & 1)
    {
        unsigned char b = p[0xdf];
        if (b)
        {
            sub_8002AF10(a2 + b * 16, a1, a4);
            return 1;
        }
        return 0;
    }
    return 0;
}
INCLUDE_ASM(sub_8002C6DC);
INCLUDE_ASM(sub_8002C728);
INCLUDE_ASM(sub_8002CAC8);
