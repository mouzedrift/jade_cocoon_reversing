// MAP.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct MapTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} MapTask;

typedef struct MapRow
{
    int f0;
    int f4;
    int f8;
    int fc;
    int f10;
    int f14;
} MapRow;

extern int dword_800B9430;
extern int dword_800B9314;
extern int dword_800B9318;
extern int dword_800B931C;
extern int dword_800B9320;
extern int dword_800B9434;
extern int dword_800B9438;
extern int dword_800B9420[4];
extern int dword_800B9400[];
extern MapRow dword_800B9220[];
extern unsigned short word_800AEBF8[2];
extern unsigned short dword_800B8C94[2];
extern void sub_800B8448(void*);
extern short word_800B932C;
extern void sub_8001C19C(int, int);
extern void sub_8001CD04(int);
extern void sub_8003BC84(void*);
extern void sub_800B6CB4();
extern void sub_800B6C7C();
extern void sub_800B6DE0(MapTask*, int);
extern void sub_800B6E80();
extern void sub_800B6EE8();
extern void sub_800B6FAC(MapTask*);
extern void sub_800B7044();
extern void sub_800B7980();
extern void sub_800B7A90();
extern void sub_800B860C();
extern void sub_800B8B5C();

INCLUDE_OVERLAY_ASM(map, dword_800B66C0);

// Matched
void sub_800B6BFC(MapTask* t, int a1)
{
    void (*f)();
    dword_800B8C94[0] = word_800AEBF8[0];
    dword_800B8C94[1] = word_800AEBF8[1];
    sub_800B8448(word_800AEBF8);
    f = sub_800B6C7C;
    t->next_8 = f;
    f(t, a1);
    t->flags_0 = (t->flags_0 | 4) & 0xFFFF7FFF;
}

// Matched
void sub_800B6C7C(MapTask* t)
{
    sub_8001C19C(0, 0x20);
    t->next_8 = sub_800B6CB4;
}

INCLUDE_OVERLAY_ASM(map, sub_800B6CB4);

// Matched
void sub_800B6D90(int* p, int a1)
{
    dword_800B9430 = 0;
    p[0] = 0x2C;
    p[1] = a1;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = 0;
    p[6] = 0;
    p[7] = (int)sub_800B6DE0;
    sub_8003BC84(p);
}

// Matched
void sub_800B6DE0(MapTask* t, int a1)
{
    sub_800B6FAC(t);
    if (dword_800B9434 == 1)
    {
        sub_80028E74(&dword_800B931C, 0, &dword_800B9320, a1, 1);
    }
    else
    {
        sub_80028E74(&dword_800B9314, 0, &dword_800B9318, a1, 1);
    }
    dword_800B9430 = 1;
}

// Matched
void sub_800B6E5C(MapTask* t)
{
    if (dword_800B9430)
    {
        t->next_8 = sub_800B6E80;
    }
}

// Matched
void sub_800B6E80(MapTask* t)
{
    dword_800B9434 = 1;
    sub_800B6D90(dword_800B9400, dword_800B9220[(short)word_800AEBF8[0]].f4);
    t->next_8 = sub_800B6EE8;
}

// Matched
void sub_800B6EE8(MapTask* t, int a1)
{
    if (dword_800B9430 && sub_8001C2FC())
    {
        t->next_8 = sub_800B7044;
        sub_8001CD04(0);
        t->next_8(t, a1);
        sub_8001C19C(3, 0x20);
    }
}

// Matched
void sub_800B6F60(MapTask* t)
{
    sub_800B6FAC(t);
    t->flags_0 &= ~4;
    unknownFlags_8008D678 &= 0xFBFFFFFF;
}

INCLUDE_OVERLAY_ASM(map, sub_800B6FAC);

INCLUDE_OVERLAY_ASM(map, sub_800B7044);

// Matched
void sub_800B7948(MapTask* t)
{
    sub_8001C19C(0, 0x20);
    t->next_8 = sub_800B7980;
}

INCLUDE_OVERLAY_ASM(map, sub_800B7980);

// Matched
void sub_800B7A38(MapTask* t)
{
    if (dword_800B9430 && sub_8001C2FC())
    {
        t->next_8 = sub_800B7A90;
        sub_8001C19C(3, 0x20);
        word_800B932C = 0;
    }
}

INCLUDE_OVERLAY_ASM(map, sub_800B7A90);

INCLUDE_OVERLAY_ASM(map, sub_800B7E54);

INCLUDE_OVERLAY_ASM(map, sub_800B7EE0);

INCLUDE_OVERLAY_ASM(map, sub_800B8128);

INCLUDE_OVERLAY_ASM(map, sub_800B81D0);

INCLUDE_OVERLAY_ASM(map, sub_800B8290);

INCLUDE_OVERLAY_ASM(map, sub_800B8338);

INCLUDE_OVERLAY_ASM(map, sub_800B8448);

// Matched
void sub_800B85CC(MapTask* t)
{
    int* p;
    void (*f)() = sub_800B860C;
    dword_800B9420[0] = 0;
    p = dword_800B9420;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    t->next_8 = f;
    f();
}

INCLUDE_OVERLAY_ASM(map, sub_800B860C);

// Matched
void sub_800B8B2C(MapTask* t)
{
    void (*f)() = sub_800B8B5C;
    dword_800B9438 = 0;
    t->next_8 = f;
    f();
}

INCLUDE_OVERLAY_ASM(map, sub_800B8B5C);

INCLUDE_OVERLAY_ASM(map, dword_800B8C94);
