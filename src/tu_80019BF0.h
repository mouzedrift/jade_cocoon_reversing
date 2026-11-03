#ifndef _TU_80019BF0_H_
#define _TU_80019BF0_H_

#include "actor.h"

// per-species model description (dword_8007BD30, sub_80019C70)
typedef struct
{
    unsigned short modelId_0;
    unsigned char field_2; // angles in units of 2 degrees (sub_800C064C)
    unsigned char field_3;
} MinionModelDesc;
extern MinionModelDesc dword_8007BD30[];
extern MinionModelDesc* sub_80019C70(int idx);

// effect request built by sub_8001E28C and handed to sub_800182B8 / sub_800184DC
// (tu_80018430.c calls it EffectSet, tu_800174F8.c EntryList)
typedef struct
{
    int effect_0;
    short (*hitTimes_4)[2];   // Actor.hitTimes_108
    int field_8;              // Actor.f14C
    int* pos_C;
    char* bonePos_10;
    MATRIX* boneMatrices_14;
    char pad_18[0x1C];
    SVECTOR* boneScale_34;
    int* scale_38;
    char pad_3C[0xEC];        // count at 0x40, then 0x38-byte entries
} ActorEffectReq;

// sound cue table dword_8007C750 (ModelAnimCue.arg_4 indexes it)
typedef struct
{
    int kind; // 0: sfx, 1: music, 2: sequence, 3: fade out the system sequence
    short arg;
    short pad;
} SoundCue_8007C750;

// the block at 0x8008D4F0 (tu_80036528.c copies its first 0x68 bytes as Block104)
typedef struct
{
    char pad_0[0x30];
    unsigned char ambient_30[3];
    unsigned char pad_33;
    SVECTOR lightDir_34;
    short lightColor_3C[3];
    short pad_42;
    struct
    {
        VECTOR pos;
        int field_10;
        int active;
    } points_44[8];
} CameraState;

// screen fade task state (the dword_8008D628 task buffer, run by sub_8001A41C)
typedef struct Fade_8001A41C
{
    unsigned short flags; // 0x10: flash, 1: fade in, 2: fade out, 4: darken, 8: brighten, 0x20: front OT
    short count;
    short pad_4;
    unsigned short duration;
} Fade_8001A41C;

#endif
