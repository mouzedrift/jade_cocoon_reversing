// COMBBTL.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "camera.h"
#include "combbtl.h"

int dword_800A4088 SDATA = 22;
short previewHp_800A82D0 = 0;
short previewMp_800A82D2 = 0;
short sideWindowPos_800A82D4[2][2] = {
    { 10, 20 },
    { 210, 20 },
};
CombBtlNode *announcerTask_800A82DC = 0;
short pendingXa_800A82E0[4] = { 0 };
int turnCount_800A82E8 = 0;
// the announcer's message lists (NULL terminated), picked by ResolveCommand_800A616C / RunExchange_800A68E0
const char *winLinesP1_800A82EC[5] = {
    "\202b\202\217\202\216\202\207\202\222\202\201\202\224\202\225\202\214\202\201\202\224\202\211\202\217\202\216\202\223\201I", // Congratulations!
    "\202s\202\210\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\202\223\201@\202\217\202\206\201@\202\224\202\210\202\205\201@\202c\202\201\202\227\202\216", // The Minions of the Dawn
    "\202\201\202\222\202\205\201@\202\226\202\211\202\203\202\224\202\217\202\222\202\211\202\217\202\225\202\223\201I", // are victorious!
};
const char *winLinesP2_800A8300[5] = {
    "\202b\202\217\202\216\202\207\202\222\202\201\202\224\202\225\202\214\202\201\202\224\202\211\202\217\202\216\202\223\201I", // Congratulations!
    "\202s\202\210\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\202\223\201@\202\217\202\206\201@\202\224\202\210\202\205\201@\202r\202\225\202\216\202\223\202\205\202\224", // The Minions of the Sunset
    "\202\201\202\222\202\205\201@\202\226\202\211\202\203\202\224\202\217\202\222\202\211\202\217\202\225\202\223\201I", // are victorious!
};
const char *doubleSwapLines_800A8314[4] = {
    "\202h\202\224\201@\202\223\202\205\202\205\202\215\202\223\201@\202\231\202\217\202\225\201@\202\201\202\222\202\205\201@\202\207\202\201\202\225\202\207\202\211\202\216\202\207", // It seems you are gauging
    "\202\205\202\201\202\203\202\210\201@\202\217\202\224\202\210\202\205\202\222\201f\202\223\201@\202\215\202\217\202\226\202\205\202\223\201D", // each other's moves.
};
const char *everyNthTurnLines_800A8324[4] = {
    "\202h\201@\202\203\202\201\202\216\202\216\202\217\202\224\201@\202\224\202\201\202\213\202\205\201@\202\215\202\231\201@\202\205\202\231\202\205\202\223\201@\202\217\202\206\202\206", // I cannot take my eyes off
    "\202\224\202\210\202\211\202\223\201@\202\224\202\210\202\222\202\211\202\214\202\214\202\211\202\216\202\207\201@\202\202\202\201\202\224\202\224\202\214\202\205\201I", // this thrilling battle!
};
const char *dodgeLines_800A8334[4] = {
    "\202n\202\210\201@\202\215\202\231\201C\201@\202\211\202\224\201@\202\204\202\217\202\204\202\207\202\205\202\204\201@\202\224\202\210\202\205\201@\202\202\202\214\202\217\202\227\201I", // Oh my, it dodged the blow!
    "\202m\202\217\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\224\202\201\202\213\202\205\202\216\201D", // No damage taken.
};
const char *directHitLines_800A8344[4] = {
    "\202`\201@\202\204\202\211\202\222\202\205\202\203\202\224\201@\202\210\202\211\202\224\201I", // A direct hit!
    "\202n\202\210\201C\201@\202\224\202\210\202\201\202\224\201@\202\210\202\201\202\204\201@\202\224\202\217\201@\202\210\202\225\202\222\202\224\201I", // Oh, that had to hurt!
};
const char *poisonLines_800A8354[4] = {
    "\202o\202\217\202\211\202\223\202\217\202\216\201I", // Poison!
    "\202s\202\210\202\205\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\214\202\217\202\217\202\213\202\223\201@\202\204\202\211\202\232\202\232\202\231\201D", // The minion looks dizzy.
};
const char *statusLines_800A8364[6] = {
    "\202n\202\210\201@\202\216\202\217\201C\201@\202\211\202\224\201@\202\211\202\223\201@\202\206\202\201\202\214\202\214\202\211\202\216\202\207\201@\202\201\202\223\202\214\202\205\202\205\202\220\201I", // Oh no, it is falling asleep!
    "\202s\202\210\202\211\202\223\201@\202\203\202\217\202\225\202\214\202\204\201@\202\202\202\205\201@\202\204\202\201\202\216\202\207\202\205\202\222\202\217\202\225\202\223\201D", // This could be dangerous.
    "\202h\202\224\201@\202\211\202\223\201@\202\214\202\211\202\213\202\205\201@\202\201\201@\202\210\202\205\202\214\202\220\202\214\202\205\202\223\202\223\201@\202\206\202\211\202\223\202\210", // It is like a helpless fish
    "\202\217\202\216\201@\202\201\201@\202\203\202\210\202\217\202\220\202\220\202\211\202\216\202\207\201@\202\202\202\214\202\217\202\203\202\213\201I", // on a chopping block!
};
const char *stoneLines_800A837C[6] = {
    "\202s\202\210\202\205\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\211\202\223\201@\202\202\202\205\202\211\202\216\202\207\201@\202\224\202\225\202\222\202\216\202\205\202\204\201@\202\211\202\216\202\224\202\217", // The minion is being turned into
    "\202\223\202\224\202\217\202\216\202\205\201I\201@\202h\202\224\201@\202\211\202\223\201@\202\223\202\220\202\222\202\205\202\201\202\204\202\211\202\216\202\207\201@\202\206\202\201\202\223\202\224\201D", // stone! It is spreading fast.
    "\202s\202\210\202\211\202\223\201@\202\203\202\217\202\225\202\214\202\204\201@\202\202\202\205\201@\202\206\202\201\202\224\202\201\202\214\201@\202\211\202\206\201@\202\211\202\224\201@\202\211\202\223", // This could be fatal if it is
    "\202\216\202\217\202\224\201@\202\210\202\205\202\201\202\214\202\205\202\204\201I", // not healed!
};
const char *halfHpLines_800A8394[3] = {
    "\202s\202\210\202\205\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\211\202\223\201@\202\207\202\222\202\201\202\226\202\205\202\214\202\231\201@\202\227\202\217\202\225\202\216\202\204\202\205\202\204\201D", // The minion is gravely wounded.
};
const char *tenthHpLines_800A83A0[4] = {
    "\202h\202\224\201@\202\211\202\223\201@\202\202\202\222\202\205\202\201\202\224\202\210\202\211\202\216\202\207\201@\202\210\202\205\202\201\202\226\202\211\202\214\202\231\201@\202\201\202\216\202\204", // It is breathing heavily and
    "\202\203\202\217\202\225\202\214\202\204\201@\202\213\202\205\202\205\202\214\201@\202\217\202\226\202\205\202\222\201@\202\201\202\224\201@\202\201\202\216\202\231\202\224\202\211\202\215\202\205\201D", // could keel over at anytime.
};
const char *koLines_800A83B0[5] = {
    "\202h\202\223\201@\202\224\202\210\202\205\201@\202\206\202\211\202\207\202\210\202\224\201@\202\217\202\226\202\205\202\222\201H", // Is the fight over?
    "\202h\202\224\201@\202\214\202\217\202\217\202\213\202\223\201@\202\214\202\211\202\213\202\205\201@\202\224\202\210\202\201\202\224\201@\202\211\202\223\201@\202\211\202\224", // It looks like that is it
    "\202\206\202\217\202\222\201@\202\224\202\210\202\211\202\223\201@\202\215\202\211\202\216\202\211\202\217\202\216\201D", // for this minion.
    "\202h\202\224\201@\202\210\202\201\202\223\201@\202\206\202\201\202\214\202\214\202\205\202\216\201@\202\201\202\216\202\204\201@\202\203\202\201\202\216\202\216\202\217\202\224\201@\202\207\202\205\202\224\201@\202\225\202\220\201I", // It has fallen and cannot get up!
};
// unused: an empty list
const char *emptyLines_800A83C4[5] = {
    0,
    "",
    "",
};
// unused
const char *weakSpotLines_800A83D8[5] = {
    "\202v\202\210\202\201\202\224\201@\202\201\201@\202\227\202\205\202\214\202\214\201|\202\203\202\210\202\217\202\223\202\205\202\216\201@\202\201\202\224\202\224\202\201\202\203\202\213\201I", // What a well-chosen attack!
    "\202q\202\211\202\207\202\210\202\224\201@\202\201\202\224\201@\202\224\202\210\202\205\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\202\201\202\214\201@\202\227\202\205\202\201\202\213\201@\202\223\202\220\202\217\202\224\201D", // Right at the elemental weak spot.
    "\202u\202\205\202\222\202\231\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\201D", // Very effective.
};
const char *swapLines_800A83EC[5] = {
    "\202s\202\210\202\205\201@\202\220\202\214\202\201\202\231\202\205\202\222\201@\202\210\202\201\202\223\201@\202\223\202\227\202\211\202\224\202\203\202\210\202\205\202\204\201@\202\215\202\211\202\216\202\211\202\217\202\216\202\223\201I", // The player has switched minions!
    "\202`\201@\202\216\202\205\202\227\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\210\202\201\202\223", // A new minion has
    "\202\205\202\216\202\224\202\205\202\222\202\205\202\204\201@\202\224\202\210\202\205\201@\202\201\202\222\202\205\202\216\202\201\201I", // entered the arena!
};
const char *elementChangeLines_800A8400[5] = {
    "\202`\201@\202\203\202\210\202\201\202\216\202\207\202\205\201@\202\217\202\206\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\202\201\202\214\201@\202\220\202\222\202\217\202\220\202\205\202\222\202\224\202\211\202\205\202\223\201I", // A change of elemental properties!
    "\202v\202\210\202\201\202\224\201@\202\201\202\216\201@\202\205\202\230\202\203\202\211\202\224\202\211\202\216\202\207\201@\202\215\202\217\202\226\202\205\201D", // What an exciting move.
    "\202v\202\210\202\201\202\224\201@\202\227\202\211\202\214\202\214\201@\202\210\202\201\202\220\202\220\202\205\202\216\201@\202\216\202\217\202\227\201I\201H", // What will happen now!?
};
const char *oneBlowLines_800A8414[5] = {
    "\202r\202\225\202\203\202\210\201@\202\217\202\226\202\205\202\222\202\227\202\210\202\205\202\214\202\215\202\211\202\216\202\207\201@\202\220\202\217\202\227\202\205\202\222\201I", // Such overwhelming power!
    "\202s\202\210\202\205\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\210\202\201\202\223\201@\202\206\202\201\202\214\202\214\202\205\202\216", // The minion has fallen
    "\202\227\202\211\202\224\202\210\201@\202\217\202\216\202\205\201@\202\206\202\201\202\224\202\201\202\214\201@\202\202\202\214\202\217\202\227\201I", // with one fatal blow!
};
const char *oneHpLeftLines_800A8428[5] = {
    "\202v\202\210\202\201\202\224\201@\202\201\202\215\202\201\202\232\202\211\202\216\202\207\201@\202\227\202\211\202\214\202\214\202\220\202\217\202\227\202\205\202\222\201I", // What amazing willpower!
    "\202`\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\201\202\214\202\214\201@\202\217\202\204\202\204\202\223\201C", // Against all odds,
    "\202\211\202\224\201@\202\203\202\217\202\225\202\214\202\204\201@\202\202\202\205\201@\202\226\202\211\202\203\202\224\202\217\202\222\202\231\201I", // it could be victory!
};
const char *lossLines_800A843C[6] = {
    "\202`\202\216\202\217\202\224\202\210\202\205\202\222\201@\202\214\202\217\202\223\202\223\201I\201@\202s\202\210\202\205\201@\202\206\202\211\202\207\202\210\202\224\201@\202\210\202\201\202\223\201@\202\202\202\205\202\205\202\216", // Another loss! The fight has been
    "\202\204\202\205\202\203\202\211\202\204\202\205\202\204\201@\202\202\202\205\202\206\202\217\202\222\202\205\201@\202\224\202\210\202\205\201@\202\224\202\210\202\211\202\222\202\204\201@\202\222\202\217\202\225\202\216\202\204\201D", // decided before the third round.
    "\202s\202\217\202\217\201@\202\202\202\201\202\204\201I", // Too bad!
    "\202h\201@\202\227\202\201\202\223\201@\202\205\202\226\202\205\202\216\201@\202\222\202\217\202\217\202\224\202\211\202\216\202\207\201@\202\206\202\217\202\222\201@\202\231\202\217\202\225\201I", // I was even rooting for you!
};
CombBtlLineList6 finalLines_800A8454 = {
    {
        "\202v\202\210\202\201\202\224\201@\202\201\201@\202\203\202\214\202\217\202\223\202\205\201@\202\206\202\211\202\207\202\210\202\224\201I", // What a close fight!
        "\202e\202\211\202\216\202\201\202\214\202\214\202\231\201@\202\201\201@\202\204\202\205\202\203\202\211\202\223\202\211\202\217\202\216\201@\202\210\202\201\202\223\201@\202\202\202\205\202\205\202\216", // Finally a decision has been
        "\202\222\202\205\202\201\202\203\202\210\202\205\202\204\201D", // reached.
        "\202v\202\205\202\214\202\214\201@\202\204\202\217\202\216\202\205\201I", // Well done!
    },
    0x63750B00,
};
short hpDamage_800A8470[2] = { 0 };
short mpDamage_800A8474[2] = { 0 };
MsgWindowEntry* announcerWindow_800A8478 = 0;
int unused_800A847C = 0;
int statusCured_800A8480[2] = { 0 };
short exchangeStep_800A8488 = 0;
EventEntry *commandMenuTask_800A848C = 0;
int koSide_800A8490 = 0;
ShortPair hitWindow_800A8494 = { 0 };
int stageElement_800A8498 = 0;
int fixedStageElement_800A849C = 0;
int newStageElement_800A84A0 = 0;
short targetSfx_800A84A4 = 0;
short koSfx_800A84A6 = 0;
unsigned char exchangeFlags_800A84A8 = 0;
int unused_800A84AC = 0;
int sideEntering_800A84B0[2] = { 0 };
int setupStep_800A84B8 = 0;
short actorHpLoss_800A84BC = 0;
int stageId_800A84C0 = 0;
short actorMpLoss_800A84C4 = 0;
ShortPair sideHitWindows_800A84C8[2] = { { 0 } };
short sideGauges_800A84D0[2] = { 0 };
int waitTimer_800A84D4 = 0;
CombBtlHist commandHistory_800A84D8[10] = { { 0 } };
int fileRequest_800A85A0 = 0;
int unused_800A85A4 = 0;
BattleCmd actorCmd_800A85A8 = { 0 };
int actorSide_800A85B8 = 0;
unsigned char swapSlot_800A85BC = 0;
unsigned char actorSlot_800A85BD = 0;
const char** announcerLines_800A85C0 = 0;
int unused_800A85C4 = 0;
ActionResult result_800A85C8 = { 0 };
int statusInflicted_800A85F0[2] = { 0 };
int loserSide_800A85F8 = 0;
unsigned char sideHitKind_800A85FC[4] = { 0 };
BattleCmd chosenCmd_800A8600 = { 0 };
BattleCmd targetCmd_800A8610 = { 0 };
int targetSide_800A8620 = 0;

