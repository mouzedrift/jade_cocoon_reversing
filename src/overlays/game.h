// GAME.BIN: declarations shared by its source files
// GAME.BIN
#include "common.h"

#include "funcs.h"

#include "globals.h"

#include "actor.h"

#include "model.h"
#include "effect_obj.h"
#include "camera.h"
#include "engine.h"

extern void sub_800A6D30(int a);


// AI of an enemy actor (CreateEnemyAiEvent_800A2D90; the name_800ADEB8 state handlers)
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
    int f28; // turn direction (FindActorInFront_8001DECC)
    int f2c; // turn amount
} GameAi;

typedef struct GameRec_1
{
    int f0, f4, f8, fc, f10;
} GameRec_1;

typedef struct GameV3_1
{
    int a, b, c;
} GameV3_1;

// an enemy group of the map (EVENTFNC's EvEnemyEventfnc, copied into GameSlot_1.data_8 by sub_800A17F4)
typedef struct GameEnemyMember
{
    int species_0; // GetSpeciesModelDesc_80019C70 / InitMinionData_8001900C
    int f4;
} GameEnemyMember;

typedef struct GameEnemy
{
    int kind_0; // 0: actors already exist, 1: hide them when reused
    int maxCount_4;
    int f8;
    int fC;
    int f10;
    int f14;
    int useMinion_18; // 1: the first member is minion_1C
    UnitStats minion_1C;
    Actor* actors_A4[3];
    GameEnemyMember members_B0[3];
    int* anims_C8[3]; // [0]: when it is the group being fought, [1]: otherwise (default name_8007A024)
    int fD4[3];
} GameEnemy;

typedef struct GameSlot_1
{
    int f0;
    GameAi* f4;
    GameEnemy data_8;
} GameSlot_1;

extern void SetBoneGroupFlags_80019B14(short* p, unsigned short* a1, unsigned short* a2);
extern short defaultBones_80079140[]; // default bone table
extern GameEnemy* sub_800A5F6C(void);
extern GameSlot_1* sub_800A17F4(unsigned int* src, GameAi* b);



extern void sub_800A2D28(GameAi* p);

extern void sub_800A2EC8(GameAi* p);

extern void FreeActiveOverlay_8002C014(void);

extern void FreeSeqSlotSound_80030664(void);



// context of an event script (list eventScripts_8008D410); same layout as EvCtxEventfnc in eventfnc.h
typedef struct GameEvCtx
{
    unsigned int flags_0;
    int start_4;
    int pc_8;
    int ret_C;
    int id_10;
    int f14;
    int f18;
    int f1C;
    int f20;
    int f24[6];
    int vec3C[5][3];
    int vec78[5][3];
    int fB4;
    int fB8;
    int fBC;
    int fC0;
    unsigned int fC4;
    int fC8;
    int fCC[8];
    int fEC;
    int fF0;
    int fF4;
    int fF8;
    int fFC;
    short f100;
    short f102;
    int f104;
    int f108;
    int pad_10C;
    int f110;
    int f114;
    int f118;
    int f11C;
    int f120;
} GameEvCtx;

// an event entity (list eventEntities_8008D400); same layout as EvEntEventfnc in eventfnc.h
typedef struct GameEvEnt
{
    int f0;
    int f4;
    int f8;
    int fC;
    int id_10;
    char pad_14[0x34];
    int pos_48[3];
    char pad_54[0x24];
    int f78;
    int f7C;
    int f80;
    int f84;
    int f88;
    int f8C;
} GameEvEnt;

extern EventEntry* sub_800A59D0(int a);

extern int sub_800B76B8(char* p);



extern GameSlot_1 dword_800B19F0[];

extern void sub_800A2D48(GameAi* p);

extern int sub_800A2CA8(int, int);

extern void DestroyActor_8001D600(Actor* p);

extern char* dword_8008B520;

extern void sub_800A170C(void);

extern int sub_800A2CA8(int, int);

extern int sub_800A7A60(int a);

extern char dword_800B19CC[];




// model header of a party member (first word: model id)
typedef struct GameModelHdr
{
    int id_0;
    char pad_4[0x1C];
    short f20;
    short f22;
    short f24;
    short f26;
    short pad_28;
    short f2A;
} GameModelHdr;

// the part of a party member its callbacks get (GameMember.cb_14)
typedef struct GameCb_1
{
    int f0;
    Actor* actor_4;
    int* f8;
    int (*cb_c)();
    void (*cb_10)();
} GameCb_1;

// what Actor.desc_15C of a party member points to
typedef struct GameActorDesc
{
    char pad_0[0x30];
    int clut_30; // index into name_8007DCAC / name_8007DCBC
} GameActorDesc;

