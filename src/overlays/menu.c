// MENU.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "tiy.h"
#include "tu_80019BF0.h"
#include "minion_menu.h"

typedef struct MenuTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} MenuTask;

typedef struct MenuObj
{
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    char pad_18[0x10];
    short f28;
    char pad_2A[0x36];
    short f60;
} MenuObj;


typedef struct MenuCtx
{
    unsigned short flags_0;
    short sel_2;
    short f4;
    short f6;
    int f8;
    int fC;
    unsigned int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
    int f24;
    short f28;
    short arr_2A[11];
    short pad_40[3];
    short arr_46[4];
    char pad_4E[8];
    short f56;
    short f58;
    short f5A;
    short f5C;
    short f5E;
    short f60;
    short f62;
} MenuCtx;

typedef struct MenuRow
{
    unsigned short lim_0;
    unsigned char a_2;
    unsigned char a_3;
    unsigned short lim_4;
    unsigned char a_6;
    unsigned char a_7;
} MenuRow;

typedef struct MenuCol
{
    unsigned short col;
    unsigned char c_2;
    unsigned char c_3;
} MenuCol;

typedef struct MenuQ
{
    int w[4];
} MenuQ;

typedef struct MenuPair
{
    short a;
    short b;
} MenuPair;

typedef struct MenuStatQ
{
    short b;
    short s;
    int z4;
    int z8;
} MenuStatQ;
// what DrawEquipmentWindow_800C0E04 / DrawKeyItemsWindow_800C09B0 take
typedef struct MenuEquipQ
{
    short sel_0; // -> MenuDlg.fC
    short scroll_2;
    short f4;    // -> MenuDlg.f0
    short ot_6;  // -> MenuDlg.f14
    short f8;
    short fA;
    int z;
} MenuEquipQ;

typedef struct MenuLoc
{
    short a;
    short b;
    short c;
    short d;
    int e;
    short f;
    short pad_1E;
    int g;
} MenuLoc;

typedef struct MenuEnt
{
    char pad_0[4];
    short s4;
    unsigned short idx_6;
    unsigned short u8;
    unsigned short a;
} MenuEnt;
extern MenuEnt name_800B1238[];

typedef struct MenuQuad
{
    short a;
    short b;
    unsigned short c;
    short d;
} MenuQuad;
extern char name_800C18F4[];
extern void DrawLargeTextBox_8002AF10();
extern void DrawUnitStatusWindow_8002F1C8();

extern int name_800AD288();
extern UnitStatus* name_80014390();

extern int sub_80034140();
extern void DrawButtonHelpBar_8002B004(void* p, int a, int b);
extern char name_80082680[];
extern char name_800826B0[];
extern char name_800C28F0[];
extern char name_800C28D8[];
extern char name_800C2910[];
extern char name_800C2930[];
extern char name_800C2958[];
extern char name_800C2968[];
extern unsigned short padPressed_8009194C;
extern void sub_800BE294();
extern short name_800C1B74[];
extern short name_800C1B98[];
extern void sub_800BDE10();
extern void sub_800BF794();
extern void sub_800BFCA8();
extern void sub_800BFE18();
extern void sub_800C0084();
extern void sub_800C01AC();
extern void sub_800C01D0();
extern void MinionListScreen_800BD80C();

extern int sub_800AD7F8();
extern MenuQ name_800C1E98[];
extern int IsConfirmPressedP1_8003D380();
extern int IsCancelPressedP1_8003D41C();

extern int sub_800BFB10();
extern int sub_800BFBE0();
extern void PlaySfx_80031494();

// stat changes worked out by sub_80013C28
typedef struct MenuStatDelta
{
    int f0;
    int f4;
    int f8;
    int pad_C[4];
    int x_1C;
    int y_20;
    int f24;
} MenuStatDelta;
// the head of a MenuObj (sub_800C00D4 / sub_800C00F8) followed by the delta
typedef struct MenuTmp
{
    int f0;
    int f4;
    int f8;
    int fC;
    MenuStatDelta d_10;
} MenuTmp;
extern void sub_80013C28();
extern void sub_800C00F8();
extern void sub_800C00D4();
extern void sub_800AD1E0();
extern void sub_800C0084();


extern int sub_800BF540();
extern void sub_800BE048();

typedef struct MenuBox
{
    short x_0;
    short y_2;
    int pad_4;
    short col_8;
    char c_A;
    char c_B;
} MenuBox;
extern void DrawUiTiySprt_8002C06C();
extern unsigned short uiColor_8008B590;
extern void sub_800BFF84();
extern void sub_80027478();
extern EventNode* name_8008D498;
extern int sub_800C0990();
typedef struct MenuDlg
{
    int f0, f4, f8, fC, f10, f14;
} MenuDlg;
extern MenuDlg name_800BBB7C;
extern void DrawMenuWindows_8002A5A4();
extern int name_800C1998[];
extern void sub_800BE25C();
extern void sub_800BF8B4();
extern void sub_800BE38C();
extern int name_800C29BC;
extern void sub_800BD590();
extern void DrawWindow_80042460();

extern void sub_800BE4A0();
extern void sub_800BD5E4();
extern void sub_800BD6C8();

INCLUDE_OVERLAY_ASM(menu, dword_800B66C0);

typedef struct MenuMain
{
    int f0;
    char pad_4[0x30];
    unsigned int a34[4];
    short count_44;
    short s46;
    int i48;
    int a4C[3];
    short s58;
    short pad_5A;
    int a5C[4];
    unsigned int a6C[4];
    int a7C[4];
    UnitStatus st_8C[4];
    UnitStatus st_1AC[4];
    unsigned int a2CC[4];
    int i2DC;
} MenuMain;
extern void sub_800BBE50();
extern void LoadUiTiy_8002BF74();
extern void sub_800122A0();
EventEntry* CreateMenuTask_800BBB9C(EventNode* n)
{
    EventEntry* t = AllocEventEntry_80043AF8(n);
    MenuMain* c;
    short i;
    UnitStatus* p;
    if (t)
    {
        LoadUiTiy_8002BF74();
        c = t->buffer;
        t->flags = (t->flags | 1) & ~0x8000;
        c->s46 = 0;
        c->i48 = 1;
        for (i = 0; i < 4; i++)
        {
            c->a34[i] = 0;
            c->a6C[i] = 0;
            c->a7C[i] = 0;
            c->a2CC[i] = 0;
            c->a5C[i] = 0;
        }
        c->i2DC = 0;
        for (i = 0; i < 3; i++)
        {
            int ok = 0;
            if (name_800B1238[i].a == 7)
                continue;
            if (name_800B1238[i].idx_6)
                p = GetMinionStatus_800107A0(3, name_800B1238[i].idx_6 - 1);
            else
                p = &levantStatus_8008BD38;
            if (name_800B1238[i].idx_6 || name_800B1238[i].a == 5 || name_800B1238[i].a == 0x1A)
                ok = 1;
            if (ok && !(p->status_0 & 0x400))
                sub_800122A0(name_800B1238[i].idx_6, name_800B1238[i].u8, &c->a6C[name_800B1238[i].idx_6]);
        }
        c->s58 = 0;
        c->count_44 = CountMinions_80010548(3) + 1;
        c->f0 = 0;
        p = &levantStatus_8008BD38;
        MemCopy_800403E8(&c->st_8C[0], p, 0x48);
        MemCopy_800403E8(&c->st_1AC[0], p, 0x48);
        c->a2CC[0] = p->exp_4;
        for (i = 1; i < c->count_44; i++)
        {
            p = GetMinionStatus_800107A0(3, i - 1);
            MemCopy_800403E8(&c->st_8C[i], p, 0x48);
            MemCopy_800403E8(&c->st_1AC[i], p, 0x48);
            c->a2CC[i] = p->exp_4;
        }
        t->cb_8 = (EventEntryFn)sub_800BBE50;
    }
    return t;
}

extern int uiTiyLoaded_8008B4E8;
extern void DrawMenuBackground_8002BE10();
extern void sub_800BBE90();
void sub_800BBE50(MenuTask* t)
{
    if (uiTiyLoaded_8008B4E8)
    {
        DrawMenuBackground_8002BE10();
        t->next_8 = sub_800BBE90;
    }
}

extern int sub_800BD230();
extern void sub_800BCFDC();
extern void sub_800BC2A8();
extern void sub_800BD1B0();
extern void sub_800BBF48();
void sub_800BBE90(MenuTask* t, MenuMain* a)
{
    MenuMain* q = a;
    DrawMenuBackground_8002BE10();
    SetFadeMode_8001C19C(3, 0x20);
    if (sub_800BD230(q))
    {
        sub_800BCFDC(a);
        t->next_8 = sub_800BD1B0;
    }
    else
    {
        sub_800BC2A8(q);
        t->next_8 = sub_800BBF48;
    }
}

extern int sub_800121A8();
int sub_800BBF10(unsigned char a, unsigned char b)
{
    int x = sub_800121A8(a);
    return x < sub_800121A8(b);
}

extern void sub_800BC56C();
extern void sub_800BC9E8();
extern void sub_800BCB98();
extern void sub_800BCEA0(MenuMain* a, int b, void* c, short d);
extern void sub_800BC24C();
extern char name_800C172C[];
extern int name_8008D678;
extern void FreeActiveOverlay_8002C014();
extern void sub_800A6D30();
void sub_800BBF48(MenuTask* t, MenuMain* c)
{
    void* p = 0;
    short i;
    int m;
    if (!(c->f0 & 0x80))
    {
        sub_800BC56C(c);
    }
    else if (!(c->f0 & 0x40))
    {
        for (i = 0; i < c->count_44; i++)
        {
            p = name_80014390(i & 0xFF);
            MemCopy_800403E8(p, &c->st_8C[i], 0x48);
        }
        sub_800BC9E8(c);
    }
    m = 1;
    if (c->f0 & (m << c->count_44))
        DrawButtonHelpBar_8002B004(name_800C172C, 0, 0xE);
    if (c->f0 & 0x20)
    {
        if (!(c->f0 & 2))
        {
            sub_800BCB98(c, 0xF);
            if (c->s46 >= 0x80)
                c->i48 = 0;
            if (c->i48)
                c->s46 += 4;
            else if (c->s46 >= 5)
                c->s46 -= 4;
        }
        else
        {
            for (i = 1; i < c->count_44; i++)
            {
                int m2 = 1 << (i + 1);
                if (!(c->f0 & m2))
                {
                    p = name_80014390(i & 0xFF);
                    break;
                }
            }
            if (p)
                sub_800BCEA0(c, 0xE, p, i);
        }
    }
    else
    {
        sub_800BC2A8(c);
    }
    DrawMenuBackground_8002BE10();
    if (c->f0 & 0x40)
    {
        t->next_8 = sub_800BC24C;
        SetFadeMode_8001C19C(0, 0x20);
        FreeActiveOverlay_8002C014();
        if (saveData_8008B570.mapId_2E4[3].field_2 == saveData_8008B570.mapId_2E4[3].field_0)
            sub_80027314();
    }
    else if (padPressed_8009194C & 0x20)
    {
        i = 1;
        if (c->f0 & (i << c->count_44))
        {
            MenuTask* g;
            name_8008D678 |= 0x800000;
            g = (MenuTask*)&name_8008D498->entry;
            g->flags_0 = (g->flags_0 | 1) & ~0x8000;
            sub_800A6D30(4);
            eventDispatchHalt_8008B540 = 1;
            t->flags_0 = (t->flags_0 & ~1) | 0x8000;
        }
    }
}

