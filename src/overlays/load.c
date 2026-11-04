// LOAD.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "load.h"
#include "tiy.h"

extern int dword_800BE174;
extern int (*dword_800BE294[])();
// a task (EventEntry of the event lists) as its callbacks see it
typedef struct
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
    void (*cb_C)();
    int size_10;
    void* work_14;
} Task_LOAD;
extern EventNode* loadMenuTask_8008D480; // the load menu's task list
extern int MemCardSync(int a, int* b, int* c);
extern void MemCardAccept();
extern void MemCardExist();
extern long MemCardReadFile(long chan, char* file, void* adrs, long ofs, long bytes);
extern void LoadMenuInit_800B7674(int mode, int b);
extern void LoadMenuWaitUiTiy_800B7894();
extern int uiTiyLoaded_8008B4E8;
extern long MemCardCreateFile(long chan, char* file, long blocks);
extern long MemCardWriteFile(long chan, char* file, void* adrs, long ofs, long bytes);
extern int UnpackSaveFile_800BA3EC();
extern void DrawLoadingIcon_8003CD5C(void);
extern void DrawMenuBackground_8002BE10(void);
extern void DrawMessageBox_800BACBC(char** lines);
extern void LoadMenuTask_800B794C();
extern void LoadMenuScreen_800B79F8();
extern void PackSaveFile_800B9A8C();
extern void WriteSaveTask_800B98C4();
extern void LoadSaveTask_800BA234();
extern void FormatCardWait1_800BA968();
extern void LoadMenuExit_800BAAE0();
extern void FormatCardWait2_800BA9AC();
extern void FormatCardTask_800BA9F0();
extern void LoadUiTiy_8002BF74(void);
extern int dword_8008BD80;
extern int UpdateMenuCursor_8003D794(short* cursor, int b);

// memory card file header (the PSY-Q _CARD layout; the game's own data in the reserved part and behind the icons)
typedef struct
{
    char magic_0[2];
    char type_2;
    char blocks_3;
    char title_4[64];
    char field_44[12];
    short field_50;
    Bytes5_LOAD tag_52; // "CRD0"
    char field_57;
    char pad_58[4];
    int field_5C;
    char clut_60[32];
    char icon_80[3][128];
    char field_200[0x80];
} CardHeader_LOAD;
extern char* strcpy_8004E2D8(char* dst, char* src); // PSY-Q strcpy (not in symbol_addrs.txt)
// a memory card directory entry (the PSY-Q struct DIRENTRY layout)
typedef struct DirEntry_LOAD
{
    char name_0[20];
    long attr_14;
    long size_18;
    struct DirEntry_LOAD* next_1C;
    long head_20;
    char system_24[4];
} DirEntry_LOAD;
extern long MemCardGetDirentry(long chan, char* name, DirEntry_LOAD* dir, long* files, long ofs, long max);
extern void FreeActiveOverlay_8002C014(void);
extern int GetGameMode_800A6D50(int a);
extern void RequestGameMode_800A6D30(int a);
extern int dword_80091C54;
extern int MemCardFormat(long chan);
extern void ScanCardSaves_800BAFB0(int a);
extern void _card_stop(void);
extern void UserFuncInit(void);
extern void _card_start(void);
extern void sub_800BD06C(void);
extern void DrawText_8003E91C(int a0, char* a1, void* a2, short a3);
extern char byte_800B682C[];
extern void DrawNumberRightAlignedFont1_8003F264(void* p, int a, int b);
extern void DrawMenuWindows_8002A5A4(void* p);
extern unsigned char cardSlotCursor_800BDF68;
extern void _clr_card_event(void);
extern int _get_card_event_x(void);
typedef struct
{
    short color_0; // uiColor_8008B590
    char field_2;
    char field_3;
} WinColor_LOAD;
extern unsigned short uiColor_8008B590;
extern char* dword_8008D454;
extern void DrawUiTiySprt_8002C06C(void* a, int b, int c);
extern void DrawWindow_80042460(void* a, void* b, void* c, int d);
// the summary block (file offset 0x280) of a save file
typedef struct
{
    unsigned char name_0[0xC];
    char text_C[0x18];
    short icon_24;
    short f26;
    int vals_28[6];
    int sum_40; // byte sum of the save body (SaveFile_LOAD.body_300)
    char pad44[0x3C];
} SaveSummary_LOAD;
// a unit's status as packed in a save file (0x38 bytes): UnitStatus without the name and the equipment
typedef struct
{
    int status_0;
    unsigned int exp_4;
    UnitGauge hp_8;
    UnitGauge mp_C;
    unsigned char field_10[0xC]; // UnitStatus.field_20
    UnitStatBlock stats_1C;
    unsigned char element_2E[4];
    short elementMask_32;
    unsigned char level_34;
    unsigned char field_35;
} SaveStatus_LOAD;
// a Minion as packed in a save file (0xA0 bytes); the names are kept apart (SaveBody_LOAD)
typedef struct
{
    short id_0;
    unsigned char species_2;
    unsigned char field_3;
    unsigned char species_4[0x30];
    unsigned char field_34[8];
    SaveStatus_LOAD status_3C;
    UnitStatBlock field_74;
    UnitSkills skills_86;
    unsigned int magicBits_9C;
} SaveMinion_LOAD;
// a stored minion (SaveData.items, UnitStats) as packed in a save file (0x6C bytes)
typedef struct
{
    SaveStatus_LOAD status_0;
    char pad_38[0x14];
    unsigned int species_4C;
    char pad_50[0x1C];
} SaveStats_LOAD;
// the checksummed part of a save file (file offset 0x300)
typedef struct
{
    unsigned char data_0[0x984]; // the head of saveData_8008B570 (0x988 bytes, up to the minions)
    int version_984;             // SaveData.field_984: 5
    SaveMinion_LOAD minions_988[15];
    SaveStats_LOAD items_12E8[12];
    unsigned char ancestorNames_17F8[15][6][10];
    unsigned char minionNames_1B7C[15][12]; // 10 used
    unsigned char itemNames_1C30[12][12];   // 10 used
} SaveBody_LOAD;
// a save file (0x2180 bytes)
typedef struct
{
    CardHeader_LOAD header_0;
    SaveSummary_LOAD summary_280;
    SaveBody_LOAD body_300;
    char pad_1FC0[0x1C0];
} SaveFile_LOAD;
typedef struct
{
    SaveSummary_LOAD* summaries_0; // one per save (15)
    SaveFile_LOAD* fileBuf_4; // one save file
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
    void* rows_64[6];
} LoadMenuWork;
typedef struct
{
    short w_0;
    short h_2;
} Size_LOAD;
typedef struct
{
    short x_0;
    short y_2;
    short w_4;
    short h_6;
} Rect_LOAD;
extern Size_LOAD MeasureTextLines_8003E3B4(int* list);
extern int IsConfirmPressed_8003D288(int a, int b);
extern int IsCancelPressed_8003D3C0(int a, int b);
extern void UserFuncOpen(void* fn, int a);
extern void sub_800BB6F4(void);
extern void sub_800BBA5C(void);
typedef struct
{
    short field_0;
    short field_2;
} Pair_LOAD;
extern void ResetMenuRow_800BADE0(MenuRow_LOAD* p);
extern void DrawScrollArrows_8002B8DC(Pair_LOAD q, short* a, short* b, int c);
void DrawSaveSlots_800B8BD4(LoadMenuWork* t);
extern void PlaySfx_80031494(int a);
extern void WaitCardSync_800BADF4(void);
extern char* GetCardSaveName_800BAE4C(int n);
extern int GetCardFreeBlocks_800BAE2C(void);
extern int GetCardSaveCount_800BAE3C(void);
typedef struct
{
    char c[6];
} Bytes6_LOAD;
extern void sub_800BBF88(void);
extern void sub_800BC17C(void);

int dword_800B66C0 SDATA = 24;
const char aSelectGameToLoa_800B66C4[44] = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202\207\202\201\202\215\202\205\201@\202\224\202\217\201@\202\214\202\217\202\201\202\204\201D";
const char aSelectSaveLocat_800B66F0[44] = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202\223\202\201\202\226\202\205\201@\202\214\202\217\202\203\202\201\202\224\202\211\202\217\202\216\201D";
const char aYES_800B671C[] = "\202x\202d\202r"; // YES
const char aNO_800B6724[] = "\202m\201@\202n"; // N O
const char aExit_800B672C[] = "\202d\202\230\202\211\202\224"; // Exit
const char aSelect_800B6738[] = "\202r\202\205\202\214\202\205\202\203\202\224"; // Select
const char aMEMORYCARDFull_800B6748[36] = "\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201@\202\206\202\225\202\214\202\214\201D";
const char aDoNotRemoveMEMO_800B676C[56] = "\202c\202\217\201@\202\216\202\217\202\224\201@\202\222\202\205\202\215\202\217\202\226\202\205\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201D";
const char aFormattingMEMOR_800B67A4[52] = "\202e\202\217\202\222\202\215\202\201\202\224\202\224\202\211\202\216\202\207\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201D\201D\201D";
const char aLoading_800B67D8[24] = "\202k\202\217\202\201\202\204\202\211\202\216\202\207\201D\201D\201D";
const char aSaving_800B67F0[20] = "\202r\202\201\202\226\202\211\202\216\202\207\201D\201D\201D";
const char aNoSaveGameData_800B6804[40] = "\202m\202\217\201@\202\223\202\201\202\226\202\205\201@\202\207\202\201\202\215\202\205\201@\202\204\202\201\202\224\202\201\201D";
const char aMEMORYCARDNotFo_800B682C[56] = "\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201@\202\216\202\217\202\224\201@\202\206\202\217\202\222\202\215\202\201\202\224\202\224\202\205\202\204\201D";
const char aFormattingFaile_800B6864[40] = "\202e\202\217\202\222\202\215\202\201\202\224\202\224\202\211\202\216\202\207\201@\202\206\202\201\202\211\202\214\202\205\202\204\201D";
const char aSaveFailed_800B688C[28] = "\202r\202\201\202\226\202\205\201@\202\206\202\201\202\211\202\214\202\205\202\204\201D";
const char aLoadFailed_800B68A8[28] = "\202k\202\217\202\201\202\204\201@\202\206\202\201\202\211\202\214\202\205\202\204\201D";

void LoadMenuStart_800B7650(void)
{
    LoadMenuInit_800B7674(4, 0);
}

#if 0
// Not matched: mode and t swap $s3/$s4, and the case 0/1 stores are scheduled differently
void LoadMenuInit_800B7674(int mode, int b)
{
    int i;
    Task_LOAD* t;
    LoadMenuWork* s;
    MemCardStart();
    t = (Task_LOAD*)&loadMenuTask_8008D480->entry;
    s = (LoadMenuWork*)t->work_14;
    t->flags_0 = (t->flags_0 | 1) & ~0x8000;
    for (i = 0; i < 6; i++)
    {
        ResetMenuRow_800BADE0(&loadMenuRows_800BDF4C[i]);
    }
    s->loaded_8 = 0;
    s->nextScreen_24 = -1;
    s->phase_28 = 0;
    switch (mode)
    {
    case 0:
        s->screen_30 = 1;
        loadMenuRows_800BDF4C[0].cursor_C = 0;
        s->flags_54 = 4;
        break;
    case 1:
        s->screen_30 = 1;
        loadMenuRows_800BDF4C[0].cursor_C = 1;
        s->flags_54 = 4;
        break;
    case 2:
        s->screen_30 = 1;
        loadMenuRows_800BDF4C[0].cursor_C = 1;
        s->flags_54 = 0xC;
        t->next_8 = LoadMenuTask_800B794C;
        goto done;
    case 3:
        s->screen_30 = 1;
        loadMenuRows_800BDF4C[0].cursor_C = 1;
        s->flags_54 = 0x4C;
        t->next_8 = LoadMenuTask_800B794C;
        goto done;
    default:
        s->screen_30 = 0;
        loadMenuRows_800BDF4C[0].cursor_C = 0;
        s->flags_54 = 0;
        break;
    }
    LoadUiTiy_8002BF74();
    t->next_8 = LoadMenuWaitUiTiy_800B7894;
done:
    if (dword_8008BD80 == -1 && !(s->flags_54 & 8))
    {
        s->screen_30 = 1;
        loadMenuRows_800BDF4C[0].cursor_C = 0;
        s->flags_54 = 0x20;
    }
    s->field_5C = 0;
    s->nRead_20 = 0;
    s->field_14 = 0;
    s->field_32 = 0;
    s->field_2C = 0;
    s->field_3C = 0;
    s->field_40 = 0;
    s->rows_64[0] = &loadMenuRows_800BDF4C[0];
    s->rows_64[1] = &loadMenuRows_800BDF4C[1];
    s->rows_64[2] = &loadMenuRows_800BDF4C[2];
    s->rows_64[3] = &loadMenuRows_800BDF4C[3];
    s->rows_64[4] = &loadMenuRows_800BDF4C[4];
    s->rows_64[5] = &loadMenuRows_800BDF4C[5];
    s->summaries_0 = malloc3_8003FC4C(0x780);
    s->fileBuf_4 = malloc3_8003FC4C(sizeof(SaveFile_LOAD));
    loadMenuActive_800BE184 = 1;
}
#endif
INCLUDE_OVERLAY_ASM(load, LoadMenuInit_800B7674);

