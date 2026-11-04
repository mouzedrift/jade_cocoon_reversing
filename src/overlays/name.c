// NAME.BIN - player name selection screen, loaded at 0x800B6D00
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "name.h"
typedef struct
{
    unsigned short flags_0;
    char pad_2[2];
    int moveResult_4; // MoveCursorWithSfx_800B80E4 result
    short focus_8; // 0 character grid, 1 page selector, 2 commands
    short page_A;
    short cursor_C;
    unsigned short gridCursor_E;
    short name_10[10]; // SJIS characters, the first byte of a full-width character is >= 0x81
    char c_24;
    char c_25;
    short pad_26;
    short savedName_28[10];
    short pad_3C[2];
    int nameDest_40;
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
    unsigned short unused_4;
    unsigned short pos_6;
    short cols_8;
    short rows_A;
} NameCursor;
extern void DrawMenuWindows_8002A5A4(void* p);
extern void DrawButtonHelpBar_8002B004(void* a, void* b, int c);
extern unsigned short uiColor_8008B590;
extern void DrawCharRow_800B75EC(NameCharRow row);
extern void DrawNameField_800B7414(NameEntry* p);
extern void HandleCharGridInput_800B7A88(NameEntry* p);
extern void HandlePageSelectInput_800B7DC4(NameEntry* p);
extern void HandleNameCommandInput_800B7E30(NameEntry* p);
extern // Start jumps to the commands, Select restores the saved name (flags 8)
void HandleNameShortcutButtons_800B7D60(NameEntry* p);
extern void SwitchCharPage_800B7CD8(NameEntry* p);
extern void DrawWindow_80042460(void* a, void* b, void* c, int d);
extern int MoveCursorWithSfx_800B80E4(NameCursor* p);
extern unsigned short padPressed_8009194C;
extern short charPageCount_800B8204[];
extern void InputNameChar_800B7AB4(NameEntry* p);
extern void RestoreSavedName_800B7F08(NameEntry* p);
extern int SavedNameLength_800B7F70(NameEntry* p);
extern void ClampNameLength_800B7CA4(NameEntry* p);

int overlayId_800B6D00 SDATA = 39;
const char charRowBlank_800B6D04[28] = "\201@\201@\201@\201@\201@\201@\201@\201@\201@\201@\201@\201@";
const char charRowDigits2_800B6D20[28] = "\202U\202V\202W\202X\202O\201@\201@\201`\201\227\201[\201@\201@";
const char charRowDigits1_800B6D3C[28] = "\202P\202Q\202R\202S\202T\201@\201@\201C\201E\201H\201I\201@";
const char aYz_800B6D58[28] = "\202\231\202\232\201@\201@\201@\201@\201@\201@\201@\201@\201@\201@";
const char aMnopqrstuvwx_800B6D74[28] = "\202\215\202\216\202\217\202\220\202\221\202\222\202\223\202\224\202\225\202\226\202\227\202\230";
const char aAbcdefghijkl_800B6D90[28] = "\202\201\202\202\202\203\202\204\202\205\202\206\202\207\202\210\202\211\202\212\202\213\202\214";
const char aYZ_800B6DAC[28] = "\202x\202y\201@\201@\201@\201@\201@\201@\201@\201@\201@\201@";
const char aMNOPQRSTUVWX_800B6DC8[28] = "\202l\202m\202n\202o\202p\202q\202r\202s\202t\202u\202v\202w";
const char aABCDEFGHIJKL_800B6DE4[28] = "\202`\202a\202b\202c\202d\202e\202f\202g\202h\202i\202j\202k";
const char aABC_800B6E00[] = "\202`\202a\202b"; // ABC
const char a123_800B6E08[] = "\202P\202Q\202R"; // 123
const char aCancel_800B6E10[] = "\202b\202\201\202\216\202\203\202\205\202\214"; // Cancel
const char aSelect_800B6E20[] = "\202r\202\205\202\214\202\205\202\203\202\224"; // Select
const NameBuf nameBufInit_800B6E30 = { { -1 } };
const char nameUnderlineChar_800B6E48[] = "\201["; // ー

extern void DrawMenuBackground_8002BE10();
extern void EncodeName_8003F7C8(void* name, int a);
extern void DecodeText_8003F748(int a, void* name);
extern void SetFadeMode_8001C19C(int a, int b);
extern void name_800B6CA0();
extern void MoveNameCursor_800B78EC(NameEntry* p);
extern void UpdateNameEntry_800B70F4(NameEntry* p);
extern void NameEntryNop_800B8018();

