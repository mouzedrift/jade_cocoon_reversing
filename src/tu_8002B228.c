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

INCLUDE_DATA(dword_800741C8);
INCLUDE_DATA(dword_800741CC);
INCLUDE_DATA(dword_800741D0);
INCLUDE_DATA(dword_800741D4);

typedef struct
{
    short s[8];
} Block16;
extern Block16 dword_800741D4;
extern void DrawElementIcons_8002B2A4(short a, int b, int c, Block16* d, int e);
// Matched
void sub_8002B228(short a, int b, int c)
{
    Block16 local = dword_800741D4;
    DrawElementIcons_8002B2A4(a, b, c, &local, 1);
}
