#ifndef _TU_80019BF0_H_
#define _TU_80019BF0_H_

#include "actor.h"

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

#endif
