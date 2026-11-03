// COMBSTRT.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct CombStrtTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombStrtTask;

typedef struct CombStrtBox
{
    short col_0;
    char c_2;
    char c_3;
} CombStrtBox;

typedef struct CombStrtUnit
{
    char pad_0[0x84];
    char field_84[0x74];
} CombStrtUnit;

extern short word_800A4BF8;
extern unsigned char byte_800A4C14;
extern int dword_800A3A88;
extern short word_800A4C90;
extern short word_800A4C92;
extern short word_800A4C94;
extern short word_800A4C96;
extern unsigned int dword_8008D3FC;
extern unsigned short word_8008D3FC;
extern unsigned short uiColor_8008B590;
extern CombStrtUnit dword_800A3AA0[2][3];
extern void* dword_800A4C50[];
extern void sub_800A16FC();
extern int sub_800A1AAC(int);
extern int sub_800A1934(void*);
extern void Heal_80011CD0(void*);
extern void PlaySfx_80031494(int);
extern void sub_8002ADB4(void*, void*, int, int);
extern void sub_800A473C(int);
extern void sub_800A49DC(int, int);

INCLUDE_OVERLAY_ASM(combstrt, dword_800A4088);

INCLUDE_OVERLAY_ASM(combstrt, sub_800A4170);

void sub_800A43FC()
{
    if (IsConfirmPressedP1_8003D380(1))
    {
        if (word_800A4BF8 == 0)
        {
            dword_800A3A88 |= 2;
        }
        else
        {
            dword_800A3A88 &= ~2;
        }
        if (sub_800A1AAC(0) >= 2u || sub_800A1AAC(1) >= 2u)
        {
            byte_800A4C14 = byte_800A4C14 + 1;
        }
        else
        {
            byte_800A4C14 = 2;
        }
    }
}

void sub_800A4498()
{
    if (IsConfirmPressedP1_8003D380(1) && word_800A4BF8 == 1)
    {
        byte_800A4C14 = byte_800A4C14 + 1;
    }
    else if (IsConfirmPressedP1_8003D380(1))
    {
        byte_800A4C14 = 3;
        word_800A4C94 = 0;
        word_800A4C92 = 0;
        word_800A4C90 = (word_8008D3FC & 0xF) + 0x2D;
    }
}

void sub_800A4524(CombStrtTask* t)
{
    if (IsConfirmPressedP1_8003D380(1) && word_800A4BF8 == 1)
    {
        t->next_8 = sub_800A16FC;
        dword_800A3A88 &= ~1;
    }
    else if (IsConfirmPressedP1_8003D380(1))
    {
        byte_800A4C14 = 1;
        dword_800A3A88 |= 1;
        t->next_8 = sub_800A16FC;
    }
}

void sub_800A45B8()
{
    short st = word_800A4C92;
    switch (st)
    {
    case 0:
        sub_800A46FC();
        if (word_800A4C90 < word_800A4C94++)
        {
            word_800A4C92 = 1;
            word_800A4C94 = 0;
            word_800A4C96 = 0;
            word_800A4C90 = ((dword_8008D3FC & 0x70) >> 4) + 5;
        }
        break;
    case 1:
        if (word_800A4C96 < word_800A4C94++)
        {
            word_800A4C92 = 2;
        }
        break;
    case 2:
        sub_800A46FC();
        word_800A4C92 = 1;
        word_800A4C94 = 0;
        if (word_800A4C90 < word_800A4C96++)
        {
            byte_800A4C14 = 2;
        }
        break;
    }
}

void sub_800A46FC()
{
    int i;
    for (i = 0; i < 2; i++)
    {
        sub_800A473C(i);
    }
    PlaySfx_80031494(0x7F);
}

