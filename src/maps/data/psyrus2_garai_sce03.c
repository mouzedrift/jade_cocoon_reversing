#include "maps/map.h"

void MinionInit_800B22F0(MapEnt* ent);
int AddEffects_800B2628(MapFx* fx);
void FxSprite_800B27B4(MapEnt* ent);
void MapInit_800B2928(int phase);
void MinionIdle_800B29A8(MapEnt* ent);
int EndEffects_800B29B0(void);
void FxInit_800B2A30(MapEnt* ent);
void FxLight_800B2AE8(MapEnt* ent);
void FxAtMinion_800B2BA8(int* pos, short* rot);
void StartMapTask_800B2C7C(void);
void MapTaskLoad_800B2CAC(EventEntry* entry, int* st);
void MapTask_800B2D44(EventEntry* entry, int* st);
int LeaveArea_800B2DFC(MapEvent* ev, int area);
int EnterArea_800B2F18(MapEvent* ev, int area, int prev);
void RequestModels_800B3020(MapEvent* ev);
void EntityTask_800B30F0(EventEntry* entry, MapEnt* ent);
int AddEntity_800B3170(void* ev);
void MapInit_800B329C(int phase);
int MinionF_800B3308(void);
int MinionF_800B3310(void);
int FxFrame_800B3318(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B339C(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B3468(MapFx* fx, MapFxWork* w);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[12];
extern const char str_800B22D0[12];
extern const MapFxInits fxInits_800B22DC;
extern int unknown_800B35B0[11];
extern int data_800B35DC[12];
extern ActorScriptCmd* script_800B360C;
extern MapActorModel model_800B3610;
extern int data_800B363C[3];
extern short bones_800B3648[116];
extern int data_800B3730[11];
extern int data_800B375C[12];
extern int data_800B378C[16];
extern ActorScriptCmd* script_800B37CC;
extern MapActorModel model_800B37D0;
extern MapVoice voices_800B37FC[25];
extern MapFx effects_800B38C4[2];
extern MapFx effects_800B391C[3];
extern MapFx effects_800B39A0[7];
extern MapFx effects_800B3AD4[3];
extern int data_800B3B58[4];
extern MapInstr script_800B3B68[135];
extern MapMinion minion_800B43D8;
extern MapMinion minion_800B43FC;
extern MapEvent events_800B4420[5];
extern short bones_800B4484[92];
extern int scale_800B453C[3];

int unknown_800B35B0[11] = {
    -0x1FEF1, -0xFDF5, 0x10000, -0xFDFA, 0x1000000, -0xFDFF, 0x470000, -0x1FDEC,
    0x40000000, -0x1FEF0, -0x1FF00,
};
int data_800B35DC[12] = {
    -0x1FEF1, -0xFDF9, 0x1000000, -0x1FDE9, 0x1E0000, -0x1FDEC, 0x40000000, -0xFEF8,
    -0xFDF5, 0, -0x1FEF0, -0x1FF00,
};
ActorScriptCmd* script_800B360C = 0;
MapActorModel model_800B3610 = { str_800B22C4, 0x16, 0, 0, 0, 0, 4, &script_800B360C, 0, 0x800000, 0, 1 };
int data_800B363C[3] = {
    0x333, 0x333, 0x333,
};
short bones_800B3648[116] = {
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
int data_800B3730[11] = {
    -0x1FEF1, -0xFDF5, 0x10000, -0xFDF9, 0x1000000, -0x1FDE9, 0x20000, -0x1FDEC,
    0x40000000, -0x1FEF0, -0x1FF00,
};
int data_800B375C[12] = {
    -0x1FEF1, -0xFDF5, 0x10000, -0xFDFA, 0x1000000, -0xFDFF, 0x60000, -0x1FEEB,
    -0x1FDEC, 0x40000000, -0x1FEF0, -0x1FF00,
};
int data_800B378C[16] = {
    -0x1FEF1, -0xFDFF, 0xF0000, -0x1FEEB, -0xFDF9, 0x1000000, -0xFDFF, 0x50000,
    -0x1FEEB, -0x1FDEC, 0x40000000, -0xFEF8, -0xFDF5, 0, -0x1FEF0, -0x1FF00,
};
ActorScriptCmd* script_800B37CC = 0;
MapActorModel model_800B37D0 = { str_800B22D0, 0x33, bones_800B3648, data_800B363C, 0, 0, 4, &script_800B37CC, 0, 0x800000, 0, 0 };
MapVoice voices_800B37FC[25] = {
    { 1, 0, { 0xF, 0x309, 0x16 } },
    { 1, 1, { 1, 0x30B, 0x1A } },
    { 1, 2, { 0x10, 0x30C, 0x1E } },
    { 2, 0, { 0xD, 0x30D, 0x18 } },
    { 2, 1, { 0xE, 0x30E, 0x1F } },
    { 2, 2, { 0x15, 0x30E, 0x13 } },
    { 2, 3, { 0x19, 0x30E, 0x23 } },
    { 3, 0, { 0x18, 0x30F, 0x28 } },
    { 3, 1, { 0x1B, 0x30F, 0x21 } },
    { 3, 2, { 0x12, 0x310, 0x11 } },
    { 3, 3, { 0x1A, 0x310, 0x1C } },
    { 4, 0, { 0x14, 0x8D, 0x35 } },
    { 5, 0, { 0, 0x8E, 0x26 } },
    { 6, 0, { 4, 0x8F, 0x31 } },
    { 8, 0, { 0x1D, 0x91, 0x1A } },
    { 8, 1, { 0x10, 0x94, 0x1C } },
    { 8, 2, { 0x15, 0x94, 0x18 } },
    { 8, 3, { 0x19, 0x94, 0x1E } },
    { 9, 0, { 3, 0x97, 0x18 } },
    { 9, 1, { 0x16, 0x97, 0x1D } },
    { 9, 2, { 0xD, 0x99, 0x16 } },
    { 9, 3, { 1, 0x9B, 0x29 } },
    { 0xA, 0, { 0x1B, 0x9B, 0x32 } },
    { 0xA, 1, { 6, 0x9C, 0x26 } },
    { 0, 0, { -1, 0, 0 } },
};
MapFx effects_800B38C4[2] = {
    { 0, 0x14F, { 0x19B, -0x19, -0xCC }, { 0, 0, 0 }, 0, 0x1E, 0, -1, 0, 0, -1, 0x30, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B391C[3] = {
    { 0, 0x150, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 1, -1, 0, 0, -1, 0x30, 0, FxAtMinion_800B2BA8 },
    { 4, 0, { 0, 0, 0 }, { 0x999, 0x999, 0x1000 }, 0, 0x1E, 0, -1, 0, 0, -1, 0x30D4, 0, FxAtMinion_800B2BA8 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B39A0[7] = {
    { 0, 0x150, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, 2, 0, 0, -1, 0x30, 0, FxAtMinion_800B2BA8 },
    { 0, 0x151, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x96, 0, 0, 0, 0, 0x95, 0x30, 0, FxAtMinion_800B2BA8 },
    { 0, 0x151, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0xB4, 0x96, -1, 0x96, 0x96, 0xB3, 0x30, 0, FxAtMinion_800B2BA8 },
    { 0, 0x152, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0x1E, 0, 0, 0, -1, 0x30, 0, FxAtMinion_800B2BA8 },
    { 4, 0, { 0, 0, 0 }, { 0x999, 0x999, 0x1000 }, 0, 0x1E, 0, 0, 0, 0, -1, 0x30D4, 0, FxAtMinion_800B2BA8 },
    { 4, 0, { 0, 0, 0 }, { 0x666, 0x1000, 0x666 }, 0, 0x1E, 0x1E, -1, 0, 0, -1, 0x30D4, 0, FxAtMinion_800B2BA8 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3AD4[3] = {
    { 0, 0x151, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0xD2, 0, 0, 0xB4, 0xB4, 0xD1, 0x30, 0, FxAtMinion_800B2BA8 },
    { 4, 0, { 0, 0, 0 }, { 0x666, 0x1000, 0x666 }, 0, 0xD2, 0, 0, 0, 0, -1, 0x30D4, 0, FxAtMinion_800B2BA8 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
int data_800B3B58[4] = {
    -0x89, 0, -0x177, 0x155,
};
MapInstr script_800B3B68[135] = {
    { 5, 0, 0, 0 },
    { 7, 0, 7, 0 },
    { 0x67, 1, 0, 0 },
    { 0x5E, 0, 1, 0 },
    { 0x13, 0, 0, MAP_REF(data_800B3B58) },
    { 0x1B, 1, 0, 0 },
    { 0x1C, 1, 1, 0 },
    { 0x48, 0, 0x10D, 5 },
    { 0x46, 1, 0, MAP_REF(data_800B3730) },
    { 0xD, 0, 2, 0 },
    { 0x55, 0, 2, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B38C4) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B2628) },
    { 0x67, 2, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x48, 0, 0x111, 1 },
    { 0x48, 0, 0x112, 1 },
    { 0x56, 0, 2, 0 },
    { 0x55, 0, 3, 0 },
    { 0x61, 0, 2, 0 },
    { 0x49, 0, 0x1130120, 1 },
    { 0xD, 0, 1, 0 },
    { 0x3E, 0xB, 2, 5 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B29B0) },
    { 0x56, 0, 3, 0 },
    { 0x55, 0, 2, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B391C) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B2628) },
    { 0x49, 1, 0x40005, 5 },
    { 0x48, 0, 0x114, 1 },
    { 0x48, 0, 0x115, 1 },
    { 0x48, 0, 0x116, 1 },
    { 0xD, 0, 3, 0 },
    { 0xC, 0, 0xF, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B29B0) },
    { 0x4B, 0, 0, MAP_REF(effects_800B39A0) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B2628) },
    { 0xC, 0, 0x1E, 0 },
    { 0x67, 0xD, 0x2F, 0 },
    { 0xC, 0, 0xA, 0 },
    { 0x48, 0, 0x117, 1 },
    { 0xC, 0, 0x50, 0 },
    { 0x46, 1, 0, MAP_REF(data_800B375C) },
    { 0x49, 0, 0x118010E, 1 },
    { 0x49, 0, 0x119010E, 1 },
    { 0x48, 1, 7, 1 },
    { 0xD, 0, 3, 0 },
    { 0x56, 0, 2, 0 },
    { 0x55, 0, 3, 0 },
    { 0x38, 1, 0, 1 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x80001, 1 },
    { 0x42, 0, 1, 0 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x90001, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x56, 0, 3, 0 },
    { 0x55, 0, 4, 0 },
    { 0x38, 1, 0, 2 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0xA0001, 1 },
    { 0x42, 0, 1, 0 },
    { 0x48, 1, 0xB, 1 },
    { 0x42, 0, 2, 0 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0xC0001, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x56, 0, 4, 0 },
    { 0x55, 0, 1, 0 },
    { 0x38, 1, 0, 3 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x80001, 1 },
    { 0x42, 0, 1, 0 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0xD000E, 1 },
    { 0x42, 0, 3, 0 },
    { 0x3F, 0, 0, 0 },
    { 0x38, 2, 0, 4 },
    { 0x42, 0, 0, 0 },
    { 0x49, 0, 0x11A010F, 1 },
    { 0x48, 1, 3, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x56, 0, 1, 0 },
    { 0x55, 0, 5, 0 },
    { 0x46, 2, 0, MAP_REF(unknown_800B35B0) },
    { 0x38, 2, 0, 5 },
    { 0x3F, 0, 0, 0 },
    { 0x56, 0, 5, 0 },
    { 0x55, 0, 3, 0 },
    { 0x38, 2, 0, 6 },
    { 0x3F, 0, 0, 0 },
    { 0x49, 0, 0x11B010E, 1 },
    { 0xD, 0, 1, 0 },
    { 0x56, 0, 3, 0 },
    { 0x55, 0, 1, 0 },
    { 0x46, 1, 0, MAP_REF(data_800B378C) },
    { 0xD, 0, 2, 0 },
    { 0x48, 1, 0x10, 1 },
    { 0xC, 0, 0x1E, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B29B0) },
    { 0x4B, 0, 0, MAP_REF(effects_800B3AD4) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B2628) },
    { 0x49, 0, 0x11C011F, 1 },
    { 0xC, 0, 0xF0, 0 },
    { 0x48, 0, 0x11D, 1 },
    { 0x3E, 0xC, 1, 5 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B29B0) },
    { 0x56, 0, 1, 0 },
    { 0x55, 0, 6, 0 },
    { 0x49, 0, 0x11E0110, 1 },
    { 0x38, 2, 0, 8 },
    { 0x3F, 0, 0, 0 },
    { 0x56, 0, 6, 0 },
    { 0x55, 0, 1, 0 },
    { 0x38, 2, 0, 9 },
    { 0x3F, 0, 0, 0 },
    { 0x56, 0, 1, 0 },
    { 0x38, 2, 0, 0xA },
    { 0x3F, 0, 0, 0 },
    { 0x46, 2, 0, MAP_REF(data_800B35DC) },
    { 0xD, 0, 4, 0 },
    { 0x3E, 8, 1, 2 },
    { 0x67, 0xC, 0xFF00, 0 },
    { 0x67, 3, 0x1E, 0 },
    { 0xC, 0, 0x3C, 0 },
    { 0x67, 0xC, 0xFF03, 0x7C },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B29B0) },
    { 0x20, 0, 1, 0 },
    { 0x20, 0, 0x77, 0 },
    { 0x57, 0, 0x68, 0 },
    { 0x51, 2, 0x10001, 0x47 },
    { 8, 0, 7, 0 },
    { 4, 0, 0, 0 },
    { 0x58, 0, 0, 0 },
    { 3, 0, 0, 0 },
};
MapMinion minion_800B43D8 = { &model_800B37D0, 0, { 0x1CE, -0xB8, 0 }, 0x977, 0, 5, 0, 0xB };
MapMinion minion_800B43FC = { &model_800B3610, 0, { -0x25, -0xAF, 0x6A }, 0x67D, 0, 0x47, 9, 0xB };
MapEvent events_800B4420[5] = {
    { -1, 0xF, &minion_800B43D8, 0x14, { MinionInit_800B22F0 } },
    { -1, 0xF, &minion_800B43FC, 0x14, { MinionInit_800B22F0 } },
    { -1, 8, script_800B3B68, 0, { 0 } },
    { -1, 0xB, voices_800B37FC, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
short bones_800B4484[92] = {
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
int scale_800B453C[3] = {
    0x1000, 0x1000, 0x1000,
};
const char unknown_800B22C0[4] = "n";
const char str_800B22C4[12] = "\x82""f\x82\x81\x82\x92\x82\x81\x82\x89";
const char str_800B22D0[12] = "\x82l\x82\x81\x82\x88\x82\x82\x82\x95";
const MapFxInits fxInits_800B22DC = { { FxSprite_800B27B4, 0, 0, 0, FxLight_800B2AE8 } };
