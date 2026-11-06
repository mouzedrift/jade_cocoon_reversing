// COMBSEL.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "combsel.h"

int unused_800A4088 SDATA = 19; // first word of the overlay

MenuWindowItem teamRow0_800A55C4[2] = {
    { 0, 0, 0, 0, 0, 10, 39, 144, 19, 2, 4 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem teamRow1_800A55FC[2] = {
    { 0, 0, 0, 0, 0, 10, 59, 144, 19, 2, 4 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem teamRow2_800A5634[2] = {
    { 0, 0, 0, 0, 0, 10, 79, 144, 19, 2, 4 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem *teamRows_800A566C[4] = { teamRow0_800A55C4, teamRow1_800A55FC, teamRow2_800A5634, 0 };
MenuWindowList teamWindow_800A567C = { 2, 0, 8, 0, teamRows_800A566C, 0 };
MenuWindowItem listRow0_800A5694[2] = {
    { 0, 0, 0, 0, 0, 155, 74, 144, 19, 2, 4 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem listRow1_800A56CC[2] = {
    { 0, 0, 0, 0, 0, 155, 94, 144, 19, 2, 4 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem listRow2_800A5704[2] = {
    { 0, 0, 0, 0, 0, 155, 114, 144, 19, 2, 4 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem listRow3_800A573C[2] = {
    { 0, 0, 0, 0, 0, 155, 134, 144, 19, 2, 4 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem listRow4_800A5774[2] = {
    { 0, 0, 0, 0, 0, 155, 154, 144, 19, 2, 4 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem listRow5_800A57AC[2] = {
    { 0, 0, 0, 0, 0, 155, 174, 144, 19, 2, 4 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem *listRows_800A57E4[7] = { listRow0_800A5694, listRow1_800A56CC, listRow2_800A5704, listRow3_800A573C, listRow4_800A5774, listRow5_800A57AC, 0 };
MenuWindowList listWindow_800A5800 = { 2, 0, 8, 0, listRows_800A57E4, 0 };
MenuWindowItem loadRow_800A5818[2] = {
    { 8, 1, 155, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 10, 99, 108, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem enterRow_800A5850[2] = {
    { 8, 1, 29, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 10, 118, 108, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem deleteRow_800A5888[2] = {
    { 8, 1, 27, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 10, 137, 108, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem nextRow_800A58C0[2] = {
    { 8, 1, 0, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 10, 156, 108, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem quitRow_800A58F8[2] = {
    { 8, 1, 28, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 10, 175, 108, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem *mainRows_800A5930[6] = { loadRow_800A5818, enterRow_800A5850, deleteRow_800A5888, nextRow_800A58C0, quitRow_800A58F8, 0 };
MenuWindowList mainWindow_800A5948 = { 2, 0, 8, 0, mainRows_800A5930, 0 };
MenuCursor teamCursor_800A5960 = { 1, 3, 3, 0x40, 0, 0 };
MenuCursor listCursor_800A596C = { 1, 6, 15, 0x40, 0, 0 };
MenuCursor quitCursor_800A5978 = { 2, 1, 2, 0, 1, 0 };
MenuCursor *modeCursors_800A5984[4] = { &combatCursor_800A1BBC, &teamCursor_800A5960, &listCursor_800A596C, &quitCursor_800A5978 };
MenuWindowList *modeWindows_800A5994[4] = { &mainWindow_800A5948, &teamWindow_800A567C, &listWindow_800A5800, &yesNoWindow_80082784 };
int playerIcons_800A59A4[2] = { 55, 56 };
int nextIcons_800A59AC[2] = { 56, 36 };
void (*modeHandlers_800A59B4[4])() = { MainMenuInput_800A4E94, TeamSlotInput_800A5188, ListInput_800A53B0, QuitConfirmInput_800A54A0 };
const char *mainMenuHelp_800A59C4[5] = { "\202q\202\205\202\201\202\204\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\204\202\201\202\224\202\201\201@\202\206\202\222\202\217\202\215\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201D", "\202d\202\216\202\224\202\205\202\222\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\206\202\222\202\217\202\215\201@\202\214\202\211\202\223\202\224\201D", "\202c\202\205\202\214\202\205\202\224\202\205\201@\202\205\202\216\202\224\202\205\202\222\202\205\202\204\201@\202\215\202\211\202\216\202\211\202\217\202\216\201D", 0, "\202q\202\205\202\224\202\225\202\222\202\216\201@\202\224\202\217\201@\202\224\202\211\202\224\202\214\202\205\201@\202\223\202\203\202\222\202\205\202\205\202\216\201D" }; // Read minion data from MEMORY CARD. / Enter minion from list. / Delete entered minion. / Return to title screen.
const char *quitPrompt_800A59D8[1] = { "\202q\202\205\202\224\202\225\202\222\202\216\201@\202\224\202\217\201@\202\224\202\211\202\224\202\214\202\205\201@\202\223\202\203\202\222\202\205\202\205\202\216\201H" }; // Return to title screen?
const char *nextTextP1_800A59DC[1] = { "\202d\202\216\202\224\202\205\202\222\201@\202o\202\214\202\201\202\231\202\205\202\222\201@\202Q\201f\202\223\201@\202\215\202\211\202\216\202\211\202\217\202\216\202\223\201D" }; // Enter Player 2's minions.
const char *nextTextP2_800A59E0[1] = { "\202r\202\224\202\201\202\222\202\224\201@\202\206\202\211\202\207\202\210\202\224\202\211\202\216\202\207\201D" }; // Start fighting.
ButtonHelpEntry buttonHelpP1_800A59E4[4] = { { 16, "\202r\202\205\202\214\202\205\202\203\202\224" }, { 167, "\202p\202\225\202\211\202\224" }, { 94, "\202d\202\216\202\224\202\205\202\222\201@\202o\202\214\202\201\202\231\202\205\202\222\201@\202Q\201f\202\223\201@\202l\202\211\202\216\202\211\202\217\202\216\202\223\201D" }, { -1 } }; // Select / Quit / Enter Player 2's Minions.
ButtonHelpEntry buttonHelpP2_800A5A04[4] = { { 16, "\202r\202\205\202\214\202\205\202\203\202\224" }, { 167, "\202p\202\225\202\211\202\224" }, { 94, "\202r\202\224\202\201\202\222\202\224\201@\202\206\202\211\202\207\202\210\202\224\202\211\202\216\202\207\201D" }, { -1 } }; // Select / Quit / Start fighting.

const MenuWindowItem titleItem_800A4238 = { 8, 1, 15, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x6A, 0x14, 0x6C, 0x12, 2, 2 };
const MenuWindowItem playerItems_800A4254[2] = {
    { 8, 1, 0, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xA, 0x14, 0x4D, 0x12, 2, 2 },
    { 16, 1, 1, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xA, 0x27, 0x90, 0x13, 2, 2 },
};
const MenuWindowItem listHeaderItem_800A428C = { 8, 1, 1, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x9B, 0x37, 0x32, 0x12, 2, 2 };

void CombSelMain_800A4360(CombSelTask* t, int a)
{
    MenuCursor* cursor = modeCursors_800A5984[selMode_800A38DB];
    MenuWindowList* win = modeWindows_800A5994[selMode_800A38DB];
    int i;
    int j;
    if (AllSlotsEmpty_800A5560(teams_800A3AA0[curPlayer_800A38D9], 3) == 1)
    {
        deleteRow_800A5888[0].flags_0 |= 2;
        nextRow_800A58C0[0].flags_0 |= 2;
    }
    else
    {
        deleteRow_800A5888[0].flags_0 &= ~2;
        nextRow_800A58C0[0].flags_0 &= ~2;
    }
    if (AllSlotsEmpty_800A5560(rosters_800A1BC8[curPlayer_800A38D9], 6) == 1)
    {
        enterRow_800A5850[0].flags_0 |= 2;
    }
    else
    {
        enterRow_800A5850[0].flags_0 &= ~2;
    }
    if (curPlayer_800A38D9 == 0)
    {
        curPad_800A3A94 = 0;
    }
    else
    {
        curPad_800A3A94 = player2Pad_800A38D8;
    }
    nextRow_800A58C0[0].text_4 = nextIcons_800A59AC[curPlayer_800A38D9];
    listCursor_800A596C.rows_2 = 6;
    listCursor_800A596C.count_4 = 15;
    PlaceSideWindows_800A4C74();
    switch (selMode_800A38DB)
    {
    case 0:
        mainWindow_800A5948.flags_0 = 2;
        teamWindow_800A567C.flags_0 = 1;
        listWindow_800A5800.flags_0 = 1;
        break;
    case 1:
        mainWindow_800A5948.flags_0 = 4;
        teamWindow_800A567C.flags_0 = 2;
        switch (combatMenuChoice_800A1BC4)
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
        DrawMinionNameLevel_800A1844(&teams_800A3AA0[curPlayer_800A38D9][i + teamCursor_800A5960.scroll_A], pt, 0);
    }
    for (j = 0; j < 6; j++)
    {
        unsigned short pt[2];
        pt[0] = listRows_800A57E4[j]->x_10;
        pt[1] = listRows_800A57E4[j]->y_12;
        DrawMinionNameLevel_800A1844(&rosters_800A1BC8[curPlayer_800A38D9][j + listCursor_800A596C.scroll_A], pt, 0);
    }
    {
        WindowStyle col;
        RECT rect;
        short xs[2];
        unsigned short pos[2];
        xs[0] = 0x100;
        xs[1] = 0x15;
        col.colorSet_2 = 0;
        col.semiTrans_3 = 1;
        col.color_0 = saveData_8008B570.uiColor_20.h;
        rect.x = xs[curPlayer_800A38D9];
        rect.y = 0x3B;
        rect.w = 0x2F;
        rect.h = 0xE;
        pos[0] = rect.x + 0x13;
        pos[1] = 0x3E;
        DrawSmallNumber3_8002C290(pos, (short)GetMenuCursorIndex_8003DA54(&listCursor_800A596C) + 1, 10);
        pos[0] += 1;
        DrawUiTiySprt_8002C06C(pos, 0xDA, 10);
        pos[0] += 0x16;
        DrawSmallNumber3_8002C290(pos, 15, 10);
        DrawWindow_80042460(&rect, &col, pOT_8008D454 + 15, 0);
    }
    {
        MenuWindowItem item;
        WindowStyle col;
        item = titleItem_800A4238;
        col.colorSet_2 = 0;
        col.semiTrans_3 = 1;
        col.color_0 = saveData_8008B570.uiColor_20.h;
        DrawMenuItemWithWindow_8002ADB4(&item, &col, 10, 0);
    }
    {
        WindowStyle col;
        MenuWindowItem item = playerItems_800A4254[0];
        short xs[2] = { 0xA, 0xE9 };
        MenuWindowItem unused; // never used (it keeps the original frame layout)
        item.x_10 = xs[curPlayer_800A38D9];
        item.text_4 = playerIcons_800A59A4[curPlayer_800A38D9];
        col.colorSet_2 = 0;
        col.semiTrans_3 = 1;
        col.color_0 = saveData_8008B570.uiColor_20.h;
        DrawMenuItemWithWindow_8002ADB4(&item, &col, 10, 0);
        if (selMode_800A38DB == 2)
        {
            CombSelArrow arrow;
            short pos[4];
            short xs[2];
            xs[0] = 0x132;
            xs[1] = 0xF;
            arrow.kind_0 = 1;
            arrow.dir_2 = 1;
            pos[0] = xs[curPlayer_800A38D9];
            pos[1] = 0x52;
            pos[2] = xs[curPlayer_800A38D9];
            pos[3] = 0xB8;
            DrawScrollArrows_8002B8DC(arrow, &listCursor_800A596C, pos, 10);
        }
        {
            MenuWindowItem item = listHeaderItem_800A428C;
            WindowStyle col;
            short xs[2] = { 0x9B, 0x73 };
            item.x_10 = xs[curPlayer_800A38D9];
            col.colorSet_2 = 0;
            col.semiTrans_3 = 1;
            col.color_0 = saveData_8008B570.uiColor_20.h;
            DrawMenuItemWithWindow_8002ADB4(&item, &col, 10, 0);
        }
        switch (selMode_800A38DB)
        {
        case 0:
            if (curPlayer_800A38D9 == 0)
            {
                mainMenuHelp_800A59C4[3] = nextTextP1_800A59DC[0];
            }
            else
            {
                mainMenuHelp_800A59C4[3] = nextTextP2_800A59E0[0];
            }
            DrawSmallTextBox_8002AF58(&mainMenuHelp_800A59C4[combatMenuChoice_800A1BC4], 0, 15);
            break;
        case 1:
        {
            const char* prompt = 0;
            switch (combatMenuChoice_800A1BC4)
            {
            case 1:
                prompt = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202\223\202\220\202\201\202\203\202\205\201@\202\224\202\217\201@\202\205\202\216\202\224\202\205\202\222\201@\202\215\202\211\202\216\202\211\202\217\202\216\201D"; // Select space to enter minion.
                break;
            case 2:
                prompt = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\224\202\217\201@\202\204\202\205\202\214\202\205\202\224\202\205\201D"; // Select minion to delete.
                break;
            }
            DrawSmallTextBox_8002AF58(&prompt, 0, 15);
            break;
        }
        case 2:
        {
            const char* prompt = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\224\202\217\201@\202\205\202\216\202\224\202\205\202\222\201D"; // Select minion to enter.
            DrawSmallTextBox_8002AF58(&prompt, 0, 15);
            break;
        }
        case 3:
            DrawSmallTextBox_8002AF58(quitPrompt_800A59D8, 0, 15);
            break;
        }
        win->time_4 = GetTime30Hz_8002C64C();
        mainWindow_800A5948.cursor_C = combatCursor_800A1BBC.cursor_8;
        listWindow_800A5800.cursor_C = listCursor_800A596C.cursor_8;
        teamWindow_800A567C.cursor_C = teamCursor_800A5960.cursor_8;
        DrawMenuWindows_8002A5A4(&mainWindow_800A5948);
        DrawMenuWindows_8002A5A4(&teamWindow_800A567C);
        DrawMenuWindows_8002A5A4(&listWindow_800A5800);
        if (curPlayer_800A38D9 == 0)
        {
            DrawButtonHelpBar_8002B004(buttonHelpP1_800A59E4, 0, 15);
        }
        else
        {
            DrawButtonHelpBar_8002B004(buttonHelpP2_800A5A04, 0, 15);
        }
        if (selMode_800A38DB == 3)
        {
            yesNoWindow_80082784.flags_0 = 10;
            yesNoWindow_80082784.time_4 = GetTime30Hz_8002C64C();
            yesNoWindow_80082784.open_8 = 8;
            yesNoWindow_80082784.ot_14 = 0;
            yesNoWindow_80082784.cursor_C = quitCursor_800A5978.cursor_8;
            yesNoItemYes_80082708[0].flags_0 = 8;
            yesNoItemNo_80082740[0].flags_0 = 8;
            yesNoItemYes_80082708[0].x_10 = 0xC8;
            yesNoItemYes_80082708[0].y_12 = 0xC3;
            yesNoItemNo_80082740[0].x_10 = 0xF6;
            yesNoItemNo_80082740[0].y_12 = 0xC3;
            DrawMenuWindows_8002A5A4(&yesNoWindow_80082784);
        }
        DrawMenuBackground_8002BE10();
        UpdateMenuCursor_8003D794(cursor, curPad_800A3A94);
        if (padPressed_8009194C[curPad_800A3A94] & 0x80)
        {
            NextOrFight_800A5080(t, a);
        }
        else
        {
            modeHandlers_800A59B4[selMode_800A38DB](t, a);
        }
    }
}

const int unused_800A4348 = 0; // (.rdata after CombSelMain_800A4360's strings)

void PlaceSideWindows_800A4C74()
{
    short xs[2];
    int i;
    for (i = 0; i < 3; i++)
    {
        xs[0] = 0xA;
        xs[1] = 0xA6;
        teamRows_800A566C[i]->x_10 = xs[*(volatile unsigned char*)&curPlayer_800A38D9];
    }
    for (i = 0; i < 6; i++)
    {
        xs[0] = 0x9B;
        xs[1] = 0x15;
        listRows_800A57E4[i]->x_10 = xs[*(volatile unsigned char*)&curPlayer_800A38D9];
    }
    for (i = 0; i < 5; i++)
    {
        xs[0] = 0xA;
        xs[1] = 0xCA;
        mainRows_800A5930[i]->x_10 = xs[*(volatile unsigned char*)&curPlayer_800A38D9];
    }
}

void CompactTeam_800A4D64(Minion* team)
{
    int i;
    int j;
    for (i = 0; i < 2; i++)
    {
        if (IsMinionSlotEmpty_800A1934(&team[i]) == 1)
        {
            for (j = i + 1; j < 3; j++)
            {
                if (IsMinionSlotEmpty_800A1934(&team[j]) == 0)
                {
                    MemCopy_800403E8(&team[i], &team[j], 0xF8);
                    ClearMinionSlot_800A197C(&team[j]);
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
        CompactTeam_800A4D64(teams_800A3AA0[i]);
    }
}


void MainMenuInput_800A4E94(CombSelTask* t, int a)
{
    if (IsConfirmPressed_8003D288(0, curPad_800A3A94))
    {
        switch (combatMenuChoice_800A1BC4)
        {
        case 0:
            PlaySfx_80031494(0x7E);
            t->next_8 = CombatNextStage_800A16FC;
            t->next_8(t, a);
            break;
        case 1:
            if (AllSlotsEmpty_800A5560(rosters_800A1BC8[curPlayer_800A38D9], 6) == 1)
            {
                PlaySfx_80031494(0x7C);
            }
            else
            {
                PlaySfx_80031494(0x7E);
                selMode_800A38DB = 2;
            }
            break;
        case 2:
            if (AllSlotsEmpty_800A5560(teams_800A3AA0[curPlayer_800A38D9], 3) == 1)
            {
                PlaySfx_80031494(0x7C);
            }
            else
            {
                PlaySfx_80031494(0x7E);
                selMode_800A38DB = 1;
            }
            break;
        case 3:
            NextOrFight_800A5080(t, a);
            break;
        case 4:
            PlaySfx_80031494(0x7E);
            selMode_800A38DB = 3;
            quitCursor_800A5978.cursor_8 = 1;
            break;
        }
    }
    else if (IsCancelPressed_8003D3C0(1, curPad_800A3A94))
    {
        switch (curPlayer_800A38D9)
        {
        case 0:
            combatMenuChoice_800A1BC4 = 4;
            break;
        case 1:
            combatMenuChoice_800A1BC4 = 1;
            teamCursor_800A5960.cursor_8 = 0;
            curPlayer_800A38D9 = 0;
            listCursor_800A596C.cursor_8 = 0;
            break;
        }
    }
}

void NextOrFight_800A5080(CombSelTask* t, int a)
{
    if (AllSlotsEmpty_800A5560(teams_800A3AA0[curPlayer_800A38D9], 3) == 1)
    {
        PlaySfx_80031494(0x7C);
    }
    else
    {
        selMode_800A38DB = 0;
        combatCursor_800A1BBC.cursor_8 = 3;
        PlaySfx_80031494(0x7E);
        switch (curPlayer_800A38D9)
        {
        case 0:
            combatCursor_800A1BBC.cursor_8 = 0;
            teamCursor_800A5960.cursor_8 = 0;
            curPlayer_800A38D9 = 1;
            listCursor_800A596C.cursor_8 = 0;
            break;
        case 1:
            CompactTeams_800A4E4C();
            t->next_8 = CombatNextStage_800A16FC;
            t->next_8(t, a);
            break;
        }
    }
}


void TeamSlotInput_800A5188()
{
    if (IsConfirmPressed_8003D288(0, curPad_800A3A94))
    {
        switch (combatMenuChoice_800A1BC4)
        {
        case 1:
        {
            Minion* dst = &teams_800A3AA0[curPlayer_800A38D9][(short)GetMenuCursorIndex_8003DA54(&teamCursor_800A5960)];
            Minion* src = &rosters_800A1BC8[curPlayer_800A38D9][(short)GetMenuCursorIndex_8003DA54(&listCursor_800A596C)];
            MemCopy_800403E8(dst, src, 0xF8);
            selMode_800A38DB = 2;
            PlaySfx_80031494(0x7E);
            break;
        }
        case 2:
            if (IsMinionSlotEmpty_800A1934(&teams_800A3AA0[curPlayer_800A38D9][(short)GetMenuCursorIndex_8003DA54(&teamCursor_800A5960)]) == 1)
            {
                PlaySfx_80031494(0x7C);
            }
            else
            {
                PlaySfx_80031494(0x7E);
                ClearMinionSlot_800A197C(&teams_800A3AA0[curPlayer_800A38D9][(short)GetMenuCursorIndex_8003DA54(&teamCursor_800A5960)]);
                selMode_800A38DB = 0;
            }
            break;
        }
    }
    else if (IsCancelPressed_8003D3C0(1, curPad_800A3A94))
    {
        switch (combatMenuChoice_800A1BC4)
        {
        case 1:
            selMode_800A38DB = 2;
            break;
        case 2:
            selMode_800A38DB = 0;
            break;
        }
    }
}

void ListInput_800A53B0()
{
    short choice;
    if (IsConfirmPressed_8003D288(0, curPad_800A3A94))
    {
        choice = combatMenuChoice_800A1BC4;
        if (choice == 1)
        {
            short row = GetMenuCursorIndex_8003DA54(&listCursor_800A596C);
            if (IsMinionSlotEmpty_800A1934(&rosters_800A1BC8[curPlayer_800A38D9][row]) == 1)
            {
                PlaySfx_80031494(0x7C);
            }
            else
            {
                selMode_800A38DB = 1;
                PlaySfx_80031494(0x7E);
            }
        }
    }
    else if (IsCancelPressed_8003D3C0(1, curPad_800A3A94))
    {
        selMode_800A38DB = 0;
        if (CountTeamMinions_800A1AAC(curPlayer_800A38D9))
        {
            combatMenuChoice_800A1BC4 = 3;
        }
    }
}

void QuitConfirmInput_800A54A0(CombSelTask* t)
{
    if (IsConfirmPressed_8003D288(0, curPad_800A3A94))
    {
        PlaySfx_80031494(0x7E);
        if ((short)GetMenuCursorIndex_8003DA54(&quitCursor_800A5978) == 0)
        {
            XaRequestPlay_80043564(1, 0x678, 0x1F);
            t->next_8 = QuitToTitle_800A5538;
        }
        else
        {
            selMode_800A38DB = 0;
        }
    }
    else if (IsCancelPressed_8003D3C0(1, curPad_800A3A94))
    {
        selMode_800A38DB = 0;
    }
}

void QuitToTitle_800A5538(CombSelTask* t)
{
    t->next_8 = CombatNextStage_800A16FC;
    t->next_8(t);
}

int AllSlotsEmpty_800A5560(Minion* team, int count)
{
    int i;
    for (i = 0; i < count; i++)
    {
        if (IsMinionSlotEmpty_800A1934(team + i) == 0)
        {
            return 0;
        }
    }
    return 1;
}
