// COMBCOM.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "minion_menu.h"

typedef struct CombComTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombComTask;

typedef struct CombComDlg
{
    int f0;
    int f4;
    int f8;
    int fC;
} CombComDlg;

// the battle command being chosen (COMBBTL's CombBtlCmd)
typedef struct CombComCmd
{
    int kind_0;
    int arg_4;
    int mask_8; // acting unit bits
    int targets_C; // target unit bits
} CombComCmd;

// a menu entry / window (0x38 bytes)
typedef struct CombComItem
{
    unsigned short flags;
    short pad_2;
    void* text_4;
    int f8;
    int fC;
    short x_10;
    short y_12;
    int rest[9];
} CombComItem;

// DrawMenuWindows_8002A5A4's argument
typedef struct CombComMenu
{
    int f0;
    int time_4;
    int f8;
    int sel_C;
    void* items_10;
    int f14;
} CombComMenu;

extern short dword_800CD298[]; // menu cursors (GetMenuCursorIndex_8003DA54)
extern short dword_800CD2A4[];
extern unsigned char byte_800CD839;
extern unsigned char byte_800CD83C;
extern unsigned char byte_800CD844;
extern unsigned char byte_800A85BD;
extern unsigned char dword_800A4078[];
extern short word_800CD2A8;
extern short word_800CD28C[];
extern unsigned short word_800CD3CC;
extern char dword_800CD468[];
extern void* dword_800CD490;
extern void* dword_800CD414;
extern char dword_800CD3CC[];
extern int dword_800A3A88;
extern int sub_800A11BC(int);
extern int sub_800A1AAC(int);
extern int GetMenuCursorIndex_8003DA54(void*);
extern int CountMagicBits_8001AE54(int);
extern int FindNthMagicBit_8001AEC0(int, int);

INCLUDE_OVERLAY_ASM(combcom, dword_800C9E88);

extern EventNode* dword_8008D614;
extern CombComCmd* dword_800CD840;
extern int dword_800CD848;
extern unsigned char byte_800A38D8;
extern unsigned char byte_800A38DC;
extern unsigned char byte_800CD83A;
extern unsigned char byte_800CD838;
extern unsigned char byte_800CD845;
extern unsigned char byte_800CD850;
extern unsigned short padPressed_8009194C[];
extern unsigned char byte_800CD83B;
extern int dword_800CD84C;
extern void sub_800CD16C();
extern int dword_800CD83C;
extern unsigned char byte_800A85BC;
extern short word_800A82D0;
extern short word_800A82D2;
extern void sub_800CB88C();
extern void sub_800CB924();

EventEntry* sub_800CB7AC(int a, int b)
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D614);
    if (e)
    {
        e->cb_8 = (EventEntryFn)sub_800CD16C;
        dword_800CD840 = (CombComCmd*)a;
        byte_800CD839 = b;
        e->flags = (e->flags | 1) & ~0x8000;
        if (!b)
        {
            dword_800CD848 = 0;
        }
        else
        {
            dword_800CD848 = byte_800A38D8;
        }
        byte_800A38DC = 0;
        byte_800CD83A = 0;
        byte_800CD850 = 0;
        byte_800CD838 = 0;
        byte_800CD844 = 4;
        byte_800CD845 = 0;
        sub_800CB88C();
        sub_800CB924();
    }
    return e;
}

void sub_800CB88C()
{
    if (CountMagicBits_8001AE54(sub_800A11BC(byte_800CD839)) >= 5)
    {
        word_800CD2A8 = CountMagicBits_8001AE54(sub_800A11BC(byte_800CD839));
    }
    if (dword_800A3A88 & 2)
    {
        word_800CD28C[1] = 3;
        word_800CD28C[2] = 5;
        dword_800CD414 = dword_800CD3CC;
    }
}

void sub_800CB924()
{
    if (sub_800A1AAC(byte_800CD839) == 1)
    {
        dword_800CD490 = dword_800CD468;
        word_800CD3CC |= 2;
    }
}

