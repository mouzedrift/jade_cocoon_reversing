// COMBSEL.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "combsel.h"

int dword_800A4088 SDATA = 19;
const char aReturnToTitleSc_800A408C[] = "\202q\202\205\202\224\202\225\202\222\202\216\201@\202\224\202\217\201@\202\224\202\211\202\224\202\214\202\205\201@\202\223\202\203\202\222\202\205\202\205\202\216\201D"; // Return to title screen.
const char aDeleteEnteredMi_800A40BC[] = "\202c\202\205\202\214\202\205\202\224\202\205\201@\202\205\202\216\202\224\202\205\202\222\202\205\202\204\201@\202\215\202\211\202\216\202\211\202\217\202\216\201D"; // Delete entered minion.
const char aEnterMinionFrom_800A40EC[] = "\202d\202\216\202\224\202\205\202\222\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\206\202\222\202\217\202\215\201@\202\214\202\211\202\223\202\224\201D"; // Enter minion from list.
const char aReadMinionDataF_800A411C[] = "\202q\202\205\202\201\202\204\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\204\202\201\202\224\202\201\201@\202\206\202\222\202\217\202\215\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201D"; // Read minion data from MEMORY CARD.
const char aReturnToTitleSc_800A4164[] = "\202q\202\205\202\224\202\225\202\222\202\216\201@\202\224\202\217\201@\202\224\202\211\202\224\202\214\202\205\201@\202\223\202\203\202\222\202\205\202\205\202\216\201H"; // Return to title screen?
const char aEnterPlayer2SMi_800A4194[] = "\202d\202\216\202\224\202\205\202\222\201@\202o\202\214\202\201\202\231\202\205\202\222\201@\202Q\201f\202\223\201@\202\215\202\211\202\216\202\211\202\217\202\216\202\223\201D"; // Enter Player 2's minions.
const char aStartFighting_800A41C8[] = "\202r\202\224\202\201\202\222\202\224\201@\202\206\202\211\202\207\202\210\202\224\202\211\202\216\202\207\201D"; // Start fighting.
const char aEnterPlayer2SMi_800A41E8[] = "\202d\202\216\202\224\202\205\202\222\201@\202o\202\214\202\201\202\231\202\205\202\222\201@\202Q\201f\202\223\201@\202l\202\211\202\216\202\211\202\217\202\216\202\223\201D"; // Enter Player 2's Minions.
const char aQuit_800A421C[] = "\202p\202\225\202\211\202\224"; // Quit
const char aSelect_800A4228[] = "\202r\202\205\202\214\202\205\202\203\202\224"; // Select
const CombSelItem titleItem_800A4238 = { 8, 1, 15, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x6A, 0x14, 0x6C, 0x12, 2, 2 };
const CombSelItem playerItems_800A4254[2] = {
    { 8, 1, 0, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xA, 0x14, 0x4D, 0x12, 2, 2 },
    { 16, 1, 1, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xA, 0x27, 0x90, 0x13, 2, 2 },
};
const CombSelItem listHeaderItem_800A428C = { 8, 1, 1, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x9B, 0x37, 0x32, 0x12, 2, 2 };
const char aSelectSpaceToEn_800A42A8[] = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202\223\202\220\202\201\202\203\202\205\201@\202\224\202\217\201@\202\205\202\216\202\224\202\205\202\222\201@\202\215\202\211\202\216\202\211\202\217\202\216\201D"; // Select space to enter minion.
const char aSelectMinionToD_800A42E4[] = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\224\202\217\201@\202\204\202\205\202\214\202\205\202\224\202\205\201D"; // Select minion to delete.
const char aSelectMinionToE_800A4318[] = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\224\202\217\201@\202\205\202\216\202\224\202\205\202\222\201D"; // Select minion to enter.
const int dword_800A4348 = 0;

