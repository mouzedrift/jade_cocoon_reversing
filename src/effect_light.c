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
#include "effect_light.h"
#include "model.h"
#include "cd.h"
#include "sound_seq.h"

const ColorRGBA orangeGlowColor_80072270 = { { 255, 128, 0, 0 } };
const int dword_80072274 = 0;

// Matched
void CountdownTask_80016BF4(EventEntry* entry, EffectObj* obj)
{
    if (--obj->field_4 < 0)
    {
        entry->flags = (entry->flags & ~1) | 0x8000;
        PlaySfx_80031494(0x24);
    }
}
extern void PlayMusic_800300E0(int idx, int a1);
// Matched
void BoneModelFadeTask_80016C3C(int* flags, void* buf)
{
    EffectObj* obj = buf;
    int idx;
    EffectModel* model;
    int pos[3];
    int scale[3];
    int* scalePtr;
    idx = FindEffectIndex_80020F00(&effectFile_80091BD0, 1, 6);
    model = &effectFile_80091BD0.models_28[idx];
    if (--obj->field_4 > 0)
    {
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
        DrawFtgObjectAtSlot0_8004D1EC(model->ftg_4, pOT_8008D690, pos, &zeroSvector_800795D4, pointLights_8008D534, (obj->field_4 << 24) | 0xB0, scalePtr);
    }
    else
    {
        *flags = (*flags & ~1) | 0x8000;
    }
}
extern void SpawnSpriteAnim_800C1A5C(void* pos, short* rot, int sprite, int speed);
void SpawnMdecEffect_80017A6C(int parent, int frames);
// Matched
void RadialBurstTask_80016E20(int* flags, void* buf)
{
    EffectObj* obj = buf;
    short rot[3];
    int i;
    short angle;
    short angle2;
    int idx;
    angle = ratan2Difference_8003B9E0(obj->targetPos_1C, obj->srcPos_14);
    rot[0] = 0;
    rot[1] = angle;
    rot[2] = 0;
    if (obj->field_4 == 1)
    {
        PlayMusic_800300E0(6, 1);
        PlaySfx_80031494(0x18);
        PlaySfx_80031494(0x4A);
        for (i = 0; i < 5; i++)
        {
            rot[1] = angle + (i << 12) / 5;
            idx = FindEffectIndex_80020F00(&effectFile_80091BD0, 0, 0x176);
            SpawnSpriteAnim_800C1A5C(obj->pos_44, rot, (int)&effectFile_80091BD0.sprites_20[idx], 0x1000);
            SpawnModelAnim_800C32DC(obj->pos_44, 0xB2, 0, rot[1]);
        }
    }
    if (obj->field_4 == 0x5D)
    {
        angle2 = ratan2Difference_8003B9E0(obj->targetPos_1C, obj->srcPos_14);
        StopSoundSeqById_800306FC(6);
        PlaySfx_80031494(0x1A);
        SpawnMdecEffect_80017A6C((int)obj, SpawnModelAnim_800C32DC(obj->pos_44, 0xB3, 0, angle2));
        *flags = (*flags & ~1) | 0x8000;
    }
    obj->field_4++;
}
extern void PlayTimedSfx_800C1190(int frames, int sfx);
// Matched
void QuadBurstTask_80016FC8(int* flags, EffectObj* obj)
{
    short rot[3];
    int i;
    int idx;
    idx = ratan2Difference_8003B9E0(obj->targetPos_1C, obj->srcPos_14);
    rot[0] = 0;
    rot[1] = idx;
    rot[2] = 0;
    if (obj->field_4 == 0)
    {
        PlayTimedSfx_800C1190(0x32, 0x1E);
        PlayTimedSfx_800C1190(0x50, 0x1D);
        for (i = 0; i < 4; i++)
        {
            idx = FindEffectIndex_80020F00(&effectFile_80091BD0, 0, 0x16);
            SpawnSpriteAnim_800C1A5C(obj->pos_44, rot, (int)&effectFile_80091BD0.sprites_20[idx], 0x1000);
            rot[1] += 0x400;
            SpawnModelAnim_800C32DC(obj->targetPos_1C, 0xF, 0, rot[1]);
        }
    }
    if (obj->field_4 == 0x30)
    {
        idx = FindEffectIndex_80020F00(&effectFile_80091BD0, 0, 0x15);
        SpawnSpriteAnim_800C1A5C(obj->pos_44, rot, (int)&effectFile_80091BD0.sprites_20[idx], 0x1000);
    }
    if (obj->field_4 == 0x33)
    {
        SpawnModelAnim_800C32DC(obj->targetPos_1C, 0xE, 0, rot[1]);
        *flags = (*flags & ~1) | 0x8000;
    }
    obj->field_4++;
}
extern EventNode* effectObjects_8008B4A8;
extern void LightFlashTask_80017208(int* flags, EffectObj* obj);
// Matched
void SpawnLightFlash_80017158(int* pos, unsigned char* rgb)
{
    EventEntry* entry = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    EffectObj* obj;
    if (entry)
    {
        entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
        obj = entry->buffer;
        obj->pos_44[0] = pos[0];
        obj->pos_44[1] = pos[1];
        obj->pos_44[2] = pos[2];
        obj->frame_0 = 0;
        obj->rgb_A8[0] = rgb[0];
        obj->rgb_A8[1] = rgb[1];
        obj->rgb_A8[2] = rgb[2];
        entry->cb_8 = (EventEntryFn)LightFlashTask_80017208;
    }
}
// Matched
void LightFlashTask_80017208(int* flags, EffectObj* obj)
{
    if (obj->frame_0 < 0x20)
    {
        SetPointLight_800C4090((int)obj->pos_44, (int)obj->rgb_A8, 0x5DC, (0x20 - obj->frame_0) << 7);
        obj->frame_0 = obj->frame_0 + 1;
    }
    else
    {
        ClearPointLight_800C410C();
        flags[0] = (flags[0] & ~1) | 0x8000;
    }
}
void GlowModelTask_800173A8(int* flags, void* buf);
// Matched
void SpawnGlowModel_80017290(EffectObj* parent, int modelId)
{
    EventEntry* entry;
    SpawnMdecEffect_80017A6C((int)parent, 0);
    entry = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    if (entry)
    {
        EffectObj* obj = entry->buffer;
        int idx;
        obj->pos_44[0] = parent->targetPos_1C[0];
        obj->pos_44[1] = parent->targetPos_1C[1];
        obj->pos_44[2] = parent->targetPos_1C[2];
        obj->frame_0 = 0;
        obj->field_4 = GetMdecEffectLength_800181E8();
        obj->field_30 = 0;
        obj->field_34 = 0x23F000;
        obj->rot_80.vz = 0;
        obj->rot_80.vy = 0;
        obj->rot_80.vx = 0;
        obj->rot_80.pad = 0;
        idx = FindEffectIndex_80020F00(&effectFile_80091BD0, 1, modelId);
        entry->flags = (entry->flags | 1) & ~0x8000;
        obj->res_88 = (int)&effectFile_80091BD0.models_28[idx];
        entry->cb_8 = (EventEntryFn)GlowModelTask_800173A8;
    }
}
// Matched
void GlowModelTask_800173A8(int* flags, void* buf)
{
    EffectObj* obj = buf;
    EffectModel* model = (EffectModel*)obj->res_88;
    ColorRGBA color;
    int scale[3];
    if (obj->frame_0 < obj->field_4)
    {
        color = orangeGlowColor_80072270;
        obj->field_34 = obj->field_34 * 7 / 8;
        obj->field_30 += obj->field_34;
        scale[0] = scale[1] = scale[2] = obj->field_30 / 4096;
        obj->rot_80.vy += obj->rot_80.pad;
        DrawFtgObjectAtSlot0_8004D1EC(model->ftg_4, pOT_8008D690, obj->pos_44, &obj->rot_80, pointLights_8008D534, 0x30, scale);
        SetPointLight_800C4090((int)obj->pos_44, (int)&color, 0x5DC, ((obj->field_4 - obj->frame_0) << 12) / obj->field_4);
        obj->frame_0++;
    }
    else
    {
        ClearPointLight_800C410C();
        *flags = (*flags & ~1) | 0x8000;
    }
}
