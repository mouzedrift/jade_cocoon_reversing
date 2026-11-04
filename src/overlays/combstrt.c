// COMBSTRT.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "combstrt.h"

typedef struct CombStrtTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombStrtTask;

typedef struct CombStrtBox
{
    short col_0;
    char c_2;
    char c_3;
} CombStrtBox;


typedef struct CombStrtWin
{
    int f0;
    void* text_4;
    int f8;
    int fC;
    short x_10;
    short y_12;
    int f14;
    int f18;
} CombStrtWin;

extern int dword_800A3A88;
extern unsigned int dword_8008D3FC;
extern unsigned short word_8008D3FC;
extern unsigned short uiColor_8008B590;
extern Minion dword_800A3AA0[2][3];
extern void sub_800A16FC();
extern int sub_800A1AAC(int);
extern int sub_800A1934(Minion*);
extern void PlaySfx_80031494(int);
extern void sub_8002ADB4(void*, void*, int, int);
extern void ShuffleTeam_800A473C(int);
extern void sub_800A49DC(int, int);

int dword_800A4088 SDATA = 21;
const char aShufflingMinion_800A408C[] = "\202r\202\210\202\225\202\206\202\206\202\214\202\211\202\216\202\207\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\217\202\222\202\204\202\205\202\222\201D\201D\201D"; // Shuffling minion order...
const char aStartFight_800A40C0[] = "\202r\202\224\202\201\202\222\202\224\201@\202\206\202\211\202\207\202\210\202\224\201H"; // Start fight?
const char aShuffleMinionOr_800A40DC[] = "\202r\202\210\202\225\202\206\202\206\202\214\202\205\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\217\202\222\202\204\202\205\202\222\201H"; // Shuffle minion order?
const char aAllowMinionChan_800A4108[] = "\202`\202\214\202\214\202\217\202\227\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\203\202\210\202\201\202\216\202\207\202\211\202\216\202\207\201H"; // Allow minion changing?
const int dword_800A4138[7] = { 0x10008, 36, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x14007A, 0x14004C, 0x40002 };
const int dword_800A4154[7] = { 0x10008, 0, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0, 0x140032, 0x40002 };

#if 0
// Not matched: CSE/regalloc of the %hi parts: the original keeps byte_800A4C14's high half in s2 from the != 3 test on and rematerialises word_800A4C8C's
typedef struct CombStrtMenu
{
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
} CombStrtMenu;
typedef struct CombStrtPos
{
    short s0;
    char pad_2[0xE];
    short x_10;
    short y_12;
} CombStrtPos;
typedef struct CombStrtCursor
{
    char pad_0[8];
    short sel_8;
} CombStrtCursor;
extern CombStrtWin name_800A4138;
extern CombStrtMenu dword_80082784;
extern CombStrtPos dword_80082708;
extern CombStrtPos dword_80082740;
extern char dword_800826E8[];
extern short word_800A4C00;
extern short word_800A4C8C;
extern unsigned short word_800A4BFC[];
extern CombStrtCursor name_800A4BF0;
extern void sub_800A48C0();
extern void sub_800A4958(int i);
extern void DrawMenuWindows_8002A5A4(void* p);
extern void DrawButtonHelpBar_8002B004(void* a, void* b, int c);
extern void DrawMenuBackground_8002BE10();
extern void UpdateMenuCursor_8003D794(void* p, int a);
void sub_800A4170(CombStrtTask* t, int a)
{
    CombStrtBox col;
    CombStrtWin w;
    int i;
    int old;
    w = name_800A4138;
    col.c_2 = 0;
    col.c_3 = 1;
    col.col_0 = uiColor_8008B590;
    sub_8002ADB4(&w, &col, 0xF, 0);
    sub_800A48C0();
    if (sub_800A1AAC(0) < 2u && sub_800A1AAC(1) < 2u)
    {
        if (byte_800A4C14 == 0xFF)
        {
            word_800A4BF8 = word_800A4C00;
        }
        byte_800A4C14 = 2;
    }
    else if (byte_800A4C14 == 0xFF)
    {
        byte_800A4C14 = 0;
    }
    for (i = 0; i < 2; i++)
    {
        sub_800A4958(i);
    }
    if (byte_800A4C14 != 3)
    {
        dword_80082784.f0 = 10;
        dword_80082784.f4 = GetTime30Hz_8002C64C();
        dword_80082784.f14 = 10;
        dword_80082708.s0 = 8;
        dword_80082740.s0 = 8;
        dword_80082708.x_10 = 0xC8;
        dword_80082708.y_12 = 0xC3;
        dword_80082740.x_10 = 0xF6;
        dword_80082740.y_12 = 0xC3;
        dword_80082784.f8 = word_800A4C8C;
        dword_80082784.fC = word_800A4BF8;
        DrawMenuWindows_8002A5A4(&dword_80082784);
        if (++word_800A4C8C >= 9)
        {
            word_800A4C8C = 8;
        }
    }
    DrawSmallTextBox_8002AF58((int)dword_800A4C04[byte_800A4C14], 0, 0xF);
    DrawButtonHelpBar_8002B004(dword_800826E8, 0, 0xF);
    DrawMenuBackground_8002BE10();
    UpdateMenuCursor_8003D794(&name_800A4BF0, 0);
    old = byte_800A4C14;
    dword_800A4C7C[old](t, a);
    if (old != byte_800A4C14)
    {
        name_800A4BF0.sel_8 = word_800A4BFC[byte_800A4C14];
    }
}
#endif
INCLUDE_OVERLAY_ASM(combstrt, sub_800A4170);

