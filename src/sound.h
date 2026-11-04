#ifndef _SOUND_H
#define _SOUND_H

typedef struct SoundStruct
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
  short field_0_file_id;
  short field_2_seq; // sequence played from the file (-1 = none)
  unsigned char field_4_seq_count;
  unsigned char field_5_seq_count;
  short field_6_sub_sound;
} SoundInfo;

extern int GetSoundFileId_80030D4C(int idx);
extern void InitSound_8002FE54(SoundStruct* arg1);
extern void PlaySfx_80031494(int id);
extern void LoadSound_80030A84(short soundId, SoundStruct* sound);

extern SoundStruct bgmSound_80091CE0;
extern SoundStruct sfxSound_80091D20;
extern SoundStruct seqSlotSound_80091D00;
extern SoundStruct systemSound_80091D40;

void FreeSoundTask_8003006C();
void InitSoundTask_8002FF10();

#endif