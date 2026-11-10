// EVENTFNC.BIN: declarations shared by its source files
// EVENTFNC.BIN
#include "common.h"

#include "funcs.h"

#include "globals.h"
#include "main.h"
#include "model.h"
#include "engine.h"
#include "minion_init.h"
#include "sound.h"
#include "camera.h"
#include "model_ftg.h"
#include "levant_actor.h"
#include "util.h"
#include "msgwin.h"
#include "msg_window.h"
#include "event.h"
#include "cd.h"
#include "sound_seq.h"
#include "tim.h"
#include "unit_stats.h"
#include "party.h"

typedef struct EvVec
{
    int x_0;
    int y_4;
    int z_8;
} EvVec;

// one event script instruction: op_0 indexes eventFuncs_800BCDBC (GAME's RunEventScript_800A6060 runs them until one returns 0)
typedef struct EvInstr
{
    int op_0;
    int a_4;
    int b_8;
    int c_C;
} EvInstr;


// an event entity as the script commands see it (GAME's GameEvEnt)
typedef struct EvEntity
{
    EVENT_ENTITY_HEAD
    int work_14[0x19];
    int armed_78;
    int f7C_7C;
    int tri_80; // a state EvCmdWaitEntityState_800B9E48 waits for
    int mesh_84;
    int slideTri_88;
    void* param_8C; /* a map entity's (MapEnt.arg_8C): what its scripts get, GetOwnEntityParam_800BBDF4 */
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
    long callArg_F0; // the argument of the map code a script calls: a value, or an address (a pointer on PC)
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
    MsgWindowEntry* msgWindow_11C; // the message window (OpenMessageWindow_8003422C)
    EvEntity* ent_120;
} EvScriptCtx;

// an actor command (GAME's GameActorCmd): kind 0 walk / 1 run / 2 turn to x/y/z, 3 / 4 play / stop a held animation,
// 5 play animation data, 6 visible, 7 ground move, 8 root motion, 9..11 play a motion
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

extern int SendActorCmd_800BB840(EvScriptCtx* ctx, GameActorCmd* cmd, int a, int b);

extern int SendActorCmdMask_800BB990(EvScriptCtx* ctx, GameActorCmd* cmd, int a, int b);

extern void SetTempFlags_800BBDA0(int mask, int on);

extern int TestTempFlags_800BBDD8(int mask);


// the low halves of cameraEye_8008D600 (VECTOR camera eye), read with lhu by IsActorLeftOf_800BC5C8

extern int sceneScriptId_800AEBD8;

extern void LoadEncounterModels_800B8940(int* ids);






extern int CollideWithMapEnts_800B82C8(int* pos, int* prevPos, MapMesh* ents, unsigned char* flags, int n);

extern void SlideOffEdge_800B8220(int* pos, int* prevPos, MapMesh* mesh, int* tri, int* edge, int* dir);

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
static inline int EvFindLevantMesh(GameLevantActor* ent)
{
    unsigned int i;
    unsigned int mesh = ent->mesh_84;
    int tri;
    for (i = 0; i < mapState_8008B500.nMeshes_4; mesh++, i++)
    {
        mesh %= mapState_8008B500.nMeshes_4;
        tri = FindTriAtXZ_800B76B8(&mapState_8008B500.meshes_C[mesh], (EvVec*)&levantPos_8008BD18.pos);
        if (tri >= 0)
        {
            ent->tri_80 = tri;
            if (ent->mesh_84 != mesh)
            {
                ent->mesh_84 = mesh;
            }
            return 1;
        }
    }
    return 0;
}

extern void FindCrossedEdge_800B79E0(MapMesh* m, int* p, int* q, int* tri, int* edge);

extern void SlideAlongEdge_800B7E40(int* pos, MapMesh* mesh, int tri, int edge, int* out);

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

extern void SpawnEncounterEnemy_800B8568(EvEncounterMember* members, EvSpawnPlace* place, int aiArg, int index);

extern EventNode* encounterTask_8008D674;

extern void ResetEncounter_800A170C(void);

