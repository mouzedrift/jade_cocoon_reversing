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

typedef struct MenuSaveView
{
    char pad_0[0x814];
    unsigned int flags_814[1];
} MenuSaveView;

typedef struct MenuBox
{
    short x_0;
    short y_2;
    int pad_4;
    short col_8;
    char c_A;
    char c_B;
} MenuBox;
extern void sub_8002C06C();
extern unsigned short uiColor_8008B590;
extern void sub_800BFF84();
extern void sub_80027478();
extern void sub_80042460();

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

extern int sub_800BD230();
extern void sub_800BCFDC();
extern void sub_800BC2A8();
extern void sub_800BD1B0();
extern void sub_800BBF48();
// near miss: original keeps a second copy of the argument in another saved register
#if 0
void sub_800BBE90(MenuTask* t, void* a)
{
    void* q;
    sub_8002BE10();
    sub_8001C19C(3, 0x20);
    q = a;
    if (sub_800BD230(a))
    {
        sub_800BCFDC(a);
        t->next_8 = sub_800BD1B0;
    }
    else
    {
        sub_800BC2A8(q);
        t->next_8 = sub_800BBF48;
    }
}
#endif
INCLUDE_OVERLAY_ASM(menu, sub_800BBE90);

extern int sub_800121A8();
int sub_800BBF10(unsigned char a, unsigned char b)
{
    int x = sub_800121A8(a);
    return x < sub_800121A8(b);
}

INCLUDE_OVERLAY_ASM(menu, sub_800BBF48);

extern int sub_800272D0();
extern void sub_80020D68();
extern void sub_800A6D30();
void sub_800BC24C(MenuTask* t)
{
    if (sub_800272D0() == 0)
    {
        sub_80020D68();
        sub_800A6D30(1);
        dword_8008B540 = 1;
        t->flags_0 = (t->flags_0 & ~1) | 0x8000;
    }
}

INCLUDE_OVERLAY_ASM(menu, sub_800BC2A8);

INCLUDE_OVERLAY_ASM(menu, sub_800BC56C);

void sub_800BC8A8(void)
{
    short rect[4];
    MenuBox b;
    rect[0] = 0x6C;
    rect[1] = 0x1A;
    rect[2] = 0x6C;
    rect[3] = 0x12;
    b.x_0 = 0x6F;
    b.y_2 = 0x1C;
    sub_8002C06C(&b, 0xE4, 0xE);
    b.c_A = 1;
    b.c_B = 1;
    b.col_8 = uiColor_8008B590;
    sub_80042460(rect, &b.col_8, (char*)pOT_8008D454 + 0x38, frameCount_8008D3FC);
}

extern int sub_8002FA0C();
void sub_800BC934(int a, int b)
{
    short rect[4];
    MenuBox bx;
    short r = sub_8002FA0C((short)b, (short)(a - 1));
    if (r != 0)
    {
        rect[0] = r + 8;
        rect[1] = 0xBF;
        rect[2] = 0x54;
        rect[3] = 0x12;
        bx.x_0 = r + 0xE;
        bx.y_2 = 0xC1;
        sub_8002C06C(&bx, 0x5D, 0xE);
        bx.c_A = 1;
        bx.c_B = 1;
        bx.col_8 = uiColor_8008B590;
        sub_80042460(rect, &bx.col_8, (char*)pOT_8008D454 + 0x38, frameCount_8008D3FC);
    }
}

INCLUDE_OVERLAY_ASM(menu, sub_800BC9E8);

INCLUDE_OVERLAY_ASM(menu, sub_800BCB98);

INCLUDE_OVERLAY_ASM(menu, sub_800BCEA0);

extern void sub_8001AEB8();
extern int name_800338B0();
void sub_800BCF74(short a)
{
    int x = a - 1;
    int r17 = (int)sub_80010824(3, x);
    char* r16 = (char*)sub_80010598(3, x);
    sub_8001AEB8(name_800338B0(r16), r16 + 0x84, r17);
}

INCLUDE_OVERLAY_ASM(menu, sub_800BCFDC);

extern int sub_8003D380();
extern int sub_8003D41C();
extern void sub_80034A84();
extern int* name_8008D640;
void sub_800BD1B0(MenuTask* t)
{
    int* p = name_8008D640;
    int f;
    sub_8002BE10();
    f = p[4] & 0x8001;
    p += 4;
    if (f != 1)
        t->next_8 = sub_800BBF48;
    if (sub_8003D380(1) || sub_8003D41C(1))
        sub_80034A84(p);
}

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

