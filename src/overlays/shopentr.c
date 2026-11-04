// SHOPENTR.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"
#include "shopentr.h"

int dword_800B6D00 SDATA = 40;
const char aSaved_800B6D04[] = "\203Z\201[\203u\202\265\202\334\202\265\202\275"; // セーブしました
const char aSaving_800B6D14[] = "\203Z\201[\203u\202\265\202\304\202\242\202\351"; // セーブしている
const char aNoSpace_800B6D24[] = "\213\363\202\253\202\252\226\263\202\242"; // 空きが無い
const char aSaveNew_800B6D30[] = "\220V\202\265\202\255\203Z\201[\203u\202\265\202\334\202\267\202\251\201H"; // 新しくセーブしますか？
const char aOverwrite_800B6D48[] = "\217\343\217\221\202\253\202\265\202\334\202\267\202\251\201H"; // 上書きしますか？
const char aOverwriting_800B6D5C[] = "\217\343\217\221\202\253\202\265\202\304\202\242\202\351"; // 上書きしている
const char aFormatting_800B6D6C[] = "\203t\203H\201[\203}\203b\203g\202\265\202\304\202\242\202\351"; // フォーマットしている
const char aFormatOrNot_800B6D84[] = "\203t\203H\201[\203}\203b\203g\202\267\202\351\202\265\202\310\202\242\201H"; // フォーマットするしない？
const char aUnformatted_800B6DA0[] = "\203A\203\223\203t\203H\201[\203}\203b\203g\202\276"; // アンフォーマットだ
const char aNoDataSpace_800B6DB4[] = "\203f\201[\203^\202\314\213\363\202\253\202\252\202\310\202\251\202\301\202\275"; // データの空きがなかった
const char aDataSpaceMinion_800B6DCC[] = "\203f\201[\203^\201i\202\314\213\363\202\253\201j\202\252\202\240\202\301\202\275\226\202\225\250"; // データ（の空き）があった魔物
const char aDataSpaceBlock_800B6DEC[] = "\203f\201[\203^\201i\202\314\213\363\202\253\201j\202\252\202\240\202\301\202\275\203u\203\215\203b\203N"; // データ（の空き）があったブロック
const char aCardCheck2_800B6E10[] = "\203J\201[\203h\203`\203F\203b\203N\202Q"; // カードチェック２
const char aSlotSelect_800B6E24[] = "\203X\203\215\203b\203g\221I\221\360\201H"; // スロット選択？
const char aCardCheck1_800B6E34[] = "\203J\201[\203h\203`\203F\203b\203N\202P"; // カードチェック１
const int dword_800B6E48 = 0;

int IsShelfMenuActive_800B6F0C(void)
{
    return shelfMenuActive_800B7EAC;
}

// starts the cocoon shelf menu (memory card check, slot and shelf selection, registered minion list); when it
// reaches state 15 it hands back to the shop (ShopCtrlRequestShop_800B6CA0)
// Matched
void StartShelfMenu_800B6F1C(void)
{
    EventEntry* task;
    ShelfMenu* menu;
    task = AllocEventEntry_80043AF8(shelfMenuTask_8008D4A8);
    if (task)
    {
        task->flags = (task->flags | 1) & 0xFFFF7FFF;
        menu = task->buffer;
        menu->state_14 = 4;
        menu->flags_C = 0;
        menu->pages_10 = 0;
        menu->progress_16 = 0;
        menu->pages_10 = 0;
        menu->pages_10 = shelfStatePages_800B7E34[menu->state_14];
        SetShelfMenuCursorRect_800B7520(menu);
        menu->cursor_8 = 0;
        menu->scroll_A = 0;
        if (menu->state_14 < 15 && shelfMenuStates_800B7D08[menu->state_14].timed_10)
        {
            menu->flags_C |= 1;
        }
        shelfMenuActive_800B7EAC = 1;
        DrawMenuBackground_8002BE10();
    }
}

