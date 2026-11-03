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
#include "gte.h"

INCLUDE_DATA(dword_8008713C);
INCLUDE_DATA(dword_80087140);
INCLUDE_DATA(dword_80087144);

#define ABS_8004B0A8(x) ((x) < 0 ? -(x) : (x))
// Matched
void sub_8004B0A8(VECTOR* v, MATRIX* m)
{
    VECTOR t;
    VECTOR u;
    VECTOR n0;
    VECTOR n1;
    VECTOR n2;
    int ax;
    int ay;
    int az;
    sub_8003B684((int*)v);
    VectorNormal(v, &n0);
    m->m[0][0] = n0.vx;
    m->m[1][0] = n0.vy;
    m->m[2][0] = n0.vz;
    ay = ABS_8004B0A8(n0.vy);
    ax = ABS_8004B0A8(n0.vx);
    if (ax < ay)
    {
        az = ABS_8004B0A8(n0.vz);
        if (az < ax)
        {
            t.vx = n0.vy;
            t.vy = -n0.vx;
            if (n0.vz)
            {
                t.vz = -(n0.vx * t.vx + n0.vy * t.vy) / n0.vz;
            }
            else
            {
                t.vz = 0;
            }
        }
        else
        {
            if (n0.vy)
            {
                t.vz = n0.vy;
                t.vy = -n0.vz;
            }
            else
            {
                t.vz = 0;
                t.vy = n0.vz;
            }
            if (n0.vx)
            {
                t.vx = -(n0.vz * t.vz + n0.vy * t.vy) / n0.vx;
            }
            else
            {
                t.vx = 0;
            }
        }
    }
    else
    {
        az = ABS_8004B0A8(n0.vz);
        if (az < ay)
        {
            t.vx = n0.vy;
            t.vy = -n0.vx;
            if (n0.vz)
            {
                t.vz = -(n0.vx * t.vx + n0.vy * t.vy) / n0.vz;
            }
            else
            {
                t.vz = 0;
            }
        }
        else
        {
            if (n0.vz)
            {
                t.vx = n0.vz;
                t.vz = -n0.vx;
            }
            else
            {
                t.vx = 0;
                t.vz = n0.vx;
            }
            if (n0.vy)
            {
                t.vy = -(n0.vx * t.vx + n0.vz * t.vz) / n0.vy;
            }
            else
            {
                t.vy = 0;
            }
        }
    }
    sub_8003B684((int*)&t);
    VectorNormal(&t, &n1);
    m->m[0][1] = n1.vx;
    m->m[1][1] = n1.vy;
    m->m[2][1] = n1.vz;
    OuterProduct12(&n0, &n1, &u);
    sub_8003B684((int*)&u);
    VectorNormal(&u, &n2);
    m->m[0][2] = n2.vx;
    m->m[1][2] = n2.vy;
    m->m[2][2] = n2.vz;
}
INCLUDE_ASM(sub_8004B320);
INCLUDE_ASM(sub_8004B590);
INCLUDE_ASM(sub_8004B844);
INCLUDE_ASM(sub_8004BB9C);
INCLUDE_ASM(sub_8004BFA8);
INCLUDE_ASM(sub_8004C21C);
INCLUDE_ASM(sub_8004C4F0);
INCLUDE_ASM(sub_8004C7BC);
extern unsigned char byte_8008D460[3]; // back colour
extern MATRIX dword_80087114;            // light matrix
extern MATRIX dword_80087134;            // light colour matrix
extern SVECTOR word_8008D4C8;
// Matched
void sub_8004D0E8(void)
{
    MATRIX* m;
    gte_SetBackColor(byte_8008D460[0], byte_8008D460[1], byte_8008D460[2]);
    gte_SetColorMatrix(&dword_80087134);
    gte_SetLightMatrix(&dword_80087114);
    RotMatrixZXY_8004668C(&word_8008D4C8, (MATRIX*)getScratchAddr(0));
    m = (MATRIX*)getScratchAddr(0);
    m->t[2] = 0;
    m->t[1] = 0;
    m->t[0] = 0;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);
}
extern void sub_80044D0C(struct FtgObject* obj, unsigned long* ot, void* pos, void* rot, void* cam, int flags, void* scale, int a7);

// Matched
void sub_8004D1EC(struct FtgObject* a0, unsigned long* a1, void* a2, void* a3, void* a4, int a5, void* a6)
{
    sub_80044D0C(a0, a1, a2, a3, a4, a5, a6, 0);
}
typedef struct
{
    char pad_0[0x14];
    unsigned short* field_14;
} struct_tbl14;

