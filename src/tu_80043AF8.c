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


// Matched
EventEntry* AllocEventEntry_80043AF8(EventNode* n)
{
    int i;
    int count = n->count;
    for (i = 0; i < count; i++)
    {
        EventEntry* e = &n->entry;
        if (!(e->flags & 1))
        {
            return e;
        }
        n = n->next;
    }
    return 0;
}
// Matched
void StopAllEventEntries_80043B40(EventNode* p)
{
    int n = p->count;
    int i;
    for (i = 0; i < n; i++)
    {
        if (p->entry.flags & 1)
        {
            p->entry.flags = (p->entry.flags & ~1) | 0x8000;
        }
        p = p->next;
    }
}
INCLUDE_ASM(sub_80043B8C);
INCLUDE_ASM(sub_80043DE0);
INCLUDE_ASM(sub_80044010);
INCLUDE_ASM(sub_80044D0C);
INCLUDE_ASM(sub_800451BC);
INCLUDE_ASM(sub_80045534);
INCLUDE_ASM(sub_800459E4);
INCLUDE_ASM(sub_80045E48);
INCLUDE_ASM(sub_80046248);
/* 4096-entry sine table at 0x80084540 (inside the asc_80084350 data chunk) */
extern short asc_80084350[];
#define SIN_TABLE (asc_80084350 + 0xF8)
// Matched
void RotMatrixZXY_8004668C(SVECTOR* r, MATRIX* m)
{
    int cx = SIN_TABLE[(r->vx + 0x400) & 0xFFF];
    int cz = SIN_TABLE[(r->vz + 0x400) & 0xFFF];
    int sx = SIN_TABLE[r->vx & 0xFFF];
    int sz = SIN_TABLE[r->vz & 0xFFF];
    int cy = SIN_TABLE[(r->vy + 0x400) & 0xFFF];
    int sy = SIN_TABLE[r->vy & 0xFFF];
    int a;
    int b;
    m->m[2][1] = sx;
    b = (cz * sx) >> 12;
    a = (sz * sx) >> 12;
    m->m[0][0] = ((cz * cy) >> 12) - ((a * sy) >> 12);
    m->m[1][0] = ((sz * cy) >> 12) + ((b * sy) >> 12);
    m->m[2][0] = -(cx * sy) >> 12;
    m->m[0][1] = -(sz * cx) >> 12;
    m->m[1][1] = (cz * cx) >> 12;
    m->m[0][2] = ((cz * sy) >> 12) + ((a * cy) >> 12);
    m->m[2][2] = (cx * cy) >> 12;
    m->m[1][2] = ((sz * sy) >> 12) - ((b * cy) >> 12);
}
// Matched
void RotMatrixYXZ_80046874(SVECTOR* r, MATRIX* m)
{
    int cy = SIN_TABLE[(r->vy + 0x400) & 0xFFF];
    int cx = SIN_TABLE[(r->vx + 0x400) & 0xFFF];
    int sx = SIN_TABLE[r->vx & 0xFFF];
    int sy = SIN_TABLE[r->vy & 0xFFF];
    int cz = SIN_TABLE[(r->vz + 0x400) & 0xFFF];
    int sz = SIN_TABLE[r->vz & 0xFFF];
    int a;
    int b;
    m->m[1][2] = -sx;
    b = (cy * sx) >> 12;
    a = (sy * sx) >> 12;
    m->m[0][0] = ((cy * cz) >> 12) + ((a * sz) >> 12);
    m->m[1][0] = (cx * sz) >> 12;
    m->m[2][0] = -((sy * cz) >> 12) + ((b * sz) >> 12);
    m->m[0][1] = -((cy * sz) >> 12) + ((a * cz) >> 12);
    m->m[1][1] = (cx * cz) >> 12;
    m->m[0][2] = (sy * cx) >> 12;
    m->m[2][2] = (cy * cx) >> 12;
    m->m[2][1] = ((sy * sz) >> 12) + ((b * cz) >> 12);
}
INCLUDE_ASM(sub_80046A58);
INCLUDE_ASM(sub_80047E28);
typedef struct
{
    short x;
    short y;
    short z;
} Vec3s;

