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
#include "sound.h"
#include "shopctrl.h"
#include "main.h"
#include "menu_window.h"
#include "model_ftg.h"
#include "util.h"
#include "unit_query.h"
#include "event.h"
#include "movie.h"
#include "pad_text.h"
#include "cd.h"
#include "sound_seq.h"
#include "ui_sprites.h"
#include "menu_draw.h"
#include "effect.h"
#include "status_panel.h"

// the minion model of the shop's form view (LoadFormModel_800BF4B8 .. EndFormView_800BF750)
typedef struct ShopFormModel
{
    int task_0;        // StartModelTask_80010850 handle, -1: none
    Minion* minion_4;
    int desc_8[13];    // BuildFormModelDesc_800BF02C
    Actor* actor_3C;   // SpawnFormActor_800BF574
} ShopFormModel;


// a line of the shopkeeper's dialog window (DrawTextList_8002A310)
typedef struct ShopTextLine
{
    int pos_0; // x | y << 16
    const char* text_4;
} ShopTextLine;

typedef struct ShopElementOrder
{
    int order[4];
} ShopElementOrder;


// work area of the shop menu task (EventEntry.buffer)
typedef struct ShopMenu
{
    short state_0; // 0 main menu, 1 merge base, 2 merge partner, 3 merge confirm, 4 merge again, 5 spin select,
                   // 6 spin confirm, 7 party, 8 view, 9 rename, 10 exchange, 11 quit, 12 storage full, 13 skin ask,
                   // 14 skin pick, 15 stats
    short prevState_2;
    short storedCount_4; // minions/cocoons in storage (state 2)
    short partyCount_6;  // state 3
    short errorId_8;     // CheckShopSelection_800BCF74 result shown by SetShopHelpText_800BBB54(u, 1)
    short pad_A;
    short openTimer_C;   // window open animation, 0..8
    short pad_E;
    int confirm_10;
    int cancel_14;
    int messageShown_18; // ShopWaitMessage_800BBA3C
    unsigned int windows_1C;     // stateWindows_800BF8B4 bits
    unsigned int windowsOpen_20; // windows that finished opening
    int flags_24; // 1 recount, 2 prompt shown, 4 quitting, 8 party + stored lists, 0x10 party list active,
                  // 0x20 form view, 0x40/0x80/0x100 ability/magic/family tree page, 0x200 skin chosen,
                  // 0x400 stats view, 0x800 fading, 0x1000 description shown
    // MenuCursor (UpdateMenuCursor_8003D794) of the minion lists
    short listCols_28;
    short listRows_2A;
    short listCount_2C;
    short listFlags_2E;
    short listIndex_30;
    short listScroll_32;
    // MenuCursor of the merge preview (0 base, 1 partner, 2 result)
    short tabCols_34;
    short tabRows_36;
    short tabCount_38;
    short tabFlags_3A;
    short tabIndex_3C;
    short tabScroll_3E;
    // MenuCursor of the ability / magic page
    short pageCols_40;
    short pageRows_42;
    short pageCount_44;
    short pageFlags_46;
    short pageIndex_48;
    short pageScroll_4A;
    Minion* base_4C;    // the chosen minion (merge base, ...)
    Minion* partner_50; // the second minion (merge partner, exchange)
    Minion* shown_54;   // the minion the status panel shows
    unsigned short partyIndex_58;
    unsigned short storedIndex_5A;
    unsigned short storedScroll_5C;
    short savedIndex_5E[10]; // per stateIndexSlots_800BFD1C
    short savedScroll_72[4]; // per stateScrollSlots_800BFD3C
    short savedList_7A[2];   // per stateListSlots_800BFD5C
    short list_7E; // 0 party list, 1 stored list
    short markCount_80;
    short pad_82;
    int marks_84;       // marked entries: party 0..2, stored from 3
    int partyMarks_88;
    int storedMarks_8C;
    int field_90;
    short fadeAction_94; // 1 merge, 2 spin
    short shopId_96;     // 4: the first shopkeeper's texts (stateTextsA_800BFAB4), else stateTextsB_800BFAF4
    short messageTimer_98;
} ShopMenu;

typedef struct FormActorDesc
{
    int modelId_0; // the CreateActor_8001D45C ActorDesc without hasMatrices_4C
    int kind_4;
    int posX_8;
    int posY_C;
    int posZ_10;
    short rotX_14;
    short rotY_16;
    short rotZ_18;
    short pad_1A;
    int clutRow_1C;
    int animIdx_20;
    int frame_24;
    int frameSpeed_28;
    int blendDiv_2C;
    int visible_30;
    int bones_34;
    int baseScale_38;
    int boneScale_3C;
    int anims_40;
    int effectTbl_44;
    int model_48;
} FormActorDesc;