extern void ClearEnemySlots_800A1794(void);



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

extern void (*eventHook_800B1D98)(void* arg); // GAME's EventHookFn

extern EventEntry* StartEventScript_800A59D0(void* script);

extern SVECTOR* GetActorRot_800BBBD0(int actor); // rotation of Levant (0) or a party member

extern short screenOffset_8008D474[2];



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

extern void SetVoiceTable_800A6830(void* tbl);

extern void EvMessageNop_800BC7A0(EvScriptCtx* ctx);

extern int OpenEventMessage_800BBE3C(EvScriptCtx* ctx);

extern int UpdateEventMessage_800BC2B4(EvScriptCtx* ctx);



extern struct Actor* GetFieldMinionActor_800A7A60(int i);

extern void* GetEventDataSlot_800A55B0(int a);

extern int useMapStartPos_80091C94;

extern int eventDispatchHalt_8008B540;

extern void RequestGameMode_800A6D30(int mode);

extern void SetMapVar_800ADC5C(unsigned short* v, int a);

extern void FindMapEntrance_800ADCEC(unsigned short* v, int a);

extern int forceMapReload_80091C9C;

extern int mapStartMode_80091C54;


extern int GetSetReturnEntrance_800A683C(int a);

typedef struct EvShopRequest
{
    int pending_0; // set by EvCmdOpenShop_800BABB0, cleared by GAME when the shop closes
    int kind_4;    // 0 / 1 SHOP, 2 WPNSHOP, else SHOPCTRL (GAME's StartShopRequest_800A7204)
    int shopId_8;
} EvShopRequest;

extern EvShopRequest shopRequest_800B06B0;

extern int ExchangeEventResult_800A5F9C(int a);



typedef struct EvViewRect
{
    short x_0;
    short y_2;
    short w_4;
    short h_6;
} EvViewRect;

extern EvViewRect viewport_8008D420;


extern int GetFieldMinionCount_800A7790(void);


extern int IsEventPointValid_800A6504(int a, EvVec* v);

extern int battleResult_800B1230;



extern int IsActorCmdReady_800BBAB0(int i);

extern int IsActorCmdDone_800BBAE4(int i);

extern int StartActorCmd_800BBB18(GameActorCmd* cmd);

extern int FinishActorCmd_800BBB5C(GameActorCmd* cmd);

extern int IsLevantControlHeld_800A8E7C();

extern int IsFieldMinionIdle_800A7CB8(int a);

extern int IsLevantCmdDone_800A8FE0();

extern int IsFieldMinionReady_800A7CFC(int a);

extern EvVec* GetFieldMinionPos_800A7940(int a);


extern SVECTOR* GetFieldMinionRot_800A7984(int a);

extern int eventTempFlags_800AEBD4;


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


extern void SkipActorAnims_800A67B4(EvScriptCtx* ctx);




extern int currentMessageId_800AEBE8;

extern EvXaClip* currentVoice_800AEBEC;

extern EvVoiceCue* voiceTable_800AEBF0;



typedef struct EvItemMsgSrc
{
    short a_0;
    short b_2;
    int c_4;
} EvItemMsgSrc;



extern int mdecBufferMode_800AEB7C;

extern EffectFile eventEffects_800AEB80;

extern void FreeMdecBuffer_800A5854(void);

extern void AllocMdecBuffer_800A5804(int a);


// sprites / tpages of the TIY loaded by LoadEventTiy_800BC98C
typedef struct
{
    SPRT* sprts_0;
    DR_TPAGE* tpages_4;
} EvTiyData;
extern EvTiyData eventTiy_800AEBC0;

#ifndef EVENT_RECORDS_DEFINED
#define EVENT_RECORDS_DEFINED
// the event record tables a map's event data brings (LoadEventData_800A5628 kind 4)
typedef struct EventRecords
{
    int count_0;
    RecordTable* tables_4;
} EventRecords;

#endif
extern EventRecords eventRecords_800AEBCC;




