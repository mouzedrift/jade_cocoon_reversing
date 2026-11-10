#include "maps/map.h"

void Warp_800B22EC(MapEnt* ent);
void SlidingDoor_800B2410(MapEnt* ent);
void MinionInit_800B2700(MapEnt* ent);
void MapInit_800B2A38(int phase);
void ScriptSpot_800B2AA8(MapEnt* ent);
void SlidingDoorInit_800B2B1C(MapEnt* ent);
void MinionIdle_800B2BB0(MapEnt* ent);
void TintParty_800B2BB8(MapEnt* ent);
int FadeOut_800B2C4C(void);
int FadeIn_800B2C70(void);
void StartMapTask_800B2C94(void);
void MapTaskLoad_800B2CC4(EventEntry* entry, int* st);
void MapTask_800B2D5C(EventEntry* entry, int* st);
int LeaveArea_800B2E14(MapEvent* ev, int area);
int EnterArea_800B2F30(MapEvent* ev, int area, int prev);
void RequestModels_800B3038(MapEvent* ev);
int AddEntity_800B3108(void* ev);
int StopLevantIfSet_800B3234(MapScriptSpot* spot);
int MinionF_800B3264(void);
int MinionF_800B326C(void);
void EntityTask_800B3274(EventEntry* entry, MapEnt* ent);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[16];
extern const char data_800B22D4[24];
extern ActorScriptCmd* script_800B32F4;
extern MapActorModel model_800B32F8;
extern int data_800B3324[2];
extern MapWarp warp_800B332C;
extern MapInstr script_800B3344[18];
extern int data_800B3464[20];
extern MapMinion minion_800B34B4;
extern MapEvent events_800B34D8[7];
extern int data_800B3564[16];
extern int data_800B35A4[3];
extern int data_800B35B0[28];
extern int data_800B3620[32];
extern int data_800B36A0[24];
extern short bones_800B3700[92];
extern int scale_800B37B8[3];

ActorScriptCmd* script_800B32F4 = 0;
MapActorModel model_800B32F8 = { str_800B22C4, 0x24, 0, 0, 0, 0, 4, &script_800B32F4, 0, 0x800000, 0, 0 };
int data_800B3324[2] = {
    0x1010001, 0,
};
MapWarp warp_800B332C = { { -0x7D, 0, -0x1F4 }, 0xE3, 0, 0, { 2, 1, 1 } };
MapInstr script_800B3344[18] = {
    { 0x64, 0, 0, 0 },
    { 0x1F, 1, 0x77, 0 },
    { 0xA, 0, 0xFF, 0 },
    { 0xA, 0, 0, 0 },
    { 9, 0, 0, 0 },
    { 5, 0, 0, 0 },
    { 7, 0, 1, 0 },
    { 0x2E, 1, -3, MAP_REF(warp_800B332C) },
    { 0x67, 0xC, 0xFF00, 0 },
    { 0x4D, 0, 1, MAP_REF(FadeOut_800B2C4C) },
    { 0xC, 0, 0x3C, 0 },
    { 0x67, 0xC, 0xFF03, 0xF },
    { 0x4D, 0, 1, MAP_REF(FadeIn_800B2C70) },
    { 0x2E, 1, -1, MAP_REF(warp_800B332C) },
    { 8, 0, 1, 0 },
    { 4, 0, 0, 0 },
    { 9, 0, 0xFF, 0 },
    { 3, 0, 0, 0 },
};
int data_800B3464[20] = {
    -1, 0x122, 0, 0xD1, -1, -1, -1, 0,
    0x6D, 0, 0x1D4, -0x4000000, 0x6D, -1, 0, 0,
    0, 0, 0, 0x1A0010,
};
MapMinion minion_800B34B4 = { &model_800B32F8, 0, { 0xF, 0, 0x296 }, 0, 0, 0x4E, 7, 2 };
MapEvent events_800B34D8[7] = {
    { -1, 0, data_800B3324, 0, { ScriptSpot_800B2AA8 } },
    { -1, 2, data_800B3464, 0xC, { SlidingDoorInit_800B2B1C } },
    { -1, 1, &warp_800B332C, 0, { Warp_800B22EC } },
    { -1, 0xF, &minion_800B34B4, 0x14, { MinionInit_800B2700 } },
    { -1, 0xD, (void*)0x2, 0, { TintParty_800B2BB8 } },
    { -1, 8, script_800B3344, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
int data_800B3564[16] = {
    0x4B, 0, 0, 0, 0x4D, 0, 0, MAP_REF(StopLevantIfSet_800B3234),
    0x58, 0, 0, 0, 3, 0, 0, 0,
};
int data_800B35A4[3] = {
    MAP_REF(data_800B22D4), 0, 0,
};
int data_800B35B0[28] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x30, 0, 1, 0, 0x31, 0, 2, 0,
    8, 0, 1, 0, 4, 0, 0, 0,
    3, 0, 0, 0,
};
int data_800B3620[32] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x3E, -1, 4, 5, 0x30, 0, 1, 0,
    0x31, 0, 2, 0, 8, 0, 1, 0,
    4, 0, 0, 0, 3, 0, 0, 0,
};
int data_800B36A0[24] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x3B, 0, 0, MAP_REF(data_800B35A4), 8, 0, 1, 0,
    4, 0, 0, 0, 3, 0, 0, 0,
};
short bones_800B3700[92] = {
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
int scale_800B37B8[3] = {
    0x1000, 0x1000, 0x1000,
};
const char unknown_800B22C0[4] = "m";
const char str_800B22C4[16] = "\x82j\x82\x85\x82\x8c\x82\x8d\x82\x81\x82\x92";
const char data_800B22D4[24] = "\x82h\x82\x94\x81""f\x82\x93\x81@\x82k\x82\x8f\x82\x83\x82\x8b\x82\x85\x82\x84";
