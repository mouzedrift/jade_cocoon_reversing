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

extern unsigned short padPressed_8009194C[];
extern unsigned short padReleased_800918D4[];
extern unsigned short padRepeat_800918CC[];
extern void PlaySfx_80031494(int a1);

INCLUDE_DATA(word_80074994);
INCLUDE_DATA(dword_80074998);

// Matched
int AdjustByShoulderButtons_8003D198(int limit, int pos, int step, int idx)
{
    if (padRepeat_800918CC[idx] & 2)
    {
        pos += step;
    }
    else if (padRepeat_800918CC[idx] & 8)
    {
        if (!(padHeld_800918D0[idx] & 2))
        {
            pos -= step;
        }
    }
    if (pos >= limit)
    {
        pos = limit - 1;
    }
    if (pos < 0)
    {
        pos = 0;
    }
    return pos;
}
// Matched
int AdjustByLeftRight_8003D210(int limit, int pos, int step, int idx)
{
    if (padRepeat_800918CC[idx] & 0x2000)
    {
        pos += step;
    }
    else if (padRepeat_800918CC[idx] & 0x8000)
    {
        if (!(padHeld_800918D0[idx] & 0x2000))
        {
            pos -= step;
        }
    }
    if (pos >= limit)
    {
        pos = limit - 1;
    }
    if (pos < 0)
    {
        pos = 0;
    }
    return pos;
}
// Matched
int IsConfirmPressed_8003D288(int flag, int idx)
{
    int r = 0;
    unsigned int x;
    if ((padPressed_8009194C[idx] & 0x40) && !(padHeld_800918D0[idx] & 4) && !(((unsigned short*)padReleased_800918D4)[idx] & 4))
    {
        goto done;
    }
    x = padPressed_8009194C[idx];
    if (!(x & 4))
    {
        goto end;
    }
    if ((padHeld_800918D0[idx] & 0x40) || (((unsigned short*)padReleased_800918D4)[idx] & 0x40))
    {
        if (!(x & 0x40))
        {
            goto end;
        }
    }
done:
    if (flag)
    {
        PlaySfx_80031494(0x7E);
    }
    r = 1;
end:
    return r;
}
// Matched
int IsConfirmPressedP1_8003D380(int a0)
{
    return IsConfirmPressed_8003D288(a0, 0);
}
// Matched
int IsConfirmPressedP2_8003D3A0(int a0)
{
    return IsConfirmPressed_8003D288(a0, 1);
}
// Matched
int IsCancelPressed_8003D3C0(int arg0, int arg1)
{
    int r = 0;
    unsigned short x = padPressed_8009194C[arg1];
    if ((x & 0x10) || (x & 1))
    {
        if (arg0)
        {
            PlaySfx_80031494(0x7D);
        }
        r = 1;
    }
    return r;
}
// Matched
int IsCancelPressedP1_8003D41C(int a0)
{
    return IsCancelPressed_8003D3C0(a0, 0);
}
// Matched
int IsCancelPressedP2_8003D43C(int a0)
{
    return IsCancelPressed_8003D3C0(a0, 1);
}
// Matched
int IsCircleHeld_8003D45C(int idx)
{
    unsigned int f = padHeld_800918D0[idx] & 0x20;
    return f != 0;
}
// Matched
int IsCircleHeldP1_8003D480(void)
{
    return IsCircleHeld_8003D45C(0);
}
// Matched
int IsCircleHeldP2_8003D4A0(void)
{
    return IsCircleHeld_8003D45C(1);
}
// Matched
int MoveGridCursor_8003D4C0(short* m, int idx)
{
    int r = 1;
    if (m[4] < 0)
    {
        m[4] = 0;
    }
    if (padRepeat_800918CC[idx] & 0x2000)
    {
        if (m[4] % m[0] == m[0] - 1)
        {
            r |= 2;
        }
        else
        {
            m[4]++;
        }
    }
    if (padRepeat_800918CC[idx] & 0x8000)
    {
        if (m[4] % m[0] == 0)
        {
            r |= 4;
        }
        else
        {
            m[4]--;
        }
    }
    if (padRepeat_800918CC[idx] & 0x1000)
    {
        if (m[4] < m[0])
        {
            r |= 8;
        }
        else
        {
            m[4] -= m[0];
        }
    }
    if (padRepeat_800918CC[idx] & 0x4000)
    {
        if (m[4] > m[0] * (m[1] - 1) - 1)
        {
            r |= 0x10;
        }
        else
        {
            m[4] += m[0];
        }
    }
    return r;
}
// Matched
int MoveGridCursorP1_8003D630(short* m)
{
    int idx = 0;
    if (m[3] < 0)
    {
        m[3] = 0;
    }
    if (padRepeat_800918CC[idx] & 0x2000)
    {
        if (m[3] % m[4] == m[4] - 1)
        {
            return 1;
        }
        m[3]++;
    }
    if (padRepeat_800918CC[idx] & 0x8000)
    {
        if (m[3] % m[4] == 0)
        {
            return 2;
        }
        m[3]--;
    }
    if (padRepeat_800918CC[idx] & 0x1000)
    {
        if (m[3] < m[4])
        {
            return 3;
        }
        m[3] -= m[4];
    }
    if (padRepeat_800918CC[idx] & 0x4000)
    {
        if (m[3] > m[4] * (m[5] - 1) - 1)
        {
            return 4;
        }
        m[3] = m[3] + m[4];
    }
    return 0;
}
typedef struct
{
    short field_0;
    short field_2;
    unsigned short field_4;
    unsigned short field_6;
    short field_8;
    short field_A;
} MenuCursor;

