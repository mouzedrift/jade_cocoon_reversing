#ifndef MAP_H
#define MAP_H
/* The code that map files bring along (scripts/mapcode.py): every map is its own image, linked at
   mapCodeAddr_80073210 (0x800B22C0, behind GAME), from src/maps/NAME.c. Most maps are built from the same
   pieces (the functions here), with the map's own tables. */
#include "overlays/game.h"

#define CLAMP(x, lo, hi) ((x) < (lo) ? (lo) : ((hi) < (x) ? (hi) : (x)))

typedef struct MapEnt MapEnt;
typedef void (*MapEntFn)(MapEnt* ent);

/* MapEvent.type_4 */
#define MAP_EV_SCRIPT 8     /* data_8: an event script, started for the areas it is in (run_10: the script) */
#define MAP_EV_VOICES 0xB   /* data_8: the voice table (SetVoiceTable_800A6830) */
#define MAP_EV_MINION 0xF   /* data_8: a MapMinion */
#define MAP_EV_END 0x12

/* an entry of a map's event table: what is there in which area (currentArea_80091C44) */
typedef struct MapEvent
{
    int areas_0; /* the areas it is there in, one bit each (-1: every area) */
    int type_4;
    void* data_8;
    int size_C;
    union
    {
        MapEntFn init; /* creates the entity: MapEnt.update_90 */
        EventEntry* script; /* MAP_EV_SCRIPT: the running script */
    } run_10;
} MapEvent;

/* a map entity (the buffer of an eventEntities_8008D400 entry): GAME's GameEvEnt and an update function */
struct MapEnt
{
    EventEntry* entry_0;
    MapEvent* event_4;
    int areas_8;
    int type_C;
    void* data_10;
    int work_14[0x19]; /* what the entity's functions keep */
    int armed_78;
    int state_7C; /* -1: running; -2: done (its entry stops); -3 */
    int f80;
    int trigger_84;
    int script_88;
    int f8C;
    MapEntFn update_90;
};

/* a character standing in the map (MAP_EV_MINION) */
typedef struct MapActorModel
{
    char* name_0;
    int modelId_4;
    short* bones_8;
    int* baseScale_C;
    SVECTOR* boneScale_10;
    int* ftgs_14; /* SaveModelFtgs_80024FFC */
    int blendDiv_18;
    ActorScriptCmd** script_1C;
    int f20;
    int f24;
    short sel_28; /* RequestLoaderModel_800206A0 */
    short f2A;
} MapActorModel;

typedef struct MapMinionSpecies
{
    int species_0;
    int level_4;
} MapMinionSpecies;

typedef struct MapMinion
{
    MapActorModel* model_0;
    MapMinionSpecies* species_4; /* a minion of a species instead of the model */
    int pos_8[3];
    short rotY_14;
    short pad_16;
    int anim_18;
    int f1C;
    unsigned int flags_20; /* 1: hidden; 2: root motion; 4: bone matrices; 8: no ground move */
} MapMinion;

typedef struct MapMinionWork
{
    int minion_0; /* AddFieldMinion_800A77A0 */
    Actor* actor_4;
    ActorScriptCmd** script_8;
    int (*f_C)(void);
    int (*f_10)(void);
} MapMinionWork;

/* an effect placed in the map (a list ends with type_0 MAP_FX_END) */
#define MAP_FX_MODEL 1
#define MAP_FX_MDEC 3
#define MAP_FX_END 5
typedef struct MapFx
{
    short type_0;
    short id_2; /* the effect (FindEffectIndex_80020F00) */
    int pos_4[3];
    short rot_10[3];
    short pad_16;
    short length_18; /* frames of one run (< 0: the effect's frame count) */
    short delay_1A;  /* frames before it starts */
    short runs_1C;   /* runs before it ends (< 0: forever) */
    short first_1E;  /* first frame */
    short restart_20; /* the time a run starts again from */
    short last_22;   /* last frame (< 0: the effect's last) */
    short arg_24;
    short pad_26;
    void (*place_28)(int* pos, short* rot); /* moves it (relative to pos_4 / rot_10) */
} MapFx;

typedef struct MapFxWork
{
    EffectFile* file_0;
    int pos_4[3];
    short rot_10[3];
    short pad_16;
    short time_18;
    short delay_1A;
    short runs_1C;
} MapFxWork;

/* an event script instruction (EVENTFNC's EvInstr) */
typedef struct MapInstr
{
    int op_0;
    int a_4;
    int b_8;
    int c_C;
} MapInstr;

/* a voice of the map's voice table (EVENTFNC's EvVoiceCue) */
typedef struct MapVoice
{
    unsigned char id_0;
    unsigned char sub_1;
    short xa_2[3];
} MapVoice;

extern int AddFieldMinion_800A77A0(MapEnt* ent);
extern void ClearFieldMinions_800A7784(void);
extern void LoadLevantAnimSet_800AC708(int set, int arg1);
extern void SetEventHook_800A5F90(int hook);
extern void SetVoiceTable_800A6830(int table);
extern int AreLevantFilesLoaded_800AC768();
extern int levantAnimSet_80091C74; /* main.h (which GAME does not include) */
extern int pointLightRange_8008D3F0;
extern EventNode* mapEventTasks_800B1DA8[1];

#endif
