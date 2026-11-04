// COMBSTRT.BIN: declarations shared by its source files
#ifndef _COMBSTRT_H_
#define _COMBSTRT_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"

extern int dword_800A4088;
extern const char aShufflingMinion_800A408C[];
extern const char aStartFight_800A40C0[];
extern const char aShuffleMinionOr_800A40DC[];
extern const char aAllowMinionChan_800A4108[];
extern const char *stateQuestions_800A4C04[4];
extern unsigned char setupState_800A4C14;
extern unsigned short stateDefaultSel_800A4BFC[4];
extern short windowAnimStep_800A4C8C;
extern int playerLabelItemP1_800A4C18[7];
extern int playerLabelItemP2_800A4C34[7];
extern void *playerLabelItems_800A4C50[2];
extern int slotLabelSprites_800A4C58[3];
extern short minionSlotPos_800A4C64[2][3][2];
extern void (*setupStateHandlers_800A4C7C[4])();
extern short shuffleLimit_800A4C90;
extern short shufflePhase_800A4C92;
extern short shuffleTimer_800A4C94;
extern short shuffleDelay_800A4C96;

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
extern CombStrtMenu dword_80082784;
extern CombStrtPos dword_80082708;
extern CombStrtPos dword_80082740;
extern char dword_800826E8[];
extern void HealTeams_800A48C0();
extern void DrawTeam_800A4958(int i);
extern void DrawMenuWindows_8002A5A4(void* p);
extern void DrawButtonHelpBar_8002B004(void* a, void* b, int c);
extern void DrawMenuBackground_8002BE10();
extern void UpdateMenuCursor_8003D794(void* p, int a);
extern void DrawHpGauge_8002F078(void* a, void* b, int c, int d);
extern void DrawMinionNameLevel_800A1844(void* a, void* b, int c);
extern void DrawWindow_80042460(void* a, void* b, void* c, int d);

#endif
