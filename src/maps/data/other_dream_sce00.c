#include "maps/map.h"

void MinionInit_800B22F8(MapEnt* ent);
void FtgAnim_800B2630(MapEnt* ent);
void MapInit_800B276C(int phase);
void MinionIdle_800B2850(MapEnt* ent);
void CameraOrbitInit_800B2858(MapEnt* ent);
void CameraOrbit_800B2890(MapEnt* ent);
void FtgAnimInit_800B2920(MapEnt* ent);
int ExitDream_800B2958(MapExitArgs* args);
void StartMapTask_800B299C(void);
void MapTaskLoad_800B29CC(EventEntry* entry, int* st);
void MapTask_800B2A64(EventEntry* entry, int* st);
int LeaveArea_800B2B18(MapEvent* ev, int area);
int EnterArea_800B2C34(MapEvent* ev, int area, int prev);
void RequestModels_800B2D3C(MapEvent* ev);
int AddEntity_800B2E0C(void* ev);
void MapReinit_800B2F38(int phase);
int MinionF_800B2FAC(void);
int MinionF_800B2FB4(void);
void EntityTask_800B2FBC(EventEntry* entry, MapEnt* ent);

extern const int unknown_800B22C0[1];
extern const char str_800B22C4[12];
extern const char str_800B22D0[8];
extern const char str_800B22D8[20];
extern const int str_800B22EC[3];
extern int unknown_800B303C[12];
extern int data_800B306C[12];
extern ActorScriptCmd* script_800B309C;
extern MapActorModel model_800B30A0;
extern int data_800B30CC[12];
extern int data_800B30FC[12];
extern ActorScriptCmd* script_800B312C;
extern MapActorModel model_800B3130;
extern short bones_800B315C[100];
extern int data_800B3224[3];
extern SVECTOR boneScale_800B3230[24];
extern int anim_800B32F0[19];
extern int anim_800B333C[19];
extern ActorScriptCmd anim_800B3388[4];
extern ActorScriptCmd anim_800B33B8[4];
extern ActorScriptCmd anim_800B33E8[4];
extern ActorScriptCmd* script_800B3418[34];
extern int data_800B34A0[3];
extern MapActorModel model_800B34AC;
extern int data_800B34D8[3];
extern SVECTOR boneScale_800B34E4[25];
extern int anim_800B35AC[19];
extern ActorScriptCmd anim_800B35F8[5];
extern ActorScriptCmd anim_800B3634[5];
extern ActorScriptCmd* script_800B3670[32];
extern MapActorModel model_800B36F0;
extern MapVoice voices_800B371C[12];
extern SVECTOR rots_800B377C[6];
extern MapFtgAnim ftgAnim_800B37AC;
extern MapEvent event_800B37B8;
extern MapEvent event_800B37CC;
extern int data_800B37E0[2];
extern int data_800B37E8[4];
extern int data_800B37F8[4];
extern int data_800B3808[18];
extern MapInstr script_800B3850[66];
extern MapInstr script_800B3C70[45];
extern MapMinion minion_800B3F40;
extern MapMinion minion_800B3F64;
extern MapMinion minion_800B3F88;
extern MapMinion minion_800B3FAC;
extern MapEvent events_800B3FD0[5];
extern MapEvent events_800B4034[5];
extern short bones_800B4098[92];
extern int scale_800B4150[3];
extern MapEvent* curEvents_800B415C;

