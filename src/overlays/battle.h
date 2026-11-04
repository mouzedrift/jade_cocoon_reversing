// BATTLE.BIN: declarations shared by its source files
// BATTLE.BIN
#include "common.h"

#include "funcs.h"

#include "globals.h"

#include "actor.h"
#include "minion_menu.h"
#include "engine.h"
#include "minion_init.h"

#include "model.h"
#include "camera.h"


extern int GetActiveSwapEnemy_800A2AB4();

extern void SetHitVariant_80018430(int a);

extern int GetEmptyCocoons_800AD8E4();

extern void InterpolateWindowRect_8004196C(void* a0, void* a1, int a2, int a3, int a4);

extern void AddDrawAreaPrim_8003326C();

extern void AddClipDrawAreaPrim_80033308();

extern unsigned short padPressed_8009194C;

extern int MeasureTextWidth_8003E4C8();





extern unsigned char enemyUnits_800C9E80[4];



extern int partyMinionMask_800C9E78;




typedef struct BatMenu_a
{
    short f0;
    short f2;
    unsigned short count_4;
    unsigned short flags_6;
    short cursor_8;
    short scroll_A;
} BatMenu_a; // same layout as the exe's MenuCursor










// a battle command (curCommand_800C9C88 is the current one, unitReactions_800C9CC8 holds each unit's reaction).
// Units: 0 Levant, 1..3 his minions (one is summoned at a time), 4..6 the enemies.
typedef struct BatCmd_a
{
    int kind_0; // 0 attack, 1 magic, 2 summon, 3 recall, 4 item, 5 capture, 6 special attack, 7 flee,
                // 8 change fighter, 0xB killed, 0x12 defend, 0x14 none, 0x15 an enemy calls an ally, 0x1A capture of the last enemy
    int arg_4;
    int mask_8; // acting unit bits
    int targets_C; // target unit bits
} BatCmd_a;

// the battle menu's enemy target list. bits_2 is a member (a global array would be word aligned, it is at 0x800C9E72);
// the code indexes it through its decayed address (`*(t.bits_2 + n)`, a bits pointer), which keeps the base at +2
typedef struct BatEnemyTargets_a
{
    unsigned char flag_0; // cleared when the menu opens
    unsigned char unk_1;
    unsigned char bits_2[3]; // unit bit of each living enemy, in menu order
} BatEnemyTargets_a;
extern BatEnemyTargets_a enemyTargets_800C9E70;

// the enemy AI's context (ChooseEnemyCommand_800C4118)
typedef struct BatTask
{
    unsigned int* magicBits_0; // &self_10->magicBits_80
    UnitSkills* skills_4;      // &self_10->skills_6C
    BatCmd_a* cmd_8;           // the command to fill in
    int slot_C;                // the enemy's slot (unit slot_C + 4)
    UnitStats* self_10;        // the acting encounter minion
    UnitStatus* target_14;     // its target: Levant or the summoned minion
    int targetMask_18;         // the target's unit bit
    int f1C;
} BatTask;


extern void AiSetCommand_800C6AFC(BatTask* t, int a, int b);






extern int menuErrorText_800C9E7C;

extern int GetLatestHitFrame_800BE364();

extern void UpdateAction_800BE3C0();

extern int IsActionDone_800BEA94();


extern int GetUnitPos_800BC6CC();

extern void FadeOutSeqSlot_800313C8(int);

extern EventNode* dword_8008D624;



extern char savedEnemyCursor_800C9D56;


extern int GetSpecialStageIndex_800A5354();

extern int GetEncounterAdvantage_800BAAD8();

extern void SpawnEncounterEnemies_800A1F80();

extern void StartLevantBattle_800A8D0C();

extern void DisableCameraPoints_800A096C();

extern void BattleLoad_800BAC4C();


extern int GetEnemyPos_800A2C28();

extern int IsActorActionDone_800BEB50();

extern int AreReactionsDone_800BEB68();

extern int AnyHitNumberActive_800BF47C();

extern int IsUnitInBattle_800BC784();

typedef struct BatV12_a
{
    int x;
    int y;
    int z;
} BatV12_a;

extern unsigned int battleHitEnemies_800B122C;

extern int dword_800ADE88;

extern int IsSummonedMinionIdle_800C0D60();

extern int IsLevantIdle_800A89F0();

extern int IsEnemyIdle_800A2550();

extern int IsEffectTaskIdle_800148D4();

extern int CalcElementAngle_800C09D4();

extern int sub_800B4318();

extern void Midpoint3D_8003B95C();

extern void BattleNextTurn_800BAE74();

extern void ClearBattleFlag_800BC850(unsigned int);

extern char dword_80091D40[];

// GAME's battle chain record (game.h GameRec_1): f0 1 while a chain of battles runs, fc the battle count, f10 the next entry
typedef struct BatChain_a
{
    int f0, f4, f8, fc, f10;
} BatChain_a;
extern BatChain_a encounterRecord_800ADE78;

extern int levantAnimSet_80091C74;

extern int dword_8007DC74;


extern short dword_80091CE0[];

extern void sub_800B42A8();

extern void EnemyChooseCommand_800A2618();

extern int StartBattleMenu_800C6EFC();

extern void WaitBattleMenu_800BB940();

extern void DestroyEncounterActors_800A1B78();

extern void FreeActiveOverlay_8002C014();

extern void LoadLevantAnimSet_800AC708();

extern void StopLevantAnimLoop_800A9364();

extern int IsLevantActionFinished_800A8DAC();

extern int AreAllEncounterEnemiesGone_800A1B2C();



extern void SsSepSetDecrescendo();

extern void BattleEndReturnToField_800BA848();

extern void BattleEndWaitFade_800BA4F4();

// BuildMinionModelReq_800C064C: what StartModelTask_80010850 builds a minion's model from
typedef struct BatModelReq_a
{
    int count_0; // distinct parts
    int ids_4[3];
    int nums_10[3];
    int f1C;
    int f20;
    int angle_24;
    int f28;
    int f2C;
    int f30;
    int f34;
} BatModelReq_a;


extern void BuildMinionModelReq_800C064C();

extern void StartModelTask_80010850();

extern int GetUnitTurnSpeed_800BF784();

