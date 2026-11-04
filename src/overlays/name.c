// NAME.BIN - player name selection screen, loaded at 0x800B6D00
#include "common.h"
#include "funcs.h"
#include "globals.h"
typedef struct
{
    unsigned short flags_0;
    char pad_2[2];
    int field_4;
    short field_8;
    short pad_A;
    short field_C;
    unsigned short pad_E;
    short name_10[10]; // SJIS characters, the first byte of a full-width character is >= 0x81
    char c_24;
    char c_25;
    short pad_26;
    short field_28[10];
    short pad_3C[2];
    int field_40;
    short length_44; // length of name_10 in bytes
} NameEntry;
// window style for DrawWindow_80042460
typedef struct
{
    unsigned short color_0;
    unsigned char colors_2; // GetWindowColors_8004226C
    unsigned char frame_3;  // DrawWindowFrame_80041ED0
} NameWinStyle;
typedef struct
{
    int flags;
    unsigned short s4;
    unsigned short s6;
    short s8;
    short sA;
} NameCursor;
typedef struct
{
    short s0;
    short s2;
    short s4;
    short s6;
    short s8;
    short sA;
    short sC;
    short sE;
    short s10;
    short s12;
} NameGrid;
typedef struct
{
    DVECTOR pos;
    char* chars_4;
} NameCharRow;
extern NameCharRow dword_800B8190[][7];
typedef struct
{
    int f0;
    int f4;
    int f8;
    int fC;
} NameSprite;
extern NameSprite name_800B82F4;
extern NameSprite name_800B8388;
extern char name_800B83A0[];
extern void DrawMenuWindows_8002A5A4(void* p);
extern void DrawButtonHelpBar_8002B004(void* a, void* b, int c);
extern unsigned short uiColor_8008B590;
extern void DrawCharRow_800B75EC(NameCharRow row);
extern void DrawNameField_800B7414(NameEntry* p);
extern void sub_800B7A88(NameEntry* p);
extern void sub_800B7DC4(NameEntry* p);
extern void sub_800B7E30(NameEntry* p);
extern void sub_800B7D60(NameEntry* p);
extern void SwitchCharPage_800B7CD8(NameEntry* p);
extern void DrawWindow_80042460(void* a, void* b, void* c, int d);
extern NameGrid name_800B8200[];
extern int MoveCursorWithSfx_800B80E4(NameCursor* p);
extern int nameEntryActive_800B83F8;
extern char defaultName_800B83B8[0x14];
extern unsigned short padPressed_8009194C;
extern short name_800B8204[];
extern void sub_800B7AB4(NameEntry* p);
extern void RestoreSavedName_800B7F08(NameEntry* p);
extern int SavedNameLength_800B7F70(NameEntry* p);
extern void ClampNameLength_800B7CA4(NameEntry* p);

INCLUDE_OVERLAY_ASM(name, dword_800B6D00);

extern void DrawMenuBackground_8002BE10();
extern void EncodeName_8003F7C8(void* name, int a);
extern void DecodeText_8003F748(int a, void* name);
extern void SetFadeMode_8001C19C(int a, int b);
extern void name_800B6CA0();
extern void MoveNameCursor_800B78EC(NameEntry* p);
extern void UpdateNameEntry_800B70F4(NameEntry* p);
extern void sub_800B8018();

typedef struct NameBuf
{
    short s[11];
} NameBuf;
extern NameBuf name_800B6E30;
extern EventNode* name_8008D484;
void NameEntryTask_800B6FD8();
void StartNameEntry_800B6E4C(int a, int flags)
{
    EventEntry* e = AllocEventEntry_80043AF8(name_8008D484);
    NameEntry* p;
    NameBuf buf;
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        p = (NameEntry*)e->buffer;
        p->flags_0 = flags;
        p->field_4 = 0;
        p->field_8 = 0;
        p->pad_A = 0;
        p->field_C = 0;
        p->pad_E = 0;
        p->length_44 = 0;
        p->field_40 = a;
        buf = name_800B6E30;
        CopyPlayerName_8003F860((unsigned char*)a, (unsigned short*)&buf);
        DecodeText_8003F748(1, &buf);
        sub_800B8018(&buf);
        MemCopy_800403E8(p->field_28, &buf, 0x14);
        MemCopy_800403E8(p->name_10, &buf, 0x14);
        p->c_24 = 0;
        p->c_25 = 0;
        p->length_44 = SavedNameLength_800B7F70(p);
        if (p->flags_0 & 0x10)
        {
            DrawMenuBackground_8002BE10();
        }
        UpdateNameEntry_800B70F4(p);
        nameEntryActive_800B83F8 = 1;
        e->cb_8 = (EventEntryFn)NameEntryTask_800B6FD8;
    }
}

