#include "maps/map.h"

void MinionInit_800B22F0(MapEnt* ent);
int AddEffects_800B2628(MapFx* fx);
void FxSprite_800B27B4(MapEnt* ent);
void MapInit_800B2928(int phase);
void MinionIdle_800B29A8(MapEnt* ent);
int EndEffects_800B29B0(void);
void FxInit_800B2A30(MapEnt* ent);
void FxLight_800B2AE8(MapEnt* ent);
void FxAtMinion_800B2BA8(int* pos, short* rot);
void StartMapTask_800B2C7C(void);
void MapTaskLoad_800B2CAC(EventEntry* entry, int* st);
void MapTask_800B2D44(EventEntry* entry, int* st);
int LeaveArea_800B2DFC(MapEvent* ev, int area);
int EnterArea_800B2F18(MapEvent* ev, int area, int prev);
void RequestModels_800B3020(MapEvent* ev);
void EntityTask_800B30F0(EventEntry* entry, MapEnt* ent);
int AddEntity_800B3170(void* ev);
void MapInit_800B329C(int phase);
int MinionF_800B3308(void);
int MinionF_800B3310(void);
int FxFrame_800B3318(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B339C(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B3468(MapFx* fx, MapFxWork* w);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[12];
extern const char str_800B22D0[12];
extern const MapFxInits fxInits_800B22DC;
extern int unknown_800B35B0[11];
extern int data_800B35DC[12];
extern ActorScriptCmd* script_800B360C;
extern MapActorModel model_800B3610;
extern int data_800B363C[3];
extern short bones_800B3648[116];
extern int data_800B3730[11];
extern int data_800B375C[12];
extern int data_800B378C[16];
extern ActorScriptCmd* script_800B37CC;
extern MapActorModel model_800B37D0;
extern MapVoice voices_800B37FC[25];
extern MapFx effects_800B38C4[2];
extern MapFx effects_800B391C[3];
extern MapFx effects_800B39A0[7];
extern MapFx effects_800B3AD4[3];
extern int data_800B3B58[4];
extern MapInstr script_800B3B68[135];
extern MapMinion minion_800B43D8;
extern MapMinion minion_800B43FC;
extern MapEvent events_800B4420[5];
extern short bones_800B4484[92];
extern int scale_800B453C[3];

void MinionInit_800B22F0(MapEnt* ent)
{
    ActorDesc desc;
    int params[2];
    UnitStats unit;
    MapMinion* m;
    MapActorModel* model;
    MapMinionSpecies* species;
    Model* mdl;
    int modelId;
    short* bones;
    int* baseScale;
    SVECTOR* boneScale;
    ActorScriptCmd** script;
    MapMinionWork* w;
    int blendDiv;
    void* effects;
    unsigned short* levels;
    unsigned short* flags;
    int rec;
    Actor* actor;

    levels = 0;
    flags = 0;
    m = ent->data_10;
    w = (MapMinionWork*)ent->work_14;
    species = m->species_4;
    model = m->model_0;
    if (species)
    {
        modelId = GetSpeciesModelDesc_80019C70(species->species_0)->modelId_0;
        blendDiv = 4;
        mdl = AcquireLoaderModel_80020734(modelId);
        params[0] = species->species_0;
        params[1] = species->level_4;
        rec = InitMinionData_8001900C(&unit, params);
        bones = defaultBones_80079140;
        baseScale = GetModelBaseScale_80024E90(mdl, rec);
        boneScale = GetModelBoneScale_80024EC8(mdl, rec);
        effects = GetModelEffectTable_80024E64(mdl);
        levels = GetModelBoneGroupLevels_80024F00(mdl, rec);
        flags = GetModelBoneGroupFlags_80024F38(mdl, rec);
        if (model && model->script_1C)
        {
            script = model->script_1C;
        }
        else
        {
            script = commandScripts_8007A024;
        }
    }
    else
    {
        modelId = model->modelId_4;
        mdl = AcquireLoaderModel_80020734(modelId);
        blendDiv = model->blendDiv_18;
        bones = model->bones_8;
        baseScale = model->baseScale_C;
        boneScale = model->boneScale_10;
        effects = GetModelEffectTable_80024E64(mdl);
        script = model->script_1C;
    }
    desc.modelId_0 = modelId;
    desc.kind_4 = GetFieldMinionCount_800A7790() + 3;
    desc.pos_8[0] = m->pos_8[0];
    desc.pos_8[1] = m->pos_8[1];
    desc.pos_8[2] = m->pos_8[2];
    desc.rot_14[0] = 0;
    desc.rot_14[1] = m->rotY_14;
    desc.rot_14[2] = 0;
    desc.clutRow_1C = GetFieldMinionCount_800A7790();
    desc.animIdx_20 = m->anim_18;
    desc.frame_24 = -1;
    desc.frameSpeed_28 = 0x1000;
    desc.blendDiv_2C = blendDiv;
    desc.visible_30 = 1;
    if (bones)
    {
        desc.bones_34 = bones;
    }
    else
    {
        desc.bones_34 = bones_800B4484;
    }
    if (baseScale)
    {
        desc.baseScale_38 = baseScale;
    }
    else
    {
        desc.baseScale_38 = scale_800B453C;
    }
    if (boneScale)
    {
        desc.boneScale_3C = boneScale;
    }
    else
    {
        desc.boneScale_3C = 0;
    }
    desc.anims_40 = GetModelActorAnims_80024E38(mdl);
    desc.effectTbl_44 = effects;
    desc.hasMatrices_4C = (m->flags_20 >> 2) & 1;
    actor = CreateActor_8001D45C(&desc);
    if (levels && flags)
    {
        SetBoneGroupFlags_80019B14(actor->bones_134, levels, flags);
    }
    if (model->ftgs_14)
    {
        SaveModelFtgs_80024FFC(mdl, model->ftgs_14);
    }
    w->f_C = MinionF_800B3308;
    w->actor_4 = actor;
    w->script_8 = script;
    w->f_10 = MinionF_800B3310;
    w->minion_0 = AddFieldMinion_800A77A0(ent);
    if (m->flags_20 & 1)
    {
        SetActorVisible_8001D730(actor, 0);
    }
    if (m->flags_20 & 2)
    {
        SetActorRootMotion_8001D6BC(actor, 1);
    }
    if (m->flags_20 & 8)
    {
        SetActorGroundMove_8001D68C(actor, 0);
    }
    ent->update_90 = MinionIdle_800B29A8;
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
        entry->cb_8 = (EventEntryFn)EntityTask_800B30F0;
        return 1;
    }
    return 0;
}

/* NONMATCHING: AddEffects_800B2544's C does not compile to its code yet */
int AddEffects_800B2628(MapFx* fx)
{
    MapEvent ev;

    while (fx->type_0 != MAP_FX_END)
    {
        ev.areas_0 = -1;
        ev.type_4 = 7;
        ev.data_8 = fx;
        ev.size_C = 0x20;
        ev.run_10.init = FxInit_800B2A30;
        NewEntity(&ev);
        fx++;
    }
    return 1;
}

/* NONMATCHING: FxSprite_800B26D0's C does not compile to its code yet */
void FxSprite_800B27B4(MapEnt* ent)
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
    frame = FxFrame_800B3318(fx, w, sprite->count_0);
    FxTime_800B339C(ent, fx, w);
    FxPlace_800B3468(fx, w);
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

void MapInit_800B2928(int phase)
{
    if (phase == 0)
    {
        savedLevantPos_80091C78.mapIdx = 1;
    }
    if (phase == 1)
    {
        StartMapTask_800B2C7C();
        ClearFieldMinions_800A7784();
        RequestModels_800B3020(events_800B4420);
        levantAnimSet_80091C74 = 42;
        LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B3170);
    }
}