extern int sub_800272D0();
extern void ResetOverlayLoaderTask_80020D68();
extern void sub_800A6D30();
void sub_800BC24C(MenuTask* t)
{
    if (sub_800272D0() == 0)
    {
        ResetOverlayLoaderTask_80020D68();
        sub_800A6D30(1);
        eventDispatchHalt_8008B540 = 1;
        t->flags_0 = (t->flags_0 & ~1) | 0x8000;
    }
}

extern void DrawLevantSummary_8002E334();
extern void DrawLevantHeaderWindows_8002FD0C();
extern void DrawPartySlotWindow_8002F8E4();
extern void AddClipDrawAreaPrim_80033308();
extern void sub_800BC934(int a, int b);
typedef struct MenuPartyQ
{
    short x;
    short y;
    int f4;
    int f8;
} MenuPartyQ;
void sub_800BC2A8(MenuMain* c)
{
    short pos[2];
    MenuPartyQ q20;
    MenuPartyQ q30;
    MenuLoc loc;
    void* st;
    short i;
    pos[0] = 0xA;
    pos[1] = 0x2C;
    AddClipDrawAreaPrim_80033308(pOT_8008D454 + 14);
    if (!(c->f0 & 2))
        st = &c->st_8C[0];
    else
        st = &levantStatus_8008BD38;
    pos[0] = 0xA;
    pos[1] = 0x2C;
    if (c->a7C[0] && !(c->f0 & 2))
    {
        q20.x = 0xE;
        q20.y = 8;
        q20.f4 = 1;
        q20.f8 = frameCount_8008D3FC;
        DrawLevantSummary_8002E334(st, &q20);
        DrawLevantHeaderWindows_8002FD0C(0xE, 8, 1, 1, 0);
    }
    else
    {
        q30.x = 0xE;
        q30.y = 8;
        q30.f4 = 0;
        q30.f8 = 0;
        DrawLevantSummary_8002E334(st, &q30);
        DrawLevantHeaderWindows_8002FD0C(0xE, 8, 0, 0, 0);
    }
    AddClipDrawAreaPrim_80033308(pOT_8008D454 + 14);
    for (i = 0; i < c->count_44 - 1; i++)
    {
        int g = 0;
        int e = 0;
        short cv = -1;
        int m = 1 << (i + 2);
        if (c->f0 & m)
        {
            st = name_80014390((unsigned char)(i + 1));
        }
        else
        {
            st = &c->st_8C[i + 1];
            if (c->a7C[i + 1])
            {
                g = 1;
                e = frameCount_8008D3FC;
                cv = i;
            }
        }
        loc.a = 8;
        loc.b = c->count_44 - 1;
        loc.c = cv;
        loc.d = 0xE;
        loc.e = e;
        loc.f = i;
        loc.g = g;
        DrawPartySlotWindow_8002F8E4(st, &loc);
    }
    AddClipDrawAreaPrim_80033308(pOT_8008D454 + 14);
    for (i = 0; i < c->count_44; i++)
    {
        if (c->a7C[i])
        {
            int m = 1 << (i + 1);
            if (!(c->f0 & m))
            {
                if (i == 0)
                    sub_800BC8A8();
                else
                    sub_800BC934(i, (short)(c->count_44 - 1));
            }
        }
    }
}

extern void sub_800BCF74(short a);
extern void PlayMusic_800300E0();
void sub_800BC56C(MenuMain* c)
{
    short i;
    int any;
    if (IsConfirmPressedP1_8003D380(0) || IsCancelPressedP1_8003D41C(0))
    {
        any = 0;
        for (i = 0; i < c->count_44; i++)
        {
            c->st_8C[i].exp_4 += c->a6C[i] - c->a34[i];
            if (c->st_8C[i].exp_4 > 0x3FFFFFF)
                c->a5C[i] = ((int (*)())sub_80011D78)(&c->st_8C[i]);
            if (c->a5C[i])
                c->a7C[i] = 1;
            if (i > 0 && c->a5C[i])
                sub_800BCF74(i - 1);
        }
        c->f0 |= 0x80;
        PlaySfx_80031494(0x7E);
        for (i = 0; i < c->count_44; i++)
        {
            if (c->a7C[i])
                any = 1;
        }
        if (any)
            PlayMusic_800300E0(4, 1);
    }
    else
    {
        int busy = 0;
        for (i = 0; i < c->count_44; i++)
        {
            if (c->a34[i] < c->a6C[i])
            {
                busy = 1;
                break;
            }
        }
        if (busy)
        {
            for (i = 0; i < c->count_44; i++)
            {
                if (c->a34[i] < c->a6C[i])
                {
                    unsigned int d = c->a6C[i] >> 5;
                    if (d == 0)
                        d = c->a6C[i] & 0x1F;
                    c->a2CC[i] += d;
                    c->a34[i] += d;
                    if (c->st_8C[i].exp_4 > 0x3FFFFFF || (c->st_8C[i].exp_4 += d) > 0x3FFFFFF)
                    {
                        unsigned int rest = c->st_8C[i].exp_4 - 0x4000000;
                        c->st_8C[i].exp_4 = 0x4000000;
                        c->a5C[i] = ((int (*)())sub_80011D78)(&c->st_8C[i]);
                        if (i > 0)
                            sub_800BCF74(i - 1);
                        c->st_8C[i].exp_4 = rest;
                        c->a2CC[i] = rest;
                        c->a7C[i] = 1;
                        PlayMusic_800300E0(4, 1);
                    }
                }
            }
            PlaySfx_80031494(0x7F);
        }
        else
        {
            c->f0 |= 0x80;
        }
    }
}

void sub_800BC8A8(void)
{
    short rect[4];
    MenuBox b;
    rect[0] = 0x6C;
    rect[1] = 0x1A;
    rect[2] = 0x6C;
    rect[3] = 0x12;
    b.x_0 = 0x6F;
    b.y_2 = 0x1C;
    DrawUiTiySprt_8002C06C(&b, 0xE4, 0xE);
    b.c_A = 1;
    b.c_B = 1;
    b.col_8 = uiColor_8008B590;
    DrawWindow_80042460(rect, &b.col_8, pOT_8008D454 + 14, frameCount_8008D3FC);
}

extern int GetPartyWindowX_8002FA0C();
void sub_800BC934(int a, int b)
{
    short rect[4];
    MenuBox bx;
    short r = GetPartyWindowX_8002FA0C((short)b, (short)(a - 1));
    if (r != 0)
    {
        rect[0] = r + 8;
        rect[1] = 0xBF;
        rect[2] = 0x54;
        rect[3] = 0x12;
        bx.x_0 = r + 0xE;
        bx.y_2 = 0xC1;
        DrawUiTiySprt_8002C06C(&bx, 0x5D, 0xE);
        bx.c_A = 1;
        bx.c_B = 1;
        bx.col_8 = uiColor_8008B590;
        DrawWindow_80042460(rect, &bx.col_8, pOT_8008D454 + 14, frameCount_8008D3FC);
    }
}

void sub_800BC9E8(MenuMain* p)
{
    short i;
    short s;
    int m;
    SaveData* sv;
    i = 0;
    if (p->count_44 > 0)
    {
        do
        {
            if (i == p->count_44 - 1)
            {
                m = 1 << p->count_44;
                if (p->f0 & m)
                {
                    if (IsConfirmPressedP1_8003D380(1) || IsCancelPressedP1_8003D41C(1))
                        p->f0 |= 0x40;
                    return;
                }
            }
            else
            {
                int m2 = 1 << (i + 1);
                if (p->f0 & m2)
                    continue;
            }
            s = i;
            if (p->a5C[s] > 0)
            {
                if (IsConfirmPressedP1_8003D380(1) || IsCancelPressedP1_8003D41C(1))
                {
                    int f = p->f0;
                    if (!(f & 0x20))
                    {
                        if (s == 0)
                        {
                            sv = &saveData_8008B570;
                            if (sub_800BBF10(p->st_1AC[0].level_44, sv->levantStatus_7C8.level_44))
                                p->f0 |= 0x20;
                            else
                                p->f0 |= 2;
                        }
                        else
                        {
                            p->f0 = f | 0x20;
                        }
                    }
                    else
                    {
                        p->f0 = (f | (1 << (s + 1))) & ~0x20;
                    }
                }
            }
            else
            {
                p->f0 |= 1 << (s + 1);
            }
            return;
        } while (++i < p->count_44);
    }
}

extern void DrawPortrait_8002A42C(short* p, int a, int b, short c);
extern void DrawLargeText_8002FBD8();
extern int GetRankName_8002FCD8();
// Not matched: frame/stack layout matches, but saved-register assignment differs (the 0x80
// constant, &r, 1 and the pOT/b*4 values are rotated by one s-register) and the brightness uses
// -0x80 - x instead of 0x80 - x
#if 0
void sub_800BCB98(MenuMain* c, int b)
{
    short pos[2];
    RECT r;
    MenuCol col;
    MenuCol col2;
    short t[2];
    short t2[2];
    int ra;
    int rb;
    pos[0] = 0x80;
    pos[1] = 0x36;
    DrawPortrait_8002A42C(pos, 0, 0, b);
    r.x = 0x7E;
    r.y = 0x34;
    r.w = 0x44;
    r.h = 0x44;
    col.c_2 = 0;
    col.c_3 = 1;
    col.col = saveData_8008B570.uiColor_20.i;
    DrawWindow_80042460(&r, &col, &pOT_8008D454[b], 0);
    pos[0] = 0x61;
    pos[1] = 0x80;
    DrawUiTiySprt_8002C06C(pos, 0x11, 0xE);
    pos[0] = 0x81;
    pos[1] = 0x81;
    DrawLargeText_8002FBD8(0, pos, saveData_8008B570.levantStatus_7C8.name_10, b);
    r.x = 0x5C;
    r.y = 0x7B;
    r.w = 0x89;
    r.h = 0x15;
    col2.c_2 = 0;
    col2.c_3 = 1;
    col2.col = saveData_8008B570.uiColor_20.i;
    DrawWindow_80042460(&r, &col2, &pOT_8008D454[b], 0);
    ra = sub_800121A8(c->st_1AC[0].level_44);
    rb = sub_800121A8(levantStatus_8008BD38.level_44);
    if (ra < rb)
    {
        if (c->i48)
        {
            SetSemiTrans(&fonts_80095FB0[2], 1);
            t[0] = 0x81;
            t[1] = 0x99;
            fonts_80095FB0[2].r_4 = fonts_80095FB0[2].g_5 = fonts_80095FB0[2].b_6 = 0x80 - (unsigned char)c->s46;
            DrawText_8003E91C(2, GetRankName_8002FCD8(ra), t, b);
        }
        else
        {
            SetSemiTrans(&fonts_80095FB0[2], 1);
            t2[0] = 0x81;
            t2[1] = 0x99;
            fonts_80095FB0[2].r_4 = fonts_80095FB0[2].g_5 = fonts_80095FB0[2].b_6 = 0x80 - (unsigned char)c->s46;
            DrawText_8003E91C(2, GetRankName_8002FCD8(rb), t2, b);
        }
        fonts_80095FB0[2].r_4 = fonts_80095FB0[2].g_5 = fonts_80095FB0[2].b_6 = 0x80;
        SetSemiTrans(&fonts_80095FB0[2], 0);
    }
    else
    {
        t[0] = 0x81;
        t[1] = 0x99;
        DrawText_8003E91C(2, GetRankName_8002FCD8(rb), t, b);
    }
    {
        MenuCol* col3 = (MenuCol*)t;
        pos[0] = 0x61;
        pos[1] = 0x99;
        DrawUiTiySprt_8002C06C(pos, 0xC2, 0xE);
        r.x = 0x5C;
        r.y = 0x93;
        r.w = 0x89;
        r.h = 0x15;
        col3->c_2 = 0;
        col3->c_3 = 1;
        col3->col = uiColor_8008B590;
        DrawWindow_80042460(&r, col3, &pOT_8008D454[b], 0);
    }
}
#endif
INCLUDE_OVERLAY_ASM(menu, sub_800BCB98);

