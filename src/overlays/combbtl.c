// COMBBTL.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct CombBtlTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombBtlTask;

typedef struct CombBtl4
{
    int a;
    int b;
    int c;
    int d;
} CombBtl4;

extern short word_800A82E0[4];
extern int* dword_8008B564;
extern int dword_800A85A0;
extern CombBtl4 dword_800A8600;
extern CombBtl4 dword_800A85A8;
extern int dword_800A4078[2];
extern unsigned char byte_800A3A98[2];
extern short word_800A84D0[2];
extern void sub_800A0D1C(int);
extern void sub_800A0B70(int);
extern void sub_8001C02C(void*);
extern void sub_800376A0(int*, int);
typedef struct CombBtlUnit
{
    char pad_0[0xF8];
} CombBtlUnit;

typedef struct CombBtlHist
{
    int a;
    char pad_4[0x10];
} CombBtlHist;

extern CombBtlUnit dword_800A3AA0[2][3];
extern CombBtlHist dword_800A84D8[];
extern int dword_8008D778;
extern void sub_8001A38C();
extern void sub_8001A41C();
extern int sub_800A1958(void*);
extern int sub_800A10DC(int);
extern void sub_800A7EFC();
typedef struct CombBtlObj
{
    int a;
    int b;
    short x;
    short y;
    short w;
    short h;
} CombBtlObj;

typedef struct CombBtlPair
{
    short lo;
    short hi;
} CombBtlPair;

extern short word_800A82D4[][2];
extern void sub_800A7694();
typedef struct CombBtlA24
{
    int w[6];
} CombBtlA24;

typedef struct CombBtlB16
{
    char c[16];
} CombBtlB16;

extern CombBtlA24 dword_800A4AD4;
extern CombBtlB16 dword_800A4AEC;
extern void sub_800A0BA8(int, void*, void*);
typedef struct CombBtlD
{
    short s0;
    short s2;
    int w[8];
    short s24;
    short s26;
} CombBtlD;

extern CombBtlD dword_800A85C8;
extern int dword_800A85B8;
extern int dword_800A8620;
extern int xarr_800A85B8[1];
extern int xarr_800A8620[1];
extern CombBtl4 dword_800A8610;
extern int dword_800A84C0;
extern int dword_800A84A0;
extern int dword_800A8498;
extern int dword_800A849C;
extern unsigned char byte_800A38DC;
extern int dword_800A84B8;
extern int dword_800A85F8;
extern short word_800A8488;
extern void sub_800A4C40();
extern void sub_800A4D48();
extern void sub_800A68E0();
extern void sub_800A616C();
extern void sub_800A5000();
extern void sub_80039FA4(int);
extern void sub_800A0A28();
extern void sub_800300E0(int, int);
extern void sub_800A5EF8();
extern void sub_800A5F60();
extern void sub_800A50E4();
extern void sub_800A5544();
extern void sub_800A5BB4();
extern void sub_800A5080();
extern int dword_800A848C;
extern int dword_800A84D4;
extern int* dword_800A84B0[2];
extern short word_80091CE0[];
extern char dword_80091D40[];
extern short word_800A84A4;
extern short word_800A84A6;
extern short word_800A84BC;
extern short word_800A84C4;
extern short word_800A8470[2];
extern short word_800A8474[2];
extern int dword_800A8480[2];
extern int dword_800A85F0[2];
extern int sub_800CB7AC(void*, int);
extern int sub_800A0B3C(int);
extern void sub_80031334(int);
extern void sub_80030D68(int);
extern void sub_80030664();
extern void sub_8006281C(int, int, int, int);
extern void sub_8001AA50(int);
extern void sub_80031160(int, int);

INCLUDE_OVERLAY_ASM(combbtl, dword_800A4088);

void sub_800A4B8C(CombBtlTask* t, int a)
{
    dword_800A85A0 = LoadOverlay_80020BF8(1, 6);
    dword_800A84C0 = (unsigned int)gnFrame_8008D610 % 39;
    t->next_8 = sub_800A4C40;
    t->next_8(t, a);
    sub_80030D68((int)word_80091CE0);
    sub_800300E0(0, 1);
}

