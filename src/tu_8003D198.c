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

extern unsigned short word_8009194C[];
extern unsigned short word_800918CC[];
extern void PlaySfx_80031494(int a1);

INCLUDE_DATA(word_80074994);
INCLUDE_DATA(dword_80074998);

// Matched
int sub_8003D198(int limit, int pos, int step, int idx)
{
    if (word_800918CC[idx] & 2)
    {
        pos += step;
    }
    else if (word_800918CC[idx] & 8)
    {
        if (!(word_800918D0[idx] & 2))
        {
            pos -= step;
        }
    }
    if (pos >= limit)
    {
        pos = limit - 1;
    }
    if (pos < 0)
    {
        pos = 0;
    }
    return pos;
}
// Matched
int sub_8003D210(int limit, int pos, int step, int idx)
{
    if (word_800918CC[idx] & 0x2000)
    {
        pos += step;
    }
    else if (word_800918CC[idx] & 0x8000)
    {
        if (!(word_800918D0[idx] & 0x2000))
        {
            pos -= step;
        }
    }
    if (pos >= limit)
    {
        pos = limit - 1;
    }
    if (pos < 0)
    {
        pos = 0;
    }
    return pos;
}
#if 0
int sub_8003D288(int arg0, int arg1)
{
    return 0;
}
#endif
INCLUDE_ASM(sub_8003D288);
// Matched
int sub_8003D380(int a0)
{
    return sub_8003D288(a0, 0);
}
// Matched
int sub_8003D3A0(int a0)
{
    return sub_8003D288(a0, 1);
}
#if 0
int sub_8003D3C0(int arg0, int arg1)
{
    return 0;
}
#endif
INCLUDE_ASM(sub_8003D3C0);
// Matched
int sub_8003D41C(int a0)
{
    return sub_8003D3C0(a0, 0);
}
// Matched
int sub_8003D43C(int a0)
{
    return sub_8003D3C0(a0, 1);
}
// Matched
int sub_8003D45C(int idx)
{
    unsigned int f = word_800918D0[idx] & 0x20;
    return f != 0;
}
// Matched
int sub_8003D480(void)
{
    return sub_8003D45C(0);
}
// Matched
int sub_8003D4A0(void)
{
    return sub_8003D45C(1);
}
INCLUDE_ASM(sub_8003D4C0);
INCLUDE_ASM(sub_8003D630);
INCLUDE_ASM(sub_8003D794);
INCLUDE_ASM(sub_8003D830);
INCLUDE_ASM(sub_8003DA70);
INCLUDE_ASM(sub_8003DB74);
INCLUDE_ASM(sub_8003DCA4);
// Matched
void sub_8003E268(unsigned short* p)
{
    short x = p[0] + 0xC3;
    short y = p[1] + 0x23;
    sub_8003CF88(x, y, 0);
}
INCLUDE_ASM(sub_8003E2A8);
INCLUDE_ASM(sub_8003E3B4);
// Matched
int sub_8003E484(int a0)
{
    int v = *sub_8003F684(2, a0);
    if (v < 0xC3)
    {
        if (v >= 0x91)
        {
            return 1;
        }
    }
    return 0;
}
INCLUDE_ASM(sub_8003E4C8);
INCLUDE_ASM(sub_8003E6B0);
