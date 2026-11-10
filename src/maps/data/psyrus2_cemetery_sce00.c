#include "maps/map.h"

void MinionInit_800B22D0(MapEnt* ent);
void ScriptSpot_800B2608(MapEnt* ent);
void MinionIdle_800B267C(MapEnt* ent);
void TintParty_800B2684(MapEnt* ent);
void CameraOrbitInit_800B2718(MapEnt* ent);
void CameraOrbit_800B2750(MapEnt* ent);
void MapInit_800B2758(int phase);
void StartMapTask_800B27C8(void);
void MapTaskLoad_800B27F8(EventEntry* entry, int* st);
void MapTask_800B2890(EventEntry* entry, int* st);
int LeaveArea_800B2948(MapEvent* ev, int area);
int EnterArea_800B2A64(MapEvent* ev, int area, int prev);
void RequestModels_800B2B6C(MapEvent* ev);
int AddEntity_800B2C3C(void* ev);
int StopLevantIfSet_800B2D68(MapScriptSpot* spot);
int MinionF_800B2D98(void);
int MinionF_800B2DA0(void);
void EntityTask_800B2DA8(EventEntry* entry, MapEnt* ent);

extern const char unknown_800B22C0[4];
extern const int str_800B22C4[3];
extern short bones_800B2E28[92];
extern ActorScriptCmd* script_800B2EE0;
extern MapActorModel model_800B2EE4;
extern int data_800B2F10[2];
extern MapMinion minion_800B2F18;
extern int data_800B2F3C[1];
extern MapEvent events_800B2F40[5];
extern int data_800B2FA4[16];
extern short bones_800B2FE4[92];
extern int scale_800B309C[3];

short bones_800B2E28[92] = {
    0, 0, 0, 0x44, 1, 1, 1, 0,
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
ActorScriptCmd* script_800B2EE0 = 0;
MapActorModel model_800B2EE4 = { (const char*)str_800B22C4, 0x1E, bones_800B2E28, 0, 0, 0, 4, &script_800B2EE0, 0, 0x800000, 0, 0 };
int data_800B2F10[2] = {
    0x1010000, 0,
};
MapMinion minion_800B2F18 = { &model_800B2EE4, 0, { 0x12FE, 0, 0x296 }, -0x71C, -1, 0x2B, 4, 2 };
int data_800B2F3C[1] = {
    0,
};
MapEvent events_800B2F40[5] = {
    { -1, 0, data_800B2F10, 0, { ScriptSpot_800B2608 } },
    { -1, 0xF, &minion_800B2F18, 0x14, { MinionInit_800B22D0 } },
    { -1, 0xD, (void*)0x2, 0, { (void*)TintParty_800B2684 } },
    { -1, 0xD, data_800B2F3C, 8, { CameraOrbitInit_800B2718 } },
    { 0, 0x12, 0, 0, { 0 } },
};
int data_800B2FA4[16] = {
    0x4B, 0, 0, 0, 0x4D, 0, 0, MAP_REF(StopLevantIfSet_800B2D68),
    0x58, 0, 0, 0, 3, 0, 0, 0,
};
short bones_800B2FE4[92] = {
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
int scale_800B309C[3] = {
    0x1000, 0x1000, 0x1000,
};
const char unknown_800B22C0[4] = "\x7f";
const int str_800B22C4[3] = {
    -0x707D907E, -0x707D6B7E, -0x7A7E0000,
};
