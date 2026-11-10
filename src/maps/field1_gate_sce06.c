#include "maps/map.h"

void Warp_800B2368(MapEnt* ent);
void MinionInit_800B248C(MapEnt* ent);
void GateSpot_800B27C4(MapEnt* ent);
void GateReturn_800B2A14(MapEnt* ent);
void GlowTrail_800B2BF4(MapEnt* ent);
int AddEffects_800B3038(MapFx* fx);
void FxSprite_800B31C4(MapEnt* ent);
void FxModel_800B3338(MapEnt* ent);
void SavePoint_800B3560(MapEnt* ent);
void MapInit_800B39D0(int phase);
void ScriptSpot_800B3BB4(MapEnt* ent);
void MinionIdle_800B3C28(MapEnt* ent);
void FxInit_800B3C30(MapEnt* ent);
void FxMdec_800B3CE8(MapEnt* ent);
void GateSpotInit_800B3DD4(MapEnt* ent);
void GateReturnInit_800B3E1C(MapEnt* ent);
void FxAtLevant_800B3E98(int* pos, short* rot);
void GlowTrailInit_800B3F88(MapEnt* ent);
void SavePointInit_800B3FC8(MapEnt* ent);
void StartMapTask_800B4008(void);
void MapTaskLoad_800B4038(EventEntry* entry, int* st);
void MapTask_800B40D0(EventEntry* entry, int* st);
int LeaveArea_800B4188(MapEvent* ev, int area);
int EnterArea_800B42A4(MapEvent* ev, int area, int prev);
void RequestModels_800B43AC(MapEvent* ev);
void EntityTask_800B447C(EventEntry* entry, MapEnt* ent);
int AddEntity_800B44FC(void* ev);
void MapInit_800B4628(int phase);
int StopLevantIfSet_800B4694(MapScriptSpot* spot);
int MinionF_800B46C4(void);
int MinionF_800B46CC(void);
int FxFrame_800B46D4(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B4758(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B4824(MapFx* fx, MapFxWork* w);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[28];
extern const char str_800B22E0[12];
extern const MapFxInits fxInits_800B2300;
extern const MapRgb savePointDim_800B2314;
extern const MapRgb savePointLit_800B2318;
extern MapSavePoint savePoint_800B496C;
extern int data_800B497C[3];
extern short bones_800B4988[116];
extern ActorScriptCmd* script_800B4A70;
extern MapActorModel model_800B4A74;
extern MapVoice voices_800B4AA0[5];
extern int data_800B4AC8[2];
extern MapWarp warp_800B4AD0;
extern MapWarp warp_800B4AE8;
extern MapWarp warp_800B4B00;
extern MapWarp warp_800B4B18;
extern MapFx effects_800B4B30[3];
extern MapFx effects_800B4BB4[3];
extern MapFx effects_800B4C38[3];
extern MapFx effects_800B4CBC[3];
extern MapFx effects_800B4D40[3];
extern MapFx effects_800B4DC4[3];
extern MapFx effects_800B4E48[3];
extern MapFx effects_800B4ECC[3];
extern MapGateSpot data_800B4F50;
extern MapGateSpot data_800B4F84;
extern MapGateSpot data_800B4FB8;
extern MapGateSpot data_800B4FEC;
extern MapGateSpot data_800B5020;
extern MapGateSpot data_800B5054;
extern MapGateSpot data_800B5088;
extern MapGateSpot data_800B50BC;
extern MapGateReturn data_800B50F0;
extern MapGateReturn data_800B50F8;
extern MapGateReturn data_800B5100;
extern MapGateReturn data_800B5108;
extern MapGateReturn data_800B5110;
extern MapGateReturn data_800B5118;
extern MapGateReturn data_800B5120;
extern MapGateReturn data_800B5128;
extern MapMinion minion_800B5130;
extern MapEvent events_800B5154[25];
extern int data_800B5348[16];
extern short bones_800B5388[92];
extern int scale_800B5440[3];
extern MapFx effects_800B544C[3];
extern int data_800B54D0[104];
extern int data_800B5670[24];
extern int data_800B56D0[172];

void Warp_800B2368(MapEnt* ent)
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

void MinionInit_800B248C(MapEnt* ent)
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
        desc.bones_34 = bones_800B5388;
    }
    if (baseScale)
    {
        desc.baseScale_38 = baseScale;
    }
    else
    {
        desc.baseScale_38 = scale_800B5440;
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
    w->f_C = MinionF_800B46C4;
    w->actor_4 = actor;
    w->script_8 = script;
    w->f_10 = MinionF_800B46CC;
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
    ent->update_90 = MinionIdle_800B3C28;
}

void GateSpot_800B27C4(MapEnt* ent)
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
            script = data_800B54D0;
            w->open_C = 1;
        }
        else
        {
            script = data_800B5670;
        }
        ent->trigger_84 = gate->valuable_0;
        w->script_0 = GetEventScriptId_800A5AD0(StartEventScriptForEntity_800A5AA0(script, ent));
        ent->state_7C = -1;
        return;
    case 1:
        FreeMdecBuffer_800A5854();
        AllocMdecBuffer_800A5804(1);
        AddEffects_800B3038(w->fx_8 = w->turn_4 == 0 ? gate->fx_28[0] : gate->fx_28[1]);
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
        entry->cb_8 = (EventEntryFn)EntityTask_800B447C;
        return 1;
    }
    return 0;
}