extern int MenuCursorInput_8003D830();

// Matched
int UpdateMenuCursor_8003D794(MenuCursor* p)
{
    unsigned short a = p->field_8;
    unsigned short b = p->field_A;
    int r = MenuCursorInput_8003D830(p);
    if (r == 0)
    {
        int t = p->field_4 - 1;
        if (t < p->field_8)
        {
            p->field_8 = t;
        }
    }
    if ((short)a != p->field_8 || (short)b != p->field_A)
    {
        PlaySfx_80031494(0x7F);
    }
    return r;
}
// Matched
int MenuCursorInput_8003D830(MenuCursor* p, int idx)
{
    int r = MoveGridCursor_8003D4C0((short*)p, idx);
    int t;
    int t2;

    if (p->field_6 & 0x40)
    {
        if (r & 8)
        {
            if (p->field_A >= p->field_0)
            {
                p->field_A -= p->field_0;
                return 8;
            }
        }
        else if (r & 0x10)
        {
            if (p->field_A < p->field_4 - p->field_0 * p->field_2)
            {
                p->field_A += p->field_0;
                return 7;
            }
        }
    }
    if (p->field_6 & 1)
    {
        if (r & 2)
        {
            t = p->field_0 - 1;
            p->field_8 -= t;
        }
        if (r & 4)
        {
            p->field_8 += p->field_0 - 1;
        }
    }
    if (p->field_6 & 2)
    {
        if (r & 8)
        {
            p->field_8 += p->field_0 * (p->field_2 - 1);
        }
        if (r & 0x10)
        {
            t2 = p->field_0 - p->field_2 * p->field_0;
            p->field_8 += t2;
        }
    }
    if ((p->field_6 & 4) && (r & 2))
    {
        return 1;
    }
    if ((p->field_6 & 8) && (r & 4))
    {
        return 2;
    }
    if ((p->field_6 & 0x10) && (r & 8))
    {
        return 3;
    }
    if ((p->field_6 & 0x20) && (r & 0x10))
    {
        return 4;
    }
    if (p->field_6 & 0x40)
    {
        p->field_A = AdjustByShoulderButtons_8003D198(p->field_4 - p->field_0 * p->field_2 + 1, p->field_A, p->field_0 * p->field_2, 0);
    }
    return 0;
}
// Matched
int GetMenuCursorIndex_8003DA54(MenuCursor* p)
{
    return (short)(p->field_8 + p->field_A);
}
typedef struct
{
    unsigned short field_0;
    unsigned short field_2;
    unsigned short field_4;
    unsigned short field_6;
    unsigned short field_8;
    unsigned short field_A;
    unsigned short field_C;
    unsigned short pad_E;
    unsigned char* field_10;
    unsigned short field_14;
    unsigned short pad_16;
} FontDef;
extern FontDef fontDefs_80086574[];
extern char* publicTiySprts_8008D434;
extern char* publicTiyTPages_8008D440;
// Matched
void InitFonts_8003DA70(void)
{
    int i;
    FontDef* e;
    Font* f;
    for (i = 0; i < 3; i++)
    {
        e = &fontDefs_80086574[i];
        f = &fonts_80095FB0[i];
        MemCopy_800403E8((unsigned int*)f, (unsigned int*)(publicTiySprts_8008D434 + e->field_0 * 20), 0x14);
        f->w_10 = e->field_6;
        f->h_12 = e->field_8;
        f->tpage_14 = (unsigned short*)(publicTiyTPages_8008D440 + e->field_0 * 8);
        f->field_18 = f->u_C;
        f->field_1A = f->v_D;
        f->firstChar_1E = e->field_4;
        f->clutX_20 = e->field_A;
        f->clutY_22 = e->field_C;
        f->widths_24 = e->field_10;
        f->field_1C = e->field_2;
        f->field_28 = e->field_14;
        f->field_2A = 0;
    }
}
extern void AddClipTexWindowPrim_80033308(unsigned long* ot);
extern void AddTexWindowPrim_8003326C(void* p, unsigned long* ot);
extern void sub_8003DCA4(int a, unsigned int* w);
// Matched
int sub_8003DB74(unsigned int* w, int a)
{
    if (w[9] >= 3 - (settingsFlags_8008B58C & 7))
    {
        w[9] = 0;
        w[7]++;
    }
    if (w[5] == 0)
    {
        w[7] = 0x0FFFFFFF;
    }
    w[8] = w[7];
    AddClipTexWindowPrim_80033308(pOT_8008D454);
    sub_8003DCA4(a, w);
    AddTexWindowPrim_8003326C(w + 1, pOT_8008D454);
    switch (w[10])
    {
    case 1:
        if (w[6] == 1 && ((padHeld_800918D0[0] & 0x60F) || (padPressed_8009194C[0] & 0xF0)))
        {
            w[7] = 0x0FFFFFFF;
        }
        else
        {
            w[9]++;
        }
        break;
    case 10:
        return 1;
    }
    return 0;
}
INCLUDE_ASM(sub_8003DCA4);
// Matched
void sub_8003E268(unsigned short* p)
{
    short x = p[0] + 0xC3;
    short y = p[1] + 0x23;
    sub_8003CF88(x, y, 0);
}
typedef struct
{
    short w;
    short h;
} struct_size_8003E3B4;
extern int MeasureTextWidth_8003E4C8(int str);
// Matched
struct_size_8003E3B4 MeasureTextLinesMasked_8003E2A8(int* list, unsigned int mask)
{
    struct_size_8003E3B4 sz;
    short w;
    int i;
    sz.w = 0;
    sz.h = 0;
    for (i = 0; list[i]; i++)
    {
        if (mask & (1 << i))
        {
            w = MeasureTextWidth_8003E4C8(list[sz.h]);
            if (sz.w < w)
            {
                sz.w = w;
            }
            sz.h++;
        }
    }
    sz.h *= 12;
    return sz;
}
typedef struct
{
    short w;
    short h;
} Size2;
extern int MeasureTextWidth_8003E4C8(int str);