extern EventNode* name_8008D484;
void NameEntryTask_800B6FD8();
void StartNameEntry_800B6E4C(int nameDest, int flags)
{
    EventEntry* e = AllocEventEntry_80043AF8(name_8008D484);
    NameEntry* p;
    NameBuf buf;
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        p = (NameEntry*)e->buffer;
        p->flags_0 = flags;
        p->moveResult_4 = 0;
        p->focus_8 = 0;
        p->page_A = 0;
        p->cursor_C = 0;
        p->gridCursor_E = 0;
        p->length_44 = 0;
        p->nameDest_40 = nameDest;
        buf = nameBufInit_800B6E30;
        CopyPlayerName_8003F860((unsigned char*)nameDest, (unsigned short*)&buf);
        DecodeText_8003F748(1, &buf);
        NameEntryNop_800B8018(&buf);
        MemCopy_800403E8(p->savedName_28, &buf, 0x14);
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
        NameEntryNop_800B8018(p->name_10);
        EncodeName_8003F7C8(p->name_10, p->nameDest_40);
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
    switch (p->focus_8)
    {
    case 0:
        pos[0] = cursorGrids_800B8200[0].x_10 + (p->cursor_C % cursorGrids_800B8200[0].cols_6) * cursorGrids_800B8200[0].cellW_C;
        pos[1] = cursorGrids_800B8200[0].y_12 + (p->cursor_C / cursorGrids_800B8200[0].cols_6) * cursorGrids_800B8200[0].cellH_E;
        r.x = pos[0] - 1;
        r.y = pos[1] - 1;
        r.w = 0xD;
        r.h = 0xD;
        c.colors_2 = 1;
        c.frame_3 = 1;
        c.color_0 = uiColor_8008B590;
        DrawWindow_80042460(&r, &c, pOT_8008D454 + 14, GetTime30Hz_8002C64C());
        pageMenu_800B8388.time_4 = 0;
        cmdMenu_800B82F4.time_4 = 0;
        pageMenu_800B8388.mode_0 = 4;
        break;
    case 1:
        p->page_A = p->cursor_C;
        pageMenu_800B8388.time_4 = GetTime30Hz_8002C64C();
        cmdMenu_800B82F4.time_4 = 0;
        pageMenu_800B8388.mode_0 = 2;
        break;
    case 2:
        cmdMenu_800B82F4.cursor_C = p->cursor_C;
        cmdMenu_800B82F4.time_4 = GetTime30Hz_8002C64C();
        pageMenu_800B8388.time_4 = 0;
        pageMenu_800B8388.mode_0 = 4;
        break;
    }
    pageMenu_800B8388.cursor_C = p->page_A;
    DrawNameField_800B7414(p);
    DrawMenuWindows_8002A5A4(&pageMenu_800B8388);
    DrawMenuWindows_8002A5A4(&cmdMenu_800B82F4);
    t.pos[0] = 0xA;
    t.pos[1] = 0xD6;
    DrawButtonHelpBar_8002B004(helpBar_800B83A0, t.pos, 1);
    r.x = 0xA;
    r.y = 0x61;
    r.w = 0xC2;
    r.h = 0x65;
    t.style.colors_2 = 1;
    t.style.frame_3 = 1;
    t.style.color_0 = uiColor_8008B590;
    DrawWindow_80042460(&r, &t.style, pOT_8008D454 + 14, 0);
    for (k = 0; charPages_800B8190[p->page_A][k].chars_4; k++)
    {
        DrawCharRow_800B75EC(charPages_800B8190[p->page_A][k]);
    }
    switch (p->focus_8)
    {
    case 0:
        HandleCharGridInput_800B7A88(p);
        break;
    case 1:
        HandlePageSelectInput_800B7DC4(p);
        break;
    case 2:
        HandleNameCommandInput_800B7E30(p);
        break;
    }
    HandleNameShortcutButtons_800B7D60(p);
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
        DrawText_8003E91C(2, nameUnderlineChar_800B6E48, pos3, 1);
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
    if (p->focus_8 == 0)
    {
        p->gridCursor_E = p->cursor_C;
    }
    cur.flags = cursorGrids_800B8200[p->focus_8].cursorFlags_2;
    cur.unused_4 = 0;
    cur.cols_8 = cursorGrids_800B8200[p->focus_8].cols_6;
    cur.rows_A = cursorGrids_800B8200[p->focus_8].rows_8;
    cur.pos_6 = p->cursor_C;
    p->moveResult_4 = MoveCursorWithSfx_800B80E4(&cur);
    p->cursor_C = cur.pos_6;
    if (p->focus_8 == 0)
    {
        if (p->moveResult_4 == 1)
        {
            p->focus_8 = 1;
            p->cursor_C = p->page_A;
        }
    }
    else if (p->focus_8 == 1)
    {
        if (p->moveResult_4 == 1)
        {
            p->cursor_C = 0;
            p->focus_8 = 2;
        }
        else if (p->moveResult_4 == 2)
        {
            if ((short)p->gridCursor_E % 12 != 0)
            {
                p->cursor_C = p->gridCursor_E;
            }
            else
            {
                p->cursor_C = p->gridCursor_E + 11;
            }
            p->focus_8 = 0;
        }
    }
    else if (p->focus_8 == 2)
    {
        if (p->moveResult_4 == 2)
        {
            p->focus_8 = 1;
            p->cursor_C = p->page_A;
        }
    }
    p->moveResult_4 = 0;
}

