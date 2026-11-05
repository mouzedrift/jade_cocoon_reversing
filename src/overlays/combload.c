// COMBLOAD.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "combload.h"

int dword_800A4088 SDATA = 20; // first word of the overlay

MenuCursor cardSlotCursor_800A468C = { 2, 1, 2, 1, 0, 0 };
MenuCursor dataCursor_800A4698 = { 1, 5, 15, 0x40, 0, 0 };
MenuWindowItem dataRow0_800A46A4[2] = { { 8, 0, 0, NULL, NULL, 0x64, 0x38, 0x78, 0x10, 2, 2 }, { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 } };
MenuWindowItem dataRow1_800A46DC[2] = { { 8, 0, 0, NULL, NULL, 0x64, 0x49, 0x78, 0x10, 2, 2 }, { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 } };
MenuWindowItem dataRow2_800A4714[2] = { { 8, 0, 0, NULL, NULL, 0x64, 0x5A, 0x78, 0x10, 2, 2 }, { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 } };
MenuWindowItem dataRow3_800A474C[2] = { { 8, 0, 0, NULL, NULL, 0x64, 0x6B, 0x78, 0x10, 2, 2 }, { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 } };
MenuWindowItem dataRow4_800A4784[2] = { { 8, 0, 0, NULL, NULL, 0x64, 0x7C, 0x78, 0x10, 2, 2 }, { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 } };
MenuWindowItem* dataRows_800A47BC[6] = { dataRow0_800A46A4, dataRow1_800A46DC, dataRow2_800A4714, dataRow3_800A474C, dataRow4_800A4784 };
MenuWindowList dataMenuWin_800A47D4 = { 2, 0, 8, 0, dataRows_800A47BC };
static int dataMenuWinPad = 0; // unused (0x800A47EC)
int cardSelectState_800A47F0 = 0;
int loadOvlRequest_800A47F4 = 0;

// Versus mode data load: loads the LOAD overlay, runs its menu (mode 2/3) and returns to the versus task
void CombLoadStart_800A40FC(CombatTask* task)
{
    loadOvlRequest_800A47F4 = LoadOverlay_80020BF8(1, 0x10);
    DrawMenuBackground_8002BE10();
    task->next_8 = CombLoadWaitOverlay_800A4140;
}

void CombLoadWaitOverlay_800A4140(CombatTask* task)
{
    if (GetFileRequestStatus_8003BE30(loadOvlRequest_800A47F4) == 0)
    {
        LoadMenuInit_800B7674(curPad_800A3A94 == 0 ? 2 : 3, 0);
        task->next_8 = CombLoadWaitMenu_800A41A8;
    }
    DrawMenuBackground_8002BE10();
}

void CombLoadWaitMenu_800A41A8(CombatTask* task)
{
    if (IsLoadMenuActive_800B793C() == 0)
    {
        if (GetLoadMenuLoaded_800B7914() == 1)
        {
            CopySaveMinionsToRoster_800A1988();
        }
        task->next_8 = CombatNextStage_800A16FC;
    }
}

// Unreferenced memory card / data select screen (the LOAD menu replaced it)
void CardSelectScreen_800A41FC(CombatTask* task)
{
    const char* str;
    short code[4];
    int busy = 0;
    int i;
    for (i = 0; i < 2; i++)
    {
        if (IsCardReady_800BAE24(i) == 0)
        {
            busy = 1;
        }
    }
    SetFontClutOffset_8003F900(2, 0);
    code[0] = 0xC3;
    if (busy)
    {
        str = "\202b\202\210\202\205\202\203\202\213\202\211\202\216\202\207\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201D\201D\201D"; // Checking MEMORY CARD...
    }
    else if (cardSelectState_800A47F0 == 0)
    {
        str = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201D"; // Select MEMORY CARD.
    }
    else if (cardSelectState_800A47F0 == 1)
    {
        str = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202\204\202\201\202\224\202\201"; // Select data
    }
    DrawSmallTextBox_8002AF58(&str, code, 0xF);
    switch (cardSelectState_800A47F0)
    {
    case 0:
        DrawTitleWindow_800A4364();
        if (!busy)
        {
            DrawCardSlotMenu_800BB4A8(cardSlotCursor_800A468C.cursor_8);
            UpdateMenuCursor_8003D794(&cardSlotCursor_800A468C, 0);
            if (IsConfirmPressedP1_8003D380(1))
            {
                cardSelectState_800A47F0 = 1;
            }
        }
        break;
    case 1:
        DrawTitleWindow2_800A4420();
        DrawDataHeaderWindows_800A44DC();
        dataMenuWin_800A47D4.time_4 = GetTime30Hz_8002C64C();
        dataMenuWin_800A47D4.cursor_C = dataCursor_800A4698.cursor_8;
        DrawMenuWindows_8002A5A4(&dataMenuWin_800A47D4);
        UpdateMenuCursor_8003D794(&dataCursor_800A4698, 0);
        break;
    }
    DrawMenuBackground_8002BE10();
}

