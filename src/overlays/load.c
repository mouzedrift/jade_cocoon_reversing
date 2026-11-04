// LOAD.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "load.h"

extern int dword_800BE174;
extern int (*dword_800BE294[])();
// a task (EventEntry of the event lists) as its callbacks see it
typedef struct
{
    unsigned int flags_0;
    int f4;
    void (*next_8)();
    void (*fC)();
    int size_10;
    void* work_14;
} Task_LOAD;
extern EventNode* loadMenuTask_8008D480; // the load menu's task list
extern int MemCardSync(int a, int* b, int* c);
extern void MemCardAccept();
extern void MemCardExist();
extern long MemCardReadFile(long chan, char* file, void* adrs, long ofs, long bytes);
extern void LoadMenuInit_800B7674(int mode, int b);
extern void sub_800B7894();
extern int uiTiyLoaded_8008B4E8;
extern long MemCardCreateFile(long chan, char* file, long blocks);
extern long MemCardWriteFile(long chan, char* file, void* adrs, long ofs, long bytes);
extern int sub_800BA3EC();
extern void DrawLoadingIcon_8003CD5C(void);
extern void DrawMenuBackground_8002BE10(void);
extern void DrawMessageBox_800BACBC(char** lines);
extern void LoadMenuTask_800B794C();
extern void sub_800B79F8();
extern void sub_800B9A8C();
extern void WriteSaveTask_800B98C4();
extern void LoadSaveTask_800BA234();
extern void sub_800BA968();
extern void LoadMenuExit_800BAAE0();
extern void sub_800BA9AC();
extern void FormatCardTask_800BA9F0();
extern void LoadUiTiy_8002BF74(void);
extern int dword_8008BD80;
extern int UpdateMenuCursor_8003D794(short* cursor, int b);

