#include "maps/map.h"

void Warp_800B2408(MapEnt* ent);
void SavePoint_800B252C(MapEnt* ent);
void Chest_800B299C(MapEnt* ent);
void ChestDraw_800B2B90(MapChest* chest, MapChestWork* w);
void MapInit_800B2E5C(int phase);
void SavePointInit_800B2EC8(MapEnt* ent);
void ChestInit_800B2F08(MapEnt* ent);
int ChestShut_800B2FE8(MapEnt* ent);
int ChestTake_800B2FF4(void* arg);
int ChestText_800B3078(void* arg);
int ChestCheck_800B30B0(MapEnt* ent);
void MeshTrigger_800B30F0(MapEnt* ent);
void StartMapTask_800B3158(void);
void MapTaskLoad_800B3188(EventEntry* entry, int* st);
void MapTask_800B3220(EventEntry* entry, int* st);
int LeaveArea_800B32D8(MapEvent* ev, int area);
int EnterArea_800B33F4(MapEvent* ev, int area, int prev);
void RequestModels_800B34FC(MapEvent* ev);
int AddEntity_800B35CC(void* ev);
void ChestKind1_800B36F8(MapChest* chest, MapChestWork* w);
void ChestKind2_800B3700(MapChest* chest, MapChestWork* w);
void EntityTask_800B3708(EventEntry* entry, MapEnt* ent);

extern const char unknown_800B22C0[4];
extern const char data_800B22C4[64];
extern const char data_800B2304[68];
extern const char str_800B2348[24];
extern const char data_800B2360[36];
extern const MapRgb savePointDim_800B2384;
extern const MapRgb savePointLit_800B2388;
extern const char data_800B238C[28];
extern const char data_800B23A8[52];
extern int text_800B3788[4];
extern MapChest chest_800B3798;
extern MapSavePoint savePoint_800B37E0;
extern MapWarp warp_800B37F0;
extern MapWarp warp_800B3808;
extern MapEvent event_800B3820;
extern int data_800B3834[3];
extern MapInstr script_800B3840[11];
extern MapEvent events_800B38F0[6];
extern int data_800B3968[3];
extern int data_800B3974[3];
extern int data_800B3980[212];