// Matched
struct_size_8003E3B4 MeasureTextLines_8003E3B4(int* list)
{
    struct_size_8003E3B4 sz;
    short w;
    int i;
    sz.w = 0;
    sz.h = 0;
    for (i = 0; list[i]; i++)
    {
        if (!sub_8003E484(list[i]))
        {
            w = MeasureTextWidth_8003E4C8(list[i]);
            if (sz.w < w)
            {
                sz.w = w;
            }
            sz.h++;
        }
    }
    sz.h *= 12;
    return sz;
}
// Matched
int sub_8003E484(int a0)
{
    int v = *EncodeText_8003F684(2, (unsigned short*)a0);
    if (v < 0xC3)
    {
        if (v >= 0x91)
        {
            return 1;
        }
    }
    return 0;
}
typedef struct
{
    unsigned short s[11];
} TextBuf22;
extern unsigned short word_80074994[];
extern TextBuf22 dword_80074998;
extern int textNumberArgs_80096038[];
extern int GetCharWidth_8003E884(int idx, short n);
extern void IntToText_8003F610(unsigned short* buf, int val);
extern unsigned short* DecodeText_8003F748(int mode, unsigned short* s);
// Matched
int MeasureTextWidth_8003E4C8(int str)
{
    unsigned short num[12];
    TextBuf22 name;
    unsigned short* s;
    unsigned short* sub;
    short w;
    int k;
    unsigned short c;

    sub = word_80074994;
    w = 0;
    name = dword_80074998;
    k = -1;
    s = EncodeText_8003F684(2, (unsigned short*)str);
    while (*s != 0 || *sub != 0)
    {
        if (*sub != 0 && sub != NULL)
        {
            c = *sub++;
        }
        else
        {
            c = *s++;
        }
        if (c < 0x7F)
        {
            w += GetCharWidth_8003E884(2, (short)c);
        }
        else
        {
            switch (c)
            {
            case 0x86:
            case 0x87:
                if (CopyPlayerName_8003F860(playerName_8008BD48, name.s))
                {
                    DecodeText_8003F748(1, name.s);
                }
                sub = EncodeText_8003F684(2, name.s);
                break;
            case 0x88:
            case 0x89:
            case 0x8A:
            case 0x8B:
            case 0x8C:
                IntToText_8003F610(num, textNumberArgs_80096038[k - 0x88]);
                sub = EncodeText_8003F684(2, num);
                break;
            case -1:
                w += 14;
                break;
            }
        }
    }
    return w;
}
// Matched
int MeasureTextWidthFont1_8003E6B0(int str)
{
    unsigned short num[12];
    TextBuf22 name;
    unsigned short* s;
    unsigned short* sub;
    short w;
    int k;
    unsigned short c;

    sub = word_80074994;
    w = 0;
    name = dword_80074998;
    k = -1;
    s = EncodeText_8003F684(1, (unsigned short*)str);
    while (*s != 0 || *sub != 0)
    {
        if (*sub != 0 && sub != NULL)
        {
            c = *sub++;
        }
        else
        {
            c = *s++;
        }
        if (c < 0x71)
        {
            w += GetCharWidth_8003E884(1, (short)c);
        }
        else
        {
            switch (c)
            {
            case 0x86:
            case 0x87:
                if (CopyPlayerName_8003F860(playerName_8008BD48, name.s))
                {
                    DecodeText_8003F748(1, name.s);
                }
                sub = EncodeText_8003F684(2, name.s);
                break;
            case 0x88:
            case 0x89:
            case 0x8A:
            case 0x8B:
            case 0x8C:
                IntToText_8003F610(num, textNumberArgs_80096038[k - 0x88]);
                sub = EncodeText_8003F684(1, num);
                break;
            case -1:
                break;
            }
        }
    }
    return w;
}
