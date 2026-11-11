#include "maps/map.h"

void Warp_800B2368(MapEnt* ent);
void MinionInit_800B248C(MapEnt* ent);
void GateSpot_800B27C4(MapEnt* ent);
void GateReturn_800B2A14(MapEnt* ent);
void GlowTrail_800B2BF4(MapEnt* ent);
int AddEffects_800B3038(MapFx* fx);
void FxSprite_800B31C4(MapEnt* ent);
void FxModel_800B3338(MapEnt* ent);
void SavePoint_800B3560(MapEnt* ent);
void MapInit_800B39D0(int phase);
void ScriptSpot_800B3BB4(MapEnt* ent);
void MinionIdle_800B3C28(MapEnt* ent);
void FxInit_800B3C30(MapEnt* ent);
void FxMdec_800B3CE8(MapEnt* ent);
void GateSpotInit_800B3DD4(MapEnt* ent);
void GateReturnInit_800B3E1C(MapEnt* ent);
void FxAtLevant_800B3E98(int* pos, short* rot);
void GlowTrailInit_800B3F88(MapEnt* ent);
void SavePointInit_800B3FC8(MapEnt* ent);
void StartMapTask_800B4008(void);
void MapTaskLoad_800B4038(EventEntry* entry, int* st);
void MapTask_800B40D0(EventEntry* entry, int* st);
int LeaveArea_800B4188(MapEvent* ev, int area);
int EnterArea_800B42A4(MapEvent* ev, int area, int prev);
void RequestModels_800B43AC(MapEvent* ev);
void EntityTask_800B447C(EventEntry* entry, MapEnt* ent);
int AddEntity_800B44FC(void* ev);
void MapInit_800B4628(int phase);
int StopLevantIfSet_800B4694(MapScriptSpot* spot);
int MinionF_800B46C4(void);
int MinionF_800B46CC(void);
int FxFrame_800B46D4(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B4758(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B4824(MapFx* fx, MapFxWork* w);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[28];
extern const char str_800B22E0[12];
extern const MapFxInits fxInits_800B2300;
extern const MapRgb savePointDim_800B2314;
extern const MapRgb savePointLit_800B2318;
extern MapSavePoint savePoint_800B496C;
extern int data_800B497C[3];
extern short bones_800B4988[116];
extern ActorScriptCmd* script_800B4A70;
extern MapActorModel model_800B4A74;
extern MapVoice voices_800B4AA0[5];
extern int data_800B4AC8[2];
extern MapWarp warp_800B4AD0;
extern MapWarp warp_800B4AE8;
extern MapWarp warp_800B4B00;
extern MapWarp warp_800B4B18;
extern MapFx effects_800B4B30[3];
extern MapFx effects_800B4BB4[3];
extern MapFx effects_800B4C38[3];
extern MapFx effects_800B4CBC[3];
extern MapFx effects_800B4D40[3];
extern MapFx effects_800B4DC4[3];
extern MapFx effects_800B4E48[3];
extern MapFx effects_800B4ECC[3];
extern MapGateSpot data_800B4F50;
extern MapGateSpot data_800B4F84;
extern MapGateSpot data_800B4FB8;
extern MapGateSpot data_800B4FEC;
extern MapGateSpot data_800B5020;
extern MapGateSpot data_800B5054;
extern MapGateSpot data_800B5088;
extern MapGateSpot data_800B50BC;
extern MapGateReturn data_800B50F0;
extern MapGateReturn data_800B50F8;
extern MapGateReturn data_800B5100;
extern MapGateReturn data_800B5108;
extern MapGateReturn data_800B5110;
extern MapGateReturn data_800B5118;
extern MapGateReturn data_800B5120;
extern MapGateReturn data_800B5128;
extern MapMinion minion_800B5130;
extern MapEvent events_800B5154[25];
extern int data_800B5348[16];
extern short bones_800B5388[92];
extern int scale_800B5440[3];
extern MapFx effects_800B544C[3];
extern int data_800B54D0[104];
extern int data_800B5670[24];
extern int data_800B56D0[172];

MapSavePoint savePoint_800B496C = { { -0x32, -0x1B4, 0x384 }, str_800B22C4 };
int data_800B497C[3] = {
    0x333, 0x333, 0x333,
};
short bones_800B4988[116] = {
    0, 0, 0, 0x44, 1, 1, 1, 0,
    2, 0x102, 2, 0xB, 3, 0x203, 3, 0xB,
    4, 0x304, 4, 0xB, 5, 0x405, 5, 0xB,
    5, 0x406, 6, 0xB, 6, 0x507, 7, 0xB,
    3, 0x208, 8, 0xB, 4, 0x309, 9, 0xB,
    5, 0x40A, 0xA, 0xB, 5, 0x40B, 0xB, 0xB,
    6, 0x50C, 0xC, 0xB, 3, 0x20D, 0xD, 0xB,
    4, 0x30E, 0xE, 0xB, 2, 0x10F, 0xF, 0xB,
    3, 0x210, 0x10, 0xB, 4, 0x311, 0x11, 0xB,
    5, 0x412, 0x12, 0xB, 3, 0x213, 0x13, 0xB,
    4, 0x314, 0x14, 0xB, 5, 0x415, 0x15, 0xB,
    3, 0x216, 0x16, 0xB, 4, 0x317, 0x17, 0xB,
    3, 0x218, 0x18, 0xB, 4, 0x319, 0x19, 0xB,
    3, 0x21A, 0x1A, 0xB, 3, 0x21B, 0x1B, 0xB,
    -1, -1, -1, -1,
};
ActorScriptCmd* script_800B4A70 = 0;
MapActorModel model_800B4A74 = { str_800B22E0, 0x33, bones_800B4988, data_800B497C, 0, 0, 4, &script_800B4A70, 0, 0x800000, 0, 0 };
MapVoice voices_800B4AA0[5] = {
    { 0, 0, { 6, 0x312, 0x1E } },
    { 0, 1, { 0x14, 0x312, 0x19 } },
    { 0, 2, { 0x1C, 0x314, 0x1C } },
    { 0, 3, { 0x1E, 0x314, 0x12 } },
    { 0, 0, { -1, 0, 0 } },
};
int data_800B4AC8[2] = {
    0x1010000, 0,
};
MapWarp warp_800B4AD0 = { { -0x25, -0xE8, -0xF55 }, -0x688, 0, 5, { 4, 1, 0 } };
MapWarp warp_800B4AE8 = { { -0x1A2, 0, -0x1278 }, -0x155, 0, 9, { 4, 2, 0 } };
MapWarp warp_800B4B00 = { { -0xD4, 0, -0x7EC }, 0xE3, 0, 7, { 4, 3, 0 } };
MapWarp warp_800B4B18 = { { 0x8F, 0, -0x8D9 }, 0x200, 0, 0xB, { 4, 4, 0 } };
MapFx effects_800B4B30[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, 0, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B4BB4[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 4, 4, 4, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B4C38[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 2, 2, 2, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B4CBC[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 6, 6, 6, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B4D40[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 1, 1, 1, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B4DC4[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 5, 5, 5, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B4E48[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 3, 3, 3, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B4ECC[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 7, 7, 7, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapGateSpot data_800B4F50 = { 3, 1, { 0x88B, -0x1DE, 0xBF6 }, { 0xB1F, 9, 0xE0C }, -0xDC2, 0x11, { effects_800B4B30, effects_800B4BB4 }, 1, 0x6A };
MapGateSpot data_800B4F84 = { 4, 3, { 0x2FD, -0x1AF, 0xE93 }, { 0x481, 0x19, 0x128E }, 0xEE, 0x20, { effects_800B4C38, effects_800B4CBC }, 2, 0x76 };
MapGateSpot data_800B4FB8 = { 6, 2, { -0x2A3, -0x190, 0xE4E }, { -0x3F7, 0x73, 0x123C }, -0xE1, 0x1A, { effects_800B4D40, effects_800B4DC4 }, 3, 0x89 };
MapGateSpot data_800B4FEC = { 0xB, 4, { -0x753, -0x1DE, 0xB5D }, { -0xA82, 0x8F, 0xE1F }, -0x251, 0x1F, { effects_800B4E48, effects_800B4ECC }, 4, 0xBA };
MapGateSpot data_800B5020 = { 3, 6, { 0xA31, -0x12C, 0xD32 }, { 0x6F5, -0xBE, 0xB15 }, 0xA3A, 0x16, { effects_800B4BB4, effects_800B4B30 }, -1, -1 };
MapGateSpot data_800B5054 = { 4, 0xA, { 0x426, -0x157, 0x1187 }, { 0x264, -0x9F, 0xCCB }, -0x6E1, 0x16, { effects_800B4CBC, effects_800B4C38 }, -1, -1 };
MapGateSpot data_800B5088 = { 6, 8, { -0x3A9, -0xCE, 0x111A }, { -0x25B, -0x83, 0xD0F }, -0x8E1, 0x16, { effects_800B4DC4, effects_800B4D40 }, -1, -1 };
MapGateSpot data_800B50BC = { 0xB, 0xC, { -0x963, -0xB8, 0xD35 }, { -0x659, -0x83, 0xABB }, -0xA3D, 0x16, { effects_800B4ECC, effects_800B4E48 }, -1, -1 };
MapGateReturn data_800B50F0 = { 1, effects_800B4BB4 };
MapGateReturn data_800B50F8 = { 2, effects_800B4CBC };
MapGateReturn data_800B5100 = { 3, effects_800B4DC4 };
MapGateReturn data_800B5108 = { 4, effects_800B4ECC };
MapGateReturn data_800B5110 = { 5, effects_800B4B30 };
MapGateReturn data_800B5118 = { 6, effects_800B4C38 };
MapGateReturn data_800B5120 = { 7, effects_800B4D40 };
MapGateReturn data_800B5128 = { 8, effects_800B4E48 };
MapMinion minion_800B5130 = { &model_800B4A74, 0, { 0xC99, 0, 0x104F }, 0, 0, 0, 1, 3 };
MapEvent events_800B5154[25] = {
    { -1, 0xF, &minion_800B5130, 0x14, { MinionInit_800B248C } },
    { -1, 0, data_800B4AC8, 0, { ScriptSpot_800B3BB4 } },
    { -1, 1, &warp_800B4AD0, 0, { Warp_800B2368 } },
    { -1, 1, &warp_800B4AE8, 0, { Warp_800B2368 } },
    { -1, 1, &warp_800B4B00, 0, { Warp_800B2368 } },
    { -1, 1, &warp_800B4B18, 0, { Warp_800B2368 } },
    { -1, 0xD, &data_800B4F50, 0x10, { GateSpotInit_800B3DD4 } },
    { -1, 0xD, &data_800B4F84, 0x10, { GateSpotInit_800B3DD4 } },
    { -1, 0xD, &data_800B4FB8, 0x10, { GateSpotInit_800B3DD4 } },
    { -1, 0xD, &data_800B4FEC, 0x10, { GateSpotInit_800B3DD4 } },
    { -1, 0xD, &data_800B5020, 0x10, { GateSpotInit_800B3DD4 } },
    { -1, 0xD, &data_800B5054, 0x10, { GateSpotInit_800B3DD4 } },
    { -1, 0xD, &data_800B5088, 0x10, { GateSpotInit_800B3DD4 } },
    { -1, 0xD, &data_800B50BC, 0x10, { GateSpotInit_800B3DD4 } },
    { -1, 0xD, &data_800B50F0, 4, { GateReturnInit_800B3E1C } },
    { -1, 0xD, &data_800B50F8, 4, { GateReturnInit_800B3E1C } },
    { -1, 0xD, &data_800B5100, 4, { GateReturnInit_800B3E1C } },
    { -1, 0xD, &data_800B5108, 4, { GateReturnInit_800B3E1C } },
    { -1, 0xD, &data_800B5110, 4, { GateReturnInit_800B3E1C } },
    { -1, 0xD, &data_800B5118, 4, { GateReturnInit_800B3E1C } },
    { -1, 0xD, &data_800B5120, 4, { GateReturnInit_800B3E1C } },
    { -1, 0xD, &data_800B5128, 4, { GateReturnInit_800B3E1C } },
    { -1, 0xB, voices_800B4AA0, 0, { 0 } },
    { -1, 0xC, &savePoint_800B496C, 0xC, { SavePointInit_800B3FC8 } },
    { 0, 0x12, 0, 0, { 0 } },
};
int data_800B5348[16] = {
    0x4B, 0, 0, 0, 0x4D, 0, 0, MAP_REF(StopLevantIfSet_800B4694),
    0x58, 0, 0, 0, 3, 0, 0, 0,
};
short bones_800B5388[92] = {
    0, 0, 0, 0x46, 1, 1, 1, 0,
    2, 0x102, 2, 0xB, 3, 0x203, 3, 0xB,
    4, 0x304, 4, 0xB, 5, 0x405, 5, 0xB,
    5, 0x506, 6, 0xB, 6, 0x607, 7, 0xB,
    3, 0x208, 8, 0xB, 4, 0x809, 9, 0xB,
    5, 0x90A, 0xA, 0xB, 5, 0xA0B, 0xB, 0xB,
    6, 0xB0C, 0xC, 0xB, 3, 0x20D, 0xD, 0,
    4, 0xD0E, 0xE, 0xB, 2, 0x10F, 0xF, 0xB,
    3, 0xF10, 0x10, 0xB, 4, 0x1011, 0x11, 0xB,
    5, 0x1112, 0x12, 0xB, 3, 0xF13, 0x13, 0xB,
    4, 0x1314, 0x14, 0xB, 5, 0x1415, 0x15, 0xB,
    -1, -1, -1, -1,
};
int scale_800B5440[3] = {
    0x1000, 0x1000, 0x1000,
};
MapFx effects_800B544C[3] = {
    { 0, 0x145, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x28, 0, 0, 0, 0, -1, 0x30, 0, FxAtLevant_800B3E98 },
    { 0, 0x144, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0xF0, 0x28, 0, 0, 0, -1, 0x30, 0, FxAtLevant_800B3E98 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
int data_800B54D0[104] = {
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
int data_800B5670[24] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x3E, -1, 8, 5, 8, 0, 1, 0,
    4, 0, 0, 0, 3, 0, 0, 0,
};
int data_800B56D0[172] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x67, 0xC, 5, 0, 0x30, 0, 0, 0,
    0x31, 0, 0, 0, 0xC, 0, 0x1E, 0,
    0x67, 5, 0x1E, 0, 0xC, 0, 0x3C, 0,
    0x1A, 1, 1, 0, 0x67, 4, 0x1E, 0,
    0x1F, 1, 0, 0, 0xA, 0, 1, 0,
    0xA, 0, 2, 0, 9, 0, 1, 0,
    0x1F, 1, 0x77, 0, 0xA, 0, 4, 0,
    0xA, 0, 3, 0, 9, 0, 3, 0,
    0x48, 0, 0xE1, 5, 0x48, 0, 0xE2, 1,
    0x48, 0, 0xE4, 1, 0x49, 0, 0xE300E5, 1,
    0xD, 0, 1, 0, 0x67, 6, 0, 0,
    0xA, 0, 2, 0, 9, 0, 4, 0,
    0x48, 0, 0xE1, 5, 0x48, 0, 0xE2, 1,
    0x48, 0, 0xE4, 1, 0x38, 1, 0, 0,
    0x3F, 0, 0, 0, 0x30, 0, 2, 0,
    0xC, 0, 0x154, 0, 0x49, 0, 0xE300E5, 1,
    0xD, 0, 1, 0, 0x2C, 0, 1, 0,
    0x67, 6, 0, 0, 9, 0, 2, 0,
    0x21, 0, 0, 0, 0x30, 0, 1, 0,
    8, 0, 1, 0, 4, 0, 0, 0,
    3, 0, 0, 0,
};
const char unknown_800B22C0[4] = "\x91";
const char str_800B22C4[28] = "\x82""a\x82`\x82q\x82q\x82h\x82""d\x82q\x81@\x82""f\x82`\x82s\x82""d";
const char str_800B22E0[12] = "\x82l\x82\x81\x82\x88\x82\x82\x82\x95";
