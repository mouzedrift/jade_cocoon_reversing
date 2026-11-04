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

extern Block104 cameraState_8008D4F0;
extern ShortPair screenOffset_8008D474;
typedef struct
{
    unsigned char idx;
    unsigned char b;
    unsigned char k;
    unsigned char pad;
    short field_4;
} struct_buf_80036528;
extern void UpdatePadVibration_800366A0(EventEntry* e, struct_buf_80036528* o);
// Matched
void StartPadVibration_80036528(int idx, int b)
{
    EventNode* n;
    int i;
    struct_buf_80036528* o;
    EventEntry* e;

    if ((saveData_8008B570.field_0 & 0x40) || (pads_800918E8[(unsigned char)idx][1] >> 4) != 7)
    {
        StopPadVibration_80036658((unsigned char)idx);
        return;
    }
    n = vibrationTasks_8008D4B8;
    for (i = 0; i < (unsigned char)idx; i++)
    {
        n = n->next;
    }
    e = &n->entry;
    o = e->buffer;
    e->cb_8 = (EventEntryFn)UpdatePadVibration_800366A0;
    o->b = b;
    o->idx = idx;
    o->k = 0;
    o->field_4 = vibrationPatterns_80083B30[o->b][0].field_0;
    padVibration_80095460[o->idx].motor_2[0] = vibrationPatterns_80083B30[o->b][o->k].field_2;
    padVibration_80095460[o->idx].motor_2[1] = vibrationPatterns_80083B30[o->b][o->k].field_3;
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
extern void StopPadVibrationTask_800367F0(int a0, unsigned char* a1);
// Matched
void UpdatePadVibration_800366A0(EventEntry* e, struct_buf_80036528* o)
{
    if (--o->field_4 <= 0)
    {
        o->k++;
        o->field_4 = vibrationPatterns_80083B30[o->b][o->k].field_0;
        padVibration_80095460[o->idx].motor_2[0] = vibrationPatterns_80083B30[o->b][o->k].field_2;
        padVibration_80095460[o->idx].motor_2[1] = vibrationPatterns_80083B30[o->b][o->k].field_3;
        if (o->field_4 < 0)
        {
            e->cb_8 = (EventEntryFn)StopPadVibrationTask_800367F0;
        }
    }
    if ((saveData_8008B570.field_0 & 0x40) || (pads_800918E8[o->idx][1] >> 4) != 7)
    {
        padVibration_80095460[o->idx].motor_2[0] = 0;
        padVibration_80095460[o->idx].motor_2[1] = 0;
    }
}
// Matched
void StopPadVibrationTask_800367F0(int a0, unsigned char* a1)
{
    padVibration_80095460[*a1].motor_2[0] = 0;
    padVibration_80095460[*a1].motor_2[1] = 0;
}

// Matched
void UpdatePadVibration_80036820(int port)
{
    int st = PadGetState(port << 4);
    if (st != 0)
    {
        if (st == 1)
        {
            padVibration_80095460[port].flags_0 &= 0xFFFE;
        }
        if (!(padVibration_80095460[port].flags_0 & 1))
        {
            PadSetAct(port << 4, (unsigned char*)&padVibration_80095460[port].motor_2[0], 2);
            if (st == 2 || (st == 6 && PadSetActAlign(port << 4, padActAlign_80083844)))
            {
                padVibration_80095460[port].flags_0 |= 1;
            }
        }
    }
}
extern void UpdateCameraFollow_80037918(CameraCtrl* p);
extern void SaveCameraState_80039620(CameraCtrl* o);
extern void SetupCameraOrbit_80038CA8(CameraCtrl* p);
extern void SetupBattleIntroCamera_80037F44(CameraCtrl* p);
extern void CameraOrbitTask_800374E0();
extern int FindMeshAtPos_800B8184(int a, int b);
extern void CameraBattleIntroTask_800369E0(EventEntry* p, CameraCtrl* q);

// Matched
void InitCameraTask_800368F8(EventEntry* p, CameraCtrl* q)
{
    if (q->flags_4 & 0x100)
    {
        SaveCameraState_80039620(q);
        q->pos_38.x = levantPos_8008BD18.pos.x;
        q->pos_38.y = levantPos_8008BD18.pos.y;
        q->pos_38.z = levantPos_8008BD18.pos.z;
        SetupCameraOrbit_80038CA8(q);
        q->mode_8 = 6;
        p->cb_8 = (EventEntryFn)CameraOrbitTask_800374E0;
    }
    else if (!(q->flags_4 & 0x2000))
    {
        int r = FindMeshAtPos_800B8184(q->target_0, saveData_8008B570.mapId_2E4[3].field_0);
        if (r >= 0)
        {
            saveData_8008B570.mapId_2E4[3].field_0 = r;
        }
    }
    else
    {
        SetupBattleIntroCamera_80037F44(q);
        q->mode_8 = 2;
        p->cb_8 = (EventEntryFn)CameraBattleIntroTask_800369E0;
        p->cb_8(p, q);
    }
    UpdateCameraFollow_80037918(q);
}
extern void PlaceBattleIntroCamera_80037C74(CameraCtrl* q);
extern void TrackCameraTarget_8003891C(CameraCtrl* p, struct_v3* v);
extern void DrawBattleStage_800BC90C(CameraCtrl* q);
extern void CameraBattleTask_80036AB4(EventEntry* p, CameraCtrl* q);
extern void StartSceneFadeIn_8001AA04(int a);

// Matched
void CameraBattleIntroTask_800369E0(EventEntry* p, CameraCtrl* q)
{
    switch (q->mode_8)
    {
    case 2:
        if (q->flags_4 & 4)
        {
            q->mode_8 += 1;
            PlaceBattleIntroCamera_80037C74(q);
            StartSceneFadeIn_8001AA04(8);
        }
        break;
    case 3:
        q->counter_14 = q->counter_14 + 1;
        if (q->counter_14 >= 0x3D)
        {
            MoveBattleCamera_800390F4(q, 1);
            q->mode_8 = 4;
            p->cb_8 = (EventEntryFn)CameraBattleTask_80036AB4;
        }
        TrackCameraTarget_8003891C(q, &levantPos_8008BD18.pos);
        DrawBattleStage_800BC90C(q);
        break;
    }
}
extern void UpdateCameraMove_80038230(CameraCtrl* p);
extern void InitCameraTask_800368F8(EventEntry* p, CameraCtrl* q);
void CameraSplineTask_80036BB0(EventEntry* p, CameraCtrl* q);

// Matched
void CameraBattleTask_80036AB4(EventEntry* p, CameraCtrl* q)
{
    CameraCtrl* r = q;
    if (q->flags_4 & 4)
    {
        UpdateCameraMove_80038230(q);
        if (q->t_C > 0)
        {
            q->t_C -= 0x100;
        }
        if (q->t_C < 0)
        {
            q->t_C = 0;
        }
        if (q->flags_4 & 4)
        {
            goto run;
        }
    }
    UpdateCameraFollow_80037918(r);
    TrackCameraTarget_8003891C(r, &levantPos_8008BD18.pos);
    r->flags_4 &= ~0x1000;
    r->mode_8 = 0;
    p->cb_8 = (EventEntryFn)InitCameraTask_800368F8;
    return;
run:
    DrawBattleStage_800BC90C(r);
    if (r->flags_4 & 8)
    {
        r->mode_8 = 5;
        r->keyIdx_1C4 = 0;
        p->cb_8 = (EventEntryFn)CameraSplineTask_80036BB0;
        r->t_C = 0;
    }
}
#define SPLINE(c) ((int)((c)[0] * t3 + (c)[1] * t2 + (c)[2] * t + (c)[3]))
// Matched
void CameraSplineTask_80036BB0(EventEntry* p, CameraCtrl* r)
{
    CameraCtrl* q = r;
    int i;
    int k;
    int n;
    float t;
    float t2;
    float t3;
    int ang;
    CamSpline* sp;
    VECTOR v;
    int ex;
    int ey;
    int ez;
    int x;
    int y;
    int z;

    if (!AdvanceSplineKey_800395D0(&q->keyIdx_1C4, ++q->t_C, &q->keys_1C8[0]) || !(q->flags_4 & 8))
    {
        MoveBattleCamera_800390F4(q, 1);
        q->mode_8 = 4;
        p->cb_8 = (EventEntryFn)CameraBattleTask_80036AB4;
    }
    else
    {
        i = q->keyIdx_1C4;
        k = q->keys_1C8[i];
        n = i + 1;
        t = (float)(q->t_C - k) / (float)(q->keys_1C8[n] - k);
        t2 = t * t;
        t3 = t2 * t;
        sp = q->spline_218;
        ang = SPLINE(sp[i].c[3]);
        v.vx = SPLINE(sp[i].c[0]);
        v.vy = SPLINE(sp[i].c[1]);
        v.vz = SPLINE(sp[i].c[2]);
        ex = SPLINE(sp[i].c[4]);
        ey = SPLINE(sp[i].c[5]);
        ez = SPLINE(sp[i].c[6]);
        x = v.vx + ex * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096 + ez * sinTable_80084540[ang & 0xFFF] / 4096;
        y = v.vy + ey;
        z = v.vz - ex * sinTable_80084540[ang & 0xFFF] / 4096 + ez * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096;
        cameraState_8008D4F0.eye_14.x = q->splinePos_1BC->vx + x * sinTable_80084540[(q->splineRot_1C0->vy + 0x400) & 0xFFF] / 4096 + z * sinTable_80084540[q->splineRot_1C0->vy & 0xFFF] / 4096;
        cameraState_8008D4F0.eye_14.y = q->splinePos_1BC->vy + y;
        cameraState_8008D4F0.eye_14.z = q->splinePos_1BC->vz - x * sinTable_80084540[q->splineRot_1C0->vy & 0xFFF] / 4096 + z * sinTable_80084540[(q->splineRot_1C0->vy + 0x400) & 0xFFF] / 4096;
        ex = SPLINE(sp[i].c[8]);
        ey = SPLINE(sp[i].c[9]);
        ez = SPLINE(sp[i].c[10]);
        x = v.vx + ex * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096 + ez * sinTable_80084540[ang & 0xFFF] / 4096;
        y = v.vy + ey;
        z = v.vz - ex * sinTable_80084540[ang & 0xFFF] / 4096 + ez * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096;
        cameraState_8008D4F0.lookAt_20.x = q->splinePos_1BC->vx + x * sinTable_80084540[(q->splineRot_1C0->vy + 0x400) & 0xFFF] / 4096 + z * sinTable_80084540[q->splineRot_1C0->vy & 0xFFF] / 4096;
        cameraState_8008D4F0.lookAt_20.y = q->splinePos_1BC->vy + y;
        cameraState_8008D4F0.lookAt_20.z = q->splinePos_1BC->vz - x * sinTable_80084540[q->splineRot_1C0->vy & 0xFFF] / 4096 + z * sinTable_80084540[(q->splineRot_1C0->vy + 0x400) & 0xFFF] / 4096;
        cameraState_8008D4F0.geomScreen_2E = SPLINE(sp[i].c[7]);
    }
    TrackCameraTarget_8003891C(q, &levantPos_8008BD18.pos);
    DrawBattleStage_800BC90C(q);
}
#undef SPLINE
extern int DistanceSquaredXZ_8003B860(int* a, int* b);
void ComputeCameraMoveAngles_80038D64(CameraCtrl* o, int* a);
extern void UpdateCameraMove_80038230(CameraCtrl* p);
extern void CameraOrbitReturnTask_800375F8(EventEntry* o, CameraCtrl* p);
// Matched
void CameraOrbitTask_800374E0(EventEntry* p, CameraCtrl* q)
{
    CameraCtrl* o = q;
    if (q->flags_4 & 0x100)
    {
        o->angDst_152 += 0x10;
        UpdateCameraMove_80038230(q);
        if (q->t_C > 0)
        {
            q->t_C -= 0x1000;
        }
        if (q->t_C < 0)
        {
            q->t_C = 0;
        }
    }
    else
    {
        q->t_C = 0x1000;
        o->lookSrc_1B0 = cameraState_8008D4F0.lookAt_20;
        o->lookDst_198 = o->saved_48.lookAt_20;
        o->eyeSrc_1A4 = o->saved_48.eye_14;
        o->eyeDst_18C = o->saved_48.eye_14;
        q->field2ESrc_17C = cameraState_8008D4F0.geomScreen_2E;
        q->field2EDst_180 = cameraState_8008D4F0.geomScreen_2E;
        ComputeCameraMoveAngles_80038D64(o, &levantPos_8008BD18.pos.x);
        p->cb_8 = (EventEntryFn)CameraOrbitReturnTask_800375F8;
    }
}
extern int cameraZoom_8008B4F8;
// Matched
void CameraOrbitReturnTask_800375F8(EventEntry* o, CameraCtrl* p)
{
    CameraCtrl* q = p;
    if (p->t_C > 0)
    {
        UpdateCameraMove_80038230(p);
        if (p->t_C > 0)
        {
            p->t_C -= 0x1000;
        }
        if (p->t_C < 0)
        {
            p->t_C = 0;
        }
    }
    else
    {
        RestoreCameraState_80039698(q);
        UpdateCameraFollow_80037918(q);
        TrackCameraTarget_8003891C(q, &levantPos_8008BD18.pos);
        q->mode_8 = 0;
        o->cb_8 = (EventEntryFn)InitCameraTask_800368F8;
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
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    UpdateCameraRotation_80039E14();
    cameraZoom_8008B4F8 = 0x1000;
    geomScreenDistance_8008B548 = (geomScreenBase_8008D51E << 12) / 0x1000;
    p->flags_4 = 0;
    p->mode_8 = 0;
    p->blend_24 = 0;
    p->blendStep_26 = 0x1000;
    p->target_0 = (int)&levantPos_8008BD18;
}
// Matched
void SetCameraBattleMode_80037720(void)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    p->flags_4 |= 0x2000;
}
// Matched
void StartBattleCamera_80037748(void)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    p->flags_4 |= 4;
}
// Matched
void EndBattleCamera_80037770(void)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    p->flags_4 &= ~4;
    p->flags_4 &= ~0x2000;
    RestoreCameraState_80039698(p);
}
extern void StartCameraSplineLong_8003970C(int a, int* b);
extern void StartCameraSplineShort_8003983C(int a, int* b);
// Matched
void StartBattleCameraSpline_800377B4(int a0, short a1)
{
    if (a0 == 0)
    {
        if (a1 == 5 || a1 == 0x1A)
        {
            StartCameraSplineLong_8003970C(a1, battleCamSpline0_80083D00);
        }
    }
    else if (a0 == 1)
    {
        if (a1 == 2)
        {
            StartCameraSplineShort_8003983C(2, battleCamSpline1_80084330);
        }
    }
}
// Table in the overlay area (outside the linked image), 8 bytes per entry
extern struct_pair8 levantBattleActions_800B1084[];
__asm__(".globl levantBattleActions_800B1084\n.equ levantBattleActions_800B1084,0x800b1084");
// Matched
void MoveBattleCameraForAction_80037828(int a, short b, int c)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    if (c)
    {
        MoveBattleCamera_800390F4(p, 2);
    }
    else if (a == 0)
    {
        if (levantBattleActions_800B1084[b].a != 0x10 && b != 0x11 && b != 0x12)
        {
            MoveBattleCamera_800390F4(p, 1);
        }
    }
    else if (a != 1 || (unsigned short)(b - 0x11) >= 2)
    {
        MoveBattleCamera_800390F4(p, 1);
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
extern void TrackCameraTargetBlend_80038A5C(CameraCtrl* p, int a, struct_v3* b, int c);
// Matched
void UpdateCameraFollow_80037918(CameraCtrl* p)
{
    if (p->flags_4 & 0x10)
    {
        TrackCameraTargetBlend_80038A5C(p, p->target_0, &p->blendTarget_28, p->blend_24);
        p->blend_24 += 0x1000 / p->blendStep_26;
        if (p->blend_24 > 0x1000)
        {
            p->blend_24 = 0x1000;
        }
    }
    else
    {
        TrackCameraTargetBlend_80038A5C(p, p->target_0, &p->blendTarget_28, p->blend_24);
        p->blend_24 -= 0x1000 / p->blendStep_26;
        if (p->blend_24 < 0)
        {
            p->blend_24 = 0;
        }
    }
}
// Matched
void SetCameraBlendTarget_800379DC(int* v, short n)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    p->blendTarget_28.x = v[0];
    p->blendTarget_28.y = v[1];
    p->blendTarget_28.z = v[2];
    p->flags_4 |= 0x10;
    p->blendStep_26 = n;
}
// Matched
void ClearCameraBlendTarget_80037A20(int a0, short n)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    p->blendStep_26 = n;
    p->flags_4 &= ~0x10;
}
// Matched
short GetCameraBlend_80037A4C(void)
{
    return ((CameraCtrl*)cameraTask_8008D4A0->entry.buffer)->blend_24;
}
// Matched
void SetCameraZoom_80037A6C(int a, int b)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    if (b >= 2)
    {
        p->zoomTarget_34 = a;
        p->zoomSteps_12 = b;
        p->zoomStart_A = *(unsigned short*)&cameraZoom_8008B4F8;
        p->flags_4 |= 0x20;
    }
    else
    {
        cameraZoom_8008B4F8 = a;
        UpdateCameraFollow_80037918(p);
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
extern void MoveCameraToFocusPreset_80038E2C(CameraCtrl* p, int a, int b);
extern void CameraBattleTask_80036AB4();
// Matched
void FocusBattleCamera_80037AE0(unsigned short mask)
{
    int sel = 0;
    int cnt = 0;
    int i;
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    int* r;
    int v;
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
    if (*(unsigned short*)&p->mode_8 == 4 || *(unsigned short*)&p->mode_8 == 5)
    {
        r = GetBattleSelection_800A1E3C();
        if (actingUnit_800C9C7C == 0)
        {
            v = 0;
        }
        else
        {
            v = GetSummonedMinionBonePos_800C0FAC()->field_7C + 0xF5;
        }
        MoveCameraToFocusPreset_80038E2C(p, battleCamFocusIndex_80083CE8[r[0] - 1][sel], v);
        *(unsigned short*)&p->mode_8 = 4;
        cameraTask_8008D4A0->entry.cb_8 = (EventEntryFn)CameraBattleTask_80036AB4;
    }
}
// Matched
void StartCameraShake_80037BFC(void)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    p->shake_10 = 0;
    p->flags_4 |= 0xC0;
}
// Matched
void StartCameraOrbit_80037C24(void)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    p->flags_4 |= 0x100;
}
// Matched
void StopCameraOrbit_80037C4C(void)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    p->flags_4 &= ~0x100;
}
// Matched
void PlaceBattleIntroCamera_80037C74(CameraCtrl* q)
{
    int sel;

    q->counter_14 = 0;
    q->t_C = 0;
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
    cameraState_8008D4F0.lookAt_20.x = q->pos_38.x + (sinTable_80084540[(q->rotY_44 + 0x400) & 0xFFF] * battleCamIntroPresets_80083BE4[sel].x1 / 4096 + sinTable_80084540[q->rotY_44 & 0xFFF] * battleCamIntroPresets_80083BE4[sel].z1 / 4096);
    cameraState_8008D4F0.lookAt_20.y = levantPos_8008BD18.pos.y + battleCamIntroPresets_80083BE4[sel].y1;
    cameraState_8008D4F0.lookAt_20.z = q->pos_38.z + (-sinTable_80084540[q->rotY_44 & 0xFFF] * battleCamIntroPresets_80083BE4[sel].x1 / 4096 + sinTable_80084540[(q->rotY_44 + 0x400) & 0xFFF] * battleCamIntroPresets_80083BE4[sel].z1 / 4096);
    cameraState_8008D4F0.eye_14.x = q->pos_38.x + (sinTable_80084540[(q->rotY_44 + 0x400) & 0xFFF] * battleCamIntroPresets_80083BE4[sel].x0 / 4096 + sinTable_80084540[q->rotY_44 & 0xFFF] * battleCamIntroPresets_80083BE4[sel].z0 / 4096);
    cameraState_8008D4F0.eye_14.y = levantPos_8008BD18.pos.y + battleCamIntroPresets_80083BE4[sel].y0;
    cameraState_8008D4F0.eye_14.z = q->pos_38.z + (-sinTable_80084540[q->rotY_44 & 0xFFF] * battleCamIntroPresets_80083BE4[sel].x0 / 4096 + sinTable_80084540[(q->rotY_44 + 0x400) & 0xFFF] * battleCamIntroPresets_80083BE4[sel].z0 / 4096);
    cameraState_8008D4F0.geomScreen_2E = battleCamIntroPresets_80083BE4[sel].field_8;
    setVector(&cameraState_8008D4F0.lightDir_34, q->rot_164.vx, q->rot_164.vy, q->rot_164.vz);
    setVector(&cameraState_8008D4F0.lightColor_3C, q->rot_174.vx, q->rot_174.vy, q->rot_174.vz);
    cameraState_8008D4F0.ent_44[0].color_C.vx = 0x800;
    cameraState_8008D4F0.ent_44[0].color_C.vy = 0x800;
    cameraState_8008D4F0.ent_44[0].color_C.vz = 0x800;
    cameraZoom_8008B4F8 = q->field_188;
}
// Matched
void SetupBattleIntroCamera_80037F44(CameraCtrl* q)
{
    int i;

    SaveCameraState_80039620(q);
    q->field2ESrc_17C = cameraState_8008D4F0.geomScreen_2E;
    q->field2EDst_180 = 0xA0;
    q->lookSrc_1B0 = cameraState_8008D4F0.lookAt_20;
    q->lookDst_198.x = saveData_8008B570.levant_7A8.pos.x;
    q->lookDst_198.y = saveData_8008B570.levant_7A8.pos.y - 0xFA;
    q->lookDst_198.z = saveData_8008B570.levant_7A8.pos.z;
    q->eyeSrc_1A4 = cameraState_8008D4F0.eye_14;
    q->eyeDst_18C.x = saveData_8008B570.levant_7A8.pos.x + sinTable_80084540[saveData_8008B570.levant_7A8.rot.vy & 0xFFF] * 200 / 4096;
    q->eyeDst_18C.y = saveData_8008B570.levant_7A8.pos.y - 0xFA;
    q->eyeDst_18C.z = saveData_8008B570.levant_7A8.pos.z + sinTable_80084540[(saveData_8008B570.levant_7A8.rot.vy + 0x400) & 0xFFF] * 200 / 4096;
    q->pos_38.x = saveData_8008B570.levant_7A8.pos.x + sinTable_80084540[saveData_8008B570.levant_7A8.rot.vy & 0xFFF] * 500 / 4096;
    q->pos_38.y = saveData_8008B570.levant_7A8.pos.y + 0xFA;
    q->pos_38.z = saveData_8008B570.levant_7A8.pos.z + sinTable_80084540[(saveData_8008B570.levant_7A8.rot.vy + 0x400) & 0xFFF] * 500 / 4096;
    q->rotY_44 = saveData_8008B570.levant_7A8.rot.vy;
    for (i = 7; i >= 0; i--)
    {
        cameraState_8008D4F0.ent_44[i].range_14 = 0;
    }
    cameraState_8008D4F0.ent_44[0].pos_0 = q->pos_38;
    setVector(&cameraState_8008D4F0.ent_44[0].color_C, 0, 0, 0);
    cameraState_8008D4F0.ent_44[0].range_14 = 0xEA6;
    cameraState_8008D4F0.ent_44[0].pos_0.y -= 1000;
    q->rot_15C = cameraState_8008D4F0.lightDir_34;
    q->rot_164.vx = 0x7FC;
    q->rot_164.vy = -0xAA6;
    q->rot_164.vz = 0x8DE;
    q->rot_16C = cameraState_8008D4F0.lightColor_3C;
    q->rot_174.vx = 0x1000;
    q->rot_174.vy = 0x1000;
    q->rot_174.vz = 0x1000;
    q->savedZoom_184 = cameraZoom_8008B4F8;
    q->field_188 = 0x1000;
    ComputeCameraMoveAngles_80038D64(q, &levantPos_8008BD18.pos.x);
    q->t_C = 0x1000;
}
#define EASE(p) (0x1000 - sinTable_80084540[(((p)->t_C / 4) + 0x400) & 0xFFF])
// Matched
void UpdateCameraMove_80038230(CameraCtrl* p)
{
    short ang;
    short r;

    cameraState_8008D4F0.lookAt_20.x = p->lookDst_198.x + (p->lookSrc_1B0.x - p->lookDst_198.x) * EASE(p) / 4096;
    cameraState_8008D4F0.lookAt_20.y = p->lookDst_198.y + (p->lookSrc_1B0.y - p->lookDst_198.y) * EASE(p) / 4096;
    cameraState_8008D4F0.lookAt_20.z = p->lookDst_198.z + (p->lookSrc_1B0.z - p->lookDst_198.z) * EASE(p) / 4096;

    ang = *(unsigned short*)&p->angDst_152 + (p->angSrc_150 - p->angDst_152) * EASE(p) / 4096;
    r = *(unsigned short*)&p->distDst_158 + (p->distSrc_154 - p->distDst_158) * EASE(p) / 4096;
    cameraState_8008D4F0.eye_14.x = p->pos_38.x + r * sinTable_80084540[ang & 0xFFF] / 4096;
    cameraState_8008D4F0.eye_14.y = p->eyeDst_18C.y + (p->eyeSrc_1A4.y - p->eyeDst_18C.y) * EASE(p) / 4096;
    cameraState_8008D4F0.eye_14.z = p->pos_38.z + r * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096;
    cameraState_8008D4F0.geomScreen_2E = *(unsigned short*)&p->field2EDst_180 + (p->field2ESrc_17C - p->field2EDst_180) * EASE(p) / 4096;
    if (p->t_C == 0)
    {
        cameraState_8008D4F0.eye_14 = p->eyeDst_18C;
    }
    TrackCameraTarget_8003891C(p, &levantPos_8008BD18.pos);
}
extern double pow(double, double);
// Matched
void UpdateCameraZoom_8003856C(CameraCtrl* p)
{
    unsigned int u;
    float f;

    prevCameraZoom_8008D4BC = cameraZoom_8008B4F8;
    if (GetCameraMode_800378F8() != 0)
    {
        return;
    }
    u = p->zoomTarget_34;
    if (u < (unsigned int)cameraZoom_8008B4F8 && (p->flags_4 & 0x20))
    {

        f = (float)cameraZoom_8008B4F8 * pow((float)u / (float)p->zoomStart_A, 1.0f / (float)p->zoomSteps_12);
        cameraZoom_8008B4F8 = f;
        if ((unsigned int)p->zoomTarget_34 >= (unsigned int)cameraZoom_8008B4F8)
        {
            p->flags_4 &= ~0x20;
        }
    }
    else if ((unsigned int)cameraZoom_8008B4F8 < u && (p->flags_4 & 0x20))
    {

        f = (float)cameraZoom_8008B4F8 * pow((float)u / (float)p->zoomStart_A, 1.0f / (float)p->zoomSteps_12);
        cameraZoom_8008B4F8 = f;
        if ((unsigned int)cameraZoom_8008B4F8 >= (unsigned int)p->zoomTarget_34)
        {
            p->flags_4 &= ~0x20;
        }
    }
    if (cameraZoom_8008B4F8 < 0x1000)
    {
        cameraZoom_8008B4F8 = 0x1000;
        p->flags_4 &= ~0x20;
    }
    if (cameraZoom_8008B4F8 > 0x10000)
    {
        cameraZoom_8008B4F8 = 0x10000;
        p->flags_4 &= ~0x20;
    }
    if (zoomLimit_8008D66C * 4 < geomScreenBase_8008D51E * cameraZoom_8008B4F8 / 4096)
    {
        cameraZoom_8008B4F8 = (zoomLimit_8008D66C << 14) / geomScreenBase_8008D51E;
        if (cameraZoom_8008B4F8 < 0x1000)
        {
            cameraZoom_8008B4F8 = 0x1000;
        }
        p->flags_4 &= ~0x20;
    }
}
extern void UpdateCameraZoom_8003856C(CameraCtrl* p);
extern void UpdateScreenScroll_800398B4(CameraCtrl* p, void* q);
extern int prevCameraZoom_8008D4BC;
typedef struct
{
    DVECTOR xy;
    int z;
} ScreenPosZ;
extern ScreenPosZ cameraTargetScreenPos_8008D668;
// Matched
void TrackCameraTarget_8003891C(CameraCtrl* p, struct_v3* v)
{
    SVECTOR sv;
    long pr;
    long flag;
    int a;
    unsigned int b;
    UpdateCameraRotation_80039E14();
    UpdateCameraZoom_8003856C(p);
    a = geomScreenBase_8008D51E * cameraZoom_8008B4F8;
    b = geomScreenBase_8008D51E * prevCameraZoom_8008D4BC;
    sv.vx = v->x;
    sv.vy = v->y;
    sv.vz = v->z;
    sv.vy -= 0x15E;
    sv.vx -= cameraEye_8008D600.vx;
    sv.vy -= cameraEye_8008D600.vy;
    sv.vz -= cameraEye_8008D600.vz;
    geomScreenDistance_8008B548 = b >> 12;
    SetGeomScreen(a / 4096);
    cameraTargetScreenPos_8008D668.z = RotTransPers(&sv, (long*)&cameraTargetScreenPos_8008D668.xy, &pr, &flag);
    if (flag < 0)
    {
        cameraTargetScreenPos_8008D668.xy.vx = 0xA0;
        cameraTargetScreenPos_8008D668.xy.vy = 0x78;
    }
    SetGeomScreen(geomScreenDistance_8008B548);
    if (!(p->flags_4 & 0x800))
    {
        UpdateScreenScroll_800398B4(p, &cameraTargetScreenPos_8008D668);
    }
}
// Matched
void TrackCameraTargetBlend_80038A5C(CameraCtrl* p, int a, struct_v3* b, int t)
{
    struct_v3* v = (struct_v3*)a;
    SVECTOR sv;
    SVECTOR sv2;
    ScreenPosZ tmp;
    long pr;
    long flag;
    int s;
    unsigned int g;

    UpdateCameraRotation_80039E14();
    UpdateCameraZoom_8003856C(p);
    g = geomScreenBase_8008D51E * prevCameraZoom_8008D4BC;
    s = geomScreenBase_8008D51E * cameraZoom_8008B4F8;
    geomScreenDistance_8008B548 = g >> 12;
    SetGeomScreen(s / 4096);
    sv.vx = v->x;
    sv.vy = v->y;
    sv.vz = v->z;
    sv.vy -= 0x15E;
    sv.vx -= cameraEye_8008D600.vx;
    sv.vy -= cameraEye_8008D600.vy;
    sv.vz -= cameraEye_8008D600.vz;
    cameraTargetScreenPos_8008D668.z = RotTransPers(&sv, (long*)&cameraTargetScreenPos_8008D668.xy, &pr, &flag);
    sv2.vx = b->x;
    sv2.vy = b->y;
    sv2.vz = b->z;
    sv2.vy -= 0x15E;
    sv2.vx -= cameraEye_8008D600.vx;
    sv2.vy -= cameraEye_8008D600.vy;
    sv2.vz -= cameraEye_8008D600.vz;
    tmp.z = RotTransPers(&sv2, (long*)&tmp.xy, &pr, &flag);
    cameraTargetScreenPos_8008D668.xy.vx += (tmp.xy.vx - cameraTargetScreenPos_8008D668.xy.vx) * t / 4096;
    cameraTargetScreenPos_8008D668.xy.vy += (tmp.xy.vy - cameraTargetScreenPos_8008D668.xy.vy) * t / 4096;
    cameraTargetScreenPos_8008D668.z += (tmp.z - cameraTargetScreenPos_8008D668.z) * t / 4096;
    SetGeomScreen(geomScreenDistance_8008B548);
    if (!(p->flags_4 & 0x800))
    {
        UpdateScreenScroll_800398B4(p, &cameraTargetScreenPos_8008D668);
    }
}
// Matched
void SetupCameraOrbit_80038CA8(CameraCtrl* p)
{
    CameraCtrl* o = p;
    p->t_C = 0x1000;
    p->flags_4 &= ~8;
    o->lookSrc_1B0 = cameraState_8008D4F0.lookAt_20;
    o->lookDst_198 = saveData_8008B570.levant_7A8.pos;
    o->eyeSrc_1A4 = cameraState_8008D4F0.eye_14;
    o->eyeDst_18C = cameraState_8008D4F0.eye_14;
    p->field2ESrc_17C = cameraState_8008D4F0.geomScreen_2E;
    p->field2EDst_180 = cameraState_8008D4F0.geomScreen_2E;
    ComputeCameraMoveAngles_80038D64(o, &saveData_8008B570.levant_7A8.pos.x);
}
extern int DistanceSquaredXZ_8003B860(int* a, int* b);

