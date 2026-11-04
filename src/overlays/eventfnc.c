// EVENTFNC.BIN, source file 1 of 2
#include "eventfnc.h"
#include "actor.h"

INCLUDE_OVERLAY_ASM(eventfnc, dword_800B6D00);

#if 0
// Not matched: FindLevantMesh_800B80C8 is inlined here; the original keeps its result in $s3 and sets it to 1 before
// the mesh loop (0 on exhaustion), this C returns it in $v0, one saved register and one word short
int sub_800B6DD4(EvEntEventfnc* o)
{
    EvQuadEventfnc v[4];
    int n[4];
    int ret;
    int i;
    int found;
    MapVtx* vt;
    EvQuadEventfnc* q;
    EvQuadEventfnc* q2;
    int d;
    ret = 0;
    i = 0;
    sub_800B82C8(&levantPos_8008BD18.pos.x, (int*)&o->pos_48, dword_8008B500.ents_14,
                 dword_8008B500.entFlags_18, dword_8008B500.nEnts_10);
    o->f8C_8C = -1;
    o->f88_88 = -1;
    for (;;)
    {
        found = EvFindLevantMesh(o);
        if (found)
        {
            break;
        }
        if (i >= 2)
        {
            if (FindDuplicatePoint_800B8028(&levantPos_8008BD18.pos.x, v))
            {
                return ret;
            }
            printf(aAssertionFaile_800B6D04, aColiC_800B6D2C, 153);
            exit(1);
        }
        sub_800B8220(&levantPos_8008BD18.pos.x, (int)&o->pos_48, (int)&dword_8008B500.meshes_C[o->f84_84], &o->f88_88, &o->f8C_8C, n);
        vt = dword_8008B500.meshes_C[o->f84_84].tris_4[o->f88_88].v_0;
        q = (EvQuadEventfnc*)(i * 16 + (int)v); // &v[i * 2]; that form allocates registers differently
        q->x_0 = vt[o->f8C_8C % 3].x_0;
        q->y_2 = vt[o->f8C_8C % 3].y_2;
        q->z_4 = vt[o->f8C_8C % 3].z_4;
        q2 = q + 1;
        q2->x_0 = vt[(o->f8C_8C + 1) % 3].x_0;
        q2->y_2 = vt[(o->f8C_8C + 1) % 3].y_2;
        q2->z_4 = vt[(o->f8C_8C + 1) % 3].z_4;
        i++;
    }
    GetTriHeight_800B83E4(&levantPos_8008BD18.pos.x, &dword_8008B500.meshes_C[o->f84_84], o->f80_80);
    if (o->f88_88 == -1)
    {
        return ret;
    }
    if (o->f8C_8C == -1)
    {
        return ret;
    }
    d = ((unsigned short)levantPos_8008BD18.rot.vy - ((int (*)(long, long))ratan2_8003B548)(n[0], n[2])) & 0xFFF;
    if (d > 0xC00 || (d > 0x400 && d < 0x800))
    {
        ret = 1;
    }
    else
    {
        ret = -1;
    }
    return ret;
}
#endif

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B6DD4);

int CollideWithMap_800B716C(EvVecEventfnc* pos, int* a1, SVECTOR* rot)
{
    EvQuadEventfnc v[4];
    int n[4];
    int tri;
    int t0;
    int t1;
    int i;
    int d;
    MapVtx* vt;
    EvQuadEventfnc* q;
    EvQuadEventfnc* q2;
    if (!sub_800B82C8((int*)pos, a1, dword_8008B500.ents_30, dword_8008B500.entFlags_34, dword_8008B500.nEnts_2C))
    {
        return 3;
    }
    t1 = -1;
    t0 = -1;
    i = 0;
    for (;;)
    {
        if (EvFindTri(&tri, &dword_8008B500, pos))
        {
            break;
        }
        if (i >= 2)
        {
            if (FindDuplicatePoint_800B8028((int*)pos, v))
            {
                return 3;
            }
            printf(aAssertionFaile_800B6D04, aColiC_800B6D2C, 255);
            exit(1);
        }
        sub_800B8220((int*)pos, (int)a1, (int)dword_8008B500.mesh_28, &t0, &t1, n);
        vt = dword_8008B500.mesh_28->tris_4[t0].v_0;
        q = (EvQuadEventfnc*)(i * 16 + (int)v); // &v[i * 2]; that form allocates registers differently
        q->x_0 = vt[t1 % 3].x_0;
        q->y_2 = vt[t1 % 3].y_2;
        q->z_4 = vt[t1 % 3].z_4;
        q2 = q + 1;
        q2->x_0 = vt[(t1 + 1) % 3].x_0;
        q2->y_2 = vt[(t1 + 1) % 3].y_2;
        q2->z_4 = vt[(t1 + 1) % 3].z_4;
        i++;
    }
    GetTriHeight_800B83E4((int*)pos, dword_8008B500.mesh_28, tri);
    if (i == 2)
    {
        return 3;
    }
    if (t0 == -1)
    {
        return 0;
    }
    if (t1 == -1)
    {
        return 0;
    }
    d = ((unsigned short)rot->vy - ((int (*)(long, long))ratan2_8003B548)(n[0], n[2])) & 0xFFF;
    if (d > 0xC00 || (d > 0x400 && d < 0x800))
    {
        return 1;
    }
    return 2;
}

// Matched
// clears the pad_6 edge flag of every vertex, then sets it to -1 where the edge (v, v+1) of a triangle is shared
// (same x/z, either direction) with another triangle of the same mesh. The vertices are re-indexed in every test
// (a named pointer to t's vertex gets its loads hoisted out of the b loop)
void MarkSharedEdges_800B73C0(MapMesh* m, int n)
{
    int i;
    int j;
    int k;
    int a;
    int b;
    MapTri* t;
    MapTri* u;
    for (i = 0; i < n; i++)
    {
        int e;
        int f;
        MapTri* r;
        for (f = 0; f < m[i].nTris_0; f++)
        {
            r = &m[i].tris_4[f];
            for (e = 0; e < 3; e++)
            {
                (r->v_0 + e % 3)->pad_6 = 0;
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m[i].nTris_0; j++)
        {
            for (k = 0; k < m[i].nTris_0; k++)
            {
                if (j == k)
                {
                    continue;
                }
                t = &m[i].tris_4[j];
                u = &m[i].tris_4[k];
                for (a = 0; a < 3; a++)
                {
                    for (b = 0; b < 3; b++)
                    {
                        if (((t->v_0 + a % 3)->x_0 == (u->v_0 + b % 3)->x_0 && (t->v_0 + a % 3)->z_4 == (u->v_0 + b % 3)->z_4 &&
                             (t->v_0 + (a + 1) % 3)->x_0 == (u->v_0 + (b + 1) % 3)->x_0 && (t->v_0 + (a + 1) % 3)->z_4 == (u->v_0 + (b + 1) % 3)->z_4) ||
                            ((t->v_0 + a % 3)->x_0 == (u->v_0 + (b + 1) % 3)->x_0 && (t->v_0 + a % 3)->z_4 == (u->v_0 + (b + 1) % 3)->z_4 &&
                             (t->v_0 + (a + 1) % 3)->x_0 == (u->v_0 + b % 3)->x_0 && (t->v_0 + (a + 1) % 3)->z_4 == (u->v_0 + b % 3)->z_4))
                        {
                            (t->v_0 + a % 3)->pad_6 = -1;
                        }
                    }
                }
            }
        }
    }
}

int FindTriAtXZ_800B76B8(MapMesh* m, EvVecEventfnc* p)
{
    VECTOR e;
    VECTOR r;
    int i;
    int minx;
    int maxx;
    int minz;
    int maxz;
    for (i = 0; i < m->nTris_0; i++)
    {
        if (m->tris_4[i].v_0[0].x_0 > m->tris_4[i].v_0[1].x_0)
        {
            maxx = m->tris_4[i].v_0[0].x_0;
            minx = m->tris_4[i].v_0[1].x_0;
        }
        else
        {
            minx = m->tris_4[i].v_0[0].x_0;
            maxx = m->tris_4[i].v_0[1].x_0;
        }
        if (maxx < m->tris_4[i].v_0[2].x_0)
        {
            maxx = m->tris_4[i].v_0[2].x_0;
        }
        else if (m->tris_4[i].v_0[2].x_0 < minx)
        {
            minx = m->tris_4[i].v_0[2].x_0;
        }
        if (m->tris_4[i].v_0[0].z_4 > m->tris_4[i].v_0[1].z_4)
        {
            maxz = m->tris_4[i].v_0[0].z_4;
            minz = m->tris_4[i].v_0[1].z_4;
        }
        else
        {
            minz = m->tris_4[i].v_0[0].z_4;
            maxz = m->tris_4[i].v_0[1].z_4;
        }
        if (maxz < m->tris_4[i].v_0[2].z_4)
        {
            maxz = m->tris_4[i].v_0[2].z_4;
        }
        else if (m->tris_4[i].v_0[2].z_4 < minz)
        {
            minz = m->tris_4[i].v_0[2].z_4;
        }
        if (p->x_0 < minx || maxx < p->x_0 || p->z_8 < minz || maxz < p->z_8)
        {
            continue;
        }
        e.vx = m->tris_4[i].v_0[1].x_0 - m->tris_4[i].v_0[0].x_0;
        e.vz = m->tris_4[i].v_0[1].z_4 - m->tris_4[i].v_0[0].z_4;
        r.vx = p->x_0 - m->tris_4[i].v_0[0].x_0;
        r.vz = p->z_8 - m->tris_4[i].v_0[0].z_4;
        if (e.vx * r.vz - e.vz * r.vx > 0)
        {
            continue;
        }
        e.vx = m->tris_4[i].v_0[2].x_0 - m->tris_4[i].v_0[1].x_0;
        e.vz = m->tris_4[i].v_0[2].z_4 - m->tris_4[i].v_0[1].z_4;
        r.vx = p->x_0 - m->tris_4[i].v_0[1].x_0;
        r.vz = p->z_8 - m->tris_4[i].v_0[1].z_4;
        if (e.vx * r.vz - e.vz * r.vx > 0)
        {
            continue;
        }
        e.vx = m->tris_4[i].v_0[0].x_0 - m->tris_4[i].v_0[2].x_0;
        e.vz = m->tris_4[i].v_0[0].z_4 - m->tris_4[i].v_0[2].z_4;
        r.vx = p->x_0 - m->tris_4[i].v_0[2].x_0;
        r.vz = p->z_8 - m->tris_4[i].v_0[2].z_4;
        if (e.vx * r.vz - e.vz * r.vx <= 0)
        {
            return i;
        }
    }
    return -1;
}

// Matched
// finds the first unshared edge (pad_6 == 0) of mesh m crossed by the segment p-q in x/z and returns it in
// *tri / *edge, unless it is the one already there
void sub_800B79E0(MapMesh* m, int* p, int* q, int* tri, int* edge)
{
    VECTOR e;
    VECTOR r;
    VECTOR s;
    MapTri* t;
    int i;
    int k;
    int minx;
    int maxx;
    int emin;
    int emax;
    int sg;
    for (i = 0; i < m->nTris_0; i++)
    {
        t = &m->tris_4[i];
        for (k = 0; k < 3; k++)
        {
            if ((t->v_0 + k)->pad_6 != 0)
            {
                continue;
            }
            if (p[0] > q[0])
            {
                minx = q[0];
                maxx = p[0];
            }
            else
            {
                minx = p[0];
                maxx = q[0];
            }
            if ((t->v_0 + k % 3)->x_0 > (t->v_0 + (k + 1) % 3)->x_0)
            {
                emin = (t->v_0 + (k + 1) % 3)->x_0;
                emax = (t->v_0 + k % 3)->x_0;
            }
            else
            {
                emin = (t->v_0 + k % 3)->x_0;
                emax = (t->v_0 + (k + 1) % 3)->x_0;
            }
            if (emax < minx || maxx < emin)
            {
                continue;
            }
            if (p[2] > q[2])
            {
                minx = q[2];
                maxx = p[2];
            }
            else
            {
                minx = p[2];
                maxx = q[2];
            }
            if ((t->v_0 + k % 3)->z_4 > (t->v_0 + (k + 1) % 3)->z_4)
            {
                emin = (t->v_0 + (k + 1) % 3)->z_4;
                emax = (t->v_0 + k % 3)->z_4;
            }
            else
            {
                emin = (t->v_0 + k % 3)->z_4;
                emax = (t->v_0 + (k + 1) % 3)->z_4;
            }
            if (emax < minx || maxx < emin)
            {
                continue;
            }
            e.vx = (t->v_0 + (k + 1) % 3)->x_0 - (t->v_0 + k % 3)->x_0;
            e.vz = (t->v_0 + (k + 1) % 3)->z_4 - (t->v_0 + k % 3)->z_4;
            r.vx = p[0] - (t->v_0 + k % 3)->x_0;
            r.vz = p[2] - (t->v_0 + k % 3)->z_4;
            s.vx = q[0] - (t->v_0 + k % 3)->x_0;
            s.vz = q[2] - (t->v_0 + k % 3)->z_4;
            if (e.vx * r.vz - e.vz * r.vx <= 0)
            {
                continue;
            }
            if (e.vx * s.vz - e.vz * s.vx > 0)
            {
                continue;
            }
            e.vx = p[0] - q[0];
            e.vz = p[2] - q[2];
            r.vx = (t->v_0 + k % 3)->x_0 - q[0];
            r.vz = (t->v_0 + k % 3)->z_4 - q[2];
            s.vx = (t->v_0 + (k + 1) % 3)->x_0 - q[0];
            s.vz = (t->v_0 + (k + 1) % 3)->z_4 - q[2];
            sg = Sign_8003B664(e.vx * r.vz - e.vz * r.vx);
            if (sg * Sign_8003B664(e.vx * s.vz - e.vz * s.vx) > 0)
            {
                continue;
            }
            if (*tri != i || *edge != k)
            {
                *tri = i;
                *edge = k;
                return;
            }
        }
    }
}

void SlideAlongEdge_800B7E40(int* p, int a, int b, int c, int* out)
{
    int t = (int)&((MapMesh*)a)->tris_4[b];
    MapVtx* v0 = (MapVtx*)(((c + 1) % 3) * 8 + t);
    MapVtx* v1 = (MapVtx*)((c % 3) * 8 + t);
    int d[3];
    int r[3];
    int len;
    int k;
    d[0] = v0->x_0 - v1->x_0;
    d[1] = v0->y_2 - v1->y_2;
    d[2] = v0->z_4 - v1->z_4;
    r[0] = p[0] - v1->x_0;
    r[1] = p[1] - v1->y_2;
    r[2] = p[2] - v1->z_4;
    d[1] = 0;
    len = ISqrt_8003B918(d[0] * d[0] + d[2] * d[2]);
    d[0] = (d[0] << 12) / len;
    d[2] = (d[2] << 12) / len;
    k = (d[0] * r[0] + d[2] * r[2]) / 4096;
    p[0] = v1->x_0 + k * d[0] / 4096;
    p[2] = v1->z_4 + k * d[2] / 4096;
    out[0] = d[0];
    out[1] = 0;
    out[2] = d[2];
}

int FindDuplicatePoint_800B8028(int* out, EvQuadEventfnc* v)
{
    int i;
    int j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (i != j && v[i].x_0 == v[j].x_0 && v[i].y_2 == v[j].y_2 && v[i].z_4 == v[j].z_4)
            {
                out[0] = v[i].x_0;
                out[1] = v[i].y_2;
                out[2] = v[i].z_4;
                return 1;
            }
        }
    }
    return 0;
}