// near miss: original has an extra register copy of i / 32
#if 0
void sub_800BD634(void)
{
    int i;
    for (i = 0; i < 0xD3; i++)
    {
        if (sub_800BDD94(i) && (unsigned)(i - 0x25) >= 4)
        {
            int q = i / 32;
            ((MenuSaveView*)&saveData_8008B570)->flags_814[q] |= 1 << (i - q * 32);
        }
    }
}
#endif
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
int sub_800BDBB8(int a)
{
    int q = a / 32;
    return (((MenuSaveView*)&saveData_8008B570)->flags_814[q] & (1 << (a - q * 32))) != 0;
}
#endif
INCLUDE_OVERLAY_ASM(menu, sub_800BDBB8);

INCLUDE_OVERLAY_ASM(menu, sub_800BDBFC);

// near miss: 1 word (delay slot of the last return)
#if 0
int sub_800BDD94(int a)
{
    if ((unsigned)(a - 0x29) < 0x10 || (unsigned)(a - 0xC9) < 0xA)
        return 0;
    if ((unsigned)(a - 0x20) < 4 || (unsigned)(a - 0xC1) < 8)
        return (unsigned)(a - 0x22) < 2;
    if ((unsigned)(a - 0x24) < 5)
        return 1;
    if ((unsigned)(a - 0x20) < 2 || (unsigned)(a - 0x39) < 0x88)
        return 1;
    return 0;
}
#endif
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

extern void sub_8002DB48();
void sub_800BEBFC(int* o, int a)
{
    Minion* m = 0;
    char* m2 = 0;
    short s[2];
    short x = *(unsigned short*)((char*)o + 0x2C) + *(unsigned short*)((char*)o + 0x4C);
    if (x < o[2] - 1)
    {
        m = sub_80010598(3, x);
        m2 = (char*)m + 0x84;
    }
    s[0] = 0x33;
    s[1] = 0x3E;
    if (m)
        sub_8002DB48(m2, 0xE, a, s, m, 0);
}

typedef struct MenuCol
{
    unsigned short col;
    unsigned char c_2;
    unsigned char c_3;
} MenuCol;
void sub_800BEC8C(int unused, int a, short b)
{
    MenuCol t;
    t.col = uiColor_8008B590;
    t.c_2 = 1;
    t.c_3 = 1;
    sub_80042460(a, &t, &pOT_8008D454[b], frameCount_8008D3FC);
}

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

extern void sub_80033308();
extern void sub_800C07F0();
extern int name_8008D678;
// near miss: scheduling of the global load vs. prologue
#if 0
void sub_800BFEC0(MenuTask* t, int a)
{
    if (name_8008D678 < 0)
    {
        sub_80033308((char*)pOT_8008D454 + 0x38);
        sub_800C07F0(a);
        sub_80033308((char*)pOT_8008D454 + 0x38);
    }
    else
    {
        sub_800BFF84(a);
        t->next_8 = sub_800BD6C8;
    }
}
#endif
INCLUDE_OVERLAY_ASM(menu, sub_800BFEC0);

extern int name_800C45D8();
extern void sub_800BFF84();
void sub_800BFF38(MenuTask* t, int a)
{
    if (name_800C45D8() == 0)
    {
        sub_800BFF84(a);
        t->next_8 = sub_800BD6C8;
    }
}

INCLUDE_OVERLAY_ASM(menu, sub_800BFF84);

extern int name_800C29BC;
extern void sub_800A7714();
extern void sub_800BD40C();
void sub_800BFFFC(MenuTask* t)
{
    if (sub_800272D0() == 0)
    {
        if (name_800C29BC)
            sub_800A7714(0);
        sub_80027478(0x40, 0);
        sub_800A6D30(1);
        t->next_8 = sub_800BD40C;
        t->flags_0 = (t->flags_0 & ~1) | 0x8000;
    }
    dword_8008B540 = 1;
}

extern void sub_80027478();
extern void sub_80027314();
extern void sub_800BFFFC();
extern char* name_8008D498;
void sub_800C0084(void)
{
    MenuTask* t = (MenuTask*)(name_8008D498 + 0x10);
    sub_80027478(0x40, 1);
    FreeActiveOverlay_8002C014();
    sub_80027314();
    t->next_8 = sub_800BFFFC;
}

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

extern int sub_800C0990();
extern void sub_8002F7D0();
extern void sub_8002BEC8();
extern char name_800C18C4[];
void sub_800C0578(MenuObj* o)
{
    int buf[2];
    short r[2];
    short s = sub_800C0990(o, 1);
    r[0] = 0xC2;
    r[1] = 0x31;
    sub_8002F7D0(r, 0xE);
    sub_8002BEC8(buf, name_800C18C4, s, 0xE, 0, 0);
}

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