void CombSelMain_800A4360(CombSelTask* t, int a)
{
    CombSelCursor* cursor = modeCursors_800A5984[byte_800A38DB];
    CombSelMenu* win = modeWindows_800A5994[byte_800A38DB];
    int i;
    int j;
    if (AllSlotsEmpty_800A5560(dword_800A3AA0[byte_800A38D9], 3) == 1)
    {
        deleteRow_800A5888[0].flags_0 |= 2;
        nextRow_800A58C0[0].flags_0 |= 2;
    }
    else
    {
        deleteRow_800A5888[0].flags_0 &= ~2;
        nextRow_800A58C0[0].flags_0 &= ~2;
    }
    if (AllSlotsEmpty_800A5560(dword_800A1BC8[byte_800A38D9], 6) == 1)
    {
        enterRow_800A5850[0].flags_0 |= 2;
    }
    else
    {
        enterRow_800A5850[0].flags_0 &= ~2;
    }
    if (byte_800A38D9 == 0)
    {
        dword_800A3A94 = 0;
    }
    else
    {
        dword_800A3A94 = byte_800A38D8;
    }
    nextRow_800A58C0[0].icon_4 = nextIcons_800A59AC[byte_800A38D9];
    listCursor_800A596C.rows_2 = 6;
    listCursor_800A596C.count_4 = 15;
    PlaceSideWindows_800A4C74();
    switch (byte_800A38DB)
    {
    case 0:
        mainWindow_800A5948.flags_0 = 2;
        teamWindow_800A567C.flags_0 = 1;
        listWindow_800A5800.flags_0 = 1;
        break;
    case 1:
        mainWindow_800A5948.flags_0 = 4;
        teamWindow_800A567C.flags_0 = 2;
        switch (word_800A1BC4)
        {
        case 1:
            listWindow_800A5800.flags_0 = 4;
            break;
        case 2:
            listWindow_800A5800.flags_0 = 1;
            break;
        }
        break;
    case 2:
        mainWindow_800A5948.flags_0 = 4;
        teamWindow_800A567C.flags_0 = 1;
        listWindow_800A5800.flags_0 = 2;
        break;
    }
    for (i = 0; i < 3; i++)
    {
        unsigned short pt[2];
        pt[0] = teamRows_800A566C[i]->x_10;
        pt[1] = teamRows_800A566C[i]->y_12;
        sub_800A1844(&dword_800A3AA0[byte_800A38D9][i + teamCursor_800A5960.scroll_A], pt, 0);
    }
    for (j = 0; j < 6; j++)
    {
        unsigned short pt[2];
        pt[0] = listRows_800A57E4[j]->x_10;
        pt[1] = listRows_800A57E4[j]->y_12;
        sub_800A1844(&dword_800A1BC8[byte_800A38D9][j + listCursor_800A596C.scroll_A], pt, 0);
    }
    {
        CombSelBox col;
        RECT r;
        short xs[2];
        unsigned short pos[2];
        xs[0] = 0x100;
        xs[1] = 0x15;
        col.state_2 = 0;
        col.frame_3 = 1;
        col.color_0 = saveData_8008B570.uiColor_20.h;
        r.x = xs[byte_800A38D9];
        r.y = 0x3B;
        r.w = 0x2F;
        r.h = 0xE;
        pos[0] = r.x + 0x13;
        pos[1] = 0x3E;
        DrawSmallNumber3_8002C290(pos, (short)GetMenuCursorIndex_8003DA54(&listCursor_800A596C) + 1, 10);
        pos[0] += 1;
        DrawUiTiySprt_8002C06C(pos, 0xDA, 10);
        pos[0] += 0x16;
        DrawSmallNumber3_8002C290(pos, 15, 10);
        DrawWindow_80042460(&r, &col, pOT_8008D454 + 15, 0);
    }
    {
        CombSelItem item;
        CombSelBox col;
        item = titleItem_800A4238;
        col.state_2 = 0;
        col.frame_3 = 1;
        col.color_0 = saveData_8008B570.uiColor_20.h;
        DrawMenuItemWithWindow_8002ADB4(&item, &col, 10, 0);
    }
    {
        CombSelBox col;
        CombSelItem item = playerItems_800A4254[0];
        short xs[2] = { 0xA, 0xE9 };
        CombSelItem unused; // never used (it keeps the original frame layout)
        item.x_10 = xs[byte_800A38D9];
        item.icon_4 = playerIcons_800A59A4[byte_800A38D9];
        col.state_2 = 0;
        col.frame_3 = 1;
        col.color_0 = saveData_8008B570.uiColor_20.h;
        DrawMenuItemWithWindow_8002ADB4(&item, &col, 10, 0);
        if (byte_800A38DB == 2)
        {
            CombSelArrow arrow;
            short pos[4];
            short xs[2];
            xs[0] = 0x132;
            xs[1] = 0xF;
            arrow.kind_0 = 1;
            arrow.dir_2 = 1;
            pos[0] = xs[byte_800A38D9];
            pos[1] = 0x52;
            pos[2] = xs[byte_800A38D9];
            pos[3] = 0xB8;
            DrawScrollArrows_8002B8DC(arrow, &listCursor_800A596C, pos, 10);
        }
        {
            CombSelItem item = listHeaderItem_800A428C;
            CombSelBox col;
            short xs[2] = { 0x9B, 0x73 };
            item.x_10 = xs[byte_800A38D9];
            col.state_2 = 0;
            col.frame_3 = 1;
            col.color_0 = saveData_8008B570.uiColor_20.h;
            DrawMenuItemWithWindow_8002ADB4(&item, &col, 10, 0);
        }
        switch (byte_800A38DB)
        {
        case 0:
            if (byte_800A38D9 == 0)
            {
                mainMenuHelp_800A59C4[3] = nextTextP1_800A59DC[0];
            }
            else
            {
                mainMenuHelp_800A59C4[3] = nextTextP2_800A59E0[0];
            }
            DrawSmallTextBox_8002AF58((int)&mainMenuHelp_800A59C4[word_800A1BC4], 0, 15);
            break;
        case 1:
        {
            const char* s = 0;
            switch (word_800A1BC4)
            {
            case 1:
                s = aSelectSpaceToEn_800A42A8;
                break;
            case 2:
                s = aSelectMinionToD_800A42E4;
                break;
            }
            DrawSmallTextBox_8002AF58((int)&s, 0, 15);
            break;
        }
        case 2:
        {
            const char* s = aSelectMinionToE_800A4318;
            DrawSmallTextBox_8002AF58((int)&s, 0, 15);
            break;
        }
        case 3:
            DrawSmallTextBox_8002AF58((int)quitPrompt_800A59D8, 0, 15);
            break;
        }
        win->time_4 = GetTime30Hz_8002C64C();
        mainWindow_800A5948.cursor_C = dword_800A1BBC.index_8;
        listWindow_800A5800.cursor_C = listCursor_800A596C.index_8;
        teamWindow_800A567C.cursor_C = teamCursor_800A5960.index_8;
        DrawMenuWindows_8002A5A4(&mainWindow_800A5948);
        DrawMenuWindows_8002A5A4(&teamWindow_800A567C);
        DrawMenuWindows_8002A5A4(&listWindow_800A5800);
        if (byte_800A38D9 == 0)
        {
            DrawButtonHelpBar_8002B004(buttonHelpP1_800A59E4, 0, 15);
        }
        else
        {
            DrawButtonHelpBar_8002B004(buttonHelpP2_800A5A04, 0, 15);
        }
        if (byte_800A38DB == 3)
        {
            dword_80082784.flags_0 = 10;
            dword_80082784.time_4 = GetTime30Hz_8002C64C();
            dword_80082784.anim_8 = 8;
            dword_80082784.ot_14 = 0;
            dword_80082784.cursor_C = quitCursor_800A5978.index_8;
            dword_80082708[0].flags_0 = 8;
            dword_80082740[0].flags_0 = 8;
            dword_80082708[0].x_10 = 0xC8;
            dword_80082708[0].y_12 = 0xC3;
            dword_80082740[0].x_10 = 0xF6;
            dword_80082740[0].y_12 = 0xC3;
            DrawMenuWindows_8002A5A4(&dword_80082784);
        }
        DrawMenuBackground_8002BE10();
        UpdateMenuCursor_8003D794(cursor, dword_800A3A94);
        if (padPressed_8009194C[dword_800A3A94] & 0x80)
        {
            NextOrFight_800A5080(t, a);
        }
        else
        {
            modeHandlers_800A59B4[byte_800A38DB](t, a);
        }
    }
}

