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
void sub_80030D00(int a0)
{
    short* p = (short*)a0;
    if (p && p[3] >= 0)
    {
        sub_80030EEC(p);
        sub_80030EA4(p);
        p[3] = -1;
    }
}
// Matched
int GetSoundFileId_80030D4C(int idx)
{
  return soundFiles_80082F0C[idx].field_0_file_id;
}
INCLUDE_ASM(sub_80030D68);
// Matched
void sub_80030EA4(short* p)
{
    sub_8006AF08(p[0]);
    if (*(int*)(p + 0xC))
    {
        free3_8003FC6C(*(void**)(p + 0xC));
        *(int*)(p + 0xC) = 0;
    }
}
#if 0
void sub_80030EEC(void* arg0)
{
}
#endif
INCLUDE_ASM(sub_80030EEC);
INCLUDE_ASM(sub_8003105C);
INCLUDE_ASM(sub_80031160);
INCLUDE_ASM(sub_80031260);
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
void sub_80031408(SoundStruct* s, int idx)
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
short sub_800314F4(int a)
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
void sub_80031574(short a, short b)
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
    sub_80030D00(s0[1]);
    sub_80030D00(s0[2]);
}
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
