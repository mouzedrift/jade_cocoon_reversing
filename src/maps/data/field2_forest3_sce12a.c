#include "maps/map.h"

void Warp_800B22F0(MapEnt* ent);
void MinionInit_800B2414(MapEnt* ent);
int AddEffects_800B274C(MapFx* fx);
void FxModel_800B28D8(MapEnt* ent);
void MapInit_800B2B00(int phase);
void MinionIdle_800B2B6C(MapEnt* ent);
void FxInit_800B2B74(MapEnt* ent);
int WarpLostBattle_800B2C18(void);
void StartMapTask_800B2C38(void);
void MapTaskLoad_800B2C68(EventEntry* entry, int* st);
void MapTask_800B2D00(EventEntry* entry, int* st);
int LeaveArea_800B2DB8(MapEvent* ev, int area);
int EnterArea_800B2ED4(MapEvent* ev, int area, int prev);
void RequestModels_800B2FDC(MapEvent* ev);
void EntityTask_800B30AC(EventEntry* entry, MapEnt* ent);
int AddEntity_800B312C(void* ev);
int MinionF_800B3258(void);
int MinionF_800B3260(void);
int FxFrame_800B3268(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B32EC(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B33B8(MapFx* fx, MapFxWork* w);

extern const int unknown_800B22C0[1];
extern const char str_800B22C4[20];
extern const int str_800B22D8[6];
extern short bones_800B3500[64];
extern int data_800B3580[12];
extern ActorScriptCmd* script_800B35B0;
extern MapActorModel model_800B35B4;
extern short bones_800B35E0[96];
extern ActorScriptCmd anim_800B36A0[4];
extern int anim_800B36D0[19];
extern int anim_800B371C[19];
extern ActorScriptCmd anim_800B3768[4];
extern ActorScriptCmd* script_800B3798[33];
extern MapActorModel model_800B381C;
extern MapVoice voices_800B3848[11];
extern MapWarp warp_800B38A0;
extern MapFx effects_800B38B8[6];
extern int data_800B39C0[18];
extern MapInstr script_800B3A08[107];
extern MapMinion minion_800B40B8;
extern MapMinion minion_800B40DC;
extern MapEvent events_800B4100[6];
extern short bones_800B4178[92];
extern int scale_800B4230[3];

short bones_800B3500[64] = {
    0, 0, 0, 0x46, 1, 1, 1, 0,
    2, 0x102, 2, 0xB, 3, 0x203, 3, 0xB,
    4, 0x304, 4, 0xB, 5, 0x405, 5, 0xB,
    3, 0x206, 6, 0xB, 4, 0x307, 7, 0xB,
    5, 0x408, 8, 0xB, 3, 0x209, 9, 0xB,
    4, 0x30A, 0xA, 0xB, 5, 0x40B, 0xB, 0xB,
    3, 0x20C, 0xC, 0xB, 4, 0x30D, 0xD, 0xB,
    5, 0x40E, 0xE, 0xB, -1, -1, -1, -1,
};
int data_800B3580[12] = {
    -0x1FEF1, -0xFDF5, 0x10000, -0xFDFA, 0x1000000, -0x1FDE9, 0x5A0000, -0x1FDEC,
    0x40000000, -0xFEF8, -0x1FEF0, -0x1FF00,
};
ActorScriptCmd* script_800B35B0 = 0;
MapActorModel model_800B35B4 = { str_800B22C4, 0x60, bones_800B3500, 0, 0, 0, 4, &script_800B35B0, 0, 0x800000, 0, 0 };
short bones_800B35E0[96] = {
    0, 0, 0, 0x4E, 1, 1, 1, 0xB,
    2, 0x102, 2, 0xB, 3, 0x203, 3, 0xB,
    4, 0x304, 4, 0xB, 5, 0x405, 5, 0xB,
    2, 0x106, 6, 0xB, 3, 0x207, 7, 0xB,
    4, 0x308, 8, 0xB, 5, 0x409, 9, 0xB,
    2, 0x10A, 0xA, 0xB, 3, 0x20B, 0xB, 0xB,
    4, 0x30C, 0xC, 0xB, 5, 0x40D, 0xD, 0xB,
    2, 0x10E, 0xE, 0xB, 3, 0x20F, 0xF, 0xB,
    4, 0x310, 0x10, 0xB, 5, 0x411, 0x11, 0xB,
    3, 0x212, 0x12, 0xB, 4, 0x313, 0x13, 0xB,
    5, 0x414, 0x14, 0xB, 2, 0x115, 0x15, 0xB,
    2, 0x116, 0x16, 0xB, -1, -1, -1, -1,
};
ActorScriptCmd anim_800B36A0[4] = {
    { 0xC, 2, -2, 0, 0x15, 0x10D, -2 },
    { 0xF, 1, -2, 0x103, -1, 0x201, -1 },
    { 0, 0, 0x15, 0x115, -2, 0x217, -2 },
    { 0, 0, 0x3C, 0x110, -2, 0x100, -2 },
};
int anim_800B36D0[19] = {
    -0x1FDF4, 0x1A0000, -0x1FEF3, -0x1FEF1, -0xFDF9, 0x1000000, -0xFEFD, -0xFDFF,
    0x1A0000, -0x1FDEC, 0x40000000, -0xFEF8, -0xFDF5, 0, -0x1FEF0, -0x1FEEF,
    -0xFDF2, 0x1A0000, -0x1FF00,
};
int anim_800B371C[19] = {
    -0x1FDF4, 0x1B0000, -0x1FEF3, -0x1FEF1, -0xFDF5, 0x10000, -0xFDFA, 0x1000000,
    -0xFDFF, 0x1B0000, -0x1FDEC, 0x40000000, -0xFEF8, -0x1FEF0, -0xFDFF, 0x40000,
    -0xFDF2, 0x1B0000, -0x1FF00,
};
ActorScriptCmd anim_800B3768[4] = {
    { 0xF, 1, -2, 0x207, -1, 0, 0x100 },
    { 0x17, 2, -2, 0, 0x5A, 0x214, -2 },
    { 0, 0, 0x4000, 0x108, -1, 0x20B, -1 },
    { 0, 0, 0, 0x110, -2, 0x100, -2 },
};
ActorScriptCmd* script_800B3798[33] = {
    (void*)&commandScriptData_80079754, (void*)((char*)&commandScriptData_80079754 + 0xC), (void*)((char*)&commandScriptData_80079754 + 0x1C), (void*)((char*)&commandScriptData_80079754 + 0x54), (void*)((char*)&commandScriptData_80079754 + 0x8C), (void*)((char*)&commandScriptData_80079754 + 0xC4), (void*)((char*)&commandScriptData_80079754 + 0xFC), (void*)((char*)&commandScriptData_80079754 + 0x134),
    (void*)((char*)&commandScriptData_80079754 + 0x16C), (void*)((char*)&commandScriptData_80079754 + 0x1A4), (void*)((char*)&commandScriptData_80079754 + 0x200), (void*)((char*)&commandScriptData_80079754 + 0x238), (void*)((char*)&commandScriptData_80079754 + 0x270), (void*)((char*)&commandScriptData_80079754 + 0x2A8), (void*)((char*)&commandScriptData_80079A2C + 0x4), (void*)((char*)&commandScriptData_80079A2C + 0x1C),
    anim_800B36A0, (ActorScriptCmd*)anim_800B36D0, (ActorScriptCmd*)anim_800B371C, (void*)((char*)&commandScriptData_80079B44 + 0x8), (void*)((char*)&commandScriptData_80079B44 + 0x1C), (void*)((char*)&commandScriptData_80079B6C + 0x8), (void*)((char*)&commandScriptData_80079B6C + 0x20), (void*)((char*)&commandScriptData_80079B6C + 0x44),
    0, 0, 0, 0, 0, 0, 0, 0,
    anim_800B3768,
};
MapActorModel model_800B381C = { (const char*)str_800B22D8, 4, bones_800B35E0, 0, 0, 0, 4, script_800B3798, 0, 0x800000, 0, 0 };
MapVoice voices_800B3848[11] = {
    { 0, 0, { 5, 0x1ED, 0x2C } },
    { 1, 0, { 9, 0x15C, 0x15 } },
    { 1, 1, { 0x19, 0x15D, 0x17 } },
    { 2, 0, { 0x15, 0x15E, 0x1C } },
    { 2, 1, { 8, 0x15F, 0x10 } },
    { 2, 2, { 0xB, 0x15F, 0x1A } },
    { 3, 0, { 0, 0x160, 0x19 } },
    { 3, 1, { 5, 0x160, 0x1E } },
    { 4, 0, { 0xF, 0x160, 0x17 } },
    { 4, 1, { 0x14, 0x161, 0x12 } },
    { 0, 0, { -1, 0, 0 } },
};
MapWarp warp_800B38A0 = { { 0x51A, 0, 0xD09 }, 0, 0, 0, { 5, 3, 6 } };
MapFx effects_800B38B8[6] = {
    { 1, 0x98, { -0x258, 0, -0x2EE }, { 0, 0, 0 }, 0, 0xF0, 0, 0, 0, 0, -1, 0, 0, 0 },
    { 1, 0x99, { -0x258, 0, -0x2EE }, { 0, 0, 0 }, 0, 0xA1, 0x4F, 0, 0, 0, -1, 0, 0, 0 },
    { 1, 0x9A, { -0x258, 0, -0x2EE }, { 0, 0, 0 }, 0, 0x1F, 0x95, 0, 0, 0, -1, 0, 0, 0 },
    { 1, 0x9B, { -0x258, 0, -0x2EE }, { 0, 0, 0 }, 0, 0x1F, 0xB3, 0, 0, 0, -1, 0, 0, 0 },
    { 1, 0x9C, { -0x258, 0, -0x2EE }, { 0, 0, 0 }, 0, 0x1F, 0xD1, 0, 0, 0, -1, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
int data_800B39C0[18] = {
    1, 1, 0, 1, 0, 0, 2, 5,
    5, 0x2C, 0x48000000, 8, 0xD3, 0, 0, 0xD3,
    0, 0,
};
MapInstr script_800B3A08[107] = {
    { 0x1F, 1, 0x34, 0 },
    { 0xA, 0, 0x20, 0 },
    { 0xA, 0, 0x10, 0 },
    { 9, 0, 0x10, 0 },
    { 0x1A, 2, 0, 0 },
    { 0x1A, 4, 0, 0 },
    { 0x64, 0, 1, 0 },
    { 5, 0, 0, 0 },
    { 7, 0, 7, 0 },
    { 0x20, 0, 0x34, 0 },
    { 0x19, 0, 1, -1 },
    { 0x19, 1, 0, 0x14 },
    { 0x19, 2, 0, 0x2A },
    { 0xD, 0, 3, 0 },
    { 0x46, 1, 0, MAP_REF(data_800B3580) },
    { 0xD, 0, 2, 0 },
    { 0x38, 1, 0, 0 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x150014, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x68, 1, 0x24, 0 },
    { 0x67, 0xC, 6, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B38B8) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B274C) },
    { 0x49, 1, 0x160014, 1 },
    { 0xC, 0, 0x1E, 0 },
    { 0x49, 0, 0x1850186, 1 },
    { 0xC, 0, 0xB3, 0 },
    { 0x67, 0xD, 0x4E, 0 },
    { 0x67, 5, 0x1F, 0 },
    { 0x67, 6, 0, 0 },
    { 0x67, 0xC, 0xFF03, 6 },
    { 0x68, 0, 0, 0 },
    { 0x1A, 2, 0, 0 },
    { 0x1A, 4, 1, 0 },
    { 0x67, 4, 0x1F, 0 },
    { 0x67, 6, 0, 0 },
    { 0x49, 0, 0x18A0137, 1 },
    { 0x38, 2, 0, 1 },
    { 0x42, 0, 0, 0 },
    { 0x49, 2, 0x2D002A, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 2, 0x2E002A, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x30, 0 },
    { 9, 0, 0x20, 0 },
    { 0x1A, 2, 0, 0 },
    { 0x1A, 4, 1, 0 },
    { 0x64, 0, 1, 0 },
    { 5, 0, 0, 0 },
    { 7, 0, 7, 0 },
    { 0x19, 0, 1, -1 },
    { 0x19, 2, 0, 0x2B },
    { 0xD, 0, 5, 0 },
    { 0x38, 2, 0, 4 },
    { 0x42, 0, 0, 0 },
    { 0x49, 2, 0x2F002B, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 2, 0x32002B, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x30, 0 },
    { 9, 0, 0x30, 0 },
    { 0x45, 0, 1, 0 },
    { 0x65, 0, 0, MAP_REF(data_800B39C0) },
    { 0x66, 0, 0, 0 },
    { 0xA, 0, 0x40, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0x40, 0 },
    { 0x1A, 4, 1, 0 },
    { 0x48, 2, 0x2C, 5 },
    { 0x38, 2, 0, 3 },
    { 0x42, 0, 0, 0 },
    { 0x49, 2, 0x30002C, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 2, 0x31002C, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x46, 2, 0, MAP_REF(anim_800B3768) },
    { 0xD, 0, 4, 0 },
    { 0x51, 5, 0x3000C, 0xFA },
    { 0xA, 0, 0xFF, 0 },
    { 9, 0, 0x50, 0 },
    { 0x1A, 4, 1, 0 },
    { 0x48, 2, 0x2B, 5 },
    { 0x48, 0, 0xD7, 5 },
    { 0x67, 2, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x38, 2, 0, 2 },
    { 0x42, 0, 0, 0 },
    { 0x49, 2, 0x2F002B, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 2, 0x32002B, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 2, 0x33002B, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x67, 3, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0xA, 0, 0xFF, 0 },
    { 9, 0, 0xFF, 0 },
    { 8, 0, 7, 0 },
    { 4, 0, 0, 0 },
    { 0x66, 0, 0, 0 },
    { 0xA, 0, 0xFFF, 0 },
    { 0xA, 0, 0xFFE, 0 },
    { 9, 0, 0xFFE, 0 },
    { 0x4D, 0, 0, MAP_REF(WarpLostBattle_800B2C18) },
    { 9, 0, 0xFFF, 0 },
    { 3, 0, 0, 0 },
};
MapMinion minion_800B40B8 = { &model_800B35B4, 0, { -0x258, 0, -0x2EE }, -0x9DD, -1, 0x14, 3, 2 };
MapMinion minion_800B40DC = { &model_800B381C, 0, { -0x258, 0, -0x2EE }, -0x9DD, -1, 0x2A, 0, 2 };
MapEvent events_800B4100[6] = {
    { -1, 1, &warp_800B38A0, 0, { Warp_800B22F0 } },
    { -1, 0xF, &minion_800B40B8, 0x14, { MinionInit_800B2414 } },
    { -1, 0xF, &minion_800B40DC, 0x14, { MinionInit_800B2414 } },
    { -1, 8, script_800B3A08, 0, { 0 } },
    { -1, 0xB, voices_800B3848, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
short bones_800B4178[92] = {
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
int scale_800B4230[3] = {
    0x1000, 0x1000, 0x1000,
};
const int unknown_800B22C0[1] = {
    0x124,
};
const char str_800B22C4[20] = "\x82j\x82\x81\x82\x8b\x82\x81\x82\x99\x82\x81\x82\x8d\x82\x95";
const int str_800B22D8[6] = {
    -0x7E7D9B7E, -0x6B7D6D7E, 0x40818882, -0x707D9E7E, -0x6C7D6C7E, -0x73BE0000,
};
