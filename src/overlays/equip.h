// EQUIP.BIN: declarations shared by its source files
#ifndef _EQUIP_H_
#define _EQUIP_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"
#include "tiy.h"
#include "main.h"
#include "menu_window.h"
#include "engine.h"
#include "util.h"
#include "unit_query.h"
#include "event.h"


/* the types of equip.c */
struct EquipCtx;

typedef struct EquipCtx
{
    short stepCursor_0[6];
    short stepScroll_C[6];
    short category_18; // 0 weapon, 1 armor, 2 accessory
    short step_1A;
    short mode_1C;   // equipMenuStepModes_800C59B0[step_1A]: 0 category, 1 item list, 2 equip
    short activeWindows_1E;
    int openedWindows_20;
    int pad_24;
    int confirmed_28;
    int cancelled_2C;
    short pad_30[2];
    short cols_34;
    short rows_36;
    short count_38;
    short cursorFlags_3A;
    short cursor_3C; // cols_34..scroll_3E: an exe MenuCursor (UpdateMenuCursor_8003D794)
    short scroll_3E;
    short item_40;
    short openTimer_42;
    unsigned short flags_44;
    short msgTimer_46;
} EquipCtx;

typedef struct
{
    short x;
    short y;
    short w;
    short h;
} EquipRect;

// DrawScrollArrow_8002B3DC: an arrow kind and an orientation (CombSelArrow)
typedef struct
{
    short kind_0;
    short dir_2;
} EquipArrow;

// the window colour DrawWindow_80042460 takes (CombSelBox)
typedef struct
{
    short color_0;
    char state_2;
    char frame_3;
} EquipBox;


typedef struct
{
    short cursor;
    short scroll;
    short mode;
    short ot;
    short e;
    int f;
} EquipListParams;

/* EQUIP functions */
extern void EquipMenuTask_800C48B4(EventEntry* t, EquipCtx* c);
extern void SetEquipCursorArea_800C497C(EquipCtx* c);
extern void DrawEquipMenu_800C4A94(EquipCtx* c);
extern void HandleEquipCursorInput_800C4D50(EquipCtx* c);
extern void ChangeEquipMenuStep_800C4DF4(EquipCtx* c);
extern void TryEquipItem_800C5064(EquipCtx* c);
extern void CannotUnequipTask_800C50F0(EventEntry* t, EquipCtx* c);
extern void UpdateEquipSelection_800C51B0(EquipCtx* c);
extern void DrawEquipStats_800C5314(EquipCtx* c);
extern void DrawEquipDescription_800C5440(short itemId, short category, int pos);
extern void DrawEquipItemList_800C5510(EquipListParams* list, EquipRect* rect, short category);

