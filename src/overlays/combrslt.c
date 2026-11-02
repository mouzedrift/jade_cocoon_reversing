// COMBRSLT.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct CombRsltTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombRsltTask;

typedef struct CombRsltBox
{
    short col_0;
    char c_2;
    char c_3;
} CombRsltBox;

typedef struct CombRsltStr
{
    int w[7];
} CombRsltStr;

extern CombRsltStr dword_800A408C;
extern unsigned short uiColor_8008B590;
extern char dword_80082680[];
extern void sub_8002ADB4(void*, void*, int, int);
extern void sub_8002B004(void*, int, int);
extern void sub_800A41E4();
extern void sub_8002C290(void*, int, int);
extern void sub_8002C06C(void*, int, int);
extern void sub_800A16FC();
extern void sub_8001C19C(int, int);
extern void sub_800A4240(int);
extern void sub_8002BE10();

INCLUDE_OVERLAY_ASM(combrslt, dword_800A4088);

void sub_800A40E0(CombRsltTask* t)
{
    CombRsltBox box;
    CombRsltStr str = dword_800A408C;
    int i;
    box.c_2 = 0;
    box.c_3 = 1;
    box.col_0 = uiColor_8008B590;
    sub_8002ADB4(&str, &box, 0xF, 0);
    for (i = 0; i < 2; i++)
    {
        sub_800A4240(i);
    }
    sub_8002BE10();
    sub_8002B004(dword_80082680, 0, 0xF);
    if (sub_8003D380(1) || sub_8003D41C(1))
    {
        sub_8001C19C(1, 0x20);
        t->next_8 = sub_800A41E4;
    }
}

void sub_800A41E4(CombRsltTask* t, int a)
{
    if (sub_8001C2FC() == 1)
    {
        sub_8001C19C(3, 0x20);
        t->next_8 = sub_800A16FC;
        t->next_8(t, a);
    }
}

INCLUDE_OVERLAY_ASM(combrslt, sub_800A4240);

// Near miss: scheduling of the repeated x/y stores
#if 0
void sub_800A444C(unsigned short* p, int a, int b, int c)
{
    short v[2];
    unsigned int x;
    unsigned int y;
    x = p[0];
    v[0] = x + 0x1C;
    y = p[1];
    v[0] = x + 0x12;
    v[1] = y + 4;
    v[1] = y + 7;
    sub_8002C290(v, b, a);
    x = p[0];
    v[0] = x + 0x1C;
    y = p[1];
    v[0] = x + 0x14;
    v[1] = y + 5;
    sub_8002C06C(v, 0xAE, a);
    x = p[0];
    v[0] = x + 0x43;
    y = p[1];
    v[0] = x + 0x39;
    v[1] = y + 4;
    v[1] = y + 7;
    sub_8002C290(v, c, a);
    x = p[0];
    v[0] = x + 0x43;
    y = p[1];
    v[0] = x + 0x3B;
    v[1] = y + 5;
    sub_8002C06C(v, 0x4D, a);
}
#endif
INCLUDE_OVERLAY_ASM(combrslt, sub_800A444C);

INCLUDE_OVERLAY_ASM(combrslt, sub_800A4554);

INCLUDE_OVERLAY_ASM(combrslt, dword_800A47E8);