// a party member (dword_800B0EC4.a)
typedef struct GameMember
{
    char pad_0[0x10];
    GameModelHdr** hdr_10;
    GameCb_1 cb_14;
} GameMember;

typedef struct GameList_1
{
    int count;
    GameMember* a[4];
    int b[4];
    int c[4];
} GameList_1;



extern GameMember* sub_800A77F4(int a);
extern GameActorDesc* sub_800A7A1C(int a);


extern int dword_800B19E0;





extern char* dword_8008B518;

extern char* dword_8008B534;

extern int* dword_8008D46C;

extern int* dword_800B1264;

typedef struct GameS3_1
{
    unsigned short a, b, c;
} GameS3_1;

extern int IsWithinDistance_8003B740(int* a, int* b, unsigned int* out);


extern void sub_800ADCEC();

extern void sub_800AD0F8(unsigned a);

extern int dword_80091C54;

extern int forceMapReload_80091C9C;

extern int dword_80091C8C;

typedef struct GameTask_1
{
    int f0;
    int f4;
    void (*next_8)();
} GameTask_1;


typedef struct GameSub_1
{
    int f0;
    int f4;
    int f8;
    int fc;
} GameSub_1;


extern void SetActorStatusTint_80018EBC(Actor* a, UnitStatus* b);

extern void GetActorHitFrame_80018E5C(Actor* a, int b);

extern void SetActorAnim_8001D760(Actor* a, int b, int c, int d);

extern int sub_800A52EC(short** a, int b, int c);

extern void* LoadOverlayIfChanged_80020D1C(int a, int b);

extern void sub_800A76D8();

extern void sub_800B78B8(int a);

extern void sub_800B78D0();

extern int sub_800A7790(void);

extern GameMember* sub_800A77F4(int a);
extern GameActorDesc* sub_800A7A1C(int a);



typedef struct GameCtx_1
{
    int f0;
    GameSlot_1* f4;     // the enemy slot that started the encounter
    int f8;             // number of fc entries
    GameSlot_1* fc[12]; // the other enemy slots
    int f3c;
    int f40;
    int f44;
    int f48;
    int f4c[12];
    Actor* actors_7c[12];
    UnitStats ents_ac[12]; // the encounter's minions (minion data)
    int f70c[12];
    int f73c[12];
    int f76c;
    int f770;
    int f774;
    int f778;
    int f77c;
    int f780;
    int f784;
    int f788;
    char pad_78c[0xa48 - 0x78c];
    int fa48;
} GameCtx_1;


typedef struct GameJ_1
{
    short h0;
    short h2;
} GameJ_1;

typedef struct GameQ_1
{
    int req_0; // file request
    int f4;
    int f8;
    char pad_c[0x30];
    int f3c;
} GameQ_1;

extern int TurnActorBy_8001DD44(Actor* a, int b, int c, int d);

extern void ReflectPoint_800A47B8(struct_v3* a, struct_v3* b, struct_v3* out);

extern void sub_800A7654();

extern void sub_800A1314();

extern void SetFadeMode_8001C19C(int a, int b);

extern void RunEventListFreeCallbacks_800438F8(int a);

extern void FreeEventList_80043A5C(int a);

extern void sub_800A6534(int a, int b);

extern void sub_800A654C(int a, int b);



typedef struct GameTab_1
{
    int f0;
    void (*fn)();
} GameTab_1;

extern void FreeMdecBuffer_800418CC(void);

extern void ReleaseMdecVLCFileBuffer_800418FC(void);

extern void sub_800B8A34(GameEvCtx* q);

extern void sub_800C4118(void* a, void* b, int c, int d);

extern void StartSceneFadeOut_8001AA50(int a);

extern int sub_800BA9E4(void);

extern void sub_800BA254();


extern void sub_800A7B00(int a);

extern void sub_800A7BF0(int a);

extern void sub_800A188C(GameSlot_1* p);

extern void sub_800A18C8(GameSlot_1* p);



extern int dword_800B199C[];

extern short sinTable_80084540[];


typedef struct GameObjList_1
{
    char pad_0[0xc];
    int count_c;
    char pad_10[4];
} GameObjList_1;

typedef struct GameTabEnt_1
{
    int v;
    int w;
} GameTabEnt_1;

typedef struct GameTable_1
{
    unsigned int count;
    GameTabEnt_1 e[1];
} GameTable_1;

extern EventNode* eventScripts_8008D410;

extern void sub_800A8EA4();

extern void sub_800BAE2C(int a, int b);

extern void sub_800B66C4(int a);

