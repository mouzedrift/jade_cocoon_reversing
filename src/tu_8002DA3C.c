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
    MemCopy_800403E8(0, a0, 0x48);
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
    CalcEquippedStats_80033624(a3, p);
}
INCLUDE_ASM(sub_8002E334);
extern unsigned char dword_80082EA4[];
extern unsigned char dword_80082EA8[][4];
extern unsigned char dword_80082EB8[];
void sub_8002E944(POLY_F3* p, unsigned short* pos, short idx, short dir);
// Matched
void sub_8002E730(unsigned short* pos, unsigned char* a1, short ot)
{
    unsigned short p1[2];
    unsigned short p2[2];
    unsigned short v[2];
    POLY_F3 poly;
    unsigned short q[2];
    short i;
    short fy;
    short fx;
    int n;
    unsigned short x;
    for (i = 0; i < 4; i++)
    {
        x = pos[0];
        p2[0] = x + 2;
        fx = (unsigned short)(i - 1) < 2;
        p1[0] = x;
        if (fx)
        {
            p1[0] = x + 0x1A;
            p2[0] = x + 0x24;
        }
        x = pos[1];
        p1[1] = x;
        p2[1] = x + 2;
        fy = (unsigned short)(i - 2) < 2;
        if (fy)
        {
            p1[1] = x + 0x1A;
            p2[1] = x + 0x24;
        }
        SetPolyF3(&poly);
        poly.r0 = dword_80082EA8[i][0];
        poly.g0 = dword_80082EA8[i][1];
        poly.b0 = dword_80082EA8[i][2];
        v[0] = p1[0];
        v[1] = p1[1];
        q[0] = pos[0] + 2;
        q[1] = pos[1] + 2;
        if (fx)
        {
            q[0] = pos[0] + 0x25;
        }
        if (fy)
        {
            q[1] = pos[1] + 0x25;
        }
        sub_8002C06C(q, dword_80082EA4[i], ot);
        n = a1[dword_80082EB8[i]];
        if (n)
        {
            sub_8002E944(&poly, v, n, i);
            AddPrimCopy_80040298(&pOT_8008D454[ot], &poly, 5);
        }
    }
    sub_8002C06C(pos, 0xB, ot);
}
extern unsigned char dword_80082EF0[];
// Matched
void sub_8002E944(POLY_F3* p, unsigned short* pos, short idx, short dir)
{
    int n = dword_80082EF0[idx];
    int w = 26;
    switch (dir)
    {
    case 0:
        p->x0 = pos[0] + w;
        p->y0 = pos[1] + w;
        p->x1 = p->x0;
        p->y1 = pos[1] - (n - w) - 1;
        p->x2 = pos[0] - (n - w) - 1;
        p->y2 = p->y0;
        break;
    case 1:
        p->x0 = pos[0];
        p->y0 = pos[1] + w;
        p->x1 = p->x0;
        p->y1 = pos[1] - (n - w) - 1;
        p->x2 = pos[0] + n;
        p->y2 = p->y0;
        break;
    case 2:
        p->x0 = pos[0];
        p->y0 = pos[1];
        p->x1 = p->x0;
        p->y1 = pos[1] + n;
        p->x2 = pos[0] + n;
        p->y2 = p->y0;
        break;
    case 3:
        p->x0 = pos[0] + w;
        p->y0 = pos[1];
        p->x1 = p->x0;
        p->y1 = pos[1] + n;
        p->x2 = pos[0] - (n - w);
        p->y2 = p->y0;
        break;
    }
}
typedef struct
{
    unsigned char c[4];
} Color_EACC;
extern Color_EACC dword_800743D0;
extern unsigned char dword_80082E9C[];
extern unsigned char dword_80082EA0[];
extern void sub_8001419C(unsigned char* p, short* out);
extern void sub_80042750(RECT* r, unsigned char* rgb, void* ot);
extern void sub_80042870(DVECTOR* a, DVECTOR* b, unsigned char* rgb, void* ot);
// Matched
void sub_8002EACC(unsigned char* a0, unsigned short* pos, int a2, short ot)
{
    short loc[2];
    DVECTOR a;
    DVECTOR b;
    RECT r;
    Color_EACC col = dword_800743D0;
    char* prim;
    sub_8001419C(a0 + 0x2C, loc);
    loc[0] += pos[0];
    loc[1] += pos[1];
    sub_8002C06C(loc, 10, ot);
    prim = (char*)loadedOverlayMaybe_8008D620;
    *(unsigned short*)(prim + 0xF8) = pos[0] + 2;
    *(unsigned short*)(prim + 0xFA) = pos[1] + 2;
    SetSemiTrans(prim + 0xF0, 1);
    AddPrimCopy_80040298(&pOT_8008D454[ot], (char*)loadedOverlayMaybe_8008D620 + 0xF0, 5);
    AddPrimCopy_80040298(&pOT_8008D454[ot], (char*)dword_8008D3F4 + 0x60, 2);
    r.x = pos[0];
    r.y = pos[1];
    r.w = 0x32;
    r.h = 0x32;
    sub_80042750(&r, dword_80082E9C, &pOT_8008D454[ot]);
    r.x = pos[0] + 1;
    r.y = pos[1] + 1;
    r.w = 0x30;
    r.h = 0x30;
    sub_80042750(&r, dword_80082EA0, &pOT_8008D454[ot]);
    a.vx = pos[0] + 2;
    a.vy = pos[1] + 0x1A;
    b.vx = pos[0] + 0x32;
    b.vy = a.vy;
    sub_80042870(&a, &b, col.c, &pOT_8008D454[ot]);
    a.vx = pos[0] + 0x19;
    a.vy = pos[1] + 2;
    b.vx = a.vx;
    b.vy = pos[1] + 0x32;
    sub_80042870(&a, &b, col.c, &pOT_8008D454[ot]);
}
