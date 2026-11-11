#include "maps/map.h"

void MinionInit_800B22D4(MapEnt* ent);
void MapInit_800B260C(int phase);
void MinionIdle_800B26E4(MapEnt* ent);
int EndingDone_800B26EC(void);
void EndingSkip_800B2708(MapEnt* ent);
void EndingStop_800B274C(MapEnt* ent);
void EndingWait_800B27B4(MapEnt* ent);
void StartMapTask_800B2808(void);
void MapTaskLoad_800B2838(EventEntry* entry, int* st);
void MapTask_800B28D0(EventEntry* entry, int* st);
int LeaveArea_800B2984(MapEvent* ev, int area);
int EnterArea_800B2AA0(MapEvent* ev, int area, int prev);
void RequestModels_800B2BA8(MapEvent* ev);
int AddEntity_800B2C78(void* ev);
void MapInitOld_800B2DA4(int phase);
int MinionF_800B2E14(void);
int MinionF_800B2E1C(void);
void EntityTask_800B2E24(EventEntry* entry, MapEnt* ent);

extern const int unknown_800B22C0[1];
extern const char data_800B22C4[8];
extern const int data_800B22CC[2];
extern int unknown_800B2EA4[40];
extern int data_800B2F44[1];
extern int data_800B2F48[11];
extern int data_800B2F74[42];
extern int data_800B301C[1];
extern int data_800B3020[11];
extern int data_800B304C[18];
extern int data_800B3094[16];
extern int data_800B30D4[4];
extern int data_800B30E4[5];
extern int data_800B30F8[356];
extern int data_800B3688[196];
extern int data_800B3998[9];
extern int data_800B39BC[9];
extern int data_800B39E0[9];
extern int data_800B3A04[9];
extern MapEvent data_800B3A28[5];
extern MapEvent data_800B3A8C[5];
extern short bones_800B3AF0[92];
extern int scale_800B3BA8[3];
extern MapEvent* curEvents_800B3BB4;