void CombBtlStart_800A4B8C(CombBtlTask* t, int a)
{
    fileRequest_800A85A0 = LoadOverlay_80020BF8(1, 6);
    stageId_800A84C0 = (unsigned int)gnFrame_8008D610 % 39;
    t->next_8 = CombBtlWaitFile_800A4C40;
    t->next_8(t, a);
    StopSoundSeqs_80030D68(&bgmSound_80091CE0);
    PlayMusic_800300E0(0, 1);
}

void CombBtlWaitFile_800A4C40(CombBtlTask* t, int a)
{
    if (GetFileRequestStatus_8003BE30(fileRequest_800A85A0) == 0)
    {
        newStageElement_800A84A0 = -1;
        stageElement_800A8498 = -1;
        fixedStageElement_800A849C = -1;
        battleResult_800A38DC = 2;
        actorSide_800A85B8 = -1;
        targetSide_800A8620 = -1;
        SetBattleStageId_80039FA4(stageId_800A84C0);
        InitCombatSlots_800A0A28();
        setupStep_800A84B8 = 0;
        loserSide_800A85F8 = -1;
        ResetSides_800A4CFC();
        t->next_8 = CombBtlSetup_800A4D48;
        t->next_8(t, a);
    }
}

void ResetSides_800A4CFC()
{
    unsigned int i;
    for (i = 0; i < 2; i++)
    {
        sideSlot_800A4078[i] = -1;
        sideResult_800A3A98[i] = 0;
        sideGauges_800A84D0[i] = 0;
    }
}

void CombBtlSetup_800A4D48(CombBtlTask* t, int a)
{
    switch (setupStep_800A84B8)
    {
    case 0:
        if (!LoadSeqSlotSound_800303E8())
        {
            break;
        }
        setupStep_800A84B8 = 1;
    case 1:
        if (!IsSoundTaskReady_80030688())
        {
            break;
        }
        FreeBgmAndSfx_800315F4();
        setupStep_800A84B8 = 2;
    case 2:
        if (!PlayMusic_800300E0(0x99, 1))
        {
            break;
        }
        setupStep_800A84B8 = 3;
    case 3:
        LoadStageEffects_800BC878();
        setupStep_800A84B8 = 4;
    case 4:
        if (!AreStageEffectsLoaded_800BC8E8())
        {
            break;
        }
        setupStep_800A84B8 = 5;
    case 5:
        StartArenaCamera_800A7290();
        StartFadeTask_800A7420();
        SetCameraBattleMode_80037720();
        StartBattleCamera_80037748();
        setupStep_800A84B8 = 9;
        break;
    case 6:
        SetFadeMode_8001C19C(3, 0x20);
        setupStep_800A84B8 = 7;
    case 7:
        LoadUiTiy_8002BF74();
        setupStep_800A84B8 = 8;
    case 8:
        if (!uiTiyLoaded_8008B4E8)
        {
            break;
        }
        setupStep_800A84B8 = 9;
    case 9:
        if (GetCameraMode_800378F8() != 4)
        {
            t->next_8 = CheckBattleOver_800A4EC8;
            t->next_8(t, a);
        }
        break;
    }
}

