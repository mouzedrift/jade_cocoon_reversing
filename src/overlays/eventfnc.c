// EVENTFNC.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct EvInsEventfnc
{
    int op_0;
    int a_4;
    int b_8;
    int c_C;
} EvInsEventfnc;

typedef struct EvEntEventfnc
{
    char pad_0[0x7C];
    int f7C_7C;
    int f80_80;
    int f84_84;
    int pad_88;
    int f8C_8C;
} EvEntEventfnc;

typedef struct EvVecEventfnc
{
    int x_0;
    int y_4;
    int z_8;
} EvVecEventfnc;

typedef struct EvCtxEventfnc
{
    unsigned int flags_0;
    EvInsEventfnc* start_4;
    EvInsEventfnc* pc_8;
    EvInsEventfnc* ret_C;
    int f10_10;
    int f14_14;
    int f18_18;
    char pad_1C[0x24 - 0x1C];
    int f24_24[6];
    EvVecEventfnc vec3C_3C[5];
    EvVecEventfnc vec78_78[5];
    int padB4_B4;
    int fB8_B8;
    char pad_BC[8];
    unsigned int fC4_C4;
    int fC8_C8;
    int fCC_CC[8];
    int fEC_EC;
    int fF0_F0;
    int fF4_F4;
    int fF8_F8;
    int fFC_FC;
    unsigned short f100_100;
    unsigned short f102_102;
    int f104_104;
    int f108_108;
    char pad_10C[4];
    int* f110_110;
    int f114_114;
    char pad_118[4];
    int f11C_11C;
    EvEntEventfnc* ent_120;
} EvCtxEventfnc;

typedef struct EvMsgEventfnc
{
    int m0_0;
    int m4_4;
    int m8_8;
    int mC_C;
    int m10_10;
    int m14_14;
    int m18_18;
    int m1C_1C;
    int m20_20;
    int m24_24;
} EvMsgEventfnc;

typedef struct EvObjEventfnc
{
    char pad_0[0x1A];
    short f1A_1A;
    char pad_1C[0x90 - 0x1C];
    int f90_90;
} EvObjEventfnc;

extern EvVecEventfnc* sub_800BBC00(EvCtxEventfnc* c, int a, int b);
extern EvVecEventfnc* sub_800BBC80(EvCtxEventfnc* c, int a, int b);
extern EvVecEventfnc* sub_800BBBA0(int a);
extern int sub_800BB840(EvCtxEventfnc* c, EvMsgEventfnc* m, int a, int b);
extern int sub_800BB990(EvCtxEventfnc* c, EvMsgEventfnc* m, int a, int b);
extern void sub_800BBDA0(int a, int b);
extern int sub_800BBDD8(int a);

INCLUDE_OVERLAY_ASM(eventfnc, dword_800B6D00);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B6DD4);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B716C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B73C0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B76B8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B79E0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B7E40);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8028);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B80C8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8184);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8220);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B82C8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B83E4);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B844C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8568);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B88A4);

void sub_800B8928()
{
    int i;
    for (i = 0x2a; i >= 0; i--)
    {
    }
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8940);

int sub_800B89A8(EvCtxEventfnc* c)
{
    c->pc_8++;
    return 1;
}

extern unsigned short word_8009194C;
int sub_800B89C0(EvCtxEventfnc* c)
{
    if (word_8009194C & 0x100)
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

extern int sub_800B8A34(EvCtxEventfnc* c);
int sub_800B89F4(EvCtxEventfnc* c)
{
    if (sub_800B8A34(c))
    {
        c->flags_0 |= 1;
    }
    return 0;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8A34);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8BE8);

int sub_800B8CB0(EvCtxEventfnc* c)
{
    EvInsEventfnc* p = c->pc_8;
    if (p->b_8 != 0)
    {
        c->ret_C = p;
        c->pc_8 = p + 1;
        c->flags_0 |= 0x10;
    }
    else
    {
        c->flags_0 &= ~0x10;
        c->pc_8++;
    }
    return 1;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8D08);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8DDC);

