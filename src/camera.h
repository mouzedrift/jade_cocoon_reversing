#ifndef TU_80036528_H
#define TU_80036528_H

/* camera controller (camera.c) */

#include "engine.h"


/* cameraState_8008D4F0: the scene camera and lights (main.c; tim.c / SHOPCTRL copy all 0x104 bytes) */
typedef struct
{
    int pad_0[5];
    Vec3i eye_14; // eye (copied to cameraEye_8008D600; also the alias cameraEye_8008D504)
    Vec3i lookAt_20; // look-at
    short roll_2C;     // roll
    short geomScreen_2E; // projection distance (also the alias geomScreenBase_8008D51E)
    unsigned char ambientR_30; // scene ambient colour
    unsigned char ambientG_31;
    unsigned char ambientB_32;
    unsigned char pad_33;
    SVECTOR lightDir_34;   // scene light direction
    SVECTOR lightColor_3C; // scene light colour (vx/vy/vz used)
    PointLight ent_44[8]; // point lights; .range_14 == 0 ends the list (also the alias cameraState_8008D4F0.ent_44)
} CameraView;
extern CameraView cameraState_8008D4F0;

/* cameraState_8008D4F0.ent_44: accessed through its own symbol (going through cameraState changes the codegen) */
extern LVec3 cameraEye_8008D600; // camera eye (cameraState_8008D4F0.eye_14)

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


/* levantBattleActions_800B1084: 8-byte table in the overlay area */
typedef struct
{
    int a;
    int b;
} struct_pair8;


// the buffer of a pad vibration task (vibrationTasks_8008D4B8, one per port)
typedef struct
{
    unsigned char port_0;
    unsigned char pattern_1; // vibrationPatterns_80083B30 row
    unsigned char step_2;
    unsigned char pad_3;
    short timer_4; // frames left of the step
} PadVibTask;

void StartCameraShake_80037BFC(int strength);

void UpdateCameraFollow_80037918(CameraCtrl* cam);
void SaveCameraState_80039620(CameraCtrl* cam);
void SetupCameraOrbit_80038CA8(CameraCtrl* cam);
void SetupBattleIntroCamera_80037F44(CameraCtrl* cam);
void CameraOrbitTask_800374E0(EventEntry* entry, CameraCtrl* cam);
void CameraBattleIntroTask_800369E0(EventEntry* entry, CameraCtrl* cam);
void PlaceBattleIntroCamera_80037C74(CameraCtrl* cam);
void TrackCameraTarget_8003891C(CameraCtrl* cam, Vec3i* target);
void CameraBattleTask_80036AB4(EventEntry* entry, CameraCtrl* cam);
void UpdateCameraMove_80038230(CameraCtrl* cam);
void InitCameraTask_800368F8(EventEntry* entry, CameraCtrl* cam);
void CameraSplineTask_80036BB0(EventEntry* entry, CameraCtrl* cam);
void ComputeCameraMoveAngles_80038D64(CameraCtrl* cam, int* center);
void CameraOrbitReturnTask_800375F8(EventEntry* entry, CameraCtrl* cam);
void UpdateCameraRotation_80039E14(void);
void StartCameraSplineLong_8003970C(int action, int* spline);
void StartCameraSplineShort_8003983C(int action, int* spline);
void TrackCameraTargetBlend_80038A5C(CameraCtrl* cam, int target, Vec3i* blendTarget, int blend);
void MoveCameraToFocusPreset_80038E2C(CameraCtrl* cam, int preset, int eyeRaise);
void UpdateCameraZoom_8003856C(CameraCtrl* cam);
void UpdateScreenScroll_800398B4(CameraCtrl* cam, void* screenPos);
void ResetCameraToLevant_800376A8(void);
void StartBattleCamera_80037748(void);
void MoveBattleCameraForAction_80037828(int side, short action, int force);
void StartPadVibration_80036528(int idx, int pattern);
void SetAreaElementLight_80039ED8(int mode);
void FocusBattleCamera_80037AE0(unsigned short mask);
void SetCameraBattleMode_80037720(void);
void SetCameraZoom_80037A6C(int zoom, int steps);
void UpdatePadVibration_800366A0(EventEntry* entry, PadVibTask* vib);
void SetCameraTarget_80037AC8(int target);
void StopAllPadVibration_80036678(void);
void MoveBattleCameraDefault_800378CC(void);
void MoveBattleCamera_800390F4(CameraCtrl* cam, int mode);
int GetCameraMode_800378F8(void);
short GetCameraBlend_80037A4C(void);
void UpdatePadVibration_80036820(int port);
void FreeCameraTask_800376A0(EventEntry* entry, void* buffer);
void RestoreCameraState_80039698(CameraCtrl* cam);
void EndBattleCamera_80037770(void);
void StopPadVibrationTask_800367F0(int entry, unsigned char* port);
void StopPadVibration_80036658(int idx);
void StartBattleCameraSpline_800377B4(int side, short action, int unused);
void SetCameraBlendTarget_800379DC(int* target, int steps);
void ClearCameraBlendTarget_80037A20(int a0, int steps);
#endif
