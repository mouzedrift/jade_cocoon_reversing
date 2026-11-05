// BATTLE.BIN: declarations shared by its source files
// BATTLE.BIN
#include "common.h"
#include "common_tu.h"
#include "msg_window.h"

#include "funcs.h"

#include "globals.h"

#include "actor.h"
#include "minion_menu.h"
#include "engine.h"
#include "minion_init.h"

#include "model.h"
#include "camera.h"
#include "sound.h"
#include "pad_text.h"
#include "main.h"
#include "font.h"
#include "menu_window.h"
#include "util.h"
#include "unit_query.h"
#include "event.h"
#include "movie.h"
#include "cd.h"
#include "sound_seq.h"
#include "ui_sprites.h"
#include "effect.h"
#include "unit_gauges.h"
#include "unit_stats.h"
#include "party.h"
#include "model_ftg.h"
#include "ability_menu.h"
#include "ftg_draw.h"
#include "skills.h"
#include "battle_damage.h"



extern int GetActiveSwapEnemy_800A2AB4();

extern void SetHitVariant_80018430(int a);

extern int GetEmptyCocoons_800AD8E4();










extern unsigned char enemyUnits_800C9E80[4];



extern int partyMinionMask_800C9E78;














// a battle command (curCommand_800C9C88 is the current one, unitReactions_800C9CC8 holds each unit's reaction).
// Units: 0 Levant, 1..3 his minions (one is summoned at a time), 4..6 the enemies.

// the battle menu's enemy target list. bits_2 is a member (a global array would be word aligned, it is at 0x800C9E72);
// the code indexes it through its decayed address (`*(t.bits_2 + n)`, a bits pointer), which keeps the base at +2
typedef struct BatEnemyTargets
{
    unsigned char flag_0; // cleared when the menu opens
    unsigned char pad_1;
    unsigned char bits_2[3]; // unit bit of each living enemy, in menu order
} BatEnemyTargets;
extern BatEnemyTargets enemyTargets_800C9E70;

// the enemy AI's context (ChooseEnemyCommand_800C4118)
typedef struct EnemyAi
{
    unsigned int* magicBits_0; // &self_10->magicBits_80
    UnitSkills* skills_4;      // &self_10->skills_6C
    BattleCmd* cmd_8;           // the command to fill in
    int slot_C;                // the enemy's slot (unit slot_C + 4)
    UnitStats* self_10;        // the acting encounter minion
    UnitStatus* target_14;     // its target: Levant or the summoned minion
    int targetMask_18;         // the target's unit bit
    int f1C;
} EnemyAi;


extern void AiSetCommand_800C6AFC(EnemyAi* ai, int kind, int arg);






extern int menuErrorText_800C9E7C;

extern int GetLatestHitFrame_800BE364();

extern void UpdateAction_800BE3C0();

extern int IsActionDone_800BEA94();


extern int GetUnitPos_800BC6CC();





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


extern unsigned int battleHitEnemies_800B122C;

extern int dword_800ADE88;

extern int IsSummonedMinionIdle_800C0D60();

extern int IsLevantIdle_800A89F0(void);

extern int IsEnemyIdle_800A2550();


extern int CalcElementAngle_800C09D4();

extern int sub_800B4318();


extern void BattleNextTurn_800BAE74();

extern void ClearBattleFlag_800BC850(unsigned int);


// GAME's battle chain record (game.h GameBattleChain)
typedef struct BatChainRecord
{
    int active_0; // 1 while a chain of battles runs
    int f4, f8;
    int count_C;  // the battle count
    int next_10;  // the next entry (>= 0: show its message first)
} BatChainRecord;
extern BatChainRecord encounterRecord_800ADE78;





extern void sub_800B42A8();

extern void EnemyChooseCommand_800A2618();

extern int StartBattleMenu_800C6EFC();

extern void WaitBattleMenu_800BB940();

extern void DestroyEncounterActors_800A1B78();


extern void LoadLevantAnimSet_800AC708();

extern void StopLevantAnimLoop_800A9364();

extern int IsLevantActionFinished_800A8DAC();

extern int AreAllEncounterEnemiesGone_800A1B2C();



