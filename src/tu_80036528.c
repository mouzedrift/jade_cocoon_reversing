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
typedef struct
{
    int pad_0[5];
    struct_v3 field_14;
    struct_v3 field_20;
    short field_2C;
    short field_2E;
    unsigned char r_30;
    unsigned char g_31;
    unsigned char b_32;
    unsigned char pad_33;
    SVECTOR rot_34;
    SVECTOR rot_3C;
    CamEntry ent_44[8];
} Block104;
typedef struct
{
    short x0;
    short y0;
    short z0;
    short pad_6;
    int field_8;
    short x1;
    short y1;
    short z1;
    short pad_12;
} CamOffset;

typedef struct
{
    short a;
    short b;
} ShortPair;
extern Block104 cameraState_8008D4F0;
extern ShortPair dword_8008D474;
typedef struct
{
    unsigned short field_0;
    unsigned char field_2;
    unsigned char field_3;
} PadVibEntry;
extern PadVibEntry* vibrationPatterns_80083B30[];
typedef struct
{
    unsigned char idx;
    unsigned char b;
    unsigned char k;
    unsigned char pad;
    short field_4;
} struct_buf_80036528;
extern EventNode* vibrationTasks_8008D4B8;
extern void UpdatePadVibration_800366A0(EventEntry* e, struct_buf_80036528* o);
#if 0
// Not matched: o->idx store is forwarded instead of reloaded, idx/b land in swapped registers
void StartPadVibration_80036528(int idx, unsigned char b)
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
    o->field_4 = vibrationPatterns_80083B30[(unsigned char)b][0].field_0;
    padVibration_80095460[o->idx].motor_2[0] = vibrationPatterns_80083B30[o->b][o->k].field_2;
    padVibration_80095460[o->idx].motor_2[1] = vibrationPatterns_80083B30[o->b][o->k].field_3;
}
#endif
INCLUDE_ASM(StartPadVibration_80036528);
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
extern int dword_80083844[];

// Matched
void UpdatePadVibration_80036820(int port)
{
    int st = PadGetState(port << 4);
    if (st != 0)
    {
        if (st == 1)
        {
            *(unsigned short*)&padVibration_80095460[port] &= 0xFFFE;
        }
        if (!(*(unsigned short*)&padVibration_80095460[port] & 1))
        {
            PadSetAct(port << 4, (unsigned char*)&padVibration_80095460[port].motor_2[0], 2);
            if (st == 2 || (st == 6 && PadSetActAlign(port << 4, (unsigned char*)dword_80083844)))
            {
                *(unsigned short*)&padVibration_80095460[port] |= 1;
            }
        }
    }
}
extern void sub_80037918();
extern char levantPos_8008BD18[];
extern void SaveCameraState_80039620(char* o);
extern void sub_80038CA8();
extern void sub_80037F44(int* p);
extern void sub_800374E0();
extern int sub_800B8184(int a, int b);
extern void sub_800369E0(struct_obj_D* p, int* q);


// Matched
void InitCameraTask_800368F8(struct_obj_D* p, int* q)
{
    if (q[1] & 0x100)
    {
        SaveCameraState_80039620((char*)q);
        q[0xE] = ((int*)levantPos_8008BD18)[0];
        q[0xF] = ((int*)levantPos_8008BD18)[1];
        q[0x10] = ((int*)levantPos_8008BD18)[2];
        sub_80038CA8((char*)q);
        *(short*)(q + 2) = 6;
        p->field_8 = sub_800374E0;
    }
    else if (!(q[1] & 0x2000))
    {
        char* sd = (char*)&saveData_8008B570;
        int r = sub_800B8184(q[0], *(short*)(sd + 0x2F0));
        if (r >= 0)
        {
            *(short*)(sd + 0x2F0) = r;
        }
    }
    else
    {
        sub_80037F44(q);
        *(short*)(q + 2) = 2;
        p->field_8 = (void (*)(void))sub_800369E0;
        ((void (*)(struct_obj_D*, int*))p->field_8)(p, q);
    }
    sub_80037918(q);
}
extern void sub_80037C74(int* q);
extern void sub_8003891C(int* p, void* q);
extern void sub_800BC90C(int* q);
extern void sub_80036AB4(struct_obj_D* p, int* q);
extern void sub_8001AA04(int a);



// Matched
void sub_800369E0(struct_obj_D* p, int* q)
{
    switch (*(short*)(q + 2))
    {
    case 2:
        if (q[1] & 4)
        {
            *(short*)(q + 2) += 1;
            sub_80037C74(q);
            sub_8001AA04(8);
        }
        break;
    case 3:
        q[5] = q[5] + 1;
        if (q[5] >= 0x3D)
        {
            sub_800390F4(q, 1);
            *(short*)(q + 2) = 4;
            p->field_8 = (void (*)(void))sub_80036AB4;
        }
        sub_8003891C(q, levantPos_8008BD18);
        sub_800BC90C(q);
        break;
    }
}
extern void sub_80038230(int* p);
extern void InitCameraTask_800368F8(struct_obj_D* p, int* q);
extern void sub_80036BB0(void);

