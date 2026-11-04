// EVENTFNC.BIN: declarations shared by its source files
// EVENTFNC.BIN
#include "common.h"

#include "funcs.h"

#include "globals.h"
#include "model.h"
#include "engine.h"
#include "minion_init.h"

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



typedef struct EvCtxEventfnc
{
    unsigned int flags_0;
    EvInsEventfnc* start_4;
    EvInsEventfnc* pc_8;
    EvInsEventfnc* ret_C;
    int f10_10;
    int f14_14;
    int f18_18;
    int f1C_1C;
    char pad_20[4];
    int f24_24[6];
    EvVecEventfnc vec3C_3C[5];
    EvVecEventfnc vec78_78[5];
    int fB4_B4;
    int fB8_B8;
    int fBC_BC;
    int fC0_C0;
    unsigned int fC4_C4;
    int fC8_C8;
    int fCC_CC[8];
    int fEC_EC;
    int fF0_F0;
    int fF4_F4;
    int fF8_F8;
    int fFC_FC;
    unsigned short f100_100;
    unsigned short f102_102;
    int f104_104;
    int f108_108;
    char pad_10C[4];
    int* f110_110;
    int f114_114;
    int f118_118;
    int f11C_11C;
    EvEntEventfnc* ent_120;
} EvCtxEventfnc;

typedef struct EvMsgEventfnc
{
    int m0_0;
    int m4_4;
    int m8_8;
    int mC_C;
    int m10_10;
    int m14_14;
    int m18_18;
    int m1C_1C;
    int m20_20;
    int m24_24;
} EvMsgEventfnc;

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

extern EvVecEventfnc* sub_800BBC00(EvCtxEventfnc* c, int a, int b);

extern EvVecEventfnc* sub_800BBC80(EvCtxEventfnc* c, int a, int b);

extern EvVecEventfnc* sub_800BBBA0(int a);

extern int sub_800BB840(EvCtxEventfnc* c, EvMsgEventfnc* m, int a, int b);

extern int sub_800BB990(EvCtxEventfnc* c, EvMsgEventfnc* m, int a, int b);

extern void sub_800BBDA0(int a, int b);

extern int sub_800BBDD8(int a);

extern char eventHeap_80091C10[];

// the low halves of cameraEye_8008D600 (VECTOR camera eye), read with lhu by sub_800BC5C8
extern unsigned short word_8008D600[];

extern int dword_800AEBD8;

extern void sub_800B8940(int* ids);

extern void RequestLoaderModel_800206A0(int a, int b, int c, int d);

extern void StartModelLoader_8002056C(void);




extern int sub_800B82C8(int* p, int* a1, MapMesh* ents, unsigned char* flags, int n);

extern void sub_800B8220(int* p, int a1, int a2, int* a3, int* a4, int* a5);

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

// FindLevantMesh_800B80C8, inlined into sub_800B6DD4
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

extern void sub_800B79E0(MapMesh* m, int* p, int* q, int* tri, int* edge);

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

extern int sub_800A49CC(int a, int b, MapList16* c, EvSpawnEventfnc* d);

extern void sub_800B8568();

extern EventNode* encounterTask_8008D674;

extern void sub_800A170C();

extern void sub_800A1794();

extern void sub_800B844C();

extern unsigned short padPressed_8009194C;

extern int sub_800B8A34(EvCtxEventfnc* c);

extern void sub_800A1974(void);

extern void sub_800A5B54(EvCtxEventfnc* c);

extern int sub_800A7810(int a);

extern void sub_800A8E0C(void);

extern void sub_800A8DEC(void);

extern void sub_800A8E38(void);

extern void sub_800A785C(int a);

extern int sub_800AD16C(int a, int b);

extern int sub_800AD154(int a);

extern void (*dword_800B1D98)(int);

extern int sub_800A59D0(int a);

extern SVECTOR* sub_800BBBD0(int i); // rotation of Levant (0) or a party member

extern short screenOffset_8008D474[2];

extern void UpdateCameraFollow_80037918(void* p);

extern void SetGeomOffset(long ofx, long ofy);

extern short name_80084540[];

extern int sub_800AD0D4(int a);

extern void sub_800AD0F8(int a);

extern void sub_800AD124(int a);

extern int sub_800AD184(int a, int b, int c);

extern int sub_800AD1E0(int a, int b, int c);

extern int sub_800AD73C(int a);

extern int sub_800AD68C(int a);

extern int sub_800AD6E4(int a);

extern int sub_800AD058(int a);

extern int sub_800AD8F4(int a);

extern UnitStatus* sub_800A8C34();





extern EvEntEventfnc* sub_800A5DDC(int a, int b, int c);

extern void sub_800A6830(int a);

extern void sub_800BC7A0(EvCtxEventfnc* c);

extern int sub_800BBE3C(EvCtxEventfnc* c);

extern int sub_800BC2B4(EvCtxEventfnc* c);

extern int XaRequestStop_80043524(void);

extern int ConsumeMsgWindowMark_80034ADC(int a, int b);

extern EvObjEventfnc* sub_800A7A60(int a);

extern void* sub_800A55B0(int a);

extern int useMapStartPos_80091C94;

extern int eventDispatchHalt_8008B540;

extern int sub_800A6D30(int a);

extern void sub_800ADC5C(unsigned short* v, int a);

extern void sub_800ADCEC(unsigned short* v, int a);

extern int forceMapReload_80091C9C;

extern int dword_80091C54;

extern int UsePreloadedArea_80027358(int a);

extern int sub_800A683C(int a);

typedef struct EvWaitEventfnc
{
    int f0_0;
    int f4_4;
    int f8_8;
} EvWaitEventfnc;

extern EvWaitEventfnc dword_800B06B0;

extern int sub_800A5F9C(int a);

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

