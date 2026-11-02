// LOAD.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

extern int dword_800BE184;
extern int dword_800BE14C;
extern int dword_800BE150;
extern int dword_800BE174;
extern int dword_800BE188[];
extern int dword_800BE2C4;
extern int dword_800BE2C8;
extern int dword_800BE2CC;
extern int dword_800BE2D0;
extern int dword_800BE2D4;
extern int dword_800BE2D8;
extern int dword_800BE2DC;
extern int dword_800BE2E0;
extern int** dword_8008D480;
extern int sub_8004EE8C(void);
extern void sub_8004EDE8(void);
extern void sub_8004EE54(void);
extern int sub_8004EDD8(void);
extern void sub_800BC9DC(int a, int* b, int* c);
extern void sub_800B7674(int a, int b);

INCLUDE_OVERLAY_ASM(load, dword_800B66C0);

void sub_800B7650(void)
{
    sub_800B7674(4, 0);
}

INCLUDE_OVERLAY_ASM(load, sub_800B7674);

INCLUDE_OVERLAY_ASM(load, sub_800B7894);

void sub_800B78B8(int v)
{
    dword_8008D480[9][22] = v;
}

INCLUDE_OVERLAY_ASM(load, sub_800B78D0);

int sub_800B7914(void)
{
    return dword_8008D480[9][2];
}

void sub_800B7934(void)
{
}

int sub_800B793C(void)
{
    return dword_800BE184;
}

INCLUDE_OVERLAY_ASM(load, sub_800B794C);

INCLUDE_OVERLAY_ASM(load, sub_800B79F8);

INCLUDE_OVERLAY_ASM(load, sub_800B80F8);

INCLUDE_OVERLAY_ASM(load, sub_800B82FC);

INCLUDE_OVERLAY_ASM(load, sub_800B847C);

INCLUDE_OVERLAY_ASM(load, sub_800B85AC);

INCLUDE_OVERLAY_ASM(load, sub_800B867C);

INCLUDE_OVERLAY_ASM(load, sub_800B877C);

INCLUDE_OVERLAY_ASM(load, sub_800B8984);

INCLUDE_OVERLAY_ASM(load, sub_800B8A20);

INCLUDE_OVERLAY_ASM(load, sub_800B8AE4);

INCLUDE_OVERLAY_ASM(load, sub_800B8BD4);

INCLUDE_OVERLAY_ASM(load, sub_800B9220);

INCLUDE_OVERLAY_ASM(load, sub_800B92C0);

INCLUDE_OVERLAY_ASM(load, sub_800B9360);

INCLUDE_OVERLAY_ASM(load, sub_800B9470);

INCLUDE_OVERLAY_ASM(load, sub_800B952C);

INCLUDE_OVERLAY_ASM(load, sub_800B9654);

INCLUDE_OVERLAY_ASM(load, sub_800B9724);

INCLUDE_OVERLAY_ASM(load, sub_800B98C4);

INCLUDE_OVERLAY_ASM(load, sub_800B9A8C);

INCLUDE_OVERLAY_ASM(load, sub_800BA234);

INCLUDE_OVERLAY_ASM(load, sub_800BA3EC);

INCLUDE_OVERLAY_ASM(load, sub_800BA968);

INCLUDE_OVERLAY_ASM(load, sub_800BA9AC);

INCLUDE_OVERLAY_ASM(load, sub_800BA9F0);

INCLUDE_OVERLAY_ASM(load, sub_800BAAE0);

INCLUDE_OVERLAY_ASM(load, sub_800BAC14);

INCLUDE_OVERLAY_ASM(load, sub_800BAC68);

INCLUDE_OVERLAY_ASM(load, sub_800BACBC);

INCLUDE_OVERLAY_ASM(load, sub_800BADE0);

void sub_800BADF4(void)
{
    int a = 0;
    int b = 0;
    sub_800BC9DC(0, &b, &a);
}

int sub_800BAE24(void)
{
    return 1;
}

int sub_800BAE2C(void)
{
    return dword_800BE14C;
}

int sub_800BAE3C(void)
{
    return dword_800BE150;
}

int sub_800BAE4C(int i)
{
    int* p = dword_800BE188;
    return p[i];
}

INCLUDE_OVERLAY_ASM(load, sub_800BAE68);

INCLUDE_OVERLAY_ASM(load, sub_800BAF0C);

INCLUDE_OVERLAY_ASM(load, sub_800BAFB0);

INCLUDE_OVERLAY_ASM(load, sub_800BB0E4);

INCLUDE_OVERLAY_ASM(load, sub_800BB23C);

INCLUDE_OVERLAY_ASM(load, sub_800BB2AC);

INCLUDE_OVERLAY_ASM(load, sub_800BB4A8);

INCLUDE_OVERLAY_ASM(load, sub_800BB5DC);

INCLUDE_OVERLAY_ASM(load, sub_800BB64C);

