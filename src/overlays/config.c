// CONFIG.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"

typedef struct { char b[8]; } Bytes8Config;

typedef struct CfgSettingsConfig
{
    unsigned int w0;
    char pad_4[0x18];
    unsigned int a_1C : 3;
    unsigned int b_1C : 1;
    unsigned int c_1C : 1;
    unsigned int d_1C : 1;
    unsigned int e_1C : 1;
    unsigned int f_1C : 7;
    unsigned int g_1C : 7;
    unsigned int h_1C : 1;
    unsigned int i_1C : 1;
    unsigned int j_1C : 1;
    unsigned int k_1C : 8;
    unsigned char b_20;
} CfgSettingsConfig;

typedef struct CfgCtxConfig
{
    char pad_0[2];
    short prev_2;
    short cur_4;
    char pad_6[2];
    unsigned char f8, f9, fa, fb, fc, fd, fe, ff, f10, f11, f12, f13, f14, f15, f16;
    char pad_17[0x30 - 0x17];
    int f30;
    short f34;
    short pad_36;
    int f38;
    Bytes8Config f3c;
    short f44;
    short f46;
} CfgCtxConfig;

typedef struct CfgTaskConfig
{
    unsigned int flags_0;
    int pad_4;
    void (*next_8)();
    int pad_C;
    int pad_10;
    CfgCtxConfig* ctx_14;
} CfgTaskConfig;

typedef struct CfgHolderConfig
{
    char pad_0[0x10];
    CfgTaskConfig t_10;
} CfgHolderConfig;
extern CfgHolderConfig* dword_8008B4B8;
extern CfgSettingsConfig dword_8008B570;
extern unsigned int dword_8008B58C;
extern int dword_800C5944;
extern Bytes8Config dword_800C4CD4[];
extern char dword_800C592C[];
extern void sub_8002AE38(void* a0, void* a1, int a2, void* a3, int a4);
extern int sub_8003D380(int a);
extern int sub_8003D41C(int a);
extern void PlaySfx_80031494(int a);
extern int* dword_800C4CC0[];
extern char dword_800C2D40[];
extern char dword_800C2DA4[];
extern char dword_800C2DF4[];
extern char dword_800C2E5C[];
extern void sub_800C4BDC(int n);
typedef struct CfgDlgConfig
{
    int f0, f4, f8, fC, f10, f14;
} CfgDlgConfig;

typedef struct CfgBoxConfig
{
    short x_0;
    short y_2;
    int pad_4;
    short col_8;
    char c_A;
    char c_B;
} CfgBoxConfig;

extern CfgDlgConfig dword_800C2CD0;
extern CfgDlgConfig dword_800C2CE8;
extern char dword_800C4DDC[];
extern char dword_800C4E98[];
extern char* dword_8008D454;
extern unsigned short uiColor_8008B590;
extern void sub_8002A5A4(CfgDlgConfig* p);
extern void sub_8002C06C(void* p, int a, short b);
extern void sub_80042460(void* a0, void* a1, void* a2, unsigned int a3);
extern unsigned int sub_8002C64C(void);
extern char dword_800C5298[];
extern char dword_800C52BC[];
extern char dword_800C52E0[];
extern void sub_800309D8(void* p);
extern void sub_8002BE10();
extern void sub_8002B004(void*, int, int);
extern void sub_8003D794(void*, int);
extern void sub_800C2F70();
extern void sub_800C3060(CfgCtxConfig*);
extern void sub_800C383C(CfgCtxConfig*);
extern void sub_800C450C(CfgCtxConfig*);
extern void sub_800C3540(CfgCtxConfig*);
extern void sub_800C378C(CfgCtxConfig*);

INCLUDE_OVERLAY_ASM(config, dword_800C29D0);

// Matched
void sub_800C2EB4(void)
{
    CfgHolderConfig* h = dword_8008B4B8;
    CfgTaskConfig* t = &h->t_10;
    CfgCtxConfig* c = t->ctx_14;
    h->t_10.flags_0 = (h->t_10.flags_0 | 1) & 0xFFFF7FFF;
    sub_8002BE10();
    c->cur_4 = 0;
    c->prev_2 = 0;
    c->f3c = dword_800C4CD4[5];
    c->f44 = 0;
    c->f46 = 0;
    c->f38 = 0;
    c->f30 = 0;
    c->f34 = 0;
    sub_800C3060(c);
    sub_800C383C(c);
    dword_800C5944 = 1;
    t->next_8 = sub_800C2F70;
}

