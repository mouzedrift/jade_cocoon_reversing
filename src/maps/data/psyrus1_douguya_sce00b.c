#include "maps/map.h"

void MinionInit_800B22D4(MapEnt* ent);
void ScriptSpot_800B260C(MapEnt* ent);
void MinionIdle_800B2680(MapEnt* ent);
int ReturnFalse_800B2688(void);
void MapInit_800B2690(int phase);
void StartMapTask_800B2700(void);
void MapTaskLoad_800B2730(EventEntry* entry, int* st);
void MapTask_800B27C8(EventEntry* entry, int* st);
int LeaveArea_800B2880(MapEvent* ev, int area);
int EnterArea_800B299C(MapEvent* ev, int area, int prev);
void RequestModels_800B2AA4(MapEvent* ev);
int AddEntity_800B2B74(void* ev);
int StopLevantIfSet_800B2CA0(MapScriptSpot* spot);
int MinionF_800B2CD0(void);
int MinionF_800B2CD8(void);
void EntityTask_800B2CE0(EventEntry* entry, MapEnt* ent);

extern const char unknown_800B22C0[4];
extern const int str_800B22C4[4];
extern ActorScriptCmd* script_800B2D60;
extern MapActorModel model_800B2D64;
extern int data_800B2D90[2];
extern MapInstr script_800B2D98[121];
extern MapMinion minion_800B3528;
extern MapEvent events_800B354C[4];
extern int data_800B359C[16];
extern short bones_800B35DC[92];
extern int scale_800B3694[3];

ActorScriptCmd* script_800B2D60 = 0;
MapActorModel model_800B2D64 = { (const char*)str_800B22C4, 0x36, 0, 0, 0, 0, 4, &script_800B2D60, 0, 0x800000, 0, 1 };
int data_800B2D90[2] = {
    0x1010000, 0,
};
MapInstr script_800B2D98[121] = {
    { 9, 0, 0, 0 },
    { 0x62, 1, 2, 0 },
    { 5, 0, 0, 0 },
    { 7, 0, 3, 0 },
    { 0x61, 0, 1, 0 },
    { 0x48, 1, 0xD, 1 },
    { 0xD, 0, 2, 0 },
    { 9, 0, 1, 0 },
    { 0x4E, 0, 0, MAP_REF(ReturnFalse_800B2688) },
    { 0xA, 0, 2, 0 },
    { 0xA, 0, 3, 0 },
    { 9, 0, 2, 0 },
    { 0x43, 0, 1, 0 },
    { 0xA, 0, 0x10, 0 },
    { 9, 0, 3, 0 },
    { 0x43, 1, 1, 0 },
    { 0xA, 0, 0x10, 0 },
    { 9, 0, 0x10, 0 },
    { 0xF, 0, 0x20001, 0 },
    { 0xA, 0, 0x10A, 0 },
    { 0xA, 0, 0x10B, 0 },
    { 9, 0, 0x10A, 0 },
    { 0x38, 1, 0, 0 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0xE0021, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0xF0021, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x100021, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x20, 0 },
    { 9, 0, 0x10B, 0 },
    { 0x38, 1, 0, 6 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x1D0021, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x1E0021, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x1F0021, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0x200021, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x20, 0 },
    { 9, 0, 0x20, 0 },
    { 0x3A, 1, 0, 1 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x110021, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x30, 0 },
    { 0xA, 0, 0x40, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0x30, 0 },
    { 0xF, 0x10000, 0x20000, 0 },
    { 0xA, 0, 0x30A, 0 },
    { 0xA, 0, 0x30B, 0 },
    { 9, 0, 0x30A, 0 },
    { 0x38, 1, 0, 2 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x240029, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x270029, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x240029, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0x220029, 1 },
    { 0x42, 0, 4, 0 },
    { 0x49, 1, 0x270029, 1 },
    { 0x42, 0, 5, 0 },
    { 0x49, 1, 0x250029, 1 },
    { 0x42, 0, 6, 0 },
    { 0x49, 1, 0x270029, 1 },
    { 0x42, 0, 7, 0 },
    { 0x49, 1, 0x260029, 1 },
    { 0x42, 0, 8, 0 },
    { 0x49, 1, 0x230029, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x20, 0 },
    { 9, 0, 0x30B, 0 },
    { 0x38, 1, 0, 3 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x260029, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x230029, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x270029, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x20, 0 },
    { 9, 0, 0x40, 0 },
    { 0x59, 0, 0x10001, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0x50, 0 },
    { 0xF, 0x20000, 0x20000, 0 },
    { 0xA, 0, 0x50A, 0 },
    { 0xA, 0, 0x50B, 0 },
    { 9, 0, 0x50A, 0 },
    { 0x38, 1, 0, 4 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x180021, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x190021, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x1A0021, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0x1B0021, 1 },
    { 0x42, 0, 4, 0 },
    { 0x49, 1, 0x1C0021, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0xFF, 0 },
    { 9, 0, 0x50B, 0 },
    { 0x38, 1, 0, 5 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x1C0021, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0xFF, 0 },
    { 9, 0, 0xFF, 0 },
    { 0x61, 0, 0, 0 },
    { 0x48, 1, 0xC, 9 },
    { 8, 0, 3, 0 },
    { 4, 0, 0, 0 },
    { 0xA, 0, 0, 0 },
    { 3, 0, 0, 0 },
};
MapMinion minion_800B3528 = { &model_800B2D64, 0, { 0x19, 0, -0x19 }, -0x555, -1, 0xC, 1, 2 };
MapEvent events_800B354C[4] = {
    { -1, 0, data_800B2D90, 0, { ScriptSpot_800B260C } },
    { -1, 0xF, &minion_800B3528, 0x14, { MinionInit_800B22D4 } },
    { -1, 8, script_800B2D98, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
int data_800B359C[16] = {
    0x4B, 0, 0, 0, 0x4D, 0, 0, MAP_REF(StopLevantIfSet_800B2CA0),
    0x58, 0, 0, 0, 3, 0, 0, 0,
};
short bones_800B35DC[92] = {
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
int scale_800B3694[3] = {
    0x1000, 0x1000, 0x1000,
};
const char unknown_800B22C0[4] = "F";
const int str_800B22C4[4] = {
    -0x7E7D957E, -0x737D6D7E, -0x6B7D707E, -0x7FF50000,
};