void sub_800A43FC()
{
    if (IsConfirmPressedP1_8003D380(1))
    {
        if (word_800A4BF8 == 0)
        {
            dword_800A3A88 |= 2;
        }
        else
        {
            dword_800A3A88 &= ~2;
        }
        if (sub_800A1AAC(0) >= 2u || sub_800A1AAC(1) >= 2u)
        {
            byte_800A4C14 = byte_800A4C14 + 1;
        }
        else
        {
            byte_800A4C14 = 2;
        }
    }
}

void sub_800A4498()
{
    if (IsConfirmPressedP1_8003D380(1) && word_800A4BF8 == 1)
    {
        byte_800A4C14 = byte_800A4C14 + 1;
    }
    else if (IsConfirmPressedP1_8003D380(1))
    {
        byte_800A4C14 = 3;
        word_800A4C94 = 0;
        word_800A4C92 = 0;
        word_800A4C90 = (word_8008D3FC & 0xF) + 0x2D;
    }
}

void sub_800A4524(CombStrtTask* t)
{
    if (IsConfirmPressedP1_8003D380(1) && word_800A4BF8 == 1)
    {
        t->next_8 = sub_800A16FC;
        dword_800A3A88 &= ~1;
    }
    else if (IsConfirmPressedP1_8003D380(1))
    {
        byte_800A4C14 = 1;
        dword_800A3A88 |= 1;
        t->next_8 = sub_800A16FC;
    }
}

void sub_800A45B8()
{
    short st = word_800A4C92;
    switch (st)
    {
    case 0:
        ShuffleTeams_800A46FC();
        if (word_800A4C90 < word_800A4C94++)
        {
            word_800A4C92 = 1;
            word_800A4C94 = 0;
            word_800A4C96 = 0;
            word_800A4C90 = ((dword_8008D3FC & 0x70) >> 4) + 5;
        }
        break;
    case 1:
        if (word_800A4C96 < word_800A4C94++)
        {
            word_800A4C92 = 2;
        }
        break;
    case 2:
        ShuffleTeams_800A46FC();
        word_800A4C92 = 1;
        word_800A4C94 = 0;
        if (word_800A4C90 < word_800A4C96++)
        {
            byte_800A4C14 = 2;
        }
        break;
    }
}

void ShuffleTeams_800A46FC()
{
    int i;
    for (i = 0; i < 2; i++)
    {
        ShuffleTeam_800A473C(i);
    }
    PlaySfx_80031494(0x7F);
}

extern int rand(void);
extern int PickNthFreeSlot_800A4878(int idx, int* arr, int n);
void ShuffleTeam_800A473C(int side)
{
    int used[10];
    int order[10];
    Minion tmp[10];
    int n = sub_800A1AAC(side);
    Minion* units = dword_800A3AA0[side];
    int i;
    if (n < 2)
    {
        return;
    }
    for (i = 0; i < n; i++)
    {
        used[i] = -1;
        order[i] = -1;
    }
    for (i = 0; i < n; i++)
    {
        order[i] = PickNthFreeSlot_800A4878(rand() % (n - i), used, n);
        MemCopy_800403E8(&tmp[i], &units[order[i]], 0xF8);
    }
    for (i = 0; i < n; i++)
    {
        MemCopy_800403E8(&units[i], &tmp[i], 0xF8);
    }
}