void PlaceSideWindows_800A4C74()
{
    short v[2];
    int i;
    for (i = 0; i < 3; i++)
    {
        v[0] = 0xA;
        v[1] = 0xA6;
        teamRows_800A566C[i]->x_10 = v[*(volatile unsigned char*)&byte_800A38D9];
    }
    for (i = 0; i < 6; i++)
    {
        v[0] = 0x9B;
        v[1] = 0x15;
        listRows_800A57E4[i]->x_10 = v[*(volatile unsigned char*)&byte_800A38D9];
    }
    for (i = 0; i < 5; i++)
    {
        v[0] = 0xA;
        v[1] = 0xCA;
        mainRows_800A5930[i]->x_10 = v[*(volatile unsigned char*)&byte_800A38D9];
    }
}

void CompactTeam_800A4D64(Minion* base)
{
    int i;
    int j;
    for (i = 0; i < 2; i++)
    {
        if (sub_800A1934(&base[i]) == 1)
        {
            for (j = i + 1; j < 3; j++)
            {
                if (sub_800A1934(&base[j]) == 0)
                {
                    MemCopy_800403E8(&base[i], &base[j], 0xF8);
                    sub_800A197C(&base[j]);
                    break;
                }
            }
            if (j >= 3)
            {
                return;
            }
        }
    }
}

