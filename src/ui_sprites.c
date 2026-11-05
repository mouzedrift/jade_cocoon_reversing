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
#include "minion_menu.h"
#include "effect_data.h"
#include "engine.h"
#include "util.h"
#include "unit_query.h"
#include "movie.h"
#include "cd.h"
#include "ui_sprites.h"
#include "menu_draw.h"

const int emptyString_800741EC = 0;

// Matched
void DrawMenuBackground_8002BE10(void)
{
    unsigned short pos[2];
    short i;
    short j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 3; j++)
        {
            pos[0] = (j << 16) >> 9;
            if (i & 1)
            {
                pos[0] -= 0x40;
            }
            pos[1] = i * 60;
            DrawUiTiySprt_8002C06C(pos, 0x95, 0xF);
        }
    }
}
// Matched
void DrawAnimatedWindow_8002BEC8(RECT* outRect, RECT* rect, short step, short ot, int highlight, int time)
{
    UiWindowDesc desc;
    InterpolateWindowRect_8004196C(outRect, rect, step, 8, 0);
    AddDrawAreaPrim_8003326C(outRect, &pOT_8008D454[ot]);
    if (highlight)
    {
        desc.colorSet_8 = 1;
    }
    else
    {
        desc.colorSet_8 = 0;
    }
    desc.rect_0 = outRect;
    desc.time_4 = time;
    desc.ot_A = ot;
    DrawUiWindow_8002A384(&desc);
    AddClipDrawAreaPrim_80033308(&pOT_8008D454[ot]);
}
// Matched
void LoadUiTiy_8002BF74(void)
{
    FileRequestDesc req;
    uiTiyLoaded_8008B4E8 = 0;
    req.flags_0 = 0x29;
    req.fileId_4 = 0x3B;
    req.offset_8 = 0;
    req.size_C = 0;
    req.dest_10 = 0;
    req.params_14 = 0;
    req.paramsSize_18 = 0;
    req.callback_1C = OnUiTiyLoaded_8002BFCC;
    QueueFileRequest_8003BC84(&req);
}
// Matched
void OnUiTiyLoaded_8002BFCC(void* params, int* data)
{
    LoadTiy_80028E74(&uiTiySprts_8008D620, 0, &uiTiyTPages_8008D3F4, data, 1);
    uiTiyLoaded_8008B4E8 = 1;
}
// Matched
void FreeActiveOverlay_8002C014(void)
{
    if (uiTiySprts_8008D620)
    {
        free3_8003FC6C(uiTiySprts_8008D620);
        uiTiySprts_8008D620 = 0;
    }
    if (uiTiyTPages_8008D3F4)
    {
        free3_8003FC6C(uiTiyTPages_8008D3F4);
        uiTiyTPages_8008D3F4 = 0;
    }
}
// Matched
void DrawUiTiySprt_8002C06C(unsigned short* pos, int idx, int ot)
{
    uiTiySprts_8008D620[idx].x0 = pos[0];
    uiTiySprts_8008D620[idx].y0 = pos[1];
    AddPrimCopy_80040298(&pOT_8008D454[ot], &uiTiySprts_8008D620[idx], 5);
    AddPrimCopy_80040298(&pOT_8008D454[ot], &uiTiyTPages_8008D3F4[idx], 2);
}
// Matched
void DrawLargeNumber_8002C100(unsigned short* origin, int value, int ot)
{
    short digits[7];
    unsigned short pos[2];
    short i;
    short j;
    for (i = 0; i < 7; i++)
    {
        digits[i] = -1;
    }
    if (value > 9999999)
    {
        value = 9999999;
    }
    i = 0;
    do
    {
        digits[i] = value % 10 + 0x84;
        value /= 10;
        i++;
    } while (value);
    pos[1] = origin[1];
    for (j = 0; j < i; j++)
    {
        if (digits[j] != -1)
        {
            pos[0] = origin[0] - (j + 1) * (uiTiySprts_8008D620[digits[j]].w - 1);
            DrawUiTiySprt_8002C06C(pos, digits[j], ot);
        }
    }
}
// Matched
void DrawSmallNumber3_8002C290(unsigned short* origin, int value, int ot)
{
    short digits[3];
    unsigned short pos[2];
    short i;
    short j;
    for (i = 0; i < 3; i++)
    {
        digits[i] = -1;
    }
    if (value > 999)
    {
        value = 999;
    }
    i = 0;
    do
    {
        digits[i] = value % 10 + 0xCF;
        value /= 10;
        i++;
    } while (value);
    pos[1] = origin[1];
    for (j = 0; j < i; j++)
    {
        if (digits[j] != -1)
        {
            pos[0] = origin[0] - (j + 1) * (uiTiySprts_8008D620[digits[j]].w - 1);
            DrawUiTiySprt_8002C06C(pos, digits[j], ot);
        }
    }
}
// Matched
void DrawSmallNumber9_8002C414(unsigned short* origin, int value, int ot)
{
    short digits[9];
    unsigned short pos[2];
    short i;
    short j;
    for (i = 0; i < 9; i++)
    {
        digits[i] = -1;
    }
    if (value > 999999999)
    {
        value = 999999999;
    }
    i = 0;
    do
    {
        digits[i] = value % 10 + 0xCF;
        value /= 10;
        i++;
    } while (value);
    pos[1] = origin[1];
    for (j = 0; j < i; j++)
    {
        if (digits[j] != -1)
        {
            pos[0] = origin[0] - (j + 1) * (uiTiySprts_8008D620[digits[j]].w - 1);
            DrawUiTiySprt_8002C06C(pos, digits[j], ot);
        }
    }
}
// Matched
int CountDigits_8002C5A4(int value)
{
    do
    {
        value /= 10;
    } while (value);
    return 0;
}
// Matched
void SetLargeDigitColor_8002C5D0(int color)
{
    short i = 0x84;
    do
    {
        uiTiySprts_8008D620[i].r0 = largeDigitColors_800826F8[color][0];
        uiTiySprts_8008D620[i].g0 = largeDigitColors_800826F8[color][1];
        uiTiySprts_8008D620[i].b0 = largeDigitColors_800826F8[color][2];
        i++;
    } while (i < 0x8e);
}
// Matched
unsigned int GetTime30Hz_8002C64C(void)
{
    return (unsigned int)(frameCount_8008D3FC * display_8008B4D8.vsyncsPerFrame_4) >> 1;
}
// Matched
int DrawAbilityDescription_8002C670(char* minion, int pos, int texts, short slot, short ot)
{
    char* skill = minion + slot * 4;
    int b;
    if (!(skill[0xde] & 1))
    {
        return 0;
    }
    if (skill[0xdf] == 0)
    {
        return 0;
    }
    DrawLargeTextBox_8002AF10(texts + (unsigned char)skill[0xdf] * 16, pos, ot);
    return 1;
}
typedef struct
{
    short kind;
    short dir;
} ScrollArrow;
extern void DrawScrollArrow_8002B3DC(ScrollArrow arrow, int time, short* pos, int ot);
// Matched
void DrawScrollArrow_8002C6DC(short* pos, short dir, short ot)
{
    ScrollArrow arrow;
    arrow.kind = 2;
    arrow.dir = dir;
    DrawScrollArrow_8002B3DC(arrow, frameCount_8008D3FC, pos, ot);
}
extern int GetLastInventorySlot_800AD308(int a0);
extern const int emptyString_800741EC;
// Matched
void DrawItemList_8002C728(ListMenuState* menu)
{
    MenuWindowList list;
    short cursor;
    short openStep;
    short i;
    int idx;
    int count;
    int icon;
    int name;
    MenuWindowItem** row;
    int y;
    int total;
    cursor = menu->cursor_0;
    openStep = 8;
    for (i = 0; i < 4; i++)
    {
        idx = GetInventorySlotId_800AD288(i + menu->scroll_2, 0);
        if (idx < 0x2B)
        {
            icon = GetItemIcon_8001D2AC(idx);
            name = GetItemName_8001CE20(idx);
            count = GetInventorySlotCount_800AD2C8(i + menu->scroll_2, 0);
        }
        else
        {
            icon = -1;
            name = (int)&emptyString_800741EC;
            count = 0;
        }
        row = &itemListRows_800829E8[i];
        (*row)[0].text_4 = icon;
        (*row)[0].sprts_8 = &publicTiySprts_8008D434;
        (*row)[0].tpages_C = &publicTiyTPages_8008D440;
        (*row)[1].text_4 = name;
        (*row)[2].text_4 = count;
        (*row)[0].x_10 = 0x53;
        y = i * 22 + 0x36;
        (*row)[0].y_12 = y;
        (*row)[1].x_10 = 0x68;
        (*row)[1].y_12 = y;
        (*row)[2].x_10 = 0xD8;
        (*row)[2].y_12 = y;
        menu->cursor_0 = i;
        if ((short)CheckItemUsable_80033AFC(menu))
        {
            (*row)[0].flags_0 |= 2;
            (*row)[1].flags_0 |= 2;
            (*row)[2].flags_0 |= 2;
        }
        else
        {
            (*row)[0].flags_0 &= ~2;
            (*row)[1].flags_0 &= ~2;
            (*row)[2].flags_0 &= ~2;
        }
        if (count == 0)
        {
            itemListRows_800829E8[i][0].flags_0 |= 0x40;
            itemListRows_800829E8[i][1].flags_0 |= 0x40;
            itemListRows_800829E8[i][2].flags_0 |= 0x40;
        }
        else
        {
            itemListRows_800829E8[i][0].flags_0 &= ~0x40;
            itemListRows_800829E8[i][1].flags_0 &= ~0x40;
            itemListRows_800829E8[i][2].flags_0 &= ~0x40;
        }
    }
    list.flags_0 = menu->windowFlags_4;
    list.time_4 = frameCount_8008D3FC;
    list.open_8 = openStep;
    list.cursor_C = cursor;
    list.items_10 = itemListRows_800829E8;
    list.ot_14 = menu->ot_6;
    DrawMenuWindows_8002A5A4(&list);
    SetFontClutOffset_8003F900(2, 0);
    total = GetLastInventorySlot_800AD308(0) + 1;
    if (total < 4)
    {
        total = 4;
    }
    if (menu->scroll_2)
    {
        DrawScrollArrow_8002C6DC(itemScrollUpPos_80082820, 3, menu->ot_6);
    }
    if (menu->scroll_2 < total - 4 && total >= 5)
    {
        DrawScrollArrow_8002C6DC(itemScrollDownPos_80082824, 1, menu->ot_6);
    }
}
// Matched
void DrawMagicList_8002CAC8(ListMenuState* menu, unsigned short* origin)
{
    unsigned short pos[2];
    MenuWindowList list;
    unsigned short arrowPos[2];
    short cursor;
    short openStep;
    short i;
    int idx;
    int icon;
    int name;
    MenuWindowItem** row;
    int y;
    int total;
    cursor = menu->cursor_0;
    openStep = 8;
    if (origin)
    {
        pos[0] = origin[0];
        pos[1] = origin[1];
    }
    else
    {
        pos[0] = 0x60;
        pos[1] = 0x36;
    }
    if (menu->minion_C == 0)
    {
        return;
    }
    for (i = 0; i < 4; i++)
    {
        idx = FindNthMagicBit_8001AEC0(&menu->minion_C->magicBits_F4, i + menu->scroll_2);
        if (idx < 0x1E)
        {
            icon = GetMagicIcon_8001AF3C(idx);
            name = GetMagicName_8001AC2C(idx);
        }
        else
        {
            icon = -1;
            name = (int)&emptyString_800741EC;
        }
        row = &magicListRows_80082B54[i];
        (*row)[0].text_4 = icon;
        (*row)[1].text_4 = name;
        (*row)[0].x_10 = pos[0];
        y = i * 22;
        (*row)[0].y_12 = pos[1] + y;
        (*row)[1].x_10 = pos[0] + 0x15;
        (*row)[1].y_12 = pos[1] + y;
        menu->cursor_0 = i;
        if ((short)CheckMagicCastable_80033C08(menu))
        {
            (*row)[0].flags_0 |= 2;
            (*row)[1].flags_0 |= 2;
        }
        else
        {
            (*row)[0].flags_0 &= ~2;
            (*row)[1].flags_0 &= ~2;
        }
    }
    list.flags_0 = menu->windowFlags_4;
    list.time_4 = frameCount_8008D3FC;
    list.open_8 = openStep;
    list.cursor_C = cursor;
    list.items_10 = magicListRows_80082B54;
    list.ot_14 = menu->ot_6;
    DrawMenuWindows_8002A5A4(&list);
    SetFontClutOffset_8003F900(2, 0);
    total = CountMagicBits_8001AE54(&menu->minion_C->magicBits_F4);
    if (total < 4)
    {
        total = 4;
    }
    if (menu->scroll_2)
    {
        if (origin)
        {
            arrowPos[0] = magicScrollUpPos_800829FC[0] + origin[0] - 0x60;
            arrowPos[1] = magicScrollUpPos_800829FC[1] + origin[1] - 0x36;
        }
        else
        {
            arrowPos[0] = magicScrollUpPos_800829FC[0];
            arrowPos[1] = magicScrollUpPos_800829FC[1];
        }
        DrawScrollArrow_8002C6DC((short*)arrowPos, 3, menu->ot_6);
    }
    if (menu->scroll_2 < total - 4 && total >= 5)
    {
        if (origin)
        {
            arrowPos[0] = magicScrollDownPos_80082A00[0] + origin[0] - 0x60;
            arrowPos[1] = magicScrollDownPos_80082A00[1] + origin[1] - 0x36;
        }
        else
        {
            arrowPos[0] = magicScrollDownPos_80082A00[0];
            arrowPos[1] = magicScrollDownPos_80082A00[1];
        }
        DrawScrollArrow_8002C6DC((short*)arrowPos, 1, menu->ot_6);
    }
}

