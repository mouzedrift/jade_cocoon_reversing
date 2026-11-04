// COMBBTL.BIN: declarations shared by its source files
#ifndef _COMBBTL_H_
#define _COMBBTL_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "camera.h"

typedef struct CombBtlNode
{
    unsigned int flags;
} CombBtlNode;

typedef struct CombBtlCmd
{
    int kind_0; // 0x14: none
    int arg_4;
    int mask_8; // acting unit bits
    int targets_C; // target unit bits
} CombBtlCmd;

typedef struct CombBtlHist
{
    int unit_0;
    CombBtlCmd cmd_4;
} CombBtlHist;

typedef struct CombBtlPair
{
    short lo;
    short hi;
} CombBtlPair;

typedef struct CombBtlA24
{
    int pos_0[2][3]; // per side
} CombBtlA24;

typedef struct CombBtlB16
{
    unsigned char f0[2][8]; // per side
} CombBtlB16;

typedef struct CombBtlResult
{
    unsigned short kind_0;
    short arg_2;
    int cured_4;
    int inflicted_8;
    int actorHpLoss_C;
    int actorMpLoss_10;
    int actorHpDamage_14;
    int actorMpDamage_18;
    int hpDamage_1C;
    int mpDamage_20;
    short element_24;
    short f26;
} CombBtlResult;

// a menu item drawn by DrawMenuItemWithWindow_8002ADB4 (DrawMenuWindowContents_8002A710)
typedef struct CombBtlItem
{
    unsigned short flags_0;
    unsigned short type_2; // 1: TIY sprite
    int icon_4;
    SPRT** sprts_8;
    DR_TPAGE** tpages_C;
    short x_10; // the window rect
    short y_12;
    short w_14;
    short h_16;
    short mx_18;
    short my_1A;
} CombBtlItem;

typedef struct CombBtlPos2
{
    CombBtlPair p[2]; // per side
} CombBtlPos2;

typedef struct CombBtlInt3
{
    int v[3];
} CombBtlInt3;

