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
#include "tiy.h"
#include "effect_data.h"

const CVECTOR colorGrey_800741E4 = { 128, 128, 128 };
const CVECTOR colorWhite_800741E8 = { 255, 255, 255 };

extern int elementIcons_800827BC[];
extern void DrawUiTiySprt_8002C06C(void* p, int a1, int a2);
// Matched
void DrawElementIcons_8002B2A4(short mask, short* base, int ot, short (*offsets)[2], int showUnlit)
{
    short pos[2];
    int i;
    int v;
    for (i = 0; i < 4; i++)
    {
        pos[0] = base[0] + offsets[i][0];
        pos[1] = base[1] + offsets[i][1];
        if (mask == 0)
        {
            v = elementIconsUnlit_800827D0[4];
        }
        else if ((mask >> i) & 1)
        {
            v = elementIcons_800827BC[i];
        }
        else if (showUnlit == 0)
        {
            v = elementIconsUnlit_800827D0[4];
        }
        else
        {
            v = elementIconsUnlit_800827D0[i];
        }
        SetShadeTex(uiTiySprts_8008D620 + v, 1);
        DrawUiTiySprt_8002C06C(pos, v, ot);
    }
}
typedef struct
{
    unsigned short a;
    unsigned short b;
} UShortPair;
extern const CVECTOR colorGrey_800741E4;
extern const CVECTOR colorWhite_800741E8;
extern void PulseColor_80033394(unsigned char* out, unsigned char* c0, unsigned char* c1, unsigned int t, int period, int half);
#if 0
// Not matched: same shape; the original reloads publicTiyPolyFT4s_8008D430 one division earlier in the third vertex (CSE path length) and allocates registers differently
void DrawScrollArrow_8002B3DC(UShortPair p, int t, int pos, int ot)
{
    CVECTOR c0;
    CVECTOR c1;
    short idx;
    int ang;
    int x;
    int y;
    int nx;
    int ny;
    short* c = (short*)pos;
    c0 = colorGrey_800741E4;
    c1 = colorWhite_800741E8;
    idx = scrollArrowIcons_8008279C[(short)saveData_8008B570.uiColor_20.i * 3 + p.a];
    publicTiyPolyFT4s_8008D430[idx].x0 = 1 - publicTiySprts_8008D434[idx].w / 2;
    publicTiyPolyFT4s_8008D430[idx].y0 = 1 - publicTiySprts_8008D434[idx].h / 2;
    publicTiyPolyFT4s_8008D430[idx].x1 = publicTiySprts_8008D434[idx].w / 2;
    publicTiyPolyFT4s_8008D430[idx].y1 = 1 - publicTiySprts_8008D434[idx].h / 2;
    publicTiyPolyFT4s_8008D430[idx].x2 = 1 - publicTiySprts_8008D434[idx].w / 2;
    publicTiyPolyFT4s_8008D430[idx].y2 = publicTiySprts_8008D434[idx].h / 2;
    publicTiyPolyFT4s_8008D430[idx].x3 = publicTiySprts_8008D434[idx].w / 2;
    publicTiyPolyFT4s_8008D430[idx].y3 = publicTiySprts_8008D434[idx].h / 2;
    ang = p.b << 10;
    x = publicTiyPolyFT4s_8008D430[idx].x0;
    y = publicTiyPolyFT4s_8008D430[idx].y0;
    nx = x * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096 - y * sinTable_80084540[ang & 0xFFF] / 4096;
    ny = x * sinTable_80084540[ang & 0xFFF] / 4096 + y * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096;
    publicTiyPolyFT4s_8008D430[idx].x0 = c[0] + nx;
    publicTiyPolyFT4s_8008D430[idx].y0 = c[1] + ny;
    x = publicTiyPolyFT4s_8008D430[idx].x1;
    y = publicTiyPolyFT4s_8008D430[idx].y1;
    nx = x * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096 - y * sinTable_80084540[ang & 0xFFF] / 4096;
    ny = x * sinTable_80084540[ang & 0xFFF] / 4096 + y * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096;
    publicTiyPolyFT4s_8008D430[idx].x1 = c[0] + nx;
    publicTiyPolyFT4s_8008D430[idx].y1 = c[1] + ny;
    x = publicTiyPolyFT4s_8008D430[idx].x2;
    y = publicTiyPolyFT4s_8008D430[idx].y2;
    nx = x * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096 - y * sinTable_80084540[ang & 0xFFF] / 4096;
    ny = x * sinTable_80084540[ang & 0xFFF] / 4096 + y * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096;
    publicTiyPolyFT4s_8008D430[idx].x2 = c[0] + nx;
    publicTiyPolyFT4s_8008D430[idx].y2 = c[1] + ny;
    x = publicTiyPolyFT4s_8008D430[idx].x3;
    y = publicTiyPolyFT4s_8008D430[idx].y3;
    nx = x * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096 - y * sinTable_80084540[ang & 0xFFF] / 4096;
    ny = x * sinTable_80084540[ang & 0xFFF] / 4096 + y * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096;
    publicTiyPolyFT4s_8008D430[idx].x3 = c[0] + nx;
    publicTiyPolyFT4s_8008D430[idx].y3 = c[1] + ny;
    setSemiTrans(&publicTiyPolyFT4s_8008D430[idx], 0);
    PulseColor_80033394((unsigned char*)&publicTiyPolyFT4s_8008D430[idx].r0, (unsigned char*)&c0, (unsigned char*)&c1, t, 0x28, 0xA);
    AddPrimCopy_80040298(&pOT_8008D454[ot], &publicTiyPolyFT4s_8008D430[idx], 10);
    AddPrimCopy_80040298(&pOT_8008D454[ot], &publicTiyTPages_8008D440[idx], 2);
}
#endif
INCLUDE_ASM(DrawScrollArrow_8002B3DC);
extern void DrawScrollArrow_8002B3DC(UShortPair p, int b, int c, int d);
// Matched
void DrawScrollArrows_8002B8DC(UShortPair arrow, short* p, int pos, int ot)
{
    switch (arrow.b)
    {
    case 0:
    case 2:
        if (p[5] > 0)
        {
            arrow.b = 0;
            DrawScrollArrow_8002B3DC(arrow, GetTime30Hz_8002C64C(), pos, ot);
        }
        if (p[0] * p[1] + p[5] < (unsigned short)p[2])
        {
            arrow.b = 2;
            DrawScrollArrow_8002B3DC(arrow, GetTime30Hz_8002C64C(), pos + 4, ot);
        }
        break;
    case 1:
    case 3:
        if (p[5] > 0)
        {
            arrow.b = 3;
            DrawScrollArrow_8002B3DC(arrow, GetTime30Hz_8002C64C(), pos, ot);
        }
        if (p[0] * p[1] + p[5] < (unsigned short)p[2])
        {
            arrow.b = 1;
            DrawScrollArrow_8002B3DC(arrow, GetTime30Hz_8002C64C(), pos + 4, ot);
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
unsigned int ScaleGaugeLength_8002BC60(unsigned int a, unsigned int b, unsigned int c);
void DrawGaugeBar_8002BCAC(int idx, int scale, short* pos, unsigned int t, int ot);
// Matched
void DrawGauge_8002BA54(struct_BA54* a0, int arg1, short* a2, int a3)
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
    w = ScaleGaugeLength_8002BC60(a0->field_8, a0->field_C, c);
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
            n = ScaleGaugeLength_8002BC60(m, a0->field_C, c);
        }
        if (frameCount_8008D3FC & 0x10)
        {
            DrawGaugeBar_8002BCAC(0x14, n, pos, a1, a3);
        }
    }
    pos[0] = a2[0] + 8;
    pos[1] = a2[1] + 2;
    DrawGaugeBar_8002BCAC(idx, w, pos, a1, a3);
    DrawUiTiySprt_8002C06C(a2, e, a3);
}
// Not matched: original has no zero-divisor check (plain divu), cc1psx/aspsx emit one
// Matched
unsigned int ScaleGaugeLength_8002BC60(unsigned int a, unsigned int b, unsigned int c)
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
extern const CVECTOR colorWhite_800741E8;
extern void PulseColor_80033394(unsigned char* out, unsigned char* c0, unsigned char* c1, unsigned int t, int period, int half);
extern void AddScaledPolyFT4_80031BE4(void* p, unsigned long* ot, int x, int y, int scale, int a5, int a6, int a7);
// Matched
void DrawGaugeBar_8002BCAC(int idx, int scale, short* pos, unsigned int t, int ot)
{
    POLY_FT4 poly;
    CVECTOR c0;
    CVECTOR c1;
    if (scale)
    {
        c0 = colorWhite_800741E8;
        c1 = colorWhite_800741E8;
        setPolyFT4(&poly);
        poly.code = publicTiyPolyFT4s_8008D430[idx].code;
        poly.clut = publicTiyPolyFT4s_8008D430[idx].clut;
        poly.tpage = publicTiyPolyFT4s_8008D430[idx].tpage;
        poly.u0 = publicTiyPolyFT4s_8008D430[idx].u0;
        poly.v0 = publicTiyPolyFT4s_8008D430[idx].v0;
        poly.u1 = publicTiyPolyFT4s_8008D430[idx].u1;
        poly.v1 = publicTiyPolyFT4s_8008D430[idx].v1;
        poly.u2 = publicTiyPolyFT4s_8008D430[idx].u2;
        poly.v2 = publicTiyPolyFT4s_8008D430[idx].v2;
        poly.u3 = publicTiyPolyFT4s_8008D430[idx].u3;
        poly.v3 = publicTiyPolyFT4s_8008D430[idx].v3;
        setShadeTex(&poly, 0);
        scale *= 512;
        PulseColor_80033394(&poly.r0, (unsigned char*)&c0, (unsigned char*)&c1, t, 40, 10);
        AddScaledPolyFT4_80031BE4(&poly, pOT_8008D454 + ot, pos[0], pos[1], scale, 0x100, 0, 0x11);
    }
}
