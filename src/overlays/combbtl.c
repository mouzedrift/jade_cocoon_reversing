// COMBBTL.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "camera.h"
#include "combbtl.h"



// a battle command (same layout as BATTLE.BIN's BatCmd_a)
extern EventNode* dword_8008B564;
extern int dword_800A4078[2];
extern unsigned char byte_800A3A98[2];
extern void DestroySlotActor_800A0D1C(int);
extern void FreeSlotModel_800A0B70(int);
extern void StartScreenFlash_8001C02C(void*);
extern void sub_800376A0(void* a, void* b);

extern Minion teams_800A3AA0[2][3];
extern EventNode* hitNumberTasks_8008D778;
extern void InitSceneFade_8001A38C();
extern void SceneFadeTask_8001A41C();
extern int sub_800A1958(void*);
extern int* GetSlotPos_800A10DC(int); // COMBAT: the slot actor pos_38
extern void HitNumberTask_800A7EFC();

extern void SideWindowTask_800A7694();
extern void CreateSlotActor_800A0BA8(int, void*, void*);
// a command's result (same layout as BATTLE.BIN's BatResult_a)
extern int actorSideArr_800A85B8[];
extern int targetSideArr_800A8620[];
extern unsigned char battleResult_800A38DC;
extern void CombBtlWaitFile_800A4C40();
extern void CombBtlSetup_800A4D48();
extern void RunExchange_800A68E0();
extern void ResolveCommand_800A616C();
extern void PlayVictoryJingle_800A5000();
extern void SetBattleStageId_80039FA4(int);
extern void InitCombatSlots_800A0A28();
extern int PlayMusic_800300E0(int, int);
extern void OpenCommandMenu_800A5EF8();
extern void WaitCommandMenu_800A5F60();
extern void RecordBattleResult_800A50E4();
extern void CombBtlExit_800A5544();
extern void ResetCommands_800A5BB4();
extern void WaitVictoryJingle_800A5080();
extern short word_80091CE0[];
extern char dword_80091D40[];
extern EventEntry* CombComStart_800CB7AC(void*, int);
extern int RunSlotModelTask_800A0B3C(int);
extern void StopSeqSlot_80031334(int);
extern void StopSoundSeqs_80030D68(int);
extern void FreeSeqSlotSound_80030664();
extern void SsSepSetDecrescendo(int, int, int, int);
extern void StartSceneFadeOut_8001AA50(int);
extern void PlaySeqSlot_80031160(int, int);

