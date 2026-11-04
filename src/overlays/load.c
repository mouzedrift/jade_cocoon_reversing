// LOAD.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

extern int loadMenuActive_800BE184;
extern int cardFreeBlocks_800BE14C;
extern int cardSaveCount_800BE150;
extern int dword_800BE174;
extern int (*dword_800BE294[])();
extern char* cardSaveNames_800BE188[];
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
extern char* dword_800BDECC[];
extern char* dword_800BDEDC[];
extern char* dword_800BDEEC[];
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
extern char byte_800B6A2C[];
extern char byte_800B6A54[];
extern char byte_800B6A58[];
extern char byte_800B6AA4[];
extern char byte_800B6ADC[];
extern char byte_800B6B0C[];
extern char* dword_800BDA08[];
extern int UpdateMenuCursor_8003D794(short* cursor, int b);

typedef struct
{
    char c_LOAD[5];
} Bytes5_LOAD;
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
    int poly_LOAD;
    short clutX_LOAD;
    short clutY_LOAD;
} IconSrc_LOAD;
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
extern IconSrc_LOAD dword_800BE0A0[];
extern Bytes5_LOAD dword_800B7300;
extern char* dword_800BDFB0[];
extern char dword_800BE0B8[];
extern char* strcpy_8004E2D8(char* dst, char* src); // PSY-Q strcpy (not in symbol_addrs.txt)
typedef struct
{
    unsigned short flags_LOAD;
    short pad2_LOAD;
    int f4_LOAD;
    int f8_LOAD;
    int fC_LOAD;
    short x_LOAD;
    short y_LOAD;
    char pad14_LOAD[8];
} MenuItem_LOAD;
typedef struct
{
    MenuItem_LOAD item_LOAD[2];
} MenuItems2_LOAD;
typedef struct
{
    int f0_LOAD;
    int f4_LOAD;
    int f8_LOAD;
    int fC_LOAD;
    MenuItem_LOAD** items_LOAD;
    int f14_LOAD;
} MenuWin_LOAD;
extern MenuItems2_LOAD dword_800B731C;
extern MenuItems2_LOAD dword_800B7368;
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
extern char byte_800B72FC[];
extern char* saveFileNames_800BE028[2][15];
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
extern char byte_800B6B9C[];
extern void sub_8003F264(void* p, int a, int b);
extern char byte_800B69FC[];
extern MenuWin_LOAD dword_800BDD64;
extern void DrawMenuWindows_8002A5A4(void* p);
typedef struct
{
    short x_LOAD;
    short y_LOAD;
} Pos_LOAD;
extern unsigned char byte_800BDF68;
extern void _clr_card_event(void);
extern int _get_card_event_x(void);
typedef struct
{
    char c_LOAD[8];
} Bytes8_LOAD;
typedef struct
{
    short s_LOAD;
    char c0_LOAD;
    char c1_LOAD;
} Tail4_LOAD;
typedef struct
{
    short f0_LOAD;
    short f2_LOAD;
    short f4_LOAD;
    short f6_LOAD;
} Row8_LOAD;
extern Row8_LOAD dword_800BD998[];
extern Bytes8_LOAD dword_800B6B8C;
extern Bytes8_LOAD dword_800B6A24;
extern Bytes8_LOAD dword_800B6B3C;
extern Bytes8_LOAD dword_800B69F4;
extern int dword_800BDB64;
extern int dword_800BDBBC;
extern int* dword_800BDBD4[];
extern Bytes8_LOAD dword_800B6BA0;
extern Bytes8_LOAD dword_800B6B94;
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
    char pad40[0x40];
} SaveSummary_LOAD;
typedef struct
{
    SaveSummary_LOAD* summaries_LOAD; // one per save (15)
    char* fileBuf_LOAD;   // one save file (0x2180 bytes)
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
    int f58_LOAD;
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
typedef struct
{
    unsigned char pad0_LOAD[6];
    unsigned char f6_LOAD;
    unsigned char f7_LOAD;
    unsigned char f8_LOAD;
    unsigned char f9_LOAD;
    unsigned char fA_LOAD;
    unsigned char fB_LOAD;
    unsigned char fC_LOAD;
    unsigned char fD_LOAD;
    unsigned char padE_LOAD[2];
} Row16_LOAD;
extern Row16_LOAD stru_800BDF4C[];
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

INCLUDE_OVERLAY_ASM(load, dword_800B66C0);

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
    s->fileBuf_LOAD = malloc3_8003FC4C(0x2180);
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

void sub_800B78B8(int v)
{
    ((LoadTask_LOAD*)loadMenuTask_8008D480->entry.buffer)->f58_LOAD = v;
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
INCLUDE_OVERLAY_ASM(load, dword_800B68E0);

extern unsigned short padPressed_8009194C[];
extern MenuWin_LOAD dword_800BDB0C;
extern MenuWin_LOAD dword_800BDCD0;
extern MenuWin_LOAD dword_800BDDF8;
extern MenuWin_LOAD dword_800BDE8C;
extern char* dword_800BDEBC[];
extern char* dword_800BDEFC[];
extern char* dword_800BDF1C[];
extern char* dword_800BDF2C[];
extern char* dword_800BDF3C[];
extern char dword_800BDEA4[];
extern char byte_800B68E0[];
extern char byte_800B68F8[];
extern char byte_800B6918[];
extern char byte_800B6938[];
extern Bytes8_LOAD dword_800B6930;
extern Bytes8_LOAD dword_800B6968;
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
INCLUDE_OVERLAY_ASM(load, dword_800B69F4);

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
INCLUDE_OVERLAY_ASM(load, dword_800B6B8C);

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
    sub_8003F264(&p0, stru_800BDF4C[3].fD_LOAD + stru_800BDF4C[3].fC_LOAD + 1, 5);
    p1.x_LOAD = 0x1C;
    p1.y_LOAD = 0x24;
    DrawText_8003E91C(1, byte_800B6B9C, &p1, 5);
    p2.x_LOAD = 0x32;
    p2.y_LOAD = 0x24;
    sub_8003F264(&p2, 0xF, 5);
    a = dword_800B6BA0;
    b.c1_LOAD = 1;
    b.c0_LOAD = 0;
    b.s_LOAD = uiColor_8008B590;
    DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
}

extern Pos_LOAD dword_800BD93C[]; // the save list's column positions
extern Row8_LOAD dword_800BD960[]; // sprites drawn on every save row (ends with f4 <= 0)
extern Row8_LOAD dword_800BD9E8[]; // the save's icon sprite per SaveSummary_LOAD.icon_24
extern RECT dword_800BDA10; // the save list's clip area
extern char byte_800B6BA8[];
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
                        sub_8003F264(&p3, t->summaries_LOAD[n].f26, 1);
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
        MemCardWriteFile(chan, name, s->fileBuf_LOAD, 0, 0x2180);
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
                MemCopy_800403E8(&s->summaries_LOAD[n], s->fileBuf_LOAD + 0x280, 0x80);
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

INCLUDE_OVERLAY_ASM(load, sub_800B9A8C);

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
            MemCardReadFile(chan, name, s->fileBuf_LOAD, 0, 0x2180);
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

INCLUDE_OVERLAY_ASM(load, sub_800BA3EC);

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

INCLUDE_OVERLAY_ASM(load, dword_800BD93C);

INCLUDE_OVERLAY_ASM(load, dword_800BE184);