int sub_800B8E9C(EvCtxEventfnc* c)
{
    int target = c->pc_8[c->fEC_EC].b_8;
    EvInsEventfnc* p = c->start_4;
    while (p->op_0 != 3)
    {
        if (p->op_0 == 9 && target == p->b_8)
        {
            c->pc_8 = p;
            c->fEC_EC = 0;
            return 1;
        }
        p++;
    }
    return 0;
}

#if 0
int sub_800B8F14(EvCtxEventfnc* c)
{
    EvInsEventfnc* p = (EvInsEventfnc*)c->pc_8[c->fEC_EC].c_C;
    c->fEC_EC = 0;
    c->pc_8 = p;
    c->ret_C = c->start_4 = p;
    return 1;
}
#endif
INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8F14);

int sub_800B8F44(EvCtxEventfnc* c)
{
    c->fC4_C4++;
    if (c->fC4_C4 >= c->pc_8->b_8 + 1)
    {
        c->fC4_C4 = 0;
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800B8F88(EvCtxEventfnc* c)
{
    if (c->f18_18 & c->pc_8->b_8)
    {
        return 0;
    }
    c->pc_8++;
    return 1;
}

extern int sub_800AD16C(int a, int b);
int sub_800B8FB8(EvCtxEventfnc* c)
{
    unsigned int v = c->pc_8->b_8;
    int hi = v >> 16;
    int lo = v & 0xFFFF;
    if (c->pc_8->a_4 == 0)
    {
        c->fCC_CC[hi] = lo;
    }
    else
    {
        sub_800AD16C(hi, lo);
    }
    c->pc_8++;
    return 1;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9020);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9110);

extern void (*dword_800B1D98)(int);
int sub_800B91CC(EvCtxEventfnc* c)
{
    dword_800B1D98(c->pc_8->c_C);
    c->pc_8++;
    return 1;
}

extern int sub_800A59D0(int a);
int sub_800B9218(EvCtxEventfnc* c)
{
    sub_800A59D0(c->pc_8->c_C);
    c->pc_8++;
    return 1;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9260);

int sub_800B93A8(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    EvVecEventfnc* v = (EvVecEventfnc*)c->pc_8->c_C;
    m.m0_0 = c->pc_8->a_4;
    m.m4_4 = c->pc_8->op_0 != 0x14;
    m.m18_18 = v->x_0;
    m.m1C_1C = v->y_4;
    m.m20_20 = v->z_8;
    m.m14_14 = c->pc_8->b_8;
    return sub_800BB840(c, &m, 1, 1);
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B942C);

int sub_800B95BC(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    EvInsEventfnc* i = c->pc_8;
    EvVecEventfnc* v = (EvVecEventfnc*)i->c_C;
    int a = i->a_4;
    m.m0_0 = a;
    m.m4_4 = 2;
    m.m18_18 = v->x_0;
    m.m1C_1C = v->y_4;
    m.m20_20 = v->z_8;
    m.m14_14 = c->pc_8->b_8;
    return sub_800BB840(c, &m, 1, 1);
}

int sub_800B962C(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    EvVecEventfnc* v;
    int a = c->pc_8->a_4;
    int b = c->pc_8->b_8;
    v = (a == b) ? sub_800BBC80(c, b, 0) : sub_800BBBA0(b);
    m.m0_0 = c->pc_8->a_4;
    m.m4_4 = 2;
    m.m18_18 = v->x_0;
    m.m1C_1C = v->y_4;
    m.m20_20 = v->z_8;
    m.m14_14 = c->pc_8->c_C;
    return sub_800BB840(c, &m, 1, 1);
}

int sub_800B96D8(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = c->pc_8->a_4;
    m.m4_4 = 6;
    m.mC_C = c->pc_8->b_8;
    return sub_800BB990(c, &m, 0, 1);
}

int sub_800B9720(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = c->pc_8->a_4;
    m.m4_4 = 7;
    m.mC_C = c->pc_8->b_8;
    return sub_800BB990(c, &m, 0, 1);
}

int sub_800B9768(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = c->pc_8->a_4;
    m.m4_4 = 8;
    m.mC_C = c->pc_8->b_8;
    return sub_800BB990(c, &m, 0, 1);
}

int sub_800B97B0(EvCtxEventfnc* c)
{
    sub_800BBC00(c, c->pc_8->a_4, 1);
    c->pc_8++;
    return 1;
}

int sub_800B97F8(EvCtxEventfnc* c)
{
    sub_800BBC80(c, c->pc_8->a_4, 1);
    c->pc_8++;
    return 1;
}

extern int sub_800AD0D4(int a);
int sub_800B9840(EvCtxEventfnc* c)
{
    if (c->pc_8->a_4 == 0)
    {
        if (sub_800AD0D4(c->pc_8->b_8))
        {
            c->pc_8++;
            return 1;
        }
        return 0;
    }
    c->fEC_EC = sub_800AD0D4(c->pc_8->b_8) == 0;
    c->pc_8++;
    return 1;
}

extern void sub_800AD0F8(int a);
int sub_800B98C4(EvCtxEventfnc* c)
{
    sub_800AD0F8(c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

extern void sub_800AD124(int a);
int sub_800B990C(EvCtxEventfnc* c)
{
    sub_800AD124(c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

int sub_800B9954(EvCtxEventfnc* c)
{
    if (c->pc_8->a_4 == 0)
    {
        if (sub_800BBDD8(c->pc_8->b_8))
        {
            c->pc_8++;
            return 1;
        }
        return 0;
    }
    c->fEC_EC = sub_800BBDD8(c->pc_8->b_8) == 0;
    c->pc_8++;
    return 1;
}

int sub_800B99D8(EvCtxEventfnc* c)
{
    sub_800BBDA0(c->pc_8->b_8, 1);
    c->pc_8++;
    return 1;
}

int sub_800B9A20(EvCtxEventfnc* c)
{
    sub_800BBDA0(c->pc_8->b_8, 0);
    c->pc_8++;
    return 1;
}

extern int sub_800AD184(int a, int b, int c);
extern int sub_800AD1E0(int a, int b, int c);
int sub_800B9A68(EvCtxEventfnc* c)
{
    sub_800AD184(c->pc_8->a_4, c->pc_8->b_8, 0);
    c->pc_8++;
    return 1;
}

int sub_800B9AB4(EvCtxEventfnc* c)
{
    sub_800AD1E0(c->pc_8->a_4, c->pc_8->b_8, 0);
    c->pc_8++;
    return 1;
}

int sub_800B9B00(EvCtxEventfnc* c)
{
    sub_800AD184(c->pc_8->a_4, c->pc_8->b_8, 1);
    c->pc_8++;
    return 1;
}

int sub_800B9B4C(EvCtxEventfnc* c)
{
    sub_800AD1E0(c->pc_8->a_4, c->pc_8->b_8, 1);
    c->pc_8++;
    return 1;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9B98);

extern int sub_800AD68C(int a);
extern int sub_800AD6E4(int a);
int sub_800B9C5C(EvCtxEventfnc* c)
{
    int a = c->pc_8->a_4;
    int b = c->pc_8->b_8;
    if (a != 0)
    {
        sub_800AD68C(b);
    }
    else
    {
        sub_800AD6E4(b);
    }
    c->pc_8++;
    return 1;
}

extern int sub_800AD058(int a);
int sub_800B9CC0(EvCtxEventfnc* c)
{
    sub_800AD058(c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

extern int sub_800AD8F4(int a);
int sub_800B9D08(EvCtxEventfnc* c)
{
    sub_800AD8F4(c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9D50);

extern EvEntEventfnc* sub_800A5DDC(int a, int b, int c);
int sub_800B9DE0(EvCtxEventfnc* c)
{
    EvEntEventfnc* e = sub_800A5DDC(c->pc_8->c_C, c->pc_8->a_4, 0);
    if (e == 0)
    {
        return 0;
    }
    e->f7C_7C = c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

int sub_800B9E48(EvCtxEventfnc* c)
{
    EvEntEventfnc* e = sub_800A5DDC(c->pc_8->c_C, c->pc_8->a_4, 0);
    if (e != 0 && e->f80_80 == c->pc_8->b_8)
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800B9EB0(EvCtxEventfnc* c)
{
    c->ent_120->f7C_7C = c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

int sub_800B9EDC(EvCtxEventfnc* c)
{
    if (c->ent_120->f80_80 == c->pc_8->b_8)
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800B9F0C(EvCtxEventfnc* c)
{
    if (sub_800A5DDC(c->pc_8->c_C, c->pc_8->b_8, 0) == 0)
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800B9F5C(EvCtxEventfnc* c)
{
    c->f108_108 |= c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

int sub_800B9F84(EvCtxEventfnc* c)
{
    c->f100_100 = c->pc_8->a_4;
    c->f102_102 = c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

int sub_800B9FB4(EvCtxEventfnc* c)
{
    c->f104_104 = c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

extern void sub_800A6830(int a);
int sub_800B9FD8(EvCtxEventfnc* c)
{
    sub_800A6830(c->pc_8->c_C);
    c->pc_8++;
    return 1;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA020);

int sub_800BA1DC(EvCtxEventfnc* c)
{
    int* p = c->f110_110;
    if (p != 0)
    {
        EvInsEventfnc* i = c->pc_8;
        unsigned int a = i->a_4;
        unsigned int b = i->b_8;
        if (b >= a)
        {
            p[3] = i->c_C;
        }
        else
        {
            i->b_8 = b + 1;
        }
    }
    c->pc_8++;
    return 1;
}

extern int sub_80034ADC(int a, int b);
int sub_800BA238(EvCtxEventfnc* c)
{
    if (sub_80034ADC(c->f11C_11C, c->pc_8->b_8))
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800BA28C(EvCtxEventfnc* c)
{
    EvInsEventfnc* i = c->pc_8;
    if (i->a_4 == 1)
    {
        c->f114_114 |= i->b_8;
    }
    else
    {
        c->f114_114 &= ~i->b_8;
    }
    c->pc_8++;
    return 1;
}

int sub_800BA2E8(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = 1 << c->pc_8->a_4;
    m.m4_4 = 3;
    m.mC_C = c->pc_8->b_8;
    return sub_800BB990(c, &m, 1, 1);
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA338);

int sub_800BA40C(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = 1 << c->pc_8->a_4;
    m.m4_4 = 5;
    m.m24_24 = c->pc_8->c_C;
    return sub_800BB990(c, &m, 1, 1);
}

extern EvObjEventfnc* sub_800A7A60(int a);
int sub_800BA45C(EvCtxEventfnc* c)
{
    int ok = 0;
    int a = c->pc_8->a_4;
    if (a != 0)
    {
        EvObjEventfnc* o = sub_800A7A60(a - 1);
        if (o->f90_90 == o->f1A_1A)
        {
            sub_8001D6EC((struct_obj_A*)o, c->pc_8->b_8);
            ok = 1;
        }
    }
    if (ok)
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800BA4F0(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = 1 << c->pc_8->a_4;
    m.m4_4 = 9;
    m.mC_C = c->pc_8->b_8;
    m.m14_14 = c->pc_8->c_C;
    return sub_800BB990(c, &m, 1, 1);
}

int sub_800BA554(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = 1 << c->pc_8->a_4;
    m.m4_4 = 0xA;
    m.mC_C = ((unsigned short*)&c->pc_8->b_8)[1];
    m.m10_10 = ((unsigned short*)&c->pc_8->b_8)[0];
    m.m14_14 = c->pc_8->c_C;
    return sub_800BB990(c, &m, 1, 1);
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA5CC);

int sub_800BA678(EvCtxEventfnc* c)
{
    c->fF0_F0 = c->pc_8->c_C;
    if (c->fF0_F0 == 0)
    {
        c->fF0_F0 = sub_800BBDF4(c);
    }
    c->pc_8++;
    return 1;
}

int sub_800BA6D0(EvCtxEventfnc* c)
{
    c->fF4_F4 = c->pc_8->a_4;
    c->fF8_F8 = c->pc_8->b_8;
    c->fFC_FC = c->pc_8->c_C;
    c->fF0_F0 = (int)&c->fF4_F4;
    c->pc_8++;
    return 1;
}

extern int dword_800AEBD8;
int sub_800BA714(EvCtxEventfnc* c)
{
    if (c->pc_8->b_8 == 1 || dword_800AEBD8 < 0 || dword_800AEBD8 == c->f10_10)
    {
        if (((int (*)(int))c->pc_8->c_C)(c->fF0_F0) == 1)
        {
            c->fF0_F0 = 0;
            c->pc_8++;
            return 1;
        }
    }
    return 0;
}

int sub_800BA7A4(EvCtxEventfnc* c)
{
    if (c->pc_8->b_8 == 1 || dword_800AEBD8 < 0 || dword_800AEBD8 == c->f10_10)
    {
        c->fEC_EC = ((int (*)(int))c->pc_8->c_C)(c->fF0_F0);
        c->fF0_F0 = 0;
        c->pc_8++;
        return 1;
    }
    return 0;
}

#if 0
extern unsigned short word_8008B84C;
extern int sub_800A6D30(int a);
int sub_800BA82C(EvCtxEventfnc* c)
{
    word_8008B84C = *(unsigned short*)&c->pc_8->b_8;
    sub_800A6D30(0);
    c->pc_8++;
    dword_8008B540 = 1;
    return 1;
}
#endif
INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA82C);

#if 0
extern unsigned short word_8008B850;
int sub_800BA880(EvCtxEventfnc* c)
{
    word_8008B850 = *(unsigned short*)&c->pc_8->b_8;
    c->pc_8++;
    return 1;
}
#endif
INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA880);

extern void sub_800ADC5C(unsigned short* v, int a);
int sub_800BA8AC(EvCtxEventfnc* c)
{
    unsigned short v[3];
    v[0] = ((unsigned short*)&c->pc_8->a_4)[0];
    v[1] = ((unsigned short*)&c->pc_8->b_8)[1];
    v[2] = ((unsigned short*)&c->pc_8->b_8)[0];
    sub_800ADC5C(v, c->pc_8->c_C);
    c->pc_8++;
    return 1;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA930);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA9E4);

int sub_800BAA6C(EvCtxEventfnc* c)
{
    if (((int (*)(int))sub_80027330)(c->pc_8->b_8))
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

extern int sub_80027358(int a);
int sub_800BAAC0(EvCtxEventfnc* c)
{
    if (sub_80027358(c->pc_8->b_8))
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

extern int sub_800A683C(int a);
int sub_800BAB14(EvCtxEventfnc* c)
{
    sub_800A683C(c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

#if 0
extern int sub_8001C19C(int a, int b);
int sub_800BAB5C(EvCtxEventfnc* c)
{
    sub_8001C19C(1, 0x20);
    sub_800A6D30(8);
    dword_8008B540 = 1;
    c->pc_8++;
    return 1;
}
#endif
INCLUDE_OVERLAY_ASM(eventfnc, sub_800BAB5C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BABB0);

extern void sub_800379DC(EvVecEventfnc* v, int b);
int sub_800BAC60(EvCtxEventfnc* c)
{
    EvVecEventfnc v;
    EvVecEventfnc* src = (EvVecEventfnc*)c->pc_8->c_C;
    v.x_0 = src->x_0;
    v.y_4 = src->y_4 + 0x15E;
    v.z_8 = src->z_8;
    sub_800379DC(&v, c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

extern void sub_800379DC(EvVecEventfnc* v, int b);
int sub_800BACE0(EvCtxEventfnc* c)
{
    sub_800379DC(sub_800BBBA0(c->pc_8->a_4), c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

extern void sub_80037A20(int a, int b);
int sub_800BAD3C(EvCtxEventfnc* c)
{
    sub_80037A20(c->pc_8->c_C, c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

int sub_800BAD88(EvCtxEventfnc* c)
{
    int v = ((int (*)())sub_80037A4C)();
    int b = c->pc_8->b_8;
    if ((b == 1 && (short)v == 0x1000) || (b == 0 && (short)v == 0))
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BADF8);

extern void sub_80037A6C(int a, int b);
int sub_800BAEBC(EvCtxEventfnc* c)
{
    sub_80037A6C(c->pc_8->a_4, c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

int sub_800BAF08(EvCtxEventfnc* c)
{
    int v = c->pc_8->c_C;
    if (v == 0)
    {
        v = (int)sub_800BBBA0(c->pc_8->a_4);
    }
    sub_80037AC8(v);
    c->pc_8++;
    return 1;
}

int sub_800BAF68(EvCtxEventfnc* c)
{
    char* s = (char*)&saveData_8008B570;
    unsigned short v = *(unsigned short*)&c->pc_8->b_8;
    *(unsigned short*)(s + 0x2F0) = v;
    if ((short)v == *(short*)(s + 0x2F2))
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BAFAC);

int sub_800BB180(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    int r;
    int v = c->pc_8->b_8 & 0x80000000;
    c->f24_24[c->pc_8->a_4] = v;
    if ((c->pc_8->b_8 & 0x80000000) == 0)
    {
        c->pc_8++;
        r = 1;
    }
    else
    {
        m.m0_0 = 1 << c->pc_8->a_4;
        m.m4_4 = 3;
        m.mC_C = v;
        r = sub_800BB990(c, &m, 1, 1);
    }
    return r;
}

extern int sub_800A6504(int a, EvVecEventfnc* v);
int sub_800BB214(EvCtxEventfnc* c)
{
    EvVecEventfnc* v = sub_800BBBA0(c->pc_8->a_4);
    if (sub_800A6504(c->pc_8->b_8, v))
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BB27C);

extern int dword_800B1230;
int sub_800BB45C(EvCtxEventfnc* c)
{
    if (c->pc_8->b_8 == dword_800B1230)
    {
        c->fEC_EC = 0;
    }
    else
    {
        c->fEC_EC = 1;
    }
    c->pc_8++;
    return 1;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BB4A4);

extern void sub_80036528(int a, int b);
extern void sub_80036658(int a);
int sub_800BB7D8(EvCtxEventfnc* c)
{
    EvInsEventfnc* i = c->pc_8;
    if (i->a_4 == 1)
    {
        sub_80036528(0, *(unsigned char*)&i->b_8);
    }
    else
    {
        sub_80036658(0);
    }
    c->pc_8++;
    return 1;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BB840);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BB990);

extern int sub_800A8E7C();
extern int sub_800A7CB8(int a);
int sub_800BBAB0(int i)
{
    int r;
    if (i == 0)
    {
        r = sub_800A8E7C();
    }
    else
    {
        r = sub_800A7CB8(i - 1);
    }
    return r;
}

extern int sub_800A8FE0();
extern int sub_800A7CFC(int a);
int sub_800BBAE4(int i)
{
    int r;
    if (i == 0)
    {
        r = sub_800A8FE0();
    }
    else
    {
        r = sub_800A7CFC(i - 1);
    }
    return r;
}

#if 0
extern int sub_800A8EC4(int* p);
extern int sub_800A7D40(int a);
int sub_800BBB18(int* p)
{
    int r;
    int v = *p;
    if (v == 0)
    {
        r = sub_800A8EC4(p);
    }
    else
    {
        r = sub_800A7D40(v - 1);
    }
    return r;
}
#endif
INCLUDE_OVERLAY_ASM(eventfnc, sub_800BBB18);

#if 0
extern int sub_800A9008(int* p);
extern int sub_800A80C4(int a);
int sub_800BBB5C(int* p)
{
    int r;
    int v = *p;
    if (v == 0)
    {
        r = sub_800A9008(p);
    }
    else
    {
        r = sub_800A80C4(v - 1);
    }
    return r;
}
#endif
INCLUDE_OVERLAY_ASM(eventfnc, sub_800BBB5C);

extern EvVecEventfnc levantPos_8008BD18;
extern EvVecEventfnc* sub_800A7940(int a);
EvVecEventfnc* sub_800BBBA0(int i)
{
    EvVecEventfnc* r;
    if (i == 0)
    {
        r = &levantPos_8008BD18;
    }
    else
    {
        r = sub_800A7940(i - 1);
    }
    return r;
}

extern EvVecEventfnc levantRot_8008BD24;
extern EvVecEventfnc* sub_800A7984(int a);
EvVecEventfnc* sub_800BBBD0(int i)
{
    EvVecEventfnc* r;
    if (i == 0)
    {
        r = &levantRot_8008BD24;
    }
    else
    {
        r = sub_800A7984(i - 1);
    }
    return r;
}

EvVecEventfnc* sub_800BBC00(EvCtxEventfnc* c, int idx, int mode)
{
    if (mode == 1)
    {
        EvVecEventfnc* v = sub_800BBBA0(idx);
        c->vec3C_3C[idx].x_0 = v->x_0;
        c->vec3C_3C[idx].y_4 = v->y_4;
        c->vec3C_3C[idx].z_8 = v->z_8;
    }
    return &c->vec3C_3C[idx];
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BBC80);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BBDA0);

extern int dword_800AEBD4;
int sub_800BBDD8(int a)
{
    return (~dword_800AEBD4 & a) == 0;
}

int sub_800BBDF4(EvCtxEventfnc* c)
{
    if (c->ent_120 != 0)
    {
        return c->ent_120->f8C_8C;
    }
    return 0;
}

int sub_800BBE18(EvCtxEventfnc* c)
{
    if (c->ent_120 != 0)
    {
        return c->ent_120->f84_84;
    }
    return -1;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BBE3C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BC2B4);

int* sub_800BC560(int* p)
{
    int n = 0;
    do
    {
        n++;
        if (*p != 0)
        {
            n = 0;
        }
        p++;
    } while (n != 2);
    return p;
}

int sub_800BC58C(int* p)
{
    int m = 0;
    int i;
    for (i = 0; *p != 0; p++, i++)
    {
        m |= 1 << i;
    }
    return m;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BC5C8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BC6C4);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BC7A0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BC7A8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BC854);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BC98C);

#if 0
extern int dword_800AEBC8;
extern char dword_80091C10[];
void sub_800BCA18(unsigned int* a, unsigned int* b)
{
    unsigned int* r = (unsigned int*)sub_8003FDC0(dword_80091C10);
    dword_800AEBC8 = (int)r;
    sub_800403E8(r, a, (unsigned int)b);
}
#endif
INCLUDE_OVERLAY_ASM(eventfnc, sub_800BCA18);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BCA68);

typedef struct TaskEventfnc
{
    unsigned int flags_0;
    int f4_4;
    void (*next_8)();
} TaskEventfnc;
extern void sub_800BCB3C();
void sub_800BCB00(TaskEventfnc* t, int* x)
{
    x[0] = 0;
    x[1] = 0x1D;
    sub_800BCB3C(t, x);
    t->next_8 = sub_800BCB3C;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BCB3C);

INCLUDE_OVERLAY_ASM(eventfnc, dword_800BCDBC);
