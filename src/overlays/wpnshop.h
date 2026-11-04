// WPNSHOP.BIN: declarations shared by its source files
#ifndef _WPNSHOP_H_
#define _WPNSHOP_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "tiy.h"
#include "sound.h"
#include "main.h"

// DrawMenuWindows_8002A5A4's parameter block (MenuWindowList in menu_draw.c)
typedef struct StoreMenuWindows
{
    int flags_0;
    int time_4;
    int open_8;
    int cursor_C;
    int items_10;
    int ot_14;
} StoreMenuWindows;

// a list panel of the store (StoreMenu.panel_34)
typedef struct StorePanel
{
    unsigned short* cursor_0; // MenuCursor setup: columns, rows, count, flags
    char pad_4[16];
} StorePanel;

typedef struct StoreMenuItem
{
    unsigned short flags_0; // 2: price too high, 0x40: empty row
    short pad_2;
    int value_4; // icon, name text, price
    char pad_8[0x14];
} StoreMenuItem;

// work area of the store task (EventEntry.buffer)
typedef struct StoreMenu
{
    short state_0; // 0 item main, 1 equipment main, 2/3 item buy/sell list, 4/5 equipment buy/sell list,
                   // 6/7 equipment kind for buy/sell, 8/9 equipment buy/sell count, 10/11 item buy/sell count,
                   // 12/13 equipment buy/sell confirm, 14/15 item buy/sell confirm, 16 ready it now?, 17 readied,
                   // 18 ready it later
    short nextState_2; // -1: none (StoreEnterState_800BB30C)
    int flags_4;       // 1 message shown, 2 leaving
    int windows_8;     // stateWindows_800BE7CC bits
    int windowsOpen_C;
    short equipKind_10; // 0 weapon, 1 armor, 2 accessory
    short sell_12;      // 0 buy, 1 sell
    int itemId_14;
    int quantity_18;
    short storeKind_1C; // 0 equipment, 1 items
    unsigned short stockMask_1E; // GetStoreStockMask_800BB088
    short stockCounts_20[4];     // weapons, armor, accessories, items in stock
    short cursor_28[4];          // MenuCursor (UpdateMenuCursor_8003D794): columns, rows, count, flags
    short cursorIndex_30;
    short cursorScroll_32;
    short panel_34; // storePanels_800BE580 index
    short savedIndex_36;
    short savedScroll_38;
    short textId_3A; // storeTextsA_800BE37C index
    short field_3C;
    short field_3E;
    int confirm_40;
    int cancel_44;
    short openTimer_48; // window open animation, 0..8
    char pad_4A[2];
    short keeperId_4C;  // 2 / 3: storeTextsB_800BE3D8 / storeTextsC_800BE434
    short errorId_4E;   // 1 not enough money, 2 can't carry more
    short messageTimer_50;
} StoreMenu;

typedef struct StoreRect
{
    short x, y, w, h;
} StoreRect;

// window style for DrawWindow_80042460 (CombSelBox)
typedef struct StoreWinStyle
{
    unsigned short col_0;
    char state_2;
    char frame_3;
} StoreWinStyle;

// DrawScrollArrow_8002B3DC: an arrow kind and an orientation (CombSelArrow)
typedef struct StoreArrow
{
    short kind_0;
    short dir_2;
} StoreArrow;

// window colour for DrawWindow_80042460 (CombSelBox)
typedef struct StoreWinColor
{
    short color_0;
    char state_2;
    char frame_3;
} StoreWinColor;

// DrawUiWindow_8002A384's parameter block
typedef struct StoreUiWindow
{
    void* rect;
    int frame;
    short highlight;
    short ot;
} StoreUiWindow;

typedef struct StoreXY
{
    short x;
    short y;
} StoreXY;

typedef struct StorePos
{
    unsigned short x;
    unsigned short y;
} StorePos;

