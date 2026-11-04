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


extern int sub_800A2AB4();

extern void SetHitVariant_80018430(int a);

extern int sub_800AD8E4();

extern void InterpolateWindowRect_8004196C(void* a0, void* a1, int a2, int a3, int a4);

extern void AddDrawAreaPrim_8003326C();

extern void AddClipDrawAreaPrim_80033308();

extern unsigned short padPressed_8009194C;

extern int MeasureTextWidth_8003E4C8();




extern unsigned char dword_800C9E72[];

extern unsigned char dword_800C9E80[];



extern int dword_800C9E78;




typedef struct BatMenu_a
{
    short f0;
    short f2;
    unsigned short count_4;
    unsigned short flags_6;
    short cursor_8;
    short scroll_A;
} BatMenu_a; // same layout as the exe's MenuCursor










// a battle command (dword_800C9C88 is the current one, dword_800C9CC8 holds each unit's reaction)
typedef struct BatCmd_a
{
    int kind_0; // 0x14: none
    int arg_4;
    int mask_8; // acting unit bits
    int targets_C; // target unit bits
} BatCmd_a;

typedef struct BatTask
{
    unsigned int* f0;  // &f10->magicBits_80
    UnitSkills* f4;    // &f10->skills_6C
    BatCmd_a* f8;
    int fC;
    UnitStats* f10;    // the acting encounter minion
    UnitStatus* f14;   // its target: Levant or one of his minions
    int f18;
    int f1C;
} BatTask;


extern void sub_800C6AFC(BatTask* t, int a, int b);






extern int dword_800C9E7C;

extern int sub_800BE364();

extern void sub_800BE3C0();

extern int sub_800BEA94();


extern int sub_800BC6CC();

extern void FadeOutSeqSlot_800313C8(int);

extern EventNode* dword_8008D624;



extern char dword_800C9D56;


extern int sub_800A5354();

extern int sub_800BAAD8();

extern void sub_800A1F80();

extern void sub_800A8D0C();

extern void sub_800A096C();

extern void sub_800BAC4C();


extern int sub_800A2C28();

extern int sub_800BEB50();

extern int sub_800BEB68();

extern int sub_800BF47C();

extern int sub_800BC784();

typedef struct BatV12_a
{
    int x;
    int y;
    int z;
} BatV12_a;

extern unsigned int dword_800B122C;

extern int dword_800ADE88;

extern int sub_800C0D60();

extern int sub_800A89F0();

extern int sub_800A2550();

extern int IsEffectTaskIdle_800148D4();

extern int sub_800C09D4();

extern int sub_800B4318();

extern void Midpoint3D_8003B95C();

extern void sub_800BAE74();

extern void sub_800BC850(unsigned int);

extern char dword_80091D40[];

// GAME's battle chain record (game.h GameRec_1): f0 1 while a chain of battles runs, fc the battle count, f10 the next entry
typedef struct BatChain_a
{
    int f0, f4, f8, fc, f10;
} BatChain_a;
extern BatChain_a dword_800ADE78;

extern int dword_80091C74;

extern int dword_8007DC74;


extern short dword_80091CE0[];

extern void sub_800B42A8();

extern void sub_800A2618();

extern int StartBattleMenu_800C6EFC();

extern void sub_800BB940();

extern void sub_800A1B78();

extern void FreeActiveOverlay_8002C014();

extern void sub_800AC708();

extern void sub_800A9364();

extern int sub_800A8DAC();

extern int sub_800A1B2C();



extern void SsSepSetDecrescendo();

extern void sub_800BA848();

extern void sub_800BA4F4();

// sub_800C064C: what StartModelTask_80010850 builds a minion's model from
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


extern void sub_800C064C();

extern void StartModelTask_80010850();

extern int sub_800BF784();

extern void sub_800BC468();

