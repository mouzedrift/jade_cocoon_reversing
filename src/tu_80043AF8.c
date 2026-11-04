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
#define ABS_80043AF8(x) ((x) < 0 ? -(x) : (x))
#include "tu_80036528.h"
#include "tu_80043AF8.h"
#include "tu_80019BF0.h"
#include "tu_8004B0A8.h"

INCLUDE_DATA(dword_80098690);
INCLUDE_DATA(dword_800986A0);
INCLUDE_DATA(dword_800987D8);
INCLUDE_DATA(dword_8009AAD8);

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
extern short word_8008D51E; // projection distance
extern int sub_80031BE4(POLY_FT4* p, unsigned long* ot, short x, short y, int sx, int sy, short* off, int fl);
// Matched
int DrawBillboard_80043B8C(POLY_FT4* p, VECTOR* pos, short* size, int flags, short* off, short fl)
{
    BillboardScratch* s = BILLBOARD_SCRATCH;
    int shade;
    s->rel_4.vx = pos->vx - dword_8008D600.vx;
    s->rel_4.vy = pos->vy - dword_8008D600.vy;
    s->rel_4.vz = pos->vz - dword_8008D600.vz;
    gte_ldv0(&s->rel_4);
    gte_rtps();
    gte_stsxy(s);
    gte_stszotz(&s->otz_C);
    if (s->otz_C - 1 < 0xFFFU)
    {
        s->w_10 = (size[0] << 7) / s->otz_C * dword_8008B4F8 * word_8008D51E / 0xA0000;
        s->h_14 = (size[1] << 7) / s->otz_C * dword_8008B4F8 * word_8008D51E / 0xA0000;
        if (s->w_10 > 0x800)
        {
            s->w_10 = 0x800;
        }
        if (s->h_14 > 0x800)
        {
            s->h_14 = 0x800;
        }
        p->r0 = p->g0 = p->b0 = s->shade_18 = ((0x80 - (flags >> 16) / 32) * dword_8008D40C) >> 12;
        if (flags & 0x10)
        {
            setSemiTrans(p, 1);
            p->tpage = (p->tpage & ~0x60) | (flags & 0x60);
        }
        return sub_80031BE4(p, pOT_8008D690 + ((s->otz_C >> 2) & 0x3FF), s->x_0, s->y_2, s->w_10, s->h_14, off, fl);
    }
    return 0;
}
// Matched
int DrawBillboardRgb_80043DE0(POLY_FT4* p, VECTOR* pos, short* size, unsigned char* rgb)
{
    BillboardScratch* s = BILLBOARD_SCRATCH;
    s->rel_4.vx = pos->vx - dword_8008D600.vx;
    s->rel_4.vy = pos->vy - dword_8008D600.vy;
    s->rel_4.vz = pos->vz - dword_8008D600.vz;
    gte_ldv0(&s->rel_4);
    gte_rtps();
    gte_stsxy(s);
    gte_stszotz(&s->otz_C);
    if (s->otz_C - 101 < 0xF9BU)
    {
        s->w_10 = (size[0] << 7) / s->otz_C * dword_8008B4F8 * word_8008D51E / 0xA0000;
        s->h_14 = (size[1] << 7) / s->otz_C * dword_8008B4F8 * word_8008D51E / 0xA0000;
        if (s->w_10 > 0x800)
        {
            s->w_10 = 0x800;
        }
        if (s->h_14 > 0x800)
        {
            s->h_14 = 0x800;
        }
        p->r0 = (rgb[0] * dword_8008D40C) >> 12;
        p->g0 = (rgb[1] * dword_8008D40C) >> 12;
        p->b0 = (rgb[2] * dword_8008D40C) >> 12;
        return sub_80031BE4(p, pOT_8008B4C8 + ((s->otz_C >> 2) & 0x3FF), s->x_0, s->y_2, s->w_10, s->h_14, 0, 0x20);
    }
    return 0;
}
/* 4096-entry sine table at 0x80084540 (inside the asc_80084350 data chunk) */
extern short asc_80084350[];
#define SIN_TABLE (asc_80084350 + 0xF8)
#if 0
// Not matched: code layout right; register allocation differs throughout (the original never uses $t0 in the screen-aligned branch, keeps &geomScreenDistance in $t0 for the last extent), 1 instruction short
#define ROT_SPRITE_UV(s, src, uv, size)                       \
    {                                                         \
        (s)->prim_0.u0 = (src)->u0 + (uv)[0];                 \
        (s)->prim_0.v0 = (src)->v0 + (uv)[1];                 \
        (s)->prim_0.u1 = (src)->u0 + (uv)[0] + (size)[0];     \
        (s)->prim_0.v1 = (src)->v0 + (uv)[1];                 \
        (s)->prim_0.u2 = (src)->u0 + (uv)[0];                 \
        (s)->prim_0.v2 = (src)->v0 + (uv)[1] + (size)[1];     \
        (s)->prim_0.u3 = (src)->u0 + (uv)[0] + (size)[0];     \
        (s)->prim_0.v3 = (src)->v0 + (uv)[1] + (size)[1];     \
    }
