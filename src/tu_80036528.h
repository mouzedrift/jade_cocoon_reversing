#ifndef TU_80036528_H
#define TU_80036528_H

/* camera controller (tu_80036528.c) */

typedef struct
{
    int x;
    int y;
    int z;
} struct_v3;

typedef struct
{
    struct_v3 pos;
    SVECTOR rot;
    int field_14;
} CamEntry;

/* cameraState_8008D4F0 */
typedef struct
{
    int pad_0[5];
    struct_v3 field_14; // eye (copied to dword_8008D600)
    struct_v3 field_20; // look-at
    short field_2C;     // roll
    short field_2E;
    unsigned char r_30;
    unsigned char g_31;
    unsigned char b_32;
    unsigned char pad_33;
    SVECTOR rot_34;
    SVECTOR rot_3C;
    CamEntry ent_44[8]; // 0x8008D534 == ent_44[0]
} Block104;

typedef struct
{
    short a;
    short b;
} ShortPair;

/* levantPos_8008BD18 (== saveData_8008B570 + 0x7A8) */
typedef struct
{
    struct_v3 pos;
    SVECTOR rot_C;
} LevantPos;

/* view of saveData_8008B570 for the part globals.h still pads */
typedef struct
{
    char pad_0[0x7A8];
    LevantPos levant_7A8;
} SaveDataLevant;
#define SAVE_LEVANT (((SaveDataLevant*)&saveData_8008B570)->levant_7A8)

/* one cubic per key: c[n] = {t^3, t^2, t, 1} coefficients */
typedef struct
{
    float c[11][4];
} CamSpline;

/* the buffer of the camera task (cameraTask_8008D4A0->entry.buffer) */
typedef struct CameraCtrl
{
    int target_0; // position the camera follows (struct_v3*, e.g. &levantPos_8008BD18)
    unsigned int flags_4;
    short mode_8;
    unsigned short zoomStart_A;
    int t_C; // 0x1000 -> 0 for the src -> dst moves; spline time
    short shake_10;
    unsigned short zoomSteps_12;
    int counter_14;
    int field_18;
    int field_1C;
    int field_20;
    short blend_24;
    short blendStep_26;
    struct_v3 blendTarget_28;
    int zoomTarget_34;
    struct_v3 pos_38;
    int rotY_44;
    Block104 saved_48; // SaveCameraState_80039620
    ShortPair savedShake_14C;
    short angSrc_150;
    short angDst_152;
    int distSrc_154;
    int distDst_158;
    SVECTOR rot_15C;
    SVECTOR rot_164;
    SVECTOR rot_16C;
    SVECTOR rot_174;
    int field2ESrc_17C;
    int field2EDst_180;
    int savedZoom_184;
    int field_188;
    struct_v3 eyeDst_18C;
    struct_v3 lookDst_198;
    struct_v3 eyeSrc_1A4;
    struct_v3 lookSrc_1B0;
    VECTOR* splinePos_1BC;
    SVECTOR* splineRot_1C0;
    int keyIdx_1C4;
    int keys_1C8[20]; // key times, -1 terminated
    CamSpline* spline_218;
} CameraCtrl;


/* the object returned by the battle overlay's sub_800C0FAC */
typedef struct
{
    char pad_0[0x7C];
    int field_7C;
} BattleObj_800C0FAC;

/* dword_800B1084: 8-byte table in the overlay area */
typedef struct
{
    int a;
    int b;
} struct_pair8;

#endif
