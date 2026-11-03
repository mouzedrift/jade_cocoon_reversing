// GAME.BIN: declarations shared by its source files
// GAME.BIN
#include "common.h"

#include "funcs.h"

#include "globals.h"

#include "actor.h"

#include "tu_8001EA48.h"
#include "tu_80036528.h"

extern void sub_800A6D30(int a);

struct GameObj5_1;
struct GameEnt_1;
// AI of an enemy actor (CreateEnemyAiEvent_800A2D90; the name_800ADEB8 state handlers)
typedef struct GameAi
{
    unsigned int* flags_0;     // the flags of its event entry (q[0] = the entry)
    struct GameEnt_1* minion_4; // minion data (in the enemy slot)
    Actor* actor_8;
    int state_c;
    int f10;
    char pad_14[0xC];
    int anim_20;
    int timer_24;
    int f28; // turn direction (FindActorInFront_8001DECC)
    int f2c; // turn amount
} GameAi;

typedef struct GameHolder_1
{
    int f0;
    GameAi* f4;
} GameHolder_1;

typedef struct GameRec_1
{
    int f0, f4, f8, fc, f10;
} GameRec_1;

typedef struct GameV3_1
{
    int a, b, c;
} GameV3_1;

typedef struct GameSlot_1
{
    int f0;
    GameAi* f4;
    char data_8[0xe0];
} GameSlot_1;

// minion data (0x88 bytes, InitMinionData_8001900C)
typedef struct GameEnt_1
{
    char pad_0[0x44];
    unsigned char rank_44;
    char pad_45[0x17];
    int f5c; // species
    char pad_60[0x28];
} GameEnt_1;

extern void sub_800A2D28(GameAi* p);

extern void sub_800A2EC8(GameAi* p);

extern void FreeActiveOverlay_8002C014(void);

extern void FreeSeqSlotSound_80030664(void);

extern GameRec_1 dword_800ADE78;

extern int dword_800AEB6C[];

// context of an event script (list dword_8008D410); same layout as EvCtxEventfnc in eventfnc.h
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

// an event entity (list dword_8008D400); same layout as EvEntEventfnc in eventfnc.h
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

extern struct GameObj5_1* sub_800A59D0(int a);

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

extern int dword_800B1D98;

extern int dword_800AEBF0;

extern int dword_800B0EC0;

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

extern GameList_1 dword_800B0EC4;

extern int dword_800AEBF4;

extern GameMember* sub_800A77F4(int a);
extern GameActorDesc* sub_800A7A1C(int a);

extern int dword_800AEBD8;

extern int dword_800B19E0;

extern EventNode* dword_800B1DBC;

extern int dword_800B0698;

extern int dword_800AEBE0;

extern char dword_800B1CB8[];

extern char* dword_8008B518;

extern char* dword_8008B534;

extern int* dword_8008D46C;

extern int* dword_800B1264;

typedef struct GameSave3_1
{
    char pad_0[0x2e4];
    short f2e4;
    short pad_2e6;
    short f2e8;
    short pad_2ea;
    short f2ec;
    short pad_2ee;
    short f2f0;
} GameSave3_1;

typedef struct GameS3_1
{
    unsigned short a, b, c;
} GameS3_1;

extern int IsWithinDistance_8003B740(int* a, int* b, unsigned int* out);

extern int dword_800AEBE4;

extern void sub_800ADCEC();

extern void sub_800AD0F8(unsigned a);

extern int dword_80091C54;

extern int dword_80091C9C;

extern int dword_80091C8C;

typedef struct GameVec3_1
{
    int x, y, z;
} GameVec3_1;

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


extern void sub_80018EBC(Actor* a, int b);

extern void sub_80018E5C(Actor* a, int b);

extern void sub_8001D760(Actor* a, int b, int c, int d);

extern int sub_800A52EC(short** a, int b, int c);

extern void* LoadOverlayIfChanged_80020D1C(int a, int b);

extern void sub_800A76D8();

extern void sub_800B78B8(int a);

extern void sub_800B78D0();

extern int sub_800A7790(void);

