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

INCLUDE_DATA(dword_800741F0);
INCLUDE_DATA(dword_80074260);
INCLUDE_DATA(dword_80074290);
INCLUDE_DATA(dword_80074298);
INCLUDE_DATA(dword_800742C8);
INCLUDE_DATA(dword_800742D0);
INCLUDE_DATA(dword_80074300);
INCLUDE_DATA(dword_80074308);

typedef struct
{
    unsigned short flags;
    short pad_2;
    int f4;
    int f8;
    int fC;
    short x;
    short y;
    char pad_14[8];
} MenuItem_1C;
typedef struct
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    MenuItem_1C** field_10;
    int field_14;
} struct_A5A4;
extern void DrawMenuWindows_8002A5A4(struct_A5A4* p);
extern int sub_80033C98(short* p);
int sub_8002D1A4(int a, short b);
extern int abilityNames_800834E4[];
extern int abilityBonusNames_80083580[];
extern MenuItem_1C* off_80082D98[];
// Matched
void sub_8002CE28(short* a0, unsigned short* a1)
{
    struct_A5A4 s;
    unsigned short pos[2];
    short saved;
    short w;
    short i;
    int v20;
    int v19;
    unsigned char* m;
    MenuItem_1C** e;
    MenuItem_1C** e2;
    int y;
    saved = a0[0];
    w = 8;
    if (a1)
    {
        pos[0] = a1[0];
        pos[1] = a1[1];
    }
    else
    {
        pos[0] = 0x38;
        pos[1] = 0x2C;
    }
    for (i = 0; i < 5; i++)
    {
        v20 = abilityNames_800834E4[0];
        v19 = abilityBonusNames_80083580[0];
        m = *(unsigned char**)(a0 + 6) + i * 4;
        if (m[0xDE] & 1)
        {
            if (m[0xDF])
            {
                v20 = abilityNames_800834E4[m[0xDF]];
            }
            if (m[0xE0])
            {
                v19 = abilityBonusNames_80083580[m[0xE0]];
            }
            e = &off_80082D98[i];
            (*e)[0].flags &= ~2;
            (*e)[1].flags &= ~2;
            (*e)[2].flags &= ~2;
            a0[0] = i;
            if ((short)sub_80033C98(a0))
            {
                (*e)[0].flags |= 2;
                (*e)[1].flags |= 2;
                (*e)[2].flags |= 2;
            }
            else
            {
                (*e)[0].flags &= ~2;
                (*e)[1].flags &= ~2;
                (*e)[2].flags &= ~2;
            }
        }
        else
        {
            off_80082D98[i][0].flags |= 2;
            off_80082D98[i][1].flags |= 2;
            off_80082D98[i][2].flags |= 2;
        }
        y = sub_8002D1A4(((unsigned char*)sub_800318C8((*(unsigned char**)(a0 + 6) + (i << 2))[0xDF]))[8], i);
        e2 = &off_80082D98[i];
        (*e2)[0].f4 = y;
        (*e2)[1].f4 = v20;
        (*e2)[2].f4 = v19;
        (*e2)[0].f8 = (int)&uiTiySprts_8008D620;
        (*e2)[0].fC = (int)&uiTiyTPages_8008D3F4;
        (*e2)[0].x = pos[0];
        y = i * 22;
        (*e2)[0].y = pos[1] + y;
        (*e2)[1].x = pos[0] + 0x26;
        (*e2)[1].y = pos[1] + y;
        (*e2)[2].x = pos[0] + 0x83;
        (*e2)[2].y = pos[1] + y;
    }
    s.field_0 = a0[2];
    s.field_4 = frameCount_8008D3FC;
    s.field_8 = w;
    s.field_C = saved;
    s.field_10 = off_80082D98;
    s.field_14 = a0[3];
    DrawMenuWindows_8002A5A4(&s);
    sub_8003F900(2, 0);
}
extern unsigned char dword_800827F0[];
extern unsigned char* off_8008280C[];
// Matched
int sub_8002D1A4(int a, short b)
{
    int r = 0;
    switch ((short)a)
    {
    case 0:
        break;
    default:
        r = 4;
        break;
    case 3:
        r = 1;
        break;
    case 1:
        r = 2;
        break;
    case 2:
        r = 3;
        break;
    }
    a = r;
    if (a >= 4)
    {
        return dword_800827F0[b];
    }
    return off_8008280C[b][a];
}
INCLUDE_ASM(sub_8002D250);
