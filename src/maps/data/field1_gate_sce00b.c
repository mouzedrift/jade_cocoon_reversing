#include "maps/map.h"

void Warp_800B2348(MapEnt* ent);
void GateSpot_800B246C(MapEnt* ent);
int AddEffects_800B26BC(MapFx* fx);
void FxSprite_800B2848(MapEnt* ent);
void FxModel_800B29BC(MapEnt* ent);
void SavePoint_800B2BE4(MapEnt* ent);
void MapInit_800B3054(int phase);
void ScriptSpot_800B3230(MapEnt* ent);
void FxInit_800B32A4(MapEnt* ent);
void FxMdec_800B335C(MapEnt* ent);
void GateSpotInit_800B3448(MapEnt* ent);
void GateReturnInit_800B3490(MapEnt* ent);
void GateReturn_800B350C(MapEnt* ent);
void SavePointInit_800B357C(MapEnt* ent);
void StartMapTask_800B35BC(void);
void MapTaskLoad_800B35EC(EventEntry* entry, int* st);
void MapTask_800B3684(EventEntry* entry, int* st);
int LeaveArea_800B373C(MapEvent* ev, int area);
int EnterArea_800B3858(MapEvent* ev, int area, int prev);
void RequestModels_800B3960(MapEvent* ev);
void EntityTask_800B3A30(EventEntry* entry, MapEnt* ent);
int AddEntity_800B3AB0(void* ev);
void MapInit_800B3BDC(int phase);
int StopLevantIfSet_800B3C48(MapScriptSpot* spot);
int FxFrame_800B3C78(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B3CFC(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B3DC8(MapFx* fx, MapFxWork* w);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[28];
extern const MapFxInits fxInits_800B22E0;
extern const MapRgb savePointDim_800B22F4;
extern const MapRgb savePointLit_800B22F8;
extern MapSavePoint savePoint_800B3F10;
extern int data_800B3F20[2];
extern MapWarp warp_800B3F28;
extern MapWarp warp_800B3F40;
extern MapWarp warp_800B3F58;
extern MapWarp warp_800B3F70;
extern MapFx effects_800B3F88[3];
extern MapFx effects_800B400C[3];
extern MapFx effects_800B4090[3];
extern MapFx effects_800B4114[3];
extern MapFx effects_800B4198[3];
extern MapFx effects_800B421C[3];
extern MapFx effects_800B42A0[3];
extern MapFx effects_800B4324[3];
extern MapGateSpot data_800B43A8;
extern MapGateSpot data_800B43DC;
extern MapGateSpot data_800B4410;
extern MapGateSpot data_800B4444;
extern MapGateSpot data_800B4478;
extern MapGateSpot data_800B44AC;
extern MapGateSpot data_800B44E0;
extern MapGateSpot data_800B4514;
extern MapGateReturn data_800B4548;
extern MapGateReturn data_800B4550;
extern MapGateReturn data_800B4558;
extern MapGateReturn data_800B4560;
extern MapGateReturn data_800B4568;
extern MapGateReturn data_800B4570;
extern MapGateReturn data_800B4578;
extern MapGateReturn data_800B4580;
extern MapEvent events_800B4588[23];
extern int data_800B4754[16];
extern int data_800B4794[104];
extern int data_800B4934[24];
extern int data_800B4994[104];

MapSavePoint savePoint_800B3F10 = { { -0x32, -0x1B4, 0x384 }, str_800B22C4 };
int data_800B3F20[2] = {
    0x1010000, 0,
};
MapWarp warp_800B3F28 = { { -0x25, -0xE8, -0xF55 }, -0x688, 0, 5, { 4, 1, 0 } };
MapWarp warp_800B3F40 = { { -0x1A2, 0, -0x1278 }, -0x155, 0, 9, { 4, 2, 0 } };
MapWarp warp_800B3F58 = { { -0xD4, 0, -0x7EC }, 0xE3, 0, 7, { 4, 3, 0 } };
MapWarp warp_800B3F70 = { { 0x8F, 0, -0x8D9 }, 0x200, 0, 0xB, { 4, 4, 0 } };
MapFx effects_800B3F88[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, 0, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B400C[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 4, 4, 4, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B4090[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 2, 2, 2, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B4114[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 6, 6, 6, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B4198[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 1, 1, 1, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B421C[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 5, 5, 5, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B42A0[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 3, 3, 3, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B4324[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 7, 7, 7, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapGateSpot data_800B43A8 = { 3, 1, { 0x88B, -0x1DE, 0xBF6 }, { 0xB1F, 9, 0xE0C }, -0xDC2, 0x11, { effects_800B3F88, effects_800B400C }, 1, 0x6A };
MapGateSpot data_800B43DC = { 4, 3, { 0x2FD, -0x1AF, 0xE93 }, { 0x481, 0x19, 0x128E }, 0xEE, 0x20, { effects_800B4090, effects_800B4114 }, 2, 0x76 };
MapGateSpot data_800B4410 = { 6, 2, { -0x2A3, -0x190, 0xE4E }, { -0x3F7, 0x73, 0x123C }, -0xE1, 0x1A, { effects_800B4198, effects_800B421C }, 3, 0x89 };
MapGateSpot data_800B4444 = { 0xB, 4, { -0x753, -0x1DE, 0xB5D }, { -0xA82, 0x8F, 0xE1F }, -0x251, 0x1F, { effects_800B42A0, effects_800B4324 }, 4, 0xBA };
MapGateSpot data_800B4478 = { 3, 6, { 0xA31, -0x12C, 0xD32 }, { 0x6F5, -0xBE, 0xB15 }, 0xA3A, 0x16, { effects_800B400C, effects_800B3F88 }, -1, -1 };
MapGateSpot data_800B44AC = { 4, 0xA, { 0x426, -0x157, 0x1187 }, { 0x264, -0x9F, 0xCCB }, -0x6E1, 0x16, { effects_800B4114, effects_800B4090 }, -1, -1 };
MapGateSpot data_800B44E0 = { 6, 8, { -0x3A9, -0xCE, 0x111A }, { -0x25B, -0x83, 0xD0F }, -0x8E1, 0x16, { effects_800B421C, effects_800B4198 }, -1, -1 };
MapGateSpot data_800B4514 = { 0xB, 0xC, { -0x963, -0xB8, 0xD35 }, { -0x659, -0x83, 0xABB }, -0xA3D, 0x16, { effects_800B4324, effects_800B42A0 }, -1, -1 };
MapGateReturn data_800B4548 = { 1, effects_800B400C };
MapGateReturn data_800B4550 = { 2, effects_800B4114 };
MapGateReturn data_800B4558 = { 3, effects_800B421C };
MapGateReturn data_800B4560 = { 4, effects_800B4324 };
MapGateReturn data_800B4568 = { 5, effects_800B3F88 };
MapGateReturn data_800B4570 = { 6, effects_800B4090 };
MapGateReturn data_800B4578 = { 7, effects_800B4198 };
MapGateReturn data_800B4580 = { 8, effects_800B42A0 };
MapEvent events_800B4588[23] = {
    { -1, 0, data_800B3F20, 0, { ScriptSpot_800B3230 } },
    { -1, 1, &warp_800B3F28, 0, { Warp_800B2348 } },
    { -1, 1, &warp_800B3F40, 0, { Warp_800B2348 } },
    { -1, 1, &warp_800B3F58, 0, { Warp_800B2348 } },
    { -1, 1, &warp_800B3F70, 0, { Warp_800B2348 } },
    { -1, 0xD, &data_800B43A8, 0x10, { GateSpotInit_800B3448 } },
    { -1, 0xD, &data_800B43DC, 0x10, { GateSpotInit_800B3448 } },
    { -1, 0xD, &data_800B4410, 0x10, { GateSpotInit_800B3448 } },
    { -1, 0xD, &data_800B4444, 0x10, { GateSpotInit_800B3448 } },
    { -1, 0xD, &data_800B4478, 0x10, { GateSpotInit_800B3448 } },
    { -1, 0xD, &data_800B44AC, 0x10, { GateSpotInit_800B3448 } },
    { -1, 0xD, &data_800B44E0, 0x10, { GateSpotInit_800B3448 } },
    { -1, 0xD, &data_800B4514, 0x10, { GateSpotInit_800B3448 } },
    { -1, 0xD, &data_800B4548, 4, { GateReturnInit_800B3490 } },
    { -1, 0xD, &data_800B4550, 4, { GateReturnInit_800B3490 } },
    { -1, 0xD, &data_800B4558, 4, { GateReturnInit_800B3490 } },
    { -1, 0xD, &data_800B4560, 4, { GateReturnInit_800B3490 } },
    { -1, 0xD, &data_800B4568, 4, { GateReturnInit_800B3490 } },
    { -1, 0xD, &data_800B4570, 4, { GateReturnInit_800B3490 } },
    { -1, 0xD, &data_800B4578, 4, { GateReturnInit_800B3490 } },
    { -1, 0xD, &data_800B4580, 4, { GateReturnInit_800B3490 } },
    { -1, 0xC, &savePoint_800B3F10, 0xC, { SavePointInit_800B357C } },
    { 0, 0x12, 0, 0, { 0 } },
};
int data_800B4754[16] = {
    0x4B, 0, 0, 0, 0x4D, 0, 0, MAP_REF(StopLevantIfSet_800B3C48),
    0x58, 0, 0, 0, 3, 0, 0, 0,
};
int data_800B4794[104] = {
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
int data_800B4934[24] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x3E, -1, 8, 5, 8, 0, 1, 0,
    4, 0, 0, 0, 3, 0, 0, 0,
};
int data_800B4994[104] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x67, 0xC, 5, 0, 0x30, 0, 0, 0,
    0x31, 0, 0, 0, 0xC, 0, 0x1E, 0,
    0x67, 5, 0x1E, 0, 0xC, 0, 0x3C, 0,
    0x1A, 1, 1, 0, 0x67, 4, 0x1E, 0,
    0x1F, 1, 0, 0, 0xA, 0, 1, 0,
    0xA, 0, 2, 0, 9, 0, 1, 0,
    0x48, 0, 0xE1, 5, 0x48, 0, 0xE2, 1,
    0x48, 0, 0xE4, 1, 0x49, 0, 0xE300E5, 1,
    0xD, 0, 1, 0, 0x67, 6, 0, 0,
    9, 0, 2, 0, 0x21, 0, 0, 0,
    0x30, 0, 1, 0, 8, 0, 1, 0,
    4, 0, 0, 0, 3, 0, 0, 0,
};
const char unknown_800B22C0[4] = "\x8e";
const char str_800B22C4[28] = "\x82""a\x82`\x82q\x82q\x82h\x82""d\x82q\x81@\x82""f\x82`\x82s\x82""d";
const MapFxInits fxInits_800B22E0 = { { FxSprite_800B2848, FxModel_800B29BC, 0, FxMdec_800B335C, 0 } };
const MapRgb savePointDim_800B22F4 = { 0x80, 0x40, 0x20, 0 };
const MapRgb savePointLit_800B22F8 = { 0x20, 0x40, 0x80, 0 };
