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
    unsigned int k_1C : 1;
    unsigned int l_1C : 7;
    unsigned char b_20;
} CfgSettingsConfig;

typedef struct CfgCtxConfig
{
    char pad_0[2];
    short prev_2;
    short cur_4;
    unsigned short f6;
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
typedef struct CfgSpinConfig
{
    int f0;
    short f4, f6, f8, fA;
} CfgSpinConfig;

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
extern char dword_800C58A8[];
extern char dword_800C5920[];
typedef struct CfgTailConfig
{
    short col_0;
    char c_2;
    char c_3;
} CfgTailConfig;
extern int frameCount_8008D3FC;
extern void sub_8002BE10();
extern void sub_8002B004(void*, int, int);
extern void sub_8003D794(void*, int);
extern void sub_800C2F70();
extern void sub_800C3060(CfgCtxConfig*);
extern void sub_800C383C(CfgCtxConfig*);
extern void sub_800C450C(CfgCtxConfig*);
extern void sub_800C3540(CfgCtxConfig*);
extern void sub_800C378C(CfgCtxConfig*);
extern void sub_800C38CC(CfgCtxConfig*);
extern void sub_800C39C4(CfgCtxConfig*);
extern void sub_800C3CA4(CfgCtxConfig*);
extern void sub_800C4180(CfgCtxConfig*);
extern void sub_800C4390(CfgCtxConfig*);
extern void sub_800C45E8();
extern void sub_800C4B34(CfgTaskConfig*, CfgCtxConfig*);

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

void sub_800C31DC(CfgCtxConfig* c)
{
    switch (c->prev_2)
    {
    case 1:
        if (dword_800C5944 != 0)
        {
            switch (c->f44)
            {
            case 0:
                c->f15 = dword_8008B570.f_1C / 16;
                break;
            case 1:
                c->f16 = dword_8008B570.g_1C / 16;
                break;
            case 2:
                dword_8008B570.e_1C = c->fc;
                break;
            }
        }
        break;
    case 2:
        if (dword_800C5944 != 0)
        {
            switch (c->f44)
            {
            case 0:
                {
                CfgSettingsConfig* s = &dword_8008B570;
                s->a_1C = c->f8;
                }
                break;
            case 1:
                {
                CfgSettingsConfig* s = &dword_8008B570;
                unsigned char t = c->f9;
                s->b_1C = t;
                s->c_1C = t;
                s->c_1C = c->fa;
                }
                break;
            case 2:
                {
                CfgSettingsConfig* s = &dword_8008B570;
                s->i_1C = c->f11;
                if (s->i_1C == 0)
                {
                    c->f13 = 0;
                    s->j_1C = 0;
                }
                }
                break;
            case 3:
                {
                CfgSettingsConfig* s = &dword_8008B570;
                s->j_1C = c->f13;
                }
                break;
            case 4:
                {
                CfgSettingsConfig* s = &dword_8008B570;
                s->k_1C = c->f14;
                if (s->k_1C == 0)
                {
                    c->f11 = 1;
                    s->i_1C = 1;
                    c->f13 = 1;
                    s->j_1C = 1;
                }
                }
                break;
            case 5:
                {
                CfgSettingsConfig* s = &dword_8008B570;
                s->d_1C = c->fb;
                }
                break;
            case 6:
                {
                CfgSettingsConfig* s = &dword_8008B570;
                s->h_1C = c->f10;
                }
                break;
            }
        }
        break;
    case 3:
        if (dword_800C5944 != 0)
        {
            uiColor_8008B590 = c->ff;
        }
        break;
    case 4:
        if (dword_800C5944 != 0)
        {
            if (c->f12 == 0)
            {
                dword_8008B570.w0 |= 0x40;
            }
            else
            {
                dword_8008B570.w0 &= ~0x40;
            }
        }
        break;
    }
}
INCLUDE_OVERLAY_ASM(config, dword_800C2C88);

void sub_800C3540(CfgCtxConfig* c)
{
    switch (c->prev_2)
    {
    case 0:
        if (dword_800C5944 != 0)
        {
            if (sub_8003D380(1))
            {
                c->cur_4 = c->f44 + 1;
                c->f6 = c->f44;
            }
            else if (sub_8003D41C(1))
            {
                c->cur_4 = 5;
            }
        }
        break;
    case 1:
        if (dword_800C5944 != 0)
        {
            if (sub_8003D380(1))
            {
                dword_8008B4B8->t_10.next_8 = sub_800C45E8;
                c->f38 = 1;
            }
            else if (sub_8003D41C(1))
            {
                sub_800C3060(c);
                c->cur_4 = 0;
                c->f44 = c->f6;
            }
        }
        break;
    case 2:
        if (dword_800C5944 != 0)
        {
            if (sub_8003D380(0))
            {
                if (c->f14 == 0 && (unsigned short)(c->f44 - 2) < 2)
                {
                    dword_8008B4B8->t_10.next_8 = sub_800C4B34;
                    c->f30 = 1;
                    PlaySfx_80031494(0x7C);
                }
                else if (c->f11 == 0 && c->f44 == 3)
                {
                    dword_8008B4B8->t_10.next_8 = sub_800C4B34;
                    c->f30 = 2;
                    PlaySfx_80031494(0x7C);
                }
                else
                {
                    dword_8008B4B8->t_10.next_8 = sub_800C45E8;
                    c->f38 = 1;
                    PlaySfx_80031494(0x7E);
                }
            }
            else if (sub_8003D41C(1))
            {
                sub_800C3060(c);
                c->cur_4 = 0;
                c->f44 = c->f6;
            }
        }
        break;
    case 3:
        if (dword_800C5944 != 0)
        {
            c->ff = c->f44;
            if (sub_8003D380(1))
            {
                sub_800C31DC(c);
            }
            else if (sub_8003D41C(1))
            {
                sub_800C3060(c);
                c->cur_4 = 0;
                c->f44 = c->f6;
            }
        }
        break;
    case 4:
        if (dword_800C5944 != 0)
        {
            if (sub_8003D380(1))
            {
                dword_8008B4B8->t_10.next_8 = sub_800C45E8;
                c->f38 = 1;
            }
            else if (sub_8003D41C(1))
            {
                sub_800C3060(c);
                c->cur_4 = 0;
                c->f44 = c->f6;
            }
        }
        break;
    }
}
INCLUDE_OVERLAY_ASM(config, dword_800C2CA0);

void sub_800C378C(CfgCtxConfig* c)
{
    c->f3c = dword_800C4CD4[c->cur_4];
    switch (c->cur_4)
    {
    case 3:
        if (c->prev_2 == 0)
        {
            c->f44 = uiColor_8008B590;
            c->f46 = 0;
        }
        break;
    case 1:
    case 2:
    case 4:
        if (c->prev_2 == 0)
        {
            c->f44 = 0;
    case 0:
            c->f46 = 0;
        }
        break;
    }
    c->prev_2 = c->cur_4;
    c->cur_4 = -1;
}
INCLUDE_OVERLAY_ASM(config, dword_800C2CB8);

void sub_800C383C(CfgCtxConfig* c)
{
    switch (c->prev_2)
    {
    case 0:
        sub_800C38CC(c);
        break;
    case 1:
        sub_800C39C4(c);
        break;
    case 2:
        sub_800C3CA4(c);
        break;
    case 3:
        sub_800C4180(c);
        break;
    case 4:
        sub_800C4390(c);
        break;
    }
}
INCLUDE_OVERLAY_ASM(config, dword_800C2CD0);

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

extern unsigned short* dword_800C5474[];
extern char dword_800C5574[];
extern char dword_800C55F8[];
extern char dword_800C5674[];
extern char dword_800C56F0[];
extern char dword_800C576C[];
extern char dword_800C57E8[];
extern char dword_800C5864[];

void sub_800C3CA4(CfgCtxConfig* c)
{
    short rect[4];
    CfgDlgConfig a;
    CfgDlgConfig b1;
    CfgDlgConfig b2;
    CfgDlgConfig b3;
    CfgDlgConfig b4;
    CfgDlgConfig b5;
    CfgDlgConfig b6;
    CfgDlgConfig b7;
    CfgBoxConfig box;
    unsigned short** t;
    a = dword_800C2CD0;
    b1 = dword_800C2CE8;
    b2 = dword_800C2CE8;
    b3 = dword_800C2CE8;
    b4 = dword_800C2CE8;
    b5 = dword_800C2CE8;
    b6 = dword_800C2CE8;
    b7 = dword_800C2CE8;
    a.f4 = sub_8002C64C();
    a.fC = c->f44;
    t = dword_800C5474;
    a.f10 = (int)t;
    b1.f4 = sub_8002C64C();
    b1.fC = c->f8;
    b1.f10 = (int)dword_800C5574;
    b2.f4 = sub_8002C64C();
    b2.fC = (*(unsigned int*)&c->f8 & 0xFFFF00) != 0;
    b2.f10 = (int)dword_800C55F8;
    b3.f4 = sub_8002C64C();
    b3.fC = c->f11;
    b3.f10 = (int)dword_800C5674;
    b4.f4 = sub_8002C64C();
    b4.fC = c->fb;
    b4.f10 = (int)dword_800C56F0;
    b5.f4 = sub_8002C64C();
    b5.fC = c->f10;
    b5.f10 = (int)dword_800C576C;
    b6.f4 = sub_8002C64C();
    b6.fC = c->f13;
    b6.f10 = (int)dword_800C57E8;
    b7.f4 = sub_8002C64C();
    b7.fC = c->f14;
    b7.f10 = (int)dword_800C5864;
    if (c->f38)
    {
        a.f0 = 4;
    }
    else
    {
        a.f0 = 2;
        if (c->f14 == 0)
        {
            *t[2] |= 2;
        }
        else
        {
            *t[2] &= ~2;
            *t[3] &= ~2;
            if (c->f11 != 0)
            {
                goto done;
            }
        }
        *t[3] |= 2;
    }
done:
    sub_8002A5A4(&a);
    if (c->f38)
    {
        b1.f0 = 4;
        b2.f0 = 4;
        b3.f0 = 4;
        b4.f0 = 4;
        b5.f0 = 4;
        b6.f0 = 4;
        b7.f0 = 4;
        switch (c->f44)
        {
        case 0:
            b1.f0 = 2;
            break;
        case 1:
            b2.f0 = 2;
            break;
        case 2:
            b3.f0 = 2;
            break;
        case 3:
            b6.f0 = 2;
            break;
        case 4:
            b7.f0 = 2;
            break;
        case 5:
            b4.f0 = 2;
            break;
        case 6:
            b5.f0 = 2;
            break;
        }
    }
    else
    {
        b1.f0 = 4;
        b2.f0 = 4;
        b3.f0 = 4;
        b4.f0 = 4;
        b5.f0 = 4;
        b6.f0 = 4;
        b7.f0 = 4;
    }
    sub_8002A5A4(&b1);
    sub_8002A5A4(&b2);
    sub_8002A5A4(&b3);
    sub_8002A5A4(&b6);
    sub_8002A5A4(&b7);
    sub_8002A5A4(&b4);
    sub_8002A5A4(&b5);
    rect[0] = 0x72;
    rect[1] = 0x12;
    rect[2] = 0x5C;
    rect[3] = 0x12;
    box.c_B = 1;
    box.x_0 = 0x78;
    box.col_8 = uiColor_8008B590;
    box.c_A = 0;
    box.y_2 = 0x15;
    sub_8002C06C(&box, 0xE8, 0xE);
    sub_80042460(rect, &box.col_8, dword_8008D454 + 0x38, 0);
}
INCLUDE_OVERLAY_ASM(config, dword_800C2D20);

#if 0
// Not matched: the original does not keep i*38 in a register across the loop body (uses fewer saved registers)
void sub_800C4180(CfgCtxConfig* c)
{
    short rect[4];
    CfgBoxConfig box1;
    short rect2[4];
    short rect3[4];
    CfgTailConfig tail;
    CfgBoxConfig box3;
    short i;
    rect[0] = 0x72;
    rect[1] = 0x12;
    rect[2] = 0x5C;
    rect[3] = 0x12;
    box1.c_B = 1;
    box1.x_0 = 0x8C;
    box1.col_8 = uiColor_8008B590;
    box1.c_A = 0;
    box1.y_2 = 0x14;
    sub_8002C06C(&box1, 0x2A, 0xE);
    box1.x_0 = 0x8C;
    box1.y_2 = 0x15;
    sub_80042460(rect, &box1.col_8, dword_8008D454 + 0x38, 0);
    for (i = 0; i < 4; i++)
    {
        unsigned int n = 0;
        rect2[0] = 0x52;
        rect2[1] = i * 38 + 0x2A;
        rect2[2] = 0x12;
        rect2[3] = 0x24;
        tail.c_2 = 1;
        if (c->ff == i)
        {
            n = (unsigned int)(frameCount_8008D3FC * stru_8008B4D8.field_4) >> 1;
        }
        tail.col_0 = i;
        tail.c_3 = 1;
        sub_80042460(rect2, &tail, dword_8008D454 + 0x38, n);
        rect3[0] = 0x66;
        rect3[1] = i * 38 + 0x2A;
        rect3[2] = 0x76;
        rect3[3] = 0x24;
        box3.col_8 = i;
        box3.c_A = 0;
        box3.c_B = 1;
        box3.x_0 = 0x74;
        box3.y_2 = i * 38 + 0x2C;
        sub_8002C06C(&box3, 0xCA, 0xE);
        box3.x_0 = rect3[0] + 0xE;
        box3.y_2 = rect3[1] + 6;
        sub_80042460(rect3, &box3.col_8, dword_8008D454 + 0x38, 0);
    }
}
#endif
INCLUDE_OVERLAY_ASM(config, sub_800C4180);

// Matched
void sub_800C4390(CfgCtxConfig* c)
{
    short rect[4];
    CfgDlgConfig a;
    CfgDlgConfig b;
    CfgBoxConfig box;
    a = dword_800C2CE8;
    b = dword_800C2CE8;
    a.f4 = sub_8002C64C();
    a.fC = 0;
    a.f10 = (int)dword_800C58A8;
    b.f4 = sub_8002C64C();
    b.fC = c->f12;
    b.f10 = (int)dword_800C5920;
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
        b.f0 = 2;
    }
    else
    {
        b.f0 = 4;
    }
    sub_8002A5A4(&b);
    rect[0] = 0x72;
    rect[1] = 0x12;
    rect[2] = 0x5C;
    rect[3] = 0x12;
    box.c_B = 1;
    box.x_0 = 0x85;
    box.col_8 = uiColor_8008B590;
    box.c_A = 0;
    box.y_2 = 0x15;
    sub_8002C06C(&box, 0xAB, 0xE);
    box.x_0 = 0x8C;
    box.y_2 = 0x15;
    sub_80042460(rect, &box.col_8, dword_8008D454 + 0x38, 0);
}

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

