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

/* NONMATCHING: scheduling / registers */
/* takes Levant through the door of the room he is in that he stands at */
void Corridor_800B29FC(MapEnt* ent)
{
    MapCorridorWork* w = (MapCorridorWork*)ent->work_14;
    int i;

    if (!(unknownFlags_8008D678 & 0x20000))
    {
        return;
    }
    CorridorRoomKind_800B34A4(w);
    for (i = 0; i < 3; i++)
    {
        if (w->cur_20->exits_4[i].room_0 && IsEventPointValid_800A6504(i, (int*)&levantPos_8008BD18))
        {
            CorridorGo_800B33C0(w, i);
            savedLevantPos_80091C78.pos[0] = CorridorDoor_800B34B8(w)->pos_0[0];
            savedLevantPos_80091C78.pos[1] = CorridorDoor_800B34B8(w)->pos_0[1];
            savedLevantPos_80091C78.pos[2] = CorridorDoor_800B34B8(w)->pos_0[2];
            savedLevantRot_80091CA8[0] = 0;
            savedLevantRot_80091CA8[1] = CorridorDoorRot_800B351C(w);
            savedLevantRot_80091CA8[2] = 0;
            useSavedLevantPos_80091C98 = 1;
            saveData_8008B570.mapId_2E4[2].cur_0 = CorridorRoomKind_800B34A4(w);
            forceMapReload_80091C9C = 1;
            return;
        }
    }
}

/* NONMATCHING: scheduling / registers */
/* GAME (fixed address, hunting): the encounter table of the room (the way on: its floor's boss, unless fought) */
GameSpawnEntry* CorridorSpawns_800B2B40(void)
{
    int floor;
    int boss;
    int group;

    if (curKind_800B54D0 % 5 == 4)
    {
        floor = floor_800B54CC;
        boss = floor % 8;
        group = (floor - 1) / 8;
        if (group < 0)
        {
            group = 0;
        }
        else if (group >= 3)
        {
            group = 2;
        }
        if (boss < 8)
        {
            if (!roomCount_800B54C4 || !curRoom_800B54C8 || curRoom_800B54C8->flags_1C)
            {
                return bossSpawns_800B5600[group];
            }
        }
        return 0;
    }
    group = curKind_800B54D0 / 2;
    if (group >= 16)
    {
        group = 15;
    }
    return spawns_800B5540[group];
}

/* NONMATCHING: scheduling / registers */
/* a new floor: the start room and the rooms grown from it, one dead end the way on */
void CorridorNewFloor_800B2C6C(MapCorridorWork* w)
{
    int n;

    w->cur_20 = &w->start_0;
    curRoom_800B54C8 = &w->start_0;
    ClearEncounterSpecies_800A5474();
    w->f28 = 0;
    w->budget_2C = 1;
    w->theme_38 = rand() % 5;
    w->start_0.flags_1C = 0x8000;
    w->start_0.exits_4[0].door_4 = -1;
    w->start_0.exits_4[1].door_4 = -1;
    w->start_0.exits_4[2].door_4 = -1;
    w->start_0.f1E = 0;
    w->start_0.exits_4[0].room_0 = 0;
    w->start_0.exits_4[1].room_0 = 0;
    w->start_0.exits_4[2].room_0 = 0;
    roomCount_800B54C4 = 0;
    w->start_0.kind_0 = rand() % 3 * 5 + w->theme_38 * 15;
    n = CorridorGrow_800B2D98(w, 1, &w->start_0, 0, 0);
    CorridorPlaceExit_800B3584(w, &w->start_0, rand() % n);
    saveData_8008B570.mapId_2E4[2].cur_0 = w->start_0.kind_0;
}

