#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "STDLIB.H"
#include "STDIO.H"
#include "LIBPAD.H"
#include "LIBSND.H"
#include "LIBMCX.H"
#include "LIBPRESS.H"
#include "LIBETC.H"
#include "LIBMCRD.H"
#include "sound.h"
#include "soundtask.h"
#include "data_decls.h"

const char aAssertionFaile_0[] = "Assertion failed: file \"%s\", line %d\n";
const char aSoundC[] = "SOUND.C";

typedef struct
{
    void* rect_0;
    int time_4;
    short colorSet_8;
    short ot_A;
} UiWindowDesc;
extern void InterpolateWindowRect_8004196C(void* a0, RECT* a1, int a2, int a3, int a4);
extern void DrawPortrait_8002A42C(unsigned short* pos, short a1, int a2, short a3);
extern void DrawUiWindow_8002A384(UiWindowDesc* p);
// Matched
void DrawLevantHeaderWindows_8002FD0C(int ot, short step, short highlight, short animate, int clipRect)
{
    char buf[8];
    RECT rect;
    unsigned short loc[2];
    UiWindowDesc desc1;
    UiWindowDesc desc2;
    int time;
    if (animate)
    {
        time = frameCount_8008D3FC;
    }
    else
    {
        time = 0;
    }
    rect.x = 10;
    rect.y = 0x2C;
    rect.w = 0x44;
    rect.h = 0x44;
    InterpolateWindowRect_8004196C(buf, &rect, step, 8, 0);
    loc[0] = 12;
    loc[1] = 0x2E;
    DrawPortrait_8002A42C(loc, 0, clipRect, ot);
    desc1.colorSet_8 = highlight;
    desc1.rect_0 = buf;
    desc1.time_4 = time;
    desc1.ot_A = ot;
    DrawUiWindow_8002A384(&desc1);
    rect.x = 0x4E;
    rect.y = 0x2C;
    rect.w = 0x8D;
    rect.h = 0x44;
    InterpolateWindowRect_8004196C(buf, &rect, step, 8, 0);
    desc2.colorSet_8 = highlight;
    desc2.rect_0 = buf;
    desc2.time_4 = time;
    desc2.ot_A = ot;
    DrawUiWindow_8002A384(&desc2);
}
// Matched
void InitSound_8002FE54(SoundStruct* sound)
{
    sound->field_0_vab_id = -1;
    sound->field_4_seq_num = -1;
    sound->field_6_sound_idx = -1;
    sound->field_C_sep_access_num = -1;
    sound->field_14_sep_access_num = -1;
    sound->field_8_sep_data_ptr = 0;
    sound->field_10_sep_data_ptr = 0;
    sound->field_18_vab_header_ptr = 0;
}
// Matched
void InitSounds_8002FE7C(void)
{
    InitSound_8002FE54(&bgmSound_80091CE0);
    InitSound_8002FE54(&sfxSound_80091D20);
    InitSound_8002FE54(&seqSlotSound_80091D00);
}
// Matched
void ResetSoundTask_8002FEB8(void)
{
    SoundTask* task = soundTask_8008D4A4->entry.buffer;
    int i;
    task->bgm_4 = &bgmSound_80091CE0;
    task->sfx_8 = &sfxSound_80091D20;
    task->seqSlot_C = &seqSlotSound_80091D00;
    task->state_2 = 2;
    for (i = 4; i >= 0; i--)
    {
        task->fades_18[i].active = 0;
    }
}
extern void UpdateSoundTask_8002FF64();
// Matched
void InitSoundTask_8002FF10(EventEntry* entry, SoundTask* task)
{
    int i;
    task->bgm_4 = &bgmSound_80091CE0;
    task->sfx_8 = &sfxSound_80091D20;
    task->seqSlot_C = &seqSlotSound_80091D00;
    task->state_2 = 2;
    for (i = 4; i >= 0; i--)
    {
        task->fades_18[i].active = 0;
    }
    entry->cb_8 = (EventEntryFn)UpdateSoundTask_8002FF64;
}
// Matched
void UpdateSoundTask_8002FF64(int entry, SoundTask* task)
{
    int i;
    switch (task->state_2)
    {
    case 0:
        if (!GetFileRequestStatus_8003BE30(task->request_10) && !GetFileRequestStatus_8003BE30(task->request_14))
        {
            task->state_2++;
        }
        else
        {
            eventDispatchHalt_8008B540 = 1;
        }
        break;
    case 1:
        task->state_2 = 2;
        break;
    case 2:
        for (i = 0; i < 5; i++)
        {
            if (task->fades_18[i].active)
            {
                if (--task->fades_18[i].timer <= 0)
                {
                    SsSepStop(task->fades_18[i].access_num, task->fades_18[i].seq);
                    task->fades_18[i].active = 0;
                }
            }
        }
        break;
    }
}
extern void StopSoundSeqs_80030D68(SoundStruct* p);
// Matched
void FreeSoundTask_8003006C(EventEntry* entry, SoundTask* buffer)
{
    SoundTask* task = buffer;
    SoundStruct* bgm = &bgmSound_80091CE0;
    if (bgm->field_4_seq_num >= 0)
    {
        SsSepStop(bgm->field_C_sep_access_num, bgm->field_4_seq_num);
        bgm->field_4_seq_num = -1;
    }
    FreeSound_80030D00(task->bgm_4);
    StopSoundSeqs_80030D68(&systemSound_80091D40);
    FreeSound_80030D00(task->sfx_8);
}

