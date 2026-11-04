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
    char* chars_4;
} NameCharRow;

// header of a DrawMenuWindows_8002A5A4 menu (followed by its item lists and OT index)
typedef struct
{
    int mode_0;
    int time_4;
    int anim_8;
    int cursor_C;
} NameMenu;

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
    int nameDest_40;
    short length_44; // length of name_10 in bytes
} NameEntry;

// window style for DrawWindow_80042460
typedef struct
{
    unsigned short color_0;
    unsigned char colors_2; // GetWindowColors_8004226C
    unsigned char frame_3;  // DrawWindowFrame_80041ED0
} NameWinStyle;

typedef struct
{
    int flags;
    unsigned short unused_4;
    unsigned short pos_6;
    short cols_8;
    short rows_A;
} NameCursor;

typedef struct
{
    unsigned short color;
    unsigned char colors_2;
    unsigned char frame_3;
} NameWinColor;

typedef struct
{
    short x;
    short y;
    void* text;
} NameTextItem;

/* NAME functions */
extern void StartNameEntry_800B6E4C(int nameDest, int flags);
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
extern void WrapGridCursor_800B8020(NameCursor* cursor, int dir);
extern int MoveCursorWithSfx_800B80E4(NameCursor* cursor);

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
extern int cmdItemDefault_800B823C[14];
extern int cmdItemRestore_800B8274[14];
extern int cmdItemOk_800B82AC[14];
extern void *cmdItemLists_800B82E4[4];
extern NameMenu cmdMenu_800B82F4;
extern void *cmdMenuItems_800B8304[2];
extern int pageItemAbc_800B830C[14];
extern int pageItem123_800B8344[14];
extern void *pageItemLists_800B837C[3];
extern NameMenu pageMenu_800B8388;
extern void *pageMenuItems_800B8398[2];
extern char helpBar_800B83A0[24];
extern char defaultName_800B83B8[0x10];
extern short cursorWrapMasks_800B83C8[4];
extern short cursorWrapDirs_800B83D0[4];
extern NameCursorTbl cursorExitTbl_800B83D8[4];
extern int nameEntryActive_800B83F8;

/* SHOPCTRL overlay (resident under NAME) */
extern void ShopCtrlRequestShop_800B6CA0();

/* exe-side, to move to <exe header> */
extern void DrawMenuWindows_8002A5A4(void* p);
extern unsigned short uiColor_8008B590;
extern void DrawWindow_80042460(void* rect, void* box, void* ot, int a3);
extern void DrawMenuBackground_8002BE10();
extern void EncodeName_8003F7C8(void* name, int dest);
extern void DecodeText_8003F748(int a, void* name);
extern void SetFadeMode_8001C19C(int a, int b); // engine.c: K&R, one argument
extern void DrawUiTiySprt_8002C06C(void* pos, int idx, int ot);
extern int charWidthThresholds_80086898[][12];
extern int MoveGridCursorP1_8003D630();

#endif
