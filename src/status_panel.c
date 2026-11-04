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
#include "status_panel.h"
#include "effect_data.h"

const Color_EACC statGridLineColor_800743D0 = { "```" };


extern void DrawUiTiySprt_8002C06C(void* p, int a1, int a2);
void DrawStatIcons_8002E0D8(unsigned short* p, short a1);
// Matched
void DrawStatusPanelLabels_8002DA3C(unsigned short* pos, int ot)
{
    unsigned short p[2];
    p[0] = pos[0] + 3;
    p[1] = pos[1] + 4;
    DrawUiTiySprt_8002C06C(p, 0x11, ot);
    p[0] = pos[0] + 4;
    p[1] = pos[1] + 0x11;
    DrawUiTiySprt_8002C06C(p, 0x5C, ot);
    p[0] = pos[0] + 4;
    p[1] = pos[1] + 0x1E;
    DrawUiTiySprt_8002C06C(p, 0x3C, ot);
    p[0] = pos[0] + 1;
    p[1] = pos[1] + 0x37;
    DrawUiTiySprt_8002C06C(p, 0x54, ot);
    p[1] = pos[1] + 0x56;
    DrawUiTiySprt_8002C06C(p, 0x72, ot);
    p[0] = pos[0] + 0x4E;
    p[1] = pos[1];
    DrawStatIcons_8002E0D8(p, ot);
}
extern void AddClipDrawAreaPrim_80033308(unsigned long* ot);
extern void DrawLargeText_8002FBD8(int a0, unsigned short* pos, unsigned char* name, int a3);
extern void DrawStatDelta_8002E004(unsigned short* p, int a1, int a2);
extern void DrawLargeNumber_8002C100(unsigned short* pos, int v, int ot);
extern void DrawValueGauge_8002EFC4(char* a0, int a1, int a2, void* a3_, int a4, int a5);
extern void DrawGauge_8002BA54(void* a, int b, void* c, int d);
extern void GetElementLevels_80033864(Minion* m, unsigned char* out);
extern void DrawElementChart_8002E730(unsigned short* pos, unsigned char* a1, short ot);
extern void DrawStatGrid_8002EACC(UnitStatus* a0, unsigned short* pos, int a2, short ot);
// Matched
void DrawUnitStatusPanel_8002DB48(UnitStatus* unit, int ot, int unused, unsigned short* pos, Minion* minion, UnitStatus* cmp)
{
    short i;
    short j;
    unsigned char elements[8];
    unsigned short loc[2];
    unsigned short loc2[2];
    unsigned int expGauge[4];
    unsigned char stats[0x18];
    unsigned char cmpStats[0x18];
    unsigned short loc3[2];
    unsigned short loc4[2];
    int delta;
    unsigned short x;
    unsigned short y;
    unsigned int u;

    AddClipDrawAreaPrim_80033308(&pOT_8008D454[ot]);
    DrawStatusPanelLabels_8002DA3C(pos, ot);
    x = pos[0];
    loc[0] = x + 0x1E;
    y = pos[1];
    loc[1] = y + 3;
    loc[0] = x + 0x26;
    loc[1] = y + 5;
    DrawLargeText_8002FBD8(0, loc, unit->name_10, ot);
    loc[0] = pos[0] + 0x42;
    loc[1] = pos[1] + 0x11;
    delta = 0;
    if (cmp)
    {
        delta = cmp->level_44 - unit->level_44;
        if (delta)
        {
            loc2[0] = pos[0] + 0x43;
            loc2[1] = pos[1] + 0x14;
            DrawStatDelta_8002E004(loc2, delta, ot);
        }
    }
    if (delta < 0)
    {
        SetLargeDigitColor_8002C5D0(1);
    }
    else if (delta > 0)
    {
        SetLargeDigitColor_8002C5D0(2);
    }
    else
    {
        SetLargeDigitColor_8002C5D0(0);
    }
    loc[1] += 1;
    DrawLargeNumber_8002C100(loc, unit->level_44, ot);
    if (delta)
    {
        SetLargeDigitColor_8002C5D0(0);
    }
    if (cmp)
    {
        delta = cmp->maxHp_A - unit->maxHp_A;
        if (delta)
        {
            loc2[0] = pos[0] + 0x2F;
            loc2[1] = pos[1] + 0x3A;
            DrawStatDelta_8002E004(loc2, delta, ot);
        }
    }
    loc[0] = pos[0] + 3;
    loc[1] = pos[1] + 0x45;
    DrawValueGauge_8002EFC4((char*)&unit->hp_8, 0, 0, loc, ot, 1);
    if (cmp)
    {
        delta = cmp->maxMp_E - unit->maxMp_E;
        if (delta)
        {
            loc2[0] = pos[0] + 0x2F;
            loc2[1] = pos[1] + 0x59;
            DrawStatDelta_8002E004(loc2, delta, ot);
        }
    }
    loc[0] = pos[0] + 3;
    loc[1] = pos[1] + 0x63;
    DrawValueGauge_8002EFC4((char*)&unit->mp_C, 0, 0, loc, ot, 1);
    expGauge[0] = 2;
    expGauge[1] = 0;
    u = unit->exp_4;
    while (u > 0x4000000)
    {
        u -= 0x4000000;
    }
    expGauge[2] = u;
    expGauge[3] = 0x4000000;
    loc[0] = pos[0] + 3;
    loc[1] = pos[1] + 0x2B;
    DrawGauge_8002BA54(expGauge, 0, loc, ot);
    GetElementLevels_80033864(minion, elements);
    loc[0] = pos[0] + 0xA2;
    loc[1] = pos[1] + 4;
    DrawElementChart_8002E730(loc, elements, ot);
    loc[0] = pos[0] + 0xA2;
    loc[1] = pos[1] + 0x3D;
    DrawStatGrid_8002EACC(unit, loc, (int)minion->field_CC, ot);
    CalcEquippedStats_80033624(stats, unit);
    if (cmp)
    {
        CalcEquippedStats_80033624(cmpStats, cmp);
        for (i = 0; i < 5; i++)
        {
            delta = cmpStats[i] - stats[i];
            if (delta < 0)
            {
                SetLargeDigitColor_8002C5D0(1);
            }
            else if (delta > 0)
            {
                SetLargeDigitColor_8002C5D0(2);
            }
            else
            {
                SetLargeDigitColor_8002C5D0(0);
            }
            loc3[0] = pos[0] + 0x8C;
            loc3[1] = pos[1] + statRowY_80082EE8[i] + 1;
            DrawLargeNumber_8002C100(loc3, stats[i], ot);
            if (delta)
            {
                SetLargeDigitColor_8002C5D0(0);
                loc3[0] = pos[0] + 0x8C;
                loc3[1] = pos[1] + statRowY_80082EE8[i] + 3;
                DrawStatDelta_8002E004(loc3, delta, ot);
            }
        }
    }
    else
    {
        loc4[0] = pos[0] + 0x8C;
        for (j = 0; j < 5; j++)
        {
            loc4[1] = pos[1] + statRowY_80082EE8[j] + 1;
            DrawLargeNumber_8002C100(loc4, stats[j], ot);
        }
    }
}
extern void DrawRotatedPublicSprite_80031FF4(int a, void* b, void* c, int d);
extern void DrawSmallNumber3_8002C290(void* p, int a1, int a2);
// Matched
void DrawStatDelta_8002E004(unsigned short* p, int delta, int ot)
{
    unsigned short pos[2];
    unsigned short x = p[0];
    pos[0] = x + 3;
    pos[1] = p[1] + 3;
    if (delta > 0)
    {
        if (delta >= 100)
        {
            pos[0] = x - 5;
        }
        DrawRotatedPublicSprite_80031FF4(0x58, &pOT_8008D454[ot], pos, 0x400);
    }
    else if (delta < 0)
    {
        delta = -delta;
        if (delta >= 100)
        {
            pos[0] = x - 5;
        }
        DrawRotatedPublicSprite_80031FF4(0x58, &pOT_8008D454[ot], pos, 0xC00);
    }
    pos[0] = p[0] + 0x14;
    pos[1] = p[1];
    DrawSmallNumber3_8002C290(pos, delta, ot);
}
extern unsigned char statIcons_80082EBC[];
extern unsigned char statRowY_80082EE8[];
extern void DrawUiTiySprt_8002C06C(void* p, int a1, int a2);
// Matched
void DrawStatIcons_8002E0D8(unsigned short* p, short ot)
{
    unsigned short pos[2];
    short i;
    pos[0] = p[0];
    for (i = 0; i < 5; i++)
    {
        pos[1] = p[1] + statRowY_80082EE8[i];
        DrawUiTiySprt_8002C06C(pos, statIcons_80082EBC[i], ot);
    }
}
extern void DrawLargeNumber_8002C100(unsigned short* pos, int v, int ot);
// Matched
void DrawStatCompare_8002E188(unsigned char* oldStats, unsigned char* newStats, unsigned short* pos, short ot)
{
    unsigned short loc[2];
    short i;
    for (i = 0; i < 5; i++)
    {
        if (oldStats[i] < newStats[i])
        {
            SetLargeDigitColor_8002C5D0(1);
        }
        else if (newStats[i] < oldStats[i])
        {
            SetLargeDigitColor_8002C5D0(2);
        }
        loc[0] = pos[0] + 0x16;
        loc[1] = pos[1] + i * 14 + 2;
        DrawLargeNumber_8002C100(loc, newStats[i], ot);
        SetLargeDigitColor_8002C5D0(0);
    }
}
// Matched
void CalcStatsWithEquip_8002E288(UnitStatus* src, int itemId, int slot, unsigned char* outStats)
{
    UnitStatus* p = 0; // works on a copy at address 0 (the scratch area)
    MemCopy_800403E8(0, src, sizeof(UnitStatus));

    switch (slot)
    {
    case 0:
        p->field_1C[0] = itemId;
        break;
    case 1:
        p->field_1C[1] = itemId;
        break;
    case 2:
        p->field_1C[2] = itemId;
        break;
    }
    CalcEquippedStats_80033624(outStats, p);
}
extern void AddClipDrawAreaPrim_80033308(unsigned long* ot);
extern int sub_800AD8E4(void);
extern void DrawAnimatedWindow_8002BEC8(int a0, int a1, short a2, short a3, int a4, int a5);
extern void DrawLargeText_8002FBD8(int a0, unsigned short* pos, unsigned char* name, int a3);
extern void DrawGauge_8002BA54(void* a, int b, void* c, int d);
extern void DrawCurMaxValue_8002EE28(short* a, unsigned short* pos, short c, int d);
// Matched
void DrawLevantSummary_8002E334(UnitStatus* st, MenuDrawArgs* args)
{
    short r[4];
    unsigned short loc2[2];
    unsigned short base[2];
    unsigned short loc[2];
    int buf[2];
    int hpGauge[4];
    int expGauge[4];

    base[0] = 0x4E;
    base[1] = 0x2C;
    AddClipDrawAreaPrim_80033308(&pOT_8008D454[args->ot_0]);
    loc[0] = 0xE0;
    loc[1] = 0x31;
    DrawUiTiySprt_8002C06C(loc, 0x82, args->ot_0);
    loc[0] = 0x132;
    loc[1] = 0x32;
    DrawLargeNumber_8002C100(loc, sub_800AD8E4(), args->ot_0);
    r[0] = 0xDB;
    r[1] = 0x2C;
    r[2] = 0x5B;
    r[3] = 0x17;
    DrawAnimatedWindow_8002BEC8((int)buf, (int)r, args->field_2, args->ot_0, args->field_4, args->field_8);
    loc[0] = 0xE0;
    loc[1] = 0x48;
    DrawUiTiySprt_8002C06C(loc, 0x52, args->ot_0);
    loc[0] = 0x132;
    loc[1] = 0x49;
    DrawLargeNumber_8002C100(loc, CountItems_800106B8(), args->ot_0);
    r[1] = 0x43;
    r[0] = 0xDB;
    r[2] = 0x5B;
    r[3] = 0x16;
    DrawAnimatedWindow_8002BEC8((int)buf, (int)r, args->field_2, args->ot_0, args->field_4, args->field_8);
    loc[0] = 0xE0;
    loc[1] = 0x5E;
    DrawUiTiySprt_8002C06C(loc, 0x6F, args->ot_0);
    loc[0] = 0x132;
    loc[1] = 0x5F;
    DrawLargeNumber_8002C100(loc, GetCapturedMinionsCount_800125B8(), args->ot_0);
    r[0] = 0xDB;
    r[1] = 0x59;
    r[2] = 0x5B;
    r[3] = 0x17;
    DrawAnimatedWindow_8002BEC8((int)buf, (int)r, args->field_2, args->ot_0, args->field_4, args->field_8);
    AddClipDrawAreaPrim_80033308(&pOT_8008D454[args->ot_0]);
    loc2[0] = base[0] + 4;
    loc2[1] = base[1] + 5;
    DrawUiTiySprt_8002C06C(loc2, 0x11, args->ot_0);
    loc2[0] = base[0] + 0x25;
    loc2[1] = base[1] + 6;
    DrawLargeText_8002FBD8(0, loc2, st->name_10, args->ot_0);
    loc2[0] = base[0] + 4;
    loc2[1] = base[1] + 0x15;
    DrawUiTiySprt_8002C06C(loc2, 0x12, args->ot_0);
    hpGauge[0] = 0;
    hpGauge[1] = 0;
    loc2[0] = base[0] + 0x22;
    loc2[1] = base[1] + 0x14;
    hpGauge[2] = st->hp_8;
    hpGauge[3] = st->maxHp_A;
    DrawGauge_8002BA54(hpGauge, 0, loc2, args->ot_0);
    loc2[0] = base[0] + 0x3C;
    loc2[1] = base[1] + 0x1C;
    DrawCurMaxValue_8002EE28((short*)&st->hp_8, loc2, args->ot_0, 1);
    loc2[0] = base[0] + 4;
    loc2[1] = base[1] + 0x24;
    DrawUiTiySprt_8002C06C(loc2, 0x70, args->ot_0);
    loc2[0] = base[0] + 0x80;
    loc2[1] = base[1] + 0x25;
    DrawLargeNumber_8002C100(loc2, st->level_44, args->ot_0);
    loc2[0] = base[0] + 4;
    loc2[1] = base[1] + 0x34;
    DrawUiTiySprt_8002C06C(loc2, 0xE2, args->ot_0);
    expGauge[0] = 2;
    expGauge[1] = 0;
    loc2[0] = base[0] + 0x4B;
    loc2[1] = base[1] + 0x36;
    expGauge[2] = st->exp_4;
    while (expGauge[2] > 0x4000000)
    {
        expGauge[2] -= 0x4000000;
    }
    expGauge[3] = 0x4000000;
    DrawGauge_8002BA54(expGauge, 0, loc2, args->ot_0);
}
void SetElementChartTri_8002E944(POLY_F3* p, unsigned short* pos, short idx, short dir);
// Matched
void DrawElementChart_8002E730(unsigned short* pos, unsigned char* levels, short ot)
{
    unsigned short p1[2];
    unsigned short p2[2];
    unsigned short v[2];
    POLY_F3 tri;
    unsigned short q[2];
    short i;
    short fy;
    short fx;
    int level;
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
        SetPolyF3(&tri);
        tri.r0 = elementChartColors_80082EA8[i][0];
        tri.g0 = elementChartColors_80082EA8[i][1];
        tri.b0 = elementChartColors_80082EA8[i][2];
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
        DrawUiTiySprt_8002C06C(q, elementChartIcons_80082EA4[i], ot);
        level = levels[elementChartOrder_80082EB8[i]];
        if (level)
        {
            SetElementChartTri_8002E944(&tri, v, level, i);
            AddPrimCopy_80040298(&pOT_8008D454[ot], &tri, 5);
        }
    }
    DrawUiTiySprt_8002C06C(pos, 0xB, ot);
}
// Matched
void SetElementChartTri_8002E944(POLY_F3* tri, unsigned short* pos, short level, short quadrant)
{
    int size = elementChartSizes_80082EF0[level];
    int w = 26;
    switch (quadrant)
    {
    case 0:
        tri->x0 = pos[0] + w;
        tri->y0 = pos[1] + w;
        tri->x1 = tri->x0;
        tri->y1 = pos[1] - (size - w) - 1;
        tri->x2 = pos[0] - (size - w) - 1;
        tri->y2 = tri->y0;
        break;
    case 1:
        tri->x0 = pos[0];
        tri->y0 = pos[1] + w;
        tri->x1 = tri->x0;
        tri->y1 = pos[1] - (size - w) - 1;
        tri->x2 = pos[0] + size;
        tri->y2 = tri->y0;
        break;
    case 2:
        tri->x0 = pos[0];
        tri->y0 = pos[1];
        tri->x1 = tri->x0;
        tri->y1 = pos[1] + size;
        tri->x2 = pos[0] + size;
        tri->y2 = tri->y0;
        break;
    case 3:
        tri->x0 = pos[0] + w;
        tri->y0 = pos[1];
        tri->x1 = tri->x0;
        tri->y1 = pos[1] + size;
        tri->x2 = pos[0] - (size - w);
        tri->y2 = tri->y0;
        break;
    }
}
extern void BaseStatRatios_8001419C(unsigned char* p, short* out);
extern void DrawRectOutline_80042750(RECT* r, unsigned char* rgb, void* ot);
extern void DrawLine_80042870(DVECTOR* a, DVECTOR* b, unsigned char* rgb, void* ot);
// Matched
void DrawStatGrid_8002EACC(UnitStatus* st, unsigned short* pos, int unused, short ot)
{
    short loc[2];
    DVECTOR a;
    DVECTOR b;
    RECT r;
    Color_EACC lineColor = statGridLineColor_800743D0;
    SPRT* prim;
    BaseStatRatios_8001419C(st->stats_2C, loc);
    loc[0] += pos[0];
    loc[1] += pos[1];
    DrawUiTiySprt_8002C06C(loc, 10, ot);
    prim = uiTiySprts_8008D620;
    prim[12].x0 = pos[0] + 2;
    prim[12].y0 = pos[1] + 2;
    SetSemiTrans(&prim[12], 1);
    AddPrimCopy_80040298(&pOT_8008D454[ot], &uiTiySprts_8008D620[12], 5);
    AddPrimCopy_80040298(&pOT_8008D454[ot], &uiTiyTPages_8008D3F4[12], 2);
    r.x = pos[0];
    r.y = pos[1];
    r.w = 0x32;
    r.h = 0x32;
    DrawRectOutline_80042750(&r, statGridOuterColor_80082E9C, &pOT_8008D454[ot]);
    r.x = pos[0] + 1;
    r.y = pos[1] + 1;
    r.w = 0x30;
    r.h = 0x30;
    DrawRectOutline_80042750(&r, statGridInnerColor_80082EA0, &pOT_8008D454[ot]);
    a.vx = pos[0] + 2;
    a.vy = pos[1] + 0x1A;
    b.vx = pos[0] + 0x32;
    b.vy = a.vy;
    DrawLine_80042870(&a, &b, lineColor.c, &pOT_8008D454[ot]);
    a.vx = pos[0] + 0x19;
    a.vy = pos[1] + 2;
    b.vx = a.vx;
    b.vy = pos[1] + 0x32;
    DrawLine_80042870(&a, &b, lineColor.c, &pOT_8008D454[ot]);
}
