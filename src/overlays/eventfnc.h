// EVENTFNC.BIN: declarations shared by its source files
// EVENTFNC.BIN
#include "common.h"

#include "funcs.h"

#include "globals.h"
#include "model.h"
#include "engine.h"
#include "minion_init.h"
#include "sound.h"

// one event script instruction: op_0 indexes eventFuncs_800BCDBC (GAME's RunEventScript_800A6060 runs them until one returns 0)
typedef struct EvInstr
{
    int op_0;
    int a_4;
    int b_8;
    int c_C;
} EvInstr;

typedef struct EvVec
{
    int x_0;
    int y_4;
    int z_8;
} EvVec;

typedef struct EvEntity
{
    char pad_0[0x48];
    EvVec pos_48;
    char pad_54[0x28];
    int f7C_7C;
    int f80_80;
    int f84_84;
    int f88_88;
    int f8C_8C;
} EvEntity;



// an event script (GAME's GameEvCtx, list eventScripts_8008D410)
typedef struct EvScriptCtx
{
    unsigned int flags_0; // 1 ended, 2 message advancing, 4 triggered, 8 waiting for a trigger, 0x10 loop point set,
                          // 0x20 holds the scene, 0x40 message kept open, 0x100 XA voice playing
    EvInstr* start_4;
    EvInstr* pc_8;
    EvInstr* ret_C;
    int id_10;
    int heldActors_14; // actors (bit 0 Levant, 1..4 party) taken by EvCmdTakeActors_800B8D08
    int busyActors_18; // actors still running an actor command
    int animActors_1C; // actors playing a held animation (EvCmdPlayAnim_800BA2E8)
    char pad_20[4];
    int idleAnims_24[6]; // per actor animation restored at the end; [5]: SendActorCmdMask_800BB990's pending mask
    EvVec savedPos_3C[5];
    EvVec savedFront_78[5];
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
    short msgX_100;
    short msgY_102;
    int msgPosMode_104;
    int msgOptions_108;
    char pad_10C[4];
    int* lastMsg_110;
    int choiceMask_114;
    int msgOpen_118;
    int msgWindow_11C; // the message window (OpenMessageWindow_8003422C)
    EvEntity* ent_120;
} EvScriptCtx;

// an actor command (GAME's GameActorCmd): kind 0 walk / 1 run / 2 turn to x/y/z, 3 / 4 play / stop a held animation,
// 5 play animation data, 6 visible, 7 ground move, 8 root motion, 9..11 play a motion
typedef struct EvActorCmd
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
} EvActorCmd;

typedef struct EvSVec
{
    short x_0;
    short y_2;
    short z_4;
    short pad_6;
} EvSVec;

extern EvVec* GetSavedActorPos_800BBC00(EvScriptCtx* ctx, int idx, int mode);

extern EvVec* GetSavedActorFront_800BBC80(EvScriptCtx* ctx, int idx, int mode);

extern EvVec* GetActorPos_800BBBA0(int actor);

extern int SendActorCmd_800BB840(EvScriptCtx* ctx, EvActorCmd* cmd, int a, int b);

extern int SendActorCmdMask_800BB990(EvScriptCtx* ctx, EvActorCmd* cmd, int a, int b);

extern void SetTempFlags_800BBDA0(int mask, int on);

extern int TestTempFlags_800BBDD8(int mask);

extern char eventHeap_80091C10[];

// the low halves of cameraEye_8008D600 (VECTOR camera eye), read with lhu by IsActorLeftOf_800BC5C8
extern unsigned short word_8008D600[];

extern int sceneScriptId_800AEBD8;

extern void LoadEncounterModels_800B8940(int* ids);

extern void RequestLoaderModel_800206A0(int a, int b, int c, int d);

extern void StartModelLoader_8002056C(void);




extern int CollideWithMapEnts_800B82C8(int* pos, int* prevPos, MapMesh* ents, unsigned char* flags, int n);

extern void SlideOffEdge_800B8220(int* pos, int prevPos, int mesh, int* tri, int* edge, int* dir);

