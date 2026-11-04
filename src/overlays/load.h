// LOAD.BIN: declarations shared by its source files
#ifndef _LOAD_H_
#define _LOAD_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"
#include "pad_text.h"
#include "main.h"
#include "font.h"

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

// a DrawButtonHelpBar_8002B004 entry, icon -1 ends the list
typedef struct
{
    int icon_0;
    const char* text_4;
} LoadHelpEntry;

typedef struct
{
    char icon_0[0x80];        // the save icon bitmap copied into the card header (BuildCardHeader_800BB2AC)
    const char* textsJp_80[5]; // unused Japanese memory card texts
} CardHeaderTail;

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
extern LoadUiSprite cardSlotSprites_800BD9A8[8];
extern LoadUiSprite saveIconSprites_800BD9E8[4];
extern char *saveListPrompts_800BDA08[2];
extern RECT saveListClip_800BDA10;
extern LoadMenuItem saveListRow0_800BDA18[2];
extern LoadMenuItem saveListRow1_800BDA50[2];
extern LoadMenuItem saveListRow2_800BDA88[2];
extern LoadMenuItem saveListRow3_800BDAC0[2];
extern LoadMenuItem *saveListRows_800BDAF8[5];
extern LoadMenuWin saveListWin_800BDB0C;
extern LoadMenuItem cardSlot1Item_800BDB24[2];
extern LoadMenuItem *cardSlot1Items_800BDB5C[2];
extern LoadMenuWin cardSlot1Win_800BDB64;
extern LoadMenuItem cardSlot2Item_800BDB7C[2];
extern LoadMenuItem *cardSlot2Items_800BDBB4[2];
extern LoadMenuWin cardSlot2Win_800BDBBC;
extern LoadMenuWin *cardSlotWins_800BDBD4[2];
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
extern LoadHelpEntry loadMenuButtonHelp_800BDEA4[3];
extern char *msgCardFull_800BDEBC[4];
extern char *msgFormatting_800BDECC[4];
extern char *msgLoading_800BDEDC[4];
extern char *msgSaving_800BDEEC[4];
extern char *msgNoSaveData_800BDEFC[8];
extern char *msgFormatFailed_800BDF1C[4];
extern char *msgSaveFailed_800BDF2C[4];
extern char *msgLoadFailed_800BDF3C[4];
extern LoadMenuRow loadMenuRows_800BDF4C[6];
extern SaveTitle *saveTitle_800BDFAC;
extern char *cardTitles_800BDFB0[30];
extern char *saveFileNames_800BE028[2][15];
extern SaveIconSrc saveIconSrc_800BE0A0[3];
extern CardHeaderTail cardHeaderTail_800BE0B8;
extern int cardFreeBlocks_800BE14C;
extern int cardSaveCount_800BE150;
extern int loadMenuActive_800BE184;
extern char *cardSaveNames_800BE188[15];

