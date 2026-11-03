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
    sub_8006AF08(p[0]);
    if (*(int*)(p + 0xC))
    {
        free3_8003FC6C(*(void**)(p + 0xC));
        *(int*)(p + 0xC) = 0;
    }
}
#if 0
void FreeSoundSeqs_80030EEC(void* arg0)
{
}
#endif
INCLUDE_ASM(FreeSoundSeqs_80030EEC);
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
void sub_80031160(unsigned int idx, short loops)
{
    SoundStruct* s = &stru_80091D00;
    int a;
    int b;
    if (dword_800833E4[idx].field_0 == 1)
    {
        a = s->field_14_sep_access_num;
    }
    else
    {
        a = s->field_C_sep_access_num;
    }
    b = dword_800833E4[idx].field_4;
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
void sub_80031260(SoundStruct* s, int idx, short loops)
{
    int seq = ((SoundSeqInfo*)soundFiles_80082F0C)[idx].field_2_seq;
    if (seq >= 0)
    {
        if (s == &stru_80091CE0)
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
void sub_80031334(int idx)
{
    SoundStruct* s = &stru_80091D00;
    int a;
    short b;
    if (dword_800833E4[idx].field_0 == 1)
    {
        a = s->field_14_sep_access_num;
    }
    else
    {
        a = s->field_C_sep_access_num;
    }
    b = dword_800833E4[idx].field_4;
    SsSepStop(a, b);
    SsSepSetVol(a, b, 0, 0);
}
// Matched
void sub_800313C8(int idx)
{
    SsSepSetDecrescendo(word_80091D0C, dword_800833E4[idx].field_4, 0x7F, 0x78);
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
        SsVoKeyOn((stru_80091D20.field_0_vab_id << 8) + a1,
                  0x3C00u,
                  (settingsFlags_8008B58C >> 14) & 0x7F,
                  (settingsFlags_8008B58C >> 14) & 0x7F);
    }
    else
    {
        SsVoKeyOn((stru_80091D40.field_0_vab_id << 8) + a1,
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
        s = &stru_80091D20;
    }
    else
    {
        s = &stru_80091D40;
    }
    return SsUtKeyOn(*(short*)s, a, 0, 0x3c, 0, (saveData_8008B570.field_1C_settings >> 14) & 0x7F, (saveData_8008B570.field_1C_settings >> 14) & 0x7F);
}
// Matched
void SfxKeyOff_80031574(short a, short b)
{
    SoundStruct* s;
    if (b < 0x3f)
    {
        s = &stru_80091D20;
    }
    else
    {
        s = &stru_80091D40;
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
void sub_800315F4(void)
{
    int* s0 = ((int**)dword_8008D4A4)[0x24 / 4];
    FreeSound_80030D00(s0[1]);
    FreeSound_80030D00(s0[2]);
}
#if 0
// Not matched (loop pointer gets strength-reduced with folded offsets)
void sub_80031638(void)
{
    char* q;
    int i;
    q = (char*)dword_8008D4A4[0x24 / 4];
    if (stru_80091D20.field_4_seq_num >= 0)
    {
        i = 0;
        do
        {
            i++;
            if (*(short*)(q + 0x18) == 0)
            {
                *(short*)(q + 0x18) = 1;
                SsSepSetDecrescendo(stru_80091D20.field_C_sep_access_num, stru_80091D20.field_4_seq_num, 0x7F, 0x40);
                *(short*)(q + 0x1C) = stru_80091D20.field_C_sep_access_num;
                *(short*)(q + 0x1A) = 0x20;
                *(short*)(q + 0x1E) = stru_80091D20.field_4_seq_num;
                break;
            }
            q += 8;
        } while (i < 5);
    }
}
#endif
INCLUDE_ASM(sub_80031638);
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
INCLUDE_ASM(sub_800316EC);
