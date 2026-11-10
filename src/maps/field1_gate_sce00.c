#include "maps/map.h"

void Warp_800B2348(MapEnt* ent);
void GateSpot_800B246C(MapEnt* ent);
int AddEffects_800B26BC(MapFx* fx);
void FxModel_800B2848(MapEnt* ent);
void SavePoint_800B2A70(MapEnt* ent);
void MapInit_800B2EE0(int phase);
void ScriptSpot_800B30C0(MapEnt* ent);
void FxInit_800B3134(MapEnt* ent);
void FxMdec_800B31EC(MapEnt* ent);
void GateSpotInit_800B32D8(MapEnt* ent);
void GateReturnInit_800B3320(MapEnt* ent);
void GateReturn_800B339C(MapEnt* ent);
void SavePointInit_800B340C(MapEnt* ent);
void StartMapTask_800B344C(void);
void MapTaskLoad_800B347C(EventEntry* entry, int* st);
void MapTask_800B3514(EventEntry* entry, int* st);
int LeaveArea_800B35CC(MapEvent* ev, int area);
int EnterArea_800B36E8(MapEvent* ev, int area, int prev);
void RequestModels_800B37F0(MapEvent* ev);
void EntityTask_800B38C0(EventEntry* entry, MapEnt* ent);
int AddEntity_800B3940(void* ev);
void MapInit_800B3A6C(int phase);
int StopLevantIfSet_800B3ADC(MapScriptSpot* spot);
int FxFrame_800B3B0C(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B3B90(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B3C5C(MapFx* fx, MapFxWork* w);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[28];
extern const MapFxInits fxInits_800B22E0;
extern const MapRgb savePointDim_800B22F4;
extern const MapRgb savePointLit_800B22F8;
extern MapSavePoint savePoint_800B3DA4;
extern int data_800B3DB4[2];
extern MapWarp warp_800B3DBC;
extern MapWarp warp_800B3DD4;
extern MapWarp warp_800B3DEC;
extern MapWarp warp_800B3E04;
extern MapFx effects_800B3E1C[3];
extern MapFx effects_800B3EA0[3];
extern MapFx effects_800B3F24[3];
extern MapFx effects_800B3FA8[3];
extern MapFx effects_800B402C[3];
extern MapFx effects_800B40B0[3];
extern MapFx effects_800B4134[3];
extern MapFx effects_800B41B8[3];
extern MapGateSpot data_800B423C;
extern MapGateSpot data_800B4270;
extern MapGateSpot data_800B42A4;
extern MapGateSpot data_800B42D8;
extern MapGateSpot data_800B430C;
extern MapGateSpot data_800B4340;
extern MapGateSpot data_800B4374;
extern MapGateSpot data_800B43A8;
extern MapGateReturn data_800B43DC;
extern MapGateReturn data_800B43E4;
extern MapGateReturn data_800B43EC;
extern MapGateReturn data_800B43F4;
extern MapGateReturn data_800B43FC;
extern MapGateReturn data_800B4404;
extern MapGateReturn data_800B440C;
extern MapGateReturn data_800B4414;
extern MapEvent events_800B441C[23];
extern int data_800B45E8[16];
extern int data_800B4628[104];
extern int data_800B47C8[24];
extern int data_800B4828[84];

void Warp_800B2348(MapEnt* ent)
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

void GateSpot_800B246C(MapEnt* ent)
{
    MapGateSpot* gate = ent->data_10;
    MapGateSpotWork* w = (MapGateSpotWork*)ent->work_14;
    SaveMapVar key;
    void* script;

    if (IsEventPointInView_800A66A4(&gate->point_4, (int*)&levantPos_8008BD18, (unsigned short*)&levantPos_8008BD18.rot) && !w->open_C
        && !FindEventScript_800A5AE4(ent->work_14[0]))
    {
        int valuable = gate->valuable_0;

        ent->armed_78 = 1;
        ent->trigger_84 = valuable;
    }
    if (w->fx_8 && !FindEventEntity_800A5DDC(MAP_ADDR(w->fx_8), 1, 0))
    {
        FreeMdecBuffer_800A5854();
        w->fx_8 = 0;
    }
    switch (ent->state_7C)
    {
    case 0:
        if (TestValuableFlag_800AD73C(gate->valuable_0))
        {
            script = data_800B4628;
            w->open_C = 1;
        }
        else
        {
            script = data_800B47C8;
        }
        ent->trigger_84 = gate->valuable_0;
        w->script_0 = GetEventScriptId_800A5AD0(StartEventScriptForEntity_800A5AA0(script, ent));
        ent->state_7C = -1;
        return;
    case 1:
        FreeMdecBuffer_800A5854();
        AllocMdecBuffer_800A5804(1);
        AddEffects_800B26BC(w->fx_8 = w->turn_4 == 0 ? gate->fx_28[0] : gate->fx_28[1]);
        w->turn_4 = (w->turn_4 + 1) & 1;
        break;
    case 2:
        if (w->fx_8)
        {
            return;
        }
        if (gate->mapVar_30 >= 0)
        {
            key.area_0 = 4;
            key.map_2 = gate->mapVar_30;
            key.sub_4 = 0;
            if (GetMapVar_800ADC1C(&key.area_0) == -1)
            {
                SetMapVar_800ADC5C((unsigned short*)&key.area_0, gate->value_32);
            }
        }
        PlayMusic_800300E0(gate->music_24, 1);
        SetBattleMusic_800315D8(gate->music_24);
        SetLoadFadeFlag_80027478(4, 1);
        saveData_8008B570.levant_7A8.pos.x = gate->dest_14[0];
        saveData_8008B570.levant_7A8.pos.y = gate->dest_14[1];
        saveData_8008B570.levant_7A8.pos.z = gate->dest_14[2];
        saveData_8008B570.levant_7A8.rot.vy = gate->rotY_20;
        w->open_C = 0;
        break;
    default:
        return;
    }
    ent->prev_80 = ent->state_7C;
    ent->state_7C = -1;
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
        entry->cb_8 = (EventEntryFn)EntityTask_800B38C0;
        return 1;
    }
    return 0;
}

/* NONMATCHING: AddEffects_800B2544's C does not compile to its code yet */
int AddEffects_800B26BC(MapFx* fx)
{
    MapEvent ev;

    while (fx->type_0 != MAP_FX_END)
    {
        ev.areas_0 = -1;
        ev.type_4 = 7;
        ev.data_8 = fx;
        ev.size_C = 0x20;
        ev.run_10.init = FxInit_800B3134;
        NewEntity(&ev);
        fx++;
    }
    return 1;
}

void FxModel_800B2848(MapEnt* ent)
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
    frame = FxFrame_800B3B0C(fx, w, model->frameCount_14);
    FxTime_800B3B90(ent, fx, w);
    FxPlace_800B3C5C(fx, w);
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
                                          ((0x1000 - key->alpha_2) << 16) | 0x80 | key->mode_24, key->f18);
        }
    }
}