extern void SsSepSetDecrescendo(short, short, short, long); // PSY-Q libsnd

extern void BattleEndReturnToField_800BA848();

extern void BattleEndWaitFade_800BA4F4();

// BuildMinionModelReq_800C064C: what StartModelTask_80010850 builds a minion's model from
typedef struct BatModelReq
{
    int count_0; // distinct parts
    int ids_4[3];
    int nums_10[3];
    int rank_1C; // GetRankForLevel_80019A80 of the minion's level
    int f20;
    int angle_24;
    int f28;
    int f2C;
    int f30;
    int f34;
} BatModelReq;


extern void BuildMinionModelReq_800C064C();


extern int GetUnitTurnSpeed_800BF784();

extern void TurnUnitsToward_800BC468();

// GAME's record of one enemy for the battle result (battleEnemyResults_800B1238)
typedef struct BatEnemyResult
{
    int exp_0;
    short species_4; // -1: no enemy in the slot
    short killer_6;  // the unit that defeated or captured it
    short level_8;
    short kind_A;    // the command that ended it (7: none)
} BatEnemyResult;

// StartMinionAction_800C0DDC's view of a BatActionTiming (hit/end frames): a byte-aligned 4-byte copy
typedef struct BatRawTiming
{
    unsigned char bytes_0[4];
} BatRawTiming;

extern int battleResult_800B1230;

extern BatEnemyResult battleEnemyResults_800B1238[];



















extern int eventDispatchHalt_8008B540;

extern int battleStageId_80083BD0;

// per battle stage (indexed by battleStageId_80083BD0)
typedef struct BatStage
{
    unsigned short* list_0;
    unsigned short effect_4; // effect file to load
    unsigned char model_6;
    unsigned char f7;
    short floor_8;
    short anim_A;
    unsigned short* models_C;
} BatStage;






extern void RemoveEnemy_800A2924();





extern void* memset(void* dst, int c, unsigned int n); // the exe's libc memset



extern void SwapEncounterEnemy_800A2AE8(void);


extern void StartCommandAction_80018A4C();



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

extern void SetBattleFlag_800BC838(unsigned int mask);

extern void BattleEndFadeOut_800BA624();

extern void BattleEndFled_800BA6A0();

extern void BattleEndUnload_800BA788();

extern void RemoveAliveEnemies_800BA720();


extern void BattleFinish_800BB1B0();

// the handler of curCommand_800C9C88's kind (commandHandlers_800C8B54[commandHandlerIdx_800C8B38[kind]])
extern void (*GetCommandHandler_800BC174())();

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



// the battle task's buffer: a command handler starts an action task (handle_C, a menu task or a message window
// while waiting on those) and continues with next_8 once it ends, then returns to resume_4
typedef struct BatTurnWork
{
    int pad_0;
    void (*resume_4)(); // state function to return to after the command
    void (*next_8)();
    int handle_C;
} BatTurnWork;

// when a unit's action hits and when it ends (frames of the action timeline)
typedef struct BatActionTiming
{
    short hit_0;
    short end_2;
} BatActionTiming;










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

// a battle task's EventEntry (flags_0, next_8 = cb_8); CmdSimple_800BC0FC / WaitActionTask_800BC144 also view
// their buffer through it (resume_4, next_8, handle_C: the action task's flags)
typedef struct BatTaskEntry
{
    int flags_0;
    void (*resume_4)();
    void (*next_8)();
    int* handle_C;
} BatTaskEntry;



extern unsigned int battleFlags_800B1228;

// the summoned minion's actor and where it appears (LoadSummonedMinion_800C0AEC)
typedef struct BatSummonedActor
{
    Actor* actor_0;
    int x_4;
    int y_8;
    int z_C;
    int rotY_10;
} BatSummonedActor;


// an animated window rect (ActorWindowTask_800C0254, HelpWindowTask_800C04A4)
typedef struct BatAnimWindow
{
    unsigned int frame_0;
    short from_4[4];
    short rect_C[4];
} BatAnimWindow;



















extern void InputCommand_800BB894();

extern void CmdSummonWait_800BBCC8();