// a task (EventEntry of the event lists) as its callbacks see it
typedef struct
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
    void (*cb_C)();
    int size_10;
    void* work_14;
} LoadMenuTaskEntry;
// memory card file header (the PSY-Q _CARD layout; the game's own data in the reserved part and behind the icons)
typedef struct
{
    char magic_0[2];
    char type_2;
    char blocks_3;
    char title_4[64];
    char field_44[12];
    short field_50;
    CardTag tag_52; // "CRD0"
    char field_57;
    char pad_58[4];
    int field_5C;
    char clut_60[32];
    char icon_80[3][128];
    char field_200[0x80];
} CardHeader;
// a memory card directory entry (the PSY-Q struct DIRENTRY layout)
typedef struct CardDirEntry
{
    char name_0[20];
    long attr_14;
    long size_18;
    struct CardDirEntry* next_1C;
    long head_20;
    char system_24[4];
} CardDirEntry;
typedef struct
{
    short color_0; // uiColor_8008B590
    char colorSet_2; // window colour set (1 pulses, GetWindowColors_8004226C)
    char semiTrans_3;
} LoadWinColor;
// the summary block (file offset 0x280) of a save file
typedef struct
{
    unsigned char name_0[0xC];
    char text_C[0x18];
    short icon_24;
    short corridor_26; // SaveData.field_810: the corridor floor (-1 end of game, -2 an ordinary save)
    int vals_28[6];
    int sum_40; // byte sum of the save body (SaveFile.body_300)
    char pad44[0x3C];
} SaveSummary;
// a unit's status as packed in a save file (0x38 bytes): UnitStatus without the name and the equipment
typedef struct
{
    int status_0;
    unsigned int exp_4;
    UnitGauge hp_8;
    UnitGauge mp_C;
    unsigned char modifiers_10[0xC]; // UnitStatus.modifiers_20
    UnitStatBlock stats_1C;
    unsigned char element_2E[4];
    short elementMask_32;
    unsigned char level_34;
    unsigned char field_35;
} SaveStatus;
// a Minion as packed in a save file (0xA0 bytes); the names are kept apart (SaveBody)
typedef struct
{
    short id_0;
    unsigned char species_2;
    unsigned char field_3;
    unsigned char species_4[0x30];
    unsigned char field_34[8];
    SaveStatus status_3C;
    UnitStatBlock field_74;
    UnitSkills skills_86;
    unsigned int magicBits_9C;
} SaveMinion;
// a stored minion (SaveData.items, UnitStats) as packed in a save file (0x6C bytes)
typedef struct
{
    SaveStatus status_0;
    char pad_38[0x14];
    unsigned int species_4C;
    char pad_50[0x1C];
} SaveStats;
// the checksummed part of a save file (file offset 0x300)
typedef struct
{
    unsigned char data_0[0x984]; // the head of saveData_8008B570 (0x988 bytes, up to the minions)
    int version_984;             // SaveData.field_984: 5
    SaveMinion minions_988[15];
    SaveStats items_12E8[12];
    unsigned char ancestorNames_17F8[15][6][10];
    unsigned char minionNames_1B7C[15][12]; // 10 used
    unsigned char itemNames_1C30[12][12];   // 10 used
} SaveBody;
// a save file (0x2180 bytes)
typedef struct
{
    CardHeader header_0;
    SaveSummary summary_280;
    SaveBody body_300;
    char pad_1FC0[0x1C0];
} SaveFile;
typedef struct
{
    SaveSummary* summaries_0; // one per save (15)
    SaveFile* fileBuf_4; // one save file
    int loaded_8;     // 1 once a save was loaded (GetLoadMenuLoaded_800B7914)
    char pad_C[8];
    int field_14;
    char pad_18[8];
    int nRead_20;     // ReadSaveSummaries_800B9724 progress: summaries read (15 = all, 16 = card checked)
    int nextScreen_24; // the screen to switch to (-1: none), UpdateLoadMenuCursor_800B80F8
    int phase_28;     // 0 menu, 2 save, 3 load, 4 format, 5/6 exit (LoadMenuTask_800B794C)
    int field_2C;
    short screen_30;  // the current screen (LoadMenuScreen_800B79F8); <6 also the loadMenuRows_800BDF4C row
    short field_32;
    char pad_34[8];
    int field_3C;
    int field_40;
    char pad_44[0x10];
    unsigned flags_54; // 1 loaded, 4, 8 keep settings / from the title, 0x10 back to the title,
                       // 0x20 end of game save, bit 6 the pad
    char* place_58;   // the save place text of the summary (SetLoadMenuSavePlace_800B78B8)
    int field_5C;
    int field_60;
    LoadMenuRow* rows_64[6];
} LoadMenuWork;
typedef struct
{
    short w_0;
    short h_2;
} TextSize;
typedef struct
{
    short x_0;
    short y_2;
    short w_4;
    short h_6;
} MsgBoxRect;
typedef struct
{
    short field_0;
    short dir_2; // DrawScrollArrow_8002B3DC direction
} ScrollArrowArg;
typedef struct
{
    char c[6];
} Bytes6_LOAD;

