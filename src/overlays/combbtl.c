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
extern void sub_800A5EF8();

INCLUDE_OVERLAY_ASM(combbtl, dword_800A4088);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A4B8C);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A4C40);

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

INCLUDE_OVERLAY_ASM(combbtl, sub_800A5000);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A5080);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A50E4);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A51EC);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A5290);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A5408);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A54CC);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A5544);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A5638);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A58E8);

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

INCLUDE_OVERLAY_ASM(combbtl, sub_800A5BB4);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A5C64);

void sub_800A5EB8(CombBtlTask* t)
{
    dword_800A85A0 = LoadOverlay_80020BF8(1, 0x19);
    t->next_8 = sub_800A5EF8;
}

INCLUDE_OVERLAY_ASM(combbtl, sub_800A5EF8);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A5F60);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A601C);

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

INCLUDE_OVERLAY_ASM(combbtl, sub_800A60F0);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A616C);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A68E0);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A7164);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A71E4);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A7290);

void sub_800A73E4()
{
    sub_800376A0((int*)dword_8008D4A0 + 4, dword_8008D4A0[9]);
    sub_80043B40((int*)dword_8008D4A0);
}

INCLUDE_OVERLAY_ASM(combbtl, sub_800A7420);

void sub_800A7478()
{
    sub_80043B40((int*)dword_8008D628);
}

INCLUDE_OVERLAY_ASM(combbtl, sub_800A74A0);

void sub_800A7560(int a)
{
    sub_800A0D1C(a);
    sub_800A0B70(a);
}

INCLUDE_OVERLAY_ASM(combbtl, sub_800A758C);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A75F8);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A7694);

void sub_800A7BE4()
{
    sub_80043B40(dword_8008B564);
}

INCLUDE_OVERLAY_ASM(combbtl, sub_800A7C0C);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A7E34);

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
