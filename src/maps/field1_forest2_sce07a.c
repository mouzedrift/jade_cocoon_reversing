#include "maps/map.h"

void Warp_800B2408(MapEnt* ent);
void SavePoint_800B252C(MapEnt* ent);
void Chest_800B299C(MapEnt* ent);
void ChestDraw_800B2B90(MapChest* chest, MapChestWork* w);
void MapInit_800B2E5C(int phase);
void SavePointInit_800B2EC8(MapEnt* ent);
void ChestInit_800B2F08(MapEnt* ent);
int ChestShut_800B2FE8(MapEnt* ent);
int ChestTake_800B2FF4(void* arg);
int ChestText_800B3078(void* arg);
int ChestCheck_800B30B0(MapEnt* ent);
void MeshTrigger_800B30F0(MapEnt* ent);
void StartMapTask_800B3158(void);
void MapTaskLoad_800B3188(EventEntry* entry, int* st);
void MapTask_800B3220(EventEntry* entry, int* st);
int LeaveArea_800B32D8(MapEvent* ev, int area);
int EnterArea_800B33F4(MapEvent* ev, int area, int prev);
void RequestModels_800B34FC(MapEvent* ev);
int AddEntity_800B35CC(void* ev);
void ChestKind1_800B36F8(MapChest* chest, MapChestWork* w);
void ChestKind2_800B3700(MapChest* chest, MapChestWork* w);
void EntityTask_800B3708(EventEntry* entry, MapEnt* ent);

extern const char unknown_800B22C0[4];
extern const char data_800B22C4[64];
extern const char data_800B2304[68];
extern const char str_800B2348[24];
extern const char data_800B2360[36];
extern const MapRgb savePointDim_800B2384;
extern const MapRgb savePointLit_800B2388;
extern const char data_800B238C[28];
extern const char data_800B23A8[52];
extern int text_800B3788[4];
extern MapChest chest_800B3798;
extern MapSavePoint savePoint_800B37E0;
extern MapWarp warp_800B37F0;
extern MapWarp warp_800B3808;
extern MapEvent event_800B3820;
extern int data_800B3834[3];
extern MapInstr script_800B3840[11];
extern MapEvent events_800B38F0[6];
extern int data_800B3968[3];
extern int data_800B3974[3];
extern int data_800B3980[212];

void Warp_800B2408(MapEnt* ent)
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

void SavePoint_800B252C(MapEnt* ent)
{
    int pos[3];
    short rot[4];
    int scale[3];
    MapRgb dim;
    MapRgb lit;
    MapRgb rgb;
    MapSavePoint* save;
    MapSavePointWork* w;
    FtgPolyG3List* list;
    int i;
    int alpha;
    int light;
    int near;

    save = ent->data_10;
    w = (MapSavePointWork*)ent->work_14;
    if (IsPointInViewCone_800A65F0(save->pos_0, (int*)&levantPos_8008BD18, (unsigned short*)&levantPos_8008BD18.rot, 300))
    {
        ent->armed_78 = 1;
    }
    if (ent->state_7C == 0)
    {
        saveRequest_800B06BC.active_0 = 1;
        saveRequest_800B06BC.kind_4 = 0;
        saveRequest_800B06BC.arg_8.savePlace = save->name_C;
        saveRequest_800B06BC.endOfGame_C = 0;
        ent->state_7C = -1;
    }
    list = &publicFtg_8008D4D0[1].g3_8;
    dim = savePointDim_800B2384;
    lit = savePointLit_800B2388;
    rgb.r = dim.r + (lit.r - dim.r) * w->glow_8 / 15;
    rgb.g = dim.g + (lit.g - dim.g) * w->glow_8 / 15;
    rgb.b = dim.b + (lit.b - dim.b) * w->glow_8 / 15;
    for (i = 0; i < list->count; i++)
    {
        list->items[i].c[0].r = list->items[i].c[1].r = list->items[i].c[2].r = rgb.r;
        list->items[i].c[0].g = list->items[i].c[1].g = list->items[i].c[2].g = rgb.g;
        list->items[i].c[0].b = list->items[i].c[1].b = list->items[i].c[2].b = rgb.b;
    }
    w->glow_8 = CLAMP(w->glow_8 + (ent->armed_78 ? 1 : -1), 0, 15);
    pos[0] = save->pos_0[0];
    pos[1] = save->pos_0[1] + (short)(sinTable_80084540[w->phase_4 & 0xFFF] / 163);
    pos[2] = save->pos_0[2];
    scale[0] = scale[1] = scale[2] = (sinTable_80084540[w->phase_4 & 0xFFF] + 0x1000) / 10 + 0x1000;
    rot[0] = 0;
    rot[1] = w->angle_0;
    rot[2] = 0;
    alpha = (short)sinTable_80084540[w->phase_4 & 0xFFF] / 2 + 0x1000;
    light = FindNearestCameraPoint_80019CC4(pos);
    near = ent->armed_78 != 0;
    DrawFtgObjectAtSlot0_8004D1EC(&publicFtg_8008D4D0[1], pOT_8008D690, pos, rot, &cameraState_8008D4F0.ent_44[light],
                                  (near << 5) | 0x91 | ((0x1000 - alpha) << 16), 0);
    DrawFtgObjectAtSlot0_8004D1EC(&publicFtg_8008D4D0[2], pOT_8008D690, save->pos_0, rot, &cameraState_8008D4F0.ent_44[light], 0x31, scale);
    if (ent->armed_78)
    {
        w->angle_0 += 0x40;
        w->phase_4 += 0xE2;
    }
    else
    {
        w->angle_0 += 0x20;
        w->phase_4 += 0x71;
    }
}

