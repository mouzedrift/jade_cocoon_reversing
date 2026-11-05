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
#include "unit_gauges.h"
#include "menu_window.h"
#include "msg_window.h"
#include "event.h"

const MenuWindowItem statusIcon0_800743D4 = { 0x10, 1, 151, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 210, 172, 21, 20, 3, 4 };
const MenuWindowItem statusIcon1_800743F0 = { 0x10, 1, 189, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0, 0, 34, 20, 3, 5 };
const MenuWindowItem statusIcon2_8007440C = { 0x10, 1, 177, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0, 0, 34, 20, 6, 5 };
const StatusIconMasks statusIconMasks_80074428 = { { 1, 0x3F8, 2 } };

extern void DrawUnitStatus_8002F23C(UnitStatus* a0, int a1, int a2, unsigned short* a3, int a4, int a5);
extern void DrawGauge_8002BA54(void* a, int b, void* c, int d);
void DrawMpGauge_8002F120(char* a0, unsigned short* pos, int a2, short a3);
extern void DrawUiTiySprt_8002C06C(void* p, int a1, int a2);
// Matched
void DrawUnitStatusExp_8002ECE0(UnitStatus* unit, unsigned short* pos, int unused, short ot)
{
    unsigned short loc[2];
    unsigned int expGauge[4];
    RECT rect;
    unsigned int exp;
    rect.x = pos[0];
    rect.y = pos[1];
    rect.w = 0;
    rect.h = 0;
    DrawUnitStatus_8002F23C(unit, 0, frameCount_8008D3FC, (unsigned short*)&rect, (short)ot, 0);
    loc[0] = pos[0] + 7;
    loc[1] = pos[1] + 0x37;
    DrawUiTiySprt_8002C06C(loc, 0x3B, ot);
    expGauge[0] = 2;
    expGauge[1] = 0;
    exp = unit->exp_4;
    while (exp > 0x4000000)
    {
        exp -= 0x4000000;
    }
    expGauge[2] = exp;
    expGauge[3] = 0x4000000;
    loc[0] = pos[0] + 0x20;
    loc[1] = pos[1] + 0x42;
    DrawGauge_8002BA54(expGauge, 0, loc, (short)ot);
    loc[0] = pos[0];
    loc[1] = pos[1] + 0x24;
    DrawMpGauge_8002F120((char*)unit, loc, 0, ot);
}
extern void DrawUiTiySprt_8002C06C(void* p, int a1, int a2);
extern void DrawSmallNumber3_8002C290(unsigned short* pos, int val, int ot);
void DrawUiTiySprtRow_8002EF5C(unsigned short* pos, short count, short a2);
// Matched
void DrawCurMaxValue_8002EE28(short* values, unsigned short* pos, short ot, int showNumbers)
{
    unsigned short loc[2];
    if (showNumbers)
    {
        loc[0] = pos[0] + 0x15;
        loc[1] = pos[1];
        DrawSmallNumber3_8002C290(loc, values[0], ot);
    }
    else
    {
        unsigned short x = pos[0];
        unsigned short y;
        loc[0] = x - 5;
        y = pos[1];
        loc[0] = x;
        loc[1] = y;
        DrawUiTiySprtRow_8002EF5C(loc, 3, ot);
    }
    loc[0] = pos[0] + 0x15;
    loc[1] = pos[1];
    DrawUiTiySprt_8002C06C(loc, 0xDA, ot);
    if (showNumbers)
    {
        unsigned short x = pos[0];
        unsigned short y;
        loc[0] = x + 0x2B;
        y = pos[1];
        loc[0] = x + 0x30;
        loc[1] = y;
        DrawSmallNumber3_8002C290(loc, values[1], ot);
    }
    else
    {
        unsigned short x = pos[0];
        unsigned short y;
        loc[0] = x + 0x1E;
        y = pos[1];
        loc[0] = x + 0x1B;
        loc[1] = y;
        DrawUiTiySprtRow_8002EF5C(loc, 3, ot);
    }
}
extern void DrawUiTiySprt_8002C06C(void* p, int a1, int a2);
// Matched
void DrawUiTiySprtRow_8002EF5C(unsigned short* pos, short count, short ot)
{
    unsigned short loc[2];
    loc[0] = pos[0];
    loc[1] = pos[1];
    do
    {
        DrawUiTiySprt_8002C06C(loc, 0xd9, ot);
        count--;
        loc[0] += 7;
    } while (count > 0);
}
extern void DrawGauge_8002BA54(void* a, int b, void* c, int d);
extern void DrawCurMaxValue_8002EE28(short* a, unsigned short* pos, short c, int d);
extern void DrawValueGauge_8002EFC4(char* a0, int a1, int a2, void* a3_, int a4, int a5);
// Matched
void DrawValueGauge_8002EFC4(char* values, int gaugeArg, int time, void* origin_, int ot, int showNumbers)
{
    unsigned short pos[2];
    int gauge[4];
    unsigned short* origin = (unsigned short*)origin_;
    gauge[0] = 1;
    gauge[1] = gaugeArg;
    gauge[2] = ((short*)values)[0];
    gauge[3] = ((short*)values)[1];
    pos[0] = origin[0];
    pos[1] = origin[1];
    DrawGauge_8002BA54(gauge, time, pos, ot);
    pos[0] = origin[0] + 8;
    pos[1] = origin[1] + 7;
    DrawCurMaxValue_8002EE28(values, pos, (short)ot, showNumbers);
}
// Matched
void DrawHpGauge_8002F078(char* unit, unsigned short* pos, int gaugeArg, short ot)
{
    unsigned short loc[2];
    loc[0] = pos[0] + 7;
    loc[1] = pos[1] + 4;
    DrawUiTiySprt_8002C06C(loc, 0x76, ot);
    loc[0] = pos[0] + 0x20;
    loc[1] = pos[1] + 3;
    DrawValueGauge_8002EFC4(unit + 8, gaugeArg, 0, loc, ot, 1);
}
// Matched
void DrawMpGauge_8002F120(char* unit, unsigned short* pos, int gaugeArg, short ot)
{
    unsigned short loc[2];
    loc[0] = pos[0] + 7;
    loc[1] = pos[1] + 4;
    DrawUiTiySprt_8002C06C(loc, 0x71, ot);
    loc[0] = pos[0] + 0x20;
    loc[1] = pos[1] + 3;
    DrawValueGauge_8002EFC4(unit + 0xC, gaugeArg, 0, loc, ot, 1);
}
typedef struct
{
    int rect_0;
    int time_4;
    short colorSet_8;
    short ot_A;
} UiWindowDesc;
extern void DrawUnitStatus_8002F23C(UnitStatus* a0, int a1, int a2, unsigned short* a3, int a4, int a5);
extern void DrawUiWindow_8002A384(UiWindowDesc* p);
// Matched
void DrawUnitStatusWindow_8002F1C8(UnitStatus* unit, int gaugeArg, int highlight, int time, int rect, int ot, int flags)

