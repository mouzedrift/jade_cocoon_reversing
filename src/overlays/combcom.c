// COMBCOM.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

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

extern char dword_800CD298[];
extern char dword_800CD2A4[];
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

extern int dword_8008D614;
extern CombComDlg* dword_800CD840;
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
    EventEntry* e = AllocEventEntry_80043AF8((EventNode*)dword_8008D614);
    if (e)
    {
        e->cb_8 = (EventEntryFn)sub_800CD16C;
        dword_800CD840 = (CombComDlg*)a;
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
extern char* dword_800CD404[];

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
        *(short*)(dword_800CD404[i] + 0x10) = word_800CD434[i] + off * 192;
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
    return sub_80031BDC((short)GetMenuCursorIndex_8003DA54(dword_800CD298));
}

int sub_800CBC58()
{
    int r = sub_800A11BC(byte_800CD839);
    return FindNthMagicBit_8001AEC0(r, (short)GetMenuCursorIndex_8003DA54(dword_800CD2A4));
}

typedef struct CombComWin
{
    int w[14];
} CombComWin;
typedef struct CombComMenu
{
    int w[6];
} CombComMenu;
typedef struct CombComColor
{
    unsigned short color;
    unsigned char a;
    unsigned char b;
} CombComColor;
extern CombComWin name_800CB4F0;
extern CombComWin name_800CB528;
extern CombComWin name_800CB560;
extern CombComWin name_800CB598;
extern CombComMenu name_800CB5D0;
extern short word_800CD2D0;
extern unsigned short uiColor_8008B590;
extern void* memset(void* p, int c, unsigned int n);
extern void sub_8002ADB4(void* a, void* b, int c, int d);
extern void DrawMenuWindows_8002A5A4(void* p);
void sub_800CBCA0()
{
    CombComColor col;
    CombComWin a;
    CombComWin b;
    CombComWin c;
    CombComWin d;
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
    sub_8002ADB4(&a, &col, 0, GetTime30Hz_8002C64C());
    m.w[1] = GetTime30Hz_8002C64C();
    m.w[4] = (int)list;
    m.w[3] = word_800CD2D0;
    DrawMenuWindows_8002A5A4(&m);
}

INCLUDE_OVERLAY_ASM(combcom, sub_800CBEA4);

#if 0
// Not matched: scheduling of the three word_800A82D0/2 -= pairs (the original reloads the globals before the third pair) and the 1 constant hoist; masks need separate statements to keep sllv+and
typedef struct CombComBox
{
    char pad_0[8];
    short x0;
    short x1;
    short y0;
    short y1;
} CombComBox;
extern int sub_80012BB0(void* a, void* b, void* c, int* d);
extern int sub_80013228(void* a, void* b, void* c, int* d);
extern int sub_80034068(short* p);
void sub_800CC40C()
{
    short arg[4];
    int out[10];
    unsigned int i;
    void* src;
    CombComBox* t;
    if (byte_800CD83A == 3)
    {
        word_800A82D0 = 0;
        word_800A82D2 = 0;
        src = (void*)sub_80014390((unsigned char)(byte_800CD839 + 8));
        for (i = 0; i < 2; i++)
        {
            int bit = 1 << (i + 8);
            if (dword_800CD840->fC & bit)
            {
                t = (CombComBox*)sub_80014390((unsigned char)(i + 8));
                sub_80012BB0(src, t, dword_800CD840, out);
                if (!sub_80013228(src, t, dword_800CD840, out))
                {
                    bit = 1 << i;
                    if (dword_800CD840->f8 & bit)
                    {
                    word_800A82D0 -= out[3];
                    word_800A82D2 -= out[4];
                    word_800A82D0 -= out[5];
                    word_800A82D2 -= out[6];
                    word_800A82D0 -= out[7];
                    word_800A82D2 -= out[8];
                    if (t->x1 - t->x0 < word_800A82D0)
                    {
                        word_800A82D0 = t->x1 - t->x0;
                    }
                    if (t->y1 - t->y0 < word_800A82D2)
                    {
                        word_800A82D2 = t->y1 - t->y0;
                    }
                    }
                }
            }
        }
        arg[0] = dword_800CD840->f4;
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
extern CombComItem name_800CB690;
extern CombComItem name_800CB6C8;
extern CombComItem name_800CB700;
extern char dword_800A3AA0[][3][0xF8];
extern int sub_800A1934(void*);
extern int sub_800A1958(void*);
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
    void* u;
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
    m.w[5] = f;
    x = byte_800CD839 * 62 + 100;
    w[0].x_10 = x;
    w[1].x_10 = x;
    w[2].x_10 = x;
    m.w[1] = GetTime30Hz_8002C64C();
    m.w[3] = sel;
    m.w[4] = (int)pk;
    q[0] = arg[0];
    res = 0;
    if (mode == 1)
    {
        {
            char* s = (char*)sub_80014390((unsigned char)(((unsigned char*)arg)[2] + 8));
            list[0] = p0;
            p0->text_4 = s + 0x10;
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
            u = dword_800A3AA0[arg[1]][i];
            if (i != ((int*)dword_800A4078)[byte_800CD839] && sub_800A1934(u) == 0)
            {
                it = items[k];
                *pk = it;
                it->text_4 = (char*)u + 0x94;
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
    if (dword_800CD840->f0 == 0x12)
    {
        dword_800CD840->fC = 0;
        *(int*)sub_80014390((unsigned char)(byte_800CD839 + 8)) |= 0x8000;
    }
    else
    {
        if (dword_800CD840->f0 == 1 && byte_800CD839 != dword_800CD83C)
        {
            return;
        }
        if (dword_800CD840->f0 == 8)
        {
            dword_800CD840->fC = 0;
        }
    }
}

INCLUDE_OVERLAY_ASM(combcom, sub_800CCA94);

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
extern int sub_8001ACE4(int);
void sub_800CCDD0()
{
    int v;
    byte_800CD850 = byte_800CD83A;
    switch (byte_800CD83A)
    {
    case 0:
        byte_800CD844 = byte_800CD494[(short)GetMenuCursorIndex_8003DA54(word_800CD28C)];
        byte_800CD83A = byte_800CD49C[(short)GetMenuCursorIndex_8003DA54(word_800CD28C)];
        dword_800CD840->f0 = dword_800CD524[(short)GetMenuCursorIndex_8003DA54(word_800CD28C)];
        break;
    case 1:
        v = sub_800A11A0(byte_800CD839);
        byte_800CD844 = sub_80031B0C(v, sub_800CBC28());
        byte_800CD83A = 4;
        dword_800CD840->f4 = sub_800CBC28();
        break;
    case 2:
        byte_800CD844 = sub_8001ACE4(sub_800CBC58());
        if (byte_800CD844 & 2)
        {
            byte_800CD83A = 3;
        }
        else
        {
            byte_800CD83A = 4;
        }
        dword_800CD840->f4 = sub_800CBC58();
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
    dword_800CD840->fC = sub_800CCD84();
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
