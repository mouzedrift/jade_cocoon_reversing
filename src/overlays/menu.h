// MENU.BIN: declarations shared by its source files
#ifndef _MENU_H_
#define _MENU_H_

#include "common.h"
#include "common_tu.h"
#include "funcs.h"
#include "globals.h"
#include "tiy.h"
#include "engine.h"
#include "minion_menu.h"
#include "main.h"
#include "sound.h"
#include "STDLIB.H"
#include "font.h"
#include "menu_window.h"
#include "model_ftg.h"
#include "msg_window.h"
#include "util.h"
#include "unit_query.h"
#include "event.h"
#include "movie.h"

// a battle drop table row (RollDrop_800BD358): two chances against rand(), each with an item kind and id
typedef struct ItemDropRow
{
    unsigned short lim_0;
    unsigned char kind_2;
    unsigned char item_3;
    unsigned short lim_4;
    unsigned char kind2_6;
    unsigned char item2_7;
} ItemDropRow;

typedef struct MenuQ
{
    int w[4];
} MenuQ;


typedef struct BattleDrop
{
    char pad_0[2];
    unsigned char kind_2;
    unsigned char item_3; // 0xFF: no drop
    char pad_4[4];
} BattleDrop;


typedef struct MenuCursorLayout
{
    unsigned short cols_0; // a MenuCursor layout (MenuCtx.cols_58..cursorFlags_5E)
    unsigned short rows_2;
    unsigned short count_4;
    unsigned short flags_6;
    char pad_8[8];
} MenuCursorLayout;

typedef struct MenuCell
{
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
} MenuCell;



/* the types of menu.c */

typedef struct MenuTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} MenuTask;

// the field menu (StartFieldMenu_800BD40C)
typedef struct MenuCtx
{
    unsigned short flags_0; // top screen focus: 1 Levant window, 2 party minions, 4 the menu below; 8 closing, 0x20 a sub overlay runs
    short state_2;          // the screen: index of menuNextState_800C1950, menuStateWindows_800C1998, ...
    short prevState_4;
    short message_6;        // CheckMenuAction_800BF540 result: menuMessages_800C18FC index
    int partyCount_8;       // Levant + minions
    int storedCount_C;      // CountItems_800106B8
    unsigned int windows_10;       // bit i: window i of DrawFieldMenu_800BE4A0 is drawn
    int openedWindows_14;          // bit i: window i finished opening
    int confirmed_18;
    int cancelled_1C;
    int f20;
    int showMessage_24;            // DrawMenuMessage_800BF794 runs
    short openTimer_28;            // 0..8 window open animation
    short cursors_2A[11];          // cursor per screen (cursorSaveSlot_800C1B74)
    short pad_40[3];
    short scrolls_46[4];
    char pad_4E[8];
    short messageTimer_56;
    short cols_58; // cols_58..scroll_62: an exe MenuCursor (UpdateMenuCursor_8003D794)
    short rows_5A;
    short count_5C;
    short cursorFlags_5E;
    short cursor_60;
    short scroll_62;
} MenuCtx;


typedef struct MenuPair
{
    short a;
    short b;
} MenuPair;

// what DrawLevantSummary_8002E334 takes
typedef struct LevantSummaryArgs
{
    short ot_0;
    short step_2;      // window open step
    int highlight_4;
    int time_8;
} LevantSummaryArgs;

// what DrawEquipmentWindow_800C0E04 / DrawKeyItemsWindow_800C09B0 take
typedef struct MenuEquipQ
{
    short sel_0; // -> MenuWindowList.cursor_C
    short scroll_2;
    short winFlags_4; // -> MenuWindowList.flags_0
    short ot_6;  // -> MenuWindowList.ot_14
    short f8;
    short fA;
    int z;
} MenuEquipQ;

// what DrawPartySlotWindow_8002F8E4 takes
typedef struct PartySlotArgs
{
    short step_0;   // window open step
    short count_2;  // party minions
    short cursor_4; // the highlighted slot (-1: none)
    short ot_6;
    int time_8;
    short slot_C;
    short pad_1E;
    int g;
} PartySlotArgs;

typedef struct MenuEnt
{
    char pad_0[4];
    short dropTable_4; // itemDropTable_800C1080 row (-1: none)
    unsigned short idx_6;
    unsigned short u8;
    unsigned short a;
} MenuEnt;

// what CheckItemOnTarget_80033DF4 takes
typedef struct ItemTargetQuery
{
    short item_0;
    short b;
    unsigned short target_4;
    short d;
} ItemTargetQuery;

