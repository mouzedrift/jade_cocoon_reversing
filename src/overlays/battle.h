// BATTLE.BIN: declarations shared by its source files
// BATTLE.BIN
#include "common.h"

#include "funcs.h"

#include "globals.h"

#include "actor.h"

extern unsigned char dword_800C8B30;

extern int sub_800A2AB4();

extern void sub_80018430(int a);

extern int sub_800AD8E4();

extern void InterpolateWindowRect_8004196C(void* a0, void* a1, int a2, int a3, int a4);

extern void AddDrawAreaPrim_8003326C();

extern void AddClipDrawAreaPrim_80033308();

extern unsigned short padPressed_8009194C;

extern int MeasureTextWidth_8003E4C8();

extern int dword_800C9E38;

extern unsigned char dword_800C9E68;

extern unsigned char dword_800C9E40;

extern unsigned char dword_800C9E72[];

extern unsigned char dword_800C9E80[];

extern unsigned char dword_800C9E4A;

extern int dword_800C9E4C;

extern int dword_800C9E78;

extern void sub_8004D1EC(int a0, int a1, int a2, int a3, int a4, int a5, int a6);

extern char stru_8008D534[];

extern unsigned char dword_800C9E49;

typedef struct BatMenu_a
{
    short f0;
    short f2;
    unsigned short count_4;
    unsigned short flags_6;
    short cursor_8;
    short scroll_A;
} BatMenu_a; // same layout as the exe's MenuCursor

extern BatMenu_a dword_800C92D8[1];

extern BatMenu_a dword_800C92E4[1];

extern BatMenu_a dword_800C92F0[1];

extern BatMenu_a dword_800C9308[1];

extern BatMenu_a dword_800C9314[1];

extern BatMenu_a dword_800C9320[1];

extern BatMenu_a dword_800C932C[1];

extern int dword_800C8B34;

extern int dword_800C9DD0[];

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
    int f0;
    int f4;
    BatCmd_a* f8;
    int fC;
    int f10;
    unsigned char* f14;
    int f18;
    int f1C;
} BatTask;

extern BatCmd_a dword_800C9E58;

extern void sub_800C6AFC(BatTask* t, int a, int b);

extern unsigned char dword_800C9E54;

extern int dword_800C9E3C;

extern unsigned char dword_800C9E51;

extern unsigned char dword_800C9E48;

extern unsigned char dword_800C9E50;

extern int dword_800C9E7C;

extern int sub_800BE364();

extern void sub_800BE3C0();

extern int sub_800BEA94();

typedef struct BatMin_a
{
    unsigned int f0;
    int f4;
    short h8;
} BatMin_a;

extern int sub_800BC6CC();

extern void FadeOutSeqSlot_800313C8(int);

extern EventNode* dword_8008D624;

extern char dword_800C9D82;

extern char dword_800C9D83;

extern char dword_800C9D56;

extern int dword_800C9C58;

extern int sub_800A5354();

extern int sub_800BAAD8();

extern void sub_800A1F80();

extern void sub_800A8D0C();

extern void sub_800A096C();

extern void sub_800BAC4C();

extern char dword_800C912C[];

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

extern int dword_800ADE78;

extern int dword_80091C74;

extern int dword_8007DC74;

extern int dword_800C9188;

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

extern void ReviveOneHp_80011CF4();

extern void SsSepSetDecrescendo();

extern void sub_800BA848();

extern void sub_800BA4F4();

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

extern short dword_800C9C68[];

extern unsigned char dword_800C9C82;

extern unsigned char dword_800C9C99;

extern short dword_800C9D38[];

extern short dword_800C9D48[];

extern char dword_800C9CBC[];

extern int dword_800C9D58[];

extern int dword_800C9CA0[];

extern short dword_800C9D78;

extern short dword_800C9D80;

extern short dword_800C9C7E;

extern short dword_800C9C80;

extern int dword_800C9D90;

extern short dword_800C9DBC;

extern short dword_800C9DC0[];

extern short dword_800C9D8C[2];

extern EventNode* dword_8008B4C0;

extern int dword_800ADE88;

extern int eventDispatchHalt_8008B540;

extern int dword_80083BD0;

typedef struct BatRow_a
{
    int a;
    unsigned short b;
    short c;
    int d;
    int e;
} BatRow_a;