extern void TurnUnitsToward_800BC468();

// GAME's record of one enemy for the battle result (dword_800B1238)
typedef struct BatEnt_a
{
    int exp_0;
    short species_4; // -1: no enemy in the slot
    short killer_6;  // the unit that defeated or captured it
    short level_8;
    short kind_A;    // the command that ended it (7: none)
} BatEnt_a;

typedef struct BatCol_a
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} BatCol_a;

extern int dword_800B1230;

extern BatEnt_a dword_800B1238[];

















extern EventNode* dword_8008B4C0;

extern int dword_800ADE88;

extern int eventDispatchHalt_8008B540;

extern int battleStageId_80083BD0;

// per battle stage (indexed by battleStageId_80083BD0)
typedef struct BatStage_a
{
    unsigned short* list_0;
    unsigned short effect_4; // effect file to load
    unsigned char model_6;
    unsigned char f7;
    short floor_8;
    short anim_A;
    unsigned short* models_C;
} BatStage_a;


extern int IsMsgWindowAlive_80034AB8();

extern int GetMsgWindowResultIfDone_800349B4();

extern void CloseMsgWindow_80034A84();

extern void TriggerActorEffect_8001E28C();

extern void RemoveEnemy_800A2924();





extern void memset();


extern void SetFadeMode_8001C19C();

extern void SwapEncounterEnemy_800A2AE8();

extern void PlaySeqSlot_80031160();

extern void StartCommandAction_80018A4C();

extern int LoadOverlay_80020BF8();

extern void StopSceneDarken_8001AAF4();

extern void TurnLevantToward_800A8D48();

extern void TurnEnemyToward_800A25D8();

extern int GetEnemySpecies_800A2BE4();

extern int AdvanceTurnGauges_800BF6BC();

extern int GetUnitsCenter_800BC378();

extern int AreUnitsReady_800BDE04();

extern int IsUnitOnField_800BC570();

extern int GetUnitSide_800BC7DC();

extern void TurnUnitToward_800BC4D4();

extern void ResetTurnGauge_800BF770();

extern void SetBattleFlag_800BC838();

extern void BattleEndFadeOut_800BA624();

extern void BattleEndFled_800BA6A0();

extern void BattleEndUnload_800BA788();

extern void RemoveAliveEnemies_800BA720();

extern void BattleNextTurn_800BAE74();

extern void BattleFinish_800BB1B0();

extern void WaitChainMessageClosed_800BB168();

extern void BeginUnitTurn_800BB380();

extern void CmdSwapMinionLoad_800BBC84();

extern void ActionRun_800BDC3C();

extern void HitNumberTask_800BF4D0();

extern void ActorWindowTask_800C0254();

extern void CmdRecall_800BBDB4();

extern void TurnSummonedMinionToward_800C0DB0();

extern void WaitBtlExecLoaded_800BC324();

extern void CmdRecallEnd_800BBE7C();



typedef struct BatObj_a
{
    int f0;
    int f4;
    void (*next_8)();
    int fc;
} BatObj_a;

// when a unit's action hits and when it ends (frames of the action timeline)
typedef struct BatPair_a
{
    short hit_0;
    short end_2;
} BatPair_a;


extern EventNode* dword_8008B568;

extern EventNode* dword_8008B564;

extern EventNode* dword_8008D4B0;

extern EventNode* dword_8008D63C;

extern EventNode* hitNumberTasks_8008D778;



extern short effectOutcomeFlag_8008D780;

extern void CmdActionReactions_800BBA70();

extern void CmdRecallDone_800BBE00();

extern void CmdEnemySwapJoin_800BC05C();

extern void CmdEnemyCallJoin_800BBF64();

extern void ActionStart_800BDA28();

extern void ActionWaitReady_800BDBB0();

extern void HelpWindowTask_800C04A4();

extern int AreUnitsIdle_800BDD3C();

extern void UpdateWindowsHidden_800BF2E8();

extern void FaceActorAndTargets_800BDEBC();

extern void StartActorAction_800BDF74();

extern void StartReactions_800BDFAC();

extern void AlignActionTimings_800BE2C8();

extern int GetPartyMinionMask_800C0A9C();

extern int GetSummonedMinionSlot_800C0D50();

typedef struct BatTask_a
{
    int f0;
    int f4;
    void (*next_8)();
    int* fc;
} BatTask_a;



extern unsigned int battleFlags_800B1228;

// the summoned minion's actor and where it appears (LoadSummonedMinion_800C0AEC)
typedef struct BatSummon_a
{
    Actor* actor_0;
    int x_4;
    int y_8;
    int z_C;
    int rotY_10;
} BatSummon_a;


// an animated window rect (ActorWindowTask_800C0254, HelpWindowTask_800C04A4)
typedef struct BatWin_b
{
    unsigned int frame_0;
    short from_4[4];
    short rect_C[4];
} BatWin_b;
















extern int IsSceneFadeDone_8001AB94(void*);

extern int IsLevantIdle_800A89F0();

extern void BattleEndFadeOut_800BA624();

extern void InputCommand_800BB894();

extern void CmdSummonWait_800BBCC8();

extern void WaitActionTask_800BC144();

extern void ClearBattleFlag_800BC850(unsigned int);

extern int StartActionTask_800BC28C();

extern int NeedsStatusReaction_800BC1A8();

extern struct BatPair_a* StartUnitAction_800BE058();

extern void ResetWindowHighlights_800BFC10();

extern void StartEnemyWindows_800BFC40();

extern void StartActorWindow_800C01D8();

extern void StartHelpWindow_800C0440();

extern int FreeSummonedMinion_800C0BA0();

extern int LoadSummonedMinion_800C0AEC();

extern void ResetUnitReactions_800BB794();

extern UnitStatus* GetPartyMinionStatus_800C0F78(int);

extern void StartScreenFlash_8001C02C(void*);

extern void SetActorTurnTarget_8001DB00(Actor*, int, int);

extern void GetActorHitFrame_80018E5C(Actor*, int);

extern void SetActorStatusTint_80018EBC(Actor*, UnitStatus*);


extern int IsSummonedMinionReady_800C0D88();

extern int IsLevantReady_800A8BE4();