/* NONMATCHING: scheduling / registers */
/* grows a room behind door door of parent (and its own rooms); deadEnds: the dead ends so far */
int CorridorGrow_800B2D98(MapCorridorWork* w, int door, MapCorridorRoom* parent, int budget, int deadEnds)
{
    MapCorridorRoom* room = ListAlloc_8003FDC0(&heap_80091C48, sizeof(MapCorridorRoom));
    int i;

    roomCount_800B54C4++;
    if (parent)
    {
        parent->exits_4[door].room_0 = room;
        parent->exits_4[door].door_4 = 0;
    }
    room->kind_0 = CorridorRoomType_800B3714(&budget);
    if (room->kind_0 == 3)
    {
        deadEnds++;
        w->budget_2C--;
    }
    else if (room->kind_0 == 2)
    {
        w->budget_2C++;
    }
    room->exits_4[0].room_0 = parent;
    room->kind_0 = rand() % 3 * 5 + room->kind_0 + w->theme_38 * 15;
    room->exits_4[0].door_4 = door;
    room->exits_4[1].room_0 = 0;
    room->exits_4[2].room_0 = 0;
    room->flags_1C = 0x8000;
    room->exits_4[1].door_4 = -1;
    room->exits_4[2].door_4 = -1;
    for (i = 1; i <= corridorRooms_800B53A4[room->kind_0 % 5].exits_0; i++)
    {
        deadEnds = CorridorGrow_800B2D98(w, i, room, budget, deadEnds);
    }
    return deadEnds;
}

/* NONMATCHING: scheduling / registers */
/* the floor's monsters: species 57..184 (theme 0) or of the theme, sometimes one of 185.. */
void CorridorSpecies_800B2FAC(MapCorridorWork* w)
{
    int i;
    int* s = corridorSpecies_800B5534;

    for (i = 0; i < 3; i++, s++)
    {
        if (w->theme_38 == 0)
        {
            *s = rand() % 128 + 57;
            if (rand() <= w->floor_34 + 256)
            {
                *s = rand() % 8 + 185;
            }
        }
        else
        {
            *s = rand() % 32 * 4 + w->theme_38 + 56;
            if (rand() <= w->floor_34 + 256)
            {
                *s = rand() % 2 * (w->theme_38 - 1) + 185;
            }
        }
        CorridorUniqueModel_800B3870(corridorSpecies_800B5534, i);
    }
}

void MapInit_800B3128(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B3908();
        ClearFieldMinions_800A7784();
        RequestModels_800B3CAC(events_800B537C);
        if (levantAnimSet_80091C74 >= 0)
        {
            LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        }
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B3D7C);
    }
}

/* NONMATCHING: scheduling / registers */
/* GAME (fixed address, hunting): the species of the room's encounters (the way on: its floor's boss) */
int* CorridorEncounterSpecies_800B3198(void)
{
    int boss;

    if (curKind_800B54D0 % 5 == 4)
    {
        boss = (floor_800B54CC - 1) % 8;
        if (boss < 8)
        {
            return bossSpecies_800B54D4[boss];
        }
        return 0;
    }
    return corridorSpecies_800B5534;
}

/* GAME (fixed address, hunting): the encounter flags of the room Levant is in */
unsigned short* CorridorEncounterFlags_800B322C(void)
{
    unsigned short* flags = 0;

    if (roomCount_800B54C4 && curRoom_800B54C8)
    {
        flags = &curRoom_800B54C8->flags_1C;
    }
    return flags;
}

/* the species tables from 0x39 on and the species from 0xC9 on (the executable, MENU: fixed addresses) */
int* CorridorMagicBits_800B3260(int idx)
{
    return &magicBits_800B4168[idx];
}

UnitSkills* CorridorSkills_800B3274(int idx)
{
    return &skills_800B43D0[idx];
}

int* CorridorSpeciesInt_800B3290(int idx)
{
    return &speciesInts_800B4FD8[idx];
}

MinionBaseStats* CorridorBaseStats_800B32A4(int idx)
{
    return &baseStats_800B5268[idx];
}

const char* CorridorSpeciesName_800B32B8(int idx)
{
    return speciesNames_800B3F28[idx];
}

const char* CorridorNewSpeciesName_800B32D4(int idx)
{
    return newSpeciesNames_800B5240[idx];
}

unsigned char* CorridorModifiers_800B32F0(int idx)
{
    return modifiers_800B52B8[idx];
}

int CorridorFloor_800B330C(void)
{
    return floor_800B54CC;
}

/* NONMATCHING: scheduling / registers */
void CorridorInit_800B331C(MapEnt* ent)
{
    MapCorridorWork* w = (MapCorridorWork*)ent->work_14;

    floor_800B54CC = 1;
    curKind_800B54D0 = 0;
    dword_80091C8C = 1;
    w->floor_34 = 1;
    w->theme_38 = 0;
    unknownFlags_8008D678 |= 0x20000;
    CorridorFloorStart_800B3394(w);
    Corridor_800B29FC(ent);
    ent->update_90 = Corridor_800B29FC;
}

