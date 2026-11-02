// TSTCOMPO.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

INCLUDE_OVERLAY_ASM(tstcompo, dword_800A05A0);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A0800);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A0918);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A097C);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A0AB8);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A1320);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A1354);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A13B8);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A1468);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A15F4);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A1804);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A194C);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A19A4);

// Matched
void sub_800A1AD0(int* a)
{
    sub_8001098C(0);
    *a = 0;
}

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A1AFC);

typedef struct TstCompoA
{
    char pad_0[0x14C];
    short s14C;
    short s14E;
    short s150;
    char pad_152[6];
    int i158;
    char pad_15C[8];
    int i164;
    char pad_168[4];
    int i16C;
    int i170;
    int i174;
    short s178;
    short s17A;
    short s17C;
} TstCompoA;

// Matched
void sub_800A1BE0(TstCompoA* a)
{
    a->s150 = 0x4B0;
    a->s14C = 0;
    a->i16C = 0;
    a->i170 = 0;
    a->i174 = 0;
    a->s178 = 0;
    a->s17A = 0;
    a->s17C = 0;
    a->i164 = -0xFA;
    a->i158 = -0xFA;
}

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A1C14);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A1E68);

// Matched
extern char name_800A2560[];
int sub_800A200C()
{
    DrawIntroMovie_8001AF64(name_800A2560);
    return 6;
}

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A2030);

INCLUDE_OVERLAY_ASM(tstcompo, dword_800A20EC);
