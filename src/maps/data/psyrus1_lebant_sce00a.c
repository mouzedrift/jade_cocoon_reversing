#include "maps/map.h"

void SlidingDoor_800B2300(MapEnt* ent);
void MinionInit_800B25F0(MapEnt* ent);
void SavePoint_800B2928(MapEnt* ent);
void MapInit_800B2D98(int phase);
void ScriptSpot_800B2E04(MapEnt* ent);
void SlidingDoorInit_800B2E78(MapEnt* ent);
void MinionIdle_800B2F0C(MapEnt* ent);
void SavePointInit_800B2F14(MapEnt* ent);
int HasItem0_800B2F54(void);
void StartMapTask_800B2F78(void);
void MapTaskLoad_800B2FA8(EventEntry* entry, int* st);
void MapTask_800B3040(EventEntry* entry, int* st);
int LeaveArea_800B30F8(MapEvent* ev, int area);
int EnterArea_800B3214(MapEvent* ev, int area, int prev);
void RequestModels_800B331C(MapEvent* ev);
int AddEntity_800B33EC(void* ev);
int StopLevantIfSet_800B3518(MapScriptSpot* spot);
int MinionF_800B3548(void);
int MinionF_800B3550(void);
void EntityTask_800B3558(EventEntry* entry, MapEnt* ent);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[16];
extern const char str_800B22D4[12];
extern const char data_800B22E0[24];
extern const MapRgb savePointDim_800B22F8;
extern const MapRgb savePointLit_800B22FC;
extern MapSavePoint savePoint_800B35D8;
extern short bones_800B35E8[68];
extern ActorScriptCmd* script_800B3670;
extern MapActorModel model_800B3674;
extern int data_800B36A0[20];
extern int data_800B36F0[2];
extern MapVoice voices_800B36F8[38];
extern int data_800B3828[4];
extern int data_800B3838[4];
extern int data_800B3848[2];
extern MapInstr script_800B3850[44];
extern MapInstr script_800B3B10[142];
extern MapMinion minion_800B43F0;
extern MapEvent events_800B4414[8];
extern int data_800B44B4[16];
extern int data_800B44F4[3];
extern int data_800B4500[28];
extern int data_800B4570[32];
extern int data_800B45F0[24];
extern short bones_800B4650[92];
extern int scale_800B4708[3];