typedef struct BatEnt_a
{
    int a;
    short b;
    short c;
    short d;
    short e;
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

extern void sub_800A2924();





extern void memset();


extern void SetFadeMode_8001C19C();

extern void sub_800A2AE8();

extern void PlaySeqSlot_80031160();

extern void StartCommandAction_80018A4C();

extern int LoadOverlay_80020BF8();

extern void StopSceneDarken_8001AAF4();

extern void sub_800A8D48();

extern void sub_800A25D8();

extern int sub_800A2BE4();

extern int sub_800BF6BC();

extern int sub_800BC378();

extern int sub_800BDE04();

extern int sub_800BC570();

extern int sub_800BC7DC();

extern void sub_800BC4D4();

extern void sub_800BF770();

extern void sub_800BC838();

extern void sub_800BA624();

extern void sub_800BA6A0();

extern void sub_800BA788();

extern void sub_800BA720();

extern void sub_800BAE74();

extern void sub_800BB1B0();

extern void sub_800BB168();

extern void sub_800BB380();

extern void sub_800BBC84();

extern void sub_800BDC3C();

extern void sub_800BF4D0();

extern void sub_800C0254();

extern void sub_800BBDB4();

extern void sub_800C0DB0();

extern void sub_800BC324();

extern void sub_800BBE7C();



typedef struct BatObj_a
{
    int f0;
    int f4;
    void (*next_8)();
    int fc;
} BatObj_a;

typedef struct BatPair_a
{
    short a;
    short b;
} BatPair_a;


extern EventNode* dword_8008B568;

extern EventNode* dword_8008B564;

extern EventNode* dword_8008D4B0;

extern EventNode* dword_8008D63C;

extern EventNode* hitNumberTasks_8008D778;



extern short effectOutcomeFlag_8008D780;

extern void sub_800BBA70();

extern void sub_800BBE00();

extern void sub_800BC05C();

extern void sub_800BBF64();

extern void sub_800BDA28();

extern void sub_800BDBB0();

extern void sub_800C04A4();

extern int sub_800BDD3C();

extern void sub_800BF2E8();

extern void sub_800BDEBC();

extern void sub_800BDF74();

extern void sub_800BDFAC();

extern void sub_800BE2C8();

extern int sub_800C0A9C();

extern int sub_800C0D50();

typedef struct BatTask_a
{
    int f0;
    int f4;
    void (*next_8)();
    int* fc;
} BatTask_a;



extern unsigned int dword_800B1228;

typedef struct BatCtx_a
{
    Actor* obj;
    int f4;
    int f8;
    int fc;
    int f10;
} BatCtx_a;


// an animated window rect (sub_800C0254, sub_800C04A4)
typedef struct BatWin_b
{
    unsigned int frame_0;
    short from_4[4];
    short rect_C[4];
} BatWin_b;




extern short dword_800C9D9A;












extern int IsSceneFadeDone_8001AB94(void*);

extern int sub_800A89F0();

extern void sub_800BA624();

extern void sub_800BB894();

extern void sub_800BBCC8();

extern void sub_800BC144();

extern void sub_800BC850(unsigned int);

extern int sub_800BC28C();

extern int sub_800BC1A8();

extern struct BatPair_a* sub_800BE058();

extern void sub_800BFC10();

extern void sub_800BFC40();

extern void sub_800C01D8();

extern void sub_800C0440();

extern int sub_800C0BA0();

extern int sub_800C0AEC();

extern void sub_800BB794();

extern UnitStatus* sub_800C0F78(int);

extern void StartScreenFlash_8001C02C(void*);

extern void SetActorTurnTarget_8001DB00(Actor*, int, int);

extern void GetActorHitFrame_80018E5C(Actor*, int);

extern void SetActorStatusTint_80018EBC(Actor*, UnitStatus*);


extern int sub_800C0D88();

extern int sub_800A8BE4();

extern int sub_800A2594();

extern int sub_800AC768();

extern void sub_800A1F0C();

extern void sub_800A9384(int a);

extern void sub_800A8DCC();

extern void sub_800A89C8();

extern void sub_800A1E1C();

extern void sub_800A094C();

extern void sub_800A5FAC();

extern void sub_800A14E0();

extern void sub_800A15FC();

extern int forceMapReload_80091C9C;

extern short sinTable_80084540[];

extern int* sub_800A1E48(void); // GAME.BIN: an actor's pos_38

extern short* sub_800A1E68(void); // GAME.BIN: the same actor's rot_5C

extern int LoadSeqSlotSound_800303E8();

extern int IsSoundTaskReady_80030688();

extern void StartBattleCamera_80037748();

extern void LoadUiTiy_8002BF74();

extern void sub_800BFB80();

extern int sub_800B4200(BatChain_a* p);

extern int sub_800B41D0(BatChain_a* p);

extern int* sub_800B41A8(BatChain_a* p);


extern void sub_800BB100();

extern void sub_800BB314();

extern void sub_800BB74C();

extern void sub_800BB7D4();

extern void sub_800BB860();

extern BatV12_a* sub_800BC5EC();

extern void ApplyBattleCommand_800BEBB8();

extern void MoveBattleCameraForAction_80037828(int a, int b, int c);

extern void sub_800BDB4C();

extern void sub_800A8A30();

extern void sub_800A2684();

extern void sub_800A8C0C(int b);

extern void sub_800A2760(BatCmd_a* p, int b);

extern void StartBattleCameraSpline_800377B4(int a, int b, int c);

extern void StartCameraShake_80037BFC(int a);

extern void PlaySfx_80031494(int id);

extern void StartPadVibration_80036528(int pad, int kind);

extern void sub_800AD944(int a);

extern void sub_800AD1E0(int a, int b, int c);

extern void sub_800A2898(int a);

extern void sub_800A284C(int a);

extern void sub_80039ED8(int a);

extern void AdjustUnitStatById_800127D0(int a0, int a1, int a2, int a3);

extern void sub_800BF3DC(int a, int b, int c, int d, int e);

extern void sub_800BE834(int a, int b);

extern void sub_800C0F1C();

typedef struct BatSettingsBits
{
    unsigned int pad0 : 21;
    unsigned int b21 : 1;
} BatSettingsBits;

extern void sub_800BF3DC(int a, int b, int c, int d, int e);

extern void sub_800BF3AC();

// sub_800BF3DC: the hp/mp change shown over a unit
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
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
    short f24;
    short f26;
} BatResult_a;