int text_800B3788[4] = {
    MAP_REF(data_800B2304), MAP_REF(data_800B22C4), 0, 0,
};
MapChest chest_800B3798 = { 0x48, -1, 3, 3, 3, { 0x35, 0, -0x264 }, 0, text_800B3788, 0, { 0x290000, 1, 0xFFFF, 0, 0xFFFF, 0 }, { 0, -1 } };
MapSavePoint savePoint_800B37E0 = { { 0xC8, 0, -0x11C6 }, str_800B2348 };
MapWarp warp_800B37F0 = { { 0, 0, 0x364 }, 0x4000, 0, 0, { 4, 2, 6 } };
MapWarp warp_800B3808 = { { 0, 0, -0x6FE }, 0x4000, 0, 1, { 4, 2, 8 } };
MapEvent event_800B3820 = { -1, 0xD, 0, 0, { (void*)MeshTrigger_800B30F0 } };
int data_800B3834[3] = {
    MAP_REF(data_800B2360), 0, 0,
};
MapInstr script_800B3840[11] = {
    { 0x11, 0, 0, MAP_REF(event_800B3820) },
    { 9, 0, 0, 0 },
    { 0x2F, 0, 0, MAP_REF(event_800B3820) },
    { 5, 0, 0, 0 },
    { 7, 0, 1, 0 },
    { 0xC, 0, 0x3C, 0 },
    { 0x3B, 0, 0, MAP_REF(data_800B3834) },
    { 8, 0, 1, 0 },
    { 4, 0, 0, 0 },
    { 0xA, 0, 0, 0 },
    { 3, 0, 0, 0 },
};
MapEvent events_800B38F0[6] = {
    { -1, 1, &warp_800B37F0, 0, { Warp_800B2408 } },
    { -1, 1, &warp_800B3808, 0, { Warp_800B2408 } },
    { -1, 8, script_800B3840, 0, { 0 } },
    { -1, 0xC, &savePoint_800B37E0, 0xC, { SavePointInit_800B2EC8 } },
    { -1, 4, &chest_800B3798, 0x18, { ChestInit_800B2F08 } },
    { 0, 0x12, 0, 0, { 0 } },
};
int data_800B3968[3] = {
    MAP_REF(data_800B238C), 0, 0,
};
int data_800B3974[3] = {
    MAP_REF(data_800B23A8), 0, 0,
};
int data_800B3980[212] = {
    9, 0, 0, 0, 5, 0, 0, 0,
    7, 0, 1, 0, 0x30, 0, 4, 0,
    0x31, 0, 4, 0, 0x4B, 0, 0, 0,
    0x4E, 0, 0, MAP_REF(ChestShut_800B2FE8), 0xA, 0, 0x70, 0,
    0xA, 0, 0x10, 0, 9, 0, 0x10, 0,
    0x30, 0, 4, 0, 0x31, 0, 4, 0,
    0x4B, 0, 0, 0, 0x4E, 0, 0, MAP_REF(ChestTake_800B2FF4),
    0xA, 0, 0x20, 0, 0xA, 0, 0x30, 0,
    0xA, 0, 0x40, 0, 9, 0, 0x20, 0,
    0x3E, -1, 4, 0, 0xA, 0, 0x50, 0,
    9, 0, 0x30, 0, 0x3B, 0, 0, -1,
    0xA, 0, 0xFF, 0, 9, 0, 0x40, 0,
    0x3B, 0, 0, -1, 0xA, 0, 0x50, 0,
    9, 0, 0x50, 0, 0x30, 0, 4, 0,
    0x31, 0, 4, 0, 0x4B, 0, 0, 0,
    0x4E, 0, 0, MAP_REF(ChestCheck_800B30B0), 0xA, 0, 0x60, 0,
    0xA, 0, 0xFF, 0, 9, 0, 0x60, 0,
    0x30, 0, 3, 0, 0x31, 0, 3, 0,
    0x3C, 3, 0, 0, 0x30, 0, 1, 0,
    0x31, 0, 1, 0, 0x30, 0, 2, 0,
    0x31, 0, 2, 0, 0xA, 0, 0xFF, 0,
    9, 0, 0x70, 0, 0x30, 0, 4, 0,
    0x31, 0, 4, 0, 0x4B, 0, 0, 0,
    0x4E, 0, 0, MAP_REF(ChestText_800B3078), 0x3B, 0, 0, -1,
    0xA, 0, 0xFF, 0, 9, 0, 0xFF, 0,
    8, 0, 1, 0, 4, 0, 0, 0,
    3, 0, 0, 0,
};
const char unknown_800B22C0[4] = "\xa7";
const char data_800B22C4[64] = "\x82\x93\x82\x8d\x82\x85\x82\x8c\x82\x8c\x82\x89\x82\x8e\x82\x87\x81@\x82\x90\x82\x8f\x82\x97\x82\x84\x82\x85\x82\x92\x81@\x82\x8f\x82\x8e\x81@\x82\x94\x82\x88\x82\x85\x81@\x82\x87\x82\x92\x82\x8f\x82\x95\x82\x8e\x82\x84\x81""D";
const char data_800B2304[68] = "\x82s\x82\x88\x82\x85\x82\x92\x82\x85\x81@\x82\x89\x82\x93\x81@\x82\x81\x81@\x82\x82\x82\x81\x82\x87\x81@\x82\x86\x82\x89\x82\x8c\x82\x8c\x82\x85\x82\x84\x81@\x82\x97\x82\x89\x82\x94\x82\x88\x81@\x82\x93\x82\x97\x82\x85\x82\x85\x82\x94\x81|";
const char str_800B2348[24] = "\x82""c\x82q\x82`\x82""f\x82n\x82m\x82""e\x82k\x82x\x81@\x82P";
const char data_800B2360[36] = "\x82m\x82\x8f\x82\x94\x82\x88\x82\x89\x82\x8e\x82\x87\x81@\x82g\x82\x81\x82\x90\x82\x90\x82\x85\x82\x8e\x82\x85\x82\x84\x81""D";
const MapRgb savePointDim_800B2384 = { 0x80, 0x40, 0x20, 0 };
const MapRgb savePointLit_800B2388 = { 0x20, 0x40, 0x80, 0 };
const char data_800B238C[28] = "\x82h\x82\x94\x81""f\x82\x93\x81@\x82k\x82\x8f\x82\x83\x82\x8b\x82\x85\x82\x84\x81""D";
const char data_800B23A8[52] = "\x82s\x82\x88\x82\x85\x82\x92\x82\x85\x81@\x82\x89\x82\x93\x81@\x82\x8e\x82\x8f\x82\x94\x82\x88\x82\x89\x82\x8e\x82\x87\x81@\x82\x89\x82\x8e\x82\x93\x82\x89\x82\x84\x82\x85\x81""D";
