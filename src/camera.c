#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "STDLIB.H"
#include "STDIO.H"
#include "LIBPAD.H"
#include "LIBSND.H"
#include "LIBMCX.H"
#include "LIBPRESS.H"
#include "LIBETC.H"
#include "LIBMCRD.H"
#include "sound.h"
#include "data_decls.h"

#include "camera.h"
#include "effect_data.h"
#include "main.h"

extern CameraView cameraState_8008D4F0;
extern ShortPair screenOffset_8008D474;
// the buffer of a pad vibration task (vibrationTasks_8008D4B8, one per port)
typedef struct
{
    unsigned char port_0;
    unsigned char pattern_1; // vibrationPatterns_80083B30 row
    unsigned char step_2;
    unsigned char pad_3;
    short timer_4; // frames left of the step
} PadVibTask;
extern void UpdatePadVibration_800366A0(EventEntry* entry, PadVibTask* vib);
// Matched
void StartPadVibration_80036528(int idx, int pattern)
{
    EventNode* node;
    int i;
    PadVibTask* vib;
    EventEntry* entry;

    if ((saveData_8008B570.field_0 & 0x40) || (pads_800918E8[(unsigned char)idx][1] >> 4) != 7)
    {
        StopPadVibration_80036658((unsigned char)idx);
        return;
    }
    node = vibrationTasks_8008D4B8;
    for (i = 0; i < (unsigned char)idx; i++)
    {
        node = node->next;
    }
    entry = &node->entry;
    vib = entry->buffer;
    entry->cb_8 = (EventEntryFn)UpdatePadVibration_800366A0;
    vib->pattern_1 = pattern;
    vib->port_0 = idx;
    vib->step_2 = 0;
    vib->timer_4 = vibrationPatterns_80083B30[vib->pattern_1][0].frames_0;
    padVibration_80095460[vib->port_0].motor_2[0] = vibrationPatterns_80083B30[vib->pattern_1][vib->step_2].motor0_2;
    padVibration_80095460[vib->port_0].motor_2[1] = vibrationPatterns_80083B30[vib->pattern_1][vib->step_2].motor1_3;
}
// Matched
void StopPadVibration_80036658(int idx)
{
    padVibration_80095460[(unsigned char)idx].motor_2[0] = 0;
    padVibration_80095460[(unsigned char)idx].motor_2[1] = 0;
}
// Matched
void StopAllPadVibration_80036678(void)
{
    StopPadVibration_80036658(0);
    StopPadVibration_80036658(1);
}
extern void StopPadVibrationTask_800367F0(int entry, unsigned char* port);
// Matched
void UpdatePadVibration_800366A0(EventEntry* entry, PadVibTask* vib)
{
    if (--vib->timer_4 <= 0)
    {
        vib->step_2++;
        vib->timer_4 = vibrationPatterns_80083B30[vib->pattern_1][vib->step_2].frames_0;
        padVibration_80095460[vib->port_0].motor_2[0] = vibrationPatterns_80083B30[vib->pattern_1][vib->step_2].motor0_2;
        padVibration_80095460[vib->port_0].motor_2[1] = vibrationPatterns_80083B30[vib->pattern_1][vib->step_2].motor1_3;
        if (vib->timer_4 < 0)
        {
            entry->cb_8 = (EventEntryFn)StopPadVibrationTask_800367F0;
        }
    }
    if ((saveData_8008B570.field_0 & 0x40) || (pads_800918E8[vib->port_0][1] >> 4) != 7)
    {
        padVibration_80095460[vib->port_0].motor_2[0] = 0;
        padVibration_80095460[vib->port_0].motor_2[1] = 0;
    }
}
// Matched
void StopPadVibrationTask_800367F0(int entry, unsigned char* port)
{
    padVibration_80095460[*port].motor_2[0] = 0;
    padVibration_80095460[*port].motor_2[1] = 0;
}

// Matched
void UpdatePadVibration_80036820(int port)
{
    int state = PadGetState(port << 4);
    if (state != 0)
    {
        if (state == 1)
        {
            padVibration_80095460[port].flags_0 &= 0xFFFE;
        }
        if (!(padVibration_80095460[port].flags_0 & 1))
        {
            PadSetAct(port << 4, (unsigned char*)&padVibration_80095460[port].motor_2[0], 2);
            if (state == 2 || (state == 6 && PadSetActAlign(port << 4, padActAlign_80083844)))
            {
                padVibration_80095460[port].flags_0 |= 1;
            }
        }
    }
}
extern void UpdateCameraFollow_80037918(CameraCtrl* cam);
extern void SaveCameraState_80039620(CameraCtrl* cam);
extern void SetupCameraOrbit_80038CA8(CameraCtrl* cam);
extern void SetupBattleIntroCamera_80037F44(CameraCtrl* cam);
extern void CameraOrbitTask_800374E0();
extern int FindMeshAtPos_800B8184(int a, int b);
extern void CameraBattleIntroTask_800369E0(EventEntry* entry, CameraCtrl* cam);

// Matched
void InitCameraTask_800368F8(EventEntry* entry, CameraCtrl* cam)
{
    if (cam->flags_4 & 0x100)
    {
        SaveCameraState_80039620(cam);
        cam->pos_38.x = levantPos_8008BD18.pos.x;
        cam->pos_38.y = levantPos_8008BD18.pos.y;
        cam->pos_38.z = levantPos_8008BD18.pos.z;
        SetupCameraOrbit_80038CA8(cam);
        cam->mode_8 = 6;
        entry->cb_8 = (EventEntryFn)CameraOrbitTask_800374E0;
    }
    else if (!(cam->flags_4 & 0x2000))
    {
        int mesh = FindMeshAtPos_800B8184(cam->target_0, saveData_8008B570.mapId_2E4[3].field_0);
        if (mesh >= 0)
        {
            saveData_8008B570.mapId_2E4[3].field_0 = mesh;
        }
    }
    else
    {
        SetupBattleIntroCamera_80037F44(cam);
        cam->mode_8 = 2;
        entry->cb_8 = (EventEntryFn)CameraBattleIntroTask_800369E0;
        entry->cb_8(entry, cam);
    }
    UpdateCameraFollow_80037918(cam);
}
extern void PlaceBattleIntroCamera_80037C74(CameraCtrl* cam);
extern void TrackCameraTarget_8003891C(CameraCtrl* cam, Vec3i* target);
extern void DrawBattleStage_800BC90C(CameraCtrl* cam);
extern void CameraBattleTask_80036AB4(EventEntry* entry, CameraCtrl* cam);
extern void StartSceneFadeIn_8001AA04(int a);