extern BatRow_a dword_800C8EAC[];

extern int sub_80034AB8();

extern int sub_800349B4();

extern void sub_80034A84();

extern void sub_8001E28C();

extern void sub_800A2924();

extern void ClearStatus_80011C30();

extern void RecoverQuarterHpMp_80011C44();

extern void memset();

extern void LoadEffectFile_80020DDC();

extern void SetFadeMode_8001C19C();

extern void sub_800A2AE8();

extern void PlaySeqSlot_80031160();

extern void sub_80018A4C();

extern int LoadOverlay_80020BF8();

extern void sub_8001AAF4();

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

extern char levantStatus_8008BD38[];

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

extern BatPair_a dword_800C9DA0[];

extern int* dword_8008B568;

extern int* dword_8008B564;

extern EventNode* dword_8008D4B0;

extern EventNode* dword_8008D63C;

extern EventNode* dword_8008D778;

extern int dword_800C9D74;

extern int dword_800C9D7C;

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


typedef struct BatLevant_a
{
    int pos_0[3];
    short fC;
    short angle_E;
} BatLevant_a;

extern BatLevant_a levantPos_8008BD18;

extern unsigned int dword_800B1228;

typedef struct BatCtx_a
{
    Actor* obj;
    int f4;
    int f8;
    int fc;
    int f10;
} BatCtx_a;

extern BatCtx_a dword_800C9190;

extern int dword_800C918C;

extern signed char dword_800C9D84;

extern short dword_800C9D94;

extern short dword_800C9D9A;

extern short dword_800C9D98[];

extern int dword_800C9170;

extern int dword_800C9174[3];

extern char dword_800C9DFC;

extern char dword_800C9DFD;

extern BatCmd_a dword_800C9C88;

extern unsigned char dword_800C9C7C;

extern unsigned char dword_800C9C98;

extern int dword_800C8B54[];

extern char dword_800C8B38[];

extern BatCmd_a dword_800C9CC8[7];

extern int sub_8001AB94(void*);

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

extern int sub_800C0F78(int);

extern void StartScreenFlash_8001C02C(void*);

extern void sub_8001DB00(Actor*, int, int);

extern void sub_80018E5C(Actor*, int);

extern void sub_80018EBC(Actor*, int);

extern int sub_8001E1DC(void*);

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

extern int dword_80091C9C;

extern short sinTable_80084540[];

extern int sub_800A1E48(void);

extern int sub_800A1E68(void);

extern int LoadSeqSlotSound_800303E8();

extern int IsSoundTaskReady_80030688();

extern void sub_80037748();

extern void LoadUiTiy_8002BF74();

extern void sub_800BFB80();

extern int sub_800B4200(int* p);

extern int sub_800B41D0(int* p);

extern int* sub_800B41A8(int* p);

extern int* dword_800C9C78;

extern void sub_800BB100();

extern void sub_800BB314();

extern void sub_800BB74C();

extern void sub_800BB7D4();

extern void sub_800BB860();

extern BatV12_a* sub_800BC5EC();

extern void ApplyBattleCommand_800BEBB8();

extern void sub_80037828(int a, int b, int c);

extern void sub_800BDB4C();

extern void sub_800A8A30();

extern void sub_800A2684();

extern void sub_800A8C0C(int b);

extern void sub_800A2760(BatCmd_a* p, int b);

extern void sub_800377B4(int a, int b, int c);

extern void sub_80037BFC(int a);

extern void PlaySfx_80031494(int id);

extern void StartPadVibration_80036528(int pad, int kind);

extern void sub_800AD944(int a);

extern void sub_800AD1E0(int a, int b, int c);

extern void sub_800A2898(int a);

extern void sub_800A284C(int a);

extern void sub_80039ED8(int a);

extern void sub_800127D0(int a0, int a1, int a2, int a3);

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

extern void sub_80037BFC(int a);

extern void StartPadVibration_80036528(int a, int b);

extern unsigned char dword_800C9134[];

typedef struct BatUnit_a
{
    unsigned int flags_0;
    int f4;
    short hp_8;
    short hpLoss_A;
    short mp_C;
    short mpLoss_E;
    char pad10[0x34];
    unsigned char f44;
} BatUnit_a;


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