extern void* sub_800A55B0(int a); // one of the loaded event data blocks (what each holds depends on a)



extern void sub_800A15FC();

extern void sub_800A167C();

extern void sub_800A7AD8(int a);

typedef struct GameV6_1
{
    int a, b, c, d, e, f;
} GameV6_1;


extern char aFile_800A05CC[];

extern void sub_800A895C();

extern void sub_800A1BD0();

extern void sub_800A1E98();

extern void sub_800AC73C();

extern void FreeLoaderModelAnimSets_80020814(void);

extern void SetCameraBattleMode_80037720(void);

extern void StopSoundSeqs_80030D68(char* s);

extern void PlayMusic_800300E0(int a, int b);

extern void sub_800A1474();

extern char dword_80091CE0[];

extern int FindActorInFront_8001DECC(Actor* a, int b, int c);

extern unsigned short* sub_800B322C();

extern unsigned short* sub_800A53CC();

extern int sub_800AD154(int a);

extern int sub_800AD16C(int a, int b);

typedef struct GameRect_1
{
    short x, y, w, h;
} GameRect_1;

extern int GameFn_8003B9E0(int* a, int* b);

extern void sub_800B6BFC();

extern void sub_800B66DC();

extern int sub_800BBB94(void);


extern void sub_800A6968();

extern int CreateEventList_800435B4(char* p);


extern void TriggerActorEffect_8001E28C(Actor* a);

extern void InitMapState_80026FAC(void);

extern void GameFn_800A094C(void);

extern void ResetSoundTask_8002FEB8(void);

extern void InitSceneFade_8001A38C(void);

extern void ResetCameraToLevant_800376A8(void);

extern void sub_800A8140(void);

extern void sub_800A94CC(void);

extern EventNode* eventEntities_8008D400;

extern GameRect_1 stru_8008D420;

extern int useMapStartPos_80091C94;

typedef struct GameMode2_1
{
    int a;
    int b;
} GameMode2_1;

extern GameMode2_1* sub_800A72C8(GameMode2_1* out);

typedef struct GameMapEnt_1
{
    int pad_0;
    short f4;
    char pad_6[10];
} GameMapEnt_1;

extern GameMapEnt_1** mapTable_800B0608[];

extern void sub_800A4940(int a, int b);

extern void sub_800A5B54(GameEvCtx* p);

extern void sub_800A6060();

extern void sub_800A6168();


extern void sub_800A0A04();

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

extern int sub_800A48F4(int a);

extern void sub_800A46FC(GameAi* p);
extern void sub_800A45F8(GameAi* p);

typedef struct GameLst_1
{
    EventNode** p0; // a list head variable; 0 ends the table
    int f4;
} GameLst_1;



extern void sub_800A6CCC();

extern void ApplyAudioOutputFormat_80030988(void);

extern void sub_800A6C00();

extern void sub_800A6A48();

extern void sub_800A6B00();

extern void sub_800A73A8(void);

extern void sub_800A7450(EventNode* n);

extern void sub_800A13B8();

extern int CheckEnemyContact_800A19E4();

extern void StartPadVibration_80036528();

extern EventNode* enemyAiTasks_8008D49C;

extern unsigned char levantCaptureLevel_8008BD7C;

extern void sub_800A2EE4(EventEntry* e, void* ai);


extern int sub_800A4278();

extern void SetActorState_800A433C();

extern unsigned int DistanceSquaredXZ_8003B860(void* a, void* b);

extern int sub_800AB39C();

extern void sub_800A43FC();

extern void sub_800A44C0();

extern int* sub_800B3198(void);


extern int dword_8008B554;

#define ELEM(x) ((short)((int (*)(int))GetMinionElement_80019BF0)(x))






extern char name_80091C10[];

extern void FreeRecordTables_80026DE8(void* a, int b, void* c);



extern unsigned int name_80091C38;

extern int (*name_800BCDBC[])(GameEvCtx*);

extern void sub_800BC2B4(GameEvCtx* q);

typedef struct GameTim_1
{
    int mode_valid;
    int mode;
    int clut_len;
    RECT crect;
    u_long* caddr;
    int pix_len;
    RECT prect;
    u_long* paddr;
} GameTim_1;

typedef struct GameXY_1
{
    unsigned short x;
    unsigned short y;
} GameXY_1;

extern GameXY_1 name_8007DCA4;

extern GameXY_1 name_8007DCA8;

extern GameXY_1 name_8007DCAC[];

extern GameXY_1 name_8007DCBC[];



typedef struct GameStage_1
{
    int idx_0;
    int f4;
    int f8;
    int done_c[12];
} GameStage_1;

