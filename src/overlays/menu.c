// MENU.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

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

typedef struct MenuSaveView
{
    char pad_0[0x814];
    unsigned int flags_814[1];
} MenuSaveView;

typedef struct MenuCtx
{
    unsigned short flags_0;
    short sel_2;
    short f4;
    short f6;
    int f8;
    int fC;
    int f10;
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
extern char name_800C18F4[];
extern void DrawLargeTextBox_8002AF10();
extern void sub_8002F1C8();

typedef struct MenuRc
{
    char pad_0[8];
    short x8;
    short xA;
    short xC;
    short xE;
} MenuRc;
extern int name_800AD288();
extern MenuRc* name_80014390();

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
extern void sub_800BD80C();

extern int sub_800AD7F8();
extern MenuQ name_800C1E98[];
extern int IsConfirmPressedP1_8003D380();
extern int IsCancelPressedP1_8003D41C();

extern int sub_800BFB10();
extern int sub_800BFBE0();
extern void PlaySfx_80031494();

typedef struct MenuTmp
{
    int w[14];
} MenuTmp;
extern void sub_80013C28();
extern void sub_800C00F8();
extern void sub_800C00D4();
extern void sub_800AD1E0();
extern void sub_800C0084();

extern char levantStatus_8008BD38[];

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
extern char* name_8008D498;
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

INCLUDE_OVERLAY_ASM(menu, sub_800BBB9C);

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
void sub_800BBE90(MenuTask* t, int a)
{
    int q = a;
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

INCLUDE_OVERLAY_ASM(menu, sub_800BBF48);

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

INCLUDE_OVERLAY_ASM(menu, sub_800BC2A8);

INCLUDE_OVERLAY_ASM(menu, sub_800BC56C);

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
    DrawWindow_80042460(rect, &b.col_8, (char*)pOT_8008D454 + 0x38, frameCount_8008D3FC);
}

extern int sub_8002FA0C();
void sub_800BC934(int a, int b)
{
    short rect[4];
    MenuBox bx;
    short r = sub_8002FA0C((short)b, (short)(a - 1));
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
        DrawWindow_80042460(rect, &bx.col_8, (char*)pOT_8008D454 + 0x38, frameCount_8008D3FC);
    }
}

typedef struct MenuPad
{
    int f0;
    char pad_4[0x40];
    short s44;
    char pad_46[0x16];
    int arr_5C[1];
} MenuPad;

typedef struct MenuPadB
{
    char pad_0[0x1F0];
    unsigned char b_1F0;
} MenuPadB;