extern void sub_8003D630(CfgSpinConfig* p);
extern void sub_800C2F70();

void sub_800C45E8(CfgTaskConfig* t, CfgCtxConfig* c)
{
    CfgSpinConfig v10;
    CfgSpinConfig v20;
    CfgSpinConfig v30;
    CfgSpinConfig v40;
    CfgSpinConfig v50;
    CfgSpinConfig v60;
    CfgSpinConfig v70;
    CfgSpinConfig v80;
    int v;
    sub_8002BE10();
    sub_800C383C(c);
    sub_800C450C(c);
    sub_8002B004(dword_800C592C, 0, 0xE);
    if (c->prev_2 == 1)
    {
        switch (c->f44)
        {
        case 0:
            v = dword_8008B570.f_1C / 16;
            v10.f0 = 0;
            v10.f4 = 0;
            v10.f8 = 8;
            v10.fA = 1;
            v10.f6 = v;
            sub_8003D630(&v10);
            if (v != v10.f6)
            {
                PlaySfx_80031494(0x7F);
            }
            v = v10.f6;
            dword_8008B570.f_1C = v * 16;
            break;
        case 1:
            v = dword_8008B570.g_1C / 16;
            v20.f0 = 0;
            v20.f4 = 0;
            v20.f8 = 8;
            v20.fA = 1;
            v20.f6 = v;
            sub_8003D630(&v20);
            if (v != v20.f6)
            {
                PlaySfx_80031494(0x7F);
            }
            v = v20.f6;
            dword_8008B570.g_1C = v * 16;
            break;
        case 2:
            v30.f0 = 0;
            v30.f4 = 0;
            v30.f8 = 2;
            v30.fA = 1;
            v30.f6 = c->fc;
            sub_8003D630(&v30);
            if (c->fc != v30.f6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->fc = v30.f6;
            break;
        }
    }
    else if (c->prev_2 == 2)
    {
        switch (c->f44)
        {
        case 0:
            {
            v10.f0 = 0;
            v10.f4 = 0;
            v10.f8 = 4;
            v10.fA = 1;
            v10.f6 = c->f8;
            sub_8003D630(&v10);
            if (c->f8 != v10.f6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->f8 = v10.f6;
            }
            break;
        case 1:
            {
            v20.f0 = 0;
            v20.f4 = 0;
            v20.f8 = 2;
            v20.fA = 1;
            v20.f6 = c->f9;
            sub_8003D630(&v20);
            if (c->f9 != v20.f6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->fa = c->f9 = v20.f6;
            }
            break;
        case 2:
            {
            v40.f0 = 0;
            v40.f4 = 0;
            v40.f8 = 2;
            v40.fA = 1;
            v40.f6 = c->f11;
            sub_8003D630(&v40);
            if (c->f11 != v40.f6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->f11 = v40.f6;
            }
            break;
        case 3:
            {
            v50.f0 = 0;
            v50.f4 = 0;
            v50.f8 = 2;
            v50.fA = 1;
            v50.f6 = c->f13;
            sub_8003D630(&v50);
            if (c->f13 != v50.f6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->f13 = v50.f6;
            }
            break;
        case 4:
            {
            v60.f0 = 0;
            v60.f4 = 0;
            v60.f8 = 2;
            v60.fA = 1;
            v60.f6 = c->f14;
            sub_8003D630(&v60);
            if (c->f14 != v60.f6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->f14 = v60.f6;
            }
            break;
        case 5:
            {
            v70.f0 = 0;
            v70.f4 = 0;
            v70.f8 = 2;
            v70.fA = 1;
            v70.f6 = c->fb;
            sub_8003D630(&v70);
            if (c->fb != v70.f6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->fb = v70.f6;
            }
            break;
        case 6:
            {
            v80.f0 = 0;
            v80.f4 = 0;
            v80.f8 = 2;
            v80.fA = 1;
            v80.f6 = c->f10;
            sub_8003D630(&v80);
            if (c->f10 != v80.f6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->f10 = v80.f6;
            }
            break;
        }
    }
    else if (c->prev_2 == 4)
    {
        v10.f0 = 0;
        v10.f4 = 0;
        v10.f8 = 2;
        v10.fA = 1;
        v10.f6 = c->f12;
        sub_8003D630(&v10);
        if (c->f12 != v10.f6)
        {
            PlaySfx_80031494(0x7F);
        }
        c->f12 = v10.f6;
    }
    if (sub_8003D380(1))
    {
        sub_800C31DC(c);
        t->next_8 = sub_800C2F70;
        c->f38 = 0;
    }
    else if (sub_8003D41C(1))
    {
        dword_8008B570.f_1C = c->f15 * 16;
        dword_8008B570.g_1C = c->f16 * 16;
        sub_800C3060(c);
        t->next_8 = sub_800C2F70;
        c->f38 = 0;
    }
}
INCLUDE_OVERLAY_ASM(config, dword_800C2D40);

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
