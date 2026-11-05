#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "camera.h"
#include "model.h"
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
#include "effect_data.h"
#include "engine.h"
#include "main.h"
#include "model_ftg.h"
#include "util.h"
#include "cd.h"

extern short screenOffset_8008D474[2];
extern short battleCamSpline1Tail_80084350[]; // a short table (indexed & 0xFFF) starts at +0x1F0 (0x80084540)
extern int StartFileRequestTask_8003C6C8(FileRequestDesc* req);
extern unsigned short padPrevHeld_800918C8[];
extern unsigned short padRepeat_800918CC[];
extern unsigned short padReleased_800918D4[];
extern unsigned short padPressed_8009194C[];
extern unsigned short padHoldFrames_80091950[][16];
extern signed char padAnalog_800918D8[][4];
extern unsigned char padAnalogMax_800918E0[][4];
// Matched
void RunActorScript_8001EA48(void* actor)
{
    Actor* o = actor;
    int done;
    int flag22;
    int flag21;
    int target;
    ActorScriptCmd* cmd;
    int anim;
    int mode;
    int flagsD4;
    flag22 = 0;
    flag21 = flag22;
    done = flag22;
    target = o->frame_90;
    if (o->scriptLen_C6 <= 0)
    {
        return;
    }
    if (o->flags_4 & 0x4000)
    {
        if (++o->wait_C8 >= o->waitLen_CA)
        {
            o->wait_C8 = 0;
            o->waitLen_CA = 0;
            o->flags_4 |= 0x10000;
        }
    }
    if (o->flags_4 & 0x10000)
    {
        target = -1;
    }
    cmd = (ActorScriptCmd*)((unsigned int*)o->script_D0 + o->scriptPos_C4);
    while (!done)
    {
        if (target != cmd->frame_2 && o->frame_90 != cmd->frame_2 && cmd->frame_2 != -2)
        {
            return;
        }
        o->flags_4 &= ~0x10000;
        switch (cmd->op_0)
        {
        case 0:
            o->flags_4 &= 0xFF17FFFF;
            return;
        case 1:
            anim = cmd->arg_6;
            if (o->animIdx_C2 != anim)
            {
                SetActorAnimPaused_8001D6EC(o, 0);
                if (anim == 0x4003)
                {
                    anim = o->nextAnim_A4;
                    o->animIdx_C2 = o->nextAnim_A4;
                    o->nextAnim_A4 = o->queuedAnim_FE;
                    o->queuedAnim_FE = -1;
                }
                else
                {
                    o->animIdx_C2 = anim;
                }
                mode = flag22 ? -2 : -1;
                if (o->startMode_A8 >= 0)
                {
                    mode = o->startMode_A8;
                    o->startMode_A8 = -1;
                }
                SetActorAnim_8001D760(o, anim, mode, flag21);
            }
            done = 1;
            break;
        case 2:
            flag22 = 1;
            break;
        case 3:
            if (!(o->flags_4 & 0x2000000))
            {
                flagsD4 = o->flags_D4;
                if (!(flagsD4 & 1))
                {
                    flag21 = 1;
                }
                o->flags_D4 = flagsD4 & ~1;
            }
            break;
        case 4:
            o->wait_C8 = 0;
            o->waitLen_CA = cmd->arg_6;
            break;
        case 5:
            o->wait_C8 = 0;
            o->waitLen_CA = o->loopCount_F4;
            break;
        case 6:
            StartActorFadeIn_8001D9E4(o, GetActorScriptTime_8001F03C((int)o, (int)cmd, 0x4000, 0), cmd->arg_6);
            break;
        case 7:
            StartActorFadeOut_8001DA08(o, GetActorScriptTime_8001F03C((int)o, (int)cmd, 0x4000, 0), cmd->arg_6);
            break;
        case 8:
            StopActorFade_8001DA2C(o);
            break;
        case 9:
            StartActorScale_8001DA4C(o, GetActorScriptTime_8001F03C((int)o, (int)cmd, 0x4001, 0), o->scale_26, cmd->arg_6);
            break;
        case 10:
            StartActorScale_8001DA4C(o, GetActorScriptTime_8001F03C((int)o, (int)cmd, 0x4001, 0), o->scale_26, o->scaleTarget_F6);
            break;
        case 11:
            SetActorVisible_8001D730(o, cmd->arg_6);
            break;
        case 12:
            RequestActorAnim_8001D8B4(o, cmd->arg_6);
            break;
        case 13:
            if (IsActorAnimLoadIdle_8001D8A8(o))
            {
                break;
            }
            else
            {
                o->flags_4 |= 0x10000;
                return;
            }
        case 14:
            ReleaseActorAnim_8001D92C(o, cmd->arg_6);
            break;
        case 15:
            if ((o->flags_4 & 0x4080000) && o->kind_C < 3)
            {
                if (!TurnActorTowards_8001DDFC(o, &o->target_70, o->target_70.pad))
                {
                    RestartActorMotion_8001D71C(o);
                    o->flags_4 |= 0x10000;
                    return;
                }
                o->flags_4 &= ~0x80000;
            }
            o->flags_4 &= ~0x400000;
            if (!(o->flags_4 & 0x20000))
            {
                o->flags_4 |= 0x10000;
                return;
            }
            o->flags_4 &= ~0x20000;
            break;
        case 16:
            StopActorScript_8001EFC4(o);
            break;
        case 17:
            if (o->animIdx_C2 != o->prevAnimIdx_C0)
            {
                o->animIdx_C2 = o->prevAnimIdx_C0;
                SetActorAnim_8001D760(o, o->prevAnimIdx_C0, -2, flag21);
            }
            break;
        case 18:
            if (!ApproachActorTarget_8001DC60(o, &o->target_70, o->target_70.pad, 200))
            {
                o->flags_4 |= 0x10000;
                return;
            }
            target = -1;
            o->flags_4 &= ~0x80000;
            break;
        case 19:
            if (TurnActorTowards_8001DDFC(o, &o->target_70, o->target_70.pad))
            {
                target = -1;
                o->flags_4 &= ~0x80000;
            }
            else
            {
                RestartActorMotion_8001D71C(o);
                o->flags_4 |= 0x10000;
                return;
            }
            break;
        case 21:
            if (o->waitLen_CA != 0 || o->frame_90 != o->endFrame_1A || (o->flags_4 & 0x2000000))
            {
                o->flags_4 |= 0x10000;
                return;
            }
            break;
        case 22:
            SetActorAnimPaused_8001D6EC(o, cmd->arg_6 != 0);
            break;
        case 23:
            if (++o->waitCount_B0 > cmd->arg_6)
            {
                o->waitCount_B0 = 0;
            }
            else
            {
                o->flags_4 |= 0x10000;
                return;
            }
            break;
        case 24:
            o->pulse_BC = 0;
            o->pulseRate_BE = cmd->arg_6;
            o->flags_4 = o->flags_4 | cmd->arg_A | 0x40000000;
            break;
        }
        o->scriptPos_C4 += cmd->len_1;
        cmd = (ActorScriptCmd*)((unsigned int*)cmd + cmd->len_1);
    }
}
// Matched
void StopActorScript_8001EFC4(Actor* actor)
{
    unsigned int flags = actor->flags_4;
    int kind;
    if (flags & 0x800000)
    {
        kind = actor->kind_C;
        if (kind < 0)
        {
            if (flags & 0x200000)
            {
                ClearScriptActorBusy_800A5BCC(kind - 2);
            }
        }
        else if (kind >= 3)
        {
            if (flags & 0x200000)
            {
                ClearScriptActorBusy_800A5BCC(kind - 2);
            }
        }
    }
    actor->flags_4 &= 0xFF17FFFF;
}
// Matched
int GetActorScriptTime_8001F03C(int actorAddr, int scriptAddr, int target, int frame)
{
    Actor* o = (Actor*)actorAddr;
    ActorScriptCmd* cmd = (ActorScriptCmd*)scriptAddr;
    int time;
    int repeats;
    int fromLoop;
    int start;
    int loop;
    int idx;
    int end;
    time = 0;
    repeats = time;
    fromLoop = time;
    while (cmd->op_0 != 0)
    {
        if (cmd->op_0 == 1)
        {
            idx = cmd->arg_6;
            if (fromLoop == 0)
            {
                start = o->anims_148[idx].start_2;
            }
            else
            {
                start = o->anims_148[idx].loop_4;
            }
            loop = o->anims_148[idx].loop_4;
            end = o->anims_148[idx].end_6;
            if (target != -1 && target < 0x4000 && o->anims_148[target].id_0 == o->anims_148[idx].id_0 && end >= frame)
            {
                return ((time + frame - start) << 12) / o->frameSpeed_1E;
            }
            if (start == loop)
            {
                time += (end - start + 1) * (repeats + 1);
            }
            else
            {
                time += (end - loop + 1) * (repeats + 1);
                time += loop - start;
            }
            time--;
            fromLoop = 0;
        }
        else if (cmd->op_0 == 0x14)
        {
            if (target >= 0x4000 && target == cmd->arg_6)
            {
                return (time << 12) / o->frameSpeed_1E;
            }
        }
        else if (cmd->op_0 == 0xF)
        {
            time = 0;
        }
        else if (cmd->op_0 == 2)
        {
            fromLoop = 1;
        }
        else if (cmd->op_0 == 4)
        {
            repeats = cmd->arg_6 - 1;
        }
        else if (cmd->op_0 == 5)
        {
            repeats = o->loopCount_F4 - 1;
        }
        else if (cmd->op_0 == 0x17)
        {
            time += cmd->arg_6;
        }
        else if (cmd->op_0 == 0 || cmd->op_0 == 0x10)
        {
            if (target != -1 && target < 0x4000 && o->anims_148[target].end_6 < frame)
            {
                time += frame - o->anims_148[target].end_6;
            }
            return (time << 12) / o->frameSpeed_1E;
        }
        cmd = (ActorScriptCmd*)((unsigned int*)cmd + cmd->len_1);
    }
    return -1;
}
// Matched
short GetActorHitTimes_8001F268(Actor* o, HitTimes* out, ActorScriptCmd* script, int anim)
{
    short* e = o->anims_148[anim].hitFrames_8[0];
    int i;
    for (i = 0; i < 10; i++)
    {
        if (e[i * 2] < 0 && e[i * 2 + 1] < 0)
        {
            out[i].start_0 = -1;
            out[i].end_2 = -1;
        }
        else
        {
            out[i].start_0 = GetActorScriptTime_8001F03C((int)o, (int)script, anim, e[i * 2]);
            out[i].end_2 = GetActorScriptTime_8001F03C((int)o, (int)script, anim, e[i * 2 + 1]);
        }
    }
    return out[0].start_0;
}
extern void GetAnimRootMotion_8004D288(int* out, ModelAnim* s, int k);
extern int CollideWithMap_800B716C(VECTOR* pos, VECTOR* prev, SVECTOR* rot, void* a3);
// Matched
void UpdateActorMotion_8001F354(void* actor)
{
    Actor* o = actor;
    int prevDelta[3];
    ModelAnim* anim;
    int dx;
    int dz;
    int v;
    SVECTOR* boneScale;
    int* baseScale;
    short c;
    int sin;
    short a;
    anim = &o->model_15C->anims_54[o->anim_9C];
    o->prevPos_44[0] = o->pos_38[0];
    o->prevPos_44[1] = o->pos_38[1];
    o->prevPos_44[2] = o->pos_38[2];
    prevDelta[0] = o->animDelta_64[0];
    prevDelta[1] = o->animDelta_64[1];
    prevDelta[2] = o->animDelta_64[2];
    GetAnimRootMotion_8004D288(o->animDelta_64, anim, o->frame_90 % anim->frameCount_0);
    if (o->frame_90 % anim->frameCount_0 == 0 || (o->flags_4 & 8))
    {
        o->flags_4 &= ~8;
        if (o->flags_4 & 0x40000)
        {
            dx = 0;
            dz = 0;
        }
        else
        {
            dx = o->animDelta_64[0];
            dz = o->animDelta_64[2];
        }
    }
    else if (o->flags_4 & 0x40000)
    {
        dx = o->animDelta_64[0] - prevDelta[0];
        dz = o->animDelta_64[2] - prevDelta[2];
    }
    else
    {
        dx = o->animDelta_64[0];
        dz = o->animDelta_64[2];
    }
    if (dx < 0)
    {
        dx = 0;
    }
    if (dz < 0)
    {
        dz = 0;
    }
    if (o->flags_4 & 0x20000000)
    {
        dx = dx * o->speedScale_8C / 4096;
        dz = dz * o->speedScale_8C / 4096;
    }
    boneScale = o->boneScale_144;
    baseScale = o->baseScale_138;
    if (o->flags_4 & 0x4000000)
    {
        if (TurnActorTowards_8001DDFC(o, &o->target_70, o->target_70.pad))
        {
            o->flags_4 &= ~0x4000000;
        }
    }
    if (o->flags_4 & 0x2000000)
    {
        o->animDelta_64[0] = o->path_160->steps_8[o->pathStep_98][0];
        o->animDelta_64[1] = o->path_160->steps_8[o->pathStep_98][1];
        o->animDelta_64[2] = o->path_160->steps_8[o->pathStep_98][2];
        o->pos_38[0] = o->basePos_50[0] + o->animDelta_64[0] / o->path_160->divisor_4;
        o->pos_38[1] = o->basePos_50[1] + o->animDelta_64[1] / o->path_160->divisor_4;
        o->pos_38[2] = o->basePos_50[2] + o->animDelta_64[2] / o->path_160->divisor_4;
        o->rot_5C[1] = o->path_160->steps_8[o->pathStep_98][3];
    }
    else if (o->flags_4 & 0x1000000)
    {
        a = o->rot_5C[1];
        sin = (battleCamSpline1Tail_80084350 + 0xF8)[a & 0xFFF];
        c = (battleCamSpline1Tail_80084350 + 0xF8)[(a + 0x400) & 0xFFF];
        o->pos_38[2] = o->basePos_50[2] + (o->animDelta_64[2] * c - o->animDelta_64[0] * sin) / 4096 / anim->divisor_8;
        o->pos_38[0] = o->basePos_50[0] + (o->animDelta_64[2] * sin + o->animDelta_64[0] * c) / 4096 / anim->divisor_8;
        o->pos_38[1] = o->basePos_50[1] + o->animDelta_64[1] / anim->divisor_8;
    }
    else if (o->flags_4 & 0x40000)
    {
        o->pos_38[0] += dz * (battleCamSpline1Tail_80084350 + 0xF8)[o->rot_5C[1] & 0xFFF] / 4096 * boneScale->vz / 4096 * baseScale[2] / 4096 / anim->divisor_8;
        o->pos_38[2] += dz * (battleCamSpline1Tail_80084350 + 0xF8)[(o->rot_5C[1] + 0x400) & 0xFFF] / 4096 * boneScale->vz / 4096 * baseScale[2] / 4096 / anim->divisor_8;
    }
    else
    {
        o->pos_38[0] = o->basePos_50[0] + dz * (battleCamSpline1Tail_80084350 + 0xF8)[o->rot_5C[1] & 0xFFF] / 4096 / anim->divisor_8;
        o->pos_38[2] = o->basePos_50[2] + dz * (battleCamSpline1Tail_80084350 + 0xF8)[(o->rot_5C[1] + 0x400) & 0xFFF] / 4096 / anim->divisor_8;
    }
    if (o->flags_4 & 0x40000)
    {
        o->prevGround_84 = o->ground_80;
        o->ground_80 = CollideWithMap_800B716C((VECTOR*)o->pos_38, (VECTOR*)o->prevPos_44, (SVECTOR*)o->rot_5C, &o->fB4);
    }
}
// Matched
void UpdateActorAnimLoad_8001F918(void* actor)
{
    Actor* act = actor;
    switch (act->animLoadState_10)
    {
    case 0:
        break;
    case 1:
        RequestModelAnim_8002032C(act->modelRef_16, act->task_0->index_4, act->animRequest_12);
        *(unsigned short*)&act->animLoading_14 = *(unsigned short*)&act->animRequest_12;
        act->animRequest_12 = -1;
        act->animLoadState_10 = 2;
        break;
    case 2:
        if (AreFileRequestsDone_80024DC4(act->model_15C))
        {
            act->animLoadState_10 = 0;
        }
        break;
    }
}
// Matched
void UpdateActor_8001F9AC(void* actor)
{
    UpdateActorScale_8001F9F0(actor);
    UpdateActorDrawMode_8001FB00(actor);
    DrawActor_8001FD08(actor);
    AdvanceActorFrame_8001FF48(actor);
    CopyActorBoneMatrices_800200F8(actor);
}
// Matched
void UpdateActorScale_8001F9F0(Actor* o)
{
    unsigned int f = o->flags_4;
    if (f & 1)
    {
        if (f & 2)
        {
            o->scale_26 += o->scaleStep_28;
            if (o->scaleTarget_2A < o->scale_26)
            {
                o->scale_26 = o->scaleTarget_2A;
                o->flags_4 &= ~3;
            }
        }
        else
        {
            o->scale_26 -= o->scaleStep_28;
            if (o->scale_26 < o->scaleTarget_2A)
            {
                o->scale_26 = o->scaleTarget_2A;
                o->flags_4 &= ~1;
            }
        }
    }
    o->scale_2C[0] = o->baseScale_138[0] * o->scale_26 / 4096;
    o->scale_2C[1] = o->baseScale_138[1] * o->scale_26 / 4096;
    o->scale_2C[2] = o->baseScale_138[2] * o->scale_26 / 4096;
}
// Matched
void UpdateActorDrawMode_8001FB00(Actor* o)
{
    unsigned int flags = o->flags_4;
    int mode = 0;
    int value;
    int fade;
    o->drawMode_8 = 0;
    if (flags & 0x780)
    {
        if (flags & 0x80)
        {
            mode = 0x10;
        }
        else if (flags & 0x100)
        {
            mode = 0x30;
        }
        else if (flags & 0x200)
        {
            mode = 0x50;
        }
        else if (flags & 0x400)
        {
            mode = 0x70;
        }
    }
    if (o->flags_4 & 0x40000000)
    {
        value = (battleCamSpline1Tail_80084350 + 0xF8)[(o->pulse_BC * o->pulseRate_BE + 0x400) & 0xFFF];
        (o->pulse_BC)++;
        o->drawMode_8 = mode | 0x80 | (-((value + 0x1000) / 2) << 16);
    }
    if (o->flags_4 & 0x60)
    {
        value = o->fade_20 + 0x1000 / o->fadeDiv_22;
        if (value >= 0)
        {
            fade = value;
            if (value > 0x1000)
            {
                fade = 0x1000;
            }
        }
        else
        {
            fade = 0;
        }
        o->fade_20 = fade;
        if (o->flags_4 & 0x20)
        {
            o->drawMode_8 = mode | 0x80 | ((0x1000 - o->fade_20) << 16);
        }
        else
        {
            o->drawMode_8 = mode | 0x80 | (o->fade_20 << 16);
        }
    }
    if (o->flags_4 & 0x800)
    {
        o->drawMode_8 |= (o->clut_158[1] - o->image_150.y) << 8;
    }
}
// Matched
int IsActorOnScreen_8001FC90(Actor* actor)
{
    SVECTOR rel;
    long sxy;
    long z;
    long flag;
    rel.vx = *(unsigned short*)&actor->pos_38[0];
    rel.vy = *(unsigned short*)&actor->pos_38[1];
    rel.vz = *(unsigned short*)&actor->pos_38[2];
    rel.vx -= cameraEye_8008D600.vx;
    rel.vy -= cameraEye_8008D600.vy;
    rel.vz -= cameraEye_8008D600.vz;
    RotTransPers(&rel, &sxy, &z, &flag);
    return flag >= 0;
}
extern void DrawAnimSkelBlend_80047E28();
extern void DrawAnimSkel_80046A58();
extern void DrawSpriteVtxQuadsGT4_800459E4();
// Matched
void DrawActor_8001FD08(void* actor)
{
    Actor* o = (Actor*)actor;
    int light;
    ModelAnim* altPose;
    unsigned long* ot;
    unsigned long* ot2;
    if (!(o->flags_4 & 0x2000) && IsActorOnScreen_8001FC90(o))
    {
        light = FindNearestCameraPoint_80019CC4(o->pos_38);
        o->draw_164.anim_14 = &o->model_15C->anims_54[o->anim_9C];
        o->draw_164.ftg_0 = o->model_15C->ftg_50;
        o->draw_164.pos_4 = o->pos_38;
        o->draw_164.rot_8 = o->rot_5C;
        o->draw_164.bones_C = o->bones_134;
        o->draw_164.boneScale_10 = o->boneScale_144;
        o->draw_164.frame_18 = o->frame_90 % o->draw_164.anim_14->frameCount_0;
        o->draw_164.drawMode_1C = o->drawMode_8;
        o->draw_164.scale_24 = o->scale_2C;
        o->draw_164.bonePos_20 = o->bonePos_1C4;
        if (unknownFlags_8008D678 & 0x10000)
        {
            ot = pOT_8008B4C8;
        }
        else
        {
            ot = pOT_8008D690;
        }
        o->draw_164.ot_28 = ot;
        if (o->flags_4 & 0x1000)
        {
            altPose = o->model_15C->anims_54;
        }
        else
        {
            altPose = 0;
        }
        if (o->flags_4 & 0x10)
        {
            DrawAnimSkelBlend_80047E28(&o->draw_164, o->draw_164.boneScale_10, &o->model_15C->anims_54[o->prevAnim_A0],
                         o->prevFrame_94 % o->model_15C->anims_54[o->prevAnim_A0].frameCount_0,
                         0x1000 - o->blend_AC, &pointLights_8008D534[light], altPose);
        }
        else
        {
            DrawAnimSkel_80046A58(&o->draw_164, &pointLights_8008D534[light], altPose);
        }
        if (unknownFlags_8008D678 & 0x10000)
        {
            ot2 = pOT_8008B4C8;
        }
        else
        {
            ot2 = pOT_8008D690;
        }
        DrawSpriteVtxQuadsGT4_800459E4(o->bones_134, &o->model_15C->mats_5C, ot2, o->drawMode_8);
        RunAnimFrameCues_8001C440(o->model_15C, o->anim_9C, o->frame_90 % o->draw_164.anim_14->frameCount_0);
    }
}
// Matched
void AdvanceActorFrame_8001FF48(Actor* o)
{
    int g;
    int f;
    o->flags_4 &= ~0x4000;
    if (!(o->flags_4 & 4))
    {
        o->frameFrac_1C += o->frameSpeed_1E;
        if (o->frameFrac_1C >= 0x1000)
        {
            o->frameFrac_1C -= 0x1000;
            (o->frame_90)++;
        }
        if (o->frame_90 == o->endFrame_1A)
        {
            o->flags_4 |= 0x4000;
        }
        else if (o->endFrame_1A < o->frame_90)
        {
            o->flags_4 |= 8;
            o->frame_90 = o->loopFrame_18;
        }
    }
    f = o->flags_4;
    if (f & 0x10)
    {
        if (f < 0)
        {
            o->blend_AC += 0x111;
        }
        else
        {
            o->blend_AC += 0x1000 / o->blendDiv_24;
        }
        if (o->blend_AC >= 0x1000)
        {
            g = o->flags_4 & ~0x10;
            o->flags_4 = g & 0x7FFFFFFF;
        }
        f = o->flags_4;
    }
    if (f & 0x2000000)
    {
        o->flags_4 = f & ~0x4000;
        if (++o->pathStep_98 >= **(int**)&o->path_160)
        {
            o->frame_90 = o->endFrame_1A;
            o->flags_4 = (o->flags_4 & ~0x2000000) | 0x4008;
            o->basePos_50[0] = o->pos_38[0];
            o->basePos_50[1] = o->pos_38[1];
            o->basePos_50[2] = o->pos_38[2];
            if (o->flags_D4 & 4)
            {
                o->flags_4 |= 0x80000000;
                o->flags_D4 &= ~1;
            }
        }
    }
}
// Matched
void CopyActorBoneMatrices_800200F8(void* actor)
{
    Actor* o = actor;
    int i;
    if (o->flags_4 & 0x10000000)
    {
        if (o->bones_134[0] != -1)
        {
            i = 0;
            do
            {
                o->boneMatrices_1C8[i] = boneMatrices_80098188[i];
                i++;
            } while (o->bones_134[i * 4] != -1);
        }
    }
}
// Matched
void ClearModelAnimRefs_800201A4(void)
{
    int i;
    for (i = 0; i < 7; i++)
    {
        ClearModelAnimRef_800204AC(&modelAnimRefs_800919A0[i]);
    }
}
// Matched
int AddModelAnimRef_800201EC(Model* model)
{
    int i;
    ModelAnimRef* ref = modelAnimRefs_800919A0;
    for (i = 0; i < 7; i++, ref++)
    {
        if (model == ref->model_0)
        {
            ref->refs_4++;
            return i;
        }
    }
    ref = modelAnimRefs_800919A0;
    for (i = 0; i < 7; i++, ref++)
    {
        if (ref->model_0 == 0)
        {
            ref->model_0 = model;
            ref->refs_4 = 1;
            return i;
        }
    }
    return -1;
}
// Matched
void ReleaseModelAnimRef_80020278(int ref, int user)
{
    int i;
    ModelAnimRef* e = &modelAnimRefs_800919A0[ref];
    for (i = 0; i < 0x23; i++)
    {
        if ((e->users_8[i] >> user) & 1)
        {
            ReleaseModelAnim_800203B0(ref, user, i);
        }
    }
    if (--e->refs_4 == 0)
    {
        ClearModelAnimRef_800204AC(e);
    }
}
// Matched
int RequestModelAnim_8002032C(int ref, int user, int anim)
{
    ModelAnimRef* e = &modelAnimRefs_800919A0[ref];
    int loaded = 0;
    if (e->users_8[anim] == 0)
    {
        LoadModelAnim_80025440(e->model_0, anim, loaded);
        loaded = 1;
    }
    e->users_8[anim] |= 1 << user;
    return loaded;
}
// Matched
void ReleaseModelAnim_800203B0(int ref, int user, int anim)
{
    ModelAnimRef* e = &modelAnimRefs_800919A0[ref];
    if ((e->users_8[anim] &= ~(1 << user)) == 0)
    {
        FreeModelAnim_8002556C(e->model_0, anim);
    }
}
// Matched
int IsModelAnimUsed_80020410(int ref, int user, int anim)
{
    ModelAnimRef* e = &modelAnimRefs_800919A0[ref];
    int* list;
    int i;
    if (((e->users_8[anim] >> user) & 1) == 0)
    {
        list = e->model_0->animSet_58;
        if (list != 0)
        {
            for (i = 0; i < list[0]; i++)
            {
                if (anim == list[i + 1])
                {
                    return 1;
                }
            }
        }
        return 0;
    }
    return 1;
}
// Matched
void ClearModelAnimRef_800204AC(ModelAnimRef* ref)
{
    int i;
    for (i = 0x22; i >= 0; i--)
    {
        ref->users_8[i] = 0;
    }
    ref->model_0 = 0;
    ref->refs_4 = 0;
}
// Matched
void ResetModelLoader_800204D0(void)
{
    ModelLoader* loader = modelLoaderTask_8008B54C->entry.buffer;
    ModelLoadSlot* slot = loader->slots_C;
    int i;
    loader->state_0 = 0;
    loader->done_4 = 1;
    loader->models_8 = 0;
    for (i = 0; i < 4; i++)
    {
        slot->loaded_0 = 0;
        slot->id_4 = -1;
        slot->sel_8 = 0;
        slot->arg_C = 0;
        slot->animSet_10 = -1;
        slot++;
    }
}
// Matched
void FreeModelLoaderList_8002052C(void)
{
    ModelLoader* loader = modelLoaderTask_8008B54C->entry.buffer;
    if (loader->models_8)
    {
        FreeModelList_80024BB0(&loader->models_8);
    }
}
// Matched
void StartModelLoader_8002056C(void)
{
    EventEntry* entry = &modelLoaderTask_8008B54C->entry;
    entry->cb_8 = (EventEntryFn)ModelLoaderTask_800209AC;
    entry->flags = (entry->flags | 1) & ~0x8000;
    ((ModelLoader*)entry->buffer)->state_0 = 0;
    entry->cb_8(entry, entry->buffer);
}
// Matched
int IsModelLoaderDone_800205D0(void)
{
    return ((ModelLoader*)modelLoaderTask_8008B54C->entry.buffer)->done_4;
}
// Matched
void StopModelLoader_800205F0(void)
{
    EventEntry* entry = &modelLoaderTask_8008B54C->entry;
    entry->flags = (entry->flags & ~1) | 0x8000;
}
// Matched
int CountLoaderModels_80020614(void)
{
    ModelLoader* loader = modelLoaderTask_8008B54C->entry.buffer;
    ModelLoadSlot* slot = loader->slots_C;
    int count = 0;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (slot->id_4 >= 0)
        {
            count++;
        }
        slot++;
    }
    return count;
}
// Matched
int GetLoaderModelId_80020654(int nth)
{
    ModelLoader* loader = modelLoaderTask_8008B54C->entry.buffer;
    ModelLoadSlot* slot = loader->slots_C;
    int count = 0;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (slot->id_4 >= 0)
        {
            if (count == nth)
            {
                return slot->id_4;
            }
            count++;
        }
        slot++;
    }
    return -1;
}
// Matched
int RequestLoaderModel_800206A0(int id, int sel, int animMode, int animSet)
{
    ModelLoader* loader = modelLoaderTask_8008B54C->entry.buffer;
    ModelLoadSlot* slot = loader->slots_C;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (id == slot->id_4)
        {
            return 1;
        }
        slot++;
    }
    slot = loader->slots_C;
    for (i = 0; i < 4; i++)
    {
        if (slot->id_4 == -1)
        {
            slot->loaded_0 = 0;
            slot->id_4 = id;
            slot->sel_8 = sel;
            slot->arg_C = animMode;
            slot->animSet_10 = animSet;
            loader->done_4 = 0;
            return 1;
        }
        slot++;
    }
    return 0;
}
// Matched
Model* AcquireLoaderModel_80020734(int arg)
{
    return AcquireModel_80024D70(((ModelLoader*)modelLoaderTask_8008B54C->entry.buffer)->models_8, arg);
}
// Matched
void FreeLoaderModel_80020768(Model* model)
{
    ModelLoader* base = modelLoaderTask_8008B54C->entry.buffer;
    ModelLoadSlot* slot = base->slots_C;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (slot->id_4 >= 0 && slot->animSet_10 >= 0)
        {
            if (model == AcquireModel_80024D70(base->models_8, slot->id_4))
            {
                FreeModel_80024C48(model);
                slot->id_4 = -1;
                return;
            }
        }
        slot++;
    }
}
// Matched
void FreeLoaderModelAnimSets_80020814(void)
{
    ModelLoader* base = modelLoaderTask_8008B54C->entry.buffer;
    ModelLoadSlot* slot = base->slots_C;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (slot->id_4 >= 0 && slot->animSet_10 >= 0)
        {
            FreeModelAnimSet_80025884(AcquireModel_80024D70(base->models_8, slot->id_4));
        }
        slot++;
    }
}
// Matched
void LoadLoaderModelAnimSets_80020898(void)
{
    ModelLoader* base = modelLoaderTask_8008B54C->entry.buffer;
    ModelLoadSlot* slot = base->slots_C;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (slot->id_4 >= 0 && slot->animSet_10 >= 0)
        {
            LoadModelAnimSet_80025780(AcquireModel_80024D70(base->models_8, slot->id_4), slot->animSet_10, 1);
        }
        slot++;
    }
}
// Matched
int AreLoaderModelsLoaded_80020924(void)
{
    ModelLoader* base = modelLoaderTask_8008B54C->entry.buffer;
    ModelLoadSlot* slot = base->slots_C;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (slot->id_4 >= 0)
        {
            if (AreFileRequestsDone_80024DC4(AcquireModel_80024D70(base->models_8, slot->id_4)) == 0)
            {
                return 0;
            }
        }
        slot++;
    }
    return 1;
}
// Matched
void ModelLoaderTask_800209AC(EventEntry* entry, int* buf)
{
    ModelLoader* loader = (ModelLoader*)buf;
    int state = loader->state_0;
    int next;
    switch (state)
    {
    case 0:
        LoadRequestedModels_80020A38(loader);
        next = loader->state_0;
        eventDispatchHalt_8008B540 = 1;
        loader->state_0 = next + 1;
        break;
    case 1:
        if (AreRequestedModelsLoaded_80020B70(loader))
        {
            StopModelLoader_800205F0();
        }
        eventDispatchHalt_8008B540 = state;
        break;
    }
}
// Matched
void LoadRequestedModels_80020A38(ModelLoader* loader)
{
    ModelLoadSlot* slot;
    int i;
    if (loader->models_8 == 0)
    {
        InitModelList_80024ADC(&loader->models_8, modelLoaderVram_8007DC70, 1);
    }
    slot = loader->slots_C;
    for (i = 0; i < 4; i++)
    {
        if (slot->id_4 >= 0 && slot->loaded_0 == 0)
        {
            LoadModel_80025200(loader->models_8, slot->id_4, slot->sel_8, slot->arg_C, 1);
        }
        slot++;
    }
    slot = loader->slots_C;
    for (i = 0; i < 4; i++)
    {
        if (slot->id_4 >= 0 && slot->loaded_0 == 0)
        {
            if (slot->animSet_10 >= 0)
            {
                LoadModelAnimSet_80025780(AcquireModel_80024D70(loader->models_8, slot->id_4), slot->animSet_10, 1);
            }
            slot->loaded_0 = 1;
        }
        slot++;
    }
}
// Matched
int AreRequestedModelsLoaded_80020B70(ModelLoader* loader)
{
    ModelLoadSlot* slot = loader->slots_C;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (slot->loaded_0 != 0)
        {
            if (AreFileRequestsDone_80024DC4(AcquireModel_80024D70(loader->models_8, slot->id_4)) == 0)
            {
                return 0;
            }
        }
        slot++;
    }
    loader->done_4 = 1;
    return 1;
}
// Matched
int LoadOverlay_80020BF8(unsigned int mode, enum OverlayIds overlayIdx)
{
    FileRequestDesc req;
    switch (mode)
    {
    case 0:
        req.flags_0 = 0x22;
        break;
    case 2:
        DATA_ReadFileInto_8003CAEC(overlays_8007D9E8[overlayIdx].fileIdx, *overlays_8007D9E8[overlayIdx].ppDest);
        return -1;
    case 1:
    case 3:
        req.flags_0 = 0x2A;
        break;
    }
    req.fileId_4 = overlays_8007D9E8[overlayIdx].fileIdx;
    req.offset_8 = 0;
    req.size_C = 0;
    req.dest_10 = *overlays_8007D9E8[overlayIdx].ppDest;
    req.params_14 = 0;
    req.paramsSize_18 = 0;
    req.callback_1C = 0;
    return QueueFileRequest_8003BC84(&req);
}
// Matched
void InitOverlayLoaderTask_80020CB8(EventEntry* entry, OverlayLoader* loader)
{
    loader->loaded_4 = -1;
    loader->wanted_0 = 0x1D;
    entry->cb_8 = (EventEntryFn)UpdateOverlayLoaderTask_80020CD8;
}
// Matched
void UpdateOverlayLoaderTask_80020CD8(int entry, OverlayLoader* loader)
{
    if (loader->wanted_0 != loader->loaded_4)
    {
        loader->loaded_4 = loader->wanted_0;
        loader->request_8 = LoadOverlay_80020BF8(2, loader->wanted_0);
    }
}
// Matched
int LoadOverlayIfChanged_80020D1C(int mode, int overlay)
{
    OverlayLoader* loader = overlayLoaderTask_8008D4C0->entry.buffer;
    if (loader->wanted_0 == overlay)
    {
        return -1;
    }
    loader->wanted_0 = overlay;
    loader->loaded_4 = overlay;
    return LoadOverlay_80020BF8(mode, loader->wanted_0);
}
// Matched
void ResetOverlayLoaderTask_80020D68(void)
{
    ((OverlayLoader*)overlayLoaderTask_8008D4C0->entry.buffer)->wanted_0 = 0x1D;
}
// Matched
int IsOverlayLoaderIdle_80020D84(void)
{
    OverlayLoader* loader = overlayLoaderTask_8008D4C0->entry.buffer;
    int idle;
    if (loader->wanted_0 == 0x1D)
    {
        idle = GetFileRequestStatus_8003BE30(loader->request_8) == 0;
    }
    else
    {
        ResetOverlayLoaderTask_80020D68();
        idle = 0;
    }
    return idle;
}
// Matched
void LoadEffectFile_80020DDC(int fileId, EffectFile* out, short* tpagePos, short* clutPos, int sel, int flag)
{
    FileRequestDesc req;
    EffectLoadArg arg;
    arg.out_0 = out;
    arg.reloc_4[0] = tpagePos[0];
    arg.reloc_4[1] = tpagePos[1];
    arg.reloc_4[2] = clutPos[0];
    arg.reloc_4[3] = clutPos[1];
    arg.reloc_4[4] = clutPos[0];
    arg.reloc_4[5] = clutPos[1];
    arg.sel_10 = sel;
    ListInit_8003FDB0(&out->list_4);
    req.flags_0 = 0x28;
    if (flag)
    {
        req.flags_0 |= 4;
    }
    else
    {
        req.flags_0 |= 1;
    }
    req.fileId_4 = fileId;
    req.offset_8 = 0;
    req.size_C = 0;
    req.dest_10 = 0;
    req.params_14 = &arg;
    req.paramsSize_18 = 0x14;
    req.callback_1C = OnEffectFileLoaded_80020F5C;
    out->request_0 = StartFileRequestTask_8003C6C8(&req);
}
// Matched
int IsEffectFileLoaded_80020EBC(EffectFile* file)
{
    return GetFileRequestStatus_8003BE30(file->request_0) == 0;
}
// Matched
void FreeEffectFile_80020EE0(EffectFile* file)
{
    ListFreeAll_8003FEC8(&file->list_4);
}
// Matched
int FindEffectIndex_80020F00(EffectFile* file, int kind, int id)
{
    int i;
    for (i = 0; i < file->pointCount_14; i++)
    {
        if (file->points_18[i].kind == kind && file->points_18[i].id == id)
        {
            return file->points_18[i].index;
        }
    }
    return -1;
}
// Matched
void OnEffectFileLoaded_80020F5C(EffectLoadArg* arg_in, int* hdr)
{
    EffectLoadArg* arg = arg_in;
    EffectFile* out = arg->out_0;
    int* dataSec = (int*)((char*)hdr + hdr[1]);
    int* pointSec = (int*)((char*)hdr + hdr[2]);
    int* spriteSec = (int*)((char*)hdr + hdr[3]);
    int* modelSec = (int*)((char*)hdr + hdr[4]);
    int* imageSec = (int*)((char*)hdr + hdr[5]);
    int* tiySec = (int*)((char*)hdr + hdr[6]);
    int i;
    int max;
    int bufSize;
    int count;
    int* src;
    out->pointCount_14 = 0;
    out->spriteCount_1C = 0;
    out->modelCount_24 = 0;
    out->imageSetCount_2C = 0;
    out->data_10 = ListAlloc_8003FDC0(&out->list_4, dataSec[0]);
    MemCopy_800403E8(out->data_10, dataSec + 1, dataSec[0]);
    count = pointSec[0];
    if (count)
    {
        out->pointCount_14 = count;
        out->points_18 = ListAlloc_8003FDC0(&out->list_4, count * 12);
        src = pointSec + 1;
        for (i = 0; i < out->pointCount_14; i++)
        {
            out->points_18[i].kind = src[0];
            out->points_18[i].id = src[1];
            out->points_18[i].index = src[2];
            src += 3;
        }
    }
    count = spriteSec[0];
    if (count)
    {
        out->spriteCount_1C = count;
        out->sprites_20 = ListAlloc_8003FDC0(&out->list_4, count * 0x34);
        for (i = 0; i < out->spriteCount_1C; i++)
        {
            EffectSprite* d = &out->sprites_20[i];
            LoadEffectSprite_80021298((int*)((char*)spriteSec + spriteSec[i + 1]), d, (int)arg->reloc_4, arg->sel_10, &out->list_4);
        }
    }
    count = modelSec[0];
    if (count)
    {
        out->modelCount_24 = count;
        out->models_28 = ListAlloc_8003FDC0(&out->list_4, count * 0x1C);
        for (i = 0; i < out->modelCount_24; i++)
        {
            EffectModel* d = &out->models_28[i];
            LoadEffectModel_80021464((int*)((char*)modelSec + modelSec[i + 1]), d, (int)arg->reloc_4, arg->sel_10, &out->list_4);
        }
    }
    count = imageSec[0];
    if (count)
    {
        out->imageSetCount_2C = count;
        out->imageSets_30 = ListAlloc_8003FDC0(&out->list_4, count * 8);
        i = 0;
        max = i;
        for (; i < out->imageSetCount_2C; i++)
        {
            bufSize = LoadMdecImages_800215E8((int*)((char*)imageSec + imageSec[i + 1]), &out->imageSets_30[i], &out->list_4);
            if (max < bufSize)
            {
                max = bufSize;
            }
        }
        AllocMdecBuffers_800216E8(&out->mdec_34, max, &out->list_4);
    }
    if (GetTiyFileCount_80028E68(tiySec))
    {
        LoadTiyTimsRelocated_80028FDC(0, 0, 0, (int)tiySec, GetTiyFileCount_80028E68(tiySec), (int)arg->reloc_4, arg->sel_10);
    }
}
// Matched
void LoadEffectSprite_80021298(int* src, EffectSprite* out, int reloc, int sel, List* heap)
{
    POLY_FT4 buf;
    int i;
    int j;
    int count;
    EffectSpriteFrameBytes* dst;
    EffectSpriteFrameBytes* cur;
    out->count_0 = *src++;
    out->frameCounts_4 = ListAlloc_8003FDC0(heap, out->count_0);
    out->frames_8 = ListAlloc_8003FDC0(heap, out->count_0 * 4);
    for (i = 0; i < out->count_0; i++)
    {
        count = *src++;
        cur = (EffectSpriteFrameBytes*)src;
        dst = ListAlloc_8003FDC0(heap, count * 28);
        out->frameCounts_4[i] = count;
        out->frames_8[i] = (EffectSpriteFrame*)dst;
        for (j = 0; j < out->frameCounts_4[i]; j++)
        {
            dst->texPos_0 = cur->texPos_0;
            dst->texSize_4 = cur->texSize_4;
            dst->pivot_8 = cur->pivot_8;
            dst->size_C = cur->size_C;
            dst->pos_10 = cur->pos_10;
            dst->rgb_18 = cur->rgb_18;
            dst++;
            cur++;
        }
        src = (int*)cur;
    }
    MemCopy_800403E8(&buf, src, 0x28);
    InitPolyFT4_80029A10(&out->poly_C, &buf);
}
// Matched
void LoadEffectModel_80021464(int* hdr, EffectModel* out, int reloc, int sel, List* heap)
{
    int* models = (int*)((char*)hdr + hdr[1]);
    int* images = (int*)((char*)hdr + hdr[2]);
    if (GetFtgObjectCount_80021738(models))
    {
        out->ftgCount_0 = GetFtgObjectCount_80021738(models);
        AllocFtgObjects_80021744(&out->ftg_4, out->ftgCount_0, (int)heap);
        LoadFtgObjects_80021824(models, out->ftg_4, out->ftgCount_0, (int)heap, reloc);
    }
    if (GetFtgMatCount_80021DE4(models))
    {
        AllocFtgMatList_80021DF0(&out->mats_8, GetFtgMatCount_80021DE4(models), (int)heap);
        LoadFtgMatList_80021E4C(models, &out->mats_8, GetFtgMatCount_80021DE4(models));
    }
    else
    {
        out->mats_8.count_0 = 0;
    }
    out->keyCount_10 = 0;
    out->frameCount_14 = 0;
    out->keys_18 = 0;
    if (images[0] && images[1])
    {
        out->keyCount_10 = images[0];
        out->frameCount_14 = images[1];
        out->keys_18 = ListAlloc_8003FDC0(heap, images[0] * 40 * images[1]);
        MemCopy_800403E8(out->keys_18, images + 2, images[0] * 40 * images[1]);
    }
}
// Matched
int LoadMdecImages_800215E8(int* hdr, MdecImageSet* out, List* heap)
{
    int i;
    int max;
    int size;
    unsigned long* src;
    int bufSize;
    int count = hdr[0];
    out->count_0 = count;
    out->images_4 = ListAlloc_8003FDC0(heap, count * 4);
    i = 0;
    max = i;
    for (; i < out->count_0; i++)
    {
        size = hdr[i * 2 + 2];
        src = (unsigned long*)((char*)hdr + hdr[i * 2 + 1]);
        out->images_4[i] = ListAlloc_8003FDC0(heap, size);
        MemCopy_800403E8(out->images_4[i], src, size);
        bufSize = DecDCTBufSize(src);
        if (max < bufSize)
        {
            max = bufSize;
        }
    }
    return max;
}
// Matched
void AllocMdecBuffers_800216E8(EffectMdecBuffers* out, int maxSize, List* heap)
{
    out->dct_0 = ListAlloc_8003FDC0(heap, (maxSize + 1) * 4);
    out->work_4 = ListAlloc_8003FDC0(heap, 0x2000);
}