// near miss: the original keeps 1 in a register (sllv) and hoists the saveData base out of the loop
#if 0
void sub_800BC9E8(MenuPad* p)
{
    short i;
    short s;
    if (p->s44 > 0)
    {
        for (i = 0; i < p->s44; i++)
        {
            int n = p->s44;
            if (i == n - 1)
            {
                if (p->f0 & (1 << n))
                {
                    if (IsConfirmPressedP1_8003D380(1) || IsCancelPressedP1_8003D41C(1))
                        p->f0 |= 0x40;
                    return;
                }
            }
            else if (p->f0 & (1 << (i + 1)))
            {
                continue;
            }
            s = i;
            if (p->arr_5C[s] > 0)
            {
                if (IsConfirmPressedP1_8003D380(1) || IsCancelPressedP1_8003D41C(1))
                {
                    int f = p->f0;
                    if (f & 0x20)
                    {
                        p->f0 = (f | (1 << (s + 1))) & ~0x20;
                    }
                    else if (s != 0)
                    {
                        p->f0 = f | 0x20;
                    }
                    else if (sub_800BBF10(((MenuPadB*)p)->b_1F0, ((unsigned char*)&saveData_8008B570)[0x80C]))
                    {
                        p->f0 |= 0x20;
                    }
                    else
                    {
                        p->f0 |= 2;
                    }
                }
            }
            else
            {
                p->f0 |= 1 << (s + 1);
            }
            return;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(menu, sub_800BC9E8);

INCLUDE_OVERLAY_ASM(menu, sub_800BCB98);

extern char name_800C1060[];
void sub_800BCEA0(char* a, int b, void* c, short d)
{
    short s[2];
    MenuCol col;
    if (c)
    {
        int i = d;
        Minion* m = GetMinion_80010598(3, i - 1);
        s[0] = 0x33;
        s[1] = 0x3E;
        sub_8002DB48(c, b, 0, s, m, a + 0x1AC + i * 72);
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
    char* r16 = (char*)GetMinion_80010598(3, x);
    sub_8001AEB8(name_800338B0(r16), r16 + 0x84, r17);
}

INCLUDE_OVERLAY_ASM(menu, sub_800BCFDC);

extern void sub_80034A84();
extern int* name_8008D640;
void sub_800BD1B0(MenuTask* t)
{
    int* p = name_8008D640;
    int f;
    DrawMenuBackground_8002BE10();
    f = p[4] & 0x8001;
    p += 4;
    if (f != 1)
        t->next_8 = sub_800BBF48;
    if (IsConfirmPressedP1_8003D380(1) || IsCancelPressedP1_8003D41C(1))
        sub_80034A84(p);
}

typedef struct MenuCtxB
{
    char pad_0[0x4C];
    int a_4C[3];
} MenuCtxB;

typedef struct MenuSlot
{
    char pad_0[3];
    unsigned char f3;
    char pad_4[4];
} MenuSlot;

typedef struct MenuEnt
{
    char pad_0[4];
    short s4;
    char pad_6[4];
    unsigned short a;
} MenuEnt;

extern MenuSlot name_800C29A0[];
extern MenuEnt name_800B1238[];
int sub_800BD230(MenuCtx* c)
{
    short i;
    int found = 0;
    for (i = 0; i < 3; i++)
    {
        name_800C29A0[i].f3 = 0xFF;
        ((MenuCtxB*)c)->a_4C[i] = 0;
    }
    for (i = 0; i < 3; i++)
    {
        MenuEnt* e = &name_800B1238[i];
        if (e->s4 != -1 && e->a != 7)
        {
            if (sub_800BD358(&name_800C29A0[i], e->s4))
            {
                ((MenuCtxB*)c)->a_4C[i] = 1;
                found = 1;
            }
        }
    }
    return found;
}

extern int rand();
extern MenuRow name_800C1080[];
int sub_800BD358(MenuCtx* out, int idx)
{
    MenuRow* r = &name_800C1080[idx];
    int found = 0;
    int a;
    int b;
    a = rand();
    b = rand();
    if (a < r->lim_0)
    {
        ((unsigned char*)out)[2] = r->a_2;
        ((unsigned char*)out)[3] = r->a_3;
        found = 1;
    }
    else if (b < r->lim_4)
    {
        ((unsigned char*)out)[2] = r->a_6;
        ((unsigned char*)out)[3] = r->a_7;
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

void sub_800BD634(void)
{
    int i;
    for (i = 0; i < 0xD3; i++)
    {
        if (sub_800BDD94(i) && (unsigned)(i - 0x25) >= 4)
        {
            int r = i / 32;
            int q = r;
            r = i - q * 32;
            ((MenuSaveView*)&saveData_8008B570)->flags_814[q] |= 1 << r;
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
        t->next_8 = sub_800BD80C;
}

INCLUDE_OVERLAY_ASM(menu, sub_800BD80C);

extern int sub_800B32D4();
extern int name_8007A170[];
int sub_800BDB74(int a)
{
    if (a < 0xC9)
        return name_8007A170[a];
    return sub_800B32D4(a - 0xC9);
}

int sub_800BDBB8(int a)
{
    int q = a / 32;
    int r = a - q * 32;
    return (((MenuSaveView*)&saveData_8008B570)->flags_814[q] & (1 << r)) != 0;
}

INCLUDE_OVERLAY_ASM(menu, sub_800BDBFC);

// Not matched: 1 word, the delay slot of the last bnez holds "li v0,1" in the original (the final
// fall-through returns no value); tried no final return, return;, uninitialised return var (gives
// move v0,a1), merged conditions, if/else chain into a variable
#if 0
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
    return 0;
}
#endif
INCLUDE_OVERLAY_ASM(menu, sub_800BDD94);

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
// near miss: gcc cross-jumps the 'moved = 1' tails differently from the original
#if 0
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
            moved = 1;
            if (c->flags_0 & 1)
                c->sel_2 = 6;
            else if (c->flags_0 & 2)
                c->sel_2 = 7;
            else
                c->sel_2 = 8;
            break;
        case 6:
            moved = 1;
            c->sel_2 = name_800C193C[c->f60];
            break;
        case 7:
            moved = 1;
            c->sel_2 = name_800C1948[c->f60];
            break;
        default:
            moved = 1;
            break;
        }
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
#endif
INCLUDE_OVERLAY_ASM(menu, sub_800BE048);

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

extern void sub_8002DB48();
void sub_800BEBFC(int* o, int a)
{
    Minion* m = 0;
    char* m2 = 0;
    short s[2];
    short x = *(unsigned short*)((char*)o + 0x2C) + *(unsigned short*)((char*)o + 0x4C);
    if (x < o[2] - 1)
    {
        m = GetMinion_80010598(3, x);
        m2 = (char*)m + 0x84;
    }
    s[0] = 0x33;
    s[1] = 0x3E;
    if (m)
        sub_8002DB48(m2, 0xE, a, s, m, 0);
}

void sub_800BEC8C(int unused, int a, short b)
{
    MenuCol t;
    t.col = uiColor_8008B590;
    t.c_2 = 1;
    t.c_3 = 1;
    DrawWindow_80042460(a, &t, &pOT_8008D454[b], frameCount_8008D3FC);
}

INCLUDE_OVERLAY_ASM(menu, sub_800BECE4);

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
extern void sub_8002F8E4();
// near miss: saved register assignment differs
#if 0
void sub_800BEFAC(MenuCtx* a, short b)
{
    MenuLoc loc;
    int v = sub_800C0990(a, 4);
    int j = 0;
    if (a->f8 - 1 > 0)
    {
        do
        {
            MenuRc* r18 = name_80014390((j + 1) & 0xFF);
            int r16;
            int r17;
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
            sub_8002F8E4(r18, &loc);
            AddClipDrawAreaPrim_80033308(&pOT_8008D454[b]);
            j++;
        } while ((short)j < a->f8 - 1);
    }
}
#endif
INCLUDE_OVERLAY_ASM(menu, sub_800BEFAC);

INCLUDE_OVERLAY_ASM(menu, sub_800BF0F4);

extern void sub_800AD1E0();
void sub_800BF3AC(MenuObj* o)
{
    sub_80011B24((int)o);
    sub_800AD1E0(o, 1, 0);
}

extern void sub_800A911C();
// near miss: original tests s == 0 via sltiu + bnez (one word more)
#if 0
void sub_800BF3E0(MenuCtx* c)
{
    MenuTmp tmp;
    int r17;
    MenuRc* p;
    int s;
    switch (c->sel_2)
    {
    case 2:
        r17 = name_800AD288((short)((unsigned short)c->arr_2A[3] + (unsigned short)c->arr_46[0]), 0);
        tmp.w[2] = 1;
        sub_800C00D4(&tmp, r17, c->arr_2A[5]);
        tmp.w[0] = 4;
        p = name_80014390(*(unsigned char*)&c->arr_2A[5]);
        if (p)
            sub_80013C28(levantStatus_8008BD38, p, &tmp, &tmp.w[4]);
        sub_800C00F8(&tmp, &tmp.w[4]);
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

INCLUDE_OVERLAY_ASM(menu, sub_800BF540);

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

INCLUDE_OVERLAY_ASM(menu, sub_800BF8B4);

// near miss: register allocation (context pointer ends up in a1 instead of a2)
#if 0
int sub_800BFB10(MenuCtx* c)
{
    unsigned short cnt = *(unsigned short*)&c->f8;
    int n = cnt - 1;
    if (c->flags_0 & 1)
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
    if (c->flags_0 & 2)
    {
        unsigned short t = c->f60;
        unsigned short fl = c->flags_0;
        c->f58 = 1;
        c->f5A = 1;
        c->f5C = 1;
        c->f5E = 0x10;
        c->f60 = 0;
        c->arr_2A[1] = t;
        c->flags_0 = (fl & ~2) | 4;
        return 1;
    }
    return 0;
}
#endif
INCLUDE_OVERLAY_ASM(menu, sub_800BFB10);

// Not matched: first block: original ORs the flags with a register holding 1 (or v1,v1,v0)
// and copies fl first; tried n = 1 / r = 1 temporaries (gives ori)
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
    MenuTask* t = (MenuTask*)(name_8008D498 + 0x10);
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
        AddClipDrawAreaPrim_80033308((char*)pOT_8008D454 + 0x38);
        sub_800C07F0(x);
        AddClipDrawAreaPrim_80033308((char*)pOT_8008D454 + 0x38);
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
    MenuTask* t = (MenuTask*)(name_8008D498 + 0x10);
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
void sub_800C00F8(MenuObj* a, int* b)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        int bit = 1 << i;
        if (a->fC & bit)
        {
            sub_800127D0(i, 0, -b[7], 0);
            sub_800127D0(i, 2, -b[8], 0);
            sub_800127D0(i, 0x11, 0, b[1]);
            sub_800127D0(i, 0x10, 0, b[2]);
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

INCLUDE_OVERLAY_ASM(menu, sub_800C01F4);

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
        MenuRc* r;
        if (c->sel_2 == 2)
        {
            u = c->arr_2A[5];
            sub_800C0CA4(c, tmp);
            a = tmp[0];
        }
        r = name_80014390(u & 0xFF);
        if (u == 0)
            sub_8002F1C8(r, a, 0, 0, name_800C18F4, 0xE, 2);
        else
            sub_8002F1C8(r, a, 0, 0, name_800C18F4, 0xE, 0);
    }
}

extern int sub_800C0990();
extern void sub_8002F7D0();
extern void DrawAnimatedWindow_8002BEC8();
extern char name_800C18C4[];
void sub_800C0578(MenuObj* o)
{
    int buf[2];
    short r[2];
    short s = sub_800C0990(o, 1);
    r[0] = 0xC2;
    r[1] = 0x31;
    sub_8002F7D0(r, 0xE);
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
        sub_8002F1C8(levantStatus_8008BD38, 0, 0, 0, name_800C18F4, 0xE, 2);
}

extern int name_8001AEC0();
extern MenuQ name_800C20F8[];
void sub_800C06E8(MenuCtx* c)
{
    int found = 0;
    int sum = (unsigned short)c->arr_2A[7] + (unsigned short)c->arr_46[2];
    char* m = (char*)GetMinion_80010598(3, c->arr_2A[1]);
    int is = c->sel_2 == 4;
    if (IsCircleHeldP1_8003D480() && is && c->f24 == 0)
    {
        int r = name_8001AEC0(m + 0xF4, (short)sum);
        if (r < 0x1E)
        {
            DrawLargeTextBox_8002AF10(&name_800C20F8[r], found, 0xE);
            found = 1;
        }
    }
    if (!found && c->f24 == 0)
        sub_8002F1C8(m + 0x84, 0, 0, 0, name_800C18F4, 0xE, 0);
}

extern char name_800C2660[];
// near miss: c and s swap their saved registers
#if 0
void sub_800C07F0(MenuCtx* c)
{
    int s;
    MenuDlg d;
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
    d.f8 = (short)s;
    d.fC = c->arr_2A[0];
    DrawMenuWindows_8002A5A4(&d);
}
#endif
INCLUDE_OVERLAY_ASM(menu, sub_800C07F0);

extern char name_800C2758[];
// near miss: c and s swap their saved registers
#if 0
void sub_800C08C0(MenuCtx* c)
{
    int s;
    MenuDlg d;
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
    d.f8 = (short)s;
    d.fC = c->arr_2A[2];
    DrawMenuWindows_8002A5A4(&d);
}
#endif
INCLUDE_OVERLAY_ASM(menu, sub_800C08C0);

int sub_800C0990(MenuCtx* o, int m)
{
    if (m & o->f14)
        return 8;
    return o->f28;
}

INCLUDE_OVERLAY_ASM(menu, sub_800C09B0);


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



typedef struct MenuQuad
{
    short a;
    short b;
    unsigned short c;
    short d;
} MenuQuad;

extern int sub_80033DF4();
void sub_800C0CA4(MenuCtx* c, int* out)
{
    MenuTmp tmp;
    MenuQuad q;
    int r17;
    MenuRc* r16;
    unsigned short u = c->arr_2A[5];
    r17 = name_800AD288(c->arr_2A[3] + c->arr_46[0], 0);
    r16 = name_80014390(u & 0xFF);
    q.a = r17;
    q.b = 0;
    q.c = u;
    q.d = 1;
    out[0] = 0;
    out[1] = 0;
    tmp.w[2] = 1;
    sub_800C00D4(&tmp, r17, (short)u);
    tmp.w[0] = 4;
    if (sub_80033DF4(&q) == 0 && sub_800C0DD4(r17))
    {
        int v;
        sub_80013C28(levantStatus_8008BD38, r16, &tmp, &tmp.w[4]);
        out[0] = -tmp.w[11];
        out[1] = -tmp.w[12];
        v = r16->xA - r16->x8;
        if (v < out[0])
            out[0] = v;
        v = r16->xE - r16->xC;
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

INCLUDE_OVERLAY_ASM(menu, sub_800C0E04);

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
