#include "maps/map.h"

void MinionInit_800B2304(MapEnt* ent);
int AddEffects_800B263C(MapFx* fx);
void FxModel_800B27C8(MapEnt* ent);
void MapInit_800B29F0(int phase);
void MinionIdle_800B2A60(MapEnt* ent);
int EndEffects_800B2A68(void);
void FxInit_800B2AE8(MapEnt* ent);
void FxMdec_800B2BA0(MapEnt* ent);
int PlayMovie_800B2C8C(MapMovieArgs* args);
int Equip_800B2D04(void);
void StartMapTask_800B2D28(void);
void MapTaskLoad_800B2D58(EventEntry* entry, int* st);
void MapTask_800B2DF0(EventEntry* entry, int* st);
int LeaveArea_800B2EA8(MapEvent* ev, int area);
int EnterArea_800B2FC4(MapEvent* ev, int area, int prev);
void RequestModels_800B30CC(MapEvent* ev);
void EntityTask_800B319C(EventEntry* entry, MapEnt* ent);
int AddEntity_800B321C(void* ev);
int MinionF_800B3348(void);
int MinionF_800B3350(void);
int FxFrame_800B3358(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B33DC(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B34A8(MapFx* fx, MapFxWork* w);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[16];
extern const char str_800B22D4[16];
extern const char str_800B22E4[12];
extern const MapFxInits fxInits_800B22F0;
extern ActorScriptCmd* script_800B35F0;
extern MapActorModel model_800B35F4;
extern short bones_800B3620[80];
extern int data_800B36C0[2];
extern ActorScriptCmd* script_800B36C8;
extern MapActorModel model_800B36CC;
extern ActorScriptCmd* script_800B36F8;
extern MapActorModel model_800B36FC;
extern MapFx effects_800B3728[3];
extern MapFx effects_800B37AC[3];
extern MapFx effects_800B3830[3];
extern MapFx effects_800B38B4[3];
extern MapVoice voices_800B3938[45];
extern MapInstr script_800B3AA0[200];
extern MapMinion minion_800B4720;
extern MapMinion minion_800B4744;
extern MapMinion minion_800B4768;
extern MapEvent events_800B478C[6];
extern short bones_800B4804[92];
extern int scale_800B48BC[3];

ActorScriptCmd* script_800B35F0 = 0;
MapActorModel model_800B35F4 = { str_800B22C4, 0x66, 0, 0, 0, 0, 4, &script_800B35F0, 0, 0x800000, 0, 0 };
short bones_800B3620[80] = {
    0, 0, 0, 0x46, 1, 1, 1, 0,
    2, 0x102, 2, 0xB, 3, 0x203, 3, 0xB,
    4, 0x304, 4, 0xB, 5, 0x405, 5, 0xB,
    3, 0x206, 6, 0xB, 4, 0x607, 7, 0xB,
    5, 0x708, 8, 0xB, 3, 0x209, 9, 0,
    4, 0x90A, 0xA, 0xB, 2, 0x10B, 0xB, 0xB,
    3, 0xB0C, 0xC, 0xB, 4, 0xC0D, 0xD, 0xB,
    5, 0xD0E, 0xE, 0xB, 3, 0xB0F, 0xF, 0xB,
    4, 0x1010, 0x10, 0xB, 5, 0x1111, 0x11, 0xB,
    3, 0x212, 0x12, 0xB, -1, -1, -1, -1,
};
int data_800B36C0[2] = {
    5, -1,
};
ActorScriptCmd* script_800B36C8 = 0;
MapActorModel model_800B36CC = { str_800B22D4, 0x64, bones_800B3620, 0, 0, data_800B36C0, 4, &script_800B36C8, 0, 0x800000, 0, 1 };
ActorScriptCmd* script_800B36F8 = 0;
MapActorModel model_800B36FC = { str_800B22E4, 0x16, 0, 0, 0, 0, 4, &script_800B36F8, 0, 0x800000, 0, 1 };
MapFx effects_800B3728[3] = {
    { 1, 0x66, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x78, 0, -1, 0, 0, 0, 0, 0, 0 },
    { 3, 0x17, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x78, 0, -1, 0, 0, 0x3B, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B37AC[3] = {
    { 1, 0x66, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x78, 0, -1, 1, 1, 1, 0, 0, 0 },
    { 3, 0x17, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x78, 0, -1, 0, 0, 0x3B, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B3830[3] = {
    { 1, 0x66, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x78, 0, -1, 2, 2, 2, 0, 0, 0 },
    { 3, 0x17, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x78, 0, -1, 0, 0, 0x3B, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B38B4[3] = {
    { 1, 0x66, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x78, 0, -1, 3, 3, 3, 0, 0, 0 },
    { 3, 0x17, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x78, 0, -1, 0, 0, 0x3B, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapVoice voices_800B3938[45] = {
    { 0, 0, { 0x11, 0x170, 0x2B } },
    { 0, 1, { 9, 0x171, 0x1C } },
    { 1, 0, { 0x13, 0x1FF, 0x22 } },
    { 1, 1, { 0x1E, 0x200, 0x20 } },
    { 2, 0, { 0, 0, 0x2D } },
    { 2, 1, { 1, 0, 0x1A } },
    { 3, 0, { 0x10, 0x172, 0x2C } },
    { 3, 1, { 0x14, 0x173, 0xC } },
    { 4, 0, { 2, 0, 0x2D } },
    { 4, 1, { 3, 0, 0x26 } },
    { 4, 2, { 4, 0, 0x2B } },
    { 4, 3, { 5, 0, 0x1C } },
    { 5, 0, { 0x19, 0x201, 0x1B } },
    { 5, 1, { 0x1F, 0x201, 0x19 } },
    { 5, 2, { 1, 0x203, 0x19 } },
    { 5, 3, { 0x15, 0x203, 0x24 } },
    { 5, 4, { 0, 0x204, 0x1D } },
    { 6, 0, { 6, 0, 0x2C } },
    { 7, 0, { 0xB, 0x204, 0x29 } },
    { 8, 0, { 7, 0, 0x1A } },
    { 9, 0, { 0xF, 0x204, 0x23 } },
    { 0xA, 0, { 0x19, 0x174, 0xA } },
    { 0xA, 1, { 7, 0x175, 0x19 } },
    { 0xB, 0, { 8, 0, 0x1A } },
    { 0xB, 1, { 9, 0, 0x17 } },
    { 0xC, 0, { 6, 0x207, 0x19 } },
    { 0xC, 1, { 0xA, 0x207, 0x20 } },
    { 0xC, 2, { 0x1B, 0x207, 0x21 } },
    { 0xC, 3, { 8, 0x20A, 0x20 } },
    { 0xD, 0, { 0xA, 0, 0x1D } },
    { 0xD, 1, { 0xB, 0, 0x1D } },
    { 0xE, 0, { 3, 0x20B, 0x1C } },
    { 0xE, 1, { 0xE, 0x20C, 0x18 } },
    { 0xE, 2, { 0xC, 0x20D, 0x19 } },
    { 0xF, 0, { 3, 0x176, 0x17 } },
    { 0xF, 1, { 0xF, 0x177, 0x1E } },
    { 0xF, 2, { 0, 0x179, 0x30 } },
    { 0xF, 3, { 0xB, 0x179, 0x1A } },
    { 0x10, 0, { 0xC, 0, 0x1E } },
    { 0x10, 1, { 0xD, 0, 0xE } },
    { 0x10, 2, { 0xE, 0, 0x21 } },
    { 0x11, 0, { 0x15, 0x17A, 0x12 } },
    { 0x11, 1, { 0x17, 0x17A, 0x2B } },
    { 0x11, 2, { 1, 0x17B, 0x14 } },
    { 0, 0, { -1, 0, 0 } },
};
MapInstr script_800B3AA0[200] = {
    { 9, 0, 0, 0 },
    { 0x4C, 0xB, 0, 0 },
    { 0x4D, 0, 0, MAP_REF(PlayMovie_800B2C8C) },
    { 5, 0, 0, 0 },
    { 7, 0, 0xF, 0 },
    { 0x5E, 0, 1, 0 },
    { 0x1A, 1, 0, 0 },
    { 0x55, 0, 1, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B3728) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B263C) },
    { 0x67, 2, 0x1E, 0 },
    { 0xC, 0, 0x1E, 0 },
    { 0x38, 1, 0, 0 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x1000C, 1 },
    { 0x42, 0, 1, 0 },
    { 0x3F, 0, 0, 0 },
    { 0x38, 2, 0, 1 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0xD000E, 1 },
    { 0x49, 2, 0x1000B, 1 },
    { 0x49, 3, 0xC000D, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0xF000C, 1 },
    { 0x49, 2, 0xC000D, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x56, 0, 1, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B2A68) },
    { 0x55, 0, 2, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B37AC) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B263C) },
    { 0x38, 3, 0, 2 },
    { 0x42, 0, 0, 0 },
    { 0x49, 3, 0x3000D, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 3, 0x4000D, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x38, 1, 0, 3 },
    { 0x42, 0, 0, 0 },
    { 0x48, 1, 0xC, 1 },
    { 0x49, 3, 0xE000B, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x20010, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x49, 1, 0x3000C, 1 },
    { 0x38, 3, 0, 4 },
    { 0x42, 0, 0, 0 },
    { 0x49, 3, 0x5000B, 1 },
    { 0x42, 0, 1, 0 },
    { 0x42, 0, 2, 0 },
    { 0x49, 3, 0x6000B, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 3, 0x7000B, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x56, 0, 2, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B2A68) },
    { 0x55, 0, 1, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B3830) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B263C) },
    { 0x38, 2, 0, 5 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0xD000E, 1 },
    { 0x49, 2, 0x2000D, 1 },
    { 0x49, 3, 0xC000D, 1 },
    { 0x42, 0, 1, 0 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0xF000C, 1 },
    { 0x49, 2, 0x3000D, 1 },
    { 0x42, 0, 3, 0 },
    { 0x42, 0, 4, 0 },
    { 0x49, 2, 0x4000D, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x56, 0, 1, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B2A68) },
    { 0x55, 0, 3, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B37AC) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B263C) },
    { 0x38, 3, 0, 6 },
    { 0x42, 0, 0, 0 },
    { 0x49, 3, 0x3000D, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x38, 2, 0, 7 },
    { 0x42, 0, 0, 0 },
    { 0x48, 2, 0xD, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x38, 3, 0, 8 },
    { 0x42, 0, 0, 0 },
    { 0x49, 3, 0x4000D, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x38, 2, 0, 9 },
    { 0x42, 0, 0, 0 },
    { 0x49, 2, 0x5000D, 1 },
    { 0x68, 1, 0x10, 0 },
    { 0x3F, 0, 0, 0 },
    { 0x56, 0, 3, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B2A68) },
    { 0x55, 0, 2, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B38B4) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B263C) },
    { 0x38, 1, 0, 0xA },
    { 0x42, 0, 0, 0 },
    { 0x48, 1, 4, 1 },
    { 0x49, 1, 0x5000C, 1 },
    { 0x49, 2, 0xE000B, 1 },
    { 0x49, 3, 0xE000B, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 2, 0xC000D, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x38, 3, 0, 0xB },
    { 0x42, 0, 0, 0 },
    { 0x49, 3, 0x6000B, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 3, 0x8000B, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x56, 0, 2, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B2A68) },
    { 0x55, 0, 1, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B3830) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B263C) },
    { 0x38, 2, 0, 0xC },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0xD000E, 1 },
    { 0x49, 2, 0x6000D, 1 },
    { 0x49, 3, 0xC000D, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 2, 0x7000D, 1 },
    { 0x42, 0, 2, 0 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0xF000C, 1 },
    { 0x49, 2, 0x8000D, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x56, 0, 1, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B2A68) },
    { 0x55, 0, 3, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B37AC) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B263C) },
    { 0x38, 3, 0, 0xD },
    { 0x42, 0, 0, 0 },
    { 0x49, 3, 0x9000D, 1 },
    { 0x42, 0, 1, 0 },
    { 0x3F, 0, 0, 0 },
    { 0x38, 2, 0, 0xE },
    { 0x42, 0, 0, 0 },
    { 0x49, 2, 0x9000D, 1 },
    { 0x42, 0, 1, 0 },
    { 0x42, 0, 2, 0 },
    { 0x49, 2, 0xA000D, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x56, 0, 3, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B2A68) },
    { 0x55, 0, 1, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B38B4) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B263C) },
    { 0x38, 1, 0, 0xF },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x6000C, 1 },
    { 0x48, 2, 0xE, 1 },
    { 0x49, 3, 0xE000B, 1 },
    { 0x42, 0, 1, 0 },
    { 0x48, 2, 0xB, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x7000C, 1 },
    { 0x42, 0, 3, 0 },
    { 0x48, 1, 8, 1 },
    { 0x49, 1, 0x9000C, 1 },
    { 0x49, 2, 0xC000D, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x56, 0, 1, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B2A68) },
    { 0x55, 0, 0, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B37AC) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B263C) },
    { 0x38, 3, 0, 0x10 },
    { 0x42, 0, 0, 0 },
    { 0x49, 3, 0xA000B, 1 },
    { 0x42, 0, 1, 0 },
    { 0x3F, 0, 0, 0 },
    { 0x56, 0, 0, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B2A68) },
    { 0x4B, 0, 0, MAP_REF(effects_800B3728) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B263C) },
    { 0x38, 1, 0, 0x11 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0xA000C, 1 },
    { 0x49, 2, 0xE000B, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0xB000B, 1 },
    { 0x42, 0, 2, 0 },
    { 0x3F, 0, 0, 0 },
    { 0x67, 0xC, 0xFF00, 0 },
    { 0x67, 3, 0x1E, 0 },
    { 0xC, 0, 0x1E, 0 },
    { 0x4D, 0, 0, MAP_REF(EndEffects_800B2A68) },
    { 9, 0, 0xFF, 0 },
    { 0x1A, 1, 1, 0 },
    { 8, 0, 0xF, 0 },
    { 4, 0, 0, 0 },
    { 0x4D, 0, 0, MAP_REF(Equip_800B2D04) },
    { 0x53, 0, 0x31, 0 },
    { 3, 0, 0, 0 },
};
MapMinion minion_800B4720 = { &model_800B35F4, 0, { 0, -0x38, 0x2CC }, -0x800, -1, 0xC, 0, 2 };
MapMinion minion_800B4744 = { &model_800B36CC, 0, { -0xD7, 0, 0x1AC }, -0xD55, -1, 0xB, 0, 2 };
MapMinion minion_800B4768 = { &model_800B36FC, 0, { 0, 0, 0x8E }, 0, 0, 0xB, 1, 2 };
MapEvent events_800B478C[6] = {
    { -1, 0xF, &minion_800B4720, 0x14, { MinionInit_800B2304 } },
    { -1, 0xF, &minion_800B4744, 0x14, { MinionInit_800B2304 } },
    { -1, 0xF, &minion_800B4768, 0x14, { MinionInit_800B2304 } },
    { -1, 8, script_800B3AA0, 0, { 0 } },
    { -1, 0xB, voices_800B3938, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
short bones_800B4804[92] = {
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
int scale_800B48BC[3] = {
    0x1000, 0x1000, 0x1000,
};
const char unknown_800B22C0[4] = "_";
const char str_800B22C4[16] = "\x82""f\x82\x92\x82\x8f\x82\x94\x82\x94\x82\x81";
const char str_800B22D4[16] = "\x82i\x82\x89\x82\x82\x82\x81\x82\x92\x82\x81";
const char str_800B22E4[12] = "\x82""f\x82\x81\x82\x92\x82\x81\x82\x89";
const MapFxInits fxInits_800B22F0 = { { 0, FxModel_800B27C8, 0, FxMdec_800B2BA0, 0 } };