extern int IsEnemyReady_800A2594();

extern int AreLevantFilesLoaded_800AC768();

extern void ResumeOtherEnemies_800A1F0C();

extern void SetLevantVisible_800A9384(int a);

extern void ClearLevantBattleStance_800A8DCC();

extern void UnlockLevantMovement_800A89C8();

extern void EndEncounter_800A1E1C();

extern void EnableCameraPoints_800A094C();

extern void WarpAfterLostBattle_800A5FAC();

extern void WaitBattleReturnFiles_800A14E0();

extern void WaitMapReloadAfterBattle_800A15FC();

extern int forceMapReload_80091C9C;

extern short sinTable_80084540[];

extern int* GetEncounterLeaderPos_800A1E48(void); // GAME.BIN: an actor's pos_38

extern short* GetEncounterLeaderRot_800A1E68(void); // GAME.BIN: the same actor's rot_5C

extern int LoadSeqSlotSound_800303E8();

extern int IsSoundTaskReady_80030688();

extern void StartBattleCamera_80037748();

extern void LoadUiTiy_8002BF74();

extern void StartBattleWindows_800BFB80();

extern int sub_800B4200(BatChain_a* p);

extern int sub_800B41D0(BatChain_a* p);

extern int* sub_800B41A8(BatChain_a* p);


extern void WaitChainMessage_800BB100();

extern void SelectActingUnit_800BB314();

extern void ResetCurrentCommand_800BB74C();

extern void ResetTurnResults_800BB7D4();

extern void PrepareCommandInput_800BB860();

extern BatV12_a* AveragePositions_800BC5EC();

extern void ApplyBattleCommand_800BEBB8();

extern void MoveBattleCameraForAction_80037828(int a, int b, int c);

extern void ActionWaitIdle_800BDB4C();

extern void StartLevantAction_800A8A30();

extern void StartEnemyCommandAction_800A2684();

extern void TriggerLevantAction_800A8C0C(int b);

extern void TriggerEnemyEffects_800A2760(BatCmd_a* p, int b);

extern void StartBattleCameraSpline_800377B4(int a, int b, int c);

extern void StartCameraShake_80037BFC(int a);

extern void PlaySfx_80031494(int id);

extern void StartPadVibration_80036528(int pad, int kind);

extern void RemoveEmptyCocoons_800AD944(int a);

extern void RemoveInventory_800AD1E0(int a, int b, int c);

extern void AddEnemyItem_800A2898(int a);

extern void SetEnemyStatusTint_800A284C(int a);

extern void SetAreaElementLight_80039ED8(int a);

extern void AdjustUnitStatById_800127D0(int a0, int a1, int a2, int a3);

extern void StartHitNumber_800BF3DC(int unit, int kind, int amount, int pos, int f14);

extern void ShowUnitHitResult_800BE834(int unit, int pos);

extern void UpdateMinionStatusTint_800C0F1C();

typedef struct BatSettingsBits
{
    unsigned int pad0 : 21;
    unsigned int b21 : 1;
} BatSettingsBits;

extern void StartHitNumber_800BF3DC(int unit, int kind, int amount, int pos, int f14);

extern void FlashScreenWhite_800BF3AC();

// StartHitNumber_800BF3DC: the hp/mp change shown over a unit
typedef struct BatHitNum_a
{
    int kind_0; // 0 hp, 1 mp
    int amount_4;
    int frame_8;
    int alpha_C;
    unsigned short* pos_10; // int[3]; the low halves are read
    int f14;
    int unit_18;
} BatHitNum_a;

extern void StartCameraShake_80037BFC(int a);

extern void StartPadVibration_80036528(int a, int b);





typedef struct BatResult_a
{
    unsigned short kind_0;
    unsigned short arg_2;
    int flags_4;
    int status_8;         // status bits inflicted on the target
    int actorHpCost_C;
    int actorMpCost_10;
    int actorHpDamage_14; // hp/mp the actor takes from the target (counter, drain)
    int actorMpDamage_18;
    int hpDamage_1C;      // the target's hp/mp damage
    int mpDamage_20;
    short areaElement_24; // in: the area element, out: the new one
    short fixedElement_26; // the stage's fixed element (-1: magic can change the area element)
} BatResult_a; // the exe's ActionResult (common.c)

extern void ResolveBattleAction_80012BB0(UnitStatus* a, UnitStatus* b, BatCmd_a* c, BatResult_a* r);

extern void sub_800B4390(UnitStatus* a, UnitStatus* b, BatCmd_a* c, BatResult_a* r, BatChain_a* e);

extern void MarkSpeciesCaptured_800BF9F0(int a);

extern void AdjustUnitStatById_800127D0(int a0, int a1, int a2, int a3);

typedef struct BatXY_a
{
    short x;
    short y;
} BatXY_a;




// StartEnemyWindows_800BFC40: one unit's window (EnemyWindowTask_800C0074)
typedef struct BatUnitWin_a
{
    int slot_0;
    int frame_4;
    short from_8[4];
    short rect_10[4];
} BatUnitWin_a;




extern void EnemyWindowsLayoutTask_800BFDEC();

extern void EnemyWindowTask_800C0074();


extern int GetElementModelAngle_800C0904(unsigned char* p);




extern short defaultBones_80079140[]; // default bone table

extern EventNode* miscTasks_8008D60C;

// PlayTimedSeq_800C10B8: stops a seq slot after a delay
typedef struct BatSeqStop_a
{
    int slot_0;
    int timer_4;
} BatSeqStop_a;

// PlayTimedSfx_800C1190: keys an sfx voice off after a delay
typedef struct BatSfxStop_a
{
    union
    {
        int id;
        short id16; // read back as a short
    } sfx_0;
    int timer_4;
    short voice_8;
} BatSfxStop_a;

extern void HomingSparkTask_800C17EC();

typedef struct BatSpark_a
{
    int frame_0;
    int f4;
    short speed_8;
    short padA;
    int padC;
    int pos_10[3];
    int base_1C[3];
    int vel_28[3];
    short rot_34[4];
    EffectSprite* anim_3C;
    int* target_40;
    int* offset_44;
} BatSpark_a;

