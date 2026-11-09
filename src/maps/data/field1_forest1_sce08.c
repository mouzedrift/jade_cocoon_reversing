#include "maps/map.h"

void Warp_800B2420(MapEnt* ent);
int AddEffects_800B2544(MapFx* fx);
int fn_800B26D0();
void FxModel_800B2844(MapEnt* ent);
int fn_800B2A6C();
int fn_800B2D54();
void Chest_800B31C4(MapEnt* ent);
void ChestDraw_800B33B8(MapChest* chest, MapChestWork* w);
void MapInit_800B3684(int phase);
void FxInit_800B36F4(MapEnt* ent);
int fn_800B37AC();
int fn_800B37E8();
int fn_800B3920();
void ChestInit_800B3960(MapEnt* ent);
int ChestShut_800B3A40(MapEnt* ent);
int ChestTake_800B3A4C(void* arg);
int ChestText_800B3AD0(void* arg);
int ChestCheck_800B3B08(MapEnt* ent);
void StartMapTask_800B3B48(void);
void MapTaskLoad_800B3B78(EventEntry* entry, int* st);
void MapTask_800B3C10(EventEntry* entry, int* st);
int LeaveArea_800B3CC8(MapEvent* ev, int area);
int EnterArea_800B3DE4(MapEvent* ev, int area, int prev);
void RequestModels_800B3EEC(MapEvent* ev);
void EntityTask_800B3FBC(EventEntry* entry, MapEnt* ent);
int AddEntity_800B403C(void* ev);
int FxFrame_800B4168(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B41EC(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B42B8(MapFx* fx, MapFxWork* w);
void ChestKind1_800B4400(MapChest* chest, MapChestWork* w);
void ChestKind2_800B4408(MapChest* chest, MapChestWork* w);

extern const char unknown_800B22C0[4];
extern const char data_800B22C4[44];
extern const char data_800B22F0[72];
extern const char data_800B2338[20];
extern const MapFxInits fxInits_800B234C;
extern const int data_800B2360[4];
extern const int data_800B2370[5];
extern const char data_800B2398[4];
extern const char data_800B239C[4];
extern const char data_800B23A0[28];
extern const char data_800B23BC[56];
extern int text_800B4410[4];
extern MapChest chest_800B4420;
extern int data_800B4468[4];
extern MapWarp warp_800B4478;
extern int data_800B4490[10];
extern MapEvent events_800B44B8[5];
extern int data_800B451C[66];
extern int data_800B4624[33];
extern int data_800B46A8[72];
extern int data_800B47C8[56];
extern int data_800B48A8[3];
extern int data_800B48B4[3];
extern int data_800B48C0[212];

int text_800B4410[4] = {
    MAP_REF(data_800B22F0), MAP_REF(data_800B22C4), 0, 0,
};
MapChest chest_800B4420 = { 0x42, -1, 3, 3, 3, { 0x364, 0, 0x190 }, 0, text_800B4410, 0, { 0x150005, 1, 0xFFFF, 0, 0xFFFF, 0 }, { 0, -1 } };
int data_800B4468[4] = {
    -0x87, 0, -0xFF, MAP_REF(data_800B2338),
};
MapWarp warp_800B4478 = { { 0x32B, 0, -0x10FE }, 0x4000, 0, 0, { 4, 1, 7 } };
int data_800B4490[10] = {
    0x15, 0x662, -0xB2, 0, 0, -0x274, -0xAB, 0xF6,
    0x4CC, 0xA0002,
};
MapEvent events_800B44B8[5] = {
    { -1, 1, &warp_800B4478, 0, { Warp_800B2420 } },
    { -1, 0x11, data_800B4490, 0xC, { (void*)fn_800B37AC } },
    { -1, 0xC, data_800B4468, 0xC, { (void*)fn_800B3920 } },
    { -1, 4, &chest_800B4420, 0x18, { ChestInit_800B3960 } },
    { 0, 0x12, 0, 0, { 0 } },
};
int data_800B451C[66] = {
    0x14D0000, 0, 0, 0, 0, 0, 0xA7, 0,
    -0x10000, 0x30, MAP_REF(fn_800B37E8), 0x610001, 0, 0, 0, 0,
    0, 0x6300B4, 0, -0x10000, 0, MAP_REF(fn_800B37E8), 0x620001, 0,
    0, 0, 0, 0, 0x9F0079, 0, -0x10000, 0,
    MAP_REF(fn_800B37E8), 0x630001, 0, 0, 0, 0, 0, 0x63006A,
    0, -0x10000, 0, MAP_REF(fn_800B37E8), 0x640001, 0, 0, 0,
    0, 0, 0xD7003C, 0, -0x10000, 0, MAP_REF(fn_800B37E8), 5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};
int data_800B4624[33] = {
    0x14E0000, 0, 0, 0, 0, 0, 0x66001E, 0,
    -0x10000, 0x30, MAP_REF(fn_800B37E8), 0x650001, 0, 0, 0, 0,
    0, 0x1E005B, 0, -0x10000, 0, MAP_REF(fn_800B37E8), 5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0,
};
int data_800B46A8[72] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x4B, 0, 0, MAP_REF(data_800B451C), 0x4D, 0, 1, MAP_REF(AddEffects_800B2544),
    0x30, 0, 0, 0, 0xC, 0, 0xBD, 0,
    0x1A, 1, 0, 0, 0xC, 0, 0x13, 0,
    0x30, 0, 1, 0, 0xC, 0, 0xB, 0,
    0x30, 0, 2, 0, 0xC, 0, 0x3D, 0,
    0x67, 3, 0x3C, 0, 0x67, 6, 0, 0,
    0x30, 0, 3, 0, 8, 0, 1, 0,
    4, 0, 0, 0, 3, 0, 0, 0,
};
int data_800B47C8[56] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x1A, 1, 0, 0, 0x67, 2, 0x1E, 0,
    0x4B, 0, 0, MAP_REF(data_800B4624), 0x4D, 0, 1, MAP_REF(AddEffects_800B2544),
    0xC, 0, 0x49, 0, 0x30, 0, 4, 0,
    0xC, 0, 0x29, 0, 0x1A, 1, 1, 0,
    0xC, 0, 0x12, 0, 8, 0, 1, 0,
    4, 0, 0, 0, 3, 0, 0, 0,
};
int data_800B48A8[3] = {
    MAP_REF(data_800B23A0), 0, 0,
};
int data_800B48B4[3] = {
    MAP_REF(data_800B23BC), 0, 0,
};
int data_800B48C0[212] = {
    9, 0, 0, 0, 5, 0, 0, 0,
    7, 0, 1, 0, 0x30, 0, 4, 0,
    0x31, 0, 4, 0, 0x4B, 0, 0, 0,
    0x4E, 0, 0, MAP_REF(ChestShut_800B3A40), 0xA, 0, 0x70, 0,
    0xA, 0, 0x10, 0, 9, 0, 0x10, 0,
    0x30, 0, 4, 0, 0x31, 0, 4, 0,
    0x4B, 0, 0, 0, 0x4E, 0, 0, MAP_REF(ChestTake_800B3A4C),
    0xA, 0, 0x20, 0, 0xA, 0, 0x30, 0,
    0xA, 0, 0x40, 0, 9, 0, 0x20, 0,
    0x3E, -1, 4, 0, 0xA, 0, 0x50, 0,
    9, 0, 0x30, 0, 0x3B, 0, 0, -1,
    0xA, 0, 0xFF, 0, 9, 0, 0x40, 0,
    0x3B, 0, 0, -1, 0xA, 0, 0x50, 0,
    9, 0, 0x50, 0, 0x30, 0, 4, 0,
    0x31, 0, 4, 0, 0x4B, 0, 0, 0,
    0x4E, 0, 0, MAP_REF(ChestCheck_800B3B08), 0xA, 0, 0x60, 0,
    0xA, 0, 0xFF, 0, 9, 0, 0x60, 0,
    0x30, 0, 3, 0, 0x31, 0, 3, 0,
    0x3C, 3, 0, 0, 0x30, 0, 1, 0,
    0x31, 0, 1, 0, 0x30, 0, 2, 0,
    0x31, 0, 2, 0, 0xA, 0, 0xFF, 0,
    9, 0, 0x70, 0, 0x30, 0, 4, 0,
    0x31, 0, 4, 0, 0x4B, 0, 0, 0,
    0x4E, 0, 0, MAP_REF(ChestText_800B3AD0), 0x3B, 0, 0, -1,
    0xA, 0, 0xFF, 0, 9, 0, 0xFF, 0,
    8, 0, 1, 0, 4, 0, 0, 0,
    3, 0, 0, 0,
};
const char unknown_800B22C0[4] = "\x9b";
const char data_800B22C4[44] = "\x82\x82\x82\x95\x82\x92\x82\x89\x82\x85\x82\x84\x81@\x82\x89\x82\x8e\x81@\x82\x94\x82\x88\x82\x85\x81@\x82\x87\x82\x92\x82\x8f\x82\x95\x82\x8e\x82\x84\x81""D";
const char data_800B22F0[72] = "\x82`\x81@\x82\x8a\x82\x85\x82\x97\x82\x85\x82\x8c\x81@\x82\x8e\x82\x85\x82\x83\x82\x8b\x82\x8c\x82\x81\x82\x83\x82\x85\x81@\x82\x8f\x82\x86\x81@\x82\x8c\x82\x89\x82\x85\x82\x93\x81@\x82\x90\x82\x81\x82\x92\x82\x94\x82\x89\x82\x81\x82\x8c\x82\x8c\x82\x99";
const char data_800B2338[20] = "\x82""a\x82""d\x82""d\x82s\x82k\x82""d\x81@\x82P";
const MapFxInits fxInits_800B234C = { { (void*)fn_800B26D0, FxModel_800B2844, 0, 0, 0 } };
const int data_800B2360[4] = {
    0x70, 0x72, 0x74, 0x76,
};
const int data_800B2370[5] = {
    0x81, 0x82, 0x83, 0x84, 0,
};
const char data_800B2398[4] = "\x80@ ";
const char data_800B239C[4] = " @\x80";
const char data_800B23A0[28] = "\x82h\x82\x94\x81""f\x82\x93\x81@\x82k\x82\x8f\x82\x83\x82\x8b\x82\x85\x82\x84\x81""D";
const char data_800B23BC[56] = "\x82s\x82\x88\x82\x85\x82\x92\x82\x85\x81@\x82\x89\x82\x93\x81@\x82\x8e\x82\x8f\x82\x94\x82\x88\x82\x89\x82\x8e\x82\x87\x81@\x82\x89\x82\x8e\x82\x93\x82\x89\x82\x84\x82\x85\x81""D";
