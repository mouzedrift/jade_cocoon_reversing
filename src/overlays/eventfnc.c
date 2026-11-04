// EVENTFNC.BIN, source file 1 of 2
#include "eventfnc.h"
#include "actor.h"

int dword_800B6D00 SDATA = 41;
const char aAssertionFaile_800B6D04[] = "Assertion failed: file \"%s\", line %d\n";
const char aColiC_800B6D2C[8] = "COLI.C\000$";

// FindLevantMesh_800B80C8 is inlined; the edge points are written through `(edgePts + i * 2)->` so the address is
// expanded as an address sum (index term first), as in the original.
// Matched
int CollideLevantWithMap_800B6DD4(EvEntity* ent)
{
    EvSVec edgePts[4];
    int normal[4];
    int ret;
    int i;
    MapVtx* verts;
    int angle;
    ret = 0;
    CollideWithMapEnts_800B82C8(&levantPos_8008BD18.pos.x, (int*)&ent->pos_48, mapState_8008B500.ents_14,
                 mapState_8008B500.entFlags_18, mapState_8008B500.nEnts_10);
    ent->f8C_8C = -1;
    ent->f88_88 = -1;
    for (i = 0;; i++)
    {
        if (EvFindLevantMesh(ent))
        {
            break;
        }
        if (i >= 2)
        {
            if (FindDuplicatePoint_800B8028(&levantPos_8008BD18.pos.x, edgePts))
            {
                return ret;
            }
            printf(aAssertionFaile_800B6D04, aColiC_800B6D2C, 153);
            exit(1);
        }
        SlideOffEdge_800B8220(&levantPos_8008BD18.pos.x, (int)&ent->pos_48, (int)&mapState_8008B500.meshes_C[ent->f84_84], &ent->f88_88, &ent->f8C_8C, normal);
        verts = mapState_8008B500.meshes_C[ent->f84_84].tris_4[ent->f88_88].v_0;
        (edgePts + i * 2)->x_0 = verts[ent->f8C_8C % 3].x_0;
        (edgePts + i * 2)->y_2 = verts[ent->f8C_8C % 3].y_2;
        (edgePts + i * 2)->z_4 = verts[ent->f8C_8C % 3].z_4;
        (edgePts + i * 2 + 1)->x_0 = verts[(ent->f8C_8C + 1) % 3].x_0;
        (edgePts + i * 2 + 1)->y_2 = verts[(ent->f8C_8C + 1) % 3].y_2;
        (edgePts + i * 2 + 1)->z_4 = verts[(ent->f8C_8C + 1) % 3].z_4;
    }
    GetTriHeight_800B83E4(&levantPos_8008BD18.pos.x, &mapState_8008B500.meshes_C[ent->f84_84], ent->f80_80);
    if (ent->f88_88 == -1)
    {
        return ret;
    }
    if (ent->f8C_8C == -1)
    {
        return ret;
    }
    angle = ((unsigned short)levantPos_8008BD18.rot.vy - ((int (*)(long, long))ratan2_8003B548)(normal[0], normal[2])) & 0xFFF;
    if (angle > 0xC00 || (angle > 0x400 && angle < 0x800))
    {
        ret = 1;
    }
    else
    {
        ret = -1;
    }
    return ret;
}

int CollideWithMap_800B716C(EvVec* pos, int* prevPos, SVECTOR* rot)
{
    EvSVec edgePts[4];
    int normal[4];
    int tri;
    int edgeTri;
    int edge;
    int i;
    int angle;
    MapVtx* verts;
    EvSVec* pt;
    EvSVec* pt2;
    if (!CollideWithMapEnts_800B82C8((int*)pos, prevPos, mapState_8008B500.ents_30, mapState_8008B500.entFlags_34, mapState_8008B500.nEnts_2C))
    {
        return 3;
    }
    edge = -1;
    edgeTri = -1;
    i = 0;
    for (;;)
    {
        if (EvFindTri(&tri, &mapState_8008B500, pos))
        {
            break;
        }
        if (i >= 2)
        {
            if (FindDuplicatePoint_800B8028((int*)pos, edgePts))
            {
                return 3;
            }
            printf(aAssertionFaile_800B6D04, aColiC_800B6D2C, 255);
            exit(1);
        }
        SlideOffEdge_800B8220((int*)pos, (int)prevPos, (int)mapState_8008B500.mesh_28, &edgeTri, &edge, normal);
        verts = mapState_8008B500.mesh_28->tris_4[edgeTri].v_0;
        pt = (EvSVec*)(i * 16 + (int)edgePts); // &edgePts[i * 2]; that form allocates registers differently
        pt->x_0 = verts[edge % 3].x_0;
        pt->y_2 = verts[edge % 3].y_2;
        pt->z_4 = verts[edge % 3].z_4;
        pt2 = pt + 1;
        pt2->x_0 = verts[(edge + 1) % 3].x_0;
        pt2->y_2 = verts[(edge + 1) % 3].y_2;
        pt2->z_4 = verts[(edge + 1) % 3].z_4;
        i++;
    }
    GetTriHeight_800B83E4((int*)pos, mapState_8008B500.mesh_28, tri);
    if (i == 2)
    {
        return 3;
    }
    if (edgeTri == -1)
    {
        return 0;
    }
    if (edge == -1)
    {
        return 0;
    }
    angle = ((unsigned short)rot->vy - ((int (*)(long, long))ratan2_8003B548)(normal[0], normal[2])) & 0xFFF;
    if (angle > 0xC00 || (angle > 0x400 && angle < 0x800))
    {
        return 1;
    }
    return 2;
}

// clears the pad_6 edge flag of every vertex, then sets it to -1 where the edge (v, v+1) of a triangle is shared
// (same x/z, either direction) with another triangle of the same mesh. The vertices are re-indexed in every test
// (a named pointer to t's vertex gets its loads hoisted out of the b loop)
// Matched
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

int FindTriAtXZ_800B76B8(MapMesh* mesh, EvVec* pos)
{
    VECTOR edge;
    VECTOR rel;
    int i;
    int minx;
    int maxx;
    int minz;
    int maxz;
    for (i = 0; i < mesh->nTris_0; i++)
    {
        if (mesh->tris_4[i].v_0[0].x_0 > mesh->tris_4[i].v_0[1].x_0)
        {
            maxx = mesh->tris_4[i].v_0[0].x_0;
            minx = mesh->tris_4[i].v_0[1].x_0;
        }
        else
        {
            minx = mesh->tris_4[i].v_0[0].x_0;
            maxx = mesh->tris_4[i].v_0[1].x_0;
        }
        if (maxx < mesh->tris_4[i].v_0[2].x_0)
        {
            maxx = mesh->tris_4[i].v_0[2].x_0;
        }
        else if (mesh->tris_4[i].v_0[2].x_0 < minx)
        {
            minx = mesh->tris_4[i].v_0[2].x_0;
        }
        if (mesh->tris_4[i].v_0[0].z_4 > mesh->tris_4[i].v_0[1].z_4)
        {
            maxz = mesh->tris_4[i].v_0[0].z_4;
            minz = mesh->tris_4[i].v_0[1].z_4;
        }
        else
        {
            minz = mesh->tris_4[i].v_0[0].z_4;
            maxz = mesh->tris_4[i].v_0[1].z_4;
        }
        if (maxz < mesh->tris_4[i].v_0[2].z_4)
        {
            maxz = mesh->tris_4[i].v_0[2].z_4;
        }
        else if (mesh->tris_4[i].v_0[2].z_4 < minz)
        {
            minz = mesh->tris_4[i].v_0[2].z_4;
        }
        if (pos->x_0 < minx || maxx < pos->x_0 || pos->z_8 < minz || maxz < pos->z_8)
        {
            continue;
        }
        edge.vx = mesh->tris_4[i].v_0[1].x_0 - mesh->tris_4[i].v_0[0].x_0;
        edge.vz = mesh->tris_4[i].v_0[1].z_4 - mesh->tris_4[i].v_0[0].z_4;
        rel.vx = pos->x_0 - mesh->tris_4[i].v_0[0].x_0;
        rel.vz = pos->z_8 - mesh->tris_4[i].v_0[0].z_4;
        if (edge.vx * rel.vz - edge.vz * rel.vx > 0)
        {
            continue;
        }
        edge.vx = mesh->tris_4[i].v_0[2].x_0 - mesh->tris_4[i].v_0[1].x_0;
        edge.vz = mesh->tris_4[i].v_0[2].z_4 - mesh->tris_4[i].v_0[1].z_4;
        rel.vx = pos->x_0 - mesh->tris_4[i].v_0[1].x_0;
        rel.vz = pos->z_8 - mesh->tris_4[i].v_0[1].z_4;
        if (edge.vx * rel.vz - edge.vz * rel.vx > 0)
        {
            continue;
        }
        edge.vx = mesh->tris_4[i].v_0[0].x_0 - mesh->tris_4[i].v_0[2].x_0;
        edge.vz = mesh->tris_4[i].v_0[0].z_4 - mesh->tris_4[i].v_0[2].z_4;
        rel.vx = pos->x_0 - mesh->tris_4[i].v_0[2].x_0;
        rel.vz = pos->z_8 - mesh->tris_4[i].v_0[2].z_4;
        if (edge.vx * rel.vz - edge.vz * rel.vx <= 0)
        {
            return i;
        }
    }
    return -1;
}

// finds the first unshared edge (pad_6 == 0) of mesh m crossed by the segment p-q in x/z and returns it in
// *tri / *edge, unless it is the one already there
// Matched
void FindCrossedEdge_800B79E0(MapMesh* m, int* p, int* q, int* tri, int* edge)
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

void SlideAlongEdge_800B7E40(int* pos, int mesh, int tri, int edge, int* out)
{
    int triAddr = (int)&((MapMesh*)mesh)->tris_4[tri];
    MapVtx* v0 = (MapVtx*)(((edge + 1) % 3) * 8 + triAddr);
    MapVtx* v1 = (MapVtx*)((edge % 3) * 8 + triAddr);
    int dir[3];
    int rel[3];
    int len;
    int proj;
    dir[0] = v0->x_0 - v1->x_0;
    dir[1] = v0->y_2 - v1->y_2;
    dir[2] = v0->z_4 - v1->z_4;
    rel[0] = pos[0] - v1->x_0;
    rel[1] = pos[1] - v1->y_2;
    rel[2] = pos[2] - v1->z_4;
    dir[1] = 0;
    len = ISqrt_8003B918(dir[0] * dir[0] + dir[2] * dir[2]);
    dir[0] = (dir[0] << 12) / len;
    dir[2] = (dir[2] << 12) / len;
    proj = (dir[0] * rel[0] + dir[2] * rel[2]) / 4096;
    pos[0] = v1->x_0 + proj * dir[0] / 4096;
    pos[2] = v1->z_4 + proj * dir[2] / 4096;
    out[0] = dir[0];
    out[1] = 0;
    out[2] = dir[2];
}

int FindDuplicatePoint_800B8028(int* out, EvSVec* pts)
{
    int i;
    int j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (i != j && pts[i].x_0 == pts[j].x_0 && pts[i].y_2 == pts[j].y_2 && pts[i].z_4 == pts[j].z_4)
            {
                out[0] = pts[i].x_0;
                out[1] = pts[i].y_2;
                out[2] = pts[i].z_4;
                return 1;
            }
        }
    }
    return 0;
}

