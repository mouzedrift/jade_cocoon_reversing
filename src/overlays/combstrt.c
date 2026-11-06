// COMBSTRT.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "pad_text.h"
#include "combstrt.h"

int dword_800A4088 SDATA = 21; // first word of the overlay

MenuCursor yesNoCursor_800A4BF0 = { 2, 1, 2, 0, 1, 0 };
unsigned short stateDefaultSel_800A4BFC[4] = { 1, 0, 0, 0 };
// the question of each setup state (state 3: the shuffle animation)
const char* stateQuestions_800A4C04[4] = {
    "\202`\202\214\202\214\202\217\202\227\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\203\202\210\202\201\202\216\202\207\202\211\202\216\202\207\201H", // Allow minion changing?
    "\202r\202\210\202\225\202\206\202\206\202\214\202\205\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\217\202\222\202\204\202\205\202\222\201H", // Shuffle minion order?
    "\202r\202\224\202\201\202\222\202\224\201@\202\206\202\211\202\207\202\210\202\224\201H", // Start fight?
    "\202r\202\210\202\225\202\206\202\206\202\214\202\211\202\216\202\207\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\217\202\222\202\204\202\205\202\222\201D\201D\201D", // Shuffling minion order...
};
unsigned char setupState_800A4C14 = 255;
MenuWindowItem playerLabelItemP1_800A4C18 = { 8, 1, 51, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 10, 20, 0x32, 0x14, 2, 4 };
MenuWindowItem playerLabelItemP2_800A4C34 = { 8, 1, 223, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 260, 20, 0x32, 0x14, 2, 4 };
MenuWindowItem* playerLabelItems_800A4C50[2] = { &playerLabelItemP1_800A4C18, &playerLabelItemP2_800A4C34 };
int slotLabelSprites_800A4C58[3] = { 219, 115, 102 };
short minionSlotPos_800A4C64[2][3][2] = { { { 10, 64 }, { 10, 109 }, { 10, 154 } }, { { 166, 64 }, { 166, 109 }, { 166, 154 } } };
void (*setupStateHandlers_800A4C7C[4])() = { SetupAllowChangeInput_800A43FC, SetupShuffleInput_800A4498, SetupStartFightInput_800A4524, SetupShuffleAnim_800A45B8 };
short windowAnimStep_800A4C8C = 0;
static short windowAnimPad = 0; // unused (0x800A4C8E)
short shuffleLimit_800A4C90 = 0;
short shufflePhase_800A4C92 = 0;
short shuffleTimer_800A4C94 = 0;
short shuffleDelay_800A4C96 = 0;

const MenuWindowItem titleItem_800A4138 = { 8, 1, 36, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x7A, 0x14, 0x4C, 0x14, 2, 4 };
const MenuWindowItem minionLabelItem_800A4154 = { 8, 1, 0, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0, 0, 0x32, 0x14, 2, 4 };

// Versus fight setup: yes/no questions (allow minion changing, shuffle order, start fight) and the shuffle animation
void VersusSetupTask_800A4170(CombatTask* t, int a)
{
    WindowStyle box;
    MenuWindowItem title;
    int i;
    int prevState;
    title = titleItem_800A4138;
    box.colorSet_2 = 0;
    box.semiTrans_3 = 1;
    box.color_0 = saveData_8008B570.uiColor_20.h;
    DrawMenuItemWithWindow_8002ADB4(&title, &box, 0xF, 0);
    HealTeams_800A48C0();
    if (CountTeamMinions_800A1AAC(0) < 2u && CountTeamMinions_800A1AAC(1) < 2u)
    {
        if (setupState_800A4C14 == 0xFF)
        {
            yesNoCursor_800A4BF0.cursor_8 = stateDefaultSel_800A4BFC[2];
        }
        setupState_800A4C14 = 2;
    }
    else if (setupState_800A4C14 == 0xFF)
    {
        setupState_800A4C14 = 0;
    }
    for (i = 0; i < 2; i++)
    {
        DrawTeam_800A4958(i);
    }
    if (setupState_800A4C14 != 3)
    {
        yesNoWindow_80082784.flags_0 = 10;
        yesNoWindow_80082784.time_4 = GetTime30Hz_8002C64C();
        yesNoWindow_80082784.ot_14 = 10;
        yesNoWindow_80082784.open_8 = windowAnimStep_800A4C8C;
        yesNoWindow_80082784.cursor_C = yesNoCursor_800A4BF0.cursor_8;
        yesNoItemYes_80082708[0].flags_0 = 8;
        yesNoItemNo_80082740[0].flags_0 = 8;
        yesNoItemYes_80082708[0].x_10 = 0xC8;
        yesNoItemYes_80082708[0].y_12 = 0xC3;
        yesNoItemNo_80082740[0].x_10 = 0xF6;
        yesNoItemNo_80082740[0].y_12 = 0xC3;
        DrawMenuWindows_8002A5A4(&yesNoWindow_80082784);
    }
    if (++windowAnimStep_800A4C8C >= 9)
    {
        windowAnimStep_800A4C8C = 8;
    }
    DrawSmallTextBox_8002AF58(&stateQuestions_800A4C04[setupState_800A4C14], 0, 0xF);
    DrawButtonHelpBar_8002B004(helpBarSelect_800826E8, 0, 0xF);
    DrawMenuBackground_8002BE10();
    UpdateMenuCursor_8003D794(&yesNoCursor_800A4BF0, 0);
    prevState = setupState_800A4C14;
    setupStateHandlers_800A4C7C[prevState](t, a);
    if (prevState != setupState_800A4C14)
    {
        yesNoCursor_800A4BF0.cursor_8 = stateDefaultSel_800A4BFC[setupState_800A4C14];
    }
}

