#include "maps/map.h"

void Warp_800B2348(MapEnt* ent);
void GateSpot_800B246C(MapEnt* ent);
int AddEffects_800B26BC(MapFx* fx);
void FxModel_800B2848(MapEnt* ent);
void SavePoint_800B2A70(MapEnt* ent);
void MapInit_800B2EE0(int phase);
void ScriptSpot_800B30C0(MapEnt* ent);
void FxInit_800B3134(MapEnt* ent);
void FxMdec_800B31EC(MapEnt* ent);
void GateSpotInit_800B32D8(MapEnt* ent);
void GateReturnInit_800B3320(MapEnt* ent);
void GateReturn_800B339C(MapEnt* ent);
void SavePointInit_800B340C(MapEnt* ent);
void StartMapTask_800B344C(void);
void MapTaskLoad_800B347C(EventEntry* entry, int* st);
void MapTask_800B3514(EventEntry* entry, int* st);
int LeaveArea_800B35CC(MapEvent* ev, int area);
int EnterArea_800B36E8(MapEvent* ev, int area, int prev);
void RequestModels_800B37F0(MapEvent* ev);
void EntityTask_800B38C0(EventEntry* entry, MapEnt* ent);
int AddEntity_800B3940(void* ev);
void MapInit_800B3A6C(int phase);
int StopLevantIfSet_800B3ADC(MapScriptSpot* spot);
int FxFrame_800B3B0C(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B3B90(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B3C5C(MapFx* fx, MapFxWork* w);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[28];
extern const MapFxInits fxInits_800B22E0;
extern const MapRgb savePointDim_800B22F4;
extern const MapRgb savePointLit_800B22F8;
extern MapSavePoint savePoint_800B3DA4;
extern int data_800B3DB4[2];
extern MapWarp warp_800B3DBC;
extern MapWarp warp_800B3DD4;
extern MapWarp warp_800B3DEC;
extern MapWarp warp_800B3E04;
extern MapFx effects_800B3E1C[3];
extern MapFx effects_800B3EA0[3];
extern MapFx effects_800B3F24[3];
extern MapFx effects_800B3FA8[3];
extern MapFx effects_800B402C[3];
extern MapFx effects_800B40B0[3];
extern MapFx effects_800B4134[3];
extern MapFx effects_800B41B8[3];
extern MapGateSpot data_800B423C;
extern MapGateSpot data_800B4270;
extern MapGateSpot data_800B42A4;
extern MapGateSpot data_800B42D8;
extern MapGateSpot data_800B430C;
extern MapGateSpot data_800B4340;
extern MapGateSpot data_800B4374;
extern MapGateSpot data_800B43A8;
extern MapGateReturn data_800B43DC;
extern MapGateReturn data_800B43E4;
extern MapGateReturn data_800B43EC;
extern MapGateReturn data_800B43F4;
extern MapGateReturn data_800B43FC;
extern MapGateReturn data_800B4404;
extern MapGateReturn data_800B440C;
extern MapGateReturn data_800B4414;
extern MapEvent events_800B441C[23];
extern int data_800B45E8[16];
extern int data_800B4628[104];
extern int data_800B47C8[24];
extern int data_800B4828[84];

MapSavePoint savePoint_800B3DA4 = { { -0x32, -0x1B4, 0x384 }, str_800B22C4 };
int data_800B3DB4[2] = {
    0x1010000, 0,
};
MapWarp warp_800B3DBC = { { -0x25, -0xE8, -0xF55 }, -0x688, 0, 5, { 4, 1, 0 } };
MapWarp warp_800B3DD4 = { { -0x1A2, 0, -0x1278 }, -0x155, 0, 9, { 4, 2, 0 } };
MapWarp warp_800B3DEC = { { -0xD4, 0, -0x7EC }, 0xE3, 0, 7, { 4, 3, 0 } };
MapWarp warp_800B3E04 = { { 0x8F, 0, -0x8D9 }, 0x200, 0, 0xB, { 4, 4, 0 } };
MapFx effects_800B3E1C[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, 0, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3EA0[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 4, 4, 4, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3F24[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 2, 2, 2, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3FA8[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 6, 6, 6, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B402C[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 1, 1, 1, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B40B0[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 5, 5, 5, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B4134[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 3, 3, 3, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B41B8[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 7, 7, 7, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapGateSpot data_800B423C = { 3, 1, { 0x88B, -0x1DE, 0xBF6 }, { 0xB1F, 9, 0xE0C }, -0xDC2, 0x11, { effects_800B3E1C, effects_800B3EA0 }, 1, 0x6A };
MapGateSpot data_800B4270 = { 4, 3, { 0x2FD, -0x1AF, 0xE93 }, { 0x481, 0x19, 0x128E }, 0xEE, 0x20, { effects_800B3F24, effects_800B3FA8 }, 2, 0x76 };
MapGateSpot data_800B42A4 = { 6, 2, { -0x2A3, -0x190, 0xE4E }, { -0x3F7, 0x73, 0x123C }, -0xE1, 0x1A, { effects_800B402C, effects_800B40B0 }, 3, 0x89 };
MapGateSpot data_800B42D8 = { 0xB, 4, { -0x753, -0x1DE, 0xB5D }, { -0xA82, 0x8F, 0xE1F }, -0x251, 0x1F, { effects_800B4134, effects_800B41B8 }, 4, 0xBA };
MapGateSpot data_800B430C = { 3, 6, { 0xA31, -0x12C, 0xD32 }, { 0x6F5, -0xBE, 0xB15 }, 0xA3A, 0x16, { effects_800B3EA0, effects_800B3E1C }, -1, -1 };
MapGateSpot data_800B4340 = { 4, 0xA, { 0x426, -0x157, 0x1187 }, { 0x264, -0x9F, 0xCCB }, -0x6E1, 0x16, { effects_800B3FA8, effects_800B3F24 }, -1, -1 };
MapGateSpot data_800B4374 = { 6, 8, { -0x3A9, -0xCE, 0x111A }, { -0x25B, -0x83, 0xD0F }, -0x8E1, 0x16, { effects_800B40B0, effects_800B402C }, -1, -1 };
MapGateSpot data_800B43A8 = { 0xB, 0xC, { -0x963, -0xB8, 0xD35 }, { -0x659, -0x83, 0xABB }, -0xA3D, 0x16, { effects_800B41B8, effects_800B4134 }, -1, -1 };
MapGateReturn data_800B43DC = { 1, effects_800B3EA0 };
MapGateReturn data_800B43E4 = { 2, effects_800B3FA8 };
MapGateReturn data_800B43EC = { 3, effects_800B40B0 };
MapGateReturn data_800B43F4 = { 4, effects_800B41B8 };
MapGateReturn data_800B43FC = { 5, effects_800B3E1C };
MapGateReturn data_800B4404 = { 6, effects_800B3F24 };
MapGateReturn data_800B440C = { 7, effects_800B402C };
MapGateReturn data_800B4414 = { 8, effects_800B4134 };
MapEvent events_800B441C[23] = {
    { -1, 0, data_800B3DB4, 0, { ScriptSpot_800B30C0 } },
    { -1, 1, &warp_800B3DBC, 0, { Warp_800B2348 } },
    { -1, 1, &warp_800B3DD4, 0, { Warp_800B2348 } },
    { -1, 1, &warp_800B3DEC, 0, { Warp_800B2348 } },
    { -1, 1, &warp_800B3E04, 0, { Warp_800B2348 } },
    { -1, 0xD, &data_800B423C, 0x10, { GateSpotInit_800B32D8 } },
    { -1, 0xD, &data_800B4270, 0x10, { GateSpotInit_800B32D8 } },
    { -1, 0xD, &data_800B42A4, 0x10, { GateSpotInit_800B32D8 } },
    { -1, 0xD, &data_800B42D8, 0x10, { GateSpotInit_800B32D8 } },
    { -1, 0xD, &data_800B430C, 0x10, { GateSpotInit_800B32D8 } },
    { -1, 0xD, &data_800B4340, 0x10, { GateSpotInit_800B32D8 } },
    { -1, 0xD, &data_800B4374, 0x10, { GateSpotInit_800B32D8 } },
    { -1, 0xD, &data_800B43A8, 0x10, { GateSpotInit_800B32D8 } },
    { -1, 0xD, &data_800B43DC, 4, { GateReturnInit_800B3320 } },
    { -1, 0xD, &data_800B43E4, 4, { GateReturnInit_800B3320 } },
    { -1, 0xD, &data_800B43EC, 4, { GateReturnInit_800B3320 } },
    { -1, 0xD, &data_800B43F4, 4, { GateReturnInit_800B3320 } },
    { -1, 0xD, &data_800B43FC, 4, { GateReturnInit_800B3320 } },
    { -1, 0xD, &data_800B4404, 4, { GateReturnInit_800B3320 } },
    { -1, 0xD, &data_800B440C, 4, { GateReturnInit_800B3320 } },
    { -1, 0xD, &data_800B4414, 4, { GateReturnInit_800B3320 } },
    { -1, 0xC, &savePoint_800B3DA4, 0xC, { SavePointInit_800B340C } },
    { 0, 0x12, 0, 0, { 0 } },
};
int data_800B45E8[16] = {
    0x4B, 0, 0, 0, 0x4D, 0, 0, MAP_REF(StopLevantIfSet_800B3ADC),
    0x58, 0, 0, 0, 3, 0, 0, 0,
};
int data_800B4628[104] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x3E, -1, 4, 5, 0x67, 0xC, 5, 0,
    0x30, 0, 1, 0, 0x31, 0, 1, 0,
    0xC, 0, 0x1E, 0, 0x67, 5, 0x1E, 0,
    0xC, 0, 0x3C, 0, 0x30, 0, 2, 0,
    0x31, 0, 2, 0, 0xC, 0, 2, 0,
    0x1A, 1, 0, 0, 0x67, 0, 0, 0,
    0x67, 0xC, 5, 0, 0x30, 0, 1, 0,
    0x31, 0, 1, 0, 0xC, 0, 0x1E, 0,
    0x67, 5, 0x1E, 0, 0xC, 0, 0x3C, 0,
    0x1A, 1, 1, 0, 0x67, 4, 0x1E, 0,
    0x67, 6, 0, 0, 8, 0, 1, 0,
    4, 0, 0, 0, 3, 0, 0, 0,
};
int data_800B47C8[24] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x3E, -1, 8, 5, 8, 0, 1, 0,
    4, 0, 0, 0, 3, 0, 0, 0,
};
int data_800B4828[84] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x67, 0xC, 5, 0, 0x30, 0, 0, 0,
    0x31, 0, 0, 0, 0xC, 0, 0x1E, 0,
    0x67, 5, 0x1E, 0, 0xC, 0, 0x3C, 0,
    0x1A, 1, 1, 0, 0x67, 4, 0x1E, 0,
    0x1F, 1, 0, 0, 0xA, 0, 1, 0,
    0xA, 0, 2, 0, 9, 0, 1, 0,
    0x67, 6, 0, 0, 9, 0, 2, 0,
    0x21, 0, 0, 0, 0x30, 0, 1, 0,
    8, 0, 1, 0, 4, 0, 0, 0,
    3, 0, 0, 0,
};
const char unknown_800B22C0[4] = "\x8c";
const char str_800B22C4[28] = "\x82""a\x82`\x82q\x82q\x82h\x82""d\x82q\x81@\x82""f\x82`\x82s\x82""d";
const MapFxInits fxInits_800B22E0 = { { 0, FxModel_800B2848, 0, FxMdec_800B31EC, 0 } };
const MapRgb savePointDim_800B22F4 = { 0x80, 0x40, 0x20, 0 };
const MapRgb savePointLit_800B22F8 = { 0x20, 0x40, 0x80, 0 };
