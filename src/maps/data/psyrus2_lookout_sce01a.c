#include "maps/map.h"

void MinionInit_800B2318(MapEnt* ent);
void Door_800B2650(MapEnt* ent);
void MapInit_800B2910(int phase);
void MinionIdle_800B2980(MapEnt* ent);
void CameraOrbitInit_800B2988(MapEnt* ent);
int LoadMinionAnim_800B29C0(MapLoadArgs* args);
int LoadMinionAnimSet_800B2A68(MapLoadArgs* args);
int FadeOutSeq_800B2AE4(void);
void StartMapTask_800B2B30(void);
void MapTaskLoad_800B2B60(EventEntry* entry, int* st);
void MapTask_800B2BF8(EventEntry* entry, int* st);
int LeaveArea_800B2CB0(MapEvent* ev, int area);
int EnterArea_800B2DCC(MapEvent* ev, int area, int prev);
void RequestModels_800B2ED4(MapEvent* ev);
int AddEntity_800B2FA4(void* ev);
int MinionF_800B30D0(void);
int MinionF_800B30D8(void);
void EntityTask_800B30E0(EventEntry* entry, MapEnt* ent);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[12];
extern const char str_800B22D0[8];
extern ActorScriptCmd* script_800B3160;
extern MapActorModel model_800B3164;
extern ActorScriptCmd* script_800B3190;
extern MapActorModel model_800B3194;
extern MapVoice voices_800B31C0[19];
extern int data_800B3258[4];
extern int data_800B3268[3];
extern MapEvent event_800B3274;
extern MapInstr script_800B3288[104];
extern MapMinion minion_800B3908;
extern MapMinion minion_800B392C;
extern MapEvent events_800B3950[5];
extern short bones_800B39B4[92];
extern int scale_800B3A6C[3];