extern short dword_800CD2BC[];
extern short dword_800CD2B0[];
extern short* dword_800CD2D4[];

short* sub_800CB974(int a)
{
    a &= 0xFF;
    if (a == 3)
    {
        if ((byte_800CD844 & 1) == 0)
        {
            if ((byte_800CD844 & 4) == 0)
            {
                if ((short)GetMenuCursorIndex_8003DA54(word_800CD28C) == 4)
                {
                    dword_800CD2BC[2] = sub_800A1AAC(byte_800CD839) - 1;
                    return dword_800CD2BC;
                }
            }
        }
        return dword_800CD2B0;
    }
    return dword_800CD2D4[a];
}

extern unsigned int dword_800CD41C[];
extern short word_800CD294;
extern short word_800CD434[];
extern CombComItem* dword_800CD404[];

void sub_800CBA20(int a)
{
    int i;
    int off;
    a &= 0xFF;
    if (a == 0)
    {
        dword_800CD41C[0] = 2;
    }
    else
    {
        dword_800CD41C[0] = 4;
    }
    dword_800CD41C[1] = GetTime30Hz_8002C64C();
    if (dword_800CD41C[2] < 8)
    {
        dword_800CD41C[2]++;
    }
    off = byte_800CD839;
    dword_800CD41C[3] = word_800CD294;
    for (i = 0; i < 5; i++)
    {
        dword_800CD404[i]->x_10 = word_800CD434[i] + off * 192;
    }
}

void sub_800CBAD4(int a)
{
    if ((a & 0xFF) != 3)
    {
        byte_800A85BD = dword_800A4078[byte_800CD839 * 4];
    }
    else if (byte_800CD844 & 5)
    {
        byte_800A85BD = dword_800A4078[byte_800CD839 * 4];
    }
    else
    {
        byte_800A85BD = byte_800CD83C;
    }
}

extern int MeasureTextWidth_8003E4C8(int);

void sub_800CBB4C(int p)
{
    RECT a;
    short b[2];
    int d;
    int w;
    a.w = w = MeasureTextWidth_8003E4C8(p) + 4;
    a.h = 0x12;
    if (byte_800CD839 == 1)
    {
        a.x = 0xDD - w;
    }
    else
    {
        a.x = 0x5F;
    }
    a.y = 0xC1;
    b[1] = 0xC3;
    b[0] = a.x + 2;
    d = p;
    DrawTextBox_8002AFA0((int)&d, (int)b, 0xF, &a, 1);
}

void sub_800CBBE0(int p)
{
    short v[2] = {0xA, 0x14};
    CombComDlg d;
    d.f0 = p;
    d.f4 = 0;
    d.f8 = 0;
    d.fC = 0;
    DrawLargeTextBox_8002AF10((int)&d, (int)v, 0xF);
}

int sub_800CBC28()
{
    return MenuIndexToSkillSlot_80031BDC((short)GetMenuCursorIndex_8003DA54(dword_800CD298));
}

int sub_800CBC58()
{
    int r = sub_800A11BC(byte_800CD839);
    return FindNthMagicBit_8001AEC0(r, (short)GetMenuCursorIndex_8003DA54(dword_800CD2A4));
}

typedef struct CombComColor
{
    unsigned short color;
    unsigned char a;
    unsigned char b;
} CombComColor;
extern CombComItem name_800CB4F0;
extern CombComItem name_800CB528;
extern CombComItem name_800CB560;
extern CombComItem name_800CB598;
extern CombComMenu name_800CB5D0;
extern short word_800CD2D0;
extern unsigned short uiColor_8008B590;
extern void* memset(void* p, int c, unsigned int n);
extern void DrawMenuItemWithWindow_8002ADB4(void* a, void* b, int c, int d);
extern void DrawMenuWindows_8002A5A4(void* p);
void sub_800CBCA0()
{
    CombComColor col;
    CombComItem a;
    CombComItem b;
    CombComItem c;
    CombComItem d;
    void* list[4];
    CombComMenu m;
    a = name_800CB4F0;
    b = name_800CB528;
    c = name_800CB560;
    d = name_800CB598;
    memset(list, 0, 0x10);
    m = name_800CB5D0;
    list[0] = &b;
    list[1] = &c;
    list[2] = &d;
    col.color = uiColor_8008B590;
    col.a = 0;
    col.b = 1;
    DrawMenuItemWithWindow_8002ADB4(&a, &col, 0, GetTime30Hz_8002C64C());
    m.time_4 = GetTime30Hz_8002C64C();
    m.items_10 = list;
    m.sel_C = word_800CD2D0;
    DrawMenuWindows_8002A5A4(&m);
}

