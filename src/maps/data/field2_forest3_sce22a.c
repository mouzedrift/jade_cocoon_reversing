#include "maps/map.h"

int DrawPicture_800B2334(void);
int AddEffects_800B2444(MapFx* fx);
void FxSprite_800B25D0(MapEnt* ent);
void FxModel_800B2744(MapEnt* ent);
void MinionInit_800B296C(MapEnt* ent);
void MapInit_800B2CA4(int phase);
void FxInit_800B2DA4(MapEnt* ent);
void MinionIdle_800B2E5C(MapEnt* ent);
int PlayMovie_800B2E64(MapMovieArgs* args);
int LoadPicture_800B2EDC(void);
int SetEvents_800B2F58(MapExitArgs* args);
int WarpLostBattle_800B2FAC(void);
int FreeEventData_800B2FCC(void);
int SaveEndOfGame_800B2FEC(void);
void SfxLoopInit_800B3018(MapEnt* ent);
void SfxLoop_800B304C(MapEnt* ent);
void StartMapTask_800B309C(void);
void MapTaskLoad_800B30CC(EventEntry* entry, int* st);
void MapTask_800B3164(EventEntry* entry, int* st);
int LeaveArea_800B3218(MapEvent* ev, int area);
int EnterArea_800B3334(MapEvent* ev, int area, int prev);
void RequestModels_800B343C(MapEvent* ev);
void EntityTask_800B350C(EventEntry* entry, MapEnt* ent);
int AddEntity_800B358C(void* ev);
void MapInitOld_800B36B8(int phase);
int FxFrame_800B3728(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B37AC(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B3878(MapFx* fx, MapFxWork* w);
int MinionF_800B39C0(void);
int MinionF_800B39C8(void);

extern const int unknown_800B22C0[1];
extern const char data_800B22C4[24];
extern const char data_800B22DC[12];
extern const char data_800B22E8[16];
extern const MapFxInits fxInits_800B22F8;
extern int unknown_800B39D0[50];
extern int data_800B3A98[3];
extern int data_800B3AA4[48];
extern int data_800B3B64[14];
extern int data_800B3B9C[14];
extern int data_800B3BD4[19];
extern int data_800B3C20[19];
extern int data_800B3C6C[12];
extern int data_800B3C9C[12];
extern int data_800B3CCC[12];
extern int data_800B3CFC[34];
extern int data_800B3D84[3];
extern int data_800B3D90[11];
extern int data_800B3DBC[72];
extern int data_800B3EDC[32];
extern int data_800B3F5C[11];
extern int data_800B3F88[48];
extern int data_800B4048[1];
extern int data_800B404C[3];
extern int data_800B4058[11];
extern int data_800B4084[46];
extern int data_800B413C[44];
extern int data_800B41EC[44];
extern int data_800B429C[22];
extern int data_800B42F4[18];
extern int data_800B433C[4];
extern int data_800B434C[4];
extern int data_800B435C[4];
extern int data_800B436C[4];
extern int data_800B437C[3];
extern int data_800B4388[3];
extern int data_800B4394[5];
extern int data_800B43A8[340];
extern int data_800B48F8[152];
extern int data_800B4B58[184];
extern int data_800B4E38[92];
extern int data_800B4FA8[9];
extern int data_800B4FCC[9];
extern int data_800B4FF0[9];
extern MapEvent data_800B5014[5];
extern MapEvent data_800B5078[5];
extern MapEvent data_800B50DC[4];
extern short bones_800B512C[92];
extern int scale_800B51E4[3];
extern SPRT* sprts_800B51F0;
extern DR_TPAGE* tpages_800B51F4;
extern MapEvent* curEvents_800B51F8;

int unknown_800B39D0[50] = {
    0, 0x460000, 0x10001, 1, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x2060003, 0xB0006, 0x3070004, 0xB0007,
    0x4080005, 0xB0008, 0x2090003, 9, 0x30A0004, 0xB000A, 0x2120003, 0xB0012,
    0x2130003, 0xB0013, 0x2140003, 0xB0014, 0x2150003, 0xB0015, 0x2160003, 0xB0016,
    0x3170004, 0xB0017, 0x10B0002, 0xB000B, 0x20C0003, 0xB000C, 0x30D0004, 0xB000D,
    0x40E0005, 0xB000E, 0x20F0003, 0xB000F, 0x3100004, 0xB0010, 0x4110005, 0xB0011,
    -1, -1,
};
int data_800B3A98[3] = {
    0x1000, 0x1000, 0x1000,
};
int data_800B3AA4[48] = {
    0x10001000, 0x11000, 0x10001000, 0x11000, 0x10001000, 0x11000, 0x10001000, 0x11000,
    0x10001000, 0x11000, 0x10001000, 0x11000, 0x10001000, 0x11000, 0x10001000, 0x11000,
    0x10001000, 0x11000, 0x10001000, 0x11000, 0x10001000, 0x11000, 0x10001000, 0x11000,
    0x10001000, 0x11000, 0x10001000, 0x11000, 0x10001000, 0x11000, 0x10001000, 0x11000,
    0x10001000, 0x11000, 0x10001000, 0x11000, 0x10001000, 0x11000, 0x10001000, 0x11000,
    0x10001000, 0x11000, 0x10001000, 0x11000, 0x10001000, 0x11000, 0x10001000, 0x11000,
};
int data_800B3B64[14] = {
    -0x1FEF1, -0xFDF5, 0x10000, -0xFDFA, 0x1000000, -0xFDFF, 0x280000, -0x1FDE9,
    0x5A0000, -0x1FDEC, 0x40000000, -0xFEF8, -0x1FEF0, -0x1FF00,
};
int data_800B3B9C[14] = {
    -0x1FEF1, -0xFDF5, 0x10000, -0xFDFA, 0x1000000, -0xFDFF, 0x290000, -0x1FDE9,
    0x5A0000, -0x1FDEC, 0x40000000, -0xFEF8, -0x1FEF0, -0x1FF00,
};
int data_800B3BD4[19] = {
    -0x1FDF4, 0x1A0000, -0x1FEF3, -0x1FEF1, -0xFDF9, 0x1000000, -0xFEFD, -0xFDFF,
    0x1A0000, -0x1FDEC, 0x40000000, -0xFEF8, -0xFDF5, 0, -0x1FEF0, -0x1FEEF,
    -0xFDF2, 0x1A0000, -0x1FF00,
};
int data_800B3C20[19] = {
    -0x1FDF4, 0x1B0000, -0x1FEF3, -0x1FEF1, -0xFDF5, 0x10000, -0xFDFA, 0x1000000,
    -0xFDFF, 0x1B0000, -0x1FDEC, 0x40000000, -0xFEF8, -0x1FEF0, -0xFDFF, 0x40000,
    -0xFDF2, 0x1B0000, -0x1FF00,
};
int data_800B3C6C[12] = {
    -0x1FEF1, -0xFDF5, 0x10000, -0xFDFA, 0x1000000, -0xFDFF, 0x10000, -0x1FDEC,
    0x40000000, -0xFEF8, -0x1FEF0, -0x1FF00,
};
int data_800B3C9C[12] = {
    -0x1FEF1, -0xFDF9, 0x1000000, -0xFDFF, 0x10000, -0x1FDEC, 0x40000000, -0xFEF8,
    -0xFDF5, 0, -0x1FEF0, -0x1FF00,
};
int data_800B3CCC[12] = {
    -0x1FDF4, 0x150000, -0x1FEF3, -0x1FEF1, -0xFEFD, -0xFDFF, 0x150000, -0x1FEEB,
    -0x1FDE9, 0x3C0000, -0x1FEF0, -0x1FF00,
};
int data_800B3CFC[34] = {
    -0x7FF868AC, -0x7FF868A0, -0x7FF86890, -0x7FF86858, -0x7FF86820, -0x7FF867E8, -0x7FF867B0, -0x7FF86778,
    -0x7FF86740, -0x7FF86708, -0x7FF866AC, -0x7FF86674, -0x7FF8663C, -0x7FF86604, -0x7FF865D0, -0x7FF865B8,
    MAP_REF(data_800B3CCC), MAP_REF(data_800B3BD4), MAP_REF(data_800B3C20), -0x7FF864B4, -0x7FF864A0, -0x7FF8648C, -0x7FF86474, -0x7FF86450,
    0, 0, 0, 0, 0, 0, 0, 0,
    MAP_REF(data_800B3C6C), MAP_REF(data_800B3C9C),
};
int data_800B3D84[3] = {
    8, 0x17, -1,
};
int data_800B3D90[11] = {
    MAP_REF(data_800B22C4), 0x63, MAP_REF(unknown_800B39D0), MAP_REF(data_800B3A98), MAP_REF(data_800B3AA4), MAP_REF(data_800B3D84), 4, MAP_REF(data_800B3CFC),
    0, 0x800000, 0x10000,
};
int data_800B3DBC[72] = {
    0, 0x4E0000, 0x10001, 1, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x5060006, 0xB0006, 0x6090007, 0xB0009,
    0x5070006, 0xB0007, 0x60A0007, 0xB000A, 0x5080006, 0xB0008, 0x60B0007, 0xB000B,
    0x20C0003, 0xB000C, 0x30D0004, 0xB000D, 0x40E0005, 0xB000E, 0x50F0006, 0xB000F,
    0x6120007, 0xB0012, 0x5100006, 0xB0010, 0x6130007, 0xB0013, 0x5110006, 0xB0011,
    0x6140007, 0xB0014, 0x2150003, 0xB0015, 0x2160003, 0xB0016, 0x3170004, 0xB0017,
    0x2180003, 0xB0018, 0x3190004, 0xB0019, 0x11A0002, 0xB001A, 0x21B0003, 0xB001B,
    0x31C0004, 0xB001C, 0x41D0005, 0xB001D, 0x51E0006, 0xB001E, 0x21F0003, 0xB001F,
    0x3200004, 0xB0020, 0x4210005, 0xB0021, 0x5220006, 0xB0022, -1, -1,
};
int data_800B3EDC[32] = {
    -0x7FF868AC, -0x7FF868A0, -0x7FF86890, -0x7FF86858, -0x7FF86820, -0x7FF867E8, -0x7FF867B0, -0x7FF86778,
    -0x7FF86740, -0x7FF86708, -0x7FF866AC, -0x7FF86674, -0x7FF8663C, -0x7FF86604, -0x7FF865D0, -0x7FF865B8,
    -0x7FF86594, -0x7FF8652C, -0x7FF864F0, -0x7FF864B4, -0x7FF864A0, -0x7FF8648C, -0x7FF86474, -0x7FF86450,
    0, 0, 0, 0, 0, 0, 0, 0,
};
int data_800B3F5C[11] = {
    MAP_REF(data_800B22DC), 8, MAP_REF(data_800B3DBC), 0, 0, 0, 4, MAP_REF(data_800B3EDC),
    0, 0x800000, 0,
};
int data_800B3F88[48] = {
    0, 0x460000, 0x10001, 1, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x5060005, 0xB0006, 0x6070006, 0xB0007,
    0x2080003, 0xB0008, 0x8090004, 0xB0009, 0x90A0005, 0xB000A, 0xA0B0005, 0xB000B,
    0xB0C0006, 0xB000C, 0x20D0003, 0xD, 0xD0E0004, 0xB000E, 0x10F0002, 0xB000F,
    0xF100003, 0xB0010, 0x10110004, 0xB0011, 0x11120005, 0xB0012, 0xF130003, 0xB0013,
    0x13140004, 0xB0014, 0x14150005, 0xB0015, 0x2160003, 0xB0016, -1, -1,
};
int data_800B4048[1] = {
    0,
};
int data_800B404C[3] = {
    0xC, 0x16, -1,
};
int data_800B4058[11] = {
    MAP_REF(data_800B22E8), 0x47, MAP_REF(data_800B3F88), 0, 0, MAP_REF(data_800B404C), 4, MAP_REF(data_800B4048),
    0, 0x800000, 0,
};
int data_800B4084[46] = {
    0x180000, 0x1603F9, 0x40100, 0x1E03FA, 0x1A0200, 0x1C03FA, 0xE0300, 0x1903FB,
    0x110400, 0x1E03FC, 1, 0x1A03FD, 0x1C0101, 0x1D0400, 0x130201, 0x240402,
    0x1B0002, 0xC0402, 0xA0102, 0xE0403, 0x140003, 0x140403, 0x90004, 0x180404,
    0x150104, 0x1D0404, 0x80005, 0x260405, 0x10105, 0x210408, 0x1E0205, 0x1A0408,
    0xD0006, 0x16040E, 0x1B0106, 0x12040E, 0x20007, 0x2C040F, 0x30008, 0x20040F,
    0x180108, 0x29040F, 0x1D0208, 0x1A040F, -0x10000, 0,
};
int data_800B413C[44] = {
    0xA60001, 0, 0, 0, 0, 0, 0x3C, 1,
    -0x10000, 0, 0, 0x1690000, 0, 0, 0, 0,
    0, 0x3C, 1, -0x10000, 0x38, 0, 0x16B0000, 0,
    0, 0, 0, 0, 0x1E, 4, -0x10000, 0x38,
    0, 5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};
int data_800B41EC[44] = {
    0xAA0001, 0, 0, 0, 0, 0, 0x3C, 0,
    -0x10000, 0, 0, 0x16C0000, 0, 0, 0, 0,
    0, 0x1E001E, 0, -0x10000, 0x38, 0, 0x16D0000, 0,
    0, 0, 0, 0, 0x3C, 0, -0x10000, 0x38,
    0, 5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};
int data_800B429C[22] = {
    0xC40001, 0, 0, 0, 0, 0, 1, 0xFFFF,
    -0x10000, 0, 0, 5, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};
int data_800B42F4[18] = {
    0, 1, 0, 1, 0, 0, 1, 2,
    5, 0x37, 0x58000000, 0xE, 0x38, 0x58000000, 0xE, 0xD3,
    0, 0,
};
int data_800B433C[4] = {
    0x8FC, 0, -0x21FC, 0,
};
int data_800B434C[4] = {
    0x8FC, 0, -0x21FC, -0x800,
};
int data_800B435C[4] = {
    0x947, 0, -0x251C, -0x58E,
};
int data_800B436C[4] = {
    0x960, 0, -0x21FC, 0,
};
int data_800B437C[3] = {
    0x8FC, -0x1B2, -0x2599,
};
int data_800B4388[3] = {
    0x8FC, -0x6C3, -0x2942,
};
int data_800B4394[5] = {
    -1, 0xD, 0, 4, MAP_REF(SfxLoopInit_800B3018),
};
int data_800B43A8[340] = {
    5, 0, 0, 0, 7, 0, 3, 0,
    0x5E, 0, 1, 0, 0x4B, 0, 0, MAP_REF(data_800B429C),
    0x4D, 0, 0, MAP_REF(AddEffects_800B2444), 0x13, 0, 0, MAP_REF(data_800B436C),
    0x1C, 1, 1, 0, 0x67, 1, 1, 0,
    0x48, 0, 0x16F, 5, 0x48, 1, 6, 5,
    0x2D, 0, 0xC, 0, 0x2D, 0, 0xD, 0,
    0x2D, 0, 0xE, 0, 0x2D, 0, 0xF, 0,
    0x55, 0, 8, 0, 0x67, 2, 0x1E, 0,
    0x67, 6, 0, 0, 0x38, 1, 0, 2,
    0x42, 0, 0, 0, 0x42, 0, 1, 0,
    0x49, 1, 7, 1, 0x3F, 0, 0, 0,
    0x49, 1, 0x10008, 1, 0xC, 0, 0x28, 0,
    0x56, 0, 8, 0, 0x55, 0, 9, 0,
    0xD, 0, 2, 0, 0x56, 0, 9, 0,
    0x55, 0, 0xA, 0, 0x38, 1, 0, 3,
    0x3F, 0, 0, 0, 0x56, 0, 0xA, 0,
    0x55, 0, 5, 0, 0x49, 0, 0x1660170, 1,
    0xC, 0, 0xB4, 0, 0x56, 0, 5, 0,
    0x55, 0, 6, 0, 0x38, 1, 0, 4,
    0x42, 0, 0, 0, 0x42, 0, 1, 0,
    0x49, 1, 0x20008, 1, 0x3F, 0, 0, 0,
    0x56, 0, 6, 0, 0x55, 0, 8, 0,
    0x38, 1, 0, 5, 0x3F, 0, 0, 0,
    0x56, 0, 8, 0, 0x55, 0, 0xA, 0,
    0x38, 1, 0, 6, 0x42, 0, 0, 0,
    0x49, 1, 0x30008, 1, 0x42, 0, 1, 0,
    0x49, 1, 0x40009, 1, 0x3F, 0, 0, 0,
    0x56, 0, 0xA, 0, 0x55, 0, 0xB, 0,
    0x49, 0, 0x1670171, 1, 0xC, 0, 0xB4, 0,
    0x56, 0, 0xB, 0, 0x60, 1, 0, 0,
    0x38, 1, 0, 7, 0x42, 0, 0, 0,
    0x49, 1, 0x5000A, 1, 0x3F, 0, 0, 0,
    0x5A, 0, 0x5A, MAP_REF(data_800B4388), 0x5D, 0, 1, 0,
    0x67, 3, 0x5A, 0, 0x67, 6, 0, 0,
    0x5C, 0, 1, 0, 0x67, 0xC, 0xFF00, 0,
    0xC, 0, 0x5A, 0, 0x4C, 0x17, 0, 0,
    0x4D, 0, 0, MAP_REF(PlayMovie_800B2E64), 0x4C, 0x18, 0, 0,
    0x4D, 0, 0, MAP_REF(PlayMovie_800B2E64), 8, 0, 3, 0,
    4, 0, 0, 0, 0x4D, 0, 0, MAP_REF(SaveEndOfGame_800B2FEC),
    0xC, 0, 2, 0, 5, 0, 0, 0,
    7, 0, 1, 0, 0x5E, 0, 0, 0,
    0x4D, 0, 0, MAP_REF(LoadPicture_800B2EDC), 0x4D, 0, 0, MAP_REF(DrawPicture_800B2334),
    3, 0, 0, 0,
};
int data_800B48F8[152] = {
    0x4D, 0, 0, MAP_REF(FreeEventData_800B2FCC), 0x67, 3, 0x1E, 0,
    0x67, 6, 0, 0, 0x45, 0, 1, 0,
    0x65, 0, 0, MAP_REF(data_800B42F4), 0x66, 0, 0, 0,
    0xA, 0, 0x10, 0, 0xA, 0, 0x20, 0,
    9, 0, 0x10, 0, 0x1C, 1, 0, 0,
    0x13, 0, 0, MAP_REF(data_800B436C), 0x13, 1, 0, MAP_REF(data_800B435C),
    0x1A, 2, 1, 0, 0x1C, 1, 1, 0,
    0x48, 1, 0x2B, 5, 0x67, 3, 0x1E, 0,
    0x67, 6, 0, 0, 0x4C, 2, 1, 0,
    0x4D, 0, 0, MAP_REF(SetEvents_800B2F58), 0xA, 0, 0xFF, 0,
    9, 0, 0x20, 0, 0x13, 0, 0, MAP_REF(data_800B434C),
    0x1A, 2, 1, 0, 0x48, 0, 0x177, 5,
    0x48, 1, 0x29, 5, 0x67, 2, 0x1E, 0,
    0x67, 6, 0, 0, 0x38, 1, 0, 1,
    0x3F, 0, 0, 0, 0x67, 3, 0x1E, 0,
    0x67, 6, 0, 0, 8, 0, 7, 0,
    4, 0, 0, 0, 0x4C, 1, 0, 0,
    0x4D, 0, 0, MAP_REF(SetEvents_800B2F58), 0x4D, 0, 0, MAP_REF(WarpLostBattle_800B2FAC),
    9, 0, 0xFF, 0, 3, 0, 0, 0,
};
int data_800B4B58[184] = {
    5, 0, 0, 0, 7, 0, 7, 0,
    0x5E, 0, 1, 0, 0x67, 1, 0, 0,
    0x13, 0, 0, MAP_REF(data_800B433C), 0x1C, 1, 1, 0,
    0x48, 0, 0x16D, 5, 0x1A, 2, 0, 0,
    0x11, 0, 0, MAP_REF(data_800B4394), 0x55, 0, 7, 0,
    0x4B, 0, 0, MAP_REF(data_800B413C), 0x4D, 0, 0, MAP_REF(AddEffects_800B2444),
    0x67, 2, 0x1E, 0, 0xC, 0, 0x5A, 0,
    0x46, 1, 0, MAP_REF(data_800B3B64), 0xC, 0, 0x1E, 0,
    0x2E, 0, -2, MAP_REF(data_800B4394), 0x4B, 0, 0, MAP_REF(data_800B41EC),
    0x4D, 0, 0, MAP_REF(AddEffects_800B2444), 0xC, 0, 0x96, 0,
    0x56, 0, 7, 0, 0x55, 0, 5, 0,
    0x49, 1, 0x260029, 1, 0xC, 0, 0xB4, 0,
    0x56, 0, 5, 0, 0x55, 0, 8, 0,
    0x49, 0, 0x165016E, 1, 0xC, 0, 0x96, 0,
    0x56, 0, 8, 0, 0x55, 0, 5, 0,
    0x5A, 0, 1, MAP_REF(data_800B437C), 0x38, 1, 0, 0,
    0x42, 0, 0, 0, 0x5F, 0x3000, 0x96, 0,
    0x42, 0, 1, 0, 0x42, 0, 2, 0,
    0x42, 0, 3, 0, 0x42, 0, 4, 0,
    0x5F, 0x1000, 0xA, 0, 0x49, 1, 0x27002A, 1,
    0x3F, 0, 0, 0, 0x5B, 0, 1, 0,
    0x5C, 0, 1, 0, 0x56, 0, 5, 0,
    0xB, 0, 0, MAP_REF(data_800B48F8), 3, 0, 0, 0,
};
int data_800B4E38[92] = {
    5, 0, 0, 0, 7, 0, 7, 0,
    0x5E, 0, 1, 0, 0x67, 1, 0, 0,
    0x13, 0, 0, MAP_REF(data_800B434C), 0x1A, 2, 0, 0,
    0x1C, 1, 1, 0, 0x48, 0, 0x175, 5,
    0x48, 1, 0x29, 5, 0x55, 0, 5, 0,
    0x67, 2, 0x1E, 0, 0x67, 6, 0, 0,
    0x46, 1, 0, MAP_REF(data_800B3B9C), 0xD, 0, 2, 0,
    0x38, 1, 0, 8, 0x42, 0, 0, 0,
    0x42, 0, 1, 0, 0x42, 0, 2, 0,
    0x49, 0, 0x1780179, 1, 0x3F, 0, 0, 0,
    0x56, 0, 5, 0, 0xB, 0, 0, MAP_REF(data_800B48F8),
    3, 0, 0, 0,
};
int data_800B4FA8[9] = {
    MAP_REF(data_800B3D90), 0, 0x8FC, 0, -0x2599, 0, 0x28, 1,
    2,
};
int data_800B4FCC[9] = {
    MAP_REF(data_800B3F5C), 0, 0x8FC, 0, -0x2599, 0, 1, -1,
    3,
};
int data_800B4FF0[9] = {
    MAP_REF(data_800B4058), 0, 0x947, 0, -0x251C, -0x638, 6, 0,
    2,
};
MapEvent data_800B5014[5] = {
    { -1, 0xF, data_800B4FA8, 0x14, { (void*)MinionInit_800B296C } },
    { -1, 0xF, data_800B4FCC, 0x14, { (void*)MinionInit_800B296C } },
    { -1, 8, data_800B4B58, 0, { 0 } },
    { -1, 0xB, data_800B4084, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
MapEvent data_800B5078[5] = {
    { -1, 0xF, data_800B4FA8, 0x14, { (void*)MinionInit_800B296C } },
    { -1, 0xF, data_800B4FCC, 0x14, { (void*)MinionInit_800B296C } },
    { -1, 8, data_800B4E38, 0, { 0 } },
    { -1, 0xB, data_800B4084, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
MapEvent data_800B50DC[4] = {
    { -1, 0xF, data_800B4FF0, 0x14, { (void*)MinionInit_800B296C } },
    { -1, 8, data_800B43A8, 0, { 0 } },
    { -1, 0xB, data_800B4084, 0, { 0 } },
    { 0, 0x12, 0, 0, { 0 } },
};
short bones_800B512C[92] = {
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
int scale_800B51E4[3] = {
    0x1000, 0x1000, 0x1000,
};
SPRT* sprts_800B51F0 = 0;
DR_TPAGE* tpages_800B51F4 = 0;
MapEvent* curEvents_800B51F8 = 0;
const int unknown_800B22C0[1] = {
    0x130,
};
const char data_800B22C4[24] = "\x82""b\x82\x88\x82\x8f\x82\x93\x82\x85\x82\x8e\x81@\x82n\x82\x8e\x82\x85";
const char data_800B22DC[12] = "\x82""a\x82r\x82y\x82y";
const char data_800B22E8[16] = "\x82q\x82\x89\x82\x8b\x82\x85\x82\x94\x82\x9a";
const MapFxInits fxInits_800B22F8 = { { FxSprite_800B25D0, FxModel_800B2744, 0, 0, 0 } };