extern GameMember* sub_800A77F4(int a);
extern GameActorDesc* sub_800A7A1C(int a);

extern short* dword_800AE254[];

// what sub_800A29CC hands out about an actor
typedef struct GameActorInfo
{
    int f0;
    int* pos_4;
    char* f8;
    char* fC;
    int pad_10[7];
    char* f2C;
    int* f30;
} GameActorInfo;

typedef struct GameCtx_1
{
    int f0;
    int f4;
    int f8;
    int fc[12];
    int f3c;
    int f40;
    int f44;
    int f48;
    int f4c[12];
    Actor* actors_7c[12];
    GameEnt_1 ents_ac[12]; // the encounter's minions (minion data)
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

extern GameCtx_1 gCtx_800B1260;

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

extern int sub_8001DD44(Actor* a, int b, int c, int d);

extern void ReflectPoint_800A47B8(GameVec3_1* a, GameVec3_1* b, GameVec3_1* out);

extern void sub_800A7654();

extern void sub_800A1314();

extern void SetFadeMode_8001C19C(int a, int b);

extern void RunEventListFreeCallbacks_800438F8(int a);

extern void FreeEventList_80043A5C(int a);

extern void sub_800A6534(int a, int b);

extern void sub_800A654C(int a, int b);

extern GameVec3_1 levantPos_8008BD18; // saveData_8008B570 + 0x7A8

extern int dword_800AEB7C;

typedef struct GameTab_1
{
    int f0;
    void (*fn)();
} GameTab_1;

extern void FreeMdecBuffer_800418CC(void);

extern void ReleaseMdecVLCFileBuffer_800418FC(void);

extern void sub_800B8A34(GameEvCtx* q);

extern void sub_800C4118(void* a, void* b, int c, int d);

extern void sub_8001AA50(int a);

extern int sub_800BA9E4(void);

extern void sub_800BA254();

extern short* dword_800AE3D0[];

extern void sub_800A7B00(int a);

extern void sub_800A7BF0(int a);

extern void sub_800A188C(GameHolder_1* p);

extern void sub_800A18C8(GameHolder_1* p);

extern GameTab_1 dword_800B0EB8[];

extern int dword_800AEBD8;

extern int dword_800B199C[];

extern short sinTable_80084540[];

typedef struct GameSave_1
{
    char pad_0[0x2f0];
    short f2f0;
    short f2f2;
} GameSave_1;

typedef struct GameObj5_1
{
    unsigned int flags_0;
    char pad_4[4];
    void (*fn_8)();
    void (*fn_c)();
    int pad_10;
    void* obj_14; // the work area (EventEntry.buffer)
} GameObj5_1;

typedef struct GameNode_1
{
    char pad_0[4];
    struct GameNode_1* next_4;
    char pad_8[4];
    int count_c;
    GameObj5_1 sub_10;
} GameNode_1;

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

extern GameNode_1* dword_8008D410;

extern void sub_800A8EA4();

extern void sub_800BAE2C(int a, int b);

extern void sub_800B66C4(int a);

extern GameTable_1* sub_800A55B0(int a);

extern int dword_800AEBE8;

extern int dword_800B1228;

extern void sub_800A15FC();

extern void sub_800A167C();

extern void sub_800A7AD8(int a);

typedef struct GameV6_1
{
    int a, b, c, d, e, f;
} GameV6_1;

extern char aAssertionFaile_800A05A4[];

extern char aFile_800A05CC[];

extern void sub_800A895C();

extern void sub_800A1BD0();

extern void sub_800A1E98();

extern void sub_800AC73C();

extern void FreeLoaderModelAnimSets_80020814(void);

extern void sub_80037720(void);

extern void StopSoundSeqs_80030D68(char* s);

extern void PlayMusic_800300E0(int a, int b);

extern void sub_800A1474();

extern char dword_80091CE0[];

extern int FindActorInFront_8001DECC(Actor* a, int b, int c);

extern short* sub_800B322C();

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

extern int dword_800B1DC8[];

extern void sub_800A6968();

extern int CreateEventList_800435B4(char* p);

extern char dword_800B0DA4[];

extern void sub_8001E28C(Actor* a);

extern void sub_80026FAC(void);

extern void GameFn_800A094C(void);

extern void ResetSoundTask_8002FEB8(void);

extern void sub_8001A38C(void);

extern void ResetCameraToLevant_800376A8(void);

extern void sub_800A8140(void);

extern void sub_800A94CC(void);

extern GameNode_1* dword_8008D400;

extern GameRect_1 stru_8008D420;

extern int dword_80091C94;

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

typedef struct GameSave2_1
{
    char pad_0[0x2e4];
    short f2e4;
    short pad_2e6;
    short f2e8;
    short pad_2ea;
    short f2ec;
    char pad_2ee[0x54A];
    unsigned short f838[12]; // the tables sub_800A53CC picks by f2e4/f2e8 (title.c fills them with 0x8000)
    unsigned short f850[18];
    unsigned short f874[44];
    unsigned short f8cc[22];
    unsigned short f8f8[10];
    unsigned short f90c[16];
    unsigned short f92c[42];
} GameSave2_1;

extern GameMapEnt_1** dword_800B0608[];

extern void sub_800A4940(int a, int b);

extern void sub_800A5B54(GameEvCtx* p);

extern void sub_800A6060();

extern void sub_800A6168();

extern int dword_800AEBDC;

extern void sub_800A0A04();

typedef struct GameVec4_1
{
    int x, y, z, w;
} GameVec4_1;

typedef struct GameSave4_1
{
    char pad_0[0x7a8];
    int f7a8;
    int pad_7ac;
    int f7b0;
} GameSave4_1;

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

typedef struct GameLst_1
{
    int** p0;
    int f4;
} GameLst_1;

extern GameLst_1 dword_800B09FC[];

extern GameLst_1* dword_800B0D74[];

extern void sub_800A6CCC();

extern void ApplyAudioOutputFormat_80030988(void);

extern void sub_800A6C00();

extern void sub_800A6A48();

extern void sub_800A6B00();

extern void sub_800A73A8(void);

extern void sub_800A7450(GameNode_1* n);

extern void sub_800A13B8();

extern int CheckEnemyContact_800A19E4();

extern void StartPadVibration_80036528();

extern int dword_8008D49C;

extern unsigned char levantCaptureLevel_8008BD7C;

extern void sub_800A2EE4(void);

extern void (*name_800ADEB8[][2])();

extern int sub_800A4278();

extern void SetActorState_800A433C();

extern unsigned int DistanceSquaredXZ_8003B860(void* a, void* b);

extern int sub_800AB39C();

extern void sub_800A43FC();

extern void sub_800A44C0();

extern int* sub_800B3198(void);

extern int* name_800AE4E0[];

extern int dword_8008B554;

#define ELEM(x) ((short)((int (*)(int))GetMinionElement_80019BF0)(x))

extern int name_800AEB80[];

extern int name_800AEBBC;

extern int name_800AEBC0[];

extern int name_800AEBC8;

extern int name_800AEBCC[];

extern char name_80091C10[];

extern void sub_80026DE8(void* a, int b, void* c);

extern int name_800AEBD4;

extern int name_800AEBEC;

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

extern char aAssertionFaile_800A0660[];

extern char aEventcomC_800A0688[];

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

extern int dword_8008D498;

extern int dword_8008D480;

extern int dword_800B1DAC;

extern int dword_800B06B0[];

extern int dword_800B06BC;

extern void sub_800A70F8();

extern void sub_800A7204();

extern void sub_800A7280();

extern int GetFileRequestStatus_8003BE30();

extern void sub_8001C224();

extern void EndFade_8001C290();

extern void BeginFade_8001C260();

extern void sub_800A6DAC();

extern void DrawIntroMovie_8001AF64(void* p);

extern void SsUtAllKeyOff(int a);

extern char name_800B0EA4[];

extern char name_80096090[];

/* ---- GAME second half (G2) ---- */

typedef struct G2Inner
{
    unsigned int f0;
    char pad_4[0x98];
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

typedef struct G2Inner2
{
    unsigned int f0;
    int f4;
    int f8;
    int fC;
    char pad_10[0x10];
    short s20;
    short f22;
    short f24;
    char pad_26[2];
    short f28;
    char pad_2A[0xA];
    int f34;
    int f38;
    char pad_3C[4];
    struct_obj_E* f40;
    char pad_44[4];
    G2V12 v48;
    G2V12 v54;
    G2V12 v60;
    char pad_6C[0xC];
    int f78;
    int f7c;
} G2Inner2;

typedef struct G2Ctx2
{
    char pad_0[0x24];
    G2Inner2* f24;
} G2Ctx2;

typedef struct G2Bits
{
    char pad_0[0x290];
    unsigned char b[0x20];
} G2Bits;

typedef struct G2Bits3
{
    char pad_0[0x2A3];
    unsigned char c[0x20];
} G2Bits3;

extern G2Ctx* dword_8008B4CC;

extern G2Ctx2* dword_8008B4A4;

extern char levantStatus_8008BD38;


extern int dword_8008BDA0;

extern short word_8008BDA4;

extern short word_8008BDA6;

extern char dword_800B1DF8;

extern char dword_800B0FB0;

extern void sub_800AC380(int);

extern int levantEmptyCocoons_8008B818;

extern int* dword_8007DC60;

extern unsigned char playerYan_8008B594[];

#define G2SAVE ((unsigned char*)&saveData_8008B570)

typedef struct G2Sv
{
    char pad_0[0x2FE];
    short s;
} G2Sv;

typedef struct G2Act
{
    unsigned int f0;
    int f4; // input bits
    int f8;
    int fC;
    int f10;
    int f14;
    char pad_18[4];
    short s1c;
    short s1e;
    short s20;
    unsigned short u22;
    short s24;
    short s26;
    short s28;
    short s2A;
    int f2C;
    char pad_30[4];
    int f34;
    int f38;
    char pad_3C[4];
    int f40;
} G2Act;

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

#define G2REC(a, b) ((G2Rec*)sub_80024E38(dword_8007DC60[2]))

extern int sub_800AC794(int, int);

extern void sub_800A913C();

extern void sub_800ABAD4();

extern void sub_800AB444();

extern void FirFilterInit_8001450C(int*, void*, int, int);

extern char dword_800795C0;

typedef struct G2Stat
{
    char pad_0[0x7D0];
    unsigned short cur;
    unsigned short max;
    unsigned short cur2;
    unsigned short max2;
} G2Stat;

typedef struct G2P
{
    short s0;
    short s2;
    unsigned short u4;
    unsigned short u6;
} G2P;

typedef struct G2E
{
    char pad_0[0x2F8];
    short a;
    short b;
    short c;
    short d;
} G2E;

typedef struct G2Save2
{
    char pad_0[0x2F4];
    int n;
} G2Save2;

extern unsigned char equippedWeaponId_8008BD54;

extern unsigned char equippedArmor_8008BD55;

extern unsigned char byte_8008BD56;

extern unsigned char* sub_800AD4D8();

extern int sub_800AD8E4();

typedef struct G2Sv4
{
    char pad_0[0x7E4];
    unsigned char b7E4;
    unsigned char b7E5;
    char pad_7E6[0x4A];
    int f830;
    short s834;
} G2Sv4;

extern int dword_800B116C[];

extern unsigned char dword_800B11B8[];


extern int sub_800A7790();




extern void sub_800ABC78();

extern void sub_800AA25C();

extern void sub_800AA51C();

extern void sub_800AACF8();

extern void sub_800AC02C();

extern int sub_800AD670(int, int);

extern int IsAnimInModelAnimSet_80025924(int, int);

extern void PoolInit_8003FF1C(void*, unsigned);

extern void sub_800ACB64();

extern void PlaySfx_80031494(int);

extern void PlaySeqSlot_80031160(int, int);

typedef struct G2Sv5
{
    char pad_0[0x7B6];
    unsigned short u7B6;
} G2Sv5;

typedef struct G2Q
{
    char pad_0[4];
    unsigned int f4;
    char pad_8[0x770];
    int f778;
    unsigned short u77C;
} G2Q;

typedef struct G2Ent16
{
    short id;
    char pad_2[2];
    unsigned short u4;
    short s6;
    char pad_8[8];
} G2Ent16;

extern G2Ent16** name_800B0608[];

extern void FirFilterStep_80014588(void*, void*, int);

extern char dword_800A07E0[];

extern char dword_800A0808[];

extern int sub_8001AC8C(int);

extern void RequestEffect_800148F4(int);

extern int sub_800189F8();

extern short word_8008D782;

extern void sub_8004ED78(int);

#define G2LEV ((G2V12*)((char*)&saveData_8008B570 + 0x7A8))

extern int sub_8003B9E0(int*, int*);

extern G2V12 dword_8007A0A4;

extern G2V12 dword_8007A0B0;

extern G2V12 dword_8007A0BC;

extern G2V12 dword_8007A0C8;

extern G2V12 dword_8007A0D4;

extern G2V12 dword_8007A0E0;

extern G2V12 dword_8007A0EC;

extern G2V12 dword_8007A0F8;

extern G2V12 dword_8007A104;

extern G2V12 dword_8007A110;

extern G2V12 dword_8007A11C;

extern G2V12 dword_8007A128;

extern G2V12 dword_8007A134;

extern G2V12 dword_8007A140;

extern G2V12 dword_8007A14C;

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

extern void FreeModelAnim_8002556C(int, int);

extern void PoolDestroy_8003FF7C(void*);

extern char dword_800B1DD0;

extern int dword_800B11DC[];

extern int LoadModelAnim_80025440(int, int, int);

extern void LoadModelAnimSet_80025780(int, int, int);

extern int sub_800AC474(int);

extern int sub_800AC3E4();

extern int sub_800AC38C();

extern unsigned char* sub_800AD58C();

extern unsigned char* sub_800AD604(int);

extern int sub_800AD374(int);

extern int sub_800AD308(int);

extern int sub_800AD288(int, int);

extern int sub_800AD2C8(int, int);

extern int sub_800AD67C(int, int);

extern unsigned char* sub_800AC7B4(int);

extern int sub_800AD73C(int);

typedef struct G2Flags
{
    char pad_0[0x288];
    unsigned int w[2];
} G2Flags;

extern int sub_800AD8BC();

typedef struct G2Save
{
    char pad_0[0x24];
    int f24;
} G2Save;

extern void FreeModelAnimSet_80025884(int);

extern short word_8008D668[2];

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

typedef struct G2ActB
{
    unsigned int f0;
    char pad_4[0xc];
    int f10;
    char pad_14[4];
    unsigned short u18;
    unsigned short u1a;
    short s1c;
    char pad_1e[8];
    short s26;
    char pad_28[0x20];
    int v48[3];
    char pad_54[0x3c];
    MATRIX mats_90[40];
    char pad_590[0x1e8];
    int f778;
} G2ActB;

typedef struct G2Skel_1
{
    int f0;
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

typedef struct G2ActD
{
    unsigned int f0;
    char pad_4[0xc];
    unsigned int f10;
    unsigned int f14;
    char pad_18[4];
    short s1c;
    short s1e;
    char pad_20[6];
    short s26;
    char pad_28[8];
    int f30;
    char pad_34[8];
    int f3c;
    struct_112* model_40;
} G2ActD;

// one animation of a model (struct_112.field_54 points to an array of them)
typedef struct GameAnim
{
    unsigned int frames_0;
    char pad_4[0x18];
} GameAnim;

extern int sub_80019CC4(void* p);


extern short word_8007DC82;

extern short word_8007DC8A;

extern char dword_800B0EF8;

extern void sub_80046A58(void* sk, void* buf, char* pose);

extern void sub_80047E28(void* sk, void* base, char* pose, unsigned int frame, int w, void* buf, char* t);

extern void sub_800459E4(void* bones, void* m, unsigned long* ot, int flags);

extern void sub_8004D288(void* out, void* s, int k);
