// COMBLOAD.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct CombLoadTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombLoadTask;

typedef struct CombLoadDlg
{
    int f0;
    int f4;
    int f8;
    int fC;
} CombLoadDlg;

typedef struct CombLoadObj
{
    int f0;
    int f4;
    short f8;
    short fA;
} CombLoadObj;

typedef struct CombLoadBox
{
    short col_0;
    char c_2;
    char c_3;
} CombLoadBox;

extern int dword_800A47F4;
extern int dword_800A47F0;
extern char dword_800A408C[];
extern char dword_800A40BC[];
extern char dword_800A40E4[];
extern CombLoadObj dword_800A468C[];
extern CombLoadObj dword_800A4698;
extern CombLoadDlg dword_800A47D4;
extern int sub_800BAE24(int);
extern void sub_800BB4A8(int);
extern void UpdateMenuCursor_8003D794(void*, int);
extern int IsConfirmPressedP1_8003D380(int);
extern void DrawMenuWindows_8002A5A4(void*);
extern void sub_800A4364();
extern void sub_800A4420();
extern void sub_800A44DC();
extern int dword_800A3A94;
extern unsigned short uiColor_8008B590;
extern void sub_800A4140();
extern void sub_800A41A8();
extern void sub_800A16FC();
extern void sub_800A1988();
extern void sub_800B7674(int, int);
extern int sub_800B793C();
extern int sub_800B7914();
extern void DrawMenuBackground_8002BE10();
extern void DrawWindow_80042460(void* a0, void* a1, void* a2, unsigned int a3);

INCLUDE_OVERLAY_ASM(combload, dword_800A4088);

void sub_800A40FC(CombLoadTask* t)
{
    dword_800A47F4 = LoadOverlay_80020BF8(1, 0x10);
    DrawMenuBackground_8002BE10();
    t->next_8 = sub_800A4140;
}

void sub_800A4140(CombLoadTask* t)
{
    if (GetFileRequestStatus_8003BE30(dword_800A47F4) == 0)
    {
        sub_800B7674(dword_800A3A94 == 0 ? 2 : 3, 0);
        t->next_8 = sub_800A41A8;
    }
    DrawMenuBackground_8002BE10();
}

void sub_800A41A8(CombLoadTask* t)
{
    if (sub_800B793C() == 0)
    {
        if (sub_800B7914() == 1)
        {
            sub_800A1988();
        }
        t->next_8 = sub_800A16FC;
    }
}

void sub_800A41FC(CombLoadTask* t)
{
    char* str;
    short code[4];
    int found = 0;
    int i;
    for (i = 0; i < 2; i++)
    {
        if (sub_800BAE24(i) == 0)
        {
            found = 1;
        }
    }
    SetFontClutOffset_8003F900(2, 0);
    code[0] = 0xC3;
    if (found)
    {
        str = dword_800A408C;
    }
    else if (dword_800A47F0 == 0)
    {
        str = dword_800A40BC;
    }
    else if (dword_800A47F0 == 1)
    {
        str = dword_800A40E4;
    }
    DrawSmallTextBox_8002AF58((int)&str, (int)code, 0xF);
    switch (dword_800A47F0)
    {
    case 0:
        sub_800A4364();
        if (!found)
        {
            sub_800BB4A8(dword_800A468C[0].f8);
            UpdateMenuCursor_8003D794(&dword_800A468C[0], 0);
            if (IsConfirmPressedP1_8003D380(1))
            {
                dword_800A47F0 = 1;
            }
        }
        break;
    case 1:
        sub_800A4420();
        sub_800A44DC();
        dword_800A47D4.f4 = GetTime30Hz_8002C64C();
        dword_800A47D4.fC = dword_800A4698.f8;
        DrawMenuWindows_8002A5A4(&dword_800A47D4);
        UpdateMenuCursor_8003D794(&dword_800A4698, 0);
        break;
    }
    DrawMenuBackground_8002BE10();
}

// Near miss: the compiler shares the constant 0x78 between the two stores
#if 0
void sub_800A4364()
{
    RECT r;
    CombLoadBox b;
    short* p = (short*)(uiTiySprts_8008D620 + 0x12C);
    p[4] = 0x78;
    p[5] = 0x14;
    AddPrimCopy_80040298(pOT_8008D454 + 10, p, 5);
    AddPrimCopy_80040298(pOT_8008D454 + 10, (char*)uiTiyTPages_8008D3F4 + 0x78, 2);
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
INCLUDE_OVERLAY_ASM(combload, sub_800A4364);

INCLUDE_OVERLAY_ASM(combload, sub_800A4420);

// Near miss: pointer register allocation for the 0xC1C buffer
#if 0
void sub_800A44DC()
{
    short rect[4];
    CombLoadBox b;
    short* p;
    int base;
    base = uiTiySprts_8008D620;
    p = (short*)(base + 0xC1C);
    p[4] = 0x66;
    p[5] = 0x2A;
    AddPrimCopy_80040298(pOT_8008D454 + 10, p, 5);
    AddPrimCopy_80040298(pOT_8008D454 + 10, (char*)uiTiyTPages_8008D3F4 + 0x4D8, 2);
    base = uiTiySprts_8008D620;
    p = (short*)(base + 0xC1C);
    p[4] = 0x8E;
    p[5] = 0x2A;
    AddPrimCopy_80040298(pOT_8008D454 + 10, p, 5);
    AddPrimCopy_80040298(pOT_8008D454 + 10, (char*)uiTiyTPages_8008D3F4 + 0x4D8, 2);
    base = uiTiySprts_8008D620;
    p = (short*)(base + 0xC1C);
    p[4] = 0xD4;
    p[5] = 0x2A;
    AddPrimCopy_80040298(pOT_8008D454 + 10, p, 5);
    AddPrimCopy_80040298(pOT_8008D454 + 10, (char*)uiTiyTPages_8008D3F4 + 0x4D8, 2);
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
INCLUDE_OVERLAY_ASM(combload, sub_800A44DC);

INCLUDE_OVERLAY_ASM(combload, dword_800A468C);
