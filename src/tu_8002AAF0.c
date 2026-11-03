#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "STDLIB.H"
#include "STDIO.H"
#include "LIBPAD.H"
#include "LIBSND.H"
#include "LIBMCX.H"
#include "LIBPRESS.H"
#include "LIBETC.H"
#include "LIBMCRD.H"
#include "sound.h"
#include "data_decls.h"

INCLUDE_DATA(dword_800741C4);

typedef struct
{
    unsigned short flags;
    char pad_2[0x1A];
} struct_AAF0_item;
typedef struct
{
    int flags;
    int field_4;
    int field_8;
    int field_C;
    struct_AAF0_item** items;
    int ot;
} struct_AAF0;
typedef struct
{
    unsigned short color;
    unsigned char b;
    unsigned char c;
} struct_AAF0_param;
extern short uiColor_8008B590;
extern void DrawWindow_80042460(void* a, int b, void* c, int d);
// Matched
void sub_8002AAF0(struct_AAF0* p, int i, int j, RECT* r)
{
    struct_AAF0_param t;
    int k;
    int f;
    struct_AAF0_item* it = &p->items[i][j];
    k = 0;
    if (it->flags & 0x20)
    {
        return;
    }
    f = p->flags;
    if (f & 8)
    {
        t.c = 0;
    }
    else if (f & 0x10)
    {
        t.c = 1;
    }
    else if (f & 0x20)
    {
        t.c = 2;
    }
    else if (f & 0x40)
    {
        t.c = 3;
    }
    else if (f & 0x80)
    {
        t.c = 4;
    }
    else
    {
        t.c = 1;
    }
    f = p->flags;
    if (f & 1)
    {
        t.b = 0;
    }
    else if (f & 2)
    {
        t.b = 1;
        if (p->field_C == i)
        {
            k = p->field_4;
        }
    }
    else if ((f & 4) && p->field_C == i)
    {
        t.b = 2;
    }
    else
    {
        t.b = 0;
    }
    f = p->flags;
    if (!(f & 0x100))
    {
        t.color = uiColor_8008B590;
    }
    else if (f & 0x2000)
    {
        t.color = 4;
    }
    else if (f & 0x1000)
    {
        t.color = 3;
    }
    else if (f & 0x800)
    {
        t.color = 2;
    }
    else if (f & 0x400)
    {
        t.color = 1;
    }
    else
    {
        t.color = 0;
    }
    DrawWindow_80042460(r, (int)&t, &pOT_8008D454[p->ot], k);
}
#if 0
// Not matched (2 words: first branch emits subu/subu; written as a[0] + (a[2] - b) gcc cross-jumps it into the second branch)
void AlignMenuItem_8002AC88(int flags, short* a, int b, short* out)
{
    if (flags & 4)
    {
        out[0] = a[0] - (b - a[2]);
    }
    else if (flags & 8)
    {
        out[0] = a[0] + ((unsigned int)(a[2] - b) >> 1);
    }
    else
    {
        out[0] = a[0];
    }
    out[1] = a[1];
}
#endif
INCLUDE_ASM(AlignMenuItem_8002AC88);
// Matched
void GetMenuItemColor_8002ACE8(int flags, unsigned char* out)
{
    unsigned char val;
    if (flags & 2)
    {
        val = 0x40;
    }
    else
    {
        val = 0x80;
    }
    out[0] = val;
    out[1] = val;
    out[2] = val;
}
// Matched
void SetMenuItemFont1Clut_8002AD08(int flags)
{
    if (flags & 2)
    {
        SetFontClutOffset_8003F900(1, 1);
    }
    else
    {
        SetFontClutOffset_8003F900(1, 0);
    }
}
// Matched
void SetMenuItemFont2Clut_8002AD44(int flags)
{
    if (flags & 2)
    {
        SetFontClutOffset_8003F900(2, 1);
    }
    else
    {
        SetFontClutOffset_8003F900(2, 0);
    }
}
// Matched
void SetMenuItemDigitColor_8002AD80(int flags)
{
    if (flags & 2)
    {
        SetLargeDigitColor_8002C5D0(3);
    }
    else
    {
        SetLargeDigitColor_8002C5D0(0);
    }
}
extern void DrawMenuWindowContents_8002A710(void* a, int b);
extern void DrawWindow_80042460(void* a, int b, void* c, int d);
// Matched
void sub_8002ADB4(char* a0, int a1, int a2, int a3)
{
    DrawMenuWindowContents_8002A710(a0, a2);
    SetFontClutOffset_8003F900(2, 0);
    SetFontClutOffset_8003F900(1, 0);
    DrawWindow_80042460(a0 + 0x10, a1, &pOT_8008D454[a2], a3);
}
typedef struct
{
    unsigned short x;
    unsigned short y;
} Pos16;
typedef struct
{
    unsigned short color;
    unsigned char b;
    unsigned char c;
} struct_text_param;
extern short uiColor_8008B590;
extern void DrawText_8003E91C(int mode, int a, void* b, int c);
// Matched
void DrawTextLinesWindow_8002AE38(int a0, Pos16* a1, int a2, RECT* a3, int a4)
{
    int* lines = (int*)a0;
    Pos16 p;
    struct_text_param t;
    unsigned int i;
    p.x = a1->x;
    p.y = a1->y;
    for (i = 0; i < a4; i++)
    {
        if (lines[i])
        {
            DrawText_8003E91C(2, lines[i], &p, a2);
        }
        p.y += 12;
    }
    if (a3)
    {
        t.c = 1;
        t.b = 0;
        t.color = uiColor_8008B590;
        DrawWindow_80042460(a3, (int)&t, &pOT_8008D454[a2], 0);
    }
}
// Matched
void DrawLargeTextBox_8002AF10(int a0, int a1, int a2)
{
    RECT r;
    r.x = 10;
    r.y = 0x99;
    r.w = 0x12C;
    r.h = 0x3C;
    DrawTextBox_8002AFA0(a0, a1, a2, &r, 4);
}
// Matched
void DrawSmallTextBox_8002AF58(int a0, int a1, int a2)
{
    RECT r;
    r.x = 10;
    r.y = 0xC3;
    r.w = 0x12C;
    r.h = 0x12;
    DrawTextBox_8002AFA0(a0, a1, a2, &r, 1);
}
#if 0
void DrawTextBox_8002AFA0(int a0, int a1, int a2, RECT* a3, int a4)
{
}
#endif
// Matched
void DrawTextBox_8002AFA0(int a0, int a1, int a2, RECT* a3, int a4)
{
    Pos16 p;
    Pos16* src = (Pos16*)a1;
    if (src)
    {
        ((Pos16*)a3)->x = src->x;
        ((Pos16*)a3)->y = src->y;
    }
    p.x = ((Pos16*)a3)->x + 4;
    p.y = ((Pos16*)a3)->y + 5;
    DrawTextLinesWindow_8002AE38(a0, &p, a2, a3, a4);
}
typedef struct
{
    int icon;
    int text;
} struct_B004_entry;
extern void DrawUiTiySprt_8002C06C(void* p, int a1, int a2);
extern int MeasureTextWidth_8003E4C8(int text);
// Matched
void DrawButtonHelpBar_8002B004(struct_B004_entry* e, Pos16* a1, int ot)
{
    Pos16 cur;
    Pos16 base;
    RECT r;
    struct_text_param t;
    int i;
    i = 0;
    if (a1)
    {
        base.x = a1->x;
        base.y = a1->y;
    }
    else
    {
        base.x = 10;
        base.y = 0xD6;
    }
    cur.x = base.x + 2;
    for (; e[i].icon >= 0; i++)
    {
        cur.y = base.y + (14 - ((SPRT*)uiTiySprts_8008D620)[e[i].icon].h) / 2;
        DrawUiTiySprt_8002C06C(&cur, e[i].icon, ot);
        cur.x = (unsigned short)(cur.x + 1) + ((SPRT*)uiTiySprts_8008D620)[e[i].icon].w;
        cur.y = base.y + 2;
        DrawText_8003E91C(2, e[i].text, &cur, ot);
        cur.x = MeasureTextWidth_8003E4C8(e[i].text) + (unsigned short)(cur.x + 4);
    }
    r.x = base.x;
    r.y = base.y;
    r.w = 0x12C;
    r.h = 0xE;
    t.c = 1;
    t.b = 0;
    t.color = uiColor_8008B590;
    DrawWindow_80042460(&r, (int)&t, &pOT_8008D454[ot], 0);
}
typedef struct
{
    short s[8];
} Block16;
extern Block16 dword_800741C4;
extern void sub_8002B2A4(short a, int b, int c, Block16* d, int e);
// Matched
void sub_8002B1B0(short a, int b, int c)
{
    Block16 local = dword_800741C4;
    sub_8002B2A4(a, b, c, &local, 0);
}