void CheckBattleOver_800A4EC8(CombBtlTask* t, int a)
{
    int ok[2];
    unsigned int i;
    unsigned int j;
    for (i = 0; i < 2; i++)
    {
        ok[i] = 1;
        for (j = 0; j < 3; j++)
        {
            if (IsMinionSlotEmpty_800A1934(&teams_800A3AA0[i][j]) == 0 && IsMinionFainted_800A1958(&teams_800A3AA0[i][j]) == 0)
            {
                ok[i] = 0;
                break;
            }
        }
        if (ok[i] == 1)
        {
            loserSide_800A85F8 = i;
            break;
        }
    }
    if (loserSide_800A85F8 >= 0)
    {
        t->next_8 = PlayVictoryJingle_800A5000;
    }
    else
    {
        setupStep_800A84B8 = 10;
        t->next_8 = SendInMinions_800A5638;
    }
    t->next_8(t, a);
}

void PlayVictoryJingle_800A5000(CombBtlTask* t)
{
    if (bgmSound_80091CE0.seqNum_4 >= 0)
    {
        SsSepSetDecrescendo(bgmSound_80091CE0.sepAccessNum_C, bgmSound_80091CE0.seqNum_4, 0x7F, 0x78);
        bgmSound_80091CE0.seqNum_4 = -1;
    }
    StopSeqSlot_80031334(0);
    PlaySeqSlot_80031160(1, 1);
    waitTimer_800A84D4 = 0x78;
    t->next_8 = WaitVictoryJingle_800A5080;
}

void WaitVictoryJingle_800A5080(CombBtlTask* t)
{
    if (--waitTimer_800A84D4 <= 0)
    {
        FadeOutSeqSlot_800313C8(0);
        StopSeqSlot_80031334(0);
        StopSoundSeqs_80030D68(&systemSound_80091D40);
        FreeSeqSlotSound_80030664();
        t->next_8 = RecordBattleResult_800A50E4;
    }
}

void RecordBattleResult_800A50E4(CombBtlTask* t)
{
    int idle = IsEffectTaskIdle_800148D4();
    if (idle == 1)
    {
        if (loserSide_800A85F8 < 0)
        {
            if (battleResult_800A38DC == idle)
            {
                loserSide_800A85F8 = actorSide_800A85B8;
                sideWins_800A3A90[actorSide_800A85B8]++;
                if (sideWins_800A3A90[actorSide_800A85B8] >= 100)
                {
                    sideWins_800A3A90[actorSide_800A85B8] = 99;
                }
            }
            else
            {
                t->next_8 = CombBtlEnd_800A54CC;
                return;
            }
        }
        else
        {
            battleResult_800A38DC = 0;
            sideResult_800A3A98[loserSide_800A85F8] = idle;
            sideWins_800A3A90[loserSide_800A85F8]++;
            if (sideWins_800A3A90[loserSide_800A85F8] >= 100)
            {
                sideWins_800A3A90[loserSide_800A85F8] = 99;
            }
        }
        t->next_8 = AnnounceWinner_800A51EC;
        waitTimer_800A84D4 = 0x1E;
    }
}

void AnnounceWinner_800A51EC(CombBtlTask* t)
{
    if (--waitTimer_800A84D4 <= 0)
    {
        if (loserSide_800A85F8 == 1)
        {
            SetAnnouncerXa_800A8078(7, 0x3BC, 0x1B);
            announcerTask_800A82DC = StartAnnouncer_800A8098(0, winLinesP1_800A82EC, 1);
        }
        else
        {
            SetAnnouncerXa_800A8078(9, 0x3BF, 0x1F);
            announcerTask_800A82DC = StartAnnouncer_800A8098(0, winLinesP2_800A8300, 0);
        }
        t->next_8 = DrawWinnerBanner_800A5290;
    }
}

const MenuWindowItem winnerBanner_800A4A54 = { 8, 1, 0, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x87, 0x56, 0x32, 0x14, 2, 4 };
const MenuWindowItem resultBanner_800A4A70 = { 8, 1, 0xE6, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x87, 0x6B, 0x32, 0x14, 2, 4 };

void DrawWinnerBanner_800A5290(CombBtlTask* t)
{
    WindowStyle box;
    MenuWindowItem winner = winnerBanner_800A4A54;
    int icons[2];
    MenuWindowItem result;
    icons[0] = 0x33;
    icons[1] = 0xDF;
    winner.text_4 = icons[loserSide_800A85F8 ^ 1];
    box.colorSet_2 = 1;
    box.semiTrans_3 = 1;
    box.color_0 = saveData_8008B570.uiColor_20.h;
    DrawMenuItemWithWindow_8002ADB4(&winner, &box, 0xF, GetTime30Hz_8002C64C());
    result = resultBanner_800A4A70;
    box.colorSet_2 = 1;
    box.semiTrans_3 = 1;
    box.color_0 = saveData_8008B570.uiColor_20.h;
    DrawMenuItemWithWindow_8002ADB4(&result, &box, 0xF, GetTime30Hz_8002C64C());
    if (announcerTask_800A82DC == 0 || (announcerTask_800A82DC->flags & 0x8001) != 1)
    {
        announcerTask_800A82DC = 0;
        t->next_8 = CombBtlEnd_800A54CC;
    }
}

MsgWindowEntry* OpenAnnouncerWindow_800A5408(int which, int lines, int side)
{
    MsgWindowCfg cfg;
    int kinds[2] = {2, 3};
    char* tbl[2] = {"\202q\202\201" /* Ra */, "\202l\202\225" /* Mu */};
    cfg.posMode_0 = 2;
    cfg.pos_4 = 0;
    cfg.text_8 = (int*)lines;
    cfg.field_10 = (saveData_8008B570.settings_1C.word & 7) != 3;
    cfg.cancelable_14 = 0;
    cfg.mask_18 = 0;
    cfg.lines_1C = 0;
    cfg.portraitKind_20 = 7;
    cfg.portraitId_24 = kinds[which];
    cfg.style_28 = side;
    cfg.field_2C = 1;
    cfg.field_30 = 0;
    cfg.field_34 = 0;
    cfg.field_38 = (saveData_8008B570.settings_1C.word >> 3) & 1;
    cfg.field_3C = 1;
    cfg.field_40 = 0;
    cfg.title_C = tbl[which];
    return OpenMessageWindow_8003422C(&cfg);
}

void CombBtlEnd_800A54CC(CombBtlTask* t)
{
    FadeOutSeqSlot_800313C8(0);
    if (bgmSound_80091CE0.seqNum_4 >= 0)
    {
        SsSepSetDecrescendo(bgmSound_80091CE0.sepAccessNum_C, bgmSound_80091CE0.seqNum_4, 0x7F, 0x78);
        bgmSound_80091CE0.seqNum_4 = -1;
    }
    StartSceneFadeOut_8001AA50(0x1E);
    CloseSideWindows_800A7BE4();
    t->next_8 = CombBtlExit_800A5544;
}

void CombBtlExit_800A5544(CombBtlTask* t)
{
    int i;
    if (IsSceneFadeDone_8001AB94() == 1)
    {
        StopArenaCamera_800A73E4();
        StopFadeTask_800A7478();
        for (i = 0; i < 2; i++)
        {
            if (sideSlot_800A4078[i] >= 0)
            {
                if (IsMinionFainted_800A1958(&teams_800A3AA0[i][sideSlot_800A4078[i]]) == 0)
                {
                    RemoveSideMinion_800A7560(i);
                }
            }
        }
        FreeCombatSlots_800A0A6C();
        FreeSeqSlotSound_80030664();
        SsUtAllKeyOff(0);
        PlayMusic_800300E0(0x8E, 1);
        FreeStageEffects_80039FC0();
        t->next_8 = CombatNextStage_800A16FC;
    }
}

