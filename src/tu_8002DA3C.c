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

INCLUDE_DATA(dword_800743D0);

INCLUDE_ASM(sub_8002DA3C);
INCLUDE_ASM(sub_8002DB48);
extern void sub_80031FF4(int a0, unsigned long* ot, unsigned short* pos, int a3);
extern void sub_8002C290(unsigned short* pos, int val, int ot);
// Matched
void sub_8002E004(unsigned short* pos, int val, int ot)
{
    unsigned short loc[2];
    unsigned short x = pos[0];
    loc[0] = x + 3;
    loc[1] = pos[1] + 3;
    if (val > 0)
    {
        if (val >= 100)
        {
            loc[0] = x - 5;
        }
        sub_80031FF4(0x58, &pOT_8008D454[ot], loc, 0x400);
    }
    else if (val < 0)
    {
        val = -val;
        if (val >= 100)
        {
            loc[0] = x - 5;
        }
        sub_80031FF4(0x58, &pOT_8008D454[ot], loc, 0xC00);
    }
    loc[0] = pos[0] + 0x14;
    loc[1] = pos[1];
    sub_8002C290(loc, val, ot);
}
extern unsigned char dword_80082EBC[];
extern unsigned char a1ftf[];
extern void sub_8002C06C(void* p, int a1, short a2);
// Matched
void sub_8002E0D8(short* pos, short ot)
{
    short loc[2];
    short i;
    loc[0] = pos[0];
    for (i = 0; i < 5; i++)
    {
        loc[1] = pos[1] + a1ftf[i];
        sub_8002C06C(loc, dword_80082EBC[i], ot);
    }
}
INCLUDE_ASM(sub_8002E188);
// Matched
void sub_8002E288(void* src, int v, int which, void* dst)
{
    char* m = 0;
    sub_800403E8((unsigned int*)m, (unsigned int*)src, 0x48);
    switch (which)
    {
    case 0:
        m[0x1C] = v;
        break;
    case 1:
        m[0x1D] = v;
        break;
    case 2:
        m[0x1E] = v;
        break;
    }
    sub_80033624(dst, (int)m);
}
INCLUDE_ASM(sub_8002E334);
INCLUDE_ASM(sub_8002E730);
INCLUDE_ASM(sub_8002E944);
INCLUDE_ASM(sub_8002EACC);
