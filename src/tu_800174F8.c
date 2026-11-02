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

INCLUDE_DATA(off_80072278);

INCLUDE_ASM(sub_800174F8);
INCLUDE_ASM(sub_8001761C);
INCLUDE_ASM(sub_80017784);
INCLUDE_ASM(sub_800178C0);
void sub_80017B10(unsigned int* a0, int* a1);
// Matched
void sub_80017A6C(int a0, int a1)
{
    EventEntry* e = sub_80043AF8(dword_8008B4A8);
    if (e)
    {
        int* b = e->buffer;
        b[0x8C / 4] = (int)dword_80091C00;
        b[0] = 0;
        if (a1 > 0)
        {
            b[1] = a1;
        }
        else
        {
            b[1] = sub_800181E8();
        }
        e->cb_8 = (EventEntryFn)sub_80017B10;
        e->flags = (e->flags | 1) & ~0x8000;
        sub_8004188C();
        DecDCTReset(0);
    }
}
// Matched
void sub_80017B10(unsigned int* a0, int* a1)
{
    int* t = (int*)a1[0x8C / 4];
    if (++a1[0] < a1[1] && word_8008D780 == 0)
    {
        if (!(unknownFlags_8008D678 & 0x800))
        {
            DecodeMdec_80041920(((unsigned long**)t[1])[a1[0] % t[0]], dword_8008D42C, 2);
            unknownFlags_8008D678 |= 0x800;
        }
    }
    else
    {
        sub_800418FC();
        unknownFlags_8008D678 &= ~0x800;
        *a0 = (*a0 & ~1) | 0x8000;
    }
}
void sub_80017CE4(int* a0, int* a1);
// Matched
void sub_80017BF0(char* a0, int a1)
{
    EventEntry* e = sub_80043AF8(dword_8008B4A8);
    if (e)
    {
        int* b = e->buffer;
        int idx;
        b[0x44 / 4] = (*(int**)(a0 + 0x14))[0];
        b[0x48 / 4] = (*(int**)(a0 + 0x14))[1];
        b[0x4C / 4] = (*(int**)(a0 + 0x14))[2];
        b[0] = 0;
        b[0x30 / 4] = 0;
        b[0x34 / 4] = 0x23F000;
        ((short*)b)[0x84 / 2] = 0;
        ((short*)b)[0x82 / 2] = 0;
        ((short*)b)[0x80 / 2] = 0;
        idx = sub_80020F00((struct_list_14*)dword_80091BD0, 1, a1);
        e->flags = (e->flags | 1) & ~0x8000;
        b[0x88 / 4] = dword_80091BD0[0x28 / 4] + idx * 28;
        e->cb_8 = (EventEntryFn)sub_80017CE4;
    }
}
INCLUDE_ASM(sub_80017CE4);
INCLUDE_ASM(sub_80017E30);
INCLUDE_ASM(sub_80017FF8);
// Matched
int sub_800181E8(void)
{
    return *dword_80091C00;
}
// Matched
struct_4s* sub_80018200(struct_4s* src, unsigned short lo, unsigned short hi, short n)
{
    struct_4s* dst = (struct_4s*)dword_8008D3F8[9];
    int i;
    int j;
    short d;
    for (i = 0; i < 10; i++)
    {
        dst[i].field_0 = src[i].field_0;
        dst[i].field_2 = src[i].field_2;
    }
    d = hi - lo;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (dst[j].field_0 >= hi)
            {
                dst[j].field_0 += d;
            }
            if (dst[j].field_2 >= hi)
            {
                dst[j].field_2 += d;
            }
        }
    }
    return dst;
}
INCLUDE_ASM(sub_800182B8);
