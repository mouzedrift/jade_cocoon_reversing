// COMBSEL.BIN: declarations shared by its source files
#ifndef _COMBSEL_H_
#define _COMBSEL_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "effect_data.h"
#include "main.h"
#include "pad_text.h"
#include "menu_window.h" // MenuWindowItem / MenuWindowList (menu_draw.h)
#include "util.h"


// the window colour DrawWindow_80042460 takes
typedef struct CombSelBox
{
    unsigned short color_0;
    unsigned char state_2; // 0 normal, 1 blinking, 2 selected
    unsigned char frame_3;
} CombSelBox;

// DrawScrollArrows_8002B8DC: an arrow kind (scrollArrowIcons_8008279C) and an orientation (quarter turns)
typedef struct CombSelArrow
{
    unsigned short kind_0;
    unsigned short dir_2;
} CombSelArrow;




typedef struct CombSelTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombSelTask;

// the main executable's Yes / No window (its two rows and the window list)

// COMBAT (the overlay below this one)
extern MenuCursor combatCursor_800A1BBC; // the main menu cursor
extern short combatMenuChoice_800A1BC4;          // == combatCursor_800A1BBC.cursor_8
extern Minion rosters_800A1BC8[2][15];
extern unsigned char player2Pad_800A38D8;
extern unsigned char curPlayer_800A38D9;
extern unsigned char selMode_800A38DB;
extern int curPad_800A3A94;
extern Minion teams_800A3AA0[2][3];
extern void CombatNextStage_800A16FC();
extern void DrawMinionNameLevel_800A1844(Minion* m, unsigned short* pt, unsigned int flags);
extern int IsMinionSlotEmpty_800A1934(Minion* m);
extern void ClearMinionSlot_800A197C(Minion* m);
extern int CountTeamMinions_800A1AAC(int side);

extern void CombSelMain_800A4360(CombSelTask* t, int a);
extern void PlaceSideWindows_800A4C74(void);
extern void CompactTeam_800A4D64(Minion* team);
extern void CompactTeams_800A4E4C(void);
extern void MainMenuInput_800A4E94(CombSelTask* t, int a);
extern void NextOrFight_800A5080(CombSelTask* t, int a);
extern void TeamSlotInput_800A5188(void);
extern void ListInput_800A53B0(void);
extern void QuitConfirmInput_800A54A0(CombSelTask* t);
extern void QuitToTitle_800A5538(CombSelTask* t);
extern int AllSlotsEmpty_800A5560(Minion* team, int count);

/* exe-side, to move to <exe header> */
extern void PlaySfx_80031494(int id);
extern void DrawSmallNumber3_8002C290(void* pos, int value, int ot);
extern void DrawUiTiySprt_8002C06C(void* pos, int idx, int ot);
extern void DrawWindow_80042460(void* r, void* col, void* ot, int time);
extern void DrawScrollArrows_8002B8DC(CombSelArrow arrow, void* cursor, void* pos, int ot);
extern void DrawMenuBackground_8002BE10(void);

extern int dword_800A4088;
extern const MenuWindowItem titleItem_800A4238;
extern const MenuWindowItem playerItems_800A4254[2];
extern const MenuWindowItem listHeaderItem_800A428C;
extern const int dword_800A4348;
extern MenuWindowItem teamRow0_800A55C4[2];
extern MenuWindowItem teamRow1_800A55FC[2];
extern MenuWindowItem teamRow2_800A5634[2];
extern MenuWindowItem *teamRows_800A566C[4];
extern MenuWindowList teamWindow_800A567C;
extern MenuWindowItem listRow0_800A5694[2];
extern MenuWindowItem listRow1_800A56CC[2];
extern MenuWindowItem listRow2_800A5704[2];
extern MenuWindowItem listRow3_800A573C[2];
extern MenuWindowItem listRow4_800A5774[2];
extern MenuWindowItem listRow5_800A57AC[2];
extern MenuWindowItem *listRows_800A57E4[7];
extern MenuWindowList listWindow_800A5800;
extern MenuWindowItem loadRow_800A5818[2];
extern MenuWindowItem enterRow_800A5850[2];
extern MenuWindowItem deleteRow_800A5888[2];
extern MenuWindowItem nextRow_800A58C0[2];
extern MenuWindowItem quitRow_800A58F8[2];
extern MenuWindowItem *mainRows_800A5930[6];
extern MenuWindowList mainWindow_800A5948;
extern MenuCursor teamCursor_800A5960;
extern MenuCursor listCursor_800A596C;
extern MenuCursor quitCursor_800A5978;
extern MenuCursor *modeCursors_800A5984[4];
extern MenuWindowList *modeWindows_800A5994[4];
extern int playerIcons_800A59A4[2];
extern int nextIcons_800A59AC[2];
extern void (*modeHandlers_800A59B4[4])();
extern const char *mainMenuHelp_800A59C4[5];
extern const char *quitPrompt_800A59D8[1];
extern const char *nextTextP1_800A59DC[1];
extern const char *nextTextP2_800A59E0[1];
extern ButtonHelpEntry buttonHelpP1_800A59E4[4];
extern ButtonHelpEntry buttonHelpP2_800A5A04[4];

#endif
