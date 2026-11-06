// BATTLE.BIN, source file 1 of 6
#include "battle.h"

int dword_800B66C0 SDATA = 31;

// GAME's encounter task buffer while a battle runs (GAME's GameQ_1; WaitBattleOverlay_800A1474 starts the battle)

void BattleEnd_800BA254(BatTaskEntry* task, BatEndWork* work)
{
    SoundStruct* seq;
    BatSelection* sel;
    if ((*work->battleTask_8 & 0x8001) == 1)
    {
        return;
    }
    if (IsEffectTaskIdle_800148D4() != 1)
    {
        return;
    }
    sel = GetBattleSelection_800A1E3C();
    work->c_C = sel->c_18;
    encounterRecord_800ADE78.active_0 = 0;
    MoveBattleCameraForAction_80037828(2, 0, 0);
    switch (battleResult_800B1230)
    {
    case 0:
        StopSoundSeqs_80030D68(&systemSound_80091D40);
        seq = &bgmSound_80091CE0;
        if (seq->seqNum_4 >= 0)
        {
            SsSepSetDecrescendo(seq->sepAccessNum_C, seq->seqNum_4, 0x7F, 0x78);
            seq->seqNum_4 = -1;
        }
        StopSeqSlot_80031334(0);
        PlaySeqSlot_80031160(1, 1);
        if (summonedUnit_800C9C82 != 0)
        {
            ExitLevantBattleMode_800A8984(0);
        }
        else
        {
            ExitLevantBattleMode_800A8984(1);
        }
        work->timer_4 = 0x3C;
        task->next_8 = BattleEndVictory_800BA564;
        break;
    case 1:
        ExitLevantBattleMode_800A8984(0);
        work->timer_4 = 0;
        task->next_8 = BattleEndVictory_800BA564;
        break;
    case 2:
        ExitLevantBattleMode_800A8984(0);
        if (TestBattleFlag_800BC820(0x20000) == 0)
        {
            FadeOutSeqSlot_800313C8(0);
        }
        else
        {
            seq = &bgmSound_80091CE0;
            if (seq->seqNum_4 >= 0)
            {
                SsSepSetDecrescendo(seq->sepAccessNum_C, seq->seqNum_4, 0x7F, 0x78);
                seq->seqNum_4 = -1;
            }
        }
        task->next_8 = BattleEndWaitLevant_800BA52C;
        break;
    case 3:
        ExitLevantBattleMode_800A8984(0);
        StartSceneDarken_8001AAA8(0x3C);
        task->next_8 = BattleEndDefeat_800BA444;
        break;
    case 4:
    case 5:
        ExitLevantBattleMode_800A8984(0);
        work->timer_4 = 0x12;
        if (TestBattleFlag_800BC820(0x20000) == 0)
        {
            FadeOutSeqSlot_800313C8(0);
        }
        else
        {
            seq = &bgmSound_80091CE0;
            if (seq->seqNum_4 >= 0)
            {
                SsSepSetDecrescendo(seq->sepAccessNum_C, seq->seqNum_4, 0x7F, 0x78);
                seq->seqNum_4 = -1;
            }
        }
        task->next_8 = BattleEndWaitLevant_800BA52C;
        break;
    }
}


void BattleEndDefeat_800BA444(BatTaskEntry* task)
{
    int done = IsSceneFadeDone_8001AB94();
    if (done == 1)
    {
        StopLevantAnimLoop_800A9364();
        if (IsLevantActionFinished_800A8DAC() == done)
        {
            ReviveOneHp_80011CF4(&saveData_8008B570.levantStatus_7C8);
            task->next_8 = BattleEndWaitFade_800BA4F4;
            if (TestBattleFlag_800BC820(0x20000) == 0)
            {
                FadeOutSeqSlot_800313C8(0);
            }
            else
            {
                SoundStruct* seq = &bgmSound_80091CE0;
                if (seq->seqNum_4 >= 0)
                {
                    SsSepSetDecrescendo(seq->sepAccessNum_C, seq->seqNum_4, 0x7F, 0x78);
                    seq->seqNum_4 = -1;
                }
            }
        }
    }
}

void BattleEndWaitFade_800BA4F4(BatTaskEntry* task)
{
    if (IsSceneFadeDone_8001AB94() == 1)
    {
        task->next_8 = BattleEndFadeOut_800BA624;
    }
}

void BattleEndWaitLevant_800BA52C(BatTaskEntry* task)
{
    if (IsLevantIdle_800A89F0() == 1)
    {
        task->next_8 = BattleEndFadeOut_800BA624;
    }
}

void BattleEndVictory_800BA564(BatTaskEntry* task, BatEndWork* work)
{
    int done = IsLevantActionFinished_800A8DAC();
    if (done == 1)
    {
        if (AreAllEncounterEnemiesGone_800A1B2C() == done)
        {
            if (--work->timer_4 < 0)
            {
                if (TestBattleFlag_800BC820(0x20000) == 0)
                {
                    FadeOutSeqSlot_800313C8(0);
                }
                else
                {
                    SoundStruct* seq = &bgmSound_80091CE0;
                    if (seq->seqNum_4 >= 0)
                    {
                        SsSepSetDecrescendo(seq->sepAccessNum_C, seq->seqNum_4, 0x7F, 0x78);
                        seq->seqNum_4 = -1;
                    }
                }
                task->next_8 = BattleEndFadeOut_800BA624;
            }
        }
    }
}