void SendInMinions_800A5638(CombBtlTask* t, int a)
{
    int i;
    int any;
    switch ((unsigned int)setupStep_800A84B8)
    {
    case 10:
        any = 0;
        for (i = 0; i < 2; i++)
        {
            sideEntering_800A84B0[i] = 0;
            if (sideSlot_800A4078[i] < 0 || IsMinionFainted_800A1958(&teams_800A3AA0[i][sideSlot_800A4078[i]]))
            {
                NextLivingMinion_800A58E8(i);
                StartSlotModel_800A0ACC(i, &teams_800A3AA0[i][sideSlot_800A4078[i]]);
                any = sideEntering_800A84B0[i] = 1;
            }
        }
        if (any == 1)
        {
            setupStep_800A84B8 = 11;
        }
        else
        {
            void (*f)() = ChooseNextActor_800A599C;
            t->next_8 = f;
            f(t, a);
        }
        break;
    case 11:
        if (AreSideModelsReady_800A758C() == 1)
        {
            for (i = 0; i < 2; i++)
            {
                if (sideEntering_800A84B0[i] == 1)
                {
                    CreateSideActor_800A74A0(i);
                    OpenSideWindow_800A75F8(i);
                }
            }
            for (i = 0; i < 2; i++)
            {
                MoveSlotActorTo_800A0E1C(i, GetSlotPos_800A10DC(i ^ 1));
                SetSlotStatusTint_800A1068(i);
            }
            setupStep_800A84B8 = 12;
        }
        break;
    case 12:
        ResetCommands_800A5BB4();
        ClearHitResults_800A60F0();
        actorSide_800A85B8 = 0;
        targetSide_800A8620 = 1;
        exchangeStep_800A8488 = 0;
        actorSlot_800A85BD = sideSlot_800A4078[0];
        if (sideEntering_800A84B0[0] == 1)
        {
            sideEntering_800A84B0[0] = 0;
            actorCmd_800A85A8.kind_0 = 2;
            actorCmd_800A85A8.arg_4 = 0;
            actorCmd_800A85A8.mask_8 = 0x100;
            actorCmd_800A85A8.targets_C = 0;
        }
        if (sideEntering_800A84B0[1] == 1)
        {
            sideEntering_800A84B0[1] = 0;
            targetCmd_800A8610.kind_0 = 2;
            targetCmd_800A8610.arg_4 = 0;
            targetCmd_800A8610.targets_C = 0;
            targetCmd_800A8610.mask_8 = 1 << (targetSide_800A8620 + 8);
        }
        t->next_8 = RunExchange_800A68E0;
        break;
    }
}

void NextLivingMinion_800A58E8(int side)
{
    Minion* minion;
    do
    {
        sideSlot_800A4078[side]++;
        if (sideSlot_800A4078[side] >= 3)
        {
            sideSlot_800A4078[side] = 0;
        }
        minion = &teams_800A3AA0[side][sideSlot_800A4078[side]];
    } while (IsMinionSlotEmpty_800A1934(minion) || IsMinionFainted_800A1958(minion));
}

void ChooseNextActor_800A599C(CombBtlTask* t, int side)
{
    int gauge[2];
    int i;
    void (*f)();
    actorSide_800A85B8 = -1;
    targetSide_800A8620 = -1;
    if (sideGauges_800A84D0[0] == 0 && sideGauges_800A84D0[1] == 0)
    {
        sideGauges_800A84D0[(gnFrame_8008D610 & 2) >> 1] += 100;
    }
    for (i = 0; i < 2; i++)
    {
        gauge[i] = (short)GetGaugeRate_800A5B70(i);
    }
    while (actorSide_800A85B8 < 0)
    {
        for (i = 0; i < 2; i++)
        {
            sideGauges_800A84D0[i] += gauge[i];
            if (sideGauges_800A84D0[i] >= 1000)
            {
                sideGauges_800A84D0[i] -= 1000;
                actorSide_800A85B8 = i;
                targetSide_800A8620 = i ^ 1;
                if (i == 1)
                {
                    sideGauges_800A84D0[1] += gauge[1];
                }
                break;
            }
        }
    }
    if (actorSide_800A85B8 >= 0)
    {
        MoveBattleCameraDefault_800378CC();
    }
    turnCount_800A82E8++;
    actorSlot_800A85BD = sideSlot_800A4078[actorSide_800A85B8];
    f = StartTurn_800A5C64;
    t->next_8 = f;
    f(t, side);
}

int GetGaugeRate_800A5B70(int side)
{
    UnitStatus* status;
    int rate;
    unsigned char stats[0x18];
    status = GetUnitStatus_80014390((side + 8) & 0xFF);

    if (status)
    {
        CalcEquippedStats_80033624(stats, status);
        rate = stats[4] + 0xA;
    }
    else
    {
        rate = 0;
    }
    return rate;
}

void ResetCommands_800A5BB4()
{
    chosenCmd_800A8600.kind_0 = 0x14;
    chosenCmd_800A8600.arg_4 = 0;
    actorCmd_800A85A8.kind_0 = 0x14;
    actorCmd_800A85A8.arg_4 = 0;
    targetCmd_800A8610.kind_0 = 0x14;
    targetCmd_800A8610.arg_4 = 0;
    result_800A85C8.kind_0 = 0;
    result_800A85C8.arg_2 = 0;
    result_800A85C8.flags_4 = 0;
    result_800A85C8.status_8 = 0;
    result_800A85C8.actorHpCost_C = 0;
    result_800A85C8.actorMpCost_10 = 0;
    result_800A85C8.actorHpDamage_14 = 0;
    result_800A85C8.actorMpDamage_18 = 0;
    result_800A85C8.hpDamage_1C = 0;
    result_800A85C8.mpDamage_20 = 0;
    result_800A85C8.areaElement_24 = -1;
    result_800A85C8.fixedElement_26 = -1;
    chosenCmd_800A8600.mask_8 = 1 << (actorSide_800A85B8 + 8);
    chosenCmd_800A8600.targets_C = 1 << (targetSide_800A8620 + 8);
    actorCmd_800A85A8.mask_8 = 1 << (actorSide_800A85B8 + 8);
    actorCmd_800A85A8.targets_C = 1 << (targetSide_800A8620 + 8);
    targetCmd_800A8610.mask_8 = 1 << (targetSide_800A8620 + 8);
    targetCmd_800A8610.targets_C = 1 << (actorSide_800A85B8 + 8);
}

void StartTurn_800A5C64(CombBtlTask* t)
{
    UnitStatus* status;
    int prevFlags;
    int flags;
    int cmdKind;
    ResetCommands_800A5BB4();
    exchangeStep_800A8488 = 0;
    exchangeFlags_800A84A8 &= 0xFC;
    ClearHitResults_800A60F0();
    status = GetUnitStatus_80014390((unsigned char)(actorSide_800A85B8 + 8));
    prevFlags = status->status_0;
    TickUnitStatus_800BF7C4(status, &actorHpLoss_800A84BC, &actorMpLoss_800A84C4);
    if (actorHpLoss_800A84BC != 0)
    {
        if (actorMpLoss_800A84C4 != 0)
        {
            sideHitKind_800A85FC[actorSide_800A85B8] = 3;
            result_800A85C8.kind_0 = 3;
        }
        else
        {
            sideHitKind_800A85FC[actorSide_800A85B8] = 1;
            result_800A85C8.kind_0 = 1;
        }
    }
    else if (mpDamage_800A8474)
    {
        sideHitKind_800A85FC[actorSide_800A85B8] = 2;
        result_800A85C8.kind_0 = 2;
    }
    flags = status->status_0;
    cmdKind = GetStatusCommand_800BFA4C(flags, prevFlags);
    actorCmd_800A85A8.kind_0 = cmdKind;
    actorCmd_800A85A8.targets_C = 0;
    if (flags & 0x200)
    {
        t->next_8 = RunExchange_800A68E0;
        koSfx_800A84A6 = 0x6F;
        exchangeFlags_800A84A8 |= 1;
        koSide_800A8490 = actorSide_800A85B8;
        exchangeFlags_800A84A8 |= 2;
    }
    else if (status->hp_8.cur_0 - actorHpLoss_800A84BC <= 0)
    {
        actorCmd_800A85A8.kind_0 = 0xB;
        actorHpLoss_800A84BC = status->hp_8.cur_0;
        t->next_8 = RunExchange_800A68E0;
        koSfx_800A84A6 = 0x6F;
        exchangeFlags_800A84A8 |= 1;
        koSide_800A8490 = actorSide_800A85B8;
    }
    else if (flags & 2)
    {
        t->next_8 = CheckBattleOver_800A4EC8;
    }
    else if (cmdKind == 0x14)
    {
        t->next_8 = LoadCommandMenu_800A5EB8;
    }
    else
    {
        exchangeFlags_800A84A8 |= 2;
        t->next_8 = RunExchange_800A68E0;
    }
}

void LoadCommandMenu_800A5EB8(CombBtlTask* t)
{
    fileRequest_800A85A0 = LoadOverlay_80020BF8(1, 0x19);
    t->next_8 = OpenCommandMenu_800A5EF8;
}

void OpenCommandMenu_800A5EF8(CombBtlTask* t)
{
    if (GetFileRequestStatus_8003BE30(fileRequest_800A85A0) == 0)
    {
        ResetCommands_800A5BB4();
        commandMenuTask_800A848C = CombComStart_800CB7AC(&chosenCmd_800A8600, actorSide_800A85B8);
        t->next_8 = WaitCommandMenu_800A5F60;
    }
}

void WaitCommandMenu_800A5F60(CombBtlTask* t, int a)
{
    if ((commandMenuTask_800A848C->flags & 0x8001) != 1)
    {
        PushCommandHistory_800A601C();
        if (battleResult_800A38DC)
        {
            sideResult_800A3A98[actorSide_800A85B8] = 2;
            t->next_8 = PlayVictoryJingle_800A5000;
            t->next_8(t, a);
        }
        else
        {
            TakeChosenCommand_800A60A4();
            ResolveCommand_800A616C();
            exchangeStep_800A8488 = 0;
            t->next_8 = RunExchange_800A68E0;
        }
    }
}