// Matched
void ShelfMenuTask_800B7000(EventEntry* task, ShelfMenu* menu)
{
    int rejected;
    DrawMenuBackground_8002BE10();
    DrawShelfMenu_800B7440(menu);
    rejected = 0;
    if (!(menu->flags_C & 1))
    {
        UpdateMenuCursor_8003D794(menu, rejected);
    }
    if (IsConfirmPressedP1_8003D380(0))
    {
        if (!(menu->flags_C & 1))
        {
            PlaySfx_80031494(0x7e);
            ShelfMenuConfirm_800B7144(menu);
        }
        else
        {
            rejected = 1;
        }
    }
    else if (IsCancelPressedP1_8003D41C(0))
    {
        if (!(menu->flags_C & 1))
        {
            ShelfMenuCancel_800B72D4(menu);
        }
        else
        {
            rejected = 1;
        }
    }
    if (rejected)
    {
        PlaySfx_80031494(0x7c);
    }
    if (menu->flags_C & 1)
    {
        if (ShelfMenuProgress_800B73A8(menu))
        {
            PlaySfx_80031494(0x7e);
            ShelfMenuConfirm_800B7144(menu);
        }
    }
    if (menu->state_14 == 15)
    {
        shelfMenuActive_800B7EAC = 0;
        task->flags = (task->flags & ~1) | 0x8000;
        ShopCtrlRequestShop_800B6CA0();
    }
}

void ShelfMenuConfirm_800B7144(ShelfMenu* menu)
{
    if (shelfMenuStates_800B7D08[menu->state_14].confirmNext_0 == -1)
    {
        switch (menu->state_14)
        {
        case 2:
            if (padHeld_800918D0[0] & 0x40)
            {
                menu->state_14 = 5;
            }
            else if (padHeld_800918D0[0] & 4)
            {
                menu->state_14 = 6;
            }
            else
            {
                menu->state_14 = 3;
            }
            break;
        case 4:
            if (menu->cursor_8 & 1)
            {
                menu->state_14 = 0xb;
            }
            else
            {
                menu->state_14 = 0xa;
            }
            break;
        case 7:
            if (menu->cursor_8)
            {
                menu->state_14 = 1;
            }
            else
            {
                menu->state_14 = 8;
            }
            break;
        case 10:
            if (menu->cursor_8)
            {
                menu->state_14 = 3;
            }
            else
            {
                menu->state_14 = 9;
            }
            break;
        case 11:
            if (!menu->cursor_8)
            {
                menu->state_14 = 0xd;
            }
            else
            {
                menu->state_14 = 3;
            }
            break;
        }
    }
    else
    {
        menu->state_14 = shelfMenuStates_800B7D08[menu->state_14].confirmNext_0;
    }
    menu->pages_10 = 0;
    menu->pages_10 = shelfStatePages_800B7E34[menu->state_14];
    SetShelfMenuCursorRect_800B7520(menu);
    if (menu->state_14 < 15 && shelfMenuStates_800B7D08[menu->state_14].timed_10)
    {
        menu->flags_C |= 1;
    }
}
const char aCardChecking_800B6E74[] = "\203\201\203\202\203\212\201[\203J\201[\203h\201@\203`\203F\203b\203N\222\206"; // メモリーカード　チェック中
const char aCardSelect_800B6E90[] = "\203\201\203\202\203\212\201[\203J\201[\203h\221I\221\360"; // メモリーカード選択
const char aSlot1_800B6EA4[] = "\203X\203\215\203b\203g\202P"; // スロット１
const char aSlot2_800B6EB0[] = "\203X\203\215\203b\203g\202Q"; // スロット２
const char aShelfSelect_800B6EBC[] = "\226\232\222I\221I\221\360"; // 繭棚選択
const char aShelf_800B6EC8[] = "\226\232\222I"; // 繭棚
const char aMinionCount_800B6ED0[] = "\202\265\202\340\202\327\220\224"; // しもべ数
const char aTime_800B6EDC[] = "\216\236\212\324"; // 時間
const char aRegistered_800B6EE4[] = "\223o\230^"; // 登録
const char aName_800B6EEC[] = "\226\274\221O"; // 名前
const char aRank_800B6EF4[] = "\212K\213\211"; // 階級
const char aElement_800B6EFC[] = "\221\256\220\253"; // 属性
const char aSlash_800B6F04[] = "\201^"; // /
const char aColon_800B6F08[] = "\201F"; // :

// Matched
void ShelfMenuCancel_800B72D4(ShelfMenu* menu)
{
    int snd;
    if (shelfMenuStates_800B7D08[menu->state_14].cancelNext_2 != -2)
    {
        menu->state_14 = shelfMenuStates_800B7D08[menu->state_14].cancelNext_2;
        snd = 0x7d;
    }
    else
    {
        snd = 0x7c;
    }
    PlaySfx_80031494(snd);
    menu->pages_10 = 0;
    menu->pages_10 = shelfStatePages_800B7E34[menu->state_14];
    SetShelfMenuCursorRect_800B7520(menu);
    if (menu->state_14 < 15 && shelfMenuStates_800B7D08[menu->state_14].timed_10)
    {
        menu->flags_C |= 1;
    }
}

