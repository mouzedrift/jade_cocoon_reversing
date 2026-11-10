#ifndef MAP_H
#define MAP_H
/* The code that map files bring along (scripts/mapcode.py): every map is its own image, linked at
   mapCodeAddr_80073210 (0x800B22C0, behind GAME), from src/maps/NAME.c. Most maps are built from the same
   pieces (the functions here), with the map's own tables. */
#include "overlays/game.h"
#include "ftg_draw.h"

/* a map name in an event script (an int): its address; on PC the PlayStation's (scripts/pc_maps.py's REF_
   defines), which PSX_PTR turns into the name's object */
#ifdef __psyz
#define MAP_REF(name) REF_##name
#else
#define MAP_REF(name) ((int)&name)
#endif

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
    EVENT_ENTITY_HEAD /* event_4: the MapEvent */
    int work_14[0x19]; /* what the entity's functions keep */
    int armed_78;
    int state_7C; /* -1: running; -2: done (its entry stops); -3 */
    int prev_80; /* the state it left (state_7C) */
    int trigger_84;
    int script_88;
    void* arg_8C; /* what its event script gets (StartEventScriptForEntity_800A5AA0: the entity; messages) */
    MapEntFn update_90;
};

/* a character standing in the map (MAP_EV_MINION) */
typedef struct MapActorModel
{
    const char* name_0;
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

/* a way out of the map (Warp): where Levant goes when he reaches the event point */
typedef struct MapWarp
{
    int pos_0[3];   /* where he starts on the next map */
    short rotY_C;   /* added to his rotation (0x4000: his rotation as it is) */
    short idle_E;   /* stop his animation (ResetLevantActorToIdle_800A8DEC) */
    short point_10; /* the event point (IsEventPointValid_800A6504) */
    short map_12[3]; /* area, map, entrance (saveData_8008B570.mapId_2E4) */
} MapWarp;

/* a chest (ChestInit): its event script opens it and gives its item once */
#define MAP_CHEST_ONCE 2   /* flags_C: shut until its flag is set */
#define MAP_CHEST_EMPTY 4  /* flags_C: starts empty */
#define MAP_CHEST_WAIT 8   /* flags_C: the script waits for the lid */
typedef struct MapChest
{
    int flag_0;  /* event flag: opened */
    int item_4;  /* the item in it (< 0: none) */
    int kind_8;  /* what draws it (3: ChestDraw) */
    unsigned int flags_C; /* 1: drawn open; MAP_CHEST_ */
    int point_10; /* the event point it is opened from (IsEventPointInView_800A66A4: this and pos_14) */
    int pos_14[3];
    int rotY_20;
    void* text_24; /* the script's messages (MapEnt.arg_8C) when it holds nothing */
    void* text_28;
    int f2C[6];    /* the script's (MapEnt.arg_8C) when shut */
    short ftg_44[2]; /* its box and lid (mapState_8008B500.ftg_3C; < 0: none) */
} MapChest;

typedef struct MapChestWork
{
    int full_0;    /* there is something in it */
    int opened_4;
    int draw_8;
    int opening_C;
    int lid_10;    /* the lid's angle (0 - 10) */
    int script_14; /* its event script's id (-1: none) */
} MapChestWork;

/* a gate out of the map (type 0x11, GateInit): with the valuable, Levant walks through it to an entrance of
   the map */
typedef struct MapGate
{
    int valuable_0; /* what opens it (TestValuableFlag_800AD73C; < 0: nothing) */
    int pos_4[3];   /* where it is (GateSpot) */
    short rotY_10;
    short pad_12;
    int dest_14[3]; /* where Levant starts behind it */
    unsigned short destRotY_20;
    short pad_22;
    short point_24;    /* the event point in front of it */
    short entrance_26; /* the entrance he comes back in by (saveData_8008B570.mapId_2E4[2]) */
} MapGate;

typedef struct MapGateWork
{
    int state_0; /* 0: start, 1: shut, 2: going through, 3: coming back */
    int script_4;
    int voice_8; /* its sound (SfxKeyOn_800314F4) */
} MapGateWork;

/* the gate's music, by map (saveData_8008B570.mapId_2E4[1]) */
typedef struct MapGateMusic
{
    int track[4];
} MapGateMusic;

/* a part of a sliding door: slides along x and turns while it opens */
typedef struct MapSlidingDoorPart
{
    int ftg_0;     /* mapState_8008B500.ftg_3C index (< 0: none) */
    int pos_4[3];  /* where it is shut */
    short rotY_10;
    short turn_12; /* rotY added when open */
    int openX_14;  /* pos_4[0] when open */
} MapSlidingDoorPart;

/* a door that opens with a valuable (SlidingDoor): its event script runs when Levant faces it */
typedef struct MapSlidingDoor
{
    int point_0;  /* the event point it is opened from (IsEventPointInView_800A66A4: this and pos_4) */
    int pos_4[3];
    GameWallPair walls_10; /* turned off once it is open */
    int flag_14;     /* event flag: opened (< 0: none) */
    int valuable_18; /* what opens it (TestValuableFlag_800AD73C; < 0: nothing) */
    MapSlidingDoorPart parts_1C[2];
    short frames_4C; /* frames to open */
    short sfx_4E;
} MapSlidingDoor;

/* an event point that starts the map's script when Levant stands on it (ScriptSpot) */
typedef struct MapScriptSpot
{
    short point_0;         /* the event point (IsEventPointValid_800A6504) */
    unsigned char idle_2;  /* the script stops his animation (ResetLevantActorToIdle_800A8DEC) */
    unsigned char f3;
    int pad_4;
} MapScriptSpot;

typedef struct MapSlidingDoorWork
{
    int script_0; /* its event script's id */
    int open_4;
    int t_8;      /* 0 - frames_4C */
} MapSlidingDoorWork;

/* an animated FTG object drawn around the camera (the dream's sky): frames first_0..last_2, speed_4 frames / 4096 a
   tick, turned by rots_8[the mesh Levant came from] */
typedef struct MapFtgAnim
{
    short first_0;
    short last_2;
    short speed_4;
    short pad_6;
    SVECTOR* rots_8;
} MapFtgAnim;

typedef struct MapFtgAnimWork
{
    short frame_0;
    short frac_2;
} MapFtgAnimWork;

/* the arguments of a map's change-map hook (event script ops 0x4C / 0x4D): event var 0, forceMapReload_80091C9C */
typedef struct MapExitArgs
{
    int var_0;
    int reload_4;
} MapExitArgs;

/* a save point (type 0xC, SavePointInit) */
typedef struct MapSavePoint
{
    int pos_0[3];
    const char* name_C; /* the save place (GameMenuRequest.arg_8) */
} MapSavePoint;

typedef struct MapSavePointWork
{
    int angle_0; /* its spin */
    int phase_4; /* its bob */
    int glow_8;  /* 0 .. 15: Levant near */
} MapSavePointWork;

typedef struct MapRgb
{
    unsigned char r, g, b, pad;
} MapRgb;

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

/* the update of each MapFx.type_0 */
typedef struct MapFxInits
{
    MapEntFn init[5];
} MapFxInits;

typedef struct MapFadeWork
{
    EffectModel* model_0;
    int index_4;
    short time_8[2];
} MapFadeWork;

/* runs the entity's update unless it is done (-2) or waits (-3) */
static inline void StepEntity(EventEntry* entry, void* buffer)
{
    MapEnt* ent = buffer;

    ent->armed_78 = 0;
    ent->trigger_84 = -1;
    if ((unsigned)(ent->state_7C + 3) >= 2)
    {
        ent->update_90(ent);
    }
    if (ent->state_7C == -2)
    {
        entry->flags = (entry->flags & ~1) | 0x8000;
    }
}


typedef struct MapDoorWork
{
    int state_0;
    int t_4;
} MapDoorWork;

/* is area one of the areas (a MapEvent.areas_0 mask) */
static inline int InAreas(int areas, int area)
{
    return areas & (1 << area);
}

extern EventEntry* StartEventScriptForEntity_800A5AA0(void* script, void* ent);
extern int GetEventScriptId_800A5AD0(EventEntry* entry);
extern EventEntry* FindEventScript_800A5AE4(int id);
extern int IsEventPointValid_800A6504(int point, int* pos);
extern int IsEventPointInView_800A66A4(int* point, int* eye, unsigned short* rot);
extern int TestEventFlag_800AD0D4(unsigned flag);
extern void ClearEventFlag_800AD124(unsigned flag);
extern int IsPointInViewCone_800A65F0(int* point, int* eye, unsigned short* rot, int range);
extern int GetInventoryCount_800AD254(int id, int table);
extern void ResetLevantActorToIdle_800A8DEC();
extern int savedLevantPos_80091C78[4]; /* main.h: where Levant starts on the next map (useSavedLevantPos_80091C98) */
extern int useSavedLevantPos_80091C98;
extern short savedLevantRot_80091CA8[4];
extern int AddFieldMinion_800A77A0(MapEnt* ent);
extern void ClearFieldMinions_800A7784(void);
extern void LoadLevantAnimSet_800AC708(int set, int arg1);
extern void SetEventHook_800A5F90(EventHookFn hook);
extern void SetVoiceTable_800A6830(void* table);
extern int AreLevantFilesLoaded_800AC768();
extern int levantAnimSet_80091C74; /* main.h (which GAME does not include) */
extern int pointLightRange_8008D3F0;
extern EventNode* mapEventTasks_800B1DA8[1];

#endif
