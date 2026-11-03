#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "tu_8001EA48.h"
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

extern VECTOR levantPos_8008BD18;
extern short dword_8008D474[2];
extern int off_8007DC70;
extern short asc_80084350[]; // a short table (indexed & 0xFFF) starts at +0x1F0 (0x80084540)
typedef struct
{
    int fileIdx;
    unsigned int** ppDest;
} OverlayEntry;
extern OverlayEntry overlays_8007D9E8[];
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
void sub_8001EA48(void* arg0)
{
    Actor* o = arg0;
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
                sub_8001D6EC((struct_obj_A*)o, 0);
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
                sub_8001D760(o, n, mode, flag21);
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
            sub_8001D9E4((struct_obj_A*)o, sub_8001F03C((int)o, (int)cmd, 0x4000, 0), cmd->arg_6);
            break;
        case 7:
            sub_8001DA08((struct_obj_A*)o, sub_8001F03C((int)o, (int)cmd, 0x4000, 0), cmd->arg_6);
            break;
        case 8:
            sub_8001DA2C((struct_obj_A*)o);
            break;
        case 9:
            sub_8001DA4C(o, sub_8001F03C((int)o, (int)cmd, 0x4001, 0), o->scale_26, cmd->arg_6);
            break;
        case 10:
            sub_8001DA4C(o, sub_8001F03C((int)o, (int)cmd, 0x4001, 0), o->scale_26, o->scaleTarget_F6);
            break;
        case 11:
            sub_8001D730((struct_obj_A*)o, cmd->arg_6);
            break;
        case 12:
            sub_8001D8B4(o, cmd->arg_6);
            break;
        case 13:
            if (sub_8001D8A8(o))
            {
                break;
            }
            else
            {
                o->flags_4 |= 0x10000;
                return;
            }
        case 14:
            sub_8001D92C(o, cmd->arg_6);
            break;
        case 15:
            if ((o->flags_4 & 0x4080000) && o->kind_C < 3)
            {
                if (!TurnActorTowards_8001DDFC(o, &o->target_70, o->target_70.pad))
                {
                    sub_8001D71C((struct_obj_A*)o);
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
            sub_8001EFC4(o);
            break;
        case 17:
            if (o->animIdx_C2 != o->prevAnimIdx_C0)
            {
                o->animIdx_C2 = o->prevAnimIdx_C0;
                sub_8001D760(o, o->prevAnimIdx_C0, -2, flag21);
            }
            break;
        case 18:
            if (!sub_8001DC60(o, &o->target_70, o->target_70.pad, 200))
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
                sub_8001D71C((struct_obj_A*)o);
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
            sub_8001D6EC((struct_obj_A*)o, cmd->arg_6 != 0);
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
INCLUDE_DATA(dword_8007411C);
// Matched
void sub_8001EFC4(Actor* p)
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
                sub_800A5BCC(n - 2);
            }
        }
        else if (n >= 3)
        {
            if (f & 0x200000)
            {
                sub_800A5BCC(n - 2);
            }
        }
    }
    p->flags_4 &= 0xFF17FFFF;
}
// Matched
int sub_8001F03C(int a0, int a1, int a2, int a3)
{
    Actor* o = (Actor*)a0;
    ActorScriptCmd* s = (ActorScriptCmd*)a1;
    int t;
    int rep;
    int flag;
    int start;
    int loop;
    int idx;
    int end;
    t = 0;
    rep = t;
    flag = t;
    while (s->op_0 != 0)
    {
        if (s->op_0 == 1)
        {
            idx = s->arg_6;
            if (flag == 0)
            {
                start = o->anims_148[idx].start_2;
            }
            else
            {
                start = o->anims_148[idx].loop_4;
            }
            loop = o->anims_148[idx].loop_4;
            end = o->anims_148[idx].end_6;
            if (a2 != -1 && a2 < 0x4000 && o->anims_148[a2].id_0 == o->anims_148[idx].id_0 && end >= a3)
            {
                return ((t + a3 - start) << 12) / o->frameSpeed_1E;
            }
            if (start == loop)
            {
                t += (end - start + 1) * (rep + 1);
            }
            else
            {
                t += (end - loop + 1) * (rep + 1);
                t += loop - start;
            }
            t--;
            flag = 0;
        }
        else if (s->op_0 == 0x14)
        {
            if (a2 >= 0x4000 && a2 == s->arg_6)
            {
                return (t << 12) / o->frameSpeed_1E;
            }
        }
        else if (s->op_0 == 0xF)
        {
            t = 0;
        }
        else if (s->op_0 == 2)
        {
            flag = 1;
        }
        else if (s->op_0 == 4)
        {
            rep = s->arg_6 - 1;
        }
        else if (s->op_0 == 5)
        {
            rep = o->loopCount_F4 - 1;
        }
        else if (s->op_0 == 0x17)
        {
            t += s->arg_6;
        }
        else if (s->op_0 == 0 || s->op_0 == 0x10)
        {
            if (a2 != -1 && a2 < 0x4000 && o->anims_148[a2].end_6 < a3)
            {
                t += a3 - o->anims_148[a2].end_6;
            }
            return (t << 12) / o->frameSpeed_1E;
        }
        s = (ActorScriptCmd*)((unsigned int*)s + s->len_1);
    }
    return -1;
}
// Matched
short sub_8001F268(Actor* o, short* out, ActorScriptCmd* script, int idx)
{
    short* e = o->anims_148[idx].hitFrames_8[0];
    int i;
    for (i = 0; i < 10; i++)
    {
        if (e[i * 2] < 0 && e[i * 2 + 1] < 0)
        {
            out[i * 2] = -1;
            out[i * 2 + 1] = -1;
        }
        else
        {
            out[i * 2] = sub_8001F03C((int)o, (int)script, idx, e[i * 2]);
            out[i * 2 + 1] = sub_8001F03C((int)o, (int)script, idx, e[i * 2 + 1]);
        }
    }
    return out[0];
}
extern void sub_8004D288(int* out, ModelAnim* s, int k);
extern int sub_800B716C(VECTOR* pos, VECTOR* prev, SVECTOR* rot, void* a3);
// Matched
void sub_8001F354(void* a0)
{
    Actor* o = a0;
    int save[3];
    ModelAnim* e;
    int dx;
    int dz;
    int v;
    SVECTOR* r;
    int* s;
    short c;
    int sn;
    short a;
    e = &((ModelAnim*)o->model_15C->field_54)[o->anim_9C];
    o->prevPos_44[0] = o->pos_38[0];
    o->prevPos_44[1] = o->pos_38[1];
    o->prevPos_44[2] = o->pos_38[2];
    save[0] = o->animDelta_64[0];
    save[1] = o->animDelta_64[1];
    save[2] = o->animDelta_64[2];
    sub_8004D288(o->animDelta_64, e, o->frame_90 % e->frameCount_0);
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
        dx = o->animDelta_64[0] - save[0];
        dz = o->animDelta_64[2] - save[2];
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
        sn = (asc_80084350 + 0xF8)[a & 0xFFF];
        c = (asc_80084350 + 0xF8)[(a + 0x400) & 0xFFF];
        o->pos_38[2] = o->basePos_50[2] + (o->animDelta_64[2] * c - o->animDelta_64[0] * sn) / 4096 / e->divisor_8;
        o->pos_38[0] = o->basePos_50[0] + (o->animDelta_64[2] * sn + o->animDelta_64[0] * c) / 4096 / e->divisor_8;
        o->pos_38[1] = o->basePos_50[1] + o->animDelta_64[1] / e->divisor_8;
    }
    else if (o->flags_4 & 0x40000)
    {
        o->pos_38[0] += dz * (asc_80084350 + 0xF8)[o->rot_5C[1] & 0xFFF] / 4096 * r->vz / 4096 * s[2] / 4096 / e->divisor_8;
        o->pos_38[2] += dz * (asc_80084350 + 0xF8)[(o->rot_5C[1] + 0x400) & 0xFFF] / 4096 * r->vz / 4096 * s[2] / 4096 / e->divisor_8;
    }
    else
    {
        o->pos_38[0] = o->basePos_50[0] + dz * (asc_80084350 + 0xF8)[o->rot_5C[1] & 0xFFF] / 4096 / e->divisor_8;
        o->pos_38[2] = o->basePos_50[2] + dz * (asc_80084350 + 0xF8)[(o->rot_5C[1] + 0x400) & 0xFFF] / 4096 / e->divisor_8;
    }
    if (o->flags_4 & 0x40000)
    {
        o->prevGround_84 = o->ground_80;
        o->ground_80 = sub_800B716C((VECTOR*)o->pos_38, (VECTOR*)o->prevPos_44, (SVECTOR*)o->rot_5C, &o->fB4);
    }
}
// Matched
void sub_8001F918(void* a0)
{
    Actor* p = a0;
    switch (p->animLoadState_10)
    {
    case 0:
        break;
    case 1:
        RequestModelAnim_8002032C(p->modelRef_16, p->task_0->field_4, p->animRequest_12);
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
void sub_8001F9AC(void* p)
{
    sub_8001F9F0(p);
    sub_8001FB00(p);
    sub_8001FD08(p);
    sub_8001FF48(p);
    sub_800200F8(p);
}
// Matched
void sub_8001F9F0(Actor* o)
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
void sub_8001FB00(Actor* o)
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
        v = (asc_80084350 + 0xF8)[(o->pulse_BC * o->pulseRate_BE + 0x400) & 0xFFF];
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
int sub_8001FC90(Actor* a0)
{
    SVECTOR v;
    long sxy;
    long p;
    long flag;
    v.vx = *(unsigned short*)&a0->pos_38[0];
    v.vy = *(unsigned short*)&a0->pos_38[1];
    v.vz = *(unsigned short*)&a0->pos_38[2];
    v.vx -= dword_8008D600[0].field_0;
    v.vy -= dword_8008D600[1].field_0;
    v.vz -= dword_8008D600[2].field_0;
    RotTransPers(&v, &sxy, &p, &flag);
    return flag >= 0;
}
extern int sub_80019CC4();
extern void sub_8001C440();
extern void sub_80047E28();
extern void sub_80046A58();
extern void sub_800459E4();
// Matched
void sub_8001FD08(void* a0)
{
    Actor* o = (Actor*)a0;
    int v;
    ModelAnim* t;
    unsigned long* ot;
    unsigned long* ot2;
    if (!(o->flags_4 & 0x2000) && sub_8001FC90(o))
    {
        v = sub_80019CC4(o->pos_38);
        o->draw_164.anim_14 = &((ModelAnim*)o->model_15C->field_54)[o->anim_9C];
        o->draw_164.field_0 = o->model_15C->field_50;
        o->draw_164.pos_4 = o->pos_38;
        o->draw_164.rot_8 = o->rot_5C;
        o->draw_164.bones_C = o->bones_134;
        o->draw_164.boneScale_10 = o->boneScale_144;
        o->draw_164.frame_18 = o->frame_90 % o->draw_164.anim_14->frameCount_0;
        o->draw_164.drawMode_1C = o->drawMode_8;
        o->draw_164.scale_24 = o->scale_2C;
        o->draw_164.bonePos_20 = (int)o->bonePos_1C4;
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
            t = (ModelAnim*)o->model_15C->field_54;
        }
        else
        {
            t = 0;
        }
        if (o->flags_4 & 0x10)
        {
            sub_80047E28(&o->draw_164, o->draw_164.boneScale_10, &((ModelAnim*)o->model_15C->field_54)[o->prevAnim_A0],
                         o->prevFrame_94 % ((ModelAnim*)o->model_15C->field_54)[o->prevAnim_A0].frameCount_0,
                         0x1000 - o->blend_AC, (char*)stru_8008D534 + v * 24, t);
        }
        else
        {
            sub_80046A58(&o->draw_164, (char*)stru_8008D534 + v * 24, t);
        }
        if (unknownFlags_8008D678 & 0x10000)
        {
            ot2 = pOT_8008B4C8;
        }
        else
        {
            ot2 = pOT_8008D690;
        }
        sub_800459E4(o->bones_134, &o->model_15C->field_5C, ot2, o->drawMode_8);
        sub_8001C440(o->model_15C, o->anim_9C, o->frame_90 % o->draw_164.anim_14->frameCount_0);
    }
}
// Matched
void sub_8001FF48(Actor* o)
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
void sub_800200F8(void* a0)
{
    Actor* o = a0;
    int i;
    if (o->flags_4 & 0x10000000)
    {
        if (o->bones_134[0] != -1)
        {
            i = 0;
            do
            {
                o->boneMatrices_1C8[i] = dword_80098188[i];
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
int AddModelAnimRef_800201EC(int a0)
{
    int i;
    struct_obj_C* p = modelAnimRefs_800919A0;
    for (i = 0; i < 7; i++, p++)
    {
        if (a0 == p->field_0)
        {
            p->field_4++;
            return i;
        }
    }
    p = modelAnimRefs_800919A0;
    for (i = 0; i < 7; i++, p++)
    {
        if (p->field_0 == 0)
        {
            p->field_0 = a0;
            p->field_4 = 1;
            return i;
        }
    }
    return -1;
}
// Matched
void ReleaseModelAnimRef_80020278(int a0, int a1)
{
    int i;
    struct_obj_C* e = &modelAnimRefs_800919A0[a0];
    for (i = 0; i < 0x23; i++)
    {
        if ((e->field_8[i] >> a1) & 1)
        {
            ReleaseModelAnim_800203B0(a0, a1, i);
        }
    }
    if (--e->field_4 == 0)
    {
        ClearModelAnimRef_800204AC(e);
    }
}
// Matched
int RequestModelAnim_8002032C(int a0, int a1, int a2)
{
    struct_obj_C* e = &modelAnimRefs_800919A0[a0];
    int r = 0;
    if (e->field_8[a2] == 0)
    {
        LoadModelAnim_80025440(e->field_0, a2, r);
        r = 1;
    }
    e->field_8[a2] |= 1 << a1;
    return r;
}
// Matched
void ReleaseModelAnim_800203B0(int a0, int a1, int a2)
{
    struct_obj_C* e = &modelAnimRefs_800919A0[a0];
    if ((e->field_8[a2] &= ~(1 << a1)) == 0)
    {
        FreeModelAnim_8002556C(e->field_0, a2);
    }
}
// Matched
int sub_80020410(int a0, int a1, int a2)
{
    struct_obj_C* e = &modelAnimRefs_800919A0[a0];
    int* list;
    int i;
    if (((e->field_8[a2] >> a1) & 1) == 0)
    {
        list = (int*)((struct_112*)e->field_0)->field_58;
        if (list != 0)
        {
            for (i = 0; i < list[0]; i++)
            {
                if (a2 == list[i + 1])
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
void ClearModelAnimRef_800204AC(struct_obj_C* p)
{
    int i;
    for (i = 0x22; i >= 0; i--)
    {
        p->field_8[i] = 0;
    }
    p->field_0 = 0;
    p->field_4 = 0;
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
int RequestLoaderModel_800206A0(int id, int a1, int a2, int a3)
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
            e->sel_8 = a1;
            e->arg_C = a2;
            e->animSet_10 = a3;
            p->done_4 = 0;
            return 1;
        }
        e++;
    }
    return 0;
}
// Matched
struct_112* AcquireLoaderModel_80020734(int arg)
{
    return AcquireModel_80024D70(((ModelLoader*)modelLoaderTask_8008B54C->entry.buffer)->models_8, arg);
}
// Matched
void FreeLoaderModel_80020768(struct_112* a0)
{
    ModelLoader* base = modelLoaderTask_8008B54C->entry.buffer;
    ModelLoadSlot* p = base->slots_C;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (p->id_4 >= 0 && p->animSet_10 >= 0)
        {
            if (a0 == AcquireModel_80024D70(base->models_8, p->id_4))
            {
                FreeModel_80024C48(a0);
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
        InitModelList_80024ADC(&p->models_8, off_8007DC70, 1);
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
int AreRequestedModelsLoaded_80020B70(ModelLoader* a0)
{
    ModelLoadSlot* p = a0->slots_C;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (p->loaded_0 != 0)
        {
            if (AreFileRequestsDone_80024DC4(AcquireModel_80024D70(a0->models_8, p->id_4)) == 0)
            {
                return 0;
            }
        }
        p++;
    }
    a0->done_4 = 1;
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
#if 0
// Not matched
int LoadOverlayIfChanged_80020D1C(int a0, int a1)
{
    OverlayLoader* p = overlayLoaderTask_8008D4C0->entry.buffer;
    if (p->wanted_0 == a1)
    {
        return -1;
    }
    p->wanted_0 = a1;
    p->loaded_4 = a1;
    return LoadOverlay_80020BF8(a0, a1);
}
#endif
INCLUDE_ASM(LoadOverlayIfChanged_80020D1C);
// Matched
void ResetOverlayLoaderTask_80020D68(void)
{
    ((OverlayLoader*)overlayLoaderTask_8008D4C0->entry.buffer)->wanted_0 = 0x1D;
}
// Matched
int sub_80020D84(void)
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
void LoadEffectFile_80020DDC(int a0, EffectFile* out, short* a2, short* a3, int a4, int a5)
{
    FileRequestDesc req;
    EffectLoadArg arg;
    arg.out_0 = out;
    arg.reloc_4[0] = a2[0];
    arg.reloc_4[1] = a2[1];
    arg.reloc_4[2] = a3[0];
    arg.reloc_4[3] = a3[1];
    arg.reloc_4[4] = a3[0];
    arg.reloc_4[5] = a3[1];
    arg.sel_10 = a4;
    ListInit_8003FDB0(out->list_4);
    req.flags_0 = 0x28;
    if (a5)
    {
        req.flags_0 |= 4;
    }
    else
    {
        req.flags_0 |= 1;
    }
    req.fileId_4 = a0;
    req.offset_8 = 0;
    req.size_C = 0;
    req.dest_10 = 0;
    req.params_14 = &arg;
    req.paramsSize_18 = 0x14;
    req.callback_1C = OnEffectFileLoaded_80020F5C;
    out->request_0 = StartFileRequestTask_8003C6C8(&req);
}
// Matched
int IsEffectFileLoaded_80020EBC(int* p)
{
    return GetFileRequestStatus_8003BE30(*p) == 0;
}
// Matched
void FreeEffectFile_80020EE0(int* p)
{
    ListFreeAll_8003FEC8(p + 1);
}
// Matched
int sub_80020F00(struct_list_14* p, int a, int b)
{
    int i;
    for (i = 0; i < p->count; i++)
    {
        if (p->items[i].field_0 == a && p->items[i].field_4 == b)
        {
            return p->items[i].field_8;
        }
    }
    return -1;
}
void sub_80021298(int* src, EffectSprite* out, int a2, int a3, int heap);
void sub_80021464(int* hdr, EffectModel* out, int a2, int a3, int heap);
int LoadMdecImages_800215E8(int* hdr, MdecImageSet* out, int heap);
void sub_800216E8(EffectMdecBuffers* a0, int a1, int a2);
void sub_80021E4C(int* a0, FtgMatList* a1, unsigned int n);
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
    MemCopy_800403E8((unsigned int*)out->data_10, (unsigned int*)(p1 + 1), p1[0]);
    n = p2[0];
    if (n)
    {
        out->pointCount_14 = n;
        out->points_18 = ListAlloc_8003FDC0(out->list_4, n * 12);
        src = p2 + 1;
        for (i = 0; i < out->pointCount_14; i++)
        {
            out->points_18[i].a = src[0];
            out->points_18[i].b = src[1];
            out->points_18[i].c = src[2];
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
            sub_80021298((int*)((char*)p3 + p3[i + 1]), d, (int)arg->reloc_4, arg->sel_10, (int)out->list_4);
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
            sub_80021464((int*)((char*)p4 + p4[i + 1]), d, (int)arg->reloc_4, arg->sel_10, (int)out->list_4);
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
        sub_800216E8(&out->mdec_34, max, (int)out->list_4);
    }
    if (GetTiyFileCount_80028E68(p6))
    {
        LoadTiyTimsRelocated_80028FDC(0, 0, 0, (int)p6, GetTiyFileCount_80028E68(p6), (int)arg->reloc_4, arg->sel_10);
    }
}
// Matched
void sub_80021298(int* src, EffectSprite* out, int a2, int a3, int heap)
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
        d = (struct_1c*)ListAlloc_8003FDC0(heap, n * 28);
        out->frameCounts_4[i] = n;
        out->frames_8[i] = d;
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
    MemCopy_800403E8((unsigned int*)&buf, (unsigned int*)src, 0x28);
    InitPolyFT4_80029A10(&out->poly_C, &buf);
}
// Matched
void sub_80021464(int* hdr, EffectModel* out, int a2, int a3, int heap)
{
    int* models = (int*)((char*)hdr + hdr[1]);
    int* images = (int*)((char*)hdr + hdr[2]);
    if (GetFtgObjectCount_80021738(models))
    {
        out->ftgCount_0 = GetFtgObjectCount_80021738(models);
        AllocFtgObjects_80021744((int*)&out->ftg_4, out->ftgCount_0, heap);
        LoadFtgObjects_80021824(models, out->ftg_4, out->ftgCount_0, heap, a2);
    }
    if (sub_80021DE4(models))
    {
        sub_80021DF0((int*)&out->mats_8, sub_80021DE4(models), heap);
        sub_80021E4C(models, &out->mats_8, sub_80021DE4(models));
    }
    else
    {
        out->mats_8.count_0 = 0;
    }
    out->imageW_10 = 0;
    out->imageH_14 = 0;
    out->images_18 = 0;
    if (images[0] && images[1])
    {
        out->imageW_10 = images[0];
        out->imageH_14 = images[1];
        out->images_18 = ListAlloc_8003FDC0(heap, images[0] * 40 * images[1]);
        MemCopy_800403E8((unsigned int*)out->images_18, (unsigned int*)(images + 2), images[0] * 40 * images[1]);
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
        MemCopy_800403E8((unsigned int*)out->images_4[i], (unsigned int*)src, size);
        n = DecDCTBufSize(src);
        if (max < n)
        {
            max = n;
        }
    }
    return max;
}
// Matched
void sub_800216E8(EffectMdecBuffers* a0, int a1, int a2)
{
    a0->dct_0 = ListAlloc_8003FDC0(a2, (a1 + 1) * 4);
    a0->work_4 = ListAlloc_8003FDC0(a2, 0x2000);
}
// Matched
int GetFtgObjectCount_80021738(int* p)
{
    return p[1];
}
// Matched
void AllocFtgObjects_80021744(int* p, int idx, int a2)
{
    *p = HeapAlloc_8003FC8C(idx * 0x54, a2);
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
void sub_80021804(int* p, int heap)
{
    FreeFtgObject_800229B0((FtgObject*)p, heap);
}
// Matched
void LoadFtgObjects_80021824(int* a0, FtgObject* a1, int a2, int a3, int a4)
{
    unsigned int n = GetFtgObjectCount_80021738(a0);
    int r = (int)(a0 + 4);
    unsigned int i;
    for (i = 0; i < n; i++)
    {
        r = LoadFtgObject_80022458(a1, r, a3, a4);
        a1++;
    }
}
// Matched
void sub_800218A8(FtgObject* s, FtgObject* d, int a2)
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
        buf = (char*)HeapAlloc_8003FC8C(size, (struct Pool*)a2);
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
        MemCopy_800403E8((unsigned int*)&d->f3_0.items[i], (unsigned int*)&s->f3_0.items[i], 0x24);
    }
    for (i = 0; i < d->g3_8.count; i++)
    {
        MemCopy_800403E8((unsigned int*)&d->g3_8.items[i], (unsigned int*)&s->g3_8.items[i], 0x3C);
    }
    for (i = 0; i < d->ft3_10.count; i++)
    {
        MemCopy_800403E8((unsigned int*)&d->ft3_10.items[i], (unsigned int*)&s->ft3_10.items[i], 0x30);
    }
    for (i = 0; i < d->gt3_18.count; i++)
    {
        MemCopy_800403E8((unsigned int*)&d->gt3_18.items[i], (unsigned int*)&s->gt3_18.items[i], 0x48);
    }
    for (i = 0; i < d->f4_20.count; i++)
    {
        MemCopy_800403E8((unsigned int*)&d->f4_20.items[i], (unsigned int*)&s->f4_20.items[i], 0x2C);
    }
    for (i = 0; i < d->g4_28.count; i++)
    {
        MemCopy_800403E8((unsigned int*)&d->g4_28.items[i], (unsigned int*)&s->g4_28.items[i], 0x50);
    }
    for (i = 0; i < d->ft4_30.count; i++)
    {
        MemCopy_800403E8((unsigned int*)&d->ft4_30.items[i], (unsigned int*)&s->ft4_30.items[i], 0x38);
    }
    for (i = 0; i < d->gt4_38.count; i++)
    {
        MemCopy_800403E8((unsigned int*)&d->gt4_38.items[i], (unsigned int*)&s->gt4_38.items[i], 0x5C);
    }
    for (i = 0; i < d->spriteCount_40; i++)
    {
        MemCopy_800403E8((unsigned int*)&d->sprites_44[i], (unsigned int*)&s->sprites_44[i], 0x14);
    }
    for (i = 0; i < d->texSpriteCount_48; i++)
    {
        MemCopy_800403E8((unsigned int*)&d->texSprites_50[i], (unsigned int*)&s->texSprites_50[i], 0x14);
    }
    d->tpage_4C = s->tpage_4C;
    d->clut_4E = s->clut_4E;
}
// Matched
int sub_80021DE4(int* p)
{
    return p[2];
}
// Matched
void sub_80021DF0(int* p, int a1, int a2)
{
    p[0] = a1;
    p[1] = HeapAlloc_8003FC8C(a1 * 16, a2);
}
// p is volatile to keep the store before the load
// Matched
void sub_80021E24(volatile int* p, int h)
{
    p[0] = 0;
    HeapFree_8003FD18(p[1]);
}
// Matched
void sub_80021E4C(int* a0, FtgMatList* a1, unsigned int n)
{
    unsigned short* src = (unsigned short*)((char*)a0 + a0[3]);
    unsigned int i;
    for (i = 0; i < n; i++)
    {
        unsigned short* dst = a1->items_4[i];
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
void sub_80021EDC(FtgPolyFT4* p, POLY_FT4* d)
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
void sub_800221DC(FtgPolyFT4* p, SPRT* d, DR_TPAGE* tp)
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
typedef void (*fn_80022458_a)(unsigned char* body, int a3);
typedef int (*fn_80022458_b)(FtgPrimHeader* hdr, unsigned char* body, FtgObject* obj, int k, int h);
extern fn_80022458_a ftgPrimRelocators_8007DB08[];
extern fn_80022458_b ftgPrimLoaders_8007DAE0[];
void sub_80022B84(FtgSrcObjectHeader* c, int* x, int* y);
int sub_80022634(FtgObject* out, FtgSrcObjectHeader* hdr, int h);
int sub_8002300C(FtgPrimHeader* hdr, FtgSrcSprites8* p, FtgSpriteGroups8* a, int k, int h);
int sub_8002320C(FtgPrimHeader* hdr, FtgSrcSprites9* p, FtgSpriteGroups9* b, int k, int h);
void sub_80022CC4(FtgObject* a0, FtgSpriteGroups8* a, FtgSpriteGroups9* b, int h);
// Matched
int LoadFtgObject_80022458(FtgObject* a0, unsigned char* a1, int h, int a3)
{
    int cnt[10];
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
        cnt[j] = 0;
    }
    hdr = a1;
    a1 += 0x28;
    n = sub_80022634(a0, (FtgSrcObjectHeader*)hdr, h);
    sub_800228F8(&A, &B, (FtgSrcObjectHeader*)hdr, h);
    for (i = 0; i < n; i++)
    {
        p = (FtgPrimHeader*)a1;
        a1 += 4;
        type = p->type_0;
        k = cnt[type];
        cnt[type] = k + 1;
        if (a3 != 0 && ftgPrimRelocators_8007DB08[type] != 0)
        {
            ftgPrimRelocators_8007DB08[type](a1, a3);
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
            a1 += ftgPrimLoaders_8007DAE0[type](p, a1, a0, k, h);
            break;
        case 8:
            a1 += sub_8002300C(p, (FtgSrcSprites8*)a1, &A, k, h);
            break;
        case 9:
            a1 += sub_8002320C(p, (FtgSrcSprites9*)a1, &B, k, h);
            break;
        }
    }
    sub_80022CC4(a0, &A, &B, h);
    sub_800229E0(&A, &B, h);
    return (int)a1;
}
// Matched
int sub_80022634(FtgObject* out, FtgSrcObjectHeader* hdr, int h)
{
    int x;
    int y;
    int size;
    int total;
    char* p;
    int* c = hdr->counts_0;
    p = 0;
    sub_80022B84(hdr, &x, &y);
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
        p = (char*)HeapAlloc_8003FC8C(size, h);
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
int sub_800228F8(FtgSpriteGroups8* a0, FtgSpriteGroups9* a1, FtgSrcObjectHeader* a2, int heap)
{
    int n;
    int m;
    a0->count = a2->counts_0[8];
    n = a2->counts_0[8];
    if (n)
    {
        a0->groups = (FtgSpriteGroup8*)HeapAlloc_8003FC8C(n << 3, (struct Pool*)heap);
    }
    else
    {
        a0->groups = 0;
    }
    a1->count = a2->counts_0[9];
    m = a2->counts_0[9];
    n += m;
    if (m)
    {
        a1->groups = (FtgSpriteGroup9*)HeapAlloc_8003FC8C(m * 12, (struct Pool*)heap);
    }
    else
    {
        a1->groups = 0;
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
void sub_800229E0(FtgSpriteGroups8* a0, FtgSpriteGroups9* a1, int h)
{
    int i;
    if (a0->groups != 0)
    {
        for (i = 0; i < a0->count; i++)
        {
            if (a0->groups[i].items != 0)
            {
                HeapFree_8003FD18(a0->groups[i].items, h);
            }
        }
        HeapFree_8003FD18(a0->groups, h);
    }
    if (a1->groups != 0)
    {
        for (i = 0; i < a1->count; i++)
        {
            if (a1->groups[i].items != 0)
            {
                HeapFree_8003FD18(a1->groups[i].items, h);
            }
        }
        HeapFree_8003FD18(a1->groups, h);
    }
}
// Matched
void RelocateTPageClut_80022AE8(unsigned short* a0, unsigned short* a1, short* a2)
{
    int u = a2[0] / 64;
    int v = a2[1] / 256;
    int tp = v * 16 + u;
    unsigned short t = *a1;
    u = (t & 0x3F) * 16;
    v = (t >> 6) & 0x1FF;
    if (((*a0 >> 7) & 3) == 0)
    {
        u += a2[2];
        v += a2[3];
    }
    else
    {
        u += a2[4];
        v += a2[5];
    }
    *a0 += tp;
    *a1 = v * 64 + (u >> 4);
}
#if 0
// Not matched: the original copies c/q/k into extra registers (looks like inlined helpers) and keeps q+4/q+8 unfolded; needs its jump table split out of dword_800740B4 (keep 0x68 of its 0x90 bytes)
void sub_80022B84(FtgSrcObjectHeader* c, int* x, int* y)
{
    int n;
    int i;
    int a;
    int b;
    int k;
    int* r;
    unsigned char* q;
    unsigned char* t;
    a = 0;
    q = (unsigned char*)c;
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
        case 1:
            q += 0x3C;
            break;
        case 0:
        case 2:
            q += 0x24;
            break;
        case 3:
            q += 0x40;
            break;
        case 5:
            q += 0x50;
            break;
        case 4:
        case 6:
            q += 0x2C;
            break;
        case 7:
            q += 0x54;
            break;
        case 8:
            r = (int*)q;
            k = r[0];
            q = (unsigned char*)(r + 1) + k * 20;
            a += k;
            break;
        case 9:
            r = (int*)q;
            k = r[0];
            q = (unsigned char*)(r + 2) + k * 20;
            b += k;
            break;
        }
    }
    *x = a;
    *y = b;
}
#endif
INCLUDE_ASM(sub_80022B84);
#if 0
// Not matched: first loop swaps the j/k registers and fills the first beqz delay slot; second loop has the j++/n++ increments in the other order
void sub_80022CC4(FtgObject* a0, FtgSpriteGroups8* a, FtgSpriteGroups9* b, int h)
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
        for (n = 0; n < a0->spriteCount_40; n++)
        {
            if (j >= a->groups[k].count)
            {
                k++;
                j = 0;
                e = &a->groups[k];
            }
            a0->sprites_44[n].p0.x = e->items[j].p0.x;
            a0->sprites_44[n].p0.y = e->items[j].p0.y;
            a0->sprites_44[n].p0.z = e->items[j].p0.z;
            a0->sprites_44[n].p0.uv = 0;
            a0->sprites_44[n].p1.x = e->items[j].p1.x;
            a0->sprites_44[n].p1.y = e->items[j].p1.y;
            a0->sprites_44[n].p1.z = e->items[j].p1.z;
            a0->sprites_44[n].p1.uv = 0;
            a0->sprites_44[n].c.r = e->items[j].c.r;
            a0->sprites_44[n].c.g = e->items[j].c.g;
            a0->sprites_44[n].c.b = e->items[j].c.b;
            a0->sprites_44[n].c.code = 0;
            j++;
        }
    }
    if (b->count)
    {
        j = 0;
        a0->tpage_4C = b->groups->tpage;
        a0->clut_4E = b->groups->clut;
        f = b->groups;
        k = 0;
        for (n = 0; n < a0->texSpriteCount_48; n++, j++)
        {
            if (j >= b->groups[k].count)
            {
                k++;
                j = 0;
                f = &b->groups[k];
            }
            a0->texSprites_50[n].p0.x = f->items[j].p0.x;
            a0->texSprites_50[n].p0.y = f->items[j].p0.y;
            a0->texSprites_50[n].p0.z = f->items[j].p0.z;
            a0->texSprites_50[n].p0.uv = 0;
            a0->texSprites_50[n].p1.x = f->items[j].p1.x;
            a0->texSprites_50[n].p1.y = f->items[j].p1.y;
            a0->texSprites_50[n].p1.z = f->items[j].p1.z;
            a0->texSprites_50[n].p1.uv = 0;
            a0->texSprites_50[n].c.r = f->items[j].c.r;
            a0->texSprites_50[n].c.g = f->items[j].c.g;
            a0->texSprites_50[n].c.b = f->items[j].c.b;
            a0->texSprites_50[n].c.code = f->items[j].c.code;
            a0->texSprites_50[n].p1.uv = f->items[j].p1.uv;
        }
    }
}
#endif
INCLUDE_ASM(sub_80022CC4);
// Matched
int sub_8002300C(FtgPrimHeader* hdr, FtgSrcSprites8* p_in, FtgSpriteGroups8* a, int k, int h)
{
    FtgSrcSprites8* p = p_in;
    int r = 4;
    int i;
    FtgSrcSprite8* q;
    a->groups[k].count = p->count_0;
    a->groups[k].items = (FtgSprite*)HeapAlloc_8003FC8C(p->count_0 * 20, h);
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
int sub_8002320C(FtgPrimHeader* hdr, FtgSrcSprites9* p_in, FtgSpriteGroups9* b, int k, int h)
{
    FtgSrcSprites9* p = p_in;
    int r;
    int i;
    FtgSrcSprite9* q;
    b->groups[k].count = p->count_0;
    b->groups[k].items = (FtgSprite*)HeapAlloc_8003FC8C(p->count_0 * 20, h);
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
void sub_80023460(FtgSrcSprites9* p, int arg1)
{
    RelocateTPageClut_80022AE8(&p->tpage_4, &p->clut_6, arg1);
}
// Matched
int sub_8002348C(FtgPrimHeader* a0, FtgPolyF3* a1, FtgObject* a2, int a3)
{
    if (a0->flags_3 & 2)
    {
        SetSemiTrans(&a2->f3_0.items[a3], 1);
    }
    sub_80023514(&a2->f3_0, a1, a0->flags_3, a3);
    return 0x24;
}
// Matched
void sub_80023514(FtgPolyF3List* a0, FtgPolyF3* s, int a2, int a3)
{
    a0->items[a3].c.r = s->c.r;
    a0->items[a3].c.g = s->c.g;
    a0->items[a3].c.b = s->c.b;
    a0->items[a3].c.code = a2;
    a0->items[a3].v[0].x = s->v[0].x;
    a0->items[a3].v[0].y = s->v[0].y;
    a0->items[a3].v[0].z = s->v[0].z;
    a0->items[a3].v[1].x = s->v[1].x;
    a0->items[a3].v[1].y = s->v[1].y;
    a0->items[a3].v[1].z = s->v[1].z;
    a0->items[a3].v[2].x = s->v[2].x;
    a0->items[a3].v[2].y = s->v[2].y;
    a0->items[a3].v[2].z = s->v[2].z;
    a0->items[a3].n.x = s->n.x;
    a0->items[a3].n.y = s->n.y;
    a0->items[a3].n.z = s->n.z;
}
// Matched
int sub_80023624(FtgPrimHeader* a0, FtgSrcPolyG3* a1, FtgObject* a2, int a3)
{
    if (a0->flags_3 & 2)
    {
        SetSemiTrans(&a2->g3_8.items[a3], 1);
    }
    sub_800236AC(&a2->g3_8, a1, a0->flags_3, a3);
    return 0x3C;
}
// Matched
void sub_800236AC(FtgPolyG3List* a0, FtgSrcPolyG3* s, int a2, int a3)
{
    a0->items[a3].c[0].r = s->c[0].r;
    a0->items[a3].c[0].g = s->c[0].g;
    a0->items[a3].c[0].b = s->c[0].b;
    a0->items[a3].c[0].code = a2;
    a0->items[a3].c[1].r = s->c[1].r;
    a0->items[a3].c[1].g = s->c[1].g;
    a0->items[a3].c[1].b = s->c[1].b;
    a0->items[a3].c[0].code = a2;
    a0->items[a3].c[2].r = s->c[2].r;
    a0->items[a3].c[2].g = s->c[2].g;
    a0->items[a3].c[2].b = s->c[2].b;
    a0->items[a3].c[0].code = a2;
    a0->items[a3].v[0].x = s->p[0].v.x;
    a0->items[a3].v[0].y = s->p[0].v.y;
    a0->items[a3].v[0].z = s->p[0].v.z;
    a0->items[a3].v[1].x = s->p[1].v.x;
    a0->items[a3].v[1].y = s->p[1].v.y;
    a0->items[a3].v[1].z = s->p[1].v.z;
    a0->items[a3].v[2].x = s->p[2].v.x;
    a0->items[a3].v[2].y = s->p[2].v.y;
    a0->items[a3].v[2].z = s->p[2].v.z;
    a0->items[a3].n[0].x = s->p[0].n.x;
    a0->items[a3].n[0].y = s->p[0].n.y;
    a0->items[a3].n[0].z = s->p[0].n.z;
    a0->items[a3].n[1].x = s->p[1].n.x;
    a0->items[a3].n[1].y = s->p[1].n.y;
    a0->items[a3].n[1].z = s->p[1].n.z;
    a0->items[a3].n[2].x = s->p[2].n.x;
    a0->items[a3].n[2].y = s->p[2].n.y;
    a0->items[a3].n[2].z = s->p[2].n.z;
    a0->items[a3].c[0].code = a2;
}
// Matched
int sub_800238AC(FtgPrimHeader* a0, FtgSrcPolyFT3* a1, FtgObject* a2, int a3)
{
    if (a0->flags_3 & 2)
    {
        SetSemiTrans(&a2->ft3_10.items[a3], 1);
    }
    sub_80023934(&a2->ft3_10, a1, a0->flags_3, a3);
    return 0x24;
}
// Matched
void sub_80023934(FtgPolyFT3List* a0, FtgSrcPolyFT3* s, int a2, int a3)
{
    a0->items[a3].tpage = s->tex.tpage;
    a0->items[a3].clut = s->tex.clut;
    a0->items[a3].u0 = s->v[0].u;
    a0->items[a3].v0 = s->v[0].v;
    a0->items[a3].v[0].uv = a0->items[a3].u0 + (a0->items[a3].v0 << 8);
    a0->items[a3].u1 = s->v[1].u;
    a0->items[a3].v1 = s->v[1].v;
    a0->items[a3].v[1].uv = a0->items[a3].u1 + (a0->items[a3].v1 << 8);
    a0->items[a3].u2 = s->v[2].u;
    a0->items[a3].v2 = s->v[2].v;
    a0->items[a3].v[2].uv = a0->items[a3].u2 + (a0->items[a3].v2 << 8);
    a0->items[a3].c.r = 0x80;
    a0->items[a3].c.g = 0x80;
    a0->items[a3].c.b = 0x80;
    a0->items[a3].c.code = a2;
    a0->items[a3].v[0].x = s->v[0].x;
    a0->items[a3].v[0].y = s->v[0].y;
    a0->items[a3].v[0].z = s->v[0].z;
    a0->items[a3].v[1].x = s->v[1].x;
    a0->items[a3].v[1].y = s->v[1].y;
    a0->items[a3].v[1].z = s->v[1].z;
    a0->items[a3].v[2].x = s->v[2].x;
    a0->items[a3].v[2].y = s->v[2].y;
    a0->items[a3].v[2].z = s->v[2].z;
    a0->items[a3].n.x = s->n.x;
    a0->items[a3].n.y = s->n.y;
    a0->items[a3].n.z = s->n.z;
}
// Matched
void sub_80023B24(FtgSrcPolyFT3* p, int arg1)
{
    RelocateTPageClut_80022AE8(&p->tex.tpage, &p->tex.clut, arg1);
}
// Matched
int sub_80023B48(FtgPrimHeader* a0, FtgSrcPolyGT3* a1, FtgObject* a2, int a3)
{
    if (a0->flags_3 & 2)
    {
        SetSemiTrans(&a2->gt3_18.items[a3], 1);
    }
    sub_80023BD0(&a2->gt3_18, a1, a0->flags_3, a3);
    return 0x40;
}
// Matched
void sub_80023BD0(FtgPolyGT3List* a0, FtgSrcPolyGT3* s, int a2, int a3)
{
    a0->items[a3].tpage = s->tex.tpage;
    a0->items[a3].clut = s->tex.clut;
    a0->items[a3].u0 = s->p[0].v.u;
    a0->items[a3].v0 = s->p[0].v.v;
    a0->items[a3].v[0].uv = a0->items[a3].u0 + (a0->items[a3].v0 << 8);
    a0->items[a3].u1 = s->p[1].v.u;
    a0->items[a3].v1 = s->p[1].v.v;
    a0->items[a3].v[1].uv = a0->items[a3].u1 + (a0->items[a3].v1 << 8);
    a0->items[a3].u2 = s->p[2].v.u;
    a0->items[a3].v2 = s->p[2].v.v;
    a0->items[a3].v[2].uv = a0->items[a3].u2 + (a0->items[a3].v2 << 8);
    a0->items[a3].c[0].code = a2;
    a0->items[a3].c[0].r = s->c[0].r;
    a0->items[a3].c[0].g = s->c[0].g;
    a0->items[a3].c[0].b = s->c[0].b;
    a0->items[a3].c[1].r = s->c[1].r;
    a0->items[a3].c[1].g = s->c[1].g;
    a0->items[a3].c[1].b = s->c[1].b;
    a0->items[a3].c[2].r = s->c[2].r;
    a0->items[a3].c[2].g = s->c[2].g;
    a0->items[a3].c[2].b = s->c[2].b;
    a0->items[a3].v[0].x = s->p[0].v.x;
    a0->items[a3].v[0].y = s->p[0].v.y;
    a0->items[a3].v[0].z = s->p[0].v.z;
    a0->items[a3].v[1].x = s->p[1].v.x;
    a0->items[a3].v[1].y = s->p[1].v.y;
    a0->items[a3].v[1].z = s->p[1].v.z;
    a0->items[a3].v[2].x = s->p[2].v.x;
    a0->items[a3].v[2].y = s->p[2].v.y;
    a0->items[a3].v[2].z = s->p[2].v.z;
    a0->items[a3].n[0].x = s->p[0].n.x;
    a0->items[a3].n[0].y = s->p[0].n.y;
    a0->items[a3].n[0].z = s->p[0].n.z;
    a0->items[a3].n[1].x = s->p[1].n.x;
    a0->items[a3].n[1].y = s->p[1].n.y;
    a0->items[a3].n[1].z = s->p[1].n.z;
    a0->items[a3].n[2].x = s->p[2].n.x;
    a0->items[a3].n[2].y = s->p[2].n.y;
    a0->items[a3].n[2].z = s->p[2].n.z;
}
// Matched
void sub_80023E80(FtgSrcPolyGT3* p, int arg1)
{
    RelocateTPageClut_80022AE8(&p->tex.tpage, &p->tex.clut, arg1);
}
// Matched
int sub_80023EA4(FtgPrimHeader* a0, FtgPolyF4* a1, FtgObject* a2, int a3)
{
    if (a0->flags_3 & 2)
    {
        SetSemiTrans(&a2->f4_20.items[a3], 1);
    }
    sub_80023F34(&a2->f4_20, a1, a0->flags_3, a3);
    return 0x2C;
}
// Matched
void sub_80023F34(FtgPolyF4List* a0, FtgPolyF4* s, int a2, int a3)
{
    a0->items[a3].c.r = s->c.r;
    a0->items[a3].c.g = s->c.g;
    a0->items[a3].c.b = s->c.b;
    a0->items[a3].c.code = a2;
    a0->items[a3].v[0].x = s->v[0].x;
    a0->items[a3].v[0].y = s->v[0].y;
    a0->items[a3].v[0].z = s->v[0].z;
    a0->items[a3].v[1].x = s->v[1].x;
    a0->items[a3].v[1].y = s->v[1].y;
    a0->items[a3].v[1].z = s->v[1].z;
    a0->items[a3].v[2].x = s->v[2].x;
    a0->items[a3].v[2].y = s->v[2].y;
    a0->items[a3].v[2].z = s->v[2].z;
    a0->items[a3].v[3].x = s->v[3].x;
    a0->items[a3].v[3].y = s->v[3].y;
    a0->items[a3].v[3].z = s->v[3].z;
    a0->items[a3].n.x = s->n.x;
    a0->items[a3].n.y = s->n.y;
    a0->items[a3].n.z = s->n.z;
}
// Matched
int sub_8002407C(FtgPrimHeader* a0, FtgSrcPolyG4* a1, FtgObject* a2, int a3)
{
    if (a0->flags_3 & 2)
    {
        SetSemiTrans(&a2->g4_28.items[a3], 1);
    }
    sub_80024104(&a2->g4_28, a1, a0->flags_3, a3);
    return 0x50;
}
// Matched
void sub_80024104(FtgPolyG4List* a0, FtgSrcPolyG4* s, int a2, int a3)
{
    a0->items[a3].c[0].r = s->c[0].r;
    a0->items[a3].c[0].g = s->c[0].g;
    a0->items[a3].c[0].b = s->c[0].b;
    a0->items[a3].c[0].code = a2;
    a0->items[a3].c[1].r = s->c[1].r;
    a0->items[a3].c[1].g = s->c[1].g;
    a0->items[a3].c[1].b = s->c[1].b;
    a0->items[a3].c[0].code = a2;
    a0->items[a3].c[2].r = s->c[2].r;
    a0->items[a3].c[2].g = s->c[2].g;
    a0->items[a3].c[2].b = s->c[2].b;
    a0->items[a3].c[0].code = a2;
    a0->items[a3].c[3].r = s->c[3].r;
    a0->items[a3].c[3].g = s->c[3].g;
    a0->items[a3].c[3].b = s->c[3].b;
    a0->items[a3].c[0].code = a2;
    a0->items[a3].v[0].x = s->p[0].v.x;
    a0->items[a3].v[0].y = s->p[0].v.y;
    a0->items[a3].v[0].z = s->p[0].v.z;
    a0->items[a3].v[1].x = s->p[1].v.x;
    a0->items[a3].v[1].y = s->p[1].v.y;
    a0->items[a3].v[1].z = s->p[1].v.z;
    a0->items[a3].v[2].x = s->p[2].v.x;
    a0->items[a3].v[2].y = s->p[2].v.y;
    a0->items[a3].v[2].z = s->p[2].v.z;
    a0->items[a3].v[3].x = s->p[3].v.x;
    a0->items[a3].v[3].y = s->p[3].v.y;
    a0->items[a3].v[3].z = s->p[3].v.z;
    a0->items[a3].n[0].x = s->p[0].n.x;
    a0->items[a3].n[0].y = s->p[0].n.y;
    a0->items[a3].n[0].z = s->p[0].n.z;
    a0->items[a3].n[1].x = s->p[1].n.x;
    a0->items[a3].n[1].y = s->p[1].n.y;
    a0->items[a3].n[1].z = s->p[1].n.z;
    a0->items[a3].n[2].x = s->p[2].n.x;
    a0->items[a3].n[2].y = s->p[2].n.y;
    a0->items[a3].n[2].z = s->p[2].n.z;
    a0->items[a3].n[3].x = s->p[3].n.x;
    a0->items[a3].n[3].y = s->p[3].n.y;
    a0->items[a3].n[3].z = s->p[3].n.z;
}
// Matched
int sub_80024394(FtgPrimHeader* a0, FtgSrcPolyFT4* a1, FtgObject* a2, int a3)
{
    if (a0->flags_3 & 2)
    {
        SetSemiTrans(&a2->ft4_30.items[a3], 1);
    }
    sub_8002441C(&a2->ft4_30, a1, a0->flags_3, a3);
    return 0x2C;
}
// Matched
void sub_8002441C(FtgPolyFT4List* a0, FtgSrcPolyFT4* s, int a2, int a3)
{
    a0->items[a3].tpage = s->tex.tpage;
    a0->items[a3].clut = s->tex.clut;
    a0->items[a3].u0 = s->v[0].u;
    a0->items[a3].v0 = s->v[0].v;
    a0->items[a3].v[0].uv = a0->items[a3].u0 + (a0->items[a3].v0 << 8);
    a0->items[a3].u1 = s->v[1].u;
    a0->items[a3].v1 = s->v[1].v;
    a0->items[a3].v[1].uv = a0->items[a3].u1 + (a0->items[a3].v1 << 8);
    a0->items[a3].u2 = s->v[2].u;
    a0->items[a3].v2 = s->v[2].v;
    a0->items[a3].v[2].uv = a0->items[a3].u2 + (a0->items[a3].v2 << 8);
    a0->items[a3].u3 = s->v[3].u;
    a0->items[a3].v3 = s->v[3].v;
    a0->items[a3].v[3].uv = a0->items[a3].u3 + (a0->items[a3].v3 << 8);
    a0->items[a3].c.r = 0x80;
    a0->items[a3].c.g = 0x80;
    a0->items[a3].c.b = 0x80;
    a0->items[a3].c.code = a2;
    a0->items[a3].v[0].x = s->v[0].x;
    a0->items[a3].v[0].y = s->v[0].y;
    a0->items[a3].v[0].z = s->v[0].z;
    a0->items[a3].v[1].x = s->v[1].x;
    a0->items[a3].v[1].y = s->v[1].y;
    a0->items[a3].v[1].z = s->v[1].z;
    a0->items[a3].v[2].x = s->v[2].x;
    a0->items[a3].v[2].y = s->v[2].y;
    a0->items[a3].v[2].z = s->v[2].z;
    a0->items[a3].v[3].x = s->v[3].x;
    a0->items[a3].v[3].y = s->v[3].y;
    a0->items[a3].v[3].z = s->v[3].z;
    a0->items[a3].n.x = s->n.x;
    a0->items[a3].n.y = s->n.y;
    a0->items[a3].n.z = s->n.z;
}
// Matched
void sub_8002467C(FtgSrcPolyFT4* p, int arg1)
{
    RelocateTPageClut_80022AE8(&p->tex.tpage, &p->tex.clut, arg1);
}
// Matched
int sub_800246A0(FtgPrimHeader* a0, FtgSrcPolyGT4* a1, FtgObject* a2, int a3)
{
    if (a0->flags_3 & 2)
    {
        SetSemiTrans(&a2->gt4_38.items[a3], 1);
    }
    sub_80024730(&a2->gt4_38, a1, a0->flags_3, a3);
    return 0x54;
}
// Matched
void sub_80024730(FtgPolyGT4List* a0, FtgSrcPolyGT4* s, int a2, int a3)
{
    a0->items[a3].tpage = s->tex.tpage;
    a0->items[a3].clut = s->tex.clut;
    a0->items[a3].u0 = s->p[0].v.u;
    a0->items[a3].v0 = s->p[0].v.v;
    a0->items[a3].v[0].uv = a0->items[a3].u0 + (a0->items[a3].v0 << 8);
    a0->items[a3].u1 = s->p[1].v.u;
    a0->items[a3].v1 = s->p[1].v.v;
    a0->items[a3].v[1].uv = a0->items[a3].u1 + (a0->items[a3].v1 << 8);
    a0->items[a3].u2 = s->p[2].v.u;
    a0->items[a3].v2 = s->p[2].v.v;
    a0->items[a3].v[2].uv = a0->items[a3].u2 + (a0->items[a3].v2 << 8);
    a0->items[a3].u3 = s->p[3].v.u;
    a0->items[a3].v3 = s->p[3].v.v;
    a0->items[a3].v[3].uv = a0->items[a3].u3 + (a0->items[a3].v3 << 8);
    a0->items[a3].c[0].code = a2;
    a0->items[a3].c[0].r = s->c[0].r;
    a0->items[a3].c[0].g = s->c[0].g;
    a0->items[a3].c[0].b = s->c[0].b;
    a0->items[a3].c[1].r = s->c[1].r;
    a0->items[a3].c[1].g = s->c[1].g;
    a0->items[a3].c[1].b = s->c[1].b;
    a0->items[a3].c[2].r = s->c[2].r;
    a0->items[a3].c[2].g = s->c[2].g;
    a0->items[a3].c[2].b = s->c[2].b;
    a0->items[a3].c[3].r = s->c[3].r;
    a0->items[a3].c[3].g = s->c[3].g;
    a0->items[a3].c[3].b = s->c[3].b;
    a0->items[a3].v[0].x = s->p[0].v.x;
    a0->items[a3].v[0].y = s->p[0].v.y;
    a0->items[a3].v[0].z = s->p[0].v.z;
    a0->items[a3].v[1].x = s->p[1].v.x;
    a0->items[a3].v[1].y = s->p[1].v.y;
    a0->items[a3].v[1].z = s->p[1].v.z;
    a0->items[a3].v[2].x = s->p[2].v.x;
    a0->items[a3].v[2].y = s->p[2].v.y;
    a0->items[a3].v[2].z = s->p[2].v.z;
    a0->items[a3].v[3].x = s->p[3].v.x;
    a0->items[a3].v[3].y = s->p[3].v.y;
    a0->items[a3].v[3].z = s->p[3].v.z;
    a0->items[a3].n[0].x = s->p[0].n.x;
    a0->items[a3].n[0].y = s->p[0].n.y;
    a0->items[a3].n[0].z = s->p[0].n.z;
    a0->items[a3].n[1].x = s->p[1].n.x;
    a0->items[a3].n[1].y = s->p[1].n.y;
    a0->items[a3].n[1].z = s->p[1].n.z;
    a0->items[a3].n[2].x = s->p[2].n.x;
    a0->items[a3].n[2].y = s->p[2].n.y;
    a0->items[a3].n[2].z = s->p[2].n.z;
    a0->items[a3].n[3].x = s->p[3].n.x;
    a0->items[a3].n[3].y = s->p[3].n.y;
    a0->items[a3].n[3].z = s->p[3].n.z;
}
// Matched
void sub_80024AB8(FtgSrcPolyGT4* p, int arg1)
{
    RelocateTPageClut_80022AE8(&p->tex.tpage, &p->tex.clut, arg1);
}
// Matched
void InitModelList_80024ADC(struct_112_list** a0, void* a1, int heap)
{
    struct_112_list* l;
    int i;
    l = *a0 = (struct_112_list*)HeapAlloc_8003FC8C(0x10, (struct Pool*)heap);
    l->count = sub_80026600(a1);
    l->field_4 = heap;
    l->items = (struct_112*)HeapAlloc_8003FC8C(l->count * 0x70, (struct Pool*)heap);
    l->field_C = a1;
    for (i = 0; i < l->count; i++)
    {
        l->items[i].field_0 = (int)l;
        l->items[i].field_30 = i;
        ClearModel_800266CC(&l->items[i]);
    }
}
// Matched
void FreeModelList_80024BB0(struct_112_list** a0)
{
    struct_112_list* l = *a0;
    int i;
    for (i = 0; i < l->count; i++)
    {
        FreeModel_80024C48(&l->items[i]);
    }
    HeapFree_8003FD18(l->items, l->field_4);
    HeapFree_8003FD18(l, l->field_4);
    *a0 = 0;
}
// Matched
void FreeModel_80024C48(struct_112* p)
{
    int h;
    sub_80025AB0(p);
    sub_80025C38(p, 1);
    h = ((struct_112_list*)p->field_0)->field_4;
    if (p->field_44 != 0)
    {
        HeapFree_8003FD18(p->field_44, h);
    }
    if (p->field_4C != 0)
    {
        HeapFree_8003FD18(p->field_4C, h);
    }
    if (p->field_50 != 0)
    {
        FreeFtgObjects_80021784((int**)&p->field_50, p->field_3C, h);
    }
    if (p->field_54 != 0)
    {
        FreeModelAnims_8002679C((ModelAnim**)&p->field_54, p->field_3E, h);
    }
    if (p->field_58 != 0)
    {
        HeapFree_8003FD18(p->field_58, h);
    }
    if (p->field_60 != 0)
    {
        sub_80021E24(&p->field_5C, h);
    }
    if (p->field_64 != 0)
    {
        HeapFree_8003FD18(p->field_64, h);
    }
    if (p->field_68 != 0)
    {
        FreeFtgObjects_80021784((int**)&p->field_68, p->field_42, h);
    }
    if (p->field_6C != 0)
    {
        HeapFree_8003FD18(p->field_6C, h);
    }
    ClearModel_800266CC(p);
}
// Matched
struct_112* AcquireModel_80024D70(struct_112_list* p, unsigned int id)
{
    int i = FindModelIndex_80026630(p, id);
    if (i >= 0)
    {
        struct_112* r = &p->items[i];
        r->field_3A++;
        return r;
    }
    return 0;
}
// Matched
int AreFileRequestsDone_80024DC4(void* a0)
{
    struct_list10* p = a0;
    int i;
    i = 0;
    while (i < p->count)
    {
        if (GetFileRequestStatus_8003BE30(p->items[i]) != 0)
        {
            return 0;
        }
        i++;
    }
    p->count = 0;
    return 1;
}
// Matched
char* sub_80024E38(struct_obj_E* p)
{
    char* result = 0;
    int* hdr = p->field_4C;
    if (hdr && hdr[0])
    {
        result = (char*)hdr + hdr[0] + 4;
    }
    return result;
}
// Matched
char* sub_80024E64(struct_obj_E* p)
{
    char* result = 0;
    int* hdr = p->field_4C;
    if (hdr && hdr[1])
    {
        result = (char*)hdr + hdr[1];
    }
    return result;
}
// Matched
char* sub_80024E90(void* p, int n)
{
    char* r = sub_80024FA8(p, n);
    if (r)
    {
        r += ((ModelHeaderRecord*)r)->offsets_0[0];
    }
    return r;
}
// Matched
char* sub_80024EC8(void* p, int n)
{
    char* r = sub_80024FA8(p, n);
    if (r)
    {
        r += ((ModelHeaderRecord*)r)->offsets_0[1];
    }
    return r;
}
// Matched
char* sub_80024F00(void* p, int n)
{
    char* r = sub_80024FA8(p, n);
    if (r)
    {
        r += ((ModelHeaderRecord*)r)->offsets_0[2];
    }
    return r;
}
// Matched
char* sub_80024F38(void* p, int n)
{
    char* r = sub_80024FA8(p, n);
    if (r)
    {
        r += ((ModelHeaderRecord*)r)->offsets_0[3];
    }
    return r;
}
// Matched
char* sub_80024F70(void* p, int n)
{
    char* r = sub_80024FA8(p, n);
    if (r)
    {
        r += ((ModelHeaderRecord*)r)->offsets_0[4];
    }
    return r;
}
// Matched
char* sub_80024FA8(void* a0, int n)
{
    char* hdr = (char*)((struct_112*)a0)->field_4C;
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
void sub_80024FFC(struct_112* p, int* ids)
{
    int n;
    int heap;
    for (n = 0; ids[n] >= 0; n++)
    {
    }
    heap = ((struct_112_list*)p->field_0)->field_4;
    p->field_40 = n;
    p->field_64 = HeapAlloc_8003FC8C(n * sizeof(struct_58), heap);
    n--;
    while (n >= 0)
    {
        int id = ids[n];
        ((struct_58*)p->field_64)[n].id = id;
        ((struct_58*)p->field_64)[n].d = ((struct_54*)p->field_50)[id];
        n--;
    }
}
// Matched
void sub_8002512C(unsigned int* a0, struct_112* a1, int a2)
{
    int i;
    for (i = 0; i < a1->field_40; i++)
    {
        struct_58* e = (struct_58*)(i * 0x58 + a1->field_64);
        if (a2 == e->id)
        {
            MemCopy_800403E8(a0, (unsigned int*)&e->d, 0x54);
            break;
        }
    }
}
// Matched
void sub_800251A0(void* dst, struct_obj_E* src, int a2, int idx)
{
    MemCopy_800403E8((unsigned int*)dst, (unsigned int*)&src->field_50[idx], sizeof(struct_54));
}
// Matched
void nullsub_4(void)
{
}
// Matched
int GetModelDesc_800251E4(int idx)
{
    return modelDescs_800824CC[idx];
}
// Matched
int LoadModel_80025200(struct_112_list* a0, int id, int sel, int a3, int flag)
{
    ModelLoadParams b;
    FileRequestDesc c;
    int two = 1;
    int i;
    ModelDesc* e;
    struct_112* it;
    ModelVramSlot* x;
    int u;
    int v;
    i = FindModelIndex_80026630(a0, id);
    if (i >= 0)
    {
        return AreFileRequestsDone_80024DC4(&a0->items[i]) == 0;
    }
    i = FindFreeModelIndex_8002667C(a0);
    if (i >= 0)
    {
        e = (ModelDesc*)modelDescs_800824CC[id];
        it = &a0->items[i];
        x = (ModelVramSlot*)a0->field_C + i;
        InitModelLoadParams_80025ED0(&b);
        if (sel != -1)
        {
            b.flags_0 |= 3;
        }
        b.flags_0 |= 0xC;
        v = 0;
        b.model_14 = it;
        b.vram_18 = x;
        b.desc_4 = e;
        b.sel_8 = sel;
        b.mode_C = a3;
        if (sel != -1)
        {
            two = 0;
            v += e->header_2.size;
            v += e->tex_6.size;
            u = e->header_2.offset;
        }
        else
        {
            u = e->ftg_A.offset;
        }
        v += e->ftg_A.size;
        v += e->anims_E.size;
        c.fileId_4 = e->fileId_0;
        c.flags_0 = 0x68;
        if (flag == 1)
        {
            c.flags_0 = 0x6C;
        }
        else
        {
            c.flags_0 = 0x69;
        }
        c.offset_8 = u;
        c.size_C = v;
        c.dest_10 = 0;
        c.params_14 = &b;
        c.paramsSize_18 = 0x3C;
        c.callback_1C = OnModelFileLoaded_80025D7C;
        AddFileRequest_80025D00((struct_list10*)it, &c);
        if (two != 0)
        {
            InitModelLoadParams_80025ED0(&b);
            b.flags_0 = 1;
            b.model_14 = it;
            b.desc_4 = e;
            c.fileId_4 = e->fileId_0;
            c.flags_0 = 0x68;
            if (flag == 1)
            {
                c.flags_0 = 0x6C;
            }
            else
            {
                c.flags_0 = 0x69;
            }
            c.offset_8 = e->header_2.offset;
            c.size_C = e->header_2.size;
            c.params_14 = &b;
            c.paramsSize_18 = 0x3C;
            c.dest_10 = 0;
            c.callback_1C = OnModelFileLoaded_80025D7C;
            AddFileRequest_80025D00((struct_list10*)it, &c);
        }
        it->id_38 = id;
        return 1;
    }
    return 2;
}
#if 0
// Not matched (5 lines): the pointer-add form below fixes the &b scheduling and the v0/v1 choice, but gcc then folds
// k*2 into idx*4 + 0x14 instead of keeping (e[9] + k) * 2. The int form ((k + e[9]) * 2 + (int)e) keeps the sum but
// misplaces &b and the sum register (8 lines). Tried: operand orders, temporaries for e[9]/k, k/idx types, e[k + 1]
// double reads, statement order, shifts instead of *2; permuter 1500 iters
int LoadModelAnim_80025440(struct_112* p, int idx, int flag)
{
    ModelLoadParams b;
    FileRequestDesc c;
    unsigned short* e;
    unsigned short* t;
    int u;
    int v;
    int k;
    unsigned char* f = (unsigned char*)p->field_44 + idx;
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
        AddFileRequest_80025D00((struct_list10*)p, &c);
        return 1;
    }
    return AreFileRequestsDone_80024DC4(p) == 0;
}
#endif
INCLUDE_ASM(LoadModelAnim_80025440);
// Matched
void FreeModelAnim_8002556C(struct_112* p, int idx)
{
    if (((char*)p->field_44)[idx])
    {
        FreeModelAnimData_800269C4((ModelAnim*)p->field_54, p->field_3E, idx, ((struct_112_list*)p->field_0)->field_4);
        ((char*)p->field_44)[idx] = 0;
    }
}
// Matched
int IsModelAnimLoaded_800255D8(struct_112* p, int idx)
{
    return ((char*)p->field_44)[idx] != 0;
}
// Matched
int sub_800255F0(int a, int idx, int a2)
{
    struct_112_list* a0 = (struct_112_list*)a;
    ModelLoadParams b;
    FileRequestDesc c;
    struct_112* x = a0->items;
    ModelVramSlot* y = a0->field_C;
    ModelDesc* e = (ModelDesc*)modelDescs_800824CC[idx];
    InitModelLoadParams_80025ED0(&b);
    b.flags_0 = 2;
    b.sel_8 = a2;
    c.flags_0 = 0x69;
    b.model_14 = x;
    b.vram_18 = y;
    b.desc_4 = e;
    c.fileId_4 = e->fileId_0;
    c.offset_8 = e->tex_6.offset;
    c.size_C = e->tex_6.size;
    c.dest_10 = 0;
    c.params_14 = &b;
    c.paramsSize_18 = 0x3C;
    c.callback_1C = OnModelFileLoaded_80025D7C;
    AddFileRequest_80025D00((struct_list10*)x, &c);
    return 1;
}
// Matched
int sub_800256B8(int a, int id)
{
    struct_112_list* a0 = (struct_112_list*)a;
    ModelLoadParams b;
    FileRequestDesc c;
    struct_112* it = &a0->items[FindModelIndex_80026630(a0, id)];
    ModelDesc* e = (ModelDesc*)modelDescs_800824CC[it->id_38];
    InitModelLoadParams_80025ED0(&b);
    b.flags_0 = 8;
    b.model_14 = it;
    b.mode_C = 3;
    b.desc_4 = e;
    c.flags_0 = 0x69;
    c.fileId_4 = e->fileId_0;
    c.offset_8 = e->anims_E.offset;
    c.size_C = e->anims_E.size;
    c.dest_10 = 0;
    c.params_14 = &b;
    c.paramsSize_18 = 0x3C;
    c.callback_1C = OnModelFileLoaded_80025D7C;
    AddFileRequest_80025D00((struct_list10*)it, &c);
    return 1;
}
// Matched
int LoadModelAnimSet_80025780(struct_112* p, int idx, int flag)
{
    ModelLoadParams b;
    FileRequestDesc c;
    ModelDesc* e;
    char* t;
    int u;
    int v;
    FreeModelAnimSet_80025884(p);
    e = (ModelDesc*)modelDescs_800824CC[p->id_38];
    t = (char*)e + (e->animCount_12 * 6 + 0x14);
    u = ((unsigned short*)t)[idx * 2 + 1];
    v = ((unsigned short*)t)[idx * 2 + 2];
    InitModelLoadParams_80025ED0(&b);
    b.flags_0 = 0x20;
    b.model_14 = p;
    b.desc_4 = e;
    c.flags_0 = 0x68;
    if (flag != 0)
    {
        c.flags_0 = 0x6C;
    }
    else
    {
        c.flags_0 = 0x69;
    }
    c.fileId_4 = e->fileId_0;
    c.offset_8 = u;
    c.size_C = v;
    c.dest_10 = 0;
    c.params_14 = &b;
    c.paramsSize_18 = 0x3C;
    c.callback_1C = OnModelFileLoaded_80025D7C;
    AddFileRequest_80025D00((struct_list10*)p, &c);
    return 1;
}
// Matched
void FreeModelAnimSet_80025884(struct_112* p)
{
    int* list = (int*)p->field_58;
    if (list)
    {
        int heap = ((struct_112_list*)p->field_0)->field_4;
        int n = list[0];
        int i;
        for (i = 0; i < n; i++)
        {
            int id = ((int*)p->field_58)[i + 1];
            if (id >= 0)
            {
                FreeModelAnim_8002556C(p, id);
            }
        }
        HeapFree_8003FD18(p->field_58, heap);
        p->field_58 = 0;
    }
}
// Matched
int IsAnimInModelAnimSet_80025924(struct_112* p, int id)
{
    int* list = (int*)p->field_58;
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
int sub_80025974(struct_112* p, int idx, int flag)
{
    ModelLoadParams b;
    FileRequestDesc c;
    ModelDesc* e;
    char* t;
    int u;
    int v;
    struct_112_list* g;
    sub_80025AB0(p);
    e = (ModelDesc*)modelDescs_800824CC[p->id_38];
    t = (char*)e + (e->animCount_12 * 6 + 0x14);
    t += *(unsigned short*)t * 4 + 2;
    g = (struct_112_list*)p->field_0;
    u = ((unsigned short*)t)[idx * 2 + 1];
    v = ((unsigned short*)t)[idx * 2 + 2];
    InitModelLoadParams_80025ED0(&b);
    b.flags_0 = 0x40;
    b.model_14 = p;
    b.vram_18 = (ModelVramSlot*)g->field_C + p->field_30;
    b.sel_8 = p->field_34;
    b.desc_4 = e;
    c.flags_0 = 0x68;
    if (flag != 0)
    {
        c.flags_0 = 0x6C;
    }
    else
    {
        c.flags_0 = 0x69;
    }
    c.fileId_4 = e->fileId_0;
    c.offset_8 = u;
    c.size_C = v;
    c.dest_10 = 0;
    c.params_14 = &b;
    c.paramsSize_18 = 0x3C;
    c.callback_1C = OnModelFileLoaded_80025D7C;
    AddFileRequest_80025D00((struct_list10*)p, &c);
    return 1;
}
// Matched
void sub_80025AB0(struct_112* p)
{
    struct Pool* h = (struct Pool*)((struct_112_list*)p->field_0)->field_4;
    if (p->field_68)
    {
        FreeFtgObjects_80021784((int**)&p->field_68, p->field_42, h);
        p->field_42 = 0;
        p->field_68 = 0;
    }
    if (p->field_6C)
    {
        HeapFree_8003FD18(p->field_6C, h);
        p->field_43 = 0;
        p->field_6C = 0;
    }
}
// Matched
void sub_80025B20(void* dst, struct_obj_E* src, int idx)
{
    MemCopy_800403E8((unsigned int*)dst, (unsigned int*)&src->field_68[idx], sizeof(struct_54));
}
// Matched
void sub_80025B5C(struct_obj_E* p, int idx, int sel)
{
    struct_54 tmp;
    if (idx == sel)
    {
        sub_8002512C((unsigned int*)&tmp, (struct_112*)p, idx);
    }
    else if (sel < p->field_3C)
    {
        sub_800251A0(&tmp, p, idx, sel);
    }
    else
    {
        sub_80025B20(&tmp, p, sel - p->field_3C);
    }
    p->field_50[idx] = tmp;
}
// Matched
void sub_80025C38(struct_112* p, int flag)
{
    int i;
    for (i = 0; i < p->field_40; i++)
    {
        struct_58* e = (struct_58*)(i * 0x58 + p->field_64);
        sub_80025B5C(p, e->id, e->id);
    }
    if (flag)
    {
        for (i = 0; i < p->field_43; i++)
        {
            short* s = (short*)(i * 4 + p->field_6C);
            sub_80025B5C(p, s[0], s[1]);
        }
    }
}
// Matched
int AddFileRequest_80025D00(struct_list10* a0, FileRequestDesc* a1)
{
    if (a0->count < 10)
    {
        a1->offset_8 <<= 11;
        a1->size_C <<= 11;
        a0->items[a0->count] = QueueFileRequest_8003BC84(a1);
        a0->count += 1;
        return 1;
    }
    return 0;
}
// Matched
void OnModelFileLoaded_80025D7C(int* a0, int b)
{
    ModelLoadParams* p = (ModelLoadParams*)a0;
    if (p->flags_0 & 1)
    {
        p->header_1C = (ModelHeaderSection*)b;
        b += p->desc_4->header_2.size << 11;
    }
    if (p->flags_0 & 2)
    {
        p->tim_20 = (int*)b;
        b += p->desc_4->tex_6.size << 11;
    }
    if (p->flags_0 & 4)
    {
        p->ftg_24 = (int*)b;
        b += p->desc_4->ftg_A.size << 11;
    }
    if (p->flags_0 & 8)
    {
        p->anims_28 = (ModelAnimSection*)b;
        b += p->desc_4->anims_E.size << 11;
    }
    if (p->flags_0 & 0x10)
    {
        p->anim_2C = (char*)b;
    }
    if (p->flags_0 & 0x20)
    {
        p->animSet_30 = (ModelAnimSetSection*)b;
    }
    if (p->flags_0 & 0x40)
    {
        p->flags_0 |= 0x80;
        p->extra_38 = (unsigned char*)(b + ((int*)b)[1]);
        p->flags_0 |= 0x40;
        p->ftg2_34 = (int*)(b + ((int*)b)[2]);
        p->flags_0 |= 2;
        p->tim_20 = (int*)(b + ((int*)b)[3]);
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
void ParseModelFile_80025F14(ModelLoadParams* a0)
{
    if (a0->flags_0 & 1)
    {
        sub_80026014(a0);
    }
    if (a0->flags_0 & 2)
    {
        LoadModelTextures_8002607C(a0);
    }
    if (a0->flags_0 & 4)
    {
        LoadModelFtg_800260FC(a0);
    }
    if (a0->flags_0 & 8)
    {
        LoadModelAnims_800261C8(a0);
    }
    if (a0->flags_0 & 0x10)
    {
        LoadSingleModelAnim_800263CC(a0);
    }
    if (a0->flags_0 & 0x20)
    {
        LoadModelAnimSetSection_80026410(a0);
    }
    if (a0->flags_0 & 0x40)
    {
        sub_8002651C(a0);
    }
    if (a0->flags_0 & 0x80)
    {
        sub_8002659C(a0);
    }
}
// Matched
void sub_80026014(ModelLoadParams* a0)
{
    ModelHeaderSection* q = a0->header_1C;
    struct_112* p = a0->model_14;
    int h = ((struct_112_list*)p->field_0)->field_4;
    int n = q->size_0;
    int r;
    p->field_48 = n;
    r = HeapAlloc_8003FC8C(n, h);
    p->field_4C = r;
    MemCopy_800403E8((unsigned int*)r, (unsigned int*)a0->header_1C->data_4, n);
}
// Matched
void LoadModelTextures_8002607C(ModelLoadParams* a0)
{
    if (a0->sel_8 != -1)
    {
        struct_112* p = a0->model_14;
        LoadTiyTimsRelocated_80028FDC(0, 0, 0, (int)a0->tim_20, GetTiyFileCount_80028E68(a0->tim_20), (int)a0->vram_18->reloc_4, a0->sel_8);
        p->field_34 = a0->sel_8;
    }
}
#if 0
// Not matched: the a0[9] list argument is loaded before the a0[6] load in the original, ours after; insensitive to statement order, types and temporaries
void LoadModelFtg_800260FC(ModelLoadParams* a0)
{
    int q = (int)a0->vram_18;
    struct_112* p = a0->model_14;
    int h = ((struct_112_list*)p->field_0)->field_4;
    q += 4;
    p->field_3C = GetFtgObjectCount_80021738(a0->ftg_24);
    AllocFtgObjects_80021744(&p->field_50, p->field_3C, h);
    LoadFtgObjects_80021824(a0->ftg_24, (FtgObject*)p->field_50, p->field_3C, h, q);
    if (sub_80021DE4(a0->ftg_24) != 0)
    {
        sub_80021DF0(&p->field_5C, sub_80021DE4(a0->ftg_24), h);
        sub_80021E4C(a0->ftg_24, &p->field_5C, sub_80021DE4(a0->ftg_24));
    }
}
#endif
INCLUDE_ASM(LoadModelFtg_800260FC);
// Matched
void LoadModelAnims_800261C8(ModelLoadParams* a0)
{
    struct_112* p = a0->model_14;
    int h = ((struct_112_list*)p->field_0)->field_4;
    int i;
    int j;
    int mode;
    p->field_3E = a0->desc_4->animCount_12;
    if (p->field_54 == 0)
    {
        AllocModelAnims_80026730((ModelAnim**)&p->field_54, p->field_3E, h);
    }
    if (p->field_44 != 0)
    {
        HeapFree_8003FD18(p->field_44, h);
    }
    p->field_44 = HeapAlloc_8003FC8C(p->field_3E, h);
    for (i = 0; i < p->field_3E; i++)
    {
        mode = a0->mode_C;
        if (mode == 0)
        {
            if (i == 0)
            {
                ((unsigned char*)p->field_44)[0] = 1;
            }
            else
            {
                ((unsigned char*)p->field_44)[i] = 0;
            }
        }
        else if (mode == 1)
        {
            if (i == 0)
            {
                ((unsigned char*)p->field_44)[0] = 1;
            }
            else if (i == 1)
            {
                ((unsigned char*)p->field_44)[1] = 1;
            }
            else
            {
                ((unsigned char*)p->field_44)[i] = 0;
            }
        }
        else if (mode == 3)
        {
            if (i == 0)
            {
                ((unsigned char*)p->field_44)[0] = 0;
            }
            else if (i == 1)
            {
                ((unsigned char*)p->field_44)[1] = 0;
            }
            else
            {
                ((unsigned char*)p->field_44)[i] = *(unsigned char*)&a0->desc_4->animFlags_14[i];
            }
        }
        else
        {
            ((unsigned char*)p->field_44)[i] = *(unsigned char*)&a0->desc_4->animFlags_14[i];
        }
    }
    for (i = 0, j = 0; i < p->field_3E; i++)
    {
        if ((&a0->desc_4->animFlags_14[0])[i] != 0) // indexed through the decayed pointer, as the original
        {
            if (((unsigned char*)p->field_44)[i] != 0)
            {
                LoadModelAnimData_80026A8C(&((ModelAnim*)p->field_54)[i], (int)a0->anims_28 + (&a0->anims_28->offsets_4[0])[j], h);
            }
            j++;
        }
    }
}
// Matched
void LoadSingleModelAnim_800263CC(ModelLoadParams* p)
{
    struct_112_list* l;
    struct_112* q = p->model_14;
    l = (struct_112_list*)q->field_0;
    LoadModelAnimData_80026A8C(&((ModelAnim*)q->field_54)[p->animIdx_10], (int)p->anim_2C, l->field_4);
}
// Matched
void LoadModelAnimSetSection_80026410(ModelLoadParams* a0)
{
    ModelAnimSetSection* q = a0->animSet_30;
    struct_112* p = a0->model_14;
    int n = q->count_0;
    int h = ((struct_112_list*)p->field_0)->field_4;
    int* list = (int*)HeapAlloc_8003FC8C((n + 1) * 4, h);
    int i;
    int id;
    int src;
    p->field_58 = (int)list;
    list[0] = n;
    for (i = 0; i < n; i++)
    {
        id = q->items_4[i].id;
        src = (int)q + q->items_4[i].offset;
        if (((unsigned char*)p->field_44)[id] == 0)
        {
            ((int*)p->field_58)[i + 1] = id;
            ((unsigned char*)p->field_44)[id] = 1;
            LoadModelAnimData_80026A8C(&((ModelAnim*)p->field_54)[id], src, h);
        }
        else
        {
            ((int*)p->field_58)[i + 1] = -1;
        }
    }
}
#if 0
// Not matched: the original loads the list argument (+0x34) right after the owner pointer, ours schedules it first (same as LoadModelFtg_800260FC)
void sub_8002651C(ModelLoadParams* a)
{
    struct_112* p = a->model_14;
    int* list = a->ftg2_34;
    int heap = ((struct_112_list*)p->field_0)->field_4;
    short* q = a->vram_18->reloc_4;
    p->field_42 = GetFtgObjectCount_80021738(list);
    AllocFtgObjects_80021744(&p->field_68, p->field_42, heap);
    LoadFtgObjects_80021824(a->ftg2_34, (FtgObject*)p->field_68, p->field_42, heap, (int)q);
}
#endif
INCLUDE_ASM(sub_8002651C);
// Matched
void sub_8002659C(ModelLoadParams* a0)
{
    unsigned char* q = a0->extra_38;
    struct_112* p = a0->model_14;
    int h = ((struct_112_list*)p->field_0)->field_4;
    int r;
    p->field_43 = *q;
    q += 4;
    r = HeapAlloc_8003FC8C(p->field_43 << 2, h);
    p->field_6C = r;
    MemCopy_800403E8((unsigned int*)r, (unsigned int*)q, p->field_43 << 2);
}
// Matched
int sub_80026600(struct_16_b* p)
{
    int n = 0;
    if (p->field_2 != -1)
    {
        do
        {
            p++;
            n++;
        } while (p->field_2 != -1);
    }
    return n;
}
// Matched
int FindModelIndex_80026630(struct_112_list* p, unsigned int id)
{
    int i;
    for (i = 0; i < p->count; i++)
    {
        if (p->items[i].id_38 == id)
        {
            return i;
        }
    }
    return -1;
}
// Matched
int FindFreeModelIndex_8002667C(struct_112_list* p)
{
    int i;
    for (i = 0; i < p->count; i++)
    {
        if (p->items[i].id_38 == 0xFFFF)
        {
            return i;
        }
    }
    return -1;
}
// Matched
void ClearModel_800266CC(struct_112* p)
{
    p->id_38 = 0xFFFF;
    p->field_4 = 0;
    p->field_34 = 0;
    p->field_3A = 0;
    p->field_3C = 0;
    p->field_3E = 0;
    p->field_40 = 0;
    p->field_42 = 0;
    p->field_43 = 0;
    p->field_44 = 0;
    p->field_48 = 0;
    p->field_4C = 0;
    p->field_50 = 0;
    p->field_54 = 0;
    p->field_58 = 0;
    p->field_5C = 0;
    p->field_60 = 0;
    p->field_64 = 0;
    p->field_68 = 0;
    p->field_6C = 0;
}
// Matched
int sub_80026724(int* p)
{
    return p[0];
}
// Matched
void AllocModelAnims_80026730(ModelAnim** a0, int a1, int a2)
{
    ModelAnim* p = (ModelAnim*)HeapAlloc_8003FC8C(a1 * 28, a2);
    int i;
    *a0 = p;
    for (i = 0; i < a1; i++)
    {
        p[i].cues_10 = 0;
        p[i].basePose_14 = 0;
        p[i].frames_18 = 0;
    }
}
// Matched
void FreeModelAnims_8002679C(ModelAnim** a0, int n, int heap)
{
    ModelAnim* arr;
    int i;
    if (*a0)
    {
        arr = *a0;
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
        *a0 = 0;
    }
}
// Matched
void sub_80026870(ModelAnim** a0, int a1, int a2)
{
    int r = sub_80026724((int*)a1);
    AllocModelAnims_80026730(a0, r, a2);
    sub_800268E8(a0[0], a1, r, a2, -1);
}
// Matched
void sub_800268E8(ModelAnim* a0, int a1, int n, int h, int mask)
{
    int* q = (int*)a1;
    int i;
    for (i = 0; i < n; i++, a0++)
    {
        int bit = 1 << i;
        if ((mask & bit) && a0->basePose_14 == 0 && a0->frames_18 == 0)
        {
            LoadModelAnimData_80026A8C(a0, a1 + q[i + 1], h);
        }
    }
}
// Matched
void FreeModelAnimData_800269C4(ModelAnim* a0, int n, int sel, int h)
{
    ModelAnim* p = a0;
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
void LoadModelAnimData_80026A8C(ModelAnim* a0, int a1, int a2)
{
    int f1 = 0;
    int f2 = f1;
    unsigned int n;
    unsigned int m;
    unsigned short* s;
    unsigned short* d;
    unsigned int i;
    unsigned int j;
    int r;
    int k;
    a0->frameCount_0 = ((ModelAnimFile*)a1)->frameCount_0;
    n = a0->frameCount_0;
    a0->boneCount_4 = ((ModelAnimFile*)a1)->boneCount_4;
    m = a0->boneCount_4;
    if ((int)n < 0)
    {
        n &= 0x7FFFFFFF;
        s = (unsigned short*)(((int*)a1) + 3);
        a0->frameCount_0 = n;
        a0->divisor_8 = ((ModelAnimFile*)a1)->divisor_8;
        f1 = 1;
    }
    else
    {
        a0->divisor_8 = 0x20;
        s = (unsigned short*)(((int*)a1) + 2);
    }
    if ((int)m < 0)
    {
        m &= 0x7FFFFFFF;
        f2 = 1;
    }
    else
    {
        a0->cueCount_C = 0;
    }
    a0->basePose_14 = (unsigned short*)HeapAlloc_8003FC8C(m * 6, (struct Pool*)a2);
    a0->frames_18 = (unsigned short*)HeapAlloc_8003FC8C((m + 2) * (n << 1) * 3, (struct Pool*)a2);
    d = a0->basePose_14;
    for (i = 0; i < m; i++)
    {
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
    }
    d = a0->frames_18;
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
    if (f2)
    {
        r = m * 6 + 8;
        r += (m * 6 + 0xC) * n;
        if (f1)
        {
            r += 4;
        }
        s = (unsigned short*)((char*)((int*)a1) + r);
        if (r & 3)
        {
            r += 2;
            s = (unsigned short*)((char*)((int*)a1) + r);
        }
        a0->cueCount_C = *(int*)s;
        s += 2;
        a0->cues_10 = (ModelAnimCue*)HeapAlloc_8003FC8C(a0->cueCount_C * 8, (struct Pool*)a2);
        k = 0;
        while (k < a0->cueCount_C)
        {
            a0->cues_10[k].frame_0 = s[0];
            a0->cues_10[k].kind_2 = s[1];
            a0->cues_10[k].arg_4 = s[2];
            a0->cues_10[k].arg_6 = s[3];
            k++;
            s += 4;
        }
    }
}
// Matched
int sub_80026D6C(int* p)
{
    return p[0];
}
// Matched
void sub_80026D78(struct_12** a0, int a1, int a2)
{
    struct_12* p = (struct_12*)HeapAlloc_8003FC8C(a1 * 12, a2);
    int i;
    for (i = 0; i < a1; i++)
    {
        p[i].field_0 = 0;
        p[i].field_4 = 0;
        p[i].field_8 = 0;
    }
    *a0 = p;
}
// Matched
void sub_80026DE8(struct_12** a0, int n, int h)
{
    struct_12* p = *a0;
    int i;
    for (i = 0; i < n; i++, p++)
    {
        if (p->field_8 != 0)
        {
            HeapFree_8003FD18(p->field_8, h);
        }
    }
    HeapFree_8003FD18(*a0, h);
    *a0 = 0;
}
// Matched
void sub_80026E74(struct_12* a0, int* a1, int a2)
{
    int i;
    for (i = 0; i < sub_80026D6C(a1); i++)
    {
        sub_80026EF8(a0, (unsigned short*)((char*)a1 + a1[i + 1]), a2);
        a0++;
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
void sub_80026EF8(struct_12* p, unsigned short* s, int a2)
{
    unsigned short* d;
    int i;
    p->field_0 = *(int*)s;
    s += 2;
    p->field_4 = *(int*)s;
    s += 2;
    d = (unsigned short*)HeapAlloc_8003FC8C(p->field_0 * 8, a2);
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
extern struct_8008D648 dword_8008D648;
extern int* dword_80082674;
extern int dword_80091C98;
extern int dword_80091C94;
extern int dword_80091C5C;
extern int dword_80091C58;
extern int dword_80091C90;
extern int dword_80091C9C;
extern int dword_80091C8C;
typedef struct
{
    int pos[3];
    int mapIdx;
} struct_80091C78;
extern struct_80091C78 stru_80091C78;
extern int dword_800B1DC8;
extern int dword_80091C54;
extern short word_80091CB8[];
extern int dword_80091C10;
extern int dword_80091C68;
extern int dword_80091C48;
// Matched
void sub_80026FAC(void)
{
    ListInit_8003FDB0(&dword_80091C68);
    ListInit_8003FDB0(&dword_80091C20);
    ListInit_8003FDB0(&dword_80091C10);
    ListInit_8003FDB0(&dword_80091C48);
    dword_80091C30[0] = 0x3A;
    dword_80091C30[1] = 0;
    dword_80091C30[2] = 0;
    dword_80091C30[3] = -1;
    dword_8008B500[1] = 0;
    dword_8008B500[2] = 0;
    dword_8008B500[3] = 0;
    dword_8008B500[10] = 0;
    dword_8008B500[14] = 0;
    dword_8008B500[15] = 0;
    dword_8008D648.count_0 = 0;
    dword_8008D648.field_4 = 0;
    dword_8008D648.field_8 = 0;
    dword_8008D648.items_C = 0;
    dword_8008D648.field_4 = 0;
    dword_8008D648.field_8 = 0;
    dword_8008D648.listCount_10 = 0;
    dword_8008D648.lists_14 = 0;
    dword_8008D648.pairs_18 = 0;
    dword_80091C88 = -1;
    dword_80091C44 = -1;
    dword_80082674 = 0;
    dword_80091C98 = 0;
    dword_80091C94 = 0;
    dword_80091C5C = 1;
    dword_80091C58 = 1;
    dword_80091C90 = 0;
    dword_80091CA0 = 0;
    dword_80091C9C = 0;
    dword_80091C8C = 0;
    stru_80091C78.mapIdx = -1;
    dword_80091C54 = dword_800B1DC8;
    word_80091CB8[7] = -1;
    word_80091CB8[6] = -1;
    word_80091CB8[5] = -1;
    word_80091CB8[4] = -1;
    word_80091CB8[3] = -1;
    word_80091CB8[2] = -1;
    word_80091CB8[1] = -1;
    word_80091C40[0] = -1;
    word_80091CB8[0] = -1;
    word_80091C40[1] = -1;
    dword_80082678 = 0;
    InitActors_8001D378();
}
extern int dword_80091C74;
extern int dword_80091CB4;
extern int dword_80082668;
extern int dword_8008266C;
extern EventNode* dword_800B1DA8;
extern EventNode* dword_8008D400;
extern EventNode* messageWindowTask_8008D640;
extern EventNode* dword_8008D49C;
extern EventNode* dword_8008D674;
extern EventNode* fileRequestTasks_8008D488;
extern void FreeActors_8001D3C4(int a0);
extern void sub_800AC73C(void);
extern void sub_800A54A0(void);
extern void sub_800A58B4(void);
extern void sub_800A7784(void);
extern void sub_800A170C(void);
extern void sub_800A1794(void);
// Matched
void sub_80027118(void)
{
    word_80091CB8[7] = -1;
    word_80091CB8[6] = -1;
    word_80091CB8[5] = -1;
    word_80091CB8[4] = -1;
    word_80091CB8[3] = -1;
    word_80091CB8[2] = -1;
    word_80091CB8[1] = -1;
    word_80091C40[0] = -1;
    word_80091CB8[0] = -1;
    word_80091C40[1] = -1;
    sub_8002741C();
    dword_80082678 = 0;
    dword_80091C74 = -1;
    dword_80091CB4 = 0;
    dword_80091C88 = -1;
    dword_80082668 = 0;
    dword_8008266C = 0;
    if (dword_80091C8C == 0)
    {
        StopAllEventEntries_80043B40(dword_800B1DA8);
        StopAllEventEntries_80043B40(dword_8008D400);
    }
    sub_800AC73C();
    StopAllEventEntries_80043B40(messageWindowTask_8008D640);
    StopAllEventEntries_80043B40(dword_8008D49C);
    StopAllEventEntries_80043B40(dword_8008D674);
    StopAllEventEntries_80043B40(fileRequestTasks_8008D488);
    sub_800A54A0();
    sub_800A58B4();
    FreeActors_8001D3C4(dword_80091CA0);
    sub_800A7784();
    sub_800A170C();
    sub_800A1794();
    ListFreeAll_8003FEC8(&dword_80091C10);
    ListFreeAll_8003FEC8(&dword_80091C68);
    if (!(unknownFlags_8008D678 & 0x20000))
    {
        ListFreeAll_8003FEC8(&dword_80091C48);
    }
}
// Matched
void sub_8002728C(void)
{
    dword_80091C44 = -1;
    ListFreeAll_8003FEC8(&dword_80091C20);
}
// Matched
void sub_800272BC(int a0, int a1)
{
    dword_80091C88 = a0;
    dword_80091C44 = a1;
}
#if 0
// Not matched (close)
int sub_800272D0(void)
{
    int* a = dword_800B1DC4[0x24 / 4];
    int* b = dword_800B1DB8[0x24 / 4];
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
int sub_800272D0(void)
{
    int* a = dword_800B1DC4[9];
    int* b = dword_800B1DB8[9];
    if (a[0] != 0 || b[0] != 0)
    {
        return 1;
    }
    return 0;
}
// Matched
void sub_80027314(void)
{
    dword_80082670 = 1;
    word_8008B862 = -1;
}
// Matched
int sub_80027330(short a0)
{
    if (dword_80082678 == 0)
    {
        word_80091C40[0] = a0;
        return 1;
    }
    return 0;
}
// Matched
// Matched
int sub_80027358(int id)
{
    int* p;
    short* s;
    if (dword_80082678 == 1)
    {
        if (word_80091C40[0] != id)
        {
            word_8008B860 = id;
            return 0;
        }
        p = dword_800B1DB8[9];
        if (GetFileRequestStatus_8003BE30(p[1]) != 3)
        {
            return 0;
        }
        sub_8002728C();
        ConsumeFileRequest_8003BFD0(p[1], 0);
        sub_80028DC0();
        s = (short*)&saveData_8008B570;
        s[0x2F0 / 2] = id;
        s[0x2F2 / 2] = id;
        dword_80082678 = 0;
        return 1;
    }
    word_8008B860 = id;
    return 0;
}
// Matched
void sub_8002741C(void)
{
    int* p;
    if (dword_80082678 == 1)
    {
        p = dword_800B1DB8[9];
        CancelFileRequest_8003C060(p[1]);
        dword_80082678 = 0;
        p[0] = 0;
    }
}
// Matched
void sub_80027478(int mask, int set)
{
    int f;
    int code;
    if (set)
    {
        dword_80091C30[2] |= mask;
    }
    else
    {
        dword_80091C30[2] &= ~mask;
    }
    f = dword_80091C30[2];
    if (f && !(f & 1))
    {
        code = 0;
        if (!(f & 0x40))
        {
            if (dword_80091C30[0] & f)
            {
                code = 1;
            }
            else if (dword_80091C30[1] & f)
            {
                code = 2;
            }
        }
        dword_80091C30[2] |= 1;
        SetFadeMode_8001C19C(code, 0x20);
    }
}
// Matched
int sub_80027540(void)
{
    int* g = dword_80091C30;
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
void sub_800275E8(char** a0, int a1, int a2)
{
    char* p;
    char* q;
    int i;
    if (a1 != 0)
    {
        p = (char*)ListAlloc_8003FDC0(a2, a1);
        *a0 = p;
        q = p;
        for (i = 0; i < a1; i++)
        {
            q[i] = 1;
        }
    }
}
// Matched
int* sub_80027650(int* a0, int a1, int h)
{
    int* src;
    int* d;
    int n;
    int i;
    int* g = dword_80091C60;
    a0 += 1;
    n = *a0++;
    src = a0;
    g[0] = n;
    if (n != 0)
    {
        d = (int*)ListAlloc_8003FDC0(h, n * 16);
        g[1] = (int)d;
        for (i = 0; i < g[0]; i++)
        {
            d[0] = src[0];
            d[1] = src[1];
            d[2] = src[2];
            d[3] = src[3];
            d += 4;
            src += 4;
        }
    }
    return src;
}
// Matched
void sub_80027708(int* a0, int a1)
{
    int r = GetFtgObjectCount_80021738(a0);
    dword_8008B500[0x38 / 4] = r;
    if (r != 0)
    {
        AllocFtgObjects_80021744(&dword_8008B500[0x3C / 4], r, a1);
        LoadFtgObjects_80021824(a0, dword_8008B500[0x3C / 4], dword_8008B500[0x38 / 4], a1, 0);
    }
}
// Matched
void sub_80027778(int* a0, int h)
{
    struct_27778* arr;
    unsigned int i;
    int j;
    int* src;
    unsigned short* q;
    int n;
    dword_8008D648.field_4 = a0[0];
    dword_8008D648.field_8 = a0[1];
    n = a0[2];
    dword_8008D648.count_0 = n;
    arr = (struct_27778*)ListAlloc_8003FDC0(h, n * 16);
    for (i = 0; i < dword_8008D648.count_0; i++)
    {
        src = (int*)((char*)a0 + a0[i + 3]);
        arr[i].field_0 = *src++;
        arr[i].count = *src++;
        q = (unsigned short*)src;
        arr[i].field_8 = *q++;
        arr[i].field_A = *q++;
        arr[i].items = (unsigned short*)ListAlloc_8003FDC0(h, arr[i].count * 2);
        for (j = 0; j < arr[i].count; j++)
        {
            arr[i].items[j] = *q++;
        }
    }
    dword_8008D648.items_C = arr;
}
// Matched
void sub_800278BC(int* a, int h)
{
    int* a0 = a;
    unsigned int i;
    unsigned int j;
    int n;
    int* q;
    struct_4b* r;
    struct_2s* e;
    n = a0[0];
    dword_8008D648.listCount_10 = n;
    dword_8008D648.lists_14 = ListAlloc_8003FDC0(h, n * 8);
    for (i = 0; i < dword_8008D648.listCount_10; i++)
    {
        q = (int*)((char*)a0 + a0[i + 1]);
        dword_8008D648.lists_14[i].count = *q;
        dword_8008D648.lists_14[i].items = (struct_4b*)ListAlloc_8003FDC0(h, dword_8008D648.lists_14[i].count * 4);
        r = (struct_4b*)(q + 1);
        for (j = 0; j < dword_8008D648.lists_14[i].count; j++)
        {
            dword_8008D648.lists_14[i].items[j].a = r[j].a;
            dword_8008D648.lists_14[i].items[j].b = r[j].b;
            dword_8008D648.lists_14[i].items[j].c = r[j].c;
        }
    }
    dword_8008D648.pairs_18 = ListAlloc_8003FDC0(h, dword_8008D648.listCount_10 * 4);
    for (i = 0; i < dword_8008D648.listCount_10; i++)
    {
        e = (struct_2s*)(i * 4 + (int)dword_8008D648.pairs_18); // integer sum, as the original
        e->b = 0;
        e->a = 0;
    }
}
typedef struct
{
    short x;
    short y;
    short z;
    short pad;
} struct_a88_sv;
typedef struct
{
    int field_0;
    struct_a88_sv v[4];
} struct_a88_24;
typedef struct
{
    struct_a88_sv v[4];
} struct_20v;
typedef struct
{
    unsigned short n;
    struct_20v* items;
} struct_8_20v;
#if 0
// Not matched: s1/s2 swapped (p vs arr+i) and the source-item address is strength-reduced differently
int* sub_80027A88(struct_8_20v** out, int* count, int heap, int* hdr)
{
    struct_8_20v* arr;
    unsigned int i;
    unsigned int j;
    unsigned char* p;
    unsigned char* rec;
    int* hh;
    p = (unsigned char*)hdr + 0x10;
    hh = hdr;
    arr = (struct_8_20v*)ListAlloc_8003FDC0(heap, hdr[1] * 8);
    *count = hdr[1];
    if (hdr[1] == 0)
    {
        *out = 0;
        return (int*)((unsigned char*)hdr + hdr[0]);
    }
    for (i = 0; i < hh[1]; i++)
    {
        rec = p;
        arr[i].n = *(unsigned short*)rec;
        p = rec + 0x28;
        arr[i].items = (struct_20v*)ListAlloc_8003FDC0(heap, *(int*)rec * 32);
        for (j = 0; j < *(unsigned int*)rec; j++)
        {
            arr[i].items[j].v[3].x = ((struct_a88_24*)(rec + 0x2C))[j].v[0].x;
            arr[i].items[j].v[3].y = ((struct_a88_24*)(rec + 0x2C))[j].v[0].y;
            arr[i].items[j].v[3].z = ((struct_a88_24*)(rec + 0x2C))[j].v[0].z;
            arr[i].items[j].v[3].pad = 0;
            arr[i].items[j].v[0].x = ((struct_a88_24*)(rec + 0x2C))[j].v[1].x;
            arr[i].items[j].v[0].y = ((struct_a88_24*)(rec + 0x2C))[j].v[1].y;
            arr[i].items[j].v[0].z = ((struct_a88_24*)(rec + 0x2C))[j].v[1].z;
            arr[i].items[j].v[0].pad = 0;
            arr[i].items[j].v[1].x = ((struct_a88_24*)(rec + 0x2C))[j].v[2].x;
            arr[i].items[j].v[1].y = ((struct_a88_24*)(rec + 0x2C))[j].v[2].y;
            arr[i].items[j].v[1].z = ((struct_a88_24*)(rec + 0x2C))[j].v[2].z;
            arr[i].items[j].v[1].pad = 0;
            arr[i].items[j].v[2].x = ((struct_a88_24*)(rec + 0x2C))[j].v[3].x;
            arr[i].items[j].v[2].y = ((struct_a88_24*)(rec + 0x2C))[j].v[3].y;
            arr[i].items[j].v[2].z = ((struct_a88_24*)(rec + 0x2C))[j].v[3].z;
            arr[i].items[j].v[2].pad = 0;
            p += 0x28;
        }
    }
    *out = arr;
    return (int*)((unsigned char*)hdr + hh[0]);
}
#endif
INCLUDE_ASM(sub_80027A88);
// Matched
void sub_80027CC0(EventEntry* p, int* q)
{
    q[0] = 0;
    q[1] = 0;
    sub_80027CF8(p, q);
    p->cb_8 = (EventEntryFn)sub_80027CF8;
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
extern MapEntry16** dword_800B0608[];
#define MAP_ENTRY_CF8(i) dword_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0][i]
extern int dword_800B0EC0;
extern int dword_80091CB0;
extern void sub_800ADDAC(void);
extern int sub_800A683C(int a0);
extern void sub_800AD124(int a0);
extern int sub_800A5030(int a0, int a1, int a2);
extern void sub_800A52AC(int a0);
extern int sub_800AC38C(void);
extern int sub_800AD154(int a0);
extern void sub_800B88A4(int a0);
extern void PlayMusic_800300E0(int a, int b);
extern void sub_80028808(void* a0, int* a1);
// Matched
void sub_80027CF8(void* a0, int* a)
{
    int* a1 = a;
    short v[2];
    FileRequestDesc req;
    MapEntry16* e;
    int t;
    int m;
    int n;
    int k;
    switch (a1[0])
    {
    case 0:
        m = dword_800B0EC0;
        if (m == 1 && sub_80020D84() == 0)
        {
            eventDispatchHalt_8008B540 = m;
        }
        else if (sub_80027540() != 0)
        {
            if (dword_80091C9C != 1 &&
                saveData_8008B570.mapId_2E4[0].field_2 == saveData_8008B570.mapId_2E4[0].field_0 &&
                saveData_8008B570.mapId_2E4[1].field_2 == saveData_8008B570.mapId_2E4[1].field_0 &&
                saveData_8008B570.mapId_2E4[2].field_2 == saveData_8008B570.mapId_2E4[2].field_0)
            {
            }
            else
            {
                if (dword_80091C54)
                {
                    sub_800ADDAC();
                }
                if (sub_800A683C(-1) != MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).f6)
                {
                    sub_800AD124(0);
                }
                e = dword_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0];
                for (dword_80091CB0 = 0; e[dword_80091CB0].f0 != -1; dword_80091CB0++)
                {
                }
                v[1] = MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_2).f6;
                v[0] = MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).f6;
                t = sub_800A5030(v[0], v[1], dword_80091C90);
                sub_800A52AC(v[0]);
                dword_80091C54 = 1;
                dword_80082670 = 0;
                dword_80091C9C = 0;
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
                sub_80025C38((struct_112*)sub_800AC38C(), (((unsigned int)unknownFlags_8008D678 >> 24) ^ 1) & 1);
                dword_80091CA0 = 0;
                if (dword_80091C90 != 0 || MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).fA != 0 || t != 0)
                {
                    dword_80091CA0 = 1;
                }
                dword_80091C90 = MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).fA;
                sub_80027118();
                sub_8002728C();
                m = MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).f8;
                if (m >= 0)
                {
                    if (sub_800AD154(12) == 1 && m == 0xD)
                    {
                        m = 0xF;
                    }
                    else if (sub_800AD154(12) == 2 && m == 0xD)
                    {
                        m = 0x91;
                    }
                    else if (sub_800AD154(12) == 3 && m == 0x29)
                    {
                        m = 0x26;
                    }
                    else if (sub_800AD154(12) == 4 && m == 0x2A)
                    {
                        m = 0x25;
                    }
                    PlayMusic_800300E0(m, 1);
                    sub_800315D8(m);
                    sub_80027478(0x20, 1);
                }
                if (dword_80091C90 == 0 && dword_80091C58 != 0)
                {
                    sub_800B88A4(t);
                    k = a1[0];
                    eventDispatchHalt_8008B540 = 1;
                    n = k;
                    a1[0] = n + 1;
                    sub_80027478(0x10, 1);
                    break;
                }
                a1[0] += 1;
            }
        }
        if (a1[0] != 1)
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
        req.callback_1C = sub_80028808;
        a1[1] = QueueFileRequest_8003BC84(&req);
        sub_80027478(2, 1);
        {
            int z = a1[0];
            eventDispatchHalt_8008B540 = 1;
            a1[0] = z + 1;
        }
        break;
    case 2:
        if (IsSoundTaskReady_800306B0() && IsModelLoaderDone_800205D0() && GetFileRequestStatus_8003BE30(a1[1]) == 0)
        {
            sub_80027478(0x72, 0);
            a1[0] = 0;
        }
        else
        {
            eventDispatchHalt_8008B540 = 1;
        }
        break;
    }
}
// Matched
// Matched
void sub_8002830C(EventEntry* p)
{
    short* s = (short*)&saveData_8008B570;
    s[0x2E6 / 2] = -1;
    s[0x2EA / 2] = -1;
    s[0x2EE / 2] = -1;
    s[0x2F2 / 2] = -1;
    unknownFlags_8008D678 &= ~0x20000;
    dword_80091CA0 = 1;
    sub_80027118();
    sub_8002728C();
    p->cb_8 = (EventEntryFn)sub_80027CC0;
}
// Matched
void sub_80028388(EventEntry* p, int* q)
{
    q[0] = 0;
    q[1] = 0;
    sub_800283C0(p, q);
    p->cb_8 = (EventEntryFn)sub_800283C0;
}
extern int sub_800A6D50(int a0);
extern int dword_800B1228;
extern void sub_80028C60();
// Matched
void sub_800283C0(void* a0, int* a)
{
    int* a1 = a;
    FileRequestDesc req;
    FileRequestDesc req2;
    FileRequestDesc req3;
    int s;
    int load;
    int wait;
    s = a1[0];
    switch (s)
    {
    case 0:
        if (sub_800A6D50(0) != 1 && dword_80082670 == 0)
        {
            break;
        }
        if (dword_800B1228 & 0x4000)
        {
            break;
        }
        if (word_80091C40[1] != word_80091C40[0])
        {
            req.flags_0 = 0xC69;
            req.fileId_4 = dword_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0][saveData_8008B570.mapId_2E4[2].field_0].f2;
            req.offset_8 = dword_80082674[word_80091C40[0] * 3];
            req.size_C = dword_80082674[word_80091C40[0] * 3 + (dword_80082670 ? 2 : 1)];
            req.dest_10 = 0;
            req.params_14 = 0;
            req.paramsSize_18 = 0;
            req.callback_1C = sub_80028C60;
            a1[1] = QueueFileRequest_8003BC84(&req);
            dword_80082678 = 1;
            word_80091C40[1] = word_80091C40[0];
            break;
        }
        if (saveData_8008B570.mapId_2E4[3].field_2 != saveData_8008B570.mapId_2E4[3].field_0)
        {
            load = 1;
            wait = 2;
            if (dword_80082670 == 0)
            {
                sub_8002728C();
            }
            if (dword_80082678)
            {
                if (word_80091C40[0] == saveData_8008B570.mapId_2E4[3].field_0)
                {
                    load = 0;
                }
                wait = ConsumeFileRequest_8003BFD0(a1[1], 1);
                dword_80082678 = 0;
            }
            if (load)
            {
                req2.flags_0 = 0x46C;
                req2.fileId_4 = dword_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0][saveData_8008B570.mapId_2E4[2].field_0].f2;
                req2.offset_8 = dword_80082674[saveData_8008B570.mapId_2E4[3].field_0 * 3];
                req2.size_C = dword_80082674[saveData_8008B570.mapId_2E4[3].field_0 * 3 + (dword_80082670 ? 2 : 1)];
                req2.dest_10 = 0;
                req2.params_14 = 0;
                req2.paramsSize_18 = 0;
                req2.callback_1C = sub_80028C60;
                a1[1] = QueueFileRequest_8003BC84(&req2);
            }
            word_80091CB8[7] = saveData_8008B570.mapId_2E4[3].field_0;
            word_80091CB8[6] = saveData_8008B570.mapId_2E4[3].field_0;
            saveData_8008B570.mapId_2E4[3].field_2 = saveData_8008B570.mapId_2E4[3].field_0;
            if (wait)
            {
                if (dword_80082670 == 0)
                {
                    sub_80027478(4, 1);
                }
                eventDispatchHalt_8008B540 = 1;
                a1[0] = 1;
            }
            break;
        }
        if (word_80091CB8[6] != word_80091CB8[7])
        {
            req3.flags_0 = 0x450;
            req3.fileId_4 = dword_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0][saveData_8008B570.mapId_2E4[2].field_0].f2;
            req3.offset_8 = dword_80082674[word_80091CB8[6] * 3];
            req3.size_C = 0;
            req3.dest_10 = 0;
            req3.params_14 = 0;
            req3.paramsSize_18 = 0;
            req3.callback_1C = 0;
            word_80091CB8[7] = word_80091CB8[6];
            a1[1] = QueueFileRequest_8003BC84(&req3);
            a1[0] = 2;
        }
        break;
    case 1:
        if (GetFileRequestStatus_8003BE30(a1[1]) == 0)
        {
            dword_80082670 = 0;
            dword_80082668 = 0;
            sub_80028DC0();
            sub_80027478(4, 0);
            a1[0] = 0;
        }
        else
        {
            eventDispatchHalt_8008B540 = 1;
        }
        break;
    case 2:
        if (GetFileRequestStatus_8003BE30(a1[1]) == 0)
        {
            a1[0] = 0;
        }
        break;
    }
}
typedef struct
{
    int x;
    int y;
    int z;
    short rx;
    short ry;
    short rz;
} PosRot;
typedef struct
{
    char pad_0[0xC];
    int fC;
} MapEntry16b;
typedef struct
{
    char pad_0[0x7A8];
    PosRot pos;
} SaveData7A8;
extern void sub_800A5628(int a0, int* a1, int a2);
extern void sub_800B73C0(int a0, int a1);
extern int sub_800B76B8(char* a0, PosRot* a1);
extern int* sub_80027A88();
extern unsigned int* dword_80073210;
extern short dword_80091CA8[];
extern EventNode* dword_8008B4A4; // the GAME overlay task
// Matched
void sub_80028808(void* a0, int* a1)
{
    char buf[0x104];
    int n;
    int* p;
    unsigned int cnt;
    unsigned int i;
    unsigned int j;
    int a;
    int c;
    int c2;
    p = a1;
    n = *p++;
    if (n != 0 && dword_80091C8C == 0)
    {
        MemCopy_800403E8(dword_80073210, (unsigned int*)p, n);
        dword_80091CB4 = ((MapEntry16b*)dword_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0])[saveData_8008B570.mapId_2E4[2].field_0].fC;
    }
    p = (int*)((char*)p + n);
    dword_80082668 = 1;
    dword_8008266C = n != 0;
    cnt = *p++;
    for (j = 0; j < cnt; j++)
    {
        a = *p++;
        c = *p++;
        c2 = *p++;
        sub_800A5628(a, p, c);
        p = (int*)((char*)p + c2);
    }
    dword_8008B500[0] = saveData_8008B570.mapId_2E4[2].field_0;
    dword_8008B500[1] = *p++;
    dword_8008B500[2] = *p++;
    MemCopy_800403E8((unsigned int*)buf, (unsigned int*)p, 0x104);
    p = sub_80027A88(&dword_8008B500[3], &dword_8008B500[1], &dword_80091C68, (char*)p + 0x104);
    sub_800B73C0(dword_8008B500[3], dword_8008B500[1]);
    p = sub_80027A88(&dword_8008B500[5], &dword_8008B500[4], &dword_80091C68, p);
    sub_800B73C0(dword_8008B500[5], dword_8008B500[4]);
    sub_800275E8((char**)&dword_8008B500[6], dword_8008B500[4], (int)&dword_80091C68);
    p = sub_80027A88(&dword_8008B500[10], &dword_8008B500[9], &dword_80091C68, p);
    sub_800B73C0(dword_8008B500[10], dword_8008B500[9]);
    p = sub_80027A88(&dword_8008B500[12], &dword_8008B500[11], &dword_80091C68, p);
    sub_800B73C0(dword_8008B500[12], dword_8008B500[11]);
    sub_800275E8((char**)&dword_8008B500[13], dword_8008B500[11], (int)&dword_80091C68);
    p = sub_80027A88(&dword_8008B500[8], &dword_8008B500[7], &dword_80091C68, p);
    sub_800B73C0(dword_8008B500[8], dword_8008B500[7]);
    cnt = p[0];
    sub_80027708(p, (int)&dword_80091C68);
    p = (int*)((char*)p + cnt);
    cnt = *p++;
    LoadTiy_80028E74(0, 0, 0, (int*)p, (int)&dword_80091C68);
    p = sub_80027650((int*)((char*)p + cnt), 0, (int)&dword_80091C68);
    dword_80082674 = (int*)ListAlloc_8003FDC0(&dword_80091C68, dword_8008B500[1] * 12);
    MemCopy_800403E8((unsigned int*)dword_80082674, (unsigned int*)p, dword_8008B500[1] * 12);
    if (dword_8008266C && dword_80091C5C && dword_80091C8C == 0 && dword_80091CB4)
    {
        ((void (*)(int))dword_80091CB4)(0);
    }
    if (dword_80091C98)
    {
        ((SaveData7A8*)&saveData_8008B570)->pos.x = stru_80091C78.pos[0];
        ((SaveData7A8*)&saveData_8008B570)->pos.y = stru_80091C78.pos[1];
        ((SaveData7A8*)&saveData_8008B570)->pos.z = stru_80091C78.pos[2];
        ((SaveData7A8*)&saveData_8008B570)->pos.rx = dword_80091CA8[0];
        ((SaveData7A8*)&saveData_8008B570)->pos.ry = dword_80091CA8[1];
        ((SaveData7A8*)&saveData_8008B570)->pos.rz = dword_80091CA8[2];
    }
    dword_80091C98 = 0;
    if (dword_80091C94)
    {
        ((SaveData7A8*)&saveData_8008B570)->pos.x = ((PosRot*)buf)->x;
        ((SaveData7A8*)&saveData_8008B570)->pos.y = ((PosRot*)buf)->y;
        ((SaveData7A8*)&saveData_8008B570)->pos.z = ((PosRot*)buf)->z;
        ((SaveData7A8*)&saveData_8008B570)->pos.rx = ((PosRot*)buf)->rx;
        ((SaveData7A8*)&saveData_8008B570)->pos.ry = ((PosRot*)buf)->ry;
        ((SaveData7A8*)&saveData_8008B570)->pos.rz = ((PosRot*)buf)->rz;
    }
    dword_80091C94 = 0;
    if (((int*)&stru_80091C78)[3] >= 0)
    {
        saveData_8008B570.mapId_2E4[3].field_0 = *(short*)&((int*)&stru_80091C78)[3];
        saveData_8008B570.mapId_2E4[3].field_2 = -1;
        ((int*)&stru_80091C78)[3] = -1;
    }
    else
    {
        for (i = 0; i < dword_8008B500[1]; i++)
        {
            if (sub_800B76B8((char*)dword_8008B500[3] + i * 8, &((SaveData7A8*)&saveData_8008B570)->pos) >= 0)
            {
                saveData_8008B570.mapId_2E4[3].field_0 = i;
                saveData_8008B570.mapId_2E4[3].field_2 = -1;
                break;
            }
        }
    }
    ((GameTaskState*)dword_8008B4A4->entry.buffer)->mapPoint_84 = saveData_8008B570.mapId_2E4[3].field_0;
}
