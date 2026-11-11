#include "common.h"
#include "funcs.h"
#include "sdk.h"
#include "globals.h"
#include "sound.h"
#include "data_decls.h"
#include "unit.h"
#include "unit_gauges.h"
#include "menu_window.h"
#include "msg_window.h"
#include "event.h"
#include "ui_sprites.h"
#include "menu_draw.h"
#include "party_window.h"
#include "ui_gauge.h"
#include "element_grid.h"

const MenuWindowItem statusIcon0_800743D4 = { 0x10, 1, { .num = 151 }, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 210, 172, 21, 20, 3, 4 };
const MenuWindowItem statusIcon1_800743F0 = { 0x10, 1, { .num = 189 }, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0, 0, 34, 20, 3, 5 };
const MenuWindowItem statusIcon2_8007440C = { 0x10, 1, { .num = 177 }, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0, 0, 34, 20, 6, 5 };
const StatusIconMasks statusIconMasks_80074428 = { { 1, 0x3F8, 2 } };

void DrawUnitStatusExp_8002ECE0(UnitStatus* unit, unsigned short* pos, int unused, short ot)
{
    unsigned short loc[2];
    Gauge expGauge;
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
    expGauge.state = 2;
    expGauge.delta_4 = 0;
    exp = unit->exp_4;
    while (exp > 0x4000000)
    {
        exp -= 0x4000000;
    }
    expGauge.cur_8 = exp;
    expGauge.max_C = 0x4000000;
    loc[0] = pos[0] + 0x20;
    loc[1] = pos[1] + 0x42;
    DrawGauge_8002BA54(&expGauge, 0, loc, (short)ot);
    loc[0] = pos[0];
    loc[1] = pos[1] + 0x24;
    DrawMpGauge_8002F120(unit, loc, 0, ot);
}
void DrawCurMaxValue_8002EE28(UnitGauge* values, unsigned short* pos, short ot, int showNumbers)
{
    unsigned short loc[2];
    if (showNumbers)
    {
        loc[0] = pos[0] + 0x15;
        loc[1] = pos[1];
        DrawSmallNumber3_8002C290(loc, values->cur_0, ot);
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
        DrawSmallNumber3_8002C290(loc, values->max_2, ot);
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
void DrawValueGauge_8002EFC4(UnitGauge* values, int gaugeArg, int time, void* origin_, int ot, int showNumbers)
{
    unsigned short pos[2];
    Gauge gauge;
    unsigned short* origin = (unsigned short*)origin_;
    gauge.state = 1;
    gauge.delta_4 = gaugeArg;
    gauge.cur_8 = values->cur_0;
    gauge.max_C = values->max_2;
    pos[0] = origin[0];
    pos[1] = origin[1];
    DrawGauge_8002BA54(&gauge, time, pos, ot);
    pos[0] = origin[0] + 8;
    pos[1] = origin[1] + 7;
    DrawCurMaxValue_8002EE28(values, pos, (short)ot, showNumbers);
}
void DrawHpGauge_8002F078(UnitStatus* unit, unsigned short* pos, int gaugeArg, short ot)
{
    unsigned short loc[2];
    loc[0] = pos[0] + 7;
    loc[1] = pos[1] + 4;
    DrawUiTiySprt_8002C06C(loc, 0x76, ot);
    loc[0] = pos[0] + 0x20;
    loc[1] = pos[1] + 3;
    DrawValueGauge_8002EFC4(&unit->hp_8, gaugeArg, 0, loc, ot, 1);
}
void DrawMpGauge_8002F120(UnitStatus* unit, unsigned short* pos, int gaugeArg, short ot)
{
    unsigned short loc[2];
    loc[0] = pos[0] + 7;
    loc[1] = pos[1] + 4;
    DrawUiTiySprt_8002C06C(loc, 0x71, ot);
    loc[0] = pos[0] + 0x20;
    loc[1] = pos[1] + 3;
    DrawValueGauge_8002EFC4(&unit->mp_C, gaugeArg, 0, loc, ot, 1);
}
void DrawUnitStatusWindow_8002F1C8(UnitStatus* unit, int gaugeArg, int highlight, int time, RECT* rect, int ot, int flags)

{
    UiWindowDesc desc;
    DrawUnitStatus_8002F23C(unit, gaugeArg, time, (unsigned short*)rect, ot, flags);
    desc.colorSet_8 = highlight;
    desc.rect_0 = rect;
    desc.time_4 = time;
    desc.ot_A = ot;
    DrawUiWindow_8002A384(&desc);
}

void DrawUnitStatus_8002F23C(UnitStatus* unit, int gaugeArg, int time, unsigned short* pos, int ot, int flags)
{
    unsigned short loc[2];
    loc[0] = pos[0] + 7;
    loc[1] = pos[1] + 3;
    DrawSmallText_8002FAA0(0, loc, unit->name_10, ot);
    loc[0] = pos[0] + 3;
    loc[1] = pos[1] + 0xB;
    DrawValueGauge_8002EFC4(&unit->hp_8, gaugeArg, time, loc, ot, (flags ^ 1) & 1);
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
    style.color_0 = saveData_8008B570.uiColor_20.s;
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
