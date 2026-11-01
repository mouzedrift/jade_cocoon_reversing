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


INCLUDE_ASM(sub_80018430);
// Matched
void sub_800184A0(int arg, int bit)
{
    unsigned char* base = (unsigned char*)dword_8008D3F8[0x24 / 4];
    if (bit == 0)
    {
        (base + arg)[0x44] = 0;
    }
    else
    {
        (base + arg)[0x44] |= 1 << bit;
    }
}
INCLUDE_ASM(sub_800184DC);
INCLUDE_ASM(sub_8001852C);
INCLUDE_ASM(sub_80018908);
INCLUDE_ASM(sub_800189F8);
INCLUDE_ASM(sub_80018A4C);
INCLUDE_ASM(sub_80018C00);