int FindLevantMesh_800B80C8(EvEntity* ent)
{
    unsigned int i;
    unsigned int mesh = ent->f84_84;
    int tri;
    for (i = 0; i < mapState_8008B500.nMeshes_4; i++, mesh++)
    {
        mesh %= mapState_8008B500.nMeshes_4;
        tri = FindTriAtXZ_800B76B8(&mapState_8008B500.meshes_C[mesh], (EvVec*)&levantPos_8008BD18.pos);
        if (tri >= 0)
        {
            ent->f80_80 = tri;
            if (ent->f84_84 != mesh)
            {
                ent->f84_84 = mesh;
            }
            return 1;
        }
    }
    return 0;
}

int FindMeshAtPos_800B8184(EvVec* pos, unsigned int mesh)
{
    unsigned int i;
    for (i = 0; i < mapState_8008B500.nMeshes_4; i++)
    {
        mesh %= mapState_8008B500.nMeshes_4;
        if (FindTriAtXZ_800B76B8(&mapState_8008B500.meshes_C[mesh], pos) >= 0)
        {
            return mesh;
        }
        mesh++;
    }
    return -1;
}

void SlideOffEdge_800B8220(int* pos, int prevPos, int mesh, int* tri, int* edge, int* dir)
{
    FindCrossedEdge_800B79E0((MapMesh*)mesh, pos, (int*)prevPos, tri, edge);
    SlideAlongEdge_800B7E40(pos, mesh, *tri, *edge, dir);
    pos[0] += dir[2] >> 10;
    pos[2] -= dir[0] >> 10;
}

int CollideWithMapEnts_800B82C8(int* pos, int* prevPos, MapMesh* ents, unsigned char* flags, int n)
{
    int i;
    int tri;
    int edge;
    int dir[4];
    for (i = 0; i < n; i++)
    {
        if (flags[i])
        {
            edge = -1;
            tri = -1;
            FindCrossedEdge_800B79E0(&ents[i], prevPos, pos, &tri, &edge);
            if (tri != -1 && edge != -1)
            {
                SlideAlongEdge_800B7E40(pos, (int)&ents[i], tri, edge, dir);
                pos[0] -= dir[2] >> 10;
                pos[2] += dir[0] >> 10;
                return 0;
            }
        }
    }
    return 1;
}

void GetTriHeight_800B83E4(int* pos, MapMesh* mesh, int triIdx)
{
    MapTri* tri = &mesh->tris_4[triIdx];
    pos[1] = (tri->ny_1A * tri->v_0[0].y_2 - tri->nx_18 * (pos[0] - tri->v_0[0].x_0) - tri->nz_1C * (pos[2] - tri->v_0[0].z_4)) / tri->ny_1A;
}

void EncounterSpawnTask_800B844C(EvTaskEntry* task)
{
    SaveData* save;
    EvSpawnTable spawn;
    int i;
    int count;
    if (IsModelLoaderDone_800205D0())
    {
        EvMapEntry*** tbl = mapTable_800B0608;
        save = &saveData_8008B570;
        spawn.f1A_1A = tbl[save->mapId_2E4[0].field_0][save->mapId_2E4[1].field_0][save->mapId_2E4[2].field_2].f6_6;
        spawn.f18_18 = tbl[save->mapId_2E4[0].field_0][save->mapId_2E4[1].field_0][save->mapId_2E4[2].field_0].f6_6;
        count = RollEncounterGroups_800A49CC(tbl[save->mapId_2E4[0].field_0][save->mapId_2E4[1].field_0][save->mapId_2E4[2].field_2].f4_4, spawn.f18_18, &mapSpawns_80091C60, &spawn);
        for (i = 0; i < count; i++)
        {
            SpawnEncounterEnemy_800B8568(spawn.members_0[i], spawn.places_C[i], -1, i);
        }
        task->flags_0 = (task->flags_0 & ~1) | 0x8000;
    }
}

typedef struct EvEnemyGroup
{
    int kind_0; // 0: actors already exist, 1: hide them when reused (GAME's GameEnemy)
    int maxCount_4;
    int f8;
    int fC;
    int f10;
    int idx_14;
    int useMinion_18; // 1: the first member is minion_1C
    UnitStats minion_1C;
    Actor* actor_A4;
    int fA8;
    int fAC;
    EvEnemyMember members_B0[3];
    int fC8;
    int fCC;
    int fD0;
    int z_D4[3];
} EvEnemyGroup;
typedef struct EvLoaderModel
{
    int f0;
    int id_4;
    int pad_8[3];
} EvLoaderModel;
// work area of the model loader task (modelLoaderTask_8008B54C)
typedef struct EvModelLoader
{
    int f0;
    int f4;
    int f8;
    EvLoaderModel ents_C[4];
} EvModelLoader;
// an enemy slot of the GAME overlay (GameEnemySlot): AddEnemySlot_800A17F4 copies the EvEnemyGroup into data_8
typedef struct EvEnemySlot
{
    int f0;
    int aiEvent_4;
    EvEnemyGroup data_8;
} EvEnemySlot;
extern EvEnemySlot* AddEnemySlot_800A17F4(EvEnemyGroup* src, int b);
extern int CreateEnemyAiEvent_800A2D90(Actor* a, UnitStats* b, int c);
extern short defaultBones_80079140[]; // default bone table

// Matched
void SpawnEncounterEnemy_800B8568(EvEncounterMember* members, EvSpawnPlace* place, int aiArg, int index)
{
    ActorDesc desc;
    UnitStats minion;
    EvEnemyGroup group;
    int scale[3];
    unsigned short* id;
    EvLoaderModel* ent;
    int found;
    int i;
    Model* model;
    int k;
    int* p0;
    int* p1;
    int lerp;
    Actor* actor;
    unsigned short* levels;
    EvEnemySlot* slot;
    id = &GetSpeciesModelDesc_80019C70(members->member_0.species_0)->modelId_0;
    found = 0;
    ent = ((EvModelLoader*)modelLoaderTask_8008B54C->entry.buffer)->ents_C;
    for (i = 3; i >= 0; i--)
    {
        if (*id == ent->id_4)
        {
            found = 1;
        }
        ent++;
    }
    if (found)
    {
        model = AcquireLoaderModel_80020734(*id);
        k = InitMinionData_8001900C(&minion, &members->member_0.species_0);
        desc.modelId_0 = *id;
        desc.kind_4 = 0;
        desc.pos_8[0] = place->pos_0[0];
        desc.pos_8[1] = place->pos_0[1];
        desc.pos_8[2] = place->pos_0[2];
        desc.rot_14[0] = 0;
        desc.rot_14[1] = place->rotY_C;
        desc.rot_14[2] = 0;
        desc.clutRow_1C = 0;
        desc.animIdx_20 = 1;
        desc.frame_24 = -1;
        desc.frameSpeed_28 = 0x1000;
        desc.blendDiv_2C = 4;
        desc.visible_30 = 1;
        desc.bones_34 = defaultBones_80079140;
        if (k >= 4)
        {
            desc.baseScale_38 = GetModelBaseScale_80024E90(model, k);
        }
        else
        {
            p0 = GetModelBaseScale_80024E90(model, k);
            p1 = GetModelBaseScale_80024E90(model, k + 1);
            lerp = GetUnitRank_80019AD0(&minion);
            lerp = ((p1[0] - p0[0]) * lerp) / 4096;
            scale[0] = p0[0] + lerp;
            scale[1] = p0[1] + lerp;
            scale[2] = p0[2] + lerp;
            desc.baseScale_38 = scale;
        }
        desc.boneScale_3C = GetModelBoneScale_80024EC8(model, k);
        desc.anims_40 = GetModelActorAnims_80024E38(model);
        desc.effectTbl_44 = GetModelEffectTable_80024E64(model);
        desc.hasMatrices_4C = 0;
        actor = CreateActor_8001D45C(&desc);
        levels = GetModelBoneGroupLevels_80024F00(model, k);
        SetBoneGroupFlags_80019B14(actor->bones_134, levels, GetModelBoneGroupFlags_80024F38(model, k));
        group.kind_0 = 2;
        group.maxCount_4 = 3;
        group.f8 = 1;
        group.fC = 1;
        group.f10 = 1;
        group.idx_14 = index;
        group.useMinion_18 = 1;
        group.minion_1C = minion;
        group.actor_A4 = actor;
        group.fA8 = 0;
        group.fAC = 0;
        group.members_B0[0] = members[0].member_0;
        group.members_B0[1] = members[1].member_0;
        group.members_B0[2] = members[2].member_0;
        group.fC8 = 0;
        group.fCC = 0;
        group.fD0 = 0;
        group.z_D4[0] = members[0].z;
        group.z_D4[1] = members[1].z;
        group.z_D4[2] = members[2].z;
        slot = AddEnemySlot_800A17F4(&group, 0);
        slot->aiEvent_4 = CreateEnemyAiEvent_800A2D90(actor, &slot->data_8.minion_1C, aiArg);
    }
}

// work area of the encounter task (encounterTask_8008D674, EncounterSpawnTask_800B844C)
typedef struct EvEncounterWork
{
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
} EvEncounterWork;
void StartEncounter_800B88A4(int ids)
{
    EventEntry* entry;
    EvEncounterWork* work;
    if (ids)
    {
        LoadEncounterModels_800B8940((int*)ids);
        eventDispatchHalt_8008B540 = 1;
    }
    entry = &encounterTask_8008D674->entry;
    entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
    work = (EvEncounterWork*)entry->buffer;
    work->f8 = 0;
    work->fC = 0;
    work->f10 = 0;
    work->f14 = 0;
    entry->cb_8 = (EventEntryFn)EncounterSpawnTask_800B844C;
    ResetEncounter_800A170C();
    ClearEnemySlots_800A1794();
}

void EmptyLoop_800B8928()
{
    int i;
    for (i = 0x2a; i >= 0; i--)
    {
    }
}


void LoadEncounterModels_800B8940(int* ids)
{
    int i = 0;
    int* id = ids;
    for (; i < 3; i++)
    {
        MinionModelDesc* desc = GetSpeciesModelDesc_80019C70(*id++);
        RequestLoaderModel_800206A0(desc->modelId_0, desc->field_2 << 1, 3, -1);

    }
    StartModelLoader_8002056C();
}

int EvCmdNop_800B89A8(EvScriptCtx* ctx)
{
    ctx->pc_8++;
    return 1;
}

int EvCmdWaitButton_800B89C0(EvScriptCtx* ctx)
{
    if (padPressed_8009194C & 0x100)
    {
        ctx->pc_8++;
        return 1;
    }
    return 0;
}

int EvCmdEnd_800B89F4(EvScriptCtx* ctx)
{
    if (EvCmdEndScene_800B8A34(ctx))
    {
        ctx->flags_0 |= 1;
    }
    return 0;
}

int EvCmdEndScene_800B8A34(EvScriptCtx* ctx)
{
    EvActorCmd cmd;
    int i;
    switch (ctx->step_B8)
    {
    case 0:
        if (ctx->animActors_1C & ctx->heldActors_14)
        {
            cmd.actor_0 = ctx->animActors_1C;
            cmd.kind_4 = 4;
            cmd.arg_C = ctx->idleAnims_24[ctx->pc_8->b_8];
            if (!SendActorCmdMask_800BB990(ctx, &cmd, 1, 0))
            {
                return 0;
            }
        }
        ctx->step_B8++;
    case 1:
        if (ctx->busyActors_18)
        {
            return 0;
        }
        ctx->step_B8++;
    case 2:
        for (i = 0; i < 5; i++)
        {
            int bit = 1 << i;
            if (ctx->heldActors_14 & bit)
            {
                if (i == 0)
                {
                    ReleaseLevantControl_800A8E38();
                }
                else
                {
                    ReleaseFieldMinion_800A785C(i - 1);
                }
                ctx->heldActors_14 &= ~(1 << i);
            }
        }
        if (ctx->heldActors_14 == 0 && (ctx->flags_0 & 0x20))
        {
            ctx->flags_0 &= ~0x20;
            ResumeAllEnemySlots_800A1974();
        }
        if (sceneScriptId_800AEBD8 == ctx->id_10)
        {
            sceneScriptId_800AEBD8 = -1;
        }
        ResetEventCtx_800A5B54(ctx);
        ctx->step_B8 = 0;
        ctx->pc_8++;
        return 1;
    }
    return 0;
}