/* state 0: play the effects; 1: done (event var 4 cleared); 2: the glow rises (effects and a GlowTrail) */
void GateReturn_800B2A14(MapEnt* ent)
{
    MapGateReturn* ret = ent->data_10;

    switch (ent->state_7C)
    {
    case 0:
        AddEffects_800B3038(ret->fx_4);
        goto done;
    case 2:
    {
        MapEvent ev = { -1, 0xD, 0, 0x48, { GlowTrailInit_800B3F88 } };

        AddEffects_800B3038(effects_800B544C);
        NewEntity(&ev);
    }
    done:
        ent->prev_80 = ent->state_7C;
        ent->state_7C = -1;
        break;
    case 1:
        SetEventVar_800AD16C(4, 0);
        ent->state_7C = -2;
        break;
    }
}


const MapFxInits fxInits_800B2300 = { { FxSprite_800B31C4, FxModel_800B3338, 0, FxMdec_800B3CE8, 0 } };
const MapRgb savePointDim_800B2314 = { 0x80, 0x40, 0x20, 0 };
const MapRgb savePointLit_800B2318 = { 0x20, 0x40, 0x80, 0 };

/* Levant's bone 1 (FxAtLevant_800B3E90's body) */
static inline void LevantBone1(int* pos, short* rot)
{
    EffectTarget t;
    int p[3];
    SVECTOR r;

    memset(p, 0, sizeof(p));
    memset(&r, 0, sizeof(r));
    GetLevantEffectTarget_800A93A4(&t);
    p[0] = t.pos_4[0];
    p[1] = t.pos_4[1];
    p[2] = t.pos_4[2];
    p[0] = t.bonePos_8[3] + p[0];
    p[1] = t.bonePos_8[4] + p[1];
    p[2] = t.bonePos_8[5] + p[2];
    pos[0] = p[0];
    pos[1] = p[1];
    pos[2] = p[2];
    rot[0] = r.vx;
    rot[1] = r.vy;
    rot[2] = r.vz;
}

