#ifndef _ACTOR_H_
#define _ACTOR_H_

// one entry of an actor's animation table (Actor.anims_148, 0x3C bytes each; the int before
// the first entry is the count)
typedef struct
{
    signed char id_0;     // model animation id
    unsigned char kind_1; // 0: loaded on demand (sub_8001D8B4), 1: resident
    short start_2;
    short loop_4;
    short end_6;
    short hitFrames_8[10][2]; // converted to frame times by sub_8001F268
    char pad_30[0xC];
} ActorAnim;

// one sound cue of a model animation (ModelAnim.cues_10)
typedef struct
{
    short frame_0;
    short kind_2; // 0: sound cue (SoundCue_8007C750 index), 1: sub_80025B5C
    short arg_4;
    short arg_6;
} ModelAnimCue;

// model animation header (the struct_112 field_54 table, 0x1C bytes each)
typedef struct
{
    unsigned int frameCount_0;
    int field_4;
    int divisor_8;
    int cueCount_C;
    ModelAnimCue* cues_10;
    int field_14;
    int field_18;
} ModelAnim;

// scripted movement (Actor.path_160): one (x, y, z, rot y) step per frame
typedef struct
{
    int count_0;
    int divisor_4;
    short (*steps_8)[4];
} ActorPath;

// draw arguments handed to sub_80046A58 / sub_80047E28 (Actor.draw_164)
typedef struct
{
    int field_0;            // 0x164: struct_112 field_50
    int* pos_4;             // 0x168
    short* rot_8;           // 0x16C
    short* bones_C;         // 0x170: Actor.bones_134
    SVECTOR* boneScale_10;  // 0x174: Actor.boneScale_144
    ModelAnim* anim_14;     // 0x178
    unsigned int frame_18;  // 0x17C
    int drawMode_1C;        // 0x180: Actor.drawMode_8
    int bonePos_20;         // 0x184: Actor.bonePos_1C4
    int* scale_24;          // 0x188: Actor.scale_2C
    unsigned long* ot_28;   // 0x18C
} ActorDrawArgs;

// one command of an actor animation script (Actor.script_D0, run by sub_8001EA48); len_1 counts words
typedef struct
{
    unsigned char op_0;
    unsigned char len_1;
    short frame_2; // runs when the current frame is this one (-2: any frame)
    short field_4;
    short arg_6;
    short field_8;
    short arg_A;
} ActorScriptCmd;

// FirFilterSetup_80014574 / FirFilterStep_80014588 state (the shared headers call it struct_16);
// the actor reads only the low half of the output
typedef struct
{
    int* coefs_0;
    unsigned int taps_4;
    int input_8;
    short output_C;
    short outputHi_E;
} ActorFirFilter;

