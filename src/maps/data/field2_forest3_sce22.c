#include "maps/map.h"

int AddEffects_800B22D8(MapFx* fx);
void FxSprite_800B2464(MapEnt* ent);
void FxModel_800B25D8(MapEnt* ent);
void MapInit_800B2800(int phase);
void FxInit_800B286C(MapEnt* ent);
void SfxLoopInit_800B2924(MapEnt* ent);
void SfxLoop_800B2958(MapEnt* ent);
void StartMapTask_800B29A8(void);
void MapTaskLoad_800B29D8(EventEntry* entry, int* st);
void MapTask_800B2A70(EventEntry* entry, int* st);
int LeaveArea_800B2B28(MapEvent* ev, int area);
int EnterArea_800B2C44(MapEvent* ev, int area, int prev);
void RequestModels_800B2D4C(MapEvent* ev);
void EntityTask_800B2E1C(EventEntry* entry, MapEnt* ent);
int AddEntity_800B2E9C(void* ev);
int FxFrame_800B2FC8(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B304C(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B3118(MapFx* fx, MapFxWork* w);

extern const int unknown_800B22C0[1];
extern const MapFxInits fxInits_800B22C4;
extern MapFx effects_800B3260[3];
extern MapFx effects_800B32E4[2];
extern MapFx effects_800B333C[2];
extern MapFx effects_800B3394[2];
extern MapFx effects_800B33EC[3];
extern MapFx effects_800B3470[3];
extern MapFx effects_800B34F4[3];
extern MapFx effects_800B3578[2];
extern MapFx effects_800B35D0[2];
extern MapFx effects_800B3628[2];
extern int data_800B3680[4];
extern MapEvent event_800B3690;
extern MapInstr script_800B36A4[73];
extern MapEvent events_800B3B34[2];

MapFx effects_800B3260[3] = {
    { 1, 0xA4, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, 0x14, 0, 0, -1, 0, 0, 0 },
    { 0, 0x164, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, 0x14, 0, 0, -1, 0x38, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B32E4[2] = {
    { 0, 0x165, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, 0, 0, 0, -1, 0x38, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B333C[2] = {
    { 0, 0x166, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, 3, 0, 0, -1, 0x38, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3394[2] = {
    { 0, 0x167, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, 0, 0, 0, -1, 0x38, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B33EC[3] = {
    { 1, 0xA5, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0xB4, 0, 0, 0, 0, -1, 0, 0, 0 },
    { 0, 0x168, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0xB4, 0, 0, 0, 0, -1, 0x38, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3470[3] = {
    { 1, 0xA6, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 5, 0, 0, -1, 0, 0, 0 },
    { 0, 0x169, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 5, 0, 0, -1, 0x38, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B34F4[3] = {
    { 0, 0x16A, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, 0, 0, 0, -1, 0x38, 0, 0 },
    { 0, 0x16B, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0x1E, 4, 0, 0, -1, 0x38, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3578[2] = {
    { 1, 0xA7, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, 0, 0, 0, -1, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B35D0[2] = {
    { 1, 0xA8, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, 4, 0, 0, -1, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3628[2] = {
    { 1, 0xA9, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, 0, 0, 0, -1, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
int data_800B3680[4] = {
    0x8FC, 0, -0x21FC, 0,
};
MapEvent event_800B3690 = { -1, 0xD, 0, 4, { (void*)SfxLoopInit_800B2924 } };
MapInstr script_800B36A4[73] = {
    { 5, 0, 0, 0 },
    { 7, 0, 1, 0 },
    { 0x5E, 0, 1, 0 },
    { 0x67, 5, 1, 0 },
    { 0x13, 0, 0, MAP_REF(data_800B3680) },
    { 0x48, 0, 0x168, 5 },
    { 0x55, 0, 1, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B3260) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B22D8) },
    { 0x67, 4, 0x78, 0 },
    { 0x67, 6, 0, 0 },
    { 0xC, 0, 0x5A, 0 },
    { 0x56, 0, 1, 0 },
    { 0x55, 0, 2, 0 },
    { 0x49, 0, 0x1600169, 1 },
    { 0xC, 0, 0x96, 0 },
    { 0x56, 0, 2, 0 },
    { 0x55, 0, 3, 0 },
    { 0x49, 0, 0x161016A, 1 },
    { 0xC, 0, 0x5A, 0 },
    { 0x67, 0xD, 0x1E, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B32E4) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B22D8) },
    { 0xC, 0, 0x1E, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B333C) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B22D8) },
    { 0xC, 0, 0x1E, 0 },
    { 0x49, 0, 0x162016B, 1 },
    { 0xC, 0, 0x5A, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B3394) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B22D8) },
    { 0xC, 0, 0x1E, 0 },
    { 0x11, 0, 0, MAP_REF(event_800B3690) },
    { 0x4B, 0, 0, MAP_REF(effects_800B33EC) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B22D8) },
    { 0x49, 0, 0x163016C, 1 },
    { 0xC, 0, 0x3C, 0 },
    { 0x56, 0, 3, 0 },
    { 0x55, 0, 5, 0 },
    { 0xC, 0, 0xA0, 0 },
    { 0x56, 0, 5, 0 },
    { 0x55, 0, 4, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B3470) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B22D8) },
    { 0xC, 0, 0x96, 0 },
    { 0x67, 0xD, 0x1E, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B34F4) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B22D8) },
    { 0xC, 0, 0x3C, 0 },
    { 0x56, 0, 4, 0 },
    { 0x55, 0, 6, 0 },
    { 0xC, 0, 0x5A, 0 },
    { 0x67, 0xD, 0x19, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B3578) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B22D8) },
    { 0xC, 0, 5, 0 },
    { 0x49, 0, 0x164016D, 1 },
    { 0xC, 0, 0x19, 0 },
    { 0x2E, 0, -2, MAP_REF(event_800B3690) },
    { 0x56, 0, 6, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B35D0) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B22D8) },
    { 0xC, 0, 0x96, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B3628) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B22D8) },
    { 0xC, 0, 0x1E, 0 },
    { 0x67, 3, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x51, 5, 0x30014, 0x107 },
    { 0x53, 0, 0x107, 0 },
    { 8, 0, 1, 0 },
    { 4, 0, 0, 0 },
    { 3, 0, 0, 0 },
};
MapEvent events_800B3B34[2] = {
    { -1, 8, script_800B36A4, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
const int unknown_800B22C0[1] = {
    0x12F,
};
const MapFxInits fxInits_800B22C4 = { { FxSprite_800B2464, FxModel_800B25D8, 0, 0, 0 } };