int PickNthFreeSlot_800A4878(int idx, int* arr, int n)
{
    int i;
    int cnt = 0;
    i = 0;
    for (; i < n; i++, arr++)
    {
        if (*arr < 0)
        {
            if (cnt == idx)
            {
                *arr = cnt;
                break;
            }
            cnt++;
        }
    }
    return i;
}

void sub_800A48C0()
{
    int i;
    int j;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 3; j++)
        {
            Minion* p = &dword_800A3AA0[i][j];
            if (sub_800A1934(p) == 0)
            {
                Heal_80011CD0(&p->status_84);
            }
        }
    }
}

void sub_800A4958(int i)
{
    CombStrtBox box;
    int j;
    box.c_3 = 1;
    box.c_2 = 0;
    box.col_0 = uiColor_8008B590;
    sub_8002ADB4(dword_800A4C50[i], &box, 0xF, 0);
    for (j = 0; j < 3; j++)
    {
        sub_800A49DC(i, j);
    }
}

#if 0
// Not matched: s0/s1 swapped between slot and side*3 (register allocation), the rest matches
extern CombStrtWin name_800A4154;
extern void sub_8002F078(void* a, void* b, int c, int d);
extern void sub_800A1844(void* a, void* b, int c);
extern void DrawWindow_80042460(void* a, void* b, void* c, int d);
void sub_800A49DC(int side, int slot)
{
    CombStrtBox c1;
    CombStrtWin w;
    short pos[4];
    CombStrtBox c2;
    RECT r1;
    short pos2[4];
    CombStrtBox c3;
    RECT r2;
    Minion* u = &dword_800A3AA0[side][slot];
    short* xy;
    if (sub_800A1934(u) != 1)
    {
        w = name_800A4154;
        w.text_4 = dword_800A4C58[slot];
        xy = dword_800A4C64[side][slot];
        w.x_10 = xy[0];
        w.y_12 = xy[1];
        c1.c_2 = 0;
        c1.c_3 = 1;
        c1.col_0 = saveData_8008B570.uiColor_20.i;
        sub_8002ADB4(&w, &c1, 0xF, 0);
        pos[0] = xy[0] + 0x2F;
        pos[1] = xy[1];
        sub_8002F078(&u->status_84, pos, 0, 0xF);
        c2.c_2 = 0;
        c2.c_3 = 1;
        c2.col_0 = saveData_8008B570.uiColor_20.i;
        r1.x = xy[0] + 0x32;
        r1.y = xy[1];
        r1.w = 0x5E;
        r1.h = 0x14;
        DrawWindow_80042460(&r1, &c2, pOT_8008D454 + 15, 0);
        pos2[0] = xy[0];
        pos2[1] = xy[1] + 0x14;
        sub_800A1844(u, pos2, 0);
        c3.c_2 = 0;
        c3.c_3 = 1;
        c3.col_0 = saveData_8008B570.uiColor_20.i;
        r2.x = xy[0];
        r2.y = xy[1] + 0x14;
        r2.w = 0x90;
        r2.h = 0x13;
        DrawWindow_80042460(&r2, &c3, pOT_8008D454 + 15, 0);
    }
}
#endif
INCLUDE_OVERLAY_ASM(combstrt, sub_800A49DC);

int dword_800A4BF0[2] = { 0x10002, 2 };
short word_800A4BF8 = 1;
int dword_800A4BFC = 1;
int dword_800A4C00 = 0;
const char *dword_800A4C04[4] = { aAllowMinionChan_800A4108, aShuffleMinionOr_800A40DC, aStartFight_800A40C0, aShufflingMinion_800A408C };
unsigned char byte_800A4C14 = 255;
int dword_800A4C18[7] = { 0x10008, 51, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x14000A, 0x140032, 0x40002 };
int dword_800A4C34[7] = { 0x10008, 223, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x140104, 0x140032, 0x40002 };
void *dword_800A4C50[2] = { (void *)dword_800A4C18, (void *)dword_800A4C34 };
int dword_800A4C58[3] = { 219, 115, 102 };
int dword_800A4C64[6] = { 0x40000A, 0x6D000A, 0x9A000A, 0x4000A6, 0x6D00A6, 0x9A00A6 };
void (*dword_800A4C7C[4])() = { sub_800A43FC, sub_800A4498, sub_800A4524, sub_800A45B8 };
int dword_800A4C8C = 0;
short word_800A4C90 = 0;
short word_800A4C92 = 0;
short word_800A4C94 = 0;
short word_800A4C96 = 0;
