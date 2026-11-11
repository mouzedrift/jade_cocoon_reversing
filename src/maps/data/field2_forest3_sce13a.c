#include "maps/map.h"

void Warp_800B22E8(MapEnt* ent);
void MinionInit_800B240C(MapEnt* ent);
int AddEffects_800B2744(MapFx* fx);
void FxModel_800B28D0(MapEnt* ent);
void MapInit_800B2AF8(int phase);
void MinionIdle_800B2B64(MapEnt* ent);
void FxInit_800B2B6C(MapEnt* ent);
int WarpLostBattle_800B2C10(void);
void StartMapTask_800B2C30(void);
void MapTaskLoad_800B2C60(EventEntry* entry, int* st);
void MapTask_800B2CF8(EventEntry* entry, int* st);
int LeaveArea_800B2DB0(MapEvent* ev, int area);
int EnterArea_800B2ECC(MapEvent* ev, int area, int prev);
void RequestModels_800B2FD4(MapEvent* ev);
void EntityTask_800B30A4(EventEntry* entry, MapEnt* ent);
int AddEntity_800B3124(void* ev);
int MinionF_800B3250(void);
int MinionF_800B3258(void);
int FxFrame_800B3260(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B32E4(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B33B0(MapFx* fx, MapFxWork* w);

extern const int unknown_800B22C0[1];
extern const char str_800B22C4[12];
extern const int str_800B22D0[6];
extern short bones_800B34F8[64];
extern int data_800B3578[12];
extern ActorScriptCmd* script_800B35A8;
extern MapActorModel model_800B35AC;
extern short bones_800B35D8[96];
extern ActorScriptCmd anim_800B3698[4];
extern int anim_800B36C8[19];
extern int anim_800B3714[19];
extern ActorScriptCmd anim_800B3760[4];
extern ActorScriptCmd* script_800B3790[33];
extern MapActorModel model_800B3814;
extern MapVoice voices_800B3840[11];
extern MapWarp warp_800B3898;
extern MapFx effects_800B38B0[6];
extern int data_800B39B8[4];
extern int data_800B39C8[4];
extern int data_800B39D8[18];
extern MapInstr script_800B3A20[109];
extern MapMinion minion_800B40F0;
extern MapMinion minion_800B4114;
extern MapEvent events_800B4138[6];
extern short bones_800B41B0[92];
extern int scale_800B4268[3];

short bones_800B34F8[64] = {
    0, 0, 0, 0x46, 1, 1, 1, 0,
    2, 0x102, 2, 0xB, 3, 0x203, 3, 0xB,
    4, 0x304, 4, 0xB, 5, 0x405, 5, 0xB,
    3, 0x206, 6, 0xB, 4, 0x307, 7, 0xB,
    5, 0x408, 8, 0xB, 3, 0x209, 9, 0xB,
    4, 0x30A, 0xA, 0xB, 5, 0x40B, 0xB, 0xB,
    3, 0x20C, 0xC, 0xB, 4, 0x30D, 0xD, 0xB,
    5, 0x40E, 0xE, 0xB, -1, -1, -1, -1,
};
int data_800B3578[12] = {
    -0x1FEF1, -0xFDF5, 0x10000, -0xFDFA, 0x1000000, -0x1FDE9, 0x5A0000, -0x1FDEC,
    0x40000000, -0xFEF8, -0x1FEF0, -0x1FF00,
};
ActorScriptCmd* script_800B35A8 = 0;
MapActorModel model_800B35AC = { str_800B22C4, 0x5E, bones_800B34F8, 0, 0, 0, 4, &script_800B35A8, 0, 0x800000, 0, 0 };
short bones_800B35D8[96] = {
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
ActorScriptCmd anim_800B3698[4] = {
    { 0xC, 2, -2, 0, 0x15, 0x10D, -2 },
    { 0xF, 1, -2, 0x103, -1, 0x201, -1 },
    { 0, 0, 0x15, 0x115, -2, 0x217, -2 },
    { 0, 0, 0x3C, 0x110, -2, 0x100, -2 },
};
int anim_800B36C8[19] = {
    -0x1FDF4, 0x1A0000, -0x1FEF3, -0x1FEF1, -0xFDF9, 0x1000000, -0xFEFD, -0xFDFF,
    0x1A0000, -0x1FDEC, 0x40000000, -0xFEF8, -0xFDF5, 0, -0x1FEF0, -0x1FEEF,
    -0xFDF2, 0x1A0000, -0x1FF00,
};
int anim_800B3714[19] = {
    -0x1FDF4, 0x1B0000, -0x1FEF3, -0x1FEF1, -0xFDF5, 0x10000, -0xFDFA, 0x1000000,
    -0xFDFF, 0x1B0000, -0x1FDEC, 0x40000000, -0xFEF8, -0x1FEF0, -0xFDFF, 0x40000,
    -0xFDF2, 0x1B0000, -0x1FF00,
};
ActorScriptCmd anim_800B3760[4] = {
    { 0xF, 1, -2, 0x207, -1, 0, 0x100 },
    { 0x17, 2, -2, 0, 0x5A, 0x214, -2 },
    { 0, 0, 0x4000, 0x108, -1, 0x20B, -1 },
    { 0, 0, 0, 0x110, -2, 0x100, -2 },
};
ActorScriptCmd* script_800B3790[33] = {
    (void*)&commandScriptData_80079754, (void*)((char*)&commandScriptData_80079754 + 0xC), (void*)((char*)&commandScriptData_80079754 + 0x1C), (void*)((char*)&commandScriptData_80079754 + 0x54), (void*)((char*)&commandScriptData_80079754 + 0x8C), (void*)((char*)&commandScriptData_80079754 + 0xC4), (void*)((char*)&commandScriptData_80079754 + 0xFC), (void*)((char*)&commandScriptData_80079754 + 0x134),
    (void*)((char*)&commandScriptData_80079754 + 0x16C), (void*)((char*)&commandScriptData_80079754 + 0x1A4), (void*)((char*)&commandScriptData_80079754 + 0x200), (void*)((char*)&commandScriptData_80079754 + 0x238), (void*)((char*)&commandScriptData_80079754 + 0x270), (void*)((char*)&commandScriptData_80079754 + 0x2A8), (void*)((char*)&commandScriptData_80079A2C + 0x4), (void*)((char*)&commandScriptData_80079A2C + 0x1C),
    anim_800B3698, (ActorScriptCmd*)anim_800B36C8, (ActorScriptCmd*)anim_800B3714, (void*)((char*)&commandScriptData_80079B44 + 0x8), (void*)((char*)&commandScriptData_80079B44 + 0x1C), (void*)((char*)&commandScriptData_80079B6C + 0x8), (void*)((char*)&commandScriptData_80079B6C + 0x20), (void*)((char*)&commandScriptData_80079B6C + 0x44),
    0, 0, 0, 0, 0, 0, 0, 0,
    anim_800B3760,
};
MapActorModel model_800B3814 = { (const char*)str_800B22D0, 4, bones_800B35D8, 0, 0, 0, 4, script_800B3790, 0, 0x800000, 0, 0 };
MapVoice voices_800B3840[11] = {
    { 0, 0, { 0, 0x48E, 0x36 } },
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
MapWarp warp_800B3898 = { { -0x66B, 0, 0x86 }, -0x293, 0, 0, { 5, 3, 8 } };
MapFx effects_800B38B0[6] = {
    { 1, 0x98, { -0x1F4, -0xC, 0x2D5 }, { 0, 0, 0 }, 0, 0xF0, 0, 0, 0, 0, -1, 0, 0, 0 },
    { 1, 0x99, { -0x1F4, -0xC, 0x2D5 }, { 0, 0, 0 }, 0, 0xA1, 0x4F, 0, 0, 0, -1, 0, 0, 0 },
    { 1, 0x9A, { -0x1F4, -0xC, 0x2D5 }, { 0, 0, 0 }, 0, 0x1F, 0x95, 0, 0, 0, -1, 0, 0, 0 },
    { 1, 0x9B, { -0x1F4, -0xC, 0x2D5 }, { 0, 0, 0 }, 0, 0x1F, 0xB3, 0, 0, 0, -1, 0, 0, 0 },
    { 1, 0x9C, { -0x1F4, -0xC, 0x2D5 }, { 0, 0, 0 }, 0, 0x1F, 0xD1, 0, 0, 0, -1, 0, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
int data_800B39B8[4] = {
    -0x19C, 0, 0x19C, -0xE3,
};
int data_800B39C8[4] = {
    -0x1C2, -0xC, 0x352, -0x800,
};
int data_800B39D8[18] = {
    1, 1, 0, 1, 0, 0, 2, 5,
    5, 0x2C, 0x48000000, 9, 0xD3, 0, 0, 0xD3,
    0, 0,
};
MapInstr script_800B3A20[109] = {
    { 0x1F, 1, 0x35, 0 },
    { 0xA, 0, 0x20, 0 },
    { 0xA, 0, 0x10, 0 },
    { 9, 0, 0x10, 0 },
    { 0x1A, 2, 0, 0 },
    { 0x1A, 4, 0, 0 },
    { 0x64, 0, 1, 0 },
    { 5, 0, 0, 0 },
    { 7, 0, 7, 0 },
    { 0x20, 0, 0x35, 0 },
    { 0x61, 0, 1, 0 },
    { 0x13, 0, 0, MAP_REF(data_800B39B8) },
    { 0x46, 1, 0, MAP_REF(data_800B3578) },
    { 0xD, 0, 2, 0 },
    { 0x38, 1, 0, 0 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x1A0019, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x68, 1, 0x25, 0 },
    { 0x67, 0xC, 6, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B38B0) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B2744) },
    { 0x49, 1, 0x1B0019, 1 },
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
    { 0xD, 0, 1, 0 },
    { 0x38, 2, 0, 1 },
    { 0x42, 0, 0, 0 },
    { 0x49, 2, 0x230020, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 2, 0x240020, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x30, 0 },
    { 9, 0, 0x20, 0 },
    { 0x1A, 2, 0, 0 },
    { 0x1A, 4, 1, 0 },
    { 0x64, 0, 1, 0 },
    { 5, 0, 0, 0 },
    { 7, 0, 7, 0 },
    { 0x61, 0, 1, 0 },
    { 0x13, 0, 0, MAP_REF(data_800B39B8) },
    { 0x19, 2, 0, 0x21 },
    { 0x38, 2, 0, 4 },
    { 0x42, 0, 0, 0 },
    { 0x49, 2, 0x250021, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 2, 0x280021, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x30, 0 },
    { 9, 0, 0x30, 0 },
    { 0x45, 0, 1, 0 },
    { 0x65, 0, 0, MAP_REF(data_800B39D8) },
    { 0x66, 0, 0, 0 },
    { 0xA, 0, 0x40, 0 },
    { 0xA, 0, 0x50, 0 },
    { 9, 0, 0x40, 0 },
    { 0x13, 2, 0, MAP_REF(data_800B39C8) },
    { 0x1A, 4, 1, 0 },
    { 0x48, 2, 0x22, 5 },
    { 0x38, 2, 0, 3 },
    { 0x42, 0, 0, 0 },
    { 0x49, 2, 0x260022, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 2, 0x270022, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x46, 2, 0, MAP_REF(anim_800B3760) },
    { 0xD, 0, 4, 0 },
    { 0x51, 5, 0x3000D, 0xFC },
    { 0x61, 0, 0, 0 },
    { 0xA, 0, 0xFF, 0 },
    { 9, 0, 0x50, 0 },
    { 0x13, 2, 0, MAP_REF(data_800B39C8) },
    { 0x1A, 4, 1, 0 },
    { 0x48, 2, 0x21, 5 },
    { 0x48, 0, 0xD7, 5 },
    { 0x67, 2, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x38, 2, 0, 2 },
    { 0x42, 0, 0, 0 },
    { 0x49, 2, 0x250021, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 2, 0x280021, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 2, 0x290021, 1 },
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
    { 0x4D, 0, 0, MAP_REF(WarpLostBattle_800B2C10) },
    { 9, 0, 0xFFF, 0 },
    { 3, 0, 0, 0 },
};
MapMinion minion_800B40F0 = { &model_800B35AC, 0, { -0x1F4, -0xC, 0x2D5 }, -0x800, -1, 0x19, 4, 2 };
MapMinion minion_800B4114 = { &model_800B3814, 0, { -0x1C2, -0xC, 0x352 }, -0x800, -1, 0x20, 2, 2 };
MapEvent events_800B4138[6] = {
    { -1, 1, &warp_800B3898, 0, { Warp_800B22E8 } },
    { -1, 0xF, &minion_800B40F0, 0x14, { MinionInit_800B240C } },
    { -1, 0xF, &minion_800B4114, 0x14, { MinionInit_800B240C } },
    { -1, 8, script_800B3A20, 0, { 0 } },
    { -1, 0xB, voices_800B3840, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
short bones_800B41B0[92] = {
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
int scale_800B4268[3] = {
    0x1000, 0x1000, 0x1000,
};
const int unknown_800B22C0[1] = {
    0x126,
};
const char str_800B22C4[12] = "\x82x\x82\x81\x82\x8d\x82\x95";
const int str_800B22D0[6] = {
    -0x7E7D9B7E, -0x6B7D6D7E, 0x40818882, -0x707D9E7E, -0x6C7D6C7E, -0x777E0000,
};