typedef struct GameD_1
{
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    void (*f1C)(int);
} GameD_1;

extern unsigned short padPressed_8009194C;

extern short word_80091CB8[];

extern EventNode* dword_8008D498;

extern EventNode* loadMenuTask_8008D480;




extern void sub_800A70F8();

extern void sub_800A7204();

extern void sub_800A7280();

extern int GetFileRequestStatus_8003BE30();

extern void FreezeScreen_8001C224();

extern void EndFade_8001C290();

extern void BeginFade_8001C260();

extern void sub_800A6DAC();

extern void DrawIntroMovie_8001AF64(void* p);

extern void SsUtAllKeyOff(int a);


extern char name_80096090[];

/* ---- GAME second half (G2) ---- */

typedef struct G2Inner
{
    unsigned int f0;
    char pad_4[0x48];
    FirFilter turn_4C;
    int turnBuf_5C[4];
    char pad_6C[0x30];
    int f9C;
    int fA0;
    int fA4;
    int fA8;
    int fAC;
    int fB0;
    char pad_B4[0x12];
    short fC6;
} G2Inner;

typedef struct G2Ctx
{
    char pad_0[0x24];
    G2Inner* f24;
} G2Ctx;

typedef struct G2Obj
{
    unsigned int f0;
    char pad_4[0x2C];
    int f30;
} G2Obj;

typedef struct G2V12
{
    int a;
    int b;
    int c;
} G2V12;

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

// Levant's controller object (gameTask_8008B4A4->f24); the field reads disagree on signedness at 0x10/0x14
// (DrawLevantModel_800A9708 uses them as unsigned: same code for its %) and 0x22 (some setters store a signed short)
typedef struct G2Act
{
    unsigned int f0;
    int f4; // input bits
    int f8;
    int fC;
    int f10; // animation frame
    int f14; // blend animation frame
    unsigned short u18;
    unsigned short u1a;
    short s1c;
    short s1e;
    short s20;
    unsigned short u22;
    short s24;
    short s26;
    short s28;
    short s2A;
    int f2C;
    int f30;
    int f34;
    int f38;
    int f3c;
    Model* model_40;
    char pad_44[4];
    G2V12 v48;
    G2V12 v54;
    G2V12 v60;
    G2V12 v6c; // root motion of the current animation frame (sub_800AA140)
    struct G2Path* path_78; // scripted walk (flag 0x400000, sub_800ABAA4)
    int f7c;    // step of path_78
    int tri_80; // floor triangle under Levant (mapState_8008B500.meshes_C[mesh_84].tris_4)
    int mesh_84;
    char pad_88[8];
    MATRIX mats_90[40];
    int bonePos_590[40][3];
    FirFilter turn_770;  // input_8: turn speed; output_C.low is added to Levant's facing
    int turnBuf_780[4];
} G2Act;

typedef struct G2Ctx2
{
    char pad_0[0x24];
    G2Act* f24;
} G2Ctx2;

extern G2Ctx* dword_8008B4CC;

extern G2Ctx2* gameTask_8008B4A4;




extern int dword_8008BDA0;

extern short word_8008BDA4;

extern short word_8008BDA6;



extern void sub_800AC380(int);

extern int levantEmptyCocoons_8008B818;

extern ModelList* dword_8007DC60; // the GAME overlay's model list

extern int sub_800A88E0();

extern void sub_800AB010();

extern int sub_800AC518();

extern void sub_800AC6A8();

extern int sub_800AC4A8();

extern int sub_800ADBA0(short*);

typedef struct G2Rec
{
    unsigned char f0;
    unsigned char f1;
    char pad_2;
    unsigned char f3;
    short s4;
    short s6;
    short s8;
    unsigned short sA;
    short sC;
    char pad_E[0x26];
    int f34;
    char pad_38[8];
} G2Rec;

extern int sub_800AC794(int, int);

extern void sub_800A913C();

extern void sub_800ABAD4();

extern void sub_800AB444();


extern int dword_800795C0[]; // FIR coefficients of Levant's turn filter

typedef struct G2P
{
    short s0;
    short s2;
    unsigned short u4;
    unsigned short u6;
} G2P;

extern unsigned char equippedWeaponId_8008BD54;

extern unsigned char equippedArmor_8008BD55;

extern unsigned char byte_8008BD56;

extern InvSlot* sub_800AD4D8();

extern int sub_800AD8E4();




extern int sub_800A7790();




extern void sub_800ABC78();

extern void sub_800AA25C();

extern void sub_800AA51C();

extern void sub_800AACF8();

extern void sub_800AC02C();