extern void WaitActionTask_800BC144();


extern int StartActionTask_800BC28C(void);

extern int NeedsStatusReaction_800BC1A8();

extern struct BatActionTiming* StartUnitAction_800BE058();

extern void ResetWindowHighlights_800BFC10();

extern void StartEnemyWindows_800BFC40();

extern void StartActorWindow_800C01D8();

extern void StartHelpWindow_800C0440();

extern int FreeSummonedMinion_800C0BA0();

extern int LoadSummonedMinion_800C0AEC();

extern void ResetUnitReactions_800BB794();

extern UnitStatus* GetPartyMinionStatus_800C0F78(int);






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


extern short sinTable_80084540[];

extern int* GetEncounterLeaderPos_800A1E48(void); // GAME.BIN: an actor's pos_38

extern short* GetEncounterLeaderRot_800A1E68(void); // GAME.BIN: the same actor's rot_5C





extern void StartBattleWindows_800BFB80();

extern int sub_800B4200(BatChainRecord* chain);

extern int sub_800B41D0(BatChainRecord* chain);

extern int* sub_800B41A8(BatChainRecord* chain);


extern void WaitChainMessage_800BB100();

extern void SelectActingUnit_800BB314();

extern void ResetCurrentCommand_800BB74C();

extern void ResetTurnResults_800BB7D4();

extern void PrepareCommandInput_800BB860();

extern Vec3i* AveragePositions_800BC5EC();

extern void ApplyBattleCommand_800BEBB8();


extern void ActionWaitIdle_800BDB4C();

extern void StartLevantAction_800A8A30();

extern void StartEnemyCommandAction_800A2684();

extern void TriggerLevantAction_800A8C0C(int b);

extern void TriggerEnemyEffects_800A2760(BattleCmd* p, int b);






extern void RemoveEmptyCocoons_800AD944(int a);

extern void RemoveInventory_800AD1E0(int a, int b, int c);

extern void AddEnemyItem_800A2898(int a);

extern void SetEnemyStatusTint_800A284C(int a);



extern void StartHitNumber_800BF3DC(int unit, int kind, int amount, int pos, int lineOffset);

extern void ShowUnitHitResult_800BE834(int unit, int pos);

extern int CreateSummonedMinionActor_800C0BF0(void);

extern void UpdateMinionStatusTint_800C0F1C(void);

typedef struct BatSettingsBits
{
    unsigned int pad0 : 21;
    unsigned int b21 : 1;
} BatSettingsBits;


extern void FlashScreenWhite_800BF3AC();

// StartHitNumber_800BF3DC: the hp/mp change shown over a unit
typedef struct BatHitNumber
{
    int kind_0; // 0 hp, 1 mp
    int amount_4;
    int frame_8;
    int alpha_C;
    unsigned short* pos_10; // int[3]; the low halves are read
    int lineOffset_14; // 0, or 0xC for a unit's second number
    int unit_18;
} BatHitNumber;







extern void sub_800B4390(UnitStatus* actor, UnitStatus* target, BattleCmd* cmd, ActionResult* res, BatChainRecord* chain);

extern void MarkSpeciesCaptured_800BF9F0(int species);


typedef struct BatXY
{
    short x;
    short y;
} BatXY;




// StartEnemyWindows_800BFC40: one unit's window (EnemyWindowTask_800C0074)
typedef struct BatEnemyWindow
{
    int slot_0;
    int frame_4;
    short from_8[4];
    short rect_10[4];
} BatEnemyWindow;




extern void EnemyWindowsLayoutTask_800BFDEC();

extern void EnemyWindowTask_800C0074();


extern int GetElementModelAngle_800C0904(unsigned char* elements);




extern short defaultBones_80079140[]; // default bone table

extern EventNode* miscTasks_8008D60C;

// PlayTimedSeq_800C10B8: stops a seq slot after a delay
typedef struct BatTimedSeq
{
    int slot_0;
    int timer_4;
} BatTimedSeq;

// PlayTimedSfx_800C1190: keys an sfx voice off after a delay
typedef struct BatTimedSfx
{
    union
    {
        int id;
        short id16; // read back as a short
    } sfx_0;
    int timer_4;
    short voice_8;
} BatTimedSfx;

