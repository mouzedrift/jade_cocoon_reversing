#ifndef EFFECT_OBJ_H
#define EFFECT_OBJ_H

#include "tu_8001EA48.h"

/* battle/spell effects: the effect task (effectTask_8008D3F8), the effect objects
   (buffers of effectObjects_8008B4A8 entries) and the effect file (effectFile_80091BD0).
   Used by tu_80014954.c, tu_80016BF4.c, tu_800174F8.c and tu_80018430.c. */


/* the buffer of the effect task (effectTask_8008D3F8->entry.buffer) */
typedef struct
{
    struct_4s pairs_0[10]; // sub_80018200
    unsigned int flags_28; // 1: start, 2: file freed, 4: load requested, 8: sub_80018460
    int state_2C;          // UpdateEffectTask_80014638: 0 idle, 1 loading, 2 loaded, 3 running
    int pad_30[2];
    int idx_38;            // effect file index (RequestEffect_800148F4)
    int timer_3C;
    short field_40;
    short field_42;
    unsigned char bits_44[12];
} EffectTaskState;

/* buffer of an effect object (an EventEntry of effectObjects_8008B4A8) */
typedef struct EffectObj
{
    int field_0; // frame counter
    int field_4;
    short field_8;
    short field_A;
    short field_C;
    short field_E;
    int field_10;
    int* field_14; // target position
    int* field_18; // target bone positions
    int* field_1C; // position
    int* field_20; // int[][3] bone offsets, indexed by field_98
    SVECTOR field_24;
    MATRIX* field_2C; // bone matrices, indexed by field_98
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
    int field_98;
    SVECTOR* field_9C; // bone scales
    int* field_A0;     // scale (or 0)
    char field_A4;
    signed char field_A5;
    short field_A6;
    unsigned char rgb_A8[4];
    int field_AC;
} EffectObj;

/* arguments of sub_800149A4 (spawn an effect object), filled by sub_8001852C from an ActorEffectReq */
typedef struct
{
    int field_0;
    int* field_4;     // source position
    int* field_8;     // source bone positions
    int* field_C;     // target position
    int* field_10;    // target bone positions
    short* scale_14;
    MATRIX* field_18; // target bone matrices
    short field_1C;
    short field_1E;
    int pad_20;
    int field_24;
    SVECTOR* field_28; // bone scales, indexed by field_24
    int* field_2C;     // scale (or 0)
    int field_30;
} EffectArgs;

/* what an effect needs to know about an actor (ActorEffectReq.targets_44; filled by sub_800C0FC4 (BATTLE),
   sub_800A93A4 / sub_800A29CC (GAME) and sub_800A111C (COMBAT)) */
typedef struct EffectTarget
{
    short (*tbl_0)[6];       // Actor.effectTbl_14C
    int* pos_4;              // Actor.pos_38
    int* bonePos_8;          // Actor.bonePos_1C4
    MATRIX* boneMatrices_C;  // Actor.boneMatrices_1C8
    char pad_10[0x1C];
    SVECTOR* boneScale_2C;   // Actor.boneScale_144
    int* scale_30;           // Actor.scale_2C
    int field_34;
} EffectTarget;

/* effect request: built by sub_8001E28C (tu_80019BF0.c) from an actor, filled by sub_800182B8,
   played by sub_800184DC / sub_8001852C */
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
    EffectTarget targets_44[4]; // filled from the 11 effect-task slots; sub_8001E28C's local is 0x128 bytes
    int pad_124;
} ActorEffectReq;

#endif