extern void ResolveBattleAction_80012BB0(UnitStatus* a, UnitStatus* b, BatCmd_a* c, BatResult_a* r);

extern void sub_800B4390(UnitStatus* a, UnitStatus* b, BatCmd_a* c, BatResult_a* r, BatChain_a* e);

extern void sub_800BF9F0(int a);

extern void AdjustUnitStatById_800127D0(int a0, int a1, int a2, int a3);

typedef struct BatXY_a
{
    short x;
    short y;
} BatXY_a;




// sub_800BFC40: one unit's window (sub_800C0074)
typedef struct BatUnitWin_a
{
    int slot_0;
    int frame_4;
    short from_8[4];
    short rect_10[4];
} BatUnitWin_a;




extern void sub_800BFDEC();

extern void sub_800C0074();


extern int sub_800C0904(unsigned char* p);




extern short defaultBones_80079140[]; // default bone table

extern EventNode* dword_8008D60C;

// sub_800C10B8: stops a seq slot after a delay
typedef struct BatSeqStop_a
{
    int slot_0;
    int timer_4;
} BatSeqStop_a;

// sub_800C1190: keys an sfx voice off after a delay
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

extern void sub_800C17EC();

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

// buffer of the sub_800C1450 task: walks along path_88 (one frame per 4096 of time_4) and drops
// three sub_800C1220 sprites every fourth frame
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

extern void sub_800C1B2C();

extern void sub_800C1DA4();

extern void sub_800C2170();

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


extern void sub_800C273C();

extern void sub_800C2CD8();

extern void sub_800C23D0();

typedef struct BatSrc_a
{
    char pad0[0x1C];
    int* pos_1C;
} BatSrc_a;

extern void VectorToAngles_8003B5D4(int* v, short* rot);

extern void sub_800C2FC8();

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



extern void sub_800C33E4();

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


extern void sub_800C3B50(int* p, int id);



extern void free3_8003FC6C(void* p);

extern void sub_800C4090(int a0, int a1, int c, int a3);




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

extern void sub_800C6AFC();

extern int sub_800C473C();

extern int sub_800C6BD0();

extern int sub_800C6EC8();

extern int sub_800C6DF8();

extern int sub_800C6A8C();

extern int sub_800C6A68();

extern int sub_800C6BD0();

extern int rand();