void LoadMenuWaitUiTiy_800B7894(Task_LOAD* t)
{
    if (uiTiyLoaded_8008B4E8)
    {
        t->next_8 = LoadMenuTask_800B794C;
    }
}

void SetLoadMenuSavePlace_800B78B8(char* place)
{
    ((LoadMenuWork*)loadMenuTask_8008D480->entry.buffer)->place_58 = place;
}

void LoadMenuSetEndOfGame_800B78D0(void)
{
    LoadMenuWork* t;
    saveData_8008B570.field_810 = -1;
    saveData_8008B570.field_0 |= 0x180;
    t = loadMenuTask_8008D480->entry.buffer;
    t->screen_30 = 1;
    loadMenuRows_800BDF4C[0].cursor_C = 0;
    t->flags_54 = 0x20;
}

int GetLoadMenuLoaded_800B7914(void)
{
    return ((LoadMenuWork*)loadMenuTask_8008D480->entry.buffer)->loaded_8;
}

void LoadMenuNop_800B7934(void)
{
}

int IsLoadMenuActive_800B793C(void)
{
    return loadMenuActive_800BE184;
}

void LoadMenuTask_800B794C(Task_LOAD* t, LoadMenuWork* s)
{
    switch (s->phase_28)
    {
    case 0:
        LoadMenuScreen_800B79F8(s);
        break;
    case 2:
        PackSaveFile_800B9A8C(s);
        t->next_8 = WriteSaveTask_800B98C4;
        s->field_2C = 0;
        break;
    case 3:
        t->next_8 = LoadSaveTask_800BA234;
        break;
    case 4:
        t->next_8 = FormatCardWait1_800BA968;
        break;
    case 5:
    case 6:
        t->next_8 = LoadMenuExit_800BAAE0;
        break;
    }
}
const char aLoadGame_800B68E0[] = "\202k\202\217\202\201\202\204\201@\202\207\202\201\202\215\202\205\201H"; // Load game?
const char aOverwriteGame_800B68F8[] = "\202n\202\226\202\205\202\222\202\227\202\222\202\211\202\224\202\205\201@\202\207\202\201\202\215\202\205\201H"; // Overwrite game?
const char aSaveGame_800B6918[] = "\202r\202\201\202\226\202\205\201@\202\207\202\201\202\215\202\205\201H"; // Save game?
const WinRect_LOAD confirmTextWin_800B6930 = { { 10, 0, 193, 0, 204, 0, 20 } };
const char aReturnToTitle_800B6938[] = "\202q\202\205\202\224\202\225\202\222\202\216\201@\202\224\202\217\201@\202\224\202\211\202\224\202\214\202\205\201@\202\223\202\203\202\222\202\205\202\205\202\216\201H"; // Return to title screen?
const WinRect_LOAD titlePromptWin_800B6968 = { { 92, 0, 100, 0, 140, 0, 19 } };
const int dword_800B6970 = 0;

extern unsigned short padPressed_8009194C[];
extern void DrawButtonHelpBar_8002B004(void* p, int a, int b);
extern int PollCardExist_800BAF0C(int a);
extern int PollCardAccept_800BAE68(int a);
void UpdateLoadMenuCursor_800B80F8(LoadMenuWork* t);
void DrawCardSlotSelect_800B82FC(LoadMenuWork* t);
void DrawCardSlotChosen_800B847C(LoadMenuWork* t);
void DrawFormatPrompt_800B85AC(LoadMenuWork* t);
void DrawSaveList_800B867C(LoadMenuWork* t);
void DrawLoadMenuHelpText_800B877C(LoadMenuWork* t);
void DrawLoadMenuModeTitle_800B8984(LoadMenuWork* t);
void DrawCardSlotLabel_800B8A20(LoadMenuWork* t);
void DrawSaveListPosition_800B8AE4(LoadMenuWork* t);
void TopMenuInput_800B9220(LoadMenuWork* t);
void CardSlotInput_800B92C0(LoadMenuWork* t);
void CheckCardTask_800B9360(LoadMenuWork* t);
void FormatPromptInput_800B9470(LoadMenuWork* t);
void SaveListInput_800B952C(LoadMenuWork* t);
void ConfirmPromptInput_800B9654(LoadMenuWork* t);
int ReadSaveSummaries_800B9724(LoadMenuWork* t);
// draws the current screen (LoadMenuWork.screen_30) and handles its input:
//  0 top menu (Save / Load / Exit / Title), 1 card slot select, 2 format the card?, 3 the save list,
//  4 load / save / overwrite?, 5 return to the title?, 6 no card in the slot, 7 card full, 8 no save data,
//  9 no empty blocks, 10 damaged data, 11 card not formatted, 13..15 format / save / load failed,
//  18 checking the card
// Matched
void LoadMenuScreen_800B79F8(LoadMenuWork* t)
{
    union // the text position and the window colour share one slot (case 4)
    {
        Pos_LOAD pos;
        WinColor_LOAD tail;
    } u;
    int r;
    UpdateLoadMenuCursor_800B80F8(t);
    switch (t->screen_30)
    {
    case 9:
    case 10:
        saveListWin_800BDB0C.time_4 = 0;
        saveListWin_800BDB0C.field_0 = 1;
        DrawMenuWindows_8002A5A4(&saveListWin_800BDB0C);
        DrawSaveList_800B867C(t);
        DrawLoadMenuModeTitle_800B8984(t);
        DrawCardSlotLabel_800B8A20(t);
        DrawSaveListPosition_800B8AE4(t);
        DrawLoadMenuHelpText_800B877C(t);
        if (padPressed_8009194C[(t->flags_54 >> 6) & 1])
        {
            t->nextScreen_24 = 3;
        }
        if (!ReadSaveSummaries_800B9724(t))
        {
            t->nextScreen_24 = 1;
        }
        break;
    case 7:
        DrawMessageBox_800BACBC(msgCardFull_800BDEBC);
        if (!ReadSaveSummaries_800B9724(t) || padPressed_8009194C[(t->flags_54 >> 6) & 1])
        {
            t->nextScreen_24 = 1;
        }
        break;
    case 11:
        switch (PollCardExist_800BAF0C(cardSlotCursor_800BDF68))
        {
        case -1:
        case 0:
        case 2:
        case 3:
            break;
        case 1:
            t->nextScreen_24 = 1;
            break;
        }
        DrawCardSlotChosen_800B847C(t);
        DrawLoadMenuHelpText_800B877C(t);
        if (padPressed_8009194C[(t->flags_54 >> 6) & 1])
        {
            t->nextScreen_24 = 1;
        }
        break;
    case 8:
        DrawMessageBox_800BACBC(msgNoSaveData_800BDEFC);
        switch (PollCardAccept_800BAE68(cardSlotCursor_800BDF68))
        {
        case -1:
        case 0:
        case 4:
            break;
        default:
            t->nextScreen_24 = 1;
            break;
        }
        if (padPressed_8009194C[(t->flags_54 >> 6) & 1])
        {
            t->nextScreen_24 = 1;
        }
        break;
    case 0:
        topMenuWin_800BDCD0.time_4 = GetTime30Hz_8002C64C();
        topMenuWin_800BDCD0.cursor_C = loadMenuRows_800BDF4C[t->screen_30].cursor_C;
        DrawMenuWindows_8002A5A4(&topMenuWin_800BDCD0);
        DrawLoadMenuHelpText_800B877C(t);
        TopMenuInput_800B9220(t);
        break;
    case 1:
        DrawCardSlotSelect_800B82FC(t);
        DrawLoadMenuHelpText_800B877C(t);
        CardSlotInput_800B92C0(t);
        break;
    case 6:
        switch (PollCardExist_800BAF0C(cardSlotCursor_800BDF68))
        {
        case 0:
        case 3:
        case 4:
            WaitCardSync_800BADF4();
            t->nextScreen_24 = 0x12;
            break;
        }
        DrawCardSlotChosen_800B847C(t);
        DrawLoadMenuHelpText_800B877C(t);
        if (padPressed_8009194C[(t->flags_54 >> 6) & 1])
        {
            t->nextScreen_24 = 1;
        }
        break;
    case 18:
        DrawCardSlotChosen_800B847C(t);
        DrawLoadMenuHelpText_800B877C(t);
        CheckCardTask_800B9360(t);
        break;
    case 2:
        formatWin_800BDD64.time_4 = GetTime30Hz_8002C64C();
        formatWin_800BDD64.cursor_C = loadMenuRows_800BDF4C[t->screen_30].cursor_C;
        DrawFormatPrompt_800B85AC(t);
        FormatPromptInput_800B9470(t);
        break;
    case 3:
        saveListWin_800BDB0C.time_4 = GetTime30Hz_8002C64C();
        saveListWin_800BDB0C.cursor_C = loadMenuRows_800BDF4C[t->screen_30].cursor_C;
        saveListWin_800BDB0C.field_0 = 2;
        if (!ReadSaveSummaries_800B9724(t))
        {
            t->nextScreen_24 = 1;
        }
        DrawMenuWindows_8002A5A4(&saveListWin_800BDB0C);
        DrawSaveList_800B867C(t);
        DrawLoadMenuModeTitle_800B8984(t);
        DrawCardSlotLabel_800B8A20(t);
        DrawSaveListPosition_800B8AE4(t);
        DrawLoadMenuHelpText_800B877C(t);
        SaveListInput_800B952C(t);
        break;
    case 4:
        saveListWin_800BDB0C.time_4 = 0;
        saveListWin_800BDB0C.cursor_C = loadMenuRows_800BDF4C[3].cursor_C;
        saveListWin_800BDB0C.field_0 = 4;
        confirmWin_800BDDF8.time_4 = GetTime30Hz_8002C64C();
        confirmWin_800BDDF8.cursor_C = loadMenuRows_800BDF4C[t->screen_30].cursor_C;
        if (!ReadSaveSummaries_800B9724(t))
        {
            t->nextScreen_24 = 1;
        }
        DrawMenuWindows_8002A5A4(&saveListWin_800BDB0C);
        DrawSaveList_800B867C(t);
        DrawLoadMenuModeTitle_800B8984(t);
        DrawCardSlotLabel_800B8A20(t);
        DrawSaveListPosition_800B8AE4(t);
        DrawMenuWindows_8002A5A4(&confirmWin_800BDDF8);
        if (loadMenuRows_800BDF4C[0].cursor_C == 1)
        {
            u.pos.x_0 = 0xD;
            u.pos.y_2 = 0xC4;
            DrawText_8003E91C(2, aLoadGame_800B68E0, &u.pos, 5);
        }
        else if (loadMenuRows_800BDF4C[0].cursor_C == 0)
        {
            if (GetCardSaveName_800BAE4C(loadMenuRows_800BDF4C[3].scroll_D + loadMenuRows_800BDF4C[3].cursor_C))
            {
                u.pos.x_0 = 0xD;
                u.pos.y_2 = 0xC4;
                DrawText_8003E91C(2, aOverwriteGame_800B68F8, &u.pos, 5);
            }
            else
            {
                u.pos.x_0 = 0xD;
                u.pos.y_2 = 0xC4;
                DrawText_8003E91C(2, aSaveGame_800B6918, &u.pos, 5);
            }
        }
        {
            WinRect_LOAD a;
            a = confirmTextWin_800B6930;
            u.tail.field_3 = 1;
            u.tail.field_2 = 0;
            u.tail.color_0 = uiColor_8008B590;
            DrawWindow_80042460(&a, &u.tail, dword_8008D454 + 0x38, 0);
        }
        ConfirmPromptInput_800B9654(t);
        break;
    case 5:
        titleWin_800BDE8C.time_4 = GetTime30Hz_8002C64C();
        titleWin_800BDE8C.cursor_C = loadMenuRows_800BDF4C[t->screen_30].cursor_C;
        u.pos.x_0 = 0x66;
        u.pos.y_2 = 0x69;
        DrawText_8003E91C(2, aReturnToTitle_800B6938, &u.pos, 5);
        {
        WinRect_LOAD a;
        WinColor_LOAD b;
        a = titlePromptWin_800B6968;
        b.field_3 = 1;
        b.field_2 = 0;
        b.color_0 = uiColor_8008B590;
        DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
        }
        DrawMenuWindows_8002A5A4(&titleWin_800BDE8C);
        if (IsConfirmPressed_8003D288(0, (t->flags_54 >> 6) & 1))
        {
            if (loadMenuRows_800BDF4C[t->screen_30].cursor_C == 0)
            {
                t->flags_54 = 0x10;
                t->phase_28 = 5;
                PlaySfx_80031494(0x7E);
                break;
            }
            t->nextScreen_24 = 0;
            PlaySfx_80031494(0x7D);
        }
        else if (IsCancelPressed_8003D3C0(0, (t->flags_54 >> 6) & 1))
        {
            t->nextScreen_24 = 0;
            PlaySfx_80031494(0x7D);
        }
        break;
    case 13:
        DrawMessageBox_800BACBC(msgFormatFailed_800BDF1C);
        if (padPressed_8009194C[(t->flags_54 >> 6) & 1])
        {
            t->nextScreen_24 = 1;
        }
        break;
    case 14:
        DrawMessageBox_800BACBC(msgSaveFailed_800BDF2C);
        if (padPressed_8009194C[(t->flags_54 >> 6) & 1])
        {
            t->nextScreen_24 = 1;
        }
        break;
    case 15:
        DrawMessageBox_800BACBC(msgLoadFailed_800BDF3C);
        if (padPressed_8009194C[(t->flags_54 >> 6) & 1])
        {
            t->nextScreen_24 = 1;
        }
        break;
    }
    DrawButtonHelpBar_8002B004(loadMenuButtonHelp_800BDEA4, 0, 1);
    DrawMenuBackground_8002BE10();
}