extern int fieldMode_800B0EC0;
extern int gCtx_800B1260;
extern int GetGameMode_800A6D50(int a);
extern void SuspendAllEnemySlots_800A1904(void);
// Matched
int EvCmdBeginScene_800B8BE8(EvScriptCtx* ctx)
{
    int r;
    if (fieldMode_800B0EC0 != 1)
    {
        return 0;
    }
    if (gCtx_800B1260 != 0)
    {
        return 0;
    }
    if (sceneScriptId_800AEBD8 < 0 || ctx->id_10 == sceneScriptId_800AEBD8)
    {
        r = GetGameMode_800A6D50(0);
        if (r != GetGameMode_800A6D50(2))
        {
            return 0;
        }
        ctx->flags_0 |= 0x20;
        SuspendAllEnemySlots_800A1904();
        sceneScriptId_800AEBD8 = ctx->id_10;
        ctx->pc_8++;
        return 1;
    }
    return 0;
}

int EvCmdSetLoopPoint_800B8CB0(EvScriptCtx* ctx)
{
    EvInstr* p = ctx->pc_8;
    if (p->b_8 != 0)
    {
        ctx->ret_C = p;
        ctx->pc_8 = p + 1;
        ctx->flags_0 |= 0x10;
    }
    else
    {
        ctx->flags_0 &= ~0x10;
        ctx->pc_8++;
    }
    return 1;
}

int EvCmdTakeActors_800B8D08(EvScriptCtx* ctx)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        int bit = 1 << i;
        if (ctx->pc_8->b_8 & bit)
        {
            if (i == 0)
            {
                HoldLevantControl_800A8E0C();
                ResetLevantActorToIdle_800A8DEC();
            }
            else if (HoldFieldMinion_800A7810(i - 1) == 0)
            {
                return 0;
            }
            GetSavedActorPos_800BBC00(ctx, i, 1);
            GetSavedActorFront_800BBC80(ctx, i, 1);
            ctx->heldActors_14 |= 1 << i;
        }
    }
    ctx->pc_8++;
    return 1;
}

int EvCmdReleaseActors_800B8DDC(EvScriptCtx* ctx)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        int bit = 1 << i;
        if ((ctx->heldActors_14 & bit) && (ctx->pc_8->b_8 & bit))
        {
            if (i == 0)
            {
                ReleaseLevantControl_800A8E38();
            }
            else
            {
                ReleaseFieldMinion_800A785C(i - 1);
            }
            ctx->heldActors_14 &= ~(1 << i);
        }
    }
    ctx->pc_8++;
    return 1;
}

int EvCmdGotoLabel_800B8E9C(EvScriptCtx* ctx)
{
    int target = ctx->pc_8[ctx->branch_EC].b_8;
    EvInstr* p = ctx->start_4;
    while (p->op_0 != 3)
    {
        if (p->op_0 == 9 && target == p->b_8)
        {
            ctx->pc_8 = p;
            ctx->branch_EC = 0;
            return 1;
        }
        p++;
    }
    return 0;
}

// Matched
int EvCmdJumpScript_800B8F14(EvScriptCtx* ctx)
{
    EvInstr* p = (EvInstr*)ctx->pc_8[ctx->branch_EC].c_C;
    ctx->branch_EC = 0;
    ctx->pc_8 = p;
    ctx->start_4 = p;
    ctx->ret_C = ctx->pc_8;
    return 1;
}

int EvCmdWait_800B8F44(EvScriptCtx* ctx)
{
    ctx->waitCount_C4++;
    if (ctx->waitCount_C4 >= ctx->pc_8->b_8 + 1)
    {
        ctx->waitCount_C4 = 0;
        ctx->pc_8++;
        return 1;
    }
    return 0;
}

int EvCmdWaitActors_800B8F88(EvScriptCtx* ctx)
{
    if (ctx->busyActors_18 & ctx->pc_8->b_8)
    {
        return 0;
    }
    ctx->pc_8++;
    return 1;
}

int EvCmdSetVar_800B8FB8(EvScriptCtx* ctx)
{
    unsigned int v = ctx->pc_8->b_8;
    int hi = v >> 16;
    int lo = v & 0xFFFF;
    if (ctx->pc_8->a_4 == 0)
    {
        ctx->vars_CC[hi] = lo;
    }
    else
    {
        SetEventVar_800AD16C(hi, lo);
    }
    ctx->pc_8++;
    return 1;
}

int EvCmdPickBranch_800B9020(EvScriptCtx* ctx)
{
    unsigned int a = ctx->pc_8->a_4;
    unsigned int b = ctx->pc_8->b_8;
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
        ctx->branch_EC = r;
        if (idx < 8)
        {
            ctx->vars_CC[idx] = r;
        }
    }
    else
    {
        ctx->branch_EC = ctx->vars_CC[slot];
        if (++ctx->vars_CC[slot] >= mod)
        {
            if (idx)
            {
                ctx->vars_CC[slot] = lo;
            }
            else
            {
                ctx->vars_CC[slot] = mod - 1;
            }
        }
    }
    ctx->pc_8++;
    return 1;
}

int EvCmdCountYanVar_800B9110(EvScriptCtx* ctx)
{
    unsigned int a = ctx->pc_8->a_4;
    unsigned int b = ctx->pc_8->b_8;
    int hi = a >> 16;
    int lo = a & 0xFFFF;
    int hi2 = b >> 16;
    int lo2 = b & 0xFFFF;
    int v = GetEventVar_800AD154(hi);
    ctx->branch_EC = v;
    SetEventVar_800AD16C(hi, v + 1);
    if (GetEventVar_800AD154(hi) >= hi2)
    {
        if (lo2)
        {
            SetEventVar_800AD16C(hi, lo);
        }
        else
        {
            SetEventVar_800AD16C(hi, hi2 - 1);
        }
    }
    ctx->pc_8++;
    return 1;
}

int EvCmdCallHook_800B91CC(EvScriptCtx* ctx)
{
    eventHook_800B1D98(ctx->pc_8->c_C);
    ctx->pc_8++;
    return 1;
}

int EvCmdStartScript_800B9218(EvScriptCtx* ctx)
{
    StartEventScript_800A59D0(ctx->pc_8->c_C);
    ctx->pc_8++;
    return 1;
}

int EvCmdWarpActor_800B9260(EvScriptCtx* ctx)
{
    int* dest = (int*)ctx->pc_8->c_C;
    EvVec* pos = GetActorPos_800BBBA0(ctx->pc_8->a_4);
    SVECTOR* rot = GetActorRot_800BBBD0(ctx->pc_8->a_4);
    int ang;
    if (dest)
    {
        ang = dest[3];
    }
    else
    {
        dest = (int*)GetSavedActorPos_800BBC00(ctx, ctx->pc_8->a_4, 0);
        ang = GetSavedActorFront_800BBC80(ctx, ctx->pc_8->a_4, 0)->y_4;
    }
    pos->x_0 = dest[0];
    pos->y_4 = dest[1];
    pos->z_8 = dest[2];
    rot->vy = ang;
    UpdateCameraFollow_80037918(cameraTask_8008D4A0->entry.buffer);
    SetGeomOffset(display_8008B4D8.w_C / 2 + screenOffset_8008D474[0], display_8008B4D8.h_E / 2 + screenOffset_8008D474[1]);
    ctx->pc_8++;
    return 1;
}

int EvCmdMoveToPoint_800B93A8(EvScriptCtx* ctx)
{
    EvActorCmd cmd;
    EvVec* dest = (EvVec*)ctx->pc_8->c_C;
    cmd.actor_0 = ctx->pc_8->a_4;
    cmd.kind_4 = ctx->pc_8->op_0 != 0x14;
    cmd.x_18 = dest->x_0;
    cmd.y_1C = dest->y_4;
    cmd.z_20 = dest->z_8;
    cmd.field_14 = ctx->pc_8->b_8;
    return SendActorCmd_800BB840(ctx, &cmd, 1, 1);
}

int EvCmdMoveToActor_800B942C(EvScriptCtx* ctx)
{
    EvActorCmd cmd;
    EvVec delta;
    EvVec* from = GetActorPos_800BBBA0(ctx->pc_8->a_4);
    EvVec* target;
    int ang;
    if (ctx->pc_8->a_4 == ctx->pc_8->b_8)
    {
        target = GetSavedActorPos_800BBC00(ctx, ctx->pc_8->a_4, 0);
    }
    else
    {
        target = GetActorPos_800BBBA0(ctx->pc_8->b_8);
    }
    delta.x_0 = from->x_0 - target->x_0;
    delta.z_8 = from->z_8 - target->z_8;
    ang = ratan2_8003B548(delta.x_0, delta.z_8);
    cmd.actor_0 = ctx->pc_8->a_4;
    cmd.kind_4 = ctx->pc_8->op_0 != 0x15;
    cmd.x_18 = target->x_0 + sinTable_80084540[ang & 0xFFF] * 200 / 4096;
    cmd.y_1C = target->y_4;
    cmd.z_20 = target->z_8 + sinTable_80084540[(ang + 0x400) & 0xFFF] * 200 / 4096;
    cmd.field_14 = ctx->pc_8->c_C;
    return SendActorCmd_800BB840(ctx, &cmd, 1, 1);
}

int EvCmdTurnToPoint_800B95BC(EvScriptCtx* ctx)
{
    EvActorCmd cmd;
    EvInstr* ins = ctx->pc_8;
    EvVec* dest = (EvVec*)ins->c_C;
    int actor = ins->a_4;
    cmd.actor_0 = actor;
    cmd.kind_4 = 2;
    cmd.x_18 = dest->x_0;
    cmd.y_1C = dest->y_4;
    cmd.z_20 = dest->z_8;
    cmd.field_14 = ctx->pc_8->b_8;
    return SendActorCmd_800BB840(ctx, &cmd, 1, 1);
}

int EvCmdTurnToActor_800B962C(EvScriptCtx* ctx)
{
    EvActorCmd cmd;
    EvVec* dest;
    int actor = ctx->pc_8->a_4;
    int target = ctx->pc_8->b_8;
    dest = (actor == target) ? GetSavedActorFront_800BBC80(ctx, target, 0) : GetActorPos_800BBBA0(target);
    cmd.actor_0 = ctx->pc_8->a_4;
    cmd.kind_4 = 2;
    cmd.x_18 = dest->x_0;
    cmd.y_1C = dest->y_4;
    cmd.z_20 = dest->z_8;
    cmd.field_14 = ctx->pc_8->c_C;
    return SendActorCmd_800BB840(ctx, &cmd, 1, 1);
}

int EvCmdSetActorVisible_800B96D8(EvScriptCtx* ctx)
{
    EvActorCmd cmd;
    cmd.actor_0 = ctx->pc_8->a_4;
    cmd.kind_4 = 6;
    cmd.arg_C = ctx->pc_8->b_8;
    return SendActorCmdMask_800BB990(ctx, &cmd, 0, 1);
}

int EvCmdSetActorGroundMove_800B9720(EvScriptCtx* ctx)
{
    EvActorCmd cmd;
    cmd.actor_0 = ctx->pc_8->a_4;
    cmd.kind_4 = 7;
    cmd.arg_C = ctx->pc_8->b_8;
    return SendActorCmdMask_800BB990(ctx, &cmd, 0, 1);
}

