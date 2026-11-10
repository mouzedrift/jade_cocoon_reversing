#ifndef TU_80010B90_H
#define TU_80010B90_H

#include "event.h" // EventDesc
#include "party.h" // ModelTaskState

/* the buffer of sporeTask_8008D464 (made by the game overlay): Sleep Spores (item 0x29) set mode 0, Attract Spores (0x2A) mode 1, for 1000 frames; the field AI reads it (GetSporeMode_80011B6C) */
typedef struct
{
    int mode_0;
    int timer_4;
} SporeTaskBuf;

extern const char msgAsleep_80071B78[];
extern const char msgParalyzed_80071B88[];
extern const char msgPoisonDamage_80071B98[];
extern const char msgCannotChooseCommand_80071BA8[];
extern const char msgCouldNotEscape_80071BC4[];
extern const char msgEscapedBattle_80071BD8[];
extern const char msgCannotUseItemNow_80071BEC[];
extern const char msgSealFailed_80071C08[];
extern const char msgSealSucceeded_80071C1C[];
extern const char msgCannotSealMore_80071C30[];
extern const char msgNoEmptyCocoon_80071C48[];
extern const char msgMinionIsDead_80071C5C[];
extern const char msgNoMinionEquipped_80071C74[];
extern const char msgCannotUseInBattle_80071C8C[];
extern const char msgNoElementMinion_80071CA0[];
extern const char msgNotEnoughMp_80071CC0[];
extern const char msgMagicSealed_80071CD4[];
extern const char msgSwapWhichMinion_80071CEC[];
extern const char msgWhichSpecialAttack_80071D08[];
extern const char msgSealWhichMinion_80071D24[];
extern const char msgWhichItem_80071D40[];
extern const char msgSummonWhichMinion_80071D5C[];
extern const char msgWhichMagic_80071D78[];
extern const char msgSpecialAttackWhom_80071D90[];
extern const char msgUseItemOnWhom_80071DAC[];
extern const char msgCastMagicOnWhom_80071DC8[];
extern const char msgAttackWhom_80071DE0[];
extern const char helpSwapMinion_80071DF4[];
extern const char helpSpecialAttack_80071E08[];
extern const char helpBackToCocoonMaster_80071E1C[];
extern const char helpNormalAttack_80071E2C[];
extern const char helpSealInCocoon_80071E44[];
extern const char helpSummonMinion_80071E58[];
extern const char helpUseMagic_80071E68[];
extern const char helpWeaponAttack_80071E80[];
extern const char helpChangeEquipment_80071E9C[];
extern const char helpEscape_80071EAC[];
extern const char helpUseItem_80071EC0[];
extern const char helpDefend_80071ED0[];
extern const char helpAttackMenu_80071EF0[];
extern const char helpEmpty_80071F00[];
extern const int unused_80071F04;

// the event lists of the game's tasks (CreateEventList_800435B4)
extern EventDesc eventDescs_80078EB8[];

extern int unused_80078E90[10];

typedef struct
{
    int f0;
    short x;
    short y;
    short z;
    short pad;
} Vtx12;

typedef struct
{
    char* pos[3];
    char* rot[3];
    Vtx12* src[3];
    int w[3];
} VtxBlend;

void LoadMenuStart_800B7650(); /* an EventEntry callback */

int BaseMaxMpForLevel_80012178(int level, void* unused);
int BaseMaxHpForLevel_80012140(int level, void* unused);
unsigned int GetCapturedMinionsCount_800125B8(void);
int GetSporeMode_80011B6C(void);
int ApplyLevelUpsBonus_80011D78(UnitStatus* status);
void ApplyLevelUpsPlain_80012188(UnitStatus* status);
void FillHpMp_80011C0C(UnitStatus* dst, UnitStatus* src);
void ClearStatus_80011C30(UnitStatus* status);
void RecoverQuarterHpMp_80011C44(UnitStatus* status);
void Heal_80011CD0(UnitStatus* status);
void ReviveOneHp_80011CF4(UnitStatus* status);
void HaltEventsAndFade_80011B8C(void);
void HaltEventsFadeStopMovie_80011BCC(void);
void EmptyCallback_80011C04(void);
void UseSporeItem_80011B24(int item);
void AdjustUnitStat_80012614(UnitStatus* status, int sel, int delta, int mask);
int CombinedExpDelta_80012204(int levelA, int expA, int levelB, int expB);
double PackedExpToTotal_80012358(int level, int exp);
int TotalExpToPacked_8001247C(double x);
int ModelTaskLoad_80010B90(ModelTaskState* task);
int ModelTaskWaitLoad_80010C30(ModelTaskState* task);
int ModelTaskApplyTextures_80010CDC(ModelTaskState* task);
int ModelTaskDraw_80010DB0(ModelTaskState* task);
void InitSporeTask_80011ADC(EventEntry* entry, int* spore);
void AccumulateExpGain_800122A0(int unit, int exp, int* acc);
int GetLevelRank_800121A8(int level);
int ApplyLevelUps_80011D98(UnitStatus* status, int mode);
void BlendVertices_80011904(VtxBlend* blend, Vtx12* out);
void UpdateSporeTask_80011AF8(EventEntry* entry, int* spore);
int GetGrowthKind_80011D28(int base);
#endif
