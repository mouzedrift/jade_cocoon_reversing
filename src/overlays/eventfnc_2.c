// EVENTFNC.BIN, source file 2 of 2 from 0x800BCB3C (.rdata from 0x800B6D98)
#include "eventfnc.h"

const int returnWarpAreaVars_800B6D98[10] = {
    0, 0, 0, 0, 0, 5, 7, 6,
    8,
};
INCLUDE_OVERLAY_ASM(eventfnc, dword_800B6DC0);

#if 0
// Not matched: with this file's own .rdata the initializer and jump table land where the original's are;
// the code is 1 word short: case 4 keeps the saveData address in a0 (dead across the calls, recomputed
// for the stores) and shares the constant 4 of SetEventVar_800AD16C's first argument with word_8008B858 + 4
extern int fieldMode_800B0EC0;
void ReturnWarpTask_800BCB3C(TaskEventfnc* t, int* st)
{
    EvActorCmdEventfnc m;
    unsigned short v[3];
    SaveData* s;
    int k;
    switch (st[0])
    {
    case 0:
        SuspendAllEnemySlots_800A1904();
        HoldLevantControl_800A8E0C();
        sub_800A8DEC();
        LoadLevantAnimById_800AC604(st[1], 0);
        st[0] = 1;
        break;
    case 1:
        if (AreLevantFilesLoaded_800AC768())
        {
            st[0] = 2;
        }
        break;
    case 2:
        if (IsLevantControlHeld_800A8E7C())
        {
            st[0] = 3;
        }
        break;
    case 3:
        if (sub_800A8FE0())
        {
            m.actor_0 = 0;
            m.kind_4 = 9;
            m.field_8 = 0;
            m.arg_C = st[1];
            m.arg2_10 = 0;
            m.field_14 = 1;
            LevantCommand_800A8EC4((int*)&m);
            StartSceneDarken_8001AAA8(0x3C);
            st[0] = 4;
        }
        break;
    case 4:
        if (IsSceneFadeDone_8001AB94())
        {
            FreeLevantAnimById_800AC6A8(st[1]);
            ReleaseLevantControl_800A8E38();
            s = &saveData_8008B570;
            if (s->mapId_2E4[0].field_0 == 4 && s->mapId_2E4[1].field_0 == 0 && mapTable_800B0608[4][0][s->mapId_2E4[2].field_0].f4_4 == 0)
            {
                int tbl2[9] = {0, 0, 0, 0, 0, 5, 7, 6, 8};
                k = tbl2[pendingArea_8008B860];
            }
            else
            {
                k = word_8008B858 + 4;
            }
            SetEventVar_800AD16C(4, k);
            FindMapEntrance_800ADCEC(v, GetSetReturnEntrance_800A683C(-1));
            forceMapReload_80091C9C = 1;
            useMapStartPos_80091C94 = 1;
            dword_80091C54 = 0;
            dword_80091C8C = 0;
            fieldMode_800B0EC0 = 1;
            s = &saveData_8008B570;
            s->mapId_2E4[3].field_0 = 0;
            s->mapId_2E4[0].field_0 = v[0];
            s->mapId_2E4[1].field_0 = v[1];
            s->mapId_2E4[2].field_0 = v[2];
            unknownFlags_8008D678 &= ~0x20000;
            t->next_8 = FieldModeTask_800A7720;
        }
        break;
    }
}
#endif

INCLUDE_OVERLAY_ASM(eventfnc, ReturnWarpTask_800BCB3C);