void PushCommandHistory_800A601C()
{
    int i;
    for (i = 10; i > 0; i--)
    {
        MemCopy_800403E8(&commandHistory_800A84D8[i], &commandHistory_800A84D8[i - 1], 0x14);
    }
    commandHistory_800A84D8[0].unit_0 = actorSide_800A85B8;
    MemCopy_800403E8(&commandHistory_800A84D8[0].cmd_4, &chosenCmd_800A8600, 0x10);
}

void TakeChosenCommand_800A60A4()
{
    int kind = chosenCmd_800A8600.kind_0;
    actorCmd_800A85A8.kind_0 = kind;
    actorCmd_800A85A8.arg_4 = chosenCmd_800A8600.arg_4;
    actorCmd_800A85A8.mask_8 = chosenCmd_800A8600.mask_8;
    actorCmd_800A85A8.targets_C = chosenCmd_800A8600.targets_C;
    if (kind == 8)
    {
        actorCmd_800A85A8.kind_0 = 3;
        actorCmd_800A85A8.arg_4 = 0;
    }
}

void ClearHitResults_800A60F0()
{
    unsigned int i;
    targetSfx_800A84A4 = -1;
    koSfx_800A84A6 = -1;
    actorHpLoss_800A84BC = 0;
    actorMpLoss_800A84C4 = 0;
    for (i = 0; i < 2; i++)
    {
        hpDamage_800A8470[i] = 0;
        mpDamage_800A8474[i] = 0;
        statusCured_800A8480[i] = 0;
        statusInflicted_800A85F0[i] = 0;
    }
}

void ResolveCommand_800A616C()
{
    UnitStatus* actor = GetUnitStatus_80014390((unsigned char)(actorSide_800A85B8 + 8));
    UnitStatus* u;
    unsigned int i;
    short tenth;
    int bit;
    if (commandHistory_800A84D8[0].cmd_4.kind_0 == 0x12 && commandHistory_800A84D8[1].cmd_4.kind_0 == commandHistory_800A84D8[0].cmd_4.kind_0 &&
        commandHistory_800A84D8[0].unit_0 != commandHistory_800A84D8[1].unit_0)
    {
        SetAnnouncerXa_800A8078(0x15, 0x4D9, 0x13);
        announcerLines_800A85C0 = doubleSwapLines_800A8314;
    }
    else if ((turnCount_800A82E8 & 0xF) == 0)
    {
        SetAnnouncerXa_800A8078(7, 0x4DA, 0x15);
        announcerLines_800A85C0 = everyNthTurnLines_800A8324;
    }
    if (chosenCmd_800A8600.kind_0 == 8)
    {
        SetAnnouncerXa_800A8078(0xE, 0x4E0, 0x1F);
        announcerLines_800A85C0 = swapLines_800A83EC;
    }
    ClearHitResults_800A60F0();
    for (i = 0; i < 2; i++)
    {
        bit = 1 << (i + 8);
        if (!(actorCmd_800A85A8.targets_C & bit))
        {
            continue;
        }
        u = GetUnitStatus_80014390((unsigned char)(i + 8));
        result_800A85C8.areaElement_24 = stageElement_800A8498;
        result_800A85C8.fixedElement_26 = fixedStageElement_800A849C;
        ResolveBattleAction_80012BB0(actor, u, &actorCmd_800A85A8, &result_800A85C8);
        newStageElement_800A84A0 = result_800A85C8.areaElement_24;
        actorHpLoss_800A84BC = result_800A85C8.actorHpCost_C;
        actorMpLoss_800A84C4 = result_800A85C8.actorMpCost_10;
        hpDamage_800A8470[i] = result_800A85C8.hpDamage_1C;
        mpDamage_800A8474[i] = result_800A85C8.mpDamage_20;
        hpDamage_800A8470[actorSide_800A85B8] += result_800A85C8.actorHpDamage_14;
        mpDamage_800A8474[actorSide_800A85B8] += result_800A85C8.actorMpDamage_18;
        if (u->hp_8.cur_0 <= hpDamage_800A8470[i])
        {
            hpDamage_800A8470[i] = u->hp_8.cur_0;
        }
        if (u->mp_C.cur_0 <= mpDamage_800A8474[i])
        {
            mpDamage_800A8474[i] = u->mp_C.cur_0;
        }
        sideHitKind_800A85FC[i] = result_800A85C8.kind_0;
        statusCured_800A8480[i] = result_800A85C8.flags_4;
        statusInflicted_800A85F0[i] = result_800A85C8.status_8;
        if (statusInflicted_800A85F0[i] & 8)
        {
            SetAnnouncerXa_800A8078(0x1F, 0x4DC, 0x29);
            announcerLines_800A85C0 = stoneLines_800A837C;
        }
        else if (statusInflicted_800A85F0[i] & 2)
        {
            SetAnnouncerXa_800A8078(0x11, 0x4DC, 0x2D);
            announcerLines_800A85C0 = statusLines_800A8364;
        }
        else if (statusInflicted_800A85F0[i] & 1)
        {
            SetAnnouncerXa_800A8078(6, 0x4DC, 0x15);
            announcerLines_800A85C0 = poisonLines_800A8354;
        }
        if (newStageElement_800A84A0 != stageElement_800A8498)
        {
            SetAnnouncerXa_800A8078(0x1C, 0x4E1, 0x26);
            announcerLines_800A85C0 = elementChangeLines_800A8400;
        }
        switch (result_800A85C8.kind_0)
        {
        case 0:
            break;
        case 1:
        case 2:
        case 3:
            if (result_800A85C8.hpDamage_1C > 0 || result_800A85C8.mpDamage_20 > 0)
            {
                targetCmd_800A8610.kind_0 = 9;
                targetSfx_800A84A4 = 0x72;
            }
            tenth = u->hp_8.max_2 / 10;
            if (u->hp_8.cur_0 > tenth && u->hp_8.cur_0 - hpDamage_800A8470[i] <= tenth)
            {
                SetAnnouncerXa_800A8078(0x1D, 0x4DE, 0x1B);
                announcerLines_800A85C0 = tenthHpLines_800A83A0;
            }
            else if (u->hp_8.max_2 / 2 < u->hp_8.cur_0 && u->hp_8.cur_0 - hpDamage_800A8470[i] <= u->hp_8.max_2 / 2)
            {
                SetAnnouncerXa_800A8078(0x13, 0x4DE, 0x10);
                announcerLines_800A85C0 = halfHpLines_800A8394;
            }
            break;
        case 4:
            targetCmd_800A8610.kind_0 = 10;
            targetSfx_800A84A4 = 0x71;
            SetAnnouncerXa_800A8078(0x16, 0x4DB, 0x18);
            announcerLines_800A85C0 = directHitLines_800A8344;
            break;
        case 5:
            targetCmd_800A8610.kind_0 = 0xC;
            targetSfx_800A84A4 = 0x70;
            SetAnnouncerXa_800A8078(0x1A, 0x4DA, 0x1E);
            announcerLines_800A85C0 = dodgeLines_800A8334;
            break;
        }
        if (u->hp_8.cur_0 <= hpDamage_800A8470[i] || (statusInflicted_800A85F0[i] & 0x400))
        {
            if (CountTeamMinions_800A1AAC(actorSide_800A85B8) == 3 && CountTeamMinions_800A1AAC(targetSide_800A8620) == 3 &&
                CountLivingMinions_800A7164(actorSide_800A85B8) == 1 && CountLivingMinions_800A7164(targetSide_800A8620) == 1)
            {
                SetAnnouncerXa_800A8078(0x17, 0x4E4, 0x23);
                announcerLines_800A85C0 = finalLines_800A8454.lines_0;
            }
            else if (!(combatFlags_800A3A88 & 2) && CountTeamMinions_800A1AAC(actorSide_800A85B8) == 3 && CountLivingMinions_800A7164(actorSide_800A85B8) >= 2 &&
                     CountLivingMinions_800A7164(targetSide_800A8620) == 1)
            {
                SetAnnouncerXa_800A8078(9, 0x4E4, 0x34);
                announcerLines_800A85C0 = lossLines_800A843C;
            }
            else if (u->hp_8.cur_0 == u->hp_8.max_2)
            {
                SetAnnouncerXa_800A8078(2, 0x4E2, 0x21);
                announcerLines_800A85C0 = oneBlowLines_800A8414;
            }
            else
            {
                SetAnnouncerXa_800A8078(0x1E, 0x4DF, 0x28);
                announcerLines_800A85C0 = koLines_800A83B0;
            }
            targetCmd_800A8610.kind_0 = 0xB;
            koSfx_800A84A6 = 0x6F;
            exchangeFlags_800A84A8 |= 1;
            koSide_800A8490 = targetSide_800A8620;
        }
        else if (hpDamage_800A8470[i] == u->hp_8.cur_0 - 1)
        {
            SetAnnouncerXa_800A8078(1, 0x4E3, 0x21);
            announcerLines_800A85C0 = oneHpLeftLines_800A8428;
        }
    }
    if (hpDamage_800A8470[actorSide_800A85B8] != 0)
    {
        if (mpDamage_800A8474[actorSide_800A85B8] != 0)
        {
            sideHitKind_800A85FC[actorSide_800A85B8] = 3;
        }
        else
        {
            sideHitKind_800A85FC[actorSide_800A85B8] = 1;
        }
    }
    else if (mpDamage_800A8474[actorSide_800A85B8] != 0)
    {
        sideHitKind_800A85FC[actorSide_800A85B8] = 2;
    }
    else
    {
        sideHitKind_800A85FC[actorSide_800A85B8] = 0;
    }
}