extern void HomingSparkTask_800C17EC();

typedef struct BatSpark
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
} BatSpark;

// buffer of the DropTrailTask_800C1450 task: walks along path_88 (one frame per 4096 of time_4) and drops
// three DropSpriteTask_800C1220 sprites every fourth frame
typedef struct BatDropTrail
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
} BatDropTrail;


extern int* DrawRotSprite_80044010();

extern void SpriteAnimTask_800C1B2C();

extern void BounceSparkTask_800C1DA4();

extern void RisingSparkTask_800C2170();

typedef struct BatShard
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
} BatShard;



extern void ShardTask_800C273C();

extern void ImplodeShardTask_800C2CD8();

extern void ShatterTask_800C23D0();

typedef struct BatShatterSource
{
    char pad0[0x1C];
    int* pos_1C;
} BatShatterSource;


extern void SpriteTrailTask_800C2FC8();

typedef struct BatSpriteTrail
{
    int frame_0;
    int count_4;
    short speed_8;
    char padA[0x3A];
    int pos_44[3];
    Vec3i trail_50[4];
    short rot_80[4];
    EffectSprite* anim_88;
    EffectModel* clip_8C;
} BatSpriteTrail;

extern void DrawFtgObjectAt_80044D0C();

extern void DrawSpriteVtxQuadsGT4_800459E4();



extern void ModelAnimTask_800C33E4();

typedef struct BatModelAnim
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
} BatModelAnim;

extern void DrawSpriteVtxQuadsG4_80045E48();

typedef struct BatGlow
{
    int frame_0;
    int end_4;
    char pad8[0x14];
    int* base_1C;
    int* path_20;
    char pad24[0xC];
    int alpha_30; // steps by 0x100 a frame: the model blend and the point light's intensity
    char pad34[0x10];
    char pos_44[0x44]; // the point light's position
    EffectModel* model_88;
    char pad8C[8];
    FtgObject* work_94; // malloc'd copy of the model's first FtgObject
    int idx_98;
    char pad9C[4];
    int* scale_A0;
} BatGlow;


extern void SpawnOrb_800C3B50(int* pos, int id);




extern void SetPointLight_800C4090(int pos, int rgb, int range, int intensity);





typedef struct BatOrb
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
} BatOrb;

typedef struct BatHero
{
    char pad0[0x5E4];
    int pos_5E4[3];
} BatHero;







extern void AiSetCommand_800C6AFC();

extern int EnemyAiDefault_800C473C();

extern int AiCastMagic_800C6BD0();

extern int TargetHasStatus_800C6EC8();

extern int AiHealWeakAlly_800C6DF8();

extern int AiUseSkill_800C6A8C();

extern int AiAttack_800C6A68();


extern int rand();

extern void SetElementAffinity_800C66B4(unsigned char* buf, unsigned int element);

extern void AiSetCommandOnSelf_800C6B24(EnemyAi* ai, int kind, int arg);

extern int FindUsableSkill_800C6D6C();

extern int CanCastMagic_800C6CFC();




extern void SelectMenuWindows_800C71A0();

extern void BattleMenuTask_800C8A08();

extern int GetLastInventorySlot_800AD308(int a);








typedef struct BatMenuItem
{
    int* text;
    int* data_4;
} BatMenuItem;



























extern unsigned char GetSelectedCommand_800C78D0();









extern int GetUnitSkills_80031B30(int a);





























extern void DrawMenuHelpText_800C8828(int text);















extern void (*menuStateFns_800C966C[])(EventEntry* task, int buffer);




extern void PreviewCommandResult_800C83B0();

