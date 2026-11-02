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
extern unsigned short word_8008D3FC;
extern unsigned short uiColor_8008B590;
extern CombStrtUnit dword_800A3AA0[2][3];
extern void* dword_800A4C50[];
extern void sub_800A16FC();
extern int sub_800A1AAC(int);
extern int sub_800A1934(void*);
extern void sub_80011CD0(void*);
extern void sub_80031494(int);
extern void sub_8002ADB4(void*, void*, int, int);
extern void sub_800A473C(int);
extern void sub_800A49DC(int, int);

INCLUDE_OVERLAY_ASM(combstrt, dword_800A4088);

INCLUDE_OVERLAY_ASM(combstrt, sub_800A4170);

void sub_800A43FC()
{
    if (sub_8003D380(1))
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
    if (sub_8003D380(1) && word_800A4BF8 == 1)
    {
        byte_800A4C14 = byte_800A4C14 + 1;
    }
    else if (sub_8003D380(1))
    {
        byte_800A4C14 = 3;
        word_800A4C94 = 0;
        word_800A4C92 = 0;
        word_800A4C90 = (word_8008D3FC & 0xF) + 0x2D;
    }
}

void sub_800A4524(CombStrtTask* t)
{
    if (sub_8003D380(1) && word_800A4BF8 == 1)
    {
        t->next_8 = sub_800A16FC;
        dword_800A3A88 &= ~1;
    }
    else if (sub_8003D380(1))
    {
        byte_800A4C14 = 1;
        dword_800A3A88 |= 1;
        t->next_8 = sub_800A16FC;
    }
}

INCLUDE_OVERLAY_ASM(combstrt, sub_800A45B8);

void sub_800A46FC()
{
    int i;
    for (i = 0; i < 2; i++)
    {
        sub_800A473C(i);
    }
    sub_80031494(0x7F);
}

INCLUDE_OVERLAY_ASM(combstrt, sub_800A473C);

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
                sub_80011CD0(p->field_84 - 0);
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

INCLUDE_OVERLAY_ASM(combstrt, sub_800A49DC);

INCLUDE_OVERLAY_ASM(combstrt, dword_800A4BF0);