int EvCmdSetActorRootMotion_800B9768(EvScriptCtx* ctx)
{
    EvActorCmd cmd;
    cmd.actor_0 = ctx->pc_8->a_4;
    cmd.kind_4 = 8;
    cmd.arg_C = ctx->pc_8->b_8;
    return SendActorCmdMask_800BB990(ctx, &cmd, 0, 1);
}

int EvCmdSaveActorPos_800B97B0(EvScriptCtx* ctx)
{
    GetSavedActorPos_800BBC00(ctx, ctx->pc_8->a_4, 1);
    ctx->pc_8++;
    return 1;
}

int EvCmdSaveActorFront_800B97F8(EvScriptCtx* ctx)
{
    GetSavedActorFront_800BBC80(ctx, ctx->pc_8->a_4, 1);
    ctx->pc_8++;
    return 1;
}

int EvCmdTestFlag_800B9840(EvScriptCtx* ctx)
{
    if (ctx->pc_8->a_4 == 0)
    {
        if (TestEventFlag_800AD0D4(ctx->pc_8->b_8))
        {
            ctx->pc_8++;
            return 1;
        }
        return 0;
    }
    ctx->branch_EC = TestEventFlag_800AD0D4(ctx->pc_8->b_8) == 0;
    ctx->pc_8++;
    return 1;
}

int EvCmdSetFlag_800B98C4(EvScriptCtx* ctx)
{
    SetEventFlag_800AD0F8(ctx->pc_8->b_8);
    ctx->pc_8++;
    return 1;
}

int EvCmdClearFlag_800B990C(EvScriptCtx* ctx)
{
    ClearEventFlag_800AD124(ctx->pc_8->b_8);
    ctx->pc_8++;
    return 1;
}

int EvCmdTestTempFlags_800B9954(EvScriptCtx* ctx)
{
    if (ctx->pc_8->a_4 == 0)
    {
        if (TestTempFlags_800BBDD8(ctx->pc_8->b_8))
        {
            ctx->pc_8++;
            return 1;
        }
        return 0;
    }
    ctx->branch_EC = TestTempFlags_800BBDD8(ctx->pc_8->b_8) == 0;
    ctx->pc_8++;
    return 1;
}

int EvCmdSetTempFlags_800B99D8(EvScriptCtx* ctx)
{
    SetTempFlags_800BBDA0(ctx->pc_8->b_8, 1);
    ctx->pc_8++;
    return 1;
}

int EvCmdClearTempFlags_800B9A20(EvScriptCtx* ctx)
{
    SetTempFlags_800BBDA0(ctx->pc_8->b_8, 0);
    ctx->pc_8++;
    return 1;
}

int EvCmdAddItem_800B9A68(EvScriptCtx* ctx)
{
    AddInventory_800AD184(ctx->pc_8->a_4, ctx->pc_8->b_8, 0);
    ctx->pc_8++;
    return 1;
}

int EvCmdRemoveItem_800B9AB4(EvScriptCtx* ctx)
{
    RemoveInventory_800AD1E0(ctx->pc_8->a_4, ctx->pc_8->b_8, 0);
    ctx->pc_8++;
    return 1;
}

int EvCmdAddItemCat1_800B9B00(EvScriptCtx* ctx)
{
    AddInventory_800AD184(ctx->pc_8->a_4, ctx->pc_8->b_8, 1);
    ctx->pc_8++;
    return 1;
}

int EvCmdRemoveItemCat1_800B9B4C(EvScriptCtx* ctx)
{
    RemoveInventory_800AD1E0(ctx->pc_8->a_4, ctx->pc_8->b_8, 1);
    ctx->pc_8++;
    return 1;
}

// a == 0: wait for trigger b (GAME's FireEventTrigger_800A5C40 sets flags 4); else branch_EC = !valuable flag b
// Matched
int EvCmdWaitTrigger_800B9B98(EvScriptCtx* ctx)
{
    unsigned int f;
    if (ctx->pc_8->a_4 == 0)
    {
        if (sceneScriptId_800AEBD8 >= 0 && sceneScriptId_800AEBD8 != ctx->id_10)
        {
        wait:
            return 0;
        }
        ctx->trigger_C8 = ctx->pc_8->b_8;
        f = ctx->flags_0 | 8;
        ctx->flags_0 = f;
        if (!(f & 4))
        {
            goto wait;
        }
        ctx->flags_0 = f & ~0xC;
        ctx->trigger_C8 = -1;
        ctx->pc_8++;
        return 1;
    }
    ctx->branch_EC = TestValuableFlag_800AD73C(ctx->pc_8->b_8) == 0;
    ctx->pc_8++;
    return 1;
}

int EvCmdSetValuable_800B9C5C(EvScriptCtx* ctx)
{
    int a = ctx->pc_8->a_4;
    int b = ctx->pc_8->b_8;
    if (a != 0)
    {
        SetValuableFlag_800AD68C(b);
    }
    else
    {
        ClearValuableFlag_800AD6E4(b);
    }
    ctx->pc_8++;
    return 1;
}

int EvCmdAddMoney_800B9CC0(EvScriptCtx* ctx)
{
    AddMoney_800AD058(ctx->pc_8->b_8);
    ctx->pc_8++;
    return 1;
}

int EvCmdAddEmptyCocoons_800B9D08(EvScriptCtx* ctx)
{
    AddEmptyCocoons_800AD8F4(ctx->pc_8->b_8);
    ctx->pc_8++;
    return 1;
}

int EvCmdHealParty_800B9D50(EvScriptCtx* ctx)
{
    int i;
    UnitStatus* status;
    Heal_80011CD0(GetLevantStatus_800A8C34());

    for (i = 0; i < CountMinions_80010548(3); i++)
    {
        status = GetMinionStatus_800107A0(3, i);
        Heal_80011CD0(status);
        FillHpMp_80011C0C(status, status);
    }
    ctx->pc_8 += 1;
    return 1;
}

int EvCmdSetEntityState_800B9DE0(EvScriptCtx* ctx)
{
    EvEntity* ent = FindEventEntity_800A5DDC(ctx->pc_8->c_C, ctx->pc_8->a_4, 0);
    if (ent == 0)
    {
        return 0;
    }
    ent->f7C_7C = ctx->pc_8->b_8;
    ctx->pc_8++;
    return 1;
}

int EvCmdWaitEntityState_800B9E48(EvScriptCtx* ctx)
{
    EvEntity* ent = FindEventEntity_800A5DDC(ctx->pc_8->c_C, ctx->pc_8->a_4, 0);
    if (ent != 0 && ent->f80_80 == ctx->pc_8->b_8)
    {
        ctx->pc_8++;
        return 1;
    }
    return 0;
}

int EvCmdSetOwnEntityState_800B9EB0(EvScriptCtx* ctx)
{
    ctx->ent_120->f7C_7C = ctx->pc_8->b_8;
    ctx->pc_8++;
    return 1;
}

int EvCmdWaitOwnEntityState_800B9EDC(EvScriptCtx* ctx)
{
    if (ctx->ent_120->f80_80 == ctx->pc_8->b_8)
    {
        ctx->pc_8++;
        return 1;
    }
    return 0;
}

int EvCmdWaitEntityGone_800B9F0C(EvScriptCtx* ctx)
{
    if (FindEventEntity_800A5DDC(ctx->pc_8->c_C, ctx->pc_8->b_8, 0) == 0)
    {
        ctx->pc_8++;
        return 1;
    }
    return 0;
}

int EvCmdSetMsgOptions_800B9F5C(EvScriptCtx* ctx)
{
    ctx->msgOptions_108 |= ctx->pc_8->b_8;
    ctx->pc_8++;
    return 1;
}

int EvCmdSetMsgPos_800B9F84(EvScriptCtx* ctx)
{
    ctx->msgX_100 = ctx->pc_8->a_4;
    ctx->msgY_102 = ctx->pc_8->b_8;
    ctx->pc_8++;
    return 1;
}

int EvCmdSetMsgPosMode_800B9FB4(EvScriptCtx* ctx)
{
    ctx->msgPosMode_104 = ctx->pc_8->b_8;
    ctx->pc_8++;
    return 1;
}

int EvCmdSetVoiceTable_800B9FD8(EvScriptCtx* ctx)
{
    SetVoiceTable_800A6830(ctx->pc_8->c_C);
    ctx->pc_8++;
    return 1;
}

// ops 0x37..0x3F: 0x37/0x38 text, 0x39/0x3A choice (0x38/0x3A keep the window open), 0x3B a string,
// 0x3C/0x3D/0x3E item messages, 0x3F closes a kept window
int EvCmdMessage_800BA020(EvScriptCtx* ctx)
{
    EvInstr* pc = ctx->pc_8;
    switch (ctx->msgStep_B4)
    {
    case 0:
        if (pc->op_0 == 0x3F)
        {
            ctx->msgStep_B4 = 3;
            ctx->flags_0 &= ~0x40;
            return 1;
        }
        ctx->msgStep_B4++;
    case 1:
        EvMessageNop_800BC7A0(ctx);
        if (!OpenEventMessage_800BBE3C(ctx))
        {
            break;
        }
        ctx->lastMsg_110 = (int*)ctx->pc_8;
        ctx->msgStep_B4++;
    case 2:
        if (pc->op_0 == 0x38 || pc->op_0 == 0x3A)
        {
            ctx->msgStep_B4 = 0;
            ctx->flags_0 |= 0x40;
            ctx->pc_8++;
            return 1;
        }
        ctx->msgStep_B4++;
    case 3:
        if (!UpdateEventMessage_800BC2B4(ctx))
        {
            break;
        }
        ctx->msgStep_B4++;
    case 4:
        if (ctx->flags_0 & 0x100)
        {
            if (!XaRequestStop_80043524())
            {
                break;
            }
            ctx->flags_0 &= ~0x100;
        }
    case 5:
        if (ctx->msgOpen_118)
        {
            ctx->msgStep_B4 = 2;
            ctx->pc_8++;
            return 1;
        }
        if ((*(int*)ctx->msgWindow_11C & 0x8001) == 1)
        {
            break;
        }
        ctx->msgWindow_11C = 0;
        ctx->msgStep_B4 = 0;
        ctx->pc_8++;
        return 1;
    }
    ctx->pc_8 = pc;
    return 0;
}


// once shown a times, the last message instruction shows text c instead
int EvCmdSwapMsgAfterCount_800BA1DC(EvScriptCtx* ctx)
{
    int* lastMsg = ctx->lastMsg_110;
    if (lastMsg != 0)
    {
        EvInstr* ins = ctx->pc_8;
        unsigned int limit = ins->a_4;
        unsigned int count = ins->b_8;
        if (count >= limit)
        {
            lastMsg[3] = ins->c_C;
        }
        else
        {
            ins->b_8 = count + 1;
        }
    }
    ctx->pc_8++;
    return 1;
}

int EvCmdWaitMsgMark_800BA238(EvScriptCtx* ctx)
{
    if (ConsumeMsgWindowMark_80034ADC(ctx->msgWindow_11C, ctx->pc_8->b_8))
    {
        ctx->pc_8++;
        return 1;
    }
    return 0;
}

int EvCmdSetChoiceMask_800BA28C(EvScriptCtx* ctx)
{
    EvInstr* ins = ctx->pc_8;
    if (ins->a_4 == 1)
    {
        ctx->choiceMask_114 |= ins->b_8;
    }
    else
    {
        ctx->choiceMask_114 &= ~ins->b_8;
    }
    ctx->pc_8++;
    return 1;
}

int EvCmdPlayAnim_800BA2E8(EvScriptCtx* ctx)
{
    EvActorCmd cmd;
    cmd.actor_0 = 1 << ctx->pc_8->a_4;
    cmd.kind_4 = 3;
    cmd.arg_C = ctx->pc_8->b_8;
    return SendActorCmdMask_800BB990(ctx, &cmd, 1, 1);
}

