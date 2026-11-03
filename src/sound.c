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
extern void sub_8004196C(void* a0, RECT* a1, int a2, int a3, int a4);
extern void sub_8002A42C(unsigned short* pos, short a1, int a2, short a3);
extern void sub_8002A384(struct_FD0C* p);
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
    sub_8004196C(buf, &r, a1, 8, 0);
    loc[0] = 12;
    loc[1] = 0x2E;
    sub_8002A42C(loc, 0, a4, a0);
    s1.field_8 = a2;
    s1.field_0 = buf;
    s1.field_4 = v;
    s1.field_A = a0;
    sub_8002A384(&s1);
    r.x = 0x4E;
    r.y = 0x2C;
    r.w = 0x8D;
    r.h = 0x44;
    sub_8004196C(buf, &r, a1, 8, 0);
    s2.field_8 = a2;
    s2.field_0 = buf;
    s2.field_4 = v;
    s2.field_A = a0;
    sub_8002A384(&s2);
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
    InitSound_8002FE54(&stru_80091D00);
}
// Matched
void sub_8002FEB8(void)
{
    char* p = (char*)soundTask_8008D4A4[0x24 / 4];
    char* q;
    int i;
    *(SoundStruct**)(p + 4) = &bgmSound_80091CE0;
    *(SoundStruct**)(p + 8) = &sfxSound_80091D20;
    *(SoundStruct**)(p + 0xC) = &stru_80091D00;
    *(short*)(p + 2) = 2;
    q = p + 0x20;
    for (i = 4; i >= 0; i--)
    {
        *(short*)(q + 0x18) = 0;
        q -= 8;
    }
}
extern void sub_8002FF64();
typedef struct
{
    short field_0;
    short field_2;
    SoundStruct* field_4;
    SoundStruct* field_8;
    SoundStruct* field_C;
    char pad_10[8];
    struct
    {
        short a;
        short b;
        int c;
    } e[5];
} struct_FF10;
// Matched
void sub_8002FF10(char* a, struct_FF10* p)
{
    int i;
    p->field_4 = &bgmSound_80091CE0;
    p->field_8 = &sfxSound_80091D20;
    p->field_C = &stru_80091D00;
    p->field_2 = 2;
    for (i = 4; i >= 0; i--)
    {
        p->e[i].a = 0;
    }
    *(void (**)(void))(a + 8) = sub_8002FF64;
}
typedef struct
{
    short active;
    short timer;
    short access_num;
    short seq;
} SeqFade_FF64;
typedef struct
{
    short field_0;
    unsigned short state_2;
    char pad_4[0xC];
    int request_10;
    int request_14;
    SeqFade_FF64 fades[5];
} SoundTask_FF64;
// Matched
void sub_8002FF64(int a0, SoundTask_FF64* p)
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
            if (p->fades[i].active)
            {
                if (--p->fades[i].timer <= 0)
                {
                    SsSepStop(p->fades[i].access_num, p->fades[i].seq);
                    p->fades[i].active = 0;
                }
            }
        }
        break;
    }
}
extern void StopSoundSeqs_80030D68(SoundStruct* p);
#if 0
// Not matched: register allocation of the sequence number
void sub_8003006C(int a0, int* a1)
{
    SoundStruct* s = &bgmSound_80091CE0;
    short seq = s->field_4_seq_num;
    if (seq >= 0)
    {
        SsSepStop(s->field_C_sep_access_num, seq);
        s->field_4_seq_num = -1;
    }
    FreeSound_80030D00(a1[1]);
    StopSoundSeqs_80030D68(&systemSound_80091D40);
    FreeSound_80030D00(a1[2]);
}
#endif
INCLUDE_ASM(sub_8003006C);

