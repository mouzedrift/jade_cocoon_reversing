#include "maps/map.h"

void Warp_800B23C0(MapEnt* ent);
void Chest_800B24E4(MapEnt* ent);
void ChestDraw_800B26D8(MapChest* chest, MapChestWork* w);
void MinionInit_800B29A4(MapEnt* ent);
void MapInit_800B2CDC(int phase);
void ChestInit_800B2D48(MapEnt* ent);
int ChestShut_800B2E28(MapEnt* ent);
int ChestTake_800B2E34(void* arg);
int ChestText_800B2EB8(void* arg);
int ChestCheck_800B2EF0(MapEnt* ent);
void MinionIdle_800B2F30(MapEnt* ent);
int CheckReturn_800B2F38(void);
int BattleLost_800B2F94(void);
int WarpLostBattle_800B2FA4(void);
void StartMapTask_800B2FC4(void);
void MapTaskLoad_800B2FF4(EventEntry* entry, int* st);
void MapTask_800B308C(EventEntry* entry, int* st);
int LeaveArea_800B3144(MapEvent* ev, int area);
int EnterArea_800B3260(MapEvent* ev, int area, int prev);
void RequestModels_800B3368(MapEvent* ev);
int AddEntity_800B3438(void* ev);
void ChestKind1_800B3564(MapChest* chest, MapChestWork* w);
void ChestKind2_800B356C(MapChest* chest, MapChestWork* w);
int MinionF_800B3574(void);
int MinionF_800B357C(void);
void EntityTask_800B3584(EventEntry* entry, MapEnt* ent);

extern const char unknown_800B22C0[4];
extern const char data_800B22C4[44];
extern const char data_800B22F0[60];
extern const char str_800B232C[24];
extern const char data_800B2344[28];
extern const char data_800B2360[52];
extern int text_800B3604[4];
extern MapChest chest_800B3614;
extern short bones_800B365C[92];
extern ActorScriptCmd anim_800B3714[4];
extern ActorScriptCmd* script_800B3744[32];
extern int data_800B37C4[3];
extern MapActorModel model_800B37D0;
extern MapVoice voices_800B37FC[8];
extern MapWarp warp_800B383C;
extern MapWarp warp_800B3854;
extern int data_800B386C[4];
extern int data_800B387C[18];
extern MapInstr script_800B38C4[69];
extern MapMinion minion_800B3D14;
extern MapEvent events_800B3D38[7];
extern int data_800B3DC4[3];
extern int data_800B3DD0[3];
extern int data_800B3DDC[212];
extern short bones_800B412C[92];
extern int scale_800B41E4[3];