void BattleEndFadeOut_800BA624(BatTaskEntry* task, BatEndWork* work)
{
    SetFadeMode_8001C19C(0, 0x20);
    SetFadeMode_8001C19C(1, 0x20);
    StopSceneDarken_8001AAF4();
    if (battleResult_800B1230 == 2)
    {
        work->timer_4 = 0x1E;
        task->next_8 = BattleEndFled_800BA6A0;
    }
    else
    {
        task->next_8 = BattleEndUnload_800BA788;
    }
}

void BattleEndFled_800BA6A0(BatTaskEntry* task, BatEndWork* work)
{
    eventDispatchHalt_8008B540 = 1;
    SetFadeMode_8001C19C(0, 0x20);
    if (--work->timer_4 <= 0)
    {
        if (battleResult_800B1230 == 2)
        {
            RemoveAliveEnemies_800BA720();
        }
        task->next_8 = BattleEndUnload_800BA788;
    }
}

void RemoveAliveEnemies_800BA720()
{
    int alive = GetEnemyAliveMask_800A248C();
    int i;
    int bit;
    for (i = 0; i < 3; i++)
    {
        bit = 1 << (i + 4);
        if (alive & bit)
        {
            RemoveEnemy_800A2924(i);
        }
    }
}

void BattleEndUnload_800BA788(BatTaskEntry* task)
{
    SetFadeMode_8001C19C(0, 0x20);
    FreeSummonedMinion_800C0BA0();
    DestroyEncounterActors_800A1B78();
    FreeActiveOverlay_8002C014();
    FreeStageEffects_80039FC0();
    StopSoundSeqs_80030D68(&systemSound_80091D40);
    StopSeqSlot_80031334(0);
    FreeSeqSlotSound_80030664();
    SsUtAllKeyOff(0);
    PlayMusic_800300E0(GetBattleMusic_800315E4(), 1);
    LoadLoaderModelAnimSets_80020898();
    if (levantAnimSet_80091C74 >= 0)
    {
        LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
    }
    eventDispatchHalt_8008B540 = 1;
    task->next_8 = BattleEndReturnToField_800BA848;
}

void BattleEndReturnToField_800BA848(BatTaskEntry* task, BatEndWork* work)
{
    SetFadeMode_8001C19C(0, 0x20);
    if (AreLoaderModelsLoaded_80020924() && AreLevantFilesLoaded_800AC768())
    {
        ResumeOtherEnemies_800A1F0C();
        EndBattleCamera_80037770();
        SetLevantVisible_800A9384(1);
        ClearLevantBattleStance_800A8DCC();
        UnlockLevantMovement_800A89C8();
        EndEncounter_800A1E1C();
        RecoverPartyAfterBattle_800BA97C();
        EnableCameraPoints_800A094C();
        if ((battleResult_800B1230 == 0 || battleResult_800B1230 == 2) && work->c_C == 1)
        {
            work->fileReq_0 = LoadOverlayIfChanged_80020D1C(1, 7);
            task->next_8 = WaitBattleReturnFiles_800A14E0;
        }
        else if (battleResult_800B1230 == 3)
        {
            StopLevantAnimLoop_800A9364();
            WarpAfterLostBattle_800A5FAC();
            if (forceMapReload_80091C9C == 0)
            {
                RequestAreaReload_80027314();
            }
            task->next_8 = WaitMapReloadAfterBattle_800A15FC;
        }
        else
        {
            RequestAreaReload_80027314();
            task->next_8 = WaitMapReloadAfterBattle_800A15FC;
        }
    }
    eventDispatchHalt_8008B540 = 1;
}

void RecoverPartyAfterBattle_800BA97C()
{
    int count;
    int i;
    ClearStatus_80011C30(&saveData_8008B570.levantStatus_7C8);
    count = CountMinions_80010548(3);
    for (i = 0; i < count; i++)
    {
        RecoverQuarterHpMp_80011C44(GetMinionStatus_800107A0(3, i));
    }
}

EventEntry* StartBattle_800BA9E4()
{
    EventEntry* entry = AllocEventEntry_80043AF8(battleTask_8008D624);
    char center[0x10];
    int element;
    if (entry)
    {
        entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
        entry->cb_8 = (EventEntryFn)BattleLoad_800BAC4C;
        element = GetSpecialStageIndex_800A5354();
        shownAreaElement_800C9D82 = element;
        areaElement_800C9D84 = element;
        fixedStageElement_800C9D83 = element;
        InitTurnGauges_800BF648(turnGauges_800C9C68, GetEncounterAdvantage_800BAAD8());
        battleFlags_800B1228 = 0;
        SetBattleFlag_800BC838(0x80000);
        savedEnemyCursor_800C9D56 = 0;
        actingUnit_800C9C7C = 0;
        shownUnit_800C9C99 = 0;
        summonedUnit_800C9C82 = 0;
        battleHitEnemies_800B122C = 0;
        SpawnEncounterEnemies_800A1F80();
        GetUnitsCenter_800BC378(GetEnemyAliveMask_800A248C(), center);
        StartLevantBattle_800A8D0C(center);
        InitEnemyRecords_800BABC4();
        battleLoadState_800C9C58 = 0;
        DisableCameraPoints_800A096C();
    }
    return entry;
}

int GetEncounterAdvantage_800BAAD8()
{
    SaveData* sd = &saveData_8008B570;
    int levantX = sd->levant_7A8.pos.x;
    int levantZ = sd->levant_7A8.pos.z;
    short levantRot = (unsigned short)sd->levant_7A8.rot.vy;
    int leaderX = GetEncounterLeaderPos_800A1E48()[0];
    int leaderZ = GetEncounterLeaderPos_800A1E48()[2];
    short* leaderRot = GetEncounterLeaderRot_800A1E68();
    int angle;
    if (sinTable_80084540[(levantRot - leaderRot[1] + 0x400) & 0xFFF] >= 0)
    {
        angle = ratan2_8003B548(leaderX - levantX, leaderZ - levantZ);
        if (sinTable_80084540[(angle - levantRot + 0x400) & 0xFFF] >= 0)
        {
            return 1;
        }
        return 2;
    }
    return 0;
}