// what DrawGauge_8002BA54 takes (struct_BA54 in ui_gauge.c)
typedef struct ShelfGauge
{
    int state_0;
    int f4;
    int value_8;
    int max_C;
} ShelfGauge;
// Matched
int ShelfMenuProgress_800B73A8(ShelfMenu* menu)
{
    short pos[2];
    ShelfGauge gauge;
    gauge.state_0 = 2;
    gauge.f4 = 0;
    gauge.value_8 = menu->progress_16;
    gauge.max_C = 0x3c;
    pos[0] = 0x8c;
    pos[1] = 0xa0;
    DrawGauge_8002BA54(&gauge, 0, pos, 14);
    if (menu->progress_16 < 0x3c)
    {
        menu->progress_16++;
        return 0;
    }
    menu->progress_16 = 0;
    menu->flags_C &= ~1;
    return 1;
}

// Matched
void DrawShelfMenu_800B7440(ShelfMenu* menu)
{
    short i;
    for (i = 0; i < 4; i++)
    {
        if (menu->pages_10 & (1 << i))
        {
            switch (i)
            {
            case 0:
                DrawCardCheckPage_800B7594(menu);
                break;
            case 1:
                DrawCardSelectPage_800B75DC(menu);
                break;
            case 2:
                DrawShelfSelectPage_800B7684(menu);
                break;
            case 3:
                DrawShelfContentsPage_800B7858(menu);
                break;
            }
        }
    }
}

// Matched
void SetShelfMenuCursorRect_800B7520(ShelfMenu* menu)
{
    ShelfRect* rect;
    if (menu->state_14 < 15)
    {
        rect = &shelfCursorRects_800B7CE8[shelfMenuStates_800B7D08[menu->state_14].cursorRect_4];
        menu->cursorRect_0[0] = rect->x;
        menu->cursorRect_0[1] = rect->y;
        menu->cursorRect_0[2] = rect->w;
        menu->cursorRect_0[3] = rect->h;
    }
}

// Matched
void DrawCardCheckPage_800B7594(ShelfMenu* menu)
{
    unsigned short pos[2];
    pos[0] = cardCheckTextPos_800B7CC8[0];
    pos[1] = cardCheckTextPos_800B7CC8[1];
    DrawText_8003E91C(2, aCardChecking_800B6E74, pos, 14);
}

// Matched
void DrawCardSelectPage_800B75DC(ShelfMenu* menu)
{
    unsigned short titlePos[2];
    unsigned short slot1Pos[2];
    unsigned short slot2Pos[2];
    titlePos[0] = cardSelectTitlePos_800B7CD0[0];
    titlePos[1] = cardSelectTitlePos_800B7CD0[1];
    DrawText_8003E91C(2, aCardSelect_800B6E90, titlePos, 14);
    slot1Pos[0] = slot1TextPos_800B7CD8[0];
    slot1Pos[1] = slot1TextPos_800B7CD8[1];
    DrawText_8003E91C(2, aSlot1_800B6EA4, slot1Pos, 14);
    slot2Pos[0] = slot2TextPos_800B7CE0[0];
    slot2Pos[1] = slot2TextPos_800B7CE0[1];
    DrawText_8003E91C(2, aSlot2_800B6EB0, slot2Pos, 14);
}

