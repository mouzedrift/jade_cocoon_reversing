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

#include "tu_80036528.h"
#include "tu_80014954.h"
#include "main.h"

extern Block104 cameraState_8008D4F0;
extern ShortPair dword_8008D474;
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
            if (st == 2 || (st == 6 && PadSetActAlign(port << 4, dword_80083844)))
            {
                padVibration_80095460[port].flags_0 |= 1;
            }
        }
    }
}
extern void sub_80037918(CameraCtrl* p);
extern void SaveCameraState_80039620(CameraCtrl* o);
extern void sub_80038CA8(CameraCtrl* p);
extern void sub_80037F44(CameraCtrl* p);
extern void sub_800374E0();
extern int sub_800B8184(int a, int b);
extern void sub_800369E0(EventEntry* p, CameraCtrl* q);

// Matched
void InitCameraTask_800368F8(EventEntry* p, CameraCtrl* q)
{
    if (q->flags_4 & 0x100)
    {
        SaveCameraState_80039620(q);
        q->pos_38.x = levantPos_8008BD18.pos.x;
        q->pos_38.y = levantPos_8008BD18.pos.y;
        q->pos_38.z = levantPos_8008BD18.pos.z;
        sub_80038CA8(q);
        q->mode_8 = 6;
        p->cb_8 = (EventEntryFn)sub_800374E0;
    }
    else if (!(q->flags_4 & 0x2000))
    {
        int r = sub_800B8184(q->target_0, saveData_8008B570.mapId_2E4[3].field_0);
        if (r >= 0)
        {
            saveData_8008B570.mapId_2E4[3].field_0 = r;
        }
    }
    else
    {
        sub_80037F44(q);
        q->mode_8 = 2;
        p->cb_8 = (EventEntryFn)sub_800369E0;
        p->cb_8(p, q);
    }
    sub_80037918(q);
}
extern void sub_80037C74(CameraCtrl* q);
extern void sub_8003891C(CameraCtrl* p, struct_v3* v);
extern void sub_800BC90C(CameraCtrl* q);
extern void sub_80036AB4(EventEntry* p, CameraCtrl* q);
extern void sub_8001AA04(int a);

// Matched
void sub_800369E0(EventEntry* p, CameraCtrl* q)
{
    switch (q->mode_8)
    {
    case 2:
        if (q->flags_4 & 4)
        {
            q->mode_8 += 1;
            sub_80037C74(q);
            sub_8001AA04(8);
        }
        break;
    case 3:
        q->counter_14 = q->counter_14 + 1;
        if (q->counter_14 >= 0x3D)
        {
            sub_800390F4(q, 1);
            q->mode_8 = 4;
            p->cb_8 = (EventEntryFn)sub_80036AB4;
        }
        sub_8003891C(q, &levantPos_8008BD18.pos);
        sub_800BC90C(q);
        break;
    }
}
extern void sub_80038230(CameraCtrl* p);
extern void InitCameraTask_800368F8(EventEntry* p, CameraCtrl* q);
void sub_80036BB0(EventEntry* p, CameraCtrl* q);

