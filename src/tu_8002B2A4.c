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

INCLUDE_DATA(dword_800741D8);
INCLUDE_DATA(dword_800741DC);
INCLUDE_DATA(dword_800741E0);
INCLUDE_DATA(dword_800741E4);
INCLUDE_DATA(dword_800741E8);

INCLUDE_ASM(sub_8002B2A4);
INCLUDE_ASM(sub_8002B3DC);
INCLUDE_ASM(sub_8002B8DC);
INCLUDE_ASM(sub_8002BA54);
// Matched
unsigned int sub_8002BC60(unsigned int a, unsigned int b, unsigned int c)
{
    if (b < a)
    {
        a = b;
    }
    if (a)
    {
        a = a * c / b;
        if (a == 0)
        {
            return 1;
        }
        return a;
    }
    return 0;
}
INCLUDE_ASM(sub_8002BCAC);
