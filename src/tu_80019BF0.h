#ifndef _TU_80019BF0_H_
#define _TU_80019BF0_H_

#include "actor.h"
#include "effect_obj.h"

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
