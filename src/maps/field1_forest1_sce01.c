#include "maps/map.h"

void Warp_800B23D0(MapEnt* ent);
void TileDoor_800B24F4(MapEnt* ent);
void Chest_800B2650(MapEnt* ent);
void ChestDraw_800B2844(MapChest* chest, MapChestWork* w);
void MapInit_800B2B10(int phase);
void SwitchInit_800B2B80(MapEnt* ent);
void Switch_800B2BDC(MapEnt* ent);
void TileDoorInit_800B2C94(MapEnt* ent);
void WallFlagsInit_800B2D28(MapEnt* ent);
void ChestInit_800B2DC0(MapEnt* ent);
int ChestShut_800B2EA0(MapEnt* ent);
int ChestTake_800B2EAC(void* arg);
int ChestText_800B2F30(void* arg);
int ChestCheck_800B2F68(MapEnt* ent);
void StartMapTask_800B2FA8(void);
void MapTaskLoad_800B2FD8(EventEntry* entry, int* st);
void MapTask_800B3070(EventEntry* entry, int* st);
int LeaveArea_800B3128(MapEvent* ev, int area);
int EnterArea_800B3244(MapEvent* ev, int area, int prev);
void RequestModels_800B334C(MapEvent* ev);
int AddEntity_800B341C(void* ev);
int FindTileLayer_800B3548(int id);
void SetTileLayerFrame_800B3600(int layer, int frame);
int IsTileLayerDone_800B361C(int layer, int frame);
void ChestKind1_800B3684(MapChest* chest, MapChestWork* w);
void ChestKind2_800B368C(MapChest* chest, MapChestWork* w);
void EntityTask_800B3694(EventEntry* entry, MapEnt* ent);

extern const char unknown_800B22C0[4];
extern const char data_800B22C4[40];
extern const char data_800B22EC[44];
extern const char data_800B2318[56];
extern const char data_800B2350[28];
extern const char data_800B236C[56];
extern int text_800B3714[4];
extern MapChest chest_800B3724;
extern MapWarp warp_800B376C;
extern MapWarp warp_800B3784;
extern MapWarp warp_800B379C;
extern MapWarp warp_800B37B4;
extern MapSwitch data_800B37CC;
extern MapTileDoor data_800B37E4;
extern MapWallFlag data_800B37F4[2];
extern MapEvent events_800B3804[9];
extern int data_800B38B8[3];
extern int data_800B38C4[3];
extern int data_800B38D0[212];

void Warp_800B23D0(MapEnt* ent)
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

void TileDoor_800B24F4(MapEnt* ent)
{
    MapTileDoor* door = ent->data_10;
    MapTileDoorWork* w = (MapTileDoorWork*)ent->work_14;
    int open;

    if (!IsTileLayerDone_800B361C(w->layer_4, w->frame_8))
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
    SetTileLayerFrame_800B3600(w->layer_4, w->frame_8);
}

void Chest_800B2650(MapEnt* ent)
{
    MapChestWork* w;
    MapChest* chest;
    int seen;

    w = (MapChestWork*)ent->work_14;
    chest = ent->data_10;
    seen = IsEventPointInView_800A66A4(&chest->point_10, (int*)&levantPos_8008BD18, (unsigned short*)&levantPos_8008BD18.rot);
    if (seen == 1 && !FindEventScript_800A5AE4(w->script_14))
    {
        ent->armed_78 = seen;
    }
    switch (ent->state_7C)
    {
    case 0:
        if (w->full_0)
        {
            ent->arg_8C = ent;
            w->script_14 = GetEventScriptId_800A5AD0(StartEventScriptForEntity_800A5AA0(data_800B38D0, ent));
            ent->prev_80 = ent->state_7C;
            ent->state_7C = -1;
        }
        break;
    case 1:
        SetEventFlag_800AD0F8(chest->flag_0);
        w->full_0 = (chest->flags_C >> 2) & 1;
        w->opened_4 = 1;
        ent->prev_80 = ent->state_7C;
        ent->state_7C = -1;
        break;
    case 2:
        w->draw_8 = (chest->flags_C ^ 1) & 1;
        ent->prev_80 = ent->state_7C;
        ent->state_7C = -1;
        break;
    case 3:
        w->opening_C = 1;
        if (!(chest->flags_C & MAP_CHEST_WAIT) || w->lid_10 >= 10)
        {
            ent->prev_80 = ent->state_7C;
            ent->state_7C = -1;
        }
        break;
    case 4:
        ent->arg_8C = ent;
        ent->prev_80 = ent->state_7C;
        ent->state_7C = -1;
        break;
    }
    if (w->draw_8)
    {
        switch (chest->kind_8)
        {
        case 0:
            break;
        case 1:
            ChestKind1_800B3684(chest, w);
            break;
        case 2:
            ChestKind2_800B368C(chest, w);
            break;
        case 3:
            ChestDraw_800B2844(chest, w);
            break;
        }
    }
}

