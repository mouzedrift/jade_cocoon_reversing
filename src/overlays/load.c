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
extern int** dword_8008D480;
extern int MemCardSync(int a, int* b, int* c);
extern void MemCardAccept();
extern void MemCardExist();
extern long MemCardReadFile(long chan, char* file, void* adrs, long ofs, long bytes);
extern void LoadMenuInit_800B7674(int mode, int b);
extern void sub_800B7894();
extern int uiTiyLoaded_8008B4E8;
extern int dword_8008B570[];
extern unsigned char byte_800BDF58;
extern char* dword_800BDECC[];
extern char* dword_800BDEDC[];
extern char* dword_800BDEEC[];
extern long MemCardCreateFile(long chan, char* file, long blocks);
extern long MemCardWriteFile(long chan, char* file, void* adrs, long ofs, long bytes);
extern int sub_800BA3EC();
extern void DrawLoadingIcon_8003CD5C(void);
extern void DrawMenuBackground_8002BE10(void);
extern void DrawMessageBox_800BACBC(char** lines);
extern void LoadMenuTask_800B794C(int* t, int* s);
extern void sub_800B79F8();
extern void sub_800B9A8C();
extern void WriteSaveTask_800B98C4();
extern void LoadSaveTask_800BA234();
extern void sub_800BA968();
extern void LoadMenuExit_800BAAE0();
extern void sub_800BA9AC(int* t);
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
extern void ResetMenuRow_800BADE0(unsigned char* p);
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
extern int dword_800BDD64;
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
typedef struct
{
    char* summaries_LOAD; // 15 x 0x80 bytes: the summary block (file offset 0x280) of each save
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
    unsigned char pad9_LOAD[2];
    unsigned char fB_LOAD;
    unsigned char fC_LOAD;
    unsigned char fD_LOAD;
    unsigned char padE_LOAD[2];
} Row16_LOAD;
typedef struct
{
    unsigned char pad0_LOAD[0xC];
    unsigned char fC_LOAD;
    unsigned char padD_LOAD[0xF];
    unsigned char f1C_LOAD;
    unsigned char pad1D_LOAD[0xF];
    unsigned char f2C_LOAD;
    unsigned char pad2D_LOAD[0xF];
    unsigned char f3C_LOAD;
    unsigned char f3D_LOAD;
    unsigned char pad3E_LOAD[0xE];
    unsigned char f4C_LOAD;
} Opts_LOAD;
extern Opts_LOAD dword_800BDF4C;
extern Row16_LOAD stru_800BDF4C[];
extern void sub_8002B8DC(Pair_LOAD q, short* a, short* b, int c);
extern void sub_800B8BD4(void* t);
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
    int* t;
    LoadTask_LOAD* s;
    MemCardStart();
    t = (int*)dword_8008D480 + 4;
    s = (LoadTask_LOAD*)t[5];
    t[0] = (t[0] | 1) & ~0x8000;
    for (i = 0; i < 6; i++)
    {
        ResetMenuRow_800BADE0((unsigned char*)&stru_800BDF4C[i]);
    }
    s->f8_LOAD = 0;
    s->f24_LOAD = -1;
    s->f28_LOAD = 0;
    switch (mode)
    {
    case 0:
        s->s30_LOAD = 1;
        byte_800BDF58 = 0;
        s->f54_LOAD = 4;
        break;
    case 1:
        s->s30_LOAD = 1;
        byte_800BDF58 = 1;
        s->f54_LOAD = 4;
        break;
    case 2:
        s->s30_LOAD = 1;
        byte_800BDF58 = 1;
        s->f54_LOAD = 0xC;
        t[2] = (int)LoadMenuTask_800B794C;
        goto done;
    case 3:
        s->s30_LOAD = 1;
        byte_800BDF58 = 1;
        s->f54_LOAD = 0x4C;
        t[2] = (int)LoadMenuTask_800B794C;
        goto done;
    default:
        s->s30_LOAD = 0;
        byte_800BDF58 = 0;
        s->f54_LOAD = 0;
        break;
    }
    LoadUiTiy_8002BF74();
    t[2] = (int)sub_800B7894;