typedef struct
{
    char pad[0x14];
    Vec3s* pos;
    Vec3s* rot;
} AnimPose;

typedef struct
{
    short parent;
    unsigned char idx;
    char pad[5];
} AnimBone;

typedef struct
{
    char pad[0xC];
    AnimBone* bones;
    SVECTOR* base;
} AnimSkel;

extern SVECTOR dword_80098690[];

/* inlined helpers: the original keeps the bone index in a copy of the argument */
static inline void GetRot(SVECTOR* o, AnimPose* p, int j)
{
    int k;
    if (j == 0)
    {
        o->vx = 0;
        o->vy = 0;
        o->vz = 0;
    }
    else
    {
        k = j + 2;
        o->vx = p->rot[k].x;
        o->vy = p->rot[k].y;
        o->vz = p->rot[k].z;
    }
}

static inline void GetPos(SVECTOR* o, AnimPose* p, int j)
{
    if (j == 0)
    {
        o->vx = 0;
        o->vy = 0;
        o->vz = 0;
    }
    else
    {
        o->vx = p->pos[j].x;
        o->vy = p->pos[j].y;
        o->vz = p->pos[j].z;
    }
}

// Matched
void sub_8004A4FC(AnimSkel* sk, SVECTOR* v1, AnimPose* a1, int t1, SVECTOR* v2, AnimPose* a2, int t2,
                  AnimPose* r0, AnimPose* p0, AnimPose* out, SVECTOR* vout)
{
    SVECTOR s;
    SVECTOR b0;
    SVECTOR b1;
    SVECTOR b2;
    SVECTOR s2;
    SVECTOR q0;
    SVECTOR q1;
    SVECTOR q2;
    SVECTOR* d;
    int i;
    int k;
    int n;
    int idx;

    for (i = 0; sk->bones[i].parent >= 0; i++)
    {
        n = sk->bones[i].parent + 2;
        GetRot(&b0, r0, sk->bones[i].idx);
        GetRot(&b1, a1, sk->bones[i].idx);
        GetRot(&b2, a2, sk->bones[i].idx);

        k = (b1.vx - b0.vx) & 0xFFF;
        if (k >= 0x800)
            k -= 0x1000;
        s.vx = (b0.vx + k * t1 / 4096) & 0xFFF;
        k = (b1.vy - b0.vy) & 0xFFF;
        if (k >= 0x800)
            k -= 0x1000;
        s.vy = (b0.vy + k * t1 / 4096) & 0xFFF;
        k = (b1.vz - b0.vz) & 0xFFF;
        if (k >= 0x800)
            k -= 0x1000;
        s.vz = (b0.vz + k * t1 / 4096) & 0xFFF;
        s.vx = s.vx - b0.vx;
        s.vy = 0;
        s.vz = 0;

        k = (b2.vx - b0.vx) & 0xFFF;
        if (k >= 0x800)
            k -= 0x1000;
        s2.vx = (b0.vx + k * t2 / 4096) & 0xFFF;
        k = (b2.vy - b0.vy) & 0xFFF;
        if (k >= 0x800)
            k -= 0x1000;
        s2.vy = (b0.vy + k * t2 / 4096) & 0xFFF;
        k = (b2.vz - b0.vz) & 0xFFF;
        if (k >= 0x800)
            k -= 0x1000;
        s2.vz = (b0.vz + k * t2 / 4096) & 0xFFF;
        s2.vy = 0;
        s2.vz = 0;
        s2.vx = s2.vx - b0.vx;

        idx = sk->bones[i].idx + 2;
        out->rot[idx].x = s.vx + s2.vx;
        out->rot[idx].y = 0;
        out->rot[idx].z = 0;

        if (vout != 0)
        {
            vout[i].vx = sk->base[i].vx + (v1[i].vx - sk->base[i].vx) * t1 / 4096 + (v2[i].vx - sk->base[i].vx) * t2 / 4096;
            vout[i].vy = sk->base[i].vy + (v1[i].vy - sk->base[i].vy) * t1 / 4096 + (v2[i].vy - sk->base[i].vy) * t2 / 4096;
            vout[i].vz = sk->base[i].vz + (v1[i].vz - sk->base[i].vz) * t1 / 4096 + (v2[i].vz - sk->base[i].vz) * t2 / 4096;
        }

        GetPos(&q0, p0, sk->bones[i].idx);
        GetPos(&q1, a1, sk->bones[i].idx);
        GetPos(&q2, a2, sk->bones[i].idx);
        d = &dword_80098690[n];
        d->vx = q0.vx + (q1.vx - q0.vx) * t1 / 4096 + (q2.vx - q0.vx) * t2 / 4096;
        d->vy = q0.vy + (q1.vy - q0.vy) * t1 / 4096 + (q2.vy - q0.vy) * t2 / 4096;
        d->vz = q0.vz + (q1.vz - q0.vz) * t1 / 4096 + (q2.vz - q0.vz) * t2 / 4096;
        if (i == 1)
        {
            d->vy -= q0.vy;
        }
        idx = sk->bones[i].idx;
        out->pos[idx].x = d->vx;
        out->pos[idx].y = d->vy;
        out->pos[idx].z = d->vz;
    }
}
// Matched
void sub_8004AD44(MATRIX* in, VECTOR* out)
{
    MATRIX m;
    int c[9];
    int v[6];
    VECTOR r;
    int i;
    int j;
    int max;
    int idx;

    m.m[0][0] = in->m[0][0] - 0x1000;
    m.m[0][1] = in->m[0][1];
    m.m[0][2] = in->m[0][2];
    m.m[1][0] = in->m[1][0];
    m.m[1][1] = in->m[1][1] - 0x1000;
    m.m[1][2] = in->m[1][2];
    m.m[2][0] = in->m[2][0];
    m.m[2][1] = in->m[2][1];
    m.m[2][2] = in->m[2][2] - 0x1000;
    c[0] = m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1];
    c[1] = m.m[1][0] * m.m[2][2] - m.m[0][2] * m.m[2][0];
    c[2] = m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0];
    c[3] = m.m[0][1] * m.m[2][2] - m.m[0][2] * m.m[2][1];
    c[4] = m.m[0][0] * m.m[2][2] - m.m[0][2] * m.m[2][0];
    c[5] = m.m[0][0] * m.m[2][1] - m.m[0][1] * m.m[2][0];
    c[6] = m.m[0][1] * m.m[2][2] - m.m[0][2] * m.m[2][1];
    c[7] = m.m[0][0] * m.m[1][2] - m.m[0][2] * m.m[1][0];
    c[8] = m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0];
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (c[i * 3 + j] < 0)
            {
                c[i * 3 + j] = -c[i * 3 + j];
            }
        }
    }
    idx = 0;
    max = c[0];
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (max < c[i * 3 + j])
            {
                idx = i * 3 + j;
                max = c[i * 3 + j];
            }
        }
    }
    switch (idx)
    {
    case 6:
    case 7:
    case 8:
        v[0] = m.m[0][0];
        v[1] = m.m[0][1];
        v[2] = m.m[0][2];
        v[3] = m.m[1][0];
        v[4] = m.m[1][1];
        v[5] = m.m[1][2];
        break;
    case 3:
    case 4:
    case 5:
        v[0] = m.m[0][0];
        v[1] = m.m[0][1];
        v[2] = m.m[0][2];
        v[3] = m.m[2][0];
        v[4] = m.m[2][1];
        v[5] = m.m[2][2];
        break;
    case 0:
    case 1:
    case 2:
        v[0] = m.m[1][0];
        v[1] = m.m[1][1];
        v[2] = m.m[1][2];
        v[3] = m.m[2][0];
        v[4] = m.m[2][1];
        v[5] = m.m[2][2];
        break;
    }
    OuterProduct12((VECTOR*)&v[0], (VECTOR*)&v[3], &r);
    VectorNormal(&r, out);
}

INCLUDE_DATA(dword_80096120);
INCLUDE_DATA(dword_80096130);
INCLUDE_DATA(dword_80096628);
