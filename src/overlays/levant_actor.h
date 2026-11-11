#ifndef LEVANT_ACTOR_H
#define LEVANT_ACTOR_H
/* Levant's actor (GAME's levantActorTaskDef_800B0864 buffer), which EVENTFNC's map collision also moves */
#include "common.h"
#include "globals.h"
#include "model.h"
#include "effect.h" // FirFilter

typedef struct G2V12
{
    int a;
    int b;
    int c;
} G2V12;

struct G2Path;

// an actor command for Levant or a field minion (GAME's LevantCommand_800A8EC4 / FieldMinionCommand_800A7D40; EVENTFNC's
// event scripts send them): kind 0 walk / 1 run / 2 turn to x/y/z, 3 / 4 play / stop a held animation, 5 play animation
// data, 6 visible, 7 ground move, 8 root motion, 9..11 play a motion
typedef struct GameActorCmd
{
    int actor_0;
    int kind_4;
    int wait_8; // the sender waits: the actor's busy bit is cleared when it is done
    int arg_C;
    int arg2_10;
    unsigned int opts_14; // kind 0..2: the animation (-1: default); 9..11: 1 no turn, 4 / 0x10 / 0x20 action flags, 8
    int x_18;
    int y_1C;
    int z_20;
    void* data_24; // kind 3: the script, kind 9..11: the path
} GameActorCmd;

// Levant's controller object (gameTask_8008B4A4->buffer_24); the field reads disagree on signedness at 0x10/0x14
// (DrawLevantModel_800A9708 uses them as unsigned: same code for its %) and 0x22 (some setters store a signed short)
typedef struct GameLevantActor
{
    // 1: acting, 2: fading out, 4: fading in, 8: animation changed this frame, 0x10: blending from prevAnim_1E,
    // 0x20: continue (ContinueLevantAnim_800AB1A4), 0x100: in battle (field position saved in basePos_60),
    // 0x200: the action plays an effect, 0x400: defending, 0x800: loop between the loop frames, 0x1000: victory
    // pose, 0x2000: action finished, 0x4000: battle stance, 0x8000: the loop wrapped, 0x20000: hidden,
    // 0x40000: no map collision, 0x80000: root motion from basePos_60, 0x200000: turning on the spot,
    // 0x400000: walking path_78, 0x800000: skip the script animation, 0x1000000: capture of the last enemy
    unsigned int flags_0;
    int moveCmd_4; // input bits
    int action_8;  // step of the mode_C state machine (0 / 1: idle animations)
    int mode_C;    // 0 field, 1 battle action, 2 script animation, 3 queued animation
    int frame_10; // animation frame
    int blendFrame_14; // blend animation frame
    unsigned short frameStep_18;
    unsigned short frameFrac_1A;
    short anim_1C;
    short prevAnim_1E;
    short actionAnim_20;
    unsigned short queuedAnim_22;
    short nextAnim_24;
    short blend_26;
    short idleTimer_28;
    short hitRepeat_2A;
    int effect_2C;
    int fade_30;
    int arg_34;
    int targets_38;
    int status_3C;
    Model* model_40;
    char pad_44[4];
    G2V12 pos_48;
    G2V12 savedPos_54;
    G2V12 basePos_60;
    G2V12 rootMotion_6C; // root motion of the current animation frame (SetLevantRootMotion_800AA140)
    struct G2Path* path_78; // scripted walk (flag 0x400000, SetLevantPath_800ABAA4)
    int pathStep_7C;    // step of path_78
    int tri_80; // floor triangle under Levant (mapState_8008B500.meshes_C[mesh_84].tris_4)
    int mesh_84;
    int slideTri_88;  // CollideLevantWithMap_800B6DD4: the triangle and edge it slides along
    int slideEdge_8C;
    MATRIX mats_90[40];
    LVec3 bonePos_590[40];
    FirFilter turn_770;  // input_8: turn speed; output_C.low is added to Levant's facing
    int turnBuf_780[4];
} GameLevantActor;

typedef struct GameLevantActorNode
{
    char pad_0[offsetof(EventNode, entry.buffer)]; // the EventNode up to entry.buffer
    GameLevantActor* buffer_24; // EventNode.entry.buffer
} GameLevantActorNode;

int CollideLevantWithMap_800B6DD4(GameLevantActor* lev);
int FindLevantMesh_800B80C8(GameLevantActor* lev);

#endif
