// LOAD.BIN: declarations shared by its source files
#ifndef _LOAD_H_
#define _LOAD_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct
{
    char c[5];
} CardTag;

typedef struct
{
    int poly_0; // index into publicTiyPolyFT4s_8008D430
    short clutX_4;
    short clutY_6;
} SaveIconSrc;

typedef struct
{
    unsigned short flags_0;
    short kind_2;  // 1: a UI TIY sprite, 3: a text
    int data_4;    // the sprite index or the text
    int sprts_8;   // the sprite set (uiTiySprts_8008D620)
    int tpages_C;  // its texture pages (uiTiyTPages_8008D3F4)
    short x_10;
    short y_12;
    char window_14[8]; // the window around it
} LoadMenuItem;

typedef struct
{
    LoadMenuItem items_0[2];
} LoadMenuItemPair;

typedef struct
{
    int flags_0;  // 1 plain, 2 blinking cursor, 4 fixed cursor (DrawMenuItemWindow_8002AAF0)
    int time_4;   // blink timer (GetTime30Hz_8002C64C), 0 = no highlight
    int open_8;   // window open step out of 8 (InterpolateWindowRect_8004196C)
    int cursor_C; // the highlighted item
    LoadMenuItem** items_10;
    int ot_14;
} LoadMenuWin;

typedef struct
{
    short x_0;
    short y_2;
} LoadTextPos;

typedef struct
{
    char c[8];
} LoadWinRect;

typedef struct
{
    short x_0;
    short y_2;
    short sprite_4; // UI TIY sprite index (DrawUiTiySprt_8002C06C)
    short ot_6;
} LoadUiSprite;

typedef struct
{
    unsigned char pad_0[6];
    unsigned char cols_6; // cols_6..count_8 and flags_B: the UpdateMenuCursor_8003D794 grid parameters
    unsigned char rows_7;
    unsigned char count_8;
    unsigned char initCursor_9;
    unsigned char initScroll_A;
    unsigned char flags_B; // 0x40: scrolls
    unsigned char cursor_C;
    unsigned char scroll_D;
    unsigned char pad_E[2];
} LoadMenuRow;

typedef union
{
    char str[0x42];
    struct
    {
        unsigned short text_0[0x12];
        unsigned char level_24[4]; // the two level digits
        unsigned short slash_28;
        unsigned short place_2A[0xC];
    } f;
} SaveTitle;

