// EVENTFNC.BIN: declarations shared by its source files
// EVENTFNC.BIN
#include "common.h"

#include "funcs.h"

#include "globals.h"
#include "model.h"
#include "engine.h"
#include "minion_init.h"

// one event script instruction: op_0 indexes eventFuncs_800BCDBC (GAME's RunEventScript_800A6060 runs them until one returns 0)
typedef struct EvInsEventfnc
{
    int op_0;
    int a_4;
    int b_8;
    int c_C;
} EvInsEventfnc;

typedef struct EvVecEventfnc
{
    int x_0;
    int y_4;
    int z_8;
} EvVecEventfnc;

typedef struct EvEntEventfnc
{
    char pad_0[0x48];
    EvVecEventfnc pos_48;
    char pad_54[0x28];
    int f7C_7C;
    int f80_80;
    int f84_84;
    int f88_88;
    int f8C_8C;
} EvEntEventfnc;



// an event script (GAME's GameEvCtx, list eventScripts_8008D410)
typedef struct EvCtxEventfnc
{
    unsigned int flags_0; // 1 ended, 2 message advancing, 4 triggered, 8 waiting for a trigger, 0x10 loop point set,
                          // 0x20 holds the scene, 0x40 message kept open, 0x100 XA voice playing
    EvInsEventfnc* start_4;
    EvInsEventfnc* pc_8;
    EvInsEventfnc* ret_C;
    int id_10;
    int heldActors_14; // actors (bit 0 Levant, 1..4 party) taken by EvCmdTakeActors_800B8D08
    int busyActors_18; // actors still running an actor command
    int animActors_1C; // actors playing a held animation (EvCmdPlayAnim_800BA2E8)
    char pad_20[4];
    int idleAnims_24[6]; // per actor animation restored at the end; [5]: SendActorCmdMask_800BB990's pending mask
    EvVecEventfnc savedPos_3C[5];
    EvVecEventfnc savedFront_78[5];
    int msgStep_B4;
    int step_B8;
    int maskStep_BC;
    int cmdStep_C0;
    unsigned int waitCount_C4;
    int trigger_C8; // the trigger id waited for (EvCmdWaitTrigger_800B9B98, GAME's FireEventTrigger_800A5C40)
    int vars_CC[8]; // script local variables (EvCmdSetVar_800B8FB8)
    int branch_EC; // the selected branch: choice / test / random result, indexes the goto / jump instructions
    int callArg_F0;
    int callArg0_F4;
    int callArg1_F8;
    int callArg2_FC;
    unsigned short msgX_100;
    unsigned short msgY_102;
    int msgPosMode_104;
    int msgOptions_108;
    char pad_10C[4];
    int* lastMsg_110;
    int choiceMask_114;
    int msgOpen_118;
    int msgWindow_11C; // the message window (OpenMessageWindow_8003422C)
    EvEntEventfnc* ent_120;
} EvCtxEventfnc;

// an actor command (GAME's G2Cmd_1): kind 0 walk / 1 run / 2 turn to x/y/z, 3 / 4 play / stop a held animation,
// 5 play animation data, 6 visible, 7 ground move, 8 root motion, 9..11 play a motion
typedef struct EvActorCmdEventfnc
{
    int actor_0;
    int kind_4;
    int field_8;
    int arg_C;
    int arg2_10;
    int field_14;
    int x_18;
    int y_1C;
    int z_20;
    int data_24;
} EvActorCmdEventfnc;

typedef struct EvObjEventfnc
{
    char pad_0[0x1A];
    short f1A_1A;
    char pad_1C[0x90 - 0x1C];
    int f90_90;
} EvObjEventfnc;

typedef struct EvQuadEventfnc
{
    short x_0;
    short y_2;
    short z_4;
    short pad_6;
} EvQuadEventfnc;

extern EvVecEventfnc* GetSavedActorPos_800BBC00(EvCtxEventfnc* c, int a, int b);

extern EvVecEventfnc* GetSavedActorFront_800BBC80(EvCtxEventfnc* c, int a, int b);

extern EvVecEventfnc* GetActorPos_800BBBA0(int a);

extern int SendActorCmd_800BB840(EvCtxEventfnc* c, EvActorCmdEventfnc* m, int a, int b);