extern void sub_800C66B4(unsigned char* buf, unsigned int b);

extern void sub_800C6B24(BatTask* t, int a, int b);

extern int sub_800C6D6C();

extern int sub_800C6CFC();

extern EventNode* battleMenuTask_8008D468;


extern unsigned char dword_800C9E70;

extern void sub_800C71A0();

extern void BattleMenuTask_800C8A08();

extern int sub_800AD308(int a);

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



extern int dword_800C9E5C;







extern int GetMenuCursorIndex_8003DA54(void*);

extern int CheckItemUsable_80033AFC(struct_minion_ref* q);

extern int CheckMagicCastable_80033C08(struct_minion_ref* q);

extern int CheckSkillUsable_80033C98(struct_minion_ref* q);

extern int CheckItemOnTarget_80033DF4(BatTgtQ_a* q);

extern int CheckMagicUsable_80034068(BatTgtQ_a* q);

extern unsigned char sub_800C78D0();


extern int GetMenuCursorIndex_8003DA54(void*);





extern unsigned int dword_800C9E64;

extern int GetItemTargetFlags_8001CE8C(int a);

extern int GetUnitSkills_80031B30(int a);

extern int sub_80031B0C(int a, int b);

extern int FindNthMagicBit_8001AEC0(unsigned int* h, int n);

extern int GetMagicTargetFlags_8001ACE4(int a);

struct BatState
{
    int f0;
    int f4;
    int f8;
    int fC;
};


extern short dword_800C92E0;









extern int dword_800C9E5C;



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

extern void sub_800C8828(int a);






extern int sub_80013228(UnitStatus* a, UnitStatus* b, BatCmd_a* c, BatResult_a* r);

extern unsigned char dword_800C9E72[];





extern int dword_800C9E7C;

extern unsigned int dword_800C9E64;


extern void (*dword_800C966C[])(EventEntry* t, int a);



extern void UpdateMenuCursor_8003D794();

extern void sub_800C83B0();

typedef void (*BatFxFn)(BatTask* t);

