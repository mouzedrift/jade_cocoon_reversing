// NAME.BIN - player name selection screen, loaded at 0x800B6D00
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "name.h"

int nameOverlayId_800B6D00 SDATA = 39;
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
MenuWindowItem cmdItemDefault_800B823C[2] = {
    { 8, 1, { .num = 5 }, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xF6, 0x61, 0x40, 0x13, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem cmdItemRestore_800B8274[2] = {
    { 8, 1, { .num = 142 }, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xF6, 0x75, 0x40, 0x13, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem cmdItemOk_800B82AC[2] = {
    { 8, 1, { .num = 47 }, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xF6, 0x8E, 0x40, 0x13, 0, 4 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem* cmdItemLists_800B82E4[4] = { cmdItemDefault_800B823C, cmdItemRestore_800B8274, cmdItemOk_800B82AC, NULL };
MenuWindowList cmdMenu_800B82F4 = { 2, 0, 8, 0, cmdItemLists_800B82E4, 0 };
MenuWindowItem pageItemAbc_800B830C[2] = {
    { 8, 2, aABC_800B6E00, NULL, NULL, 0xCE, 0x61, 0x26, 0xD, 0, 0 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem pageItem123_800B8344[2] = {
    { 8, 2, a123_800B6E08, NULL, NULL, 0xCE, 0x6F, 0x26, 0xD, 0, 0 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem* pageItemLists_800B837C[3] = { pageItemAbc_800B830C, pageItem123_800B8344, NULL };
MenuWindowList pageMenu_800B8388 = { 2, 0, 8, 0, pageItemLists_800B837C, 0 };
ButtonHelpEntry helpBar_800B83A0[3] = { { 16, aSelect_800B6E20 }, { 167, aCancel_800B6E10 }, { -1 } };
char defaultName_800B83B8[0x10] = { 0 }; // ResetNameToDefault_800B7FA0 copies 0x14 bytes from it
// WrapGridCursor_800B8020: the GridCursor flag that lets the cursor wrap, per direction (1 left .. 4 down)
short cursorWrapMasks_800B83C8[4] = { 1, 1, 2, 2 };
short cursorWrapDirs_800B83D0[4] = { -1, 1, 1, -1 };
NameCursorTbl cursorExitTbl_800B83D8[4] = {
    { 4, 1 },
    { 8, 2 },
    { 16, 3 },
    { 32, 4 },
};
int nameEntryActive_800B83F8 = 0;

void StartNameEntry_800B6E4C(unsigned char* nameDest, int flags)
{
    EventEntry* e = AllocEventEntry_80043AF8(nameEntryTask_8008D484);
    NameEntry* entry;
    NameBuf buf;
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        entry = (NameEntry*)e->buffer;
        entry->flags_0 = flags;
        entry->moveResult_4 = 0;
        entry->focus_8 = 0;
        entry->page_A = 0;
        entry->cursor_C = 0;
        entry->gridCursor_E = 0;
        entry->length_44 = 0;
        entry->nameDest_40 = nameDest;
        buf = nameBufInit_800B6E30;
        CopyPlayerName_8003F860(nameDest, (unsigned short*)&buf);
        DecodeText_8003F748(1, &buf);
        NameEntryNop_800B8018(&buf);
        MemCopy_800403E8(entry->savedName_28, &buf, 0x14);
        MemCopy_800403E8(entry->name_10, &buf, 0x14);
        entry->c_24 = 0;
        entry->c_25 = 0;
        entry->length_44 = SavedNameLength_800B7F70(entry);
        if (entry->flags_0 & 0x10)
        {
            DrawMenuBackground_8002BE10();
        }
        UpdateNameEntry_800B70F4(entry);
        nameEntryActive_800B83F8 = 1;
        e->cb_8 = (EventEntryFn)NameEntryTask_800B6FD8;
    }
}

int IsNameEntryActive_800B6FC8(void)
{
    return nameEntryActive_800B83F8;
}

void NameEntryTask_800B6FD8(EventEntry* e, NameEntry* entry)
{
    NameEntry* q = entry;
    if (entry->flags_0 & 0x10)
    {
        DrawMenuBackground_8002BE10();
    }
    MoveNameCursor_800B78EC(entry);
    UpdateNameEntry_800B70F4(entry);
    if (entry->flags_0 & 1)
    {
        NameEntryNop_800B8018(entry->name_10);
        EncodeName_8003F7C8(entry->name_10, entry->nameDest_40);
        nameEntryActive_800B83F8 = 0;
        DecodeText_8003F748(2, entry->name_10);
        e->flags = (e->flags & ~1) | 0x8000;
        if (entry->flags_0 & 0x10)
        {
            SetFadeMode_8001C19C(0, 0x20);
            ShopCtrlRequestShop_800B6CA0();
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

void UpdateNameEntry_800B70F4(NameEntry* entry)
{
    short pos[2];
    RECT rect;
    WindowStyle charStyle;
    union
    {
        unsigned short pos[2];
        WindowStyle style;
    } t; // the help bar position, then the style of the character window
    int k;
    switch (entry->focus_8)
    {
    case 0:
        pos[0] = cursorGrids_800B8200[0].x_10 + (entry->cursor_C % cursorGrids_800B8200[0].cols_6) * cursorGrids_800B8200[0].cellW_C;
        pos[1] = cursorGrids_800B8200[0].y_12 + (entry->cursor_C / cursorGrids_800B8200[0].cols_6) * cursorGrids_800B8200[0].cellH_E;
        rect.x = pos[0] - 1;
        rect.y = pos[1] - 1;
        rect.w = 0xD;
        rect.h = 0xD;
        charStyle.colorSet_2 = 1;
        charStyle.semiTrans_3 = 1;
        charStyle.color_0 = saveData_8008B570.uiColor_20.h;
        DrawWindow_80042460(&rect, &charStyle, pOT_8008D454 + 14, GetTime30Hz_8002C64C());
        pageMenu_800B8388.time_4 = 0;
        cmdMenu_800B82F4.time_4 = 0;
        pageMenu_800B8388.flags_0 = 4;
        break;
    case 1:
        entry->page_A = entry->cursor_C;
        pageMenu_800B8388.time_4 = GetTime30Hz_8002C64C();
        cmdMenu_800B82F4.time_4 = 0;
        pageMenu_800B8388.flags_0 = 2;
        break;
    case 2:
        cmdMenu_800B82F4.cursor_C = entry->cursor_C;
        cmdMenu_800B82F4.time_4 = GetTime30Hz_8002C64C();
        pageMenu_800B8388.time_4 = 0;
        pageMenu_800B8388.flags_0 = 4;
        break;
    }
    pageMenu_800B8388.cursor_C = entry->page_A;
    DrawNameField_800B7414(entry);
    DrawMenuWindows_8002A5A4(&pageMenu_800B8388);
    DrawMenuWindows_8002A5A4(&cmdMenu_800B82F4);
    t.pos[0] = 0xA;
    t.pos[1] = 0xD6;
    DrawButtonHelpBar_8002B004(helpBar_800B83A0, t.pos, 1);
    rect.x = 0xA;
    rect.y = 0x61;
    rect.w = 0xC2;
    rect.h = 0x65;
    t.style.colorSet_2 = 1;
    t.style.semiTrans_3 = 1;
    t.style.color_0 = saveData_8008B570.uiColor_20.h;
    DrawWindow_80042460(&rect, &t.style, pOT_8008D454 + 14, 0);
    for (k = 0; charPages_800B8190[entry->page_A][k].chars_4; k++)
    {
        DrawCharRow_800B75EC(charPages_800B8190[entry->page_A][k]);
    }
    switch (entry->focus_8)
    {
    case 0:
        HandleCharGridInput_800B7A88(entry);
        break;
    case 1:
        HandlePageSelectInput_800B7DC4(entry);
        break;
    case 2:
        HandleNameCommandInput_800B7E30(entry);
        break;
    }
    HandleNameShortcutButtons_800B7D60(entry);
    SwitchCharPage_800B7CD8(entry);
}

void DrawNameField_800B7414(NameEntry* entry)
{
    NameTextItem item;
    short pos[2];
    short pos2[2];
    RECT rect;
    WindowStyle fieldStyle;
    WindowStyle cursorStyle;
    short pos3[2];
    int i;
    item.x = 0x74;
    item.y = 0x28;
    item.text = entry->name_10;
    pos[0] = 0x74;
    pos[1] = 0x28;
    DrawText_8003E91C(2, entry->name_10, pos, 1);
    pos2[0] = 0x49;
    pos2[1] = 0x28;
    DrawUiTiySprt_8002C06C(pos2, 0x11, 1);
    rect.x = 0x45;
    rect.y = 0x24;
    rect.w = 0xB8;
    rect.h = 0x14;
    fieldStyle.color_0 = saveData_8008B570.uiColor_20.i;
    fieldStyle.colorSet_2 = 0;
    fieldStyle.semiTrans_3 = 1;
    DrawWindow_80042460(&rect, &fieldStyle, pOT_8008D454 + 14, 0);
    rect.x = MeasureTextWidth_8003E4C8(entry->name_10) + 0x74;
    rect.y = 0x27;
    rect.w = 8;
    rect.h = 0xC;
    cursorStyle.color_0 = saveData_8008B570.uiColor_20.i;
    cursorStyle.colorSet_2 = 1;
    cursorStyle.semiTrans_3 = 1;
    DrawWindow_80042460(&rect, &cursorStyle, pOT_8008D454 + 14, GetTime30Hz_8002C64C());
    for (i = 0; i <= 9 - entry->length_44 / 2; i++)
    {
        pos3[0] = MeasureTextWidth_8003E4C8(entry->name_10) + 0x74 + i * 8;
        pos3[1] = 0x30;
        DrawText_8003E91C(2, nameUnderlineChar_800B6E48, pos3, 1);
    }
}

void DrawCharRow_800B75EC(NameCharRow row)
{
    Font* font = &fonts_80095FB0[2];
    unsigned short* text = EncodeText_8003F684(2, (unsigned short*)row.chars_4);
    int col;
    unsigned short ch;
    short k;
    int off;
    int v;
    int clutRow;
    ch = *text;
    while (ch != 0)
    {
        text++;
        if (ch < 0x7F)
        {
            off = 2;
            for (k = 12; k != 0; k--)
            {
                if (ch - 1 < charWidthThresholds_80086898[1][k - 1])
                {
                    off -= k;
                    break;
                }
            }
            off = -off;
            off /= 2;
            v = ch - 1;
            clutRow = v / 126;
            font->clut_E = GetClut(font->clutX_20, font->clutY_22 + clutRow);
            v = v % 126;
            col = v % (unsigned short)font->columns_1C;
            v = v / (unsigned short)font->columns_1C;
            font->u_C = font->u0_18 + font->w_10 * col;
            font->v_D = font->v0_1A + font->h_12 * v;
            font->x0_8 = row.pos.vx + off;
            font->y0_A = row.pos.vy;
            COPY_SPRT(primAllocPtr_800960A8[bDoubleBuffer_8008D428], font);
            addPrim(&pOT_8008D454[0], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
            primAllocPtr_800960A8[bDoubleBuffer_8008D428] += sizeof(SPRT);
        }
        row.pos.vx += 0x10;
        ch = *text;
    }
    COPY_DR_TPAGE(primAllocPtr_800960A8[bDoubleBuffer_8008D428], font->tpage_14);
    addPrim(&pOT_8008D454[0], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += sizeof(DR_TPAGE);
}

void MoveNameCursor_800B78EC(NameEntry* entry)
{
    GridCursor cur;
    if (entry->focus_8 == 0)
    {
        entry->gridCursor_E = entry->cursor_C;
    }
    cur.flags_0 = cursorGrids_800B8200[entry->focus_8].cursorFlags_2;
    cur.field_4 = 0;
    cur.cols_8 = cursorGrids_800B8200[entry->focus_8].cols_6;
    cur.rows_A = cursorGrids_800B8200[entry->focus_8].rows_8;
    cur.pos_6 = entry->cursor_C;
    entry->moveResult_4 = MoveCursorWithSfx_800B80E4(&cur);
    entry->cursor_C = cur.pos_6;
    if (entry->focus_8 == 0)
    {
        if (entry->moveResult_4 == 1)
        {
            entry->focus_8 = 1;
            entry->cursor_C = entry->page_A;
        }
    }
    else if (entry->focus_8 == 1)
    {
        if (entry->moveResult_4 == 1)
        {
            entry->cursor_C = 0;
            entry->focus_8 = 2;
        }
        else if (entry->moveResult_4 == 2)
        {
            if ((short)entry->gridCursor_E % 12 != 0)
            {
                entry->cursor_C = entry->gridCursor_E;
            }
            else
            {
                entry->cursor_C = entry->gridCursor_E + 11;
            }
            entry->focus_8 = 0;
        }
    }
    else if (entry->focus_8 == 2)
    {
        if (entry->moveResult_4 == 2)
        {
            entry->focus_8 = 1;
            entry->cursor_C = entry->page_A;
        }
    }
    entry->moveResult_4 = 0;
}

void HandleCharGridInput_800B7A88(NameEntry* entry)
{
    InputNameChar_800B7AB4(entry);
    ClampNameLength_800B7CA4(entry);
}

void InputNameChar_800B7AB4(NameEntry* entry)
{
    unsigned short* list[2];
    unsigned short** p;
    unsigned short** q;
    short i = 0;
    int charLen;
    p = list;
    q = list;
    list[0] = 0;
    if (IsConfirmPressedP1_8003D380(0) && entry->length_44 < 0x13)
    {
        PlaySfx_80031494(0x7E);
        entry->name_10[entry->length_44] = charPages_800B8190[entry->page_A][entry->cursor_C / cursorGrids_800B8200[entry->focus_8].cols_6].chars_4[(entry->cursor_C % cursorGrids_800B8200[entry->focus_8].cols_6) * 2];
        entry->length_44 += 2;
    }
    if (IsCancelPressedP1_8003D41C(1))
    {
        DeleteNameChar_800B7C68(entry);
    }
    charLen = 2; // bytes per SJIS character
    for (; p[i]; i++)
    {
        if (*EncodeText_8003F684(2, p[i]) == entry->name_10[entry->length_44 - charLen])
        {
            entry->name_10[entry->length_44 - charLen] = *(unsigned char*)EncodeText_8003F684(2, q[i]);
            break;
        }
    }
}

void DeleteNameChar_800B7C68(NameEntry* entry)
{
    if (entry->length_44)
    {
        *(short*)((char*)entry->name_10 + entry->length_44) = 0;
        entry->length_44 -= 2;
        *(short*)((char*)entry->name_10 + entry->length_44) = 0;
    }
}

void ClampNameLength_800B7CA4(NameEntry* entry)
{
    if (entry->length_44 >= 0x15)
    {
        entry->length_44 = 0x14;
    }
    if (entry->length_44 < 0)
    {
        entry->length_44 = 0;
    }
}

void SwitchCharPage_800B7CD8(NameEntry* entry)
{
    if (padPressed_8009194C[0] & 2)
    {
        if (++entry->page_A > cursorGrids_800B8200[0].count_4 - 1)
        {
            entry->page_A = 0;
        }
    }
    else if (padPressed_8009194C[0] & 8)
    {
        entry->page_A--;
        if (entry->page_A < 0)
        {
            entry->page_A = cursorGrids_800B8200[0].count_4 - 1;
        }
    }
}

// Start jumps to the commands, Select restores the saved name (flags 8)
void HandleNameShortcutButtons_800B7D60(NameEntry* entry)
{
    if (padPressed_8009194C[0] & 0x800)
    {
        entry->focus_8 = 2;
        entry->cursor_C = 2;
    }
    if (padPressed_8009194C[0] & 0x100)
    {
        if (entry->flags_0 & 8)
        {
            RestoreSavedName_800B7F08(entry);
        }
    }
}

void HandlePageSelectInput_800B7DC4(NameEntry* entry)
{
    if (IsConfirmPressedP1_8003D380(0))
    {
        if (entry->cursor_C >= 2)
        {
            return;
        }
        if (entry->cursor_C < 0)
        {
            return;
        }
        entry->page_A = entry->cursor_C;
    }
    if (IsCancelPressedP1_8003D41C(0))
    {
        entry->focus_8 = 0;
        entry->cursor_C = entry->gridCursor_E;
    }
}

void HandleNameCommandInput_800B7E30(NameEntry* entry)
{
    if (IsConfirmPressedP1_8003D380(0))
    {
        switch (entry->cursor_C)
        {
        case 0:
            ResetNameToDefault_800B7FA0(entry);
            PlaySfx_80031494(0x7E);
            break;
        case 1:
            RestoreSavedName_800B7F08(entry);
            PlaySfx_80031494(0x7E);
            break;
        case 2:
            if (!IsNameBlank_800B7FD8((unsigned char*)entry->name_10))
            {
                PlaySfx_80031494(0x7E);
                entry->flags_0 |= 1;
            }
            break;
        default:
            return;
        }
    }
    if (IsCancelPressedP1_8003D41C(0))
    {
        entry->focus_8 = 0;
        entry->cursor_C = entry->gridCursor_E;
    }
}

void RestoreSavedName_800B7F08(NameEntry* entry)
{
    int i;
    short* ch;

    MemCopy_800403E8(entry->name_10, entry->savedName_28, 0x14);
    ch = entry->savedName_28;
    i = 0;
    for (i = 0; i < 10; ch++)
    {
        i++;
        if (*ch == 0)
        {
            break;
        }
    }
    entry->length_44 = SavedNameLength_800B7F70(entry);
}

int SavedNameLength_800B7F70(NameEntry* entry)
{
    int n;
    short* ch;
    for (n = 0, ch = entry->savedName_28; n < 10; n++, ch++)
    {
        if (*ch == 0)
        {
            break;
        }
    }
    return n * 2;
}

void ResetNameToDefault_800B7FA0(NameEntry* entry)
{
    MemCopy_800403E8(entry->name_10, defaultName_800B83B8, 0x14);
    entry->length_44 = 0;
}

int IsNameBlank_800B7FD8(unsigned char* name)
{
    int n = 0;
    do
    {
        if (*name != 0x91)
        {
            if (*name != 0)
            {
                return 0;
            }
        }
        n++;
        name += 2;
    } while (n < 10);
    return 1;
}

void NameEntryNop_800B8018(void* name)
{
}

// on a move off an edge (k = direction 1..4) of a wrapping area, jump to the opposite edge
void WrapGridCursor_800B8020(GridCursor* cursor, int dir)
{
    if (cursor->flags_0 & cursorWrapMasks_800B83C8[dir - 1])
    {
        if ((cursor->flags_0 & 1) && (unsigned)(dir - 1) < 2)
        {
            cursor->pos_6 += cursorWrapDirs_800B83D0[dir - 1] * (cursor->cols_8 - 1);
        }
        else if ((cursor->flags_0 & 2) && (unsigned)(dir - 3) < 2)
        {
            cursor->pos_6 += cursorWrapDirs_800B83D0[dir - 1] * cursor->cols_8 * (cursor->rows_A - 1);
        }
    }
}

int MoveCursorWithSfx_800B80E4(GridCursor* cursor)
{
    int prevPos = (short)cursor->pos_6;
    int dir = MoveGridCursorP1_8003D630(cursor);
    if (dir)
    {
        WrapGridCursor_800B8020(cursor, dir);
        if (cursor->flags_0 & cursorExitTbl_800B83D8[dir - 1].mask)
        {
            PlaySfx_80031494(0x7F);
            return cursorExitTbl_800B83D8[dir - 1].result;
        }
    }
    if (prevPos != (short)cursor->pos_6)
    {
        PlaySfx_80031494(0x7F);
    }
    return 0;
}
