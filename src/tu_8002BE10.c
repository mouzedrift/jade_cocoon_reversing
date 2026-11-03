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

INCLUDE_DATA(dword_800741EC);

extern void DrawUiTiySprt_8002C06C(unsigned short* p, int a1, int a2);
// Matched
void DrawMenuBackground_8002BE10(void)
{
    unsigned short pos[2];
    short i;
    short j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 3; j++)
        {
            pos[0] = (j << 16) >> 9;
            if (i & 1)
            {
                pos[0] -= 0x40;
            }
            pos[1] = i * 60;
            DrawUiTiySprt_8002C06C(pos, 0x95, 0xF);
        }
    }
}
typedef struct
{
    int field_0;
    int field_4;
    short field_8;
    short field_A;
} struct_BEC8;
extern void InterpolateWindowRect_8004196C(int a, int b, int c, int d, int e);
extern void AddTexWindowPrim_8003326C(int a, void* b);
extern void AddClipTexWindowPrim_80033308(void* a);
extern void DrawUiWindow_8002A384(struct_BEC8* p);
// Matched
void DrawAnimatedWindow_8002BEC8(int a0, int a1, short a2, short a3, int a4, int a5)
{
    struct_BEC8 s;
    InterpolateWindowRect_8004196C(a0, a1, a2, 8, 0);
    AddTexWindowPrim_8003326C(a0, &pOT_8008D454[a3]);
    if (a4)
    {
        s.field_8 = 1;
    }
    else
    {
        s.field_8 = 0;
    }
    s.field_0 = a0;
    s.field_4 = a5;
    s.field_A = a3;
    DrawUiWindow_8002A384(&s);
    AddClipTexWindowPrim_80033308(&pOT_8008D454[a3]);
}
extern void QueueFileRequest_8003BC84(int* a);
// Matched
void LoadUiTiy_8002BF74(void)
{
    int s[8];
    uiTiyLoaded_8008B4E8 = 0;
    s[0] = 0x29;
    s[1] = 0x3B;
    s[2] = 0;
    s[3] = 0;
    s[4] = 0;
    s[5] = 0;
    s[6] = 0;
    s[7] = (int)OnUiTiyLoaded_8002BFCC;
    QueueFileRequest_8003BC84(s);
}
// Matched
void OnUiTiyLoaded_8002BFCC(int a0, int a1)
{
    LoadTiy_80028E74(&uiTiySprts_8008D620, 0, &uiTiyTPages_8008D3F4, a1, 1);
    uiTiyLoaded_8008B4E8 = 1;
}
// Matched
void FreeActiveOverlay_8002C014(void)
{
    if (uiTiySprts_8008D620)
    {
        free3_8003FC6C((void*)uiTiySprts_8008D620);
        uiTiySprts_8008D620 = 0;
    }
    if (uiTiyTPages_8008D3F4)
    {
        free3_8003FC6C((void*)uiTiyTPages_8008D3F4);
        uiTiyTPages_8008D3F4 = 0;
    }
}
typedef struct
{
    int field_0;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    char pad_7;
    unsigned short x;
    unsigned short y;
    char pad_C[8];
} OverlayColorEntry;
// Matched
void DrawUiTiySprt_8002C06C(unsigned short* pos, int idx, int ot)
{
    ((OverlayColorEntry*)uiTiySprts_8008D620)[idx].x = pos[0];
    ((OverlayColorEntry*)uiTiySprts_8008D620)[idx].y = pos[1];
    AddPrimCopy_80040298(&pOT_8008D454[ot], &((OverlayColorEntry*)uiTiySprts_8008D620)[idx], 5);
    AddPrimCopy_80040298(&pOT_8008D454[ot], (char*)uiTiyTPages_8008D3F4 + idx * 8, 2);
}
// Matched
void DrawLargeNumber_8002C100(unsigned short* p, int n, int ot)
{
    short digits[7];
    unsigned short pos[2];
    short i;
    short j;
    for (i = 0; i < 7; i++)
    {
        digits[i] = -1;
    }
    if (n > 9999999)
    {
        n = 9999999;
    }
    i = 0;
    do
    {
        digits[i] = n % 10 + 0x84;
        n /= 10;
        i++;
    } while (n);
    pos[1] = p[1];
    for (j = 0; j < i; j++)
    {
        if (digits[j] != -1)
        {
            pos[0] = p[0] - (j + 1) * (((SPRT*)uiTiySprts_8008D620)[digits[j]].w - 1);
            DrawUiTiySprt_8002C06C(pos, digits[j], ot);
        }
    }
}
// Matched
void DrawSmallNumber3_8002C290(unsigned short* p, int n, int ot)
{
    short digits[3];
    unsigned short pos[2];
    short i;
    short j;
    for (i = 0; i < 3; i++)
    {
        digits[i] = -1;
    }
    if (n > 999)
    {
        n = 999;
    }
    i = 0;
    do
    {
        digits[i] = n % 10 + 0xCF;
        n /= 10;
        i++;
    } while (n);
    pos[1] = p[1];
    for (j = 0; j < i; j++)
    {
        if (digits[j] != -1)
        {
            pos[0] = p[0] - (j + 1) * (((SPRT*)uiTiySprts_8008D620)[digits[j]].w - 1);
            DrawUiTiySprt_8002C06C(pos, digits[j], ot);
        }
    }
}
// Matched
void DrawSmallNumber9_8002C414(unsigned short* p, int n, int ot)
{
    short digits[9];
    unsigned short pos[2];
    short i;
    short j;
    for (i = 0; i < 9; i++)
    {
        digits[i] = -1;
    }
    if (n > 999999999)
    {
        n = 999999999;
    }
    i = 0;
    do
    {
        digits[i] = n % 10 + 0xCF;
        n /= 10;
        i++;
    } while (n);
    pos[1] = p[1];
    for (j = 0; j < i; j++)
    {
        if (digits[j] != -1)
        {
            pos[0] = p[0] - (j + 1) * (((SPRT*)uiTiySprts_8008D620)[digits[j]].w - 1);
            DrawUiTiySprt_8002C06C(pos, digits[j], ot);
        }
    }
}
// Matched
int sub_8002C5A4(int n)
{
    do
    {
        n /= 10;
    } while (n);
    return 0;
}
extern unsigned char largeDigitColors_800826F8[][4];
// Matched
void SetLargeDigitColor_8002C5D0(int a0)
{
    short i = 0x84;
    do
    {
        ((OverlayColorEntry*)uiTiySprts_8008D620)[i].r = largeDigitColors_800826F8[a0][0];
        ((OverlayColorEntry*)uiTiySprts_8008D620)[i].g = largeDigitColors_800826F8[a0][1];
        ((OverlayColorEntry*)uiTiySprts_8008D620)[i].b = largeDigitColors_800826F8[a0][2];
        i++;
    } while (i < 0x8e);
}
// Matched
unsigned int GetTime30Hz_8002C64C(void)
{
    return (unsigned int)(frameCount_8008D3FC * display_8008B4D8.vsyncsPerFrame_4) >> 1;
}
// Matched
int sub_8002C670(char* base, int a1, int a2, short idx, short a4)
{
    char* p = base + idx * 4;
    int b;
    if (!(p[0xde] & 1))
    {
        return 0;
    }
    if (p[0xdf] == 0)
    {
        return 0;
    }
    DrawLargeTextBox_8002AF10(a2 + (unsigned char)p[0xdf] * 16, a1, a4);
    return 1;
}
typedef struct
{
    short a;
    short b;
} ShortPair2;
extern void sub_8002B3DC(ShortPair2 p, int b, int c, int d);
// Matched
void sub_8002C6DC(int a0, short a1, short a2)
{
    ShortPair2 p;
    p.a = 2;
    p.b = a1;
    sub_8002B3DC(p, frameCount_8008D3FC, a0, a2);
}
typedef struct
{
    unsigned short flags;
    short pad_2;
    int f4;
    int f8;
    int fC;
    short x;
    short y;
    char pad_14[8];
} MenuItem_1C;
typedef struct
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    MenuItem_1C** field_10;
    int field_14;
} struct_A5A4;
extern void DrawMenuWindows_8002A5A4(struct_A5A4* p);
extern int CheckItemUsable_80033AFC(short* p);
extern int sub_800AD308(int a0);
extern int dword_800741EC;
extern int publicTiySprts_8008D434;
extern int publicTiyTPages_8008D440;
extern int dword_80082820;
extern int dword_80082824;
extern MenuItem_1C* off_800829E8[];
// Matched
void sub_8002C728(short* a0)
{
    struct_A5A4 s;
    short saved;
    short w;
    short i;
    int idx;
    int v17;
    int v18;
    int v19;
    MenuItem_1C** e;
    int y;
    int n;
    saved = a0[0];
    w = 8;
    for (i = 0; i < 4; i++)
    {
        idx = sub_800AD288(i + a0[1], 0);
        if (idx < 0x2B)
        {
            v18 = GetItemIcon_8001D2AC(idx);
            v19 = GetItemName_8001CE20(idx);
            v17 = sub_800AD2C8(i + a0[1], 0);
        }
        else
        {
            v18 = -1;
            v19 = (int)&dword_800741EC;
            v17 = 0;
        }
        e = &off_800829E8[i];
        (*e)[0].f4 = v18;
        (*e)[0].f8 = (int)&publicTiySprts_8008D434;
        (*e)[0].fC = (int)&publicTiyTPages_8008D440;
        (*e)[1].f4 = v19;
        (*e)[2].f4 = v17;
        (*e)[0].x = 0x53;
        y = i * 22 + 0x36;
        (*e)[0].y = y;
        (*e)[1].x = 0x68;
        (*e)[1].y = y;
        (*e)[2].x = 0xD8;
        (*e)[2].y = y;
        a0[0] = i;
        if ((short)CheckItemUsable_80033AFC(a0))
        {
            (*e)[0].flags |= 2;
            (*e)[1].flags |= 2;
            (*e)[2].flags |= 2;
        }
        else
        {
            (*e)[0].flags &= ~2;
            (*e)[1].flags &= ~2;
            (*e)[2].flags &= ~2;
        }
        if (v17 == 0)
        {
            off_800829E8[i][0].flags |= 0x40;
            off_800829E8[i][1].flags |= 0x40;
            off_800829E8[i][2].flags |= 0x40;
        }
        else
        {
            off_800829E8[i][0].flags &= ~0x40;
            off_800829E8[i][1].flags &= ~0x40;
            off_800829E8[i][2].flags &= ~0x40;
        }
    }
    s.field_0 = a0[2];
    s.field_4 = frameCount_8008D3FC;
    s.field_8 = w;
    s.field_C = saved;
    s.field_10 = off_800829E8;
    s.field_14 = a0[3];
    DrawMenuWindows_8002A5A4(&s);
    sub_8003F900(2, 0);
    n = sub_800AD308(0) + 1;
    if (n < 4)
    {
        n = 4;
    }
    if (a0[1])
    {
        sub_8002C6DC((int)&dword_80082820, 3, a0[3]);
    }
    if (a0[1] < n - 4 && n >= 5)
    {
        sub_8002C6DC((int)&dword_80082824, 1, a0[3]);
    }
}
extern int FindNthMagicBit_8001AEC0(void* p, int v);
extern int CountMagicBits_8001AE54(void* p);
extern int CheckMagicCastable_80033C08(short* p);
extern MenuItem_1C* off_80082B54[];
extern unsigned short word_800829FC[];
extern unsigned short word_80082A00[];
// Matched
void sub_8002CAC8(short* a0, unsigned short* a1)
{
    unsigned short pos[2];
    struct_A5A4 s;
    unsigned short r[2];
    short saved;
    short w;
    short i;
    int idx;
    int v17;
    int v3;
    MenuItem_1C** e;
    int y;
    int n;
    saved = a0[0];
    w = 8;
    if (a1)
    {
        pos[0] = a1[0];
        pos[1] = a1[1];
    }
    else
    {
        pos[0] = 0x60;
        pos[1] = 0x36;
    }
    if (*(char**)(a0 + 6) == 0)
    {
        return;
    }
    for (i = 0; i < 4; i++)
    {
        idx = FindNthMagicBit_8001AEC0(*(char**)(a0 + 6) + 0xF4, i + a0[1]);
        if (idx < 0x1E)
        {
            v17 = sub_8001AF3C(idx);
            v3 = GetMagicName_8001AC2C(idx);
        }
        else
        {
            v17 = -1;
            v3 = (int)&dword_800741EC;
        }
        e = &off_80082B54[i];
        (*e)[0].f4 = v17;
        (*e)[1].f4 = v3;
        (*e)[0].x = pos[0];
        y = i * 22;
        (*e)[0].y = pos[1] + y;
        (*e)[1].x = pos[0] + 0x15;
        (*e)[1].y = pos[1] + y;
        a0[0] = i;
        if ((short)CheckMagicCastable_80033C08(a0))
        {
            (*e)[0].flags |= 2;
            (*e)[1].flags |= 2;
        }
        else
        {
            (*e)[0].flags &= ~2;
            (*e)[1].flags &= ~2;
        }
    }
    s.field_0 = a0[2];
    s.field_4 = frameCount_8008D3FC;
    s.field_8 = w;
    s.field_C = saved;
    s.field_10 = off_80082B54;
    s.field_14 = a0[3];
    DrawMenuWindows_8002A5A4(&s);
    sub_8003F900(2, 0);
    n = CountMagicBits_8001AE54(*(char**)(a0 + 6) + 0xF4);
    if (n < 4)
    {
        n = 4;
    }
    if (a0[1])
    {
        if (a1)
        {
            r[0] = word_800829FC[0] + a1[0] - 0x60;
            r[1] = word_800829FC[1] + a1[1] - 0x36;
        }
        else
        {
            r[0] = word_800829FC[0];
            r[1] = word_800829FC[1];
        }
        sub_8002C6DC((int)r, 3, a0[3]);
    }
    if (a0[1] < n - 4 && n >= 5)
    {
        if (a1)
        {
            r[0] = word_80082A00[0] + a1[0] - 0x60;
            r[1] = word_80082A00[1] + a1[1] - 0x36;
        }
        else
        {
            r[0] = word_80082A00[0];
            r[1] = word_80082A00[1];
        }
        sub_8002C6DC((int)r, 1, a0[3]);
    }
}

