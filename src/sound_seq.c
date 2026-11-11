#include "common.h"
#include "funcs.h"
#include "sdk.h"
#include "globals.h"
#include "sound.h"
#include "soundtask.h"
#include "data_decls.h"
#include "sound_seq.h"
#include "skill_anim.h"
#include "util.h"
#include "effect.h"
#include "effect_cmd.h"

const char aRendWings_8007447C[24] = "\202q\202\205\202\216\202\204\201@\202v\202\211\202\216\202\207\202\223"; // Rend Wings
const char aBreakLegs_80074494[24] = "\202a\202\222\202\205\202\201\202\213\201@\202k\202\205\202\207\202\223"; // Break Legs
const char aCritical_800744AC[20] = "\202b\202\222\202\211\202\224\202\211\202\203\202\201\202\214"; // Critical
const char aAllEnemies_800744C0[24] = "\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223"; // All Enemies
const char aAbsorbMana_800744D8[24] = "\202`\202\202\202\223\202\217\202\222\202\202\201@\202l\202\201\202\216\202\201"; // Absorb Mana
const char aAbsorbHP_800744F0[20] = "\202`\202\202\202\223\202\217\202\222\202\202\201@\202g\202o"; // Absorb HP
const char aDestroyMana_80074504[28] = "\202c\202\205\202\223\202\224\202\222\202\217\202\231\201@\202l\202\201\202\216\202\201"; // Destroy Mana
const char aFleshToStone_80074520[32] = "\202e\202\214\202\205\202\223\202\210\201@\202\224\202\217\201@\202r\202\224\202\217\202\216\202\205"; // Flesh to Stone
const char aSleep_80074540[12] = "\202r\202\214\202\205\202\205\202\220"; // Sleep
const char aPoison_8007454C[16] = "\202o\202\217\202\211\202\223\202\217\202\216"; // Poison
const char aWindAttack_8007455C[24] = "\202v\202\211\202\216\202\204\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Wind Attack
const char aFireAttack_80074574[24] = "\202e\202\211\202\222\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Fire Attack
const char aWaterAttack_8007458C[28] = "\202v\202\201\202\224\202\205\202\222\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Water Attack
const char aEarthAttack_800745A8[28] = "\202d\202\201\202\222\202\224\202\210\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Earth Attack
const char aDashes4_800745C4[12] = "\201[\201[\201[\201["; // ーーーー
const char aPlusCritical_800745D0[24] = "\201{\201@\202b\202\222\202\211\202\224\202\211\202\203\202\201\202\214"; // + Critical
const char aPlusAccuracy_800745E8[24] = "\201{\201@\202`\202\203\202\203\202\225\202\222\202\201\202\203\202\231"; // + Accuracy
const char aPlusPower_80074600[16] = "\201{\201@\202o\202\217\202\227\202\205\202\222"; // + Power
const char aDashes3_80074610[8] = "\201[\201[\201["; // ーーー
const int unused_80074618 = 0;

