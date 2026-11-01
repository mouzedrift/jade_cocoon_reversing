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

INCLUDE_DATA(dword_80098690);
INCLUDE_DATA(dword_800986A0);
INCLUDE_DATA(dword_800987D8);
INCLUDE_DATA(dword_8009AAD8);

INCLUDE_ASM(sub_80043AF8);
// Matched
void sub_80043B40(int* p)
{
    int n = p[3];
    int i;
    for (i = 0; i < n; i++)
    {
        if (p[4] & 1)
        {
            p[4] = (p[4] & ~1) | 0x8000;
        }
        p = (int*)p[1];
    }
}
INCLUDE_ASM(sub_80043B8C);
INCLUDE_ASM(sub_80043DE0);
INCLUDE_ASM(sub_80044010);
INCLUDE_ASM(sub_80044D0C);
INCLUDE_ASM(sub_800451BC);
INCLUDE_ASM(sub_80045534);
INCLUDE_ASM(sub_800459E4);
INCLUDE_ASM(sub_80045E48);
INCLUDE_ASM(sub_80046248);
INCLUDE_ASM(sub_8004668C);
INCLUDE_ASM(sub_80046874);
INCLUDE_ASM(sub_80046A58);
INCLUDE_ASM(sub_80047E28);
INCLUDE_ASM(sub_8004A4FC);
INCLUDE_ASM(sub_8004AD44);
