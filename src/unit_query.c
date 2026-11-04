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
#include "unit.h"
#include "tiy.h"
#include "minion_menu.h"




extern UnitSkill* GetUnitSkills_80031B30(int a0);

// Matched
int sub_80031A94(int* p)
{
    int r = 2;
    UnitSkill* base;
    if (p[2] & 0xF)
    {
        r = 4;
    }
    base = GetUnitSkills_80031B30(LowestSetBit_80014358(p[2]) & 0xFF);
    base += p[1];
    if (base->id_1 == 0xC)
    {
        r |= 1;
    }
    return r;
}
// Matched
int sub_80031B0C(UnitSkill* base, int idx)
{
    int r = 4;
    base += idx;
    if (base->id_1 == 0xC)
    {
        r = 5;
    }
    return r;
}
extern UnitSkill* sub_800A11A0(int a0);
extern UnitSkill* sub_800A2BA0(int a0);



#if 0
// Not matched (13 words): a0 and r swap saved registers ($s1/$s2), same problem as GetUnitStatus_80014390 / GetUnitStats_8001449C. Tried: two-arg calls (t, t & 0xFF), int/unsigned t, t used in all three branches; permuter 1500: nothing
UnitSkill* GetUnitSkills_80031B30(int unit)
{
    UnitSkill* r = 0;
    unsigned int v = unit & 0xFF;
    unsigned int t;
    if (v >= 8)
    {
        t = unit - 8;
        r = sub_800A11A0(t & 0xFF);
    }
    else if (v >= 4)
    {
        int flags = sub_800A248C();
        int bit = 1 << v;
        if (flags & bit)
        {
            t = unit - 4;
            r = sub_800A2BA0(t & 0xFF);
        }
    }
    else if (v != 0)
    {
        t = unit - 1;
        r = GetMinionSkills_800107F8(3, t & 0xFF)->slot;
    }
    return r;
}
#endif
INCLUDE_ASM(GetUnitSkills_80031B30);
// Matched
int MenuIndexToSkillSlot_80031BDC(int a0)
{
    return a0;
}
// Matched
int AddScaledPolyFT4_80031BE4(POLY_FT4* p, unsigned long* ot, short x, short y, int scaleX, int scaleY, short* offset, int anchorFlags)
{
    int d;
    int w;
    int h;
    int x0;
    int y0;
    short lo;
    short hi;
    unsigned short flags;

    flags = anchorFlags;
    if (scaleX < 0)
    {
        scaleX = -scaleX;
        flags = anchorFlags ^ 0x100;
    }
    if (scaleY < 0)
    {
        scaleY = -scaleY;
        flags ^= 0x200;
    }
    w = (p->u3 - p->u0 >= 0 ? p->u3 - p->u0 : p->u0 - p->u3) * scaleX / 256;
    h = (p->v3 - p->v0 >= 0 ? p->v3 - p->v0 : p->v0 - p->v3) * scaleY / 256;
    if (w > 0x200)
    {
        w = 0x200;
    }
    if (h > 0x200)
    {
        h = 0x200;
    }
    switch (flags & 3)
    {
    case 1:
        x0 = x;
        break;
    case 2:
        x0 = x - w;
        break;
    case 0:
        x0 = x - w / 2;
        break;
    default:
        x0 = x - w / 2;
        break;
    }
    switch (flags & 0x30)
    {
    case 0x10:
        y0 = y;
        break;
    case 0x20:
        y0 = y - h;
        break;
    case 0:
        y0 = y - h / 2;
        break;
    default:
        y0 = y - h / 2;
        break;
    }
    if (offset)
    {
        x0 += offset[0] * scaleX / 256;
        y0 += offset[1] * scaleY / 256;
    }
    if ((flags & 0x300) == 0x300)
    {
        p->x1 = x0;
        p->y2 = y0;
        p->x0 = x0 + w;
        p->y3 = y0;
        p->x3 = x0;
        p->y0 = y0 + h;
        p->x2 = x0 + w;
        p->y1 = y0 + h;
    }
    else if (flags & 0x100)
    {
        p->x1 = x0;
        p->y0 = y0;
        p->x0 = x0 + w;
        p->y1 = y0;
        p->x3 = x0;
        p->y2 = y0 + h;
        p->x2 = x0 + w;
        p->y3 = y0 + h;
    }
    else if (flags & 0x200)
    {
        p->x0 = x0;
        p->y2 = y0;
        p->x1 = x0 + w;
        p->y3 = y0;
        p->x2 = x0;
        p->y0 = y0 + h;
        p->x3 = x0 + w;
        p->y1 = y0 + h;
    }
    else
    {
        p->x0 = x0;
        p->y0 = y0;
        p->x1 = x0 + w;
        p->y1 = y0;
        p->x2 = x0;
        p->y2 = y0 + h;
        p->x3 = x0 + w;
        p->y3 = y0 + h;
    }
    if (p->x0 > p->x1)
    {
        hi = p->x0;
        lo = p->x1;
    }
    else
    {
        lo = p->x0;
        hi = p->x1;
    }
    if (hi < p->x2)
    {
        hi = p->x2;
    }
    else if (p->x2 < lo)
    {
        lo = p->x2;
    }
    if (hi < p->x3)
    {
        hi = p->x3;
    }
    else if (p->x3 < lo)
    {
        lo = p->x3;
    }
    if (lo > 0x140 || hi < 0)
    {
        return 0;
    }
    if (p->y0 > p->y1)
    {
        hi = p->y0;
        lo = p->y1;
    }
    else
    {
        lo = p->y0;
        hi = p->y1;
    }
    if (hi < p->y2)
    {
        hi = p->y2;
    }
    else if (p->y2 < lo)
    {
        lo = p->y2;
    }
    if (hi < p->y3)
    {
        hi = p->y3;
    }
    else if (p->y3 < lo)
    {
        lo = p->y3;
    }
    if (lo > 0xF0 || hi < 0)
    {
        return 0;
    }
    AddPrimCopy_80040298(ot, p, 10);
    return 1;
}
#define ROT_X(x, y, a) ((x) * sinTable_80084540[((a) + 0x400) & 0xFFF] / 4096 - (y) * sinTable_80084540[(a) & 0xFFF] / 4096)
#define ROT_Y(x, y, a) ((x) * sinTable_80084540[(a) & 0xFFF] / 4096 + (y) * sinTable_80084540[((a) + 0x400) & 0xFFF] / 4096)
// Matched
void DrawRotatedPublicSprite_80031FF4(int idx, unsigned long* ot, unsigned short* pos, int angle)
{
    POLY_FT4 poly;
    short x;
    short y;
    int rx;
    int ry;

    setPolyFT4(&poly);
    poly.r0 = publicTiyPolyFT4s_8008D430[idx].r0;
    poly.g0 = publicTiyPolyFT4s_8008D430[idx].g0;
    poly.b0 = publicTiyPolyFT4s_8008D430[idx].b0;
    poly.code = publicTiyPolyFT4s_8008D430[idx].code;
    poly.clut = publicTiyPolyFT4s_8008D430[idx].clut;
    poly.tpage = publicTiyPolyFT4s_8008D430[idx].tpage;
    poly.u0 = publicTiyPolyFT4s_8008D430[idx].u0;
    poly.v0 = publicTiyPolyFT4s_8008D430[idx].v0;
    poly.u1 = publicTiyPolyFT4s_8008D430[idx].u1;
    poly.v1 = publicTiyPolyFT4s_8008D430[idx].v1;
    poly.u2 = publicTiyPolyFT4s_8008D430[idx].u2;
    poly.v2 = publicTiyPolyFT4s_8008D430[idx].v2;
    poly.u3 = publicTiyPolyFT4s_8008D430[idx].u3;
    poly.v3 = publicTiyPolyFT4s_8008D430[idx].v3;
    poly.x0 = 1 - (short)publicTiySprts_8008D434[idx].w / 2;
    poly.y0 = 1 - (short)publicTiySprts_8008D434[idx].h / 2;
    poly.x1 = (short)publicTiySprts_8008D434[idx].w / 2;
    poly.y1 = 1 - (short)publicTiySprts_8008D434[idx].h / 2;
    poly.x2 = 1 - (short)publicTiySprts_8008D434[idx].w / 2;
    poly.y2 = (short)publicTiySprts_8008D434[idx].h / 2;
    poly.x3 = (short)publicTiySprts_8008D434[idx].w / 2;
    poly.y3 = (short)publicTiySprts_8008D434[idx].h / 2;
    x = poly.x0;
    y = poly.y0;
    rx = ROT_X(x, y, angle);
    ry = ROT_Y(x, y, angle);
    poly.x0 = pos[0] + rx;
    poly.y0 = pos[1] + ry;
    x = poly.x1;
    y = poly.y1;
    rx = ROT_X(x, y, angle);
    ry = ROT_Y(x, y, angle);
    poly.x1 = pos[0] + rx;
    poly.y1 = pos[1] + ry;
    x = poly.x2;
    y = poly.y2;
    rx = ROT_X(x, y, angle);
    ry = ROT_Y(x, y, angle);
    poly.x2 = pos[0] + rx;
    poly.y2 = pos[1] + ry;
    rx = ROT_X(poly.x3, poly.y3, angle);
    ry = ROT_Y(poly.x3, poly.y3, angle);
    poly.x3 = pos[0] + rx;
    poly.y3 = pos[1] + ry;
    AddPrimCopy_80040298(ot, &poly, 10);
}
// Matched
void GetPublicTiySprt_80032470(int idx, SPRT* pOut20, DR_TPAGE* pOut8)
{
    *pOut20 = publicTiySprts_8008D434[idx];
    *pOut8 = publicTiyTPages_8008D440[idx];
}
// Matched
void AddRotatedPolyFT4_800324D8(POLY_FT4* p, int cx, int cy, int w, int h, int angle, void* ot)
{
    int a = -angle;
    short* c = &sinTable_80084540[(a + 0x400) & 0xFFF];
    short* s = &sinTable_80084540[(a + 0x800) & 0xFFF];
    p->x0 = cx + (w + (*c * -w + *s * -h) / 4096) / 2;
    p->y0 = cy + (h + (-*s * -w + *c * -h) / 4096) / 2;
    p->x1 = cx + (w + (*c * w + *s * -h) / 4096) / 2;
    p->y1 = cy + (h + (-*s * w + *c * -h) / 4096) / 2;
    p->x2 = cx + (w + (*c * -w + *s * h) / 4096) / 2;
    p->y2 = cy + (h + (-*s * -w + *c * h) / 4096) / 2;
    p->x3 = cx + (w + (*c * w + *s * h) / 4096) / 2;
    p->y3 = cy + (h + (-*s * w + *c * h) / 4096) / 2;
    AddPrimCopy_80040298(ot, p, 10);
}
// Matched
void AddRotatedPolyFT4Uv_800327A8(POLY_FT4* p, int cx, int cy, int w, int h, int du, int dv, int angle, void* ot)
{
    short* s = &sinTable_80084540[angle & 0xFFF];
    short* c = &sinTable_80084540[(angle + 0x400) & 0xFFF];

    p->u1 = p->u0 + du;
    p->v1 = p->v0;
    p->u2 = p->u0;
    p->v2 = p->v0 + dv;
    p->u3 = p->u0 + du;
    p->v3 = p->v0 + dv;
    p->x0 = cx + (w / 2 + (*c * (-w / 2) + *s * (-h / 2)) / 4096);
    p->y0 = cy + (h / 2 + (-*s * (-w / 2) + *c * (-h / 2)) / 4096);
    p->x1 = cx + (w / 2 + (*c * (w / 2) + *s * (-h / 2)) / 4096);
    p->y1 = cy + (h / 2 + (-*s * (w / 2) + *c * (-h / 2)) / 4096);
    p->x2 = cx + (w / 2 + (*c * (-w / 2) + *s * (h / 2)) / 4096);
    p->y2 = cy + (h / 2 + (-*s * (-w / 2) + *c * (h / 2)) / 4096);
    p->x3 = cx + (w / 2 + (*c * (w / 2) + *s * (h / 2)) / 4096);
    p->y3 = cy + (h / 2 + (-*s * (w / 2) + *c * (h / 2)) / 4096);
    AddPrimCopy_80040298(ot, p, 10);
}
// Matched
void SetRotatedPolyFT4_80032A88(POLY_FT4* p, int cx, int cy, int w, int h, int angle)
{
    int a = -angle;
    short* c = &sinTable_80084540[(a + 0x400) & 0xFFF];
    short* s = &sinTable_80084540[(a + 0x800) & 0xFFF];
    p->x0 = cx + (w + (*c * -w + *s * -h) / 4096) / 2;
    p->y0 = cy + (h + (-*s * -w + *c * -h) / 4096) / 2;
    p->x1 = cx + (w + (*c * w + *s * -h) / 4096) / 2;
    p->y1 = cy + (h + (-*s * w + *c * -h) / 4096) / 2;
    p->x2 = cx + (w + (*c * -w + *s * h) / 4096) / 2;
    p->y2 = cy + (h + (-*s * -w + *c * h) / 4096) / 2;
    p->x3 = cx + (w + (*c * w + *s * h) / 4096) / 2;
    p->y3 = cy + (h + (-*s * w + *c * h) / 4096) / 2;
}
// Matched
void AddPolyFT4FlipXY_80032D34(unsigned short* a, void* b)
{
    int dx = (short)a[8] - (short)a[4];
    int dy = (short)a[0xD] - (short)a[5];
    short* r = AddPrimCopy_80040298(b, a, 10);
    r[4] = a[4] + dx;
    r[5] = a[5] + dy;
    r[8] = a[4];
    r[9] = a[5] + dy;
    r[0xC] = a[4] + dx;
    r[0xD] = a[5];
    r[0x10] = a[4];
    r[0x11] = a[5];
}
// Matched
void AddPolyFT4FlipX_80032DFC(short* p, void* a1)
{
    int d = p[8] - p[4];
    short* q = AddPrimCopy_80040298(a1, p, 10);
    q[4] = p[4] + d;
    q[8] = p[4];
    q[12] = p[4] + d;
    q[16] = p[4];
}
// Matched
void AddPolyFT4FlipY_80032E78(unsigned short* p, void* a1)
{
    int d = ((short*)p)[13] - ((short*)p)[5];
    unsigned short* q = AddPrimCopy_80040298(a1, p, 10);
    q[5] = p[5] + d;
    q[9] = p[5] + d;
    q[13] = p[5];
    q[17] = p[5];
}
// Matched
void AddPolyFT4Rot90Ccw_80032EF4(unsigned short* p, void* a1)
{
    int a = ((short*)p)[4];
    int b = ((short*)p)[5];
    unsigned short* q = AddPrimCopy_80040298(a1, p, 10);
    unsigned short t;
    q[4] = p[12];
    q[5] = p[13];
    q[12] = p[16];
    q[13] = p[17];
    q[16] = p[8];
    t = p[9];
    q[8] = a;
    q[9] = b;
    q[17] = t;
}
// Matched
void AddPolyFT4Rot90Cw_80032F88(unsigned short* p, void* a1)
{
    int a = ((short*)p)[4];
    int b = ((short*)p)[5];
    unsigned short* q = AddPrimCopy_80040298(a1, p, 10);
    unsigned short t;
    q[4] = p[8];
    q[5] = p[9];
    q[8] = p[16];
    q[9] = p[17];
    q[16] = p[12];
    t = p[13];
    q[12] = a;
    q[13] = b;
    q[17] = t;
}
// Matched
void AddPolyFT4Copy_8003301C(void* a, void* b)
{
    AddPrimCopy_80040298(b, a, 10);
}
// Matched
void SetDrTPageAbr_80033048(unsigned short* p, int v)
{
    p[2] = (p[2] & 0xFF9F) | ((v & 3) << 5);
}
// Matched
void SetPolyFT4Abr_80033064(unsigned short* p, int v)
{
    p[0xB] = (p[0xB] & 0xFF9F) | ((v & 3) << 5);
}
// Matched
void DrawPublicTiySprt_80033080(unsigned short* a, int i, int j)
{
    publicTiySprts_8008D434[i].x0 = a[0];
    publicTiySprts_8008D434[i].y0 = a[1];
    AddPrimCopy_80040298(pOT_8008D454 + j, &publicTiySprts_8008D434[i], 5);
    AddPrimCopy_80040298(pOT_8008D454 + j, &publicTiyTPages_8008D440[i], 2);
}
// Matched
void DrawPublicTiySprtColored_80033114(unsigned short* a, int idx, void* c, unsigned char* col)
{
    publicTiySprts_8008D434[idx].r0 = col[0];
    publicTiySprts_8008D434[idx].g0 = col[1];
    publicTiySprts_8008D434[idx].b0 = col[2];
    publicTiySprts_8008D434[idx].x0 = a[0];
    publicTiySprts_8008D434[idx].y0 = a[1];
    AddPrimCopy_80040298(c, &publicTiySprts_8008D434[idx], 5);
    AddPrimCopy_80040298(c, &publicTiyTPages_8008D440[idx], 2);
}
// Matched
void AddSprtWithTPage_800331C4(unsigned short* a, SPRT* o, void* b, void* c, unsigned char* col)
{
    if (col)
    {
        o->code &= 0xFE;
        o->r0 = col[0];
        o->g0 = col[1];
        o->b0 = col[2];
    }
    else
    {
        o->code |= 1;
    }
    o->x0 = a[0];
    o->y0 = a[1];
    AddPrimCopy_80040298(c, o, 5);
    AddPrimCopy_80040298(c, b, 2);
}
extern DRAWENV drawEnv_8008D698[2];
// Matched
void AddDrawAreaPrim_8003326C(unsigned short* a, void* b)
{
    DR_AREA area;
    RECT rect;
    DRAWENV* e = drawEnv_8008D698;
    unsigned short* c = (unsigned short*)&e[bDoubleBuffer_8008D428].clip;
    rect.x = a[0] + c[0];
    rect.y = a[1] + c[1];
    rect.w = a[2];
    rect.h = a[3];
    SetDrawArea(&area, &rect);
    AddPrimCopy_80040298(b, &area, 3);
}
// Matched
void AddClipDrawAreaPrim_80033308(void* p)
{
    DR_AREA area;
    RECT rect;
    DRAWENV* e = drawEnv_8008D698;
    unsigned short* c = (unsigned short*)&e[bDoubleBuffer_8008D428].clip;
    rect.x = c[0];
    rect.y = c[1];
    rect.w = c[2];
    rect.h = c[3];
    SetDrawArea(&area, &rect);
    AddPrimCopy_80040298(p, &area, 3);
}
// Matched
void PulseColor_80033394(unsigned char* out, unsigned char* c0, unsigned char* c1, unsigned int t, int period, int half)
{
    int ph;
    int den;
    int r, g, b;
    if (period <= 0)
    {
        period = 40;
    }
    if (half <= 0)
    {
        half = 20;
    }
    ph = t % period;
    if (ph < half)
    {
        den = half;
    }
    else
    {
        ph = period - ph;
        den = period - half;
    }
    r = c0[0] + (c1[0] - c0[0]) * ph / den;
    g = c0[1] + (c1[1] - c0[1]) * ph / den;
    b = c0[2] + (c1[2] - c0[2]) * ph / den;
    if (r > 255)
    {
        r = 255;
    }
    if (g > 255)
    {
        g = 255;
    }
    if (b > 255)
    {
        b = 255;
    }
    if (r < 0)
    {
        r = 0;
    }
    if (g < 0)
    {
        g = 0;
    }
    if (b < 0)
    {
        b = 0;
    }
    out[0] = r;
    out[1] = g;
    out[2] = b;
}
// Matched
unsigned char GetByteAt_800334BC(unsigned char* arr, int idx)
{
    return arr[idx];
}
// Matched
short GetMaxHp_800334CC(UnitStatus* p)
{
    return p->maxHp_A;
}
// Matched
short GetHp_800334D8(UnitStatus* p)
{
    return p->hp_8;
}
// Matched
short GetMaxMp_800334E4(UnitStatus* p)
{
    return p->maxMp_E;
}
// Matched
short GetMp_800334F0(UnitStatus* p)
{
    return p->mp_C;
}
// Matched
int GetExp_800334FC(int* p)
{
    return p[1];
}
// Matched
short GetElementMask_80033508(UnitStatus* p)
{
    return p->elementMask_42;
}
// Matched
short GetLevel_80033514(UnitStatus* p)
{
    return p->level_44;
}
// Matched
unsigned char* GetStats_80033520(UnitStatus* p)
{
    return p->stats_2C;
}
// Matched
unsigned char GetStat_80033528(UnitStatus* p, int idx)
{
    return GetByteAt_800334BC(p->stats_2C, idx);
}
// Matched
int HasStatusFlag_80033548(UnitStatus* p, int mask)
{
    return (p->status_0 & mask) != 0;
}
// Matched
unsigned char GetModifier_8003355C(UnitStatus* p, int idx)
{
    return p->field_20[idx];
}
// Matched
int GetEquipmentId_8003356C(UnitStatus* p, unsigned int idx)
{
    int r = 0xFF;
    switch (idx)
    {
    case 0:
        r = p->field_1C[0];
        break;
    case 1:
        r = p->field_1C[1];
        break;
    case 2:
        r = p->field_1C[2];
        break;
    case 3:
        r = p->field_1C[3];
        break;

    }
    return r;
}
extern void ApplyEquipmentModifiers_80033754(unsigned char* a, UnitStatus* b);
// Matched
void CalcEffectiveStatus_800335D0(UnitStatus* src, UnitStatus* dst)
{
    int level;
    MemCopy_800403E8(dst, src, sizeof(UnitStatus));
    level = CalcEquippedStats_80033624(dst->stats_2C, dst);
    if (level)
    {
        dst->level_44 = level;
    }
    ApplyEquipmentModifiers_80033754(dst->field_20, dst);
}
// Matched
int CalcEquippedStats_80033624(unsigned char* arg0, UnitStatus* arg1)
{
    unsigned char* stats = arg1->stats_2C;
    unsigned char* ids = arg1->field_1C;
    int* tbl[4];
    int i;
    int j;
    int v;
    int max;
    tbl[0] = GetWeaponStatBonus_8001CEF4(ids[0]);
    tbl[1] = GetArmorStatBonus_8001CFB0(ids[1]);
    tbl[2] = GetAccessoryStatBonus_8001D078(ids[2]);
    tbl[3] = 0;
    for (i = 0; i < 6; i++)
    {
        v = stats[i];
        for (j = 0; j < 4; j++)
        {
            if (tbl[j])
            {
                v += ((signed char*)tbl[j])[i];
            }
        }
        arg0[i] = v < 0 ? 0 : (v < 100 ? v : 99);
    }
    max = 0;
    for (j = 0; j < 4; j++)
    {
        if (tbl[j])
        {
            if (max < tbl[j][4])
            {
                max = tbl[j][4];
            }
        }
    }
    return max;
}
// Matched
void ApplyEquipmentModifiers_80033754(unsigned char* dst, UnitStatus* src)
{
    unsigned char* tbl[2];
    int i;
    int j;
    unsigned char* ids;
    MemCopy_800403E8(dst, src->field_20, 12);
    ids = src->field_1C;
    tbl[0] = GetArmorModifiers_8001CDA0(ids[1]);
    tbl[1] = GetAccessoryModifiers_8001CD74(ids[2]);
    for (j = 0; j < 2; j++)
    {
        if (tbl[j])
        {
            for (i = 0; i < 12; i++)
            {
                if ((signed char)tbl[j][i] < (signed char)dst[i])
                {
                    dst[i] = tbl[j][i];
                }
            }
        }
    }
}
// Matched
UnitStatus* GetMinionStatusOf_80033818(Minion* p)
{
    return &p->status_84;
}
// Matched
unsigned char* sub_80033820(Minion* p)
{
    return p->field_CC;
}
// Matched
unsigned char* GetMinionNameOf_80033828(Minion* p)
{
    return p->status_84.name_10;
}
// Matched
unsigned char* GetAncestorName_80033830(Minion* m, int idx)
{
    return m->ancestors_4[idx];
}
// Matched
int GetAncestorElementMask_80033848(Minion* m, int idx)
{
    return m->field_7C[idx];
}
// Matched
short GetMinionId_80033858(Minion* p)
{
    return p->id;
}
// Matched
void GetElementLevels_80033864(Minion* m, unsigned char* out)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        out[i] = m->status_84.element_3E[i];
        if (out[i] < 8)
        {
            out[i] = 0;
        }
        out[i] >>= 1;
    }
}
// Matched
unsigned char GetDominantSpecies_800338B0(Minion* m)
{
    unsigned char ids[8];
    unsigned char ratios[16];
    GetTopSpecies_800338DC(m->species_4C, ids, ratios);
    return ids[0];
}
// Matched
int GetTopSpecies_800338DC(unsigned char* history, unsigned char* ids, int* ratios)
{
    unsigned char hist[0xD3];
    int i;
    int j;
    int k;
    int res;
    int sum;
    k = 0;
    res = k;
    for (i = 0; i < 0xD3; i++)
    {
        hist[i] = 0;
    }
    for (i = 0; i < 3; i++)
    {
        ids[i] = 0xD3;
        ratios[i] = 0;
    }
    for (i = 0; i < 0x30; i++)
    {
        hist[history[i]]++;
    }
    for (i = 0xFF; i >= 0; i--)
    {
        for (j = 0; j < 0xD3; j++)
        {
            if (hist[j] >= i)
            {
                if (i != 0)
                {
                    ids[k] = j;
                }
                else
                {
                    ids[k] = ids[0];
                    if (res == 0)
                    {
                        res = k;
                    }
                }
                ratios[k] = i;
                k++;
                hist[j] = 0;
            }
            if (k >= 3)
            {
                if (res == 0)
                {
                    res = 3;
                }
                goto done;
            }
        }
    }
done:
    sum = ratios[0] + ratios[1] + ratios[2];
    ratios[0] <<= 12;
    ratios[1] <<= 12;
    ratios[2] <<= 12;
    ratios[0] /= sum;
    ratios[1] /= sum;
    ratios[2] /= sum;
    return res;
}
// Matched
void* sub_80033A60(void* p)
{
    return p;
}
// Matched
char* sub_80033A68(char* p)
{
    return p + 0x48;
}
// Matched
int HasSkill_80033A70(UnitStats* p, int idx)
{
    return IsSkillLearned_80031954(&p->skills_6C, idx);
}
// Matched
int HasMagic_80033A90(UnitStats* p, unsigned int idx)
{
    return TestMagicBit_8001AE2C(&p->magicBits_80, idx);
}
// Matched
int GetItemId_80033AB0(UnitStats* p)
{
    return p->species_5C;
}
// Matched
UnitStatus* GetLevantStatus_80033ABC(SaveData* s)
{
    return &s->levantStatus_7C8;
}
// Matched
char* sub_80033AC4(SaveData* s)
{
    return s->field_7BC;
}
// Matched
Minion* GetSaveMinion_80033ACC(SaveData* s, int idx)
{
    return &s->minions[idx];
}
// Matched
UnitStats* GetSaveItem_80033AE4(SaveData* s, int idx)
{
    return &s->items[idx];
}
extern int IsCurrentMapListed_80034140(void);
extern int GetItemFlags_8001CE70(int a);
// Matched
int CheckItemUsable_80033AFC(struct_minion_ref* p)
{
    int item = sub_800AD288(p->cursor_0 + p->scroll_2, 0);
    if (sub_800AD2C8(p->cursor_0 + p->scroll_2, 0) <= 0)
    {
        return 1;
    }
    if (item == 0x29 && p->field_A == 1)
    {
        if (IsCurrentMapListed_80034140())
        {
            return 0;
        }
        return 3;
    }
    if (!(GetItemFlags_8001CE70(item) & 1) && !(GetItemFlags_8001CE70(item) & 2))
    {
        return 2;
    }
    if (p->field_A == 0)
    {
        if (!(GetItemFlags_8001CE70(item) & 2))
        {
            return 4;
        }
    }
    else if (p->field_A == 1)
    {
        if (!(GetItemFlags_8001CE70(item) & 1))
        {
            return 3;
        }
    }
    return 0;
}
extern int FindNthMagicBit_8001AEC0(void* p, int v);
extern int GetSkillMpCost_80031A04(void* p, int idx);
// Matched
int CheckMagicCastable_80033C08(struct_minion_ref* p)
{
    Minion* minion = p->minion_C;
    UnitStatus* status = &minion->status_84;
    int idx = FindNthMagicBit_8001AEC0(&minion->magicBits_F4, p->cursor_0 + p->scroll_2);
    int cost = GetMagicMpCost_8001AC58(idx);
    if (idx >= 0x1E)
    {
        return 6;
    }
    if (status->mp_C >= cost)
    {
        return 0;
    }
    if (p->field_A == 0)
    {
        return 5;
    }
    return 0;
}
// Matched
int CheckSkillUsable_80033C98(struct_minion_ref* p)
{
    int cost;
    short idx = p->cursor_0;
    cost = GetSkillMpCost_80031A04(&p->minion_C->skills_DE, idx);
    if (!IsSkillLearned_80031954(&p->minion_C->skills_DE, idx))
    {
        return 7;
    }
    if (p->minion_C->status_84.mp_C < cost)
    {
        if (p->field_A == 0)
        {
            return 5;
        }
    }
    return 0;
}
// Matched
int CheckMagicHasEffect_80033D20(struct_minion_ref* p)
{
    Minion* minion = p->minion_C;
    UnitStatus* status = &minion->status_84;
    int magic = FindNthMagicBit_8001AEC0(&minion->magicBits_F4, p->cursor_0 + p->scroll_2);
    if (magicData_8007C438[magic].field_0 & 0x40)
    {
        switch (magicData_8007C438[magic].field_7)
        {
        case 0:
            if (status->hp_8 == status->maxHp_A)
            {
                return 3;
            }
            break;
        case 1:
            if (magic != 0x10 && !(minion->status_84.status_0 & 0x7FB))
            {
                return 3;
            }
            break;
        }
    }
    return 0;
}
// Matched
int sub_80033DEC(void)
{
    return 0;
}
typedef struct
{
    short item;
    short pad_2;
    short target;
} ItemUse_DF4;
// Matched
int CheckItemOnTarget_80033DF4(ItemUse_DF4* p)
{
    UnitStatus* target;
    int noEffect = 0;
    if (GetItemFlags_8001CE70(p->item) & 0x80)
    {
        return 0;
    }
    if (GetItemFlags_8001CE70(p->item) & 4)
    {
        return 0;
    }
    if (!(GetItemFlags_8001CE70(p->item) & 8) && p->target == 0)
    {
        return 2;
    }
    if (!(GetItemFlags_8001CE70(p->item) & 0x10) && (p->target == 1 || p->target == 2 || p->target == 3))
    {
        return 1;
    }
    target = GetUnitStatus_80014390(p->target & 0xFF);
    if (p->item != 13 && (target->status_0 & 0x400))
    {
        return 4;
    }
    switch (p->item)
    {
    case 0:
    case 1:
    case 2:
        if (target->hp_8 == target->maxHp_A)
        {
            noEffect = 1;
        }
        break;
    case 3:
        if (target->maxHp_A == 999)
        {
            noEffect = 1;
        }
        break;
    case 4:
        if (target->stats_2C[0] >= 99)
        {
            noEffect = 1;
        }
        break;
    case 5:
        if (target->stats_2C[4] >= 99)
        {
            noEffect = 1;
        }
        break;
    case 6:
        if (target->stats_2C[1] >= 99)
        {
            noEffect = 1;
        }
        break;
    case 7:
        if (target->stats_2C[2] >= 99)
        {
            noEffect = 1;
        }
        break;
    case 8:
        if (target->stats_2C[3] >= 99)
        {
            noEffect = 1;
        }
        break;
    case 9:
    case 10:
    case 11:
    case 12:
        if (target->hp_8 == target->maxHp_A && target->mp_C == target->maxMp_E)
        {
            noEffect = 1;
        }
        break;
    case 13:
        if (!(target->status_0 & 0x7FB) && target->hp_8 == target->maxHp_A && target->mp_C == target->maxMp_E)
        {
            noEffect = 1;
        }
        break;
    case 14:
        if (!(target->status_0 & 1))
        {
            noEffect = 1;
        }
        break;
    case 15:
        if (!(target->status_0 & 0x3F8))
        {
            noEffect = 1;
        }
        break;
    }
    if (noEffect == 1)
    {
        return 3;
    }
    return 0;
}
