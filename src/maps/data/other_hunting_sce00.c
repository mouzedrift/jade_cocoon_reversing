#include "maps/map.h"

void Corridor_800B29FC(MapEnt* ent);
GameSpawnEntry* CorridorSpawns_800B2B40(void);
void CorridorNewFloor_800B2C6C(MapCorridorWork* w);
int CorridorGrow_800B2D98(MapCorridorWork* w, int door, MapCorridorRoom* parent, int budget, int deadEnds);
void CorridorSpecies_800B2FAC(MapCorridorWork* w);
void MapInit_800B3128(int phase);
int* CorridorEncounterSpecies_800B3198(void);
unsigned short* CorridorEncounterFlags_800B322C(void);
int* CorridorMagicBits_800B3260(int idx);
UnitSkills* CorridorSkills_800B3274(int idx);
int* CorridorSpeciesInt_800B3290(int idx);
MinionBaseStats* CorridorBaseStats_800B32A4(int idx);
const char* CorridorSpeciesName_800B32B8(int idx);
const char* CorridorNewSpeciesName_800B32D4(int idx);
unsigned char* CorridorModifiers_800B32F0(int idx);
int CorridorFloor_800B330C(void);
void CorridorInit_800B331C(MapEnt* ent);
void CorridorFloorStart_800B3394(MapCorridorWork* w);
void CorridorGo_800B33C0(MapCorridorWork* w, int exit);
int CorridorRoomKind_800B34A4(MapCorridorWork* w);
MapCorridorDoor* CorridorDoor_800B34B8(MapCorridorWork* w);
int CorridorDoorRot_800B351C(MapCorridorWork* w);
int CorridorPlaceExit_800B3584(MapCorridorWork* w, MapCorridorRoom* room, int n);
int CorridorRoomType_800B3714(int* budget);
void CorridorFreeFloor_800B37B0(MapCorridorWork* w);
void CorridorFreeRooms_800B37D8(MapCorridorRoom* start, MapCorridorRoom* room);
void CorridorUniqueModel_800B3870(int* species, int n);
void StartMapTask_800B3908(void);
void MapTaskLoad_800B3938(EventEntry* entry, int* st);
void MapTask_800B39D0(EventEntry* entry, int* st);
int LeaveArea_800B3A88(MapEvent* ev, int area);
int EnterArea_800B3BA4(MapEvent* ev, int area, int prev);
void RequestModels_800B3CAC(MapEvent* ev);
int AddEntity_800B3D7C(void* ev);
void EntityTask_800B3EA8(EventEntry* entry, MapEnt* ent);

