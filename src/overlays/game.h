// GAME.BIN: declarations shared by its source files
// GAME.BIN
#include "common.h"

#include "funcs.h"

#include "globals.h"
#include <libetc.h>

#include "actor.h"

#include "model.h"
#include "effect_obj.h"
#include "effect_model.h"
#include "camera.h"
#include "engine.h"
#include "event.h" // EventDesc
#include "sound.h"
#include "unit_stats.h" // eventDescs_80078EB8
#include "model_ftg.h"
#include "util.h"
#include "unit_query.h"
#include "pad_text.h"
#include "cd.h"
#include "sound_seq.h"
#include "movie.h"
#include "ui_sprites.h"
#include "tim.h"
#include "effect.h"
#include "minion_init.h"
#include "party.h"
#include "effect_data.h"
#include "battle_damage.h"
#include "levant_actor.h"

extern void RequestGameMode_800A6D30(int mode);

// AI of an enemy actor (CreateEnemyAiEvent_800A2D90; the enemyAiBySpecies_800ADEB8 state handlers)
typedef struct GameAi
{
    unsigned int* flags_0;     // the flags of its event entry (q[0] = the entry)
    UnitStats* minion_4; // minion data (in the enemy slot)
    Actor* actor_8;
    int state_c;
    int f10;
    char pad_14[0xC];
    int anim_20;
    int timer_24;
    int turnDir_28; // turn direction (FindActorInFront_8001DECC: 1 / 2)
    int turnLeft_2C; // turn amount
} GameAi;

// the battle chain record (encounterRecord_800ADE78; battle.h BatChain_a)
typedef struct GameBattleChain
{
    int active_0; // 1 while a chain of battles runs
    int f4, f8;
    int index_C;  // the battle of the chain (-1 before the first)
    int next_10;  // the next entry (-1: none)
} GameBattleChain;

typedef struct GameV3_1
{
    int a, b, c;
} GameV3_1;

// an enemy group of the map (EVENTFNC's EvEnemyGroup, copied into GameEnemySlot.data_8 by AddEnemySlot_800A17F4)
typedef struct GameEnemyMember
{
    int species_0; // GetSpeciesModelDesc_80019C70 / InitMinionData_8001900C
    int f4;
} GameEnemyMember;

typedef struct GameEnemy
{
    int kind_0; // 0: actors already exist, 1: hide them when reused
    int maxCount_4;
    int canFlee_8; // GameEncounter.canFlee_780 (CanFleeFromEnemy_800A28FC)
    int fC;
    int f10;
    int groupIndex_14; // GameEncounter.groupIndex_48 (ClearEncounterGroupFlags_800A4940; -1: none)
    int useMinion_18; // 1: the first member is minion_1C
    UnitStats minion_1C;
    Actor* actors_A4[3];
    GameEnemyMember members_B0[3];
    int* anims_C8[3]; // [0]: when it is the group being fought, [1]: otherwise (default name_8007A024)
    int fD4[3];
} GameEnemy;

typedef struct GameEnemySlot
{
    int used_0;
    GameAi* ai_4;
    GameEnemy data_8;
} GameEnemySlot;

#ifdef __psyz /* an alias (config/aliases.txt), on PC the place itself */
#define enemySlots_800B19F0 (gCtx_800B1260.enemySlots_790)
#else
extern GameEnemySlot enemySlots_800B19F0[3]; // == gCtx_800B1260.enemySlots_790 (config/aliases.txt)
#endif

extern short defaultBones_80079140[]; // default bone table
extern GameEnemy* GetEventEnemy_800A5F6C(void);
extern GameEnemySlot* AddEnemySlot_800A17F4(unsigned int* src, GameAi* ai);

extern void FreeEnemyAi_800A2D28(GameAi* ai);

extern void SuspendEnemyAi_800A2EC8(GameAi* ai);

// context of an event script (list eventScripts_8008D410); same layout as EvScriptCtx in eventfnc.h
typedef struct GameEvCtx
{
    unsigned int flags_0;
    struct EvInstr* start_4;
    struct EvInstr* pc_8;
    struct EvInstr* ret_C;
    int id_10;
    int heldActors_14;
    int busyActors_18;
    int animActors_1C;
    int f20;
    int idleAnims_24[6];
    int savedPos_3C[5][3];
    int savedFront_78[5][3];
    int msgStep_B4;
    int step_B8;
    int maskStep_BC;
    int cmdStep_C0;
    unsigned int waitCount_C4;
    int trigger_C8;
    int vars_CC[8];
    int branch_EC;
    int callArg_F0;
    int callArg0_F4;
    int callArg1_F8;
    int callArg2_FC;
    short msgX_100;
    short msgY_102;
    int msgPosMode_104;
    int msgOptions_108;
    int pad_10C;
    int lastMsg_110;
    int choiceMask_114;
    int msgOpen_118;
    struct MsgWindowEntry* msgWindow_11C;
    int ent_120;
} GameEvCtx;

// an event entity (list eventEntities_8008D400); same layout as EvEntity in eventfnc.h
typedef struct GameEvEnt
{
    EVENT_ENTITY_HEAD
    int work_14[0x19];
    int armed_78; // waits for a trigger (FireEventTrigger_800A5C40)
    int f7C;
    int pad_80;
    int trigger_84; // the trigger it waits for (-1: any; 0x40000000: compare with the fired one)
    int script_88;  // the event script it starts when triggered
    int pad_8C;
} GameEvEnt;

extern EventEntry* StartEventScript_800A59D0(void* script);

extern int FindTriAtXZ_800B76B8(char* p, int* pos);

extern void ResumeEnemyAi_800A2D48(GameAi* ai);

extern int AssertEnemyIndex_800A2CA8(int idx, int noExit);

extern void ResetEncounter_800A170C(void);

extern Actor* GetFieldMinionActor_800A7A60(int idx);

// model header of a party member (first word: model id)
typedef struct GameModelHdr
{
    int id_0;
    char pad_4[0x1C];
    short walkAnim_20; // the actor command animations (FieldMinionCommand_800A7D40)
    short runAnim_22;
    short turnAnim_24;
    short turnStep_26;
    short pad_28;
    short f2A;
} GameModelHdr;

// the part of a party member its callbacks get (GameMember.cb_14)
typedef struct GameMemberCb
{
    int f0;
    Actor* actor_4;
    int* anims_8; // animation table (indexed by the script commands)
    int (*hold_C)();     // HoldFieldMinion_800A7810 (0: busy)
    void (*release_10)(); // ReleaseFieldMinion_800A785C
} GameMemberCb;

// what Actor.desc_15C of a party member points to
typedef struct GameActorDesc
{
    char pad_0[0x30];
    int clut_30; // index into combatPortraitImagePos_8007DCAC / combatPortraitClutPos_8007DCBC
} GameActorDesc;

// a party member (fieldMinions_800B0EC4.a)
typedef struct GameMember
{
    struct EventEntry* entry_0; /* EVENT_ENTITY_HEAD, with its data as the model */
    void* event_4;
    int areas_8;
    int type_C;
    GameModelHdr** hdr_10;
    GameMemberCb cb_14;
} GameMember;

// the party members following Levant (fieldMinions_800B0EC4)
typedef struct GameFieldMinions
{
    int count;
    GameMember* members[4];
    int suspended[4]; // SuspendFieldMinions_800A7B00 made it inactive
    int hidden[4];    // SuspendFieldMinions_800A7B00 paused and hid it
} GameFieldMinions;

extern GameMember* GetFieldMinion_800A77F4(int idx);
extern GameActorDesc* GetFieldMinionModelDesc_800A7A1C(int idx);

extern EventNode* gameMainTask_8008D46C;