#if 0
// Not matched: the original keeps a second copy of the context pointer in another register
void sub_800C2F70(CfgTaskConfig* t, CfgCtxConfig* d)
{
    short old;
    CfgCtxConfig* c;
    sub_8002BE10();
    sub_800C383C(d);
    sub_800C450C(d);
    sub_8002B004(dword_800C592C, 0, 0xE);
    old = d->f44;
    sub_8003D794(&d->f3c, 0);
    c = d;
    if (old != c->f44)
    {
        sub_800C3060(c);
    }
    if (c->f30 == 0)
    {
        sub_800C3540(c);
    }
    if (c->cur_4 != -1)
    {
        if (c->cur_4 != 5)
        {
            sub_800C378C(c);
            if (d->cur_4 != 5)
            {
                return;
            }
        }
    }
    else if (d->cur_4 != 5)
    {
        return;
    }
    dword_800C5944 = 0;
    t->flags_0 = (t->flags_0 & ~1) | 0x8000;
}

#endif
INCLUDE_OVERLAY_ASM(config, sub_800C2F70);

// Matched
void sub_800C3060(CfgCtxConfig* c)
{
    CfgSettingsConfig* s = &dword_8008B570;
    c->f14 = ((unsigned char*)s)[0x1F] & 1;
    c->f8 = s->a_1C;
    c->f9 = s->b_1C;
    c->fa = s->c_1C;
    c->fb = s->d_1C;
    c->fc = s->e_1C;
    c->fd = s->f_1C / 16;
    c->fe = s->g_1C / 16;
    c->f15 = c->fd;
    c->f16 = c->fe;
    c->ff = s->b_20;
    c->f10 = s->h_1C;
    c->f11 = s->i_1C;
    if (c->f14 == 0)
    {
        c->f11 = 1;
    }
    if (dword_8008B570.w0 & 0x40)
    {
        c->f12 = 0;
    }
    else
    {
        c->f12 = 1;
    }
    c->fa = c->f9;
    c->f13 = (dword_8008B58C >> 0x17) & 1;
    if (c->f14 == 0)
    {
        c->f13 = 1;
    }
    if (c->f11 == 0)
    {
        c->f13 = 0;
    }
}

INCLUDE_OVERLAY_ASM(config, sub_800C31DC);

INCLUDE_OVERLAY_ASM(config, sub_800C3540);

INCLUDE_OVERLAY_ASM(config, sub_800C378C);

INCLUDE_OVERLAY_ASM(config, sub_800C383C);

// Matched
void sub_800C38CC(CfgCtxConfig* c)
{
    short rect[4];
    CfgDlgConfig cfg;
    CfgBoxConfig b;
    cfg = dword_800C2CD0;
    cfg.f4 = sub_8002C64C();
    cfg.fC = c->f44;
    cfg.f10 = (int)dword_800C4DDC;
    sub_8002A5A4(&cfg);
    rect[0] = 0x7D;
    rect[1] = 0x12;
    rect[2] = 0x46;
    rect[3] = 0x12;
    b.c_B = 1;
    b.x_0 = 0x84;
    b.col_8 = uiColor_8008B590;
    b.c_A = 0;
    b.y_2 = 0x15;
    sub_8002C06C(&b, 0x4F, 0xE);
    sub_80042460(rect, &b.col_8, dword_8008D454 + 0x38, 0);
}