// Matched
void CameraBattleIntroTask_800369E0(EventEntry* entry, CameraCtrl* cam)
{
    switch (cam->mode_8)
    {
    case 2:
        if (cam->flags_4 & 4)
        {
            cam->mode_8 += 1;
            PlaceBattleIntroCamera_80037C74(cam);
            StartSceneFadeIn_8001AA04(8);
        }
        break;
    case 3:
        cam->counter_14 = cam->counter_14 + 1;
        if (cam->counter_14 >= 0x3D)
        {
            MoveBattleCamera_800390F4(cam, 1);
            cam->mode_8 = 4;
            entry->cb_8 = (EventEntryFn)CameraBattleTask_80036AB4;
        }
        TrackCameraTarget_8003891C(cam, &levantPos_8008BD18.pos);
        DrawBattleStage_800BC90C(cam);
        break;
    }
}
extern void UpdateCameraMove_80038230(CameraCtrl* cam);
extern void InitCameraTask_800368F8(EventEntry* entry, CameraCtrl* cam);
void CameraSplineTask_80036BB0(EventEntry* entry, CameraCtrl* cam);

// Matched
void CameraBattleTask_80036AB4(EventEntry* entry, CameraCtrl* cam)
{
    CameraCtrl* ctrl = cam;
    if (cam->flags_4 & 4)
    {
        UpdateCameraMove_80038230(cam);
        if (cam->t_C > 0)
        {
            cam->t_C -= 0x100;
        }
        if (cam->t_C < 0)
        {
            cam->t_C = 0;
        }
        if (cam->flags_4 & 4)
        {
            goto run;
        }
    }
    UpdateCameraFollow_80037918(ctrl);
    TrackCameraTarget_8003891C(ctrl, &levantPos_8008BD18.pos);
    ctrl->flags_4 &= ~0x1000;
    ctrl->mode_8 = 0;
    entry->cb_8 = (EventEntryFn)InitCameraTask_800368F8;
    return;
run:
    DrawBattleStage_800BC90C(ctrl);
    if (ctrl->flags_4 & 8)
    {
        ctrl->mode_8 = 5;
        ctrl->keyIdx_1C4 = 0;
        entry->cb_8 = (EventEntryFn)CameraSplineTask_80036BB0;
        ctrl->t_C = 0;
    }
}
#define SPLINE(c) ((int)((c)[0] * t3 + (c)[1] * t2 + (c)[2] * t + (c)[3]))
// Matched
void CameraSplineTask_80036BB0(EventEntry* entry, CameraCtrl* cam)
{
    CameraCtrl* ctrl = cam;
    int i;
    int keyTime;
    int next;
    float t;
    float t2;
    float t3;
    int ang;
    CamSpline* spline;
    VECTOR base;
    int offX;
    int offY;
    int offZ;
    int rotX;
    int rotY;
    int rotZ;

    if (!AdvanceSplineKey_800395D0(&ctrl->keyIdx_1C4, ++ctrl->t_C, &ctrl->keys_1C8[0]) || !(ctrl->flags_4 & 8))
    {
        MoveBattleCamera_800390F4(ctrl, 1);
        ctrl->mode_8 = 4;
        entry->cb_8 = (EventEntryFn)CameraBattleTask_80036AB4;
    }
    else
    {
        i = ctrl->keyIdx_1C4;
        keyTime = ctrl->keys_1C8[i];
        next = i + 1;
        t = (float)(ctrl->t_C - keyTime) / (float)(ctrl->keys_1C8[next] - keyTime);
        t2 = t * t;
        t3 = t2 * t;
        spline = ctrl->spline_218;
        ang = SPLINE(spline[i].c[3]);
        base.vx = SPLINE(spline[i].c[0]);
        base.vy = SPLINE(spline[i].c[1]);
        base.vz = SPLINE(spline[i].c[2]);
        offX = SPLINE(spline[i].c[4]);
        offY = SPLINE(spline[i].c[5]);
        offZ = SPLINE(spline[i].c[6]);
        rotX = base.vx + offX * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096 + offZ * sinTable_80084540[ang & 0xFFF] / 4096;
        rotY = base.vy + offY;
        rotZ = base.vz - offX * sinTable_80084540[ang & 0xFFF] / 4096 + offZ * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096;
        cameraState_8008D4F0.eye_14.x = ctrl->splinePos_1BC->vx + rotX * sinTable_80084540[(ctrl->splineRot_1C0->vy + 0x400) & 0xFFF] / 4096 + rotZ * sinTable_80084540[ctrl->splineRot_1C0->vy & 0xFFF] / 4096;
        cameraState_8008D4F0.eye_14.y = ctrl->splinePos_1BC->vy + rotY;
        cameraState_8008D4F0.eye_14.z = ctrl->splinePos_1BC->vz - rotX * sinTable_80084540[ctrl->splineRot_1C0->vy & 0xFFF] / 4096 + rotZ * sinTable_80084540[(ctrl->splineRot_1C0->vy + 0x400) & 0xFFF] / 4096;
        offX = SPLINE(spline[i].c[8]);
        offY = SPLINE(spline[i].c[9]);
        offZ = SPLINE(spline[i].c[10]);
        rotX = base.vx + offX * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096 + offZ * sinTable_80084540[ang & 0xFFF] / 4096;
        rotY = base.vy + offY;
        rotZ = base.vz - offX * sinTable_80084540[ang & 0xFFF] / 4096 + offZ * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096;
        cameraState_8008D4F0.lookAt_20.x = ctrl->splinePos_1BC->vx + rotX * sinTable_80084540[(ctrl->splineRot_1C0->vy + 0x400) & 0xFFF] / 4096 + rotZ * sinTable_80084540[ctrl->splineRot_1C0->vy & 0xFFF] / 4096;
        cameraState_8008D4F0.lookAt_20.y = ctrl->splinePos_1BC->vy + rotY;
        cameraState_8008D4F0.lookAt_20.z = ctrl->splinePos_1BC->vz - rotX * sinTable_80084540[ctrl->splineRot_1C0->vy & 0xFFF] / 4096 + rotZ * sinTable_80084540[(ctrl->splineRot_1C0->vy + 0x400) & 0xFFF] / 4096;
        cameraState_8008D4F0.geomScreen_2E = SPLINE(spline[i].c[7]);
    }
    TrackCameraTarget_8003891C(ctrl, &levantPos_8008BD18.pos);
    DrawBattleStage_800BC90C(ctrl);
}
#undef SPLINE
extern int DistanceSquaredXZ_8003B860(int* a, int* b);
void ComputeCameraMoveAngles_80038D64(CameraCtrl* cam, int* center);
extern void UpdateCameraMove_80038230(CameraCtrl* cam);
extern void CameraOrbitReturnTask_800375F8(EventEntry* entry, CameraCtrl* cam);
// Matched
void CameraOrbitTask_800374E0(EventEntry* entry, CameraCtrl* cam)
{
    CameraCtrl* ctrl = cam;
    if (cam->flags_4 & 0x100)
    {
        ctrl->angDst_152 += 0x10;
        UpdateCameraMove_80038230(cam);
        if (cam->t_C > 0)
        {
            cam->t_C -= 0x1000;
        }
        if (cam->t_C < 0)
        {
            cam->t_C = 0;
        }
    }
    else
    {
        cam->t_C = 0x1000;
        ctrl->lookSrc_1B0 = cameraState_8008D4F0.lookAt_20;
        ctrl->lookDst_198 = ctrl->saved_48.lookAt_20;
        ctrl->eyeSrc_1A4 = ctrl->saved_48.eye_14;
        ctrl->eyeDst_18C = ctrl->saved_48.eye_14;
        cam->geomScreenSrc_17C = cameraState_8008D4F0.geomScreen_2E;
        cam->geomScreenDst_180 = cameraState_8008D4F0.geomScreen_2E;
        ComputeCameraMoveAngles_80038D64(ctrl, &levantPos_8008BD18.pos.x);
        entry->cb_8 = (EventEntryFn)CameraOrbitReturnTask_800375F8;
    }
}
extern int cameraZoom_8008B4F8;
// Matched
void CameraOrbitReturnTask_800375F8(EventEntry* entry, CameraCtrl* cam)
{
    CameraCtrl* ctrl = cam;
    if (cam->t_C > 0)
    {
        UpdateCameraMove_80038230(cam);
        if (cam->t_C > 0)
        {
            cam->t_C -= 0x1000;
        }
        if (cam->t_C < 0)
        {
            cam->t_C = 0;
        }
    }
    else
    {
        RestoreCameraState_80039698(ctrl);
        UpdateCameraFollow_80037918(ctrl);
        TrackCameraTarget_8003891C(ctrl, &levantPos_8008BD18.pos);
        ctrl->mode_8 = 0;
        entry->cb_8 = (EventEntryFn)InitCameraTask_800368F8;
    }
}
// Matched
void FreeCameraTask_800376A0(void)
{
}
extern void UpdateCameraRotation_80039E14(void);
extern int geomScreenDistance_8008B548;
// Matched
void ResetCameraToLevant_800376A8(void)
{
    CameraCtrl* cam = cameraTask_8008D4A0->entry.buffer;
    UpdateCameraRotation_80039E14();
    cameraZoom_8008B4F8 = 0x1000;
    geomScreenDistance_8008B548 = (geomScreenBase_8008D51E << 12) / 0x1000;
    cam->flags_4 = 0;
    cam->mode_8 = 0;
    cam->blend_24 = 0;
    cam->blendStep_26 = 0x1000;
    cam->target_0 = (int)&levantPos_8008BD18;
}
// Matched
void SetCameraBattleMode_80037720(void)
{
    CameraCtrl* cam = cameraTask_8008D4A0->entry.buffer;
    cam->flags_4 |= 0x2000;
}
// Matched
void StartBattleCamera_80037748(void)
{
    CameraCtrl* cam = cameraTask_8008D4A0->entry.buffer;
    cam->flags_4 |= 4;
}
// Matched
void EndBattleCamera_80037770(void)
{
    CameraCtrl* cam = cameraTask_8008D4A0->entry.buffer;
    cam->flags_4 &= ~4;
    cam->flags_4 &= ~0x2000;
    RestoreCameraState_80039698(cam);
}
extern void StartCameraSplineLong_8003970C(int action, int* spline);
extern void StartCameraSplineShort_8003983C(int action, int* spline);
// Matched
void StartBattleCameraSpline_800377B4(int side, short action)
{
    if (side == 0)
    {
        if (action == 5 || action == 0x1A)
        {
            StartCameraSplineLong_8003970C(action, battleCamSpline0_80083D00);
        }
    }
    else if (side == 1)
    {
        if (action == 2)
        {
            StartCameraSplineShort_8003983C(2, battleCamSpline1_80084330);
        }
    }
}
// Table in the overlay area (outside the linked image), 8 bytes per entry
extern struct_pair8 levantBattleActions_800B1084[];
__asm__(".globl levantBattleActions_800B1084\n.equ levantBattleActions_800B1084,0x800b1084");
// Matched
void MoveBattleCameraForAction_80037828(int side, short action, int force)
{
    CameraCtrl* cam = cameraTask_8008D4A0->entry.buffer;
    if (force)
    {
        MoveBattleCamera_800390F4(cam, 2);
    }
    else if (side == 0)
    {
        if (levantBattleActions_800B1084[action].a != 0x10 && action != 0x11 && action != 0x12)
        {
            MoveBattleCamera_800390F4(cam, 1);
        }
    }
    else if (side != 1 || (unsigned short)(action - 0x11) >= 2)
    {
        MoveBattleCamera_800390F4(cam, 1);
    }
}
// Matched
void MoveBattleCameraDefault_800378CC(void)
{
    MoveBattleCamera_800390F4(cameraTask_8008D4A0->entry.buffer, 1);
}
// Matched
int GetCameraMode_800378F8(void)
{
    return ((CameraCtrl*)cameraTask_8008D4A0->entry.buffer)->mode_8;
}
extern void TrackCameraTargetBlend_80038A5C(CameraCtrl* cam, int target, Vec3i* blendTarget, int blend);
// Matched
void UpdateCameraFollow_80037918(CameraCtrl* cam)
{
    if (cam->flags_4 & 0x10)
    {
        TrackCameraTargetBlend_80038A5C(cam, cam->target_0, &cam->blendTarget_28, cam->blend_24);
        cam->blend_24 += 0x1000 / cam->blendStep_26;
        if (cam->blend_24 > 0x1000)
        {
            cam->blend_24 = 0x1000;
        }
    }
    else
    {
        TrackCameraTargetBlend_80038A5C(cam, cam->target_0, &cam->blendTarget_28, cam->blend_24);
        cam->blend_24 -= 0x1000 / cam->blendStep_26;
        if (cam->blend_24 < 0)
        {
            cam->blend_24 = 0;
        }
    }
}
// Matched
void SetCameraBlendTarget_800379DC(int* target, short steps)
{
    CameraCtrl* cam = cameraTask_8008D4A0->entry.buffer;
    cam->blendTarget_28.x = target[0];
    cam->blendTarget_28.y = target[1];
    cam->blendTarget_28.z = target[2];
    cam->flags_4 |= 0x10;
    cam->blendStep_26 = steps;
}
// Matched
void ClearCameraBlendTarget_80037A20(int a0, short steps)
{
    CameraCtrl* cam = cameraTask_8008D4A0->entry.buffer;
    cam->blendStep_26 = steps;
    cam->flags_4 &= ~0x10;
}
// Matched
short GetCameraBlend_80037A4C(void)
{
    return ((CameraCtrl*)cameraTask_8008D4A0->entry.buffer)->blend_24;
}
// Matched
void SetCameraZoom_80037A6C(int zoom, int steps)
{
    CameraCtrl* cam = cameraTask_8008D4A0->entry.buffer;
    if (steps >= 2)
    {
        cam->zoomTarget_34 = zoom;
        cam->zoomSteps_12 = steps;
        cam->zoomStart_A = *(unsigned short*)&cameraZoom_8008B4F8;
        cam->flags_4 |= 0x20;
    }
    else
    {
        cameraZoom_8008B4F8 = zoom;
        UpdateCameraFollow_80037918(cam);
    }
}
// Matched
void SetCameraTarget_80037AC8(int target)
{
    ((CameraCtrl*)cameraTask_8008D4A0->entry.buffer)->target_0 = target;
}
extern int* GetBattleSelection_800A1E3C(void);
extern BattleObj_800C0FAC* GetSummonedMinionBonePos_800C0FAC(void);
extern unsigned char actingUnit_800C9C7C;
extern void MoveCameraToFocusPreset_80038E2C(CameraCtrl* cam, int preset, int eyeRaise);
extern void CameraBattleTask_80036AB4();
// Matched
void FocusBattleCamera_80037AE0(unsigned short mask)
{
    int sel = 0;
    int cnt = 0;
    int i;
    CameraCtrl* cam = cameraTask_8008D4A0->entry.buffer;
    int* selection;
    int eyeRaise;
    for (i = 0; i < 3; i++)
    {
        if ((mask >> (i + 4)) & 1)
        {
            sel = i;
            cnt++;
        }
    }
    if (cnt != 1)
    {
        sel = 3;
    }
    if (*(unsigned short*)&cam->mode_8 == 4 || *(unsigned short*)&cam->mode_8 == 5)
    {
        selection = GetBattleSelection_800A1E3C();
        if (actingUnit_800C9C7C == 0)
        {
            eyeRaise = 0;
        }
        else
        {
            eyeRaise = GetSummonedMinionBonePos_800C0FAC()->field_7C + 0xF5;
        }
        MoveCameraToFocusPreset_80038E2C(cam, battleCamFocusIndex_80083CE8[selection[0] - 1][sel], eyeRaise);
        *(unsigned short*)&cam->mode_8 = 4;
        cameraTask_8008D4A0->entry.cb_8 = (EventEntryFn)CameraBattleTask_80036AB4;
    }
}
// Matched
void StartCameraShake_80037BFC(void)
{
    CameraCtrl* cam = cameraTask_8008D4A0->entry.buffer;
    cam->shake_10 = 0;
    cam->flags_4 |= 0xC0;
}
// Matched
void StartCameraOrbit_80037C24(void)
{
    CameraCtrl* cam = cameraTask_8008D4A0->entry.buffer;
    cam->flags_4 |= 0x100;
}
// Matched
void StopCameraOrbit_80037C4C(void)
{
    CameraCtrl* cam = cameraTask_8008D4A0->entry.buffer;
    cam->flags_4 &= ~0x100;
}
// Matched
void PlaceBattleIntroCamera_80037C74(CameraCtrl* cam)
{
    int sel;

    cam->counter_14 = 0;
    cam->t_C = 0;
    screenOffset_8008D474.a = 0;
    screenOffset_8008D474.b = 0;
    cameraState_8008D4F0.ambientR_30 = cameraState_8008D4F0.ambientG_31 = cameraState_8008D4F0.ambientB_32 = 0x40;
    cameraState_8008D4F0.roll_2C = 0;
    if (unknownFlags_8008D678 & 0x2000000)
    {
        sel = 1;
    }
    else
    {
        sel = 0;
    }
    cameraState_8008D4F0.lookAt_20.x = cam->pos_38.x + (sinTable_80084540[(cam->rotY_44 + 0x400) & 0xFFF] * battleCamIntroPresets_80083BE4[sel].x1 / 4096 + sinTable_80084540[cam->rotY_44 & 0xFFF] * battleCamIntroPresets_80083BE4[sel].z1 / 4096);
    cameraState_8008D4F0.lookAt_20.y = levantPos_8008BD18.pos.y + battleCamIntroPresets_80083BE4[sel].y1;
    cameraState_8008D4F0.lookAt_20.z = cam->pos_38.z + (-sinTable_80084540[cam->rotY_44 & 0xFFF] * battleCamIntroPresets_80083BE4[sel].x1 / 4096 + sinTable_80084540[(cam->rotY_44 + 0x400) & 0xFFF] * battleCamIntroPresets_80083BE4[sel].z1 / 4096);
    cameraState_8008D4F0.eye_14.x = cam->pos_38.x + (sinTable_80084540[(cam->rotY_44 + 0x400) & 0xFFF] * battleCamIntroPresets_80083BE4[sel].x0 / 4096 + sinTable_80084540[cam->rotY_44 & 0xFFF] * battleCamIntroPresets_80083BE4[sel].z0 / 4096);
    cameraState_8008D4F0.eye_14.y = levantPos_8008BD18.pos.y + battleCamIntroPresets_80083BE4[sel].y0;
    cameraState_8008D4F0.eye_14.z = cam->pos_38.z + (-sinTable_80084540[cam->rotY_44 & 0xFFF] * battleCamIntroPresets_80083BE4[sel].x0 / 4096 + sinTable_80084540[(cam->rotY_44 + 0x400) & 0xFFF] * battleCamIntroPresets_80083BE4[sel].z0 / 4096);
    cameraState_8008D4F0.geomScreen_2E = battleCamIntroPresets_80083BE4[sel].geomScreen_8;
    setVector(&cameraState_8008D4F0.lightDir_34, cam->lightDirDst_164.vx, cam->lightDirDst_164.vy, cam->lightDirDst_164.vz);
    setVector(&cameraState_8008D4F0.lightColor_3C, cam->lightColorDst_174.vx, cam->lightColorDst_174.vy, cam->lightColorDst_174.vz);
    cameraState_8008D4F0.ent_44[0].color_C.vx = 0x800;
    cameraState_8008D4F0.ent_44[0].color_C.vy = 0x800;
    cameraState_8008D4F0.ent_44[0].color_C.vz = 0x800;
    cameraZoom_8008B4F8 = cam->introZoom_188;
}
// Matched
void SetupBattleIntroCamera_80037F44(CameraCtrl* cam)
{
    int i;

    SaveCameraState_80039620(cam);
    cam->geomScreenSrc_17C = cameraState_8008D4F0.geomScreen_2E;
    cam->geomScreenDst_180 = 0xA0;
    cam->lookSrc_1B0 = cameraState_8008D4F0.lookAt_20;
    cam->lookDst_198.x = saveData_8008B570.levant_7A8.pos.x;
    cam->lookDst_198.y = saveData_8008B570.levant_7A8.pos.y - 0xFA;
    cam->lookDst_198.z = saveData_8008B570.levant_7A8.pos.z;
    cam->eyeSrc_1A4 = cameraState_8008D4F0.eye_14;
    cam->eyeDst_18C.x = saveData_8008B570.levant_7A8.pos.x + sinTable_80084540[saveData_8008B570.levant_7A8.rot.vy & 0xFFF] * 200 / 4096;
    cam->eyeDst_18C.y = saveData_8008B570.levant_7A8.pos.y - 0xFA;
    cam->eyeDst_18C.z = saveData_8008B570.levant_7A8.pos.z + sinTable_80084540[(saveData_8008B570.levant_7A8.rot.vy + 0x400) & 0xFFF] * 200 / 4096;
    cam->pos_38.x = saveData_8008B570.levant_7A8.pos.x + sinTable_80084540[saveData_8008B570.levant_7A8.rot.vy & 0xFFF] * 500 / 4096;
    cam->pos_38.y = saveData_8008B570.levant_7A8.pos.y + 0xFA;
    cam->pos_38.z = saveData_8008B570.levant_7A8.pos.z + sinTable_80084540[(saveData_8008B570.levant_7A8.rot.vy + 0x400) & 0xFFF] * 500 / 4096;
    cam->rotY_44 = saveData_8008B570.levant_7A8.rot.vy;
    for (i = 7; i >= 0; i--)
    {
        cameraState_8008D4F0.ent_44[i].range_14 = 0;
    }
    cameraState_8008D4F0.ent_44[0].pos_0 = cam->pos_38;
    setVector(&cameraState_8008D4F0.ent_44[0].color_C, 0, 0, 0);
    cameraState_8008D4F0.ent_44[0].range_14 = 0xEA6;
    cameraState_8008D4F0.ent_44[0].pos_0.y -= 1000;
    cam->lightDirSrc_15C = cameraState_8008D4F0.lightDir_34;
    cam->lightDirDst_164.vx = 0x7FC;
    cam->lightDirDst_164.vy = -0xAA6;
    cam->lightDirDst_164.vz = 0x8DE;
    cam->lightColorSrc_16C = cameraState_8008D4F0.lightColor_3C;
    cam->lightColorDst_174.vx = 0x1000;
    cam->lightColorDst_174.vy = 0x1000;
    cam->lightColorDst_174.vz = 0x1000;
    cam->savedZoom_184 = cameraZoom_8008B4F8;
    cam->introZoom_188 = 0x1000;
    ComputeCameraMoveAngles_80038D64(cam, &levantPos_8008BD18.pos.x);
    cam->t_C = 0x1000;
}
#define EASE(p) (0x1000 - sinTable_80084540[(((p)->t_C / 4) + 0x400) & 0xFFF])
// Matched
void UpdateCameraMove_80038230(CameraCtrl* cam)
{
    short ang;
    short dist;

    cameraState_8008D4F0.lookAt_20.x = cam->lookDst_198.x + (cam->lookSrc_1B0.x - cam->lookDst_198.x) * EASE(cam) / 4096;
    cameraState_8008D4F0.lookAt_20.y = cam->lookDst_198.y + (cam->lookSrc_1B0.y - cam->lookDst_198.y) * EASE(cam) / 4096;
    cameraState_8008D4F0.lookAt_20.z = cam->lookDst_198.z + (cam->lookSrc_1B0.z - cam->lookDst_198.z) * EASE(cam) / 4096;

    ang = *(unsigned short*)&cam->angDst_152 + (cam->angSrc_150 - cam->angDst_152) * EASE(cam) / 4096;
    dist = *(unsigned short*)&cam->distDst_158 + (cam->distSrc_154 - cam->distDst_158) * EASE(cam) / 4096;
    cameraState_8008D4F0.eye_14.x = cam->pos_38.x + dist * sinTable_80084540[ang & 0xFFF] / 4096;
    cameraState_8008D4F0.eye_14.y = cam->eyeDst_18C.y + (cam->eyeSrc_1A4.y - cam->eyeDst_18C.y) * EASE(cam) / 4096;
    cameraState_8008D4F0.eye_14.z = cam->pos_38.z + dist * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096;
    cameraState_8008D4F0.geomScreen_2E = *(unsigned short*)&cam->geomScreenDst_180 + (cam->geomScreenSrc_17C - cam->geomScreenDst_180) * EASE(cam) / 4096;
    if (cam->t_C == 0)
    {
        cameraState_8008D4F0.eye_14 = cam->eyeDst_18C;
    }
    TrackCameraTarget_8003891C(cam, &levantPos_8008BD18.pos);
}
extern double pow(double, double);
// Matched
void UpdateCameraZoom_8003856C(CameraCtrl* cam)
{
    unsigned int target;
    float zoom;

    prevCameraZoom_8008D4BC = cameraZoom_8008B4F8;
    if (GetCameraMode_800378F8() != 0)
    {
        return;
    }
    target = cam->zoomTarget_34;
    if (target < (unsigned int)cameraZoom_8008B4F8 && (cam->flags_4 & 0x20))
    {

        zoom = (float)cameraZoom_8008B4F8 * pow((float)target / (float)cam->zoomStart_A, 1.0f / (float)cam->zoomSteps_12);
        cameraZoom_8008B4F8 = zoom;
        if ((unsigned int)cam->zoomTarget_34 >= (unsigned int)cameraZoom_8008B4F8)
        {
            cam->flags_4 &= ~0x20;
        }
    }
    else if ((unsigned int)cameraZoom_8008B4F8 < target && (cam->flags_4 & 0x20))
    {

        zoom = (float)cameraZoom_8008B4F8 * pow((float)target / (float)cam->zoomStart_A, 1.0f / (float)cam->zoomSteps_12);
        cameraZoom_8008B4F8 = zoom;
        if ((unsigned int)cameraZoom_8008B4F8 >= (unsigned int)cam->zoomTarget_34)
        {
            cam->flags_4 &= ~0x20;
        }
    }
    if (cameraZoom_8008B4F8 < 0x1000)
    {
        cameraZoom_8008B4F8 = 0x1000;
        cam->flags_4 &= ~0x20;
    }
    if (cameraZoom_8008B4F8 > 0x10000)
    {
        cameraZoom_8008B4F8 = 0x10000;
        cam->flags_4 &= ~0x20;
    }
    if (zoomLimit_8008D66C * 4 < geomScreenBase_8008D51E * cameraZoom_8008B4F8 / 4096)
    {
        cameraZoom_8008B4F8 = (zoomLimit_8008D66C << 14) / geomScreenBase_8008D51E;
        if (cameraZoom_8008B4F8 < 0x1000)
        {
            cameraZoom_8008B4F8 = 0x1000;
        }
        cam->flags_4 &= ~0x20;
    }
}
extern void UpdateCameraZoom_8003856C(CameraCtrl* cam);
extern void UpdateScreenScroll_800398B4(CameraCtrl* cam, void* screenPos);
extern int prevCameraZoom_8008D4BC;
typedef struct
{
    DVECTOR xy;
    int z;
} ScreenPosZ;
extern ScreenPosZ cameraTargetScreenPos_8008D668;
// Matched
void TrackCameraTarget_8003891C(CameraCtrl* cam, Vec3i* target)
{
    SVECTOR sv;
    long pr;
    long flag;
    int screen;
    unsigned int prevScreen;
    UpdateCameraRotation_80039E14();
    UpdateCameraZoom_8003856C(cam);
    screen = geomScreenBase_8008D51E * cameraZoom_8008B4F8;
    prevScreen = geomScreenBase_8008D51E * prevCameraZoom_8008D4BC;
    sv.vx = target->x;
    sv.vy = target->y;
    sv.vz = target->z;
    sv.vy -= 0x15E;
    sv.vx -= cameraEye_8008D600.vx;
    sv.vy -= cameraEye_8008D600.vy;
    sv.vz -= cameraEye_8008D600.vz;
    geomScreenDistance_8008B548 = prevScreen >> 12;
    SetGeomScreen(screen / 4096);
    cameraTargetScreenPos_8008D668.z = RotTransPers(&sv, (long*)&cameraTargetScreenPos_8008D668.xy, &pr, &flag);
    if (flag < 0)
    {
        cameraTargetScreenPos_8008D668.xy.vx = 0xA0;
        cameraTargetScreenPos_8008D668.xy.vy = 0x78;
    }
    SetGeomScreen(geomScreenDistance_8008B548);
    if (!(cam->flags_4 & 0x800))
    {
        UpdateScreenScroll_800398B4(cam, &cameraTargetScreenPos_8008D668);
    }
}
// Matched
void TrackCameraTargetBlend_80038A5C(CameraCtrl* cam, int target, Vec3i* blendTarget, int blend)
{
    Vec3i* targetPos = (Vec3i*)target;
    SVECTOR sv;
    SVECTOR sv2;
    ScreenPosZ blendScreenPos;
    long pr;
    long flag;
    int screen;
    unsigned int prevScreen;

    UpdateCameraRotation_80039E14();
    UpdateCameraZoom_8003856C(cam);
    prevScreen = geomScreenBase_8008D51E * prevCameraZoom_8008D4BC;
    screen = geomScreenBase_8008D51E * cameraZoom_8008B4F8;
    geomScreenDistance_8008B548 = prevScreen >> 12;
    SetGeomScreen(screen / 4096);
    sv.vx = targetPos->x;
    sv.vy = targetPos->y;
    sv.vz = targetPos->z;
    sv.vy -= 0x15E;
    sv.vx -= cameraEye_8008D600.vx;
    sv.vy -= cameraEye_8008D600.vy;
    sv.vz -= cameraEye_8008D600.vz;
    cameraTargetScreenPos_8008D668.z = RotTransPers(&sv, (long*)&cameraTargetScreenPos_8008D668.xy, &pr, &flag);
    sv2.vx = blendTarget->x;
    sv2.vy = blendTarget->y;
    sv2.vz = blendTarget->z;
    sv2.vy -= 0x15E;
    sv2.vx -= cameraEye_8008D600.vx;
    sv2.vy -= cameraEye_8008D600.vy;
    sv2.vz -= cameraEye_8008D600.vz;
    blendScreenPos.z = RotTransPers(&sv2, (long*)&blendScreenPos.xy, &pr, &flag);
    cameraTargetScreenPos_8008D668.xy.vx += (blendScreenPos.xy.vx - cameraTargetScreenPos_8008D668.xy.vx) * blend / 4096;
    cameraTargetScreenPos_8008D668.xy.vy += (blendScreenPos.xy.vy - cameraTargetScreenPos_8008D668.xy.vy) * blend / 4096;
    cameraTargetScreenPos_8008D668.z += (blendScreenPos.z - cameraTargetScreenPos_8008D668.z) * blend / 4096;
    SetGeomScreen(geomScreenDistance_8008B548);
    if (!(cam->flags_4 & 0x800))
    {
        UpdateScreenScroll_800398B4(cam, &cameraTargetScreenPos_8008D668);
    }
}
// Matched
void SetupCameraOrbit_80038CA8(CameraCtrl* cam)
{
    CameraCtrl* ctrl = cam;
    cam->t_C = 0x1000;
    cam->flags_4 &= ~8;
    ctrl->lookSrc_1B0 = cameraState_8008D4F0.lookAt_20;
    ctrl->lookDst_198 = saveData_8008B570.levant_7A8.pos;
    ctrl->eyeSrc_1A4 = cameraState_8008D4F0.eye_14;
    ctrl->eyeDst_18C = cameraState_8008D4F0.eye_14;
    cam->geomScreenSrc_17C = cameraState_8008D4F0.geomScreen_2E;
    cam->geomScreenDst_180 = cameraState_8008D4F0.geomScreen_2E;
    ComputeCameraMoveAngles_80038D64(ctrl, &saveData_8008B570.levant_7A8.pos.x);
}
extern int DistanceSquaredXZ_8003B860(int* a, int* b);