// a map location (saveData_8008B570.mapId_2E4[0..2]; FindMapEntrance_800ADCEC)
typedef struct GameMapLoc
{
    unsigned short area, map, entrance; // mapTable_800B0608[area][map][entrance]
} GameMapLoc;

extern void FindMapEntrance_800ADCEC();

extern void SetEventFlag_800AD0F8(unsigned flag);

extern int mapStartMode_80091C54;

extern int forceMapReload_80091C9C;

extern int dword_80091C8C;

// a GAME task: the layout of an EventEntry, with the update callback it switches between
typedef struct GameTask
{
    unsigned int flags_0; // EventEntry.flags (1: run, 0x8000: free)
    int f4;
    void (*next_8)();
} GameTask;

// a menu request handed to the sub overlay once it is loaded (shopRequest_800B06B0 / saveRequest_800B06BC)
typedef struct GameMenuRequest
{
    int active_0;
    int kind_4;      // shop: 0 / 1 store, 2 shop control
    int arg_8;       // shop: the shop id (short), save menu: the save place
    int endOfGame_C; // save menu: LoadMenuSetEndOfGame_800B78D0
} GameMenuRequest;

extern int FindInLists_800A52EC(short** tab, int count, int key);

extern void WaitChapterOverlay_800A76D8();

extern void SetLoadMenuSavePlace_800B78B8(int a);

extern void LoadMenuSetEndOfGame_800B78D0();

extern int GetFieldMinionCount_800A7790(void);

typedef struct GameEncounter
{
    int active_0;
    GameEnemySlot* leader_4;     // the enemy slot that started the encounter
    int otherCount_8;             // number of others_C entries
    GameEnemySlot* others_C[12]; // the other enemy slots
    int swapped_3C; // fixed encounters: which of the two enemies is out (SwapEncounterEnemy_800A2AE8)
    int count_40;
    int remaining_44;
    int groupIndex_48;
    int gone_4C[12];
    Actor* actors_7c[12];
    UnitStats ents_ac[12]; // the encounter's minions (minion data)
    int anims_70C[12];
    int f73c[12];
    int activeCount_76C;
    int memberCount_770;
    int fixed_774;
    int reused_778;
    int f77c;
    int canFlee_780; // CanFleeFromEnemy_800A28FC
    int f784;
    int f788;
    int f78c;
    GameEnemySlot enemySlots_790[3]; // the code uses them as enemySlots_800B19F0 (config/aliases.txt)
} GameEncounter;

// the record of one enemy of the last battle (battleEnemyResults_800B1238; BATTLE fills it, MENU's results use it)
typedef struct GameEnemyResult
{
    int exp_0;
    short species_4; // -1: no enemy in the slot
    short killer_6;  // the unit that defeated or captured it
    short level_8;
    short kind_A;    // the command that ended it (7: none)
} GameEnemyResult;

// the walls an event toggles (SetWallsEnabled_800A6564)
typedef struct GameWallPair
{
    short levantWall_0; // mapState_8008B500.ents_14 index (-1: none)
    short actorWall_2;  // mapState_8008B500.ents_30 index (-1: none)
} GameWallPair;

// the work area of the encounter tasks (EncounterWatchTask_800A1314 .. EncounterFadeInWait_800A167C)
typedef struct GameBattleWork
{
    int req_0; // file request
    int fadeWait_4; // frames to wait before fading back in
    EventEntry* battleTask_8; // StartBattle_800BA9E4 / StartBattleResult_800BBB94
} GameBattleWork;

extern void ReflectPoint_800A47B8(Vec3i* center, Vec3i* point, Vec3i* out);

extern void WaitMapOverlay_800A7654();

extern void EncounterWatchTask_800A1314();

extern void SetLevantWallEnabled_800A6534(int wall, int on);

extern void SetActorWallEnabled_800A654C(int wall, int on);

// fieldModeHandlers_800B0EB8 (FieldModeTask_800A7720)
typedef struct GameFieldModeHandler
{
    int f0;
    void (*fn)();
} GameFieldModeHandler;

extern void EvCmdEndScene_800B8A34(GameEvCtx* q);

extern void ChooseEnemyCommand_800C4118(void* a, void* b, int c, int d);

extern EventEntry* StartBattle_800BA9E4(void);

extern void BattleEnd_800BA254();

extern void SuspendFieldMinions_800A7B00(int idx);

extern void ResumeFieldMinions_800A7BF0(int idx);

extern void SuspendEnemySlot_800A188C(GameEnemySlot* slot);

extern void ResumeEnemySlot_800A18C8(GameEnemySlot* slot);

extern int dword_800B199C[];

extern short sinTable_80084540[];

typedef struct GameObjList_1
{
    char pad_0[0xc];
    int count_c;
    char pad_10[4];
} GameObjList_1;

typedef struct GameMsgEntry
{
    void** text; // the message's lines: pages end with 0, the last with two, then the choice lines (0 ended)
    int count;   // its words
} GameMsgEntry;

// the event message table (GetEventDataSlot_800A55B0(1), GetEventString_800A6738)
typedef struct GameMsgTable
{
    unsigned int count;
    GameMsgEntry e[1];
} GameMsgTable;

extern EventNode* eventScripts_8008D410;

extern void SkipLevantAnim_800A8EA4();

extern void StartStore_800BAE2C(int a, int b);

extern void StartShopCtrl_800B66C4(int a);

extern void* GetEventDataSlot_800A55B0(int kind); // one of the loaded event data blocks (what each holds depends on a)

extern void WaitMapReloadAfterBattle_800A15FC();

extern void EncounterFadeInWait_800A167C();

extern void SkipFieldMinionAnim_800A7AD8(int idx);

typedef struct GameV6_1
{
    int a, b, c, d, e, f;
} GameV6_1;

extern void EnterLevantBattleMode_800A895C();

extern void SetupEncounter_800A1BD0();

extern void SuspendOtherEnemies_800A1E98();

extern void FreeLevantAnimSet_800AC73C();

extern void WaitBattleOverlay_800A1474();

extern unsigned short* sub_800B322C();

extern unsigned short* GetMapEncounterFlags_800A53CC();

extern int GetEventVar_800AD154(int var);

extern int SetEventVar_800AD16C(int var, int value);

// the field view rectangle (viewport_8008D420)
typedef struct GameViewRect
{
    short x, y, w, h;
} GameViewRect;

// a primitive's u0, v0, clut, also copied as one word (the SPRT takes the POLY_FT4's)
typedef union TileUVClut
{
    struct
    {
        unsigned char u0, v0;
        unsigned short clut;
    } f;
    unsigned long word;
} TileUVClut;
// POLY_FT4 / SPRT with the u0, v0, clut word as a TileUVClut
typedef struct TileFT4
{
    unsigned long tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    TileUVClut uv0;
    short x1, y1;
    unsigned char u1, v1;
    unsigned short tpage;
    short x2, y2;
    unsigned char u2, v2;
    unsigned short pad1;
    short x3, y3;
    unsigned char u3, v3;
    unsigned short pad2;
} TileFT4;
typedef struct TileSprt
{
    unsigned long tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    TileUVClut uv0;
    short w, h;
} TileSprt;
// the animated map tile layers' work area (DrawTileAnimLayers_800A0A5C), in the scratchpad at 0x1F800214
typedef struct TileAnimScratch
{
    unsigned int i_0; // the layer (tileAnim_8008D648.lists_14 index)
    TileFT4 ft4_4;    // a cell, zoomed
    TileSprt sprt_2C; // a cell at zoom 0x1000
    DR_TPAGE tpage_40;
    short x0_48; // the cell's screen corners
    short y0_4A;
    short x1_4C;
    short y1_4E;
    short cx_50; // the view centre (viewport_8008D420)
    short cy_52;
    int zoom_54; // cameraZoom_8008B4F8
    int ox_58;   // screen offset of the view centre
    int oy_5C;
    TileSet tiles_60; // the frame's tile set
    int set_70;  // the frame: tile set,
    int clut_74; // clut row,
    int time_78; // frames to show
} TileAnimScratch;
#define TILE_ANIM_SCRATCH ((TileAnimScratch*)getScratchAddr(0x85))
extern ShortPair screenOffset_8008D474;
extern EventNode* taskSlot_8008D478;
extern TileAnimLayers tileAnim_8008D648;
extern void DrawTileAnimLayers_800A0A5C(short* work);

