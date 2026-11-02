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

INCLUDE_DATA(dword_80072310);
INCLUDE_DATA(dword_80072324);
INCLUDE_DATA(dword_80072354);
INCLUDE_DATA(dword_80072380);
INCLUDE_DATA(dword_800723AC);
INCLUDE_DATA(dword_800723FC);
INCLUDE_DATA(dword_80072410);
INCLUDE_DATA(dword_80072420);
INCLUDE_DATA(dword_80072440);
INCLUDE_DATA(dword_80072454);
INCLUDE_DATA(dword_80072464);
INCLUDE_DATA(dword_800724C4);
INCLUDE_DATA(dword_800724D4);
INCLUDE_DATA(dword_80072518);
INCLUDE_DATA(dword_80072534);
INCLUDE_DATA(dword_80072548);
INCLUDE_DATA(dword_80072558);
INCLUDE_DATA(dword_8007256C);
INCLUDE_DATA(dword_80072578);
INCLUDE_DATA(dword_80072584);
INCLUDE_DATA(dword_800725AC);
INCLUDE_DATA(dword_800725BC);
INCLUDE_DATA(dword_800725C8);
INCLUDE_DATA(dword_800725D4);
INCLUDE_DATA(dword_800725E0);
INCLUDE_DATA(dword_80072620);
INCLUDE_DATA(dword_80072640);
INCLUDE_DATA(dword_8007268C);
INCLUDE_DATA(dword_800726A4);
INCLUDE_DATA(dword_800726B8);
INCLUDE_DATA(dword_800726C8);
INCLUDE_DATA(dword_800726F8);
INCLUDE_DATA(dword_8007270C);
INCLUDE_DATA(dword_80072740);
INCLUDE_DATA(dword_80072764);
INCLUDE_DATA(dword_80072774);
INCLUDE_DATA(dword_80072794);
INCLUDE_DATA(dword_800727B8);
INCLUDE_DATA(dword_800727CC);
INCLUDE_DATA(dword_800727F0);
INCLUDE_DATA(dword_80072804);
INCLUDE_DATA(dword_80072818);
INCLUDE_DATA(dword_8007282C);
INCLUDE_DATA(dword_8007284C);
INCLUDE_DATA(dword_8007285C);
INCLUDE_DATA(dword_8007286C);
INCLUDE_DATA(dword_8007287C);
INCLUDE_DATA(dword_800728C0);
INCLUDE_DATA(dword_800728D4);
INCLUDE_DATA(dword_800728E8);
INCLUDE_DATA(dword_800728FC);
INCLUDE_DATA(dword_80072910);
INCLUDE_DATA(dword_80072954);
INCLUDE_DATA(dword_80072964);
INCLUDE_DATA(dword_800729A8);
INCLUDE_DATA(dword_800729BC);
INCLUDE_DATA(dword_80072A10);
INCLUDE_DATA(dword_80072A64);
INCLUDE_DATA(dword_80072AA8);
INCLUDE_DATA(dword_80072AC8);
INCLUDE_DATA(dword_80072AE4);
INCLUDE_DATA(dword_80072AF8);
INCLUDE_DATA(dword_80072B0C);
INCLUDE_DATA(dword_80072B20);
INCLUDE_DATA(dword_80072B34);
INCLUDE_DATA(dword_80072B68);
INCLUDE_DATA(dword_80072B78);
INCLUDE_DATA(dword_80072BA8);
INCLUDE_DATA(dword_80072BBC);
INCLUDE_DATA(dword_80072BCC);
INCLUDE_DATA(dword_80072BF0);
INCLUDE_DATA(dword_80072C04);
INCLUDE_DATA(dword_80072C18);
INCLUDE_DATA(dword_80072C2C);
INCLUDE_DATA(dword_80072C50);
INCLUDE_DATA(dword_80072C78);
INCLUDE_DATA(dword_80072C9C);
INCLUDE_DATA(dword_80072CB0);
INCLUDE_DATA(dword_80072CC8);
INCLUDE_DATA(dword_80072CD8);
INCLUDE_DATA(dword_80072CE8);
INCLUDE_DATA(dword_80072CF4);
INCLUDE_DATA(dword_80072D1C);
INCLUDE_DATA(dword_80072D54);
INCLUDE_DATA(dword_80072D90);
INCLUDE_DATA(dword_80072DA4);
INCLUDE_DATA(dword_80072DB4);
INCLUDE_DATA(dword_80072DEC);
INCLUDE_DATA(dword_80072E28);
INCLUDE_DATA(dword_80072E38);
INCLUDE_DATA(dword_80072E64);
INCLUDE_DATA(dword_80072EA8);
INCLUDE_DATA(dword_80072EC4);
INCLUDE_DATA(dword_80072EE4);
INCLUDE_DATA(dword_80072EF4);
INCLUDE_DATA(dword_80072F18);
INCLUDE_DATA(dword_80072F2C);
INCLUDE_DATA(dword_80072F40);
INCLUDE_DATA(dword_80072F64);
INCLUDE_DATA(dword_80072F88);
INCLUDE_DATA(dword_80072FAC);
INCLUDE_DATA(dword_80072FC0);
INCLUDE_DATA(dword_80072FD4);
INCLUDE_DATA(dword_80072FE8);
INCLUDE_DATA(dword_80073008);
INCLUDE_DATA(dword_80073028);
INCLUDE_DATA(dword_8007303C);

