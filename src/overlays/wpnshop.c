// WPNSHOP.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct WpnObj_wpnshop
{
    short f_0;
    short f_2;
    int f_4;
    char pad_8[4];
    int f_C;
    short f_10;
    short f_12;
    char pad_14[0x14];
    char f_28[8];
    short f_30;
    short f_32;
    short f_34;
    short f_36;
    short f_38;
    char pad_3A[6];
    int f_40;
    int f_44;
} WpnObj_wpnshop;

typedef struct WpnRect_wpnshop
{
    short x, y, w, h;
} WpnRect_wpnshop;

typedef struct WpnDlg_wpnshop
{
    int f0, f4, f8, fC, f10, f14;
} WpnDlg_wpnshop;

typedef struct WpnCol_wpnshop
{
    unsigned short col_0;
    char c_2;
    char c_3;
} WpnCol_wpnshop;

extern unsigned short uiColor_8008B590;
extern char* dword_8008D454;
extern int frameCount_8008D3FC;
extern void sub_80042460(void* a0, void* a1, void* a2, unsigned int a3);
/* funcs.h declares unsigned short; the callers here use the full register */
#define GETINT_8001CE54(x) (((int (*)(int))sub_8001CE54)(x))
extern void sub_8002B004(void* p, int a, int b);
extern void sub_8002BE10();
extern void sub_8002A4E4(int a);
extern void sub_8001C19C(int a, int b);
extern unsigned int sub_8002C64C(void);
extern void sub_8002A5A4(WpnDlg_wpnshop* p);
extern char name_800826B0[];
extern char name_80082680[];
extern unsigned short name_800BF1EC[];
extern void sub_800BCF80(unsigned short* p);
extern void sub_800BB950(unsigned short* p);
extern void sub_800BC0AC();
extern WpnDlg_wpnshop name_800BADF0;
extern int dword_8008B4E8;
extern int sub_800AD184(int a, int b, int c);
extern void sub_800AD1E0(int a, int b, int c);
extern void sub_800AD058(int a);
extern int sub_800AD0A4(int a);
extern int sub_8001D1F8(int a, int b);
extern void sub_8003CF88(short a0, short a1, int a2);
extern void PlaySfx_80031494(int a);
extern void sub_8003D794(void* p, int a1);
extern void sub_8002A310(void* p, int a);
extern void sub_800429F8(int a0, int a1);
extern void sub_80042B38(int a0, int a1);
extern unsigned short name_800BE870[];
extern char name_800BE134[];
extern char name_800BE7C4[];
extern unsigned short name_800BF244[];
extern unsigned short name_800BF274[];
extern unsigned short name_800BF294[];
extern void sub_800BC210();
extern void sub_800BB194();
extern void sub_800BB1F4();
extern unsigned int sub_800AD990(int a);
typedef struct WpnTask_wpnshop
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} WpnTask_wpnshop;
extern char name_800BEAFC[];
extern char name_800BEBB4[];

INCLUDE_OVERLAY_ASM(wpnshop, dword_800B66C0);

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BAE2C);

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BB088);

// Matched
void sub_800BB130(WpnTask_wpnshop* t, unsigned short* p)
{
    if (dword_8008B4E8 != 0)
    {
        sub_8002BE10();
        sub_8002A4E4(0xE);
        sub_800BCF80(p);
        sub_800BB950(p);
        t->next_8 = sub_800BB194;
    }
}

// Matched
void sub_800BB194(WpnTask_wpnshop* t, unsigned short* p)
{
    sub_8002BE10();
    sub_8002A4E4(0xE);
    sub_800BCF80(p);
    sub_800BB950(p);
    sub_8001C19C(3, 0x20);
    t->next_8 = sub_800BB1F4;
}

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BB1F4);

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BB298);

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BB30C);

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BB664);

// Matched
void sub_800BB868(WpnObj_wpnshop* o, WpnRect_wpnshop* r, int a2, int a3, short idx)
{
    WpnCol_wpnshop c;
    int bit = 1 << idx;
    if (o->f_C & bit)
    {
        c.col_0 = uiColor_8008B590;
        c.c_2 = 1;
        c.c_3 = 1;
        sub_80042460(r, &c, dword_8008D454 + 0x38, frameCount_8008D3FC);
    }
}

// Matched
void sub_800BB8CC(WpnObj_wpnshop* o)
{
    sub_8002A4E4(0xE);
    sub_8002A310(name_800BE134, 0xE);
    sub_800429F8((int)name_800BE7C4, 0xE);
    sub_80042B38((int)name_800BE7C4, 0xE);
    if (o->f_0 < 0x11)
    {
        if (o->f_0 >= 0xC)
        {
            sub_800BC210(o);
        }
    }
}

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BB950);

// Matched
void sub_800BBDD0(WpnObj_wpnshop* o)
{
    short s;
    if (!(o->f_4 & 1) && o->f_34 != -1 && o->f_2 == -1)
    {
        s = o->f_0;
        if ((unsigned short)(s - 10) >= 2 && s != 8 && s != 9)
        {
            sub_8003D794(o->f_28, 0);
        }
    }
}

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BBE54);

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BBED0);

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BBFD4);

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BC0AC);

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BC194);