void InitEnemyRecords_800BABC4()
{
    int i;
    int alive;
    BatEnemyResult* rec;
    i = 0;
    rec = battleEnemyResults_800B1238;
loop: // a for loop hoists the constants (-1, 7, 1) out of the loop; the original keeps them inside
    alive = GetEnemyAliveMask_800A248C() & (1 << (i + 4));
    if (alive != 0)
    {
        rec->species_4 = GetEnemySpecies_800A2BE4(i);
    }
    else
    {
        rec->species_4 = -1;
    }
    rec->exp_0 = 0;
    rec->level_8 = 0;
    rec->killer_6 = 0;
    rec->kind_A = 7;
    rec++;
    i++;
    if (i < 3)
    {
        goto loop;
    }
}

void BattleLoad_800BAC4C(BatTaskEntry* task)
{
    int species;
    int music;
    switch (battleLoadState_800C9C58)
    {
    case 0:
        if (LoadSeqSlotSound_800303E8() == 0)
        {
            break;
        }
        battleLoadState_800C9C58 = 1;
    case 1:
        if (IsSoundTaskReady_80030688() == 0)
        {
            break;
        }
        species = GetEnemySpecies_800A2BE4(0);
        if (IsUncapturableSpecies_800BF980(species))
        {
            SetBattleFlag_800BC838(0x20000);
            if (species == 0x37)
            {
                music = 0x92;
            }
            else if (species == 0x32)
            {
                music = 0x23;
            }
            else
            {
                music = 0x24;
            }
            if (PlayMusic_800300E0(music, 1) == 0)
            {
                break;
            }
        }
        else
        {
            ClearBattleFlag_800BC850(0x20000);
            FreeBgmAndSfx_800315F4();
            PlaySeqSlot_80031160(0, 1);
        }
        battleLoadState_800C9C58 = 2;
    case 2:
        LoadStageEffects_800BC878();
        battleLoadState_800C9C58 = 3;
        break;
    case 3:
        if (AreStageEffectsLoaded_800BC8E8() == 0)
        {
            break;
        }
        battleLoadState_800C9C58 = 4;
    case 4:
        if (IsFadeDone_8001C2FC() == 0)
        {
            break;
        }
        SetFadeMode_8001C19C(3, 0x20);
        StartBattleCamera_80037748();
        battleLoadState_800C9C58 = 5;
    case 5:
        if (((int (*)())IsSceneFadeDone_8001AB94)() == 0) // called without its argument here
        {
            break;
        }
        battleLoadState_800C9C58 = 6;
    case 6:
        LoadUiTiy_8002BF74();
        battleLoadState_800C9C58 = 7;
    case 7:
        if (uiTiyLoaded_8008B4E8 == 0)
        {
            break;
        }
        StartBattleWindows_800BFB80();
        battleLoadState_800C9C58 = 8;
    case 8:
        if (GetCameraMode_800378F8() >= 4u)
        {
            task->next_8 = BattleNextTurn_800BAE74;
        }
        break;
    }
}

int IsBattleOver_800BAE10()
{
    if (TestBattleFlag_800BC820(4) == 1 || TestBattleFlag_800BC820(0x80) == 1)
    {
        return 1;
    }
    if (TestBattleFlag_800BC820(2) == 1)
    {
        return 0;
    }
    return GetEnemyAliveMask_800A248C() == 0;
}

void BattleNextTurn_800BAE74(BatTaskEntry* task, BatTurnWork* work)
{
    BatTurnWork* workCopy = work;
    int* entry;
    int entryUnit;
    ClearBattleFlag_800BC850(0x8000);
    ClearBattleFlag_800BC850(0x10000);
    if (encounterRecord_800ADE78.active_0 == 1)
    {
        if (encounterRecord_800ADE78.next_10 >= 0)
        {
            actingUnit_800C9C7C = 10;
            work->handle_C = sub_800B4200(&encounterRecord_800ADE78);
            task->next_8 = WaitChainMessage_800BB100;
            return;
        }
        if (TestBattleFlag_800BC820(0x2000) == 1)
        {
            SetBattleFlag_800BC838(0x100);
            BattleFinish_800BB1B0(task, work);
            task->next_8 = BattleFinish_800BB1B0;
            return;
        }
        encounterRecord_800ADE78.count_C++;
        if (sub_800B41D0(&encounterRecord_800ADE78) == 1)
        {
            SetBattleFlag_800BC838(0x100);
            BattleFinish_800BB1B0(task, work);
            task->next_8 = BattleFinish_800BB1B0;
            return;
        }
        entry = sub_800B41A8(&encounterRecord_800ADE78);
        entryUnit = *entry;
        chainEntry_800C9C78 = entry;
        if (entryUnit == 0)
        {
            actingUnit_800C9C7C = summonedUnit_800C9C82;
        }
        else
        {
            actingUnit_800C9C7C = *chainEntry_800C9C78;
        }
        if (actingUnit_800C9C7C == 10)
        {
            BatChainRecord* chain = &encounterRecord_800ADE78;
            chain->next_10 = chainEntry_800C9C78[5];
            workCopy->handle_C = sub_800B4200(chain);
            task->next_8 = WaitChainMessage_800BB100;
            return;
        }
    }
    else
    {
        if (IsBattleOver_800BAE10())
        {
            BattleFinish_800BB1B0(task, work);
            task->next_8 = BattleFinish_800BB1B0;
            return;
        }
        if (TestBattleFlag_800BC820(8) == 1)
        {
            ClearBattleFlag_800BC850(8);
            actingUnit_800C9C7C = 0;
            curCommand_800C9C88.kind_0 = 3;
            curCommand_800C9C88.arg_4 = 0;
            curCommand_800C9C88.mask_8 = 1;
            curCommand_800C9C88.targets_C = 0;
            SetBattleFlag_800BC838(0x8000);
            task->next_8 = CmdRecallDone_800BBE00;
            work->next_8 = work->resume_4 = BattleNextTurn_800BAE74;
            return;
        }
        if (TestBattleFlag_800BC820(2) == 1)
        {
            ClearBattleFlag_800BC850(2);
            commandUnit_800C9C98 = 4;
            actingUnit_800C9C7C = 4;
            curCommand_800C9C88.kind_0 = 3;
            curCommand_800C9C88.arg_4 = 0;
            curCommand_800C9C88.mask_8 = 0x10;
            curCommand_800C9C88.targets_C = 0;
            SetBattleFlag_800BC838(0x10000);
            task->next_8 = CmdEnemySwapJoin_800BC05C;
            workCopy->next_8 = workCopy->resume_4 = BattleNextTurn_800BAE74;
            return;
        }
        actingUnit_800C9C7C = 7;
    }
    task->next_8 = SelectActingUnit_800BB314;
}