// Matched
void DrawTitleWindow_800A4364()
{
    RECT rect;
    WindowStyle box;
    int x = 0x78;
    SPRT* sprt = &uiTiySprts_8008D620[15];
    sprt->x0 = x;
    sprt->y0 = 0x14;
    AddPrimCopy_80040298(pOT_8008D454 + 10, sprt, 5);
    AddPrimCopy_80040298(pOT_8008D454 + 10, &uiTiyTPages_8008D3F4[15], 2);
    rect.x = 0x78;
    rect.w = 0x7E;
    rect.h = 0x12;
    box.semiTrans_3 = 1;
    box.color_0 = uiColor_8008B590;
    rect.y = 0x14;
    box.colorSet_2 = 0;
    DrawWindow_80042460(&rect, &box, pOT_8008D454 + 10, 0);
}

// Matched
void DrawTitleWindow2_800A4420()
{
    RECT rect;
    WindowStyle box;
    int x = 0x78;
    SPRT* sprt = &uiTiySprts_8008D620[15];
    sprt->x0 = x;
    sprt->y0 = 0x14;
    AddPrimCopy_80040298(pOT_8008D454 + 10, sprt, 5);
    AddPrimCopy_80040298(pOT_8008D454 + 10, &uiTiyTPages_8008D3F4[15], 2);
    rect.x = 0x78;
    rect.w = 0x7E;
    rect.h = 0x12;
    box.semiTrans_3 = 1;
    box.color_0 = uiColor_8008B590;
    rect.y = 0x14;
    box.colorSet_2 = 0;
    DrawWindow_80042460(&rect, &box, pOT_8008D454 + 10, 0);
}

// (the three sprite blocks look like an expanded macro: { int x = X; SPRT* sprt = &uiTiySprts_8008D620[idx]; ... })
// Matched
void DrawDataHeaderWindows_800A44DC()
{
    short rect[4];
    WindowStyle box;
    {
        int x = 0x66;
        SPRT* sprt = &uiTiySprts_8008D620[155];
        sprt->x0 = x;
        sprt->y0 = 0x2A;
        AddPrimCopy_80040298(pOT_8008D454 + 10, sprt, 5);
        AddPrimCopy_80040298(pOT_8008D454 + 10, &uiTiyTPages_8008D3F4[155], 2);
    }
    {
        int x = 0x8E;
        SPRT* sprt = &uiTiySprts_8008D620[155];
        sprt->x0 = x;
        sprt->y0 = 0x2A;
        AddPrimCopy_80040298(pOT_8008D454 + 10, sprt, 5);
        AddPrimCopy_80040298(pOT_8008D454 + 10, &uiTiyTPages_8008D3F4[155], 2);
    }
    {
        int x = 0xD4;
        SPRT* sprt = &uiTiySprts_8008D620[155];
        sprt->x0 = x;
        sprt->y0 = 0x2A;
        AddPrimCopy_80040298(pOT_8008D454 + 10, sprt, 5);
        AddPrimCopy_80040298(pOT_8008D454 + 10, &uiTiyTPages_8008D3F4[155], 2);
    }
    box.semiTrans_3 = 1;
    rect[0] = 0x64;
    box.color_0 = uiColor_8008B590;
    box.colorSet_2 = 0;
    rect[1] = 0x28;
    rect[2] = 0x20;
    rect[3] = 0x10;
    DrawWindow_80042460(rect, &box, pOT_8008D454 + 10, 0);
    rect[0] = 0x8C;
    rect[1] = 0x28;
    rect[2] = 0x3C;
    rect[3] = 0x10;
    DrawWindow_80042460(rect, &box, pOT_8008D454 + 10, 0);
    rect[0] = 0xD2;
    rect[1] = 0x28;
    rect[2] = 0x20;
    rect[3] = 0x10;
    DrawWindow_80042460(rect, &box, pOT_8008D454 + 10, 0);
}