extern void sub_80012BB0(BatUnit_a* a, BatUnit_a* b, BatCmd_a* c, BatResult_a* r);

extern void sub_800B4390(BatUnit_a* a, BatUnit_a* b, BatCmd_a* c, BatResult_a* r, int* e);

extern void sub_800BF9F0(int a);

extern void sub_800127D0(int a0, int a1, int a2, int a3);

typedef struct BatXY_a
{
    short x;
    short y;
} BatXY_a;

extern int dword_800C9DF8;

extern int dword_800C9E24;

extern BatXY_a dword_800C9140[];

extern char* dword_800C9E28[];

extern BatXY_a dword_800C9E18[];

extern EventEntry* dword_800C9E08[];

extern void sub_800BFDEC();

extern void sub_800C0074();

extern unsigned int dword_800C9E00;

extern int sub_800C0904(unsigned char* p);

extern int* CreateActor_8001D45C(int a0);

extern int sub_80010A44();

extern void sub_80019B14(int a, int b, int c);

extern int dword_80079140;

extern EventNode* dword_8008D60C;

extern void sub_800C17EC();

// one sprite of an effect frame (0x1C bytes)
typedef struct BatFxElem_a
{
    int f0;
    int f4;
    int f8;
    short size_C[2];
    short f10[4];
    int f18;
} BatFxElem_a;

// sprite effect animation (0x34 bytes, the table at effectFile_80091BD0[0x20 / 4])
typedef struct BatFxAnim_a
{
    int count_0; // frames
    unsigned char* counts_4; // sprites per frame
    BatFxElem_a** frames_8;
    int state_C[10];
} BatFxAnim_a;

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
    BatFxAnim_a* anim_3C;
    int* target_40;
    int* offset_44;
} BatSpark_a;

extern char dword_800795D4[];

extern int* sub_80044010();

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
    void* obj_3C; // BatClip_a or a model
} BatShard_a;

extern void PlaySfx_80031494(int id);

extern int sub_80020F00(void* p, int a, int b);

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
    BatFxAnim_a* anim_88;
    struct BatClip_a* clip_8C;
} BatTrail_a;

extern void sub_80044D0C();

extern void sub_800459E4();

extern char dword_800C91A4[];

extern int sub_80020F00(void* p, int a, int b);

extern void sub_800C33E4();

typedef struct BatKey_a
{
    short model_0;
    short alpha_2;
    int x_4;
    int y_8;
    int z_C;
    short rot_10[3];
    short pad16;
    int f18[3];
    int mode_24;
} BatKey_a;

typedef struct BatClip_a
{
    int f0;
    char* models_4;
    int f8;
    int fC;
    int count_10;
    int frames_14;
    BatKey_a* keys_18;
} BatClip_a;

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
    BatClip_a* clip_88;
} BatAnim_a;

extern void sub_80045E48();

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
    int* f88;
    char pad8C[8];
    int* f94;
    int idx_98;
    char pad9C[4];
    int* scale_A0;
} BatGlow_a;

extern char dword_800795D4[];

extern void sub_800C3B50(int* p, int id);

extern void sub_8003A6C4();

extern void sub_80021804(int* p, int heap);

extern void free3_8003FC6C(void* p);

extern void sub_800C4090(int a0, int a1, int c, int a3);


extern void sub_8003A6C4();

extern void sub_80021804(int* p, int heap);

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
    BatClip_a* clip_88;
    char pad8C[8];
    int* model_94; // malloc'd copy of the clip's first model
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

extern BatScene_a* dword_8008B4A4;

extern int DistanceSquared3D_8003B80C(int* a, int* b);

extern int dword_8008D680[3];

extern short dword_8008D418[3];

extern int dword_8008D3F0;

extern int dword_8008D3F0;

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

extern EventNode* dword_8008D468;

extern unsigned char dword_800C9E4B;

extern unsigned char dword_800C9E70;

extern void sub_800C71A0();

extern void BattleMenuTask_800C8A08();

extern int sub_800AD308(int a);

extern int CountMagicBits_8001AE54(char* h);

extern int dword_800C9628[];

extern int dword_800C9640;

extern char dword_800C9378[];

extern char dword_800C9384[];