// buffer of the DropTrailTask_800C1450 task: walks along path_88 (one frame per 4096 of time_4) and drops
// three DropSpriteTask_800C1220 sprites every fourth frame
typedef struct BatDropSrc_a
{
    int count_0;
    int time_4;
    short step_8;
    char pad_A[0x3A];
    int pos_44[3];
    char pad_50[0x38];
    EffectSprite* path_88;
    EffectSprite* animA_8C;
    EffectSprite* animB_90;
} BatDropSrc_a;


extern int* DrawRotSprite_80044010();

extern void SpriteAnimTask_800C1B2C();

extern void BounceSparkTask_800C1DA4();

extern void RisingSparkTask_800C2170();

typedef struct BatShard_a
{
    int frame_0;
    int f4;
    short f8;
    short fA;
    int scale_C;
    int pos_10[3];
    int base_1C[3];
    int vel_28[3];
    short rot_34[4];
    void* obj_3C; // EffectModel or a model
} BatShard_a;

extern void PlaySfx_80031494(int id);


extern void ShardTask_800C273C();

extern void ImplodeShardTask_800C2CD8();

extern void ShatterTask_800C23D0();

typedef struct BatSrc_a
{
    char pad0[0x1C];
    int* pos_1C;
} BatSrc_a;

extern void VectorToAngles_8003B5D4(int* v, short* rot);

extern void SpriteTrailTask_800C2FC8();

typedef struct BatVec_a
{
    int x;
    int y;
    int z;
} BatVec_a;

typedef struct BatTrail_a
{
    int frame_0;
    int count_4;
    short speed_8;
    char padA[0x3A];
    int pos_44[3];
    BatVec_a trail_50[4];
    short rot_80[4];
    EffectSprite* anim_88;
    EffectModel* clip_8C;
} BatTrail_a;

extern void DrawFtgObjectAt_80044D0C();

extern void DrawSpriteVtxQuadsGT4_800459E4();



extern void ModelAnimTask_800C33E4();

typedef struct BatAnim_a
{
    int frame_0;
    int f4;
    short speed_8;
    char padA[0x3A];
    int pos_44[3];
    char pad50[0x32];
    short rot_82;
    char pad84[4];
    EffectModel* clip_88;
} BatAnim_a;

extern void DrawSpriteVtxQuadsG4_80045E48();

typedef struct BatGlow_a
{
    int frame_0;
    int end_4;
    char pad8[0x14];
    int* base_1C;
    int* path_20;
    char pad24[0xC];
    int f30;
    char pad34[0x10];
    char f44[0x44];
    EffectModel* model_88;
    char pad8C[8];
    FtgObject* work_94; // malloc'd copy of the model's first FtgObject
    int idx_98;
    char pad9C[4];
    int* scale_A0;
} BatGlow_a;


extern void SpawnOrb_800C3B50(int* p, int id);



extern void free3_8003FC6C(void* p);

extern void SetPointLight_800C4090(int pos, int rgb, int range, int intensity);




extern void free3_8003FC6C(void* p);

typedef struct BatOrb_a
{
    int frame_0;
    char pad4[0xA];
    short fx_E;
    char pad10[0x20];
    int alpha_30;
    int f34;
    int vel_38[3];
    int pos_44[3];
    char pad50[0x30];
    short rot_80[4];
    EffectModel* clip_88;
    char pad8C[8];
    FtgObject* model_94; // malloc'd copy of the clip's first model
} BatOrb_a;

typedef struct BatHero_a
{
    char pad0[0x5E4];
    int pos_5E4[3];
} BatHero_a;

typedef struct BatScene_a
{
    char pad0[0x24];
    BatHero_a* hero_24;
} BatScene_a;

extern BatScene_a* gameTask_8008B4A4;

extern int DistanceSquared3D_8003B80C(int* a, int* b);

extern int pointLightPos_8008D680[3];

extern short dword_8008D418[3];

extern int pointLightRange_8008D3F0;

extern int pointLightRange_8008D3F0;

extern void AiSetCommand_800C6AFC();

extern int EnemyAiDefault_800C473C();

extern int AiCastMagic_800C6BD0();

extern int TargetHasStatus_800C6EC8();

extern int AiHealWeakAlly_800C6DF8();

extern int AiUseSkill_800C6A8C();

extern int AiAttack_800C6A68();

extern int AiCastMagic_800C6BD0();

extern int rand();

extern void SetElementAffinity_800C66B4(unsigned char* buf, unsigned int b);

extern void AiSetCommandOnSelf_800C6B24(BatTask* t, int a, int b);

extern int FindUsableSkill_800C6D6C();

extern int CanCastMagic_800C6CFC();

extern EventNode* battleMenuTask_8008D468;



extern void SelectMenuWindows_800C71A0();

extern void BattleMenuTask_800C8A08();

extern int GetLastInventorySlot_800AD308(int a);

extern int CountMagicBits_8001AE54(unsigned int* h);







typedef struct BatMenuItem_a
{
    int* text;
    int* data_4;
} BatMenuItem_a;











typedef struct BatTgtQ_a
{
    short f0;
    short f2;
    short f4;
    short f6;
} BatTgtQ_a;










extern int GetMenuCursorIndex_8003DA54(void*);

extern int CheckItemUsable_80033AFC(struct_minion_ref* q);

extern int CheckMagicCastable_80033C08(struct_minion_ref* q);

extern int CheckSkillUsable_80033C98(struct_minion_ref* q);

extern int CheckItemOnTarget_80033DF4(BatTgtQ_a* q);

extern int CheckMagicUsable_80034068(BatTgtQ_a* q);

extern unsigned char GetSelectedCommand_800C78D0();


extern int GetMenuCursorIndex_8003DA54(void*);






extern int GetItemTargetFlags_8001CE8C(int a);

extern int GetUnitSkills_80031B30(int a);

extern int GetSkillTargetFlags_80031B0C(int a, int b);

extern int FindNthMagicBit_8001AEC0(unsigned int* h, int n);

extern int GetMagicTargetFlags_8001ACE4(int a);

