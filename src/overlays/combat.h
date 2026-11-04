// COMBAT.BIN: declarations shared by its source files
#ifndef _COMBAT_H_
#define _COMBAT_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "actor.h"
#include "engine.h"
#include "minion_init.h"
#include "unit_stats.h"
#include "camera.h"
#include "LIBSND.H"
#include "sound.h"
#include "data_decls.h"
#include "MEMORY.H"

// parameters of StartModelTask_80010850 (0x34 bytes), built from a minion by BuildMinionModelParams_800A05E0
typedef struct CombatModelParams
{
    int count_0;        // number of different parts
    int parts_4[3];
    int weights_10[3];
    int modelId_1C;
    int texPart_20;     // parts_4 index of the model the textures come from
    int angle_24;
    int texId_28;       // model id to take the textures from
    int main_2C;        // parts_4 index of the model whose animations are kept
    int vram_30;        // ModelVramSlot* (ModelTaskState.vram_34)
} CombatModelParams;

typedef struct CombatSlot
{
    int task_0;         // StartModelTask_80010850 id, -1 = free
    Minion* minion_4;
    CombatModelParams params_8;
    Actor* actor_3C;
} CombatSlot;

typedef struct CombatTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombatTask;

// GetTopSpecies_800338DC output: the three main ancestor species and their weights
typedef struct CombatTopSpecies
{
    unsigned char species[4];
    int pad_4;
    int weights[3];
} CombatTopSpecies;


typedef struct CombatVramPos
{
    unsigned short x;
    unsigned short y;
} CombatVramPos;

extern int dword_800A05A0;
extern short combatCursor_800A1BBC[4];
extern short combatMenuChoice_800A1BC4;
extern unsigned char player2Pad_800A38D8;
extern unsigned char curPlayer_800A38D9;
extern unsigned char rosterFill_800A38DA;
extern unsigned char selMode_800A38DB;
extern unsigned char battleResult_800A38DC;
extern int dword_800A38E0;
extern int combatTaskDesc_800A38E4[6];
extern int combatModelLoaderDesc_800A38FC[6];
extern int combatActorTaskDesc_800A3914[6];
extern int enemyWindowTaskDef_800A392C[6];
extern int announcerTaskDef_800A3944[6];
extern int combatCameraTaskDesc_800A395C[6];
extern int combatFadeTaskDesc_800A3974[6];
extern void *combatTaskList_800A398C[25];
extern int stageOverlays_800A39F0[6];
extern CombatSlot combatSlots_800A3A08[2];
extern int combatFlags_800A3A88; // bit 0: COMBSTRT goes on to COMBBTL (else back to COMBSEL)
extern int stage_800A3A8C; // stageOverlays_800A39F0 index: 0 CUI, 1 SEL, 2 LOAD, 3 STRT, 4 BTL, 5 RSLT
extern unsigned char sideWins_800A3A90[4];
extern int curPad_800A3A94;
extern unsigned char sideResult_800A3A98[8];
extern int prevStage_800A4070;
extern int dword_800A4074;
extern int sideSlot_800A4078[2];
extern int stageOvlRequest_800A4080;

extern Minion rosters_800A1BC8[2][15];
extern Minion teams_800A3AA0[2][3];

