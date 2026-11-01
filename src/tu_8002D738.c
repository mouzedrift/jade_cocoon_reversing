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

INCLUDE_DATA(dword_8007430C);
INCLUDE_DATA(dword_80074310);
INCLUDE_DATA(dword_80074314);
INCLUDE_DATA(dword_80074318);
INCLUDE_DATA(dword_8007431C);
INCLUDE_DATA(dword_80074320);
INCLUDE_DATA(dword_80074360);
INCLUDE_DATA(dword_80074374);
INCLUDE_DATA(dword_80074380);
INCLUDE_DATA(dword_80074398);
INCLUDE_DATA(dword_800743B4);
INCLUDE_DATA(dword_800743CC);

// Matched
int sub_8002D738(int a0, int a1, int a2)
{
    if (a2 == 0 || a2 == 2)
    {
        return 1;
    }
    if (a2 == 3 && a0 + 1 != a1)
    {
        return 1;
    }
    if (a2 == 1 && a0 + 1 == a1)
    {
        return 1;
    }
    return 0;
}
// Matched
int sub_8002D780(void)
{
    int n = sub_80010548(3);
    int i;
    int mask = 0;
    for (i = 0; i < n; i++)
    {
        mask |= 1 << (i + 1);
    }
    return mask;
}
INCLUDE_ASM(sub_8002D7D0);