void sub_800A4C40(CombBtlTask* t, int a)
{
    if (sub_8003BE30(dword_800A85A0) == 0)
    {
        dword_800A84A0 = -1;
        dword_800A8498 = -1;
        dword_800A849C = -1;
        byte_800A38DC = 2;
        dword_800A85B8 = -1;
        dword_800A8620 = -1;
        sub_80039FA4(dword_800A84C0);
        sub_800A0A28();
        dword_800A84B8 = 0;
        dword_800A85F8 = -1;
        sub_800A4CFC();
        t->next_8 = sub_800A4D48;
        t->next_8(t, a);
    }
}

void sub_800A4CFC()
{
    unsigned int i;
    for (i = 0; i < 2; i++)
    {
        dword_800A4078[i] = -1;
        byte_800A3A98[i] = 0;
        word_800A84D0[i] = 0;
    }
}

INCLUDE_OVERLAY_ASM(combbtl, sub_800A4D48);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A4EC8);

void sub_800A5000(CombBtlTask* t)
{
    if (word_80091CE0[2] >= 0)
    {
        sub_8006281C(word_80091CE0[6], word_80091CE0[2], 0x7F, 0x78);
        word_80091CE0[2] = -1;
    }
    sub_80031334(0);
    sub_80031160(1, 1);
    dword_800A84D4 = 0x78;
    t->next_8 = sub_800A5080;
}

void sub_800A5080(CombBtlTask* t)
{
    if (--dword_800A84D4 <= 0)
    {
        sub_800313C8(0);
        sub_80031334(0);
        sub_80030D68(dword_80091D40);
        sub_80030664();
        t->next_8 = sub_800A50E4;
    }
}

INCLUDE_OVERLAY_ASM(combbtl, sub_800A50E4);

extern void sub_800A8078(short, short, short);
extern int sub_800A8098();
extern void sub_800A5290();
extern char dword_800A82EC[];
extern char dword_800A8300[];
extern int dword_800A82DC;

void sub_800A51EC(CombBtlTask* t)
{
    if (--dword_800A84D4 <= 0)
    {
        if (dword_800A85F8 == 1)
        {
            sub_800A8078(7, 0x3BC, 0x1B);
            dword_800A82DC = sub_800A8098(0, dword_800A82EC, 1);
        }
        else
        {
            sub_800A8078(9, 0x3BF, 0x1F);
            dword_800A82DC = sub_800A8098(0, dword_800A8300, 0);
        }
        t->next_8 = sub_800A5290;
    }
}

INCLUDE_OVERLAY_ASM(combbtl, sub_800A5290);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A5408);

void sub_800A54CC(CombBtlTask* t)
{
    sub_800313C8(0);
    if (word_80091CE0[2] >= 0)
    {
        sub_8006281C(word_80091CE0[6], word_80091CE0[2], 0x7F, 0x78);
        word_80091CE0[2] = -1;
    }
    sub_8001AA50(0x1E);
    sub_800A7BE4();
    t->next_8 = sub_800A5544;
}

INCLUDE_OVERLAY_ASM(combbtl, sub_800A5544);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A5638);

void sub_800A58E8(int i)
{
    CombBtlUnit* u;
    do
    {
        dword_800A4078[i]++;
        if (dword_800A4078[i] >= 3)
        {
            dword_800A4078[i] = 0;
        }
        u = &dword_800A3AA0[i][dword_800A4078[i]];
    } while (sub_800A1934(u) || sub_800A1958(u));
}

INCLUDE_OVERLAY_ASM(combbtl, sub_800A599C);

int sub_800A5B70(int a)
{
    int r;
    int v;
    unsigned char buf[0x18];
    r = sub_80014390((a + 8) & 0xFF);
    if (r)
    {
        sub_80033624(buf, r);
        v = buf[4] + 0xA;
    }
    else
    {
        v = 0;
    }
    return v;
}

