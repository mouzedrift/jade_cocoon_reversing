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

INCLUDE_DATA(dword_80074BA0);

// Matched
int sub_80041E68(int mode, int a, int b, int c)
{
    switch (mode)
    {
    case 0:
        return a;
    case 1:
        return a + c;
    case 2:
        return a - c + b;
    case 3:
        return a + b;
    }
    return -1;
}
INCLUDE_ASM(DrawWindowFrame_80041ED0);