#define ROT_SPRITE_EXTENT(v, piv, sc) (((v) * (sc) * geomScreenDistance_8008B548 / 256) / s->otz_4C / 4)
VECTOR* DrawRotSprite_80044010(POLY_FT4* src, VECTOR* pos, SVECTOR* rot, short* uv, short* size, short* pivot, short* scale,
                     SVECTOR* ofs, unsigned char* rgb, short flags, int abr, unsigned long* ot)
{
    RotSpriteScratch* s = ROT_SPRITE_SCRATCH;
    short min;
    short max;
    if (flags & 1)
    {
        MATRIX m;
        s->rel_2C.vx = pos->vx - dword_8008D600.vx + ofs->vx;
        s->rel_2C.vy = pos->vy - dword_8008D600.vy + ofs->vy;
        s->rel_2C.vz = pos->vz - dword_8008D600.vz + ofs->vz;
        gte_ReadRotMatrix(&s->rot_78);
        m.m[0][0] = m.m[1][1] = m.m[2][2] = 0x1000;
        m.m[0][1] = m.m[0][2] = m.m[1][0] = m.m[1][2] = m.m[2][0] = m.m[2][1] = 0;
        gte_SetRotMatrix(&m);
        gte_ldv0(&s->rel_2C);
        gte_rtps();
        gte_stsxy(&s->x_28);
        gte_stszotz(&s->otz_4C);
        gte_SetRotMatrix(&s->rot_78);
        s->prim_0 = *src;
        ROT_SPRITE_UV(s, src, uv, size);
    }
    else
    {
        gte_ReadRotMatrix(&s->rot_78);
        RotMatrixZXY_8004668C(rot, (MATRIX*)getScratchAddr(0));
        s->ofs_34.vx = ofs->vx;
        s->ofs_34.vy = ofs->vy;
        s->ofs_34.vz = ofs->vz;
        ApplyMatrixLV((MATRIX*)getScratchAddr(0), (VECTOR*)&s->ofs_34, (VECTOR*)&s->wofs_40);
        gte_SetRotMatrix(&s->rot_78);
        s->prim_0 = *src;
        ROT_SPRITE_UV(s, src, uv, size);
        s->rel_2C.vx = pos->vx - dword_8008D600.vx + s->wofs_40.vx;
        s->rel_2C.vy = pos->vy - dword_8008D600.vy + s->wofs_40.vy;
        s->rel_2C.vz = pos->vz - dword_8008D600.vz + s->wofs_40.vz;
        gte_ldv0(&s->rel_2C);
        gte_rtps();
        gte_stsxy(&s->x_28);
        gte_stszotz(&s->otz_4C);
    }
    if (s->otz_4C - 1 < 0xFFFU)
    {
        s->prim_0.r0 = (rgb[0] * dword_8008D40C) >> 12;
        s->prim_0.g0 = (rgb[1] * dword_8008D40C) >> 12;
        s->prim_0.b0 = (rgb[2] * dword_8008D40C) >> 12;
        if ((scale[0] * geomScreenDistance_8008B548 / 256) / s->otz_4C / 4 * dword_8008B4F8 / 4096 >= 9)
        {
            return (VECTOR*)&s->wofs_40;
        }
        s->x0_5C = (-pivot[0] * scale[0] * geomScreenDistance_8008B548 / 256) / s->otz_4C / 4;
        s->x1_64 = ((ABS_80043AF8(size[0]) - pivot[0]) * scale[0] * geomScreenDistance_8008B548 / 256) / s->otz_4C / 4;
        s->y0_60 = (-pivot[1] * scale[1] * geomScreenDistance_8008B548 / 256) / s->otz_4C / 4;
        s->y1_68 = ((ABS_80043AF8(size[1]) - pivot[1]) * scale[1] * geomScreenDistance_8008B548 / 256) / s->otz_4C / 4;
        if (ofs->pad == 0)
        {
            s->prim_0.x0 = s->x_28 + s->x0_5C;
            s->prim_0.y0 = s->y_2A + s->y0_60;
            s->prim_0.x1 = s->x_28 + s->x1_64;
            s->prim_0.y1 = s->y_2A + s->y0_60;
            s->prim_0.x2 = s->x_28 + s->x0_5C;
            s->prim_0.y2 = s->y_2A + s->y1_68;
            s->prim_0.x3 = s->x_28 + s->x1_64;
            s->prim_0.y3 = s->y_2A + s->y1_68;
        }
        else
        {
            s->sin_70 = SIN_TABLE[ofs->pad & 0xFFF];
            s->cos_6C = SIN_TABLE[(ofs->pad + 0x400) & 0xFFF];
            s->prim_0.x0 = s->x_28 + (s->x0_5C * s->cos_6C + s->y0_60 * s->sin_70) / 4096;
            s->prim_0.y0 = s->y_2A + (-s->x0_5C * s->sin_70 + s->y0_60 * s->cos_6C) / 4096;
            s->prim_0.x1 = s->x_28 + (s->x1_64 * s->cos_6C + s->y0_60 * s->sin_70) / 4096;
            s->prim_0.y1 = s->y_2A + (-s->x1_64 * s->sin_70 + s->y0_60 * s->cos_6C) / 4096;
            s->prim_0.x2 = s->x_28 + (s->x0_5C * s->cos_6C + s->y1_68 * s->sin_70) / 4096;
            s->prim_0.y2 = s->y_2A + (-s->x0_5C * s->sin_70 + s->y1_68 * s->cos_6C) / 4096;
            s->prim_0.x3 = s->x_28 + (s->x1_64 * s->cos_6C + s->y1_68 * s->sin_70) / 4096;
            s->prim_0.y3 = s->y_2A + (-s->x1_64 * s->sin_70 + s->y1_68 * s->cos_6C) / 4096;
        }
        if (s->prim_0.x1 < s->prim_0.x0)
        {
            max = s->prim_0.x0;
            min = s->prim_0.x1;
        }
        else
        {
            max = s->prim_0.x1;
            min = s->prim_0.x0;
        }
        if (max < s->prim_0.x2)
        {
            max = s->prim_0.x2;
        }
        else if (s->prim_0.x2 < min)
        {
            min = s->prim_0.x2;
        }
        if (max < s->prim_0.x3)
        {
            max = s->prim_0.x3;
        }
        else if (s->prim_0.x3 < min)
        {
            min = s->prim_0.x3;
        }
        if (min >= 320 || max < 0)
        {
            return (VECTOR*)&s->wofs_40;
        }
        if (s->prim_0.y1 < s->prim_0.y0)
        {
            max = s->prim_0.y0;
            min = s->prim_0.y1;
        }
        else
        {
            max = s->prim_0.y1;
            min = s->prim_0.y0;
        }
        if (max < s->prim_0.y2)
        {
            max = s->prim_0.y2;
        }
        else if (s->prim_0.y2 < min)
        {
            min = s->prim_0.y2;
        }
        if (max < s->prim_0.y3)
        {
            max = s->prim_0.y3;
        }
        else if (s->prim_0.y3 < min)
        {
            min = s->prim_0.y3;
        }
        if (min >= 240 || max < 0)
        {
            return (VECTOR*)&s->wofs_40;
        }
        if (abr & 0x10)
        {
            setSemiTrans(&s->prim_0, 1);
            s->prim_0.tpage = (s->prim_0.tpage & ~0x60) | (abr & 0x60);
        }
        if (flags & 2)
        {
            s->otz_4C = 0;
        }
        *(POLY_FT4*)primAllocPtr_800960A8[bDoubleBuffer_8008D428] = s->prim_0;
        addPrim(ot + ((s->otz_4C >> 2) & 0x3FF), primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
        primAllocPtr_800960A8[bDoubleBuffer_8008D428] += sizeof(POLY_FT4);
    }
    return (VECTOR*)&s->wofs_40;
}
#endif
INCLUDE_ASM(DrawRotSprite_80044010);
extern MATRIX dword_80087114; // light matrix
// Matched
void DrawFtgObjectAt_80044D0C(FtgObject* obj, unsigned long* ot, VECTOR* pos, SVECTOR* rot, void* cam, int flags, VECTOR* scale, int slot)
{
    MATRIX* m;
    VECTOR zero;
    PushMatrix();
    RotMatrixYXZ_80046874(rot, (MATRIX*)getScratchAddr(0));
    gte_ReadRotMatrix((MATRIX*)getScratchAddr(8));
    m = (MATRIX*)getScratchAddr(8);
    m->t[0] = pos->vx - dword_8008D600.vx;
    m->t[1] = pos->vy - dword_8008D600.vy;
    m->t[2] = pos->vz - dword_8008D600.vz;
    ApplyMatrixLV(m, (VECTOR*)m->t, (VECTOR*)m->t);
    gte_MulMatrix0((MATRIX*)getScratchAddr(8), (MATRIX*)getScratchAddr(0), (MATRIX*)getScratchAddr(8));
    if (scale)
    {
        m->m[0][0] = m->m[0][0] * scale->vx / 4096;
        m->m[0][1] = m->m[0][1] * scale->vy / 4096;
        m->m[0][2] = m->m[0][2] * scale->vz / 4096;
        m->m[1][0] = m->m[1][0] * scale->vx / 4096;
        m->m[1][1] = m->m[1][1] * scale->vy / 4096;
        m->m[1][2] = m->m[1][2] * scale->vz / 4096;
        m->m[2][0] = m->m[2][0] * scale->vx / 4096;
        m->m[2][1] = m->m[2][1] * scale->vy / 4096;
        m->m[2][2] = m->m[2][2] * scale->vz / 4096;
    }
    gte_SetRotMatrix((MATRIX*)getScratchAddr(8));
    gte_SetTransMatrix((MATRIX*)getScratchAddr(8));
    PushMatrix();
    zero.vx = 0;
    zero.vy = 0;
    zero.vz = 0;
    *(MATRIX*)getScratchAddr(8) = *(MATRIX*)getScratchAddr(0);
    sub_80019D84(pos, &zero, cam, (MATRIX*)getScratchAddr(8));
    PopMatrix();
    DrawFtgObject_8004C7BC(obj, ot, flags, slot);
    PopMatrix();
    gte_SetLightMatrix(&dword_80087114);
}
// Matched
void DrawFtgObjectCurRot_800451BC(FtgObject* obj, unsigned long* ot, VECTOR* pos, void* cam, int flags, VECTOR* scale)
{
    MATRIX* m;
    VECTOR zero;
    PushMatrix();
    gte_ReadRotMatrix((MATRIX*)getScratchAddr(8));
    m = (MATRIX*)getScratchAddr(8);
    m->t[0] = pos->vx - dword_8008D600.vx;
    m->t[1] = pos->vy - dword_8008D600.vy;
    m->t[2] = pos->vz - dword_8008D600.vz;
    ApplyMatrixLV(m, (VECTOR*)m->t, (VECTOR*)m->t);
    gte_SetTransMatrix((MATRIX*)getScratchAddr(8));
    if (scale)
    {
        m->m[0][0] = m->m[0][0] * scale->vx / 4096;
        m->m[0][1] = m->m[0][1] * scale->vy / 4096;
        m->m[0][2] = m->m[0][2] * scale->vz / 4096;
        m->m[1][0] = m->m[1][0] * scale->vx / 4096;
        m->m[1][1] = m->m[1][1] * scale->vy / 4096;
        m->m[1][2] = m->m[1][2] * scale->vz / 4096;
        m->m[2][0] = m->m[2][0] * scale->vx / 4096;
        m->m[2][1] = m->m[2][1] * scale->vy / 4096;
        m->m[2][2] = m->m[2][2] * scale->vz / 4096;
    }
    gte_SetRotMatrix((MATRIX*)getScratchAddr(8));
    gte_SetTransMatrix((MATRIX*)getScratchAddr(8));
    PushMatrix();
    zero.vx = 0;
    zero.vy = 0;
    zero.vz = 0;
    sub_80019D84(pos, &zero, cam, (MATRIX*)getScratchAddr(8));
    PopMatrix();
    DrawFtgObject_8004C7BC(obj, ot, flags, 0);
    gte_SetLightMatrix(&dword_80087114);
    PopMatrix();
}
// Matched
void DrawWireTris_80045534(WireTriList* list, unsigned long* ot, VECTOR* pos, SVECTOR* rot, unsigned char* rgb)
{
    MATRIX* m;
    LINE_F2 line;
    long opz;
    long otz;
    long* sxy;
    WireTri* e;
    int i;
    int j;
    PushMatrix();
    RotMatrixZYX_8004D5CC(rot, (MATRIX*)getScratchAddr(0));
    gte_ReadRotMatrix((MATRIX*)getScratchAddr(8));
    m = (MATRIX*)getScratchAddr(8);
    m->t[0] = pos->vx - dword_8008D600.vx;
    m->t[1] = pos->vy - dword_8008D600.vy;
    m->t[2] = pos->vz - dword_8008D600.vz;
    ApplyMatrixLV(m, (VECTOR*)m->t, (VECTOR*)m->t);
    gte_MulMatrix0((MATRIX*)getScratchAddr(8), (MATRIX*)getScratchAddr(0), (MATRIX*)getScratchAddr(8));
    gte_SetRotMatrix((MATRIX*)getScratchAddr(8));
    gte_SetTransMatrix((MATRIX*)getScratchAddr(8));
    sxy = (long*)FTG_PRIM_SCRATCH;
    e = list->items;
    setLineF2(&line);
    for (i = 0; i < list->count; i++, e++)
    {
        gte_ldv3c(e->v);
        gte_rtpt();
        gte_stsxy3(&sxy[0], &sxy[1], &sxy[2]);
        gte_nclip();
        gte_stopz(&opz);
        if (opz >= 0)
        {
            gte_avsz3();
            gte_stotz(&otz);
            if (otz - 1 < 0xFFFU)
            {
                SVECTOR* v = e->v;
                for (j = 0; j < 3; j++)
                {
                    if (v[j].pad)
                    {
                        line.r0 = line.g0 = line.b0 = 0x40;
                    }
                    else
                    {
                        line.r0 = rgb[0];
                        line.g0 = rgb[1];
                        line.b0 = rgb[2];
                    }
                    *(long*)&line.x0 = sxy[j % 3];
                    *(long*)&line.x1 = sxy[(j + 1) % 3];
                    ((unsigned long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((unsigned long*)&line)[0];
                    ((unsigned long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((unsigned long*)&line)[1];
                    ((unsigned long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[2] = ((unsigned long*)&line)[2];
                    ((unsigned long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[3] = ((unsigned long*)&line)[3];
                    addPrim(ot + ((otz >> 2) & 0x3FF), primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
                    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += sizeof(LINE_F2);
                }
            }
        }
    }
    PopMatrix();
}
// Matched
void DrawSpriteVtxQuadsGT4_800459E4(SVECTOR* slots, FtgQuadRefList* list, unsigned long* ot, int flags)
{
    FtgQuadCtx* s = FTG_QUAD_CTX;
    FtgPrimGT4* t;
    unsigned int i;
    s->next_14 = (unsigned char*)primAllocPtr_800960A8[bDoubleBuffer_8008D428];
    t = (FtgPrimGT4*)FTG_PRIM_SCRATCH;
    s->ref_28 = list->items;
    t->tpage = dword_8009AAD8.tc.tpage;
    t->clut = dword_8009AAD8.tc.clut;
    for (i = 0; i < list->count; i++)
    {
        s->slot_10 = s->ref_28->v[0].slot;
        s->attr_0 = slots[s->slot_10].pad;
        if (s->attr_0 & 2)
        {
            if ((flags & 0x10) && !(s->attr_0 & 4))
            {
                s->attr_0 = flags | (s->attr_0 & ~0x60);
            }
            else
            {
                s->attr_0 = (flags & ~0x60) | s->attr_0;
            }
            s->v_18[0] = dword_800987D8[s->slot_10][s->ref_28->v[0].idx];
            s->v_18[1] = dword_800987D8[s->ref_28->v[1].slot][s->ref_28->v[1].idx];
            s->v_18[2] = dword_800987D8[s->ref_28->v[2].slot][s->ref_28->v[2].idx];
            s->v_18[3] = dword_800987D8[s->ref_28->v[3].slot][s->ref_28->v[3].idx];
            *(long*)&t->x0 = s->v_18[0]->sxy_0;
            *(long*)&t->x1 = s->v_18[1]->sxy_0;
            *(long*)&t->x2 = s->v_18[2]->sxy_0;
            gte_ldsxy3(*(long*)&t->x0, *(long*)&t->x1, *(long*)&t->x2);
            gte_nclip();
            *(long*)&t->x3 = s->v_18[3]->sxy_0;
            gte_stopz(&s->opz_8);
            gte_ldsxy3(*(long*)&t->x1, *(long*)&t->x2, *(long*)&t->x3);
            gte_nclip();
            s->otz_4 = (s->v_18[0]->sz_4 + s->v_18[1]->sz_4 + s->v_18[2]->sz_4 + s->v_18[3]->sz_4) / 16;
            gte_stopz(&s->opz2_C);
            if (s->opz_8 > 0 || s->opz2_C < 0)
            {
                if (s->otz_4 - 1 < 0xFFFU)
                {
                    {
                        unsigned long c0 = s->v_18[0]->rgbc_C;
                        unsigned long c1 = s->v_18[1]->rgbc_C;
                        unsigned long c2 = s->v_18[2]->rgbc_C;
                        unsigned long c3 = s->v_18[3]->rgbc_C;
                        t->rgbc0 = c0;
                        t->rgbc1 = c1;
                        t->rgbc2 = c2;
                        t->rgbc3 = c3;
                    }
                    t->uv0 = s->v_18[0]->uv_8;
                    t->uv1 = s->v_18[1]->uv_8;
                    t->uv2 = *(unsigned long*)&s->v_18[2]->uv_8;
                    t->uv3 = *(unsigned long*)&s->v_18[3]->uv_8;
                    setPolyGT4(t);
                    if (s->attr_0 & 0x10)
                    {
                        setSemiTrans(t, 1);
                        t->tpage &= ~0x60;
                        t->tpage |= s->attr_0 & 0x60;
                    }
                    *(FtgPrimGT4*)s->next_14 = *t;
                    addPrim(ot + ((s->otz_4 >> 2) & 0x3FF), s->next_14);
                    s->next_14 += sizeof(FtgPrimGT4);
                }
            }
        }
        s->ref_28++;
    }
    primAllocPtr_800960A8[bDoubleBuffer_8008D428] = (int)s->next_14;
    sub_8004D924();
}
// Matched
void DrawSpriteVtxQuadsG4_80045E48(FtgQuadRefList* list, unsigned long* ot, int flags)
{
    FtgQuadG4Ctx* s = FTG_QUAD_G4_CTX;
    unsigned int i;
    int otz;
    s->next_30 = (unsigned char*)primAllocPtr_800960A8[bDoubleBuffer_8008D428];
    s->ref_44 = list->items;
    setlen(&s->tpage_8, 1);
    s->tpage_8.code[0] = 0xE1000200;
    if (flags & 0x10)
    {
        s->tpage_8.code[0] |= flags & 0x60;
    }
    else
    {
        s->tpage_8.code[0] |= 0x20;
    }
    for (i = 0; i < list->count; i++)
    {
        s->v_34[0] = dword_800987D8[s->ref_44->v[0].slot][s->ref_44->v[0].idx];
        s->v_34[1] = dword_800987D8[s->ref_44->v[1].slot][s->ref_44->v[1].idx];
        s->v_34[2] = dword_800987D8[s->ref_44->v[2].slot][s->ref_44->v[2].idx];
        s->v_34[3] = dword_800987D8[s->ref_44->v[3].slot][s->ref_44->v[3].idx];
        otz = (s->v_34[0]->sz_4 + s->v_34[1]->sz_4 + s->v_34[2]->sz_4 + s->v_34[3]->sz_4) / 4;
        if (otz - 1 < 0xFFFU)
        {
            gte_ldsxy3(s->v_34[0]->sxy_0, s->v_34[1]->sxy_0, s->v_34[2]->sxy_0);
            gte_nclip();
            gte_stopz(&s->opz_0);
            gte_ldsxy3(s->v_34[1]->sxy_0, s->v_34[2]->sxy_0, s->v_34[3]->sxy_0);
            gte_nclip();
            gte_stopz(&s->opz2_4);
            if (s->opz_0 > 0 || s->opz2_4 < 0)
            {
                *(long*)&((POLY_G4*)s->next_30)->x0 = s->v_34[0]->sxy_0;
                *(long*)&((POLY_G4*)s->next_30)->x1 = s->v_34[1]->sxy_0;
                *(long*)&((POLY_G4*)s->next_30)->x2 = s->v_34[2]->sxy_0;
                *(long*)&((POLY_G4*)s->next_30)->x3 = s->v_34[3]->sxy_0;
                *(unsigned long*)&((POLY_G4*)s->next_30)->r0 = s->v_34[0]->rgbc_C;
                *(unsigned long*)&((POLY_G4*)s->next_30)->r1 = s->v_34[1]->rgbc_C;
                *(unsigned long*)&((POLY_G4*)s->next_30)->r2 = s->v_34[2]->rgbc_C;
                *(unsigned long*)&((POLY_G4*)s->next_30)->r3 = s->v_34[3]->rgbc_C;
                setPolyG4((POLY_G4*)s->next_30);
                if (flags & 0x10)
                {
                    setSemiTrans((POLY_G4*)s->next_30, 1);
                }
                addPrim(ot + ((otz >> 2) & 0x3FF), s->next_30);
                s->next_30 += sizeof(POLY_G4);
                *(DR_TPAGE*)s->next_30 = s->tpage_8;
                addPrim(ot + ((otz >> 2) & 0x3FF), s->next_30);
                s->next_30 += sizeof(DR_TPAGE);
            }
        }
        s->ref_44++;
    }
    primAllocPtr_800960A8[bDoubleBuffer_8008D428] = (int)s->next_30;
    sub_8004D924();
}
/* inline copy of sub_8004D224 */
static inline void GetBonePos(SVECTOR* o, AnimPose* p, int j)
{
    if (j == 0)
    {
        o->vx = 0;
        o->vy = 0;
        o->vz = 0;
    }
    else
    {
        o->vx = p->pos[j * 3];
        o->vy = p->pos[j * 3 + 1];
        o->vz = p->pos[j * 3 + 2];
    }
}
// Matched
void GetBoneOffsets_80046248(AnimSkel* sk, SVECTOR* out, AnimPose* alt)
{
    int n = 0;
    SVECTOR* t = (SVECTOR*)getScratchAddr(5);
    SVECTOR d;
    int k;
    int j;
    int i;
    if (sk->scale_24)
    {
        MATRIX* m = (MATRIX*)getScratchAddr(0);
        m->m[0][0] = sk->scale_24->vx;
        m->m[0][1] = 0;
        m->m[0][2] = 0;
        m->m[1][0] = 0;
        m->m[1][1] = sk->scale_24->vy;
        m->m[1][2] = 0;
        m->m[2][0] = 0;
        m->m[2][1] = 0;
        m->m[2][2] = sk->scale_24->vz;
        gte_SetRotMatrix(m);
    }
    for (i = 0; sk->bones[i].parent >= 0; n++)
    {
        j = sk->bones[i].idx;
        if (n == 1)
        {
            if (alt)
            {
                k = (sk->frame_18 * (sk->pose_14->n_4 + 2) + 1) * 3;
                t->vx = sk->pose_14->rot[k];
                t->vy = sk->pose_14->rot[k + 1];
                t->vz = sk->pose_14->rot[k + 2];
                GetBonePos(&d, alt, sk->bones[1].idx);
                t->vy += d.vy;
            }
            else
            {
                k = (sk->frame_18 * (sk->pose_14->n_4 + 2) + 1) * 3;
                t->vx = sk->pose_14->rot[k];
                t->vy = sk->pose_14->rot[k + 1];
                t->vz = sk->pose_14->rot[k + 2];
            }
        }
        else if (j == 0)
        {
            t->vx = 0;
            t->vy = 0;
            t->vz = 0;
        }
        else if (alt)
        {
            k = j * 3;
            t->vx = alt->pos[k];
            t->vy = alt->pos[k + 1];
            t->vz = alt->pos[k + 2];
        }
        else
        {
            k = j * 3;
            t->vx = sk->pose_14->pos[k];
            t->vy = sk->pose_14->pos[k + 1];
            t->vz = sk->pose_14->pos[k + 2];
        }
        if (sk->scale_24)
        {
            gte_ldv0(t);
            gte_rtv0();
            gte_stsv(t);
        }
        j = sk->bones[i].scale_3;
        if (sk->bones[i].parent > 0)
        {
            t->vx = t->vx * sk->base[j].vx / 4096;
            t->vy = t->vy * sk->base[j].vy / 4096;
            t->vz = t->vz * sk->base[j].vz / 4096;
        }
        i++;
        *out++ = *t;
    }
}
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
        o->vx = p->rot[k * 3];
        o->vy = p->rot[k * 3 + 1];
        o->vz = p->rot[k * 3 + 2];
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
        out->rot[idx * 3] = s.vx + s2.vx;
        out->rot[idx * 3 + 1] = 0;
        out->rot[idx * 3 + 2] = 0;

        if (vout != 0)
        {
            vout[i].vx = sk->base[i].vx + (v1[i].vx - sk->base[i].vx) * t1 / 4096 + (v2[i].vx - sk->base[i].vx) * t2 / 4096;
            vout[i].vy = sk->base[i].vy + (v1[i].vy - sk->base[i].vy) * t1 / 4096 + (v2[i].vy - sk->base[i].vy) * t2 / 4096;
            vout[i].vz = sk->base[i].vz + (v1[i].vz - sk->base[i].vz) * t1 / 4096 + (v2[i].vz - sk->base[i].vz) * t2 / 4096;
        }

        GetBonePos(&q0, p0, sk->bones[i].idx);
        GetBonePos(&q1, a1, sk->bones[i].idx);
        GetBonePos(&q2, a2, sk->bones[i].idx);
        d = &dword_80098690[n];
        d->vx = q0.vx + (q1.vx - q0.vx) * t1 / 4096 + (q2.vx - q0.vx) * t2 / 4096;
        d->vy = q0.vy + (q1.vy - q0.vy) * t1 / 4096 + (q2.vy - q0.vy) * t2 / 4096;
        d->vz = q0.vz + (q1.vz - q0.vz) * t1 / 4096 + (q2.vz - q0.vz) * t2 / 4096;
        if (i == 1)
        {
            d->vy -= q0.vy;
        }
        idx = sk->bones[i].idx;
        out->pos[idx * 3] = d->vx;
        out->pos[idx * 3 + 1] = d->vy;
        out->pos[idx * 3 + 2] = d->vz;
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