void Chest_800B299C(MapEnt* ent)
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
            w->script_14 = GetEventScriptId_800A5AD0(StartEventScriptForEntity_800A5AA0(data_800B3980, ent));
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
            ChestKind1_800B36F8(chest, w);
            break;
        case 2:
            ChestKind2_800B3700(chest, w);
            break;
        case 3:
            ChestDraw_800B2B90(chest, w);
            break;
        }
    }
}

void ChestDraw_800B2B90(MapChest* chest, MapChestWork* w)
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

void MapInit_800B2E5C(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B3158();
        ClearFieldMinions_800A7784();
        RequestModels_800B34FC(events_800B38F0);
        levantAnimSet_80091C74 = 45;
        LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B35CC);
    }
}

void SavePointInit_800B2EC8(MapEnt* ent)
{
    MapSavePointWork* w = (MapSavePointWork*)ent->work_14;

    w->angle_0 = 0;
    w->phase_4 = 0;
    w->glow_8 = 0;
    SavePoint_800B252C(ent);
    ent->update_90 = SavePoint_800B252C;
}

void ChestInit_800B2F08(MapEnt* ent)
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
    Chest_800B299C(ent);
    ent->update_90 = Chest_800B299C;
}

int ChestShut_800B2FE8(MapEnt* ent)
{
    return ((MapChestWork*)ent->work_14)->opened_4 == 0;
}

int ChestTake_800B2FF4(void* arg)
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
    ent->arg_8C = data_800B3968;
    return 1;
}

int ChestText_800B3078(void* arg)
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
        ent->arg_8C = data_800B3974;
    }
    return 0;
}

int ChestCheck_800B30B0(MapEnt* ent)
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

/* arms the entity's trigger while Levant stands on area mesh 3 */
void MeshTrigger_800B30F0(MapEnt* ent)
{
    if (FindTriAtXZ_800B76B8((char*)&mapState_8008B500.meshes_C[3], (int*)&levantPos_8008BD18) >= 0)
    {
        ent->trigger_84 = 0x40000007;
        ent->armed_78 = 1;
    }
    ent->prev_80 = -1;
    if (ent->state_7C == 0)
    {
        ent->state_7C = -1;
        ent->prev_80 = 0;
    }
}

void StartMapTask_800B3158(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B3188;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B3188(EventEntry* entry, int* st)
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
        MapTask_800B3220(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B3220;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B3220(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = events_800B38F0;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B32D8(events, currentArea_80091C44);
        st[2] += EnterArea_800B33F4(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B32D8(MapEvent* ev, int area)
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

int EnterArea_800B33F4(MapEvent* ev, int area, int prev)
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
                AddEntity_800B35CC(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B34FC(MapEvent* ev)
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
        entry->cb_8 = (EventEntryFn)EntityTask_800B3708;
        return 1;
    }
    return 0;
}

int AddEntity_800B35CC(void* ev)
{
    return NewEntity(ev);
}

void ChestKind1_800B36F8(MapChest* chest, MapChestWork* w)
{
}

void ChestKind2_800B3700(MapChest* chest, MapChestWork* w)
{
}

void EntityTask_800B3708(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}