void UpdateLoadMenuCursor_800B80F8(LoadMenuWork* t)
{
    short c[6];
    int r;
    if (t->nextScreen_24 != -1)
    {
        switch (t->nextScreen_24)
        {
        case 0:
            break;
        case 1:
            ResetMenuRow_800BADE0(&loadMenuRows_800BDF4C[3]);
            break;
        case 2:
            ResetMenuRow_800BADE0(&loadMenuRows_800BDF4C[2]);
            break;
        case 3:
            break;
        case 4:
            ResetMenuRow_800BADE0(&loadMenuRows_800BDF4C[4]);
            if (loadMenuRows_800BDF4C[0].cursor_C == 0)
            {
                loadMenuRows_800BDF4C[4].cursor_C = 1;
            }
            break;
        case 5:
            ResetMenuRow_800BADE0(&loadMenuRows_800BDF4C[5]);
            break;
        }
        t->screen_30 = t->nextScreen_24;
        t->nextScreen_24 = -1;
    }
    if (t->screen_30 >= 6)
    {
        return;
    }
    if (t->screen_30 >= 0)
    {
        c[4] = loadMenuRows_800BDF4C[t->screen_30].cursor_C;
        c[5] = loadMenuRows_800BDF4C[t->screen_30].scroll_D;
        c[0] = loadMenuRows_800BDF4C[t->screen_30].field_6;
        c[1] = loadMenuRows_800BDF4C[t->screen_30].field_7;
        c[2] = loadMenuRows_800BDF4C[t->screen_30].field_8;
        c[3] = loadMenuRows_800BDF4C[t->screen_30].field_B;
        r = UpdateMenuCursor_8003D794(c, (t->flags_54 >> 6) & 1);
        if (loadMenuRows_800BDF4C[t->screen_30].cursor_C != c[4] || r == 8 || r == 7)
        {
            PlaySfx_80031494(0x7F);
        }
        loadMenuRows_800BDF4C[t->screen_30].cursor_C = c[4];
        loadMenuRows_800BDF4C[t->screen_30].scroll_D = c[5];
    }
}
const WinRect_LOAD cardSlotWin_800B69F4 = { { 93, 0, 18, 0, 124, 0, 18 } };
const char aFormatMemoryCard_800B69FC[] = "\202e\202\217\202\222\202\215\202\201\202\224\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201H"; // Format MEMORY CARD?
const WinRect_LOAD formatPromptWin_800B6A24 = { { 16, 0, 70, 0, 32, 1, 34 } };
const char aSelectMemoryCard_800B6A2C[] = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201D"; // Select MEMORY CARD.
const char emptyText_800B6A54[4] = { 0 };
const char aNoEmptyBlocks_800B6A58[] = "\202m\202\217\201@\202\205\202\215\202\220\202\224\202\231\201@\202\202\202\214\202\217\202\203\202\213\202\223\201@\202\206\202\217\202\222\201@\202\223\202\201\202\226\202\211\202\216\202\207\201@\202\216\202\205\202\227\201@\202\207\202\201\202\215\202\205\202\223\201D"; // No empty blocks for saving new games.
const char aDamagedData_800B6AA4[] = "\202e\202\201\202\211\202\214\202\205\202\204\201@\202\204\202\225\202\205\201@\202\224\202\217\201@\202\204\202\201\202\215\202\201\202\207\202\205\202\204\201@\202\204\202\201\202\224\202\201\201D"; // Failed due to damaged data.
const char aNoMemoryCardInSlot_800B6ADC[] = "\202m\202\217\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201@\202\211\202\216\201@\202\223\202\214\202\217\202\224\201D"; // No MEMORY CARD in slot.
const char aCheckingMemoryCard_800B6B0C[] = "\202b\202\210\202\205\202\203\202\213\202\211\202\216\202\207\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201D\201D\201D"; // Checking MEMORY CARD...
const WinRect_LOAD helpTextWin_800B6B3C = { { 10, 0, 193, 0, 44, 1, 20 } };

void DrawCardSlotSelect_800B82FC(LoadMenuWork* t)
{
    int i;
    UiSprite_LOAD* p;
    WinRect_LOAD a;
    WinColor_LOAD b;
    if (t->screen_30 == 1)
    {
        for (i = 0; i < 2; i++)
        {
            cardSlotWins_800BDBD4[i][0] = 2;
            if (i == loadMenuRows_800BDF4C[1].cursor_C)
            {
                cardSlotWins_800BDBD4[i][1] = GetTime30Hz_8002C64C();
            }
            else
            {
                cardSlotWins_800BDBD4[i][1] = 0;
            }
        }
    }
    else
    {
        cardSlotWins_800BDBD4[0][0] = 1;
        cardSlotWins_800BDBD4[1][0] = 1;
    }
    DrawMenuWindows_8002A5A4(&cardSlot1Win_800BDB64);
    DrawMenuWindows_8002A5A4(&cardSlot2Win_800BDBBC);
    for (p = &modeTitleSprites_800BD998[2]; p->sprite_4 >= 0; p++)
    {
        DrawUiTiySprt_8002C06C(p, p->sprite_4, p->ot_6);
    }
    a = cardSlotWin_800B69F4;
    b.field_3 = 1;
    b.field_2 = 0;
    b.color_0 = uiColor_8008B590;
    DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
}

void DrawCardSlotChosen_800B847C(LoadMenuWork* t)
{
    int i;
    UiSprite_LOAD* p;
    WinRect_LOAD a;
    WinColor_LOAD b;
    for (i = 0; i < 2; i++)
    {
        if (i == loadMenuRows_800BDF4C[1].cursor_C)
        {
            *cardSlotWins_800BDBD4[i] = 4;
        }
        else
        {
            *cardSlotWins_800BDBD4[i] = 1;
        }
    }
    DrawMenuWindows_8002A5A4(&cardSlot1Win_800BDB64);
    DrawMenuWindows_8002A5A4(&cardSlot2Win_800BDBBC);
    for (p = &modeTitleSprites_800BD998[2]; p->sprite_4 >= 0; p++)
    {
        DrawUiTiySprt_8002C06C(p, p->sprite_4, p->ot_6);
    }
    a = cardSlotWin_800B69F4;
    b.field_3 = 1;
    b.field_2 = 0;
    b.color_0 = uiColor_8008B590;
    DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
}

void DrawFormatPrompt_800B85AC(LoadMenuWork* t)
{
    Pos_LOAD p0;
    Pos_LOAD p1;
    WinRect_LOAD a;
    WinColor_LOAD b;
    p0.x_0 = 0x13;
    p0.y_2 = 0x49;
    DrawText_8003E91C(2, byte_800B682C, &p0, 5);
    p1.x_0 = 0x13;
    p1.y_2 = 0x57;
    DrawText_8003E91C(2, aFormatMemoryCard_800B69FC, &p1, 5);
    a = formatPromptWin_800B6A24;
    b.field_3 = 1;
    b.field_2 = 0;
    b.color_0 = uiColor_8008B590;
    DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
    DrawMenuWindows_8002A5A4(&formatWin_800BDD64);
}

void DrawSaveList_800B867C(LoadMenuWork* t)
{
    Pair_LOAD q;
    short r0[4];
    short r1[6];
    DrawSaveSlots_800B8BD4(t);
    r1[0] = loadMenuRows_800BDF4C[t->screen_30].field_6;
    r1[1] = loadMenuRows_800BDF4C[t->screen_30].field_7;
    r1[2] = loadMenuRows_800BDF4C[t->screen_30].field_8;
    r1[3] = loadMenuRows_800BDF4C[t->screen_30].field_B;
    r1[4] = loadMenuRows_800BDF4C[t->screen_30].cursor_C;
    r1[5] = loadMenuRows_800BDF4C[t->screen_30].scroll_D;
    q.field_0 = 2;
    q.field_2 = 1;
    r0[0] = 0x9A;
    r0[1] = 0x2C;
    r0[2] = 0x9A;
    r0[3] = 0xB7;
    DrawScrollArrows_8002B8DC(q, r1, r0, 1);
}

