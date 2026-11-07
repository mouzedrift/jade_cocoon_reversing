#include "common.h"
#include "funcs.h"
#include "sdk.h"
#include "globals.h"
#include <libspu.h>
#include "sound.h"
#include "data_decls.h"
#include "menu_draw.h"
#include "menu_window.h"
#include "effect_data.h"
#include "main.h"
#include "pad_text.h"
#include "font.h"
#include "util.h"
#include "unit_query.h"
#include "event.h"
#include "movie.h"
#include "ui_sprites.h"
#include "party_window.h"

const char aQuit_8007415C[] = "\202p\202\225\202\211\202\224"; // Quit
const char aSelect_80074168[] = "\202r\202\205\202\214\202\205\202\203\202\224"; // Select
const char aDescription_80074178[] = "\202c\202\205\202\223\202\203\202\222\202\211\202\220\202\224\202\211\202\217\202\216"; // Description
const char aYes_80074190[] = "\202x\202\205\202\223"; // Yes
const char aNo_80074198[] = "\202m\202\217"; // No
const int unused_800741A0 = 0;


void InitReverbTask_8002A1BC(int* task)
{
    reverbAttr_80091CC8.mask = 0;
    SetReverbMode_8002A280(&reverbAttr_80091CC8, 0);
    SetReverbDepth_8002A2A0(&reverbAttr_80091CC8, 0x42, 0x42);
    task[2] = (int)UpdateReverb_8002A218;
}
void UpdateReverb_8002A218(void)
{
    if (reverbAttr_80091CC8.mask != 0)
    {
        SpuSetReverbModeParam(&reverbAttr_80091CC8);
        if (reverbAttr_80091CC8.mask & 1)
        {
            SetReverbDepth_8002A2A0(&reverbAttr_80091CC8, 0x42, 0x42);
            SpuSetReverbDepth(&reverbAttr_80091CC8);
        }
        reverbAttr_80091CC8.mask = 0;
    }
}
void SetReverbMode_8002A280(SpuReverbAttr* attr, short mode)
{
    attr->mask |= 1;
    attr->mode = (short)(mode | 0x100);
}
void SetReverbDepth_8002A2A0(SpuReverbAttr* attr, short left, short right)
{
    SetReverbDepthLeft_8002A2E8(attr, left);
    SetReverbDepthRight_8002A2FC(attr, right);
}
void SetReverbDepthLeft_8002A2E8(SpuReverbAttr* attr, short depth)
{
    attr->mask |= 2;
    attr->depth.left = depth;
}
void SetReverbDepthRight_8002A2FC(SpuReverbAttr* attr, short depth)
{
    attr->mask |= 4;
    attr->depth.right = depth;
}
void DrawTextList_8002A310(TextListEntry* entries, int ot)
{
    unsigned short loc[2];
    int i;
    if (entries)
    {
        for (i = 0; entries[i].text_4; i++)
        {
            loc[0] = entries[i].x;
            loc[1] = entries[i].y;
            DrawText_8003E91C(2, entries[i].text_4, loc, ot);
        }
    }
}
void DrawUiWindow_8002A384(UiWindowDesc* desc)
{
    WindowStyle style;
    unsigned char colorSet = desc->colorSet_8;
    short col = saveData_8008B570.uiColor_20.s;
    style.semiTrans_3 = 1;
    style.colorSet_2 = colorSet;
    style.color_0 = col;
    DrawWindow_80042460(desc->rect_0, &style, &pOT_8008D454[desc->ot_A], desc->time_4);
}
typedef struct
{
    int field_0;
    int field_4;
    int element_8;
} MagicDataInt;
short GetMagicElementIcon_8002A3E0(int magic)
{
    if (magic < 30)
    {
        return (short)elementIcons_800827BC[((MagicDataInt*)magicData_8007C438)[magic].element_8];
    }
    return 36;
}
extern void GetPortraitSprt_800A61CC(int a, void* b, void* c);
void DrawPortrait_8002A42C(unsigned short* pos, short id, RECT* drawArea, short ot)
{
    SPRT buf1;
    DR_TPAGE buf2;
    GetPortraitSprt_800A61CC(id, &buf1, &buf2);
    buf1.x0 = pos[0];
    buf1.y0 = pos[1];
    AddPrimCopy_80040298(pOT_8008D454 + ot, &buf1, sizeof(buf1) / 4);
    AddPrimCopy_80040298(pOT_8008D454 + ot, &buf2, sizeof(buf2) / 4);
    if (drawArea)
    {
        AddDrawAreaPrim_8003326C(drawArea, &pOT_8008D454[ot]);
    }
}
void DrawPortraitWindow_8002A4E4(short ot)
{
    SPRT buf1;
    DR_TPAGE buf2;
    DrawWindowBorder_80042B38(portraitWindowRect_800827E4, ot);
    GetPortraitSprt_800A61CC(1, &buf1, &buf2);
    buf1.x0 = portraitWindowPos_800827EC[0];
    buf1.y0 = portraitWindowPos_800827EC[1];
    AddPrimCopy_80040298(pOT_8008D454 + ot, &buf1, sizeof(buf1) / 4);
    AddPrimCopy_80040298(pOT_8008D454 + ot, &buf2, sizeof(buf2) / 4);
    DrawWindowBackground_800429F8(portraitWindowRect_800827E4, ot);
}

