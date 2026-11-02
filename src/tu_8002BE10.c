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

void sub_8002C06C(unsigned short* pos, int idx, int ot);
// Matched
void sub_8002BE10(void)
{
    short i;
    short j;
    unsigned short loc[2];
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 3; j++)
        {
            loc[0] = j * 128;
            if (i & 1)
            {
                loc[0] -= 0x40;
            }
            loc[1] = i * 60;
            sub_8002C06C(loc, 0x95, 0xF);
        }
    }
}
typedef struct
{
    int field_0;
    int field_4;
    short field_8;
    short field_A;
} struct_BEC8;
extern void sub_8004196C(int a0, int a1, int a2, int a3, int a4);
extern void sub_8003326C(int a, unsigned long* b);
extern void sub_80033308(unsigned long* p);
extern void sub_8002A384(struct_BEC8* p);
// Matched
void sub_8002BEC8(int a0, int a1, short a2, short a3, int a4, int a5)
{
    struct_BEC8 s;
    sub_8004196C(a0, a1, a2, 8, 0);
    sub_8003326C(a0, &pOT_8008D454[a3]);
    if (a4)
    {
        s.field_8 = 1;
    }
    else
    {
        s.field_8 = 0;
    }
    s.field_0 = a0;
    s.field_A = a3;
    s.field_4 = a5;
    sub_8002A384(&s);
    sub_80033308(&pOT_8008D454[a3]);
}
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
typedef struct
{
    int field_0;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    char pad_7;
    unsigned short x;
    unsigned short y;
    char pad_C[8];
} OverlayColorEntry;
// Matched
void sub_8002C06C(unsigned short* pos, int idx, int ot)
{
    ((OverlayColorEntry*)loadedOverlayMaybe_8008D620)[idx].x = pos[0];
    ((OverlayColorEntry*)loadedOverlayMaybe_8008D620)[idx].y = pos[1];
    sub_80040298(&pOT_8008D454[ot], &((OverlayColorEntry*)loadedOverlayMaybe_8008D620)[idx], 5);
    sub_80040298(&pOT_8008D454[ot], (char*)dword_8008D3F4 + idx * 8, 2);
}
INCLUDE_ASM(sub_8002C100);
INCLUDE_ASM(sub_8002C290);
INCLUDE_ASM(sub_8002C414);
extern unsigned char dword_800826F8[][4];
// Matched
void sub_8002C5D0(int a0)
{
    short i = 0x84;
    do
    {
        ((OverlayColorEntry*)loadedOverlayMaybe_8008D620)[i].r = dword_800826F8[a0][0];
        ((OverlayColorEntry*)loadedOverlayMaybe_8008D620)[i].g = dword_800826F8[a0][1];
        ((OverlayColorEntry*)loadedOverlayMaybe_8008D620)[i].b = dword_800826F8[a0][2];
        i++;
    } while (i < 0x8e);
}
// Matched
unsigned int sub_8002C64C(void)
{
    return (unsigned int)(frameCount_8008D3FC * stru_8008B4D8.field_4) >> 1;
}
#if 0
// Not matched (b ends up in a0 instead of v0)
int sub_8002C670(char* base, int a1, int a2, short idx, short a4)
{
    char* p = base + idx * 4;
    int b;
    if (!(p[0xde] & 1))
    {
        return 0;
    }
    b = (unsigned char)p[0xdf];
    if (!b)
    {
        return 0;
    }
    sub_8002AF10(a2 + b * 16, a1, a4);
    return 1;
}
#endif
INCLUDE_ASM(sub_8002C670);
typedef struct
{
    short a;
    short b;
} ShortPair2;
extern void sub_8002B3DC(ShortPair2 p, int b, int c, int d);
// Matched
void sub_8002C6DC(int a0, short a1, short a2)
{
    ShortPair2 p;
    p.a = 2;
    p.b = a1;
    sub_8002B3DC(p, frameCount_8008D3FC, a0, a2);
}
INCLUDE_ASM(sub_8002C728);
INCLUDE_ASM(sub_8002CAC8);
