#include "maps/map.h"

void Warp_800B22F4(MapEnt* ent);
void TileDoor_800B2418(MapEnt* ent);
int AddEffects_800B2574(MapFx* fx);
void FxModel_800B2700(MapEnt* ent);
void EffectSpot_800B2928(MapEnt* ent);
void SavePoint_800B2A9C(MapEnt* ent);
void MapInit_800B2F0C(int phase);
void TileDoorInit_800B2F7C(MapEnt* ent);
void FxInit_800B3010(MapEnt* ent);
void FxMdec_800B30C8(MapEnt* ent);
void EffectSpotInit_800B31B4(MapEnt* ent);
void SavePointInit_800B31F8(MapEnt* ent);
void StartMapTask_800B3238(void);
void MapTaskLoad_800B3268(EventEntry* entry, int* st);
void MapTask_800B3300(EventEntry* entry, int* st);
int LeaveArea_800B33B8(MapEvent* ev, int area);
int EnterArea_800B34D4(MapEvent* ev, int area, int prev);
void RequestModels_800B35DC(MapEvent* ev);
void EntityTask_800B36AC(EventEntry* entry, MapEnt* ent);
int AddEntity_800B372C(void* ev);
int FindTileLayer_800B3858(int id);
void SetTileLayerFrame_800B3910(int layer, int frame);
int IsTileLayerDone_800B392C(int layer, int frame);
int FxFrame_800B3994(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B3A18(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B3AE4(MapFx* fx, MapFxWork* w);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[20];
extern const MapFxInits fxInits_800B22D8;
extern const MapRgb savePointDim_800B22EC;
extern const MapRgb savePointLit_800B22F0;
extern MapSavePoint savePoint_800B3C2C;
extern MapWarp warp_800B3C3C;
extern MapWarp warp_800B3C54;
extern MapFx effects_800B3C6C[3];
extern MapFx effects_800B3CF0[3];
extern MapEffectSpot data_800B3D74;
extern MapEffectSpot data_800B3DA0;
extern MapTileDoor data_800B3DCC;
extern MapEvent events_800B3DDC[7];
extern int data_800B3E68[96];

void Warp_800B22F4(MapEnt* ent)
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

/* runs a tile door's frames (the layer has shown frame_8 for its time: the next one) */
void TileDoor_800B2418(MapEnt* ent)
{
    MapTileDoor* door = ent->data_10;
    MapTileDoorWork* w = (MapTileDoorWork*)ent->work_14;
    int open;

    if (!IsTileLayerDone_800B392C(w->layer_4, w->frame_8))
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
    SetTileLayerFrame_800B3910(w->layer_4, w->frame_8);
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
        entry->cb_8 = (EventEntryFn)EntityTask_800B36AC;
        return 1;
    }
    return 0;
}

/* NONMATCHING: AddEffects_800B2544's C does not compile to its code yet */
int AddEffects_800B2574(MapFx* fx)
{
    MapEvent ev;

    while (fx->type_0 != MAP_FX_END)
    {
        ev.areas_0 = -1;
        ev.type_4 = 7;
        ev.data_8 = fx;
        ev.size_C = 0x20;
        ev.run_10.init = FxInit_800B3010;
        NewEntity(&ev);
        fx++;
    }
    return 1;
}

void FxModel_800B2700(MapEnt* ent)
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
    frame = FxFrame_800B3994(fx, w, model->frameCount_14);
    FxTime_800B3A18(ent, fx, w);
    FxPlace_800B3AE4(fx, w);
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

/* NONMATCHING: ent and w get s2 / s1 (the original: s1 / s2) */
void EffectSpot_800B2928(MapEnt* ent)
{
    MapEffectSpotWork* w = (MapEffectSpotWork*)ent->work_14;
    MapEffectSpot* spot = ent->data_10;

    if (IsEventPointInView_800A66A4(&spot->point_4, (int*)&levantPos_8008BD18, (unsigned short*)&levantPos_8008BD18.rot) && !w->busy_8
        && !FindEventScript_800A5AE4(w->script_0))
    {
        ent->armed_78 = 1;
    }
    switch (ent->state_7C)
    {
    case 0:
        if (TestEventFlag_800AD0D4(spot->flag_0))
        {
            w->script_0 = GetEventScriptId_800A5AD0(StartEventScriptForEntity_800A5AA0(data_800B3E68, ent));
        }
        ent->state_7C = -1;
        return;
    case 1:
        AddEffects_800B2574(w->turn_4 == 0 ? spot->fx_24[0] : spot->fx_24[1]);
        w->turn_4 = (w->turn_4 + 1) & 1;
        break;
    case 2:
        saveData_8008B570.levant_7A8.pos.x = spot->dest_14[0];
        saveData_8008B570.levant_7A8.pos.y = spot->dest_14[1];
        saveData_8008B570.levant_7A8.pos.z = spot->dest_14[2];
        saveData_8008B570.levant_7A8.rot.vy = spot->rotY_20;
        w->busy_8 = 0;
        break;
    default:
        return;
    }
    ent->prev_80 = ent->state_7C;
    ent->state_7C = -1;
}

void SavePoint_800B2A9C(MapEnt* ent)
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
    dim = savePointDim_800B22EC;
    lit = savePointLit_800B22F0;
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

void MapInit_800B2F0C(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B3238();
        ClearFieldMinions_800A7784();
        RequestModels_800B35DC(events_800B3DDC);
        if (levantAnimSet_80091C74 >= 0)
        {
            LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        }
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B372C);
    }
}