// hitWindow_800A8494: the merged window; lo counts the frames up to hi
// The exchange of the two sides' commands: runs both animations, lands the hits at the hit frame, then
// handles side KO / swap / counter. Steps fall through in one call while the step keeps changing.
void RunExchange_800A68E0(CombBtlTask* t)
{
    int prev = -1;
    UnitStatus* target;
    int flags;
    while (prev != exchangeStep_800A8488)
    {
        prev = exchangeStep_800A8488;
        switch (prev)
        {
        case 0:
            if (IsEffectTaskIdle_800148D4() == 1 && IsSlotActorIdle_800A0EE8(actorSide_800A85B8) == 1 &&
                IsSlotActorIdle_800A0EE8(targetSide_800A8620) == 1)
            {
                exchangeStep_800A8488 = 1;
            }
            break;
        case 1:
            sideHitWindows_800A84C8[actorSide_800A85B8] = StartSlotAction_800A0F50(actorSide_800A85B8, &actorCmd_800A85A8, 0);
            sideHitWindows_800A84C8[targetSide_800A8620] = StartSlotAction_800A0F50(targetSide_800A8620, &targetCmd_800A8610, 1);
            hitWindow_800A8494 = MergeHitWindows_800A71E4(2, sideHitWindows_800A84C8);
            exchangeStep_800A8488 = 2;
            break;
        case 2:
            if (IsSlotActorReady_800A0F1C(actorSide_800A85B8) && IsSlotActorReady_800A0F1C(targetSide_800A8620))
            {
                exchangeStep_800A8488 = 3;
                announcerTask_800A82DC = 0;
            }
            break;
        case 3:
            if (sideHitWindows_800A84C8[actorSide_800A85B8].a == hitWindow_800A8494.a)
            {
                TriggerSlotEffect_800A0FF0(actorSide_800A85B8, &actorCmd_800A85A8, 0);
                StartHitNumber_800A7E34(actorSide_800A85B8, 1, actorHpLoss_800A84BC);
                if (actorHpLoss_800A84BC > 0)
                {
                    StartCameraShake_80037BFC(0x1E);
                    PlaySfx_80031494(0x72);
                }
                StartHitNumber_800A7E34(actorSide_800A85B8, 2, actorMpLoss_800A84C4);
                if ((unsigned int)(actorCmd_800A85A8.kind_0 - 2) < 2)
                {
                    StartPadVibration_80036528(actorSide_800A85B8 ? player2Pad_800A38D8 : 0, 9);
                }
            }
            if (sideHitWindows_800A84C8[targetSide_800A8620].a == hitWindow_800A8494.a)
            {
                TriggerSlotEffect_800A0FF0(targetSide_800A8620, &targetCmd_800A8610, 1);
                if (targetSfx_800A84A4 >= 0)
                {
                    PlaySfx_80031494(targetSfx_800A84A4);
                }
                if (koSfx_800A84A6 >= 0)
                {
                    PlaySfx_80031494(koSfx_800A84A6);
                }
                if (newStageElement_800A84A0 != stageElement_800A8498)
                {
                    SetAreaElementLight_80039ED8((short)newStageElement_800A84A0);
                    stageElement_800A8498 = newStageElement_800A84A0;
                }
            }
            hitWindow_800A8494.a++;
            if (hitWindow_800A8494.b < hitWindow_800A8494.a)
            {
                exchangeStep_800A8488 = 4;
            }
            else if (hitWindow_800A8494.a == 0)
            {
                AdjustUnitStatById_800127D0(actorSide_800A85B8 + 8, 0x11, 0, statusCured_800A8480[actorSide_800A85B8]);
                AdjustUnitStatById_800127D0(targetSide_800A8620 + 8, 0x11, 0, statusCured_800A8480[targetSide_800A8620]);
                AdjustUnitStatById_800127D0(actorSide_800A85B8 + 8, 0x10, 0, statusInflicted_800A85F0[actorSide_800A85B8]);
                AdjustUnitStatById_800127D0(targetSide_800A8620 + 8, 0x10, 0, statusInflicted_800A85F0[targetSide_800A8620]);
                PlayHitFeedback_800A7C0C(actorSide_800A85B8);
                PlayHitFeedback_800A7C0C(targetSide_800A8620);
                SetSlotStatusTint_800A1068(actorSide_800A85B8);
                SetSlotStatusTint_800A1068(targetSide_800A8620);
                if (pendingXa_800A82E0[0] == 1 && !(exchangeFlags_800A84A8 & 0x10))
                {
                    pendingXa_800A82E0[0] = 0;
                    announcerTask_800A82DC = (CombBtlNode*)StartAnnouncer_800A8098(1, announcerLines_800A85C0, actorSide_800A85B8 == 1);
                }
            }
            break;
        case 4:
            if (announcerTask_800A82DC == 0 || (announcerTask_800A82DC->flags & 0x8001) != 1)
            {
                announcerTask_800A82DC = 0;
                prev = exchangeStep_800A8488 = 5;
            }
            break;
        case 5:
            if (exchangeFlags_800A84A8 & 1)
            {
                KillUnit_800127B8(GetMinionStatusOf_80033818(&teams_800A3AA0[koSide_800A8490][sideSlot_800A4078[koSide_800A8490]]));
                DestroySlotActor_800A0D1C(koSide_800A8490);
                FreeSlotModel_800A0B70(koSide_800A8490);
                exchangeStep_800A8488 = prev;
                t->next_8 = CheckBattleOver_800A4EC8;
                exchangeFlags_800A84A8 &= ~1;
            }
            else if (actorCmd_800A85A8.kind_0 == 3)
            {
                RemoveSideMinion_800A7560(actorSide_800A85B8);
                sideSlot_800A4078[actorSide_800A85B8] = swapSlot_800A85BC;
                StartSlotModel_800A0ACC(actorSide_800A85B8, &teams_800A3AA0[actorSide_800A85B8][swapSlot_800A85BC]);
                exchangeStep_800A8488 = 6;
                sideEntering_800A84B0[actorSide_800A85B8] = 1;
                sideGauges_800A84D0[actorSide_800A85B8] = 1000 - rand() % 200;
            }
            else if (exchangeFlags_800A84A8 & 2)
            {
                exchangeFlags_800A84A8 &= ~2;
                exchangeStep_800A8488 = prev;
                t->next_8 = LoadCommandMenu_800A5EB8;
            }
            else if (exchangeFlags_800A84A8 & 0x10)
            {
                exchangeFlags_800A84A8 &= ~0x10;
                exchangeStep_800A8488 = prev;
                t->next_8 = CheckBattleOver_800A4EC8;
            }
            else if (actorCmd_800A85A8.targets_C)
            {
                exchangeStep_800A8488 = 7;
            }
            else
            {
                exchangeStep_800A8488 = prev;
                t->next_8 = CheckBattleOver_800A4EC8;
            }
            break;
        case 6:
            if (AreSideModelsReady_800A758C() == 1)
            {
                CreateSideActor_800A74A0(actorSide_800A85B8);
                MoveSlotActorTo_800A0E1C(actorSide_800A85B8, (int)GetSlotPos_800A10DC(actorSide_800A85B8 ^ 1));
                exchangeStep_800A8488 = 0;
                actorCmd_800A85A8.kind_0 = 2;
                actorCmd_800A85A8.targets_C = 0;
                actorCmd_800A85A8.arg_4 = chosenCmd_800A8600.arg_4;
                actorCmd_800A85A8.mask_8 = 1 << (actorSide_800A85B8 + 8);
            }
            break;
        case 7:
            target = GetUnitStatus_80014390((unsigned char)((unsigned char)targetSide_800A8620 + 8));
            if (target->hp_8.cur_0 > 0 && ((result_800A85C8.status_8 & 0x18202) || (target->status_0 & 0x8000)))
            {
                ResetCommands_800A5BB4();
                result_800A85C8.kind_0 = 0;
                actorSide_800A85B8 ^= 1;
                targetSide_800A8620 ^= 1;
                exchangeFlags_800A84A8 |= 0x10;
                flags = target->status_0;
                if (flags & 0x200)
                {
                    actorCmd_800A85A8.kind_0 = 0x13;
                }
                else if (flags & 0x10000)
                {
                    actorCmd_800A85A8.kind_0 = 0xE;
                }
                else if (flags & 2)
                {
                    actorCmd_800A85A8.kind_0 = 0x10;
                }
                else if (flags & 0x8000)
                {
                    actorCmd_800A85A8.kind_0 = 0x12;
                }
                actorCmd_800A85A8.arg_4 = 0;
                actorCmd_800A85A8.targets_C = 0;
                exchangeStep_800A8488 = 0;
                actorCmd_800A85A8.mask_8 = 1 << (actorSide_800A85B8 + 8);
                ResolveCommand_800A616C();
                actorSlot_800A85BD = sideSlot_800A4078[actorSide_800A85B8];
            }
            else
            {
                exchangeStep_800A8488 = prev;
                t->next_8 = CheckBattleOver_800A4EC8;
            }
            break;
        }
    }
}