void DrawLoadMenuHelpText_800B877C(LoadMenuWork* t)
{
    switch (t->screen_30)
    {
    case 1:
    {
        Pos_LOAD p;
        p.x_0 = 0xE;
        p.y_2 = 0xC7;
        DrawText_8003E91C(2, aSelectMemoryCard_800B6A2C, &p, 5);
        break;
    }
    case 2:
    {
        Pos_LOAD p;
        p.x_0 = 0xE;
        p.y_2 = 0xC7;
        DrawText_8003E91C(2, emptyText_800B6A54, &p, 5);
        break;
    }
    case 3:
    {
        Pos_LOAD p;
        p.x_0 = 0xE;
        p.y_2 = 0xC7;
        DrawText_8003E91C(2, saveListPrompts_800BDA08[loadMenuRows_800BDF4C[0].cursor_C], &p, 5);
        break;
    }
    case 9:
    {
        Pos_LOAD p;
        p.x_0 = 0xE;
        p.y_2 = 0xC7;
        DrawText_8003E91C(2, aNoEmptyBlocks_800B6A58, &p, 5);
        break;
    }
    case 10:
    {
        Pos_LOAD p;
        p.x_0 = 0xE;
        p.y_2 = 0xC7;
        DrawText_8003E91C(2, aDamagedData_800B6AA4, &p, 5);
        break;
    }
    case 6:
    {
        Pos_LOAD p;
        p.x_0 = 0xE;
        p.y_2 = 0xC7;
        DrawText_8003E91C(2, aNoMemoryCardInSlot_800B6ADC, &p, 5);
        break;
    }
    case 18:
    {
        Pos_LOAD p;
        p.x_0 = 0xE;
        p.y_2 = 0xC7;
        DrawText_8003E91C(2, aCheckingMemoryCard_800B6B0C, &p, 5);
        break;
    }
    case 11:
    {
        Pos_LOAD p;
        p.x_0 = 0xE;
        p.y_2 = 0xC7;
        DrawText_8003E91C(2, byte_800B682C, &p, 5);
        break;
    }
    }
    {
        WinRect_LOAD a;
        WinColor_LOAD b;
        a = helpTextWin_800B6B3C;
        b.field_3 = 1;
        b.field_2 = 0;
        b.color_0 = uiColor_8008B590;
        DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
    }
}
const WinRect_LOAD modeTitleWin_800B6B8C = { { 63, 0, 18, 0, 108, 0, 18 } };
const WinRect_LOAD cardSlotLabelWin_800B6B94 = { { 187, 0, 18, 0, 122, 0, 18 } };
const char aSlash_800B6B9C[] = "\201^"; // /
const WinRect_LOAD listPositionWin_800B6BA0 = { { 10, 0, 33, 0, 44, 0, 14 } };
const char aMiddleDot_800B6BA8[] = "\201E"; // ・
const char aJadeCocoonLevel_800B6BAC[] = "\202i\202\201\202\204\202\205\201@\202b\202\217\202\203\202\217\202\217\202\216\201^\202k\202\205\202\226\202\205\202\214\201@\202X\202X\201^\202k\202\201\202\224\202\205\202\223\202\224\201@\202f\202\201\202\215\202\205"; // Jade Cocoon/Level 99/Latest Game
const char aCORRIDOR_800B6BF0[] = "\202b\202n\202q\202q\202h\202c\202n\202q"; // CORRIDOR
const char aEND_800B6C04[] = "\202d\202m\202c"; // END
const int dword_800B6C0C = 0;
const int dword_800B6C10 = 0;
const int dword_800B6C14 = 0;
const unsigned short aLatestGame_800B6C18[12] = {
    0x6B82, 0x8182, 0x9482, 0x8582, 0x9382, 0x9482, 0x4081, 0x6682,
    0x8182, 0x8D82, 0x8582,
};
const unsigned short aEndOfGame_800B6C30[12] = {
    0x6482, 0x8E82, 0x8482, 0x4081, 0x8F82, 0x8682, 0x4081, 0x6682,
    0x8182, 0x8D82, 0x8582,
};
const char aCorridor_800B6C48[20] = "\202b\202\217\202\222\202\222\202\211\202\204\202\217\202\222\000\000\015";
const char aCombDataTitle15_800B6C5C[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202P\202T";
const char aCombDataTitle14_800B6C78[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202P\202S";
const char aCombDataTitle13_800B6C94[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202P\202R";
const char aCombDataTitle12_800B6CB0[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202P\202Q";
const char aCombDataTitle11_800B6CCC[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202P\202P";
const char aCombDataTitle10_800B6CE8[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202P\202O";
const char aCombDataTitle09_800B6D04[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202X";
const char aCombDataTitle08_800B6D20[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202W";
const char aCombDataTitle07_800B6D3C[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202V";
const char aCombDataTitle06_800B6D58[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202U";
const char aCombDataTitle05_800B6D74[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202T";
const char aCombDataTitle04_800B6D90[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202S";
const char aCombDataTitle03_800B6DAC[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202R";
const char aCombDataTitle02_800B6DC8[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202Q";
const char aCombDataTitle01_800B6DE4[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202P";
const char aJadeCocoon15_800B6E00[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202P\202T";
const char aJadeCocoon14_800B6E1C[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202P\202S";
const char aJadeCocoon13_800B6E38[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202P\202R";
const char aJadeCocoon12_800B6E54[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202P\202Q";
const char aJadeCocoon11_800B6E70[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202P\202P";
const char aJadeCocoon10_800B6E8C[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202P\202O";
const char aJadeCocoon09_800B6EA8[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202O\202X";
const char aJadeCocoon08_800B6EC4[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202O\202W";
const char aJadeCocoon07_800B6EE0[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202O\202V";
const char aJadeCocoon06_800B6EFC[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202O\202U";
const char aJadeCocoon05_800B6F18[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202O\202T";
const char aJadeCocoon04_800B6F34[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202O\202S";
const char aJadeCocoon03_800B6F50[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202O\202R";
const char aJadeCocoon02_800B6F6C[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202O\202Q";
const char aJadeCocoon01_800B6F88[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202O\202P";
const char aBASLUS00854COMB_800B6FA4[] = "BASLUS-00854COMB0414";
const char aBASLUS00854COMB_800B6FBC[] = "BASLUS-00854COMB0413";
const char aBASLUS00854COMB_800B6FD4[] = "BASLUS-00854COMB0412";
const char aBASLUS00854COMB_800B6FEC[] = "BASLUS-00854COMB0411";
const char aBASLUS00854COMB_800B7004[] = "BASLUS-00854COMB0410";
const char aBASLUS00854COMB_800B701C[] = "BASLUS-00854COMB0409";
const char aBASLUS00854COMB_800B7034[] = "BASLUS-00854COMB0408";
const char aBASLUS00854COMB_800B704C[] = "BASLUS-00854COMB0407";
const char aBASLUS00854COMB_800B7064[] = "BASLUS-00854COMB0406";
const char aBASLUS00854COMB_800B707C[] = "BASLUS-00854COMB0405";
const char aBASLUS00854COMB_800B7094[] = "BASLUS-00854COMB0404";
const char aBASLUS00854COMB_800B70AC[] = "BASLUS-00854COMB0403";
const char aBASLUS00854COMB_800B70C4[] = "BASLUS-00854COMB0402";
const char aBASLUS00854COMB_800B70DC[] = "BASLUS-00854COMB0401";
const char aBASLUS00854COMB_800B70F4[] = "BASLUS-00854COMB0400";
const char aBASLUS00854GAME_800B710C[] = "BASLUS-00854GAME0414";
const char aBASLUS00854GAME_800B7124[] = "BASLUS-00854GAME0413";
const char aBASLUS00854GAME_800B713C[] = "BASLUS-00854GAME0412";
const char aBASLUS00854GAME_800B7154[] = "BASLUS-00854GAME0411";
const char aBASLUS00854GAME_800B716C[] = "BASLUS-00854GAME0410";
const char aBASLUS00854GAME_800B7184[] = "BASLUS-00854GAME0409";
const char aBASLUS00854GAME_800B719C[] = "BASLUS-00854GAME0408";
const char aBASLUS00854GAME_800B71B4[] = "BASLUS-00854GAME0407";
const char aBASLUS00854GAME_800B71CC[] = "BASLUS-00854GAME0406";
const char aBASLUS00854GAME_800B71E4[] = "BASLUS-00854GAME0405";
const char aBASLUS00854GAME_800B71FC[] = "BASLUS-00854GAME0404";
const char aBASLUS00854GAME_800B7214[] = "BASLUS-00854GAME0403";
const char aBASLUS00854GAME_800B722C[] = "BASLUS-00854GAME0402";
const char aBASLUS00854GAME_800B7244[] = "BASLUS-00854GAME0401";
const char aBASLUS00854GAME_800B725C[] = "BASLUS-00854GAME0400";
const char aNoMemoryCardJp_800B7274[] = "\203\201\203\202\203\212\201[\203J\201[\203h\202\252\202\240\202\350\202\334\202\271\202\361"; // メモリーカードがありません
const char aCardSlotJp_800B7290[] = "\203\201\203\202\203\212\201[\203J\201[\203h\215\267\215\236\214\373"; // メモリーカード差込口
const char aCardSlot1Jp_800B72A8[] = "\203\201\203\202\203\212\201[\203J\201[\203h\215\267\215\236\214\373\202P"; // メモリーカード差込口１
const char aCardSlot2Jp_800B72C0[] = "\203\201\203\202\203\212\201[\203J\201[\203h\215\267\215\236\214\373\202Q"; // メモリーカード差込口２
const char aInsertMemoryCardJp_800B72D8[] = "\203\201\203\202\203\212\201[\203J\201[\203h\202\360\203Z\203b\203g\202\265\202\304\202\255\202\276\202\263\202\242"; // メモリーカードをセットしてください
const char aDirWildcard_800B72FC[4] = { 42 };
const Bytes5_LOAD aCRD0_800B7300 = { "CRD0" };
const char aMemoryCard1Jp_800B7308[] = "\203\201\203\202\203\212\201[\203J\201[\203h\202P"; // メモリーカード１
const MenuItems2_LOAD cardSlotMenuItem1_800B731C = {
    {
        { 8, 3, (int)aMemoryCard1Jp_800B7308, 0, 0, 40, 100, { 100, 0, 34, 0, 2, 0, 2 } },
        { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
    },
};
const char aMemoryCard2Jp_800B7354[] = "\203\201\203\202\203\212\201[\203J\201[\203h\202Q"; // メモリーカード２
const MenuItems2_LOAD cardSlotMenuItem2_800B7368 = {
    {
        { 8, 3, (int)aMemoryCard2Jp_800B7354, 0, 0, 180, 100, { 100, 0, 34, 0, 2, 0, 2 } },
        { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
    },
};

void DrawLoadMenuModeTitle_800B8984(LoadMenuWork* t)
{
    WinRect_LOAD a;
    WinColor_LOAD b;
    DrawUiTiySprt_8002C06C(&modeTitleSprites_800BD998[loadMenuRows_800BDF4C[0].cursor_C], modeTitleSprites_800BD998[loadMenuRows_800BDF4C[0].cursor_C].sprite_4, modeTitleSprites_800BD998[loadMenuRows_800BDF4C[0].cursor_C].ot_6);
    a = modeTitleWin_800B6B8C;
    b.field_3 = 1;
    b.field_2 = 0;
    b.color_0 = uiColor_8008B590;
    DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
}

#if 0
// Not matched: only the order of the prologue stores differs ($ra/$s0 vs argument set-up)
void DrawCardSlotLabel_800B8A20(LoadMenuWork* t)
{
    Pos_LOAD p0;
    Pos_LOAD p1;
    WinRect_LOAD a;
    WinColor_LOAD b;
    p0.x_0 = 0xBF;
    p0.y_2 = 0x15;
    DrawUiTiySprt_8002C06C(&p0, 0x27, 1);
    p1.x_0 = 0x124;
    p1.y_2 = 0x15;
    DrawUiTiySprt_8002C06C(&p1, (cardSlotCursor_800BDF68 == 1) << 1, 1);
    a = cardSlotLabelWin_800B6B94;
    b.field_3 = 1;
    b.field_2 = 0;
    b.color_0 = uiColor_8008B590;
    DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
}
#endif
INCLUDE_OVERLAY_ASM(load, DrawCardSlotLabel_800B8A20);

void DrawSaveListPosition_800B8AE4(LoadMenuWork* t)
{
    Pos_LOAD p0;
    Pos_LOAD p1;
    Pos_LOAD p2;
    WinRect_LOAD a;
    WinColor_LOAD b;
    p0.x_0 = 0x1C;
    p0.y_2 = 0x24;
    DrawNumberRightAlignedFont1_8003F264(&p0, loadMenuRows_800BDF4C[3].scroll_D + loadMenuRows_800BDF4C[3].cursor_C + 1, 5);
    p1.x_0 = 0x1C;
    p1.y_2 = 0x24;
    DrawText_8003E91C(1, aSlash_800B6B9C, &p1, 5);
    p2.x_0 = 0x32;
    p2.y_2 = 0x24;
    DrawNumberRightAlignedFont1_8003F264(&p2, 0xF, 5);
    a = listPositionWin_800B6BA0;
    b.field_3 = 1;
    b.field_2 = 0;
    b.color_0 = uiColor_8008B590;
    DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
}

extern void AddDrawAreaPrim_8003326C(RECT* r, char* ot);
extern void AddClipDrawAreaPrim_80033308(char* ot);
extern void DrawSmallNumber3_8002C290(void* p, int n, int ot);
extern void DrawSmallNumber9_8002C414(void* p, int n, int ot);
extern void DrawSmallText_8002FAA0(int a0, void* pos, unsigned char* name, int a3);
// Matched
void DrawSaveSlots_800B8BD4(LoadMenuWork* t)
{
    Pos_LOAD p0;
    Pos_LOAD p1;
    Pos_LOAD p2;
    Pos_LOAD p3;
    Pos_LOAD p4;
    Pos_LOAD p5;
    int i;
    int j;
    int n;
    int k;
    int v;
    UiSprite_LOAD* r;
    UiSprite_LOAD* icon;
    for (i = -1; i < 5; i++)
    {
        n = loadMenuRows_800BDF4C[3].scroll_D + i;
        if (!((n >= 0 && n < 15) || i == 0 || i == 1))
        {
            continue;
        }
        if (n >= t->nRead_20 - 1)
        {
            p0.x_0 = 0x7D;
            p0.y_2 = i * 33 + 0x39;
            AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
            DrawUiTiySprt_8002C06C(&p0, 0x9C, 1);
            AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + 4);
        }
        else if (!GetCardSaveName_800BAE4C(n))
        {
            p1.x_0 = 0x8B;
            p1.y_2 = i * 33 + 0x39;
            AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
            DrawUiTiySprt_8002C06C(&p1, 0x74, 1);
            AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + 4);
        }
        else
        {
            for (j = 0; j < 9; j++)
            {
                if (j < 6)
                {
                    if (j == 5)
                    {
                        v = t->summaries_0[n].vals_28[5];
                        k = 0;
                        do
                        {
                            v /= 10;
                            k++;
                        } while (v);
                        p2.x_0 = saveSlotFieldPos_800BD93C[j].x_0 + k * 7;
                        p2.y_2 = saveSlotFieldPos_800BD93C[j].y_2 + i * 33;
                        AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
                        DrawSmallNumber9_8002C414(&p2, t->summaries_0[n].vals_28[j], 1);
                    }
                    else
                    {
                        p2.x_0 = saveSlotFieldPos_800BD93C[j].x_0;
                        p2.y_2 = saveSlotFieldPos_800BD93C[j].y_2 + i * 33;
                        AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
                        DrawSmallNumber3_8002C290(&p2, t->summaries_0[n].vals_28[j], 1);
                    }
                    if ((j == 3 || j == 4) && t->summaries_0[n].vals_28[j] < 10)
                    {
                        p2.x_0 = saveSlotFieldPos_800BD93C[j].x_0 - 8;
                        p2.y_2 = saveSlotFieldPos_800BD93C[j].y_2 + i * 33;
                        DrawSmallNumber3_8002C290(&p2, 0, 1);
                    }
                    AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + 4);
                }
                else if (j == 6)
                {
                    AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
                    p3.x_0 = saveSlotFieldPos_800BD93C[6].x_0;
                    p3.y_2 = saveSlotFieldPos_800BD93C[6].y_2 + i * 33;
                    DrawSmallText_8002FAA0(0, &p3, t->summaries_0[n].name_0, 1);
                    AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + 4);
                }
                else if (j == 7)
                {
                    p3.x_0 = saveSlotFieldPos_800BD93C[j].x_0;
                    p3.y_2 = saveSlotFieldPos_800BD93C[j].y_2 + i * 33;
                    AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
                    DrawText_8003E91C(1, t->summaries_0[n].text_C, &p3, 1);
                    AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + 4);
                    if (t->summaries_0[n].f26 >= 0)
                    {
                        p3.x_0 = saveSlotFieldPos_800BD93C[j].x_0 + 0x38;
                        p3.y_2 = saveSlotFieldPos_800BD93C[j].y_2 + i * 33;
                        AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
                        DrawNumberRightAlignedFont1_8003F264(&p3, t->summaries_0[n].f26, 1);
                        AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + 4);
                    }
                }
                else if (j == 8)
                {
                    icon = &saveIconSprites_800BD9E8[t->summaries_0[n].icon_24];
                    p3.x_0 = icon->x_0;
                    p3.y_2 = icon->y_2 + i * 33;
                    AddClipDrawAreaPrim_80033308(dword_8008D454 + icon->ot_6 * 4);
                    DrawUiTiySprt_8002C06C(&p3, icon->sprite_4, icon->ot_6);
                    AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + icon->ot_6 * 4);
                }
                for (r = saveSlotSprites_800BD960; r->sprite_4 > 0; r++)
                {
                    p3.x_0 = r->x_0;
                    p3.y_2 = r->y_2 + i * 33;
                    AddClipDrawAreaPrim_80033308(dword_8008D454 + r->ot_6 * 4);
                    DrawUiTiySprt_8002C06C(&p3, r->sprite_4, r->ot_6);
                    AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + r->ot_6 * 4);
                }
            }
            p2.x_0 = saveSlotFieldPos_800BD93C[1].x_0;
            p2.y_2 = saveSlotFieldPos_800BD93C[1].y_2 + i * 33;
            AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
            DrawUiTiySprt_8002C06C(&p2, 0xDA, 1);
            AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + 4);
            p4.x_0 = saveSlotFieldPos_800BD93C[3].x_0 + 2;
            p4.y_2 = (saveSlotFieldPos_800BD93C[3].y_2 - 4) + i * 33;
            AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
            DrawText_8003E91C(2, aMiddleDot_800B6BA8, &p4, 1);
            AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + 4);
            p5.x_0 = saveSlotFieldPos_800BD93C[3].x_0 + 2;
            p5.y_2 = saveSlotFieldPos_800BD93C[3].y_2 + i * 33;
            AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
            DrawText_8003E91C(2, aMiddleDot_800B6BA8, &p5, 1);
            AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + 4);
        }
    }
}

void TopMenuInput_800B9220(LoadMenuWork* t)
{
    if (IsConfirmPressed_8003D288(1, (t->flags_54 >> 6) & 1))
    {
        switch (loadMenuRows_800BDF4C[0].cursor_C)
        {
        case 0:
        case 1:
            t->nextScreen_24 = 1;
            break;
        case 2:
            t->phase_28 = 5;
            break;
        case 3:
            t->nextScreen_24 = 5;
            break;
        }
    }
    else if (IsCancelPressed_8003D3C0(1, (t->flags_54 >> 6) & 1))
    {
        t->phase_28 = 5;
    }
}

#if 0
// Not matched: only a dead byte load (lbu $v1) of the options struct in the prologue is missing
void CardSlotInput_800B92C0(LoadMenuWork* t)
{
    if (IsConfirmPressed_8003D288(0, (t->flags_54 >> 6) & 1))
    {
        PlaySfx_80031494(0x7E);
        WaitCardSync_800BADF4();
        t->nextScreen_24 = 0x12;
    }
    else if (IsCancelPressed_8003D3C0(1, (t->flags_54 >> 6) & 1))
    {
        if (t->flags_54 & 0x24)
        {
            t->phase_28 = 5;
        }
        else
        {
            t->nextScreen_24 = 0;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(load, CardSlotInput_800B92C0);

void CheckCardTask_800B9360(LoadMenuWork* t)
{
    switch (PollCardAccept_800BAE68(loadMenuRows_800BDF4C[1].cursor_C))
    {
    case 0:
    case 3:
        ScanCardSaves_800BAFB0(loadMenuRows_800BDF4C[1].cursor_C);
        PlaySfx_80031494(0x7E);
        if (loadMenuRows_800BDF4C[0].cursor_C == 0)
        {
            if (GetCardFreeBlocks_800BAE2C() || GetCardSaveCount_800BAE3C())
            {
                t->nRead_20 = 0;
                t->nextScreen_24 = 3;
            }
            else
            {
                t->nextScreen_24 = 7;
            }
        }
        else if (GetCardSaveCount_800BAE3C())
        {
            t->nRead_20 = 0;
            t->nextScreen_24 = 3;
        }
        else
        {
            t->nextScreen_24 = 8;
        }
        break;
    case 4:
        if (loadMenuRows_800BDF4C[0].cursor_C == 0)
        {
            t->nextScreen_24 = 2;
        }
        else
        {
            t->nextScreen_24 = 0xB;
        }
        break;
    case -1:
        break;
    default:
        t->nextScreen_24 = 6;
        break;
    }
}

void FormatPromptInput_800B9470(LoadMenuWork* t)
{
    int r = PollCardAccept_800BAE68(loadMenuRows_800BDF4C[1].cursor_C);
    if (r < -1 || (r > 0 && r != 4))
    {
        t->nextScreen_24 = 1;
    }
    if (IsCancelPressed_8003D3C0(1, (t->flags_54 >> 6) & 1))
    {
        t->nextScreen_24 = 1;
    }
    if (IsConfirmPressed_8003D288(1, (t->flags_54 >> 6) & 1))
    {
        if (loadMenuRows_800BDF4C[2].cursor_C == 0)
        {
            t->phase_28 = 4;
        }
        if (loadMenuRows_800BDF4C[2].cursor_C == 1)
        {
            t->nextScreen_24 = 1;
        }
    }
}

void SaveListInput_800B952C(LoadMenuWork* t)
{
    int n = loadMenuRows_800BDF4C[3].scroll_D + loadMenuRows_800BDF4C[3].cursor_C;
    if (IsCancelPressed_8003D3C0(1, (t->flags_54 >> 6) & 1))
    {
        t->nextScreen_24 = 1;
    }
    if (IsConfirmPressed_8003D288(0, (t->flags_54 >> 6) & 1))
    {
        if (loadMenuRows_800BDF4C[0].cursor_C == 1)
        {
            if (n < t->nRead_20 - 1)
            {
                if (GetCardSaveName_800BAE4C(n))
                {
                    t->nextScreen_24 = 4;
                    PlaySfx_80031494(0x7E);
                }
                else
                {
                    PlaySfx_80031494(0x7C);
                }
            }
            else
            {
                PlaySfx_80031494(0x7C);
            }
        }
        else if (loadMenuRows_800BDF4C[0].cursor_C == 0)
        {
            if (n < t->nRead_20 - 1)
            {
                if (!GetCardSaveName_800BAE4C(n) && GetCardFreeBlocks_800BAE2C() <= 0)
                {
                    t->nextScreen_24 = 9;
                    PlaySfx_80031494(0x7C);
                }
                else
                {
                    t->nextScreen_24 = 4;
                    PlaySfx_80031494(0x7E);
                }
            }
            else
            {
                PlaySfx_80031494(0x7C);
            }
        }
    }
}

void ConfirmPromptInput_800B9654(LoadMenuWork* t)
{
    if (IsCancelPressed_8003D3C0(1, (t->flags_54 >> 6) & 1))
    {
        t->nextScreen_24 = 3;
    }
    if (IsConfirmPressed_8003D288(0, (t->flags_54 >> 6) & 1))
    {
        if (loadMenuRows_800BDF4C[4].cursor_C == 0)
        {
            PlaySfx_80031494(0x7E);
            if (loadMenuRows_800BDF4C[0].cursor_C == 1)
            {
                WaitCardSync_800BADF4();
                t->phase_28 = 3;
            }
            else if (loadMenuRows_800BDF4C[0].cursor_C == 0)
            {
                WaitCardSync_800BADF4();
                t->phase_28 = 2;
            }
        }
        else
        {
            PlaySfx_80031494(0x7D);
            t->nextScreen_24 = 3;
        }
    }
}

int ReadSaveSummaries_800B9724(LoadMenuWork* t)
{
    int ret = 1;
    int cmd = 0;
    int res = 0;
    int chan = loadMenuRows_800BDF4C[1].cursor_C << 4;
    char* name;
    switch (MemCardSync(1, &cmd, &res))
    {
    case 0:
        break;
    case -1:
        if (t->nRead_20 < 15)
        {
            name = GetCardSaveName_800BAE4C(t->nRead_20);
            if (name)
            {
                MemCardReadFile(chan, name, &t->summaries_0[t->nRead_20], 0x280, 0x80);
            }
            else if (t->nRead_20 == 14)
            {
                t->nRead_20 = 15;
            }
            t->nRead_20++;
        }
        else
        {
            MemCardExist(chan);
        }
        break;
    case 1:
        switch (cmd)
        {
        case 3:
            switch (res)
            {
            case 0:
                if (t->nRead_20 == 15)
                {
                    t->nRead_20 = 16;
                }
                break;
            case 1:
            case 2:
            case 3:
            case 5:
                ret = 0;
                break;
            }
            break;
        case 1:
            if (res != 0)
            {
                ret = 0;
            }
            break;
        }
        break;
    }
    return ret;
}

#if 0
// Not matched: same prologue scheduling as LoadSaveTask_800BA234 ($a0 = 1 before the $s1 save / second-argument copy)
void WriteSaveTask_800B98C4(Task_LOAD* t, LoadMenuWork* s)
{
    int cmd = 0;
    int res = 0;
    int chan = loadMenuRows_800BDF4C[1].cursor_C << 4;
    int n = loadMenuRows_800BDF4C[3].scroll_D + loadMenuRows_800BDF4C[3].cursor_C;
    char* name;
    switch (MemCardSync(1, &cmd, &res))
    {
    case 0:
        break;
    case -1:
        name = GetCardSaveName_800BAE4C(n);
        if (!name)
        {
            MemCardCreateFile(chan, saveFileNames_800BE028[0][n], 1);
            name = saveFileNames_800BE028[0][n];
        }
        MemCardWriteFile(chan, name, s->fileBuf_4, 0, sizeof(SaveFile_LOAD));
        break;
    case 1:
        if (cmd == 4)
        {
            switch (res)
            {
            case 0:
                t->next_8 = LoadMenuTask_800B794C;
                s->phase_28 = 0;
                s->nextScreen_24 = 3;
                PlaySfx_80031494(0x7E);
                MemCopy_800403E8(&s->summaries_0[n], &s->fileBuf_4->summary_280, 0x80);
                ScanCardSaves_800BAFB0(loadMenuRows_800BDF4C[1].cursor_C);
                break;
            case 1:
            case 2:
            case 3:
            case 5:
                t->next_8 = LoadMenuTask_800B794C;
                s->phase_28 = 0;
                s->nextScreen_24 = 0xE;
                break;
            }
        }
        break;
    }
    DrawLoadingIcon_8003CD5C();
    DrawMessageBox_800BACBC(msgSaving_800BDEEC);
    DrawMenuBackground_8002BE10();
}
#endif
INCLUDE_OVERLAY_ASM(load, WriteSaveTask_800B98C4);

// the title of the save file being written (Shift-JIS "<name>/Level 99/<place>", saveTitle_800BDFAC)
extern unsigned short name_800B6C48[]; // "Corridor"
extern void* memcpy(void* dst, const void* src, unsigned int n);
extern void BuildCardHeader_800BB2AC(CardHeader_LOAD* h, int idx, char* title);
extern void IntToText_8003F610(unsigned short* buf, int val);
extern int PlayTimeHours_800BAC14(int n);
extern int PlayTimeMinutes_800BAC68(int n);

// packs saveData_8008B570 into the save file to write, with its summary and title
// Matched
void PackSaveFile_800B9A8C(LoadMenuWork* s)
{
    unsigned short buf[12];
    SaveSummary_LOAD* sm;
    SaveSummary_LOAD* sm2;
    SaveBody_LOAD* body;
    SaveTitle_LOAD* t;
    unsigned int n;
    int i;
    int j;
    int k;
    int l;
    int idx;
    int lv;
    Minion* m;
    SaveMinion_LOAD* pm;
    UnitStats* u;
    SaveStats_LOAD* pu;

    sm = &s->fileBuf_4->summary_280;
    sm->vals_28[0] = saveData_8008B570.levantStatus_7C8.level_44;
    sm->vals_28[1] = saveData_8008B570.levantStatus_7C8.hp_8.cur_0;
    sm->vals_28[2] = saveData_8008B570.levantStatus_7C8.hp_8.max_2;
    sm->vals_28[3] = PlayTimeHours_800BAC14(saveData_8008B570.playTime_4);
    sm->vals_28[4] = PlayTimeMinutes_800BAC68(saveData_8008B570.playTime_4);
    sm->vals_28[5] = saveData_8008B570.inv_24.yan_0;
    MemCopy_800403E8(sm->name_0, saveData_8008B570.levantStatus_7C8.name_10, 0xC);
    sm->f26 = saveData_8008B570.field_810;
    if (saveData_8008B570.field_810 == -2)
    {
        sm->icon_24 = 0;
    }
    else if (saveData_8008B570.field_810 == -1)
    {
        sm->icon_24 = 1;
    }
    else
    {
        sm->icon_24 = 2;
    }
    if (sm->icon_24 == 2)
    {
        MemCopy_800403E8(sm->text_C, aCORRIDOR_800B6BF0, 0x18);
    }
    else if (sm->icon_24 == 1)
    {
        MemCopy_800403E8(sm->text_C, aEND_800B6C04, 0x18);
    }
    else
    {
        MemCopy_800403E8(sm->text_C, s->place_58, 0x18);
    }
    body = &s->fileBuf_4->body_300;
    MemCopy_800403E8(body, &saveData_8008B570, 0x988);
    for (i = 0; i < 15; i++)
    {
        m = &saveData_8008B570.minions[i];
        pm = &body->minions_988[i];
        pm->id_0 = m->id;
        pm->species_2 = m->species_2;
        pm->field_3 = m->field_3;
        for (j = 0; j < 0x30; j++)
        {
            pm->species_4[j] = m->species_4C[j];
        }
        for (j = 0; j < 8; j++)
        {
            pm->field_34[j] = m->field_7C[j];
        }
        pm->field_74 = m->field_CC;
        pm->skills_86 = m->skills_DE;
        pm->magicBits_9C = m->magicBits_F4;
        pm->status_3C.status_0 = m->status_84.status_0;
        pm->status_3C.exp_4 = m->status_84.exp_4;
        pm->status_3C.hp_8 = m->status_84.hp_8;
        pm->status_3C.mp_C = m->status_84.mp_C;
        for (j = 0; j < 0xC; j++)
        {
            pm->status_3C.field_10[j] = m->status_84.field_20[j];
        }
        pm->status_3C.stats_1C = m->status_84.stats_2C;
        for (j = 0; j < 4; j++)
        {
            pm->status_3C.element_2E[j] = m->status_84.element_3E[j];
        }
        pm->status_3C.elementMask_32 = m->status_84.elementMask_42;
        pm->status_3C.level_34 = m->status_84.level_44;
        pm->status_3C.field_35 = m->status_84.field_45;
        for (j = 0; j < 6; j++)
        {
            for (k = 0; k < 10; k++)
            {
                body->ancestorNames_17F8[i][j][k] = m->ancestors_4[j][k];
            }
        }
        for (k = 0; k < 10; k++)
        {
            body->minionNames_1B7C[i][k] = m->status_84.name_10[k];
        }
    }
    for (l = 0; l < 12; l++)
    {
        u = &saveData_8008B570.items[l];
        pu = &body->items_12E8[l];
        pu->species_4C = u->species_5C;
        pu->status_0.status_0 = u->st_0.status_0;
        pu->status_0.exp_4 = u->st_0.exp_4;
        pu->status_0.hp_8 = u->st_0.hp_8;
        pu->status_0.mp_C = u->st_0.mp_C;
        for (j = 0; j < 0xC; j++)
        {
            pu->status_0.field_10[j] = u->st_0.field_20[j];
        }
        pu->status_0.stats_1C = u->st_0.stats_2C;
        for (j = 0; j < 4; j++)
        {
            pu->status_0.element_2E[j] = u->st_0.element_3E[j];
        }
        pu->status_0.elementMask_32 = u->st_0.elementMask_42;
        pu->status_0.level_34 = u->st_0.level_44;
        pu->status_0.field_35 = u->st_0.field_45;
        for (k = 0; k < 10; k++)
        {
            body->itemNames_1C30[l][k] = u->st_0.name_10[k];
        }
    }
    sm->sum_40 = 0;
    for (n = 0x300; n < 0x1FC0; n++)
    {
        sm->sum_40 += ((unsigned char*)s->fileBuf_4)[n];
    }
    sm2 = &s->fileBuf_4->summary_280;
    idx = loadMenuRows_800BDF4C[3].scroll_D + loadMenuRows_800BDF4C[3].cursor_C;
    IntToText_8003F610(buf, sm2->vals_28[0]);
    lv = sm2->vals_28[0];
    t = saveTitle_800BDFAC;
    if (lv > 100)
    {
        lv = 99;
    }
    t->f.level_24[0] = 0x82;
    t->f.level_24[1] = lv / 10 + 0x4F;
    lv %= 10;
    t->f.level_24[2] = 0x82;
    t->f.level_24[3] = lv % 10 + 0x4F;
    switch (sm2->icon_24)
    {
    case 0:
        memcpy(saveTitle_800BDFAC->f.place_2A, aLatestGame_800B6C18, 23);
        break;
    case 1:
        memcpy(saveTitle_800BDFAC->f.place_2A, aEndOfGame_800B6C30, 23);
        break;
    case 2:
    default:
        memcpy(saveTitle_800BDFAC->f.place_2A, name_800B6C48, 17);
        break;
    }
    BuildCardHeader_800BB2AC(&s->fileBuf_4->header_0, idx, saveTitle_800BDFAC->str);
}

#if 0
// Not matched: prologue scheduling only: the original sets $a0 = 1 before saving $s1 / copying the second argument
void LoadSaveTask_800BA234(Task_LOAD* t, LoadMenuWork* s)
{
    int cmd = 0;
    int res = 0;
    int chan = loadMenuRows_800BDF4C[1].cursor_C << 4;
    int n = loadMenuRows_800BDF4C[3].scroll_D + loadMenuRows_800BDF4C[3].cursor_C;
    char* name;
    switch (MemCardSync(1, &cmd, &res))
    {
    case 0:
        break;
    case -1:
        name = GetCardSaveName_800BAE4C(n);
        if (name)
        {
            MemCardReadFile(chan, name, s->fileBuf_4, 0, sizeof(SaveFile_LOAD));
        }
        else
        {
            t->next_8 = LoadMenuTask_800B794C;
            s->phase_28 = 0;
            s->nextScreen_24 = 0xF;
        }
        break;
    case 1:
        if (cmd == 3)
        {
            switch (res)
            {
            case 0:
                if (UnpackSaveFile_800BA3EC(s))
                {
                    s->loaded_8 = 1;
                    t->next_8 = LoadMenuTask_800B794C;
                    s->phase_28 = 6;
                    s->flags_54 |= 1;
                }
                else
                {
                    t->next_8 = LoadMenuTask_800B794C;
                    s->phase_28 = 0;
                    s->nextScreen_24 = 0xA;
                }
                PlaySfx_80031494(0x7E);
                break;
            case 1:
            case 2:
            case 3:
            case 5:
                t->next_8 = LoadMenuTask_800B794C;
                s->phase_28 = 0;
                s->nextScreen_24 = 0xF;
                break;
            }
        }
        break;
    }
    DrawLoadingIcon_8003CD5C();
    DrawMessageBox_800BACBC(msgLoading_800BDEDC);
    DrawMenuBackground_8002BE10();
}
#endif
INCLUDE_OVERLAY_ASM(load, LoadSaveTask_800BA234);

// unpacks the loaded save file into saveData_8008B570; 0 when the checksum or the version is wrong
// Matched
int UnpackSaveFile_800BA3EC(LoadMenuWork* s)
{
    int ret = 0;
    int sum = ret;
    unsigned int n;
    int i;
    int j;
    int k;
    int l;
    struct UiColorBytes col = saveData_8008B570.uiColor_20.w;
    SaveSummary_LOAD* sm = &s->fileBuf_4->summary_280;
    Settings set = saveData_8008B570.settings_1C;
    SaveBody_LOAD* body;
    Minion* m;
    SaveMinion_LOAD* pm;
    UnitStats* u;
    SaveStats_LOAD* pu;

    for (n = 0x300; n < 0x1FC0; n++)
    {
        sum += ((unsigned char*)s->fileBuf_4)[n];
    }
    if (sum == sm->sum_40 && s->fileBuf_4->body_300.version_984 == 5)
    {
        body = &s->fileBuf_4->body_300;
        MemCopy_800403E8(&saveData_8008B570, body, 0x988);
        for (i = 0; i < 15; i++)
        {
            m = &saveData_8008B570.minions[i];
            pm = &body->minions_988[i];
            m->id = pm->id_0;
            m->species_2 = pm->species_2;
            m->field_3 = pm->field_3;
            for (j = 0; j < 0x30; j++)
            {
                m->species_4C[j] = pm->species_4[j];
            }
            for (j = 0; j < 8; j++)
            {
                m->field_7C[j] = pm->field_34[j];
            }
            m->field_CC = pm->field_74;
            m->skills_DE = pm->skills_86;
            m->magicBits_F4 = pm->magicBits_9C;
            m->status_84.status_0 = pm->status_3C.status_0;
            m->status_84.exp_4 = pm->status_3C.exp_4;
            m->status_84.hp_8 = pm->status_3C.hp_8;
            m->status_84.mp_C = pm->status_3C.mp_C;
            for (j = 0; j < 0xC; j++)
            {
                m->status_84.field_20[j] = pm->status_3C.field_10[j];
            }
            m->status_84.stats_2C = pm->status_3C.stats_1C;
            for (j = 0; j < 4; j++)
            {
                m->status_84.element_3E[j] = pm->status_3C.element_2E[j];
            }
            m->status_84.elementMask_42 = pm->status_3C.elementMask_32;
            m->status_84.level_44 = pm->status_3C.level_34;
            m->status_84.field_45 = pm->status_3C.field_35;
            m->status_84.field_1C[0] = 0xFF;
            m->status_84.field_1C[1] = 0xFF;
            m->status_84.field_1C[2] = 0xFF;
            m->status_84.field_1C[3] = 0xFF;
            for (j = 0; j < 6; j++)
            {
                for (k = 0; k < sizeof(m->ancestors_4[j]); k++)
                {
                    if (k < 10)
                    {
                        m->ancestors_4[j][k] = body->ancestorNames_17F8[i][j][k];
                    }
                    else
                    {
                        m->ancestors_4[j][k] = 0;
                    }
                }
            }
            for (k = 0; k < sizeof(m->status_84.name_10); k++)
            {
                if (k < 10)
                {
                    m->status_84.name_10[k] = body->minionNames_1B7C[i][k];
                }
                else
                {
                    m->status_84.name_10[k] = 0;
                }
            }
        }
        for (l = 0; l < 12; l++)
        {
            u = &saveData_8008B570.items[l];
            pu = &body->items_12E8[l];
            u->species_5C = pu->species_4C;
            u->st_0.status_0 = pu->status_0.status_0;
            u->st_0.exp_4 = pu->status_0.exp_4;
            u->st_0.hp_8 = pu->status_0.hp_8;
            u->st_0.mp_C = pu->status_0.mp_C;
            for (j = 0; j < 0xC; j++)
            {
                u->st_0.field_20[j] = pu->status_0.field_10[j];
            }
            u->st_0.stats_2C = pu->status_0.stats_1C;
            for (j = 0; j < 4; j++)
            {
                u->st_0.element_3E[j] = pu->status_0.element_2E[j];
            }
            u->st_0.elementMask_42 = pu->status_0.elementMask_32;
            u->st_0.level_44 = pu->status_0.level_34;
            u->st_0.field_45 = pu->status_0.field_35;
            u->st_0.field_1C[0] = 0xFF;
            u->st_0.field_1C[1] = 0xFF;
            u->st_0.field_1C[2] = 0xFF;
            u->st_0.field_1C[3] = 0xFF;
            for (k = 0; k < sizeof(u->st_0.name_10); k++)
            {
                if (k < 10)
                {
                    u->st_0.name_10[k] = body->itemNames_1C30[l][k];
                }
                else
                {
                    u->st_0.name_10[k] = 0;
                }
            }
        }
        if (s->flags_54 & 8)
        {
            saveData_8008B570.settings_1C = set;
            saveData_8008B570.uiColor_20.w = col;
        }
        ret = 1;
    }
    return ret;
}

void FormatCardWait1_800BA968(Task_LOAD* t)
{
    DrawLoadingIcon_8003CD5C();
    DrawMessageBox_800BACBC(msgFormatting_800BDECC);
    DrawMenuBackground_8002BE10();
    t->next_8 = FormatCardWait2_800BA9AC;
}

void FormatCardWait2_800BA9AC(Task_LOAD* t)
{
    DrawLoadingIcon_8003CD5C();
    DrawMessageBox_800BACBC(msgFormatting_800BDECC);
    DrawMenuBackground_8002BE10();
    t->next_8 = FormatCardTask_800BA9F0;
}

void FormatCardTask_800BA9F0(Task_LOAD* t, LoadMenuWork* s)
{
    switch (MemCardFormat(loadMenuRows_800BDF4C[1].cursor_C << 4))
    {
    case 0:
        t->next_8 = LoadMenuTask_800B794C;
        s->phase_28 = 0;
        s->nextScreen_24 = 3;
        s->nRead_20 = 0;
        ScanCardSaves_800BAFB0(loadMenuRows_800BDF4C[1].cursor_C);
        s->field_5C = 0;
        break;
    case 1:
        t->next_8 = LoadMenuTask_800B794C;
        s->phase_28 = 0;
        s->nextScreen_24 = 1;
        break;
    case 2:
        t->next_8 = LoadMenuTask_800B794C;
        s->phase_28 = 0;
        s->nextScreen_24 = 0xD;
        break;
    case -1:
        break;
    }
    WaitCardSync_800BADF4();
    DrawLoadingIcon_8003CD5C();
    DrawMessageBox_800BACBC(msgFormatting_800BDECC);
    DrawMenuBackground_8002BE10();
}

void LoadMenuExit_800BAAE0(Task_LOAD* t, LoadMenuWork* s)
{
    free3_8003FC6C(s->summaries_0);
    free3_8003FC6C(s->fileBuf_4);
    loadMenuActive_800BE184 = 0;
    t->flags_0 = (t->flags_0 & ~1) | 0x8000;
    MemCardStop();
    t->next_8 = LoadMenuStart_800B7650;
    if (!(s->flags_54 & 8))
    {
        FreeActiveOverlay_8002C014();
        if (s->flags_54 & 0x20)
        {
            RequestAreaReload_80027314();
            RequestGameMode_800A6D30(GetGameMode_800A6D50(1));
        }
        else if (!(s->flags_54 & 4))
        {
            RequestAreaReload_80027314();
            RequestGameMode_800A6D30(GetGameMode_800A6D50(1));
        }
        if (s->flags_54 & 1)
        {
            SaveData* m = &saveData_8008B570;
            m->field_2E2 = -1;
            m->mapId_2E4[0].field_2 = -1;
            m->mapId_2E4[1].field_2 = -1;
            m->mapId_2E4[2].field_2 = -1;
            m->mapId_2E4[3].field_2 = -1;
            dword_80091C54 = 0;
            if (!(s->flags_54 & 4))
            {
                unknownFlags_8008D678 |= 0x18000000;
            }
        }
        if (s->flags_54 & 0x10)
        {
            HaltEventsFadeStopMovie_80011BCC();
        }
    }
}

int PlayTimeHours_800BAC14(int n)
{
    return n / 216000 % 60;
}

int PlayTimeMinutes_800BAC68(int n)
{
    return n / 3600 % 60;
}

void DrawMessageBox_800BACBC(char** lines)
{
    Size_LOAD sz;
    Rect_LOAD r;
    int i;
    sz = MeasureTextLines_8003E3B4((int*)lines);
    r.x_0 = (0x13A - sz.w_0) / 2;
    r.y_2 = (0xEA - sz.h_2) / 2;
    r.w_4 = sz.w_0 + 6;
    r.h_6 = sz.h_2 + 3;
    if (sz.h_2 >= 0x10)
    {
        r.h_6 = sz.h_2 + 6;
    }
    for (i = 0; i < 3; i++)
    {
        if (lines[i])
        {
            Pos_LOAD p;
            p.x_0 = r.x_0 + 3;
            p.y_2 = r.y_2 + 5 + i * 13;
            DrawText_8003E91C(2, lines[i], &p, 5);
        }
    }
    {
        WinColor_LOAD b;
        b.field_3 = 1;
        b.field_2 = 0;
        b.color_0 = uiColor_8008B590;
        DrawWindow_80042460(&r, &b, dword_8008D454 + 0x38, 0);
    }
}

void ResetMenuRow_800BADE0(MenuRow_LOAD* p)
{
    p->cursor_C = p->initCursor_9;
    p->scroll_D = p->initScroll_A;
}

void WaitCardSync_800BADF4(void)
{
    int a = 0;
    int b = 0;
    MemCardSync(0, &b, &a);
}

int sub_800BAE24(void)
{
    return 1;
}

int GetCardFreeBlocks_800BAE2C(void)
{
    return cardFreeBlocks_800BE14C;
}

int GetCardSaveCount_800BAE3C(void)
{
    return cardSaveCount_800BE150;
}

char* GetCardSaveName_800BAE4C(int i)
{
    char** p = cardSaveNames_800BE188;
    return p[i];
}

int PollCardAccept_800BAE68(int slot)
{
    int x[2]; // the MemCardSync command and result
    int ret = -1;
    int r;
    int chan = slot << 4;
    x[0] = 0;
    x[1] = 0;
    r = MemCardSync(1, &x[0], &x[1]);
    switch (r)
    {
    case 0:
        break;
    case -1:
        MemCardAccept(chan);
        break;
    case 1:
        if (x[0] == 2)
        {
            ret = x[1];
        }
        break;
    }
    return ret;
}

int PollCardExist_800BAF0C(int slot)
{
    int x[2]; // the MemCardSync command and result
    int ret = -1;
    int r;
    int chan = slot << 4;
    x[0] = 0;
    x[1] = 0;
    r = MemCardSync(1, &x[0], &x[1]);
    switch (r)
    {
    case 0:
        break;
    case -1:
        MemCardExist(chan);
        break;
    case 1:
        if (x[0] == 1)
        {
            ret = x[1];
        }
        break;
    }
    return ret;
}

// Matched
void ScanCardSaves_800BAFB0(int slot)
{
    DirEntry_LOAD dir[15];
    long files;
    int blocks;
    int found;
    int i;
    i = found = blocks = 0;
    files = 0;
    MemCardGetDirentry(slot << 4, aDirWildcard_800B72FC, dir, &files, 0, 15);
    for (i = found; i < files; i++)
    {
        int q = dir[i].size_18 / 0x2000;
        if (dir[i].size_18 & 0x1FFF)
        {
            blocks += q + 1;
        }
        else
        {
            blocks += q;
        }
    }
    for (i = 0; i < 15; i++)
    {
        if (FindDirEntry_800BB23C(files, saveFileNames_800BE028[0][i], dir))
        {
            found++;
            cardSaveNames_800BE188[i] = saveFileNames_800BE028[0][i];
        }
        else
        {
            cardSaveNames_800BE188[i] = 0;
        }
    }
    cardFreeBlocks_800BE14C = 15 - blocks;
    cardSaveCount_800BE150 = found;
}

// Matched
void ScanCardSavesComb_800BB0E4(int slot)
{
    DirEntry_LOAD dir[15];
    long files;
    int blocks;
    int found;
    int i;
    i = found = blocks = 0;
    files = 0;
    MemCardGetDirentry(slot << 4, aDirWildcard_800B72FC, dir, &files, 0, 15);
    for (i = found; i < files; i++)
    {
        int q = dir[i].size_18 / 0x2000;
        if (dir[i].size_18 & 0x1FFF)
        {
            blocks += q + 1;
        }
        else
        {
            blocks += q;
        }
    }
    for (i = 0; i < 15; i++)
    {
        if (FindDirEntry_800BB23C(files, saveFileNames_800BE028[0][i], dir))
        {
            found++;
            cardSaveNames_800BE188[i] = saveFileNames_800BE028[0][i];
        }
        else if (FindDirEntry_800BB23C(files, saveFileNames_800BE028[1][i], dir))
        {
            found++;
            cardSaveNames_800BE188[i] = saveFileNames_800BE028[1][i];
        }
        else
        {
            cardSaveNames_800BE188[i] = 0;
        }
    }
    cardFreeBlocks_800BE14C = 15 - blocks;
    cardSaveCount_800BE150 = found;
}

// 1 when name is one of the nFiles directory entries (DirEntry_LOAD, 0x28 bytes each)
int FindDirEntry_800BB23C(int nFiles, unsigned char* name, unsigned char* dir)
{
    int i;
    int j;
    int diff;
    int res = 0;
    for (i = 0; i < nFiles; i++, dir += 0x28)
    {
        diff = 0;
        for (j = 0; j < 0x15; j++)
        {
            if (name[j] == 0)
            {
                break;
            }
            if (name[j] != dir[j])
            {
                diff++;
                break;
            }
        }
        if (diff == 0)
        {
            res = 1;
            break;
        }
    }
    return res;
}

#if 0
// Not matched: register allocation (h/i/table pointer in $s0/$s1/$s2 in the original) and the clearing loops are not strength-reduced to a decrementing pointer here
void BuildCardHeader_800BB2AC(CardHeader_LOAD* h, int idx, char* title)
{
    int i;
    int j;
    RECT r;
    for (i = 0; i < 3; i++)
    {
        POLY_FT4* p = &publicTiyPolyFT4s_8008D430[saveIconSrc_800BE0A0[i].poly_0];
        int tp = p->tpage & 0x1F;
        r.x = (p->u0 >> 2) + ((tp << 6) & 0x3FF);
        r.y = p->v0 + ((tp / 16) << 8);
        r.w = 4;
        r.h = 0x10;
        StoreImage(&r, (u_long*)h->icon_80[i]);
        DrawSync(0);
        r.x = saveIconSrc_800BE0A0[i].clutX_4;
        r.y = saveIconSrc_800BE0A0[i].clutY_6;
        r.w = 0x10;
        r.h = 1;
        StoreImage(&r, (u_long*)h->clut_60);
        DrawSync(0);
    }
    h->magic_0[0] = 'S';
    h->magic_0[1] = 'C';
    h->type_2 = 0x13;
    h->blocks_3 = 1;
    {
        char* t = h->title_4;
        for (j = 63; j >= 0; j--)
        {
            t[j] = 0;
        }
    }
    if (title)
    {
        strcpy_8004E2D8(h->title_4, title);
    }
    else
    {
        strcpy_8004E2D8(h->title_4, cardTitles_800BDFB0[idx]);
    }
    for (i = 11; i >= 0; i--)
    {
        h->field_44[i] = 0;
    }
    h->field_50 = 1;
    h->tag_52 = aCRD0_800B7300;
    h->tag_52.c[4] = 0;
    h->field_57 = 0;
    h->field_5C = 0;
    MemCopy_800403E8(h->field_200, cardHeaderTail_800BE0B8, 0x80);
}
#endif
INCLUDE_OVERLAY_ASM(load, BuildCardHeader_800BB2AC);

void DrawCardSlotMenu_800BB4A8(short sel)
{
    MenuItems2_LOAD a = cardSlotMenuItem1_800B731C;
    MenuItems2_LOAD b = cardSlotMenuItem2_800B7368;
    MenuItem_LOAD* list[3];
    MenuWin_LOAD w;
    int i;
    list[0] = a.items_0;
    list[1] = b.items_0;
    list[2] = 0;
    w.field_0 = 2;
    w.time_4 = 0;
    w.field_8 = 8;
    w.cursor_C = 0;
    w.items_10 = list;
    w.field_14 = 0;
    for (i = 0; i < 2; i++)
    {
        list[i]->flags_0 |= 2;
    }
    w.time_4 = frameCount_8008D3FC;
    w.cursor_C = sel;
    DrawMenuWindows_8002A5A4(&w);
}

// 0x800BB5DC..0x800BD93C: PSY-Q 4.4 LIBMCRD.LIB modules LIBMCRD, USERFUNC and BIOS, linked from the library
// (config/ovl_lib_objs.txt), as are their .rdata, .data and .bss.

Pos_LOAD saveSlotFieldPos_800BD93C[9] = {
    { 170, 54 },
    { 144, 68 },
    { 172, 68 },
    { 222, 68 },
    { 244, 68 },
    { 225, 54 },
    { 39, 55 },
    { 39, 68 },
    { 0x122, 52 },
};
UiSprite_LOAD saveSlotSprites_800BD960[7] = {
    { 13, 52, 119, 1 },
    { 104, 52, 227, 1 },
    { 100, 66, 118, 1 },
    { 180, 65, 203, 1 },
    { 180, 52, 122, 1 },
    { 13, 66, 150, 1 },
    { -1, -1, -1, -1 },
};
UiSprite_LOAD modeTitleSprites_800BD998[2] = {
    { 80, 21, 190, 1 },
    { 69, 21, 197, 1 },
};
int cardSlotSprites_800BD9A8[16] = {
    0x15006C, 0x10027, 0x5F0027, 0x10027, 0x6D003B, 0x100B2, 0x6D006A, 0x10000,
    0x5F00BC, 0x10027, 0x6D00D0, 0x100B2, 0x6D00FF, 0x10002, -1, -1,
};
UiSprite_LOAD saveIconSprites_800BD9E8[4] = {
    { 0x110, 52, 78, 1 },
    { 0x110, 52, 52, 1 },
    { 0x110, 52, 58, 1 },
    { -1, -1, -1, -1 },
};
char *saveListPrompts_800BDA08[2] = { aSelectSaveLocat_800B66F0, aSelectGameToLoa_800B66C4 };
RECT saveListClip_800BDA10 = { 10, 49, 0x12C, 129 };
MenuItem_LOAD saveListRow0_800BDA18[2] = {
    { 64, 0, 0, 0, 0, 10, 49, { 44, 1, 31 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD saveListRow1_800BDA50[2] = {
    { 64, 0, 0, 0, 0, 10, 82, { 44, 1, 31 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD saveListRow2_800BDA88[2] = {
    { 64, 0, 0, 0, 0, 10, 115, { 44, 1, 31 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD saveListRow3_800BDAC0[2] = {
    { 64, 0, 0, 0, 0, 10, 148, { 44, 1, 31 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD *saveListRows_800BDAF8[5] = { saveListRow0_800BDA18, saveListRow1_800BDA50, saveListRow2_800BDA88, saveListRow3_800BDAC0 };
MenuWin_LOAD saveListWin_800BDB0C = { 2, 0, 8, 0, saveListRows_800BDAF8, 5 };
int cardSlot1Item_800BDB24[14] = {
    64, 0, 0, 0, 0x5A0021, 0x240069, 0, 1,
    0, 0, 0, -1, -1, -1,
};
void *cardSlot1Items_800BDB5C[2] = { (void *)cardSlot1Item_800BDB24 };
int cardSlot1Win_800BDB64 = 2;
int cardSlot1WinRest_800BDB68[5] = { 0, 8, 0, (int)cardSlot1Items_800BDB5C, 5 };
int cardSlot2Item_800BDB7C[14] = {
    64, 0, 0, 0, 0x5A00B6, 0x240069, 0, 1,
    0, 0, 0, -1, -1, -1,
};
void *cardSlot2Items_800BDBB4[2] = { (void *)cardSlot2Item_800BDB7C };
int cardSlot2Win_800BDBBC = 2;
int cardSlot2WinRest_800BDBC0[5] = { 0, 8, 0, (int)cardSlot2Items_800BDBB4, 5 };
int *cardSlotWins_800BDBD4[2] = { &cardSlot1Win_800BDB64, &cardSlot2Win_800BDBBC };
MenuItem_LOAD topMenuSave_800BDBDC[2] = {
    { 8, 1, 190, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 106, 69, { 108, 0, 19, 0, 0, 0, 4 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD topMenuLoad_800BDC14[2] = {
    { 8, 1, 197, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 106, 90, { 108, 0, 19, 0, 0, 0, 4 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD topMenuExit_800BDC4C[2] = {
    { 8, 1, 198, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 106, 111, { 108, 0, 19, 0, 0, 0, 4 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD topMenuTitle_800BDC84[2] = {
    { 8, 1, 196, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 106, 132, { 108, 0, 19, 0, 0, 0, 4 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD *topMenuItems_800BDCBC[5] = { topMenuSave_800BDBDC, topMenuLoad_800BDC14, topMenuExit_800BDC4C, topMenuTitle_800BDC84 };
MenuWin_LOAD topMenuWin_800BDCD0 = { 2, 0, 8, 0, topMenuItems_800BDCBC, 5 };
MenuItem_LOAD formatYes_800BDCE8[2] = {
    { 8, 3, (int)aYES_800B671C, 0, 0, 126, 106, { 56, 0, 18, 0, 2, 0, 2 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD formatNo_800BDD20[2] = {
    { 8, 3, (int)aNO_800B6724, 0, 0, 126, 126, { 56, 0, 18, 0, 2, 0, 2 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD *formatItems_800BDD58[3] = { formatYes_800BDCE8, formatNo_800BDD20 };
MenuWin_LOAD formatWin_800BDD64 = { 2, 0, 8, 1, formatItems_800BDD58 };
MenuItem_LOAD confirmYes_800BDD7C[2] = {
    { 8, 3, (int)aYES_800B671C, 0, 0, 215, 193, { 46, 0, 19, 0, 2, 0, 2 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD confirmNo_800BDDB4[2] = {
    { 8, 3, (int)aNO_800B6724, 0, 0, 0x105, 193, { 48, 0, 19, 0, 2, 0, 2 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD *confirmItems_800BDDEC[3] = { confirmYes_800BDD7C, confirmNo_800BDDB4 };
MenuWin_LOAD confirmWin_800BDDF8 = { 2, 0, 8, 1, confirmItems_800BDDEC };
MenuItem_LOAD titleYes_800BDE10[2] = {
    { 8, 3, (int)aYES_800B671C, 0, 0, 106, 121, { 52, 0, 19, 0, 2, 0, 2 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD titleNo_800BDE48[2] = {
    { 8, 3, (int)aNO_800B6724, 0, 0, 163, 121, { 52, 0, 19, 0, 2, 0, 2 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD *titleItems_800BDE80[3] = { titleYes_800BDE10, titleNo_800BDE48 };
MenuWin_LOAD titleWin_800BDE8C = { 2, 0, 8, 1, titleItems_800BDE80 };
char loadMenuButtonHelp_800BDEA4[24] = { 16, 0, 0, 0, 56, 103, 11, 128, 167, 0, 0, 0, 44, 103, 11, 128, 255, 255, 255, 255 };
char *msgCardFull_800BDEBC[4] = { aMEMORYCARDFull_800B6748 };
char *msgFormatting_800BDECC[4] = { aFormattingMEMOR_800B67A4, aDoNotRemoveMEMO_800B676C };
char *msgLoading_800BDEDC[4] = { aLoading_800B67D8, aDoNotRemoveMEMO_800B676C };
char *msgSaving_800BDEEC[4] = { aSaving_800B67F0, aDoNotRemoveMEMO_800B676C };
char *msgNoSaveData_800BDEFC[8] = { aNoSaveGameData_800B6804, 0, 0, 0, byte_800B682C };
char *msgFormatFailed_800BDF1C[4] = { aFormattingFaile_800B6864 };
char *msgSaveFailed_800BDF2C[4] = { aSaveFailed_800B688C };
char *msgLoadFailed_800BDF3C[4] = { aLoadFailed_800B68A8 };
MenuRow_LOAD loadMenuRows_800BDF4C[2] = {
    { { 68, 0, 116, 0, 0, 14 }, 1, 4, 4 },
    { { 68, 0, 116, 0, 0, 14 }, 2, 1, 2 },
};
int loadMenuRow2_800BDF6C[4] = { 0x480012, 0x2010E00, 0x102 };
int loadMenuRow3_800BDF7C[4] = { 0x40000A, 0x4012100, 0x4000000F };
int loadMenuRow4_800BDF8C[4] = { 0x40000A, 0x1022100, 0x1000002 };
int loadMenuRow5_800BDF9C[4] = { 0x40000A, 0x1022100, 0x102 };
SaveTitle_LOAD *saveTitle_800BDFAC = (void *)aJadeCocoonLevel_800B6BAC;
char *cardTitles_800BDFB0[30] = {
    aJadeCocoon01_800B6F88, aJadeCocoon02_800B6F6C, aJadeCocoon03_800B6F50, aJadeCocoon04_800B6F34,
    aJadeCocoon05_800B6F18, aJadeCocoon06_800B6EFC, aJadeCocoon07_800B6EE0, aJadeCocoon08_800B6EC4,
    aJadeCocoon09_800B6EA8, aJadeCocoon10_800B6E8C, aJadeCocoon11_800B6E70, aJadeCocoon12_800B6E54,
    aJadeCocoon13_800B6E38, aJadeCocoon14_800B6E1C, aJadeCocoon15_800B6E00, aCombDataTitle01_800B6DE4,
    aCombDataTitle02_800B6DC8, aCombDataTitle03_800B6DAC, aCombDataTitle04_800B6D90, aCombDataTitle05_800B6D74,
    aCombDataTitle06_800B6D58, aCombDataTitle07_800B6D3C, aCombDataTitle08_800B6D20, aCombDataTitle09_800B6D04,
    aCombDataTitle10_800B6CE8, aCombDataTitle11_800B6CCC, aCombDataTitle12_800B6CB0, aCombDataTitle13_800B6C94,
    aCombDataTitle14_800B6C78, aCombDataTitle15_800B6C5C,
};
char *saveFileNames_800BE028[2][15] = {
    {
        aBASLUS00854GAME_800B725C, aBASLUS00854GAME_800B7244, aBASLUS00854GAME_800B722C, aBASLUS00854GAME_800B7214,
        aBASLUS00854GAME_800B71FC, aBASLUS00854GAME_800B71E4, aBASLUS00854GAME_800B71CC, aBASLUS00854GAME_800B71B4,
        aBASLUS00854GAME_800B719C, aBASLUS00854GAME_800B7184, aBASLUS00854GAME_800B716C, aBASLUS00854GAME_800B7154,
        aBASLUS00854GAME_800B713C, aBASLUS00854GAME_800B7124, aBASLUS00854GAME_800B710C,
    },
    {
        aBASLUS00854COMB_800B70F4, aBASLUS00854COMB_800B70DC, aBASLUS00854COMB_800B70C4, aBASLUS00854COMB_800B70AC,
        aBASLUS00854COMB_800B7094, aBASLUS00854COMB_800B707C, aBASLUS00854COMB_800B7064, aBASLUS00854COMB_800B704C,
        aBASLUS00854COMB_800B7034, aBASLUS00854COMB_800B701C, aBASLUS00854COMB_800B7004, aBASLUS00854COMB_800B6FEC,
        aBASLUS00854COMB_800B6FD4, aBASLUS00854COMB_800B6FBC, aBASLUS00854COMB_800B6FA4,
    },
};
IconSrc_LOAD saveIconSrc_800BE0A0[3] = {
    { 75, 0x380, 254 },
    { 76, 0x3F0, 0x143 },
    { 77, 0x380, 252 },
};
char cardHeaderTail_800BE0B8[148] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 28, 0, 0, 62, 126, 0, 0, 119, 227, 0, 0, 227, 193, 0, 0, 192, 1, 0, 0, 255, 255, 0, 192, 243, 239, 3, 224, 224, 3, 7, 48, 195, 1, 14, 152, 199, 113, 28, 220, 207, 252, 24, 204, 204, 252, 25, 206, 204, 254, 57, 206, 207, 182, 59, 142, 199, 54, 59, 142, 199, 182, 59, 206, 207, 252, 57, 206, 204, 248, 16, 206, 204, 48, 0, 196, 15, 56, 63, 128, 7, 156, 63, 0, 3, 206, 1, 192, 15, 230, 0, 224, 31, 126, 0, 112, 59, 60, 0, 48, 51, 24, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 116, 114, 11, 128, 144, 114, 11, 128, 168, 114, 11, 128, 192, 114, 11, 128, 216, 114, 11, 128 };
int cardFreeBlocks_800BE14C = 0;
int cardSaveCount_800BE150 = 0;

int loadMenuActive_800BE184 BSS = 0;
char *cardSaveNames_800BE188[15] BSS = { 0 };
