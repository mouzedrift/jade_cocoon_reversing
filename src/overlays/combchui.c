// COMBCHUI.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

extern int sub_8003E4C8(int);
extern void sub_8002AC88(int, void*, int, void*);
extern void DrawText_8003E91C(int, int, void*, int);

INCLUDE_OVERLAY_ASM(combchui, dword_800A4088);

typedef struct CombChuiTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombChuiTask;

typedef struct CombChuiMenu
{
    char pad_0[8];
    short sel_8;
} CombChuiMenu;

typedef struct CombChuiWin
{
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
} CombChuiWin;

typedef struct CombChuiPos
{
    char pad_0[0x10];
    short x_10;
    short y_12;
} CombChuiPos;

extern CombChuiMenu dword_800A45B0;
extern int dword_800A45BC[];
extern unsigned char byte_800A38D8;
extern unsigned char byte_800918F1;
extern CombChuiWin dword_80082784;
extern CombChuiPos dword_80082708;
extern CombChuiPos dword_80082740;
extern void UpdateMenuCursor_8003D794(void*, int);
extern int IsConfirmPressedP1_8003D380(int);
extern int IsCancelPressedP1_8003D41C(int);
extern int GetMenuCursorIndex_8003DA54(void*);
extern void sub_8002A5A4(void*);
extern void sub_8002BE10();
extern void sub_800A16FC();
extern void sub_800A450C();

void sub_800A4394(CombChuiTask* t, int a)
{
    short rect[4];
    int c;
    UpdateMenuCursor_8003D794(&dword_800A45B0, 0);
    if (byte_800918F1 == 0xFF)
    {
        dword_800A45B0.sel_8 = 1;
    }
    if (IsConfirmPressedP1_8003D380(1))
    {
        if ((short)GetMenuCursorIndex_8003DA54(&dword_800A45B0) == 0)
        {
            byte_800A38D8 = 1;
        }
        else
        {
            byte_800A38D8 = 0;
        }
        t->next_8 = sub_800A16FC;
        t->next_8(t, a);
    }
    else if (IsCancelPressedP1_8003D41C(1))
    {
        byte_800A38D8 = 0;
        t->next_8 = sub_800A16FC;
        t->next_8(t, a);
    }
    else
    {
        rect[0] = 10;
        rect[1] = 0x14;
        rect[2] = 0x12C;
        c = 0xC8;
        rect[3] = c;
        sub_800A450C(dword_800A45BC, rect);
        dword_80082784.f4 = GetTime30Hz_8002C64C();
        dword_80082784.f8 = 8;
        dword_80082784.f14 = 0;
        dword_80082708.x_10 = 0x72;
        dword_80082708.y_12 = c;
        dword_80082740.x_10 = 0xA0;
        dword_80082740.y_12 = c;
        dword_80082784.fC = dword_800A45B0.sel_8;
        sub_8002A5A4(&dword_80082784);
        sub_8002BE10();
    }
}

void sub_800A450C(int* p, unsigned short* q)
{
    short rect[4];
    int item;
    unsigned short y;
    sub_8003F900(2, 0);
    item = *p;
    y = q[1];
    while (item)
    {
        sub_8002AC88(8, q, (short)sub_8003E4C8(item), rect);
        rect[1] = y;
        DrawText_8003E91C(2, item, rect, 0);
        p++;
        item = *p;
        y += 0x10;
    }
}

INCLUDE_OVERLAY_ASM(combchui, dword_800A45B0);