void MinionIdle_800B29A8(MapEnt* ent)
{
}

int EndEffects_800B29B0(void)
{
    EventNode* node;
    EventEntry* entry;
    int count;
    int i;

    node = eventEntities_8008D400;
    count = node->count;
    for (i = 0; i < count; i++)
    {
        entry = &node->entry;
        if ((entry->flags & 0x8001) == 1)
        {
            if (((MapEnt*)entry->buffer)->type_C == 7)
            {
                entry->flags = (entry->flags & ~1) | 0x8000;
            }
        }
        node = node->next;
    }
    pointLightRange_8008D3F0 = 0;
    return 1;
}

void FxInit_800B2A30(MapEnt* ent)
{
    MapFxInits inits = fxInits_800B22DC;
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

/* effect type 4: a point light at the effect, coloured rot_10, range arg_24 */
void FxLight_800B2AE8(MapEnt* ent)
{
    MapFx* fx = ent->data_10;
    MapFxWork* w = (MapFxWork*)ent->work_14;
    int frame;

    frame = FxFrame_800B3318(fx, w, w->time_18);
    FxTime_800B339C(ent, fx, w);
    FxPlace_800B3468(fx, w);
    if (frame >= 0)
    {
        int range = fx->arg_24;

        pointLightPos_8008D680[0] = w->pos_4[0];
        pointLightPos_8008D680[1] = w->pos_4[1];
        pointLightPos_8008D680[2] = w->pos_4[2];
        pointLightColor_8008D418.vx = fx->rot_10[0];
        pointLightColor_8008D418.vy = fx->rot_10[1];
        pointLightRange_8008D3F0 = range;
        pointLightColor_8008D418.vz = fx->rot_10[2];
    }
}

/* places an effect at the first party member's bone 2 */
void FxAtMinion_800B2BA8(int* pos, short* rot)
{
    SVECTOR r;
    Actor* actor;

    memset(&r, 0, sizeof(r));
    actor = GetFieldMinionActor_800A7A60(0);
    pos[0] = actor->pos_38[0];
    pos[1] = actor->pos_38[1];
    pos[2] = actor->pos_38[2];
    pos[0] = actor->bonePos_1C4[6] + pos[0];
    pos[1] = actor->bonePos_1C4[7] + pos[1];
    pos[2] = actor->bonePos_1C4[8] + pos[2];
    rot[0] = r.vx;
    rot[1] = r.vy;
    rot[2] = r.vz;
}

void StartMapTask_800B2C7C(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B2CAC;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B2CAC(EventEntry* entry, int* st)
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
        MapTask_800B2D44(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B2D44;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B2D44(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = events_800B4420;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B2DFC(events, currentArea_80091C44);
        st[2] += EnterArea_800B2F18(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B2DFC(MapEvent* ev, int area)
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

int EnterArea_800B2F18(MapEvent* ev, int area, int prev)
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
                AddEntity_800B3170(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B3020(MapEvent* ev)
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

void EntityTask_800B30F0(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}

int AddEntity_800B3170(void* ev)
{
    return NewEntity(ev);
}

void MapInit_800B329C(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B2C7C();
        ClearFieldMinions_800A7784();
        RequestModels_800B3020(events_800B4420);
        levantAnimSet_80091C74 = 42;
        LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B3170);
    }
}

int MinionF_800B3308(void)
{
    return 1;
}

int MinionF_800B3310(void)
{
    return 1;
}

int FxFrame_800B3318(MapFx* fx, MapFxWork* w, int count)
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

void FxTime_800B339C(MapEnt* ent, MapFx* fx, MapFxWork* w)
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

void FxPlace_800B3468(MapFx* fx, MapFxWork* w)
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