void BuildMinionModelParams_800A05E0(Minion* minion, CombatModelParams* params, int vram);
int GetElementHueAngle_800A0898(unsigned char* elements);
int ElementMixAngle_800A0968(unsigned char* elements);
void InitCombatSlots_800A0A28(void);
void FreeCombatSlots_800A0A6C(void);
void StartSlotModel_800A0ACC(int i, Minion* minion);
int RunSlotModelTask_800A0B3C(int i);
void FreeSlotModel_800A0B70(int i);
void CreateSlotActor_800A0BA8(int i, int* pos, short* rot);
void DestroySlotActor_800A0D1C(int i);
void LoadModelTexToVram_800A0D64(int vramSlot, int modelId);
void MoveSlotActorTo_800A0E1C(int i, int* pos);
int IsSlotActorIdle_800A0EE8(int i);
int IsSlotActorReady_800A0F1C(int i);
ShortPair StartSlotAction_800A0F50(int i, int* cmd, int x);
void TriggerSlotEffect_800A0FF0(int i, int* cmd, int x);
int GetSlotHitFrame_800A1034(int i, unsigned int idx);
void SetSlotStatusTint_800A1068(int i);
int GetSlotAncestors_800A10A4(int i);
UnitStatus* GetSlotStatus_800A10C0(int i);
int* GetSlotPos_800A10DC(int i);
int* GetSlotBonePos_800A10F8(int i);
void GetSlotEffectTarget_800A111C(int i, EffectTarget* out);
int GetSlotSkills_800A11A0(int i);
int GetSlotMagicBits_800A11BC(int i);
Minion* GetSlotMinion_800A11D8(int i);
void StartCombatCamera_800A11F4(void);
void StopCombatCamera_800A127C(void);
void ResetCombatCamera_800A12B8(void);
int CombatMain_800A1324(void);
void CombatInit_800A13A0(CombatTask* t);
void CombatFree_800A148C(void);
void CombatWaitUiTiy_800A14AC(CombatTask* t);
void CombatLoadStageOvl_800A14F0(CombatTask* t);
void CombatWaitStageOvl_800A1554(CombatTask* t, int x);
void CombatEnterStage_800A15B4(CombatTask* t, int x);
void CombatNextStage_800A16FC(CombatTask* t);
void DrawMinionNameLevel_800A1844(Minion* minion, unsigned short* pt, unsigned int flags);
int IsMinionSlotEmpty_800A1934(Minion* minion);
int IsMinionFainted_800A1958(Minion* minion);
void ClearMinionSlot_800A197C(Minion* minion);
void CopySaveMinionsToRoster_800A1988(void);
int CountMinions_800A1A3C(Minion* minions, int len);
int CountTeamMinions_800A1AAC(int side);
int CountRosterMinions_800A1AEC(int side);
void GetCombatPortraitPoly_800A1B2C(int i, void* poly);

/* the stage overlays' entry tasks (combatTaskList_800A398C / CombatEnterStage_800A15B4) */
void VersusResultTask_800A40E0(); // COMBRSLT.BIN
void CombLoadStart_800A40FC();    // COMBLOAD.BIN
void VersusSetupTask_800A4170();  // COMBSTRT.BIN
void CombSelMain_800A4360();      // COMBSEL.BIN
void VersusIntroTask_800A4394();  // COMBCHUI.BIN
void CombBtlStart_800A4B8C();     // COMBBTL.BIN

/* exe-side, to move to <exe header> */
extern char* dword_8007DC78;                   // -> globals.h: the combat slots' model vram areas (0x40 bytes each)
extern CombatVramPos dword_8007DCAC[];         // -> globals.h: portrait image vram positions
extern CombatVramPos dword_8007DCBC[];         // -> globals.h: portrait clut vram positions
extern Minion saveMinions_8008BEF8[];          // -> globals.h
extern short defaultBones_80079140[];          // -> globals.h: default bone table
extern CameraView cameraState_8008D4F0;        // -> camera.h
extern void sub_800376A0(void* a, void* b);    // = FreeCameraTask_800376A0 (camera.c), an EventEntryFn: funcs.h declares it (void)
extern int GetActorHitFrame_80018E5C(Actor* actor, unsigned int idx);  // -> minion_init.h
extern void SetActorStatusTint_80018EBC(void* actor, UnitStatus* status); // -> minion_init.h
extern ShortPair StartCommandAction_80018A4C(Actor* obj, int* cmd, ActorScriptCmd** scripts, int c); // -> effect_cmd.h
extern void SetFadeMode_8001C19C(int a, int b); // -> engine.h
extern void InitActors_8001D378(void);          // -> engine.h
extern void DestroyActor_8001D600(Actor* actor); // -> engine.h
extern void TriggerActorEffect_8001E28C(Actor* actor); // -> engine.h
extern int StartModelTask_80010850(void* params); // -> party.h
extern int QueueFileRequest_8003BC84(FileRequestDesc* req); // -> cd.h
extern int ratan2Degrees_8003B56C(int x, int y); // -> cd.h
extern int PlayMusic_800300E0(int idx, int unused); // -> sound.h
extern void LoadUiTiy_8002BF74(void);           // -> tiy.h (ui_sprites.c)
extern void DrawSmallText_8002FAA0(int align, void* pos, unsigned char* text, int ot); // -> party_window.h
extern void DrawSmallNumber3_8002C290(void* pos, int value, int ot); // -> tiy.h (ui_sprites.c)
extern void DrawElementIconsRow_8002B1B0(int mask, void* pos, int ot); // -> menu_window.h

#endif