typedef void (*EnemyAiFn)(EnemyAi* ai);

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
extern unsigned char aiCounter_800C8B30[4];
extern int aiAllyCalled_800C8B34;
extern unsigned char commandHandlerIdx_800C8B38[28];
extern void (*commandHandlers_800C8B54[7])();
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
extern BatStage battleStages_800C8EAC[39];
extern unsigned char stageAnimPhases_800C911C[8];
extern SVECTOR stageRot_800C9124;
extern char handlerWaitsReactions_800C912C[8];
extern unsigned char captureVibrations_800C9134[4];
typedef struct BatCureChance
{
    unsigned int mask;   // status bit
    unsigned int chance; // % per turn
} BatCureChance;
extern BatCureChance statusCureChances_800C9138[1];
extern BatXY enemyWindowLayouts_800C9140[9];
extern int enemyGaugePreview_800C9164[3];
extern int actorHighlightTime_800C9170;
extern int enemyHighlightTimes_800C9174[3];
extern short previewHpChange_800C9180;
extern short previewMpChange_800C9182;
extern int dword_800C9184;
extern Minion *summonedMinion_800C9188;
extern int summonedMinionSlot_800C918C;
extern BatSummonedActor summonedActor_800C9190;
extern char defaultBoneSlots_800C91A4[56];
extern EnemyAiFn enemyAiHigh_800C91DC[10];
extern EnemyAiFn enemyAi_800C9204[53];
extern MenuCursor commandMenu_800C92D8[1];
extern MenuCursor skillMenu_800C92E4[1];
extern MenuCursor magicMenu_800C92F0[1];
extern int dword_800C92FC[3];
extern MenuCursor itemMenu_800C9308[1];
extern MenuCursor enemyTargetMenu_800C9314[1];
extern MenuCursor targetMenu_800C9320[1];
extern MenuCursor allTargetsMenu_800C932C[1];
extern MenuCursor *pageMenus_800C9338[6];
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
extern BatMenuItem levantMenuItems_800C93A4[6];
extern BatMenuItem minionMenuItems_800C93D4[5];
extern MenuWindowItem winAttack_800C93FC[2];
extern MenuWindowItem winDefend_800C9434[2];
extern MenuWindowItem winSummon_800C946C[2];
extern MenuWindowItem winCapture_800C94A4[2];
extern MenuWindowItem winItem_800C94DC[2];
extern MenuWindowItem winFlee_800C9514[2];
extern MenuWindowItem winSpecialAttack_800C954C[2];
extern MenuWindowItem winMagic_800C9584[2];
extern MenuWindowItem winChangeFighter_800C95BC[2];
extern MenuWindowItem *levantMenuWindows_800C95F4[7];
extern MenuWindowItem *minionMenuWindows_800C9610[6];
extern MenuWindowItem **menuWindowSets_800C9628[2];
extern MenuWindowList menuWindows_800C9630;
extern unsigned char commandByCursor_800C9648[12];
extern unsigned char commandNextPage_800C9654[12];
extern unsigned char commandTargetFlags_800C9660[12];
extern void (*menuStateFns_800C966C[2])(EventEntry *task, int buffer);
extern ButtonHelpEntry* pageButtonHelp_800C9674[6];
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
extern BattleCmd curCommand_800C9C88;
extern unsigned char commandUnit_800C9C98;
extern unsigned char shownUnit_800C9C99;
extern int dword_800C9C9C;
extern int unitStatusInflicted_800C9CA0[7];
extern char unitHitKinds_800C9CBC[12];
extern BattleCmd unitReactions_800C9CC8[7];
extern short unitHpDamage_800C9D38[8];
extern short unitMpDamage_800C9D48[8];
extern int unitResultFlags_800C9D58[7];
extern const char* helpWindowText_800C9D74;
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
extern BatActionTiming reactionTimings_800C9DA0[7];
extern short actorHitShift_800C9DBC;
extern short reactionHitFrames_800C9DC0[8];
extern int removedEnemies_800C9DD0[10];
extern int enemyWindowFlags_800C9DF8;
extern char enemyWindowsHighlight_800C9DFC;
extern char actorWindowHighlight_800C9DFD;
extern unsigned int enemyWindowSlide_800C9E00;
extern int dword_800C9E04;
extern EventEntry *enemyWindowTasks_800C9E08[4];
extern BatXY enemyWindowPos_800C9E18[3];
extern int enemyWindowMask_800C9E24;
extern BatEnemyWindow *enemyWindows_800C9E28[4];
extern int cameraFocus_800C9E38;
extern int newCameraFocus_800C9E3C;
extern unsigned char prevMenuPage_800C9E40;
extern MenuCursor *pageCursor_800C9E44;
extern unsigned char menuState_800C9E48;
extern unsigned char menuForMinion_800C9E49;
extern unsigned char enemyCount_800C9E4A;
extern unsigned char partyMinionCount_800C9E4B;
extern int enemyMask_800C9E4C;
extern unsigned char menuPage_800C9E50;
extern unsigned char menuErrorTimer_800C9E51;
extern int menuTarget_800C9E54;
extern BattleCmd menuCommand_800C9E58;
extern unsigned char targetFlags_800C9E68;
extern BatMenuItem *menuItems_800C9E6C;

