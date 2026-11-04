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
#include "camera.h"
#include "skel_draw.h"
#include "engine.h"
#include "ftg_draw.h"
#include "spadstack.h"

// Matched
EventEntry* AllocEventEntry_80043AF8(EventNode* node)
{
    int i;
    int count = node->count;
    for (i = 0; i < count; i++)
    {
        EventEntry* entry = &node->entry;
        if (!(entry->flags & 1))
        {
            return entry;
        }
        node = node->next;
    }
    return 0;
}
// Matched
void StopAllEventEntries_80043B40(EventNode* node)
{
    int count = node->count;
    int i;
    for (i = 0; i < count; i++)
    {
        if (node->entry.flags & 1)
        {
            node->entry.flags = (node->entry.flags & ~1) | 0x8000;
        }
        node = node->next;
    }
}
extern short geomScreenBase_8008D51E; // projection distance
extern int AddScaledPolyFT4_80031BE4(POLY_FT4* p, unsigned long* ot, short x, short y, int sx, int sy, short* off, int fl);
// Matched
int DrawBillboard_80043B8C(POLY_FT4* poly, VECTOR* pos, short* size, int flags, short* off, short fl)
{
    BillboardScratch* scratch = BILLBOARD_SCRATCH;
    int shade;
    scratch->rel_4.vx = pos->vx - cameraEye_8008D600.vx;
    scratch->rel_4.vy = pos->vy - cameraEye_8008D600.vy;
    scratch->rel_4.vz = pos->vz - cameraEye_8008D600.vz;
    gte_ldv0(&scratch->rel_4);
    gte_rtps();
    gte_stsxy(scratch);
    gte_stszotz(&scratch->otz_C);
    if (scratch->otz_C - 1 < 0xFFFU)
    {
        scratch->w_10 = (size[0] << 7) / scratch->otz_C * cameraZoom_8008B4F8 * geomScreenBase_8008D51E / 0xA0000;
        scratch->h_14 = (size[1] << 7) / scratch->otz_C * cameraZoom_8008B4F8 * geomScreenBase_8008D51E / 0xA0000;
        if (scratch->w_10 > 0x800)
        {
            scratch->w_10 = 0x800;
        }
        if (scratch->h_14 > 0x800)
        {
            scratch->h_14 = 0x800;
        }
        poly->r0 = poly->g0 = poly->b0 = scratch->shade_18 = ((0x80 - (flags >> 16) / 32) * sceneBrightness_8008D40C) >> 12;
        if (flags & 0x10)
        {
            setSemiTrans(poly, 1);
            poly->tpage = (poly->tpage & ~0x60) | (flags & 0x60);
        }
        return AddScaledPolyFT4_80031BE4(poly, pOT_8008D690 + ((scratch->otz_C >> 2) & 0x3FF), scratch->x_0, scratch->y_2, scratch->w_10, scratch->h_14, off, fl);
    }
    return 0;
}
// Matched
int DrawBillboardRgb_80043DE0(POLY_FT4* poly, VECTOR* pos, short* size, unsigned char* rgb)
{
    BillboardScratch* scratch = BILLBOARD_SCRATCH;
    scratch->rel_4.vx = pos->vx - cameraEye_8008D600.vx;
    scratch->rel_4.vy = pos->vy - cameraEye_8008D600.vy;
    scratch->rel_4.vz = pos->vz - cameraEye_8008D600.vz;
    gte_ldv0(&scratch->rel_4);
    gte_rtps();
    gte_stsxy(scratch);
    gte_stszotz(&scratch->otz_C);
    if (scratch->otz_C - 101 < 0xF9BU)
    {
        scratch->w_10 = (size[0] << 7) / scratch->otz_C * cameraZoom_8008B4F8 * geomScreenBase_8008D51E / 0xA0000;
        scratch->h_14 = (size[1] << 7) / scratch->otz_C * cameraZoom_8008B4F8 * geomScreenBase_8008D51E / 0xA0000;
        if (scratch->w_10 > 0x800)
        {
            scratch->w_10 = 0x800;
        }
        if (scratch->h_14 > 0x800)
        {
            scratch->h_14 = 0x800;
        }
        poly->r0 = (rgb[0] * sceneBrightness_8008D40C) >> 12;
        poly->g0 = (rgb[1] * sceneBrightness_8008D40C) >> 12;
        poly->b0 = (rgb[2] * sceneBrightness_8008D40C) >> 12;
        return AddScaledPolyFT4_80031BE4(poly, pOT_8008B4C8 + ((scratch->otz_C >> 2) & 0x3FF), scratch->x_0, scratch->y_2, scratch->w_10, scratch->h_14, 0, 0x20);
    }
    return 0;
}
/* 4096-entry sine table at 0x80084540 (inside the battleCamSpline1Tail_80084350 data chunk) */
extern short battleCamSpline1Tail_80084350[];
#define SIN_TABLE (battleCamSpline1Tail_80084350 + 0xF8)
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
// Matched
VECTOR* DrawRotSprite_80044010(POLY_FT4* src, VECTOR* pos, SVECTOR* rot, short* uv, short* size, short* pivot, short* scale,
                     SVECTOR* ofs, unsigned char* rgb, short flags, int abr, unsigned long* ot)
{
    RotSpriteScratch* s = ROT_SPRITE_SCRATCH;
    short min;
    short max;
    if (flags & 1)
    {
        MATRIX m;
        s->rel_2C.vx = pos->vx - cameraEye_8008D600.vx + ofs->vx;
        s->rel_2C.vy = pos->vy - cameraEye_8008D600.vy + ofs->vy;
        s->rel_2C.vz = pos->vz - cameraEye_8008D600.vz + ofs->vz;
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
        s->rel_2C.vx = pos->vx - cameraEye_8008D600.vx + s->wofs_40.vx;
        s->rel_2C.vy = pos->vy - cameraEye_8008D600.vy + s->wofs_40.vy;
        s->rel_2C.vz = pos->vz - cameraEye_8008D600.vz + s->wofs_40.vz;
        gte_ldv0(&s->rel_2C);
        gte_rtps();
        gte_stsxy(&s->x_28);
        gte_stszotz(&s->otz_4C);
    }
    if (s->otz_4C - 1 < 0xFFFU)
    {
        s->prim_0.r0 = (rgb[0] * sceneBrightness_8008D40C) >> 12;
        s->prim_0.g0 = (rgb[1] * sceneBrightness_8008D40C) >> 12;
        s->prim_0.b0 = (rgb[2] * sceneBrightness_8008D40C) >> 12;
        if ((scale[0] * geomScreenDistance_8008B548 / 256) / s->otz_4C / 4 * cameraZoom_8008B4F8 / 4096 >= 9)
        {
            return (VECTOR*)&s->wofs_40;
        }
        s->x0_5C = (-pivot[0] * scale[0] * geomScreenDistance_8008B548 / 256) / s->otz_4C / 4;
        s->x1_64 = ((abs(size[0]) - pivot[0]) * scale[0] * geomScreenDistance_8008B548 / 256) / s->otz_4C / 4;
        s->y0_60 = (-pivot[1] * scale[1] * geomScreenDistance_8008B548 / 256) / s->otz_4C / 4;
        s->y1_68 = ((abs(size[1]) - pivot[1]) * scale[1] * geomScreenDistance_8008B548 / 256) / s->otz_4C / 4;
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
            s->sin_70 = sinTable_80084540[ofs->pad & 0xFFF];
            s->cos_6C = sinTable_80084540[(ofs->pad + 0x400) & 0xFFF];
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
        if (min > 320 || max < 0)
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
        if (min > 240 || max < 0)
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
        return (VECTOR*)&s->wofs_40;
    }
    return (VECTOR*)&s->wofs_40;
}
extern MATRIX lightMatrix_80087114; // light matrix
// Matched
void DrawFtgObjectAt_80044D0C(FtgObject* obj, unsigned long* ot, VECTOR* pos, SVECTOR* rot, PointLight* light, int flags, VECTOR* scale, int slot)
{
    MATRIX* m;
    VECTOR zero;
    PushMatrix();
    RotMatrixYXZ_80046874(rot, (MATRIX*)getScratchAddr(0));
    gte_ReadRotMatrix((MATRIX*)getScratchAddr(8));
    m = (MATRIX*)getScratchAddr(8);
    m->t[0] = pos->vx - cameraEye_8008D600.vx;
    m->t[1] = pos->vy - cameraEye_8008D600.vy;
    m->t[2] = pos->vz - cameraEye_8008D600.vz;
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
    SetModelLighting_80019D84(pos, &zero, light, (MATRIX*)getScratchAddr(8));
    PopMatrix();
    DrawFtgObject_8004C7BC(obj, ot, flags, slot);
    PopMatrix();
    gte_SetLightMatrix(&lightMatrix_80087114);
}
// Matched
void DrawFtgObjectCurRot_800451BC(FtgObject* obj, unsigned long* ot, VECTOR* pos, PointLight* light, int flags, VECTOR* scale)
{
    MATRIX* m;
    VECTOR zero;
    PushMatrix();
    gte_ReadRotMatrix((MATRIX*)getScratchAddr(8));
    m = (MATRIX*)getScratchAddr(8);
    m->t[0] = pos->vx - cameraEye_8008D600.vx;
    m->t[1] = pos->vy - cameraEye_8008D600.vy;
    m->t[2] = pos->vz - cameraEye_8008D600.vz;
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
    SetModelLighting_80019D84(pos, &zero, light, (MATRIX*)getScratchAddr(8));
    PopMatrix();
    DrawFtgObject_8004C7BC(obj, ot, flags, 0);
    gte_SetLightMatrix(&lightMatrix_80087114);
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
    WireTri* tri;
    int i;
    int j;
    PushMatrix();
    RotMatrixZYX_8004D5CC(rot, (MATRIX*)getScratchAddr(0));
    gte_ReadRotMatrix((MATRIX*)getScratchAddr(8));
    m = (MATRIX*)getScratchAddr(8);
    m->t[0] = pos->vx - cameraEye_8008D600.vx;
    m->t[1] = pos->vy - cameraEye_8008D600.vy;
    m->t[2] = pos->vz - cameraEye_8008D600.vz;
    ApplyMatrixLV(m, (VECTOR*)m->t, (VECTOR*)m->t);
    gte_MulMatrix0((MATRIX*)getScratchAddr(8), (MATRIX*)getScratchAddr(0), (MATRIX*)getScratchAddr(8));
    gte_SetRotMatrix((MATRIX*)getScratchAddr(8));
    gte_SetTransMatrix((MATRIX*)getScratchAddr(8));
    sxy = (long*)FTG_PRIM_SCRATCH;
    tri = list->items;
    setLineF2(&line);
    for (i = 0; i < list->count; i++, tri++)
    {
        gte_ldv3c(tri->v);
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
                SVECTOR* verts = tri->v;
                for (j = 0; j < 3; j++)
                {
                    if (verts[j].pad)
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
    FtgQuadCtx* ctx = FTG_QUAD_CTX;
    FtgPrimGT4* prim;
    unsigned int i;
    ctx->next_14 = (unsigned char*)primAllocPtr_800960A8[bDoubleBuffer_8008D428];
    prim = (FtgPrimGT4*)FTG_PRIM_SCRATCH;
    ctx->ref_28 = list->items;
    prim->tpage = ftgSpriteTPageClut_8009AAD8.tc.tpage;
    prim->clut = ftgSpriteTPageClut_8009AAD8.tc.clut;
    for (i = 0; i < list->count; i++)
    {
        ctx->slot_10 = ctx->ref_28->v[0].slot;
        ctx->attr_0 = slots[ctx->slot_10].pad;
        if (ctx->attr_0 & 2)
        {
            if ((flags & 0x10) && !(ctx->attr_0 & 4))
            {
                ctx->attr_0 = flags | (ctx->attr_0 & ~0x60);
            }
            else
            {
                ctx->attr_0 = (flags & ~0x60) | ctx->attr_0;
            }
            ctx->v_18[0] = ftgSpriteVtxSlots_800987D8[ctx->slot_10][ctx->ref_28->v[0].idx];
            ctx->v_18[1] = ftgSpriteVtxSlots_800987D8[ctx->ref_28->v[1].slot][ctx->ref_28->v[1].idx];
            ctx->v_18[2] = ftgSpriteVtxSlots_800987D8[ctx->ref_28->v[2].slot][ctx->ref_28->v[2].idx];
            ctx->v_18[3] = ftgSpriteVtxSlots_800987D8[ctx->ref_28->v[3].slot][ctx->ref_28->v[3].idx];
            *(long*)&prim->x0 = ctx->v_18[0]->sxy_0;
            *(long*)&prim->x1 = ctx->v_18[1]->sxy_0;
            *(long*)&prim->x2 = ctx->v_18[2]->sxy_0;
            gte_ldsxy3(*(long*)&prim->x0, *(long*)&prim->x1, *(long*)&prim->x2);
            gte_nclip();
            *(long*)&prim->x3 = ctx->v_18[3]->sxy_0;
            gte_stopz(&ctx->opz_8);
            gte_ldsxy3(*(long*)&prim->x1, *(long*)&prim->x2, *(long*)&prim->x3);
            gte_nclip();
            ctx->otz_4 = (ctx->v_18[0]->sz_4 + ctx->v_18[1]->sz_4 + ctx->v_18[2]->sz_4 + ctx->v_18[3]->sz_4) / 16;
            gte_stopz(&ctx->opz2_C);
            if (ctx->opz_8 > 0 || ctx->opz2_C < 0)
            {
                if (ctx->otz_4 - 1 < 0xFFFU)
                {
                    {
                        unsigned long c0 = ctx->v_18[0]->rgbc_C;
                        unsigned long c1 = ctx->v_18[1]->rgbc_C;
                        unsigned long c2 = ctx->v_18[2]->rgbc_C;
                        unsigned long c3 = ctx->v_18[3]->rgbc_C;
                        prim->rgbc0 = c0;
                        prim->rgbc1 = c1;
                        prim->rgbc2 = c2;
                        prim->rgbc3 = c3;
                    }
                    prim->uv0 = ctx->v_18[0]->uv_8;
                    prim->uv1 = ctx->v_18[1]->uv_8;
                    prim->uv2 = *(unsigned long*)&ctx->v_18[2]->uv_8;
                    prim->uv3 = *(unsigned long*)&ctx->v_18[3]->uv_8;
                    setPolyGT4(prim);
                    if (ctx->attr_0 & 0x10)
                    {
                        setSemiTrans(prim, 1);
                        prim->tpage &= ~0x60;
                        prim->tpage |= ctx->attr_0 & 0x60;
                    }
                    *(FtgPrimGT4*)ctx->next_14 = *prim;
                    addPrim(ot + ((ctx->otz_4 >> 2) & 0x3FF), ctx->next_14);
                    ctx->next_14 += sizeof(FtgPrimGT4);
                }
            }
        }
        ctx->ref_28++;
    }
    primAllocPtr_800960A8[bDoubleBuffer_8008D428] = (int)ctx->next_14;
    sub_8004D924();
}
// Matched
void DrawSpriteVtxQuadsG4_80045E48(FtgQuadRefList* list, unsigned long* ot, int flags)
{
    FtgQuadG4Ctx* ctx = FTG_QUAD_G4_CTX;
    unsigned int i;
    int otz;
    ctx->next_30 = (unsigned char*)primAllocPtr_800960A8[bDoubleBuffer_8008D428];
    ctx->ref_44 = list->items;
    setlen(&ctx->tpage_8, 1);
    ctx->tpage_8.code[0] = 0xE1000200;
    if (flags & 0x10)
    {
        ctx->tpage_8.code[0] |= flags & 0x60;
    }
    else
    {
        ctx->tpage_8.code[0] |= 0x20;
    }
    for (i = 0; i < list->count; i++)
    {
        ctx->v_34[0] = ftgSpriteVtxSlots_800987D8[ctx->ref_44->v[0].slot][ctx->ref_44->v[0].idx];
        ctx->v_34[1] = ftgSpriteVtxSlots_800987D8[ctx->ref_44->v[1].slot][ctx->ref_44->v[1].idx];
        ctx->v_34[2] = ftgSpriteVtxSlots_800987D8[ctx->ref_44->v[2].slot][ctx->ref_44->v[2].idx];
        ctx->v_34[3] = ftgSpriteVtxSlots_800987D8[ctx->ref_44->v[3].slot][ctx->ref_44->v[3].idx];
        otz = (ctx->v_34[0]->sz_4 + ctx->v_34[1]->sz_4 + ctx->v_34[2]->sz_4 + ctx->v_34[3]->sz_4) / 4;
        if (otz - 1 < 0xFFFU)
        {
            gte_ldsxy3(ctx->v_34[0]->sxy_0, ctx->v_34[1]->sxy_0, ctx->v_34[2]->sxy_0);
            gte_nclip();
            gte_stopz(&ctx->opz_0);
            gte_ldsxy3(ctx->v_34[1]->sxy_0, ctx->v_34[2]->sxy_0, ctx->v_34[3]->sxy_0);
            gte_nclip();
            gte_stopz(&ctx->opz2_4);
            if (ctx->opz_0 > 0 || ctx->opz2_4 < 0)
            {
                *(long*)&((POLY_G4*)ctx->next_30)->x0 = ctx->v_34[0]->sxy_0;
                *(long*)&((POLY_G4*)ctx->next_30)->x1 = ctx->v_34[1]->sxy_0;
                *(long*)&((POLY_G4*)ctx->next_30)->x2 = ctx->v_34[2]->sxy_0;
                *(long*)&((POLY_G4*)ctx->next_30)->x3 = ctx->v_34[3]->sxy_0;
                *(unsigned long*)&((POLY_G4*)ctx->next_30)->r0 = ctx->v_34[0]->rgbc_C;
                *(unsigned long*)&((POLY_G4*)ctx->next_30)->r1 = ctx->v_34[1]->rgbc_C;
                *(unsigned long*)&((POLY_G4*)ctx->next_30)->r2 = ctx->v_34[2]->rgbc_C;
                *(unsigned long*)&((POLY_G4*)ctx->next_30)->r3 = ctx->v_34[3]->rgbc_C;
                setPolyG4((POLY_G4*)ctx->next_30);
                if (flags & 0x10)
                {
                    setSemiTrans((POLY_G4*)ctx->next_30, 1);
                }
                addPrim(ot + ((otz >> 2) & 0x3FF), ctx->next_30);
                ctx->next_30 += sizeof(POLY_G4);
                *(DR_TPAGE*)ctx->next_30 = ctx->tpage_8;
                addPrim(ot + ((otz >> 2) & 0x3FF), ctx->next_30);
                ctx->next_30 += sizeof(DR_TPAGE);
            }
        }
        ctx->ref_44++;
    }
    primAllocPtr_800960A8[bDoubleBuffer_8008D428] = (int)ctx->next_30;
    sub_8004D924();
}
/* inline copy of GetBonePos_8004D224 */
static inline void GetBonePos(SVECTOR* out, AnimPose* pose, int bone)
{
    if (bone == 0)
    {
        out->vx = 0;
        out->vy = 0;
        out->vz = 0;
    }
    else
    {
        out->vx = pose->pos[bone * 3];
        out->vy = pose->pos[bone * 3 + 1];
        out->vz = pose->pos[bone * 3 + 2];
    }
}
// Matched
void GetBoneOffsets_80046248(AnimSkel* sk, SVECTOR* out, AnimPose* alt)
{
    int boneNum = 0;
    SVECTOR* offset = (SVECTOR*)getScratchAddr(5);
    SVECTOR altPos;
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
    for (i = 0; sk->bones[i].parent >= 0; boneNum++)
    {
        j = sk->bones[i].idx;
        if (boneNum == 1)
        {
            if (alt)
            {
                k = (sk->frame_18 * (sk->pose_14->n_4 + 2) + 1) * 3;
                offset->vx = sk->pose_14->rot[k];
                offset->vy = sk->pose_14->rot[k + 1];
                offset->vz = sk->pose_14->rot[k + 2];
                GetBonePos(&altPos, alt, sk->bones[1].idx);
                offset->vy += altPos.vy;
            }
            else
            {
                k = (sk->frame_18 * (sk->pose_14->n_4 + 2) + 1) * 3;
                offset->vx = sk->pose_14->rot[k];
                offset->vy = sk->pose_14->rot[k + 1];
                offset->vz = sk->pose_14->rot[k + 2];
            }
        }
        else if (j == 0)
        {
            offset->vx = 0;
            offset->vy = 0;
            offset->vz = 0;
        }
        else if (alt)
        {
            k = j * 3;
            offset->vx = alt->pos[k];
            offset->vy = alt->pos[k + 1];
            offset->vz = alt->pos[k + 2];
        }
        else
        {
            k = j * 3;
            offset->vx = sk->pose_14->pos[k];
            offset->vy = sk->pose_14->pos[k + 1];
            offset->vz = sk->pose_14->pos[k + 2];
        }
        if (sk->scale_24)
        {
            gte_ldv0(offset);
            gte_rtv0();
            gte_stsv(offset);
        }
        j = sk->bones[i].scale_3;
        if (sk->bones[i].parent > 0)
        {
            offset->vx = offset->vx * sk->base[j].vx / 4096;
            offset->vy = offset->vy * sk->base[j].vy / 4096;
            offset->vz = offset->vz * sk->base[j].vz / 4096;
        }
        i++;
        *out++ = *offset;
    }
}
// Matched
void RotMatrixZXY_8004668C(SVECTOR* rot, MATRIX* m)
{
    int cx = SIN_TABLE[(rot->vx + 0x400) & 0xFFF];
    int cz = SIN_TABLE[(rot->vz + 0x400) & 0xFFF];
    int sx = SIN_TABLE[rot->vx & 0xFFF];
    int sz = SIN_TABLE[rot->vz & 0xFFF];
    int cy = SIN_TABLE[(rot->vy + 0x400) & 0xFFF];
    int sy = SIN_TABLE[rot->vy & 0xFFF];
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
void RotMatrixYXZ_80046874(SVECTOR* rot, MATRIX* m)
{
    int cy = SIN_TABLE[(rot->vy + 0x400) & 0xFFF];
    int cx = SIN_TABLE[(rot->vx + 0x400) & 0xFFF];
    int sx = SIN_TABLE[rot->vx & 0xFFF];
    int sy = SIN_TABLE[rot->vy & 0xFFF];
    int cz = SIN_TABLE[(rot->vz + 0x400) & 0xFFF];
    int sz = SIN_TABLE[rot->vz & 0xFFF];
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

/* inlined helpers: the original keeps the bone index in a copy of the argument */
static inline void GetRot(SVECTOR* out, AnimPose* pose, int bone)
{
    int k;
    if (bone == 0)
    {
        out->vx = 0;
        out->vy = 0;
        out->vz = 0;
    }
    else
    {
        k = bone + 2;
        out->vx = pose->rot[k * 3];
        out->vy = pose->rot[k * 3 + 1];
        out->vz = pose->rot[k * 3 + 2];
    }
}
/* inline copy of RotMatrixZYX_8004D5CC */
static inline void RotZYX(SVECTOR* rot, MATRIX* m)
{
    int cz = SIN_TABLE[(rot->vz + 0x400) & 0xFFF];
    int cy = SIN_TABLE[(rot->vy + 0x400) & 0xFFF];
    int sy = SIN_TABLE[rot->vy & 0xFFF];
    int sz = SIN_TABLE[rot->vz & 0xFFF];
    int cx = SIN_TABLE[(rot->vx + 0x400) & 0xFFF];
    int sx = SIN_TABLE[rot->vx & 0xFFF];
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
/* the bone's rotation at frame f (zero for bone 0) */
static inline void GetFrameRot(SVECTOR* out, AnimPose* pose, int frame, int bone)
{
    int k;
    if (bone == 0)
    {
        out->vx = 0;
        out->vy = 0;
        out->vz = 0;
    }
    else
    {
        k = bone + 2;
        k = frame * (pose->n_4 + 2) + k;
        out->vx = pose->rot[k * 3];
        out->vy = pose->rot[k * 3 + 1];
        out->vz = pose->rot[k * 3 + 2];
    }
}
/* RotZYX followed by a rotation about x by rx->vx (applied from the left) */
static inline void RotZYXThenX(SVECTOR* rot, SVECTOR* rx, MATRIX* m)
{
    int cz = SIN_TABLE[(rot->vz + 0x400) & 0xFFF];
    int cy = SIN_TABLE[(rot->vy + 0x400) & 0xFFF];
    int sy = SIN_TABLE[rot->vy & 0xFFF];
    int sz = SIN_TABLE[rot->vz & 0xFFF];
    int cx = SIN_TABLE[(rot->vx + 0x400) & 0xFFF];
    int sx = SIN_TABLE[rot->vx & 0xFFF];
    int c;
    int s;
    int a;
    int b;
    int m00;
    int m01;
    int m02;
    int m10;
    int m11;
    int m12;
    int m21;
    int m22;
    a = (cz * sy) >> 12;
    b = (sz * sy) >> 12;
    m21 = (sx * cy) >> 12;
    m22 = (cx * cy) >> 12;
    m10 = (cy * sz) >> 12;
    m11 = ((cz * cx) >> 12) + ((b * sx) >> 12);
    m12 = -((cz * sx) >> 12) + ((b * cx) >> 12);
    m00 = (cz * cy) >> 12;
    m01 = -((sz * cx) >> 12) + ((a * sx) >> 12);
    m02 = ((sz * sx) >> 12) + ((a * cx) >> 12);
    c = SIN_TABLE[(rx->vx + 0x400) & 0xFFF];
    s = SIN_TABLE[rx->vx & 0xFFF];
    m->m[0][0] = m00;
    m->m[0][1] = m01;
    m->m[0][2] = m02;
    m->m[1][0] = ((m10 * c) >> 12) + ((sy * s) >> 12);
    m->m[2][0] = ((m10 * s) >> 12) - ((sy * c) >> 12);
    m->m[1][1] = ((m11 * c) >> 12) - ((m21 * s) >> 12);
    m->m[1][2] = ((m12 * c) >> 12) - ((m22 * s) >> 12);
    m->m[2][1] = ((m11 * s) >> 12) + ((m21 * c) >> 12);
    m->m[2][2] = ((m12 * s) >> 12) + ((m22 * c) >> 12);
}
/* adds the translation b to a */
static inline void AddTrans(long* a, long* b)
{
    a[0] += b[0];
    a[1] += b[1];
    a[2] += b[2];
}
#if 0
// Not matched: same shape and length (1274 vs 1268 words); register allocation / scheduling differ in the alt matrix, the 5-word matrix copies and the translation adds
// draws a skeleton: bone matrices from the pose (alt: bone rotations about x added from another pose), then
// each drawn bone's FTG object
void DrawAnimSkel_80046A58(AnimSkel* sk, PointLight* light, AnimPose* alt)
{
    SVECTOR rot;
    SVECTOR altRot;
    MATRIX* m;
    MATRIX* root;
    int level;
    int i;
    int flags;

    m = SKEL_MATS;
    sk->light_2C = light;
    gte_ReadRotMatrix(m);
    root = &SKEL_MATS[1];
    RotZYX(sk->rot_8, root);
    m->t[0] = sk->pos_4->vx;
    m->t[1] = sk->pos_4->vy;
    m->t[2] = sk->pos_4->vz;
    m->t[0] -= cameraEye_8008D600.vx;
    m->t[1] -= cameraEye_8008D600.vy;
    m->t[2] -= cameraEye_8008D600.vz;
    ApplyMatrixLV(m, (VECTOR*)m->t, (VECTOR*)m->t);
    m[1].t[0] = root->t[1] = root->t[2] = 0;
    GetBoneOffsets_80046248(sk, boneOffsets_80098690, alt);
    for (i = 0; (level = sk->bones[i].parent + 2) >= 2; i++)
    {
        GetFrameRot(&rot, sk->pose_14, sk->frame_18, sk->bones[i].idx);
        if (alt)
        {
            GetRot(&altRot, alt, sk->bones[i].idx);
            RotZYXThenX(&rot, &altRot, &m[level]);
        }
        else
        {
            RotZYX(&rot, &m[level]);
        }
        gte_MulMatrix0(&m[level - 1], &m[level], &m[level]);
        gte_ldv0(&boneOffsets_80098690[i]);
        gte_rtv0();
        gte_stlvnl(m[level].t);
        AddTrans(m[level].t, m[level - 1].t);
        level++;
        ((long*)boneMatrices_80098188[i].m)[0] = ((long*)m[level - 1].m)[0];
        ((long*)boneMatrices_80098188[i].m)[1] = ((long*)m[level - 1].m)[1];
        ((long*)boneMatrices_80098188[i].m)[2] = ((long*)m[level - 1].m)[2];
        ((long*)boneMatrices_80098188[i].m)[3] = ((long*)m[level - 1].m)[3];
        ((long*)boneMatrices_80098188[i].m)[4] = ((long*)m[level - 1].m)[4];
        sk->bonePos_20[i].vx = m[level - 1].t[0];
        sk->bonePos_20[i].vy = m[level - 1].t[1];
        sk->bonePos_20[i].vz = m[level - 1].t[2];
        if (sk->bones[i].flags_6 & 2)
        {
            rot.vx = m[level - 1].t[0];
            rot.vy = m[level - 1].t[1];
            rot.vz = m[level - 1].t[2];
            gte_SetRotMatrix(&m[0]);
            gte_ldv0(&rot);
            gte_rtv0();
            gte_stlvnl(m[level].t);
            AddTrans(m[level].t, m[0].t);
            boneMatrices_80096120[i].t[0] = m[level].t[0];
            boneMatrices_80096120[i].t[1] = m[level].t[1];
            boneMatrices_80096120[i].t[2] = m[level].t[2];
            gte_ldclmv(&m[level - 1]);
            gte_rtir();
            gte_stclmv(&m[level]);
            gte_ldclmv((char*)&m[level - 1] + 2);
            gte_rtir();
            gte_stclmv((char*)&m[level] + 2);
            gte_ldclmv((char*)&m[level - 1] + 4);
            gte_rtir();
            gte_stclmv((char*)&m[level] + 4);
            if (sk->base[sk->bones[i].idx].pad)
            {
                m[level].m[0][0] = m[level].m[0][0] * sk->base[sk->bones[i].idx].vx / 4096;
                m[level].m[0][1] = m[level].m[0][1] * sk->base[sk->bones[i].idx].vy / 4096;
                m[level].m[0][2] = m[level].m[0][2] * sk->base[sk->bones[i].idx].vz / 4096;
                m[level].m[1][0] = m[level].m[1][0] * sk->base[sk->bones[i].idx].vx / 4096;
                m[level].m[1][1] = m[level].m[1][1] * sk->base[sk->bones[i].idx].vy / 4096;
                m[level].m[1][2] = m[level].m[1][2] * sk->base[sk->bones[i].idx].vz / 4096;
                m[level].m[2][0] = m[level].m[2][0] * sk->base[sk->bones[i].idx].vx / 4096;
                m[level].m[2][1] = m[level].m[2][1] * sk->base[sk->bones[i].idx].vy / 4096;
                m[level].m[2][2] = m[level].m[2][2] * sk->base[sk->bones[i].idx].vz / 4096;
            }
            if (sk->scale_24)
            {
                gte_MulMatrix0(&m[level], (MATRIX*)getScratchAddr(0), &m[level]);
            }
            ((long*)boneMatrices_80096120[i].m)[0] = ((long*)m[level].m)[0];
            ((long*)boneMatrices_80096120[i].m)[1] = ((long*)m[level].m)[1];
            ((long*)boneMatrices_80096120[i].m)[2] = ((long*)m[level].m)[2];
            ((long*)boneMatrices_80096120[i].m)[3] = ((long*)m[level].m)[3];
            ((long*)boneMatrices_80096120[i].m)[4] = ((long*)m[level].m)[4];
        }
    }
    for (i = 0; sk->bones[i].parent >= 0; i++)
    {
        if (sk->bones[i].flags_6 & 2)
        {
            SetSpadStack(SPAD_STACK_ADDR);
            SetModelLighting_80019D84(sk->pos_4, (VECTOR*)&sk->bonePos_20[i], sk->light_2C, &boneMatrices_80098188[i]);
            ResetSpadStack();
            gte_SetRotMatrix(&boneMatrices_80096120[i]);
            gte_SetTransMatrix(&boneMatrices_80096120[i]);
            flags = sk->drawMode_1C;
            if ((flags & 0x10) && !(sk->bones[i].flags_6 & 4))
            {
                flags |= (short)(sk->bones[i].flags_6 & ~0x60);
            }
            else
            {
                flags = (sk->drawMode_1C & ~0x60) | sk->bones[i].flags_6;
            }
            if (!(sk->bones[i].flags_6 & 8))
            {
                flags &= 0xFFFF00FF;
            }
            SetSpadStack(SPAD_STACK_ADDR);
            DrawFtgObject_8004C7BC(&sk->ftg_0[sk->bones[i].ftg_4], sk->ot_28, flags, sk->bones[i].ftg_4);
            ResetSpadStack();
        }
    }
    m[0].t[2] = m[0].t[1] = m[0].t[0] = 0;
    gte_SetLightMatrix(&lightMatrix_80087114);
    gte_SetRotMatrix(SKEL_MATS);
    gte_SetTransMatrix(SKEL_MATS);
}
#endif
INCLUDE_ASM(DrawAnimSkel_80046A58);
/* RotZYXThenX with the last two rows computed row by row (the blend's inline copy) */
static inline void BlendRotZYXThenX(SVECTOR* rot, SVECTOR* rx, MATRIX* m)
{
    int cz = SIN_TABLE[(rot->vz + 0x400) & 0xFFF];
    int cy = SIN_TABLE[(rot->vy + 0x400) & 0xFFF];
    int sy = SIN_TABLE[rot->vy & 0xFFF];
    int sz = SIN_TABLE[rot->vz & 0xFFF];
    int cx = SIN_TABLE[(rot->vx + 0x400) & 0xFFF];
    int sx = SIN_TABLE[rot->vx & 0xFFF];
    int c;
    int s;
    int a;
    int b;
    int m00;
    int m01;
    int m02;
    int m10;
    int m11;
    int m12;
    int m21;
    int m22;
    a = (cz * sy) >> 12;
    b = (sz * sy) >> 12;
    m21 = (sx * cy) >> 12;
    m22 = (cx * cy) >> 12;
    m10 = (cy * sz) >> 12;
    m11 = ((cz * cx) >> 12) + ((b * sx) >> 12);
    m12 = -((cz * sx) >> 12) + ((b * cx) >> 12);
    m00 = (cz * cy) >> 12;
    m01 = -((sz * cx) >> 12) + ((a * sx) >> 12);
    m02 = ((sz * sx) >> 12) + ((a * cx) >> 12);
    c = SIN_TABLE[(rx->vx + 0x400) & 0xFFF];
    s = SIN_TABLE[rx->vx & 0xFFF];
    m->m[0][0] = m00;
    m->m[0][1] = m01;
    m->m[0][2] = m02;
    m->m[1][0] = ((m10 * c) >> 12) + ((sy * s) >> 12);
    m->m[1][1] = ((m11 * c) >> 12) - ((m21 * s) >> 12);
    m->m[1][2] = ((m12 * c) >> 12) - ((m22 * s) >> 12);
    m->m[2][0] = ((m10 * s) >> 12) - ((sy * c) >> 12);
    m->m[2][1] = ((m11 * s) >> 12) + ((m21 * c) >> 12);
    m->m[2][2] = ((m12 * s) >> 12) + ((m22 * c) >> 12);
}
/* RotZYX with the matrix stored column by column (the blend's inline copy) */
static inline void BlendRotZYX(SVECTOR* rot, MATRIX* m)
{
    int cz = SIN_TABLE[(rot->vz + 0x400) & 0xFFF];
    int cy = SIN_TABLE[(rot->vy + 0x400) & 0xFFF];
    int sy = SIN_TABLE[rot->vy & 0xFFF];
    int sz = SIN_TABLE[rot->vz & 0xFFF];
    int cx = SIN_TABLE[(rot->vx + 0x400) & 0xFFF];
    int sx = SIN_TABLE[rot->vx & 0xFFF];
    int a;
    int b;
    a = (cz * sy) >> 12;
    b = (sz * sy) >> 12;
    m->m[0][0] = (cz * cy) >> 12;
    m->m[1][0] = (sz * cy) >> 12;
    m->m[2][0] = -sy;
    m->m[0][1] = -((sz * cx) >> 12) + ((a * sx) >> 12);
    m->m[1][1] = ((cz * cx) >> 12) + ((b * sx) >> 12);
    m->m[2][1] = (cy * sx) >> 12;
    m->m[0][2] = ((sz * sx) >> 12) + ((a * cx) >> 12);
    m->m[2][2] = (cy * cx) >> 12;
    m->m[1][2] = -((cz * sx) >> 12) + ((b * cx) >> 12);
}
/* the root bone's offset at frame f (stored after the rotations of each frame) */
static inline void GetRootOfs(SVECTOR* out, AnimPose* pose, int frame)
{
    int k = frame * (pose->n_4 + 2) + 1;
    out->vx = pose->rot[k * 3];
    out->vy = pose->rot[k * 3 + 1];
    out->vz = pose->rot[k * 3 + 2];
}
/* GetFrameRot keeping bone + 2 in the argument */
static inline void BlendFrameRot(SVECTOR* out, AnimPose* pose, int frame, int bone)
{
    int k;
    if (bone == 0)
    {
        out->vx = 0;
        out->vy = 0;
        out->vz = 0;
    }
    else
    {
        bone += 2;
        k = frame * (pose->n_4 + 2) + bone;
        out->vx = pose->rot[k * 3];
        out->vy = pose->rot[k * 3 + 1];
        out->vz = pose->rot[k * 3 + 2];
    }
}
// DrawAnimSkel_80046A58 blending two poses: the bone rotations are interpolated by t through the axis / angle of the
// relative rotation (GetRotationAxis_8004AD44 / BasisFromAxis_8004B0A8), the bone offsets and per-bone scales linearly
// Matched
void DrawAnimSkelBlend_80047E28(AnimSkel* sk, SVECTOR* scale2, AnimPose* pose2, int frame2, int t, PointLight* light, AnimPose* alt)
{
    VECTOR root;
    MATRIX axis[40];
    MATRIX axisT[40];
    MATRIX rel[40];
    int angle[40];
    union
    {
        MATRIX m;
        VECTOR l;
        SVECTOR v[4];
        int s[8];
    } tmp;
    MATRIX d;
    MATRIX ma;
    MATRIX mb;
    SVECTOR r1;
    SVECTOR r2;
    SVECTOR r3;
    union
    {
        VECTOR l;
        SVECTOR v;
    } acc;
    int i;
    int n;
    MATRIX* m;
    MATRIX* mr;
    int k;
    int a;
    int flags;

    PushMatrix();
    m = SKEL_MATS;
    gte_ReadRotMatrix(m);
    mr = &SKEL_MATS[1];
    BlendRotZYX(sk->rot_8, mr);
    root.vx = sk->pos_4->vx;
    root.vy = sk->pos_4->vy;
    root.vz = sk->pos_4->vz;
    root.vx -= cameraEye_8008D600.vx;
    root.vy -= cameraEye_8008D600.vy;
    root.vz -= cameraEye_8008D600.vz;
    ApplyMatrixLV(SKEL_MATS, &root, &root);
    for (i = 0; sk->bones[i].parent >= 0; i++)
    {
        n = sk->bones[i].parent + 2;
        BlendFrameRot(&r1, sk->pose_14, sk->frame_18, sk->bones[i].idx);
        BlendFrameRot(&r2, pose2, frame2, sk->bones[i].idx);
        if (alt)
        {
            GetRot(&r3, alt, sk->bones[i].idx);
            BlendRotZYXThenX(&r1, &r3, &ma);
            BlendRotZYXThenX(&r2, &r3, &mb);
        }
        else
        {
            BlendRotZYX(&r1, &ma);
            BlendRotZYX(&r2, &mb);
        }
        TransposeMatrix(&ma, &d);
        gte_MulMatrix0(&d, &mb, &d);
        if (IsIdMatrix(&d) == 1)
        {
            m[n] = ma;
        }
        else
        {
            GetRotationAxis_8004AD44(&d, &acc.l);
            BasisFromAxis_8004B0A8(&acc.l, &axis[i]);
            TransposeMatrix(&axis[i], &axisT[i]);
            gte_MulMatrix0(&axisT[i], &d, &tmp.m);
            gte_MulMatrix0(&tmp.m, &axis[i], &rel[i]);
            angle[i] = ratan2(rel[i].m[1][2], rel[i].m[1][1]);
            a = angle[i] * t / 4096;
            if (abs(a) <= 0)
            {
                m[n] = ma;
            }
            else
            {
                rel[i].m[1][1] = SIN_TABLE[(a + 0x400) & 0xFFF];
                rel[i].m[1][2] = SIN_TABLE[a & 0xFFF];
                rel[i].m[2][1] = -rel[i].m[1][2];
                rel[i].m[2][2] = rel[i].m[1][1];
                gte_MulMatrix0(&axis[i], &rel[i], &tmp.m);
                gte_MulMatrix0(&tmp.m, &axisT[i], &d);
                gte_MulMatrix0(&ma, &d, &m[n]);
            }
        }
        gte_MulMatrix0(&m[n - 1], &m[n], &m[n]);
        if (alt)
        {
            if (i == 1)
            {
                GetRootOfs(&boneOffsets_80098690[n], sk->pose_14, sk->frame_18);
                GetBonePos(&acc.v, alt, sk->bones[1].idx);
                // only the height of the alt pose's root is taken over; the original still reads x and z
                boneOffsets_80098690[n].vx += 0;
                boneOffsets_80098690[n].vy += acc.v.vy;
                boneOffsets_80098690[n].vz += 0;
            }
            else
            {
                GetBonePos(&boneOffsets_80098690[n], alt, sk->bones[i].idx);
            }
        }
        else
        {
            if (i == 1)
            {
                GetRootOfs(&acc.v, sk->pose_14, sk->frame_18);
                GetRootOfs(&tmp.v[0], pose2, frame2);
                LerpSVector_8004D7A8(&acc.v, &tmp.v[0], &boneOffsets_80098690[n], t);
            }
            else
            {
                GetBonePos(&tmp.v[1], sk->pose_14, sk->bones[i].idx);
                GetBonePos(&tmp.v[2], pose2, sk->bones[i].idx);
                LerpSVector_8004D7A8(&tmp.v[1], &tmp.v[2], &boneOffsets_80098690[n], t);
            }
            if (sk->bones[i].parent > 0)
            {
                int s = sk->bones[i].scale_3;
                boneOffsets_80098690[n].vx = boneOffsets_80098690[n].vx * (sk->base[s].vx + (scale2[s].vx - sk->base[s].vx) * t / 4096) / 4096;
                boneOffsets_80098690[n].vy = boneOffsets_80098690[n].vy * (sk->base[s].vy + (scale2[s].vy - sk->base[s].vy) * t / 4096) / 4096;
                boneOffsets_80098690[n].vz = boneOffsets_80098690[n].vz * (sk->base[s].vz + (scale2[s].vz - sk->base[s].vz) * t / 4096) / 4096;
            }
        }
        if (sk->scale_24)
        {
            boneOffsets_80098690[n].vx = boneOffsets_80098690[n].vx * sk->scale_24->vx / 4096;
            boneOffsets_80098690[n].vy = boneOffsets_80098690[n].vy * sk->scale_24->vy / 4096;
            boneOffsets_80098690[n].vz = boneOffsets_80098690[n].vz * sk->scale_24->vz / 4096;
        }
        n++;
        boneMatrices_80098188[i] = m[n - 1];
        if (sk->bones[i].flags_6 & 2)
        {
            acc.l.vx = acc.l.vy = acc.l.vz = 0;
            for (k = 0; k < n - 2; k++)
            {
                gte_SetRotMatrix(&m[k + 1]);
                gte_ldv0(&boneOffsets_80098690[k + 2]);
                gte_rtv0();
                gte_stlvnl(&tmp.l);
                acc.l.vx += tmp.l.vx;
                acc.l.vy += tmp.l.vy;
                acc.l.vz += tmp.l.vz;
            }
            sk->bonePos_20[i].vx = acc.l.vx;
            sk->bonePos_20[i].vy = acc.l.vy;
            sk->bonePos_20[i].vz = acc.l.vz;
            ApplyMatrixLV(m, &acc.l, &acc.l);
            acc.l.vx += root.vx;
            acc.l.vy += root.vy;
            acc.l.vz += root.vz;
            gte_MulMatrix0(m, &m[n - 1], &m[n]);
            tmp.s[4] = sk->base[sk->bones[i].idx].vx + (scale2[sk->bones[i].idx].vx - sk->base[sk->bones[i].idx].vx) * t / 4096;
            tmp.s[5] = sk->base[sk->bones[i].idx].vy + (scale2[sk->bones[i].idx].vy - sk->base[sk->bones[i].idx].vy) * t / 4096;
            tmp.s[6] = sk->base[sk->bones[i].idx].vz + (scale2[sk->bones[i].idx].vz - sk->base[sk->bones[i].idx].vz) * t / 4096;
            m[n].m[0][0] = m[n].m[0][0] * tmp.s[4] / 4096;
            m[n].m[0][1] = m[n].m[0][1] * tmp.s[5] / 4096;
            m[n].m[0][2] = m[n].m[0][2] * tmp.s[6] / 4096;
            m[n].m[1][0] = m[n].m[1][0] * tmp.s[4] / 4096;
            m[n].m[1][1] = m[n].m[1][1] * tmp.s[5] / 4096;
            m[n].m[1][2] = m[n].m[1][2] * tmp.s[6] / 4096;
            m[n].m[2][0] = m[n].m[2][0] * tmp.s[4] / 4096;
            m[n].m[2][1] = m[n].m[2][1] * tmp.s[5] / 4096;
            m[n].m[2][2] = m[n].m[2][2] * tmp.s[6] / 4096;
            if (sk->scale_24)
            {
                m[n].m[0][0] = m[n].m[0][0] * sk->scale_24->vx / 4096;
                m[n].m[0][1] = m[n].m[0][1] * sk->scale_24->vy / 4096;
                m[n].m[0][2] = m[n].m[0][2] * sk->scale_24->vz / 4096;
                m[n].m[1][0] = m[n].m[1][0] * sk->scale_24->vx / 4096;
                m[n].m[1][1] = m[n].m[1][1] * sk->scale_24->vy / 4096;
                m[n].m[1][2] = m[n].m[1][2] * sk->scale_24->vz / 4096;
                m[n].m[2][0] = m[n].m[2][0] * sk->scale_24->vx / 4096;
                m[n].m[2][1] = m[n].m[2][1] * sk->scale_24->vy / 4096;
                m[n].m[2][2] = m[n].m[2][2] * sk->scale_24->vz / 4096;
            }
            m[n].t[0] = acc.l.vx;
            m[n].t[1] = acc.l.vy;
            m[n].t[2] = acc.l.vz;
            boneMatrices_80096120[i] = m[n];
        }
    }
    for (i = 0; sk->bones[i].parent >= 0; i++)
    {
        if (sk->bones[i].flags_6 & 2)
        {
            SetModelLighting_80019D84(sk->pos_4, (VECTOR*)&sk->bonePos_20[i], light, &boneMatrices_80098188[i]);
            gte_SetRotMatrix(&boneMatrices_80096120[i]);
            gte_SetTransMatrix(&boneMatrices_80096120[i]);
            flags = sk->drawMode_1C;
            if ((flags & 0x10) && !(sk->bones[i].flags_6 & 4))
            {
                flags |= (short)(sk->bones[i].flags_6 & ~0x60);
            }
            else
            {
                flags = (sk->drawMode_1C & ~0x60) | sk->bones[i].flags_6;
            }
            if (!(sk->bones[i].flags_6 & 8))
            {
                flags &= 0xFFFF00FF;
            }
            DrawFtgObject_8004C7BC(&sk->ftg_0[sk->bones[i].ftg_4], sk->ot_28, flags, sk->bones[i].ftg_4);
        }
    }
    gte_SetLightMatrix(&lightMatrix_80087114);
    gte_SetRotMatrix(m);
    PopMatrix();
}

// Matched
void BlendSkelPoses_8004A4FC(AnimSkel* sk, SVECTOR* scale1, AnimPose* pose1, int t1, SVECTOR* scale2, AnimPose* pose2, int t2,
                  AnimPose* rotBase, AnimPose* posBase, AnimPose* out, SVECTOR* vout)
{
    SVECTOR blend1;
    SVECTOR baseRot;
    SVECTOR rot1;
    SVECTOR rot2;
    SVECTOR blend2;
    SVECTOR basePos;
    SVECTOR pos1;
    SVECTOR pos2;
    SVECTOR* offset;
    int i;
    int delta;
    int level;
    int idx;

    for (i = 0; sk->bones[i].parent >= 0; i++)
    {
        level = sk->bones[i].parent + 2;
        GetRot(&baseRot, rotBase, sk->bones[i].idx);
        GetRot(&rot1, pose1, sk->bones[i].idx);
        GetRot(&rot2, pose2, sk->bones[i].idx);

        delta = (rot1.vx - baseRot.vx) & 0xFFF;
        if (delta >= 0x800)
            delta -= 0x1000;
        blend1.vx = (baseRot.vx + delta * t1 / 4096) & 0xFFF;
        delta = (rot1.vy - baseRot.vy) & 0xFFF;
        if (delta >= 0x800)
            delta -= 0x1000;
        blend1.vy = (baseRot.vy + delta * t1 / 4096) & 0xFFF;
        delta = (rot1.vz - baseRot.vz) & 0xFFF;
        if (delta >= 0x800)
            delta -= 0x1000;
        blend1.vz = (baseRot.vz + delta * t1 / 4096) & 0xFFF;
        blend1.vx = blend1.vx - baseRot.vx;
        blend1.vy = 0;
        blend1.vz = 0;

        delta = (rot2.vx - baseRot.vx) & 0xFFF;
        if (delta >= 0x800)
            delta -= 0x1000;
        blend2.vx = (baseRot.vx + delta * t2 / 4096) & 0xFFF;
        delta = (rot2.vy - baseRot.vy) & 0xFFF;
        if (delta >= 0x800)
            delta -= 0x1000;
        blend2.vy = (baseRot.vy + delta * t2 / 4096) & 0xFFF;
        delta = (rot2.vz - baseRot.vz) & 0xFFF;
        if (delta >= 0x800)
            delta -= 0x1000;
        blend2.vz = (baseRot.vz + delta * t2 / 4096) & 0xFFF;
        blend2.vy = 0;
        blend2.vz = 0;
        blend2.vx = blend2.vx - baseRot.vx;

        idx = sk->bones[i].idx + 2;
        out->rot[idx * 3] = blend1.vx + blend2.vx;
        out->rot[idx * 3 + 1] = 0;
        out->rot[idx * 3 + 2] = 0;

        if (vout != 0)
        {
            vout[i].vx = sk->base[i].vx + (scale1[i].vx - sk->base[i].vx) * t1 / 4096 + (scale2[i].vx - sk->base[i].vx) * t2 / 4096;
            vout[i].vy = sk->base[i].vy + (scale1[i].vy - sk->base[i].vy) * t1 / 4096 + (scale2[i].vy - sk->base[i].vy) * t2 / 4096;
            vout[i].vz = sk->base[i].vz + (scale1[i].vz - sk->base[i].vz) * t1 / 4096 + (scale2[i].vz - sk->base[i].vz) * t2 / 4096;
        }

        GetBonePos(&basePos, posBase, sk->bones[i].idx);
        GetBonePos(&pos1, pose1, sk->bones[i].idx);
        GetBonePos(&pos2, pose2, sk->bones[i].idx);
        offset = &boneOffsets_80098690[level];
        offset->vx = basePos.vx + (pos1.vx - basePos.vx) * t1 / 4096 + (pos2.vx - basePos.vx) * t2 / 4096;
        offset->vy = basePos.vy + (pos1.vy - basePos.vy) * t1 / 4096 + (pos2.vy - basePos.vy) * t2 / 4096;
        offset->vz = basePos.vz + (pos1.vz - basePos.vz) * t1 / 4096 + (pos2.vz - basePos.vz) * t2 / 4096;
        if (i == 1)
        {
            offset->vy -= basePos.vy;
        }
        idx = sk->bones[i].idx;
        out->pos[idx * 3] = offset->vx;
        out->pos[idx * 3 + 1] = offset->vy;
        out->pos[idx * 3 + 2] = offset->vz;
    }
}
// Matched
void GetRotationAxis_8004AD44(MATRIX* in, VECTOR* out)
{
    MATRIX m;
    int cofactors[9];
    int rows[6];
    VECTOR axis;
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
    cofactors[0] = m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1];
    cofactors[1] = m.m[1][0] * m.m[2][2] - m.m[0][2] * m.m[2][0];
    cofactors[2] = m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0];
    cofactors[3] = m.m[0][1] * m.m[2][2] - m.m[0][2] * m.m[2][1];
    cofactors[4] = m.m[0][0] * m.m[2][2] - m.m[0][2] * m.m[2][0];
    cofactors[5] = m.m[0][0] * m.m[2][1] - m.m[0][1] * m.m[2][0];
    cofactors[6] = m.m[0][1] * m.m[2][2] - m.m[0][2] * m.m[2][1];
    cofactors[7] = m.m[0][0] * m.m[1][2] - m.m[0][2] * m.m[1][0];
    cofactors[8] = m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0];
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (cofactors[i * 3 + j] < 0)
            {
                cofactors[i * 3 + j] = -cofactors[i * 3 + j];
            }
        }
    }
    idx = 0;
    max = cofactors[0];
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (max < cofactors[i * 3 + j])
            {
                idx = i * 3 + j;
                max = cofactors[i * 3 + j];
            }
        }
    }
    switch (idx)
    {
    case 6:
    case 7:
    case 8:
        rows[0] = m.m[0][0];
        rows[1] = m.m[0][1];
        rows[2] = m.m[0][2];
        rows[3] = m.m[1][0];
        rows[4] = m.m[1][1];
        rows[5] = m.m[1][2];
        break;
    case 3:
    case 4:
    case 5:
        rows[0] = m.m[0][0];
        rows[1] = m.m[0][1];
        rows[2] = m.m[0][2];
        rows[3] = m.m[2][0];
        rows[4] = m.m[2][1];
        rows[5] = m.m[2][2];
        break;
    case 0:
    case 1:
    case 2:
        rows[0] = m.m[1][0];
        rows[1] = m.m[1][1];
        rows[2] = m.m[1][2];
        rows[3] = m.m[2][0];
        rows[4] = m.m[2][1];
        rows[5] = m.m[2][2];
        break;
    }
    OuterProduct12((VECTOR*)&rows[0], (VECTOR*)&rows[3], &axis);
    VectorNormal(&axis, out);
}

MATRIX boneMatrices_80096120[40] BSS = { 0 };
int dword_80096620[2] BSS = { 0 };
int dword_80096628[1750] BSS = { 0 };
