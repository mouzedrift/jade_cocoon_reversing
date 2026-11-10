#include "maps/map.h"

void Warp_800B2338(MapEnt* ent);
void MinionInit_800B245C(MapEnt* ent);
int AddEffects_800B2794(MapFx* fx);
void FxSprite_800B2920(MapEnt* ent);
void FxModel_800B2A94(MapEnt* ent);
void SavePoint_800B2CBC(MapEnt* ent);
void MapInit_800B312C(int phase);
void MinionIdle_800B31FC(MapEnt* ent);
void FxInit_800B3204(MapEnt* ent);
void SavePointInit_800B32BC(MapEnt* ent);
int SetEvents_800B32FC(MapExitArgs* args);
int WarpLostBattle_800B3348(void);
int FreeEventData_800B3368(void);
void StartMapTask_800B3388(void);
void MapTaskLoad_800B33B8(EventEntry* entry, int* st);
void MapTask_800B3450(EventEntry* entry, int* st);
int LeaveArea_800B3504(MapEvent* ev, int area);
int EnterArea_800B3620(MapEvent* ev, int area, int prev);
void RequestModels_800B3728(MapEvent* ev);
void EntityTask_800B37F8(EventEntry* entry, MapEnt* ent);
int AddEntity_800B3878(void* ev);
void MapInitOld_800B39A4(int phase);
int MinionF_800B3A14(void);
int MinionF_800B3A1C(void);
int FxFrame_800B3A24(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B3AA8(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B3B74(MapFx* fx, MapFxWork* w);

extern const int unknown_800B22C0[1];
extern const char data_800B22C4[24];
extern const char data_800B22DC[16];
extern const char data_800B22EC[16];
extern const char data_800B22FC[20];
extern const char data_800B2310[12];
extern const MapFxInits fxInits_800B231C;
extern const MapRgb savePointDim_800B2330;
extern const MapRgb savePointLit_800B2334;
extern int unknown_800B3CBC[4];
extern int data_800B3CCC[54];
extern int data_800B3DA4[12];
extern int data_800B3DD4[32];
extern int data_800B3E54[11];
extern int data_800B3E80[12];
extern int data_800B3EB0[1];
extern int data_800B3EB4[11];
extern int data_800B3EE0[48];
extern int data_800B3FA0[12];
extern int data_800B3FD0[12];
extern int data_800B4000[19];
extern int data_800B404C[19];
extern int data_800B4098[32];
extern int data_800B4118[11];
extern int data_800B4144[82];
extern int data_800B428C[32];
extern int data_800B430C[11];
extern int data_800B4338[50];
extern int data_800B4400[6];
extern int data_800B4418[6];
extern int data_800B4430[66];
extern int data_800B4538[44];
extern int data_800B45E8[4];
extern int data_800B45F8[4];
extern int data_800B4608[4];
extern int data_800B4618[18];
extern int data_800B4660[200];
extern int data_800B4980[320];
extern int data_800B4E80[72];
extern int data_800B4FA0[156];
extern int data_800B5210[76];
extern int data_800B5340[9];
extern int data_800B5364[9];
extern int data_800B5388[9];
extern int data_800B53AC[9];
extern MapEvent data_800B53D0[8];
extern MapEvent data_800B5470[5];
extern MapEvent data_800B54D4[4];
extern MapEvent data_800B5524[8];
extern short bones_800B55C4[92];
extern int scale_800B567C[3];
extern MapEvent* eventSets_800B5688[4];
extern int returnMaps_800B5698[4];
extern MapEvent* curEvents_800B56A8;

int unknown_800B3CBC[4] = {
    0xC8, 0, -0x11C6, MAP_REF(data_800B22C4),
};
int data_800B3CCC[54] = {
    0, 0x460000, 0x10001, 0xB0001, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x2060003, 0xB0006, 0x3070004, 0xB0007,
    0x4080005, 0xB0008, 0x2090003, 0xB0009, 0x30A0004, 0xB000A, 0x2130003, 0xB0013,
    0x3140004, 0xB0014, 0x4150005, 0xB0015, 0x2160003, 0xB0016, 0x3170004, 0xB0017,
    0x4180005, 0xB0018, 0x10B0002, 0xB000B, 0x20C0003, 0xB000C, 0x30D0004, 0xB000D,
    0x40E0005, 0xB000E, 0x20F0003, 0xB000F, 0x3100004, 0xB0010, 0x4110005, 0xB0011,
    0x2120003, 0xB0012, 0x2190003, 0xB0019, -1, -1,
};
int data_800B3DA4[12] = {
    -0x1FDF4, 0x150000, -0x1FEF3, -0x1FEF1, -0xFEFD, -0xFDFF, 0x150000, -0x1FEEB,
    -0x1FDE9, 0x3C0000, -0x1FEF0, -0x1FF00,
};
int data_800B3DD4[32] = {
    -0x7FF868AC, -0x7FF868A0, -0x7FF86890, -0x7FF86858, -0x7FF86820, -0x7FF867E8, -0x7FF867B0, -0x7FF86778,
    -0x7FF86740, -0x7FF86708, -0x7FF866AC, -0x7FF86674, -0x7FF8663C, -0x7FF86604, -0x7FF865D0, -0x7FF865B8,
    MAP_REF(data_800B3DA4), -0x7FF8652C, -0x7FF864F0, -0x7FF864B4, -0x7FF864A0, -0x7FF8648C, -0x7FF86474, -0x7FF86450,
    -0x7FF863E8, -0x7FF86398, -0x7FF86378, -0x7FF86304, -0x7FF862B4, -0x7FF86208, -0x7FF8616C, -0x7FF8609C,
};
int data_800B3E54[11] = {
    MAP_REF(data_800B22DC), 0x25, MAP_REF(data_800B3CCC), 0, 0, 0, 4, MAP_REF(data_800B3DD4),
    0, 0x800000, 0,
};
int data_800B3E80[12] = {
    -0x1FEF1, -0xFDF9, 0x1000000, -0x1FDE9, 0x3C0000, -0x1FDEC, 0x40000000, -0xFEF8,
    -0xFDF5, 0, -0x1FEF0, -0x1FF00,
};
int data_800B3EB0[1] = {
    0,
};
int data_800B3EB4[11] = {
    MAP_REF(data_800B22EC), 0x24, 0, 0, 0, 0, 4, MAP_REF(data_800B3EB0),
    0, 0x800000, 0,
};
int data_800B3EE0[48] = {
    0, 0x4E0000, 0x10001, 0xB0001, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x1060002, 0xB0006, 0x2070003, 0xB0007,
    0x3080004, 0xB0008, 0x4090005, 0xB0009, 0x10A0002, 0xB000A, 0x20B0003, 0xB000B,
    0x30C0004, 0xB000C, 0x40D0005, 0xB000D, 0x10E0002, 0xB000E, 0x20F0003, 0xB000F,
    0x3100004, 0xB0010, 0x4110005, 0xB0011, 0x2120003, 0xB0012, 0x3130004, 0xB0013,
    0x4140005, 0xB0014, 0x1150002, 0xB0015, 0x1160002, 0xB0016, -1, -1,
};
int data_800B3FA0[12] = {
    -0x1FEF1, -0xFDF9, 0x1000000, -0x1FDE9, 0x3C0000, -0x1FDEC, 0x40000000, -0xFEF8,
    -0xFDF5, 0, -0x1FEF0, -0x1FF00,
};
int data_800B3FD0[12] = {
    -0x1FDF4, 0x150000, -0x1FEF3, -0x1FEF1, -0xFEFD, -0xFDFF, 0x150000, -0x1FEEB,
    -0x1FDE9, 0x3C0000, -0x1FEF0, -0x1FF00,
};
int data_800B4000[19] = {
    -0x1FDF4, 0x1A0000, -0x1FEF3, -0x1FEF1, -0xFDF9, 0x1000000, -0xFEFD, -0xFDFF,
    0x1A0000, -0x1FDEC, 0x40000000, -0xFEF8, -0xFDF5, 0, -0x1FEF0, -0x1FEEF,
    -0xFDF2, 0x1A0000, -0x1FF00,
};
int data_800B404C[19] = {
    -0x1FDF4, 0x1B0000, -0x1FEF3, -0x1FEF1, -0xFDF5, 0x10000, -0xFDFA, 0x1000000,
    -0xFDFF, 0x1B0000, -0x1FDEC, 0x40000000, -0xFEF8, -0x1FEF0, -0xFDFF, 0x40000,
    -0xFDF2, 0x1B0000, -0x1FF00,
};
int data_800B4098[32] = {
    -0x7FF868AC, -0x7FF868A0, -0x7FF86890, -0x7FF86858, -0x7FF86820, -0x7FF867E8, -0x7FF867B0, -0x7FF86778,
    -0x7FF86740, -0x7FF86708, -0x7FF866AC, -0x7FF86674, -0x7FF8663C, -0x7FF86604, -0x7FF865D0, -0x7FF865B8,
    MAP_REF(data_800B3FD0), MAP_REF(data_800B4000), MAP_REF(data_800B404C), -0x7FF864B4, -0x7FF864A0, -0x7FF8648C, -0x7FF86474, -0x7FF86450,
    0, 0, 0, 0, 0, 0, 0, 0,
};
int data_800B4118[11] = {
    MAP_REF(data_800B22FC), 6, MAP_REF(data_800B3EE0), 0, 0, 0, 4, MAP_REF(data_800B4098),
    0, 0x800000, 0,
};
int data_800B4144[82] = {
    0, 0x4E0000, 0x10001, 0xB0001, 0x10E0002, 0xB000E, 0x20F0003, 0xB000F,
    0x3020004, 0xB0002, 0x4030005, 0xB0003, 0x5040006, 0xB0004, 0x6050007, 0xB0005,
    0x6060007, 0xB0006, 0x6070007, 0xB0007, 0x3080004, 0xB0008, 0x4090005, 0xB0009,
    0x50A0006, 0xB000A, 0x60B0007, 0xB000B, 0x60C0007, 0xB000C, 0x60D0007, 0xB000D,
    0x3170004, 0xB0017, 0x4180005, 0xB0018, 0x5190006, 0xB0004, 0x6050007, 0xB0005,
    0x6060007, 0xB0006, 0x6070007, 0xB0007, 0x31D0004, 0xB001D, 0x41E0005, 0xB001E,
    0x51F0006, 0xB000A, 0x60B0007, 0xB000B, 0x60C0007, 0xB000C, 0x60D0007, 0xB000D,
    0x3100004, 0xB0010, 0x4110005, 0xB0011, 0x5140006, 0xB0014, 0x6150007, 0xB0015,
    0x4120005, 0xB0012, 0x4130005, 0xB0013, 0x1160002, 0xB0016, 0x2230003, 0xB0023,
    0x3240004, 0xB0024, 0x4250005, 0xB0025, 0x5260006, 0xB0026, 0x6270007, 0xB0027,
    -1, -1,
};
int data_800B428C[32] = {
    -0x7FF868AC, -0x7FF868A0, -0x7FF86890, -0x7FF86858, -0x7FF86820, -0x7FF867E8, -0x7FF867B0, -0x7FF86778,
    -0x7FF86740, -0x7FF86708, -0x7FF866AC, -0x7FF86674, -0x7FF8663C, -0x7FF86604, -0x7FF865D0, -0x7FF865B8,
    -0x7FF86594, -0x7FF8652C, -0x7FF864F0, -0x7FF864B4, -0x7FF864A0, -0x7FF8648C, -0x7FF86474, -0x7FF86450,
    0, 0, 0, 0, 0, 0, 0, 0,
};
int data_800B430C[11] = {
    MAP_REF(data_800B2310), 7, MAP_REF(data_800B4144), 0, 0, 0, 4, MAP_REF(data_800B428C),
    0, 0x800000, 0,
};
int data_800B4338[50] = {
    0xD0000, 0x120265, 0x100100, 0x160265, 0x120200, 0x1E0265, 0x300, 0x130266,
    0x1E0400, 0x130266, 0x50500, 0x160267, 0x1D0600, 0x1E0267, 0x20001, 0x160141,
    0x160101, 0x2C0142, 0x40201, 0x190143, 0x90301, 0x110143, 0xF0401, 0x1D0143,
    0x150002, 0x1B04EC, 0xA0102, 0x1404ED, 0x140003, 0x3004ED, 0x130103, 0x2104EE,
    0x70203, 0x2E04EF, 0x303, 0x1C04F0, 0x70004, 0x140144, 0x130104, 0x1E0144,
    0x190204, 0x190144, 0xD0304, 0x290147, 0x60006, 0x1F04F1, 0xB0106, 0x1204F3,
    -0x10000, 0,
};
int data_800B4400[6] = {
    0, 0, 0x364, 0x4000, 0x50000, 0x60002,
};
int data_800B4418[6] = {
    0, 0, -0x6FE, 0x4000, 0x50001, 0x80002,
};
int data_800B4430[66] = {
    0x980001, -0xC8, 0, 0, 0, 0, 0xF0, 0,
    -0x10000, 0, 0, 0x990001, -0xC8, 0, 0, 0,
    0, 0x4F00A1, 0, -0x10000, 0, 0, 0x9A0001, -0xC8,
    0, 0, 0, 0, 0x95001F, 0, -0x10000, 0,
    0, 0x9B0001, -0xC8, 0, 0, 0, 0, 0xB3001F,
    0, -0x10000, 0, 0, 0x9C0001, -0xC8, 0, 0,
    0, 0, 0xD1001F, 0, -0x10000, 0, 0, 5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};
int data_800B4538[44] = {
    0xA00001, 0, 0, 0, 0, 0, 0x9B, 0,
    -0x10000, 0, 0, 0xA10001, 0, 0, 0, 0,
    0, 0x9B001E, 0, -0x10000, 0, 0, 0x1620000, 0,
    0, 0, 0, 0, 0x9B, 0, -0x10000, 0x30,
    0, 5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};
int data_800B45E8[4] = {
    -0x67, 0, -0x1D6, 0,
};
int data_800B45F8[4] = {
    -0xC8, 0, -0x1A9, 0,
};
int data_800B4608[4] = {
    -0xC8, 0, 0, -0x800,
};
int data_800B4618[18] = {
    0, 1, 0, 1, 0, 0, 1, 2,
    5, 0x30, 0x44000000, 0xC, 0x2F, 0x44000000, 0xC, 0xD3,
    0, 0,
};
int data_800B4660[200] = {
    0x4D, 0, 0, MAP_REF(FreeEventData_800B3368), 0x45, 0, 1, 0,
    0x65, 0, 0, MAP_REF(data_800B4618), 0x66, 0, 0, 0,
    0xA, 0, 0x10, 0, 0xA, 0, 0x20, 0,
    9, 0, 0x10, 0, 0x1A, 2, 1, 0,
    0x13, 0, 0, MAP_REF(data_800B45F8), 0x13, 1, 0, MAP_REF(data_800B4608),
    0x48, 1, 0x2C, 5, 0x46, 1, 0, MAP_REF(data_800B3FA0),
    0xD, 0, 2, 0, 0x67, 3, 0x1E, 0,
    0x67, 6, 0, 0, 8, 0, 7, 0,
    4, 0, 0, 0, 0x4C, 2, 1, 0,
    0x4D, 0, 0, MAP_REF(SetEvents_800B32FC), 0xA, 0, 0xFF, 0,
    9, 0, 0x20, 0, 0x1A, 2, 1, 0,
    0x13, 0, 0, MAP_REF(data_800B45F8), 0x13, 1, 0, MAP_REF(data_800B4608),
    0x48, 0, 0x15B, 5, 0x48, 1, 0x29, 1,
    0x67, 2, 0x1E, 0, 0x61, 0, 3, 0,
    0x67, 6, 0, 0, 0x38, 1, 0, 3,
    0x42, 0, 0, 0, 0x49, 1, 0x230029, 1,
    0x42, 0, 1, 0, 0x49, 1, 0x240029, 1,
    0x42, 0, 2, 0, 0x49, 1, 0x250029, 1,
    0x42, 0, 3, 0, 0x49, 1, 0x26002B, 1,
    0x3F, 0, 0, 0, 0xE, 1, 0xC0000, 0,
    0x67, 5, 0x1E, 0, 0x67, 6, 0, 0,
    0x4C, 3, 0, 0, 0x4D, 0, 0, MAP_REF(SetEvents_800B32FC),
    8, 0, 7, 0, 4, 0, 0, 0,
    0x4D, 0, 0, MAP_REF(WarpLostBattle_800B3348), 0xA, 0, 0xFF, 0,
    9, 0, 0xFF, 0, 3, 0, 0, 0,
};
int data_800B4980[320] = {
    0x64, 0, 3, 0, 5, 0, 0, 0,
    7, 0, 7, 0, 0xE, 1, 0xC0004, 0,
    0x67, 0x11, 1, 0, 0x67, 0xC, 0xFF04, 0x25,
    0xC, 0, 1, 0, 0x67, 0x11, 0, 0,
    0x60, 0, 0, MAP_REF(data_800B45E8), 0x61, 0, 3, 0,
    0x13, 0, 0, MAP_REF(data_800B45E8), 0x1A, 4, 1, 0,
    0x49, 2, 0x320043, 5, 0xD, 0, 4, 0,
    0x38, 2, 0, 0, 0x42, 0, 0, 0,
    0x49, 2, 0x340044, 1, 0x42, 0, 1, 0,
    0x49, 2, 0x350043, 1, 0x42, 0, 2, 0,
    0x49, 2, 0x380043, 1, 0x42, 0, 3, 0,
    0x49, 2, 0x360043, 1, 0x42, 0, 4, 0,
    0x49, 2, 0x3E0043, 1, 0x42, 0, 5, 0,
    0x49, 2, 0x380043, 1, 0x42, 0, 5, 0,
    0x49, 2, 0x370043, 1, 0x3F, 0, 0, 0,
    0x49, 2, 0x340044, 1, 0x68, 1, 0x1F, 0,
    0x67, 0xC, 6, 0, 0x4B, 0, 0, MAP_REF(data_800B4430),
    0x4D, 0, 0, MAP_REF(AddEffects_800B2794), 0xC, 0, 0x1E, 0,
    0x49, 0, 0x1850186, 1, 0xC, 0, 0xB3, 0,
    0x67, 0xD, 0x4E, 0, 0x67, 5, 0x1F, 0,
    0x67, 6, 0, 0, 0x67, 0xC, 0xFF03, 6,
    0x68, 0, 0, 0, 0x1A, 4, 0, 0,
    0x1A, 2, 1, 0, 0x67, 4, 0x1E, 0,
    0x67, 6, 0, 0, 0x49, 0, 0x18A0159, 1,
    0xD, 0, 1, 0, 0x38, 1, 0, 1,
    0x42, 0, 0, 0, 0x49, 1, 0x510056, 1,
    0x42, 0, 1, 0, 0x49, 1, 0x520056, 1,
    0x42, 0, 2, 0, 0x49, 1, 0x530056, 1,
    0x42, 0, 3, 0, 0x49, 1, 0x540056, 1,
    0x42, 0, 4, 0, 0x49, 1, 0x530056, 1,
    0x3F, 0, 0, 0, 0x49, 0, 0x1570159, 1,
    0x49, 1, 0x550057, 1, 0x68, 1, 0x20, 0,
    0x67, 0xC, 6, 0, 0x4B, 0, 0, MAP_REF(data_800B4430),
    0x4D, 0, 0, MAP_REF(AddEffects_800B2794), 0xC, 0, 0x32, 0,
    0x49, 0, 0x1850186, 1, 0xC, 0, 0x8B, 0,
    0x67, 0xD, 0x4E, 0, 0x67, 5, 0x1F, 0,
    0x67, 6, 0, 0, 0x67, 0xC, 0xFF03, 6,
    0x68, 0, 0, 0, 8, 0, 7, 0,
    4, 0, 0, 0, 0x4C, 1, 1, 0,
    0x4D, 0, 0, MAP_REF(SetEvents_800B32FC), 3, 0, 0, 0,
};
int data_800B4E80[72] = {
    5, 0, 0, 0, 7, 0, 7, 0,
    0x48, 0, 0x186, 5, 0x67, 4, 0x1E, 0,
    0x67, 6, 0, 0, 0x49, 0, 0x18E018F, 1,
    0xD, 0, 1, 0, 0x38, 1, 0, 2,
    0x42, 0, 0, 0, 0x49, 1, 0x200029, 1,
    0x42, 0, 1, 0, 0x49, 1, 0x210029, 1,
    0x3F, 0, 0, 0, 0x49, 0, 0x18D0190, 1,
    0x49, 1, 0x22002A, 1, 0xD, 0, 3, 0,
    0xB, 0, 0, MAP_REF(data_800B4660), 3, 0, 0, 0,
};
int data_800B4FA0[156] = {
    5, 0, 0, 0, 7, 0, 3, 0,
    0x1A, 2, 1, 0, 0x48, 0, 0x159, 5,
    0x48, 1, 0x5C, 5, 0x67, 2, 0x1E, 0,
    0x67, 6, 0, 0, 0x38, 1, 0, 4,
    0x42, 0, 0, 0, 0x49, 1, 0x58005D, 1,
    0x42, 0, 1, 0, 0x49, 1, 0x59005D, 1,
    0x42, 0, 2, 0, 0x49, 1, 0x5A005D, 1,
    0x42, 0, 3, 0, 0x48, 1, 0x5B, 1,
    0x48, 1, 0x5D, 1, 0x3F, 0, 0, 0,
    0x49, 1, 0x5E005C, 1, 0x49, 0, 0x158015E, 1,
    0x49, 0, 0x15F0159, 1, 0x46, 1, 0, MAP_REF(data_800B3E80),
    0x4B, 0, 0, MAP_REF(data_800B4538), 0x4D, 0, 0, MAP_REF(AddEffects_800B2794),
    0xC, 0, 0x6F, 0, 0x67, 0xD, 0x1E, 0,
    0xC, 0, 0x2C, 0, 0x49, 0, 0x155015C, 1,
    0xD, 0, 1, 0, 0x3E, 0xF, 1, 5,
    0x67, 0xC, 0xFF00, 0, 0x67, 3, 0x1E, 0,
    0x67, 6, 0, 0, 8, 0, 3, 0,
    4, 0, 0, 0, 0x4C, 0, 0, 0,
    0x4D, 0, 0, MAP_REF(SetEvents_800B32FC), 0x53, 0, 0xCD, 0,
    3, 0, 0, 0,
};
int data_800B5210[76] = {
    0x64, 0, 2, 0, 5, 0, 0, 0,
    7, 0, 7, 0, 0xE, 1, 0xC0004, 0,
    0x67, 0x11, 1, 0, 0x67, 0xC, 0xFF04, 0x25,
    0xC, 0, 1, 0, 0x67, 0x11, 0, 0,
    0x19, 1, 0, 0x29, 0x19, 0, 1, -1,
    0x48, 0, 0x159, 5, 0x38, 1, 0, 6,
    0x42, 0, 0, 0, 0x49, 1, 0x270029, 1,
    0x42, 0, 1, 0, 0x49, 1, 0x280029, 1,
    0x3F, 0, 0, 0, 0xB, 0, 0, MAP_REF(data_800B4660),
    3, 0, 0, 0,
};
int data_800B5340[9] = {
    MAP_REF(data_800B3EB4), 0, -0xC8, 0, 0, -0x800, 0x56, 9,
    3,
};
int data_800B5364[9] = {
    MAP_REF(data_800B3E54), 0, -0xC8, 0, 0, -0x800, 0x45, 2,
    3,
};
int data_800B5388[9] = {
    MAP_REF(data_800B4118), 0, -0xC8, 0, 0, -0x800, 0x29, 0,
    2,
};
int data_800B53AC[9] = {
    MAP_REF(data_800B430C), 0, -0xC8, 0, 0, -0x800, 1, -1,
    3,
};
MapEvent data_800B53D0[8] = {
    { -1, 0xF, data_800B5340, 0x14, { (void*)MinionInit_800B245C } },
    { -1, 0xF, data_800B5364, 0x14, { (void*)MinionInit_800B245C } },
    { -1, 1, data_800B4400, 0, { (void*)Warp_800B2338 } },
    { -1, 1, data_800B4418, 0, { (void*)Warp_800B2338 } },
    { -1, 8, data_800B4980, 0, { 0 } },
    { -1, 0xB, data_800B4338, 0, { 0 } },
    { -1, 0xC, unknown_800B3CBC, 0xC, { (void*)SavePointInit_800B32BC } },
    { 0, 0x12, 0, 0, { 0 } },
};
MapEvent data_800B5470[5] = {
    { -1, 0xF, data_800B5388, 0x14, { (void*)MinionInit_800B245C } },
    { -1, 0xF, data_800B53AC, 0x14, { (void*)MinionInit_800B245C } },
    { -1, 8, data_800B4E80, 0, { 0 } },
    { -1, 0xB, data_800B4338, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
MapEvent data_800B54D4[4] = {
    { -1, 0xF, data_800B5340, 0x14, { (void*)MinionInit_800B245C } },
    { -1, 8, data_800B4FA0, 0, { 0 } },
    { -1, 0xB, data_800B4338, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
MapEvent data_800B5524[8] = {
    { -1, 0xF, data_800B5388, 0x14, { (void*)MinionInit_800B245C } },
    { -1, 0xF, data_800B53AC, 0x14, { (void*)MinionInit_800B245C } },
    { -1, 1, data_800B4400, 0, { (void*)Warp_800B2338 } },
    { -1, 1, data_800B4418, 0, { (void*)Warp_800B2338 } },
    { -1, 8, data_800B5210, 0, { 0 } },
    { -1, 0xB, data_800B4338, 0, { 0 } },
    { -1, 0xC, unknown_800B3CBC, 0xC, { (void*)SavePointInit_800B32BC } },
    { 0, 0x12, 0, 0, { 0 } },
};
short bones_800B55C4[92] = {
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
int scale_800B567C[3] = {
    0x1000, 0x1000, 0x1000,
};
MapEvent* eventSets_800B5688[4] = { data_800B53D0, data_800B5470, data_800B54D4, data_800B5524 };
int returnMaps_800B5698[4] = {
    -1, 2, 3, -1,
};
MapEvent* curEvents_800B56A8 = 0;
const int unknown_800B22C0[1] = {
    0x10D,
};
const char data_800B22C4[24] = "\x82""c\x81""D\x82""c\x82q\x82`\x82""f\x82n\x82m\x82""e\x82k\x82P";
const char data_800B22DC[16] = "\x82j\x82\x89\x82\x8b\x82\x89\x82\x8e\x82\x81\x82\x8b";
const char data_800B22EC[16] = "\x82j\x82\x85\x82\x8c\x82\x8d\x82\x81\x82\x92";
const char data_800B22FC[20] = "\x82v\x82\x89\x82\x8e\x82\x84\x81@\x82""a\x82\x8f\x82\x93\x82\x93";
const char data_800B2310[12] = "\x82""a\x82r\x82v\x82r";
const MapFxInits fxInits_800B231C = { { FxSprite_800B2920, FxModel_800B2A94, 0, 0, 0 } };
const MapRgb savePointDim_800B2330 = { 0x80, 0x40, 0x20, 0 };
const MapRgb savePointLit_800B2334 = { 0x20, 0x40, 0x80, 0 };
