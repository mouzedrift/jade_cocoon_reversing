#include "maps/map.h"

void FtgAnim_800B22F4(MapEnt* ent);
void MinionInit_800B2430(MapEnt* ent);
void MapInit_800B2768(int phase);
void CameraOrbitInit_800B27D4(MapEnt* ent);
void CameraOrbit_800B280C(MapEnt* ent);
void FtgAnimInit_800B289C(MapEnt* ent);
void MinionIdle_800B28D4(MapEnt* ent);
int SetLevantAnimSet_800B28DC(void);
void StartMapTask_800B28F0(void);
void MapTaskLoad_800B2920(EventEntry* entry, int* st);
void MapTask_800B29B8(EventEntry* entry, int* st);
int LeaveArea_800B2A70(MapEvent* ev, int area);
int EnterArea_800B2B8C(MapEvent* ev, int area, int prev);
void RequestModels_800B2C94(MapEvent* ev);
int AddEntity_800B2D64(void* ev);
int MinionF_800B2E90(void);
int MinionF_800B2E98(void);
void EntityTask_800B2EA0(EventEntry* entry, MapEnt* ent);

extern const int unknown_800B22C0[1];
extern const char str_800B22C4[20];
extern const char str_800B22D8[12];
extern const char str_800B22E4[16];
extern short bones_800B2F20[100];
extern int data_800B2FE8[3];
extern SVECTOR boneScale_800B2FF4[24];
extern int anim_800B30B4[19];
extern int anim_800B3100[19];
extern ActorScriptCmd anim_800B314C[4];
extern ActorScriptCmd anim_800B317C[4];
extern ActorScriptCmd anim_800B31AC[4];
extern ActorScriptCmd* script_800B31DC[34];
extern int data_800B3264[3];
extern MapActorModel model_800B3270;
extern int data_800B329C[3];
extern SVECTOR boneScale_800B32A8[25];
extern int anim_800B3370[19];
extern ActorScriptCmd anim_800B33BC[5];
extern ActorScriptCmd anim_800B33F8[5];
extern ActorScriptCmd* script_800B3434[32];
extern MapActorModel model_800B34B4;
extern int data_800B34E0[12];
extern MapActorModel model_800B3510;
extern MapVoice voices_800B353C[8];
extern int data_800B357C[2];
extern int data_800B3584[4];
extern int data_800B3594[18];
extern int data_800B35DC[9];
extern int species_800B3600[9];
extern SVECTOR boneScale_800B3624[6];
extern MapFtgAnim ftgAnim_800B3654;
extern MapEvent event_800B3660[2];
extern MapInstr script_800B3688[80];
extern MapMinion minion_800B3B88;
extern MapMinion minion_800B3BAC;
extern MapMinion minion_800B3BD0;
extern MapEvent events_800B3BF4[6];
extern short bones_800B3C6C[92];
extern int scale_800B3D24[3];

