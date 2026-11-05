// COMBLOAD.BIN: declarations shared by its source files
#ifndef _COMBLOAD_H_
#define _COMBLOAD_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "menu_draw.h"
#include "pad_text.h"
#include "combat.h"
#include "load.h"
#include "util.h"
#include "event.h"
#include "model.h"
#include "cd.h"
#include "ui_sprites.h"
#include "menu_window.h"



extern int dword_800A4088;
extern MenuCursor cardSlotCursor_800A468C;
extern MenuCursor dataCursor_800A4698;
extern MenuWindowItem dataRow0_800A46A4[2]; // the row + its end
extern MenuWindowItem dataRow1_800A46DC[2]; // the row + its end
extern MenuWindowItem dataRow2_800A4714[2]; // the row + its end
extern MenuWindowItem dataRow3_800A474C[2]; // the row + its end
extern MenuWindowItem dataRow4_800A4784[2]; // the row + its end
extern MenuWindowItem* dataRows_800A47BC[6];
extern MenuWindowList dataMenuWin_800A47D4;
extern int cardSelectState_800A47F0;
extern int loadOvlRequest_800A47F4;

void CombLoadStart_800A40FC(CombatTask* task);
void CombLoadWaitOverlay_800A4140(CombatTask* task);
void CombLoadWaitMenu_800A41A8(CombatTask* task);
void CardSelectScreen_800A41FC(CombatTask* task);
void DrawTitleWindow_800A4364(void);
void DrawTitleWindow2_800A4420(void);
void DrawDataHeaderWindows_800A44DC(void);

/* LOAD.BIN functions not declared in load.h (LOAD.BIN is loaded by CombLoadStart_800A40FC) */
extern int GetLoadMenuLoaded_800B7914(void);
extern int IsLoadMenuActive_800B793C(void);
extern int IsCardReady_800BAE24(int slot);
extern void DrawCardSlotMenu_800BB4A8(int slot);

/* exe-side, to move to <exe header> */
extern unsigned short uiColor_8008B590; // -> globals.h

#endif