extern char name_800C1060[];
void sub_800BCEA0(MenuMain* a, int b, void* c, short d)
{
    short s[2];
    MenuCol col;
    if (c)
    {
        int i = d;
        Minion* m = GetMinion_80010598(3, i - 1);
        s[0] = 0x33;
        s[1] = 0x3E;
        DrawUnitStatusPanel_8002DB48(c, b, 0, s, m, &a->st_1AC[i]);
    }
    col.col = uiColor_8008B590;
    col.c_2 = 0;
    col.c_3 = 1;
    DrawWindow_80042460(name_800C1060, &col, &pOT_8008D454[b], 0);
}

extern void sub_8001AEB8();
extern int name_800338B0();
void sub_800BCF74(short a)
{
    int x = a - 1;
    int r17 = (int)sub_80010824(3, x);
    Minion* r16 = GetMinion_80010598(3, x);
    sub_8001AEB8(name_800338B0(r16), &r16->status_84, r17);
}

typedef struct MenuSlot
{
    char pad_0[2];
    unsigned char f2;
    unsigned char f3;
    char pad_4[4];
} MenuSlot;
extern MenuSlot name_800C29A0[];

typedef struct MenuMsgEnt
{
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
} MenuMsgEnt;

typedef struct MenuMsg
{
    int f0;
    short* size_4;
    int f8;
    MenuMsgEnt e[3];
    int f48;
    int f4C;
} MenuMsg;

extern void* OpenItemMessageWindow_80035AC8();
void sub_800BCFDC(MenuMain* c)
{
    MenuMsg m;
    short sz[2];
    MenuMsgEnt l[3];
    short i;
    short n = 0;
    sz[0] = 100;
    sz[1] = 100;
    for (i = 0; i < 3; i++)
    {
        if (c->a4C[i])
        {
            l[n].f0 = name_800C29A0[i].f2;
            l[n].f4 = name_800C29A0[i].f3;
            l[n].f8 = 1;
            l[n].fC = 2;
            l[n].f10 = name_800C29A0[i].f3;
            n++;
        }
    }
    if (n < 3)
    {
        i = n;
        do
        {
            l[i].f0 = -1;
            l[i].f4 = 0xFF;
            l[i].f8 = 0;
            l[i].fC = 0;
            l[i].f10 = 0;
        } while (++i < 3);
    }
    m.f0 = 1;
    m.size_4 = sz;
    m.f8 = 0;
    m.e[0] = l[0];
    m.e[1] = l[1];
    m.e[2] = l[2];
    m.f48 = -1;
    m.f4C = 0;
    OpenItemMessageWindow_80035AC8(&m);
}

extern void sub_80034A84();
extern EventNode* name_8008D640;
void sub_800BD1B0(MenuTask* t)
{
    EventEntry* p = &name_8008D640->entry;
    int f;
    DrawMenuBackground_8002BE10();
    f = p->flags & 0x8001;
    if (f != 1)
        t->next_8 = sub_800BBF48;
    if (IsConfirmPressedP1_8003D380(1) || IsCancelPressedP1_8003D41C(1))
        sub_80034A84(p);
}



int sub_800BD230(MenuMain* c)
{
    short i;
    int found = 0;
    for (i = 0; i < 3; i++)
    {
        name_800C29A0[i].f3 = 0xFF;
        c->a4C[i] = 0;
    }
    for (i = 0; i < 3; i++)
    {
        MenuEnt* e = &name_800B1238[i];
        if (e->s4 != -1 && e->a != 7)
        {
            if (sub_800BD358(&name_800C29A0[i], e->s4))
            {
                c->a4C[i] = 1;
                found = 1;
            }
        }
    }
    return found;
}

extern int rand();
extern MenuRow name_800C1080[];
int sub_800BD358(MenuSlot* out, int idx)
{
    MenuRow* r = &name_800C1080[idx];
    int found = 0;
    int a;
    int b;
    a = rand();
    b = rand();
    if (a < r->lim_0)
    {
        out->f2 = r->a_2;
        out->f3 = r->a_3;
        found = 1;
    }
    else if (b < r->lim_4)
    {
        out->f2 = r->a_6;
        out->f3 = r->a_7;
        found = 1;
    }
    return found;
}

extern int CountMinions_80010548();
extern int CountItems_800106B8();
extern void SetFontClutOffset_8003F900();
extern int name_800C29B8;
extern int name_8008D678;
extern void LoadUiTiy_8002BF74();
void sub_800BD40C(MenuTask* t, MenuCtx* c)
{
    short i;
    c->flags_0 = 1;
    c->sel_2 = 0;
    c->f4 = 0;
    c->f8 = CountMinions_80010548(3) + 1;
    c->fC = CountItems_800106B8();
    c->f6 = 0;
    sub_800BF8B4(c);
    c->f62 = 0;
    c->f60 = 0;
    c->f10 = 0;
    c->f10 = name_800C1998[c->sel_2];
    c->f14 = 0;
    c->f1C = 0;
    c->f18 = 0;
    c->f24 = 0;
    c->f28 = 0;
    c->f56 = 0;
    for (i = 0; i < 11; i++)
        c->arr_2A[i] = 0;
    for (i = 0; i < 4; i++)
        c->arr_46[i] = 0;
    SetFontClutOffset_8003F900(2, 0);
    SetFontClutOffset_8003F900(1, 0);
    name_800C29BC = 0;
    SetFadeMode_8001C19C(0, 0x20);
    name_800C29B8 = 0;
    if (!(name_8008D678 & 0x800000))
        LoadUiTiy_8002BF74();
    else
        name_800C29B8 = 1;
    name_8008D678 &= 0xFF7FFFFF;
    t->next_8 = sub_800BD590;
}

void sub_800BD590(MenuTask* t, int a)
{
    if (uiTiyLoaded_8008B4E8)
    {
        DrawMenuBackground_8002BE10();
        sub_800BE4A0(a);
        t->next_8 = sub_800BD5E4;
    }
}

void sub_800BD5E4(MenuTask* t, int a)
{
    DrawMenuBackground_8002BE10();
    sub_800BE4A0(a);
    SetFadeMode_8001C19C(3, 0x20);
    t->next_8 = sub_800BD6C8;
}

void SetAllMinionsCaptured_800BD634(void)
{
    int i;
    for (i = 0; i < 0xD3; i++)
    {
        if (sub_800BDD94(i) && (unsigned)(i - 0x25) >= 4)
        {
            int r = i / 32;
            int q = r;
            r = i - q * 32;
            saveData_8008B570.allMinionsBitfields_814[q] |= 1 << r;
        }
    }
}

void sub_800BD6C8(MenuTask* t, MenuCtx* c)
{
    DrawMenuBackground_8002BE10();
    sub_800BFE18(c);
    if (c->sel_2 == 6)
        sub_800C01AC(c);
    if (c->sel_2 == 7)
        sub_800C01D0(c);
    sub_800BE4A0(c);
    if (c->f24 == 0)
    {
        sub_800BE294(c);
        if (c->f18 || c->f1C)
            sub_800BDE10(c);
        if (c->flags_0 & 8)
            sub_800C0084();
        else
            sub_800BFCA8(c);
    }
    else
    {
        sub_800BF794(c);
    }
    if (c->f28 < 8)
        c->f28++;
    if ((padPressed_8009194C & 0x80) && c->sel_2 == 0 && sub_80034140())
        t->next_8 = MinionListScreen_800BD80C;
}

typedef struct MenuBox7
{
    int w[7];
} MenuBox7;
typedef struct MenuUiWin
{
    RECT* rect;
    int f4;
    short f8;
    short fA;
} MenuUiWin;
extern MenuBox7 name_800BB9A4;
extern int name_800C2980;
extern char name_800C2958[];
extern unsigned short padRepeat_800918CC;
extern void DrawMenuItemWithWindow_8002ADB4();
extern void DrawMinionListPage_800BDBFC(char* a, int page);
extern void DrawUiWindow_8002A384();
extern void DrawSmallNumber3_8002C290();
extern void DrawScrollArrow_8002B3DC(MenuPair p, int t, void* pos, int ot);
void MinionListScreen_800BD80C(MenuTask* t, char* a)
{
    MenuCol col;
    MenuBox7 box;
    MenuUiWin w;
    RECT r;
    short pos[2];
    MenuUiWin w2;
    RECT r2;
    MenuPair pr;
    short p2[2];
    char* aa = a;
    if (IsCancelPressedP1_8003D41C(1))
    {
        t->next_8 = sub_800BD6C8;
    }
    else
    {
    if (padRepeat_800918CC & 0x2000)
        name_800C2980++;
    if (padRepeat_800918CC & 0x8000)
        name_800C2980--;
    if (name_800C2980 < 0)
        name_800C2980 = 2;
    if (name_800C2980 >= 3)
        name_800C2980 = 0;
    box = name_800BB9A4;
    col.col = uiColor_8008B590;
    col.c_2 = 0;
    col.c_3 = 1;
    DrawMenuItemWithWindow_8002ADB4(&box, &col, 0xA, 0);
    r.x = 0xA;
    r.y = 0x10;
    r.w = 0x58;
    r.h = 0x12;
    w.rect = &r;
    w.f4 = 0;
    w.f8 = 0;
    w.fA = 0xE;
    pos[0] = 0x1A;
    pos[1] = 0x14;
    DrawUiTiySprt_8002C06C(pos, 0x94, 0xE);
    pos[0] = 0x42;
    pos[1] = 0x16;
    DrawSmallNumber3_8002C290(pos, name_800C2980 + 1, 0xE);
    DrawUiTiySprt_8002C06C(pos, 0xDA, 0xE);
    pos[0] += 0xF;
    DrawSmallNumber3_8002C290(pos, 3, 0xE);
    DrawUiWindow_8002A384(&w);
    r.x = 0xE0;
    r.y = 0x10;
    r.w = 0x58;
    r.h = 0x12;
    w.rect = &r;
    w.f4 = 0;
    w.f8 = 0;
    w.fA = 0xE;
    pos[0] = 0x108;
    pos[1] = 0x16;
    DrawSmallNumber3_8002C290(pos, GetCapturedMinionsCount_800125B8(), 0xE);
    DrawUiTiySprt_8002C06C(pos, 0xDA, 0xE);
    pos[0] += 0x1C;
    DrawSmallNumber3_8002C290(pos, 0xAB, 0xE);
    DrawUiWindow_8002A384(&w);
    DrawMinionListPage_800BDBFC(aa, name_800C2980);
    }
    r2.x = 0xE;
    r2.y = 0x29;
    r2.w = 0x124;
    r2.h = 0xA2;
    w2.rect = &r2;
    w2.f4 = 0;
    w2.f8 = 0;
    w2.fA = 0xE;
    DrawUiWindow_8002A384(&w2);
    pr.a = 2;
    pr.b = 2;
    p2[0] = 8;
    p2[1] = 0x7A;
    DrawScrollArrow_8002B3DC(pr, frameCount_8008D3FC, p2, 0xE);
    pr.b = 0;
    p2[0] = 0x138;
    DrawScrollArrow_8002B3DC(pr, frameCount_8008D3FC, p2, 0xE);
    SetFontClutOffset_8003F900(1, 0);
    DrawButtonHelpBar_8002B004(name_800C2958, 0, 0xF);
    DrawMenuBackground_8002BE10();
}

