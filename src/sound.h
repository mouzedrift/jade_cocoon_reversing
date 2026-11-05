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

#include "soundtask.h"

typedef struct
{
    int field_0_header_start;
    unsigned int field_4_vab_header_size;
    int field_8_vab_body_start;
    int field_C;
    int field_10_sep_data_start;
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
extern void InitSound_8002FE54(SoundStruct* sound);
extern void LoadSound_80030A84(short soundId, SoundStruct* sound);

extern SoundStruct bgmSound_80091CE0;
extern SoundStruct sfxSound_80091D20;
extern SoundStruct seqSlotSound_80091D00;
extern SoundStruct systemSound_80091D40;

void FreeSoundTask_8003006C();
void InitSoundTask_8002FF10();

int PlayMusic_800300E0(int idx, int unused);
void InitSounds_8002FE7C(void);
void FreeBgmSeqs_800306D8(void);
int IsSoundTaskReady_800306B0(void);
void StopSoundSeqById_800306FC(int idx);
int LoadSeqSlotSound_800303E8(void);
int IsSoundTaskReady_80030688(void);
void FreeSeqSlotSound_80030664(void);
void ApplyBgmVolume_800309D8(SoundStruct* sound);
void ResetSoundTask_8002FEB8(void);
void ApplyAudioOutputFormat_80030988(void);
void DrawLevantHeaderWindows_8002FD0C(int ot, short step, short highlight, short animate, RECT* clipRect);
void UpdateSoundTask_8002FF64(int entry, SoundTask* task);
void LoadSoundFromBuffer_800307B4(SoundStruct** req, GenkiSoundHeader* pSndFileHeader);
void LoadSoundSeqFromBuffer_800304D0(SoundStruct** req, char* pSndFileBuffer);
#endif