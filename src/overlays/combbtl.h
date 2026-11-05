// COMBBTL.BIN: declarations shared by its source files
#ifndef _COMBBTL_H_
#define _COMBBTL_H_

#include "common.h"
#include "common_tu.h"
#include "funcs.h"
#include "globals.h"
#include "camera.h"
#include "event.h"
#include "STDLIB.H"
#include "unit_gauges.h"
#include "combat.h"
#include "main.h"
#include "engine.h"
#include "menu_window.h"
#include "effect_data.h"
#include "util.h"
#include "msg_window.h"
#include "unit_query.h"
#include "movie.h"
#include "model.h"
#include "cd.h"
#include "sound_seq.h"
#include "ui_sprites.h"
#include "sound.h"
#include "effect.h"

typedef struct CombBtlNode
{
    unsigned int flags;
} CombBtlNode;

typedef struct CombBtlHist
{
    int unit_0;
    BattleCmd cmd_4;
} CombBtlHist;

typedef struct CombBtlPair
{
    short lo;
    short hi;
} CombBtlPair;

typedef struct CombBtlSidePos
{
    int pos_0[2][3]; // per side
} CombBtlSidePos;

typedef struct CombBtlSideRot
{
    unsigned char rot_0[2][8]; // per side: the actor rotation (3 shorts + pad)
} CombBtlSideRot;


// an announcer line list with a trailing word (finalLines_800A8454)
typedef struct CombBtlLineList6
{
    const char* lines_0[6]; // 0 ends the list
    int tail_18;
} CombBtlLineList6;

typedef struct CombBtlPos2
{
    CombBtlPair p[2]; // per side
} CombBtlPos2;

typedef struct CombBtlInt3
{
    int v[3];
} CombBtlInt3;

extern int dword_800A4088;
extern const CombBtlSidePos sideActorPos_800A4AD4;
extern const CombBtlSideRot sideActorArgs_800A4AEC;
extern const MenuWindowItem sideLabel0_800A4AFC;
extern const MenuWindowItem sideLabel1_800A4B18;
extern const CombBtlPos2 statusIconPos_800A4B34;
extern const MenuWindowItem slotItem_800A4B3C;
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
extern const char *koLines_800A83B0[5];
extern const char *emptyLines_800A83C4[5];
extern const char *weakSpotLines_800A83D8[5];
extern const char *swapLines_800A83EC[5];
extern const char *elementChangeLines_800A8400[5];
extern const char *oneBlowLines_800A8414[5];
extern const char *oneHpLeftLines_800A8428[5];
extern const char *lossLines_800A843C[6];
extern CombBtlLineList6 finalLines_800A8454;
extern short hpDamage_800A8470[2];
extern short mpDamage_800A8474[2];
extern MsgWindowEntry* announcerWindow_800A8478;
extern int dword_800A847C;
extern int statusCured_800A8480[2];
extern short exchangeStep_800A8488;
extern EventEntry *commandMenuTask_800A848C;
extern int koSide_800A8490;
extern ShortPair hitWindow_800A8494; // a: the current hit frame, b: the last one
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
extern ShortPair sideHitWindows_800A84C8[2]; // per side: the first and last hit frame of its action (StartSlotAction_800A0F50)
extern short sideGauges_800A84D0[2];
extern int waitTimer_800A84D4;
extern CombBtlHist commandHistory_800A84D8[10];
extern int fileRequest_800A85A0;
extern int dword_800A85A4;
extern BattleCmd actorCmd_800A85A8;
extern int actorSide_800A85B8;
extern unsigned char swapSlot_800A85BC;
extern unsigned char actorSlot_800A85BD;
extern const char** announcerLines_800A85C0; // the announcer line list RunExchange_800A68E0 shows once the hits land
extern int dword_800A85C4;
extern ActionResult result_800A85C8;
extern int statusInflicted_800A85F0[2];
extern int loserSide_800A85F8;
extern unsigned char sideHitKind_800A85FC[4];
extern BattleCmd chosenCmd_800A8600;
extern BattleCmd targetCmd_800A8610;
extern int targetSide_800A8620;

typedef struct CombBtlTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombBtlTask;

