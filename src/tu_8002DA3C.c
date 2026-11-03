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
#include "unit.h"
#include "tu_8002DA3C.h"

INCLUDE_DATA(dword_800743D0);


extern unsigned char dword_80082EBC[];
extern unsigned char a1ftf[];
extern void DrawUiTiySprt_8002C06C(void* p, int a1, int a2);
void sub_8002E0D8(unsigned short* p, short a1);
// Matched
void sub_8002DA3C(unsigned short* pos, int ot)
{
    unsigned short loc[2];
    loc[0] = pos[0] + 3;
    loc[1] = pos[1] + 4;
    DrawUiTiySprt_8002C06C(loc, 0x11, ot);
    loc[0] = pos[0] + 4;
    loc[1] = pos[1] + 0x11;
    DrawUiTiySprt_8002C06C(loc, 0x5C, ot);
    loc[0] = pos[0] + 4;
    loc[1] = pos[1] + 0x1E;
    DrawUiTiySprt_8002C06C(loc, 0x3C, ot);
    loc[0] = pos[0] + 1;
    loc[1] = pos[1] + 0x37;
    DrawUiTiySprt_8002C06C(loc, 0x54, ot);
    loc[1] = pos[1] + 0x56;
    DrawUiTiySprt_8002C06C(loc, 0x72, ot);
    loc[0] = pos[0] + 0x4E;
    loc[1] = pos[1];
    sub_8002E0D8(loc, ot);
}
extern void AddClipDrawAreaPrim_80033308(unsigned long* ot);
extern void DrawLargeText_8002FBD8(int a0, unsigned short* pos, unsigned char* name, int a3);
extern void sub_8002E004(unsigned short* p, int a1, int a2);
extern void DrawLargeNumber_8002C100(unsigned short* pos, int v, int ot);
extern void sub_8002EFC4(char* a0, int a1, int a2, void* a3_, int a4, int a5);
extern void DrawGauge_8002BA54(void* a, int b, void* c, int d);
extern void sub_80033864(Minion* m, unsigned char* out);
extern void sub_8002E730(unsigned short* pos, unsigned char* a1, short ot);
extern void sub_8002EACC(UnitStats* a0, unsigned short* pos, int a2, short ot);
// Matched
void sub_8002DB48(UnitStats* m, int ot, int unused, unsigned short* pos, Minion* mn, UnitStats* cmp)
{
    short i;
    short j;
    unsigned char buf[8];
    unsigned short loc[2];
    unsigned short loc2[2];
    unsigned int w[4];
    unsigned char st[0x18];
    unsigned char st2[0x18];
    unsigned short loc3[2];
    unsigned short loc4[2];
    int d;
    unsigned short x;
    unsigned short y;
    unsigned int u;

    AddClipDrawAreaPrim_80033308(&pOT_8008D454[ot]);
    sub_8002DA3C(pos, ot);
    x = pos[0];
    loc[0] = x + 0x1E;
    y = pos[1];
    loc[1] = y + 3;
    loc[0] = x + 0x26;
    loc[1] = y + 5;
    DrawLargeText_8002FBD8(0, loc, m->name_10, ot);
    loc[0] = pos[0] + 0x42;
    loc[1] = pos[1] + 0x11;
    d = 0;
    if (cmp)
    {
        d = cmp->level_44 - m->level_44;
        if (d)
        {
            loc2[0] = pos[0] + 0x43;
            loc2[1] = pos[1] + 0x14;
            sub_8002E004(loc2, d, ot);
        }
    }
    if (d < 0)
    {
        SetLargeDigitColor_8002C5D0(1);
    }
    else if (d > 0)
    {
        SetLargeDigitColor_8002C5D0(2);
    }
    else
    {
        SetLargeDigitColor_8002C5D0(0);
    }
    loc[1] += 1;
    DrawLargeNumber_8002C100(loc, m->level_44, ot);
    if (d)
    {
        SetLargeDigitColor_8002C5D0(0);
    }
    if (cmp)
    {
        d = *(short*)&cmp->maxHp_A - *(short*)&m->maxHp_A;
        if (d)
        {
            loc2[0] = pos[0] + 0x2F;
            loc2[1] = pos[1] + 0x3A;
            sub_8002E004(loc2, d, ot);
        }
    }
    loc[0] = pos[0] + 3;
    loc[1] = pos[1] + 0x45;
    sub_8002EFC4((char*)&m->hp_8, 0, 0, loc, ot, 1);
    if (cmp)
    {
        d = *(short*)&cmp->maxMp_E - *(short*)&m->maxMp_E;
        if (d)
        {
            loc2[0] = pos[0] + 0x2F;
            loc2[1] = pos[1] + 0x59;
            sub_8002E004(loc2, d, ot);
        }
    }
    loc[0] = pos[0] + 3;
    loc[1] = pos[1] + 0x63;
    sub_8002EFC4((char*)&m->mp_C, 0, 0, loc, ot, 1);
    w[0] = 2;
    w[1] = 0;
    u = m->exp_4;
    while (u > 0x4000000)
    {
        u -= 0x4000000;
    }
    w[2] = u;
    w[3] = 0x4000000;
    loc[0] = pos[0] + 3;
    loc[1] = pos[1] + 0x2B;
    DrawGauge_8002BA54(w, 0, loc, ot);
    sub_80033864(mn, buf);
    loc[0] = pos[0] + 0xA2;
    loc[1] = pos[1] + 4;
    sub_8002E730(loc, buf, ot);
    loc[0] = pos[0] + 0xA2;
    loc[1] = pos[1] + 0x3D;
    sub_8002EACC(m, loc, (int)mn->field_CC, ot);
    CalcEquippedStats_80033624(st, (int)m);
    if (cmp)
    {
        CalcEquippedStats_80033624(st2, (int)cmp);
        for (i = 0; i < 5; i++)
        {
            d = st2[i] - st[i];
            if (d < 0)
            {
                SetLargeDigitColor_8002C5D0(1);
            }
            else if (d > 0)
            {
                SetLargeDigitColor_8002C5D0(2);
            }
            else
            {
                SetLargeDigitColor_8002C5D0(0);
            }
            loc3[0] = pos[0] + 0x8C;
            loc3[1] = pos[1] + a1ftf[i] + 1;
            DrawLargeNumber_8002C100(loc3, st[i], ot);
            if (d)
            {
                SetLargeDigitColor_8002C5D0(0);
                loc3[0] = pos[0] + 0x8C;
                loc3[1] = pos[1] + a1ftf[i] + 3;
                sub_8002E004(loc3, d, ot);
            }
        }
    }
    else
    {
        loc4[0] = pos[0] + 0x8C;
        for (j = 0; j < 5; j++)
        {
            loc4[1] = pos[1] + a1ftf[j] + 1;
            DrawLargeNumber_8002C100(loc4, st[j], ot);
        }
    }
}
extern void sub_80031FF4(int a, void* b, void* c, int d);
extern void DrawSmallNumber3_8002C290(void* p, int a1, int a2);
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
    DrawSmallNumber3_8002C290(pos, a1, a2);
}
extern unsigned char dword_80082EBC[];
extern unsigned char a1ftf[];
extern void DrawUiTiySprt_8002C06C(void* p, int a1, int a2);
// Matched
void sub_8002E0D8(unsigned short* p, short a1)
{
    unsigned short pos[2];
    short i;
    pos[0] = p[0];
    for (i = 0; i < 5; i++)
    {
        pos[1] = p[1] + a1ftf[i];
        DrawUiTiySprt_8002C06C(pos, dword_80082EBC[i], a1);
    }
}
extern void DrawLargeNumber_8002C100(unsigned short* pos, int v, int ot);
// Matched
void sub_8002E188(unsigned char* a, unsigned char* b, unsigned short* pos, short ot)
{
    unsigned short loc[2];
    short i;
    for (i = 0; i < 5; i++)
    {
        if (a[i] < b[i])
        {
            SetLargeDigitColor_8002C5D0(1);
        }
        else if (b[i] < a[i])
        {
            SetLargeDigitColor_8002C5D0(2);
        }
        loc[0] = pos[0] + 0x16;
        loc[1] = pos[1] + i * 14 + 2;
        DrawLargeNumber_8002C100(loc, b[i], ot);
        SetLargeDigitColor_8002C5D0(0);
    }
}
// Matched
void sub_8002E288(unsigned int* a0, int a1, int a2, void* a3)
{
    UnitStats* p = 0;
    MemCopy_800403E8(0, a0, 0x48);
    switch (a2)
    {
    case 0:
        p->field_1C[0] = a1;
        break;
    case 1:
        p->field_1C[1] = a1;
        break;
    case 2:
        p->field_1C[2] = a1;
        break;
    }
    CalcEquippedStats_80033624(a3, (int)p);
}
extern void AddClipDrawAreaPrim_80033308(unsigned long* ot);
extern int sub_800AD8E4(void);
extern void DrawAnimatedWindow_8002BEC8(int a0, int a1, short a2, short a3, int a4, int a5);
extern void DrawLargeText_8002FBD8(int a0, unsigned short* pos, unsigned char* name, int a3);
extern void DrawGauge_8002BA54(void* a, int b, void* c, int d);
extern void sub_8002EE28(short* a, unsigned short* pos, short c, int d);
// Matched
void sub_8002E334(UnitStats* a0, MenuDrawArgs* a1)
{
    short r[4];
    unsigned short loc2[2];
    unsigned short base[2];
    unsigned short loc[2];
    int buf[2];
    int v[4];
    int w[4];

    base[0] = 0x4E;
    base[1] = 0x2C;
    AddClipDrawAreaPrim_80033308(&pOT_8008D454[a1->ot_0]);
    loc[0] = 0xE0;
    loc[1] = 0x31;
    DrawUiTiySprt_8002C06C(loc, 0x82, a1->ot_0);
    loc[0] = 0x132;
    loc[1] = 0x32;
    DrawLargeNumber_8002C100(loc, sub_800AD8E4(), a1->ot_0);
    r[0] = 0xDB;
    r[1] = 0x2C;
    r[2] = 0x5B;
    r[3] = 0x17;
    DrawAnimatedWindow_8002BEC8((int)buf, (int)r, a1->field_2, a1->ot_0, a1->field_4, a1->field_8);
    loc[0] = 0xE0;
    loc[1] = 0x48;
    DrawUiTiySprt_8002C06C(loc, 0x52, a1->ot_0);
    loc[0] = 0x132;
    loc[1] = 0x49;
    DrawLargeNumber_8002C100(loc, CountItems_800106B8(), a1->ot_0);
    r[1] = 0x43;
    r[0] = 0xDB;
    r[2] = 0x5B;
    r[3] = 0x16;
    DrawAnimatedWindow_8002BEC8((int)buf, (int)r, a1->field_2, a1->ot_0, a1->field_4, a1->field_8);
    loc[0] = 0xE0;
    loc[1] = 0x5E;
    DrawUiTiySprt_8002C06C(loc, 0x6F, a1->ot_0);
    loc[0] = 0x132;
    loc[1] = 0x5F;
    DrawLargeNumber_8002C100(loc, GetCapturedMinionsCount_800125B8(), a1->ot_0);
    r[0] = 0xDB;
    r[1] = 0x59;
    r[2] = 0x5B;
    r[3] = 0x17;
    DrawAnimatedWindow_8002BEC8((int)buf, (int)r, a1->field_2, a1->ot_0, a1->field_4, a1->field_8);
    AddClipDrawAreaPrim_80033308(&pOT_8008D454[a1->ot_0]);
    loc2[0] = base[0] + 4;
    loc2[1] = base[1] + 5;
    DrawUiTiySprt_8002C06C(loc2, 0x11, a1->ot_0);
    loc2[0] = base[0] + 0x25;
    loc2[1] = base[1] + 6;
    DrawLargeText_8002FBD8(0, loc2, a0->name_10, a1->ot_0);
    loc2[0] = base[0] + 4;
    loc2[1] = base[1] + 0x15;
    DrawUiTiySprt_8002C06C(loc2, 0x12, a1->ot_0);
    v[0] = 0;
    v[1] = 0;
    loc2[0] = base[0] + 0x22;
    loc2[1] = base[1] + 0x14;
    v[2] = *(short*)&a0->hp_8;
    v[3] = *(short*)&a0->maxHp_A;
    DrawGauge_8002BA54(v, 0, loc2, a1->ot_0);
    loc2[0] = base[0] + 0x3C;
    loc2[1] = base[1] + 0x1C;
    sub_8002EE28((short*)&a0->hp_8, loc2, a1->ot_0, 1);
    loc2[0] = base[0] + 4;
    loc2[1] = base[1] + 0x24;
    DrawUiTiySprt_8002C06C(loc2, 0x70, a1->ot_0);
    loc2[0] = base[0] + 0x80;
    loc2[1] = base[1] + 0x25;
    DrawLargeNumber_8002C100(loc2, a0->level_44, a1->ot_0);
    loc2[0] = base[0] + 4;
    loc2[1] = base[1] + 0x34;
    DrawUiTiySprt_8002C06C(loc2, 0xE2, a1->ot_0);
    w[0] = 2;
    w[1] = 0;
    loc2[0] = base[0] + 0x4B;
    loc2[1] = base[1] + 0x36;
    w[2] = a0->exp_4;
    while (w[2] > 0x4000000)
    {
        w[2] -= 0x4000000;
    }
    w[3] = 0x4000000;
    DrawGauge_8002BA54(w, 0, loc2, a1->ot_0);
}
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
        DrawUiTiySprt_8002C06C(q, dword_80082EA4[i], ot);
        n = a1[dword_80082EB8[i]];
        if (n)
        {
            sub_8002E944(&poly, v, n, i);
            AddPrimCopy_80040298(&pOT_8008D454[ot], &poly, 5);
        }
    }
    DrawUiTiySprt_8002C06C(pos, 0xB, ot);
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
extern void DrawRectOutline_80042750(RECT* r, unsigned char* rgb, void* ot);
extern void DrawLine_80042870(DVECTOR* a, DVECTOR* b, unsigned char* rgb, void* ot);
// Matched
void sub_8002EACC(UnitStats* a0, unsigned short* pos, int a2, short ot)
{
    short loc[2];
    DVECTOR a;
    DVECTOR b;
    RECT r;
    Color_EACC col = dword_800743D0;
    SPRT* prim;
    sub_8001419C(a0->stats_2C, loc);
    loc[0] += pos[0];
    loc[1] += pos[1];
    DrawUiTiySprt_8002C06C(loc, 10, ot);
    prim = (SPRT*)uiTiySprts_8008D620;
    prim[12].x0 = pos[0] + 2;
    prim[12].y0 = pos[1] + 2;
    SetSemiTrans(&prim[12], 1);
    AddPrimCopy_80040298(&pOT_8008D454[ot], &((SPRT*)uiTiySprts_8008D620)[12], 5);
    AddPrimCopy_80040298(&pOT_8008D454[ot], &((DR_TPAGE*)uiTiyTPages_8008D3F4)[12], 2);
    r.x = pos[0];
    r.y = pos[1];
    r.w = 0x32;
    r.h = 0x32;
    DrawRectOutline_80042750(&r, dword_80082E9C, &pOT_8008D454[ot]);
    r.x = pos[0] + 1;
    r.y = pos[1] + 1;
    r.w = 0x30;
    r.h = 0x30;
    DrawRectOutline_80042750(&r, dword_80082EA0, &pOT_8008D454[ot]);
    a.vx = pos[0] + 2;
    a.vy = pos[1] + 0x1A;
    b.vx = pos[0] + 0x32;
    b.vy = a.vy;
    DrawLine_80042870(&a, &b, col.c, &pOT_8008D454[ot]);
    a.vx = pos[0] + 0x19;
    a.vy = pos[1] + 2;
    b.vx = a.vx;
    b.vy = pos[1] + 0x32;
    DrawLine_80042870(&a, &b, col.c, &pOT_8008D454[ot]);
}