void WaitChainMessage_800BB100(BatTaskEntry* task, BatTurnWork* work)
{
    MsgResult result;
    if (GetMsgWindowResultIfDone_800349B4(work->handle_C, &result) && result.field_24)
    {
        CloseMsgWindow_80034A84(work->handle_C);
        task->next_8 = WaitChainMessageClosed_800BB168;
    }
}

void WaitChainMessageClosed_800BB168(BatTaskEntry* task, BatTurnWork* work)
{
    if (IsMsgWindowAlive_80034AB8(work->handle_C) == 0)
    {
        encounterChainNext_800ADE88 = -1;
        task->next_8 = BattleNextTurn_800BAE74;
    }
}

void BattleFinish_800BB1B0(BatTaskEntry* task, BatTurnWork* work)
{
    BatTurnWork* w = work;
    BatTaskEntry* t = task;
    if (TestBattleFlag_800BC820(4) == 1)
    {
        ClearBattleFlag_800BC850(4);
        battleResult_800B1230 = 3;
    }
    else if (TestBattleFlag_800BC820(0x80) == 1)
    {
        ClearBattleFlag_800BC850(0x80);
        battleResult_800B1230 = 2;
    }
    else if (TestBattleFlag_800BC820(0x100) == 1)
    {
        if (summonedUnit_800C9C82 != 0)
        {
            actingUnit_800C9C7C = summonedUnit_800C9C82;
            curCommand_800C9C88.kind_0 = 3;
            curCommand_800C9C88.arg_4 = 0;
            curCommand_800C9C88.targets_C = 0;
            curCommand_800C9C88.mask_8 = 1 << actingUnit_800C9C7C;
            t->next_8 = GetCommandHandler_800BC174();
            w->resume_4 = BattleFinish_800BB1B0;
            w->next_8 = BattleFinish_800BB1B0;
            return;
        }
        if (TestBattleFlag_800BC820(0x2000) == 1)
        {
            battleResult_800B1230 = 5;
        }
        else
        {
            battleResult_800B1230 = 4;
        }
        ClearBattleFlag_800BC850(0x100);
    }
    else
    {
        if (GetEnemyAliveMask_800A248C() != 0)
        {
            return;
        }
        if (TestBattleFlag_800BC820(0x40) == 1)
        {
            battleResult_800B1230 = 0;
        }
        else
        {
            battleResult_800B1230 = 1;
        }
    }
    StopBattleWindows_800BFBB8();
    t->flags_0 = (t->flags_0 & ~1) | 0x8000;
}

void SelectActingUnit_800BB314(BatTaskEntry* task)
{
    if (actingUnit_800C9C7C == 7)
    {
        actingUnit_800C9C7C = AdvanceTurnGauges_800BF6BC(turnGauges_800C9C68, summonedUnit_800C9C82);
    }
    task->next_8 = BeginUnitTurn_800BB380;
    shownUnit_800C9C99 = summonedUnit_800C9C82;
}

