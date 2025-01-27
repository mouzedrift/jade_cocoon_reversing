#ifndef _SOUND_H
#define _SOUND_H

typedef struct
{
    int field_0;
    short field_4_seq_num;
    short field_6_sound_idx;
    int field_8;
    int field_C_sep_access_num;
    int field_10_ptr;
    int field_14_sep_access_num;
    int field_18_ptr;
} SoundStruct;

extern void InitSound_8002FE54(SoundStruct* arg1);

extern SoundStruct stru_80091CE0;
extern SoundStruct stru_80091D20;
extern SoundStruct stru_80091D00;

#endif