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

INCLUDE_DATA(aDataData0011);
INCLUDE_DATA(aAssertionFaile_1);
INCLUDE_DATA(aCdC);

// Matched
void sub_80039FA4(int a0)
{
    dword_80083BD0 = a0;
}
// Matched
int sub_80039FB0(void)
{
    return dword_80083BD0;
}
// Matched
void sub_80039FC0(void)
{
    sub_80020EE0(dword_80095468);
}
INCLUDE_ASM(sub_80039FE4);
INCLUDE_ASM(sub_8003A6C4);
// Matched
short ratan2_8003B548(long y, long x)
{
    return ratan2(y, x);
}
INCLUDE_ASM(sub_8003B56C);
INCLUDE_ASM(sub_8003B5D4);
// Matched
int sub_8003B664(int x)
{
    if (x > 0)
    {
        return 1;
    }
    if (x < 0)
    {
        return -1;
    }
    return 0;
}
INCLUDE_ASM(sub_8003B684);
INCLUDE_ASM(sub_8003B740);
INCLUDE_ASM(sub_8003B80C);
INCLUDE_ASM(sub_8003B860);
// Matched
int sub_8003B8BC(int x, int y)
{
    return x * x + y * y;
}
// Matched
int sub_8003B8DC(int* p, int a1)
{
    return p[0] * p[0] + p[1] * p[1] + p[2] * p[2];
}
// Matched
unsigned int sub_8003B918(unsigned int n)
{
    unsigned int x;
    unsigned int y;
    if (n == 0)
    {
        return 0;
    }
    x = n;
    if (n < 2)
    {
        x = 1;
    }
    do
    {
        y = x;
        x = (n / y + y) >> 1;
    } while (x < y);
    return y;
}
INCLUDE_ASM(sub_8003B95C);
// Matched
short ratan2Difference_8003B9E0(int* a, int* b)
{
    return ratan2(b[0] - a[0], b[2] - a[2]);
}
// Matched
short sub_8003BA18(int v)
{
    short r = v & 0xFFF;
    if (r >= 0x800)
    {
        r |= 0xF000;
    }
    return r;
}
// Matched
int sub_8003BA38(unsigned int a, unsigned int b)
{
    if (a > b)
    {
        return -1;
    }
    if (a == b)
    {
        return 0;
    }
    return a < b;
}
// Matched
int GetCapturedMinionsFromBitfield_8003BA58(int arg0)
{
    int result;
    int var_v0;
    int i;

    result = 0;
    for (i = 0; i < 32; i++)
    {
        var_v0 = 1 << i;
        if (arg0 & var_v0)
        {
            result += 1;
        }
    }
    return result;
}
INCLUDE_ASM(sub_8003BA90);
INCLUDE_ASM(sub_8003BADC);
INCLUDE_ASM(sub_8003BB1C);
// Matched
long cdRomEventErrorHandler_8003BBAC(void)
{
    unknownFlags_8008D678 |= 0x100u;
    printf(aAssertionFaile_1, aCdC, 79);
    exit(1);
}
INCLUDE_ASM(sub_8003BBE4);
// Matched
int sub_8003BC34(void)
{
    return dword_80086540;
}
// Matched
int sub_8003BC44(void)
{
    int i;
    for (i = 0; i < 0x14; i++)
    {
        if (dword_80095C90[i].field_10 == 0x10000)
        {
            return i;
        }
    }
    return -1;
}
INCLUDE_ASM(sub_8003BC84);
// Matched
void nullsub_6(void)
{
}
#if 0
int sub_8003BE30(int arg0)
{
    return 0;
}
#endif
INCLUDE_ASM(sub_8003BE30);
INCLUDE_ASM(sub_8003BE88);
// Matched
struct_node_C* sub_8003BED4(int key)
{
    struct_node_C* p;
    for (p = dword_8008654C; p; p = p->next)
    {
        if (key == p->key)
        {
            return p;
        }
    }
    return 0;
}
INCLUDE_ASM(sub_8003BF18);
// Matched
int sub_8003BF88(void)
{
    if (dword_80086540 == 0 && dword_80086564 == 0)
    {
        return 1;
    }
    return 0;
}
// Matched
void sub_8003BFB8(int arg0)
{
    dword_80086564 = arg0;
}
// Matched
int sub_8003BFC0(void)
{
    return dword_8008656C;
}
INCLUDE_ASM(sub_8003BFD0);
// Matched
int sub_8003C060(int key)
{
    struct_node_C* n = sub_8003BED4(key);
    if (!n)
    {
        return 2;
    }
    n->field_24 = 0;
    n->field_C |= 0x2000;
    return 0;
}
INCLUDE_ASM(sub_8003C0A4);
INCLUDE_ASM(sub_8003C128);
INCLUDE_ASM(sub_8003C184);
// Matched
void sub_8003C684(void)
{
    if (dword_80086540)
    {
        printf(aAssertionFaile_1, aCdC, 878);
        exit(1);
    }
}