int EvCmdStopAnim_800BA338(EvScriptCtx* ctx)
{
    EvInstr* ins = ctx->pc_8;
    EvActorCmd cmd;
    switch (ctx->step_B8)
    {
    case 0:
        cmd.actor_0 = ins->b_8;
        cmd.kind_4 = 4;
        cmd.arg_C = ctx->idleAnims_24[ctx->pc_8->a_4];
        if (SendActorCmdMask_800BB990(ctx, &cmd, 1, 0))
        {
            ctx->step_B8++;
        }
    case 1:
        if ((ctx->busyActors_18 & ctx->pc_8->b_8) == 0)
        {
            ctx->step_B8 = 0;
            ctx->pc_8++;
            return 1;
        }
        ctx->pc_8 = ins;
        return 0;
    default:
        ctx->pc_8 = ins;
        return 0;
    }
}

int EvCmdPlayAnimData_800BA40C(EvScriptCtx* ctx)
{
    EvActorCmd cmd;
    cmd.actor_0 = 1 << ctx->pc_8->a_4;
    cmd.kind_4 = 5;
    cmd.data_24 = ctx->pc_8->c_C;
    return SendActorCmdMask_800BB990(ctx, &cmd, 1, 1);
}

int EvCmdPauseActorAnim_800BA45C(EvScriptCtx* ctx)
{
    int ok = 0;
    int actorIdx = ctx->pc_8->a_4;
    if (actorIdx != 0)
    {
        Actor* actor = GetFieldMinionActor_800A7A60(actorIdx - 1);
        if (actor->frame_90 == actor->endFrame_1A)
        {
            SetActorAnimPaused_8001D6EC(actor, ctx->pc_8->b_8);
            ok = 1;
        }
    }
    if (ok)
    {
        ctx->pc_8++;
        return 1;
    }
    return 0;
}

int EvCmdPlayMotion_800BA4F0(EvScriptCtx* ctx)
{
    EvActorCmd cmd;
    cmd.actor_0 = 1 << ctx->pc_8->a_4;
    cmd.kind_4 = 9;
    cmd.arg_C = ctx->pc_8->b_8;
    cmd.field_14 = ctx->pc_8->c_C;
    return SendActorCmdMask_800BB990(ctx, &cmd, 1, 1);
}

int EvCmdPlayMotionRange_800BA554(EvScriptCtx* ctx)
{
    EvActorCmd cmd;
    cmd.actor_0 = 1 << ctx->pc_8->a_4;
    cmd.kind_4 = 0xA;
    cmd.arg_C = ((unsigned short*)&ctx->pc_8->b_8)[1];
    cmd.arg2_10 = ((unsigned short*)&ctx->pc_8->b_8)[0];
    cmd.field_14 = ctx->pc_8->c_C;
    return SendActorCmdMask_800BB990(ctx, &cmd, 1, 1);
}

int EvCmdPlayMotionData_800BA5CC(EvScriptCtx* ctx)
{
    EvActorCmd cmd;
    int motion = ctx->pc_8->c_C;
    int* slot = GetEventDataSlot_800A55B0(4);
    unsigned int a = ctx->pc_8->a_4;
    cmd.actor_0 = 1 << (a >> 16);
    cmd.kind_4 = 0xB;
    cmd.arg_C = ((unsigned short*)&ctx->pc_8->b_8)[1];
    cmd.arg2_10 = ((unsigned short*)&ctx->pc_8->b_8)[0];
    cmd.data_24 = slot[1] + motion * 12;
    cmd.field_14 = a & 0xFFFF;
    return SendActorCmdMask_800BB990(ctx, &cmd, 1, 1);
}

int EvCmdSetCallArg_800BA678(EvScriptCtx* ctx)
{
    ctx->callArg_F0 = ctx->pc_8->c_C;
    if (ctx->callArg_F0 == 0)
    {
        ctx->callArg_F0 = GetOwnEntityParam_800BBDF4(ctx);
    }
    ctx->pc_8++;
    return 1;
}

int EvCmdSetCallArgs_800BA6D0(EvScriptCtx* ctx)
{
    ctx->callArg0_F4 = ctx->pc_8->a_4;
    ctx->callArg1_F8 = ctx->pc_8->b_8;
    ctx->callArg2_FC = ctx->pc_8->c_C;
    ctx->callArg_F0 = (int)&ctx->callArg0_F4;
    ctx->pc_8++;
    return 1;
}

int EvCmdCallUntilDone_800BA714(EvScriptCtx* ctx)
{
    if (ctx->pc_8->b_8 == 1 || sceneScriptId_800AEBD8 < 0 || sceneScriptId_800AEBD8 == ctx->id_10)
    {
        if (((int (*)(int))ctx->pc_8->c_C)(ctx->callArg_F0) == 1)
        {
            ctx->callArg_F0 = 0;
            ctx->pc_8++;
            return 1;
        }
    }
    return 0;
}

int EvCmdCallSelect_800BA7A4(EvScriptCtx* ctx)
{
    if (ctx->pc_8->b_8 == 1 || sceneScriptId_800AEBD8 < 0 || sceneScriptId_800AEBD8 == ctx->id_10)
    {
        ctx->branch_EC = ((int (*)(int))ctx->pc_8->c_C)(ctx->callArg_F0);
        ctx->callArg_F0 = 0;
        ctx->pc_8++;
        return 1;
    }
    return 0;
}

// Matched
int EvCmdSetChapter_800BA82C(EvScriptCtx* ctx)
{
    SaveData* s = &saveData_8008B570;
    s->chapter_2DC = *(unsigned short*)&ctx->pc_8->b_8;
    RequestGameMode_800A6D30(0);
    eventDispatchHalt_8008B540 = 1;
    ctx->pc_8++;
    return 1;
}

int EvCmdSetMapVariant_800BA880(EvScriptCtx* ctx)
{
    SaveData* s = &saveData_8008B570;
    s->mapVariant_2E0 = *(unsigned short*)&ctx->pc_8->b_8;
    ctx->pc_8++;
    return 1;
}

int EvCmdSetMapVar_800BA8AC(EvScriptCtx* ctx)
{
    unsigned short v[3];
    v[0] = ((unsigned short*)&ctx->pc_8->a_4)[0];
    v[1] = ((unsigned short*)&ctx->pc_8->b_8)[1];
    v[2] = ((unsigned short*)&ctx->pc_8->b_8)[0];
    SetMapVar_800ADC5C(v, ctx->pc_8->c_C);
    ctx->pc_8++;
    return 1;
}

int EvCmdChangeMap_800BA930(EvScriptCtx* ctx)
{
    SaveData* s = &saveData_8008B570;
    int* dest;
    s->mapId_2E4[0].field_0 = ((unsigned short*)&ctx->pc_8->a_4)[0];
    s->mapId_2E4[1].field_0 = ((unsigned short*)&ctx->pc_8->b_8)[1];
    s->mapId_2E4[2].field_0 = ((unsigned short*)&ctx->pc_8->b_8)[0];
    s->mapId_2E4[2].field_2 = -1;
    dest = (int*)ctx->pc_8->c_C;
    if (dest)
    {
        s->levant_7A8.pos.x = dest[0];
        s->levant_7A8.pos.y = dest[1];
        s->levant_7A8.pos.z = dest[2];
        s->levant_7A8.rot.vy = dest[3];
    }
    else
    {
        useMapStartPos_80091C94 = 1;
    }
    eventDispatchHalt_8008B540 = 1;
    ctx->pc_8++;
    return 1;
}

int EvCmdChangeMapToPoint_800BA9E4(EvScriptCtx* ctx)
{
    unsigned short v[3];
    SaveData* s;
    FindMapEntrance_800ADCEC(v, ctx->pc_8->b_8);
    forceMapReload_80091C9C = 1;
    mapStartMode_80091C54 = 0;
    useMapStartPos_80091C94 = 1;
    s = &saveData_8008B570;
    s->mapId_2E4[0].field_0 = v[0];
    s->mapId_2E4[1].field_0 = v[1];
    s->mapId_2E4[2].field_0 = v[2];
    eventDispatchHalt_8008B540 = 1;
    ctx->pc_8++;
    return 0;
}

int EvCmdPreloadArea_800BAA6C(EvScriptCtx* ctx)
{
    if (((int (*)(int))RequestAreaPreload_80027330)(ctx->pc_8->b_8))
    {
        ctx->pc_8++;
        return 1;
    }
    return 0;
}

int EvCmdUsePreloadedArea_800BAAC0(EvScriptCtx* ctx)
{
    if (UsePreloadedArea_80027358(ctx->pc_8->b_8))
    {
        ctx->pc_8++;
        return 1;
    }
    return 0;
}

int EvCmdSetReturnPoint_800BAB14(EvScriptCtx* ctx)
{
    GetSetReturnEntrance_800A683C(ctx->pc_8->b_8);
    ctx->pc_8++;
    return 1;
}

#if 0
extern int SetFadeMode_8001C19C(int a, int b);
int EvCmdOpenMapSelect_800BAB5C(EvScriptCtx* ctx)
{
    SetFadeMode_8001C19C(1, 0x20);
    RequestGameMode_800A6D30(8);
    eventDispatchHalt_8008B540 = 1;
    ctx->pc_8++;
    return 1;
}
#endif

INCLUDE_OVERLAY_ASM(eventfnc, EvCmdOpenMapSelect_800BAB5C);

// opens a shop (GAME loads WPNSHOP / SHOPCTRL / SHOP by b's high half) and waits for it to close
int EvCmdOpenShop_800BABB0(EvScriptCtx* ctx)
{
    switch (ctx->step_B8)
    {
    case 0:
        shopRequest_800B06B0.pending_0 = 1;
        shopRequest_800B06B0.kind_4 = ((unsigned short*)&ctx->pc_8->b_8)[1];
        shopRequest_800B06B0.shopId_8 = ((unsigned short*)&ctx->pc_8->b_8)[0];
        ctx->step_B8 = 1;
        return 0;
    case 1:
        if (shopRequest_800B06B0.pending_0 == 0)
        {
            ctx->branch_EC = ExchangeEventResult_800A5F9C(0);
            ctx->step_B8 = 0;
            ctx->pc_8++;
            return 1;
        }
        return 0;
    default:
        return 0;
    }
}

int EvCmdCameraLookAtPoint_800BAC60(EvScriptCtx* ctx)
{
    EvVec target;
    EvVec* src = (EvVec*)ctx->pc_8->c_C;
    target.x_0 = src->x_0;
    target.y_4 = src->y_4 + 0x15E;
    target.z_8 = src->z_8;
    SetCameraBlendTarget_800379DC(&target, ctx->pc_8->b_8);
    ctx->pc_8++;
    return 1;
}

int EvCmdCameraLookAtActor_800BACE0(EvScriptCtx* ctx)
{
    SetCameraBlendTarget_800379DC(GetActorPos_800BBBA0(ctx->pc_8->a_4), ctx->pc_8->b_8);
    ctx->pc_8++;
    return 1;
}

int EvCmdCameraClearLookAt_800BAD3C(EvScriptCtx* ctx)
{
    ClearCameraBlendTarget_80037A20(ctx->pc_8->c_C, ctx->pc_8->b_8);
    ctx->pc_8++;
    return 1;
}

int EvCmdWaitCameraBlend_800BAD88(EvScriptCtx* ctx)
{
    int blend = ((int (*)())GetCameraBlend_80037A4C)();
    int mode = ctx->pc_8->b_8;
    if ((mode == 1 && (short)blend == 0x1000) || (mode == 0 && (short)blend == 0))
    {
        ctx->pc_8++;
        return 1;
    }
    return 0;
}

