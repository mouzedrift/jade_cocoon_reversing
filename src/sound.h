#ifndef _SOUND_H
#define _SOUND_H

typedef struct
{
    int field_0_vab_id;
    short field_4_seq_num;
    short field_6_sound_idx;
    unsigned long* field_8_sep_data_ptr;
    int field_C_sep_access_num;
    unsigned long* field_10_sep_data_ptr;
    int field_14_sep_access_num;
    unsigned char* field_18_vab_header_ptr;
} SoundStruct;

typedef struct
{
    int field_0_header_start;
    unsigned int field_4_vab_header_size;
    int field_8;
    int field_C;
    int field_10;
    unsigned int field_14_sep_size;
    int field_18_sep_data2_ptr;
    unsigned int field_1C_sep_size;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
} GenkiSoundHeader;

typedef struct
{
  short field_0;
  unsigned char field_2;
  unsigned char field_3;
  unsigned char field_4_seq_count;
  unsigned char field_5_seq_count;
  short field_6;
} SoundInfo;

extern int GetSoundFileId_80030D4C(int idx);
extern void InitSound_8002FE54(SoundStruct* arg1);
extern void PlaySfx_80031494(int a1);
extern void sub_80030A84(short soundId, SoundStruct* sound);

extern SoundStruct stru_80091CE0;
extern SoundStruct stru_80091D20;
extern SoundStruct stru_80091D00;
extern SoundStruct stru_80091D40;

#endif