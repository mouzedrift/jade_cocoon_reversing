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

extern int dword_80086568;
extern void sub_8003BF18(struct_node_C* n);

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
// Matched
int sub_8003B80C(int* a, int* b)
{
    int dx = a[0] - b[0];
    int dy = a[1] - b[1];
    int dz = a[2] - b[2];
    return dx * dx + dy * dy + dz * dz;
}
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
// Not matched: C is right but ASPSX expands divu with a divide-by-zero check (3 extra insts); original has a bare divu
#if 0
unsigned int sub_8003B918(unsigned int n)
{
    int x;
    int y;
    if (n == 0)
    {
        return 0;
    }
    x = 1;
    if (n >= 2)
    {
        x = n;
    }
    do
    {
        y = x;
        x = (n / y + y) >> 1;
    } while (x < y);
    return y;
}
#endif
INCLUDE_ASM(sub_8003B918);
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
// Matched
void sub_8003BBE4(void)
{
    int v = 0x10000;
    int i;
    dword_80086540 = 0;
    ((int*)&dword_80086540)[1] = 0;
    ((int*)&dword_80086540)[2] = 0;
    ((int*)&dword_80086540)[3] = 0;
    for (i = 0x13; i >= 0; i--)
    {
        dword_80095C90[i].field_10 = v;
    }
    dword_80086564 = 0;
    dword_80086568 = 0;
}
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
// Matched
int sub_8003BE88(int key)
{
    struct_node_C* n = sub_8003BED4(key);
    if (n && !(n->field_C & 0x100))
    {
        sub_8003BF18(n);
        return 1;
    }
    return 0;
}
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
// Not matched: no jr after the store, execution falls through into sub_8003BFC0
#if 0
void sub_8003BFB8(int arg0)
{
    dword_80086564 = arg0;
}
#endif
INCLUDE_ASM(sub_8003BFB8);
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
    if (n)
    {
        n->field_24 = 0;
        n->field_C |= 0x2000;
        return 0;
    }
    return 2;
}
INCLUDE_ASM(sub_8003C0A4);
extern void sub_8003C184(void);
// Matched
void sub_8003C128(int* a0, int* a1)
{
    sub_8003BBE4();
    dword_8008656C = 0x801B9250;
    a1[0] = 0;
    a1[7] = 0;
    a1[8] = 0;
    a1[10] = 0;
    a0[2] = (int)sub_8003C184;
}
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