#ifdef __psyz /* an alias (config/aliases.txt), on PC the place itself */
#define Ratan2DifferenceInt_8003B9E0(a, b) ((int)ratan2Difference_8003B9E0(a, b))
#else
extern int Ratan2DifferenceInt_8003B9E0(int* a, int* b); // ratan2Difference_8003B9E0 as GAME declared it (config/aliases.txt)
#endif

extern void MapSelectStart_800B6BFC();

extern void ChapterStartTask_800B66DC();

extern EventEntry* StartBattleResult_800BBB94(void); /* MENU: the battle result screen */

extern void GameMainStart_800A6968();

extern void EnableCameraPoints_800A094C(void);

extern void InitLevantControl_800A8140(void);

extern void InitLevantActor_800A94CC(void);

extern EventNode* eventEntities_8008D400;

extern GameViewRect viewport_8008D420;

extern int useMapStartPos_80091C94;

// gameStartMode_800B1DC8 (GetGameStartMode_800A72C8)
typedef struct GameStartMode
{
    int useStartPos_0; // useMapStartPos_80091C94
    int mode_4;        // the first game mode
} GameStartMode;

extern GameStartMode* GetGameStartMode_800A72C8(GameStartMode* out);

extern void ClearEncounterGroupFlags_800A4940(int group, int encIndex);

extern void ResetEventCtx_800A5B54(GameEvCtx* ctx);

extern void RunEventScript_800A6060();

extern void EndEventScript_800A6168();

extern void TileAnimTask_800A0A04();

typedef struct GameVec4_1
{
    int x, y, z, w;
} GameVec4_1;

typedef struct GameO_1
{
    char pad_0[0x38];
    int f38;
    int pad_3c;
    int f40;
    char pad_44[0x1a];
    short f5e;
} GameO_1;

extern int TurnStepForAngle_800A48F4(int angle);

extern void EnemyAiWanderStep_800A46FC(GameAi* ai);
extern void EnemyAiChaseStep_800A45F8(GameAi* ai);

// an entry of a game mode's task list (gameModeTaskLists_800B0D74)
typedef struct GameTaskListDef
{
    EventNode** list_0; // a list head variable; 0 ends the table
    int modes_4; // bit n: exit the list when switching to mode n (SwitchGameMode_800A6C00); 0x1000: run once when the mode starts
} GameTaskListDef;

extern void GameMainExit_800A6CCC();

extern void SwitchGameMode_800A6C00();

extern void InitGameModeTasks_800A6A48();

extern void GameMainUpdate_800A6B00();

extern void ResetFieldState_800A73A8(void);

extern void RunEventListUpdate_800A7450(EventNode* node);

extern void StartEncounterBattle_800A13B8();

extern int CheckEnemyContact_800A19E4();

extern EventNode* enemyAiTasks_8008D49C;

extern void EnemyAiNone_800A2EE4(EventEntry* e, void* ai);

extern int ApplySporeToEnemyAi_800A4278();

extern void SetEnemyAiState_800A433C();

extern int GetLevantMoveCmd_800AB39C();

extern void RandomizeEnemyTurn_800A43FC();

extern void EnemyAiFleeTurnStep_800A44C0();

extern int* sub_800B3198(void);

extern int encounterVariantToggle_8008B554;

#define ELEM(x) ((short)((int (*)(int))GetMinionElement_80019BF0)(x))

extern int (*eventFuncs_800BCDBC[])(GameEvCtx*);

extern void UpdateEventMessage_800BC2B4(GameEvCtx* q);

// TIM image info handed to InitSprtFromTim_800298AC / InitPolyFT4_80029A10 (the TIM_IMAGE layout)
typedef struct GameTimImage
{
    int mode_valid;
    int mode;
    int clut_len;
    RECT crect;
    u_long* caddr;
    int pix_len;
    RECT prect;
    u_long* paddr;
} GameTimImage;

// a VRAM position (the portrait images: fieldModelImagePos_8007DCA4..combatPortraitClutPos_8007DCBC)
typedef struct GameVramXY
{
    unsigned short x;
    unsigned short y;
} GameVramXY;

extern GameVramXY fieldModelImagePos_8007DCA4;

extern GameVramXY fieldModelClutPos_8007DCA8;

extern GameVramXY combatPortraitImagePos_8007DCAC[];

extern GameVramXY combatPortraitClutPos_8007DCBC[];

// the work area of the GAME main task (GameMainInit_800A68CC); its entry.buffer
typedef struct GameMainWork
{
    int mode_0;     // the current game mode (gameModeTaskLists_800B0D74 index)
    int prevMode_4;
    int nextMode_8; // RequestGameMode_800A6D30
    int modeInited_C[12]; // the mode's init tasks (flag 0x1000) were run
    EventNode* eventList_3C; // CreateEventList_800435B4(gameEventListDefs_800B0DA4)
} GameMainWork;

// the work area of CheckSubOverlayRequests_800A6DAC / WaitSubOverlayLoad_800A70F8
typedef struct GameSubOverlayWork
{
    int mode_0;   // the game mode to switch to once loaded (-1: none)
    int req_4;    // the overlay's file request
    int waitReq_8; // nonzero: wait for req_4
    int freeze_C; // nonzero: FreezeScreen_8001C224 instead of EndFade_8001C290
    int halt_10;  // eventDispatchHalt_8008B540 when done
    int fading_14;
    int startArg_18; // start_1C's argument
    void (*start_1C)(int); // StartShopRequest_800A7204 / StartSaveMenuRequest_800A7280
} GameSubOverlayWork;

extern unsigned short padPressed_8009194C;
extern List eventHeap_80091C10;       // main.h (not included: its task pointer types differ from this overlay's views)
extern List defaultAllocList_80096090; // main.h

extern short areaLoadIds_80091CB8[];

extern EventNode* fieldMenuTask_8008D498;

extern EventNode* loadMenuTask_8008D480;
extern EventNode* nameEntryTask_8008D484;

extern void WaitSubOverlayLoad_800A70F8();

extern void StartShopRequest_800A7204();

extern void StartSaveMenuRequest_800A7280();

extern void CheckSubOverlayRequests_800A6DAC();

/* ---- GAME second half (G2) ---- */

typedef struct GameLevantCtl
{
    // 1: battle mode (EnterLevantBattleMode_800A895C), 2: action requested, 4: action triggered, 8: main action
    // (not a reaction: wait for it to finish), 0x10: entering battle, 0x20: held by a script,
    // 0x40: movement locked, 0x80: stop the scripted walk / turn
    unsigned int flags_0;
    char pad_4[0xC];
    Vec3i pos_10; // Levant's position, copied each frame by LevantControlTask_800A818C
    char pad_1C[0x18];
    int targets_34;
    int arg_38;
    char pad_3C[0x10];
    FirFilter turn_4C;
    int turnBuf_5C[4];
    char pad_6C[0x30];
    int f9C;
    int pad_A0;
    int targetX_A4; // targetX_A4..targetZ_AC: the point Levant walks to / turns toward
    int targetY_A8;
    int targetZ_AC;
    int cmdKind_B0;
    char pad_B4[0x12];
    short state_C6; // the state of Levant's input state machine (LevantControlTask_800A818C)
    char pad_C8[4];
    int anim_CC;
} GameLevantCtl;