typedef struct CombComMsg
{
    int* f0;
    int* text;
} CombComMsg;
extern CombComMsg name_800CD46C[];
extern char dword_800CD2C8[];
extern short* dword_800CD854;
extern char name_800CD718[];
extern CombComDlg name_800CD538[];
typedef struct CombComMsgs3
{
    int m[3];
} CombComMsgs3;
extern CombComMsgs3 name_800CB674;
typedef struct CombComPos2
{
    short xy[2][2];
} CombComPos2;
extern CombComPos2 name_800CB680;
extern CombComPos2 name_800CB688;
extern unsigned short name_800CD820[][2]; // per byte_800CD83A and window: which windows to hide
extern unsigned char byte_800A84A8;
extern unsigned int dword_800CD41C[];
extern char* name_800CD50C[];
extern int DrawAbilityDescription_8002C670();
extern void DrawAbilityList_8002CE28(struct_minion_ref* a0, void* a1);
extern void DrawMagicList_8002CAC8(struct_minion_ref* a0, void* a1);
extern int GetSkillMpCost_80031A04(void* skills, int a);
extern void DrawButtonHelpBar_8002B004(void* p, int a, int b);
extern void sub_800CC40C();
// Matched
void sub_800CBEA4()
{
    short w[2];
    int shown;
    int k;
    int f;
    shown = 0;
    word_800A82D0 = 0;
    word_800A82D2 = 0;
    if (IsCircleHeld_8003D45C(dword_800CD848))
    {
        if (byte_800CD83A == 0)
        {
            sub_800CBB4C(*name_800CD46C[(short)GetMenuCursorIndex_8003DA54(word_800CD28C)].f0);
            shown = 1;
        }
        else if (byte_800CD83A == 1)
        {
            short p[2];
            Minion* m;
            shown = 1;
            m = sub_800A11D8(byte_800CD839);
            p[0] = 10;
            p[1] = 0x14;
            DrawAbilityDescription_8002C670(m, p, name_800CD718, (short)GetMenuCursorIndex_8003DA54(dword_800CD298), 0xF);
        }
        else if (byte_800CD83A == 2)
        {
            if (sub_800CBC58() < 0x1E)
            {
                short p[2];
                p[0] = 10;
                p[1] = 0x14;
                DrawLargeTextBox_8002AF10((int)&name_800CD538[sub_800CBC58()], (int)p, 0xF);
                shown = 1;
            }
        }
        else if (byte_800CD83A == 5)
        {
            CombComMsgs3 t;
            t = name_800CB674;
            sub_800CBB4C(t.m[(short)GetMenuCursorIndex_8003DA54(dword_800CD2C8)]);
            shown = 1;
        }
    }
    if (shown)
    {
        k = 1;
    }
    else
    {
        k = byte_800CD838;
    }
    w[0] = dword_800CD840->arg_4;
    w[1] = byte_800CD839;
    if (!(name_800CD820[byte_800CD83A][k] & 0x10))
    {
        if (byte_800CD844 & 1)
        {
            f = -1;
        }
        else
        {
            f = (short)GetMenuCursorIndex_8003DA54(dword_800CD854);
        }
        if ((short)GetMenuCursorIndex_8003DA54(word_800CD28C) == 3)
        {
            if (byte_800CD844 & 2)
            {
                dword_800CD83C = sub_800CC674(w, 1, f, 0xF);
            }
            sub_800CC40C();
        }
        else if ((short)GetMenuCursorIndex_8003DA54(word_800CD28C) == 6)
        {
            sub_800CC40C();
        }
        else if ((short)GetMenuCursorIndex_8003DA54(word_800CD28C) == 4)
        {
            dword_800CD83C = sub_800CC674(w, 3, f, 0xF);
        }
    }
    if (name_800CD820[byte_800CD83A][k] & 1)
    {
        byte_800A84A8 |= 0xC;
    }
    else
    {
        byte_800A84A8 &= 0xF3;
    }
    if (!(name_800CD820[byte_800CD83A][k] & 4))
    {
        DrawMenuWindows_8002A5A4(dword_800CD41C);
    }
    if (!(name_800CD820[byte_800CD83A][k] & 0x40))
    {
        struct_minion_ref r;
        CombComPos2 p;
        p = name_800CB680;
        r.field_4 = 2;
        r.ot_6 = 0xF;
        r.field_8 = -1;
        r.cursor_0 = dword_800CD298[4];
        r.scroll_2 = dword_800CD298[5];
        r.minion_C = sub_800A11D8(byte_800CD839);
        r.field_A = 0;
        DrawAbilityList_8002CE28(&r, p.xy[byte_800CD839]);
        word_800A82D2 = -GetSkillMpCost_80031A04(&r.minion_C->skills_DE, MenuIndexToSkillSlot_80031BDC((short)GetMenuCursorIndex_8003DA54(dword_800CD298)));
    }
    if (!(name_800CD820[byte_800CD83A][k] & 0x80))
    {
        struct_minion_ref r;
        CombComPos2 p;
        p = name_800CB688;
        r.field_4 = 2;
        r.ot_6 = 0xF;
        r.field_8 = -1;
        r.cursor_0 = dword_800CD2A4[4];
        r.scroll_2 = dword_800CD2A4[5];
        r.minion_C = sub_800A11D8(byte_800CD839);
        r.field_A = 0;
        DrawMagicList_8002CAC8(&r, p.xy[byte_800CD839]);
        word_800A82D2 = -GetMagicMpCost_8001AC58(FindNthMagicBit_8001AEC0((int)&r.minion_C->magicBits_F4, (short)GetMenuCursorIndex_8003DA54(dword_800CD2A4)));
    }
    if (byte_800CD83A == 5)
    {
        sub_800CBCA0();
    }
    DrawButtonHelpBar_8002B004(name_800CD50C[byte_800CD83A], 0, 0xF);
}