typedef struct
{
    short field_0;
    unsigned short state_2;
    SoundStruct* bgm_4;
    SoundStruct* bgm2_8;
    int pad_C;
    int request_10;
    int request_14;
} SoundTask_300E0;
typedef struct
{
    short field_0_file_id;
    short field_2_seq;
    short field_4;
    short field_6_sub_sound;
} SoundSeqInfo_300E0;
extern void PlaySoundSeq_8003105C(SoundStruct* s, int idx, short loops);
extern void sub_80031260(SoundStruct* s, int idx, short loops);
extern int QueueFileRequest_8003BC84(int* a);
void LoadSoundFromBuffer_800307B4(SoundStruct** req, GenkiSoundHeader* pSndFileHeader);
// Matched
int PlayMusic_800300E0(int idx, int a1)
{
    SoundTask_300E0* t = (SoundTask_300E0*)soundTask_8008D4A4[0x24 / 4];
    SoundStruct* s;
    int req[8];
    int sub;
    if (idx < 10)
    {
        PlaySoundSeq_8003105C(&systemSound_80091D40, idx, 1);
        return 1;
    }
    if (t->bgm_4->field_6_sound_idx == idx)
    {
        if (t->bgm_4->field_4_seq_num == ((SoundSeqInfo_300E0*)soundFiles_80082F0C)[idx].field_2_seq)
        {
            return 1;
        }
        SsSepStop(t->bgm_4->field_C_sep_access_num, t->bgm_4->field_4_seq_num);
        SsSepSetVol(t->bgm_4->field_C_sep_access_num, t->bgm_4->field_4_seq_num, 0, 0);
        t->bgm_4->field_4_seq_num = ((SoundSeqInfo_300E0*)soundFiles_80082F0C)[idx].field_2_seq;
        sub_80031260(t->bgm_4, idx, 1);
        return 1;
    }
    if (GetSoundFileId_80030D4C(t->bgm_4->field_6_sound_idx) == GetSoundFileId_80030D4C(idx))
    {
        SsSepStop(t->bgm_4->field_C_sep_access_num, t->bgm_4->field_4_seq_num);
        SsSepSetVol(t->bgm_4->field_C_sep_access_num, t->bgm_4->field_4_seq_num, 0, 0);
        t->bgm_4->field_4_seq_num = ((SoundSeqInfo_300E0*)soundFiles_80082F0C)[idx].field_2_seq;
        sub_80031260(t->bgm_4, idx, 1);
        return 1;
    }
    if (t->bgm2_8 && GetSoundFileId_80030D4C(t->bgm2_8->field_6_sound_idx) == GetSoundFileId_80030D4C(idx))
    {
        t->bgm2_8->field_4_seq_num = ((SoundSeqInfo_300E0*)soundFiles_80082F0C)[idx].field_2_seq;
        sub_80031260(t->bgm2_8, idx, 1);
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
        FreeSound_80030D00((int)t->bgm_4);
    }
    if (t->bgm2_8->field_6_sound_idx >= 0)
    {
        FreeSound_80030D00((int)t->bgm2_8);
    }
    t->bgm_4->field_6_sound_idx = idx;
    t->state_2 = 0;
    req[0] = 0x2C;
    req[1] = GetSoundFileId_80030D4C(t->bgm_4->field_6_sound_idx);
    req[5] = (int)&t->bgm_4;
    req[2] = 0;
    req[3] = 0;
    req[4] = 0;
    req[6] = 4;
    req[7] = (int)LoadSoundFromBuffer_800307B4;
    t->request_10 = QueueFileRequest_8003BC84(req);
    sub = ((SoundSeqInfo_300E0*)soundFiles_80082F0C)[idx].field_6_sub_sound;
    if (sub >= 0)
    {
        t->bgm2_8->field_6_sound_idx = sub;
        t->state_2 = 0;
        req[0] = 0x2C;
        req[1] = GetSoundFileId_80030D4C(t->bgm2_8->field_6_sound_idx);
        req[2] = 0;
        req[3] = 0;
        req[4] = 0;
        req[5] = (int)&t->bgm2_8;
        req[6] = 4;
        req[7] = (int)LoadSoundFromBuffer_800307B4;
        t->request_14 = QueueFileRequest_8003BC84(req);
    }
    return 1;
}
extern int QueueFileRequest_8003BC84(int* a);
void LoadSoundSeqFromBuffer_800304D0(SoundStruct** req, char* pSndFileBuffer);
// Matched
int sub_800303E8(void)
{
    unsigned short* p = soundTask_8008D4A4[0x24 / 4];
    int s[8];
    if (p[1] != 2)
    {
        return 0;
    }
    stru_80091D00 = systemSound_80091D40;
    stru_80091D00.field_8_sep_data_ptr = 0;
    stru_80091D00.field_6_sound_idx = 10;
    p[1] = 0;
    s[0] = 0x2C;
    s[1] = 0x301;
    s[5] = (int)(p + 6);
    s[6] = 4;
    s[2] = 0;
    s[3] = 0;
    s[4] = 0;
    s[7] = (int)LoadSoundSeqFromBuffer_800304D0;
    *(int*)(p + 8) = QueueFileRequest_8003BC84(s);
    return 1;
}
#if 0
// Not matched: the header copy of the buffer pointer gets the other saved register (param used everywhere, copy hoisted into a delay slot)
void LoadSoundSeqFromBuffer_800304D0(SoundStruct** req, char* pSndFileBuffer)
{
    GenkiSoundHeader* pSndFileHeader = (GenkiSoundHeader*)pSndFileBuffer;
    SoundStruct* sound = req[0];

    if (pSndFileHeader->field_14_sep_size)
    {
        sound->field_8_sep_data_ptr = (unsigned long*)malloc3_8003FC4C(pSndFileHeader->field_14_sep_size);
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
        sound->field_10_sep_data_ptr = (unsigned long*)malloc3_8003FC4C(pSndFileHeader->field_1C_sep_size);
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
#endif
INCLUDE_ASM(LoadSoundSeqFromBuffer_800304D0);
// Matched
void sub_80030664(void)
{
    FreeSoundSeqs_80030EEC(&stru_80091D00);
}
// Matched
int sub_80030688(void)
{
    return soundTask_8008D4A4[0x24 / 4][1] == 2;
}
// Matched
int sub_800306B0(void)
{
    return soundTask_8008D4A4[0x24 / 4][1] == 2;
}
// Matched
void sub_800306D8(void)
{
    FreeSoundSeqs_80030EEC(&bgmSound_80091CE0);
}
extern void StopSoundSeq_80031408(SoundStruct* s, int idx);
// Matched
void sub_800306FC(int idx)
{
    SoundStruct** p = (SoundStruct**)soundTask_8008D4A4[0x24 / 4];
    if (idx < 10)
    {
        StopSoundSeq_80031408(&systemSound_80091D40, idx);
        return;
    }
    if (GetSoundFileId_80030D4C(p[1]->field_6_sound_idx) == GetSoundFileId_80030D4C(idx))
    {
        StopSoundSeq_80031408(p[1], idx);
    }
    if (GetSoundFileId_80030D4C(p[2]->field_6_sound_idx) == GetSoundFileId_80030D4C(idx))
    {
        StopSoundSeq_80031408(p[2], idx);
    }
}
extern void sub_80031260(SoundStruct* s, int idx, short loops);
typedef struct
{
    short field_0_file_id;
    short field_2_seq;
    int field_4;
} SoundSeqInfo_307B4;
// Matched
void LoadSoundFromBuffer_800307B4(SoundStruct** req, GenkiSoundHeader* pSndFileHeader)
{
    SoundStruct* sound = req[0];

    sound->field_18_vab_header_ptr = (unsigned char*)malloc3_8003FC4C(pSndFileHeader->field_4_vab_header_size);

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
        sound->field_8_sep_data_ptr = (unsigned long*)malloc3_8003FC4C(pSndFileHeader->field_14_sep_size);
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

    if (sound->field_8_sep_data_ptr && ((SoundSeqInfo_307B4*)soundFiles_80082F0C)[sound->field_6_sound_idx].field_2_seq >= 0)
    {
        sub_80031260(sound, sound->field_6_sound_idx, 1);
    }
}
// Matched
void ApplyAudioOutputFormat_80030988(void)
{
    if (!((settingsFlags_8008B58C >> 6) & 1))
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
        int vol = (saveData_8008B570.field_1C_settings >> 7) & 0x7F;
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

    sound->field_18_vab_header_ptr = (unsigned char*)malloc3_8003FC4C(pSndFileHeader->field_4_vab_header_size);

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
        sound->field_8_sep_data_ptr = (unsigned long*)malloc3_8003FC4C(pSndFileHeader->field_14_sep_size);
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
        sound->field_10_sep_data_ptr = (unsigned long*)malloc3_8003FC4C(pSndFileHeader->field_1C_sep_size);
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
