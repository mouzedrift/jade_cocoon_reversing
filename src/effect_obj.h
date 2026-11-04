#ifndef EFFECT_OBJ_H
#define EFFECT_OBJ_H

#include "model.h"

/* battle/spell effects: the effect task (effectTask_8008D3F8), the effect objects
   (buffers of effectObjects_8008B4A8 entries) and the effect file (effectFile_80091BD0).
   Used by effect_data.c, effect_light.c, effect_model.c and effect_cmd.c. */


/* the buffer of the effect task (effectTask_8008D3F8->entry.buffer) */
typedef struct
{
    struct_4s hitTimes_0[10]; // RepeatHitTimes_80018200's output
    unsigned int flags_28; // 1: start, 2: file freed, 4: load requested, 8: sub_80018460
    int state_2C;          // UpdateEffectTask_80014638: 0 idle, 1 loading, 2 loaded, 3 running
    int pad_30[2];
    int idx_38;            // effect file index (RequestEffect_800148F4)
    int timer_3C;
    short hitVariant_40;      // SetHitVariant_80018430; copied to EffectObj.hitVariant_A5
    short field_42;
    unsigned char hitFlags_44[12]; // per target slot (SetTargetHitFlag_800184A0); EffectTarget.hitFlags_34
} EffectTaskState;

/* buffer of an effect object (an EventEntry of effectObjects_8008B4A8) */
typedef struct EffectObj
{
    int field_0; // frame counter
    int field_4;
    short field_8;
    short hitEnd_A;   // last frame (the object ends once field_0 reaches it)
    short hitStart_C; // first frame the kind's effect runs
    short kind_E;     // EffectObjectTask_80015478's switch
    int field_10;
    int* srcPos_14;                // source actor position
    int* srcBonePos_18;            // source actor bone positions
    int* targetPos_1C;             // target actor position
    int* targetBonePos_20;         // int[][3] target bone offsets, indexed by bone_98
    SVECTOR offset_24;             // offset from the bone (through targetBoneMatrices_2C)
    MATRIX* targetBoneMatrices_2C; // indexed by bone_98
    int field_30;
    int field_34;
    int pad_38[3];
    int pos_44[3];
    int pos_50[3];
    int pad_5C[9];
    SVECTOR rot_80;
    int field_88; // EffectModel*
    int field_8C;
    int field_90;
    FtgObject* work_94; // malloc'd copy of the model's first FtgObject
    int bone_98;
    SVECTOR* boneScales_9C;
    int* scale_A0; // scale (or 0)
    char field_A4;
    signed char hitVariant_A5; // EffectTaskState.hitVariant_40 (sprite choice for some kinds)
    short field_A6;
    unsigned char rgb_A8[4];
    int hitFlags_AC; // EffectTarget.hitFlags_34
} EffectObj;

/* arguments of SpawnEffectObject_800149A4 (spawn an effect object), filled by SpawnActorEffects_8001852C from an ActorEffectReq */
typedef struct
{
    int kind_0;
    int* srcPos_4;
    int* srcBonePos_8;
    int* targetPos_C;
    int* targetBonePos_10;
    short* offset_14;               // effect table row + 2 (x, y, z)
    MATRIX* targetBoneMatrices_18;
    short hitStart_1C;
    short hitEnd_1E;
    int pad_20;
    int bone_24;
    SVECTOR* boneScales_28; // indexed by bone_24
    int* scale_2C;                  // scale (or 0)
    int hitFlags_30;
} EffectArgs;

/* what an effect needs to know about an actor (ActorEffectReq.targets_44; filled by GetSummonedMinionEffectTarget_800C0FC4 (BATTLE),
   GetLevantEffectTarget_800A93A4 / GetEnemyEffectTarget_800A29CC (GAME) and GetSlotEffectTarget_800A111C (COMBAT)) */
typedef struct EffectTarget
{
    short (*tbl_0)[6];       // Actor.effectTbl_14C
    int* pos_4;              // Actor.pos_38
    int* bonePos_8;          // Actor.bonePos_1C4
    MATRIX* boneMatrices_C;  // Actor.boneMatrices_1C8
    char pad_10[0x1C];
    SVECTOR* boneScale_2C;   // Actor.boneScale_144
    int* scale_30;           // Actor.scale_2C
    int hitFlags_34; // EffectTaskState.hitFlags_44[slot]
} EffectTarget;

/* effect request: built by TriggerActorEffect_8001E28C (engine.c) from an actor, filled by CollectEffectTargets_800182B8,
   played by PlayActorEffect_800184DC / SpawnActorEffects_8001852C */
typedef struct ActorEffectReq
{
    int effect_0;            // effect index (effectFileTable_800795F0)
    struct_4s* hitTimes_4;   // Actor.hitTimes_108
    short (*tbl_8)[6];       // Actor.effectTbl_14C
    int* pos_C;              // Actor.pos_38
    int* bonePos_10;         // Actor.bonePos_1C4
    MATRIX* boneMatrices_14; // Actor.boneMatrices_1C8
    char pad_18[0x1C];
    SVECTOR* boneScale_34;   // Actor.boneScale_144
    int* scale_38;           // Actor.scale_2C
    int pad_3C;
    int count_40;
    EffectTarget targets_44[4]; // filled from the 11 effect-task slots; TriggerActorEffect_8001E28C's local is 0x128 bytes
    int pad_124;
} ActorEffectReq;

#endif