void ChestDraw_800B2844(MapChest* chest, MapChestWork* w)
{
    int offset[2][3] = { { 0, 0, 0 }, { 0x4A, -0x37, 1 } };
    int angle[2] = { 0, 0x400 };
    int pos[3];
    short rot[3];
    int t;
    int lid;
    int i;
    int ftg;
    int light;

    t = w->lid_10 + (w->opening_C != 0);
    if (t >= 0)
    {
        lid = t;
        if (lid >= 11)
        {
            lid = 10;
        }
    }
    else
    {
        lid = 0;
    }
    w->lid_10 = lid;
    for (i = 0; i < 2; i++)
    {
        ftg = chest->ftg_44[i];
        if (ftg < 0)
        {
            break;
        }
        pos[0] = chest->pos_14[0] + offset[i][0] * sinTable_80084540[(chest->rotY_20 + 0x400) & 0xFFF] / 4096 +
                 offset[i][2] * sinTable_80084540[chest->rotY_20 & 0xFFF] / 4096;
        pos[1] = chest->pos_14[1] + offset[i][1];
        pos[2] = chest->pos_14[2] - offset[i][0] * sinTable_80084540[chest->rotY_20 & 0xFFF] / 4096 +
                 offset[i][2] * sinTable_80084540[(chest->rotY_20 + 0x400) & 0xFFF] / 4096;
        rot[0] = 0;
        rot[1] = chest->rotY_20;
        rot[2] = angle[i] * w->lid_10 / 10;
        light = FindNearestCameraPoint_80019CC4(pos);
        DrawFtgObjectAtSlot0_8004D1EC(&mapState_8008B500.ftg_3C[ftg], pOT_8008D690, pos, rot, &cameraState_8008D4F0.ent_44[light], 1, 0);
    }
}

void MapInit_800B2B10(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B2FA8();
        ClearFieldMinions_800A7784();
        RequestModels_800B334C(events_800B3804);
        if (levantAnimSet_80091C74 >= 0)
        {
            LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        }
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B341C);
    }
}

void SwitchInit_800B2B80(MapEnt* ent)
{
    MapSwitch* sw = ent->data_10;

    if (TestEventFlag_800AD0D4(sw->flag_0))
    {
        ent->work_14[0] = 1;
    }
    else
    {
        ent->work_14[0] = 0;
    }
    Switch_800B2BDC(ent);
    ent->update_90 = Switch_800B2BDC;
}

/* work_14[0]: its flag is set */
void Switch_800B2BDC(MapEnt* ent)
{
    MapSwitch* sw = ent->data_10;
    int* on = ent->work_14;

    if (IsEventPointInView_800A66A4(&sw->point_8, (int*)&levantPos_8008BD18, (unsigned short*)&levantPos_8008BD18.rot))
    {
        ent->armed_78 = 1;
    }
    if (ent->state_7C == 0)
    {
        if (ent->work_14[0] == 1 && sw->mode_4 == 1)
        {
            ClearEventFlag_800AD124(sw->flag_0);
            ent->work_14[0] = 0;
        }
        else
        {
            SetEventFlag_800AD0F8(sw->flag_0);
            *on = 1;
        }
        ent->state_7C = -1;
    }
}

void TileDoorInit_800B2C94(MapEnt* ent)
{
    MapTileDoor* door = ent->data_10;
    MapTileDoorWork* w = (MapTileDoorWork*)ent->work_14;

    w->open_0 = TestEventFlag_800AD0D4(door->flag_0) != 0;
    w->layer_4 = FindTileLayer_800B3548(door->layer_4);
    w->frame_8 = door->seq_8[w->open_0].last_1;
    w->sfx_C = 0;
    SetTileLayerFrame_800B3600(w->layer_4, w->frame_8);
    TileDoor_800B24F4(ent);
    ent->update_90 = TileDoor_800B24F4;
}