int dword_800A4088 SDATA = 22;
const char aAreVictorious_800A408C[] = "\202\201\202\222\202\205\201@\202\226\202\211\202\203\202\224\202\217\202\222\202\211\202\217\202\225\202\223\201I"; // are victorious!
const char aTheMinionsOfThe_800A40AC[] = "\202s\202\210\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\202\223\201@\202\217\202\206\201@\202\224\202\210\202\205\201@\202c\202\201\202\227\202\216"; // The Minions of the Dawn
const char aCongratulations_800A40DC[] = "\202b\202\217\202\216\202\207\202\222\202\201\202\224\202\225\202\214\202\201\202\224\202\211\202\217\202\216\202\223\201I"; // Congratulations!
const char aTheMinionsOfThe_800A4100[] = "\202s\202\210\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\202\223\201@\202\217\202\206\201@\202\224\202\210\202\205\201@\202r\202\225\202\216\202\223\202\205\202\224"; // The Minions of the Sunset
const char aEachOtherSMoves_800A4134[] = "\202\205\202\201\202\203\202\210\201@\202\217\202\224\202\210\202\205\202\222\201f\202\223\201@\202\215\202\217\202\226\202\205\202\223\201D"; // each other's moves.
const char aItSeemsYouAreGa_800A415C[] = "\202h\202\224\201@\202\223\202\205\202\205\202\215\202\223\201@\202\231\202\217\202\225\201@\202\201\202\222\202\205\201@\202\207\202\201\202\225\202\207\202\211\202\216\202\207"; // It seems you are gauging
const char aThisThrillingBa_800A4190[] = "\202\224\202\210\202\211\202\223\201@\202\224\202\210\202\222\202\211\202\214\202\214\202\211\202\216\202\207\201@\202\202\202\201\202\224\202\224\202\214\202\205\201I"; // this thrilling battle!
const char aICannotTakeMyEy_800A41C0[] = "\202h\201@\202\203\202\201\202\216\202\216\202\217\202\224\201@\202\224\202\201\202\213\202\205\201@\202\215\202\231\201@\202\205\202\231\202\205\202\223\201@\202\217\202\206\202\206"; // I cannot take my eyes off
const char aNoDamageTaken_800A41F4[] = "\202m\202\217\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\224\202\201\202\213\202\205\202\216\201D"; // No damage taken.
const char aOhMyItDodgedThe_800A4218[] = "\202n\202\210\201@\202\215\202\231\201C\201@\202\211\202\224\201@\202\204\202\217\202\204\202\207\202\205\202\204\201@\202\224\202\210\202\205\201@\202\202\202\214\202\217\202\227\201I"; // Oh my, it dodged the blow!
const char aOhThatHadToHurt_800A4250[] = "\202n\202\210\201C\201@\202\224\202\210\202\201\202\224\201@\202\210\202\201\202\204\201@\202\224\202\217\201@\202\210\202\225\202\222\202\224\201I"; // Oh, that had to hurt!
const char aADirectHit_800A427C[] = "\202`\201@\202\204\202\211\202\222\202\205\202\203\202\224\201@\202\210\202\211\202\224\201I"; // A direct hit!
const char aTheMinionLooksD_800A4298[] = "\202s\202\210\202\205\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\214\202\217\202\217\202\213\202\223\201@\202\204\202\211\202\232\202\232\202\231\201D"; // The minion looks dizzy.
const char aPoison_800A42C8[] = "\202o\202\217\202\211\202\223\202\217\202\216\201I"; // Poison!
const char aOnAChoppingBloc_800A42D8[] = "\202\217\202\216\201@\202\201\201@\202\203\202\210\202\217\202\220\202\220\202\211\202\216\202\207\201@\202\202\202\214\202\217\202\203\202\213\201I"; // on a chopping block!
const char aItIsLikeAHelple_800A4304[] = "\202h\202\224\201@\202\211\202\223\201@\202\214\202\211\202\213\202\205\201@\202\201\201@\202\210\202\205\202\214\202\220\202\214\202\205\202\223\202\223\201@\202\206\202\211\202\223\202\210"; // It is like a helpless fish
const char aThisCouldBeDang_800A433C[] = "\202s\202\210\202\211\202\223\201@\202\203\202\217\202\225\202\214\202\204\201@\202\202\202\205\201@\202\204\202\201\202\216\202\207\202\205\202\222\202\217\202\225\202\223\201D"; // This could be dangerous.
const char aOhNoItIsFalling_800A4370[] = "\202n\202\210\201@\202\216\202\217\201C\201@\202\211\202\224\201@\202\211\202\223\201@\202\206\202\201\202\214\202\214\202\211\202\216\202\207\201@\202\201\202\223\202\214\202\205\202\205\202\220\201I"; // Oh no, it is falling asleep!
const char aNotHealed_800A43AC[] = "\202\216\202\217\202\224\201@\202\210\202\205\202\201\202\214\202\205\202\204\201I"; // not healed!
const char aThisCouldBeFata_800A43C4[] = "\202s\202\210\202\211\202\223\201@\202\203\202\217\202\225\202\214\202\204\201@\202\202\202\205\201@\202\206\202\201\202\224\202\201\202\214\201@\202\211\202\206\201@\202\211\202\224\201@\202\211\202\223"; // This could be fatal if it is
const char aStoneItIsSpread_800A4400[] = "\202\223\202\224\202\217\202\216\202\205\201I\201@\202h\202\224\201@\202\211\202\223\201@\202\223\202\220\202\222\202\205\202\201\202\204\202\211\202\216\202\207\201@\202\206\202\201\202\223\202\224\201D"; // stone! It is spreading fast.
const char aTheMinionIsBein_800A443C[] = "\202s\202\210\202\205\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\211\202\223\201@\202\202\202\205\202\211\202\216\202\207\201@\202\224\202\225\202\222\202\216\202\205\202\204\201@\202\211\202\216\202\224\202\217"; // The minion is being turned into
const char aTheMinionIsGrav_800A447C[] = "\202s\202\210\202\205\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\211\202\223\201@\202\207\202\222\202\201\202\226\202\205\202\214\202\231\201@\202\227\202\217\202\225\202\216\202\204\202\205\202\204\201D"; // The minion is gravely wounded.
const char aCouldKeelOverAt_800A44BC[] = "\202\203\202\217\202\225\202\214\202\204\201@\202\213\202\205\202\205\202\214\201@\202\217\202\226\202\205\202\222\201@\202\201\202\224\201@\202\201\202\216\202\231\202\224\202\211\202\215\202\205\201D"; // could keel over at anytime.
const char aItIsBreathingHe_800A44F4[] = "\202h\202\224\201@\202\211\202\223\201@\202\202\202\222\202\205\202\201\202\224\202\210\202\211\202\216\202\207\201@\202\210\202\205\202\201\202\226\202\211\202\214\202\231\201@\202\201\202\216\202\204"; // It is breathing heavily and
const char aItHasFallenAndC_800A452C[] = "\202h\202\224\201@\202\210\202\201\202\223\201@\202\206\202\201\202\214\202\214\202\205\202\216\201@\202\201\202\216\202\204\201@\202\203\202\201\202\216\202\216\202\217\202\224\201@\202\207\202\205\202\224\201@\202\225\202\220\201I"; // It has fallen and cannot get up!
const char aForThisMinion_800A4570[] = "\202\206\202\217\202\222\201@\202\224\202\210\202\211\202\223\201@\202\215\202\211\202\216\202\211\202\217\202\216\201D"; // for this minion.
const char aItLooksLikeThat_800A4594[] = "\202h\202\224\201@\202\214\202\217\202\217\202\213\202\223\201@\202\214\202\211\202\213\202\205\201@\202\224\202\210\202\201\202\224\201@\202\211\202\223\201@\202\211\202\224"; // It looks like that is it
const char aIsTheFightOver_800A45C8[] = "\202h\202\223\201@\202\224\202\210\202\205\201@\202\206\202\211\202\207\202\210\202\224\201@\202\217\202\226\202\205\202\222\201H"; // Is the fight over?
const int dword_800A45F0 = 0;
const char aVeryEffective_800A45F4[] = "\202u\202\205\202\222\202\231\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\201D"; // Very effective.
const char aRightAtTheEleme_800A4614[] = "\202q\202\211\202\207\202\210\202\224\201@\202\201\202\224\201@\202\224\202\210\202\205\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\202\201\202\214\201@\202\227\202\205\202\201\202\213\201@\202\223\202\220\202\217\202\224\201D"; // Right at the elemental weak spot.
const char aWhatAWellChosen_800A4658[] = "\202v\202\210\202\201\202\224\201@\202\201\201@\202\227\202\205\202\214\202\214\201|\202\203\202\210\202\217\202\223\202\205\202\216\201@\202\201\202\224\202\224\202\201\202\203\202\213\201I"; // What a well-chosen attack!
const char aEnteredTheArena_800A4690[] = "\202\205\202\216\202\224\202\205\202\222\202\205\202\204\201@\202\224\202\210\202\205\201@\202\201\202\222\202\205\202\216\202\201\201I"; // entered the arena!
const char aANewMinionHas_800A46B8[] = "\202`\201@\202\216\202\205\202\227\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\210\202\201\202\223"; // A new minion has
const char aThePlayerHasSwi_800A46DC[] = "\202s\202\210\202\205\201@\202\220\202\214\202\201\202\231\202\205\202\222\201@\202\210\202\201\202\223\201@\202\223\202\227\202\211\202\224\202\203\202\210\202\205\202\204\201@\202\215\202\211\202\216\202\211\202\217\202\216\202\223\201I"; // The player has switched minions!
const char aWhatWillHappenN_800A4720[] = "\202v\202\210\202\201\202\224\201@\202\227\202\211\202\214\202\214\201@\202\210\202\201\202\220\202\220\202\205\202\216\201@\202\216\202\217\202\227\201I\201H"; // What will happen now!?
const char aWhatAnExcitingM_800A4750[] = "\202v\202\210\202\201\202\224\201@\202\201\202\216\201@\202\205\202\230\202\203\202\211\202\224\202\211\202\216\202\207\201@\202\215\202\217\202\226\202\205\201D"; // What an exciting move.
const char aAChangeOfElemen_800A4780[] = "\202`\201@\202\203\202\210\202\201\202\216\202\207\202\205\201@\202\217\202\206\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\202\201\202\214\201@\202\220\202\222\202\217\202\220\202\205\202\222\202\224\202\211\202\205\202\223\201I"; // A change of elemental properties!
const char aWithOneFatalBlo_800A47C4[] = "\202\227\202\211\202\224\202\210\201@\202\217\202\216\202\205\201@\202\206\202\201\202\224\202\201\202\214\201@\202\202\202\214\202\217\202\227\201I"; // with one fatal blow!
const char aTheMinionHasFal_800A47F0[] = "\202s\202\210\202\205\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\210\202\201\202\223\201@\202\206\202\201\202\214\202\214\202\205\202\216"; // The minion has fallen
const char aSuchOverwhelmin_800A481C[] = "\202r\202\225\202\203\202\210\201@\202\217\202\226\202\205\202\222\202\227\202\210\202\205\202\214\202\215\202\211\202\216\202\207\201@\202\220\202\217\202\227\202\205\202\222\201I"; // Such overwhelming power!
const char aItCouldBeVictor_800A4850[] = "\202\211\202\224\201@\202\203\202\217\202\225\202\214\202\204\201@\202\202\202\205\201@\202\226\202\211\202\203\202\224\202\217\202\222\202\231\201I"; // it could be victory!
const char aAgainstAllOdds_800A487C[] = "\202`\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\201\202\214\202\214\201@\202\217\202\204\202\204\202\223\201C"; // Against all odds,
const char aWhatAmazingWill_800A48A0[] = "\202v\202\210\202\201\202\224\201@\202\201\202\215\202\201\202\232\202\211\202\216\202\207\201@\202\227\202\211\202\214\202\214\202\220\202\217\202\227\202\205\202\222\201I"; // What amazing willpower!
const char aIWasEvenRooting_800A48D0[] = "\202h\201@\202\227\202\201\202\223\201@\202\205\202\226\202\205\202\216\201@\202\222\202\217\202\217\202\224\202\211\202\216\202\207\201@\202\206\202\217\202\222\201@\202\231\202\217\202\225\201I"; // I was even rooting for you!
const char aTooBad_800A4908[] = "\202s\202\217\202\217\201@\202\202\202\201\202\204\201I"; // Too bad!
const char aDecidedBeforeTh_800A491C[] = "\202\204\202\205\202\203\202\211\202\204\202\205\202\204\201@\202\202\202\205\202\206\202\217\202\222\202\205\201@\202\224\202\210\202\205\201@\202\224\202\210\202\211\202\222\202\204\201@\202\222\202\217\202\225\202\216\202\204\201D"; // decided before the third round.
const char aAnotherLossTheF_800A495C[] = "\202`\202\216\202\217\202\224\202\210\202\205\202\222\201@\202\214\202\217\202\223\202\223\201I\201@\202s\202\210\202\205\201@\202\206\202\211\202\207\202\210\202\224\201@\202\210\202\201\202\223\201@\202\202\202\205\202\205\202\216"; // Another loss! The fight has been
const char aWellDone_800A49A0[] = "\202v\202\205\202\214\202\214\201@\202\204\202\217\202\216\202\205\201I"; // Well done!
const char aReached_800A49B8[] = "\202\222\202\205\202\201\202\203\202\210\202\205\202\204\201D"; // reached.
const char aFinallyADecisio_800A49CC[] = "\202e\202\211\202\216\202\201\202\214\202\214\202\231\201@\202\201\201@\202\204\202\205\202\203\202\211\202\223\202\211\202\217\202\216\201@\202\210\202\201\202\223\201@\202\202\202\205\202\205\202\216"; // Finally a decision has been
const char aWhatACloseFight_800A4A04[] = "\202v\202\210\202\201\202\224\201@\202\201\201@\202\203\202\214\202\217\202\223\202\205\201@\202\206\202\211\202\207\202\210\202\224\201I"; // What a close fight!

