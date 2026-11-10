// COMBRSLT.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "combrslt.h"

int combrsltHeader_800A4088 SDATA = 23; // first word of the overlay

MenuCursor slotCursor_800A47E8 = { 1, 1, 1, 0x40, 0, 0 };
int unused_800A47F4 = 0;
MenuWindowItem playerLabelItemP1_800A47F8 = { 8, 1, { .num = 51 }, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 10, 20, 0x32, 0x14, 2, 4 };
MenuWindowItem playerLabelItemP2_800A4814 = { 8, 1, { .num = 223 }, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 260, 20, 0x32, 0x14, 2, 4 };
MenuWindowItem* playerLabelItems_800A4830[2] = { &playerLabelItemP1_800A47F8, &playerLabelItemP2_800A4814 };
// text_4 set to the win / lose / draw sprite (DrawPlayerResult_800A4240)
MenuWindowItem resultItemP1_800A4838 = { 8, 1, 0, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 10, 41, 0x32, 0x14, 2, 4 };
MenuWindowItem resultItemP2_800A4854 = { 8, 1, 0, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 260, 41, 0x32, 0x14, 2, 4 };
MenuWindowItem* resultItems_800A4870[2] = { &resultItemP1_800A4838, &resultItemP2_800A4854 };
// the score boxes (window only: DrawScorePair_800A444C draws the numbers)
MenuWindowItem scoreWindowP1_800A4878 = { 8, 0, 0, NULL, NULL, 28, 193, 0x63, 0x15, 2, 4 };
MenuWindowItem scoreWindowP2_800A4894 = { 8, 0, 0, NULL, NULL, 184, 193, 0x63, 0x15, 2, 4 };
MenuWindowItem* scoreWindows_800A48B0[2] = { &scoreWindowP1_800A4878, &scoreWindowP2_800A4894 };
int slotLabelSprites_800A48B8[3] = { 219, 115, 102 };
CombRsltPos minionSlotPos_800A48C4[2][3] = {
    { { 10, 64 }, { 10, 109 }, { 10, 154 } },
    { { 166, 64 }, { 166, 109 }, { 166, 154 } },
};

const MenuWindowItem resultTitleItem_800A408C = { 8, 1, { .num = 159 }, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 122, 20, 0x4C, 0x14, 2, 4 };
const MenuWindowItem minionLabelItem_800A40A8 = { 8, 1, 0, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0, 0, 0x32, 0x14, 2, 4 };
const MenuWindowItem minionHpItem_800A40C4 = { 10, 1, { .num = 64 }, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0, 0, 0x5E, 0x14, 2, 4 };

// Versus mode result screen: per player result, score and minions; any button fades back to the versus task
void VersusResultTask_800A40E0(CombatTask* task)
{
    WindowStyle box;
    MenuWindowItem title = resultTitleItem_800A408C;
    int i;
    box.colorSet_2 = 0;
    box.semiTrans_3 = 1;
    box.color_0 = saveData_8008B570.uiColor_20.h;
    DrawMenuItemWithWindow_8002ADB4(&title, &box, 0xF, 0);
    for (i = 0; i < 2; i++)
    {
        DrawPlayerResult_800A4240(i);
    }
    DrawMenuBackground_8002BE10();
    DrawButtonHelpBar_8002B004(helpBarSelectQuit_80082680, 0, 0xF);
    if (IsConfirmPressedP1_8003D380(1) || IsCancelPressedP1_8003D41C(1))
    {
        SetFadeMode_8001C19C(1, 0x20);
        task->next_8 = VersusResultFadeOut_800A41E4;
    }
}

void VersusResultFadeOut_800A41E4(CombatTask* task, int arg)
{
    if (IsFadeDone_8001C2FC() == 1)
    {
        SetFadeMode_8001C19C(3, 0x20);
        task->next_8 = CombatNextStage_800A16FC;
        task->next_8(task, arg);
    }
}