#if 0
// Not matched: scheduling of the three word_800A82D0/2 -= pairs (the original reloads the globals before the third pair) and the 1 constant hoist; masks need separate statements to keep sllv+and

extern int sub_80012BB0(void* a, void* b, void* c, int* d);
extern int sub_80013228(void* a, void* b, void* c, int* d);
extern int sub_80034068(short* p);
void sub_800CC40C()
{
    short arg[4];
    int out[10];
    unsigned int i;
    UnitStatus* src;
    UnitStatus* t;
    if (byte_800CD83A == 3)
    {
        word_800A82D0 = 0;
        word_800A82D2 = 0;
        src = sub_80014390((unsigned char)(byte_800CD839 + 8));
        for (i = 0; i < 2; i++)
        {
            int bit = 1 << (i + 8);
            if (dword_800CD840->targets_C & bit)
            {
                t = sub_80014390((unsigned char)(i + 8));
                sub_80012BB0(src, t, dword_800CD840, out);
                if (!sub_80013228(src, t, dword_800CD840, out))
                {
                    bit = 1 << i;
                    if (dword_800CD840->mask_8 & bit)
                    {
                    word_800A82D0 -= out[3];
                    word_800A82D2 -= out[4];
                    word_800A82D0 -= out[5];
                    word_800A82D2 -= out[6];
                    word_800A82D0 -= out[7];
                    word_800A82D2 -= out[8];
                    if (t->maxHp_A - t->hp_8 < word_800A82D0)
                    {
                        word_800A82D0 = t->maxHp_A - t->hp_8;
                    }
                    if (t->maxMp_E - t->mp_C < word_800A82D2)
                    {
                        word_800A82D2 = t->maxMp_E - t->mp_C;

                    }
                    }
                }
            }
        }
        arg[0] = dword_800CD840->arg_4;
        arg[1] = byte_800CD839 + 8;
        arg[2] = dword_800CD83C;
        arg[3] = 0;
        if ((short)GetMenuCursorIndex_8003DA54(word_800CD28C) == 6)
        {
            ((int (*)(short*))sub_80034124)(arg);
        }
        else if ((short)GetMenuCursorIndex_8003DA54(word_800CD28C) == 7 && sub_80034068(arg))
        {
            word_800A82D0 = 0;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(combcom, sub_800CC40C);

#if 0
// Not matched: register allocation only (44 words): the original gives the list pointer s1 and mode/k s3, f/i s2
extern CombComItem name_800CB690;
extern CombComItem name_800CB6C8;
extern CombComItem name_800CB700;
extern Minion dword_800A3AA0[][3];
extern int sub_800A1934(Minion* p);
extern int sub_800A1958(Minion* p);
extern int sub_80034068(short* p);
int sub_800CC674(short* arg, int mode, int sel, int f)
{
    CombComItem w[3];
    CombComItem* list[4];
    CombComItem* items[3];
    CombComMenu m;
    short q[2];
    int res;
    int i;
    int k;
    short x;
    Minion* u;
    CombComItem* p0;
    CombComItem* it;
    CombComItem** pk;
    CombComItem** pi;
    w[0] = name_800CB690;
    w[1] = name_800CB6C8;
    w[2] = name_800CB700;
    pk = list;
    memset(pk, 0, 0x10);
    memset(items, 0, 0xC);
    p0 = &w[0];
    m = name_800CB5D0;
    items[1] = &w[1];
    items[0] = p0;
    items[2] = &w[2];
    m.f14 = f;
    x = byte_800CD839 * 62 + 100;
    w[0].x_10 = x;
    w[1].x_10 = x;
    w[2].x_10 = x;
    m.time_4 = GetTime30Hz_8002C64C();
    m.sel_C = sel;
    m.items_10 = pk;
    q[0] = arg[0];
    res = 0;
    if (mode == 1)
    {
        {
            UnitStatus* s = sub_80014390((unsigned char)(((unsigned char*)arg)[2] + 8));
            list[0] = p0;
            p0->text_4 = s->name_10;
        }
        q[1] = arg[1] + 8;
        if (sub_80034068(q) == 0)
        {
            list[0]->flags &= ~2;
        }
        else
        {
            list[0]->flags |= 2;
        }
        res = ((int*)dword_800A4078)[arg[1]];
    }
    else
    {
        pi = pk;
        for (k = i = 0; i < 3; i++)
        {
            u = &dword_800A3AA0[arg[1]][i];
            if (i != ((int*)dword_800A4078)[byte_800CD839] && sub_800A1934(u) == 0)
            {
                it = items[k];
                *pk = it;
                it->text_4 = u->status_84.name_10;
                if (sub_800A1958(u))
                {
                    (*pk)->flags |= 2;
                }
                else
                {
                    (*pk)->flags &= ~2;
                }
                if (sel == k)
                {
                    res = i;
                }
                pk++;
                k++;
            }
            else
            {
                *pi = 0;
            }
            pi++;
        }
    }
    DrawMenuWindows_8002A5A4(&m);
    return res;
}
#endif
INCLUDE_OVERLAY_ASM(combcom, sub_800CC674);

void sub_800CC9FC()
{
    byte_800A85BC = dword_800CD83C;
    if (dword_800CD840->kind_0 == 0x12)
    {
        dword_800CD840->targets_C = 0;
        sub_80014390((unsigned char)(byte_800CD839 + 8))->status_0 |= 0x8000;
    }
    else
    {
        if (dword_800CD840->kind_0 == 1 && byte_800CD839 != dword_800CD83C)
        {
            return;
        }
        if (dword_800CD840->kind_0 == 8)
        {
            dword_800CD840->targets_C = 0;
        }
    }
}


extern short* dword_800CD854;
extern CombComMsg name_800CD46C[];
extern int dword_800CD454;
extern int dword_800CD458;
extern int dword_800CD460;
extern Minion dword_800A3AA0[][3];
extern int sub_800A1958(Minion* p);
extern int CheckSkillUsable_80033C98(struct_minion_ref* p);
extern int CheckMagicCastable_80033C08(struct_minion_ref* p);
int sub_800CCA94()
{
    struct_minion_ref a;
    short b[4];
    int idx = GetMenuCursorIndex_8003DA54(dword_800CD854);
    int* p;
    a.cursor_0 = dword_800CD854[4];
    dword_800CD84C = 0;
    a.scroll_2 = dword_800CD854[5];
    a.field_A = 0;
    b[3] = 0;
    b[0] = dword_800CD840->arg_4;
    b[1] = byte_800CD839 + 8;
    b[2] = dword_800CD83C;
    switch (byte_800CD83A)
    {
    case 0:
        p = name_800CD46C[(short)idx].text;
        if (p == 0)
        {
            return 1;
        }
        dword_800CD84C = *p;
        return 0;
    case 1:
        a.minion_C = sub_800A11D8(byte_800CD839);
        switch (CheckSkillUsable_80033C98(&a))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 6:
            return 1;
        case 5:
            dword_800CD84C = dword_800CD458;
            return 0;
        case 7:
            return 0;
        }
        break;
    case 2:
        a.minion_C = sub_800A11D8(byte_800CD839);
        switch (CheckMagicCastable_80033C08(&a))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 7:
            return 1;
        case 5:
            dword_800CD84C = dword_800CD458;
            return 0;
        case 6:
            return 0;
        }
        break;
    case 3:
        if ((short)GetMenuCursorIndex_8003DA54(word_800CD28C) == 2)
        {
            switch ((unsigned int)((int (*)(short*))sub_80034124)(b))
            {
            case 0:
                return 1;
            case 3:
                dword_800CD84C = dword_800CD460;
                return 0;
            case 4:
                dword_800CD84C = dword_800CD454;
                return 0;
            }
            return 0;
        }
        else if ((short)GetMenuCursorIndex_8003DA54(word_800CD28C) == 3)
        {
            switch ((unsigned int)sub_80034068(b))
            {
            case 0:
                return 1;
            case 3:
                dword_800CD84C = dword_800CD460;
                return 0;
            case 4:
                dword_800CD84C = dword_800CD454;
                return 0;
            }
            return 0;
        }
        else if ((short)GetMenuCursorIndex_8003DA54(word_800CD28C) == 4)
        {
            if (sub_800A1958(&dword_800A3AA0[byte_800CD839][dword_800CD83C]))
            {
                dword_800CD84C = dword_800CD454;
                return 0;
            }
        }
        break;
    case 4:
    case 5:
        return 1;
    }
    return 1;
}

int sub_800CCD84()
{
    if ((byte_800CD844 & 4) == 0)
    {
        return 1 << (byte_800CD839 + 8);
    }
    return 1 << ((byte_800CD839 ^ 1) + 8);
}

extern unsigned char byte_800CD494[];
extern unsigned char byte_800CD49C[];
extern int dword_800CD524[];
extern char dword_800CD2C8[];
extern int sub_800A11A0(int);
extern int sub_80031B0C(int, int);
extern int GetMagicTargetFlags_8001ACE4(int);
void sub_800CCDD0()
{
    int v;
    byte_800CD850 = byte_800CD83A;
    switch (byte_800CD83A)
    {
    case 0:
        byte_800CD844 = byte_800CD494[(short)GetMenuCursorIndex_8003DA54(word_800CD28C)];
        byte_800CD83A = byte_800CD49C[(short)GetMenuCursorIndex_8003DA54(word_800CD28C)];
        dword_800CD840->kind_0 = dword_800CD524[(short)GetMenuCursorIndex_8003DA54(word_800CD28C)];
        break;
    case 1:
        v = sub_800A11A0(byte_800CD839);
        byte_800CD844 = sub_80031B0C(v, sub_800CBC28());
        byte_800CD83A = 4;
        dword_800CD840->arg_4 = sub_800CBC28();
        break;
    case 2:
        byte_800CD844 = GetMagicTargetFlags_8001ACE4(sub_800CBC58());
        if (byte_800CD844 & 2)
        {
            byte_800CD83A = 3;
        }
        else
        {
            byte_800CD83A = 4;
        }
        dword_800CD840->arg_4 = sub_800CBC58();
        break;
    case 3:
        byte_800CD83A = 4;
        break;
    case 5:
        switch ((short)GetMenuCursorIndex_8003DA54(dword_800CD2C8))
        {
        case 0:
            byte_800CD850 = 0;
            byte_800CD83A = 0;
            break;
        case 1:
            byte_800A38DC = 1;
            break;
        case 2:
            byte_800A38DC = 2;
            break;
        }
        break;
    }
    dword_800CD840->targets_C = sub_800CCD84();
}

extern int sub_800CCA94();
extern void sub_800CCDD0();
void sub_800CCFCC(EventEntry* e)
{
    if (IsConfirmPressed_8003D288(0, dword_800CD848))
    {
        if (sub_800CCA94())
        {
            PlaySfx_80031494(0x7E);
            sub_800CCDD0();
            if (byte_800A38DC)
            {
                e->flags = (e->flags & ~1) | 0x8000;
            }
        }
        else
        {
            PlaySfx_80031494(0x7C);
            if (dword_800CD84C)
            {
                byte_800CD83B = 0x96;
                byte_800CD838 = 1;
            }
        }
    }
    else if (IsCancelPressed_8003D3C0(0, dword_800CD848))
    {
        if (byte_800CD83A)
        {
            PlaySfx_80031494(0x7D);
            byte_800CD83A = byte_800CD850;
            byte_800CD850 = 0;
        }
    }
}

void sub_800CD0C8()
{
    if (padPressed_8009194C[dword_800CD848])
    {
        byte_800CD83B = 0;
    }
    if (byte_800CD83B == 0)
    {
        byte_800CD838 = 0;
    }
    else
    {
        byte_800CD83B--;
    }
    if (dword_800CD84C)
    {
        if (byte_800CD83A == 0)
        {
            sub_800CBB4C(dword_800CD84C);
        }
        else
        {
            sub_800CBBE0(dword_800CD84C);
        }
    }
}

extern short* dword_800CD854;
extern void (*dword_800CD818[])(EventEntry*, void*);
extern unsigned char byte_800A84A8;
extern int UpdateMenuCursor_8003D794(void* p, int a1);
extern void sub_800CBEA4();
void sub_800CD16C(EventEntry* e, void* buf)
{
    short* m = sub_800CB974(byte_800CD83A);
    dword_800CD854 = m;
    UpdateMenuCursor_8003D794(m, dword_800CD848);
    if (padPressed_8009194C[dword_800CD848] & 0x800)
    {
        byte_800CD83A = 5;
    }
    sub_800CBA20(byte_800CD83A);
    sub_800CBEA4();
    sub_800CBAD4(byte_800CD83A);
    dword_800CD818[byte_800CD838](e, buf);
    if (byte_800CD83A == 4)
    {
        byte_800A84A8 &= 0xF3;
        sub_800CC9FC();
        word_800A82D0 = 0;
        word_800A82D2 = 0;
        e->flags = (e->flags & ~1) | 0x8000;
    }
}

INCLUDE_OVERLAY_ASM(combcom, dword_800CD28C);