extern unsigned char pads_800918E8[2][9];
extern int FindFacingFieldMinion_800A9164(int* out);
extern int IsFieldMinionBehind_800A926C();
extern void ClearScriptActorBusy_800A5BCC(int actor);
extern void ContinueLevantAnim_800AB1A4(int loop);
extern int StartLevantActorAction_800AB1EC(int anim, int playEffect, int targets, int arg);
extern int IsLevantActionReady_800AB32C();
extern int SetLevantMoveCmd_800AB37C(int cmd);
extern void ResetLevantIdleTimer_800AB3BC();
extern void EnterLevantActorBattle_800AB3D4();
extern int IsLevantAnimLooped_800AB938();
extern int IsLevantIdleAnim_800AB958();
extern int IsLevantScriptAnimWaiting_800ABB70();
extern void SetLevantMapCollision_800ABC34(int collide);

typedef struct GameLevantCtlNode
{
    char pad_0[offsetof(EventNode, entry.buffer)]; // the EventNode up to entry.buffer
    GameLevantCtl* buffer_24; // EventNode.entry.buffer
} GameLevantCtlNode;

typedef struct GameLevantFade
{
    unsigned int flags_0;
    char pad_4[0x2C];
    int fade_30;
} GameLevantFade;

typedef struct G2PathStep
{
    short x;
    short y;
    short z;
    short rotY;
} G2PathStep;

typedef struct G2Path
{
    int count_0;
    int div_4;
    G2PathStep* steps_8;
} G2Path;

extern GameLevantCtlNode* levantControlTask_8008B4CC;
extern EventNode* encounterWatchTask_8008B4D0;

extern GameLevantActorNode* gameTask_8008B4A4;

extern void SetLevantHasArmor_800AC380(int has);

extern ModelList* gameModelList_8007DC60; // the GAME overlay's model list

extern int PlaceWindowAwayFromQuadrant_800A88E0();

extern void SetLevantAnim_800AB010();

extern int IsLevantAnimLoaded_800AC518();

extern void FreeLevantAnimById_800AC6A8();

extern int GetLevantAnimFile_800AC4A8();

extern int FindMapVar_800ADBA0(short* key);

typedef struct GameLevantAnim
{
    unsigned char fileId_0;
    unsigned char resident_1;
    char pad_2;
    unsigned char flags_3;
    short start_4;
    short loopStart_6;
    short loopEnd_8;
    unsigned short lastFrame_A;
    HitTimes hitTimes_C[10]; // hit windows (RepeatHitTimes_80018200)
    int f34;
    char pad_38[8];
} GameLevantAnim;

extern int GetLevantAnimIndex_800AC794(int anim, int set);

extern void StopLevantScriptMove_800A913C();

extern void EndLevantPath_800ABAD4();

extern void ExitLevantActorBattle_800AB444();

// a window's screen rectangle (PlaceWindowAwayFromQuadrant_800A88E0)
typedef struct GameWinRect
{
    short x_0;
    short y_2;
    unsigned short w_4;
    unsigned short h_6;
} GameWinRect;

extern InvSlot* FindInventorySlotForAdd_800AD4D8();

extern int GetEmptyCocoons_800AD8E4();

extern int GetFieldMinionCount_800A7790();

extern void SetLevantRootMotionMode_800ABC78();

extern void UpdateLevantFieldAnim_800AA25C();

extern void UpdateLevantBattleAction_800AA51C();

extern void UpdateLevantScriptAnim_800AACF8();

extern void UpdateLevantQueuedAnim_800AC02C();

extern int CanAddInventoryCount_800AD670(int have, int count);

extern void LevantModelTask_800ACB64();

// a map entrance (mapTable_800B0608[area][map][n], ends with id -1)
typedef struct GameMapEntrance
{
    short id_0;
    char pad_2[2];
    short encIndex_4; // the map's slot in the encounter flag tables (GetMapEncounterFlags_800A53CC)
    short entrance_6; // the entrance id (FindMapEntrance_800ADCEC)
    char pad_8[8];
} GameMapEntrance;

extern int GetWeaponEffect_800189F8();

extern G2V12 statusTintLevel1_8007A0A4;

extern G2V12 statusTintLevel2_8007A0B0;

extern G2V12 statusTintLevel3_8007A0BC;

extern G2V12 statusTintLevel4_8007A0C8;

extern G2V12 statusTintLevel5_8007A0D4;

extern G2V12 statusTintLevel6_8007A0E0;

extern G2V12 statusTintLevel7_8007A0EC;

extern G2V12 statusTintPoison_8007A0F8;

extern G2V12 statusTintPoisonLevel1_8007A104;

extern G2V12 statusTintPoisonLevel2_8007A110;

extern G2V12 statusTintPoisonLevel3_8007A11C;

extern G2V12 statusTintPoisonLevel4_8007A128;

extern G2V12 statusTintPoisonLevel5_8007A134;

extern G2V12 statusTintPoisonLevel6_8007A140;

extern G2V12 statusTintPoisonLevel7_8007A14C;

#ifdef __psyz /* an alias (config/aliases.txt), on PC the place itself */
#define statusTint_8007A164 ((&statusTintPoisonLevel7_8007A14C)[2])
#else
extern G2V12 statusTint_8007A164;
#endif

#ifdef __psyz /* an alias (config/aliases.txt), on PC the place itself */
#define levantStatusBits_8008BD38 (*(unsigned int*)&saveData_8008B570.levantStatus_7C8)
#else
extern unsigned int levantStatusBits_8008BD38;
#endif

extern int IsFieldMinionVisible_800A79C8(int idx);

extern int* GetFieldMinionPos_800A7940(int idx);

extern int GetGameMode_800A6D50(int which);

extern int eventDispatchHalt_8008B540;

extern void ResetLevantActor_800A9414(void* buf, int action, int anim);

extern int GetLevantAnimSet_800AC474(int anim);

extern int GetLevantWeaponKind_800AC3E4();

extern Model* GetLevantModel_800AC38C();

extern InvSlot* FindInventorySlot_800AD58C(int id, int table);

extern InvSlot* GetInventoryTable_800AD604(int table);

extern int GetInventorySize_800AD374(int table);

extern int GetLastInventorySlot_800AD308(int table);

extern int GetInventorySlotId_800AD288(int slot, int table);

extern int GetInventorySlotCount_800AD2C8(int slot, int table);

extern int CanRemoveInventoryCount_800AD67C(int have, int count);

extern unsigned char* GetLevantAnimSetTable_800AC7B4(int set);

extern int TestValuableFlag_800AD73C(int valuable);

extern int CountCocoonsAndMinions_800AD8BC();

extern short cameraTargetScreenPos_8008D668[2];

extern int IsLevantActorIdle_800AB304();

extern int IsLevantDefending_800AB354();

extern int IsLevantActionFinished_800AB85C();

extern void ClearLevantBattleStance_800AB884();

extern void ResetLevantActorToIdle_800AB8AC();

extern void SkipLevantAnim_800AC318();

extern int FireEventTrigger_800A5C40();

extern void StopLevantAnimLoop_800AB910();

extern void SetLevantVisible_800ABBD8();

// the frames StartLevantAction_800A8A30 returns
typedef struct GameActionFrames
{
    short hit;
    short end;
} GameActionFrames;

// a Levant battle command's control state and animation (levantBattleActions_800B1084; camera.c reads it as struct_pair8)
typedef struct GameLevantBattleAction
{
    int state_0; // GameLevantCtl.state_C6 (0x10: StartLevantAction_800A8A30 starts nothing)
    int anim_4;
} GameLevantBattleAction;

extern GameLevantBattleAction levantBattleActions_800B1084[28];
extern int levantModelIds_800B1164[2];

