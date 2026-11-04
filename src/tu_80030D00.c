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
#include "tu_80030D00.h"

const char aRendWings_8007447C[] = "\202q\202\205\202\216\202\204\201@\202v\202\211\202\216\202\207\202\223"; // Rend Wings
const char aBreakLegs_80074494[] = "\202a\202\222\202\205\202\201\202\213\201@\202k\202\205\202\207\202\223"; // Break Legs
const char aCritical_800744AC[] = "\202b\202\222\202\211\202\224\202\211\202\203\202\201\202\214"; // Critical
const char aAllEnemies_800744C0[] = "\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223"; // All Enemies
const char aAbsorbMana_800744D8[] = "\202`\202\202\202\223\202\217\202\222\202\202\201@\202l\202\201\202\216\202\201"; // Absorb Mana
const char aAbsorbHP_800744F0[] = "\202`\202\202\202\223\202\217\202\222\202\202\201@\202g\202o"; // Absorb HP
const char aDestroyMana_80074504[] = "\202c\202\205\202\223\202\224\202\222\202\217\202\231\201@\202l\202\201\202\216\202\201"; // Destroy Mana
const char aFleshToStone_80074520[] = "\202e\202\214\202\205\202\223\202\210\201@\202\224\202\217\201@\202r\202\224\202\217\202\216\202\205"; // Flesh to Stone
const char aSleep_80074540[] = "\202r\202\214\202\205\202\205\202\220"; // Sleep
const char aPoison_8007454C[] = "\202o\202\217\202\211\202\223\202\217\202\216"; // Poison
const char aWindAttack_8007455C[] = "\202v\202\211\202\216\202\204\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Wind Attack
const char aFireAttack_80074574[] = "\202e\202\211\202\222\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Fire Attack
const char aWaterAttack_8007458C[] = "\202v\202\201\202\224\202\205\202\222\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Water Attack
const char aEarthAttack_800745A8[] = "\202d\202\201\202\222\202\224\202\210\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Earth Attack
const char aDashes4_800745C4[] = "\201[\201[\201[\201["; // ーーーー
const char aPlusCritical_800745D0[] = "\201{\201@\202b\202\222\202\211\202\224\202\211\202\203\202\201\202\214"; // + Critical
const char aPlusAccuracy_800745E8[] = "\201{\201@\202`\202\203\202\203\202\225\202\222\202\201\202\203\202\231"; // + Accuracy
const char aPlusPower_80074600[] = "\201{\201@\202o\202\217\202\227\202\205\202\222"; // + Power
const char aDashes3_80074610[] = "\201[\201[\201["; // ーーー
const int dword_80074618 = 0;

