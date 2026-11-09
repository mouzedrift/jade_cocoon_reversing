// NAME.BIN: declarations shared by its source files
#ifndef _NAME_H_
#define _NAME_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"
#include "main.h"
#include "pad_text.h"
#include "font.h"
#include "menu_window.h"
#include "engine.h"
#include "util.h"
#include "event.h"
#include "sound_seq.h"
#include "ui_sprites.h"

// a cursor area of the screen: the character grid, the page selector, the commands
typedef struct
{
    short id_0;
    short cursorFlags_2; // NameCursor.flags: 1 wraps horizontally, 2 vertically, 4..0x20 leave the area
    short count_4;       // character pages (character grid only)
    short cols_6;
    short rows_8;
    short sA;
    short cellW_C;
    short cellH_E;
    short x_10;
    short y_12;
} NameGrid;

typedef struct
{
    DVECTOR pos;
    const char* chars_4;
} NameCharRow;


typedef struct NameBuf
{
    short s[11];
} NameBuf;

typedef struct
{
    int mask;
    int result;
} NameCursorTbl;

/* the types of name.c */
typedef struct
{
    unsigned short flags_0;
    char pad_2[2];
    int moveResult_4; // MoveCursorWithSfx_800B80E4 result
    short focus_8; // 0 character grid, 1 page selector, 2 commands
    short page_A;
    short cursor_C;
    unsigned short gridCursor_E;
    unsigned char name_10[20]; // SJIS characters, the first byte of a full-width character is >= 0x81
    char c_24;
    char c_25;
    short pad_26;
    short savedName_28[10];
    short pad_3C[2];
    unsigned char* nameDest_40;
    short length_44; // length of name_10 in bytes
} NameEntry;




typedef struct
{
    short x;
    short y;
    void* text;
} NameTextItem;

/* NAME functions */
extern void StartNameEntry_800B6E4C(unsigned char* nameDest, int flags);
extern void NameEntryTask_800B6FD8(EventEntry* e, NameEntry* entry);
extern void UpdateNameEntry_800B70F4(NameEntry* entry);
extern void DrawNameField_800B7414(NameEntry* entry);
extern void DrawCharRow_800B75EC(NameCharRow row);
extern void MoveNameCursor_800B78EC(NameEntry* entry);
extern void HandleCharGridInput_800B7A88(NameEntry* entry);
extern void InputNameChar_800B7AB4(NameEntry* entry);
extern void DeleteNameChar_800B7C68(NameEntry* entry);
extern void ClampNameLength_800B7CA4(NameEntry* entry);
extern void SwitchCharPage_800B7CD8(NameEntry* entry);
// Start jumps to the commands, Select restores the saved name (flags 8)
extern void HandleNameShortcutButtons_800B7D60(NameEntry* entry);
extern void HandlePageSelectInput_800B7DC4(NameEntry* entry);
extern void HandleNameCommandInput_800B7E30(NameEntry* entry);
extern void RestoreSavedName_800B7F08(NameEntry* entry);
extern int SavedNameLength_800B7F70(NameEntry* entry);
extern void ResetNameToDefault_800B7FA0(NameEntry* entry);
extern int IsNameBlank_800B7FD8(unsigned char* name);
extern void NameEntryNop_800B8018(void* name); // empty; called with the name buffer
extern void WrapGridCursor_800B8020(GridCursor* cursor, int dir);
extern int MoveCursorWithSfx_800B80E4(GridCursor* cursor);

/* NAME data */
extern int nameOverlayId_800B6D00;
extern const char charRowBlank_800B6D04[28];
extern const char charRowDigits2_800B6D20[28];
extern const char charRowDigits1_800B6D3C[28];
extern const char aYz_800B6D58[28];
extern const char aMnopqrstuvwx_800B6D74[28];
extern const char aAbcdefghijkl_800B6D90[28];
extern const char aYZ_800B6DAC[28];
extern const char aMNOPQRSTUVWX_800B6DC8[28];
extern const char aABCDEFGHIJKL_800B6DE4[28];
extern const char aABC_800B6E00[];
extern const char a123_800B6E08[];
extern const char aCancel_800B6E10[];
extern const char aSelect_800B6E20[];
extern const NameBuf nameBufInit_800B6E30;
extern const char nameUnderlineChar_800B6E48[];
extern NameCharRow charPages_800B8190[2][7];
extern NameGrid cursorGrids_800B8200[3];
extern MenuWindowItem cmdItemDefault_800B823C[2];
extern MenuWindowItem cmdItemRestore_800B8274[2];
extern MenuWindowItem cmdItemOk_800B82AC[2];
extern MenuWindowItem* cmdItemLists_800B82E4[4];
extern MenuWindowList cmdMenu_800B82F4;
extern MenuWindowItem pageItemAbc_800B830C[2];
extern MenuWindowItem pageItem123_800B8344[2];
extern MenuWindowItem* pageItemLists_800B837C[3];
extern MenuWindowList pageMenu_800B8388;
extern ButtonHelpEntry helpBar_800B83A0[3];
extern char defaultName_800B83B8[0x10];
extern short cursorWrapMasks_800B83C8[4];
extern short cursorWrapDirs_800B83D0[4];
extern NameCursorTbl cursorExitTbl_800B83D8[4];
extern int nameEntryActive_800B83F8;

/* SHOPCTRL overlay (resident under NAME) */
extern void ShopCtrlRequestShop_800B6CA0();

/* exe-side, to move to <exe header> */
extern int charWidthThresholds_80086898[][12];

#endif