// Near miss: the original loads the two shift counts only after all the stores
#if 0
void sub_800A5BB4()
{
    dword_800A8600.a = 0x14;
    dword_800A8600.b = 0;
    dword_800A85A8.a = 0x14;
    dword_800A85A8.b = 0;
    dword_800A8610.a = 0x14;
    dword_800A8610.b = 0;
    dword_800A85C8.s0 = 0;
    dword_800A85C8.s24 = -1;
    dword_800A85C8.s26 = -1;
    dword_800A85C8.s2 = 0;
    dword_800A85C8.w[0] = 0;
    dword_800A85C8.w[1] = 0;
    dword_800A85C8.w[2] = 0;
    dword_800A85C8.w[3] = 0;
    dword_800A85C8.w[4] = 0;
    dword_800A85C8.w[5] = 0;
    dword_800A85C8.w[6] = 0;
    dword_800A85C8.w[7] = 0;
    dword_800A8600.c = 1 << (xarr_800A85B8[0] + 8);
    dword_800A8600.d = 1 << (xarr_800A8620[0] + 8);
    dword_800A85A8.c = 1 << (xarr_800A85B8[0] + 8);
    dword_800A85A8.d = 1 << (xarr_800A8620[0] + 8);
    dword_800A8610.c = 1 << (xarr_800A8620[0] + 8);
    dword_800A8610.d = 1 << (xarr_800A85B8[0] + 8);
}
#endif
INCLUDE_OVERLAY_ASM(combbtl, sub_800A5BB4);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A5C64);

void sub_800A5EB8(CombBtlTask* t)
{
    dword_800A85A0 = LoadOverlay_80020BF8(1, 0x19);
    t->next_8 = sub_800A5EF8;
}

void sub_800A5EF8(CombBtlTask* t)
{
    if (sub_8003BE30(dword_800A85A0) == 0)
    {
        sub_800A5BB4();
        dword_800A848C = sub_800CB7AC(&dword_800A8600, dword_800A85B8);
        t->next_8 = sub_800A5F60;
    }
}

void sub_800A5F60(CombBtlTask* t, int a)
{
    if ((*(unsigned int*)dword_800A848C & 0x8001) != 1)
    {
        sub_800A601C();
        if (byte_800A38DC)
        {
            byte_800A3A98[dword_800A85B8] = 2;
            t->next_8 = sub_800A5000;
            t->next_8(t, a);
        }
        else
        {
            sub_800A60A4();
            sub_800A616C();
            word_800A8488 = 0;
            t->next_8 = sub_800A68E0;
        }
    }
}

void sub_800A601C()
{
    int i;
    for (i = 10; i > 0; i--)
    {
        sub_800403E8((unsigned int*)&dword_800A84D8[i], (unsigned int*)&dword_800A84D8[i - 1], 0x14);
    }
    dword_800A84D8[0].a = dword_800A85B8;
    sub_800403E8((unsigned int*)((char*)dword_800A84D8 + 4), (unsigned int*)&dword_800A8600, 0x10);
}

void sub_800A60A4()
{
    int a = dword_800A8600.a;
    dword_800A85A8.a = a;
    dword_800A85A8.b = dword_800A8600.b;
    dword_800A85A8.c = dword_800A8600.c;
    dword_800A85A8.d = dword_800A8600.d;
    if (a == 8)
    {
        dword_800A85A8.a = 3;
        dword_800A85A8.b = 0;
    }
}

void sub_800A60F0()
{
    unsigned int i;
    word_800A84A4 = -1;
    word_800A84A6 = -1;
    word_800A84BC = 0;
    word_800A84C4 = 0;
    for (i = 0; i < 2; i++)
    {
        word_800A8470[i] = 0;
        word_800A8474[i] = 0;
        dword_800A8480[i] = 0;
        dword_800A85F0[i] = 0;
    }
}

