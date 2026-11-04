// SHOPENTR.BIN: declarations shared by its source files
#ifndef _SHOPENTR_H_
#define _SHOPENTR_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"
#include "main.h"

typedef struct
{
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
} ShelfRect;

typedef struct
{
    short confirmNext_0; // state after confirm (-1: chosen in ShelfMenuConfirm_800B7144)
    short cancelNext_2;  // state after cancel (-2: none)
    short cursorRect_4;  // shelfCursorRects_800B7CE8 index
    short pad_6;
    int pad_8;
    int pad_C;
    int timed_10; // advances by itself after a progress gauge
} ShelfMenuState;

typedef struct
{
    unsigned short cursorRect_0[4];
    short cursor_8; // MenuCursor row
    short scroll_A;
    unsigned int flags_C; // 1: a timed state is running (ShelfMenuProgress_800B73A8)
    unsigned int pages_10;
    short state_14;
    short progress_16;
} ShelfMenu;

/* SHOPENTR functions */
int IsShelfMenuActive_800B6F0C(void);
void StartShelfMenu_800B6F1C(void);
void ShelfMenuTask_800B7000(EventEntry* task, ShelfMenu* menu);
void ShelfMenuConfirm_800B7144(ShelfMenu* menu);
void ShelfMenuCancel_800B72D4(ShelfMenu* menu);
int ShelfMenuProgress_800B73A8(ShelfMenu* menu);
void DrawShelfMenu_800B7440(ShelfMenu* menu);
void SetShelfMenuCursorRect_800B7520(ShelfMenu* menu);
void DrawCardCheckPage_800B7594(ShelfMenu* menu);
void DrawCardSelectPage_800B75DC(ShelfMenu* menu);
void DrawShelfSelectPage_800B7684(ShelfMenu* menu);
void DrawShelfContentsPage_800B7858(ShelfMenu* menu);
void DrawPageCount_800B7A90(ShelfRect* pos, short num, short total);
void DrawNumberPair_800B7B64(ShelfRect* pos, short num, short total);
void DrawZeroTime_800B7C08(ShelfRect* pos);

/* other overlays */
void ShopCtrlRequestShop_800B6CA0(void);       // SHOPCTRL.BIN (shopctrl.h)
Minion* GetShopMinion_800B9C5C(int i);         // SHOP.BIN (shop.h), not loaded with this overlay

/* exe-side, to move to <exe header> (named in the comment) */
void DrawGauge_8002BA54(void* gauge, int arg1, void* pos, int ot); // ui_gauge
void DrawElementIconsRow_8002B1B0(short mask, void* pos, short ot); // menu_window.h
void DrawMenuBackground_8002BE10(void);        // ui_sprites
void DrawSmallText_8002FAA0(int align, void* pos, void* text, short ot); // party_window.h
void UpdateMenuCursor_8003D794(ShelfMenu* menu, int arg1); // pad_text.h
void DrawText_8003E91C(int mode, const char* text, void* pos, short ot); // font.h has int ot: this overlay was built with a short one (its callers sign-extend ot)
void DrawNumber_8003EF74(void* pos, int val, short ot); // util.h
void DrawNumberRightAlignedFont1_8003F264(void* pos, int val, short ot); // util.h

/* SHOPENTR data */

extern int dword_800B6D00;
extern const char aSaved_800B6D04[];
extern const char aSaving_800B6D14[];
extern const char aNoSpace_800B6D24[];
extern const char aSaveNew_800B6D30[];
extern const char aOverwrite_800B6D48[];
extern const char aOverwriting_800B6D5C[];
extern const char aFormatting_800B6D6C[];
extern const char aFormatOrNot_800B6D84[];
extern const char aUnformatted_800B6DA0[];
extern const char aNoDataSpace_800B6DB4[];
extern const char aDataSpaceMinion_800B6DCC[];
extern const char aDataSpaceBlock_800B6DEC[];
extern const char aCardCheck2_800B6E10[];
extern const char aSlotSelect_800B6E24[];
extern const char aCardCheck1_800B6E34[];
extern const int dword_800B6E48;
extern const char aCardChecking_800B6E74[];
extern const char aCardSelect_800B6E90[];
extern const char aSlot1_800B6EA4[];
extern const char aSlot2_800B6EB0[];
extern const char aShelfSelect_800B6EBC[];
extern const char aShelf_800B6EC8[];
extern const char aMinionCount_800B6ED0[];
extern const char aTime_800B6EDC[];
extern const char aRegistered_800B6EE4[];
extern const char aName_800B6EEC[];
extern const char aRank_800B6EF4[];
extern const char aElement_800B6EFC[];
extern const char aSlash_800B6F04[];
extern const char aColon_800B6F08[];
extern int dword_800B7CC0[2];
extern unsigned short cardCheckTextPos_800B7CC8[2];
extern int dword_800B7CCC;
extern unsigned short cardSelectTitlePos_800B7CD0[2];
extern int dword_800B7CD4;
extern unsigned short slot1TextPos_800B7CD8[2];
extern int dword_800B7CDC;
extern unsigned short slot2TextPos_800B7CE0[2];
extern int dword_800B7CE4;
extern ShelfRect shelfCursorRects_800B7CE8[4];
extern ShelfMenuState shelfMenuStates_800B7D08[15];
extern unsigned int shelfStatePages_800B7E34[30];
extern int shelfMenuActive_800B7EAC;

#endif
