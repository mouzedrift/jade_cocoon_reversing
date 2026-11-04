// COMBAT.BIN: declarations shared by its source files
#ifndef _COMBAT_H_
#define _COMBAT_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "actor.h"
#include "engine.h"
#include "minion_init.h"
#include "main.h"
#include "unit_stats.h"

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
extern int sideWins_800A3A90[4];
extern int prevStage_800A4070;
extern int dword_800A4074[3];
extern int stageOvlRequest_800A4080;

extern Minion rosters_800A1BC8[2][15];
extern Minion teams_800A3AA0[2][3];

#endif