MapSavePoint savePoint_800B35D8 = { { 0x46, 0, -0x100 }, str_800B22C4 };
short bones_800B35E8[68] = {
    0, 0, 0, 0x44, 1, 1, 1, 0,
    2, 0x102, 2, 0xB, 3, 0x203, 3, 0xB,
    4, 0x304, 4, 0xB, 5, 0x405, 5, 0xB,
    5, 0x506, 6, 0xB, 6, 0x607, 7, 0xB,
    3, 0x208, 8, 0xB, 4, 0x809, 9, 0xB,
    5, 0x90A, 0xA, 0xB, 5, 0xA0B, 0xB, 0xB,
    6, 0xB0C, 0xC, 0xB, 3, 0x20D, 0xD, 0,
    4, 0xD0E, 0xE, 0xB, 2, 0x10F, 0xF, 0xB,
    -1, -1, -1, -1,
};
ActorScriptCmd* script_800B3670 = 0;
MapActorModel model_800B3674 = { str_800B22D4, 0x38, bones_800B35E8, 0, 0, 0, 4, &script_800B3670, 0, 0x800000, 0, 1 };
int data_800B36A0[20] = {
    1, 0x66, -0xE4, -0x2FD, -0x10000, -1, -1, 0,
    0x66, -0x11, -0x296, -0x4000000, 0x66, -1, 0, 0,
    0, 0, 0, 0x1A0010,
};
int data_800B36F0[2] = {
    0x1010000, 0,
};
MapVoice voices_800B36F8[38] = {
    { 0, 0, { 0x12, 0x414, 0xF } },
    { 1, 0, { 0xB, 0x41D, 0x1B } },
    { 1, 1, { 0x1C, 0x41D, 0x29 } },
    { 2, 0, { 0, 0x420, 0x25 } },
    { 3, 0, { 5, 0x46D, 0xD } },
    { 3, 1, { 0x15, 0x46D, 0x10 } },
    { 4, 0, { 0x1B, 0x420, 0xC } },
    { 4, 1, { 0x15, 0x421, 0x1A } },
    { 4, 2, { 0x1E, 0x422, 0x1A } },
    { 6, 0, { 0x12, 0x423, 0x15 } },
    { 6, 1, { 0xD, 0x424, 0x19 } },
    { 6, 2, { 0x1A, 0x424, 0x19 } },
    { 7, 0, { 0x13, 0x426, 0x22 } },
    { 7, 1, { 1, 0x429, 0x1B } },
    { 7, 2, { 4, 0x429, 0x25 } },
    { 7, 3, { 0x1D, 0x429, 0x19 } },
    { 8, 0, { 5, 0x42B, 0x17 } },
    { 8, 1, { 8, 0x42B, 0x15 } },
    { 8, 2, { 0x1B, 0x42C, 0x22 } },
    { 8, 3, { 0x16, 0x42E, 0x1E } },
    { 8, 4, { 3, 0x42F, 0x1A } },
    { 9, 0, { 0x1F, 0x42F, 0x18 } },
    { 0xA, 0, { 7, 0x431, 0x21 } },
    { 0xA, 1, { 0xC, 0x431, 0x19 } },
    { 0xB, 0, { 0x17, 0x433, 0x25 } },
    { 0xB, 1, { 6, 0x434, 0x12 } },
    { 0xB, 2, { 0xF, 0x435, 0x1C } },
    { 0xC, 0, { 0x19, 0x436, 0x1D } },
    { 0xC, 1, { 0xA, 0x438, 0x11 } },
    { 0xD, 0, { 0xB, 0x438, 0x21 } },
    { 0xD, 1, { 0xE, 0x438, 0x33 } },
    { 0xD, 2, { 0x12, 0x438, 0x26 } },
    { 0xD, 3, { 0x18, 0x438, 0x2D } },
    { 0xD, 4, { 0x14, 0x439, 0x23 } },
    { 0xD, 5, { 9, 0x43A, 0x13 } },
    { 0xD, 6, { 2, 0x43B, 0x17 } },
    { 0xD, 7, { 0x10, 0x43B, 0x12 } },
    { 0, 0, { -1, 0, 0 } },
};
int data_800B3828[4] = {
    0x4B, 0, -0x19, -0x400,
};
int data_800B3838[4] = {
    -0x113, 0, -0x4B, 0xCC,
};
int data_800B3848[2] = {
    0, 1,
};
MapInstr script_800B3850[44] = {
    { 9, 0, 0, 0 },
    { 0x1F, 1, 0xA, 0 },
    { 0xA, 0, 0xFF, 0 },
    { 0xA, 0, 0x10, 0 },
    { 9, 0, 0x10, 0 },
    { 5, 0, 0, 0 },
    { 7, 0, 3, 0 },
    { 0x2E, 1, -2, MAP_REF(savePoint_800B35D8) },
    { 0x67, 1, 0, 0 },
    { 0x13, 0, 0, MAP_REF(data_800B3828) },
    { 0x48, 0, 0x7E, 5 },
    { 0x48, 1, 0xC, 5 },
    { 0x67, 0xD, 0x17, 0 },
    { 0xC, 0, 0xA, 0 },
    { 0x67, 0xD, 0x17, 0 },
    { 0xC, 0, 0xA, 0 },
    { 0x67, 0xD, 0x17, 0 },
    { 0xC, 0, 0xA, 0 },
    { 0x67, 0xD, 0x17, 0 },
    { 0x38, 1, 0, 0 },
    { 0x3F, 0, 0, 0 },
    { 0x67, 2, 0x1E, 0 },
    { 0x49, 0, 0x7D007E, 1 },
    { 0xD, 0, 1, 0 },
    { 0x38, 1, 0, 1 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x80009, 1 },
    { 0x42, 0, 1, 0 },
    { 0x3F, 0, 0, 0 },
    { 0x49, 1, 0xB000C, 1 },
    { 0x48, 0, 0x7F, 1 },
    { 0x45, 0, 1, 0 },
    { 0x38, 1, 0, 2 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x80009, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x49, 1, 0xB000C, 1 },
    { 0x67, 3, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x53, 0, 0xA, 0 },
    { 8, 0, 3, 0 },
    { 4, 0, 0, 0 },
    { 9, 0, 0xFF, 0 },
    { 3, 0, 0, 0 },
};
MapInstr script_800B3B10[142] = {
    { 9, 0, 0, 0 },
    { 0x62, -1, 2, 0 },
    { 5, 0, 0, 0 },
    { 7, 0, 3, 0 },
    { 0x61, 0, 1, 0 },
    { 0x13, 0, 0, MAP_REF(data_800B3838) },
    { 0x49, 0, 0xA300A4, 5 },
    { 0xD, 0, 1, 0 },
    { 0x4E, 0, 0, MAP_REF(HasItem0_800B2F54) },
    { 0xA, 0, 0xA0, 0 },
    { 0xA, 0, 1, 0 },
    { 9, 0, 1, 0 },
    { 0x10, 0x70000, 0x40001, 0 },
    { 0xA, 0, 0x10, 0 },
    { 0xA, 0, 0x20, 0 },
    { 0xA, 0, 0x30, 0 },
    { 0xA, 0, 0x40, 0 },
    { 9, 0, 0x10, 0 },
    { 0x38, 1, 0, 4 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x140020, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x160020, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x170020, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0x20, 0 },
    { 0x38, 1, 0, 0xA },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x140020, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x150020, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0x30, 0 },
    { 0x38, 1, 0, 0xB },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x150020, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x140020, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x150020, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0x40, 0 },
    { 0x38, 1, 0, 0xC },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x1C0020, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x190020, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0x50, 0 },
    { 0x3A, 1, 0, 5 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x180020, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x60, 0 },
    { 0xA, 0, 0x70, 0 },
    { 0xA, 0, 0x80, 0 },
    { 0xA, 0, 0xF0, 0 },
    { 0xA, 0, 0x90, 0 },
    { 9, 0, 0x60, 0 },
    { 0x38, 1, 0, 6 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x190020, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x1A0020, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x190020, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0x70, 0 },
    { 0x38, 1, 0, 7 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x160020, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x190020, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x170020, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0x1C0020, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0x80, 0 },
    { 0x38, 1, 0, 8 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x140020, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x150020, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x1D0020, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0x190020, 1 },
    { 0x42, 0, 4, 0 },
    { 0x49, 1, 0x170020, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0xF0, 0 },
    { 0x38, 1, 0, 0xD },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x140020, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x150020, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x1D0020, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0x190020, 1 },
    { 0x42, 0, 4, 0 },
    { 0x49, 1, 0x170020, 1 },
    { 0x42, 0, 5, 0 },
    { 0x49, 1, 0x150020, 1 },
    { 0x42, 0, 6, 0 },
    { 0x49, 1, 0x180020, 1 },
    { 0x42, 0, 7, 0 },
    { 0x49, 1, 0x140020, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0x90, 0 },
    { 0x38, 1, 0, 9 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x140020, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0xFF, 0 },
    { 9, 0, 0xA0, 0 },
    { 0x38, 1, 0, 3 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x140020, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x160020, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x3C, 1, 1, MAP_REF(data_800B3848) },
    { 0xA, 0, 0xFF, 0 },
    { 9, 0, 0xFF, 0 },
    { 0x48, 0, 0xA5, 1 },
    { 0xD, 0, 1, 0 },
    { 0x61, 0, 0, 0 },
    { 8, 0, 3, 0 },
    { 4, 0, 0, 0 },
    { 0xA, 0, 0, 0 },
    { 3, 0, 0, 0 },
};
MapMinion minion_800B43F0 = { &model_800B3674, 0, { -0x7D, 0, 0xC8 }, -0x71C, -1, 0x20, 2, 2 };
MapEvent events_800B4414[8] = {
    { -1, 0, data_800B36F0, 0, { ScriptSpot_800B2E04 } },
    { -1, 2, data_800B36A0, 0xC, { SlidingDoorInit_800B2E78 } },
    { -1, 0xF, &minion_800B43F0, 0x14, { MinionInit_800B25F0 } },
    { -1, 8, script_800B3850, 0, { 0 } },
    { -1, 8, script_800B3B10, 0, { 0 } },
    { -1, 0xB, voices_800B36F8, 0, { 0 } },
    { -1, 0xC, &savePoint_800B35D8, 0xC, { SavePointInit_800B2F14 } },
    { 0, 0x12, 0, 0, { 0 } },
};
int data_800B44B4[16] = {
    0x4B, 0, 0, 0, 0x4D, 0, 0, MAP_REF(StopLevantIfSet_800B3518),
    0x58, 0, 0, 0, 3, 0, 0, 0,
};
int data_800B44F4[3] = {
    MAP_REF(data_800B22E0), 0, 0,
};
int data_800B4500[28] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x30, 0, 1, 0, 0x31, 0, 2, 0,
    8, 0, 1, 0, 4, 0, 0, 0,
    3, 0, 0, 0,
};
int data_800B4570[32] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x3E, -1, 4, 5, 0x30, 0, 1, 0,
    0x31, 0, 2, 0, 8, 0, 1, 0,
    4, 0, 0, 0, 3, 0, 0, 0,
};
int data_800B45F0[24] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x3B, 0, 0, MAP_REF(data_800B44F4), 8, 0, 1, 0,
    4, 0, 0, 0, 3, 0, 0, 0,
};
short bones_800B4650[92] = {
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
int scale_800B4708[3] = {
    0x1000, 0x1000, 0x1000,
};
const char unknown_800B22C0[4] = "1";
const char str_800B22C4[16] = "\x82l\x82x\x81@\x82g\x82n\x82l\x82""d";
const char str_800B22D4[12] = "\x82o\x82\x88\x82\x89\x82\x8f";
const char data_800B22E0[24] = "\x82h\x82\x94\x81""f\x82\x93\x81@\x82k\x82\x8f\x82\x83\x82\x8b\x82\x85\x82\x84";
const MapRgb savePointDim_800B22F8 = { 0x80, 0x40, 0x20, 0 };
const MapRgb savePointLit_800B22FC = { 0x20, 0x40, 0x80, 0 };