// state 0: "Allow minion changing?" (combat flag 2); skips the shuffle question when no team has two minions
void SetupAllowChangeInput_800A43FC()
{
    if (IsConfirmPressedP1_8003D380(1))
    {
        if (yesNoCursor_800A4BF0.cursor_8 == 0)
        {
            combatFlags_800A3A88 |= 2;
        }
        else
        {
            combatFlags_800A3A88 &= ~2;
        }
        if (CountTeamMinions_800A1AAC(0) >= 2u || CountTeamMinions_800A1AAC(1) >= 2u)
        {
            setupState_800A4C14 = setupState_800A4C14 + 1;
        }
        else
        {
            setupState_800A4C14 = 2;
        }
    }
}

// state 1: "Shuffle minion order?" yes starts the shuffle animation (state 3)
void SetupShuffleInput_800A4498()
{
    if (IsConfirmPressedP1_8003D380(1) && yesNoCursor_800A4BF0.cursor_8 == 1)
    {
        setupState_800A4C14 = setupState_800A4C14 + 1;
    }
    else if (IsConfirmPressedP1_8003D380(1))
    {
        setupState_800A4C14 = 3;
        shuffleTimer_800A4C94 = 0;
        shufflePhase_800A4C92 = 0;
        shuffleLimit_800A4C90 = (frameCount_8008D3FC & 0xF) + 0x2D;
    }
}

// state 2: "Start fight?" returns to the versus task, combat flag 1 set when confirmed
void SetupStartFightInput_800A4524(CombatTask* task)
{
    if (IsConfirmPressedP1_8003D380(1) && yesNoCursor_800A4BF0.cursor_8 == 1)
    {
        task->next_8 = CombatNextStage_800A16FC;
        combatFlags_800A3A88 &= ~1;
    }
    else if (IsConfirmPressedP1_8003D380(1))
    {
        setupState_800A4C14 = 1;
        combatFlags_800A3A88 |= 1;
        task->next_8 = CombatNextStage_800A16FC;
    }
}

// state 3: reshuffles every frame, then ever slower, then back to "Start fight?"
void SetupShuffleAnim_800A45B8()
{
    short phase = shufflePhase_800A4C92;
    switch (phase)
    {
    case 0:
        ShuffleTeams_800A46FC();
        if (shuffleLimit_800A4C90 < shuffleTimer_800A4C94++)
        {
            shufflePhase_800A4C92 = 1;
            shuffleTimer_800A4C94 = 0;
            shuffleDelay_800A4C96 = 0;
            shuffleLimit_800A4C90 = (((unsigned int)frameCount_8008D3FC & 0x70) >> 4) + 5;
        }
        break;
    case 1:
        if (shuffleDelay_800A4C96 < shuffleTimer_800A4C94++)
        {
            shufflePhase_800A4C92 = 2;
        }
        break;
    case 2:
        ShuffleTeams_800A46FC();
        shufflePhase_800A4C92 = 1;
        shuffleTimer_800A4C94 = 0;
        if (shuffleLimit_800A4C90 < shuffleDelay_800A4C96++)
        {
            setupState_800A4C14 = 2;
        }
        break;
    }
}