typedef struct ShopPos
{
    short x;
    short y;
} ShopPos;


typedef struct ShopPair
{
    short a;
    short b;
} ShopPair;

// (o[4] += o[6]) and reloads o[6] in the o[2] != o[3] case; here the two tails get different registers.
typedef struct TopSpeciesBuf
{
    unsigned char b[4];
    int pad_4;
    int w[3];
} TopSpeciesBuf;

/* SHOP functions */
int CompactStoredMinions_800B97B0(void);
int FindStoredMinion_800B9888(short i);
int BuildShopMinionList_800B9920(void);
void ClearShopMinion_800B9B20(int i);
void SetMinionEmpty_800B9B44(short* state);
Minion* GetNthShopMinion_800B9B50(int state, int n);
int GetShopMinionState_800B9C10(int i);
short* GetShopMinionAncestors_800B9C34(int i);
char* GetMinionAncestors_800B9C54(char* minion);
Minion* GetShopMinion_800B9C5C(int i);
int CountShopMinionsInState_800B9C78(int state);
int SetMinionInParty_800B9CCC(short* state);
int MoveShopMinionToParty_800B9CDC(int i);
int SetMinionStored_800B9D48(short* state);
int MoveShopMinionToStorage_800B9D6C(int i);
int CommitShopMinionList_800B9DA8(void);
int UnitStatsToMinion_800B9E94(UnitStats* src, Minion* dst, short state);
int MergeMinions_800B9FC8(Minion* base, Minion* partner, Minion* out, int person);
void ClearMinion_800BA340(unsigned int* minion);
void InheritMergeStats_800BA368(Minion* out, Minion* src);
void MergeBaseStats_800BA3C8(unsigned char* out, unsigned char* base, unsigned char* partner);
unsigned char MergeBaseStat_800BA46C(unsigned char base, unsigned char partner);
void MergeResistances_800BA4CC(Minion* out, Minion* base, Minion* partner);
void ApplyMergeStatBonus_800BA650(Minion* out);
void MergeExp_800BA6D0(Minion* out, Minion* base, Minion* partner);
void MergeSkills_800BA72C(Minion* out, Minion* partner);
void MergeMagic_800BAA0C(Minion* out, Minion* partner);
int CanInheritMagic_800BAB30(Minion* minion);
void MergeSpeciesHistory_800BAB38(Minion* out, Minion* partner);
int GetSpecialMergeSpecies_800BACD0(Minion* minion);
int GetSilkItemForLevel_800BAE80(Minion* minion);
void SwapMinions_800BAEDC(Minion* first, Minion* second);
int ExchangeMinions_800BAF54(short* first, short* second, short firstList, short secondList);
void StartShop_800BB058(int shopId);
void ShopFadeIn_800BB0F8(EventEntry* task, void* buffer);
void InitShopMenu_800BB148(ShopMenu* menu);
int CanViewForm_800BB38C(ShopMenu* menu);
int CanRearrange_800BB3E8(ShopMenu* menu);
void ShopMenuTask_800BB444(EventEntry* task, void* buffer);
void SaveShopCursor_800BB798(ShopMenu* menu);
void RestoreShopCursor_800BB828(ShopMenu* menu);
void ShopMenuBack_800BB8C4(ShopMenu* menu);
void ShopWaitMessage_800BBA3C(ShopMenu* menu);
void UpdateMainMenuHelp_800BBAAC(ShopMenu* menu);
void SetShopHelpText_800BBB54(ShopMenu* menu, int mode);
void ShopMenuInput_800BBE24(ShopMenu* menu);
void CycleInfoPage_800BC1A8(ShopMenu* menu);
void DismissShopPrompt_800BC2DC(ShopMenu* menu);
void DrawShopMenu_800BC380(ShopMenu* menu);
void DrawShopButtonHelp_800BCCD8(ShopMenu* menu);
void DrawShopMainMenu_800BCEDC(ShopMenu* menu);
int CheckShopSelection_800BCF74(ShopMenu* menu);
void HandleShopConfirmCancel_800BD0D4(ShopMenu* menu);
int IsMergePreviewState_800BD650(short* state);
int IsMinionListState_800BD678(ShopMenu* menu);
int IsNoChosen_800BD6C4(ShopMenu* menu);
void PreviewMerge_800BD720(ShopMenu* menu);
void SetShopWindows_800BD7A8(ShopMenu* menu);
void SetupShopCursor_800BD854(ShopMenu* menu);
void ShopMenuExecute_800BD9DC(ShopMenu* menu);
void ShopWaitAreaReload_800BDD74(EventEntry* task, void* arg);
void ShopWaitDarken_800BDE44(EventEntry* task, void* buffer);
void ShopWaitBrighten_800BDEA8(EventEntry* task, void* buffer);
void ShopResumeAfterSpin_800BE07C(EventEntry* task, void* buffer);
void ShopResumeAfterNameEntry_800BE128(EventEntry* task, void* buffer);
void ShopWaitUiTiy_800BE210(EventEntry* task, void* buffer);
void ShopFadeInMenu_800BE264(EventEntry* task, void* buffer);
void StartFormView_800BE2B4(Minion* minion);
void FormViewTask_800BE334(EventEntry* task, void* buffer);
void FormViewLoadTask_800BE4D0(EventEntry* task, void* buffer);
void DrawPartyList_800BE53C(ShopMenu* menu);
void DrawStoredList_800BE7F0(ShopMenu* menu);
int GetStoredListScroll_800BEB60(ShopMenu* menu);
void UpdateSelectedMinions_800BEBC8(ShopMenu* menu);
void UpdateShownMinion_800BECC8(ShopMenu* menu);
void DrawSkinList_800BED48(short* ref);
void BuildFormModelDesc_800BF02C(Minion* minion, int* desc, int c);
int GetElementHue_800BF2E4(unsigned char* elements);
int ElementMixAngle_800BF3B4(unsigned char* elements);
void ResetFormModel_800BF474(void);
void FreeFormModel_800BF484(void);
void LoadFormModel_800BF4B8(Minion* minion);
int RunFormModelTask_800BF520(void);
void FreeFormModelTask_800BF548(void);
void SpawnFormActor_800BF574(int* pos, unsigned short* rot);
void DestroyFormActor_800BF6C4(void);
void ShowFormActor_800BF704(int shopId);
void EndFormView_800BF750(void);
Actor* GetFormActor_800BF780(void);