extern int MemCardSync(int mode, int* cmd, int* result);
extern void MemCardAccept();
extern void MemCardExist();
extern long MemCardReadFile(long chan, char* file, void* adrs, long ofs, long bytes);
extern void LoadMenuInit_800B7674(int mode, int b);
extern void LoadMenuWaitUiTiy_800B7894(LoadMenuTaskEntry* task);
extern long MemCardCreateFile(long chan, char* file, long blocks);
extern long MemCardWriteFile(long chan, char* file, void* adrs, long ofs, long bytes);
extern int UnpackSaveFile_800BA3EC(LoadMenuWork* work);
extern void DrawMessageBox_800BACBC(char** lines);
extern void LoadMenuTask_800B794C(LoadMenuTaskEntry* task, LoadMenuWork* work);
extern void LoadMenuScreen_800B79F8(LoadMenuWork* work);
extern void PackSaveFile_800B9A8C(LoadMenuWork* work);
extern void WriteSaveTask_800B98C4(void* t, void* buf);
extern void LoadSaveTask_800BA234(LoadMenuTaskEntry* task, LoadMenuWork* work);
extern void FormatCardWait1_800BA968(LoadMenuTaskEntry* task);
extern void LoadMenuExit_800BAAE0(LoadMenuTaskEntry* task, LoadMenuWork* work);
extern void FormatCardWait2_800BA9AC(LoadMenuTaskEntry* task);
extern void FormatCardTask_800BA9F0(LoadMenuTaskEntry* task, LoadMenuWork* work);
extern long MemCardGetDirentry(long chan, char* name, CardDirEntry* dir, long* files, long ofs, long max);
extern int MemCardFormat(long chan);
extern void ScanCardSaves_800BAFB0(int slot);
extern void _card_stop(void);
extern void UserFuncInit(void);
extern void _card_start(void);
extern void sub_800BD06C(void);
extern void _clr_card_event(void);
extern int _get_card_event_x(void);
extern void UserFuncOpen(void* fn, int a);
extern void sub_800BB6F4(void);
extern void sub_800BBA5C(void);
extern void ResetMenuRow_800BADE0(LoadMenuRow* row);
void DrawSaveSlots_800B8BD4(LoadMenuWork* work);
extern void WaitCardSync_800BADF4(void);
extern char* GetCardSaveName_800BAE4C(int i);
extern int GetCardFreeBlocks_800BAE2C(void);
extern int GetCardSaveCount_800BAE3C(void);
extern void sub_800BBF88(void);
extern void sub_800BC17C(void);
extern int PollCardExist_800BAF0C(int slot);
extern int PollCardAccept_800BAE68(int slot);
void UpdateLoadMenuCursor_800B80F8(LoadMenuWork* work);
void DrawCardSlotSelect_800B82FC(LoadMenuWork* work);
void DrawCardSlotChosen_800B847C(LoadMenuWork* work);
void DrawFormatPrompt_800B85AC(LoadMenuWork* work);
void DrawSaveList_800B867C(LoadMenuWork* work);
void DrawLoadMenuHelpText_800B877C(LoadMenuWork* work);
void DrawLoadMenuModeTitle_800B8984(LoadMenuWork* work);
void DrawCardSlotLabel_800B8A20(LoadMenuWork* work);
void DrawSaveListPosition_800B8AE4(LoadMenuWork* work);
void TopMenuInput_800B9220(LoadMenuWork* work);
void CardSlotInput_800B92C0(LoadMenuWork* work);
void CheckCardTask_800B9360(LoadMenuWork* work);
void FormatPromptInput_800B9470(LoadMenuWork* work);
void SaveListInput_800B952C(LoadMenuWork* work);
void ConfirmPromptInput_800B9654(LoadMenuWork* work);
int ReadSaveSummaries_800B9724(LoadMenuWork* work);
extern void BuildCardHeader_800BB2AC(CardHeader* header,int idx, char* title);
extern int PlayTimeHours_800BAC14(int frames);
extern int PlayTimeMinutes_800BAC68(int frames);

/* GAME overlay (resident below this one), to move to game.h */
extern int GetGameMode_800A6D50(int a);
extern void RequestGameMode_800A6D30(int a);

/* exe-side, to move to an exe header */
// main.h has these too, but declares loadMenuTask_8008D480 as int[2]: not included until that is fixed
extern void DrawLoadingIcon_8003CD5C(void);
extern void DrawMenuBackground_8002BE10(void);
extern void LoadUiTiy_8002BF74(void);
extern int dword_8008BD80;
extern char* strcpy_8004E2D8(char* dst, char* src); // PSY-Q strcpy (not in symbol_addrs.txt)
extern void FreeActiveOverlay_8002C014(void);
extern void DrawNumberRightAlignedFont1_8003F264(void* pos, int val, int ot);
extern void DrawMenuWindows_8002A5A4(void* p);
extern unsigned short uiColor_8008B590;
extern char* dword_8008D454;
extern void DrawUiTiySprt_8002C06C(void* pos, int sprite, int ot);
extern void DrawWindow_80042460(void* rect, void* color, void* ot, int d);
extern TextSize MeasureTextLines_8003E3B4(int* list);
extern void DrawScrollArrows_8002B8DC(ScrollArrowArg arrow, short* cursor, short* pos, int ot);
extern void DrawButtonHelpBar_8002B004(void* p, int a, int b);
extern void AddDrawAreaPrim_8003326C(RECT* r, char* ot);
extern void AddClipDrawAreaPrim_80033308(char* ot);
extern void DrawSmallNumber3_8002C290(void* p, int n, int ot);
extern void DrawSmallNumber9_8002C414(void* p, int n, int ot);
extern void DrawSmallText_8002FAA0(int align, void* pos, unsigned char* name, int ot);
extern void* memcpy(void* dst, const void* src, unsigned int n);
extern void IntToText_8003F610(unsigned short* buf, int val);

#endif
