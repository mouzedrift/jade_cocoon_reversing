#include "maps/map.h"

void Warp_800B2304(MapEnt* ent);
void MinionInit_800B2428(MapEnt* ent);
int AddEffects_800B2760(MapFx* fx);
void FxModel_800B28EC(MapEnt* ent);
void ExitSpot_800B2B14(MapEnt* ent);
void SavePoint_800B2C80(MapEnt* ent);
void MapInitOld_800B30F0(int phase);
void MinionIdle_800B31B8(MapEnt* ent);
void FxInit_800B31C0(MapEnt* ent);
void FxMdec_800B3278(MapEnt* ent);
void ExitSpotInit_800B3364(MapEnt* ent);
void SavePointInit_800B3400(MapEnt* ent);
void StartMapTask_800B3440(void);
void MapTaskLoad_800B3470(EventEntry* entry, int* st);
void MapTask_800B3508(EventEntry* entry, int* st);
int LeaveArea_800B35C0(MapEvent* ev, int area);
int EnterArea_800B36DC(MapEvent* ev, int area, int prev);
void RequestModels_800B37E4(MapEvent* ev);
void EntityTask_800B38B4(EventEntry* entry, MapEnt* ent);
int AddEntity_800B3934(void* ev);
void MapInit_800B3A60(int phase);
int MinionF_800B3ACC(void);
int MinionF_800B3AD4(void);
int FxFrame_800B3ADC(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B3B60(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B3C2C(MapFx* fx, MapFxWork* w);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[28];
extern const char str_800B22E0[8];
extern const MapFxInits fxInits_800B22E8;
extern const MapRgb savePointDim_800B22FC;
extern const MapRgb savePointLit_800B2300;
extern MapSavePoint savePoint_800B3D74;
extern short bones_800B3D84[96];
extern ActorScriptCmd* script_800B3E44;
extern MapActorModel model_800B3E48;
extern MapVoice voices_800B3E74[37];
extern MapWarp warp_800B3F9C;
extern int data_800B3FB4[4];
extern int data_800B3FC4[3];
extern MapInstr script_800B3FD0[15];
extern MapInstr script_800B40C0[146];
extern MapInstr script_800B49E0[37];
extern MapExitSpot data_800B4C30;
extern MapMinion minion_800B4C50;
extern MapEvent events_800B4C74[9];
extern short bones_800B4D28[92];
extern int scale_800B4DE0[3];
extern int data_800B4DEC[33];
extern int data_800B4E70[52];
extern int data_800B4F40[56];
extern int data_800B5020[76];

MapSavePoint savePoint_800B3D74 = { { -0x3E8, 0, 0x252 }, str_800B22C4 };
short bones_800B3D84[96] = {
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
    3, 0xF16, 0x16, 0xB, -1, -1, -1, -1,
};
ActorScriptCmd* script_800B3E44 = 0;
MapActorModel model_800B3E48 = { str_800B22E0, 0x3F, bones_800B3D84, 0, 0, 0, 4, &script_800B3E44, 0, 0x800000, 0, 0 };
MapVoice voices_800B3E74[37] = {
    { 0, 0, { 0xE, 0x356, 0x22 } },
    { 0, 1, { 8, 0x357, 0x20 } },
    { 0, 2, { 0x17, 0x357, 0x19 } },
    { 0, 3, { 1, 0x358, 0x1D } },
    { 2, 0, { 5, 0x35A, 0xF } },
    { 2, 1, { 9, 0x35F, 0x2B } },
    { 2, 2, { 0x12, 0x360, 0x19 } },
    { 2, 3, { 0x14, 0x360, 0x2E } },
    { 2, 4, { 0xF, 0x362, 0x1D } },
    { 3, 0, { 0x1F, 0x363, 0x1C } },
    { 3, 1, { 0x10, 0x364, 0x35 } },
    { 3, 2, { 0, 0x365, 0x1C } },
    { 3, 3, { 0x18, 0x365, 0x16 } },
    { 3, 4, { 0x1D, 0x367, 0x2A } },
    { 4, 0, { 7, 0x368, 0x25 } },
    { 4, 1, { 5, 0x369, 0x1B } },
    { 4, 2, { 0xC, 0x369, 0x21 } },
    { 4, 3, { 0xD, 0x369, 0x3D } },
    { 5, 0, { 0x13, 0x369, 0x30 } },
    { 5, 1, { 0xB, 0x36A, 0x15 } },
    { 5, 2, { 0x1C, 0x36A, 0x28 } },
    { 6, 0, { 3, 0x36B, 0x26 } },
    { 6, 1, { 0x16, 0x36B, 0x15 } },
    { 7, 0, { 1, 0x358, 0x1D } },
    { 8, 0, { 0x1A, 0x36E, 0x22 } },
    { 8, 1, { 0x15, 0x36F, 0x20 } },
    { 8, 2, { 0x19, 0x36F, 0x1E } },
    { 9, 0, { 0x1B, 0x36F, 0x24 } },
    { 0xA, 0, { 0xA, 0x370, 0x14 } },
    { 0xA, 1, { 0x17, 0x370, 0x18 } },
    { 0xA, 2, { 1, 0x375, 0x2A } },
    { 0xB, 0, { 2, 0x371, 0x1B } },
    { 0xB, 1, { 6, 0x374, 0x15 } },
    { 0xB, 2, { 1, 0x375, 0x2A } },
    { 0xC, 0, { 0, 0x346, 0x1F } },
    { 0xC, 1, { 1, 0x375, 0x2A } },
    { 0, 0, { -1, 0, 0 } },
};
MapWarp warp_800B3F9C = { { 0, 0, 0x655 }, 0, 0, 0, { 4, 4, 0xD } };
int data_800B3FB4[4] = {
    0, 0, 0x1F4, 0,
};
int data_800B3FC4[3] = {
    0x47E, 0, 0x47E,
};
MapInstr script_800B3FD0[15] = {
    { 0x1F, 1, 0x36, 0 },
    { 0xA, 0, 0xFF, 0 },
    { 0xA, 0, 0x10, 0 },
    { 9, 0, 0x10, 0 },
    { 0x57, 0, 0xCB, 0 },
    { 0x20, 0, 0x36, 0 },
    { 5, 0, 0, 0 },
    { 7, 0, 3, 0 },
    { 0x13, 0, 0, MAP_REF(data_800B3FB4) },
    { 0x67, 2, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 8, 0, 3, 0 },
    { 4, 0, 0, 0 },
    { 9, 0, 0xFF, 0 },
    { 3, 0, 0, 0 },
};
MapInstr script_800B40C0[146] = {
    { 9, 0, 0, 0 },
    { 0x62, 3, 2, 0 },
    { 5, 0, 0, 0 },
    { 7, 0, 3, 0 },
    { 0x61, 0, 1, 0 },
    { 0x13, 0, 0, MAP_REF(data_800B3FB4) },
    { 0x49, 0, 0x18C0192, 5 },
    { 0xD, 0, 1, 0 },
    { 9, 0, 0x10, 0 },
    { 0x1F, 1, 6, 0 },
    { 0xA, 0, 0x101, 0 },
    { 0xA, 0, 0x20, 0 },
    { 9, 0, 0x101, 0 },
    { 0x1F, 1, 0, 0 },
    { 0xA, 0, 0x40, 0 },
    { 0xA, 0, 0x30, 0 },
    { 9, 0, 0x20, 0 },
    { 0xF, 0, 0x20000, 0 },
    { 0xA, 0, 0x201, 0 },
    { 0xA, 0, 0x202, 0 },
    { 9, 0, 0x201, 0 },
    { 0x38, 1, 0, 0 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x3000B, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x5000B, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0xA000B, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0x6000B, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0x202, 0 },
    { 0x38, 1, 0, 7 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x6000B, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0x30, 0 },
    { 0xF, 0, 0x20000, 0 },
    { 0xA, 0, 0x301, 0 },
    { 0xA, 0, 0x302, 0 },
    { 9, 0, 0x301, 0 },
    { 0x38, 1, 0, 0xB },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x7000B, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x3000B, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x6000B, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0x302, 0 },
    { 0x38, 1, 0, 0xC },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x4000B, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x6000B, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0x40, 0 },
    { 0xE, 0, 1, 0 },
    { 0x21, 0, 0, 0 },
    { 0x38, 1, 0, 0xA },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x6000B, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x4000B, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x6000B, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0x50, 0 },
    { 0x3A, 1, 0, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x60, 0 },
    { 0xA, 0, 0x70, 0 },
    { 0xA, 0, 0x80, 0 },
    { 0xA, 0, 0x90, 0 },
    { 0xA, 0, 0xA0, 0 },
    { 9, 0, 0x60, 0 },
    { 0x38, 1, 0, 2 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x7000B, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x6000B, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x3000B, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0x4000B, 1 },
    { 0x42, 0, 4, 0 },
    { 0x49, 1, 0x5000B, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0x70, 0 },
    { 0x38, 1, 0, 3 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x7000B, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x3000B, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x8000B, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0x5000B, 1 },
    { 0x42, 0, 4, 0 },
    { 0x49, 1, 0x6000B, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0x80, 0 },
    { 0x38, 1, 0, 4 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x3000B, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x4000B, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x6000B, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0x5000B, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0x90, 0 },
    { 0x38, 1, 0, 5 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x5000B, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0xA000B, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x5000B, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0xA0, 0 },
    { 0x38, 1, 0, 6 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x16000B, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x6000B, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0xFF, 0 },
    { 9, 0, 0xFF, 0 },
    { 0x48, 0, 0x12E, 1 },
    { 0xD, 0, 1, 0 },
    { 0x61, 0, 0, 0 },
    { 8, 0, 3, 0 },
    { 4, 0, 0, 0 },
    { 0xA, 0, 0, 0 },
    { 3, 0, 0, 0 },
};
MapInstr script_800B49E0[37] = {
    { 9, 0, 0, 0 },
    { 0x64, 0, 1, 0 },
    { 5, 0, 0, 0 },
    { 7, 0, 3, 0 },
    { 0x49, 1, 0xD000E, 1 },
    { 0xF, 0, 0x20000, 0 },
    { 0xA, 0, 0x10, 0 },
    { 0xA, 0, 0x20, 0 },
    { 9, 0, 0x10, 0 },
    { 0x38, 1, 0, 8 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x10000E, 1 },
    { 0x18, 0, -1, MAP_REF(data_800B3FC4) },
    { 0x14, 0, -1, MAP_REF(data_800B3FC4) },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x11000E, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x10000E, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0xFF, 0 },
    { 9, 0, 0x20, 0 },
    { 0x38, 1, 0, 9 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x10000E, 1 },
    { 0x18, 0, -1, MAP_REF(data_800B3FC4) },
    { 0x14, 0, -1, MAP_REF(data_800B3FC4) },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0xFF, 0 },
    { 9, 0, 0xFF, 0 },
    { 0x49, 1, 0xF000B, 1 },
    { 0x18, 0, -1, MAP_REF(data_800B3FC4) },
    { 0x14, 0, -1, MAP_REF(data_800B3FC4) },
    { 0xD, 0, 1, 0 },
    { 8, 0, 3, 0 },
    { 4, 0, 0, 0 },
    { 0xA, 0, 0, 0 },
    { 3, 0, 0, 0 },
};
MapExitSpot data_800B4C30 = { 0xD1, 0xD2, 6, 2, { -0x61A, 0, 0x640 }, 0x614 };
MapMinion minion_800B4C50 = { &model_800B3E48, 0, { 0, 0, 0x51B }, -0x800, -1, 0xB, 2, 2 };
MapEvent events_800B4C74[9] = {
    { -1, 1, &warp_800B3F9C, 0, { Warp_800B2304 } },
    { -1, 0xD, &data_800B4C30, 4, { ExitSpotInit_800B3364 } },
    { -1, 0xF, &minion_800B4C50, 0x14, { MinionInit_800B2428 } },
    { -1, 8, script_800B3FD0, 0, { 0 } },
    { -1, 8, script_800B40C0, 0, { 0 } },
    { -1, 8, script_800B49E0, 0, { 0 } },
    { -1, 0xB, voices_800B3E74, 0, { 0 } },
    { -1, 0xC, &savePoint_800B3D74, 0xC, { SavePointInit_800B3400 } },
    { 0, 0x12, 0, 0, { 0 } },
};
short bones_800B4D28[92] = {
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
int scale_800B4DE0[3] = {
    0x1000, 0x1000, 0x1000,
};
int data_800B4DEC[33] = {
    0x9D0001, 0, 0, 0, 0, 0, 0x3C, 0,
    0, 0x30, 0, 0x140003, 0, 0, 0, 0,
    0, 0x3C, 0, -0x10000, 2, 0, 5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0,
};
int data_800B4E70[52] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x67, 0xC, 5, 0, 0x4B, 0, 0, MAP_REF(data_800B4DEC),
    0x4D, 0, 0, MAP_REF(AddEffects_800B2760), 0xC, 0, 0x1E, 0,
    0x67, 5, 0x1E, 0, 0xC, 0, 0x3C, 0,
    0x30, 0, 1, 0, 0x31, 0, 1, 0,
    8, 0, 1, 0, 4, 0, 0, 0,
    3, 0, 0, 0,
};
int data_800B4F40[56] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x67, 0xC, 5, 0, 0x4B, 0, 0, MAP_REF(data_800B4DEC),
    0x4D, 0, 0, MAP_REF(AddEffects_800B2760), 0xC, 0, 0x1E, 0,
    0x67, 5, 0x1E, 0, 0xC, 0, 0x3C, 0,
    0x1A, 1, 1, 0, 0x67, 4, 0x1E, 0,
    0x67, 6, 0, 0, 8, 0, 1, 0,
    4, 0, 0, 0, 3, 0, 0, 0,
};
int data_800B5020[76] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x67, 0xC, 5, 0, 0x4B, 0, 0, MAP_REF(data_800B4DEC),
    0x4D, 0, 0, MAP_REF(AddEffects_800B2760), 0xC, 0, 0x1E, 0,
    0x67, 5, 0x1E, 0, 0xC, 0, 0x3C, 0,
    0x1A, 1, 1, 0, 0x67, 4, 0x1E, 0,
    0x48, 0, 0xE1, 5, 0x48, 0, 0xE2, 1,
    0x48, 0, 0xE4, 1, 0x49, 0, 0xE300E5, 1,
    0xD, 0, 1, 0, 0x67, 6, 0, 0,
    8, 0, 1, 0, 4, 0, 0, 0,
    3, 0, 0, 0,
};
const char unknown_800B22C0[4] = "\xf4";
const char str_800B22C4[28] = "\x82m\x82`\x82""f\x82h\x81@\x82u\x82h\x82k\x82k\x82`\x82""f\x82""d";
const char str_800B22E0[8] = "\x82m\x82\x89";
const MapFxInits fxInits_800B22E8 = { { 0, FxModel_800B28EC, 0, FxMdec_800B3278, 0 } };
const MapRgb savePointDim_800B22FC = { 0x80, 0x40, 0x20, 0 };
const MapRgb savePointLit_800B2300 = { 0x20, 0x40, 0x80, 0 };