/* the jump table of DrawBattleStage_800BC90C (asm) and its targets, labels in the generated asm */
extern char jtgt_800BD0F4[], jtgt_800BD4F0[];
extern void* const dword_800B6710[25];

/* battle.c: the battle end task (BattleEnd_800BA254 and its next steps) */
typedef struct BatEndWork
{
    int fileReq_0;     // file request of the overlay reloaded after the battle
    int timer_4;
    int* battleTask_8; // the battle task's EventEntry (its flags)
    int c_C;
} BatEndWork;
// GAME's battle selection (GetBattleSelection_800A1E3C)
typedef struct BatSelection
{
    char pad_0[0x18];
    int c_18;
} BatSelection;
void BattleEndDefeat_800BA444(BatTaskEntry* task);
void BattleEndWaitLevant_800BA52C(BatTaskEntry* task);
void BattleEndVictory_800BA564(BatTaskEntry* task, BatEndWork* work);
int TestBattleFlag_800BC820(unsigned int mask);
void StopBattleWindows_800BFBB8();

/* GAME-side (game.h; GAME stays loaded under BATTLE) */
extern BatSelection* GetBattleSelection_800A1E3C();
extern void ExitLevantBattleMode_800A8984(int victoryPose);

/* exe-side, to move to engine.h */
/* exe-side, to move to sound_seq.h */

/* battle_5.c: the actor window's box (DrawWindow_80042460's style) */

/* battle_6.c: the enemy AI (ChooseEnemyCommand_800C4118 calls these before their definitions) */
int EnemyAiBD_800C4A40(EnemyAi* ai);
void BossAi03_800C5BC0(EnemyAi* ai);
void BossAi04_800C59A0(EnemyAi* ai);
void BossAi0A_800C58BC(EnemyAi* ai);
void BossAi0B_800C5EB8(EnemyAi* ai);
void BossAi0C_800C6038(EnemyAi* ai);
void BossAi0D_800C5D04(EnemyAi* ai);
void BossAi0E_800C61FC(EnemyAi* ai);
void BossAi0F_800C66F4(EnemyAi* ai);
void BossAi10_800C6824(EnemyAi* ai);
void BossAi11_800C6928(EnemyAi* ai);
void EnemyAiFirstSkill_800C6A40(EnemyAi* ai);
void BossAi02_800C5A7C(EnemyAi* ai);
void EnemyAiDefend_800C58AC(EnemyAi* ai);

/* exe-side, to move to unit_gauges.h */
extern void DrawStatusIcons_8002F480(UnitStatus* unit, short* pos, int ot, int reverse);
/* exe-side, to move to event.h */
/* exe-side, to move to font.h */
/* exe-side, to move to util.h */
/* exe-side, to move to menu_window.h */
/* exe-side, to move to globals.h / data_decls.h */
/* exe-side: main.h declares it (main.h itself conflicts with battle.h types) */
extern unsigned short uiColor_8008B590;