// an actor command (eventfnc.h EvActorCmdEventfnc): kind 0 walk / 1 run / 2 turn to x/y/z, 3 / 4 play / stop a held
// animation, 5 play animation data, 6 visible, 7 ground move, 8 root motion, 9..11 play a motion
typedef struct GameActorCmd
{
    int actor_0;
    int kind_4;
    int wait_8; // the sender waits: the actor's busy bit is cleared when it is done
    int arg_C;
    int arg2_10;
    unsigned int opts_14; // kind 0..2: the animation (-1: default); 9..11: 1 no turn, 4 / 0x10 / 0x20 action flags, 8
    int x_18;
    int y_1C;
    int z_20;
    void* data_24; // kind 3: the script, kind 9..11: the path
} GameActorCmd;

typedef struct GameLevantActorInit
{
    int flags_0;
    int moveCmd_4;
    int action_8;
    int mode_C;
    int frame_10;
    char pad_14[4];
    short frameStep_18;
    short frameFrac_1A;
    short anim_1C;
    short prevAnim_1E;
    char pad_20[6];
    short blend_26;
    char pad_28[8];
    int fade_30;
    char pad_34[8];
    int status_3C;
} GameLevantActorInit;

// skeleton draw arguments (skel_draw.h AnimSkel)
typedef struct GameSkelDraw
{
    FtgObject* ftg_0;
    void* pos_4;
    void* rot_8;
    void* bones;
    void* base;
    char* pose;
    unsigned int frame;
    int flags;
    char* pos; // out: bone positions
    int scale_24;
    OT_TYPE* ot;
} GameSkelDraw;

#define tintImageRectY_8007DC82 (((short*)&tintImageRect_8007DC80)[1])

#define tintClutRectY_8007DC8A (((short*)&tintClutRect_8007DC88)[1])

extern void DrawAnimSkel_80046A58(void* sk, void* buf, char* pose);

extern void DrawAnimSkelBlend_80047E28(void* sk, void* base, char* pose, unsigned int frame, int w, void* buf, char* t);

extern void DrawSpriteVtxQuadsGT4_800459E4(void* bones, void* m, unsigned long* ot, int flags);

extern void GetAnimRootMotion_8004D288(void* out, void* s, int k);

extern void LevantControlTask_800A818C();
extern void EnemyAiFlee_800A2EEC();
extern void EnemyAiWanderChase_800A2FB8();
extern void EnemyAiWatchFlee_800A31DC();
extern void EnemyAiSleepChase_800A333C();
extern void EnemyAiWander_800A34D8();
extern void EnemyAiWander2_800A366C();
extern void EnemyAiAlertChase_800A3804();
extern void EnemyAiChaseAlert_800A3954();
extern void EnemyAiWanderBump_800A3A8C();
extern void EnemyAiChaseBehind_800A3BEC();
extern void EnemyAiWanderShort_800A3D24();
extern void EnemyAiHideFlee_800A3E88();
extern void EnemyAiWanderMid_800A3FC0();
extern void TileAnimTaskInit_800A09D8();
extern void FreeBattleResources_800A1444();

extern EventNode* battleTask_8008D624;
extern EventNode* battleMenuTask_8008D468;
extern EventNode* idleTask_8008D470;
extern EventNode* taskSlot_8008D444;
extern EventNode* enemyWindowTasks_8008B564;
extern EventNode* enemyWindowsLayoutTask_8008B568;
extern EventNode* actorWindowTask_8008D4B0;
extern EventNode* encounterTask_8008D674;
extern EventNode* shopCtrlTask_8008D438;
extern EventNode* shopMenuTask_8008D670;
extern EventNode* shelfMenuTask_8008D4A8;
extern EventNode* storeTask_8008D3E0;
extern EventNode* messageWindowTask_8008D640;
extern EventNode* vibrationTasks_8008D4B8;
extern EventNode* taskSlots_8008B4AC[2];
extern EventNode* actionTask_8008B4C0;
extern EventNode* taskSlots_8008D48C[3];
extern EventNode* taskSlots_8008D5F8[2];
extern EventNode* cmdMenuTask_8008D614;
extern EventNode* helpWindowTask_8008D63C;
extern EventNode* hitNumberTasks_8008D778;
extern EventNode* equipTask_8008D4C4;
extern EventNode* configTask_8008B4B8;
extern EventNode* taskSlot_8008D62C;
extern char ReturnWarpStart_800BCB00[];
extern const int gameHeader_800A05A0;
extern const char aAssertionFaile_800A05A4[];
extern const char aEnmbatleC_800A05CC[12];
extern const char aAssertionFaile_800A0660[];
extern const char aEventcomC_800A0688[];
extern const int unused_800A0694;
/* the jump table of LevantControlTask_800A818C (asm) and its targets, labels in the generated asm */
extern const char aAssertionFailed_800A07E0[];
extern const char aPLDISPC_800A0808[];
extern GameBattleChain encounterRecord_800ADE78;
extern short formation1_800ADE8C[2];
extern short formation2_800ADE90[2];
extern short formation3_800ADE94[4];
extern short *encounterFormations_800ADE9C[7];
extern void (*enemyAiBySpecies_800ADEB8[53][2])();
extern short battleStage00Maps_800AE060[8];
extern short battleStage01Maps_800AE070[10];
extern short battleStage02Maps_800AE084[4];
extern short battleStage03Maps_800AE08C[4];
extern short battleStage04Maps_800AE094[2];
extern short battleStage05Maps_800AE098[2];
extern short battleStage06Maps_800AE09C[2];
extern short battleStage07Maps_800AE0A0[14];
extern short battleStage08Maps_800AE0BC[8];
extern short battleStage09Maps_800AE0CC[4];
extern short battleStage10Maps_800AE0D4[2];
extern short battleStage11Maps_800AE0D8[14];
extern short battleStage12Maps_800AE0F4[6];
extern short battleStage13Maps_800AE100[4];
extern short battleStage14Maps_800AE108[2];
extern short battleStage15Maps_800AE10C[2];
extern short battleStage16Maps_800AE110[2];
extern short battleStage17Maps_800AE114[2];
extern short battleStage18Maps_800AE118[2];
extern short battleStage19Maps_800AE11C[2];
extern short battleStage20Maps_800AE120[6];
extern short battleStage21Maps_800AE12C[4];
extern short battleStage22Maps_800AE134[6];
extern short battleStage23Maps_800AE140[8];
extern short battleStage24Maps_800AE150[8];
extern short battleStage25Maps_800AE160[2];
extern short battleStage26Maps_800AE164[4];
extern short battleStage27Maps_800AE16C[2];
extern short battleStage28Maps_800AE170[2];
extern short battleStage29Maps_800AE174[2];
extern short battleStage30Maps_800AE178[18];
extern short battleStage31Maps_800AE19C[6];
extern short battleStage32Maps_800AE1A8[4];
extern short battleStage33Maps_800AE1B0[2];
extern short battleStage34Maps_800AE1B4[16];
extern short battleStage35Maps_800AE1D4[16];
extern short battleStage36Maps_800AE1F4[16];
extern short battleStage37Maps_800AE214[16];
extern short battleStage38Maps_800AE234[16];
extern short *battleStageMaps_800AE254[39];
extern short encounterArea00Maps_800AE2F0[6];
extern short encounterArea01Maps_800AE2FC[4];
extern short encounterArea02Maps_800AE304[2];
extern short encounterArea03Maps_800AE308[8];
extern short encounterArea04Maps_800AE318[6];
extern short encounterArea05Maps_800AE324[6];
extern short encounterArea06Maps_800AE330[6];
extern short encounterArea07Maps_800AE33C[6];
extern short encounterArea08Maps_800AE348[16];
extern short encounterArea09Maps_800AE368[10];
extern short encounterArea10Maps_800AE37C[4];
extern short encounterArea11Maps_800AE384[6];
extern short encounterArea12Maps_800AE390[8];
extern short encounterArea13Maps_800AE3A0[6];
extern short encounterArea14Maps_800AE3AC[6];
extern short encounterArea15Maps_800AE3B8[6];
extern short encounterArea16Maps_800AE3C4[6];
extern short *encounterAreaMaps_800AE3D0[17];
extern int encounterArea00Species_800AE414[3];
extern int encounterArea01Species_800AE420[3];
extern int encounterArea02Species_800AE42C[3];
extern int encounterArea03Species_800AE438[3];
extern int encounterArea04Species_800AE444[3];
extern int encounterArea05Species_800AE450[3];
extern int encounterArea06Species_800AE45C[3];
extern int encounterArea07Species_800AE468[3];
extern int encounterArea08Species_800AE474[3];
extern int encounterArea09Species_800AE480[3];
extern int encounterArea10Species_800AE48C[3];
extern int encounterArea11Species_800AE498[3];
extern int encounterArea12Species_800AE4A4[3];
extern int encounterArea13Species_800AE4B0[3];
extern int encounterArea14Species_800AE4BC[3];
extern int encounterArea15Species_800AE4C8[3];
extern int encounterArea16Species_800AE4D4[3];
extern int *encounterAreaSpecies_800AE4E0[17];