extern int dword_800B66C0;
extern const char aSelectGameToLoa_800B66C4[44];
extern const char aSelectSaveLocat_800B66F0[44];
extern const char aYES_800B671C[];
extern const char aNO_800B6724[];
extern const char aExit_800B672C[];
extern const char aSelect_800B6738[];
extern const char aMEMORYCARDFull_800B6748[36];
extern const char aDoNotRemoveMEMO_800B676C[56];
extern const char aFormattingMEMOR_800B67A4[52];
extern const char aLoading_800B67D8[24];
extern const char aSaving_800B67F0[20];
extern const char aNoSaveGameData_800B6804[40];
extern const char aMEMORYCARDNotFo_800B682C[56];
extern const char aFormattingFaile_800B6864[40];
extern const char aSaveFailed_800B688C[28];
extern const char aLoadFailed_800B68A8[28];
extern const char aLoadGame_800B68E0[];
extern const char aOverwriteGame_800B68F8[];
extern const char aSaveGame_800B6918[];
extern const LoadWinRect confirmTextWin_800B6930;
extern const char aReturnToTitle_800B6938[];
extern const LoadWinRect titlePromptWin_800B6968;
extern const int dword_800B6970;
extern const LoadWinRect cardSlotWin_800B69F4;
extern const char aFormatMemoryCard_800B69FC[];
extern const LoadWinRect formatPromptWin_800B6A24;
extern const char aSelectMemoryCard_800B6A2C[];
extern const char emptyText_800B6A54[4];
extern const char aNoEmptyBlocks_800B6A58[];
extern const char aDamagedData_800B6AA4[];
extern const char aNoMemoryCardInSlot_800B6ADC[];
extern const char aCheckingMemoryCard_800B6B0C[];
extern const LoadWinRect helpTextWin_800B6B3C;
extern const LoadWinRect modeTitleWin_800B6B8C;
extern const LoadWinRect cardSlotLabelWin_800B6B94;
extern const char aSlash_800B6B9C[];
extern const LoadWinRect listPositionWin_800B6BA0;
extern const char aMiddleDot_800B6BA8[];
extern const char aJadeCocoonLevel_800B6BAC[];
extern const char aCORRIDOR_800B6BF0[];
extern const char aEND_800B6C04[];
extern const int dword_800B6C0C;
extern const int dword_800B6C10;
extern const int dword_800B6C14;
extern const unsigned short aLatestGame_800B6C18[12];
extern const unsigned short aEndOfGame_800B6C30[12];
extern const char aCorridor_800B6C48[20];
extern const char aCombDataTitle15_800B6C5C[28];
extern const char aCombDataTitle14_800B6C78[28];
extern const char aCombDataTitle13_800B6C94[28];
extern const char aCombDataTitle12_800B6CB0[28];
extern const char aCombDataTitle11_800B6CCC[28];
extern const char aCombDataTitle10_800B6CE8[28];
extern const char aCombDataTitle09_800B6D04[28];
extern const char aCombDataTitle08_800B6D20[28];
extern const char aCombDataTitle07_800B6D3C[28];
extern const char aCombDataTitle06_800B6D58[28];
extern const char aCombDataTitle05_800B6D74[28];
extern const char aCombDataTitle04_800B6D90[28];
extern const char aCombDataTitle03_800B6DAC[28];
extern const char aCombDataTitle02_800B6DC8[28];
extern const char aCombDataTitle01_800B6DE4[28];
extern const char aJadeCocoon15_800B6E00[28];
extern const char aJadeCocoon14_800B6E1C[28];
extern const char aJadeCocoon13_800B6E38[28];
extern const char aJadeCocoon12_800B6E54[28];
extern const char aJadeCocoon11_800B6E70[28];
extern const char aJadeCocoon10_800B6E8C[28];
extern const char aJadeCocoon09_800B6EA8[28];
extern const char aJadeCocoon08_800B6EC4[28];
extern const char aJadeCocoon07_800B6EE0[28];
extern const char aJadeCocoon06_800B6EFC[28];
extern const char aJadeCocoon05_800B6F18[28];
extern const char aJadeCocoon04_800B6F34[28];
extern const char aJadeCocoon03_800B6F50[28];
extern const char aJadeCocoon02_800B6F6C[28];
extern const char aJadeCocoon01_800B6F88[28];
extern const char aBASLUS00854COMB_800B6FA4[];
extern const char aBASLUS00854COMB_800B6FBC[];
extern const char aBASLUS00854COMB_800B6FD4[];
extern const char aBASLUS00854COMB_800B6FEC[];
extern const char aBASLUS00854COMB_800B7004[];
extern const char aBASLUS00854COMB_800B701C[];
extern const char aBASLUS00854COMB_800B7034[];
extern const char aBASLUS00854COMB_800B704C[];
extern const char aBASLUS00854COMB_800B7064[];
extern const char aBASLUS00854COMB_800B707C[];
extern const char aBASLUS00854COMB_800B7094[];
extern const char aBASLUS00854COMB_800B70AC[];
extern const char aBASLUS00854COMB_800B70C4[];
extern const char aBASLUS00854COMB_800B70DC[];
extern const char aBASLUS00854COMB_800B70F4[];
extern const char aBASLUS00854GAME_800B710C[];
extern const char aBASLUS00854GAME_800B7124[];
extern const char aBASLUS00854GAME_800B713C[];
extern const char aBASLUS00854GAME_800B7154[];
extern const char aBASLUS00854GAME_800B716C[];
extern const char aBASLUS00854GAME_800B7184[];
extern const char aBASLUS00854GAME_800B719C[];
extern const char aBASLUS00854GAME_800B71B4[];
extern const char aBASLUS00854GAME_800B71CC[];
extern const char aBASLUS00854GAME_800B71E4[];
extern const char aBASLUS00854GAME_800B71FC[];
extern const char aBASLUS00854GAME_800B7214[];
extern const char aBASLUS00854GAME_800B722C[];
extern const char aBASLUS00854GAME_800B7244[];
extern const char aBASLUS00854GAME_800B725C[];
extern const char aNoMemoryCardJp_800B7274[];
extern const char aCardSlotJp_800B7290[];
extern const char aCardSlot1Jp_800B72A8[];
extern const char aCardSlot2Jp_800B72C0[];
extern const char aInsertMemoryCardJp_800B72D8[];
extern const char aDirWildcard_800B72FC[4];
extern const CardTag aCRD0_800B7300;
extern const char aMemoryCard1Jp_800B7308[];
extern const LoadMenuItemPair cardSlotMenuItem1_800B731C;
extern const char aMemoryCard2Jp_800B7354[];
extern const LoadMenuItemPair cardSlotMenuItem2_800B7368;
extern LoadTextPos saveSlotFieldPos_800BD93C[9];
extern LoadUiSprite saveSlotSprites_800BD960[7];
extern LoadUiSprite modeTitleSprites_800BD998[2];
extern int cardSlotSprites_800BD9A8[16];
extern LoadUiSprite saveIconSprites_800BD9E8[4];
extern char *saveListPrompts_800BDA08[2];
extern RECT saveListClip_800BDA10;
extern LoadMenuItem saveListRow0_800BDA18[2];
extern LoadMenuItem saveListRow1_800BDA50[2];
extern LoadMenuItem saveListRow2_800BDA88[2];
extern LoadMenuItem saveListRow3_800BDAC0[2];
extern LoadMenuItem *saveListRows_800BDAF8[5];
extern LoadMenuWin saveListWin_800BDB0C;
extern int cardSlot1Item_800BDB24[14];
extern void *cardSlot1Items_800BDB5C[2];
extern int cardSlot1Win_800BDB64;
extern int cardSlot1WinRest_800BDB68[5];
extern int cardSlot2Item_800BDB7C[14];
extern void *cardSlot2Items_800BDBB4[2];
extern int cardSlot2Win_800BDBBC;
extern int cardSlot2WinRest_800BDBC0[5];
extern int *cardSlotWins_800BDBD4[2];
extern LoadMenuItem topMenuSave_800BDBDC[2];
extern LoadMenuItem topMenuLoad_800BDC14[2];
extern LoadMenuItem topMenuExit_800BDC4C[2];
extern LoadMenuItem topMenuTitle_800BDC84[2];
extern LoadMenuItem *topMenuItems_800BDCBC[5];
extern LoadMenuWin topMenuWin_800BDCD0;
extern LoadMenuItem formatYes_800BDCE8[2];
extern LoadMenuItem formatNo_800BDD20[2];
extern LoadMenuItem *formatItems_800BDD58[3];
extern LoadMenuWin formatWin_800BDD64;
extern LoadMenuItem confirmYes_800BDD7C[2];
extern LoadMenuItem confirmNo_800BDDB4[2];
extern LoadMenuItem *confirmItems_800BDDEC[3];
extern LoadMenuWin confirmWin_800BDDF8;
extern LoadMenuItem titleYes_800BDE10[2];
extern LoadMenuItem titleNo_800BDE48[2];
extern LoadMenuItem *titleItems_800BDE80[3];
extern LoadMenuWin titleWin_800BDE8C;
extern char loadMenuButtonHelp_800BDEA4[24];
extern char *msgCardFull_800BDEBC[4];
extern char *msgFormatting_800BDECC[4];
extern char *msgLoading_800BDEDC[4];
extern char *msgSaving_800BDEEC[4];
extern char *msgNoSaveData_800BDEFC[8];
extern char *msgFormatFailed_800BDF1C[4];
extern char *msgSaveFailed_800BDF2C[4];
extern char *msgLoadFailed_800BDF3C[4];
extern LoadMenuRow loadMenuRows_800BDF4C[2];
extern int loadMenuRow2_800BDF6C[4];
extern int loadMenuRow3_800BDF7C[4];
extern int loadMenuRow4_800BDF8C[4];
extern int loadMenuRow5_800BDF9C[4];
extern SaveTitle *saveTitle_800BDFAC;
extern char *cardTitles_800BDFB0[30];
extern char *saveFileNames_800BE028[2][15];
extern SaveIconSrc saveIconSrc_800BE0A0[3];
extern char cardHeaderTail_800BE0B8[148];
extern int cardFreeBlocks_800BE14C;
extern int cardSaveCount_800BE150;
extern int loadMenuActive_800BE184;
extern char *cardSaveNames_800BE188[15];

#endif