/* NONMATCHING: GlowTrail_800B2BF4's C does not compile to its code yet */
void GlowTrail_800B2BF4(MapEnt* ent)
{
    MapGlowTrailWork* w = (MapGlowTrailWork*)ent->work_14;
    int base[3];
    short rot[4];
    EffectFile* file;
    EffectSprite* spark;
    EffectSprite* path;
    EffectSprite* delay;
    EffectSpriteFrame* f;
    int i323;
    int i324;
    int i325;
    int i;
    int slot;
    int age;
    int j;
    int ofs;
    int n;
    int step;

    file = GetEventDataSlot_800A55B0(0);
    i323 = FindEffectIndex_80020F00(file, 0, 323);
    i324 = FindEffectIndex_80020F00(file, 0, 324);
    i325 = FindEffectIndex_80020F00(file, 0, 325);
    spark = &file->sprites_20[i323];
    path = &file->sprites_20[i324];
    delay = &file->sprites_20[i325];
    LevantBone1(base, rot);
    if (ent->work_14[0] < delay->count_0)
    {
        ent->work_14[0]++;
        return;
    }
    if (w->time_4 % 60 == 0)
    {
        PlayMusic_800300E0(4, 1);
    }
    for (i = 0; i < w->count_8; i++)
    {
        slot = w->count_8 - (i + 1);
        age = w->ages_C[slot];
        if (age < 60)
        {
            int q[3];

            f = path->frames_8[w->time_4 - age];
            q[0] = base[0];
            q[1] = base[1];
            q[2] = base[2];
            q[0] += f->pos_10[0];
            q[1] += f->pos_10[1];
            q[2] += f->pos_10[2];
            for (j = 0, ofs = 0; j < spark->frameCounts_4[age]; j++, ofs += sizeof(EffectSpriteFrame))
            {
                f = (EffectSpriteFrame*)((char*)spark->frames_8[age] + ofs);
                DrawRotSprite_80044010(&spark->poly_C, (VECTOR*)q, (SVECTOR*)rot, &f->u_0, &f->w_4, &f->pivotX_8, f->size_C,
                                       (SVECTOR*)f->pos_10, f->rgb_18, 0, 48, pOT_8008D690);
            }
            w->ages_C[slot] = age + 1;
        }
    }
    n = CLAMP(w->time_4 + 1, 0, path->count_0 - 1);
    w->time_4 = n;
    step = -1;
    if (n < path->count_0 - 1)
    {
        step = 1;
    }
    w->count_8 = CLAMP(w->count_8 + step, 0, spark->count_0);
    w->ages_C[(w->time_4 - 1) % 60] = (rand() & 7) ? 60 : 0;
    if (w->count_8 <= 0)
    {
        ent->state_7C = -2;
    }
}

/* an entity for the event (MapEvent.run_10.init its update) */
/* NONMATCHING: AddEffects_800B2544's C does not compile to its code yet */
int AddEffects_800B3038(MapFx* fx)
{
    MapEvent ev;

    while (fx->type_0 != MAP_FX_END)
    {
        ev.areas_0 = -1;
        ev.type_4 = 7;
        ev.data_8 = fx;
        ev.size_C = 0x20;
        ev.run_10.init = FxInit_800B3C30;
        NewEntity(&ev);
        fx++;
    }
    return 1;
}

/* NONMATCHING: FxSprite_800B26D0's C does not compile to its code yet */
void FxSprite_800B31C4(MapEnt* ent)
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
    frame = FxFrame_800B46D4(fx, w, sprite->count_0);
    FxTime_800B4758(ent, fx, w);
    FxPlace_800B4824(fx, w);
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

void FxModel_800B3338(MapEnt* ent)
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
    frame = FxFrame_800B46D4(fx, w, model->frameCount_14);
    FxTime_800B4758(ent, fx, w);
    FxPlace_800B4824(fx, w);
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

void SavePoint_800B3560(MapEnt* ent)
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
    dim = savePointDim_800B2314;
    lit = savePointLit_800B2318;
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
void MapInit_800B39D0(int phase)
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
            gate = &data_800B4F50;
            break;
        case 2:
            gate = &data_800B4F84;
            break;
        case 3:
            gate = &data_800B4FB8;
            break;
        case 4:
            gate = &data_800B4FEC;
            break;
        case 5:
            gate = &data_800B5020;
            break;
        case 6:
            gate = &data_800B5054;
            break;
        case 7:
            gate = &data_800B5088;
            break;
        case 8:
            gate = &data_800B50BC;
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
        GetSetReturnEntrance_800A683C(104);
    }
    if (phase == 1)
    {
        StartMapTask_800B4008();
        ClearFieldMinions_800A7784();
        RequestModels_800B43AC(events_800B5154);
        levantAnimSet_80091C74 = 21;
        LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B44FC);
    }
}

void ScriptSpot_800B3BB4(MapEnt* ent)
{
    MapScriptSpot* spot = ent->data_10;

    if (fieldMode_800B0EC0 == 1 && IsEventPointValid_800A6504(spot->point_0, (int*)&levantPos_8008BD18) && !ent->arg_8C)
    {
        ent->arg_8C = spot;
        StartEventScript_800A59D0(data_800B5348);
    }
}

void MinionIdle_800B3C28(MapEnt* ent)
{
}

