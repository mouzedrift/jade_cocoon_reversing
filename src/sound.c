#include "common.h"
#include "funcs.h"
#include "sdk.h"
#include "globals.h"
#include "sound.h"
#include "soundtask.h"
#include "data_decls.h"
#include "util.h"
#include "movie.h"
#include "cd.h"
#include "sound_seq.h"
#include "menu_draw.h"
#include "cdread.h"

const char aAssertionFaile_0[] = "Assertion failed: file \"%s\", line %d\n";
const char aSoundC[] = "SOUND.C";

void DrawLevantHeaderWindows_8002FD0C(int ot, short step, short highlight, short animate, RECT* clipRect)
{
    RECT buf;
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
    InterpolateWindowRect_8004196C(&buf, &rect, step, 8, 0);
    loc[0] = 12;
    loc[1] = 0x2E;
    DrawPortrait_8002A42C(loc, 0, clipRect, ot);
    desc1.colorSet_8 = highlight;
    desc1.rect_0 = &buf;
    desc1.time_4 = time;
    desc1.ot_A = ot;
    DrawUiWindow_8002A384(&desc1);
    rect.x = 0x4E;
    rect.y = 0x2C;
    rect.w = 0x8D;
    rect.h = 0x44;
    InterpolateWindowRect_8004196C(&buf, &rect, step, 8, 0);
    desc2.colorSet_8 = highlight;
    desc2.rect_0 = &buf;
    desc2.time_4 = time;
    desc2.ot_A = ot;
    DrawUiWindow_8002A384(&desc2);
}
void InitSound_8002FE54(SoundStruct* sound)
{
    sound->vabId_0 = -1;
    sound->seqNum_4 = -1;
    sound->soundIdx_6 = -1;
    sound->sepAccessNum_C = -1;
    sound->sepAccessNum_14 = -1;
    sound->sepDataPtr_8 = 0;
    sound->sepDataPtr_10 = 0;
    sound->vabHeaderPtr_18 = 0;
}
void InitSounds_8002FE7C(void)
{
    InitSound_8002FE54(&bgmSound_80091CE0);
    InitSound_8002FE54(&sfxSound_80091D20);
    InitSound_8002FE54(&seqSlotSound_80091D00);
}
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
void FreeSoundTask_8003006C(EventEntry* entry, SoundTask* buffer)
{
    SoundTask* task = buffer;
    SoundStruct* bgm = &bgmSound_80091CE0;
    if (bgm->seqNum_4 >= 0)
    {
        SsSepStop(bgm->sepAccessNum_C, bgm->seqNum_4);
        bgm->seqNum_4 = -1;
    }
    FreeSound_80030D00(task->bgm_4);
    StopSoundSeqs_80030D68(&systemSound_80091D40);
    FreeSound_80030D00(task->sfx_8);
}