// Matched
void DrawShelfSelectPage_800B7684(ShelfMenu* menu)
{
    ShelfRect row;
    unsigned short pos[2];
    unsigned short numPos[2];
    unsigned short titlePos[2];
    unsigned short shelfHdrPos[2];
    unsigned short countHdrPos[2];
    unsigned short timeHdrPos[2];
    short i;
    int ot = 14;
    row.x = 0x50;
    row.w = 0xa0;
    row.h = 0x12;
    for (i = 0; i < 5; i++)
    {
        row.y = i * 19 + 0x50;
        numPos[1] = row.y;
        numPos[0] = row.x;
        DrawNumber_8003EF74(numPos, menu->scroll_A + i + 1, ot);
        pos[0] = 0x82;
        pos[1] = row.y;
        DrawNumberPair_800B7B64((ShelfRect*)pos, 0x14, 0x19);
        pos[0] = 0xc8;
        pos[1] = row.y + 4;
        DrawZeroTime_800B7C08((ShelfRect*)pos);
    }
    titlePos[0] = 0x82;
    titlePos[1] = 0x20;
    DrawText_8003E91C(2, aShelfSelect_800B6EBC, titlePos, ot);
    shelfHdrPos[0] = 0x50;
    shelfHdrPos[1] = 0x3c;
    DrawText_8003E91C(2, aShelf_800B6EC8, shelfHdrPos, ot);
    countHdrPos[0] = 0x82;
    countHdrPos[1] = 0x3c;
    DrawText_8003E91C(2, aMinionCount_800B6ED0, countHdrPos, ot);
    timeHdrPos[0] = 0xd2;
    timeHdrPos[1] = 0x3c;
    DrawText_8003E91C(2, aTime_800B6EDC, timeHdrPos, ot);
    pos[0] = 0x20;
    pos[1] = 0x50;
    DrawPageCount_800B7A90((ShelfRect*)pos, menu->cursor_8 + menu->scroll_A + 1, 0xf);
}

// Matched
void DrawShelfContentsPage_800B7858(ShelfMenu* menu)
{
    ShelfRect row;
    unsigned short pos[2];
    unsigned short numPos[2];
    unsigned short titlePos[2];
    unsigned short nameHdrPos[2];
    unsigned short rankHdrPos[2];
    unsigned short elementHdrPos[2];
    Minion* minion;
    char* name;
    int level;
    short elements;
    short i;
    short ot = 14;
    row.x = 0x50;
    row.w = 0xa0;
    row.h = 0x12;
    i = 0;
    while (i < 5)
    {
        minion = GetShopMinion_800B9C5C(i + menu->scroll_A);
        if (minion && minion->id != 4)
        {
            name = minion->status_84.name_10;
            level = minion->status_84.level_44;
            elements = minion->status_84.elementMask_42;
        }
        else
        {
            name = 0;
            level = 0;
            elements = 0;
        }
        row.y = i * 19 + 0x50;
        pos[1] = row.y + 4;
        pos[0] = row.x + 3;
        if (name)
        {
            DrawSmallText_8002FAA0(0, pos, name, ot);
        }
        pos[0] = 0xa2;
        pos[1] = row.y + 4;
        if (level)
        {
            numPos[0] = 0xa2;
            numPos[1] = pos[1];
            DrawNumberRightAlignedFont1_8003F264(numPos, level, ot);
        }
        pos[0] = 0xb2;
        pos[1] = row.y + 2;
        if (elements)
            DrawElementIconsRow_8002B1B0(elements, pos, ot);
        i++;
    }
    titlePos[0] = 0x8c;
    titlePos[1] = 0x20;
    DrawText_8003E91C(2, aRegistered_800B6EE4, titlePos, ot);
    nameHdrPos[0] = 0x50;
    nameHdrPos[1] = 0x3c;
    DrawText_8003E91C(2, aName_800B6EEC, nameHdrPos, ot);
    rankHdrPos[0] = 0x8c;
    rankHdrPos[1] = 0x3c;
    DrawText_8003E91C(2, aRank_800B6EF4, rankHdrPos, ot);
    elementHdrPos[0] = 0xd2;
    elementHdrPos[1] = 0x3c;
    DrawText_8003E91C(2, aElement_800B6EFC, elementHdrPos, ot);
    pos[0] = 0x20;
    pos[1] = 0x50;
    DrawPageCount_800B7A90((ShelfRect*)pos, menu->cursor_8 + menu->scroll_A + 1, 0x19);
}

// Matched
void DrawPageCount_800B7A90(ShelfRect* pos, short num, short total)
{
    ShelfRect bounds;
    unsigned short numPos[2];
    unsigned short slashPos[2];
    unsigned short totalPos[2];
    numPos[0] = pos->x + 0x12;
    numPos[1] = pos->y + 2;
    DrawNumberRightAlignedFont1_8003F264(numPos, num, 14);
    slashPos[0] = pos->x + 0x12;
    slashPos[1] = pos->y + 2;
    DrawText_8003E91C(1, aSlash_800B6F04, slashPos, 14);
    totalPos[0] = pos->x + 0x2a;
    totalPos[1] = pos->y + 2;
    DrawNumberRightAlignedFont1_8003F264(totalPos, total, 14);
    bounds.x = pos->x;
    bounds.y = pos->y;
    bounds.w = 0x2c;
    bounds.h = 0xc;
}