extern int FindDuplicatePoint_800B8028(int* out, EvSVec* pts);

extern void GetTriHeight_800B83E4(int* pos, MapMesh* mesh, int triIdx);

int FindTriAtXZ_800B76B8(MapMesh* mesh, EvVec* pos);

static inline int EvFindTri(int* out, MapState* map, EvVec* pos)
{
    int tri = FindTriAtXZ_800B76B8(map->mesh_28, pos);
    if (tri >= 0)
    {
        *out = tri;
        return 1;
    }
    return 0;
}

extern int FindTriAtXZ_800B76B8(MapMesh* mesh, EvVec* pos);

// FindLevantMesh_800B80C8, inlined into CollideLevantWithMap_800B6DD4
static inline int EvFindLevantMesh(EvEntity* ent)
{
    unsigned int i;
    unsigned int mesh = ent->f84_84;
    int tri;
    for (i = 0; i < mapState_8008B500.nMeshes_4; mesh++, i++)
    {
        mesh %= mapState_8008B500.nMeshes_4;
        tri = FindTriAtXZ_800B76B8(&mapState_8008B500.meshes_C[mesh], (EvVec*)&levantPos_8008BD18.pos);
        if (tri >= 0)
        {
            ent->f80_80 = tri;
            if (ent->f84_84 != mesh)
            {
                ent->f84_84 = mesh;
            }
            return 1;
        }
    }
    return 0;
}

extern void FindCrossedEdge_800B79E0(MapMesh* m, int* p, int* q, int* tri, int* edge);

extern void SlideAlongEdge_800B7E40(int* pos, int mesh, int tri, int edge, int* out);

typedef struct EvMapEntry
{
    short id_0;
    char pad_2[2];
    short f4_4;
    unsigned short f6_6;
    char pad_8[8];
} EvMapEntry;

// an enemy group member of an encounter (GAME's GameEnemyMember)
typedef struct EvEnemyMember
{
    int species_0;
    int b;
} EvEnemyMember;
typedef struct EvEncounterMember
{
    EvEnemyMember member_0;
    int z;
} EvEncounterMember;
// where an encounter's actor is placed
typedef struct EvSpawnPlace
{
    int pos_0[3];
    short rotY_C;
} EvSpawnPlace;
typedef struct EvSpawnTable
{
    EvEncounterMember* members_0[3];
    EvSpawnPlace* places_C[3];
    short f18_18;
    short f1A_1A;
} EvSpawnTable;

extern EvMapEntry** mapTable_800B0608[];

extern int RollEncounterGroups_800A49CC(int a, int b, MapList16* c, EvSpawnTable* d);

extern void SpawnEncounterEnemy_800B8568();

extern EventNode* encounterTask_8008D674;

extern void ResetEncounter_800A170C();

extern void ClearEnemySlots_800A1794();

extern void EncounterSpawnTask_800B844C();

extern unsigned short padPressed_8009194C;

extern int EvCmdEndScene_800B8A34(EvScriptCtx* ctx);

extern void ResumeAllEnemySlots_800A1974(void);

extern void ResetEventCtx_800A5B54(EvScriptCtx* ctx);

extern int HoldFieldMinion_800A7810(int a);

extern void HoldLevantControl_800A8E0C(void);

extern void ResetLevantActorToIdle_800A8DEC(void);

extern void ReleaseLevantControl_800A8E38(void);

extern void ReleaseFieldMinion_800A785C(int a);

extern int SetEventVar_800AD16C(int a, int b);

extern int GetEventVar_800AD154(int a);

extern void (*eventHook_800B1D98)(int);

extern int StartEventScript_800A59D0(int a);

extern SVECTOR* GetActorRot_800BBBD0(int actor); // rotation of Levant (0) or a party member

extern short screenOffset_8008D474[2];

extern void UpdateCameraFollow_80037918(void* p);

extern void SetGeomOffset(long ofx, long ofy);

extern short sinTable_80084540[];

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





extern EvEntity* FindEventEntity_800A5DDC(int a, int b, int c);

extern void SetVoiceTable_800A6830(int a);