extern int dword_800A4088;
extern const char aAreVictorious_800A408C[];
extern const char aTheMinionsOfThe_800A40AC[];
extern const char aCongratulations_800A40DC[];
extern const char aTheMinionsOfThe_800A4100[];
extern const char aEachOtherSMoves_800A4134[];
extern const char aItSeemsYouAreGa_800A415C[];
extern const char aThisThrillingBa_800A4190[];
extern const char aICannotTakeMyEy_800A41C0[];
extern const char aNoDamageTaken_800A41F4[];
extern const char aOhMyItDodgedThe_800A4218[];
extern const char aOhThatHadToHurt_800A4250[];
extern const char aADirectHit_800A427C[];
extern const char aTheMinionLooksD_800A4298[];
extern const char aPoison_800A42C8[];
extern const char aOnAChoppingBloc_800A42D8[];
extern const char aItIsLikeAHelple_800A4304[];
extern const char aThisCouldBeDang_800A433C[];
extern const char aOhNoItIsFalling_800A4370[];
extern const char aNotHealed_800A43AC[];
extern const char aThisCouldBeFata_800A43C4[];
extern const char aStoneItIsSpread_800A4400[];
extern const char aTheMinionIsBein_800A443C[];
extern const char aTheMinionIsGrav_800A447C[];
extern const char aCouldKeelOverAt_800A44BC[];
extern const char aItIsBreathingHe_800A44F4[];
extern const char aItHasFallenAndC_800A452C[];
extern const char aForThisMinion_800A4570[];
extern const char aItLooksLikeThat_800A4594[];
extern const char aIsTheFightOver_800A45C8[];
extern const int aEmptyLine_800A45F0;
extern const char aVeryEffective_800A45F4[];
extern const char aRightAtTheEleme_800A4614[];
extern const char aWhatAWellChosen_800A4658[];
extern const char aEnteredTheArena_800A4690[];
extern const char aANewMinionHas_800A46B8[];
extern const char aThePlayerHasSwi_800A46DC[];
extern const char aWhatWillHappenN_800A4720[];
extern const char aWhatAnExcitingM_800A4750[];
extern const char aAChangeOfElemen_800A4780[];
extern const char aWithOneFatalBlo_800A47C4[];
extern const char aTheMinionHasFal_800A47F0[];
extern const char aSuchOverwhelmin_800A481C[];
extern const char aItCouldBeVictor_800A4850[];
extern const char aAgainstAllOdds_800A487C[];
extern const char aWhatAmazingWill_800A48A0[];
extern const char aIWasEvenRooting_800A48D0[];
extern const char aTooBad_800A4908[];
extern const char aDecidedBeforeTh_800A491C[];
extern const char aAnotherLossTheF_800A495C[];
extern const char aWellDone_800A49A0[];
extern const char aReached_800A49B8[];
extern const char aFinallyADecisio_800A49CC[];
extern const char aWhatACloseFight_800A4A04[];
extern const CombBtlA24 sideActorPos_800A4AD4;
extern const CombBtlB16 sideActorArgs_800A4AEC;
extern const CombBtlItem sideLabel0_800A4AFC;
extern const CombBtlItem sideLabel1_800A4B18;
extern const CombBtlPos2 statusIconPos_800A4B34;
extern const CombBtlItem slotItem_800A4B3C;
extern const CombBtlPos2 slotItemPos_800A4B58;
extern const CombBtlInt3 slotIcons_800A4B60;
extern const CombBtlPos2 mpGaugePos_800A4B6C;
extern short previewHp_800A82D0;
extern short previewMp_800A82D2;
extern short sideWindowPos_800A82D4[2][2];
extern CombBtlNode *announcerTask_800A82DC;
extern short pendingXa_800A82E0[4];
extern int turnCount_800A82E8;
extern const char *winLinesP1_800A82EC[5];
extern const char *winLinesP2_800A8300[5];
extern const char *doubleSwapLines_800A8314[4];
extern const char *everyNthTurnLines_800A8324[4];
extern const char *dodgeLines_800A8334[4];
extern const char *directHitLines_800A8344[4];
extern const char *poisonLines_800A8354[4];
extern const char *statusLines_800A8364[6];
extern const char *stoneLines_800A837C[6];
extern const char *halfHpLines_800A8394[3];
extern const char *tenthHpLines_800A83A0[4];
extern void *koLines_800A83B0[15];
extern const char *swapLines_800A83EC[5];
extern const char *elementChangeLines_800A8400[5];
extern const char *oneBlowLines_800A8414[5];
extern const char *oneHpLeftLines_800A8428[5];
extern const char *lossLines_800A843C[6];
extern int finalLines_800A8454[7];
extern short hpDamage_800A8470[2];
extern short mpDamage_800A8474[2];
extern int announcerWindow_800A8478;
extern int dword_800A847C;
extern int statusCured_800A8480[2];
extern short exchangeStep_800A8488;
extern EventEntry *commandMenuTask_800A848C;
extern int koSide_800A8490;
extern CombBtlPair hitWindow_800A8494;
extern int stageElement_800A8498;
extern int fixedStageElement_800A849C;
extern int newStageElement_800A84A0;
extern short targetSfx_800A84A4;
extern short koSfx_800A84A6;
extern unsigned char exchangeFlags_800A84A8;
extern int dword_800A84AC;
extern int sideEntering_800A84B0[2];
extern int setupStep_800A84B8;
extern short actorHpLoss_800A84BC;
extern int stageId_800A84C0;
extern short actorMpLoss_800A84C4;
extern CombBtlPair sideHitWindows_800A84C8[2];
extern short sideGauges_800A84D0[2];
extern int waitTimer_800A84D4;
extern CombBtlHist commandHistory_800A84D8[10];
extern int fileRequest_800A85A0;
extern int dword_800A85A4;
extern CombBtlCmd actorCmd_800A85A8;
extern int actorSide_800A85B8;
extern unsigned char swapSlot_800A85BC;
extern unsigned char actorSlot_800A85BD;
extern const char** announcerLines_800A85C0; // the announcer line list RunExchange_800A68E0 shows once the hits land
extern int dword_800A85C4;
extern CombBtlResult result_800A85C8;
extern int statusInflicted_800A85F0[2];
extern int loserSide_800A85F8;
extern unsigned char sideHitKind_800A85FC[4];
extern CombBtlCmd chosenCmd_800A8600;
extern CombBtlCmd targetCmd_800A8610;
extern int targetSide_800A8620;

typedef struct CombBtlTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombBtlTask;

// a side's unit window task (OpenSideWindow_800A75F8, SideWindowTask_800A7694)
typedef struct CombBtlObj
{
    int side_0;
    int frame_4; // of the open animation
    RECT dst_8;  // the final window rect
    RECT cur_10; // the window rect being opened (InterpolateWindowRect_8004196C)
} CombBtlObj;

// a menu item (DrawMenuItemWithWindow_8002ADB4)
typedef struct CombBtlBox
{
    short color_0;
    char state_2;
    char frame_3;
} CombBtlBox;

typedef struct CombBtlHitNum
{
    int kind_0; // 1 hp, 2 mp
    int amount_4;
    int frame_8;
    int fC;
    int* pos_10;
    int f14;
    int side_18;
} CombBtlHitNum;

#endif
