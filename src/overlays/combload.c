// COMBLOAD.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "combload.h"

typedef struct CombLoadTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombLoadTask;

typedef struct CombLoadBox
{
    short col_0;
    char state_2;
    char frame_3;
} CombLoadBox;

extern int IsCardReady_800BAE24(int);
extern void DrawCardSlotMenu_800BB4A8(int);
extern void UpdateMenuCursor_8003D794(void*, int);
extern int IsConfirmPressedP1_8003D380(int);
extern void DrawMenuWindows_8002A5A4(void*);
extern void DrawTitleWindow_800A4364();
extern void DrawTitleWindow2_800A4420();
extern void DrawDataHeaderWindows_800A44DC();
extern int curPad_800A3A94;
extern unsigned short uiColor_8008B590;
extern void CombLoadWaitOverlay_800A4140();
extern void CombLoadWaitMenu_800A41A8();
extern void CombatNextStage_800A16FC();
extern void CopySaveMinionsToRoster_800A1988();
extern void LoadMenuInit_800B7674(int, int);
extern int IsLoadMenuActive_800B793C();
extern int GetLoadMenuLoaded_800B7914();
extern void DrawMenuBackground_8002BE10();
extern void DrawWindow_80042460(void* rect, void* box, void* ot, unsigned int a3);

int dword_800A4088 SDATA = 20;
const char aCheckingMEMORYC_800A408C[] = "\202b\202\210\202\205\202\203\202\213\202\211\202\216\202\207\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201D\201D\201D"; // Checking MEMORY CARD...
const char aSelectMEMORYCAR_800A40BC[] = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201D"; // Select MEMORY CARD.
const char aSelectData_800A40E4[] = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202\204\202\201\202\224\202\201"; // Select data

// Versus mode data load: loads the LOAD overlay, runs its menu (mode 2/3) and returns to the versus task
void CombLoadStart_800A40FC(CombLoadTask* task)
{
    loadOvlRequest_800A47F4 = LoadOverlay_80020BF8(1, 0x10);
    DrawMenuBackground_8002BE10();
    task->next_8 = CombLoadWaitOverlay_800A4140;
}

void CombLoadWaitOverlay_800A4140(CombLoadTask* task)
{
    if (GetFileRequestStatus_8003BE30(loadOvlRequest_800A47F4) == 0)
    {
        LoadMenuInit_800B7674(curPad_800A3A94 == 0 ? 2 : 3, 0);
        task->next_8 = CombLoadWaitMenu_800A41A8;
    }
    DrawMenuBackground_8002BE10();
}

void CombLoadWaitMenu_800A41A8(CombLoadTask* task)
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
void CardSelectScreen_800A41FC(CombLoadTask* task)
{
    char* str;
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
        str = aCheckingMEMORYC_800A408C;
    }
    else if (cardSelectState_800A47F0 == 0)
    {
        str = aSelectMEMORYCAR_800A40BC;
    }
    else if (cardSelectState_800A47F0 == 1)
    {
        str = aSelectData_800A40E4;
    }
    DrawSmallTextBox_8002AF58((int)&str, (int)code, 0xF);
    switch (cardSelectState_800A47F0)
    {
    case 0:
        DrawTitleWindow_800A4364();
        if (!busy)
        {
            DrawCardSlotMenu_800BB4A8(cardSlotCursor_800A468C[0].index_8);
            UpdateMenuCursor_8003D794(&cardSlotCursor_800A468C[0], 0);
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
        dataMenuWin_800A47D4.cursor_C = dataCursor_800A4698.index_8;
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
    CombLoadBox box;
    int x = 0x78;
    SPRT* sprt = &uiTiySprts_8008D620[15];
    sprt->x0 = x;
    sprt->y0 = 0x14;
    AddPrimCopy_80040298(pOT_8008D454 + 10, sprt, 5);
    AddPrimCopy_80040298(pOT_8008D454 + 10, &uiTiyTPages_8008D3F4[15], 2);
    rect.x = 0x78;
    rect.w = 0x7E;
    rect.h = 0x12;
    box.frame_3 = 1;
    box.col_0 = uiColor_8008B590;
    rect.y = 0x14;
    box.state_2 = 0;
    DrawWindow_80042460(&rect, &box, pOT_8008D454 + 10, 0);
}

// Matched
void DrawTitleWindow2_800A4420()
{
    RECT rect;
    CombLoadBox box;
    int x = 0x78;
    SPRT* sprt = &uiTiySprts_8008D620[15];
    sprt->x0 = x;
    sprt->y0 = 0x14;
    AddPrimCopy_80040298(pOT_8008D454 + 10, sprt, 5);
    AddPrimCopy_80040298(pOT_8008D454 + 10, &uiTiyTPages_8008D3F4[15], 2);
    rect.x = 0x78;
    rect.w = 0x7E;
    rect.h = 0x12;
    box.frame_3 = 1;
    box.col_0 = uiColor_8008B590;
    rect.y = 0x14;
    box.state_2 = 0;
    DrawWindow_80042460(&rect, &box, pOT_8008D454 + 10, 0);
}

// (the three sprite blocks look like an expanded macro: { int x = X; SPRT* sprt = &uiTiySprts_8008D620[idx]; ... })
// Matched
void DrawDataHeaderWindows_800A44DC()
{
    short rect[4];
    CombLoadBox box;
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
    box.frame_3 = 1;
    rect[0] = 0x64;
    box.col_0 = uiColor_8008B590;
    box.state_2 = 0;
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

CombLoadCursor cardSlotCursor_800A468C[1] = { { 0x10002, 0x10002 } };
CombLoadCursor dataCursor_800A4698 = { 0x50001, 0x40000F };
int dataRow0_800A46A4[14] = {
    8, 0, 0, 0, 0x380064, 0x100078, 0x20002, 1,
    0, 0, 0, -1, -1, -1,
};
int dataRow1_800A46DC[14] = {
    8, 0, 0, 0, 0x490064, 0x100078, 0x20002, 1,
    0, 0, 0, -1, -1, -1,
};
int dataRow2_800A4714[14] = {
    8, 0, 0, 0, 0x5A0064, 0x100078, 0x20002, 1,
    0, 0, 0, -1, -1, -1,
};
int dataRow3_800A474C[14] = {
    8, 0, 0, 0, 0x6B0064, 0x100078, 0x20002, 1,
    0, 0, 0, -1, -1, -1,
};
int dataRow4_800A4784[14] = {
    8, 0, 0, 0, 0x7C0064, 0x100078, 0x20002, 1,
    0, 0, 0, -1, -1, -1,
};
void *dataRows_800A47BC[6] = { (void *)dataRow0_800A46A4, (void *)dataRow1_800A46DC, (void *)dataRow2_800A4714, (void *)dataRow3_800A474C, (void *)dataRow4_800A4784 };
CombLoadDlg dataMenuWin_800A47D4 = { 2, 0, 8 };
void *dataMenuWinItems_800A47E4[3] = { (void *)dataRows_800A47BC };
int cardSelectState_800A47F0 = 0;
int loadOvlRequest_800A47F4 = 0;