extern void EvMessageNop_800BC7A0(EvScriptCtx* ctx);

extern int OpenEventMessage_800BBE3C(EvScriptCtx* ctx);

extern int UpdateEventMessage_800BC2B4(EvScriptCtx* ctx);

extern int XaRequestStop_80043524(void);

extern int ConsumeMsgWindowMark_80034ADC(int a, int b);

extern struct Actor* GetFieldMinionActor_800A7A60(int i);

extern void* GetEventDataSlot_800A55B0(int a);

extern int useMapStartPos_80091C94;

extern int eventDispatchHalt_8008B540;

extern void RequestGameMode_800A6D30(int mode);

extern void SetMapVar_800ADC5C(unsigned short* v, int a);

extern void FindMapEntrance_800ADCEC(unsigned short* v, int a);

extern int forceMapReload_80091C9C;

extern int mapStartMode_80091C54;

extern int UsePreloadedArea_80027358(int a);

extern int GetSetReturnEntrance_800A683C(int a);

typedef struct EvShopRequest
{
    int pending_0; // set by EvCmdOpenShop_800BABB0, cleared by GAME when the shop closes
    int kind_4;    // 0 / 1 SHOP, 2 WPNSHOP, else SHOPCTRL (GAME's StartShopRequest_800A7204)
    int shopId_8;
} EvShopRequest;

extern EvShopRequest shopRequest_800B06B0;

extern int ExchangeEventResult_800A5F9C(int a);

extern void SetCameraBlendTarget_800379DC(EvVec* v, int b);

extern void ClearCameraBlendTarget_80037A20(int a, int b);

typedef struct EvViewRect
{
    short x_0;
    short y_2;
    short w_4;
    short h_6;
} EvViewRect;

extern EvViewRect viewport_8008D420;

extern void SetCameraZoom_80037A6C(int a, int b);

extern int GetFieldMinionCount_800A7790(void);

extern int IsWithinDistance_8003B740(int* a, int* b, unsigned int* c);

extern int IsEventPointValid_800A6504(int a, EvVec* v);

extern int battleResult_800B1230;

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

extern EvVec* GetFieldMinionPos_800A7940(int a);


extern SVECTOR* GetFieldMinionRot_800A7984(int a);

extern int eventTempFlags_800AEBD4;

typedef struct EvMsgResult
{
    short f0_0;
    short choice_2;
    int f4_4;
    int f8_8;
    int fC_C;
} EvMsgResult;

typedef struct EvXaClip
{
    short a_0;
    short b_2;
    short c_4;
} EvXaClip;

typedef struct EvVoiceCue
{
    unsigned char id_0;
    unsigned char sub_1;
    EvXaClip xa_2;
} EvVoiceCue;

extern int GetMsgWindowResultIfDone_800349B4(int a, EvMsgResult* b);

extern void SkipActorAnims_800A67B4(EvScriptCtx* ctx);

extern void CloseMsgWindow_80034A84(int a);

extern int IsMsgWindowWaiting_80034A30(int a);

extern void EnableMsgWindowAdvance_80034A68(int a);

extern int currentMessageId_800AEBE8;

extern EvXaClip* currentVoice_800AEBEC;

extern EvVoiceCue* voiceTable_800AEBF0;


extern void sub_8005BBC8();

typedef struct EvItemMsgSrc
{
    short a_0;
    short b_2;
    int c_4;
} EvItemMsgSrc;

typedef struct EvItemMsgSlot
{
    int f0_0;
    int f4_4;
    int f8_8;
    int fC_C;
    int f10_10;
} EvItemMsgSlot;

extern void memset(void* p, int v, int n);

typedef struct EvEffectFile
{
    int f0_0;
    int list_4; // ListInit_8003FDB0 list of the loaded effect data
    char pad_8[0x24];
    int usesMdec_2C; // AllocMdecBuffer_800A5804 after loading
} EvEffectFile;

typedef struct EvEffectLoadArg
{
    EvEffectFile* g_0;
    short s_4[6];
    int f10_10;
} EvEffectLoadArg;

