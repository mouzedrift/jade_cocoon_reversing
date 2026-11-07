#include "common.h"
#include "funcs.h"
#include "sdk.h"
#include "globals.h"
#include "sound.h"
#include "data_decls.h"
#include "unit.h"
#include "tiy.h"
#include "minion_menu.h"
#include "engine.h"
#include "msg_window.h"
#include "util.h"
#include "unit_query.h"
#include "effect.h"
#include "party.h"
#include "skills.h"




extern UnitSkill* GetUnitSkills_80031B30(int a0);

int GetSkillCommandTargetFlags_80031A94(int* cmd)
{
    int flags = 2;
    UnitSkill* base;
    if (cmd[2] & 0xF)
    {
        flags = 4;
    }
    base = GetUnitSkills_80031B30(LowestSetBit_80014358(cmd[2]) & 0xFF);
    base += cmd[1];
    if (base->id_1 == 0xC)
    {
        flags |= 1;
    }
    return flags;
}
int GetSkillTargetFlags_80031B0C(UnitSkill* base, int idx)
{
    int flags = 4;
    base += idx;
    if (base->id_1 == 0xC)
    {
        flags = 5;
    }
    return flags;
}
extern UnitSkill* GetSlotSkills_800A11A0(int a0);
extern UnitSkill* GetEnemySkills_800A2BA0(int a0);



