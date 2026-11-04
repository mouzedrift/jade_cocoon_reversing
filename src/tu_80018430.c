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
#include "tu_80014954.h"

typedef struct
{
    int field_0;
    int field_4;
    short ids_8[6];
} EffectRow;
extern struct_4s dword_800795F0[];
extern EffectRow* dword_80091BE0;
extern int dword_8008D784;
extern int sub_80018908(int id, short (*tbl)[6]);
extern void sub_800149A4(EffectArgs* a);
void sub_8001852C(ActorEffectReq* p, int a1);
// Matched
void sub_80018430(short v)
{
    EffectTaskState* base = effectTask_8008D3F8->entry.buffer;
    base->field_40 = v;
}
// Matched
void sub_80018448(short v)
{
    EffectTaskState* base = effectTask_8008D3F8->entry.buffer;
    base->field_42 = v;
}
// Matched
void sub_80018460(int on)
{
    EffectTaskState* base = effectTask_8008D3F8->entry.buffer;
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
    EffectTaskState* base = effectTask_8008D3F8->entry.buffer;
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
int sub_800184DC(ActorEffectReq* a0, int a1)
{
    EffectTaskState* p = effectTask_8008D3F8->entry.buffer;
    sub_8001852C(a0, p->bits_44[a1]);
    p->flags_28 |= 1;
    return 1;
}
// Matched
void sub_8001852C(ActorEffectReq* p, int a1)
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
        if (p->hitTimes_4[n].field_0 >= 0)
        {
            p->hitTimes_4[n].field_0 += dword_800795F0[p->effect_0].field_2;
        }
        if (p->hitTimes_4[n].field_2 >= 0)
        {
            p->hitTimes_4[n].field_2 += dword_800795F0[p->effect_0].field_2;
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
                if (idx == -1 || p->hitTimes_4[k].field_0 == -1)
                {
                    continue;
                }
                args.field_0 = base[k].field_0;
                args.field_4 = (int)p->pos_C;
                args.field_8 = (int)p->bonePos_10;
                args.field_C = (int)p->pos_C;
                args.field_10 = (int)p->bonePos_10;
                args.field_18 = (int)p->boneMatrices_14;
                args.scale_14 = &tbl[idx][2];
                args.field_1C = p->hitTimes_4[k].field_0;
                args.field_1E = p->hitTimes_4[k].field_2;
                args.field_24 = tbl[idx][1];
                args.field_28 = (int)p->boneScale_34;
                args.field_2C = (int)p->scale_38;
                args.field_30 = p->targets_44[0].field_34;
                sub_800149A4(&args);
            }
            else if (mode == 1)
            {
                for (i = 0; i < p->count_40; i++)
                {
                    tbl = p->targets_44[i].tbl_0;
                    idx = sub_80018908(id, tbl);
                    if (idx == -1 || p->hitTimes_4[k].field_0 == -1)
                    {
                        continue;
                    }
                        args.field_0 = base[k].field_0;
                    args.field_4 = (int)p->pos_C;
                    args.field_8 = (int)p->bonePos_10;
                    args.field_C = p->targets_44[i].field_4;
                    args.field_10 = p->targets_44[i].field_8;
                    args.field_18 = p->targets_44[i].field_C;
                    args.scale_14 = &tbl[idx][2];
                    args.field_1C = p->hitTimes_4[k].field_0;
                    args.field_1E = p->hitTimes_4[k].field_2;
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
extern int sub_80018C00(ActorActionDesc* d, int* p, ActorScriptCmd** a2);
// Matched
ShortPair sub_80018A4C(Actor* obj, int* p, ActorScriptCmd** a2, int c)
{
    ShortPair r;
    ActorActionDesc d;
    short (*q)[2];
    memset(&r, 0, 4);
    if (p[0] == 0x16)
    {
        /* animation 27: its last hit window is at least 30 frames from its start */
        q = obj->anims_148[27].hitFrames_8;
        if (q[9][0] < 0)
        {
            q[9][0] = obj->anims_148[27].start_2;
            q[9][1] = q[9][0] + 30;
        }
        if (q[9][1] - q[9][0] < 30)
        {
            q[9][0] = obj->anims_148[27].start_2;
            q[9][1] = q[9][0] + 30;
        }
    }
    d.hitAnim_E = -1;
    d.effect_10 = -1;
    d.nextAnim_24 = -1;
    d.nextAnim_26 = -1;
    d.field_28 = -1;
    d.queuedAnim_2A = -1;
    d.flags_0 = 0;
    d.script_4 = 0;
    d.target_8 = 0;
    d.turnStep_C = 0;
    d.effectKinds_18 = 0;
    d.loopCount_20 = 0;
    d.scaleTarget_22 = 0;
    d.field_1C = 1;
    d.field_2C = 0;
    d.path_30 = 0;
    d.field_1C = (c == 0);
    d.effectMask_14 = p[2];
    if (sub_80018C00(&d, p, a2))
    {
        d.field_1C = 1;
    }
    r.a = sub_8001E254(obj, &d);
    r.b = sub_8001F03C((int)obj, (int)obj->script_D0, -1, 0x10);
    if (p[0] != 0x12 && c)
    {
        r.a = 0;
    }
    return r;
}
extern int dword_800B129C[];
extern int sub_8001AC8C(int idx);
extern int sub_80031870(int a0);
extern int sub_800316EC(int a0, int a1);
// Matched
int sub_80018C00(ActorActionDesc* d, int* p, ActorScriptCmd** t)
{
    int r;
    if (t == 0)
    {
        t = off_8007A024;
    }
    switch (p[0])
    {
    case 0:
        d->script_4 = t[2];
        d->hitAnim_E = 5;
        d->effect_10 = 0x13;
        d->effectKinds_18 = p[3];
        break;
    case 1:
        d->script_4 = t[9];
        d->turnStep_C = p[1];
        d->hitAnim_E = 0xC;
        d->effect_10 = sub_8001AC8C(p[1]);
        d->effectKinds_18 = p[3];
        break;
    case 2:
        d->hitAnim_E = 4;
        d->effect_10 = 0x3A;
        d->script_4 = t[17];
        d->effectKinds_18 = p[2];
        break;
    case 3:
        d->hitAnim_E = 4;
        d->effect_10 = 0x39;
        d->script_4 = t[18];
        d->effectKinds_18 = p[2];
        break;
    case 6:
        r = sub_80031870(p[1]);
        d->script_4 = t[3 + r];
        d->turnStep_C = r;
        d->hitAnim_E = r + 6;
        d->effect_10 = sub_800316EC(p[1], p[2]);
        d->effectKinds_18 = p[3];
        break;
    case 7:
        d->script_4 = t[13];
        d->hitAnim_E = 4;
        break;
    case 9:
        d->script_4 = t[10];
        d->hitAnim_E = 0xD;
        break;
    case 10:
        d->script_4 = t[11];
        d->hitAnim_E = 0xE;
        break;
    case 11:
        d->script_4 = t[16];
        d->hitAnim_E = 0x15;
        break;
    case 12:
        d->script_4 = t[12];
        d->hitAnim_E = 0x14;
        break;
    case 13:
        d->script_4 = t[20];
        break;
    case 14:
        d->script_4 = t[19];
        break;
    case 15:
        d->script_4 = t[22];
        d->hitAnim_E = 0x18;
        break;
    case 16:
        d->script_4 = t[21];
        d->hitAnim_E = 0x17;
        break;
    case 18:
        d->script_4 = t[14];
        d->hitAnim_E = 0x12;
        break;
    case 17:
        d->script_4 = t[15];
        d->hitAnim_E = 0x13;
        break;
    case 19:
        d->script_4 = t[23];
        d->hitAnim_E = 0x19;
        break;
    case 21:
        d->hitAnim_E = 0x1A;
        d->effect_10 = dword_800B129C[0] ? 0x3A : 0x39;
        d->script_4 = t[17];
        d->effectKinds_18 = p[2];
        break;
    case 22:
        d->hitAnim_E = 0x1B;
        d->effect_10 = dword_800B129C[0] ? 0x39 : 0x3A;
        d->script_4 = t[18];
        d->effectKinds_18 = p[2];
        break;
    case 5:
    case 26:
        d->script_4 = t[0x70 / 4 + p[1]];
        break;
    case 27:
        break;
    }
    return 0;
}
