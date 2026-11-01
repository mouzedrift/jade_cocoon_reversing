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

INCLUDE_DATA(dword_80072270);

// Matched
void sub_80016BF4(int* p, int* q)
{
    if (--q[1] < 0)
    {
        *p = (*p & ~1) | 0x8000;
        PlaySfx_80031494(0x24);
    }
}
INCLUDE_ASM(sub_80016C3C);
INCLUDE_ASM(sub_80016E20);
INCLUDE_ASM(sub_80016FC8);
INCLUDE_ASM(sub_80017158);
INCLUDE_ASM(sub_80017208);
INCLUDE_ASM(sub_80017290);
INCLUDE_ASM(sub_800173A8);