extern void PlaySoundSeq_8003105C(SoundStruct* s, int idx, short loops);
extern void PlayMusicSeq_80031260(SoundStruct* s, int idx, short loops);
extern int QueueFileRequest_8003BC84(FileRequestDesc* req);
void LoadSoundFromBuffer_800307B4(SoundStruct** req, GenkiSoundHeader* pSndFileHeader);
// Matched
int PlayMusic_800300E0(int idx, int a1)
{
    SoundTask* task = soundTask_8008D4A4->entry.buffer;
    SoundStruct* bgm;
    FileRequestDesc req;
    int sub;
    if (idx < 10)
    {
        PlaySoundSeq_8003105C(&systemSound_80091D40, idx, 1);
        return 1;
    }
    if (task->bgm_4->field_6_sound_idx == idx)
    {
        if (task->bgm_4->field_4_seq_num == soundFiles_80082F0C[idx].field_2_seq)
        {
            return 1;
        }
        SsSepStop(task->bgm_4->field_C_sep_access_num, task->bgm_4->field_4_seq_num);
        SsSepSetVol(task->bgm_4->field_C_sep_access_num, task->bgm_4->field_4_seq_num, 0, 0);
        task->bgm_4->field_4_seq_num = soundFiles_80082F0C[idx].field_2_seq;
        PlayMusicSeq_80031260(task->bgm_4, idx, 1);
        return 1;
    }
    if (GetSoundFileId_80030D4C(task->bgm_4->field_6_sound_idx) == GetSoundFileId_80030D4C(idx))
    {
        SsSepStop(task->bgm_4->field_C_sep_access_num, task->bgm_4->field_4_seq_num);
        SsSepSetVol(task->bgm_4->field_C_sep_access_num, task->bgm_4->field_4_seq_num, 0, 0);
        task->bgm_4->field_4_seq_num = soundFiles_80082F0C[idx].field_2_seq;
        PlayMusicSeq_80031260(task->bgm_4, idx, 1);
        return 1;
    }
    if (task->sfx_8 && GetSoundFileId_80030D4C(task->sfx_8->field_6_sound_idx) == GetSoundFileId_80030D4C(idx))
    {
        task->sfx_8->field_4_seq_num = soundFiles_80082F0C[idx].field_2_seq;
        PlayMusicSeq_80031260(task->sfx_8, idx, 1);
        return 1;
    }
    if (task->state_2 != 2)
    {
        return 0;
    }
    bgm = &bgmSound_80091CE0;
    if (bgm->field_4_seq_num >= 0)
    {
        SsSepStop(bgm->field_C_sep_access_num, bgm->field_4_seq_num);
        bgm->field_4_seq_num = -1;
    }
    if (task->bgm_4->field_6_sound_idx >= 0)
    {
        FreeSound_80030D00(task->bgm_4);
    }
    if (task->sfx_8->field_6_sound_idx >= 0)
    {
        FreeSound_80030D00(task->sfx_8);
    }
    task->bgm_4->field_6_sound_idx = idx;
    task->state_2 = 0;
    req.flags_0 = 0x2C;
    req.fileId_4 = GetSoundFileId_80030D4C(task->bgm_4->field_6_sound_idx);
    req.params_14 = &task->bgm_4;
    req.offset_8 = 0;
    req.size_C = 0;
    req.dest_10 = 0;
    req.paramsSize_18 = 4;
    req.callback_1C = LoadSoundFromBuffer_800307B4;
    task->request_10 = QueueFileRequest_8003BC84(&req);
    sub = soundFiles_80082F0C[idx].field_6_sub_sound;
    if (sub >= 0)
    {
        task->sfx_8->field_6_sound_idx = sub;
        task->state_2 = 0;
        req.flags_0 = 0x2C;
        req.fileId_4 = GetSoundFileId_80030D4C(task->sfx_8->field_6_sound_idx);
        req.offset_8 = 0;
        req.size_C = 0;
        req.dest_10 = 0;
        req.params_14 = &task->sfx_8;
        req.paramsSize_18 = 4;
        req.callback_1C = LoadSoundFromBuffer_800307B4;
        task->request_14 = QueueFileRequest_8003BC84(&req);
    }
    return 1;
}
extern int QueueFileRequest_8003BC84(FileRequestDesc* req);
void LoadSoundSeqFromBuffer_800304D0(SoundStruct** req, char* pSndFileBuffer);
// Matched
int LoadSeqSlotSound_800303E8(void)
{
    SoundTask* task = soundTask_8008D4A4->entry.buffer;
    FileRequestDesc req;
    if (task->state_2 != 2)
    {
        return 0;
    }
    seqSlotSound_80091D00 = systemSound_80091D40;
    seqSlotSound_80091D00.field_8_sep_data_ptr = 0;
    seqSlotSound_80091D00.field_6_sound_idx = 10;
    task->state_2 = 0;
    req.flags_0 = 0x2C;
    req.fileId_4 = 0x301;
    req.params_14 = &task->seqSlot_C;
    req.paramsSize_18 = 4;
    req.offset_8 = 0;
    req.size_C = 0;
    req.dest_10 = 0;
    req.callback_1C = LoadSoundSeqFromBuffer_800304D0;
    task->request_10 = QueueFileRequest_8003BC84(&req);
    return 1;
}
// Matched
void LoadSoundSeqFromBuffer_800304D0(SoundStruct** req, char* pSndFileBuffer)
{
    SoundStruct* sound = req[0];
    GenkiSoundHeader* pSndFileHeader = (GenkiSoundHeader*)pSndFileBuffer;

    if (pSndFileHeader->field_14_sep_size)
    {
        sound->field_8_sep_data_ptr = malloc3_8003FC4C(pSndFileHeader->field_14_sep_size);
        ReadBytesInto_80040388((int*)sound->field_8_sep_data_ptr,
                               (int*)((char*)pSndFileHeader + pSndFileHeader->field_10_sep_data_start),
                               pSndFileHeader->field_14_sep_size / sizeof(int));

        sound->field_C_sep_access_num =
            SsSepOpen(sound->field_8_sep_data_ptr, sound->field_0_vab_id, soundFiles_80082F0C[sound->field_6_sound_idx].field_4_seq_count);
        if (sound->field_C_sep_access_num == -1)
        {
            printf(aAssertionFaile_0, aSoundC, 411);
            exit(1);
        }
        SsSepSetVol(sound->field_C_sep_access_num, 1, 0, 0);
    }
    else
    {
        sound->field_8_sep_data_ptr = 0;
    }

    if (pSndFileHeader->field_1C_sep_size)
    {
        sound->field_10_sep_data_ptr = malloc3_8003FC4C(pSndFileHeader->field_1C_sep_size);
        ReadBytesInto_80040388((int*)sound->field_10_sep_data_ptr,
                               (int*)(pSndFileBuffer + pSndFileHeader->field_18_sep_data2_ptr),
                               pSndFileHeader->field_1C_sep_size / sizeof(int));
        sound->field_14_sep_access_num =
            SsSepOpen(sound->field_10_sep_data_ptr, sound->field_0_vab_id, soundFiles_80082F0C[sound->field_6_sound_idx].field_5_seq_count);
        if (sound->field_14_sep_access_num == -1)
        {
            printf(aAssertionFaile_0, aSoundC, 426);
            exit(1);
        }
        SsSepSetVol(sound->field_14_sep_access_num, 1, 0, 0);
    }
    else
    {
        sound->field_10_sep_data_ptr = 0;
    }
}
// Matched
void FreeSeqSlotSound_80030664(void)
{
    FreeSoundSeqs_80030EEC(&seqSlotSound_80091D00);
}
// Matched
int IsSoundTaskReady_80030688(void)
{
    return ((SoundTask*)soundTask_8008D4A4->entry.buffer)->state_2 == 2;
}
// Matched
int IsSoundTaskReady_800306B0(void)
{
    return ((SoundTask*)soundTask_8008D4A4->entry.buffer)->state_2 == 2;
}
// Matched
void FreeBgmSeqs_800306D8(void)
{
    FreeSoundSeqs_80030EEC(&bgmSound_80091CE0);
}
extern void StopSoundSeq_80031408(SoundStruct* s, int idx);
// Matched
void StopSoundSeqById_800306FC(int idx)
{
    SoundTask* task = soundTask_8008D4A4->entry.buffer;
    if (idx < 10)
    {
        StopSoundSeq_80031408(&systemSound_80091D40, idx);
        return;
    }
    if (GetSoundFileId_80030D4C(task->bgm_4->field_6_sound_idx) == GetSoundFileId_80030D4C(idx))
    {
        StopSoundSeq_80031408(task->bgm_4, idx);
    }
    if (GetSoundFileId_80030D4C(task->sfx_8->field_6_sound_idx) == GetSoundFileId_80030D4C(idx))
    {
        StopSoundSeq_80031408(task->sfx_8, idx);
    }
}
extern void PlayMusicSeq_80031260(SoundStruct* s, int idx, short loops);
// Matched
void LoadSoundFromBuffer_800307B4(SoundStruct** req, GenkiSoundHeader* pSndFileHeader)
{
    SoundStruct* sound = req[0];

    sound->field_18_vab_header_ptr = malloc3_8003FC4C(pSndFileHeader->field_4_vab_header_size);

    ReadBytesInto_80040388((int*)sound->field_18_vab_header_ptr,
                           (int*)((char*)pSndFileHeader + pSndFileHeader->field_0_header_start),
                           pSndFileHeader->field_4_vab_header_size / sizeof(int));

    sound->field_0_vab_id = SsVabOpenHead(sound->field_18_vab_header_ptr, -1);
    if (sound->field_0_vab_id == -1)
    {
        printf(aAssertionFaile_0, aSoundC, 540);
        exit(1);
    }

    if (SsVabTransBody((unsigned char*)((char*)pSndFileHeader + pSndFileHeader->field_8_vab_body_start), sound->field_0_vab_id) == -1)
    {
        printf(aAssertionFaile_0, aSoundC, 546);
        exit(1);
    }
    SsVabTransCompleted(1);

    if (pSndFileHeader->field_14_sep_size)
    {
        sound->field_8_sep_data_ptr = malloc3_8003FC4C(pSndFileHeader->field_14_sep_size);
        ReadBytesInto_80040388((int*)sound->field_8_sep_data_ptr,
                               (int*)((char*)pSndFileHeader + pSndFileHeader->field_10_sep_data_start),
                               pSndFileHeader->field_14_sep_size / sizeof(int));

        sound->field_C_sep_access_num =
            SsSepOpen(sound->field_8_sep_data_ptr, sound->field_0_vab_id, soundFiles_80082F0C[sound->field_6_sound_idx].field_4_seq_count);
        if (sound->field_C_sep_access_num == -1)
        {
            printf(aAssertionFaile_0, aSoundC, 559);
            exit(1);
        }
        SsSepSetVol(sound->field_C_sep_access_num, 1, 0, 0);
    }
    else
    {
        sound->field_8_sep_data_ptr = 0;
    }
    sound->field_10_sep_data_ptr = 0;

    SsUtSetReverbDepth(50, 50);
    sound->field_4_seq_num = -1;

    if (sound->field_8_sep_data_ptr && soundFiles_80082F0C[sound->field_6_sound_idx].field_2_seq >= 0)
    {
        PlayMusicSeq_80031260(sound, sound->field_6_sound_idx, 1);
    }
}
// Matched
void ApplyAudioOutputFormat_80030988(void)
{
    if (!((settingsFlags_8008B58C.word >> 6) & 1))
    {
        SsSetStereo();
    }
    else
    {
        SsSetMono();
    }
    SsSetMVol(0x7F, 0x7F);
}
// Matched
void ApplyBgmVolume_800309D8(SoundStruct* sound)
{
    int i;
    for (i = 0; i < soundFiles_80082F0C[sound->field_6_sound_idx].field_4_seq_count; i++)
    {
        int vol = (saveData_8008B570.settings_1C.word >> 7) & 0x7F;
        SsSepSetVol(sound->field_C_sep_access_num, i, vol, vol);
    }
}
// Matched
void LoadSound_80030A84(short soundId, SoundStruct* sound)
{
    char* pSndFileBuffer;
    GenkiSoundHeader* pSndFileHeader;

    sound->field_6_sound_idx = soundId;

    pSndFileBuffer = DATA_GetFileBuffer_8003CAA0(GetSoundFileId_80030D4C(sound->field_6_sound_idx));
    pSndFileHeader = (GenkiSoundHeader*)pSndFileBuffer;

    sound->field_18_vab_header_ptr = malloc3_8003FC4C(pSndFileHeader->field_4_vab_header_size);

    ReadBytesInto_80040388((int*)sound->field_18_vab_header_ptr,
                           (int*)(pSndFileBuffer + pSndFileHeader->field_0_header_start),
                           pSndFileHeader->field_4_vab_header_size / sizeof(int));

    sound->field_0_vab_id = SsVabOpenHead(sound->field_18_vab_header_ptr, -1);
    if (sound->field_0_vab_id == -1)
    {
        printf(aAssertionFaile_0, aSoundC, 631);
        exit(1);
    }

    if (SsVabTransBody((unsigned char*)(pSndFileBuffer + pSndFileHeader->field_8_vab_body_start), sound->field_0_vab_id) == -1)
    {
        printf(aAssertionFaile_0, aSoundC, 639);
        exit(1);
    }
    SsVabTransCompleted(1);

    if (pSndFileHeader->field_14_sep_size)
    {
        sound->field_8_sep_data_ptr = malloc3_8003FC4C(pSndFileHeader->field_14_sep_size);
        ReadBytesInto_80040388((int*)sound->field_8_sep_data_ptr,
                               (int*)(pSndFileBuffer + pSndFileHeader->field_10_sep_data_start),
                               pSndFileHeader->field_14_sep_size / sizeof(int));

        sound->field_C_sep_access_num =
            SsSepOpen(sound->field_8_sep_data_ptr, sound->field_0_vab_id, soundFiles_80082F0C[sound->field_6_sound_idx].field_4_seq_count);
        if (sound->field_C_sep_access_num == -1)
        {
            printf(aAssertionFaile_0, aSoundC, 652);
            exit(1);
        }
        SsSepSetVol(sound->field_C_sep_access_num, 1, 0, 0);
    }
    else
    {
        sound->field_8_sep_data_ptr = 0;
    }

    if (pSndFileHeader->field_1C_sep_size)
    {
        sound->field_10_sep_data_ptr = malloc3_8003FC4C(pSndFileHeader->field_1C_sep_size);
        ReadBytesInto_80040388((int*)sound->field_10_sep_data_ptr,
                               (int*)(pSndFileBuffer + pSndFileHeader->field_18_sep_data2_ptr),
                               pSndFileHeader->field_1C_sep_size / sizeof(int));
        sound->field_14_sep_access_num =
            SsSepOpen(sound->field_10_sep_data_ptr, sound->field_0_vab_id, soundFiles_80082F0C[sound->field_6_sound_idx].field_5_seq_count);
        if (sound->field_14_sep_access_num == -1)
        {
            printf(aAssertionFaile_0, aSoundC, 667);
            exit(1);
        }
        SsSepSetVol(sound->field_14_sep_access_num, 1, 0, 0);
    }
    else
    {
        sound->field_10_sep_data_ptr = 0;
    }

    SsUtSetReverbDepth(50, 50);
    sound->field_4_seq_num = -1;

    free3_8003FC6C(pSndFileBuffer);
}