extern int sub_800AD670(int, int);


extern void PoolInit_8003FF1C(void*, unsigned);

extern void sub_800ACB64();

extern void PlaySfx_80031494(int);

extern void PlaySeqSlot_80031160(int, int);

typedef struct G2Ent16
{
    short id;
    char pad_2[2];
    unsigned short u4;
    short s6;
    char pad_8[8];
} G2Ent16;





extern int GetMagicEffect_8001AC8C(int);

extern void RequestEffect_800148F4(int);

extern int GetWeaponEffect_800189F8();

extern short word_8008D782;

extern void sub_8004ED78(int);

extern int sub_8003B9E0(int*, int*);

extern G2V12 statusTintLevel1_8007A0A4;

extern G2V12 statusTintLevel2_8007A0B0;

extern G2V12 statusTintLevel3_8007A0BC;

extern G2V12 statusTintLevel4_8007A0C8;

extern G2V12 statusTintLevel5_8007A0D4;

extern G2V12 statusTintLevel6_8007A0E0;

extern G2V12 statusTintLevel7_8007A0EC;

extern G2V12 statusTintPoison_8007A0F8;

extern G2V12 dword_8007A104;

extern G2V12 statusTintPoisonLevel2_8007A110;

extern G2V12 statusTintPoisonLevel3_8007A11C;

extern G2V12 statusTintPoisonLevel4_8007A128;

extern G2V12 statusTintPoisonLevel5_8007A134;

extern G2V12 statusTintPoisonLevel6_8007A140;

extern G2V12 statusTintPoisonLevel7_8007A14C;

extern G2V12 dword_8007A164;

extern char dword_8007DC80;

extern char dword_8007DC88;

extern unsigned int dword_8008BD38;

extern void TintVramImage_800292D0();

typedef struct G2L2
{
    int f0;
    int f4;
    int rest[0x48];
} G2L2;

extern int dword_8001D060(int);

extern int sub_800A79C8(int);

extern int* name_800A7940(int);

extern int IsWithinDistance_8003B740();


extern int sub_800A6D50(int);

extern void sub_800A6D30(int);

extern int eventDispatchHalt_8008B540;

extern void sub_800A9414(void*, int, int);


extern void PoolDestroy_8003FF7C(void*);





extern int sub_800AC474(int);

extern int sub_800AC3E4();

extern Model* sub_800AC38C();

extern InvSlot* sub_800AD58C();

extern InvSlot* sub_800AD604(int);

extern int sub_800AD374(int);

extern int sub_800AD308(int);

extern int sub_800AD288(int, int);

extern int sub_800AD2C8(int, int);

extern int sub_800AD67C(int, int);

extern unsigned char* sub_800AC7B4(int);

extern int sub_800AD73C(int);

extern int sub_800AD8BC();


extern short cameraTargetScreenPos_8008D668[2];

extern int sub_800AB304();

extern int sub_800AB354();

extern int sub_800AB85C();

extern void sub_800AB884();

extern void sub_800AB8AC();

extern void sub_800AC318();

extern int sub_800A5C40();

extern void sub_800AB910();

extern void sub_800ABBD8();

typedef struct G2Pair_1
{
    short a;
    short b;
} G2Pair_1;

typedef struct G2Mode_1
{
    int a;
    int b;
} G2Mode_1;

typedef struct G2InnerC
{
    unsigned int f0;
    char pad_4[0x30];
    int f34;
    int f38;
    char pad_3C[0x8a];
    short fC6;
    char pad_C8[4];
    int fCC;
} G2InnerC;

extern G2Mode_1 name_800B1084[];


typedef struct G2Cmd_1
{
    int f0;
    int kind_4;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
    int f24;
} G2Cmd_1;

typedef struct G2Init_1
{
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    char pad_14[4];
    short s18;
    short s1a;
    short s1c;
    short s1e;
    char pad_20[6];
    short s26;
    char pad_28[8];
    int f30;
    char pad_34[8];
    int f3C;
} G2Init_1;

extern void sub_800B80C8(void* p);

typedef struct G2Skel_1
{
    FtgObject* ftg_0;
    void* f4;
    void* f8;
    void* bones;
    void* base;
    char* pose;
    unsigned int frame;
    int flags;
    char* pos;
    int f24;
    unsigned long* ot;
} G2Skel_1;


extern int FindNearestCameraPoint_80019CC4(void* p);


extern short word_8007DC82;

extern short word_8007DC8A;


extern void DrawAnimSkel_80046A58(void* sk, void* buf, char* pose);

extern void DrawAnimSkelBlend_80047E28(void* sk, void* base, char* pose, unsigned int frame, int w, void* buf, char* t);