int PlayMusic_800300E0(int idx, int unused)
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
    if (task->bgm_4->soundIdx_6 == idx)
    {
        if (task->bgm_4->seqNum_4 == soundFiles_80082F0C[idx].field_2_seq)
        {
            return 1;
        }
        SsSepStop(task->bgm_4->sepAccessNum_C, task->bgm_4->seqNum_4);
        SsSepSetVol(task->bgm_4->sepAccessNum_C, task->bgm_4->seqNum_4, 0, 0);
        task->bgm_4->seqNum_4 = soundFiles_80082F0C[idx].field_2_seq;
        PlayMusicSeq_80031260(task->bgm_4, idx, 1);
        return 1;
    }
    if (GetSoundFileId_80030D4C(task->bgm_4->soundIdx_6) == GetSoundFileId_80030D4C(idx))
    {
        SsSepStop(task->bgm_4->sepAccessNum_C, task->bgm_4->seqNum_4);
        SsSepSetVol(task->bgm_4->sepAccessNum_C, task->bgm_4->seqNum_4, 0, 0);
        task->bgm_4->seqNum_4 = soundFiles_80082F0C[idx].field_2_seq;
        PlayMusicSeq_80031260(task->bgm_4, idx, 1);
        return 1;
    }
    if (task->sfx_8 && GetSoundFileId_80030D4C(task->sfx_8->soundIdx_6) == GetSoundFileId_80030D4C(idx))
    {
        task->sfx_8->seqNum_4 = soundFiles_80082F0C[idx].field_2_seq;
        PlayMusicSeq_80031260(task->sfx_8, idx, 1);
        return 1;
    }
    if (task->state_2 != 2)
    {
        return 0;
    }
    bgm = &bgmSound_80091CE0;
    if (bgm->seqNum_4 >= 0)
    {
        SsSepStop(bgm->sepAccessNum_C, bgm->seqNum_4);
        bgm->seqNum_4 = -1;
    }
    if (task->bgm_4->soundIdx_6 >= 0)
    {
        FreeSound_80030D00(task->bgm_4);
    }
    if (task->sfx_8->soundIdx_6 >= 0)
    {
        FreeSound_80030D00(task->sfx_8);
    }
    task->bgm_4->soundIdx_6 = idx;
    task->state_2 = 0;
    req.flags_0 = 0x2C;
    req.fileId_4 = GetSoundFileId_80030D4C(task->bgm_4->soundIdx_6);
    req.params_14 = &task->bgm_4;
    req.offset_8 = 0;
    req.size_C = 0;
    req.dest_10 = 0;
    req.paramsSize_18 = 4;
    req.callback_1C = LoadSoundFromBuffer_800307B4;
    task->request_10 = QueueFileRequest_8003BC84(&req);
    sub = soundFiles_80082F0C[idx].subSound_6;
    if (sub >= 0)
    {
        task->sfx_8->soundIdx_6 = sub;
        task->state_2 = 0;
        req.flags_0 = 0x2C;
        req.fileId_4 = GetSoundFileId_80030D4C(task->sfx_8->soundIdx_6);
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
int LoadSeqSlotSound_800303E8(void)
{
    SoundTask* task = soundTask_8008D4A4->entry.buffer;
    FileRequestDesc req;
    if (task->state_2 != 2)
    {
        return 0;
    }
    seqSlotSound_80091D00 = systemSound_80091D40;
    seqSlotSound_80091D00.sepDataPtr_8 = 0;
    seqSlotSound_80091D00.soundIdx_6 = 10;
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
void LoadSoundSeqFromBuffer_800304D0(SoundStruct** req, char* pSndFileBuffer)
{
    SoundStruct* sound = req[0];
    GenkiSoundHeader* pSndFileHeader = (GenkiSoundHeader*)pSndFileBuffer;

    if (pSndFileHeader->sepSize_14)
    {
        sound->sepDataPtr_8 = malloc3_8003FC4C(pSndFileHeader->sepSize_14);
        ReadBytesInto_80040388((int*)sound->sepDataPtr_8,
                               (int*)((char*)pSndFileHeader + pSndFileHeader->sepDataStart_10),
                               pSndFileHeader->sepSize_14 / sizeof(int));

        sound->sepAccessNum_C =
            SsSepOpen(sound->sepDataPtr_8, sound->vabId_0, soundFiles_80082F0C[sound->soundIdx_6].seqCount_4);
        if (sound->sepAccessNum_C == -1)
        {
            printf(aAssertionFaile_0, aSoundC, 411);
            exit(1);
        }
        SsSepSetVol(sound->sepAccessNum_C, 1, 0, 0);
    }
    else
    {
        sound->sepDataPtr_8 = 0;
    }

    if (pSndFileHeader->sepSize_1C)
    {
        sound->sepDataPtr_10 = malloc3_8003FC4C(pSndFileHeader->sepSize_1C);
        ReadBytesInto_80040388((int*)sound->sepDataPtr_10,
                               (int*)(pSndFileBuffer + pSndFileHeader->sepData2Ptr_18),
                               pSndFileHeader->sepSize_1C / sizeof(int));
        sound->sepAccessNum_14 =
            SsSepOpen(sound->sepDataPtr_10, sound->vabId_0, soundFiles_80082F0C[sound->soundIdx_6].seqCount_5);
        if (sound->sepAccessNum_14 == -1)
        {
            printf(aAssertionFaile_0, aSoundC, 426);
            exit(1);
        }
        SsSepSetVol(sound->sepAccessNum_14, 1, 0, 0);
    }
    else
    {
        sound->sepDataPtr_10 = 0;
    }
}
void FreeSeqSlotSound_80030664(void)
{
    FreeSoundSeqs_80030EEC(&seqSlotSound_80091D00);
}
int IsSoundTaskReady_80030688(void)
{
    return ((SoundTask*)soundTask_8008D4A4->entry.buffer)->state_2 == 2;
}
int IsSoundTaskReady_800306B0(void)
{
    return ((SoundTask*)soundTask_8008D4A4->entry.buffer)->state_2 == 2;
}
void FreeBgmSeqs_800306D8(void)
{
    FreeSoundSeqs_80030EEC(&bgmSound_80091CE0);
}
void StopSoundSeqById_800306FC(int idx)
{
    SoundTask* task = soundTask_8008D4A4->entry.buffer;
    if (idx < 10)
    {
        StopSoundSeq_80031408(&systemSound_80091D40, idx);
        return;
    }
    if (GetSoundFileId_80030D4C(task->bgm_4->soundIdx_6) == GetSoundFileId_80030D4C(idx))
    {
        StopSoundSeq_80031408(task->bgm_4, idx);
    }
    if (GetSoundFileId_80030D4C(task->sfx_8->soundIdx_6) == GetSoundFileId_80030D4C(idx))
    {
        StopSoundSeq_80031408(task->sfx_8, idx);
    }
}
void LoadSoundFromBuffer_800307B4(SoundStruct** req, GenkiSoundHeader* pSndFileHeader)
{
    SoundStruct* sound = req[0];

    sound->vabHeaderPtr_18 = malloc3_8003FC4C(pSndFileHeader->vabHeaderSize_4);

    ReadBytesInto_80040388((int*)sound->vabHeaderPtr_18,
                           (int*)((char*)pSndFileHeader + pSndFileHeader->headerStart_0),
                           pSndFileHeader->vabHeaderSize_4 / sizeof(int));

    sound->vabId_0 = SsVabOpenHead(sound->vabHeaderPtr_18, -1);
    if (sound->vabId_0 == -1)
    {
        printf(aAssertionFaile_0, aSoundC, 540);
        exit(1);
    }

    if (SsVabTransBody((unsigned char*)((char*)pSndFileHeader + pSndFileHeader->vabBodyStart_8), sound->vabId_0) == -1)
    {
        printf(aAssertionFaile_0, aSoundC, 546);
        exit(1);
    }
    SsVabTransCompleted(1);

    if (pSndFileHeader->sepSize_14)
    {
        sound->sepDataPtr_8 = malloc3_8003FC4C(pSndFileHeader->sepSize_14);
        ReadBytesInto_80040388((int*)sound->sepDataPtr_8,
                               (int*)((char*)pSndFileHeader + pSndFileHeader->sepDataStart_10),
                               pSndFileHeader->sepSize_14 / sizeof(int));

        sound->sepAccessNum_C =
            SsSepOpen(sound->sepDataPtr_8, sound->vabId_0, soundFiles_80082F0C[sound->soundIdx_6].seqCount_4);
        if (sound->sepAccessNum_C == -1)
        {
            printf(aAssertionFaile_0, aSoundC, 559);
            exit(1);
        }
        SsSepSetVol(sound->sepAccessNum_C, 1, 0, 0);
    }
    else
    {
        sound->sepDataPtr_8 = 0;
    }
    sound->sepDataPtr_10 = 0;

    SsUtSetReverbDepth(50, 50);
    sound->seqNum_4 = -1;

    if (sound->sepDataPtr_8 && soundFiles_80082F0C[sound->soundIdx_6].field_2_seq >= 0)
    {
        PlayMusicSeq_80031260(sound, sound->soundIdx_6, 1);
    }
}
void ApplyAudioOutputFormat_80030988(void)
{
    if (!((saveData_8008B570.settings_1C.word >> 6) & 1))
    {
        SsSetStereo();
    }
    else
    {
        SsSetMono();
    }
    SsSetMVol(0x7F, 0x7F);
}
void ApplyBgmVolume_800309D8(SoundStruct* sound)
{
    int i;
    for (i = 0; i < soundFiles_80082F0C[sound->soundIdx_6].seqCount_4; i++)
    {
        int vol = (saveData_8008B570.settings_1C.word >> 7) & 0x7F;
        SsSepSetVol(sound->sepAccessNum_C, i, vol, vol);
    }
}
void LoadSound_80030A84(short soundId, SoundStruct* sound)
{
    char* pSndFileBuffer;
    GenkiSoundHeader* pSndFileHeader;

    sound->soundIdx_6 = soundId;

    pSndFileBuffer = DATA_GetFileBuffer_8003CAA0(GetSoundFileId_80030D4C(sound->soundIdx_6));
    pSndFileHeader = (GenkiSoundHeader*)pSndFileBuffer;

    sound->vabHeaderPtr_18 = malloc3_8003FC4C(pSndFileHeader->vabHeaderSize_4);

    ReadBytesInto_80040388((int*)sound->vabHeaderPtr_18,
                           (int*)(pSndFileBuffer + pSndFileHeader->headerStart_0),
                           pSndFileHeader->vabHeaderSize_4 / sizeof(int));

    sound->vabId_0 = SsVabOpenHead(sound->vabHeaderPtr_18, -1);
    if (sound->vabId_0 == -1)
    {
        printf(aAssertionFaile_0, aSoundC, 631);
        exit(1);
    }

    if (SsVabTransBody((unsigned char*)(pSndFileBuffer + pSndFileHeader->vabBodyStart_8), sound->vabId_0) == -1)
    {
        printf(aAssertionFaile_0, aSoundC, 639);
        exit(1);
    }
    SsVabTransCompleted(1);

    if (pSndFileHeader->sepSize_14)
    {
        sound->sepDataPtr_8 = malloc3_8003FC4C(pSndFileHeader->sepSize_14);
        ReadBytesInto_80040388((int*)sound->sepDataPtr_8,
                               (int*)(pSndFileBuffer + pSndFileHeader->sepDataStart_10),
                               pSndFileHeader->sepSize_14 / sizeof(int));

        sound->sepAccessNum_C =
            SsSepOpen(sound->sepDataPtr_8, sound->vabId_0, soundFiles_80082F0C[sound->soundIdx_6].seqCount_4);
        if (sound->sepAccessNum_C == -1)
        {
            printf(aAssertionFaile_0, aSoundC, 652);
            exit(1);
        }
        SsSepSetVol(sound->sepAccessNum_C, 1, 0, 0);
    }
    else
    {
        sound->sepDataPtr_8 = 0;
    }

    if (pSndFileHeader->sepSize_1C)
    {
        sound->sepDataPtr_10 = malloc3_8003FC4C(pSndFileHeader->sepSize_1C);
        ReadBytesInto_80040388((int*)sound->sepDataPtr_10,
                               (int*)(pSndFileBuffer + pSndFileHeader->sepData2Ptr_18),
                               pSndFileHeader->sepSize_1C / sizeof(int));
        sound->sepAccessNum_14 =
            SsSepOpen(sound->sepDataPtr_10, sound->vabId_0, soundFiles_80082F0C[sound->soundIdx_6].seqCount_5);
        if (sound->sepAccessNum_14 == -1)
        {
            printf(aAssertionFaile_0, aSoundC, 667);
            exit(1);
        }
        SsSepSetVol(sound->sepAccessNum_14, 1, 0, 0);
    }
    else
    {
        sound->sepDataPtr_10 = 0;
    }

    SsUtSetReverbDepth(50, 50);
    sound->seqNum_4 = -1;

    free3_8003FC6C(pSndFileBuffer);
}