typedef struct EvTaskEntry
{
    unsigned int flags_0;
    int f4_4;
    void (*next_8)();
} EvTaskEntry;
extern void EncounterSpawnTask_800B844C(EvTaskEntry* task);

extern void ReturnWarpTask_800BCB3C(EvTaskEntry* task, int* st);

extern void LoadLevantAnimById_800AC604(int a, int b);

extern int AreLevantFilesLoaded_800AC768(void);

extern void FreeLevantAnimById_800AC6A8(int a);



extern int LevantCommand_800A8EC4(GameActorCmd* cmd);

extern void FieldModeTask_800A7720(); /* another overlay's function */



extern int dword_80091C8C;

extern int EvCmdBeginScene_800B8BE8(EvScriptCtx* ctx);
extern int EvCmdWaitTrigger_800B9B98(EvScriptCtx* ctx);
extern int EvCmdSetChapter_800BA82C(EvScriptCtx* ctx);
extern int EvCmdOpenMapSelect_800BAB5C(EvScriptCtx* ctx);
extern int EvCmdBattle_800BB27C(EvScriptCtx* ctx);
extern int EvCmdNop_800B89A8(EvScriptCtx* ctx);
extern int EvCmdWaitButton_800B89C0(EvScriptCtx* ctx);
extern int EvCmdEnd_800B89F4(EvScriptCtx* ctx);
extern int EvCmdSetLoopPoint_800B8CB0(EvScriptCtx* ctx);
extern int EvCmdTakeActors_800B8D08(EvScriptCtx* ctx);
extern int EvCmdReleaseActors_800B8DDC(EvScriptCtx* ctx);
extern int EvCmdGotoLabel_800B8E9C(EvScriptCtx* ctx);
extern int EvCmdJumpScript_800B8F14(EvScriptCtx* ctx);
extern int EvCmdWait_800B8F44(EvScriptCtx* ctx);
extern int EvCmdWaitActors_800B8F88(EvScriptCtx* ctx);
extern int EvCmdSetVar_800B8FB8(EvScriptCtx* ctx);
extern int EvCmdPickBranch_800B9020(EvScriptCtx* ctx);
extern int EvCmdCountYanVar_800B9110(EvScriptCtx* ctx);
extern int EvCmdCallHook_800B91CC(EvScriptCtx* ctx);
extern int EvCmdStartScript_800B9218(EvScriptCtx* ctx);
extern int EvCmdWarpActor_800B9260(EvScriptCtx* ctx);
extern int EvCmdMoveToPoint_800B93A8(EvScriptCtx* ctx);
extern int EvCmdMoveToActor_800B942C(EvScriptCtx* ctx);
extern int EvCmdTurnToPoint_800B95BC(EvScriptCtx* ctx);
extern int EvCmdTurnToActor_800B962C(EvScriptCtx* ctx);
extern int EvCmdSetActorVisible_800B96D8(EvScriptCtx* ctx);
extern int EvCmdSetActorGroundMove_800B9720(EvScriptCtx* ctx);
extern int EvCmdSetActorRootMotion_800B9768(EvScriptCtx* ctx);
extern int EvCmdSaveActorPos_800B97B0(EvScriptCtx* ctx);
extern int EvCmdSaveActorFront_800B97F8(EvScriptCtx* ctx);
extern int EvCmdTestFlag_800B9840(EvScriptCtx* ctx);
extern int EvCmdSetFlag_800B98C4(EvScriptCtx* ctx);
extern int EvCmdClearFlag_800B990C(EvScriptCtx* ctx);
extern int EvCmdTestTempFlags_800B9954(EvScriptCtx* ctx);
extern int EvCmdSetTempFlags_800B99D8(EvScriptCtx* ctx);
extern int EvCmdClearTempFlags_800B9A20(EvScriptCtx* ctx);
extern int EvCmdAddItem_800B9A68(EvScriptCtx* ctx);
extern int EvCmdRemoveItem_800B9AB4(EvScriptCtx* ctx);
extern int EvCmdAddItemCat1_800B9B00(EvScriptCtx* ctx);
extern int EvCmdRemoveItemCat1_800B9B4C(EvScriptCtx* ctx);
extern int EvCmdSetValuable_800B9C5C(EvScriptCtx* ctx);
extern int EvCmdAddMoney_800B9CC0(EvScriptCtx* ctx);
extern int EvCmdAddEmptyCocoons_800B9D08(EvScriptCtx* ctx);
extern int EvCmdHealParty_800B9D50(EvScriptCtx* ctx);
extern int EvCmdSetEntityState_800B9DE0(EvScriptCtx* ctx);
extern int EvCmdWaitEntityState_800B9E48(EvScriptCtx* ctx);
extern int EvCmdSetOwnEntityState_800B9EB0(EvScriptCtx* ctx);
extern int EvCmdWaitOwnEntityState_800B9EDC(EvScriptCtx* ctx);
extern int EvCmdWaitEntityGone_800B9F0C(EvScriptCtx* ctx);
extern int EvCmdSetMsgOptions_800B9F5C(EvScriptCtx* ctx);
extern int EvCmdSetMsgPos_800B9F84(EvScriptCtx* ctx);
extern int EvCmdSetMsgPosMode_800B9FB4(EvScriptCtx* ctx);
extern int EvCmdSetVoiceTable_800B9FD8(EvScriptCtx* ctx);
extern int EvCmdMessage_800BA020(EvScriptCtx* ctx);
extern int EvCmdSwapMsgAfterCount_800BA1DC(EvScriptCtx* ctx);
extern int EvCmdWaitMsgMark_800BA238(EvScriptCtx* ctx);
extern int EvCmdSetChoiceMask_800BA28C(EvScriptCtx* ctx);
extern int EvCmdPlayAnim_800BA2E8(EvScriptCtx* ctx);
extern int EvCmdStopAnim_800BA338(EvScriptCtx* ctx);
extern int EvCmdPlayAnimData_800BA40C(EvScriptCtx* ctx);
extern int EvCmdPauseActorAnim_800BA45C(EvScriptCtx* ctx);
extern int EvCmdPlayMotion_800BA4F0(EvScriptCtx* ctx);
extern int EvCmdPlayMotionRange_800BA554(EvScriptCtx* ctx);
extern int EvCmdPlayMotionData_800BA5CC(EvScriptCtx* ctx);
extern int EvCmdSetCallArg_800BA678(EvScriptCtx* ctx);
extern int EvCmdSetCallArgs_800BA6D0(EvScriptCtx* ctx);
extern int EvCmdCallUntilDone_800BA714(EvScriptCtx* ctx);
extern int EvCmdCallSelect_800BA7A4(EvScriptCtx* ctx);
extern int EvCmdSetMapVariant_800BA880(EvScriptCtx* ctx);
extern int EvCmdSetMapVar_800BA8AC(EvScriptCtx* ctx);
extern int EvCmdChangeMap_800BA930(EvScriptCtx* ctx);
extern int EvCmdChangeMapToPoint_800BA9E4(EvScriptCtx* ctx);
extern int EvCmdPreloadArea_800BAA6C(EvScriptCtx* ctx);
extern int EvCmdUsePreloadedArea_800BAAC0(EvScriptCtx* ctx);
extern int EvCmdSetReturnPoint_800BAB14(EvScriptCtx* ctx);
extern int EvCmdOpenShop_800BABB0(EvScriptCtx* ctx);
extern int EvCmdCameraLookAtPoint_800BAC60(EvScriptCtx* ctx);
extern int EvCmdCameraLookAtActor_800BACE0(EvScriptCtx* ctx);
extern int EvCmdCameraClearLookAt_800BAD3C(EvScriptCtx* ctx);
extern int EvCmdWaitCameraBlend_800BAD88(EvScriptCtx* ctx);
extern int EvCmdSetViewRect_800BADF8(EvScriptCtx* ctx);
extern int EvCmdSetCameraZoom_800BAEBC(EvScriptCtx* ctx);
extern int EvCmdSetCameraTarget_800BAF08(EvScriptCtx* ctx);
extern int EvCmdSetMapMesh_800BAF68(EvScriptCtx* ctx);
extern int EvCmdWaitTalk_800BAFAC(EvScriptCtx* ctx);
extern int EvCmdSetIdleAnim_800BB180(EvScriptCtx* ctx);
extern int EvCmdWaitActorInRegion_800BB214(EvScriptCtx* ctx);
extern int EvCmdIfBattleResult_800BB45C(EvScriptCtx* ctx);
extern int EvCmdFadeSound_800BB4A4(EvScriptCtx* ctx);
extern int EvCmdPadVibration_800BB7D8(EvScriptCtx* ctx);

