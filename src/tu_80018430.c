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



#include "effect_obj.h"
#include "actor.h"
#include "tu_80018430.h"

typedef struct
{
    int field_0;
    int field_4;
    short ids_8[6];
} EffectRow;
extern ShortPair2 dword_800795F0[];
extern EffectRow* dword_80091BE0;
extern int dword_8008D784;
extern int sub_80018908(int id, short (*tbl)[6]);
extern void sub_800149A4(EffectArgs* a);
void sub_8001852C(EffectSet* p, int a1);
// Matched
void sub_80018430(short v)
{
    EffectTaskState* base = EFFECT_STATE;
    base->field_40 = v;
}
// Matched
void sub_80018448(short v)
{
    EffectTaskState* base = EFFECT_STATE;
    base->field_42 = v;
}
// Matched
void sub_80018460(int on)
{
    EffectTaskState* base = EFFECT_STATE;
    if (on)
    {
        base->flags_28 |= 8;
    }
    else
    {
        base->flags_28 &= ~8;
    }
}
// Matched
void sub_800184A0(int arg, int bit)
{
    EffectTaskState* base = EFFECT_STATE;
    if (bit == 0)
    {
        base->bits_44[arg] = 0;
    }
    else
    {
        base->bits_44[arg] |= 1 << bit;
    }
}
// Matched
int sub_800184DC(int a0, int a1)
{
    EffectTaskState* p = EFFECT_STATE;
    sub_8001852C((EffectSet*)a0, p->bits_44[a1]);
    p->flags_28 |= 1;
    return 1;
}
// Matched
void sub_8001852C(EffectSet* p, int a1)
{
    EffectArgs args;
    EffectRow* base;
    int i;
    int j;
    int k;
    int n;
    int mode;
    int id;
    int idx;
    short (*tbl)[6];

    base = dword_80091BE0;
    dword_8008D784 = 0;
    for (n = 0; n < 10; n++)
    {
        if (p->pairs_4[n].a >= 0)
        {
            p->pairs_4[n].a += dword_800795F0[p->idx_0].b;
        }
        if (p->pairs_4[n].b >= 0)
        {
            p->pairs_4[n].b += dword_800795F0[p->idx_0].b;
        }
    }
    for (k = 0; k < 10; k++)
    {
        if (base[k].field_0 == -1)
        {
            continue;
        }
        for (j = 0; j < 6; j++)
        {
            id = *(short*)((char*)base + (k * 20 + j * 2) + 8);
            mode = base[k].field_4;
            if (id == -1)
            {
                continue;
            }
            if (mode == 0)
            {
                tbl = p->tbl_8;
                idx = sub_80018908(id, tbl);
                if (idx == -1 || p->pairs_4[k].a == -1)
                {
                    continue;
                }
                args.field_0 = base[k].field_0;
                args.field_4 = p->field_C;
                args.field_8 = p->field_10;
                args.field_C = p->field_C;
                args.field_10 = p->field_10;
                args.field_18 = p->field_14;
                args.scale_14 = &tbl[idx][2];
                args.field_1C = p->pairs_4[k].a;
                args.field_1E = p->pairs_4[k].b;
                args.field_24 = tbl[idx][1];
                args.field_28 = p->field_34;
                args.field_2C = p->field_38;
                args.field_30 = p->targets_44[0].field_34;
                sub_800149A4(&args);
            }
            else if (mode == 1)
            {
                for (i = 0; i < p->count_40; i++)
                {
                    tbl = p->targets_44[i].tbl_0;
                    idx = sub_80018908(id, tbl);
                    if (idx == -1 || p->pairs_4[k].a == -1)
                    {
                        continue;
                    }
                        args.field_0 = base[k].field_0;
                    args.field_4 = p->field_C;
                    args.field_8 = p->field_10;
                    args.field_C = p->targets_44[i].field_4;
                    args.field_10 = p->targets_44[i].field_8;
                    args.field_18 = p->targets_44[i].field_C;
                    args.scale_14 = &tbl[idx][2];
                    args.field_1C = p->pairs_4[k].a;
                    args.field_1E = p->pairs_4[k].b;
                    args.field_24 = tbl[idx][1];
                    args.field_28 = p->targets_44[i].field_2C;
                    args.field_2C = p->targets_44[i].field_30;
                    args.field_30 = p->targets_44[i].field_34;
                    sub_800149A4(&args);
                }
            }
        }
    }
}
// Matched
int sub_80018908(int id, short (*tbl)[6])
{
    int i;
    int r = -1;
    if (tbl != 0 && tbl[0][0] != -1)
    {
        for (i = 0; tbl[i][0] != -1; i++)
        {
            if (id == tbl[i][0])
            {
                if (tbl[i][2] == -1 && tbl[i][3] == -1 && tbl[i][4] == -1 && tbl[i][5] == -1)
                {
                    id = tbl[i][1];
                    for (i = 0; tbl[i][0] != -1; i++)
                    {
                        if (id == tbl[i][0])
                        {
                            r = i;
                            break;
                        }
                    }
                }
                else
                {
                    r = i;
                }
                break;
            }
        }
    }
    return r;
}
// Matched
int sub_800189F8(void)
{
    SaveData* sd = &saveData_8008B570;
    EquipmentData* p = GetWeaponData_8001CF84(*((unsigned char*)sd + 0x7E4));
    sub_800BFAF8(*((unsigned char*)sd + 0x7E4));
    return dword_80079708[p->field_2];
}
typedef struct
{
    short a;
    short b;
} ShortPair;
typedef struct
{
    int f0;
    int f4;
    int f8;
    short fC;
    short fE;
    int f10;
    int f14;
    int f18;
    int f1C;
    short f20;
    short f22;
    short f24[4];
    int f2C;
    int f30;
    int pad[11];
} ActionDesc;
extern int sub_80018C00(ActionDesc* d, int* p, int* a2);
// Matched
ShortPair sub_80018A4C(Actor* obj, int* p, int* a2, int c)
{
    ShortPair r;
    ActionDesc d;
    ActorRec65C* q;
    memset(&r, 0, 4);
    if (p[0] == 0x16)
    {
        q = &((ActorData148*)obj->anims_148)->rec_65C;
        if (q->field_24 < 0)
        {
            q->field_24 = ((ActorData148*)obj->anims_148)->field_656;
            q->field_26 = q->field_24 + 30;
        }
        if (q->field_26 - q->field_24 < 30)
        {
            q->field_24 = ((ActorData148*)obj->anims_148)->field_656;
            q->field_26 = q->field_24 + 30;
        }
    }
    d.fE = -1;
    d.f10 = -1;
    d.f24[0] = -1;
    d.f24[1] = -1;
    d.f24[2] = -1;
    d.f24[3] = -1;
    d.f0 = 0;
    d.f4 = 0;
    d.f8 = 0;
    d.fC = 0;
    d.f18 = 0;
    d.f20 = 0;
    d.f22 = 0;
    d.f1C = 1;
    d.f2C = 0;
    d.f30 = 0;
    d.f1C = (c == 0);
    d.f14 = p[2];
    if (sub_80018C00(&d, p, a2))
    {
        d.f1C = 1;
    }
    r.a = sub_8001E254((struct_obj_A*)obj, &d);
    r.b = sub_8001F03C((int)obj, (int)obj->script_D0, -1, 0x10);
    if (p[0] != 0x12 && c)
    {
        r.a = 0;
    }
    return r;
}
extern int off_8007A024[];
extern int dword_800B129C[];
extern int sub_8001AC8C(int idx);
extern int sub_80031870(int a0);
extern int sub_800316EC(int a0, int a1);
// Matched
int sub_80018C00(ActionDesc* d, int* p, int* t)
{
    int r;
    if (t == 0)
    {
        t = off_8007A024;
    }
    switch (p[0])
    {
    case 0:
        d->f4 = t[0x8 / 4];
        d->fE = 5;
        d->f10 = 0x13;
        d->f18 = p[3];
        break;
    case 1:
        d->f4 = t[0x24 / 4];
        d->fC = p[1];
        d->fE = 0xC;
        d->f10 = sub_8001AC8C(p[1]);
        d->f18 = p[3];
        break;
    case 2:
        d->fE = 4;
        d->f10 = 0x3A;
        d->f4 = t[0x44 / 4];
        d->f18 = p[2];
        break;
    case 3:
        d->fE = 4;
        d->f10 = 0x39;
        d->f4 = t[0x48 / 4];
        d->f18 = p[2];
        break;
    case 6:
        r = sub_80031870(p[1]);
        d->f4 = t[0xC / 4 + r];
        d->fC = r;
        d->fE = r + 6;
        d->f10 = sub_800316EC(p[1], p[2]);
        d->f18 = p[3];
        break;
    case 7:
        d->f4 = t[0x34 / 4];
        d->fE = 4;
        break;
    case 9:
        d->f4 = t[0x28 / 4];
        d->fE = 0xD;
        break;
    case 10:
        d->f4 = t[0x2C / 4];
        d->fE = 0xE;
        break;
    case 11:
        d->f4 = t[0x40 / 4];
        d->fE = 0x15;
        break;
    case 12:
        d->f4 = t[0x30 / 4];
        d->fE = 0x14;
        break;
    case 13:
        d->f4 = t[0x50 / 4];
        break;
    case 14:
        d->f4 = t[0x4C / 4];
        break;
    case 15:
        d->f4 = t[0x58 / 4];
        d->fE = 0x18;
        break;
    case 16:
        d->f4 = t[0x54 / 4];
        d->fE = 0x17;
        break;
    case 18:
        d->f4 = t[0x38 / 4];
        d->fE = 0x12;
        break;
    case 17:
        d->f4 = t[0x3C / 4];
        d->fE = 0x13;
        break;
    case 19:
        d->f4 = t[0x5C / 4];
        d->fE = 0x19;
        break;
    case 21:
        d->fE = 0x1A;
        d->f10 = dword_800B129C[0] ? 0x3A : 0x39;
        d->f4 = t[0x44 / 4];
        d->f18 = p[2];
        break;
    case 22:
        d->fE = 0x1B;
        d->f10 = dword_800B129C[0] ? 0x39 : 0x3A;
        d->f4 = t[0x48 / 4];
        d->f18 = p[2];
        break;
    case 5:
    case 26:
        d->f4 = t[0x70 / 4 + p[1]];
        break;
    case 27:
        break;
    }
    return 0;
}