extern int SendActorCmdMask_800BB990(EvCtxEventfnc* c, EvActorCmdEventfnc* m, int a, int b);

extern void SetTempFlags_800BBDA0(int a, int b);

extern int TestTempFlags_800BBDD8(int a);

extern char eventHeap_80091C10[];

// the low halves of cameraEye_8008D600 (VECTOR camera eye), read with lhu by IsActorLeftOf_800BC5C8
extern unsigned short word_8008D600[];

extern int sceneScriptId_800AEBD8;

extern void LoadEncounterModels_800B8940(int* ids);

extern void RequestLoaderModel_800206A0(int a, int b, int c, int d);

extern void StartModelLoader_8002056C(void);




extern int CollideWithMapEnts_800B82C8(int* p, int* a1, MapMesh* ents, unsigned char* flags, int n);

extern void SlideOffEdge_800B8220(int* p, int a1, int a2, int* a3, int* a4, int* a5);

extern int FindDuplicatePoint_800B8028(int* out, EvQuadEventfnc* v);

extern void GetTriHeight_800B83E4(int* v, MapMesh* m, int i);

static inline int EvFindTri(int* out, MapState* map, EvVecEventfnc* pos)
{
    int r = FindTriAtXZ_800B76B8(map->mesh_28, pos);
    if (r >= 0)
    {
        *out = r;
        return 1;
    }
    return 0;
}

extern int FindTriAtXZ_800B76B8(MapMesh* m, EvVecEventfnc* pos);

// FindLevantMesh_800B80C8, inlined into CollideLevantWithMap_800B6DD4
static inline int EvFindLevantMesh(EvEntEventfnc* e)
{
    unsigned int i;
    unsigned int k = e->f84_84;
    int r;
    for (i = 0; i < mapState_8008B500.nMeshes_4; i++, k++)
    {
        k %= mapState_8008B500.nMeshes_4;
        r = FindTriAtXZ_800B76B8(&mapState_8008B500.meshes_C[k], (EvVecEventfnc*)&levantPos_8008BD18.pos);
        if (r >= 0)
        {
            e->f80_80 = r;
            if (e->f84_84 != k)
            {
                e->f84_84 = k;
            }
            return 1;
        }
    }
    return 0;
}

extern void FindCrossedEdge_800B79E0(MapMesh* m, int* p, int* q, int* tri, int* edge);

extern void SlideAlongEdge_800B7E40(int* p, int a, int b, int c, int* d);

typedef struct EvMapEntEventfnc
{
    short id_0;
    char pad_2[2];
    short f4_4;
    unsigned short f6_6;
    char pad_8[8];
} EvMapEntEventfnc;

typedef struct EvPairEventfnc
{
    int a;
    int b;
} EvPairEventfnc;
typedef struct EvPosEventfnc
{
    EvPairEventfnc xy;
    int z;
} EvPosEventfnc;
// where an encounter's actor is placed
typedef struct EvPlaceEventfnc
{
    int pos_0[3];
    short rotY_C;
} EvPlaceEventfnc;
typedef struct EvSpawnEventfnc
{
    EvPosEventfnc* a_0[3];
    EvPlaceEventfnc* b_C[3];
    short f18_18;
    short f1A_1A;
} EvSpawnEventfnc;

extern EvMapEntEventfnc** mapTable_800B0608[];

extern int RollEncounterGroups_800A49CC(int a, int b, MapList16* c, EvSpawnEventfnc* d);

extern void SpawnEncounterEnemy_800B8568();

extern EventNode* encounterTask_8008D674;

extern void ResetEncounter_800A170C();

extern void ClearEnemySlots_800A1794();

extern void EncounterSpawnTask_800B844C();

extern unsigned short padPressed_8009194C;

extern int EvCmdEndScene_800B8A34(EvCtxEventfnc* c);

extern void ResumeAllEnemySlots_800A1974(void);

extern void ResetEventCtx_800A5B54(EvCtxEventfnc* c);

extern int HoldFieldMinion_800A7810(int a);

extern void HoldLevantControl_800A8E0C(void);

extern void ResetLevantActorToIdle_800A8DEC(void);

extern void ReleaseLevantControl_800A8E38(void);