// stat changes worked out by UseItemOnUnit_80013C28
typedef struct MenuStatDelta
{
    int f0;
    int f4;
    int f8;
    int pad_C[4];
    int hp_1C; // HP change (negated)
    int mp_20; // MP change (negated)
    int f24;
} MenuStatDelta;

// an item use command (InitItemUse_800C00D4, UseItemOnUnit_80013C28) followed by the stat changes it works out
typedef struct ItemUseWork
{
    int f0;
    int item_4;
    int f8;
    int targets_C; // bit i: unit i
    MenuStatDelta d_10;
} ItemUseWork;

typedef struct MenuSprWin
{
    short x_0;
    short y_2;
    int pad_4;
    short col_8;
    char colorSet_A;
    char semiTrans_B;
} MenuSprWin;

// the battle result screen (CreateBattleResultTask_800BBB9C); index 0 is Levant, 1.. the minions
typedef struct BattleResult
{
    int flags_0; // 2 Levant done, 1 << (i + 1) unit i done, 0x20 rank up / level up panel, 0x40 finished, 0x80 exp counted
    char pad_4[0x30];
    unsigned int expAdded_34[4];
    short count_44;
    short fade_46;
    int fadeIn_48;
    int hasDrop_4C[3];
    short s58;
    short pad_5A;
    int levelUps_5C[4];
    unsigned int expGain_6C[4];
    int leveledUp_7C[4];
    UnitStatus st_8C[4];       // working copy that gets the exp
    UnitStatus oldStatus_1AC[4];
    unsigned int expShown_2CC[4];
    int i2DC;
} BattleResult;

// what DrawLevantSummary_8002E334 takes (as LevantSummaryArgs)
typedef struct ResultSummaryArgs
{
    short ot_0;
    short step_2;
    int highlight_4;
    int time_8;
} ResultSummaryArgs;


typedef struct UiWinArgs
{
    RECT* rect;
    int f4;
    short f8;
    short ot_A;
} UiWinArgs;

typedef struct MenuUseQ
{
    short a;
    short b;
    short c;
    short d;
    short e;
    short f;
    int g;
} MenuUseQ;