char* GetMinionSpeciesName_800BDB74(int a)
{
    if (a < 0xC9)
        return minionSpeciesNames_8007A170[a];
    return sub_800B32D4(a - 0xC9);
}

int IsMinionCaptured_800BDBB8(int a)
{
    int q = a / 32;
    int r = a - q * 32;
    return (saveData_8008B570.allMinionsBitfields_814[q] & (1 << r)) != 0;
}

extern char name_800BB9C0[];
extern void DrawText_8003E91C();
extern void sub_8003F89C();
void DrawMinionListPage_800BDBFC(char* a, int page)
{
    short pos[2];
    int cnt = 0;
    int flag = 0;
    int i = 0;
    int hi = (page + 1) * 64;
    int lo = page * 64;
    char* buf = a + 0x64;
    for (i = 0; i < 0xD3; i++)
    {
        if (sub_800BDD94(i) == 0)
            continue;
        if (cnt < hi && cnt >= lo)
        {
            pos[0] = (cnt % 4) * 72 + 0x12;
            pos[1] = ((cnt - lo) / 4) * 10 + 0x2B;
            DrawText_8003E91C(1, name_800BB9C0, pos, 0xE);
        }
        if (IsMinionCaptured_800BDBB8(i) && cnt < hi && cnt >= lo)
        {
            MemCopy_800403E8(buf, GetMinionSpeciesName_800BDB74(i), 0x16);
            pos[0] += 8;
            if (buf)
            {
                sub_8003F89C(buf);
                DrawText_8003E91C(1, buf, pos, 0xE);
            }
        }
        if ((unsigned)(i - 0x24) < 5)
        {
            if (flag == 1)
            {
                if (i == 0x28)
                    cnt++;
            }
            else
                flag = 1;
        }
        else
            cnt++;
    }
}

// Matched
int sub_800BDD94(int a)
{
    if ((unsigned)(a - 0x29) < 0x10 || (unsigned)(a - 0xC9) < 0xA)
        return 0;
    if ((unsigned)(a - 0x20) < 4 || (unsigned)(a - 0xC1) < 8)
        return (unsigned)(a - 0x22) < 2;
    if ((unsigned)(a - 0x24) < 5)
        return 1;
    if ((unsigned)(a - 0x20) < 2 || (unsigned)(a - 0x39) < 0x88)
        return 1;
    return 1;
}

extern int sub_800BF540();
extern void sub_800BE048();
void sub_800BDE10(MenuCtx* c)
{
    int r = 0;
    if (c->f18)
    {
        r = sub_800BF540();
        if ((short)r == 0)
        {
            c->f4 = c->sel_2;
            sub_800BE048(c);
        }
        else if ((short)r != 0xF)
        {
            int snd = 0x7E;
            if ((short)r != 0xE)
                snd = 0x7C;
            PlaySfx_80031494(snd);
            c->f6 = r;
            c->f24 = 1;
        }
    }
    else if (c->f1C)
    {
        if (c->sel_2 == 0)
        {
            c->flags_0 |= 8;
        }
        else
        {
            sub_800BE25C(c);
            sub_800BF8B4(c);
            sub_800BE38C(c);
        }
    }
    if (!(c->flags_0 & 8) && (short)r != 0xF && (short)r != 9 && (short)r != 0xE)
    {
        if (c->f1C)
        {
            c->f10 = 0;
            if ((unsigned)((unsigned short)c->sel_2 - 6) >= 2)
                c->f10 = name_800C1998[c->sel_2];
            c->f14 = c->f10;
        }
        else
        {
            short i;
            int v;
            int mask;
            c->f10 = 0;
            v = name_800C1998[c->sel_2];
            mask = c->f14;
            c->f14 = 0;
            c->f10 = v;
            for (i = 0; i < 0x11; i++)
            {
                int bit = 1 << i;
                if ((bit & mask) && (name_800C1998[c->sel_2] & bit))
                    c->f14 |= bit;
            }
            sub_800BF8B4(c);
            if (c->sel_2 == 6)
            {
                c->arr_2A[0] = 2;
                c->f60 = 2;
            }
            else if (c->sel_2 == 7)
            {
                c->arr_2A[2] = 2;
                c->f60 = 2;
            }
        }
    }
    c->f1C = 0;
    c->f18 = 0;
}

extern short name_800C1950[];
extern unsigned short name_800C193C[];
extern unsigned short name_800C1948[];
extern int name_8001CE70();
void sub_800BE048(MenuCtx* c)
{
    int moved = 0;
    short* tbl = name_800C1950;
    short t = tbl[c->sel_2];
    if (t >= 0)
    {
        if (t == 2)
        {
            int s = c->arr_2A[3] + c->arr_46[0];
            int r = name_800AD288(s, moved);
            if (name_8001CE70(r) & 0x20)
            {
                sub_800BF3AC(r, s);
                PlaySfx_80031494(0x44);
                goto end;
            }
        }
        PlaySfx_80031494(0x7E);
        moved = 1;
        c->sel_2 = (unsigned short)tbl[c->sel_2];
    }
    else if (t == -1)
    {
        PlaySfx_80031494(0x7E);
        switch (c->sel_2)
        {
        case 0:
            if (c->flags_0 & 1)
                c->sel_2 = 6;
            else if (c->flags_0 & 2)
                c->sel_2 = 7;
            else
                c->sel_2 = 8;
            break;
        case 6:
            c->sel_2 = name_800C193C[c->f60];
            break;
        case 7:
            c->sel_2 = name_800C1948[c->f60];
            break;
        }
        moved = 1;
    }
    else if (t == -3)
    {
        short r = name_800AD7F8((short)((unsigned short)c->arr_2A[4] + (unsigned short)c->arr_46[1]));
        if (c->sel_2 == 0xE && r == 0)
        {
            PlaySfx_80031494(0x7E);
            c->sel_2 = 0x10;
            c->f60 = 1;
        }
        else
        {
            PlaySfx_80031494(0x44);
            sub_800BF3E0(c);
        }
    }
end:
    if (moved)
    {
        c->f62 = 0;
        c->f60 = 0;
        c->f28 = 0;
    }
}

extern short name_800C1974[];
void sub_800BE25C(short* p)
{
    short* tbl = name_800C1974;
    short v = tbl[p[1]];
    if (v != -1)
        p[1] = v;
}

void sub_800BE294(MenuCtx* c)
{
    short v = name_800C1B74[c->sel_2];
    if (v != -1)
    {
        c->arr_2A[v] = (unsigned short)c->f60;
    }
    switch (c->sel_2)
    {
    case 0:
        if (c->flags_0 & 1)
        {
            c->arr_46[3] = (unsigned short)c->f62;
            c->arr_2A[6] = 0;
        }
        else if (c->flags_0 & 2)
        {
            c->arr_2A[1] = (unsigned short)c->f60;
            c->arr_2A[6] = (unsigned short)c->f60 + 1;
            c->arr_46[3] = (unsigned short)c->f62;
        }
        else
        {
            c->arr_2A[0] = (unsigned short)c->f60;
        }
        break;
    case 1:
        c->arr_2A[5] = 0;
        c->arr_46[0] = (unsigned short)c->f62;
        break;
    case 14:
        c->arr_46[1] = (unsigned short)c->f62;
        break;
    case 3:
        c->arr_2A[6] = (unsigned short)c->f60 + 1;
        break;
    case 4:
        c->arr_46[2] = (unsigned short)c->f62;
        break;
    }
}
INCLUDE_OVERLAY_ASM(menu, dword_800BBA04);

void sub_800BE38C(MenuCtx* c)
{
    short v = name_800C1B98[c->sel_2];
    if (v != -1)
    {
        c->f60 = (unsigned short)c->arr_2A[v];
        c->f62 = 0;
    }
    switch (c->sel_2)
    {
    case 0:
        if (c->flags_0 & 1)
        {
            c->f60 = 0;
        }
        else if (c->flags_0 & 2)
        {
            c->f60 = (unsigned short)c->arr_2A[1];
        }
        else
        {
            c->f60 = (unsigned short)c->arr_2A[0];
        }
        c->f62 = (unsigned short)c->arr_46[3];
        break;
    case 1:
        c->arr_2A[5] = 0;
        c->f62 = (unsigned short)c->arr_46[0];
        break;
    case 14:
        c->f62 = (unsigned short)c->arr_46[1];
        break;
    case 4:
        c->f62 = (unsigned short)c->arr_46[2];
        break;
    case 6:
        if (c->flags_0 & 1)
        {
            c->f60 = (unsigned short)c->arr_2A[0];
        }
        else if (c->flags_0 & 2)
        {
            c->f60 = (unsigned short)c->arr_2A[2];
        }
        c->f62 = 0;
        break;
    }
}
INCLUDE_OVERLAY_ASM(menu, dword_800BBA44);
// (When writing sub_800BE4A0 in C, delete the jpt_800BBA80 line.)
INCLUDE_OVERLAY_ASM(menu, jpt_800BBA80);

