#ifndef EFFECT_OBJ_H
#define EFFECT_OBJ_H

/* battle/spell effects: the effect task (effectTask_8008D3F8), the effect objects
   (buffers of effectObjects_8008B4A8 entries) and the effect file (effectFile_80091BD0).
   Used by tu_80014954.c, tu_80016BF4.c, tu_800174F8.c and tu_80018430.c. */

/* 28-byte entry of effectFile_80091BD0's model table */
typedef struct
{
    int field_0;
    int data_4; // struct_54 array (model data)
    int pad_8[5];
} EffectModel;

/* 52-byte entry of effectFile_80091BD0's sprite table */
typedef struct
{
    int field_0;
    int field_4;
    int field_8; // EffSprite** (tu_80014954.c)
    int field_C[10];
} EffectSpriteDef;

/* effectFile_80091BD0 (declared as int[4] in globals.h) */
typedef struct
{
    char pad_0[0x20];
    EffectSpriteDef* sprites_20;
    int field_24;
    EffectModel* models_28;
} EffectFile;
#define EFFECT_FILE ((EffectFile*)effectFile_80091BD0)

/* the buffer of the effect task (effectTask_8008D3F8->entry.buffer) */
typedef struct
{
    struct_4s pairs_0[10]; // sub_80018200
    unsigned int flags_28;
    int state_2C;
    int pad_30[3];
    int field_3C;
    short field_40;
    short field_42;
    unsigned char bits_44[12];
} EffectTaskState;
#define EFFECT_TASK ((EventNode*)effectTask_8008D3F8)
#define EFFECT_STATE ((EffectTaskState*)EFFECT_TASK->entry.buffer)

/* buffer of an effect object (an EventEntry of effectObjects_8008B4A8) */
typedef struct
{
    int field_0; // frame counter
    int field_4;
    short field_8;
    short field_A;
    short field_C;
    short field_E;
    int field_10;
    int field_14; // int* target position
    int field_18;
    int field_1C; // int* position
    int field_20; // int[][3] offsets, indexed by field_98
    SVECTOR field_24;
    int field_2C; // MATRIX[], indexed by field_98
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
    int field_94; // malloc'd model work buffer
    int field_98;
    int field_9C;
    int field_A0; // int* scale (or 0)
    char field_A4;
    signed char field_A5;
    short field_A6;
    unsigned char rgb_A8[4];
    int field_AC;
} EffectObj;

/* arguments of sub_800149A4 (spawn an effect object) */
typedef struct
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    short* scale_14;
    int field_18;
    short field_1C;
    short field_1E;
    int pad_20;
    int field_24;
    int field_28; // SVECTOR[], indexed by field_24
    int field_2C; // int* scale (or 0)
    int field_30;
} EffectArgs;

typedef struct
{
    short a;
    short b;
} ShortPair2;

typedef struct
{
    short (*tbl_0)[6];
    int field_4;
    int field_8;
    int field_C;
    char pad_10[0x1C];
    int field_2C;
    int field_30;
    int field_34;
} EffectTarget;

/* passed to sub_800184DC / sub_8001852C, filled by sub_800182B8 */
typedef struct
{
    int idx_0;
    ShortPair2* pairs_4;
    short (*tbl_8)[6];
    int field_C;
    int field_10;
    int field_14;
    char pad_18[0x1C];
    int field_34;
    int field_38;
    int pad_3C;
    int count_40;
    EffectTarget targets_44[11];
} EffectSet;

#endif