// Matched
void FreeSound_80030D00(SoundStruct* p)
{
    if (p && p->field_6_sound_idx >= 0)
    {
        FreeSoundSeqs_80030EEC(p);
        FreeSoundVab_80030EA4(p);
        p->field_6_sound_idx = -1;
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
void FreeSoundVab_80030EA4(SoundStruct* p)
{
    SsVabClose(p->field_0_vab_id);
    if (p->field_18_vab_header_ptr)
    {
        free3_8003FC6C(p->field_18_vab_header_ptr);
        p->field_18_vab_header_ptr = 0;
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
// Matched
void PlaySoundSeq_8003105C(SoundStruct* s, int idx, short loops)
{
    int v = soundFiles_80082F0C[idx].field_2_seq;
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
        SsSepSetVol(a, b, (settingsFlags_8008B58C.word >> 7) & 0x7F, (settingsFlags_8008B58C.word >> 7) & 0x7F);
    }
    else
    {
        SsSepSetVol(a, b, (settingsFlags_8008B58C.word >> 14) & 0x7F, (settingsFlags_8008B58C.word >> 14) & 0x7F);
    }
    SsSepPlay(a, b, 1, loops);
    SsSepSetCrescendo(a, b, 1, 1);
    s->field_4_seq_num = b;
}
// Matched
void PlaySeqSlot_80031160(unsigned int idx, short loops)
{
    SoundStruct* s = &seqSlotSound_80091D00;
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
        SsSepSetVol(a, b, (settingsFlags_8008B58C.word >> 7) & 0x7F, (settingsFlags_8008B58C.word >> 7) & 0x7F);
    }
    else
    {
        SsSepSetVol(a, b, (settingsFlags_8008B58C.word >> 14) & 0x7F, (settingsFlags_8008B58C.word >> 14) & 0x7F);
    }
    SsSepPlay(a, b, 1, loops);
    SsSepSetCrescendo(a, b, 1, 1);
}
// Matched
void PlayMusicSeq_80031260(SoundStruct* s, int idx, short loops)
{
    int seq = soundFiles_80082F0C[idx].field_2_seq;
    if (seq >= 0)
    {
        if (s == &bgmSound_80091CE0)
        {
            SsSepSetVol(s->field_C_sep_access_num, seq, (settingsFlags_8008B58C.word >> 7) & 0x7F,
                        (settingsFlags_8008B58C.word >> 7) & 0x7F);
        }
        else
        {
            SsSepSetVol(s->field_C_sep_access_num, seq, (settingsFlags_8008B58C.word >> 14) & 0x7F,
                        (settingsFlags_8008B58C.word >> 14) & 0x7F);
        }
        SsSepPlay(s->field_C_sep_access_num, soundFiles_80082F0C[idx].field_2_seq, 1, loops);
        SsSepSetCrescendo(s->field_C_sep_access_num, soundFiles_80082F0C[idx].field_2_seq, 1, 1);
        s->field_4_seq_num = soundFiles_80082F0C[idx].field_2_seq;
    }
}
// Matched
void StopSeqSlot_80031334(int idx)
{
    SoundStruct* s = &seqSlotSound_80091D00;
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
    SsSepSetDecrescendo(seqSlotSepAccessNum_80091D0C, seqSlots_800833E4[idx].field_4, 0x7F, 0x78);
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
                  (settingsFlags_8008B58C.word >> 14) & 0x7F,
                  (settingsFlags_8008B58C.word >> 14) & 0x7F);
    }
    else
    {
        SsVoKeyOn((systemSound_80091D40.field_0_vab_id << 8) + a1,
                  0x3C00u,
                  (settingsFlags_8008B58C.word >> 14) & 0x7F,
                  (settingsFlags_8008B58C.word >> 14) & 0x7F);
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
    return SsUtKeyOn(*(short*)s, a, 0, 0x3c, 0, (saveData_8008B570.settings_1C.word >> 14) & 0x7F, (saveData_8008B570.settings_1C.word >> 14) & 0x7F);
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
void SetBattleMusic_800315D8(int music)
{
    battleMusic_80091CFC = music;
}
// Matched
int GetBattleMusic_800315E4(void)
{
    return battleMusic_80091CFC;
}
// Matched
void FreeBgmAndSfx_800315F4(void)
{
    SoundTask* s0 = soundTask_8008D4A4->entry.buffer;
    FreeSound_80030D00(s0->bgm_4);
    FreeSound_80030D00(s0->sfx_8);
}
// Matched
void FadeOutSfxSeq_80031638(void)
{
    SoundTask* t;
    int i;
    t = soundTask_8008D4A4->entry.buffer;
    if (sfxSound_80091D20.field_4_seq_num >= 0)
    {
        for (i = 0; i < 5; i++)
        {
            if (t->fades_18[i].active == 0)
            {
                t->fades_18[i].active = 1;
                SsSepSetDecrescendo(sfxSound_80091D20.field_C_sep_access_num, sfxSound_80091D20.field_4_seq_num, 0x7F, 0x40);
                t->fades_18[i].access_num = sfxSound_80091D20.field_C_sep_access_num;
                t->fades_18[i].seq = sfxSound_80091D20.field_4_seq_num;
                t->fades_18[i].timer = 0x20;
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
extern int SkillSlotToAnimIndex_80031870(int a0);
extern UnitSkill* GetUnitSkills_80031B30(int a0);
extern void sub_80018430(short v);
// Matched
int GetSkillEffect_800316EC(unsigned int slot, int actorMask)
{
    int r;
    int abilityId;
    UnitSkill* skill;
    r = SkillSlotToAnimIndex_80031870(slot) + 0x26;
    skill = GetUnitSkills_80031B30(LowestSetBit_80014358(actorMask) & 0xFF);
    skill += slot;
    abilityId = skill->id_1;
    sub_80018430(-1);
    if (slot >= 4)
    {
        r = 0x1E;
    }
    switch (abilityId)
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
        r = abilityId + 0x1D;
        sub_80018430(abilityId - 0x22);
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
const int dword_800746B8 = 0;