void DrawPlayerResult_800A4240(int player)
{
    WindowStyle box;
    short pos[2];
    int j;
    int res;
    int result = sideResult_800A3A98[player];
    switch (result)
    {
    case 0:
        resultItems_800A4870[player]->text_4.num = 0xE6;
        box.colorSet_2 = 1;
        break;
    case 1:
        resultItems_800A4870[player]->text_4.num = 0x68;
        box.colorSet_2 = 2;
        break;
    case 2:
        resultItems_800A4870[player]->text_4.num = 0x41;
        box.colorSet_2 = 2;
        break;
    }
    box.color_0 = saveData_8008B570.uiColor_20.h;
    box.semiTrans_3 = 1;
    DrawMenuItemWithWindow_8002ADB4(playerLabelItems_800A4830[player], &box, 0xF, GetTime30Hz_8002C64C());
    DrawMenuItemWithWindow_8002ADB4(resultItems_800A4870[player], &box, 0xF, GetTime30Hz_8002C64C());
    pos[0] = scoreWindows_800A48B0[player]->x_10;
    pos[1] = scoreWindows_800A48B0[player]->y_12;
    DrawScorePair_800A444C(pos, 0xF, sideWins_800A3A90[player ^ 1], sideWins_800A3A90[player]);
    DrawMenuItemWithWindow_8002ADB4(scoreWindows_800A48B0[player], &box, 0xF, GetTime30Hz_8002C64C());
    j = 0;
    res = sideResult_800A3A98[player];
    if (res < 3 && res != 0)
        box.colorSet_2 = 0;
    for (j = 0; j < 3; j++)
        DrawResultMinion_800A4554(player, j + slotCursor_800A47E8.scroll_A, &box);
}

// Draws the two numbers of a player's score box, each followed by a UI sprite (0xAE, 0x4D)
void DrawScorePair_800A444C(unsigned short* pos, int ot, int oppWins, int ownWins)
{
    short xy[2];
    {
        unsigned int x;
        unsigned int y;
        x = pos[0];
        xy[0] = x + 0x1C;
        y = pos[1];
        xy[1] = y + 4;
        xy[0] = x + 0x12;
        xy[1] = y + 7;
        DrawSmallNumber3_8002C290(xy, oppWins, ot);
    }
    {
        unsigned int x;
        unsigned int y;
        x = pos[0];
        xy[0] = x + 0x1C;
        y = pos[1];
        xy[0] = x + 0x14;
        xy[1] = y + 5;
        DrawUiTiySprt_8002C06C(xy, 0xAE, ot);
    }
    {
        unsigned int x;
        unsigned int y;
        x = pos[0];
        xy[0] = x + 0x43;
        y = pos[1];
        xy[1] = y + 4;
        xy[0] = x + 0x39;
        xy[1] = y + 7;
        DrawSmallNumber3_8002C290(xy, ownWins, ot);
    }
    {
        unsigned int x;
        unsigned int y;
        x = pos[0];
        xy[0] = x + 0x43;
        y = pos[1];
        xy[0] = x + 0x3B;
        xy[1] = y + 5;
        DrawUiTiySprt_8002C06C(xy, 0x4D, ot);
    }
}


void DrawResultMinion_800A4554(int player, int slot, WindowStyle* box)
{
    MenuWindowItem label = minionLabelItem_800A40A8;
    MenuWindowItem hp;
    CombRsltPos r1;
    CombRsltPos r2;
    CombRsltPos r3[2];
    Minion* minion;
    int fainted;
    if (IsMinionFainted_800A1958(&teams_800A3AA0[player][slot]))
    {
        label.flags_0 |= 2;
        fainted = 1;
    }
    else
    {
        fainted = 0;
        label.flags_0 &= ~2;
    }
    minion = &teams_800A3AA0[player][slot];
    if (IsMinionSlotEmpty_800A1934(minion) != 1)
    {
        label.text_4.num = slotLabelSprites_800A48B8[slot];
        label.x_10 = minionSlotPos_800A48C4[player][slot].x;
        label.y_12 = minionSlotPos_800A48C4[player][slot].y;
        DrawMenuItemWithWindow_8002ADB4(&label, box, 0xF, GetTime30Hz_8002C64C());
        hp = minionHpItem_800A40C4;
        hp.x_10 = minionSlotPos_800A48C4[player][slot].x + 0x32;
        hp.y_12 = minionSlotPos_800A48C4[player][slot].y;
        if (!fainted)
        {
            r1.x = minionSlotPos_800A48C4[player][slot].x + 0x2F;
            r1.y = minionSlotPos_800A48C4[player][slot].y;
            DrawHpGauge_8002F078(&minion->status_84, (unsigned short*)&r1, 0, 0xF);
            hp.type_2 = 0;
        }
        DrawMenuItemWithWindow_8002ADB4(&hp, box, 0xF, GetTime30Hz_8002C64C());
        r2.x = minionSlotPos_800A48C4[player][slot].x;
        r2.y = minionSlotPos_800A48C4[player][slot].y + 0x14;
        DrawMinionNameLevel_800A1844(minion, (unsigned short*)&r2, label.flags_0);
        r3[0].x = minionSlotPos_800A48C4[player][slot].x;
        r3[0].y = minionSlotPos_800A48C4[player][slot].y + 0x14;
        r3[1].x = 0x90;
        r3[1].y = 0x13;
        DrawWindow_80042460((RECT*)r3, box, pOT_8008D454 + 15, GetTime30Hz_8002C64C());
    }
}