/* MENU functions */
extern void SaveMenuCursor_800BE294(MenuCtx* menu);
extern void HandleMenuConfirmCancel_800BDE10(MenuCtx* menu);
extern void DrawMenuMessage_800BF794(MenuCtx* menu);
extern void HandleMenuCursorInput_800BFCA8(MenuCtx* menu);
extern void OpenSubMenuOverlay_800BFE18(MenuCtx* menu);
extern void CloseMenuReloadArea_800C0084(void);
extern void SetLevantCmdWindows_800C01AC(MenuCtx* menu);
extern void SetMinionCmdWindows_800C01D0(MenuCtx* menu);
extern void MinionListScreen_800BD80C(MenuTask* task, char* a);
extern int TopMenuCursorDown_800BFB10(MenuCtx* menu);
extern int TopMenuCursorUp_800BFBE0(MenuCtx* menu);
extern void ApplyItemUseDelta_800C00F8(ItemUseWork* use, MenuStatDelta* delta);
extern void InitItemUse_800C00D4(ItemUseWork* use, int item, int target);
// HandleMenuConfirmCancel_800BDE10 calls it without arguments (a0 still holds its menu)
extern int CheckMenuAction_800BF540();
extern void EnterNextMenuState_800BE048(MenuCtx* menu);
extern void ResumeFieldMenu_800BFF84(MenuCtx* menu);
extern int GetWindowOpenStep_800C0990(MenuCtx* menu, int mask);
extern void EnterPrevMenuState_800BE25C(MenuCtx* menu);
extern void SetMenuCursorLayout_800BF8B4(MenuCtx* menu);
extern void RestoreMenuCursor_800BE38C(MenuCtx* menu);
extern void FieldMenuWaitUiTask_800BD590(MenuTask* task, MenuCtx* menu);
extern void DrawFieldMenu_800BE4A0(MenuCtx* menu);
extern void FieldMenuFadeInTask_800BD5E4(MenuTask* task, MenuCtx* menu);
extern void FieldMenuTask_800BD6C8(MenuTask* task, MenuCtx* menu);
extern void ResultWaitUiTask_800BBE50(MenuTask* task);
extern void ResultStartTask_800BBE90(MenuTask* task, BattleResult* result);
extern int RollBattleDrops_800BD230(BattleResult* result);
extern void ShowDropMessage_800BCFDC(BattleResult* result);
extern void DrawResultParty_800BC2A8(BattleResult* result);
extern void DropMessageTask_800BD1B0(MenuTask* task);
extern void BattleResultTask_800BBF48(MenuTask* task, BattleResult* result);
extern void UpdateExpCountUp_800BC56C(BattleResult* result);
extern void HandleLevelUpInput_800BC9E8(BattleResult* result);
extern void DrawLevantRankUp_800BCB98(BattleResult* result, int b);
extern void DrawMinionLevelUpStatus_800BCEA0(BattleResult* result, int ot, void* status, short unit);
extern void ResultEndTask_800BC24C(MenuTask* task);
extern void DrawMinionLevelUp_800BC934(int unit, int count);
extern void OnMinionLevelUp_800BCF74(short index);
extern void DrawMinionListPage_800BDBFC(char* work, int page);
extern void DrawMagicInfo_800C06E8(MenuCtx* menu);
extern void DrawMinionCmdMenu_800C08C0(MenuCtx* menu);
extern void DrawItemGrid_800C01F4(MenuCtx* menu); // the item grid scroll is cursors_2A[9]
extern void DrawItemInfo_800C0428(MenuCtx* menu);
extern void DrawLevantStatsWindow_800C0578(MenuCtx* menu);
extern void DrawKeyItemInfo_800C05E0(MenuCtx* menu);
extern void DrawKeyItemsWindow_800C09B0(MenuEquipQ* eq);
extern void PreviewItemRecovery_800C0CA4(MenuCtx* menu, int* out);
extern void DrawMenuHelpBar_800BEAE0(MenuCtx* menu);
extern void DrawSelectedMinionPanel_800BEBFC(MenuCtx* menu, RECT* rect);
extern void DrawEquipmentWindow_800C0E04(MenuEquipQ* eq, short* pos, short openStep);
extern int IsKeyItemUseAllowed_800C1000(void);
extern void ConfigMenuWaitTask_800BFF38(MenuTask* task, MenuCtx* menu);
extern void EquipMenuWaitTask_800BFEC0(MenuTask* task, MenuCtx* menu);
extern void DrawLevantCmdMenu_800C07F0(MenuCtx* menu);
extern void StartFieldMenu_800BD40C(MenuTask* task, MenuCtx* menu);
extern void MenuReloadAreaTask_800BFFFC(MenuTask* task);
extern void DrawLevantLevelUp_800BC8A8(void);
extern void DrawCursorWindow_800BEC8C(MenuCtx* unused, RECT* rect, short ot, int unused2);
extern void DrawLevantWindow_800BECE4(MenuCtx* menu, short ot);
extern void DrawPartyMinionWindows_800BEFAC(MenuCtx* menu, short ot);
extern void DrawLevantStatusScreen_800BF0F4(MenuCtx* menu, short ot);
extern int RollDrop_800BD358(BattleDrop* out, int idx);
extern int IsMinionListed_800BDD94(int species);
// EnterNextMenuState_800BE048 passes the inventory slot as a 2nd argument that it ignores
extern void UseSpore_800BF3AC();
extern void ExecuteMenuAction_800BF3E0(MenuCtx* menu);
extern int IsKeyItemUsable_800C0C3C(int item);
extern int IsRecoveryItem_800C0DD4(int item);