// Matched
void sub_80036AB4(struct_obj_D* p, int* q)
{
    int* r = q;
    if (q[1] & 4)
    {
        sub_80038230(q);
        if (q[3] > 0)
        {
            q[3] -= 0x100;
        }
        if (q[3] < 0)
        {
            q[3] = 0;
        }
        if (q[1] & 4)
        {
            goto run;
        }
    }
    sub_80037918(r);
    sub_8003891C(r, levantPos_8008BD18);
    r[1] &= ~0x1000;
    *(short*)(r + 2) = 0;
    p->field_8 = (void (*)(void))InitCameraTask_800368F8;
    return;
run:
    sub_800BC90C(r);
    if (r[1] & 8)
    {
        *(short*)(r + 2) = 5;
        r[0x71] = 0;
        p->field_8 = sub_80036BB0;
        r[3] = 0;
    }
}
INCLUDE_ASM(sub_80036BB0);
extern int DistanceSquaredXZ_8003B860(int* a, int* b);
void sub_80038D64(char* o, int* a);
extern void sub_80038230(int* p);
extern char levantPos_8008BD18[];
extern void sub_800375F8(int* o, int* p);
// Matched
void sub_800374E0(struct_obj_D* p, int* q)
{
    char* o = (char*)q;
    if (q[1] & 0x100)
    {
        *(short*)(o + 0x152) += 0x10;
        sub_80038230(q);
        if (q[3] > 0)
        {
            q[3] -= 0x1000;
        }
        if (q[3] < 0)
        {
            q[3] = 0;
        }
    }
    else
    {
        q[3] = 0x1000;
        *(struct_v3*)(o + 0x1B0) = cameraState_8008D4F0.field_20;
        *(struct_v3*)(o + 0x198) = *(struct_v3*)(o + 0x68);
        *(struct_v3*)(o + 0x1A4) = *(struct_v3*)(o + 0x5C);
        *(struct_v3*)(o + 0x18C) = *(struct_v3*)(o + 0x5C);
        q[0x17C / 4] = cameraState_8008D4F0.field_2E;
        q[0x180 / 4] = cameraState_8008D4F0.field_2E;
        sub_80038D64(o, (int*)levantPos_8008BD18);
        p->field_8 = (void (*)(void))sub_800375F8;
    }
}
extern int dword_8008B4F8;
// Matched
void sub_800375F8(int* o, int* p)
{
    int* q = p;
    if (p[3] > 0)
    {
        sub_80038230(p);
        if (p[3] > 0)
        {
            p[3] -= 0x1000;
        }
        if (p[3] < 0)
        {
            p[3] = 0;
        }
    }
    else
    {
        RestoreCameraState_80039698(q);
        sub_80037918(q);
        sub_8003891C(q, levantPos_8008BD18);
        ((short*)q)[4] = 0;
        o[2] = (int)InitCameraTask_800368F8;
    }
}
// Matched
void nullsub_5(void)
{
}
extern void sub_80039E14(void);
extern int geomScreenDistance_8008B548;
extern short word_8008D51E;
// Matched
void ResetCameraToLevant_800376A8(void)
{
    int* p = cameraTask_8008D4A0[0x24 / 4];
    short* sp;
    sub_80039E14();
    dword_8008B4F8 = 0x1000;
    geomScreenDistance_8008B548 = (word_8008D51E << 12) / 0x1000;
    sp = (short*)p;
    p[1] = 0;
    sp[4] = 0;
    sp[0x24 / 2] = 0;
    sp[0x26 / 2] = 0x1000;
    p[0] = (int)levantPos_8008BD18;
}
// Matched
void sub_80037720(void)
{
    int* p = cameraTask_8008D4A0[0x24 / 4];
    p[1] |= 0x2000;
}
// Matched
void sub_80037748(void)
{
    int* p = cameraTask_8008D4A0[0x24 / 4];
    p[1] |= 4;
}
// Matched
void sub_80037770(void)
{
    int* p = cameraTask_8008D4A0[0x24 / 4];
    p[1] &= ~4;
    p[1] &= ~0x2000;
    RestoreCameraState_80039698(p);
}
extern int dword_80083D00[];
extern int dword_80084330[];
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
extern int dword_800B1084[];
__asm__(".globl dword_800B1084\n.equ dword_800B1084,0x800b1084");
// Matched
void sub_80037828(int a, short b, int c)
{
    void* p = cameraTask_8008D4A0[0x24 / 4];
    if (c)
    {
        sub_800390F4(p, 2);
    }
    else if (a == 0)
    {
        if (dword_800B1084[b * 2] != 0x10 && b != 0x11 && b != 0x12)
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
    sub_800390F4(cameraTask_8008D4A0[0x24 / 4], 1);
}
// Matched
int GetCameraMode_800378F8(void)
{
    return ((short*)cameraTask_8008D4A0[0x24 / 4])[4];
}
typedef struct
{
    int field_0;
    unsigned int flags_4;
    char pad_8[0x1C];
    short field_24;
    short field_26;
    int field_28[3];
} struct_obj_37918;
extern void sub_80038A5C(struct_obj_37918* p, int a, int* b, int c);
// Matched
void sub_80037918(struct_obj_37918* p)
{
    if (p->flags_4 & 0x10)
    {
        sub_80038A5C(p, p->field_0, p->field_28, p->field_24);
        p->field_24 += 0x1000 / p->field_26;
        if (p->field_24 > 0x1000)
        {
            p->field_24 = 0x1000;
        }
    }
    else
    {
        sub_80038A5C(p, p->field_0, p->field_28, p->field_24);
        p->field_24 -= 0x1000 / p->field_26;
        if (p->field_24 < 0)
        {
            p->field_24 = 0;
        }
    }
}
// Matched
void sub_800379DC(int* v, short n)
{
    struct_obj_37918* p = (struct_obj_37918*)cameraTask_8008D4A0[0x24 / 4];
    p->field_28[0] = v[0];
    p->field_28[1] = v[1];
    p->field_28[2] = v[2];
    p->flags_4 |= 0x10;
    p->field_26 = n;
}
// Matched
void sub_80037A20(int a0, short n)
{
    int* p = cameraTask_8008D4A0[0x24 / 4];
    ((short*)p)[0x26 / 2] = n;
    p[1] &= ~0x10;
}
// Matched
short sub_80037A4C(void)
{
    return ((short*)cameraTask_8008D4A0[0x24 / 4])[0x12];
}
// Matched
void sub_80037A6C(int a, int b)
{
    int* p = cameraTask_8008D4A0[0x24 / 4];
    if (b >= 2)
    {
        p[0x34 / 4] = a;
        ((short*)p)[0x12 / 2] = b;
        ((short*)p)[0xA / 2] = *(unsigned short*)&dword_8008B4F8;
        p[1] |= 0x20;
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
    *(int*)cameraTask_8008D4A0[0x24 / 4] = a0;
}
extern unsigned short dword_80083CE8[][4];
extern int* sub_800A1E3C(void);
extern int* sub_800C0FAC(void);
extern unsigned char byte_800C9C7C;
extern void sub_80038E2C(int* p, int a, int b);
extern void sub_80036AB4();
// Matched
void sub_80037AE0(unsigned short mask)
{
    int sel = 0;
    int cnt = 0;
    int i;
    int* p = cameraTask_8008D4A0[0x24 / 4];
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
    if (((unsigned short*)p)[4] == 4 || ((unsigned short*)p)[4] == 5)
    {
        r = sub_800A1E3C();
        if (byte_800C9C7C == 0)
        {
            v = 0;
        }
        else
        {
            v = sub_800C0FAC()[0x7C / 4] + 0xF5;
        }
        sub_80038E2C(p, dword_80083CE8[r[0] - 1][sel], v);
        ((unsigned short*)p)[4] = 4;
        cameraTask_8008D4A0[0x18 / 4] = (int*)sub_80036AB4;
    }
}
// Matched
void sub_80037BFC(void)
{
    int* p = cameraTask_8008D4A0[0x24 / 4];
    ((short*)p)[0x10 / 2] = 0;
    p[1] |= 0xC0;
}
// Matched
void sub_80037C24(void)
{
    int* p = cameraTask_8008D4A0[0x24 / 4];
    p[1] |= 0x100;
}
// Matched
void sub_80037C4C(void)
{
    int* p = cameraTask_8008D4A0[0x24 / 4];
    p[1] &= ~0x100;
}
extern CamOffset dword_80083BE4[];
// Matched
void sub_80037C74(int* q)
{
    char* o = (char*)q;
    int sel;

    q[0x14 / 4] = 0;
    q[0xC / 4] = 0;
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
    cameraState_8008D4F0.field_20.x = q[0x38 / 4] + (word_80084540[(q[0x44 / 4] + 0x400) & 0xFFF] * dword_80083BE4[sel].x1 / 4096 + word_80084540[q[0x44 / 4] & 0xFFF] * dword_80083BE4[sel].z1 / 4096);
    cameraState_8008D4F0.field_20.y = ((int*)levantPos_8008BD18)[1] + dword_80083BE4[sel].y1;
    cameraState_8008D4F0.field_20.z = q[0x40 / 4] + (-word_80084540[q[0x44 / 4] & 0xFFF] * dword_80083BE4[sel].x1 / 4096 + word_80084540[(q[0x44 / 4] + 0x400) & 0xFFF] * dword_80083BE4[sel].z1 / 4096);
    cameraState_8008D4F0.field_14.x = q[0x38 / 4] + (word_80084540[(q[0x44 / 4] + 0x400) & 0xFFF] * dword_80083BE4[sel].x0 / 4096 + word_80084540[q[0x44 / 4] & 0xFFF] * dword_80083BE4[sel].z0 / 4096);
    cameraState_8008D4F0.field_14.y = ((int*)levantPos_8008BD18)[1] + dword_80083BE4[sel].y0;
    cameraState_8008D4F0.field_14.z = q[0x40 / 4] + (-word_80084540[q[0x44 / 4] & 0xFFF] * dword_80083BE4[sel].x0 / 4096 + word_80084540[(q[0x44 / 4] + 0x400) & 0xFFF] * dword_80083BE4[sel].z0 / 4096);
    cameraState_8008D4F0.field_2E = dword_80083BE4[sel].field_8;
    setVector(&cameraState_8008D4F0.rot_34, *(short*)(o + 0x164), *(short*)(o + 0x166), *(short*)(o + 0x168));
    setVector(&cameraState_8008D4F0.rot_3C, *(short*)(o + 0x174), *(short*)(o + 0x176), *(short*)(o + 0x178));
    cameraState_8008D4F0.ent_44[0].rot.vx = 0x800;
    cameraState_8008D4F0.ent_44[0].rot.vy = 0x800;
    cameraState_8008D4F0.ent_44[0].rot.vz = 0x800;
    dword_8008B4F8 = q[0x188 / 4];
}
typedef struct
{
    struct_v3 pos;
    short rotX;
    short rotY;
} LevantPos_7A8;
typedef struct
{
    char pad_0[0x15C];
    SVECTOR v15C;
    SVECTOR v164;
    SVECTOR v16C;
    SVECTOR v174;
    int f17C;
    int f180;
    int f184;
    int f188;
} CamObj_15C;
typedef struct
{
    char pad_0[0x7A8];
    LevantPos_7A8 levant_7A8;
} SaveDataHead_7A8;
#define SAVE_LEVANT (((SaveDataHead_7A8*)&saveData_8008B570)->levant_7A8)
// Matched
void sub_80037F44(int* q)
{
    int i;

    SaveCameraState_80039620((char*)q);
    q[0x17C / 4] = cameraState_8008D4F0.field_2E;
    q[0x180 / 4] = 0xA0;
    *(struct_v3*)((char*)q + 0x1B0) = cameraState_8008D4F0.field_20;
    *(int*)((char*)q + 0x198) = SAVE_LEVANT.pos.x;
    *(int*)((char*)q + 0x19C) = SAVE_LEVANT.pos.y - 0xFA;
    *(int*)((char*)q + 0x1A0) = SAVE_LEVANT.pos.z;
    *(struct_v3*)((char*)q + 0x1A4) = cameraState_8008D4F0.field_14;
    *(int*)((char*)q + 0x18C) = SAVE_LEVANT.pos.x + word_80084540[SAVE_LEVANT.rotY & 0xFFF] * 200 / 4096;
    *(int*)((char*)q + 0x190) = SAVE_LEVANT.pos.y - 0xFA;
    *(int*)((char*)q + 0x194) = SAVE_LEVANT.pos.z + word_80084540[(SAVE_LEVANT.rotY + 0x400) & 0xFFF] * 200 / 4096;
    q[0x38 / 4] = SAVE_LEVANT.pos.x + word_80084540[SAVE_LEVANT.rotY & 0xFFF] * 500 / 4096;
    q[0x3C / 4] = SAVE_LEVANT.pos.y + 0xFA;
    q[0x40 / 4] = SAVE_LEVANT.pos.z + word_80084540[(SAVE_LEVANT.rotY + 0x400) & 0xFFF] * 500 / 4096;
    q[0x44 / 4] = SAVE_LEVANT.rotY;
    for (i = 7; i >= 0; i--)
    {
        cameraState_8008D4F0.ent_44[i].field_14 = 0;
    }
    cameraState_8008D4F0.ent_44[0].pos = *(struct_v3*)((char*)q + 0x38);
    setVector(&cameraState_8008D4F0.ent_44[0].rot, 0, 0, 0);
    cameraState_8008D4F0.ent_44[0].field_14 = 0xEA6;
    cameraState_8008D4F0.ent_44[0].pos.y -= 1000;
    ((CamObj_15C*)q)->v15C = cameraState_8008D4F0.rot_34;
    ((CamObj_15C*)q)->v164.vx = 0x7FC;
    ((CamObj_15C*)q)->v164.vy = -0xAA6;
    ((CamObj_15C*)q)->v164.vz = 0x8DE;
    ((CamObj_15C*)q)->v16C = cameraState_8008D4F0.rot_3C;
    ((CamObj_15C*)q)->v174.vx = 0x1000;
    ((CamObj_15C*)q)->v174.vy = 0x1000;
    ((CamObj_15C*)q)->v174.vz = 0x1000;
    ((CamObj_15C*)q)->f184 = dword_8008B4F8;
    ((CamObj_15C*)q)->f188 = 0x1000;
    sub_80038D64((char*)q, (int*)levantPos_8008BD18);
    q[0xC / 4] = 0x1000;
}
#define I32(o, off) (*(int*)((char*)(o) + (off)))
#define I16(o, off) (*(short*)((char*)(o) + (off)))
#define U16(o, off) (*(unsigned short*)((char*)(o) + (off)))
#define EASE(p) (0x1000 - word_80084540[(((p)[3] / 4) + 0x400) & 0xFFF])
// Matched
void sub_80038230(int* p)
{
    short ang;
    short r;

    cameraState_8008D4F0.field_20.x = I32(p, 0x198) + (I32(p, 0x1B0) - I32(p, 0x198)) * EASE(p) / 4096;
    cameraState_8008D4F0.field_20.y = I32(p, 0x19C) + (I32(p, 0x1B4) - I32(p, 0x19C)) * EASE(p) / 4096;
    cameraState_8008D4F0.field_20.z = I32(p, 0x1A0) + (I32(p, 0x1B8) - I32(p, 0x1A0)) * EASE(p) / 4096;

    ang = U16(p, 0x152) + (I16(p, 0x150) - I16(p, 0x152)) * EASE(p) / 4096;
    r = U16(p, 0x158) + (I32(p, 0x154) - I32(p, 0x158)) * EASE(p) / 4096;
    cameraState_8008D4F0.field_14.x = p[0x38 / 4] + r * word_80084540[ang & 0xFFF] / 4096;
    cameraState_8008D4F0.field_14.y = I32(p, 0x190) + (I32(p, 0x1A8) - I32(p, 0x190)) * EASE(p) / 4096;
    cameraState_8008D4F0.field_14.z = p[0x40 / 4] + r * word_80084540[(ang + 0x400) & 0xFFF] / 4096;
    cameraState_8008D4F0.field_2E = U16(p, 0x180) + (I32(p, 0x17C) - I32(p, 0x180)) * EASE(p) / 4096;
    if (p[3] == 0)
    {
        cameraState_8008D4F0.field_14 = *(struct_v3*)((char*)p + 0x18C);
    }
    sub_8003891C(p, levantPos_8008BD18);
}
extern double pow(double, double);
extern int dword_8008D4BC;
extern int dword_8008D66C;
// Matched
void sub_8003856C(int* p)
{
    unsigned int u;
    float f;

    dword_8008D4BC = dword_8008B4F8;
    if (GetCameraMode_800378F8() != 0)
    {
        return;
    }
    u = p[0x34 / 4];
    if (u < (unsigned int)dword_8008B4F8 && (p[1] & 0x20))
    {

        f = (float)dword_8008B4F8 * pow((float)u / (float)*(unsigned short*)((char*)p + 0xA), 1.0f / (float)*(unsigned short*)((char*)p + 0x12));
        dword_8008B4F8 = f;
        if ((unsigned int)p[0x34 / 4] >= (unsigned int)dword_8008B4F8)
        {
            p[1] &= ~0x20;
        }
    }
    else if ((unsigned int)dword_8008B4F8 < u && (p[1] & 0x20))
    {

        f = (float)dword_8008B4F8 * pow((float)u / (float)*(unsigned short*)((char*)p + 0xA), 1.0f / (float)*(unsigned short*)((char*)p + 0x12));
        dword_8008B4F8 = f;
        if ((unsigned int)dword_8008B4F8 >= (unsigned int)p[0x34 / 4])
        {
            p[1] &= ~0x20;
        }
    }
    if (dword_8008B4F8 < 0x1000)
    {
        dword_8008B4F8 = 0x1000;
        p[1] &= ~0x20;
    }
    if (dword_8008B4F8 > 0x10000)
    {
        dword_8008B4F8 = 0x10000;
        p[1] &= ~0x20;
    }
    if (dword_8008D66C * 4 < word_8008D51E * dword_8008B4F8 / 4096)
    {
        dword_8008B4F8 = (dword_8008D66C << 14) / word_8008D51E;
        if (dword_8008B4F8 < 0x1000)
        {
            dword_8008B4F8 = 0x1000;
        }
        p[1] &= ~0x20;
    }
}
extern void sub_8003856C(int* p);
extern void sub_800398B4(int* p, void* q);
extern int dword_8008D4BC;
#define D600_VEC ((VECTOR*)dword_8008D600)
typedef struct
{
    DVECTOR xy;
    int z;
} ScreenPosZ;
extern ScreenPosZ word_8008D668;
// Matched
void sub_8003891C(int* p, void* q)
{
    int* v = (int*)q;
    SVECTOR sv;
    long pr;
    long flag;
    int a;
    unsigned int b;
    sub_80039E14();
    sub_8003856C(p);
    a = word_8008D51E * dword_8008B4F8;
    b = word_8008D51E * dword_8008D4BC;
    sv.vx = v[0];
    sv.vy = v[1];
    sv.vz = v[2];
    sv.vy -= 0x15E;
    sv.vx -= D600_VEC->vx;
    sv.vy -= D600_VEC->vy;
    sv.vz -= D600_VEC->vz;
    geomScreenDistance_8008B548 = b >> 12;
    SetGeomScreen(a / 4096);
    word_8008D668.z = RotTransPers(&sv, (long*)&word_8008D668.xy, &pr, &flag);
    if (flag < 0)
    {
        word_8008D668.xy.vx = 0xA0;
        word_8008D668.xy.vy = 0x78;
    }
    SetGeomScreen(geomScreenDistance_8008B548);
    if (!(p[1] & 0x800))
    {
        sub_800398B4(p, &word_8008D668);
    }
}
// Matched
void sub_80038A5C(struct_obj_37918* p, int a, int* b, int t)
{
    int* v = (int*)a;
    SVECTOR sv;
    SVECTOR sv2;
    ScreenPosZ tmp;
    long pr;
    long flag;
    int s;
    unsigned int g;

    sub_80039E14();
    sub_8003856C((int*)p);
    g = word_8008D51E * dword_8008D4BC;
    s = word_8008D51E * dword_8008B4F8;
    geomScreenDistance_8008B548 = g >> 12;
    SetGeomScreen(s / 4096);
    sv.vx = v[0];
    sv.vy = v[1];
    sv.vz = v[2];
    sv.vy -= 0x15E;
    sv.vx -= D600_VEC->vx;
    sv.vy -= D600_VEC->vy;
    sv.vz -= D600_VEC->vz;
    word_8008D668.z = RotTransPers(&sv, (long*)&word_8008D668.xy, &pr, &flag);
    sv2.vx = b[0];
    sv2.vy = b[1];
    sv2.vz = b[2];
    sv2.vy -= 0x15E;
    sv2.vx -= D600_VEC->vx;
    sv2.vy -= D600_VEC->vy;
    sv2.vz -= D600_VEC->vz;
    tmp.z = RotTransPers(&sv2, (long*)&tmp.xy, &pr, &flag);
    word_8008D668.xy.vx += (tmp.xy.vx - word_8008D668.xy.vx) * t / 4096;
    word_8008D668.xy.vy += (tmp.xy.vy - word_8008D668.xy.vy) * t / 4096;
    word_8008D668.z += (tmp.z - word_8008D668.z) * t / 4096;
    SetGeomScreen(geomScreenDistance_8008B548);
    if (!(p->flags_4 & 0x800))
    {
        sub_800398B4((int*)p, &word_8008D668);
    }
}
// Matched
void sub_80038CA8(int* p)
{
    char* o = (char*)p;
    char* sd = (char*)&saveData_8008B570;
    p[3] = 0x1000;
    p[1] &= ~8;
    *(struct_v3*)(o + 0x1B0) = cameraState_8008D4F0.field_20;
    *(struct_v3*)(o + 0x198) = *(struct_v3*)(sd + 0x7A8);
    *(struct_v3*)(o + 0x1A4) = cameraState_8008D4F0.field_14;
    *(struct_v3*)(o + 0x18C) = cameraState_8008D4F0.field_14;
    p[0x17C / 4] = cameraState_8008D4F0.field_2E;
    p[0x180 / 4] = cameraState_8008D4F0.field_2E;
    sub_80038D64(o, (int*)(sd + 0x7A8));
}
extern int stru_8008D504[];
extern int DistanceSquaredXZ_8003B860(int* a, int* b);

// Matched
void sub_80038D64(char* p, int* a1)
{
    int d;
    *(short*)(p + 0x150) = ratan2Difference_8003B9E0(a1, stru_8008D504) & 0xFFF;
    *(int*)(p + 0x154) = ISqrt_8003B918(DistanceSquaredXZ_8003B860(a1, stru_8008D504));
    *(short*)(p + 0x152) = ratan2Difference_8003B9E0(a1, (int*)(p + 0x18C)) & 0xFFF;
    *(int*)(p + 0x158) = ISqrt_8003B918(DistanceSquaredXZ_8003B860(a1, (int*)(p + 0x18C)));
    d = *(short*)(p + 0x152) - *(short*)(p + 0x150);
    if (d > 0x800)
    {
        *(short*)(p + 0x152) = *(unsigned short*)(p + 0x152) - 0x1000;
    }
    else if (d < -0x800)
    {
        *(short*)(p + 0x152) = *(unsigned short*)(p + 0x152) + 0x1000;
    }
}
extern CamOffset dword_80083C70[];
// Matched
void sub_80038E2C(int* p, int a, int b)
{
    char* o = (char*)p;
    char* sd = (char*)&saveData_8008B570;

    p[3] = 0x1000;
    p[1] &= ~8;
    *(struct_v3*)(o + 0x1B0) = cameraState_8008D4F0.field_20;
    *(struct_v3*)(o + 0x198) = *(struct_v3*)(o + 0x38);
    *(int*)(o + 0x19C) = *(int*)(sd + 0x7AC) + dword_80083C70[(unsigned short)a].y1;
    *(int*)(o + 0x1A0) += -word_80084540[p[0x44 / 4] & 0xFFF] * dword_80083C70[(unsigned short)a].x1 / 4096 + word_80084540[(p[0x44 / 4] + 0x400) & 0xFFF] * dword_80083C70[(unsigned short)a].z1 / 4096;
    *(int*)(o + 0x198) += word_80084540[(p[0x44 / 4] + 0x400) & 0xFFF] * dword_80083C70[(unsigned short)a].x1 / 4096 + word_80084540[p[0x44 / 4] & 0xFFF] * dword_80083C70[(unsigned short)a].z1 / 4096;
    *(struct_v3*)(o + 0x1A4) = cameraState_8008D4F0.field_14;
    *(struct_v3*)(o + 0x18C) = *(struct_v3*)(o + 0x38);
    *(int*)(o + 0x190) = *(int*)(sd + 0x7AC) + dword_80083C70[(unsigned short)a].y0 + b;
    *(int*)(o + 0x194) += -word_80084540[p[0x44 / 4] & 0xFFF] * dword_80083C70[(unsigned short)a].x0 / 4096 + word_80084540[(p[0x44 / 4] + 0x400) & 0xFFF] * dword_80083C70[(unsigned short)a].z0 / 4096;
    *(int*)(o + 0x18C) += word_80084540[(p[0x44 / 4] + 0x400) & 0xFFF] * dword_80083C70[(unsigned short)a].x0 / 4096 + word_80084540[p[0x44 / 4] & 0xFFF] * dword_80083C70[(unsigned short)a].z0 / 4096;
    p[0x17C / 4] = cameraState_8008D4F0.field_2E;
    p[0x180 / 4] = dword_80083C70[(unsigned short)a].field_8;
    sub_80038D64(o, p + 0x38 / 4);
}
extern CamOffset dword_80083C0C[];
typedef struct
{
    char pad_0[0x7AC];
    int y_7AC;
} SaveLevantY;
extern int dword_800A85B8;
extern int DistanceSquared3D_8003B80C(int* a, int* b);
// Matched
void sub_800390F4(void* p_, int arg1)
{
    int sel = 0;
    unsigned int i;
    unsigned int best;
    unsigned int dist;
    struct_v3 v;

    ((int*)p_)[3] = 0x1000;
    ((int*)p_)[1] &= ~8;
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
                    v = *(struct_v3*)((char*)p_ + 0x38);
            v.y = ((SaveLevantY*)&saveData_8008B570)->y_7AC + dword_80083C0C[sel].y1;
            v.z += -word_80084540[((int*)p_)[0x44 / 4] & 0xFFF] * dword_80083C0C[sel].x1 / 4096 + word_80084540[(((int*)p_)[0x44 / 4] + 0x400) & 0xFFF] * dword_80083C0C[sel].z1 / 4096;
            v.x += word_80084540[(((int*)p_)[0x44 / 4] + 0x400) & 0xFFF] * dword_80083C0C[sel].x1 / 4096 + word_80084540[((int*)p_)[0x44 / 4] & 0xFFF] * dword_80083C0C[sel].z1 / 4096;
            dist = DistanceSquared3D_8003B80C((int*)&cameraState_8008D4F0.field_14, (int*)&v);
            if (dist < best)
            {
                best = dist;
                sel = i;
            }
        }
    }
    *(struct_v3*)((char*)p_ + 0x1B0) = cameraState_8008D4F0.field_20;
    *(struct_v3*)((char*)p_ + 0x198) = *(struct_v3*)((char*)p_ + 0x38);
    *(int*)((char*)p_ + 0x19C) = ((SaveLevantY*)&saveData_8008B570)->y_7AC + dword_80083C0C[sel].y1;
    *(int*)((char*)p_ + 0x1A0) += -word_80084540[((int*)p_)[0x44 / 4] & 0xFFF] * dword_80083C0C[sel].x1 / 4096 + word_80084540[(((int*)p_)[0x44 / 4] + 0x400) & 0xFFF] * dword_80083C0C[sel].z1 / 4096;
    *(int*)((char*)p_ + 0x198) += word_80084540[(((int*)p_)[0x44 / 4] + 0x400) & 0xFFF] * dword_80083C0C[sel].x1 / 4096 + word_80084540[((int*)p_)[0x44 / 4] & 0xFFF] * dword_80083C0C[sel].z1 / 4096;
    *(struct_v3*)((char*)p_ + 0x1A4) = cameraState_8008D4F0.field_14;
    *(struct_v3*)((char*)p_ + 0x18C) = *(struct_v3*)((char*)p_ + 0x38);
    *(int*)((char*)p_ + 0x190) = ((SaveLevantY*)&saveData_8008B570)->y_7AC + dword_80083C0C[sel].y0;
    *(int*)((char*)p_ + 0x194) += -word_80084540[((int*)p_)[0x44 / 4] & 0xFFF] * dword_80083C0C[sel].x0 / 4096 + word_80084540[(((int*)p_)[0x44 / 4] + 0x400) & 0xFFF] * dword_80083C0C[sel].z0 / 4096;
    *(int*)((char*)p_ + 0x18C) += word_80084540[(((int*)p_)[0x44 / 4] + 0x400) & 0xFFF] * dword_80083C0C[sel].x0 / 4096 + word_80084540[((int*)p_)[0x44 / 4] & 0xFFF] * dword_80083C0C[sel].z0 / 4096;
    ((int*)p_)[0x17C / 4] = cameraState_8008D4F0.field_2E;
    ((int*)p_)[0x180 / 4] = dword_80083C0C[sel].field_8;
    sub_80038D64((char*)p_, (int*)p_ + 0x38 / 4);
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
void SaveCameraState_80039620(char* o)
{
    *(Block104*)(o + 0x48) = cameraState_8008D4F0;
    *(int*)(o + 0x184) = dword_8008B4F8;
    *(ShortPair*)(o + 0x14C) = dword_8008D474;
}
// Matched
void RestoreCameraState_80039698(int* a0)
{
    char* o = (char*)a0;
    cameraState_8008D4F0 = *(Block104*)(o + 0x48);
    dword_8008B4F8 = *(int*)(o + 0x184);
    dword_8008D474 = *(ShortPair*)(o + 0x14C);
}
typedef struct
{
    int a;
    int b;
} struct_pair8;
extern int sub_800AB4D8(int a);
// Matched
void sub_8003970C(int idx_, int* a5)
{
    int* p = cameraTask_8008D4A0[0x24 / 4];
    struct_pair8* t = (struct_pair8*)dword_800B1084;
    int* q;
    int r;
    p[0x1C / 4] = t[(short)idx_].b;
    p[0x218 / 4] = (int)a5;
    p[1] |= 8;
    r = (short)sub_800AB4D8(0xE);
    if (((settingsFlags_8008B58C & 0x200000) >> 21) == 1)
    {
        q = p + 0x1C8 / 4;
        p[0x1C8 / 4] = 0;
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
        q = p + 0x1C8 / 4;
        p[0x1C8 / 4] = 0;
        q[1] = r + 0x32;
        q[2] = r + 0x46;
        q[3] = r + 0x5A;
        q[4] = r + 0x6E;
        q[5] = r + 0x97;
        q[6] = r + 0xC8;
        q[7] = r + 0x10E;
        q[8] = -1;
    }
    p[0x1BC / 4] = (int)levantPos_8008BD18;
    p[0x1C0 / 4] = (int)levantPos_8008BD18 + 0xC;
}
// Matched
void sub_8003983C(int idx_, int* a5)
{
    int* p = cameraTask_8008D4A0[0x24 / 4];
    struct_pair8* t = (struct_pair8*)dword_800B1084;
    int* q;
    p[0x1C / 4] = t[(short)idx_].b;
    q = p + 0x1C8 / 4;
    p[0x218 / 4] = (int)a5;
    p[0x1C8 / 4] = 0;
    p[1] |= 8;
    q[1] = 0x28;
    q[2] = 0x50;
    q[3] = 0x78;
    q[4] = -1;
    p[0x1BC / 4] = (int)levantPos_8008BD18;
    p[0x1C0 / 4] = (int)levantPos_8008BD18 + 0xC;
}
typedef struct
{
    short x, y, w, h;
} ShortRect;
extern ShortRect stru_8008D420;
extern short* dword_8008D654;
extern signed char dword_80083BD4[];
extern DRAWENV drawEnv_8008D698[2];
#define CLAMP_HALF(v, lim) ((v) < -(lim) / 2 ? -(lim) / 2 : ((lim) / 2 < (v) ? (lim) / 2 : (v)))
// Matched
void sub_800398B4(int* p, void* q_)
{
    short* q = (short*)q_;
    DR_AREA tw;
    RECT r;
    short* sp;
    int s;
    int lx;
    int ly;

    if (!(p[1] & 4))
    {
        dword_8008D474.a = dword_8008D474.a - (q[0] - (stru_8008D420.x + stru_8008D420.w / 2));
        dword_8008D474.b = dword_8008D474.b - (q[1] - (stru_8008D420.y + stru_8008D420.h / 2));
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
        if (p[1] & 0x40)
        {
            if (p[1] & 0x80)
            {
                dword_8008D474.b += dword_80083BD4[*(short*)(p + 4)];
            }
            else
            {
                dword_8008D474.a += dword_80083BD4[*(short*)(p + 4)];
            }
            if ((unsigned short)++*(short*)(p + 4) >= 15)
            {
                p[1] &= ~0x40;
            }
        }
    }
    else if (p[1] & 0x40)
    {
        if (p[1] & 0x80)
        {
            dword_8008D474.b = dword_80083BD4[*(short*)(p + 4)];
        }
        else
        {
            dword_8008D474.a = dword_80083BD4[*(short*)(p + 4)];
        }
        if ((unsigned short)++*(short*)(p + 4) >= 15)
        {
            dword_8008D474.a = 0;
            dword_8008D474.b = 0;
            p[1] &= ~0x40;
        }
    }
}
extern SVECTOR word_8008D4C8;
extern void sub_8004D0E8(void);
// Matched
void sub_80039E14(void)
{
    VECTOR d;
    int a;
    D600_VEC->vx = cameraState_8008D4F0.field_14.x;
    D600_VEC->vy = cameraState_8008D4F0.field_14.y;
    D600_VEC->vz = cameraState_8008D4F0.field_14.z;
    d.vx = cameraState_8008D4F0.field_20.x - cameraState_8008D4F0.field_14.x;
    d.vy = cameraState_8008D4F0.field_20.y - cameraState_8008D4F0.field_14.y;
    d.vz = cameraState_8008D4F0.field_20.z - cameraState_8008D4F0.field_14.z;
    a = ratan2_8003B548(d.vx, d.vz);
    word_8008D4C8.vy = -a;
    word_8008D4C8.vx = ratan2_8003B548(d.vy, ISqrt_8003B918(LengthSquared2D_8003B8BC(d.vx, d.vz)));
    word_8008D4C8.vz = cameraState_8008D4F0.field_2C;
    sub_8004D0E8();
}
#if 0
// Not matched: target is a symbol at 0x8008D540 (inside stru_8008D534, data split lives in main.c); also needs its jump table via config/c_rodata.txt (dword_80074864 0x20)
void sub_80039ED8(int mode)
{
    switch ((short)(mode + 1))
    {
    case 0:
        stru_8008D534.v[0] = 0x800;
        stru_8008D534.v[1] = 0x800;
        stru_8008D534.v[2] = 0x800;
        break;
    case 1:
        stru_8008D534.v[0] = 0x1000;
        stru_8008D534.v[1] = 0;
        stru_8008D534.v[2] = 0x6B0;
        break;
    case 4:
        stru_8008D534.v[0] = 0x150;
        stru_8008D534.v[1] = 0;
        stru_8008D534.v[2] = 0x1000;
        break;
    case 3:
        stru_8008D534.v[0] = 0;
        stru_8008D534.v[1] = 0x1000;
        stru_8008D534.v[2] = 0x940;
        break;
    case 2:
        stru_8008D534.v[0] = 0xEB0;
        stru_8008D534.v[1] = 0x1000;
        stru_8008D534.v[2] = 0;
        break;
    }
}
#endif
INCLUDE_ASM(sub_80039ED8);
