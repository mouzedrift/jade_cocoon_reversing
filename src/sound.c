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

INCLUDE_DATA(dword_80074438);
INCLUDE_DATA(dword_8007443C);
INCLUDE_DATA(dword_80074440);
INCLUDE_DATA(dword_80074444);
INCLUDE_DATA(word_80074448);
INCLUDE_DATA(aAssertionFaile_0);
INCLUDE_DATA(aSoundC);

typedef struct
{
    void* field_0;
    int field_4;
    short field_8;
    short field_A;
} struct_FD0C;
extern void InterpolateWindowRect_8004196C(void* a0, RECT* a1, int a2, int a3, int a4);
extern void sub_8002A42C(unsigned short* pos, short a1, int a2, short a3);
extern void DrawUiWindow_8002A384(struct_FD0C* p);
// Matched
void sub_8002FD0C(int a0, short a1, short a2, short flag, int a4)
{
    char buf[8];
    RECT r;
    unsigned short loc[2];
    struct_FD0C s1;
    struct_FD0C s2;
    int v;
    if (flag)
    {
        v = frameCount_8008D3FC;
    }
    else
    {
        v = 0;
    }
    r.x = 10;
    r.y = 0x2C;
    r.w = 0x44;
    r.h = 0x44;
    InterpolateWindowRect_8004196C(buf, &r, a1, 8, 0);
    loc[0] = 12;
    loc[1] = 0x2E;
    sub_8002A42C(loc, 0, a4, a0);
    s1.field_8 = a2;
    s1.field_0 = buf;
    s1.field_4 = v;
    s1.field_A = a0;
    DrawUiWindow_8002A384(&s1);
    r.x = 0x4E;
    r.y = 0x2C;
    r.w = 0x8D;
    r.h = 0x44;
    InterpolateWindowRect_8004196C(buf, &r, a1, 8, 0);
    s2.field_8 = a2;
    s2.field_0 = buf;
    s2.field_4 = v;
    s2.field_A = a0;
    DrawUiWindow_8002A384(&s2);
}
// Matched
void InitSound_8002FE54(SoundStruct* arg1)
{
    arg1->field_0_vab_id = -1;
    arg1->field_4_seq_num = -1;
    arg1->field_6_sound_idx = -1;
    arg1->field_C_sep_access_num = -1;
    arg1->field_14_sep_access_num = -1;
    arg1->field_8_sep_data_ptr = 0;
    arg1->field_10_sep_data_ptr = 0;
    arg1->field_18_vab_header_ptr = 0;
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
    SoundTask* p = soundTask_8008D4A4->entry.buffer;
    int i;
    p->bgm_4 = &bgmSound_80091CE0;
    p->sfx_8 = &sfxSound_80091D20;
    p->seqSlot_C = &seqSlotSound_80091D00;
    p->state_2 = 2;
    for (i = 4; i >= 0; i--)
    {
        p->fades_18[i].active = 0;
    }
}
extern void UpdateSoundTask_8002FF64();
// Matched
void InitSoundTask_8002FF10(EventEntry* a, SoundTask* p)
{
    int i;
    p->bgm_4 = &bgmSound_80091CE0;
    p->sfx_8 = &sfxSound_80091D20;
    p->seqSlot_C = &seqSlotSound_80091D00;
    p->state_2 = 2;
    for (i = 4; i >= 0; i--)
    {
        p->fades_18[i].active = 0;
    }
    a->cb_8 = (EventEntryFn)UpdateSoundTask_8002FF64;
}
// Matched
void UpdateSoundTask_8002FF64(int a0, SoundTask* p)
{
    int i;
    switch (p->state_2)
    {
    case 0:
        if (!GetFileRequestStatus_8003BE30(p->request_10) && !GetFileRequestStatus_8003BE30(p->request_14))
        {
            p->state_2++;
        }
        else
        {
            eventDispatchHalt_8008B540 = 1;
        }
        break;
    case 1:
        p->state_2 = 2;
        break;
    case 2:
        for (i = 0; i < 5; i++)
        {
            if (p->fades_18[i].active)
            {
                if (--p->fades_18[i].timer <= 0)
                {
                    SsSepStop(p->fades_18[i].access_num, p->fades_18[i].seq);
                    p->fades_18[i].active = 0;
                }
            }
        }
        break;
    }
}
extern void StopSoundSeqs_80030D68(SoundStruct* p);
#if 0
// Not matched: register allocation of the sequence number
void FreeSoundTask_8003006C(EventEntry* a0, SoundTask* a1)
{
    SoundStruct* s = &bgmSound_80091CE0;
    short seq = s->field_4_seq_num;
    if (seq >= 0)
    {
        SsSepStop(s->field_C_sep_access_num, seq);
        s->field_4_seq_num = -1;
    }
    FreeSound_80030D00(a1->bgm_4);
    StopSoundSeqs_80030D68(&systemSound_80091D40);
    FreeSound_80030D00(a1->sfx_8);
}
#endif
INCLUDE_ASM(FreeSoundTask_8003006C);

