#include "maps/map.h"

void Warp_800B23D0(MapEnt* ent);
void TileDoor_800B24F4(MapEnt* ent);
void Chest_800B2650(MapEnt* ent);
void ChestDraw_800B2844(MapChest* chest, MapChestWork* w);
void MapInit_800B2B10(int phase);
void SwitchInit_800B2B80(MapEnt* ent);
void Switch_800B2BDC(MapEnt* ent);
void TileDoorInit_800B2C94(MapEnt* ent);
void WallFlagsInit_800B2D28(MapEnt* ent);
void ChestInit_800B2DC0(MapEnt* ent);
int ChestShut_800B2EA0(MapEnt* ent);
int ChestTake_800B2EAC(void* arg);
int ChestText_800B2F30(void* arg);
int ChestCheck_800B2F68(MapEnt* ent);
void StartMapTask_800B2FA8(void);
void MapTaskLoad_800B2FD8(EventEntry* entry, int* st);
void MapTask_800B3070(EventEntry* entry, int* st);
int LeaveArea_800B3128(MapEvent* ev, int area);
int EnterArea_800B3244(MapEvent* ev, int area, int prev);
void RequestModels_800B334C(MapEvent* ev);
int AddEntity_800B341C(void* ev);
int FindTileLayer_800B3548(int id);
void SetTileLayerFrame_800B3600(int layer, int frame);
int IsTileLayerDone_800B361C(int layer, int frame);
void ChestKind1_800B3684(MapChest* chest, MapChestWork* w);
void ChestKind2_800B368C(MapChest* chest, MapChestWork* w);
void EntityTask_800B3694(EventEntry* entry, MapEnt* ent);

extern const char unknown_800B22C0[4];
extern const char data_800B22C4[40];
extern const char data_800B22EC[44];
extern const char data_800B2318[56];
extern const char data_800B2350[28];
extern const char data_800B236C[56];
extern int text_800B3714[4];
extern MapChest chest_800B3724;
extern MapWarp warp_800B376C;
extern MapWarp warp_800B3784;
extern MapWarp warp_800B379C;
extern MapWarp warp_800B37B4;
extern MapSwitch data_800B37CC;
extern MapTileDoor data_800B37E4;
extern MapWallFlag data_800B37F4[2];
extern MapEvent events_800B3804[9];
extern int data_800B38B8[3];
extern int data_800B38C4[3];
extern int data_800B38D0[212];

