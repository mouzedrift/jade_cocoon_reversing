#include "common.h"
#include "funcs.h"
#include "sdk.h"
#include "globals.h"
#include "sound.h"
#include "data_decls.h"
#include "gte.h"
#include "ftg_draw.h"
#include "skel_draw.h"
/* defined further on / elsewhere without a prototype the callers see */
void RotMatrixZXY_8004668C(SVECTOR* rot, MATRIX* m);
void ScaleVectorToFit_8003B684(int* v);


#define ABS_8004B0A8(x) ((x) < 0 ? -(x) : (x))
void BasisFromAxis_8004B0A8(VECTOR* axis, MATRIX* m)
{
    VECTOR tangent;
    VECTOR cross;
    VECTOR n0;
    VECTOR n1;
    VECTOR n2;
    int ax;
    int ay;
    int az;
    ScaleVectorToFit_8003B684((int*)axis);
    VectorNormal(axis, &n0);
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
            tangent.vx = n0.vy;
            tangent.vy = -n0.vx;
            if (n0.vz)
            {
                tangent.vz = -(n0.vx * tangent.vx + n0.vy * tangent.vy) / n0.vz;
            }
            else
            {
                tangent.vz = 0;
            }
        }
        else
        {
            if (n0.vy)
            {
                tangent.vz = n0.vy;
                tangent.vy = -n0.vz;
            }
            else
            {
                tangent.vz = 0;
                tangent.vy = n0.vz;
            }
            if (n0.vx)
            {
                tangent.vx = -(n0.vz * tangent.vz + n0.vy * tangent.vy) / n0.vx;
            }
            else
            {
                tangent.vx = 0;
            }
        }
    }
    else
    {
        az = ABS_8004B0A8(n0.vz);
        if (az < ay)
        {
            tangent.vx = n0.vy;
            tangent.vy = -n0.vx;
            if (n0.vz)
            {
                tangent.vz = -(n0.vx * tangent.vx + n0.vy * tangent.vy) / n0.vz;
            }
            else
            {
                tangent.vz = 0;
            }
        }
        else
        {
            if (n0.vz)
            {
                tangent.vx = n0.vz;
                tangent.vz = -n0.vx;
            }
            else
            {
                tangent.vx = 0;
                tangent.vz = n0.vx;
            }
            if (n0.vy)
            {
                tangent.vy = -(n0.vx * tangent.vx + n0.vz * tangent.vz) / n0.vy;
            }
            else
            {
                tangent.vy = 0;
            }
        }
    }
    ScaleVectorToFit_8003B684((int*)&tangent);
    VectorNormal(&tangent, &n1);
    m->m[0][1] = n1.vx;
    m->m[1][1] = n1.vy;
    m->m[2][1] = n1.vz;
    OuterProduct12(&n0, &n1, &cross);
    ScaleVectorToFit_8003B684((int*)&cross);
    VectorNormal(&cross, &n2);
    m->m[0][2] = n2.vx;
    m->m[1][2] = n2.vy;
    m->m[2][2] = n2.vz;
}
void DrawFtgPolyF3_8004B320(FtgObject* obj, OT_TYPE* ot, FtgDrawCtx* ctx)
{
    POLY_F3* prim = (POLY_F3*)FTG_PRIM_SCRATCH;
    FtgPolyF3* poly = obj->f3_0.items;
    int i;
    setPolyF3(prim);
    for (i = 0; i < obj->f3_0.count; i++, poly++)
    {
        FtgVert* normal = &poly->n;
        gte_ldv3c(poly->v);
        gte_rtpt();
        gte_stsxy3_f3(prim);
        gte_nclip();
        gte_stopz(&ctx->opz_10);
        if (ctx->opz_10 > 0)
        {
            gte_avsz3();
            gte_stotz(&ctx->otz_8);
            if (ctx->otz_8 - 1 < 0xFFFU)
            {
                if (ctx->flags_20 & 1)
                {
                    gte_ldv0(normal);
                    gte_ldrgb(&poly->c);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    gte_strgb(&prim->r0);
                }
                else
                {
                    gte_ldrgb(&poly->c);
                    gte_lddp(ctx->dq_C);
                    gte_dpcs();
                    gte_strgb(&prim->r0);
                }
                if (ctx->flags_20 & 0x10)
                {
                    setSemiTrans(prim, 1);
                }
                *(POLY_F3*)ctx->next_18 = *prim;
                addPrim(ot + ((ctx->otz_8 >> 2) & 0x3FF), ctx->next_18);
                ctx->next_18 += sizeof(POLY_F3);
                ((DR_TPAGE*)ctx->next_18)->tag = ctx->tpage_0.tag;
                ((DR_TPAGE*)ctx->next_18)->code[0] = ctx->tpage_0.code[0];
                addPrim(ot + ((ctx->otz_8 >> 2) & 0x3FF), ctx->next_18);
                ctx->next_18 += sizeof(DR_TPAGE);
            }
        }
    }
}
void DrawFtgPolyF4_8004B590(FtgObject* obj, OT_TYPE* ot, FtgDrawCtx* ctx)
{
    POLY_F4* prim = (POLY_F4*)FTG_PRIM_SCRATCH;
    FtgPolyF4* poly = obj->f4_20.items;
    int i;
    setPolyF4(prim);
    for (i = 0; i < obj->f4_20.count; i++, poly++)
    {
        FtgVert* normal = &poly->n;
        gte_ldv3c(poly->v);
        gte_rtpt();
        gte_nclip();
        gte_stopz(&ctx->opz_10);
        gte_stsxy3_f4(prim);
        gte_ldv0(&poly->v[3]);
        gte_rtps();
        gte_nclip();
        gte_stopz(&ctx->opz2_14);
        if (ctx->opz_10 > 0 || ctx->opz2_14 < 0)
        {
            gte_avsz4();
            gte_stotz(&ctx->otz_8);
            if (ctx->otz_8 - 1 < 0xFFFU)
            {
                gte_stsxy(&prim->x3);
                if (ctx->flags_20 & 1)
                {
                    gte_ldv0(normal);
                    gte_ldrgb(&poly->c);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    gte_strgb(&prim->r0);
                }
                else
                {
                    gte_ldrgb(&poly->c);
                    gte_lddp(ctx->dq_C);
                    gte_dpcs();
                    gte_strgb(&prim->r0);
                }
                if (ctx->flags_20 & 0x10)
                {
                    setSemiTrans(prim, 1);
                }
                *(POLY_F4*)ctx->next_18 = *prim;
                addPrim(ot + ((ctx->otz_8 >> 2) & 0x3FF), ctx->next_18);
                ctx->next_18 += sizeof(POLY_F4);
                ((DR_TPAGE*)ctx->next_18)->tag = ctx->tpage_0.tag;
                ((DR_TPAGE*)ctx->next_18)->code[0] = ctx->tpage_0.code[0];
                addPrim(ot + ((ctx->otz_8 >> 2) & 0x3FF), ctx->next_18);
                ctx->next_18 += sizeof(DR_TPAGE);
            }
        }
    }
}
void DrawFtgPolyG3_8004B844(FtgObject* obj, OT_TYPE* ot, FtgDrawCtx* ctx)
{
    POLY_G3* prim = (POLY_G3*)FTG_PRIM_SCRATCH;
    FtgPolyG3* poly = obj->g3_8.items;
    int i;
    setPolyG3(prim);
    for (i = 0; i < obj->g3_8.count; i++, poly++)
    {
        FtgVert* normal = poly->n;
        gte_ldv3c(poly->v);
        gte_rtpt();
        gte_stsxy3_g3(prim);
        gte_nclip();
        gte_stopz(&ctx->opz_10);
        if (ctx->opz_10 > 0)
        {
            gte_avsz3();
            gte_stotz(&ctx->otz_8);
            if (ctx->otz_8 - 1 < 0xFFFU)
            {
                if (ctx->flags_20 & 1)
                {
                    gte_ldv0(normal);
                    gte_ldrgb(&poly->c[0]);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    gte_strgb(&prim->r0);
                    gte_ldv0(&poly->n[1]);
                    gte_ldrgb(&poly->c[1]);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    gte_strgb(&prim->r1);
                    gte_ldv0(&poly->n[2]);
                    gte_ldrgb(&poly->c[2]);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    gte_strgb(&prim->r2);
                }
                else
                {
                    gte_ldrgb(&poly->c[0]);
                    gte_lddp(ctx->dq_C);
                    gte_dpcs();
                    gte_strgb(&prim->r0);
                    gte_ldrgb(&poly->c[1]);
                    gte_lddp(ctx->dq_C);
                    gte_dpcs();
                    gte_strgb(&prim->r1);
                    gte_ldrgb(&poly->c[2]);
                    gte_lddp(ctx->dq_C);
                    gte_dpcs();
                    gte_strgb(&prim->r2);
                }
                if (ctx->flags_20 & 0x10)
                {
                    setSemiTrans(prim, 1);
                }
                *(POLY_G3*)ctx->next_18 = *prim;
                addPrim(ot + ((ctx->otz_8 >> 2) & 0x3FF), ctx->next_18);
                ctx->next_18 += sizeof(POLY_G3);
                ((DR_TPAGE*)ctx->next_18)->tag = ctx->tpage_0.tag;
                ((DR_TPAGE*)ctx->next_18)->code[0] = ctx->tpage_0.code[0];
                addPrim(ot + ((ctx->otz_8 >> 2) & 0x3FF), ctx->next_18);
                ctx->next_18 += sizeof(DR_TPAGE);
            }
        }
    }
}
void DrawFtgPolyG4_8004BB9C(FtgObject* obj, OT_TYPE* ot, FtgDrawCtx* ctx)
{
    POLY_G4* prim = (POLY_G4*)FTG_PRIM_SCRATCH;
    FtgPolyG4* poly = obj->g4_28.items;
    int i;
    setPolyG4(prim);
    for (i = 0; i < obj->g4_28.count; i++, poly++)
    {
        FtgVert* normal = poly->n;
        gte_ldv3c(poly->v);
        gte_rtpt();
        gte_nclip();
        gte_stopz(&ctx->opz_10);
        gte_stsxy3_g4(prim);
        gte_ldv0(&poly->v[3]);
        gte_rtps();
        gte_nclip();
        gte_stopz(&ctx->opz2_14);
        if (ctx->opz_10 > 0 || ctx->opz2_14 < 0)
        {
            gte_avsz4();
            gte_stotz(&ctx->otz_8);
            if (ctx->otz_8 - 1 < 0xFFFU)
            {
                gte_stsxy(&prim->x3);
                if (ctx->flags_20 & 1)
                {
                    gte_ldv0(normal);
                    gte_ldrgb(&poly->c[0]);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    gte_strgb(&prim->r0);
                    gte_ldv0(&poly->n[1]);
                    gte_ldrgb(&poly->c[1]);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    gte_strgb(&prim->r1);
                    gte_ldv0(&poly->n[2]);
                    gte_ldrgb(&poly->c[2]);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    gte_strgb(&prim->r2);
                    gte_ldv0(&poly->n[3]);
                    gte_ldrgb(&poly->c[3]);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    gte_strgb(&prim->r3);
                }
                else
                {
                    gte_ldrgb(&poly->c[0]);
                    gte_lddp(ctx->dq_C);
                    gte_dpcs();
                    gte_strgb(&prim->r0);
                    gte_ldrgb(&poly->c[1]);
                    gte_lddp(ctx->dq_C);
                    gte_dpcs();
                    gte_strgb(&prim->r1);
                    gte_ldrgb(&poly->c[2]);
                    gte_lddp(ctx->dq_C);
                    gte_dpcs();
                    gte_strgb(&prim->r2);
                    gte_ldrgb(&poly->c[3]);
                    gte_lddp(ctx->dq_C);
                    gte_dpcs();
                    gte_strgb(&prim->r3);
                }
                if (ctx->flags_20 & 0x10)
                {
                    setSemiTrans(prim, 1);
                }
                *(POLY_G4*)ctx->next_18 = *prim;
                addPrim(ot + ((ctx->otz_8 >> 2) & 0x3FF), ctx->next_18);
                ctx->next_18 += sizeof(POLY_G4);
                ((DR_TPAGE*)ctx->next_18)->tag = ctx->tpage_0.tag;
                ((DR_TPAGE*)ctx->next_18)->code[0] = ctx->tpage_0.code[0];
                addPrim(ot + ((ctx->otz_8 >> 2) & 0x3FF), ctx->next_18);
                ctx->next_18 += sizeof(DR_TPAGE);
            }
        }
    }
}
void DrawFtgPolyFT3_8004BFA8(FtgObject* obj, OT_TYPE* ot, FtgDrawCtx* ctx)
{
    POLY_FT3* prim;
    FtgPolyFT3* poly;
    int i;
    if (obj->ft3_10.count == 0)
    {
        return;
    }
    prim = (POLY_FT3*)FTG_PRIM_SCRATCH;
    poly = obj->ft3_10.items;
    setPolyFT3(prim);
    for (i = 0; i < obj->ft3_10.count; i++, poly++)
    {
        FtgVert* normal = &poly->n;
        gte_ldv3c(poly->v);
        gte_rtpt();
        *(unsigned int*)&prim->u0 = *(unsigned int*)&poly->u0 + ctx->clutAdd_1C;
        gte_stsxy3_ft3(prim);
        gte_nclip();
        *(unsigned int*)&prim->u1 = *(unsigned int*)&poly->u1;
        *(unsigned short*)&prim->u2 = poly->v[2].uv;
        gte_stopz(&ctx->opz_10);
        if (ctx->opz_10 > 0)
        {
            gte_avsz3();
            gte_stotz(&ctx->otz_8);
            if (ctx->otz_8 - 1 < 0xFFFU)
            {
                if (ctx->flags_20 & 1)
                {
                    gte_ldv0(normal);
                    gte_ldrgb(&poly->c);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    gte_strgb(&prim->r0);
                }
                else
                {
                    gte_ldrgb(&poly->c);
                    gte_lddp(ctx->dq_C);
                    gte_dpcs();
                    gte_strgb(&prim->r0);
                }
                if (ctx->flags_20 & 0x10)
                {
                    setSemiTrans(prim, 1);
                    prim->tpage &= ~0x60;
                    prim->tpage |= ctx->flags_20 & 0x60;
                }
                *(POLY_FT3*)ctx->next_18 = *prim;
                addPrim(ot + ((ctx->otz_8 >> 2) & 0x3FF), ctx->next_18);
                ctx->next_18 += sizeof(POLY_FT3);
            }
        }
    }
}
void DrawFtgPolyFT4_8004C21C(FtgObject* obj, OT_TYPE* ot, FtgDrawCtx* ctx)
{
    POLY_FT4* prim;
    FtgPolyFT4* poly;
    int i;
    if (obj->ft4_30.count == 0)
    {
        return;
    }
    prim = (POLY_FT4*)FTG_PRIM_SCRATCH;
    poly = obj->ft4_30.items;
    setPolyFT4(prim);
    for (i = 0; i < obj->ft4_30.count; i++, poly++)
    {
        FtgVert* normal = &poly->n;
        gte_ldv3c(poly->v);
        gte_rtpt();
        *(unsigned int*)&prim->u0 = *(unsigned int*)&poly->u0 + ctx->clutAdd_1C;
        gte_nclip();
        gte_stopz(&ctx->opz_10);
        gte_stsxy3_ft4(prim);
        gte_ldv0(&poly->v[3]);
        gte_rtps();
        *(unsigned int*)&prim->u1 = *(unsigned int*)&poly->u1;
        gte_nclip();
        gte_stopz(&ctx->opz2_14);
        if (ctx->opz_10 > 0 || ctx->opz2_14 < 0)
        {
            gte_avsz4();
            gte_stotz(&ctx->otz_8);
            if (ctx->otz_8 - 1 < 0xFFFU)
            {
                gte_stsxy(&prim->x3);
                if (ctx->flags_20 & 1)
                {
                    gte_ldv0(normal);
                    gte_ldrgb(&poly->c);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    *(unsigned short*)&prim->u2 = poly->v[2].uv;
                    *(unsigned short*)&prim->u3 = poly->v[3].uv;
                    gte_strgb(&prim->r0);
                }
                else
                {
                    *(unsigned short*)&prim->u2 = poly->v[2].uv;
                    *(unsigned short*)&prim->u3 = poly->v[3].uv;
                    gte_ldrgb(&poly->c);
                    gte_lddp(ctx->dq_C);
                    gte_dpcs();
                    gte_strgb(&prim->r0);
                }
                if (ctx->flags_20 & 0x10)
                {
                    setSemiTrans(prim, 1);
                    prim->tpage &= ~0x60;
                    prim->tpage |= ctx->flags_20 & 0x60;
                }
                *(POLY_FT4*)ctx->next_18 = *prim;
                addPrim(ot + ((ctx->otz_8 >> 2) & 0x3FF), ctx->next_18);
                ctx->next_18 += sizeof(POLY_FT4);
            }
        }
    }
}
void ProjectFtgTexSprites_8004C4F0(FtgObject* obj, OT_TYPE* ot, FtgDrawCtx* ctxArg, int slot)
{
    FtgDrawCtx* ctx = ctxArg;
    FtgSpriteVtx* vtx;
    FtgSprite* sprite;
    int i;
    if (obj->texSpriteCount_48 == 0)
    {
        return;
    }
    vtx = ftgSpriteVtxNext_80098180;
    vtx->rgbc_C = 0x3C808080;
    gte_ldrgb(&vtx->rgbc_C);
    sprite = obj->texSprites_50;
    for (i = 0; i < (obj->texSpriteCount_48 + 2) / 3; i++, sprite += 3)
    {
        gte_ldv3(&sprite[0].p1, &sprite[1].p1, &sprite[2].p1);
        gte_rtpt();
        ftgSpriteTPageClut_8009AAD8.word = *(unsigned int*)&obj->tpage_4C + ctx->clutAdd_1C;
        gte_stsxy3(&vtx[0].sxy_0, &vtx[1].sxy_0, &vtx[2].sxy_0);
        gte_stsz3(&vtx[0].sz_4, &vtx[1].sz_4, &vtx[2].sz_4);
        if (ctx->flags_20 & 1)
        {
            gte_ldv3(&sprite[0].p0, &sprite[1].p0, &sprite[2].p0);
            gte_lddp(ctx->dq_C);
            gte_ncdt();
            vtx[0].uv_8 = sprite[0].p1.uv;
            vtx[1].uv_8 = sprite[1].p1.uv;
            vtx[2].uv_8 = sprite[2].p1.uv;
            gte_strgb3(&vtx[0].rgbc_C, &vtx[1].rgbc_C, &vtx[2].rgbc_C);
        }
        else
        {
            gte_ldv3(&sprite[0].p0, &sprite[1].p0, &sprite[2].p0);
            gte_ldrgb3(&sprite[0].c, &sprite[1].c, &sprite[2].c);
            gte_dpct();
            vtx[0].uv_8 = sprite[0].p1.uv;
            vtx[1].uv_8 = sprite[1].p1.uv;
            vtx[2].uv_8 = sprite[2].p1.uv;
            gte_strgb3(&vtx[0].rgbc_C, &vtx[1].rgbc_C, &vtx[2].rgbc_C);
        }
        ftgSpriteVtxSlots_800987D8[slot][i * 3] = &vtx[0];
        ftgSpriteVtxSlots_800987D8[slot][i * 3 + 1] = &vtx[1];
        ftgSpriteVtxSlots_800987D8[slot][i * 3 + 2] = &vtx[2];
        vtx += 3;
    }
    ftgSpriteVtxNext_80098180 = vtx;
}
static inline void FtgDrawSprites(FtgObject* obj, FtgDrawCtx* ctxArg, int slot)
{
    FtgDrawCtx* ctx = ctxArg;
    FtgSpriteVtx* vtx = ftgSpriteVtxNext_80098180;
    FtgSprite* sp = obj->sprites_44;
    int i;
    for (i = 0; i < obj->spriteCount_40; i++, sp++)
    {
        gte_ldv0(&sp->p1);
        gte_rtps();
        gte_stsxy(&vtx->sxy_0);
        gte_stszotz(&vtx->sz_4);
        if (ctx->flags_20 & 1)
        {
            gte_ldv0(&sp->p0);
            gte_ldrgb(&sp->c);
            gte_lddp(ctx->dq_C);
            gte_ncds();
            gte_strgb(&vtx->rgbc_C);
        }
        else
        {
            gte_ldrgb(&sp->c);
            gte_lddp(ctx->dq_C);
            gte_dpcs();
            gte_strgb(&vtx->rgbc_C);
        }
        ftgSpriteVtxSlots_800987D8[slot][i] = vtx;
        vtx++;
    }
    ftgSpriteVtxNext_80098180 = vtx;
}
void DrawFtgObject_8004C7BC(FtgObject* obj, OT_TYPE* ot, int flags, int slot)
{
    FtgDrawCtx* ctx = FTG_DRAW_CTX;
    int i;
    ctx->next_18 = (unsigned char*)primAllocPtr_800960A8[bDoubleBuffer_8008D428];
    setlen(&ctx->tpage_0, 1);
    ctx->tpage_0.code[0] = 0xE1000200;
    if (flags & 0x10)
    {
        ctx->tpage_0.code[0] |= flags & 0x60;
    }
    else
    {
        ctx->tpage_0.code[0] |= 0x20;
    }
    if (flags & 0x80)
    {
        ctx->dq_C = flags >> 16;
    }
    else
    {
        ctx->dq_C = 0;
    }
    if (unknownFlags_8008D678 & 0x400)
    {
        ctx->dq_C = 0x1000 - (((0x1000 - ctx->dq_C) * sceneBrightness_8008D40C) >> 12);
    }
    ctx->clutAdd_1C = (flags & 0xFF00) << 14;
    ctx->flags_20 = flags;
    if (obj->f3_0.count)
    {
        DrawFtgPolyF3_8004B320(obj, ot, ctx);
    }
    if (obj->f4_20.count)
    {
        DrawFtgPolyF4_8004B590(obj, ot, ctx);
    }
    if (obj->g3_8.count)
    {
        DrawFtgPolyG3_8004B844(obj, ot, ctx);
    }
    if (obj->g4_28.count)
    {
        DrawFtgPolyG4_8004BB9C(obj, ot, ctx);
    }
    if (obj->ft3_10.count)
    {
        DrawFtgPolyFT3_8004BFA8(obj, ot, ctx);
    }
    if (obj->ft4_30.count)
    {
        DrawFtgPolyFT4_8004C21C(obj, ot, ctx);
    }
    if (obj->gt3_18.count)
    {
        POLY_GT3* t = (POLY_GT3*)FTG_PRIM_SCRATCH;
        FtgPolyGT3* e = obj->gt3_18.items;
        *(unsigned int*)&t->r0 = 0x34808080;
        setlen(t, 9);
        t->code = 0x34;
        gte_ldrgb(&t->r0);
        for (i = 0; i < obj->gt3_18.count; i++, e++)
        {
            FtgVert* n = e->n;
            gte_ldv3c(e->v);
            gte_rtpt();
            *(unsigned int*)&t->u0 = *(unsigned int*)&e->u0 + ctx->clutAdd_1C;
            gte_stsxy3_gt3(t);
            gte_nclip();
            gte_stopz(&ctx->opz_10);
            if (ctx->opz_10 > 0)
            {
                gte_avsz3();
                gte_stotz(&ctx->otz_8);
                if (ctx->otz_8 - 1 < 0xFFFU)
                {
                    gte_lddp(ctx->dq_C);
                    if (ctx->flags_20 & 1)
                    {
                        gte_ldv3(n, &e->n[1], &e->n[2]);
                        gte_ncdt();
                        *(unsigned int*)&t->u1 = *(unsigned int*)&e->u1;
                        *(unsigned short*)&t->u2 = e->v[2].uv;
                        gte_strgb3(&t->r0, &t->r1, &t->r2);
                    }
                    else
                    {
                        *(unsigned int*)&t->u1 = *(unsigned int*)&e->u1;
                        *(unsigned short*)&t->u2 = e->v[2].uv;
                        gte_ldrgb(&e->c[0]);
                        gte_lddp(ctx->dq_C);
                        gte_dpcs();
                        gte_strgb(&t->r0);
                        gte_ldrgb(&e->c[1]);
                        gte_lddp(ctx->dq_C);
                        gte_dpcs();
                        gte_strgb(&t->r1);
                        gte_ldrgb(&e->c[2]);
                        gte_lddp(ctx->dq_C);
                        gte_dpcs();
                        gte_strgb(&t->r2);
                    }
                    if (ctx->flags_20 & 0x10)
                    {
                        setSemiTrans(t, 1);
                        t->tpage &= ~0x60;
                        t->tpage |= ctx->flags_20 & 0x60;
                    }
                    *(POLY_GT3*)ctx->next_18 = *t;
                    addPrim(ot + ((ctx->otz_8 >> 2) & 0x3FF), ctx->next_18);
                    ctx->next_18 += sizeof(POLY_GT3);
                }
            }
        }
    }
    if (obj->gt4_38.count)
    {
        POLY_GT4* t = (POLY_GT4*)FTG_PRIM_SCRATCH;
        FtgPolyGT4* e = obj->gt4_38.items;
        *(unsigned int*)&t->r0 = 0x3C808080;
        setlen(t, 12);
        t->code = 0x3C;
        gte_ldrgb(&t->r0);
        for (i = 0; i < obj->gt4_38.count; i++, e++)
        {
            FtgVert* n = e->n;
            gte_ldv3c(e->v);
            gte_rtpt();
            *(unsigned int*)&t->u0 = *(unsigned int*)&e->u0 + ctx->clutAdd_1C;
            gte_nclip();
            gte_stopz(&ctx->opz_10);
            gte_stsxy3_gt4(t);
            gte_ldv0(&e->v[3]);
            gte_rtps();
            *(unsigned int*)&t->u1 = *(unsigned int*)&e->u1;
            gte_nclip();
            gte_stopz(&ctx->opz2_14);
            if (ctx->opz_10 > 0 || ctx->opz2_14 < 0)
            {
                gte_stsxy(&t->x3);
                gte_avsz4();
                gte_stotz(&ctx->otz_8);
                if (ctx->otz_8 - 1 < 0xFFFU)
                {
                    gte_lddp(ctx->dq_C);
                    if (ctx->flags_20 & 1)
                    {
                        gte_ldv3(n, &e->n[1], &e->n[2]);
                        gte_ncdt();
                        *(unsigned short*)&t->u2 = e->v[2].uv;
                        *(unsigned short*)&t->u3 = e->v[3].uv;
                        gte_strgb3(&t->r0, &t->r1, &t->r2);
                        gte_ldv0(&e->n[3]);
                        gte_ncds();
                        gte_strgb(&t->r3);
                    }
                    else
                    {
                        gte_ldrgb(&e->c[0]);
                        gte_dpcs();
                        gte_strgb(&t->r0);
                        gte_ldrgb3(&e->c[1], &e->c[2], &e->c[3]);
                        gte_dpct();
                        *(unsigned short*)&t->u2 = e->v[2].uv;
                        *(unsigned short*)&t->u3 = e->v[3].uv;
                        gte_strgb3(&t->r1, &t->r2, &t->r3);
                    }
                    if (ctx->flags_20 & 0x10)
                    {
                        setSemiTrans(t, 1);
                        t->tpage &= ~0x60;
                        t->tpage |= ctx->flags_20 & 0x60;
                    }
                    *(POLY_GT4*)ctx->next_18 = *t;
                    addPrim(ot + ((ctx->otz_8 >> 2) & 0x3FF), ctx->next_18);
                    ctx->next_18 += sizeof(POLY_GT4);
                }
            }
        }
    }
    if (obj->spriteCount_40)
    {
        FtgDrawSprites(obj, ctx, slot);
    }
    if (obj->texSpriteCount_48)
    {
        ProjectFtgTexSprites_8004C4F0(obj, ot, ctx, slot);
    }
    primAllocPtr_800960A8[bDoubleBuffer_8008D428] = (char*)ctx->next_18;
}
extern unsigned char backColor_8008D460[3]; // back colour
extern MATRIX lightMatrix_80087114;            // light matrix
extern MATRIX colorMatrix_80087134;            // light colour matrix
extern SVECTOR cameraRot_8008D4C8;
void SetGteLightAndCamera_8004D0E8(void)
{
    MATRIX* m;
    gte_SetBackColor(backColor_8008D460[0], backColor_8008D460[1], backColor_8008D460[2]);
    gte_SetColorMatrix(&colorMatrix_80087134);
    gte_SetLightMatrix(&lightMatrix_80087114);
    RotMatrixZXY_8004668C(&cameraRot_8008D4C8, (MATRIX*)getScratchAddr(0));
    m = (MATRIX*)getScratchAddr(0);
    m->t[2] = 0;
    m->t[1] = 0;
    m->t[0] = 0;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);
}

