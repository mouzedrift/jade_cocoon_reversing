#include "common.h"
#include "funcs.h"
#include "sdk.h"
#include "globals.h"
#include "sound.h"
#include "data_decls.h"
#include "menu_window.h"
#include "effect_data.h"
#include "pad_text.h"
#include "font.h"
#include "util.h"
#include "event.h"
#include "ui_sprites.h"

const Block16 elementIconRowOffsets_800741C4 = { { 0, 0, 14, 0, 28, 0, 42 } };

void DrawMenuItemWindow_8002AAF0(MenuWindowList* list, int i, int j, RECT* rect)
{
    WindowStyle style;
    int time;
    int flags;
    MenuWindowItem* item = &list->items_10[i][j];
    time = 0;
    if (item->flags_0 & 0x20)
    {
        return;
    }
    flags = list->flags_0;
    if (flags & 8)
    {
        style.semiTrans_3 = 0;
    }
    else if (flags & 0x10)
    {
        style.semiTrans_3 = 1;
    }
    else if (flags & 0x20)
    {
        style.semiTrans_3 = 2;
    }
    else if (flags & 0x40)
    {
        style.semiTrans_3 = 3;
    }
    else if (flags & 0x80)
    {
        style.semiTrans_3 = 4;
    }
    else
    {
        style.semiTrans_3 = 1;
    }
    flags = list->flags_0;
    if (flags & 1)
    {
        style.colorSet_2 = 0;
    }
    else if (flags & 2)
    {
        style.colorSet_2 = 1;
        if (list->cursor_C == i)
        {
            time = list->time_4;
        }
    }
    else if ((flags & 4) && list->cursor_C == i)
    {
        style.colorSet_2 = 2;
    }
    else
    {
        style.colorSet_2 = 0;
    }
    flags = list->flags_0;
    if (!(flags & 0x100))
    {
        style.color_0 = saveData_8008B570.uiColor_20.s;
    }
    else if (flags & 0x2000)
    {
        style.color_0 = 4;
    }
    else if (flags & 0x1000)
    {
        style.color_0 = 3;
    }
    else if (flags & 0x800)
    {
        style.color_0 = 2;
    }
    else if (flags & 0x400)
    {
        style.color_0 = 1;
    }
    else
    {
        style.color_0 = 0;
    }
    DrawWindow_80042460(rect, &style, &pOT_8008D454[list->ot_14], time);
}
void AlignMenuItem_8002AC88(int flags, short* rect, int width, short* out)
{
    if (flags & 4)
    {
        out[0] = rect[0] + (rect[2] - width);
        out[1] = rect[1];
        return;
    }
    if (flags & 8)
    {
        out[0] = rect[0] + ((unsigned int)(rect[2] - width) >> 1);
        out[1] = rect[1];
        return;
    }
    out[0] = rect[0];
    out[1] = rect[1];
}
void GetMenuItemColor_8002ACE8(int flags, unsigned char* out)
{
    unsigned char val;
    if (flags & 2)
    {
        val = 0x40;
    }
    else
    {
        val = 0x80;
    }
    out[0] = val;
    out[1] = val;
    out[2] = val;
}
void SetMenuItemFont1Clut_8002AD08(int flags)
{
    if (flags & 2)
    {
        SetFontClutOffset_8003F900(1, 1);
    }
    else
    {
        SetFontClutOffset_8003F900(1, 0);
    }
}
void SetMenuItemFont2Clut_8002AD44(int flags)
{
    if (flags & 2)
    {
        SetFontClutOffset_8003F900(2, 1);
    }
    else
    {
        SetFontClutOffset_8003F900(2, 0);
    }
}
void SetMenuItemDigitColor_8002AD80(int flags)
{
    if (flags & 2)
    {
        SetLargeDigitColor_8002C5D0(3);
    }
    else
    {
        SetLargeDigitColor_8002C5D0(0);
    }
}
void DrawMenuItemWithWindow_8002ADB4(MenuWindowItem* item, void* window, int ot, int time)
{
    DrawMenuWindowContents_8002A710(item, ot);
    SetFontClutOffset_8003F900(2, 0);
    SetFontClutOffset_8003F900(1, 0);
    DrawWindow_80042460((RECT*)&item->x_10, window, &pOT_8008D454[ot], time);
}
void DrawTextLinesWindow_8002AE38(const char** lines, Pos16* pos, int ot, RECT* rect, int count)
{
    Pos16 cur;
    WindowStyle style;
    unsigned int i;
    cur.x = pos->x;
    cur.y = pos->y;
    for (i = 0; i < count; i++)
    {
        if (lines[i])
        {
            DrawText_8003E91C(2, lines[i], (short*)&cur, ot);
        }
        cur.y += 12;
    }
    if (rect)
    {
        style.semiTrans_3 = 1;
        style.colorSet_2 = 0;
        style.color_0 = saveData_8008B570.uiColor_20.s;
        DrawWindow_80042460(rect, &style, &pOT_8008D454[ot], 0);
    }
}
void DrawLargeTextBox_8002AF10(const char** text, Pos16* pos, int ot)
{
    RECT rect;
    rect.x = 10;
    rect.y = 0x99;
    rect.w = 0x12C;
    rect.h = 0x3C;
    DrawTextBox_8002AFA0(text, pos, ot, &rect, 4);
}
void DrawSmallTextBox_8002AF58(const char** text, Pos16* pos, int ot)
{
    RECT rect;
    rect.x = 10;
    rect.y = 0xC3;
    rect.w = 0x12C;
    rect.h = 0x12;
    DrawTextBox_8002AFA0(text, pos, ot, &rect, 1);
}
void DrawTextBox_8002AFA0(const char** text, Pos16* pos, int ot, RECT* rect, int count)
{
    Pos16 cur;
    if (pos)
    {
        rect->x = pos->x;
        rect->y = pos->y;
    }
    cur.x = rect->x + 4;
    cur.y = rect->y + 5;
    DrawTextLinesWindow_8002AE38(text, &cur, ot, rect, count);
}
void DrawButtonHelpBar_8002B004(ButtonHelpEntry* entries, Pos16* origin, int ot)
{
    Pos16 cur;
    Pos16 base;
    RECT rect;
    WindowStyle style;
    int i;
    i = 0;
    if (origin)
    {
        base.x = origin->x;
        base.y = origin->y;
    }
    else
    {
        base.x = 10;
        base.y = 0xD6;
    }
    cur.x = base.x + 2;
    for (; entries[i].icon_0 >= 0; i++)
    {
        cur.y = base.y + (14 - uiTiySprts_8008D620[entries[i].icon_0].h) / 2;
        DrawUiTiySprt_8002C06C((unsigned short*)&cur, entries[i].icon_0, ot);
        cur.x = (unsigned short)(cur.x + 1) + uiTiySprts_8008D620[entries[i].icon_0].w;
        cur.y = base.y + 2;
        DrawText_8003E91C(2, entries[i].text_4, (short*)&cur, ot);
        cur.x = MeasureTextWidth_8003E4C8(entries[i].text_4) + (unsigned short)(cur.x + 4);
    }
    rect.x = base.x;
    rect.y = base.y;
    rect.w = 0x12C;
    rect.h = 0xE;
    style.semiTrans_3 = 1;
    style.colorSet_2 = 0;
    style.color_0 = saveData_8008B570.uiColor_20.s;
    DrawWindow_80042460(&rect, &style, &pOT_8008D454[ot], 0);
}
extern void DrawElementIcons_8002B2A4(short a, short* b, int c, Block16* d, int e);
void DrawElementIconsRow_8002B1B0(short mask, short* pos, int ot)
{
    Block16 local = elementIconRowOffsets_800741C4;
    DrawElementIcons_8002B2A4(mask, pos, ot, &local, 0);
}