int text_800B3604[4] = {
    MAP_REF(data_800B22F0), MAP_REF(data_800B22C4), 0, 0,
};
MapChest chest_800B3614 = { 0x41, -1, 3, 3, 3, { 0x151, -0xD1, 0xA4A }, 0, text_800B3604, 0, { 0x20001, 1, 0xFFFF, 0, 0xFFFF, 0 }, { 0, -1 } };
short bones_800B365C[92] = {
    0, 0, 0, 0x4F, 1, 1, 1, 0xB,
    2, 0x102, 2, 0xB, 3, 0x203, 3, 0xB,
    4, 0x304, 4, 0xB, 5, 0x405, 5, 0xB,
    3, 0x206, 6, 0xB, 4, 0x307, 7, 0xB,
    5, 0x408, 8, 0xB, 3, 0x209, 9, 0xB,
    4, 0x30A, 0xA, 0xB, 3, 0x212, 0x12, 0xB,
    3, 0x213, 0x13, 0xB, 3, 0x214, 0x14, 0xB,
    3, 0x215, 0x15, 0xB, 2, 0x10B, 0xB, 0xB,
    3, 0x20C, 0xC, 0xB, 4, 0x30D, 0xD, 0xB,
    5, 0x40E, 0xE, 0xB, 3, 0x20F, 0xF, 0xB,
    4, 0x310, 0x10, 0xB, 5, 0x411, 0x11, 0xB,
    -1, -1, -1, -1,
};
ActorScriptCmd anim_800B3714[4] = {
    { 0xC, 2, -2, 0, 0x15, 0x10D, -2 },
    { 0xF, 1, -2, 0x103, -1, 0x201, -1 },
    { 0, 0, 0x15, 0x115, -2, 0x217, -2 },
    { 0, 0, 0x3C, 0x110, -2, 0x100, -2 },
};
ActorScriptCmd* script_800B3744[32] = {
    (void*)&commandScriptData_80079754, (void*)((char*)&commandScriptData_80079754 + 0xC), (void*)((char*)&commandScriptData_80079754 + 0x1C), (void*)((char*)&commandScriptData_80079754 + 0x54), (void*)((char*)&commandScriptData_80079754 + 0x8C), (void*)((char*)&commandScriptData_80079754 + 0xC4), (void*)((char*)&commandScriptData_80079754 + 0xFC), (void*)((char*)&commandScriptData_80079754 + 0x134),
    (void*)((char*)&commandScriptData_80079754 + 0x16C), (void*)((char*)&commandScriptData_80079754 + 0x1A4), (void*)((char*)&commandScriptData_80079754 + 0x200), (void*)((char*)&commandScriptData_80079754 + 0x238), (void*)((char*)&commandScriptData_80079754 + 0x270), (void*)((char*)&commandScriptData_80079754 + 0x2A8), (void*)((char*)&commandScriptData_80079A2C + 0x4), (void*)((char*)&commandScriptData_80079A2C + 0x1C),
    anim_800B3714, (void*)((char*)&commandScriptData_80079AC0 + 0x14), (void*)((char*)&commandScriptData_80079AC0 + 0x50), (void*)((char*)&commandScriptData_80079B44 + 0x8), (void*)((char*)&commandScriptData_80079B44 + 0x1C), (void*)((char*)&commandScriptData_80079B6C + 0x8), (void*)((char*)&commandScriptData_80079B6C + 0x20), (void*)((char*)&commandScriptData_80079B6C + 0x44),
    (void*)((char*)&commandScriptData_80079C04 + 0x14), (void*)((char*)&commandScriptData_80079C04 + 0x64), (void*)((char*)&commandScriptData_80079C04 + 0x84), (void*)((char*)&commandScriptData_80079CE0 + 0x1C), (void*)((char*)&commandScriptData_80079CE0 + 0x6C), (void*)((char*)&commandScriptData_80079DE4 + 0x14), (void*)((char*)&commandScriptData_80079DE4 + 0xB0), (void*)((char*)&commandScriptData_80079F50 + 0x14),
};
int data_800B37C4[3] = {
    2, 5, -1,
};
MapActorModel model_800B37D0 = { str_800B232C, 0x2D, bones_800B365C, 0, 0, data_800B37C4, 4, script_800B3744, 0, 0x800000, 0, 0 };
MapVoice voices_800B37FC[8] = {
    { 0, 0, { 1, 0x288, 0x12 } },
    { 1, 0, { 4, 0x288, 0x1C } },
    { 1, 1, { 0x1E, 0x288, 0xE } },
    { 2, 0, { 8, 0x28A, 0x1C } },
    { 3, 0, { 0xB, 0x28A, 0x1F } },
    { 3, 1, { 0xD, 0x28B, 0x27 } },
    { 4, 0, { 0x16, 0x28B, 0x29 } },
    { 0, 0, { -1, 0, 0 } },
};
MapWarp warp_800B383C = { { 0x724, -0x1E, 0x23D4 }, 0x4000, 0, 0, { 4, 1, 3 } };
MapWarp warp_800B3854 = { { -0x271, 0, -0x157C }, 0x4000, 0, 4, { 4, 1, 7 } };
int data_800B386C[4] = {
    0, -0x78, 0x5F5, -0x11C,
};
int data_800B387C[18] = {
    1, 1, 0, 1, 0, 0, 1, 5,
    5, 0x32, 0, 0xA, 0xD3, 0, 0, 0xD3,
    0, 0,
};
MapInstr script_800B38C4[69] = {
    { 0x4D, 0, 0, MAP_REF(CheckReturn_800B2F38) },
    { 5, 0, 0, 0 },
    { 7, 0, 3, 0 },
    { 0x13, 0, 0, MAP_REF(data_800B386C) },
    { 0x48, 0, 0xD3, 5 },
    { 0x38, 1, 0, 0 },
    { 0x3F, 0, 0, 0 },
    { 0x49, 0, 0xD400D3, 1 },
    { 0x1A, 2, 1, 0 },
    { 0x48, 1, 0x1F, 5 },
    { 0xD, 0, 3, 0 },
    { 0x38, 1, 0, 1 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x210020, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x220023, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x49, 0, 0xD500D3, 1 },
    { 0xD, 0, 1, 0 },
    { 0x38, 1, 0, 2 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x240025, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x45, 0, 1, 0 },
    { 0x45, 0, 1, 0 },
    { 0x65, 0, 0, MAP_REF(data_800B387C) },
    { 0x4E, 0, 0, MAP_REF(BattleLost_800B2F94) },
    { 0xA, 0, 0x10, 0 },
    { 0xA, 0, 0x20, 0 },
    { 9, 0, 0x10, 0 },
    { 0x1A, 2, 1, 0 },
    { 0x48, 1, 0x26, 5 },
    { 0x38, 1, 0, 3 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x270026, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x280026, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x48, 1, 0x29, 1 },
    { 0xC, 0, 0x2E, 0 },
    { 0x48, 0, 0xD6, 1 },
    { 0x49, 0, 0xD500D3, 1 },
    { 0xD, 0, 3, 0 },
    { 0x1A, 2, 0, 0 },
    { 0xA, 0, 0xFF, 0 },
    { 9, 0, 0x20, 0 },
    { 0x1A, 2, 1, 0 },
    { 0x48, 0, 0xD7, 5 },
    { 0x48, 1, 0x2A, 5 },
    { 0x67, 2, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x38, 1, 0, 4 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x2B002A, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x67, 5, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0xA, 0, 0xFF, 0 },
    { 9, 0, 0xFF, 0 },
    { 8, 0, 3, 0 },
    { 4, 0, 0, 0 },
    { 0x51, 4, 0x10006, 0x70 },
    { 0x4E, 0, 0, MAP_REF(BattleLost_800B2F94) },
    { 0xA, 0, 0xFF02, 0 },
    { 0xA, 0, 0xFF01, 0 },
    { 9, 0, 0xFF01, 0 },
    { 0x4D, 0, 0, MAP_REF(WarpLostBattle_800B2FA4) },
    { 9, 0, 0xFF02, 0 },
    { 3, 0, 0, 0 },
};
MapMinion minion_800B3D14 = { &model_800B37D0, 0, { -0x19C, -0x70, 0x84D }, -0x8AA, -1, 0x1E, 0, 3 };
MapEvent events_800B3D38[7] = {
    { -1, 1, &warp_800B383C, 0, { Warp_800B23C0 } },
    { -1, 1, &warp_800B3854, 0, { Warp_800B23C0 } },
    { -1, 4, &chest_800B3614, 0x18, { ChestInit_800B2D48 } },
    { -1, 0xF, &minion_800B3D14, 0x14, { MinionInit_800B29A4 } },
    { -1, 8, script_800B38C4, 0, { 0 } },
    { -1, 0xB, voices_800B37FC, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
int data_800B3DC4[3] = {
    MAP_REF(data_800B2344), 0, 0,
};
int data_800B3DD0[3] = {
    MAP_REF(data_800B2360), 0, 0,
};
int data_800B3DDC[212] = {
    9, 0, 0, 0, 5, 0, 0, 0,
    7, 0, 1, 0, 0x30, 0, 4, 0,
    0x31, 0, 4, 0, 0x4B, 0, 0, 0,
    0x4E, 0, 0, MAP_REF(ChestShut_800B2E28), 0xA, 0, 0x70, 0,
    0xA, 0, 0x10, 0, 9, 0, 0x10, 0,
    0x30, 0, 4, 0, 0x31, 0, 4, 0,
    0x4B, 0, 0, 0, 0x4E, 0, 0, MAP_REF(ChestTake_800B2E34),
    0xA, 0, 0x20, 0, 0xA, 0, 0x30, 0,
    0xA, 0, 0x40, 0, 9, 0, 0x20, 0,
    0x3E, -1, 4, 0, 0xA, 0, 0x50, 0,
    9, 0, 0x30, 0, 0x3B, 0, 0, -1,
    0xA, 0, 0xFF, 0, 9, 0, 0x40, 0,
    0x3B, 0, 0, -1, 0xA, 0, 0x50, 0,
    9, 0, 0x50, 0, 0x30, 0, 4, 0,
    0x31, 0, 4, 0, 0x4B, 0, 0, 0,
    0x4E, 0, 0, MAP_REF(ChestCheck_800B2EF0), 0xA, 0, 0x60, 0,
    0xA, 0, 0xFF, 0, 9, 0, 0x60, 0,
    0x30, 0, 3, 0, 0x31, 0, 3, 0,
    0x3C, 3, 0, 0, 0x30, 0, 1, 0,
    0x31, 0, 1, 0, 0x30, 0, 2, 0,
    0x31, 0, 2, 0, 0xA, 0, 0xFF, 0,
    9, 0, 0x70, 0, 0x30, 0, 4, 0,
    0x31, 0, 4, 0, 0x4B, 0, 0, 0,
    0x4E, 0, 0, MAP_REF(ChestText_800B2EB8), 0x3B, 0, 0, -1,
    0xA, 0, 0xFF, 0, 9, 0, 0xFF, 0,
    8, 0, 1, 0, 4, 0, 0, 0,
    3, 0, 0, 0,
};
short bones_800B412C[92] = {
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
int scale_800B41E4[3] = {
    0x1000, 0x1000, 0x1000,
};
const char unknown_800B22C0[4] = "\x99";
const char data_800B22C4[44] = "\x82\x81\x82\x8e\x82\x84\x81@\x82\x8d\x82\x8f\x82\x89\x82\x93\x82\x94\x81@\x82\x82\x82\x8c\x82\x95\x82\x85\x81@\x82\x87\x82\x8c\x82\x8f\x82\x97\x81""D";
const char data_800B22F0[60] = "\x82s\x82\x88\x82\x85\x81@\x82\x93\x82\x90\x82\x85\x82\x81\x82\x92\x81@\x82\x87\x82\x89\x82\x96\x82\x85\x82\x93\x81@\x82\x8f\x82\x86\x82\x86\x81@\x82\x81\x82\x8e\x81@\x82\x85\x82\x85\x82\x92\x82\x89\x82\x85";
const char str_800B232C[24] = "\x82l\x82\x81\x82\x93\x82\x8b\x82\x85\x82\x84\x81@\x82""a\x82\x8f\x82\x99";
const char data_800B2344[28] = "\x82h\x82\x94\x81""f\x82\x93\x81@\x82k\x82\x8f\x82\x83\x82\x8b\x82\x85\x82\x84\x81""D";
const char data_800B2360[52] = "\x82s\x82\x88\x82\x85\x82\x92\x82\x85\x81@\x82\x89\x82\x93\x81@\x82\x8e\x82\x8f\x82\x94\x82\x88\x82\x89\x82\x8e\x82\x87\x81@\x82\x89\x82\x8e\x82\x93\x82\x89\x82\x84\x82\x85\x81""D";