// a UI sprite position followed by a window style (DrawUiTiySprt_8002C06C, then DrawWindow_80042460 on col_8)
typedef struct StoreSprtBox
{
    short x_0;
    short y_2;
    int pad_4;
    unsigned short col_8;
    char state_A;
    char frame_B;
} StoreSprtBox;

/* WPNSHOP functions */
void StartStore_800BAE2C(int kind, short keeper);
int GetStoreStockMask_800BB088(StoreMenu* store);
void StoreWaitUiTiy_800BB130(EventEntry* task, StoreMenu* store);
void StoreFadeIn_800BB194(EventEntry* task, StoreMenu* store);
void StoreTask_800BB1F4(EventEntry* task, StoreMenu* store);
void StoreWaitMapReload_800BB298(EventEntry* task, void* buffer);
void StoreEnterState_800BB30C(StoreMenu* store);
void StoreInput_800BB664(StoreMenu* store);
void DrawStoreWindowFrame_800BB868(StoreMenu* store, StoreRect* rect, int a2, int a3, short idx);
void DrawStoreDialog_800BB8CC(StoreMenu* store);
void DrawStore_800BB950(StoreMenu* store);
void UpdateStoreCursor_800BBDD0(StoreMenu* store);
void SetStoreErrorText_800BBE54(StoreMenu* store);
void DrawMoneyWindow_800BBED0(void* unused, StorePos* pos);
void DrawHeldCountWindow_800BBFD4(int count);
void DrawQuantityWindow_800BC0AC(StoreMenu* store, int panel);
void DrawStoreMainMenu_800BC194(StoreMenu* store);
void DrawStoreMainCursor_800BC210(StoreMenu* store);
void DrawEquipKindMenu_800BC268(StoreMenu* store);
void DrawItemHeldCount_800BC2E4(StoreMenu* store);
void DrawStoreList_800BC374(StoreMenu* store, short panel);
void DrawEquippedMark_800BCABC(StoreMenu* store, short panel);
void DrawItemQuantity_800BCC18(StoreMenu* store);
void DrawEquipHeldCount_800BCC4C(StoreMenu* store);
void DrawEquipStatCompare_800BCCE8(StoreMenu* store);
void SetStoreDialogText_800BCED4(StoreMenu* store);
void DrawStoreButtonHelp_800BCF80(unsigned short* state);
void DrawTotalPrice_800BCFCC(StoreMenu* store);
void DrawEquipQuantity_800BD174(StoreMenu* store);
void StoreMainInput_800BD1A8(StoreMenu* store);
void ItemBuyListInput_800BD278(StoreMenu* store);
void ItemSellListInput_800BD378(StoreMenu* store);
void StoreConfirmInput_800BD444(StoreMenu* store);
void ReadyEquipInput_800BD61C(StoreMenu* store);
void StoreWaitPrompt_800BD6A4(StoreMenu* store);
int IsEquipped_800BD71C(int id, int kind);
void StoreQuantityInput_800BD760(StoreMenu* store);
void EquipKindInput_800BD928(StoreMenu* store);
void EquipBuyListInput_800BD9A8(StoreMenu* store);
void EquipSellListInput_800BDAB4(StoreMenu* store);
int BuyItem_800BDB80(int id, int count);
void SellItem_800BDBDC(int id, int count);
int BuyEquipment_800BDC40(int id, int kind, int count);
void SellEquipment_800BDCB4(int id, int kind, int count);
int GetStockEquipment_800BDD2C(int nth, unsigned int kind, int mask);
int GetStockItem_800BDDB0(int nth, int mask);
short CountStock_800BDDF8(unsigned short* stock, int count, int mask);
int GetMaxBuyEquipCount_800BDE38(short id, short kind);
int GetMaxBuyItemCount_800BDF68(short id);
short GetStoreListPos_800BE00C(StoreMenu* store, short panel);
short GetStoreListCursor_800BE058(StoreMenu* store, short panel);
int AdjustBuyQuantity_800BE084(int count, int max);

