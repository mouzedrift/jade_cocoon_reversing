// COMBSEL.BIN: declarations shared by its source files
#ifndef _COMBSEL_H_
#define _COMBSEL_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "effect_data.h"
#include "main.h"

// a menu item drawn by DrawMenuWindowContents_8002A710 / DrawMenuItemWithWindow_8002ADB4
typedef struct CombSelItem
{
    unsigned short flags_0; // 2: greyed out
    unsigned short type_2;  // 1: TIY sprite
    int icon_4;
    SPRT** sprts_8;
    DR_TPAGE** tpages_C;
    short x_10; // the window rect
    short y_12;
    short w_14;
    short h_16;
    short mx_18;
    short my_1A;
} CombSelItem;

// the window colour DrawWindow_80042460 takes
typedef struct CombSelBox
{
    unsigned short color_0;
    unsigned char b_2;
    unsigned char c_3;
} CombSelBox;

typedef struct CombSelArrow
{
    unsigned short a_0;
    unsigned short b_2;
} CombSelArrow;

// a menu cursor (UpdateMenuCursor_8003D794 / GetMenuCursorIndex_8003DA54)
typedef struct CombSelCursor
{
    short cols_0;
    short rows_2;
    short count_4;
    short flags_6; // 0x40: scrolls
    short index_8; // on screen
    short scroll_A;
} CombSelCursor;

extern CombSelCursor dword_800A1BBC; // COMBAT's main menu cursor

// a window list drawn by DrawMenuWindows_8002A5A4
typedef struct CombSelMenu
{
    int f0;
    int time_4;
    int f8;
    int cursor_C;
    CombSelItem** rows_10; // NULL-terminated; each row ends with an item with flags_0 & 1
    int f14;
} CombSelMenu;

// a button help bar entry (DrawButtonHelpBar_8002B004), icon -1 ends the list
typedef struct CombSelHelp
{
    int icon_0;
    const char* text_4;
} CombSelHelp;

extern CombSelMenu dword_80082784;
extern CombSelItem dword_80082708;
extern CombSelItem dword_80082740;
extern unsigned char byte_800A38D8;
extern void sub_800A1844(void* m, unsigned short* pt, unsigned int flags);
extern void DrawSmallNumber3_8002C290(void* p, int v, int ot);
extern void DrawUiTiySprt_8002C06C(void* p, int idx, int ot);
extern void DrawWindow_80042460(void* r, void* col, void* ot, int time);
extern void DrawMenuItemWithWindow_8002ADB4(void* item, void* col, int ot, int time);
extern void DrawScrollArrows_8002B8DC(CombSelArrow arrow, void* cursor, void* pos, int ot);
extern void DrawMenuWindows_8002A5A4(void* p);
extern void DrawButtonHelpBar_8002B004(void* e, void* pos, int ot);
extern void DrawMenuBackground_8002BE10(void);
extern int UpdateMenuCursor_8003D794(void* p, int pad);

extern int dword_800A4088;
extern const char aReturnToTitleSc_800A408C[];
extern const char aDeleteEnteredMi_800A40BC[];
extern const char aEnterMinionFrom_800A40EC[];
extern const char aReadMinionDataF_800A411C[];
extern const char aReturnToTitleSc_800A4164[];
extern const char aEnterPlayer2SMi_800A4194[];
extern const char aStartFighting_800A41C8[];
extern const char aEnterPlayer2SMi_800A41E8[];
extern const char aQuit_800A421C[];
extern const char aSelect_800A4228[];
extern const CombSelItem dword_800A4238;
extern const CombSelItem dword_800A4254[2];
extern const CombSelItem dword_800A428C;
extern const char aSelectSpaceToEn_800A42A8[];
extern const char aSelectMinionToD_800A42E4[];
extern const char aSelectMinionToE_800A4318[];
extern const int dword_800A4348;
extern CombSelItem dword_800A55C4[2];
extern CombSelItem dword_800A55FC[2];
extern CombSelItem dword_800A5634[2];
extern CombSelItem *dword_800A566C[4];
extern CombSelMenu dword_800A567C;
extern CombSelItem dword_800A5694[2];
extern CombSelItem dword_800A56CC[2];
extern CombSelItem dword_800A5704[2];
extern CombSelItem dword_800A573C[2];
extern CombSelItem dword_800A5774[2];
extern CombSelItem dword_800A57AC[2];
extern CombSelItem *dword_800A57E4[7];
extern CombSelMenu dword_800A5800;
extern CombSelItem dword_800A5818[2];
extern CombSelItem dword_800A5850[2];
extern CombSelItem dword_800A5888[2];
extern CombSelItem dword_800A58C0[2];
extern CombSelItem dword_800A58F8[2];
extern CombSelItem *dword_800A5930[6];
extern CombSelMenu dword_800A5948;
extern CombSelCursor dword_800A5960;
extern CombSelCursor dword_800A596C;
extern CombSelCursor dword_800A5978;
extern CombSelCursor *dword_800A5984[4];
extern CombSelMenu *dword_800A5994[4];
extern int dword_800A59A4[2];
extern int dword_800A59AC[2];
extern void (*dword_800A59B4[4])();
extern const char *dword_800A59C4[5];
extern const char *dword_800A59D8[1];
extern const char *dword_800A59DC[1];
extern const char *dword_800A59E0[1];
extern CombSelHelp dword_800A59E4[4];
extern CombSelHelp dword_800A5A04[4];

#endif
