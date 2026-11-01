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


extern short* dword_8008D434;
extern char* dword_8008D440;

#if 0
// Not matched: instruction scheduling differs (prologue/lw order)
void sub_8003CF88(short x, short y, int idx)
{
    ((char*)dword_8008D434)[0x4B4] = ((*(volatile int*)&frameCount_8008D3FC) & 0xF) << 4;
    *(short*)((char*)dword_8008D434 + 0x4B8) = x;
    *(short*)((char*)dword_8008D434 + 0x4BA) = y;
    ((char*)dword_8008D434)[0x4B5] = ((*(volatile int*)&frameCount_8008D3FC) & 0xF) << 4;
    ((char*)dword_8008D434)[0x4B6] = ((*(volatile int*)&frameCount_8008D3FC) & 0xF) << 4;
    sub_80040298(pOT_8008D454 + idx, (char*)dword_8008D434 + 0x4B0, 5);
    sub_80040298(pOT_8008D454 + idx, dword_8008D440 + 0x1E0, 2);
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