void BeginUnitTurn_800BB380(BatTaskEntry* task, BatTurnWork* work)
{
    BatTurnWork* w = work;
    UnitStatus* status;
    int oldStatus;
    int side;
    int cmd;
    unsigned int newStatus;
    ResetCurrentCommand_800BB74C();
    ResetTurnResults_800BB7D4();
    status = GetUnitStatus_80014390(actingUnit_800C9C7C);
    oldStatus = status->status_0;
    side = GetUnitSide_800BC7DC(actingUnit_800C9C7C);
    TickUnitStatus_800BF7C4(status, &actorHpChange_800C9C7E, &actorMpChange_800C9C80);
    if (actorHpChange_800C9C7E != 0)
    {
        if (actorMpChange_800C9C80 != 0)
        {
            unitHitKinds_800C9CBC[actingUnit_800C9C7C] = 3;
        }
        else
        {
            unitHitKinds_800C9CBC[actingUnit_800C9C7C] = 1;
        }
    }
    else if (actorMpChange_800C9C80 != 0)
    {
        unitHitKinds_800C9CBC[actingUnit_800C9C7C] = 2;
    }
    newStatus = status->status_0;
    cmd = GetStatusCommand_800BFA4C(newStatus, oldStatus);
    curCommand_800C9C88.kind_0 = cmd;
    curCommand_800C9C88.arg_4 = 0;
    curCommand_800C9C88.targets_C = 0;
    if (cmd == 0x13)
    {
        switch ((unsigned int)side)
        {
        case 0:
            SetBattleFlag_800BC838(4);
            deathSfx_800C9D80 = 0x1C;
            break;
        case 1:
            SetBattleFlag_800BC838(8);
            deathSfx_800C9D80 = 0x6F;
            break;
        case 2:
            SetBattleFlag_800BC838(0x40);
            if (IsBossSpecies_800BF9B4(GetEnemySpecies_800A2BE4(actingUnit_800C9C7C - 4)) == 1)
            {
                SetBattleFlag_800BC838(0x100000);
                deathSfx_800C9D80 = 0x1C;
            }
            else
            {
                ClearBattleFlag_800BC850(0x100000);
                deathSfx_800C9D80 = 0x6F;
            }
            if (GetActiveSwapEnemy_800A2AB4() == 2)
            {
                SetBattleFlag_800BC838(2);
            }
            break;
        }
        SetBattleFlag_800BC838(0x1000);
        task->next_8 = GetCommandHandler_800BC174();
        w->resume_4 = w->next_8 = BattleNextTurn_800BAE74;
        return;
    }
    if (status->hp_8.cur_0 - actorHpChange_800C9C7E <= 0)
    {
        curCommand_800C9C88.kind_0 = 0xB;
        actorHpChange_800C9C7E = status->hp_8.cur_0;
        switch ((unsigned int)side)
        {
        case 0:
            SetBattleFlag_800BC838(4);
            deathSfx_800C9D80 = 0x1C;
            break;
        case 1:
            SetBattleFlag_800BC838(8);
            deathSfx_800C9D80 = 0x6F;
            break;
        case 2:
            SetBattleFlag_800BC838(0x40);
            if (IsBossSpecies_800BF9B4(GetEnemySpecies_800A2BE4(actingUnit_800C9C7C - 4)) == 1)
            {
                SetBattleFlag_800BC838(0x100000);
                deathSfx_800C9D80 = 0x1C;
            }
            else
            {
                ClearBattleFlag_800BC850(0x100000);
                deathSfx_800C9D80 = 0x6F;
            }
            if (GetActiveSwapEnemy_800A2AB4() == 2)
            {
                SetBattleFlag_800BC838(2);
            }
            break;
        }
        SetBattleFlag_800BC838(0x1000);
        task->next_8 = GetCommandHandler_800BC174();
        w->resume_4 = w->next_8 = BattleNextTurn_800BAE74;
        return;
    }
    if (((newStatus & 0x10000) && (oldStatus & 0x10000)) || ((newStatus & 2) && (oldStatus & 2)))
    {
        task->next_8 = BattleNextTurn_800BAE74;
        return;
    }
    if (curCommand_800C9C88.kind_0 == 0x14)
    {
        task->next_8 = PrepareCommandInput_800BB860;
        return;
    }
    SetBattleFlag_800BC838(0x1000);
    task->next_8 = GetCommandHandler_800BC174();
    if (newStatus & 0x200)
    {
        w->resume_4 = w->next_8 = BattleNextTurn_800BAE74;
    }
    else if (newStatus & 0x10002)
    {
        w->resume_4 = w->next_8 = BattleNextTurn_800BAE74;
    }
    else
    {
        w->resume_4 = w->next_8 = PrepareCommandInput_800BB860;
    }
}

void ResetCurrentCommand_800BB74C()
{
    curCommand_800C9C88.kind_0 = 0x14;
    curCommand_800C9C88.arg_4 = 0;
    curCommand_800C9C88.targets_C = 0;
    curCommand_800C9C88.mask_8 = 1 << actingUnit_800C9C7C;
    ResetUnitReactions_800BB794();
}

void ResetUnitReactions_800BB794()
{
    int i;
    for (i = 0; i < 7; i++)
    {
        unitReactions_800C9CC8[i].kind_0 = 0x14;
        unitReactions_800C9CC8[i].arg_4 = 0;
        unitReactions_800C9CC8[i].mask_8 = 1 << i;
        unitReactions_800C9CC8[i].targets_C = 0;
    }
}

void ResetTurnResults_800BB7D4()
{
    int i;
    hitSfx_800C9D78 = -1;
    deathSfx_800C9D80 = -1;
    actorHpChange_800C9C7E = 0;
    actorMpChange_800C9C80 = 0;
    for (i = 0; i < 7; i++)
    {
        unitHpDamage_800C9D38[i] = 0;
        unitMpDamage_800C9D48[i] = 0;
        unitHitKinds_800C9CBC[i] = 0;
        unitResultFlags_800C9D58[i] = 0;
        unitStatusInflicted_800C9CA0[i] = 0;
    }
}

void PrepareCommandInput_800BB860(BatTaskEntry* task)
{
    ClearBattleFlag_800BC850(0x80000);
    task->next_8 = InputCommand_800BB894;
}

void InputCommand_800BB894(BatTaskEntry* task, BatTurnWork* work)
{
    if (actingUnit_800C9C7C >= 4)
    {
        if (encounterRecord_800ADE78.active_0 == 1)
        {
            sub_800B42A8(&curCommand_800C9C88, &encounterRecord_800ADE78);
        }
        else
        {
            EnemyChooseCommand_800A2618(&curCommand_800C9C88, actingUnit_800C9C7C - 4);
        }
        task->next_8 = GetCommandHandler_800BC174();
        work->next_8 = work->resume_4 = BattleNextTurn_800BAE74;
    }
    else
    {
        work->handle_C = StartBattleMenu_800C6EFC();
        task->next_8 = WaitBattleMenu_800BB940;
    }
}