// Matched
void ComputeCameraMoveAngles_80038D64(CameraCtrl* cam, int* center)
{
    int diff;
    cam->angSrc_150 = ratan2Difference_8003B9E0(center, cameraEye_8008D504) & 0xFFF;
    cam->distSrc_154 = ISqrt_8003B918(DistanceSquaredXZ_8003B860(center, cameraEye_8008D504));
    cam->angDst_152 = ratan2Difference_8003B9E0(center, (int*)&cam->eyeDst_18C) & 0xFFF;
    cam->distDst_158 = ISqrt_8003B918(DistanceSquaredXZ_8003B860(center, (int*)&cam->eyeDst_18C));
    diff = cam->angDst_152 - cam->angSrc_150;
    if (diff > 0x800)
    {
        cam->angDst_152 = *(unsigned short*)&cam->angDst_152 - 0x1000;
    }
    else if (diff < -0x800)
    {
        cam->angDst_152 = *(unsigned short*)&cam->angDst_152 + 0x1000;
    }
}
// Matched
void MoveCameraToFocusPreset_80038E2C(CameraCtrl* cam, int preset, int eyeRaise)
{
    CameraCtrl* ctrl = cam;

    cam->t_C = 0x1000;
    cam->flags_4 &= ~8;
    ctrl->lookSrc_1B0 = cameraState_8008D4F0.lookAt_20;
    ctrl->lookDst_198 = ctrl->pos_38;
    ctrl->lookDst_198.y = saveData_8008B570.levant_7A8.pos.y + battleCamFocusPresets_80083C70[(unsigned short)preset].y1;
    ctrl->lookDst_198.z += -sinTable_80084540[cam->rotY_44 & 0xFFF] * battleCamFocusPresets_80083C70[(unsigned short)preset].x1 / 4096 + sinTable_80084540[(cam->rotY_44 + 0x400) & 0xFFF] * battleCamFocusPresets_80083C70[(unsigned short)preset].z1 / 4096;
    ctrl->lookDst_198.x += sinTable_80084540[(cam->rotY_44 + 0x400) & 0xFFF] * battleCamFocusPresets_80083C70[(unsigned short)preset].x1 / 4096 + sinTable_80084540[cam->rotY_44 & 0xFFF] * battleCamFocusPresets_80083C70[(unsigned short)preset].z1 / 4096;
    ctrl->eyeSrc_1A4 = cameraState_8008D4F0.eye_14;
    ctrl->eyeDst_18C = ctrl->pos_38;
    ctrl->eyeDst_18C.y = saveData_8008B570.levant_7A8.pos.y + battleCamFocusPresets_80083C70[(unsigned short)preset].y0 + eyeRaise;
    ctrl->eyeDst_18C.z += -sinTable_80084540[cam->rotY_44 & 0xFFF] * battleCamFocusPresets_80083C70[(unsigned short)preset].x0 / 4096 + sinTable_80084540[(cam->rotY_44 + 0x400) & 0xFFF] * battleCamFocusPresets_80083C70[(unsigned short)preset].z0 / 4096;
    ctrl->eyeDst_18C.x += sinTable_80084540[(cam->rotY_44 + 0x400) & 0xFFF] * battleCamFocusPresets_80083C70[(unsigned short)preset].x0 / 4096 + sinTable_80084540[cam->rotY_44 & 0xFFF] * battleCamFocusPresets_80083C70[(unsigned short)preset].z0 / 4096;
    cam->geomScreenSrc_17C = cameraState_8008D4F0.geomScreen_2E;
    cam->geomScreenDst_180 = battleCamFocusPresets_80083C70[(unsigned short)preset].geomScreen_8;
    ComputeCameraMoveAngles_80038D64(ctrl, (int*)&cam->pos_38);
}
extern int actorSide_800A85B8;
extern int DistanceSquared3D_8003B80C(int* a, int* b);
// Matched
void MoveBattleCamera_800390F4(CameraCtrl* cam, int mode)
{
    int sel = 0;
    unsigned int i;
    unsigned int best;
    unsigned int dist;
    Vec3i eye;

    cam->t_C = 0x1000;
    cam->flags_4 &= ~8;
    if (mode == 0)
    {
        sel = rand() & 3;
    }
    else if (mode == 2)
    {
        sel = 3;
    }
    else if (unknownFlags_8008D678 & 0x2000000)
    {
        if (actorSide_800A85B8 < 0)
        {
            sel = 4;
        }
        else if (actorSide_800A85B8 == 0)
        {
            sel = 1;
        }
        else
        {
            sel = 2;
        }
    }
    else
    {
        best = -1;
        for (i = 0; i < 1; i++)
        {
                    eye = cam->pos_38;
            eye.y = saveData_8008B570.levant_7A8.pos.y + battleCamPresets_80083C0C[sel].y1;
            eye.z += -sinTable_80084540[cam->rotY_44 & 0xFFF] * battleCamPresets_80083C0C[sel].x1 / 4096 + sinTable_80084540[(cam->rotY_44 + 0x400) & 0xFFF] * battleCamPresets_80083C0C[sel].z1 / 4096;
            eye.x += sinTable_80084540[(cam->rotY_44 + 0x400) & 0xFFF] * battleCamPresets_80083C0C[sel].x1 / 4096 + sinTable_80084540[cam->rotY_44 & 0xFFF] * battleCamPresets_80083C0C[sel].z1 / 4096;
            dist = DistanceSquared3D_8003B80C((int*)&cameraState_8008D4F0.eye_14, (int*)&eye);
            if (dist < best)
            {
                best = dist;
                sel = i;
            }
        }
    }
    cam->lookSrc_1B0 = cameraState_8008D4F0.lookAt_20;
    cam->lookDst_198 = cam->pos_38;
    cam->lookDst_198.y = saveData_8008B570.levant_7A8.pos.y + battleCamPresets_80083C0C[sel].y1;
    cam->lookDst_198.z += -sinTable_80084540[cam->rotY_44 & 0xFFF] * battleCamPresets_80083C0C[sel].x1 / 4096 + sinTable_80084540[(cam->rotY_44 + 0x400) & 0xFFF] * battleCamPresets_80083C0C[sel].z1 / 4096;
    cam->lookDst_198.x += sinTable_80084540[(cam->rotY_44 + 0x400) & 0xFFF] * battleCamPresets_80083C0C[sel].x1 / 4096 + sinTable_80084540[cam->rotY_44 & 0xFFF] * battleCamPresets_80083C0C[sel].z1 / 4096;
    cam->eyeSrc_1A4 = cameraState_8008D4F0.eye_14;
    cam->eyeDst_18C = cam->pos_38;
    cam->eyeDst_18C.y = saveData_8008B570.levant_7A8.pos.y + battleCamPresets_80083C0C[sel].y0;
    cam->eyeDst_18C.z += -sinTable_80084540[cam->rotY_44 & 0xFFF] * battleCamPresets_80083C0C[sel].x0 / 4096 + sinTable_80084540[(cam->rotY_44 + 0x400) & 0xFFF] * battleCamPresets_80083C0C[sel].z0 / 4096;
    cam->eyeDst_18C.x += sinTable_80084540[(cam->rotY_44 + 0x400) & 0xFFF] * battleCamPresets_80083C0C[sel].x0 / 4096 + sinTable_80084540[cam->rotY_44 & 0xFFF] * battleCamPresets_80083C0C[sel].z0 / 4096;
    cam->geomScreenSrc_17C = cameraState_8008D4F0.geomScreen_2E;
    cam->geomScreenDst_180 = battleCamPresets_80083C0C[sel].geomScreen_8;
    ComputeCameraMoveAngles_80038D64(cam, (int*)&cam->pos_38);
}
// Matched
int AdvanceSplineKey_800395D0(int* pIdx, int value, int* table)
{
    if (value >= table[*pIdx + 1])
    {
        *pIdx = *pIdx + 1;
    }
    return table[*pIdx + 1] != -1;
}