void SavePoint_800B2A70(MapEnt* ent)
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
    dim = savePointDim_800B22F4;
    lit = savePointLit_800B22F8;
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

/* phase 0: Levant comes back out of the gate event var 4 names; else the music of the mesh */
void MapInit_800B2EE0(int phase)
{
    MapGateSpot* gate;

    if (phase == 0)
    {
        gate = 0;
        switch (GetEventVar_800AD154(4))
        {
        case 0:
            gate = 0;
            break;
        case 1:
            gate = &data_800B423C;
            break;
        case 2:
            gate = &data_800B4270;
            break;
        case 3:
            gate = &data_800B42A4;
            break;
        case 4:
            gate = &data_800B42D8;
            break;
        case 5:
            gate = &data_800B430C;
            break;
        case 6:
            gate = &data_800B4340;
            break;
        case 7:
            gate = &data_800B4374;
            break;
        case 8:
            gate = &data_800B43A8;
            break;
        }
        if (gate)
        {
            saveData_8008B570.levant_7A8.pos.x = gate->dest_14[0];
            saveData_8008B570.levant_7A8.pos.y = gate->dest_14[1];
            saveData_8008B570.levant_7A8.pos.z = gate->dest_14[2];
            saveData_8008B570.levant_7A8.rot.vy = gate->rotY_20;
            SetLevantVisible_800ABBD8(0);
            useMapStartPos_80091C94 = 0;
        }
    }
    else
    {
        int music[9] = { 0x16, 0x16, 0x16, 0x16, 0x16, 0x11, 0x1A, 0x20, 0x1F };
        int m = music[saveData_8008B570.mapId_2E4[3].cur_0];

        PlayMusic_800300E0(m, 1);
        SetBattleMusic_800315D8(m);
    }
    if (phase == 1)
    {
        StartMapTask_800B344C();
        ClearFieldMinions_800A7784();
        RequestModels_800B37F0(events_800B441C);
        if (levantAnimSet_80091C74 >= 0)
        {
            LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        }
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B3940);
    }
}

