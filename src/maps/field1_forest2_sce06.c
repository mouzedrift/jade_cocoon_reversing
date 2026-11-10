#include "maps/map.h"

void Warp_800B2390(MapEnt* ent);
void SlidingDoor_800B24B4(MapEnt* ent);
void TileDoor_800B27A4(MapEnt* ent);
void Lock_800B2900(MapEnt* ent);
void MapInit_800B2AEC(int phase);
void SlidingDoorInit_800B2B5C(MapEnt* ent);
void TileDoorInit_800B2BF0(MapEnt* ent);
void LockInit_800B2C84(MapEnt* ent);
void StartMapTask_800B2CF8(void);
void MapTaskLoad_800B2D28(EventEntry* entry, int* st);
void MapTask_800B2DC0(EventEntry* entry, int* st);
int LeaveArea_800B2E78(MapEvent* ev, int area);
int EnterArea_800B2F94(MapEvent* ev, int area, int prev);
void RequestModels_800B309C(MapEvent* ev);
int AddEntity_800B316C(void* ev);
int FindTileLayer_800B3298(int id);
void SetTileLayerFrame_800B3350(int layer, int frame);
int IsTileLayerDone_800B336C(int layer, int frame);
void EntityTask_800B33D4(EventEntry* entry, MapEnt* ent);

extern const char unknown_800B22C0[4];
extern const char data_800B22C4[60];
extern const char data_800B2300[52];
extern const char data_800B2334[68];
extern const char data_800B2378[24];
extern MapWarp warp_800B3454;
extern MapWarp warp_800B346C;
extern MapEvent event_800B3484[4];
extern MapTileDoor data_800B34D4;
extern MapInstr script_800B34E4[12];
extern MapInstr script_800B35A4[6];
extern int text_800B3604[3];
extern int text_800B3610[3];
extern MapLockPoint data_800B361C[3];
extern MapLock data_800B3664;
extern MapEvent events_800B3680[6];
extern int data_800B36F8[3];
extern int data_800B3704[28];
extern int data_800B3774[32];
extern int data_800B37F4[24];

void Warp_800B2390(MapEnt* ent)
{
    MapWarp* warp;
    LevantPos* levant;

    warp = ent->data_10;
    if (fieldMode_800B0EC0 == 1 && !(battleFlags_800B1228 & 0x4000))
    {
        levant = &saveData_8008B570.levant_7A8;
        if (IsEventPointValid_800A6504(warp->point_10, (int*)levant))
        {
            savedLevantPos_80091C78.pos[0] = warp->pos_0[0];
            savedLevantPos_80091C78.pos[1] = warp->pos_0[1];
            savedLevantPos_80091C78.pos[2] = warp->pos_0[2];
            if (warp->rotY_C != 0x4000)
            {
                savedLevantRot_80091CA8[0] = 0;
                savedLevantRot_80091CA8[1] = levant->rot.vy + warp->rotY_C;
                savedLevantRot_80091CA8[2] = 0;
            }
            else
            {
                savedLevantRot_80091CA8[0] = saveData_8008B570.levant_7A8.rot.vx;
                savedLevantRot_80091CA8[1] = saveData_8008B570.levant_7A8.rot.vy;
                savedLevantRot_80091CA8[2] = saveData_8008B570.levant_7A8.rot.vz;
            }
            saveData_8008B570.mapId_2E4[0].cur_0 = warp->map_12[0];
            saveData_8008B570.mapId_2E4[1].cur_0 = warp->map_12[1];
            saveData_8008B570.mapId_2E4[2].cur_0 = warp->map_12[2];
            useSavedLevantPos_80091C98 = 1;
            forceMapReload_80091C9C = 1;
            if (warp->idle_E)
            {
                ResetLevantActorToIdle_800A8DEC();
            }
        }
    }
}