extern char dword_800C9388[];

extern char dword_800C938C[];

extern char dword_800C93A4[];

extern char dword_800C93D4[];

extern char* dword_800C93B8[];

extern unsigned short dword_800C946C;

extern unsigned short dword_800C94A4;

extern unsigned short dword_800C9514;

extern char* dword_800C9E6C;

extern char* dword_800C9338[];

typedef struct BatUseQ_a
{
    short f0;
    short f2;
    short f4;
    short f6;
    short f8;
    short fA;
    int minion_C;
} BatUseQ_a;

typedef struct BatTgtQ_a
{
    short f0;
    short f2;
    short f4;
    short f6;
} BatTgtQ_a;

extern char* dword_800C9E44;

extern char* dword_800C9E6C;

extern unsigned short dword_800C9E5C;

extern int dword_800C93A0;

extern int dword_800C9380;

extern int dword_800C939C;

extern int dword_800C9398;

extern int dword_800C9390;

extern int dword_800C937C;

extern int GetMenuCursorIndex_8003DA54(void*);

extern int CheckItemUsable_80033AFC(BatUseQ_a* q);

extern int CheckMagicCastable_80033C08(BatUseQ_a* q);

extern int sub_80033C98(BatUseQ_a* q);

extern int sub_80033DF4(BatTgtQ_a* q);

extern int sub_80034068(BatTgtQ_a* q);

extern unsigned char sub_800C78D0();

extern unsigned char dword_800C9648[];

extern int GetMenuCursorIndex_8003DA54(void*);

extern unsigned char dword_800C9C7C;

extern unsigned char dword_800C9660[];

extern unsigned char dword_800C9654[];

extern int dword_800C96A4[];

extern unsigned int dword_800C9E64;

extern int sub_8001CE8C(int a);

extern int sub_80031B30(int a);

extern int sub_80031B0C(int a, int b);

extern int FindNthMagicBit_8001AEC0(char* h, int n);

extern int sub_8001ACE4(int a);

struct BatState
{
    int f0;
    int f4;
    int f8;
    int fC;
};

extern struct BatState dword_800C9630;

extern short dword_800C92E0;

extern unsigned char dword_800C9E54;

extern unsigned char dword_800C9C99;

typedef struct BatWin_a
{
    short x;
    short y;
    short w;
    short h;
    short c;
    short d;
    int p;
} BatWin_a;

typedef struct BatMenuItem_a
{
    int* text;
    int f4;
} BatMenuItem_a;

extern int dword_800C96C8[][4];

extern int dword_800C9978[][4];

extern char dword_800C9B58[];

extern unsigned short dword_800C9E5C;

extern unsigned short dword_800C968C[][2];

extern int dword_800C9674[];

extern int IsCircleHeldP1_8003D480(void);

extern int GetMenuCursorIndex_8003DA54();

extern void sub_8002C670(void* a0, int a1, void* a2, int a3, int a4);

extern int sub_8002D250(void* a0, int a1, int a2, int a3);

extern void DrawMenuWindows_8002A5A4(void* a0);

extern void sub_8002C728(void* a0);

extern void sub_8002CE28(void* a0, int a1);

extern int sub_80031A04(int a0, int a1);

extern void sub_8002CAC8(void* a0, void* a1);

extern int FindNthMagicBit_8001AEC0();

extern void DrawButtonHelpBar_8002B004(int a0, int a1, int a2);

extern void sub_800C8828(int a);

extern char* dword_800C9E44;

extern short dword_800C9180;

extern short dword_800C9182;

extern short dword_800C9180;

extern short dword_800C9182;

extern int sub_80013228(BatUnit_a* a, BatUnit_a* b, BatCmd_a* c, BatResult_a* r);

extern unsigned char dword_800C9E72[];

extern int dword_800C9E3C;

extern unsigned char dword_800C9E51;

extern unsigned char dword_800C9E48;

extern unsigned char dword_800C9E50;

extern int dword_800C9E7C;

extern unsigned int dword_800C9E64;

extern char* dword_800C9E44;

extern void (*dword_800C966C[])(EventEntry* t, int a);

extern short dword_800C9180;

extern short dword_800C9182;

extern void UpdateMenuCursor_8003D794();

extern void sub_800C83B0();
