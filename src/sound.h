#ifndef _SOUND_H
#define _SOUND_H

typedef struct SoundStruct
{
    int vabId_0;
    short seqNum_4;
    short soundIdx_6;
    unsigned long* sepDataPtr_8;
    int sepAccessNum_C;
    unsigned long* sepDataPtr_10;
    int sepAccessNum_14;
    unsigned char* vabHeaderPtr_18;
} SoundStruct;

#include "soundtask.h"

typedef struct
{
    int headerStart_0;
    unsigned int vabHeaderSize_4;
    int vabBodyStart_8;
    int field_C;
    int sepDataStart_10;
    unsigned int sepSize_14;
    int sepData2Ptr_18;
    unsigned int sepSize_1C;
    int pad_20;
    int field_24;
    int pad_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
} GenkiSoundHeader;

typedef struct
{
  short field_0_file_id;
  short field_2_seq; // sequence played from the file (-1 = none)
  unsigned char seqCount_4;
  unsigned char seqCount_5;
  short subSound_6;
} SoundInfo;

extern int GetSoundFileId_80030D4C(int idx);
extern void InitSound_8002FE54(SoundStruct* sound);
extern void LoadSound_80030A84(short soundId, SoundStruct* sound);

extern SoundStruct bgmSound_80091CE0;
extern SoundStruct sfxSound_80091D20;
extern SoundStruct seqSlotSound_80091D00;
extern SoundStruct systemSound_80091D40;

void FreeSoundTask_8003006C(EventEntry* entry, SoundTask* buffer);
void InitSoundTask_8002FF10(EventEntry* entry, SoundTask* task);

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