void CompactTeams_800A4E4C()
{
    int i;
    for (i = 0; i < 2; i++)
    {
        CompactTeam_800A4D64(dword_800A3AA0[i]);
    }
}


void MainMenuInput_800A4E94(CombSelTask* t, int a)
{
    if (IsConfirmPressed_8003D288(0, dword_800A3A94))
    {
        switch (word_800A1BC4)
        {
        case 0:
            PlaySfx_80031494(0x7E);
            t->next_8 = sub_800A16FC;
            t->next_8(t, a);
            break;
        case 1:
            if (AllSlotsEmpty_800A5560(dword_800A1BC8[byte_800A38D9], 6) == 1)
            {
                PlaySfx_80031494(0x7C);
            }
            else
            {
                PlaySfx_80031494(0x7E);
                byte_800A38DB = 2;
            }
            break;
        case 2:
            if (AllSlotsEmpty_800A5560(dword_800A3AA0[byte_800A38D9], 3) == 1)
            {
                PlaySfx_80031494(0x7C);
            }
            else
            {
                PlaySfx_80031494(0x7E);
                byte_800A38DB = 1;
            }
            break;
        case 3:
            NextOrFight_800A5080(t, a);
            break;
        case 4:
            PlaySfx_80031494(0x7E);
            byte_800A38DB = 3;
            quitCursor_800A5978.index_8 = 1;
            break;
        }
    }
    else if (IsCancelPressed_8003D3C0(1, dword_800A3A94))
    {
        switch (byte_800A38D9)
        {
        case 0:
            word_800A1BC4 = 4;
            break;
        case 1:
            word_800A1BC4 = 1;
            teamCursor_800A5960.index_8 = 0;
            byte_800A38D9 = 0;
            listCursor_800A596C.index_8 = 0;
            break;
        }
    }
}