int EvCmdSetViewRect_800BADF8(EvScriptCtx* ctx)
{
    if (ctx->pc_8->c_C)
    {
        dword_8008D420 = *(EvViewRect*)ctx->pc_8->c_C;
    }
    else
    {
        switch (ctx->pc_8->b_8)
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
    ctx->pc_8++;
    return 1;
}

int EvCmdSetCameraZoom_800BAEBC(EvScriptCtx* ctx)
{
    SetCameraZoom_80037A6C(ctx->pc_8->a_4, ctx->pc_8->b_8);
    ctx->pc_8++;
    return 1;
}

int EvCmdSetCameraTarget_800BAF08(EvScriptCtx* ctx)
{
    int target = ctx->pc_8->c_C;
    if (target == 0)
    {
        target = (int)GetActorPos_800BBBA0(ctx->pc_8->a_4);
    }
    SetCameraTarget_80037AC8(target);
    ctx->pc_8++;
    return 1;
}

int EvCmdSetMapMesh_800BAF68(EvScriptCtx* ctx)
{
    SaveData* s = &saveData_8008B570;
    unsigned short mesh = *(unsigned short*)&ctx->pc_8->b_8;
    s->mapId_2E4[3].field_0 = mesh;
    if ((short)mesh == s->mapId_2E4[3].field_2)
    {
        ctx->pc_8++;
        return 1;
    }
    return 0;
}

// waits until Levant faces one of the actors b (near it, or inside region a) and is triggered
int EvCmdWaitTalk_800BAFAC(EvScriptCtx* ctx)
{
    EvVec* levPos;
    SVECTOR* rot;
    EvVec* actorPos;
    int i;
    int hit;
    unsigned int dist;
    if (sceneScriptId_800AEBD8 >= 0 && sceneScriptId_800AEBD8 != ctx->id_10)
    {
        return 0;
    }
    if (ctx->flags_0 & 4)
    {
        ctx->flags_0 &= ~0xC;
        ctx->pc_8++;
        return 1;
    }
    ctx->flags_0 &= ~0xC;
    levPos = GetActorPos_800BBBA0(0);
    rot = GetActorRot_800BBBD0(0);
    for (i = 1; i < GetFieldMinionCount_800A7790() + 1; i++)
    {
        int bit = 1 << i;
        if (ctx->pc_8->b_8 & bit)
        {
            actorPos = GetActorPos_800BBBA0(i);
            hit = 0;
            if (ctx->pc_8->a_4 >= 0)
            {
                hit = FindTriAtXZ_800B76B8(&mapState_8008B500.meshes20_20[ctx->pc_8->a_4], levPos) >= 0;
            }
            else
            {
                dist = 0xFFF;
                IsWithinDistance_8003B740((int*)levPos, (int*)actorPos, &dist);
                if (dist <= 0x15F8F)
                {
                    hit = 1;
                }
            }
            if (hit)
            {
                if ((unsigned int)(WrapAngle_8003BA18((short)(rot->vy - ratan2Difference_8003B9E0((int*)levPos, (int*)actorPos))) + 0x198) < 0x331)
                {
                    ctx->flags_0 |= 8;
                    break;
                }
            }
        }
    }
    return 0;
}

int EvCmdSetIdleAnim_800BB180(EvScriptCtx* ctx)
{
    EvActorCmd cmd;
    int ret;
    int v = ctx->pc_8->b_8 & 0x80000000;
    ctx->idleAnims_24[ctx->pc_8->a_4] = v;
    if ((ctx->pc_8->b_8 & 0x80000000) == 0)
    {
        ctx->pc_8++;
        ret = 1;
    }
    else
    {
        cmd.actor_0 = 1 << ctx->pc_8->a_4;
        cmd.kind_4 = 3;
        cmd.arg_C = v;
        ret = SendActorCmdMask_800BB990(ctx, &cmd, 1, 1);
    }
    return ret;
}

int EvCmdWaitActorInRegion_800BB214(EvScriptCtx* ctx)
{
    EvVec* pos = GetActorPos_800BBBA0(ctx->pc_8->a_4);
    if (IsEventPointValid_800A6504(ctx->pc_8->b_8, pos))
    {
        ctx->pc_8++;
        return 1;
    }
    return 0;
}

typedef struct EvBattleArgs
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
} EvBattleArgs;

typedef struct EvBattleEnemy
{
    int f0_0[5];
    int f14_14;
    int useMinion_18;
    char pad_1C[0xA4 - 0x1C];
    int actors_A4[3];
    struct
    {
        int species_0;
        int b_4;
    } members_B0[3];
    int anims_C8[3];
    int fD4_D4[3];
} EvBattleEnemy;

extern EvBattleEnemy eventEnemy_800B1CB8;
extern int eventBattlePending_800AEBE0;
extern int eventBattleLoseWarp_800AEBE4;
extern int gCtx_800B1260;
extern int GetFieldMinionAnims_800A7A9C(int i);
// fD4 is stored in both branches (cross-jumping merges the tails); that keeps the loop big enough that a giv is
// "not worth while", so the counter i is not eliminated, as in the original
// Matched
int EvCmdBattle_800BB27C(EvScriptCtx* ctx)
{
    EvBattleArgs* args;
    int i;
    int k;
    switch (ctx->step_B8)
    {
    case 0:
        args = (EvBattleArgs*)ctx->pc_8->c_C;
        eventBattleLoseWarp_800AEBE4 = args->f14_14;
        eventEnemy_800B1CB8.f0_0[0] = args->f0_0[0];
        eventEnemy_800B1CB8.f0_0[1] = args->f0_0[1];
        eventEnemy_800B1CB8.f0_0[2] = args->f0_0[2];
        eventEnemy_800B1CB8.f0_0[3] = args->f0_0[3];
        eventEnemy_800B1CB8.f0_0[4] = args->f0_0[4];
        eventEnemy_800B1CB8.f14_14 = -1;
        eventEnemy_800B1CB8.useMinion_18 = 0;
        for (i = 0; i < 3; i++)
        {
            k = args->ids_18[i];
            if (k != 5)
            {
                eventEnemy_800B1CB8.actors_A4[i] = (int)GetFieldMinionActor_800A7A60(k - 1);
                eventEnemy_800B1CB8.members_B0[i].species_0 = args->e_24[i].a_0;
                eventEnemy_800B1CB8.members_B0[i].b_4 = args->e_24[i].b_4;
                eventEnemy_800B1CB8.anims_C8[i] = GetFieldMinionAnims_800A7A9C(k - 1);
                eventEnemy_800B1CB8.fD4_D4[i] = args->e_24[i].c_8;
            }
            else
            {
                eventEnemy_800B1CB8.actors_A4[i] = 0;
                eventEnemy_800B1CB8.members_B0[i].species_0 = args->e_24[i].a_0;
                eventEnemy_800B1CB8.members_B0[i].b_4 = args->e_24[i].b_4;
                eventEnemy_800B1CB8.anims_C8[i] = 0;
                eventEnemy_800B1CB8.fD4_D4[i] = args->e_24[i].c_8;
            }
        }
        eventBattlePending_800AEBE0 = 1;
        ctx->step_B8++;
    case 1:
        ctx->step_B8++;
        break;
    case 2:
        if (gCtx_800B1260)
        {
            return 0;
        }
        eventBattleLoseWarp_800AEBE4 = 1;
        eventBattlePending_800AEBE0 = 0;
        ctx->step_B8 = 0;
        ctx->pc_8++;
        return 1;
    }
    return 0;
}

int EvCmdIfBattleResult_800BB45C(EvScriptCtx* ctx)
{
    if (ctx->pc_8->b_8 == dword_800B1230)
    {
        ctx->branch_EC = 0;
    }
    else
    {
        ctx->branch_EC = 1;
    }
    ctx->pc_8++;
    return 1;
}

extern void StartSceneFadeIn_8001AA04(int a);
extern void StartSceneFadeOut_8001AA50(int a);
extern void StopSceneDarken_8001AAF4();
extern void StartSceneBrighten_8001AB1C(int a);
extern void EnableCameraPoints_800A094C();
extern void DisableCameraPoints_800A096C();
extern short dword_80091CE0[];
extern void SsSepSetDecrescendo(int, int, int, int);
extern void SsSepStop(int, int);
extern void FadeOutSfxSeq_80031638();
extern void PlayMusic_800300E0(int a, int b);
extern short SfxKeyOn_800314F4(int a);
extern void SfxKeyOff_80031574(int a, int b);
extern void SetLoadFadeFlag_80027478(int a, int b);
extern void SetMotionBlur_8001BCD8(int a);

// a selects: 0..9 scene fades / darken, 10/11 GAME hooks, 12 music, 13..15 sfx, 16 XA, 17 load fade, 18 motion blur
// Matched
int EvCmdFadeSound_800BB4A4(EvScriptCtx* ctx)
{
    int done = 1;
    int op;
    int k;
    short* seq;
    short* xa;
    int* keyOut;
    switch (ctx->pc_8->a_4)
    {
    case 0:
        ResetSceneFade_8001A9A4();
        break;
    case 1:
        SetSceneDark_8001A9E4();
        break;
    case 2:
        SetSceneDark_8001A9E4();
        StartSceneFadeIn_8001AA04(*(unsigned short*)&ctx->pc_8->b_8);
        break;
    case 3:
        StartSceneFadeOut_8001AA50(*(unsigned short*)&ctx->pc_8->b_8);
        break;
    case 4:
        StopSceneDarken_8001AAF4();
        StartSceneBrighten_8001AB1C(*(unsigned short*)&ctx->pc_8->b_8);
        break;
    case 5:
        StartSceneDarken_8001AAA8(*(unsigned short*)&ctx->pc_8->b_8);
        break;
    case 6:
        done = IsSceneFadeDone_8001AB94();
        break;
    case 7:
        StartFadeToBlack_8001C2CC();
        break;
    case 8:
        StartFadeToWhite_8001C2E4();
        break;
    case 9:
        done = IsFadeDone_8001C2FC();
        break;
    case 10:
        EnableCameraPoints_800A094C();
        break;
    case 11:
        DisableCameraPoints_800A096C();
        break;
    case 12:
        op = ctx->pc_8->b_8;
        if (op == 0xFF00)
        {
            seq = dword_80091CE0;
            if (seq[2] >= 0)
            {
                SsSepSetDecrescendo(seq[6], seq[2], 0x7F, 0x78);
                seq[2] = -1;
            }
        }
        else if (op == 0xFF01)
        {
            seq = dword_80091CE0;
            if (seq[2] >= 0)
            {
                SsSepStop(seq[6], seq[2]);
                seq[2] = -1;
            }
        }
        else if (op == 0xFF02)
        {
            FadeOutSfxSeq_80031638();
        }
        else if (op == 0xFF03)
        {
            StopSoundSeqById_800306FC(ctx->pc_8->c_C);
        }
        else if (op == 0xFF04)
        {
            k = ctx->pc_8->c_C;
            PlayMusic_800300E0(k, 1);
            SetBattleMusic_800315D8(k);
        }
        else
        {
            PlayMusic_800300E0(op, 1);
        }
        break;
    case 13:
        PlaySfx_80031494(ctx->pc_8->b_8);
        break;
    case 14:
        op = ctx->pc_8->b_8;
        keyOut = (int*)ctx->pc_8->c_C;
        *keyOut = SfxKeyOn_800314F4(op);
        break;
    case 15:
        SfxKeyOff_80031574(*(short*)ctx->pc_8->c_C, *(short*)&ctx->pc_8->b_8);
        break;
    case 16:
        xa = (short*)ctx->pc_8->c_C;
        XaRequestPlay_80043564(xa[0], xa[1], xa[2]);
        break;
    case 17:
        SetLoadFadeFlag_80027478(0x40, ctx->pc_8->b_8);
        break;
    case 18:
        SetMotionBlur_8001BCD8(ctx->pc_8->b_8);
        break;
    }
    if (done != 0)
    {
        ctx->pc_8++;
        return 1;
    }
    return 0;
}

