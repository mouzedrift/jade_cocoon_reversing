// TSTMODEL.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

INCLUDE_OVERLAY_ASM(tstmodel, dword_800A05A0);

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A09C0);

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A0A8C);

typedef struct TstModelA
{
    char pad_0[0x170];
    short s170;
    short s172;
    short s174;
    char pad_176[6];
    int i17C;
    char pad_180[8];
    int i188;
    char pad_18C[4];
    int i190;
    int i194;
    int i198;
    short s19C;
    short s19E;
    short s1A0;
    char pad_1A2[0x4E];
    short s1F0;
    short s1F2;
    short s1F4;
} TstModelA;

// Matched
void sub_800A0BC0(TstModelA* a)
{
    a->s174 = 0x4B0;
    a->s170 = 0;
    a->i190 = 0;
    a->i194 = 0;
    a->i198 = 0;
    a->s19C = 0;
    a->s19E = 0;
    a->s1A0 = 0;
    a->s1F0 = 0;
    a->s1F2 = 0;
    a->s1F4 = 0;
    a->i188 = -0xFA;
    a->i17C = -0xFA;
}

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A0C00);

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A0EC8);

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A0F20);

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A104C);

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A1428);

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A1614);

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A17B8);

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A18F4);

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A19E4);

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A1A24);

// Matched
extern char name_800A1EDC[];
int sub_800A1B24()
{
    DrawIntroMovie_8001AF64(name_800A1EDC);
    return 6;
}

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A1B48);

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A1CAC);

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A1D70);

INCLUDE_OVERLAY_ASM(tstmodel, dword_800A1E84);