void ShuffleTeams_800A46FC()
{
    int i;
    for (i = 0; i < 2; i++)
    {
        ShuffleTeam_800A473C(i);
    }
    PlaySfx_80031494(0x7F);
}

void ShuffleTeam_800A473C(int side)
{
    int used[10];
    int order[10];
    Minion shuffled[10];
    int count = CountTeamMinions_800A1AAC(side);
    Minion* units = teams_800A3AA0[side];
    int i;
    if (count < 2)
    {
        return;
    }
    for (i = 0; i < count; i++)
    {
        used[i] = -1;
        order[i] = -1;
    }
    for (i = 0; i < count; i++)
    {
        order[i] = PickNthFreeSlot_800A4878(rand() % (count - i), used, count);
        MemCopy_800403E8(&shuffled[i], &units[order[i]], 0xF8);
    }
    for (i = 0; i < count; i++)
    {
        MemCopy_800403E8(&units[i], &shuffled[i], 0xF8);
    }
}

int PickNthFreeSlot_800A4878(int nth, int* slots, int count)
{
    int i;
    int cnt = 0;
    i = 0;
    for (; i < count; i++, slots++)
    {
        if (*slots < 0)
        {
            if (cnt == nth)
            {
                *slots = cnt;
                break;
            }
            cnt++;
        }
    }
    return i;
}

// Fully heals every minion of both teams
void HealTeams_800A48C0()
{
    int i;
    int j;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 3; j++)
        {
            Minion* minion = &teams_800A3AA0[i][j];
            if (IsMinionSlotEmpty_800A1934(minion) == 0)
            {
                Heal_80011CD0(&minion->status_84);
            }
        }
    }
}

void DrawTeam_800A4958(int side)
{
    WindowStyle box;
    int slot;
    box.semiTrans_3 = 1;
    box.colorSet_2 = 0;
    box.color_0 = saveData_8008B570.uiColor_20.h;
    DrawMenuItemWithWindow_8002ADB4(playerLabelItems_800A4C50[side], &box, 0xF, 0);
    for (slot = 0; slot < 3; slot++)
    {
        DrawTeamMinion_800A49DC(side, slot);
    }
}

void DrawTeamMinion_800A49DC(int side, int slot)
{
    WindowStyle c1;
    MenuWindowItem label;
    short pos[4];
    WindowStyle c2;
    RECT r1;
    short pos2[4];
    WindowStyle c3;
    RECT r2;
    Minion* minion = &teams_800A3AA0[side][slot];
    if (IsMinionSlotEmpty_800A1934(minion) != 1)
    {
        label = minionLabelItem_800A4154;
        label.text_4 = slotLabelSprites_800A4C58[slot];
        label.x_10 = minionSlotPos_800A4C64[side][slot][0];
        label.y_12 = minionSlotPos_800A4C64[side][slot][1];
        c1.colorSet_2 = 0;
        c1.semiTrans_3 = 1;
        c1.color_0 = saveData_8008B570.uiColor_20.i;
        DrawMenuItemWithWindow_8002ADB4(&label, &c1, 0xF, 0);
        pos[0] = minionSlotPos_800A4C64[side][slot][0] + 0x2F;
        pos[1] = minionSlotPos_800A4C64[side][slot][1];
        DrawHpGauge_8002F078(&minion->status_84, pos, 0, 0xF);
        c2.colorSet_2 = 0;
        c2.semiTrans_3 = 1;
        c2.color_0 = saveData_8008B570.uiColor_20.i;
        r1.x = minionSlotPos_800A4C64[side][slot][0] + 0x32;
        r1.y = minionSlotPos_800A4C64[side][slot][1];
        r1.w = 0x5E;
        r1.h = 0x14;
        DrawWindow_80042460(&r1, &c2, pOT_8008D454 + 15, 0);
        pos2[0] = minionSlotPos_800A4C64[side][slot][0];
        pos2[1] = minionSlotPos_800A4C64[side][slot][1] + 0x14;
        DrawMinionNameLevel_800A1844(minion, pos2, 0);
        c3.colorSet_2 = 0;
        c3.semiTrans_3 = 1;
        c3.color_0 = saveData_8008B570.uiColor_20.i;
        r2.x = minionSlotPos_800A4C64[side][slot][0];
        r2.y = minionSlotPos_800A4C64[side][slot][1] + 0x14;
        r2.w = 0x90;
        r2.h = 0x13;
        DrawWindow_80042460(&r2, &c3, pOT_8008D454 + 15, 0);
    }
}