void TileDoorInit_800B2F7C(MapEnt* ent)
{
    MapTileDoor* door = ent->data_10;
    MapTileDoorWork* w = (MapTileDoorWork*)ent->work_14;

    w->open_0 = TestEventFlag_800AD0D4(door->flag_0) != 0;
    w->layer_4 = FindTileLayer_800B3858(door->layer_4);
    w->frame_8 = door->seq_8[w->open_0].last_1;
    w->sfx_C = 0;
    SetTileLayerFrame_800B3910(w->layer_4, w->frame_8);
    TileDoor_800B2418(ent);
    ent->update_90 = TileDoor_800B2418;
}

void FxInit_800B3010(MapEnt* ent)
{
    MapFxInits inits = fxInits_800B22D8;
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

void FxMdec_800B30C8(MapEnt* ent)
{
    MapFx* fx;
    MapFxWork* w;
    MdecImageSet* set;
    int frame;

    fx = ent->data_10;
    w = (MapFxWork*)ent->work_14;
    set = &w->file_0->imageSets_30[FindEffectIndex_80020F00(w->file_0, 2, fx->id_2)];
    frame = FxFrame_800B3994(fx, w, set->count_0);
    FxTime_800B3A18(ent, fx, w);
    if (frame >= 0 && !(unknownFlags_8008D678 & 0x800))
    {
        mdecEffectVlcBuffer_8008D42C = w->file_0->mdec_34.dct_0;
        decodedImageData_8008B4A0 = w->file_0->mdec_34.work_4;
        DecodeMdec_80041920(set->images_4[frame], mdecEffectVlcBuffer_8008D42C, fx->arg_24);
        unknownFlags_8008D678 |= 0x800;
    }
}

void EffectSpotInit_800B31B4(MapEnt* ent)
{
    MapEffectSpotWork* w = (MapEffectSpotWork*)ent->work_14;

    w->script_0 = -1;
    w->turn_4 = 0;
    w->busy_8 = 0;
    EffectSpot_800B2928(ent);
    ent->update_90 = EffectSpot_800B2928;
}

void SavePointInit_800B31F8(MapEnt* ent)
{
    MapSavePointWork* w = (MapSavePointWork*)ent->work_14;

    w->angle_0 = 0;
    w->phase_4 = 0;
    w->glow_8 = 0;
    SavePoint_800B2A9C(ent);
    ent->update_90 = SavePoint_800B2A9C;
}

void StartMapTask_800B3238(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B3268;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B3268(EventEntry* entry, int* st)
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
        MapTask_800B3300(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B3300;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B3300(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = events_800B3DDC;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B33B8(events, currentArea_80091C44);
        st[2] += EnterArea_800B34D4(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B33B8(MapEvent* ev, int area)
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

int EnterArea_800B34D4(MapEvent* ev, int area, int prev)
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
                AddEntity_800B372C(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B35DC(MapEvent* ev)
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

void EntityTask_800B36AC(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}

int AddEntity_800B372C(void* ev)
{
    return NewEntity(ev);
}

/* the animated layer of a tile set (tileAnim_8008D648.listCount_10: none) */
int FindTileLayer_800B3858(int id)
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

void SetTileLayerFrame_800B3910(int layer, int frame)
{
    TileAnimTimer* t = &tileAnim_8008D648.pairs_18[layer];

    t->frame_2 = frame;
    t->timer_0 = 0;
}

/* 0 while the layer still shows the frame */
int IsTileLayerDone_800B392C(int layer, int frame)
{
    TileAnimLayer* l = &tileAnim_8008D648.lists_14[layer];
    TileAnimTimer* t = &tileAnim_8008D648.pairs_18[layer];

    if (frame != t->frame_2 || t->timer_0 + 1 >= (l->items[frame].time_2 & 0x7F))
    {
        return 1;
    }
    return 0;
}

int FxFrame_800B3994(MapFx* fx, MapFxWork* w, int count)
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

void FxTime_800B3A18(MapEnt* ent, MapFx* fx, MapFxWork* w)
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

void FxPlace_800B3AE4(MapFx* fx, MapFxWork* w)
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