/* EQUIP data */
extern int equipOverlayId_800C29D0;
extern const char aCriticallyWound_800C29D4[];
extern const char aColdBladeWithAP_800C2A2C[];
extern const char aClearNightDeliv_800C2A80[];
extern const char aBladeThatGlowsL_800C2AD8[];
extern const char aDrainsOnlyTheEn_800C2B2C[];
extern const char aBlindinglySharp_800C2B68[];
extern const char aAxeSoundlyCrush_800C2BA0[];
extern const char aOneFellSwoopOfT_800C2BE0[];
extern const char aProvidesTheDivi_800C2C1C[];
extern const char aLeavesAPaleTrai_800C2C70[];
extern const char aWithADesignOfGa_800C2CC4[];
extern const char aLargeBreathtaki_800C2D0C[];
extern const char aEngravedWithADr_800C2D50[];
extern const char aExtremelyLongBl_800C2D80[];
extern const char aTwoHandedSword_800C2DAC[];
extern const char aWithSpectacular_800C2DD0[];
extern const char aLargeCurvedBlad_800C2E18[];
extern const char aSamuraiSword_800C2E6C[];
extern const char aOutstandingCutt_800C2E88[];
extern const char aUndulatingBlade_800C2EC0[];
extern const char aCanRenderTheEne_800C2EEC[];
extern const char aTippedWithAShar_800C2F2C[];
extern const char aProvidesAwesome_800C2F60[];
extern const char aManyBlueSinewsR_800C2FA0[];
extern const char aRefinedYetDeadl_800C2FEC[];
extern const char aBladeImbuedWith_800C3024[];
extern const char aLongSword_800C3058[];
extern const char aAlsoGoodForSlas_800C3070[];
extern const char aSoundsLikeTheWi_800C30A0[];
extern const char aWindLighteningI_800C30E4[];
extern const char aProvidesDivineP_800C3128[];
extern const char aWithAPolishedAn_800C316C[];
extern const char aLightAndEasyToW_800C31B4[];
extern const char aJavelin_800C3200[];
extern const char aLightGivesPower_800C3210[];
extern const char aFamousSwordThat_800C3258[];
extern const char aLongsword_800C32A4[];
extern const char aAsMightBeExpect_800C32B8[];
extern const char aAxeMadeOfIronFo_800C3304[];
extern const char aAxe_800C334C[];
extern const char aBladeMadeOfIron_800C3354[];
extern const char aExtremelyLargeA_800C337C[];
extern const char aTwoHandedSword_800C33B0[];
extern const char aAttackAndDefens_800C33D4[];
extern const char aLightAndEasyToW_800C3414[];
extern const char aShortSword_800C3460[];
extern const char aOfBronze_800C3478[];
extern const char aFairlyHeavySwor_800C3490[];
extern const char aLongSword_800C34C0[];
extern const char aWaterSoItsTipNe_800C34D8[];
extern const char aProvidesDivineP_800C3514[];
extern const char aSpear_800C355C[];
extern const char aCarvingMeat_800C3568[];
extern const char aUsedForCuttingA_800C3584[];
extern const char aAtTheRiver_800C35CC[];
extern const char aOftenUsedForPla_800C35E8[];
extern const char aSmallKnife_800C3638[];
extern const char aOfTheForestFlow_800C3650[];
extern const char aDyedWithTheBark_800C36A0[];
extern const char aSenseEnemyMoves_800C3704[];
extern const char aWovenFromDivine_800C3760[];
extern const char aTheBreathOfTheF_800C37B8[];
extern const char aWovenOfTheHighe_800C3804[];
extern const char aCalmsTheHeartAn_800C3864[];
extern const char aWovenFromTheHig_800C38B8[];
extern const char aBringsMisfortun_800C3914[];
extern const char aClothesOfOneWho_800C3970[];
extern const char aLightWarmAndVer_800C39C0[];
extern const char aWovenFromWhiteC_800C39FC[];
extern const char aWithstandsSnows_800C3A38[];
extern const char aLeftBehindByYou_800C3A8C[];
extern const char aClothing_800C3AD4[];
extern const char aYajakoSGreatest_800C3AE8[];
extern const char aMadeOfTheHardes_800C3B28[];
extern const char aProtectsWearerW_800C3B68[];
extern const char aSofterThanSomeO_800C3BBC[];
extern const char aProvidesResista_800C3C08[];
extern const char aMadeOfMirrorLik_800C3C60[];
extern const char aHeavyButGoodAtW_800C3CB4[];
extern const char aMadeOfIronPlate_800C3D04[];
extern const char aLightAndUnrestr_800C3D30[];
extern const char aWovenWithThinIr_800C3D64[];
extern const char aLightYetGoodAtW_800C3D9C[];
extern const char aMadeOfIronRings_800C3DEC[];
extern const char aStrongYetQuietC_800C3E34[];
extern const char aMadeOfTannedLea_800C3E6C[];
extern const char aSuitedToTheFore_800C3E9C[];
extern const char aWarmYetAiry_800C3EC8[];
extern const char aArmor_800C3EE8[];
extern const char aForSafeTravelPr_800C3EF4[];
extern const char aMadeOfWhiteCoco_800C3F5C[];
extern const char aIncreasesBodySR_800C3FB8[];
extern const char aIncreasesResist_800C4010[];
extern const char aIncreasesResist_800C406C[];
extern const char aIncreasesResist_800C40AC[];
extern const char aReleasesCleanAi_800C40EC[];
extern const char aEnhancesAimOfCu_800C4114[];
extern const char aMadeOfHawkFeath_800C4158[];
extern const char aThornyButProvid_800C4188[];
extern const char aMadeOfHollyLeav_800C41E0[];
extern const char aHelpsFocusMana_800C420C[];
extern const char aBeautifullyScul_800C4230[];
extern const char aItAMasculineApp_800C4274[];
extern const char aPlainAndUnadorn_800C42AC[];
extern const char aBoostsTheHeartA_800C42F0[];
extern const char aMadeOfSparrowFe_800C4328[];
extern const char aResistanceAgain_800C435C[];
extern const char aProvidesTheDivi_800C43AC[];
extern const char aResistanceAgain_800C4404[];
extern const char aProvidesTheDivi_800C4454[];
extern const char aResistanceAgain_800C44AC[];
extern const char aProvidesTheDivi_800C44FC[];
extern const char aResistanceAgain_800C4554[];
extern const char aProvidesTheDivi_800C45A4[];
extern const char aSilverProvidesR_800C45FC[];
extern const char aBandWithSilverW_800C4648[];
extern const char aToughButHeavy_800C4680[];
extern const char aBandWithIronWov_800C46A4[];
extern const char aProtectsHeadFro_800C46D8[];
extern const char aBandWithLeather_800C472C[];
extern const char aOrnamentalItem_800C4764[];
extern const char emptyText_800C4784[4];
extern const char aCannotUnequip_800C4788[32];
extern char scrollUpArrowPos_800C5834[4];
extern char scrollDownArrowPos_800C5838[4];
extern MenuWindowItem equipListRow0_800C583C[4];
extern MenuWindowItem equipListRow1_800C58AC[4];
extern MenuWindowItem equipListRow2_800C591C[4];
extern MenuWindowItem* equipListRows_800C598C[4];
extern char descBoxPos_800C599C[4];
extern char statCompareWindowRect_800C59A0[8];
extern char statsWindowRect_800C59A8[8];
extern short equipMenuStepModes_800C59B0[4];
extern short modeCursorAreaMasks_800C59B8[4];
extern short cursorAreas_800C59C0[16];
extern char weaponDescs_800C59E0[23][16];
extern char armorDescs_800C5B50[15][16];
extern char accessoryDescs_800C5C40[17][16];
extern char cannotUnequipBox_800C5D50[16];

/* MENU overlay (resident under EQUIP): DrawEquipmentWindow_800C0E04(MenuEquipQ* eq, short* pos, short openStep) */
extern void DrawEquipmentWindow_800C0E04(void* a0, void* a1, int a2);

/* GAME overlay, to move to game.h */
extern void CompactInventory_800AD3F0(int table);
extern int GetLastInventorySlot_800AD308(int table);
extern int SetEquipment_800AD9EC(int id, int slot);

/* exe-side, to move to <exe header> */
extern int UpdateMenuCursor_8003D794(void* cursor, int pad); // pad_text.c defines it with one argument; the callers pass two
extern void DrawMenuBackground_8002BE10();
extern short uiColor_8008B590;
extern void DrawLevantStats_8002F7D0(void* pos, int ot);
extern void CalcStatsWithEquip_8002E288(UnitStatus* unit, int itemId, int category, unsigned char* out);
extern void DrawStatCompare_8002E188(void* before, void* after, void* pos, int ot);
extern void DrawScrollArrow_8002B3DC(EquipArrow arrow, int time, void* pos, int ot);
extern void DrawScrollArrow_8002C6DC(int pos, short dir, short ot);

#endif