// actor (CreateActor_8001D45C, actorTasks_8008D43C); names carry the offset, fN fields are still unknown
typedef struct Actor
{
    EventEntry* task_0;         // 0x0: the actorTasks_8008D43C entry that owns this buffer
    unsigned int flags_4;       // 0x4
    int drawMode_8;             // 0x8
    int kind_C;                 // 0xC
    short animLoadState_10;     // 0x10: 0 idle, 1 request animRequest_12, 2 wait for the load
    short animRequest_12;       // 0x12
    short animLoading_14;       // 0x14
    short modelRef_16;          // 0x16: AddModelAnimRef_800201EC slot
    short loopFrame_18;         // 0x18
    short endFrame_1A;          // 0x1A
    short frameFrac_1C;         // 0x1C
    short frameSpeed_1E;        // 0x1E
    short fade_20;              // 0x20
    short fadeDiv_22;           // 0x22
    short blendDiv_24;          // 0x24
    short scale_26;             // 0x26
    short scaleStep_28;         // 0x28
    short scaleTarget_2A;       // 0x2A
    int scale_2C[3];            // 0x2C: baseScale_138 * scale_26
    int pos_38[3];              // 0x38
    int prevPos_44[3];          // 0x44
    int basePos_50[3];          // 0x50
    short rot_5C[3];            // 0x5C
    short pad_62;               // 0x62
    int animDelta_64[3];        // 0x64
    VECTOR target_70;           // 0x70: pad is the turn step
    int ground_80;              // 0x80
    int prevGround_84;          // 0x84
    int f88;                    // 0x88
    int speedScale_8C;          // 0x8C
    int frame_90;               // 0x90
    int prevFrame_94;           // 0x94
    int pathStep_98;            // 0x98
    int anim_9C;                // 0x9C: model animation
    int prevAnim_A0;            // 0xA0
    int nextAnim_A4;            // 0xA4
    int startMode_A8;           // 0xA8
    int blend_AC;               // 0xAC
    int waitCount_B0;           // 0xB0
    int fB4;                    // 0xB4
    int fB8;                    // 0xB8
    short pulse_BC;             // 0xBC
    short pulseRate_BE;         // 0xBE
    short prevAnimIdx_C0;       // 0xC0
    short animIdx_C2;           // 0xC2: index into anims_148
    short scriptPos_C4;         // 0xC4
    short scriptLen_C6;         // 0xC6
    short wait_C8;              // 0xC8
    short waitLen_CA;           // 0xCA
    short fCC;                  // 0xCC
    short fCE;                  // 0xCE
    ActorScriptCmd* script_D0;  // 0xD0
    unsigned int flags_D4;      // 0xD4
    int fD8;                    // 0xD8
    int* pathTarget_DC;         // 0xDC
    short fE0;                  // 0xE0
    short fE2;                  // 0xE2
    int fE4;                    // 0xE4
    int effectMask_E8;          // 0xE8
    int effectKinds_EC;         // 0xEC
    int fF0;                    // 0xF0
    short loopCount_F4;         // 0xF4
    short scaleTarget_F6;       // 0xF6
    int fF8;                    // 0xF8
    short fFC;                  // 0xFC
    short queuedAnim_FE;        // 0xFE
    int f100;                   // 0x100
    int f104;                   // 0x104
    short hitTimes_108[10][2];  // 0x108
    int effect_130;             // 0x130
    short* bones_134;           // 0x134: 4 shorts per bone, -1 terminated; start of the actor's allocation
    int baseScale_138[3];       // 0x138
    SVECTOR* boneScale_144;     // 0x144
    ActorAnim* anims_148;       // 0x148
    int f14C;                   // 0x14C
    RECT image_150;             // 0x150
    short clut_158[2];          // 0x158
    struct_112* model_15C;      // 0x15C
    ActorPath* path_160;        // 0x160
    ActorDrawArgs draw_164;     // 0x164
    int f190;                   // 0x190
    ActorFirFilter turn_194;    // 0x194: input_8 is the turn speed, output_C the smoothed one
    int turnFilterBuf_1A4[8];   // 0x1A4
    char* bonePos_1C4;          // 0x1C4
    MATRIX* boneMatrices_1C8;   // 0x1C8
} Actor;

// actor creation parameters (CreateActor_8001D45C -> sub_8001E574 / sub_8001E7F0; sub_8001D4DC fills one from an actor)
typedef struct
{
    int modelId_0;          // < 0: use model_48
    int kind_4;
    int pos_8[3];
    short rot_14[3];
    short pad_1A;
    int clutRow_1C;         // read as a short
    int animIdx_20;
    int frame_24;           // sub_8001D760 mode
    int frameSpeed_28;      // read as a short
    int blendDiv_2C;        // read as a short
    int visible_30;         // != 1 sets the hidden flag 0x2000
    short* bones_34;
    int* baseScale_38;
    SVECTOR* boneScale_3C;  // 0: all 0x1000
    ActorAnim* anims_40;
    int field_44;
    struct_112* model_48;
    int hasMatrices_4C;     // allocate Actor.boneMatrices_1C8
} ActorDesc;

// actor action (sub_8001E254 / sub_8001E34C)
typedef struct
{
    unsigned int flags_0;
    ActorScriptCmd* script_4;
    int* target_8;
    short turnStep_C;
    short hitAnim_E;        // >= 0: fill Actor.hitTimes_108 from this animation
    int effect_10;
    int effectMask_14;
    int effectKinds_18;
    int field_1C;           // != 0 sets flag 0x800000
    short loopCount_20;
    short scaleTarget_22;
    short nextAnim_24;
    short nextAnim_26;
    short field_28;
    short queuedAnim_2A;
    int field_2C;
    ActorPath* path_30;
} ActorActionDesc;

#endif