extern void sub_800BBBF4();
extern void sub_800BBA24();
extern void sub_800BBBA8();
extern void sub_800BBEFC();
extern void sub_800BBFFC();
extern void sub_800BC0FC();

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
extern unsigned char dword_800C8B30;
extern int dword_800C8B34;
extern char dword_800C8B38[28];
extern int dword_800C8B54[7];
extern unsigned short dword_800C8B70[8];
extern unsigned short dword_800C8B80[8];
extern unsigned short dword_800C8B90[8];
extern unsigned short dword_800C8BA0[8];
extern unsigned short dword_800C8BB0[8];
extern unsigned short dword_800C8BC0[10];
extern unsigned short dword_800C8BD4[10];
extern unsigned short dword_800C8BE8[8];
extern unsigned short dword_800C8BF8[10];
extern unsigned short dword_800C8C0C[8];
extern unsigned short dword_800C8C1C[8];
extern unsigned short dword_800C8C2C[8];
extern unsigned short dword_800C8C3C[10];
extern unsigned short dword_800C8C50[8];
extern unsigned short dword_800C8C60[8];
extern unsigned short dword_800C8C70[6];
extern unsigned short dword_800C8C7C[6];
extern unsigned short dword_800C8C88[8];
extern unsigned short dword_800C8C98[2];
extern unsigned short dword_800C8C9C[6];
extern unsigned short dword_800C8CA8[6];
extern unsigned short dword_800C8CB4[6];
extern unsigned short dword_800C8CC0[6];
extern unsigned short dword_800C8CCC[8];
extern unsigned short dword_800C8CDC[8];
extern unsigned short dword_800C8CEC[8];
extern unsigned short dword_800C8CFC[8];
extern unsigned short dword_800C8D0C[8];
extern unsigned short dword_800C8D1C[10];
extern unsigned short dword_800C8D30[10];
extern unsigned short dword_800C8D44[8];
extern unsigned short dword_800C8D54[10];
extern unsigned short dword_800C8D68[8];
extern unsigned short dword_800C8D78[8];
extern unsigned short dword_800C8D88[8];
extern unsigned short dword_800C8D98[6];
extern unsigned short dword_800C8DA4[8];
extern unsigned short dword_800C8DB4[8];
extern unsigned short dword_800C8DC4[8];
extern unsigned short dword_800C8DD4[12];
extern unsigned short dword_800C8DEC[12];
extern unsigned short dword_800C8E04[12];
extern unsigned short dword_800C8E1C[12];
extern unsigned short dword_800C8E34[12];
extern unsigned short dword_800C8E4C[12];
extern unsigned short dword_800C8E64[12];
extern unsigned short dword_800C8E7C[12];
extern unsigned short dword_800C8E94[12];
extern BatStage_a dword_800C8EAC[39];
extern int dword_800C911C[2];
extern int dword_800C9124[2];
extern char dword_800C912C[8];
extern unsigned char dword_800C9134[4];
extern int dword_800C9138[2];
extern BatXY_a dword_800C9140[9];
extern int dword_800C9164[3];
extern int dword_800C9170;
extern int dword_800C9174[3];
extern short dword_800C9180;
extern short dword_800C9182;
extern int dword_800C9184;
extern Minion *dword_800C9188;
extern int dword_800C918C;
extern BatCtx_a dword_800C9190;
extern char dword_800C91A4[56];
extern BatFxFn dword_800C91DC[10];
extern BatFxFn dword_800C9204[53];
extern BatMenu_a dword_800C92D8[1];
extern BatMenu_a dword_800C92E4[1];
extern BatMenu_a dword_800C92F0[1];
extern int dword_800C92FC[3];
extern BatMenu_a dword_800C9308[1];
extern BatMenu_a dword_800C9314[1];
extern BatMenu_a dword_800C9320[1];
extern BatMenu_a dword_800C932C[1];
extern BatMenu_a *dword_800C9338[6];
extern int dword_800C9350[1];
extern int dword_800C9354[1];
extern const char *dword_800C9358[1];
extern char dword_800C935C[4];
extern const char *dword_800C9360[1];
extern const char *dword_800C9364[1];
extern int dword_800C9368[1];
extern int dword_800C936C[1];
extern int dword_800C9370[1];
extern int dword_800C9374[1];
extern char dword_800C9378[4];
extern int dword_800C937C;
extern int dword_800C9380;
extern char dword_800C9384[4];
extern char dword_800C9388[4];
extern char dword_800C938C[4];
extern int dword_800C9390;
extern const char *dword_800C9394[1];
extern int dword_800C9398;
extern int dword_800C939C;
extern int dword_800C93A0;
extern BatMenuItem_a dword_800C93A4[2];
extern void *dword_800C93B4[1];
extern char *dword_800C93B8[2];
extern void *dword_800C93C0[4];
extern int dword_800C93D0;
extern BatMenuItem_a dword_800C93D4[5];
extern int dword_800C93FC[14];
extern int dword_800C9434[14];
extern unsigned short dword_800C946C;
extern short word_800C946E;
extern short word_800C9470;
extern short word_800C9472;
extern short word_800C9474;
extern short word_800C9476;
extern short word_800C9478;
extern short word_800C947A;
extern short word_800C947C;
extern short word_800C947E;
extern short word_800C9480;
extern short word_800C9482;
extern short word_800C9484;
extern short word_800C9486;
extern short word_800C9488;
extern short word_800C948A;
extern short word_800C948C;
extern short word_800C948E;
extern short word_800C9490;
extern short word_800C9492;
extern short word_800C9494;
extern short word_800C9496;
extern short word_800C9498;
extern short word_800C949A;
extern short word_800C949C;
extern short word_800C949E;
extern short word_800C94A0;
extern short word_800C94A2;
extern unsigned short dword_800C94A4;
extern short word_800C94A6;
extern short word_800C94A8;
extern short word_800C94AA;
extern short word_800C94AC;
extern short word_800C94AE;
extern short word_800C94B0;
extern short word_800C94B2;
extern short word_800C94B4;
extern short word_800C94B6;
extern short word_800C94B8;
extern short word_800C94BA;
extern short word_800C94BC;
extern short word_800C94BE;
extern short word_800C94C0;
extern short word_800C94C2;
extern short word_800C94C4;
extern short word_800C94C6;
extern short word_800C94C8;
extern short word_800C94CA;
extern short word_800C94CC;
extern short word_800C94CE;
extern short word_800C94D0;
extern short word_800C94D2;
extern short word_800C94D4;
extern short word_800C94D6;
extern short word_800C94D8;
extern short word_800C94DA;
extern int dword_800C94DC[14];
extern unsigned short dword_800C9514;
extern short word_800C9516;
extern short word_800C9518;
extern short word_800C951A;
extern short word_800C951C;
extern short word_800C951E;
extern short word_800C9520;
extern short word_800C9522;
extern short word_800C9524;
extern short word_800C9526;
extern short word_800C9528;
extern short word_800C952A;
extern short word_800C952C;
extern short word_800C952E;
extern short word_800C9530;
extern short word_800C9532;
extern short word_800C9534;
extern short word_800C9536;
extern short word_800C9538;
extern short word_800C953A;
extern short word_800C953C;
extern short word_800C953E;
extern short word_800C9540;
extern short word_800C9542;
extern short word_800C9544;
extern short word_800C9546;
extern short word_800C9548;
extern short word_800C954A;
extern int dword_800C954C[14];
extern int dword_800C9584[14];
extern int dword_800C95BC[14];
extern void *dword_800C95F4[7];
extern void *dword_800C9610[6];
extern int dword_800C9628[2];
extern struct BatState dword_800C9630;
extern int dword_800C9640;
extern int dword_800C9644;
extern unsigned char dword_800C9648[12];
extern unsigned char dword_800C9654[12];
extern unsigned char dword_800C9660[12];
extern void (*dword_800C966C[2])(EventEntry *t, int a);
extern int dword_800C9674[6];
extern unsigned short dword_800C968C[6][2];
extern int dword_800C96A4[9];
extern int dword_800C96C8[43][4];
extern int dword_800C9978[30][4];
extern char dword_800C9B58[256];
extern int dword_800C9C58;
extern int dword_800C9C5C[3];
extern short dword_800C9C68[8];
extern int *dword_800C9C78;
extern unsigned char dword_800C9C7C;
extern short dword_800C9C7E;
extern short dword_800C9C80;
extern unsigned char dword_800C9C82;
extern int dword_800C9C84;
extern BatCmd_a dword_800C9C88;
extern unsigned char dword_800C9C98;
extern unsigned char dword_800C9C99;
extern int dword_800C9C9C;
extern int dword_800C9CA0[7];
extern char dword_800C9CBC[12];
extern BatCmd_a dword_800C9CC8[7];
extern short dword_800C9D38[8];
extern short dword_800C9D48[8];
extern int dword_800C9D58[7];
extern int dword_800C9D74;
extern short dword_800C9D78;
extern int dword_800C9D7C;
extern short dword_800C9D80;
extern signed char dword_800C9D82;
extern char dword_800C9D83;
extern signed char dword_800C9D84;
extern int dword_800C9D88;
extern short dword_800C9D8C[2];
extern int dword_800C9D90;
extern short dword_800C9D94;
extern short dword_800C9D98[4];
extern BatPair_a dword_800C9DA0[7];
extern short dword_800C9DBC;
extern short dword_800C9DC0[8];
extern int dword_800C9DD0[10];
extern int dword_800C9DF8;
extern char dword_800C9DFC;
extern char dword_800C9DFD;
extern unsigned int dword_800C9E00;
extern int dword_800C9E04;
extern EventEntry *dword_800C9E08[4];
extern BatXY_a dword_800C9E18[3];
extern int dword_800C9E24;
extern BatUnitWin_a *dword_800C9E28[4];
extern int dword_800C9E38;
extern int dword_800C9E3C;
extern unsigned char dword_800C9E40;
extern BatMenu_a *dword_800C9E44;
extern unsigned char dword_800C9E48;
extern unsigned char dword_800C9E49;
extern unsigned char dword_800C9E4A;
extern unsigned char dword_800C9E4B;
extern int dword_800C9E4C;
extern unsigned char dword_800C9E50;
extern unsigned char dword_800C9E51;
extern int dword_800C9E54;
extern BatCmd_a dword_800C9E58;
extern unsigned char dword_800C9E68;
extern BatMenuItem_a *dword_800C9E6C;