extern int mdecBufferMode_800AEB7C;

extern EvEffectFile eventEffects_800AEB80;

extern void FreeMdecBuffer_800A5854(void);

extern void AllocMdecBuffer_800A5804(int a);

extern void OnEffectFileLoaded_80020F5C(EvEffectLoadArg* p, int a);

// sprites / tpages of the TIY loaded by LoadEventTiy_800BC98C
typedef struct
{
    SPRT* sprts_0;
    DR_TPAGE* tpages_4;
} EvTiyData;
extern EvTiyData eventTiy_800AEBC0;

extern int eventRecords_800AEBCC[2];

extern void FreeRecordTables_80026DE8(int* a, int b, void* c);

extern void AllocRecordTables_80026D78(int* a, int b, void* c);

extern void LoadRecordTables_80026E74(int a, int b, void* c);

typedef struct EvTaskEntry
{
    unsigned int flags_0;
    int f4_4;
    void (*next_8)();
} EvTaskEntry;

extern void ReturnWarpTask_800BCB3C();

extern void LoadLevantAnimById_800AC604(int a, int b);

extern int AreLevantFilesLoaded_800AC768(void);

extern void FreeLevantAnimById_800AC6A8(int a);


extern void StartSceneDarken_8001AAA8(int a);

extern int LevantCommand_800A8EC4(int* p);

extern void FieldModeTask_800A7720();

extern short word_8008B858;

extern short pendingArea_8008B860;

extern int dword_80091C8C;

extern int EvCmdBeginScene_800B8BE8();
extern int EvCmdWaitTrigger_800B9B98();
extern int EvCmdSetChapter_800BA82C();
extern int EvCmdOpenMapSelect_800BAB5C();
extern int EvCmdBattle_800BB27C();
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
extern int EvCmdSetMapVariant_800BA880();
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
extern int EvCmdSetIdleAnim_800BB180();
extern int EvCmdWaitActorInRegion_800BB214();
extern int EvCmdIfBattleResult_800BB45C();
extern int EvCmdFadeSound_800BB4A4();
extern int EvCmdPadVibration_800BB7D8();

extern int dword_800B6D00;
extern const char aAssertionFaile_800B6D04[];
extern const char aColiC_800B6D2C[8];
extern int (*eventFuncs_800BCDBC[157])();

/* the jump table of ReturnWarpTask_800BCB3C (asm) and its targets, labels in the generated asm */

/* ---- moved from the .c files: types ---- */
typedef struct EvEnemyGroup
{
    int kind_0; // 0: actors already exist, 1: hide them when reused (GAME's GameEnemy)
    int maxCount_4;
    int f8;
    int fC;
    int f10;
    int idx_14;
    int useMinion_18; // 1: the first member is minion_1C
    UnitStats minion_1C;
    Actor* actor_A4;
    int fA8;
    int fAC;
    EvEnemyMember members_B0[3];
    int fC8;
    int fCC;
    int fD0;
    int z_D4[3];
} EvEnemyGroup;

typedef struct EvLoaderModel
{
    int f0;
    int id_4;
    int pad_8[3];
} EvLoaderModel;

// work area of the model loader task (modelLoaderTask_8008B54C)
typedef struct EvModelLoader
{
    int f0;
    int f4;
    int f8;
    EvLoaderModel ents_C[4];
} EvModelLoader;

// an enemy slot of the GAME overlay (GameEnemySlot): AddEnemySlot_800A17F4 copies the EvEnemyGroup into data_8
typedef struct EvEnemySlot
{
    int f0;
    int aiEvent_4;
    EvEnemyGroup data_8;
} EvEnemySlot;

// work area of the encounter task (encounterTask_8008D674, EncounterSpawnTask_800B844C)
typedef struct EvEncounterWork
{
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
} EvEncounterWork;

typedef struct EvBattleArgs
{
    int f0_0[5];
    int f14_14;
    int ids_18[3];
    struct
    {
        int a_0;
        int b_4;
        int c_8;
    } e_24[3];
} EvBattleArgs;

