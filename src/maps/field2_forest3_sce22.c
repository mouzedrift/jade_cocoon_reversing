#include "maps/map.h"

int AddEffects_800B22D8(MapFx* fx);
void FxSprite_800B2464(MapEnt* ent);
void FxModel_800B25D8(MapEnt* ent);
void MapInit_800B2800(int phase);
void FxInit_800B286C(MapEnt* ent);
void SfxLoopInit_800B2924(MapEnt* ent);
void SfxLoop_800B2958(MapEnt* ent);
void StartMapTask_800B29A8(void);
void MapTaskLoad_800B29D8(EventEntry* entry, int* st);
void MapTask_800B2A70(EventEntry* entry, int* st);
int LeaveArea_800B2B28(MapEvent* ev, int area);
int EnterArea_800B2C44(MapEvent* ev, int area, int prev);
void RequestModels_800B2D4C(MapEvent* ev);
void EntityTask_800B2E1C(EventEntry* entry, MapEnt* ent);
int AddEntity_800B2E9C(void* ev);
int FxFrame_800B2FC8(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B304C(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B3118(MapFx* fx, MapFxWork* w);

extern const int unknown_800B22C0[1];
extern const MapFxInits fxInits_800B22C4;
extern MapFx effects_800B3260[3];
extern MapFx effects_800B32E4[2];
extern MapFx effects_800B333C[2];
extern MapFx effects_800B3394[2];
extern MapFx effects_800B33EC[3];
extern MapFx effects_800B3470[3];
extern MapFx effects_800B34F4[3];
extern MapFx effects_800B3578[2];
extern MapFx effects_800B35D0[2];
extern MapFx effects_800B3628[2];
extern int data_800B3680[4];
extern MapEvent event_800B3690;
extern MapInstr script_800B36A4[73];
extern MapEvent events_800B3B34[2];

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
        entry->cb_8 = (EventEntryFn)EntityTask_800B2E1C;
        return 1;
    }
    return 0;
}

/* NONMATCHING: AddEffects_800B2544's C does not compile to its code yet */
int AddEffects_800B22D8(MapFx* fx)
{
    MapEvent ev;

    while (fx->type_0 != MAP_FX_END)
    {
        ev.areas_0 = -1;
        ev.type_4 = 7;
        ev.data_8 = fx;
        ev.size_C = 0x20;
        ev.run_10.init = FxInit_800B286C;
        NewEntity(&ev);
        fx++;
    }
    return 1;
}

/* NONMATCHING: FxSprite_800B26D0's C does not compile to its code yet */
void FxSprite_800B2464(MapEnt* ent)
{
    MapFx* fx;
    MapFxWork* w;
    EffectSprite* sprite;
    EffectSpriteFrame* f;
    int frame;
    int i;
    unsigned short arg;

    fx = ent->data_10;
    w = (MapFxWork*)ent->work_14;
    sprite = &w->file_0->sprites_20[FindEffectIndex_80020F00(w->file_0, 0, fx->id_2)];
    frame = FxFrame_800B2FC8(fx, w, sprite->count_0);
    FxTime_800B304C(ent, fx, w);
    FxPlace_800B3118(fx, w);
    if (frame >= 0)
    {
        for (i = 0; i < sprite->frameCounts_4[frame]; i++)
        {
            arg = fx->arg_24;
            f = &sprite->frames_8[frame][i];
            DrawRotSprite_80044010(&sprite->poly_C, (VECTOR*)w->pos_4, (SVECTOR*)w->rot_10, &f->u_0, &f->w_4, &f->pivotX_8, f->size_C,
                                   (SVECTOR*)f->pos_10, f->rgb_18, (arg >> 2) & 2, (short)arg & ~8, pOT_8008D690);
        }
    }
}

void FxModel_800B25D8(MapEnt* ent)
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
    frame = FxFrame_800B2FC8(fx, w, model->frameCount_14);
    FxTime_800B304C(ent, fx, w);
    FxPlace_800B3118(fx, w);
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

void MapInit_800B2800(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B29A8();
        ClearFieldMinions_800A7784();
        RequestModels_800B2D4C(events_800B3B34);
        levantAnimSet_80091C74 = 8;
        LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B2E9C);
    }
}

void FxInit_800B286C(MapEnt* ent)
{
    MapFxInits inits = fxInits_800B22C4;
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

void SfxLoopInit_800B2924(MapEnt* ent)
{
    ent->work_14[0] = 0;
    SfxLoop_800B2958(ent);
    ent->update_90 = SfxLoop_800B2958;
}

/* plays sound 31 every 45 frames */
void SfxLoop_800B2958(MapEnt* ent)
{
    if (ent->work_14[0] == 0)
    {
        PlaySfx_80031494(31);
        ent->work_14[0] = 45;
    }
    ent->work_14[0]--;
}

void StartMapTask_800B29A8(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B29D8;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B29D8(EventEntry* entry, int* st)
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
        MapTask_800B2A70(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B2A70;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B2A70(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = events_800B3B34;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B2B28(events, currentArea_80091C44);
        st[2] += EnterArea_800B2C44(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B2B28(MapEvent* ev, int area)
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

int EnterArea_800B2C44(MapEvent* ev, int area, int prev)
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
                AddEntity_800B2E9C(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B2D4C(MapEvent* ev)
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

void EntityTask_800B2E1C(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}

int AddEntity_800B2E9C(void* ev)
{
    return NewEntity(ev);
}

int FxFrame_800B2FC8(MapFx* fx, MapFxWork* w, int count)
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

void FxTime_800B304C(MapEnt* ent, MapFx* fx, MapFxWork* w)
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

void FxPlace_800B3118(MapFx* fx, MapFxWork* w)
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
