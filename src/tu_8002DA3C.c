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


extern unsigned char dword_80082EBC[];
extern unsigned char a1ftf[];
extern void sub_8002C06C(void* p, int a1, int a2);
void sub_8002E0D8(unsigned short* p, short a1);
// Matched
void sub_8002DA3C(unsigned short* pos, int ot)
{
    unsigned short loc[2];
    loc[0] = pos[0] + 3;
    loc[1] = pos[1] + 4;
    sub_8002C06C(loc, 0x11, ot);
    loc[0] = pos[0] + 4;
    loc[1] = pos[1] + 0x11;
    sub_8002C06C(loc, 0x5C, ot);
    loc[0] = pos[0] + 4;
    loc[1] = pos[1] + 0x1E;
    sub_8002C06C(loc, 0x3C, ot);
    loc[0] = pos[0] + 1;
    loc[1] = pos[1] + 0x37;
    sub_8002C06C(loc, 0x54, ot);
    loc[1] = pos[1] + 0x56;
    sub_8002C06C(loc, 0x72, ot);
    loc[0] = pos[0] + 0x4E;
    loc[1] = pos[1];
    sub_8002E0D8(loc, ot);
}
INCLUDE_ASM(sub_8002DB48);
extern void sub_80031FF4(int a, void* b, void* c, int d);
extern void sub_8002C290(void* p, int a1, int a2);
// Matched
void sub_8002E004(unsigned short* p, int a1, int a2)
{
    unsigned short pos[2];
    unsigned short x = p[0];
    pos[0] = x + 3;
    pos[1] = p[1] + 3;
    if (a1 > 0)
    {
        if (a1 >= 100)
        {
            pos[0] = x - 5;
        }
        sub_80031FF4(0x58, &pOT_8008D454[a2], pos, 0x400);
    }
    else if (a1 < 0)
    {
        a1 = -a1;
        if (a1 >= 100)
        {
            pos[0] = x - 5;
        }
        sub_80031FF4(0x58, &pOT_8008D454[a2], pos, 0xC00);
    }
    pos[0] = p[0] + 0x14;
    pos[1] = p[1];
    sub_8002C290(pos, a1, a2);
}
extern unsigned char dword_80082EBC[];
extern unsigned char a1ftf[];
extern void sub_8002C06C(void* p, int a1, int a2);
// Matched
void sub_8002E0D8(unsigned short* p, short a1)
{
    unsigned short pos[2];
    short i;
    pos[0] = p[0];
    for (i = 0; i < 5; i++)
    {
        pos[1] = p[1] + a1ftf[i];
        sub_8002C06C(pos, dword_80082EBC[i], a1);
    }
}
extern void sub_8002C100(unsigned short* pos, int v, short ot);
// Matched
void sub_8002E188(unsigned char* a, unsigned char* b, unsigned short* pos, short ot)
{
    unsigned short loc[2];
    short i;
    for (i = 0; i < 5; i++)
    {
        if (a[i] < b[i])
        {
            sub_8002C5D0(1);
        }
        else if (b[i] < a[i])
        {
            sub_8002C5D0(2);
        }
        loc[0] = pos[0] + 0x16;
        loc[1] = pos[1] + i * 14 + 2;
        sub_8002C100(loc, b[i], ot);
        sub_8002C5D0(0);
    }
}
// Matched
void sub_8002E288(unsigned int* a0, int a1, int a2, void* a3)
{
    char* p = 0;
    sub_800403E8(0, a0, 0x48);
    switch (a2)
    {
    case 0:
        p[0x1C] = a1;
        break;
    case 1:
        p[0x1D] = a1;
        break;
    case 2:
        p[0x1E] = a1;
        break;
    }
    sub_80033624(a3, p);
}
INCLUDE_ASM(sub_8002E334);
INCLUDE_ASM(sub_8002E730);
INCLUDE_ASM(sub_8002E944);
INCLUDE_ASM(sub_8002EACC);