void SlidingDoor_800B24B4(MapEnt* ent)
{
    int pos[3];
    short rot[4];
    MapSlidingDoor* door;
    MapSlidingDoorWork* w;
    MapSlidingDoorPart* part;
    void* script;
    int t;
    int i;
    int light;

    door = ent->data_10;
    w = (MapSlidingDoorWork*)ent->work_14;
    if (IsEventPointInView_800A66A4(&door->point_0, (int*)&levantPos_8008BD18, (unsigned short*)&levantPos_8008BD18.rot) &&
        !w->open_4 && !FindEventScript_800A5AE4(w->script_0))
    {
        ent->trigger_84 = door->valuable_18;
        ent->armed_78 = 1;
    }
    switch (ent->state_7C)
    {
    case 0:
        if (fieldMode_800B0EC0 == 1)
        {
            if (door->valuable_18 < 0)
            {
                script = data_800B3704;
            }
            else if (TestValuableFlag_800AD73C(door->valuable_18))
            {
                script = data_800B3774;
            }
            else
            {
                script = data_800B37F4;
            }
            ent->trigger_84 = door->valuable_18;
            w->script_0 = GetEventScriptId_800A5AD0(StartEventScriptForEntity_800A5AA0(script, ent));
            ent->state_7C = -1;
        }
        break;
    case 1:
        w->open_4 = 1;
        ent->state_7C = -1;
        if (door->flag_14 >= 0)
        {
            SetEventFlag_800AD0F8(door->flag_14);
        }
        PlaySfx_80031494(door->sfx_4E);
        break;
    }
    if (w->open_4)
    {
        t = CLAMP(w->t_8 + 1, 0, door->frames_4C);
        w->t_8 = t;
        if (t == door->frames_4C)
        {
            ent->prev_80 = 2;
            SetWallsEnabled_800A6564(&door->walls_10, 0);
        }
    }
    for (i = 0; i < 2; i++)
    {
        part = &door->parts_1C[i];
        if (part->ftg_0 >= 0)
        {
            pos[0] = part->pos_4[0] + (part->openX_14 - part->pos_4[0]) * w->t_8 / door->frames_4C;
            pos[1] = part->pos_4[1];
            pos[2] = part->pos_4[2];
            rot[0] = 0;
            rot[1] = part->rotY_10 + w->t_8 * part->turn_12 / door->frames_4C;
            rot[2] = 0;
            light = FindNearestCameraPoint_80019CC4(pos);
            DrawFtgObjectAtSlot0_8004D1EC(&mapState_8008B500.ftg_3C[part->ftg_0], pOT_8008D690, pos, rot, &cameraState_8008D4F0.ent_44[light], 1, 0);
        }
    }
}

void TileDoor_800B27A4(MapEnt* ent)
{
    MapTileDoor* door = ent->data_10;
    MapTileDoorWork* w = (MapTileDoorWork*)ent->work_14;
    int open;

    if (!IsTileLayerDone_800B336C(w->layer_4, w->frame_8))
    {
        return;
    }
    if (w->frame_8 == door->seq_8[w->open_0].last_1)
    {
        open = TestEventFlag_800AD0D4(door->flag_0) != 0;
        if (!open)
        {
            open = ent->state_7C == 0;
        }
        if (w->open_0 != open)
        {
            if (door->sfx_6 != 0xFF)
            {
                w->sfx_C = 1;
                PlaySfx_80031494(door->sfx_6);
            }
            w->open_0 = open;
            w->frame_8 = door->seq_8[open].first_0;
        }
        else
        {
            if (!door->seq_8[open].loop_2)
            {
                goto set;
            }
            if (door->seq_8[open].sfx_3 != 0xFF && w->sfx_C == 1)
            {
                PlaySfx_80031494(door->seq_8[open].sfx_3);
                w->sfx_C = 0;
            }
            w->frame_8 = door->seq_8[w->open_0].first_0;
        }
    }
    else
    {
        w->frame_8++;
    }
set:
    SetTileLayerFrame_800B3350(w->layer_4, w->frame_8);
}

/* NONMATCHING: register allocation and one delay slot */
/* arms itself at the event point Levant faces; with the valuable its trigger is the valuable's */
void Lock_800B2900(MapEnt* ent)
{
    MapLock* lock = ent->data_10;
    MapLockWork* w = (MapLockWork*)ent->work_14;
    MapLockPoint* points = lock->points_0;
    MapLockPoint* p;
    int i = 0;

    for (p = points; p->arg_10; p++, i++)
    {
        if (IsEventPointInView_800A66A4(&p->point_0, (int*)&levantPos_8008BD18, (unsigned short*)&levantPos_8008BD18.rot) && !w->open_4
            && !FindEventScript_800A5AE4(w->script_0))
        {
            if (TestValuableFlag_800AD73C(lock->valuable_8))
            {
                ent->trigger_84 = lock->valuable_8;
            }
            w->point_8 = i;
            ent->armed_78 = 1;
        }
    }
    if (ent->state_7C == 0)
    {
        if (points[w->point_8].open_14 && TestValuableFlag_800AD73C(lock->valuable_8))
        {
            ent->trigger_84 = lock->valuable_8;
            ent->arg_8C = points[w->point_8].arg_10;
            w->script_0 = GetEventScriptId_800A5AD0(StartEventScriptForEntity_800A5AA0(lock->script_C, ent));
            w->open_4 = 1;
        }
        else
        {
            ent->trigger_84 = lock->valuable_8;
            ent->arg_8C = points[w->point_8].arg_10;
            w->script_0 = GetEventScriptId_800A5AD0(StartEventScriptForEntity_800A5AA0(lock->script_10, ent));
            w->open_4 = 0;
        }
        ent->state_7C = -1;
    }
}