/* SHOPCTRL.BIN (loaded below SHOP.BIN) and the exe functions both use: see shopctrl.h */

/* GAME.BIN (resident field overlay), to move to game.h */
void ExchangeEventResult_800A5F9C(int a);
void AddInventory_800AD184(int a, int b, int c);
void RemoveInventory_800AD1E0(int a, int b, int c);
int GetLastInventorySlot_800AD308(int a);
int IsInventory4NonEmpty_800AD398();
void CompactInventory_800AD3F0(int a);
int GetFreeCocoonSlots_800AD888();
void AddEmptyCocoons_800AD8F4(int a);

/* exe-side, to move to <exe header> (named in the comment) */
extern char defaultBones_80079140[];
extern short sinTable_80084540[];        // data_decls.h
extern Minion name_8008EF18[];
int StartModelTask_80010850(void* p);     // party.h
int fn_80010A44(int a);                   // party.h
void fn_80011CD0(UnitStatus* p);          // unit_stats.h
int ApplyLevelUps_80011D98(UnitStatus* a, int b); // unit_stats.h
void fn_80019B14(int a, int b, int c);    // minion_init.h
void StartSceneDarken_8001AAA8(int a);    // engine.h
void StartSceneBrighten_8001AB1C(int a);  // engine.h
void fn_8001ABEC(int a);                  // engine.h
void* fn_8001D45C(void* p);               // engine.h (CreateActor)
void fn_8001D68C(void* p, int on);        // engine.h
int fn_80024E38(int a);                   // model_ftg
int fn_80024E64(int a);                   // model_ftg
int fn_80024E90(int a, int b);            // model_ftg
int fn_80024EC8(int a, int b);            // model_ftg
int fn_80024F00(int a, int b);            // model_ftg
int fn_80024F38(int a, int b);            // model_ftg
void DrawTextList_8002A310(void* p, int a);          // menu_draw.h
void DrawPortraitWindow_8002A4E4(int a);             // menu_draw.h
void DrawScrollArrow_8002B3DC(ShopPair p, int b, void* c, int d); // ui_gauge
void DrawAbilityList_8002CE28(ListMenuState* ref, ShopPos* pos); // ability_menu
void DrawFamilyTree_8002D7D0(Minion* m, int ot, ShopPos* base); // family_tree.h
void DrawSmallText_8002FAA0(int align, unsigned short* pos, char* name, int ot); // party_window.h
void* memset(void* p, int c, unsigned int n);        // libc

