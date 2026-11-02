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
extern unsigned short dword_800918D4[];
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
// Not matched: return value register: orig keeps result in a2 across PlaySfx call (re-set after call)
int sub_8003D288(int flag, int idx)
{
    int r = 0;
    unsigned int x;
    if ((word_8009194C[idx] & 0x40) && !(word_800918D0[idx] & 4) && !(((unsigned short*)dword_800918D4)[idx] & 4))
    {
        goto done;
    }
    x = word_8009194C[idx];
    if (!(x & 4))
    {
        goto end;
    }
    if ((word_800918D0[idx] & 0x40) || (((unsigned short*)dword_800918D4)[idx] & 0x40))
    {
        if (!(x & 0x40))
        {
            goto end;
        }
    }
done:
    r = 1;
    if (flag)
    {
        PlaySfx_80031494(0x7E);
        r = 1;
    }
end:
    return r;
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
typedef struct
{
    short field_0;
    short field_2;
    unsigned short field_4;
    unsigned short field_6;
    short field_8;
    short field_A;
} struct_menu;

extern int sub_8003D830(struct_menu* p);

// Matched
int sub_8003D794(struct_menu* p)
{
    unsigned short a = p->field_8;
    unsigned short b = p->field_A;
    int r = sub_8003D830(p);
    if (r == 0)
    {
        int t = p->field_4 - 1;
        if (t < p->field_8)
        {
            p->field_8 = t;
        }
    }
    if ((short)a != p->field_8 || (short)b != p->field_A)
    {
        PlaySfx_80031494(0x7F);
    }
    return r;
}
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
typedef struct
{
    short w;
    short h;
} struct_size_8003E3B4;
extern int sub_8003E4C8(int str);
// Matched
struct_size_8003E3B4 sub_8003E3B4(int* list)
{
    struct_size_8003E3B4 sz;
    short w;
    int i;
    sz.w = 0;
    sz.h = 0;
    for (i = 0; list[i]; i++)
    {
        if (!sub_8003E484(list[i]))
        {
            w = sub_8003E4C8(list[i]);
            if (sz.w < w)
            {
                sz.w = w;
            }
            sz.h++;
        }
    }
    sz.h *= 12;
    return sz;
}
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