const CombBtlSidePos sideActorPos_800A4AD4 = { {
        { 0 },
        { 0, 0, 0x3E8 },
    } };
const CombBtlSideRot sideActorArgs_800A4AEC = { {
        { 0 },
        { 0, 0, 0, 8 },
    } };
const MenuWindowItem sideLabel0_800A4AFC = { 8, 1, 51, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 110, 20, 50, 20, 2, 4 };
const MenuWindowItem sideLabel1_800A4B18 = { 8, 1, 223, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 160, 20, 50, 20, 2, 4 };
const CombBtlPos2 statusIconPos_800A4B34 = { {
        { 10, 79 },
        { 0x136, 79 },
    } };
const MenuWindowItem slotItem_800A4B3C = { 8, 1, 0, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0, 0, 50, 20, 2, 4 };
const CombBtlPos2 slotItemPos_800A4B58 = { {
        { 110, 40 },
        { 160, 40 },
    } };
const CombBtlInt3 slotIcons_800A4B60 = { { 219, 115, 102 } };
const CombBtlPos2 mpGaugePos_800A4B6C = { {
        { 10, 59 },
        { 210, 59 },
    } };

unsigned int CountLivingMinions_800A7164(int side)
{
    int cnt = 0;
    int j;
    for (j = 0; j < 3; j++)
    {
        if (IsMinionFainted_800A1958(&teams_800A3AA0[side][j]) == 0)
        {
            cnt++;
        }
    }
    return cnt;
}

ShortPair MergeHitWindows_800A71E4(int count, ShortPair* windows)
{
    ShortPair merged;
    short hi = 0;
    short lo = hi;
    int i;
    for (i = 0; i < count; i++)
    {
        windows->b = windows->b - windows->a;
        windows->a = -windows->a;
        if (windows->a < lo)
        {
            lo = windows->a;
        }
        if (hi < windows->b)
        {
            hi = windows->b;
        }
        windows++;
    }
    merged.a = lo;
    merged.b = hi;
    return merged;
}

void StartArenaCamera_800A7290()
{
    EventEntry* e = AllocEventEntry_80043AF8(cameraTask_8008D4A0);
    CameraView* cam;
    SaveData* save;
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        ResetCameraToLevant_800376A8();
        StartBattleCamera_80037748();
        e->cb_8 = (EventEntryFn)InitCameraTask_800368F8;
        e->cb_C = FreeCameraTask_800376A0;
        e->flags = (e->flags | 4) & ~0x8000;
        cam = &cameraState_8008D4F0;
        cam->geomScreen_2E = 0;
        cam->lookAt_20.x = 0;
        cam->lookAt_20.y = 0;
        cam->lookAt_20.z = 0;
        cam->eye_14.x = 0;
        cam->eye_14.y = 0;
        cam->eye_14.z = 0;
        cam->lightDir_34.vx = 0;
        cam->lightDir_34.vy = 0;
        cam->lightDir_34.vz = 0;
        cam->lightColor_3C.vx = 0;
        cam->lightColor_3C.vy = 0;
        cam->lightColor_3C.vz = 0;
        cameraZoom_8008B4F8 = 0x1000;
        save = &saveData_8008B570;
        save->levant_7A8.pos.x = 0;
        save->levant_7A8.pos.y = 0;
        save->levant_7A8.pos.z = 0;
        save->levant_7A8.rot.vx = 0;
        save->levant_7A8.rot.vy = 0;
        save->levant_7A8.rot.vz = 0;
        cam->lightDir_34.vx = defaultLightMatrix_8007C2EC.m[0][0];
        cam->lightDir_34.vy = defaultLightMatrix_8007C2EC.m[0][1];
        cam->lightDir_34.vz = defaultLightMatrix_8007C2EC.m[0][2];
        cam->lightColor_3C.vx = defaultColorMatrix_8007C30C.m[0][0];
        cam->lightColor_3C.vy = defaultColorMatrix_8007C30C.m[1][0];
        cam->lightColor_3C.vz = defaultColorMatrix_8007C30C.m[2][0];
        lightMatrix_80087114.m[0][0] = defaultLightMatrix_8007C2EC.m[0][0];
        lightMatrix_80087114.m[0][1] = defaultLightMatrix_8007C2EC.m[0][1];
        lightMatrix_80087114.m[0][2] = defaultLightMatrix_8007C2EC.m[0][2];
        colorMatrix_80087134.m[0][0] = defaultColorMatrix_8007C30C.m[0][0];
        colorMatrix_80087134.m[1][0] = defaultColorMatrix_8007C30C.m[1][0];
        colorMatrix_80087134.m[2][0] = defaultColorMatrix_8007C30C.m[2][0];
    }
}

void StopArenaCamera_800A73E4()
{
    FreeCameraTask_800376A0(&cameraTask_8008D4A0->entry, cameraTask_8008D4A0->entry.buffer);
    StopAllEventEntries_80043B40(cameraTask_8008D4A0);
}

void StartFadeTask_800A7420()
{
    EventEntry* e = AllocEventEntry_80043AF8(fadeTask_8008D628);
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        InitSceneFade_8001A38C();
        e->cb_8 = (EventEntryFn)SceneFadeTask_8001A41C;
    }
}

void StopFadeTask_800A7478()
{
    StopAllEventEntries_80043B40(fadeTask_8008D628);
}

void CreateSideActor_800A74A0(int side)
{
    CombBtlSidePos pos = sideActorPos_800A4AD4;
    CombBtlSideRot rot = sideActorArgs_800A4AEC;
    CreateSlotActor_800A0BA8(side, pos.pos_0[side], rot.rot_0[side]);
}

void RemoveSideMinion_800A7560(int side)
{
    DestroySlotActor_800A0D1C(side);
    FreeSlotModel_800A0B70(side);
}

