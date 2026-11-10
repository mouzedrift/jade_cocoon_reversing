#include "maps/map.h"

void MinionInit_800B22D0(MapEnt* ent);
int AddEffects_800B2608(MapFx* fx);
void FxSprite_800B2794(MapEnt* ent);
void MapInit_800B2908(int phase);
void MinionIdle_800B2974(MapEnt* ent);
int EndEffects_800B297C(void);
void FxInit_800B29FC(MapEnt* ent);
void FxAtLevantBone7_800B2AA0(int* pos, short* rot);
void FxAtLevantBone7Flip_800B2B90(int* pos, short* rot);
void StartMapTask_800B2C84(void);
void MapTaskLoad_800B2CB4(EventEntry* entry, int* st);
void MapTask_800B2D4C(EventEntry* entry, int* st);
int LeaveArea_800B2E04(MapEvent* ev, int area);
int EnterArea_800B2F20(MapEvent* ev, int area, int prev);
void RequestModels_800B3028(MapEvent* ev);
void EntityTask_800B30F8(EventEntry* entry, MapEnt* ent);
int AddEntity_800B3178(void* ev);
int MinionF_800B32A4(void);
int MinionF_800B32AC(void);
int FxFrame_800B32B4(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B3338(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B3404(MapFx* fx, MapFxWork* w);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[12];
extern int data_800B354C[3];
extern short bones_800B3558[116];
extern ActorScriptCmd* script_800B3640;
extern MapActorModel model_800B3644;
extern MapVoice voices_800B3670[3];
extern MapFx effects_800B3688[3];
extern MapFx effects_800B370C[3];
extern int data_800B3790[3];
extern int data_800B379C[3];
extern int data_800B37A8[4];
extern MapInstr script_800B37B8[48];
extern MapMinion minion_800B3AB8;
extern MapEvent events_800B3ADC[4];
extern short bones_800B3B2C[92];
extern int scale_800B3BE4[3];

int data_800B354C[3] = {
    0x333, 0x333, 0x333,
};
short bones_800B3558[116] = {
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
ActorScriptCmd* script_800B3640 = 0;
MapActorModel model_800B3644 = { str_800B22C4, 0x33, bones_800B3558, data_800B354C, 0, 0, 4, &script_800B3640, 0, 0x800000, 0, 0 };
MapVoice voices_800B3670[3] = {
    { 0, 0, { 0x17, 0x318, 0x17 } },
    { 0, 1, { 8, 0x319, 0x19 } },
    { 0, 0, { -1, 0, 0 } },
};
MapFx effects_800B3688[3] = {
    { 0, 0x154, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, -1, 0, 0, -1, 0x38, 0, (void*)FxAtLevantBone7_800B2AA0 },
    { 0, 0x154, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, -1, 0, 0, -1, 0x78, 0, (void*)FxAtLevantBone7Flip_800B2B90 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B370C[3] = {
    { 0, 0x155, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, 0, 0, 0, -1, 0x38, 0, (void*)FxAtLevantBone7_800B2AA0 },
    { 0, 0x155, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, 0, 0, 0, -1, 0x78, 0, (void*)FxAtLevantBone7Flip_800B2B90 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
int data_800B3790[3] = {
    0, -0x5DC, 0,
};
int data_800B379C[3] = {
    0, 0, 0,
};
int data_800B37A8[4] = {
    0, 0, 0, 0,
};
MapInstr script_800B37B8[48] = {
    { 5, 0, 0, 0 },
    { 7, 0, 3, 0 },
    { 0x67, 1, 0x1E, 0 },
    { 0x5E, 0, 1, 0 },
    { 0x13, 0, 0, MAP_REF(data_800B37A8) },
    { 0x1C, 1, 1, 0 },
    { 0x55, 0, 1, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B3688) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B2608) },
    { 0x5A, 0, 1, MAP_REF(data_800B3790) },
    { 0x60, 0, 0, MAP_REF(data_800B379C) },
    { 0x67, 2, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x5C, 0, 0xF0, 0 },
    { 0x48, 0, 0x10B, 5 },
    { 0xD, 0, 1, 0 },
    { 0x56, 0, 1, 0 },
    { 0x55, 0, 2, 0 },
    { 0x49, 0, 0x1040108, 1 },
    { 0xC, 0, 0x96, 0 },
    { 0x56, 0, 2, 0 },
    { 0x55, 0, 3, 0 },
    { 0x60, 0, 0, 0 },
    { 0x49, 0, 0x1050109, 1 },
    { 0x38, 1, 0, 0 },
    { 0x3F, 0, 0, 0 },
    { 0x56, 0, 3, 0 },
    { 0x55, 0, 1, 0 },
    { 0x49, 0, 0x106010A, 1 },
    { 0xC, 0, 0x96, 0 },
    { 0x56, 0, 1, 0 },
    { 0x55, 0, 4, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B297C) },
    { 0x4B, 0, 0, MAP_REF(effects_800B370C) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B2608) },
    { 0x48, 0, 0x107, 1 },
    { 0x48, 0, 0x10C, 1 },
    { 0xC, 0, 0x78, 0 },
    { 0x56, 0, 4, 0 },
    { 0xC, 0, 0xB4, 0 },
    { 0xC, 0, 0x5A, 0 },
    { 0x67, 0xC, 0xFF00, 0 },
    { 0x67, 3, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 8, 0, 3, 0 },
    { 4, 0, 0, 0 },
    { 0x53, 0, 0xCF, 0 },
    { 3, 0, 0, 0 },
};
MapMinion minion_800B3AB8 = { &model_800B3644, 0, { 0, 0, 0 }, 0, 0, 0, 1, 0xB };
MapEvent events_800B3ADC[4] = {
    { -1, 0xF, &minion_800B3AB8, 0x14, { MinionInit_800B22D0 } },
    { -1, 8, script_800B37B8, 0, { 0 } },
    { -1, 0xB, voices_800B3670, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
short bones_800B3B2C[92] = {
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
int scale_800B3BE4[3] = {
    0x1000, 0x1000, 0x1000,
};
const char unknown_800B22C0[4] = "\xf7";
const char str_800B22C4[12] = "\x82l\x82\x81\x82\x88\x82\x82\x82\x95";