void CombBtlStart_800A4B8C(CombBtlTask* t, int a)
{
    fileRequest_800A85A0 = LoadOverlay_80020BF8(1, 6);
    stageId_800A84C0 = (unsigned int)gnFrame_8008D610 % 39;
    t->next_8 = CombBtlWaitFile_800A4C40;
    t->next_8(t, a);
    StopSoundSeqs_80030D68((int)word_80091CE0);
    PlayMusic_800300E0(0, 1);
}

void CombBtlWaitFile_800A4C40(CombBtlTask* t, int a)
{
    if (GetFileRequestStatus_8003BE30(fileRequest_800A85A0) == 0)
    {
        newStageElement_800A84A0 = -1;
        stageElement_800A8498 = -1;
        dword_800A849C = -1;
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
        dword_800A4078[i] = -1;
        byte_800A3A98[i] = 0;
        sideGauges_800A84D0[i] = 0;
    }
}

extern int LoadSeqSlotSound_800303E8();
extern int IsSoundTaskReady_80030688();
extern int AreStageEffectsLoaded_800BC8E8();
extern void LoadStageEffects_800BC878();
extern void SetCameraBattleMode_80037720();
extern void StartBattleCamera_80037748();
extern void SetFadeMode_8001C19C();
extern void LoadUiTiy_8002BF74();
extern int uiTiyLoaded_8008B4E8;
extern int subInt_800378F8();
extern void StartArenaCamera_800A7290();
extern void StartFadeTask_800A7420();
extern void CheckBattleOver_800A4EC8();

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
        if (subInt_800378F8() != 4)
        {
            t->next_8 = CheckBattleOver_800A4EC8;
            t->next_8(t, a);
        }
        break;
    }
}
INCLUDE_OVERLAY_ASM(combbtl, winnerBanner_800A4A54);
INCLUDE_OVERLAY_ASM(combbtl, resultBanner_800A4A70);
INCLUDE_OVERLAY_ASM(combbtl, aRa_800A4A8C);
INCLUDE_OVERLAY_ASM(combbtl, aMu_800A4A94);
INCLUDE_OVERLAY_ASM(combbtl, dword_800A4A9C);
extern void SendInMinions_800A5638();

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
            if (IsMinionSlotEmpty_800A1934(&teams_800A3AA0[i][j]) == 0 && sub_800A1958(&teams_800A3AA0[i][j]) == 0)
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
    if (word_80091CE0[2] >= 0)
    {
        SsSepSetDecrescendo(word_80091CE0[6], word_80091CE0[2], 0x7F, 0x78);
        word_80091CE0[2] = -1;
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
        StopSoundSeqs_80030D68(dword_80091D40);
        FreeSeqSlotSound_80030664();
        t->next_8 = RecordBattleResult_800A50E4;
    }
}