void DrawMenuWindows_8002A5A4(MenuWindowList* list)
{
    RECT rect;
    int i;
    int j;
    for (i = 0; list->items_10[i]; i++)
    {
        for (j = 0; !(list->items_10[i][j].flags_0 & 1); j++)
        {
            InterpolateWindowRect_8004196C(&rect, &list->items_10[i][j].x_10, list->open_8, 8, 0);
            AddClipDrawAreaPrim_80033308(pOT_8008D454 + list->ot_14);
            DrawMenuWindowContents_8002A710(&list->items_10[i][j], list->ot_14);
            AddDrawAreaPrim_8003326C(&rect, pOT_8008D454 + list->ot_14);
            DrawMenuItemWindow_8002AAF0(list, i, j, &rect);
        }
    }
    SetFontClutOffset_8003F900(2, 0);
    SetFontClutOffset_8003F900(1, 0);
}
typedef struct
{
    unsigned short x;
    unsigned short y;
} Pt;
extern void AlignMenuItem_8002AC88(int flags, unsigned short* a, short b, unsigned short* out);
void DrawMenuWindowContents_8002A710(void* item, int ot)
{
    MenuWindowItem* desc = item;
    unsigned char col[8];
    unsigned short rect[4];
    unsigned short loc[2];
    int mode;
    if (desc->flags_0 & 0x40)
    {
        return;
    }
    if (desc->type_2 == 0)
    {
        return;
    }
    rect[0] = desc->x_10 + desc->mx_18;
    rect[1] = desc->y_12 + desc->my_1A;
    rect[2] = desc->w_14 - desc->mx_18 * 2;
    rect[3] = desc->h_16 - desc->my_1A * 2;
    switch (desc->type_2)
    {
    case 1:
        if ((unsigned int)desc->text_4.num < 0xFFFFFFFF)
        {
            GetMenuItemColor_8002ACE8(desc->flags_0, col);
            AlignMenuItem_8002AC88(desc->flags_0, rect, (*desc->sprts_8)[desc->text_4.num].w, loc);
            {
                DR_TPAGE** fc = desc->tpages_C;
                mode = desc->text_4.num;
                AddSprtWithTPage_800331C4(loc, *desc->sprts_8 + mode, *fc + mode, pOT_8008D454 + ot, col);
            }
        }
        break;
    case 2:
        SetMenuItemFont1Clut_8002AD08(desc->flags_0);
        AlignMenuItem_8002AC88(desc->flags_0, rect, MeasureTextWidthFont1_8003E6B0(desc->text_4.str), loc);
        mode = 1;
        loc[1] += 2;
        DrawText_8003E91C(mode, desc->text_4.str, loc, ot);
        break;
    case 3:
        SetMenuItemFont2Clut_8002AD44(desc->flags_0);
        AlignMenuItem_8002AC88(desc->flags_0, rect, MeasureTextWidth_8003E4C8(desc->text_4.str), loc);
        mode = 2;
        loc[1] += 2;
        DrawText_8003E91C(mode, desc->text_4.str, loc, ot);
        break;
    case 4:
        SetMenuItemFont1Clut_8002AD08(desc->flags_0);
        loc[0] = rect[0];
        loc[1] = rect[1];
        if (desc->flags_0 & 4)
        {
            DrawSmallText_8002FAA0(1, loc, (unsigned char*)desc->text_4.str, ot);
        }
        else if (desc->flags_0 & 8)
        {
            loc[0] += (short)rect[2] / 2;
            DrawSmallText_8002FAA0(2, loc, (unsigned char*)desc->text_4.str, ot);
        }
        else
        {
            DrawSmallText_8002FAA0(0, loc, (unsigned char*)desc->text_4.str, ot);
        }
        break;
    case 5:
        SetMenuItemFont2Clut_8002AD44(desc->flags_0);
        loc[0] = rect[0];
        loc[1] = rect[1];
        if (desc->flags_0 & 4)
        {
            DrawLargeText_8002FBD8(1, loc, (unsigned char*)desc->text_4.str, ot);
        }
        else if (desc->flags_0 & 8)
        {
            loc[0] += (short)rect[2] / 2;
            DrawLargeText_8002FBD8(2, loc, (unsigned char*)desc->text_4.str, ot);
        }
        else
        {
            DrawLargeText_8002FBD8(0, loc, (unsigned char*)desc->text_4.str, ot);
        }
        break;
    case 6:
        SetMenuItemFont1Clut_8002AD08(desc->flags_0);
        loc[0] = rect[0] + rect[2];
        loc[1] = rect[1];
        DrawNumberRightAlignedFont1_8003F264(loc, desc->text_4.num, ot);
        break;
    case 7:
        SetMenuItemFont2Clut_8002AD44(desc->flags_0);
        loc[0] = rect[0] + rect[2];
        loc[1] = rect[1];
        DrawNumberRightAligned_8003EFBC(loc, desc->text_4.num, ot);
        break;
    case 8:
        SetMenuItemDigitColor_8002AD80(desc->flags_0);
        loc[0] = rect[0] + rect[2] - 3;
        loc[1] = rect[1] + 2;
        DrawLargeNumber_8002C100(loc, desc->text_4.num, ot);
        SetLargeDigitColor_8002C5D0(0);
        break;
    }
}