// one window of a menu's window list (the exe's DrawMenuWindowContents_8002A710 view); a list ends with flags_0 bit 0
typedef struct BatMenuWin_a
{
    unsigned short flags_0; // bit 1: greyed out
    unsigned short type_2;  // 1: a uiTiy sprite
    int text_4;             // sprite index for type 1
    SPRT** sprts_8;
    DR_TPAGE** tpages_C;
    short x_10;
    short y_12;
    short w_14;
    short h_16;
    short mx_18;
    short my_1A;
} BatMenuWin_a;

// what DrawMenuWindows_8002A5A4 draws: the command menu's windows
typedef struct BatMenuWins_a
{
    int mode_0;                // 2: the command page, 4: a sub page
    int time_4;
    unsigned int frame_8;      // open animation frame (0..8)
    int cursor_C;              // the command menu's cursor
    BatMenuWin_a** windows_10; // NULL-terminated list of window lists
    int ot_14;
} BatMenuWins_a;














extern int IsCircleHeldP1_8003D480(void);

extern int GetMenuCursorIndex_8003DA54();

extern void DrawAbilityDescription_8002C670(void* a0, int a1, void* a2, int a3, int a4);

extern int DrawTargetSelectMenu_8002D250(void* a0, int a1, int a2, int a3);

extern void DrawMenuWindows_8002A5A4(void* a0);

extern void DrawItemList_8002C728(void* a0);

extern void DrawAbilityList_8002CE28(void* a0, int a1);

extern int GetSkillMpCost_80031A04(UnitSkills* a0, int a1);

extern void DrawMagicList_8002CAC8(void* a0, void* a1);

extern int FindNthMagicBit_8001AEC0();

extern void DrawButtonHelpBar_8002B004(int a0, int a1, int a2);

extern void DrawMenuHelpText_800C8828(int a);






extern int IsDrainAction_80013228(UnitStatus* a, UnitStatus* b, BatCmd_a* c, BatResult_a* r);






extern int menuErrorText_800C9E7C;



extern void (*menuStateFns_800C966C[])(EventEntry* t, int a);



extern void UpdateMenuCursor_8003D794();

extern void PreviewCommandResult_800C83B0();

typedef void (*BatFxFn)(BatTask* t);

extern void CmdSwapMinion_800BBBF4();
extern void CmdAction_800BBA24();
extern void CmdSummon_800BBBA8();
extern void CmdEnemyCall_800BBEFC();
extern void CmdEnemySwap_800BBFFC();
extern void CmdSimple_800BC0FC();