extern const int unknown_800B22C0[1];
extern const char data_800B22C4[12];
extern const char data_800B22D0[12];
extern const char data_800B22DC[12];
extern const char data_800B22E8[12];
extern const char data_800B22F4[8];
extern const char data_800B22FC[12];
extern const char data_800B2308[16];
extern const char data_800B2318[12];
extern const char data_800B2324[12];
extern const char data_800B2330[8];
extern const char data_800B2338[12];
extern const char data_800B2344[16];
extern const char data_800B2354[12];
extern const char data_800B2360[12];
extern const char data_800B236C[16];
extern const char data_800B237C[12];
extern const char data_800B2388[8];
extern const char data_800B2390[12];
extern const char data_800B239C[16];
extern const char data_800B23AC[12];
extern const char data_800B23B8[8];
extern const char data_800B23C0[12];
extern const char data_800B23CC[12];
extern const char data_800B23D8[12];
extern const char data_800B23E4[16];
extern const char data_800B23F4[12];
extern const char data_800B2400[12];
extern const char data_800B240C[8];
extern const char data_800B2414[8];
extern const char data_800B241C[12];
extern const char data_800B2428[12];
extern const char data_800B2434[12];
extern const char data_800B2440[8];
extern const char data_800B2448[8];
extern const char data_800B2450[12];
extern const char data_800B245C[12];
extern const char data_800B2468[12];
extern const char data_800B2474[8];
extern const char data_800B247C[8];
extern const char data_800B2484[8];
extern const char data_800B248C[8];
extern const char data_800B2494[8];
extern const char data_800B249C[12];
extern const char data_800B24A8[12];
extern const char data_800B24B4[12];
extern const char data_800B24C0[12];
extern const char data_800B24CC[12];
extern const char data_800B24D8[8];
extern const char data_800B24E0[12];
extern const char data_800B24EC[8];
extern const char data_800B24F4[12];
extern const char data_800B2500[8];
extern const char data_800B2508[8];
extern const char data_800B2510[8];
extern const char data_800B2518[8];
extern const char data_800B2520[8];
extern const char data_800B2528[8];
extern const char data_800B2530[8];
extern const char data_800B2538[12];
extern const char data_800B2544[12];
extern const char data_800B2550[12];
extern const char data_800B255C[12];
extern const char data_800B2568[12];
extern const char data_800B2574[12];
extern const char data_800B2580[16];
extern const char data_800B2590[12];
extern const char data_800B259C[12];
extern const char data_800B25A8[12];
extern const char data_800B25B4[12];
extern const char data_800B25C0[12];
extern const char data_800B25CC[12];
extern const char data_800B25D8[12];
extern const char data_800B25E4[12];
extern const char data_800B25F0[12];
extern const char data_800B25FC[12];
extern const char data_800B2608[12];
extern const char data_800B2614[12];
extern const char data_800B2620[12];
extern const char data_800B262C[12];
extern const char data_800B2638[12];
extern const char data_800B2644[12];
extern const char data_800B2650[12];
extern const char data_800B265C[12];
extern const char data_800B2668[12];
extern const char data_800B2674[12];
extern const char data_800B2680[12];
extern const char data_800B268C[12];
extern const char data_800B2698[12];
extern const char data_800B26A4[16];
extern const char data_800B26B4[16];
extern const char data_800B26C4[16];
extern const char data_800B26D4[16];
extern const char data_800B26E4[12];
extern const char data_800B26F0[12];
extern const char data_800B26FC[12];
extern const char data_800B2708[12];
extern const char data_800B2714[12];
extern const char data_800B2720[12];
extern const char data_800B272C[12];
extern const char data_800B2738[12];
extern const char data_800B2744[16];
extern const char data_800B2754[16];
extern const char data_800B2764[16];
extern const char data_800B2774[16];
extern const char data_800B2784[12];
extern const char data_800B2790[12];
extern const char data_800B279C[12];
extern const char data_800B27A8[12];
extern const char data_800B27B4[12];
extern const char data_800B27C0[12];
extern const char data_800B27CC[12];
extern const char data_800B27D8[12];
extern const char data_800B27E4[12];
extern const char data_800B27F0[16];
extern const char data_800B2800[16];
extern const char data_800B2810[16];
extern const char data_800B2820[16];
extern const char data_800B2830[16];
extern const char data_800B2840[16];
extern const char data_800B2850[16];
extern const char data_800B2860[12];
extern const char data_800B286C[12];
extern const char data_800B2878[12];
extern const char data_800B2884[12];
extern const char data_800B2890[12];
extern const char data_800B289C[12];
extern const char data_800B28A8[12];
extern const char data_800B28B4[12];
extern const char data_800B28C0[12];
extern const char data_800B28CC[12];
extern const char data_800B28D8[12];
extern const char data_800B28E4[12];
extern const char data_800B28F0[12];
extern const char data_800B28FC[12];
extern const char data_800B2908[12];
extern const char data_800B2914[12];
extern const char data_800B2920[12];
extern const char data_800B292C[12];
extern const char data_800B2938[12];
extern const char data_800B2944[12];
extern const char data_800B2950[16];
extern const char data_800B2960[16];
extern const char data_800B2970[12];
extern const char data_800B297C[12];
extern const char data_800B2988[16];
extern const char data_800B2998[12];
extern const char data_800B29A4[12];
extern const char data_800B29B0[16];
extern const char data_800B29C0[16];
extern const char data_800B29D0[8];
extern const char data_800B29D8[12];
extern const char data_800B29E4[12];
extern const char data_800B29F0[12];
extern const char* speciesNames_800B3F28[144];
extern int magicBits_800B4168[154];
extern UnitSkills skills_800B43D0[154];
extern int speciesInts_800B4FD8[154];
extern const char* newSpeciesNames_800B5240[10];
extern MinionBaseStats baseStats_800B5268[10];
extern unsigned char modifiers_800B52B8[10][12];
extern int data_800B5330[15];
extern int data_800B536C[2];
extern int data_800B5374[2];
extern MapEvent events_800B537C[2];
extern MapCorridorRoomType corridorRooms_800B53A4[5];
extern unsigned char corridorRoomTypes_800B54A8[4][7];
extern int roomCount_800B54C4;
extern MapCorridorRoom* curRoom_800B54C8;
extern int floor_800B54CC;
extern int curKind_800B54D0;
extern int bossSpecies_800B54D4[8][3];
extern int corridorSpecies_800B5534[3];
extern GameSpawnEntry spawns_800B5540[16][3];
extern GameSpawnEntry bossSpawns_800B5600[3][3];

const char* speciesNames_800B3F28[144] = {
    data_800B297C, data_800B2970, data_800B2960, data_800B2950, data_800B2944, data_800B2938,
    data_800B292C, data_800B2920, data_800B2914, data_800B2908, data_800B28FC, data_800B28F0,
    data_800B28E4, data_800B28D8, data_800B28CC, data_800B28C0, data_800B28B4, data_800B28A8,
    data_800B289C, data_800B2890, data_800B2884, data_800B2878, data_800B286C, data_800B2860,
    data_800B2850, data_800B2840, data_800B2830, data_800B2820, data_800B2810, data_800B2800,
    data_800B27F0, data_800B27E4, data_800B27D8, data_800B27CC, data_800B27C0, data_800B27B4,
    data_800B27A8, data_800B279C, data_800B2790, data_800B2784, data_800B2774, data_800B2764,
    data_800B2754, data_800B2744, data_800B2738, data_800B272C, data_800B2720, data_800B2714,
    data_800B2708, data_800B26FC, data_800B26F0, data_800B26E4, data_800B26D4, data_800B26C4,
    data_800B26B4, data_800B26A4, data_800B2698, data_800B268C, data_800B2680, data_800B2674,
    data_800B2668, data_800B265C, data_800B2650, data_800B2644, data_800B2638, data_800B262C,
    data_800B2620, data_800B2614, data_800B2608, data_800B25FC, data_800B25F0, data_800B25E4,
    data_800B25D8, data_800B25CC, data_800B25C0, data_800B25B4, data_800B25A8, data_800B259C,
    data_800B2590, data_800B2580, data_800B2574, data_800B2568, data_800B255C, data_800B2550,
    data_800B2544, data_800B2538, data_800B2530, data_800B2528, data_800B2520, data_800B2518,
    data_800B2510, data_800B2508, data_800B2500, data_800B24F4, data_800B24EC, data_800B24E0,
    data_800B24D8, data_800B24CC, data_800B24C0, data_800B24B4, data_800B24A8, data_800B249C,
    data_800B2494, data_800B248C, data_800B2484, data_800B247C, data_800B2474, data_800B2468,
    data_800B245C, data_800B2450, data_800B2448, data_800B2440, data_800B2434, data_800B2428,
    data_800B241C, data_800B2414, data_800B240C, data_800B2400, data_800B23F4, data_800B23E4,
    data_800B23D8, data_800B23CC, data_800B23C0, data_800B23B8, data_800B23AC, data_800B239C,
    data_800B2390, data_800B2388, data_800B237C, data_800B236C, data_800B2360, data_800B2354,
    data_800B2344, data_800B2338, data_800B2330, data_800B2324, data_800B2318, data_800B2308,
    data_800B22FC, data_800B22F4, data_800B22E8, data_800B22DC, data_800B22D0, data_800B22C4,
};
int magicBits_800B4168[154] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0x200000, 0x1000000, 0x800000, 0x400000, 2, 0x400, 0x80, 0x10,
    2, 0x400, 0x80, 0x10, 4, 0x800, 0x100, 0x20,
    2, 0x400, 0x80, 0x2010, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0x200, 0x40, 8,
    0, 0x40000, 0, 0, 4, 0x800, 0x100, 0x20,
    1, 0x200, 0x40, 8, 0, 0, 0, 0,
    0, 0, 0x1000, 0, 0, 0, 0x20000, 0x2000,
    0, 0, 0x20000, 0x2000, 0, 0, 0x20000, 0x2000,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 4, 0x800, 0x100, 0x20,
    0x200000, 0x1000000, 0x800000, 0x400000, 0x200001, 0x1000200, 0x800040, 0x400008,
    0, 0, 0x80000, 0, 2, 0x400, 0x80, 0x10,
    1, 0x200, 0x40, 8, 0, 0, 0, 0,
    4, 0x800, 0x100, 0x20, 0x200000, 0x1000000, 0x800000, 0x400000,
    0x100000, 0x40000, 0x80000, 0, 0, 0x10000, 0, 0x8000,
    0x200007, 0x1000E00, 0x8001C0, 0x40001E, 0x100000, 0x40000, 0x80000, 0xE,
    0, 0, 0, 0, 0x100004, 0x40800, 0x80100, 0x2020,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};
