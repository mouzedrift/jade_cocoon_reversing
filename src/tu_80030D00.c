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

INCLUDE_DATA(dword_8007447C);
INCLUDE_DATA(dword_80074494);
INCLUDE_DATA(dword_800744AC);
INCLUDE_DATA(dword_800744C0);
INCLUDE_DATA(dword_80074520);
INCLUDE_DATA(dword_80074540);
INCLUDE_DATA(dword_8007455C);
INCLUDE_DATA(dword_800745A8);
INCLUDE_DATA(dword_800745C4);
INCLUDE_DATA(dword_800745D0);
INCLUDE_DATA(dword_800745E8);
INCLUDE_DATA(dword_80074600);
INCLUDE_DATA(dword_80074610);

// Matched
void FreeSound_80030D00(int a0)
{
    short* p = (short*)a0;
    if (p && p[3] >= 0)
    {
        FreeSoundSeqs_80030EEC(p);
        FreeSoundVab_80030EA4(p);
        p[3] = -1;
    }
}
// Matched
int GetSoundFileId_80030D4C(int idx)
{
  return soundFiles_80082F0C[idx].field_0_file_id;
}
// Matched
void StopSoundSeqs_80030D68(SoundStruct* s)
{
    int i;
    s->field_4_seq_num = -1;
    if (s->field_8_sep_data_ptr)
    {
        for (i = 0; i < soundFiles_80082F0C[s->field_6_sound_idx].field_4_seq_count; i++)
        {
            SsSepStop(s->field_C_sep_access_num, i);
            SsSepSetVol(s->field_C_sep_access_num, i, 0, 0);
        }
    }
    if (s->field_10_sep_data_ptr)
    {
        for (i = 0; i < soundFiles_80082F0C[s->field_6_sound_idx].field_5_seq_count; i++)
        {
            SsSepStop(s->field_14_sep_access_num, i);
            SsSepSetVol(s->field_14_sep_access_num, i, 0, 0);
        }
    }
}
// Matched
void FreeSoundVab_80030EA4(short* p)
{
    SsVabClose(p[0]);
    if (*(int*)(p + 0xC))
    {
        free3_8003FC6C(*(void**)(p + 0xC));
        *(int*)(p + 0xC) = 0;
    }
}
// Matched
void FreeSoundSeqs_80030EEC(void* arg0)
{
    SoundStruct* s = arg0;
    int i;
    if (s->field_8_sep_data_ptr)
    {
        for (i = 0; i < soundFiles_80082F0C[s->field_6_sound_idx].field_4_seq_count; i++)
        {
            SsSepStop(s->field_C_sep_access_num, (short)i);
            SsSepSetVol(s->field_C_sep_access_num, (short)i, 0, 0);
        }
        SsSepClose(s->field_C_sep_access_num);
        free3_8003FC6C(s->field_8_sep_data_ptr);
        s->field_8_sep_data_ptr = 0;
    }
    if (s->field_10_sep_data_ptr)
    {
        for (i = 0; i < soundFiles_80082F0C[s->field_6_sound_idx].field_5_seq_count; i++)
        {
            SsSepStop(s->field_14_sep_access_num, (short)i);
            SsSepSetVol(s->field_14_sep_access_num, (short)i, 0, 0);
        }
        SsSepClose(s->field_14_sep_access_num);
        free3_8003FC6C(s->field_10_sep_data_ptr);
        s->field_10_sep_data_ptr = 0;
    }
}
typedef struct
{
    short field_0_file_id;
    short field_2_seq;
    int field_4;
} SoundSeqInfo;
// Matched
void PlaySoundSeq_8003105C(SoundStruct* s, int idx, short loops)
{
    int v = ((SoundSeqInfo*)soundFiles_80082F0C)[idx].field_2_seq;
    int a;
    int b;
    if (v >= 0x10)
    {
        a = s->field_14_sep_access_num;
        b = v - 0x10;
    }
    else
    {
        b = v;
        a = s->field_C_sep_access_num;
    }
    if (idx == 0)
    {
        SsSepSetVol(a, b, (settingsFlags_8008B58C >> 7) & 0x7F, (settingsFlags_8008B58C >> 7) & 0x7F);
    }
    else
    {
        SsSepSetVol(a, b, (settingsFlags_8008B58C >> 14) & 0x7F, (settingsFlags_8008B58C >> 14) & 0x7F);
    }
    SsSepPlay(a, b, 1, loops);
    SsSepSetCrescendo(a, b, 1, 1);
    s->field_4_seq_num = b;
}
// Matched
void PlaySeqSlot_80031160(unsigned int idx, short loops)
{
    SoundStruct* s = &stru_80091D00;
    int a;
    int b;
    if (seqSlots_800833E4[idx].field_0 == 1)
    {
        a = s->field_14_sep_access_num;
    }
    else
    {
        a = s->field_C_sep_access_num;
    }
    b = seqSlots_800833E4[idx].field_4;
    if (idx < 2)
    {
        SsSepSetVol(a, b, (settingsFlags_8008B58C >> 7) & 0x7F, (settingsFlags_8008B58C >> 7) & 0x7F);
    }
    else
    {
        SsSepSetVol(a, b, (settingsFlags_8008B58C >> 14) & 0x7F, (settingsFlags_8008B58C >> 14) & 0x7F);
    }
    SsSepPlay(a, b, 1, loops);
    SsSepSetCrescendo(a, b, 1, 1);
}
// Matched
void PlayMusicSeq_80031260(SoundStruct* s, int idx, short loops)
{
    int seq = ((SoundSeqInfo*)soundFiles_80082F0C)[idx].field_2_seq;
    if (seq >= 0)
    {
        if (s == &bgmSound_80091CE0)
        {
            SsSepSetVol(s->field_C_sep_access_num, seq, (settingsFlags_8008B58C >> 7) & 0x7F,
                        (settingsFlags_8008B58C >> 7) & 0x7F);
        }
        else
        {
            SsSepSetVol(s->field_C_sep_access_num, seq, (settingsFlags_8008B58C >> 14) & 0x7F,
                        (settingsFlags_8008B58C >> 14) & 0x7F);
        }
        SsSepPlay(s->field_C_sep_access_num, ((SoundSeqInfo*)soundFiles_80082F0C)[idx].field_2_seq, 1, loops);
        SsSepSetCrescendo(s->field_C_sep_access_num, ((SoundSeqInfo*)soundFiles_80082F0C)[idx].field_2_seq, 1, 1);
        s->field_4_seq_num = ((SoundSeqInfo*)soundFiles_80082F0C)[idx].field_2_seq;
    }
}
// Matched
void StopSeqSlot_80031334(int idx)
{
    SoundStruct* s = &stru_80091D00;
    int a;
    short b;
    if (seqSlots_800833E4[idx].field_0 == 1)
    {
        a = s->field_14_sep_access_num;
    }
    else
    {
        a = s->field_C_sep_access_num;
    }
    b = seqSlots_800833E4[idx].field_4;
    SsSepStop(a, b);
    SsSepSetVol(a, b, 0, 0);
}
// Matched
void FadeOutSeqSlot_800313C8(int idx)
{
    SsSepSetDecrescendo(word_80091D0C, seqSlots_800833E4[idx].field_4, 0x7F, 0x78);
}
// Matched
void StopSoundSeq_80031408(SoundStruct* s, int idx)
{
    SoundInfo* t = soundFiles_80082F0C;
    SoundInfo* si = &t[idx];
    int v = ((short*)si)[1];
    int a;
    int b;
    if (v >= 0x10)
    {
        a = s->field_14_sep_access_num;
        b = v - 0x10;
    }
    else
    {
        a = s->field_C_sep_access_num;
        b = v;
    }
    SsSepStop(a, b);
    SsSepSetVol(a, b, 0, 0);
}
// Matched
void PlaySfx_80031494(int a1)
{
    if (a1 < 63)
    {
        SsVoKeyOn((sfxSound_80091D20.field_0_vab_id << 8) + a1,
                  0x3C00u,
                  (settingsFlags_8008B58C >> 14) & 0x7F,
                  (settingsFlags_8008B58C >> 14) & 0x7F);
    }
    else
    {
        SsVoKeyOn((systemSound_80091D40.field_0_vab_id << 8) + a1,
                  0x3C00u,
                  (settingsFlags_8008B58C >> 14) & 0x7F,
                  (settingsFlags_8008B58C >> 14) & 0x7F);
    }
}
// Matched
short SfxKeyOn_800314F4(int a)
{
    SoundStruct* s;
    if (a < 0x3f)
    {
        s = &sfxSound_80091D20;
    }
    else
    {
        s = &systemSound_80091D40;
    }
    return SsUtKeyOn(*(short*)s, a, 0, 0x3c, 0, (saveData_8008B570.field_1C_settings >> 14) & 0x7F, (saveData_8008B570.field_1C_settings >> 14) & 0x7F);
}
// Matched
void SfxKeyOff_80031574(short a, short b)
{
    SoundStruct* s;
    if (b < 0x3f)
    {
        s = &sfxSound_80091D20;
    }
    else
    {
        s = &systemSound_80091D40;
    }
    SsUtKeyOff(a, *(short*)s, b, 0, 0x3c);
}
// Matched
void sub_800315D8(int a0)
{
    dword_80091CFC = a0;
}
// Matched
int sub_800315E4(void)
{
    return dword_80091CFC;
}
// Matched
void FreeBgmAndSfx_800315F4(void)
{
    int* s0 = ((int**)soundTask_8008D4A4)[0x24 / 4];
    FreeSound_80030D00(s0[1]);
    FreeSound_80030D00(s0[2]);
}
typedef struct
{
    short active;
    short timer;
    short access_num;
    short seq;
} SeqFade_31638;
typedef struct
{
    char pad_0[0x18];
    SeqFade_31638 fades[5];
} SeqFadeTask_31638;
// Matched
void FadeOutSfxSeq_80031638(void)
{
    SeqFadeTask_31638* t;
    int i;
    t = (SeqFadeTask_31638*)soundTask_8008D4A4[0x24 / 4];
    if (sfxSound_80091D20.field_4_seq_num >= 0)
    {
        for (i = 0; i < 5; i++)
        {
            if (t->fades[i].active == 0)
            {
                t->fades[i].active = 1;
                SsSepSetDecrescendo(sfxSound_80091D20.field_C_sep_access_num, sfxSound_80091D20.field_4_seq_num, 0x7F, 0x40);
                t->fades[i].access_num = sfxSound_80091D20.field_C_sep_access_num;
                t->fades[i].seq = sfxSound_80091D20.field_4_seq_num;
                t->fades[i].timer = 0x20;
                return;
            }
        }
    }
}
// Matched
int sub_800316DC(void)
{
    return 0;
}
// Matched
int sub_800316E4(void)
{
    return 0;
}
extern int sub_80031870(int a0);
typedef struct
{
    unsigned char a;
    unsigned char type;
    unsigned char b;
    unsigned char c;
} Ent4_316EC;
extern Ent4_316EC* sub_80031B30(int a0);
extern void sub_80018430(short v);
// Matched
int sub_800316EC(unsigned int a0, int a1)
{
    int r;
    int k;
    Ent4_316EC* base;
    r = sub_80031870(a0) + 0x26;
    base = sub_80031B30(LowestSetBit_80014358(a1) & 0xFF);
    base += a0;
    k = base->type;
    sub_80018430(-1);
    if (a0 >= 4)
    {
        r = 0x1E;
    }
    switch (k)
    {
    case 2:
        sub_80018430(2);
        break;
    case 3:
        sub_80018430(3);
        break;
    case 4:
        sub_80018430(0);
        break;
    case 5:
    case 23:
    case 25:
    case 29:
        sub_80018430(1);
        break;
    case 6:
    case 20:
        sub_80018430(4);
        break;
    case 7:
    case 22:
        sub_80018430(5);
        break;
    case 9:
        sub_80018430(10);
        break;
    case 10:
        sub_80018430(8);
        break;
    case 11:
    case 19:
        sub_80018430(9);
        break;
    case 16:
        r = 0x26;
    case 8:
        sub_80018430(6);
        break;
    case 17:
        r = 0x3C;
        break;
    case 18:
        r = 0x3B;
        break;
    case 21:
        r = 0x1E;
        break;
    case 24:
        r = 0x22;
        break;
    case 38:
        r = 0x34;
        break;
    case 34:
    case 35:
    case 36:
    case 37:
        r = k + 0x1D;
        sub_80018430(k - 0x22);
        break;
    case 33:
        r = 0x19;
        break;
    case 28:
        r = -1;
        break;
    case 0:
    case 1:
        break;
    }
    return r;
}
INCLUDE_DATA(dword_800746B8);
