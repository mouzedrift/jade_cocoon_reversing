#include "maps/map.h"

void Warp_800B22F4(MapEnt* ent);
void TileDoor_800B2418(MapEnt* ent);
int AddEffects_800B2574(MapFx* fx);
void FxModel_800B2700(MapEnt* ent);
void EffectSpot_800B2928(MapEnt* ent);
void SavePoint_800B2A9C(MapEnt* ent);
void MapInit_800B2F0C(int phase);
void TileDoorInit_800B2F7C(MapEnt* ent);
void FxInit_800B3010(MapEnt* ent);
void FxMdec_800B30C8(MapEnt* ent);
void EffectSpotInit_800B31B4(MapEnt* ent);
void SavePointInit_800B31F8(MapEnt* ent);
void StartMapTask_800B3238(void);
void MapTaskLoad_800B3268(EventEntry* entry, int* st);
void MapTask_800B3300(EventEntry* entry, int* st);
int LeaveArea_800B33B8(MapEvent* ev, int area);
int EnterArea_800B34D4(MapEvent* ev, int area, int prev);
void RequestModels_800B35DC(MapEvent* ev);
void EntityTask_800B36AC(EventEntry* entry, MapEnt* ent);
int AddEntity_800B372C(void* ev);
int FindTileLayer_800B3858(int id);
void SetTileLayerFrame_800B3910(int layer, int frame);
int IsTileLayerDone_800B392C(int layer, int frame);
int FxFrame_800B3994(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B3A18(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B3AE4(MapFx* fx, MapFxWork* w);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[20];
extern const MapFxInits fxInits_800B22D8;
extern const MapRgb savePointDim_800B22EC;
extern const MapRgb savePointLit_800B22F0;
extern MapSavePoint savePoint_800B3C2C;
extern MapWarp warp_800B3C3C;
extern MapWarp warp_800B3C54;
extern MapFx effects_800B3C6C[3];
extern MapFx effects_800B3CF0[3];
extern MapEffectSpot data_800B3D74;
extern MapEffectSpot data_800B3DA0;
extern MapTileDoor data_800B3DCC;
extern MapEvent events_800B3DDC[7];
extern int data_800B3E68[96];

MapSavePoint savePoint_800B3C2C = { { 0xB1, 0, -0x19F }, str_800B22C4 };
MapWarp warp_800B3C3C = { { -0x44, 0, 0x947 }, 0, 0, 0, { 4, 3, 2 } };
MapWarp warp_800B3C54 = { { -0x83, 0, -0x17CD }, 0, 0, 2, { 4, 3, 0x10 } };
MapFx effects_800B3C6C[3] = {
    { 1, 0x81, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, 0, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3CF0[3] = {
    { 1, 0x81, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 1, 1, 1, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapEffectSpot data_800B3D74 = { 0x29, 1, { 0x3B, -0xFA, 0x1D7 }, { -0xF, 0, 0x396 }, 0, { effects_800B3C6C, effects_800B3CF0 } };
MapEffectSpot data_800B3DA0 = { 0x29, 3, { 0x3B, -0xFA, 0x1D7 }, { -0xF, 0, 0x4E }, -0x800, { effects_800B3CF0, effects_800B3C6C } };
MapTileDoor data_800B3DCC = { 0x29, 0xA, 0xFF, { 0, 0, 0, 0xFF, 0, 0xA, 1, 0xFF } };
MapEvent events_800B3DDC[7] = {
    { -1, 1, &warp_800B3C3C, 0, { Warp_800B22F4 } },
    { -1, 1, &warp_800B3C54, 0, { Warp_800B22F4 } },
    { 1, 0x10, &data_800B3DCC, 0x10, { TileDoorInit_800B2F7C } },
    { -1, 0xD, &data_800B3D74, 0xC, { EffectSpotInit_800B31B4 } },
    { -1, 0xD, &data_800B3DA0, 0xC, { EffectSpotInit_800B31B4 } },
    { -1, 0xC, &savePoint_800B3C2C, 0xC, { SavePointInit_800B31F8 } },
    { 0, 0x12, 0, 0, { 0 } },
};
int data_800B3E68[96] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x67, 0xC, 5, 0, 0x30, 0, 1, 0,
    0x31, 0, 1, 0, 0xC, 0, 0x1E, 0,
    0x67, 5, 0x1E, 0, 0xC, 0, 0x3C, 0,
    0x30, 0, 2, 0, 0xC, 0, 2, 0,
    0x1A, 1, 0, 0, 0x67, 0, 0, 0,
    0x67, 0xC, 5, 0, 0x30, 0, 1, 0,
    0x31, 0, 1, 0, 0xC, 0, 0x1E, 0,
    0x67, 5, 0x1E, 0, 0xC, 0, 0x3C, 0,
    0x1A, 1, 1, 0, 0x67, 4, 0x1E, 0,
    0x67, 6, 0, 0, 8, 0, 1, 0,
    4, 0, 0, 0, 3, 0, 0, 0,
};
const char unknown_800B22C0[4] = "\xc6";
const char str_800B22C4[20] = "\x82r\x82o\x82h\x82""c\x82""d\x82q\x81@\x82R";
const MapFxInits fxInits_800B22D8 = { { 0, FxModel_800B2700, 0, FxMdec_800B30C8, 0 } };
const MapRgb savePointDim_800B22EC = { 0x80, 0x40, 0x20, 0 };
const MapRgb savePointLit_800B22F0 = { 0x20, 0x40, 0x80, 0 };