void WaitBattleMenu_800BB940(BatTaskEntry* task, BatTurnWork* work)
{
    if ((*(int*)work->handle_C & 0x8001) != 1)
    {
        ClearBattleFlag_800BC850(0x2000);
        if (encounterRecord_800ADE78.active_0 == 1)
        {
            if ((encounterRecord_800ADE78.next_10 = sub_800B4318(&curCommand_800C9C88, &encounterRecord_800ADE78)) >= 0)
            {
                SetBattleFlag_800BC838(0x2000);
                task->next_8 = BattleNextTurn_800BAE74;
                return;
            }
        }
        task->next_8 = GetCommandHandler_800BC174();
        work->resume_4 = BattleNextTurn_800BAE74;
        if (curCommand_800C9C88.kind_0 == 2)
        {
            battleHitEnemies_800B122C |= curCommand_800C9C88.targets_C;
        }
    }
}

void CmdAction_800BBA24(BatTaskEntry* task, BatTurnWork* work)
{
    work->handle_C = StartActionTask_800BC28C();
    work->next_8 = CmdActionReactions_800BBA70;
    task->next_8 = WaitActionTask_800BC144;
}

void CmdActionReactions_800BBA70(BatTaskEntry* task, BatTurnWork* work)
{
    BatTurnWork* w = work;
    unsigned int mask;
    int i;
    BattleCmd* reactions;
    if (NeedsStatusReaction_800BC1A8(curCommand_800C9C88.targets_C) == 1)
    {
        mask = curCommand_800C9C88.targets_C;
        SetBattleFlag_800BC838(0x1000);
        ResetCurrentCommand_800BB74C();
        ResetTurnResults_800BB7D4();
        reactions = unitReactions_800C9CC8;
        for (i = 0; i < 7; i++)
        {
            if (mask & (1 << i))
            {
                int status = GetUnitStatus_80014390(i & 0xFF)->status_0;
                if (status & 0x200)
                {
                    reactions[i].kind_0 = 0x13;
                }
                else if (status & 0x10000)
                {
                    reactions[i].kind_0 = 0xE;
                }
                else if (status & 2)
                {
                    reactions[i].kind_0 = 0x10;
                }
                else if (status & 0x8000)
                {
                    reactions[i].kind_0 = 0x12;
                }
                reactions[i].arg_4 = 0;
                reactions[i].mask_8 = 1 << i;
                reactions[i].targets_C = 0;
            }
        }
        actingUnit_800C9C7C = 7;
        w->handle_C = StartActionTask_800BC28C();
        w->next_8 = w->resume_4;
        task->next_8 = WaitActionTask_800BC144;
    }
    else
    {
        task->next_8 = w->resume_4;
    }
}

void CmdSummon_800BBBA8(BatTaskEntry* task, BatTurnWork* work)
{
    work->handle_C = StartActionTask_800BC28C();
    work->next_8 = CmdSummonWait_800BBCC8;
    task->next_8 = WaitActionTask_800BC144;
}

// CmdRecall_800BBDB4 gets no arguments (task/work are still in a0/a1)
void CmdSwapMinion_800BBBF4(BatTaskEntry* task, BatTurnWork* work)
{
    BatTurnWork* w = work;
    curCommand_800C9C88.kind_0 = 3;
    curCommand_800C9C88.targets_C = 0;
    if (!commandUnit_800C9C98)
    {
        CmdRecall_800BBDB4();
    }
    else
    {
        PlaySeqSlot_80031160(0x11, 1);
        w->handle_C = StartActionTask_800BC28C();
        w->next_8 = CmdSwapMinionLoad_800BBC84;
        task->next_8 = WaitActionTask_800BC144;
    }
}

void CmdSwapMinionLoad_800BBC84(BatTaskEntry* task)
{
    task->next_8 = CmdSummonWait_800BBCC8;
    FreeSummonedMinion_800C0BA0(task);
    LoadSummonedMinion_800C0AEC(commandUnit_800C9C98 - 1, &levantPos_8008BD18.pos.x, levantPos_8008BD18.rot.vy);
}

// waits until the summoned minion's actor is created, then starts its summon action (CreateSummonedMinionActor_800C0BF0 takes no arguments; the s3 copy of work comes from 'workCopy')
void CmdSummonWait_800BBCC8(BatTaskEntry* task, BatTurnWork* work)
{
    BatTurnWork* workCopy = work;
    if (CreateSummonedMinionActor_800C0BF0() == 1)
    {
        curCommand_800C9C88.kind_0 = 2;
        curCommand_800C9C88.targets_C = 0;
        actingUnit_800C9C7C = commandUnit_800C9C98;
        shownUnit_800C9C99 = commandUnit_800C9C98;
        summonedUnit_800C9C82 = commandUnit_800C9C98;
        curCommand_800C9C88.mask_8 = 1 << commandUnit_800C9C98;
        work->handle_C = StartActionTask_800BC28C();
        if (encounterRecord_800ADE78.active_0 == 1)
        {
            work->next_8 = BattleNextTurn_800BAE74;
        }
        else
        {
            workCopy->next_8 = BattleNextTurn_800BAE74;
            ResetTurnGauge_800BF770(turnGauges_800C9C68, actingUnit_800C9C7C);
        }
        UpdateMinionStatusTint_800C0F1C();
        task->next_8 = WaitActionTask_800BC144;
    }
}

void CmdRecall_800BBDB4(BatTaskEntry* task, BatTurnWork* work)
{
    work->handle_C = StartActionTask_800BC28C();
    work->next_8 = CmdRecallDone_800BBE00;
    task->next_8 = WaitActionTask_800BC144;
}

