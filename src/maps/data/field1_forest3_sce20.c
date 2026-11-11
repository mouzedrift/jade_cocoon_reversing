#include "maps/map.h"

void MinionInit_800B22EC(MapEnt* ent);
int AddEffects_800B2624(MapFx* fx);
void FxModel_800B27B0(MapEnt* ent);
void MapInit_800B29D8(int phase);
void MinionIdle_800B2A44(MapEnt* ent);
int EndEffects_800B2A4C(void);
void FxInit_800B2ACC(MapEnt* ent);
void FxMdec_800B2B84(MapEnt* ent);
void FxAtLevant_800B2C70(int* pos, short* rot);
void StartMapTask_800B2D60(void);
void MapTaskLoad_800B2D90(EventEntry* entry, int* st);
void MapTask_800B2E28(EventEntry* entry, int* st);
int LeaveArea_800B2EE0(MapEvent* ev, int area);
int EnterArea_800B2FFC(MapEvent* ev, int area, int prev);
void RequestModels_800B3104(MapEvent* ev);
void EntityTask_800B31D4(EventEntry* entry, MapEnt* ent);
int AddEntity_800B3254(void* ev);
int MinionF_800B3380(void);
int MinionF_800B3388(void);
int FxFrame_800B3390(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B3414(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B34E0(MapFx* fx, MapFxWork* w);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[20];
extern const MapFxInits fxInits_800B22D8;
extern short bones_800B3628[64];
extern ActorScriptCmd* script_800B36A8;
extern MapActorModel model_800B36AC;
extern MapVoice voices_800B36D8[5];
extern int data_800B3700[4];
extern MapFx effects_800B3710[2];
extern MapFx effects_800B3768[2];
extern MapFx effects_800B37C0[2];
extern MapFx effects_800B3818[2];
extern MapFx effects_800B3870[2];
extern MapFx effects_800B38C8[2];
extern MapFx effects_800B3920[2];
extern MapFx effects_800B3978[2];
extern MapFx effects_800B39D0[2];
extern MapFx effects_800B3A28[2];
extern MapFx effects_800B3A80[2];
extern MapFx effects_800B3AD8[2];
extern int data_800B3B30[12];
extern MapInstr script_800B3B60[115];
extern MapMinion minion_800B4290;
extern MapEvent events_800B42B4[4];
extern short bones_800B4304[92];
extern int scale_800B43BC[3];
extern int data_800B43C8[1];
extern int data_800B43CC[1];

short bones_800B3628[64] = {
    0, 0, 0, 0x46, 1, 1, 1, 0,
    2, 0x102, 2, 0xB, 3, 0x203, 3, 0xB,
    4, 0x304, 4, 0xB, 5, 0x405, 5, 0xB,
    3, 0x206, 6, 0xB, 4, 0x307, 7, 0xB,
    5, 0x408, 8, 0xB, 3, 0x209, 9, 0xB,
    4, 0x30A, 0xA, 0xB, 5, 0x40B, 0xB, 0xB,
    3, 0x20C, 0xC, 0xB, 4, 0x30D, 0xD, 0xB,
    5, 0x40E, 0xE, 0xB, -1, -1, -1, -1,
};
ActorScriptCmd* script_800B36A8 = 0;
MapActorModel model_800B36AC = { str_800B22C4, 0x61, bones_800B3628, 0, 0, 0, 4, &script_800B36A8, 0, 0x800000, 0, 0 };
MapVoice voices_800B36D8[5] = {
    { 0, 0, { 0x15, 0x4C3, 0x16 } },
    { 0, 1, { 0, 0x4C4, 0x2C } },
    { 0, 2, { 7, 0x4C6, 0x14 } },
    { 0, 3, { 0x12, 0x4C7, 0x31 } },
    { 0, 0, { -1, 0, 0 } },
};
int data_800B3700[4] = {
    0x92E, 0, -0x20F5, 0,
};
MapFx effects_800B3710[2] = {
    { 1, 0x68, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x5A, 0, 0, 0, 0, 0x59, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3768[2] = {
    { 1, 0x69, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x10E, 0, 0, 0, 0, 0x10D, 0, 0, (void*)FxAtLevant_800B2C70 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B37C0[2] = {
    { 1, 0x6A, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, 0, 0, 0, 0x1D, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3818[2] = {
    { 1, 0x6B, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, 0, 0, 0, 0x1D, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3870[2] = {
    { 1, 0x6B, { 0, 0, 0 }, { 0, 0, 0 }, 0, 1, 0, -1, 0x1D, 0x1D, 0x1D, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B38C8[2] = {
    { 1, 0x6C, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, -1, 0, 0, 0x1D, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3920[2] = {
    { 1, 0x6D, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, 0, 0, 0, 0x1D, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3978[2] = {
    { 1, 0x6D, { 0, 0, 0 }, { 0, 0, 0 }, 0, 1, 0, -1, 0x1D, 0x1D, 0x1D, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B39D0[2] = {
    { 1, 0x6E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x2D, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3A28[2] = {
    { 1, 0x6E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, 0, 0, 0, 0x1D, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3A80[2] = {
    { 1, 0x6F, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, -1, 0, 0, 0x1D, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3AD8[2] = {
    { 1, 0x70, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, -1, 0, 0, 0x1D, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
int data_800B3B30[12] = {
    -0x1FEF1, -0xFDF9, 0x1000000, -0x1FDE9, 0x1E0000, -0x1FDEC, 0x40000000, -0xFEF8,
    -0xFDF5, 0, -0x1FEF0, -0x1FF00,
};
MapInstr script_800B3B60[115] = {
    { 5, 0, 0, 0 },
    { 7, 0, 3, 0 },
    { 0x5E, 0, 1, 0 },
    { 0x67, 1, 0, 0 },
    { 0x13, 0, 0, MAP_REF(data_800B3700) },
    { 0x55, 0, 1, 0 },
    { 0x67, 2, 0x1E, 0 },
    { 0x67, 0xC, 0x6C, 0 },
    { 0x49, 0, 0xC100C9, 5 },
    { 0xC, 0, 0x3C, 0 },
    { 0x56, 0, 1, 0 },
    { 0x55, 0, 2, 0 },
    { 0xD, 0, 1, 0 },
    { 0xC, 0, 0x5A, 0 },
    { 0x56, 0, 2, 0 },
    { 0x55, 0, 3, 0 },
    { 0x49, 0, 0xC200CA, 1 },
    { 0xC, 0, 0x78, 0 },
    { 0x56, 0, 3, 0 },
    { 0x55, 0, 4, 0 },
    { 0xC, 0, 0x5A, 0 },
    { 0x56, 0, 4, 0 },
    { 0x55, 0, 5, 0 },
    { 0x68, 1, 0x16, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B3710) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B2624) },
    { 0x4B, 0, 0, MAP_REF(effects_800B3768) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B2624) },
    { 0x67, 0xD, 0x1D, 0 },
    { 0x67, 0xE, 0x18, MAP_REF(data_800B43C8) },
    { 0xC, 0, 0x3C, 0 },
    { 0x49, 0, 0xC300CB, 1 },
    { 0xD, 0, 1, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B2A4C) },
    { 0x56, 0, 5, 0 },
    { 0x55, 0, 6, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B37C0) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B2624) },
    { 0x67, 0xD, 0x1C, 0 },
    { 0x67, 0xF, 0x18, MAP_REF(data_800B43C8) },
    { 0x67, 0xE, 0x19, MAP_REF(data_800B43CC) },
    { 0xC, 0, 0x1E, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B2A4C) },
    { 0x56, 0, 6, 0 },
    { 0x55, 0, 7, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B3818) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B2624) },
    { 0x4B, 0, 0, MAP_REF(effects_800B38C8) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B2624) },
    { 0xC, 0, 0x1E, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B3870) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B2624) },
    { 0xC, 0, 0xF, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B3920) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B2624) },
    { 0xC, 0, 0x1E, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B3978) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B2624) },
    { 0x67, 5, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B2A4C) },
    { 0xC, 0, 0x5A, 0 },
    { 0x68, 0, 0, 0 },
    { 0x56, 0, 7, 0 },
    { 0x55, 0, 8, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B39D0) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B2624) },
    { 0x4B, 0, 0, MAP_REF(effects_800B3A80) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B2624) },
    { 0x67, 0xE, 0x18, MAP_REF(data_800B43C8) },
    { 0x67, 4, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0xC, 0, 0xF, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B3A28) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B2624) },
    { 0xC, 0, 0x1E, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B2A4C) },
    { 0x56, 0, 8, 0 },
    { 0x55, 0, 9, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B3AD8) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B2624) },
    { 0x67, 0xF, 0x19, MAP_REF(data_800B43CC) },
    { 0x48, 0, 0xC4, 1 },
    { 0x49, 0, 0xC500CA, 1 },
    { 0x56, 0, 9, 0 },
    { 0x55, 0, 0xA, 0 },
    { 0x1A, 2, 1, 0 },
    { 0x49, 1, 0x1D0022, 5 },
    { 0xD, 0, 2, 0 },
    { 0x49, 0, 0xC600CC, 1 },
    { 0x38, 1, 0, 0 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x1E0023, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x1F0022, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x200022, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0x210022, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x46, 1, 0, MAP_REF(data_800B3B30) },
    { 0x49, 0, 0xC700CC, 1 },
    { 0xD, 0, 3, 0 },
    { 0x56, 0, 0xA, 0 },
    { 0x49, 0, 0xC800CD, 1 },
    { 0xD, 0, 1, 0 },
    { 0x2D, 0, 0xA, 0 },
    { 0x67, 0xF, 0x18, MAP_REF(data_800B43C8) },
    { 0x67, 0xC, 0xFF00, 0 },
    { 0x67, 3, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 8, 0, 3, 0 },
    { 4, 0, 0, 0 },
    { 0x4F, 0, 5, 0 },
    { 3, 0, 0, 0 },
};
MapMinion minion_800B4290 = { &model_800B36AC, 0, { 0x898, 0, -0x2292 }, 0, 0, 0x22, 3, 3 };
MapEvent events_800B42B4[4] = {
    { -1, 0xF, &minion_800B4290, 0x14, { MinionInit_800B22EC } },
    { -1, 8, script_800B3B60, 0, { 0 } },
    { -1, 0xB, voices_800B36D8, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
short bones_800B4304[92] = {
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
int scale_800B43BC[3] = {
    0x1000, 0x1000, 0x1000,
};
int data_800B43C8[1] = {
    0,
};
int data_800B43CC[1] = {
    0,
};
const char unknown_800B22C0[4] = "\xcb";
const char str_800B22C4[20] = "\x82s\x82\x8f\x82\x94\x82\x8f\x82\x99\x82\x81\x82\x8d\x82\x95";
const MapFxInits fxInits_800B22D8 = { { 0, FxModel_800B27B0, 0, FxMdec_800B2B84, 0 } };
