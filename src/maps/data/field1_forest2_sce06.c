#include "maps/map.h"

void Warp_800B2390(MapEnt* ent);
void SlidingDoor_800B24B4(MapEnt* ent);
void TileDoor_800B27A4(MapEnt* ent);
void Lock_800B2900(MapEnt* ent);
void MapInit_800B2AEC(int phase);
void SlidingDoorInit_800B2B5C(MapEnt* ent);
void TileDoorInit_800B2BF0(MapEnt* ent);
void LockInit_800B2C84(MapEnt* ent);
void StartMapTask_800B2CF8(void);
void MapTaskLoad_800B2D28(EventEntry* entry, int* st);
void MapTask_800B2DC0(EventEntry* entry, int* st);
int LeaveArea_800B2E78(MapEvent* ev, int area);
int EnterArea_800B2F94(MapEvent* ev, int area, int prev);
void RequestModels_800B309C(MapEvent* ev);
int AddEntity_800B316C(void* ev);
int FindTileLayer_800B3298(int id);
void SetTileLayerFrame_800B3350(int layer, int frame);
int IsTileLayerDone_800B336C(int layer, int frame);
void EntityTask_800B33D4(EventEntry* entry, MapEnt* ent);

extern const char unknown_800B22C0[4];
extern const char data_800B22C4[60];
extern const char data_800B2300[52];
extern const char data_800B2334[68];
extern const char data_800B2378[24];
extern MapWarp warp_800B3454;
extern MapWarp warp_800B346C;
extern MapEvent event_800B3484[4];
extern MapTileDoor data_800B34D4;
extern MapInstr script_800B34E4[12];
extern MapInstr script_800B35A4[6];
extern int text_800B3604[3];
extern int text_800B3610[3];
extern MapLockPoint data_800B361C[3];
extern MapLock data_800B3664;
extern MapEvent events_800B3680[6];
extern int data_800B36F8[3];
extern int data_800B3704[28];
extern int data_800B3774[32];
extern int data_800B37F4[24];

MapWarp warp_800B3454 = { { 0x43, -0x70, 0xEA6 }, 0x4000, 0, 0, { 4, 2, 4 } };
MapWarp warp_800B346C = { { -0x25, 0, -0x1211 }, 0x4000, 0, 1, { 4, 2, 7 } };
MapEvent event_800B3484[4] = {
    { -1, 0, 0, 0, { (void*)0xFFFF0000 } },
    { 0x6F, -1, 0, -0x1A9, { 0 } },
    { 0x320, 0, (void*)0xFFFFFD2B, 1, { (void*)0x1A9 } },
    { 0, 0x320, 0, 0x2D5, { (void*)0x31002D } },
};
MapTileDoor data_800B34D4 = { 0x6F, 0x70, 0x34, { 0, 0, 0, 0xFF, 1, 6, 1, 0xFF } };
MapInstr script_800B34E4[12] = {
    { 5, 0, 0, 0 },
    { 7, 0, 1, 0 },
    { 0x3E, -1, 4, 5 },
    { 0xC, 0, 0xF, 0 },
    { 0x2E, 1, 0, MAP_REF(data_800B34D4) },
    { 0xC, 0, 0xF, 0 },
    { 0x68, 1, 0x12, 0 },
    { 0x2E, 1, 0, MAP_REF(event_800B3484) },
    { 0x20, 0, 0x6F, 0 },
    { 8, 0, 1, 0 },
    { 4, 0, 0, 0 },
    { 3, 0, 0, 0 },
};
MapInstr script_800B35A4[6] = {
    { 5, 0, 0, 0 },
    { 7, 0, 1, 0 },
    { 0x3B, 0, 0, -1 },
    { 8, 0, 1, 0 },
    { 4, 0, 0, 0 },
    { 3, 0, 0, 0 },
};
int text_800B3604[3] = {
    MAP_REF(data_800B22C4), 0, 0,
};
int text_800B3610[3] = {
    MAP_REF(data_800B2334), MAP_REF(data_800B2300), 0,
};
MapLockPoint data_800B361C[3] = {
    { 3, { 0, 0, 0x377 }, text_800B3604, 0 },
    { 2, { 0, 0, 0 }, text_800B3610, 1 },
    { -1, { 0, 0, 0 }, 0, 0 },
};
MapLock data_800B3664 = { data_800B361C, 0x6F, 0x13, script_800B34E4, script_800B35A4, event_800B3484, 0 };
MapEvent events_800B3680[6] = {
    { -1, 1, &warp_800B3454, 0, { Warp_800B2390 } },
    { -1, 1, &warp_800B346C, 0, { Warp_800B2390 } },
    { -1, 2, event_800B3484, 0xC, { SlidingDoorInit_800B2B5C } },
    { 1, 0x10, &data_800B34D4, 0x10, { TileDoorInit_800B2BF0 } },
    { -1, 0xD, &data_800B3664, 0xC, { LockInit_800B2C84 } },
    { 0, 0x12, 0, 0, { 0 } },
};
int data_800B36F8[3] = {
    MAP_REF(data_800B2378), 0, 0,
};
int data_800B3704[28] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x30, 0, 1, 0, 0x31, 0, 2, 0,
    8, 0, 1, 0, 4, 0, 0, 0,
    3, 0, 0, 0,
};
int data_800B3774[32] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x3E, -1, 4, 5, 0x30, 0, 1, 0,
    0x31, 0, 2, 0, 8, 0, 1, 0,
    4, 0, 0, 0, 3, 0, 0, 0,
};
int data_800B37F4[24] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x3B, 0, 0, MAP_REF(data_800B36F8), 8, 0, 1, 0,
    4, 0, 0, 0, 3, 0, 0, 0,
};
const char unknown_800B22C0[4] = "\xa5";
const char data_800B22C4[60] = "\x82s\x82\x88\x82\x85\x81@\x82\x84\x82\x8f\x82\x8f\x82\x92\x81@\x82\x97\x82\x8f\x82\x8e\x81""f\x82\x94\x81@\x82\x82\x82\x95\x82\x84\x82\x87\x82\x85\x81@\x82\x81\x82\x94\x81@\x82\x81\x82\x8c\x82\x8c\x81""D";
const char data_800B2300[52] = "\x82\x84\x82\x95\x82\x87\x81@\x82\x95\x82\x90\x81@\x82\x86\x82\x92\x82\x8f\x82\x8d\x81@\x82\x81\x81@\x82\x88\x82\x8f\x82\x8c\x82\x85\x81@\x82\x88\x82\x85\x82\x92\x82\x85\x81""D";
const char data_800B2334[68] = "\x82h\x82\x94\x81@\x82\x8c\x82\x8f\x82\x8f\x82\x8b\x82\x93\x81@\x82\x8c\x82\x89\x82\x8b\x82\x85\x81@\x82\x93\x82\x8f\x82\x8d\x82\x85\x82\x94\x82\x88\x82\x89\x82\x8e\x82\x87\x81@\x82\x88\x82\x81\x82\x93\x81@\x82\x82\x82\x85\x82\x85\x82\x8e";
const char data_800B2378[24] = "\x82h\x82\x94\x81""f\x82\x93\x81@\x82k\x82\x8f\x82\x83\x82\x8b\x82\x85\x82\x84";