/* battle_6.c: the enemy AI scripts and battle menu steps its tables (enemyAi_800C9204, menuStateFns_800C966C) point to */
int EnemyAi00_800C4D38(EnemyAi* ai);
int EnemyAi02_800C54A4(EnemyAi* ai);
int EnemyAi03_800C4FE0(EnemyAi* ai);
int EnemyAi04_800C57D8(EnemyAi* ai);
int EnemyAi05_800C56B8(EnemyAi* ai);
int EnemyAi06_800C4BE4(EnemyAi* ai);
int EnemyAi07_800C4E34(EnemyAi* ai);
int EnemyAi08_800C580C(EnemyAi* ai);
int EnemyAi09_800C4DB8(EnemyAi* ai);
int EnemyAi0A_800C4EA8(EnemyAi* ai);
int EnemyAi0B_800C5510(EnemyAi* ai);
int EnemyAi0C_800C4CBC(EnemyAi* ai);
int EnemyAi0D_800C5424(EnemyAi* ai);
int EnemyAi0E_800C5034(EnemyAi* ai);
int EnemyAi0F_800C4B34(EnemyAi* ai);
int EnemyAi10_800C5304(EnemyAi* ai);
int EnemyAi12_800C4C74(EnemyAi* ai);
int EnemyAi13_800C507C(EnemyAi* ai);
int EnemyAi14_800C5594(EnemyAi* ai);
int EnemyAi15_800C5290(EnemyAi* ai);
int EnemyAi16_800C5608(EnemyAi* ai);
int EnemyAi17_800C50B0(EnemyAi* ai);
int EnemyAi18_800C5670(EnemyAi* ai);
int EnemyAi19_800C576C(EnemyAi* ai);
int EnemyAi1A_800C4FA8(EnemyAi* ai);
int EnemyAi1B_800C51D8(EnemyAi* ai);
int EnemyAi1C_800C53B0(EnemyAi* ai);
int EnemyAi1D_800C5700(EnemyAi* ai);
int EnemyAi1E_800C5874(EnemyAi* ai);
int EnemyAi1F_800C5840(EnemyAi* ai);
void EnemyAiC9_800C4328(EnemyAi* ai);
void EnemyAiCA_800C43D8(EnemyAi* ai);
void EnemyAiCB_800C4424(EnemyAi* ai);
void EnemyAiCC_800C4470(int ai);
void EnemyAiCD_800C4494(EnemyAi* ai);
void EnemyAiCE_800C44FC(EnemyAi* ai);
void EnemyAiCF_800C4548(EnemyAi* ai);
void EnemyAiD0_800C45A8(EnemyAi* ai);
void EnemyAiD1_800C46FC();
void EnemyAiD2_800C471C();
void MenuInput_800C8768();
void MenuShowError_800C88E4();

/* battle: functions called before their definition (or from another of its files) */
int AdvancePetrification_800BFA34(int status);
int AiDefend_800C6C44(EnemyAi* ai);
int AiFlee_800C6C58(EnemyAi* ai);
int AreStageEffectsLoaded_800BC8E8();
int CanCapture_800C7334();
int CanFlee_800C72B8();
void DisableMenuCommands_800C71C8();
int GetAreaElement_800BC868();
int GetStatusCommand_800BFA4C(unsigned int status, unsigned int prevStatus);
int* GetSummonedMinionPos_800C0F9C();
void InitEnemyRecords_800BABC4();
void InitMenuCursors_800C7088();
void InitTurnGauges_800BF648(short* gauges, unsigned int mode);
int IsBossSpecies_800BF9B4(int species);
int IsTargetWeakToMagic_800C6EE4(EnemyAi* ai);
int IsUncapturableSpecies_800BF980(int species);
void LoadStageEffects_800BC878();
void RecoverPartyAfterBattle_800BA97C();
BatRawTiming* StartMinionAction_800C0DDC(BatRawTiming* out, BattleCmd* cmd, int isReaction);
void TickUnitStatus_800BF7C4(UnitStatus* unitStatus, short* hpChange, short* mpChange);
int TriggerMinionAction_800C0E84(BattleCmd* cmd, int isReaction); // isReaction unused (TriggerUnitAction_800BE14C passes it to all three Trigger*Action)

/* GAME-side (game.h) */
extern int CanFleeFromEnemy_800A28FC(int idx);
/* exe-side, to move to model.h */
/* exe-side, to move to engine.h */
/* exe-side, to move to camera.h */
/* exe-side, to move to sound.h */
/* exe-side, to move to cd.h */
/* exe-side, to move to sound_seq.h */
/* PSY-Q libsnd */
extern void SsUtAllKeyOff(short mode);