// Matched
void sub_80036AB4(EventEntry* p, CameraCtrl* q)
{
    CameraCtrl* r = q;
    if (q->flags_4 & 4)
    {
        sub_80038230(q);
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
    sub_80037918(r);
    sub_8003891C(r, &levantPos_8008BD18.pos);
    r->flags_4 &= ~0x1000;
    r->mode_8 = 0;
    p->cb_8 = (EventEntryFn)InitCameraTask_800368F8;
    return;
run:
    sub_800BC90C(r);
    if (r->flags_4 & 8)
    {
        r->mode_8 = 5;
        r->keyIdx_1C4 = 0;
        p->cb_8 = (EventEntryFn)sub_80036BB0;
        r->t_C = 0;
    }
}
#define SPLINE(c) ((int)((c)[0] * t3 + (c)[1] * t2 + (c)[2] * t + (c)[3]))
// Matched
void sub_80036BB0(EventEntry* p, CameraCtrl* r)
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

    if (!sub_800395D0(&q->keyIdx_1C4, ++q->t_C, &q->keys_1C8[0]) || !(q->flags_4 & 8))
    {
        sub_800390F4(q, 1);
        q->mode_8 = 4;
        p->cb_8 = (EventEntryFn)sub_80036AB4;
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
        x = v.vx + ex * word_80084540[(ang + 0x400) & 0xFFF] / 4096 + ez * word_80084540[ang & 0xFFF] / 4096;
        y = v.vy + ey;
        z = v.vz - ex * word_80084540[ang & 0xFFF] / 4096 + ez * word_80084540[(ang + 0x400) & 0xFFF] / 4096;
        cameraState_8008D4F0.field_14.x = q->splinePos_1BC->vx + x * word_80084540[(q->splineRot_1C0->vy + 0x400) & 0xFFF] / 4096 + z * word_80084540[q->splineRot_1C0->vy & 0xFFF] / 4096;
        cameraState_8008D4F0.field_14.y = q->splinePos_1BC->vy + y;
        cameraState_8008D4F0.field_14.z = q->splinePos_1BC->vz - x * word_80084540[q->splineRot_1C0->vy & 0xFFF] / 4096 + z * word_80084540[(q->splineRot_1C0->vy + 0x400) & 0xFFF] / 4096;
        ex = SPLINE(sp[i].c[8]);
        ey = SPLINE(sp[i].c[9]);
        ez = SPLINE(sp[i].c[10]);
        x = v.vx + ex * word_80084540[(ang + 0x400) & 0xFFF] / 4096 + ez * word_80084540[ang & 0xFFF] / 4096;
        y = v.vy + ey;
        z = v.vz - ex * word_80084540[ang & 0xFFF] / 4096 + ez * word_80084540[(ang + 0x400) & 0xFFF] / 4096;
        cameraState_8008D4F0.field_20.x = q->splinePos_1BC->vx + x * word_80084540[(q->splineRot_1C0->vy + 0x400) & 0xFFF] / 4096 + z * word_80084540[q->splineRot_1C0->vy & 0xFFF] / 4096;
        cameraState_8008D4F0.field_20.y = q->splinePos_1BC->vy + y;
        cameraState_8008D4F0.field_20.z = q->splinePos_1BC->vz - x * word_80084540[q->splineRot_1C0->vy & 0xFFF] / 4096 + z * word_80084540[(q->splineRot_1C0->vy + 0x400) & 0xFFF] / 4096;
        cameraState_8008D4F0.field_2E = SPLINE(sp[i].c[7]);
    }
    sub_8003891C(q, &levantPos_8008BD18.pos);
    sub_800BC90C(q);
}
#undef SPLINE
extern int DistanceSquaredXZ_8003B860(int* a, int* b);
void sub_80038D64(CameraCtrl* o, int* a);
extern void sub_80038230(CameraCtrl* p);
extern void sub_800375F8(EventEntry* o, CameraCtrl* p);
// Matched
void sub_800374E0(EventEntry* p, CameraCtrl* q)
{
    CameraCtrl* o = q;
    if (q->flags_4 & 0x100)
    {
        o->angDst_152 += 0x10;
        sub_80038230(q);
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
        o->lookSrc_1B0 = cameraState_8008D4F0.field_20;
        o->lookDst_198 = o->saved_48.field_20;
        o->eyeSrc_1A4 = o->saved_48.field_14;
        o->eyeDst_18C = o->saved_48.field_14;
        q->field2ESrc_17C = cameraState_8008D4F0.field_2E;
        q->field2EDst_180 = cameraState_8008D4F0.field_2E;
        sub_80038D64(o, &levantPos_8008BD18.pos.x);
        p->cb_8 = (EventEntryFn)sub_800375F8;
    }
}
extern int dword_8008B4F8;
// Matched
void sub_800375F8(EventEntry* o, CameraCtrl* p)
{
    CameraCtrl* q = p;
    if (p->t_C > 0)
    {
        sub_80038230(p);
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
        sub_80037918(q);
        sub_8003891C(q, &levantPos_8008BD18.pos);
        q->mode_8 = 0;
        o->cb_8 = (EventEntryFn)InitCameraTask_800368F8;
    }
}
// Matched
void nullsub_5(void)
{
}
extern void sub_80039E14(void);
extern int geomScreenDistance_8008B548;
// Matched
void ResetCameraToLevant_800376A8(void)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    sub_80039E14();
    dword_8008B4F8 = 0x1000;
    geomScreenDistance_8008B548 = (word_8008D51E << 12) / 0x1000;
    p->flags_4 = 0;
    p->mode_8 = 0;
    p->blend_24 = 0;
    p->blendStep_26 = 0x1000;
    p->target_0 = (int)&levantPos_8008BD18;
}
// Matched
void sub_80037720(void)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    p->flags_4 |= 0x2000;
}
// Matched
void sub_80037748(void)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    p->flags_4 |= 4;
}
// Matched
void sub_80037770(void)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    p->flags_4 &= ~4;
    p->flags_4 &= ~0x2000;
    RestoreCameraState_80039698(p);
}
extern void sub_8003970C(int a, int* b);
extern void sub_8003983C(int a, int* b);
// Matched
void sub_800377B4(int a0, short a1)
{
    if (a0 == 0)
    {
        if (a1 == 5 || a1 == 0x1A)
        {
            sub_8003970C(a1, dword_80083D00);
        }
    }
    else if (a0 == 1)
    {
        if (a1 == 2)
        {
            sub_8003983C(2, dword_80084330);
        }
    }
}
// Table in the overlay area (outside the linked image), 8 bytes per entry
extern struct_pair8 dword_800B1084[];
__asm__(".globl dword_800B1084\n.equ dword_800B1084,0x800b1084");
// Matched
void sub_80037828(int a, short b, int c)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    if (c)
    {
        sub_800390F4(p, 2);
    }
    else if (a == 0)
    {
        if (dword_800B1084[b].a != 0x10 && b != 0x11 && b != 0x12)
        {
            sub_800390F4(p, 1);
        }
    }
    else if (a != 1 || (unsigned short)(b - 0x11) >= 2)
    {
        sub_800390F4(p, 1);
    }
}
// Matched
void sub_800378CC(void)
{
    sub_800390F4(cameraTask_8008D4A0->entry.buffer, 1);
}
// Matched
int GetCameraMode_800378F8(void)
{
    return ((CameraCtrl*)cameraTask_8008D4A0->entry.buffer)->mode_8;
}
extern void sub_80038A5C(CameraCtrl* p, int a, struct_v3* b, int c);
// Matched
void sub_80037918(CameraCtrl* p)
{
    if (p->flags_4 & 0x10)
    {
        sub_80038A5C(p, p->target_0, &p->blendTarget_28, p->blend_24);
        p->blend_24 += 0x1000 / p->blendStep_26;
        if (p->blend_24 > 0x1000)
        {
            p->blend_24 = 0x1000;
        }
    }
    else
    {
        sub_80038A5C(p, p->target_0, &p->blendTarget_28, p->blend_24);
        p->blend_24 -= 0x1000 / p->blendStep_26;
        if (p->blend_24 < 0)
        {
            p->blend_24 = 0;
        }
    }
}
// Matched
void sub_800379DC(int* v, short n)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    p->blendTarget_28.x = v[0];
    p->blendTarget_28.y = v[1];
    p->blendTarget_28.z = v[2];
    p->flags_4 |= 0x10;
    p->blendStep_26 = n;
}
// Matched
void sub_80037A20(int a0, short n)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    p->blendStep_26 = n;
    p->flags_4 &= ~0x10;
}
// Matched
short sub_80037A4C(void)
{
    return ((CameraCtrl*)cameraTask_8008D4A0->entry.buffer)->blend_24;
}
// Matched
void sub_80037A6C(int a, int b)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    if (b >= 2)
    {
        p->zoomTarget_34 = a;
        p->zoomSteps_12 = b;
        p->zoomStart_A = *(unsigned short*)&dword_8008B4F8;
        p->flags_4 |= 0x20;
    }
    else
    {
        dword_8008B4F8 = a;
        sub_80037918(p);
    }
}
// Matched
void SetCameraTarget_80037AC8(int a0)
{
    ((CameraCtrl*)cameraTask_8008D4A0->entry.buffer)->target_0 = a0;
}
extern int* sub_800A1E3C(void);
extern BattleObj_800C0FAC* sub_800C0FAC(void);
extern unsigned char byte_800C9C7C;
extern void sub_80038E2C(CameraCtrl* p, int a, int b);
extern void sub_80036AB4();
// Matched
void sub_80037AE0(unsigned short mask)
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
        r = sub_800A1E3C();
        if (byte_800C9C7C == 0)
        {
            v = 0;
        }
        else
        {
            v = sub_800C0FAC()->field_7C + 0xF5;
        }
        sub_80038E2C(p, dword_80083CE8[r[0] - 1][sel], v);
        *(unsigned short*)&p->mode_8 = 4;
        cameraTask_8008D4A0->entry.cb_8 = (EventEntryFn)sub_80036AB4;
    }
}
// Matched
void sub_80037BFC(void)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    p->shake_10 = 0;
    p->flags_4 |= 0xC0;
}
// Matched
void sub_80037C24(void)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    p->flags_4 |= 0x100;
}
// Matched
void sub_80037C4C(void)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    p->flags_4 &= ~0x100;
}
// Matched
void sub_80037C74(CameraCtrl* q)
{
    int sel;

    q->counter_14 = 0;
    q->t_C = 0;
    dword_8008D474.a = 0;
    dword_8008D474.b = 0;
    cameraState_8008D4F0.r_30 = cameraState_8008D4F0.g_31 = cameraState_8008D4F0.b_32 = 0x40;
    cameraState_8008D4F0.field_2C = 0;
    if (unknownFlags_8008D678 & 0x2000000)
    {
        sel = 1;
    }
    else
    {
        sel = 0;
    }
    cameraState_8008D4F0.field_20.x = q->pos_38.x + (word_80084540[(q->rotY_44 + 0x400) & 0xFFF] * dword_80083BE4[sel].x1 / 4096 + word_80084540[q->rotY_44 & 0xFFF] * dword_80083BE4[sel].z1 / 4096);
    cameraState_8008D4F0.field_20.y = levantPos_8008BD18.pos.y + dword_80083BE4[sel].y1;
    cameraState_8008D4F0.field_20.z = q->pos_38.z + (-word_80084540[q->rotY_44 & 0xFFF] * dword_80083BE4[sel].x1 / 4096 + word_80084540[(q->rotY_44 + 0x400) & 0xFFF] * dword_80083BE4[sel].z1 / 4096);
    cameraState_8008D4F0.field_14.x = q->pos_38.x + (word_80084540[(q->rotY_44 + 0x400) & 0xFFF] * dword_80083BE4[sel].x0 / 4096 + word_80084540[q->rotY_44 & 0xFFF] * dword_80083BE4[sel].z0 / 4096);
    cameraState_8008D4F0.field_14.y = levantPos_8008BD18.pos.y + dword_80083BE4[sel].y0;
    cameraState_8008D4F0.field_14.z = q->pos_38.z + (-word_80084540[q->rotY_44 & 0xFFF] * dword_80083BE4[sel].x0 / 4096 + word_80084540[(q->rotY_44 + 0x400) & 0xFFF] * dword_80083BE4[sel].z0 / 4096);
    cameraState_8008D4F0.field_2E = dword_80083BE4[sel].field_8;
    setVector(&cameraState_8008D4F0.rot_34, q->rot_164.vx, q->rot_164.vy, q->rot_164.vz);
    setVector(&cameraState_8008D4F0.rot_3C, q->rot_174.vx, q->rot_174.vy, q->rot_174.vz);
    cameraState_8008D4F0.ent_44[0].rot.vx = 0x800;
    cameraState_8008D4F0.ent_44[0].rot.vy = 0x800;
    cameraState_8008D4F0.ent_44[0].rot.vz = 0x800;
    dword_8008B4F8 = q->field_188;
}
// Matched
void sub_80037F44(CameraCtrl* q)
{
    int i;

    SaveCameraState_80039620(q);
    q->field2ESrc_17C = cameraState_8008D4F0.field_2E;
    q->field2EDst_180 = 0xA0;
    q->lookSrc_1B0 = cameraState_8008D4F0.field_20;
    q->lookDst_198.x = saveData_8008B570.levant_7A8.pos.x;
    q->lookDst_198.y = saveData_8008B570.levant_7A8.pos.y - 0xFA;
    q->lookDst_198.z = saveData_8008B570.levant_7A8.pos.z;
    q->eyeSrc_1A4 = cameraState_8008D4F0.field_14;
    q->eyeDst_18C.x = saveData_8008B570.levant_7A8.pos.x + word_80084540[saveData_8008B570.levant_7A8.rot.vy & 0xFFF] * 200 / 4096;
    q->eyeDst_18C.y = saveData_8008B570.levant_7A8.pos.y - 0xFA;
    q->eyeDst_18C.z = saveData_8008B570.levant_7A8.pos.z + word_80084540[(saveData_8008B570.levant_7A8.rot.vy + 0x400) & 0xFFF] * 200 / 4096;
    q->pos_38.x = saveData_8008B570.levant_7A8.pos.x + word_80084540[saveData_8008B570.levant_7A8.rot.vy & 0xFFF] * 500 / 4096;
    q->pos_38.y = saveData_8008B570.levant_7A8.pos.y + 0xFA;
    q->pos_38.z = saveData_8008B570.levant_7A8.pos.z + word_80084540[(saveData_8008B570.levant_7A8.rot.vy + 0x400) & 0xFFF] * 500 / 4096;
    q->rotY_44 = saveData_8008B570.levant_7A8.rot.vy;
    for (i = 7; i >= 0; i--)
    {
        cameraState_8008D4F0.ent_44[i].field_14 = 0;
    }
    cameraState_8008D4F0.ent_44[0].pos = q->pos_38;
    setVector(&cameraState_8008D4F0.ent_44[0].rot, 0, 0, 0);
    cameraState_8008D4F0.ent_44[0].field_14 = 0xEA6;
    cameraState_8008D4F0.ent_44[0].pos.y -= 1000;
    q->rot_15C = cameraState_8008D4F0.rot_34;
    q->rot_164.vx = 0x7FC;
    q->rot_164.vy = -0xAA6;
    q->rot_164.vz = 0x8DE;
    q->rot_16C = cameraState_8008D4F0.rot_3C;
    q->rot_174.vx = 0x1000;
    q->rot_174.vy = 0x1000;
    q->rot_174.vz = 0x1000;
    q->savedZoom_184 = dword_8008B4F8;
    q->field_188 = 0x1000;
    sub_80038D64(q, &levantPos_8008BD18.pos.x);
    q->t_C = 0x1000;
}
#define EASE(p) (0x1000 - word_80084540[(((p)->t_C / 4) + 0x400) & 0xFFF])
// Matched
void sub_80038230(CameraCtrl* p)
{
    short ang;
    short r;

    cameraState_8008D4F0.field_20.x = p->lookDst_198.x + (p->lookSrc_1B0.x - p->lookDst_198.x) * EASE(p) / 4096;
    cameraState_8008D4F0.field_20.y = p->lookDst_198.y + (p->lookSrc_1B0.y - p->lookDst_198.y) * EASE(p) / 4096;
    cameraState_8008D4F0.field_20.z = p->lookDst_198.z + (p->lookSrc_1B0.z - p->lookDst_198.z) * EASE(p) / 4096;

    ang = *(unsigned short*)&p->angDst_152 + (p->angSrc_150 - p->angDst_152) * EASE(p) / 4096;
    r = *(unsigned short*)&p->distDst_158 + (p->distSrc_154 - p->distDst_158) * EASE(p) / 4096;
    cameraState_8008D4F0.field_14.x = p->pos_38.x + r * word_80084540[ang & 0xFFF] / 4096;
    cameraState_8008D4F0.field_14.y = p->eyeDst_18C.y + (p->eyeSrc_1A4.y - p->eyeDst_18C.y) * EASE(p) / 4096;
    cameraState_8008D4F0.field_14.z = p->pos_38.z + r * word_80084540[(ang + 0x400) & 0xFFF] / 4096;
    cameraState_8008D4F0.field_2E = *(unsigned short*)&p->field2EDst_180 + (p->field2ESrc_17C - p->field2EDst_180) * EASE(p) / 4096;
    if (p->t_C == 0)
    {
        cameraState_8008D4F0.field_14 = p->eyeDst_18C;
    }
    sub_8003891C(p, &levantPos_8008BD18.pos);
}
extern double pow(double, double);
// Matched
void sub_8003856C(CameraCtrl* p)
{
    unsigned int u;
    float f;

    dword_8008D4BC = dword_8008B4F8;
    if (GetCameraMode_800378F8() != 0)
    {
        return;
    }
    u = p->zoomTarget_34;
    if (u < (unsigned int)dword_8008B4F8 && (p->flags_4 & 0x20))
    {

        f = (float)dword_8008B4F8 * pow((float)u / (float)p->zoomStart_A, 1.0f / (float)p->zoomSteps_12);
        dword_8008B4F8 = f;
        if ((unsigned int)p->zoomTarget_34 >= (unsigned int)dword_8008B4F8)
        {
            p->flags_4 &= ~0x20;
        }
    }
    else if ((unsigned int)dword_8008B4F8 < u && (p->flags_4 & 0x20))
    {

        f = (float)dword_8008B4F8 * pow((float)u / (float)p->zoomStart_A, 1.0f / (float)p->zoomSteps_12);
        dword_8008B4F8 = f;
        if ((unsigned int)dword_8008B4F8 >= (unsigned int)p->zoomTarget_34)
        {
            p->flags_4 &= ~0x20;
        }
    }
    if (dword_8008B4F8 < 0x1000)
    {
        dword_8008B4F8 = 0x1000;
        p->flags_4 &= ~0x20;
    }
    if (dword_8008B4F8 > 0x10000)
    {
        dword_8008B4F8 = 0x10000;
        p->flags_4 &= ~0x20;
    }
    if (dword_8008D66C * 4 < word_8008D51E * dword_8008B4F8 / 4096)
    {
        dword_8008B4F8 = (dword_8008D66C << 14) / word_8008D51E;
        if (dword_8008B4F8 < 0x1000)
        {
            dword_8008B4F8 = 0x1000;
        }
        p->flags_4 &= ~0x20;
    }
}
extern void sub_8003856C(CameraCtrl* p);
extern void sub_800398B4(CameraCtrl* p, void* q);
extern int dword_8008D4BC;
typedef struct
{
    DVECTOR xy;
    int z;
} ScreenPosZ;
extern ScreenPosZ word_8008D668;
// Matched
void sub_8003891C(CameraCtrl* p, struct_v3* v)
{
    SVECTOR sv;
    long pr;
    long flag;
    int a;
    unsigned int b;
    sub_80039E14();
    sub_8003856C(p);
    a = word_8008D51E * dword_8008B4F8;
    b = word_8008D51E * dword_8008D4BC;
    sv.vx = v->x;
    sv.vy = v->y;
    sv.vz = v->z;
    sv.vy -= 0x15E;
    sv.vx -= cameraEye_8008D600.vx;
    sv.vy -= cameraEye_8008D600.vy;
    sv.vz -= cameraEye_8008D600.vz;
    geomScreenDistance_8008B548 = b >> 12;
    SetGeomScreen(a / 4096);
    word_8008D668.z = RotTransPers(&sv, (long*)&word_8008D668.xy, &pr, &flag);
    if (flag < 0)
    {
        word_8008D668.xy.vx = 0xA0;
        word_8008D668.xy.vy = 0x78;
    }
    SetGeomScreen(geomScreenDistance_8008B548);
    if (!(p->flags_4 & 0x800))
    {
        sub_800398B4(p, &word_8008D668);
    }
}
// Matched
void sub_80038A5C(CameraCtrl* p, int a, struct_v3* b, int t)
{
    struct_v3* v = (struct_v3*)a;
    SVECTOR sv;
    SVECTOR sv2;
    ScreenPosZ tmp;
    long pr;
    long flag;
    int s;
    unsigned int g;

    sub_80039E14();
    sub_8003856C(p);
    g = word_8008D51E * dword_8008D4BC;
    s = word_8008D51E * dword_8008B4F8;
    geomScreenDistance_8008B548 = g >> 12;
    SetGeomScreen(s / 4096);
    sv.vx = v->x;
    sv.vy = v->y;
    sv.vz = v->z;
    sv.vy -= 0x15E;
    sv.vx -= cameraEye_8008D600.vx;
    sv.vy -= cameraEye_8008D600.vy;
    sv.vz -= cameraEye_8008D600.vz;
    word_8008D668.z = RotTransPers(&sv, (long*)&word_8008D668.xy, &pr, &flag);
    sv2.vx = b->x;
    sv2.vy = b->y;
    sv2.vz = b->z;
    sv2.vy -= 0x15E;
    sv2.vx -= cameraEye_8008D600.vx;
    sv2.vy -= cameraEye_8008D600.vy;
    sv2.vz -= cameraEye_8008D600.vz;
    tmp.z = RotTransPers(&sv2, (long*)&tmp.xy, &pr, &flag);
    word_8008D668.xy.vx += (tmp.xy.vx - word_8008D668.xy.vx) * t / 4096;
    word_8008D668.xy.vy += (tmp.xy.vy - word_8008D668.xy.vy) * t / 4096;
    word_8008D668.z += (tmp.z - word_8008D668.z) * t / 4096;
    SetGeomScreen(geomScreenDistance_8008B548);
    if (!(p->flags_4 & 0x800))
    {
        sub_800398B4(p, &word_8008D668);
    }
}
// Matched
void sub_80038CA8(CameraCtrl* p)
{
    CameraCtrl* o = p;
    p->t_C = 0x1000;
    p->flags_4 &= ~8;
    o->lookSrc_1B0 = cameraState_8008D4F0.field_20;
    o->lookDst_198 = saveData_8008B570.levant_7A8.pos;
    o->eyeSrc_1A4 = cameraState_8008D4F0.field_14;
    o->eyeDst_18C = cameraState_8008D4F0.field_14;
    p->field2ESrc_17C = cameraState_8008D4F0.field_2E;
    p->field2EDst_180 = cameraState_8008D4F0.field_2E;
    sub_80038D64(o, &saveData_8008B570.levant_7A8.pos.x);
}
extern int DistanceSquaredXZ_8003B860(int* a, int* b);