void CorridorFloorStart_800B3394(MapCorridorWork* w)
{
    CorridorNewFloor_800B2C6C(w);
    CorridorSpecies_800B2FAC(w);
}

/* NONMATCHING: scheduling / registers */
/* goes through exit of the room; back to the start room: the next floor */
void CorridorGo_800B33C0(MapCorridorWork* w, int exit)
{
    MapCorridorRoom* room = w->cur_20->exits_4[exit].room_0;
    int door = w->cur_20->exits_4[exit].door_4;

    w->cur_20 = room;
    curRoom_800B54C8 = room;
    if (room == &w->start_0 && !door)
    {
        if (w->floor_34++ >= 1000)
        {
            w->floor_34 = 999;
        }
        floor_800B54CC = w->floor_34;
        if (w->floor_34 >= saveData_8008B570.corridorFloor_810)
        {
            saveData_8008B570.corridorFloor_810 = w->floor_34;
        }
        CorridorFreeFloor_800B37B0(w);
        CorridorNewFloor_800B2C6C(w);
        CorridorSpecies_800B2FAC(w);
    }
    w->door_24 = door;
    unknownFlags_8008D678 |= 0x20000;
    curKind_800B54D0 = w->cur_20->kind_0;
}

int CorridorRoomKind_800B34A4(MapCorridorWork* w)
{
    return w->cur_20->kind_0;
}

MapCorridorDoor* CorridorDoor_800B34B8(MapCorridorWork* w)
{
    return &corridorRooms_800B53A4[w->cur_20->kind_0 % 5].doors_4[w->door_24];
}

int CorridorDoorRot_800B351C(MapCorridorWork* w)
{
    return corridorRooms_800B53A4[w->cur_20->kind_0 % 5].doors_4[w->door_24].rotY_C;
}

/* NONMATCHING: scheduling / registers */
/* turns the n-th dead end (from 0, depth first) into the way on; returns n left */
int CorridorPlaceExit_800B3584(MapCorridorWork* w, MapCorridorRoom* room, int n)
{
    int i;

    if (room->kind_0 % 5 == 3)
    {
        if (--n == -1)
        {
            room->exits_4[1].room_0 = &w->start_0;
            room->exits_4[1].door_4 = 0;
            room->kind_0 = rand() % 3 * 5 + w->theme_38 * 15 + 4;
        }
        return n;
    }
    for (i = 1; i <= corridorRooms_800B53A4[room->kind_0 % 5].exits_0; i++)
    {
        n = CorridorPlaceExit_800B3584(w, room->exits_4[i].room_0, n);
    }
    return n;
}

/* NONMATCHING: scheduling / registers */
/* a room type for a new room (2: it branches, 3: a dead end; *budget grows to 3 with them) */
int CorridorRoomType_800B3714(int* budget)
{
    int type = corridorRoomTypes_800B54A8[*budget][rand() % 7];

    if (type == 1 || type == 2)
    {
        if (++*budget >= 4)
        {
            *budget = 3;
        }
    }
    return type;
}

void CorridorFreeFloor_800B37B0(MapCorridorWork* w)
{
    CorridorFreeRooms_800B37D8(&w->start_0, w->start_0.exits_4[1].room_0);
    curRoom_800B54C8 = 0;
}

void CorridorFreeRooms_800B37D8(MapCorridorRoom* start, MapCorridorRoom* room)
{
    if (room->exits_4[1].room_0 && start != room->exits_4[1].room_0)
    {
        CorridorFreeRooms_800B37D8(start, room->exits_4[1].room_0);
    }
    if (room->exits_4[2].room_0 && start != room->exits_4[2].room_0)
    {
        CorridorFreeRooms_800B37D8(start, room->exits_4[2].room_0);
    }
    if (room && start != room)
    {
        ListFree_8003FE38(&heap_80091C48, room);
        roomCount_800B54C4--;
    }
}

/* NONMATCHING: scheduling / registers */
/* a species whose model one of the first n already has: that one instead */
void CorridorUniqueModel_800B3870(int* species, int n)
{
    unsigned int i;
    MinionModelDesc* d;

    for (i = 0; i < n; i++)
    {
        d = GetSpeciesModelDesc_80019C70(species[n]);
        if (d->modelId_0 == GetSpeciesModelDesc_80019C70(species[i])->modelId_0)
        {
            species[n] = species[i];
            return;
        }
    }
}