done:
    if (dword_8008BD80 == -1 && !(s->f54_LOAD & 8))
    {
        s->s30_LOAD = 1;
        byte_800BDF58 = 0;
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

void sub_800B7894(int* t)
{
    if (uiTiyLoaded_8008B4E8)
    {
        t[2] = (int)LoadMenuTask_800B794C;
    }
}

void sub_800B78B8(int v)
{
    dword_8008D480[9][22] = v;
}

void sub_800B78D0(void)
{
    int* t;
    dword_8008B570[516] = -1;
    dword_8008B570[0] |= 0x180;
    t = dword_8008D480[9];
    *(short*)((char*)t + 0x30) = 1;
    byte_800BDF58 = 0;
    t[21] = 0x20;
}

int sub_800B7914(void)
{
    return dword_8008D480[9][2];
}

void sub_800B7934(void)
{
}

int IsLoadMenuActive_800B793C(void)
{
    return loadMenuActive_800BE184;
}

void LoadMenuTask_800B794C(int* t, int* s)
{
    switch (s[10])
    {
    case 0:
        sub_800B79F8(s);
        break;
    case 2:
        sub_800B9A8C(s);
        t[2] = (int)WriteSaveTask_800B98C4;
        s[11] = 0;
        break;
    case 3:
        t[2] = (int)LoadSaveTask_800BA234;
        break;
    case 4:
        t[2] = (int)sub_800BA968;
        break;
    case 5:
    case 6:
        t[2] = (int)LoadMenuExit_800BAAE0;
        break;
    }
}
INCLUDE_OVERLAY_ASM(load, dword_800B68E0);

INCLUDE_OVERLAY_ASM(load, sub_800B79F8);

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
            ResetMenuRow_800BADE0((unsigned char*)&stru_800BDF4C[3]);
            break;
        case 2:
            ResetMenuRow_800BADE0((unsigned char*)&stru_800BDF4C[2]);
            break;
        case 3:
            break;
        case 4:
            ResetMenuRow_800BADE0((unsigned char*)&stru_800BDF4C[4]);
            if (stru_800BDF4C[0].fC_LOAD == 0)
            {
                stru_800BDF4C[4].fC_LOAD = 1;
            }
            break;
        case 5:
            ResetMenuRow_800BADE0((unsigned char*)&stru_800BDF4C[5]);
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

void sub_800B847C(void)
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

void sub_800B85AC(void)
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
    sub_8002B8DC(q, r1, r0, 1);
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
        DrawText_8003E91C(2, dword_800BDA08[byte_800BDF58], &p, 5);
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

void sub_800B8984(void)
{
    Bytes8_LOAD a;
    Tail4_LOAD b;
    DrawUiTiySprt_8002C06C(&dword_800BD998[byte_800BDF58], dword_800BD998[byte_800BDF58].f4_LOAD, dword_800BD998[byte_800BDF58].f6_LOAD);
    a = dword_800B6B8C;
    b.c1_LOAD = 1;
    b.c0_LOAD = 0;
    b.s_LOAD = uiColor_8008B590;
    DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
}

#if 0
// Not matched: only the order of the prologue stores differs ($ra/$s0 vs argument set-up)
void sub_800B8A20(void)
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

void sub_800B8AE4(void)
{
    Pos_LOAD p0;
    Pos_LOAD p1;
    Pos_LOAD p2;
    Bytes8_LOAD a;
    Tail4_LOAD b;
    p0.x_LOAD = 0x1C;
    p0.y_LOAD = 0x24;
    sub_8003F264(&p0, dword_800BDF4C.f3D_LOAD + dword_800BDF4C.f3C_LOAD + 1, 5);
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

INCLUDE_OVERLAY_ASM(load, sub_800B8BD4);

void sub_800B9220(LoadTask_LOAD* t)
{
    if (IsConfirmPressed_8003D288(1, (t->f54_LOAD >> 6) & 1))
    {
        switch (byte_800BDF58)
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
    switch (PollCardAccept_800BAE68(dword_800BDF4C.f1C_LOAD))
    {
    case 0:
    case 3:
        ScanCardSaves_800BAFB0(dword_800BDF4C.f1C_LOAD);
        PlaySfx_80031494(0x7E);
        if (dword_800BDF4C.fC_LOAD == 0)
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
        if (dword_800BDF4C.fC_LOAD == 0)
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
    int r = PollCardAccept_800BAE68(dword_800BDF4C.f1C_LOAD);
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
        if (dword_800BDF4C.f2C_LOAD == 0)
        {
            t->f28_LOAD = 4;
        }
        if (dword_800BDF4C.f2C_LOAD == 1)
        {
            t->f24_LOAD = 1;
        }
    }
}

void sub_800B952C(LoadTask_LOAD* t)
{
    int n = dword_800BDF4C.f3D_LOAD + dword_800BDF4C.f3C_LOAD;
    if (IsCancelPressed_8003D3C0(1, (t->f54_LOAD >> 6) & 1))
    {
        t->f24_LOAD = 1;
    }
    if (IsConfirmPressed_8003D288(0, (t->f54_LOAD >> 6) & 1))
    {
        if (dword_800BDF4C.fC_LOAD == 1)
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
        else if (dword_800BDF4C.fC_LOAD == 0)
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
        if (dword_800BDF4C.f4C_LOAD == 0)
        {
            PlaySfx_80031494(0x7E);
            if (dword_800BDF4C.fC_LOAD == 1)
            {
                WaitCardSync_800BADF4();
                t->f28_LOAD = 3;
            }
            else if (dword_800BDF4C.fC_LOAD == 0)
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
                MemCardReadFile(chan, name, t->summaries_LOAD + t->f20_LOAD * 128, 0x280, 0x80);
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
void WriteSaveTask_800B98C4(int* t, LoadTask_LOAD* s)
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
                t[2] = (int)LoadMenuTask_800B794C;
                s->f28_LOAD = 0;
                s->f24_LOAD = 3;
                PlaySfx_80031494(0x7E);
                MemCopy_800403E8((unsigned int*)(s->summaries_LOAD + n * 128), (unsigned int*)(s->fileBuf_LOAD + 0x280), 0x80);
                ScanCardSaves_800BAFB0(stru_800BDF4C[1].fC_LOAD);
                break;
            case 1:
            case 2:
            case 3:
            case 5:
                t[2] = (int)LoadMenuTask_800B794C;
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
void LoadSaveTask_800BA234(int* t, LoadTask_LOAD* s)
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
            t[2] = (int)LoadMenuTask_800B794C;
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
                    t[2] = (int)LoadMenuTask_800B794C;
                    s->f28_LOAD = 6;
                    s->f54_LOAD |= 1;
                }
                else
                {
                    t[2] = (int)LoadMenuTask_800B794C;
                    s->f28_LOAD = 0;
                    s->f24_LOAD = 0xA;
                }
                PlaySfx_80031494(0x7E);
                break;
            case 1:
            case 2:
            case 3:
            case 5:
                t[2] = (int)LoadMenuTask_800B794C;
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

void sub_800BA968(int* t)
{
    DrawLoadingIcon_8003CD5C();
    DrawMessageBox_800BACBC(dword_800BDECC);
    DrawMenuBackground_8002BE10();
    t[2] = (int)sub_800BA9AC;
}

void sub_800BA9AC(int* t)
{
    DrawLoadingIcon_8003CD5C();
    DrawMessageBox_800BACBC(dword_800BDECC);
    DrawMenuBackground_8002BE10();
    t[2] = (int)FormatCardTask_800BA9F0;
}

void FormatCardTask_800BA9F0(int* t, LoadTask_LOAD* s)
{
    switch (MemCardFormat(stru_800BDF4C[1].fC_LOAD << 4))
    {
    case 0:
        t[2] = (int)LoadMenuTask_800B794C;
        s->f28_LOAD = 0;
        s->f24_LOAD = 3;
        s->f20_LOAD = 0;
        ScanCardSaves_800BAFB0(stru_800BDF4C[1].fC_LOAD);
        s->f5C_LOAD = 0;
        break;
    case 1:
        t[2] = (int)LoadMenuTask_800B794C;
        s->f28_LOAD = 0;
        s->f24_LOAD = 1;
        break;
    case 2:
        t[2] = (int)LoadMenuTask_800B794C;
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

void LoadMenuExit_800BAAE0(int* t, LoadTask_LOAD* s)
{
    free3_8003FC6C(s->summaries_LOAD);
    free3_8003FC6C(s->fileBuf_LOAD);
    loadMenuActive_800BE184 = 0;
    t[0] = (t[0] & ~1) | 0x8000;
    MemCardStop();
    t[2] = (int)sub_800B7650;
    if (!(s->f54_LOAD & 8))
    {
        FreeActiveOverlay_8002C014();
        if (s->f54_LOAD & 0x20)
        {
            sub_80027314();
            sub_800A6D30(sub_800A6D50(1));
        }
        else if (!(s->f54_LOAD & 4))
        {
            sub_80027314();
            sub_800A6D30(sub_800A6D50(1));
        }
        if (s->f54_LOAD & 1)
        {
            short* m = (short*)&saveData_8008B570;
            m[0x2E2 / 2] = -1;
            m[0x2E6 / 2] = -1;
            m[0x2EA / 2] = -1;
            m[0x2EE / 2] = -1;
            m[0x2F2 / 2] = -1;
            dword_80091C54 = 0;
            if (!(s->f54_LOAD & 4))
            {
                unknownFlags_8008D678 |= 0x18000000;
            }
        }
        if (s->f54_LOAD & 0x10)
        {
            sub_80011BCC();
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

void ResetMenuRow_800BADE0(unsigned char* p)
{
    p[12] = p[9];
    p[13] = p[10];
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

#if 0
// Not matched: the original tests the first loop's entry as found < files (slt/beqz on the register copy of 0); this folds it to blez files and swaps which of i/found is copied before the call
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
    for (; i < files; i++)
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
#endif
INCLUDE_OVERLAY_ASM(load, ScanCardSaves_800BAFB0);

#if 0
// Not matched: same as ScanCardSaves_800BAFB0 (first loop entry test found < files is folded to blez files here)
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
    for (; i < files; i++)
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
#endif
INCLUDE_OVERLAY_ASM(load, ScanCardSavesComb_800BB0E4);

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
    MemCopy_800403E8((unsigned int*)h->f200_LOAD, (unsigned int*)dword_800BE0B8, 0x80);
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
