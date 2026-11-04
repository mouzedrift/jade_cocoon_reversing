#ifndef TU_80036528_H
#define TU_80036528_H

/* camera controller (camera.c) */

#include "engine.h"


/* cameraState_8008D4F0 */
typedef struct
{
    int pad_0[5];
    Vec3i eye_14; // eye (copied to cameraEye_8008D600)
    Vec3i lookAt_20; // look-at
    short roll_2C;     // roll
    short geomScreen_2E; // projection distance (geomScreenBase_8008D51E)
    unsigned char ambientR_30; // scene ambient colour (sceneAmbient_8008D520)
    unsigned char ambientG_31;
    unsigned char ambientB_32;
    unsigned char pad_33;
    SVECTOR lightDir_34;   // scene light direction (sceneLightDir_8008D524)
    SVECTOR lightColor_3C; // scene light colour (sceneLightColor_8008D52C)
    PointLight ent_44[8]; // 0x8008D534 == ent_44[0]
} CameraView;

/* cameraState_8008D4F0.ent_44: accessed through its own symbol (going through cameraState changes the codegen) */
extern PointLight pointLights_8008D534[8];
extern VECTOR cameraEye_8008D600; // camera eye (cameraState_8008D4F0.eye_14)

typedef struct
{
    short a;
    short b;
} ShortPair;

/* one cubic per key: c[n] = {t^3, t^2, t, 1} coefficients */
typedef struct
{
    float c[11][4];
} CamSpline;

/* the buffer of the camera task (cameraTask_8008D4A0->entry.buffer) */
typedef struct CameraCtrl
{
    int target_0; // position the camera follows (Vec3i*, e.g. &levantPos_8008BD18)
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
    Vec3i blendTarget_28;
    int zoomTarget_34;
    Vec3i pos_38;
    int rotY_44;
    CameraView saved_48; // SaveCameraState_80039620
    ShortPair savedShake_14C;
    short angSrc_150;
    short angDst_152;
    int distSrc_154;
    int distDst_158;
    SVECTOR lightDirSrc_15C;   // the scene light direction / colour before the battle intro, and the intro's
    SVECTOR lightDirDst_164;
    SVECTOR lightColorSrc_16C;
    SVECTOR lightColorDst_174;
    int geomScreenSrc_17C; // projection distance, from / to (CameraView.geomScreen_2E)
    int geomScreenDst_180;
    int savedZoom_184;
    int introZoom_188; // cameraZoom_8008B4F8 while the battle intro camera is placed
    Vec3i eyeDst_18C;
    Vec3i lookDst_198;
    Vec3i eyeSrc_1A4;
    Vec3i lookSrc_1B0;
    VECTOR* splinePos_1BC;
    SVECTOR* splineRot_1C0;
    int keyIdx_1C4;
    int keys_1C8[20]; // key times, -1 terminated
    CamSpline* spline_218;
} CameraCtrl;


/* the object returned by the battle overlay's GetSummonedMinionBonePos_800C0FAC */
typedef struct
{
    char pad_0[0x7C];
    int field_7C;
} BattleObj_800C0FAC;

/* levantBattleActions_800B1084: 8-byte table in the overlay area */
typedef struct
{
    int a;
    int b;
} struct_pair8;

void InitCameraTask_800368F8();

void ResetCameraToLevant_800376A8(void);
void StartCameraShake_80037BFC(int strength);

#endif
