#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "STDLIB.H"
#include "STDIO.H"
#include "LIBPAD.H"
#include "LIBSND.H"
#include "LIBMCX.H"
#include "LIBPRESS.H"
#include "LIBETC.H"
#include "LIBMCRD.H"
#include "sound.h"
#include "data_decls.h"




// Matched
int sub_80013358(int idx)
{
    return dword_80079320[idx];
}
typedef struct
{
    unsigned short flags_0;
    short power_2;
    signed char c4;
    unsigned char c5;
    unsigned char c6;
    signed char hit_7;
    unsigned char element_8;
    unsigned char kind_9;
    unsigned char c_A;
    unsigned char c_B;
} AttackDesc;
typedef struct
{
    unsigned short kind_0;
    short field_2;
    int flags_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
} AttackResult;
extern double sqrt(double);
extern int Rand100_80013E30(void);
#if 0
// Not matched (11 lines): the copy of the first __fixdfsi result sits in the second call's delay slot in the original, and n (Rand chance) is in $v1 instead of $v0. Also tried: dead/used second conversion into another var (c/n: call deleted), (int)dmg in the test, n = 100 hoisted, if/else and nested ternary for n, ra < n, n renamed to other locals
void sub_80013374(AttackDesc* q, UnitStatus* f0, UnitStatus* f1, int* r0, int* r1, int* p, AttackResult* out)
{
    int crit0;
    int crit1;
    int b2;
    int atk;
    int def;
    int hit;
    int eva;
    int a;
    int b;
    int v;
    int i;
    int n;
    int c;
    int ra;
    int ch;
    double d;
    double dmg;

    crit0 = 0;
    crit1 = 0;
    hit = 0;
    eva = 0;
    atk = 0;
    def = 0;
    b2 = LowestSetBit_80014358(p[3]);
    switch (q->kind_9)
    {
    case 0:
        atk = r0[0];
        hit = r0[4];
        def = r1[1];
        eva = r1[5];
        crit0 = r0[6];
        crit1 = r1[7];
        break;
    case 1:
        atk = r0[2];
        def = r1[3];
        hit = 100;
        break;
    case 2:
        atk = q->power_2;
        def = 1;
        hit = 100;
        break;
    }
    if ((signed char)f1->field_20[q->element_8] < 0)
    {
        def = 1;
        eva = def;
    }
    if (def == 0)
    {
        def = 1;
    }
    if (q->power_2 != 0)
    {
        a = Rand100_80013E30();
        b = Rand100_80013E30();
        if (!(hit - eva < a) || HasStatusFlag_80033548(f1, 2) != 0)
        {
            out->kind_0 = 1;
            if (q->element_8 != 0xFF)
            {
                d = atk * 100 / def;
                d = sqrt(d);
                dmg = (double)(atk * (f0->level_44 + 3)) * d / 10.0 * q->power_2 / 100.0 / 20.0;
                if (b < crit0 - crit1 + q->hit_7 && q->kind_9 == 0)
                {
                    out->kind_0 = 4;
                    dmg = dmg * 7.0 / 4.0;
                }
                if (q->element_8 < 4)
                {
                    d = sqrt(sqrt(f0->element_3E[q->element_8] * 1250));
                    dmg = dmg * (d / 10.0);
                }
                dmg = dmg * (signed char)f1->field_20[q->element_8];
                dmg = dmg / 32.0;
                v = dmg;
                v = dmg;
                if (v == 0 || (v += frameCount_8008D3FC & 1) == 0)
                {
                    v = 1;
                }
            }
            else
            {
                v = atk;
            }
            if (HasStatusFlag_80033548(f1, 0x400) && (q->c_A != 0 || !(q->flags_0 & 0x400)))
            {
                v = 0;
            }
            if (q->c_B == 0)
            {
                out->field_1C = v;
                if (q->element_8 == 8 && v > 0)
                {
                    if (GetHp_800334D8(f1) < v)
                    {
                        v = GetHp_800334D8(f1);
                    }
                    out->field_14 = -v;
                }
            }
            else if (q->c_B == 1)
            {
                v /= 2;
                out->field_20 = v;
                out->kind_0 = 2;
                if (q->element_8 == 8 && v > 0)
                {
                    if (GetMp_800334F0(f1) < v)
                    {
                        v = GetMp_800334F0(f1);
                    }
                    out->field_18 = -v;
                }
            }
            else if (q->c_B == 3)
            {
                c = (signed char)f1->field_20[q->element_8];
                if (rand() % 32 < c)
                {
                    out->field_1C = GetHp_800334D8(f1) - 1;
                    out->kind_0 = 4;
                    out->flags_4 |= 2;
                }
                else
                {
                    goto miss;
                }
            }
            else if (q->c_B == 2)
            {
                out->field_1C = v;
                out->kind_0 = 3;
                out->field_20 = v / 5 * 2;
            }
        }
        else
        {
        miss:
            out->kind_0 = 5;
        }
    }
    if (out->field_1C > 0 || out->field_20 > 0)
    {
        out->flags_4 |= 2;
    }
    if (q->power_2 == 0 || out->kind_0 != 5)
    {
        v = (q->c6 + r0[8]) * r1[9] / 100;
        if (q->c_A == 3)
        {
            ra = Rand100_80013E30();
            if (q->element_8 == 11)
            {
                n = 100;
            }
            else
            {
                n = (v * (signed char)f1->field_20[q->element_8]) ? v * (signed char)f1->field_20[q->element_8] / 32 : 0;
            }
            if (n > ra)
            {
                goto status;
            }
            if (q->flags_0 & 0x7FB)
            {
                SetTargetHitFlag_800184A0(b2, 2);
            }
        }
        else if (q->c_A == 0)
        {
            if (q->flags_0 & 0x3800)
            {
            status:
                out->field_8 |= q->flags_0;
            }
            else
            {
                out->flags_4 |= q->flags_0;
            }
        }
    }
    if (HasStatusFlag_80033548(f1, 0x3800) && (q->flags_0 & 0x7FB) && q->c_A == 3)
    {
        for (i = 0; i < 3; i++)
        {
            int m = 1 << (i + 11);
            if (f1->status_0 & m)
            {
                break;
            }
        }
        if (i == 0)
        {
            out->flags_4 |= 0x800;
            SetTargetHitFlag_800184A0(b2, 3);
        }
        else if (i == 1)
        {
            out->flags_4 |= 0x1800;
            SetTargetHitFlag_800184A0(b2, 4);
        }
        else
        {
            out->flags_4 |= 0x3800;
            SetTargetHitFlag_800184A0(b2, 5);
        }
        out->field_8 &= ~0x7FB;
        SetTargetHitFlag_800184A0(b2, 2);
    }
    if (out->field_1C == 0 && out->field_20 == 0 && out->field_8 != 0 && out->flags_4 != 0)
    {
        out->kind_0 = 5;
    }
    if (out->field_8 & 0x400)
    {
        out->field_1C = GetHp_800334D8(f1);
        out->kind_0 = 1;
    }
    if (HasStatusFlag_80033548(f1, 2))
    {
        out->field_8 &= ~2;
    }
}
#endif
INCLUDE_ASM(sub_80013374);
extern void sub_80012BB0(UnitStatus* a0, UnitStatus* a1, int* p, int a3);
// Matched
void sub_80013C28(UnitStatus* a0, UnitStatus* a1, int* p, int a3)
{
    int r;
    if (p[0] == 4)
    {
        switch (p[1])
        {
        case 3:
            r = rand() % 6;
            if (r == 0)
            {
                r = 1;
            }
            else if (r == 5)
            {
                r = 3;
            }
            else
            {
                r = 2;
            }
            sub_80012614(a1, 1, r, 0);
            sub_80012614(a1, 0, r, 0);
            break;
        case 4:
            sub_80012614(a1, 5, sub_80013DB0(), 0);
            break;
        case 5:
            sub_80012614(a1, 7, sub_80013DB0(), 0);
            break;
        case 6:
            sub_80012614(a1, 9, sub_80013DB0(), 0);
            break;
        case 7:
            sub_80012614(a1, 0xB, sub_80013DB0(), 0);
            break;
        case 8:
            sub_80012614(a1, 0xD, sub_80013DB0(), 0);
            break;
        }
        sub_80011B24(p[1]);
        sub_80012BB0(a0, a1, p, a3);
    }
}
