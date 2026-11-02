// TSTCOMPO.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

INCLUDE_OVERLAY_ASM(tstcompo, dword_800A05A0);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A0800);

extern int name_800A2768[];
extern int dword_8007DC74;
void sub_800A0918()
{
    int* p = name_800A2768;
    p[0] = 3;
    p[1] = 1;
    p[2] = 0xC;
    p[3] = 0x29;
    p[4] = 0x555;
    p[5] = 0x555;
    p[6] = 0x555;
    p[7] = 4;
    p[8] = 0;
    p[9] = 0;
    p[10] = 0x4C;
    p[11] = 0;
    p[12] = dword_8007DC74;
}

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A097C);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A0AB8);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A1320);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A1354);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A13B8);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A1468);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A15F4);

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A1804);

extern unsigned short word_8009194C;
typedef struct TstCompoC
{
    int state;
    char pad_4[0x17C];
    int f180;
    int f184;
    char pad_188[4];
    int f18C;
    char pad_190[0x6C];
    int f1FC;
    int f200;
    int f204;
} TstCompoC;

#if 0 // near miss: original keeps the argument in a2 (register allocation)
void sub_800A194C(TstCompoC* c)
{
    unsigned short pad = word_8009194C;
    if (pad & 0x800)
    {
        c->state = 6;
    }
    else if (pad & 0x20)
    {
        int x = c->f184;
        int y = c->f180;
        int z = x;
        c->state = 5;
        c->f1FC = 0;
        c->f18C = x;
        c->f200 = y;
        c->f204 = z;
    }
}
#endif
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
