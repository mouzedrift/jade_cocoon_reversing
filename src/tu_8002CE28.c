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

INCLUDE_DATA(dword_800741F0);
INCLUDE_DATA(dword_80074260);
INCLUDE_DATA(dword_80074290);
INCLUDE_DATA(dword_80074298);
INCLUDE_DATA(dword_800742C8);
INCLUDE_DATA(dword_800742D0);
INCLUDE_DATA(dword_80074300);
INCLUDE_DATA(dword_80074308);

INCLUDE_ASM(sub_8002CE28);
extern unsigned char dword_800827F0[];
extern unsigned char* off_8008280C[];
// Matched
unsigned char sub_8002D1A4(int a, short b)
{
    int r = 0;
    switch ((short)a)
    {
    case 0:
        break;
    default:
        r = 4;
        break;
    case 3:
        r = 1;
        break;
    case 1:
        r = 2;
        break;
    case 2:
        r = 3;
        break;
    }
    a = r;
    if (a >= 4)
    {
        return dword_800827F0[b];
    }
    return off_8008280C[b][a];
}
INCLUDE_ASM(sub_8002D250);
