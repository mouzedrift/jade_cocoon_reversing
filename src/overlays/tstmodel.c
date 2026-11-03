// TSTMODEL.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

INCLUDE_OVERLAY_ASM(tstmodel, dword_800A05A0);

typedef struct TstModelTbl { int a; int b; int c; } TstModelTbl;
extern TstModelTbl name_800A33B0[];
extern void sub_800A0A8C();
void sub_800A09C0(int* task, int* c)
{
    int i;
    c[0] = 0;
    c[1] = 0;
    c[2] = 0;
    c[3] = 0;
    c[4] = 0;
    c[5] = 0;
    c[8] = 0;
    ((short*)c)[0x172 / 2] = 0;
    c[7] = 0;
    if (name_800A33B0[0].a >= 0)
    {
        do
        {
            i = c[7] + 1;
            c[7] = i;
        } while (name_800A33B0[i].a >= 0);
    }
    c[0x1B8 / 4] = 0;
    c[0x1A8 / 4] = 0;
    c[0x1B4 / 4] = 0;
    c[0x1A4 / 4] = 0;
    c[0x1BC / 4] = 0;
    sub_800A0BC0(c);
    drawEnvRed_8008D448[0] = 0x40;
    drawEnvRed_8008D448[1] = 0x40;
    drawEnvRed_8008D448[2] = 0x80;
    task[2] = (int)sub_800A0A8C;
}

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

extern int off_8007DC70;
extern int InitModelList_80024ADC(int* a, int b, int c);
extern void LoadModel_80025200(int a, int b, int c, int d, int e);
void sub_800A0EC8(int* a)
{
    InitModelList_80024ADC(&a[5], off_8007DC70, 1);
    LoadModel_80025200(a[5], a[9], a[8], 2, 0);
    a[8] = 0;
    a[0] = 2;
}

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A0F20);

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A104C);

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A1428);

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A1614);

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A17B8);

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A18F4);

void sub_800A19E4(int* a)
{
    if (a[5])
    {
        FreeModelList_80024BB0(&a[5]);
    }
    a[5] = 0;
    a[0] = 0;
}

extern int name_8008D600[];
extern short name_8008D4C8[];
extern unsigned char name_8008D460[];
extern short name_8008D474[];
extern int geomScreenDistance_8008B548;
extern int name_8003B548();
extern void name_8004D0E8();
void sub_800A1A24(int* c)
{
    int v[3];
    int yaw;
    name_8008D600[0] = c[0x178 / 4];
    name_8008D600[1] = c[0x17C / 4];
    name_8008D600[2] = c[0x180 / 4];
    v[0] = c[0x184 / 4] - c[0x178 / 4];
    v[1] = c[0x188 / 4] - c[0x17C / 4];
    v[2] = c[0x18C / 4] - c[0x180 / 4];
    yaw = ratan2_8003B548(v[0], v[2]);
    name_8008D4C8[1] = -yaw;
    name_8008D4C8[0] = name_8003B548(v[1], ISqrt_8003B918(LengthSquared2D_8003B8BC(v[0], v[2])));
    name_8008D4C8[2] = 0;
    name_8008D460[0] = 0x40;
    name_8008D460[1] = 0x40;
    name_8008D460[2] = 0x40;
    name_8008D474[0] = 0;
    name_8008D474[1] = 0;
    geomScreenDistance_8008B548 = 0xA0;
    name_8004D0E8();
}

// Matched
extern char name_800A1EDC[];
int sub_800A1B24()
{
    DrawIntroMovie_8001AF64(name_800A1EDC);
    return 6;
}

INCLUDE_OVERLAY_ASM(tstmodel, sub_800A1B48);

typedef struct TstModelB
{
    int flags;
    unsigned short s4;
    unsigned short s6;
    short s8;
    short sA;
    short sC;
    unsigned short sE;
} TstModelB;
extern short name_800A37F4[];
extern short name_800A37FC[];
void sub_800A1CAC(TstModelB* p, int k)
{
    if (p->flags & name_800A37F4[k - 1])
    {
        if ((p->flags & 1) && (unsigned)(k - 1) < 2)
        {
            p->s6 += name_800A37FC[k - 1] * (p->s8 - 1);
        }
        else if ((p->flags & 2) && (unsigned)(k - 3) < 2)
        {
            p->s6 += name_800A37FC[k - 1] * p->s8 * (p->sA - 1);
        }
    }
}

extern int sub_800A1B48();
#if 0 // near miss: the original shares the shifted copy of sE between both tests
extern int name_8003D198();
extern void PlaySfx_80031494();
int sub_800A1D70(TstModelB* p)
{
    int old = (short)p->s6;
    int k = sub_800A1B48(p);
    unsigned short t = p->sE;
    short ts = t;
    if (k == 3)
    {
        if (ts >= p->s8)
        {
            p->sE = t - p->s8;
            PlaySfx_80031494(0x7F);
            return 8;
        }
    }
    else if (k == 4)
    {
        if (ts < p->sC - p->s8 * p->sA)
        {
            p->sE = t + p->s8;
            PlaySfx_80031494(0x7F);
            return 7;
        }
    }
    sub_800A1CAC(p, k);
    p->sE = name_8003D198(p->sC - p->s8 * p->sA + 1, (short)p->sE, p->s8 * p->sA, 0);
    if (old != (short)p->s6)
    {
        PlaySfx_80031494(0x7F);
    }
    return 9;
}
#endif
INCLUDE_OVERLAY_ASM(tstmodel, sub_800A1D70);

INCLUDE_OVERLAY_ASM(tstmodel, dword_800A1E84);
