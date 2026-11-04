// SHOP.BIN: declarations shared by its source files
#ifndef _SHOP_H_
#define _SHOP_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "actor.h"
#include "engine.h"
#include "minion_menu.h"
#include "tiy.h"

// the minion model of the shop's form view (LoadFormModel_800BF4B8 .. EndFormView_800BF750)
typedef struct ShopFormModel
{
    int task_0;        // StartModelTask_80010850 handle, -1: none
    Minion* minion_4;
    int desc_8[13];    // BuildFormModelDesc_800BF02C
    Actor* actor_3C;   // SpawnFormActor_800BF574
} ShopFormModel;

// DrawMenuWindows_8002A5A4's parameter block (struct_A5A4 in menu_draw.c)
typedef struct ShopMenuWindows
{
    int flags_0;
    int time_4;
    int open_8;   // open animation step, 8: open
    int cursor_C; // highlighted item, -1: none
    int items_10; // ShopMenuItem* list
    int ot_14;
} ShopMenuWindows;

// a line of the shopkeeper's dialog window (DrawTextList_8002A310)
typedef struct ShopTextLine
{
    int pos_0; // x | y << 16
    int text_4;
} ShopTextLine;

typedef struct ShopElementOrder
{
    int order[4];
} ShopElementOrder;

typedef struct ShopRect
{
    short x;
    short y;
    short w;
    short h;
} ShopRect;

// a menu item of DrawMenuWindows_8002A5A4 (struct_A5A4_item)
typedef struct ShopMenuItem
{
    unsigned short flags_0; // 0x40: greyed out
    short pad_2;
    int val_4;   // sprite / text / number, by kind
    void* sprts_8;
    void* tpages_C;
    short x_10;
    short y_12;
    int pad_14;
    int pad_18;
} ShopMenuItem;