/* SHOP data */
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
extern const MenuWindowList mainMenuWindow_800B9608;
extern const int dword_800B9620;
extern const int dword_800B96F0;
extern const MenuWindowList minionListWindow_800B971C;
extern RECT statusWindowRect_800BF790;
extern RECT dialogWindowRect_800BF798;
extern RECT partyLabelRect_800BF7A0;
extern RECT storedLabelRect_800BF7A8;
extern RECT mergeSlotRects_800BF7B0[3];
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
extern const char *textStatsReturnA_800BF9B8[3];
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
extern const char *textStatsReturnB_800BFAA8[3];
extern const char **stateTextsA_800BFAB4[16];
extern const char **stateTextsB_800BFAF4[16];
extern const char **resultTextsA_800BFB34[16];
extern const char **resultTextsB_800BFB74[21];
extern const char *errNoneA_800BFBC8[3];
extern const char *errNeedTwoA_800BFBD4[3];
extern const char *errNoMinionsA_800BFBE0[3];
extern const char *errCantUseA_800BFBEC[3];
extern const char *errNoSkinsA_800BFBF8[3];
extern const char **errorTextsA_800BFC04[10];
extern const char *errNoneB_800BFC2C[3];
extern const char *errNeedTwoB_800BFC38[3];
extern const char *errNoMinionsB_800BFC44[3];
extern const char *errCantUseB_800BFC50[3];
extern const char *errNoSkinsB_800BFC5C[3];
extern const char **errorTextsB_800BFC68[5];
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
extern const char **mainHelpTextsA_800BFCF4[5];
extern const char **mainHelpTextsB_800BFD08[5];
extern short stateIndexSlots_800BFD1C[16];
extern unsigned short stateScrollSlots_800BFD3C[16];
extern unsigned short stateListSlots_800BFD5C[16];
extern MenuWindowItem partyListItem0_800BFD7C[2];
extern MenuWindowItem partyListItem1_800BFDB4[2];
extern MenuWindowItem partyListItem2_800BFDEC[2];
extern MenuWindowItem *partyListItems_800BFE24[4];
extern MenuWindowItem storedListItem0_800BFE34[2];
extern MenuWindowItem storedListItem1_800BFE6C[2];
extern MenuWindowItem storedListItem2_800BFEA4[2];
extern MenuWindowItem storedListItem3_800BFEDC[2];
extern MenuWindowItem *storedListItems_800BFF14[5];
extern ButtonHelpEntry btnHelpSpinMarked_800BFF28[4];
extern ButtonHelpEntry btnHelpSpin_800BFF48[5];
extern ButtonHelpEntry btnHelpPartner_800BFF70[4];
extern ButtonHelpEntry btnHelpView_800BFF90[5];
extern ButtonHelpEntry btnHelpMergePreview_800BFFB8[5];
extern ButtonHelpEntry btnHelpFormView_800BFFE0[4];
extern ButtonHelpEntry btnHelpStats_800C0000[3];
extern ButtonHelpEntry btnHelpStatsPage_800C0018[4];
extern ButtonHelpEntry btnHelpPrompt_800C0038[2];
extern ButtonHelpEntry btnHelpSelect_800C0048[5];
extern ButtonHelpEntry btnHelpExchange_800C0070[4];
extern char skinListUpArrowPos_800C0090[4];
extern char skinListDownArrowPos_800C0094[4];
extern MenuWindowItem skinListRow0_800C0098[4];
extern MenuWindowItem skinListRow1_800C0108[4];
extern MenuWindowItem skinListRow2_800C0178[4];
extern MenuWindowItem skinListRow3_800C01E8[4];
extern MenuWindowItem *skinListRows_800C0258[5];
extern const char *magicDescLines_800C026C[30][4];
extern const char *abilityDescLines_800C044C[39][4];
extern MenuWindowItem mainMenuItem0_800C06BC[2];
extern MenuWindowItem mainMenuItem1_800C06F4[2];
extern MenuWindowItem mainMenuItem2_800C072C[2];
extern MenuWindowItem mainMenuItem3_800C0764[2];
extern MenuWindowItem mainMenuItem4_800C079C[2];
extern char mainMenuItems_800C07D4[28];
extern unsigned int emptyMinion_800C07F0[62];
extern Minion mergePreview_800C08E8;
extern ShopFormModel formModel_800C09E0;

/* the jump table of MergeSkills_800BA72C (asm) and its targets, labels in the generated asm */
extern char jtgt_800BA8A4[], jtgt_800BA8AC[], jtgt_800BA8B4[], jtgt_800BA8BC[], jtgt_800BA8C8[], jtgt_800BA910[], jtgt_800BA918[], jtgt_800BA920[], jtgt_800BA928[], jtgt_800BA958[];
extern void* const jpt_800B6D4C[12];



#endif