int FindLevantMesh_800B80C8(EvEntEventfnc* e)
{
    unsigned int i;
    unsigned int k = e->f84_84;
    int r;
    for (i = 0; i < dword_8008B500.nMeshes_4; i++, k++)
    {
        k %= dword_8008B500.nMeshes_4;
        r = FindTriAtXZ_800B76B8(&dword_8008B500.meshes_C[k], (EvVecEventfnc*)&levantPos_8008BD18.pos);
        if (r >= 0)
        {
            e->f80_80 = r;
            if (e->f84_84 != k)
            {
                e->f84_84 = k;
            }
            return 1;
        }
    }
    return 0;
}

int FindMeshAtPos_800B8184(EvVecEventfnc* pos, unsigned int k)
{
    unsigned int i;
    for (i = 0; i < dword_8008B500.nMeshes_4; i++)
    {
        k %= dword_8008B500.nMeshes_4;
        if (FindTriAtXZ_800B76B8(&dword_8008B500.meshes_C[k], pos) >= 0)
        {
            return k;
        }
        k++;
    }
    return -1;
}

void sub_800B8220(int* p, int a1, int a2, int* a3, int* a4, int* a5)
{
    sub_800B79E0((MapMesh*)a2, p, (int*)a1, a3, a4);
    SlideAlongEdge_800B7E40(p, a2, *a3, *a4, a5);
    p[0] += a5[2] >> 10;
    p[2] -= a5[0] >> 10;
}

int sub_800B82C8(int* p, int* a1, MapMesh* ents, unsigned char* flags, int n)
{
    int i;
    int t0;
    int t1;
    int v[4];
    for (i = 0; i < n; i++)
    {
        if (flags[i])
        {
            t1 = -1;
            t0 = -1;
            sub_800B79E0(&ents[i], a1, p, &t0, &t1);
            if (t0 != -1 && t1 != -1)
            {
                SlideAlongEdge_800B7E40(p, (int)&ents[i], t0, t1, v);
                p[0] -= v[2] >> 10;
                p[2] += v[0] >> 10;
                return 0;
            }
        }
    }
    return 1;
}

void GetTriHeight_800B83E4(int* v, MapMesh* m, int i)
{
    MapTri* t = &m->tris_4[i];
    v[1] = (t->ny_1A * t->v_0[0].y_2 - t->nx_18 * (v[0] - t->v_0[0].x_0) - t->nz_1C * (v[2] - t->v_0[0].z_4)) / t->ny_1A;
}

void sub_800B844C(TaskEventfnc* t)
{
    SaveData* s;
    EvSpawnEventfnc sp;
    int i;
    int n;
    if (IsModelLoaderDone_800205D0())
    {
        EvMapEntEventfnc*** tbl = dword_800B0608;
        s = &saveData_8008B570;
        sp.f1A_1A = tbl[s->mapId_2E4[0].field_0][s->mapId_2E4[1].field_0][s->mapId_2E4[2].field_2].f6_6;
        sp.f18_18 = tbl[s->mapId_2E4[0].field_0][s->mapId_2E4[1].field_0][s->mapId_2E4[2].field_0].f6_6;
        n = sub_800A49CC(tbl[s->mapId_2E4[0].field_0][s->mapId_2E4[1].field_0][s->mapId_2E4[2].field_2].f4_4, sp.f18_18, &dword_80091C60, &sp);
        for (i = 0; i < n; i++)
        {
            sub_800B8568(sp.a_0[i], sp.b_C[i], -1, i);
        }
        t->flags_0 = (t->flags_0 & ~1) | 0x8000;
    }
}

typedef struct EvEnemyEventfnc
{
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int idx_14;
    int f18;
    UnitStats minion_1C;
    Actor* actor_A4;
    int fA8;
    int fAC;
    EvPairEventfnc xy_B0[3];
    int fC8;
    int fCC;
    int fD0;
    int z_D4[3];
} EvEnemyEventfnc;
typedef struct EvLoadEntEventfnc
{
    int f0;
    int id_4;
    int pad_8[3];
} EvLoadEntEventfnc;
// work area of the model loader task (modelLoaderTask_8008B54C)
typedef struct EvLoaderEventfnc
{
    int f0;
    int f4;
    int f8;
    EvLoadEntEventfnc ents_C[4];
} EvLoaderEventfnc;
// an enemy slot of the GAME overlay (GameSlot_1): sub_800A17F4 copies the EvEnemyEventfnc into data_8
typedef struct EvEnemySlotEventfnc
{
    int f0;
    int aiEvent_4;
    EvEnemyEventfnc data_8;
} EvEnemySlotEventfnc;
extern EvEnemySlotEventfnc* sub_800A17F4(EvEnemyEventfnc* src, int b);
extern int CreateEnemyAiEvent_800A2D90(Actor* a, UnitStats* b, int c);
extern short defaultBones_80079140[]; // default bone table