UnitSkills skills_800B43D0[154] = {
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 4, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 5, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 2, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 3, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 4, 2, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 5, 2, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 2, 2, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 3, 2, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 4, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 5, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 2, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 3, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 4, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 5, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 2, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 3, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 4, 2, 1 }, { 0, 0, 0, 0 } } },
    { { { 1, 5, 2, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 2, 2, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 3, 2, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 0, 3, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0, 3, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0, 3, 1 }, { 0, 0, 0, 0 } } },
    { { { 1, 0, 3, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 4, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 5, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 2, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 3, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 4, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 5, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 2, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 3, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 4, 4, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 5, 4, 1 }, { 0, 0, 0, 0 } } },
    { { { 1, 2, 4, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 3, 4, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0, 3, 1 }, { 0, 0, 0, 0 } } },
    { { { 1, 0, 3, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 0, 3, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0, 3, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 7, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 7, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 7, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 7, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0xB, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 0xB, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 0xB, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0xB, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0xA, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0xA, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 0xA, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 0xA, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 8, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 8, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 8, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 8, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 4, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 5, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 2, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 3, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 0, 3, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 0, 3, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0, 3, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0, 3, 1 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0xD, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 0xD, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 0xD, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0xD, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 6, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 6, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 6, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 6, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 4, 2, 1 }, { 0, 0, 0, 0 } } },
    { { { 1, 5, 2, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 2, 2, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 3, 2, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 4, 4, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 5, 4, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 2, 4, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 3, 4, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 0, 3, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0, 3, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0, 3, 1 }, { 0, 0, 0, 0 } } },
    { { { 1, 0, 3, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 9, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 9, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 9, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 9, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0xC, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0xC, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0xC, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0xC, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 4, 4, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 5, 4, 1 }, { 0, 0, 0, 0 } } },
    { { { 1, 2, 4, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 3, 4, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0, 3, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0, 3, 1 }, { 0, 0, 0, 0 } } },
    { { { 1, 0, 3, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 0, 3, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0xC, 3, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0xC, 2, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0xC, 4, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0xC, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0xE, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 0xE, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 0xE, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0xE, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 4, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 5, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 2, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 3, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 4, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 5, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 2, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 3, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0xF, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 0xF, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 0xF, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0xF, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 4, 2, 1 }, { 1, 4, 3, 1 }, { 1, 4, 4, 1 }, { 1, 4, 0, 0 }, { 1, 0xC, 0, 0 } } },
    { { { 1, 5, 2, 1 }, { 1, 5, 3, 1 }, { 1, 5, 4, 1 }, { 1, 5, 0, 0 }, { 1, 0xC, 0, 0 } } },
    { { { 1, 2, 2, 1 }, { 1, 2, 3, 1 }, { 1, 2, 4, 1 }, { 1, 2, 0, 0 }, { 1, 0xC, 0, 0 } } },
    { { { 1, 3, 2, 1 }, { 1, 3, 3, 1 }, { 1, 3, 4, 1 }, { 1, 3, 0, 0 }, { 1, 0xC, 0, 0 } } },
    { { { 1, 0xD, 0, 0 }, { 1, 0xA, 0, 0 }, { 1, 9, 0, 0 }, { 1, 0xB, 0, 0 }, { 1, 0xC, 0, 0 } } },
    { { { 1, 0xB, 0, 0 }, { 1, 0xD, 0, 0 }, { 1, 0xA, 0, 0 }, { 1, 9, 0, 0 }, { 1, 0xC, 0, 0 } } },
    { { { 1, 9, 0, 0 }, { 1, 0xB, 0, 0 }, { 1, 0xD, 0, 0 }, { 1, 0xA, 0, 0 }, { 1, 0xC, 0, 0 } } },
    { { { 1, 0xA, 0, 0 }, { 1, 9, 0, 0 }, { 1, 0xB, 0, 0 }, { 1, 0xD, 0, 0 }, { 1, 0xC, 0, 0 } } },
    { { { 1, 4, 0, 0 }, { 1, 0, 4, 1 }, { 1, 0, 2, 1 }, { 1, 0, 3, 1 }, { 1, 0xC, 0, 0 } } },
    { { { 1, 5, 0, 0 }, { 1, 0, 4, 1 }, { 1, 0, 2, 1 }, { 1, 0, 3, 1 }, { 1, 0xC, 0, 0 } } },
    { { { 1, 2, 0, 0 }, { 1, 0, 4, 1 }, { 1, 0, 2, 1 }, { 1, 0, 3, 1 }, { 1, 0xC, 0, 0 } } },
    { { { 1, 3, 0, 0 }, { 1, 0, 4, 1 }, { 1, 0, 2, 1 }, { 1, 0, 3, 1 }, { 1, 0xC, 0, 0 } } },
    { { { 1, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, 0xC, 0, 0 } } },
    { { { 1, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, 0xC, 0, 0 } } },
    { { { 1, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, 0xC, 0, 0 } } },
    { { { 1, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, 0xC, 0, 0 } } },
    { { { 1, 0, 3, 1 }, { 1, 0xD, 3, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 0xF, 3, 1 }, { 1, 0xE, 3, 1 }, { 1, 0, 4, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 0, 2, 1 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 1, 0xB, 2, 1 }, { 1, 0xA, 2, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 8, 3, 1 }, { 1, 7, 3, 1 }, { 1, 6, 3, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 0, 2, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
    { { { 1, 0, 2, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },
};
int speciesInts_800B4FD8[154] = {
    -0x515FFFF4, 0x1607000C, 0x2719000C, 0x7264000C, 0x155000D, 0x1064000D, 0x388C000D, 0x6000000D,
    -0x4EFFFFF2, -0x3FF0FFF2, 0x393C000E, 0x7275000E, -0x4C87FFEE, 0x18910012, 0x3B000012, 0x773C0012,
    -0x535AFFED, 0x1D160013, 0x342D0013, 0x7A730013, -0x5ABEFFEC, 0xA5A0014, 0x37870014, 0x64000014,
    -0x6FFFFFE8, -0x42D2FFE8, 0x31550018, 0x688C0018, -0x5A69FFE7, 0xF000019, 0x28190019, 0x73640019,
    0xA7A001A, 0x2696001A, 0x4400001A, -0x78BCFFE6, -0x5276FFE5, 0x2400001B, 0x5B37001B, -0x6E92FFE5,
    -0x7F5AFFE4, 0x82D001C, 0x2146001C, 0x587D001C, 0x3475001D, 0x5596001D, 0x7300001D, -0x6C6FFE3,
    0x17AF001F, 0x2D11001F, 0x5F43001F, -0x728EFFE1, 0x41250020, 0x674B0020, -0x738FFFE0, 0x1C000020,
    -0x708CFFDF, -0x5773FFDF, 0x1C000021, 0x5D410021, -0x5058FFD7, 0x110A0029, 0x2D250029, 0x69610029,
    -0x5D8FFFD6, 0xF91002A, 0x3C0A002A, 0x6E3C002A, -0x4CB9FFD5, 0x1D64002B, 0x3D84002B, 0x7E11002B,
    0x7500004C, -0x7BF0FFB4, -0x58CDFFB4, 0x2564004C, 0x1A00004D, 0x2C11004D, 0x5B41004D, -0x728CFFB3,
    0x75F004E, 0x58004E, 0x257D004E, 0x5C00004E, 0x12000001, 0x200E0001, 0x3A280001, 0x7B690001,
    0x62930017, -0x7DFFFFE9, -0x55D7FFE9, 0x1E500017, 0x56320034, -0x779BFFCC, -0x5478FFCC, 0x2F0B0034,
    0x2B97003D, 0x4800003D, 0x6119003D, -0x5DA5FFC3, 0x7D0040, 0x19960040, 0x37000040, 0x7D460040,
    -0x55BEFFBD, 0x125D0043, 0x307B0043, 0x69000043, -0x5065FFBA, 0xBAA0046, 0x240F0046, 0x745F0046,
    -0x70CDFFAF, -0x4EABFFAF, 0x21780051, 0x5D000051, 0x689B005D, -0x7EFFFFA3, -0x62E3FFA3, 0x275A005D,
    0x23050062, 0x44250062, 0x694B0062, -0x5F7DFF9E, -0x5CB8FF9B, 0x65F0065, 0x38910065, 0x5B000065,
    -0x61C8FFDE, 0x226F0022, 0x3A870022, 0x6E070022, 0x45370044, 0x594B0044, 0x7E700044, 0xE000044,
    0x71000023, -0x7CEEFFDD, -0x6ADBFFDD, 0x21640023, -0x4971FFAE, 0x28000052, 0x4C240052, 0x7D550052,
    0x28000053, 0x28000054, 0x28000055, 0x28000056, 0x28000057, 0x28000058, 0x28000059, 0x2800005A,
    0x2800005B, 0x2800005C,
};
const char* newSpeciesNames_800B5240[10] = {
    data_800B29F0, data_800B29E4, data_800B29D8, data_800B29D0, data_800B29C0,
    data_800B29B0, data_800B29A4, data_800B2998, data_800B2988, data_800B2988,
};
MinionBaseStats baseStats_800B5268[10] = {
    { 0x14, 0xB4, 0xBE, 0xBE, 0x8C, 0x64, 0, 3 },
    { 0xA, 0xBE, 0x32, 0x32, 0xBE, 0x64, 2, 1 },
    { 0xBE, 0x64, 0xA0, 0xA0, 0x82, 0xBE, 3, 2 },
    { 0xBE, 0xBE, 0xAA, 0xAA, 0x5A, 0x64, 1, 3 },
    { 0xBE, 0xBE, 0xAA, 0xAA, 0x82, 0x64, 1, 3 },
    { 0xBE, 0xBE, 0xAA, 0xAA, 0x82, 0x64, 3, 3 },
    { 0xBE, 0xBE, 0xAA, 0xAA, 0x82, 0x64, 3, 3 },
    { 0xBE, 0xBE, 0xAA, 0xAA, 0x82, 0x64, 0, 3 },
    { 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 1, 3 },
    { 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 1, 3 },
};
unsigned char modifiers_800B52B8[10][12] = {
    { 0x20, 0x18, 0x20, 0x36, 0x20, 0x30, 0x20, 0x20, 0x20, 0xE0, 0x20, 0x40 },
    { 0x20, 0x36, 0x20, 0x18, 0x20, 0x30, 0x20, 0x20, 0x20, 0xE0, 0x20, 0x40 },
    { 0x18, 0x20, 0x36, 0x20, 0x20, 0x30, 0x20, 0x20, 0x20, 0xE0, 0x20, 0x40 },
    { 0x36, 0x20, 0x18, 0x20, 1, 0x20, 1, 1, 1, 0xE0, 0x20, 0x40 },
    { 0x36, 0x20, 0x18, 0x20, 0x20, 0x30, 0x20, 0x20, 0x20, 0xE0, 0x20, 0x40 },
    { 0x18, 0x20, 0x36, 0x20, 0x20, 0x30, 0x20, 0x20, 0x20, 0xE0, 0x20, 0x40 },
    { 0x18, 0x20, 0x36, 0x20, 0x20, 0x30, 0x20, 0x20, 0x20, 0xE0, 0x20, 0x40 },
    { 0, 0, 0, 0, 0x20, 0x30, 0x20, 0x20, 0x20, 0xE0, 0, 0 },
    { 0x36, 0x20, 0x18, 0x20, 0x20, 0x30, 0x20, 0x20, 0x20, 0xE0, 0x20, 0x40 },
    { 0x36, 0x20, 0x18, 0x20, 0x20, 0x30, 0x20, 0x20, 0x20, 0xE0, 0x20, 0x40 },
};
int data_800B5330[15] = {
    0x10000, 0, 0, 0xAF, 0x10000, 1, 0x57, 0,
    0x514, 0xF8CD, 0xFFFF, 0, 0, 0, 0,
};
int data_800B536C[2] = {
    0, 0xFFFF,
};
int data_800B5374[2] = {
    MAP_REF(data_800B5330), MAP_REF(data_800B536C),
};
MapEvent events_800B537C[2] = {
    { -1, 0xD, data_800B5374, 0x3C, { (void*)CorridorInit_800B331C } },
    { 0, 0x12, 0, 0, { 0 } },
};
MapCorridorRoomType corridorRooms_800B53A4[5] = {
    { 1, { { { 0, 0, 0x226 }, 0 }, { { 0x57, 0, 0x514 }, -0x733 }, { { 0, 0, 0 }, 0 } } },
    { 1, { { { 0, 0, 0xAF }, 0 }, { { -0x57, 0, 0x1775 }, -0x770 }, { { 0, 0, 0 }, 0 } } },
    { 2, { { { 0, 0, 0xAF }, 0 }, { { -0x70F, 0, 0x17ED }, -0x88F }, { { 0xCD7, 0, 0x1C8B }, -0x799 } } },
    { 0, { { { 0, 0, 0xAF }, 0 }, { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 } } },
    { -1, { { { 0x159, 0, 0xAA7 }, 0xA3 }, { { 0x11F, 0, 0xE67 }, -0x799 }, { { 0, 0, 0 }, 0 } } },
};
unsigned char corridorRoomTypes_800B54A8[4][7] = {
    { 1, 1, 1, 2, 2, 2, 2 },
    { 1, 1, 1, 2, 2, 3, 3 },
    { 1, 1, 2, 3, 3, 3, 3 },
    { 3, 3, 3, 3, 3, 3, 3 },
};
int roomCount_800B54C4 = 0;
MapCorridorRoom* curRoom_800B54C8 = 0;
int floor_800B54CC = 1;
int curKind_800B54D0 = 0;
int bossSpecies_800B54D4[8][3] = {
    { 0xC9, 0xC9, 0xC9 },
    { 0xCA, 0xCA, 0xCA },
    { 0xCB, 0xCB, 0xCB },
    { 0xCC, 0xCC, 0xCC },
    { 0xCD, 0xCD, 0xCD },
    { 0xCE, 0xCE, 0xCE },
    { 0xCF, 0xCF, 0xCF },
    { 0xD0, 0xD0, 0xD0 },
};
int corridorSpecies_800B5534[3] = { 0x22, 0x21, 0x23 };
GameSpawnEntry spawns_800B5540[16][3] = {
    { { 5, 0, 18, 3, 0, 3, 0 }, { 5, 1, 18, 3, 0, 3, 0 }, { 6, 2, 18, 3, 0, 3, 0 } },
    { { 5, 0, 18, 3, 0, 3, 0 }, { 5, 1, 18, 3, 0, 3, 0 }, { 6, 2, 18, 2, 0, 3, 0 } },
    { { 5, 0, 18, 3, 0, 3, 0 }, { 5, 1, 18, 3, 0, 3, 0 }, { 6, 2, 18, 3, 0, 3, 0 } },
    { { 7, 0, 18, 3, 0, 3, 0 }, { 7, 1, 18, 3, 0, 3, 0 }, { 2, 2, 18, 2, 18, 3, 0 } },
    { { 6, 0, 18, 3, 0, 3, 0 }, { 6, 1, 18, 3, 0, 3, 0 }, { 4, 2, 18, 2, 18, 3, 0 } },
    { { 6, 0, 18, 3, 0, 3, 0 }, { 4, 1, 18, 3, 0, 3, 0 }, { 6, 2, 18, 1, 18, 3, 0 } },
    { { 6, 0, 18, 3, 0, 3, 0 }, { 4, 1, 18, 0, 18, 3, 0 }, { 6, 2, 18, 1, 18, 3, 0 } },
    { { 4, 0, 18, 3, 0, 3, 0 }, { 6, 1, 18, 0, 18, 3, 0 }, { 6, 2, 18, 2, 18, 3, 0 } },
    { { 2, 0, 18, 3, 0, 3, 0 }, { 0xC, 1, 18, 0, 18, 3, 0 }, { 2, 2, 18, 1, 18, 1, 18 } },
    { { 4, 0, 18, 3, 0, 3, 0 }, { 0xA, 1, 18, 0, 18, 3, 0 }, { 2, 2, 18, 2, 0, 2, 18 } },
    { { 2, 0, 18, 3, 0, 3, 0 }, { 0xA, 1, 18, 0, 18, 3, 0 }, { 4, 2, 18, 1, 18, 1, 18 } },
    { { 2, 0, 18, 3, 0, 3, 0 }, { 8, 1, 18, 0, 18, 3, 0 }, { 6, 2, 18, 1, 18, 0, 18 } },
    { { 2, 0, 18, 3, 0, 3, 0 }, { 6, 1, 18, 0, 18, 3, 0 }, { 8, 2, 18, 2, 18, 0, 18 } },
    { { 2, 0, 18, 3, 0, 3, 0 }, { 6, 1, 18, 0, 18, 3, 0 }, { 8, 2, 18, 0, 18, 0, 18 } },
    { { 2, 0, 18, 3, 0, 3, 0 }, { 4, 1, 18, 0, 18, 3, 0 }, { 0xA, 2, 18, 1, 18, 2, 18 } },
    { { 2, 0, 18, 0, 18, 3, 0 }, { 4, 1, 18, 0, 18, 2, 18 }, { 0xA, 2, 18, 1, 18, 2, 18 } },
};
GameSpawnEntry bossSpawns_800B5600[3][3] = {
    { { 0x10, 0, 18, 3, 0, 3, 0 }, { 0, 0, 0, 3, 0, 3, 0 }, { 0, 0, 0, 3, 0, 3, 0 } },
    { { 0x10, 0, 18, 0, 18, 3, 0 }, { 0, 0, 0, 3, 0, 3, 0 }, { 0, 0, 0, 3, 0, 3, 0 } },
    { { 0x10, 0, 18, 0, 18, 0, 18 }, { 0, 0, 0, 3, 0, 3, 0 }, { 0, 0, 0, 3, 0, 3, 0 } },
};
const int unknown_800B22C0[1] = {
    0x139,
};
const char data_800B22C4[12] = "\x83^\x83""C\x83g\x83\x93";
const char data_800B22D0[12] = "\x83X\x83o\x83@\x83X";
const char data_800B22DC[12] = "\x83Z\x83g\x83\x8b\x83J";
const char data_800B22E8[12] = "\x83\x89\x83P\x83V\x83""F\x83\x8b";
const char data_800B22F4[8] = "\x83P\x83g\x81[";
const char data_800B22FC[12] = "\x83""C\x83v\x83_\x83~\x83""A";
const char data_800B2308[16] = "\x83V\x83\x83\x83N\x83\x8c\x83}\x83l\x83L";
const char data_800B2318[12] = "\x83R\x83\x8d\x83j\x83""A\x83X";
const char data_800B2324[12] = "\x83l\x83\x8c\x83""C\x83h";
const char data_800B2330[8] = "\x83J\x83\x8d";
const char data_800B2338[12] = "\x83T\x83\x89\x83\x80\x81[\x83\x93";
const char data_800B2344[16] = "\x83k\x81[\x83p\x83\x93\x83h\x83\x89";
const char data_800B2354[12] = "\x83""A\x83O\x83n\x83""C";
const char data_800B2360[12] = "\x83O\x83\x8c\x83""C\x83h\x83\x93";
const char data_800B236C[16] = "\x83""A\x81[\x83~\x83W\x83\x83\x81[";
const char data_800B237C[12] = "\x83o\x83""E\x83o\x83N";
const char data_800B2388[8] = "\x83J\x83\x80\x83\x89";
const char data_800B2390[12] = "\x83t\x83""F\x83""f\x83\x8b\x83R";
const char data_800B239C[16] = "\x83""A\x81[\x83\x94\x83\x8b\x83U\x83""b\x83N";
const char data_800B23AC[12] = "\x83X\x83p\x83""C\x83\x89\x83\x8b";
const char data_800B23B8[8] = "\x83I\x81[\x83[";
const char data_800B23C0[12] = "\x83""A\x83""C\x83I\x83i";
const char data_800B23CC[12] = "\x83l\x83\x94\x83@\x83\x93";
const char data_800B23D8[12] = "\x83""C\x83""F\x81[\x83""c";
const char data_800B23E4[16] = "\x83\x8c\x83""C\x83\x93\x83X\x83^\x81[";
const char data_800B23F4[12] = "\x83g\x83""D\x83\x8c\x83\x93";
const char data_800B2400[12] = "\x83t\x83""C\x83\x93\x83^\x83\x93";
const char data_800B240C[8] = "\x83o\x81[\x83j";
const char data_800B2414[8] = "\x83""C\x83h";
const char data_800B241C[12] = "\x83t\x83@\x83K\x81[";
const char data_800B2428[12] = "\x83J\x81[\x83\x8c\x83""b\x83W";
const char data_800B2434[12] = "\x83X\x83\x8f\x81[\x83\x94";
const char data_800B2440[8] = "\x83I\x81[\x83}";
const char data_800B2448[8] = "\x83K\x83\x8a\x83""A";
const char data_800B2450[12] = "\x83""A\x83\x93\x83N\x83""E";
const char data_800B245C[12] = "\x83\x8f\x81[\x83h\x83\x93";
const char data_800B2468[12] = "\x83""e\x83""B\x83""D\x83""c";
const char data_800B2474[8] = "\x83X\x83K\x83W";
const char data_800B247C[8] = "\x83\\\x81[\x83\x8b";
const char data_800B2484[8] = "\x83t\x83\x8c\x83""C";
const char data_800B248C[8] = "\x83\x8d\x83u\x83\x93";
const char data_800B2494[8] = "\x83G\x83\x8b";
const char data_800B249C[12] = "\x83V\x83\x87\x83\x94\x83\x93";
const char data_800B24A8[12] = "\x83t\x83\x8a\x83""b\x83O";
const char data_800B24B4[12] = "\x83Y\x83\x8b\x83\x80\x81[";
const char data_800B24C0[12] = "\x83y\x83""f\x83""B\x83\x93\x83S";
const char data_800B24CC[12] = "\x83g\x83""D\x83\x8b\x81[\x83\x93";
const char data_800B24D8[8] = "\x83K\x83r\x81[";
const char data_800B24E0[12] = "\x83G\x83\x93\x83u\x83\x89";
const char data_800B24EC[8] = "\x83""C\x83u\x83\x93";
const char data_800B24F4[12] = "\x83I\x81[\x83W\x83\x93";
const char data_800B2500[8] = "\x83""A\x83X\x83N";
const char data_800B2508[8] = "\x83""E\x83\x8b\x83h";
const char data_800B2510[8] = "\x83X\x83N\x83\x8b";
const char data_800B2518[8] = "\x83""e\x83\x8b\x83}";
const char data_800B2520[8] = "\x83J\x83\x8b\x83k";
const char data_800B2528[8] = "\x83t\x83@\x83\x8b";
const char data_800B2530[8] = "\x83V\x81[";
const char data_800B2538[12] = "\x83V\x83\x85\x83\x8a\x83@";
const char data_800B2544[12] = "\x83""A\x83i\x83V\x83\x85";
const char data_800B2550[12] = "\x83\x89\x83h\x83}\x83""C\x83\x93";
const char data_800B255C[12] = "\x83""e\x83\x89\x83}\x83""C\x83\x93";
const char data_800B2568[12] = "\x83X\x83N\x83}\x83""C\x83\x93";
const char data_800B2574[12] = "\x83J\x81[\x83}\x83""C\x83\x93";
const char data_800B2580[16] = "\x83\x89\x83h\x83""D\x83\x82\x81[\x83W";
const char data_800B2590[12] = "\x83""e\x83\x89\x83\x82\x81[\x83W";
const char data_800B259C[12] = "\x83X\x83N\x83\x82\x81[\x83W";
const char data_800B25A8[12] = "\x83p\x83^\x83\x82\x81[\x83W";
const char data_800B25B4[12] = "\x83\x89\x83h\x83""D\x81[\x83g";
const char data_800B25C0[12] = "\x83""e\x83\x89\x83""E\x81[\x83g";
const char data_800B25CC[12] = "\x83X\x83N\x83""D\x81[\x83g";
const char data_800B25D8[12] = "\x83p\x83^\x83""E\x81[\x83g";
const char data_800B25E4[12] = "\x83\x89\x83h\x83N\x81[\x83K";
const char data_800B25F0[12] = "\x83""e\x83\x89\x83N\x81[\x83K";
const char data_800B25FC[12] = "\x83X\x83N\x83""D\x81[\x83K";
const char data_800B2608[12] = "\x83p\x83^\x83N\x81[\x83K";
const char data_800B2614[12] = "\x83\x89\x83h\x83g\x83h\x83\x93";
const char data_800B2620[12] = "\x83""e\x83\x89\x83g\x83h\x83\x93";
const char data_800B262C[12] = "\x83X\x83N\x83g\x83h\x83\x93";
const char data_800B2638[12] = "\x83p\x83^\x83g\x83h\x83\x93";
const char data_800B2644[12] = "\x83\x89\x83h\x83""C\x81[\x83v";
const char data_800B2650[12] = "\x83""e\x83\x89\x83""C\x81[\x83v";
const char data_800B265C[12] = "\x83X\x83N\x83""C\x81[\x83v";
const char data_800B2668[12] = "\x83p\x83^\x83""C\x81[\x83v";
const char data_800B2674[12] = "\x83\x89\x83h\x83\x82\x81[\x83\x8b";
const char data_800B2680[12] = "\x83""e\x83\x89\x83\x82\x81[\x83\x8b";
const char data_800B268C[12] = "\x83X\x83N\x83\x82\x81[\x83\x8b";
const char data_800B2698[12] = "\x83p\x83^\x83\x82\x81[\x83\x8b";
const char data_800B26A4[16] = "\x83\x89\x83h\x83}\x83\x93\x83""e\x83""B";
const char data_800B26B4[16] = "\x83""e\x83\x89\x83}\x83\x93\x83""e\x83""B";
const char data_800B26C4[16] = "\x83X\x83N\x83}\x83\x93\x83""e\x83""B";
const char data_800B26D4[16] = "\x83p\x83^\x83}\x83\x93\x83""e\x83""B";
const char data_800B26E4[12] = "\x83\x89\x83h\x83\x8f\x83X\x83v";
const char data_800B26F0[12] = "\x83""e\x83\x89\x83\x8f\x83X\x83v";
const char data_800B26FC[12] = "\x83X\x83N\x83\x8f\x83X\x83v";
const char data_800B2708[12] = "\x83p\x83^\x83\x8f\x83X\x83v";
const char data_800B2714[12] = "\x83""A\x83}\x83T\x83O";
const char data_800B2720[12] = "\x83\x82\x83\x8a\x83T\x83O";
const char data_800B272C[12] = "\x83^\x83S\x83T\x83O";
const char data_800B2738[12] = "\x83q\x83L\x83T\x83O";
const char data_800B2744[16] = "\x83\x89\x83h\x83y\x83""b\x83J\x81[";
const char data_800B2754[16] = "\x83""e\x83\x89\x83y\x83""b\x83J\x81[";
const char data_800B2764[16] = "\x83X\x83N\x83y\x83""b\x83J\x81[";
const char data_800B2774[16] = "\x83p\x83^\x83y\x83""b\x83J\x81[";
const char data_800B2784[12] = "\x83\x89\x83h\x83\x8b\x83R";
const char data_800B2790[12] = "\x83""e\x83\x89\x83\x8b\x83R";
const char data_800B279C[12] = "\x83X\x83N\x83\x8b\x83R";
const char data_800B27A8[12] = "\x83p\x83^\x83\x8b\x83R";
const char data_800B27B4[12] = "\x83h\x83O\x83p\x83\x89";
const char data_800B27C0[12] = "\x83""e\x83\x89\x83p\x83\x89";
const char data_800B27CC[12] = "\x83X\x83N\x83p\x83\x89";
const char data_800B27D8[12] = "\x83p\x83^\x83p\x83\x89";
const char data_800B27E4[12] = "\x83h\x83O\x83\x8a\x83""b\x83p";
const char data_800B27F0[16] = "\x83""e\x83\x89\x83O\x83\x8a\x83""b\x83p";
const char data_800B2800[16] = "\x83X\x83N\x83O\x83\x8a\x83""b\x83p";
const char data_800B2810[16] = "\x83p\x83^\x83O\x83\x8a\x83""b\x83p";
const char data_800B2820[16] = "\x83\x89\x83h\x83""A\x83""b\x83V\x83\x85";
const char data_800B2830[16] = "\x83""e\x83\x89\x83""A\x83""b\x83V\x83\x85";
const char data_800B2840[16] = "\x83X\x83N\x83""A\x83""b\x83V\x83\x85";
const char data_800B2850[16] = "\x83p\x83^\x83""A\x83""b\x83V\x83\x85";
const char data_800B2860[12] = "\x83h\x83O\x83K\x83\x8d\x83\x93";
const char data_800B286C[12] = "\x83""e\x83\x89\x83K\x83\x8d\x83\x93";
const char data_800B2878[12] = "\x83X\x83N\x83K\x83\x8d\x83\x93";
const char data_800B2884[12] = "\x83p\x83^\x83K\x83\x8d\x83\x93";
const char data_800B2890[12] = "\x83\x89\x83h\x83\x8b\x83\x93\x83K";
const char data_800B289C[12] = "\x83""e\x83\x89\x83\x8b\x83\x93\x83K";
const char data_800B28A8[12] = "\x83X\x83N\x83\x8b\x83\x93\x83K";
const char data_800B28B4[12] = "\x83h\x83\x8b\x83\x93\x83K";
const char data_800B28C0[12] = "\x83\x89\x83h\x83S\x81[\x83""A";
const char data_800B28CC[12] = "\x83""e\x83\x89\x83S\x81[\x83""A";
const char data_800B28D8[12] = "\x83X\x83N\x83S\x81[\x83""A";
const char data_800B28E4[12] = "\x83p\x83^\x83S\x81[\x83""A";
const char data_800B28F0[12] = "\x83Q\x83""C\x83u\x83\x8b";
const char data_800B28FC[12] = "\x83N\x83\x8c\x83""C\x83u\x83\x8b";
const char data_800B2908[12] = "\x83o\x83""b\x83J\x83\x8b\x81[";
const char data_800B2914[12] = "\x83W\x83^\x83\x93\x83u\x83\x8b";
const char data_800B2920[12] = "\x83\x89\x83h\x83o\x83\x89\x83\x93";
const char data_800B292C[12] = "\x83""e\x83\x89\x83o\x83\x89\x83\x93";
const char data_800B2938[12] = "\x83X\x83N\x83o\x83\x89\x83\x93";
const char data_800B2944[12] = "\x83p\x83^\x83o\x83\x89\x83\x93";
const char data_800B2950[16] = "\x83\x89\x83M\x83t\x83\x8c\x83""C\x83h";
const char data_800B2960[16] = "\x83""e\x83\x89\x83t\x83\x8c\x83""C\x83h";
const char data_800B2970[12] = "\x83}\x83t\x83\x8c\x83""C\x83h";
const char data_800B297C[12] = "\x83p\x83^\x83\x8c\x83""C\x83h";
const char data_800B2988[16] = "\x81H\x81H\x81H\x81H\x81H\x81H\x81H";
const char data_800B2998[12] = "\x83N\x83\x89\x81[\x83K\x83X";
const char data_800B29A4[12] = "\x83""C\x83\x88\x83\x8b\x83K";
const char data_800B29B0[16] = "\x83""e\x83""B\x83}\x83""C\x83I\x83X";
const char data_800B29C0[16] = "\x83V\x83N\x83J\x83\x93\x83W\x83\x83\x83\x8b";
const char data_800B29D0[8] = "\x83R\x83\x8b\x83i";
const char data_800B29D8[12] = "\x83W\x83`\x83""E\x83I";
const char data_800B29E4[12] = "\x83`\x83""b\x83J\x81[";
const char data_800B29F0[12] = "\x83p\x83\x8b\x81[\x83W\x83\x83";