extern int dword_800B6D00;
extern const char aAssertFmt_800B6D04[];
extern const char aCmpactC_800B6D2C[];
extern const ShopElementOrder elementOrder_800B6D38;
extern const int dword_800B6D48;
extern const char aEmpty_800B6D7C[4];
extern const char aWhatDoYouWantTo_800B6D80[];
extern const char aForTheNewMinion_800B6DB0[];
extern const char aPickTheCocoonTo_800B6DD8[];
extern const char aIllSpinThemO_800B6E18[];
extern const char aToSpinWithX_800B6E5C[];
extern const char aPickTheCocoonsY_800B6E7C[];
extern const char aToMixWithIt_800B6EB8[];
extern const char aPickTheMinionYo_800B6ED8[];
extern const char aNo_800B6F0C[];
extern const char aYes_800B6F14[];
extern const char aOKIfISpinThisCo_800B6F20[];
extern const char aToEquipAndTakeW_800B6F54[];
extern const char aChooseTheThreeM_800B6F8C[];
extern const char aOKIfIMergeThem_800B6FD0[];
extern const char aWannaTryMerging_800B6FF8[];
extern const char aSqViewOtherAbilities_800B7034[];
extern const char aOViewMinionsForm_800B7064[];
extern const char aXRenameTriQuit_800B7090[];
extern const char aRenameThisMinio_800B70C4[];
extern const char aPickTheMinionsT_800B70EC[];
extern const char aSeeYaNextTime_800B7128[];
extern const char aIMAllDoneForNow_800B714C[];
extern const char aICanSpinToGetRi_800B7178[];
extern const char aICanTStoreAnyMo_800B71B8[];
extern const char aOhIMSorryIMAllO_800B71F8[];
extern const char aWannaUseTheMini_800B7240[];
extern const char aPickTheSkinYouW_800B727C[];
extern const char aTheSqButton_800B72AC[];
extern const char aYouCanViewOther_800B72C8[];
extern const char aOViewForm_800B7304[];
extern const char aThisIsWhatItLlL_800B7320[];
extern const char aYouCanSellThisA_800B735C[];
extern const char aOkayIHaveSpunSo_800B73AC[];
extern const char aIfWeUseThem_800B7400[];
extern const char aSomethingExciti_800B7420[];
extern const char aISeeYouHaveSome_800B7460[];
extern const char aTheTriButton_800B74A4[];
extern const char aYouCanReturnToS_800B74C0[];
extern const char aWhatDoYouWishTo_800B750C[];
extern const char aPleasePickTheCo_800B753C[];
extern const char aPleasePickTheCo_800B7588[];
extern const char aToMixItWith_800B75D0[];
extern const char aPleasePickTheMi_800B75F0[];
extern const char aMayISpinThisMin_800B7630[];
extern const char aTakeWithYou_800B7660[];
extern const char aChooseUpToThree_800B7680[];
extern const char aShallIMergeThem_800B76BC[];
extern const char aShallWeMergeSom_800B76E4[];
extern const char aPleasePickTheMi_800B7728[];
extern const char aMyWorkIsComplet_800B7774[];
extern const char aCanTStoreAnyMor_800B77B0[];
extern const char aIMAllOutOfSpace_800B77EC[];
extern const char aDoYouWantToUseT_800B7820[];
extern const char aPleasePickTheSk_800B7870[];
extern const char aToViewOtherStat_800B78B0[];
extern const char aUseTheSqButton_800B78DC[];
extern const char aItAtTheVillageS_800B7900[];
extern const char aYouCanGetMoneyB_800B7934[];
extern const char aIHaveSpunSomeSh_800B7970[];
extern const char aIfWeUseThem_800B79B8[];
extern const char aSomethingExtrao_800B79D8[];
extern const char aReturnToTheStat_800B7A24[];
extern const char aUseTheTriButtonTo_800B7A60[];
extern const char aNoSkinsJp_800B7A88[];
extern const char aCantChooseJp_800B7A9C[];
extern const char aNoMinionsJp_800B7AB4[];
extern const char aNeedTwoJp_800B7AC8[];
extern const char aMinions_800B7AE4[];
extern const char aICanTMergeUnles_800B7AF8[];
extern const char aWeDonTHaveAnyMi_800B7B3C[];
extern const char aWeCanTUseThatMi_800B7B74[];
extern const char aWeDonTHaveAnyMi_800B7BA8[];
extern const char aNoSkinsJp2_800B7BE8[];
extern const char aCantChooseJp2_800B7C00[];
extern const char aNoMinionsJp2_800B7C18[];
extern const char aNeedTwoJp2_800B7C30[];
extern const char aThereArenTAnyMi_800B7C50[];
extern const char aThereArenTAnyMi_800B7C84[];
extern const char aForYou_800B7CC4[];
extern const char aCombineThemAndC_800B7CD8[];
extern const char aIfYouSelectTwoM_800B7D1C[];
extern const char aYouCanSellItInT_800B7D60[];
extern const char aIfYouSpinTheCoc_800B7DAC[];
extern const char aWithUpToThreeCo_800B7DF0[];
extern const char aYouCanEquipYour_800B7E24[];
extern const char aCreaturesYouHav_800B7E54[];
extern const char aYouCanRenameAnd_800B7E90[];
extern const char aStopPerformingD_800B7EC8[];
extern const char aMergeThemAndCre_800B7F14[];
extern const char aCocoonsIntoSilk_800B7F54[];
extern const char aYouCanGetMoneyB_800B7FA0[];
extern const char aYouCanChangeThe_800B7FDC[];
extern const char aForNow_800B801C[];
extern const char aStopPerformingD_800B8030[];
extern const char aSpin_800B806C[];
extern const char aQuit_800B8078[];
extern const char aSelect_800B8084[];
extern const char aViewForm_800B8094[];
extern const char aRearrange_800B80A8[];
extern const char aViewOtherAbilit_800B80BC[];
extern const char aRename_800B80E8[];
extern const char aCombine_800B80F8[];
extern const char aZoom_800B8108[];
extern const char aDescription_800B8114[];
extern const char aEffectivenessOf_800B812C[];
extern const char aIncreasesWindAt_800B818C[];
extern const char aEnhanceWind_800B81E0[];
extern const char aEffectivenessOf_800B81FC[];
extern const char aIncreasesEarthA_800B825C[];
extern const char aEnhanceEarth_800B82B4[];
extern const char aEffectivenessOf_800B82D0[];
extern const char aIncreasesWaterA_800B832C[];
extern const char aEnhanceWater_800B8384[];
extern const char aEffectivenessOf_800B83A0[];
extern const char aIncreasesFireAt_800B83FC[];
extern const char aEnhanceFire_800B8450[];
extern const char aCausesAnEnemyTo_800B846C[];
extern const char aDeath_800B84C0[];
extern const char aTurnsAnEnemyInt_800B84CC[];
extern const char aFleshToStone_800B8504[];
extern const char aPutsAnEnemyToSl_800B8524[];
extern const char aSleep_800B8554[];
extern const char aPoisonsAnEnemy_800B8560[];
extern const char aPoison_800B8584[];
extern const char aEndsOnceItProte_800B8594[];
extern const char aProtectsAgainst_800B85E8[];
extern const char aProtection_800B8650[];
extern const char aCuresPoisonAndT_800B8668[];
extern const char aReturnToNormal_800B86C0[];
extern const char aRestoresAllHP_800B86E4[];
extern const char aRestoreAllHP_800B8708[];
extern const char aRestoresSomeHP_800B8728[];
extern const char aRestoreHP_800B874C[];
extern const char aCuresPoison_800B8764[];
extern const char aCurePoison_800B8780[];
extern const char aAdvancedWindAtt_800B8798[];
extern const char aWindAttackAllEn_800B87C4[];
extern const char aHigherWindEleme_800B87F8[];
extern const char aExtraDamageVsEa_800B8854[];
extern const char aWindAttackOneEn_800B8884[];
extern const char aAdvancedEarthAt_800B88B4[];
extern const char aEarthAttackAllE_800B88E0[];
extern const char aHigherEarthElem_800B8918[];
extern const char aExtraDamageVsWa_800B8978[];
extern const char aEarthAttackOneE_800B89A8[];
extern const char aAdvancedWaterAt_800B89DC[];
extern const char aWaterAttackAllE_800B8A08[];
extern const char aHigherWaterElem_800B8A40[];
extern const char aExtraDamageVsFi_800B8AA0[];
extern const char aWaterAttackOneE_800B8ACC[];
extern const char aAdvancedFireAtt_800B8B00[];
extern const char aFireAttackAllEn_800B8B2C[];
extern const char aHigherFireEleme_800B8B60[];
extern const char aExtraDamageVsAi_800B8BBC[];
extern const char aFireAttackOneEn_800B8BE8[];
extern const char aMakesItEasierTo_800B8C18[];
extern const char aSpecialAttackBr_800B8C70[];
extern const char aSlightlyMoreDif_800B8CAC[];
extern const char aMakesItEasierTo_800B8D10[];
extern const char aSpecialAttackBr_800B8D70[];
extern const char aItMoreDifficult_800B8DA8[];
extern const char aReducesAnEnemie_800B8E00[];
extern const char aSpecialAttackCr_800B8E4C[];
extern const char aBringsEnemiesTo_800B8E88[];
extern const char aAttacksAllEnemi_800B8ED4[];
extern const char aSpecialAttackAl_800B8F10[];
extern const char aUsesItToRestore_800B8F4C[];
extern const char aStealsSomeManaF_800B8F94[];
extern const char aSpecialAttackAb_800B8FDC[];
extern const char aAnEnemyToRestor_800B9018[];
extern const char aTakesSomeOfTheD_800B9068[];
extern const char aSpecialAttackAb_800B90B4[];
extern const char aMoreDifficultFo_800B90EC[];
extern const char aCausesAnEnemyTo_800B913C[];
extern const char aSpecialAttackDe_800B91A4[];
extern const char aPhysicallyDamag_800B91E0[];
extern const char aSpecialFleshToS_800B924C[];
extern const char aPhysicallyDamag_800B9288[];
extern const char aSpecialSleepAtt_800B92F0[];
extern const char aPhysicallyDamag_800B931C[];
extern const char aSpecialPoisonAt_800B9370[];
extern const char aVeryEffectiveAg_800B939C[];
extern const char aSpecialWindAtta_800B93F4[];
extern const char aVeryEffectiveAg_800B941C[];
extern const char aSpecialFireAtta_800B9474[];
extern const char aVeryEffectiveAg_800B949C[];
extern const char aSpecialWaterAtt_800B94F4[];
extern const char aVeryEffectiveAg_800B9520[];
extern const char aSpecialEarthAtt_800B9578[];
extern const ShopMenuWindows mainMenuWindow_800B9608;
extern const int dword_800B9620;
extern const int dword_800B96F0;
extern const ShopMenuWindows minionListWindow_800B971C;
extern ShopRect statusWindowRect_800BF790;
extern ShopRect dialogWindowRect_800BF798;
extern ShopRect partyLabelRect_800BF7A0;
extern ShopRect storedLabelRect_800BF7A8;
extern ShopRect mergeSlotRects_800BF7B0[3];
extern ShopTextLine dialogLines_800BF7C8[4];
extern unsigned short stateCursors_800BF7E8[16][4];
extern short stateConfirmNext_800BF868[16];
extern unsigned short stateParents_800BF888[16];
extern short mainMenuStates_800BF8A8[6];
extern short stateWindows_800BF8B4[16];
extern const char *textMainA_800BF8D4[3];
extern const char *textMergeBaseA_800BF8E0[3];
extern const char *textSpinSelectA_800BF8EC[3];
extern const char *textMergePartnerA_800BF8F8[3];
extern const char *textSpinConfirmA_800BF904[3];
extern const char *textPartyA_800BF910[3];
extern const char *textMergeConfirmA_800BF91C[3];
extern const char *textMergeAgainA_800BF928[3];
extern const char *textViewA_800BF934[3];
extern const char *textRenameA_800BF940[3];
extern const char *textExchangeA_800BF94C[3];
extern const char *textQuitA_800BF958[3];
extern const char *textFullA_800BF964[3];
extern const char *textSkinAskA_800BF970[3];
extern const char *textSkinPickA_800BF97C[3];
extern const char *textStatsA_800BF988[3];
extern const char *textMergePreviewA_800BF994[3];
extern const char *textSpunA_800BF9A0[3];
extern const char *textSkinIntroA_800BF9AC[3];
extern int textStatsReturnA_800BF9B8[3];
extern const char *textMainB_800BF9C4[3];
extern const char *textMergeBaseB_800BF9D0[3];
extern const char *textSpinSelectB_800BF9DC[3];
extern const char *textMergePartnerB_800BF9E8[3];
extern const char *textSpinConfirmB_800BF9F4[3];
extern const char *textPartyB_800BFA00[3];
extern const char *textMergeConfirmB_800BFA0C[3];
extern const char *textMergeAgainB_800BFA18[3];
extern const char *textViewB_800BFA24[3];
extern const char *textRenameB_800BFA30[3];
extern const char *textExchangeB_800BFA3C[3];
extern const char *textQuitB_800BFA48[3];
extern const char *textFullB_800BFA54[3];
extern const char *textSkinAskB_800BFA60[3];
extern const char *textSkinPickB_800BFA6C[3];
extern const char *textStatsB_800BFA78[3];
extern const char *textMergePreviewB_800BFA84[3];
extern const char *textSpunB_800BFA90[3];
extern const char *textSkinIntroB_800BFA9C[3];
extern int textStatsReturnB_800BFAA8[3];
extern int *stateTextsA_800BFAB4[16];
extern int *stateTextsB_800BFAF4[16];
extern int *resultTextsA_800BFB34[16];
extern int *resultTextsB_800BFB74[21];
extern const char *errNoneA_800BFBC8[3];
extern const char *errNeedTwoA_800BFBD4[3];
extern const char *errNoMinionsA_800BFBE0[3];
extern const char *errCantUseA_800BFBEC[3];
extern const char *errNoSkinsA_800BFBF8[3];
extern int *errorTextsA_800BFC04[10];
extern const char *errNoneB_800BFC2C[3];
extern const char *errNeedTwoB_800BFC38[3];
extern const char *errNoMinionsB_800BFC44[3];
extern const char *errCantUseB_800BFC50[3];
extern const char *errNoSkinsB_800BFC5C[3];
extern int *errorTextsB_800BFC68[5];
extern const char *helpMergeA_800BFC7C[3];
extern const char *helpSpinA_800BFC88[3];
extern const char *helpPartyA_800BFC94[3];
extern const char *helpRenameA_800BFCA0[3];
extern const char *helpQuitA_800BFCAC[3];
extern const char *helpMergeB_800BFCB8[3];
extern const char *helpSpinB_800BFCC4[3];
extern const char *helpPartyB_800BFCD0[3];
extern const char *helpRenameB_800BFCDC[3];
extern const char *helpQuitB_800BFCE8[3];
extern int *mainHelpTextsA_800BFCF4[5];
extern int *mainHelpTextsB_800BFD08[5];
extern short stateIndexSlots_800BFD1C[16];
extern unsigned short stateScrollSlots_800BFD3C[16];
extern unsigned short stateListSlots_800BFD5C[16];
extern int partyListItem0_800BFD7C[14];
extern int partyListItem1_800BFDB4[14];
extern int partyListItem2_800BFDEC[14];
extern char partyListItems_800BFE24[16];
extern int storedListItem0_800BFE34[14];
extern int storedListItem1_800BFE6C[14];
extern int storedListItem2_800BFEA4[14];
extern int storedListItem3_800BFEDC[14];
extern char storedListItems_800BFF14[20];
extern char btnHelpSpinMarked_800BFF28[32];
extern char btnHelpSpin_800BFF48[40];
extern char btnHelpPartner_800BFF70[32];
extern char btnHelpView_800BFF90[40];
extern char btnHelpMergePreview_800BFFB8[40];
extern char btnHelpFormView_800BFFE0[32];
extern char btnHelpStats_800C0000[24];
extern char btnHelpStatsPage_800C0018[32];
extern char btnHelpPrompt_800C0038[16];
extern char btnHelpSelect_800C0048[40];
extern char btnHelpExchange_800C0070[32];
extern char skinListUpArrowPos_800C0090[4];
extern char skinListDownArrowPos_800C0094[4];
extern int skinListRow0_800C0098[28];
extern int skinListRow1_800C0108[28];
extern int skinListRow2_800C0178[28];
extern int skinListRow3_800C01E8[28];
extern ShopMenuItem *skinListRows_800C0258[5];
extern char magicDescLines_800C026C[30][16];
extern char abilityDescLines_800C044C[624];
extern int mainMenuItem0_800C06BC[14];
extern int mainMenuItem1_800C06F4[14];
extern int mainMenuItem2_800C072C[14];
extern int mainMenuItem3_800C0764[14];
extern int mainMenuItem4_800C079C[14];
extern char mainMenuItems_800C07D4[28];
extern unsigned int emptyMinion_800C07F0[62];
extern Minion mergePreview_800C08E8;
extern ShopFormModel formModel_800C09E0;

/* the jump table of MergeSkills_800BA72C (asm) and its targets, labels in the generated asm */
extern char jtgt_800BA8A4[], jtgt_800BA8AC[], jtgt_800BA8B4[], jtgt_800BA8BC[], jtgt_800BA8C8[], jtgt_800BA910[], jtgt_800BA918[], jtgt_800BA920[], jtgt_800BA928[], jtgt_800BA958[];
extern void* const jpt_800B6D4C[12];

/* the jump table of CheckShopSelection_800BCF74 (asm) and its targets, labels in the generated asm */
extern char jtgt_800BCFF4[], jtgt_800BD01C[], jtgt_800BD03C[], jtgt_800BD06C[], jtgt_800BD090[], jtgt_800BD0C0[];
extern void* const jpt_800B9624[14];

/* the jump table of ShopMenuExecute_800BD9DC (asm) and its targets, labels in the generated asm */
extern char jtgt_800BDA34[], jtgt_800BDB4C[], jtgt_800BDC7C[], jtgt_800BDCEC[], jtgt_800BDD40[], jtgt_800BDD54[], jtgt_800BDD58[];
extern void* const jpt_800B96F4[10];

#endif
