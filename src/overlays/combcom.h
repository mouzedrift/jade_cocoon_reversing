// COMBCOM.BIN: declarations shared by its source files
#ifndef _COMBCOM_H_
#define _COMBCOM_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "minion_menu.h"
#include "effect_data.h"

typedef struct CombComDlg
{
    int f0;
    int f4;
    int f8;
    int fC;
} CombComDlg;

typedef struct CombComCmd
{
    int kind_0;
    int arg_4;
    int mask_8; // acting unit bits
    int targets_C; // target unit bits
} CombComCmd;

typedef struct CombComItem
{
    unsigned short flags;
    short pad_2;
    void* text_4;
    int f8;
    int fC;
    short x_10;
    short y_12;
    int rest[9];
} CombComItem;

typedef struct CombComMenu
{
    int f0;
    int time_4;
    int f8;
    int sel_C;
    void* items_10;
    int f14;
} CombComMenu;

typedef struct CombComMsg
{
    int* f0;
    int* text;
} CombComMsg;

typedef struct CombComMsgs3
{
    int m[3];
} CombComMsgs3;

typedef struct CombComPos2
{
    short xy[2][2];
} CombComPos2;

extern int dword_800C9E88;
extern const char aUseNormalAttack_800C9E8C[];
extern const char aDefendToReduceD_800C9EB0[];
extern const char aUseSpecialAttac_800C9EE0[];
extern const char aUseMagicSpell_800C9F08[];
extern const char aChangeCurrentFi_800C9F28[];
extern const char aCannotSummonInt_800C9F58[];
extern const char aNotEnoughMana_800C9F8C[];
extern const int dword_800C9FAC;
extern const char aNoNeedToUseItem_800C9FB0[];
extern const char aCannotSelect_800C9FD8[];
extern const char aNoDivineMinions_800C9FF4[];
extern const char aPause_800CA038[];
extern const char aDescription_800CA044[];
extern const char aSelect_800CA05C[];
extern const char aQuit_800CA06C[];
extern const char aEffectivenessOf_800CA078[];
extern const char aIncreasesWindAt_800CA0D8[];
extern const char aEnhanceWind_800CA12C[];
extern const char aEffectivenessOf_800CA148[];
extern const char aIncreasesEarthA_800CA1A8[];
extern const char aEnhanceEarth_800CA200[];
extern const char aEffectivenessOf_800CA21C[];
extern const char aIncreasesWaterA_800CA278[];
extern const char aEnhanceWater_800CA2D0[];
extern const char aEffectivenessOf_800CA2EC[];
extern const char aIncreasesFireAt_800CA348[];
extern const char aEnhanceFire_800CA39C[];
extern const char aCausesAnEnemyTo_800CA3B8[];
extern const char aDeath_800CA40C[];
extern const char aTurnsAnEnemyInt_800CA418[];
extern const char aFleshToStone_800CA450[];
extern const char aPutsAnEnemyToSl_800CA470[];
extern const char aSleep_800CA4A0[];
extern const char aPoisonsAnEnemy_800CA4AC[];
extern const char aPoison_800CA4D0[];
extern const char aEndsOnceItProte_800CA4E0[];
extern const char aProtectsAgainst_800CA534[];
extern const char aProtection_800CA59C[];
extern const char aCuresPoisonAndT_800CA5B4[];
extern const char aReturnToNormal_800CA60C[];
extern const char aRestoresAllHP_800CA630[];
extern const char aRestoreAllHP_800CA654[];
extern const char aRestoresSomeHP_800CA674[];
extern const char aRestoreHP_800CA698[];
extern const char aCuresPoison_800CA6B0[];
extern const char aCurePoison_800CA6CC[];
extern const char aAdvancedWindAtt_800CA6E4[];
extern const char aWindAttackAllEn_800CA710[];
extern const char aHigherWindEleme_800CA744[];
extern const char aExtraDamageVsEa_800CA7A0[];
extern const char aWindAttackOneEn_800CA7D0[];
extern const char aAdvancedEarthAt_800CA800[];
extern const char aEarthAttackAllE_800CA82C[];
extern const char aHigherEarthElem_800CA864[];
extern const char aExtraDamageVsWa_800CA8C4[];
extern const char aEarthAttackOneE_800CA8F4[];
extern const char aAdvancedWaterAt_800CA928[];
extern const char aWaterAttackAllE_800CA954[];
extern const char aHigherWaterElem_800CA98C[];
extern const char aExtraDamageVsFi_800CA9EC[];
extern const char aWaterAttackOneE_800CAA18[];
extern const char aAdvancedFireAtt_800CAA4C[];
extern const char aFireAttackAllEn_800CAA78[];
extern const char aHigherFireEleme_800CAAAC[];
extern const char aExtraDamageVsAi_800CAB08[];
extern const char aFireAttackOneEn_800CAB34[];
extern const char aMakesItEasierTo_800CAB64[];
extern const char aSpecialAttackBr_800CABBC[];
extern const char aSlightlyMoreDif_800CABF8[];
extern const char aMakesItEasierTo_800CAC5C[];
extern const char aSpecialAttackBr_800CACBC[];
extern const char aItMoreDifficult_800CACF4[];
extern const char aReducesAnEnemie_800CAD4C[];
extern const char aSpecialAttackCr_800CAD98[];
extern const char aBringsEnemiesTo_800CADD4[];
extern const char aAttacksAllEnemi_800CAE20[];
extern const char aSpecialAttackAl_800CAE5C[];
extern const char aUsesItToRestore_800CAE98[];
extern const char aStealsSomeManaF_800CAEE0[];
extern const char aSpecialAttackAb_800CAF28[];
extern const char aAnEnemyToRestor_800CAF64[];
extern const char aTakesSomeOfTheD_800CAFB4[];
extern const char aSpecialAttackAb_800CB000[];
extern const char aMoreDifficultFo_800CB038[];
extern const char aCausesAnEnemyTo_800CB088[];
extern const char aSpecialAttackDe_800CB0F0[];
extern const char aPhysicallyDamag_800CB12C[];
extern const char aSpecialFleshToS_800CB198[];
extern const char aPhysicallyDamag_800CB1D4[];
extern const char aSpecialSleepAtt_800CB23C[];
extern const char aPhysicallyDamag_800CB268[];
extern const char aSpecialPoisonAt_800CB2BC[];
extern const char aVeryEffectiveAg_800CB2E8[];
extern const char aSpecialWindAtta_800CB340[];
extern const char aVeryEffectiveAg_800CB368[];
extern const char aSpecialFireAtta_800CB3C0[];
extern const char aVeryEffectiveAg_800CB3E8[];
extern const char aSpecialWaterAtt_800CB440[];
extern const char aVeryEffectiveAg_800CB46C[];
extern const char aSpecialEarthAtt_800CB4C4[];
extern const CombComItem name_800CB4F0;
extern const CombComItem name_800CB528;
extern const CombComItem name_800CB560;
extern const CombComItem name_800CB598;
extern const CombComMenu name_800CB5D0;
extern const char aStartFight_800CB5E8[];
extern const char aGiveUpResultsIn_800CB600[];
extern const char aReturnToStartOf_800CB638[];
extern const CombComMsgs3 name_800CB674;
extern const CombComPos2 name_800CB680;
extern const CombComPos2 name_800CB688;
extern const int dword_800CB690[14];
extern const int dword_800CB6C8[14];
extern const int dword_800CB700[15];
extern short dword_800CD28C[4];
extern short word_800CD294;
extern short dword_800CD298[6];
extern short dword_800CD2A4[2];
extern short word_800CD2A8;
extern short word_800CD2AA;
extern short word_800CD2AC;
extern short word_800CD2AE;
extern short dword_800CD2B0[6];
extern short dword_800CD2BC[6];
extern char dword_800CD2C8[8];
extern short word_800CD2D0;
extern short *dword_800CD2D4[6];
extern CombComItem dword_800CD2EC[1];
extern CombComItem dword_800CD324[1];
extern CombComItem dword_800CD35C[1];
extern CombComItem dword_800CD394[1];
extern char dword_800CD3CC[56];
extern CombComItem *dword_800CD404[4];
extern void *dword_800CD414;
extern int dword_800CD418;
extern unsigned int dword_800CD41C[6];
extern short word_800CD434[6];
extern const char *dword_800CD440[1];
extern const char *dword_800CD444[1];
extern const char *dword_800CD448[1];
extern const char *dword_800CD44C[1];
extern const char *dword_800CD450[1];
extern int dword_800CD454;
extern int dword_800CD458;
extern void *dword_800CD45C[1];
extern int dword_800CD460;
extern const char *dword_800CD464[1];
extern char dword_800CD468[4];
extern CombComMsg name_800CD46C[4];
extern void *dword_800CD48C[1];
extern void *dword_800CD490;
extern unsigned char byte_800CD494[8];
extern unsigned char byte_800CD49C[8];
extern int dword_800CD4A4[8];
extern int dword_800CD4C4[10];
extern int dword_800CD4EC[8];
extern char *name_800CD50C[6];
extern int dword_800CD524[5];
extern CombComDlg name_800CD538[30];
extern char name_800CD718[256];
extern void (*dword_800CD818[2])(EventEntry *, void *);
extern unsigned short name_800CD820[6][2];
extern unsigned char byte_800CD838;
extern unsigned char byte_800CD839;
extern unsigned char byte_800CD83A;
extern unsigned char byte_800CD83B;
extern int dword_800CD83C;
extern CombComCmd *dword_800CD840;
extern unsigned char byte_800CD844;
extern unsigned char byte_800CD845;
extern int dword_800CD848;
extern int dword_800CD84C;
extern unsigned char byte_800CD850;
extern short *dword_800CD854;

#endif
