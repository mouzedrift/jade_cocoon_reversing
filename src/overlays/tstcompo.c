// TSTCOMPO.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

INCLUDE_OVERLAY_ASM(tstcompo, dword_800A05A0);

typedef struct TstCompoBlk8 { char b[8]; } TstCompoBlk8;
typedef struct TstCompoD
{
    int f0;
    char pad_4[0x17C];
    int f180;
    int f184;
    char pad_188[8];
    int f190;
    int f194;
    int f198;
    char pad_19C[0x3C];
    TstCompoBlk8 f1D8;
    short f1E0;
    short f1E2;
    int f1E4;
    int f1E8;
    int f1EC;
    int f1F0;
    int f1F4;
    int f1F8;
    int f1FC;
    int f200;
    int f204;
    int f208;
    int f20C;
    int f210;
    int f214;
    int f218;
    int f21C;
    int f220;
    int f224;
    int f228;
    int f22C;
} TstCompoD;
extern void sub_800A097C();
extern TstCompoBlk8* name_800A250C[];
void sub_800A0800(int* task, TstCompoD* c)
{
    c->f184 = 3;
    c->f0 = 0;
    c->f194 = 0;
    c->f190 = 0;
    c->f180 = 0;
    c->f198 = 0;
    drawEnvRed_8008D448[0] = 0x40;
    drawEnvRed_8008D448[1] = 0x40;
    drawEnvRed_8008D448[2] = 0x80;
    sub_800A1BE0(c);
    sub_800A0918();
    c->f1E8 = 0;
    c->f1E4 = -1;
    c->f1EC = -1;
    c->f1E0 = 0;
    c->f1E2 = 0;
    c->f1D8 = *name_800A250C[c->f1E8 * 5];
    c->f1F4 = 0;
    c->f1F0 = 0;
    c->f210 = 0;
    c->f214 = 0;
    c->f218 = 0;
    c->f21C = 0;
    c->f220 = 0;
    c->f224 = 0;
    c->f228 = 0;
    c->f22C = 0;
    c->f208 = 0;
    c->f20C = 0;
    c->f1FC = 0;
    c->f200 = 0;
    c->f204 = 0;
    task[2] = (int)sub_800A097C;
}

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

extern void name_80010850();
void sub_800A1320(int* a)
{
    name_80010850(name_800A2768);
    a[0] = 2;
}

extern int name_80010A10(int);
extern int name_80010A44(int);
extern int name_800A2784;
extern void sub_800A1AFC(int* a);
#if 0 // near miss: store scheduling
void sub_800A1354(int* a)
{
    int v;
    if (name_80010A10(0))
    {
        a[1] = name_80010A44(0);
        sub_800A1AFC(a);
        a[0x188 / 4] = -1;
        a[0x198 / 4] = 0;
        v = name_800A2784;
        a[0] = 3;
        a[0x19C / 4] = v;
    }
}
#endif
INCLUDE_OVERLAY_ASM(tstcompo, sub_800A1354);

#if 0 // near miss: register allocation (n/base swapped)
extern int name_80024DC4(int);
void sub_800A13B8(int* a)
{
    if (name_80024DC4(a[1]))
    {
        if (a[0x188 / 4] <= 0)
        {
            int i = 0;
            char* b = (char*)a[1];
            int n;
            int m = n = *(unsigned short*)(b + 0x3E);
            a[0x188 / 4] = n;
            if (m != 0)
            {
                char* base = *(char**)(b + 0x44);
                do
                {
                    int c = base[i];
                    i++;
                    if (c != 0)
                    {
                        a[0x184 / 4] = i;
                        break;
                    }
                } while (i < m);
            }
        }
        else
        {
            a[0x184 / 4] = a[0x18C / 4];
        }
        a[0] = 4;
    }
}
#endif
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

extern unsigned short word_8009194C;
typedef struct TstCompoE
{
    int f0;
    int f4;
    char pad_8[0x146];
    short s14E;
    char pad_150[0x30];
    int f180;
    int f184;
    int f188;
    int f18C;
    int f190;
    int f194;
} TstCompoE;
extern unsigned short word_800918CC;
extern void name_8002556C(int a, int b);
extern void name_80025440(int a, int b, int c);
void sub_800A19A4(TstCompoE* c)
{
    unsigned short pad = word_800918CC;
    if (pad & 0x1000)
    {
        int v = c->f18C + 1;
        int t = c->f188 - 1;
        c->f18C = v;
        if (t < v)
        {
            c->f18C = t;
        }
    }
    else if (pad & 0x4000)
    {
        int v = c->f18C - 1;
        c->f18C = v;
        if (v <= 0)
        {
            c->f18C = 1;
        }
    }
    pad = word_8009194C;
    if (pad & 0x20)
    {
        if (c->f190)
        {
            name_8002556C(c->f4, c->f184);
            c->f190 = 0;
        }
        if (*(unsigned char*)(*(int*)(c->f4 + 0x44) + c->f18C) == 0)
        {
            c->f190 = 1;
        }
        else
        {
            c->f190 = 0;
        }
        if (c->f190)
        {
            name_80025440(c->f4, c->f18C, 0);
        }
        c->f194 = 0;
        c->f180 = 0;
        c->f0 = 3;
    }
    else if (pad & 0x40)
    {
        c->s14E = 0;
        c->f0 = 4;
    }
}

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

#if 0 // near miss: loop pointer strength reduction differs
typedef struct TstCompoEnt
{
    unsigned short a;
    unsigned short b;
    int p;
} TstCompoEnt;
extern unsigned short uiColor_8008B590;
extern void sub_8003E91C(int a, int b, void* c, int d);
extern void sub_80042460(int a, void* b, void* c, int d);
void sub_800A2030(int p, TstCompoEnt* e, int idx)
{
    unsigned short t[2];
    if (e)
    {
        while (e->p)
        {
            t[0] = e->a;
            t[1] = e->b;
            sub_8003E91C(1, e->p, t, idx);
            e++;
        }
    }
    if (p)
    {
        ((unsigned char*)t)[2] = 1;
        ((unsigned char*)t)[3] = 1;
        t[0] = uiColor_8008B590;
        sub_80042460(p, t, pOT_8008D454 + idx, 0);
    }
}
#endif
INCLUDE_OVERLAY_ASM(tstcompo, sub_800A2030);

INCLUDE_OVERLAY_ASM(tstcompo, dword_800A20EC);