void ScriptSpot_800B30C0(MapEnt* ent)
{
    MapScriptSpot* spot = ent->data_10;

    if (fieldMode_800B0EC0 == 1 && IsEventPointValid_800A6504(spot->point_0, (int*)&levantPos_8008BD18) && !ent->arg_8C)
    {
        ent->arg_8C = spot;
        StartEventScript_800A59D0(data_800B45E8);
    }
}

void FxInit_800B3134(MapEnt* ent)
{
    MapFxInits inits = fxInits_800B22E0;
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

void FxMdec_800B31EC(MapEnt* ent)
{
    MapFx* fx;
    MapFxWork* w;
    MdecImageSet* set;
    int frame;

    fx = ent->data_10;
    w = (MapFxWork*)ent->work_14;
    set = &w->file_0->imageSets_30[FindEffectIndex_80020F00(w->file_0, 2, fx->id_2)];
    frame = FxFrame_800B3B0C(fx, w, set->count_0);
    FxTime_800B3B90(ent, fx, w);
    if (frame >= 0 && !(unknownFlags_8008D678 & 0x800))
    {
        mdecEffectVlcBuffer_8008D42C = w->file_0->mdec_34.dct_0;
        decodedImageData_8008B4A0 = w->file_0->mdec_34.work_4;
        DecodeMdec_80041920(set->images_4[frame], mdecEffectVlcBuffer_8008D42C, fx->arg_24);
        unknownFlags_8008D678 |= 0x800;
    }
}

void GateSpotInit_800B32D8(MapEnt* ent)
{
    MapGateSpotWork* w = (MapGateSpotWork*)ent->work_14;

    w->script_0 = -1;
    w->turn_4 = 0;
    w->open_C = 0;
    w->fx_8 = 0;
    GateSpot_800B246C(ent);
    ent->update_90 = GateSpot_800B246C;
}

void GateReturnInit_800B3320(MapEnt* ent)
{
    MapGateReturn* ret = ent->data_10;

    if (ret->var_0 == GetEventVar_800AD154(4))
    {
        ent->work_14[0] = GetEventScriptId_800A5AD0(StartEventScriptForEntity_800A5AA0(data_800B4828, ent));
        GateReturn_800B339C(ent);
        ent->update_90 = GateReturn_800B339C;
    }
    else
    {
        ent->state_7C = -2;
    }
}

/* state 0: play the effects; 1, 2: done (event var 4 cleared) */
void GateReturn_800B339C(MapEnt* ent)
{
    MapGateReturn* ret = ent->data_10;

    if (ent->state_7C == 0)
    {
        AddEffects_800B26BC(ret->fx_4);
        ent->prev_80 = ent->state_7C;
        ent->state_7C = -1;
    }
    else if (ent->state_7C >= 0)
    {
        if (ent->state_7C < 3)
        {
            SetEventVar_800AD16C(4, 0);
            ent->state_7C = -2;
        }
    }
}

void SavePointInit_800B340C(MapEnt* ent)
{
    MapSavePointWork* w = (MapSavePointWork*)ent->work_14;

    w->angle_0 = 0;
    w->phase_4 = 0;
    w->glow_8 = 0;
    SavePoint_800B2A70(ent);
    ent->update_90 = SavePoint_800B2A70;
}

void StartMapTask_800B344C(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B347C;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B347C(EventEntry* entry, int* st)
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
        MapTask_800B3514(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B3514;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B3514(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = events_800B441C;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B35CC(events, currentArea_80091C44);
        st[2] += EnterArea_800B36E8(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B35CC(MapEvent* ev, int area)
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

int EnterArea_800B36E8(MapEvent* ev, int area, int prev)
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
                AddEntity_800B3940(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B37F0(MapEvent* ev)
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

void EntityTask_800B38C0(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}

int AddEntity_800B3940(void* ev)
{
    return NewEntity(ev);
}

void MapInit_800B3A6C(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B344C();
        ClearFieldMinions_800A7784();
        RequestModels_800B37F0(events_800B441C);
        if (levantAnimSet_80091C74 >= 0)
        {
            LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        }
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B3940);
    }
}

int StopLevantIfSet_800B3ADC(MapScriptSpot* spot)
{
    if (spot->idle_2)
    {
        ResetLevantActorToIdle_800A8DEC();
    }
    return 1;
}

int FxFrame_800B3B0C(MapFx* fx, MapFxWork* w, int count)
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
        return MOD0(fx->first_1E + DIV0((end - fx->first_1E) * w->time_18, length), count);
    }
    return -1;
}

void FxTime_800B3B90(MapEnt* ent, MapFx* fx, MapFxWork* w)
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

void FxPlace_800B3C5C(MapFx* fx, MapFxWork* w)
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