short bones_800B2F20[100] = {
    0, 0, 0, 0x46, 1, 1, 1, 0,
    2, 0x102, 2, 0xB, 3, 0x203, 3, 0xB,
    4, 0x304, 4, 0xB, 5, 0x405, 5, 0xB,
    3, 0x206, 6, 0xB, 4, 0x307, 7, 0xB,
    5, 0x408, 8, 0xB, 3, 0x209, 9, 0,
    4, 0x30A, 0xA, 0xB, 3, 0x212, 0x12, 0xB,
    3, 0x213, 0x13, 0xB, 3, 0x214, 0x14, 0xB,
    3, 0x215, 0x15, 0xB, 3, 0x216, 0x16, 0xB,
    4, 0x317, 0x17, 0xB, 2, 0x10B, 0xB, 0xB,
    3, 0x20C, 0xC, 0xB, 4, 0x30D, 0xD, 0xB,
    5, 0x40E, 0xE, 0xB, 3, 0x20F, 0xF, 0xB,
    4, 0x310, 0x10, 0xB, 5, 0x411, 0x11, 0xB,
    -1, -1, -1, -1,
};
int data_800B2FE8[3] = {
    0x1000, 0x1000, 0x1000,
};
SVECTOR boneScale_800B2FF4[24] = {
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
};
int anim_800B30B4[19] = {
    -0x1FDF4, 0x1A0000, -0x1FEF3, -0x1FEF1, -0xFDF9, 0x1000000, -0xFEFD, -0xFDFF,
    0x1A0000, -0x1FDEC, 0x40000000, -0xFEF8, -0xFDF5, 0, -0x1FEF0, -0x1FEEF,
    -0xFDF2, 0x1A0000, -0x1FF00,
};
int anim_800B3100[19] = {
    -0x1FDF4, 0x1B0000, -0x1FEF3, -0x1FEF1, -0xFDF5, 0x10000, -0xFDFA, 0x1000000,
    -0xFDFF, 0x1B0000, -0x1FDEC, 0x40000000, -0xFEF8, -0x1FEF0, -0xFDFF, 0x40000,
    -0xFDF2, 0x1B0000, -0x1FF00,
};
ActorScriptCmd anim_800B314C[4] = {
    { 0xF, 1, -2, 0x20B, -1, 0, 1 },
    { 6, 2, -1, 0, 0x100, 0x201, -1 },
    { 0, 0, 1, 0x214, -2, 0, 0x4000 },
    { 8, 1, -1, 0x110, -2, 0x100, -2 },
};
ActorScriptCmd anim_800B317C[4] = {
    { 0xF, 1, -2, 0x207, -1, 0, 0x100 },
    { 1, 2, -1, 0, 1, 0x214, -2 },
    { 0, 0, 0x4000, 0x108, -1, 0x20B, -1 },
    { 0, 0, 0, 0x110, -2, 0x100, -2 },
};
ActorScriptCmd anim_800B31AC[4] = {
    { 0xC, 2, -2, 0, 0x15, 0x10D, -2 },
    { 0xF, 1, -2, 0x103, -1, 0x201, -1 },
    { 0, 0, 0x15, 0x115, -2, 0x217, -2 },
    { 0, 0, 0x3C, 0x110, -2, 0x100, -2 },
};
ActorScriptCmd* script_800B31DC[34] = {
    (void*)&commandScriptData_80079754, (void*)((char*)&commandScriptData_80079754 + 0xC), (void*)((char*)&commandScriptData_80079754 + 0x1C), (void*)((char*)&commandScriptData_80079754 + 0x54), (void*)((char*)&commandScriptData_80079754 + 0x8C), (void*)((char*)&commandScriptData_80079754 + 0xC4), (void*)((char*)&commandScriptData_80079754 + 0xFC), (void*)((char*)&commandScriptData_80079754 + 0x134),
    (void*)((char*)&commandScriptData_80079754 + 0x16C), (void*)((char*)&commandScriptData_80079754 + 0x1A4), (void*)((char*)&commandScriptData_80079754 + 0x200), (void*)((char*)&commandScriptData_80079754 + 0x238), (void*)((char*)&commandScriptData_80079754 + 0x270), (void*)((char*)&commandScriptData_80079754 + 0x2A8), (void*)((char*)&commandScriptData_80079A2C + 0x4), (void*)((char*)&commandScriptData_80079A2C + 0x1C),
    anim_800B31AC, (ActorScriptCmd*)anim_800B30B4, (ActorScriptCmd*)anim_800B3100, (void*)((char*)&commandScriptData_80079B44 + 0x8), (void*)((char*)&commandScriptData_80079B44 + 0x1C), (void*)((char*)&commandScriptData_80079B6C + 0x8), (void*)((char*)&commandScriptData_80079B6C + 0x20), (void*)((char*)&commandScriptData_80079B6C + 0x44),
    0, 0, 0, 0, 0, 0, 0, 0,
    anim_800B314C, anim_800B317C,
};
int data_800B3264[3] = {
    8, 0x17, -1,
};
MapActorModel model_800B3270 = { str_800B22C4, 0x63, bones_800B2F20, data_800B2FE8, boneScale_800B2FF4, data_800B3264, 4, script_800B31DC, 0, 0x800000, 0, 1 };
int data_800B329C[3] = {
    0x1400, 0x1400, 0x1400,
};
SVECTOR boneScale_800B32A8[25] = {
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
    { 0x1000, 0x1000, 0x1000, 1 },
};
int anim_800B3370[19] = {
    -0x1FDF4, 0x150000, -0x1FEF3, -0x1FEF1, -0xFDF9, 0x1000000, -0xFEFD, -0xFDFF,
    0x150000, -0x1FDEC, 0x40000000, -0xFEF8, -0xFDF5, 0, -0x1FEEF, -0xFDF2,
    0x150000, -0x1FEF0, -0x1FF00,
};
ActorScriptCmd anim_800B33BC[5] = {
    { 0xF, 1, -2, 0x20B, -1, 0, 1 },
    { 6, 2, -1, 0, 0x100, 0x204, -1 },
    { 0, 0, 1, 0x102, -1, 0x201, -1 },
    { 0, 0, 4, 0x214, -2, 0, 0x4000 },
    { 8, 1, -1, 0x110, -2, 0x100, -2 },
};
ActorScriptCmd anim_800B33F8[5] = {
    { 0xF, 1, -2, 0x207, -1, 0, 0x100 },
    { 4, 2, -1, 0, 1, 0x102, -1 },
    { 1, 2, -1, 0, 4, 0x214, -2 },
    { 0, 0, 0x4000, 0x108, -1, 0x20B, -1 },
    { 0, 0, 0, 0x110, -2, 0x100, -2 },
};
ActorScriptCmd* script_800B3434[32] = {
    (void*)&commandScriptData_80079754, (void*)((char*)&commandScriptData_80079754 + 0xC), (void*)((char*)&commandScriptData_80079754 + 0x1C), (void*)((char*)&commandScriptData_80079754 + 0x54), (void*)((char*)&commandScriptData_80079754 + 0x8C), (void*)((char*)&commandScriptData_80079754 + 0xC4), (void*)((char*)&commandScriptData_80079754 + 0xFC), (void*)((char*)&commandScriptData_80079754 + 0x134),
    (void*)((char*)&commandScriptData_80079754 + 0x16C), (void*)((char*)&commandScriptData_80079754 + 0x1A4), (void*)((char*)&commandScriptData_80079754 + 0x200), (void*)((char*)&commandScriptData_80079754 + 0x238), (void*)((char*)&commandScriptData_80079754 + 0x270), (void*)((char*)&commandScriptData_80079754 + 0x2A8), (void*)((char*)&commandScriptData_80079A2C + 0x4), (void*)((char*)&commandScriptData_80079A2C + 0x1C),
    (ActorScriptCmd*)anim_800B3370, anim_800B33BC, anim_800B33F8, (void*)((char*)&commandScriptData_80079B44 + 0x8), (void*)((char*)&commandScriptData_80079B44 + 0x1C), (void*)((char*)&commandScriptData_80079B6C + 0x8), (void*)((char*)&commandScriptData_80079B6C + 0x20), (void*)((char*)&commandScriptData_80079B6C + 0x44),
    (void*)((char*)&commandScriptData_80079C04 + 0x14), (void*)((char*)&commandScriptData_80079C04 + 0x64), (void*)((char*)&commandScriptData_80079C04 + 0x84), (void*)((char*)&commandScriptData_80079CE0 + 0x1C), (void*)((char*)&commandScriptData_80079CE0 + 0x6C), (void*)((char*)&commandScriptData_80079DE4 + 0x14), (void*)((char*)&commandScriptData_80079DE4 + 0xB0), (void*)((char*)&commandScriptData_80079F50 + 0x14),
};
MapActorModel model_800B34B4 = { str_800B22D8, 0x11, (void*)&defaultBones_80079140, data_800B329C, boneScale_800B32A8, 0, 4, script_800B3434, 0x20002, 0x800002, 0, 0 };
int data_800B34E0[12] = {
    -0x1FEF1, -0xFDF5, 0x10000, -0xFDFA, 0x1000000, -0xFDFF, 0x10000, -0x1FDEC,
    0x40000000, -0xFEF8, -0x1FEF0, -0x1FF00,
};
MapActorModel model_800B3510 = { str_800B22E4, 0x29, (void*)&defaultBones_80079140, 0, 0, 0, 4, 0, 0x20002, 0x800002, 0, 0 };
MapVoice voices_800B353C[8] = {
    { 0, 0, { 0x13, 0x3F4, 0xE } },
    { 0, 1, { 0x1F, 0x3F5, 0x1C } },
    { 0, 2, { 0x19, 0x3F7, 0x1E } },
    { 1, 0, { 0x1D, 0x3F8, 0x17 } },
    { 1, 1, { 6, 0x3F9, 0x1A } },
    { 2, 0, { 7, 0x3F9, 0x1E } },
    { 2, 1, { 0xF, 0x3F9, 0x23 } },
    { 0, 0, { -1, 0, 0 } },
};
int data_800B357C[2] = {
    0x15C0006, 0x56,
};
int data_800B3584[4] = {
    -0x2BC, 0xABE, -0xD2F, 0,
};
int data_800B3594[18] = {
    0, 1, 0, 0, 0, 0, 1, 2,
    5, 0x29, 0x50000000, 3, 0x2A, 0x24000000, 3, 0xD3,
    0, 0,
};
int data_800B35DC[9] = {
    1, 1, 0, 0, 0, 0, 3, 5,
    5,
};
int species_800B3600[9] = {
    0xC, 0, 0, 0xD3, 0, 0, 0xD3, 0,
    0,
};
SVECTOR boneScale_800B3624[6] = {
    { -0x10B, -0x126, 0, 0 },
    { -0x164, -0x1B2, 0, 0 },
    { -0x13B, -0xE0, 0, 0 },
    { -0x12A, -0xF2, 0, 0 },
    { -0x13B, -0xAF, 0, 0 },
    { -0xAD, -0x3B, 0, 0 },
};
MapFtgAnim ftgAnim_800B3654 = { 0, 0xF, 0x800, 0, boneScale_800B3624 };
MapEvent event_800B3660[2] = {
    { -1, 0xD, &ftgAnim_800B3654, 4, { FtgAnimInit_800B289C } },
    { -1, 0xD, 0, 8, { CameraOrbitInit_800B27D4 } },
};
MapInstr script_800B3688[80] = {
    { 5, 0, 0, 0 },
    { 7, 0, 0xF, 0 },
    { 0x67, 0x12, 1, 0 },
    { 0x67, 0xB, 0, 0 },
    { 0x67, 1, 0, 0 },
    { 0x13, 0, 0, MAP_REF(data_800B3584) },
    { 0x1B, 0, 0, 0 },
    { 0x48, 0, 0x188, 5 },
    { 0x5F, 0x1800, 1, 0 },
    { 0x67, 2, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x49, 0, 0x1870189, 1 },
    { 0x67, 0x10, 0, MAP_REF(data_800B357C) },
    { 0xC, 0, 0x348, 0 },
    { 0x67, 3, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x5F, 0x1000, 1, 0 },
    { 0x67, 0xA, 0, 0 },
    { 0x11, 0, 0, MAP_REF(event_800B3660) },
    { 0x67, 3, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0xD, 0, 1, 0 },
    { 0x1B, 0, 1, 0 },
    { 0x49, 0, 0x7A007B, 5 },
    { 0x67, 2, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x38, 1, 0, 0 },
    { 0x42, 0, 0, 0 },
    { 0x42, 0, 1, 0 },
    { 0x42, 0, 2, 0 },
    { 0x46, 3, 0, MAP_REF(data_800B34E0) },
    { 0x3F, 0, 0, 0 },
    { 0xD, 0, 8, 0 },
    { 0x45, 0, 1, 0 },
    { 0x4D, 0, 0, MAP_REF(SetLevantAnimSet_800B28DC) },
    { 0x65, 0, 0, MAP_REF(data_800B35DC) },
    { 0x66, 0, 0, 0 },
    { 0xA, 0, 0x10, 0 },
    { 0xA, 0, 0x20, 0 },
    { 9, 0, 0x10, 0 },
    { 0x38, 1, 0, 1 },
    { 0x42, 0, 0, 0 },
    { 0x42, 0, 1, 0 },
    { 0x46, 1, 0, MAP_REF(anim_800B314C) },
    { 0x3F, 0, 0, 0 },
    { 0xD, 0, 2, 0 },
    { 0x45, 0, 1, 0 },
    { 0x65, 0, 0, MAP_REF(data_800B3594) },
    { 0x2C, 0, 1, 0 },
    { 0x1A, 2, 1, 0 },
    { 0x48, 1, 0x1D, 5 },
    { 0x48, 0, 0x191, 6 },
    { 0x67, 2, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x38, 1, 0, 2 },
    { 0x3F, 0, 0, 0 },
    { 0x46, 1, 0, MAP_REF(anim_800B317C) },
    { 0xD, 0, 2, 0 },
    { 0xA, 0, 0xFF, 0 },
    { 9, 0, 0x20, 0 },
    { 0x2C, 0, 1, 0 },
    { 0x48, 0, 0x191, 6 },
    { 0x67, 2, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x38, 1, 0, 2 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x1E001D, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x24001D, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0xFF, 0 },
    { 9, 0, 0xFF, 0 },
    { 0x67, 0xC, 0xFF00, 0 },
    { 0x67, 3, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x67, 0x12, 0, 0 },
    { 8, 0, 0xF, 0 },
    { 4, 0, 0, 0 },
    { 0x4F, 0, 1, 0 },
    { 3, 0, 0, 0 },
};
MapMinion minion_800B3B88 = { &model_800B3270, 0, { -0x271, 0, -0xBB8 }, 0x871, 0, 1, 2, 3 };
MapMinion minion_800B3BAC = { &model_800B34B4, 0, { -0x271, 0, -0xBB8 }, 0x871, 0, 1, -1, 3 };
MapMinion minion_800B3BD0 = { &model_800B3510, (MapMinionSpecies*)species_800B3600, { -0x271, 0, -0xBB8 }, 0x871, 0, 1, -1, 3 };
MapEvent events_800B3BF4[6] = {
    { -1, 0xF, &minion_800B3B88, 0x14, { MinionInit_800B2430 } },
    { -1, 0xF, &minion_800B3BAC, 0x14, { MinionInit_800B2430 } },
    { -1, 0xF, &minion_800B3BD0, 0x14, { MinionInit_800B2430 } },
    { -1, 8, script_800B3688, 0, { 0 } },
    { -1, 0xB, voices_800B353C, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
short bones_800B3C6C[92] = {
    0, 0, 0, 0x46, 1, 1, 1, 0,
    2, 0x102, 2, 0xB, 3, 0x203, 3, 0xB,
    4, 0x304, 4, 0xB, 5, 0x405, 5, 0xB,
    5, 0x506, 6, 0xB, 6, 0x607, 7, 0xB,
    3, 0x208, 8, 0xB, 4, 0x809, 9, 0xB,
    5, 0x90A, 0xA, 0xB, 5, 0xA0B, 0xB, 0xB,
    6, 0xB0C, 0xC, 0xB, 3, 0x20D, 0xD, 0,
    4, 0xD0E, 0xE, 0xB, 2, 0x10F, 0xF, 0xB,
    3, 0xF10, 0x10, 0xB, 4, 0x1011, 0x11, 0xB,
    5, 0x1112, 0x12, 0xB, 3, 0xF13, 0x13, 0xB,
    4, 0x1314, 0x14, 0xB, 5, 0x1415, 0x15, 0xB,
    -1, -1, -1, -1,
};
int scale_800B3D24[3] = {
    0x1000, 0x1000, 0x1000,
};
const int unknown_800B22C0[1] = {
    0x132,
};
const char str_800B22C4[20] = "\x82""c\x82\x92\x82\x85\x82\x81\x82\x8d\x81@\x82l\x82\x81\x82\x8e";
const char str_800B22D8[12] = "\x82""c\x82l\x82x\x82""a";
const char str_800B22E4[16] = "\x82o\x82\x81\x82\x94\x82\x8c\x82\x83\x82\x88\x82\x95";
