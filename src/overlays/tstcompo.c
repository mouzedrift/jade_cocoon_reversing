// TSTCOMPO.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

extern unsigned short padPressed_8009194C;
extern unsigned short padRepeat_800918CC;

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

extern unsigned short padHeld_800918D0[];
extern void sub_800A0AB8();
extern void sub_800A1320();
extern void sub_800A1354();
extern void sub_800A13B8();
extern void sub_800A1468();
extern void sub_800A15F4();
extern void sub_800A1804();
extern void sub_800A194C();
extern void sub_800A19A4();
extern void sub_800A1AD0();
extern void sub_800A1C14();
void sub_800A097C(int* task, int* c)
{
    if (c[0] != 1 && c[0] != 3 && c[0] != 6 && (padHeld_800918D0[0] & 4) && (padHeld_800918D0[0] & 1) &&
        (padHeld_800918D0[0] & 0x90A) == 0x90A)
    {
        sub_800A1AD0(c);
        bStopDrawingMovie_8008D45C = 1;
        return;
    }
    switch (c[0])
    {
    case 0:
        sub_800A0AB8(c);
        break;
    case 1:
        sub_800A1320(c);
        break;
    case 2:
        sub_800A1354(c);
        break;
    case 3:
        sub_800A13B8(c);
        break;
    case 4:
        sub_800A194C(c);
        sub_800A1C14(c);
        sub_800A1468(c);
        sub_800A1804(c);
        break;
    case 5:
        sub_800A15F4(c);
        sub_800A19A4(c);
        break;
    case 6:
        sub_800A1AD0(c);
        break;
    }
}

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A0AB8);

extern void name_80010850();
void sub_800A1320(int* a)
{
    name_80010850(name_800A2768);
    a[0] = 2;
}

extern int name_80010A10(int);
extern int name_80010A44(int);
extern void sub_800A1AFC();
void sub_800A1354(int* a)
{
    if (name_80010A10(0))
    {
        a[1] = name_80010A44(0);
        sub_800A1AFC(a);
        a[0x188 / 4] = -1;
        a[0x198 / 4] = 0;
        a[0x19C / 4] = name_800A2768[7];
        a[0] = 3;
    }
}

extern int name_80024DC4(int);
void sub_800A13B8(int* a)
{
    if (name_80024DC4(a[1]))
    {
        if (a[0x188 / 4] <= 0)
        {
            int i;
            char* b = (char*)a[1];
            a[0x188 / 4] = *(unsigned short*)(b + 0x3E);
            for (i = 0; i < a[0x188 / 4]; i++)
            {
                if ((*(unsigned char**)(a[1] + 0x44))[i] != 0)
                {
                    a[0x184 / 4] = i;
                    break;
                }
            }
        }
        else
        {
            a[0x184 / 4] = a[0x18C / 4];
        }
        a[0] = 4;
    }
}

extern void* memset(void* p, int c, unsigned int n);
extern void sub_80046A58(void* a, void* b, int c);
extern void sub_800459E4(void* a, void* b, void* c, int d);
extern char name_800A2588[];
extern char name_800A2570[];
void sub_800A1468(int* c)
{
    VECTOR pos;
    char z[8];
    VECTOR scale;
    memset(z, 0, 8);
    pos.vx = c[0x16C / 4];
    pos.vy = c[0x170 / 4];
    pos.vz = c[0x174 / 4];
    pos.vy += 0xFA;
    c[0x1A0 / 4] = (int)sub_80024E90((void*)c[1], c[0x19C / 4]);
    scale.vx = ((int*)c[0x1A0 / 4])[0] + (c[0x198 / 4] << 12);
    scale.vy = ((int*)c[0x1A0 / 4])[1] + (c[0x198 / 4] << 12);
    scale.vz = ((int*)c[0x1A0 / 4])[2] + (c[0x198 / 4] << 12);
    c[0x1A4 / 4] = (int)sub_80024EC8((void*)c[1], c[0x19C / 4]);
    c[0x1BC / 4] = (int)(*(char**)(c[1] + 0x54) + c[0x184 / 4] * 28);
    c[0x1A8 / 4] = *(int*)(c[1] + 0x50);
    c[0x1AC / 4] = (int)&pos;
    c[0x1B0 / 4] = (int)z;
    c[0x1B4 / 4] = (int)(c + 3);
    c[0x1B8 / 4] = c[0x1A4 / 4];
    c[0x1C0 / 4] = (unsigned)c[0x180 / 4] % *(unsigned*)c[0x1BC / 4];
    c[0x1C4 / 4] = 0;
    c[0x1C8 / 4] = (int)name_800A2588;
    c[0x1CC / 4] = (int)&scale;
    c[0x1D0 / 4] = (int)pOT_8008D690;
    sub_80046A58(c + 0x1A8 / 4, name_800A2570, *(int*)(c[1] + 0x54));
    sub_800459E4(c + 3, (char*)c[1] + 0x5C, pOT_8008D690, 0);
}

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A15F4);

