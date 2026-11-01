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


INCLUDE_ASM(sub_80036528);
// Matched
void sub_80036658(int idx)
{
    byte_80095460[(unsigned char)idx].field_2 = 0;
    byte_80095460[(unsigned char)idx].field_3 = 0;
}
// Matched
void sub_80036678(void)
{
    sub_80036658(0);
    sub_80036658(1);
}
INCLUDE_ASM(sub_800366A0);
// Matched
void sub_800367F0(int a0, unsigned char* a1)
{
    byte_80095460[*a1].field_2 = 0;
    byte_80095460[*a1].field_3 = 0;
}
#if 0
void sub_80036820(int a0)
{
}
#endif
INCLUDE_ASM(sub_80036820);
INCLUDE_ASM(sub_800368F8);
INCLUDE_ASM(sub_800369E0);
INCLUDE_ASM(sub_80036AB4);
INCLUDE_ASM(sub_80036BB0);
INCLUDE_ASM(sub_800374E0);
INCLUDE_ASM(sub_800375F8);
// Matched
void nullsub_5(void)
{
}
INCLUDE_ASM(sub_800376A8);
INCLUDE_ASM(sub_80037720);
// Matched
void sub_80037770(void)
{
    int* p = dword_8008D4A0[0x24 / 4];
    p[1] &= ~4;
    p[1] &= ~0x2000;
    sub_80039698(p);
}
INCLUDE_ASM(sub_800377B4);
INCLUDE_ASM(sub_80037828);
// Matched
void sub_800378CC(void)
{
    sub_800390F4(dword_8008D4A0[0x24 / 4], 1);
}
// Matched
short sub_800378F8(void)
{
    return ((short*)dword_8008D4A0[0x24 / 4])[4];
}
INCLUDE_ASM(sub_80037918);
// Matched
short sub_80037A4C(void)
{
    return ((short*)dword_8008D4A0[0x24 / 4])[0x12];
}
INCLUDE_ASM(sub_80037A6C);
// Matched
void sub_80037AC8(int a0)
{
    *(int*)dword_8008D4A0[0x24 / 4] = a0;
}
INCLUDE_ASM(sub_80037AE0);
INCLUDE_ASM(sub_80037C74);
INCLUDE_ASM(sub_80037F44);
INCLUDE_ASM(sub_80038230);
INCLUDE_ASM(sub_8003856C);
INCLUDE_ASM(sub_8003891C);
INCLUDE_ASM(sub_80038A5C);
INCLUDE_ASM(sub_80038CA8);
INCLUDE_ASM(sub_80038D64);
INCLUDE_ASM(sub_80038E2C);
#if 0
void sub_800390F4(void* arg0, int arg1)
{
}
#endif
INCLUDE_ASM(sub_800390F4);
INCLUDE_ASM(sub_800395D0);
INCLUDE_ASM(sub_80039620);
#if 0
void sub_80039698(int* a0)
{
}
#endif
INCLUDE_ASM(sub_80039698);
INCLUDE_ASM(sub_8003970C);
INCLUDE_ASM(sub_8003983C);
INCLUDE_ASM(sub_800398B4);
INCLUDE_ASM(sub_80039E14);
