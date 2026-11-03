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
#include "tiy.h"



// Matched
void sub_8003CF88(short x, short y, int idx)
{
    publicTiySprts_8008D434[60].x0 = x;
    publicTiySprts_8008D434[60].y0 = y;
    publicTiySprts_8008D434[60].r0 = (unsigned int)frameCount_8008D3FC % 16 * 16;
    publicTiySprts_8008D434[60].g0 = (unsigned int)frameCount_8008D3FC % 16 * 16;
    publicTiySprts_8008D434[60].b0 = (unsigned int)frameCount_8008D3FC % 16 * 16;
    AddPrimCopy_80040298(pOT_8008D454 + idx, &publicTiySprts_8008D434[60], 5);
    AddPrimCopy_80040298(pOT_8008D454 + idx, &publicTiyTPages_8008D440[60], 2);
}
extern void DrawPublicTiySprt_80033080(void* a, int b, int c);
// Matched
void sub_8003D034(unsigned short* pPos, int a1)
{
    short r[2];
    r[0] = pPos[0] - 13;
    r[1] = pPos[1] - 6;
    SetSemiTrans(&publicTiySprts_8008D434[5], 1);
    DrawPublicTiySprt_80033080(r, 5, a1);
}
// Matched
void sub_8003D090(short x, short y, int a2, int a3, int idx)
{
    int r = 0;
    int t;
    switch ((unsigned int)frameCount_8008D3FC % 12)
    {
    case 0:
    case 1:
    case 10:
    case 11:
        r = 0;
        break;
    case 2:
    case 3:
    case 8:
    case 9:
        r = 1;
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        r = 2;
        break;
    }
    t = r + 0x10;
    publicTiySprts_8008D434[5].x0 = x - t;
    publicTiySprts_8008D434[5].y0 = y - 10;
    SetSemiTrans(&publicTiySprts_8008D434[5], 1);
    AddPrimCopy_80040298(pOT_8008D454 + idx, &publicTiySprts_8008D434[5], 5);
    AddPrimCopy_80040298(pOT_8008D454 + idx, &publicTiyTPages_8008D440[5], 2);
}