// Matched
int IsNameEntryActive_800B6FC8(void)
{
    return nameEntryActive_800B83F8;
}

void NameEntryTask_800B6FD8(EventEntry* e, NameEntry* p)
{
    NameEntry* q = p;
    if (p->flags_0 & 0x10)
    {
        DrawMenuBackground_8002BE10();
    }
    MoveNameCursor_800B78EC(p);
    UpdateNameEntry_800B70F4(p);
    if (p->flags_0 & 1)
    {
        sub_800B8018(p->name_10);
        EncodeName_8003F7C8(p->name_10, p->field_40);
        nameEntryActive_800B83F8 = 0;
        DecodeText_8003F748(2, p->name_10);
        e->flags = (e->flags & ~1) | 0x8000;
        if (p->flags_0 & 0x10)
        {
            SetFadeMode_8001C19C(0, 0x20);
            name_800B6CA0();
        }
    }
    else if (IsConfirmPressedP1_8003D380(0) || IsCancelPressedP1_8003D41C(0))
    {
        if (q->flags_0 & 2)
        {
            q->flags_0 &= ~2;
        }
    }
}

void UpdateNameEntry_800B70F4(NameEntry* p)
{
    short pos[2];
    RECT r;
    NameWinStyle c;
    union
    {
        unsigned short pos[2];
        NameWinStyle style;
    } t; // the help bar position, then the style of the character window
    int k;
    switch (p->field_8)
    {
    case 0:
        pos[0] = name_800B8200[0].s10 + (p->field_C % name_800B8200[0].s6) * name_800B8200[0].sC;
        pos[1] = name_800B8200[0].s12 + (p->field_C / name_800B8200[0].s6) * name_800B8200[0].sE;
        r.x = pos[0] - 1;
        r.y = pos[1] - 1;
        r.w = 0xD;
        r.h = 0xD;
        c.colors_2 = 1;
        c.frame_3 = 1;
        c.color_0 = uiColor_8008B590;
        DrawWindow_80042460(&r, &c, pOT_8008D454 + 14, GetTime30Hz_8002C64C());
        name_800B8388.f4 = 0;
        name_800B82F4.f4 = 0;
        name_800B8388.f0 = 4;
        break;
    case 1:
        p->pad_A = p->field_C;
        name_800B8388.f4 = GetTime30Hz_8002C64C();
        name_800B82F4.f4 = 0;
        name_800B8388.f0 = 2;
        break;
    case 2:
        name_800B82F4.fC = p->field_C;
        name_800B82F4.f4 = GetTime30Hz_8002C64C();
        name_800B8388.f4 = 0;
        name_800B8388.f0 = 4;
        break;
    }
    name_800B8388.fC = p->pad_A;
    DrawNameField_800B7414(p);
    DrawMenuWindows_8002A5A4(&name_800B8388);
    DrawMenuWindows_8002A5A4(&name_800B82F4);
    t.pos[0] = 0xA;
    t.pos[1] = 0xD6;
    DrawButtonHelpBar_8002B004(name_800B83A0, t.pos, 1);
    r.x = 0xA;
    r.y = 0x61;
    r.w = 0xC2;
    r.h = 0x65;
    t.style.colors_2 = 1;
    t.style.frame_3 = 1;
    t.style.color_0 = uiColor_8008B590;
    DrawWindow_80042460(&r, &t.style, pOT_8008D454 + 14, 0);
    for (k = 0; dword_800B8190[p->pad_A][k].chars_4; k++)
    {
        DrawCharRow_800B75EC(dword_800B8190[p->pad_A][k]);
    }
    switch (p->field_8)
    {
    case 0:
        sub_800B7A88(p);
        break;
    case 1:
        sub_800B7DC4(p);
        break;
    case 2:
        sub_800B7E30(p);
        break;
    }
    sub_800B7D60(p);
    SwitchCharPage_800B7CD8(p);
}

