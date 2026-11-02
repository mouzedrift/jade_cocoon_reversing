// MENU.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct MenuTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} MenuTask;

typedef struct MenuObj
{
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    char pad_18[0x10];
    short f28;
    char pad_2A[0x36];
    short f60;
} MenuObj;

extern void sub_800BE4A0();
extern void sub_800BD5E4();
extern void sub_800BD6C8();

INCLUDE_OVERLAY_ASM(menu, dword_800B66C0);

INCLUDE_OVERLAY_ASM(menu, sub_800BBB9C);

extern int dword_8008B4E8;
extern void sub_8002BE10();
extern void sub_800BBE90();
void sub_800BBE50(MenuTask* t)
{
    if (dword_8008B4E8)
    {
        sub_8002BE10();
        t->next_8 = sub_800BBE90;
    }
}

INCLUDE_OVERLAY_ASM(menu, sub_800BBE90);

extern int sub_800121A8();
int sub_800BBF10(unsigned char a, unsigned char b)
{
    int x = sub_800121A8(a);
    return x < sub_800121A8(b);
}

INCLUDE_OVERLAY_ASM(menu, sub_800BBF48);

INCLUDE_OVERLAY_ASM(menu, sub_800BC24C);

INCLUDE_OVERLAY_ASM(menu, sub_800BC2A8);

INCLUDE_OVERLAY_ASM(menu, sub_800BC56C);

INCLUDE_OVERLAY_ASM(menu, sub_800BC8A8);

INCLUDE_OVERLAY_ASM(menu, sub_800BC934);

INCLUDE_OVERLAY_ASM(menu, sub_800BC9E8);

INCLUDE_OVERLAY_ASM(menu, sub_800BCB98);

INCLUDE_OVERLAY_ASM(menu, sub_800BCEA0);

INCLUDE_OVERLAY_ASM(menu, sub_800BCF74);

INCLUDE_OVERLAY_ASM(menu, sub_800BCFDC);

INCLUDE_OVERLAY_ASM(menu, sub_800BD1B0);

INCLUDE_OVERLAY_ASM(menu, sub_800BD230);

INCLUDE_OVERLAY_ASM(menu, sub_800BD358);

INCLUDE_OVERLAY_ASM(menu, sub_800BD40C);

void sub_800BD590(MenuTask* t, int a)
{
    if (dword_8008B4E8)
    {
        sub_8002BE10();
        sub_800BE4A0(a);
        t->next_8 = sub_800BD5E4;
    }
}

void sub_800BD5E4(MenuTask* t, int a)
{
    sub_8002BE10();
    sub_800BE4A0(a);
    sub_8001C19C(3, 0x20);
    t->next_8 = sub_800BD6C8;
}

INCLUDE_OVERLAY_ASM(menu, sub_800BD634);

INCLUDE_OVERLAY_ASM(menu, sub_800BD6C8);

INCLUDE_OVERLAY_ASM(menu, sub_800BD80C);

extern int sub_800B32D4();
extern int name_8007A170[];
int sub_800BDB74(int a)
{
    if (a < 0xC9)
        return name_8007A170[a];
    return sub_800B32D4(a - 0xC9);
}

// near miss: a kept in a different register
#if 0
typedef struct MenuSaveView
{
    char pad_0[0x814];
    unsigned int flags_814[1];
} MenuSaveView;
int sub_800BDBB8(int a)
{
    int q = a / 32;
    return (((MenuSaveView*)&saveData_8008B570)->flags_814[q] & (1 << (a - q * 32))) != 0;
}
#endif
INCLUDE_OVERLAY_ASM(menu, sub_800BDBB8);

INCLUDE_OVERLAY_ASM(menu, sub_800BDBFC);

INCLUDE_OVERLAY_ASM(menu, sub_800BDD94);

INCLUDE_OVERLAY_ASM(menu, sub_800BDE10);

INCLUDE_OVERLAY_ASM(menu, sub_800BE048);

extern short name_800C1974[];
void sub_800BE25C(short* p)
{
    short* tbl = name_800C1974;
    short v = tbl[p[1]];
    if (v != -1)
        p[1] = v;
}