// Matched
void ComputeCameraMoveAngles_80038D64(CameraCtrl* p, int* a1)
{
    int d;
    p->angSrc_150 = ratan2Difference_8003B9E0(a1, cameraEye_8008D504) & 0xFFF;
    p->distSrc_154 = ISqrt_8003B918(DistanceSquaredXZ_8003B860(a1, cameraEye_8008D504));
    p->angDst_152 = ratan2Difference_8003B9E0(a1, (int*)&p->eyeDst_18C) & 0xFFF;
    p->distDst_158 = ISqrt_8003B918(DistanceSquaredXZ_8003B860(a1, (int*)&p->eyeDst_18C));
    d = p->angDst_152 - p->angSrc_150;
    if (d > 0x800)
    {
        p->angDst_152 = *(unsigned short*)&p->angDst_152 - 0x1000;
    }
    else if (d < -0x800)
    {
        p->angDst_152 = *(unsigned short*)&p->angDst_152 + 0x1000;
    }
}
// Matched
void MoveCameraToFocusPreset_80038E2C(CameraCtrl* p, int a, int b)
{
    CameraCtrl* o = p;

    p->t_C = 0x1000;
    p->flags_4 &= ~8;
    o->lookSrc_1B0 = cameraState_8008D4F0.lookAt_20;
    o->lookDst_198 = o->pos_38;
    o->lookDst_198.y = saveData_8008B570.levant_7A8.pos.y + battleCamFocusPresets_80083C70[(unsigned short)a].y1;
    o->lookDst_198.z += -sinTable_80084540[p->rotY_44 & 0xFFF] * battleCamFocusPresets_80083C70[(unsigned short)a].x1 / 4096 + sinTable_80084540[(p->rotY_44 + 0x400) & 0xFFF] * battleCamFocusPresets_80083C70[(unsigned short)a].z1 / 4096;
    o->lookDst_198.x += sinTable_80084540[(p->rotY_44 + 0x400) & 0xFFF] * battleCamFocusPresets_80083C70[(unsigned short)a].x1 / 4096 + sinTable_80084540[p->rotY_44 & 0xFFF] * battleCamFocusPresets_80083C70[(unsigned short)a].z1 / 4096;
    o->eyeSrc_1A4 = cameraState_8008D4F0.eye_14;
    o->eyeDst_18C = o->pos_38;
    o->eyeDst_18C.y = saveData_8008B570.levant_7A8.pos.y + battleCamFocusPresets_80083C70[(unsigned short)a].y0 + b;
    o->eyeDst_18C.z += -sinTable_80084540[p->rotY_44 & 0xFFF] * battleCamFocusPresets_80083C70[(unsigned short)a].x0 / 4096 + sinTable_80084540[(p->rotY_44 + 0x400) & 0xFFF] * battleCamFocusPresets_80083C70[(unsigned short)a].z0 / 4096;
    o->eyeDst_18C.x += sinTable_80084540[(p->rotY_44 + 0x400) & 0xFFF] * battleCamFocusPresets_80083C70[(unsigned short)a].x0 / 4096 + sinTable_80084540[p->rotY_44 & 0xFFF] * battleCamFocusPresets_80083C70[(unsigned short)a].z0 / 4096;
    p->field2ESrc_17C = cameraState_8008D4F0.geomScreen_2E;
    p->field2EDst_180 = battleCamFocusPresets_80083C70[(unsigned short)a].field_8;
    ComputeCameraMoveAngles_80038D64(o, (int*)&p->pos_38);
}
extern int actorSide_800A85B8;
extern int DistanceSquared3D_8003B80C(int* a, int* b);
// Matched
void MoveBattleCamera_800390F4(CameraCtrl* p_, int arg1)
{
    int sel = 0;
    unsigned int i;
    unsigned int best;
    unsigned int dist;
    struct_v3 v;

    p_->t_C = 0x1000;
    p_->flags_4 &= ~8;
    if (arg1 == 0)
    {
        sel = rand() & 3;
    }
    else if (arg1 == 2)
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
                    v = p_->pos_38;
            v.y = saveData_8008B570.levant_7A8.pos.y + battleCamPresets_80083C0C[sel].y1;
            v.z += -sinTable_80084540[p_->rotY_44 & 0xFFF] * battleCamPresets_80083C0C[sel].x1 / 4096 + sinTable_80084540[(p_->rotY_44 + 0x400) & 0xFFF] * battleCamPresets_80083C0C[sel].z1 / 4096;
            v.x += sinTable_80084540[(p_->rotY_44 + 0x400) & 0xFFF] * battleCamPresets_80083C0C[sel].x1 / 4096 + sinTable_80084540[p_->rotY_44 & 0xFFF] * battleCamPresets_80083C0C[sel].z1 / 4096;
            dist = DistanceSquared3D_8003B80C((int*)&cameraState_8008D4F0.eye_14, (int*)&v);
            if (dist < best)
            {
                best = dist;
                sel = i;
            }
        }
    }
    p_->lookSrc_1B0 = cameraState_8008D4F0.lookAt_20;
    p_->lookDst_198 = p_->pos_38;
    p_->lookDst_198.y = saveData_8008B570.levant_7A8.pos.y + battleCamPresets_80083C0C[sel].y1;
    p_->lookDst_198.z += -sinTable_80084540[p_->rotY_44 & 0xFFF] * battleCamPresets_80083C0C[sel].x1 / 4096 + sinTable_80084540[(p_->rotY_44 + 0x400) & 0xFFF] * battleCamPresets_80083C0C[sel].z1 / 4096;
    p_->lookDst_198.x += sinTable_80084540[(p_->rotY_44 + 0x400) & 0xFFF] * battleCamPresets_80083C0C[sel].x1 / 4096 + sinTable_80084540[p_->rotY_44 & 0xFFF] * battleCamPresets_80083C0C[sel].z1 / 4096;
    p_->eyeSrc_1A4 = cameraState_8008D4F0.eye_14;
    p_->eyeDst_18C = p_->pos_38;
    p_->eyeDst_18C.y = saveData_8008B570.levant_7A8.pos.y + battleCamPresets_80083C0C[sel].y0;
    p_->eyeDst_18C.z += -sinTable_80084540[p_->rotY_44 & 0xFFF] * battleCamPresets_80083C0C[sel].x0 / 4096 + sinTable_80084540[(p_->rotY_44 + 0x400) & 0xFFF] * battleCamPresets_80083C0C[sel].z0 / 4096;
    p_->eyeDst_18C.x += sinTable_80084540[(p_->rotY_44 + 0x400) & 0xFFF] * battleCamPresets_80083C0C[sel].x0 / 4096 + sinTable_80084540[p_->rotY_44 & 0xFFF] * battleCamPresets_80083C0C[sel].z0 / 4096;
    p_->field2ESrc_17C = cameraState_8008D4F0.geomScreen_2E;
    p_->field2EDst_180 = battleCamPresets_80083C0C[sel].field_8;
    ComputeCameraMoveAngles_80038D64(p_, (int*)&p_->pos_38);
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
void SaveCameraState_80039620(CameraCtrl* o)
{
    o->saved_48 = cameraState_8008D4F0;
    o->savedZoom_184 = cameraZoom_8008B4F8;
    o->savedShake_14C = screenOffset_8008D474;
}
// Matched
void RestoreCameraState_80039698(CameraCtrl* o)
{
    cameraState_8008D4F0 = o->saved_48;
    cameraZoom_8008B4F8 = o->savedZoom_184;
    screenOffset_8008D474 = o->savedShake_14C;
}
extern int GetLevantActionEndFrame_800AB4D8(int a);
// Matched
void StartCameraSplineLong_8003970C(int idx_, int* a5)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    struct_pair8* t = levantBattleActions_800B1084;
    int* q;
    int r;
    p->field_1C = t[(short)idx_].b;
    p->spline_218 = (CamSpline*)a5;
    p->flags_4 |= 8;
    r = (short)GetLevantActionEndFrame_800AB4D8(0xE);
    if (((settingsFlags_8008B58C.word & 0x200000) >> 21) == 1)
    {
        q = p->keys_1C8;
        p->keys_1C8[0] = 0;
        q[1] = r + 0x32;
        q[2] = r + 0x46;
        q[3] = r + 0x5A;
        q[4] = r + 0x6E;
        q[5] = r + 0x97;
        q[6] = r + 0xC8;
        q[7] = r + 0x10E;
        q[8] = r + 0x169;
        q[9] = r + 0x258;
        q[10] = -1;
    }
    else
    {
        q = p->keys_1C8;
        p->keys_1C8[0] = 0;
        q[1] = r + 0x32;
        q[2] = r + 0x46;
        q[3] = r + 0x5A;
        q[4] = r + 0x6E;
        q[5] = r + 0x97;
        q[6] = r + 0xC8;
        q[7] = r + 0x10E;
        q[8] = -1;
    }
    p->splinePos_1BC = (VECTOR*)&levantPos_8008BD18.pos;
    p->splineRot_1C0 = &levantPos_8008BD18.rot;
}
// Matched
void StartCameraSplineShort_8003983C(int idx_, int* a5)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    struct_pair8* t = levantBattleActions_800B1084;
    int* q;
    p->field_1C = t[(short)idx_].b;
    q = p->keys_1C8;
    p->spline_218 = (CamSpline*)a5;
    p->keys_1C8[0] = 0;
    p->flags_4 |= 8;
    q[1] = 0x28;
    q[2] = 0x50;
    q[3] = 0x78;
    q[4] = -1;
    p->splinePos_1BC = (VECTOR*)&levantPos_8008BD18.pos;
    p->splineRot_1C0 = &levantPos_8008BD18.rot;
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
void UpdateScreenScroll_800398B4(CameraCtrl* p, void* q_)
{
    ScreenPosZ* q = q_;
    DR_AREA tw;
    RECT r;
    short* sp;
    int s;
    int lx;
    int ly;

    if (!(p->flags_4 & 4))
    {
        screenOffset_8008D474.a = screenOffset_8008D474.a - (q->xy.vx - (viewport_8008D420.x + viewport_8008D420.w / 2));
        screenOffset_8008D474.b = screenOffset_8008D474.b - (q->xy.vy - (viewport_8008D420.y + viewport_8008D420.h / 2));
        sp = tileSets_8008D654;
        s = cameraZoom_8008B4F8 << 5;
        lx = sp[4] * s / 4096 - viewport_8008D420.w;
        ly = sp[5] * s / 4096 - viewport_8008D420.h;
        screenOffset_8008D474.a = CLAMP_HALF(screenOffset_8008D474.a, lx);
        screenOffset_8008D474.b = CLAMP_HALF(screenOffset_8008D474.b, ly);
        screenOffset_8008D474.a = screenOffset_8008D474.a - (display_8008B4D8.w_C / 2 - (viewport_8008D420.x + viewport_8008D420.w / 2));
        screenOffset_8008D474.b = screenOffset_8008D474.b - (display_8008B4D8.h_E / 2 - (viewport_8008D420.y + viewport_8008D420.h / 2));
        r.x = drawEnv_8008D698[bDoubleBuffer_8008D428].clip.x + viewport_8008D420.x;
        r.y = drawEnv_8008D698[bDoubleBuffer_8008D428].clip.y + viewport_8008D420.y;
        r.w = viewport_8008D420.w;
        r.h = viewport_8008D420.h;
        SetDrawArea(&tw, &r);
        *(DR_AREA*)primAllocPtr_800960A8[bDoubleBuffer_8008D428] = tw;
        addPrim(pOT_8008D3EC, primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
        primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 0xC;
        r.x = drawEnv_8008D698[bDoubleBuffer_8008D428].clip.x;
        r.y = drawEnv_8008D698[bDoubleBuffer_8008D428].clip.y;
        r.w = drawEnv_8008D698[bDoubleBuffer_8008D428].clip.w;
        r.h = drawEnv_8008D698[bDoubleBuffer_8008D428].clip.h;
        SetDrawArea(&tw, &r);
        *(DR_AREA*)primAllocPtr_800960A8[bDoubleBuffer_8008D428] = tw;
        addPrim(pOT_8008D5F4 + 2, primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
        primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 0xC;
        if (p->flags_4 & 0x40)
        {
            if (p->flags_4 & 0x80)
            {
                screenOffset_8008D474.b += cameraShakeOffsets_80083BD4[p->shake_10];
            }
            else
            {
                screenOffset_8008D474.a += cameraShakeOffsets_80083BD4[p->shake_10];
            }
            if ((unsigned short)++p->shake_10 >= 15)
            {
                p->flags_4 &= ~0x40;
            }
        }
    }
    else if (p->flags_4 & 0x40)
    {
        if (p->flags_4 & 0x80)
        {
            screenOffset_8008D474.b = cameraShakeOffsets_80083BD4[p->shake_10];
        }
        else
        {
            screenOffset_8008D474.a = cameraShakeOffsets_80083BD4[p->shake_10];
        }
        if ((unsigned short)++p->shake_10 >= 15)
        {
            screenOffset_8008D474.a = 0;
            screenOffset_8008D474.b = 0;
            p->flags_4 &= ~0x40;
        }
    }
}
extern SVECTOR cameraRot_8008D4C8;
extern void SetGteLightAndCamera_8004D0E8(void);
// Matched
void UpdateCameraRotation_80039E14(void)
{
    VECTOR d;
    int a;
    cameraEye_8008D600.vx = cameraState_8008D4F0.eye_14.x;
    cameraEye_8008D600.vy = cameraState_8008D4F0.eye_14.y;
    cameraEye_8008D600.vz = cameraState_8008D4F0.eye_14.z;
    d.vx = cameraState_8008D4F0.lookAt_20.x - cameraState_8008D4F0.eye_14.x;
    d.vy = cameraState_8008D4F0.lookAt_20.y - cameraState_8008D4F0.eye_14.y;
    d.vz = cameraState_8008D4F0.lookAt_20.z - cameraState_8008D4F0.eye_14.z;
    a = ratan2_8003B548(d.vx, d.vz);
    cameraRot_8008D4C8.vy = -a;
    cameraRot_8008D4C8.vx = ratan2_8003B548(d.vy, ISqrt_8003B918(LengthSquared2D_8003B8BC(d.vx, d.vz)));
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
