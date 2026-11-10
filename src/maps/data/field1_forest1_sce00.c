#include "maps/map.h"

void Warp_800B23A8(MapEnt* ent);
void Chest_800B24CC(MapEnt* ent);
void ChestDraw_800B26C0(MapChest* chest, MapChestWork* w);
void MapInit_800B298C(int phase);
void ChestInit_800B29FC(MapEnt* ent);
int ChestShut_800B2ADC(MapEnt* ent);
int ChestTake_800B2AE8(void* arg);
int ChestText_800B2B6C(void* arg);
int ChestCheck_800B2BA4(MapEnt* ent);
void StartMapTask_800B2BE4(void);
void MapTaskLoad_800B2C14(EventEntry* entry, int* st);
void MapTask_800B2CAC(EventEntry* entry, int* st);
int LeaveArea_800B2D64(MapEvent* ev, int area);
int EnterArea_800B2E80(MapEvent* ev, int area, int prev);
void RequestModels_800B2F88(MapEvent* ev);
int AddEntity_800B3058(void* ev);
void ChestKind1_800B3184(MapChest* chest, MapChestWork* w);
void ChestKind2_800B318C(MapChest* chest, MapChestWork* w);
void EntityTask_800B3194(EventEntry* entry, MapEnt* ent);

extern const char unknown_800B22C0[4];
extern const char data_800B22C4[40];
extern const char data_800B22EC[60];
extern const char data_800B2328[28];
extern const char data_800B2344[56];
extern int text_800B3214[4];
extern MapChest chest_800B3224;
extern MapWarp warp_800B326C;
extern MapWarp warp_800B3284;
extern int data_800B329C[3];
extern MapInstr script_800B32A8[17];
extern MapEvent events_800B33B8[5];
extern int data_800B341C[3];
extern int data_800B3428[3];
extern int data_800B3434[212];