// memory card file header (the PSY-Q _CARD layout; the game's own data in the reserved part and behind the icons)
typedef struct
{
    char magic_LOAD[2];
    char type_LOAD;
    char blocks_LOAD;
    char title_LOAD[64];
    char f44_LOAD[12];
    short f50_LOAD;
    Bytes5_LOAD f52_LOAD;
    char f57_LOAD;
    char pad58_LOAD[4];
    int f5C_LOAD;
    char clut_LOAD[32];
    char icon_LOAD[3][128];
    char f200_LOAD[0x80];
} CardHeader_LOAD;
typedef struct
{
    char pad0_LOAD[0xC];
    unsigned char u0_LOAD;
    unsigned char v0_LOAD;
    char padE_LOAD[8];
    unsigned short tpage_LOAD;
    char pad18_LOAD[0x10];
} PolyFT4_LOAD;
extern PolyFT4_LOAD* publicTiyPolyFT4s_8008D430;
extern char* strcpy_8004E2D8(char* dst, char* src); // PSY-Q strcpy (not in symbol_addrs.txt)
typedef struct DirEntry_LOAD
{
    char name_LOAD[20];
    long attr_LOAD;
    long size_LOAD;
    struct DirEntry_LOAD* next_LOAD;
    long head_LOAD;
    char system_LOAD[4];
} DirEntry_LOAD;
extern long MemCardGetDirentry(long chan, char* name, DirEntry_LOAD* dir, long* files, long ofs, long max);
extern void FreeActiveOverlay_8002C014(void);
extern int sub_800A6D50(int a);
extern void sub_800A6D30(int a);
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
extern unsigned char byte_800BDF68;
extern void _clr_card_event(void);
extern int _get_card_event_x(void);
typedef struct
{
    short s_LOAD;
    char c0_LOAD;
    char c1_LOAD;
} Tail4_LOAD;
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
    SaveSummary_LOAD* summaries_LOAD; // one per save (15)
    SaveFile_LOAD* fileBuf_LOAD; // one save file
    int f8_LOAD;
    char padC_LOAD[8];
    int f14_LOAD;
    char pad18_LOAD[8];
    int f20_LOAD;
    int f24_LOAD;
    int f28_LOAD;
    int f2C_LOAD;
    short s30_LOAD;
    short s32_LOAD;
    char pad34_LOAD[8];
    int f3C_LOAD;
    int f40_LOAD;
    char pad44_LOAD[0x10];
    unsigned f54_LOAD;
    char* place_58_LOAD; // the save place text of the summary (sub_800B78B8)
    int f5C_LOAD;
    int f60_LOAD;
    void* rows_LOAD[6];
} LoadTask_LOAD;
typedef struct
{
    short w_LOAD;
    short h_LOAD;
} Size_LOAD;
typedef struct
{
    short x_LOAD;
    short y_LOAD;
    short w_LOAD;
    short h_LOAD;
} Rect_LOAD;
extern Size_LOAD MeasureTextLines_8003E3B4(int* list);
extern int IsConfirmPressed_8003D288(int a, int b);
extern int IsCancelPressed_8003D3C0(int a, int b);
extern void UserFuncOpen(void* fn, int a);
extern void sub_800BB6F4(void);
extern void sub_800BBA5C(void);
typedef struct
{
    short a_LOAD;
    short b_LOAD;
} Pair_LOAD;
extern void ResetMenuRow_800BADE0(Row16_LOAD* p);
extern void DrawScrollArrows_8002B8DC(Pair_LOAD q, short* a, short* b, int c);
void sub_800B8BD4(LoadTask_LOAD* t);
extern void PlaySfx_80031494(int a);
extern void WaitCardSync_800BADF4(void);
extern char* GetCardSaveName_800BAE4C(int n);
extern int GetCardFreeBlocks_800BAE2C(void);
extern int GetCardSaveCount_800BAE3C(void);
typedef struct
{
    char c_LOAD[6];
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

void sub_800B7650(void)
{
    LoadMenuInit_800B7674(4, 0);
}

#if 0
// Not matched: mode and t swap $s3/$s4, and the case 0/1 stores are scheduled differently
void LoadMenuInit_800B7674(int mode, int b)
{
    int i;
    Task_LOAD* t;
    LoadTask_LOAD* s;
    MemCardStart();
    t = (Task_LOAD*)&loadMenuTask_8008D480->entry;
    s = (LoadTask_LOAD*)t->work_14;
    t->flags_0 = (t->flags_0 | 1) & ~0x8000;
    for (i = 0; i < 6; i++)
    {
        ResetMenuRow_800BADE0(&stru_800BDF4C[i]);
    }
    s->f8_LOAD = 0;
    s->f24_LOAD = -1;
    s->f28_LOAD = 0;
    switch (mode)
    {
    case 0:
        s->s30_LOAD = 1;
        stru_800BDF4C[0].fC_LOAD = 0;
        s->f54_LOAD = 4;
        break;
    case 1:
        s->s30_LOAD = 1;
        stru_800BDF4C[0].fC_LOAD = 1;
        s->f54_LOAD = 4;
        break;
    case 2:
        s->s30_LOAD = 1;
        stru_800BDF4C[0].fC_LOAD = 1;
        s->f54_LOAD = 0xC;
        t->next_8 = LoadMenuTask_800B794C;
        goto done;
    case 3:
        s->s30_LOAD = 1;
        stru_800BDF4C[0].fC_LOAD = 1;
        s->f54_LOAD = 0x4C;
        t->next_8 = LoadMenuTask_800B794C;
        goto done;
    default:
        s->s30_LOAD = 0;
        stru_800BDF4C[0].fC_LOAD = 0;
        s->f54_LOAD = 0;
        break;
    }
    LoadUiTiy_8002BF74();
    t->next_8 = sub_800B7894;
done:
    if (dword_8008BD80 == -1 && !(s->f54_LOAD & 8))
    {
        s->s30_LOAD = 1;
        stru_800BDF4C[0].fC_LOAD = 0;
        s->f54_LOAD = 0x20;
    }
    s->f5C_LOAD = 0;
    s->f20_LOAD = 0;
    s->f14_LOAD = 0;
    s->s32_LOAD = 0;
    s->f2C_LOAD = 0;
    s->f3C_LOAD = 0;
    s->f40_LOAD = 0;
    s->rows_LOAD[0] = &stru_800BDF4C[0];
    s->rows_LOAD[1] = &stru_800BDF4C[1];
    s->rows_LOAD[2] = &stru_800BDF4C[2];
    s->rows_LOAD[3] = &stru_800BDF4C[3];
    s->rows_LOAD[4] = &stru_800BDF4C[4];
    s->rows_LOAD[5] = &stru_800BDF4C[5];
    s->summaries_LOAD = malloc3_8003FC4C(0x780);
    s->fileBuf_LOAD = malloc3_8003FC4C(sizeof(SaveFile_LOAD));
    loadMenuActive_800BE184 = 1;
}
#endif
INCLUDE_OVERLAY_ASM(load, LoadMenuInit_800B7674);

void sub_800B7894(Task_LOAD* t)
{
    if (uiTiyLoaded_8008B4E8)
    {
        t->next_8 = LoadMenuTask_800B794C;
    }
}

void sub_800B78B8(char* place)
{
    ((LoadTask_LOAD*)loadMenuTask_8008D480->entry.buffer)->place_58_LOAD = place;
}

void sub_800B78D0(void)
{
    LoadTask_LOAD* t;
    saveData_8008B570.field_810 = -1;
    saveData_8008B570.field_0 |= 0x180;
    t = loadMenuTask_8008D480->entry.buffer;
    t->s30_LOAD = 1;
    stru_800BDF4C[0].fC_LOAD = 0;
    t->f54_LOAD = 0x20;
}

int sub_800B7914(void)
{
    return ((LoadTask_LOAD*)loadMenuTask_8008D480->entry.buffer)->f8_LOAD;
}

void sub_800B7934(void)
{
}

int IsLoadMenuActive_800B793C(void)
{
    return loadMenuActive_800BE184;
}

void LoadMenuTask_800B794C(Task_LOAD* t, LoadTask_LOAD* s)
{
    switch (s->f28_LOAD)
    {
    case 0:
        sub_800B79F8(s);
        break;
    case 2:
        sub_800B9A8C(s);
        t->next_8 = WriteSaveTask_800B98C4;
        s->f2C_LOAD = 0;
        break;
    case 3:
        t->next_8 = LoadSaveTask_800BA234;
        break;
    case 4:
        t->next_8 = sub_800BA968;
        break;
    case 5:
    case 6:
        t->next_8 = LoadMenuExit_800BAAE0;
        break;
    }
}
const char byte_800B68E0[] = "\202k\202\217\202\201\202\204\201@\202\207\202\201\202\215\202\205\201H"; // Load game?
const char byte_800B68F8[] = "\202n\202\226\202\205\202\222\202\227\202\222\202\211\202\224\202\205\201@\202\207\202\201\202\215\202\205\201H"; // Overwrite game?
const char byte_800B6918[] = "\202r\202\201\202\226\202\205\201@\202\207\202\201\202\215\202\205\201H"; // Save game?
const Bytes8_LOAD dword_800B6930 = { { 10, 0, 193, 0, 204, 0, 20 } };
const char byte_800B6938[] = "\202q\202\205\202\224\202\225\202\222\202\216\201@\202\224\202\217\201@\202\224\202\211\202\224\202\214\202\205\201@\202\223\202\203\202\222\202\205\202\205\202\216\201H"; // Return to title screen?
const Bytes8_LOAD dword_800B6968 = { { 92, 0, 100, 0, 140, 0, 19 } };
const int dword_800B6970 = 0;

extern unsigned short padPressed_8009194C[];
extern void DrawButtonHelpBar_8002B004(void* p, int a, int b);
extern int PollCardExist_800BAF0C(int a);
extern int PollCardAccept_800BAE68(int a);
void sub_800B80F8(LoadTask_LOAD* t);
void sub_800B82FC(LoadTask_LOAD* t);
void sub_800B847C(LoadTask_LOAD* t);
void sub_800B85AC(LoadTask_LOAD* t);
void sub_800B867C(LoadTask_LOAD* t);
void sub_800B877C(LoadTask_LOAD* t);
void sub_800B8984(LoadTask_LOAD* t);
void sub_800B8A20(LoadTask_LOAD* t);
void sub_800B8AE4(LoadTask_LOAD* t);
void sub_800B9220(LoadTask_LOAD* t);
void sub_800B92C0(LoadTask_LOAD* t);
void sub_800B9360(LoadTask_LOAD* t);
void sub_800B9470(LoadTask_LOAD* t);
void sub_800B952C(LoadTask_LOAD* t);
void sub_800B9654(LoadTask_LOAD* t);
int ReadSaveSummaries_800B9724(LoadTask_LOAD* t);
// Matched
void sub_800B79F8(LoadTask_LOAD* t)
{
    union // the text position and the window colour share one slot (case 4)
    {
        Pos_LOAD pos;
        Tail4_LOAD tail;
    } u;
    int r;
    sub_800B80F8(t);
    switch (t->s30_LOAD)
    {
    case 9:
    case 10:
        dword_800BDB0C.f4_LOAD = 0;
        dword_800BDB0C.f0_LOAD = 1;
        DrawMenuWindows_8002A5A4(&dword_800BDB0C);
        sub_800B867C(t);
        sub_800B8984(t);
        sub_800B8A20(t);
        sub_800B8AE4(t);
        sub_800B877C(t);
        if (padPressed_8009194C[(t->f54_LOAD >> 6) & 1])
        {
            t->f24_LOAD = 3;
        }
        if (!ReadSaveSummaries_800B9724(t))
        {
            t->f24_LOAD = 1;
        }
        break;
    case 7:
        DrawMessageBox_800BACBC(dword_800BDEBC);
        if (!ReadSaveSummaries_800B9724(t) || padPressed_8009194C[(t->f54_LOAD >> 6) & 1])
        {
            t->f24_LOAD = 1;
        }
        break;
    case 11:
        switch (PollCardExist_800BAF0C(byte_800BDF68))
        {
        case -1:
        case 0:
        case 2:
        case 3:
            break;
        case 1:
            t->f24_LOAD = 1;
            break;
        }
        sub_800B847C(t);
        sub_800B877C(t);
        if (padPressed_8009194C[(t->f54_LOAD >> 6) & 1])
        {
            t->f24_LOAD = 1;
        }
        break;
    case 8:
        DrawMessageBox_800BACBC(dword_800BDEFC);
        switch (PollCardAccept_800BAE68(byte_800BDF68))
        {
        case -1:
        case 0:
        case 4:
            break;
        default:
            t->f24_LOAD = 1;
            break;
        }
        if (padPressed_8009194C[(t->f54_LOAD >> 6) & 1])
        {
            t->f24_LOAD = 1;
        }
        break;
    case 0:
        dword_800BDCD0.f4_LOAD = GetTime30Hz_8002C64C();
        dword_800BDCD0.fC_LOAD = stru_800BDF4C[t->s30_LOAD].fC_LOAD;
        DrawMenuWindows_8002A5A4(&dword_800BDCD0);
        sub_800B877C(t);
        sub_800B9220(t);
        break;
    case 1:
        sub_800B82FC(t);
        sub_800B877C(t);
        sub_800B92C0(t);
        break;
    case 6:
        switch (PollCardExist_800BAF0C(byte_800BDF68))
        {
        case 0:
        case 3:
        case 4:
            WaitCardSync_800BADF4();
            t->f24_LOAD = 0x12;
            break;
        }
        sub_800B847C(t);
        sub_800B877C(t);
        if (padPressed_8009194C[(t->f54_LOAD >> 6) & 1])
        {
            t->f24_LOAD = 1;
        }
        break;
    case 18:
        sub_800B847C(t);
        sub_800B877C(t);
        sub_800B9360(t);
        break;
    case 2:
        dword_800BDD64.f4_LOAD = GetTime30Hz_8002C64C();
        dword_800BDD64.fC_LOAD = stru_800BDF4C[t->s30_LOAD].fC_LOAD;
        sub_800B85AC(t);
        sub_800B9470(t);
        break;
    case 3:
        dword_800BDB0C.f4_LOAD = GetTime30Hz_8002C64C();
        dword_800BDB0C.fC_LOAD = stru_800BDF4C[t->s30_LOAD].fC_LOAD;
        dword_800BDB0C.f0_LOAD = 2;
        if (!ReadSaveSummaries_800B9724(t))
        {
            t->f24_LOAD = 1;
        }
        DrawMenuWindows_8002A5A4(&dword_800BDB0C);
        sub_800B867C(t);
        sub_800B8984(t);
        sub_800B8A20(t);
        sub_800B8AE4(t);
        sub_800B877C(t);
        sub_800B952C(t);
        break;
    case 4:
        dword_800BDB0C.f4_LOAD = 0;
        dword_800BDB0C.fC_LOAD = stru_800BDF4C[3].fC_LOAD;
        dword_800BDB0C.f0_LOAD = 4;
        dword_800BDDF8.f4_LOAD = GetTime30Hz_8002C64C();
        dword_800BDDF8.fC_LOAD = stru_800BDF4C[t->s30_LOAD].fC_LOAD;
        if (!ReadSaveSummaries_800B9724(t))
        {
            t->f24_LOAD = 1;
        }
        DrawMenuWindows_8002A5A4(&dword_800BDB0C);
        sub_800B867C(t);
        sub_800B8984(t);
        sub_800B8A20(t);
        sub_800B8AE4(t);
        DrawMenuWindows_8002A5A4(&dword_800BDDF8);
        if (stru_800BDF4C[0].fC_LOAD == 1)
        {
            u.pos.x_LOAD = 0xD;
            u.pos.y_LOAD = 0xC4;
            DrawText_8003E91C(2, byte_800B68E0, &u.pos, 5);
        }
        else if (stru_800BDF4C[0].fC_LOAD == 0)
        {
            if (GetCardSaveName_800BAE4C(stru_800BDF4C[3].fD_LOAD + stru_800BDF4C[3].fC_LOAD))
            {
                u.pos.x_LOAD = 0xD;
                u.pos.y_LOAD = 0xC4;
                DrawText_8003E91C(2, byte_800B68F8, &u.pos, 5);
            }
            else
            {
                u.pos.x_LOAD = 0xD;
                u.pos.y_LOAD = 0xC4;
                DrawText_8003E91C(2, byte_800B6918, &u.pos, 5);
            }
        }
        {
            Bytes8_LOAD a;
            a = dword_800B6930;
            u.tail.c1_LOAD = 1;
            u.tail.c0_LOAD = 0;
            u.tail.s_LOAD = uiColor_8008B590;
            DrawWindow_80042460(&a, &u.tail, dword_8008D454 + 0x38, 0);
        }
        sub_800B9654(t);
        break;
    case 5:
        dword_800BDE8C.f4_LOAD = GetTime30Hz_8002C64C();
        dword_800BDE8C.fC_LOAD = stru_800BDF4C[t->s30_LOAD].fC_LOAD;
        u.pos.x_LOAD = 0x66;
        u.pos.y_LOAD = 0x69;
        DrawText_8003E91C(2, byte_800B6938, &u.pos, 5);
        {
        Bytes8_LOAD a;
        Tail4_LOAD b;
        a = dword_800B6968;
        b.c1_LOAD = 1;
        b.c0_LOAD = 0;
        b.s_LOAD = uiColor_8008B590;
        DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
        }
        DrawMenuWindows_8002A5A4(&dword_800BDE8C);
        if (IsConfirmPressed_8003D288(0, (t->f54_LOAD >> 6) & 1))
        {
            if (stru_800BDF4C[t->s30_LOAD].fC_LOAD == 0)
            {
                t->f54_LOAD = 0x10;
                t->f28_LOAD = 5;
                PlaySfx_80031494(0x7E);
                break;
            }
            t->f24_LOAD = 0;
            PlaySfx_80031494(0x7D);
        }
        else if (IsCancelPressed_8003D3C0(0, (t->f54_LOAD >> 6) & 1))
        {
            t->f24_LOAD = 0;
            PlaySfx_80031494(0x7D);
        }
        break;
    case 13:
        DrawMessageBox_800BACBC(dword_800BDF1C);
        if (padPressed_8009194C[(t->f54_LOAD >> 6) & 1])
        {
            t->f24_LOAD = 1;
        }
        break;
    case 14:
        DrawMessageBox_800BACBC(dword_800BDF2C);
        if (padPressed_8009194C[(t->f54_LOAD >> 6) & 1])
        {
            t->f24_LOAD = 1;
        }
        break;
    case 15:
        DrawMessageBox_800BACBC(dword_800BDF3C);
        if (padPressed_8009194C[(t->f54_LOAD >> 6) & 1])
        {
            t->f24_LOAD = 1;
        }
        break;
    }
    DrawButtonHelpBar_8002B004(dword_800BDEA4, 0, 1);
    DrawMenuBackground_8002BE10();
}

void sub_800B80F8(LoadTask_LOAD* t)
{
    short c[6];
    int r;
    if (t->f24_LOAD != -1)
    {
        switch (t->f24_LOAD)
        {
        case 0:
            break;
        case 1:
            ResetMenuRow_800BADE0(&stru_800BDF4C[3]);
            break;
        case 2:
            ResetMenuRow_800BADE0(&stru_800BDF4C[2]);
            break;
        case 3:
            break;
        case 4:
            ResetMenuRow_800BADE0(&stru_800BDF4C[4]);
            if (stru_800BDF4C[0].fC_LOAD == 0)
            {
                stru_800BDF4C[4].fC_LOAD = 1;
            }
            break;
        case 5:
            ResetMenuRow_800BADE0(&stru_800BDF4C[5]);
            break;
        }
        t->s30_LOAD = t->f24_LOAD;
        t->f24_LOAD = -1;
    }
    if (t->s30_LOAD >= 6)
    {
        return;
    }
    if (t->s30_LOAD >= 0)
    {
        c[4] = stru_800BDF4C[t->s30_LOAD].fC_LOAD;
        c[5] = stru_800BDF4C[t->s30_LOAD].fD_LOAD;
        c[0] = stru_800BDF4C[t->s30_LOAD].f6_LOAD;
        c[1] = stru_800BDF4C[t->s30_LOAD].f7_LOAD;
        c[2] = stru_800BDF4C[t->s30_LOAD].f8_LOAD;
        c[3] = stru_800BDF4C[t->s30_LOAD].fB_LOAD;
        r = UpdateMenuCursor_8003D794(c, (t->f54_LOAD >> 6) & 1);
        if (stru_800BDF4C[t->s30_LOAD].fC_LOAD != c[4] || r == 8 || r == 7)
        {
            PlaySfx_80031494(0x7F);
        }
        stru_800BDF4C[t->s30_LOAD].fC_LOAD = c[4];
        stru_800BDF4C[t->s30_LOAD].fD_LOAD = c[5];
    }
}
const Bytes8_LOAD dword_800B69F4 = { { 93, 0, 18, 0, 124, 0, 18 } };
const char byte_800B69FC[] = "\202e\202\217\202\222\202\215\202\201\202\224\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201H"; // Format MEMORY CARD?
const Bytes8_LOAD dword_800B6A24 = { { 16, 0, 70, 0, 32, 1, 34 } };
const char byte_800B6A2C[] = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201D"; // Select MEMORY CARD.
const char byte_800B6A54[4] = { 0 };
const char byte_800B6A58[] = "\202m\202\217\201@\202\205\202\215\202\220\202\224\202\231\201@\202\202\202\214\202\217\202\203\202\213\202\223\201@\202\206\202\217\202\222\201@\202\223\202\201\202\226\202\211\202\216\202\207\201@\202\216\202\205\202\227\201@\202\207\202\201\202\215\202\205\202\223\201D"; // No empty blocks for saving new games.
const char byte_800B6AA4[] = "\202e\202\201\202\211\202\214\202\205\202\204\201@\202\204\202\225\202\205\201@\202\224\202\217\201@\202\204\202\201\202\215\202\201\202\207\202\205\202\204\201@\202\204\202\201\202\224\202\201\201D"; // Failed due to damaged data.
const char byte_800B6ADC[] = "\202m\202\217\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201@\202\211\202\216\201@\202\223\202\214\202\217\202\224\201D"; // No MEMORY CARD in slot.
const char byte_800B6B0C[] = "\202b\202\210\202\205\202\203\202\213\202\211\202\216\202\207\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201D\201D\201D"; // Checking MEMORY CARD...
const Bytes8_LOAD dword_800B6B3C = { { 10, 0, 193, 0, 44, 1, 20 } };

void sub_800B82FC(LoadTask_LOAD* t)
{
    int i;
    Row8_LOAD* p;
    Bytes8_LOAD a;
    Tail4_LOAD b;
    if (t->s30_LOAD == 1)
    {
        for (i = 0; i < 2; i++)
        {
            dword_800BDBD4[i][0] = 2;
            if (i == stru_800BDF4C[1].fC_LOAD)
            {
                dword_800BDBD4[i][1] = GetTime30Hz_8002C64C();
            }
            else
            {
                dword_800BDBD4[i][1] = 0;
            }
        }
    }
    else
    {
        dword_800BDBD4[0][0] = 1;
        dword_800BDBD4[1][0] = 1;
    }
    DrawMenuWindows_8002A5A4(&dword_800BDB64);
    DrawMenuWindows_8002A5A4(&dword_800BDBBC);
    for (p = &dword_800BD998[2]; p->f4_LOAD >= 0; p++)
    {
        DrawUiTiySprt_8002C06C(p, p->f4_LOAD, p->f6_LOAD);
    }
    a = dword_800B69F4;
    b.c1_LOAD = 1;
    b.c0_LOAD = 0;
    b.s_LOAD = uiColor_8008B590;
    DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
}

void sub_800B847C(LoadTask_LOAD* t)
{
    int i;
    Row8_LOAD* p;
    Bytes8_LOAD a;
    Tail4_LOAD b;
    for (i = 0; i < 2; i++)
    {
        if (i == stru_800BDF4C[1].fC_LOAD)
        {
            *dword_800BDBD4[i] = 4;
        }
        else
        {
            *dword_800BDBD4[i] = 1;
        }
    }
    DrawMenuWindows_8002A5A4(&dword_800BDB64);
    DrawMenuWindows_8002A5A4(&dword_800BDBBC);
    for (p = &dword_800BD998[2]; p->f4_LOAD >= 0; p++)
    {
        DrawUiTiySprt_8002C06C(p, p->f4_LOAD, p->f6_LOAD);
    }
    a = dword_800B69F4;
    b.c1_LOAD = 1;
    b.c0_LOAD = 0;
    b.s_LOAD = uiColor_8008B590;
    DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
}

void sub_800B85AC(LoadTask_LOAD* t)
{
    Pos_LOAD p0;
    Pos_LOAD p1;
    Bytes8_LOAD a;
    Tail4_LOAD b;
    p0.x_LOAD = 0x13;
    p0.y_LOAD = 0x49;
    DrawText_8003E91C(2, byte_800B682C, &p0, 5);
    p1.x_LOAD = 0x13;
    p1.y_LOAD = 0x57;
    DrawText_8003E91C(2, byte_800B69FC, &p1, 5);
    a = dword_800B6A24;
    b.c1_LOAD = 1;
    b.c0_LOAD = 0;
    b.s_LOAD = uiColor_8008B590;
    DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
    DrawMenuWindows_8002A5A4(&dword_800BDD64);
}

void sub_800B867C(LoadTask_LOAD* t)
{
    Pair_LOAD q;
    short r0[4];
    short r1[6];
    sub_800B8BD4(t);
    r1[0] = stru_800BDF4C[t->s30_LOAD].f6_LOAD;
    r1[1] = stru_800BDF4C[t->s30_LOAD].f7_LOAD;
    r1[2] = stru_800BDF4C[t->s30_LOAD].f8_LOAD;
    r1[3] = stru_800BDF4C[t->s30_LOAD].fB_LOAD;
    r1[4] = stru_800BDF4C[t->s30_LOAD].fC_LOAD;
    r1[5] = stru_800BDF4C[t->s30_LOAD].fD_LOAD;
    q.a_LOAD = 2;
    q.b_LOAD = 1;
    r0[0] = 0x9A;
    r0[1] = 0x2C;
    r0[2] = 0x9A;
    r0[3] = 0xB7;
    DrawScrollArrows_8002B8DC(q, r1, r0, 1);
}

void sub_800B877C(LoadTask_LOAD* t)
{
    switch (t->s30_LOAD)
    {
    case 1:
    {
        Pos_LOAD p;
        p.x_LOAD = 0xE;
        p.y_LOAD = 0xC7;
        DrawText_8003E91C(2, byte_800B6A2C, &p, 5);
        break;
    }
    case 2:
    {
        Pos_LOAD p;
        p.x_LOAD = 0xE;
        p.y_LOAD = 0xC7;
        DrawText_8003E91C(2, byte_800B6A54, &p, 5);
        break;
    }
    case 3:
    {
        Pos_LOAD p;
        p.x_LOAD = 0xE;
        p.y_LOAD = 0xC7;
        DrawText_8003E91C(2, dword_800BDA08[stru_800BDF4C[0].fC_LOAD], &p, 5);
        break;
    }
    case 9:
    {
        Pos_LOAD p;
        p.x_LOAD = 0xE;
        p.y_LOAD = 0xC7;
        DrawText_8003E91C(2, byte_800B6A58, &p, 5);
        break;
    }
    case 10:
    {
        Pos_LOAD p;
        p.x_LOAD = 0xE;
        p.y_LOAD = 0xC7;
        DrawText_8003E91C(2, byte_800B6AA4, &p, 5);
        break;
    }
    case 6:
    {
        Pos_LOAD p;
        p.x_LOAD = 0xE;
        p.y_LOAD = 0xC7;
        DrawText_8003E91C(2, byte_800B6ADC, &p, 5);
        break;
    }
    case 18:
    {
        Pos_LOAD p;
        p.x_LOAD = 0xE;
        p.y_LOAD = 0xC7;
        DrawText_8003E91C(2, byte_800B6B0C, &p, 5);
        break;
    }
    case 11:
    {
        Pos_LOAD p;
        p.x_LOAD = 0xE;
        p.y_LOAD = 0xC7;
        DrawText_8003E91C(2, byte_800B682C, &p, 5);
        break;
    }
    }
    {
        Bytes8_LOAD a;
        Tail4_LOAD b;
        a = dword_800B6B3C;
        b.c1_LOAD = 1;
        b.c0_LOAD = 0;
        b.s_LOAD = uiColor_8008B590;
        DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
    }
}
const Bytes8_LOAD dword_800B6B8C = { { 63, 0, 18, 0, 108, 0, 18 } };
const Bytes8_LOAD dword_800B6B94 = { { 187, 0, 18, 0, 122, 0, 18 } };
const char byte_800B6B9C[] = "\201^"; // /
const Bytes8_LOAD dword_800B6BA0 = { { 10, 0, 33, 0, 44, 0, 14 } };
const char byte_800B6BA8[] = "\201E"; // ・
const char aJadeCocoonLevel_800B6BAC[] = "\202i\202\201\202\204\202\205\201@\202b\202\217\202\203\202\217\202\217\202\216\201^\202k\202\205\202\226\202\205\202\214\201@\202X\202X\201^\202k\202\201\202\224\202\205\202\223\202\224\201@\202f\202\201\202\215\202\205"; // Jade Cocoon/Level 99/Latest Game
const char name_800B6BF0[] = "\202b\202n\202q\202q\202h\202c\202n\202q"; // CORRIDOR
const char name_800B6C04[] = "\202d\202m\202c"; // END
const int dword_800B6C0C = 0;
const int dword_800B6C10 = 0;
const int dword_800B6C14 = 0;
const unsigned short name_800B6C18[12] = {
    0x6B82, 0x8182, 0x9482, 0x8582, 0x9382, 0x9482, 0x4081, 0x6682,
    0x8182, 0x8D82, 0x8582,
};
const unsigned short name_800B6C30[12] = {
    0x6482, 0x8E82, 0x8482, 0x4081, 0x8F82, 0x8682, 0x4081, 0x6682,
    0x8182, 0x8D82, 0x8582,
};
const char aCorridor_800B6C48[20] = "\202b\202\217\202\222\202\222\202\211\202\204\202\217\202\222\000\000\015";
const char asc_800B6C5C[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202P\202T";
const char asc_800B6C78[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202P\202S";
const char asc_800B6C94[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202P\202R";
const char asc_800B6CB0[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202P\202Q";
const char asc_800B6CCC[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202P\202P";
const char asc_800B6CE8[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202P\202O";
const char asc_800B6D04[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202X";
const char asc_800B6D20[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202W";
const char asc_800B6D3C[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202V";
const char asc_800B6D58[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202U";
const char asc_800B6D74[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202T";
const char asc_800B6D90[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202S";
const char asc_800B6DAC[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202R";
const char asc_800B6DC8[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202Q";
const char asc_800B6DE4[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202P";
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
const char asc_800B7274[] = "\203\201\203\202\203\212\201[\203J\201[\203h\202\252\202\240\202\350\202\334\202\271\202\361"; // メモリーカードがありません
const char asc_800B7290[] = "\203\201\203\202\203\212\201[\203J\201[\203h\215\267\215\236\214\373"; // メモリーカード差込口
const char asc_800B72A8[] = "\203\201\203\202\203\212\201[\203J\201[\203h\215\267\215\236\214\373\202P"; // メモリーカード差込口１
const char asc_800B72C0[] = "\203\201\203\202\203\212\201[\203J\201[\203h\215\267\215\236\214\373\202Q"; // メモリーカード差込口２
const char asc_800B72D8[] = "\203\201\203\202\203\212\201[\203J\201[\203h\202\360\203Z\203b\203g\202\265\202\304\202\255\202\276\202\263\202\242"; // メモリーカードをセットしてください
const char byte_800B72FC[4] = { 42 };
const Bytes5_LOAD dword_800B7300 = { "CRD0" };
const char asc_800B7308[] = "\203\201\203\202\203\212\201[\203J\201[\203h\202P"; // メモリーカード１
const MenuItems2_LOAD dword_800B731C = {
    {
        { 8, 3, (int)asc_800B7308, 0, 0, 40, 100, { 100, 0, 34, 0, 2, 0, 2 } },
        { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
    },
};
const char asc_800B7354[] = "\203\201\203\202\203\212\201[\203J\201[\203h\202Q"; // メモリーカード２
const MenuItems2_LOAD dword_800B7368 = {
    {
        { 8, 3, (int)asc_800B7354, 0, 0, 180, 100, { 100, 0, 34, 0, 2, 0, 2 } },
        { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
    },
};

void sub_800B8984(LoadTask_LOAD* t)
{
    Bytes8_LOAD a;
    Tail4_LOAD b;
    DrawUiTiySprt_8002C06C(&dword_800BD998[stru_800BDF4C[0].fC_LOAD], dword_800BD998[stru_800BDF4C[0].fC_LOAD].f4_LOAD, dword_800BD998[stru_800BDF4C[0].fC_LOAD].f6_LOAD);
    a = dword_800B6B8C;
    b.c1_LOAD = 1;
    b.c0_LOAD = 0;
    b.s_LOAD = uiColor_8008B590;
    DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
}

#if 0
// Not matched: only the order of the prologue stores differs ($ra/$s0 vs argument set-up)
void sub_800B8A20(LoadTask_LOAD* t)
{
    Pos_LOAD p0;
    Pos_LOAD p1;
    Bytes8_LOAD a;
    Tail4_LOAD b;
    p0.x_LOAD = 0xBF;
    p0.y_LOAD = 0x15;
    DrawUiTiySprt_8002C06C(&p0, 0x27, 1);
    p1.x_LOAD = 0x124;
    p1.y_LOAD = 0x15;
    DrawUiTiySprt_8002C06C(&p1, (byte_800BDF68 == 1) << 1, 1);
    a = dword_800B6B94;
    b.c1_LOAD = 1;
    b.c0_LOAD = 0;
    b.s_LOAD = uiColor_8008B590;
    DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800B8A20);

void sub_800B8AE4(LoadTask_LOAD* t)
{
    Pos_LOAD p0;
    Pos_LOAD p1;
    Pos_LOAD p2;
    Bytes8_LOAD a;
    Tail4_LOAD b;
    p0.x_LOAD = 0x1C;
    p0.y_LOAD = 0x24;
    DrawNumberRightAlignedFont1_8003F264(&p0, stru_800BDF4C[3].fD_LOAD + stru_800BDF4C[3].fC_LOAD + 1, 5);
    p1.x_LOAD = 0x1C;
    p1.y_LOAD = 0x24;
    DrawText_8003E91C(1, byte_800B6B9C, &p1, 5);
    p2.x_LOAD = 0x32;
    p2.y_LOAD = 0x24;
    DrawNumberRightAlignedFont1_8003F264(&p2, 0xF, 5);
    a = dword_800B6BA0;
    b.c1_LOAD = 1;
    b.c0_LOAD = 0;
    b.s_LOAD = uiColor_8008B590;
    DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
}

extern void AddDrawAreaPrim_8003326C(RECT* r, char* ot);
extern void AddClipDrawAreaPrim_80033308(char* ot);
extern void DrawSmallNumber3_8002C290(void* p, int n, int ot);
extern void DrawSmallNumber9_8002C414(void* p, int n, int ot);
extern void DrawSmallText_8002FAA0(int a0, void* pos, unsigned char* name, int a3);
// Matched
void sub_800B8BD4(LoadTask_LOAD* t)
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
    Row8_LOAD* r;
    Row8_LOAD* icon;
    for (i = -1; i < 5; i++)
    {
        n = stru_800BDF4C[3].fD_LOAD + i;
        if (!((n >= 0 && n < 15) || i == 0 || i == 1))
        {
            continue;
        }
        if (n >= t->f20_LOAD - 1)
        {
            p0.x_LOAD = 0x7D;
            p0.y_LOAD = i * 33 + 0x39;
            AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
            DrawUiTiySprt_8002C06C(&p0, 0x9C, 1);
            AddDrawAreaPrim_8003326C(&dword_800BDA10, dword_8008D454 + 4);
        }
        else if (!GetCardSaveName_800BAE4C(n))
        {
            p1.x_LOAD = 0x8B;
            p1.y_LOAD = i * 33 + 0x39;
            AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
            DrawUiTiySprt_8002C06C(&p1, 0x74, 1);
            AddDrawAreaPrim_8003326C(&dword_800BDA10, dword_8008D454 + 4);
        }
        else
        {
            for (j = 0; j < 9; j++)
            {
                if (j < 6)
                {
                    if (j == 5)
                    {
                        v = t->summaries_LOAD[n].vals_28[5];
                        k = 0;
                        do
                        {
                            v /= 10;
                            k++;
                        } while (v);
                        p2.x_LOAD = dword_800BD93C[j].x_LOAD + k * 7;
                        p2.y_LOAD = dword_800BD93C[j].y_LOAD + i * 33;
                        AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
                        DrawSmallNumber9_8002C414(&p2, t->summaries_LOAD[n].vals_28[j], 1);
                    }
                    else
                    {
                        p2.x_LOAD = dword_800BD93C[j].x_LOAD;
                        p2.y_LOAD = dword_800BD93C[j].y_LOAD + i * 33;
                        AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
                        DrawSmallNumber3_8002C290(&p2, t->summaries_LOAD[n].vals_28[j], 1);
                    }
                    if ((j == 3 || j == 4) && t->summaries_LOAD[n].vals_28[j] < 10)
                    {
                        p2.x_LOAD = dword_800BD93C[j].x_LOAD - 8;
                        p2.y_LOAD = dword_800BD93C[j].y_LOAD + i * 33;
                        DrawSmallNumber3_8002C290(&p2, 0, 1);
                    }
                    AddDrawAreaPrim_8003326C(&dword_800BDA10, dword_8008D454 + 4);
                }
                else if (j == 6)
                {
                    AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
                    p3.x_LOAD = dword_800BD93C[6].x_LOAD;
                    p3.y_LOAD = dword_800BD93C[6].y_LOAD + i * 33;
                    DrawSmallText_8002FAA0(0, &p3, t->summaries_LOAD[n].name_0, 1);
                    AddDrawAreaPrim_8003326C(&dword_800BDA10, dword_8008D454 + 4);
                }
                else if (j == 7)
                {
                    p3.x_LOAD = dword_800BD93C[j].x_LOAD;
                    p3.y_LOAD = dword_800BD93C[j].y_LOAD + i * 33;
                    AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
                    DrawText_8003E91C(1, t->summaries_LOAD[n].text_C, &p3, 1);
                    AddDrawAreaPrim_8003326C(&dword_800BDA10, dword_8008D454 + 4);
                    if (t->summaries_LOAD[n].f26 >= 0)
                    {
                        p3.x_LOAD = dword_800BD93C[j].x_LOAD + 0x38;
                        p3.y_LOAD = dword_800BD93C[j].y_LOAD + i * 33;
                        AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
                        DrawNumberRightAlignedFont1_8003F264(&p3, t->summaries_LOAD[n].f26, 1);
                        AddDrawAreaPrim_8003326C(&dword_800BDA10, dword_8008D454 + 4);
                    }
                }
                else if (j == 8)
                {
                    icon = &dword_800BD9E8[t->summaries_LOAD[n].icon_24];
                    p3.x_LOAD = icon->f0_LOAD;
                    p3.y_LOAD = icon->f2_LOAD + i * 33;
                    AddClipDrawAreaPrim_80033308(dword_8008D454 + icon->f6_LOAD * 4);
                    DrawUiTiySprt_8002C06C(&p3, icon->f4_LOAD, icon->f6_LOAD);
                    AddDrawAreaPrim_8003326C(&dword_800BDA10, dword_8008D454 + icon->f6_LOAD * 4);
                }
                for (r = dword_800BD960; r->f4_LOAD > 0; r++)
                {
                    p3.x_LOAD = r->f0_LOAD;
                    p3.y_LOAD = r->f2_LOAD + i * 33;
                    AddClipDrawAreaPrim_80033308(dword_8008D454 + r->f6_LOAD * 4);
                    DrawUiTiySprt_8002C06C(&p3, r->f4_LOAD, r->f6_LOAD);
                    AddDrawAreaPrim_8003326C(&dword_800BDA10, dword_8008D454 + r->f6_LOAD * 4);
                }
            }
            p2.x_LOAD = dword_800BD93C[1].x_LOAD;
            p2.y_LOAD = dword_800BD93C[1].y_LOAD + i * 33;
            AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
            DrawUiTiySprt_8002C06C(&p2, 0xDA, 1);
            AddDrawAreaPrim_8003326C(&dword_800BDA10, dword_8008D454 + 4);
            p4.x_LOAD = dword_800BD93C[3].x_LOAD + 2;
            p4.y_LOAD = (dword_800BD93C[3].y_LOAD - 4) + i * 33;
            AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
            DrawText_8003E91C(2, byte_800B6BA8, &p4, 1);
            AddDrawAreaPrim_8003326C(&dword_800BDA10, dword_8008D454 + 4);
            p5.x_LOAD = dword_800BD93C[3].x_LOAD + 2;
            p5.y_LOAD = dword_800BD93C[3].y_LOAD + i * 33;
            AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
            DrawText_8003E91C(2, byte_800B6BA8, &p5, 1);
            AddDrawAreaPrim_8003326C(&dword_800BDA10, dword_8008D454 + 4);
        }
    }
}

void sub_800B9220(LoadTask_LOAD* t)
{
    if (IsConfirmPressed_8003D288(1, (t->f54_LOAD >> 6) & 1))
    {
        switch (stru_800BDF4C[0].fC_LOAD)
        {
        case 0:
        case 1:
            t->f24_LOAD = 1;
            break;
        case 2:
            t->f28_LOAD = 5;
            break;
        case 3:
            t->f24_LOAD = 5;
            break;
        }
    }
    else if (IsCancelPressed_8003D3C0(1, (t->f54_LOAD >> 6) & 1))
    {
        t->f28_LOAD = 5;
    }
}

#if 0
// Not matched: only a dead byte load (lbu $v1) of the options struct in the prologue is missing
void sub_800B92C0(LoadTask_LOAD* t)
{
    if (IsConfirmPressed_8003D288(0, (t->f54_LOAD >> 6) & 1))
    {
        PlaySfx_80031494(0x7E);
        WaitCardSync_800BADF4();
        t->f24_LOAD = 0x12;
    }
    else if (IsCancelPressed_8003D3C0(1, (t->f54_LOAD >> 6) & 1))
    {
        if (t->f54_LOAD & 0x24)
        {
            t->f28_LOAD = 5;
        }
        else
        {
            t->f24_LOAD = 0;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800B92C0);

void sub_800B9360(LoadTask_LOAD* t)
{
    switch (PollCardAccept_800BAE68(stru_800BDF4C[1].fC_LOAD))
    {
    case 0:
    case 3:
        ScanCardSaves_800BAFB0(stru_800BDF4C[1].fC_LOAD);
        PlaySfx_80031494(0x7E);
        if (stru_800BDF4C[0].fC_LOAD == 0)
        {
            if (GetCardFreeBlocks_800BAE2C() || GetCardSaveCount_800BAE3C())
            {
                t->f20_LOAD = 0;
                t->f24_LOAD = 3;
            }
            else
            {
                t->f24_LOAD = 7;
            }
        }
        else if (GetCardSaveCount_800BAE3C())
        {
            t->f20_LOAD = 0;
            t->f24_LOAD = 3;
        }
        else
        {
            t->f24_LOAD = 8;
        }
        break;
    case 4:
        if (stru_800BDF4C[0].fC_LOAD == 0)
        {
            t->f24_LOAD = 2;
        }
        else
        {
            t->f24_LOAD = 0xB;
        }
        break;
    case -1:
        break;
    default:
        t->f24_LOAD = 6;
        break;
    }
}

void sub_800B9470(LoadTask_LOAD* t)
{
    int r = PollCardAccept_800BAE68(stru_800BDF4C[1].fC_LOAD);
    if (r < -1 || (r > 0 && r != 4))
    {
        t->f24_LOAD = 1;
    }
    if (IsCancelPressed_8003D3C0(1, (t->f54_LOAD >> 6) & 1))
    {
        t->f24_LOAD = 1;
    }
    if (IsConfirmPressed_8003D288(1, (t->f54_LOAD >> 6) & 1))
    {
        if (stru_800BDF4C[2].fC_LOAD == 0)
        {
            t->f28_LOAD = 4;
        }
        if (stru_800BDF4C[2].fC_LOAD == 1)
        {
            t->f24_LOAD = 1;
        }
    }
}

void sub_800B952C(LoadTask_LOAD* t)
{
    int n = stru_800BDF4C[3].fD_LOAD + stru_800BDF4C[3].fC_LOAD;
    if (IsCancelPressed_8003D3C0(1, (t->f54_LOAD >> 6) & 1))
    {
        t->f24_LOAD = 1;
    }
    if (IsConfirmPressed_8003D288(0, (t->f54_LOAD >> 6) & 1))
    {
        if (stru_800BDF4C[0].fC_LOAD == 1)
        {
            if (n < t->f20_LOAD - 1)
            {
                if (GetCardSaveName_800BAE4C(n))
                {
                    t->f24_LOAD = 4;
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
        else if (stru_800BDF4C[0].fC_LOAD == 0)
        {
            if (n < t->f20_LOAD - 1)
            {
                if (!GetCardSaveName_800BAE4C(n) && GetCardFreeBlocks_800BAE2C() <= 0)
                {
                    t->f24_LOAD = 9;
                    PlaySfx_80031494(0x7C);
                }
                else
                {
                    t->f24_LOAD = 4;
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

void sub_800B9654(LoadTask_LOAD* t)
{
    if (IsCancelPressed_8003D3C0(1, (t->f54_LOAD >> 6) & 1))
    {
        t->f24_LOAD = 3;
    }
    if (IsConfirmPressed_8003D288(0, (t->f54_LOAD >> 6) & 1))
    {
        if (stru_800BDF4C[4].fC_LOAD == 0)
        {
            PlaySfx_80031494(0x7E);
            if (stru_800BDF4C[0].fC_LOAD == 1)
            {
                WaitCardSync_800BADF4();
                t->f28_LOAD = 3;
            }
            else if (stru_800BDF4C[0].fC_LOAD == 0)
            {
                WaitCardSync_800BADF4();
                t->f28_LOAD = 2;
            }
        }
        else
        {
            PlaySfx_80031494(0x7D);
            t->f24_LOAD = 3;
        }
    }
}

int ReadSaveSummaries_800B9724(LoadTask_LOAD* t)
{
    int ret = 1;
    int cmd = 0;
    int res = 0;
    int chan = stru_800BDF4C[1].fC_LOAD << 4;
    char* name;
    switch (MemCardSync(1, &cmd, &res))
    {
    case 0:
        break;
    case -1:
        if (t->f20_LOAD < 15)
        {
            name = GetCardSaveName_800BAE4C(t->f20_LOAD);
            if (name)
            {
                MemCardReadFile(chan, name, &t->summaries_LOAD[t->f20_LOAD], 0x280, 0x80);
            }
            else if (t->f20_LOAD == 14)
            {
                t->f20_LOAD = 15;
            }
            t->f20_LOAD++;
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
                if (t->f20_LOAD == 15)
                {
                    t->f20_LOAD = 16;
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
void WriteSaveTask_800B98C4(Task_LOAD* t, LoadTask_LOAD* s)
{
    int cmd = 0;
    int res = 0;
    int chan = stru_800BDF4C[1].fC_LOAD << 4;
    int n = stru_800BDF4C[3].fD_LOAD + stru_800BDF4C[3].fC_LOAD;
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
        MemCardWriteFile(chan, name, s->fileBuf_LOAD, 0, sizeof(SaveFile_LOAD));
        break;
    case 1:
        if (cmd == 4)
        {
            switch (res)
            {
            case 0:
                t->next_8 = LoadMenuTask_800B794C;
                s->f28_LOAD = 0;
                s->f24_LOAD = 3;
                PlaySfx_80031494(0x7E);
                MemCopy_800403E8(&s->summaries_LOAD[n], &s->fileBuf_LOAD->summary_280, 0x80);
                ScanCardSaves_800BAFB0(stru_800BDF4C[1].fC_LOAD);
                break;
            case 1:
            case 2:
            case 3:
            case 5:
                t->next_8 = LoadMenuTask_800B794C;
                s->f28_LOAD = 0;
                s->f24_LOAD = 0xE;
                break;
            }
        }
        break;
    }
    DrawLoadingIcon_8003CD5C();
    DrawMessageBox_800BACBC(dword_800BDEEC);
    DrawMenuBackground_8002BE10();
}
#endif
INCLUDE_OVERLAY_ASM(load, WriteSaveTask_800B98C4);

// the title of the save file being written (Shift-JIS "<name>/Level 99/<place>", name_800BDFAC)
extern unsigned short name_800B6C48[]; // "Corridor"
extern void* memcpy(void* dst, const void* src, unsigned int n);
extern void BuildCardHeader_800BB2AC(CardHeader_LOAD* h, int idx, char* title);
extern void IntToText_8003F610(unsigned short* buf, int val);
extern int PlayTimeHours_800BAC14(int n);
extern int PlayTimeMinutes_800BAC68(int n);

// packs saveData_8008B570 into the save file to write, with its summary and title
// Matched
void sub_800B9A8C(LoadTask_LOAD* s)
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

    sm = &s->fileBuf_LOAD->summary_280;
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
        MemCopy_800403E8(sm->text_C, name_800B6BF0, 0x18);
    }
    else if (sm->icon_24 == 1)
    {
        MemCopy_800403E8(sm->text_C, name_800B6C04, 0x18);
    }
    else
    {
        MemCopy_800403E8(sm->text_C, s->place_58_LOAD, 0x18);
    }
    body = &s->fileBuf_LOAD->body_300;
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
        sm->sum_40 += ((unsigned char*)s->fileBuf_LOAD)[n];
    }
    sm2 = &s->fileBuf_LOAD->summary_280;
    idx = stru_800BDF4C[3].fD_LOAD + stru_800BDF4C[3].fC_LOAD;
    IntToText_8003F610(buf, sm2->vals_28[0]);
    lv = sm2->vals_28[0];
    t = name_800BDFAC;
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
        memcpy(name_800BDFAC->f.place_2A, name_800B6C18, 23);
        break;
    case 1:
        memcpy(name_800BDFAC->f.place_2A, name_800B6C30, 23);
        break;
    case 2:
    default:
        memcpy(name_800BDFAC->f.place_2A, name_800B6C48, 17);
        break;
    }
    BuildCardHeader_800BB2AC(&s->fileBuf_LOAD->header_0, idx, name_800BDFAC->str);
}

#if 0
// Not matched: prologue scheduling only: the original sets $a0 = 1 before saving $s1 / copying the second argument
void LoadSaveTask_800BA234(Task_LOAD* t, LoadTask_LOAD* s)
{
    int cmd = 0;
    int res = 0;
    int chan = stru_800BDF4C[1].fC_LOAD << 4;
    int n = stru_800BDF4C[3].fD_LOAD + stru_800BDF4C[3].fC_LOAD;
    char* name;
    switch (MemCardSync(1, &cmd, &res))
    {
    case 0:
        break;
    case -1:
        name = GetCardSaveName_800BAE4C(n);
        if (name)
        {
            MemCardReadFile(chan, name, s->fileBuf_LOAD, 0, sizeof(SaveFile_LOAD));
        }
        else
        {
            t->next_8 = LoadMenuTask_800B794C;
            s->f28_LOAD = 0;
            s->f24_LOAD = 0xF;
        }
        break;
    case 1:
        if (cmd == 3)
        {
            switch (res)
            {
            case 0:
                if (sub_800BA3EC(s))
                {
                    s->f8_LOAD = 1;
                    t->next_8 = LoadMenuTask_800B794C;
                    s->f28_LOAD = 6;
                    s->f54_LOAD |= 1;
                }
                else
                {
                    t->next_8 = LoadMenuTask_800B794C;
                    s->f28_LOAD = 0;
                    s->f24_LOAD = 0xA;
                }
                PlaySfx_80031494(0x7E);
                break;
            case 1:
            case 2:
            case 3:
            case 5:
                t->next_8 = LoadMenuTask_800B794C;
                s->f28_LOAD = 0;
                s->f24_LOAD = 0xF;
                break;
            }
        }
        break;
    }
    DrawLoadingIcon_8003CD5C();
    DrawMessageBox_800BACBC(dword_800BDEDC);
    DrawMenuBackground_8002BE10();
}
#endif
INCLUDE_OVERLAY_ASM(load, LoadSaveTask_800BA234);

// unpacks the loaded save file into saveData_8008B570; 0 when the checksum or the version is wrong
// Matched
int sub_800BA3EC(LoadTask_LOAD* s)
{
    int ret = 0;
    int sum = ret;
    unsigned int n;
    int i;
    int j;
    int k;
    int l;
    struct UiColorBytes col = saveData_8008B570.uiColor_20.w;
    SaveSummary_LOAD* sm = &s->fileBuf_LOAD->summary_280;
    Settings set = saveData_8008B570.settings_1C;
    SaveBody_LOAD* body;
    Minion* m;
    SaveMinion_LOAD* pm;
    UnitStats* u;
    SaveStats_LOAD* pu;

    for (n = 0x300; n < 0x1FC0; n++)
    {
        sum += ((unsigned char*)s->fileBuf_LOAD)[n];
    }
    if (sum == sm->sum_40 && s->fileBuf_LOAD->body_300.version_984 == 5)
    {
        body = &s->fileBuf_LOAD->body_300;
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
        if (s->f54_LOAD & 8)
        {
            saveData_8008B570.settings_1C = set;
            saveData_8008B570.uiColor_20.w = col;
        }
        ret = 1;
    }
    return ret;
}

void sub_800BA968(Task_LOAD* t)
{
    DrawLoadingIcon_8003CD5C();
    DrawMessageBox_800BACBC(dword_800BDECC);
    DrawMenuBackground_8002BE10();
    t->next_8 = sub_800BA9AC;
}

void sub_800BA9AC(Task_LOAD* t)
{
    DrawLoadingIcon_8003CD5C();
    DrawMessageBox_800BACBC(dword_800BDECC);
    DrawMenuBackground_8002BE10();
    t->next_8 = FormatCardTask_800BA9F0;
}

void FormatCardTask_800BA9F0(Task_LOAD* t, LoadTask_LOAD* s)
{
    switch (MemCardFormat(stru_800BDF4C[1].fC_LOAD << 4))
    {
    case 0:
        t->next_8 = LoadMenuTask_800B794C;
        s->f28_LOAD = 0;
        s->f24_LOAD = 3;
        s->f20_LOAD = 0;
        ScanCardSaves_800BAFB0(stru_800BDF4C[1].fC_LOAD);
        s->f5C_LOAD = 0;
        break;
    case 1:
        t->next_8 = LoadMenuTask_800B794C;
        s->f28_LOAD = 0;
        s->f24_LOAD = 1;
        break;
    case 2:
        t->next_8 = LoadMenuTask_800B794C;
        s->f28_LOAD = 0;
        s->f24_LOAD = 0xD;
        break;
    case -1:
        break;
    }
    WaitCardSync_800BADF4();
    DrawLoadingIcon_8003CD5C();
    DrawMessageBox_800BACBC(dword_800BDECC);
    DrawMenuBackground_8002BE10();
}

void LoadMenuExit_800BAAE0(Task_LOAD* t, LoadTask_LOAD* s)
{
    free3_8003FC6C(s->summaries_LOAD);
    free3_8003FC6C(s->fileBuf_LOAD);
    loadMenuActive_800BE184 = 0;
    t->flags_0 = (t->flags_0 & ~1) | 0x8000;
    MemCardStop();
    t->next_8 = sub_800B7650;
    if (!(s->f54_LOAD & 8))
    {
        FreeActiveOverlay_8002C014();
        if (s->f54_LOAD & 0x20)
        {
            RequestAreaReload_80027314();
            sub_800A6D30(sub_800A6D50(1));
        }
        else if (!(s->f54_LOAD & 4))
        {
            RequestAreaReload_80027314();
            sub_800A6D30(sub_800A6D50(1));
        }
        if (s->f54_LOAD & 1)
        {
            SaveData* m = &saveData_8008B570;
            m->field_2E2 = -1;
            m->mapId_2E4[0].field_2 = -1;
            m->mapId_2E4[1].field_2 = -1;
            m->mapId_2E4[2].field_2 = -1;
            m->mapId_2E4[3].field_2 = -1;
            dword_80091C54 = 0;
            if (!(s->f54_LOAD & 4))
            {
                unknownFlags_8008D678 |= 0x18000000;
            }
        }
        if (s->f54_LOAD & 0x10)
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
    r.x_LOAD = (0x13A - sz.w_LOAD) / 2;
    r.y_LOAD = (0xEA - sz.h_LOAD) / 2;
    r.w_LOAD = sz.w_LOAD + 6;
    r.h_LOAD = sz.h_LOAD + 3;
    if (sz.h_LOAD >= 0x10)
    {
        r.h_LOAD = sz.h_LOAD + 6;
    }
    for (i = 0; i < 3; i++)
    {
        if (lines[i])
        {
            Pos_LOAD p;
            p.x_LOAD = r.x_LOAD + 3;
            p.y_LOAD = r.y_LOAD + 5 + i * 13;
            DrawText_8003E91C(2, lines[i], &p, 5);
        }
    }
    {
        Tail4_LOAD b;
        b.c1_LOAD = 1;
        b.c0_LOAD = 0;
        b.s_LOAD = uiColor_8008B590;
        DrawWindow_80042460(&r, &b, dword_8008D454 + 0x38, 0);
    }
}

void ResetMenuRow_800BADE0(Row16_LOAD* p)
{
    p->fC_LOAD = p->f9_LOAD;
    p->fD_LOAD = p->fA_LOAD;
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

int PollCardAccept_800BAE68(int a)
{
    int x[2];
    int ret = -1;
    int r;
    int off = a << 4;
    x[0] = 0;
    x[1] = 0;
    r = MemCardSync(1, &x[0], &x[1]);
    switch (r)
    {
    case 0:
        break;
    case -1:
        MemCardAccept(off);
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

int PollCardExist_800BAF0C(int a)
{
    int x[2];
    int ret = -1;
    int r;
    int off = a << 4;
    x[0] = 0;
    x[1] = 0;
    r = MemCardSync(1, &x[0], &x[1]);
    switch (r)
    {
    case 0:
        break;
    case -1:
        MemCardExist(off);
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
    MemCardGetDirentry(slot << 4, byte_800B72FC, dir, &files, 0, 15);
    for (i = found; i < files; i++)
    {
        int q = dir[i].size_LOAD / 0x2000;
        if (dir[i].size_LOAD & 0x1FFF)
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
    MemCardGetDirentry(slot << 4, byte_800B72FC, dir, &files, 0, 15);
    for (i = found; i < files; i++)
    {
        int q = dir[i].size_LOAD / 0x2000;
        if (dir[i].size_LOAD & 0x1FFF)
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

int FindDirEntry_800BB23C(int n, unsigned char* a, unsigned char* b)
{
    int i;
    int j;
    int diff;
    int res = 0;
    for (i = 0; i < n; i++, b += 0x28)
    {
        diff = 0;
        for (j = 0; j < 0x15; j++)
        {
            if (a[j] == 0)
            {
                break;
            }
            if (a[j] != b[j])
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
        PolyFT4_LOAD* p = &publicTiyPolyFT4s_8008D430[dword_800BE0A0[i].poly_LOAD];
        int tp = p->tpage_LOAD & 0x1F;
        r.x = (p->u0_LOAD >> 2) + ((tp << 6) & 0x3FF);
        r.y = p->v0_LOAD + ((tp / 16) << 8);
        r.w = 4;
        r.h = 0x10;
        StoreImage(&r, (u_long*)h->icon_LOAD[i]);
        DrawSync(0);
        r.x = dword_800BE0A0[i].clutX_LOAD;
        r.y = dword_800BE0A0[i].clutY_LOAD;
        r.w = 0x10;
        r.h = 1;
        StoreImage(&r, (u_long*)h->clut_LOAD);
        DrawSync(0);
    }
    h->magic_LOAD[0] = 'S';
    h->magic_LOAD[1] = 'C';
    h->type_LOAD = 0x13;
    h->blocks_LOAD = 1;
    {
        char* t = h->title_LOAD;
        for (j = 63; j >= 0; j--)
        {
            t[j] = 0;
        }
    }
    if (title)
    {
        strcpy_8004E2D8(h->title_LOAD, title);
    }
    else
    {
        strcpy_8004E2D8(h->title_LOAD, dword_800BDFB0[idx]);
    }
    for (i = 11; i >= 0; i--)
    {
        h->f44_LOAD[i] = 0;
    }
    h->f50_LOAD = 1;
    h->f52_LOAD = dword_800B7300;
    h->f52_LOAD.c_LOAD[4] = 0;
    h->f57_LOAD = 0;
    h->f5C_LOAD = 0;
    MemCopy_800403E8(h->f200_LOAD, dword_800BE0B8, 0x80);
}
#endif
INCLUDE_OVERLAY_ASM(load, BuildCardHeader_800BB2AC);

void sub_800BB4A8(short sel)
{
    MenuItems2_LOAD a = dword_800B731C;
    MenuItems2_LOAD b = dword_800B7368;
    MenuItem_LOAD* list[3];
    MenuWin_LOAD w;
    int i;
    list[0] = a.item_LOAD;
    list[1] = b.item_LOAD;
    list[2] = 0;
    w.f0_LOAD = 2;
    w.f4_LOAD = 0;
    w.f8_LOAD = 8;
    w.fC_LOAD = 0;
    w.items_LOAD = list;
    w.f14_LOAD = 0;
    for (i = 0; i < 2; i++)
    {
        list[i]->flags_LOAD |= 2;
    }
    w.f4_LOAD = frameCount_8008D3FC;
    w.fC_LOAD = sel;
    DrawMenuWindows_8002A5A4(&w);
}

// 0x800BB5DC..0x800BD93C: PSY-Q 4.4 LIBMCRD.LIB modules LIBMCRD, USERFUNC and BIOS, linked from the library
// (config/ovl_lib_objs.txt), as are their .rdata, .data and .bss.

Pos_LOAD dword_800BD93C[9] = {
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
Row8_LOAD dword_800BD960[7] = {
    { 13, 52, 119, 1 },
    { 104, 52, 227, 1 },
    { 100, 66, 118, 1 },
    { 180, 65, 203, 1 },
    { 180, 52, 122, 1 },
    { 13, 66, 150, 1 },
    { -1, -1, -1, -1 },
};
Row8_LOAD dword_800BD998[2] = {
    { 80, 21, 190, 1 },
    { 69, 21, 197, 1 },
};
int dword_800BD9A8[16] = {
    0x15006C, 0x10027, 0x5F0027, 0x10027, 0x6D003B, 0x100B2, 0x6D006A, 0x10000,
    0x5F00BC, 0x10027, 0x6D00D0, 0x100B2, 0x6D00FF, 0x10002, -1, -1,
};
Row8_LOAD dword_800BD9E8[4] = {
    { 0x110, 52, 78, 1 },
    { 0x110, 52, 52, 1 },
    { 0x110, 52, 58, 1 },
    { -1, -1, -1, -1 },
};
char *dword_800BDA08[2] = { aSelectSaveLocat_800B66F0, aSelectGameToLoa_800B66C4 };
RECT dword_800BDA10 = { 10, 49, 0x12C, 129 };
MenuItem_LOAD dword_800BDA18[2] = {
    { 64, 0, 0, 0, 0, 10, 49, { 44, 1, 31 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD dword_800BDA50[2] = {
    { 64, 0, 0, 0, 0, 10, 82, { 44, 1, 31 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD dword_800BDA88[2] = {
    { 64, 0, 0, 0, 0, 10, 115, { 44, 1, 31 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD dword_800BDAC0[2] = {
    { 64, 0, 0, 0, 0, 10, 148, { 44, 1, 31 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD *dword_800BDAF8[5] = { dword_800BDA18, dword_800BDA50, dword_800BDA88, dword_800BDAC0 };
MenuWin_LOAD dword_800BDB0C = { 2, 0, 8, 0, dword_800BDAF8, 5 };
int dword_800BDB24[14] = {
    64, 0, 0, 0, 0x5A0021, 0x240069, 0, 1,
    0, 0, 0, -1, -1, -1,
};
void *dword_800BDB5C[2] = { (void *)dword_800BDB24 };
int dword_800BDB64 = 2;
int dword_800BDB68[5] = { 0, 8, 0, (int)dword_800BDB5C, 5 };
int dword_800BDB7C[14] = {
    64, 0, 0, 0, 0x5A00B6, 0x240069, 0, 1,
    0, 0, 0, -1, -1, -1,
};
void *dword_800BDBB4[2] = { (void *)dword_800BDB7C };
int dword_800BDBBC = 2;
int dword_800BDBC0[5] = { 0, 8, 0, (int)dword_800BDBB4, 5 };
int *dword_800BDBD4[2] = { &dword_800BDB64, &dword_800BDBBC };
MenuItem_LOAD dword_800BDBDC[2] = {
    { 8, 1, 190, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 106, 69, { 108, 0, 19, 0, 0, 0, 4 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD dword_800BDC14[2] = {
    { 8, 1, 197, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 106, 90, { 108, 0, 19, 0, 0, 0, 4 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD dword_800BDC4C[2] = {
    { 8, 1, 198, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 106, 111, { 108, 0, 19, 0, 0, 0, 4 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD dword_800BDC84[2] = {
    { 8, 1, 196, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 106, 132, { 108, 0, 19, 0, 0, 0, 4 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD *dword_800BDCBC[5] = { dword_800BDBDC, dword_800BDC14, dword_800BDC4C, dword_800BDC84 };
MenuWin_LOAD dword_800BDCD0 = { 2, 0, 8, 0, dword_800BDCBC, 5 };
MenuItem_LOAD dword_800BDCE8[2] = {
    { 8, 3, (int)aYES_800B671C, 0, 0, 126, 106, { 56, 0, 18, 0, 2, 0, 2 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD dword_800BDD20[2] = {
    { 8, 3, (int)aNO_800B6724, 0, 0, 126, 126, { 56, 0, 18, 0, 2, 0, 2 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD *dword_800BDD58[3] = { dword_800BDCE8, dword_800BDD20 };
MenuWin_LOAD dword_800BDD64 = { 2, 0, 8, 1, dword_800BDD58 };
MenuItem_LOAD dword_800BDD7C[2] = {
    { 8, 3, (int)aYES_800B671C, 0, 0, 215, 193, { 46, 0, 19, 0, 2, 0, 2 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD dword_800BDDB4[2] = {
    { 8, 3, (int)aNO_800B6724, 0, 0, 0x105, 193, { 48, 0, 19, 0, 2, 0, 2 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD *dword_800BDDEC[3] = { dword_800BDD7C, dword_800BDDB4 };
MenuWin_LOAD dword_800BDDF8 = { 2, 0, 8, 1, dword_800BDDEC };
MenuItem_LOAD dword_800BDE10[2] = {
    { 8, 3, (int)aYES_800B671C, 0, 0, 106, 121, { 52, 0, 19, 0, 2, 0, 2 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD dword_800BDE48[2] = {
    { 8, 3, (int)aNO_800B6724, 0, 0, 163, 121, { 52, 0, 19, 0, 2, 0, 2 } },
    { 1, 0, 0, 0, 0, -1, -1, { 255, 255, 255, 255, 255, 255, 255, 255 } },
};
MenuItem_LOAD *dword_800BDE80[3] = { dword_800BDE10, dword_800BDE48 };
MenuWin_LOAD dword_800BDE8C = { 2, 0, 8, 1, dword_800BDE80 };
char dword_800BDEA4[24] = { 16, 0, 0, 0, 56, 103, 11, 128, 167, 0, 0, 0, 44, 103, 11, 128, 255, 255, 255, 255 };
char *dword_800BDEBC[4] = { aMEMORYCARDFull_800B6748 };
char *dword_800BDECC[4] = { aFormattingMEMOR_800B67A4, aDoNotRemoveMEMO_800B676C };
char *dword_800BDEDC[4] = { aLoading_800B67D8, aDoNotRemoveMEMO_800B676C };
char *dword_800BDEEC[4] = { aSaving_800B67F0, aDoNotRemoveMEMO_800B676C };
char *dword_800BDEFC[8] = { aNoSaveGameData_800B6804, 0, 0, 0, byte_800B682C };
char *dword_800BDF1C[4] = { aFormattingFaile_800B6864 };
char *dword_800BDF2C[4] = { aSaveFailed_800B688C };
char *dword_800BDF3C[4] = { aLoadFailed_800B68A8 };
Row16_LOAD stru_800BDF4C[2] = {
    { { 68, 0, 116, 0, 0, 14 }, 1, 4, 4 },
    { { 68, 0, 116, 0, 0, 14 }, 2, 1, 2 },
};
int dword_800BDF6C[4] = { 0x480012, 0x2010E00, 0x102 };
int dword_800BDF7C[4] = { 0x40000A, 0x4012100, 0x4000000F };
int dword_800BDF8C[4] = { 0x40000A, 0x1022100, 0x1000002 };
int dword_800BDF9C[4] = { 0x40000A, 0x1022100, 0x102 };
SaveTitle_LOAD *name_800BDFAC = (void *)aJadeCocoonLevel_800B6BAC;
char *dword_800BDFB0[30] = {
    aJadeCocoon01_800B6F88, aJadeCocoon02_800B6F6C, aJadeCocoon03_800B6F50, aJadeCocoon04_800B6F34,
    aJadeCocoon05_800B6F18, aJadeCocoon06_800B6EFC, aJadeCocoon07_800B6EE0, aJadeCocoon08_800B6EC4,
    aJadeCocoon09_800B6EA8, aJadeCocoon10_800B6E8C, aJadeCocoon11_800B6E70, aJadeCocoon12_800B6E54,
    aJadeCocoon13_800B6E38, aJadeCocoon14_800B6E1C, aJadeCocoon15_800B6E00, asc_800B6DE4,
    asc_800B6DC8, asc_800B6DAC, asc_800B6D90, asc_800B6D74,
    asc_800B6D58, asc_800B6D3C, asc_800B6D20, asc_800B6D04,
    asc_800B6CE8, asc_800B6CCC, asc_800B6CB0, asc_800B6C94,
    asc_800B6C78, asc_800B6C5C,
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
IconSrc_LOAD dword_800BE0A0[3] = {
    { 75, 0x380, 254 },
    { 76, 0x3F0, 0x143 },
    { 77, 0x380, 252 },
};
char dword_800BE0B8[148] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 28, 0, 0, 62, 126, 0, 0, 119, 227, 0, 0, 227, 193, 0, 0, 192, 1, 0, 0, 255, 255, 0, 192, 243, 239, 3, 224, 224, 3, 7, 48, 195, 1, 14, 152, 199, 113, 28, 220, 207, 252, 24, 204, 204, 252, 25, 206, 204, 254, 57, 206, 207, 182, 59, 142, 199, 54, 59, 142, 199, 182, 59, 206, 207, 252, 57, 206, 204, 248, 16, 206, 204, 48, 0, 196, 15, 56, 63, 128, 7, 156, 63, 0, 3, 206, 1, 192, 15, 230, 0, 224, 31, 126, 0, 112, 59, 60, 0, 48, 51, 24, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 116, 114, 11, 128, 144, 114, 11, 128, 168, 114, 11, 128, 192, 114, 11, 128, 216, 114, 11, 128 };
int cardFreeBlocks_800BE14C = 0;
int cardSaveCount_800BE150 = 0;

int loadMenuActive_800BE184 BSS = 0;
char *cardSaveNames_800BE188[15] BSS = { 0 };
