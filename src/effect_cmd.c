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
#include "effect_data.h"
#include "skill_anim.h"
#include "engine.h"
#include "model.h"

typedef struct
{
    int kind_0;     // effect object kind (EffectObj.kind_E), -1: unused row
    int mode_4;     // 0: on the source actor, 1: on each target
    short ids_8[6]; // effect table ids (FindEffectTblRow_80018908), -1: unused
} EffectRow;
// effectFileTable_800795F0 (effect.c): per effect, the effect file and the frame offset of its hits
typedef struct
{
    short fileId_0;
    short hitOffset_2;
} EffectFileEntry;
extern EffectFileEntry effectFileTable_800795F0[];
extern EffectRow* effectRows_80091BE0;
extern int effectSfxStarted_8008D784;
extern int FindEffectTblRow_80018908(int id, short (*tbl)[6]);
extern void SpawnEffectObject_800149A4(EffectArgs* args);
void SpawnActorEffects_8001852C(ActorEffectReq* req, int hitFlags);
// Matched
void SetHitVariant_80018430(short variant)
{
    EffectTaskState* state = effectTask_8008D3F8->entry.buffer;
    state->hitVariant_40 = variant;
}
// Matched
void SetHitParam_80018448(short param)
{
    EffectTaskState* state = effectTask_8008D3F8->entry.buffer;
    state->hitParam_42 = param;
}
// Matched
void SetEffectFlag8_80018460(int on)
{
    EffectTaskState* state = effectTask_8008D3F8->entry.buffer;
    if (on)
    {
        state->flags_28 |= 8;
    }
    else
    {
        state->flags_28 &= ~8;
    }
}
// Matched
void SetTargetHitFlag_800184A0(int slot, int bit)
{
    EffectTaskState* state = effectTask_8008D3F8->entry.buffer;
    if (bit == 0)
    {
        state->hitFlags_44[slot] = 0;
    }
    else
    {
        state->hitFlags_44[slot] |= 1 << bit;
    }
}
// Matched
int PlayActorEffect_800184DC(ActorEffectReq* req, int slot)
{
    EffectTaskState* state = effectTask_8008D3F8->entry.buffer;
    SpawnActorEffects_8001852C(req, state->hitFlags_44[slot]);
    state->flags_28 |= 1;
    return 1;
}
// Matched
void SpawnActorEffects_8001852C(ActorEffectReq* req, int hitFlags)
{
    EffectArgs args;
    EffectRow* rows;
    int i;
    int j;
    int k;
    int n;
    int mode;
    int id;
    int idx;
    short (*tbl)[6];

    rows = effectRows_80091BE0;
    effectSfxStarted_8008D784 = 0;
    for (n = 0; n < 10; n++)
    {
        if (req->hitTimes_4[n].start_0 >= 0)
        {
            req->hitTimes_4[n].start_0 += effectFileTable_800795F0[req->effect_0].hitOffset_2;
        }
        if (req->hitTimes_4[n].end_2 >= 0)
        {
            req->hitTimes_4[n].end_2 += effectFileTable_800795F0[req->effect_0].hitOffset_2;
        }
    }
    for (k = 0; k < 10; k++)
    {
        if (rows[k].kind_0 == -1)
        {
            continue;
        }
        for (j = 0; j < 6; j++)
        {
            id = *(short*)((char*)rows + (k * 20 + j * 2) + 8);
            mode = rows[k].mode_4;
            if (id == -1)
            {
                continue;
            }
            if (mode == 0)
            {
                tbl = req->tbl_8;
                idx = FindEffectTblRow_80018908(id, tbl);
                if (idx == -1 || req->hitTimes_4[k].start_0 == -1)
                {
                    continue;
                }
                args.kind_0 = rows[k].kind_0;
                args.srcPos_4 = req->pos_C;
                args.srcBonePos_8 = req->bonePos_10;
                args.targetPos_C = req->pos_C;
                args.targetBonePos_10 = req->bonePos_10;
                args.targetBoneMatrices_18 = req->boneMatrices_14;
                args.offset_14 = &tbl[idx][2];
                args.hitStart_1C = req->hitTimes_4[k].start_0;
                args.hitEnd_1E = req->hitTimes_4[k].end_2;
                args.bone_24 = tbl[idx][1];
                args.boneScales_28 = req->boneScale_34;
                args.scale_2C = req->scale_38;
                args.hitFlags_30 = req->targets_44[0].hitFlags_34;
                SpawnEffectObject_800149A4(&args);
            }
            else if (mode == 1)
            {
                for (i = 0; i < req->count_40; i++)
                {
                    tbl = req->targets_44[i].tbl_0;
                    idx = FindEffectTblRow_80018908(id, tbl);
                    if (idx == -1 || req->hitTimes_4[k].start_0 == -1)
                    {
                        continue;
                    }
                        args.kind_0 = rows[k].kind_0;
                    args.srcPos_4 = req->pos_C;
                    args.srcBonePos_8 = req->bonePos_10;
                    args.targetPos_C = req->targets_44[i].pos_4;
                    args.targetBonePos_10 = req->targets_44[i].bonePos_8;
                    args.targetBoneMatrices_18 = req->targets_44[i].boneMatrices_C;
                    args.offset_14 = &tbl[idx][2];
                    args.hitStart_1C = req->hitTimes_4[k].start_0;
                    args.hitEnd_1E = req->hitTimes_4[k].end_2;
                    args.bone_24 = tbl[idx][1];
                    args.boneScales_28 = req->targets_44[i].boneScale_2C;
                    args.scale_2C = req->targets_44[i].scale_30;
                    args.hitFlags_30 = req->targets_44[i].hitFlags_34;
                    SpawnEffectObject_800149A4(&args);
                }
            }
        }
    }
}
// Matched
int FindEffectTblRow_80018908(int id, short (*tbl)[6])
{
    int i;
    int row = -1;
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
                            row = i;
                            break;
                        }
                    }
                }
                else
                {
                    row = i;
                }
                break;
            }
        }
    }
    return row;
}
// Matched
int GetWeaponEffect_800189F8(void)
{
    SaveData* sd = &saveData_8008B570;
    EquipmentData* weapon = GetWeaponData_8001CF84(*((unsigned char*)sd + 0x7E4));
    SetHitVariantForCommand_800BFAF8(*((unsigned char*)sd + 0x7E4));
    return weaponEffectIds_80079708[weapon->kind_2];
}
typedef struct
{
    short a;
    short b;
} ShortPair;
extern int SetupCommandAction_80018C00(ActorActionDesc* desc, int* cmd, ActorScriptCmd** scripts);
// Matched
ShortPair StartCommandAction_80018A4C(Actor* obj, int* cmd, ActorScriptCmd** scripts, int c)
{
    ShortPair result;
    ActorActionDesc desc;
    short (*hitFrames)[2];
    memset(&result, 0, 4);
    if (cmd[0] == 0x16)
    {
        /* animation 27: its last hit window is at least 30 frames from its start */
        hitFrames = obj->anims_148[27].hitFrames_8;
        if (hitFrames[9][0] < 0)
        {
            hitFrames[9][0] = obj->anims_148[27].start_2;
            hitFrames[9][1] = hitFrames[9][0] + 30;
        }
        if (hitFrames[9][1] - hitFrames[9][0] < 30)
        {
            hitFrames[9][0] = obj->anims_148[27].start_2;
            hitFrames[9][1] = hitFrames[9][0] + 30;
        }
    }
    desc.hitAnim_E = -1;
    desc.effect_10 = -1;
    desc.nextAnim_24 = -1;
    desc.nextAnim_26 = -1;
    desc.anim_28 = -1;
    desc.queuedAnim_2A = -1;
    desc.flags_0 = 0;
    desc.script_4 = 0;
    desc.target_8 = 0;
    desc.turnStep_C = 0;
    desc.effectKinds_18 = 0;
    desc.loopCount_20 = 0;
    desc.scaleTarget_22 = 0;
    desc.field_1C = 1;
    desc.field_2C = 0;
    desc.path_30 = 0;
    desc.field_1C = (c == 0);
    desc.effectMask_14 = cmd[2];
    if (SetupCommandAction_80018C00(&desc, cmd, scripts))
    {
        desc.field_1C = 1;
    }
    result.a = StartActorAction_8001E254(obj, &desc);
    result.b = GetActorScriptTime_8001F03C((int)obj, (int)obj->script_D0, -1, 0x10);
    if (cmd[0] != 0x12 && c)
    {
        result.a = 0;
    }
    return result;
}
extern int dword_800B129C[];
extern int GetSkillEffect_800316EC(int slot, int actorMask);
// Matched
int SetupCommandAction_80018C00(ActorActionDesc* desc, int* cmd, ActorScriptCmd** scripts)
{
    int animIdx;
    if (scripts == 0)
    {
        scripts = commandScripts_8007A024;
    }
    switch (cmd[0])
    {
    case 0:
        desc->script_4 = scripts[2];
        desc->hitAnim_E = 5;
        desc->effect_10 = 0x13;
        desc->effectKinds_18 = cmd[3];
        break;
    case 1:
        desc->script_4 = scripts[9];
        desc->turnStep_C = cmd[1];
        desc->hitAnim_E = 0xC;
        desc->effect_10 = GetMagicEffect_8001AC8C(cmd[1]);
        desc->effectKinds_18 = cmd[3];
        break;
    case 2:
        desc->hitAnim_E = 4;
        desc->effect_10 = 0x3A;
        desc->script_4 = scripts[17];
        desc->effectKinds_18 = cmd[2];
        break;
    case 3:
        desc->hitAnim_E = 4;
        desc->effect_10 = 0x39;
        desc->script_4 = scripts[18];
        desc->effectKinds_18 = cmd[2];
        break;
    case 6:
        animIdx = SkillSlotToAnimIndex_80031870(cmd[1]);
        desc->script_4 = scripts[3 + animIdx];
        desc->turnStep_C = animIdx;
        desc->hitAnim_E = animIdx + 6;
        desc->effect_10 = GetSkillEffect_800316EC(cmd[1], cmd[2]);
        desc->effectKinds_18 = cmd[3];
        break;
    case 7:
        desc->script_4 = scripts[13];
        desc->hitAnim_E = 4;
        break;
    case 9:
        desc->script_4 = scripts[10];
        desc->hitAnim_E = 0xD;
        break;
    case 10:
        desc->script_4 = scripts[11];
        desc->hitAnim_E = 0xE;
        break;
    case 11:
        desc->script_4 = scripts[16];
        desc->hitAnim_E = 0x15;
        break;
    case 12:
        desc->script_4 = scripts[12];
        desc->hitAnim_E = 0x14;
        break;
    case 13:
        desc->script_4 = scripts[20];
        break;
    case 14:
        desc->script_4 = scripts[19];
        break;
    case 15:
        desc->script_4 = scripts[22];
        desc->hitAnim_E = 0x18;
        break;
    case 16:
        desc->script_4 = scripts[21];
        desc->hitAnim_E = 0x17;
        break;
    case 18:
        desc->script_4 = scripts[14];
        desc->hitAnim_E = 0x12;
        break;
    case 17:
        desc->script_4 = scripts[15];
        desc->hitAnim_E = 0x13;
        break;
    case 19:
        desc->script_4 = scripts[23];
        desc->hitAnim_E = 0x19;
        break;
    case 21:
        desc->hitAnim_E = 0x1A;
        desc->effect_10 = dword_800B129C[0] ? 0x3A : 0x39;
        desc->script_4 = scripts[17];
        desc->effectKinds_18 = cmd[2];
        break;
    case 22:
        desc->hitAnim_E = 0x1B;
        desc->effect_10 = dword_800B129C[0] ? 0x39 : 0x3A;
        desc->script_4 = scripts[18];
        desc->effectKinds_18 = cmd[2];
        break;
    case 5:
    case 26:
        desc->script_4 = scripts[0x70 / 4 + cmd[1]];
        break;
    case 27:
        break;
    }
    return 0;
}
