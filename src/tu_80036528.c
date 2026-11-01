#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "STDLIB.H"
#include "STDIO.H"
#include "LIBPAD.H"
#include "LIBSND.H"
#include "LIBMCX.H"
#include "LIBPRESS.H"
#include "LIBETC.H"
#include "LIBMCRD.H"
#include "sound.h"
#include "data_decls.h"


INCLUDE_ASM(sub_80036528);
// Matched
void sub_80036658(int idx)
{
    byte_80095460[(unsigned char)idx].field_2 = 0;
    byte_80095460[(unsigned char)idx].field_3 = 0;
}
// Matched
void sub_80036678(void)
{
    sub_80036658(0);
    sub_80036658(1);
}
INCLUDE_ASM(sub_800366A0);
// Matched
void sub_800367F0(int a0, unsigned char* a1)
{
    byte_80095460[*a1].field_2 = 0;
    byte_80095460[*a1].field_3 = 0;
}
#if 0
void sub_80036820(int a0)
{
}
#endif
INCLUDE_ASM(sub_80036820);
INCLUDE_ASM(sub_800368F8);
INCLUDE_ASM(sub_800369E0);
INCLUDE_ASM(sub_80036AB4);
INCLUDE_ASM(sub_80036BB0);
INCLUDE_ASM(sub_800374E0);
extern void sub_80038230(int* p);
extern void sub_80037918(int* p);
extern void sub_8003891C(int* p, void* q);
extern void sub_800368F8(void);
extern char levantPos_8008BD18[];
extern int dword_8008B4F8;
// Matched
void sub_800375F8(int* o, int* p)
{
    int* q = p;
    if (p[3] > 0)
    {
        sub_80038230(p);
        if (p[3] > 0)
        {
            p[3] -= 0x1000;
        }
        if (p[3] < 0)
        {
            p[3] = 0;
        }
    }
    else
    {
        sub_80039698(q);
        sub_80037918(q);
        sub_8003891C(q, levantPos_8008BD18);
        ((short*)q)[4] = 0;
        o[2] = (int)sub_800368F8;
    }
}
// Matched
void nullsub_5(void)
{
}
extern void sub_80039E14(void);
extern int geomScreenDistance_8008B548;
extern short word_8008D51E;
// Matched
void sub_800376A8(void)
{
    int* p = dword_8008D4A0[0x24 / 4];
    short* sp;
    sub_80039E14();
    dword_8008B4F8 = 0x1000;
    geomScreenDistance_8008B548 = (word_8008D51E << 12) / 0x1000;
    sp = (short*)p;
    p[1] = 0;
    sp[4] = 0;
    sp[0x24 / 2] = 0;
    sp[0x26 / 2] = 0x1000;
    p[0] = (int)levantPos_8008BD18;
}
// Matched
void sub_80037720(void)
{
    int* p = dword_8008D4A0[0x24 / 4];
    p[1] |= 0x2000;
}
// Matched
void sub_80037748(void)
{
    int* p = dword_8008D4A0[0x24 / 4];
    p[1] |= 4;
}
// Matched
void sub_80037770(void)
{
    int* p = dword_8008D4A0[0x24 / 4];
    p[1] &= ~4;
    p[1] &= ~0x2000;
    sub_80039698(p);
}
extern int dword_80083D00[];
extern int dword_80084330[];
extern void sub_8003970C(int a, int* b);
extern void sub_8003983C(int a, int* b);
// Matched
void sub_800377B4(int a0, short a1)
{
    if (a0 == 0)
    {
        if (a1 == 5 || a1 == 0x1A)
        {
            sub_8003970C(a1, dword_80083D00);
        }
    }
    else if (a0 == 1)
    {
        if (a1 == 2)
        {
            sub_8003983C(2, dword_80084330);
        }
    }
}
// Table in the overlay area (outside the linked image), 8 bytes per entry
extern int dword_800B1084[];
__asm__(".globl dword_800B1084\n.equ dword_800B1084,0x800b1084");
// Matched
void sub_80037828(int a, short b, int c)
{
    void* p = dword_8008D4A0[0x24 / 4];
    if (c)
    {
        sub_800390F4(p, 2);
    }
    else if (a == 0)
    {
        if (dword_800B1084[b * 2] != 0x10 && b != 0x11 && b != 0x12)
        {
            sub_800390F4(p, 1);
        }
    }
    else if (a != 1 || (unsigned short)(b - 0x11) >= 2)
    {
        sub_800390F4(p, 1);
    }
}
// Matched
void sub_800378CC(void)
{
    sub_800390F4(dword_8008D4A0[0x24 / 4], 1);
}
// Matched
short sub_800378F8(void)
{
    return ((short*)dword_8008D4A0[0x24 / 4])[4];
}
INCLUDE_ASM(sub_80037918);
// Matched
short sub_80037A4C(void)
{
    return ((short*)dword_8008D4A0[0x24 / 4])[0x12];
}
// Matched
void sub_80037A6C(int a, int b)
{
    int* p = dword_8008D4A0[0x24 / 4];
    if (b >= 2)
    {
        p[0x34 / 4] = a;
        ((short*)p)[0x12 / 2] = b;
        ((short*)p)[0xA / 2] = *(unsigned short*)&dword_8008B4F8;
        p[1] |= 0x20;
    }
    else
    {
        dword_8008B4F8 = a;
        sub_80037918(p);
    }
}
// Matched
void sub_80037AC8(int a0)
{
    *(int*)dword_8008D4A0[0x24 / 4] = a0;
}
INCLUDE_ASM(sub_80037AE0);
INCLUDE_ASM(sub_80037C74);
INCLUDE_ASM(sub_80037F44);
INCLUDE_ASM(sub_80038230);
INCLUDE_ASM(sub_8003856C);
INCLUDE_ASM(sub_8003891C);
INCLUDE_ASM(sub_80038A5C);
INCLUDE_ASM(sub_80038CA8);
INCLUDE_ASM(sub_80038D64);
INCLUDE_ASM(sub_80038E2C);
#if 0
void sub_800390F4(void* arg0, int arg1)
{
}
#endif
INCLUDE_ASM(sub_800390F4);
// Matched
int sub_800395D0(int* pIdx, int value, int* table)
{
    if (value >= table[*pIdx + 1])
    {
        *pIdx = *pIdx + 1;
    }
    return table[*pIdx + 1] != -1;
}

INCLUDE_ASM(sub_80039620);
#if 0
void sub_80039698(int* a0)
{
}
#endif
INCLUDE_ASM(sub_80039698);
INCLUDE_ASM(sub_8003970C);
typedef struct
{
    int a;
    int b;
} struct_pair8;
// Matched
void sub_8003983C(int idx_, int* a5)
{
    int* p = dword_8008D4A0[0x24 / 4];
    struct_pair8* t = (struct_pair8*)dword_800B1084;
    int* q;
    p[0x1C / 4] = t[(short)idx_].b;
    q = p + 0x1C8 / 4;
    p[0x218 / 4] = (int)a5;
    p[0x1C8 / 4] = 0;
    p[1] |= 8;
    q[1] = 0x28;
    q[2] = 0x50;
    q[3] = 0x78;
    q[4] = -1;
    p[0x1BC / 4] = (int)levantPos_8008BD18;
    p[0x1C0 / 4] = (int)levantPos_8008BD18 + 0xC;
}
INCLUDE_ASM(sub_800398B4);
INCLUDE_ASM(sub_80039E14);
