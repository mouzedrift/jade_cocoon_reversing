#include "maps/map.h"

void MinionInit_800B22E4(MapEnt* ent);
int AddEffects_800B261C(MapFx* fx);
void FxSprite_800B27A8(MapEnt* ent);
void FxModel_800B291C(MapEnt* ent);
void FxModels_800B2B44(MapEnt* ent);
void MapInit_800B30EC(int phase);
void MinionIdle_800B3158(MapEnt* ent);
int EndEffects_800B3160(void);
void FxInit_800B31E0(MapEnt* ent);
void FxModelsInit_800B3298(MapEnt* ent);
void FxAtLevantBone_800B32F4(int* pos, short* rot);
int SwitchBone_800B3404(void);
int ShakeCamera_800B342C(void);
void StartMapTask_800B344C(void);
void MapTaskLoad_800B347C(EventEntry* entry, int* st);
void MapTask_800B3514(EventEntry* entry, int* st);
int LeaveArea_800B35CC(MapEvent* ev, int area);
int EnterArea_800B36E8(MapEvent* ev, int area, int prev);
void RequestModels_800B37F0(MapEvent* ev);
void EntityTask_800B38C0(EventEntry* entry, MapEnt* ent);
int AddEntity_800B3940(void* ev);
int MinionF_800B3A6C(void);
int MinionF_800B3A74(void);
int FxFrame_800B3A7C(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B3B00(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B3BCC(MapFx* fx, MapFxWork* w);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[12];
extern const MapFxInits fxInits_800B22D0;
extern int data_800B3D14[3];
extern short bones_800B3D20[116];
extern ActorScriptCmd* script_800B3E08;
extern MapActorModel model_800B3E0C;
extern int bone7_800B3E38;
extern MapVoice voices_800B3E3C[5];
extern MapFxModels fxModels_800B3E64;
extern int unknown_800B3E8C[2];
extern MapFx effects_800B3E94[2];
extern MapFx effects_800B3EEC[2];
extern MapFx effects_800B3F44[2];
extern MapFx effects_800B3F9C[2];
extern MapFx effects_800B3FF4[3];
extern MapFx effects_800B4078[2];
extern MapFx effects_800B40D0[2];
extern int data_800B4128[4];
extern MapInstr script_800B4138[103];
extern MapMinion minion_800B47A8;
extern MapEvent events_800B47CC[5];
extern short bones_800B4830[92];
extern int scale_800B48E8[3];

int data_800B3D14[3] = {
    0x333, 0x333, 0x333,
};
short bones_800B3D20[116] = {
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
ActorScriptCmd* script_800B3E08 = 0;
MapActorModel model_800B3E0C = { str_800B22C4, 0x33, bones_800B3D20, data_800B3D14, 0, 0, 4, &script_800B3E08, 0, 0x800000, 0, 0 };
int bone7_800B3E38 = 0;
MapVoice voices_800B3E3C[5] = {
    { 1, 0, { 0x1F, 0x314, 0xC } },
    { 1, 1, { 3, 0x316, 0x2D } },
    { 1, 2, { 0x13, 0x316, 0x26 } },
    { 1, 3, { 0x1D, 0x316, 0x2E } },
    { 0, 0, { -1, 0, 0 } },
};
MapFxModels fxModels_800B3E64 = { 0x82, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x83, { 0, 0, 0 } };
int unknown_800B3E8C[2] = {
    0, 0,
};
MapFx effects_800B3E94[2] = {
    { 0, 0x14F, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, -1, 0, 0, -1, 0x30, 0, (void*)FxAtLevantBone_800B32F4 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3EEC[2] = {
    { 0, 0x153, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, -1, 0, 0, -1, 0x38, 0, (void*)FxAtLevantBone_800B32F4 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3F44[2] = {
    { 0, 0x153, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, -1, 0, 0, -1, 0x30, 0, (void*)FxAtLevantBone_800B32F4 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3F9C[2] = {
    { 1, 0x84, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x10, 0, 0, 0, 0, -1, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3FF4[3] = {
    { 1, 0x85, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0xF, 0, 0, 0, 0, -1, 0, 0, 0 },
    { 1, 0x87, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x28, 0, 0, 0, 0, -1, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B4078[2] = {
    { 1, 0x86, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B40D0[2] = {
    { 1, 0x87, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x28, 0, 0, 0, 0, -1, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
int data_800B4128[4] = {
    0, 0, 0, 0,
};
MapInstr script_800B4138[103] = {
    { 5, 0, 0, 0 },
    { 7, 0, 3, 0 },
    { 0x67, 1, 0x1E, 0 },
    { 0x5E, 0, 1, 0 },
    { 0x13, 0, 0, MAP_REF(data_800B4128) },
    { 0x1C, 1, 1, 0 },
    { 0x55, 0, 1, 0 },
    { 0x67, 2, 0x1E, 0 },
    { 0x49, 0, 0xE700EF, 5 },
    { 0xD, 0, 1, 0 },
    { 0xC, 0, 0x78, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B3E94) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B261C) },
    { 0x38, 1, 0, 0 },
    { 0x42, 0, 0, 0 },
    { 0x49, 0, 0xE800F0, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x56, 0, 1, 0 },
    { 0x55, 0, 2, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B3160) },
    { 0x4B, 0, 0, MAP_REF(effects_800B3EEC) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B261C) },
    { 0x38, 1, 0, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x56, 0, 2, 0 },
    { 0x55, 0, 3, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B3160) },
    { 0x4B, 0, 0, MAP_REF(effects_800B3F44) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B261C) },
    { 0x49, 0, 0xE900F1, 1 },
    { 0xC, 0, 0x1D, 0 },
    { 0x4D, 0, 0, MAP_REF(SwitchBone_800B3404) },
    { 0xD, 0, 1, 0 },
    { 0x2E, 1, 0, MAP_REF(fxModels_800B3E64) },
    { 0x4B, 0, 0, MAP_REF(effects_800B3F9C) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B261C) },
    { 0xC, 0, 0x10, 0 },
    { 0x56, 0, 3, 0 },
    { 0x55, 0, 4, 0 },
    { 0xC, 0, 0x3C, 0 },
    { 0xC, 0, 0x3C, 0 },
    { 0x56, 0, 4, 0 },
    { 0x55, 0, 5, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B3FF4) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B261C) },
    { 0x2E, 1, 0, MAP_REF(fxModels_800B3E64) },
    { 0xC, 0, 0x1E, 0 },
    { 0x4D, 0, 0, MAP_REF(ShakeCamera_800B342C) },
    { 0xC, 0, 0x3C, 0 },
    { 0x56, 0, 5, 0 },
    { 0x55, 0, 6, 0 },
    { 0xC, 0, 0x78, 0 },
    { 0x56, 0, 6, 0 },
    { 0x55, 0, 7, 0 },
    { 0xC, 0, 0x3C, 0 },
    { 0x56, 0, 7, 0 },
    { 0x55, 0, 8, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B3160) },
    { 0x49, 0, 0xEA00F2, 1 },
    { 0xC, 0, 0x21, 0 },
    { 0x56, 0, 8, 0 },
    { 0x55, 0, 9, 0 },
    { 0xC, 0, 0xD, 0 },
    { 0x56, 0, 9, 0 },
    { 0x55, 0, 0xA, 0 },
    { 0xD, 0, 1, 0 },
    { 0x56, 0, 0xA, 0 },
    { 0x55, 0, 0xB, 0 },
    { 0xC, 0, 0x5A, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B4078) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B261C) },
    { 0xC, 0, 0x1E, 0 },
    { 0x67, 0xD, 0x4E, 0 },
    { 0x49, 0, 0xEB00F3, 1 },
    { 0x67, 5, 0x1E, 0 },
    { 0xC, 0, 0x3C, 0 },
    { 0x56, 0, 0xB, 0 },
    { 0x55, 0, 0xC, 0 },
    { 0x67, 4, 0x5A, 0 },
    { 0x67, 6, 0, 0 },
    { 0x49, 0, 0xEC00F4, 1 },
    { 0xD, 0, 1, 0 },
    { 0x56, 0, 0xC, 0 },
    { 0x55, 0, 0xD, 0 },
    { 0xC, 0, 0x3C, 0 },
    { 0x49, 0, 0xED00F4, 1 },
    { 0xD, 0, 1, 0 },
    { 0x56, 0, 0xD, 0 },
    { 0xC, 0, 0x1E, 0 },
    { 0x2E, 1, 0, MAP_REF(fxModels_800B3E64) },
    { 0x4D, 0, 0, MAP_REF(ShakeCamera_800B342C) },
    { 0x4B, 0, 0, MAP_REF(effects_800B40D0) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B261C) },
    { 0xC, 0, 0x1E, 0 },
    { 0x49, 0, 0xEE00F5, 1 },
    { 0xC, 0, 0x96, 0 },
    { 0x67, 3, 0x96, 0 },
    { 0x67, 6, 0, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B3160) },
    { 8, 0, 3, 0 },
    { 4, 0, 0, 0 },
    { 0x4F, 0, 6, 0 },
    { 3, 0, 0, 0 },
};
MapMinion minion_800B47A8 = { &model_800B3E0C, 0, { 0, 0, 0 }, 0, 0, 0, 1, 0xB };
MapEvent events_800B47CC[5] = {
    { -1, 0xF, &minion_800B47A8, 0x14, { MinionInit_800B22E4 } },
    { -1, 8, script_800B4138, 0, { 0 } },
    { -1, 0xD, &fxModels_800B3E64, 0x24, { (void*)FxModelsInit_800B3298 } },
    { -1, 0xB, voices_800B3E3C, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
short bones_800B4830[92] = {
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
int scale_800B48E8[3] = {
    0x1000, 0x1000, 0x1000,
};
const char unknown_800B22C0[4] = "\xf0";
const char str_800B22C4[12] = "\x82l\x82\x81\x82\x88\x82\x82\x82\x95";
const MapFxInits fxInits_800B22D0 = { { FxSprite_800B27A8, FxModel_800B291C, 0, 0, 0 } };
