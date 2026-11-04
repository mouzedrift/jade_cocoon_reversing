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

extern short screenOffset_8008D474[2];
extern short battleCamSpline1Tail_80084350[]; // a short table (indexed & 0xFFF) starts at +0x1F0 (0x80084540)
extern int QueueFileRequest_8003BC84(FileRequestDesc* req);
extern int StartFileRequestTask_8003C6C8(FileRequestDesc* req);
void OnEffectFileLoaded_80020F5C(EffectLoadArg* arg_in, int* hdr);
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
    int n;
    int mode;
    int r;
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
            n = cmd->arg_6;
            if (o->animIdx_C2 != n)
            {
                SetActorAnimPaused_8001D6EC(o, 0);
                if (n == 0x4003)
                {
                    n = o->nextAnim_A4;
                    o->animIdx_C2 = o->nextAnim_A4;
                    o->nextAnim_A4 = o->queuedAnim_FE;
                    o->queuedAnim_FE = -1;
                }
                else
                {
                    o->animIdx_C2 = n;
                }
                mode = flag22 ? -2 : -1;
                if (o->startMode_A8 >= 0)
                {
                    mode = o->startMode_A8;
                    o->startMode_A8 = -1;
                }
                SetActorAnim_8001D760(o, n, mode, flag21);
            }
            done = 1;
            break;
        case 2:
            flag22 = 1;
            break;
        case 3:
            if (!(o->flags_4 & 0x2000000))
            {
                r = o->flags_D4;
                if (!(r & 1))
                {
                    flag21 = 1;
                }
                o->flags_D4 = r & ~1;
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
// the jump table of CountFtgSprites_80022B84 (asm; its targets are labels of the generated asm, gen_asm.jump_label):
// delete it and its externs in model.h when the function is C, the compiler emits it then
void* const dword_8007411C[10] = { jtgt_80022C34, jtgt_80022C2C, jtgt_80022C34, jtgt_80022C3C, jtgt_80022C4C, jtgt_80022C44, jtgt_80022C4C, jtgt_80022C54, jtgt_80022C5C, jtgt_80022C84 };
// Matched
void StopActorScript_8001EFC4(Actor* p)
{
    unsigned int f = p->flags_4;
    int n;
    if (f & 0x800000)
    {
        n = p->kind_C;
        if (n < 0)
        {
            if (f & 0x200000)
            {
                ClearScriptActorBusy_800A5BCC(n - 2);
            }
        }
        else if (n >= 3)
        {
            if (f & 0x200000)
            {
                ClearScriptActorBusy_800A5BCC(n - 2);
            }
        }
    }
    p->flags_4 &= 0xFF17FFFF;
}
// Matched
int GetActorScriptTime_8001F03C(int actorAddr, int scriptAddr, int target, int frame)
{
    Actor* o = (Actor*)actorAddr;
    ActorScriptCmd* s = (ActorScriptCmd*)scriptAddr;
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
    while (s->op_0 != 0)
    {
        if (s->op_0 == 1)
        {
            idx = s->arg_6;
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
        else if (s->op_0 == 0x14)
        {
            if (target >= 0x4000 && target == s->arg_6)
            {
                return (time << 12) / o->frameSpeed_1E;
            }
        }
        else if (s->op_0 == 0xF)
        {
            time = 0;
        }
        else if (s->op_0 == 2)
        {
            fromLoop = 1;
        }
        else if (s->op_0 == 4)
        {
            repeats = s->arg_6 - 1;
        }
        else if (s->op_0 == 5)
        {
            repeats = o->loopCount_F4 - 1;
        }
        else if (s->op_0 == 0x17)
        {
            time += s->arg_6;
        }
        else if (s->op_0 == 0 || s->op_0 == 0x10)
        {
            if (target != -1 && target < 0x4000 && o->anims_148[target].end_6 < frame)
            {
                time += frame - o->anims_148[target].end_6;
            }
            return (time << 12) / o->frameSpeed_1E;
        }
        s = (ActorScriptCmd*)((unsigned int*)s + s->len_1);
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
    ModelAnim* e;
    int dx;
    int dz;
    int v;
    SVECTOR* r;
    int* s;
    short c;
    int sin;
    short a;
    e = &o->model_15C->anims_54[o->anim_9C];
    o->prevPos_44[0] = o->pos_38[0];
    o->prevPos_44[1] = o->pos_38[1];
    o->prevPos_44[2] = o->pos_38[2];
    prevDelta[0] = o->animDelta_64[0];
    prevDelta[1] = o->animDelta_64[1];
    prevDelta[2] = o->animDelta_64[2];
    GetAnimRootMotion_8004D288(o->animDelta_64, e, o->frame_90 % e->frameCount_0);
    if (o->frame_90 % e->frameCount_0 == 0 || (o->flags_4 & 8))
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
    r = o->boneScale_144;
    s = o->baseScale_138;
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
        o->pos_38[2] = o->basePos_50[2] + (o->animDelta_64[2] * c - o->animDelta_64[0] * sin) / 4096 / e->divisor_8;
        o->pos_38[0] = o->basePos_50[0] + (o->animDelta_64[2] * sin + o->animDelta_64[0] * c) / 4096 / e->divisor_8;
        o->pos_38[1] = o->basePos_50[1] + o->animDelta_64[1] / e->divisor_8;
    }
    else if (o->flags_4 & 0x40000)
    {
        o->pos_38[0] += dz * (battleCamSpline1Tail_80084350 + 0xF8)[o->rot_5C[1] & 0xFFF] / 4096 * r->vz / 4096 * s[2] / 4096 / e->divisor_8;
        o->pos_38[2] += dz * (battleCamSpline1Tail_80084350 + 0xF8)[(o->rot_5C[1] + 0x400) & 0xFFF] / 4096 * r->vz / 4096 * s[2] / 4096 / e->divisor_8;
    }
    else
    {
        o->pos_38[0] = o->basePos_50[0] + dz * (battleCamSpline1Tail_80084350 + 0xF8)[o->rot_5C[1] & 0xFFF] / 4096 / e->divisor_8;
        o->pos_38[2] = o->basePos_50[2] + dz * (battleCamSpline1Tail_80084350 + 0xF8)[(o->rot_5C[1] + 0x400) & 0xFFF] / 4096 / e->divisor_8;
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
    Actor* p = actor;
    switch (p->animLoadState_10)
    {
    case 0:
        break;
    case 1:
        RequestModelAnim_8002032C(p->modelRef_16, p->task_0->index_4, p->animRequest_12);
        *(unsigned short*)&p->animLoading_14 = *(unsigned short*)&p->animRequest_12;
        p->animRequest_12 = -1;
        p->animLoadState_10 = 2;
        break;
    case 2:
        if (AreFileRequestsDone_80024DC4(p->model_15C))
        {
            p->animLoadState_10 = 0;
        }
        break;
    }
}
// Matched
void UpdateActor_8001F9AC(void* p)
{
    UpdateActorScale_8001F9F0(p);
    UpdateActorDrawMode_8001FB00(p);
    DrawActor_8001FD08(p);
    AdvanceActorFrame_8001FF48(p);
    CopyActorBoneMatrices_800200F8(p);
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
    unsigned int f = o->flags_4;
    int r = 0;
    int v;
    int w;
    o->drawMode_8 = 0;
    if (f & 0x780)
    {
        if (f & 0x80)
        {
            r = 0x10;
        }
        else if (f & 0x100)
        {
            r = 0x30;
        }
        else if (f & 0x200)
        {
            r = 0x50;
        }
        else if (f & 0x400)
        {
            r = 0x70;
        }
    }
    if (o->flags_4 & 0x40000000)
    {
        v = (battleCamSpline1Tail_80084350 + 0xF8)[(o->pulse_BC * o->pulseRate_BE + 0x400) & 0xFFF];
        (o->pulse_BC)++;
        o->drawMode_8 = r | 0x80 | (-((v + 0x1000) / 2) << 16);
    }
    if (o->flags_4 & 0x60)
    {
        v = o->fade_20 + 0x1000 / o->fadeDiv_22;
        if (v >= 0)
        {
            w = v;
            if (v > 0x1000)
            {
                w = 0x1000;
            }
        }
        else
        {
            w = 0;
        }
        o->fade_20 = w;
        if (o->flags_4 & 0x20)
        {
            o->drawMode_8 = r | 0x80 | ((0x1000 - o->fade_20) << 16);
        }
        else
        {
            o->drawMode_8 = r | 0x80 | (o->fade_20 << 16);
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
    SVECTOR v;
    long sxy;
    long p;
    long flag;
    v.vx = *(unsigned short*)&actor->pos_38[0];
    v.vy = *(unsigned short*)&actor->pos_38[1];
    v.vz = *(unsigned short*)&actor->pos_38[2];
    v.vx -= cameraEye_8008D600.vx;
    v.vy -= cameraEye_8008D600.vy;
    v.vz -= cameraEye_8008D600.vz;
    RotTransPers(&v, &sxy, &p, &flag);
    return flag >= 0;
}
extern int FindNearestCameraPoint_80019CC4();
extern void RunAnimFrameCues_8001C440();
extern void DrawAnimSkelBlend_80047E28();
extern void DrawAnimSkel_80046A58();
extern void DrawSpriteVtxQuadsGT4_800459E4();
// Matched
void DrawActor_8001FD08(void* actor)
{
    Actor* o = (Actor*)actor;
    int v;
    ModelAnim* t;
    unsigned long* ot;
    unsigned long* ot2;
    if (!(o->flags_4 & 0x2000) && IsActorOnScreen_8001FC90(o))
    {
        v = FindNearestCameraPoint_80019CC4(o->pos_38);
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
            t = o->model_15C->anims_54;
        }
        else
        {
            t = 0;
        }
        if (o->flags_4 & 0x10)
        {
            DrawAnimSkelBlend_80047E28(&o->draw_164, o->draw_164.boneScale_10, &o->model_15C->anims_54[o->prevAnim_A0],
                         o->prevFrame_94 % o->model_15C->anims_54[o->prevAnim_A0].frameCount_0,
                         0x1000 - o->blend_AC, &pointLights_8008D534[v], t);
        }
        else
        {
            DrawAnimSkel_80046A58(&o->draw_164, &pointLights_8008D534[v], t);
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
    ModelAnimRef* p = modelAnimRefs_800919A0;
    for (i = 0; i < 7; i++, p++)
    {
        if (model == p->model_0)
        {
            p->refs_4++;
            return i;
        }
    }
    p = modelAnimRefs_800919A0;
    for (i = 0; i < 7; i++, p++)
    {
        if (p->model_0 == 0)
        {
            p->model_0 = model;
            p->refs_4 = 1;
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
void ClearModelAnimRef_800204AC(ModelAnimRef* p)
{
    int i;
    for (i = 0x22; i >= 0; i--)
    {
        p->users_8[i] = 0;
    }
    p->model_0 = 0;
    p->refs_4 = 0;
}
// Matched
void ResetModelLoader_800204D0(void)
{
    ModelLoader* p = modelLoaderTask_8008B54C->entry.buffer;
    ModelLoadSlot* q = p->slots_C;
    int i;
    p->state_0 = 0;
    p->done_4 = 1;
    p->models_8 = 0;
    for (i = 0; i < 4; i++)
    {
        q->loaded_0 = 0;
        q->id_4 = -1;
        q->sel_8 = 0;
        q->arg_C = 0;
        q->animSet_10 = -1;
        q++;
    }
}
// Matched
void FreeModelLoaderList_8002052C(void)
{
    ModelLoader* p = modelLoaderTask_8008B54C->entry.buffer;
    if (p->models_8)
    {
        FreeModelList_80024BB0(&p->models_8);
    }
}
// Matched
void StartModelLoader_8002056C(void)
{
    EventEntry* q = &modelLoaderTask_8008B54C->entry;
    q->cb_8 = (EventEntryFn)ModelLoaderTask_800209AC;
    q->flags = (q->flags | 1) & ~0x8000;
    ((ModelLoader*)q->buffer)->state_0 = 0;
    q->cb_8(q, q->buffer);
}
// Matched
int IsModelLoaderDone_800205D0(void)
{
    return ((ModelLoader*)modelLoaderTask_8008B54C->entry.buffer)->done_4;
}
// Matched
void StopModelLoader_800205F0(void)
{
    EventEntry* n = &modelLoaderTask_8008B54C->entry;
    n->flags = (n->flags & ~1) | 0x8000;
}
// Matched
int CountLoaderModels_80020614(void)
{
    ModelLoader* p = modelLoaderTask_8008B54C->entry.buffer;
    ModelLoadSlot* e = p->slots_C;
    int count = 0;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (e->id_4 >= 0)
        {
            count++;
        }
        e++;
    }
    return count;
}
// Matched
int GetLoaderModelId_80020654(int k)
{
    ModelLoader* p = modelLoaderTask_8008B54C->entry.buffer;
    ModelLoadSlot* e = p->slots_C;
    int n = 0;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (e->id_4 >= 0)
        {
            if (n == k)
            {
                return e->id_4;
            }
            n++;
        }
        e++;
    }
    return -1;
}
// Matched
int RequestLoaderModel_800206A0(int id, int sel, int animMode, int animSet)
{
    ModelLoader* p = modelLoaderTask_8008B54C->entry.buffer;
    ModelLoadSlot* e = p->slots_C;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (id == e->id_4)
        {
            return 1;
        }
        e++;
    }
    e = p->slots_C;
    for (i = 0; i < 4; i++)
    {
        if (e->id_4 == -1)
        {
            e->loaded_0 = 0;
            e->id_4 = id;
            e->sel_8 = sel;
            e->arg_C = animMode;
            e->animSet_10 = animSet;
            p->done_4 = 0;
            return 1;
        }
        e++;
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
    ModelLoadSlot* p = base->slots_C;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (p->id_4 >= 0 && p->animSet_10 >= 0)
        {
            if (model == AcquireModel_80024D70(base->models_8, p->id_4))
            {
                FreeModel_80024C48(model);
                p->id_4 = -1;
                return;
            }
        }
        p++;
    }
}
// Matched
void FreeLoaderModelAnimSets_80020814(void)
{
    ModelLoader* base = modelLoaderTask_8008B54C->entry.buffer;
    ModelLoadSlot* p = base->slots_C;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (p->id_4 >= 0 && p->animSet_10 >= 0)
        {
            FreeModelAnimSet_80025884(AcquireModel_80024D70(base->models_8, p->id_4));
        }
        p++;
    }
}
// Matched
void LoadLoaderModelAnimSets_80020898(void)
{
    ModelLoader* base = modelLoaderTask_8008B54C->entry.buffer;
    ModelLoadSlot* p = base->slots_C;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (p->id_4 >= 0 && p->animSet_10 >= 0)
        {
            LoadModelAnimSet_80025780(AcquireModel_80024D70(base->models_8, p->id_4), p->animSet_10, 1);
        }
        p++;
    }
}
// Matched
int AreLoaderModelsLoaded_80020924(void)
{
    ModelLoader* base = modelLoaderTask_8008B54C->entry.buffer;
    ModelLoadSlot* p = base->slots_C;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (p->id_4 >= 0)
        {
            if (AreFileRequestsDone_80024DC4(AcquireModel_80024D70(base->models_8, p->id_4)) == 0)
            {
                return 0;
            }
        }
        p++;
    }
    return 1;
}
// Matched
void ModelLoaderTask_800209AC(EventEntry* p, int* a1)
{
    ModelLoader* q = (ModelLoader*)a1;
    int s = q->state_0;
    int t;
    switch (s)
    {
    case 0:
        LoadRequestedModels_80020A38(q);
        t = q->state_0;
        eventDispatchHalt_8008B540 = 1;
        q->state_0 = t + 1;
        break;
    case 1:
        if (AreRequestedModelsLoaded_80020B70(q))
        {
            StopModelLoader_800205F0();
        }
        eventDispatchHalt_8008B540 = s;
        break;
    }
}
// Matched
void LoadRequestedModels_80020A38(ModelLoader* p)
{
    ModelLoadSlot* e;
    int i;
    if (p->models_8 == 0)
    {
        InitModelList_80024ADC(&p->models_8, modelLoaderVram_8007DC70, 1);
    }
    e = p->slots_C;
    for (i = 0; i < 4; i++)
    {
        if (e->id_4 >= 0 && e->loaded_0 == 0)
        {
            LoadModel_80025200(p->models_8, e->id_4, e->sel_8, e->arg_C, 1);
        }
        e++;
    }
    e = p->slots_C;
    for (i = 0; i < 4; i++)
    {
        if (e->id_4 >= 0 && e->loaded_0 == 0)
        {
            if (e->animSet_10 >= 0)
            {
                LoadModelAnimSet_80025780(AcquireModel_80024D70(p->models_8, e->id_4), e->animSet_10, 1);
            }
            e->loaded_0 = 1;
        }
        e++;
    }
}
// Matched
int AreRequestedModelsLoaded_80020B70(ModelLoader* loader)
{
    ModelLoadSlot* p = loader->slots_C;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (p->loaded_0 != 0)
        {
            if (AreFileRequestsDone_80024DC4(AcquireModel_80024D70(loader->models_8, p->id_4)) == 0)
            {
                return 0;
            }
        }
        p++;
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
void InitOverlayLoaderTask_80020CB8(EventEntry* p, OverlayLoader* q)
{
    q->loaded_4 = -1;
    q->wanted_0 = 0x1D;
    p->cb_8 = (EventEntryFn)UpdateOverlayLoaderTask_80020CD8;
}
// Matched
void UpdateOverlayLoaderTask_80020CD8(int a0, OverlayLoader* p)
{
    if (p->wanted_0 != p->loaded_4)
    {
        p->loaded_4 = p->wanted_0;
        p->request_8 = LoadOverlay_80020BF8(2, p->wanted_0);
    }
}
// Matched
int LoadOverlayIfChanged_80020D1C(int mode, int overlay)
{
    OverlayLoader* p = overlayLoaderTask_8008D4C0->entry.buffer;
    if (p->wanted_0 == overlay)
    {
        return -1;
    }
    p->wanted_0 = overlay;
    p->loaded_4 = overlay;
    return LoadOverlay_80020BF8(mode, p->wanted_0);
}
// Matched
void ResetOverlayLoaderTask_80020D68(void)
{
    ((OverlayLoader*)overlayLoaderTask_8008D4C0->entry.buffer)->wanted_0 = 0x1D;
}
// Matched
int IsOverlayLoaderIdle_80020D84(void)
{
    OverlayLoader* p = overlayLoaderTask_8008D4C0->entry.buffer;
    int r;
    if (p->wanted_0 == 0x1D)
    {
        r = GetFileRequestStatus_8003BE30(p->request_8) == 0;
    }
    else
    {
        ResetOverlayLoaderTask_80020D68();
        r = 0;
    }
    return r;
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
    ListInit_8003FDB0(out->list_4);
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
int IsEffectFileLoaded_80020EBC(EffectFile* p)
{
    return GetFileRequestStatus_8003BE30(p->request_0) == 0;
}
// Matched
void FreeEffectFile_80020EE0(EffectFile* p)
{
    ListFreeAll_8003FEC8(p->list_4);
}
// Matched
int FindEffectIndex_80020F00(EffectFile* p, int kind, int id)
{
    int i;
    for (i = 0; i < p->pointCount_14; i++)
    {
        if (p->points_18[i].kind == kind && p->points_18[i].id == id)
        {
            return p->points_18[i].index;
        }
    }
    return -1;
}
void LoadEffectSprite_80021298(int* src, EffectSprite* out, int a2, int a3, int heap);
void LoadEffectModel_80021464(int* hdr, EffectModel* out, int a2, int a3, int heap);
int LoadMdecImages_800215E8(int* hdr, MdecImageSet* out, int heap);
void AllocMdecBuffers_800216E8(EffectMdecBuffers* a0, int a1, int a2);
void LoadFtgMatList_80021E4C(int* a0, FtgMatList* a1, unsigned int n);
// Matched
void OnEffectFileLoaded_80020F5C(EffectLoadArg* arg_in, int* hdr)
{
    EffectLoadArg* arg = arg_in;
    EffectFile* out = arg->out_0;
    int* p1 = (int*)((char*)hdr + hdr[1]);
    int* p2 = (int*)((char*)hdr + hdr[2]);
    int* p3 = (int*)((char*)hdr + hdr[3]);
    int* p4 = (int*)((char*)hdr + hdr[4]);
    int* p5 = (int*)((char*)hdr + hdr[5]);
    int* p6 = (int*)((char*)hdr + hdr[6]);
    int i;
    int max;
    int r;
    int n;
    int* src;
    out->pointCount_14 = 0;
    out->spriteCount_1C = 0;
    out->modelCount_24 = 0;
    out->imageSetCount_2C = 0;
    out->data_10 = ListAlloc_8003FDC0(out->list_4, p1[0]);
    MemCopy_800403E8(out->data_10, p1 + 1, p1[0]);
    n = p2[0];
    if (n)
    {
        out->pointCount_14 = n;
        out->points_18 = ListAlloc_8003FDC0(out->list_4, n * 12);
        src = p2 + 1;
        for (i = 0; i < out->pointCount_14; i++)
        {
            out->points_18[i].kind = src[0];
            out->points_18[i].id = src[1];
            out->points_18[i].index = src[2];
            src += 3;
        }
    }
    n = p3[0];
    if (n)
    {
        out->spriteCount_1C = n;
        out->sprites_20 = ListAlloc_8003FDC0(out->list_4, n * 0x34);
        for (i = 0; i < out->spriteCount_1C; i++)
        {
            EffectSprite* d = &out->sprites_20[i];
            LoadEffectSprite_80021298((int*)((char*)p3 + p3[i + 1]), d, (int)arg->reloc_4, arg->sel_10, (int)out->list_4);
        }
    }
    n = p4[0];
    if (n)
    {
        out->modelCount_24 = n;
        out->models_28 = ListAlloc_8003FDC0(out->list_4, n * 0x1C);
        for (i = 0; i < out->modelCount_24; i++)
        {
            EffectModel* d = &out->models_28[i];
            LoadEffectModel_80021464((int*)((char*)p4 + p4[i + 1]), d, (int)arg->reloc_4, arg->sel_10, (int)out->list_4);
        }
    }
    n = p5[0];
    if (n)
    {
        out->imageSetCount_2C = n;
        out->imageSets_30 = ListAlloc_8003FDC0(out->list_4, n * 8);
        i = 0;
        max = i;
        for (; i < out->imageSetCount_2C; i++)
        {
            r = LoadMdecImages_800215E8((int*)((char*)p5 + p5[i + 1]), &out->imageSets_30[i], (int)out->list_4);
            if (max < r)
            {
                max = r;
            }
        }
        AllocMdecBuffers_800216E8(&out->mdec_34, max, (int)out->list_4);
    }
    if (GetTiyFileCount_80028E68(p6))
    {
        LoadTiyTimsRelocated_80028FDC(0, 0, 0, (int)p6, GetTiyFileCount_80028E68(p6), (int)arg->reloc_4, arg->sel_10);
    }
}
// Matched
void LoadEffectSprite_80021298(int* src, EffectSprite* out, int reloc, int sel, int heap)
{
    POLY_FT4 buf;
    int i;
    int j;
    int n;
    struct_1c* d;
    struct_1c* s;
    out->count_0 = *src++;
    out->frameCounts_4 = ListAlloc_8003FDC0(heap, out->count_0);
    out->frames_8 = ListAlloc_8003FDC0(heap, out->count_0 * 4);
    for (i = 0; i < out->count_0; i++)
    {
        n = *src++;
        s = (struct_1c*)src;
        d = ListAlloc_8003FDC0(heap, n * 28);
        out->frameCounts_4[i] = n;
        out->frames_8[i] = (EffectSpriteFrame*)d;
        for (j = 0; j < out->frameCounts_4[i]; j++)
        {
            d->f0 = s->f0;
            d->f4 = s->f4;
            d->f8 = s->f8;
            d->fC = s->fC;
            d->f10 = s->f10;
            d->f18 = s->f18;
            d++;
            s++;
        }
        src = (int*)s;
    }
    MemCopy_800403E8(&buf, src, 0x28);
    InitPolyFT4_80029A10(&out->poly_C, &buf);
}
// Matched
void LoadEffectModel_80021464(int* hdr, EffectModel* out, int reloc, int sel, int heap)
{
    int* models = (int*)((char*)hdr + hdr[1]);
    int* images = (int*)((char*)hdr + hdr[2]);
    if (GetFtgObjectCount_80021738(models))
    {
        out->ftgCount_0 = GetFtgObjectCount_80021738(models);
        AllocFtgObjects_80021744(&out->ftg_4, out->ftgCount_0, heap);
        LoadFtgObjects_80021824(models, out->ftg_4, out->ftgCount_0, heap, reloc);
    }
    if (GetFtgMatCount_80021DE4(models))
    {
        AllocFtgMatList_80021DF0(&out->mats_8, GetFtgMatCount_80021DE4(models), heap);
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
int LoadMdecImages_800215E8(int* hdr, MdecImageSet* out, int heap)
{
    int i;
    int max;
    int size;
    unsigned long* src;
    int n;
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
        n = DecDCTBufSize(src);
        if (max < n)
        {
            max = n;
        }
    }
    return max;
}
// Matched
void AllocMdecBuffers_800216E8(EffectMdecBuffers* out, int maxSize, int heap)
{
    out->dct_0 = ListAlloc_8003FDC0(heap, (maxSize + 1) * 4);
    out->work_4 = ListAlloc_8003FDC0(heap, 0x2000);
}
// Matched
int GetFtgObjectCount_80021738(int* p)
{
    return p[1];
}
// Matched
void AllocFtgObjects_80021744(FtgObject** p, int count, int heap)
{
    *p = HeapAlloc_8003FC8C(count * 0x54, (struct Pool*)heap);
}
// Matched
void FreeFtgObjects_80021784(FtgObject** a0, unsigned int n, int heap)
{
    FtgObject* p = *a0;
    unsigned int i;
    for (i = 0; i < n; i++)
    {
        FreeFtgObject_800229B0(p, heap);
        p++;
    }
    HeapFree_8003FD18(*a0, heap);
    *a0 = 0;
}
// Matched
void FreeFtgObjectData_80021804(FtgObject* p, int heap)
{
    FreeFtgObject_800229B0(p, heap);
}
// Matched
void LoadFtgObjects_80021824(int* file, FtgObject* out, int count, int heap, int reloc)
{
    unsigned int n = GetFtgObjectCount_80021738(file);
    int src = (int)(file + 4);
    unsigned int i;
    for (i = 0; i < n; i++)
    {
        src = LoadFtgObject_80022458(out, src, heap, reloc);
        out++;
    }
}
// Matched
void CopyFtgObject_800218A8(FtgObject* s, FtgObject* d, int heap)
{
    char* buf;
    int size;
    int i;
    size = s->f3_0.count * 0x24 + s->g3_8.count * 0x3C;
    size += s->ft3_10.count * 0x30;
    size += s->gt3_18.count * 0x48;
    size += s->f4_20.count * 0x2C;
    size += s->g4_28.count * 0x50;
    size += s->ft4_30.count * 0x38;
    size += s->gt4_38.count * 0x5C;
    size += s->spriteCount_40 * 0x14;
    size += s->texSpriteCount_48 * 0x14;
    if (size)
    {
        buf = HeapAlloc_8003FC8C(size, (struct Pool*)heap);
    }
    else
    {
        buf = 0;
    }
    d->f3_0.count = s->f3_0.count;
    d->f3_0.items = (FtgPolyF3*)buf;
    buf += s->f3_0.count * 0x24;
    d->g3_8.count = s->g3_8.count;
    d->g3_8.items = (FtgPolyG3*)buf;
    buf += s->g3_8.count * 0x3C;
    d->ft3_10.count = s->ft3_10.count;
    d->ft3_10.items = (FtgPolyFT3*)buf;
    buf += s->ft3_10.count * 0x30;
    d->gt3_18.count = s->gt3_18.count;
    d->gt3_18.items = (FtgPolyGT3*)buf;
    buf += s->gt3_18.count * 0x48;
    d->f4_20.count = s->f4_20.count;
    d->f4_20.items = (FtgPolyF4*)buf;
    buf += s->f4_20.count * 0x2C;
    d->g4_28.count = s->g4_28.count;
    d->g4_28.items = (FtgPolyG4*)buf;
    buf += s->g4_28.count * 0x50;
    d->ft4_30.count = s->ft4_30.count;
    d->ft4_30.items = (FtgPolyFT4*)buf;
    buf += s->ft4_30.count * 0x38;
    d->gt4_38.count = s->gt4_38.count;
    d->gt4_38.items = (FtgPolyGT4*)buf;
    buf += s->gt4_38.count * 0x5C;
    d->spriteCount_40 = s->spriteCount_40;
    d->sprites_44 = (FtgSprite*)buf;
    buf += s->spriteCount_40 * 0x14;
    d->texSpriteCount_48 = s->texSpriteCount_48;
    d->texSprites_50 = (FtgSprite*)buf;
    for (i = 0; i < d->f3_0.count; i++)
    {
        MemCopy_800403E8(&d->f3_0.items[i], &s->f3_0.items[i], 0x24);
    }
    for (i = 0; i < d->g3_8.count; i++)
    {
        MemCopy_800403E8(&d->g3_8.items[i], &s->g3_8.items[i], 0x3C);
    }
    for (i = 0; i < d->ft3_10.count; i++)
    {
        MemCopy_800403E8(&d->ft3_10.items[i], &s->ft3_10.items[i], 0x30);
    }
    for (i = 0; i < d->gt3_18.count; i++)
    {
        MemCopy_800403E8(&d->gt3_18.items[i], &s->gt3_18.items[i], 0x48);
    }
    for (i = 0; i < d->f4_20.count; i++)
    {
        MemCopy_800403E8(&d->f4_20.items[i], &s->f4_20.items[i], 0x2C);
    }
    for (i = 0; i < d->g4_28.count; i++)
    {
        MemCopy_800403E8(&d->g4_28.items[i], &s->g4_28.items[i], 0x50);
    }
    for (i = 0; i < d->ft4_30.count; i++)
    {
        MemCopy_800403E8(&d->ft4_30.items[i], &s->ft4_30.items[i], 0x38);
    }
    for (i = 0; i < d->gt4_38.count; i++)
    {
        MemCopy_800403E8(&d->gt4_38.items[i], &s->gt4_38.items[i], 0x5C);
    }
    for (i = 0; i < d->spriteCount_40; i++)
    {
        MemCopy_800403E8(&d->sprites_44[i], &s->sprites_44[i], 0x14);
    }
    for (i = 0; i < d->texSpriteCount_48; i++)
    {
        MemCopy_800403E8(&d->texSprites_50[i], &s->texSprites_50[i], 0x14);
    }
    d->tpage_4C = s->tpage_4C;
    d->clut_4E = s->clut_4E;
}
// Matched
int GetFtgMatCount_80021DE4(int* p)
{
    return p[2];
}
// Matched
void AllocFtgMatList_80021DF0(FtgMatList* p, int count, int heap)
{
    p->count_0 = count;
    p->items_4 = HeapAlloc_8003FC8C(count * 16, (struct Pool*)heap);
}
// p is volatile to keep the store before the load
// Matched
void FreeFtgMatList_80021E24(volatile FtgMatList* p, int h)
{
    p->count_0 = 0;
    HeapFree_8003FD18(p->items_4);
}
// Matched
void LoadFtgMatList_80021E4C(int* file, FtgMatList* out, unsigned int n)
{
    unsigned short* src = (unsigned short*)((char*)file + file[3]);
    unsigned int i;
    for (i = 0; i < n; i++)
    {
        unsigned short* dst = out->items_4[i];
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = src[3];
        dst[4] = src[4];
        dst[5] = src[5];
        dst[6] = src[6];
        dst[7] = src[7];
        src += 8;
    }
}
// r2 is unused (the original frame has room for it)
// Matched
void MakeFtgSpritePoly_80021EDC(FtgPolyFT4* p, POLY_FT4* d)
{
    RECT r;
    RECT r2;
    r.x = p->u0;
    r.y = p->v0;
    r.w = p->u3;
    r.h = p->v3;
    if (p->u1 < r.x)
    {
        r.x = p->u1;
    }
    if (r.x > p->u2)
    {
        r.x = p->u2;
    }
    if (r.x > p->u3)
    {
        r.x = p->u3;
    }
    if (p->v1 < r.y)
    {
        r.y = p->v1;
    }
    if (r.y > p->v2)
    {
        r.y = p->v2;
    }
    if (r.y > p->v3)
    {
        r.y = p->v3;
    }
    if (r.w < p->u2)
    {
        r.w = p->u2;
    }
    if (r.w < p->u1)
    {
        r.w = p->u1;
    }
    if (r.w < p->u0)
    {
        r.w = p->u0;
    }
    if (r.h < p->v2)
    {
        r.h = p->v2;
    }
    if (r.h < p->v1)
    {
        r.h = p->v1;
    }
    if (r.h < p->v0)
    {
        r.h = p->v0;
    }
    setlen(d, 9);
    d->code = 0x2C;
    d->r0 = p->c.r;
    d->g0 = p->c.g;
    d->b0 = p->c.b;
    d->u0 = r.x;
    d->v0 = r.y;
    d->u1 = r.w;
    d->v1 = r.y;
    d->u2 = r.x;
    d->v2 = r.h;
    d->u3 = r.w;
    d->v3 = r.h;
    d->x0 = 0;
    d->y0 = 0;
    d->x1 = r.w - r.x;
    d->y1 = 0;
    d->x2 = 0;
    d->y2 = r.h - r.y;
    d->x3 = r.w - r.x;
    d->y3 = r.h - r.y;
    d->code = p->c.code;
    d->tpage = p->tpage;
    d->clut = p->clut;
}
// Matched
void MakeFtgSprt_800221DC(FtgPolyFT4* p, SPRT* d, DR_TPAGE* tp)
{
    RECT r;
    r.x = p->u0;
    r.y = p->v0;
    r.w = p->u3;
    r.h = p->v3;
    if (p->u1 < r.x)
    {
        r.x = p->u1;
    }
    if (r.x > p->u2)
    {
        r.x = p->u2;
    }
    if (r.x > p->u3)
    {
        r.x = p->u3;
    }
    if (p->v1 < r.y)
    {
        r.y = p->v1;
    }
    if (r.y > p->v2)
    {
        r.y = p->v2;
    }
    if (r.y > p->v3)
    {
        r.y = p->v3;
    }
    if (r.w < p->u2)
    {
        r.w = p->u2;
    }
    if (r.w < p->u1)
    {
        r.w = p->u1;
    }
    if (r.w < p->u0)
    {
        r.w = p->u0;
    }
    if (r.h < p->v2)
    {
        r.h = p->v2;
    }
    if (r.h < p->v1)
    {
        r.h = p->v1;
    }
    if (r.h < p->v0)
    {
        r.h = p->v0;
    }
    setlen(d, 4);
    d->code = 0x64;
    d->r0 = p->c.r;
    d->g0 = p->c.g;
    d->b0 = p->c.b;
    d->u0 = r.x;
    d->v0 = r.y;
    d->x0 = 0;
    d->y0 = 0;
    d->w = r.w - r.x;
    d->h = r.h - r.y;
    d->clut = p->clut;
    SetDrawTPage(tp, 0, 1, p->tpage);
}
void CountFtgSprites_80022B84(FtgSrcObjectHeader* c, int* x, int* y);
int AllocFtgObjectPrims_80022634(FtgObject* out, FtgSrcObjectHeader* hdr, int h);
int LoadFtgSprites_8002300C(FtgPrimHeader* hdr, FtgSrcSprites8* p, FtgSpriteGroups8* a, int k, int h);
int LoadFtgTexSprites_8002320C(FtgPrimHeader* hdr, FtgSrcSprites9* p, FtgSpriteGroups9* b, int k, int h);
void MergeFtgSpriteGroups_80022CC4(FtgObject* a0, FtgSpriteGroups8* a, FtgSpriteGroups9* b, int h);
// Matched
int LoadFtgObject_80022458(FtgObject* out, unsigned char* src, int h, int reloc)
{
    int typeCounts[10];
    FtgSpriteGroups8 A;
    FtgSpriteGroups9 B;
    unsigned int i;
    unsigned int n;
    unsigned char* hdr;
    FtgPrimHeader* p;
    unsigned int type;
    unsigned int j;
    int k;
    for (j = 0; j < 10; j++)
    {
        typeCounts[j] = 0;
    }
    hdr = src;
    src += 0x28;
    n = AllocFtgObjectPrims_80022634(out, (FtgSrcObjectHeader*)hdr, h);
    AllocFtgSpriteGroups_800228F8(&A, &B, (FtgSrcObjectHeader*)hdr, h);
    for (i = 0; i < n; i++)
    {
        p = (FtgPrimHeader*)src;
        src += 4;
        type = p->type_0;
        k = typeCounts[type];
        typeCounts[type] = k + 1;
        if (reloc != 0 && ftgPrimRelocators_8007DB08[type] != 0)
        {
            ftgPrimRelocators_8007DB08[type](src, reloc);
        }
        switch (type)
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            src += ftgPrimLoaders_8007DAE0[type](p, src, out, k, h);
            break;
        case 8:
            src += LoadFtgSprites_8002300C(p, (FtgSrcSprites8*)src, &A, k, h);
            break;
        case 9:
            src += LoadFtgTexSprites_8002320C(p, (FtgSrcSprites9*)src, &B, k, h);
            break;
        }
    }
    MergeFtgSpriteGroups_80022CC4(out, &A, &B, h);
    FreeFtgSpriteGroups_800229E0(&A, &B, h);
    return (int)src;
}
// Matched
int AllocFtgObjectPrims_80022634(FtgObject* out, FtgSrcObjectHeader* hdr, int h)
{
    int x;
    int y;
    int size;
    int total;
    char* p;
    int* c = hdr->counts_0;
    p = 0;
    CountFtgSprites_80022B84(hdr, &x, &y);
    size = c[0] * 0x24 + c[1] * 0x3C;
    total = c[0] + c[1];
    size += c[2] * 0x30;
    total += c[2];
    size += c[3] * 0x48;
    total += c[3];
    size += c[4] * 0x2C;
    total += c[4];
    size += c[5] * 0x50;
    total += c[5];
    size += c[6] * 0x38;
    total += c[6];
    size += c[7] * 0x5C;
    total += c[7];
    size += x * 0x14;
    total += c[8];
    size += y * 0x14;
    total += c[9];
    if (size != 0)
    {
        p = HeapAlloc_8003FC8C(size, h);
    }
    out->f3_0.count = c[0];
    out->f3_0.items = (FtgPolyF3*)p;
    p += c[0] * 0x24;
    out->g3_8.count = c[1];
    out->g3_8.items = (FtgPolyG3*)p;
    p += c[1] * 0x3C;
    out->ft3_10.count = c[2];
    out->ft3_10.items = (FtgPolyFT3*)p;
    p += c[2] * 0x30;
    out->gt3_18.count = c[3];
    out->gt3_18.items = (FtgPolyGT3*)p;
    p += c[3] * 0x48;
    out->f4_20.count = c[4];
    out->f4_20.items = (FtgPolyF4*)p;
    p += c[4] * 0x2C;
    out->g4_28.count = c[5];
    out->g4_28.items = (FtgPolyG4*)p;
    p += c[5] * 0x50;
    out->ft4_30.count = c[6];
    out->ft4_30.items = (FtgPolyFT4*)p;
    p += c[6] * 0x38;
    out->gt4_38.count = c[7];
    out->gt4_38.items = (FtgPolyGT4*)p;
    p += c[7] * 0x5C;
    out->spriteCount_40 = x;
    out->sprites_44 = (FtgSprite*)p;
    p += x * 0x14;
    out->texSpriteCount_48 = y;
    out->texSprites_50 = (FtgSprite*)p;
    return total;
}
// Matched
int AllocFtgSpriteGroups_800228F8(FtgSpriteGroups8* groups8, FtgSpriteGroups9* groups9, FtgSrcObjectHeader* hdr, int heap)
{
    int n;
    int m;
    groups8->count = hdr->counts_0[8];
    n = hdr->counts_0[8];
    if (n)
    {
        groups8->groups = HeapAlloc_8003FC8C(n << 3, (struct Pool*)heap);
    }
    else
    {
        groups8->groups = 0;
    }
    groups9->count = hdr->counts_0[9];
    m = hdr->counts_0[9];
    n += m;
    if (m)
    {
        groups9->groups = HeapAlloc_8003FC8C(m * 12, (struct Pool*)heap);
    }
    else
    {
        groups9->groups = 0;
    }
    return n;
}
// Matched
void FreeFtgObject_800229B0(FtgObject* p, int heap)
{
    FtgPolyF3* a = p->f3_0.items;
    if (a)
    {
        HeapFree_8003FD18(a, heap);
    }
}
// Matched
void FreeFtgSpriteGroups_800229E0(FtgSpriteGroups8* groups8, FtgSpriteGroups9* groups9, int h)
{
    int i;
    if (groups8->groups != 0)
    {
        for (i = 0; i < groups8->count; i++)
        {
            if (groups8->groups[i].items != 0)
            {
                HeapFree_8003FD18(groups8->groups[i].items, h);
            }
        }
        HeapFree_8003FD18(groups8->groups, h);
    }
    if (groups9->groups != 0)
    {
        for (i = 0; i < groups9->count; i++)
        {
            if (groups9->groups[i].items != 0)
            {
                HeapFree_8003FD18(groups9->groups[i].items, h);
            }
        }
        HeapFree_8003FD18(groups9->groups, h);
    }
}
// Matched
void RelocateTPageClut_80022AE8(unsigned short* tpage, unsigned short* clut, short* reloc)
{
    int u = reloc[0] / 64;
    int v = reloc[1] / 256;
    int tp = v * 16 + u;
    unsigned short t = *clut;
    u = (t & 0x3F) * 16;
    v = (t >> 6) & 0x1FF;
    if (((*tpage >> 7) & 3) == 0)
    {
        u += reloc[2];
        v += reloc[3];
    }
    else
    {
        u += reloc[4];
        v += reloc[5];
    }
    *tpage += tp;
    *clut = v * 64 + (u >> 4);
}
#if 0
// Not matched (18 lines; its jump table is dword_8007411C: drop that C table when this compiles). Needs the
// prototype above changed to take unsigned char*: using the parameter itself as the cursor gives the header exactly
// (c copied to $a3, r a separate copy because q changes before the loads). Left: the type 8/9 cases, where the original
// keeps a copy P = q (lw 0(P), P + 4 into a fresh register, then q = (P + 4) + k * 20) and a second copy of k for
// a += k. Copies only survived here when q is written between the copy and its uses (t = q; q += 4; k = *t), but then
// q + 4 goes to q's own register. Tried: block-local pointers / struct casts, inline helpers (by value: cse removes the
// param copies; by pointer: memory), (r + 1) + k * 20 vs q += 4 + k * 20, -O1 / single -fno-* flags (no copies either).
// k = *p++ (below) already puts q + 4 in its own register; only the P and k copies are missing.
void CountFtgSprites_80022B84(unsigned char* q, int* x, int* y)
{
    int n;
    int i;
    int a;
    int b;
    int k;
    unsigned char* t;
    int* r;
    a = 0;
    r = (int*)q;
    q += 0x28;
    n = r[0] + r[1] + r[2] + r[3] + r[4] + r[5] + r[6] + r[7] + r[8] + r[9];
    b = 0;
    for (i = 0; i < n; i++)
    {
        t = q;
        q += 4;
        switch (*t)
        {
        case 1: q += 0x3C; break;
        case 0: case 2: q += 0x24; break;
        case 3: q += 0x40; break;
        case 5: q += 0x50; break;
        case 4: case 6: q += 0x2C; break;
        case 7: q += 0x54; break;
        case 8: { int* p = (int*)q; k = *p++; q = (unsigned char*)p + k * 20; a += k; break; }
        case 9: { int* p = (int*)q; k = *p; p += 2; q = (unsigned char*)p + k * 20; b += k; break; }
        }
    }
    *x = a;
    *y = b;
}
#endif
INCLUDE_ASM(CountFtgSprites_80022B84);
#if 0
// Not matched (2 words): the second loop has the j++ / n++ increments in the other order (j++, n++ in the for header
// or in the body fixes them but then swaps the sprite pointer increments). A j of its own for the second loop fixed the
// first loop's j/k registers
void MergeFtgSpriteGroups_80022CC4(FtgObject* obj, FtgSpriteGroups8* a, FtgSpriteGroups9* b, int h)
{
    int j;
    int n;
    int k;
    FtgSpriteGroup8* e;
    FtgSpriteGroup9* f;
    if (a->count)
    {
        j = 0;
        e = a->groups;
        k = 0;
        for (n = 0; n < obj->spriteCount_40; n++)
        {
            if (j >= a->groups[k].count)
            {
                k++;
                j = 0;
                e = &a->groups[k];
            }
            obj->sprites_44[n].p0.x = e->items[j].p0.x;
            obj->sprites_44[n].p0.y = e->items[j].p0.y;
            obj->sprites_44[n].p0.z = e->items[j].p0.z;
            obj->sprites_44[n].p0.uv = 0;
            obj->sprites_44[n].p1.x = e->items[j].p1.x;
            obj->sprites_44[n].p1.y = e->items[j].p1.y;
            obj->sprites_44[n].p1.z = e->items[j].p1.z;
            obj->sprites_44[n].p1.uv = 0;
            obj->sprites_44[n].c.r = e->items[j].c.r;
            obj->sprites_44[n].c.g = e->items[j].c.g;
            obj->sprites_44[n].c.b = e->items[j].c.b;
            obj->sprites_44[n].c.code = 0;
            j++;
        }
    }
    if (b->count)
    {
        int j;
        j = 0;
        obj->tpage_4C = b->groups->tpage;
        obj->clut_4E = b->groups->clut;
        f = b->groups;
        k = 0;
        for (n = 0; n < obj->texSpriteCount_48; n++, j++)
        {
            if (j >= b->groups[k].count)
            {
                k++;
                j = 0;
                f = &b->groups[k];
            }
            obj->texSprites_50[n].p0.x = f->items[j].p0.x;
            obj->texSprites_50[n].p0.y = f->items[j].p0.y;
            obj->texSprites_50[n].p0.z = f->items[j].p0.z;
            obj->texSprites_50[n].p0.uv = 0;
            obj->texSprites_50[n].p1.x = f->items[j].p1.x;
            obj->texSprites_50[n].p1.y = f->items[j].p1.y;
            obj->texSprites_50[n].p1.z = f->items[j].p1.z;
            obj->texSprites_50[n].p1.uv = 0;
            obj->texSprites_50[n].c.r = f->items[j].c.r;
            obj->texSprites_50[n].c.g = f->items[j].c.g;
            obj->texSprites_50[n].c.b = f->items[j].c.b;
            obj->texSprites_50[n].c.code = f->items[j].c.code;
            obj->texSprites_50[n].p1.uv = f->items[j].p1.uv;
        }
    }
}
#endif
INCLUDE_ASM(MergeFtgSpriteGroups_80022CC4);
// Matched
int LoadFtgSprites_8002300C(FtgPrimHeader* hdr, FtgSrcSprites8* p_in, FtgSpriteGroups8* a, int k, int h)
{
    FtgSrcSprites8* p = p_in;
    int r = 4;
    int i;
    FtgSrcSprite8* q;
    a->groups[k].count = p->count_0;
    a->groups[k].items = HeapAlloc_8003FC8C(p->count_0 * 20, h);
    q = (FtgSrcSprite8*)((unsigned char*)p + r); // r: bytes read so far
    for (i = 0; i < p->count_0; i++)
    {
        a->groups[k].items[i].p0.x = q[i].p0.x;
        a->groups[k].items[i].p0.y = q[i].p0.y;
        a->groups[k].items[i].p0.z = q[i].p0.z;
        a->groups[k].items[i].p0.uv = 0;
        a->groups[k].items[i].p1.x = q[i].p1.x;
        a->groups[k].items[i].p1.y = q[i].p1.y;
        a->groups[k].items[i].p1.z = q[i].p1.z;
        a->groups[k].items[i].p1.uv = 0;
        a->groups[k].items[i].c.r = q[i].c.r;
        a->groups[k].items[i].c.g = q[i].c.g;
        a->groups[k].items[i].c.b = q[i].c.b;
        a->groups[k].items[i].c.code = 0;
        r += 20;
    }
    return r;
}
// Matched
int LoadFtgTexSprites_8002320C(FtgPrimHeader* hdr, FtgSrcSprites9* p_in, FtgSpriteGroups9* b, int k, int h)
{
    FtgSrcSprites9* p = p_in;
    int r;
    int i;
    FtgSrcSprite9* q;
    b->groups[k].count = p->count_0;
    b->groups[k].items = HeapAlloc_8003FC8C(p->count_0 * 20, h);
    r = 8;
    b->groups[k].tpage = p->tpage_4;
    b->groups[k].clut = p->clut_6;
    q = (FtgSrcSprite9*)((unsigned char*)p + r); // r: bytes read so far
    for (i = 0; i < p->count_0; i++)
    {
        b->groups[k].items[i].p0.x = q[i].p0.x;
        b->groups[k].items[i].p0.y = q[i].p0.y;
        b->groups[k].items[i].p0.z = q[i].p0.z;
        b->groups[k].items[i].p0.uv = 0;
        b->groups[k].items[i].p1.x = q[i].p1.x;
        b->groups[k].items[i].p1.y = q[i].p1.y;
        b->groups[k].items[i].p1.z = q[i].p1.z;
        b->groups[k].items[i].p1.uv = 0;
        b->groups[k].items[i].c.r = q[i].c.r;
        b->groups[k].items[i].c.g = q[i].c.g;
        b->groups[k].items[i].c.b = q[i].c.b;
        b->groups[k].items[i].c.code = hdr->flags_3;
        b->groups[k].items[i].p1.uv = q[i].p1.u + (q[i].p1.v << 8);
        r += 20;
    }
    return r;
}
// Matched
void RelocFtgTexSprites_80023460(FtgSrcSprites9* p, int reloc)
{
    RelocateTPageClut_80022AE8(&p->tpage_4, &p->clut_6, reloc);
}
// Matched
int LoadFtgPolyF3_8002348C(FtgPrimHeader* hdr, FtgPolyF3* src, FtgObject* obj, int idx)
{
    if (hdr->flags_3 & 2)
    {
        SetSemiTrans(&obj->f3_0.items[idx], 1);
    }
    CopyFtgPolyF3_80023514(&obj->f3_0, src, hdr->flags_3, idx);
    return 0x24;
}
// Matched
void CopyFtgPolyF3_80023514(FtgPolyF3List* list, FtgPolyF3* s, int code, int idx)
{
    list->items[idx].c.r = s->c.r;
    list->items[idx].c.g = s->c.g;
    list->items[idx].c.b = s->c.b;
    list->items[idx].c.code = code;
    list->items[idx].v[0].x = s->v[0].x;
    list->items[idx].v[0].y = s->v[0].y;
    list->items[idx].v[0].z = s->v[0].z;
    list->items[idx].v[1].x = s->v[1].x;
    list->items[idx].v[1].y = s->v[1].y;
    list->items[idx].v[1].z = s->v[1].z;
    list->items[idx].v[2].x = s->v[2].x;
    list->items[idx].v[2].y = s->v[2].y;
    list->items[idx].v[2].z = s->v[2].z;
    list->items[idx].n.x = s->n.x;
    list->items[idx].n.y = s->n.y;
    list->items[idx].n.z = s->n.z;
}
// Matched
int LoadFtgPolyG3_80023624(FtgPrimHeader* hdr, FtgSrcPolyG3* src, FtgObject* obj, int idx)
{
    if (hdr->flags_3 & 2)
    {
        SetSemiTrans(&obj->g3_8.items[idx], 1);
    }
    CopyFtgPolyG3_800236AC(&obj->g3_8, src, hdr->flags_3, idx);
    return 0x3C;
}
// Matched
void CopyFtgPolyG3_800236AC(FtgPolyG3List* list, FtgSrcPolyG3* s, int code, int idx)
{
    list->items[idx].c[0].r = s->c[0].r;
    list->items[idx].c[0].g = s->c[0].g;
    list->items[idx].c[0].b = s->c[0].b;
    list->items[idx].c[0].code = code;
    list->items[idx].c[1].r = s->c[1].r;
    list->items[idx].c[1].g = s->c[1].g;
    list->items[idx].c[1].b = s->c[1].b;
    list->items[idx].c[0].code = code;
    list->items[idx].c[2].r = s->c[2].r;
    list->items[idx].c[2].g = s->c[2].g;
    list->items[idx].c[2].b = s->c[2].b;
    list->items[idx].c[0].code = code;
    list->items[idx].v[0].x = s->p[0].v.x;
    list->items[idx].v[0].y = s->p[0].v.y;
    list->items[idx].v[0].z = s->p[0].v.z;
    list->items[idx].v[1].x = s->p[1].v.x;
    list->items[idx].v[1].y = s->p[1].v.y;
    list->items[idx].v[1].z = s->p[1].v.z;
    list->items[idx].v[2].x = s->p[2].v.x;
    list->items[idx].v[2].y = s->p[2].v.y;
    list->items[idx].v[2].z = s->p[2].v.z;
    list->items[idx].n[0].x = s->p[0].n.x;
    list->items[idx].n[0].y = s->p[0].n.y;
    list->items[idx].n[0].z = s->p[0].n.z;
    list->items[idx].n[1].x = s->p[1].n.x;
    list->items[idx].n[1].y = s->p[1].n.y;
    list->items[idx].n[1].z = s->p[1].n.z;
    list->items[idx].n[2].x = s->p[2].n.x;
    list->items[idx].n[2].y = s->p[2].n.y;
    list->items[idx].n[2].z = s->p[2].n.z;
    list->items[idx].c[0].code = code;
}
// Matched
int LoadFtgPolyFT3_800238AC(FtgPrimHeader* hdr, FtgSrcPolyFT3* src, FtgObject* obj, int idx)
{
    if (hdr->flags_3 & 2)
    {
        SetSemiTrans(&obj->ft3_10.items[idx], 1);
    }
    CopyFtgPolyFT3_80023934(&obj->ft3_10, src, hdr->flags_3, idx);
    return 0x24;
}
// Matched
void CopyFtgPolyFT3_80023934(FtgPolyFT3List* list, FtgSrcPolyFT3* s, int code, int idx)
{
    list->items[idx].tpage = s->tex.tpage;
    list->items[idx].clut = s->tex.clut;
    list->items[idx].u0 = s->v[0].u;
    list->items[idx].v0 = s->v[0].v;
    list->items[idx].v[0].uv = list->items[idx].u0 + (list->items[idx].v0 << 8);
    list->items[idx].u1 = s->v[1].u;
    list->items[idx].v1 = s->v[1].v;
    list->items[idx].v[1].uv = list->items[idx].u1 + (list->items[idx].v1 << 8);
    list->items[idx].u2 = s->v[2].u;
    list->items[idx].v2 = s->v[2].v;
    list->items[idx].v[2].uv = list->items[idx].u2 + (list->items[idx].v2 << 8);
    list->items[idx].c.r = 0x80;
    list->items[idx].c.g = 0x80;
    list->items[idx].c.b = 0x80;
    list->items[idx].c.code = code;
    list->items[idx].v[0].x = s->v[0].x;
    list->items[idx].v[0].y = s->v[0].y;
    list->items[idx].v[0].z = s->v[0].z;
    list->items[idx].v[1].x = s->v[1].x;
    list->items[idx].v[1].y = s->v[1].y;
    list->items[idx].v[1].z = s->v[1].z;
    list->items[idx].v[2].x = s->v[2].x;
    list->items[idx].v[2].y = s->v[2].y;
    list->items[idx].v[2].z = s->v[2].z;
    list->items[idx].n.x = s->n.x;
    list->items[idx].n.y = s->n.y;
    list->items[idx].n.z = s->n.z;
}
// Matched
void RelocFtgPolyFT3_80023B24(FtgSrcPolyFT3* p, int reloc)
{
    RelocateTPageClut_80022AE8(&p->tex.tpage, &p->tex.clut, reloc);
}
// Matched
int LoadFtgPolyGT3_80023B48(FtgPrimHeader* hdr, FtgSrcPolyGT3* src, FtgObject* obj, int idx)
{
    if (hdr->flags_3 & 2)
    {
        SetSemiTrans(&obj->gt3_18.items[idx], 1);
    }
    CopyFtgPolyGT3_80023BD0(&obj->gt3_18, src, hdr->flags_3, idx);
    return 0x40;
}
// Matched
void CopyFtgPolyGT3_80023BD0(FtgPolyGT3List* list, FtgSrcPolyGT3* s, int code, int idx)
{
    list->items[idx].tpage = s->tex.tpage;
    list->items[idx].clut = s->tex.clut;
    list->items[idx].u0 = s->p[0].v.u;
    list->items[idx].v0 = s->p[0].v.v;
    list->items[idx].v[0].uv = list->items[idx].u0 + (list->items[idx].v0 << 8);
    list->items[idx].u1 = s->p[1].v.u;
    list->items[idx].v1 = s->p[1].v.v;
    list->items[idx].v[1].uv = list->items[idx].u1 + (list->items[idx].v1 << 8);
    list->items[idx].u2 = s->p[2].v.u;
    list->items[idx].v2 = s->p[2].v.v;
    list->items[idx].v[2].uv = list->items[idx].u2 + (list->items[idx].v2 << 8);
    list->items[idx].c[0].code = code;
    list->items[idx].c[0].r = s->c[0].r;
    list->items[idx].c[0].g = s->c[0].g;
    list->items[idx].c[0].b = s->c[0].b;
    list->items[idx].c[1].r = s->c[1].r;
    list->items[idx].c[1].g = s->c[1].g;
    list->items[idx].c[1].b = s->c[1].b;
    list->items[idx].c[2].r = s->c[2].r;
    list->items[idx].c[2].g = s->c[2].g;
    list->items[idx].c[2].b = s->c[2].b;
    list->items[idx].v[0].x = s->p[0].v.x;
    list->items[idx].v[0].y = s->p[0].v.y;
    list->items[idx].v[0].z = s->p[0].v.z;
    list->items[idx].v[1].x = s->p[1].v.x;
    list->items[idx].v[1].y = s->p[1].v.y;
    list->items[idx].v[1].z = s->p[1].v.z;
    list->items[idx].v[2].x = s->p[2].v.x;
    list->items[idx].v[2].y = s->p[2].v.y;
    list->items[idx].v[2].z = s->p[2].v.z;
    list->items[idx].n[0].x = s->p[0].n.x;
    list->items[idx].n[0].y = s->p[0].n.y;
    list->items[idx].n[0].z = s->p[0].n.z;
    list->items[idx].n[1].x = s->p[1].n.x;
    list->items[idx].n[1].y = s->p[1].n.y;
    list->items[idx].n[1].z = s->p[1].n.z;
    list->items[idx].n[2].x = s->p[2].n.x;
    list->items[idx].n[2].y = s->p[2].n.y;
    list->items[idx].n[2].z = s->p[2].n.z;
}
// Matched
void RelocFtgPolyGT3_80023E80(FtgSrcPolyGT3* p, int reloc)
{
    RelocateTPageClut_80022AE8(&p->tex.tpage, &p->tex.clut, reloc);
}
// Matched
int LoadFtgPolyF4_80023EA4(FtgPrimHeader* hdr, FtgPolyF4* src, FtgObject* obj, int idx)
{
    if (hdr->flags_3 & 2)
    {
        SetSemiTrans(&obj->f4_20.items[idx], 1);
    }
    CopyFtgPolyF4_80023F34(&obj->f4_20, src, hdr->flags_3, idx);
    return 0x2C;
}
// Matched
void CopyFtgPolyF4_80023F34(FtgPolyF4List* list, FtgPolyF4* s, int code, int idx)
{
    list->items[idx].c.r = s->c.r;
    list->items[idx].c.g = s->c.g;
    list->items[idx].c.b = s->c.b;
    list->items[idx].c.code = code;
    list->items[idx].v[0].x = s->v[0].x;
    list->items[idx].v[0].y = s->v[0].y;
    list->items[idx].v[0].z = s->v[0].z;
    list->items[idx].v[1].x = s->v[1].x;
    list->items[idx].v[1].y = s->v[1].y;
    list->items[idx].v[1].z = s->v[1].z;
    list->items[idx].v[2].x = s->v[2].x;
    list->items[idx].v[2].y = s->v[2].y;
    list->items[idx].v[2].z = s->v[2].z;
    list->items[idx].v[3].x = s->v[3].x;
    list->items[idx].v[3].y = s->v[3].y;
    list->items[idx].v[3].z = s->v[3].z;
    list->items[idx].n.x = s->n.x;
    list->items[idx].n.y = s->n.y;
    list->items[idx].n.z = s->n.z;
}
// Matched
int LoadFtgPolyG4_8002407C(FtgPrimHeader* hdr, FtgSrcPolyG4* src, FtgObject* obj, int idx)
{
    if (hdr->flags_3 & 2)
    {
        SetSemiTrans(&obj->g4_28.items[idx], 1);
    }
    CopyFtgPolyG4_80024104(&obj->g4_28, src, hdr->flags_3, idx);
    return 0x50;
}
// Matched
void CopyFtgPolyG4_80024104(FtgPolyG4List* list, FtgSrcPolyG4* s, int code, int idx)
{
    list->items[idx].c[0].r = s->c[0].r;
    list->items[idx].c[0].g = s->c[0].g;
    list->items[idx].c[0].b = s->c[0].b;
    list->items[idx].c[0].code = code;
    list->items[idx].c[1].r = s->c[1].r;
    list->items[idx].c[1].g = s->c[1].g;
    list->items[idx].c[1].b = s->c[1].b;
    list->items[idx].c[0].code = code;
    list->items[idx].c[2].r = s->c[2].r;
    list->items[idx].c[2].g = s->c[2].g;
    list->items[idx].c[2].b = s->c[2].b;
    list->items[idx].c[0].code = code;
    list->items[idx].c[3].r = s->c[3].r;
    list->items[idx].c[3].g = s->c[3].g;
    list->items[idx].c[3].b = s->c[3].b;
    list->items[idx].c[0].code = code;
    list->items[idx].v[0].x = s->p[0].v.x;
    list->items[idx].v[0].y = s->p[0].v.y;
    list->items[idx].v[0].z = s->p[0].v.z;
    list->items[idx].v[1].x = s->p[1].v.x;
    list->items[idx].v[1].y = s->p[1].v.y;
    list->items[idx].v[1].z = s->p[1].v.z;
    list->items[idx].v[2].x = s->p[2].v.x;
    list->items[idx].v[2].y = s->p[2].v.y;
    list->items[idx].v[2].z = s->p[2].v.z;
    list->items[idx].v[3].x = s->p[3].v.x;
    list->items[idx].v[3].y = s->p[3].v.y;
    list->items[idx].v[3].z = s->p[3].v.z;
    list->items[idx].n[0].x = s->p[0].n.x;
    list->items[idx].n[0].y = s->p[0].n.y;
    list->items[idx].n[0].z = s->p[0].n.z;
    list->items[idx].n[1].x = s->p[1].n.x;
    list->items[idx].n[1].y = s->p[1].n.y;
    list->items[idx].n[1].z = s->p[1].n.z;
    list->items[idx].n[2].x = s->p[2].n.x;
    list->items[idx].n[2].y = s->p[2].n.y;
    list->items[idx].n[2].z = s->p[2].n.z;
    list->items[idx].n[3].x = s->p[3].n.x;
    list->items[idx].n[3].y = s->p[3].n.y;
    list->items[idx].n[3].z = s->p[3].n.z;
}
// Matched
int LoadFtgPolyFT4_80024394(FtgPrimHeader* hdr, FtgSrcPolyFT4* src, FtgObject* obj, int idx)
{
    if (hdr->flags_3 & 2)
    {
        SetSemiTrans(&obj->ft4_30.items[idx], 1);
    }
    CopyFtgPolyFT4_8002441C(&obj->ft4_30, src, hdr->flags_3, idx);
    return 0x2C;
}
// Matched
void CopyFtgPolyFT4_8002441C(FtgPolyFT4List* list, FtgSrcPolyFT4* s, int code, int idx)
{
    list->items[idx].tpage = s->tex.tpage;
    list->items[idx].clut = s->tex.clut;
    list->items[idx].u0 = s->v[0].u;
    list->items[idx].v0 = s->v[0].v;
    list->items[idx].v[0].uv = list->items[idx].u0 + (list->items[idx].v0 << 8);
    list->items[idx].u1 = s->v[1].u;
    list->items[idx].v1 = s->v[1].v;
    list->items[idx].v[1].uv = list->items[idx].u1 + (list->items[idx].v1 << 8);
    list->items[idx].u2 = s->v[2].u;
    list->items[idx].v2 = s->v[2].v;
    list->items[idx].v[2].uv = list->items[idx].u2 + (list->items[idx].v2 << 8);
    list->items[idx].u3 = s->v[3].u;
    list->items[idx].v3 = s->v[3].v;
    list->items[idx].v[3].uv = list->items[idx].u3 + (list->items[idx].v3 << 8);
    list->items[idx].c.r = 0x80;
    list->items[idx].c.g = 0x80;
    list->items[idx].c.b = 0x80;
    list->items[idx].c.code = code;
    list->items[idx].v[0].x = s->v[0].x;
    list->items[idx].v[0].y = s->v[0].y;
    list->items[idx].v[0].z = s->v[0].z;
    list->items[idx].v[1].x = s->v[1].x;
    list->items[idx].v[1].y = s->v[1].y;
    list->items[idx].v[1].z = s->v[1].z;
    list->items[idx].v[2].x = s->v[2].x;
    list->items[idx].v[2].y = s->v[2].y;
    list->items[idx].v[2].z = s->v[2].z;
    list->items[idx].v[3].x = s->v[3].x;
    list->items[idx].v[3].y = s->v[3].y;
    list->items[idx].v[3].z = s->v[3].z;
    list->items[idx].n.x = s->n.x;
    list->items[idx].n.y = s->n.y;
    list->items[idx].n.z = s->n.z;
}
// Matched
void RelocFtgPolyFT4_8002467C(FtgSrcPolyFT4* p, int reloc)
{
    RelocateTPageClut_80022AE8(&p->tex.tpage, &p->tex.clut, reloc);
}
// Matched
int LoadFtgPolyGT4_800246A0(FtgPrimHeader* hdr, FtgSrcPolyGT4* src, FtgObject* obj, int idx)
{
    if (hdr->flags_3 & 2)
    {
        SetSemiTrans(&obj->gt4_38.items[idx], 1);
    }
    CopyFtgPolyGT4_80024730(&obj->gt4_38, src, hdr->flags_3, idx);
    return 0x54;
}
// Matched
void CopyFtgPolyGT4_80024730(FtgPolyGT4List* list, FtgSrcPolyGT4* s, int code, int idx)
{
    list->items[idx].tpage = s->tex.tpage;
    list->items[idx].clut = s->tex.clut;
    list->items[idx].u0 = s->p[0].v.u;
    list->items[idx].v0 = s->p[0].v.v;
    list->items[idx].v[0].uv = list->items[idx].u0 + (list->items[idx].v0 << 8);
    list->items[idx].u1 = s->p[1].v.u;
    list->items[idx].v1 = s->p[1].v.v;
    list->items[idx].v[1].uv = list->items[idx].u1 + (list->items[idx].v1 << 8);
    list->items[idx].u2 = s->p[2].v.u;
    list->items[idx].v2 = s->p[2].v.v;
    list->items[idx].v[2].uv = list->items[idx].u2 + (list->items[idx].v2 << 8);
    list->items[idx].u3 = s->p[3].v.u;
    list->items[idx].v3 = s->p[3].v.v;
    list->items[idx].v[3].uv = list->items[idx].u3 + (list->items[idx].v3 << 8);
    list->items[idx].c[0].code = code;
    list->items[idx].c[0].r = s->c[0].r;
    list->items[idx].c[0].g = s->c[0].g;
    list->items[idx].c[0].b = s->c[0].b;
    list->items[idx].c[1].r = s->c[1].r;
    list->items[idx].c[1].g = s->c[1].g;
    list->items[idx].c[1].b = s->c[1].b;
    list->items[idx].c[2].r = s->c[2].r;
    list->items[idx].c[2].g = s->c[2].g;
    list->items[idx].c[2].b = s->c[2].b;
    list->items[idx].c[3].r = s->c[3].r;
    list->items[idx].c[3].g = s->c[3].g;
    list->items[idx].c[3].b = s->c[3].b;
    list->items[idx].v[0].x = s->p[0].v.x;
    list->items[idx].v[0].y = s->p[0].v.y;
    list->items[idx].v[0].z = s->p[0].v.z;
    list->items[idx].v[1].x = s->p[1].v.x;
    list->items[idx].v[1].y = s->p[1].v.y;
    list->items[idx].v[1].z = s->p[1].v.z;
    list->items[idx].v[2].x = s->p[2].v.x;
    list->items[idx].v[2].y = s->p[2].v.y;
    list->items[idx].v[2].z = s->p[2].v.z;
    list->items[idx].v[3].x = s->p[3].v.x;
    list->items[idx].v[3].y = s->p[3].v.y;
    list->items[idx].v[3].z = s->p[3].v.z;
    list->items[idx].n[0].x = s->p[0].n.x;
    list->items[idx].n[0].y = s->p[0].n.y;
    list->items[idx].n[0].z = s->p[0].n.z;
    list->items[idx].n[1].x = s->p[1].n.x;
    list->items[idx].n[1].y = s->p[1].n.y;
    list->items[idx].n[1].z = s->p[1].n.z;
    list->items[idx].n[2].x = s->p[2].n.x;
    list->items[idx].n[2].y = s->p[2].n.y;
    list->items[idx].n[2].z = s->p[2].n.z;
    list->items[idx].n[3].x = s->p[3].n.x;
    list->items[idx].n[3].y = s->p[3].n.y;
    list->items[idx].n[3].z = s->p[3].n.z;
}
// Matched
void RelocFtgPolyGT4_80024AB8(FtgSrcPolyGT4* p, int reloc)
{
    RelocateTPageClut_80022AE8(&p->tex.tpage, &p->tex.clut, reloc);
}
// Matched
void InitModelList_80024ADC(ModelList** out, ModelVramSlot* vram, int heap)
{
    ModelList* l;
    int i;
    l = *out = HeapAlloc_8003FC8C(0x10, (struct Pool*)heap);
    l->count_0 = CountModelVramSlots_80026600(vram);
    l->heap_4 = heap;
    l->items_8 = HeapAlloc_8003FC8C(l->count_0 * 0x70, (struct Pool*)heap);
    l->vram_C = vram;
    for (i = 0; i < l->count_0; i++)
    {
        l->items_8[i].list_0 = l;
        l->items_8[i].slot_30 = i;
        ClearModel_800266CC(&l->items_8[i]);
    }
}
// Matched
void FreeModelList_80024BB0(ModelList** list)
{
    ModelList* l = *list;
    int i;
    for (i = 0; i < l->count_0; i++)
    {
        FreeModel_80024C48(&l->items_8[i]);
    }
    HeapFree_8003FD18(l->items_8, l->heap_4);
    HeapFree_8003FD18(l, l->heap_4);
    *list = 0;
}
// Matched
void FreeModel_80024C48(Model* p)
{
    int h;
    FreeModelAltFtgs_80025AB0(p);
    ApplyModelFtgSwaps_80025C38(p, 1);
    h = p->list_0->heap_4;
    if (p->animLoaded_44 != 0)
    {
        HeapFree_8003FD18(p->animLoaded_44, h);
    }
    if (p->header_4C != 0)
    {
        HeapFree_8003FD18(p->header_4C, h);
    }
    if (p->ftg_50 != 0)
    {
        FreeFtgObjects_80021784(&p->ftg_50, p->ftgCount_3C, h);
    }
    if (p->anims_54 != 0)
    {
        FreeModelAnims_8002679C(&p->anims_54, p->animCount_3E, h);
    }
    if (p->animSet_58 != 0)
    {
        HeapFree_8003FD18(p->animSet_58, h);
    }
    if (p->mats_5C.items_4 != 0)
    {
        FreeFtgMatList_80021E24(&p->mats_5C, h);
    }
    if (p->saved_64 != 0)
    {
        HeapFree_8003FD18(p->saved_64, h);
    }
    if (p->ftg2_68 != 0)
    {
        FreeFtgObjects_80021784(&p->ftg2_68, p->ftg2Count_42, h);
    }
    if (p->swaps_6C != 0)
    {
        HeapFree_8003FD18(p->swaps_6C, h);
    }
    ClearModel_800266CC(p);
}
// Matched
Model* AcquireModel_80024D70(ModelList* p, unsigned int id)
{
    int i = FindModelIndex_80026630(p, id);
    if (i >= 0)
    {
        Model* r = &p->items_8[i];
        r->refs_3A++;
        return r;
    }
    return 0;
}
// Matched
int AreFileRequestsDone_80024DC4(Model* p)
{
    int i;
    i = 0;
    while (i < p->requestCount_4)
    {
        if (GetFileRequestStatus_8003BE30(p->requests_8[i]) != 0)
        {
            return 0;
        }
        i++;
    }
    p->requestCount_4 = 0;
    return 1;
}
// Matched
void* GetModelActorAnims_80024E38(Model* p)
{
    char* result = 0;
    ModelHeaderData* hdr = p->header_4C;
    if (hdr && hdr->offset_0)
    {
        result = (char*)hdr + hdr->offset_0 + 4;
    }
    return result;
}
// Matched
void* GetModelEffectTable_80024E64(Model* p)
{
    char* result = 0;
    ModelHeaderData* hdr = p->header_4C;
    if (hdr && hdr->offset_4)
    {
        result = (char*)hdr + hdr->offset_4;
    }
    return result;
}
// Matched
void* GetModelBaseScale_80024E90(Model* p, int n)
{
    char* r = GetModelHeaderRecord_80024FA8(p, n);
    if (r)
    {
        r += ((ModelHeaderRecord*)r)->offsets_0[0];
    }
    return r;
}
// Matched
void* GetModelBoneScale_80024EC8(Model* p, int n)
{
    char* r = GetModelHeaderRecord_80024FA8(p, n);
    if (r)
    {
        r += ((ModelHeaderRecord*)r)->offsets_0[1];
    }
    return r;
}
// Matched
void* GetModelBoneGroupLevels_80024F00(Model* p, int n)
{
    char* r = GetModelHeaderRecord_80024FA8(p, n);
    if (r)
    {
        r += ((ModelHeaderRecord*)r)->offsets_0[2];
    }
    return r;
}
// Matched
void* GetModelBoneGroupFlags_80024F38(Model* p, int n)
{
    char* r = GetModelHeaderRecord_80024FA8(p, n);
    if (r)
    {
        r += ((ModelHeaderRecord*)r)->offsets_0[3];
    }
    return r;
}
// Matched
void* GetModelFtgWeights_80024F70(Model* p, int n)
{
    char* r = GetModelHeaderRecord_80024FA8(p, n);
    if (r)
    {
        r += ((ModelHeaderRecord*)r)->offsets_0[4];
    }
    return r;
}
// Matched
char* GetModelHeaderRecord_80024FA8(Model* model, int n)
{
    char* hdr = (char*)model->header_4C;
    char* r = 0;
    int i;
    if (hdr)
    {
        int off = ((ModelHeaderData*)hdr)->records_8;
        if (off)
        {
            hdr += off;
            hdr += 8;
            for (i = 0; i < n; i++)
            {
                hdr += ((ModelHeaderRecord*)hdr)->size_14;
            }
            r = hdr;
        }
    }
    return r;
}
// Matched
void SaveModelFtgs_80024FFC(Model* p, int* ids)
{
    int n;
    int heap;
    for (n = 0; ids[n] >= 0; n++)
    {
    }
    heap = p->list_0->heap_4;
    p->savedCount_40 = n;
    p->saved_64 = HeapAlloc_8003FC8C(n * sizeof(ModelSavedFtg), (struct Pool*)heap);
    n--;
    while (n >= 0)
    {
        int id = ids[n];
        p->saved_64[n].id_0 = id;
        p->saved_64[n].ftg_4 = p->ftg_50[id];
        n--;
    }
}
// Matched
void GetSavedModelFtg_8002512C(unsigned int* out, Model* model, int id)
{
    int i;
    for (i = 0; i < model->savedCount_40; i++)
    {
        ModelSavedFtg* e = (ModelSavedFtg*)(i * 0x58 + (int)model->saved_64); // integer sum: the original adds the base second
        if (id == e->id_0)
        {
            MemCopy_800403E8(out, &e->ftg_4, 0x54);
            break;
        }
    }
}
// Matched
void GetModelFtg_800251A0(void* dst, Model* src, int a2, int idx)
{
    MemCopy_800403E8(dst, &src->ftg_50[idx], sizeof(FtgObject));
}
// Matched
void EmptyCallback_800251DC(void)
{
}
// Matched
ModelDesc* GetModelDesc_800251E4(int idx)
{
    return modelDescs_800824CC[idx];
}
// Matched
int LoadModel_80025200(ModelList* list, int id, int texSel, int animMode, int flag)
{
    ModelLoadParams params;
    FileRequestDesc req;
    int separateHeader = 1;
    int i;
    ModelDesc* desc;
    Model* model;
    ModelVramSlot* vram;
    int offset;
    int size;
    i = FindModelIndex_80026630(list, id);
    if (i >= 0)
    {
        return AreFileRequestsDone_80024DC4(&list->items_8[i]) == 0;
    }
    i = FindFreeModelIndex_8002667C(list);
    if (i >= 0)
    {
        desc = modelDescs_800824CC[id];
        model = &list->items_8[i];
        vram = list->vram_C + i;
        InitModelLoadParams_80025ED0(&params);
        if (texSel != -1)
        {
            params.flags_0 |= 3;
        }
        params.flags_0 |= 0xC;
        size = 0;
        params.model_14 = model;
        params.vram_18 = vram;
        params.desc_4 = desc;
        params.sel_8 = texSel;
        params.mode_C = animMode;
        if (texSel != -1)
        {
            separateHeader = 0;
            size += desc->header_2.size;
            size += desc->tex_6.size;
            offset = desc->header_2.offset;
        }
        else
        {
            offset = desc->ftg_A.offset;
        }
        size += desc->ftg_A.size;
        size += desc->anims_E.size;
        req.fileId_4 = desc->fileId_0;
        req.flags_0 = 0x68;
        if (flag == 1)
        {
            req.flags_0 = 0x6C;
        }
        else
        {
            req.flags_0 = 0x69;
        }
        req.offset_8 = offset;
        req.size_C = size;
        req.dest_10 = 0;
        req.params_14 = &params;
        req.paramsSize_18 = 0x3C;
        req.callback_1C = OnModelFileLoaded_80025D7C;
        AddFileRequest_80025D00(model, &req);
        if (separateHeader != 0)
        {
            InitModelLoadParams_80025ED0(&params);
            params.flags_0 = 1;
            params.model_14 = model;
            params.desc_4 = desc;
            req.fileId_4 = desc->fileId_0;
            req.flags_0 = 0x68;
            if (flag == 1)
            {
                req.flags_0 = 0x6C;
            }
            else
            {
                req.flags_0 = 0x69;
            }
            req.offset_8 = desc->header_2.offset;
            req.size_C = desc->header_2.size;
            req.params_14 = &params;
            req.paramsSize_18 = 0x3C;
            req.dest_10 = 0;
            req.callback_1C = OnModelFileLoaded_80025D7C;
            AddFileRequest_80025D00(model, &req);
        }
        model->id_38 = id;
        return 1;
    }
    return 2;
}
#if 0
// Not matched (5 lines): the pointer-add form below fixes the &b scheduling and the v0/v1 choice, but gcc then folds
// k*2 into idx*4 + 0x14 instead of keeping (e[9] + k) * 2. The int form ((k + e[9]) * 2 + (int)e) keeps the sum but
// misplaces &b and the sum register (8 lines). Tried: operand orders, temporaries for e[9]/k, k/idx types, e[k + 1]
// double reads, statement order, shifts instead of *2; permuter 1500 iters
int LoadModelAnim_80025440(Model* p, int idx, int flag)
{
    ModelLoadParams b;
    FileRequestDesc c;
    unsigned short* e;
    unsigned short* t;
    int u;
    int v;
    int k;
    unsigned char* f = p->animLoaded_44 + idx;
    if (*f == 0)
    {
        k = idx * 2 + 10;
        e = (unsigned short*)modelDescs_800824CC[p->id_38];
        t = e;
        t += e[9];
        t += k;
        u = t[0];
        v = t[1];
        *f = 1;
        InitModelLoadParams_80025ED0(&b);
        b.flags_0 = 0x10;
        b.model_14 = p;
        b.desc_4 = (ModelDesc*)e;
        b.animIdx_10 = idx;
        c.flags_0 = 0x68;
        if (flag != 0)
        {
            c.flags_0 = 0x6C;
        }
        else
        {
            c.flags_0 = 0x69;
        }
        c.fileId_4 = e[0];
        c.offset_8 = u;
        c.size_C = v;
        c.dest_10 = 0;
        c.params_14 = &b;
        c.paramsSize_18 = 0x3C;
        c.callback_1C = OnModelFileLoaded_80025D7C;
        AddFileRequest_80025D00(p, &c);
        return 1;
    }
    return AreFileRequestsDone_80024DC4(p) == 0;
}
#endif
INCLUDE_ASM(LoadModelAnim_80025440);
// Matched
void FreeModelAnim_8002556C(Model* p, int idx)
{
    if (((char*)p->animLoaded_44)[idx])
    {
        FreeModelAnimData_800269C4(p->anims_54, p->animCount_3E, idx, p->list_0->heap_4);
        p->animLoaded_44[idx] = 0;
    }
}
// Matched
int IsModelAnimLoaded_800255D8(Model* p, int idx)
{
    return ((char*)p->animLoaded_44)[idx] != 0;
}
// Matched
int LoadModelListTextures_800255F0(ModelList* list, int id, int sel)
{
    ModelLoadParams params;
    FileRequestDesc req;
    Model* model = list->items_8;
    ModelVramSlot* vram = list->vram_C;
    ModelDesc* desc = modelDescs_800824CC[id];
    InitModelLoadParams_80025ED0(&params);
    params.flags_0 = 2;
    params.sel_8 = sel;
    req.flags_0 = 0x69;
    params.model_14 = model;
    params.vram_18 = vram;
    params.desc_4 = desc;
    req.fileId_4 = desc->fileId_0;
    req.offset_8 = desc->tex_6.offset;
    req.size_C = desc->tex_6.size;
    req.dest_10 = 0;
    req.params_14 = &params;
    req.paramsSize_18 = 0x3C;
    req.callback_1C = OnModelFileLoaded_80025D7C;
    AddFileRequest_80025D00(model, &req);
    return 1;
}
// Matched
int LoadAllModelAnims_800256B8(ModelList* list, int id)
{
    ModelLoadParams params;
    FileRequestDesc req;
    Model* model = &list->items_8[FindModelIndex_80026630(list, id)];
    ModelDesc* desc = modelDescs_800824CC[model->id_38];
    InitModelLoadParams_80025ED0(&params);
    params.flags_0 = 8;
    params.model_14 = model;
    params.mode_C = 3;
    params.desc_4 = desc;
    req.flags_0 = 0x69;
    req.fileId_4 = desc->fileId_0;
    req.offset_8 = desc->anims_E.offset;
    req.size_C = desc->anims_E.size;
    req.dest_10 = 0;
    req.params_14 = &params;
    req.paramsSize_18 = 0x3C;
    req.callback_1C = OnModelFileLoaded_80025D7C;
    AddFileRequest_80025D00(model, &req);
    return 1;
}
// Matched
int LoadModelAnimSet_80025780(Model* p, int idx, int flag)
{
    ModelLoadParams params;
    FileRequestDesc req;
    ModelDesc* desc;
    char* t;
    int offset;
    int size;
    FreeModelAnimSet_80025884(p);
    desc = modelDescs_800824CC[p->id_38];
    t = (char*)desc + (desc->animCount_12 * 6 + 0x14);
    offset = ((unsigned short*)t)[idx * 2 + 1];
    size = ((unsigned short*)t)[idx * 2 + 2];
    InitModelLoadParams_80025ED0(&params);
    params.flags_0 = 0x20;
    params.model_14 = p;
    params.desc_4 = desc;
    req.flags_0 = 0x68;
    if (flag != 0)
    {
        req.flags_0 = 0x6C;
    }
    else
    {
        req.flags_0 = 0x69;
    }
    req.fileId_4 = desc->fileId_0;
    req.offset_8 = offset;
    req.size_C = size;
    req.dest_10 = 0;
    req.params_14 = &params;
    req.paramsSize_18 = 0x3C;
    req.callback_1C = OnModelFileLoaded_80025D7C;
    AddFileRequest_80025D00(p, &req);
    return 1;
}
// Matched
void FreeModelAnimSet_80025884(Model* p)
{
    int* list = p->animSet_58;
    if (list)
    {
        int heap = p->list_0->heap_4;
        int n = list[0];
        int i;
        for (i = 0; i < n; i++)
        {
            int id = p->animSet_58[i + 1];
            if (id >= 0)
            {
                FreeModelAnim_8002556C(p, id);
            }
        }
        HeapFree_8003FD18(p->animSet_58, heap);
        p->animSet_58 = 0;
    }
}
// Matched
int IsAnimInModelAnimSet_80025924(Model* p, int id)
{
    int* list = p->animSet_58;
    int i;
    int n;
    if (list != 0)
    {
        n = list[0];
        for (i = 0; i < n; i++)
        {
            if (id == list[i + 1])
            {
                return 1;
            }
        }
    }
    return 0;
}
// Matched
int LoadModelAltFtgs_80025974(Model* p, int idx, int flag)
{
    ModelLoadParams params;
    FileRequestDesc req;
    ModelDesc* desc;
    char* t;
    int offset;
    int size;
    ModelList* list;
    FreeModelAltFtgs_80025AB0(p);
    desc = modelDescs_800824CC[p->id_38];
    t = (char*)desc + (desc->animCount_12 * 6 + 0x14);
    t += *(unsigned short*)t * 4 + 2;
    list = p->list_0;
    offset = ((unsigned short*)t)[idx * 2 + 1];
    size = ((unsigned short*)t)[idx * 2 + 2];
    InitModelLoadParams_80025ED0(&params);
    params.flags_0 = 0x40;
    params.model_14 = p;
    params.vram_18 = list->vram_C + p->slot_30;
    params.sel_8 = p->texSel_34;
    params.desc_4 = desc;
    req.flags_0 = 0x68;
    if (flag != 0)
    {
        req.flags_0 = 0x6C;
    }
    else
    {
        req.flags_0 = 0x69;
    }
    req.fileId_4 = desc->fileId_0;
    req.offset_8 = offset;
    req.size_C = size;
    req.dest_10 = 0;
    req.params_14 = &params;
    req.paramsSize_18 = 0x3C;
    req.callback_1C = OnModelFileLoaded_80025D7C;
    AddFileRequest_80025D00(p, &req);
    return 1;
}
// Matched
void FreeModelAltFtgs_80025AB0(Model* p)
{
    int h = p->list_0->heap_4;
    if (p->ftg2_68)
    {
        FreeFtgObjects_80021784(&p->ftg2_68, p->ftg2Count_42, h);
        p->ftg2Count_42 = 0;
        p->ftg2_68 = 0;
    }
    if (p->swaps_6C)
    {
        HeapFree_8003FD18(p->swaps_6C, h);
        p->swapCount_43 = 0;
        p->swaps_6C = 0;
    }
}
// Matched
void GetModelAltFtg_80025B20(void* dst, Model* src, int idx)
{
    MemCopy_800403E8(dst, &src->ftg2_68[idx], sizeof(FtgObject));
}
// Matched
void SetModelFtg_80025B5C(Model* p, int idx, int sel)
{
    FtgObject tmp;
    if (idx == sel)
    {
        GetSavedModelFtg_8002512C((unsigned int*)&tmp, p, idx);
    }
    else if (sel < p->ftgCount_3C)
    {
        GetModelFtg_800251A0(&tmp, p, idx, sel);
    }
    else
    {
        GetModelAltFtg_80025B20(&tmp, p, sel - p->ftgCount_3C);
    }
    p->ftg_50[idx] = tmp;
}
// Matched
void ApplyModelFtgSwaps_80025C38(Model* p, int flag)
{
    int i;
    for (i = 0; i < p->savedCount_40; i++)
    {
        ModelSavedFtg* e = (ModelSavedFtg*)(i * 0x58 + (int)p->saved_64); // integer sum, as above
        SetModelFtg_80025B5C(p, e->id_0, e->id_0);
    }
    if (flag)
    {
        for (i = 0; i < p->swapCount_43; i++)
        {
            ModelFtgSwap* s = (ModelFtgSwap*)(i * 4 + (int)p->swaps_6C);
            SetModelFtg_80025B5C(p, s->dst_0, s->src_2);
        }
    }
}
// Matched
int AddFileRequest_80025D00(Model* model, FileRequestDesc* req)
{
    if (model->requestCount_4 < 10)
    {
        req->offset_8 <<= 11;
        req->size_C <<= 11;
        model->requests_8[model->requestCount_4] = QueueFileRequest_8003BC84(req);
        model->requestCount_4 += 1;
        return 1;
    }
    return 0;
}
// Matched
void OnModelFileLoaded_80025D7C(int* arg, int data)
{
    ModelLoadParams* p = (ModelLoadParams*)arg;
    if (p->flags_0 & 1)
    {
        p->header_1C = (ModelHeaderSection*)data;
        data += p->desc_4->header_2.size << 11;
    }
    if (p->flags_0 & 2)
    {
        p->tim_20 = (int*)data;
        data += p->desc_4->tex_6.size << 11;
    }
    if (p->flags_0 & 4)
    {
        p->ftg_24 = (int*)data;
        data += p->desc_4->ftg_A.size << 11;
    }
    if (p->flags_0 & 8)
    {
        p->anims_28 = (ModelAnimSection*)data;
        data += p->desc_4->anims_E.size << 11;
    }
    if (p->flags_0 & 0x10)
    {
        p->anim_2C = (char*)data;
    }
    if (p->flags_0 & 0x20)
    {
        p->animSet_30 = (ModelAnimSetSection*)data;
    }
    if (p->flags_0 & 0x40)
    {
        p->flags_0 |= 0x80;
        p->extra_38 = (unsigned char*)(data + ((int*)data)[1]);
        p->flags_0 |= 0x40;
        p->ftg2_34 = (int*)(data + ((int*)data)[2]);
        p->flags_0 |= 2;
        p->tim_20 = (int*)(data + ((int*)data)[3]);
    }
    ParseModelFile_80025F14(p);
}
// Matched
void InitModelLoadParams_80025ED0(ModelLoadParams* p)
{
    p->sel_8 = -1;
    p->flags_0 = 0;
    p->desc_4 = 0;
    p->mode_C = 2;
    p->animIdx_10 = 0;
    p->model_14 = 0;
    p->vram_18 = 0;
    p->header_1C = 0;
    p->tim_20 = 0;
    p->ftg_24 = 0;
    p->anims_28 = 0;
    p->anim_2C = 0;
    p->ftg2_34 = 0;
    p->extra_38 = 0;
}
// Matched
void ParseModelFile_80025F14(ModelLoadParams* params)
{
    if (params->flags_0 & 1)
    {
        LoadModelHeader_80026014(params);
    }
    if (params->flags_0 & 2)
    {
        LoadModelTextures_8002607C(params);
    }
    if (params->flags_0 & 4)
    {
        LoadModelFtg_800260FC(params);
    }
    if (params->flags_0 & 8)
    {
        LoadModelAnims_800261C8(params);
    }
    if (params->flags_0 & 0x10)
    {
        LoadSingleModelAnim_800263CC(params);
    }
    if (params->flags_0 & 0x20)
    {
        LoadModelAnimSetSection_80026410(params);
    }
    if (params->flags_0 & 0x40)
    {
        LoadModelAltFtgSection_8002651C(params);
    }
    if (params->flags_0 & 0x80)
    {
        LoadModelFtgSwaps_8002659C(params);
    }
}
// Matched
void LoadModelHeader_80026014(ModelLoadParams* params)
{
    ModelHeaderSection* q = params->header_1C;
    Model* p = params->model_14;
    int h = p->list_0->heap_4;
    int n = q->size_0;
    void* r;
    p->headerSize_48 = n;
    r = HeapAlloc_8003FC8C(n, (struct Pool*)h);
    p->header_4C = r;
    MemCopy_800403E8(r, params->header_1C->data_4, n);
}
// Matched
void LoadModelTextures_8002607C(ModelLoadParams* params)
{
    if (params->sel_8 != -1)
    {
        Model* p = params->model_14;
        LoadTiyTimsRelocated_80028FDC(0, 0, 0, (int)params->tim_20, GetTiyFileCount_80028E68(params->tim_20), (int)params->vram_18->reloc_4, params->sel_8);
        p->texSel_34 = params->sel_8;
    }
}
// Matched
void LoadModelFtg_800260FC(ModelLoadParams* params)
{
    Model* p = params->model_14;
    int* list = params->ftg_24;
    ModelVramSlot* v = params->vram_18;
    int h = p->list_0->heap_4;
    p->ftgCount_3C = GetFtgObjectCount_80021738(list);
    AllocFtgObjects_80021744(&p->ftg_50, p->ftgCount_3C, h);
    LoadFtgObjects_80021824(params->ftg_24, p->ftg_50, p->ftgCount_3C, h, (int)v->reloc_4);
    if (GetFtgMatCount_80021DE4(params->ftg_24) != 0)
    {
        AllocFtgMatList_80021DF0(&p->mats_5C, GetFtgMatCount_80021DE4(params->ftg_24), h);
        LoadFtgMatList_80021E4C(params->ftg_24, &p->mats_5C, GetFtgMatCount_80021DE4(params->ftg_24));
    }
}
// Matched
void LoadModelAnims_800261C8(ModelLoadParams* params)
{
    Model* p = params->model_14;
    int h = p->list_0->heap_4;
    int i;
    int j;
    int mode;
    p->animCount_3E = params->desc_4->animCount_12;
    if (p->anims_54 == 0)
    {
        AllocModelAnims_80026730(&p->anims_54, p->animCount_3E, h);
    }
    if (p->animLoaded_44 != 0)
    {
        HeapFree_8003FD18(p->animLoaded_44, h);
    }
    p->animLoaded_44 = HeapAlloc_8003FC8C(p->animCount_3E, (struct Pool*)h);
    for (i = 0; i < p->animCount_3E; i++)
    {
        mode = params->mode_C;
        if (mode == 0)
        {
            if (i == 0)
            {
                p->animLoaded_44[0] = 1;
            }
            else
            {
                p->animLoaded_44[i] = 0;
            }
        }
        else if (mode == 1)
        {
            if (i == 0)
            {
                p->animLoaded_44[0] = 1;
            }
            else if (i == 1)
            {
                p->animLoaded_44[1] = 1;
            }
            else
            {
                p->animLoaded_44[i] = 0;
            }
        }
        else if (mode == 3)
        {
            if (i == 0)
            {
                p->animLoaded_44[0] = 0;
            }
            else if (i == 1)
            {
                p->animLoaded_44[1] = 0;
            }
            else
            {
                p->animLoaded_44[i] = *(unsigned char*)&params->desc_4->animFlags_14[i];
            }
        }
        else
        {
            p->animLoaded_44[i] = *(unsigned char*)&params->desc_4->animFlags_14[i];
        }
    }
    for (i = 0, j = 0; i < p->animCount_3E; i++)
    {
        if ((&params->desc_4->animFlags_14[0])[i] != 0) // indexed through the decayed pointer, as the original
        {
            if (p->animLoaded_44[i] != 0)
            {
                LoadModelAnimData_80026A8C(&p->anims_54[i], (int)params->anims_28 + (&params->anims_28->offsets_4[0])[j], h);
            }
            j++;
        }
    }
}
// Matched
void LoadSingleModelAnim_800263CC(ModelLoadParams* p)
{
    ModelList* l;
    Model* q = p->model_14;
    l = q->list_0;
    LoadModelAnimData_80026A8C(&q->anims_54[p->animIdx_10], (int)p->anim_2C, l->heap_4);
}
// Matched
void LoadModelAnimSetSection_80026410(ModelLoadParams* params)
{
    ModelAnimSetSection* q = params->animSet_30;
    Model* p = params->model_14;
    int n = q->count_0;
    int h = p->list_0->heap_4;
    int* list = HeapAlloc_8003FC8C((n + 1) * 4, (struct Pool*)h);
    int i;
    int id;
    int src;
    p->animSet_58 = list;
    list[0] = n;
    for (i = 0; i < n; i++)
    {
        id = q->items_4[i].id;
        src = (int)q + q->items_4[i].offset;
        if (p->animLoaded_44[id] == 0)
        {
            p->animSet_58[i + 1] = id;
            p->animLoaded_44[id] = 1;
            LoadModelAnimData_80026A8C(&p->anims_54[id], src, h);
        }
        else
        {
            p->animSet_58[i + 1] = -1;
        }
    }
}
// Matched
void LoadModelAltFtgSection_8002651C(ModelLoadParams* params)
{
    Model* p = params->model_14;
    int* list = params->ftg2_34;
    ModelVramSlot* v = params->vram_18;
    int heap = p->list_0->heap_4;
    p->ftg2Count_42 = GetFtgObjectCount_80021738(list);
    AllocFtgObjects_80021744(&p->ftg2_68, p->ftg2Count_42, heap);
    LoadFtgObjects_80021824(params->ftg2_34, p->ftg2_68, p->ftg2Count_42, heap, (int)v->reloc_4);
}
// Matched
void LoadModelFtgSwaps_8002659C(ModelLoadParams* params)
{
    unsigned char* q = params->extra_38;
    Model* p = params->model_14;
    int h = p->list_0->heap_4;
    void* r;
    p->swapCount_43 = *q;
    q += 4;
    r = HeapAlloc_8003FC8C(p->swapCount_43 << 2, (struct Pool*)h);
    p->swaps_6C = r;
    MemCopy_800403E8(r, q, p->swapCount_43 << 2);
}
// Matched
int CountModelVramSlots_80026600(ModelVramSlot* p)
{
    int n = 0;
    if (p->id_2 != -1)
    {
        do
        {
            p++;
            n++;
        } while (p->id_2 != -1);
    }
    return n;
}
// Matched
int FindModelIndex_80026630(ModelList* p, unsigned int id)
{
    int i;
    for (i = 0; i < p->count_0; i++)
    {
        if (p->items_8[i].id_38 == id)
        {
            return i;
        }
    }
    return -1;
}
// Matched
int FindFreeModelIndex_8002667C(ModelList* p)
{
    int i;
    for (i = 0; i < p->count_0; i++)
    {
        if (p->items_8[i].id_38 == 0xFFFF)
        {
            return i;
        }
    }
    return -1;
}
// Matched
void ClearModel_800266CC(Model* p)
{
    p->id_38 = 0xFFFF;
    p->requestCount_4 = 0;
    p->texSel_34 = 0;
    p->refs_3A = 0;
    p->ftgCount_3C = 0;
    p->animCount_3E = 0;
    p->savedCount_40 = 0;
    p->ftg2Count_42 = 0;
    p->swapCount_43 = 0;
    p->animLoaded_44 = 0;
    p->headerSize_48 = 0;
    p->header_4C = 0;
    p->ftg_50 = 0;
    p->anims_54 = 0;
    p->animSet_58 = 0;
    p->mats_5C.count_0 = 0;
    p->mats_5C.items_4 = 0;
    p->saved_64 = 0;
    p->ftg2_68 = 0;
    p->swaps_6C = 0;
}
// Matched
int GetModelAnimCount_80026724(int* p)
{
    return p[0];
}
// Matched
void AllocModelAnims_80026730(ModelAnim** out, int count, int heap)
{
    ModelAnim* p = HeapAlloc_8003FC8C(count * 28, (struct Pool*)heap);
    int i;
    *out = p;
    for (i = 0; i < count; i++)
    {
        p[i].cues_10 = 0;
        p[i].basePose_14 = 0;
        p[i].frames_18 = 0;
    }
}
// Matched
void FreeModelAnims_8002679C(ModelAnim** anims, int n, int heap)
{
    ModelAnim* arr;
    int i;
    if (*anims)
    {
        arr = *anims;
        for (i = 0; i < n; i++)
        {
            if (arr[i].cues_10)
            {
                HeapFree_8003FD18(arr[i].cues_10, heap);
            }
            if (arr[i].basePose_14)
            {
                HeapFree_8003FD18(arr[i].basePose_14, heap);
            }
            if (arr[i].frames_18)
            {
                HeapFree_8003FD18(arr[i].frames_18, heap);
            }
        }
        HeapFree_8003FD18(arr, heap);
        *anims = 0;
    }
}
// Matched
void LoadModelAnimSection_80026870(ModelAnim** out, int section, int heap)
{
    int r = GetModelAnimCount_80026724((int*)section);
    AllocModelAnims_80026730(out, r, heap);
    LoadModelAnimsMasked_800268E8(out[0], section, r, heap, -1);
}
// Matched
void LoadModelAnimsMasked_800268E8(ModelAnim* anims, int section, int n, int h, int mask)
{
    int* q = (int*)section;
    int i;
    for (i = 0; i < n; i++, anims++)
    {
        int bit = 1 << i;
        if ((mask & bit) && anims->basePose_14 == 0 && anims->frames_18 == 0)
        {
            LoadModelAnimData_80026A8C(anims, section + q[i + 1], h);
        }
    }
}
// Matched
void FreeModelAnimData_800269C4(ModelAnim* anims, int n, int sel, int h)
{
    ModelAnim* p = anims;
    int i;
    for (i = 0; i < n; i++, p++)
    {
        if (sel == i && p->basePose_14 != 0 && p->frames_18 != 0)
        {
            if (p->cues_10 != 0)
            {
                HeapFree_8003FD18(p->cues_10, h);
            }
            HeapFree_8003FD18(p->basePose_14, h);
            HeapFree_8003FD18(p->frames_18, h);
            p->cues_10 = 0;
            p->basePose_14 = 0;
            p->frames_18 = 0;
        }
    }
}
// Matched
void LoadModelAnimData_80026A8C(ModelAnim* anim, int src, int heap)
{
    int hasDivisor = 0;
    int hasCues = hasDivisor;
    unsigned int n;
    unsigned int m;
    unsigned short* s;
    unsigned short* d;
    unsigned int i;
    unsigned int j;
    int r;
    int k;
    anim->frameCount_0 = ((ModelAnimFile*)src)->frameCount_0;
    n = anim->frameCount_0;
    anim->boneCount_4 = ((ModelAnimFile*)src)->boneCount_4;
    m = anim->boneCount_4;
    if ((int)n < 0)
    {
        n &= 0x7FFFFFFF;
        s = (unsigned short*)(((int*)src) + 3);
        anim->frameCount_0 = n;
        anim->divisor_8 = ((ModelAnimFile*)src)->divisor_8;
        hasDivisor = 1;
    }
    else
    {
        anim->divisor_8 = 0x20;
        s = (unsigned short*)(((int*)src) + 2);
    }
    if ((int)m < 0)
    {
        m &= 0x7FFFFFFF;
        hasCues = 1;
    }
    else
    {
        anim->cueCount_C = 0;
    }
    anim->basePose_14 = HeapAlloc_8003FC8C(m * 6, (struct Pool*)heap);
    anim->frames_18 = HeapAlloc_8003FC8C((m + 2) * (n << 1) * 3, (struct Pool*)heap);
    d = anim->basePose_14;
    for (i = 0; i < m; i++)
    {
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
    }
    d = anim->frames_18;
    for (j = 0; j < n; j++)
    {
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        for (i = 0; i < m; i++)
        {
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
        }
    }
    if (hasCues)
    {
        r = m * 6 + 8;
        r += (m * 6 + 0xC) * n;
        if (hasDivisor)
        {
            r += 4;
        }
        s = (unsigned short*)((char*)((int*)src) + r);
        if (r & 3)
        {
            r += 2;
            s = (unsigned short*)((char*)((int*)src) + r);
        }
        anim->cueCount_C = *(int*)s;
        s += 2;
        anim->cues_10 = HeapAlloc_8003FC8C(anim->cueCount_C * 8, (struct Pool*)heap);
        k = 0;
        while (k < anim->cueCount_C)
        {
            anim->cues_10[k].frame_0 = s[0];
            anim->cues_10[k].kind_2 = s[1];
            anim->cues_10[k].arg_4 = s[2];
            anim->cues_10[k].arg_6 = s[3];
            k++;
            s += 4;
        }
    }
}
// Matched
int GetRecordTableCount_80026D6C(int* p)
{
    return p[0];
}
// Matched
void AllocRecordTables_80026D78(struct_12** out, int count, int heap)
{
    struct_12* p = HeapAlloc_8003FC8C(count * 12, heap);
    int i;
    for (i = 0; i < count; i++)
    {
        p[i].field_0 = 0;
        p[i].field_4 = 0;
        p[i].field_8 = 0;
    }
    *out = p;
}
// Matched
void FreeRecordTables_80026DE8(struct_12** tables, int n, int h)
{
    struct_12* p = *tables;
    int i;
    for (i = 0; i < n; i++, p++)
    {
        if (p->field_8 != 0)
        {
            HeapFree_8003FD18(p->field_8, h);
        }
    }
    HeapFree_8003FD18(*tables, h);
    *tables = 0;
}
// Matched
void LoadRecordTables_80026E74(struct_12* tables, int* file, int heap)
{
    int i;
    for (i = 0; i < GetRecordTableCount_80026D6C(file); i++)
    {
        LoadRecordTable_80026EF8(tables, (unsigned short*)((char*)file + file[i + 1]), heap);
        tables++;
    }
}
typedef struct
{
    unsigned short a;
    unsigned short b;
    unsigned short c;
    unsigned short d;
} struct_4h;
// Matched
void LoadRecordTable_80026EF8(struct_12* p, unsigned short* s, int heap)
{
    unsigned short* d;
    int i;
    p->field_0 = *(int*)s;
    s += 2;
    p->field_4 = *(int*)s;
    s += 2;
    d = HeapAlloc_8003FC8C(p->field_0 * 8, heap);
    p->field_8 = (int)d;
    for (i = 0; i < p->field_0; i++)
    {
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
        d[3] = s[3];
        d += 4;
        s += 4;
    }
}
typedef struct
{
    int pos[3];
    int mapIdx;
} struct_80091C78;
extern struct_80091C78 savedLevantPos_80091C78;
extern int gameStartMode_800B1DC8;
extern int mapHeap_80091C68;
// Matched
void InitMapState_80026FAC(void)
{
    ListInit_8003FDB0(&mapHeap_80091C68);
    ListInit_8003FDB0(&areaHeap_80091C20);
    ListInit_8003FDB0(&eventHeap_80091C10);
    ListInit_8003FDB0(&dword_80091C48);
    loadFade_80091C30[0] = 0x3A;
    loadFade_80091C30[1] = 0;
    loadFade_80091C30[2] = 0;
    loadFade_80091C30[3] = -1;
    mapState_8008B500.nMeshes_4 = 0;
    mapState_8008B500.f8_8 = 0;
    mapState_8008B500.meshes_C = 0;
    mapState_8008B500.mesh_28 = 0;
    mapState_8008B500.ftgCount_38 = 0;
    mapState_8008B500.ftg_3C = 0;
    tileAnim_8008D648.count_0 = 0;
    tileAnim_8008D648.field_4 = 0;
    tileAnim_8008D648.field_8 = 0;
    tileAnim_8008D648.items_C = 0;
    tileAnim_8008D648.field_4 = 0;
    tileAnim_8008D648.field_8 = 0;
    tileAnim_8008D648.listCount_10 = 0;
    tileAnim_8008D648.lists_14 = 0;
    tileAnim_8008D648.pairs_18 = 0;
    currentAreaMap_80091C88 = -1;
    currentArea_80091C44 = -1;
    mapAreas_80082674 = 0;
    useSavedLevantPos_80091C98 = 0;
    useMapStartPos_80091C94 = 0;
    dword_80091C5C = 1;
    dword_80091C58 = 1;
    dword_80091C90 = 0;
    freeActorModels_80091CA0 = 0;
    forceMapReload_80091C9C = 0;
    dword_80091C8C = 0;
    savedLevantPos_80091C78.mapIdx = -1;
    mapStartMode_80091C54 = gameStartMode_800B1DC8;
    areaLoadIds_80091CB8[7] = -1;
    areaLoadIds_80091CB8[6] = -1;
    areaLoadIds_80091CB8[5] = -1;
    areaLoadIds_80091CB8[4] = -1;
    areaLoadIds_80091CB8[3] = -1;
    areaLoadIds_80091CB8[2] = -1;
    areaLoadIds_80091CB8[1] = -1;
    areaPreload_80091C40[0] = -1;
    areaLoadIds_80091CB8[0] = -1;
    areaPreload_80091C40[1] = -1;
    areaPreloading_80082678 = 0;
    InitActors_8001D378();
}
extern int mapCallback_80091CB4;
extern EventNode* dword_800B1DA8;
extern void FreeActors_8001D3C4(int a0);
extern void FreeLevantAnimSet_800AC73C(void);
extern void FreeAllEventData_800A54A0(void);
extern void StopAllEventScripts_800A58B4(void);
extern void ClearFieldMinions_800A7784(void);
extern void ResetEncounter_800A170C(void);
extern void ClearEnemySlots_800A1794(void);
// Matched
void UnloadMap_80027118(void)
{
    areaLoadIds_80091CB8[7] = -1;
    areaLoadIds_80091CB8[6] = -1;
    areaLoadIds_80091CB8[5] = -1;
    areaLoadIds_80091CB8[4] = -1;
    areaLoadIds_80091CB8[3] = -1;
    areaLoadIds_80091CB8[2] = -1;
    areaLoadIds_80091CB8[1] = -1;
    areaPreload_80091C40[0] = -1;
    areaLoadIds_80091CB8[0] = -1;
    areaPreload_80091C40[1] = -1;
    CancelAreaPreload_8002741C();
    areaPreloading_80082678 = 0;
    levantAnimSet_80091C74 = -1;
    mapCallback_80091CB4 = 0;
    currentAreaMap_80091C88 = -1;
    mapJustLoaded_80082668 = 0;
    mapHasCode_8008266C = 0;
    if (dword_80091C8C == 0)
    {
        StopAllEventEntries_80043B40(dword_800B1DA8);
        StopAllEventEntries_80043B40(eventEntities_8008D400);
    }
    FreeLevantAnimSet_800AC73C();
    StopAllEventEntries_80043B40(messageWindowTask_8008D640);
    StopAllEventEntries_80043B40(enemyAiTasks_8008D49C);
    StopAllEventEntries_80043B40(encounterTask_8008D674);
    StopAllEventEntries_80043B40(fileRequestTasks_8008D488);
    FreeAllEventData_800A54A0();
    StopAllEventScripts_800A58B4();
    FreeActors_8001D3C4(freeActorModels_80091CA0);
    ClearFieldMinions_800A7784();
    ResetEncounter_800A170C();
    ClearEnemySlots_800A1794();
    ListFreeAll_8003FEC8(&eventHeap_80091C10);
    ListFreeAll_8003FEC8(&mapHeap_80091C68);
    if (!(unknownFlags_8008D678 & 0x20000))
    {
        ListFreeAll_8003FEC8(&dword_80091C48);
    }
}
// Matched
void FreeMapArea_8002728C(void)
{
    currentArea_80091C44 = -1;
    ListFreeAll_8003FEC8(&areaHeap_80091C20);
}
// Matched
void SetCurrentArea_800272BC(int a0, int a1)
{
    currentAreaMap_80091C88 = a0;
    currentArea_80091C44 = a1;
}
#if 0
// Not matched (close)
int IsMapLoading_800272D0(void)
{
    int* a = mapLoaderTask_800B1DC4[0x24 / 4];
    int* b = areaLoaderTask_800B1DB8[0x24 / 4];
    if (*a != 0)
    {
        return 1;
    }
    if (*b == 0)
    {
        return 0;
    }
    return 1;
}
#endif
// Matched
int IsMapLoading_800272D0(void)
{
    int* a = mapLoaderTask_800B1DC4[9];
    int* b = areaLoaderTask_800B1DB8[9];
    if (a[0] != 0 || b[0] != 0)
    {
        return 1;
    }
    return 0;
}
// Matched
void RequestAreaReload_80027314(void)
{
    areaReload_80082670 = 1;
    word_8008B862 = -1;
}
// Matched
int RequestAreaPreload_80027330(short a0)
{
    if (areaPreloading_80082678 == 0)
    {
        areaPreload_80091C40[0] = a0;
        return 1;
    }
    return 0;
}
// Matched
int UsePreloadedArea_80027358(int id)
{
    int* task;
    if (areaPreloading_80082678 == 1)
    {
        if (areaPreload_80091C40[0] != id)
        {
            pendingArea_8008B860 = id;
            return 0;
        }
        task = areaLoaderTask_800B1DB8[9];
        if (GetFileRequestStatus_8003BE30(task[1]) != 3)
        {
            return 0;
        }
        FreeMapArea_8002728C();
        ConsumeFileRequest_8003BFD0(task[1], 0);
        InitRoomCamera_80028DC0();
        saveData_8008B570.mapId_2E4[3].field_0 = id;
        saveData_8008B570.mapId_2E4[3].field_2 = id;
        areaPreloading_80082678 = 0;
        return 1;
    }
    pendingArea_8008B860 = id;
    return 0;
}
// Matched
void CancelAreaPreload_8002741C(void)
{
    int* task;
    if (areaPreloading_80082678 == 1)
    {
        task = areaLoaderTask_800B1DB8[9];
        CancelFileRequest_8003C060(task[1]);
        areaPreloading_80082678 = 0;
        task[0] = 0;
    }
}
// Matched
void SetLoadFadeFlag_80027478(int mask, int set)
{
    int f;
    int code;
    if (set)
    {
        loadFade_80091C30[2] |= mask;
    }
    else
    {
        loadFade_80091C30[2] &= ~mask;
    }
    f = loadFade_80091C30[2];
    if (f && !(f & 1))
    {
        code = 0;
        if (!(f & 0x40))
        {
            if (loadFade_80091C30[0] & f)
            {
                code = 1;
            }
            else if (loadFade_80091C30[1] & f)
            {
                code = 2;
            }
        }
        loadFade_80091C30[2] |= 1;
        SetFadeMode_8001C19C(code, 0x20);
    }
}
// Matched
int UpdateLoadFade_80027540(void)
{
    int* g = loadFade_80091C30;
    if (g[2] & 0x40)
    {
        return 1;
    }
    if (g[2] & 1)
    {
        if (g[2] == 1 && IsFadeDone_8001C2FC())
        {
            g[3] = 2;
            g[2] &= ~1;
            return 1;
        }
        return 0;
    }
    if (g[3] > 0)
    {
        g[3]--;
        if (g[3] <= 0)
        {
            SetFadeMode_8001C19C(3, 0);
        }
    }
    return 1;
}
// Matched
void AllocMapWallFlags_800275E8(unsigned char** out, int count, int heap)
{
    unsigned char* p;
    unsigned char* q;
    int i;
    if (count != 0)
    {
        p = ListAlloc_8003FDC0(heap, count);
        *out = p;
        q = p;
        for (i = 0; i < count; i++)
        {
            q[i] = 1;
        }
    }
}
// Matched
int* LoadMapSpawns_80027650(int* file, int unused, int h)
{
    int* src;
    int (*d)[4];
    int n;
    int i;
    MapList16* g = &mapSpawns_80091C60;
    file += 1;
    n = *file++;
    src = file;
    g->count_0 = n;
    if (n != 0)
    {
        d = ListAlloc_8003FDC0(h, n * 16);
        g->items_4 = d;
        for (i = 0; i < g->count_0; i++)
        {
            (*d)[0] = src[0];
            (*d)[1] = src[1];
            (*d)[2] = src[2];
            (*d)[3] = src[3];
            d++;
            src += 4;
        }
    }
    return src;
}
// Matched
void LoadMapFtg_80027708(int* file, int heap)
{
    int r = GetFtgObjectCount_80021738(file);
    mapState_8008B500.ftgCount_38 = r;
    if (r != 0)
    {
        AllocFtgObjects_80021744(&mapState_8008B500.ftg_3C, r, heap);
        LoadFtgObjects_80021824(file, mapState_8008B500.ftg_3C, mapState_8008B500.ftgCount_38, heap, 0);
    }
}
// Matched
void LoadTileSets_80027778(int* data, int heap)
{
    struct_27778* arr;
    unsigned int i;
    int j;
    int* src;
    unsigned short* q;
    int n;
    tileAnim_8008D648.field_4 = data[0];
    tileAnim_8008D648.field_8 = data[1];
    n = data[2];
    tileAnim_8008D648.count_0 = n;
    arr = ListAlloc_8003FDC0(heap, n * 16);
    for (i = 0; i < tileAnim_8008D648.count_0; i++)
    {
        src = (int*)((char*)data + data[i + 3]);
        arr[i].field_0 = *src++;
        arr[i].count = *src++;
        q = (unsigned short*)src;
        arr[i].field_8 = *q++;
        arr[i].field_A = *q++;
        arr[i].items = ListAlloc_8003FDC0(heap, arr[i].count * 2);
        for (j = 0; j < arr[i].count; j++)
        {
            arr[i].items[j] = *q++;
        }
    }
    tileAnim_8008D648.items_C = arr;
}
// Matched
void LoadTileAnimLayers_800278BC(int* data, int heap)
{
    int* p = data;
    unsigned int i;
    unsigned int j;
    int n;
    int* q;
    struct_4b* r;
    struct_2s* e;
    n = p[0];
    tileAnim_8008D648.listCount_10 = n;
    tileAnim_8008D648.lists_14 = ListAlloc_8003FDC0(heap, n * 8);
    for (i = 0; i < tileAnim_8008D648.listCount_10; i++)
    {
        q = (int*)((char*)p + p[i + 1]);
        tileAnim_8008D648.lists_14[i].count = *q;
        tileAnim_8008D648.lists_14[i].items = ListAlloc_8003FDC0(heap, tileAnim_8008D648.lists_14[i].count * 4);
        r = (struct_4b*)(q + 1);
        for (j = 0; j < tileAnim_8008D648.lists_14[i].count; j++)
        {
            tileAnim_8008D648.lists_14[i].items[j].a = r[j].a;
            tileAnim_8008D648.lists_14[i].items[j].b = r[j].b;
            tileAnim_8008D648.lists_14[i].items[j].c = r[j].c;
        }
    }
    tileAnim_8008D648.pairs_18 = ListAlloc_8003FDC0(heap, tileAnim_8008D648.listCount_10 * 4);
    for (i = 0; i < tileAnim_8008D648.listCount_10; i++)
    {
        e = (struct_2s*)(i * 4 + (int)tileAnim_8008D648.pairs_18); // integer sum, as the original
        e->b = 0;
        e->a = 0;
    }
}
// Matched
int* LoadMapMeshes_80027A88(MapMesh** out, unsigned int* count, void* heap, MapMeshFile* hdr)
{
    MapMesh* arr;
    unsigned int i;
    unsigned int j;
    unsigned char* p;
    MapMeshRec* rec;
    MapTriRec* tri;
    MapMeshFile* hh;
    p = (unsigned char*)(hdr + 1);
    hh = hdr;
    arr = ListAlloc_8003FDC0(heap, hdr->count_4 * sizeof(MapMesh));
    *count = hdr->count_4;
    if (hdr->count_4 == 0)
    {
        *out = 0;
        return (int*)((unsigned char*)hdr + hdr->size_0);
    }
    for (i = 0; i < hh->count_4; i++)
    {
        rec = (MapMeshRec*)p;
        arr[i].nTris_0 = rec->nTris_0;
        p = (unsigned char*)(rec + 1);
        arr[i].tris_4 = ListAlloc_8003FDC0(heap, rec->nTris_0 * sizeof(MapTri));
        for (j = 0; j < rec->nTris_0; j++)
        {
            tri = (MapTriRec*)p;
            p += sizeof(int);
            arr[i].tris_4[j].nx_18 = tri->n_8.x_0;
            arr[i].tris_4[j].ny_1A = tri->n_8.y_2;
            arr[i].tris_4[j].nz_1C = tri->n_8.z_4;
            arr[i].tris_4[j].pad_1E = 0;
            arr[i].tris_4[j].v_0[0].x_0 = tri->v_10[0].x_0;
            arr[i].tris_4[j].v_0[0].y_2 = tri->v_10[0].y_2;
            arr[i].tris_4[j].v_0[0].z_4 = tri->v_10[0].z_4;
            arr[i].tris_4[j].v_0[0].pad_6 = 0;
            arr[i].tris_4[j].v_0[1].x_0 = tri->v_10[1].x_0;
            arr[i].tris_4[j].v_0[1].y_2 = tri->v_10[1].y_2;
            arr[i].tris_4[j].v_0[1].z_4 = tri->v_10[1].z_4;
            arr[i].tris_4[j].v_0[1].pad_6 = 0;
            arr[i].tris_4[j].v_0[2].x_0 = tri->v_10[2].x_0;
            arr[i].tris_4[j].v_0[2].y_2 = tri->v_10[2].y_2;
            arr[i].tris_4[j].v_0[2].z_4 = tri->v_10[2].z_4;
            arr[i].tris_4[j].v_0[2].pad_6 = 0;
            p += sizeof(MapTriRec) - sizeof(int);
        }
    }
    *out = arr;
    return (int*)((unsigned char*)hdr + hh->size_0);
}
// Matched
void InitMapLoaderTask_80027CC0(EventEntry* p, int* q)
{
    q[0] = 0;
    q[1] = 0;
    MapLoaderTask_80027CF8(p, q);
    p->cb_8 = (EventEntryFn)MapLoaderTask_80027CF8;
}
typedef struct
{
    short f0;
    short f2;
    short f4;
    short f6;
    short f8;
    short fA;
    char pad_C[4];
} MapEntry16;
extern MapEntry16** mapTable_800B0608[];
#define MAP_ENTRY_CF8(i) mapTable_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0][i]
extern int fieldMode_800B0EC0;
extern void SelectMapEntrance_800ADDAC(void);
extern int GetSetReturnEntrance_800A683C(int a0);
extern void ClearEventFlag_800AD124(int a0);
extern int SelectEncounterSpecies_800A5030(int a0, int a1, int a2);
extern void SetBattleStageForMap_800A52AC(int a0);
extern Model* GetLevantModel_800AC38C(void);
extern int GetEventVar_800AD154(int a0);
extern void StartEncounter_800B88A4(int a0);
extern void PlayMusic_800300E0(int a, int b);
extern void OnMapFileLoaded_80028808(void* a0, int* a1);
// Matched
void MapLoaderTask_80027CF8(void* a0, int* state)
{
    int* st = state;
    short v[2];
    FileRequestDesc req;
    MapEntry16* e;
    int t;
    int m;
    int n;
    int k;
    switch (st[0])
    {
    case 0:
        m = fieldMode_800B0EC0;
        if (m == 1 && IsOverlayLoaderIdle_80020D84() == 0)
        {
            eventDispatchHalt_8008B540 = m;
        }
        else if (UpdateLoadFade_80027540() != 0)
        {
            if (forceMapReload_80091C9C != 1 &&
                saveData_8008B570.mapId_2E4[0].field_2 == saveData_8008B570.mapId_2E4[0].field_0 &&
                saveData_8008B570.mapId_2E4[1].field_2 == saveData_8008B570.mapId_2E4[1].field_0 &&
                saveData_8008B570.mapId_2E4[2].field_2 == saveData_8008B570.mapId_2E4[2].field_0)
            {
            }
            else
            {
                if (mapStartMode_80091C54)
                {
                    SelectMapEntrance_800ADDAC();
                }
                if (GetSetReturnEntrance_800A683C(-1) != MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).f6)
                {
                    ClearEventFlag_800AD124(0);
                }
                e = mapTable_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0];
                for (mapAreaCount_80091CB0 = 0; e[mapAreaCount_80091CB0].f0 != -1; mapAreaCount_80091CB0++)
                {
                }
                v[1] = MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_2).f6;
                v[0] = MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).f6;
                t = SelectEncounterSpecies_800A5030(v[0], v[1], dword_80091C90);
                SetBattleStageForMap_800A52AC(v[0]);
                mapStartMode_80091C54 = 1;
                areaReload_80082670 = 0;
                forceMapReload_80091C9C = 0;
                saveData_8008B570.mapId_2E4[0].field_2 = saveData_8008B570.mapId_2E4[0].field_0;
                saveData_8008B570.mapId_2E4[1].field_2 = saveData_8008B570.mapId_2E4[1].field_0;
                saveData_8008B570.mapId_2E4[2].field_2 = saveData_8008B570.mapId_2E4[2].field_0;
                if ((unsigned short)(saveData_8008B570.mapId_2E4[0].field_0 - 1) < 2)
                {
                    unknownFlags_8008D678 |= 0x1000000;
                }
                else
                {
                    unknownFlags_8008D678 &= ~0x1000000;
                }
                ApplyModelFtgSwaps_80025C38(GetLevantModel_800AC38C(), (((unsigned int)unknownFlags_8008D678 >> 24) ^ 1) & 1);
                freeActorModels_80091CA0 = 0;
                if (dword_80091C90 != 0 || MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).fA != 0 || t != 0)
                {
                    freeActorModels_80091CA0 = 1;
                }
                dword_80091C90 = MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).fA;
                UnloadMap_80027118();
                FreeMapArea_8002728C();
                m = MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).f8;
                if (m >= 0)
                {
                    if (GetEventVar_800AD154(12) == 1 && m == 0xD)
                    {
                        m = 0xF;
                    }
                    else if (GetEventVar_800AD154(12) == 2 && m == 0xD)
                    {
                        m = 0x91;
                    }
                    else if (GetEventVar_800AD154(12) == 3 && m == 0x29)
                    {
                        m = 0x26;
                    }
                    else if (GetEventVar_800AD154(12) == 4 && m == 0x2A)
                    {
                        m = 0x25;
                    }
                    PlayMusic_800300E0(m, 1);
                    SetBattleMusic_800315D8(m);
                    SetLoadFadeFlag_80027478(0x20, 1);
                }
                if (dword_80091C90 == 0 && dword_80091C58 != 0)
                {
                    StartEncounter_800B88A4(t);
                    k = st[0];
                    eventDispatchHalt_8008B540 = 1;
                    n = k;
                    st[0] = n + 1;
                    SetLoadFadeFlag_80027478(0x10, 1);
                    break;
                }
                st[0] += 1;
            }
        }
        if (st[0] != 1)
        {
            break;
        }
    case 1:
        req.flags_0 = 0x2C;
        req.fileId_4 = MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).f0;
        req.offset_8 = 0;
        req.size_C = 0;
        req.dest_10 = 0;
        req.params_14 = 0;
        req.paramsSize_18 = 0;
        req.callback_1C = OnMapFileLoaded_80028808;
        st[1] = QueueFileRequest_8003BC84(&req);
        SetLoadFadeFlag_80027478(2, 1);
        {
            int z = st[0];
            eventDispatchHalt_8008B540 = 1;
            st[0] = z + 1;
        }
        break;
    case 2:
        if (IsSoundTaskReady_800306B0() && IsModelLoaderDone_800205D0() && GetFileRequestStatus_8003BE30(st[1]) == 0)
        {
            SetLoadFadeFlag_80027478(0x72, 0);
            st[0] = 0;
        }
        else
        {
            eventDispatchHalt_8008B540 = 1;
        }
        break;
    }
}
// Matched
void ResetMapLoaderTask_8002830C(EventEntry* p)
{
    saveData_8008B570.mapId_2E4[0].field_2 = -1;
    saveData_8008B570.mapId_2E4[1].field_2 = -1;
    saveData_8008B570.mapId_2E4[2].field_2 = -1;
    saveData_8008B570.mapId_2E4[3].field_2 = -1;
    unknownFlags_8008D678 &= ~0x20000;
    freeActorModels_80091CA0 = 1;
    UnloadMap_80027118();
    FreeMapArea_8002728C();
    p->cb_8 = (EventEntryFn)InitMapLoaderTask_80027CC0;
}
// Matched
void InitAreaLoaderTask_80028388(EventEntry* p, int* q)
{
    q[0] = 0;
    q[1] = 0;
    AreaLoaderTask_800283C0(p, q);
    p->cb_8 = (EventEntryFn)AreaLoaderTask_800283C0;
}
extern int GetGameMode_800A6D50(int a0);
extern int battleFlags_800B1228;
extern void OnRoomDataLoaded_80028C60();
// Matched
void AreaLoaderTask_800283C0(void* a0, int* state)
{
    int* st = state;
    FileRequestDesc req;
    FileRequestDesc req2;
    FileRequestDesc req3;
    int s;
    int load;
    int wait;
    s = st[0];
    switch (s)
    {
    case 0:
        if (GetGameMode_800A6D50(0) != 1 && areaReload_80082670 == 0)
        {
            break;
        }
        if (battleFlags_800B1228 & 0x4000)
        {
            break;
        }
        if (areaPreload_80091C40[1] != areaPreload_80091C40[0])
        {
            req.flags_0 = 0xC69;
            req.fileId_4 = mapTable_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0][saveData_8008B570.mapId_2E4[2].field_0].f2;
            req.offset_8 = mapAreas_80082674[areaPreload_80091C40[0] * 3];
            req.size_C = mapAreas_80082674[areaPreload_80091C40[0] * 3 + (areaReload_80082670 ? 2 : 1)];
            req.dest_10 = 0;
            req.params_14 = 0;
            req.paramsSize_18 = 0;
            req.callback_1C = OnRoomDataLoaded_80028C60;
            st[1] = QueueFileRequest_8003BC84(&req);
            areaPreloading_80082678 = 1;
            areaPreload_80091C40[1] = areaPreload_80091C40[0];
            break;
        }
        if (saveData_8008B570.mapId_2E4[3].field_2 != saveData_8008B570.mapId_2E4[3].field_0)
        {
            load = 1;
            wait = 2;
            if (areaReload_80082670 == 0)
            {
                FreeMapArea_8002728C();
            }
            if (areaPreloading_80082678)
            {
                if (areaPreload_80091C40[0] == saveData_8008B570.mapId_2E4[3].field_0)
                {
                    load = 0;
                }
                wait = ConsumeFileRequest_8003BFD0(st[1], 1);
                areaPreloading_80082678 = 0;
            }
            if (load)
            {
                req2.flags_0 = 0x46C;
                req2.fileId_4 = mapTable_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0][saveData_8008B570.mapId_2E4[2].field_0].f2;
                req2.offset_8 = mapAreas_80082674[saveData_8008B570.mapId_2E4[3].field_0 * 3];
                req2.size_C = mapAreas_80082674[saveData_8008B570.mapId_2E4[3].field_0 * 3 + (areaReload_80082670 ? 2 : 1)];
                req2.dest_10 = 0;
                req2.params_14 = 0;
                req2.paramsSize_18 = 0;
                req2.callback_1C = OnRoomDataLoaded_80028C60;
                st[1] = QueueFileRequest_8003BC84(&req2);
            }
            areaLoadIds_80091CB8[7] = saveData_8008B570.mapId_2E4[3].field_0;
            areaLoadIds_80091CB8[6] = saveData_8008B570.mapId_2E4[3].field_0;
            saveData_8008B570.mapId_2E4[3].field_2 = saveData_8008B570.mapId_2E4[3].field_0;
            if (wait)
            {
                if (areaReload_80082670 == 0)
                {
                    SetLoadFadeFlag_80027478(4, 1);
                }
                eventDispatchHalt_8008B540 = 1;
                st[0] = 1;
            }
            break;
        }
        if (areaLoadIds_80091CB8[6] != areaLoadIds_80091CB8[7])
        {
            req3.flags_0 = 0x450;
            req3.fileId_4 = mapTable_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0][saveData_8008B570.mapId_2E4[2].field_0].f2;
            req3.offset_8 = mapAreas_80082674[areaLoadIds_80091CB8[6] * 3];
            req3.size_C = 0;
            req3.dest_10 = 0;
            req3.params_14 = 0;
            req3.paramsSize_18 = 0;
            req3.callback_1C = 0;
            areaLoadIds_80091CB8[7] = areaLoadIds_80091CB8[6];
            st[1] = QueueFileRequest_8003BC84(&req3);
            st[0] = 2;
        }
        break;
    case 1:
        if (GetFileRequestStatus_8003BE30(st[1]) == 0)
        {
            areaReload_80082670 = 0;
            mapJustLoaded_80082668 = 0;
            InitRoomCamera_80028DC0();
            SetLoadFadeFlag_80027478(4, 0);
            st[0] = 0;
        }
        else
        {
            eventDispatchHalt_8008B540 = 1;
        }
        break;
    case 2:
        if (GetFileRequestStatus_8003BE30(st[1]) == 0)
        {
            st[0] = 0;
        }
        break;
    }
}
// the 0x104-byte header of a map file (OnMapFileLoaded_80028808)
typedef struct
{
    LevantPos start_0; // where Levant starts
    char pad_14[0xF0];
} MapFileHeader;
typedef struct
{
    char pad_0[0xC];
    int fC;
} MapEntry16b;
extern void LoadEventData_800A5628(int a0, int* a1, int a2);
extern void MarkSharedEdges_800B73C0(MapMesh* a0, int a1);
extern int FindTriAtXZ_800B76B8(MapMesh* a0, Vec3i* a1);
extern int* LoadMapMeshes_80027A88();
extern short savedLevantRot_80091CA8[];
extern EventNode* gameTask_8008B4A4; // the GAME overlay task
// Matched
void OnMapFileLoaded_80028808(void* a0, int* data)
{
    MapFileHeader hdr;
    int n;
    int* p;
    unsigned int cnt;
    unsigned int i;
    unsigned int j;
    int a;
    int c;
    int c2;
    p = data;
    n = *p++;
    if (n != 0 && dword_80091C8C == 0)
    {
        MemCopy_800403E8(mapCodeAddr_80073210, p, n);
        mapCallback_80091CB4 = ((MapEntry16b*)mapTable_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0])[saveData_8008B570.mapId_2E4[2].field_0].fC;
    }
    p = (int*)((char*)p + n);
    mapJustLoaded_80082668 = 1;
    mapHasCode_8008266C = n != 0;
    cnt = *p++;
    for (j = 0; j < cnt; j++)
    {
        a = *p++;
        c = *p++;
        c2 = *p++;
        LoadEventData_800A5628(a, p, c);
        p = (int*)((char*)p + c2);
    }
    mapState_8008B500.id_0 = saveData_8008B570.mapId_2E4[2].field_0;
    mapState_8008B500.nMeshes_4 = *p++;
    mapState_8008B500.f8_8 = *p++;
    MemCopy_800403E8(&hdr, p, sizeof(hdr));
    p = LoadMapMeshes_80027A88(&mapState_8008B500.meshes_C, &mapState_8008B500.nMeshes_4, &mapHeap_80091C68, (char*)p + 0x104);
    MarkSharedEdges_800B73C0(mapState_8008B500.meshes_C, mapState_8008B500.nMeshes_4);
    p = LoadMapMeshes_80027A88(&mapState_8008B500.ents_14, &mapState_8008B500.nEnts_10, &mapHeap_80091C68, p);
    MarkSharedEdges_800B73C0(mapState_8008B500.ents_14, mapState_8008B500.nEnts_10);
    AllocMapWallFlags_800275E8(&mapState_8008B500.entFlags_18, mapState_8008B500.nEnts_10, (int)&mapHeap_80091C68);
    p = LoadMapMeshes_80027A88(&mapState_8008B500.mesh_28, &mapState_8008B500.nMesh_24, &mapHeap_80091C68, p);
    MarkSharedEdges_800B73C0(mapState_8008B500.mesh_28, mapState_8008B500.nMesh_24);
    p = LoadMapMeshes_80027A88(&mapState_8008B500.ents_30, &mapState_8008B500.nEnts_2C, &mapHeap_80091C68, p);
    MarkSharedEdges_800B73C0(mapState_8008B500.ents_30, mapState_8008B500.nEnts_2C);
    AllocMapWallFlags_800275E8(&mapState_8008B500.entFlags_34, mapState_8008B500.nEnts_2C, (int)&mapHeap_80091C68);
    p = LoadMapMeshes_80027A88(&mapState_8008B500.meshes20_20, &mapState_8008B500.nMeshes20_1C, &mapHeap_80091C68, p);
    MarkSharedEdges_800B73C0(mapState_8008B500.meshes20_20, mapState_8008B500.nMeshes20_1C);
    cnt = p[0];
    LoadMapFtg_80027708(p, (int)&mapHeap_80091C68);
    p = (int*)((char*)p + cnt);
    cnt = *p++;
    LoadTiy_80028E74(0, 0, 0, (int*)p, (int)&mapHeap_80091C68);
    p = LoadMapSpawns_80027650((int*)((char*)p + cnt), 0, (int)&mapHeap_80091C68);
    mapAreas_80082674 = ListAlloc_8003FDC0(&mapHeap_80091C68, mapState_8008B500.nMeshes_4 * 12);
    MemCopy_800403E8(mapAreas_80082674, p, mapState_8008B500.nMeshes_4 * 12);
    if (mapHasCode_8008266C && dword_80091C5C && dword_80091C8C == 0 && mapCallback_80091CB4)
    {
        ((void (*)(int))mapCallback_80091CB4)(0);
    }
    if (useSavedLevantPos_80091C98)
    {
        saveData_8008B570.levant_7A8.pos.x = savedLevantPos_80091C78.pos[0];
        saveData_8008B570.levant_7A8.pos.y = savedLevantPos_80091C78.pos[1];
        saveData_8008B570.levant_7A8.pos.z = savedLevantPos_80091C78.pos[2];
        saveData_8008B570.levant_7A8.rot.vx = savedLevantRot_80091CA8[0];
        saveData_8008B570.levant_7A8.rot.vy = savedLevantRot_80091CA8[1];
        saveData_8008B570.levant_7A8.rot.vz = savedLevantRot_80091CA8[2];
    }
    useSavedLevantPos_80091C98 = 0;
    if (useMapStartPos_80091C94)
    {
        saveData_8008B570.levant_7A8.pos.x = hdr.start_0.pos.x;
        saveData_8008B570.levant_7A8.pos.y = hdr.start_0.pos.y;
        saveData_8008B570.levant_7A8.pos.z = hdr.start_0.pos.z;
        saveData_8008B570.levant_7A8.rot.vx = hdr.start_0.rot.vx;
        saveData_8008B570.levant_7A8.rot.vy = hdr.start_0.rot.vy;
        saveData_8008B570.levant_7A8.rot.vz = hdr.start_0.rot.vz;
    }
    useMapStartPos_80091C94 = 0;
    // stays an int* view: savedLevantPos_80091C78.mapIdx addresses the field as sym+12 and changes the code
    if (((int*)&savedLevantPos_80091C78)[3] >= 0)
    {
        saveData_8008B570.mapId_2E4[3].field_0 = *(short*)&((int*)&savedLevantPos_80091C78)[3];
        saveData_8008B570.mapId_2E4[3].field_2 = -1;
        ((int*)&savedLevantPos_80091C78)[3] = -1;
    }
    else
    {
        for (i = 0; i < (int)mapState_8008B500.nMeshes_4; i++)
        {
            if (FindTriAtXZ_800B76B8(&mapState_8008B500.meshes_C[i], &saveData_8008B570.levant_7A8.pos) >= 0)
            {
                saveData_8008B570.mapId_2E4[3].field_0 = i;
                saveData_8008B570.mapId_2E4[3].field_2 = -1;
                break;
            }
        }
    }
    ((GameTaskState*)gameTask_8008B4A4->entry.buffer)->mapPoint_84 = saveData_8008B570.mapId_2E4[3].field_0;
}