void FxInit_800B3C30(MapEnt* ent)
{
    MapFxInits inits = fxInits_800B2300;
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

void FxMdec_800B3CE8(MapEnt* ent)
{
    MapFx* fx;
    MapFxWork* w;
    MdecImageSet* set;
    int frame;

    fx = ent->data_10;
    w = (MapFxWork*)ent->work_14;
    set = &w->file_0->imageSets_30[FindEffectIndex_80020F00(w->file_0, 2, fx->id_2)];
    frame = FxFrame_800B46D4(fx, w, set->count_0);
    FxTime_800B4758(ent, fx, w);
    if (frame >= 0 && !(unknownFlags_8008D678 & 0x800))
    {
        mdecEffectVlcBuffer_8008D42C = w->file_0->mdec_34.dct_0;
        decodedImageData_8008B4A0 = w->file_0->mdec_34.work_4;
        DecodeMdec_80041920(set->images_4[frame], mdecEffectVlcBuffer_8008D42C, fx->arg_24);
        unknownFlags_8008D678 |= 0x800;
    }
}

void GateSpotInit_800B3DD4(MapEnt* ent)
{
    MapGateSpotWork* w = (MapGateSpotWork*)ent->work_14;

    w->script_0 = -1;
    w->turn_4 = 0;
    w->open_C = 0;
    w->fx_8 = 0;
    GateSpot_800B27C4(ent);
    ent->update_90 = GateSpot_800B27C4;
}

void GateReturnInit_800B3E1C(MapEnt* ent)
{
    MapGateReturn* ret = ent->data_10;

    if (ret->var_0 == GetEventVar_800AD154(4))
    {
        ent->work_14[0] = GetEventScriptId_800A5AD0(StartEventScriptForEntity_800A5AA0(data_800B56D0, ent));
        GateReturn_800B2A14(ent);
        ent->update_90 = GateReturn_800B2A14;
    }
    else
    {
        ent->state_7C = -2;
    }
}

void FxAtLevant_800B3E98(int* pos, short* rot)
{
    EffectTarget t;
    int p[3];
    SVECTOR r;

    memset(p, 0, sizeof(p));
    memset(&r, 0, sizeof(r));
    GetLevantEffectTarget_800A93A4(&t);
    p[0] = t.pos_4[0];
    p[1] = t.pos_4[1];
    p[2] = t.pos_4[2];
    p[0] = t.bonePos_8[3] + p[0];
    p[1] = t.bonePos_8[4] + p[1];
    p[2] = t.bonePos_8[5] + p[2];
    pos[0] = p[0];
    pos[1] = p[1];
    pos[2] = p[2];
    rot[0] = r.vx;
    rot[1] = r.vy;
    rot[2] = r.vz;
}

void GlowTrailInit_800B3F88(MapEnt* ent)
{
    MapGlowTrailWork* w = (MapGlowTrailWork*)ent->work_14;

    w->delay_0 = 0;
    w->time_4 = 0;
    w->count_8 = 0;
    GlowTrail_800B2BF4(ent);
    ent->update_90 = GlowTrail_800B2BF4;
}

void SavePointInit_800B3FC8(MapEnt* ent)
{
    MapSavePointWork* w = (MapSavePointWork*)ent->work_14;

    w->angle_0 = 0;
    w->phase_4 = 0;
    w->glow_8 = 0;
    SavePoint_800B3560(ent);
    ent->update_90 = SavePoint_800B3560;
}

void StartMapTask_800B4008(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B4038;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B4038(EventEntry* entry, int* st)
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
        MapTask_800B40D0(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B40D0;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B40D0(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = events_800B5154;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B4188(events, currentArea_80091C44);
        st[2] += EnterArea_800B42A4(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B4188(MapEvent* ev, int area)
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

int EnterArea_800B42A4(MapEvent* ev, int area, int prev)
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
                AddEntity_800B44FC(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B43AC(MapEvent* ev)
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

void EntityTask_800B447C(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}

int AddEntity_800B44FC(void* ev)
{
    return NewEntity(ev);
}

void MapInit_800B4628(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B4008();
        ClearFieldMinions_800A7784();
        RequestModels_800B43AC(events_800B5154);
        levantAnimSet_80091C74 = 21;
        LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B44FC);
    }
}

int StopLevantIfSet_800B4694(MapScriptSpot* spot)
{
    if (spot->idle_2)
    {
        ResetLevantActorToIdle_800A8DEC();
    }
    return 1;
}

int MinionF_800B46C4(void)
{
    return 1;
}

int MinionF_800B46CC(void)
{
    return 1;
}

int FxFrame_800B46D4(MapFx* fx, MapFxWork* w, int count)
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

void FxTime_800B4758(MapEnt* ent, MapFx* fx, MapFxWork* w)
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

void FxPlace_800B4824(MapFx* fx, MapFxWork* w)
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