void DrawFtgObjectAtSlot0_8004D1EC(struct FtgObject* obj, OT_TYPE* ot, void* pos, void* rot, void* light, int flags, void* scale)
{
    DrawFtgObjectAt_80044D0C(obj, ot, pos, rot, light, flags, scale, 0);
}
// the part of a skeleton GetBonePos_8004D224 reads
typedef struct
{
    char pad_0[0x14];
    unsigned short* offsets_14; // per bone (x, y, z) offset from its parent
} SkelBoneOffsets;

void GetBonePos_8004D224(unsigned short* out, SkelBoneOffsets* skel, int idx)
{
    if (idx == 0)
    {
        out[0] = 0;
        out[1] = 0;
        out[2] = 0;
        return;
    }
    out[0] = skel->offsets_14[idx * 3];
    out[1] = skel->offsets_14[idx * 3 + 1];
    out[2] = skel->offsets_14[idx * 3 + 2];
}
// the part of an animation GetAnimRoot* / GetAnimBoneRot_8004D354 read
typedef struct
{
    int pad_0;
    int boneCount_4;
    int pad_8;
    int pad_C;
    void* cues_10;     // as ModelAnim
    short* basePose_14;
    short* frames_18; // per frame: root motion, root rotation, then one rotation per bone (x, y, z)
} AnimFrames;
void GetAnimRootMotion_8004D288(int* out, AnimFrames* anim, int frame)
{
    int i = frame * (anim->boneCount_4 + 2);
    out[0] = anim->frames_18[i * 3];
    out[1] = anim->frames_18[i * 3 + 1];
    out[2] = anim->frames_18[i * 3 + 2];
}
void GetAnimRootRot_8004D2EC(short* out, AnimFrames* anim, int frame)
{
    int i = frame * (anim->boneCount_4 + 2) + 1;
    out[0] = anim->frames_18[i * 3];
    out[1] = anim->frames_18[i * 3 + 1];
    out[2] = anim->frames_18[i * 3 + 2];
}
void GetAnimBoneRot_8004D354(short* out, AnimFrames* anim, int bone, int frame)
{
    int i;
    int row;
    if (bone == 0)
    {
        out[0] = 0;
        out[1] = 0;
        out[2] = 0;
        return;
    }
    row = bone + 2;
    i = frame * (anim->boneCount_4 + 2) + row;
    out[0] = anim->frames_18[i * 3];
    out[1] = anim->frames_18[i * 3 + 1];
    out[2] = anim->frames_18[i * 3 + 2];
}
void RotMatrixXYZ_8004D3D8(SVECTOR* rot, MATRIX* m)
{
    int cy = sinTable_80084540[(rot->vy + 0x400) & 0xFFF];
    int cz = sinTable_80084540[(rot->vz + 0x400) & 0xFFF];
    int sy = sinTable_80084540[rot->vy & 0xFFF];
    int cx = sinTable_80084540[(rot->vx + 0x400) & 0xFFF];
    int sz = sinTable_80084540[rot->vz & 0xFFF];
    int sx = sinTable_80084540[rot->vx & 0xFFF];
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
void RotMatrixZYX_8004D5CC(SVECTOR* rot, MATRIX* m)
{
    int cz = sinTable_80084540[(rot->vz + 0x400) & 0xFFF];
    int cy = sinTable_80084540[(rot->vy + 0x400) & 0xFFF];
    int sy = sinTable_80084540[rot->vy & 0xFFF];
    int sz = sinTable_80084540[rot->vz & 0xFFF];
    int cx = sinTable_80084540[(rot->vx + 0x400) & 0xFFF];
    int sx = sinTable_80084540[rot->vx & 0xFFF];
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
void LerpSVector_8004D7A8(SVECTOR* a, SVECTOR* b, SVECTOR* out, int t)
{
    out->vx = a->vx + (b->vx - a->vx) * t / 4096;
    out->vy = a->vy + (b->vy - a->vy) * t / 4096;
    out->vz = a->vz + (b->vz - a->vz) * t / 4096;
}
void LerpAngles_8004D848(SVECTOR* a, SVECTOR* b, SVECTOR* out, int t)
{
    int diff;
    diff = (b->vx - a->vx) & 0xFFF;
    if (diff >= 0x800)
    {
        diff -= 0x1000;
    }
    out->vx = (a->vx + diff * t / 4096) & 0xFFF;
    diff = (b->vy - a->vy) & 0xFFF;
    if (diff >= 0x800)
    {
        diff -= 0x1000;
    }
    out->vy = (a->vy + diff * t / 4096) & 0xFFF;
    diff = (b->vz - a->vz) & 0xFFF;
    if (diff >= 0x800)
    {
        diff -= 0x1000;
    }
    out->vz = (a->vz + diff * t / 4096) & 0xFFF;
}
void ResetFtgSpriteVtx_8004D924(void)
{
    ftgSpriteVtxNext_80098180 = ftgSpriteVtxPool_80096628;
}
// RotMatrixZYX_8004D5CC's matrix with its rows 1 and 2 turned by roll (a rotation about X applied after it)
void RotMatrixZYXRollX_8004D938(short roll, SVECTOR* rot, MATRIX* m)
{
    int cz = sinTable_80084540[(rot->vz + 0x400) & 0xFFF];
    int cy = sinTable_80084540[(rot->vy + 0x400) & 0xFFF];
    int sy = sinTable_80084540[rot->vy & 0xFFF];
    int sz = sinTable_80084540[rot->vz & 0xFFF];
    int cx = sinTable_80084540[(rot->vx + 0x400) & 0xFFF];
    int sx = sinTable_80084540[rot->vx & 0xFFF];
    int a = (cz * sy) >> 12;
    int b = (sz * sy) >> 12;
    int m21 = (sx * cy) >> 12;
    int m22 = (cx * cy) >> 12;
    int m10 = (cy * sz) >> 12;
    int m11 = ((cz * cx) >> 12) + ((b * sx) >> 12);
    int m12 = -((cz * sx) >> 12) + ((b * cx) >> 12);
    int m00 = (cz * cy) >> 12;
    int m01 = -((sz * cx) >> 12) + ((a * sx) >> 12);
    int m02 = ((sz * sx) >> 12) + ((a * cx) >> 12);
    int cr = sinTable_80084540[(roll + 0x400) & 0xFFF];
    int sr = sinTable_80084540[roll & 0xFFF];
    int r10 = ((m10 * cr) >> 12) + ((sy * sr) >> 12);
    int r11 = ((m11 * cr) >> 12) - ((m21 * sr) >> 12);
    int r12 = ((m12 * cr) >> 12) - ((m22 * sr) >> 12);
    int r20 = ((m10 * sr) >> 12) - ((sy * cr) >> 12);
    int r21 = ((m11 * sr) >> 12) + ((m21 * cr) >> 12);
    int r22 = ((m12 * sr) >> 12) + ((m22 * cr) >> 12);
    m->m[0][0] = m00;
    m->m[0][1] = m01;
    m->m[0][2] = m02;
    m->m[1][0] = r10;
    m->m[1][1] = r11;
    m->m[1][2] = r12;
    m->m[2][0] = r20;
    m->m[2][1] = r21;
    m->m[2][2] = r22;
}
void PrintMatrix_8004DC54(MATRIX* m)
{
    printf("%d,%d,%d\r", m->m[0][0], m->m[0][1], m->m[0][2]);
    printf("%d,%d,%d\r", m->m[1][0], m->m[1][1], m->m[1][2]);
    printf("%d,%d,%d\r", m->m[2][0], m->m[2][1], m->m[2][2]);
}
void ProjectFtgSprites_8004DCC0(FtgObject* obj, OT_TYPE* ot, FtgDrawCtx* ctx, int slot)
{
    if (obj->spriteCount_40 == 0)
    {
        return;
    }
    FtgDrawSprites(obj, ctx, slot);
}

FtgSpriteVtx *ftgSpriteVtxNext_80098180 BSS = 0;
int unused_80098184 BSS = 0;
MATRIX boneMatrices_80098188[40] BSS = { 0 };
int unusedWord_80098688 BSS = 0;
int unused_8009868C BSS = 0;
SVECTOR boneOffsets_80098690[2] BSS = { 0 };
int unused_800986A0[78] BSS = { 0 };
FtgSpriteVtx *ftgSpriteVtxSlots_800987D8[40][56] BSS = { 0 };
FtgTPageClut ftgSpriteTPageClut_8009AAD8 BSS = { 0 };
int unused_8009AADC BSS = 0;