// an encounter table row (encounterTables_800AE524; RollEncounterGroup_800A4DD0)
typedef struct GameSpawnEntry
{
    unsigned int chance : 8;
    unsigned int species0 : 3; // encounterSpecies_800AEB6C index
    unsigned int v0 : 5;
    unsigned int species1 : 3; // encounterSpecies_800AEB6C index
    unsigned int v1 : 5;
    unsigned int species2 : 3; // encounterSpecies_800AEB6C index
    unsigned int v2 : 5;
} GameSpawnEntry;
typedef struct GameSpawnMember
{
    int species_0;
    int f4;
    int f8;
} GameSpawnMember;

extern GameSpawnEntry encounterTables_800AE524[73][3];
extern short encounterTable00Maps_800AE890[2];
extern short encounterTable01Maps_800AE894[2];
extern short encounterTable02Maps_800AE898[2];
extern short encounterTable03Maps_800AE89C[2];
extern short encounterTable04Maps_800AE8A0[2];
extern short encounterTable05Maps_800AE8A4[2];
extern short encounterTable06Maps_800AE8A8[2];
extern short encounterTable07Maps_800AE8AC[2];
extern short encounterTable08Maps_800AE8B0[2];
extern short encounterTable09Maps_800AE8B4[2];
extern short encounterTable10Maps_800AE8B8[2];
extern short encounterTable11Maps_800AE8BC[2];
extern short encounterTable12Maps_800AE8C0[2];
extern short encounterTable13Maps_800AE8C4[2];
extern short encounterTable14Maps_800AE8C8[2];
extern short encounterTable15Maps_800AE8CC[2];
extern short encounterTable16Maps_800AE8D0[2];
extern short encounterTable17Maps_800AE8D4[2];
extern short encounterTable18Maps_800AE8D8[2];
extern short encounterTable19Maps_800AE8DC[2];
extern short encounterTable20Maps_800AE8E0[2];
extern short encounterTable21Maps_800AE8E4[2];
extern short encounterTable22Maps_800AE8E8[2];
extern short encounterTable23Maps_800AE8EC[2];
extern short encounterTable24Maps_800AE8F0[2];
extern short encounterTable25Maps_800AE8F4[2];
extern short encounterTable26Maps_800AE8F8[2];
extern short encounterTable27Maps_800AE8FC[2];
extern short encounterTable28Maps_800AE900[2];
extern short encounterTable29Maps_800AE904[2];
extern short encounterTable30Maps_800AE908[2];
extern short encounterTable31Maps_800AE90C[2];
extern short encounterTable32Maps_800AE910[2];
extern short encounterTable33Maps_800AE914[16];
extern short encounterTable34Maps_800AE934[2];
extern short encounterTable35Maps_800AE938[4];
extern short encounterTable36Maps_800AE940[2];
extern short encounterTable37Maps_800AE944[2];
extern short encounterTable38Maps_800AE948[2];
extern short encounterTable39Maps_800AE94C[2];
extern short encounterTable40Maps_800AE950[2];
extern short encounterTable41Maps_800AE954[2];
extern short encounterTable42Maps_800AE958[2];
extern short encounterTable43Maps_800AE95C[2];
extern short encounterTable44Maps_800AE960[2];
extern short encounterTable45Maps_800AE964[2];
extern short encounterTable46Maps_800AE968[2];
extern short encounterTable47Maps_800AE96C[2];
extern short encounterTable48Maps_800AE970[2];
extern short encounterTable49Maps_800AE974[2];
extern short encounterTable50Maps_800AE978[2];
extern short encounterTable51Maps_800AE97C[2];
extern short encounterTable52Maps_800AE980[2];
extern short encounterTable53Maps_800AE984[2];
extern short encounterTable54Maps_800AE988[2];
extern short encounterTable55Maps_800AE98C[2];
extern short encounterTable56Maps_800AE990[2];
extern short encounterTable57Maps_800AE994[2];
extern short encounterTable58Maps_800AE998[2];
extern short encounterTable59Maps_800AE99C[2];
extern short encounterTable60Maps_800AE9A0[2];
extern short encounterTable61Maps_800AE9A4[2];
extern short encounterTable62Maps_800AE9A8[2];
extern short encounterTable63Maps_800AE9AC[2];
extern short encounterTable64Maps_800AE9B0[2];
extern short encounterTable65Maps_800AE9B4[2];
extern short encounterTable66Maps_800AE9B8[2];
extern short encounterTable67Maps_800AE9BC[2];
extern short encounterTable68Maps_800AE9C0[2];
extern short encounterTable69Maps_800AE9C4[2];
extern short encounterTable70Maps_800AE9C8[2];
extern short encounterTable71Maps_800AE9CC[2];
extern short encounterTable72Maps_800AE9D0[5];
extern short *encounterMapLists_800AE9DC[73];
extern GameSpawnMember encounterGroups_800AEB00[3][3];
extern int encounterSpecies_800AEB6C[4];
extern int mdecBufferMode_800AEB7C;
extern EffectFile eventEffects_800AEB80;
extern int *eventReloc_800AEBBC;
extern void *eventTiy_800AEBC0[2];
extern void *eventDataBuf_800AEBC8;
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
extern int eventTempFlags_800AEBD4;
extern int sceneScriptId_800AEBD8;
extern int nextScriptId_800AEBDC;
extern int eventBattlePending_800AEBE0;
extern int eventBattleLoseWarp_800AEBE4;
extern int currentMessageId_800AEBE8;
extern int currentVoice_800AEBEC;
extern void* voiceTable_800AEBF0;
extern int eventResult_800AEBF4;
// a menu cursor of the MAP overlay's destination select (UpdateMenuCursor_8003D794 / GetMenuCursorIndex_8003DA54)
typedef struct GameMapCursor
{
    short cols_0;
    short rows_2;
    short count_4;
    short flags_6; // 0x40: scrolls
    short index_8; // on screen
    short scroll_A;
} GameMapCursor;

// the MAP overlay's destination select state, kept in GAME across the MAP overlay's loads
typedef struct GameMapSelect
{
    short area_0; // the selected area (-1: none yet)
    short dest_2;
    GameMapCursor cursors_4[6]; // one per area
} GameMapSelect;