INCLUDE_OVERLAY_ASM(combbtl, sub_800A616C);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A68E0);

int sub_800A7164(int i)
{
    int cnt = 0;
    int j;
    for (j = 0; j < 3; j++)
    {
        if (sub_800A1958(&dword_800A3AA0[i][j]) == 0)
        {
            cnt++;
        }
    }
    return cnt;
}

// Near miss: register assignment of the two element pointers
#if 0
CombBtlPair sub_800A71E4(int n, CombBtlPair* p)
{
    CombBtlPair r;
    short hi = 0;
    short lo = hi;
    int i;
    for (i = 0; i < n; i++)
    {
        p[i].hi = p[i].hi - p[i].lo;
        p[i].lo = -p[i].lo;
        if (p[i].lo < lo)
        {
            lo = p[i].lo;
        }
        if (hi < p[i].hi)
        {
            hi = p[i].hi;
        }
    }
    r.lo = lo;
    r.hi = hi;
    return r;
}
#endif
INCLUDE_OVERLAY_ASM(combbtl, sub_800A71E4);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A7290);

void sub_800A73E4()
{
    sub_800376A0((int*)dword_8008D4A0 + 4, dword_8008D4A0[9]);
    sub_80043B40((int*)dword_8008D4A0);
}

void sub_800A7420()
{
    EventEntry* e = sub_80043AF8((EventNode*)dword_8008D628);
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        sub_8001A38C();
        e->cb_8 = (EventEntryFn)sub_8001A41C;
    }
}

void sub_800A7478()
{
    sub_80043B40((int*)dword_8008D628);
}

void sub_800A74A0(int i)
{
    CombBtlA24 a = dword_800A4AD4;
    CombBtlB16 b = dword_800A4AEC;
    sub_800A0BA8(i, (char*)&a + i * 12, (char*)&b + i * 8);
}

void sub_800A7560(int a)
{
    sub_800A0D1C(a);
    sub_800A0B70(a);
}

int sub_800A758C()
{
    unsigned int i;
    for (i = 0; i < 2; i++)
    {
        if (dword_800A84B0[i])
        {
            if (sub_800A0B3C(i) == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

void sub_800A75F8(int a)
{
    EventEntry* e = sub_80043AF8((EventNode*)dword_8008B564);
    CombBtlObj* p;
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        p = (CombBtlObj*)e->buffer;
        p->a = a;
        p->b = 0;
        p->x = word_800A82D4[a][0];
        p->y = word_800A82D4[a][1];
        p->w = 0x64;
        p->h = 0x29;
        e->cb_8 = (EventEntryFn)sub_800A7694;
    }
}

INCLUDE_OVERLAY_ASM(combbtl, sub_800A7694);

void sub_800A7BE4()
{
    sub_80043B40(dword_8008B564);
}

INCLUDE_OVERLAY_ASM(combbtl, sub_800A7C0C);

void sub_800A7E34(int a, int b, int c)
{
    EventEntry* e = sub_80043AF8((EventNode*)dword_8008D778);
    int* p;
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        p = (int*)e->buffer;
        p[0] = b;
        p[2] = 0;
        p[1] = c;
        p[6] = a;
        p[4] = sub_800A10DC(a);
        e->cb_8 = (EventEntryFn)sub_800A7EFC;
    }
}

void sub_800A7ECC()
{
    unsigned char c[3];
    c[0] = 0xFF;
    c[1] = 0xFF;
    c[2] = 0xFF;
    sub_8001C02C(c);
}

INCLUDE_OVERLAY_ASM(combbtl, sub_800A7EFC);

void sub_800A8078(short a, short b, short c)
{
    word_800A82E0[0] = 1;
    word_800A82E0[1] = a;
    word_800A82E0[2] = b;
    word_800A82E0[3] = c;
}

INCLUDE_OVERLAY_ASM(combbtl, sub_800A8098);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A816C);

INCLUDE_OVERLAY_ASM(combbtl, dword_800A82D0);