typedef struct TstCompoF
{
    char pad_0[0x14E];
    short s14E;
    char pad_150[0x30];
    int i180;
    char pad_184[0x10];
    int i194;
    int i198;
    int i19C;
    char pad_1A0[0x1C];
    unsigned int* p1BC;
} TstCompoF;
void sub_800A1804(TstCompoF* c)
{
    if (c->i194)
    {
        if (padRepeat_800918CC & 0x80)
        {
            c->i180++;
        }
        else if (padRepeat_800918CC & 0x10)
        {
            if (--c->i180 < 0)
            {
                c->i180 = *c->p1BC - 1;
            }
        }
        c->i180 = c->i180 % *c->p1BC;
    }
    else
    {
        c->i180++;
    }
    if (padPressed_8009194C & 0x40)
    {
        c->s14E = 0;
        c->i194 = !c->i194;
    }
    if (c->i194 == 0)
    {
        if (padPressed_8009194C & 0x100)
        {
            c->i198 = (c->i198 + 1) & 3;
        }
        if (padPressed_8009194C & 0x10)
        {
            c->i19C = (c->i19C + 1) % 5;
        }
    }
}

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

void sub_800A194C(TstCompoC* c)
{
    if (padPressed_8009194C & 0x800)
    {
        c->state = 6;
    }
    else if (padPressed_8009194C & 0x20)
    {
        c->state = 5;
        c->f1FC = 0;
        c->f18C = c->f184;
        c->f200 = c->f180;
        c->f204 = c->f184;
    }
}

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
extern void name_8002556C(int a, int b);
extern void name_80025440(int a, int b, int c);
void sub_800A19A4(TstCompoE* c)
{
    unsigned short pad = padRepeat_800918CC;
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
    pad = padPressed_8009194C;
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
    FreeModelTask_8001098C(0);
    *a = 0;
}

typedef struct TstCompoBone
{
    short s0;
    short s2;
    short s4;
    short s6;
} TstCompoBone;
extern TstCompoBone dword_80079140[];
extern void sub_80019B14(void* p, char* a1, char* a2);
extern char* sub_80024F00(void* p, int n);
extern char* sub_80024F38(void* p, int n);
typedef struct TstCompoSkel
{
    int f0;
    int f4;
    int f8;
    TstCompoBone bones[1];
} TstCompoSkel;
void sub_800A1AFC(TstCompoSkel* a)
{
    int i;
    char* r;
    for (i = 0; dword_80079140[i].s0 >= 0; i++)
    {
        a->bones[i] = dword_80079140[i];
    }
    a->bones[i] = dword_80079140[i];
    r = sub_80024F00((void*)a->f4, name_800A2768[7]);
    sub_80019B14(a->bones, r, sub_80024F38((void*)a->f4, name_800A2768[7]));
}

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

extern char name_800A2560[];
// Matched
int sub_800A200C()
{
    DrawIntroMovie_8001AF64(name_800A2560);
    return 6;
}

typedef struct TstCompoEnt
{
    unsigned short a;
    unsigned short b;
    int p;
} TstCompoEnt;
extern unsigned short uiColor_8008B590;
extern void DrawText_8003E91C(int a, int b, void* c, int d);
extern void DrawWindow_80042460(int a, void* b, void* c, int d);
void sub_800A2030(int p, TstCompoEnt* e, int idx)
{
    unsigned short t[2];
    if (e)
    {
        int i = 0;
        while (e[i].p)
        {
            t[0] = e[i].a;
            t[1] = e[i].b;
            DrawText_8003E91C(1, e[i].p, t, idx);
            i++;
        }
    }
    if (p)
    {
        ((unsigned char*)t)[2] = 1;
        ((unsigned char*)t)[3] = 1;
        t[0] = uiColor_8008B590;
        DrawWindow_80042460(p, t, pOT_8008D454 + idx, 0);
    }
}

INCLUDE_OVERLAY_ASM(tstcompo, dword_800A20EC);
