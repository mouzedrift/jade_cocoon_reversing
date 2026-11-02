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
INCLUDE_ASM(sub_80017BF0);
INCLUDE_ASM(sub_80017CE4);
INCLUDE_ASM(sub_80017E30);
INCLUDE_ASM(sub_80017FF8);
// Matched
int sub_800181E8(void)
{
    return *dword_80091C00;
}
INCLUDE_ASM(sub_80018200);
INCLUDE_ASM(sub_800182B8);
