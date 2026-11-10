#include "maps/map.h"

void Warp_800B22D0(MapEnt* ent);
void MinionInit_800B23F4(MapEnt* ent);
void MapInit_800B272C(int phase);
void MinionIdle_800B2798(MapEnt* ent);
void TintParty_800B27A0(MapEnt* ent);
void FadeBarsInit_800B2834(MapEnt* ent);
void FadeBars_800B2868(MapEnt* ent);
void DrawFadeBars_800B2980(MapFadeBars* bars, int* t);
void StartMapTask_800B2AB8(void);
void MapTaskLoad_800B2AE8(EventEntry* entry, int* st);
void MapTask_800B2B80(EventEntry* entry, int* st);
int LeaveArea_800B2C38(MapEvent* ev, int area);
int EnterArea_800B2D54(MapEvent* ev, int area, int prev);
void RequestModels_800B2E5C(MapEvent* ev);
int AddEntity_800B2F2C(void* ev);
int MinionF_800B3058(void);
int MinionF_800B3060(void);
void EntityTask_800B3068(EventEntry* entry, MapEnt* ent);

extern const char unknown_800B22C0[4];
extern const int str_800B22C4[3];
extern short bones_800B30E8[80];
extern ActorScriptCmd* script_800B3188;
extern MapActorModel model_800B318C;
extern MapWarp warp_800B31B8;
extern MapWarp warp_800B31D0;
extern MapEvent event_800B31E8;
extern int data_800B31FC[4];
extern MapInstr script_800B320C[22];
extern MapMinion minion_800B336C;
extern MapEvent events_800B3390[7];
extern short bones_800B341C[92];
extern int scale_800B34D4[3];

short bones_800B30E8[80] = {
    0, 0, 0, 0x46, 1, 1, 1, 0,
    2, 0x102, 2, 0xB, 3, 0x203, 3, 0xB,
    4, 0x304, 4, 0xB, 5, 0x405, 5, 0xB,
    6, 0x506, 6, 0xB, 3, 0x207, 7, 0xB,
    4, 0x708, 8, 0xB, 5, 0x809, 9, 0xB,
    3, 0x20A, 0xA, 0, 4, 0xA0B, 0xB, 0xB,
    2, 0x10C, 0xC, 0xB, 3, 0xC0D, 0xD, 0xB,
    4, 0xD0E, 0xE, 0xB, 5, 0xE0F, 0xF, 0xB,
    3, 0xC10, 0x10, 0xB, 4, 0x1011, 0x11, 0xB,
    5, 0x1112, 0x12, 0xB, -1, -1, -1, -1,
};
ActorScriptCmd* script_800B3188 = 0;
MapActorModel model_800B318C = { (const char*)str_800B22C4, 0x39, bones_800B30E8, 0, 0, 0, 4, &script_800B3188, 0, 0x800000, 0, 0 };
MapWarp warp_800B31B8 = { { 0, 0, -0x56B }, 0x4000, 0, 1, { 2, 6, 2 } };
MapWarp warp_800B31D0 = { { 0x4F1, 0x32, 0 }, 0, 0, 0, { 2, 6, 0 } };
MapEvent event_800B31E8 = { 0x200000, 0xA00140, 0, 0xF00140, { (void*)0x1E } };
int data_800B31FC[4] = {
    -0x3E, 0, -0x16A, -0x4FA,
};
MapInstr script_800B320C[22] = {
    { 0x1F, 1, 0x2E, 0 },
    { 0xA, 0, 0xFF, 0 },
    { 0xA, 0, 0x10, 0 },
    { 9, 0, 0x10, 0 },
    { 0x20, 0, 0x2E, 0 },
    { 5, 0, 0, 0 },
    { 7, 0, 3, 0 },
    { 0x5E, 0, 0, 0 },
    { 0x2E, 1, 0, MAP_REF(event_800B31E8) },
    { 0x67, 5, 1, 0 },
    { 0x13, 0, 0, MAP_REF(data_800B31FC) },
    { 0x48, 0, 0xD8, 5 },
    { 0xC, 0, 0x1E, 0 },
    { 0x67, 4, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x48, 0, 0xD9, 1 },
    { 0xD, 0, 1, 0 },
    { 0x2E, 1, 3, MAP_REF(event_800B31E8) },
    { 8, 0, 3, 0 },
    { 4, 0, 0, 0 },
    { 9, 0, 0xFF, 0 },
    { 3, 0, 0, 0 },
};
MapMinion minion_800B336C = { &model_800B318C, 0, { -0xF5, -0x19, -0x2B7 }, -0x14, -1, 0xE, 6, 2 };
MapEvent events_800B3390[7] = {
    { -1, 1, &warp_800B31B8, 0, { Warp_800B22D0 } },
    { -1, 1, &warp_800B31D0, 0, { Warp_800B22D0 } },
    { -1, 0xF, &minion_800B336C, 0x14, { MinionInit_800B23F4 } },
    { -1, 0xD, (void*)0x2, 0, { TintParty_800B27A0 } },
    { -1, 8, script_800B320C, 0, { 0 } },
    { -1, 0xD, &event_800B31E8, 4, { FadeBarsInit_800B2834 } },
    { 0, 0x12, 0, 0, { 0 } },
};
short bones_800B341C[92] = {
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
int scale_800B34D4[3] = {
    0x1000, 0x1000, 0x1000,
};
const char unknown_800B22C0[4] = "\x82";
const int str_800B22C4[3] = {
    -0x7E7D9E7E, -0x7E7D7D7E, -0x7E7E0000,
};