// a side's unit window task (OpenSideWindow_800A75F8, SideWindowTask_800A7694)
typedef struct CombBtlSideWindow
{
    int side_0;
    int frame_4; // of the open animation
    RECT dst_8;  // the final window rect
    RECT cur_10; // the window rect being opened (InterpolateWindowRect_8004196C)
} CombBtlSideWindow;


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

/* the jump table of ResolveCommand_800A616C (asm) and its targets, labels in the generated asm */
extern char jtgt_800A64C0[], jtgt_800A65BC[], jtgt_800A65F0[], jtgt_800A6624[];
extern void* const dword_800A4A9C[6];

extern int dword_8008D610;
void CombBtlStart_800A4B8C(CombBtlTask* t, int a);
void CombBtlWaitFile_800A4C40(CombBtlTask* t, int a);
void ResetSides_800A4CFC(void);
void CombBtlSetup_800A4D48(CombBtlTask* t, int a);
void CheckBattleOver_800A4EC8(CombBtlTask* t, int a);
void PlayVictoryJingle_800A5000(CombBtlTask* t);
void WaitVictoryJingle_800A5080(CombBtlTask* t);
void RecordBattleResult_800A50E4(CombBtlTask* t);
void AnnounceWinner_800A51EC(CombBtlTask* t);
void DrawWinnerBanner_800A5290(CombBtlTask* t);
MsgWindowEntry* OpenAnnouncerWindow_800A5408(int which, int lines, int side);
void CombBtlEnd_800A54CC(CombBtlTask* t);
void CombBtlExit_800A5544(CombBtlTask* t);
void SendInMinions_800A5638(CombBtlTask* t, int a);
void NextLivingMinion_800A58E8(int side);
void ChooseNextActor_800A599C(CombBtlTask* t, int side);
int GetGaugeRate_800A5B70(int side);
void ResetCommands_800A5BB4(void);
void StartTurn_800A5C64(CombBtlTask* t);
void LoadCommandMenu_800A5EB8(CombBtlTask* t);
void OpenCommandMenu_800A5EF8(CombBtlTask* t);
void WaitCommandMenu_800A5F60(CombBtlTask* t, int a);
void PushCommandHistory_800A601C(void);
void TakeChosenCommand_800A60A4(void);
void ClearHitResults_800A60F0(void);
void ResolveCommand_800A616C(void);
void RunExchange_800A68E0(CombBtlTask* t);
unsigned int CountLivingMinions_800A7164(int side);
ShortPair MergeHitWindows_800A71E4(int count, ShortPair* windows);
void StartArenaCamera_800A7290(void);
void StopArenaCamera_800A73E4(void);
void StartFadeTask_800A7420(void);
void StopFadeTask_800A7478(void);
void CreateSideActor_800A74A0(int side);
void RemoveSideMinion_800A7560(int side);
int AreSideModelsReady_800A758C(void);
void OpenSideWindow_800A75F8(int side);
void SideWindowTask_800A7694(EventEntry* e, void* buf);
void CloseSideWindows_800A7BE4(void);
void PlayHitFeedback_800A7C0C(int side);
void StartHitNumber_800A7E34(int side, int kind, int amount);
void FlashScreenWhite_800A7ECC(void);
void HitNumberTask_800A7EFC(EventEntry* e, CombBtlHitNum* buf);
void SetAnnouncerXa_800A8078(short channel, short startSector, short length);
int StartAnnouncer_800A8098(int which, int lines, int side);
void AnnouncerTask_800A816C(EventEntry* e);

/* COMBCOM.BIN */
EventEntry* CombComStart_800CB7AC(int cmd, int side);

/* BATTLE.BIN (loaded alongside) */
void LoadStageEffects_800BC878(void);
int AreStageEffectsLoaded_800BC8E8(void);
void TickUnitStatus_800BF7C4(UnitStatus* unit, short* hpLoss, short* mpLoss);
int GetStatusCommand_800BFA4C(int flags, int prevFlags);

/* exe-side, to move to <exe header> */
/* main.h declares these too, but can't be included here: it has hitNumberTasks_8008D778 as int[2] (main.c), the code
   uses it as a task list head like the other two (BATTLE.BIN's battle_3.c too) -> main.h: EventNode* hitNumberTasks_8008D778 */
extern void DrawUnitStatusWindow_8002F1C8(UnitStatus* unit, int gaugeArg, int highlight, int time, RECT* rect, int ot,
                                          int flags); // -> unit_gauges.h

#endif