extern unsigned char byte_800A3A90[];
extern void CombBtlEnd_800A54CC();
extern void AnnounceWinner_800A51EC();
void RecordBattleResult_800A50E4(CombBtlTask* t)
{
    int r = IsEffectTaskIdle_800148D4();
    if (r == 1)
    {
        if (loserSide_800A85F8 < 0)
        {
            if (battleResult_800A38DC == r)
            {
                loserSide_800A85F8 = actorSide_800A85B8;
                byte_800A3A90[actorSide_800A85B8]++;
                if (byte_800A3A90[actorSide_800A85B8] >= 100)
                {
                    byte_800A3A90[actorSide_800A85B8] = 99;
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
            byte_800A3A98[loserSide_800A85F8] = r;
            byte_800A3A90[loserSide_800A85F8]++;
            if (byte_800A3A90[loserSide_800A85F8] >= 100)
            {
                byte_800A3A90[loserSide_800A85F8] = 99;
            }
        }
        t->next_8 = AnnounceWinner_800A51EC;
        waitTimer_800A84D4 = 0x1E;
    }
}

extern void SetAnnouncerXa_800A8078(short, short, short);
extern int StartAnnouncer_800A8098();
extern void DrawWinnerBanner_800A5290();
extern void CombBtlEnd_800A54CC();

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


extern CombBtlItem winnerBanner_800A4A54;
extern CombBtlItem resultBanner_800A4A70;
extern void DrawMenuItemWithWindow_8002ADB4(void*, void*, int, int);

void DrawWinnerBanner_800A5290(CombBtlTask* t)
{
    CombBtlBox box;
    CombBtlItem a = winnerBanner_800A4A54;
    int pair[2];
    CombBtlItem b;
    pair[0] = 0x33;
    pair[1] = 0xDF;
    a.icon_4 = pair[loserSide_800A85F8 ^ 1];
    box.state_2 = 1;
    box.frame_3 = 1;
    box.color_0 = saveData_8008B570.uiColor_20.h;
    DrawMenuItemWithWindow_8002ADB4(&a, &box, 0xF, GetTime30Hz_8002C64C());
    b = resultBanner_800A4A70;
    box.state_2 = 1;
    box.frame_3 = 1;
    box.color_0 = saveData_8008B570.uiColor_20.h;
    DrawMenuItemWithWindow_8002ADB4(&b, &box, 0xF, GetTime30Hz_8002C64C());
    if (announcerTask_800A82DC == 0 || (announcerTask_800A82DC->flags & 0x8001) != 1)
    {
        announcerTask_800A82DC = 0;
        t->next_8 = CombBtlEnd_800A54CC;
    }
}

extern int dword_800A4A8C[];
extern int dword_800A4A94[];
// Matched
int OpenAnnouncerWindow_800A5408(int which, int lines, int side)
{
    int cfg[18];
    int kinds[2] = {2, 3};
    int* tbl[2] = {dword_800A4A8C, dword_800A4A94};
    cfg[0] = 2;
    cfg[1] = 0;
    cfg[2] = lines;
    cfg[4] = (settingsFlags_8008B58C.word & 7) != 3;
    cfg[5] = 0;
    cfg[6] = 0;
    cfg[7] = 0;
    cfg[8] = 7;
    cfg[9] = kinds[which];
    cfg[10] = side;
    cfg[11] = 1;
    cfg[12] = 0;
    cfg[13] = 0;
    cfg[14] = (settingsFlags_8008B58C.word >> 3) & 1;
    cfg[15] = 1;
    cfg[16] = 0;
    cfg[3] = (int)tbl[which];
    return (int)OpenMessageWindow_8003422C(cfg);
}

void CombBtlEnd_800A54CC(CombBtlTask* t)
{
    FadeOutSeqSlot_800313C8(0);
    if (word_80091CE0[2] >= 0)
    {
        SsSepSetDecrescendo(word_80091CE0[6], word_80091CE0[2], 0x7F, 0x78);
        word_80091CE0[2] = -1;
    }
    StartSceneFadeOut_8001AA50(0x1E);
    CloseSideWindows_800A7BE4();
    t->next_8 = CombBtlExit_800A5544;
}

extern int IsSceneFadeDone_8001AB94();
extern void StopArenaCamera_800A73E4();
extern void StopFadeTask_800A7478();
extern void RemoveSideMinion_800A7560();
extern void FreeCombatSlots_800A0A6C();
extern void SsUtAllKeyOff();
extern void CombatNextStage_800A16FC();

void CombBtlExit_800A5544(CombBtlTask* t)
{
    int i;
    if (IsSceneFadeDone_8001AB94() == 1)
    {
        StopArenaCamera_800A73E4();
        StopFadeTask_800A7478();
        for (i = 0; i < 2; i++)
        {
            if (dword_800A4078[i] >= 0)
            {
                if (sub_800A1958(&teams_800A3AA0[i][dword_800A4078[i]]) == 0)
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

extern void NextLivingMinion_800A58E8(int i);
extern void StartSlotModel_800A0ACC(int i, void* u);
extern int AreSideModelsReady_800A758C();
extern void CreateSideActor_800A74A0(int i);
extern void OpenSideWindow_800A75F8(int i);
extern void MoveSlotActorTo_800A0E1C(int i, int v);
extern void SetSlotStatusTint_800A1068(int i);
extern void ChooseNextActor_800A599C();
extern void ClearHitResults_800A60F0();
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
            if (dword_800A4078[i] < 0 || sub_800A1958(&teams_800A3AA0[i][dword_800A4078[i]]))
            {
                NextLivingMinion_800A58E8(i);
                StartSlotModel_800A0ACC(i, &teams_800A3AA0[i][dword_800A4078[i]]);
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
        actorSlot_800A85BD = dword_800A4078[0];
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

void NextLivingMinion_800A58E8(int i)
{
    Minion* u;
    do
    {
        dword_800A4078[i]++;
        if (dword_800A4078[i] >= 3)
        {
            dword_800A4078[i] = 0;
        }
        u = &teams_800A3AA0[i][dword_800A4078[i]];
    } while (IsMinionSlotEmpty_800A1934(u) || sub_800A1958(u));
}

#if 0
// Not matched: the original has a jump to the loop increment right after the i == 1 block (one word longer) plus a t0/a3 swap; tried continue/while/switch forms
extern int GetGaugeRate_800A5B70(int side);
extern void MoveBattleCameraDefault_800378CC();
extern int dword_8008D610;
extern int turnCount_800A82E8;
extern unsigned char actorSlot_800A85BD;
extern void StartTurn_800A5C64();
void ChooseNextActor_800A599C(CombBtlTask* t, int side)
{
    int gauge[2];
    int i;
    actorSide_800A85B8 = -1;
    targetSide_800A8620 = -1;
    if (sideGauges_800A84D0[0] == 0 && sideGauges_800A84D0[1] == 0)
    {
        *(short*)((char*)sideGauges_800A84D0 + (dword_8008D610 & 2)) += 100;
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
            }
        }
    }
    if (actorSide_800A85B8 >= 0)
    {
        void (*f)();
        MoveBattleCameraDefault_800378CC();
        turnCount_800A82E8++;
        actorSlot_800A85BD = dword_800A4078[actorSide_800A85B8];
        f = StartTurn_800A5C64;
        t->next_8 = f;
        f(t, side);
    }
}
#endif
INCLUDE_OVERLAY_ASM(combbtl, ChooseNextActor_800A599C);

int GetGaugeRate_800A5B70(int a)
{
    UnitStatus* r;
    int v;
    unsigned char buf[0x18];
    r = GetUnitStatus_80014390((a + 8) & 0xFF);

    if (r)
    {
        CalcEquippedStats_80033624(buf, r);
        v = buf[4] + 0xA;
    }
    else
    {
        v = 0;
    }
    return v;
}

// Near miss: the original loads the two shift counts only after all the stores
#if 0
// Not matched: the original loads the two shift counts after all the stores (alias/scheduling), tried array/struct/pointer forms
void ResetCommands_800A5BB4()
{
    chosenCmd_800A8600.kind_0 = 0x14;
    chosenCmd_800A8600.arg_4 = 0;
    actorCmd_800A85A8.kind_0 = 0x14;
    actorCmd_800A85A8.arg_4 = 0;
    targetCmd_800A8610.kind_0 = 0x14;
    targetCmd_800A8610.arg_4 = 0;
    result_800A85C8.kind_0 = 0;
    result_800A85C8.element_24 = -1;
    result_800A85C8.f26 = -1;
    result_800A85C8.arg_2 = 0;
    result_800A85C8.cured_4 = 0;
    result_800A85C8.inflicted_8 = 0;
    result_800A85C8.actorHpLoss_C = 0;
    result_800A85C8.actorMpLoss_10 = 0;
    result_800A85C8.actorHpDamage_14 = 0;
    result_800A85C8.actorMpDamage_18 = 0;
    result_800A85C8.hpDamage_1C = 0;
    result_800A85C8.mpDamage_20 = 0;
    chosenCmd_800A8600.mask_8 = 1 << (actorSideArr_800A85B8[0] + 8);
    chosenCmd_800A8600.targets_C = 1 << (targetSideArr_800A8620[0] + 8);
    actorCmd_800A85A8.mask_8 = 1 << (actorSideArr_800A85B8[0] + 8);
    actorCmd_800A85A8.targets_C = 1 << (targetSideArr_800A8620[0] + 8);
    targetCmd_800A8610.mask_8 = 1 << (targetSideArr_800A8620[0] + 8);
    targetCmd_800A8610.targets_C = 1 << (actorSideArr_800A85B8[0] + 8);
}
#endif
INCLUDE_OVERLAY_ASM(combbtl, ResetCommands_800A5BB4);

extern void ResetCommands_800A5BB4();
extern void ClearHitResults_800A60F0();
extern void LoadCommandMenu_800A5EB8();
extern void name_800BF7C4(UnitStatus* u, short* a, short* b);
extern int name_800BFA4C(int a, int b);

void StartTurn_800A5C64(CombBtlTask* t)
{
    UnitStatus* u;
    int flags0;
    int fl;
    int r;
    ResetCommands_800A5BB4();
    exchangeStep_800A8488 = 0;
    exchangeFlags_800A84A8 &= 0xFC;
    ClearHitResults_800A60F0();
    u = GetUnitStatus_80014390((unsigned char)(actorSide_800A85B8 + 8));
    flags0 = u->status_0;
    name_800BF7C4(u, &actorHpLoss_800A84BC, &actorMpLoss_800A84C4);
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
    fl = u->status_0;
    r = name_800BFA4C(fl, flags0);
    actorCmd_800A85A8.kind_0 = r;
    actorCmd_800A85A8.targets_C = 0;
    if (fl & 0x200)
    {
        t->next_8 = RunExchange_800A68E0;
        koSfx_800A84A6 = 0x6F;
        exchangeFlags_800A84A8 |= 1;
        koSide_800A8490 = actorSide_800A85B8;
        exchangeFlags_800A84A8 |= 2;
    }
    else if (u->hp_8.cur_0 - actorHpLoss_800A84BC <= 0)
    {
        actorCmd_800A85A8.kind_0 = 0xB;
        actorHpLoss_800A84BC = u->hp_8.cur_0;
        t->next_8 = RunExchange_800A68E0;
        koSfx_800A84A6 = 0x6F;
        exchangeFlags_800A84A8 |= 1;
        koSide_800A8490 = actorSide_800A85B8;
    }
    else if (fl & 2)
    {
        t->next_8 = CheckBattleOver_800A4EC8;
    }
    else if (r == 0x14)
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
            byte_800A3A98[actorSide_800A85B8] = 2;
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
    int a = chosenCmd_800A8600.kind_0;
    actorCmd_800A85A8.kind_0 = a;
    actorCmd_800A85A8.arg_4 = chosenCmd_800A8600.arg_4;
    actorCmd_800A85A8.mask_8 = chosenCmd_800A8600.mask_8;
    actorCmd_800A85A8.targets_C = chosenCmd_800A8600.targets_C;
    if (a == 8)
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


extern void ResolveBattleAction_80012BB0(UnitStatus* actor, UnitStatus* target, CombBtlCmd* cmd, CombBtlResult* out);
extern int CountTeamMinions_800A1AAC(int i);
extern unsigned int CountLivingMinions_800A7164(int i);
extern int turnCount_800A82E8;
extern unsigned int dword_800A3A88;
extern unsigned char exchangeFlags_800A84A8;
extern unsigned char sideHitKind_800A85FC[];
extern int koSide_800A8490;
// announcerLines_800A85C0: the announcer line list RunExchange_800A68E0 shows once the hits land
// the announcer's message lists (NULL terminated), picked by ResolveCommand_800A616C
extern const char* doubleSwapLines_800A8314[];
extern const char* everyNthTurnLines_800A8324[];
extern const char* dodgeLines_800A8334[];
extern const char* directHitLines_800A8344[];
extern const char* poisonLines_800A8354[];
extern const char* statusLines_800A8364[];
extern const char* stoneLines_800A837C[];
extern const char* halfHpLines_800A8394[];
extern const char* tenthHpLines_800A83A0[];
extern const char* swapLines_800A83EC[];
extern const char* elementChangeLines_800A8400[];
extern const char* oneBlowLines_800A8414[];
extern const char* oneHpLeftLines_800A8428[];
extern const char* lossLines_800A843C[];
#if 0
// Not matched: loop strength reduction differs - the original keeps mpDamage_800A8474[i] as (i*2 spilled) + base
// and only hpDamage_800A8470[i] as a pointer; here both become pointers and i spills. Logic is complete.
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
        result_800A85C8.element_24 = stageElement_800A8498;
        result_800A85C8.f26 = dword_800A849C;
        ResolveBattleAction_80012BB0(actor, u, &actorCmd_800A85A8, &result_800A85C8);
        hpDamage_800A8470[i] = result_800A85C8.hpDamage_1C;
        mpDamage_800A8474[i] = result_800A85C8.mpDamage_20;
        newStageElement_800A84A0 = result_800A85C8.element_24;
        actorHpLoss_800A84BC = result_800A85C8.actorHpLoss_C;
        hpDamage_800A8470[actorSide_800A85B8] += result_800A85C8.actorHpDamage_14;
        actorMpLoss_800A84C4 = result_800A85C8.actorMpLoss_10;
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
        statusCured_800A8480[i] = result_800A85C8.cured_4;
        statusInflicted_800A85F0[i] = result_800A85C8.inflicted_8;
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
            if (tenth < u->hp_8.cur_0 && u->hp_8.cur_0 - hpDamage_800A8470[i] <= tenth)
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
                announcerLines_800A85C0 = (const char**)finalLines_800A8454;
            }
            else if (!(dword_800A3A88 & 2) && CountTeamMinions_800A1AAC(actorSide_800A85B8) == 3 && CountLivingMinions_800A7164(actorSide_800A85B8) >= 2 &&
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
                announcerLines_800A85C0 = (const char**)koLines_800A83B0;
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
#endif
INCLUDE_OVERLAY_ASM(combbtl, ResolveCommand_800A616C);

extern unsigned char byte_800A38D8;
extern void StartCameraShake_80037BFC(int a);
extern void StartPadVibration_80036528(int pad, int kind);
extern void StartHitNumber_800A7E34(int side, int kind, int amount);
extern void PlayHitFeedback_800A7C0C(int side);
extern int sub_800A0EE8(int i);
extern int sub_800A0F1C(int i);
extern CombBtlPair sub_800A0F50(int i, CombBtlCmd* cmd, int x);
extern void TriggerSlotEffect_800A0FF0(int i, CombBtlCmd* cmd, int x);
extern void SetAreaElementLight_80039ED8(int mode);
extern void AdjustUnitStatById_800127D0(int unit, int sel, int delta, int mask);
extern int rand();
extern void PlaySfx_80031494(int id);
// hitWindow_800A8494: the merged window; lo counts the frames up to hi
extern CombBtlPair MergeHitWindows_800A71E4(int n, CombBtlPair* p);
extern unsigned char swapSlot_800A85BC; // the minion slot side swap command (kind 3) brings in
// Matched
// The exchange of the two sides' commands: runs both animations, lands the hits at the hit frame, then
// handles side KO / swap / counter. Steps fall through in one call while the step keeps changing.
void RunExchange_800A68E0(CombBtlTask* t)
{
    int prev = -1;
    UnitStatus* u;
    int fl;
    while (prev != exchangeStep_800A8488)
    {
        prev = exchangeStep_800A8488;
        switch (prev)
        {
        case 0:
            if (IsEffectTaskIdle_800148D4() == 1 && sub_800A0EE8(actorSide_800A85B8) == 1 &&
                sub_800A0EE8(targetSide_800A8620) == 1)
            {
                exchangeStep_800A8488 = 1;
            }
            break;
        case 1:
            sideHitWindows_800A84C8[actorSide_800A85B8] = sub_800A0F50(actorSide_800A85B8, &actorCmd_800A85A8, 0);
            sideHitWindows_800A84C8[targetSide_800A8620] = sub_800A0F50(targetSide_800A8620, &targetCmd_800A8610, 1);
            hitWindow_800A8494 = MergeHitWindows_800A71E4(2, sideHitWindows_800A84C8);
            exchangeStep_800A8488 = 2;
            break;
        case 2:
            if (sub_800A0F1C(actorSide_800A85B8) && sub_800A0F1C(targetSide_800A8620))
            {
                exchangeStep_800A8488 = 3;
                announcerTask_800A82DC = 0;
            }
            break;
        case 3:
            if (sideHitWindows_800A84C8[actorSide_800A85B8].lo == hitWindow_800A8494.lo)
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
                    StartPadVibration_80036528(actorSide_800A85B8 ? byte_800A38D8 : 0, 9);
                }
            }
            if (sideHitWindows_800A84C8[targetSide_800A8620].lo == hitWindow_800A8494.lo)
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
            hitWindow_800A8494.lo++;
            if (hitWindow_800A8494.hi < hitWindow_800A8494.lo)
            {
                exchangeStep_800A8488 = 4;
            }
            else if (hitWindow_800A8494.lo == 0)
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
                KillUnit_800127B8(GetMinionStatusOf_80033818(&teams_800A3AA0[koSide_800A8490][dword_800A4078[koSide_800A8490]]));
                DestroySlotActor_800A0D1C(koSide_800A8490);
                FreeSlotModel_800A0B70(koSide_800A8490);
                exchangeStep_800A8488 = prev;
                t->next_8 = CheckBattleOver_800A4EC8;
                exchangeFlags_800A84A8 &= ~1;
            }
            else if (actorCmd_800A85A8.kind_0 == 3)
            {
                RemoveSideMinion_800A7560(actorSide_800A85B8);
                dword_800A4078[actorSide_800A85B8] = swapSlot_800A85BC;
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
            u = GetUnitStatus_80014390((unsigned char)((unsigned char)targetSide_800A8620 + 8));
            if (u->hp_8.cur_0 > 0 && ((result_800A85C8.inflicted_8 & 0x18202) || (u->status_0 & 0x8000)))
            {
                ResetCommands_800A5BB4();
                result_800A85C8.kind_0 = 0;
                actorSide_800A85B8 ^= 1;
                targetSide_800A8620 ^= 1;
                exchangeFlags_800A84A8 |= 0x10;
                fl = u->status_0;
                if (fl & 0x200)
                {
                    actorCmd_800A85A8.kind_0 = 0x13;
                }
                else if (fl & 0x10000)
                {
                    actorCmd_800A85A8.kind_0 = 0xE;
                }
                else if (fl & 2)
                {
                    actorCmd_800A85A8.kind_0 = 0x10;
                }
                else if (fl & 0x8000)
                {
                    actorCmd_800A85A8.kind_0 = 0x12;
                }
                actorCmd_800A85A8.arg_4 = 0;
                actorCmd_800A85A8.targets_C = 0;
                exchangeStep_800A8488 = 0;
                actorCmd_800A85A8.mask_8 = 1 << (actorSide_800A85B8 + 8);
                ResolveCommand_800A616C();
                actorSlot_800A85BD = dword_800A4078[actorSide_800A85B8];
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

const CombBtlA24 sideActorPos_800A4AD4 = { {
        { 0 },
        { 0, 0, 0x3E8 },
    } };
const CombBtlB16 sideActorArgs_800A4AEC = { {
        { 0 },
        { 0, 0, 0, 8 },
    } };
const CombBtlItem sideLabel0_800A4AFC = { 8, 1, 51, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 110, 20, 50, 20, 2, 4 };
const CombBtlItem sideLabel1_800A4B18 = { 8, 1, 223, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 160, 20, 50, 20, 2, 4 };
const CombBtlPos2 statusIconPos_800A4B34 = { {
        { 10, 79 },
        { 0x136, 79 },
    } };
const CombBtlItem slotItem_800A4B3C = { 8, 1, 0, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0, 0, 50, 20, 2, 4 };
const CombBtlPos2 slotItemPos_800A4B58 = { {
        { 110, 40 },
        { 160, 40 },
    } };
const CombBtlInt3 slotIcons_800A4B60 = { { 219, 115, 102 } };
const CombBtlPos2 mpGaugePos_800A4B6C = { {
        { 10, 59 },
        { 210, 59 },
    } };


unsigned int CountLivingMinions_800A7164(int i)
{
    int cnt = 0;
    int j;
    for (j = 0; j < 3; j++)
    {
        if (sub_800A1958(&teams_800A3AA0[i][j]) == 0)
        {
            cnt++;
        }
    }
    return cnt;
}

CombBtlPair MergeHitWindows_800A71E4(int n, CombBtlPair* p)
{
    CombBtlPair r;
    short hi = 0;
    short lo = hi;
    int i;
    for (i = 0; i < n; i++)
    {
        p->hi = p->hi - p->lo;
        p->lo = -p->lo;
        if (p->lo < lo)
        {
            lo = p->lo;
        }
        if (hi < p->hi)
        {
            hi = p->hi;
        }
        p++;
    }
    r.lo = lo;
    r.hi = hi;
    return r;
}

#if 0
// Not matched: scheduling/regalloc around the 0x1000 store and the cb_C address (15 words); the flags store only stays ahead of the camera stores with e as int*
extern void ResetCameraToLevant_800376A8(void);
extern void InitCameraTask_800368F8(void);
extern int cameraState_8008D4F0[];
extern int cameraZoom_8008B4F8;
extern short dword_8007C2EC[];
extern short dword_8007C30C[];
extern short lightMatrix_80087114[];
extern short colorMatrix_80087134[];
void StartArenaCamera_800A7290()
{
    int* e = (int*)AllocEventEntry_80043AF8(cameraTask_8008D4A0);
    char* p;
    SaveData* q;
    if (e)
    {
        e[0] = (e[0] | 1) & ~0x8000;
        ResetCameraToLevant_800376A8();
        StartBattleCamera_80037748();
        e[2] = (int)InitCameraTask_800368F8;
        cameraZoom_8008B4F8 = 0x1000;
        e[3] = (int)FreeCameraTask_800376A0;
        e[0] = (e[0] | 4) & ~0x8000;
        p = (char*)cameraState_8008D4F0;
        *(short*)(p + 0x2E) = 0;
        *(int*)(p + 0x20) = 0;
        *(int*)(p + 0x24) = 0;
        *(int*)(p + 0x28) = 0;
        *(int*)(p + 0x14) = 0;
        *(int*)(p + 0x18) = 0;
        *(int*)(p + 0x1C) = 0;
        *(short*)(p + 0x34) = 0;
        *(short*)(p + 0x36) = 0;
        *(short*)(p + 0x38) = 0;
        *(short*)(p + 0x3C) = 0;
        *(short*)(p + 0x3E) = 0;
        *(short*)(p + 0x40) = 0;
        q = &saveData_8008B570;
        q->levant_7A8.pos.x = 0;
        q->levant_7A8.pos.y = 0;
        q->levant_7A8.pos.z = 0;
        q->levant_7A8.rot.vx = 0;
        q->levant_7A8.rot.vy = 0;
        q->levant_7A8.rot.vz = 0;
        *(short*)(p + 0x34) = dword_8007C2EC[0];
        *(short*)(p + 0x36) = dword_8007C2EC[1];
        *(short*)(p + 0x38) = dword_8007C2EC[2];
        *(short*)(p + 0x3C) = dword_8007C30C[0];
        *(short*)(p + 0x3E) = dword_8007C30C[3];
        *(short*)(p + 0x40) = dword_8007C30C[6];
        lightMatrix_80087114[0] = dword_8007C2EC[0];
        lightMatrix_80087114[1] = dword_8007C2EC[1];
        lightMatrix_80087114[2] = dword_8007C2EC[2];
        colorMatrix_80087134[0] = dword_8007C30C[0];
        colorMatrix_80087134[3] = dword_8007C30C[3];
        colorMatrix_80087134[6] = dword_8007C30C[6];
    }
}
#endif
INCLUDE_OVERLAY_ASM(combbtl, StartArenaCamera_800A7290);

void StopArenaCamera_800A73E4()
{
    sub_800376A0(&cameraTask_8008D4A0->entry, cameraTask_8008D4A0->entry.buffer);
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

void CreateSideActor_800A74A0(int i)
{
    CombBtlA24 a = sideActorPos_800A4AD4;
    CombBtlB16 b = sideActorArgs_800A4AEC;
    CreateSlotActor_800A0BA8(i, a.pos_0[i], b.f0[i]);
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
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008B564);
    CombBtlObj* p;
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        p = (CombBtlObj*)e->buffer;
        p->side_0 = side;
        p->frame_4 = 0;
        p->dst_8.x = sideWindowPos_800A82D4[side][0];
        p->dst_8.y = sideWindowPos_800A82D4[side][1];
        p->dst_8.w = 0x64;
        p->dst_8.h = 0x29;
        e->cb_8 = (EventEntryFn)SideWindowTask_800A7694;
    }
}

extern void AddClipDrawAreaPrim_80033308(unsigned long* ot);
extern void AddDrawAreaPrim_8003326C(RECT* r, unsigned long* ot);
extern void InterpolateWindowRect_8004196C(RECT* d, RECT* s, int cur, int max, int mode);
extern void DrawUnitStatusWindow_8002F1C8(UnitStatus* unit, int gaugeArg, int highlight, int time, RECT* rect, int ot,
                                          int flags);
extern void DrawStatusIcons_8002F480(UnitStatus* status, CombBtlPair* pos, int ot, int reverse);
extern void DrawMpGauge_8002F120(UnitStatus* unit, CombBtlPair* pos, int gaugeArg, short ot);
extern void DrawWindow_80042460(void* a, void* b, void* c, int d);

// Matched
void SideWindowTask_800A7694(EventEntry* e, void* buf)
{
    CombBtlItem w0 = sideLabel0_800A4AFC;
    CombBtlItem w1 = sideLabel1_800A4B18;
    CombBtlBox box60;
    CombBtlPair pt;
    CombBtlPos2 pos70 = statusIconPos_800A4B34;
    CombBtlBox box78;
    CombBtlItem w2;
    union
    {
        CombBtlPos2 pos;
        CombBtlBox box;
    } uA0;
    union
    {
        CombBtlInt3 v;
        RECT r;
    } uA8;
    CombBtlPos2 posB8;
    int sel = 0;
    UnitStatus* st;
    CombBtlItem* w;
    CombBtlObj* o;

    if (exchangeFlags_800A84A8 & 0xC)
    {
        return;
    }
    o = buf;
    if (o->side_0 == actorSide_800A85B8)
    {
        st = GetMinionStatusOf_80033818(&teams_800A3AA0[o->side_0][actorSlot_800A85BD]);
    }
    else
    {
        st = GetMinionStatusOf_80033818(&teams_800A3AA0[o->side_0][dword_800A4078[o->side_0]]);
    }
    AddClipDrawAreaPrim_80033308(pOT_8008D454);
    SetFontClutOffset_8003F900(1, 0);
    InterpolateWindowRect_8004196C(&o->cur_10, &o->dst_8, o->frame_4, 4, 9);
    if (loserSide_800A85F8 >= 0 && loserSide_800A85F8 != o->side_0)
    {
        sel = 1;
    }
    if (o->side_0 == actorSide_800A85B8)
    {
        DrawUnitStatusWindow_8002F1C8(st, word_800A82D0, sel, GetTime30Hz_8002C64C(), &o->cur_10, 10, 0);
    }
    else
    {
        DrawUnitStatusWindow_8002F1C8(st, 0, sel, GetTime30Hz_8002C64C(), &o->cur_10, 10, 0);
    }
    o->frame_4++;
    AddDrawAreaPrim_8003326C(&o->cur_10, pOT_8008D454);
    pt.lo = pos70.p[o->side_0].lo;
    pt.hi = pos70.p[o->side_0].hi;
    DrawStatusIcons_8002F480(st, &pt, 0xF, o->side_0);
    if (o->side_0)
    {
        w = &w1;
    }
    else
    {
        w = &w0;
    }
    if (loserSide_800A85F8 < 0)
    {
        if (o->side_0 == actorSide_800A85B8)
        {
            box60.state_2 = 1;
        }
        else
        {
            box60.state_2 = 0;
        }
    }
    else if (o->side_0 == loserSide_800A85F8)
    {
        box60.state_2 = 0;
    }
    else
    {
        box60.state_2 = 1;
    }
    box60.frame_3 = 1;
    box60.color_0 = saveData_8008B570.uiColor_20.h;
    DrawMenuItemWithWindow_8002ADB4(w, &box60, 0xF, GetTime30Hz_8002C64C());
    w2 = slotItem_800A4B3C;
    uA0.pos = slotItemPos_800A4B58;
    uA8.v = slotIcons_800A4B60;
    w2.icon_4 = uA8.v.v[dword_800A4078[o->side_0]];
    w2.x_10 = uA0.pos.p[o->side_0].lo;
    w2.y_12 = uA0.pos.p[o->side_0].hi;
    box78.state_2 = 0;
    box78.frame_3 = 1;
    box78.color_0 = saveData_8008B570.uiColor_20.h;
    DrawMenuItemWithWindow_8002ADB4(&w2, &box78, 0xF, 0);
    posB8 = mpGaugePos_800A4B6C;
    pt.lo = posB8.p[o->side_0].lo;
    pt.hi = posB8.p[o->side_0].hi;
    uA8.r.w = 0x64;
    uA8.r.h = 0x14;
    uA8.r.x = pt.lo;
    uA8.r.y = pt.hi;
    if (o->side_0 == actorSide_800A85B8)
    {
        DrawMpGauge_8002F120(st, &pt, word_800A82D2, 0xF);
    }
    else
    {
        DrawMpGauge_8002F120(st, &pt, 0, 0xF);
    }
    uA0.box.frame_3 = 1;
    uA0.box.color_0 = saveData_8008B570.uiColor_20.h;
    uA0.box.state_2 = 0;
    DrawWindow_80042460(&uA8.r, &uA0.box, &pOT_8008D454[0xF], 0);
    AddClipDrawAreaPrim_80033308(pOT_8008D454);
}

void CloseSideWindows_800A7BE4()
{
    StopAllEventEntries_80043B40(dword_8008B564);
}

extern unsigned char byte_800A38D8;
extern void StartCameraShake_80037BFC(int a);
extern void StartPadVibration_80036528(int pad, int kind);
extern void StartHitNumber_800A7E34(int a, int b, int c);
extern void FlashScreenWhite_800A7ECC();
void PlayHitFeedback_800A7C0C(int side)
{
    int me;
    int other;
    if (side == 0)
    {
        other = byte_800A38D8;
        me = 0;
    }
    else
    {
        me = byte_800A38D8;
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
            StartPadVibration_80036528(side ? byte_800A38D8 : 0, 0);
        }
        break;
    case 3:
        StartHitNumber_800A7E34(side, 1, hpDamage_800A8470[side]);
        StartHitNumber_800A7E34(side, 2, mpDamage_800A8474[side]);
        if (hpDamage_800A8470[side] > 0 || mpDamage_800A8474[side] > 0)
        {
            StartCameraShake_80037BFC(0x1E);
            StartPadVibration_80036528(side ? byte_800A38D8 : 0, 0);
        }
        break;
    case 4:
        StartHitNumber_800A7E34(side, 1, hpDamage_800A8470[side]);
        StartCameraShake_80037BFC(0x1E);
        StartPadVibration_80036528(side ? byte_800A38D8 : 0, 1);
        FlashScreenWhite_800A7ECC();
        break;
    case 5:
        StartPadVibration_80036528(0, 0x26);
        break;
    }
}

void StartHitNumber_800A7E34(int a, int b, int c)
{
    EventEntry* e = AllocEventEntry_80043AF8(hitNumberTasks_8008D778);
    CombBtlHitNum* p;
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        p = e->buffer;
        p->kind_0 = b;
        p->frame_8 = 0;
        p->amount_4 = c;
        p->side_18 = a;
        p->pos_10 = GetSlotPos_800A10DC(a);
        e->cb_8 = (EventEntryFn)HitNumberTask_800A7EFC;
    }
}

void FlashScreenWhite_800A7ECC()
{
    unsigned char c[3];
    c[0] = 0xFF;
    c[1] = 0xFF;
    c[2] = 0xFF;
    StartScreenFlash_8001C02C(c);
}

extern void AdjustUnitStatById_800127D0(int a, int b, int c, int d);
void HitNumberTask_800A7EFC(EventEntry* e, CombBtlHitNum* buf)
{
    CombBtlHitNum* p = buf;
    DVECTOR sxy;
    SVECTOR v;
    long z;
    long flag;
    int d;
    v.vx = buf->pos_10[0];
    v.vy = buf->pos_10[1];
    v.vz = buf->pos_10[2];
    v.vx -= cameraEye_8008D600.vx;
    v.vy -= cameraEye_8008D600.vy;
    v.vz -= cameraEye_8008D600.vz;
    RotTransPers(&v, (long*)&sxy, &z, &flag);
    if (++p->frame_8 > 16)
    {
        e->flags = (e->flags & ~1) | 0x8000;
        return;
    }
    d = p->amount_4 / (17 - p->frame_8);
    d = -d;
    p->amount_4 += d;
    if (p->kind_0 == 1)
    {
        UnitStatus* r = GetUnitStatus_80014390((unsigned char)(p->side_18 + 8));
        AdjustUnitStatById_800127D0(p->side_18 + 8, 0, d, 0);
        if (r->hp_8.cur_0 <= 0)
        {
            KillUnit_800127B8(GetUnitStatus_80014390((unsigned char)(p->side_18 + 8)));
        }
    }
    else if (p->kind_0 == 2)
    {
        AdjustUnitStatById_800127D0(p->side_18 + 8, 2, d, 0);
    }
}

void SetAnnouncerXa_800A8078(short a0, short a1, short a2)
{
    pendingXa_800A82E0[0] = 1;
    pendingXa_800A82E0[1] = a0;
    pendingXa_800A82E0[2] = a1;
    pendingXa_800A82E0[3] = a2;
}

extern EventNode* dword_8008D458;
extern unsigned int dword_800A3A88;
extern int OpenAnnouncerWindow_800A5408();
extern void AnnouncerTask_800A816C();

int StartAnnouncer_800A8098(int which, int lines, int side)
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D458);
    if (e)
    {
        e->cb_8 = (EventEntryFn)AnnouncerTask_800A816C;
        e->flags = (e->flags | 1) & ~0x8000;
        XaRequestPlay_80043564(pendingXa_800A82E0[1], pendingXa_800A82E0[2], pendingXa_800A82E0[3]);
        announcerWindow_800A8478 = OpenAnnouncerWindow_800A5408(which, lines, side);
        dword_800A3A88 &= ~4;
        dword_800A3A88 &= ~8;
        dword_800A3A88 &= ~0x10;
    }
    return (int)e;
}

extern int GetMsgWindowResultIfDone_800349B4();
extern int XaRequestStop_80043524();
extern void CloseMsgWindow_80034A84();

void AnnouncerTask_800A816C(EventEntry* e)
{
    int buf[4];
    int v;
    if (!(dword_800A3A88 & 4))
    {
        if (GetMsgWindowResultIfDone_800349B4(announcerWindow_800A8478, buf) && buf[3])
        {
            dword_800A3A88 |= 4;
        }
    }
    v = XaNoRequestPending_800435A4();
    if (v == 1 && XaIsIdle_80043584() == v)
    {
        dword_800A3A88 |= 8;
    }
    if (!(dword_800A3A88 & 8))
    {
        v = (settingsFlags_8008B58C.word >> 3) & 1;
        if (v == 1 && (dword_800A3A88 & 4))
        {
            if (!(dword_800A3A88 & 0x10))
            {
                if (XaRequestStop_80043524() == v)
                {
                    dword_800A3A88 |= 0x10;
                }
            }
        }
    }
    if ((dword_800A3A88 & 0xC) == 0xC)
    {
        dword_800A3A88 &= ~4;
        dword_800A3A88 &= ~8;
        dword_800A3A88 &= ~0x10;
        CloseMsgWindow_80034A84(announcerWindow_800A8478);
        e->flags = (e->flags & ~1) | 0x8000;
    }
}

short word_800A82D0 = 0;
short word_800A82D2 = 0;
short sideWindowPos_800A82D4[2][2] = {
    { 10, 20 },
    { 210, 20 },
};
CombBtlNode *announcerTask_800A82DC = 0;
short pendingXa_800A82E0[4] = { 0 };
int turnCount_800A82E8 = 0;
const char *winLinesP1_800A82EC[5] = { aCongratulations_800A40DC, aTheMinionsOfThe_800A40AC, aAreVictorious_800A408C };
const char *winLinesP2_800A8300[5] = { aCongratulations_800A40DC, aTheMinionsOfThe_800A4100, aAreVictorious_800A408C };
const char *doubleSwapLines_800A8314[4] = { aItSeemsYouAreGa_800A415C, aEachOtherSMoves_800A4134 };
const char *everyNthTurnLines_800A8324[4] = { aICannotTakeMyEy_800A41C0, aThisThrillingBa_800A4190 };
const char *dodgeLines_800A8334[4] = { aOhMyItDodgedThe_800A4218, aNoDamageTaken_800A41F4 };
const char *directHitLines_800A8344[4] = { aADirectHit_800A427C, aOhThatHadToHurt_800A4250 };
const char *poisonLines_800A8354[4] = { aPoison_800A42C8, aTheMinionLooksD_800A4298 };
const char *statusLines_800A8364[6] = { aOhNoItIsFalling_800A4370, aThisCouldBeDang_800A433C, aItIsLikeAHelple_800A4304, aOnAChoppingBloc_800A42D8 };
const char *stoneLines_800A837C[6] = { aTheMinionIsBein_800A443C, aStoneItIsSpread_800A4400, aThisCouldBeFata_800A43C4, aNotHealed_800A43AC };
const char *halfHpLines_800A8394[3] = { aTheMinionIsGrav_800A447C };
const char *tenthHpLines_800A83A0[4] = { aItIsBreathingHe_800A44F4, aCouldKeelOverAt_800A44BC };
void *koLines_800A83B0[15] = {
    (void *)aIsTheFightOver_800A45C8, (void *)aItLooksLikeThat_800A4594, (void *)aForThisMinion_800A4570, (void *)aItHasFallenAndC_800A452C,
    0, 0, (void *)&dword_800A45F0, (void *)&dword_800A45F0,
    0, 0, (void *)aWhatAWellChosen_800A4658, (void *)aRightAtTheEleme_800A4614,
    (void *)aVeryEffective_800A45F4,
};
const char *swapLines_800A83EC[5] = { aThePlayerHasSwi_800A46DC, aANewMinionHas_800A46B8, aEnteredTheArena_800A4690 };
const char *elementChangeLines_800A8400[5] = { aAChangeOfElemen_800A4780, aWhatAnExcitingM_800A4750, aWhatWillHappenN_800A4720 };
const char *oneBlowLines_800A8414[5] = { aSuchOverwhelmin_800A481C, aTheMinionHasFal_800A47F0, aWithOneFatalBlo_800A47C4 };
const char *oneHpLeftLines_800A8428[5] = { aWhatAmazingWill_800A48A0, aAgainstAllOdds_800A487C, aItCouldBeVictor_800A4850 };
const char *lossLines_800A843C[6] = { aAnotherLossTheF_800A495C, aDecidedBeforeTh_800A491C, aTooBad_800A4908, aIWasEvenRooting_800A48D0 };
int finalLines_800A8454[7] = { (int)aWhatACloseFight_800A4A04, (int)aFinallyADecisio_800A49CC, (int)aReached_800A49B8, (int)aWellDone_800A49A0, 0, 0, 0x63750B00 };
short hpDamage_800A8470[2] = { 0 };
short mpDamage_800A8474[2] = { 0 };
int announcerWindow_800A8478 = 0;
int dword_800A847C = 0;
int statusCured_800A8480[2] = { 0 };
short exchangeStep_800A8488 = 0;
EventEntry *commandMenuTask_800A848C = 0;
int koSide_800A8490 = 0;
CombBtlPair hitWindow_800A8494 = { 0 };
int stageElement_800A8498 = 0;
int dword_800A849C = 0;
int newStageElement_800A84A0 = 0;
short targetSfx_800A84A4 = 0;
short koSfx_800A84A6 = 0;
unsigned char exchangeFlags_800A84A8 = 0;
int dword_800A84AC = 0;
int sideEntering_800A84B0[2] = { 0 };
int setupStep_800A84B8 = 0;
short actorHpLoss_800A84BC = 0;
int stageId_800A84C0 = 0;
short actorMpLoss_800A84C4 = 0;
CombBtlPair sideHitWindows_800A84C8[2] = { { 0 } };
short sideGauges_800A84D0[2] = { 0 };
int waitTimer_800A84D4 = 0;
CombBtlHist commandHistory_800A84D8[10] = { { 0 } };
int fileRequest_800A85A0 = 0;
int dword_800A85A4 = 0;
CombBtlCmd actorCmd_800A85A8 = { 0 };
int actorSide_800A85B8 = 0;
unsigned char swapSlot_800A85BC = 0;
unsigned char actorSlot_800A85BD = 0;
const char** announcerLines_800A85C0 = 0;
int dword_800A85C4 = 0;
CombBtlResult result_800A85C8 = { 0 };
int statusInflicted_800A85F0[2] = { 0 };
int loserSide_800A85F8 = 0;
unsigned char sideHitKind_800A85FC[4] = { 0 };
CombBtlCmd chosenCmd_800A8600 = { 0 };
CombBtlCmd targetCmd_800A8610 = { 0 };
int targetSide_800A8620 = 0;