// Matched
void HandleCharGridInput_800B7A88(NameEntry* p)
{
    InputNameChar_800B7AB4(p);
    ClampNameLength_800B7CA4(p);
}

#if 0
// Not matched: frame/regalloc: the original keeps 6 saved regs (two copies of the list address, the constant 2 for length_44 - 2) and recomputes the list[i] address for the second EncodeText call
extern void DeleteNameChar_800B7C68(NameEntry* p);
void InputNameChar_800B7AB4(NameEntry* p)
{
    unsigned short* list[2];
    short i = 0;
    list[0] = 0;
    if (IsConfirmPressedP1_8003D380(0) && p->length_44 < 0x13)
    {
        PlaySfx_80031494(0x7E);
        ((char*)p->name_10)[p->length_44] = charPages_800B8190[p->page_A][p->cursor_C / cursorGrids_800B8200[p->focus_8].cols_6].chars_4[(p->cursor_C % cursorGrids_800B8200[p->focus_8].cols_6) * 2];
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
INCLUDE_OVERLAY_ASM(name, InputNameChar_800B7AB4);

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
        if (++p->page_A > charPageCount_800B8204[0] - 1)
        {
            p->page_A = 0;
        }
    }
    else if (padPressed_8009194C & 8)
    {
        p->page_A--;
        if (p->page_A < 0)
        {
            p->page_A = charPageCount_800B8204[0] - 1;
        }
    }
}

// Matched
// Start jumps to the commands, Select restores the saved name (flags 8)
void HandleNameShortcutButtons_800B7D60(NameEntry* p)
{
    if (padPressed_8009194C & 0x800)
    {
        p->focus_8 = 2;
        p->cursor_C = 2;
    }
    if (padPressed_8009194C & 0x100)
    {
        if (p->flags_0 & 8)
        {
            RestoreSavedName_800B7F08(p);
        }
    }
}

void HandlePageSelectInput_800B7DC4(NameEntry* p)
{
    if (IsConfirmPressedP1_8003D380(0))
    {
        if (p->cursor_C >= 2)
        {
            return;
        }
        if (p->cursor_C < 0)
        {
            return;
        }
        p->page_A = p->cursor_C;
    }
    if (IsCancelPressedP1_8003D41C(0))
    {
        p->focus_8 = 0;
        p->cursor_C = p->gridCursor_E;
    }
}

extern void ResetNameToDefault_800B7FA0(NameEntry* p);
extern int IsNameBlank_800B7FD8(unsigned char* p);
void HandleNameCommandInput_800B7E30(NameEntry* p)
{
    if (IsConfirmPressedP1_8003D380(0))
    {
        switch (p->cursor_C)
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
        p->focus_8 = 0;
        p->cursor_C = p->gridCursor_E;
    }
}

