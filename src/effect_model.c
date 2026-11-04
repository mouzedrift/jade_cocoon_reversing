#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "camera.h"
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
#include "effect_model.h"

const int off_80072278[0] = {  };

void PulseModelTask_8001761C(int* flags, EffectObj* obj);
// Matched
void SpawnPulseModel_800174F8(EffectObj* parent, int modelId)
{
    EventEntry* entry = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    if (entry)
    {
        EffectObj* obj = entry->buffer;
        EffectModel* model;
        int idx;
        obj->pos_44[0] = parent->targetPos_1C[0];
        obj->pos_44[1] = parent->targetPos_1C[1];
        obj->pos_44[2] = parent->targetPos_1C[2];
        obj->frame_0 = 0;
        obj->field_30 = 0;
        obj->field_34 = 0x23F000;
        obj->rot_80.vz = 0;
        obj->rot_80.vy = 0;
        obj->rot_80.vx = 0;
        obj->rot_80.pad = 0;
        idx = FindEffectIndex_80020F00(&effectFile_80091BD0, 1, modelId);
        entry->flags = (entry->flags | 1) & ~0x8000;
        model = &effectFile_80091BD0.models_28[idx];
        obj->res_88 = (int)model;
        obj->work_94 = malloc3_8003FC4C(0x54);
        CopyFtgObject_800218A8(model->ftg_4, obj->work_94, 1);
        DiffFtgObjects_80039FE4(model->ftg_4, model->ftg_4 + 1, obj->work_94);
        entry->cb_8 = (EventEntryFn)PulseModelTask_8001761C;
    }
}
// Matched
void PulseModelTask_8001761C(int* flags, EffectObj* obj)
{
    EffectModel* model = (EffectModel*)obj->res_88;
    int scale[3];
    int fade;
    obj->field_34 = obj->field_34 * 7 / 8;
    obj->field_30 += obj->field_34;
    scale[0] = scale[1] = scale[2] = obj->field_30 / 4096;
    obj->rot_80.vy += 0x80;
    fade = (obj->frame_0 < 45) ? 0 : (((obj->frame_0 - 44) << 24) | 0x80);
    LerpFtgObject_8003A6C4(sinTable_80084540[(obj->frame_0 * 512) & 0xE00] / 2 + 0x800, model->ftg_4, model->ftg_4 + 1, obj->work_94);
    DrawFtgObjectAtSlot0_8004D1EC(model->ftg_4, pOT_8008D690, obj->pos_44, &obj->rot_80, pointLights_8008D534, fade | 0x31, scale);
    if (obj->frame_0++ > 60)
    {
        *flags = (*flags & ~1) | 0x8000;
        FreeFtgObjectData_80021804(obj->work_94, 1);
        free3_8003FC6C(obj->work_94);
    }
}
void MorphModelTask_800178C0(int* flags, EffectObj* obj);
// Matched
void SpawnMorphModel_80017784(EffectObj* parent, int modelId, short* rot)
{
    EventEntry* entry = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    if (entry)
    {
        EffectObj* obj = entry->buffer;
        EffectModel* model;
        int idx;
        obj->pos_44[0] = parent->targetPos_1C[0];
        obj->pos_44[1] = parent->targetPos_1C[1];
        obj->pos_44[2] = parent->targetPos_1C[2];
        obj->frame_0 = 0;
        obj->field_8 = 0;
        obj->field_30 = 0;
        obj->field_34 = 0x23F000;
        obj->rot_80.vx = rot[0];
        obj->rot_80.vy = rot[1];
        obj->rot_80.vz = rot[2];
        idx = FindEffectIndex_80020F00(&effectFile_80091BD0, 1, modelId);
        entry->flags = (entry->flags | 1) & ~0x8000;
        model = &effectFile_80091BD0.models_28[idx];
        obj->res_88 = (int)model;
        obj->work_94 = malloc3_8003FC4C(0x54);
        CopyFtgObject_800218A8(model->ftg_4, obj->work_94, 1);
        DiffFtgObjects_80039FE4(model->ftg_4, model->ftg_4 + 1, obj->work_94);
        entry->cb_8 = (EventEntryFn)MorphModelTask_800178C0;
    }
}
// Matched
void MorphModelTask_800178C0(int* flags, EffectObj* obj)
{
    EffectModel* model = (EffectModel*)obj->res_88;
    int scale[3];
    obj->field_34 = obj->field_34 * 7 / 8;
    obj->field_30 += obj->field_34;
    scale[0] = scale[1] = scale[2] = obj->field_30 / 4096;
    if (obj->field_8 < 3)
    {
        LerpFtgObject_8003A6C4(0x1000 - (obj->frame_0 << 10), model->ftg_4, &model->ftg_4[obj->field_8 + 1], obj->work_94);
        if (++obj->frame_0 >= 5)
        {
            obj->field_8++;
            obj->frame_0 = 0;
            if (obj->field_8 < 3)
            {
                DiffFtgObjects_80039FE4(&model->ftg_4[obj->field_8], &model->ftg_4[obj->field_8 + 1], obj->work_94);
            }
        }
    }
    else
    {
        if (++obj->frame_0 >= 0x35)
        {
            obj->frame_0 = 0;
            *flags = (*flags & ~1) | 0x8000;
            FreeFtgObjectData_80021804(obj->work_94, 1);
            free3_8003FC6C(obj->work_94);
        }
    }
    DrawFtgObjectAtSlot0_8004D1EC(model->ftg_4, pOT_8008D690, obj->pos_44, &obj->rot_80, pointLights_8008D534, 0x10, scale);
}
extern EventNode* effectObjects_8008B4A8;
extern void MdecEffectTask_80017B10(unsigned int* flags, EffectObj* obj);
// Matched
void SpawnMdecEffect_80017A6C(int parent, int frames)
{
    EventEntry* entry = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    EffectObj* obj;
    if (entry)
    {
        obj = entry->buffer;
        obj->field_8C = (int)mdecEffectSchedule_80091C00;
        obj->frame_0 = 0;
        if (frames > 0)
        {
            obj->field_4 = frames;
        }
        else
        {
            obj->field_4 = GetMdecEffectLength_800181E8();
        }
        entry->cb_8 = (EventEntryFn)MdecEffectTask_80017B10;
        entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
        AllocMdecVLCBufferInFileBuffer_8004188C();
        DecDCTReset(0);
    }
}
// Matched
void MdecEffectTask_80017B10(unsigned int* flags, EffectObj* obj)
{
    int* schedule = (int*)obj->field_8C;
    if (++obj->frame_0 < obj->field_4 && effectOutcomeFlag_8008D780[0] == 0)
    {
        if (!(unknownFlags_8008D678 & 0x800))
        {
            DecodeMdec_80041920(((unsigned long**)schedule[1])[obj->frame_0 % schedule[0]], mdecEffectVlcBuffer_8008D42C, 2);
            unknownFlags_8008D678 |= 0x800;
        }
    }
    else
    {
        ReleaseMdecVLCFileBuffer_800418FC();
        unknownFlags_8008D678 &= ~0x800;
        *flags = (*flags & ~1) | 0x8000;
    }
}
extern void WaveModelTask_80017CE4(EventEntry* entry, void* buf);
// Matched
void SpawnWaveModel_80017BF0(EventEntry* parent, int modelId)
{
    EventEntry* entry = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    EffectObj* obj;
    int idx;
    if (entry)
    {
        obj = entry->buffer;
        obj->pos_44[0] = ((int*)parent->buffer)[0];
        obj->pos_44[1] = ((int*)parent->buffer)[1];
        obj->pos_44[2] = ((int*)parent->buffer)[2];
        obj->frame_0 = 0;
        obj->field_30 = 0;
        obj->field_34 = 0x23F000;
        obj->rot_80.vz = 0;
        obj->rot_80.vy = 0;
        obj->rot_80.vx = 0;
        idx = FindEffectIndex_80020F00(&effectFile_80091BD0, 1, modelId);
        entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
        obj->res_88 = (int)&effectFile_80091BD0.models_28[idx];
        entry->cb_8 = WaveModelTask_80017CE4;
    }
}
// Matched
void WaveModelTask_80017CE4(EventEntry* entry, void* buf)
{
    int* flags = (int*)entry;
    EffectObj* obj = buf;
    EffectModel* model = (EffectModel*)obj->res_88;
    int i;
    int scale[3];
    int scaleY;
    if (obj->frame_0 < 0x80)
    {
        for (i = 0; i < 16; i++)
        {
            scale[0] = scale[2] = 0x1000 + i * 0x80;
            scaleY = sinTable_80084540[(obj->frame_0 * 16) & 0xFF0] * (sinTable_80084540[((i - obj->frame_0) * 256) & 0xF00] + 0x1000) / 4096;
            scale[1] = scaleY;
            DrawFtgObjectAtSlot0_8004D1EC(model->ftg_4, pOT_8008D690, obj->pos_44, &obj->rot_80, pointLights_8008D534, ((0x1000 - scaleY / 2) << 16) | 0xB0, scale);
        }
        obj->frame_0++;
    }
    else
    {
        *flags = (*flags & ~1) | 0x8000;
    }
}
void FadeOutModelTask_80017FF8(EventEntry* entry, void* buf);
// Matched
void MorphInModelTask_80017E30(EventEntry* entry, void* buf)
{
    EffectObj* obj = buf;
    EffectModel* model = (EffectModel*)obj->res_88;
    int pos[3];
    int scale[3];
    int* scalePtr;
    if ((obj->field_30 -= 0x80) <= 0)
    {
        obj->frame_0 = 0x1000;
        obj->field_30 = 0;
        entry->cb_8 = FadeOutModelTask_80017FF8;
    }
    LerpFtgObject_8003A6C4(0x1000 - obj->field_30, model->ftg_4, model->ftg_4 + 1, obj->work_94);
    if (obj->scale_A0)
    {
        scalePtr = scale;
        scale[0] = obj->scale_A0[0] * 3 / 2;
        scale[1] = obj->scale_A0[1] * 3 / 2;
        scale[2] = obj->scale_A0[2] * 3 / 2;
    }
    else
    {
        scalePtr = 0;
    }
    pos[0] = obj->targetBonePos_20[obj->bone_98 * 3 + 0] + obj->targetPos_1C[0];
    pos[1] = obj->targetBonePos_20[obj->bone_98 * 3 + 1] + obj->targetPos_1C[1];
    pos[2] = obj->targetBonePos_20[obj->bone_98 * 3 + 2] + obj->targetPos_1C[2];
    DrawFtgObjectAtSlot0_8004D1EC(model->ftg_4, pOT_8008D690, pos, &zeroSvector_800795D4, pointLights_8008D534, (obj->field_30 << 16) | 0xB0, scalePtr);
}
// Matched
void FadeOutModelTask_80017FF8(EventEntry* entry, void* buf)
{
    EffectObj* obj = buf;
    EffectModel* model = (EffectModel*)obj->res_88;
    int pos[3];
    int scale[3];
    int* scalePtr;
    if ((obj->frame_0 -= 0x80) > 0)
    {
        LerpFtgObject_8003A6C4(0x1000 - obj->field_30, model->ftg_4, model->ftg_4 + 1, obj->work_94);
        if (obj->scale_A0)
        {
            scalePtr = scale;
            scale[0] = obj->scale_A0[0] * 3 / 2;
            scale[1] = obj->scale_A0[1] * 3 / 2;
            scale[2] = obj->scale_A0[2] * 3 / 2;
        }
        else
        {
            scalePtr = 0;
        }
        pos[0] = obj->targetBonePos_20[obj->bone_98 * 3 + 0] + obj->targetPos_1C[0];
        pos[1] = obj->targetBonePos_20[obj->bone_98 * 3 + 1] + obj->targetPos_1C[1];
        pos[2] = obj->targetBonePos_20[obj->bone_98 * 3 + 2] + obj->targetPos_1C[2];
        DrawFtgObjectAtSlot0_8004D1EC(model->ftg_4, pOT_8008D690, pos, &zeroSvector_800795D4, pointLights_8008D534, (obj->field_30 << 16) | 0xB0, scalePtr);
    }
    else
    {
        entry->flags = (entry->flags & ~1) | 0x8000;
        FreeFtgObjectData_80021804(obj->work_94, 1);
        free3_8003FC6C(obj->work_94);
    }
}
// Matched
int GetMdecEffectLength_800181E8(void)
{
    return *mdecEffectSchedule_80091C00;
}
// Matched
HitTimes* RepeatHitTimes_80018200(HitTimes* src, unsigned short loopStart, unsigned short loopEnd, short loops, int effect)
{
    HitTimes* dst = ((EffectTaskState*)effectTask_8008D3F8->entry.buffer)->hitTimes_0;
    int i;
    int j;
    short len;
    for (i = 0; i < 10; i++)
    {
        dst[i].start_0 = src[i].start_0;
        dst[i].end_2 = src[i].end_2;
    }
    len = loopEnd - loopStart;
    for (i = 0; i < loops; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (dst[j].start_0 >= loopEnd)
            {
                dst[j].start_0 += len;
            }
            if (dst[j].end_2 >= loopEnd)
            {
                dst[j].end_2 += len;
            }
        }
    }
    return dst;
}
extern int GetSummonedMinionSlot_800C0D50(void);
extern void GetSummonedMinionEffectTarget_800C0FC4(EffectTarget* out);
extern void GetLevantEffectTarget_800A93A4(EffectTarget* out);
extern void GetEnemyEffectTarget_800A29CC(int idx, EffectTarget* out);
extern void GetSlotEffectTarget_800A111C(int slot, EffectTarget* out);
// Matched
void CollectEffectTargets_800182B8(ActorEffectReq* req, int mask)
{
    EffectTaskState* state = effectTask_8008D3F8->entry.buffer;
    int i;
    int bit;
    req->count_40 = 0;
    for (i = 0; i < 11; i++)
    {
        bit = 1 << i;
        if (mask & bit)
        {
            switch (i)
            {
            case 1:
            case 2:
            case 3:
                if (GetSummonedMinionSlot_800C0D50() >= 0)
                {
                    GetSummonedMinionEffectTarget_800C0FC4(&req->targets_44[req->count_40]);
                    break;
                }
            case 0:
                GetLevantEffectTarget_800A93A4(&req->targets_44[req->count_40]);
                break;
            case 4:
            case 5:
            case 6:
                GetEnemyEffectTarget_800A29CC(i - 4, &req->targets_44[req->count_40]);
                break;
            case 8:
            case 9:
                GetSlotEffectTarget_800A111C(i - 8, &req->targets_44[req->count_40]);
                break;
            }
            req->targets_44[req->count_40].hitFlags_34 = state->hitFlags_44[i];
            req->count_40++;
        }
    }
}