void MapInit_800B2AEC(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B2CF8();
        ClearFieldMinions_800A7784();
        RequestModels_800B309C(events_800B3680);
        if (levantAnimSet_80091C74 >= 0)
        {
            LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        }
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B316C);
    }
}

void SlidingDoorInit_800B2B5C(MapEnt* ent)
{
    MapSlidingDoor* door = ent->data_10;
    MapSlidingDoorWork* w = (MapSlidingDoorWork*)ent->work_14;

    if (door->flag_14 >= 0 && TestEventFlag_800AD0D4(door->flag_14))
    {
        w->script_0 = -1;
        w->open_4 = 1;
        w->t_8 = door->frames_4C;
    }
    else
    {
        w->script_0 = -1;
        w->open_4 = 0;
        w->t_8 = 0;
    }
    SlidingDoor_800B24B4(ent);
    ent->update_90 = SlidingDoor_800B24B4;
}

void TileDoorInit_800B2BF0(MapEnt* ent)
{
    MapTileDoor* door = ent->data_10;
    MapTileDoorWork* w = (MapTileDoorWork*)ent->work_14;

    w->open_0 = TestEventFlag_800AD0D4(door->flag_0) != 0;
    w->layer_4 = FindTileLayer_800B3298(door->layer_4);
    w->frame_8 = door->seq_8[w->open_0].last_1;
    w->sfx_C = 0;
    SetTileLayerFrame_800B3350(w->layer_4, w->frame_8);
    TileDoor_800B27A4(ent);
    ent->update_90 = TileDoor_800B27A4;
}

/* NONMATCHING: the point_8 store is scheduled after the call */
void LockInit_800B2C84(MapEnt* ent)
{
    MapLock* lock = ent->data_10;
    MapLockWork* w = (MapLockWork*)ent->work_14;

    if (TestEventFlag_800AD0D4(lock->flag_4))
    {
        w->script_0 = -1;
        w->open_4 = 1;
    }
    else
    {
        w->script_0 = -1;
        w->open_4 = 0;
    }
    w->point_8 = 0;
    Lock_800B2900(ent);
    ent->update_90 = Lock_800B2900;
}

void StartMapTask_800B2CF8(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B2D28;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B2D28(EventEntry* entry, int* st)
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
        MapTask_800B2DC0(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B2DC0;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B2DC0(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = events_800B3680;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B2E78(events, currentArea_80091C44);
        st[2] += EnterArea_800B2F94(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B2E78(MapEvent* ev, int area)
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

int EnterArea_800B2F94(MapEvent* ev, int area, int prev)
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
                AddEntity_800B316C(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B309C(MapEvent* ev)
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
        entry->cb_8 = (EventEntryFn)EntityTask_800B33D4;
        return 1;
    }
    return 0;
}

int AddEntity_800B316C(void* ev)
{
    return NewEntity(ev);
}

int FindTileLayer_800B3298(int id)
{
    int set = -1;
    unsigned int i;

    for (i = 0; i < tileAnim_8008D648.count_0; i++)
    {
        if (id == tileAnim_8008D648.items_C[i].depth_0)
        {
            set = i;
            break;
        }
    }
    for (i = 0; i < tileAnim_8008D648.listCount_10; i++)
    {
        if (tileAnim_8008D648.lists_14[i].count >= 2 && set == tileAnim_8008D648.lists_14[i].items->set_0)
        {
            break;
        }
    }
    return i;
}

void SetTileLayerFrame_800B3350(int layer, int frame)
{
    TileAnimTimer* t = &tileAnim_8008D648.pairs_18[layer];

    t->frame_2 = frame;
    t->timer_0 = 0;
}

int IsTileLayerDone_800B336C(int layer, int frame)
{
    TileAnimLayer* l = &tileAnim_8008D648.lists_14[layer];
    TileAnimTimer* t = &tileAnim_8008D648.pairs_18[layer];

    if (frame != t->frame_2 || t->timer_0 + 1 >= (l->items[frame].time_2 & 0x7F))
    {
        return 1;
    }
    return 0;
}

void EntityTask_800B33D4(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}
