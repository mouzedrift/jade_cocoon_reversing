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

INCLUDE_DATA(dword_800741D8);
INCLUDE_DATA(dword_800741DC);
INCLUDE_DATA(dword_800741E0);
INCLUDE_DATA(dword_800741E4);
INCLUDE_DATA(dword_800741E8);

extern int dword_800827D0[];
extern int dword_800827BC[];
extern void sub_8002C06C(void* p, int a1, int a2);
// Matched
void sub_8002B2A4(short a, short* b, int c, short (*d)[2], int e)
{
    short pos[2];
    int i;
    int v;
    for (i = 0; i < 4; i++)
    {
        pos[0] = b[0] + d[i][0];
        pos[1] = b[1] + d[i][1];
        if (a == 0)
        {
            v = dword_800827D0[4];
        }
        else if ((a >> i) & 1)
        {
            v = dword_800827BC[i];
        }
        else if (e == 0)
        {
            v = dword_800827D0[4];
        }
        else
        {
            v = dword_800827D0[i];
        }
        SetShadeTex((SPRT*)loadedOverlayMaybe_8008D620 + v, 1);
        sub_8002C06C(pos, v, c);
    }
}
INCLUDE_ASM(sub_8002B3DC);
typedef struct
{
    unsigned short a;
    unsigned short b;
} UShortPair;
extern void sub_8002B3DC(UShortPair p, int b, int c, int d);
// Matched
void sub_8002B8DC(UShortPair a, short* p, int c, int d)
{
    switch (a.b)
    {
    case 0:
    case 2:
        if (p[5] > 0)
        {
            a.b = 0;
            sub_8002B3DC(a, GetTime30Hz_8002C64C(), c, d);
        }
        if (p[0] * p[1] + p[5] < (unsigned short)p[2])
        {
            a.b = 2;
            sub_8002B3DC(a, GetTime30Hz_8002C64C(), c + 4, d);
        }
        break;
    case 1:
    case 3:
        if (p[5] > 0)
        {
            a.b = 3;
            sub_8002B3DC(a, GetTime30Hz_8002C64C(), c, d);
        }
        if (p[0] * p[1] + p[5] < (unsigned short)p[2])
        {
            a.b = 1;
            sub_8002B3DC(a, GetTime30Hz_8002C64C(), c + 4, d);
        }
        break;
    }
}
typedef struct
{
    int state;
    int field_4;
    int field_8;
    int field_C;
} struct_BA54;
unsigned int sub_8002BC60(unsigned int a, unsigned int b, unsigned int c);
void sub_8002BCAC(int idx, int scale, short* pos, unsigned int t, int ot);
// Matched
void sub_8002BA54(struct_BA54* a0, int arg1, short* a2, int a3)
{
    short pos[2];
    int idx;
    int a1;
    int c;
    int e;
    int w;
    int n;
    int t;
    int m;
    idx = 2;
    a1 = arg1;
    c = 0x2F;
    e = 0x69;
    switch ((unsigned int)a0->state)
    {
    case 0:
        if (a0->field_8 < a0->field_C / 4)
        {
            idx = 0x42;
        }
        else
        {
            idx = 2;
            a1 = 0;
        }
        c = 0x57;
        e = 0x6A;
        break;
    case 1:
        if (a0->field_8 < a0->field_C / 4)
        {
            idx = 0x42;
        }
        else
        {
            idx = 2;
            a1 = 0;
        }
        break;
    case 2:
        idx = 0x14;
        break;
    }
    w = sub_8002BC60(a0->field_8, a0->field_C, c);
    t = a0->field_4;
    if (t)
    {
        if (t < 0)
        {
            pos[0] = a2[0] + 8;
            pos[1] = a2[1] + 2;
            m = -t;
        }
        else
        {
            pos[0] = (short)(a2[0] + 8) + w;
            pos[1] = a2[1] + 2;
            m = t;
        }
        if (a0->field_C < a0->field_8 + a0->field_4)
        {
            n = a0->field_C - a0->field_8;
        }
        else
        {
            n = sub_8002BC60(m, a0->field_C, c);
        }
        if (frameCount_8008D3FC & 0x10)
        {
            sub_8002BCAC(0x14, n, pos, a1, a3);
        }
    }
    pos[0] = a2[0] + 8;
    pos[1] = a2[1] + 2;
    sub_8002BCAC(idx, w, pos, a1, a3);
    sub_8002C06C(a2, e, a3);
}
// Not matched: original has no zero-divisor check (plain divu), cc1psx/aspsx emit one
// Matched
unsigned int sub_8002BC60(unsigned int a, unsigned int b, unsigned int c)
{
    if (b < a)
    {
        a = b;
    }
    if (a)
    {
        a = a * c / b;
        if (a == 0)
        {
            return 1;
        }
        return a;
    }
    return 0;
}
extern CVECTOR dword_800741E8;
extern int dword_8008D430;
extern void sub_80033394(unsigned char* out, unsigned char* c0, unsigned char* c1, unsigned int t, int period, int half);
extern void sub_80031BE4(void* p, unsigned long* ot, int x, int y, int scale, int a5, int a6, int a7);
// Matched
void sub_8002BCAC(int idx, int scale, short* pos, unsigned int t, int ot)
{
    POLY_FT4 poly;
    CVECTOR c0;
    CVECTOR c1;
    if (scale)
    {
        c0 = dword_800741E8;
        c1 = dword_800741E8;
        setPolyFT4(&poly);
        poly.code = ((POLY_FT4*)dword_8008D430)[idx].code;
        poly.clut = ((POLY_FT4*)dword_8008D430)[idx].clut;
        poly.tpage = ((POLY_FT4*)dword_8008D430)[idx].tpage;
        poly.u0 = ((POLY_FT4*)dword_8008D430)[idx].u0;
        poly.v0 = ((POLY_FT4*)dword_8008D430)[idx].v0;
        poly.u1 = ((POLY_FT4*)dword_8008D430)[idx].u1;
        poly.v1 = ((POLY_FT4*)dword_8008D430)[idx].v1;
        poly.u2 = ((POLY_FT4*)dword_8008D430)[idx].u2;
        poly.v2 = ((POLY_FT4*)dword_8008D430)[idx].v2;
        poly.u3 = ((POLY_FT4*)dword_8008D430)[idx].u3;
        poly.v3 = ((POLY_FT4*)dword_8008D430)[idx].v3;
        setShadeTex(&poly, 0);
        scale *= 512;
        sub_80033394(&poly.r0, (unsigned char*)&c0, (unsigned char*)&c1, t, 40, 10);
        sub_80031BE4(&poly, pOT_8008D454 + ot, pos[0], pos[1], scale, 0x100, 0, 0x11);
    }
}
