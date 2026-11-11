#include "maps/map.h"

void Warp_800B2304(MapEnt* ent);
void MinionInit_800B2428(MapEnt* ent);
int AddEffects_800B2760(MapFx* fx);
void FxSprite_800B28EC(MapEnt* ent);
void FxModel_800B2A60(MapEnt* ent);
void MapInit_800B2C88(int phase);
void MinionIdle_800B2D34(MapEnt* ent);
void FxInit_800B2D3C(MapEnt* ent);
int SetEvents_800B2DF4(MapExitArgs* args);
int OnMesh2_800B2E40(void);
int WarpLostBattle_800B2E58(void);
int FreeEventData_800B2E78(void);
void StartMapTask_800B2E98(void);
void MapTaskLoad_800B2EC8(EventEntry* entry, int* st);
void MapTask_800B2F60(EventEntry* entry, int* st);
int LeaveArea_800B3014(MapEvent* ev, int area);
int EnterArea_800B3130(MapEvent* ev, int area, int prev);
void RequestModels_800B3238(MapEvent* ev);
void EntityTask_800B3308(EventEntry* entry, MapEnt* ent);
int AddEntity_800B3388(void* ev);
void MapInitOld_800B34B4(int phase);
int MinionF_800B3524(void);
int MinionF_800B352C(void);
int FxFrame_800B3534(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B35B8(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B3684(MapFx* fx, MapFxWork* w);

extern const int unknown_800B22C0[1];
extern const char data_800B22C4[12];
extern const char data_800B22D0[20];
extern const char data_800B22E4[12];
extern const MapFxInits fxInits_800B22F0;
extern int unknown_800B37CC[2];
extern int data_800B37D4[12];
extern int data_800B3804[12];
extern int data_800B3834[1];
extern int data_800B3838[11];
extern int data_800B3864[48];
extern int data_800B3924[12];
extern int data_800B3954[12];
extern int data_800B3984[19];
extern int data_800B39D0[19];
extern int data_800B3A1C[32];
extern int data_800B3A9C[11];
extern int data_800B3AC8[82];
extern int data_800B3C10[32];
extern int data_800B3C90[11];
extern int data_800B3CBC[46];
extern int data_800B3D74[6];
extern int data_800B3D8C[6];
extern int data_800B3DA4[6];
extern int data_800B3DBC[6];
extern int data_800B3DD4[66];
extern int data_800B3EDC[44];
extern int data_800B3F8C[4];
extern int data_800B3F9C[18];
extern int data_800B3FE4[176];
extern int data_800B42A4[212];
extern int data_800B45F4[56];
extern int data_800B46D4[136];
extern int data_800B48F4[76];
extern int data_800B4A24[9];
extern int data_800B4A48[9];
extern int data_800B4A6C[9];
extern MapEvent data_800B4A90[8];
extern MapEvent data_800B4B30[5];
extern MapEvent data_800B4B94[4];
extern MapEvent data_800B4BE4[9];
extern short bones_800B4C98[92];
extern int scale_800B4D50[3];
extern MapEvent* eventSets_800B4D5C[4];
extern MapEvent* curEvents_800B4D6C;

int unknown_800B37CC[2] = {
    7, -1,
};
int data_800B37D4[12] = {
    -0x1FEF1, -0xFDF5, 0x10000, -0xFDFA, 0x1000000, -0x1FDE9, 0x3C0000, -0x1FDEC,
    0x40000000, -0xFEF8, -0x1FEF0, -0x1FF00,
};
int data_800B3804[12] = {
    -0x1FEF1, -0xFDF9, 0x1000000, -0x1FDE9, 0x3C0000, -0x1FDEC, 0x40000000, -0xFEF8,
    -0xFDF5, 0, -0x1FEF0, -0x1FF00,
};
int data_800B3834[1] = {
    0,
};
int data_800B3838[11] = {
    MAP_REF(data_800B22C4), 0x26, 0, 0, 0, MAP_REF(unknown_800B37CC), 4, MAP_REF(data_800B3834),
    0, 0x800000, 0,
};
int data_800B3864[48] = {
    0, 0x4E0000, 0x10001, 0xB0001, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x1060002, 0xB0006, 0x2070003, 0xB0007,
    0x3080004, 0xB0008, 0x4090005, 0xB0009, 0x10A0002, 0xB000A, 0x20B0003, 0xB000B,
    0x30C0004, 0xB000C, 0x40D0005, 0xB000D, 0x10E0002, 0xB000E, 0x20F0003, 0xB000F,
    0x3100004, 0xB0010, 0x4110005, 0xB0011, 0x2120003, 0xB0012, 0x3130004, 0xB0013,
    0x4140005, 0xB0014, 0x1150002, 0xB0015, 0x1160002, 0xB0016, -1, -1,
};
int data_800B3924[12] = {
    -0x1FEF1, -0xFDF9, 0x1000000, -0x1FDE9, 0x3C0000, -0x1FDEC, 0x40000000, -0xFEF8,
    -0xFDF5, 0, -0x1FEF0, -0x1FF00,
};
int data_800B3954[12] = {
    -0x1FDF4, 0x150000, -0x1FEF3, -0x1FEF1, -0xFEFD, -0xFDFF, 0x150000, -0x1FEEB,
    -0x1FDE9, 0x3C0000, -0x1FEF0, -0x1FF00,
};
int data_800B3984[19] = {
    -0x1FDF4, 0x1A0000, -0x1FEF3, -0x1FEF1, -0xFDF9, 0x1000000, -0xFEFD, -0xFDFF,
    0x1A0000, -0x1FDEC, 0x40000000, -0xFEF8, -0xFDF5, 0, -0x1FEF0, -0x1FEEF,
    -0xFDF2, 0x1A0000, -0x1FF00,
};
int data_800B39D0[19] = {
    -0x1FDF4, 0x1B0000, -0x1FEF3, -0x1FEF1, -0xFDF5, 0x10000, -0xFDFA, 0x1000000,
    -0xFDFF, 0x1B0000, -0x1FDEC, 0x40000000, -0xFEF8, -0x1FEF0, -0xFDFF, 0x40000,
    -0xFDF2, 0x1B0000, -0x1FF00,
};
int data_800B3A1C[32] = {
    -0x7FF868AC, -0x7FF868A0, -0x7FF86890, -0x7FF86858, -0x7FF86820, -0x7FF867E8, -0x7FF867B0, -0x7FF86778,
    -0x7FF86740, -0x7FF86708, -0x7FF866AC, -0x7FF86674, -0x7FF8663C, -0x7FF86604, -0x7FF865D0, -0x7FF865B8,
    MAP_REF(data_800B3954), MAP_REF(data_800B3984), MAP_REF(data_800B39D0), -0x7FF864B4, -0x7FF864A0, -0x7FF8648C, -0x7FF86474, -0x7FF86450,
    0, 0, 0, 0, 0, 0, 0, 0,
};
int data_800B3A9C[11] = {
    MAP_REF(data_800B22D0), 2, MAP_REF(data_800B3864), 0, 0, 0, 4, MAP_REF(data_800B3A1C),
    0, 0x800000, 0,
};
int data_800B3AC8[82] = {
    0, 0x4E0000, 0x10001, 0xB0001, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x5060006, 0xB0006, 0x5070006, 0xB0007,
    0x5080006, 0xB0008, 0x2090003, 0xB0009, 0x30A0004, 0xB000A, 0x40B0005, 0xB000B,
    0x50C0006, 0xB000C, 0x50D0006, 0xB000D, 0x50E0006, 0xB000E, 0x20F0003, 0xB000F,
    0x3100004, 0xB0010, 0x4110005, 0xB0011, 0x2120003, 0x1B0012, 0x2130003, 0x1B0013,
    0x1140002, 0xB0014, 0x2150003, 0xB0015, 0x3160004, 0xB0016, 0x4170005, 0xB0017,
    0x5180006, 0xB0018, 0x6190007, 0xB0019, 0x61A0007, 0xB001A, 0x61B0007, 0xB001B,
    0x31C0004, 0xB001C, 0x41D0005, 0xB001D, 0x51E0006, 0xB001E, 0x61F0007, 0xB001F,
    0x6200007, 0xB0020, 0x6210007, 0xB0021, 0x3220004, 0xB0022, 0x4230005, 0xB0023,
    0x5240006, 0xB0024, 0x6250007, 0xB0025, 0x7260008, 0xB0026, 0x8270009, 0xB0027,
    -1, -1,
};
int data_800B3C10[32] = {
    -0x7FF868AC, -0x7FF868A0, -0x7FF86890, -0x7FF86858, -0x7FF86820, -0x7FF867E8, -0x7FF867B0, -0x7FF86778,
    -0x7FF86740, -0x7FF86708, -0x7FF866AC, -0x7FF86674, -0x7FF8663C, -0x7FF86604, -0x7FF865D0, -0x7FF865B8,
    -0x7FF86594, -0x7FF8652C, -0x7FF864F0, -0x7FF864B4, -0x7FF864A0, -0x7FF8648C, -0x7FF86474, -0x7FF86450,
    0, 0, 0, 0, 0, 0, 0, 0,
};
int data_800B3C90[11] = {
    MAP_REF(data_800B22E4), 3, MAP_REF(data_800B3AC8), 0, 0, 0, 4, MAP_REF(data_800B3C10),
    0, 0x800000, 0,
};
int data_800B3CBC[46] = {
    0xF0000, 0x2D0104, 0x60001, 0x170107, 0x130101, 0x2A0107, 0x30201, 0x190108,
    0x150301, 0x1D0108, 0x1A0401, 0x130108, 0xC0501, 0x27010A, 0x601, 0x1E010B,
    0x170701, 0x21010C, 0x1F0801, 0x22010C, 0x120002, 0x25016B, 0xE0003, 0x12016C,
    0x1B0103, 0x20016C, 0x160203, 0x30016E, 0x80303, 0x18016F, 0xB0004, 0x28010D,
    0x40104, 0x12010E, 0x1B0204, 0x25010E, 0xE0304, 0x18010F, 0x120404, 0x1A010F,
    0xC0006, 0x180170, 0xD0106, 0x160170, -0x10000, 0,
};
int data_800B3D74[6] = {
    -0x331, 0, 0x16D3, 0x4000, 0x50000, 0x60001,
};
int data_800B3D8C[6] = {
    0xB3B, 0, 0xABE, 0x4000, 0x50001, 0x50001,
};
int data_800B3DA4[6] = {
    -0x371, 0, 0x70, 0x4000, 0x50002, 0x80001,
};
int data_800B3DBC[6] = {
    0x164, 0, -0x22, 0x4000, 0x50003, 0x90001,
};
int data_800B3DD4[66] = {
    0x980001, -0x70, -0x3E8, -0x25, 0, 0, 0xF0, 0,
    -0x10000, 0, 0, 0x990001, -0x70, -0x3E8, -0x25, 0,
    0, 0x4F00A1, 0, -0x10000, 0, 0, 0x9A0001, -0x70,
    -0x3E8, -0x25, 0, 0, 0x95001F, 0, -0x10000, 0,
    0, 0x9B0001, -0x70, -0x3E8, -0x25, 0, 0, 0xB3001F,
    0, -0x10000, 0, 0, 0x9C0001, -0x70, -0x3E8, -0x25,
    0, 0, 0xD1001F, 0, -0x10000, 0, 0, 5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};
int data_800B3EDC[44] = {
    0x9E0001, 0, 0, 0, 0, 0, 0xEB, 0,
    -0x10000, 0, 0, 0x9F0001, 0, 0, 0, 0,
    0, 0xEB001E, 0, -0x10000, 0, 0, 0x1610000, 0,
    0, 0, 0, 0, 0xEB, 0, -0x10000, 0x30,
    0, 5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};
int data_800B3F8C[4] = {
    0xA2, -0x3B6, -0x1F4, -0x11C,
};
int data_800B3F9C[18] = {
    0, 1, 0, 1, 0, 0, 1, 2,
    5, 0x2E, 0x38000000, 0xB, 0x2D, 0x38000000, 0xB, 0xD3,
    0, 0,
};
int data_800B3FE4[176] = {
    0x4D, 0, 0, MAP_REF(FreeEventData_800B2E78), 0x45, 0, 1, 0,
    0x65, 0, 0, MAP_REF(data_800B3F9C), 0x66, 0, 0, 0,
    0xA, 0, 0x10, 0, 0xA, 0, 0x20, 0,
    9, 0, 0x10, 0, 0x1A, 2, 1, 0,
    0x48, 1, 0x26, 5, 0x46, 1, 0, MAP_REF(data_800B3924),
    0xD, 0, 2, 0, 0x67, 3, 0x1E, 0,
    0x67, 6, 0, 0, 8, 0, 7, 0,
    4, 0, 0, 0, 0x4C, 2, 1, 0,
    0x4D, 0, 0, MAP_REF(SetEvents_800B2DF4), 0xA, 0, 0xFF, 0,
    9, 0, 0x20, 0, 0x1A, 2, 1, 0,
    0x48, 0, 0x103, 5, 0x48, 1, 0x25, 1,
    0x67, 2, 0x1E, 0, 0x67, 6, 0, 0,
    0x38, 1, 0, 3, 0x42, 0, 0, 0,
    0x49, 1, 0x220025, 1, 0x42, 0, 1, 0,
    0x49, 1, 0x230025, 1, 0x42, 0, 2, 0,
    0x49, 1, 0x240025, 1, 0x42, 0, 3, 0,
    0x49, 1, 0x220025, 1, 0x3F, 0, 0, 0,
    0xE, 1, 0xC0000, 0, 0x67, 5, 0x1E, 0,
    0x67, 6, 0, 0, 0x4C, 3, 0, 0,
    0x4D, 0, 0, MAP_REF(SetEvents_800B2DF4), 8, 0, 7, 0,
    4, 0, 0, 0, 0x4D, 0, 0, MAP_REF(WarpLostBattle_800B2E58),
    9, 0, 0xFF, 0, 3, 0, 0, 0,
};
int data_800B42A4[212] = {
    0x4D, 0, 0, MAP_REF(OnMesh2_800B2E40), 5, 0, 0, 0,
    7, 0, 3, 0, 0x13, 0, 0, MAP_REF(data_800B3F8C),
    0xE, 1, 0xC0003, 0, 0x67, 0x11, 1, 0,
    0x67, 0xC, 0xFF04, 0x26, 0xC, 0, 1, 0,
    0x67, 0x11, 0, 0, 0x38, 1, 0, 0,
    0x42, 0, 0, 0, 0x49, 0, 0xFE0101, 1,
    0x3F, 0, 0, 0, 0x49, 0, 0x1780179, 1,
    0xD, 0, 2, 0, 0x46, 1, 0, MAP_REF(data_800B37D4),
    0xD, 0, 2, 0, 0xD, 0, 1, 0,
    0x38, 1, 0, 1, 0x42, 0, 0, 0,
    0x49, 1, 0x23002B, 1, 0x42, 0, 1, 0,
    0x49, 1, 0x24002B, 1, 0x42, 0, 2, 0,
    0x49, 1, 0x25002B, 1, 0x42, 0, 3, 0,
    0x49, 1, 0x26002B, 1, 0x42, 0, 4, 0,
    0x49, 1, 0x27002B, 1, 0x42, 0, 5, 0,
    0x49, 1, 0x26002B, 1, 0x42, 0, 6, 0,
    0x49, 1, 0x24002B, 1, 0x42, 0, 7, 0,
    0x49, 1, 0x25002B, 1, 0x42, 0, 8, 0,
    0x49, 1, 0x28002C, 1, 0x3F, 0, 0, 0,
    0x68, 1, 0x1E, 0, 0x67, 0xC, 6, 0,
    0x4B, 0, 0, MAP_REF(data_800B3DD4), 0x4D, 0, 0, MAP_REF(AddEffects_800B2760),
    0xC, 0, 0xD1, 0, 0x67, 0xD, 0x4E, 0,
    0x67, 5, 0x1F, 0, 0x67, 6, 0, 0,
    0x67, 0xC, 0xFF03, 6, 0x68, 0, 0, 0,
    8, 0, 3, 0, 4, 0, 0, 0,
    0x4C, 1, 1, 0, 0x4D, 0, 0, MAP_REF(SetEvents_800B2DF4),
    3, 0, 0, 0,
};
int data_800B45F4[56] = {
    5, 0, 0, 0, 7, 0, 7, 0,
    0x67, 5, 1, 0, 0x48, 0, 0x179, 5,
    0x19, 1, 0, 0x25, 0xD, 0, 3, 0,
    0x67, 4, 0x1E, 0, 0x67, 6, 0, 0,
    0x38, 1, 0, 2, 0x42, 0, 0, 0,
    0x49, 1, 0x220025, 1, 0x3F, 0, 0, 0,
    0xB, 0, 0, MAP_REF(data_800B3FE4), 3, 0, 0, 0,
};
int data_800B46D4[136] = {
    0x1A, 2, 1, 0, 5, 0, 0, 0,
    7, 0, 3, 0, 0x48, 1, 0x2D, 5,
    0x49, 0, 0x1780179, 5, 0x67, 2, 0x1E, 0,
    0x67, 6, 0, 0, 0x38, 1, 0, 4,
    0x42, 0, 0, 0, 0x49, 1, 0x29002D, 1,
    0x42, 0, 1, 0, 0x42, 0, 2, 0,
    0x49, 1, 0x2A002D, 1, 0x42, 0, 3, 0,
    0x42, 0, 4, 0, 0x49, 1, 0x29002D, 1,
    0x3F, 0, 0, 0, 0x46, 1, 0, MAP_REF(data_800B3804),
    0x4B, 0, 0, MAP_REF(data_800B3EDC), 0x4D, 0, 0, MAP_REF(AddEffects_800B2760),
    0xC, 0, 0x7A, 0, 0x67, 0xD, 0x1E, 0,
    0xC, 0, 0x71, 0, 0x49, 0, 0x17A0179, 1,
    0x3E, 0xE, 1, 5, 0x67, 0xC, 0xFF00, 0,
    0x67, 3, 0x1E, 0, 0x67, 6, 0, 0,
    8, 0, 3, 0, 4, 0, 0, 0,
    0x4C, 0, 0, 0, 0x4D, 0, 0, MAP_REF(SetEvents_800B2DF4),
    0x53, 0, 0xCC, 0, 3, 0, 0, 0,
};
int data_800B48F4[76] = {
    0x4D, 0, 0, MAP_REF(OnMesh2_800B2E40), 5, 0, 0, 0,
    7, 0, 7, 0, 0x13, 0, 0, MAP_REF(data_800B3F8C),
    0xE, 1, 0xC0003, 0, 0x67, 0x11, 1, 0,
    0x67, 0xC, 0xFF04, 0x26, 0xC, 0, 1, 0,
    0x67, 0x11, 0, 0, 0x48, 0, 0x101, 5,
    0x38, 1, 0, 6, 0x42, 0, 0, 0,
    0x49, 1, 0x220025, 1, 0x42, 0, 1, 0,
    0x49, 0, 0x1780179, 1, 0x49, 1, 0x230025, 1,
    0x3F, 0, 0, 0, 0xB, 0, 0, MAP_REF(data_800B3FE4),
    3, 0, 0, 0,
};
int data_800B4A24[9] = {
    MAP_REF(data_800B3838), 0, -0x70, -0x3E8, -0x25, 0x671, 0x2B, 2,
    3,
};
int data_800B4A48[9] = {
    MAP_REF(data_800B3A9C), 0, -0x4B, -0x3E8, -0x25, 0x671, 0x25, 0,
    2,
};
int data_800B4A6C[9] = {
    MAP_REF(data_800B3C90), 0, -0x4B, -0x3E8, -0x25, 0x671, 1, -1,
    3,
};
MapEvent data_800B4A90[8] = {
    { -1, 0xF, data_800B4A24, 0x14, { (void*)MinionInit_800B2428 } },
    { -1, 8, data_800B42A4, 0, { 0 } },
    { -1, 1, data_800B3D74, 0, { (void*)Warp_800B2304 } },
    { -1, 1, data_800B3D8C, 0, { (void*)Warp_800B2304 } },
    { -1, 1, data_800B3DA4, 0, { (void*)Warp_800B2304 } },
    { -1, 1, data_800B3DBC, 0, { (void*)Warp_800B2304 } },
    { -1, 0xB, data_800B3CBC, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
MapEvent data_800B4B30[5] = {
    { -1, 0xF, data_800B4A48, 0x14, { (void*)MinionInit_800B2428 } },
    { -1, 0xF, data_800B4A6C, 0x14, { (void*)MinionInit_800B2428 } },
    { -1, 8, data_800B45F4, 0, { 0 } },
    { -1, 0xB, data_800B3CBC, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
MapEvent data_800B4B94[4] = {
    { -1, 0xF, data_800B4A24, 0x14, { (void*)MinionInit_800B2428 } },
    { -1, 8, data_800B46D4, 0, { 0 } },
    { -1, 0xB, data_800B3CBC, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
MapEvent data_800B4BE4[9] = {
    { -1, 0xF, data_800B4A48, 0x14, { (void*)MinionInit_800B2428 } },
    { -1, 0xF, data_800B4A6C, 0x14, { (void*)MinionInit_800B2428 } },
    { -1, 8, data_800B48F4, 0, { 0 } },
    { -1, 1, data_800B3D74, 0, { (void*)Warp_800B2304 } },
    { -1, 1, data_800B3D8C, 0, { (void*)Warp_800B2304 } },
    { -1, 1, data_800B3DA4, 0, { (void*)Warp_800B2304 } },
    { -1, 1, data_800B3DBC, 0, { (void*)Warp_800B2304 } },
    { -1, 0xB, data_800B3CBC, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
short bones_800B4C98[92] = {
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
int scale_800B4D50[3] = {
    0x1000, 0x1000, 0x1000,
};
MapEvent* eventSets_800B4D5C[4] = { data_800B4A90, data_800B4B30, data_800B4B94, data_800B4BE4 };
MapEvent* curEvents_800B4D6C = 0;
const int unknown_800B22C0[1] = {
    0x102,
};
const char data_800B22C4[12] = "\x82j\x82\x8f\x82\x92\x82\x89\x82\x93";
const char data_800B22D0[20] = "\x82""e\x82\x89\x82\x92\x82\x85\x81@\x82""a\x82\x8f\x82\x93\x82\x93";
const char data_800B22E4[12] = "\x82""a\x82r\x82""e\x82r";
const MapFxInits fxInits_800B22F0 = { { FxSprite_800B28EC, FxModel_800B2A60, 0, 0, 0 } };