// Matched
void sub_800BC210(WpnObj_wpnshop* o)
{
    WpnRect_wpnshop r;
    r.x = 0x56;
    r.y = o->f_30 * 16 + 0x25;
    r.w = 0x1E;
    r.h = 0x10;
    sub_800BB868(o, &r, o->f_34, o->f_34, 0x17);
}

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BC268);

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BC2E4);

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BC374);

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BCABC);

// Matched
void sub_800BCC18(WpnObj_wpnshop* o)
{
    sub_800BC0AC(o, o->f_12 == 1 ? 0x12 : 0x11);
}

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BCC4C);

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BCCE8);

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BCED4);

// Matched
void sub_800BCF80(unsigned short* p)
{
    if ((unsigned int)(*p - 2) < 4)
    {
        sub_8002B004(name_800826B0, 0, 0xE);
    }
    else
    {
        sub_8002B004(name_80082680, 0, 0xE);
    }
}

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BCFCC);

// Matched
void sub_800BD174(WpnObj_wpnshop* o)
{
    sub_800BC0AC(o, o->f_12 == 1 ? 0xE : 0xD);
}

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BD1A8);

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BD278);

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BD378);

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BD444);

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BD61C);

// Matched
void sub_800BD6A4(WpnObj_wpnshop* o)
{
    sub_8003CF88(0x11E, 0x3C, 0xE);
    if (o->f_40 || o->f_44)
    {
        PlaySfx_80031494(0x7D);
        o->f_2 = name_800BE870[o->f_12];
    }
}

// Matched
int sub_800BD71C(int a, int b)
{
    int r = sub_800AD990(b);
    if (a != 0xFF && a == r)
    {
        return 1;
    }
    return 0;
}

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BD760);

// Matched
void sub_800BD928(WpnObj_wpnshop* o)
{
    if (o->f_40)
    {
        PlaySfx_80031494(0x7E);
        o->f_10 = o->f_30;
        o->f_2 = name_800BE870[o->f_12];
    }
    else if (o->f_44)
    {
        PlaySfx_80031494(0x7D);
        o->f_2 = 1;
    }
}

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BD9A8);

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BDAB4);

// Matched
int sub_800BDB80(int a, int b)
{
    if (sub_800AD184(a, b, 0))
    {
        return sub_800AD0A4(GETINT_8001CE54(a) * b) != 1;
    }
    return 2;
}

// Matched
void sub_800BDBDC(int a, int b)
{
    int x;
    sub_800AD1E0(a, b, 0);
    x = GETINT_8001CE54(a);
    sub_800AD058((x * 3 / 4) * b);
}

// Matched
int sub_800BDC40(int a, int b, int c)
{
    if (sub_800AD184(a, c, b + 1) == 1)
    {
        return sub_800AD0A4(sub_8001D1F8(a, b) * c) != 1;
    }
    return 2;
}

// Matched
void sub_800BDCB4(int a, int b, int c)
{
    int x;
    sub_800AD1E0(a, c, b + 1);
    x = sub_8001D1F8(a, b);
    sub_800AD058((x * 3 / 4) * c);
}

#if 0
// switch/if chain order differs: original tests 1,0,2 with blocks in order 0,1,2
int sub_800BDD2C(int n, int sel, int mask)
{
    int c = 0;
    unsigned short* p;
    n++;
    switch (sel)
    {
    case 1:
        p = name_800BF274;
        break;
    case 0:
        p = name_800BF244;
        break;
    case 2:
        p = name_800BF294;
        break;
    default:
        return 0;
    }
    while (n != 0)
    {
        if (*p++ & mask)
        {
            n--;
        }
        c++;
    }
    if (c == 0)
    {
        return 0xFF;
    }
    return c - 1;
}
#endif
INCLUDE_OVERLAY_ASM(wpnshop, sub_800BDD2C);

// Matched
int sub_800BDDB0(int n, int mask)
{
    int c = 0;
    unsigned short* p = name_800BF1EC;
    n++;
    while (n != 0)
    {
        if (*p++ & mask)
        {
            n--;
        }
        c++;
    }
    if (c == 0)
    {
        return 0xFF;
    }
    return c - 1;
}

// Matched
short sub_800BDDF8(unsigned short* p, int n, int mask)
{
    int c = 0;
    while (n-- != 0)
    {
        if (*p++ & mask)
        {
            c++;
        }
    }
    return c;
}

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BDE38);

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BDF68);

// Matched
int sub_800BE00C(WpnObj_wpnshop* o, short i)
{
    if (i == o->f_34)
    {
        return (short)(o->f_30 + o->f_32);
    }
    return (short)(o->f_36 + o->f_38);
}

// Matched
int sub_800BE058(WpnObj_wpnshop* o, short i)
{
    if (i == o->f_34)
    {
        return o->f_30;
    }
    return o->f_36;
}

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BE084);

INCLUDE_OVERLAY_ASM(wpnshop, dword_800BE110);