extern GameMapSelect mapSelect_800AEBF8;
extern int mapArea0Map00Entrances_800AEC44[20];
extern int mapArea0Map01Entrances_800AEC94[20];
extern int mapArea0Map02Entrances_800AECE4[16];
extern int mapArea0Map03Entrances_800AED24[304];
extern int mapArea0Map04Entrances_800AF1E4[32];
extern int mapArea1Map00Entrances_800AF264[36];
extern int mapArea1Map01Entrances_800AF2F4[32];
extern int mapArea1Map02Entrances_800AF374[20];
extern int mapArea1Map03Entrances_800AF3C4[20];
extern int mapArea1Map04Entrances_800AF414[36];
extern int mapArea1Map05Entrances_800AF4A4[24];
extern int mapArea1Map06Entrances_800AF504[56];
extern int mapArea1Map07Entrances_800AF5E4[20];
extern int mapArea1Map08Entrances_800AF634[20];
extern int mapArea1Map09Entrances_800AF684[20];
extern int mapArea1Map10Entrances_800AF6D4[20];
extern int mapArea1Map11Entrances_800AF724[8];
extern int mapArea2Map00Entrances_800AF744[16];
extern int mapArea2Map01Entrances_800AF784[24];
extern int mapArea2Map02Entrances_800AF7E4[12];
extern int mapArea2Map03Entrances_800AF814[12];
extern int mapArea2Map04Entrances_800AF844[20];
extern int mapArea2Map05Entrances_800AF894[20];
extern int mapArea2Map06Entrances_800AF8E4[28];
extern int mapArea2Map07Entrances_800AF954[8];
extern int mapArea2Map08Entrances_800AF974[8];
extern int mapArea2Map09Entrances_800AF994[16];
extern int mapArea2Map10Entrances_800AF9D4[16];
extern int mapArea2Map11Entrances_800AFA14[16];
extern int mapArea4Map00Entrances_800AFA54[28];
extern int mapArea4Map01Entrances_800AFAC4[56];
extern int mapArea4Map02Entrances_800AFBA4[80];
extern int mapArea4Map03Entrances_800AFCE4[200];
extern int mapArea4Map04Entrances_800B0004[100];
extern int mapArea5Map01Entrances_800B0194[48];
extern int mapArea5Map02Entrances_800B0254[68];
extern int mapArea5Map03Entrances_800B0364[112];
extern void *mapArea0Maps_800B0524[6];
extern void *mapArea1Maps_800B053C[13];
extern void *mapArea2Maps_800B0570[13];
extern void *mapArea3Maps_800B05A4[13];
extern void *mapArea4Maps_800B05D8[6];
extern void *mapArea5Maps_800B05F0[6];
extern GameMapEntrance **mapTable_800B0608[7];
extern int areaMapCounts_800B0624[29];
extern int gameModeChanged_800B0698;
extern int levantStartPos_800B069C[5];
extern int shopRequest_800B06B0[3];
extern int saveRequest_800B06BC;
extern int unused_800B06C0[3];
extern EventDesc mapLoaderTaskDef_800B06CC;
extern EventDesc areaLoaderTaskDef_800B06E4;
extern EventDesc levantModelTaskDef_800B06FC;
extern EventDesc modelLoaderTaskDef_800B0714;
extern EventDesc actorTasksDef_800B072C;
extern EventDesc tileAnimTaskDef_800B0744;
extern EventDesc eventScriptsDef_800B075C;
extern EventDesc encounterWatchTaskDef_800B0774;
extern EventDesc battleTaskDef_800B078C;
extern EventDesc battleMenuTaskDef_800B07A4;
extern EventDesc taskSlotDef_800B07BC;
extern EventDesc enemyWindowsTaskDef_800B07D4;
extern EventDesc enemyWindowTaskDef_800B07EC;
extern EventDesc actorWindowTaskDef_800B0804;
extern EventDesc helpWindowTaskDef_800B081C;
extern EventDesc levantControlTaskDef_800B0834;
extern EventDesc taskSlotsDef_800B084C;
extern EventDesc levantActorTaskDef_800B0864;
extern EventDesc encounterTaskDef_800B087C;
extern EventDesc enemyAiTasksDef_800B0894;
extern EventDesc mapEventTasksDef_800B08AC;
extern EventDesc eventEntitiesDef_800B08C4;
extern EventDesc prevModeTaskDef_800B08DC;
extern EventDesc mapOverlayTaskDef_800B08F4;
extern EventDesc fieldMenuTaskDef_800B090C;
extern EventDesc shopCtrlTaskDef_800B0924;
extern EventDesc shopMenuTaskDef_800B093C;
extern EventDesc shelfMenuTaskDef_800B0954;
extern EventDesc storeTaskDef_800B096C;
extern EventDesc taskSlotDef_800B0984;
extern EventDesc chapterOverlayTaskDef_800B099C;
extern EventDesc sporeTaskDef_800B09B4;
extern EventDesc fieldModeTaskDef_800B09CC;
extern EventDesc subOverlayTaskDef_800B09E4;
extern GameTaskListDef globalTaskLists_800B09FC[2];
extern GameTaskListDef gameModeChapterTasks_800B0A0C[4];
extern GameTaskListDef gameModeFieldTasks_800B0A2C[26];
extern GameTaskListDef gameModeBattleTasks_800B0AFC[35];
extern GameTaskListDef gameModeBattleEndTasks_800B0C14[4];
extern GameTaskListDef gameModeEquipTasks_800B0C34[3];
extern GameTaskListDef gameModeMenuTasks_800B0C4C[7];
extern GameTaskListDef gameModeShopTasks_800B0C84[12];
extern GameTaskListDef gameModeSaveTasks_800B0CE4[4];
extern GameTaskListDef gameModeReturnTasks_800B0D04[2];
extern GameTaskListDef gameModeMapTasks_800B0D14[6];
extern GameTaskListDef gameModeUnused9Tasks_800B0D44[3];
extern GameTaskListDef gameModeLoadingTasks_800B0D5C[3];
extern GameTaskListDef *gameModeTaskLists_800B0D74[12];
extern EventDesc* gameEventListDefs_800B0DA4[58];
extern EventDesc gameMainTaskDef_800B0E8C;
extern EventDesc* endMovie_800B0EA4[5];
extern GameFieldModeHandler fieldModeHandlers_800B0EB8[1];
extern int fieldMode_800B0EC0;
extern GameFieldMinions fieldMinions_800B0EC4;
extern char levantBones_800B0EF8;
extern int unused_800B0EFC[45];
extern SVECTOR levantBoneScale_800B0FB0[22];
extern int dword_800B1168;
extern int levantBaseModels_800B116C[19];
extern unsigned char levantOutfitModelOffsets_800B11B8[20];
extern int levantSavedFtgIds_800B11CC[4];
extern int levantAnimSets_800B11DC[19];
extern int battleFlags_800B1228;
extern unsigned int battleHitEnemies_800B122C; // enemy slots hit in the battle (BATTLE)
extern int battleResult_800B1230;              // how the last battle ended (BATTLE, EVENTFNC)
extern int unused_800B1234;
extern GameEnemyResult battleEnemyResults_800B1238[3]; // the enemies of the last battle (BATTLE, MENU)
extern int unused_800B125C;
extern GameEncounter gCtx_800B1260;
extern GameEnemy eventEnemy_800B1CB8;
typedef void (*EventHookFn)(void* arg); // the map code's (SetEventHook_800A5F90), for the script command EvCmdCallHook_800B91CC
extern EventHookFn eventHook_800B1D98;
extern int unused_800B1D9C;
extern EventNode *levantModelTask_800B1DA0[1];
extern EventNode *mapOverlayTask_800B1DA4[1];
extern EventNode *mapEventTasks_800B1DA8[1];
extern EventNode *fieldModeTask_800B1DAC;
extern EventNode *chapterOverlayTask_800B1DB0[1];
extern EventNode *subOverlayTask_800B1DB4[1];
extern EventNode *tileAnimTask_800B1DBC;
extern EventNode *prevModeTask_800B1DC0[1];
extern int gameStartMode_800B1DC8[2];
extern Pool levantPool_800B1DD0;
extern int unused_800B1DF4;
extern char levantByte_800B1DF8;
extern int unused_800B1DFC[304];

