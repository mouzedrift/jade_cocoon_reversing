#ifndef _TU_80030D00_H_
#define _TU_80030D00_H_

#include "sound.h"

extern const char aRendWings_8007447C[];
extern const char aBreakLegs_80074494[];
extern const char aCritical_800744AC[];
extern const char aAllEnemies_800744C0[];
extern const char aAbsorbMana_800744D8[];
extern const char aAbsorbHP_800744F0[];
extern const char aDestroyMana_80074504[];
extern const char aFleshToStone_80074520[];
extern const char aSleep_80074540[];
extern const char aPoison_8007454C[];
extern const char aWindAttack_8007455C[];
extern const char aFireAttack_80074574[];
extern const char aWaterAttack_8007458C[];
extern const char aEarthAttack_800745A8[];
extern const char aDashes4_800745C4[];
extern const char aPlusCritical_800745D0[];
extern const char aPlusAccuracy_800745E8[];
extern const char aPlusPower_80074600[];
extern const char aDashes3_80074610[];
extern const int dword_80074618;
extern const int dword_800746B8;

int GetSkillEffect_800316EC(unsigned int slot, int actorMask);
void PlaySeqSlot_80031160(unsigned int idx, short loops);
void PlaySfx_80031494(int id);
void FreeSoundSeqs_80030EEC(void* soundArg);
void SetBattleMusic_800315D8(int music);
int GetBattleMusic_800315E4(void);
void FadeOutSeqSlot_800313C8(int idx);
int ReturnZero_800316DC(void);
int ReturnZero_800316E4(void);
void FreeSound_80030D00(SoundStruct* sound);
void FreeBgmAndSfx_800315F4(void);
void FreeSoundVab_80030EA4(SoundStruct* sound);
void StopSoundSeqs_80030D68(SoundStruct* sound);
void StopSeqSlot_80031334(int idx);
void SfxKeyOff_80031574(short voice, short sfx);
short SfxKeyOn_800314F4(int sfx);
void FadeOutSfxSeq_80031638(void);
void PlayMusicSeq_80031260(SoundStruct* sound, int idx, short loops);
void PlaySoundSeq_8003105C(SoundStruct* sound, int idx, short loops);
void StopSoundSeq_80031408(SoundStruct* sound, int idx);
#endif
