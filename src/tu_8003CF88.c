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


#if 0
void sub_8003CF88(short a0, short a1, int a2)
{
}
#endif
INCLUDE_ASM(sub_8003CF88);
extern void sub_80033080(void* a, int b, int c);
extern short* dword_8008D434;
// Matched
void sub_8003D034(unsigned short* pPos, int a1)
{
    short r[2];
    r[0] = pPos[0] - 13;
    r[1] = pPos[1] - 6;
    SetSemiTrans((char*)dword_8008D434 + 0x64, 1);
    sub_80033080(r, 5, a1);
}
INCLUDE_ASM(sub_8003D090);
