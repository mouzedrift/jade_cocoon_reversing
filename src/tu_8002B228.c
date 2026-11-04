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
#include "tu_8002B228.h"

const Block16 dword_800741D4 = { { 14, 0, 14, 14, 0, 14 } };

extern void DrawElementIcons_8002B2A4(short a, int b, int c, Block16* d, int e);
// Matched
void sub_8002B228(short a, int b, int c)
{
    Block16 local = dword_800741D4;
    DrawElementIcons_8002B2A4(a, b, c, &local, 1);
}