int EvCmdPadVibration_800BB7D8(EvScriptCtx* ctx)
{
    EvInstr* ins = ctx->pc_8;
    if (ins->a_4 == 1)
    {
        StartPadVibration_80036528(0, *(unsigned char*)&ins->b_8);
    }
    else
    {
        StopPadVibration_80036658(0);
    }
    ctx->pc_8++;
    return 1;
}

// Matched
int SendActorCmd_800BB840(EvScriptCtx* ctx, EvActorCmd* cmd, int a, int b)
{
    int step;
    int actor;
    int mask;
    while (1)
    {
        step = ctx->cmdStep_C0;
        switch (step)
        {
        case 0:
            actor = cmd->actor_0;
            mask = 1 << actor;
            cmd->field_8 = a;
            if (ctx->busyActors_18 & mask)
            {
                return 0;
            }
            if (!IsActorCmdReady_800BBAB0(actor))
            {
                return 0;
            }
            StartActorCmd_800BBB18((int*)cmd);
            if (a)
            {
                ctx->busyActors_18 |= 1 << cmd->actor_0;
            }
            ctx->cmdStep_C0 = 1;
            break;
        case 1:
            if (!IsActorCmdDone_800BBAE4(cmd->actor_0))
            {
                return 0;
            }
            FinishActorCmd_800BBB5C((int*)cmd);
            if (b)
            {
                ctx->pc_8++;
            }
            if (cmd->kind_4 == 3)
            {
                ctx->animActors_1C |= step << cmd->actor_0;
            }
            else if (cmd->kind_4 == 4)
            {
                ctx->animActors_1C &= ~(step << cmd->actor_0);
            }
            ctx->cmdStep_C0 = 0;
            return 1;
        }
    }
}

int SendActorCmdMask_800BB990(EvScriptCtx* ctx, EvActorCmd* cmd, int a, int b)
{
    int i;
    int bit;
    switch (ctx->maskStep_BC)
    {
    case 0:
        ctx->idleAnims_24[5] = cmd->actor_0;
        ctx->maskStep_BC++;
    case 1:
        for (i = 0; i < 5; i++)
        {
            bit = 1 << i;
            if (ctx->idleAnims_24[5] & bit)
            {
                cmd->actor_0 = i;
                if (!SendActorCmd_800BB840(ctx, cmd, a, 0))
                {
                    break;
                }
                ctx->idleAnims_24[5] &= ~bit;
            }
        }
        if (ctx->idleAnims_24[5] == 0)
        {
            if (b)
            {
                ctx->pc_8++;
            }
            ctx->maskStep_BC = 0;
            return 1;
        }
        return 0;
    default:
        return 0;
    }
}

int IsActorCmdReady_800BBAB0(int actor)
{
    int ret;
    if (actor == 0)
    {
        ret = IsLevantControlHeld_800A8E7C();
    }
    else
    {
        ret = IsFieldMinionIdle_800A7CB8(actor - 1);
    }
    return ret;
}

int IsActorCmdDone_800BBAE4(int actor)
{
    int ret;
    if (actor == 0)
    {
        ret = IsLevantCmdDone_800A8FE0();
    }
    else
    {
        ret = IsFieldMinionReady_800A7CFC(actor - 1);
    }
    return ret;
}

// Matched
extern int LevantCommand_800A8EC4(int* p);
extern int FieldMinionCommand_800A7D40(int a, int* p);
int StartActorCmd_800BBB18(int* cmd)
{
    int ret;
    int actor = *cmd;
    if (actor == 0)
    {
        ret = LevantCommand_800A8EC4(cmd);
    }
    else
    {
        ret = FieldMinionCommand_800A7D40(actor - 1, cmd);
    }
    return ret;
}

// Matched
extern int FinishLevantCommand_800A9008(int* p);
extern int TriggerFieldMinionEffect_800A80C4(int a, int* p);
int FinishActorCmd_800BBB5C(int* cmd)
{
    int ret;
    int actor = *cmd;
    if (actor == 0)
    {
        ret = FinishLevantCommand_800A9008(cmd);
    }
    else
    {
        ret = TriggerFieldMinionEffect_800A80C4(actor - 1, cmd);
    }
    return ret;
}

EvVec* GetActorPos_800BBBA0(int actor)
{
    EvVec* ret;
    if (actor == 0)
    {
        ret = (EvVec*)&levantPos_8008BD18.pos;
    }
    else
    {
        ret = GetFieldMinionPos_800A7940(actor - 1);
    }
    return ret;
}

SVECTOR* GetActorRot_800BBBD0(int actor)
{
    SVECTOR* ret;
    if (actor == 0)
    {
        ret = &levantRot_8008BD24;
    }
    else
    {
        ret = GetFieldMinionRot_800A7984(actor - 1);
    }
    return ret;
}

EvVec* GetSavedActorPos_800BBC00(EvScriptCtx* ctx, int idx, int mode)
{
    if (mode == 1)
    {
        EvVec* pos = GetActorPos_800BBBA0(idx);
        ctx->savedPos_3C[idx].x_0 = pos->x_0;
        ctx->savedPos_3C[idx].y_4 = pos->y_4;
        ctx->savedPos_3C[idx].z_8 = pos->z_8;
    }
    return &ctx->savedPos_3C[idx];
}

EvVec* GetSavedActorFront_800BBC80(EvScriptCtx* ctx, int idx, int mode)
{
    if (mode == 1)
    {
        EvVec* pos = GetActorPos_800BBBA0(idx);
        SVECTOR* rot = GetActorRot_800BBBD0(idx);
        ctx->savedFront_78[idx].x_0 = pos->x_0 + sinTable_80084540[rot->vy & 0xFFF] * 100 / 4096;
        ctx->savedFront_78[idx].y_4 = rot->vy;
        ctx->savedFront_78[idx].z_8 = pos->z_8 + sinTable_80084540[(rot->vy + 0x400) & 0xFFF] * 100 / 4096;
    }
    return &ctx->savedFront_78[idx];
}

void SetTempFlags_800BBDA0(int mask, int on)
{
    if (on == 1)
    {
        eventTempFlags_800AEBD4 |= mask;
    }
    else
    {
        eventTempFlags_800AEBD4 &= ~mask;
    }
}

int TestTempFlags_800BBDD8(int mask)
{
    return (~eventTempFlags_800AEBD4 & mask) == 0;
}

int GetOwnEntityParam_800BBDF4(EvScriptCtx* ctx)
{
    if (ctx->ent_120 != 0)
    {
        return ctx->ent_120->f8C_8C;
    }
    return 0;
}

int sub_800BBE18(EvScriptCtx* ctx)
{
    if (ctx->ent_120 != 0)
    {
        return ctx->ent_120->f84_84;
    }
    return -1;
}

typedef struct EvSpeaker
{
    int a_0;
    int b_4;
} EvSpeaker;
typedef struct EvMsgWindowCfg
{
    int posMode_0;
    unsigned short* pos_4;
    int str_8;
    int fC;
    int f10;
    int f14;
    int mask_18;
    int* list_1C;
    EvSpeaker pair_20;
    int f28;
    int f2C;
    int f30;
    int f34;
    int f38;
    int f3C;
    int f40;
    int voice_44;
} EvMsgWindowCfg;
typedef struct EvItemMsgCfg
{
    int posMode_0;
    unsigned short* pos_4;
    int f8;
    EvItemMsgSlot slots_C[3];
    int f48;
    int f4C;
} EvItemMsgCfg;
typedef struct EvMsgOptions
{
    EvSpeaker pair_A8;
    EvItemMsgSrc src_B0;
    int* list_B8;
    int fBC;
    int fC0;
    int fC4;
    int fC8;
    int fCC;
} EvMsgOptions;
extern int GetEventString_800A6738(int a);
extern int GetFieldMinionModelId_800A78A8(int a);
extern int sub_800A78F4(int a);
extern int OpenMessageWindow_8003422C(EvMsgWindowCfg* cfg);
extern int OpenItemMessageWindow_80035AC8(EvItemMsgCfg* cfg);
int* FindMsgChoiceList_800BC560(int* p);
int GetChoiceMask_800BC58C(int* p);
int IsActorLeftOf_800BC5C8(int a, int b);
void SetupItemMsgSlots_800BC6C4(EvItemMsgCfg* cfg, EvItemMsgSrc* src, int n);

#if 0
// Not matched (register allocation): list/bc/c0/c4/c8/cc are spilled scalars as in the original, but here list keeps
// $fp and mask is spilled, so mask/ret/pos/skip sit one callee-saved register off (orig s5/s6/s7/fp) and list's stack
// slot moves; control flow, the double store of c8 and the call sequence match
int OpenEventMessage_800BBE3C(EvScriptCtx* ctx)
{
    EvMsgWindowCfg cfg;
    EvItemMsgCfg it;
    EvSpeaker pair;
    EvItemMsgSrc src;
    int* list;
    int bc;
    int c0;
    int c4;
    int c8;
    int cc;
    int mode;
    EvInstr* pc;
    int posMode;
    int str;
    int mask;
    int ret;
    unsigned short* pos;
    int skip;
    EvVoiceCue* voice;
    int srcArg;
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
    pc = ctx->pc_8;
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
            str = GetOwnEntityParam_800BBDF4(ctx);
        }
        else
        {
            str = GetEventString_800A6738(pc->c_C);
        }
        mode = 3;
    }
    else if (pc->op_0 == 0x39 || pc->op_0 == 0x3A)
    {
        mask = 0;
        mode = 0;
        str = GetEventString_800A6738(pc->c_C);
        list = FindMsgChoiceList_800BC560((int*)str);
        mask = GetChoiceMask_800BC58C(list) & ~ctx->choiceMask_114;
    }
    else
    {
        mode = mask;
        list = 0;
        str = GetEventString_800A6738(pc->c_C);
    }
    if (*(short*)&ctx->msgX_100 != -1 && *(short*)&ctx->msgY_102 != -1)
    {
        posMode = 0;
        pos = &ctx->msgX_100;
    }
    else
    {
        posMode = ctx->msgPosMode_104;
        if (posMode < 0)
        {
            posMode = !(pc->op_0 == 0x39 || pc->op_0 == 0x3A) << 1;
        }
    }
    if (pc->op_0 >= 0x37 && pc->op_0 < 0x3B)
    {
        pair.a_0 = 1;
        pair.b_4 = pc->a_4;
        bc = IsActorLeftOf_800BC5C8(pc->a_4, pc->b_8);
    }
    else if (pc->op_0 == 0x3B)
    {
        bc = 1;
        pair.a_0 = 0;
        pair.b_4 = -1;
    }
    fl = ctx->msgOptions_108;
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
        cfg.posMode_0 = posMode;
        cfg.pos_4 = pos;
        cfg.str_8 = str;
        cfg.f10 = skip;
        cfg.mask_18 = mask;
        cfg.f14 = cc;
        cfg.list_1C = list;
        cfg.pair_20 = pair;
        cfg.f28 = bc;
        cfg.f30 = c0;
        cfg.f34 = c4;
        cfg.f38 = c8;
        cfg.f3C = 0;
        cfg.f40 = 0;
        cfg.fC = GetFieldMinionModelId_800A78A8(pc->a_4 - 1);
        cfg.f2C = sub_800A78F4(pc->a_4 - 1);
        voice = voiceTable_800AEBF0;
        cfg.voice_44 = 0;
        if (voice != 0)
        {
            for (; voice->xa_2.a_0 >= 0; voice++)
            {
                if (currentMessageId_800AEBE8 == voice->id_0)
                {
                    cfg.voice_44 = 1;
                    break;
                }
            }
        }
        ret = OpenMessageWindow_8003422C(&cfg);
    }
    else if (mode == 1)
    {
        it.posMode_0 = posMode;
        it.pos_4 = pos;
        it.f8 = 0;
        it.f48 = pc->b_8;
        it.f4C = 0;
        srcArg = pc->c_C;
        if (srcArg == 0)
        {
            srcArg = GetOwnEntityParam_800BBDF4(ctx);
        }
        SetupItemMsgSlots_800BC6C4(&it, (EvItemMsgSrc*)srcArg, pc->a_4);
        ret = OpenItemMessageWindow_80035AC8(&it);
    }
    else if (mode == 2)
    {
        it.posMode_0 = posMode;
        it.pos_4 = pos;
        it.f8 = 0;
        it.f48 = pc->b_8;
        it.f4C = 0;
        srcArg = pc->a_4;
        if (srcArg == -1)
        {
            srcArg = sub_800BBE18(ctx);
        }
        src.a_0 = pc->c_C;
        src.b_2 = srcArg;
        src.c_4 = 1;
        SetupItemMsgSlots_800BC6C4(&it, &src, 1);
        ret = OpenItemMessageWindow_80035AC8(&it);
    }
    else if (mode == 3)
    {
        it.posMode_0 = posMode;
        it.pos_4 = pos;
        it.f8 = 0;
        it.f48 = 0xB;
        it.f4C = str;
        SetupItemMsgSlots_800BC6C4(&it, 0, 0);
        ret = OpenItemMessageWindow_80035AC8(&it);
    }
    if (ret == 0)
    {
        return 0;
    }
    ctx->msgOpen_118 = 1;
    ctx->msgX_100 = -1;
    ctx->msgY_102 = -1;
    ctx->msgWindow_11C = ret;
    ctx->msgPosMode_104 = -1;
    ctx->msgOptions_108 = 0;
    return 1;
}
#endif