extern void DrawSpriteVtxQuadsGT4_800459E4(void* bones, void* m, unsigned long* ot, int flags);

extern void GetAnimRootMotion_8004D288(void* out, void* s, int k);

extern void InitSporeTask_80011ADC();
extern void ResetMapLoaderTask_8002830C();
extern void sub_800A818C();
extern void sub_800A2EEC();
extern void sub_800A2FB8();
extern void sub_800A31DC();
extern void sub_800A333C();
extern void sub_800A34D8();
extern void sub_800A366C();
extern void sub_800A3804();
extern void sub_800A3954();
extern void sub_800A3A8C();
extern void sub_800A3BEC();
extern void sub_800A3D24();
extern void sub_800A3E88();
extern void sub_800A3FC0();
extern void sub_800A09D8();
extern void sub_800A1444();

extern int dword_8008D624;
extern int battleMenuTask_8008D468[3];
extern int dword_8008D444;
extern int dword_8008B564[3];
extern int dword_8008D4B0;
extern EventNode* encounterTask_8008D674;
extern int dword_8008D438;
extern int dword_8008D670;
extern int dword_8008D4A8;
extern int dword_8008D3E0;
extern EventNode* messageWindowTask_8008D640;
extern EventNode* vibrationTasks_8008D4B8;
extern int dword_8008B4AC[2];
extern int dword_8008B4C0[2];
extern int dword_8008D48C[4];
extern int dword_8008D5F8[2];
extern int dword_8008D614;
extern int dword_8008D634[3];
extern int hitNumberTasks_8008D778[2];
extern int dword_8008D4C4;
extern int dword_8008B4B8;
extern int dword_8008D62C;
extern ShortPair screenOffset_8008D474;
extern char name_800BCB00[];
extern const int dword_800A05A0;
extern const char aAssertionFaile_800A05A4[];
extern const char aEnmbatleC_800A05CC[12];
extern const char aAssertionFaile_800A0660[];
extern const char aEventcomC_800A0688[];
extern const int dword_800A0694;
extern const int dword_800A06F0[18];
extern const char dword_800A07E0[];
extern const char dword_800A0808[];
extern const int dword_800A0814;
extern GameRec_1 dword_800ADE78;
extern short dword_800ADE8C[2];
extern short dword_800ADE90[2];
extern short dword_800ADE94[4];
extern short *dword_800ADE9C[7];
extern void (*name_800ADEB8[53][2])();
extern short dword_800AE060[8];
extern short dword_800AE070[10];
extern short dword_800AE084[4];
extern short dword_800AE08C[4];
extern short dword_800AE094[2];
extern short dword_800AE098[2];
extern short dword_800AE09C[2];
extern short dword_800AE0A0[14];
extern short dword_800AE0BC[8];
extern short dword_800AE0CC[4];
extern short dword_800AE0D4[2];
extern short dword_800AE0D8[14];
extern short dword_800AE0F4[6];
extern short dword_800AE100[4];
extern short dword_800AE108[2];
extern short dword_800AE10C[2];
extern short dword_800AE110[2];
extern short dword_800AE114[2];
extern short dword_800AE118[2];
extern short dword_800AE11C[2];
extern short dword_800AE120[6];
extern short dword_800AE12C[4];
extern short dword_800AE134[6];
extern short dword_800AE140[8];
extern short dword_800AE150[8];
extern short dword_800AE160[2];
extern short dword_800AE164[4];
extern short dword_800AE16C[2];
extern short dword_800AE170[2];
extern short dword_800AE174[2];
extern short dword_800AE178[18];
extern short dword_800AE19C[6];
extern short dword_800AE1A8[4];
extern short dword_800AE1B0[2];
extern short dword_800AE1B4[16];
extern short dword_800AE1D4[16];
extern short dword_800AE1F4[16];
extern short dword_800AE214[16];
extern short dword_800AE234[16];
extern short *dword_800AE254[39];
extern short dword_800AE2F0[6];
extern short dword_800AE2FC[4];
extern short dword_800AE304[2];
extern short dword_800AE308[8];
extern short dword_800AE318[6];
extern short dword_800AE324[6];
extern short dword_800AE330[6];
extern short dword_800AE33C[6];
extern short dword_800AE348[16];
extern short dword_800AE368[10];
extern short dword_800AE37C[4];
extern short dword_800AE384[6];
extern short dword_800AE390[8];
extern short dword_800AE3A0[6];
extern short dword_800AE3AC[6];
extern short dword_800AE3B8[6];
extern short dword_800AE3C4[6];
extern short *dword_800AE3D0[17];
extern int dword_800AE414[3];
extern int dword_800AE420[3];
extern int dword_800AE42C[3];
extern int dword_800AE438[3];
extern int dword_800AE444[3];
extern int dword_800AE450[3];
extern int dword_800AE45C[3];
extern int dword_800AE468[3];
extern int dword_800AE474[3];
extern int dword_800AE480[3];
extern int dword_800AE48C[3];
extern int dword_800AE498[3];
extern int dword_800AE4A4[3];
extern int dword_800AE4B0[3];
extern int dword_800AE4BC[3];
extern int dword_800AE4C8[3];
extern int dword_800AE4D4[3];
extern int *name_800AE4E0[17];
extern int dword_800AE524[219];
extern int dword_800AE890;
extern int dword_800AE894;
extern int dword_800AE898;
extern int dword_800AE89C;
extern int dword_800AE8A0;
extern int dword_800AE8A4;
extern int dword_800AE8A8;
extern int dword_800AE8AC;
extern int dword_800AE8B0;
extern int dword_800AE8B4;
extern int dword_800AE8B8;
extern int dword_800AE8BC;
extern int dword_800AE8C0;
extern int dword_800AE8C4;
extern int dword_800AE8C8;
extern int dword_800AE8CC;
extern int dword_800AE8D0;
extern int dword_800AE8D4;
extern int dword_800AE8D8;
extern int dword_800AE8DC;
extern int dword_800AE8E0;
extern int dword_800AE8E4;
extern int dword_800AE8E8;
extern int dword_800AE8EC;
extern int dword_800AE8F0;
extern int dword_800AE8F4;
extern int dword_800AE8F8;
extern int dword_800AE8FC;
extern int dword_800AE900;
extern int dword_800AE904;
extern int dword_800AE908;
extern int dword_800AE90C;
extern int dword_800AE910;
extern int dword_800AE914[8];
extern int dword_800AE934;
extern int dword_800AE938[2];
extern int dword_800AE940;
extern int dword_800AE944;
extern int dword_800AE948;
extern int dword_800AE94C;
extern int dword_800AE950;
extern int dword_800AE954;
extern int dword_800AE958;
extern int dword_800AE95C;
extern int dword_800AE960;
extern int dword_800AE964;
extern int dword_800AE968;
extern int dword_800AE96C;
extern int dword_800AE970;
extern int dword_800AE974;
extern int dword_800AE978;
extern int dword_800AE97C;
extern int dword_800AE980;
extern int dword_800AE984;
extern int dword_800AE988;
extern int dword_800AE98C;
extern int dword_800AE990;
extern int dword_800AE994;
extern int dword_800AE998;
extern int dword_800AE99C;
extern int dword_800AE9A0;
extern int dword_800AE9A4;
extern int dword_800AE9A8;
extern int dword_800AE9AC;
extern int dword_800AE9B0;
extern int dword_800AE9B4;
extern int dword_800AE9B8;
extern int dword_800AE9BC;
extern int dword_800AE9C0;
extern int dword_800AE9C4;
extern int dword_800AE9C8;
extern int dword_800AE9CC;
extern int dword_800AE9D0[3];
extern void *dword_800AE9DC[73];
extern int dword_800AEB00[27];
extern int dword_800AEB6C[3];
extern int dword_800AEB78;
extern int dword_800AEB7C;
extern int name_800AEB80[15];
extern int *name_800AEBBC;
extern void *name_800AEBC0[2];
extern void *name_800AEBC8;
extern int name_800AEBCC[2];
extern int name_800AEBD4;
extern int dword_800AEBD8;
extern int dword_800AEBDC;
extern int dword_800AEBE0;
extern int dword_800AEBE4;
extern int dword_800AEBE8;
extern int name_800AEBEC;
extern int dword_800AEBF0;
extern int dword_800AEBF4;
extern int dword_800AEBF8[19];
extern int dword_800AEC44[20];
extern int dword_800AEC94[20];
extern int dword_800AECE4[16];
extern int dword_800AED24[304];
extern int dword_800AF1E4[32];
extern int dword_800AF264[36];
extern int dword_800AF2F4[32];
extern int dword_800AF374[20];
extern int dword_800AF3C4[20];
extern int dword_800AF414[36];
extern int dword_800AF4A4[24];
extern int dword_800AF504[56];
extern int dword_800AF5E4[20];
extern int dword_800AF634[20];
extern int dword_800AF684[20];
extern int dword_800AF6D4[20];
extern int dword_800AF724[8];
extern int dword_800AF744[16];
extern int dword_800AF784[24];
extern int dword_800AF7E4[12];
extern int dword_800AF814[12];
extern int dword_800AF844[20];
extern int dword_800AF894[20];
extern int dword_800AF8E4[28];
extern int dword_800AF954[8];
extern int dword_800AF974[8];
extern int dword_800AF994[16];
extern int dword_800AF9D4[16];
extern int dword_800AFA14[16];
extern int dword_800AFA54[28];
extern int dword_800AFAC4[56];
extern int dword_800AFBA4[80];
extern int dword_800AFCE4[200];
extern int dword_800B0004[100];
extern int dword_800B0194[48];
extern int dword_800B0254[68];
extern int dword_800B0364[112];
extern void *dword_800B0524[6];
extern void *dword_800B053C[13];
extern void *dword_800B0570[13];
extern void *dword_800B05A4[13];
extern void *dword_800B05D8[6];
extern void *dword_800B05F0[6];
extern G2Ent16 **name_800B0608[36];
extern int dword_800B0698;
extern int dword_800B069C[5];
extern int dword_800B06B0[3];
extern int dword_800B06BC;
extern int dword_800B06C0[3];
extern int dword_800B06CC[6];
extern int dword_800B06E4[6];
extern int dword_800B06FC[6];
extern int dword_800B0714[6];
extern int dword_800B072C[6];
extern int dword_800B0744[6];
extern int dword_800B075C[6];
extern int dword_800B0774[6];
extern int dword_800B078C[6];
extern int dword_800B07A4[6];
extern int dword_800B07BC[6];
extern int dword_800B07D4[6];
extern int dword_800B07EC[6];
extern int dword_800B0804[6];
extern int dword_800B081C[6];
extern int dword_800B0834[6];
extern int dword_800B084C[6];
extern int dword_800B0864[6];
extern int dword_800B087C[6];
extern int dword_800B0894[6];
extern int dword_800B08AC[6];
extern int dword_800B08C4[6];
extern int dword_800B08DC[6];
extern int dword_800B08F4[6];
extern int dword_800B090C[6];
extern int dword_800B0924[6];
extern int dword_800B093C[6];
extern int dword_800B0954[6];
extern int dword_800B096C[6];
extern int dword_800B0984[6];
extern int dword_800B099C[6];
extern int dword_800B09B4[6];
extern int dword_800B09CC[6];
extern int dword_800B09E4[6];
extern GameLst_1 dword_800B09FC[2];
extern GameLst_1 dword_800B0A0C[4];
extern GameLst_1 dword_800B0A2C[26];
extern GameLst_1 dword_800B0AFC[35];
extern GameLst_1 dword_800B0C14[4];
extern GameLst_1 dword_800B0C34[3];
extern GameLst_1 dword_800B0C4C[7];
extern GameLst_1 dword_800B0C84[12];
extern GameLst_1 dword_800B0CE4[4];
extern GameLst_1 dword_800B0D04[2];
extern GameLst_1 dword_800B0D14[6];
extern GameLst_1 dword_800B0D44[3];
extern GameLst_1 dword_800B0D5C[3];
extern GameLst_1 *dword_800B0D74[12];
extern char dword_800B0DA4[232];
extern int dword_800B0E8C[6];
extern char name_800B0EA4[20];
extern GameTab_1 dword_800B0EB8[1];
extern int dword_800B0EC0;
extern GameList_1 dword_800B0EC4;
extern char dword_800B0EF8;
extern int dword_800B0EFC[45];
extern SVECTOR dword_800B0FB0[55];
extern int dword_800B1168;
extern int dword_800B116C[19];
extern unsigned char dword_800B11B8[20];
extern int dword_800B11CC[4];
extern int dword_800B11DC[19];
extern int dword_800B1228;
extern int dword_800B122C[13];
extern GameCtx_1 gCtx_800B1260;
extern int dword_800B1CAC[3];
extern GameEnemy dword_800B1CB8;
extern int dword_800B1D98;
extern int dword_800B1D9C;
extern EventNode *dword_800B1DA0[1];
extern EventNode *dword_800B1DA4[1];
extern EventNode *dword_800B1DA8[1];
extern EventNode *dword_800B1DAC;
extern EventNode *dword_800B1DB0[1];
extern EventNode *dword_800B1DB4[1];
extern EventNode *dword_800B1DB8[1];
extern EventNode *dword_800B1DBC;
extern EventNode *dword_800B1DC0[1];
extern EventNode *dword_800B1DC4[1];
extern int dword_800B1DC8[2];
extern char dword_800B1DD0;
extern int dword_800B1DD4[9];
extern char dword_800B1DF8;
extern int dword_800B1DFC[304];