/* GAME.BIN (resident field overlay), to move to game.h */
void RequestGameMode_800A6D30(int a);
void SuspendFieldMinions_800A7B00(int a);
void ResumeFieldMinions_800A7BF0(int a);
int GetMoney_800AD02C(void);
void AddMoney_800AD058(int a);
int SpendMoney_800AD0A4(int a);
int AddInventory_800AD184(int a, int b, int c);
void RemoveInventory_800AD1E0(int a, int b, int c);
int GetInventoryCount_800AD254(int a, int b);
int GetLastInventorySlot_800AD308(int a);
int FindInventorySlotForAdd_800AD4D8(int a, int b, int c);
int TestValuableFlag_800AD73C(int a);
void SetEquipment_800AD9EC(int itemId, int category);

/* exe-side, to move to <exe header> (named in the comment) */
extern char name_80082680[];
extern char name_800826B0[];
extern unsigned short uiColor_8008B590;
extern char* dword_8008D454;
int GetEquipmentName_8001D128(int idx, unsigned int kind); // engine.h
void SetFadeMode_8001C19C(int a, int b);    // engine.h
void SetLoadFadeFlag_80027478(int a, int b); // model_ftg
void DrawTextList_8002A310(void* p, int a); // menu_draw.h
void DrawUiWindow_8002A384(void* p);        // menu_draw.h
void DrawPortraitWindow_8002A4E4(int a);    // menu_draw.h
void DrawMenuWindows_8002A5A4(StoreMenuWindows* p); // menu_draw.h
void DrawButtonHelpBar_8002B004(void* entries, int pos, int ot); // menu_window.h
void DrawScrollArrow_8002B3DC(StoreArrow arrow, int time, void* pos, int ot); // ui_gauge
void DrawMenuBackground_8002BE10();         // ui_sprites
void FreeActiveOverlay_8002C014(void);      // ui_sprites
void DrawUiTiySprt_8002C06C(void* pos, int idx, short ot); // ui_sprites
void DrawSmallNumber9_8002C414(void* p, int a, short b); // ui_sprites
void DrawStatCompare_8002E188(void* before, void* after, void* pos, int ot); // status_panel.h
void CalcStatsWithEquip_8002E288(UnitStatus* unit, int itemId, int category, unsigned char* out); // status_panel.h
void DrawLevantStats_8002F7D0(void* pos, int ot); // party_window.h
void UpdateMenuCursor_8003D794(void* cursor, int pad); // pad_text.h
int AdjustByShoulderButtons_8003D198(int a, int b, int c, int d); // pad_text.h
void DrawWindow_80042460(void* rect, void* box, void* ot, unsigned int a3); // event.h

/* WPNSHOP data */