typedef struct EvBattleEnemy
{
    int f0_0[5];
    int f14_14;
    int useMinion_18;
    char pad_1C[0xA4 - 0x1C];
    int actors_A4[3];
    struct
    {
        int species_0;
        int b_4;
    } members_B0[3];
    int anims_C8[3];
    int fD4_D4[3];
} EvBattleEnemy;

typedef struct EvSpeaker
{
    int a_0;
    int b_4;
} EvSpeaker;

typedef struct EvMsgWindowCfg
{
    int posMode_0;
    short* pos_4;
    int str_8;
    int fC;
    int f10;
    int f14;
    int mask_18;
    int* list_1C;
    EvSpeaker pair_20;
    int f28;
    int f2C;
    int f30;
    int f34;
    int f38;
    int f3C;
    int f40;
    int voice_44;
} EvMsgWindowCfg;

typedef struct EvItemMsgCfg
{
    int posMode_0;
    short* pos_4;
    int f8;
    EvItemMsgSlot slots_C[3];
    int f48;
    int f4C;
} EvItemMsgCfg;

typedef struct EvMsgOptions
{
    EvSpeaker pair_A8;
    EvItemMsgSrc src_B0;
    int* list_B8;
    int fBC;
    int fC0;
    int fC4;
    int fC8;
    int fCC;
} EvMsgOptions;

typedef struct EvRelocBlob
{
    int* p_0;
} EvRelocBlob;

int GetOwnEntityParam_800BBDF4(EvScriptCtx* ctx);

/* GAME-side (game.h; GAME stays loaded under EVENTFNC) */
extern EvEnemySlot* AddEnemySlot_800A17F4(EvEnemyGroup* src, int b);
extern int CreateEnemyAiEvent_800A2D90(Actor* a, UnitStats* b, int c);
extern int fieldMode_800B0EC0;
extern int gCtx_800B1260;
extern int GetGameMode_800A6D50(int a);
extern void SuspendAllEnemySlots_800A1904(void);
extern EvBattleEnemy eventEnemy_800B1CB8;
extern int eventBattlePending_800AEBE0;
extern int eventBattleLoseWarp_800AEBE4;
extern int GetFieldMinionAnims_800A7A9C(int i);
extern void EnableCameraPoints_800A094C();
extern void DisableCameraPoints_800A096C();
extern int FieldMinionCommand_800A7D40(int a, int* p);
extern int FinishLevantCommand_800A9008(int* p);
extern int TriggerFieldMinionEffect_800A80C4(int a, int* p);
extern int GetEventString_800A6738(int a);
extern int GetFieldMinionModelId_800A78A8(int a);
extern int sub_800A78F4(int a);
extern EvRelocBlob eventReloc_800AEBBC;
extern int eventDataBuf_800AEBC8;
/* exe-side, to move to unit_stats.h */
extern short defaultBones_80079140[]; // default bone table
/* exe-side, to move to engine.h */
extern void StartSceneFadeIn_8001AA04(int duration); // not short: EvCmdFadeSound_800BB4A4 passes an lhu value
extern void StartSceneFadeOut_8001AA50(int duration);
extern void StartSceneBrighten_8001AB1C(int duration);
/* exe-side, to move to sound_seq.h */
extern void FadeOutSfxSeq_80031638(void);
extern short SfxKeyOn_800314F4(int sfx);
extern void SfxKeyOff_80031574(short voice, short sfx);
/* exe-side, to move to sound.h */
extern int PlayMusic_800300E0(int idx, int unused);
/* exe-side, to move to model_ftg.h */
extern void SetLoadFadeFlag_80027478(int mask, int set);
/* exe-side, to move to msg_window.h */
extern int OpenMessageWindow_8003422C(EvMsgWindowCfg* cfg);
extern int OpenItemMessageWindow_80035AC8(EvItemMsgCfg* cfg);
/* PSY-Q library */
extern int printf(const char* fmt, ...);
extern int rand(void);
extern void exit(int status);
extern void SsSepSetDecrescendo(short, short, short, long);
extern void SsSepStop(short, short);