void StartMapTask_800B3908(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B3938;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B3938(EventEntry* entry, int* st)
{
    if (!AreLevantFilesLoaded_800AC768() || !IsModelLoaderDone_800205D0())
    {
        eventDispatchHalt_8008B540 = 1;
    }
    else
    {
        st[0] = 0;
        st[1] = -1;
        st[2] = 0;
        MapTask_800B39D0(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B39D0;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B39D0(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = events_800B537C;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B3A88(events, currentArea_80091C44);
        st[2] += EnterArea_800B3BA4(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B3A88(MapEvent* ev, int area)
{
    EventNode* node;
    EventEntry* entry;
    int areas;
    int n;
    int i;
    int count;

    n = 0;
    for (; ev->type_4 != MAP_EV_END; ev++)
    {
        if (ev->type_4 == MAP_EV_SCRIPT && ev->areas_0 != -1 && !InAreas(ev->areas_0, area))
        {
            entry = ev->run_10.script;
            if (entry)
            {
                n++;
                entry->flags = (entry->flags & ~1) | 0x8000;
            }
            ev->run_10.script = 0;
        }
    }
    node = eventEntities_8008D400;
    count = node->count;
    for (i = 0; i < count; i++)
    {
        entry = &node->entry;
        if ((entry->flags & 0x8001) == 1)
        {
            areas = ((MapEnt*)entry->buffer)->areas_8;
            if (areas != -1 && !InAreas(areas, area))
            {
                entry->flags = (entry->flags & ~1) | 0x8000;
                n++;
            }
        }
        node = node->next;
    }
    return n;
}

int EnterArea_800B3BA4(MapEvent* ev, int area, int prev)
{
    int n;
    int areas;
    int enter;

    n = 0;
    for (; ev->type_4 != MAP_EV_END; ev++)
    {
        areas = ev->areas_0;
        enter = 0;
        if ((prev == -1 || !InAreas(areas, prev)) && InAreas(areas, area))
        {
            enter = 1;
        }
        if (enter)
        {
            if (ev->type_4 == MAP_EV_VOICES)
            {
                SetVoiceTable_800A6830(ev->data_8);
            }
            else if (ev->type_4 == MAP_EV_SCRIPT)
            {
                n++;
                ev->run_10.script = StartEventScript_800A59D0(ev->data_8);
            }
            else
            {
                AddEntity_800B3D7C(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B3CAC(MapEvent* ev)
{
    MapMinion* m;
    MapActorModel* model;
    MinionModelDesc* desc;

    for (; ev->type_4 != MAP_EV_END; ev++)
    {
        if (ev->type_4 == MAP_EV_MINION)
        {
            m = ev->data_8;
            model = m->model_0;
            if (m->species_4)
            {
                desc = GetSpeciesModelDesc_80019C70(m->species_4->species_0);
                if (!RequestLoaderModel_800206A0(desc->modelId_0, desc->field_2 * 2 + model->sel_28, 3, m->f1C))
                {
                    break;
                }
            }
            else if (model)
            {
                if (!RequestLoaderModel_800206A0(model->modelId_4, model->sel_28, 2, m->f1C))
                {
                    break;
                }
            }
        }
    }
    StartModelLoader_8002056C();
}

/* an entity for the event (MapEvent.run_10.init its update) */
static inline int NewEntity(MapEvent* ev)
{
    EventEntry* entry;
    MapEnt* ent;

    entry = AllocEventEntry_80043AF8(eventEntities_8008D400);
    if (entry)
    {
        ent = entry->buffer;
        entry->flags = (entry->flags | 1) & ~0x8000;
        ent->entry_0 = entry;
        ent->event_4 = ev;
        ent->areas_8 = ev->areas_0;
        ent->type_C = ev->type_4;
        ent->data_10 = ev->data_8;
        ent->armed_78 = 0;
        ent->state_7C = -1;
        ent->prev_80 = -1;
        ent->trigger_84 = -1;
        ent->script_88 = 0;
        ent->arg_8C = 0;
        ent->update_90 = ev->run_10.init;
        if ((unsigned)ev->type_4 >= 14)
        {
            StepEntity(entry, entry->buffer);
        }
        entry->cb_8 = (EventEntryFn)EntityTask_800B3EA8;
        return 1;
    }
    return 0;
}

int AddEntity_800B3D7C(void* ev)
{
    return NewEntity(ev);
}

void EntityTask_800B3EA8(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}
