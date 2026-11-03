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

extern int dword_80086898[][12];

INCLUDE_DATA(dword_8007499C);
INCLUDE_DATA(dword_800749A0);
INCLUDE_DATA(dword_800749A4);
INCLUDE_DATA(dword_800749A8);
INCLUDE_DATA(word_800749AC);

// Matched
int sub_8003E884(int idx, short n)
{
    Font* p = &fonts_80095FB0[idx];
    short k = 12;
    int r = p->w_10;
    int v = n - 1;
    for (; k != 0; k--)
    {
        if (v < dword_80086898[idx - 1][k - 1])
        {
            r -= k;
            break;
        }
    }
    return r;
}
INCLUDE_ASM(DrawText_8003E91C);
INCLUDE_ASM(sub_8003EC2C);