int (*eventFuncs_800BCDBC[157])() = {
    EvCmdNop_800B89A8, EvCmdWaitButton_800B89C0, EvCmdNop_800B89A8, EvCmdEnd_800B89F4,
    (int (*)())EvCmdEndScene_800B8A34, (int (*)())EvCmdBeginScene_800B8BE8, EvCmdSetLoopPoint_800B8CB0, EvCmdTakeActors_800B8D08,
    EvCmdReleaseActors_800B8DDC, EvCmdNop_800B89A8, EvCmdGotoLabel_800B8E9C, EvCmdJumpScript_800B8F14,
    EvCmdWait_800B8F44, EvCmdWaitActors_800B8F88, EvCmdSetVar_800B8FB8, EvCmdPickBranch_800B9020,
    EvCmdCountYanVar_800B9110, EvCmdCallHook_800B91CC, EvCmdStartScript_800B9218, EvCmdWarpActor_800B9260,
    EvCmdMoveToPoint_800B93A8, EvCmdMoveToActor_800B942C, EvCmdMoveToPoint_800B93A8, EvCmdMoveToActor_800B942C,
    EvCmdTurnToPoint_800B95BC, EvCmdTurnToActor_800B962C, EvCmdSetActorVisible_800B96D8, EvCmdSetActorGroundMove_800B9720,
    EvCmdSetActorRootMotion_800B9768, EvCmdSaveActorPos_800B97B0, EvCmdSaveActorFront_800B97F8, EvCmdTestFlag_800B9840,
    EvCmdSetFlag_800B98C4, EvCmdClearFlag_800B990C, EvCmdTestTempFlags_800B9954, EvCmdSetTempFlags_800B99D8,
    EvCmdClearTempFlags_800B9A20, EvCmdAddItem_800B9A68, EvCmdRemoveItem_800B9AB4, EvCmdAddItemCat1_800B9B00,
    EvCmdRemoveItemCat1_800B9B4C, (int (*)())EvCmdWaitTrigger_800B9B98, EvCmdAddMoney_800B9CC0, EvCmdAddEmptyCocoons_800B9D08,
    EvCmdHealParty_800B9D50, EvCmdSetValuable_800B9C5C, EvCmdSetEntityState_800B9DE0, EvCmdWaitEntityState_800B9E48,
    EvCmdSetOwnEntityState_800B9EB0, EvCmdWaitOwnEntityState_800B9EDC, EvCmdWaitEntityGone_800B9F0C, EvCmdSetMsgOptions_800B9F5C,
    EvCmdSetMsgPos_800B9F84, EvCmdSetMsgPosMode_800B9FB4, EvCmdSetVoiceTable_800B9FD8, EvCmdMessage_800BA020,
    EvCmdMessage_800BA020, EvCmdMessage_800BA020, EvCmdMessage_800BA020, EvCmdMessage_800BA020,
    EvCmdMessage_800BA020, EvCmdMessage_800BA020, EvCmdMessage_800BA020, EvCmdMessage_800BA020,
    EvCmdNop_800B89A8, EvCmdSwapMsgAfterCount_800BA1DC, EvCmdWaitMsgMark_800BA238, EvCmdSetChoiceMask_800BA28C,
    EvCmdPlayAnim_800BA2E8, EvCmdStopAnim_800BA338, EvCmdPlayAnimData_800BA40C, EvCmdPauseActorAnim_800BA45C,
    EvCmdPlayMotion_800BA4F0, EvCmdPlayMotionRange_800BA554, EvCmdPlayMotionData_800BA5CC, EvCmdSetCallArg_800BA678,
    EvCmdSetCallArgs_800BA6D0, EvCmdCallUntilDone_800BA714, EvCmdCallSelect_800BA7A4, (int (*)())EvCmdSetChapter_800BA82C,
    sub_800BA880, EvCmdSetMapVar_800BA8AC, EvCmdChangeMap_800BA930, EvCmdChangeMapToPoint_800BA9E4,
    EvCmdNop_800B89A8, EvCmdPreloadArea_800BAA6C, EvCmdUsePreloadedArea_800BAAC0, EvCmdSetReturnPoint_800BAB14,
    (int (*)())EvCmdOpenMapSelect_800BAB5C, EvCmdOpenShop_800BABB0, EvCmdCameraLookAtPoint_800BAC60, EvCmdCameraLookAtActor_800BACE0,
    EvCmdCameraClearLookAt_800BAD3C, EvCmdWaitCameraBlend_800BAD88, EvCmdSetViewRect_800BADF8, EvCmdSetCameraZoom_800BAEBC,
    EvCmdSetCameraTarget_800BAF08, EvCmdSetMapMesh_800BAF68, EvCmdWaitTalk_800BAFAC, EvCmdSetIdleAnim_800BB180,
    EvCmdWaitActorInRegion_800BB214, (int (*)())EvCmdBattle_800BB27C, EvCmdIfBattleResult_800BB45C, EvCmdFadeSound_800BB4A4,
    EvCmdPadVibration_800BB7D8,
};