// Matched
void RestoreSavedName_800B7F08(NameEntry* p)
{
    int i;
    short* s;

    MemCopy_800403E8(p->name_10, p->savedName_28, 0x14);
    s = p->savedName_28;
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
    for (n = 0, q = p->savedName_28; n < 10; n++, q++)
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
void NameEntryNop_800B8018(void)
{
}

extern short cursorWrapMasks_800B83C8[];
// on a move off an edge (k = direction 1..4) of a wrapping area, jump to the opposite edge
void WrapGridCursor_800B8020(NameCursor* p, int k)
{
    if (p->flags & cursorWrapMasks_800B83C8[k - 1])
    {
        if ((p->flags & 1) && (unsigned)(k - 1) < 2)
        {
            p->pos_6 += cursorWrapDirs_800B83D0[k - 1] * (p->cols_8 - 1);
        }
        else if ((p->flags & 2) && (unsigned)(k - 3) < 2)
        {
            p->pos_6 += cursorWrapDirs_800B83D0[k - 1] * p->cols_8 * (p->rows_A - 1);
        }
    }
}

extern int MoveGridCursorP1_8003D630();
extern void PlaySfx_80031494(int);
int MoveCursorWithSfx_800B80E4(NameCursor* p)
{
    int old = (short)p->pos_6;
    int k = MoveGridCursorP1_8003D630();
    if (k)
    {
        WrapGridCursor_800B8020(p, k);
        if (p->flags & cursorExitTbl_800B83D8[k - 1].mask)
        {
            PlaySfx_80031494(0x7F);
            return cursorExitTbl_800B83D8[k - 1].result;
        }
    }
    if (old != (short)p->pos_6)
    {
        PlaySfx_80031494(0x7F);
    }
    return 0;
}

NameCharRow charPages_800B8190[2][7] = {
    {
        { { 13, 100 }, aABCDEFGHIJKL_800B6DE4 },
        { { 13, 116 }, aMNOPQRSTUVWX_800B6DC8 },
        { { 13, 132 }, aYZ_800B6DAC },
        { { 13, 148 }, aAbcdefghijkl_800B6D90 },
        { { 13, 164 }, aMnopqrstuvwx_800B6D74 },
        { { 13, 180 }, aYz_800B6D58 },
    },
    {
        { { 13, 100 }, charRowDigits1_800B6D3C },
        { { 13, 116 }, charRowDigits2_800B6D20 },
        { { 13, 132 }, charRowBlank_800B6D04 },
        { { 13, 148 }, charRowBlank_800B6D04 },
        { { 13, 164 }, charRowBlank_800B6D04 },
        { { 13, 180 }, charRowBlank_800B6D04 },
    },
};
NameGrid cursorGrids_800B8200[3] = {
    { 0, 6, 2, 12, 6, 0, 16, 16, 13, 100 },
    { 1, 14, 1, 1, 2, 0, 54, 10, 209, 99 },
    { 2, 10, 1, 1, 3, 0, 54, 10, 209, 99 },
};
int cmdItemDefault_800B823C[14] = {
    0x10008, 5, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x6100F6, 0x130040, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int cmdItemRestore_800B8274[14] = {
    0x10008, 142, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x7500F6, 0x130040, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int cmdItemOk_800B82AC[14] = {
    0x10008, 47, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x8E00F6, 0x130040, 0x40000, 1,
    0, 0, 0, -1, -1, -1,
};
void *cmdItemLists_800B82E4[4] = { (void *)cmdItemDefault_800B823C, (void *)cmdItemRestore_800B8274, (void *)cmdItemOk_800B82AC };
NameMenu cmdMenu_800B82F4 = { 2, 0, 8 };
void *cmdMenuItems_800B8304[2] = { (void *)cmdItemLists_800B82E4 };
int pageItemAbc_800B830C[14] = {
    0x20008, (int)aABC_800B6E00, 0, 0, 0x6100CE, 0xD0026, 0, 1,
    0, 0, 0, -1, -1, -1,
};
int pageItem123_800B8344[14] = {
    0x20008, (int)a123_800B6E08, 0, 0, 0x6F00CE, 0xD0026, 0, 1,
    0, 0, 0, -1, -1, -1,
};
void *pageItemLists_800B837C[3] = { (void *)pageItemAbc_800B830C, (void *)pageItem123_800B8344 };
NameMenu pageMenu_800B8388 = { 2, 0, 8 };
void *pageMenuItems_800B8398[2] = { (void *)pageItemLists_800B837C };
char helpBar_800B83A0[24] = { 16, 0, 0, 0, 32, 110, 11, 128, 167, 0, 0, 0, 16, 110, 11, 128, 255, 255, 255, 255 };
char defaultName_800B83B8[0x14] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 };
int cursorWrapMasks2_800B83CC = 0x20002;
short cursorWrapDirs_800B83D0[4] = { -1, 1, 1, -1 };
NameCursorTbl cursorExitTbl_800B83D8[4] = {
    { 4, 1 },
    { 8, 2 },
    { 16, 3 },
    { 32, 4 },
};
int nameEntryActive_800B83F8 = 0;
