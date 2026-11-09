#include "maps/map.h"

void Warp_800B2420(MapEnt* ent);
int AddEffects_800B2544(MapFx* fx);
int fn_800B26D0();
void FxModel_800B2844(MapEnt* ent);
int fn_800B2A6C();
int fn_800B2D54();
void Chest_800B31C4(MapEnt* ent);
void ChestDraw_800B33B8(MapChest* chest, MapChestWork* w);
void MapInit_800B3684(int phase);
void FxInit_800B36F4(MapEnt* ent);
int fn_800B37AC();
int fn_800B37E8();
int fn_800B3920();
void ChestInit_800B3960(MapEnt* ent);
int ChestShut_800B3A40(MapEnt* ent);
int ChestTake_800B3A4C(void* arg);
int ChestText_800B3AD0(void* arg);
int ChestCheck_800B3B08(MapEnt* ent);
void StartMapTask_800B3B48(void);
void MapTaskLoad_800B3B78(EventEntry* entry, int* st);
void MapTask_800B3C10(EventEntry* entry, int* st);
int LeaveArea_800B3CC8(MapEvent* ev, int area);
int EnterArea_800B3DE4(MapEvent* ev, int area, int prev);
void RequestModels_800B3EEC(MapEvent* ev);
void EntityTask_800B3FBC(EventEntry* entry, MapEnt* ent);
int AddEntity_800B403C(void* ev);
int FxFrame_800B4168(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B41EC(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B42B8(MapFx* fx, MapFxWork* w);
void ChestKind1_800B4400(MapChest* chest, MapChestWork* w);
void ChestKind2_800B4408(MapChest* chest, MapChestWork* w);

extern const char unknown_800B22C0[4];
extern const char data_800B22C4[44];
extern const char data_800B22F0[72];
extern const char data_800B2338[20];
extern const MapFxInits fxInits_800B234C;
extern const int data_800B2360[4];
extern const int data_800B2370[5];
extern const char data_800B2398[4];
extern const char data_800B239C[4];
extern const char data_800B23A0[28];
extern const char data_800B23BC[56];
extern int text_800B4410[4];
extern MapChest chest_800B4420;
extern int data_800B4468[4];
extern MapWarp warp_800B4478;
extern int data_800B4490[10];
extern MapEvent events_800B44B8[5];
extern int data_800B451C[66];
extern int data_800B4624[33];
extern int data_800B46A8[72];
extern int data_800B47C8[56];
extern int data_800B48A8[3];
extern int data_800B48B4[3];
extern int data_800B48C0[212];

void Warp_800B2420(MapEnt* ent)
{
    MapWarp* warp;
    LevantPos* levant;

    warp = ent->data_10;
    if (fieldMode_800B0EC0 == 1 && !(battleFlags_800B1228 & 0x4000))
    {
        levant = &saveData_8008B570.levant_7A8;
        if (IsEventPointValid_800A6504(warp->point_10, (int*)levant))
        {
            savedLevantPos_80091C78[0] = warp->pos_0[0];
            savedLevantPos_80091C78[1] = warp->pos_0[1];
            savedLevantPos_80091C78[2] = warp->pos_0[2];
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
        entry->cb_8 = (EventEntryFn)EntityTask_800B3FBC;
        return 1;
    }
    return 0;
}

/* NONMATCHING: AddEffects_800B2994's C does not compile to its code yet */
int AddEffects_800B2544(MapFx* fx)
{
    MapEvent ev;

    while (fx->type_0 != MAP_FX_END)
    {
        ev.areas_0 = -1;
        ev.type_4 = 7;
        ev.data_8 = fx;
        ev.size_C = 0x20;
        ev.run_10.init = FxInit_800B36F4;
        NewEntity(&ev);
        fx++;
    }
    return 1;
}

/* TODO: not decompiled yet (93 words) */
int fn_800B26D0()
{
    return 0;
}

/* NONMATCHING: FxModel_800B2B20's C does not compile to its code yet */
void FxModel_800B2844(MapEnt* ent)
{
    int pos[3];
    short rot[3];
    MapFx* fx;
    MapFxWork* w;
    EffectModel* model;
    EffectKey* key;
    int frame;
    int i;
    int light;

    fx = ent->data_10;
    w = (MapFxWork*)ent->work_14;
    model = &w->file_0->models_28[FindEffectIndex_80020F00(w->file_0, 1, fx->id_2)];
    frame = FxFrame_800B4168(fx, w, model->frameCount_14);
    FxTime_800B41EC(ent, fx, w);
    FxPlace_800B42B8(fx, w);
    if (frame >= 0)
    {
        for (i = 0; i < model->keyCount_10; i++)
        {
            key = &model->keys_18[frame * model->keyCount_10] + i;
            pos[0] = w->pos_4[0];
            pos[1] = w->pos_4[1];
            pos[2] = w->pos_4[2];
            pos[0] += key->x_4;
            pos[1] += key->y_8;
            pos[2] += key->z_C;
            rot[0] = w->rot_10[0];
            rot[1] = w->rot_10[1];
            rot[2] = w->rot_10[2];
            rot[0] += key->rot_10[0];
            rot[1] += key->rot_10[1];
            rot[2] += key->rot_10[2];
            light = FindNearestCameraPoint_80019CC4(pos);
            DrawFtgObjectAtSlot0_8004D1EC(&model->ftg_4[key->model_0], pOT_8008D690, pos, rot, &cameraState_8008D4F0.ent_44[light],
                                          ((0x1000 - key->alpha_2) << 16) | (key->mode_24 | 0x80), key->f18);
        }
    }
}

/* TODO: not decompiled yet (186 words) */
int fn_800B2A6C()
{
    return 0;
}

/* TODO: not decompiled yet (284 words) */
int fn_800B2D54()
{
    return 0;
}

void Chest_800B31C4(MapEnt* ent)
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
            w->script_14 = GetEventScriptId_800A5AD0(StartEventScriptForEntity_800A5AA0(data_800B48C0, ent));
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
            ChestKind1_800B4400(chest, w);
            break;
        case 2:
            ChestKind2_800B4408(chest, w);
            break;
        case 3:
            ChestDraw_800B33B8(chest, w);
            break;
        }
    }
}

