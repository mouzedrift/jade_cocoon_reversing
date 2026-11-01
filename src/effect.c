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
// Not matched
int sub_80013DB0(void)
{
    return rand() % 6 ? 1 : 2;
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
#if 0
// Not matched: the original calls sub_800107A0 with only one argument
void sub_80013EB4(void* p, int a1, int a2)
{
    sub_80033624(p, (int)sub_800107A0(a2, 0));
}
#endif
INCLUDE_ASM(sub_80013EB4);
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
INCLUDE_ASM(sub_80014444);
INCLUDE_ASM(sub_8001449C);
INCLUDE_ASM(sub_8001450C);
// Matched
void sub_80014574(struct_16* p, int a1, int a2)
{
    p->field_0 = a1;
    p->field_4 = a2;
    p->field_8 = 0;
    p->field_C = 0;
}
INCLUDE_ASM(sub_80014588);
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
INCLUDE_ASM(sub_800148F4);