extern void ReleaseFieldMinion_800A785C(int a);

extern int SetEventVar_800AD16C(int a, int b);

extern int GetEventVar_800AD154(int a);

extern void (*eventHook_800B1D98)(int);

extern int StartEventScript_800A59D0(int a);

extern SVECTOR* GetActorRot_800BBBD0(int i); // rotation of Levant (0) or a party member

extern short screenOffset_8008D474[2];

extern void UpdateCameraFollow_80037918(void* p);

extern void SetGeomOffset(long ofx, long ofy);

extern short name_80084540[];

extern int TestEventFlag_800AD0D4(int a);

extern void SetEventFlag_800AD0F8(int a);

extern void ClearEventFlag_800AD124(int a);

extern int AddInventory_800AD184(int a, int b, int c);

extern int RemoveInventory_800AD1E0(int a, int b, int c);

extern int TestValuableFlag_800AD73C(int a);

extern int SetValuableFlag_800AD68C(int a);

extern int ClearValuableFlag_800AD6E4(int a);

extern int AddMoney_800AD058(int a);

extern int AddEmptyCocoons_800AD8F4(int a);

extern UnitStatus* GetLevantStatus_800A8C34();





extern EvEntEventfnc* FindEventEntity_800A5DDC(int a, int b, int c);

extern void SetVoiceTable_800A6830(int a);

extern void EvMessageNop_800BC7A0(EvCtxEventfnc* c);

extern int OpenEventMessage_800BBE3C(EvCtxEventfnc* c);

extern int UpdateEventMessage_800BC2B4(EvCtxEventfnc* c);

extern int XaRequestStop_80043524(void);

extern int ConsumeMsgWindowMark_80034ADC(int a, int b);

extern EvObjEventfnc* GetFieldMinionActor_800A7A60(int a);

extern void* GetEventDataSlot_800A55B0(int a);

extern int useMapStartPos_80091C94;

extern int eventDispatchHalt_8008B540;

extern int RequestGameMode_800A6D30(int a);

extern void SetMapVar_800ADC5C(unsigned short* v, int a);

extern void FindMapEntrance_800ADCEC(unsigned short* v, int a);

extern int forceMapReload_80091C9C;

extern int dword_80091C54;

extern int UsePreloadedArea_80027358(int a);

extern int GetSetReturnEntrance_800A683C(int a);

typedef struct EvWaitEventfnc
{
    int f0_0;
    int f4_4;
    int f8_8;
} EvWaitEventfnc;

extern EvWaitEventfnc shopRequest_800B06B0;

extern int ExchangeEventResult_800A5F9C(int a);

extern void SetCameraBlendTarget_800379DC(EvVecEventfnc* v, int b);

extern void ClearCameraBlendTarget_80037A20(int a, int b);

typedef struct EvRectEventfnc
{
    short x_0;
    short y_2;
    short w_4;
    short h_6;
} EvRectEventfnc;

extern EvRectEventfnc dword_8008D420;

extern void SetCameraZoom_80037A6C(int a, int b);

extern int GetFieldMinionCount_800A7790(void);

extern int IsWithinDistance_8003B740(int* a, int* b, unsigned int* c);

extern int IsEventPointValid_800A6504(int a, EvVecEventfnc* v);

extern int dword_800B1230;

extern void StartPadVibration_80036528(int a, int b);

extern void StopPadVibration_80036658(int a);

extern int IsActorCmdReady_800BBAB0(int i);

extern int IsActorCmdDone_800BBAE4(int i);

extern int StartActorCmd_800BBB18(int* p);

extern int FinishActorCmd_800BBB5C(int* p);

extern int IsLevantControlHeld_800A8E7C();

extern int IsFieldMinionIdle_800A7CB8(int a);

extern int IsLevantCmdDone_800A8FE0();

extern int IsFieldMinionReady_800A7CFC(int a);

extern EvVecEventfnc* GetFieldMinionPos_800A7940(int a);


extern SVECTOR* GetFieldMinionRot_800A7984(int a);

extern int eventTempFlags_800AEBD4;

typedef struct EvMsgInfoEventfnc
{
    short f0_0;
    short s2_2;
    int f4_4;
    int f8_8;
    int fC_C;
} EvMsgInfoEventfnc;