// Near miss: store order of the case 0 assignments
#if 0
void NextOrFight_800A5080(CombSelTask* t, int a)
{
    if (AllSlotsEmpty_800A5560(dword_800A3AA0[byte_800A38D9], 3) == 1)
    {
        PlaySfx_80031494(0x7C);
    }
    else
    {
        byte_800A38DB = 0;
        dword_800A1BBC.index_8 = 3;
        PlaySfx_80031494(0x7E);
        switch (byte_800A38D9)
        {
        case 0:
            dword_800A1BBC.index_8 = 0;
            teamCursor_800A5960.index_8 = 0;
            byte_800A38D9 = 1;
            listCursor_800A596C.index_8 = 0;
            break;
        case 1:
            CompactTeams_800A4E4C();
            t->next_8 = sub_800A16FC;
            t->next_8(t, a);
            break;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(combsel, NextOrFight_800A5080);


void TeamSlotInput_800A5188()
{
    if (IsConfirmPressed_8003D288(0, dword_800A3A94))
    {
        switch (word_800A1BC4)
        {
        case 1:
        {
            Minion* a = &dword_800A3AA0[byte_800A38D9][(short)GetMenuCursorIndex_8003DA54(&teamCursor_800A5960)];
            Minion* b = &dword_800A1BC8[byte_800A38D9][(short)GetMenuCursorIndex_8003DA54(&listCursor_800A596C)];
            MemCopy_800403E8(a, b, 0xF8);
            byte_800A38DB = 2;
            PlaySfx_80031494(0x7E);
            break;
        }
        case 2:
            if (sub_800A1934(&dword_800A3AA0[byte_800A38D9][(short)GetMenuCursorIndex_8003DA54(&teamCursor_800A5960)]) == 1)
            {
                PlaySfx_80031494(0x7C);
            }
            else
            {
                PlaySfx_80031494(0x7E);
                sub_800A197C(&dword_800A3AA0[byte_800A38D9][(short)GetMenuCursorIndex_8003DA54(&teamCursor_800A5960)]);
                byte_800A38DB = 0;
            }
            break;
        }
    }
    else if (IsCancelPressed_8003D3C0(1, dword_800A3A94))
    {
        switch (word_800A1BC4)
        {
        case 1:
            byte_800A38DB = 2;
            break;
        case 2:
            byte_800A38DB = 0;
            break;
        }
    }
}

void ListInput_800A53B0()
{
    short s;
    if (IsConfirmPressed_8003D288(0, dword_800A3A94))
    {
        s = word_800A1BC4;
        if (s == 1)
        {
            short r = GetMenuCursorIndex_8003DA54(&listCursor_800A596C);
            if (sub_800A1934(&dword_800A1BC8[byte_800A38D9][r]) == 1)
            {
                PlaySfx_80031494(0x7C);
            }
            else
            {
                byte_800A38DB = 1;
                PlaySfx_80031494(0x7E);
            }
        }
    }
    else if (IsCancelPressed_8003D3C0(1, dword_800A3A94))
    {
        byte_800A38DB = 0;
        if (sub_800A1AAC(byte_800A38D9))
        {
            word_800A1BC4 = 3;
        }
    }
}

void QuitConfirmInput_800A54A0(CombSelTask* t)
{
    if (IsConfirmPressed_8003D288(0, dword_800A3A94))
    {
        PlaySfx_80031494(0x7E);
        if ((short)GetMenuCursorIndex_8003DA54(&quitCursor_800A5978) == 0)
        {
            XaRequestPlay_80043564(1, 0x678, 0x1F);
            t->next_8 = QuitToTitle_800A5538;
        }
        else
        {
            byte_800A38DB = 0;
        }
    }
    else if (IsCancelPressed_8003D3C0(1, dword_800A3A94))
    {
        byte_800A38DB = 0;
    }
}

void QuitToTitle_800A5538(CombSelTask* t)
{
    t->next_8 = sub_800A16FC;
    t->next_8(t);
}

int AllSlotsEmpty_800A5560(Minion* p, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (sub_800A1934(p + i) == 0)
        {
            return 0;
        }
    }
    return 1;
}

CombSelItem teamRow0_800A55C4[2] = {
    { 0, 0, 0, 0, 0, 10, 39, 144, 19, 2, 4 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
CombSelItem teamRow1_800A55FC[2] = {
    { 0, 0, 0, 0, 0, 10, 59, 144, 19, 2, 4 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
CombSelItem teamRow2_800A5634[2] = {
    { 0, 0, 0, 0, 0, 10, 79, 144, 19, 2, 4 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
CombSelItem *teamRows_800A566C[4] = { teamRow0_800A55C4, teamRow1_800A55FC, teamRow2_800A5634, 0 };
CombSelMenu teamWindow_800A567C = { 2, 0, 8, 0, teamRows_800A566C, 0 };
CombSelItem listRow0_800A5694[2] = {
    { 0, 0, 0, 0, 0, 155, 74, 144, 19, 2, 4 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
CombSelItem listRow1_800A56CC[2] = {
    { 0, 0, 0, 0, 0, 155, 94, 144, 19, 2, 4 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
CombSelItem listRow2_800A5704[2] = {
    { 0, 0, 0, 0, 0, 155, 114, 144, 19, 2, 4 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
CombSelItem listRow3_800A573C[2] = {
    { 0, 0, 0, 0, 0, 155, 134, 144, 19, 2, 4 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
CombSelItem listRow4_800A5774[2] = {
    { 0, 0, 0, 0, 0, 155, 154, 144, 19, 2, 4 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
CombSelItem listRow5_800A57AC[2] = {
    { 0, 0, 0, 0, 0, 155, 174, 144, 19, 2, 4 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
CombSelItem *listRows_800A57E4[7] = { listRow0_800A5694, listRow1_800A56CC, listRow2_800A5704, listRow3_800A573C, listRow4_800A5774, listRow5_800A57AC, 0 };
CombSelMenu listWindow_800A5800 = { 2, 0, 8, 0, listRows_800A57E4, 0 };
CombSelItem loadRow_800A5818[2] = {
    { 8, 1, 155, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 10, 99, 108, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
CombSelItem enterRow_800A5850[2] = {
    { 8, 1, 29, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 10, 118, 108, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
CombSelItem deleteRow_800A5888[2] = {
    { 8, 1, 27, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 10, 137, 108, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
CombSelItem nextRow_800A58C0[2] = {
    { 8, 1, 0, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 10, 156, 108, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
CombSelItem quitRow_800A58F8[2] = {
    { 8, 1, 28, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 10, 175, 108, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
CombSelItem *mainRows_800A5930[6] = { loadRow_800A5818, enterRow_800A5850, deleteRow_800A5888, nextRow_800A58C0, quitRow_800A58F8, 0 };
CombSelMenu mainWindow_800A5948 = { 2, 0, 8, 0, mainRows_800A5930, 0 };
CombSelCursor teamCursor_800A5960 = { 1, 3, 3, 0x40, 0, 0 };
CombSelCursor listCursor_800A596C = { 1, 6, 15, 0x40, 0, 0 };
CombSelCursor quitCursor_800A5978 = { 2, 1, 2, 0, 1, 0 };
CombSelCursor *modeCursors_800A5984[4] = { &dword_800A1BBC, &teamCursor_800A5960, &listCursor_800A596C, &quitCursor_800A5978 };
CombSelMenu *modeWindows_800A5994[4] = { &mainWindow_800A5948, &teamWindow_800A567C, &listWindow_800A5800, &dword_80082784 };
int playerIcons_800A59A4[2] = { 55, 56 };
int nextIcons_800A59AC[2] = { 56, 36 };
void (*modeHandlers_800A59B4[4])() = { MainMenuInput_800A4E94, TeamSlotInput_800A5188, ListInput_800A53B0, QuitConfirmInput_800A54A0 };
const char *mainMenuHelp_800A59C4[5] = { aReadMinionDataF_800A411C, aEnterMinionFrom_800A40EC, aDeleteEnteredMi_800A40BC, 0, aReturnToTitleSc_800A408C };
const char *quitPrompt_800A59D8[1] = { aReturnToTitleSc_800A4164 };
const char *nextTextP1_800A59DC[1] = { aEnterPlayer2SMi_800A4194 };
const char *nextTextP2_800A59E0[1] = { aStartFighting_800A41C8 };
CombSelHelp buttonHelpP1_800A59E4[4] = { { 16, aSelect_800A4228 }, { 167, aQuit_800A421C }, { 94, aEnterPlayer2SMi_800A41E8 }, { -1 } };
CombSelHelp buttonHelpP2_800A5A04[4] = { { 16, aSelect_800A4228 }, { 167, aQuit_800A421C }, { 94, aStartFighting_800A41C8 }, { -1 } };
