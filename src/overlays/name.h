// NAME.BIN: declarations shared by its source files
#ifndef _NAME_H_
#define _NAME_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"

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
    int f8;
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

extern int overlayId_800B6D00;
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
extern char defaultName_800B83B8[0x14];
extern int cursorWrapMasks2_800B83CC;
extern short cursorWrapDirs_800B83D0[4];
extern NameCursorTbl cursorExitTbl_800B83D8[4];
extern int nameEntryActive_800B83F8;

#endif
