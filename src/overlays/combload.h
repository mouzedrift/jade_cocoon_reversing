// COMBLOAD.BIN: declarations shared by its source files
#ifndef _COMBLOAD_H_
#define _COMBLOAD_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "pad_text.h"
#include "combat.h"
#include "load.h"

// the window colour DrawWindow_80042460 takes (CombSelBox)
typedef struct CombLoadBox
{
    short col_0;
    char state_2;
    char frame_3;
} CombLoadBox;

// a menu entry / window (0x38 bytes, CombComItem)
typedef struct CombLoadItem
{
    unsigned short flags;
    short type_2;
    void* text_4;
    int sprts_8;
    int tpages_C;
    short x_10;
    short y_12;
    int rest[9];
} CombLoadItem;

// a window list drawn by DrawMenuWindows_8002A5A4 (CombSelMenu)
typedef struct CombLoadMenu
{
    int flags_0;
    unsigned int time_4;
    int anim_8;
    int cursor_C;
    CombLoadItem** items_10;
    int ot_14;
} CombLoadMenu;

extern int dword_800A4088;
extern MenuCursor cardSlotCursor_800A468C;
extern MenuCursor dataCursor_800A4698;
extern CombLoadItem dataRow0_800A46A4;
extern CombLoadItem dataRow1_800A46DC;
extern CombLoadItem dataRow2_800A4714;
extern CombLoadItem dataRow3_800A474C;
extern CombLoadItem dataRow4_800A4784;
extern CombLoadItem* dataRows_800A47BC[6];
extern CombLoadMenu dataMenuWin_800A47D4;
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
extern void DrawMenuWindows_8002A5A4(void* list);            // -> menu_draw.h
extern void DrawMenuBackground_8002BE10(void);

#endif