int text_800B3214[4] = {
    MAP_REF(data_800B22EC), MAP_REF(data_800B22C4), 0, 0,
};
MapChest chest_800B3224 = { 0x3B, -1, 3, 3, 3, { 0x37A, 0, 0x1181 }, 0x400, text_800B3214, 0, { 0x190005, 1, 0xFFFF, 0, 0xFFFF, 0 }, { 0, -1 } };
MapWarp warp_800B326C = { { 0xD4E, 0, 0x105E }, 0x688, 0, 0, { 4, 0, 0 } };
MapWarp warp_800B3284 = { { 0xCE, 0, -0x33F }, 0xC1, 0, 2, { 4, 1, 0xA } };
int data_800B329C[3] = {
    -0x25, -0x520, -0xF55,
};
MapInstr script_800B32A8[17] = {
    { 0x1F, 1, 2, 0 },
    { 0xA, 0, 0xFF, 0 },
    { 0xA, 0, 0x10, 0 },
    { 9, 0, 0x10, 0 },
    { 0x20, 0, 2, 0 },
    { 5, 0, 0, 0 },
    { 7, 0, 1, 0 },
    { 0x5A, 0, 1, MAP_REF(data_800B329C) },
    { 0x67, 2, 0x1E, 0 },
    { 0xC, 0, 0x1E, 0 },
    { 0x5C, 0, 0x78, 0 },
    { 0x5D, 0, 0, 0 },
    { 0xC, 0, 0x1E, 0 },
    { 8, 0, 1, 0 },
    { 4, 0, 0, 0 },
    { 9, 0, 0xFF, 0 },
    { 3, 0, 0, 0 },
};
MapEvent events_800B33B8[5] = {
    { -1, 1, &warp_800B326C, 0, { Warp_800B23A8 } },
    { -1, 1, &warp_800B3284, 0, { Warp_800B23A8 } },
    { -1, 8, script_800B32A8, 0, { 0 } },
    { -1, 4, &chest_800B3224, 0x18, { ChestInit_800B29FC } },
    { 0, 0x12, 0, 0, { 0 } },
};
int data_800B341C[3] = {
    MAP_REF(data_800B2328), 0, 0,
};
int data_800B3428[3] = {
    MAP_REF(data_800B2344), 0, 0,
};
int data_800B3434[212] = {
    9, 0, 0, 0, 5, 0, 0, 0,
    7, 0, 1, 0, 0x30, 0, 4, 0,
    0x31, 0, 4, 0, 0x4B, 0, 0, 0,
    0x4E, 0, 0, MAP_REF(ChestShut_800B2ADC), 0xA, 0, 0x70, 0,
    0xA, 0, 0x10, 0, 9, 0, 0x10, 0,
    0x30, 0, 4, 0, 0x31, 0, 4, 0,
    0x4B, 0, 0, 0, 0x4E, 0, 0, MAP_REF(ChestTake_800B2AE8),
    0xA, 0, 0x20, 0, 0xA, 0, 0x30, 0,
    0xA, 0, 0x40, 0, 9, 0, 0x20, 0,
    0x3E, -1, 4, 0, 0xA, 0, 0x50, 0,
    9, 0, 0x30, 0, 0x3B, 0, 0, -1,
    0xA, 0, 0xFF, 0, 9, 0, 0x40, 0,
    0x3B, 0, 0, -1, 0xA, 0, 0x50, 0,
    9, 0, 0x50, 0, 0x30, 0, 4, 0,
    0x31, 0, 4, 0, 0x4B, 0, 0, 0,
    0x4E, 0, 0, MAP_REF(ChestCheck_800B2BA4), 0xA, 0, 0x60, 0,
    0xA, 0, 0xFF, 0, 9, 0, 0x60, 0,
    0x30, 0, 3, 0, 0x31, 0, 3, 0,
    0x3C, 3, 0, 0, 0x30, 0, 1, 0,
    0x31, 0, 1, 0, 0x30, 0, 2, 0,
    0x31, 0, 2, 0, 0xA, 0, 0xFF, 0,
    9, 0, 0x70, 0, 0x30, 0, 4, 0,
    0x31, 0, 4, 0, 0x4B, 0, 0, 0,
    0x4E, 0, 0, MAP_REF(ChestText_800B2B6C), 0x3B, 0, 0, -1,
    0xA, 0, 0xFF, 0, 9, 0, 0xFF, 0,
    8, 0, 1, 0, 4, 0, 0, 0,
    3, 0, 0, 0,
};
const char unknown_800B22C0[4] = "\x92";
const char data_800B22C4[40] = "\x82\x94\x82\x88\x82\x85\x81@\x82\x82\x82\x81\x82\x93\x82\x85\x81@\x82\x8f\x82\x86\x81@\x82\x81\x81@\x82\x92\x82\x8f\x82\x83\x82\x8b\x81""D";
const char data_800B22EC[60] = "\x82`\x81@\x82\x93\x82\x94\x82\x8f\x82\x8e\x82\x85\x81@\x82\x94\x82\x81\x82\x82\x82\x8c\x82\x85\x82\x94\x81@\x82\x8c\x82\x85\x82\x81\x82\x8e\x82\x93\x81@\x82\x81\x82\x87\x82\x81\x82\x89\x82\x8e\x82\x93\x82\x94";
const char data_800B2328[28] = "\x82h\x82\x94\x81""f\x82\x93\x81@\x82k\x82\x8f\x82\x83\x82\x8b\x82\x85\x82\x84\x81""D";
const char data_800B2344[56] = "\x82s\x82\x88\x82\x85\x82\x92\x82\x85\x81@\x82\x89\x82\x93\x81@\x82\x8e\x82\x8f\x82\x94\x82\x88\x82\x89\x82\x8e\x82\x87\x81@\x82\x89\x82\x8e\x82\x93\x82\x89\x82\x84\x82\x85\x81""D";