// Matched
void sub_800C39C4(CfgCtxConfig* c)
{
    short rect[4];
    CfgDlgConfig a;
    CfgDlgConfig b;
    CfgDlgConfig d;
    CfgDlgConfig e;
    CfgBoxConfig box;
    a = dword_800C2CD0;
    b = dword_800C2CE8;
    d = dword_800C2CE8;
    e = dword_800C2CE8;
    a.f4 = sub_8002C64C();
    a.fC = c->f44;
    a.f10 = (int)dword_800C4E98;
    b.f4 = sub_8002C64C();
    b.fC = dword_8008B570.f_1C / 16;
    b.f10 = (int)dword_800C5298;
    d.f4 = sub_8002C64C();
    d.fC = dword_8008B570.g_1C / 16;
    d.f10 = (int)dword_800C52BC;
    e.f4 = sub_8002C64C();
    e.fC = c->fc;
    e.f10 = (int)dword_800C52E0;
    sub_800309D8(&stru_80091CE0);
    if (c->f38)
    {
        a.f0 = 4;
    }
    else
    {
        a.f0 = 2;
    }
    sub_8002A5A4(&a);
    if (c->f38)
    {
        b.f0 = 4;
        d.f0 = 4;
        e.f0 = 4;
        switch (c->f44)
        {
        case 0:
            b.f0 = 2;
            break;
        case 1:
            d.f0 = 2;
            break;
        case 2:
            e.f0 = 2;
            break;
        }
    }
    else
    {
        b.f0 = 4;
        d.f0 = 4;
        e.f0 = 4;
    }
    sub_8002A5A4(&b);
    sub_8002A5A4(&d);
    sub_8002A5A4(&e);
    rect[0] = 0x72;
    rect[1] = 0x12;
    rect[2] = 0x5C;
    rect[3] = 0x12;
    box.c_B = 1;
    box.x_0 = 0x93;
    box.y_2 = 0x15;
    box.col_8 = uiColor_8008B590;
    box.c_A = 0;
    box.x_0 = 0x8B;
    sub_8002C06C(&box, 0xDD, 0xE);
    sub_80042460(rect, &box.col_8, dword_8008D454 + 0x38, 0);
}

INCLUDE_OVERLAY_ASM(config, sub_800C3CA4);

INCLUDE_OVERLAY_ASM(config, sub_800C4180);

INCLUDE_OVERLAY_ASM(config, sub_800C4390);

// Matched
void sub_800C450C(CfgCtxConfig* c)
{
    int p;
    short rect[4];
    short pos[2];
    short s = c->prev_2;
    if (s >= 0)
    {
        if (s < 3)
        {
            p = dword_800C4CC0[s][c->f44];
        }
        else if (s < 5)
        {
            p = *dword_800C4CC0[s];
        }
        else
        {
            p = 0;
        }
    }
    else
    {
        p = 0;
    }
    rect[0] = 10;
    rect[1] = 0xC2;
    rect[2] = 0x12C;
    rect[3] = 0x12;
    pos[0] = 0xE;
    pos[1] = 0xC5;
    sub_8002AE38(&p, pos, 0xE, rect, 1);
}

// Matched
int sub_800C45D8(void)
{
    return dword_800C5944;
}

INCLUDE_OVERLAY_ASM(config, sub_800C45E8);

// Matched
void sub_800C4B34(CfgTaskConfig* t, CfgCtxConfig* c)
{
    sub_8002BE10();
    sub_800C383C(c);
    sub_800C4BDC((short)c->f30);
    if (c->f34 >= 0x96 || sub_8003D380(0) || sub_8003D41C(0))
    {
        PlaySfx_80031494(0x7D);
        t->next_8 = sub_800C2F70;
        c->f30 = 0;
        c->f34 = 0;
    }
    else
    {
        c->f34++;
    }
}

// Matched
void sub_800C4BDC(int n)
{
    short rect[4];
    short pos[2];
    char* p[2];
    if ((short)n == 2)
    {
        p[0] = dword_800C2D40;
        p[1] = dword_800C2DA4;
    }
    else
    {
        p[0] = dword_800C2DF4;
        p[1] = dword_800C2E5C;
    }
    rect[0] = 10;
    rect[1] = 0xC2;
    rect[2] = 0x12C;
    rect[3] = 0x22;
    pos[0] = 0xD;
    pos[1] = 0xC4;
    sub_8002AE38(p, pos, 0xE, rect, 2);
}

INCLUDE_OVERLAY_ASM(config, dword_800C4C80);