/* the jump table of UpdateLevantBattleAction_800AA51C (asm) and its targets, labels in the generated asm */
extern GameActionFrames StartCommandAction_80018A4C(Actor* obj, int* cmd, ActorScriptCmd** scripts, int c);

/* ---- moved from the .c files: types ---- */
// the rolled encounter groups (EvSpawnTable on the EVENTFNC side)
typedef struct GameSpawnOut
{
    GameSpawnMember* members_0[3];
    int (*places_C[3])[4]; // MapList16.items_4 entries
} GameSpawnOut;

// the work area of LevantModelTask_800ACB64
typedef struct GameLevantModelWork
{
    int state;
    int flags; // 1: reload the model, 2: reload the outfit, 4: load the weapon's animations, 8 / 0x10: FTG save / swaps
    int model_8; // saveData_8008B570.hasArmor_830 (levantModelIds_800B1164 index)
    int prevModel_C;
    int weaponKind_10; // saveData_8008B570.weaponKind_834
    int weaponKind_14;
    int outfit_18; // saveData_8008B570.outfit_836
    int outfit_1C;
} GameLevantModelWork;

/* GAME's own functions/data used before their definition or from another of its files */
void FreeLevantAnimSetAnims_800ACF3C(GameLevantModelWork* work);
void LoadLevantAnimSetAnims_800ACFB8();
extern int dword_800B1CA8[4];

/* code loaded behind GAME (0x800B1E00..0x800B66C0, not an overlay of overlays.py); MENU calls sub_800B330C too */
extern int sub_800B330C(void);
extern GameSpawnEntry* sub_800B2B40();

/* EVENTFNC-side (eventfnc.h; EVENTFNC is loaded under GAME) */
extern void LoadEventEffectFile_800BC7A8(int* file);
extern void LoadRelocBlob_800BC854(int* src);
extern void LoadEventTiy_800BC98C(int* tiy);
extern void CopyEventData_800BCA18(unsigned int* src, unsigned int size);
extern void LoadEventRecordTables_800BCA68(int* data);

/* exe-side, to move to effect_data.h (declared there as ActorScriptCmd* commandScripts_8007A024[]) */
extern int name_8007A024[];
/* exe-side, to move to effect_data.h */
extern ModelVramSlot* gameModelVramSlots_8007DC6C;

/* GAME: functions called before their definition (or from another of its files) */
/* (the task definitions at the top of game_3.c point to these) */
void FieldModeTask_800A7720(GameTask* task);
void GameMainInit_800A68CC(GameTask* task, GameMainWork* work);
void LevantActorTask_800A9564(int entry, GameLevantActor* lev);
void LevantActorTaskExit_800A955C();
void LevantModelTaskExit_800ACF0C();
void LevantModelTaskInit_800ACAA4(int* task, int* work);
void ReturnToPrevGameMode_800A8108();
void StartChapterOverlay_800A7690(GameTask* task, int* work);
void StartMapOverlay_800A75F8(GameTask* task, int* work);
int AreLevantFilesLoaded_800AC768();
void ClearLevantDefending_800AB28C();
void ClearLevantFade_800AB150(GameLevantFade* lev);
GameAi* CreateEnemyAiEvent_800A2D90(Actor* actor, UnitStats* minion, int active);
void DrawLevantModel_800A9708(GameLevantActor* lev);
int EnemyAiCheckBlocked_800A4804(GameAi* ai);
void EnemyAiFleeStep_800A459C(GameAi* ai);
int EnemyAiTurnStep_800A4470(GameAi* ai);
int FreeMdecBuffer_800A5854(void);
int GetCameraTargetQuadrant_800A8930();
int GetLevantAnimFlags_800AC900(int anim, int set);
HitTimes* GetLevantAnimHitFrames_800AC9CC(int anim);
int GetSetReturnEntrance_800A683C(int entrance);
int IsInFrontHalf_800A4884(Vec3i* from, short* rot, Vec3i* to);
int IsLevantAnimLoadedOrFree_800AAFD8(int anim);
int IsOtherEncounterArea_800A5240(int entrance, int prevEntrance);
int IsSceneHeld_800A5E68(void);
int LoadLevantAnimById_800AC604(int anim, int resident);
void PlayLevantScriptAnim_800AB9A8(int anim, int nextAnim, int blend);
void RequestLevantActionEffect_800ABCF4(GameLevantActor* lev);
void RunEventListExit_800A74F0(EventNode* node);
void RunLevantActionCues_800ABDF0(GameLevantActor* lev);
void RunLevantAnimCues_800AA220(GameLevantActor* lev);
void SetLevantDefending_800AB264();
void SetLevantLastCapture_800AC340(int on);
void SetLevantPath_800ABAA4(G2Path* path);
void SetLevantRootMotion_800AA140(GameLevantActor* lev);
void SetLevantStatusTint_800ABECC();
void SetLevantFlag10000_800AB2B4();
void ClearLevantFlag10000_800AB2DC();
void SetLevantFlag100000_800ABB98(int fromLoop);
void UpdateLevantActionState_800AAF58(GameLevantActor* lev);
void UpdateLevantActorModel_800AB8DC();
void UpdateLevantTurn_800A99DC(GameLevantActor* lev);
void UpdateLevantMove_800A9A9C(GameLevantActor* lev);

int PlayActorEffect_800184DC(struct ActorEffectReq* req, int slot);

/* left undeclared on purpose: these return short/u_char, but their callers in game_3.c see them as int (implicit
   declarations, no sign extension of the result; a prototype changes the code):
   short GetLevantActionEndFrame_800AB4D8(int anim)
   short GetLevantActionHitFrame_800AB750(int anim)
   short GetLevantAnimEventFrame_800AC944(int anim, int set)
   unsigned char GetLevantAnimFileId_800AC988(int anim, int set)
   unsigned short GetLevantAnimLastFrame_800AC8BC(int anim, int set)
   short GetLevantAnimLoopEnd_800AC878(int anim, int set)
   short GetLevantAnimLoopStart_800AC834(int anim, int set)
   short GetLevantAnimStartFrame_800AC7F0(int anim, int set) */
#ifdef __psyz /* a modern compiler wants them declared (the result is the same, the callee extends it) */
short GetLevantActionEndFrame_800AB4D8(int anim);
short GetLevantActionHitFrame_800AB750(int anim);
short GetLevantAnimEventFrame_800AC944(int anim, int set);
unsigned char GetLevantAnimFileId_800AC988(int anim, int set);
unsigned short GetLevantAnimLastFrame_800AC8BC(int anim, int set);
short GetLevantAnimLoopEnd_800AC878(int anim, int set);
short GetLevantAnimLoopStart_800AC834(int anim, int set);
short GetLevantAnimStartFrame_800AC7F0(int anim, int set);
#endif
/* exe-side, to move to unit_query.h */
/* exe-side, to move to effect_data.h */
/* exe-side, to move to engine.h */
/* libc (PSY-Q) */
extern int rand(void);

// event callbacks of the sub-overlays GAME starts (MAP, MENU, SHOPCTRL, SHOP, SHOPENTR, WPNSHOP)
void StartFieldMenu_800BD40C();
void ShopCtrlInit_800B67C0();
void ShopMenuTask_800BB444();
void ShelfMenuTask_800B7000();
void StoreTask_800BB1F4();
void MapSelectEnd_800B6F60();