typedef struct
{
    unsigned short color;
    unsigned char a;
    unsigned char b;
} NameWinColor;
typedef struct
{
    short x;
    short y;
    void* text;
} NameTextItem;
extern void DrawText_8003E91C(int a, void* b, void* c, int d);
extern void DrawWindow_80042460(void* a, void* b, void* c, int d);
extern void DrawUiTiySprt_8002C06C(void* pos, int a, int b);
extern int MeasureTextWidth_8003E4C8(void* p);
extern char name_800B6E48[];
void DrawNameField_800B7414(NameEntry* p)
{
    NameTextItem item;
    short pos[2];
    short pos2[2];
    RECT r;
    NameWinColor c1;
    NameWinColor c2;
    short pos3[2];
    int i;
    item.x = 0x74;
    item.y = 0x28;
    item.text = p->name_10;
    pos[0] = 0x74;
    pos[1] = 0x28;
    DrawText_8003E91C(2, p->name_10, pos, 1);
    pos2[0] = 0x49;
    pos2[1] = 0x28;
    DrawUiTiySprt_8002C06C(pos2, 0x11, 1);
    r.x = 0x45;
    r.y = 0x24;
    r.w = 0xB8;
    r.h = 0x14;
    c1.color = saveData_8008B570.uiColor_20.i;
    c1.a = 0;
    c1.b = 1;
    DrawWindow_80042460(&r, &c1, pOT_8008D454 + 14, 0);
    r.x = MeasureTextWidth_8003E4C8(p->name_10) + 0x74;
    r.y = 0x27;
    r.w = 8;
    r.h = 0xC;
    c2.color = saveData_8008B570.uiColor_20.i;
    c2.a = 1;
    c2.b = 1;
    DrawWindow_80042460(&r, &c2, pOT_8008D454 + 14, GetTime30Hz_8002C64C());
    for (i = 0; i <= 9 - p->length_44 / 2; i++)
    {
        pos3[0] = MeasureTextWidth_8003E4C8(p->name_10) + 0x74 + i * 8;
        pos3[1] = 0x30;
        DrawText_8003E91C(2, name_800B6E48, pos3, 1);
    }
}

extern int charWidthThresholds_80086898[][12];
void DrawCharRow_800B75EC(NameCharRow row)
{
    Font* p = &fonts_80095FB0[2];
    unsigned short* s = EncodeText_8003F684(2, (unsigned short*)row.chars_4);
    int col;
    unsigned short c;
    short k;
    int off;
    int v;
    int q;
    c = *s;
    while (c != 0)
    {
        s++;
        if (c < 0x7F)
        {
            off = 2;
            for (k = 12; k != 0; k--)
            {
                if (c - 1 < charWidthThresholds_80086898[1][k - 1])
                {
                    off -= k;
                    break;
                }
            }
            off = -off;
            off /= 2;
            v = c - 1;
            q = v / 126;
            p->clut_E = GetClut(p->clutX_20, p->clutY_22 + q);
            v = v % 126;
            col = v % (unsigned short)p->field_1C;
            v = v / (unsigned short)p->field_1C;
            p->u_C = p->field_18 + p->w_10 * col;
            p->v_D = p->field_1A + p->h_12 * v;
            p->x0_8 = row.pos.vx + off;
            p->y0_A = row.pos.vy;
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)p)[0];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)p)[1];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[2] = ((u_long*)p)[2];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[3] = ((u_long*)p)[3];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[4] = ((u_long*)p)[4];
            addPrim(&pOT_8008D454[0], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
            primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 0x14;
        }
        row.pos.vx += 0x10;
        c = *s;
    }
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)p->tpage_14)[0];
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)p->tpage_14)[1];
    addPrim(&pOT_8008D454[0], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 8;
}