/* MENU data */
extern const int menuOverlayId_800B66C0;
extern const char aItemsObtained_800B66C4[];
extern const char aStatus_800B66D0[];
extern const char aQuit_800B66E0[];
extern const int emptyHelpLabel_800B66EC;
extern const char aNoNeedToUseThis_800B66F0[];
extern const char aThisMinionCanno_800B6724[];
extern const char aMinionsCannotUs_800B676C[];
extern const char aThisItemIsForTh_800B67A8[];
extern const char aNoMinionsCaptur_800B67E4[];
extern const char aNotAvailable_800B6818[];
extern const char emptyText_800B6838[4];
extern const char aNotUsableHere_800B683C[];
extern const char aNoItems_800B6860[];
extern const char aAttractsNearbyM_800B6874[];
extern const char aTreeSporesWithA_800B68A8[];
extern const char aCausesSurroundi_800B68F4[];
extern const char aSweetSmellingSl_800B694C[];
extern const char aTreeSpores_800B69B4[];
extern const char aBendsAndBecomes_800B69CC[];
extern const char aMultipurposeKey_800B6A24[];
extern const char aKeyToTreasureCh_800B6A88[];
extern const char aHighestGradeBes_800B6AB8[];
extern const char aSoftThreadThatG_800B6AFC[];
extern const char aSecondHighestGr_800B6B50[];
extern const char aGivesOffAnUnear_800B6B8C[];
extern const char aThirdHighestGra_800B6BDC[];
extern const char aGivesOffAPhosph_800B6C18[];
extern const char aFourthHighestGr_800B6C68[];
extern const char aGivesOffAModera_800B6CA4[];
extern const char aFifthHighestGra_800B6CEC[];
extern const char aGivesOffADazzli_800B6D28[];
extern const char aSixthHighestGra_800B6D60[];
extern const char aEmitsVagueInsta_800B6D9C[];
extern const char aSeventhHighestG_800B6DF8[];
extern const char aGivesOffAShineT_800B6E38[];
extern const char aSilkThreadSpunF_800B6E94[];
extern const char aInflictsAWindBa_800B6EE0[];
extern const char aAttackMultipleE_800B6F44[];
extern const char aInflictsAWindBa_800B6F88[];
extern const char aSealWithTheMark_800B6FE8[];
extern const char aAttackSingleEne_800B7050[];
extern const char aInflictsAFireBa_800B708C[];
extern const char aAttackAllEnemie_800B70E8[];
extern const char aInflictsAFireBa_800B7124[];
extern const char aSealWithTheMark_800B7184[];
extern const char aAttackSingleEne_800B71E8[];
extern const char aInflictsAWaterB_800B7224[];
extern const char aAttackAllEnemie_800B7280[];
extern const char aInflictsAWaterB_800B72BC[];
extern const char aSealWithTheMark_800B7320[];
extern const char aAttackSingleEne_800B7388[];
extern const char aInflictsAnEarth_800B73C8[];
extern const char aAttackAllEnemie_800B7428[];
extern const char aInflictsAnEarth_800B7464[];
extern const char aSealWithTheMark_800B74C8[];
extern const char aAttackSingleEne_800B7530[];
extern const char aChangesAreaProp_800B7570[];
extern const char aACharmBlessedBy_800B75D4[];
extern const char aChangesAreaProp_800B7634[];
extern const char aACharmBlessedBy_800B7698[];
extern const char aChangesAreaProp_800B76F8[];
extern const char aACharmBlessedBy_800B7760[];
extern const char aChangesAreaProp_800B77C0[];
extern const char aACharmBlessedBy_800B7828[];
extern const char aChangeAreaPrope_800B7888[];
extern const char aAllAbnormalStat_800B78B8[];
extern const char aReflectsAllUncl_800B7920[];
extern const char aProtectionFromA_800B7980[];
extern const char aInstantlyCauses_800B79A8[];
extern const char aReleasesADeathM_800B7A04[];
extern const char aCauseDeath_800B7A4C[];
extern const char aCausesBodyHarde_800B7A64[];
extern const char aReleasesAFleshT_800B7AC0[];
extern const char aFleshToStone_800B7B18[];
extern const char aCausesADeepSlum_800B7B38[];
extern const char aReleasesASleepM_800B7BA4[];
extern const char aInduceSleep_800B7BEC[];
extern const char aInstantlyCauses_800B7C08[];
extern const char aReleasesPoisonM_800B7C50[];
extern const char aSprayPoison_800B7C94[];
extern const char aInnerStrengthTo_800B7CB0[];
extern const char aPowderMadeFromS_800B7D0C[];
extern const char aStoneToFlesh_800B7D70[];
extern const char aSoothesTheSpiri_800B7D90[];
extern const char aPowderedFormOfD_800B7DE4[];
extern const char aPoisonAntidote_800B7E30[];
extern const char aAdjustsTheVisce_800B7E50[];
extern const char aAlsoCalledTheIm_800B7E7C[];
extern const char aDriedRootOfAGre_800B7EC0[];
extern const char aTotalRestoratio_800B7F28[];
extern const char aRestoresAllMini_800B7F4C[];
extern const char aSpecialLiquorMa_800B7F90[];
extern const char aRestoresAGreatD_800B7FEC[];
extern const char aExcellentLiquor_800B8048[];
extern const char aRestoresMinionH_800B80A8[];
extern const char aFineLiquorMadeF_800B810C[];
extern const char aRestoresSomeMin_800B8164[];
extern const char aLiquorMadeFromP_800B81A8[];
extern const char aRestoreMinionHP_800B81F4[];
extern const char aStrengthensMini_800B822C[];
extern const char aOilFromAPlantWi_800B8268[];
extern const char aIncreaseMinionM_800B82B0[];
extern const char aStrengthensMini_800B82EC[];
extern const char aOilFromTreeWith_800B8324[];
extern const char aIncreaseMinionM_800B836C[];
extern const char aHardensMinionSS_800B83A8[];
extern const char aOilFromAPlantWi_800B83D8[];
extern const char aIncreaseMinionD_800B8424[];
extern const char aStrengthensMini_800B8464[];
extern const char aOilFromAVeryPot_800B849C[];
extern const char aIncreasesMinion_800B84D8[];
extern const char aSharpensMinionS_800B8508[];
extern const char aOilFromATreeWit_800B853C[];
extern const char aIncreaseMinionA_800B8584[];
extern const char aStrengthensTheB_800B85C0[];
extern const char aANutPackingEner_800B8624[];
extern const char aIncreaseMaxHeal_800B8684[];
extern const char aBitterTasteThat_800B86AC[];
extern const char aATypeOfMugwortW_800B8718[];
extern const char aCuresBleedingAn_800B877C[];
extern const char aSweeterSmelling_800B87C0[];
extern const char aATypeOfMugwortB_800B8818[];
extern const char aGrindLeavesInto_800B8858[];
extern const char aIncreasesHealth_800B88B4[];
extern const char aGrowsInOpenArea_800B8900[];
extern const char aRestoreHealth_800B8948[];
extern const char aSharpClawsAndFo_800B8968[];
extern const char aTheSixLeggedCre_800B89D0[];
extern const char aBarrelLikeBodyF_800B8A34[];
extern const char aTheMythicalBird_800B8A98[];
extern const char aMinionsSoThatTh_800B8AFC[];
extern const char aMovesCloserToAT_800B8B5C[];
extern const char aToIncreaseHPMer_800B8BB8[];
extern const char aMinionsWithSlee_800B8C18[];
extern const char aPoisonResistant_800B8C78[];
extern const char aMergingSuchAMin_800B8CDC[];
extern const char aMinionsThatUseP_800B8D40[];
extern const char aOneOfYourMinion_800B8DA4[];
extern const char aOfTheSecondItIs_800B8E0C[];
extern const char aTheFirstMinionA_800B8E74[];
extern const char aAmountOfElement_800B8ED8[];
extern const char aYourElementalAt_800B8F2C[];
extern const char aBoostYourSpecia_800B8F88[];
extern const char aLessLikelyWhile_800B8FE0[];
extern const char aManaWillRecover_800B9044[];
extern const char aAndAvoidanceWil_800B9098[];
extern const char aEachTurnEventua_800B90F8[];
extern const char aWhileTurningToS_800B915C[];
extern const char aDecreaseResulti_800B91C4[];
extern const char aPhysicalAndMagi_800B9228[];
extern const char aWhileInflictedW_800B9290[];
extern const char aYouWillAlsoLose_800B92F4[];
extern const char aAttackDecreases_800B9358[];
extern const char aWhilePoisonedYo_800B93AC[];
extern const char aYouReceiveToAtt_800B93FC[];
extern const char aTheHigherYourSp_800B9440[];
extern const char aMoreEffectiveNo_800B948C[];
extern const char aHigherAttackAnd_800B94F4[];
extern const char aEffectiveAgains_800B9544[];
extern const char aFireBasedCreatu_800B9594[];
extern const char aWaterBasedAttac_800B95F0[];
extern const char aKikinakHoweverC_800B9644[];
extern const char aPreciousTreasur_800B9694[];
extern const char aUsedForTravelIn_800B96E4[];
extern const char aUsedForTravelIn_800B9730[];
extern const char aAllowsUserToTel_800B9784[];
extern const char aUsedForTravelIn_800B97DC[];
extern const char aKeyModeledAfter_800B9828[];
extern const char aOversizedAndStu_800B9868[];
extern const char aKeyModeledAfter_800B98C0[];
extern const char aVeryHardAndUsef_800B990C[];
extern const char aBoneOfABeastSha_800B9964[];
extern const char aStrangeSmellShu_800B99C4[];
extern const char aRareBerryFoundO_800B9A24[];
extern const char aTellsOfProfound_800B9A80[];
extern const char aStoneTabletEngr_800B9AB4[];
extern const char aYellowJewelGlow_800B9B18[];
extern const char aRedJewelGlowing_800B9B70[];
extern const char aTestamentToYour_800B9BC0[];
extern const char aBlueJewelGlowin_800B9C24[];
extern const char aMahbuSSoulWillV_800B9C78[];
extern const char aCocoonForExtend_800B9CD8[];
extern const char aUnlocksTheGateT_800B9D20[];
extern const char aKeyCarvedInTheS_800B9D6C[];
extern const char aCapturesTheDivi_800B9DB4[];
extern const char aAmuletPackingTh_800B9E14[];
extern const char aBringsBackFondM_800B9E78[];
extern const char aChampionSBeltFo_800B9ED4[];
extern const char aSourceOfCalabas_800B9F38[];
extern const char aUsedToSummonKik_800B9F6C[];
extern const char aOcarinaGivenByK_800B9FA0[];
extern const char aUnlocksTheGateT_800BA008[];
extern const char aKeyCarvedInTheS_800BA058[];
extern const char aSaidToWakeTheSl_800BA0A4[];
extern const char aPowderInfusedWi_800BA100[];
extern const char aUnlocksTheGateT_800BA144[];
extern const char aKeyCarvedInTheS_800BA198[];
extern const char aUnlocksTheGateT_800BA1E8[];
extern const char aKeyCarvedInTheS_800BA238[];
extern const char aBestowedToYoung_800BA284[];
extern const char aGiftFromMahbuGi_800BA2DC[];
extern const char aNeededForCaptur_800BA33C[];
extern const char aMusicalInstrume_800BA3A4[];
extern const char aBackToTheBarrie_800BA408[];
extern const char aASymbolOfAnAdul_800BA464[];
extern const char aValuable_800BA4C0[];
extern const char aEffectivenessOf_800BA4D4[];
extern const char aIncreasesWindAt_800BA534[];
extern const char aEnhanceWind_800BA588[];
extern const char aEffectivenessOf_800BA5A4[];
extern const char aIncreasesEarthA_800BA604[];
extern const char aEnhanceEarth_800BA65C[];
extern const char aEffectivenessOf_800BA678[];
extern const char aIncreasesWaterA_800BA6D4[];
extern const char aEnhanceWater_800BA72C[];
extern const char aEffectivenessOf_800BA748[];
extern const char aIncreasesFireAt_800BA7A4[];
extern const char aEnhanceFire_800BA7F8[];
extern const char aCausesAnEnemyTo_800BA814[];
extern const char aDeath_800BA868[];
extern const char aTurnsAnEnemyInt_800BA874[];
extern const char aPutsAnEnemyToSl_800BA8AC[];
extern const char aSleep_800BA8DC[];
extern const char aPoisonsAnEnemy_800BA8E8[];
extern const char aPoison_800BA90C[];
extern const char aEndsOnceItProte_800BA91C[];
extern const char aProtectsAgainst_800BA970[];
extern const char aProtection_800BA9D8[];
extern const char aCuresPoisonAndT_800BA9F0[];
extern const char aReturnToNormal_800BAA48[];
extern const char aRestoresAllHP_800BAA6C[];
extern const char aRestoreAllHP_800BAA90[];
extern const char aRestoresSomeHP_800BAAB0[];
extern const char aRestoreHP_800BAAD4[];
extern const char aCuresPoison_800BAAEC[];
extern const char aCurePoison_800BAB08[];
extern const char aAdvancedWindAtt_800BAB20[];
extern const char aWindAttackAllEn_800BAB4C[];
extern const char aHigherWindEleme_800BAB80[];
extern const char aExtraDamageVsEa_800BABDC[];
extern const char aWindAttackOneEn_800BAC0C[];
extern const char aAdvancedEarthAt_800BAC3C[];
extern const char aEarthAttackAllE_800BAC68[];
extern const char aHigherEarthElem_800BACA0[];
extern const char aExtraDamageVsWa_800BAD00[];
extern const char aEarthAttackOneE_800BAD30[];
extern const char aAdvancedWaterAt_800BAD64[];
extern const char aWaterAttackAllE_800BAD90[];
extern const char aHigherWaterElem_800BADC8[];
extern const char aExtraDamageVsFi_800BAE28[];
extern const char aWaterAttackOneE_800BAE54[];
extern const char aAdvancedFireAtt_800BAE88[];
extern const char aFireAttackAllEn_800BAEB4[];
extern const char aHigherFireEleme_800BAEE8[];
extern const char aExtraDamageVsAi_800BAF44[];
extern const char aFireAttackOneEn_800BAF70[];
extern const char aMakesItEasierTo_800BAFA0[];
extern const char aSpecialAttackBr_800BAFF8[];
extern const char aSlightlyMoreDif_800BB034[];
extern const char aMakesItEasierTo_800BB098[];
extern const char aSpecialAttackBr_800BB0F8[];
extern const char aItMoreDifficult_800BB130[];
extern const char aReducesAnEnemie_800BB188[];
extern const char aSpecialAttackCr_800BB1D4[];
extern const char aBringsEnemiesTo_800BB210[];
extern const char aAttacksAllEnemi_800BB25C[];
extern const char aSpecialAttackAl_800BB298[];
extern const char aUsesItToRestore_800BB2D4[];
extern const char aStealsSomeManaF_800BB31C[];
extern const char aSpecialAttackAb_800BB364[];
extern const char aAnEnemyToRestor_800BB3A0[];
extern const char aTakesSomeOfTheD_800BB3F0[];
extern const char aSpecialAttackAb_800BB43C[];
extern const char aMoreDifficultFo_800BB474[];
extern const char aCausesAnEnemyTo_800BB4C4[];
extern const char aSpecialAttackDe_800BB52C[];
extern const char aPhysicallyDamag_800BB568[];
extern const char aSpecialFleshToS_800BB5D4[];
extern const char aPhysicallyDamag_800BB610[];
extern const char aSpecialSleepAtt_800BB678[];
extern const char aPhysicallyDamag_800BB6A4[];
extern const char aSpecialPoisonAt_800BB6F8[];
extern const char aVeryEffectiveAg_800BB724[];
extern const char aSpecialWindAtta_800BB77C[];
extern const char aVeryEffectiveAg_800BB7A4[];
extern const char aSpecialFireAtta_800BB7FC[];
extern const char aVeryEffectiveAg_800BB824[];
extern const char aSpecialWaterAtt_800BB87C[];
extern const char aVeryEffectiveAg_800BB8A8[];
extern const char aSpecialEarthAtt_800BB900[];
extern const char aQuit_800BB92C[];
extern const char aViewStatus_800BB938[];
extern const char aMinionList_800BB950[];
extern const char aSelect_800BB968[];
extern const char aRearrange_800BB978[];
extern const char aDescription_800BB98C[];
extern const MenuWindowItem minionListTitle_800BB9A4;
extern const char minionListBullet_800BB9C0[];
extern const int dword_800BB9C4;
extern const char aLeaveTheForest_800BBA44[];
extern const char aYesNo_800BBA68[];
extern const int dword_800BBA7C;
extern const MenuWindowList menuHdrActive_800BBB7C;
extern const int dword_800BBB94[2];
extern int dword_800C1050[4];
extern char levelUpStatusRect_800C1060[32];
extern ItemDropRow itemDropTable_800C1080[211];
extern short dword_800C1718[10];
extern int resultHelpBar_800C172C[7];
extern char dword_800C1748[12];
extern int equipSlotLabels_800C1754[3];
extern MenuWindowItem equipRowWeapon_800C1760[4];
extern MenuWindowItem equipRowArmor_800C17D0[4];
extern MenuWindowItem equipRowAccessory_800C1840[4];
extern MenuWindowItem* equipRows_800C18B0[4];
extern short dword_800C18C0[2];
extern char levantStatsRect_800C18C4[8];
extern char menuTitleRect_800C18CC[8];
extern char configLabelRect_800C18D4[8];
extern char rankRect_800C18DC[8];
extern char moneyWindowRect_800C18E4[8];
extern MenuCell itemGridCell_800C18EC;
extern char statusWindowRect_800C18F4[8];
extern int menuMessages_800C18FC[16];
extern unsigned short levantCmdStates_800C193C[6];
extern unsigned short minionCmdStates_800C1948[4];
extern short menuNextState_800C1950[18];
extern short menuPrevState_800C1974[18];
extern int menuStateWindows_800C1998[17];
extern MenuCursorLayout menuStateCursors_800C19DC[17];
extern RECT menuWindowRects_800C1AEC[17]; // one per menu state
extern short cursorSaveSlot_800C1B74[18];
extern short cursorRestoreSlot_800C1B98[18];
extern int levantCmdWindows_800C1BBC[5];
extern int minionCmdWindows_800C1BD0[4];
extern char statusStatsRect_800C1BE0[8];
extern MenuQ itemDescs_800C1BE8[43];
extern MenuQ keyItemDescs_800C1E98[38];
extern MenuQ magicDescs_800C20F8[30];
extern char abilityDescs_800C22D8[624];
extern MenuWindowItem levantCmdItem0_800C2548[2];
extern MenuWindowItem levantCmdItem1_800C2580[2];
extern MenuWindowItem levantCmdItem2_800C25B8[2];
extern MenuWindowItem levantCmdItem3_800C25F0[2];
extern MenuWindowItem levantCmdItem4_800C2628[2];
extern MenuWindowItem* levantCmdItems_800C2660[6];
extern MenuWindowItem minionCmdItem0_800C2678[2];
extern MenuWindowItem minionCmdItem1_800C26B0[2];
extern MenuWindowItem minionCmdItem2_800C26E8[2];
extern MenuWindowItem minionCmdItem3_800C2720[2];
extern MenuWindowItem* minionCmdItems_800C2758[5];
extern char keyItemsUpArrowPos_800C276C[4];
extern char keyItemsDownArrowPos_800C2770[4];
extern MenuWindowItem keyItemRow0_800C2774[3];
extern MenuWindowItem keyItemRow1_800C27C8[3];
extern MenuWindowItem keyItemRow2_800C281C[3];
extern MenuWindowItem keyItemRow3_800C2870[3];
extern MenuWindowItem* keyItemRows_800C28C4[5];
extern char helpBarParty_800C28D8[24];
extern char helpBarPartyList_800C28F0[32];
extern char helpBarTopList_800C2910[32];
extern char helpBarItems_800C2930[40];
extern char helpBarBack_800C2958[16];
extern char helpBarDescription_800C2968[24];
extern int minionListPage_800C2980;
extern char name_800C2984[8];
extern char levantHeaderRect_800C298C[8];
extern char levantSummaryRect_800C2994[12];
extern BattleDrop battleDrops_800C29A0[3];
extern int menuFromResults_800C29B8;
extern int leaveForest_800C29BC;