extern int dword_800B66C0;
extern const int dword_800B6700[4];
extern const char aAttackWithReadi_800B68AC[];
extern const char aDefendToReduceD_800B68E4[];
extern const char aSummonDivineMin_800B6914[];
extern const char aCaptureMinionIn_800B6940[];
extern const char aUseItem_800B6984[];
extern const char aFleeFromCombat_800B6998[];
extern const char aUseNormalAttack_800B69BC[];
extern const char aUseSpecialAttac_800B69E0[];
extern const char aUseMagicSpell_800B6A08[];
extern const char aChangeCurrentFi_800B6A28[];
extern const char aNoDivineMinions_800B6A58[];
extern const char aCannotSummonInt_800B6A88[];
extern const char aNotEnoughMana_800B6ABC[];
extern const char aCannotCapture_800B6ADC[];
extern const char aNoEmptyCocoons_800B6AFC[];
extern const char aCannotEscape_800B6B20[];
extern const char aNoNeedToUseItem_800B6B3C[];
extern const char aCannotSelect_800B6B64[];
extern const char aThisItemIsForDi_800B6B80[];
extern const char aDivineMinionsCa_800B6BC0[];
extern const char aCannotUseHere_800B6C08[];
extern const char aAttractsNearbyM_800B6C28[];
extern const char aTreeSporesWithA_800B6C5C[];
extern const char aCausesSurroundi_800B6CA8[];
extern const char aSweetSmellingSl_800B6D00[];
extern const char aTreeSpores_800B6D68[];
extern const char aBendsAndBecomes_800B6D80[];
extern const char aMultipurposeKey_800B6DD8[];
extern const char aKeyToTreasureCh_800B6E3C[];
extern const char aHighestGradeBes_800B6E6C[];
extern const char aSoftThreadThatG_800B6EB0[];
extern const char aSecondHighestGr_800B6F04[];
extern const char aGivesOffAnUnear_800B6F40[];
extern const char aThirdHighestGra_800B6F90[];
extern const char aGivesOffAPhosph_800B6FCC[];
extern const char aFourthHighestGr_800B701C[];
extern const char aGivesOffAModera_800B7058[];
extern const char aFifthHighestGra_800B70A0[];
extern const char aGivesOffADazzli_800B70DC[];
extern const char aSixthHighestGra_800B7114[];
extern const char aEmitsVagueInsta_800B7150[];
extern const char aSeventhHighestG_800B71AC[];
extern const char aGivesOffAShineT_800B71EC[];
extern const char aSilkThreadSpunF_800B7248[];
extern const char aInflictsAWindBa_800B7294[];
extern const char aAttackMultipleE_800B72F8[];
extern const char aInflictsAWindBa_800B733C[];
extern const char aSealWithTheMark_800B739C[];
extern const char aAttackSingleEne_800B7404[];
extern const char aInflictsAFireBa_800B7440[];
extern const char aAttackAllEnemie_800B749C[];
extern const char aInflictsAFireBa_800B74D8[];
extern const char aSealWithTheMark_800B7538[];
extern const char aAttackSingleEne_800B759C[];
extern const char aInflictsAWaterB_800B75D8[];
extern const char aAttackAllEnemie_800B7634[];
extern const char aInflictsAWaterB_800B7670[];
extern const char aSealWithTheMark_800B76D4[];
extern const char aAttackSingleEne_800B773C[];
extern const char aInflictsAnEarth_800B777C[];
extern const char aAttackAllEnemie_800B77DC[];
extern const char aInflictsAnEarth_800B7818[];
extern const char aSealWithTheMark_800B787C[];
extern const char aAttackSingleEne_800B78E4[];
extern const char aChangesAreaProp_800B7924[];
extern const char aACharmBlessedBy_800B7988[];
extern const char aChangesAreaProp_800B79E8[];
extern const char aACharmBlessedBy_800B7A4C[];
extern const char aChangesAreaProp_800B7AAC[];
extern const char aACharmBlessedBy_800B7B14[];
extern const char aChangesAreaProp_800B7B74[];
extern const char aACharmBlessedBy_800B7BDC[];
extern const char aChangeAreaPrope_800B7C3C[];
extern const char aAllAbnormalStat_800B7C6C[];
extern const char aReflectsAllUncl_800B7CD4[];
extern const char aProtectionFromA_800B7D34[];
extern const char aInstantlyCauses_800B7D5C[];
extern const char aReleasesADeathM_800B7DB8[];
extern const char aCauseDeath_800B7E00[];
extern const char aCausesBodyHarde_800B7E18[];
extern const char aReleasesAFleshT_800B7E74[];
extern const char aFleshToStone_800B7ECC[];
extern const char aCausesADeepSlum_800B7EEC[];
extern const char aReleasesASleepM_800B7F58[];
extern const char aInduceSleep_800B7FA0[];
extern const char aInstantlyCauses_800B7FBC[];
extern const char aReleasesPoisonM_800B8004[];
extern const char aSprayPoison_800B8048[];
extern const char aInnerStrengthTo_800B8064[];
extern const char aPowderMadeFromS_800B80C0[];
extern const char aStoneToFlesh_800B8124[];
extern const char aSoothesTheSpiri_800B8144[];
extern const char aPowderedFormOfD_800B8198[];
extern const char aPoisonAntidote_800B81E4[];
extern const char aAdjustsTheVisce_800B8204[];
extern const char aAlsoCalledTheIm_800B8230[];
extern const char aDriedRootOfAGre_800B8274[];
extern const char aTotalRestoratio_800B82DC[];
extern const char aRestoresAllMini_800B8300[];
extern const char aSpecialLiquorMa_800B8344[];
extern const char aRestoresAGreatD_800B83A0[];
extern const char aExcellentLiquor_800B83FC[];
extern const char aRestoresMinionH_800B845C[];
extern const char aFineLiquorMadeF_800B84C0[];
extern const char aRestoresSomeMin_800B8518[];
extern const char aLiquorMadeFromP_800B855C[];
extern const char aRestoreMinionHP_800B85A8[];
extern const char aStrengthensMini_800B85E0[];
extern const char aOilFromAPlantWi_800B861C[];
extern const char aIncreaseMinionM_800B8664[];
extern const char aStrengthensMini_800B86A0[];
extern const char aOilFromTreeWith_800B86D8[];
extern const char aIncreaseMinionM_800B8720[];
extern const char aHardensMinionSS_800B875C[];
extern const char aOilFromAPlantWi_800B878C[];
extern const char aIncreaseMinionD_800B87D8[];
extern const char aStrengthensMini_800B8818[];
extern const char aOilFromAVeryPot_800B8850[];
extern const char aIncreasesMinion_800B888C[];
extern const char aSharpensMinionS_800B88BC[];
extern const char aOilFromATreeWit_800B88F0[];
extern const char aIncreaseMinionA_800B8938[];
extern const char aStrengthensTheB_800B8974[];
extern const char aANutPackingEner_800B89D8[];
extern const char aIncreaseMaxHeal_800B8A38[];
extern const char aBitterTasteThat_800B8A60[];
extern const char aATypeOfMugwortW_800B8ACC[];
extern const char aCuresBleedingAn_800B8B30[];
extern const char aSweeterSmelling_800B8B74[];
extern const char aATypeOfMugwortB_800B8BCC[];
extern const char aGrindLeavesInto_800B8C0C[];
extern const char aIncreasesHealth_800B8C68[];
extern const char aGrowsInOpenArea_800B8CB4[];
extern const char aRestoreHealth_800B8CFC[];
extern const char aEffectivenessOf_800B8D1C[];
extern const char aIncreasesWindAt_800B8D7C[];
extern const char aEnhanceWind_800B8DD0[];
extern const char aEffectivenessOf_800B8DEC[];
extern const char aIncreasesEarthA_800B8E4C[];
extern const char aEnhanceEarth_800B8EA4[];
extern const char aEffectivenessOf_800B8EC0[];
extern const char aIncreasesWaterA_800B8F1C[];
extern const char aEnhanceWater_800B8F74[];
extern const char aEffectivenessOf_800B8F90[];
extern const char aIncreasesFireAt_800B8FEC[];
extern const char aEnhanceFire_800B9040[];
extern const char aCausesAnEnemyTo_800B905C[];
extern const char aDeath_800B90B0[];
extern const char aTurnsAnEnemyInt_800B90BC[];
extern const char aPutsAnEnemyToSl_800B90F4[];
extern const char aSleep_800B9124[];
extern const char aPoisonsAnEnemy_800B9130[];
extern const char aPoison_800B9154[];
extern const char aEndsOnceItProte_800B9164[];
extern const char aProtectsAgainst_800B91B8[];
extern const char aProtection_800B9220[];
extern const char aCuresPoisonAndT_800B9238[];
extern const char aReturnToNormal_800B9290[];
extern const char aRestoresAllHP_800B92B4[];
extern const char aRestoreAllHP_800B92D8[];
extern const char aRestoresSomeHP_800B92F8[];
extern const char aRestoreHP_800B931C[];
extern const char aCuresPoison_800B9334[];
extern const char aCurePoison_800B9350[];
extern const char aAdvancedWindAtt_800B9368[];
extern const char aWindAttackAllEn_800B9394[];
extern const char aHigherWindEleme_800B93C8[];
extern const char aExtraDamageVsEa_800B9424[];
extern const char aWindAttackOneEn_800B9454[];
extern const char aAdvancedEarthAt_800B9484[];
extern const char aEarthAttackAllE_800B94B0[];
extern const char aHigherEarthElem_800B94E8[];
extern const char aExtraDamageVsWa_800B9548[];
extern const char aEarthAttackOneE_800B9578[];
extern const char aAdvancedWaterAt_800B95AC[];
extern const char aWaterAttackAllE_800B95D8[];
extern const char aHigherWaterElem_800B9610[];
extern const char aExtraDamageVsFi_800B9670[];
extern const char aWaterAttackOneE_800B969C[];
extern const char aAdvancedFireAtt_800B96D0[];
extern const char aFireAttackAllEn_800B96FC[];
extern const char aHigherFireEleme_800B9730[];
extern const char aExtraDamageVsAi_800B978C[];
extern const char aFireAttackOneEn_800B97B8[];
extern const char aMakesItEasierTo_800B97E8[];
extern const char aSpecialAttackBr_800B9840[];
extern const char aSlightlyMoreDif_800B987C[];
extern const char aMakesItEasierTo_800B98E0[];
extern const char aSpecialAttackBr_800B9940[];
extern const char aItMoreDifficult_800B9978[];
extern const char aReducesAnEnemie_800B99D0[];
extern const char aSpecialAttackCr_800B9A1C[];
extern const char aBringsEnemiesTo_800B9A58[];
extern const char aAttacksAllEnemi_800B9AA4[];
extern const char aSpecialAttackAl_800B9AE0[];
extern const char aUsesItToRestore_800B9B1C[];
extern const char aStealsSomeManaF_800B9B64[];
extern const char aSpecialAttackAb_800B9BAC[];
extern const char aAnEnemyToRestor_800B9BE8[];
extern const char aTakesSomeOfTheD_800B9C38[];
extern const char aSpecialAttackAb_800B9C84[];
extern const char aMoreDifficultFo_800B9CBC[];
extern const char aCausesAnEnemyTo_800B9D0C[];
extern const char aSpecialAttackDe_800B9D74[];
extern const char aPhysicallyDamag_800B9DB0[];
extern const char aSpecialFleshToS_800B9E1C[];
extern const char aPhysicallyDamag_800B9E58[];
extern const char aSpecialSleepAtt_800B9EC0[];
extern const char aPhysicallyDamag_800B9EEC[];
extern const char aSpecialPoisonAt_800B9F40[];
extern const char aVeryEffectiveAg_800B9F6C[];
extern const char aSpecialWindAtta_800B9FC4[];
extern const char aVeryEffectiveAg_800B9FEC[];
extern const char aSpecialFireAtta_800BA044[];
extern const char aVeryEffectiveAg_800BA06C[];
extern const char aSpecialWaterAtt_800BA0C4[];
extern const char aVeryEffectiveAg_800BA0F0[];
extern const char aSpecialEarthAtt_800BA148[];
extern const int dword_800BA174[2];
extern int dword_800C8B2C;
extern unsigned char aiCounter_800C8B30;
extern int aiAllyCalled_800C8B34;
extern char commandHandlerIdx_800C8B38[28];
extern int commandHandlers_800C8B54[7];
extern unsigned short stage00Sprites_800C8B70[8];
extern unsigned short stage01Sprites_800C8B80[8];
extern unsigned short stage02Sprites_800C8B90[8];
extern unsigned short stage03Sprites_800C8BA0[8];
extern unsigned short stage04Sprites_800C8BB0[8];
extern unsigned short stage05Sprites_800C8BC0[10];
extern unsigned short stage06Sprites_800C8BD4[10];
extern unsigned short stage07Sprites_800C8BE8[8];
extern unsigned short stage08Sprites_800C8BF8[10];
extern unsigned short stage09Sprites_800C8C0C[8];
extern unsigned short stage0ASprites_800C8C1C[8];
extern unsigned short stage0BSprites_800C8C2C[8];
extern unsigned short stage0CSprites_800C8C3C[10];
extern unsigned short stage0DSprites_800C8C50[8];
extern unsigned short stage0ESprites_800C8C60[8];
extern unsigned short stage0FSprites_800C8C70[6];
extern unsigned short stage10Sprites_800C8C7C[6];
extern unsigned short stage11Sprites_800C8C88[8];
extern unsigned short stage12Sprites_800C8C98[2];
extern unsigned short stage13Sprites_800C8C9C[6];
extern unsigned short stage14Sprites_800C8CA8[6];
extern unsigned short stage15Sprites_800C8CB4[6];
extern unsigned short stage16Sprites_800C8CC0[6];
extern unsigned short stage17Sprites_800C8CCC[8];
extern unsigned short stage18Sprites_800C8CDC[8];
extern unsigned short stage19Sprites_800C8CEC[8];
extern unsigned short stage1ASprites_800C8CFC[8];
extern unsigned short stage1BSprites_800C8D0C[8];
extern unsigned short stage1CSprites_800C8D1C[10];
extern unsigned short stage1DSprites_800C8D30[10];
extern unsigned short stage1ESprites_800C8D44[8];
extern unsigned short stage1FSprites_800C8D54[10];
extern unsigned short stage20Sprites_800C8D68[8];
extern unsigned short stage21Sprites_800C8D78[8];
extern unsigned short stage22Sprites_800C8D88[8];
extern unsigned short stage23Sprites_800C8D98[6];
extern unsigned short stage24Sprites_800C8DA4[8];
extern unsigned short stage25Sprites_800C8DB4[8];
extern unsigned short stage26Sprites_800C8DC4[8];
extern unsigned short stage10Models_800C8DD4[12];
extern unsigned short stage12Models_800C8DEC[12];
extern unsigned short stage13Models_800C8E04[12];
extern unsigned short stage0AModels_800C8E1C[12];
extern unsigned short stage0EModels_800C8E34[12];
extern unsigned short stage21Models_800C8E4C[12];
extern unsigned short stage14Models_800C8E64[12];
extern unsigned short stage15Models_800C8E7C[12];
extern unsigned short stage16Models_800C8E94[12];
extern BatStage_a battleStages_800C8EAC[39];
extern int stageAnimPhases_800C911C[2];
extern int stageRot_800C9124[2];
extern char handlerWaitsReactions_800C912C[8];
extern unsigned char captureVibrations_800C9134[4];
extern int statusCureChances_800C9138[2];
extern BatXY_a enemyWindowLayouts_800C9140[9];
extern int enemyGaugePreview_800C9164[3];
extern int actorHighlightTime_800C9170;
extern int enemyHighlightTimes_800C9174[3];
extern short previewHpChange_800C9180;
extern short previewMpChange_800C9182;
extern int dword_800C9184;
extern Minion *summonedMinion_800C9188;
extern int summonedMinionSlot_800C918C;
extern BatSummon_a summonedActor_800C9190;
extern char defaultBoneSlots_800C91A4[56];
extern BatFxFn enemyAiHigh_800C91DC[10];
extern BatFxFn enemyAi_800C9204[53];
extern BatMenu_a commandMenu_800C92D8[1];
extern BatMenu_a skillMenu_800C92E4[1];
extern BatMenu_a magicMenu_800C92F0[1];
extern int dword_800C92FC[3];
extern BatMenu_a itemMenu_800C9308[1];
extern BatMenu_a enemyTargetMenu_800C9314[1];
extern BatMenu_a targetMenu_800C9320[1];
extern BatMenu_a allTargetsMenu_800C932C[1];
extern BatMenu_a *pageMenus_800C9338[6];
extern int helpAttack_800C9350[1];
extern int helpDefend_800C9354[1];
extern int helpSummon_800C9358[1];
extern int helpCapture_800C935C[1];
extern int helpItem_800C9360[1];
extern int helpFlee_800C9364[1];
extern int helpMinionAttack_800C9368[1];
extern int helpSpecialAttack_800C936C[1];
extern int helpMagic_800C9370[1];
extern int helpChangeFighter_800C9374[1];
extern int msgNoDivineMinions_800C9378[1];
extern int msgCannotSummon_800C937C;
extern int msgNotEnoughMana_800C9380;
extern int msgCannotCapture_800C9384[1];
extern int msgNoEmptyCocoons_800C9388[1];
extern int msgCannotEscape_800C938C[1];
extern int msgNoNeedToUseItem_800C9390;
extern int msgCannotSelect_800C9394[1];
extern int msgItemForDivineMinions_800C9398;
extern int msgDivineMinionsCannot_800C939C;
extern int msgCannotUseHere_800C93A0;
extern BatMenuItem_a levantMenuItems_800C93A4[6];
extern BatMenuItem_a minionMenuItems_800C93D4[5];
extern BatMenuWin_a winAttack_800C93FC[2];
extern BatMenuWin_a winDefend_800C9434[2];
extern BatMenuWin_a winSummon_800C946C[2];
extern BatMenuWin_a winCapture_800C94A4[2];
extern BatMenuWin_a winItem_800C94DC[2];
extern BatMenuWin_a winFlee_800C9514[2];
extern BatMenuWin_a winSpecialAttack_800C954C[2];
extern BatMenuWin_a winMagic_800C9584[2];
extern BatMenuWin_a winChangeFighter_800C95BC[2];
extern BatMenuWin_a *levantMenuWindows_800C95F4[7];
extern BatMenuWin_a *minionMenuWindows_800C9610[6];
extern BatMenuWin_a **menuWindowSets_800C9628[2];
extern BatMenuWins_a menuWindows_800C9630;
extern unsigned char commandByCursor_800C9648[12];
extern unsigned char commandNextPage_800C9654[12];
extern unsigned char commandTargetFlags_800C9660[12];
extern void (*menuStateFns_800C966C[2])(EventEntry *t, int a);
extern int pageButtonHelp_800C9674[6];
extern unsigned short pageHideFlags_800C968C[6][2];
extern int commandKinds_800C96A4[9];
extern int itemDescriptions_800C96C8[43][4];
extern int magicDescriptions_800C9978[30][4];
extern char skillDescriptions_800C9B58[256];
extern int battleLoadState_800C9C58;
extern int dword_800C9C5C[3];
extern short turnGauges_800C9C68[8];
extern int *chainEntry_800C9C78;
extern unsigned char actingUnit_800C9C7C;
extern short actorHpChange_800C9C7E;
extern short actorMpChange_800C9C80;
extern unsigned char summonedUnit_800C9C82;
extern int dword_800C9C84;
extern BatCmd_a curCommand_800C9C88;
extern unsigned char commandUnit_800C9C98;
extern unsigned char shownUnit_800C9C99;
extern int dword_800C9C9C;
extern int unitStatusInflicted_800C9CA0[7];
extern char unitHitKinds_800C9CBC[12];
extern BatCmd_a unitReactions_800C9CC8[7];
extern short unitHpDamage_800C9D38[8];
extern short unitMpDamage_800C9D48[8];
extern int unitResultFlags_800C9D58[7];
extern int helpWindowText_800C9D74;
extern short hitSfx_800C9D78;
extern int btlExecLoad_800C9D7C;
extern short deathSfx_800C9D80;
extern signed char shownAreaElement_800C9D82;
extern char fixedStageElement_800C9D83;
extern signed char areaElement_800C9D84;
extern int dword_800C9D88;
extern short stageAnimUv_800C9D8C[2];
extern int removedEnemyCount_800C9D90;
extern short actionFrame_800C9D94;
extern short actorTiming_800C9D98[4];
extern BatPair_a reactionTimings_800C9DA0[7];
extern short actorHitShift_800C9DBC;
extern short reactionHitFrames_800C9DC0[8];
extern int removedEnemies_800C9DD0[10];
extern int enemyWindowFlags_800C9DF8;
extern char enemyWindowsHighlight_800C9DFC;
extern char actorWindowHighlight_800C9DFD;
extern unsigned int enemyWindowSlide_800C9E00;
extern int dword_800C9E04;
extern EventEntry *enemyWindowTasks_800C9E08[4];
extern BatXY_a enemyWindowPos_800C9E18[3];
extern int enemyWindowMask_800C9E24;
extern BatUnitWin_a *enemyWindows_800C9E28[4];
extern int cameraFocus_800C9E38;
extern int newCameraFocus_800C9E3C;
extern unsigned char prevMenuPage_800C9E40;
extern BatMenu_a *pageCursor_800C9E44;
extern unsigned char menuState_800C9E48;
extern unsigned char menuForMinion_800C9E49;
extern unsigned char enemyCount_800C9E4A;
extern unsigned char partyMinionCount_800C9E4B;
extern int enemyMask_800C9E4C;
extern unsigned char menuPage_800C9E50;
extern unsigned char menuErrorTimer_800C9E51;
extern int menuTarget_800C9E54;
extern BatCmd_a menuCommand_800C9E58;
extern unsigned char targetFlags_800C9E68;
extern BatMenuItem_a *menuItems_800C9E6C;
