// WPNSHOP.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct WpnObj_wpnshop
{
    short f_0;
    short f_2;
    int f_4;
    int f_8;
    int f_C;
    short f_10;
    short f_12;
    int f_14;
    int f_18;
    short f_1C;
    unsigned short f_1E;
    short f_20[4];
    short f_28[4];
    short f_30;
    short f_32;
    short f_34;
    short f_36;
    short f_38;
    short f_3A;
    short f_3C;
    short f_3E;
    int f_40;
    int f_44;
    short f_48;
    char pad_4A[2];
    short f_4C;
    short f_4E;
    short f_50;
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
extern void sub_800BCF80();
extern void sub_800BB950();
extern void sub_800BC0AC();
extern WpnDlg_wpnshop name_800BADF0;
extern int dword_8008B4E8;
extern int sub_800AD184(int a, int b, int c);
extern void sub_800AD1E0(int a, int b, int c);
extern void sub_800AD058(int a);
extern int sub_800AD0A4(int a);
extern void sub_8003CF88(short a0, short a1, int a2);
extern void PlaySfx_80031494(int a);
extern void sub_8003D794(void* p, int a1);
extern void sub_8002A310(void* p, int a);
extern void sub_800429F8(int a0, int a1);
extern void sub_80042B38(int a0, int a1);
extern unsigned short name_800BE870[];
extern int name_800BE134[];
extern int* name_800BE3D8[];
extern int* name_800BE434[];
extern int* name_800BE37C[];
extern char name_800BE7C4[];
extern unsigned short name_800BF244[];
extern unsigned short name_800BF274[];
extern unsigned short name_800BF294[];
extern void sub_800BC210();
typedef struct WpnPair_wpnshop
{
    short a;
    short b;
} WpnPair_wpnshop;
typedef struct WpnSmall_wpnshop
{
    short a;
    char b;
    char c;
} WpnSmall_wpnshop;
extern char levantStatus_8008BD38[];
extern void sub_8002F7D0(void* p, int a1);
extern void sub_8002E288(int a0, int a1, int a2, void* p);
extern void sub_8002E188(void* a0, void* a1, void* a2, int a3);
extern void sub_8002B3DC(WpnPair_wpnshop p, int b, void* c, int d);
#define f_26 f_20[3]
extern int sub_8003D480(void);
extern char name_800BEBC4[];
extern char name_800BEBC8[];
extern char name_800BEBCC[];
extern char name_800BEFEC[];
extern char name_800BEE7C[];
extern char name_800BF0DC[];
extern void sub_800BC194();
extern void sub_800BC2E4();
extern void sub_800BBED0();
extern void sub_800BC374();
extern void sub_800BCC4C();
extern void sub_800BCCE8();
extern void sub_800BD174();
extern void sub_800BCC18();
extern void sub_800BC268();
extern void sub_800BCED4();
extern void sub_800BCFCC();
extern void sub_800BB8CC();
typedef struct WpnRow_wpnshop
{
    unsigned short* p;
    char pad_4[16];
} WpnRow_wpnshop;
extern WpnRow_wpnshop name_800BE580[];
extern int name_800BE7CC[];
extern int** dword_8008D3E0;
extern void sub_800A7B00(int a);
extern void sub_800BB130();
extern short sub_800BDDF8();
extern int sub_800BB088();
typedef struct WpnA384_wpnshop
{
    void* rect;
    int frame;
    short a;
    short b;
} WpnA384_wpnshop;
typedef struct WpnBox2_wpnshop
{
    short x;
    short y;
} WpnBox2_wpnshop;
extern void sub_8002A384(void* p);
extern int sub_800AD02C(void);
extern int sub_800BDF68();
extern int sub_800BDE38();
typedef struct WpnPos_wpnshop
{
    unsigned short x;
    unsigned short y;
} WpnPos_wpnshop;
extern void sub_800BBFD4();
extern short sub_800BE00C(WpnObj_wpnshop* o, short i);
extern int sub_800BDDB0();
extern int sub_800BDD2C();
extern int sub_800AD2C8(int a, int b);
extern int sub_800AD254(int a, int b);
extern int sub_800AD288(int a, int b);
extern int sub_800AD73C(int a);
extern void sub_8002C06C(void* p, int a, short b);
extern void sub_8002C414(void* p, int a, short b);
extern unsigned short name_800BE868[];
extern unsigned short name_800BE86C[];
typedef struct WpnBox_wpnshop
{
    short x_0;
    short y_2;
    int pad_4;
    unsigned short col_8;
    char c_A;
    char c_B;
} WpnBox_wpnshop;
typedef struct WpnSave_wpnshop
{
    char pad_0[0x20];
    unsigned short f20;
    char pad_22[0x2BA];
    short f2DC;
    char pad_2DE[6];
    short f2E4;
    char pad_2E6[2];
    short f2E8;
} WpnSave_wpnshop;
#define WPNSAVE ((WpnSave_wpnshop*)&saveData_8008B570)
extern void FreeActiveOverlay_8002C014(void);
extern void sub_800AD9EC(int a, int b);
extern void sub_800BBDD0();
extern void sub_800BB664();
extern void sub_800BB30C();
extern int sub_8003D380(int a);
extern int sub_8003D41C(int a);
extern unsigned short name_8009194C;
extern void sub_800BD1A8();
extern void sub_800BD278();
extern void sub_800BD378();
extern void sub_800BD9A8();
extern void sub_800BDAB4();
extern void sub_800BD928();
extern void sub_800BD760();
extern void sub_800BD444();
extern void sub_800BD61C();
extern void sub_800BD6A4();

extern unsigned short name_800BE818[];
extern unsigned short name_800BE840[];
extern int sub_800AD308(int a);
extern void sub_800BB298();
extern void sub_80027478(int a, int b);
extern void sub_800A7BF0(int a);
extern void sub_800A6D30(int a);
extern int sub_800272D0(void);
extern int sub_8003D198(int a, int b, int c, int d);
extern unsigned short padRepeat_800918CC;
extern int eventDispatchHalt_8008B540;
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

#if 0
// register allocation only: original has b in s1, t in s2, a in s3
void sub_800BAE2C(int a, int b)
{
    WpnObj_wpnshop* o;
    EventEntry* t = AllocEventEntry_80043AF8((EventNode*)dword_8008D3E0);
    if (t)
    {
        t->flags = (t->flags | 1) & ~0x8000;
        o = (WpnObj_wpnshop*)t->buffer;
        o->f_4C = b;
        if (a == 0)
        {
            o->f_0 = 1;
            o->f_34 = 6;
            o->f_3A = 0;
        }
        else if (a == 1)
        {
            o->f_0 = 0;
            o->f_34 = 0;
            o->f_3A = 9;
        }
        sub_8003F900(2, 0);
        sub_8003F900(1, 0);
        o->f_2 = -1;
        o->f_4 = 4;
        o->f_8 = 0;
        o->f_C = 0;
        o->f_10 = 0;
        o->f_14 = 0;
        o->f_12 = 0;
        o->f_18 = 1;
        o->f_1C = a;
        o->f_8 = name_800BE7CC[o->f_0];
        o->f_1E = sub_800BB088(o);
        o->f_20[0] = sub_800BDDF8(name_800BF244, 0x17, o->f_1E);
        o->f_20[1] = sub_800BDDF8(name_800BF274, 0xF, o->f_1E);
        o->f_20[2] = sub_800BDDF8(name_800BF294, 0x11, o->f_1E);
        o->f_20[3] = sub_800BDDF8(name_800BF1EC, 0x2B, o->f_1E);
        o->f_36 = 0;
        o->f_38 = 0;
        o->f_3C = 0;
        o->f_3E = 0;
        o->f_28[0] = name_800BE580[o->f_34].p[0];
        o->f_28[1] = name_800BE580[o->f_34].p[1];
        o->f_28[2] = name_800BE580[o->f_34].p[2];
        o->f_28[3] = name_800BE580[o->f_34].p[3];
        o->f_30 = 0;
        o->f_32 = 0;
        o->f_40 = 0;
        o->f_44 = 0;
        o->f_48 = 0;
        o->f_4E = 0;
        o->f_50 = 0;
        sub_8001C19C(0, 0x20);
        sub_800A7B00(-1);
        sub_8002BF74();
        t->cb_8 = (EventEntryFn)sub_800BB130;
    }
}
#endif
INCLUDE_OVERLAY_ASM(wpnshop, sub_800BAE2C);

// Matched
int sub_800BB088(WpnObj_wpnshop* o)
{
    int r = 1;
    if (sub_800AD73C(4))
    {
        r = 2;
    }
    if (sub_800AD73C(6))
    {
        r = 4;
    }
    if (o->f_4C == 3)
    {
        r = 8;
    }
    if (WPNSAVE->f2DC == 0 && WPNSAVE->f2E4 == 0 && WPNSAVE->f2E8 == 4 && o->f_4C == 3)
    {
        r = 0x10;
    }
    return r;
}

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

#if 0
// extra callee-saved copy of ctx pointer (s1=s0) in the original
void sub_800BB1F4(WpnTask_wpnshop* t, WpnObj_wpnshop* o)
{
    sub_8002BE10();
    sub_800BBDD0(o);
    sub_800BB664(o);
    sub_800BB30C(o);
    if (o->f_48 < 8)
    {
        o->f_48++;
    }
    if (o->f_4 & 2)
    {
        sub_80027478(0x40, 1);
        FreeActiveOverlay_8002C014();
        sub_80027314();
        t->next_8 = sub_800BB298;
    }
}
#endif
INCLUDE_OVERLAY_ASM(wpnshop, sub_800BB1F4);

// Matched
void sub_800BB298(WpnTask_wpnshop* t)
{
    if (sub_800272D0() == 0)
    {
        sub_800A7BF0(-1);
        t->next_8 = sub_800BB1F4;
        t->flags_0 = (t->flags_0 & ~1) | 0x8000;
        sub_80027478(0x40, 0);
        sub_800A6D30(1);
        eventDispatchHalt_8008B540 = 1;
    }
}

void sub_800BB30C(WpnObj_wpnshop* o)
{
    int r;
    int a;
    short i;
    int old;
    int m;
    if (o->f_2 != -1)
    {
        o->f_8 = 0;
        o->f_34 = name_800BE818[o->f_2];
        o->f_28[0] = name_800BE580[o->f_34].p[0];
        o->f_28[1] = name_800BE580[o->f_34].p[1];
        o->f_28[2] = name_800BE580[o->f_34].p[2];
        o->f_28[3] = name_800BE580[o->f_34].p[3];
        switch (o->f_2)
        {
        case 3:
            r = sub_800AD308(0);
            if (r < 3)
                r = 3;
            o->f_28[2] = r + 1;
            break;
        case 5:
            r = sub_800AD308(o->f_10 + 1);
            if (r < 3)
                r = 3;
            o->f_28[2] = r + 1;
            break;
        }
        o->f_3A = name_800BE840[o->f_2];
        switch (o->f_2)
        {
        case 0:
        case 1:
            o->f_30 = (unsigned short)o->f_12;
            o->f_32 = 0;
            o->f_10 = 0;
            break;
        case 2:
        case 3:
            o->f_30 = (unsigned short)o->f_36;
            o->f_32 = (unsigned short)o->f_38;
            if (o->f_12 == 0)
                o->f_28[2] = o->f_26;
            break;
        case 4:
        case 5:
            o->f_30 = (unsigned short)o->f_36;
            o->f_32 = (unsigned short)o->f_38;
            if (o->f_12 == 0)
                o->f_28[2] = o->f_20[o->f_10];
            break;
        case 6:
        case 7:
            o->f_30 = (unsigned short)o->f_10;
            o->f_32 = 0;
            o->f_36 = 0;
            o->f_38 = 0;
            break;
        case 8:
        case 9:
            o->f_30 = (unsigned short)o->f_30;
            o->f_36 = o->f_30;
            o->f_38 = o->f_32;
            o->f_18 = 1;
            if (o->f_12 == 1)
                o->f_8 |= 0x800;
            else if (o->f_12 == 0)
                o->f_8 |= 0x400;
            break;
        case 10:
        case 11:
            o->f_36 = o->f_30;
            o->f_38 = o->f_32;
            o->f_18 = 1;
            if (o->f_12 == 1)
                o->f_8 |= 0x20;
            else if (o->f_12 == 0)
                o->f_8 |= 0x10;
            break;
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            o->f_30 = 1;
            o->f_32 = 0;
            break;
        case 17:
        case 18:
            o->f_30 = 0;
            o->f_32 = 0;
            break;
        }
        o->f_48 = 0;
        old = o->f_C;
        o->f_8 |= name_800BE7CC[o->f_2];
        o->f_C = 0;
        for (i = 0; i < 29; i++)
        {
            m = 1 << i;
            if ((old & m) && (o->f_8 & m))
                o->f_C |= m;
        }
        o->f_0 = o->f_2;
        o->f_2 = -1;
    }
}
INCLUDE_OVERLAY_ASM(wpnshop, dword_800BADA0);

void sub_800BB664(WpnObj_wpnshop* o)
{
    if (o->f_48 == 8 && !(o->f_4 & 1))
    {
        if (sub_8003D380(0))
        {
            o->f_40 = 1;
        }
        else if (sub_8003D41C(0))
        {
            o->f_44 = 1;
        }
    }
    if (o->f_4 & 1)
    {
        sub_800BBE54(o);
        if (o->f_50 < 150)
        {
            o->f_50++;
        }
        if (name_8009194C || o->f_50 >= 150)
        {
            o->f_3A = name_800BE840[o->f_0];
            o->f_4 &= ~1;
            o->f_4E = 0;
            o->f_3E = 0;
            o->f_50 = 0;
        }
    }
    else
    {
        switch (o->f_0)
        {
        case 0:
        case 1:
            sub_800BD1A8(o);
            break;
        case 2:
            sub_800BD278(o);
            break;
        case 3:
            sub_800BD378(o);
            break;
        case 4:
            sub_800BD9A8(o);
            break;
        case 5:
            sub_800BDAB4(o);
            break;
        case 6:
        case 7:
            sub_800BD928(o);
            break;
        case 8:
        case 9:
        case 10:
        case 11:
            sub_800BD760(o);
            break;
        case 12:
        case 13:
        case 14:
        case 15:
            sub_800BD444(o);
            break;
        case 16:
            sub_800BD61C(o);
            break;
        case 17:
        case 18:
            sub_800BD6A4(o);
            break;
        }
        if (o->f_40)
        {
            o->f_40 = 0;
        }
        if (o->f_44)
        {
            o->f_44 = 0;
        }
    }
    sub_800BB950(o);
    sub_800BCF80(o);
}
INCLUDE_OVERLAY_ASM(wpnshop, dword_800BADF0);

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

// Matched
void sub_800BB950(WpnObj_wpnshop* o)
{
    WpnPos_wpnshop pos;
    char* p;
    int r;
    int s;
    short i;
    p = 0;
    if (o->f_8 & 1)
    {
        sub_800BC194(o);
    }
    if (o->f_8 & 2)
    {
        sub_800BC2E4(o);
    }
    if (o->f_8 & 4)
    {
        sub_800BBED0(o, name_800BEBC4);
    }
    if (o->f_8 & 8)
    {
        sub_800BBED0(o, name_800BEBC8);
    }
    if (o->f_8 & 0x10)
    {
        sub_800BC374(o, 4);
    }
    if (o->f_8 & 0x20)
    {
        sub_800BC374(o, 5);
    }
    if (o->f_8 & 0x80)
    {
        sub_800BCC4C(o);
    }
    if (o->f_8 & 0x400)
    {
        sub_800BCCE8(o);
        sub_800BC374(o, 0xA);
    }
    if (o->f_8 & 0x800)
    {
        sub_800BC374(o, 0xB);
    }
    if (o->f_8 & 0x40)
    {
        sub_800BC194(o);
    }
    if (o->f_8 & 0x2000)
    {
        sub_800BD174(o);
    }
    if (o->f_8 & 0x4000)
    {
        sub_800BD174(o);
    }
    if (o->f_8 & 0x20000)
    {
        sub_800BCC18(o);
    }
    if (o->f_8 & 0x40000)
    {
        sub_800BCC18(o);
    }
    if (o->f_8 & 0x200)
    {
        sub_800BC268(o);
    }
    if (o->f_8 & 0x800000)
    {
        sub_800BCED4(o);
    }
    if (o->f_8 & 0x2000000)
    {
        sub_800BCFCC(o);
    }
    if ((unsigned short)(o->f_0 - 2) < 4)
    {
        p = (char*)1;
    }
    if (p)
    {
        p = 0;
        if (sub_8003D480())
        {
            pos.x = 0xA;
            pos.y = 0x12;
            s = (unsigned short)o->f_32 + (unsigned short)o->f_30;
            r = 0xFF;
            switch (o->f_34)
            {
            case 4:
                if ((short)s < o->f_26)
                {
                    r = sub_800BDDB0((short)s, o->f_1E);
                }
                if (r != 0xFF)
                {
                    p = name_800BEBCC + r * 16;
                }
                break;
            case 5:
                r = sub_800AD288((short)s, 0);
                if (r != 0xFF)
                {
                    p = name_800BEBCC + r * 16;
                }
                break;
            case 10:
                if ((short)s < o->f_20[o->f_10])
                {
                    r = sub_800BDD2C((short)s, o->f_10, o->f_1E);
                }
                if (r != 0xFF)
                {
                    switch (o->f_10)
                    {
                    case 0:
                        p = name_800BEE7C + r * 16;
                        break;
                    case 1:
                        p = name_800BEFEC + r * 16;
                        break;
                    case 2:
                        p = name_800BF0DC + r * 16;
                        break;
                    }
                }
                break;
            case 11:
                r = sub_800AD288((short)s, o->f_10 + 1);
                if (r != 0xFF)
                {
                    switch (o->f_10)
                    {
                    case 0:
                        p = name_800BEE7C + r * 16;
                        break;
                    case 1:
                        p = name_800BEFEC + r * 16;
                        break;
                    case 2:
                        p = name_800BF0DC + r * 16;
                        break;
                    }
                }
                break;
            default:
                p = 0;
                break;
            }
        }
    }
    if (p)
    {
        sub_8002AF10((int)p, (int)&pos, 0xE);
    }
    else
    {
        sub_800BB8CC(o);
    }
    for (i = 0; i < 0x1D; i++)
    {
        int bit = 1 << i;
        if ((o->f_8 & bit) && i != 0x18)
        {
            int c = o->f_C;
            if (o->f_48 == 8)
            {
                o->f_C = c | bit;
            }
        }
    }
}

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

// Matched
void sub_800BBE54(WpnObj_wpnshop* o)
{
    switch (o->f_34)
    {
    case 4:
        if (o->f_4E == 1)
        {
            o->f_3A = 0x11;
        }
        else if (o->f_4E == 2)
        {
            o->f_3A = 0x12;
        }
        break;
    case 10:
        if (o->f_4E == 1)
        {
            o->f_3A = 0x10;
        }
        else if (o->f_4E == 2)
        {
            o->f_3A = 0x13;
        }
        break;
    }
}

// Matched
void sub_800BBED0(void* unused, WpnPos_wpnshop* p)
{
    WpnRect_wpnshop r;
    WpnBox_wpnshop b;
    r.x = p->x;
    r.y = p->y;
    r.w = 0x79;
    r.h = 0x10;
    b.col_8 = uiColor_8008B590;
    b.c_A = 0;
    b.c_B = 1;
    b.x_0 = p->x + 4;
    b.y_2 = p->y + 3;
    sub_8002C06C(&b, 0x7A, 0xE);
    b.x_0 = p->x + 0x60;
    b.y_2 = p->y + 6;
    sub_8002C414(&b, sub_800AD02C(), 0xE);
    b.x_0 = p->x + 0x61;
    b.y_2 = p->y + 4;
    sub_8002C06C(&b, 0xEA, 0xE);
    sub_80042460(&r, &b.col_8, dword_8008D454 + 0x38, 0);
}

#if 0
// register allocation: original keeps &box in s0, 0x4d in s1, 0x77 in s2
void sub_800BBFD4(int a)
{
    WpnRect_wpnshop r;
    WpnBox_wpnshop b;
    r.w = 0x45;
    r.h = 0x10;
    b.c_B = 1;
    b.x_0 = 0x7B;
    b.col_8 = uiColor_8008B590;
    r.x = 0x77;
    r.y = 0x4D;
    b.c_A = 0;
    b.y_2 = 0x50;
    sub_8002C06C(&b, 0x93, 0xE);
    b.x_0 = 0xB8;
    b.y_2 = 0x52;
    sub_8002C414(&b, a, 0xE);
    b.x_0 = 0x77;
    b.y_2 = 0x4D;
    sub_80042460(&r, &b.col_8, dword_8008D454 + 0x38, 0);
}
#endif
INCLUDE_OVERLAY_ASM(wpnshop, sub_800BBFD4);

// Matched
void sub_800BC0AC(WpnObj_wpnshop* o, int k)
{
    WpnRect_wpnshop r;
    WpnBox_wpnshop b;
    r.x = 0x77;
    r.y = 0x5E;
    r.w = 0x45;
    r.h = 0x10;
    if (o->f_34 == k)
    {
        b.c_A = 1;
    }
    else
    {
        b.c_A = 2;
    }
    b.c_B = 1;
    b.x_0 = 0x7B;
    b.col_8 = uiColor_8008B590;
    b.y_2 = 0x61;
    sub_8002C06C(&b, 0x53, 0xE);
    b.x_0 = 0xB8;
    b.y_2 = 0x63;
    sub_8002C414(&b, o->f_18, 0xE);
    b.x_0 = 0x77;
    b.y_2 = 0x5E;
    sub_80042460(&r, &b.col_8, dword_8008D454 + 0x38, frameCount_8008D3FC);
}


// Matched
void sub_800BC194(WpnObj_wpnshop* o)
{
    WpnDlg_wpnshop cfg;
    cfg = name_800BADF0;
    cfg.f4 = sub_8002C64C();
    cfg.fC = o->f_30;
    cfg.f10 = (int)name_800BEAFC;
    sub_8002A5A4(&cfg);
}

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

// Matched
void sub_800BC268(WpnObj_wpnshop* o)
{
    WpnDlg_wpnshop cfg;
    cfg = name_800BADF0;
    cfg.f4 = sub_8002C64C();
    cfg.fC = o->f_30;
    cfg.f10 = (int)name_800BEBB4;
    sub_8002A5A4(&cfg);
}

// Matched
void sub_800BC2E4(WpnObj_wpnshop* o)
{
    int r = 0;
    if (o->f_12 == 1)
    {
        r = sub_800AD2C8(sub_800BE00C(o, 5), 0);
    }
    else if (o->f_12 == 0)
    {
        r = sub_800AD254(sub_800BDDB0(sub_800BE00C(o, 4), o->f_1E), 0);
    }
    sub_800BBFD4(r);
}

INCLUDE_OVERLAY_ASM(wpnshop, sub_800BC374);

// Matched
void sub_800BCABC(WpnObj_wpnshop* o, short k)
{
    WpnRect_wpnshop rect;
    WpnA384_wpnshop d;
    WpnBox2_wpnshop box;
    int cur = sub_800AD990(o->f_10);
    int s;
    int r = 0xFF;
    if (k == o->f_34)
    {
        s = o->f_30 + o->f_32;
    }
    else
    {
        s = o->f_36 + o->f_38;
    }
    if (k == 0xA)
    {
        if (s < o->f_20[o->f_10])
        {
            r = sub_800BDD2C(s, o->f_10, o->f_1E);
        }
        else
        {
            r = 0xFF;
        }
    }
    else if (k == 0xB)
    {
        r = sub_800AD288(s, o->f_10 + 1);
    }
    if (r != 0xFF && r == cur)
    {
        rect.x = 0x50;
        rect.y = 0x4D;
        rect.w = 0x26;
        rect.h = 0x10;
        d.a = 1;
        d.rect = &rect;
        d.frame = frameCount_8008D3FC;
        d.b = 0xE;
        box.x = 0x54;
        box.y = 0x50;
        sub_8002C06C(&box, 0xB6, 0xE);
        sub_8002A384(&d);
    }
}

// Matched
void sub_800BCC18(WpnObj_wpnshop* o)
{
    sub_800BC0AC(o, o->f_12 == 1 ? 0x12 : 0x11);
}

// Matched
void sub_800BCC4C(WpnObj_wpnshop* o)
{
    int r = 0;
    if (o->f_12 == 1)
    {
        r = sub_800AD2C8(sub_800BE00C(o, 0xB), o->f_10 + 1);
    }
    else if (o->f_12 == 0)
    {
        r = sub_800AD254(sub_800BDD2C(sub_800BE00C(o, 0xA), o->f_10, o->f_1E), o->f_10 + 1);
    }
    sub_800BBFD4(r);
}

// Matched
void sub_800BCCE8(WpnObj_wpnshop* o)
{
    char buf10[0x18];
    char buf28[0x18];
    WpnRect_wpnshop r40;
    WpnRect_wpnshop r48;
    WpnSmall_wpnshop s50;
    union
    {
        WpnPair_wpnshop p;
        WpnSmall_wpnshop s;
    } u;
    WpnRect_wpnshop r60;
    int r;
    sub_80033624(buf10, (int)levantStatus_8008BD38);
    r = sub_800BDD2C(sub_800BE00C(o, 0xA), o->f_10, o->f_1E);
    if (r != 0xFF)
    {
        if (o->f_0 != 0x11)
        {
            if (o->f_2 != 0x11)
            {
                sub_8002E288((int)levantStatus_8008BD38, r, o->f_10, buf28);
                r40.x = 0x119;
                r40.y = 0x73;
                sub_8002E188(buf10, buf28, &r40, 0xE);
            }
        }
    }
    r40.x = 0xC2;
    r40.y = 0x70;
    sub_8002F7D0(&r40, 0xE);
    r48.x = 0xC2;
    r48.y = 0x70;
    r48.w = 0x4B;
    r48.h = 0x4D;
    s50.b = 0;
    s50.c = 1;
    s50.a = WPNSAVE->f20;
    sub_80042460(&r48, &s50, dword_8008D454 + 0x38, 0);
    if (o->f_0 != 0x11)
    {
        u.p.a = 2;
        u.p.b = 0;
        r48.x = 0x112;
        r48.y = 0x95;
        sub_8002B3DC(u.p, frameCount_8008D3FC, &r48, 0xE);
        if (o->f_0 != 0x11)
        {
            r60.x = 0x119;
            r60.y = 0x70;
            r60.w = 0x1D;
            r60.h = 0x4D;
            u.s.b = 0;
            u.s.c = 1;
            u.s.a = WPNSAVE->f20;
            sub_80042460(&r60, &u.s, dword_8008D454 + 0x38, 0);
        }
    }
}

#if 0
// register allocation: original copies the ctx pointer to a1 (move a1,a0) and keeps the table in a0
void sub_800BCED4(WpnObj_wpnshop* o)
{
    int** tbl;
    switch (o->f_4C)
    {
    case 2:
        tbl = name_800BE3D8;
        break;
    case 3:
        tbl = name_800BE434;
        break;
    default:
        tbl = name_800BE37C;
        break;
    }
    name_800BE134[1] = tbl[o->f_3A][0];
    name_800BE134[3] = tbl[o->f_3A][1];
    name_800BE134[5] = tbl[o->f_3A][2];
}
#endif
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

void sub_800BCFCC(WpnObj_wpnshop* o)
{
    int v = 0;
    WpnRect_wpnshop r;
    WpnBox_wpnshop b;
    if (o->f_14 != 0xFF)
    {
        switch (o->f_34)
        {
        case 17:
        case 19:
            v = GETINT_8001CE54(o->f_14);
            break;
        case 16:
        case 18:
            v = GETINT_8001CE54(o->f_14) * 3 / 4;
            break;
        case 13:
        case 15:
            v = sub_8001D1F8(o->f_14, o->f_10);
            break;
        case 12:
        case 14:
            v = sub_8001D1F8(o->f_14, o->f_10) * 3 / 4;
            break;
        }
        r.x = 0xBD;
        r.y = 0x5E;
        r.w = 0x79;
        r.h = 0x10;
        b.c_B = 1;
        b.x_0 = 0xC1;
        b.col_8 = uiColor_8008B590;
        b.c_A = 0;
        b.y_2 = 0x60;
        sub_8002C06C(&b, 0xCE, 0xE);
        b.x_0 = 0x11D;
        b.y_2 = 0x64;
        sub_8002C414(&b, v * o->f_18, 0xE);
        b.x_0 = 0x11E;
        b.y_2 = 0x62;
        sub_8002C06C(&b, 0xEA, 0xE);
        sub_80042460(&r, &b.col_8, dword_8008D454 + 0x38, 0);
    }
}

// Matched
void sub_800BD174(WpnObj_wpnshop* o)
{
    sub_800BC0AC(o, o->f_12 == 1 ? 0xE : 0xD);
}

// Matched
void sub_800BD1A8(WpnObj_wpnshop* o)
{
    if (o->f_40)
    {
        if (o->f_30 != 2)
        {
            if (o->f_1C == 0)
            {
                o->f_2 = name_800BE868[o->f_30];
            }
            else if (o->f_1C == 1)
            {
                o->f_2 = name_800BE86C[o->f_30];
            }
            PlaySfx_80031494(0x7E);
            o->f_12 = o->f_30;
        }
        else
        {
            o->f_4 |= 2;
            PlaySfx_80031494(0x7D);
        }
    }
    else if (o->f_44)
    {
        if (o->f_30 != 2)
        {
            o->f_30 = 2;
            PlaySfx_80031494(0x7F);
        }
    }
}

// Matched
void sub_800BD278(WpnObj_wpnshop* o)
{
    int s = o->f_30 + o->f_32;
    int r;
    if (o->f_40)
    {
        r = sub_800BDF68((short)sub_800BDDB0(s, o->f_1E));
        if (r > 0)
        {
            if (o->f_12 == 0)
            {
                o->f_2 = 0xA;
            }
            else if (o->f_12 == 1)
            {
                o->f_2 = 0xB;
            }
            PlaySfx_80031494(0x7E);
        }
        else if (r < 0)
        {
            PlaySfx_80031494(0x7C);
            o->f_4E = 2;
            o->f_4 |= 1;
        }
        else
        {
            PlaySfx_80031494(0x7C);
            o->f_4E = 1;
            o->f_4 |= 1;
        }
        o->f_14 = sub_800BDDB0(s, o->f_1E);
    }
    else if (o->f_44)
    {
        o->f_2 = 0;
        o->f_36 = 0;
        o->f_38 = 0;
        PlaySfx_80031494(0x7D);
    }
}

// Matched
void sub_800BD378(WpnObj_wpnshop* o)
{
    int s = o->f_30 + o->f_32;
    int r;
    sub_800AD288(s, 0);
    r = sub_800AD2C8(s, 0);
    if (o->f_40)
    {
        if (r)
        {
            o->f_14 = sub_800AD288(s, 0);
            if (o->f_12 == 0)
            {
                o->f_2 = 0xA;
            }
            else if (o->f_12 == 1)
            {
                o->f_2 = 0xB;
            }
            PlaySfx_80031494(0x7E);
        }
        else
        {
            PlaySfx_80031494(0x7C);
        }
    }
    else if (o->f_44)
    {
        o->f_2 = 0;
        o->f_36 = 0;
        o->f_38 = 0;
        PlaySfx_80031494(0x7D);
    }
}

// Matched
void sub_800BD444(WpnObj_wpnshop* o)
{
    if (o->f_40 && o->f_30 == 0)
    {
        if (o->f_12 == 0)
        {
            if (o->f_1C == 0)
            {
                sub_800BDC40(o->f_14, o->f_10, o->f_18);
            }
            else if (o->f_1C == 1)
            {
                sub_800BDB80(o->f_14, o->f_18);
            }
        }
        else if (o->f_12 == 1)
        {
            if (o->f_1C == 0)
            {
                sub_800BDCB4(o->f_14, o->f_10, o->f_18);
            }
            else if (o->f_1C == 1)
            {
                sub_800BDBDC(o->f_14, o->f_18);
            }
        }
        PlaySfx_80031494(0x7E);
    }
    else if ((o->f_40 && o->f_30 == 1) || o->f_44)
    {
        PlaySfx_80031494(0x7D);
    }
    if (o->f_40 || o->f_44)
    {
        if (o->f_1C == 0)
        {
            if (o->f_40)
            {
                if (o->f_12 == 0 && o->f_30 == 0 && sub_800BD71C(o->f_14, o->f_10) == 0)
                {
                    o->f_2 = 0x10;
                }
                else
                {
                    o->f_2 = name_800BE870[o->f_12];
                }
            }
            else if (o->f_44)
            {
                o->f_2 = name_800BE870[o->f_12];
            }
        }
        else if (o->f_1C == 1)
        {
            o->f_2 = name_800BE86C[o->f_12];
        }
    }
}

// Matched
void sub_800BD61C(WpnObj_wpnshop* o)
{
    if (o->f_40)
    {
        if (o->f_30 == 0)
        {
            PlaySfx_80031494(0x7E);
            sub_800AD9EC(o->f_14, o->f_10);
            o->f_2 = 0x11;
            return;
        }
        if (o->f_30 == 1)
        {
            goto snd;
        }
    }
    if (o->f_44)
    {
    snd:
        PlaySfx_80031494(0x7D);
        o->f_2 = 0x12;
    }
}

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

// Matched
void sub_800BD760(WpnObj_wpnshop* o)
{
    int prev = o->f_18;
    int v = 0;
    switch (o->f_0)
    {
    case 8:
        v = sub_800BDE38((short)o->f_14, o->f_10);
        break;
    case 9:
        v = sub_800AD2C8(o->f_36 + o->f_38, o->f_10 + 1);
        break;
    case 10:
        v = sub_800BDF68((short)o->f_14);
        break;
    case 11:
        v = sub_800AD2C8(o->f_36 + o->f_38, 0);
        break;
    }
    o->f_18 = sub_800BE084(o->f_18, v);
    if (o->f_18 != prev)
    {
        PlaySfx_80031494(0x7F);
    }
    if (o->f_40)
    {
        PlaySfx_80031494(0x7E);
        switch (o->f_0)
        {
        case 8:
            o->f_2 = 0xC;
            break;
        case 9:
            o->f_2 = 0xD;
            break;
        case 10:
            o->f_2 = 0xE;
            break;
        case 11:
            o->f_2 = 0xF;
            break;
        }
    }
    else if (o->f_44)
    {
        PlaySfx_80031494(0x7D);
        switch (o->f_0)
        {
        case 8:
            o->f_2 = 4;
            break;
        case 9:
            o->f_2 = 5;
            break;
        case 10:
            o->f_2 = 2;
            break;
        case 11:
            o->f_2 = 3;
            break;
        }
    }
}

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

// Matched
void sub_800BD9A8(WpnObj_wpnshop* o)
{
    int s = o->f_32 + o->f_30;
    int r;
    if (o->f_40)
    {
        r = sub_800BDE38((short)sub_800BDD2C(s, o->f_10, o->f_1E), o->f_10);
        if (r > 0)
        {
            PlaySfx_80031494(0x7E);
            if (o->f_12 == 0)
            {
                o->f_2 = 8;
            }
            else if (o->f_12 == 1)
            {
                o->f_2 = 9;
            }
        }
        else if (r < 0)
        {
            PlaySfx_80031494(0x7C);
            o->f_4E = 2;
            o->f_4 |= 1;
        }
        else
        {
            PlaySfx_80031494(0x7C);
            o->f_4E = 1;
            o->f_4 |= 1;
        }
        o->f_14 = sub_800BDD2C(s, o->f_10, o->f_1E);
    }
    else if (o->f_44)
    {
        PlaySfx_80031494(0x7D);
        o->f_2 = 6;
    }
}

// Matched
void sub_800BDAB4(WpnObj_wpnshop* o)
{
    int s = o->f_30 + o->f_32;
    if (o->f_40)
    {
        if (sub_800AD2C8(s, o->f_10 + 1))
        {
            PlaySfx_80031494(0x7E);
            o->f_14 = sub_800AD288(s, o->f_10 + 1);
            if (o->f_12 == 0)
            {
                o->f_2 = 8;
            }
            else if (o->f_12 == 1)
            {
                o->f_2 = 9;
            }
        }
        else
        {
            PlaySfx_80031494(0x7C);
        }
    }
    else if (o->f_44)
    {
        PlaySfx_80031494(0x7D);
        o->f_2 = 7;
    }
}

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
short sub_800BE00C(WpnObj_wpnshop* o, short i)
{
    if (i == o->f_34)
    {
        return (short)(o->f_30 + o->f_32);
    }
    return (short)(o->f_36 + o->f_38);
}

// Matched
short sub_800BE058(WpnObj_wpnshop* o, short i)
{
    if (i == o->f_34)
    {
        return o->f_30;
    }
    return o->f_36;
}

#if 0
// register allocation: original copies a to a new reg, keeps b in a1
int sub_800BE084(int a, int b)
{
    int n = a;
    int t;
    if ((padRepeat_800918CC & 0x1000) && (t = n + 1, t <= b))
    {
        n = t;
    }
    else if (padRepeat_800918CC & 0x4000)
    {
        if (n - 1 > 0)
        {
            n = n - 1;
        }
    }
    n = sub_8003D198(b + 1, n, 10, 0);
    if (n == 0)
    {
        n = 1;
    }
    return n;
}
#endif
INCLUDE_OVERLAY_ASM(wpnshop, sub_800BE084);

INCLUDE_OVERLAY_ASM(wpnshop, dword_800BE110);