typedef struct EvXaEventfnc
{
    short a_0;
    short b_2;
    short c_4;
} EvXaEventfnc;

typedef struct EvVoiceEventfnc
{
    unsigned char id_0;
    unsigned char sub_1;
    EvXaEventfnc xa_2;
} EvVoiceEventfnc;

extern int GetMsgWindowResultIfDone_800349B4(int a, EvMsgInfoEventfnc* b);

extern void SkipActorAnims_800A67B4(EvCtxEventfnc* c);

extern void CloseMsgWindow_80034A84(int a);

extern int IsMsgWindowWaiting_80034A30(int a);

extern void EnableMsgWindowAdvance_80034A68(int a);

extern int currentMessageId_800AEBE8;

extern EvXaEventfnc* currentVoice_800AEBEC;

extern EvVoiceEventfnc* voiceTable_800AEBF0;


extern void sub_8005BBC8();

typedef struct EvSrcEventfnc
{
    short a_0;
    short b_2;
    int c_4;
} EvSrcEventfnc;

typedef struct EvSlotEventfnc
{
    int f0_0;
    int f4_4;
    int f8_8;
    int fC_C;
    int f10_10;
} EvSlotEventfnc;

extern void memset(void* p, int v, int n);

typedef struct EvGfxEventfnc
{
    int f0_0;
    int f4_4;
    char pad_8[0x24];
    int f2C_2C;
} EvGfxEventfnc;

typedef struct EvGfxArgEventfnc
{
    EvGfxEventfnc* g_0;
    short s_4[6];
    int f10_10;
} EvGfxArgEventfnc;

extern int mdecBufferMode_800AEB7C;

extern EvGfxEventfnc eventEffects_800AEB80;

extern void FreeMdecBuffer_800A5854(void);

extern void AllocMdecBuffer_800A5804(int a);

extern void OnEffectFileLoaded_80020F5C(EvGfxArgEventfnc* p, int a);

// sprites / tpages of the TIY loaded by LoadEventTiy_800BC98C
typedef struct
{
    SPRT* sprts_0;
    DR_TPAGE* tpages_4;
} EvTiyEventfnc;
extern EvTiyEventfnc eventTiy_800AEBC0;

extern int eventRecords_800AEBCC[2];

extern void FreeRecordTables_80026DE8(int* a, int b, void* c);

extern void AllocRecordTables_80026D78(int* a, int b, void* c);

extern void LoadRecordTables_80026E74(int a, int b, void* c);

typedef struct TaskEventfnc
{
    unsigned int flags_0;
    int f4_4;
    void (*next_8)();
} TaskEventfnc;

extern void ReturnWarpTask_800BCB3C();

extern void LoadLevantAnimById_800AC604(int a, int b);

extern int AreLevantFilesLoaded_800AC768(void);

extern void FreeLevantAnimById_800AC6A8(int a);

extern int IsSceneFadeDone_8001AB94(void);

extern void StartSceneDarken_8001AAA8(int a);

extern int LevantCommand_800A8EC4(int* p);

extern void FieldModeTask_800A7720();

extern short word_8008B858;

extern short pendingArea_8008B860;

extern int dword_80091C8C;

