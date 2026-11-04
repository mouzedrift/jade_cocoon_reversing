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

// a menu item drawn by DrawMenuItemWithWindow_8002ADB4 (0x1C bytes, CombSelItem)
typedef struct CombRsltText
{
    unsigned short flags_0;
    short type_2;
    int text_4; // string, or sprite index for type 1
    int sprts_8;
    int tpages_C;
    unsigned short x_10;
    unsigned short y_12;
    int size_14;
    int margin_18;
} CombRsltText;

// the window colour DrawWindow_80042460 takes (CombSelBox)
typedef struct CombRsltBox
{
    short col_0;
    char state_2;
    char frame_3;
} CombRsltBox;

typedef struct CombRsltPos
{
    unsigned short x;
    unsigned short y;
} CombRsltPos;

extern int dword_800A4088;
extern const CombRsltText resultTitleItem_800A408C;
extern const CombRsltText minionLabelItem_800A40A8;
extern const CombRsltText minionHpItem_800A40C4;
extern MenuCursor slotCursor_800A47E8;
extern int dword_800A47F4;
extern CombRsltText playerLabelItemP1_800A47F8;
extern CombRsltText playerLabelItemP2_800A4814;
extern CombRsltText* playerLabelItems_800A4830[2];
extern CombRsltText resultItemP1_800A4838;
extern CombRsltText resultItemP2_800A4854;
extern CombRsltText* resultItems_800A4870[2];
extern CombRsltText scoreWindowP1_800A4878;
extern CombRsltText scoreWindowP2_800A4894;
extern CombRsltText* scoreWindows_800A48B0[2];
extern int slotLabelSprites_800A48B8[3];
extern CombRsltPos minionSlotPos_800A48C4[2][3];

void VersusResultTask_800A40E0(CombatTask* task);
void VersusResultFadeOut_800A41E4(CombatTask* task, int arg);
void DrawPlayerResult_800A4240(int player);
void DrawScorePair_800A444C(unsigned short* pos, int ot, int oppWins, int ownWins);
void DrawResultMinion_800A4554(int player, int slot, CombRsltBox* box);

/* exe-side, to move to <exe header> */
extern unsigned short uiColor_8008B590; // -> globals.h
extern void DrawMenuItemWithWindow_8002ADB4(void* item, void* window, int ot, int time); // -> menu_window.h
extern void DrawUiTiySprt_8002C06C(void* pos, int sprite, int ot); // -> tiy.h (ui_sprites.c)
extern void DrawMenuBackground_8002BE10(void);
extern void DrawHpGauge_8002F078(void* status, void* pos, int a, int ot); // -> unit_gauges.h
extern void DrawWindow_80042460(void* rect, void* box, void* ot, int time); // -> event.h

#endif