extern int eventfncHeader_800B6D00;
extern const char aAssertionFaile_800B6D04[];
extern const char aColiC_800B6D2C[8];
extern int (*eventFuncs_800BCDBC[157])();

/* the jump table of ReturnWarpTask_800BCB3C (asm) and its targets, labels in the generated asm */

/* ---- moved from the .c files: types ---- */
typedef struct EvEnemyGroup
{
    int kind_0; // 0: actors already exist, 1: hide them when reused (GAME's GameEnemy)
    int maxCount_4;
    int canFlee_8; // GAME: GameEncounter.canFlee_780
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
    void* aiEvent_4;
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
    int loseWarp_14;
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
    int loseWarp_14;
    int useMinion_18;
    char pad_1C[0xA4 - 0x1C];
    Actor* actors_A4[3];
    struct
    {
        int species_0;
        int b_4;
    } members_B0[3];
    ActorScriptCmd** anims_C8[3];
    int fD4_D4[3];
} EvBattleEnemy;

typedef struct EvSpeaker
{
    int a_0;
    int b_4;
} EvSpeaker;

typedef struct EvMsgOptions
{
    EvSpeaker pair_A8;
    EvItemMsgSrc src_B0;
    int* list_B8;
    int pad_BC;
    int pad_C0;
    int pad_C4;
    int fC8;
    int fCC;
} EvMsgOptions;

