// COMBSTRT.BIN: declarations shared by its source files
#ifndef _COMBSTRT_H_
#define _COMBSTRT_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "pad_text.h"
#include "combat.h"

// the window colour DrawWindow_80042460 takes (CombSelBox)
typedef struct CombStrtBox
{
    short col_0;
    char state_2;
    char frame_3;
} CombStrtBox;

// a menu item drawn by DrawMenuItemWithWindow_8002ADB4 (CombSelItem)
typedef struct CombStrtWin
{
    int flagsType_0; // flags_0 | type_2 << 16
    void* icon_4;
    int sprts_8;
    int tpages_C;
    short x_10;
    short y_12;
    int size_14;
    int margin_18;
} CombStrtWin;

// a window list drawn by DrawMenuWindows_8002A5A4
typedef struct CombStrtMenu
{
    int flags_0;
    int time_4;
    int anim_8;
    int cursor_C;
    int rows_10;
    int ot_14;
} CombStrtMenu;

typedef struct CombStrtPos
{
    short flags_0;
    char pad_2[0xE];
    short x_10;
    short y_12;
} CombStrtPos;

extern int dword_800A4088;
extern MenuCursor yesNoCursor_800A4BF0;
extern unsigned short stateDefaultSel_800A4BFC[4];
extern const char* stateQuestions_800A4C04[4];
extern unsigned char setupState_800A4C14;
extern CombStrtWin playerLabelItemP1_800A4C18;
extern CombStrtWin playerLabelItemP2_800A4C34;
extern CombStrtWin* playerLabelItems_800A4C50[2];
extern int slotLabelSprites_800A4C58[3];
extern short minionSlotPos_800A4C64[2][3][2];
extern void (*setupStateHandlers_800A4C7C[4])();
extern short windowAnimStep_800A4C8C;
extern short shuffleLimit_800A4C90;
extern short shufflePhase_800A4C92;
extern short shuffleTimer_800A4C94;
extern short shuffleDelay_800A4C96;
extern const CombStrtWin titleItem_800A4138;
extern const CombStrtWin minionLabelItem_800A4154;

void VersusSetupTask_800A4170(CombatTask* t, int a);
void SetupAllowChangeInput_800A43FC(void);
void SetupShuffleInput_800A4498(void);
void SetupStartFightInput_800A4524(CombatTask* task);
void SetupShuffleAnim_800A45B8(void);
void ShuffleTeams_800A46FC(void);
void ShuffleTeam_800A473C(int side);
int PickNthFreeSlot_800A4878(int nth, int* slots, int count);
void HealTeams_800A48C0(void);
void DrawTeam_800A4958(int side);
void DrawTeamMinion_800A49DC(int side, int slot);

/* exe-side, to move to <exe header> */
extern CombStrtMenu dword_80082784;  // -> menu data (the yes/no window list)
extern CombStrtPos dword_80082708;   // -> menu data (its "yes" item)
extern CombStrtPos dword_80082740;   // -> menu data (its "no" item)
extern char dword_800826E8[];        // -> menu data (a button help bar)
extern unsigned short word_8008D3FC; // low half of frameCount_8008D3FC (globals.h), read with lhu
extern unsigned short uiColor_8008B590; // -> globals.h
extern int rand(void);
extern void DrawMenuItemWithWindow_8002ADB4(void* item, void* window, int ot, int time); // -> menu_window.h
extern void DrawMenuWindows_8002A5A4(void* list);            // -> menu_draw.h
extern void DrawButtonHelpBar_8002B004(void* entries, void* origin, int ot); // -> menu_window.h
extern void DrawMenuBackground_8002BE10(void);
extern void DrawHpGauge_8002F078(void* status, void* pos, int a, int ot); // -> unit_gauges.h
extern void DrawWindow_80042460(void* rect, void* box, void* ot, int time); // -> event.h

#endif
