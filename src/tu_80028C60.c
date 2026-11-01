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


INCLUDE_ASM(sub_80028C60);
INCLUDE_ASM(sub_80028DC0);
// Matched
int GetTiyFileCount_80028E68(int* p)
{
    return p[0];
}
extern void sub_800295D8(int* a0, int a1, int* a2, int a3, int a4);
extern void sub_80028EEC(int* a0, int a1, int* a2, int a3, int a4);
// Matched
void sub_80028E74(int* a0, int a1, int* a2, int a3, int a4)
{
    int v = *(int*)a3;
    sub_800295D8(a0, a1, a2, v, a4);
    sub_80028EEC(a0, a1, a2, a3, v);
}
INCLUDE_ASM(sub_80028EEC);
INCLUDE_ASM(sub_80028FDC);
INCLUDE_ASM(sub_800290FC);
INCLUDE_ASM(sub_800292D0);
INCLUDE_ASM(sub_800295D8);
// Matched
void sub_80029674(void* p)
{
    char buf[0x28];
    sub_80029708(buf, p);
    sub_800296A0(buf);
}
#if 0
void sub_800296A0(void* arg0)
{
}
#endif
INCLUDE_ASM(sub_800296A0);
#if 0
void sub_80029708(void* arg0, void* arg1)
{
}
#endif
INCLUDE_ASM(sub_80029708);
INCLUDE_ASM(sub_800297C0);
// Matched
void sub_80029868(int a0, int a1, int a2)
{
    char buf[0x28];
    sub_80029708(buf, (void*)a1);
    sub_800298AC(a0, a2, buf);
}
#if 0
void sub_800298AC(int a0, int a1, void* a2)
{
}
#endif
INCLUDE_ASM(sub_800298AC);
// Matched
void sub_800299DC(void* p, void* q)
{
    char buf[0x28];
    sub_80029708(buf, q);
    InitPolyFT4_80029A10(p, buf);
}
#if 0
void InitPolyFT4_80029A10(void* a0, void* a1)
{
}
#endif
INCLUDE_ASM(InitPolyFT4_80029A10);
INCLUDE_ASM(sub_80029C68);
INCLUDE_ASM(sub_80029CB4);
INCLUDE_ASM(sub_80029D00);
INCLUDE_ASM(sub_80029EA8);
INCLUDE_ASM(sub_8002A040);
