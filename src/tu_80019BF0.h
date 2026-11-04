#ifndef _TU_80019BF0_H_
#define _TU_80019BF0_H_

#include "actor.h"
#include "effect_obj.h"
#include "unit.h"

// each species' starting skills: 0xC9 in the exe, the rest from the overlay (sub_800B3274)
extern UnitSkills dword_8007A9F8[];
extern UnitSkills* sub_800B3274(int a0);
extern UnitSkills* sub_80019C28(unsigned int idx);

// per-species model description (dword_8007BD30, sub_80019C70)
typedef struct
{
    unsigned short modelId_0;
    unsigned char field_2; // angles in units of 2 degrees (sub_800C064C)
    unsigned char field_3;
} MinionModelDesc;
extern MinionModelDesc dword_8007BD30[];
extern MinionModelDesc* sub_80019C70(int idx);



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

// a point light passed to SetModelLighting_80019D84
typedef struct
{
    int pos_0[3];
    SVECTOR color_C;   // only vx/vy/vz used
    int range_14;
} PointLight;
extern void SetModelLighting_80019D84(VECTOR* pos, VECTOR* ofs, PointLight* light, MATRIX* m);

// screen fade task state (the dword_8008D628 task buffer, run by sub_8001A41C)
typedef struct Fade_8001A41C
{
    unsigned short flags; // 0x10: flash, 1: fade in, 2: fade out, 4: darken, 8: brighten, 0x20: front OT
    short count;
    short pad_4;
    unsigned short duration;
} Fade_8001A41C;

#endif