extern int sub_800A7790(void);

extern int IsWithinDistance_8003B740(int* a, int* b, unsigned int* c);

extern int sub_800A6504(int a, EvVecEventfnc* v);

extern int dword_800B1230;

extern void StartPadVibration_80036528(int a, int b);

extern void StopPadVibration_80036658(int a);

extern int sub_800BBAB0(int i);

extern int sub_800BBAE4(int i);

extern int sub_800BBB18(int* p);

extern int sub_800BBB5C(int* p);

extern int sub_800A8E7C();

extern int sub_800A7CB8(int a);

extern int sub_800A8FE0();

extern int sub_800A7CFC(int a);

extern EvVecEventfnc* sub_800A7940(int a);


extern SVECTOR* sub_800A7984(int a);

extern int dword_800AEBD4;

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

extern void sub_800A67B4(EvCtxEventfnc* c);

extern void CloseMsgWindow_80034A84(int a);

extern int IsMsgWindowWaiting_80034A30(int a);

extern void EnableMsgWindowAdvance_80034A68(int a);

extern int dword_800AEBE8;

extern EvXaEventfnc* dword_800AEBEC;

extern EvVoiceEventfnc* dword_800AEBF0;


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

extern int dword_800AEB7C;

extern EvGfxEventfnc dword_800AEB80;

extern void sub_800A5854(void);

extern void sub_800A5804(int a);

extern void OnEffectFileLoaded_80020F5C(EvGfxArgEventfnc* p, int a);

// sprites / tpages of the TIY loaded by sub_800BC98C
typedef struct
{
    SPRT* sprts_0;
    DR_TPAGE* tpages_4;
} EvTiyEventfnc;
extern EvTiyEventfnc dword_800AEBC0;

extern int dword_800AEBCC[2];

extern void FreeRecordTables_80026DE8(int* a, int b, void* c);

extern void AllocRecordTables_80026D78(int* a, int b, void* c);

extern void LoadRecordTables_80026E74(int a, int b, void* c);

typedef struct TaskEventfnc
{
    unsigned int flags_0;
    int f4_4;
    void (*next_8)();
} TaskEventfnc;

extern void sub_800BCB3C();

extern void sub_800AC604(int a, int b);

extern int sub_800AC768(void);

extern void sub_800AC6A8(int a);

extern int IsSceneFadeDone_8001AB94(void);

extern void StartSceneDarken_8001AAA8(int a);

extern int sub_800A8EC4(int* p);

extern void sub_800A7720();

extern short word_8008B858;

extern short pendingArea_8008B860;

extern int dword_80091C8C;

extern void sub_800B8BE8();
extern void sub_800B9B98();
extern void sub_800BA82C();
extern void sub_800BAB5C();
extern void sub_800BB27C();
extern int sub_800B89A8();
extern int sub_800B89C0();
extern int sub_800B89F4();
extern int sub_800B8CB0();
extern int sub_800B8D08();
extern int sub_800B8DDC();
extern int sub_800B8E9C();
extern int sub_800B8F14();
extern int sub_800B8F44();
extern int sub_800B8F88();
extern int sub_800B8FB8();
extern int sub_800B9020();
extern int sub_800B9110();
extern int sub_800B91CC();
extern int sub_800B9218();
extern int sub_800B9260();
extern int sub_800B93A8();
extern int sub_800B942C();
extern int sub_800B95BC();
extern int sub_800B962C();
extern int sub_800B96D8();
extern int sub_800B9720();
extern int sub_800B9768();
extern int sub_800B97B0();
extern int sub_800B97F8();
extern int sub_800B9840();
extern int sub_800B98C4();
extern int sub_800B990C();
extern int sub_800B9954();
extern int sub_800B99D8();
extern int sub_800B9A20();
extern int sub_800B9A68();
extern int sub_800B9AB4();
extern int sub_800B9B00();
extern int sub_800B9B4C();
extern int sub_800B9C5C();
extern int sub_800B9CC0();
extern int sub_800B9D08();
extern int sub_800B9D50();
extern int sub_800B9DE0();
extern int sub_800B9E48();
extern int sub_800B9EB0();
extern int sub_800B9EDC();
extern int sub_800B9F0C();
extern int sub_800B9F5C();
extern int sub_800B9F84();
extern int sub_800B9FB4();
extern int sub_800B9FD8();
extern int sub_800BA020();
extern int sub_800BA1DC();
extern int sub_800BA238();
extern int sub_800BA28C();
extern int sub_800BA2E8();
extern int sub_800BA338();
extern int sub_800BA40C();
extern int sub_800BA45C();
extern int sub_800BA4F0();
extern int sub_800BA554();
extern int sub_800BA5CC();
extern int sub_800BA678();
extern int sub_800BA6D0();
extern int sub_800BA714();
extern int sub_800BA7A4();
extern int sub_800BA880();
extern int sub_800BA8AC();
extern int sub_800BA930();
extern int sub_800BA9E4();
extern int sub_800BAA6C();
extern int sub_800BAAC0();
extern int sub_800BAB14();
extern int sub_800BABB0();
extern int sub_800BAC60();
extern int sub_800BACE0();
extern int sub_800BAD3C();
extern int sub_800BAD88();
extern int sub_800BADF8();
extern int sub_800BAEBC();
extern int sub_800BAF08();
extern int sub_800BAF68();
extern int sub_800BAFAC();
extern int sub_800BB180();
extern int sub_800BB214();
extern int sub_800BB45C();
extern int sub_800BB4A4();
extern int sub_800BB7D8();

extern int dword_800B6D00;
extern const char aAssertionFaile_800B6D04[];
extern const char aColiC_800B6D2C[8];
extern const int dword_800B6D98[10];
extern int (*eventFuncs_800BCDBC[157])();