/* turns the walls on while their flags are clear */
void WallFlagsInit_800B2D28(MapEnt* ent)
{
    MapWallFlag* w;
    int on;

    for (w = ent->data_10; w->kind_4 != 2; w++)
    {
        on = !TestEventFlag_800AD0D4(w->flag_0);
        if (w->kind_4 == 0)
        {
            SetLevantWallEnabled_800A6534(w->wall_6, on);
        }
        else
        {
            SetActorWallEnabled_800A654C(w->wall_6, on);
        }
    }
}

void ChestInit_800B2DC0(MapEnt* ent)
{
    MapChest* chest;
    MapChestWork* w;

    chest = ent->data_10;
    w = (MapChestWork*)ent->work_14;
    if ((chest->flags_C & MAP_CHEST_ONCE) && chest->flag_0 >= 0 && !TestEventFlag_800AD0D4(chest->flag_0))
    {
        w->script_14 = -1;
        w->opening_C = 0;
        w->lid_10 = 0;
        w->draw_8 = 1;
        w->full_0 = 1;
        w->opened_4 = 0;
    }
    else
    {
        w->script_14 = -1;
        w->opening_C = 1;
        w->lid_10 = 10;
        w->draw_8 = (chest->flags_C ^ 1) & 1;
        w->full_0 = (chest->flags_C >> 2) & 1;
        w->opened_4 = 1;
    }
    Chest_800B2650(ent);
    ent->update_90 = Chest_800B2650;
}

int ChestShut_800B2EA0(MapEnt* ent)
{
    return ((MapChestWork*)ent->work_14)->opened_4 == 0;
}

int ChestTake_800B2EAC(void* arg)
{
    MapEnt* ent;
    MapChest* chest;

    ent = arg;
    chest = ent->data_10;
    if (chest->item_4 < 0)
    {
        ent->arg_8C = chest->text_24;
        return 2;
    }
    if (GetInventoryCount_800AD254(chest->item_4, 0))
    {
        ent->trigger_84 = chest->item_4;
        return 0;
    }
    ent->arg_8C = data_800B38B8;
    return 1;
}

int ChestText_800B2F30(void* arg)
{
    MapEnt* ent;
    MapChest* chest;

    ent = arg;
    chest = ent->data_10;
    if (chest->item_4 < 0)
    {
        ent->arg_8C = chest->text_28;
    }
    else
    {
        ent->arg_8C = data_800B38C4;
    }
    return 0;
}

int ChestCheck_800B2F68(MapEnt* ent)
{
    MapChest* chest;
    MapChestWork* w;

    chest = ent->data_10;
    w = (MapChestWork*)ent->work_14;
    if ((chest->flags_C & MAP_CHEST_ONCE) && !w->opened_4)
    {
        ent->arg_8C = chest->f2C;
        return 0;
    }
    return 1;
}

void StartMapTask_800B2FA8(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B2FD8;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B2FD8(EventEntry* entry, int* st)
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
        MapTask_800B3070(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B3070;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B3070(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = events_800B3804;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B3128(events, currentArea_80091C44);
        st[2] += EnterArea_800B3244(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B3128(MapEvent* ev, int area)
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

int EnterArea_800B3244(MapEvent* ev, int area, int prev)
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
                AddEntity_800B341C(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B334C(MapEvent* ev)
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
        entry->cb_8 = (EventEntryFn)EntityTask_800B3694;
        return 1;
    }
    return 0;
}

int AddEntity_800B341C(void* ev)
{
    return NewEntity(ev);
}

int FindTileLayer_800B3548(int id)
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

void SetTileLayerFrame_800B3600(int layer, int frame)
{
    TileAnimTimer* t = &tileAnim_8008D648.pairs_18[layer];

    t->frame_2 = frame;
    t->timer_0 = 0;
}

int IsTileLayerDone_800B361C(int layer, int frame)
{
    TileAnimLayer* l = &tileAnim_8008D648.lists_14[layer];
    TileAnimTimer* t = &tileAnim_8008D648.pairs_18[layer];

    if (frame != t->frame_2 || t->timer_0 + 1 >= (l->items[frame].time_2 & 0x7F))
    {
        return 1;
    }
    return 0;
}

void ChestKind1_800B3684(MapChest* chest, MapChestWork* w)
{
}

void ChestKind2_800B368C(MapChest* chest, MapChestWork* w)
{
}

void EntityTask_800B3694(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}