/* CONFIG / EQUIP overlays (loaded above MENU) */
extern void StartConfigMenu_800C2EB4(void);
extern void StartEquipMenu_800C47A8(); // MENU passes a 0 that it ignores
extern int IsConfigMenuActive_800C45D8(void);

/* GAME overlay (resident under MENU), to move to game.h */
extern MenuEnt battleEnemyResults_800B1238[]; // GAME's record of each enemy of the last battle (battle.h dword_800B1238)
extern int GetNthValuable_800AD7F8(int nth);
extern int RemoveInventory_800AD1E0(int id, int count, int table);
extern void RequestGameMode_800A6D30(int mode);
extern int sub_800B330C(); // called by DrawLevantWindow_800BECE4 (asm), not in GAME.SYM
extern int GetMoney_800AD02C();
extern void FireEventTriggerById_800A911C(int id);
extern int TestValuableFlag_800AD73C(int valuable);
extern int IsTriggerWaited_800A5E80(int trigger);
extern int GetLastInventorySlot_800AD308(int table);
extern int CountValuables_800AD79C();
extern void CompactInventory_800AD3F0(int table);
extern void SetFieldMode_800A7714(int mode);
extern int fieldMode_800B0EC0;
extern int IsSceneHeld_800A5E68(void);

/* exe-side, to move to <exe header> */
// = GetDominantSpecies_800338B0: rename once funcs.h declares it returning int (with its unsigned char return
// OnMinionLevelUp_800BCF74 gets an extra andi; the callee returns an lbu value either way)
extern void DrawUnitStatusWindow_8002F1C8();
extern void UseItemOnUnit_80013C28();
extern void DrawUiTiySprt_8002C06C();
extern unsigned short uiColor_8008B590;
extern void LoadUiTiy_8002BF74();
extern void AccumulateExpGain_800122A0();
extern void DrawMenuBackground_8002BE10();
extern int GetLevelRank_800121A8();
extern void FreeActiveOverlay_8002C014();
extern void DrawLevantSummary_8002E334();
extern void DrawLevantHeaderWindows_8002FD0C();
extern void DrawPartySlotWindow_8002F8E4();
extern void PlayMusic_800300E0();
extern int GetPartyWindowX_8002FA0C();
extern void DrawPortrait_8002A42C(short* p, int a, int b, short c);
extern void DrawLargeText_8002FBD8();
extern int GetRankName_8002FCD8();
extern void DrawUiWindow_8002A384();
extern void DrawSmallNumber3_8002C290();
extern void DrawScrollArrow_8002B3DC(MenuPair p, int t, void* pos, int ot);
extern void DrawMagicList_8002CAC8();
extern void DrawAbilityList_8002CE28();
extern void DrawItemList_8002C728();
extern void DrawFamilyTree_8002D7D0();
extern int DrawTargetSelectMenu_8002D250();
extern void DrawMpGauge_8002F120();
extern int DrawAbilityDescription_8002C670();
extern void DrawUnitStatusPanel_8002DB48();
extern void DrawAnimatedWindow_8002BEC8();
extern void DrawLargeNumber_8002C100();
extern void DrawLevantStats_8002F7D0();
extern int UpdateMenuCursor_8003D794();
extern void DrawScrollArrow_8002C6DC();

/* the jump table of CheckMenuAction_800BF540 (asm) and its targets, labels in the generated asm */

#endif