// Matched
void DrawNumberPair_800B7B64(ShelfRect* pos, short num, short total)
{
    unsigned short numPos[2];
    unsigned short slashPos[2];
    unsigned short totalPos[2];
    numPos[0] = pos->x;
    numPos[1] = pos->y;
    DrawNumber_8003EF74(numPos, num, 14);
    slashPos[0] = pos->x + 0x18;
    slashPos[1] = 0x3c;
    DrawText_8003E91C(2, aSlash_800B6F04, slashPos, 14);
    totalPos[0] = pos->x + 0x24;
    totalPos[1] = pos->y;
    DrawNumber_8003EF74(totalPos, total, 14);
}

// Matched
void DrawZeroTime_800B7C08(ShelfRect* pos)
{
    unsigned short hoursPos[2];
    unsigned short colonPos[2];
    unsigned short minutesPos[2];
    unsigned short minutesOnesPos[2];
    hoursPos[0] = pos->x + 0x10;
    hoursPos[1] = pos->y;
    DrawNumberRightAlignedFont1_8003F264(hoursPos, 0, 14);
    colonPos[0] = pos->x + 0x10;
    colonPos[1] = pos->y;
    DrawText_8003E91C(1, aColon_800B6F08, colonPos, 14);
    minutesPos[0] = pos->x + 0x20;
    minutesPos[1] = pos->y;
    DrawNumberRightAlignedFont1_8003F264(minutesPos, 0, 14);
    minutesOnesPos[0] = pos->x + 0x28;
    minutesOnesPos[1] = pos->y;
    DrawNumberRightAlignedFont1_8003F264(minutesOnesPos, 0, 14);
}

int dword_800B7CC0[2] = { 0xC80010, 0xC0120 };
unsigned short cardCheckTextPos_800B7CC8[2] = { 16, 120 };
int dword_800B7CCC = 0x120120;
unsigned short cardSelectTitlePos_800B7CD0[2] = { 80, 32 };
int dword_800B7CD4 = 0x1200A0;
unsigned short slot1TextPos_800B7CD8[2] = { 40, 120 };
int dword_800B7CDC = 0x12003C;
unsigned short slot2TextPos_800B7CE0[2] = { 200, 120 };
int dword_800B7CE4 = 0x12003C;
ShelfRect shelfCursorRects_800B7CE8[4] = {
    { 1, 1, 1 },
    { 2, 1, 2, 1 },
    { 1, 5, 15, 64 },
    { 1, 5, 25, 64 },
};
ShelfMenuState shelfMenuStates_800B7D08[15] = {
    { 1, -2, 0, 0, 0, 0, 1 },
    { 2, 15, 1, 0, 1 },
    { -1, -2, 0, 0, 0, 0, 1 },
    { 4, 1, 2 },
    { 15, 15, 3 },
    { 1, 1 },
    { 7, 1 },
    { -1, 1, 1, 0, 1 },
    { 2, -2, 0, 0, 0, 0, 1 },
    { 15, -2, 0, 0, 0, 0, 1 },
    { -1, 4, 1, 0, 1 },
    { -1, 4, 1, 0, 1 },
    { 3, 4 },
    { 14, -2, 0, 0, 0, 0, 1 },
    { 15, 15 },
};
unsigned int shelfStatePages_800B7E34[30] = {
    1, 2, 1, 4, 8, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (unsigned int)aCardCheck1_800B6E34,
    (unsigned int)aSlotSelect_800B6E24, (unsigned int)aCardCheck2_800B6E10, (unsigned int)aDataSpaceBlock_800B6DEC, (unsigned int)aDataSpaceMinion_800B6DCC, (unsigned int)aNoDataSpace_800B6DB4, (unsigned int)aUnformatted_800B6DA0, (unsigned int)aFormatOrNot_800B6D84, (unsigned int)aFormatting_800B6D6C,
    (unsigned int)aOverwriting_800B6D5C, (unsigned int)aOverwrite_800B6D48, (unsigned int)aSaveNew_800B6D30, (unsigned int)aNoSpace_800B6D24, (unsigned int)aSaving_800B6D14, (unsigned int)aSaved_800B6D04,
};
int shelfMenuActive_800B7EAC = 0;