ActorScriptCmd* script_800B3160 = 0;
MapActorModel model_800B3164 = { str_800B22C4, 0x2F, 0, 0, 0, 0, 4, &script_800B3160, 0, 0x800000, 0, 0 };
ActorScriptCmd* script_800B3190 = 0;
MapActorModel model_800B3194 = { str_800B22D0, 0x2C, 0, 0, 0, 0, 4, &script_800B3190, 0, 0x800000, 0, 1 };
MapVoice voices_800B31C0[19] = {
    { 0, 0, { 0x16, 0x2B4, 0x1B } },
    { 1, 0, { 0x1C, 0x2B4, 0x16 } },
    { 1, 1, { 0xB, 0x2B7, 0x16 } },
    { 1, 2, { 0x12, 0x2B7, 0x19 } },
    { 1, 3, { 2, 0x2B8, 0x10 } },
    { 1, 4, { 3, 0x2B8, 0x10 } },
    { 2, 0, { 0xE, 0x275, 0x1D } },
    { 2, 1, { 0x1A, 0x275, 0x23 } },
    { 2, 2, { 0x17, 0x276, 0x19 } },
    { 3, 0, { 5, 0x2BA, 0x18 } },
    { 3, 1, { 0x15, 0x2BB, 0x19 } },
    { 4, 0, { 0xD, 0x277, 0x14 } },
    { 4, 1, { 0x16, 0x278, 0x13 } },
    { 4, 2, { 0, 0x279, 0x15 } },
    { 5, 0, { 0x1E, 0x2BB, 0x1D } },
    { 5, 1, { 4, 0x2BC, 0x16 } },
    { 5, 2, { 0x18, 0x2BC, 0x16 } },
    { 6, 0, { 0x14, 0x2BD, 0xB } },
    { 0, 0, { -1, 0, 0 } },
};
int data_800B3258[4] = {
    0xC8, -0x759, 0x23F, 0,
};
int data_800B3268[3] = {
    -0x134, -0x18EB, 0x269,
};
MapEvent event_800B3274 = { -1, 0xD, 0, 8, { CameraOrbitInit_800B2988 } };
MapInstr script_800B3288[104] = {
    { 5, 0, 0, 0 },
    { 7, 0, 7, 0 },
    { 0x67, 1, 0, 0 },
    { 0x5E, 0, 1, 0 },
    { 0x5A, 0, 1, MAP_REF(data_800B3268) },
    { 0x11, 0, 0, MAP_REF(event_800B3274) },
    { 0x13, 0, 0, MAP_REF(data_800B3258) },
    { 0x48, 0, 0xB5, 5 },
    { 0x1B, 6, 0, 0 },
    { 0x4C, 0, 0, 0 },
    { 0x4D, 0, 0, MAP_REF(LoadMinionAnim_800B29C0) },
    { 0x55, 0, 1, 0 },
    { 0x67, 2, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x2E, 0, 0, MAP_REF(event_800B3274) },
    { 0x5C, 0, 0x78, 0 },
    { 0x5D, 0, 0, 0 },
    { 0xC, 0, 0x1E, 0 },
    { 0x56, 0, 1, 0 },
    { 0x49, 2, 0x3B003C, 1 },
    { 0xD, 0, 4, 0 },
    { 0x38, 2, 0, 0 },
    { 0x42, 0, 0, 0 },
    { 0x49, 0, 0xB000B6, 1 },
    { 0x49, 2, 0x3D003C, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x4D, 0, 0, MAP_REF(FadeOutSeq_800B2AE4) },
    { 0x49, 0, 0xB100B7, 1 },
    { 0xD, 0, 1, 0 },
    { 0x49, 2, 0x3E006C, 1 },
    { 0xD, 0, 4, 0 },
    { 0x49, 0, 0xB800B6, 1 },
    { 0xD, 0, 1, 0 },
    { 0x4C, 0, 2, 0 },
    { 0x4D, 0, 0, MAP_REF(LoadMinionAnimSet_800B2A68) },
    { 0x38, 2, 0, 1 },
    { 0x42, 0, 0, 0 },
    { 0x49, 2, 0x2D0040, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 2, 0x2E0040, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 2, 0x2F003F, 1 },
    { 0x42, 0, 3, 0 },
    { 0x42, 0, 4, 0 },
    { 0x48, 2, 0x2D, 1 },
    { 0x49, 2, 0x2F003F, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x38, 1, 0, 2 },
    { 0x68, 1, 0xD, 0 },
    { 0x42, 0, 0, 0 },
    { 0x49, 0, 0xB100B7, 1 },
    { 0x49, 2, 0x300041, 1 },
    { 0x1A, 2, 1, 0 },
    { 0x49, 1, 0x45004C, 5 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x46004C, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x47004C, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x38, 2, 0, 3 },
    { 0x42, 0, 0, 0 },
    { 0x49, 2, 0x310041, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 2, 0x32006D, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x4C, 0, 3, 0 },
    { 0x4D, 0, 0, MAP_REF(LoadMinionAnimSet_800B2A68) },
    { 0x38, 1, 0, 4 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x48004C, 1 },
    { 0x68, 1, 0xF, 0 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x49004C, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x4A004C, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x48, 1, 0x4B, 1 },
    { 0x38, 2, 0, 5 },
    { 0x42, 0, 0, 0 },
    { 0x49, 2, 0x330042, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 2, 0x340043, 1 },
    { 0x49, 2, 0x350044, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 2, 0x360044, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x49, 2, 0x370045, 1 },
    { 0xD, 0, 4, 0 },
    { 0x38, 2, 0, 6 },
    { 0x42, 0, 0, 0 },
    { 0x49, 0, 0xB300B6, 1 },
    { 0x49, 2, 0x380045, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x48, 0, 0xB4, 1 },
    { 0x48, 2, 0x39, 1 },
    { 0xD, 0, 4, 0 },
    { 0x1A, 4, 0, 0 },
    { 0xC, 0, 0x3C, 0 },
    { 0x67, 3, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 8, 0, 7, 0 },
    { 4, 0, 0, 0 },
    { 0x53, 0, 0x45, 0 },
    { 3, 0, 0, 0 },
};
MapMinion minion_800B3908 = { &model_800B3194, 0, { -0x177, -0x759, 0x145 }, 0, 0, 0x4C, 1, 3 };
MapMinion minion_800B392C = { &model_800B3164, 0, { 0, -0x759, 0x20D }, 0, 0, 0x3A, 1, 2 };
MapEvent events_800B3950[5] = {
    { -1, 0xF, &minion_800B3908, 0x14, { MinionInit_800B2318 } },
    { -1, 0xF, &minion_800B392C, 0x14, { MinionInit_800B2318 } },
    { -1, 8, script_800B3288, 0, { 0 } },
    { -1, 0xB, voices_800B31C0, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
short bones_800B39B4[92] = {
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
int scale_800B3A6C[3] = {
    0x1000, 0x1000, 0x1000,
};
const char unknown_800B22C0[4] = "x";
const char str_800B22C4[12] = "\x82l\x82\x81\x82\x88\x82\x82\x82\x95";
const char str_800B22D0[8] = "\x82k\x82\x95\x82\x89";