extern int dword_800B66C0;
extern const int aEmpty_800B66C4;
extern const char aYesWhatDoYouWan_800B66C8[];
extern const char aWhatDoYouWantTo_800B66F8[];
extern const char aWhichWillYouGet_800B672C[];
extern const char aPickWhateverYou_800B6764[];
extern const char aChooseWisely_800B6794[];
extern const char aYouMightRegretI_800B67B4[];
extern const char aHowManyWillYouB_800B67F8[];
extern const char aHowManyWillYouG_800B6828[];
extern const char aNo_800B6864[];
extern const char aYes_800B686C[];
extern const char aWillYouBuyThis_800B6878[];
extern const char aShallWeConclude_800B68A0[];
extern const char aHowMayIHelpYou_800B68DC[];
extern const char aOkayThenPickWha_800B6904[];
extern const char aWhatWillYouTrad_800B694C[];
extern const char aHowManyDoYouWan_800B698C[];
extern const char aHowManyWillYouT_800B69B8[];
extern const char aThisIsOkayThen_800B69EC[];
extern const char aOkay_800B6A14[];
extern const char aLikeThat_800B6A20[];
extern const char aHeyILlGoBrokeWi_800B6A38[];
extern const char aSorryThatSNotEn_800B6A78[];
extern const char aYouCanTBuyThatM_800B6AAC[];
extern const char aWillYouReadyItN_800B6AE0[];
extern const char aItImproperly_800B6B10[];
extern const char aYouLlRegretItIf_800B6B30[];
extern const char aDonTForgetToRea_800B6B68[];
extern const char aWhatDoYouWishTo_800B6BA8[];
extern const char aWhatDoYouWishTo_800B6BD8[];
extern const char aWhatWillYouTrad_800B6C0C[];
extern const char aWhichOneDoYouWa_800B6C38[];
extern const char aHowManyDoYouNee_800B6C68[];
extern const char aIsThisOkay_800B6C94[];
extern const char aIsTheTradeOkayW_800B6CB0[];
extern const char aEnoughMoney_800B6CE8[];
extern const char aItLooksLikeYouD_800B6D04[];
extern const char aYouHaveReadiedI_800B6D40[];
extern const char aOrMakeATrade_800B6D6C[];
extern const char aDoYouWantToBuyS_800B6D90[];
extern const char aWhichDoYouWant_800B6DCC[];
extern const char aWhatDoYouWannaS_800B6DF4[];
extern const char aAndHowManyDoYou_800B6E24[];
extern const char aSoIsThisOkay_800B6E58[];
extern const char aOhThatSNotEnoug_800B6E7C[];
extern const char aAttractsNearbyM_800B6EAC[];
extern const char aTreeSporesWithA_800B6EE0[];
extern const char aCausesSurroundi_800B6F2C[];
extern const char aSweetSmellingSl_800B6F84[];
extern const char aTreeSpores_800B6FEC[];
extern const char aBendsAndBecomes_800B7004[];
extern const char aMultipurposeKey_800B705C[];
extern const char aKeyToTreasureCh_800B70C0[];
extern const char aHighestGradeBes_800B70F0[];
extern const char aSoftThreadThatG_800B7134[];
extern const char aSecondHighestGr_800B7188[];
extern const char aGivesOffAnUnear_800B71C4[];
extern const char aThirdHighestGra_800B7214[];
extern const char aGivesOffAPhosph_800B7250[];
extern const char aFourthHighestGr_800B72A0[];
extern const char aGivesOffAModera_800B72DC[];
extern const char aFifthHighestGra_800B7324[];
extern const char aGivesOffADazzli_800B7360[];
extern const char aSixthHighestGra_800B7398[];
extern const char aEmitsVagueInsta_800B73D4[];
extern const char aSeventhHighestG_800B7430[];
extern const char aGivesOffAShineT_800B7470[];
extern const char aSilkThreadSpunF_800B74CC[];
extern const char aInflictsAWindBa_800B7518[];
extern const char aAttackMultipleE_800B757C[];
extern const char aInflictsAWindBa_800B75C0[];
extern const char aSealWithTheMark_800B7620[];
extern const char aAttackSingleEne_800B7688[];
extern const char aInflictsAFireBa_800B76C4[];
extern const char aAttackAllEnemie_800B7720[];
extern const char aInflictsAFireBa_800B775C[];
extern const char aSealWithTheMark_800B77BC[];
extern const char aAttackSingleEne_800B7820[];
extern const char aInflictsAWaterB_800B785C[];
extern const char aAttackAllEnemie_800B78B8[];
extern const char aInflictsAWaterB_800B78F4[];
extern const char aSealWithTheMark_800B7958[];
extern const char aAttackSingleEne_800B79C0[];
extern const char aInflictsAnEarth_800B7A00[];
extern const char aAttackAllEnemie_800B7A60[];
extern const char aInflictsAnEarth_800B7A9C[];
extern const char aSealWithTheMark_800B7B00[];
extern const char aAttackSingleEne_800B7B68[];
extern const char aChangesAreaProp_800B7BA8[];
extern const char aACharmBlessedBy_800B7C0C[];
extern const char aChangesAreaProp_800B7C6C[];
extern const char aACharmBlessedBy_800B7CD0[];
extern const char aChangesAreaProp_800B7D30[];
extern const char aACharmBlessedBy_800B7D98[];
extern const char aChangesAreaProp_800B7DF8[];
extern const char aACharmBlessedBy_800B7E60[];
extern const char aChangeAreaPrope_800B7EC0[];
extern const char aAllAbnormalStat_800B7EF0[];
extern const char aReflectsAllUncl_800B7F58[];
extern const char aProtectionFromA_800B7FB8[];
extern const char aInstantlyCauses_800B7FE0[];
extern const char aReleasesADeathM_800B803C[];
extern const char aCauseDeath_800B8084[];
extern const char aCausesBodyHarde_800B809C[];
extern const char aReleasesAFleshT_800B80F8[];
extern const char aFleshToStone_800B8150[];
extern const char aCausesADeepSlum_800B8170[];
extern const char aReleasesASleepM_800B81DC[];
extern const char aInduceSleep_800B8224[];
extern const char aInstantlyCauses_800B8240[];
extern const char aReleasesPoisonM_800B8288[];
extern const char aSprayPoison_800B82CC[];
extern const char aInnerStrengthTo_800B82E8[];
extern const char aPowderMadeFromS_800B8344[];
extern const char aStoneToFlesh_800B83A8[];
extern const char aSoothesTheSpiri_800B83C8[];
extern const char aPowderedFormOfD_800B841C[];
extern const char aPoisonAntidote_800B8468[];
extern const char aAdjustsTheVisce_800B8488[];
extern const char aAlsoCalledTheIm_800B84B4[];
extern const char aDriedRootOfAGre_800B84F8[];
extern const char aTotalRestoratio_800B8560[];
extern const char aRestoresAllMini_800B8584[];
extern const char aSpecialLiquorMa_800B85C8[];
extern const char aRestoresAGreatD_800B8624[];
extern const char aExcellentLiquor_800B8680[];
extern const char aRestoresMinionH_800B86E0[];
extern const char aFineLiquorMadeF_800B8744[];
extern const char aRestoresSomeMin_800B879C[];
extern const char aLiquorMadeFromP_800B87E0[];
extern const char aRestoreMinionHP_800B882C[];
extern const char aStrengthensMini_800B8864[];
extern const char aOilFromAPlantWi_800B88A0[];
extern const char aIncreaseMinionM_800B88E8[];
extern const char aStrengthensMini_800B8924[];
extern const char aOilFromTreeWith_800B895C[];
extern const char aIncreaseMinionM_800B89A4[];
extern const char aHardensMinionSS_800B89E0[];
extern const char aOilFromAPlantWi_800B8A10[];
extern const char aIncreaseMinionD_800B8A5C[];
extern const char aStrengthensMini_800B8A9C[];
extern const char aOilFromAVeryPot_800B8AD4[];
extern const char aIncreasesMinion_800B8B10[];
extern const char aSharpensMinionS_800B8B40[];
extern const char aOilFromATreeWit_800B8B74[];
extern const char aIncreaseMinionA_800B8BBC[];
extern const char aStrengthensTheB_800B8BF8[];
extern const char aANutPackingEner_800B8C5C[];
extern const char aIncreaseMaxHeal_800B8CBC[];
extern const char aBitterTasteThat_800B8CE4[];
extern const char aATypeOfMugwortW_800B8D50[];
extern const char aCuresBleedingAn_800B8DB4[];
extern const char aSweeterSmelling_800B8DF8[];
extern const char aATypeOfMugwortB_800B8E50[];
extern const char aGrindLeavesInto_800B8E90[];
extern const char aIncreasesHealth_800B8EEC[];
extern const char aGrowsInOpenArea_800B8F38[];
extern const char aRestoreHealth_800B8F80[];
extern const char aCriticallyWound_800B8FA0[];
extern const char aColdBladeWithAP_800B8FF8[];
extern const char aClearNightDeliv_800B904C[];
extern const char aBladeThatGlowsL_800B90A4[];
extern const char aDrainsOnlyTheEn_800B90F8[];
extern const char aBlindinglySharp_800B9134[];
extern const char aAxeSoundlyCrush_800B916C[];
extern const char aOneFellSwoopOfT_800B91AC[];
extern const char aProvidesTheDivi_800B91E8[];
extern const char aLeavesAPaleTrai_800B923C[];
extern const char aWithADesignOfGa_800B9290[];
extern const char aLargeBreathtaki_800B92D8[];
extern const char aEngravedWithADr_800B931C[];
extern const char aExtremelyLongBl_800B934C[];
extern const char aTwoHandedSword_800B9378[];
extern const char aWithSpectacular_800B939C[];
extern const char aLargeCurvedBlad_800B93E4[];
extern const char aSamuraiSword_800B9438[];
extern const char aOutstandingCutt_800B9454[];
extern const char aUndulatingBlade_800B948C[];
extern const char aCanRenderTheEne_800B94B8[];
extern const char aTippedWithAShar_800B94F8[];
extern const char aProvidesAwesome_800B952C[];
extern const char aManyBlueSinewsR_800B956C[];
extern const char aRefinedYetDeadl_800B95B8[];
extern const char aBladeImbuedWith_800B95F0[];
extern const char aLongSword_800B9624[];
extern const char aAlsoGoodForSlas_800B963C[];
extern const char aSoundsLikeTheWi_800B966C[];
extern const char aWindLighteningI_800B96B0[];
extern const char aProvidesDivineP_800B96F4[];
extern const char aWithAPolishedAn_800B9738[];
extern const char aLightAndEasyToW_800B9780[];
extern const char aJavelin_800B97CC[];
extern const char aLightGivesPower_800B97DC[];
extern const char aFamousSwordThat_800B9824[];
extern const char aLongsword_800B9870[];
extern const char aAsMightBeExpect_800B9884[];
extern const char aAxeMadeOfIronFo_800B98D0[];
extern const char aAxe_800B9918[];
extern const char aBladeMadeOfIron_800B9920[];
extern const char aExtremelyLargeA_800B9948[];
extern const char aTwoHandedSword_800B997C[];
extern const char aAttackAndDefens_800B99A0[];
extern const char aLightAndEasyToW_800B99E0[];
extern const char aShortSword_800B9A2C[];
extern const char aOfBronze_800B9A44[];
extern const char aFairlyHeavySwor_800B9A5C[];
extern const char aLongSword_800B9A8C[];
extern const char aWaterSoItsTipNe_800B9AA4[];
extern const char aProvidesDivineP_800B9AE0[];
extern const char aSpear_800B9B28[];
extern const char aCarvingMeat_800B9B34[];
extern const char aUsedForCuttingA_800B9B50[];
extern const char aAtTheRiver_800B9B98[];
extern const char aOftenUsedForPla_800B9BB4[];
extern const char aSmallKnife_800B9C04[];
extern const char aOfTheForestFlow_800B9C1C[];
extern const char aDyedWithTheBark_800B9C6C[];
extern const char aSenseEnemyMoves_800B9CD0[];
extern const char aWovenFromDivine_800B9D2C[];
extern const char aTheBreathOfTheF_800B9D84[];
extern const char aWovenOfTheHighe_800B9DD0[];
extern const char aCalmsTheHeartAn_800B9E30[];
extern const char aWovenFromTheHig_800B9E84[];
extern const char aBringsMisfortun_800B9EE0[];
extern const char aClothesOfOneWho_800B9F3C[];
extern const char aLightWarmAndVer_800B9F8C[];
extern const char aWovenFromWhiteC_800B9FC8[];
extern const char aWithstandsSnows_800BA004[];
extern const char aLeftBehindByYou_800BA058[];
extern const char aClothing_800BA0A0[];
extern const char aYajakoSGreatest_800BA0B4[];
extern const char aMadeOfTheHardes_800BA0F4[];
extern const char aProtectsWearerW_800BA134[];
extern const char aSofterThanSomeO_800BA188[];
extern const char aProvidesResista_800BA1D4[];
extern const char aMadeOfMirrorLik_800BA22C[];
extern const char aHeavyButGoodAtW_800BA280[];
extern const char aMadeOfIronPlate_800BA2D0[];
extern const char aLightAndUnrestr_800BA2FC[];
extern const char aWovenWithThinIr_800BA330[];
extern const char aLightYetGoodAtW_800BA368[];
extern const char aMadeOfIronRings_800BA3B8[];
extern const char aStrongYetQuietC_800BA400[];
extern const char aMadeOfTannedLea_800BA438[];
extern const char aSuitedToTheFore_800BA468[];
extern const char aWarmYetAiry_800BA494[];
extern const char aArmor_800BA4B4[];
extern const char aForSafeTravelPr_800BA4C0[];
extern const char aMadeOfWhiteCoco_800BA528[];
extern const char aIncreasesBodySR_800BA584[];
extern const char aIncreasesResist_800BA5DC[];
extern const char aIncreasesResist_800BA638[];
extern const char aIncreasesResist_800BA678[];
extern const char aReleasesCleanAi_800BA6B8[];
extern const char aEnhancesAimOfCu_800BA6E0[];
extern const char aMadeOfHawkFeath_800BA724[];
extern const char aThornyButProvid_800BA754[];
extern const char aMadeOfHollyLeav_800BA7AC[];
extern const char aHelpsFocusMana_800BA7D8[];
extern const char aBeautifullyScul_800BA7FC[];
extern const char aItAMasculineApp_800BA840[];
extern const char aPlainAndUnadorn_800BA878[];
extern const char aBoostsTheHeartA_800BA8BC[];
extern const char aMadeOfSparrowFe_800BA8F4[];
extern const char aResistanceAgain_800BA928[];
extern const char aProvidesTheDivi_800BA978[];
extern const char aResistanceAgain_800BA9D0[];
extern const char aProvidesTheDivi_800BAA20[];
extern const char aResistanceAgain_800BAA78[];
extern const char aProvidesTheDivi_800BAAC8[];
extern const char aResistanceAgain_800BAB20[];
extern const char aProvidesTheDivi_800BAB70[];
extern const char aSilverProvidesR_800BABC8[];
extern const char aBandWithSilverW_800BAC14[];
extern const char aToughButHeavy_800BAC4C[];
extern const char aBandWithIronWov_800BAC70[];
extern const char aProtectsHeadFro_800BACA4[];
extern const char aBandWithLeather_800BACF8[];
extern const char aOrnamentalItem_800BAD30[];
extern const int dword_800BAD50;
extern const StoreMenuWindows menuWindow_800BADF0;
extern const int dword_800BAE08;
extern int dword_800BE110;
extern int dword_800BE114[4];
extern int dword_800BE124[4];
extern int dialogLines_800BE134[8];
extern void *txtEquipMainA_800BE154[3];
extern void *txtEquipBuyKindA_800BE160[3];
extern void *txtEquipSellKindA_800BE16C[3];
extern void *txtEquipBuyListA_800BE178[3];
extern void *txtEquipSellListA_800BE184[3];
extern void *txtEquipBuyCountA_800BE190[3];
extern void *txtEquipSellCountA_800BE19C[3];
extern const char *txtEquipBuyConfirmA_800BE1A8[3];
extern const char *txtEquipSellConfirmA_800BE1B4[3];
extern void *txtItemMainA_800BE1C0[3];
extern void *txtItemBuyListA_800BE1CC[3];
extern void *txtItemSellListA_800BE1D8[3];
extern void *txtItemBuyCountA_800BE1E4[3];
extern void *txtItemSellCountA_800BE1F0[3];
extern const char *txtItemBuyConfirmA_800BE1FC[3];
extern const char *txtItemSellConfirmA_800BE208[3];
extern void *txtEquipNoMoneyA_800BE214[3];
extern void *txtItemNoMoneyA_800BE220[3];
extern void *txtItemCantBuyMoreA_800BE22C[3];
extern void *txtEquipCantBuyMoreA_800BE238[3];
extern const char *txtReadyAskA_800BE244[3];
extern void *txtReadiedA_800BE250[3];
extern void *txtReadyLaterA_800BE25C[3];
extern void *txtMainC_800BE268[3];
extern void *txtEquipBuyKindC_800BE274[3];
extern void *txtSellC_800BE280[3];
extern void *txtBuyListC_800BE28C[3];
extern void *txtBuyCountC_800BE298[3];
extern void *txtSellCountC_800BE2A4[3];
extern const char *txtEquipBuyConfirmC_800BE2B0[3];
extern const char *txtEquipSellConfirmC_800BE2BC[3];
extern const char *txtItemConfirmC_800BE2C8[3];
extern void *txtNoMoneyC_800BE2D4[3];
extern void *txtCantBuyMoreC_800BE2E0[3];
extern const char *txtReadyAskC_800BE2EC[3];
extern void *txtReadiedC_800BE2F8[3];
extern void *txtReadyLaterC_800BE304[3];
extern void *txtItemMainB_800BE310[3];
extern void *txtItemBuyListB_800BE31C[3];
extern void *txtItemSellListB_800BE328[3];
extern void *txtItemBuyCountB_800BE334[3];
extern void *txtItemSellCountB_800BE340[3];
extern const char *txtItemBuyConfirmB_800BE34C[3];
extern const char *txtItemSellConfirmB_800BE358[3];
extern void *txtItemNoMoneyB_800BE364[3];
extern void *txtCantBuyMoreB_800BE370[3];
extern int *storeTextsA_800BE37C[23];
extern int *storeTextsB_800BE3D8[23];
extern int *storeTextsC_800BE434[23];
extern int panelCursor0_800BE490[4];
extern int panelCursor4_800BE4A0[4];
extern int panelCursor5_800BE4B0[4];
extern int panelCursor6_800BE4C0[4];
extern int panelCursor9_800BE4D0[4];
extern int panelCursor10_800BE4E0[4];
extern int panelCursor11_800BE4F0[8];
extern int panelCursor12_800BE510[8];
extern int panelCursor15_800BE530[4];
extern int panelCursor16_800BE540[4];
extern int panelCursor27_800BE550[4];
extern int panelCursor19_800BE560[8];
extern StorePanel storePanels_800BE580[29];
extern char dialogWindowRect_800BE7C4[8];
extern int stateWindows_800BE7CC[19];
extern unsigned short statePanels_800BE818[20];
extern unsigned short stateTexts_800BE840[20];
extern unsigned short equipModeStates_800BE868[2];
extern unsigned short itemModeStates_800BE86C[2];
extern unsigned short equipListStates_800BE870[2];
extern int equipKindSprites_800BE874[3];
extern int storeListRow0_800BE880[28];
extern int storeListRow1_800BE8F0[28];
extern int storeListRow2_800BE960[28];
extern int storeListRow3_800BE9D0[28];
extern StoreMenuItem *storeListRows_800BEA40[5];
extern int mainMenuItem0_800BEA54[14];
extern int mainMenuItem1_800BEA8C[14];
extern int mainMenuItem2_800BEAC4[14];
extern char mainMenuItems_800BEAFC[16];
extern int equipKindItem0_800BEB0C[14];
extern int equipKindItem1_800BEB44[14];
extern int equipKindItem2_800BEB7C[14];
extern char equipKindItems_800BEBB4[16];
extern StorePos moneyWindowPosL_800BEBC4;
extern StorePos moneyWindowPosR_800BEBC8;
extern char itemDescLines_800BEBCC[688];
extern char weaponDescLines_800BEE7C[368];
extern char armorDescLines_800BEFEC[240];
extern char accessoryDescLines_800BF0DC[272];
extern unsigned short itemStock_800BF1EC[44];
extern unsigned short weaponStock_800BF244[24];
extern unsigned short armorStock_800BF274[16];
extern unsigned short accessoryStock_800BF294[18];

#endif