{
    UiWindowDesc desc;
    DrawUnitStatus_8002F23C(unit, gaugeArg, time, (unsigned short*)rect, ot, flags);
    desc.colorSet_8 = highlight;
    desc.rect_0 = rect;
    desc.time_4 = time;
    desc.ot_A = ot;
    DrawUiWindow_8002A384(&desc);
}

extern void DrawSmallText_8002FAA0(int a0, unsigned short* pos, unsigned char* name, int a3);
extern void DrawElementIconsGrid_8002B228(short a, unsigned short* pos, int ot, int flags);
// Matched
void DrawUnitStatus_8002F23C(UnitStatus* unit, int gaugeArg, int time, unsigned short* pos, int ot, int flags)
{
    unsigned short loc[2];
    loc[0] = pos[0] + 7;
    loc[1] = pos[1] + 3;
    DrawSmallText_8002FAA0(0, loc, unit->name_10, ot);
    loc[0] = pos[0] + 3;
    loc[1] = pos[1] + 0xB;
    DrawValueGauge_8002EFC4((char*)&unit->hp_8.cur_0, gaugeArg, time, loc, ot, (flags ^ 1) & 1);
    loc[0] = pos[0] + 0x45;
    loc[1] = pos[1] + 4;
    DrawElementIconsGrid_8002B228(GetUnitElementMask_8003412C(unit), loc, ot, flags);
    if (flags & 2)
    {
        loc[0] = pos[0] + 4;
        loc[1] = pos[1] + 0x1C;
        DrawUiTiySprt_8002C06C(loc, 0xE1, ot);
        loc[0] = pos[0] + 0x1B;
        loc[1] = pos[1] + 0x1B;
        DrawUiTiySprt_8002C06C(loc, 0x78, ot);
        loc[0] = pos[0] + 0x35;
    }
    else
    {
        loc[0] = pos[0] + 0x10;
        loc[1] = pos[1] + 0x1B;
        DrawUiTiySprt_8002C06C(loc, 0x78, ot);
        loc[0] = pos[0] + 0x2A;
    }
    loc[1] = pos[1] + 0x1D;
    if (!(flags & 1))
    {
        loc[0] += 0xD;
        DrawSmallNumber3_8002C290(loc, ((unsigned char*)unit)[0x44], ot);
    }
    else
    {
        DrawUiTiySprtRow_8002EF5C(loc, 2, ot);
    }
}
// Matched
short ElementLevelsToMask_8002F424(unsigned char* levels)
{
    short mask = 0;
    short i;
    if (levels)
    {
        for (i = 0; i < 4; i++)
        {
            if (levels[i])
            {
                mask |= 1 << i;
            }
        }
    }
    return mask;
}
extern short uiColor_8008B590;
// Matched
void DrawMenuWindowItems_8002F480(int* status, unsigned short* pos, int ot, int reverse)
{
    MenuWindowItem icon0 = statusIcon0_800743D4;
    MenuWindowItem icon1 = statusIcon1_800743F0;
    MenuWindowItem icon2 = statusIcon2_8007440C;
    WindowStyle style;
    MenuWindowItem* icons[3];
    StatusIconMasks masks = statusIconMasks_80074428;
    unsigned short loc[2];
    int i;
    int j;
    icons[0] = &icon0;
    icons[1] = &icon1;
    icons[2] = &icon2;
    if (pos)
    {
        loc[0] = pos[0];
        loc[1] = pos[1];
    }
    else
    {
        loc[0] = 0xD2;
        loc[1] = 0xAC;
    }
    style.colorSet_2 = 0;
    style.semiTrans_3 = 1;
    style.color_0 = uiColor_8008B590;
    for (i = 0; i < 3; i++)
    {
        j = i;
        if (reverse)
        {
            j = 2 - i;
        }
        if (*status & masks.m[j])
        {
            if (!reverse)
            {
                icons[j]->x_10 = loc[0];
                icons[j]->y_12 = loc[1];
                DrawMenuItemWithWindow_8002ADB4(icons[j], &style, ot, 0);
                loc[0] += icons[j]->w_14;
            }
            else
            {
                loc[0] -= icons[j]->w_14;
                icons[j]->x_10 = loc[0];
                icons[j]->y_12 = loc[1];
                DrawMenuItemWithWindow_8002ADB4(icons[j], &style, ot, 0);
            }
        }
    }
}