void MoveNameCursor_800B78EC(NameEntry* p)
{
    NameCursor cur;
    if (p->field_8 == 0)
    {
        p->pad_E = p->field_C;
    }
    cur.flags = name_800B8200[p->field_8].s2;
    cur.s4 = 0;
    cur.s8 = name_800B8200[p->field_8].s6;
    cur.sA = name_800B8200[p->field_8].s8;
    cur.s6 = p->field_C;
    p->field_4 = MoveCursorWithSfx_800B80E4(&cur);
    p->field_C = cur.s6;
    if (p->field_8 == 0)
    {
        if (p->field_4 == 1)
        {
            p->field_8 = 1;
            p->field_C = p->pad_A;
        }
    }
    else if (p->field_8 == 1)
    {
        if (p->field_4 == 1)
        {
            p->field_C = 0;
            p->field_8 = 2;
        }
        else if (p->field_4 == 2)
        {
            if ((short)p->pad_E % 12 != 0)
            {
                p->field_C = p->pad_E;
            }
            else
            {
                p->field_C = p->pad_E + 11;
            }
            p->field_8 = 0;
        }
    }
    else if (p->field_8 == 2)
    {
        if (p->field_4 == 2)
        {
            p->field_8 = 1;
            p->field_C = p->pad_A;
        }
    }
    p->field_4 = 0;
}

// Matched
void sub_800B7A88(NameEntry* p)
{
    sub_800B7AB4(p);
    ClampNameLength_800B7CA4(p);
}