INCLUDE_OVERLAY_ASM(load, sub_800BB68C);

INCLUDE_OVERLAY_ASM(load, sub_800BB6F4);

INCLUDE_OVERLAY_ASM(load, sub_800BB9F4);

INCLUDE_OVERLAY_ASM(load, sub_800BBA5C);

INCLUDE_OVERLAY_ASM(load, sub_800BBD04);

INCLUDE_OVERLAY_ASM(load, sub_800BBE8C);

INCLUDE_OVERLAY_ASM(load, sub_800BBED0);

INCLUDE_OVERLAY_ASM(load, sub_800BBF88);

INCLUDE_OVERLAY_ASM(load, sub_800BC0C4);

INCLUDE_OVERLAY_ASM(load, sub_800BC17C);

INCLUDE_OVERLAY_ASM(load, sub_800BC2B8);

INCLUDE_OVERLAY_ASM(load, sub_800BC3D0);

INCLUDE_OVERLAY_ASM(load, sub_800BC510);

INCLUDE_OVERLAY_ASM(load, sub_800BC628);

INCLUDE_OVERLAY_ASM(load, sub_800BC768);

// Not matched: the original keeps &var in a register (lui/addiu) for the load and the store
INCLUDE_OVERLAY_ASM(load, sub_800BC9C8);

INCLUDE_OVERLAY_ASM(load, sub_800BC9DC);

INCLUDE_OVERLAY_ASM(load, sub_800BCAF8);

INCLUDE_OVERLAY_ASM(load, sub_800BCCF4);

INCLUDE_OVERLAY_ASM(load, sub_800BCEA8);

INCLUDE_OVERLAY_ASM(load, sub_800BCF64);

INCLUDE_OVERLAY_ASM(load, sub_800BD018);

INCLUDE_OVERLAY_ASM(load, sub_800BD06C);

INCLUDE_OVERLAY_ASM(load, sub_800BD118);

INCLUDE_OVERLAY_ASM(load, sub_800BD174);

// Not decompilable as plain C: the store is "sw $v0,sym" (lui $at) in the delay slot, as hand-written asm does
INCLUDE_OVERLAY_ASM(load, sub_800BD17C);

INCLUDE_OVERLAY_ASM(load, sub_800BD18C);

INCLUDE_OVERLAY_ASM(load, sub_800BD208);

unsigned sub_800BD274(void)
{
    return (unsigned)dword_800BE174 >> 31;
}

INCLUDE_OVERLAY_ASM(load, sub_800BD284);

// Not decompilable as plain C: the store is "sw $v0,sym" (lui $at) in the delay slot, as hand-written asm does
INCLUDE_OVERLAY_ASM(load, sub_800BD2A0);

// Not decompilable as plain C: the store is "sw $v0,sym" (lui $at) in the delay slot, as hand-written asm does
INCLUDE_OVERLAY_ASM(load, sub_800BD2B4);

// Not decompilable as plain C: the store is "sw $v0,sym" (lui $at) in the delay slot, as hand-written asm does
INCLUDE_OVERLAY_ASM(load, sub_800BD2C8);

INCLUDE_OVERLAY_ASM(load, sub_800BD2DC);

INCLUDE_OVERLAY_ASM(load, sub_800BD2F0);

// Not decompilable as plain C: the store is "sw $v0,sym" (lui $at) in the delay slot, as hand-written asm does
INCLUDE_OVERLAY_ASM(load, sub_800BD304);

// Not decompilable as plain C: the store is "sw $v0,sym" (lui $at) in the delay slot, as hand-written asm does
INCLUDE_OVERLAY_ASM(load, sub_800BD318);

#if 0
// Not matched: epilogue order differs (addiu sp before jr, nop in delay slot)
int sub_800BD32C(void)
{
    sub_8004EDE8();
    sub_8004EE54();
    return sub_8004EDD8();
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BD32C);

INCLUDE_OVERLAY_ASM(load, sub_800BD35C);

#if 0
// Not matched: epilogue order differs
int sub_800BD538(void)
{
    return sub_8004EE8C();
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BD538);

INCLUDE_OVERLAY_ASM(load, sub_800BD558);

INCLUDE_OVERLAY_ASM(load, sub_800BD60C);

INCLUDE_OVERLAY_ASM(load, sub_800BD714);

INCLUDE_OVERLAY_ASM(load, sub_800BD7EC);

#if 0
// Not matched: load scheduling differs
int sub_800BD8C4(void)
{
    return dword_800BE2C4 + dword_800BE2C8 * 2 + dword_800BE2CC * 4 + dword_800BE2D0 * 8;
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BD8C4);

#if 0
// Not matched: load scheduling differs
int sub_800BD900(void)
{
    return dword_800BE2D4 + dword_800BE2D8 * 2 + dword_800BE2DC * 4 + dword_800BE2E0 * 8;
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BD900);

INCLUDE_OVERLAY_ASM(load, dword_800BD93C);