int unknown_800B303C[12] = {
    -0x1FEF1, -0xFDF5, 0x10000, -0xFDFA, 0x1000000, -0xFDFF, 0x1A0000, -0x1FDEC,
    0x40000000, -0xFEF8, -0x1FEF0, -0x1FF00,
};
int data_800B306C[12] = {
    -0x1FEF1, -0xFDF9, 0x1000000, -0xFDFF, 0x1E0000, -0x1FDEC, 0x40000000, -0xFEF8,
    -0xFDF5, 0, -0x1FEF0, -0x1FF00,
};
ActorScriptCmd* script_800B309C = 0;
MapActorModel model_800B30A0 = { str_800B22C4, 0x2E, 0, 0, 0, 0, 4, &script_800B309C, 0, 0x800000, 0, 1 };
int data_800B30CC[12] = {
    -0x1FEF1, -0xFDF5, 0x10000, -0xFDFA, 0x1000000, -0xFDFF, 0xA0000, -0x1FDEC,
    0x40000000, -0xFEF8, -0x1FEF0, -0x1FF00,
};
int data_800B30FC[12] = {
    -0x1FEF1, -0xFDF9, 0x1000000, -0xFDFF, 0xD0000, -0x1FDEC, 0x40000000, -0xFEF8,
    -0xFDF5, 0, -0x1FEF0, -0x1FF00,
};
ActorScriptCmd* script_800B312C = 0;
MapActorModel model_800B3130 = { str_800B22D0, 0x2C, 0, 0, 0, 0, 4, &script_800B312C, 0, 0x800000, 0, 1 };
short bones_800B315C[100] = {
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
int data_800B3224[3] = {
    0x1000, 0x1000, 0x1000,
};
SVECTOR boneScale_800B3230[24] = {
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
int anim_800B32F0[19] = {
    -0x1FDF4, 0x1A0000, -0x1FEF3, -0x1FEF1, -0xFDF9, 0x1000000, -0xFEFD, -0xFDFF,
    0x1A0000, -0x1FDEC, 0x40000000, -0xFEF8, -0xFDF5, 0, -0x1FEF0, -0x1FEEF,
    -0xFDF2, 0x1A0000, -0x1FF00,
};
int anim_800B333C[19] = {
    -0x1FDF4, 0x1B0000, -0x1FEF3, -0x1FEF1, -0xFDF5, 0x10000, -0xFDFA, 0x1000000,
    -0xFDFF, 0x1B0000, -0x1FDEC, 0x40000000, -0xFEF8, -0x1FEF0, -0xFDFF, 0x40000,
    -0xFDF2, 0x1B0000, -0x1FF00,
};
ActorScriptCmd anim_800B3388[4] = {
    { 0xF, 1, -2, 0x20B, -1, 0, 1 },
    { 6, 2, -1, 0, 0x100, 0x201, -1 },
    { 0, 0, 1, 0x214, -2, 0, 0x4000 },
    { 8, 1, -1, 0x110, -2, 0x100, -2 },
};
ActorScriptCmd anim_800B33B8[4] = {
    { 0xF, 1, -2, 0x207, -1, 0, 0x100 },
    { 1, 2, -1, 0, 1, 0x214, -2 },
    { 0, 0, 0x4000, 0x108, -1, 0x20B, -1 },
    { 0, 0, 0, 0x110, -2, 0x100, -2 },
};
ActorScriptCmd anim_800B33E8[4] = {
    { 0xC, 2, -2, 0, 0x15, 0x10D, -2 },
    { 0xF, 1, -2, 0x103, -1, 0x201, -1 },
    { 0, 0, 0x15, 0x115, -2, 0x217, -2 },
    { 0, 0, 0x3C, 0x110, -2, 0x100, -2 },
};
ActorScriptCmd* script_800B3418[34] = {
    (void*)&commandScriptData_80079754, (void*)((char*)&commandScriptData_80079754 + 0xC), (void*)((char*)&commandScriptData_80079754 + 0x1C), (void*)((char*)&commandScriptData_80079754 + 0x54), (void*)((char*)&commandScriptData_80079754 + 0x8C), (void*)((char*)&commandScriptData_80079754 + 0xC4), (void*)((char*)&commandScriptData_80079754 + 0xFC), (void*)((char*)&commandScriptData_80079754 + 0x134),
    (void*)((char*)&commandScriptData_80079754 + 0x16C), (void*)((char*)&commandScriptData_80079754 + 0x1A4), (void*)((char*)&commandScriptData_80079754 + 0x200), (void*)((char*)&commandScriptData_80079754 + 0x238), (void*)((char*)&commandScriptData_80079754 + 0x270), (void*)((char*)&commandScriptData_80079754 + 0x2A8), (void*)((char*)&commandScriptData_80079A2C + 0x4), (void*)((char*)&commandScriptData_80079A2C + 0x1C),
    anim_800B33E8, (ActorScriptCmd*)anim_800B32F0, (ActorScriptCmd*)anim_800B333C, (void*)((char*)&commandScriptData_80079B44 + 0x8), (void*)((char*)&commandScriptData_80079B44 + 0x1C), (void*)((char*)&commandScriptData_80079B6C + 0x8), (void*)((char*)&commandScriptData_80079B6C + 0x20), (void*)((char*)&commandScriptData_80079B6C + 0x44),
    0, 0, 0, 0, 0, 0, 0, 0,
    anim_800B3388, anim_800B33B8,
};
int data_800B34A0[3] = {
    8, 0x17, -1,
};
MapActorModel model_800B34AC = { str_800B22D8, 0x63, bones_800B315C, data_800B3224, boneScale_800B3230, data_800B34A0, 4, script_800B3418, 0, 0x800000, 0, 1 };
int data_800B34D8[3] = {
    0x1400, 0x1400, 0x1400,
};
SVECTOR boneScale_800B34E4[25] = {
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
int anim_800B35AC[19] = {
    -0x1FDF4, 0x150000, -0x1FEF3, -0x1FEF1, -0xFDF9, 0x1000000, -0xFEFD, -0xFDFF,
    0x150000, -0x1FDEC, 0x40000000, -0xFEF8, -0xFDF5, 0, -0x1FEEF, -0xFDF2,
    0x150000, -0x1FEF0, -0x1FF00,
};
ActorScriptCmd anim_800B35F8[5] = {
    { 0xF, 1, -2, 0x20B, -1, 0, 1 },
    { 6, 2, -1, 0, 0x100, 0x204, -1 },
    { 0, 0, 1, 0x102, -1, 0x201, -1 },
    { 0, 0, 4, 0x214, -2, 0, 0x4000 },
    { 8, 1, -1, 0x110, -2, 0x100, -2 },
};
ActorScriptCmd anim_800B3634[5] = {
    { 0xF, 1, -2, 0x207, -1, 0, 0x100 },
    { 4, 2, -1, 0, 1, 0x102, -1 },
    { 1, 2, -1, 0, 4, 0x214, -2 },
    { 0, 0, 0x4000, 0x108, -1, 0x20B, -1 },
    { 0, 0, 0, 0x110, -2, 0x100, -2 },
};
ActorScriptCmd* script_800B3670[32] = {
    (void*)&commandScriptData_80079754, (void*)((char*)&commandScriptData_80079754 + 0xC), (void*)((char*)&commandScriptData_80079754 + 0x1C), (void*)((char*)&commandScriptData_80079754 + 0x54), (void*)((char*)&commandScriptData_80079754 + 0x8C), (void*)((char*)&commandScriptData_80079754 + 0xC4), (void*)((char*)&commandScriptData_80079754 + 0xFC), (void*)((char*)&commandScriptData_80079754 + 0x134),
    (void*)((char*)&commandScriptData_80079754 + 0x16C), (void*)((char*)&commandScriptData_80079754 + 0x1A4), (void*)((char*)&commandScriptData_80079754 + 0x200), (void*)((char*)&commandScriptData_80079754 + 0x238), (void*)((char*)&commandScriptData_80079754 + 0x270), (void*)((char*)&commandScriptData_80079754 + 0x2A8), (void*)((char*)&commandScriptData_80079A2C + 0x4), (void*)((char*)&commandScriptData_80079A2C + 0x1C),
    (ActorScriptCmd*)anim_800B35AC, anim_800B35F8, anim_800B3634, (void*)((char*)&commandScriptData_80079B44 + 0x8), (void*)((char*)&commandScriptData_80079B44 + 0x1C), (void*)((char*)&commandScriptData_80079B6C + 0x8), (void*)((char*)&commandScriptData_80079B6C + 0x20), (void*)((char*)&commandScriptData_80079B6C + 0x44),
    (void*)((char*)&commandScriptData_80079C04 + 0x14), (void*)((char*)&commandScriptData_80079C04 + 0x64), (void*)((char*)&commandScriptData_80079C04 + 0x84), (void*)((char*)&commandScriptData_80079CE0 + 0x1C), (void*)((char*)&commandScriptData_80079CE0 + 0x6C), (void*)((char*)&commandScriptData_80079DE4 + 0x14), (void*)((char*)&commandScriptData_80079DE4 + 0xB0), (void*)((char*)&commandScriptData_80079F50 + 0x14),
};
MapActorModel model_800B36F0 = { (const char*)str_800B22EC, 0x11, (void*)&defaultBones_80079140, data_800B34D8, boneScale_800B34E4, 0, 4, script_800B3670, 0x20002, 0x800002, 0, 0 };
MapVoice voices_800B371C[12] = {
    { 0, 0, { 0x14, 0x2B3, 0xA } },
    { 0, 1, { 0x1A, 0x2B3, 0x17 } },
    { 0, 2, { 7, 0x2B4, 0x10 } },
    { 1, 0, { 0x18, 0x272, 0xC } },
    { 1, 1, { 0x19, 0x273, 0x21 } },
    { 2, 0, { 0xD, 0x3F0, 0x1E } },
    { 2, 1, { 3, 0x3F1, 0x1E } },
    { 2, 2, { 5, 0x3F2, 0x1F } },
    { 2, 3, { 0x15, 0x3F2, 0x12 } },
    { 3, 0, { 2, 0x3F3, 0x1C } },
    { 3, 1, { 0x17, 0x3F3, 0x1D } },
    { 0, 0, { -1, 0, 0 } },
};
SVECTOR rots_800B377C[6] = {
    { -0x10B, -0x126, 0, 0 },
    { -0x164, -0x1B2, 0, 0 },
    { -0x13B, -0xE0, 0, 0 },
    { -0x12A, -0xF2, 0, 0 },
    { -0x13B, -0xAF, 0, 0 },
    { -0xAD, -0x3B, 0, 0 },
};
MapFtgAnim ftgAnim_800B37AC = { 0, 0xF, 0x800, 0, rots_800B377C };
MapEvent event_800B37B8 = { -1, 0xD, &ftgAnim_800B37AC, 4, { FtgAnimInit_800B2920 } };
MapEvent event_800B37CC = { -1, 0xD, 0, 8, { CameraOrbitInit_800B2858 } };
int data_800B37E0[2] = {
    0x15C0004, 0x71,
};
int data_800B37E8[4] = {
    -0x2BC, 0, -0xD2F, 0,
};
int data_800B37F8[4] = {
    0x12C, 0, 0x16F3, 0,
};
int data_800B3808[18] = {
    0, 1, 0, 0, 0, 0, 1, 2,
    5, 0x29, 0x50000000, 2, 0x2A, 0x24000000, 2, 0xD3,
    0, 0,
};
MapInstr script_800B3850[66] = {
    { 5, 0, 0, 0 },
    { 7, 0, 7, 0 },
    { 0x67, 0x12, 1, 0 },
    { 0x67, 0xB, 0, 0 },
    { 0x67, 1, 0, 0 },
    { 0x11, 0, 0, MAP_REF(event_800B37CC) },
    { 0x13, 0, 0, MAP_REF(data_800B37E8) },
    { 0x48, 0, 0x17B, 5 },
    { 0x67, 2, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x49, 0, 0x17C017D, 1 },
    { 0x67, 0x10, 0, MAP_REF(data_800B37E0) },
    { 0xC, 0, 0x348, 0 },
    { 0x67, 3, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x2E, 0, 0, MAP_REF(event_800B37CC) },
    { 0x2F, 0, 1, MAP_REF(event_800B37CC) },
    { 0x2E, 0, -2, MAP_REF(event_800B37CC) },
    { 0x67, 0xA, 0, 0 },
    { 0x11, 0, 0, MAP_REF(event_800B37B8) },
    { 0x67, 3, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0xD, 0, 1, 0 },
    { 0x45, 0, 1, 0 },
    { 0x49, 0, 0x7A007B, 5 },
    { 0x67, 2, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x46, 1, 0, MAP_REF(unknown_800B303C) },
    { 0xD, 0, 2, 0 },
    { 0x38, 1, 0, 0 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x1B0020, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x1C001F, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x1D001F, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x46, 1, 0, MAP_REF(data_800B306C) },
    { 8, 0, 1, 0 },
    { 0x64, 0, 1, 0 },
    { 7, 0, 1, 0 },
    { 0x19, 0, 2, -1 },
    { 0x49, 0, 0x7A007B, 1 },
    { 0xD, 0, 1, 0 },
    { 0x46, 2, 0, MAP_REF(data_800B30CC) },
    { 0xD, 0, 5, 0 },
    { 0x38, 2, 0, 1 },
    { 0x42, 0, 0, 0 },
    { 0x49, 2, 0xB000E, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 2, 0xC000E, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x46, 2, 0, MAP_REF(data_800B30FC) },
    { 8, 0, 1, 0 },
    { 0x64, 0, 2, 0 },
    { 7, 0, 1, 0 },
    { 0x49, 0, 0x7A007B, 1 },
    { 0xD, 0, 1, 0 },
    { 0x67, 3, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x67, 0x12, 0, 0 },
    { 8, 0, 7, 0 },
    { 4, 0, 0, 0 },
    { 0x4C, 1, 1, 0 },
    { 0x4D, 0, 0, MAP_REF(ExitDream_800B2958) },
    { 3, 0, 0, 0 },
};
MapInstr script_800B3C70[45] = {
    { 5, 0, 0, 0 },
    { 7, 0, 7, 0 },
    { 0x13, 0, 0, MAP_REF(data_800B37F8) },
    { 0x67, 0x12, 1, 0 },
    { 0x67, 1, 0, 0 },
    { 0x11, 0, 0, MAP_REF(event_800B37B8) },
    { 0x67, 2, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x46, 1, 0, MAP_REF(anim_800B3388) },
    { 0xD, 0, 2, 0 },
    { 0x38, 1, 0, 2 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x1E001D, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x200021, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x22001D, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0x23001D, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x45, 0, 1, 0 },
    { 0x65, 0, 0, MAP_REF(data_800B3808) },
    { 0x2C, 0, 1, 0 },
    { 0x1A, 2, 1, 0 },
    { 0x48, 1, 0x1D, 5 },
    { 0x48, 0, 0x191, 6 },
    { 0x67, 2, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x38, 1, 0, 3 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x1E001D, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x24001D, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x46, 1, 0, MAP_REF(anim_800B33B8) },
    { 0xD, 0, 2, 0 },
    { 0x67, 3, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x67, 0x12, 0, 0 },
    { 8, 0, 7, 0 },
    { 4, 0, 0, 0 },
    { 0xE, 1, 0, 0 },
    { 0x50, 0, 0, 0 },
    { 0x53, 0, 2, 0 },
    { 3, 0, 0, 0 },
};
MapMinion minion_800B3F40 = { &model_800B30A0, 0, { -0x271, 0, -0xBB8 }, 0x871, 0, 0x19, 1, 3 };
MapMinion minion_800B3F64 = { &model_800B3130, 0, { -0xAF, 0, 0x9C4 }, 0x871, 0, 9, 3, 3 };
MapMinion minion_800B3F88 = { &model_800B34AC, 0, { 0x178, -0xE, 0x1952 }, 0x1880, 0, 0x1D, 0, 3 };
MapMinion minion_800B3FAC = { &model_800B36F0, 0, { 0x178, -0xE, 0x1952 }, 0x1880, 0, 1, -1, 3 };
MapEvent events_800B3FD0[5] = {
    { -1, 0xF, &minion_800B3F40, 0x14, { MinionInit_800B22F8 } },
    { -1, 0xF, &minion_800B3F64, 0x14, { MinionInit_800B22F8 } },
    { -1, 8, script_800B3850, 0, { 0 } },
    { -1, 0xB, voices_800B371C, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
MapEvent events_800B4034[5] = {
    { -1, 0xF, &minion_800B3F88, 0x14, { MinionInit_800B22F8 } },
    { -1, 0xF, &minion_800B3FAC, 0x14, { MinionInit_800B22F8 } },
    { -1, 8, script_800B3C70, 0, { 0 } },
    { -1, 0xB, voices_800B371C, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
short bones_800B4098[92] = {
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
int scale_800B4150[3] = {
    0x1000, 0x1000, 0x1000,
};
MapEvent* curEvents_800B415C = 0;
const int unknown_800B22C0[1] = {
    0x131,
};
const char str_800B22C4[12] = "\x82l\x82\x81\x82\x88\x82\x82\x82\x95";
const char str_800B22D0[8] = "\x82k\x82\x95\x82\x89";
const char str_800B22D8[20] = "\x82""c\x82\x92\x82\x85\x82\x81\x82\x8d\x81@\x82l\x82\x81\x82\x8e";
const int str_800B22EC[3] = {
    0x6C826382, 0x61827882, -0x6D7E0000,
};