#if 0
// Not matched: frame/regalloc: the original keeps 6 saved regs (two copies of the list address, the constant 2 for length_44 - 2) and recomputes the list[i] address for the second EncodeText call
extern void DeleteNameChar_800B7C68(NameEntry* p);
void sub_800B7AB4(NameEntry* p)
{
    unsigned short* list[2];
    short i = 0;
    list[0] = 0;
    if (IsConfirmPressedP1_8003D380(0) && p->length_44 < 0x13)
    {
        PlaySfx_80031494(0x7E);
        ((char*)p->name_10)[p->length_44] = dword_800B8190[p->pad_A][p->field_C / name_800B8200[p->field_8].s6].chars_4[(p->field_C % name_800B8200[p->field_8].s6) * 2];
        p->length_44 += 2;
    }
    if (IsCancelPressedP1_8003D41C(1))
    {
        DeleteNameChar_800B7C68(p);
    }
    for (i = 0; list[i]; i++)
    {
        if (*EncodeText_8003F684(2, list[i]) == ((unsigned char*)p->name_10)[p->length_44 - 2])
        {
            ((unsigned char*)p->name_10)[p->length_44 - 2] = *EncodeText_8003F684(2, list[i]);
            break;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(name, sub_800B7AB4);

void DeleteNameChar_800B7C68(NameEntry* p)
{
    if (p->length_44)
    {
        *(short*)((char*)p->name_10 + p->length_44) = 0;
        p->length_44 -= 2;
        *(short*)((char*)p->name_10 + p->length_44) = 0;
    }
}

// Matched
void ClampNameLength_800B7CA4(NameEntry* p)
{
    if (p->length_44 >= 0x15)
    {
        p->length_44 = 0x14;
    }
    if (p->length_44 < 0)
    {
        p->length_44 = 0;
    }
}

void SwitchCharPage_800B7CD8(NameEntry* p)
{
    if (padPressed_8009194C & 2)
    {
        if (++p->pad_A > name_800B8204[0] - 1)
        {
            p->pad_A = 0;
        }
    }
    else if (padPressed_8009194C & 8)
    {
        p->pad_A--;
        if (p->pad_A < 0)
        {
            p->pad_A = name_800B8204[0] - 1;
        }
    }
}

// Matched
void sub_800B7D60(NameEntry* p)
{
    if (padPressed_8009194C & 0x800)
    {
        p->field_8 = 2;
        p->field_C = 2;
    }
    if (padPressed_8009194C & 0x100)
    {
        if (p->flags_0 & 8)
        {
            RestoreSavedName_800B7F08(p);
        }
    }
}

void sub_800B7DC4(NameEntry* p)
{
    if (IsConfirmPressedP1_8003D380(0))
    {
        if (p->field_C >= 2)
        {
            return;
        }
        if (p->field_C < 0)
        {
            return;
        }
        p->pad_A = p->field_C;
    }
    if (IsCancelPressedP1_8003D41C(0))
    {
        p->field_8 = 0;
        p->field_C = p->pad_E;
    }
}

extern void ResetNameToDefault_800B7FA0(NameEntry* p);
extern int IsNameBlank_800B7FD8(unsigned char* p);
void sub_800B7E30(NameEntry* p)
{
    if (IsConfirmPressedP1_8003D380(0))
    {
        switch (p->field_C)
        {
        case 0:
            ResetNameToDefault_800B7FA0(p);
            PlaySfx_80031494(0x7E);
            break;
        case 1:
            RestoreSavedName_800B7F08(p);
            PlaySfx_80031494(0x7E);
            break;
        case 2:
            if (!IsNameBlank_800B7FD8((unsigned char*)p->name_10))
            {
                PlaySfx_80031494(0x7E);
                p->flags_0 |= 1;
            }
            break;
        default:
            return;
        }
    }
    if (IsCancelPressedP1_8003D41C(0))
    {
        p->field_8 = 0;
        p->field_C = p->pad_E;
    }
}

// Matched
void RestoreSavedName_800B7F08(NameEntry* p)
{
    int i;
    short* s;

    MemCopy_800403E8(p->name_10, p->field_28, 0x14);
    s = p->field_28;
    i = 0;
    for (i = 0; i < 10; s++)
    {
        i++;
        if (*s == 0)
        {
            break;
        }
    }
    p->length_44 = SavedNameLength_800B7F70(p);
}

int SavedNameLength_800B7F70(NameEntry* p)
{
    int n;
    short* q;
    for (n = 0, q = p->field_28; n < 10; n++, q++)
    {
        if (*q == 0)
        {
            break;
        }
    }
    return n * 2;
}

// Matched
void ResetNameToDefault_800B7FA0(NameEntry* p)
{
    MemCopy_800403E8(p->name_10, defaultName_800B83B8, 0x14);
    p->length_44 = 0;
}

// Matched
int IsNameBlank_800B7FD8(unsigned char* p)
{
    int n = 0;
    do
    {
        if (*p != 0x91)
        {
            if (*p != 0)
            {
                return 0;
            }
        }
        n++;
        p += 2;
    } while (n < 10);
    return 1;
}

// Matched
void sub_800B8018(void)
{
}

extern short name_800B83C8[];
extern short name_800B83D0[];
void sub_800B8020(NameCursor* p, int k)
{
    if (p->flags & name_800B83C8[k - 1])
    {
        if ((p->flags & 1) && (unsigned)(k - 1) < 2)
        {
            p->s6 += name_800B83D0[k - 1] * (p->s8 - 1);
        }
        else if ((p->flags & 2) && (unsigned)(k - 3) < 2)
        {
            p->s6 += name_800B83D0[k - 1] * p->s8 * (p->sA - 1);
        }
    }
}

typedef struct
{
    int mask;
    int result;
} NameCursorTbl;
extern NameCursorTbl name_800B83D8[];
extern int MoveGridCursorP1_8003D630();
extern void PlaySfx_80031494(int);
int MoveCursorWithSfx_800B80E4(NameCursor* p)
{
    int old = (short)p->s6;
    int k = MoveGridCursorP1_8003D630();
    if (k)
    {
        sub_800B8020(p, k);
        if (p->flags & name_800B83D8[k - 1].mask)
        {
            PlaySfx_80031494(0x7F);
            return name_800B83D8[k - 1].result;
        }
    }
    if (old != (short)p->s6)
    {
        PlaySfx_80031494(0x7F);
    }
    return 0;
}

INCLUDE_OVERLAY_ASM(name, dword_800B8190);