// Matched
void sub_8004D224(unsigned short* out, struct_tbl14* s, int idx)
{
    if (idx == 0)
    {
        out[0] = 0;
        out[1] = 0;
        out[2] = 0;
        return;
    }
    out[0] = s->field_14[idx * 3];
    out[1] = s->field_14[idx * 3 + 1];
    out[2] = s->field_14[idx * 3 + 2];
}
typedef struct
{
    int pad_0;
    int n;
    char pad_8[0x10];
    short* field_18;
} struct_tbl18;
// Matched
void sub_8004D288(int* out, struct_tbl18* s, int k)
{
    int i = k * (s->n + 2);
    out[0] = s->field_18[i * 3];
    out[1] = s->field_18[i * 3 + 1];
    out[2] = s->field_18[i * 3 + 2];
}
// Matched
void sub_8004D2EC(short* out, struct_tbl18* s, int k)
{
    int i = k * (s->n + 2) + 1;
    out[0] = s->field_18[i * 3];
    out[1] = s->field_18[i * 3 + 1];
    out[2] = s->field_18[i * 3 + 2];
}
// Matched
void sub_8004D354(short* out, struct_tbl18* s, int j, int k)
{
    int i;
    int t;
    if (j == 0)
    {
        out[0] = 0;
        out[1] = 0;
        out[2] = 0;
        return;
    }
    t = j + 2;
    i = k * (s->n + 2) + t;
    out[0] = s->field_18[i * 3];
    out[1] = s->field_18[i * 3 + 1];
    out[2] = s->field_18[i * 3 + 2];
}
/* 4096-entry sine table at 0x80084540 (inside the asc_80084350 data chunk) */
extern short asc_80084350[];
#define SIN_TABLE (asc_80084350 + 0xF8)
// Matched
void RotMatrixXYZ_8004D3D8(SVECTOR* r, MATRIX* m)
{
    int cy = SIN_TABLE[(r->vy + 0x400) & 0xFFF];
    int cz = SIN_TABLE[(r->vz + 0x400) & 0xFFF];
    int sy = SIN_TABLE[r->vy & 0xFFF];
    int cx = SIN_TABLE[(r->vx + 0x400) & 0xFFF];
    int sz = SIN_TABLE[r->vz & 0xFFF];
    int sx = SIN_TABLE[r->vx & 0xFFF];
    int a;
    int b;
    m->m[0][2] = sy;
    m->m[0][0] = (cz * cy) >> 12;
    a = (cz * -sy) >> 12;
    m->m[1][0] = ((sz * cx) >> 12) - ((a * sx) >> 12);
    m->m[2][0] = ((sz * sx) >> 12) + ((a * cx) >> 12);
    m->m[0][1] = -(sz * cy) >> 12;
    b = (sz * -sy) >> 12;
    m->m[1][1] = ((cz * cx) >> 12) + ((b * sx) >> 12);
    m->m[1][2] = -(cy * sx) >> 12;
    m->m[2][2] = (cy * cx) >> 12;
    m->m[2][1] = ((cz * sx) >> 12) - ((b * cx) >> 12);
}
// Matched
void RotMatrixZYX_8004D5CC(SVECTOR* r, MATRIX* m)
{
    int cz = SIN_TABLE[(r->vz + 0x400) & 0xFFF];
    int cy = SIN_TABLE[(r->vy + 0x400) & 0xFFF];
    int sy = SIN_TABLE[r->vy & 0xFFF];
    int sz = SIN_TABLE[r->vz & 0xFFF];
    int cx = SIN_TABLE[(r->vx + 0x400) & 0xFFF];
    int sx = SIN_TABLE[r->vx & 0xFFF];
    int a;
    int b;
    m->m[2][0] = -sy;
    a = (cz * sy) >> 12;
    b = (sz * sy) >> 12;
    m->m[0][0] = (cz * cy) >> 12;
    m->m[1][0] = (sz * cy) >> 12;
    m->m[0][1] = -((sz * cx) >> 12) + ((a * sx) >> 12);
    m->m[1][1] = ((cz * cx) >> 12) + ((b * sx) >> 12);
    m->m[2][1] = (cy * sx) >> 12;
    m->m[0][2] = ((sz * sx) >> 12) + ((a * cx) >> 12);
    m->m[2][2] = (cy * cx) >> 12;
    m->m[1][2] = -((cz * sx) >> 12) + ((b * cx) >> 12);
}
// Matched
void LerpSVector_8004D7A8(SVECTOR* a, SVECTOR* b, SVECTOR* out, int t)
{
    out->vx = a->vx + (b->vx - a->vx) * t / 4096;
    out->vy = a->vy + (b->vy - a->vy) * t / 4096;
    out->vz = a->vz + (b->vz - a->vz) * t / 4096;
}
// Matched
void LerpAngles_8004D848(SVECTOR* a, SVECTOR* b, SVECTOR* out, int t)
{
    int d;
    d = (b->vx - a->vx) & 0xFFF;
    if (d >= 0x800)
    {
        d -= 0x1000;
    }
    out->vx = (a->vx + d * t / 4096) & 0xFFF;
    d = (b->vy - a->vy) & 0xFFF;
    if (d >= 0x800)
    {
        d -= 0x1000;
    }
    out->vy = (a->vy + d * t / 4096) & 0xFFF;
    d = (b->vz - a->vz) & 0xFFF;
    if (d >= 0x800)
    {
        d -= 0x1000;
    }
    out->vz = (a->vz + d * t / 4096) & 0xFFF;
}