void FreeSound_80030D00(SoundStruct* sound)
{
    if (sound && sound->soundIdx_6 >= 0)
    {
        FreeSoundSeqs_80030EEC(sound);
        FreeSoundVab_80030EA4(sound);
        sound->soundIdx_6 = -1;
    }
}
int GetSoundFileId_80030D4C(int idx)
{
  return soundFiles_80082F0C[idx].field_0_file_id;
}
void StopSoundSeqs_80030D68(SoundStruct* sound)
{
    int i;
    sound->seqNum_4 = -1;
    if (sound->sepDataPtr_8)
    {
        for (i = 0; i < soundFiles_80082F0C[sound->soundIdx_6].seqCount_4; i++)
        {
            SsSepStop(sound->sepAccessNum_C, i);
            SsSepSetVol(sound->sepAccessNum_C, i, 0, 0);
        }
    }
    if (sound->sepDataPtr_10)
    {
        for (i = 0; i < soundFiles_80082F0C[sound->soundIdx_6].seqCount_5; i++)
        {
            SsSepStop(sound->sepAccessNum_14, i);
            SsSepSetVol(sound->sepAccessNum_14, i, 0, 0);
        }
    }
}
void FreeSoundVab_80030EA4(SoundStruct* sound)
{
    SsVabClose(sound->vabId_0);
    if (sound->vabHeaderPtr_18)
    {
        free3_8003FC6C(sound->vabHeaderPtr_18);
        sound->vabHeaderPtr_18 = 0;
    }
}
void FreeSoundSeqs_80030EEC(void* soundArg)
{
    SoundStruct* sound = soundArg;
    int i;
    if (sound->sepDataPtr_8)
    {
        for (i = 0; i < soundFiles_80082F0C[sound->soundIdx_6].seqCount_4; i++)
        {
            SsSepStop(sound->sepAccessNum_C, (short)i);
            SsSepSetVol(sound->sepAccessNum_C, (short)i, 0, 0);
        }
        SsSepClose(sound->sepAccessNum_C);
        free3_8003FC6C(sound->sepDataPtr_8);
        sound->sepDataPtr_8 = 0;
    }
    if (sound->sepDataPtr_10)
    {
        for (i = 0; i < soundFiles_80082F0C[sound->soundIdx_6].seqCount_5; i++)
        {
            SsSepStop(sound->sepAccessNum_14, (short)i);
            SsSepSetVol(sound->sepAccessNum_14, (short)i, 0, 0);
        }
        SsSepClose(sound->sepAccessNum_14);
        free3_8003FC6C(sound->sepDataPtr_10);
        sound->sepDataPtr_10 = 0;
    }
}
void PlaySoundSeq_8003105C(SoundStruct* sound, int idx, short loops)
{
    int seq = soundFiles_80082F0C[idx].field_2_seq;
    int accessNum;
    int seqNum;
    if (seq >= 0x10)
    {
        accessNum = sound->sepAccessNum_14;
        seqNum = seq - 0x10;
    }
    else
    {
        seqNum = seq;
        accessNum = sound->sepAccessNum_C;
    }
    if (idx == 0)
    {
        SsSepSetVol(accessNum, seqNum, (saveData_8008B570.settings_1C.word >> 7) & 0x7F, (saveData_8008B570.settings_1C.word >> 7) & 0x7F);
    }
    else
    {
        SsSepSetVol(accessNum, seqNum, (saveData_8008B570.settings_1C.word >> 14) & 0x7F, (saveData_8008B570.settings_1C.word >> 14) & 0x7F);
    }
    SsSepPlay(accessNum, seqNum, 1, loops);
    SsSepSetCrescendo(accessNum, seqNum, 1, 1);
    sound->seqNum_4 = seqNum;
}
void PlaySeqSlot_80031160(unsigned int idx, short loops)
{
    SoundStruct* sound = &seqSlotSound_80091D00;
    int accessNum;
    int seqNum;
    if (seqSlots_800833E4[idx].sep_0 == 1)
    {
        accessNum = sound->sepAccessNum_14;
    }
    else
    {
        accessNum = sound->sepAccessNum_C;
    }
    seqNum = seqSlots_800833E4[idx].seq_4;
    if (idx < 2)
    {
        SsSepSetVol(accessNum, seqNum, (saveData_8008B570.settings_1C.word >> 7) & 0x7F, (saveData_8008B570.settings_1C.word >> 7) & 0x7F);
    }
    else
    {
        SsSepSetVol(accessNum, seqNum, (saveData_8008B570.settings_1C.word >> 14) & 0x7F, (saveData_8008B570.settings_1C.word >> 14) & 0x7F);
    }
    SsSepPlay(accessNum, seqNum, 1, loops);
    SsSepSetCrescendo(accessNum, seqNum, 1, 1);
}
void PlayMusicSeq_80031260(SoundStruct* sound, int idx, short loops)
{
    int seq = soundFiles_80082F0C[idx].field_2_seq;
    if (seq >= 0)
    {
        if (sound == &bgmSound_80091CE0)
        {
            SsSepSetVol(sound->sepAccessNum_C, seq, (saveData_8008B570.settings_1C.word >> 7) & 0x7F,
                        (saveData_8008B570.settings_1C.word >> 7) & 0x7F);
        }
        else
        {
            SsSepSetVol(sound->sepAccessNum_C, seq, (saveData_8008B570.settings_1C.word >> 14) & 0x7F,
                        (saveData_8008B570.settings_1C.word >> 14) & 0x7F);
        }
        SsSepPlay(sound->sepAccessNum_C, soundFiles_80082F0C[idx].field_2_seq, 1, loops);
        SsSepSetCrescendo(sound->sepAccessNum_C, soundFiles_80082F0C[idx].field_2_seq, 1, 1);
        sound->seqNum_4 = soundFiles_80082F0C[idx].field_2_seq;
    }
}
void StopSeqSlot_80031334(int idx)
{
    SoundStruct* sound = &seqSlotSound_80091D00;
    int accessNum;
    short seqNum;
    if (seqSlots_800833E4[idx].sep_0 == 1)
    {
        accessNum = sound->sepAccessNum_14;
    }
    else
    {
        accessNum = sound->sepAccessNum_C;
    }
    seqNum = seqSlots_800833E4[idx].seq_4;
    SsSepStop(accessNum, seqNum);
    SsSepSetVol(accessNum, seqNum, 0, 0);
}
void FadeOutSeqSlot_800313C8(int idx)
{
    SsSepSetDecrescendo(seqSlotSound_80091D00.sepAccessNum_C, seqSlots_800833E4[idx].seq_4, 0x7F, 0x78);
}
void StopSoundSeq_80031408(SoundStruct* sound, int idx)
{
    SoundInfo* files = soundFiles_80082F0C;
    SoundInfo* info = &files[idx];
    int seq = ((short*)info)[1];
    int accessNum;
    int seqNum;
    if (seq >= 0x10)
    {
        accessNum = sound->sepAccessNum_14;
        seqNum = seq - 0x10;
    }
    else
    {
        accessNum = sound->sepAccessNum_C;
        seqNum = seq;
    }
    SsSepStop(accessNum, seqNum);
    SsSepSetVol(accessNum, seqNum, 0, 0);
}
void PlaySfx_80031494(int id)
{
    if (id < 63)
    {
        SsVoKeyOn((sfxSound_80091D20.vabId_0 << 8) + id,
                  0x3C00u,
                  (saveData_8008B570.settings_1C.word >> 14) & 0x7F,
                  (saveData_8008B570.settings_1C.word >> 14) & 0x7F);
    }
    else
    {
        SsVoKeyOn((systemSound_80091D40.vabId_0 << 8) + id,
                  0x3C00u,
                  (saveData_8008B570.settings_1C.word >> 14) & 0x7F,
                  (saveData_8008B570.settings_1C.word >> 14) & 0x7F);
    }
}
short SfxKeyOn_800314F4(int sfx)
{
    SoundStruct* sound;
    if (sfx < 0x3f)
    {
        sound = &sfxSound_80091D20;
    }
    else
    {
        sound = &systemSound_80091D40;
    }
    return SsUtKeyOn(*(short*)sound, sfx, 0, 0x3c, 0, (saveData_8008B570.settings_1C.word >> 14) & 0x7F, (saveData_8008B570.settings_1C.word >> 14) & 0x7F);
}
void SfxKeyOff_80031574(short voice, short sfx)
{
    SoundStruct* sound;
    if (sfx < 0x3f)
    {
        sound = &sfxSound_80091D20;
    }
    else
    {
        sound = &systemSound_80091D40;
    }
    SsUtKeyOff(voice, *(short*)sound, sfx, 0, 0x3c);
}
void SetBattleMusic_800315D8(int music)
{
    battleMusic_80091CFC = music;
}
int GetBattleMusic_800315E4(void)
{
    return battleMusic_80091CFC;
}
void FreeBgmAndSfx_800315F4(void)
{
    SoundTask* task = soundTask_8008D4A4->entry.buffer;
    FreeSound_80030D00(task->bgm_4);
    FreeSound_80030D00(task->sfx_8);
}
void FadeOutSfxSeq_80031638(void)
{
    SoundTask* task;
    int i;
    task = soundTask_8008D4A4->entry.buffer;
    if (sfxSound_80091D20.seqNum_4 >= 0)
    {
        for (i = 0; i < 5; i++)
        {
            if (task->fades_18[i].active == 0)
            {
                task->fades_18[i].active = 1;
                SsSepSetDecrescendo(sfxSound_80091D20.sepAccessNum_C, sfxSound_80091D20.seqNum_4, 0x7F, 0x40);
                task->fades_18[i].access_num = sfxSound_80091D20.sepAccessNum_C;
                task->fades_18[i].seq = sfxSound_80091D20.seqNum_4;
                task->fades_18[i].timer = 0x20;
                return;
            }
        }
    }
}
int ReturnZero_800316DC(void)
{
    return 0;
}
int ReturnZero_800316E4(void)
{
    return 0;
}
extern UnitSkill* GetUnitSkills_80031B30(int a0);
int GetSkillEffect_800316EC(unsigned int slot, int actorMask)
{
    int effect;
    int abilityId;
    UnitSkill* skill;
    effect = SkillSlotToAnimIndex_80031870(slot) + 0x26;
    skill = GetUnitSkills_80031B30(LowestSetBit_80014358(actorMask) & 0xFF);
    skill += slot;
    abilityId = skill->id_1;
    SetHitVariant_80018430(-1);
    if (slot >= 4)
    {
        effect = 0x1E;
    }
    switch (abilityId)
    {
    case 2:
        SetHitVariant_80018430(2);
        break;
    case 3:
        SetHitVariant_80018430(3);
        break;
    case 4:
        SetHitVariant_80018430(0);
        break;
    case 5:
    case 23:
    case 25:
    case 29:
        SetHitVariant_80018430(1);
        break;
    case 6:
    case 20:
        SetHitVariant_80018430(4);
        break;
    case 7:
    case 22:
        SetHitVariant_80018430(5);
        break;
    case 9:
        SetHitVariant_80018430(10);
        break;
    case 10:
        SetHitVariant_80018430(8);
        break;
    case 11:
    case 19:
        SetHitVariant_80018430(9);
        break;
    case 16:
        effect = 0x26;
    case 8:
        SetHitVariant_80018430(6);
        break;
    case 17:
        effect = 0x3C;
        break;
    case 18:
        effect = 0x3B;
        break;
    case 21:
        effect = 0x1E;
        break;
    case 24:
        effect = 0x22;
        break;
    case 38:
        effect = 0x34;
        break;
    case 34:
    case 35:
    case 36:
    case 37:
        effect = abilityId + 0x1D;
        SetHitVariant_80018430(abilityId - 0x22);
        break;
    case 33:
        effect = 0x19;
        break;
    case 28:
        effect = -1;
        break;
    case 0:
    case 1:
        break;
    }
    return effect;
}
const int unused_800746B8 = 0;