// Matched
void sub_800B8568(EvPosEventfnc* a, EvPlaceEventfnc* b, int c, int d)
{
    ActorDesc s;
    UnitStats mi;
    EvEnemyEventfnc e;
    int v[3];
    unsigned short* id;
    EvLoadEntEventfnc* l;
    int found;
    int i;
    Model* model;
    int k;
    int* p0;
    int* p1;
    int f;
    Actor* actor;
    unsigned short* x;
    EvEnemySlotEventfnc* slot;
    id = &GetSpeciesModelDesc_80019C70(a->xy.a)->modelId_0;
    found = 0;
    l = ((EvLoaderEventfnc*)modelLoaderTask_8008B54C->entry.buffer)->ents_C;
    for (i = 3; i >= 0; i--)
    {
        if (*id == l->id_4)
        {
            found = 1;
        }
        l++;
    }
    if (found)
    {
        model = AcquireLoaderModel_80020734(*id);
        k = InitMinionData_8001900C(&mi, &a->xy.a);
        s.modelId_0 = *id;
        s.kind_4 = 0;
        s.pos_8[0] = b->pos_0[0];
        s.pos_8[1] = b->pos_0[1];
        s.pos_8[2] = b->pos_0[2];
        s.rot_14[0] = 0;
        s.rot_14[1] = b->rotY_C;
        s.rot_14[2] = 0;
        s.clutRow_1C = 0;
        s.animIdx_20 = 1;
        s.frame_24 = -1;
        s.frameSpeed_28 = 0x1000;
        s.blendDiv_2C = 4;
        s.visible_30 = 1;
        s.bones_34 = defaultBones_80079140;
        if (k >= 4)
        {
            s.baseScale_38 = sub_80024E90(model, k);
        }
        else
        {
            p0 = sub_80024E90(model, k);
            p1 = sub_80024E90(model, k + 1);
            f = GetUnitRank_80019AD0(&mi);
            f = ((p1[0] - p0[0]) * f) / 4096;
            v[0] = p0[0] + f;
            v[1] = p0[1] + f;
            v[2] = p0[2] + f;
            s.baseScale_38 = v;
        }
        s.boneScale_3C = sub_80024EC8(model, k);
        s.anims_40 = sub_80024E38(model);
        s.effectTbl_44 = sub_80024E64(model);
        s.hasMatrices_4C = 0;
        actor = CreateActor_8001D45C(&s);
        x = sub_80024F00(model, k);
        SetBoneGroupFlags_80019B14(actor->bones_134, x, sub_80024F38(model, k));
        e.f0 = 2;
        e.f4 = 3;
        e.f8 = 1;
        e.fC = 1;
        e.f10 = 1;
        e.idx_14 = d;
        e.f18 = 1;
        e.minion_1C = mi;
        e.actor_A4 = actor;
        e.fA8 = 0;
        e.fAC = 0;
        e.xy_B0[0] = a[0].xy;
        e.xy_B0[1] = a[1].xy;
        e.xy_B0[2] = a[2].xy;
        e.fC8 = 0;
        e.fCC = 0;
        e.fD0 = 0;
        e.z_D4[0] = a[0].z;
        e.z_D4[1] = a[1].z;
        e.z_D4[2] = a[2].z;
        slot = sub_800A17F4(&e, 0);
        slot->aiEvent_4 = CreateEnemyAiEvent_800A2D90(actor, &slot->data_8.minion_1C, c);
    }
}

// work area of the encounter task (dword_8008D674, sub_800B844C)
typedef struct EvEncWorkEventfnc
{
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
} EvEncWorkEventfnc;
void sub_800B88A4(int a)
{
    EventEntry* p;
    EvEncWorkEventfnc* q;
    if (a)
    {
        sub_800B8940((int*)a);
        eventDispatchHalt_8008B540 = 1;
    }
    p = &dword_8008D674->entry;
    p->flags = (p->flags | 1) & 0xFFFF7FFF;
    q = (EvEncWorkEventfnc*)p->buffer;
    q->f8 = 0;
    q->fC = 0;
    q->f10 = 0;
    q->f14 = 0;
    p->cb_8 = (EventEntryFn)sub_800B844C;
    sub_800A170C();
    sub_800A1794();
}

void sub_800B8928()
{
    int i;
    for (i = 0x2a; i >= 0; i--)
    {
    }
}


void sub_800B8940(int* ids)
{
    int i = 0;
    int* q = ids;
    for (; i < 3; i++)
    {
        MinionModelDesc* e = GetSpeciesModelDesc_80019C70(*q++);
        RequestLoaderModel_800206A0(e->modelId_0, e->field_2 << 1, 3, -1);

    }
    StartModelLoader_8002056C();
}

int sub_800B89A8(EvCtxEventfnc* c)
{
    c->pc_8++;
    return 1;
}

int sub_800B89C0(EvCtxEventfnc* c)
{
    if (padPressed_8009194C & 0x100)
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800B89F4(EvCtxEventfnc* c)
{
    if (sub_800B8A34(c))
    {
        c->flags_0 |= 1;
    }
    return 0;
}

int sub_800B8A34(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    int i;
    switch (c->fB8_B8)
    {
    case 0:
        if (c->f1C_1C & c->f14_14)
        {
            m.m0_0 = c->f1C_1C;
            m.m4_4 = 4;
            m.mC_C = c->f24_24[c->pc_8->b_8];
            if (!sub_800BB990(c, &m, 1, 0))
            {
                return 0;
            }
        }
        c->fB8_B8++;
    case 1:
        if (c->f18_18)
        {
            return 0;
        }
        c->fB8_B8++;
    case 2:
        for (i = 0; i < 5; i++)
        {
            int bit = 1 << i;
            if (c->f14_14 & bit)
            {
                if (i == 0)
                {
                    sub_800A8E38();
                }
                else
                {
                    sub_800A785C(i - 1);
                }
                c->f14_14 &= ~(1 << i);
            }
        }
        if (c->f14_14 == 0 && (c->flags_0 & 0x20))
        {
            c->flags_0 &= ~0x20;
            sub_800A1974();
        }
        if (dword_800AEBD8 == c->f10_10)
        {
            dword_800AEBD8 = -1;
        }
        sub_800A5B54(c);
        c->fB8_B8 = 0;
        c->pc_8++;
        return 1;
    }
    return 0;
}

#if 0
extern int dword_800B0EC0;
extern int dword_800B1260;
extern int sub_800A6D50(int a);
extern void sub_800A1904(void);
int sub_800B8BE8(EvCtxEventfnc* c)
{
    int r;
    if (dword_800B0EC0 != 1)
    {
        return 0;
    }
    if (dword_800B1260 != 0)
    {
        return 0;
    }
    if (dword_800AEBD8 >= 0)
    {
        if (c->f10_10 != dword_800AEBD8)
        {
            return 0;
        }
    }
    r = sub_800A6D50(0);
    if (r != sub_800A6D50(2))
    {
        return 0;
    }
    c->flags_0 |= 0x20;
    sub_800A1904();
    dword_800AEBD8 = c->f10_10;
    c->pc_8++;
    return 1;
}
#endif

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8BE8);

int sub_800B8CB0(EvCtxEventfnc* c)
{
    EvInsEventfnc* p = c->pc_8;
    if (p->b_8 != 0)
    {
        c->ret_C = p;
        c->pc_8 = p + 1;
        c->flags_0 |= 0x10;
    }
    else
    {
        c->flags_0 &= ~0x10;
        c->pc_8++;
    }
    return 1;
}

int sub_800B8D08(EvCtxEventfnc* c)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        int bit = 1 << i;
        if (c->pc_8->b_8 & bit)
        {
            if (i == 0)
            {
                sub_800A8E0C();
                sub_800A8DEC();
            }
            else if (sub_800A7810(i - 1) == 0)
            {
                return 0;
            }
            sub_800BBC00(c, i, 1);
            sub_800BBC80(c, i, 1);
            c->f14_14 |= 1 << i;
        }
    }
    c->pc_8++;
    return 1;
}

int sub_800B8DDC(EvCtxEventfnc* c)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        int bit = 1 << i;
        if ((c->f14_14 & bit) && (c->pc_8->b_8 & bit))
        {
            if (i == 0)
            {
                sub_800A8E38();
            }
            else
            {
                sub_800A785C(i - 1);
            }
            c->f14_14 &= ~(1 << i);
        }
    }
    c->pc_8++;
    return 1;
}

int sub_800B8E9C(EvCtxEventfnc* c)
{
    int target = c->pc_8[c->fEC_EC].b_8;
    EvInsEventfnc* p = c->start_4;
    while (p->op_0 != 3)
    {
        if (p->op_0 == 9 && target == p->b_8)
        {
            c->pc_8 = p;
            c->fEC_EC = 0;
            return 1;
        }
        p++;
    }
    return 0;
}

// Matched
int sub_800B8F14(EvCtxEventfnc* c)
{
    EvInsEventfnc* p = (EvInsEventfnc*)c->pc_8[c->fEC_EC].c_C;
    c->fEC_EC = 0;
    c->pc_8 = p;
    c->start_4 = p;
    c->ret_C = c->pc_8;
    return 1;
}