// Matched
void SaveCameraState_80039620(CameraCtrl* cam)
{
    cam->saved_48 = cameraState_8008D4F0;
    cam->savedZoom_184 = cameraZoom_8008B4F8;
    cam->savedShake_14C = screenOffset_8008D474;
}
// Matched
void RestoreCameraState_80039698(CameraCtrl* cam)
{
    cameraState_8008D4F0 = cam->saved_48;
    cameraZoom_8008B4F8 = cam->savedZoom_184;
    screenOffset_8008D474 = cam->savedShake_14C;
}
extern int GetLevantActionEndFrame_800AB4D8(int a);
// Matched
void StartCameraSplineLong_8003970C(int action, int* spline)
{
    CameraCtrl* cam = cameraTask_8008D4A0->entry.buffer;
    struct_pair8* actions = levantBattleActions_800B1084;
    int* keys;
    int endFrame;
    cam->field_1C = actions[(short)action].b;
    cam->spline_218 = (CamSpline*)spline;
    cam->flags_4 |= 8;
    endFrame = (short)GetLevantActionEndFrame_800AB4D8(0xE);
    if (((settingsFlags_8008B58C.word & 0x200000) >> 21) == 1)
    {
        keys = cam->keys_1C8;
        cam->keys_1C8[0] = 0;
        keys[1] = endFrame + 0x32;
        keys[2] = endFrame + 0x46;
        keys[3] = endFrame + 0x5A;
        keys[4] = endFrame + 0x6E;
        keys[5] = endFrame + 0x97;
        keys[6] = endFrame + 0xC8;
        keys[7] = endFrame + 0x10E;
        keys[8] = endFrame + 0x169;
        keys[9] = endFrame + 0x258;
        keys[10] = -1;
    }
    else
    {
        keys = cam->keys_1C8;
        cam->keys_1C8[0] = 0;
        keys[1] = endFrame + 0x32;
        keys[2] = endFrame + 0x46;
        keys[3] = endFrame + 0x5A;
        keys[4] = endFrame + 0x6E;
        keys[5] = endFrame + 0x97;
        keys[6] = endFrame + 0xC8;
        keys[7] = endFrame + 0x10E;
        keys[8] = -1;
    }
    cam->splinePos_1BC = (VECTOR*)&levantPos_8008BD18.pos;
    cam->splineRot_1C0 = &levantPos_8008BD18.rot;
}
// Matched
void StartCameraSplineShort_8003983C(int action, int* spline)
{
    CameraCtrl* cam = cameraTask_8008D4A0->entry.buffer;
    struct_pair8* actions = levantBattleActions_800B1084;
    int* keys;
    cam->field_1C = actions[(short)action].b;
    keys = cam->keys_1C8;
    cam->spline_218 = (CamSpline*)spline;
    cam->keys_1C8[0] = 0;
    cam->flags_4 |= 8;
    keys[1] = 0x28;
    keys[2] = 0x50;
    keys[3] = 0x78;
    keys[4] = -1;
    cam->splinePos_1BC = (VECTOR*)&levantPos_8008BD18.pos;
    cam->splineRot_1C0 = &levantPos_8008BD18.rot;
}
typedef struct
{
    short x, y, w, h;
} ShortRect;
extern ShortRect viewport_8008D420;
extern short* tileSets_8008D654;
extern DRAWENV drawEnv_8008D698[2];
#define CLAMP_HALF(v, lim) ((v) < -(lim) / 2 ? -(lim) / 2 : ((lim) / 2 < (v) ? (lim) / 2 : (v)))
// Matched
void UpdateScreenScroll_800398B4(CameraCtrl* cam, void* screenPos)
{
    ScreenPosZ* pos = screenPos;
    DR_AREA area;
    RECT rect;
    short* tiles;
    int scale;
    int rangeX;
    int rangeY;

    if (!(cam->flags_4 & 4))
    {
        screenOffset_8008D474.a = screenOffset_8008D474.a - (pos->xy.vx - (viewport_8008D420.x + viewport_8008D420.w / 2));
        screenOffset_8008D474.b = screenOffset_8008D474.b - (pos->xy.vy - (viewport_8008D420.y + viewport_8008D420.h / 2));
        tiles = tileSets_8008D654;
        scale = cameraZoom_8008B4F8 << 5;
        rangeX = tiles[4] * scale / 4096 - viewport_8008D420.w;
        rangeY = tiles[5] * scale / 4096 - viewport_8008D420.h;
        screenOffset_8008D474.a = CLAMP_HALF(screenOffset_8008D474.a, rangeX);
        screenOffset_8008D474.b = CLAMP_HALF(screenOffset_8008D474.b, rangeY);
        screenOffset_8008D474.a = screenOffset_8008D474.a - (display_8008B4D8.w_C / 2 - (viewport_8008D420.x + viewport_8008D420.w / 2));
        screenOffset_8008D474.b = screenOffset_8008D474.b - (display_8008B4D8.h_E / 2 - (viewport_8008D420.y + viewport_8008D420.h / 2));
        rect.x = drawEnv_8008D698[bDoubleBuffer_8008D428].clip.x + viewport_8008D420.x;
        rect.y = drawEnv_8008D698[bDoubleBuffer_8008D428].clip.y + viewport_8008D420.y;
        rect.w = viewport_8008D420.w;
        rect.h = viewport_8008D420.h;
        SetDrawArea(&area, &rect);
        *(DR_AREA*)primAllocPtr_800960A8[bDoubleBuffer_8008D428] = area;
        addPrim(pOT_8008D3EC, primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
        primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 0xC;
        rect.x = drawEnv_8008D698[bDoubleBuffer_8008D428].clip.x;
        rect.y = drawEnv_8008D698[bDoubleBuffer_8008D428].clip.y;
        rect.w = drawEnv_8008D698[bDoubleBuffer_8008D428].clip.w;
        rect.h = drawEnv_8008D698[bDoubleBuffer_8008D428].clip.h;
        SetDrawArea(&area, &rect);
        *(DR_AREA*)primAllocPtr_800960A8[bDoubleBuffer_8008D428] = area;
        addPrim(pOT_8008D5F4 + 2, primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
        primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 0xC;
        if (cam->flags_4 & 0x40)
        {
            if (cam->flags_4 & 0x80)
            {
                screenOffset_8008D474.b += cameraShakeOffsets_80083BD4[cam->shake_10];
            }
            else
            {
                screenOffset_8008D474.a += cameraShakeOffsets_80083BD4[cam->shake_10];
            }
            if ((unsigned short)++cam->shake_10 >= 15)
            {
                cam->flags_4 &= ~0x40;
            }
        }
    }
    else if (cam->flags_4 & 0x40)
    {
        if (cam->flags_4 & 0x80)
        {
            screenOffset_8008D474.b = cameraShakeOffsets_80083BD4[cam->shake_10];
        }
        else
        {
            screenOffset_8008D474.a = cameraShakeOffsets_80083BD4[cam->shake_10];
        }
        if ((unsigned short)++cam->shake_10 >= 15)
        {
            screenOffset_8008D474.a = 0;
            screenOffset_8008D474.b = 0;
            cam->flags_4 &= ~0x40;
        }
    }
}
extern SVECTOR cameraRot_8008D4C8;
extern void SetGteLightAndCamera_8004D0E8(void);
// Matched
void UpdateCameraRotation_80039E14(void)
{
    VECTOR dir;
    int yaw;
    cameraEye_8008D600.vx = cameraState_8008D4F0.eye_14.x;
    cameraEye_8008D600.vy = cameraState_8008D4F0.eye_14.y;
    cameraEye_8008D600.vz = cameraState_8008D4F0.eye_14.z;
    dir.vx = cameraState_8008D4F0.lookAt_20.x - cameraState_8008D4F0.eye_14.x;
    dir.vy = cameraState_8008D4F0.lookAt_20.y - cameraState_8008D4F0.eye_14.y;
    dir.vz = cameraState_8008D4F0.lookAt_20.z - cameraState_8008D4F0.eye_14.z;
    yaw = ratan2_8003B548(dir.vx, dir.vz);
    cameraRot_8008D4C8.vy = -yaw;
    cameraRot_8008D4C8.vx = ratan2_8003B548(dir.vy, ISqrt_8003B918(LengthSquared2D_8003B8BC(dir.vx, dir.vz)));
    cameraRot_8008D4C8.vz = cameraState_8008D4F0.roll_2C;
    SetGteLightAndCamera_8004D0E8();
}
// pointLights_8008D534[0].color_C.vx/vy/vz through the PointLight type changes the scheduling, so the short view stays
// Matched
void SetAreaElementLight_80039ED8(int mode)
{
    switch ((short)(mode + 1))
    {
    case 0:
        ((short*)pointLights_8008D534)[6] = 0x800;
        ((short*)pointLights_8008D534)[7] = 0x800;
        ((short*)pointLights_8008D534)[8] = 0x800;
        break;
    case 1:
        ((short*)pointLights_8008D534)[6] = 0x1000;
        ((short*)pointLights_8008D534)[7] = 0;
        ((short*)pointLights_8008D534)[8] = 0x6B0;
        break;
    case 4:
        ((short*)pointLights_8008D534)[6] = 0x150;
        ((short*)pointLights_8008D534)[7] = 0;
        ((short*)pointLights_8008D534)[8] = 0x1000;
        break;
    case 3:
        ((short*)pointLights_8008D534)[6] = 0;
        ((short*)pointLights_8008D534)[7] = 0x1000;
        ((short*)pointLights_8008D534)[8] = 0x940;
        break;
    case 2:
        ((short*)pointLights_8008D534)[6] = 0xEB0;
        ((short*)pointLights_8008D534)[7] = 0x1000;
        ((short*)pointLights_8008D534)[8] = 0;
        break;
    }
}