UnitSkill* GetUnitSkills_80031B30(unit)
    unsigned char unit;
{
    UnitSkill* r = 0;
    unsigned char idx;
    if (unit >= 8)
    {
        idx = unit - 8;
        r = GetSlotSkills_800A11A0(idx);
    }
    else if (unit >= 4)
    {
        int flags = GetEnemyAliveMask_800A248C();
        int bit = 1 << unit;
        if (flags & bit)
        {
            idx = unit - 4;
            r = GetEnemySkills_800A2BA0(idx);
        }
    }
    else if (unit != 0)
    {
        idx = unit - 1;
        r = GetMinionSkills_800107F8(3, idx)->slot;
    }
    return r;
}
int MenuIndexToSkillSlot_80031BDC(int index)
{
    return index;
}
int AddScaledPolyFT4_80031BE4(POLY_FT4* poly, unsigned long* ot, short x, short y, int scaleX, int scaleY, short* offset, int anchorFlags)
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
    w = (poly->u3 - poly->u0 >= 0 ? poly->u3 - poly->u0 : poly->u0 - poly->u3) * scaleX / 256;
    h = (poly->v3 - poly->v0 >= 0 ? poly->v3 - poly->v0 : poly->v0 - poly->v3) * scaleY / 256;
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
        poly->x1 = x0;
        poly->y2 = y0;
        poly->x0 = x0 + w;
        poly->y3 = y0;
        poly->x3 = x0;
        poly->y0 = y0 + h;
        poly->x2 = x0 + w;
        poly->y1 = y0 + h;
    }
    else if (flags & 0x100)
    {
        poly->x1 = x0;
        poly->y0 = y0;
        poly->x0 = x0 + w;
        poly->y1 = y0;
        poly->x3 = x0;
        poly->y2 = y0 + h;
        poly->x2 = x0 + w;
        poly->y3 = y0 + h;
    }
    else if (flags & 0x200)
    {
        poly->x0 = x0;
        poly->y2 = y0;
        poly->x1 = x0 + w;
        poly->y3 = y0;
        poly->x2 = x0;
        poly->y0 = y0 + h;
        poly->x3 = x0 + w;
        poly->y1 = y0 + h;
    }
    else
    {
        poly->x0 = x0;
        poly->y0 = y0;
        poly->x1 = x0 + w;
        poly->y1 = y0;
        poly->x2 = x0;
        poly->y2 = y0 + h;
        poly->x3 = x0 + w;
        poly->y3 = y0 + h;
    }
    if (poly->x0 > poly->x1)
    {
        hi = poly->x0;
        lo = poly->x1;
    }
    else
    {
        lo = poly->x0;
        hi = poly->x1;
    }
    if (hi < poly->x2)
    {
        hi = poly->x2;
    }
    else if (poly->x2 < lo)
    {
        lo = poly->x2;
    }
    if (hi < poly->x3)
    {
        hi = poly->x3;
    }
    else if (poly->x3 < lo)
    {
        lo = poly->x3;
    }
    if (lo > 0x140 || hi < 0)
    {
        return 0;
    }
    if (poly->y0 > poly->y1)
    {
        hi = poly->y0;
        lo = poly->y1;
    }
    else
    {
        lo = poly->y0;
        hi = poly->y1;
    }
    if (hi < poly->y2)
    {
        hi = poly->y2;
    }
    else if (poly->y2 < lo)
    {
        lo = poly->y2;
    }
    if (hi < poly->y3)
    {
        hi = poly->y3;
    }
    else if (poly->y3 < lo)
    {
        lo = poly->y3;
    }
    if (lo > 0xF0 || hi < 0)
    {
        return 0;
    }
    AddPrimCopy_80040298(ot, poly, 10);
    return 1;
}
#define ROT_X(x, y, a) ((x) * sinTable_80084540[((a) + 0x400) & 0xFFF] / 4096 - (y) * sinTable_80084540[(a) & 0xFFF] / 4096)
#define ROT_Y(x, y, a) ((x) * sinTable_80084540[(a) & 0xFFF] / 4096 + (y) * sinTable_80084540[((a) + 0x400) & 0xFFF] / 4096)
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
void GetPublicTiySprt_80032470(int idx, SPRT* pOut20, DR_TPAGE* pOut8)
{
    *pOut20 = publicTiySprts_8008D434[idx];
    *pOut8 = publicTiyTPages_8008D440[idx];
}
void AddRotatedPolyFT4_800324D8(POLY_FT4* poly, int cx, int cy, int w, int h, int angle, void* ot)
{
    int a = -angle;
    short* cosA = &sinTable_80084540[(a + 0x400) & 0xFFF];
    short* sinA = &sinTable_80084540[(a + 0x800) & 0xFFF];
    poly->x0 = cx + (w + (*cosA * -w + *sinA * -h) / 4096) / 2;
    poly->y0 = cy + (h + (-*sinA * -w + *cosA * -h) / 4096) / 2;
    poly->x1 = cx + (w + (*cosA * w + *sinA * -h) / 4096) / 2;
    poly->y1 = cy + (h + (-*sinA * w + *cosA * -h) / 4096) / 2;
    poly->x2 = cx + (w + (*cosA * -w + *sinA * h) / 4096) / 2;
    poly->y2 = cy + (h + (-*sinA * -w + *cosA * h) / 4096) / 2;
    poly->x3 = cx + (w + (*cosA * w + *sinA * h) / 4096) / 2;
    poly->y3 = cy + (h + (-*sinA * w + *cosA * h) / 4096) / 2;
    AddPrimCopy_80040298(ot, poly, 10);
}
void AddRotatedPolyFT4Uv_800327A8(POLY_FT4* poly, int cx, int cy, int w, int h, int du, int dv, int angle, void* ot)
{
    short* sinA = &sinTable_80084540[angle & 0xFFF];
    short* cosA = &sinTable_80084540[(angle + 0x400) & 0xFFF];

    poly->u1 = poly->u0 + du;
    poly->v1 = poly->v0;
    poly->u2 = poly->u0;
    poly->v2 = poly->v0 + dv;
    poly->u3 = poly->u0 + du;
    poly->v3 = poly->v0 + dv;
    poly->x0 = cx + (w / 2 + (*cosA * (-w / 2) + *sinA * (-h / 2)) / 4096);
    poly->y0 = cy + (h / 2 + (-*sinA * (-w / 2) + *cosA * (-h / 2)) / 4096);
    poly->x1 = cx + (w / 2 + (*cosA * (w / 2) + *sinA * (-h / 2)) / 4096);
    poly->y1 = cy + (h / 2 + (-*sinA * (w / 2) + *cosA * (-h / 2)) / 4096);
    poly->x2 = cx + (w / 2 + (*cosA * (-w / 2) + *sinA * (h / 2)) / 4096);
    poly->y2 = cy + (h / 2 + (-*sinA * (-w / 2) + *cosA * (h / 2)) / 4096);
    poly->x3 = cx + (w / 2 + (*cosA * (w / 2) + *sinA * (h / 2)) / 4096);
    poly->y3 = cy + (h / 2 + (-*sinA * (w / 2) + *cosA * (h / 2)) / 4096);
    AddPrimCopy_80040298(ot, poly, 10);
}
void SetRotatedPolyFT4_80032A88(POLY_FT4* poly, int cx, int cy, int w, int h, int angle)
{
    int a = -angle;
    short* cosA = &sinTable_80084540[(a + 0x400) & 0xFFF];
    short* sinA = &sinTable_80084540[(a + 0x800) & 0xFFF];
    poly->x0 = cx + (w + (*cosA * -w + *sinA * -h) / 4096) / 2;
    poly->y0 = cy + (h + (-*sinA * -w + *cosA * -h) / 4096) / 2;
    poly->x1 = cx + (w + (*cosA * w + *sinA * -h) / 4096) / 2;
    poly->y1 = cy + (h + (-*sinA * w + *cosA * -h) / 4096) / 2;
    poly->x2 = cx + (w + (*cosA * -w + *sinA * h) / 4096) / 2;
    poly->y2 = cy + (h + (-*sinA * -w + *cosA * h) / 4096) / 2;
    poly->x3 = cx + (w + (*cosA * w + *sinA * h) / 4096) / 2;
    poly->y3 = cy + (h + (-*sinA * w + *cosA * h) / 4096) / 2;
}
void AddPolyFT4FlipXY_80032D34(unsigned short* poly, void* ot)
{
    int dx = (short)poly[8] - (short)poly[4];
    int dy = (short)poly[0xD] - (short)poly[5];
    short* copy = AddPrimCopy_80040298(ot, poly, 10);
    copy[4] = poly[4] + dx;
    copy[5] = poly[5] + dy;
    copy[8] = poly[4];
    copy[9] = poly[5] + dy;
    copy[0xC] = poly[4] + dx;
    copy[0xD] = poly[5];
    copy[0x10] = poly[4];
    copy[0x11] = poly[5];
}
void AddPolyFT4FlipX_80032DFC(short* poly, void* ot)
{
    int d = poly[8] - poly[4];
    short* copy = AddPrimCopy_80040298(ot, poly, 10);
    copy[4] = poly[4] + d;
    copy[8] = poly[4];
    copy[12] = poly[4] + d;
    copy[16] = poly[4];
}
void AddPolyFT4FlipY_80032E78(unsigned short* poly, void* ot)
{
    int d = ((short*)poly)[13] - ((short*)poly)[5];
    unsigned short* copy = AddPrimCopy_80040298(ot, poly, 10);
    copy[5] = poly[5] + d;
    copy[9] = poly[5] + d;
    copy[13] = poly[5];
    copy[17] = poly[5];
}
void AddPolyFT4Rot90Ccw_80032EF4(unsigned short* poly, void* ot)
{
    int x0 = ((short*)poly)[4];
    int y0 = ((short*)poly)[5];
    unsigned short* copy = AddPrimCopy_80040298(ot, poly, 10);
    unsigned short y1;
    copy[4] = poly[12];
    copy[5] = poly[13];
    copy[12] = poly[16];
    copy[13] = poly[17];
    copy[16] = poly[8];
    y1 = poly[9];
    copy[8] = x0;
    copy[9] = y0;
    copy[17] = y1;
}
void AddPolyFT4Rot90Cw_80032F88(unsigned short* poly, void* ot)
{
    int x0 = ((short*)poly)[4];
    int y0 = ((short*)poly)[5];
    unsigned short* copy = AddPrimCopy_80040298(ot, poly, 10);
    unsigned short y1;
    copy[4] = poly[8];
    copy[5] = poly[9];
    copy[8] = poly[16];
    copy[9] = poly[17];
    copy[16] = poly[12];
    y1 = poly[13];
    copy[12] = x0;
    copy[13] = y0;
    copy[17] = y1;
}
void AddPolyFT4Copy_8003301C(void* poly, void* ot)
{
    AddPrimCopy_80040298(ot, poly, 10);
}
void SetDrTPageAbr_80033048(unsigned short* tpage, int abr)
{
    tpage[2] = (tpage[2] & 0xFF9F) | ((abr & 3) << 5);
}
void SetPolyFT4Abr_80033064(unsigned short* poly, int abr)
{
    poly[0xB] = (poly[0xB] & 0xFF9F) | ((abr & 3) << 5);
}
void DrawPublicTiySprt_80033080(unsigned short* pos, int idx, int otIdx)
{
    publicTiySprts_8008D434[idx].x0 = pos[0];
    publicTiySprts_8008D434[idx].y0 = pos[1];
    AddPrimCopy_80040298(pOT_8008D454 + otIdx, &publicTiySprts_8008D434[idx], 5);
    AddPrimCopy_80040298(pOT_8008D454 + otIdx, &publicTiyTPages_8008D440[idx], 2);
}
void DrawPublicTiySprtColored_80033114(unsigned short* pos, int idx, void* ot, unsigned char* col)
{
    publicTiySprts_8008D434[idx].r0 = col[0];
    publicTiySprts_8008D434[idx].g0 = col[1];
    publicTiySprts_8008D434[idx].b0 = col[2];
    publicTiySprts_8008D434[idx].x0 = pos[0];
    publicTiySprts_8008D434[idx].y0 = pos[1];
    AddPrimCopy_80040298(ot, &publicTiySprts_8008D434[idx], 5);
    AddPrimCopy_80040298(ot, &publicTiyTPages_8008D440[idx], 2);
}
void AddSprtWithTPage_800331C4(unsigned short* pos, SPRT* sprt, void* tpage, void* ot, unsigned char* col)
{
    if (col)
    {
        sprt->code &= 0xFE;
        sprt->r0 = col[0];
        sprt->g0 = col[1];
        sprt->b0 = col[2];
    }
    else
    {
        sprt->code |= 1;
    }
    sprt->x0 = pos[0];
    sprt->y0 = pos[1];
    AddPrimCopy_80040298(ot, sprt, 5);
    AddPrimCopy_80040298(ot, tpage, 2);
}
extern DRAWENV drawEnv_8008D698[2];
void AddDrawAreaPrim_8003326C(RECT* bounds, void* ot)
{
    DR_AREA area;
    RECT rect;
    DRAWENV* env = drawEnv_8008D698;
    RECT* clip = &env[bDoubleBuffer_8008D428].clip;
    rect.x = bounds->x + clip->x;
    rect.y = bounds->y + clip->y;
    rect.w = bounds->w;
    rect.h = bounds->h;
    SetDrawArea(&area, &rect);
    AddPrimCopy_80040298(ot, &area, 3);
}
void AddClipDrawAreaPrim_80033308(void* ot)
{
    DR_AREA area;
    RECT rect;
    DRAWENV* env = drawEnv_8008D698;
    unsigned short* clip = (unsigned short*)&env[bDoubleBuffer_8008D428].clip;
    rect.x = clip[0];
    rect.y = clip[1];
    rect.w = clip[2];
    rect.h = clip[3];
    SetDrawArea(&area, &rect);
    AddPrimCopy_80040298(ot, &area, 3);
}
void PulseColor_80033394(unsigned char* out, unsigned char* c0, unsigned char* c1, unsigned int tick, int period, int half)
{
    int phase;
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
    phase = tick % period;
    if (phase < half)
    {
        den = half;
    }
    else
    {
        phase = period - phase;
        den = period - half;
    }
    r = c0[0] + (c1[0] - c0[0]) * phase / den;
    g = c0[1] + (c1[1] - c0[1]) * phase / den;
    b = c0[2] + (c1[2] - c0[2]) * phase / den;
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
unsigned char GetByteAt_800334BC(unsigned char* arr, int idx)
{
    return arr[idx];
}
short GetMaxHp_800334CC(UnitStatus* status)
{
    return status->hp_8.max_2;
}
short GetHp_800334D8(UnitStatus* status)
{
    return status->hp_8.cur_0;
}
short GetMaxMp_800334E4(UnitStatus* status)
{
    return status->mp_C.max_2;
}
short GetMp_800334F0(UnitStatus* status)
{
    return status->mp_C.cur_0;
}
int GetExp_800334FC(int* status)
{
    return status[1];
}
short GetElementMask_80033508(UnitStatus* status)
{
    return status->elementMask_42;
}
short GetLevel_80033514(UnitStatus* status)
{
    return status->level_44;
}
unsigned char* GetStats_80033520(UnitStatus* status)
{
    return status->stats_2C.cur_0;
}
unsigned char GetStat_80033528(UnitStatus* status, int idx)
{
    return GetByteAt_800334BC(status->stats_2C.cur_0, idx);
}
int HasStatusFlag_80033548(UnitStatus* status, int mask)
{
    return (status->status_0 & mask) != 0;
}
unsigned char GetModifier_8003355C(UnitStatus* status, int idx)
{
    return status->modifiers_20[idx];
}
int GetEquipmentId_8003356C(UnitStatus* status, unsigned int idx)
{
    int id = 0xFF;
    switch (idx)
    {
    case 0:
        id = status->equipment_1C[0];
        break;
    case 1:
        id = status->equipment_1C[1];
        break;
    case 2:
        id = status->equipment_1C[2];
        break;
    case 3:
        id = status->equipment_1C[3];
        break;

    }
    return id;
}
void CalcEffectiveStatus_800335D0(UnitStatus* src, UnitStatus* dst)
{
    int level;
    MemCopy_800403E8(dst, src, sizeof(UnitStatus));
    level = CalcEquippedStats_80033624(dst->stats_2C.cur_0, dst);
    if (level)
    {
        dst->level_44 = level;
    }
    ApplyEquipmentModifiers_80033754(dst->modifiers_20, dst);
}
int CalcEquippedStats_80033624(unsigned char* out, UnitStatus* status)
{
    unsigned char* stats = status->stats_2C.cur_0;
    unsigned char* ids = status->equipment_1C;
    int* tbl[4];
    int i;
    int j;
    int value;
    int max;
    tbl[0] = GetWeaponStatBonus_8001CEF4(ids[0]);
    tbl[1] = GetArmorStatBonus_8001CFB0(ids[1]);
    tbl[2] = GetAccessoryStatBonus_8001D078(ids[2]);
    tbl[3] = 0;
    for (i = 0; i < 6; i++)
    {
        value = stats[i];
        for (j = 0; j < 4; j++)
        {
            if (tbl[j])
            {
                value += ((signed char*)tbl[j])[i];
            }
        }
        out[i] = value < 0 ? 0 : (value < 100 ? value : 99);
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
void ApplyEquipmentModifiers_80033754(unsigned char* dst, UnitStatus* src)
{
    unsigned char* tbl[2];
    int i;
    int j;
    unsigned char* ids;
    MemCopy_800403E8(dst, src->modifiers_20, 12);
    ids = src->equipment_1C;
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
UnitStatus* GetMinionStatusOf_80033818(Minion* minion)
{
    return &minion->status_84;
}
unsigned char* GetMinionStatBlockOf_80033820(Minion* minion)
{
    return minion->field_CC.cur_0;
}
unsigned char* GetMinionNameOf_80033828(Minion* minion)
{
    return minion->status_84.name_10;
}
unsigned char* GetAncestorName_80033830(Minion* m, int idx)
{
    return m->ancestors_4[idx];
}
int GetAncestorElementMask_80033848(Minion* m, int idx)
{
    return m->ancestorElements_7C[idx];
}
short GetMinionId_80033858(Minion* minion)
{
    return minion->id;
}
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
int GetDominantSpecies_800338B0(Minion* m)
{
    unsigned char ids[8];
    unsigned char ratios[16];
    GetTopSpecies_800338DC(m->species_4C, ids, ratios);
    return ids[0];
}
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
void* GetStatsStatus_80033A60(void* stats)
{
    return stats;
}
char* NextUnitStatus_80033A68(char* stats)
{
    return stats + 0x48;
}
int HasSkill_80033A70(UnitStats* stats, int idx)
{
    return IsSkillLearned_80031954(&stats->skills_6C, idx);
}
int HasMagic_80033A90(UnitStats* stats, unsigned int idx)
{
    return TestMagicBit_8001AE2C(&stats->magicBits_80, idx);
}
int GetItemId_80033AB0(UnitStats* stats)
{
    return stats->species_5C;
}
UnitStatus* GetLevantStatus_80033ABC(SaveData* save)
{
    return &save->levantStatus_7C8;
}
char* GetSaveDataField7BC_80033AC4(SaveData* save)
{
    return save->field_7BC;
}
Minion* GetSaveMinion_80033ACC(SaveData* save, int idx)
{
    return &save->minions[idx];
}
UnitStats* GetSaveItem_80033AE4(SaveData* save, int idx)
{
    return &save->items[idx];
}
int CheckItemUsable_80033AFC(ListMenuState* menu)
{
    int item = GetInventorySlotId_800AD288(menu->cursor_0 + menu->scroll_2, 0);
    if (GetInventorySlotCount_800AD2C8(menu->cursor_0 + menu->scroll_2, 0) <= 0)
    {
        return 1;
    }
    if (item == 0x29 && menu->fieldMenu_A == 1)
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
    if (menu->fieldMenu_A == 0)
    {
        if (!(GetItemFlags_8001CE70(item) & 2))
        {
            return 4;
        }
    }
    else if (menu->fieldMenu_A == 1)
    {
        if (!(GetItemFlags_8001CE70(item) & 1))
        {
            return 3;
        }
    }
    return 0;
}
int CheckMagicCastable_80033C08(ListMenuState* menu)
{
    Minion* minion = menu->minion_C;
    UnitStatus* status = &minion->status_84;
    int idx = FindNthMagicBit_8001AEC0(&minion->magicBits_F4, menu->cursor_0 + menu->scroll_2);
    int cost = GetMagicMpCost_8001AC58(idx);
    if (idx >= 0x1E)
    {
        return 6;
    }
    if (status->mp_C.cur_0 >= cost)
    {
        return 0;
    }
    if (menu->fieldMenu_A == 0)
    {
        return 5;
    }
    return 0;
}
int CheckSkillUsable_80033C98(ListMenuState* menu)
{
    int cost;
    short idx = menu->cursor_0;
    cost = GetSkillMpCost_80031A04(menu->minion_C->skills_DE.slot, idx);
    if (!IsSkillLearned_80031954(&menu->minion_C->skills_DE, idx))
    {
        return 7;
    }
    if (menu->minion_C->status_84.mp_C.cur_0 < cost)
    {
        if (menu->fieldMenu_A == 0)
        {
            return 5;
        }
    }
    return 0;
}
int CheckMagicHasEffect_80033D20(ListMenuState* menu)
{
    Minion* minion = menu->minion_C;
    UnitStatus* status = &minion->status_84;
    int magic = FindNthMagicBit_8001AEC0(&minion->magicBits_F4, menu->cursor_0 + menu->scroll_2);
    if (magicData_8007C438[magic].flags_0 & 0x40)
    {
        switch (magicData_8007C438[magic].kind_7)
        {
        case 0:
            if (status->hp_8.cur_0 == status->hp_8.max_2)
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
int ReturnZero_80033DEC(void)
{
    return 0;
}
int CheckItemOnTarget_80033DF4(TargetQuery* use)
{
    UnitStatus* target;
    int noEffect = 0;
    if (GetItemFlags_8001CE70(use->id_0) & 0x80)
    {
        return 0;
    }
    if (GetItemFlags_8001CE70(use->id_0) & 4)
    {
        return 0;
    }
    if (!(GetItemFlags_8001CE70(use->id_0) & 8) && use->target_4 == 0)
    {
        return 2;
    }
    if (!(GetItemFlags_8001CE70(use->id_0) & 0x10) && (use->target_4 == 1 || use->target_4 == 2 || use->target_4 == 3))
    {
        return 1;
    }
    target = GetUnitStatus_80014390(use->target_4 & 0xFF);
    if (use->id_0 != 13 && (target->status_0 & 0x400))
    {
        return 4;
    }
    switch (use->id_0)
    {
    case 0:
    case 1:
    case 2:
        if (target->hp_8.cur_0 == target->hp_8.max_2)
        {
            noEffect = 1;
        }
        break;
    case 3:
        if (target->hp_8.max_2 == 999)
        {
            noEffect = 1;
        }
        break;
    case 4:
        if (target->stats_2C.cur_0[0] >= 99)
        {
            noEffect = 1;
        }
        break;
    case 5:
        if (target->stats_2C.cur_0[4] >= 99)
        {
            noEffect = 1;
        }
        break;
    case 6:
        if (target->stats_2C.cur_0[1] >= 99)
        {
            noEffect = 1;
        }
        break;
    case 7:
        if (target->stats_2C.cur_0[2] >= 99)
        {
            noEffect = 1;
        }
        break;
    case 8:
        if (target->stats_2C.cur_0[3] >= 99)
        {
            noEffect = 1;
        }
        break;
    case 9:
    case 10:
    case 11:
    case 12:
        if (target->hp_8.cur_0 == target->hp_8.max_2 && target->mp_C.cur_0 == target->mp_C.max_2)
        {
            noEffect = 1;
        }
        break;
    case 13:
        if (!(target->status_0 & 0x7FB) && target->hp_8.cur_0 == target->hp_8.max_2 && target->mp_C.cur_0 == target->mp_C.max_2)
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