extern void EvCmdBeginScene_800B8BE8();
extern void EvCmdWaitTrigger_800B9B98();
extern void EvCmdSetChapter_800BA82C();
extern void sub_800BAB5C();
extern void EvCmdBattle_800BB27C();
extern int EvCmdNop_800B89A8();
extern int EvCmdWaitButton_800B89C0();
extern int EvCmdEnd_800B89F4();
extern int EvCmdSetLoopPoint_800B8CB0();
extern int EvCmdTakeActors_800B8D08();
extern int EvCmdReleaseActors_800B8DDC();
extern int EvCmdGotoLabel_800B8E9C();
extern int EvCmdJumpScript_800B8F14();
extern int EvCmdWait_800B8F44();
extern int EvCmdWaitActors_800B8F88();
extern int EvCmdSetVar_800B8FB8();
extern int EvCmdPickBranch_800B9020();
extern int EvCmdCountYanVar_800B9110();
extern int EvCmdCallHook_800B91CC();
extern int EvCmdStartScript_800B9218();
extern int EvCmdWarpActor_800B9260();
extern int EvCmdMoveToPoint_800B93A8();
extern int EvCmdMoveToActor_800B942C();
extern int EvCmdTurnToPoint_800B95BC();
extern int EvCmdTurnToActor_800B962C();
extern int EvCmdSetActorVisible_800B96D8();
extern int EvCmdSetActorGroundMove_800B9720();
extern int EvCmdSetActorRootMotion_800B9768();
extern int EvCmdSaveActorPos_800B97B0();
extern int EvCmdSaveActorFront_800B97F8();
extern int EvCmdTestFlag_800B9840();
extern int EvCmdSetFlag_800B98C4();
extern int EvCmdClearFlag_800B990C();
extern int EvCmdTestTempFlags_800B9954();
extern int EvCmdSetTempFlags_800B99D8();
extern int EvCmdClearTempFlags_800B9A20();
extern int EvCmdAddItem_800B9A68();
extern int EvCmdRemoveItem_800B9AB4();
extern int EvCmdAddItemCat1_800B9B00();
extern int EvCmdRemoveItemCat1_800B9B4C();
extern int EvCmdSetValuable_800B9C5C();
extern int EvCmdAddMoney_800B9CC0();
extern int EvCmdAddEmptyCocoons_800B9D08();
extern int EvCmdHealParty_800B9D50();
extern int EvCmdSetEntityState_800B9DE0();
extern int EvCmdWaitEntityState_800B9E48();
extern int EvCmdSetOwnEntityState_800B9EB0();
extern int EvCmdWaitOwnEntityState_800B9EDC();
extern int EvCmdWaitEntityGone_800B9F0C();
extern int EvCmdSetMsgOptions_800B9F5C();
extern int EvCmdSetMsgPos_800B9F84();
extern int EvCmdSetMsgPosMode_800B9FB4();
extern int EvCmdSetVoiceTable_800B9FD8();
extern int EvCmdMessage_800BA020();
extern int EvCmdSwapMsgAfterCount_800BA1DC();
extern int EvCmdWaitMsgMark_800BA238();
extern int EvCmdSetChoiceMask_800BA28C();
extern int EvCmdPlayAnim_800BA2E8();
extern int EvCmdStopAnim_800BA338();
extern int EvCmdPlayAnimData_800BA40C();
extern int EvCmdPauseActorAnim_800BA45C();
extern int EvCmdPlayMotion_800BA4F0();
extern int EvCmdPlayMotionRange_800BA554();
extern int EvCmdPlayMotionData_800BA5CC();
extern int EvCmdSetCallArg_800BA678();
extern int EvCmdSetCallArgs_800BA6D0();
extern int EvCmdCallUntilDone_800BA714();
extern int EvCmdCallSelect_800BA7A4();
extern int sub_800BA880();
extern int EvCmdSetMapVar_800BA8AC();
extern int EvCmdChangeMap_800BA930();
extern int EvCmdChangeMapToPoint_800BA9E4();
extern int EvCmdPreloadArea_800BAA6C();
extern int EvCmdUsePreloadedArea_800BAAC0();
extern int EvCmdSetReturnPoint_800BAB14();
extern int EvCmdOpenShop_800BABB0();
extern int EvCmdCameraLookAtPoint_800BAC60();
extern int EvCmdCameraLookAtActor_800BACE0();
extern int EvCmdCameraClearLookAt_800BAD3C();
extern int EvCmdWaitCameraBlend_800BAD88();
extern int EvCmdSetViewRect_800BADF8();
extern int EvCmdSetCameraZoom_800BAEBC();
extern int EvCmdSetCameraTarget_800BAF08();
extern int EvCmdSetMapMesh_800BAF68();
extern int EvCmdWaitTalk_800BAFAC();
extern int sub_800BB180();
extern int EvCmdWaitActorInRegion_800BB214();
extern int sub_800BB45C();
extern int EvCmdFadeSound_800BB4A4();
extern int EvCmdPadVibration_800BB7D8();

extern int dword_800B6D00;
extern const char aAssertionFaile_800B6D04[];
extern const char aColiC_800B6D2C[8];
extern const int returnWarpAreaVars_800B6D98[10];
extern int (*eventFuncs_800BCDBC[157])();
