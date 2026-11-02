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

INCLUDE_DATA(dword_80071F58);
INCLUDE_DATA(dword_80071F5C);
INCLUDE_DATA(dword_80071F60);
INCLUDE_DATA(aAssertionFaile_2);
INCLUDE_DATA(aCommonC);
INCLUDE_DATA(byte_800793C4);
INCLUDE_DATA(dword_800793C8);

// Matched
void sub_80012794(struct_obj_B* p, int a1)
{
    unsigned int f = p->flags_0;
    if (f & 0x3F8)
    {
        a1 &= ~0x3F8;
    }
    p->flags_0 = f | a1;
}
// Matched
void sub_800127B8(struct_obj_B* p)
{
    p->field_4 = 0;
    p->field_8 = 0;
    p->flags_0 |= 0x400;
}
// Matched
void sub_800127D0(int a0, int a1, int a2, int a3)
{
    int v = sub_80014390(a0 & 0xFF);
    if (v != 0)
    {
        sub_80012614(v, a1, a2, a3);
    }
}
INCLUDE_ASM(sub_80012828);
INCLUDE_ASM(sub_800129B0);
INCLUDE_ASM(sub_80012BB0);
INCLUDE_ASM(sub_80013228);