typedef struct EvRelocBlob
{
    int* p_0;
} EvRelocBlob;

void* GetOwnEntityParam_800BBDF4(EvScriptCtx* ctx);

/* GAME-side (game.h; GAME stays loaded under EVENTFNC) */
extern EvEnemySlot* AddEnemySlot_800A17F4(EvEnemyGroup* src, int b);
extern void* CreateEnemyAiEvent_800A2D90(Actor* a, UnitStats* b, int c);
extern int fieldMode_800B0EC0;
extern int gCtx_800B1260;
extern int GetGameMode_800A6D50(int a);
extern void SuspendAllEnemySlots_800A1904(void);
extern EvBattleEnemy eventEnemy_800B1CB8;
extern int eventBattlePending_800AEBE0;
extern int eventBattleLoseWarp_800AEBE4;
extern ActorScriptCmd** GetFieldMinionAnims_800A7A9C(int i);
extern void EnableCameraPoints_800A094C(void);
extern void DisableCameraPoints_800A096C(void);
extern int FieldMinionCommand_800A7D40(int idx, GameActorCmd* cmd);
extern int FinishLevantCommand_800A9008(GameActorCmd* cmd);
extern int TriggerFieldMinionEffect_800A80C4(int idx, GameActorCmd* cmd);
extern void* GetEventString_800A6738(unsigned int id);
extern char* GetFieldMinionName_800A78A8(int a);
extern int GetFieldMinionHeaderF2A_800A78F4(int a);
extern EvRelocBlob eventReloc_800AEBBC;
extern void* eventDataBuf_800AEBC8;
/* exe-side, to move to unit_stats.h */
extern short defaultBones_80079140[]; // default bone table
/* exe-side, to move to engine.h */
/* exe-side, to move to sound_seq.h */
/* exe-side, to move to sound.h */
/* exe-side, to move to model_ftg.h */
/* exe-side, to move to msg_window.h */
/* PSY-Q library */
extern int rand(void);