int sub_800B8F44(EvCtxEventfnc* c)
{
    c->fC4_C4++;
    if (c->fC4_C4 >= c->pc_8->b_8 + 1)
    {
        c->fC4_C4 = 0;
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800B8F88(EvCtxEventfnc* c)
{
    if (c->f18_18 & c->pc_8->b_8)
    {
        return 0;
    }
    c->pc_8++;
    return 1;
}

int sub_800B8FB8(EvCtxEventfnc* c)
{
    unsigned int v = c->pc_8->b_8;
    int hi = v >> 16;
    int lo = v & 0xFFFF;
    if (c->pc_8->a_4 == 0)
    {
        c->fCC_CC[hi] = lo;
    }
    else
    {
        sub_800AD16C(hi, lo);
    }
    c->pc_8++;
    return 1;
}

int sub_800B9020(EvCtxEventfnc* c)
{
    unsigned int a = c->pc_8->a_4;
    unsigned int b = c->pc_8->b_8;
    int slot = a >> 16;
    int lo = a & 0xFFFF;
    int mod = b >> 16;
    int idx = b & 0xFFFF;
    int r;
    if (slot == 9)
    {
        do
        {
            r = rand() % mod;
        } while (r < lo);
        c->fEC_EC = r;
        if (idx < 8)
        {
            c->fCC_CC[idx] = r;
        }
    }
    else
    {
        c->fEC_EC = c->fCC_CC[slot];
        if (++c->fCC_CC[slot] >= mod)
        {
            if (idx)
            {
                c->fCC_CC[slot] = lo;
            }
            else
            {
                c->fCC_CC[slot] = mod - 1;
            }
        }
    }
    c->pc_8++;
    return 1;
}

int sub_800B9110(EvCtxEventfnc* c)
{
    unsigned int a = c->pc_8->a_4;
    unsigned int b = c->pc_8->b_8;
    int hi = a >> 16;
    int lo = a & 0xFFFF;
    int hi2 = b >> 16;
    int lo2 = b & 0xFFFF;
    int v = sub_800AD154(hi);
    c->fEC_EC = v;
    sub_800AD16C(hi, v + 1);
    if (sub_800AD154(hi) >= hi2)
    {
        if (lo2)
        {
            sub_800AD16C(hi, lo);
        }
        else
        {
            sub_800AD16C(hi, hi2 - 1);
        }
    }
    c->pc_8++;
    return 1;
}

int sub_800B91CC(EvCtxEventfnc* c)
{
    dword_800B1D98(c->pc_8->c_C);
    c->pc_8++;
    return 1;
}

int sub_800B9218(EvCtxEventfnc* c)
{
    sub_800A59D0(c->pc_8->c_C);
    c->pc_8++;
    return 1;
}

int sub_800B9260(EvCtxEventfnc* c)
{
    int* q = (int*)c->pc_8->c_C;
    EvVecEventfnc* pos = sub_800BBBA0(c->pc_8->a_4);
    SVECTOR* rot = sub_800BBBD0(c->pc_8->a_4);
    int ang;
    if (q)
    {
        ang = q[3];
    }
    else
    {
        q = (int*)sub_800BBC00(c, c->pc_8->a_4, 0);
        ang = sub_800BBC80(c, c->pc_8->a_4, 0)->y_4;
    }
    pos->x_0 = q[0];
    pos->y_4 = q[1];
    pos->z_8 = q[2];
    rot->vy = ang;
    sub_80037918(cameraTask_8008D4A0->entry.buffer);
    SetGeomOffset(display_8008B4D8.field_C_w / 2 + screenOffset_8008D474[0], display_8008B4D8.field_E_h / 2 + screenOffset_8008D474[1]);
    c->pc_8++;
    return 1;
}

int sub_800B93A8(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    EvVecEventfnc* v = (EvVecEventfnc*)c->pc_8->c_C;
    m.m0_0 = c->pc_8->a_4;
    m.m4_4 = c->pc_8->op_0 != 0x14;
    m.m18_18 = v->x_0;
    m.m1C_1C = v->y_4;
    m.m20_20 = v->z_8;
    m.m14_14 = c->pc_8->b_8;
    return sub_800BB840(c, &m, 1, 1);
}

int sub_800B942C(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    EvVecEventfnc d;
    EvVecEventfnc* a = sub_800BBBA0(c->pc_8->a_4);
    EvVecEventfnc* b;
    int ang;
    if (c->pc_8->a_4 == c->pc_8->b_8)
    {
        b = sub_800BBC00(c, c->pc_8->a_4, 0);
    }
    else
    {
        b = sub_800BBBA0(c->pc_8->b_8);
    }
    d.x_0 = a->x_0 - b->x_0;
    d.z_8 = a->z_8 - b->z_8;
    ang = ratan2_8003B548(d.x_0, d.z_8);
    m.m0_0 = c->pc_8->a_4;
    m.m4_4 = c->pc_8->op_0 != 0x15;
    m.m18_18 = b->x_0 + name_80084540[ang & 0xFFF] * 200 / 4096;
    m.m1C_1C = b->y_4;
    m.m20_20 = b->z_8 + name_80084540[(ang + 0x400) & 0xFFF] * 200 / 4096;
    m.m14_14 = c->pc_8->c_C;
    return sub_800BB840(c, &m, 1, 1);
}

int sub_800B95BC(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    EvInsEventfnc* i = c->pc_8;
    EvVecEventfnc* v = (EvVecEventfnc*)i->c_C;
    int a = i->a_4;
    m.m0_0 = a;
    m.m4_4 = 2;
    m.m18_18 = v->x_0;
    m.m1C_1C = v->y_4;
    m.m20_20 = v->z_8;
    m.m14_14 = c->pc_8->b_8;
    return sub_800BB840(c, &m, 1, 1);
}

int sub_800B962C(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    EvVecEventfnc* v;
    int a = c->pc_8->a_4;
    int b = c->pc_8->b_8;
    v = (a == b) ? sub_800BBC80(c, b, 0) : sub_800BBBA0(b);
    m.m0_0 = c->pc_8->a_4;
    m.m4_4 = 2;
    m.m18_18 = v->x_0;
    m.m1C_1C = v->y_4;
    m.m20_20 = v->z_8;
    m.m14_14 = c->pc_8->c_C;
    return sub_800BB840(c, &m, 1, 1);
}

int sub_800B96D8(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = c->pc_8->a_4;
    m.m4_4 = 6;
    m.mC_C = c->pc_8->b_8;
    return sub_800BB990(c, &m, 0, 1);
}

int sub_800B9720(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = c->pc_8->a_4;
    m.m4_4 = 7;
    m.mC_C = c->pc_8->b_8;
    return sub_800BB990(c, &m, 0, 1);
}

int sub_800B9768(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = c->pc_8->a_4;
    m.m4_4 = 8;
    m.mC_C = c->pc_8->b_8;
    return sub_800BB990(c, &m, 0, 1);
}

int sub_800B97B0(EvCtxEventfnc* c)
{
    sub_800BBC00(c, c->pc_8->a_4, 1);
    c->pc_8++;
    return 1;
}

int sub_800B97F8(EvCtxEventfnc* c)
{
    sub_800BBC80(c, c->pc_8->a_4, 1);
    c->pc_8++;
    return 1;
}

int sub_800B9840(EvCtxEventfnc* c)
{
    if (c->pc_8->a_4 == 0)
    {
        if (sub_800AD0D4(c->pc_8->b_8))
        {
            c->pc_8++;
            return 1;
        }
        return 0;
    }
    c->fEC_EC = sub_800AD0D4(c->pc_8->b_8) == 0;
    c->pc_8++;
    return 1;
}

int sub_800B98C4(EvCtxEventfnc* c)
{
    sub_800AD0F8(c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

int sub_800B990C(EvCtxEventfnc* c)
{
    sub_800AD124(c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

int sub_800B9954(EvCtxEventfnc* c)
{
    if (c->pc_8->a_4 == 0)
    {
        if (sub_800BBDD8(c->pc_8->b_8))
        {
            c->pc_8++;
            return 1;
        }
        return 0;
    }
    c->fEC_EC = sub_800BBDD8(c->pc_8->b_8) == 0;
    c->pc_8++;
    return 1;
}

int sub_800B99D8(EvCtxEventfnc* c)
{
    sub_800BBDA0(c->pc_8->b_8, 1);
    c->pc_8++;
    return 1;
}

int sub_800B9A20(EvCtxEventfnc* c)
{
    sub_800BBDA0(c->pc_8->b_8, 0);
    c->pc_8++;
    return 1;
}

int sub_800B9A68(EvCtxEventfnc* c)
{
    sub_800AD184(c->pc_8->a_4, c->pc_8->b_8, 0);
    c->pc_8++;
    return 1;
}

int sub_800B9AB4(EvCtxEventfnc* c)
{
    sub_800AD1E0(c->pc_8->a_4, c->pc_8->b_8, 0);
    c->pc_8++;
    return 1;
}

int sub_800B9B00(EvCtxEventfnc* c)
{
    sub_800AD184(c->pc_8->a_4, c->pc_8->b_8, 1);
    c->pc_8++;
    return 1;
}

int sub_800B9B4C(EvCtxEventfnc* c)
{
    sub_800AD1E0(c->pc_8->a_4, c->pc_8->b_8, 1);
    c->pc_8++;
    return 1;
}

#if 0
// Not matched: the original places a shared 'return 0' block in front of the body and tests the condition differently
int sub_800B9B98(EvCtxEventfnc* c)
{
    unsigned int f;
    if (c->pc_8->a_4 == 0)
    {
        if (dword_800AEBD8 < 0 || dword_800AEBD8 == c->f10_10)
        {
            f = c->flags_0 | 8;
            c->flags_0 = f;
            c->fC8_C8 = c->pc_8->b_8;
            if (!(f & 4))
            {
                return 0;
            }
            c->flags_0 = f & ~0xC;
            c->fC8_C8 = -1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        c->fEC_EC = sub_800AD73C(c->pc_8->b_8) == 0;
    }
    c->pc_8++;
    return 1;
}
#endif

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9B98);

int sub_800B9C5C(EvCtxEventfnc* c)
{
    int a = c->pc_8->a_4;
    int b = c->pc_8->b_8;
    if (a != 0)
    {
        sub_800AD68C(b);
    }
    else
    {
        sub_800AD6E4(b);
    }
    c->pc_8++;
    return 1;
}

int sub_800B9CC0(EvCtxEventfnc* c)
{
    sub_800AD058(c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

int sub_800B9D08(EvCtxEventfnc* c)
{
    sub_800AD8F4(c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

int sub_800B9D50(EvCtxEventfnc* c)
{
    int i;
    UnitStatus* p;
    Heal_80011CD0(sub_800A8C34());

    for (i = 0; i < CountMinions_80010548(3); i++)
    {
        p = GetMinionStatus_800107A0(3, i);
        Heal_80011CD0(p);
        FillHpMp_80011C0C(p, p);
    }
    c->pc_8 += 1;
    return 1;
}

int sub_800B9DE0(EvCtxEventfnc* c)
{
    EvEntEventfnc* e = sub_800A5DDC(c->pc_8->c_C, c->pc_8->a_4, 0);
    if (e == 0)
    {
        return 0;
    }
    e->f7C_7C = c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

int sub_800B9E48(EvCtxEventfnc* c)
{
    EvEntEventfnc* e = sub_800A5DDC(c->pc_8->c_C, c->pc_8->a_4, 0);
    if (e != 0 && e->f80_80 == c->pc_8->b_8)
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800B9EB0(EvCtxEventfnc* c)
{
    c->ent_120->f7C_7C = c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

int sub_800B9EDC(EvCtxEventfnc* c)
{
    if (c->ent_120->f80_80 == c->pc_8->b_8)
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800B9F0C(EvCtxEventfnc* c)
{
    if (sub_800A5DDC(c->pc_8->c_C, c->pc_8->b_8, 0) == 0)
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800B9F5C(EvCtxEventfnc* c)
{
    c->f108_108 |= c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

int sub_800B9F84(EvCtxEventfnc* c)
{
    c->f100_100 = c->pc_8->a_4;
    c->f102_102 = c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

int sub_800B9FB4(EvCtxEventfnc* c)
{
    c->f104_104 = c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

int sub_800B9FD8(EvCtxEventfnc* c)
{
    sub_800A6830(c->pc_8->c_C);
    c->pc_8++;
    return 1;
}

int sub_800BA020(EvCtxEventfnc* c)
{
    EvInsEventfnc* pc = c->pc_8;
    switch (c->fB4_B4)
    {
    case 0:
        if (pc->op_0 == 0x3F)
        {
            c->fB4_B4 = 3;
            c->flags_0 &= ~0x40;
            return 1;
        }
        c->fB4_B4++;
    case 1:
        sub_800BC7A0(c);
        if (!sub_800BBE3C(c))
        {
            break;
        }
        c->f110_110 = (int*)c->pc_8;
        c->fB4_B4++;
    case 2:
        if (pc->op_0 == 0x38 || pc->op_0 == 0x3A)
        {
            c->fB4_B4 = 0;
            c->flags_0 |= 0x40;
            c->pc_8++;
            return 1;
        }
        c->fB4_B4++;
    case 3:
        if (!sub_800BC2B4(c))
        {
            break;
        }
        c->fB4_B4++;
    case 4:
        if (c->flags_0 & 0x100)
        {
            if (!XaRequestStop_80043524())
            {
                break;
            }
            c->flags_0 &= ~0x100;
        }
    case 5:
        if (c->f118_118)
        {
            c->fB4_B4 = 2;
            c->pc_8++;
            return 1;
        }
        if ((*(int*)c->f11C_11C & 0x8001) == 1)
        {
            break;
        }
        c->f11C_11C = 0;
        c->fB4_B4 = 0;
        c->pc_8++;
        return 1;
    }
    c->pc_8 = pc;
    return 0;
}


int sub_800BA1DC(EvCtxEventfnc* c)
{
    int* p = c->f110_110;
    if (p != 0)
    {
        EvInsEventfnc* i = c->pc_8;
        unsigned int a = i->a_4;
        unsigned int b = i->b_8;
        if (b >= a)
        {
            p[3] = i->c_C;
        }
        else
        {
            i->b_8 = b + 1;
        }
    }
    c->pc_8++;
    return 1;
}

int sub_800BA238(EvCtxEventfnc* c)
{
    if (sub_80034ADC(c->f11C_11C, c->pc_8->b_8))
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800BA28C(EvCtxEventfnc* c)
{
    EvInsEventfnc* i = c->pc_8;
    if (i->a_4 == 1)
    {
        c->f114_114 |= i->b_8;
    }
    else
    {
        c->f114_114 &= ~i->b_8;
    }
    c->pc_8++;
    return 1;
}

int sub_800BA2E8(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = 1 << c->pc_8->a_4;
    m.m4_4 = 3;
    m.mC_C = c->pc_8->b_8;
    return sub_800BB990(c, &m, 1, 1);
}

int sub_800BA338(EvCtxEventfnc* c)
{
    EvInsEventfnc* ins = c->pc_8;
    EvMsgEventfnc m;
    switch (c->fB8_B8)
    {
    case 0:
        m.m0_0 = ins->b_8;
        m.m4_4 = 4;
        m.mC_C = c->f24_24[c->pc_8->a_4];
        if (sub_800BB990(c, &m, 1, 0))
        {
            c->fB8_B8++;
        }
    case 1:
        if ((c->f18_18 & c->pc_8->b_8) == 0)
        {
            c->fB8_B8 = 0;
            c->pc_8++;
            return 1;
        }
        c->pc_8 = ins;
        return 0;
    default:
        c->pc_8 = ins;
        return 0;
    }
}

int sub_800BA40C(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = 1 << c->pc_8->a_4;
    m.m4_4 = 5;
    m.m24_24 = c->pc_8->c_C;
    return sub_800BB990(c, &m, 1, 1);
}

int sub_800BA45C(EvCtxEventfnc* c)
{
    int ok = 0;
    int a = c->pc_8->a_4;
    if (a != 0)
    {
        EvObjEventfnc* o = sub_800A7A60(a - 1);
        if (o->f90_90 == o->f1A_1A)
        {
            SetActorAnimPaused_8001D6EC(o, c->pc_8->b_8);
            ok = 1;
        }
    }
    if (ok)
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800BA4F0(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = 1 << c->pc_8->a_4;
    m.m4_4 = 9;
    m.mC_C = c->pc_8->b_8;
    m.m14_14 = c->pc_8->c_C;
    return sub_800BB990(c, &m, 1, 1);
}

int sub_800BA554(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = 1 << c->pc_8->a_4;
    m.m4_4 = 0xA;
    m.mC_C = ((unsigned short*)&c->pc_8->b_8)[1];
    m.m10_10 = ((unsigned short*)&c->pc_8->b_8)[0];
    m.m14_14 = c->pc_8->c_C;
    return sub_800BB990(c, &m, 1, 1);
}

int sub_800BA5CC(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    int n = c->pc_8->c_C;
    int* r = sub_800A55B0(4);
    unsigned int a = c->pc_8->a_4;
    m.m0_0 = 1 << (a >> 16);
    m.m4_4 = 0xB;
    m.mC_C = ((unsigned short*)&c->pc_8->b_8)[1];
    m.m10_10 = ((unsigned short*)&c->pc_8->b_8)[0];
    m.m24_24 = r[1] + n * 12;
    m.m14_14 = a & 0xFFFF;
    return sub_800BB990(c, &m, 1, 1);
}

int sub_800BA678(EvCtxEventfnc* c)
{
    c->fF0_F0 = c->pc_8->c_C;
    if (c->fF0_F0 == 0)
    {
        c->fF0_F0 = sub_800BBDF4(c);
    }
    c->pc_8++;
    return 1;
}

int sub_800BA6D0(EvCtxEventfnc* c)
{
    c->fF4_F4 = c->pc_8->a_4;
    c->fF8_F8 = c->pc_8->b_8;
    c->fFC_FC = c->pc_8->c_C;
    c->fF0_F0 = (int)&c->fF4_F4;
    c->pc_8++;
    return 1;
}

int sub_800BA714(EvCtxEventfnc* c)
{
    if (c->pc_8->b_8 == 1 || dword_800AEBD8 < 0 || dword_800AEBD8 == c->f10_10)
    {
        if (((int (*)(int))c->pc_8->c_C)(c->fF0_F0) == 1)
        {
            c->fF0_F0 = 0;
            c->pc_8++;
            return 1;
        }
    }
    return 0;
}

int sub_800BA7A4(EvCtxEventfnc* c)
{
    if (c->pc_8->b_8 == 1 || dword_800AEBD8 < 0 || dword_800AEBD8 == c->f10_10)
    {
        c->fEC_EC = ((int (*)(int))c->pc_8->c_C)(c->fF0_F0);
        c->fF0_F0 = 0;
        c->pc_8++;
        return 1;
    }
    return 0;
}

#if 0
// Not matched: the tail is scheduled differently (the constant 1 lands in $v0 and the halt store sinks below the pc store; original: $v1, halt store first)
int sub_800BA82C(EvCtxEventfnc* c)
{
    SaveData* s = &saveData_8008B570;
    s->chapter_2DC = *(unsigned short*)&c->pc_8->b_8;
    sub_800A6D30(0);
    eventDispatchHalt_8008B540 = 1;
    c->pc_8++;
    return 1;
}
#endif

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA82C);

int sub_800BA880(EvCtxEventfnc* c)
{
    SaveData* s = &saveData_8008B570;
    s->field_2E0 = *(unsigned short*)&c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

int sub_800BA8AC(EvCtxEventfnc* c)
{
    unsigned short v[3];
    v[0] = ((unsigned short*)&c->pc_8->a_4)[0];
    v[1] = ((unsigned short*)&c->pc_8->b_8)[1];
    v[2] = ((unsigned short*)&c->pc_8->b_8)[0];
    sub_800ADC5C(v, c->pc_8->c_C);
    c->pc_8++;
    return 1;
}

int sub_800BA930(EvCtxEventfnc* c)
{
    SaveData* s = &saveData_8008B570;
    int* p;
    s->mapId_2E4[0].field_0 = ((unsigned short*)&c->pc_8->a_4)[0];
    s->mapId_2E4[1].field_0 = ((unsigned short*)&c->pc_8->b_8)[1];
    s->mapId_2E4[2].field_0 = ((unsigned short*)&c->pc_8->b_8)[0];
    s->mapId_2E4[2].field_2 = -1;
    p = (int*)c->pc_8->c_C;
    if (p)
    {
        s->levant_7A8.pos.x = p[0];
        s->levant_7A8.pos.y = p[1];
        s->levant_7A8.pos.z = p[2];
        s->levant_7A8.rot.vy = p[3];
    }
    else
    {
        dword_80091C94 = 1;
    }
    eventDispatchHalt_8008B540 = 1;
    c->pc_8++;
    return 1;
}

int sub_800BA9E4(EvCtxEventfnc* c)
{
    unsigned short v[3];
    SaveData* s;
    sub_800ADCEC(v, c->pc_8->b_8);
    dword_80091C9C = 1;
    dword_80091C54 = 0;
    dword_80091C94 = 1;
    s = &saveData_8008B570;
    s->mapId_2E4[0].field_0 = v[0];
    s->mapId_2E4[1].field_0 = v[1];
    s->mapId_2E4[2].field_0 = v[2];
    eventDispatchHalt_8008B540 = 1;
    c->pc_8++;
    return 0;
}

int sub_800BAA6C(EvCtxEventfnc* c)
{
    if (((int (*)(int))sub_80027330)(c->pc_8->b_8))
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800BAAC0(EvCtxEventfnc* c)
{
    if (sub_80027358(c->pc_8->b_8))
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800BAB14(EvCtxEventfnc* c)
{
    sub_800A683C(c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

#if 0
extern int SetFadeMode_8001C19C(int a, int b);
int sub_800BAB5C(EvCtxEventfnc* c)
{
    SetFadeMode_8001C19C(1, 0x20);
    sub_800A6D30(8);
    eventDispatchHalt_8008B540 = 1;
    c->pc_8++;
    return 1;
}
#endif

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BAB5C);

int sub_800BABB0(EvCtxEventfnc* c)
{
    switch (c->fB8_B8)
    {
    case 0:
        dword_800B06B0.f0_0 = 1;
        dword_800B06B0.f4_4 = ((unsigned short*)&c->pc_8->b_8)[1];
        dword_800B06B0.f8_8 = ((unsigned short*)&c->pc_8->b_8)[0];
        c->fB8_B8 = 1;
        return 0;
    case 1:
        if (dword_800B06B0.f0_0 == 0)
        {
            c->fEC_EC = sub_800A5F9C(0);
            c->fB8_B8 = 0;
            c->pc_8++;
            return 1;
        }
        return 0;
    default:
        return 0;
    }
}

int sub_800BAC60(EvCtxEventfnc* c)
{
    EvVecEventfnc v;
    EvVecEventfnc* src = (EvVecEventfnc*)c->pc_8->c_C;
    v.x_0 = src->x_0;
    v.y_4 = src->y_4 + 0x15E;
    v.z_8 = src->z_8;
    sub_800379DC(&v, c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

int sub_800BACE0(EvCtxEventfnc* c)
{
    sub_800379DC(sub_800BBBA0(c->pc_8->a_4), c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

int sub_800BAD3C(EvCtxEventfnc* c)
{
    sub_80037A20(c->pc_8->c_C, c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

int sub_800BAD88(EvCtxEventfnc* c)
{
    int v = ((int (*)())sub_80037A4C)();
    int b = c->pc_8->b_8;
    if ((b == 1 && (short)v == 0x1000) || (b == 0 && (short)v == 0))
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800BADF8(EvCtxEventfnc* c)
{
    if (c->pc_8->c_C)
    {
        dword_8008D420 = *(EvRectEventfnc*)c->pc_8->c_C;
    }
    else
    {
        switch (c->pc_8->b_8)
        {
        case 0:
            dword_8008D420.x_0 = 0;
            dword_8008D420.y_2 = 0;
            dword_8008D420.w_4 = 0x140;
            dword_8008D420.h_6 = 0xF0;
            break;
        case 1:
            dword_8008D420.x_0 = 0;
            dword_8008D420.y_2 = 0x20;
            dword_8008D420.w_4 = 0x140;
            dword_8008D420.h_6 = 0xA0;
            break;
        }
    }
    c->pc_8++;
    return 1;
}

int sub_800BAEBC(EvCtxEventfnc* c)
{
    sub_80037A6C(c->pc_8->a_4, c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

int sub_800BAF08(EvCtxEventfnc* c)
{
    int v = c->pc_8->c_C;
    if (v == 0)
    {
        v = (int)sub_800BBBA0(c->pc_8->a_4);
    }
    SetCameraTarget_80037AC8(v);
    c->pc_8++;
    return 1;
}

int sub_800BAF68(EvCtxEventfnc* c)
{
    SaveData* s = &saveData_8008B570;
    unsigned short v = *(unsigned short*)&c->pc_8->b_8;
    s->mapId_2E4[3].field_0 = v;
    if ((short)v == s->mapId_2E4[3].field_2)
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800BAFAC(EvCtxEventfnc* c)
{
    EvVecEventfnc* lev;
    SVECTOR* rot;
    EvVecEventfnc* p;
    int i;
    int hit;
    unsigned int dist;
    if (dword_800AEBD8 >= 0 && dword_800AEBD8 != c->f10_10)
    {
        return 0;
    }
    if (c->flags_0 & 4)
    {
        c->flags_0 &= ~0xC;
        c->pc_8++;
        return 1;
    }
    c->flags_0 &= ~0xC;
    lev = sub_800BBBA0(0);
    rot = sub_800BBBD0(0);
    for (i = 1; i < sub_800A7790() + 1; i++)
    {
        int bit = 1 << i;
        if (c->pc_8->b_8 & bit)
        {
            p = sub_800BBBA0(i);
            hit = 0;
            if (c->pc_8->a_4 >= 0)
            {
                hit = FindTriAtXZ_800B76B8(&dword_8008B500.meshes20_20[c->pc_8->a_4], lev) >= 0;
            }
            else
            {
                dist = 0xFFF;
                IsWithinDistance_8003B740((int*)lev, (int*)p, &dist);
                if (dist <= 0x15F8F)
                {
                    hit = 1;
                }
            }
            if (hit)
            {
                if ((unsigned int)(WrapAngle_8003BA18((short)(rot->vy - ratan2Difference_8003B9E0((int*)lev, (int*)p))) + 0x198) < 0x331)
                {
                    c->flags_0 |= 8;
                    break;
                }
            }
        }
    }
    return 0;
}

int sub_800BB180(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    int r;
    int v = c->pc_8->b_8 & 0x80000000;
    c->f24_24[c->pc_8->a_4] = v;
    if ((c->pc_8->b_8 & 0x80000000) == 0)
    {
        c->pc_8++;
        r = 1;
    }
    else
    {
        m.m0_0 = 1 << c->pc_8->a_4;
        m.m4_4 = 3;
        m.mC_C = v;
        r = sub_800BB990(c, &m, 1, 1);
    }
    return r;
}

int sub_800BB214(EvCtxEventfnc* c)
{
    EvVecEventfnc* v = sub_800BBBA0(c->pc_8->a_4);
    if (sub_800A6504(c->pc_8->b_8, v))
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

#if 0
// Not matched: 4 words short - the compiler eliminates the loop counter (compares the src pointer instead); the original keeps i in $s5
typedef struct EvPartySrcEventfnc
{
    int f0_0[5];
    int f14_14;
    int ids_18[3];
    struct
    {
        int a_0;
        int b_4;
        int c_8;
    } e_24[3];
} EvPartySrcEventfnc;

typedef struct EvPartyEventfnc
{
    int f0_0[5];
    int f14_14;
    int f18_18;
    char pad_1C[0xA4 - 0x1C];
    int fA4_A4[3];
    struct
    {
        int a_0;
        int b_4;
    } fB0_B0[3];
    int fC8_C8[3];
    int fD4_D4[3];
} EvPartyEventfnc;

extern EvPartyEventfnc dword_800B1CB8;
extern int dword_800AEBE0;
extern int dword_800AEBE4;
extern int dword_800B1260;
extern int sub_800A7A9C(int i);
int sub_800BB27C(EvCtxEventfnc* c)
{
    EvPartySrcEventfnc* s;
    int i;
    int k;
    switch (c->fB8_B8)
    {
    case 0:
        s = (EvPartySrcEventfnc*)c->pc_8->c_C;
        dword_800AEBE4 = s->f14_14;
        dword_800B1CB8.f0_0[0] = s->f0_0[0];
        dword_800B1CB8.f0_0[1] = s->f0_0[1];
        dword_800B1CB8.f0_0[2] = s->f0_0[2];
        dword_800B1CB8.f0_0[3] = s->f0_0[3];
        dword_800B1CB8.f0_0[4] = s->f0_0[4];
        dword_800B1CB8.f14_14 = -1;
        dword_800B1CB8.f18_18 = 0;
        for (i = 0; i < 3; i++)
        {
            k = s->ids_18[i];
            if (k != 5)
            {
                dword_800B1CB8.fA4_A4[i] = (int)sub_800A7A60(k - 1);
                dword_800B1CB8.fB0_B0[i].a_0 = s->e_24[i].a_0;
                dword_800B1CB8.fB0_B0[i].b_4 = s->e_24[i].b_4;
                dword_800B1CB8.fC8_C8[i] = sub_800A7A9C(k - 1);
            }
            else
            {
                dword_800B1CB8.fA4_A4[i] = 0;
                dword_800B1CB8.fB0_B0[i].a_0 = s->e_24[i].a_0;
                dword_800B1CB8.fB0_B0[i].b_4 = s->e_24[i].b_4;
                dword_800B1CB8.fC8_C8[i] = 0;
            }
            dword_800B1CB8.fD4_D4[i] = s->e_24[i].c_8;
        }
        dword_800AEBE0 = 1;
        c->fB8_B8++;
    case 1:
        c->fB8_B8++;
        return 0;
    case 2:
        if (dword_800B1260)
        {
            return 0;
        }
        dword_800AEBE4 = 1;
        dword_800AEBE0 = 0;
        c->fB8_B8 = 0;
        c->pc_8++;
        return 1;
    }
    return 0;
}
#endif

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BB27C);

int sub_800BB45C(EvCtxEventfnc* c)
{
    if (c->pc_8->b_8 == dword_800B1230)
    {
        c->fEC_EC = 0;
    }
    else
    {
        c->fEC_EC = 1;
    }
    c->pc_8++;
    return 1;
}

extern void StartSceneFadeIn_8001AA04(int a);
extern void StartSceneFadeOut_8001AA50(int a);
extern void StopSceneDarken_8001AAF4();
extern void StartSceneBrighten_8001AB1C(int a);
extern void sub_800A094C();
extern void sub_800A096C();
extern short dword_80091CE0[];
extern void SsSepSetDecrescendo(int, int, int, int);
extern void SsSepStop(int, int);
extern void FadeOutSfxSeq_80031638();
extern void PlayMusic_800300E0(int a, int b);
extern short SfxKeyOn_800314F4(int a);
extern void SfxKeyOff_80031574(int a, int b);
extern void sub_80027478(int a, int b);
extern void SetMotionBlur_8001BCD8(int a);

// Matched
int sub_800BB4A4(EvCtxEventfnc* c)
{
    int r = 1;
    int op;
    int k;
    short* p;
    short* q;
    int* d;
    switch (c->pc_8->a_4)
    {
    case 0:
        ResetSceneFade_8001A9A4();
        break;
    case 1:
        SetSceneDark_8001A9E4();
        break;
    case 2:
        SetSceneDark_8001A9E4();
        StartSceneFadeIn_8001AA04(*(unsigned short*)&c->pc_8->b_8);
        break;
    case 3:
        StartSceneFadeOut_8001AA50(*(unsigned short*)&c->pc_8->b_8);
        break;
    case 4:
        StopSceneDarken_8001AAF4();
        StartSceneBrighten_8001AB1C(*(unsigned short*)&c->pc_8->b_8);
        break;
    case 5:
        StartSceneDarken_8001AAA8(*(unsigned short*)&c->pc_8->b_8);
        break;
    case 6:
        r = IsSceneFadeDone_8001AB94();
        break;
    case 7:
        StartFadeToBlack_8001C2CC();
        break;
    case 8:
        StartFadeToWhite_8001C2E4();
        break;
    case 9:
        r = IsFadeDone_8001C2FC();
        break;
    case 10:
        sub_800A094C();
        break;
    case 11:
        sub_800A096C();
        break;
    case 12:
        op = c->pc_8->b_8;
        if (op == 0xFF00)
        {
            p = dword_80091CE0;
            if (p[2] >= 0)
            {
                SsSepSetDecrescendo(p[6], p[2], 0x7F, 0x78);
                p[2] = -1;
            }
        }
        else if (op == 0xFF01)
        {
            p = dword_80091CE0;
            if (p[2] >= 0)
            {
                SsSepStop(p[6], p[2]);
                p[2] = -1;
            }
        }
        else if (op == 0xFF02)
        {
            FadeOutSfxSeq_80031638();
        }
        else if (op == 0xFF03)
        {
            StopSoundSeqById_800306FC(c->pc_8->c_C);
        }
        else if (op == 0xFF04)
        {
            k = c->pc_8->c_C;
            PlayMusic_800300E0(k, 1);
            SetBattleMusic_800315D8(k);
        }
        else
        {
            PlayMusic_800300E0(op, 1);
        }
        break;
    case 13:
        PlaySfx_80031494(c->pc_8->b_8);
        break;
    case 14:
        op = c->pc_8->b_8;
        d = (int*)c->pc_8->c_C;
        *d = SfxKeyOn_800314F4(op);
        break;
    case 15:
        SfxKeyOff_80031574(*(short*)c->pc_8->c_C, *(short*)&c->pc_8->b_8);
        break;
    case 16:
        q = (short*)c->pc_8->c_C;
        XaRequestPlay_80043564(q[0], q[1], q[2]);
        break;
    case 17:
        sub_80027478(0x40, c->pc_8->b_8);
        break;
    case 18:
        SetMotionBlur_8001BCD8(c->pc_8->b_8);
        break;
    }
    if (r != 0)
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800BB7D8(EvCtxEventfnc* c)
{
    EvInsEventfnc* i = c->pc_8;
    if (i->a_4 == 1)
    {
        StartPadVibration_80036528(0, *(unsigned char*)&i->b_8);
    }
    else
    {
        StopPadVibration_80036658(0);
    }
    c->pc_8++;
    return 1;
}

#if 0
// Not matched: the original keeps fC0 in $s0 for the whole loop (default case spins on the stale value); register allocation differs
int sub_800BB840(EvCtxEventfnc* c, EvMsgEventfnc* m, int a, int b)
{
    while (1)
    {
        switch (c->fC0_C0)
        {
        case 0:
            m->m8_8 = a;
            if (c->f18_18 & (1 << m->m0_0))
            {
                return 0;
            }
            if (!sub_800BBAB0(m->m0_0))
            {
                return 0;
            }
            sub_800BBB18((int*)m);
            if (a)
            {
                c->f18_18 |= 1 << m->m0_0;
            }
            c->fC0_C0 = 1;
            break;
        case 1:
            if (!sub_800BBAE4(m->m0_0))
            {
                return 0;
            }
            sub_800BBB5C((int*)m);
            if (b)
            {
                c->pc_8++;
            }
            if (m->m4_4 == 3)
            {
                c->f1C_1C |= c->fC0_C0 << m->m0_0;
            }
            else if (m->m4_4 == 4)
            {
                c->f1C_1C &= ~(c->fC0_C0 << m->m0_0);
            }
            c->fC0_C0 = 0;
            return 1;
        }
    }
}
#endif

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BB840);

int sub_800BB990(EvCtxEventfnc* c, EvMsgEventfnc* m, int a, int b)
{
    int i;
    int bit;
    switch (c->fBC_BC)
    {
    case 0:
        c->f24_24[5] = m->m0_0;
        c->fBC_BC++;
    case 1:
        for (i = 0; i < 5; i++)
        {
            bit = 1 << i;
            if (c->f24_24[5] & bit)
            {
                m->m0_0 = i;
                if (!sub_800BB840(c, m, a, 0))
                {
                    break;
                }
                c->f24_24[5] &= ~bit;
            }
        }
        if (c->f24_24[5] == 0)
        {
            if (b)
            {
                c->pc_8++;
            }
            c->fBC_BC = 0;
            return 1;
        }
        return 0;
    default:
        return 0;
    }
}

int sub_800BBAB0(int i)
{
    int r;
    if (i == 0)
    {
        r = sub_800A8E7C();
    }
    else
    {
        r = sub_800A7CB8(i - 1);
    }
    return r;
}

int sub_800BBAE4(int i)
{
    int r;
    if (i == 0)
    {
        r = sub_800A8FE0();
    }
    else
    {
        r = sub_800A7CFC(i - 1);
    }
    return r;
}

// Matched
extern int sub_800A8EC4(int* p);
extern int sub_800A7D40(int a, int* p);
int sub_800BBB18(int* p)
{
    int r;
    int v = *p;
    if (v == 0)
    {
        r = sub_800A8EC4(p);
    }
    else
    {
        r = sub_800A7D40(v - 1, p);
    }
    return r;
}

// Matched
extern int sub_800A9008(int* p);
extern int sub_800A80C4(int a, int* p);
int sub_800BBB5C(int* p)
{
    int r;
    int v = *p;
    if (v == 0)
    {
        r = sub_800A9008(p);
    }
    else
    {
        r = sub_800A80C4(v - 1, p);
    }
    return r;
}

EvVecEventfnc* sub_800BBBA0(int i)
{
    EvVecEventfnc* r;
    if (i == 0)
    {
        r = (EvVecEventfnc*)&levantPos_8008BD18.pos;
    }
    else
    {
        r = sub_800A7940(i - 1);
    }
    return r;
}

SVECTOR* sub_800BBBD0(int i)
{
    SVECTOR* r;
    if (i == 0)
    {
        r = &levantRot_8008BD24;
    }
    else
    {
        r = sub_800A7984(i - 1);
    }
    return r;
}

EvVecEventfnc* sub_800BBC00(EvCtxEventfnc* c, int idx, int mode)
{
    if (mode == 1)
    {
        EvVecEventfnc* v = sub_800BBBA0(idx);
        c->vec3C_3C[idx].x_0 = v->x_0;
        c->vec3C_3C[idx].y_4 = v->y_4;
        c->vec3C_3C[idx].z_8 = v->z_8;
    }
    return &c->vec3C_3C[idx];
}

EvVecEventfnc* sub_800BBC80(EvCtxEventfnc* c, int idx, int mode)
{
    if (mode == 1)
    {
        EvVecEventfnc* v = sub_800BBBA0(idx);
        SVECTOR* r = sub_800BBBD0(idx);
        c->vec78_78[idx].x_0 = v->x_0 + name_80084540[r->vy & 0xFFF] * 100 / 4096;
        c->vec78_78[idx].y_4 = r->vy;
        c->vec78_78[idx].z_8 = v->z_8 + name_80084540[(r->vy + 0x400) & 0xFFF] * 100 / 4096;
    }
    return &c->vec78_78[idx];
}

void sub_800BBDA0(int a, int b)
{
    if (b == 1)
    {
        dword_800AEBD4 |= a;
    }
    else
    {
        dword_800AEBD4 &= ~a;
    }
}

int sub_800BBDD8(int a)
{
    return (~dword_800AEBD4 & a) == 0;
}

int sub_800BBDF4(EvCtxEventfnc* c)
{
    if (c->ent_120 != 0)
    {
        return c->ent_120->f8C_8C;
    }
    return 0;
}

int sub_800BBE18(EvCtxEventfnc* c)
{
    if (c->ent_120 != 0)
    {
        return c->ent_120->f84_84;
    }
    return -1;
}

typedef struct EvPairEventfnc2
{
    int a_0;
    int b_4;
} EvPairEventfnc2;
typedef struct EvMsgCfgEventfnc
{
    int posMode_0;
    unsigned short* pos_4;
    int str_8;
    int fC;
    int f10;
    int f14;
    int mask_18;
    int* list_1C;
    EvPairEventfnc2 pair_20;
    int f28;
    int f2C;
    int f30;
    int f34;
    int f38;
    int f3C;
    int f40;
    int voice_44;
} EvMsgCfgEventfnc;
typedef struct EvItemCfgEventfnc
{
    int posMode_0;
    unsigned short* pos_4;
    int f8;
    char pad_C[0x3C];
    int f48;
    int f4C;
} EvItemCfgEventfnc;
typedef struct EvMsgOptEventfnc
{
    EvPairEventfnc2 pair_A8;
    EvSrcEventfnc src_B0;
    int* list_B8;
    int fBC;
    int fC0;
    int fC4;
    int fC8;
    int fCC;
} EvMsgOptEventfnc;
extern int sub_800A6738(int a);
extern int sub_800A78A8(int a);
extern int sub_800A78F4(int a);
extern int OpenMessageWindow_8003422C(EvMsgCfgEventfnc* cfg);
extern int OpenItemMessageWindow_80035AC8(EvItemCfgEventfnc* cfg);
int* sub_800BC560(int* p);
int sub_800BC58C(int* p);
int sub_800BC5C8(int a, int b);
void sub_800BC6C4(char* base, EvSrcEventfnc* src, int n);

#if 0
// Not matched (register allocation): list/bc/c0/c4/c8/cc are spilled scalars as in the original, but here list keeps
// $fp and mask is spilled, so mask/ret/pos/skip sit one callee-saved register off (orig s5/s6/s7/fp) and list's stack
// slot moves; control flow, the double store of c8 and the call sequence match
int sub_800BBE3C(EvCtxEventfnc* c)
{
    EvMsgCfgEventfnc m;
    EvItemCfgEventfnc it;
    EvPairEventfnc2 pair;
    EvSrcEventfnc src;
    int* list;
    int bc;
    int c0;
    int c4;
    int c8;
    int cc;
    int mode;
    EvInsEventfnc* pc;
    int posMode;
    int str;
    int mask;
    int ret;
    unsigned short* pos;
    int skip;
    EvVoiceEventfnc* v;
    int x;
    int fl;
    ret = 0;
    str = ret;
    mask = ret;
    list = 0;
    bc = 1;
    c0 = 0;
    c4 = 0;
    cc = 1;
    skip = (settingsFlags_8008B58C.word & 7) != 3;
    c8 = settingsFlags_8008B58C.word & 0x18;
    pc = c->pc_8;
    c8 = c8 == 0x18;
    pos = (unsigned short*)ret;
    if (pc->op_0 == 0x3E)
    {
        mode = 2;
    }
    else if (pc->op_0 == 0x3C || pc->op_0 == 0x3D)
    {
        mode = 1;
    }
    else if (pc->op_0 == 0x3B)
    {
        if (pc->c_C == -1)
        {
            str = sub_800BBDF4(c);
        }
        else
        {
            str = sub_800A6738(pc->c_C);
        }
        mode = 3;
    }
    else if (pc->op_0 == 0x39 || pc->op_0 == 0x3A)
    {
        mask = 0;
        mode = 0;
        str = sub_800A6738(pc->c_C);
        list = sub_800BC560((int*)str);
        mask = sub_800BC58C(list) & ~c->f114_114;
    }
    else
    {
        mode = mask;
        list = 0;
        str = sub_800A6738(pc->c_C);
    }
    if (*(short*)&c->f100_100 != -1 && *(short*)&c->f102_102 != -1)
    {
        posMode = 0;
        pos = &c->f100_100;
    }
    else
    {
        posMode = c->f104_104;
        if (posMode < 0)
        {
            posMode = !(pc->op_0 == 0x39 || pc->op_0 == 0x3A) << 1;
        }
    }
    if (pc->op_0 >= 0x37 && pc->op_0 < 0x3B)
    {
        pair.a_0 = 1;
        pair.b_4 = pc->a_4;
        bc = sub_800BC5C8(pc->a_4, pc->b_8);
    }
    else if (pc->op_0 == 0x3B)
    {
        bc = 1;
        pair.a_0 = 0;
        pair.b_4 = -1;
    }
    fl = c->f108_108;
    if (fl & 1)
    {
        skip = 0;
    }
    if (fl & 2)
    {
        c4 = 1;
    }
    if (fl & 4)
    {
        c8 = 1;
    }
    if (fl & 8)
    {
        c0 = 1;
    }
    if (fl & 0x10)
    {
        cc = 0;
    }
    if (mode == 0)
    {
        m.posMode_0 = posMode;
        m.pos_4 = pos;
        m.str_8 = str;
        m.f10 = skip;
        m.mask_18 = mask;
        m.f14 = cc;
        m.list_1C = list;
        m.pair_20 = pair;
        m.f28 = bc;
        m.f30 = c0;
        m.f34 = c4;
        m.f38 = c8;
        m.f3C = 0;
        m.f40 = 0;
        m.fC = sub_800A78A8(pc->a_4 - 1);
        m.f2C = sub_800A78F4(pc->a_4 - 1);
        v = dword_800AEBF0;
        m.voice_44 = 0;
        if (v != 0)
        {
            for (; v->xa_2.a_0 >= 0; v++)
            {
                if (dword_800AEBE8 == v->id_0)
                {
                    m.voice_44 = 1;
                    break;
                }
            }
        }
        ret = OpenMessageWindow_8003422C(&m);
    }
    else if (mode == 1)
    {
        it.posMode_0 = posMode;
        it.pos_4 = pos;
        it.f8 = 0;
        it.f48 = pc->b_8;
        it.f4C = 0;
        x = pc->c_C;
        if (x == 0)
        {
            x = sub_800BBDF4(c);
        }
        sub_800BC6C4((char*)&it, (EvSrcEventfnc*)x, pc->a_4);
        ret = OpenItemMessageWindow_80035AC8(&it);
    }
    else if (mode == 2)
    {
        it.posMode_0 = posMode;
        it.pos_4 = pos;
        it.f8 = 0;
        it.f48 = pc->b_8;
        it.f4C = 0;
        x = pc->a_4;
        if (x == -1)
        {
            x = sub_800BBE18(c);
        }
        src.a_0 = pc->c_C;
        src.b_2 = x;
        src.c_4 = 1;
        sub_800BC6C4((char*)&it, &src, 1);
        ret = OpenItemMessageWindow_80035AC8(&it);
    }
    else if (mode == 3)
    {
        it.posMode_0 = posMode;
        it.pos_4 = pos;
        it.f8 = 0;
        it.f48 = 0xB;
        it.f4C = str;
        sub_800BC6C4((char*)&it, 0, 0);
        ret = OpenItemMessageWindow_80035AC8(&it);
    }
    if (ret == 0)
    {
        return 0;
    }
    c->f118_118 = 1;
    c->f100_100 = -1;
    c->f102_102 = -1;
    c->f11C_11C = ret;
    c->f104_104 = -1;
    c->f108_108 = 0;
    return 1;
}
#endif

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BBE3C);

int sub_800BC2B4(EvCtxEventfnc* c)
{
    EvMsgInfoEventfnc info;
    unsigned int f;
    int i;
    EvXaEventfnc* k;
    SaveData* s;
    if (c->flags_0 & 0x80)
    {
        c->flags_0 &= ~0x80;
        return 1;
    }
    if (c->flags_0 & 2)
    {
        if (!sub_800349B4(c->f11C_11C, &info))
        {
            return 0;
        }
        if (c->flags_0 & 0x100)
        {
            if (XaRequestStop_80043524())
            {
                c->flags_0 &= ~0x100;
            }
        }
        sub_800A67B4(c);
        f = c->flags_0;
        c->flags_0 = f & ~2;
        if (!info.fC_C)
        {
            return 0;
        }
        if (f & 0x40)
        {
            c->flags_0 = (c->flags_0 & ~0x40) | 0x80;
        }
        if (info.f8_8)
        {
            c->fEC_EC = info.s2_2;
        }
        sub_80034A84(c->f11C_11C);
        dword_800AEBE8 = 0x8000;
        dword_800AEBEC = 0;
        c->f118_118 = 0;
        return 1;
    }
    if (dword_800AEBF0)
    {
        k = 0;
        for (i = 0; dword_800AEBF0[i].xa_2.a_0 >= 0; i++)
        {
            if (dword_800AEBE8 == dword_800AEBF0[i].id_0 && sub_80034ADC(c->f11C_11C, dword_800AEBF0[i].sub_1))
            {
                k = &dword_800AEBF0[i].xa_2;
            }
        }
        if (saveData_8008B570.settings_1C.bits.i_22 == 1 && k && dword_800AEBEC != k)
        {
            dword_800AEBEC = k;
            XaRequestPlay_80043564(k->a_0, k->b_2, k->c_4);
            c->flags_0 |= 0x100;
        }
    }
    if (sub_80034A30(c->f11C_11C))
    {
        s = &saveData_8008B570;
        if (s->settings_1C.bits.b_3 == 1 || XaIsIdle_80043584())
        {
            if (s->settings_1C.bits.c_4 == 1 || !c->f18_18)
            {
                sub_80034A68(c->f11C_11C);
                c->flags_0 |= 2;
            }
        }
    }
    return 0;
}

int* sub_800BC560(int* p)
{
    int n = 0;
    do
    {
        n++;
        if (*p != 0)
        {
            n = 0;
        }
        p++;
    } while (n != 2);
    return p;
}

int sub_800BC58C(int* p)
{
    int m = 0;
    int i;
    for (i = 0; *p != 0; p++, i++)
    {
        m |= 1 << i;
    }
    return m;
}

int sub_800BC5C8(int a, int b)
{
    unsigned short v[3];
    short r1[4];
    short r2[4];
    short tmp[4];
    unsigned short* p = (unsigned short*)sub_800BBBA0(a);
    unsigned short* q;
    v[0] = p[0];
    v[1] = p[2];
    v[2] = p[4];
    v[0] -= word_8008D600[0];
    v[1] -= word_8008D600[2];
    v[2] -= word_8008D600[4];
    sub_8005BBC8(v, r1, tmp, tmp);
    q = (unsigned short*)sub_800BBBA0(b);
    v[0] = q[0];
    v[1] = q[2];
    v[2] = q[4];
    v[0] -= word_8008D600[0];
    v[1] -= word_8008D600[2];
    v[2] -= word_8008D600[4];
    sub_8005BBC8(v, r2, tmp, tmp);
    return r1[0] < r2[0];
}

#if 0
// Not matched: loop induction variables are allocated differently (the original strength-reduces only the slot offset)
void sub_800BC6C4(char* base, EvSrcEventfnc* src, int n)
{
    int local[8];
    int i;
    int off = 0xC;
    EvSlotEventfnc* p;
    memset(local, 0, 0x20);
    local[0] = 2;
    local[5] = 3;
    for (i = 0; i < 3; i++, off += 0x14)
    {
        p = (EvSlotEventfnc*)(base + off);
        if (i < n)
        {
            p->f0_0 = src->a_0;
            p->f4_4 = src->b_2;
            p->f8_8 = src->c_4;
        }
        else
        {
            p->f0_0 = -1;
            p->f4_4 = 0;
            p->f8_8 = 0;
        }
        if (p->f0_0 >= 0)
        {
            p->fC_C = local[p->f0_0];
            p->f10_10 = p->f4_4;
        }
        src++;
    }
}
#endif

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BC6C4);

void sub_800BC7A0(EvCtxEventfnc* c)
{
}

void sub_800BC7A8(int a)
{
    EvGfxArgEventfnc t;
    if (dword_800AEB7C != 2)
    {
        sub_800A5854();
    }
    if (dword_800AEB80.f4_4)
    {
        ListFreeAll_8003FEC8(&dword_800AEB80.f4_4);
    }
    t.g_0 = &dword_800AEB80;
    t.s_4[5] = 0;
    t.s_4[4] = 0;
    t.s_4[3] = 0;
    t.s_4[2] = 0;
    t.s_4[1] = 0;
    t.s_4[0] = 0;
    t.f10_10 = 0;
    ListInit_8003FDB0(&dword_800AEB80.f4_4);
    OnEffectFileLoaded_80020F5C(&t, a);
    if (dword_800AEB80.f2C_2C)
    {
        sub_800A5804(0);
    }
}

#if 0
// Not matched: src/size are allocated to $s1/$s0 (original $s0/$s1); the rest is identical. The global is wrapped in a struct so the stores through it reload it (as the original does)
typedef struct EvBlobPtrEventfnc
{
    int* p_0;
} EvBlobPtrEventfnc;
extern EvBlobPtrEventfnc dword_800AEBBC;
void LoadRelocBlob_800BC854(int* src)
{
    int size;
    int n;
    int i;
    int j;
    int m;
    int* p;
    int* e;
    size = *src++;
    if (dword_800AEBBC.p_0)
    {
        ListFree_8003FE38(dword_80091C10, dword_800AEBBC.p_0);
        dword_800AEBBC.p_0 = 0;
    }
    dword_800AEBBC.p_0 = ListAlloc_8003FDC0(dword_80091C10, size);
    MemCopy_800403E8(dword_800AEBBC.p_0, src, size);
    n = dword_800AEBBC.p_0[0];
    for (i = 0; i < n; i++)
    {
        e = (int*)((char*)dword_800AEBBC.p_0 + (i * 8 + 4));
        *e = (int)dword_800AEBBC.p_0 + *e;
    }
    for (i = 0; i < n; i++)
    {
        e = (int*)((char*)dword_800AEBBC.p_0 + (i * 8 + 4));
        m = e[1];
        p = (int*)e[0];
        for (j = 0; j < m; j++, p++)
        {
            if (*p == -1)
            {
                *p = 0;
            }
            else
            {
                *p = (int)dword_800AEBBC.p_0 + *p;
            }
        }
    }
}
#endif

INCLUDE_OVERLAY_ASM(eventfnc, LoadRelocBlob_800BC854);

void sub_800BC98C(int* a)
{
    if (dword_800AEBC0.sprts_0)
    {
        ListFree_8003FE38(dword_80091C10, dword_800AEBC0.sprts_0);
        dword_800AEBC0.sprts_0 = 0;
    }
    if (dword_800AEBC0.tpages_4)
    {
        ListFree_8003FE38(dword_80091C10, dword_800AEBC0.tpages_4);
        dword_800AEBC0.tpages_4 = 0;
    }
    LoadTiy_80028E74(&dword_800AEBC0.sprts_0, 0, &dword_800AEBC0.tpages_4, a, (int)dword_80091C10);
}

#if 0
// Not matched: a/b land in $s1/$s0 in the original, swapped here (param types, temporaries, call-embedded assignment tried)
extern int dword_800AEBC8;
void sub_800BCA18(unsigned int* a, unsigned int* b)
{
    unsigned int* r = ListAlloc_8003FDC0(dword_80091C10);
    dword_800AEBC8 = (int)r;
    MemCopy_800403E8(r, a, (unsigned int)b);
}
#endif

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BCA18);

void sub_800BCA68(int a)
{
    if (dword_800AEBCC[1] != 0)
    {
        sub_80026DE8(&dword_800AEBCC[1], dword_800AEBCC[0], dword_80091C10);
        dword_800AEBCC[0] = 0;
    }
    dword_800AEBCC[0] = sub_80026D6C((int*)a);
    sub_80026D78(&dword_800AEBCC[1], dword_800AEBCC[0], dword_80091C10);
    sub_80026E74(dword_800AEBCC[1], a, dword_80091C10);
}

void sub_800BCB00(TaskEventfnc* t, int* x)
{
    x[0] = 0;
    x[1] = 0x1D;
    sub_800BCB3C(t, x);
    t->next_8 = sub_800BCB3C;
}
