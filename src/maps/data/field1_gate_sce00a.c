#include "maps/map.h"

void Warp_800B2374(MapEnt* ent);
void GateSpot_800B2498(MapEnt* ent);
int AddEffects_800B26E8(MapFx* fx);
void FxModel_800B2874(MapEnt* ent);
void MinionInit_800B2A9C(MapEnt* ent);
void SavePoint_800B2DD4(MapEnt* ent);
void MapInit_800B3244(int phase);
void ScriptSpot_800B3450(MapEnt* ent);
void FxInit_800B34C4(MapEnt* ent);
void FxMdec_800B357C(MapEnt* ent);
void GateSpotInit_800B3668(MapEnt* ent);
void GateReturnInit_800B36B0(MapEnt* ent);
void GateReturn_800B372C(MapEnt* ent);
void MinionIdle_800B379C(MapEnt* ent);
int ChainWon_800B37A4(void);
int StartChain_800B37BC(int* chain);
int SetLevantAnimSet_800B37F0(void);
void SavePointInit_800B3804(MapEnt* ent);
void StartMapTask_800B3844(void);
void MapTaskLoad_800B3874(EventEntry* entry, int* st);
void MapTask_800B390C(EventEntry* entry, int* st);
int LeaveArea_800B39C4(MapEvent* ev, int area);
int EnterArea_800B3AE0(MapEvent* ev, int area, int prev);
void RequestModels_800B3BE8(MapEvent* ev);
void EntityTask_800B3CB8(EventEntry* entry, MapEnt* ent);
int AddEntity_800B3D38(void* ev);
void MapInit_800B3E64(int phase);
int StopLevantIfSet_800B3ED0(MapScriptSpot* spot);
int FxFrame_800B3F00(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B3F84(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B4050(MapFx* fx, MapFxWork* w);
int MinionF_800B4198(void);
int MinionF_800B41A0(void);
MapChainEntry* ChainEntry_800B41A8(GameBattleChain* chain);
int ChainEnds_800B41D0(GameBattleChain* chain);
MsgWindowEntry* ChainMessage_800B4200(GameBattleChain* chain);
void ChainCommand_800B42A8(BattleCmd* cmd, GameBattleChain* chain);
int ChainNext_800B4318(BattleCmd* cmd, GameBattleChain* chain);
void ChainResult_800B4390(UnitStatus* actor, UnitStatus* target, BattleCmd* cmd, ActionResult* res, GameBattleChain* chain);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[12];
extern const char str_800B22D0[16];
extern const char data_800B22E0[8];
extern const char str_800B22E8[28];
extern const MapFxInits fxInits_800B2304;
extern const MapRgb savePointDim_800B2318;
extern const MapRgb savePointLit_800B231C;
extern int data_800B4474[2];
extern ActorScriptCmd* script_800B447C;
extern MapActorModel model_800B4480;
extern MapActorModel model_800B44AC;
extern MapActorModel model_800B44D8;
extern MapVoice voices_800B4504[81];
extern int data_800B478C[9];
extern int species_800B47B0[9];
extern MapMinion minion_800B47D4;
extern MapMinion minion_800B47F8;
extern MapInstr script_800B481C[253];
extern MapSavePoint savePoint_800B57EC;
extern int data_800B57FC[2];
extern MapWarp warp_800B5804;
extern MapWarp warp_800B581C;
extern MapWarp warp_800B5834;
extern MapWarp warp_800B584C;
extern MapFx effects_800B5864[3];
extern MapFx effects_800B58E8[3];
extern MapFx effects_800B596C[3];
extern MapFx effects_800B59F0[3];
extern MapFx effects_800B5A74[3];
extern MapFx effects_800B5AF8[3];
extern MapFx effects_800B5B7C[3];
extern MapFx effects_800B5C00[3];
extern MapGateSpot data_800B5C84;
extern MapGateSpot data_800B5CB8;
extern MapGateSpot data_800B5CEC;
extern MapGateSpot data_800B5D20;
extern MapGateSpot data_800B5D54;
extern MapGateSpot data_800B5D88;
extern MapGateSpot data_800B5DBC;
extern MapGateSpot data_800B5DF0;
extern MapGateReturn data_800B5E24;
extern MapGateReturn data_800B5E2C;
extern MapGateReturn data_800B5E34;
extern MapGateReturn data_800B5E3C;
extern MapGateReturn data_800B5E44;
extern MapGateReturn data_800B5E4C;
extern MapGateReturn data_800B5E54;
extern MapGateReturn data_800B5E5C;
extern MapEvent events_800B5E64[27];
extern int data_800B6080[16];
extern int data_800B60C0[104];
extern int data_800B6260[24];
extern int data_800B62C0[84];
extern short bones_800B6410[92];
extern int scale_800B64C8[3];
extern MapChainEntry chain_800B64D4[10];
extern MapChainEntry chain_800B6614[5];
extern MapChainEntry* chains_800B66B4[2];

int data_800B4474[2] = {
    7, -1,
};
ActorScriptCmd* script_800B447C = 0;
MapActorModel model_800B4480 = { str_800B22C4, 0x26, 0, 0, 0, data_800B4474, 4, &script_800B447C, 0, 0x800000, 0, 0 };
MapActorModel model_800B44AC = { str_800B22D0, 0x12, (void*)&defaultBones_80079140, 0, 0, 0, 4, 0, 0x20002, 0x800002, 0, 0 };
MapActorModel model_800B44D8 = { data_800B22E0, 0x45, (void*)&defaultBones_80079140, 0, 0, 0, 4, 0, 0x20002, 0x800002, 0, 0 };
MapVoice voices_800B4504[81] = {
    { 0, 0, { 0xB, 0x9C, 0x1B } },
    { 0, 1, { 8, 0x9D, 0x20 } },
    { 1, 0, { 0x18, 0x9D, 0x24 } },
    { 1, 1, { 7, 0x9F, 0x1B } },
    { 1, 2, { 0xF, 0x9F, 0xD } },
    { 2, 0, { 0xE, 0xA1, 0x1B } },
    { 2, 1, { 0x13, 0xA1, 0x13 } },
    { 2, 2, { 0x1A, 0xA1, 0x23 } },
    { 2, 3, { 0x17, 0xA2, 0x1A } },
    { 2, 4, { 2, 0xA3, 0x30 } },
    { 3, 0, { 0x19, 0xDE, 0x18 } },
    { 3, 1, { 0x14, 0xE0, 0x15 } },
    { 5, 0, { 0x15, 0xAC, 0x16 } },
    { 5, 1, { 3, 0xAF, 0x14 } },
    { 6, 0, { 0x19, 0xDE, 0x18 } },
    { 7, 0, { 0xC, 0xA3, 0x1A } },
    { 7, 1, { 0x1C, 0xA3, 0x18 } },
    { 7, 2, { 9, 0xA6, 0x16 } },
    { 7, 3, { 5, 0xA7, 0x17 } },
    { 8, 0, { 0x11, 0xA8, 0xC } },
    { 8, 1, { 0x1E, 0xA8, 0x22 } },
    { 0xA, 0, { 0x1D, 0xAB, 9 } },
    { 0xB, 0, { 0xF, 0xAC, 0x21 } },
    { 0xC, 0, { 0xD, 0xAF, 0x1F } },
    { 0xC, 1, { 0x10, 0xB0, 0x20 } },
    { 0xC, 2, { 0x19, 0xB2, 0x10 } },
    { 0xD, 0, { 0xA, 0xB3, 0x22 } },
    { 0xD, 1, { 0, 0xB4, 0x18 } },
    { 0xD, 2, { 0x11, 0xB4, 0x17 } },
    { 0xD, 3, { 0x13, 0xB4, 0x17 } },
    { 0xD, 4, { 0x16, 0xB4, 0x11 } },
    { 0xE, 0, { 0x1D, 0xB4, 0x1E } },
    { 0xE, 1, { 0x1F, 0xB4, 0xF } },
    { 0xE, 2, { 0xB, 0xB7, 9 } },
    { 0xF, 0, { 7, 0xBA, 0x14 } },
    { 0xF, 1, { 0x12, 0xBA, 0x1B } },
    { 0xF, 2, { 0x1C, 0xBB, 0x15 } },
    { 0xF, 3, { 9, 0xBC, 0x10 } },
    { 0xF, 4, { 0xE, 0xBC, 0x10 } },
    { 0xF, 5, { 0x17, 0xBC, 0x26 } },
    { 0xF, 6, { 8, 0xBD, 0x28 } },
    { 0xF, 7, { 0xC, 0xBD, 0x18 } },
    { 0x10, 0, { 5, 0xBE, 0x27 } },
    { 0x10, 1, { 4, 0xC0, 0x10 } },
    { 0x11, 0, { 0xB, 0xC0, 0x19 } },
    { 0x11, 1, { 0x18, 0xC1, 0x1A } },
    { 0x11, 2, { 6, 0xC2, 0x19 } },
    { 0x12, 0, { 0x14, 0xC2, 0x1E } },
    { 0x13, 0, { 0x15, 0xC2, 0x24 } },
    { 0x13, 1, { 0x19, 0xC2, 0x1C } },
    { 0x13, 2, { 3, 0xC3, 0x12 } },
    { 0x13, 3, { 0x1F, 0xC3, 0x31 } },
    { 0x13, 4, { 1, 0xC4, 0x22 } },
    { 0x13, 5, { 0x1A, 0xC4, 0x13 } },
    { 0x13, 6, { 0x16, 0xC5, 0x14 } },
    { 0x13, 7, { 0x1E, 0xCA, 0x17 } },
    { 0x14, 0, { 0x11, 0xCB, 0x18 } },
    { 0x14, 1, { 0x13, 0xCB, 0xF } },
    { 0x14, 2, { 0, 0xCC, 0x20 } },
    { 0x14, 3, { 9, 0xCC, 0x1D } },
    { 0x14, 4, { 0xE, 0xCC, 0x18 } },
    { 0x15, 0, { 0xF, 0xCD, 0x20 } },
    { 0x15, 1, { 0x1B, 0xCD, 0x28 } },
    { 0x15, 2, { 7, 0xCE, 0x2F } },
    { 0x15, 3, { 0xD, 0xCE, 0x15 } },
    { 0x15, 4, { 4, 0xD0, 0x1C } },
    { 0x15, 5, { 0x10, 0xD0, 0x26 } },
    { 0x15, 6, { 0x1C, 0xD0, 0x2D } },
    { 0x15, 7, { 0x1D, 0xD2, 0x16 } },
    { 0x16, 0, { 2, 0xD3, 0x15 } },
    { 0x16, 1, { 3, 0xD5, 0x19 } },
    { 0x16, 2, { 0xA, 0xD5, 0xE } },
    { 0x16, 3, { 0xC, 0xD5, 0xE } },
    { 0x16, 4, { 0x12, 0xD5, 0x1B } },
    { 0x16, 5, { 0x1A, 0xD7, 0x1B } },
    { 0x16, 6, { 0xB, 0xD9, 0x21 } },
    { 0x17, 0, { 0x16, 0xD9, 0x1A } },
    { 0x17, 1, { 0x13, 0xDA, 0xF } },
    { 0x17, 2, { 6, 0xDB, 0x19 } },
    { 0x17, 3, { 0x18, 0xDB, 0x27 } },
    { 0, 0, { -1, 0, 0 } },
};
int data_800B478C[9] = {
    1, 1, 0, 0, 1, 0, 2, 5,
    5,
};
int species_800B47B0[9] = {
    0x24, 0, 0, 0xD3, 0, 0, 0xD3, 0,
    0,
};
MapMinion minion_800B47D4 = { &model_800B4480, 0, { 0xC99, 0, 0x104F }, -0x7B0, -1, 1, 0, 3 };
MapMinion minion_800B47F8 = { &model_800B44AC, (MapMinionSpecies*)species_800B47B0, { 0xCB2, 0, 0xF23 }, -0x638, -1, 1, -1, 3 };
MapInstr script_800B481C[253] = {
    { 9, 0, 0, 0 },
    { 0x1F, 1, 0x10, 0 },
    { 0xA, 0, 0x10, 0 },
    { 0xA, 0, 1, 0 },
    { 9, 0, 1, 0 },
    { 0x51, 1, 0x10000, 0xB },
    { 0x51, 4, 0, 0x64 },
    { 0x1A, 2, 1, 0 },
    { 0x20, 0, 0x10, 0 },
    { 0xC, 0, 0xF, 0 },
    { 0x49, 1, 0x60001, 1 },
    { 5, 0, 0, 0 },
    { 7, 0, 7, 0 },
    { 0x38, 1, 0, 0 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0xC0001, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x60001, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x48, 0, 0x9F, 1 },
    { 0xC, 0, 0x13A, 0 },
    { 0x49, 0, 0xA2009E, 1 },
    { 0xD, 0, 1, 0 },
    { 0x38, 1, 0, 1 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0xB0001, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x50001, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x20001, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x67, 3, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x67, 2, 0x1E, 0 },
    { 0x67, 6, 0, 0 },
    { 0x38, 1, 0, 2 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x30001, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x40001, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x40001, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0x60001, 1 },
    { 0x42, 0, 4, 0 },
    { 0x49, 1, 0x60001, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x45, 0, 1, 0 },
    { 0xA, 0, 0x20, 0 },
    { 9, 0, 0x10, 0 },
    { 0x62, -1, 2, 0 },
    { 5, 0, 0, 0 },
    { 7, 0, 7, 0 },
    { 0x19, 1, 0, 1 },
    { 0xD, 0, 2, 0 },
    { 0x38, 1, 0, 3 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x50001, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x20001, 1 },
    { 0x3F, 0, 0, 0 },
    { 9, 0, 0x20, 0 },
    { 0x4D, 0, 0, MAP_REF(SetLevantAnimSet_800B37F0) },
    { 0x22, 1, 1, 0 },
    { 0xA, 0, 0x201, 0 },
    { 0xA, 0, 0x202, 0 },
    { 9, 0, 0x201, 0 },
    { 0x43, 1, 1, 0 },
    { 9, 0, 0x202, 0 },
    { 0x22, 1, 2, 0 },
    { 0xA, 0, 0x203, 0 },
    { 0xA, 0, 0x204, 0 },
    { 9, 0, 0x203, 0 },
    { 0x43, 1, 2, 0 },
    { 9, 0, 0x204, 0 },
    { 0x3A, 1, 0, 4 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x70001, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x43, 0, 3, 0 },
    { 0xA, 0, 0x30, 0 },
    { 0xA, 0, 0x40, 0 },
    { 0xA, 0, 0x50, 0 },
    { 0xA, 0, 0x60, 0 },
    { 0xA, 0, 0x70, 0 },
    { 0xA, 0, 0x80, 0 },
    { 9, 0, 0x30, 0 },
    { 0x3A, 1, 0, 7 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0xC0001, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0xB0001, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x90001, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0x90001, 1 },
    { 0x42, 0, 4, 0 },
    { 0x49, 1, 0xA0001, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x301, 0 },
    { 0xA, 0, 0x20, 0 },
    { 9, 0, 0x301, 0 },
    { 0x38, 1, 0, 8 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x90001, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x40001, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x3E, 0, 1, 0 },
    { 0x38, 1, 0, 0xA },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x90001, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x4C, 0, -1, 0 },
    { 0x4D, 0, 0, MAP_REF(StartChain_800B37BC) },
    { 0x65, 0, 0, MAP_REF(data_800B478C) },
    { 0x2C, 0, 1, 0 },
    { 0x4E, 0, 0, MAP_REF(ChainWon_800B37A4) },
    { 0xA, 0, 0x304, 0 },
    { 0xA, 0, 0x20, 0 },
    { 9, 0, 0x304, 0 },
    { 0x23, 0, 1, 0 },
    { 0x38, 1, 0, 0xF },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x90001, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0xC0001, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x80001, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0x90001, 1 },
    { 0x42, 0, 4, 0 },
    { 0x42, 0, 5, 0 },
    { 0x49, 1, 0x70001, 1 },
    { 0x42, 0, 6, 0 },
    { 0x49, 1, 0xC0001, 1 },
    { 0x42, 0, 7, 0 },
    { 0x49, 1, 0xE0001, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x3E, 0, 1, 0 },
    { 0xA, 0, 0x20, 0 },
    { 9, 0, 0x40, 0 },
    { 0x3A, 1, 0, 0x10 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x80001, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x80001, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x90001, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x401, 0 },
    { 0xA, 0, 0x20, 0 },
    { 9, 0, 0x401, 0 },
    { 0x38, 1, 0, 0xA },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x20001, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x4C, 1, -1, 0 },
    { 0x4D, 0, 0, MAP_REF(StartChain_800B37BC) },
    { 0x65, 0, 0, MAP_REF(data_800B478C) },
    { 0x2C, 0, 1, 0 },
    { 0x4E, 0, 0, MAP_REF(ChainWon_800B37A4) },
    { 0xA, 0, 0x402, 0 },
    { 0xA, 0, 0x20, 0 },
    { 9, 0, 0x402, 0 },
    { 0x23, 0, 2, 0 },
    { 0x38, 1, 0, 0x13 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x90001, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x80001, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x70001, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0xC0001, 1 },
    { 0x42, 0, 4, 0 },
    { 0x49, 1, 0x80001, 1 },
    { 0x42, 0, 5, 0 },
    { 0x49, 1, 0x70001, 1 },
    { 0x42, 0, 6, 0 },
    { 0x49, 1, 0x90001, 1 },
    { 0x42, 0, 7, 0 },
    { 0x49, 1, 0xA0001, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x20, 0 },
    { 9, 0, 0x50, 0 },
    { 0x38, 1, 0, 0x14 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0xB0001, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0xA0001, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x90001, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0xB0001, 1 },
    { 0x42, 0, 4, 0 },
    { 0x49, 1, 0x80001, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x20, 0 },
    { 9, 0, 0x60, 0 },
    { 0x38, 1, 0, 0x15 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x90001, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x30001, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x80001, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0xB0001, 1 },
    { 0x42, 0, 4, 0 },
    { 0x49, 1, 0xC0001, 1 },
    { 0x42, 0, 5, 0 },
    { 0x49, 1, 0x90001, 1 },
    { 0x42, 0, 6, 0 },
    { 0x49, 1, 0xB0001, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x20, 0 },
    { 9, 0, 0x70, 0 },
    { 0x38, 1, 0, 0x16 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0xC0001, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x90001, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x70001, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0x90001, 1 },
    { 0x42, 0, 4, 0 },
    { 0x49, 1, 0xB0001, 1 },
    { 0x42, 0, 5, 0 },
    { 0x49, 1, 0x80001, 1 },
    { 0x42, 0, 6, 0 },
    { 0x49, 1, 0xD0001, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x20, 0 },
    { 9, 0, 0x80, 0 },
    { 0x38, 1, 0, 0x17 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x80001, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x90001, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0xA0001, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0xC0001, 1 },
    { 0x3F, 0, 0, 0 },
    { 0xA, 0, 0x90, 0 },
    { 9, 0, 0x90, 0 },
    { 8, 0, 7, 0 },
    { 4, 0, 0, 0 },
    { 0xA, 0, 0x10, 0 },
    { 9, 0, 0xFF, 0 },
    { 3, 0, 0, 0 },
};
MapSavePoint savePoint_800B57EC = { { -0x32, -0x1B4, 0x384 }, str_800B22E8 };
int data_800B57FC[2] = {
    0x1010000, 0,
};
MapWarp warp_800B5804 = { { -0x25, -0xE8, -0xF55 }, -0x688, 0, 5, { 4, 1, 0 } };
MapWarp warp_800B581C = { { -0x1A2, 0, -0x1278 }, -0x155, 0, 9, { 4, 2, 0 } };
MapWarp warp_800B5834 = { { -0xD4, 0, -0x7EC }, 0xE3, 0, 7, { 4, 3, 0 } };
MapWarp warp_800B584C = { { 0x8F, 0, -0x8D9 }, 0x200, 0, 0xB, { 4, 4, 0 } };
MapFx effects_800B5864[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, 0, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B58E8[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 4, 4, 4, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B596C[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 2, 2, 2, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B59F0[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 6, 6, 6, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B5A74[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 1, 1, 1, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B5AF8[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 5, 5, 5, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B5B7C[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 3, 3, 3, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapFx effects_800B5C00[3] = {
    { 1, 0x4E, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 7, 7, 7, 0x30, 0, 0 },
    { 3, 0x14, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x3C, 0, 0, 0, 0, -1, 2, 0, 0 },
    { 5, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
MapGateSpot data_800B5C84 = { 3, 1, { 0x88B, -0x1DE, 0xBF6 }, { 0xB1F, 9, 0xE0C }, -0xDC2, 0x19, { effects_800B5864, effects_800B58E8 }, 1, 0x6A };
MapGateSpot data_800B5CB8 = { 4, 3, { 0x2FD, -0x1AF, 0xE93 }, { 0x481, 0x19, 0x128E }, 0xEE, 0x20, { effects_800B596C, effects_800B59F0 }, 2, 0x76 };
MapGateSpot data_800B5CEC = { 6, 2, { -0x2A3, -0x190, 0xE4E }, { -0x3F7, 0x73, 0x123C }, -0xE1, 0x1A, { effects_800B5A74, effects_800B5AF8 }, 3, 0x89 };
MapGateSpot data_800B5D20 = { 0xB, 4, { -0x753, -0x1DE, 0xB5D }, { -0xA82, 0x8F, 0xE1F }, -0x251, 0x1F, { effects_800B5B7C, effects_800B5C00 }, 4, 0xBA };
MapGateSpot data_800B5D54 = { 3, 6, { 0xA31, -0x12C, 0xD32 }, { 0x6F5, -0xBE, 0xB15 }, 0xA3A, 0x16, { effects_800B58E8, effects_800B5864 }, -1, -1 };
MapGateSpot data_800B5D88 = { 4, 0xA, { 0x426, -0x157, 0x1187 }, { 0x264, -0x9F, 0xCCB }, -0x6E1, 0x16, { effects_800B59F0, effects_800B596C }, -1, -1 };
MapGateSpot data_800B5DBC = { 6, 8, { -0x3A9, -0xCE, 0x111A }, { -0x25B, -0x83, 0xD0F }, -0x8E1, 0x16, { effects_800B5AF8, effects_800B5A74 }, -1, -1 };
MapGateSpot data_800B5DF0 = { 0xB, 0xC, { -0x963, -0xB8, 0xD35 }, { -0x659, -0x83, 0xABB }, -0xA3D, 0x16, { effects_800B5C00, effects_800B5B7C }, -1, -1 };
MapGateReturn data_800B5E24 = { 1, effects_800B58E8 };
MapGateReturn data_800B5E2C = { 2, effects_800B59F0 };
MapGateReturn data_800B5E34 = { 3, effects_800B5AF8 };
MapGateReturn data_800B5E3C = { 4, effects_800B5C00 };
MapGateReturn data_800B5E44 = { 5, effects_800B5864 };
MapGateReturn data_800B5E4C = { 6, effects_800B596C };
MapGateReturn data_800B5E54 = { 7, effects_800B5A74 };
MapGateReturn data_800B5E5C = { 8, effects_800B5B7C };
MapEvent events_800B5E64[27] = {
    { -1, 0, data_800B57FC, 0, { ScriptSpot_800B3450 } },
    { -1, 1, &warp_800B5804, 0, { Warp_800B2374 } },
    { -1, 1, &warp_800B581C, 0, { Warp_800B2374 } },
    { -1, 1, &warp_800B5834, 0, { Warp_800B2374 } },
    { -1, 1, &warp_800B584C, 0, { Warp_800B2374 } },
    { -1, 0xD, &data_800B5C84, 0x10, { GateSpotInit_800B3668 } },
    { -1, 0xD, &data_800B5CB8, 0x10, { GateSpotInit_800B3668 } },
    { -1, 0xD, &data_800B5CEC, 0x10, { GateSpotInit_800B3668 } },
    { -1, 0xD, &data_800B5D20, 0x10, { GateSpotInit_800B3668 } },
    { -1, 0xD, &data_800B5D54, 0x10, { GateSpotInit_800B3668 } },
    { -1, 0xD, &data_800B5D88, 0x10, { GateSpotInit_800B3668 } },
    { -1, 0xD, &data_800B5DBC, 0x10, { GateSpotInit_800B3668 } },
    { -1, 0xD, &data_800B5DF0, 0x10, { GateSpotInit_800B3668 } },
    { -1, 0xD, &data_800B5E24, 4, { GateReturnInit_800B36B0 } },
    { -1, 0xD, &data_800B5E2C, 4, { GateReturnInit_800B36B0 } },
    { -1, 0xD, &data_800B5E34, 4, { GateReturnInit_800B36B0 } },
    { -1, 0xD, &data_800B5E3C, 4, { GateReturnInit_800B36B0 } },
    { -1, 0xD, &data_800B5E44, 4, { GateReturnInit_800B36B0 } },
    { -1, 0xD, &data_800B5E4C, 4, { GateReturnInit_800B36B0 } },
    { -1, 0xD, &data_800B5E54, 4, { GateReturnInit_800B36B0 } },
    { -1, 0xD, &data_800B5E5C, 4, { GateReturnInit_800B36B0 } },
    { -1, 0xF, &minion_800B47D4, 0x14, { MinionInit_800B2A9C } },
    { -1, 0xF, &minion_800B47F8, 0x14, { MinionInit_800B2A9C } },
    { -1, 0xB, voices_800B4504, 0, { 0 } },
    { 0x20, 8, script_800B481C, 0, { 0 } },
    { -1, 0xC, &savePoint_800B57EC, 0xC, { SavePointInit_800B3804 } },
    { 0, 0x12, 0, 0, { 0 } },
};
int data_800B6080[16] = {
    0x4B, 0, 0, 0, 0x4D, 0, 0, MAP_REF(StopLevantIfSet_800B3ED0),
    0x58, 0, 0, 0, 3, 0, 0, 0,
};
int data_800B60C0[104] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x3E, -1, 4, 5, 0x67, 0xC, 5, 0,
    0x30, 0, 1, 0, 0x31, 0, 1, 0,
    0xC, 0, 0x1E, 0, 0x67, 5, 0x1E, 0,
    0xC, 0, 0x3C, 0, 0x30, 0, 2, 0,
    0x31, 0, 2, 0, 0xC, 0, 2, 0,
    0x1A, 1, 0, 0, 0x67, 0, 0, 0,
    0x67, 0xC, 5, 0, 0x30, 0, 1, 0,
    0x31, 0, 1, 0, 0xC, 0, 0x1E, 0,
    0x67, 5, 0x1E, 0, 0xC, 0, 0x3C, 0,
    0x1A, 1, 1, 0, 0x67, 4, 0x1E, 0,
    0x67, 6, 0, 0, 8, 0, 1, 0,
    4, 0, 0, 0, 3, 0, 0, 0,
};
int data_800B6260[24] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x3E, -1, 8, 5, 8, 0, 1, 0,
    4, 0, 0, 0, 3, 0, 0, 0,
};
int data_800B62C0[84] = {
    5, 0, 0, 0, 7, 0, 1, 0,
    0x67, 0xC, 5, 0, 0x30, 0, 0, 0,
    0x31, 0, 0, 0, 0xC, 0, 0x1E, 0,
    0x67, 5, 0x1E, 0, 0xC, 0, 0x3C, 0,
    0x1A, 1, 1, 0, 0x67, 4, 0x1E, 0,
    0x1F, 1, 0, 0, 0xA, 0, 1, 0,
    0xA, 0, 2, 0, 9, 0, 1, 0,
    0x67, 6, 0, 0, 9, 0, 2, 0,
    0x21, 0, 0, 0, 0x30, 0, 1, 0,
    8, 0, 1, 0, 4, 0, 0, 0,
    3, 0, 0, 0,
};
short bones_800B6410[92] = {
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
int scale_800B64C8[3] = {
    0x1000, 0x1000, 0x1000,
};
MapChainEntry chain_800B64D4[10] = {
    { 0xA, 0x18, 0, 0, 0, 0xB, 1, 0 },
    { 0, 0, 0, 1, 0x10, 5, 1, 0x5A },
    { 4, 0, 0, 0x10, 1, 0, 1, 0x24 },
    { 0xA, 0x18, 0, 0, 0, 0xC, 1, 0 },
    { 0, 0x12, 0, 1, 0x10, 5, 1, 0 },
    { 4, 0, 0, 0x10, 1, 0, 1, 0x13 },
    { 0xA, 0x18, 0, 0, 0, 0xD, 1, 0 },
    { 0, 4, 0, 1, 1, 5, 1, 0 },
    { 0xA, 0x18, 0, 0, 0, 0xE, 1, 0 },
    { -1, -1, 0, 0, 0, -1, 1, -1 },
};
MapChainEntry chain_800B6614[5] = {
    { 0xA, 0x18, 0, 0, 0, 0x11, 1, 0 },
    { 0, 0, 0, 1, 0x10, 5, 1, 0x5A },
    { 0xA, 0x18, 0, 0, 0, 0x12, 1, 0 },
    { 0, 5, 0, 1, 0x10, 5, 1, 0 },
    { -1, -1, 0, 0, 0, -1, 1, -1 },
};
MapChainEntry* chains_800B66B4[2] = { chain_800B64D4, chain_800B6614 };
const char unknown_800B22C0[4] = "\x8d";
const char str_800B22C4[12] = "\x82j\x82\x8f\x82\x92\x82\x89\x82\x93";
const char str_800B22D0[16] = "\x83""A\x83\x8b\x83p\x83^\x83\x8d\x83\x93";
const char data_800B22E0[8] = "\x82o\x82""c\x82`";
const char str_800B22E8[28] = "\x82""a\x82`\x82q\x82q\x82h\x82""d\x82q\x81@\x82""f\x82`\x82s\x82""d";
const MapFxInits fxInits_800B2304 = { { 0, FxModel_800B2874, 0, FxMdec_800B357C, 0 } };
const MapRgb savePointDim_800B2318 = { 0x80, 0x40, 0x20, 0 };