extern void PlaySoundSeq_8003105C(SoundStruct* s, int idx, short loops);
extern void PlayMusicSeq_80031260(SoundStruct* s, int idx, short loops);
extern int QueueFileRequest_8003BC84(FileRequestDesc* req);
void LoadSoundFromBuffer_800307B4(SoundStruct** req, GenkiSoundHeader* pSndFileHeader);
// Matched
int PlayMusic_800300E0(int idx, int a1)
{
    SoundTask* t = soundTask_8008D4A4->entry.buffer;
    SoundStruct* s;
    FileRequestDesc req;
    int sub;
    if (idx < 10)
    {
        PlaySoundSeq_8003105C(&systemSound_80091D40, idx, 1);
        return 1;
    }
    if (t->bgm_4->field_6_sound_idx == idx)
    {
        if (t->bgm_4->field_4_seq_num == soundFiles_80082F0C[idx].field_2_seq)
        {
            return 1;
        }
        SsSepStop(t->bgm_4->field_C_sep_access_num, t->bgm_4->field_4_seq_num);
        SsSepSetVol(t->bgm_4->field_C_sep_access_num, t->bgm_4->field_4_seq_num, 0, 0);
        t->bgm_4->field_4_seq_num = soundFiles_80082F0C[idx].field_2_seq;
        PlayMusicSeq_80031260(t->bgm_4, idx, 1);
        return 1;
    }
    if (GetSoundFileId_80030D4C(t->bgm_4->field_6_sound_idx) == GetSoundFileId_80030D4C(idx))
    {
        SsSepStop(t->bgm_4->field_C_sep_access_num, t->bgm_4->field_4_seq_num);
        SsSepSetVol(t->bgm_4->field_C_sep_access_num, t->bgm_4->field_4_seq_num, 0, 0);
        t->bgm_4->field_4_seq_num = soundFiles_80082F0C[idx].field_2_seq;
        PlayMusicSeq_80031260(t->bgm_4, idx, 1);
        return 1;
    }
    if (t->sfx_8 && GetSoundFileId_80030D4C(t->sfx_8->field_6_sound_idx) == GetSoundFileId_80030D4C(idx))
    {
        t->sfx_8->field_4_seq_num = soundFiles_80082F0C[idx].field_2_seq;
        PlayMusicSeq_80031260(t->sfx_8, idx, 1);
        return 1;
    }
    if (t->state_2 != 2)
    {
        return 0;
    }
    s = &bgmSound_80091CE0;
    if (s->field_4_seq_num >= 0)
    {
        SsSepStop(s->field_C_sep_access_num, s->field_4_seq_num);
        s->field_4_seq_num = -1;
    }
    if (t->bgm_4->field_6_sound_idx >= 0)
    {
        FreeSound_80030D00(t->bgm_4);
    }
    if (t->sfx_8->field_6_sound_idx >= 0)
    {
        FreeSound_80030D00(t->sfx_8);
    }
    t->bgm_4->field_6_sound_idx = idx;
    t->state_2 = 0;
    req.flags_0 = 0x2C;
    req.fileId_4 = GetSoundFileId_80030D4C(t->bgm_4->field_6_sound_idx);
    req.params_14 = &t->bgm_4;
    req.offset_8 = 0;
    req.size_C = 0;
    req.dest_10 = 0;
    req.paramsSize_18 = 4;
    req.callback_1C = LoadSoundFromBuffer_800307B4;
    t->request_10 = QueueFileRequest_8003BC84(&req);
    sub = soundFiles_80082F0C[idx].field_6_sub_sound;
    if (sub >= 0)
    {
        t->sfx_8->field_6_sound_idx = sub;
        t->state_2 = 0;
        req.flags_0 = 0x2C;
        req.fileId_4 = GetSoundFileId_80030D4C(t->sfx_8->field_6_sound_idx);
        req.offset_8 = 0;
        req.size_C = 0;
        req.dest_10 = 0;
        req.params_14 = &t->sfx_8;
        req.paramsSize_18 = 4;
        req.callback_1C = LoadSoundFromBuffer_800307B4;
        t->request_14 = QueueFileRequest_8003BC84(&req);
    }
    return 1;
}
extern int QueueFileRequest_8003BC84(FileRequestDesc* req);
void LoadSoundSeqFromBuffer_800304D0(SoundStruct** req, char* pSndFileBuffer);
// Matched
int LoadSeqSlotSound_800303E8(void)
{
    SoundTask* p = soundTask_8008D4A4->entry.buffer;
    FileRequestDesc s;
    if (p->state_2 != 2)
    {
        return 0;
    }
    seqSlotSound_80091D00 = systemSound_80091D40;
    seqSlotSound_80091D00.field_8_sep_data_ptr = 0;
    seqSlotSound_80091D00.field_6_sound_idx = 10;
    p->state_2 = 0;
    s.flags_0 = 0x2C;
    s.fileId_4 = 0x301;
    s.params_14 = &p->seqSlot_C;
    s.paramsSize_18 = 4;
    s.offset_8 = 0;
    s.size_C = 0;
    s.dest_10 = 0;
    s.callback_1C = LoadSoundSeqFromBuffer_800304D0;
    p->request_10 = QueueFileRequest_8003BC84(&s);
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
                               (int*)((char*)pSndFileHeader + pSndFileHeader->field_10),
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
    SoundTask* p = soundTask_8008D4A4->entry.buffer;
    if (idx < 10)
    {
        StopSoundSeq_80031408(&systemSound_80091D40, idx);
        return;
    }
    if (GetSoundFileId_80030D4C(p->bgm_4->field_6_sound_idx) == GetSoundFileId_80030D4C(idx))
    {
        StopSoundSeq_80031408(p->bgm_4, idx);
    }
    if (GetSoundFileId_80030D4C(p->sfx_8->field_6_sound_idx) == GetSoundFileId_80030D4C(idx))
    {
        StopSoundSeq_80031408(p->sfx_8, idx);
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

    if (SsVabTransBody((unsigned char*)((char*)pSndFileHeader + pSndFileHeader->field_8), sound->field_0_vab_id) == -1)
    {
        printf(aAssertionFaile_0, aSoundC, 546);
        exit(1);
    }
    SsVabTransCompleted(1);

    if (pSndFileHeader->field_14_sep_size)
    {
        sound->field_8_sep_data_ptr = malloc3_8003FC4C(pSndFileHeader->field_14_sep_size);
        ReadBytesInto_80040388((int*)sound->field_8_sep_data_ptr,
                               (int*)((char*)pSndFileHeader + pSndFileHeader->field_10),
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
void ApplyBgmVolume_800309D8(SoundStruct* s)
{
    int i;
    for (i = 0; i < soundFiles_80082F0C[s->field_6_sound_idx].field_4_seq_count; i++)
    {
        int vol = (saveData_8008B570.settings_1C.word >> 7) & 0x7F;
        SsSepSetVol(s->field_C_sep_access_num, i, vol, vol);
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

    if (SsVabTransBody((unsigned char*)(pSndFileBuffer + pSndFileHeader->field_8), sound->field_0_vab_id) == -1)
    {
        printf(aAssertionFaile_0, aSoundC, 639);
        exit(1);
    }
    SsVabTransCompleted(1);

    if (pSndFileHeader->field_14_sep_size)
    {
        sound->field_8_sep_data_ptr = malloc3_8003FC4C(pSndFileHeader->field_14_sep_size);
        ReadBytesInto_80040388((int*)sound->field_8_sep_data_ptr,
                               (int*)(pSndFileBuffer + pSndFileHeader->field_10),
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
