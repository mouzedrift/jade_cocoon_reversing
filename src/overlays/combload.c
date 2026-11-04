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
    char c_2;
    char c_3;
} CombLoadBox;

extern int sub_800BAE24(int);
extern void sub_800BB4A8(int);
extern void UpdateMenuCursor_8003D794(void*, int);
extern int IsConfirmPressedP1_8003D380(int);
extern void DrawMenuWindows_8002A5A4(void*);
extern void DrawTitleWindow_800A4364();
extern void DrawTitleWindow2_800A4420();
extern void DrawDataHeaderWindows_800A44DC();
extern int dword_800A3A94;
extern unsigned short uiColor_8008B590;
extern void CombLoadWaitOverlay_800A4140();
extern void CombLoadWaitMenu_800A41A8();
extern void sub_800A16FC();
extern void sub_800A1988();
extern void LoadMenuInit_800B7674(int, int);
extern int IsLoadMenuActive_800B793C();
extern int sub_800B7914();
extern void DrawMenuBackground_8002BE10();
extern void DrawWindow_80042460(void* a0, void* a1, void* a2, unsigned int a3);

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
        LoadMenuInit_800B7674(dword_800A3A94 == 0 ? 2 : 3, 0);
        task->next_8 = CombLoadWaitMenu_800A41A8;
    }
    DrawMenuBackground_8002BE10();
}

void CombLoadWaitMenu_800A41A8(CombLoadTask* task)
{
    if (IsLoadMenuActive_800B793C() == 0)
    {
        if (sub_800B7914() == 1)
        {
            sub_800A1988();
        }
        task->next_8 = sub_800A16FC;
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
        if (sub_800BAE24(i) == 0)
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
            sub_800BB4A8(cardSlotCursor_800A468C[0].f8);
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
        dataMenuWin_800A47D4.f4 = GetTime30Hz_8002C64C();
        dataMenuWin_800A47D4.fC = dataCursor_800A4698.f8;
        DrawMenuWindows_8002A5A4(&dataMenuWin_800A47D4);
        UpdateMenuCursor_8003D794(&dataCursor_800A4698, 0);
        break;
    }
    DrawMenuBackground_8002BE10();
}

// Near miss: the compiler shares the constant 0x78 between the two stores
#if 0
void DrawTitleWindow_800A4364()
{
    RECT r;
    CombLoadBox b;
    SPRT* p = &uiTiySprts_8008D620[15];
    p->x0 = 0x78;
    p->y0 = 0x14;
    AddPrimCopy_80040298(pOT_8008D454 + 10, p, 5);
    AddPrimCopy_80040298(pOT_8008D454 + 10, &uiTiyTPages_8008D3F4[15], 2);
    r.x = 0x78;
    r.w = 0x7E;
    r.h = 0x12;
    b.c_3 = 1;
    b.col_0 = uiColor_8008B590;
    r.y = 0x14;
    b.c_2 = 0;
    DrawWindow_80042460(&r, &b, pOT_8008D454 + 10, 0);
}
#endif
INCLUDE_OVERLAY_ASM(combload, DrawTitleWindow_800A4364);

INCLUDE_OVERLAY_ASM(combload, DrawTitleWindow2_800A4420);

// Near miss: pointer register allocation for UI sprite 155
#if 0
void DrawDataHeaderWindows_800A44DC()
{
    short rect[4];
    CombLoadBox b;
    SPRT* p;
    SPRT* base;
    base = uiTiySprts_8008D620;
    p = &base[155];
    p->x0 = 0x66;
    p->y0 = 0x2A;
    AddPrimCopy_80040298(pOT_8008D454 + 10, p, 5);
    AddPrimCopy_80040298(pOT_8008D454 + 10, &uiTiyTPages_8008D3F4[155], 2);
    base = uiTiySprts_8008D620;
    p = &base[155];
    p->x0 = 0x8E;
    p->y0 = 0x2A;
    AddPrimCopy_80040298(pOT_8008D454 + 10, p, 5);
    AddPrimCopy_80040298(pOT_8008D454 + 10, &uiTiyTPages_8008D3F4[155], 2);
    base = uiTiySprts_8008D620;
    p = &base[155];
    p->x0 = 0xD4;
    p->y0 = 0x2A;
    AddPrimCopy_80040298(pOT_8008D454 + 10, p, 5);
    AddPrimCopy_80040298(pOT_8008D454 + 10, &uiTiyTPages_8008D3F4[155], 2);
    b.c_3 = 1;
    rect[0] = 0x64;
    b.col_0 = uiColor_8008B590;
    b.c_2 = 0;
    rect[1] = 0x28;
    rect[2] = 0x20;
    rect[3] = 0x10;
    DrawWindow_80042460(rect, &b, pOT_8008D454 + 10, 0);
    rect[0] = 0x8C;
    rect[1] = 0x28;
    rect[2] = 0x3C;
    rect[3] = 0x10;
    DrawWindow_80042460(rect, &b, pOT_8008D454 + 10, 0);
    rect[0] = 0xD2;
    rect[1] = 0x28;
    rect[2] = 0x20;
    rect[3] = 0x10;
    DrawWindow_80042460(rect, &b, pOT_8008D454 + 10, 0);
}
#endif
INCLUDE_OVERLAY_ASM(combload, DrawDataHeaderWindows_800A44DC);

CombLoadObj cardSlotCursor_800A468C[1] = { { 0x10002, 0x10002 } };
CombLoadObj dataCursor_800A4698 = { 0x50001, 0x40000F };
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