// Matched
int sub_80018E5C(char* a0, unsigned int a1)
{
    struct_4s* t = (struct_4s*)(a0 + 0x108);
    int v = 0;
    switch (a1)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        v = t[a1].field_0;
        break;
    case 10:
        v = sub_8001F03C((int)a0, ((int*)a0)[0xD0 / 4], -1, 0x10);
        break;
    }
    return v;
}
// Matched
void sub_80018EBC(int a0, unsigned int* a1)
{
    unsigned int f = *a1;
    int* r = 0;
    if (f & 0x200)
    {
        r = (f & 1) ? dword_8007A14C : dword_8007A0EC;
    }
    else if (f & 0x100)
    {
        r = (f & 1) ? dword_8007A140 : dword_8007A0E0;
    }
    else if (f & 0x80)
    {
        r = (f & 1) ? dword_8007A134 : dword_8007A0D4;
    }
    else if (f & 0x40)
    {
        r = (f & 1) ? dword_8007A128 : dword_8007A0C8;
    }
    else if (f & 0x20)
    {
        r = (f & 1) ? dword_8007A11C : dword_8007A0BC;
    }
    else if (f & 0x10)
    {
        r = (f & 1) ? dword_8007A110 : dword_8007A0B0;
    }
    else if (f & 0x8)
    {
        r = (f & 1) ? sub_8007A104 : dword_8007A0A4;
    }
    else if (f & 1)
    {
        r = dword_8007A0F8;
    }
    sub_8001DAAC(a0, r);
}
INCLUDE_ASM(sub_8001900C);
INCLUDE_ASM(sub_8001980C);
// Matched
void sub_800199A0(char* p)
{
    *(struct_20_u8*)(p + 0x6C) = *(struct_20_u8*)sub_80019C28(*(unsigned int*)(p + 0x5C));
}
// Matched
void sub_80019A20(char* a0)
{
    unsigned int idx = *(unsigned int*)(a0 + 0x5C);
    if (idx < 0xC9)
    {
        *(int*)(a0 + 0x80) = dword_8007A6AC[idx];
    }
    else
    {
        *(int*)(a0 + 0x80) = *sub_800B3260(idx - 0x39);
    }
}
// Matched
int sub_80019A80(int arg0)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (arg0 < dword_8007C2E4[i])
        {
            break;
        }
    }
    i--;
    if (i == 5)
    {
        return 4;
    }
    return i;
}
// Matched
int sub_80019AD0(char* p)
{
    sub_80019A80(*(unsigned char*)(p + 0x44));
    return 4;
}
// Matched
void sub_80019AF4(unsigned int* arg0, unsigned int* arg1)
{
    sub_800403E8(arg0, arg1, 12);
}
// Matched
void sub_80019B14(short* p, unsigned short* a1, unsigned short* a2)
{
    struct_int3 masks;
    int k;
    int i;
    masks = dword_8007303C;
    for (k = 0; k < 3; k++)
    {
        int set = 0;
        int clr = 0;
        if (a1[k] < 2)
        {
            clr = masks.m[k];
        }
        if (a2[k] == 0)
        {
            set = masks.m[k];
        }
        for (i = 0; i < 25; i++)
        {
            int bit = 1 << i;
            if (clr & bit)
            {
                p[i * 4 + 3] &= ~2;
            }
            if (set & bit)
            {
                p[i * 4 + 3] |= 0x10;
            }
        }
    }
}