INCLUDE_OVERLAY_ASM(menu, sub_800BE294);

INCLUDE_OVERLAY_ASM(menu, sub_800BE38C);

INCLUDE_OVERLAY_ASM(menu, sub_800BE4A0);

INCLUDE_OVERLAY_ASM(menu, sub_800BEAE0);

INCLUDE_OVERLAY_ASM(menu, sub_800BEBFC);

INCLUDE_OVERLAY_ASM(menu, sub_800BEC8C);

INCLUDE_OVERLAY_ASM(menu, sub_800BECE4);

INCLUDE_OVERLAY_ASM(menu, sub_800BEFAC);

INCLUDE_OVERLAY_ASM(menu, sub_800BF0F4);

extern void sub_800AD1E0();
void sub_800BF3AC(MenuObj* o)
{
    sub_80011B24((int)o);
    sub_800AD1E0(o, 1, 0);
}

INCLUDE_OVERLAY_ASM(menu, sub_800BF3E0);

INCLUDE_OVERLAY_ASM(menu, sub_800BF540);

INCLUDE_OVERLAY_ASM(menu, sub_800BF794);

INCLUDE_OVERLAY_ASM(menu, sub_800BF8B4);

INCLUDE_OVERLAY_ASM(menu, sub_800BFB10);

INCLUDE_OVERLAY_ASM(menu, sub_800BFBE0);

INCLUDE_OVERLAY_ASM(menu, sub_800BFCA8);

INCLUDE_OVERLAY_ASM(menu, sub_800BFE18);

INCLUDE_OVERLAY_ASM(menu, sub_800BFEC0);

INCLUDE_OVERLAY_ASM(menu, sub_800BFF38);

INCLUDE_OVERLAY_ASM(menu, sub_800BFF84);

INCLUDE_OVERLAY_ASM(menu, sub_800BFFFC);

INCLUDE_OVERLAY_ASM(menu, sub_800C0084);

void sub_800C00D4(MenuObj* o, int a, int s)
{
    o->fC = 0;
    o->f0 = 0;
    o->f4 = a;
    o->fC |= 1 << s;
}

INCLUDE_OVERLAY_ASM(menu, sub_800C00F8);

extern int name_800C1BBC[];
void sub_800C01AC(MenuObj* o)
{
    o->f10 = 0;
    o->f10 = name_800C1BBC[o->f60];
}

extern int name_800C1BD0[];
void sub_800C01D0(MenuObj* o)
{
    o->f10 = 0;
    o->f10 = name_800C1BD0[o->f60];
}

INCLUDE_OVERLAY_ASM(menu, sub_800C01F4);

INCLUDE_OVERLAY_ASM(menu, sub_800C0428);

INCLUDE_OVERLAY_ASM(menu, sub_800C0578);

INCLUDE_OVERLAY_ASM(menu, sub_800C05E0);

INCLUDE_OVERLAY_ASM(menu, sub_800C06E8);

INCLUDE_OVERLAY_ASM(menu, sub_800C07F0);

INCLUDE_OVERLAY_ASM(menu, sub_800C08C0);

int sub_800C0990(MenuObj* o, int m)
{
    if (m & o->f14)
        return 8;
    return o->f28;
}

INCLUDE_OVERLAY_ASM(menu, sub_800C09B0);

INCLUDE_OVERLAY_ASM(menu, sub_800C0C3C);

INCLUDE_OVERLAY_ASM(menu, sub_800C0CA4);

// near miss: compiler folds the range tests differently
#if 0
int sub_800C0DD4(int a)
{
    if ((a >= 0 && a < 3) || (a >= 9 && a < 14))
        return 1;
    return 0;
}
#endif
INCLUDE_OVERLAY_ASM(menu, sub_800C0DD4);

INCLUDE_OVERLAY_ASM(menu, sub_800C0E04);

extern int name_800C29B8;
extern int name_800B0EC0;
extern int sub_800A5E68();
int sub_800C1000(void)
{
    int v = name_800C29B8;
    if (v != 1)
        return 1;
    if (sub_800A5E68() == 0 && name_800B0EC0 == v)
        return 1;
    return 0;
}

INCLUDE_OVERLAY_ASM(menu, dword_800C1050);