int unknown_800B2EA4[40] = {
    0, 0x4F0000, 0x10001, 0xB0001, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x2060003, 0xB0006, 0x3070004, 0xB0007,
    0x4080005, 0xB0008, 0x2090003, 0xB0009, 0x30A0004, 0xB000A, 0x10B0002, 0xB000B,
    0x20C0003, 0xB000C, 0x30D0004, 0xB000D, 0x40E0005, 0xB000E, 0x20F0003, 0xB000F,
    0x3100004, 0xB0010, 0x4110005, 0xB0011, 0x2120003, 0xB0012, -1, -1,
};
int data_800B2F44[1] = {
    0,
};
int data_800B2F48[11] = {
    MAP_REF(data_800B22C4), 0x42, MAP_REF(unknown_800B2EA4), 0, 0, 0, 4, MAP_REF(data_800B2F44),
    0, 0x800000, 0,
};
int data_800B2F74[42] = {
    0, 0x4F0000, 0x10001, 0xB0001, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x2060003, 0xB0006, 0x3070004, 0xB0007,
    0x4080005, 0xB0008, 0x2090003, 0xB0009, 0x30A0004, 0xB000A, 0x10B0002, 0xB000B,
    0x20C0003, 0xB000C, 0x30D0004, 0xB000D, 0x40E0005, 0xB000E, 0x20F0003, 0xB000F,
    0x3100004, 0xB0010, 0x4110005, 0xB0011, 0x2120003, 0xB0012, 0x2130003, 0xB0013,
    -1, -1,
};
int data_800B301C[1] = {
    0,
};
int data_800B3020[11] = {
    MAP_REF(data_800B22CC), 0x41, MAP_REF(data_800B2F74), 0, 0, 0, 4, MAP_REF(data_800B301C),
    0, 0x800000, 0x10000,
};
int data_800B304C[18] = {
    0x40000, 0x1203C0, 0x50001, 0x1904E8, 0x1B0002, 0x1304E8, 0x1D0003, 0x3803C0,
    0x40004, 0x3E04EA, 0x100005, 0x1A03C1, 0x80006, 0x2103C2, 0x150007, 0x1E03C4,
    -0x10000, 0,
};
int data_800B3094[16] = {
    0xC0008, 0x1303BA, 0x190009, 0x2D04D6, 0x8000A, 0x2D04D8, 0xB010A, 0x1A04D9,
    0xF000B, 0x2303BA, 0x18000C, 0x1503BA, 0x19000D, 0x1803BA, -0x10000, 0,
};
int data_800B30D4[4] = {
    0, 0, 0x1F4, 0,
};
int data_800B30E4[5] = {
    -1, 0xD, 0, 0, MAP_REF(EndingSkip_800B2708),
};
int data_800B30F8[356] = {
    5, 0, 0, 0, 7, 0, 7, 0,
    0x5E, 0, 1, 0, 0x67, 1, 0, 0,
    0x13, 0, 0, MAP_REF(data_800B30D4), 0x1C, 1, 1, 0,
    0x48, 0, 0x14C, 5, 0x55, 0, 1, 0,
    0x67, 2, 0x1E, 0, 0x67, 6, 0, 0,
    0xC, 0, 0x5A, 0, 0x56, 0, 1, 0,
    0x55, 0, 2, 0, 0x38, 1, 0, 0,
    0x42, 0, 0, 0, 0x49, 1, 0x140013, 1,
    0x49, 2, 0x160015, 1, 0x3F, 0, 0, 0,
    0x56, 0, 2, 0, 0x55, 0, 3, 0,
    0x38, 2, 0, 1, 0x42, 0, 0, 0,
    0x49, 2, 0x180015, 1, 0x3F, 0, 0, 0,
    0x56, 0, 3, 0, 0x55, 0, 4, 0,
    0x38, 2, 0, 2, 0x42, 0, 0, 0,
    0x49, 1, 0x150013, 1, 0x49, 2, 0x180015, 1,
    0x3F, 0, 0, 0, 0x56, 0, 4, 0,
    0x55, 0, 5, 0, 0x38, 1, 0, 3,
    0x42, 0, 0, 0, 0x49, 1, 0x160013, 1,
    0x3F, 0, 0, 0, 0x56, 0, 5, 0,
    0x55, 0, 6, 0, 0x38, 2, 0, 4,
    0x42, 0, 0, 0, 0x49, 2, 0x190015, 1,
    0x3F, 0, 0, 0, 0x56, 0, 6, 0,
    0x55, 0, 1, 0, 0x38, 1, 0, 5,
    0x42, 0, 0, 0, 0x49, 1, 0x170013, 1,
    0x3F, 0, 0, 0, 0x56, 0, 1, 0,
    0x55, 0, 0, 0, 0x38, 2, 0, 6,
    0x42, 0, 0, 0, 0x49, 1, 0x180013, 1,
    0x49, 2, 0x1A0015, 1, 0x3F, 0, 0, 0,
    0x38, 1, 0, 7, 0x42, 0, 0, 0,
    0x49, 1, 0x140013, 1, 0x49, 2, 0x160015, 1,
    0x3F, 0, 0, 0, 0x49, 1, 0x19000E, 1,
    0x49, 2, 0x1B0010, 1, 0xD, 0, 6, 0,
    0x48, 1, 0x12, 1, 0x48, 2, 0x14, 1,
    0xD, 0, 6, 0, 0x56, 0, 0, 0,
    0x55, 0, 7, 0, 0x49, 0, 0x14D014E, 1,
    0x48, 1, 0x11, 9, 0x48, 2, 0x1C, 9,
    0xC, 0, 0x78, 0, 0x56, 0, 7, 0,
    0x55, 0, 0, 0, 0x1A, 6, 0, 0,
    0x49, 0, 0x14F0150, 1, 0xD, 0, 1, 0,
    0xC, 0, 0x3C, 0, 0x56, 0, 0, 0,
    0x48, 0, 0x151, 1, 0xD, 0, 1, 0,
    0x67, 3, 0x1E, 0, 0x67, 6, 0, 0,
    0x2C, 0, 1, 0, 8, 0, 7, 0,
    4, 0, 0, 0, 0x53, 0, 0x154, 0,
    3, 0, 0, 0,
};
int data_800B3688[196] = {
    5, 0, 0, 0, 7, 0, 7, 0,
    0x5E, 0, 1, 0, 0x67, 1, 0, 0,
    0x13, 0, 0, MAP_REF(data_800B30D4), 0x1A, 1, 0, 0,
    0x11, 0, 0, MAP_REF(data_800B30E4), 0x55, 0, 5, 0,
    0x67, 2, 0x1E, 0, 0x67, 6, 0, 0,
    0x38, 2, 0, 8, 0x42, 0, 0, 0,
    0x49, 2, 0x160015, 1, 0x49, 1, 0x140013, 1,
    0x3F, 0, 0, 0, 0x56, 0, 5, 0,
    0x55, 0, 4, 0, 0x38, 2, 0, 9,
    0x42, 0, 0, 0, 0x49, 2, 0x180015, 1,
    0x3F, 0, 0, 0, 0x38, 2, 0, 0xA,
    0x42, 0, 0, 0, 0x49, 2, 0x170015, 1,
    0x42, 0, 1, 0, 0x49, 2, 0x1D0015, 1,
    0x3F, 0, 0, 0, 0x56, 0, 4, 0,
    0x55, 0, 1, 0, 0x38, 1, 0, 0xB,
    0x42, 0, 0, 0, 0x49, 1, 0x150013, 1,
    0x3F, 0, 0, 0, 0x38, 1, 0, 0xC,
    0x42, 0, 0, 0, 0x49, 1, 0x170013, 1,
    0x3F, 0, 0, 0, 0x56, 0, 1, 0,
    0x38, 1, 0, 0xD, 0x42, 0, 0, 0,
    0x49, 1, 0x180013, 1, 0x49, 2, 0x1A0015, 1,
    0x3F, 0, 0, 0, 0x67, 3, 0x1E, 0,
    0x67, 6, 0, 0, 0x4D, 0, 1, MAP_REF(EndingDone_800B26EC),
    8, 0, 7, 0, 4, 0, 0, 0,
    3, 0, 0, 0,
};
int data_800B3998[9] = {
    MAP_REF(data_800B2F48), 0, -0xE1, 0, 0x4B0, -0x800, 0x13, 0,
    2,
};
int data_800B39BC[9] = {
    MAP_REF(data_800B3020), 0, 2, 0, 0x411, -0x800, 0x15, 0,
    2,
};
int data_800B39E0[9] = {
    MAP_REF(data_800B2F48), 0, -0xE1, 0, 0x4B0, -0x800, 0x13, 2,
    2,
};
int data_800B3A04[9] = {
    MAP_REF(data_800B3020), 0, 2, 0, 0x411, -0x800, 0x15, 2,
    2,
};
MapEvent data_800B3A28[5] = {
    { -1, 8, data_800B30F8, 0, { 0 } },
    { -1, 0xF, data_800B3998, 0x14, { (void*)MinionInit_800B22D4 } },
    { -1, 0xF, data_800B39BC, 0x14, { (void*)MinionInit_800B22D4 } },
    { -1, 0xB, data_800B304C, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
MapEvent data_800B3A8C[5] = {
    { -1, 8, data_800B3688, 0, { 0 } },
    { -1, 0xF, data_800B39E0, 0x14, { (void*)MinionInit_800B22D4 } },
    { -1, 0xF, data_800B3A04, 0x14, { (void*)MinionInit_800B22D4 } },
    { -1, 0xB, data_800B3094, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
short bones_800B3AF0[92] = {
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
int scale_800B3BA8[3] = {
    0x1000, 0x1000, 0x1000,
};
MapEvent* curEvents_800B3BB4 = 0;
const int unknown_800B22C0[1] = {
    0x134,
};
const char data_800B22C4[8] = "\x82q\x82\x81";
const int data_800B22CC[2] = {
    -0x6A7D937E, 0x24030000,
};
