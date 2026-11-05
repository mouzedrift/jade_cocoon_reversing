// COMBSTRT.BIN: declarations shared by its source files
#ifndef _COMBSTRT_H_
#define _COMBSTRT_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "pad_text.h"
#include "combat.h"
#include "menu_window.h"
#include "util.h"
#include "event.h"

// the window colour DrawWindow_80042460 takes (CombSelBox)
typedef struct CombStrtBox
{
    short col_0;
    char state_2;
    char frame_3;
} CombStrtBox;


extern int dword_800A4088;
extern MenuCursor yesNoCursor_800A4BF0;
extern unsigned short stateDefaultSel_800A4BFC[4];
extern const char* stateQuestions_800A4C04[4];
extern unsigned char setupState_800A4C14;
extern MenuWindowItem playerLabelItemP1_800A4C18;
extern MenuWindowItem playerLabelItemP2_800A4C34;
extern MenuWindowItem* playerLabelItems_800A4C50[2];
extern int slotLabelSprites_800A4C58[3];
extern short minionSlotPos_800A4C64[2][3][2];
extern void (*setupStateHandlers_800A4C7C[4])();
extern short windowAnimStep_800A4C8C;
extern short shuffleLimit_800A4C90;
extern short shufflePhase_800A4C92;
extern short shuffleTimer_800A4C94;
extern short shuffleDelay_800A4C96;
extern const MenuWindowItem titleItem_800A4138;
extern const MenuWindowItem minionLabelItem_800A4154;

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
extern unsigned short word_8008D3FC; // low half of frameCount_8008D3FC (globals.h), read with lhu
extern unsigned short uiColor_8008B590; // -> globals.h
extern int rand(void);
extern void DrawMenuBackground_8002BE10(void);
extern void DrawHpGauge_8002F078(void* status, void* pos, int a, int ot); // -> unit_gauges.h

#endif
