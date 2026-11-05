// COMBRSLT.BIN: declarations shared by its source files
#ifndef _COMBRSLT_H_
#define _COMBRSLT_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "pad_text.h"
#include "combat.h"
#include "menu_window.h"
#include "engine.h"
#include "event.h"
#include "ui_sprites.h"



typedef struct CombRsltPos
{
    unsigned short x;
    unsigned short y;
} CombRsltPos;

extern int dword_800A4088;
extern const MenuWindowItem resultTitleItem_800A408C;
extern const MenuWindowItem minionLabelItem_800A40A8;
extern const MenuWindowItem minionHpItem_800A40C4;
extern MenuCursor slotCursor_800A47E8;
extern int dword_800A47F4;
extern MenuWindowItem playerLabelItemP1_800A47F8;
extern MenuWindowItem playerLabelItemP2_800A4814;
extern MenuWindowItem* playerLabelItems_800A4830[2];
extern MenuWindowItem resultItemP1_800A4838;
extern MenuWindowItem resultItemP2_800A4854;
extern MenuWindowItem* resultItems_800A4870[2];
extern MenuWindowItem scoreWindowP1_800A4878;
extern MenuWindowItem scoreWindowP2_800A4894;
extern MenuWindowItem* scoreWindows_800A48B0[2];
extern int slotLabelSprites_800A48B8[3];
extern CombRsltPos minionSlotPos_800A48C4[2][3];

void VersusResultTask_800A40E0(CombatTask* task);
void VersusResultFadeOut_800A41E4(CombatTask* task, int arg);
void DrawPlayerResult_800A4240(int player);
void DrawScorePair_800A444C(unsigned short* pos, int ot, int oppWins, int ownWins);
void DrawResultMinion_800A4554(int player, int slot, WindowStyle* box);

/* exe-side, to move to <exe header> */
extern unsigned short uiColor_8008B590; // -> globals.h
extern void DrawHpGauge_8002F078(void* status, void* pos, int a, int ot); // -> unit_gauges.h

#endif