int AreSideModelsReady_800A758C()
{
    unsigned int i;
    for (i = 0; i < 2; i++)
    {
        if (sideEntering_800A84B0[i])
        {
            if (RunSlotModelTask_800A0B3C(i) == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

void OpenSideWindow_800A75F8(int side)
{
    EventEntry* e = AllocEventEntry_80043AF8(enemyWindowTasks_8008B564);
    CombBtlSideWindow* win;
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        win = (CombBtlSideWindow*)e->buffer;
        win->side_0 = side;
        win->frame_4 = 0;
        win->dst_8.x = sideWindowPos_800A82D4[side][0];
        win->dst_8.y = sideWindowPos_800A82D4[side][1];
        win->dst_8.w = 0x64;
        win->dst_8.h = 0x29;
        e->cb_8 = (EventEntryFn)SideWindowTask_800A7694;
    }
}

void SideWindowTask_800A7694(EventEntry* e, void* buf)
{
    MenuWindowItem w0 = sideLabel0_800A4AFC;
    MenuWindowItem w1 = sideLabel1_800A4B18;
    WindowStyle box60;
    CombBtlPair pt;
    CombBtlPos2 pos70 = statusIconPos_800A4B34;
    WindowStyle box78;
    MenuWindowItem w2;
    union
    {
        CombBtlPos2 pos;
        WindowStyle box;
    } uA0;
    union
    {
        CombBtlInt3 v;
        RECT r;
    } uA8;
    CombBtlPos2 posB8;
    int sel = 0;
    UnitStatus* status;
    MenuWindowItem* label;
    CombBtlSideWindow* win;

    if (exchangeFlags_800A84A8 & 0xC)
    {
        return;
    }
    win = buf;
    if (win->side_0 == actorSide_800A85B8)
    {
        status = GetMinionStatusOf_80033818(&teams_800A3AA0[win->side_0][actorSlot_800A85BD]);
    }
    else
    {
        status = GetMinionStatusOf_80033818(&teams_800A3AA0[win->side_0][sideSlot_800A4078[win->side_0]]);
    }
    AddClipDrawAreaPrim_80033308(pOT_8008D454);
    SetFontClutOffset_8003F900(1, 0);
    InterpolateWindowRect_8004196C(&win->cur_10, &win->dst_8, win->frame_4, 4, 9);
    if (loserSide_800A85F8 >= 0 && loserSide_800A85F8 != win->side_0)
    {
        sel = 1;
    }
    if (win->side_0 == actorSide_800A85B8)
    {
        DrawUnitStatusWindow_8002F1C8(status, previewHp_800A82D0, sel, GetTime30Hz_8002C64C(), &win->cur_10, 10, 0);
    }
    else
    {
        DrawUnitStatusWindow_8002F1C8(status, 0, sel, GetTime30Hz_8002C64C(), &win->cur_10, 10, 0);
    }
    win->frame_4++;
    AddDrawAreaPrim_8003326C(&win->cur_10, pOT_8008D454);
    pt.lo = pos70.p[win->side_0].lo;
    pt.hi = pos70.p[win->side_0].hi;
    DrawMenuWindowItems_8002F480(status, &pt, 0xF, win->side_0);
    if (win->side_0)
    {
        label = &w1;
    }
    else
    {
        label = &w0;
    }
    if (loserSide_800A85F8 < 0)
    {
        if (win->side_0 == actorSide_800A85B8)
        {
            box60.colorSet_2 = 1;
        }
        else
        {
            box60.colorSet_2 = 0;
        }
    }
    else if (win->side_0 == loserSide_800A85F8)
    {
        box60.colorSet_2 = 0;
    }
    else
    {
        box60.colorSet_2 = 1;
    }
    box60.semiTrans_3 = 1;
    box60.color_0 = saveData_8008B570.uiColor_20.h;
    DrawMenuItemWithWindow_8002ADB4(label, &box60, 0xF, GetTime30Hz_8002C64C());
    w2 = slotItem_800A4B3C;
    uA0.pos = slotItemPos_800A4B58;
    uA8.v = slotIcons_800A4B60;
    w2.text_4 = uA8.v.v[sideSlot_800A4078[win->side_0]];
    w2.x_10 = uA0.pos.p[win->side_0].lo;
    w2.y_12 = uA0.pos.p[win->side_0].hi;
    box78.colorSet_2 = 0;
    box78.semiTrans_3 = 1;
    box78.color_0 = saveData_8008B570.uiColor_20.h;
    DrawMenuItemWithWindow_8002ADB4(&w2, &box78, 0xF, 0);
    posB8 = mpGaugePos_800A4B6C;
    pt.lo = posB8.p[win->side_0].lo;
    pt.hi = posB8.p[win->side_0].hi;
    uA8.r.w = 0x64;
    uA8.r.h = 0x14;
    uA8.r.x = pt.lo;
    uA8.r.y = pt.hi;
    if (win->side_0 == actorSide_800A85B8)
    {
        DrawMpGauge_8002F120(status, &pt, previewMp_800A82D2, 0xF);
    }
    else
    {
        DrawMpGauge_8002F120(status, &pt, 0, 0xF);
    }
    uA0.box.semiTrans_3 = 1;
    uA0.box.color_0 = saveData_8008B570.uiColor_20.h;
    uA0.box.colorSet_2 = 0;
    DrawWindow_80042460(&uA8.r, &uA0.box, &pOT_8008D454[0xF], 0);
    AddClipDrawAreaPrim_80033308(pOT_8008D454);
}

void CloseSideWindows_800A7BE4()
{
    StopAllEventEntries_80043B40(enemyWindowTasks_8008B564);
}

void PlayHitFeedback_800A7C0C(int side)
{
    int me;
    int other;
    if (side == 0)
    {
        other = player2Pad_800A38D8;
        me = 0;
    }
    else
    {
        me = player2Pad_800A38D8;
        other = 0;
    }
    switch (result_800A85C8.kind_0)
    {
    case 0:
        break;
    case 1:
        StartHitNumber_800A7E34(side, result_800A85C8.kind_0, hpDamage_800A8470[side]);
        if (hpDamage_800A8470[side] > 0)
        {
            StartCameraShake_80037BFC(0x1E);
            StartPadVibration_80036528(me, 0);
            StartPadVibration_80036528(other, 2);
        }
        break;
    case 2:
        StartHitNumber_800A7E34(side, result_800A85C8.kind_0, mpDamage_800A8474[side]);
        if (mpDamage_800A8474[side] > 0)
        {
            StartCameraShake_80037BFC(0x1E);
            StartPadVibration_80036528(side ? player2Pad_800A38D8 : 0, 0);
        }
        break;
    case 3:
        StartHitNumber_800A7E34(side, 1, hpDamage_800A8470[side]);
        StartHitNumber_800A7E34(side, 2, mpDamage_800A8474[side]);
        if (hpDamage_800A8470[side] > 0 || mpDamage_800A8474[side] > 0)
        {
            StartCameraShake_80037BFC(0x1E);
            StartPadVibration_80036528(side ? player2Pad_800A38D8 : 0, 0);
        }
        break;
    case 4:
        StartHitNumber_800A7E34(side, 1, hpDamage_800A8470[side]);
        StartCameraShake_80037BFC(0x1E);
        StartPadVibration_80036528(side ? player2Pad_800A38D8 : 0, 1);
        FlashScreenWhite_800A7ECC();
        break;
    case 5:
        StartPadVibration_80036528(0, 0x26);
        break;
    }
}

void StartHitNumber_800A7E34(int side, int kind, int amount)
{
    EventEntry* e = AllocEventEntry_80043AF8(hitNumberTasks_8008D778);
    CombBtlHitNum* num;
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        num = e->buffer;
        num->kind_0 = kind;
        num->frame_8 = 0;
        num->amount_4 = amount;
        num->side_18 = side;
        num->pos_10 = GetSlotPos_800A10DC(side);
        e->cb_8 = (EventEntryFn)HitNumberTask_800A7EFC;
    }
}

void FlashScreenWhite_800A7ECC()
{
    unsigned char rgb[3];
    rgb[0] = 0xFF;
    rgb[1] = 0xFF;
    rgb[2] = 0xFF;
    StartScreenFlash_8001C02C(rgb);
}

void HitNumberTask_800A7EFC(EventEntry* e, CombBtlHitNum* buf)
{
    CombBtlHitNum* num = buf;
    DVECTOR sxy;
    SVECTOR pos;
    long z;
    long flag;
    int step;
    pos.vx = buf->pos_10[0];
    pos.vy = buf->pos_10[1];
    pos.vz = buf->pos_10[2];
    pos.vx -= cameraEye_8008D600.vx;
    pos.vy -= cameraEye_8008D600.vy;
    pos.vz -= cameraEye_8008D600.vz;
    RotTransPers(&pos, (long*)&sxy, &z, &flag);
    if (++num->frame_8 > 16)
    {
        e->flags = (e->flags & ~1) | 0x8000;
        return;
    }
    step = num->amount_4 / (17 - num->frame_8);
    step = -step;
    num->amount_4 += step;
    if (num->kind_0 == 1)
    {
        UnitStatus* status = GetUnitStatus_80014390((unsigned char)(num->side_18 + 8));
        AdjustUnitStatById_800127D0(num->side_18 + 8, 0, step, 0);
        if (status->hp_8.cur_0 <= 0)
        {
            KillUnit_800127B8(GetUnitStatus_80014390((unsigned char)(num->side_18 + 8)));
        }
    }
    else if (num->kind_0 == 2)
    {
        AdjustUnitStatById_800127D0(num->side_18 + 8, 2, step, 0);
    }
}

void SetAnnouncerXa_800A8078(short channel, short startSector, short length)
{
    pendingXa_800A82E0[0] = 1;
    pendingXa_800A82E0[1] = channel;
    pendingXa_800A82E0[2] = startSector;
    pendingXa_800A82E0[3] = length;
}

int StartAnnouncer_800A8098(int which, int lines, int side)
{
    EventEntry* e = AllocEventEntry_80043AF8(announcerTasks_8008D458);
    if (e)
    {
        e->cb_8 = (EventEntryFn)AnnouncerTask_800A816C;
        e->flags = (e->flags | 1) & ~0x8000;
        XaRequestPlay_80043564(pendingXa_800A82E0[1], pendingXa_800A82E0[2], pendingXa_800A82E0[3]);
        announcerWindow_800A8478 = OpenAnnouncerWindow_800A5408(which, lines, side);
        combatFlags_800A3A88 &= ~4;
        combatFlags_800A3A88 &= ~8;
        combatFlags_800A3A88 &= ~0x10;
    }
    return (int)e;
}

void AnnouncerTask_800A816C(EventEntry* e)
{
    MsgResult buf;
    int v;
    if (!(combatFlags_800A3A88 & 4))
    {
        if (GetMsgWindowResultIfDone_800349B4(announcerWindow_800A8478, &buf) && buf.field_24)
        {
            combatFlags_800A3A88 |= 4;
        }
    }
    v = XaNoRequestPending_800435A4();
    if (v == 1 && XaIsIdle_80043584() == v)
    {
        combatFlags_800A3A88 |= 8;
    }
    if (!(combatFlags_800A3A88 & 8))
    {
        v = (saveData_8008B570.settings_1C.word >> 3) & 1;
        if (v == 1 && (combatFlags_800A3A88 & 4))
        {
            if (!(combatFlags_800A3A88 & 0x10))
            {
                if (XaRequestStop_80043524() == v)
                {
                    combatFlags_800A3A88 |= 0x10;
                }
            }
        }
    }
    if ((combatFlags_800A3A88 & 0xC) == 0xC)
    {
        combatFlags_800A3A88 &= ~4;
        combatFlags_800A3A88 &= ~8;
        combatFlags_800A3A88 &= ~0x10;
        CloseMsgWindow_80034A84(announcerWindow_800A8478);
        e->flags = (e->flags & ~1) | 0x8000;
    }
}
