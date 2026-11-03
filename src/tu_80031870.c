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




// Matched
int sub_80031870(int a0)
{
    switch (a0)
    {
    case 0:
        return 3;
    case 1:
        return 0;
    case 2:
        return 2;
    case 3:
        return 1;
    case 4:
        return 4;
    }
    return 0;
}
INCLUDE_DATA(dword_800746D0);
