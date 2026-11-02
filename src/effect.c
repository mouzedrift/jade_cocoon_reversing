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

INCLUDE_DATA(aAssertionFaile_3);
INCLUDE_DATA(aEffectC);
INCLUDE_DATA(dword_800795A0);
INCLUDE_DATA(dword_800795D0);
INCLUDE_DATA(dword_800795D4);
INCLUDE_DATA(word_800795D8);
INCLUDE_DATA(dword_800795DC);
INCLUDE_DATA(dword_800795E0);
INCLUDE_DATA(dword_800795E4);
INCLUDE_DATA(dword_800795E8);
INCLUDE_DATA(dword_800795EC);
INCLUDE_DATA(dword_800795F0);

#if 0
// Not matched: branch sense (beq vs bne) and registers differ
int sub_80013DB0(void)
{
    int r;
    if (rand() % 6 != 0)
    {
        r = 1;
    }
    else
    {
        r = 2;
    }
    return r;
}
#endif
INCLUDE_ASM(sub_80013DB0);
// Matched
int sub_80013E00(unsigned int idx, int add)
{
    int result = 0;
    if (idx < 0x15)
    {
        result = dword_80079348[idx] + add;
    }
    return result;
}
// Matched
int sub_80013E30(void)
{
    return rand() % 100;
}
// Matched
void sub_80013E80(void* p, int arg)
{
    sub_80033624(p, sub_80014390(arg & 0xFF));
}
// Matched
void sub_80013EB4(void* p, int nth, int id)
{
    sub_80033624(p, (int)sub_800107A0(id, nth));
}
INCLUDE_ASM(sub_80013EE8);
// Matched
int sub_80014114(int x)
{
    return (x * x) / 10;
}
// Matched
int sub_8001413C(int x)
{
    return (x * x) / 5;
}
// Matched
int sub_80014164(int x)
{
    return (x * x * x) / 400;
}
INCLUDE_ASM(sub_8001419C);
INCLUDE_ASM(sub_80014200);
#if 0
// Not matched
int sub_800142B8(unsigned char* p)
{
    int v = p[8] * 200 / (p[8] + p[6]);
    if (v > 0)
    {
        if (v > 200)
        {
            v = 200;
        }
    }
    else
    {
        v = 1;
    }
    return v;
}
#endif
INCLUDE_ASM(sub_800142B8);
#if 0
// Not matched
int sub_80014308(unsigned char* p)
{
    int v = p[6] * 200 / (p[6] + p[8]);
    if (v <= 0)
    {
        v = 1;
    }
    else if (v >= 0xC9)
    {
        v = 0xC8;
    }
    return v;
}
#endif
INCLUDE_ASM(sub_80014308);
// Matched
int sub_80014358(unsigned int mask)
{
    unsigned int i;
    for (i = 0; i < 32; i++)
    {
        if (mask & (1 << i))
        {
            return i;
        }
    }
    return 0;
}
#if 0
int sub_80014390(int arg0)
{
    return 0;
}
#endif
INCLUDE_ASM(sub_80014390);
#if 0
// Not matched
int sub_80014444(unsigned int a0)
{
    int r = 0;
    if ((a0 & 0xFF) >= 8)
    {
        r = sub_800A11D8((a0 - 8) & 0xFF);
    }
    else if ((a0 & 0xFF) != 0)
    {
        r = (int)sub_80010598(3, (a0 - 1) & 0xFF);
    }
    return r;
}
#endif
INCLUDE_ASM(sub_80014444);
#if 0
// Not matched
int sub_8001449C(int a0)
{
    int r = 0;
    int v = a0 - 4;
    if ((unsigned char)v < 3)
    {
        if ((1 << a0) & sub_800A248C())
        {
            r = sub_800A2B20((unsigned char)v);
        }
    }
    return r;
}
#endif
INCLUDE_ASM(sub_8001449C);
// Matched
void sub_8001450C(int* a0, struct_16* a1, int a2, int a3)
{
    unsigned int i;
    sub_80014574(a1, a2, a3);
    for (i = 0; i < a1->field_4; i++)
    {
        a0[i] = 0;
    }
}
// Matched
void sub_80014574(struct_16* p, int a1, int a2)
{
    p->field_0 = a1;
    p->field_4 = a2;
    p->field_8 = 0;
    p->field_C = 0;
}
INCLUDE_ASM(sub_80014588);
void sub_80014638(struct_obj_D* p, int* q);
// Matched
void sub_80014618(struct_obj_D* p, int* q)
{
    q[0x28 / 4] = 2;
    q[0x3C / 4] = 0;
    q[0x2C / 4] = 0;
    p->field_8 = (void (*)(void))sub_80014638;
}
INCLUDE_ASM(sub_80014638);
INCLUDE_ASM(sub_800147FC);
// Matched
void sub_800148A0(void)
{
    sub_80020EE0(dword_80091BD0);
    unknownFlags_8008D678 &= ~0x800;
}
// Matched
int sub_800148D4(void)
{
    return ((int*)dword_8008D3F8[9])[0x2C / 4] == 0;
}
// Matched
void sub_800148F4(int a0)
{
    int* p = dword_8008D3F8[9];
    p[0x28 / 4] |= 4;
    p[0x38 / 4] = a0;
    if (p[0x2C / 4] != 0)
    {
        printf(aAssertionFaile_3, aEffectC, 0x124);
        exit(1);
    }
}