void CmdRecallDone_800BBE00(BatTaskEntry* task, BatTurnWork* work)
{
    actingUnit_800C9C7C = 0;
    shownUnit_800C9C99 = 0;
    summonedUnit_800C9C82 = 0;
    curCommand_800C9C88.mask_8 = 1 << commandUnit_800C9C98;
    work->handle_C = StartActionTask_800BC28C();
    work->next_8 = CmdRecallEnd_800BBE7C;
    task->next_8 = WaitActionTask_800BC144;
}

void CmdRecallEnd_800BBE7C(BatTaskEntry* task)
{
    FreeSummonedMinion_800C0BA0();
    if (TestBattleFlag_800BC820(0x100) == 1)
    {
        task->next_8 = BattleFinish_800BB1B0;
    }
    else if (GetEnemyAliveMask_800A248C() == 0)
    {
        task->next_8 = BattleNextTurn_800BAE74;
    }
    else
    {
        task->next_8 = BattleNextTurn_800BAE74;
        ResetTurnGauge_800BF770(turnGauges_800C9C68, actingUnit_800C9C7C);
    }
}

void CmdEnemyCall_800BBEFC(BatTaskEntry* task, BatTurnWork* work)
{
    work->handle_C = StartActionTask_800BC28C();
    work->next_8 = CmdEnemyCallJoin_800BBF64;
    curCommand_800C9C88.targets_C = 0;
    commandUnit_800C9C98 = curCommand_800C9C88.arg_4 + 4;
    task->next_8 = WaitActionTask_800BC144;
}

// an enemy's call for help: the called enemy joins (SwapEncounterEnemy_800A2AE8 takes no arguments; a typed '(void)' prototype keeps &curCommand_800C9C88 from becoming its argument)
void CmdEnemyCallJoin_800BBF64(BatTaskEntry* task, BatTurnWork* work)
{
    curCommand_800C9C88.kind_0 = 0x15;
    actingUnit_800C9C7C = commandUnit_800C9C98;
    curCommand_800C9C88.mask_8 = 1 << commandUnit_800C9C98;
    SwapEncounterEnemy_800A2AE8();
    work->handle_C = StartActionTask_800BC28C();
    work->next_8 = work->resume_4;
    task->next_8 = WaitActionTask_800BC144;
    ResetTurnGauge_800BF770(turnGauges_800C9C68, actingUnit_800C9C7C);
}

void CmdEnemySwap_800BBFFC(BatTaskEntry* task, BatTurnWork* work)
{
    work->handle_C = StartActionTask_800BC28C();
    work->next_8 = CmdEnemySwapJoin_800BC05C;
    commandUnit_800C9C98 = curCommand_800C9C88.arg_4 + 4;
    task->next_8 = WaitActionTask_800BC144;
}

// an enemy swaps with its partner in a fixed encounter (SwapEncounterEnemy_800A2AE8 takes no arguments)
void CmdEnemySwapJoin_800BC05C(BatTaskEntry* task, BatTurnWork* work)
{
    curCommand_800C9C88.kind_0 = 0x16;
    actingUnit_800C9C7C = commandUnit_800C9C98;
    curCommand_800C9C88.mask_8 = 1 << commandUnit_800C9C98;
    SwapEncounterEnemy_800A2AE8();
    SetBattleFlag_800BC838(0x10000);
    work->handle_C = StartActionTask_800BC28C();
    work->next_8 = work->resume_4;
    task->next_8 = WaitActionTask_800BC144;
    ResetTurnGauge_800BF770(turnGauges_800C9C68, actingUnit_800C9C7C);
}

void CmdSimple_800BC0FC(BatTaskEntry* task, BatTaskEntry* work)
{
    work->handle_C = (int*)StartActionTask_800BC28C();
    work->next_8 = work->resume_4;
    task->next_8 = WaitActionTask_800BC144;
}

void WaitActionTask_800BC144(BatTaskEntry* task, BatTaskEntry* work)
{
    if ((*work->handle_C & 0x8001) != 1)
    {
        task->next_8 = work->next_8;
    }
}

void (*GetCommandHandler_800BC174())()
{
    return commandHandlers_800C8B54[commandHandlerIdx_800C8B38[curCommand_800C9C88.kind_0]];
}

