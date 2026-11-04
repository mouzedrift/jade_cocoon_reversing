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
#include "tu_8004B0A8.h"
#include "tu_80043AF8.h"

#define ABS_8004B0A8(x) ((x) < 0 ? -(x) : (x))
// Matched
void BasisFromAxis_8004B0A8(VECTOR* v, MATRIX* m)
{
    VECTOR t;
    VECTOR u;
    VECTOR n0;
    VECTOR n1;
    VECTOR n2;
    int ax;
    int ay;
    int az;
    ScaleVectorToFit_8003B684((int*)v);
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
    ScaleVectorToFit_8003B684((int*)&t);
    VectorNormal(&t, &n1);
    m->m[0][1] = n1.vx;
    m->m[1][1] = n1.vy;
    m->m[2][1] = n1.vz;
    OuterProduct12(&n0, &n1, &u);
    ScaleVectorToFit_8003B684((int*)&u);
    VectorNormal(&u, &n2);
    m->m[0][2] = n2.vx;
    m->m[1][2] = n2.vy;
    m->m[2][2] = n2.vz;
}
// Matched
void DrawFtgPolyF3_8004B320(FtgObject* obj, unsigned long* ot, FtgDrawCtx* ctx)
{
    POLY_F3* t = (POLY_F3*)FTG_PRIM_SCRATCH;
    FtgPolyF3* e = obj->f3_0.items;
    int i;
    setPolyF3(t);
    for (i = 0; i < obj->f3_0.count; i++, e++)
    {
        FtgVert* n = &e->n;
        gte_ldv3c(e->v);
        gte_rtpt();
        gte_stsxy3_f3(t);
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
                    gte_ldv0(n);
                    gte_ldrgb(&e->c);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    gte_strgb(&t->r0);
                }
                else
                {
                    gte_ldrgb(&e->c);
                    gte_lddp(ctx->dq_C);
                    gte_dpcs();
                    gte_strgb(&t->r0);
                }
                if (ctx->flags_20 & 0x10)
                {
                    setSemiTrans(t, 1);
                }
                *(POLY_F3*)ctx->next_18 = *t;
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
// Matched
void DrawFtgPolyF4_8004B590(FtgObject* obj, unsigned long* ot, FtgDrawCtx* ctx)
{
    POLY_F4* t = (POLY_F4*)FTG_PRIM_SCRATCH;
    FtgPolyF4* e = obj->f4_20.items;
    int i;
    setPolyF4(t);
    for (i = 0; i < obj->f4_20.count; i++, e++)
    {
        FtgVert* n = &e->n;
        gte_ldv3c(e->v);
        gte_rtpt();
        gte_nclip();
        gte_stopz(&ctx->opz_10);
        gte_stsxy3_f4(t);
        gte_ldv0(&e->v[3]);
        gte_rtps();
        gte_nclip();
        gte_stopz(&ctx->opz2_14);
        if (ctx->opz_10 > 0 || ctx->opz2_14 < 0)
        {
            gte_avsz4();
            gte_stotz(&ctx->otz_8);
            if (ctx->otz_8 - 1 < 0xFFFU)
            {
                gte_stsxy(&t->x3);
                if (ctx->flags_20 & 1)
                {
                    gte_ldv0(n);
                    gte_ldrgb(&e->c);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    gte_strgb(&t->r0);
                }
                else
                {
                    gte_ldrgb(&e->c);
                    gte_lddp(ctx->dq_C);
                    gte_dpcs();
                    gte_strgb(&t->r0);
                }
                if (ctx->flags_20 & 0x10)
                {
                    setSemiTrans(t, 1);
                }
                *(POLY_F4*)ctx->next_18 = *t;
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
// Matched
void DrawFtgPolyG3_8004B844(FtgObject* obj, unsigned long* ot, FtgDrawCtx* ctx)
{
    POLY_G3* t = (POLY_G3*)FTG_PRIM_SCRATCH;
    FtgPolyG3* e = obj->g3_8.items;
    int i;
    setPolyG3(t);
    for (i = 0; i < obj->g3_8.count; i++, e++)
    {
        FtgVert* n = e->n;
        gte_ldv3c(e->v);
        gte_rtpt();
        gte_stsxy3_g3(t);
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
                    gte_ldv0(n);
                    gte_ldrgb(&e->c[0]);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    gte_strgb(&t->r0);
                    gte_ldv0(&e->n[1]);
                    gte_ldrgb(&e->c[1]);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    gte_strgb(&t->r1);
                    gte_ldv0(&e->n[2]);
                    gte_ldrgb(&e->c[2]);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    gte_strgb(&t->r2);
                }
                else
                {
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
                }
                *(POLY_G3*)ctx->next_18 = *t;
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
// Matched
void DrawFtgPolyG4_8004BB9C(FtgObject* obj, unsigned long* ot, FtgDrawCtx* ctx)
{
    POLY_G4* t = (POLY_G4*)FTG_PRIM_SCRATCH;
    FtgPolyG4* e = obj->g4_28.items;
    int i;
    setPolyG4(t);
    for (i = 0; i < obj->g4_28.count; i++, e++)
    {
        FtgVert* n = e->n;
        gte_ldv3c(e->v);
        gte_rtpt();
        gte_nclip();
        gte_stopz(&ctx->opz_10);
        gte_stsxy3_g4(t);
        gte_ldv0(&e->v[3]);
        gte_rtps();
        gte_nclip();
        gte_stopz(&ctx->opz2_14);
        if (ctx->opz_10 > 0 || ctx->opz2_14 < 0)
        {
            gte_avsz4();
            gte_stotz(&ctx->otz_8);
            if (ctx->otz_8 - 1 < 0xFFFU)
            {
                gte_stsxy(&t->x3);
                if (ctx->flags_20 & 1)
                {
                    gte_ldv0(n);
                    gte_ldrgb(&e->c[0]);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    gte_strgb(&t->r0);
                    gte_ldv0(&e->n[1]);
                    gte_ldrgb(&e->c[1]);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    gte_strgb(&t->r1);
                    gte_ldv0(&e->n[2]);
                    gte_ldrgb(&e->c[2]);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    gte_strgb(&t->r2);
                    gte_ldv0(&e->n[3]);
                    gte_ldrgb(&e->c[3]);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    gte_strgb(&t->r3);
                }
                else
                {
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
                    gte_ldrgb(&e->c[3]);
                    gte_lddp(ctx->dq_C);
                    gte_dpcs();
                    gte_strgb(&t->r3);
                }
                if (ctx->flags_20 & 0x10)
                {
                    setSemiTrans(t, 1);
                }
                *(POLY_G4*)ctx->next_18 = *t;
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
// Matched
void DrawFtgPolyFT3_8004BFA8(FtgObject* obj, unsigned long* ot, FtgDrawCtx* ctx)
{
    POLY_FT3* t;
    FtgPolyFT3* e;
    int i;
    if (obj->ft3_10.count == 0)
    {
        return;
    }
    t = (POLY_FT3*)FTG_PRIM_SCRATCH;
    e = obj->ft3_10.items;
    setPolyFT3(t);
    for (i = 0; i < obj->ft3_10.count; i++, e++)
    {
        FtgVert* n = &e->n;
        gte_ldv3c(e->v);
        gte_rtpt();
        *(unsigned long*)&t->u0 = *(unsigned long*)&e->u0 + ctx->clutAdd_1C;
        gte_stsxy3_ft3(t);
        gte_nclip();
        *(unsigned long*)&t->u1 = *(unsigned long*)&e->u1;
        *(unsigned short*)&t->u2 = e->v[2].uv;
        gte_stopz(&ctx->opz_10);
        if (ctx->opz_10 > 0)
        {
            gte_avsz3();
            gte_stotz(&ctx->otz_8);
            if (ctx->otz_8 - 1 < 0xFFFU)
            {
                if (ctx->flags_20 & 1)
                {
                    gte_ldv0(n);
                    gte_ldrgb(&e->c);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    gte_strgb(&t->r0);
                }
                else
                {
                    gte_ldrgb(&e->c);
                    gte_lddp(ctx->dq_C);
                    gte_dpcs();
                    gte_strgb(&t->r0);
                }
                if (ctx->flags_20 & 0x10)
                {
                    setSemiTrans(t, 1);
                    t->tpage &= ~0x60;
                    t->tpage |= ctx->flags_20 & 0x60;
                }
                *(POLY_FT3*)ctx->next_18 = *t;
                addPrim(ot + ((ctx->otz_8 >> 2) & 0x3FF), ctx->next_18);
                ctx->next_18 += sizeof(POLY_FT3);
            }
        }
    }
}
// Matched
void DrawFtgPolyFT4_8004C21C(FtgObject* obj, unsigned long* ot, FtgDrawCtx* ctx)
{
    POLY_FT4* t;
    FtgPolyFT4* e;
    int i;
    if (obj->ft4_30.count == 0)
    {
        return;
    }
    t = (POLY_FT4*)FTG_PRIM_SCRATCH;
    e = obj->ft4_30.items;
    setPolyFT4(t);
    for (i = 0; i < obj->ft4_30.count; i++, e++)
    {
        FtgVert* n = &e->n;
        gte_ldv3c(e->v);
        gte_rtpt();
        *(unsigned long*)&t->u0 = *(unsigned long*)&e->u0 + ctx->clutAdd_1C;
        gte_nclip();
        gte_stopz(&ctx->opz_10);
        gte_stsxy3_ft4(t);
        gte_ldv0(&e->v[3]);
        gte_rtps();
        *(unsigned long*)&t->u1 = *(unsigned long*)&e->u1;
        gte_nclip();
        gte_stopz(&ctx->opz2_14);
        if (ctx->opz_10 > 0 || ctx->opz2_14 < 0)
        {
            gte_avsz4();
            gte_stotz(&ctx->otz_8);
            if (ctx->otz_8 - 1 < 0xFFFU)
            {
                gte_stsxy(&t->x3);
                if (ctx->flags_20 & 1)
                {
                    gte_ldv0(n);
                    gte_ldrgb(&e->c);
                    gte_lddp(ctx->dq_C);
                    gte_ncds();
                    *(unsigned short*)&t->u2 = e->v[2].uv;
                    *(unsigned short*)&t->u3 = e->v[3].uv;
                    gte_strgb(&t->r0);
                }
                else
                {
                    *(unsigned short*)&t->u2 = e->v[2].uv;
                    *(unsigned short*)&t->u3 = e->v[3].uv;
                    gte_ldrgb(&e->c);
                    gte_lddp(ctx->dq_C);
                    gte_dpcs();
                    gte_strgb(&t->r0);
                }
                if (ctx->flags_20 & 0x10)
                {
                    setSemiTrans(t, 1);
                    t->tpage &= ~0x60;
                    t->tpage |= ctx->flags_20 & 0x60;
                }
                *(POLY_FT4*)ctx->next_18 = *t;
                addPrim(ot + ((ctx->otz_8 >> 2) & 0x3FF), ctx->next_18);
                ctx->next_18 += sizeof(POLY_FT4);
            }
        }
    }
}
// Matched
void ProjectFtgTexSprites_8004C4F0(FtgObject* obj, unsigned long* ot, FtgDrawCtx* ctxArg, int slot)
{
    FtgDrawCtx* ctx = ctxArg;
    FtgSpriteVtx* o;
    FtgSprite* s;
    int i;
    if (obj->texSpriteCount_48 == 0)
    {
        return;
    }
    o = ftgSpriteVtxNext_80098180;
    o->rgbc_C = 0x3C808080;
    gte_ldrgb(&o->rgbc_C);
    s = obj->texSprites_50;
    for (i = 0; i < (obj->texSpriteCount_48 + 2) / 3; i++, s += 3)
    {
        gte_ldv3(&s[0].p1, &s[1].p1, &s[2].p1);
        gte_rtpt();
        ftgSpriteTPageClut_8009AAD8.word = *(unsigned long*)&obj->tpage_4C + ctx->clutAdd_1C;
        gte_stsxy3(&o[0].sxy_0, &o[1].sxy_0, &o[2].sxy_0);
        gte_stsz3(&o[0].sz_4, &o[1].sz_4, &o[2].sz_4);
        if (ctx->flags_20 & 1)
        {
            gte_ldv3(&s[0].p0, &s[1].p0, &s[2].p0);
            gte_lddp(ctx->dq_C);
            gte_ncdt();
            o[0].uv_8 = s[0].p1.uv;
            o[1].uv_8 = s[1].p1.uv;
            o[2].uv_8 = s[2].p1.uv;
            gte_strgb3(&o[0].rgbc_C, &o[1].rgbc_C, &o[2].rgbc_C);
        }
        else
        {
            gte_ldv3(&s[0].p0, &s[1].p0, &s[2].p0);
            gte_ldrgb3(&s[0].c, &s[1].c, &s[2].c);
            gte_dpct();
            o[0].uv_8 = s[0].p1.uv;
            o[1].uv_8 = s[1].p1.uv;
            o[2].uv_8 = s[2].p1.uv;
            gte_strgb3(&o[0].rgbc_C, &o[1].rgbc_C, &o[2].rgbc_C);
        }
        ftgSpriteVtxSlots_800987D8[slot][i * 3] = &o[0];
        ftgSpriteVtxSlots_800987D8[slot][i * 3 + 1] = &o[1];
        ftgSpriteVtxSlots_800987D8[slot][i * 3 + 2] = &o[2];
        o += 3;
    }
    ftgSpriteVtxNext_80098180 = o;
}
static inline void FtgDrawSprites(FtgObject* obj, FtgDrawCtx* ctxArg, int slot)
{
    FtgDrawCtx* ctx = ctxArg;
    FtgSpriteVtx* o = ftgSpriteVtxNext_80098180;
    FtgSprite* sp = obj->sprites_44;
    int i;
    for (i = 0; i < obj->spriteCount_40; i++, sp++)
    {
        gte_ldv0(&sp->p1);
        gte_rtps();
        gte_stsxy(&o->sxy_0);
        gte_stszotz(&o->sz_4);
        if (ctx->flags_20 & 1)
        {
            gte_ldv0(&sp->p0);
            gte_ldrgb(&sp->c);
            gte_lddp(ctx->dq_C);
            gte_ncds();
            gte_strgb(&o->rgbc_C);
        }
        else
        {
            gte_ldrgb(&sp->c);
            gte_lddp(ctx->dq_C);
            gte_dpcs();
            gte_strgb(&o->rgbc_C);
        }
        ftgSpriteVtxSlots_800987D8[slot][i] = o;
        o++;
    }
    ftgSpriteVtxNext_80098180 = o;
}
// Matched
void DrawFtgObject_8004C7BC(FtgObject* obj, unsigned long* ot, int flags, int slot)
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
        ctx->dq_C = 0x1000 - (((0x1000 - ctx->dq_C) * dword_8008D40C) >> 12);
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
        *(unsigned long*)&t->r0 = 0x34808080;
        setlen(t, 9);
        t->code = 0x34;
        gte_ldrgb(&t->r0);
        for (i = 0; i < obj->gt3_18.count; i++, e++)
        {
            FtgVert* n = e->n;
            gte_ldv3c(e->v);
            gte_rtpt();
            *(unsigned long*)&t->u0 = *(unsigned long*)&e->u0 + ctx->clutAdd_1C;
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
                        *(unsigned long*)&t->u1 = *(unsigned long*)&e->u1;
                        *(unsigned short*)&t->u2 = e->v[2].uv;
                        gte_strgb3(&t->r0, &t->r1, &t->r2);
                    }
                    else
                    {
                        *(unsigned long*)&t->u1 = *(unsigned long*)&e->u1;
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
        *(unsigned long*)&t->r0 = 0x3C808080;
        setlen(t, 12);
        t->code = 0x3C;
        gte_ldrgb(&t->r0);
        for (i = 0; i < obj->gt4_38.count; i++, e++)
        {
            FtgVert* n = e->n;
            gte_ldv3c(e->v);
            gte_rtpt();
            *(unsigned long*)&t->u0 = *(unsigned long*)&e->u0 + ctx->clutAdd_1C;
            gte_nclip();
            gte_stopz(&ctx->opz_10);
            gte_stsxy3_gt4(t);
            gte_ldv0(&e->v[3]);
            gte_rtps();
            *(unsigned long*)&t->u1 = *(unsigned long*)&e->u1;
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
    primAllocPtr_800960A8[bDoubleBuffer_8008D428] = (int)ctx->next_18;
}
extern unsigned char byte_8008D460[3]; // back colour
extern MATRIX dword_80087114;            // light matrix
extern MATRIX dword_80087134;            // light colour matrix
extern SVECTOR cameraRot_8008D4C8;
// Matched
void SetGteLightAndCamera_8004D0E8(void)
{
    MATRIX* m;
    gte_SetBackColor(byte_8008D460[0], byte_8008D460[1], byte_8008D460[2]);
    gte_SetColorMatrix(&dword_80087134);
    gte_SetLightMatrix(&dword_80087114);
    RotMatrixZXY_8004668C(&cameraRot_8008D4C8, (MATRIX*)getScratchAddr(0));
    m = (MATRIX*)getScratchAddr(0);
    m->t[2] = 0;
    m->t[1] = 0;
    m->t[0] = 0;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);
}

// Matched
void DrawFtgObjectAtSlot0_8004D1EC(struct FtgObject* obj, unsigned long* ot, void* pos, void* rot, void* light, int flags, void* scale)
{
    DrawFtgObjectAt_80044D0C(obj, ot, pos, rot, light, flags, scale, 0);
}
typedef struct
{
    char pad_0[0x14];
    unsigned short* field_14;
} struct_tbl14;

// Matched
void GetBonePos_8004D224(unsigned short* out, struct_tbl14* s, int idx)
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
void GetAnimRootMotion_8004D288(int* out, struct_tbl18* s, int k)
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
void GetAnimBoneRot_8004D354(short* out, struct_tbl18* s, int j, int k)
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

FtgSpriteVtx *ftgSpriteVtxNext_80098180 BSS = 0;
int dword_80098184 BSS = 0;
MATRIX dword_80098188[40] BSS = { 0 };
int dword_80098688 BSS = 0;
int dword_8009868C BSS = 0;
SVECTOR boneOffsets_80098690[2] BSS = { 0 };
int dword_800986A0[78] BSS = { 0 };
FtgSpriteVtx *ftgSpriteVtxSlots_800987D8[40][56] BSS = { 0 };
FtgTPageClut ftgSpriteTPageClut_8009AAD8 BSS = { 0 };
int dword_8009AADC BSS = 0;
