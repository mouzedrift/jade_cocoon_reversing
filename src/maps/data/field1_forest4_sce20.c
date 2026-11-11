#include "maps/map.h"

int AddEffects_800B22C4(MapFx* fx);
void FxModel_800B2450(MapEnt* ent);
void MapInit_800B2678(int phase);
void FxInit_800B26E4(MapEnt* ent);
void CameraZoomInit_800B2788(MapEnt* ent);
void CameraZoom_800B27FC(MapEnt* ent);
int GoToEntrance_800B2864(void);
void SfxDelayLoopInit_800B28DC(MapEnt* ent);
void SfxDelayLoop_800B2918(MapEnt* ent);
void StartMapTask_800B2980(void);
void MapTaskLoad_800B29B0(EventEntry* entry, int* st);
void MapTask_800B2A48(EventEntry* entry, int* st);
int LeaveArea_800B2B00(MapEvent* ev, int area);
int EnterArea_800B2C1C(MapEvent* ev, int area, int prev);
void RequestModels_800B2D24(MapEvent* ev);
void EntityTask_800B2DF4(EventEntry* entry, MapEnt* ent);
int AddEntity_800B2E74(void* ev);
int FxFrame_800B2FA0(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B3024(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B30F0(MapFx* fx, MapFxWork* w);

extern const char unknown_800B22C0[4];
extern MapFx effects_800B3238[2];
extern MapFx effects_800B3290[5];
extern int data_800B336C[4];
extern int data_800B337C[3];
extern MapInstr script_800B3388[21];
extern MapEvent events_800B34D8[4];
extern int event_800B3528[1];

MapFx effects_800B3238[2] = {
    { 1, 0x8E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3290[5] = {
    { 1, 0x8E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0xD3, 0, 0, 0, 0, -1, 0, 0, 0 },
    { 1, 0x8F, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0xD7, 0xB0, 0, 0, 0, -1, 0, 0, 0 },
    { 1, 0x90, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x79, 0xD8, 0, 0, 0, -1, 0, 0, 0 },
    { 1, 0x91, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x14, 0x8D, 0, 0, 0, -1, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
int data_800B336C[4] = {
    0, 0, 0, -0x800,
};
int data_800B337C[3] = {
    0, 0, -0x2710,
};
MapInstr script_800B3388[21] = {
    { 5, 0, 0, 0 },
    { 7, 0, 1, 0 },
    { 0x67, 5, 1, 0 },
    { 0x13, 0, 0, MAP_REF(data_800B336C) },
    { 0x4B, 0, 0, MAP_REF(effects_800B3238) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B22C4) },
    { 0x67, 0xD, 0x4E, 0 },
    { 0x67, 4, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x16, 0, -1, MAP_REF(data_800B337C) },
    { 0x4B, 0, 0, MAP_REF(effects_800B3290) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B22C4) },
    { 0xC, 0, 0x132, 0 },
    { 0x2E, 1, -2, MAP_REF(event_800B3528) },
    { 0x67, 0xD, 0x4E, 0 },
    { 0x67, 5, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 8, 0, 1, 0 },
    { 4, 0, 0, 0 },
    { 0x4D, 0, 0, MAP_REF(GoToEntrance_800B2864) },
    { 3, 0, 0, 0 },
};
MapEvent events_800B34D8[4] = {
    { -1, 8, script_800B3388, 0, { 0 } },
    { -1, 0xD, 0, 4, { CameraZoomInit_800B2788 } },
    { -1, 0xD, event_800B3528, 8, { SfxDelayLoopInit_800B28DC } },
    { 0, 0x12, 0, 0, { 0 } },
};
int event_800B3528[1] = {
    0,
};
const char unknown_800B22C0[4] = "\xfa";