int NeedsStatusReaction_800BC1A8(unsigned int mask)
{
    int i;
    int bit;
    UnitStatus* status;
    int hitKind;
    for (i = 0; i < 7; i++)
    {
        bit = 1 << i;
        if (mask & bit)
        {
            status = GetUnitStatus_80014390(i & 0xFF);
            hitKind = (unsigned char)unitHitKinds_800C9CBC[i];
            if (hitKind != 0 && hitKind != 5 && hitKind != 6 && status->hp_8.cur_0 > 0)
            {
                if (unitStatusInflicted_800C9CA0[i] & 0x18202)
                {
                    return 1;
                }
                if (status->status_0 & 0x8000)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int StartActionTask_800BC28C()
{
    EventEntry* entry = AllocEventEntry_80043AF8(actionTask_8008B4C0);
    if (entry)
    {
        entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
        if (TestBattleFlag_800BC820(0x80000) == 1)
        {
            btlExecLoad_800C9D7C = LoadOverlay_80020BF8(1, 0x1E);
            entry->cb_8 = (EventEntryFn)WaitBtlExecLoaded_800BC324;
            ClearBattleFlag_800BC850(0x80000);
        }
        else
        {
            entry->cb_8 = (EventEntryFn)ActionStart_800BDA28;
        }
    }
    return (int)entry;
}

void WaitBtlExecLoaded_800BC324(BatTaskEntry* task, int buffer)
{
    if (GetFileRequestStatus_8003BE30(btlExecLoad_800C9D7C) == 0)
    {
        task->next_8 = ActionStart_800BDA28;
        task->next_8(task, buffer);
    }
}

int GetUnitsCenter_800BC378(unsigned int mask, Vec3i* out)
{
    Vec3i pos[7];
    Vec3i center;
    unsigned int i;
    int count;
    int bit;
    count = i = 0;
    for (; i < 7; i++)
    {
        bit = 1 << i;
        if (mask & bit)
        {
            Vec3i* unitPos = (Vec3i*)GetUnitPos_800BC6CC(i);
            if (unitPos)
            {
                pos[count].x = unitPos->x;
                pos[count].y = unitPos->y;
                pos[count].z = unitPos->z;
                count++;
            }
        }
    }
    if (count != 0)
    {
        AveragePositions_800BC5EC(&center, pos, count);
        *out = center;
        return 1;
    }
    return 0;
}

void TurnUnitsToward_800BC468(int targetMask, int unitMask)
{
    char center[0x10];
    unsigned int i;
    int bit;
    if (GetUnitsCenter_800BC378(targetMask, center))
    {
        for (i = 0; i < 7; i++)
        {
            bit = 1 << i;
            if (unitMask & bit)
            {
                TurnUnitToward_800BC4D4(i, center);
            }
        }
    }
}

void TurnUnitToward_800BC4D4(int unit, int pos)
{
    int onField = IsUnitOnField_800BC570(unit);
    if (onField == 1)
    {
        switch ((unsigned int)GetUnitSide_800BC7DC(unit))
        {
        case 0:
            TurnLevantToward_800A8D48(pos);
            break;
        case 1:
            TurnSummonedMinionToward_800C0DB0(pos);
            break;
        case 2:
            TurnEnemyToward_800A25D8(unit - 4, pos);
            break;
        default:
            break;
        }
    }
}

int IsUnitOnField_800BC570(int unit)
{
    int bit;
    if (unit == 0 && summonedUnit_800C9C82 == 0)
    {
        return 1;
    }
    if (GetPartyMinionMask_800C0A9C() & (bit = 1 << unit))
    {
        if (unit == summonedUnit_800C9C82)
        {
            return 1;
        }
    }
    return (GetEnemyAliveMask_800A248C() & (bit = 1 << unit)) != 0;
}

Vec3i* AveragePositions_800BC5EC(Vec3i* dst, Vec3i* src, unsigned int n)
{
    unsigned char i;
    Vec3i mid;
    if (n == 1)
    {
        *dst = *src;
    }
    else
    {
        n--;
        if (n)
        {
            i = 0;
            do
            {
                Vec3i* cur = &src[i];
                Midpoint3D_8003B95C(&mid, cur, &src[i + 1]);
                *cur = mid;
                i++;
            } while (i < n);
        }
        AveragePositions_800BC5EC(dst, src, n);
    }
    return dst;
}

int GetUnitPos_800BC6CC(int unit)
{
    int pos = 0;
    int summonedSide;
    if (IsUnitInBattle_800BC784(unit))
    {
        int side = GetUnitSide_800BC7DC(unit);
        switch ((unsigned int)side)
        {
        case 1:
            summonedSide = GetUnitSide_800BC7DC(summonedUnit_800C9C82);
            if (summonedSide == 0)
            {
            case 0:
                pos = (int)&levantPos_8008BD18.pos;
                break;
            }
            if (summonedSide == side)
            {
                pos = (int)GetSummonedMinionPos_800C0F9C();
            }
            break;
        case 2:
            pos = GetEnemyPos_800A2C28(unit - 4);
            break;
        }
    }
    return pos;
}

int IsUnitInBattle_800BC784(int unit)
{
    int bit;
    if (unit != 0)
    {
        if ((GetPartyMinionMask_800C0A9C() & (bit = 1 << unit)) == 0)
        {
            return (GetEnemyAliveMask_800A248C() & bit) != 0;
        }
    }
    return 1;
}

// 'side = 3' (a pseudo) and 'return 3' (v0) only become the same 'v0 = 3' after reload, too short for jump2 to merge;
// reorg then drops the redundant 'unit == 7' branch after its 'li v0,7' went into the previous branch's delay slot
int GetUnitSide_800BC7DC(int unit)
{
    int side;
    if (unit == 0)
    {
        side = 0;
    }
    else if ((unsigned int)(unit - 1) < 3)
    {
        side = 1;
    }
    else if ((unsigned int)(unit - 4) < 3)
    {
        side = 2;
    }
    else if (unit == 7)
    {
        side = 3;
    }
    else
    {
        return 3;
    }
    return side;
}

int TestBattleFlag_800BC820(unsigned int mask)
{
    return (battleFlags_800B1228 & mask) != 0;
}

void SetBattleFlag_800BC838(unsigned int mask)
{
    battleFlags_800B1228 |= mask;
}

void ClearBattleFlag_800BC850(unsigned int mask)
{
    battleFlags_800B1228 &= ~mask;
}

int GetAreaElement_800BC868()
{
    return areaElement_800C9D84;
}

void LoadStageEffects_800BC878()
{
    char buf[4];
    memset(buf, 0, 4);
    LoadEffectFile_80020DDC(battleStages_800C8EAC[battleStageId_80083BD0].effect_4, &battleEffectFile_80095468, buf, buf, 0, 0);
    stageAnimUv_800C9D8C[1] = -1;
    stageAnimUv_800C9D8C[0] = -1;
}

int AreStageEffectsLoaded_800BC8E8()
{
    return IsEffectFileLoaded_80020EBC(&battleEffectFile_80095468);
}