INCLUDE_OVERLAY_ASM(eventfnc, OpenEventMessage_800BBE3C);

int UpdateEventMessage_800BC2B4(EvScriptCtx* ctx)
{
    EvMsgResult info;
    unsigned int flags;
    int i;
    EvXaClip* voice;
    SaveData* save;
    if (ctx->flags_0 & 0x80)
    {
        ctx->flags_0 &= ~0x80;
        return 1;
    }
    if (ctx->flags_0 & 2)
    {
        if (!GetMsgWindowResultIfDone_800349B4(ctx->msgWindow_11C, &info))
        {
            return 0;
        }
        if (ctx->flags_0 & 0x100)
        {
            if (XaRequestStop_80043524())
            {
                ctx->flags_0 &= ~0x100;
            }
        }
        SkipActorAnims_800A67B4(ctx);
        flags = ctx->flags_0;
        ctx->flags_0 = flags & ~2;
        if (!info.fC_C)
        {
            return 0;
        }
        if (flags & 0x40)
        {
            ctx->flags_0 = (ctx->flags_0 & ~0x40) | 0x80;
        }
        if (info.f8_8)
        {
            ctx->branch_EC = info.choice_2;
        }
        CloseMsgWindow_80034A84(ctx->msgWindow_11C);
        currentMessageId_800AEBE8 = 0x8000;
        currentVoice_800AEBEC = 0;
        ctx->msgOpen_118 = 0;
        return 1;
    }
    if (voiceTable_800AEBF0)
    {
        voice = 0;
        for (i = 0; voiceTable_800AEBF0[i].xa_2.a_0 >= 0; i++)
        {
            if (currentMessageId_800AEBE8 == voiceTable_800AEBF0[i].id_0 && ConsumeMsgWindowMark_80034ADC(ctx->msgWindow_11C, voiceTable_800AEBF0[i].sub_1))
            {
                voice = &voiceTable_800AEBF0[i].xa_2;
            }
        }
        if (saveData_8008B570.settings_1C.bits.i_22 == 1 && voice && currentVoice_800AEBEC != voice)
        {
            currentVoice_800AEBEC = voice;
            XaRequestPlay_80043564(voice->a_0, voice->b_2, voice->c_4);
            ctx->flags_0 |= 0x100;
        }
    }
    if (IsMsgWindowWaiting_80034A30(ctx->msgWindow_11C))
    {
        save = &saveData_8008B570;
        if (save->settings_1C.bits.b_3 == 1 || XaIsIdle_80043584())
        {
            if (save->settings_1C.bits.c_4 == 1 || !ctx->busyActors_18)
            {
                EnableMsgWindowAdvance_80034A68(ctx->msgWindow_11C);
                ctx->flags_0 |= 2;
            }
        }
    }
    return 0;
}

int* FindMsgChoiceList_800BC560(int* text)
{
    int zeros = 0;
    do
    {
        zeros++;
        if (*text != 0)
        {
            zeros = 0;
        }
        text++;
    } while (zeros != 2);
    return text;
}

int GetChoiceMask_800BC58C(int* list)
{
    int mask = 0;
    int i;
    for (i = 0; *list != 0; list++, i++)
    {
        mask |= 1 << i;
    }
    return mask;
}

int IsActorLeftOf_800BC5C8(int actorA, int actorB)
{
    unsigned short rel[3];
    short scr1[4];
    short scr2[4];
    short scratch[4];
    unsigned short* posA = (unsigned short*)GetActorPos_800BBBA0(actorA);
    unsigned short* posB;
    rel[0] = posA[0];
    rel[1] = posA[2];
    rel[2] = posA[4];
    rel[0] -= word_8008D600[0];
    rel[1] -= word_8008D600[2];
    rel[2] -= word_8008D600[4];
    sub_8005BBC8(rel, scr1, scratch, scratch);
    posB = (unsigned short*)GetActorPos_800BBBA0(actorB);
    rel[0] = posB[0];
    rel[1] = posB[2];
    rel[2] = posB[4];
    rel[0] -= word_8008D600[0];
    rel[1] -= word_8008D600[2];
    rel[2] -= word_8008D600[4];
    sub_8005BBC8(rel, scr2, scratch, scratch);
    return scr1[0] < scr2[0];
}

// Matched
void SetupItemMsgSlots_800BC6C4(EvItemMsgCfg* cfg, EvItemMsgSrc* src, int n)
{
    int local[8];
    int i;
    EvItemMsgSlot* slot;
    memset(local, 0, 0x20);
    local[0] = 2;
    local[5] = 3;
    for (i = 0; i < 3; i++)
    {
        slot = &cfg->slots_C[i];
        if (i < n)
        {
            slot->f0_0 = src[i].a_0;
            slot->f4_4 = src[i].b_2;
            slot->f8_8 = src[i].c_4;
        }
        else
        {
            slot->f0_0 = -1;
            slot->f4_4 = 0;
            slot->f8_8 = 0;
        }
        if (slot->f0_0 >= 0)
        {
            slot->fC_C = local[slot->f0_0];
            slot->f10_10 = slot->f4_4;
        }
    }
}

void EvMessageNop_800BC7A0(EvScriptCtx* ctx)
{
}

void LoadEventEffectFile_800BC7A8(int file)
{
    EvEffectLoadArg arg;
    if (mdecBufferMode_800AEB7C != 2)
    {
        FreeMdecBuffer_800A5854();
    }
    if (eventEffects_800AEB80.list_4)
    {
        ListFreeAll_8003FEC8(&eventEffects_800AEB80.list_4);
    }
    arg.g_0 = &eventEffects_800AEB80;
    arg.s_4[5] = 0;
    arg.s_4[4] = 0;
    arg.s_4[3] = 0;
    arg.s_4[2] = 0;
    arg.s_4[1] = 0;
    arg.s_4[0] = 0;
    arg.f10_10 = 0;
    ListInit_8003FDB0(&eventEffects_800AEB80.list_4);
    OnEffectFileLoaded_80020F5C(&arg, file);
    if (eventEffects_800AEB80.usesMdec_2C)
    {
        AllocMdecBuffer_800A5804(0);
    }
}

typedef struct EvRelocBlob
{
    int* p_0;
} EvRelocBlob;
extern EvRelocBlob eventReloc_800AEBBC;
// Matched
void LoadRelocBlob_800BC854(int* src)
{
    int size;
    int* data;
    int n;
    int i;
    int j;
    int m;
    int* ptr;
    int* entry;
    if (eventReloc_800AEBBC.p_0)
    {
        ListFree_8003FE38(eventHeap_80091C10, eventReloc_800AEBBC.p_0);
        eventReloc_800AEBBC.p_0 = 0;
    }
    size = *src;
    data = src + 1;
    eventReloc_800AEBBC.p_0 = ListAlloc_8003FDC0(eventHeap_80091C10, size);
    MemCopy_800403E8(eventReloc_800AEBBC.p_0, data, size);
    n = eventReloc_800AEBBC.p_0[0];
    for (i = 0; i < n; i++)
    {
        entry = (int*)((char*)eventReloc_800AEBBC.p_0 + (i * 8 + 4));
        *entry = (int)eventReloc_800AEBBC.p_0 + *entry;
    }
    for (i = 0; i < n; i++)
    {
        entry = (int*)((char*)eventReloc_800AEBBC.p_0 + (i * 8 + 4));
        m = entry[1];
        ptr = (int*)entry[0];
        for (j = 0; j < m; j++, ptr++)
        {
            if (*ptr == -1)
            {
                *ptr = 0;
            }
            else
            {
                *ptr = (int)eventReloc_800AEBBC.p_0 + *ptr;
            }
        }
    }
}

void LoadEventTiy_800BC98C(int* tiy)
{
    if (eventTiy_800AEBC0.sprts_0)
    {
        ListFree_8003FE38(eventHeap_80091C10, eventTiy_800AEBC0.sprts_0);
        eventTiy_800AEBC0.sprts_0 = 0;
    }
    if (eventTiy_800AEBC0.tpages_4)
    {
        ListFree_8003FE38(eventHeap_80091C10, eventTiy_800AEBC0.tpages_4);
        eventTiy_800AEBC0.tpages_4 = 0;
    }
    LoadTiy_80028E74(&eventTiy_800AEBC0.sprts_0, 0, &eventTiy_800AEBC0.tpages_4, tiy, (int)eventHeap_80091C10);
}

extern int eventDataBuf_800AEBC8;
// Matched
void CopyEventData_800BCA18(unsigned int* src, unsigned int size)
{
    unsigned int* buf = ListAlloc_8003FDC0(eventHeap_80091C10, size);
    eventDataBuf_800AEBC8 = (int)buf;
    MemCopy_800403E8(buf, src, size);
}

void LoadEventRecordTables_800BCA68(int data)
{
    if (eventRecords_800AEBCC[1] != 0)
    {
        FreeRecordTables_80026DE8(&eventRecords_800AEBCC[1], eventRecords_800AEBCC[0], eventHeap_80091C10);
        eventRecords_800AEBCC[0] = 0;
    }
    eventRecords_800AEBCC[0] = GetRecordTableCount_80026D6C((int*)data);
    AllocRecordTables_80026D78(&eventRecords_800AEBCC[1], eventRecords_800AEBCC[0], eventHeap_80091C10);
    LoadRecordTables_80026E74(eventRecords_800AEBCC[1], data, eventHeap_80091C10);
}

void ReturnWarpStart_800BCB00(EvTaskEntry* task, int* state)
{
    state[0] = 0;
    state[1] = 0x1D;
    ReturnWarpTask_800BCB3C(task, state);
    task->next_8 = ReturnWarpTask_800BCB3C;
}