void sub_800BECE4(MenuCtx* c, short b);
void sub_800BEFAC(MenuCtx* a, short b);
void sub_800BF0F4(MenuCtx* a, short b);
extern void sub_800C06E8();
extern void sub_800C08C0();
extern void DrawItemGrid_800C01F4();
extern void sub_800C0428();
extern void sub_800C0578();
extern void sub_800C05E0();
extern void DrawKeyItemsWindow_800C09B0();
void DrawEquipmentWindow_800C0E04(MenuEquipQ* a, short* pos, short c);
extern void sub_800C0CA4();
extern void sub_800BEAE0();
extern void sub_800BEBFC();
void sub_800BEC8C(MenuCtx* unused, RECT* a, short b, int unused2);
extern void DrawMagicList_8002CAC8();
extern void DrawAbilityList_8002CE28();
extern void DrawItemList_8002C728();
extern void DrawFamilyTree_8002D7D0();
extern int DrawTargetSelectMenu_8002D250();
extern void DrawMpGauge_8002F120();
extern int DrawAbilityDescription_8002C670();
extern RECT name_800C1AEC[]; // the menu windows' rects
extern char name_800C22D8[];
extern char name_800BBA44[];
extern char name_800BBA68[];
extern char name_800B6838[];
#if 0
// Not matched: stack layout and code match; register allocation differs (the original gets the window table base into $fp, here it is rematerialised)
void sub_800BE4A0(MenuCtx* c)
{
    short i;
    int s;
    Minion* m;
    if (!(c->flags_0 & 0x20))
    {
        sub_800BEAE0(c);
    }
    for (i = 0; i < 17; i++)
    {
        s = 1 << i;
        if (!(s & c->f10))
        {
            continue;
        }
        AddClipDrawAreaPrim_80033308(&pOT_8008D454[14]);
        s = sub_800C0990(c, s);
        switch (i)
        {
        case 0:
            sub_800C07F0(c);
            break;
        case 1:
            sub_800BECE4(c, 14);
            break;
        case 2:
            sub_800BEFAC(c, 14);
            break;
        case 5:
            if (c->sel_2 == 6 && c->f60 == 2)
            {
                sub_800BF0F4(c, 14);
            }
            break;
        case 4:
        {
            struct_minion_ref r;
            sub_800C06E8(c);
            if (c->sel_2 == 4)
            {
                s = 2;
            }
            else if (c->sel_2 == 7)
            {
                s = 1;
            }
            else
            {
                s = 4;
            }
            m = GetMinion_80010598(3, c->arr_2A[1]);
            if (m)
            {
                r.cursor_0 = c->arr_2A[7];
                r.scroll_2 = c->arr_46[2];
                r.field_4 = s;
                r.ot_6 = 14;
                r.field_8 = 0;
                r.field_A = 1;
                r.minion_C = m;
                DrawMagicList_8002CAC8(&r, 0);
            }
            break;
        }
        case 6:
            if (c->sel_2 == 7 && c->f60 == 2)
            {
                RECT r;
                InterpolateWindowRect_8004196C(&r, &name_800C1AEC[6], (short)s, 8, 0);
                sub_800BEBFC(c, &r);
                DrawAnimatedWindow_8002BEC8(&r, &name_800C1AEC[i], (short)s, 14, 0, 0);
            }
            break;
        case 7:
            sub_800C08C0(c);
            break;
        case 8:
        {
            if (c->sel_2 == 11)
            {
                s = 2;
            }
            else
            {
                s = 1;
            }
            m = GetMinion_80010598(3, c->arr_2A[1]);
            if (m)
            {
                struct_minion_ref r;
                r.cursor_0 = c->arr_2A[10];
                r.scroll_2 = 0;
                r.field_4 = s;
                r.ot_6 = 14;
                r.field_8 = 0;
                r.field_A = 1;
                r.minion_C = m;
                DrawAbilityList_8002CE28(&r, 0);
            }
            {
                int found = 0;
                int is = c->sel_2 == 11;
                if (IsCircleHeldP1_8003D480() && is && c->f24 == 0)
                {
                    found = DrawAbilityDescription_8002C670(GetMinion_80010598(3, c->arr_2A[1]), 0, name_800C22D8, c->arr_2A[10], 14) != 0;
                }
                if (!found)
                {
                    DrawUnitStatusWindow_8002F1C8(&m->status_84, 0, 0, 0, name_800C18F4, 14, 0);
                }
            }
            break;
        }
        case 9:
        {
            MenuPair p;
            p.a = 0;
            p.b = 0;
            DrawFamilyTree_8002D7D0(GetMinion_80010598(3, c->arr_2A[1]), 14, &p);
            break;
        }
        case 10:
            DrawItemGrid_800C01F4(c);
            break;
        case 11:
        {
            struct_minion_ref r;
            sub_800C0428(c);
            if (c->sel_2 == 1)
            {
                s = 2;
            }
            else if (c->sel_2 == 6)
            {
                s = 1;
            }
            else
            {
                s = 4;
            }
            r.cursor_0 = c->arr_2A[3];
            r.scroll_2 = c->arr_46[0];
            r.field_4 = s;
            r.ot_6 = 14;
            r.field_8 = 0;
            r.field_A = 1;
            r.minion_C = 0;
            DrawItemList_8002C728(&r);
            break;
        }
        case 12:
        {
            MenuPair p;
            MenuEquipQ q;
            sub_800C0578(c);
            p.a = 10;
            p.b = 0x3D;
            q.sel_0 = -1;
            q.scroll_2 = 0;
            q.f4 = 1;
            q.ot_6 = 14;
            q.f8 = 0;
            q.fA = 1;
            q.z = 0;
            DrawEquipmentWindow_800C0E04(&q, (short*)&p, 8);
            break;
        }
        case 13:
        {
            MenuEquipQ q;
            sub_800C05E0(c);
            if (c->sel_2 == 6)
            {
                s = 1;
            }
            else if (c->sel_2 == 14)
            {
                s = 2;
            }
            else
            {
                s = 4;
            }
            q.sel_0 = c->arr_2A[4];
            q.scroll_2 = c->arr_46[1];
            q.f4 = s;
            q.ot_6 = 14;
            q.f8 = 0;
            q.fA = 1;
            q.z = 0;
            DrawKeyItemsWindow_800C09B0(&q);
            break;
        }
        case 15:
        {
            if (c->f24 == 0)
            {
                short pr[4];
                pr[0] = sub_800AD288(c->arr_2A[3] + c->arr_46[0], 0);
                pr[1] = 0;
                pr[2] = c->arr_2A[5];
                pr[3] = 1;
                DrawTargetSelectMenu_8002D250(pr, 0, c->arr_2A[5], 14);
                if (c->sel_2 == 2 && c->arr_2A[5] != 0)
                {
                    MenuPair p;
                    MenuUiWin w;
                    RECT r;
                    int buf[2];
                    sub_800C0CA4(c, buf);
                    s = buf[1];
                    p.a = 0xD2;
                    p.b = 0xBB;
                    DrawMpGauge_8002F120(sub_80014390(c->arr_2A[5] & 0xFF), &p, s, 14);
                    r.w = 0x64;
                    r.h = 0x15;
                    r.x = 0xD2;
                    r.y = 0xBB;
                    w.rect = &r;
                    w.f4 = 0;
                    w.f8 = 0;
                    w.fA = 14;
                    DrawUiWindow_8002A384(&w);
                }
            }
            break;
        }
        case 16:
        {
            RECT r;
            char* tb[4];
            tb[0] = name_800BBA44;
            tb[1] = name_800B6838;
            tb[2] = name_800BBA68;
            tb[3] = name_800B6838;
            r.y = 0xB3;
            r.w = 0x1C;
            r.h = 0x10;
            r.x = c->f60 * 28 + 0x12;
            DrawLargeTextBox_8002AF10(tb, 0, 14);
            sub_800BEC8C(c, &r, 14, 0);
            break;
        }
        }
        if (c->f28 == 8)
        {
            c->f14 |= 1 << i;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(menu, sub_800BE4A0);

void sub_800BEAE0(MenuCtx* c)
{
    char* s;
    switch (c->sel_2)
    {
    case 0:
        if ((c->flags_0 & 1) || (c->flags_0 & 2))
        {
            if (sub_80034140())
                s = name_800C28F0;
            else
                s = name_800C28D8;
        }
        else
        {
            if (sub_80034140())
                s = name_800C2910;
            else
                s = name_80082680;
        }
        break;
    case 6:
        if (c->f60 == 2)
            s = name_800C2958;
        else
            s = name_80082680;
        break;
    case 7:
        if (c->f60 == 2 || c->f60 == 3)
            s = name_800C2958;
        else
            s = name_80082680;
        break;
    case 1:
        s = name_800C2930;
        break;
    case 4:
    case 11:
        s = name_800C2968;
        break;
    case 14:
        s = name_800826B0;
        break;
    case 13:
        s = name_800C2958;
        break;
    default:
        s = name_80082680;
        break;
    }
    DrawButtonHelpBar_8002B004(s, 0, 0xE);
}
INCLUDE_OVERLAY_ASM(menu, dword_800BBB04);

extern void DrawUnitStatusPanel_8002DB48();
void sub_800BEBFC(MenuCtx* o, int a)
{
    Minion* m = 0;
    UnitStatus* m2 = 0;
    short s[2];
    short x = (unsigned short)o->arr_2A[1] + (unsigned short)o->arr_46[3];
    if (x < o->f8 - 1)
    {
        m = GetMinion_80010598(3, x);
        m2 = &m->status_84;
    }
    s[0] = 0x33;
    s[1] = 0x3E;
    if (m)
        DrawUnitStatusPanel_8002DB48(m2, 0xE, a, s, m, 0);
}

void sub_800BEC8C(MenuCtx* unused, RECT* a, short b, int unused2)
{
    MenuCol t;
    t.col = uiColor_8008B590;
    t.c_2 = 1;
    t.c_3 = 1;
    DrawWindow_80042460(a, &t, &pOT_8008D454[b], frameCount_8008D3FC);
}

extern void DrawLevantSummary_8002E334();
extern void InterpolateWindowRect_8004196C();
extern void AddDrawAreaPrim_8003326C();
extern void DrawLevantHeaderWindows_8002FD0C();
extern void DrawAnimatedWindow_8002BEC8();
extern void DrawLargeNumber_8002C100();
extern void AddClipDrawAreaPrim_80033308();
extern int sub_800B330C();
extern int name_8008D678;
extern char name_800C2994[];
extern char name_800C298C[];
extern char name_800C18CC[];
extern char name_800C18D4[];
extern char name_800C2984[];
// Not matched: register allocation - the original keeps c/s in s6/s7 swapped vs. this, computes
// flag in a3 and copies it to s5, and spills the short b to the stack (sh 0x38); tried a ternary,
// a separate f = ... ; flag = f copy
#if 0
void sub_800BECE4(MenuCtx* c, short b)
{
    short pos[2];
    int tmp[2];
    MenuStatQ q;
    int s = sub_800C0990(c, 2);
    int flag = 0;
    int t = 0;
    pos[0] = 0xA;
    pos[1] = 0x2C;
    if (c->sel_2 == 0)
        flag = c->flags_0 & 1;
    if (flag)
        t = frameCount_8008D3FC;
    q.b = b;
    q.s = s;
    q.z4 = 1;
    q.z8 = t;
    DrawLevantSummary_8002E334(&levantStatus_8008BD38, &q);
    InterpolateWindowRect_8004196C(tmp, name_800C2994, (short)s, 8, 0);
    AddDrawAreaPrim_8003326C(tmp, &pOT_8008D454[b]);
    InterpolateWindowRect_8004196C(tmp, name_800C298C, (short)s, 8, 0);
    AddDrawAreaPrim_8003326C(tmp, &pOT_8008D454[b]);
    DrawLevantHeaderWindows_8002FD0C(b, (short)s, 1, flag, tmp);
    AddClipDrawAreaPrim_80033308(&pOT_8008D454[b]);
    if (c->sel_2 == 0)
    {
        pos[0] = 0x93;
        pos[1] = 0x15;
        DrawUiTiySprt_8002C06C(pos, 0xBB, b);
        DrawAnimatedWindow_8002BEC8(tmp, name_800C18CC, (short)s, b, 0, 0);
        pos[0] = 0x84;
        pos[1] = 0xC4;
        DrawUiTiySprt_8002C06C(pos, 0x4F, b);
        DrawAnimatedWindow_8002BEC8(tmp, name_800C18D4, (short)s, b, 1, (c->flags_0 & 4) ? frameCount_8008D3FC : 0);
        if (name_8008D678 & 0x20000)
        {
            int v = sub_800B330C();
            pos[0] = 0xF;
            pos[1] = 0x13;
            DrawUiTiySprt_8002C06C(pos, 0x3A, b);
            pos[0] = 0x54;
            pos[1] = 0x19;
            DrawLargeNumber_8002C100(pos, v, b);
            DrawAnimatedWindow_8002BEC8(tmp, name_800C2984, (short)s, b, 0, 0);
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(menu, sub_800BECE4);

extern void DrawPartySlotWindow_8002F8E4();
void sub_800BEFAC(MenuCtx* a, short b)
{
    MenuLoc loc;
    int v = sub_800C0990(a, 4);
    short j = 0;
    if (a->f8 - 1 > 0)
    {
        do
        {
            UnitStatus* r18 = name_80014390((unsigned char)(j + 1));
            short r17;
            int r16;
            if ((*(int*)a & 0xFFFF0002) == 2)
            {
                r17 = a->f60;
                r16 = frameCount_8008D3FC;
            }
            else
            {
                r17 = -1;
                r16 = 0;
            }
            AddClipDrawAreaPrim_80033308(&pOT_8008D454[b]);
            loc.a = v;
            loc.b = (unsigned short)a->f8 - 1;
            loc.c = r17;
            loc.d = b;
            loc.e = r16;
            loc.f = j;
            loc.g = 1;
            DrawPartySlotWindow_8002F8E4(r18, &loc);
            AddClipDrawAreaPrim_80033308(&pOT_8008D454[b]);
            j++;
        } while (j < a->f8 - 1);
    }
}

extern void DrawLevantSummary_8002E334();
extern void InterpolateWindowRect_8004196C();
extern void AddDrawAreaPrim_8003326C();
extern void DrawLevantHeaderWindows_8002FD0C();
extern void DrawLevantStats_8002F7D0();
extern void DrawAnimatedWindow_8002BEC8();
extern int GetRankName_8002FCD8();
extern int sub_800AD02C();
extern void DrawLargeNumber_8002C100();
extern void AddClipDrawAreaPrim_80033308();
extern void DrawEquipmentWindow_800C0E04(MenuEquipQ* a, short* pos, short c);
extern char name_800C2994[];
extern char name_800C298C[];
extern char name_800C1BE0[];
extern char name_800C18DC[];
extern char name_800C18E4[];
void sub_800BF0F4(MenuCtx* a, short b)
{
    short pos[2];
    int tmp[2];
    MenuStatQ q;
    short pp[2];
    MenuEquipQ w;
    int t50[2];
    short pos2[2];
    int s = sub_800C0990(a, 1);
    UnitStatus* lv;
    AddClipDrawAreaPrim_80033308(&pOT_8008D454[b]);
    lv = &levantStatus_8008BD38;
    pos[0] = 0xA;
    pos[1] = 0x2C;
    q.b = b;
    q.s = s;
    q.z4 = 0;
    q.z8 = 0;
    DrawLevantSummary_8002E334(lv, &q);
    InterpolateWindowRect_8004196C(tmp, name_800C2994, (short)s, 8, 0);
    AddDrawAreaPrim_8003326C(tmp, &pOT_8008D454[b]);
    InterpolateWindowRect_8004196C(tmp, name_800C298C, (short)s, 8, 0);
    AddDrawAreaPrim_8003326C(tmp, &pOT_8008D454[b]);
    DrawLevantHeaderWindows_8002FD0C(b, (short)s, 0, 0, tmp);
    AddClipDrawAreaPrim_80033308(&pOT_8008D454[b]);
    pos[0] = 0xD1;
    pos[1] = 0x88;
    DrawLevantStats_8002F7D0(pos, 0xE);
    DrawAnimatedWindow_8002BEC8(tmp, name_800C1BE0, (short)s, b, 0, 0);
    w.sel_0 = -1;
    pp[0] = 0xA;
    pp[1] = 0x88;
    w.scroll_2 = 0;
    w.f4 = 1;
    w.ot_6 = b;
    w.f8 = 0;
    w.fA = 1;
    w.z = 0;
    DrawEquipmentWindow_800C0E04(&w, pp, s);
    AddClipDrawAreaPrim_80033308(&pOT_8008D454[b]);
    pos[0] = 0xF;
    pos[1] = 0x77;
    DrawUiTiySprt_8002C06C(pos, 0xC2, b);
    pos2[0] = 0x2F;
    pos2[1] = 0x77;
    DrawText_8003E91C(2, GetRankName_8002FCD8(sub_800121A8(lv->level_44)), pos2, b);
    DrawAnimatedWindow_8002BEC8(t50, name_800C18DC, (short)s, b, 0, 0);
    pos[0] = 0x9A;
    pos[1] = 0x75;
    DrawUiTiySprt_8002C06C(pos, 0x7B, b);
    pos[0] = 0x104;
    pos[1] = 0x76;
    DrawLargeNumber_8002C100(pos, sub_800AD02C(), b);
    pos[0] = 0x104;
    pos[1] = 0x76;
    DrawUiTiySprt_8002C06C(pos, 0xE9, b);
    DrawAnimatedWindow_8002BEC8(t50, name_800C18E4, (short)s, b, 0, 0);
}

extern void sub_800AD1E0();
void sub_800BF3AC(MenuObj* o)
{
    sub_80011B24((int)o);
    sub_800AD1E0(o, 1, 0);
}

extern void sub_800A911C();
// Not matched: original tests s == 0 via sltiu + bnez (one word more); also tried
// (unsigned)s < 1 and short s (both fold to beqz)
#if 0
void sub_800BF3E0(MenuCtx* c)
{
    MenuTmp tmp;
    int r17;
    UnitStatus* p;
    int s;
    switch (c->sel_2)
    {
    case 2:
        r17 = name_800AD288((short)((unsigned short)c->arr_2A[3] + (unsigned short)c->arr_46[0]), 0);
        tmp.f8 = 1;
        sub_800C00D4(&tmp, r17, c->arr_2A[5]);
        tmp.f0 = 4;
        p = name_80014390(*(unsigned char*)&c->arr_2A[5]);
        if (p)
            sub_80013C28(&levantStatus_8008BD38, p, &tmp, &tmp.d_10);
        sub_800C00F8(&tmp, &tmp.d_10);
        sub_800AD1E0(r17, 1, 0);
        break;
    case 0xE:
        s = (short)sub_800AD7F8((short)((unsigned short)c->arr_2A[4] + (unsigned short)c->arr_46[1]));
        c->flags_0 |= 8;
        sub_800C0084();
        if (s == 0)
            name_800C29BC = 1;
        else
            sub_800A911C(s);
        break;
    case 0x10:
        c->flags_0 |= 8;
        sub_800C0084();
        name_800C29BC = 1;
        break;
    }
}
#endif
INCLUDE_OVERLAY_ASM(menu, sub_800BF3E0);

typedef struct MenuUseQ
{
    short a;
    short b;
    short c;
    short d;
    short e;
    short f;
    int g;
} MenuUseQ;
extern int CheckItemUsable_80033AFC();
extern int CheckItemOnTarget_80033DF4();
extern int sub_800AD73C();
extern int sub_800A5E80();
extern int sub_800C1000();
// Not matched: cases 1, 2 and 4 match; in cases 6, 7 and 14 the original returns through the delay
// slot of branches straight to the epilogue (v0 used as temp) and the 14 tail is not a store-flag;
// tried a single ret variable (goes to a saved reg), && in the 14 tail, case order 6/7/4 fall-through
#if 0
int sub_800BF540(MenuCtx* c)
{
    MenuUseQ q;
    MenuQuad q2;
    short r;
    short s;
    switch (c->sel_2)
    {
    case 1:
        q.a = c->arr_2A[3];
        q.b = c->arr_46[0];
        q.c = 0;
        q.d = 0;
        q.e = 0;
        q.f = 1;
        q.g = 0;
        r = CheckItemUsable_80033AFC(&q);
        if (r == 1)
            return 1;
        if (r <= 0)
            return 0;
        return (r < 4) ? 2 : 0;
    case 2:
        s = c->arr_2A[3] + c->arr_46[0];
        if (sub_800AD2C8(s, 0) == 0)
            return 1;
        q2.a = sub_800AD288(s, 0);
        q2.b = 0;
        q2.c = c->arr_2A[5];
        q2.d = 1;
        r = CheckItemOnTarget_80033DF4(&q2);
        switch (r)
        {
        case 2:
            return 0xA;
        case 1:
            return 0xB;
        case 4:
            return 0xC;
        case 3:
            return 0xD;
        }
        return 0;
    case 6:
        if (c->f60 == 2)
            return 0xF;
        if (c->f60 != 0)
            return 0;
        if (c->fC != 0)
            return 0;
        return 9;
    case 7:
        if ((unsigned short)c->f60 - 2 >= 2u)
            return 0;
    case 4:
        return 0xF;
    case 14:
    {
        int v;
        s = sub_800AD7F8((short)((unsigned short)c->arr_2A[4] + (unsigned short)c->arr_46[1]));
        if (sub_800AD73C(s) == 0)
            return 3;
        if (sub_8001D36C(s))
            return 0xE;
        if (s)
            v = sub_800A5E80(s);
        else
            v = sub_80034140();
        if (v != 0 && sub_800C1000() != 0)
            return 0;
        return 2;
    }
    }
    return 0;
}
#endif
INCLUDE_OVERLAY_ASM(menu, sub_800BF540);
INCLUDE_OVERLAY_ASM(menu, jpt_800BBB08);

extern int name_800C18FC[];
extern char name_800B6838[];
void sub_800BF794(MenuCtx* c)
{
    int tmp[4];
    if (c->f56 < 0x96)
        c->f56++;
    if (c->f6 != 0xE)
    {
        tmp[0] = name_800C18FC[c->f6];
        tmp[1] = (int)name_800B6838;
        tmp[2] = (int)name_800B6838;
        tmp[3] = (int)name_800B6838;
        DrawLargeTextBox_8002AF10(tmp, 0, 0xE);
        if (padPressed_8009194C == 0)
        {
            if (c->f56 < 0x96)
                return;
        }
    }
    else
    {
        int r = (short)name_800AD7F8((short)((unsigned short)c->arr_2A[4] + (unsigned short)c->arr_46[1]));
        DrawLargeTextBox_8002AF10(&name_800C1E98[r], 0, 0xE);
        if (!IsConfirmPressedP1_8003D380(0) && !IsCancelPressedP1_8003D41C(0))
            return;
        PlaySfx_80031494(0x7D);
    }
    c->f6 = 0;
    c->f24 = 0;
    c->f56 = 0;
}

typedef struct MenuLayout
{
    unsigned short a;
    unsigned short b;
    unsigned short c;
    unsigned short d;
    char pad_8[8];
} MenuLayout;
extern MenuLayout name_800C19DC[];
extern int sub_800AD308();
extern int sub_800AD79C();
extern int CountMagicBits_8001AE54();
void sub_800BF8B4(MenuCtx* c)
{
    MenuLayout* e = &name_800C19DC[c->sel_2];
    int v;
    c->f58 = e->a;
    c->f5A = e->b;
    c->f5C = e->c;
    c->f5E = e->d;
    switch (c->sel_2)
    {
    case 0:
        if (c->flags_0 & 1)
        {
            c->f58 = 1;
            c->f5A = 1;
            c->f5C = 1;
            c->f60 = 0;
            c->f5E = 0x20;
        }
        else if (c->flags_0 & 2)
        {
            c->f5A = 1;
            c->f5E = 0x31;
            c->f60 = c->arr_2A[1];
            c->f58 = c->f8 - 1;
            c->f5C = c->f8 - 1;
        }
        else
        {
            c->f58 = 1;
            c->f5A = 1;
            c->f5C = 1;
            c->f5E = 0x10;
        }
        break;
    case 3:
        c->f5A = c->f5C = c->f8 - 1;
        if (c->f8 - 1 > 0)
            break;
    case 5:
    case 9:
        c->f5C = 1;
        c->f5A = 1;
        break;
    case 1:
        c->f60 = c->arr_2A[3];
        c->f62 = c->arr_46[0];
        v = sub_800AD308(0);
        if (v < 3)
            v = 3;
        c->f5C = v + 1;
        break;
    case 14:
        c->f60 = c->arr_2A[4];
        c->f62 = c->arr_46[1];
        v = sub_800AD79C();
        if (v < 4)
            v = 4;
        c->f5C = v;
        break;
    case 4:
        c->f60 = c->arr_2A[7];
        c->f62 = c->arr_46[2];
        v = CountMagicBits_8001AE54(sub_80010824(3, c->arr_2A[1]));
        if (v < 4)
            v = 4;
        c->f5C = v;
        break;
    case 13:
    {
        int n = c->fC;
        if (n >= 10)
        {
            short rows;
            int q = n / 3;
            rows = q;
            if (n % 3 != 0)
                rows = q + 1;
            c->f5C = rows - 2;
            c->f5A = rows - 2;
        }
        c->f60 = c->arr_2A[9];
        break;
    }
    case 11:
        c->f60 = c->arr_2A[10];
        break;
    case 2:
        c->f58 = 1;
        c->f5E = 2;
        c->f5A = c->f8;
        c->f5C = c->f8;
        break;
    }
}
INCLUDE_OVERLAY_ASM(menu, dword_800BBB7C);

int sub_800BFB10(MenuCtx* c)
{
    int n = *(unsigned short*)&c->f8 - 1;
    unsigned short fl = c->flags_0;
    if (fl & 1)
    {
        if ((short)n != 0)
        {
            c->f58 = n;
            c->f5C = n;
            c->f5A = 1;
            c->f5E = 0x31;
            c->f60 = c->arr_2A[1];
            c->flags_0 |= 2;
        }
        else
        {
            c->f58 = 1;
            c->f5A = 1;
            c->f5C = 1;
            c->f5E = 0x10;
            c->flags_0 |= 4;
        }
        c->flags_0 &= ~1;
        return 1;
    }
    if (fl & 2)
    {
        c->arr_2A[1] = c->f60;
        c->f58 = 1;
        c->f5A = 1;
        c->f5C = 1;
        c->f5E = 0x10;
        c->f60 = 0;
        c->flags_0 = (c->flags_0 & ~2) | 4;
        return 1;
    }
    return 0;
}

// Not matched: first block: original ORs the flags with a register holding 1 (or v1,v1,v0)
// and copies fl first; tried n = 1 / r = 1 temporaries, | n, return n (all give ori)
#if 0
int sub_800BFBE0(MenuCtx* c)
{
    int n = *(unsigned short*)&c->f8 - 1;
    unsigned short fl = c->flags_0;
    if (fl & 2)
    {
        c->f58 = 1;
        c->f5A = 1;
        c->f5C = 1;
        c->f5E = 0x20;
        c->f60 = 0;
        c->flags_0 = (fl & ~2) | 1;
        return 1;
    }
    if (fl & 4)
    {
        if ((short)n != 0)
        {
            c->f58 = n;
            c->f5C = n;
            c->f5A = 1;
            c->f5E = 0x31;
            c->f60 = c->arr_2A[1];
            c->flags_0 |= 2;
        }
        else
        {
            c->f58 = 1;
            c->f5A = 1;
            c->f5C = 1;
            c->f5E = 0x20;
            c->flags_0 |= 1;
        }
        c->flags_0 &= ~4;
        return 1;
    }
    return 0;
}
#endif
INCLUDE_OVERLAY_ASM(menu, sub_800BFBE0);

extern int name_8003D794();
extern void sub_800AD3F0();
extern int sub_800AD308();
void sub_800BFCA8(MenuCtx* c)
{
    if (c->sel_2 != 0)
    {
        name_8003D794(&c->f58, 0);
    }
    else
    {
        int r16 = 0;
        int x = name_8003D794(&c->f58, r16);
        if (x == 4)
            r16 = sub_800BFB10(c);
        else if (x == 3)
            r16 = sub_800BFBE0(c);
        if (r16)
            PlaySfx_80031494(0x7F);
    }
    if (c->f28 >= 8)
    {
        if (IsConfirmPressedP1_8003D380(0))
        {
            if (c->sel_2 == 0x10 && c->f60 == 1)
            {
                int v = c->f60;
                PlaySfx_80031494(0x7D);
                c->f1C = v;
            }
            else
            {
                c->f18 = 1;
            }
        }
        else if (IsCancelPressedP1_8003D41C(1))
        {
            c->f1C = 1;
        }
        else if ((padPressed_8009194C & 0x80) && c->sel_2 == 1)
        {
            int r;
            sub_800AD3F0(0);
            PlaySfx_80031494(0x7E);
            c->f62 = 0;
            c->f60 = 0;
            r = sub_800AD308(0);
            if (r < 3)
                r = 3;
            c->f5C = r + 1;
        }
    }
}

extern void sub_80020BF8();
extern void name_800C2EB4();
extern void name_800C47A8();
extern void sub_800BFF38();
extern void sub_800BFEC0();
void sub_800BFE18(MenuCtx* c)
{
    MenuTask* t = (MenuTask*)&name_8008D498->entry;
    switch (c->sel_2)
    {
    case 8:
        t->next_8 = sub_800BFF38;
        sub_80020BF8(2, 0xF);
        c->flags_0 |= 0x20;
        name_800C2EB4();
        break;
    case 10:
        t->next_8 = sub_800BFEC0;
        sub_80020BF8(2, 0x12);
        c->flags_0 |= 0x20;
        name_800C47A8(0);
        break;
    }
}

extern void AddClipDrawAreaPrim_80033308();
extern void sub_800C07F0();
extern int name_8008D678;
void sub_800BFEC0(MenuTask* t, int a)
{
    int x;
    x = a;
    if (name_8008D678 >= 0)
    {
        sub_800BFF84(x);
        t->next_8 = sub_800BD6C8;
    }
    else
    {
        AddClipDrawAreaPrim_80033308(pOT_8008D454 + 14);
        sub_800C07F0(x);
        AddClipDrawAreaPrim_80033308(pOT_8008D454 + 14);
    }
}

extern int name_800C45D8();
extern void sub_800BFF84();
void sub_800BFF38(MenuTask* t, int a)
{
    if (name_800C45D8() == 0)
    {
        sub_800BFF84(a);
        t->next_8 = sub_800BD6C8;
    }
}

void sub_800BFF84(MenuCtx* c)
{
    c->flags_0 &= ~0x20;
    sub_800BE25C(c);
    c->f10 = 0;
    {
        int v = name_800C1998[c->sel_2];
        c->f10 = v;
        c->f14 = v;
    }
    sub_800BF8B4(c);
    sub_800BE38C(c);
    DrawMenuBackground_8002BE10();
    sub_800BE4A0(c);
}

extern void sub_800A7714();
extern void sub_800BD40C();
void sub_800BFFFC(MenuTask* t)
{
    if (sub_800272D0() == 0)
    {
        if (name_800C29BC)
            sub_800A7714(0);
        sub_80027478(0x40, 0);
        sub_800A6D30(1);
        t->next_8 = sub_800BD40C;
        t->flags_0 = (t->flags_0 & ~1) | 0x8000;
    }
    eventDispatchHalt_8008B540 = 1;
}

extern void sub_80027478();
extern void sub_80027314();
extern void sub_800BFFFC();
void sub_800C0084(void)
{
    MenuTask* t = (MenuTask*)&name_8008D498->entry;
    sub_80027478(0x40, 1);
    FreeActiveOverlay_8002C014();
    sub_80027314();
    t->next_8 = sub_800BFFFC;
}

void sub_800C00D4(MenuObj* o, int a, int s)
{
    o->fC = 0;
    o->f0 = 0;
    o->f4 = a;
    o->fC |= 1 << s;
}

extern void sub_800127D0();
void sub_800C00F8(MenuObj* a, MenuStatDelta* b)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        int bit = 1 << i;
        if (a->fC & bit)
        {
            sub_800127D0(i, 0, -b->x_1C, 0);
            sub_800127D0(i, 2, -b->y_20, 0);
            sub_800127D0(i, 0x11, 0, b->f4);
            sub_800127D0(i, 0x10, 0, b->f8);
        }
    }
}

extern int name_800C1BBC[];
void sub_800C01AC(MenuObj* o)
{
    o->f10 = 0;
    o->f10 = name_800C1BBC[o->f60];
}

extern int name_800C1BD0[];
void sub_800C01D0(MenuObj* o)
{
    o->f10 = 0;
    o->f10 = name_800C1BD0[o->f60];
}

typedef struct MenuCell
{
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
} MenuCell;
extern MenuCell name_800C18EC;
extern void DrawScrollArrow_8002B3DC(MenuPair p, int t, void* pos, int ot);
typedef struct MenuItemGrid
{
    char pad_0[0xC];
    int count_C;
    char pad_10[0x2C];
    short scroll_3C;
} MenuItemGrid;
void DrawItemGrid_800C01F4(MenuItemGrid* c)
{
    MenuCell r;
    MenuPair pr;
    short pa[2];
    short pb[2];
    short i;
    short max;
    int n = c->count_C;
    if (n == 0)
        return;
    max = 0;
    if (n >= 10)
    {
        short rows;
        int q = n / 3;
        rows = q;
        if (n % 3 != 0)
            rows = q + 1;
        max = rows - 3;
    }
    for (i = 0; i < 9; i++)
    {
        if ((short)(i + c->scroll_3C * 3) < 12)
        {
            UnitStats* it;
            int k = i;
            unsigned short w = name_800C18EC.w;
            unsigned short h = name_800C18EC.h;
            int dx = w * (k % 3);
            int dy = h * (k / 3);
            r.w = w;
            r.h = h;
            r.x = name_800C18EC.x + dx;
            r.y = name_800C18EC.y + dy;
            it = GetSaveItem_80033AE4(&saveData_8008B570, k + c->scroll_3C * 3);
            if (it && it->species_5C != 0xD3)
                DrawUnitStatusWindow_8002F1C8(it, 0, 0, 0, &r, 0xE, 0);
        }
    }
    if (c->scroll_3C != 0)
    {
        pr.a = 2;
        pr.b = 3;
        pa[0] = 0xA0;
        pa[1] = 0x2D;
        DrawScrollArrow_8002B3DC(pr, frameCount_8008D3FC, pa, 0xE);
    }
    if (c->scroll_3C < max)
    {
        pr.a = 2;
        pr.b = 1;
        pb[0] = 0xA0;
        pb[1] = 0xC4;
        DrawScrollArrow_8002B3DC(pr, frameCount_8008D3FC, pb, 0xE);
    }
}

extern MenuQ name_800C1BE8[];
void sub_800C0428(MenuCtx* c)
{
    int found = 0;
    int sum = (unsigned short)c->arr_2A[3] + (unsigned short)c->arr_46[0];
    int is = c->sel_2 == 1;
    if (IsCircleHeldP1_8003D480() && is && c->f24 == 0)
    {
        int r = name_800AD288((short)sum, found);
        if (r < 0x2B)
        {
            DrawLargeTextBox_8002AF10(&name_800C1BE8[r], found, 0xE);
            found = 1;
        }
    }
    if (!found && c->f24 == 0)
    {
        int tmp[2];
        unsigned short u = 0;
        int a = 0;
        UnitStatus* r;
        if (c->sel_2 == 2)
        {
            u = c->arr_2A[5];
            sub_800C0CA4(c, tmp);
            a = tmp[0];
        }
        r = name_80014390(u & 0xFF);
        if (u == 0)
            DrawUnitStatusWindow_8002F1C8(r, a, 0, 0, name_800C18F4, 0xE, 2);
        else
            DrawUnitStatusWindow_8002F1C8(r, a, 0, 0, name_800C18F4, 0xE, 0);
    }
}

extern int sub_800C0990();
extern void DrawLevantStats_8002F7D0();
extern void DrawAnimatedWindow_8002BEC8();
extern char name_800C18C4[];
void sub_800C0578(MenuObj* o)
{
    int buf[2];
    short r[2];
    short s = sub_800C0990(o, 1);
    r[0] = 0xC2;
    r[1] = 0x31;
    DrawLevantStats_8002F7D0(r, 0xE);
    DrawAnimatedWindow_8002BEC8(buf, name_800C18C4, s, 0xE, 0, 0);
}

void sub_800C05E0(MenuCtx* c)
{
    int found = 0;
    int sum = (unsigned short)c->arr_2A[4] + (unsigned short)c->arr_46[1];
    int is = c->sel_2 == 0xE;
    if (IsCircleHeldP1_8003D480() && is && c->f24 == 0)
    {
        int r = (short)sub_800AD7F8((short)sum);
        if (r < 0x26)
        {
            DrawLargeTextBox_8002AF10(&name_800C1E98[r], found, 0xE);
            found = 1;
        }
    }
    if (!found && c->f24 == 0 && c->sel_2 != 0x10)
        DrawUnitStatusWindow_8002F1C8(&levantStatus_8008BD38, 0, 0, 0, name_800C18F4, 0xE, 2);
}

extern int name_8001AEC0();
extern MenuQ name_800C20F8[];
void sub_800C06E8(MenuCtx* c)
{
    int found = 0;
    int sum = (unsigned short)c->arr_2A[7] + (unsigned short)c->arr_46[2];
    Minion* m = GetMinion_80010598(3, c->arr_2A[1]);
    int is = c->sel_2 == 4;
    if (IsCircleHeldP1_8003D480() && is && c->f24 == 0)
    {
        int r = name_8001AEC0(&m->magicBits_F4, (short)sum);
        if (r < 0x1E)
        {
            DrawLargeTextBox_8002AF10(&name_800C20F8[r], found, 0xE);
            found = 1;
        }
    }
    if (!found && c->f24 == 0)
        DrawUnitStatusWindow_8002F1C8(&m->status_84, 0, 0, 0, name_800C18F4, 0xE, 0);

}

extern char name_800C2660[];
void sub_800C07F0(MenuCtx* c)
{
    MenuDlg d;
    int s;
    d = name_800BBB7C;
    s = sub_800C0990(c, 1);
    d.f4 = GetTime30Hz_8002C64C();
    d.f8 = (short)s;
    d.f10 = (int)name_800C2660;
    d.f0 &= ~7;
    if (c->sel_2 == 6)
        d.f0 |= 2;
    else
        d.f0 |= 4;
    d.fC = c->arr_2A[0];
    d.f8 = (short)s;
    DrawMenuWindows_8002A5A4(&d);
}

extern char name_800C2758[];
void sub_800C08C0(MenuCtx* c)
{
    MenuDlg d;
    int s;
    d = name_800BBB7C;
    s = sub_800C0990(c, 0x80);
    d.f4 = GetTime30Hz_8002C64C();
    d.f8 = (short)s;
    d.f10 = (int)name_800C2758;
    d.f0 &= ~7;
    if (c->sel_2 == 7)
        d.f0 |= 2;
    else
        d.f0 |= 4;
    d.fC = c->arr_2A[2];
    d.f8 = (short)s;
    DrawMenuWindows_8002A5A4(&d);
}

int sub_800C0990(MenuCtx* o, int m)
{
    if (m & o->f14)
        return 8;
    return o->f28;
}

typedef struct MenuWinItem
{
    unsigned short flags_0;
    short pad_2;
    void* data_4;
    SPRT** spr_8;
    DR_TPAGE** tp_C;
    short x_10;
    short y_12;
    char pad_14[8];
} MenuWinItem;
extern MenuWinItem* name_800C28C4[];
extern int GetKeyItemIcon_8001D344();
extern void DrawScrollArrow_8002C6DC();
extern char name_800C276C[];
extern char name_800C2770[];
void DrawKeyItemsWindow_800C09B0(MenuEquipQ* a)
{
    MenuDlg d;
    short i;
    short w;
    short saved = a->sel_0;
    int n;
    w = 8;
    for (i = 0; i < 4; i++)
    {
        int id = (short)sub_800AD7F8(i + a->scroll_2);
        int icon;
        void* nm;
        if (id < 0x26)
        {
            icon = GetKeyItemIcon_8001D344(id);
            nm = GetKeyItemName_8001D318(id);
        }
        else
        {
            icon = -1;
            nm = name_800B6838;
        }
        name_800C28C4[i][0].data_4 = (void*)icon;
        name_800C28C4[i][0].spr_8 = &publicTiySprts_8008D434;
        name_800C28C4[i][0].tp_C = &publicTiyTPages_8008D440;
        name_800C28C4[i][1].data_4 = nm;
        name_800C28C4[i][0].x_10 = 0x61;
        name_800C28C4[i][0].y_12 = i * 22 + 0x36;
        name_800C28C4[i][1].x_10 = 0x76;
        name_800C28C4[i][1].y_12 = i * 22 + 0x36;
        a->sel_0 = i;
        if (sub_800C0C3C(id) == 0)
        {
            name_800C28C4[i][0].flags_0 |= 2;
            name_800C28C4[i][1].flags_0 |= 2;
        }
        else
        {
            name_800C28C4[i][0].flags_0 &= ~2;
            name_800C28C4[i][1].flags_0 &= ~2;
        }
    }
    d.f0 = a->f4;
    d.f4 = frameCount_8008D3FC;
    d.f8 = w;
    d.fC = saved;
    d.f10 = (int)name_800C28C4;
    d.f14 = a->ot_6;
    DrawMenuWindows_8002A5A4(&d);
    SetFontClutOffset_8003F900(2, 0);
    n = sub_800AD79C();
    if (n < 4)
        n = 4;
    if (a->scroll_2 != 0)
        DrawScrollArrow_8002C6DC(name_800C276C, 3, a->ot_6);
    if (a->scroll_2 < n - 4 && n >= 5)
        DrawScrollArrow_8002C6DC(name_800C2770, 1, a->ot_6);
}


extern int sub_800A5E80();
extern int sub_800C1000();
// Not matched: compiler turns the tail into a boolean (sltu); also tried r = 1 / r = 0 tail,
// == 0 inverted tests, nested if (r), return r && sub_800C1000()
#if 0
int sub_800C0C3C(void* a)
{
    int r;
    if (a)
    {
        if (sub_8001D36C((int)a))
            return 1;
        r = sub_800A5E80(a);
    }
    else
    {
        r = sub_80034140();
    }
    if (r == 0)
        return 0;
    if (sub_800C1000())
        return 1;
    return 0;
}
#endif
INCLUDE_OVERLAY_ASM(menu, sub_800C0C3C);




extern int CheckItemOnTarget_80033DF4();
void sub_800C0CA4(MenuCtx* c, int* out)
{
    MenuTmp tmp;
    MenuQuad q;
    int r17;
    UnitStatus* r16;
    unsigned short u = c->arr_2A[5];
    r17 = name_800AD288(c->arr_2A[3] + c->arr_46[0], 0);
    r16 = name_80014390(u & 0xFF);
    q.a = r17;
    q.b = 0;
    q.c = u;
    q.d = 1;
    out[0] = 0;
    out[1] = 0;
    tmp.f8 = 1;
    sub_800C00D4(&tmp, r17, (short)u);
    tmp.f0 = 4;
    if (CheckItemOnTarget_80033DF4(&q) == 0 && sub_800C0DD4(r17))
    {
        int v;
        sub_80013C28(&levantStatus_8008BD38, r16, &tmp, &tmp.d_10);
        out[0] = -tmp.d_10.x_1C;
        out[1] = -tmp.d_10.y_20;
        v = r16->maxHp_A - r16->hp_8;
        if (v < out[0])
            out[0] = v;
        v = r16->maxMp_E - r16->mp_C;
        if (v < out[1])
            out[1] = v;
    }
}

int sub_800C0DD4(int a)
{
    switch (a)
    {
    case 0:
    case 1:
    case 2:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        return 1;
    }
    return 0;
}

typedef struct MenuEquipLine
{
    char pad_0[4];
    int f4;
    SPRT** sprts_8;
    DR_TPAGE** tpages_C;
    short x_10;
    short y_12;
    char pad_14[0xC];
    int icon_20;
    char pad_24[8];
    short x_2C;
    short y_2E;
    char pad_30[0xC];
    void* name_3C;
    char pad_40[8];
    short x_48;
    short y_4A;
} MenuEquipLine;
extern MenuEquipLine* name_800C18B0[];
extern int name_800C1754[];
extern int GetEquipmentName_8001D128();
void DrawEquipmentWindow_800C0E04(MenuEquipQ* a, short* pos, short c)
{
    MenuDlg d;
    short i;
    for (i = 0; i < 3; i++)
    {
        int icon;
        void* nm;
        int id = sub_800AD990(i);
        if (id != 0xFF)
        {
            icon = GetEquipmentIcon_8001D2D4(id, i);
            nm = (void*)GetEquipmentName_8001D128(id, i);
        }
        else
        {
            icon = -1;
            nm = name_800B6838;
        }
        name_800C18B0[i]->f4 = name_800C1754[i];
        name_800C18B0[i]->icon_20 = icon;
        name_800C18B0[i]->name_3C = nm;
        name_800C18B0[i]->sprts_8 = &uiTiySprts_8008D620;
        name_800C18B0[i]->tpages_C = &uiTiyTPages_8008D3F4;
        name_800C18B0[i]->x_10 = pos[0];
        name_800C18B0[i]->y_12 = pos[1] + i * 22;
        name_800C18B0[i]->x_2C = pos[0] + 0x32;
        name_800C18B0[i]->y_2E = pos[1] + i * 22;
        name_800C18B0[i]->x_48 = pos[0] + 0x47;
        name_800C18B0[i]->y_4A = pos[1] + i * 22;
    }
    d.f0 = a->f4;
    d.f4 = frameCount_8008D3FC;
    d.f8 = c;
    d.fC = a->sel_0;
    d.f10 = (int)name_800C18B0;
    d.f14 = a->ot_6;
    DrawMenuWindows_8002A5A4(&d);
    SetFontClutOffset_8003F900(2, 0);
}

extern int name_800C29B8;
extern int name_800B0EC0;
extern int sub_800A5E68();
int sub_800C1000(void)
{
    int v = name_800C29B8;
    if (v != 1)
        return 1;
    if (sub_800A5E68() == 0 && name_800B0EC0 == v)
        return 1;
    return 0;
}

INCLUDE_OVERLAY_ASM(menu, dword_800C1050);