int text_800B3714[4] = {
    MAP_REF(data_800B2318), MAP_REF(data_800B22EC), MAP_REF(data_800B22C4), 0,
};
MapChest chest_800B3724 = { 0x3C, -1, 3, 3, 6, { -0x310, -0x99, 0x2EE }, 0, text_800B3714, 0, { 0x90000, 1, 0xFFFF, 0, 0xFFFF, 0 }, { 0, -1 } };
MapWarp warp_800B376C = { { 0x23F, 0, 0x69D }, 0x66, 0, 0, { 4, 1, 0xA } };
MapWarp warp_800B3784 = { { -0x4B, -0x19, -0x1D33 }, -0x400, 0, 5, { 4, 1, 2 } };
MapWarp warp_800B379C = { { -0x36B, 0, -0x7D }, 0x2AA, 0, 3, { 4, 1, 2 } };
MapWarp warp_800B37B4 = { { -0x57, -0xA2, -0x3B9 }, 0x2AA, 0, 4, { 4, 1, 3 } };
MapSwitch data_800B37CC = { 0x6C, 0, 1, { 0x68A, 0, -0xE47 } };
MapTileDoor data_800B37E4 = { 0x6C, 0xC8, 0x17, { 0, 0, 0, 0xFF, 1, 7, 0, 0xFF } };
MapWallFlag data_800B37F4[2] = {
    { 0x6C, 0, 0 },
    { 0, 2, 0 },
};
MapEvent events_800B3804[9] = {
    { -1, 3, &data_800B37CC, 4, { SwitchInit_800B2B80 } },
    { 1, 0x10, &data_800B37E4, 0x10, { TileDoorInit_800B2C94 } },
    { -1, 9, data_800B37F4, 0, { WallFlagsInit_800B2D28 } },
    { -1, 1, &warp_800B376C, 0, { Warp_800B23D0 } },
    { -1, 1, &warp_800B3784, 0, { Warp_800B23D0 } },
    { -1, 1, &warp_800B379C, 0, { Warp_800B23D0 } },
    { -1, 1, &warp_800B37B4, 0, { Warp_800B23D0 } },
    { -1, 4, &chest_800B3724, 0x18, { ChestInit_800B2DC0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
int data_800B38B8[3] = {
    MAP_REF(data_800B2350), 0, 0,
};
int data_800B38C4[3] = {
    MAP_REF(data_800B236C), 0, 0,
};
int data_800B38D0[212] = {
    9, 0, 0, 0, 5, 0, 0, 0,
    7, 0, 1, 0, 0x30, 0, 4, 0,
    0x31, 0, 4, 0, 0x4B, 0, 0, 0,
    0x4E, 0, 0, MAP_REF(ChestShut_800B2EA0), 0xA, 0, 0x70, 0,
    0xA, 0, 0x10, 0, 9, 0, 0x10, 0,
    0x30, 0, 4, 0, 0x31, 0, 4, 0,
    0x4B, 0, 0, 0, 0x4E, 0, 0, MAP_REF(ChestTake_800B2EAC),
    0xA, 0, 0x20, 0, 0xA, 0, 0x30, 0,
    0xA, 0, 0x40, 0, 9, 0, 0x20, 0,
    0x3E, -1, 4, 0, 0xA, 0, 0x50, 0,
    9, 0, 0x30, 0, 0x3B, 0, 0, -1,
    0xA, 0, 0xFF, 0, 9, 0, 0x40, 0,
    0x3B, 0, 0, -1, 0xA, 0, 0x50, 0,
    9, 0, 0x50, 0, 0x30, 0, 4, 0,
    0x31, 0, 4, 0, 0x4B, 0, 0, 0,
    0x4E, 0, 0, MAP_REF(ChestCheck_800B2F68), 0xA, 0, 0x60, 0,
    0xA, 0, 0xFF, 0, 9, 0, 0x60, 0,
    0x30, 0, 3, 0, 0x31, 0, 3, 0,
    0x3C, 3, 0, 0, 0x30, 0, 1, 0,
    0x31, 0, 1, 0, 0x30, 0, 2, 0,
    0x31, 0, 2, 0, 0xA, 0, 0xFF, 0,
    9, 0, 0x70, 0, 0x30, 0, 4, 0,
    0x31, 0, 4, 0, 0x4B, 0, 0, 0,
    0x4E, 0, 0, MAP_REF(ChestText_800B2F30), 0x3B, 0, 0, -1,
    0xA, 0, 0xFF, 0, 9, 0, 0xFF, 0,
    8, 0, 1, 0, 4, 0, 0, 0,
    3, 0, 0, 0,
};
const char unknown_800B22C0[4] = "\x93";
const char data_800B22C4[40] = "\x82\x83\x82\x8f\x82\x96\x82\x85\x82\x92\x82\x89\x82\x8e\x82\x87\x81@\x82\x81\x81@\x82\x82\x82\x8f\x82\x95\x82\x8c\x82\x84\x82\x85\x82\x92\x81""D";
const char data_800B22EC[44] = "\x82\x82\x82\x85\x82\x94\x82\x97\x82\x85\x82\x85\x82\x8e\x81@\x82\x8c\x82\x85\x82\x81\x82\x96\x82\x85\x82\x93\x81@\x82\x8f\x82\x86\x81@\x82\x89\x82\x96\x82\x99";
const char data_800B2318[56] = "\x82`\x82\x8e\x81@\x82\x8f\x82\x8c\x82\x84\x81@\x82\x83\x82\x8c\x82\x8f\x82\x94\x82\x88\x81@\x82\x93\x82\x81\x82\x83\x82\x8b\x81@\x82\x89\x82\x93\x81@\x82\x93\x82\x94\x82\x95\x82\x83\x82\x8b";
const char data_800B2350[28] = "\x82h\x82\x94\x81""f\x82\x93\x81@\x82k\x82\x8f\x82\x83\x82\x8b\x82\x85\x82\x84\x81""D";
const char data_800B236C[56] = "\x82s\x82\x88\x82\x85\x82\x92\x82\x85\x81@\x82\x89\x82\x93\x81@\x82\x8e\x82\x8f\x82\x94\x82\x88\x82\x89\x82\x8e\x82\x87\x81@\x82\x89\x82\x8e\x82\x93\x82\x89\x82\x84\x82\x85\x81""D";