void ChestDraw_800B33B8(MapChest* chest, MapChestWork* w)
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

void MapInit_800B3684(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B3B48();
        ClearFieldMinions_800A7784();
        RequestModels_800B3EEC(events_800B44B8);
        if (levantAnimSet_80091C74 >= 0)
        {
            LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        }
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B403C);
    }
}

void FxInit_800B36F4(MapEnt* ent)
{
    MapFxInits inits = fxInits_800B234C;
    MapFx* fx;
    MapFxWork* w;

    fx = ent->data_10;
    w = (MapFxWork*)ent->work_14;
    w->file_0 = GetEventDataSlot_800A55B0(0);
    w->time_18 = 0;
    w->delay_1A = 0;
    w->runs_1C = 0;
    w->pos_4[0] = 0;
    w->pos_4[1] = 0;
    w->pos_4[2] = 0;
    w->rot_10[0] = 0;
    w->rot_10[1] = 0;
    w->rot_10[2] = 0;
    ent->update_90 = inits.init[fx->type_0];
    ent->update_90(ent);
}

/* TODO: not decompiled yet (15 words) */
int fn_800B37AC()
{
    return 0;
}

/* TODO: not decompiled yet (78 words) */
int fn_800B37E8()
{
    return 0;
}

/* TODO: not decompiled yet (16 words) */
int fn_800B3920()
{
    return 0;
}

void ChestInit_800B3960(MapEnt* ent)
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
    Chest_800B31C4(ent);
    ent->update_90 = Chest_800B31C4;
}

int ChestShut_800B3A40(MapEnt* ent)
{
    return ((MapChestWork*)ent->work_14)->opened_4 == 0;
}

int ChestTake_800B3A4C(void* arg)
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
    ent->arg_8C = data_800B48A8;
    return 1;
}

int ChestText_800B3AD0(void* arg)
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
        ent->arg_8C = data_800B48B4;
    }
    return 0;
}

int ChestCheck_800B3B08(MapEnt* ent)
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

void StartMapTask_800B3B48(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B3B78;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B3B78(EventEntry* entry, int* st)
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
        MapTask_800B3C10(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B3C10;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B3C10(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = events_800B44B8;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B3CC8(events, currentArea_80091C44);
        st[2] += EnterArea_800B3DE4(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B3CC8(MapEvent* ev, int area)
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

int EnterArea_800B3DE4(MapEvent* ev, int area, int prev)
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
                AddEntity_800B403C(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B3EEC(MapEvent* ev)
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

void EntityTask_800B3FBC(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}

int AddEntity_800B403C(void* ev)
{
    return NewEntity(ev);
}

int FxFrame_800B4168(MapFx* fx, MapFxWork* w, int count)
{
    int end;
    int length;

    if (fx->delay_1A <= w->delay_1A)
    {
        end = count;
        if (fx->last_22 >= 0)
        {
            end = fx->last_22 + 1;
        }
        length = count;
        if (fx->length_18 >= 0)
        {
            length = fx->length_18;
        }
        return (fx->first_1E + (end - fx->first_1E) * w->time_18 / length) % count;
    }
    return -1;
}

void FxTime_800B41EC(MapEnt* ent, MapFx* fx, MapFxWork* w)
{
    int delay;

    delay = fx->delay_1A;
    if (w->delay_1A < delay)
    {
        w->delay_1A = CLAMP(w->delay_1A + 1, 0, delay);
        return;
    }
    if (++w->time_18 >= fx->length_18)
    {
        if (fx->runs_1C >= 0 && w->runs_1C >= fx->runs_1C)
        {
            if (fx->type_0 == 4)
            {
                pointLightRange_8008D3F0 = 0;
            }
            ent->state_7C = -2;
        }
        w->time_18 = fx->restart_20;
        w->runs_1C++;
    }
}

void FxPlace_800B42B8(MapFx* fx, MapFxWork* w)
{
    int pos[3];
    short rot[3];

    if (fx->place_28)
    {
        fx->place_28(pos, rot);
        w->pos_4[0] = pos[0];
        w->pos_4[1] = pos[1];
        w->pos_4[2] = pos[2];
        w->pos_4[0] += fx->pos_4[0];
        w->pos_4[1] += fx->pos_4[1];
        w->pos_4[2] += fx->pos_4[2];
        w->rot_10[0] = rot[0];
        w->rot_10[1] = rot[1];
        w->rot_10[2] = rot[2];
        w->rot_10[0] += fx->rot_10[0];
        w->rot_10[1] += fx->rot_10[1];
        w->rot_10[2] += fx->rot_10[2];
    }
    else
    {
        w->pos_4[0] = fx->pos_4[0];
        w->pos_4[1] = fx->pos_4[1];
        w->pos_4[2] = fx->pos_4[2];
        w->rot_10[0] = fx->rot_10[0];
        w->rot_10[1] = fx->rot_10[1];
        w->rot_10[2] = fx->rot_10[2];
    }
}

void ChestKind1_800B4400(MapChest* chest, MapChestWork* w)
{
}

void ChestKind2_800B4408(MapChest* chest, MapChestWork* w)
{
}