// Matched
void sub_80038D64(CameraCtrl* p, int* a1)
{
    int d;
    p->angSrc_150 = ratan2Difference_8003B9E0(a1, stru_8008D504) & 0xFFF;
    p->distSrc_154 = ISqrt_8003B918(DistanceSquaredXZ_8003B860(a1, stru_8008D504));
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
void sub_80038E2C(CameraCtrl* p, int a, int b)
{
    CameraCtrl* o = p;

    p->t_C = 0x1000;
    p->flags_4 &= ~8;
    o->lookSrc_1B0 = cameraState_8008D4F0.field_20;
    o->lookDst_198 = o->pos_38;
    o->lookDst_198.y = saveData_8008B570.levant_7A8.pos.y + dword_80083C70[(unsigned short)a].y1;
    o->lookDst_198.z += -word_80084540[p->rotY_44 & 0xFFF] * dword_80083C70[(unsigned short)a].x1 / 4096 + word_80084540[(p->rotY_44 + 0x400) & 0xFFF] * dword_80083C70[(unsigned short)a].z1 / 4096;
    o->lookDst_198.x += word_80084540[(p->rotY_44 + 0x400) & 0xFFF] * dword_80083C70[(unsigned short)a].x1 / 4096 + word_80084540[p->rotY_44 & 0xFFF] * dword_80083C70[(unsigned short)a].z1 / 4096;
    o->eyeSrc_1A4 = cameraState_8008D4F0.field_14;
    o->eyeDst_18C = o->pos_38;
    o->eyeDst_18C.y = saveData_8008B570.levant_7A8.pos.y + dword_80083C70[(unsigned short)a].y0 + b;
    o->eyeDst_18C.z += -word_80084540[p->rotY_44 & 0xFFF] * dword_80083C70[(unsigned short)a].x0 / 4096 + word_80084540[(p->rotY_44 + 0x400) & 0xFFF] * dword_80083C70[(unsigned short)a].z0 / 4096;
    o->eyeDst_18C.x += word_80084540[(p->rotY_44 + 0x400) & 0xFFF] * dword_80083C70[(unsigned short)a].x0 / 4096 + word_80084540[p->rotY_44 & 0xFFF] * dword_80083C70[(unsigned short)a].z0 / 4096;
    p->field2ESrc_17C = cameraState_8008D4F0.field_2E;
    p->field2EDst_180 = dword_80083C70[(unsigned short)a].field_8;
    sub_80038D64(o, (int*)&p->pos_38);
}
extern int dword_800A85B8;
extern int DistanceSquared3D_8003B80C(int* a, int* b);
// Matched
void sub_800390F4(CameraCtrl* p_, int arg1)
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
        if (dword_800A85B8 < 0)
        {
            sel = 4;
        }
        else if (dword_800A85B8 == 0)
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
            v.y = saveData_8008B570.levant_7A8.pos.y + dword_80083C0C[sel].y1;
            v.z += -word_80084540[p_->rotY_44 & 0xFFF] * dword_80083C0C[sel].x1 / 4096 + word_80084540[(p_->rotY_44 + 0x400) & 0xFFF] * dword_80083C0C[sel].z1 / 4096;
            v.x += word_80084540[(p_->rotY_44 + 0x400) & 0xFFF] * dword_80083C0C[sel].x1 / 4096 + word_80084540[p_->rotY_44 & 0xFFF] * dword_80083C0C[sel].z1 / 4096;
            dist = DistanceSquared3D_8003B80C((int*)&cameraState_8008D4F0.field_14, (int*)&v);
            if (dist < best)
            {
                best = dist;
                sel = i;
            }
        }
    }
    p_->lookSrc_1B0 = cameraState_8008D4F0.field_20;
    p_->lookDst_198 = p_->pos_38;
    p_->lookDst_198.y = saveData_8008B570.levant_7A8.pos.y + dword_80083C0C[sel].y1;
    p_->lookDst_198.z += -word_80084540[p_->rotY_44 & 0xFFF] * dword_80083C0C[sel].x1 / 4096 + word_80084540[(p_->rotY_44 + 0x400) & 0xFFF] * dword_80083C0C[sel].z1 / 4096;
    p_->lookDst_198.x += word_80084540[(p_->rotY_44 + 0x400) & 0xFFF] * dword_80083C0C[sel].x1 / 4096 + word_80084540[p_->rotY_44 & 0xFFF] * dword_80083C0C[sel].z1 / 4096;
    p_->eyeSrc_1A4 = cameraState_8008D4F0.field_14;
    p_->eyeDst_18C = p_->pos_38;
    p_->eyeDst_18C.y = saveData_8008B570.levant_7A8.pos.y + dword_80083C0C[sel].y0;
    p_->eyeDst_18C.z += -word_80084540[p_->rotY_44 & 0xFFF] * dword_80083C0C[sel].x0 / 4096 + word_80084540[(p_->rotY_44 + 0x400) & 0xFFF] * dword_80083C0C[sel].z0 / 4096;
    p_->eyeDst_18C.x += word_80084540[(p_->rotY_44 + 0x400) & 0xFFF] * dword_80083C0C[sel].x0 / 4096 + word_80084540[p_->rotY_44 & 0xFFF] * dword_80083C0C[sel].z0 / 4096;
    p_->field2ESrc_17C = cameraState_8008D4F0.field_2E;
    p_->field2EDst_180 = dword_80083C0C[sel].field_8;
    sub_80038D64(p_, (int*)&p_->pos_38);
}
// Matched
int sub_800395D0(int* pIdx, int value, int* table)
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
    o->savedZoom_184 = dword_8008B4F8;
    o->savedShake_14C = dword_8008D474;
}
// Matched
void RestoreCameraState_80039698(CameraCtrl* o)
{
    cameraState_8008D4F0 = o->saved_48;
    dword_8008B4F8 = o->savedZoom_184;
    dword_8008D474 = o->savedShake_14C;
}
extern int sub_800AB4D8(int a);
// Matched
void sub_8003970C(int idx_, int* a5)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    struct_pair8* t = dword_800B1084;
    int* q;
    int r;
    p->field_1C = t[(short)idx_].b;
    p->spline_218 = (CamSpline*)a5;
    p->flags_4 |= 8;
    r = (short)sub_800AB4D8(0xE);
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
void sub_8003983C(int idx_, int* a5)
{
    CameraCtrl* p = cameraTask_8008D4A0->entry.buffer;
    struct_pair8* t = dword_800B1084;
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
extern ShortRect stru_8008D420;
extern short* dword_8008D654;
extern DRAWENV drawEnv_8008D698[2];
#define CLAMP_HALF(v, lim) ((v) < -(lim) / 2 ? -(lim) / 2 : ((lim) / 2 < (v) ? (lim) / 2 : (v)))
// Matched
void sub_800398B4(CameraCtrl* p, void* q_)
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
        dword_8008D474.a = dword_8008D474.a - (q->xy.vx - (stru_8008D420.x + stru_8008D420.w / 2));
        dword_8008D474.b = dword_8008D474.b - (q->xy.vy - (stru_8008D420.y + stru_8008D420.h / 2));
        sp = dword_8008D654;
        s = dword_8008B4F8 << 5;
        lx = sp[4] * s / 4096 - stru_8008D420.w;
        ly = sp[5] * s / 4096 - stru_8008D420.h;
        dword_8008D474.a = CLAMP_HALF(dword_8008D474.a, lx);
        dword_8008D474.b = CLAMP_HALF(dword_8008D474.b, ly);
        dword_8008D474.a = dword_8008D474.a - (display_8008B4D8.field_C_w / 2 - (stru_8008D420.x + stru_8008D420.w / 2));
        dword_8008D474.b = dword_8008D474.b - (display_8008B4D8.field_E_h / 2 - (stru_8008D420.y + stru_8008D420.h / 2));
        r.x = drawEnv_8008D698[bDoubleBuffer_8008D428].clip.x + stru_8008D420.x;
        r.y = drawEnv_8008D698[bDoubleBuffer_8008D428].clip.y + stru_8008D420.y;
        r.w = stru_8008D420.w;
        r.h = stru_8008D420.h;
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
                dword_8008D474.b += dword_80083BD4[p->shake_10];
            }
            else
            {
                dword_8008D474.a += dword_80083BD4[p->shake_10];
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
            dword_8008D474.b = dword_80083BD4[p->shake_10];
        }
        else
        {
            dword_8008D474.a = dword_80083BD4[p->shake_10];
        }
        if ((unsigned short)++p->shake_10 >= 15)
        {
            dword_8008D474.a = 0;
            dword_8008D474.b = 0;
            p->flags_4 &= ~0x40;
        }
    }
}
extern SVECTOR word_8008D4C8;
extern void SetGteLightAndCamera_8004D0E8(void);
// Matched
void sub_80039E14(void)
{
    VECTOR d;
    int a;
    cameraEye_8008D600.vx = cameraState_8008D4F0.field_14.x;
    cameraEye_8008D600.vy = cameraState_8008D4F0.field_14.y;
    cameraEye_8008D600.vz = cameraState_8008D4F0.field_14.z;
    d.vx = cameraState_8008D4F0.field_20.x - cameraState_8008D4F0.field_14.x;
    d.vy = cameraState_8008D4F0.field_20.y - cameraState_8008D4F0.field_14.y;
    d.vz = cameraState_8008D4F0.field_20.z - cameraState_8008D4F0.field_14.z;
    a = ratan2_8003B548(d.vx, d.vz);
    word_8008D4C8.vy = -a;
    word_8008D4C8.vx = ratan2_8003B548(d.vy, ISqrt_8003B918(LengthSquared2D_8003B8BC(d.vx, d.vz)));
    word_8008D4C8.vz = cameraState_8008D4F0.field_2C;
    SetGteLightAndCamera_8004D0E8();
}
// stru_8008D534[0].rot.vx/vy/vz through the CamEntry type changes the scheduling, so the short view stays
// Matched
void sub_80039ED8(int mode)
{
    switch ((short)(mode + 1))
    {
    case 0:
        ((short*)stru_8008D534)[6] = 0x800;
        ((short*)stru_8008D534)[7] = 0x800;
        ((short*)stru_8008D534)[8] = 0x800;
        break;
    case 1:
        ((short*)stru_8008D534)[6] = 0x1000;
        ((short*)stru_8008D534)[7] = 0;
        ((short*)stru_8008D534)[8] = 0x6B0;
        break;
    case 4:
        ((short*)stru_8008D534)[6] = 0x150;
        ((short*)stru_8008D534)[7] = 0;
        ((short*)stru_8008D534)[8] = 0x1000;
        break;
    case 3:
        ((short*)stru_8008D534)[6] = 0;
        ((short*)stru_8008D534)[7] = 0x1000;
        ((short*)stru_8008D534)[8] = 0x940;
        break;
    case 2:
        ((short*)stru_8008D534)[6] = 0xEB0;
        ((short*)stru_8008D534)[7] = 0x1000;
        ((short*)stru_8008D534)[8] = 0;
        break;
    }
}