extern int rand(void);
extern int sub_800A4878(int idx, int* arr, int n);
void sub_800A473C(int side)
{
    int used[10];
    int order[10];
    CombStrtUnit tmp[10];
    int n = sub_800A1AAC(side);
    CombStrtUnit* units = dword_800A3AA0[side];
    int i;
    if (n < 2)
    {
        return;
    }
    for (i = 0; i < n; i++)
    {
        used[i] = -1;
        order[i] = -1;
    }
    for (i = 0; i < n; i++)
    {
        order[i] = sub_800A4878(rand() % (n - i), used, n);
        MemCopy_800403E8((unsigned int*)&tmp[i], (unsigned int*)&units[order[i]], 0xF8);
    }
    for (i = 0; i < n; i++)
    {
        MemCopy_800403E8((unsigned int*)&units[i], (unsigned int*)&tmp[i], 0xF8);
    }
}

int sub_800A4878(int idx, int* arr, int n)
{
    int i;
    int cnt = 0;
    i = 0;
    for (; i < n; i++, arr++)
    {
        if (*arr < 0)
        {
            if (cnt == idx)
            {
                *arr = cnt;
                break;
            }
            cnt++;
        }
    }
    return i;
}

void sub_800A48C0()
{
    int i;
    int j;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 3; j++)
        {
            CombStrtUnit* p = &dword_800A3AA0[i][j];
            if (sub_800A1934(p) == 0)
            {
                Heal_80011CD0(p->field_84 - 0);
            }
        }
    }
}

void sub_800A4958(int i)
{
    CombStrtBox box;
    int j;
    box.c_3 = 1;
    box.c_2 = 0;
    box.col_0 = uiColor_8008B590;
    sub_8002ADB4(dword_800A4C50[i], &box, 0xF, 0);
    for (j = 0; j < 3; j++)
    {
        sub_800A49DC(i, j);
    }
}

#if 0
// Not matched: s0/s1 swapped between slot and side*3 (register allocation), the rest matches
typedef struct CombStrtWin
{
    int f0;
    void* text_4;
    int f8;
    int fC;
    short x_10;
    short y_12;
    int f14;
    int f18;
} CombStrtWin;
extern CombStrtWin name_800A4154;
extern void* dword_800A4C58[];
extern short dword_800A4C64[][3][2];
extern void sub_8002F078(void* a, void* b, int c, int d);
extern void sub_800A1844(void* a, void* b, int c);
extern void DrawWindow_80042460(void* a, void* b, void* c, int d);
void sub_800A49DC(int side, int slot)
{
    CombStrtBox c1;
    CombStrtWin w;
    short pos[4];
    CombStrtBox c2;
    RECT r1;
    short pos2[4];
    CombStrtBox c3;
    RECT r2;
    CombStrtUnit* u = &dword_800A3AA0[side][slot];
    short* xy;
    if (sub_800A1934(u) != 1)
    {
        w = name_800A4154;
        w.text_4 = dword_800A4C58[slot];
        xy = dword_800A4C64[side][slot];
        w.x_10 = xy[0];
        w.y_12 = xy[1];
        c1.c_2 = 0;
        c1.c_3 = 1;
        c1.col_0 = saveData_8008B570.uiColor_20;
        sub_8002ADB4(&w, &c1, 0xF, 0);
        pos[0] = xy[0] + 0x2F;
        pos[1] = xy[1];
        sub_8002F078(u->field_84, pos, 0, 0xF);
        c2.c_2 = 0;
        c2.c_3 = 1;
        c2.col_0 = saveData_8008B570.uiColor_20;
        r1.x = xy[0] + 0x32;
        r1.y = xy[1];
        r1.w = 0x5E;
        r1.h = 0x14;
        DrawWindow_80042460(&r1, &c2, pOT_8008D454 + 15, 0);
        pos2[0] = xy[0];
        pos2[1] = xy[1] + 0x14;
        sub_800A1844(u, pos2, 0);
        c3.c_2 = 0;
        c3.c_3 = 1;
        c3.col_0 = saveData_8008B570.uiColor_20;
        r2.x = xy[0];
        r2.y = xy[1] + 0x14;
        r2.w = 0x90;
        r2.h = 0x13;
        DrawWindow_80042460(&r2, &c3, pOT_8008D454 + 15, 0);
    }
}
#endif
INCLUDE_OVERLAY_ASM(combstrt, sub_800A49DC);

INCLUDE_OVERLAY_ASM(combstrt, dword_800A4BF0);
