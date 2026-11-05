#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "camera.h"
#include "model.h"
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
#include "effect_data.h"
#include "engine.h"
#include "main.h"
#include "model_ftg.h"
#include "util.h"

extern short screenOffset_8008D474[2];
extern short battleCamSpline1Tail_80084350[]; // a short table (indexed & 0xFFF) starts at +0x1F0 (0x80084540)
extern int QueueFileRequest_8003BC84(FileRequestDesc* req);
extern int StartFileRequestTask_8003C6C8(FileRequestDesc* req);
extern unsigned short padPrevHeld_800918C8[];
extern unsigned short padRepeat_800918CC[];
extern unsigned short padReleased_800918D4[];
extern unsigned short padPressed_8009194C[];
extern unsigned short padHoldFrames_80091950[][16];
extern signed char padAnalog_800918D8[][4];
extern unsigned char padAnalogMax_800918E0[][4];
// Matched
int GetFtgObjectCount_80021738(int* file)
{
    return file[1];
}
// Matched
void AllocFtgObjects_80021744(FtgObject** out, int count, int heap)
{
    *out = HeapAlloc_8003FC8C(count * 0x54, heap);
}
// Matched
void FreeFtgObjects_80021784(FtgObject** objs, unsigned int count, int heap)
{
    FtgObject* obj = *objs;
    unsigned int i;
    for (i = 0; i < count; i++)
    {
        FreeFtgObject_800229B0(obj, heap);
        obj++;
    }
    HeapFree_8003FD18(*objs, heap);
    *objs = 0;
}
// Matched
void FreeFtgObjectData_80021804(FtgObject* obj, int heap)
{
    FreeFtgObject_800229B0(obj, heap);
}
// Matched
void LoadFtgObjects_80021824(int* file, FtgObject* out, int count, int heap, int reloc)
{
    unsigned int fileCount = GetFtgObjectCount_80021738(file);
    int src = (int)(file + 4);
    unsigned int i;
    for (i = 0; i < fileCount; i++)
    {
        src = LoadFtgObject_80022458(out, src, heap, reloc);
        out++;
    }
}
// Matched
void CopyFtgObject_800218A8(FtgObject* src, FtgObject* dst, int heap)
{
    char* buf;
    int size;
    int i;
    size = src->f3_0.count * 0x24 + src->g3_8.count * 0x3C;
    size += src->ft3_10.count * 0x30;
    size += src->gt3_18.count * 0x48;
    size += src->f4_20.count * 0x2C;
    size += src->g4_28.count * 0x50;
    size += src->ft4_30.count * 0x38;
    size += src->gt4_38.count * 0x5C;
    size += src->spriteCount_40 * 0x14;
    size += src->texSpriteCount_48 * 0x14;
    if (size)
    {
        buf = HeapAlloc_8003FC8C(size, heap);
    }
    else
    {
        buf = 0;
    }
    dst->f3_0.count = src->f3_0.count;
    dst->f3_0.items = (FtgPolyF3*)buf;
    buf += src->f3_0.count * 0x24;
    dst->g3_8.count = src->g3_8.count;
    dst->g3_8.items = (FtgPolyG3*)buf;
    buf += src->g3_8.count * 0x3C;
    dst->ft3_10.count = src->ft3_10.count;
    dst->ft3_10.items = (FtgPolyFT3*)buf;
    buf += src->ft3_10.count * 0x30;
    dst->gt3_18.count = src->gt3_18.count;
    dst->gt3_18.items = (FtgPolyGT3*)buf;
    buf += src->gt3_18.count * 0x48;
    dst->f4_20.count = src->f4_20.count;
    dst->f4_20.items = (FtgPolyF4*)buf;
    buf += src->f4_20.count * 0x2C;
    dst->g4_28.count = src->g4_28.count;
    dst->g4_28.items = (FtgPolyG4*)buf;
    buf += src->g4_28.count * 0x50;
    dst->ft4_30.count = src->ft4_30.count;
    dst->ft4_30.items = (FtgPolyFT4*)buf;
    buf += src->ft4_30.count * 0x38;
    dst->gt4_38.count = src->gt4_38.count;
    dst->gt4_38.items = (FtgPolyGT4*)buf;
    buf += src->gt4_38.count * 0x5C;
    dst->spriteCount_40 = src->spriteCount_40;
    dst->sprites_44 = (FtgSprite*)buf;
    buf += src->spriteCount_40 * 0x14;
    dst->texSpriteCount_48 = src->texSpriteCount_48;
    dst->texSprites_50 = (FtgSprite*)buf;
    for (i = 0; i < dst->f3_0.count; i++)
    {
        MemCopy_800403E8(&dst->f3_0.items[i], &src->f3_0.items[i], 0x24);
    }
    for (i = 0; i < dst->g3_8.count; i++)
    {
        MemCopy_800403E8(&dst->g3_8.items[i], &src->g3_8.items[i], 0x3C);
    }
    for (i = 0; i < dst->ft3_10.count; i++)
    {
        MemCopy_800403E8(&dst->ft3_10.items[i], &src->ft3_10.items[i], 0x30);
    }
    for (i = 0; i < dst->gt3_18.count; i++)
    {
        MemCopy_800403E8(&dst->gt3_18.items[i], &src->gt3_18.items[i], 0x48);
    }
    for (i = 0; i < dst->f4_20.count; i++)
    {
        MemCopy_800403E8(&dst->f4_20.items[i], &src->f4_20.items[i], 0x2C);
    }
    for (i = 0; i < dst->g4_28.count; i++)
    {
        MemCopy_800403E8(&dst->g4_28.items[i], &src->g4_28.items[i], 0x50);
    }
    for (i = 0; i < dst->ft4_30.count; i++)
    {
        MemCopy_800403E8(&dst->ft4_30.items[i], &src->ft4_30.items[i], 0x38);
    }
    for (i = 0; i < dst->gt4_38.count; i++)
    {
        MemCopy_800403E8(&dst->gt4_38.items[i], &src->gt4_38.items[i], 0x5C);
    }
    for (i = 0; i < dst->spriteCount_40; i++)
    {
        MemCopy_800403E8(&dst->sprites_44[i], &src->sprites_44[i], 0x14);
    }
    for (i = 0; i < dst->texSpriteCount_48; i++)
    {
        MemCopy_800403E8(&dst->texSprites_50[i], &src->texSprites_50[i], 0x14);
    }
    dst->tpage_4C = src->tpage_4C;
    dst->clut_4E = src->clut_4E;
}
// Matched
int GetFtgMatCount_80021DE4(int* file)
{
    return file[2];
}
// Matched
void AllocFtgMatList_80021DF0(FtgMatList* list, int count, int heap)
{
    list->count_0 = count;
    list->items_4 = HeapAlloc_8003FC8C(count * 16, heap);
}
// p is volatile to keep the store before the load
// Matched
void FreeFtgMatList_80021E24(volatile FtgMatList* list, int h)
{
    list->count_0 = 0;
    HeapFree_8003FD18(list->items_4, h);
}
// Matched
void LoadFtgMatList_80021E4C(int* file, FtgMatList* out, unsigned int count)
{
    unsigned short* src = (unsigned short*)((char*)file + file[3]);
    unsigned int i;
    for (i = 0; i < count; i++)
    {
        unsigned short* dst = out->items_4[i];
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = src[3];
        dst[4] = src[4];
        dst[5] = src[5];
        dst[6] = src[6];
        dst[7] = src[7];
        src += 8;
    }
}
// r2 is unused (the original frame has room for it)
// Matched
void MakeFtgSpritePoly_80021EDC(FtgPolyFT4* src, POLY_FT4* dst)
{
    RECT rect;
    RECT r2;
    rect.x = src->u0;
    rect.y = src->v0;
    rect.w = src->u3;
    rect.h = src->v3;
    if (src->u1 < rect.x)
    {
        rect.x = src->u1;
    }
    if (rect.x > src->u2)
    {
        rect.x = src->u2;
    }
    if (rect.x > src->u3)
    {
        rect.x = src->u3;
    }
    if (src->v1 < rect.y)
    {
        rect.y = src->v1;
    }
    if (rect.y > src->v2)
    {
        rect.y = src->v2;
    }
    if (rect.y > src->v3)
    {
        rect.y = src->v3;
    }
    if (rect.w < src->u2)
    {
        rect.w = src->u2;
    }
    if (rect.w < src->u1)
    {
        rect.w = src->u1;
    }
    if (rect.w < src->u0)
    {
        rect.w = src->u0;
    }
    if (rect.h < src->v2)
    {
        rect.h = src->v2;
    }
    if (rect.h < src->v1)
    {
        rect.h = src->v1;
    }
    if (rect.h < src->v0)
    {
        rect.h = src->v0;
    }
    setlen(dst, 9);
    dst->code = 0x2C;
    dst->r0 = src->c.r;
    dst->g0 = src->c.g;
    dst->b0 = src->c.b;
    dst->u0 = rect.x;
    dst->v0 = rect.y;
    dst->u1 = rect.w;
    dst->v1 = rect.y;
    dst->u2 = rect.x;
    dst->v2 = rect.h;
    dst->u3 = rect.w;
    dst->v3 = rect.h;
    dst->x0 = 0;
    dst->y0 = 0;
    dst->x1 = rect.w - rect.x;
    dst->y1 = 0;
    dst->x2 = 0;
    dst->y2 = rect.h - rect.y;
    dst->x3 = rect.w - rect.x;
    dst->y3 = rect.h - rect.y;
    dst->code = src->c.code;
    dst->tpage = src->tpage;
    dst->clut = src->clut;
}
// Matched
void MakeFtgSprt_800221DC(FtgPolyFT4* src, SPRT* dst, DR_TPAGE* tpage)
{
    RECT rect;
    rect.x = src->u0;
    rect.y = src->v0;
    rect.w = src->u3;
    rect.h = src->v3;
    if (src->u1 < rect.x)
    {
        rect.x = src->u1;
    }
    if (rect.x > src->u2)
    {
        rect.x = src->u2;
    }
    if (rect.x > src->u3)
    {
        rect.x = src->u3;
    }
    if (src->v1 < rect.y)
    {
        rect.y = src->v1;
    }
    if (rect.y > src->v2)
    {
        rect.y = src->v2;
    }
    if (rect.y > src->v3)
    {
        rect.y = src->v3;
    }
    if (rect.w < src->u2)
    {
        rect.w = src->u2;
    }
    if (rect.w < src->u1)
    {
        rect.w = src->u1;
    }
    if (rect.w < src->u0)
    {
        rect.w = src->u0;
    }
    if (rect.h < src->v2)
    {
        rect.h = src->v2;
    }
    if (rect.h < src->v1)
    {
        rect.h = src->v1;
    }
    if (rect.h < src->v0)
    {
        rect.h = src->v0;
    }
    setlen(dst, 4);
    dst->code = 0x64;
    dst->r0 = src->c.r;
    dst->g0 = src->c.g;
    dst->b0 = src->c.b;
    dst->u0 = rect.x;
    dst->v0 = rect.y;
    dst->x0 = 0;
    dst->y0 = 0;
    dst->w = rect.w - rect.x;
    dst->h = rect.h - rect.y;
    dst->clut = src->clut;
    SetDrawTPage(tpage, 0, 1, src->tpage);
}
// Matched
int LoadFtgObject_80022458(FtgObject* out, unsigned char* src, int h, int reloc)
{
    int typeCounts[10];
    FtgSpriteGroups8 A;
    FtgSpriteGroups9 B;
    unsigned int i;
    unsigned int primCount;
    unsigned char* hdr;
    FtgPrimHeader* prim;
    unsigned int type;
    unsigned int j;
    int k;
    for (j = 0; j < 10; j++)
    {
        typeCounts[j] = 0;
    }
    hdr = src;
    src += 0x28;
    primCount = AllocFtgObjectPrims_80022634(out, (FtgSrcObjectHeader*)hdr, h);
    AllocFtgSpriteGroups_800228F8(&A, &B, (FtgSrcObjectHeader*)hdr, h);
    for (i = 0; i < primCount; i++)
    {
        prim = (FtgPrimHeader*)src;
        src += 4;
        type = prim->type_0;
        k = typeCounts[type];
        typeCounts[type] = k + 1;
        if (reloc != 0 && ftgPrimRelocators_8007DB08[type] != 0)
        {
            ftgPrimRelocators_8007DB08[type](src, reloc);
        }
        switch (type)
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            src += ftgPrimLoaders_8007DAE0[type](prim, src, out, k, h);
            break;
        case 8:
            src += LoadFtgSprites_8002300C(prim, (FtgSrcSprites8*)src, &A, k, h);
            break;
        case 9:
            src += LoadFtgTexSprites_8002320C(prim, (FtgSrcSprites9*)src, &B, k, h);
            break;
        }
    }
    MergeFtgSpriteGroups_80022CC4(out, &A, &B, h);
    FreeFtgSpriteGroups_800229E0(&A, &B, h);
    return (int)src;
}
// Matched
int AllocFtgObjectPrims_80022634(FtgObject* out, FtgSrcObjectHeader* hdr, int h)
{
    int spriteCount;
    int texSpriteCount;
    int size;
    int total;
    char* buf;
    int* c = hdr->counts_0;
    buf = 0;
    CountFtgSprites_80022B84((unsigned char*)hdr, &spriteCount, &texSpriteCount);
    size = c[0] * 0x24 + c[1] * 0x3C;
    total = c[0] + c[1];
    size += c[2] * 0x30;
    total += c[2];
    size += c[3] * 0x48;
    total += c[3];
    size += c[4] * 0x2C;
    total += c[4];
    size += c[5] * 0x50;
    total += c[5];
    size += c[6] * 0x38;
    total += c[6];
    size += c[7] * 0x5C;
    total += c[7];
    size += spriteCount * 0x14;
    total += c[8];
    size += texSpriteCount * 0x14;
    total += c[9];
    if (size != 0)
    {
        buf = HeapAlloc_8003FC8C(size, h);
    }
    out->f3_0.count = c[0];
    out->f3_0.items = (FtgPolyF3*)buf;
    buf += c[0] * 0x24;
    out->g3_8.count = c[1];
    out->g3_8.items = (FtgPolyG3*)buf;
    buf += c[1] * 0x3C;
    out->ft3_10.count = c[2];
    out->ft3_10.items = (FtgPolyFT3*)buf;
    buf += c[2] * 0x30;
    out->gt3_18.count = c[3];
    out->gt3_18.items = (FtgPolyGT3*)buf;
    buf += c[3] * 0x48;
    out->f4_20.count = c[4];
    out->f4_20.items = (FtgPolyF4*)buf;
    buf += c[4] * 0x2C;
    out->g4_28.count = c[5];
    out->g4_28.items = (FtgPolyG4*)buf;
    buf += c[5] * 0x50;
    out->ft4_30.count = c[6];
    out->ft4_30.items = (FtgPolyFT4*)buf;
    buf += c[6] * 0x38;
    out->gt4_38.count = c[7];
    out->gt4_38.items = (FtgPolyGT4*)buf;
    buf += c[7] * 0x5C;
    out->spriteCount_40 = spriteCount;
    out->sprites_44 = (FtgSprite*)buf;
    buf += spriteCount * 0x14;
    out->texSpriteCount_48 = texSpriteCount;
    out->texSprites_50 = (FtgSprite*)buf;
    return total;
}
// Matched
int AllocFtgSpriteGroups_800228F8(FtgSpriteGroups8* groups8, FtgSpriteGroups9* groups9, FtgSrcObjectHeader* hdr, int heap)
{
    int count;
    int m;
    groups8->count = hdr->counts_0[8];
    count = hdr->counts_0[8];
    if (count)
    {
        groups8->groups = HeapAlloc_8003FC8C(count << 3, heap);
    }
    else
    {
        groups8->groups = 0;
    }
    groups9->count = hdr->counts_0[9];
    m = hdr->counts_0[9];
    count += m;
    if (m)
    {
        groups9->groups = HeapAlloc_8003FC8C(m * 12, heap);
    }
    else
    {
        groups9->groups = 0;
    }
    return count;
}
// Matched
void FreeFtgObject_800229B0(FtgObject* obj, int heap)
{
    FtgPolyF3* a = obj->f3_0.items;
    if (a)
    {
        HeapFree_8003FD18(a, heap);
    }
}
// Matched
void FreeFtgSpriteGroups_800229E0(FtgSpriteGroups8* groups8, FtgSpriteGroups9* groups9, int h)
{
    int i;
    if (groups8->groups != 0)
    {
        for (i = 0; i < groups8->count; i++)
        {
            if (groups8->groups[i].items != 0)
            {
                HeapFree_8003FD18(groups8->groups[i].items, h);
            }
        }
        HeapFree_8003FD18(groups8->groups, h);
    }
    if (groups9->groups != 0)
    {
        for (i = 0; i < groups9->count; i++)
        {
            if (groups9->groups[i].items != 0)
            {
                HeapFree_8003FD18(groups9->groups[i].items, h);
            }
        }
        HeapFree_8003FD18(groups9->groups, h);
    }
}
// Matched
void RelocateTPageClut_80022AE8(unsigned short* tpage, unsigned short* clut, short* reloc)
{
    int x = reloc[0] / 64;
    int y = reloc[1] / 256;
    int tp = y * 16 + x;
    unsigned short clutVal = *clut;
    x = (clutVal & 0x3F) * 16;
    y = (clutVal >> 6) & 0x1FF;
    if (((*tpage >> 7) & 3) == 0)
    {
        x += reloc[2];
        y += reloc[3];
    }
    else
    {
        x += reloc[4];
        y += reloc[5];
    }
    *tpage += tp;
    *clut = y * 64 + (x >> 4);
}
// Matched
void CountFtgSprites_80022B84(unsigned char* cursor, int* sprites, int* texSprites)
{
    int spriteCount;
    int primCount;
    int i;
    int texSpriteCount;
    unsigned char* prim;
    FtgSrcSprites8* sprites8;
    FtgSrcSprites9* sprites9;
    int* counts;
    spriteCount = 0;
    counts = (int*)cursor;
    cursor += 0x28;
    primCount = counts[0] + counts[1] + counts[2] + counts[3] + counts[4] + counts[5] + counts[6] + counts[7] + counts[8] + counts[9];
    texSpriteCount = 0;
    for (i = 0; i < primCount; i++)
    {
        prim = cursor;
        cursor += 4;
        switch (*prim)
        {
        case 1: cursor += 0x3C; break;
        case 0: case 2: cursor += 0x24; break;
        case 3: cursor += 0x40; break;
        case 5: cursor += 0x50; break;
        case 4: case 6: cursor += 0x2C; break;
        case 7: cursor += 0x54; break;
        case 8:
        {
            FtgSrcSprite8* items;
            sprites8 = (FtgSrcSprites8*)cursor;
            items = sprites8->items_4;
            cursor = (unsigned char*)(items + sprites8->count_0);
            spriteCount += sprites8->count_0;
            break;
        }
        case 9:
        {
            FtgSrcSprite9* items;
            sprites9 = (FtgSrcSprites9*)cursor;
            items = sprites9->items_8;
            cursor = (unsigned char*)(items + sprites9->count_0);
            texSpriteCount += sprites9->count_0;
            break;
        }
        }
    }
    *sprites = spriteCount;
    *texSprites = texSpriteCount;
}
// Matched
void MergeFtgSpriteGroups_80022CC4(FtgObject* obj, FtgSpriteGroups8* groups8, FtgSpriteGroups9* groups9, int h)
{
    int j;
    int sprite;
    int k;
    FtgSpriteGroup8* e;
    FtgSpriteGroup9* f;
    if (groups8->count)
    {
        j = 0;
        e = groups8->groups;
        k = 0;
        for (sprite = 0; sprite < obj->spriteCount_40; sprite++)
        {
            if (j >= groups8->groups[k].count)
            {
                k++;
                j = 0;
                e = &groups8->groups[k];
            }
            obj->sprites_44[sprite].p0.x = e->items[j].p0.x;
            obj->sprites_44[sprite].p0.y = e->items[j].p0.y;
            obj->sprites_44[sprite].p0.z = e->items[j].p0.z;
            obj->sprites_44[sprite].p0.uv = 0;
            obj->sprites_44[sprite].p1.x = e->items[j].p1.x;
            obj->sprites_44[sprite].p1.y = e->items[j].p1.y;
            obj->sprites_44[sprite].p1.z = e->items[j].p1.z;
            obj->sprites_44[sprite].p1.uv = 0;
            obj->sprites_44[sprite].c.r = e->items[j].c.r;
            obj->sprites_44[sprite].c.g = e->items[j].c.g;
            obj->sprites_44[sprite].c.b = e->items[j].c.b;
            obj->sprites_44[sprite].c.code = 0;
            j++;
        }
    }
    if (groups9->count)
    {
        int used;  // sprites taken from the current group
        int item;  // index of the next one in it
        used = 0;
        item = 0;
        obj->tpage_4C = groups9->groups->tpage;
        obj->clut_4E = groups9->groups->clut;
        f = groups9->groups;
        k = 0;
        for (sprite = 0; sprite < obj->texSpriteCount_48; sprite++, item++)
        {
            if (used >= groups9->groups[k].count)
            {
                k++;
                item = 0;
                used = 0;
                f = &groups9->groups[k];
            }
            obj->texSprites_50[sprite].p0.x = f->items[item].p0.x;
            obj->texSprites_50[sprite].p0.y = f->items[item].p0.y;
            obj->texSprites_50[sprite].p0.z = f->items[item].p0.z;
            obj->texSprites_50[sprite].p0.uv = 0;
            obj->texSprites_50[sprite].p1.x = f->items[item].p1.x;
            obj->texSprites_50[sprite].p1.y = f->items[item].p1.y;
            obj->texSprites_50[sprite].p1.z = f->items[item].p1.z;
            obj->texSprites_50[sprite].p1.uv = 0;
            obj->texSprites_50[sprite].c.r = f->items[item].c.r;
            obj->texSprites_50[sprite].c.g = f->items[item].c.g;
            obj->texSprites_50[sprite].c.b = f->items[item].c.b;
            obj->texSprites_50[sprite].c.code = f->items[item].c.code;
            obj->texSprites_50[sprite].p1.uv = f->items[item].p1.uv;
            used++;
        }
    }
}
// Matched
int LoadFtgSprites_8002300C(FtgPrimHeader* hdr, FtgSrcSprites8* p_in, FtgSpriteGroups8* groups8, int k, int h)
{
    FtgSrcSprites8* src = p_in;
    int read = 4;
    int i;
    FtgSrcSprite8* items;
    groups8->groups[k].count = src->count_0;
    groups8->groups[k].items = HeapAlloc_8003FC8C(src->count_0 * 20, h);
    items = (FtgSrcSprite8*)((unsigned char*)src + read); // r: bytes read so far
    for (i = 0; i < src->count_0; i++)
    {
        groups8->groups[k].items[i].p0.x = items[i].p0.x;
        groups8->groups[k].items[i].p0.y = items[i].p0.y;
        groups8->groups[k].items[i].p0.z = items[i].p0.z;
        groups8->groups[k].items[i].p0.uv = 0;
        groups8->groups[k].items[i].p1.x = items[i].p1.x;
        groups8->groups[k].items[i].p1.y = items[i].p1.y;
        groups8->groups[k].items[i].p1.z = items[i].p1.z;
        groups8->groups[k].items[i].p1.uv = 0;
        groups8->groups[k].items[i].c.r = items[i].c.r;
        groups8->groups[k].items[i].c.g = items[i].c.g;
        groups8->groups[k].items[i].c.b = items[i].c.b;
        groups8->groups[k].items[i].c.code = 0;
        read += 20;
    }
    return read;
}
// Matched
int LoadFtgTexSprites_8002320C(FtgPrimHeader* hdr, FtgSrcSprites9* p_in, FtgSpriteGroups9* groups9, int k, int h)
{
    FtgSrcSprites9* src = p_in;
    int read;
    int i;
    FtgSrcSprite9* items;
    groups9->groups[k].count = src->count_0;
    groups9->groups[k].items = HeapAlloc_8003FC8C(src->count_0 * 20, h);
    read = 8;
    groups9->groups[k].tpage = src->tpage_4;
    groups9->groups[k].clut = src->clut_6;
    items = (FtgSrcSprite9*)((unsigned char*)src + read); // r: bytes read so far
    for (i = 0; i < src->count_0; i++)
    {
        groups9->groups[k].items[i].p0.x = items[i].p0.x;
        groups9->groups[k].items[i].p0.y = items[i].p0.y;
        groups9->groups[k].items[i].p0.z = items[i].p0.z;
        groups9->groups[k].items[i].p0.uv = 0;
        groups9->groups[k].items[i].p1.x = items[i].p1.x;
        groups9->groups[k].items[i].p1.y = items[i].p1.y;
        groups9->groups[k].items[i].p1.z = items[i].p1.z;
        groups9->groups[k].items[i].p1.uv = 0;
        groups9->groups[k].items[i].c.r = items[i].c.r;
        groups9->groups[k].items[i].c.g = items[i].c.g;
        groups9->groups[k].items[i].c.b = items[i].c.b;
        groups9->groups[k].items[i].c.code = hdr->flags_3;
        groups9->groups[k].items[i].p1.uv = items[i].p1.u + (items[i].p1.v << 8);
        read += 20;
    }
    return read;
}
// Matched
void RelocFtgTexSprites_80023460(FtgSrcSprites9* sprites, int reloc)
{
    RelocateTPageClut_80022AE8(&sprites->tpage_4, &sprites->clut_6, reloc);
}
// Matched
int LoadFtgPolyF3_8002348C(FtgPrimHeader* hdr, FtgPolyF3* src, FtgObject* obj, int idx)
{
    if (hdr->flags_3 & 2)
    {
        SetSemiTrans(&obj->f3_0.items[idx], 1);
    }
    CopyFtgPolyF3_80023514(&obj->f3_0, src, hdr->flags_3, idx);
    return 0x24;
}
// Matched
void CopyFtgPolyF3_80023514(FtgPolyF3List* list, FtgPolyF3* src, int code, int idx)
{
    list->items[idx].c.r = src->c.r;
    list->items[idx].c.g = src->c.g;
    list->items[idx].c.b = src->c.b;
    list->items[idx].c.code = code;
    list->items[idx].v[0].x = src->v[0].x;
    list->items[idx].v[0].y = src->v[0].y;
    list->items[idx].v[0].z = src->v[0].z;
    list->items[idx].v[1].x = src->v[1].x;
    list->items[idx].v[1].y = src->v[1].y;
    list->items[idx].v[1].z = src->v[1].z;
    list->items[idx].v[2].x = src->v[2].x;
    list->items[idx].v[2].y = src->v[2].y;
    list->items[idx].v[2].z = src->v[2].z;
    list->items[idx].n.x = src->n.x;
    list->items[idx].n.y = src->n.y;
    list->items[idx].n.z = src->n.z;
}
// Matched
int LoadFtgPolyG3_80023624(FtgPrimHeader* hdr, FtgSrcPolyG3* src, FtgObject* obj, int idx)
{
    if (hdr->flags_3 & 2)
    {
        SetSemiTrans(&obj->g3_8.items[idx], 1);
    }
    CopyFtgPolyG3_800236AC(&obj->g3_8, src, hdr->flags_3, idx);
    return 0x3C;
}
// Matched
void CopyFtgPolyG3_800236AC(FtgPolyG3List* list, FtgSrcPolyG3* src, int code, int idx)
{
    list->items[idx].c[0].r = src->c[0].r;
    list->items[idx].c[0].g = src->c[0].g;
    list->items[idx].c[0].b = src->c[0].b;
    list->items[idx].c[0].code = code;
    list->items[idx].c[1].r = src->c[1].r;
    list->items[idx].c[1].g = src->c[1].g;
    list->items[idx].c[1].b = src->c[1].b;
    list->items[idx].c[0].code = code;
    list->items[idx].c[2].r = src->c[2].r;
    list->items[idx].c[2].g = src->c[2].g;
    list->items[idx].c[2].b = src->c[2].b;
    list->items[idx].c[0].code = code;
    list->items[idx].v[0].x = src->p[0].v.x;
    list->items[idx].v[0].y = src->p[0].v.y;
    list->items[idx].v[0].z = src->p[0].v.z;
    list->items[idx].v[1].x = src->p[1].v.x;
    list->items[idx].v[1].y = src->p[1].v.y;
    list->items[idx].v[1].z = src->p[1].v.z;
    list->items[idx].v[2].x = src->p[2].v.x;
    list->items[idx].v[2].y = src->p[2].v.y;
    list->items[idx].v[2].z = src->p[2].v.z;
    list->items[idx].n[0].x = src->p[0].n.x;
    list->items[idx].n[0].y = src->p[0].n.y;
    list->items[idx].n[0].z = src->p[0].n.z;
    list->items[idx].n[1].x = src->p[1].n.x;
    list->items[idx].n[1].y = src->p[1].n.y;
    list->items[idx].n[1].z = src->p[1].n.z;
    list->items[idx].n[2].x = src->p[2].n.x;
    list->items[idx].n[2].y = src->p[2].n.y;
    list->items[idx].n[2].z = src->p[2].n.z;
    list->items[idx].c[0].code = code;
}
// Matched
int LoadFtgPolyFT3_800238AC(FtgPrimHeader* hdr, FtgSrcPolyFT3* src, FtgObject* obj, int idx)
{
    if (hdr->flags_3 & 2)
    {
        SetSemiTrans(&obj->ft3_10.items[idx], 1);
    }
    CopyFtgPolyFT3_80023934(&obj->ft3_10, src, hdr->flags_3, idx);
    return 0x24;
}
// Matched
void CopyFtgPolyFT3_80023934(FtgPolyFT3List* list, FtgSrcPolyFT3* src, int code, int idx)
{
    list->items[idx].tpage = src->tex.tpage;
    list->items[idx].clut = src->tex.clut;
    list->items[idx].u0 = src->v[0].u;
    list->items[idx].v0 = src->v[0].v;
    list->items[idx].v[0].uv = list->items[idx].u0 + (list->items[idx].v0 << 8);
    list->items[idx].u1 = src->v[1].u;
    list->items[idx].v1 = src->v[1].v;
    list->items[idx].v[1].uv = list->items[idx].u1 + (list->items[idx].v1 << 8);
    list->items[idx].u2 = src->v[2].u;
    list->items[idx].v2 = src->v[2].v;
    list->items[idx].v[2].uv = list->items[idx].u2 + (list->items[idx].v2 << 8);
    list->items[idx].c.r = 0x80;
    list->items[idx].c.g = 0x80;
    list->items[idx].c.b = 0x80;
    list->items[idx].c.code = code;
    list->items[idx].v[0].x = src->v[0].x;
    list->items[idx].v[0].y = src->v[0].y;
    list->items[idx].v[0].z = src->v[0].z;
    list->items[idx].v[1].x = src->v[1].x;
    list->items[idx].v[1].y = src->v[1].y;
    list->items[idx].v[1].z = src->v[1].z;
    list->items[idx].v[2].x = src->v[2].x;
    list->items[idx].v[2].y = src->v[2].y;
    list->items[idx].v[2].z = src->v[2].z;
    list->items[idx].n.x = src->n.x;
    list->items[idx].n.y = src->n.y;
    list->items[idx].n.z = src->n.z;
}
// Matched
void RelocFtgPolyFT3_80023B24(FtgSrcPolyFT3* poly, int reloc)
{
    RelocateTPageClut_80022AE8(&poly->tex.tpage, &poly->tex.clut, reloc);
}
// Matched
int LoadFtgPolyGT3_80023B48(FtgPrimHeader* hdr, FtgSrcPolyGT3* src, FtgObject* obj, int idx)
{
    if (hdr->flags_3 & 2)
    {
        SetSemiTrans(&obj->gt3_18.items[idx], 1);
    }
    CopyFtgPolyGT3_80023BD0(&obj->gt3_18, src, hdr->flags_3, idx);
    return 0x40;
}
// Matched
void CopyFtgPolyGT3_80023BD0(FtgPolyGT3List* list, FtgSrcPolyGT3* src, int code, int idx)
{
    list->items[idx].tpage = src->tex.tpage;
    list->items[idx].clut = src->tex.clut;
    list->items[idx].u0 = src->p[0].v.u;
    list->items[idx].v0 = src->p[0].v.v;
    list->items[idx].v[0].uv = list->items[idx].u0 + (list->items[idx].v0 << 8);
    list->items[idx].u1 = src->p[1].v.u;
    list->items[idx].v1 = src->p[1].v.v;
    list->items[idx].v[1].uv = list->items[idx].u1 + (list->items[idx].v1 << 8);
    list->items[idx].u2 = src->p[2].v.u;
    list->items[idx].v2 = src->p[2].v.v;
    list->items[idx].v[2].uv = list->items[idx].u2 + (list->items[idx].v2 << 8);
    list->items[idx].c[0].code = code;
    list->items[idx].c[0].r = src->c[0].r;
    list->items[idx].c[0].g = src->c[0].g;
    list->items[idx].c[0].b = src->c[0].b;
    list->items[idx].c[1].r = src->c[1].r;
    list->items[idx].c[1].g = src->c[1].g;
    list->items[idx].c[1].b = src->c[1].b;
    list->items[idx].c[2].r = src->c[2].r;
    list->items[idx].c[2].g = src->c[2].g;
    list->items[idx].c[2].b = src->c[2].b;
    list->items[idx].v[0].x = src->p[0].v.x;
    list->items[idx].v[0].y = src->p[0].v.y;
    list->items[idx].v[0].z = src->p[0].v.z;
    list->items[idx].v[1].x = src->p[1].v.x;
    list->items[idx].v[1].y = src->p[1].v.y;
    list->items[idx].v[1].z = src->p[1].v.z;
    list->items[idx].v[2].x = src->p[2].v.x;
    list->items[idx].v[2].y = src->p[2].v.y;
    list->items[idx].v[2].z = src->p[2].v.z;
    list->items[idx].n[0].x = src->p[0].n.x;
    list->items[idx].n[0].y = src->p[0].n.y;
    list->items[idx].n[0].z = src->p[0].n.z;
    list->items[idx].n[1].x = src->p[1].n.x;
    list->items[idx].n[1].y = src->p[1].n.y;
    list->items[idx].n[1].z = src->p[1].n.z;
    list->items[idx].n[2].x = src->p[2].n.x;
    list->items[idx].n[2].y = src->p[2].n.y;
    list->items[idx].n[2].z = src->p[2].n.z;
}
// Matched
void RelocFtgPolyGT3_80023E80(FtgSrcPolyGT3* poly, int reloc)
{
    RelocateTPageClut_80022AE8(&poly->tex.tpage, &poly->tex.clut, reloc);
}
// Matched
int LoadFtgPolyF4_80023EA4(FtgPrimHeader* hdr, FtgPolyF4* src, FtgObject* obj, int idx)
{
    if (hdr->flags_3 & 2)
    {
        SetSemiTrans(&obj->f4_20.items[idx], 1);
    }
    CopyFtgPolyF4_80023F34(&obj->f4_20, src, hdr->flags_3, idx);
    return 0x2C;
}
// Matched
void CopyFtgPolyF4_80023F34(FtgPolyF4List* list, FtgPolyF4* src, int code, int idx)
{
    list->items[idx].c.r = src->c.r;
    list->items[idx].c.g = src->c.g;
    list->items[idx].c.b = src->c.b;
    list->items[idx].c.code = code;
    list->items[idx].v[0].x = src->v[0].x;
    list->items[idx].v[0].y = src->v[0].y;
    list->items[idx].v[0].z = src->v[0].z;
    list->items[idx].v[1].x = src->v[1].x;
    list->items[idx].v[1].y = src->v[1].y;
    list->items[idx].v[1].z = src->v[1].z;
    list->items[idx].v[2].x = src->v[2].x;
    list->items[idx].v[2].y = src->v[2].y;
    list->items[idx].v[2].z = src->v[2].z;
    list->items[idx].v[3].x = src->v[3].x;
    list->items[idx].v[3].y = src->v[3].y;
    list->items[idx].v[3].z = src->v[3].z;
    list->items[idx].n.x = src->n.x;
    list->items[idx].n.y = src->n.y;
    list->items[idx].n.z = src->n.z;
}
// Matched
int LoadFtgPolyG4_8002407C(FtgPrimHeader* hdr, FtgSrcPolyG4* src, FtgObject* obj, int idx)
{
    if (hdr->flags_3 & 2)
    {
        SetSemiTrans(&obj->g4_28.items[idx], 1);
    }
    CopyFtgPolyG4_80024104(&obj->g4_28, src, hdr->flags_3, idx);
    return 0x50;
}
// Matched
void CopyFtgPolyG4_80024104(FtgPolyG4List* list, FtgSrcPolyG4* src, int code, int idx)
{
    list->items[idx].c[0].r = src->c[0].r;
    list->items[idx].c[0].g = src->c[0].g;
    list->items[idx].c[0].b = src->c[0].b;
    list->items[idx].c[0].code = code;
    list->items[idx].c[1].r = src->c[1].r;
    list->items[idx].c[1].g = src->c[1].g;
    list->items[idx].c[1].b = src->c[1].b;
    list->items[idx].c[0].code = code;
    list->items[idx].c[2].r = src->c[2].r;
    list->items[idx].c[2].g = src->c[2].g;
    list->items[idx].c[2].b = src->c[2].b;
    list->items[idx].c[0].code = code;
    list->items[idx].c[3].r = src->c[3].r;
    list->items[idx].c[3].g = src->c[3].g;
    list->items[idx].c[3].b = src->c[3].b;
    list->items[idx].c[0].code = code;
    list->items[idx].v[0].x = src->p[0].v.x;
    list->items[idx].v[0].y = src->p[0].v.y;
    list->items[idx].v[0].z = src->p[0].v.z;
    list->items[idx].v[1].x = src->p[1].v.x;
    list->items[idx].v[1].y = src->p[1].v.y;
    list->items[idx].v[1].z = src->p[1].v.z;
    list->items[idx].v[2].x = src->p[2].v.x;
    list->items[idx].v[2].y = src->p[2].v.y;
    list->items[idx].v[2].z = src->p[2].v.z;
    list->items[idx].v[3].x = src->p[3].v.x;
    list->items[idx].v[3].y = src->p[3].v.y;
    list->items[idx].v[3].z = src->p[3].v.z;
    list->items[idx].n[0].x = src->p[0].n.x;
    list->items[idx].n[0].y = src->p[0].n.y;
    list->items[idx].n[0].z = src->p[0].n.z;
    list->items[idx].n[1].x = src->p[1].n.x;
    list->items[idx].n[1].y = src->p[1].n.y;
    list->items[idx].n[1].z = src->p[1].n.z;
    list->items[idx].n[2].x = src->p[2].n.x;
    list->items[idx].n[2].y = src->p[2].n.y;
    list->items[idx].n[2].z = src->p[2].n.z;
    list->items[idx].n[3].x = src->p[3].n.x;
    list->items[idx].n[3].y = src->p[3].n.y;
    list->items[idx].n[3].z = src->p[3].n.z;
}
// Matched
int LoadFtgPolyFT4_80024394(FtgPrimHeader* hdr, FtgSrcPolyFT4* src, FtgObject* obj, int idx)
{
    if (hdr->flags_3 & 2)
    {
        SetSemiTrans(&obj->ft4_30.items[idx], 1);
    }
    CopyFtgPolyFT4_8002441C(&obj->ft4_30, src, hdr->flags_3, idx);
    return 0x2C;
}
// Matched
void CopyFtgPolyFT4_8002441C(FtgPolyFT4List* list, FtgSrcPolyFT4* src, int code, int idx)
{
    list->items[idx].tpage = src->tex.tpage;
    list->items[idx].clut = src->tex.clut;
    list->items[idx].u0 = src->v[0].u;
    list->items[idx].v0 = src->v[0].v;
    list->items[idx].v[0].uv = list->items[idx].u0 + (list->items[idx].v0 << 8);
    list->items[idx].u1 = src->v[1].u;
    list->items[idx].v1 = src->v[1].v;
    list->items[idx].v[1].uv = list->items[idx].u1 + (list->items[idx].v1 << 8);
    list->items[idx].u2 = src->v[2].u;
    list->items[idx].v2 = src->v[2].v;
    list->items[idx].v[2].uv = list->items[idx].u2 + (list->items[idx].v2 << 8);
    list->items[idx].u3 = src->v[3].u;
    list->items[idx].v3 = src->v[3].v;
    list->items[idx].v[3].uv = list->items[idx].u3 + (list->items[idx].v3 << 8);
    list->items[idx].c.r = 0x80;
    list->items[idx].c.g = 0x80;
    list->items[idx].c.b = 0x80;
    list->items[idx].c.code = code;
    list->items[idx].v[0].x = src->v[0].x;
    list->items[idx].v[0].y = src->v[0].y;
    list->items[idx].v[0].z = src->v[0].z;
    list->items[idx].v[1].x = src->v[1].x;
    list->items[idx].v[1].y = src->v[1].y;
    list->items[idx].v[1].z = src->v[1].z;
    list->items[idx].v[2].x = src->v[2].x;
    list->items[idx].v[2].y = src->v[2].y;
    list->items[idx].v[2].z = src->v[2].z;
    list->items[idx].v[3].x = src->v[3].x;
    list->items[idx].v[3].y = src->v[3].y;
    list->items[idx].v[3].z = src->v[3].z;
    list->items[idx].n.x = src->n.x;
    list->items[idx].n.y = src->n.y;
    list->items[idx].n.z = src->n.z;
}
// Matched
void RelocFtgPolyFT4_8002467C(FtgSrcPolyFT4* poly, int reloc)
{
    RelocateTPageClut_80022AE8(&poly->tex.tpage, &poly->tex.clut, reloc);
}
// Matched
int LoadFtgPolyGT4_800246A0(FtgPrimHeader* hdr, FtgSrcPolyGT4* src, FtgObject* obj, int idx)
{
    if (hdr->flags_3 & 2)
    {
        SetSemiTrans(&obj->gt4_38.items[idx], 1);
    }
    CopyFtgPolyGT4_80024730(&obj->gt4_38, src, hdr->flags_3, idx);
    return 0x54;
}
// Matched
void CopyFtgPolyGT4_80024730(FtgPolyGT4List* list, FtgSrcPolyGT4* src, int code, int idx)
{
    list->items[idx].tpage = src->tex.tpage;
    list->items[idx].clut = src->tex.clut;
    list->items[idx].u0 = src->p[0].v.u;
    list->items[idx].v0 = src->p[0].v.v;
    list->items[idx].v[0].uv = list->items[idx].u0 + (list->items[idx].v0 << 8);
    list->items[idx].u1 = src->p[1].v.u;
    list->items[idx].v1 = src->p[1].v.v;
    list->items[idx].v[1].uv = list->items[idx].u1 + (list->items[idx].v1 << 8);
    list->items[idx].u2 = src->p[2].v.u;
    list->items[idx].v2 = src->p[2].v.v;
    list->items[idx].v[2].uv = list->items[idx].u2 + (list->items[idx].v2 << 8);
    list->items[idx].u3 = src->p[3].v.u;
    list->items[idx].v3 = src->p[3].v.v;
    list->items[idx].v[3].uv = list->items[idx].u3 + (list->items[idx].v3 << 8);
    list->items[idx].c[0].code = code;
    list->items[idx].c[0].r = src->c[0].r;
    list->items[idx].c[0].g = src->c[0].g;
    list->items[idx].c[0].b = src->c[0].b;
    list->items[idx].c[1].r = src->c[1].r;
    list->items[idx].c[1].g = src->c[1].g;
    list->items[idx].c[1].b = src->c[1].b;
    list->items[idx].c[2].r = src->c[2].r;
    list->items[idx].c[2].g = src->c[2].g;
    list->items[idx].c[2].b = src->c[2].b;
    list->items[idx].c[3].r = src->c[3].r;
    list->items[idx].c[3].g = src->c[3].g;
    list->items[idx].c[3].b = src->c[3].b;
    list->items[idx].v[0].x = src->p[0].v.x;
    list->items[idx].v[0].y = src->p[0].v.y;
    list->items[idx].v[0].z = src->p[0].v.z;
    list->items[idx].v[1].x = src->p[1].v.x;
    list->items[idx].v[1].y = src->p[1].v.y;
    list->items[idx].v[1].z = src->p[1].v.z;
    list->items[idx].v[2].x = src->p[2].v.x;
    list->items[idx].v[2].y = src->p[2].v.y;
    list->items[idx].v[2].z = src->p[2].v.z;
    list->items[idx].v[3].x = src->p[3].v.x;
    list->items[idx].v[3].y = src->p[3].v.y;
    list->items[idx].v[3].z = src->p[3].v.z;
    list->items[idx].n[0].x = src->p[0].n.x;
    list->items[idx].n[0].y = src->p[0].n.y;
    list->items[idx].n[0].z = src->p[0].n.z;
    list->items[idx].n[1].x = src->p[1].n.x;
    list->items[idx].n[1].y = src->p[1].n.y;
    list->items[idx].n[1].z = src->p[1].n.z;
    list->items[idx].n[2].x = src->p[2].n.x;
    list->items[idx].n[2].y = src->p[2].n.y;
    list->items[idx].n[2].z = src->p[2].n.z;
    list->items[idx].n[3].x = src->p[3].n.x;
    list->items[idx].n[3].y = src->p[3].n.y;
    list->items[idx].n[3].z = src->p[3].n.z;
}
// Matched
void RelocFtgPolyGT4_80024AB8(FtgSrcPolyGT4* poly, int reloc)
{
    RelocateTPageClut_80022AE8(&poly->tex.tpage, &poly->tex.clut, reloc);
}
// Matched
void InitModelList_80024ADC(ModelList** out, ModelVramSlot* vram, int heap)
{
    ModelList* l;
    int i;
    l = *out = HeapAlloc_8003FC8C(0x10, heap);
    l->count_0 = CountModelVramSlots_80026600(vram);
    l->heap_4 = heap;
    l->items_8 = HeapAlloc_8003FC8C(l->count_0 * 0x70, heap);
    l->vram_C = vram;
    for (i = 0; i < l->count_0; i++)
    {
        l->items_8[i].list_0 = l;
        l->items_8[i].slot_30 = i;
        ClearModel_800266CC(&l->items_8[i]);
    }
}
// Matched
void FreeModelList_80024BB0(ModelList** list)
{
    ModelList* l = *list;
    int i;
    for (i = 0; i < l->count_0; i++)
    {
        FreeModel_80024C48(&l->items_8[i]);
    }
    HeapFree_8003FD18(l->items_8, l->heap_4);
    HeapFree_8003FD18(l, l->heap_4);
    *list = 0;
}
// Matched
void FreeModel_80024C48(Model* model)
{
    int h;
    FreeModelAltFtgs_80025AB0(model);
    ApplyModelFtgSwaps_80025C38(model, 1);
    h = model->list_0->heap_4;
    if (model->animLoaded_44 != 0)
    {
        HeapFree_8003FD18(model->animLoaded_44, h);
    }
    if (model->header_4C != 0)
    {
        HeapFree_8003FD18(model->header_4C, h);
    }
    if (model->ftg_50 != 0)
    {
        FreeFtgObjects_80021784(&model->ftg_50, model->ftgCount_3C, h);
    }
    if (model->anims_54 != 0)
    {
        FreeModelAnims_8002679C(&model->anims_54, model->animCount_3E, h);
    }
    if (model->animSet_58 != 0)
    {
        HeapFree_8003FD18(model->animSet_58, h);
    }
    if (model->mats_5C.items_4 != 0)
    {
        FreeFtgMatList_80021E24(&model->mats_5C, h);
    }
    if (model->saved_64 != 0)
    {
        HeapFree_8003FD18(model->saved_64, h);
    }
    if (model->ftg2_68 != 0)
    {
        FreeFtgObjects_80021784(&model->ftg2_68, model->ftg2Count_42, h);
    }
    if (model->swaps_6C != 0)
    {
        HeapFree_8003FD18(model->swaps_6C, h);
    }
    ClearModel_800266CC(model);
}
// Matched
Model* AcquireModel_80024D70(ModelList* list, unsigned int id)
{
    int i = FindModelIndex_80026630(list, id);
    if (i >= 0)
    {
        Model* model = &list->items_8[i];
        model->refs_3A++;
        return model;
    }
    return 0;
}
// Matched
int AreFileRequestsDone_80024DC4(Model* model)
{
    int i;
    i = 0;
    while (i < model->requestCount_4)
    {
        if (GetFileRequestStatus_8003BE30(model->requests_8[i]) != 0)
        {
            return 0;
        }
        i++;
    }
    model->requestCount_4 = 0;
    return 1;
}
// Matched
void* GetModelActorAnims_80024E38(Model* model)
{
    char* result = 0;
    ModelHeaderData* hdr = model->header_4C;
    if (hdr && hdr->offset_0)
    {
        result = (char*)hdr + hdr->offset_0 + 4;
    }
    return result;
}
// Matched
void* GetModelEffectTable_80024E64(Model* model)
{
    char* result = 0;
    ModelHeaderData* hdr = model->header_4C;
    if (hdr && hdr->offset_4)
    {
        result = (char*)hdr + hdr->offset_4;
    }
    return result;
}
// Matched
void* GetModelBaseScale_80024E90(Model* model, int record)
{
    char* rec = GetModelHeaderRecord_80024FA8(model, record);
    if (rec)
    {
        rec += ((ModelHeaderRecord*)rec)->offsets_0[0];
    }
    return rec;
}
// Matched
void* GetModelBoneScale_80024EC8(Model* model, int record)
{
    char* rec = GetModelHeaderRecord_80024FA8(model, record);
    if (rec)
    {
        rec += ((ModelHeaderRecord*)rec)->offsets_0[1];
    }
    return rec;
}
// Matched
void* GetModelBoneGroupLevels_80024F00(Model* model, int record)
{
    char* rec = GetModelHeaderRecord_80024FA8(model, record);
    if (rec)
    {
        rec += ((ModelHeaderRecord*)rec)->offsets_0[2];
    }
    return rec;
}
// Matched
void* GetModelBoneGroupFlags_80024F38(Model* model, int record)
{
    char* rec = GetModelHeaderRecord_80024FA8(model, record);
    if (rec)
    {
        rec += ((ModelHeaderRecord*)rec)->offsets_0[3];
    }
    return rec;
}
// Matched
void* GetModelFtgWeights_80024F70(Model* model, int record)
{
    char* rec = GetModelHeaderRecord_80024FA8(model, record);
    if (rec)
    {
        rec += ((ModelHeaderRecord*)rec)->offsets_0[4];
    }
    return rec;
}
// Matched
char* GetModelHeaderRecord_80024FA8(Model* model, int record)
{
    char* hdr = (char*)model->header_4C;
    char* rec = 0;
    int i;
    if (hdr)
    {
        int off = ((ModelHeaderData*)hdr)->records_8;
        if (off)
        {
            hdr += off;
            hdr += 8;
            for (i = 0; i < record; i++)
            {
                hdr += ((ModelHeaderRecord*)hdr)->size_14;
            }
            rec = hdr;
        }
    }
    return rec;
}
// Matched
void SaveModelFtgs_80024FFC(Model* model, int* ids)
{
    int count;
    int heap;
    for (count = 0; ids[count] >= 0; count++)
    {
    }
    heap = model->list_0->heap_4;
    model->savedCount_40 = count;
    model->saved_64 = HeapAlloc_8003FC8C(count * sizeof(ModelSavedFtg), heap);
    count--;
    while (count >= 0)
    {
        int id = ids[count];
        model->saved_64[count].id_0 = id;
        model->saved_64[count].ftg_4 = model->ftg_50[id];
        count--;
    }
}
// Matched
void GetSavedModelFtg_8002512C(unsigned int* out, Model* model, int id)
{
    int i;
    for (i = 0; i < model->savedCount_40; i++)
    {
        ModelSavedFtg* e = (ModelSavedFtg*)(i * 0x58 + (int)model->saved_64); // integer sum: the original adds the base second
        if (id == e->id_0)
        {
            MemCopy_800403E8(out, &e->ftg_4, 0x54);
            break;
        }
    }
}
// Matched
void GetModelFtg_800251A0(void* dst, Model* src, int unused, int idx)
{
    MemCopy_800403E8(dst, &src->ftg_50[idx], sizeof(FtgObject));
}
// Matched
void EmptyCallback_800251DC(void)
{
}
// Matched
ModelDesc* GetModelDesc_800251E4(int idx)
{
    return modelDescs_800824CC[idx];
}
// Matched
int LoadModel_80025200(ModelList* list, int id, int texSel, int animMode, int flag)
{
    ModelLoadParams params;
    FileRequestDesc req;
    int separateHeader = 1;
    int i;
    ModelDesc* desc;
    Model* model;
    ModelVramSlot* vram;
    int offset;
    int size;
    i = FindModelIndex_80026630(list, id);
    if (i >= 0)
    {
        return AreFileRequestsDone_80024DC4(&list->items_8[i]) == 0;
    }
    i = FindFreeModelIndex_8002667C(list);
    if (i >= 0)
    {
        desc = modelDescs_800824CC[id];
        model = &list->items_8[i];
        vram = list->vram_C + i;
        InitModelLoadParams_80025ED0(&params);
        if (texSel != -1)
        {
            params.flags_0 |= 3;
        }
        params.flags_0 |= 0xC;
        size = 0;
        params.model_14 = model;
        params.vram_18 = vram;
        params.desc_4 = desc;
        params.sel_8 = texSel;
        params.mode_C = animMode;
        if (texSel != -1)
        {
            separateHeader = 0;
            size += desc->header_2.size;
            size += desc->tex_6.size;
            offset = desc->header_2.offset;
        }
        else
        {
            offset = desc->ftg_A.offset;
        }
        size += desc->ftg_A.size;
        size += desc->anims_E.size;
        req.fileId_4 = desc->fileId_0;
        req.flags_0 = 0x68;
        if (flag == 1)
        {
            req.flags_0 = 0x6C;
        }
        else
        {
            req.flags_0 = 0x69;
        }
        req.offset_8 = offset;
        req.size_C = size;
        req.dest_10 = 0;
        req.params_14 = &params;
        req.paramsSize_18 = 0x3C;
        req.callback_1C = OnModelFileLoaded_80025D7C;
        AddFileRequest_80025D00(model, &req);
        if (separateHeader != 0)
        {
            InitModelLoadParams_80025ED0(&params);
            params.flags_0 = 1;
            params.model_14 = model;
            params.desc_4 = desc;
            req.fileId_4 = desc->fileId_0;
            req.flags_0 = 0x68;
            if (flag == 1)
            {
                req.flags_0 = 0x6C;
            }
            else
            {
                req.flags_0 = 0x69;
            }
            req.offset_8 = desc->header_2.offset;
            req.size_C = desc->header_2.size;
            req.params_14 = &params;
            req.paramsSize_18 = 0x3C;
            req.dest_10 = 0;
            req.callback_1C = OnModelFileLoaded_80025D7C;
            AddFileRequest_80025D00(model, &req);
        }
        model->id_38 = id;
        return 1;
    }
    return 2;
}
// Matched
int LoadModelAnim_80025440(Model* model, int idx, int flag)
{
    ModelLoadParams b;
    FileRequestDesc c;
    unsigned short* e;
    unsigned short* sectors;
    int offset;
    int size;
    int k;
    int entry; // index of the anim's (offset, size) pair in the descriptor
    unsigned char* f = model->animLoaded_44 + idx;
    if (*f == 0)
    {
        e = (unsigned short*)modelDescs_800824CC[model->id_38];
        k = idx * 2 + 10;
        entry = e[9];
        entry += k;
        sectors = (unsigned short*)(entry * 2 + (int)e);
        offset = sectors[0];
        size = sectors[1];
        *f = 1;
        InitModelLoadParams_80025ED0(&b);
        b.flags_0 = 0x10;
        b.model_14 = model;
        b.desc_4 = (ModelDesc*)e;
        b.animIdx_10 = idx;
        c.flags_0 = 0x68;
        if (flag != 0)
        {
            c.flags_0 = 0x6C;
        }
        else
        {
            c.flags_0 = 0x69;
        }
        c.fileId_4 = e[0];
        c.offset_8 = offset;
        c.size_C = size;
        c.dest_10 = 0;
        c.params_14 = &b;
        c.paramsSize_18 = 0x3C;
        c.callback_1C = OnModelFileLoaded_80025D7C;
        AddFileRequest_80025D00(model, &c);
        return 1;
    }
    return AreFileRequestsDone_80024DC4(model) == 0;
}
// Matched
void FreeModelAnim_8002556C(Model* model, int idx)
{
    if (((char*)model->animLoaded_44)[idx])
    {
        FreeModelAnimData_800269C4(model->anims_54, model->animCount_3E, idx, model->list_0->heap_4);
        model->animLoaded_44[idx] = 0;
    }
}
// Matched
int IsModelAnimLoaded_800255D8(Model* model, int idx)
{
    return ((char*)model->animLoaded_44)[idx] != 0;
}
// Matched
int LoadModelListTextures_800255F0(ModelList* list, int id, int sel)
{
    ModelLoadParams params;
    FileRequestDesc req;
    Model* model = list->items_8;
    ModelVramSlot* vram = list->vram_C;
    ModelDesc* desc = modelDescs_800824CC[id];
    InitModelLoadParams_80025ED0(&params);
    params.flags_0 = 2;
    params.sel_8 = sel;
    req.flags_0 = 0x69;
    params.model_14 = model;
    params.vram_18 = vram;
    params.desc_4 = desc;
    req.fileId_4 = desc->fileId_0;
    req.offset_8 = desc->tex_6.offset;
    req.size_C = desc->tex_6.size;
    req.dest_10 = 0;
    req.params_14 = &params;
    req.paramsSize_18 = 0x3C;
    req.callback_1C = OnModelFileLoaded_80025D7C;
    AddFileRequest_80025D00(model, &req);
    return 1;
}
// Matched
int LoadAllModelAnims_800256B8(ModelList* list, int id)
{
    ModelLoadParams params;
    FileRequestDesc req;
    Model* model = &list->items_8[FindModelIndex_80026630(list, id)];
    ModelDesc* desc = modelDescs_800824CC[model->id_38];
    InitModelLoadParams_80025ED0(&params);
    params.flags_0 = 8;
    params.model_14 = model;
    params.mode_C = 3;
    params.desc_4 = desc;
    req.flags_0 = 0x69;
    req.fileId_4 = desc->fileId_0;
    req.offset_8 = desc->anims_E.offset;
    req.size_C = desc->anims_E.size;
    req.dest_10 = 0;
    req.params_14 = &params;
    req.paramsSize_18 = 0x3C;
    req.callback_1C = OnModelFileLoaded_80025D7C;
    AddFileRequest_80025D00(model, &req);
    return 1;
}
// Matched
int LoadModelAnimSet_80025780(Model* model, int idx, int flag)
{
    ModelLoadParams params;
    FileRequestDesc req;
    ModelDesc* desc;
    char* sets;
    int offset;
    int size;
    FreeModelAnimSet_80025884(model);
    desc = modelDescs_800824CC[model->id_38];
    sets = (char*)desc + (desc->animCount_12 * 6 + 0x14);
    offset = ((unsigned short*)sets)[idx * 2 + 1];
    size = ((unsigned short*)sets)[idx * 2 + 2];
    InitModelLoadParams_80025ED0(&params);
    params.flags_0 = 0x20;
    params.model_14 = model;
    params.desc_4 = desc;
    req.flags_0 = 0x68;
    if (flag != 0)
    {
        req.flags_0 = 0x6C;
    }
    else
    {
        req.flags_0 = 0x69;
    }
    req.fileId_4 = desc->fileId_0;
    req.offset_8 = offset;
    req.size_C = size;
    req.dest_10 = 0;
    req.params_14 = &params;
    req.paramsSize_18 = 0x3C;
    req.callback_1C = OnModelFileLoaded_80025D7C;
    AddFileRequest_80025D00(model, &req);
    return 1;
}
// Matched
void FreeModelAnimSet_80025884(Model* model)
{
    int* list = model->animSet_58;
    if (list)
    {
        int heap = model->list_0->heap_4;
        int count = list[0];
        int i;
        for (i = 0; i < count; i++)
        {
            int id = model->animSet_58[i + 1];
            if (id >= 0)
            {
                FreeModelAnim_8002556C(model, id);
            }
        }
        HeapFree_8003FD18(model->animSet_58, heap);
        model->animSet_58 = 0;
    }
}
// Matched
int IsAnimInModelAnimSet_80025924(Model* model, int id)
{
    int* list = model->animSet_58;
    int i;
    int count;
    if (list != 0)
    {
        count = list[0];
        for (i = 0; i < count; i++)
        {
            if (id == list[i + 1])
            {
                return 1;
            }
        }
    }
    return 0;
}
// Matched
int LoadModelAltFtgs_80025974(Model* model, int idx, int flag)
{
    ModelLoadParams params;
    FileRequestDesc req;
    ModelDesc* desc;
    char* sets;
    int offset;
    int size;
    ModelList* list;
    FreeModelAltFtgs_80025AB0(model);
    desc = modelDescs_800824CC[model->id_38];
    sets = (char*)desc + (desc->animCount_12 * 6 + 0x14);
    sets += *(unsigned short*)sets * 4 + 2;
    list = model->list_0;
    offset = ((unsigned short*)sets)[idx * 2 + 1];
    size = ((unsigned short*)sets)[idx * 2 + 2];
    InitModelLoadParams_80025ED0(&params);
    params.flags_0 = 0x40;
    params.model_14 = model;
    params.vram_18 = list->vram_C + model->slot_30;
    params.sel_8 = model->texSel_34;
    params.desc_4 = desc;
    req.flags_0 = 0x68;
    if (flag != 0)
    {
        req.flags_0 = 0x6C;
    }
    else
    {
        req.flags_0 = 0x69;
    }
    req.fileId_4 = desc->fileId_0;
    req.offset_8 = offset;
    req.size_C = size;
    req.dest_10 = 0;
    req.params_14 = &params;
    req.paramsSize_18 = 0x3C;
    req.callback_1C = OnModelFileLoaded_80025D7C;
    AddFileRequest_80025D00(model, &req);
    return 1;
}
// Matched
void FreeModelAltFtgs_80025AB0(Model* model)
{
    int h = model->list_0->heap_4;
    if (model->ftg2_68)
    {
        FreeFtgObjects_80021784(&model->ftg2_68, model->ftg2Count_42, h);
        model->ftg2Count_42 = 0;
        model->ftg2_68 = 0;
    }
    if (model->swaps_6C)
    {
        HeapFree_8003FD18(model->swaps_6C, h);
        model->swapCount_43 = 0;
        model->swaps_6C = 0;
    }
}
// Matched
void GetModelAltFtg_80025B20(void* dst, Model* src, int idx)
{
    MemCopy_800403E8(dst, &src->ftg2_68[idx], sizeof(FtgObject));
}
// Matched
void SetModelFtg_80025B5C(Model* model, int idx, int sel)
{
    FtgObject ftg;
    if (idx == sel)
    {
        GetSavedModelFtg_8002512C((unsigned int*)&ftg, model, idx);
    }
    else if (sel < model->ftgCount_3C)
    {
        GetModelFtg_800251A0(&ftg, model, idx, sel);
    }
    else
    {
        GetModelAltFtg_80025B20(&ftg, model, sel - model->ftgCount_3C);
    }
    model->ftg_50[idx] = ftg;
}
// Matched
void ApplyModelFtgSwaps_80025C38(Model* model, int flag)
{
    int i;
    for (i = 0; i < model->savedCount_40; i++)
    {
        ModelSavedFtg* e = (ModelSavedFtg*)(i * 0x58 + (int)model->saved_64); // integer sum, as above
        SetModelFtg_80025B5C(model, e->id_0, e->id_0);
    }
    if (flag)
    {
        for (i = 0; i < model->swapCount_43; i++)
        {
            ModelFtgSwap* swap = (ModelFtgSwap*)(i * 4 + (int)model->swaps_6C);
            SetModelFtg_80025B5C(model, swap->dst_0, swap->src_2);
        }
    }
}
// Matched
int AddFileRequest_80025D00(Model* model, FileRequestDesc* req)
{
    if (model->requestCount_4 < 10)
    {
        req->offset_8 <<= 11;
        req->size_C <<= 11;
        model->requests_8[model->requestCount_4] = QueueFileRequest_8003BC84(req);
        model->requestCount_4 += 1;
        return 1;
    }
    return 0;
}
// Matched
void OnModelFileLoaded_80025D7C(int* arg, int data)
{
    ModelLoadParams* params = (ModelLoadParams*)arg;
    if (params->flags_0 & 1)
    {
        params->header_1C = (ModelHeaderSection*)data;
        data += params->desc_4->header_2.size << 11;
    }
    if (params->flags_0 & 2)
    {
        params->tim_20 = (int*)data;
        data += params->desc_4->tex_6.size << 11;
    }
    if (params->flags_0 & 4)
    {
        params->ftg_24 = (int*)data;
        data += params->desc_4->ftg_A.size << 11;
    }
    if (params->flags_0 & 8)
    {
        params->anims_28 = (ModelAnimSection*)data;
        data += params->desc_4->anims_E.size << 11;
    }
    if (params->flags_0 & 0x10)
    {
        params->anim_2C = (char*)data;
    }
    if (params->flags_0 & 0x20)
    {
        params->animSet_30 = (ModelAnimSetSection*)data;
    }
    if (params->flags_0 & 0x40)
    {
        params->flags_0 |= 0x80;
        params->extra_38 = (unsigned char*)(data + ((int*)data)[1]);
        params->flags_0 |= 0x40;
        params->ftg2_34 = (int*)(data + ((int*)data)[2]);
        params->flags_0 |= 2;
        params->tim_20 = (int*)(data + ((int*)data)[3]);
    }
    ParseModelFile_80025F14(params);
}
// Matched
void InitModelLoadParams_80025ED0(ModelLoadParams* params)
{
    params->sel_8 = -1;
    params->flags_0 = 0;
    params->desc_4 = 0;
    params->mode_C = 2;
    params->animIdx_10 = 0;
    params->model_14 = 0;
    params->vram_18 = 0;
    params->header_1C = 0;
    params->tim_20 = 0;
    params->ftg_24 = 0;
    params->anims_28 = 0;
    params->anim_2C = 0;
    params->ftg2_34 = 0;
    params->extra_38 = 0;
}
// Matched
void ParseModelFile_80025F14(ModelLoadParams* params)
{
    if (params->flags_0 & 1)
    {
        LoadModelHeader_80026014(params);
    }
    if (params->flags_0 & 2)
    {
        LoadModelTextures_8002607C(params);
    }
    if (params->flags_0 & 4)
    {
        LoadModelFtg_800260FC(params);
    }
    if (params->flags_0 & 8)
    {
        LoadModelAnims_800261C8(params);
    }
    if (params->flags_0 & 0x10)
    {
        LoadSingleModelAnim_800263CC(params);
    }
    if (params->flags_0 & 0x20)
    {
        LoadModelAnimSetSection_80026410(params);
    }
    if (params->flags_0 & 0x40)
    {
        LoadModelAltFtgSection_8002651C(params);
    }
    if (params->flags_0 & 0x80)
    {
        LoadModelFtgSwaps_8002659C(params);
    }
}
// Matched
void LoadModelHeader_80026014(ModelLoadParams* params)
{
    ModelHeaderSection* section = params->header_1C;
    Model* model = params->model_14;
    int h = model->list_0->heap_4;
    int size = section->size_0;
    void* buf;
    model->headerSize_48 = size;
    buf = HeapAlloc_8003FC8C(size, h);
    model->header_4C = buf;
    MemCopy_800403E8(buf, params->header_1C->data_4, size);
}
// Matched
void LoadModelTextures_8002607C(ModelLoadParams* params)
{
    if (params->sel_8 != -1)
    {
        Model* model = params->model_14;
        LoadTiyTimsRelocated_80028FDC(0, 0, 0, (int)params->tim_20, GetTiyFileCount_80028E68(params->tim_20), (int)params->vram_18->reloc_4, params->sel_8);
        model->texSel_34 = params->sel_8;
    }
}
// Matched
void LoadModelFtg_800260FC(ModelLoadParams* params)
{
    Model* model = params->model_14;
    int* list = params->ftg_24;
    ModelVramSlot* vram = params->vram_18;
    int h = model->list_0->heap_4;
    model->ftgCount_3C = GetFtgObjectCount_80021738(list);
    AllocFtgObjects_80021744(&model->ftg_50, model->ftgCount_3C, h);
    LoadFtgObjects_80021824(params->ftg_24, model->ftg_50, model->ftgCount_3C, h, (int)vram->reloc_4);
    if (GetFtgMatCount_80021DE4(params->ftg_24) != 0)
    {
        AllocFtgMatList_80021DF0(&model->mats_5C, GetFtgMatCount_80021DE4(params->ftg_24), h);
        LoadFtgMatList_80021E4C(params->ftg_24, &model->mats_5C, GetFtgMatCount_80021DE4(params->ftg_24));
    }
}
// Matched
void LoadModelAnims_800261C8(ModelLoadParams* params)
{
    Model* model = params->model_14;
    int h = model->list_0->heap_4;
    int i;
    int j;
    int mode;
    model->animCount_3E = params->desc_4->animCount_12;
    if (model->anims_54 == 0)
    {
        AllocModelAnims_80026730(&model->anims_54, model->animCount_3E, h);
    }
    if (model->animLoaded_44 != 0)
    {
        HeapFree_8003FD18(model->animLoaded_44, h);
    }
    model->animLoaded_44 = HeapAlloc_8003FC8C(model->animCount_3E, h);
    for (i = 0; i < model->animCount_3E; i++)
    {
        mode = params->mode_C;
        if (mode == 0)
        {
            if (i == 0)
            {
                model->animLoaded_44[0] = 1;
            }
            else
            {
                model->animLoaded_44[i] = 0;
            }
        }
        else if (mode == 1)
        {
            if (i == 0)
            {
                model->animLoaded_44[0] = 1;
            }
            else if (i == 1)
            {
                model->animLoaded_44[1] = 1;
            }
            else
            {
                model->animLoaded_44[i] = 0;
            }
        }
        else if (mode == 3)
        {
            if (i == 0)
            {
                model->animLoaded_44[0] = 0;
            }
            else if (i == 1)
            {
                model->animLoaded_44[1] = 0;
            }
            else
            {
                model->animLoaded_44[i] = *(unsigned char*)&params->desc_4->animFlags_14[i];
            }
        }
        else
        {
            model->animLoaded_44[i] = *(unsigned char*)&params->desc_4->animFlags_14[i];
        }
    }
    for (i = 0, j = 0; i < model->animCount_3E; i++)
    {
        if ((&params->desc_4->animFlags_14[0])[i] != 0) // indexed through the decayed pointer, as the original
        {
            if (model->animLoaded_44[i] != 0)
            {
                LoadModelAnimData_80026A8C(&model->anims_54[i], (int)params->anims_28 + (&params->anims_28->offsets_4[0])[j], h);
            }
            j++;
        }
    }
}
// Matched
void LoadSingleModelAnim_800263CC(ModelLoadParams* params)
{
    ModelList* l;
    Model* model = params->model_14;
    l = model->list_0;
    LoadModelAnimData_80026A8C(&model->anims_54[params->animIdx_10], (int)params->anim_2C, l->heap_4);
}
// Matched
void LoadModelAnimSetSection_80026410(ModelLoadParams* params)
{
    ModelAnimSetSection* section = params->animSet_30;
    Model* model = params->model_14;
    int count = section->count_0;
    int h = model->list_0->heap_4;
    int* list = HeapAlloc_8003FC8C((count + 1) * 4, h);
    int i;
    int id;
    int src;
    model->animSet_58 = list;
    list[0] = count;
    for (i = 0; i < count; i++)
    {
        id = section->items_4[i].id;
        src = (int)section + section->items_4[i].offset;
        if (model->animLoaded_44[id] == 0)
        {
            model->animSet_58[i + 1] = id;
            model->animLoaded_44[id] = 1;
            LoadModelAnimData_80026A8C(&model->anims_54[id], src, h);
        }
        else
        {
            model->animSet_58[i + 1] = -1;
        }
    }
}
// Matched
void LoadModelAltFtgSection_8002651C(ModelLoadParams* params)
{
    Model* model = params->model_14;
    int* list = params->ftg2_34;
    ModelVramSlot* vram = params->vram_18;
    int heap = model->list_0->heap_4;
    model->ftg2Count_42 = GetFtgObjectCount_80021738(list);
    AllocFtgObjects_80021744(&model->ftg2_68, model->ftg2Count_42, heap);
    LoadFtgObjects_80021824(params->ftg2_34, model->ftg2_68, model->ftg2Count_42, heap, (int)vram->reloc_4);
}
// Matched
void LoadModelFtgSwaps_8002659C(ModelLoadParams* params)
{
    unsigned char* src = params->extra_38;
    Model* model = params->model_14;
    int h = model->list_0->heap_4;
    void* buf;
    model->swapCount_43 = *src;
    src += 4;
    buf = HeapAlloc_8003FC8C(model->swapCount_43 << 2, h);
    model->swaps_6C = buf;
    MemCopy_800403E8(buf, src, model->swapCount_43 << 2);
}
// Matched
int CountModelVramSlots_80026600(ModelVramSlot* slot)
{
    int count = 0;
    if (slot->id_2 != -1)
    {
        do
        {
            slot++;
            count++;
        } while (slot->id_2 != -1);
    }
    return count;
}
// Matched
int FindModelIndex_80026630(ModelList* list, unsigned int id)
{
    int i;
    for (i = 0; i < list->count_0; i++)
    {
        if (list->items_8[i].id_38 == id)
        {
            return i;
        }
    }
    return -1;
}
// Matched
int FindFreeModelIndex_8002667C(ModelList* list)
{
    int i;
    for (i = 0; i < list->count_0; i++)
    {
        if (list->items_8[i].id_38 == 0xFFFF)
        {
            return i;
        }
    }
    return -1;
}
// Matched
void ClearModel_800266CC(Model* model)
{
    model->id_38 = 0xFFFF;
    model->requestCount_4 = 0;
    model->texSel_34 = 0;
    model->refs_3A = 0;
    model->ftgCount_3C = 0;
    model->animCount_3E = 0;
    model->savedCount_40 = 0;
    model->ftg2Count_42 = 0;
    model->swapCount_43 = 0;
    model->animLoaded_44 = 0;
    model->headerSize_48 = 0;
    model->header_4C = 0;
    model->ftg_50 = 0;
    model->anims_54 = 0;
    model->animSet_58 = 0;
    model->mats_5C.count_0 = 0;
    model->mats_5C.items_4 = 0;
    model->saved_64 = 0;
    model->ftg2_68 = 0;
    model->swaps_6C = 0;
}
// Matched
int GetModelAnimCount_80026724(int* section)
{
    return section[0];
}
// Matched
void AllocModelAnims_80026730(ModelAnim** out, int count, int heap)
{
    ModelAnim* anims = HeapAlloc_8003FC8C(count * 28, heap);
    int i;
    *out = anims;
    for (i = 0; i < count; i++)
    {
        anims[i].cues_10 = 0;
        anims[i].basePose_14 = 0;
        anims[i].frames_18 = 0;
    }
}
// Matched
void FreeModelAnims_8002679C(ModelAnim** anims, int count, int heap)
{
    ModelAnim* arr;
    int i;
    if (*anims)
    {
        arr = *anims;
        for (i = 0; i < count; i++)
        {
            if (arr[i].cues_10)
            {
                HeapFree_8003FD18(arr[i].cues_10, heap);
            }
            if (arr[i].basePose_14)
            {
                HeapFree_8003FD18(arr[i].basePose_14, heap);
            }
            if (arr[i].frames_18)
            {
                HeapFree_8003FD18(arr[i].frames_18, heap);
            }
        }
        HeapFree_8003FD18(arr, heap);
        *anims = 0;
    }
}
// Matched
void LoadModelAnimSection_80026870(ModelAnim** out, int section, int heap)
{
    int count = GetModelAnimCount_80026724((int*)section);
    AllocModelAnims_80026730(out, count, heap);
    LoadModelAnimsMasked_800268E8(out[0], section, count, heap, -1);
}
// Matched
void LoadModelAnimsMasked_800268E8(ModelAnim* anims, int section, int count, int h, int mask)
{
    int* offsets = (int*)section;
    int i;
    for (i = 0; i < count; i++, anims++)
    {
        int bit = 1 << i;
        if ((mask & bit) && anims->basePose_14 == 0 && anims->frames_18 == 0)
        {
            LoadModelAnimData_80026A8C(anims, section + offsets[i + 1], h);
        }
    }
}
// Matched
void FreeModelAnimData_800269C4(ModelAnim* anims, int count, int sel, int h)
{
    ModelAnim* anim = anims;
    int i;
    for (i = 0; i < count; i++, anim++)
    {
        if (sel == i && anim->basePose_14 != 0 && anim->frames_18 != 0)
        {
            if (anim->cues_10 != 0)
            {
                HeapFree_8003FD18(anim->cues_10, h);
            }
            HeapFree_8003FD18(anim->basePose_14, h);
            HeapFree_8003FD18(anim->frames_18, h);
            anim->cues_10 = 0;
            anim->basePose_14 = 0;
            anim->frames_18 = 0;
        }
    }
}
// Matched
void LoadModelAnimData_80026A8C(ModelAnim* anim, int src, int heap)
{
    int hasDivisor = 0;
    int hasCues = hasDivisor;
    unsigned int frames;
    unsigned int m;
    unsigned short* cur;
    unsigned short* dst;
    unsigned int i;
    unsigned int j;
    int size;
    int k;
    anim->frameCount_0 = ((ModelAnimFile*)src)->frameCount_0;
    frames = anim->frameCount_0;
    anim->boneCount_4 = ((ModelAnimFile*)src)->boneCount_4;
    m = anim->boneCount_4;
    if ((int)frames < 0)
    {
        frames &= 0x7FFFFFFF;
        cur = (unsigned short*)(((int*)src) + 3);
        anim->frameCount_0 = frames;
        anim->divisor_8 = ((ModelAnimFile*)src)->divisor_8;
        hasDivisor = 1;
    }
    else
    {
        anim->divisor_8 = 0x20;
        cur = (unsigned short*)(((int*)src) + 2);
    }
    if ((int)m < 0)
    {
        m &= 0x7FFFFFFF;
        hasCues = 1;
    }
    else
    {
        anim->cueCount_C = 0;
    }
    anim->basePose_14 = HeapAlloc_8003FC8C(m * 6, heap);
    anim->frames_18 = HeapAlloc_8003FC8C((m + 2) * (frames << 1) * 3, heap);
    dst = anim->basePose_14;
    for (i = 0; i < m; i++)
    {
        *dst++ = *cur++;
        *dst++ = *cur++;
        *dst++ = *cur++;
    }
    dst = anim->frames_18;
    for (j = 0; j < frames; j++)
    {
        *dst++ = *cur++;
        *dst++ = *cur++;
        *dst++ = *cur++;
        *dst++ = *cur++;
        *dst++ = *cur++;
        *dst++ = *cur++;
        for (i = 0; i < m; i++)
        {
            *dst++ = *cur++;
            *dst++ = *cur++;
            *dst++ = *cur++;
        }
    }
    if (hasCues)
    {
        size = m * 6 + 8;
        size += (m * 6 + 0xC) * frames;
        if (hasDivisor)
        {
            size += 4;
        }
        cur = (unsigned short*)((char*)((int*)src) + size);
        if (size & 3)
        {
            size += 2;
            cur = (unsigned short*)((char*)((int*)src) + size);
        }
        anim->cueCount_C = *(int*)cur;
        cur += 2;
        anim->cues_10 = HeapAlloc_8003FC8C(anim->cueCount_C * 8, heap);
        k = 0;
        while (k < anim->cueCount_C)
        {
            anim->cues_10[k].frame_0 = cur[0];
            anim->cues_10[k].kind_2 = cur[1];
            anim->cues_10[k].arg_4 = cur[2];
            anim->cues_10[k].arg_6 = cur[3];
            k++;
            cur += 4;
        }
    }
}
// Matched
int GetRecordTableCount_80026D6C(int* file)
{
    return file[0];
}
// Matched
void AllocRecordTables_80026D78(RecordTable** out, int count, int heap)
{
    RecordTable* tables = HeapAlloc_8003FC8C(count * 12, heap);
    int i;
    for (i = 0; i < count; i++)
    {
        tables[i].count_0 = 0;
        tables[i].field_4 = 0;
        tables[i].records_8 = 0;
    }
    *out = tables;
}
// Matched
void FreeRecordTables_80026DE8(RecordTable** tables, int count, int h)
{
    RecordTable* table = *tables;
    int i;
    for (i = 0; i < count; i++, table++)
    {
        if (table->records_8 != 0)
        {
            HeapFree_8003FD18(table->records_8, h);
        }
    }
    HeapFree_8003FD18(*tables, h);
    *tables = 0;
}
// Matched
void LoadRecordTables_80026E74(RecordTable* tables, int* file, int heap)
{
    int i;
    for (i = 0; i < GetRecordTableCount_80026D6C(file); i++)
    {
        LoadRecordTable_80026EF8(tables, (unsigned short*)((char*)file + file[i + 1]), heap);
        tables++;
    }
}
typedef struct
{
    unsigned short a;
    unsigned short b;
    unsigned short c;
    unsigned short d;
} RecordEntry; // one 8-byte entry of a record table (LoadRecordTable_80026EF8)
// Matched
void LoadRecordTable_80026EF8(RecordTable* table, unsigned short* src, int heap)
{
    unsigned short* d;
    int i;
    table->count_0 = *(int*)src;
    src += 2;
    table->field_4 = *(int*)src;
    src += 2;
    d = HeapAlloc_8003FC8C(table->count_0 * 8, heap);
    table->records_8 = d;
    for (i = 0; i < table->count_0; i++)
    {
        d[0] = src[0];
        d[1] = src[1];
        d[2] = src[2];
        d[3] = src[3];
        d += 4;
        src += 4;
    }
}
typedef struct
{
    int pos[3];
    int mapIdx;
} SavedLevantPos;
extern SavedLevantPos savedLevantPos_80091C78;
extern int gameStartMode_800B1DC8;
// Matched
void InitMapState_80026FAC(void)
{
    ListInit_8003FDB0(&mapHeap_80091C68);
    ListInit_8003FDB0(&areaHeap_80091C20);
    ListInit_8003FDB0(&eventHeap_80091C10);
    ListInit_8003FDB0(&heap_80091C48);
    loadFade_80091C30[0] = 0x3A;
    loadFade_80091C30[1] = 0;
    loadFade_80091C30[2] = 0;
    loadFade_80091C30[3] = -1;
    mapState_8008B500.nMeshes_4 = 0;
    mapState_8008B500.f8_8 = 0;
    mapState_8008B500.meshes_C = 0;
    mapState_8008B500.mesh_28 = 0;
    mapState_8008B500.ftgCount_38 = 0;
    mapState_8008B500.ftg_3C = 0;
    tileAnim_8008D648.count_0 = 0;
    tileAnim_8008D648.field_4 = 0;
    tileAnim_8008D648.field_8 = 0;
    tileAnim_8008D648.items_C = 0;
    tileAnim_8008D648.field_4 = 0;
    tileAnim_8008D648.field_8 = 0;
    tileAnim_8008D648.listCount_10 = 0;
    tileAnim_8008D648.lists_14 = 0;
    tileAnim_8008D648.pairs_18 = 0;
    currentAreaMap_80091C88 = -1;
    currentArea_80091C44 = -1;
    mapAreas_80082674 = 0;
    useSavedLevantPos_80091C98 = 0;
    useMapStartPos_80091C94 = 0;
    dword_80091C5C = 1;
    dword_80091C58 = 1;
    dword_80091C90 = 0;
    freeActorModels_80091CA0 = 0;
    forceMapReload_80091C9C = 0;
    dword_80091C8C = 0;
    savedLevantPos_80091C78.mapIdx = -1;
    mapStartMode_80091C54 = gameStartMode_800B1DC8;
    areaLoadIds_80091CB8[7] = -1;
    areaLoadIds_80091CB8[6] = -1;
    areaLoadIds_80091CB8[5] = -1;
    areaLoadIds_80091CB8[4] = -1;
    areaLoadIds_80091CB8[3] = -1;
    areaLoadIds_80091CB8[2] = -1;
    areaLoadIds_80091CB8[1] = -1;
    areaPreload_80091C40[0] = -1;
    areaLoadIds_80091CB8[0] = -1;
    areaPreload_80091C40[1] = -1;
    areaPreloading_80082678 = 0;
    InitActors_8001D378();
}
extern int mapCallback_80091CB4;
extern EventNode* dword_800B1DA8;
extern void FreeLevantAnimSet_800AC73C(void);
extern void FreeAllEventData_800A54A0(void);
extern void StopAllEventScripts_800A58B4(void);
extern void ClearFieldMinions_800A7784(void);
extern void ResetEncounter_800A170C(void);
extern void ClearEnemySlots_800A1794(void);
// Matched
void UnloadMap_80027118(void)
{
    areaLoadIds_80091CB8[7] = -1;
    areaLoadIds_80091CB8[6] = -1;
    areaLoadIds_80091CB8[5] = -1;
    areaLoadIds_80091CB8[4] = -1;
    areaLoadIds_80091CB8[3] = -1;
    areaLoadIds_80091CB8[2] = -1;
    areaLoadIds_80091CB8[1] = -1;
    areaPreload_80091C40[0] = -1;
    areaLoadIds_80091CB8[0] = -1;
    areaPreload_80091C40[1] = -1;
    CancelAreaPreload_8002741C();
    areaPreloading_80082678 = 0;
    levantAnimSet_80091C74 = -1;
    mapCallback_80091CB4 = 0;
    currentAreaMap_80091C88 = -1;
    mapJustLoaded_80082668 = 0;
    mapHasCode_8008266C = 0;
    if (dword_80091C8C == 0)
    {
        StopAllEventEntries_80043B40(dword_800B1DA8);
        StopAllEventEntries_80043B40(eventEntities_8008D400);
    }
    FreeLevantAnimSet_800AC73C();
    StopAllEventEntries_80043B40(messageWindowTask_8008D640);
    StopAllEventEntries_80043B40(enemyAiTasks_8008D49C);
    StopAllEventEntries_80043B40(encounterTask_8008D674);
    StopAllEventEntries_80043B40(fileRequestTasks_8008D488);
    FreeAllEventData_800A54A0();
    StopAllEventScripts_800A58B4();
    FreeActors_8001D3C4(freeActorModels_80091CA0);
    ClearFieldMinions_800A7784();
    ResetEncounter_800A170C();
    ClearEnemySlots_800A1794();
    ListFreeAll_8003FEC8(&eventHeap_80091C10);
    ListFreeAll_8003FEC8(&mapHeap_80091C68);
    if (!(unknownFlags_8008D678 & 0x20000))
    {
        ListFreeAll_8003FEC8(&heap_80091C48);
    }
}
// Matched
void FreeMapArea_8002728C(void)
{
    currentArea_80091C44 = -1;
    ListFreeAll_8003FEC8(&areaHeap_80091C20);
}
// Matched
void SetCurrentArea_800272BC(int map, int area)
{
    currentAreaMap_80091C88 = map;
    currentArea_80091C44 = area;
}
#if 0
// Not matched (close)
int IsMapLoading_800272D0(void)
{
    int* a = mapLoaderTask_800B1DC4[0x24 / 4];
    int* b = areaLoaderTask_800B1DB8[0x24 / 4];
    if (*a != 0)
    {
        return 1;
    }
    if (*b == 0)
    {
        return 0;
    }
    return 1;
}
#endif
// Matched
int IsMapLoading_800272D0(void)
{
    int* a = mapLoaderTask_800B1DC4[9];
    int* b = areaLoaderTask_800B1DB8[9];
    if (a[0] != 0 || b[0] != 0)
    {
        return 1;
    }
    return 0;
}
// Matched
void RequestAreaReload_80027314(void)
{
    areaReload_80082670 = 1;
    word_8008B862 = -1;
}
// Matched
int RequestAreaPreload_80027330(short area)
{
    if (areaPreloading_80082678 == 0)
    {
        areaPreload_80091C40[0] = area;
        return 1;
    }
    return 0;
}
// Matched
int UsePreloadedArea_80027358(int id)
{
    int* task;
    if (areaPreloading_80082678 == 1)
    {
        if (areaPreload_80091C40[0] != id)
        {
            pendingArea_8008B860 = id;
            return 0;
        }
        task = areaLoaderTask_800B1DB8[9];
        if (GetFileRequestStatus_8003BE30(task[1]) != 3)
        {
            return 0;
        }
        FreeMapArea_8002728C();
        ConsumeFileRequest_8003BFD0(task[1], 0);
        InitRoomCamera_80028DC0();
        saveData_8008B570.mapId_2E4[3].field_0 = id;
        saveData_8008B570.mapId_2E4[3].field_2 = id;
        areaPreloading_80082678 = 0;
        return 1;
    }
    pendingArea_8008B860 = id;
    return 0;
}
// Matched
void CancelAreaPreload_8002741C(void)
{
    int* task;
    if (areaPreloading_80082678 == 1)
    {
        task = areaLoaderTask_800B1DB8[9];
        CancelFileRequest_8003C060(task[1]);
        areaPreloading_80082678 = 0;
        task[0] = 0;
    }
}
// Matched
void SetLoadFadeFlag_80027478(int mask, int set)
{
    int f;
    int code;
    if (set)
    {
        loadFade_80091C30[2] |= mask;
    }
    else
    {
        loadFade_80091C30[2] &= ~mask;
    }
    f = loadFade_80091C30[2];
    if (f && !(f & 1))
    {
        code = 0;
        if (!(f & 0x40))
        {
            if (loadFade_80091C30[0] & f)
            {
                code = 1;
            }
            else if (loadFade_80091C30[1] & f)
            {
                code = 2;
            }
        }
        loadFade_80091C30[2] |= 1;
        SetFadeMode_8001C19C(code, 0x20);
    }
}
// Matched
int UpdateLoadFade_80027540(void)
{
    int* g = loadFade_80091C30;
    if (g[2] & 0x40)
    {
        return 1;
    }
    if (g[2] & 1)
    {
        if (g[2] == 1 && IsFadeDone_8001C2FC())
        {
            g[3] = 2;
            g[2] &= ~1;
            return 1;
        }
        return 0;
    }
    if (g[3] > 0)
    {
        g[3]--;
        if (g[3] <= 0)
        {
            SetFadeMode_8001C19C(3, 0);
        }
    }
    return 1;
}
// Matched
void AllocMapWallFlags_800275E8(unsigned char** out, int count, List* heap)
{
    unsigned char* flags;
    unsigned char* cur;
    int i;
    if (count != 0)
    {
        flags = ListAlloc_8003FDC0(heap, count);
        *out = flags;
        cur = flags;
        for (i = 0; i < count; i++)
        {
            cur[i] = 1;
        }
    }
}
// Matched
int* LoadMapSpawns_80027650(int* file, int unused, List* h)
{
    int* src;
    int (*d)[4];
    int count;
    int i;
    MapList16* g = &mapSpawns_80091C60;
    file += 1;
    count = *file++;
    src = file;
    g->count_0 = count;
    if (count != 0)
    {
        d = ListAlloc_8003FDC0(h, count * 16);
        g->items_4 = d;
        for (i = 0; i < g->count_0; i++)
        {
            (*d)[0] = src[0];
            (*d)[1] = src[1];
            (*d)[2] = src[2];
            (*d)[3] = src[3];
            d++;
            src += 4;
        }
    }
    return src;
}
// Matched
void LoadMapFtg_80027708(int* file, int heap)
{
    int count = GetFtgObjectCount_80021738(file);
    mapState_8008B500.ftgCount_38 = count;
    if (count != 0)
    {
        AllocFtgObjects_80021744(&mapState_8008B500.ftg_3C, count, heap);
        LoadFtgObjects_80021824(file, mapState_8008B500.ftg_3C, mapState_8008B500.ftgCount_38, heap, 0);
    }
}
// Matched
void LoadTileSets_80027778(int* data, List* heap)
{
    TileSet* arr;
    unsigned int i;
    int j;
    int* src;
    unsigned short* cur;
    int count;
    tileAnim_8008D648.field_4 = data[0];
    tileAnim_8008D648.field_8 = data[1];
    count = data[2];
    tileAnim_8008D648.count_0 = count;
    arr = ListAlloc_8003FDC0(heap, count * 16);
    for (i = 0; i < tileAnim_8008D648.count_0; i++)
    {
        src = (int*)((char*)data + data[i + 3]);
        arr[i].depth_0 = *src++;
        arr[i].count = *src++;
        cur = (unsigned short*)src;
        arr[i].columns_8 = *cur++;
        arr[i].rows_A = *cur++;
        arr[i].items = ListAlloc_8003FDC0(heap, arr[i].count * 2);
        for (j = 0; j < arr[i].count; j++)
        {
            arr[i].items[j] = *cur++;
        }
    }
    tileAnim_8008D648.items_C = arr;
}
// Matched
void LoadTileAnimLayers_800278BC(int* data, List* heap)
{
    int* file = data;
    unsigned int i;
    unsigned int j;
    int count;
    int* src;
    TileAnimFrame* frames;
    TileAnimTimer* timer;
    count = file[0];
    tileAnim_8008D648.listCount_10 = count;
    tileAnim_8008D648.lists_14 = ListAlloc_8003FDC0(heap, count * 8);
    for (i = 0; i < tileAnim_8008D648.listCount_10; i++)
    {
        src = (int*)((char*)file + file[i + 1]);
        tileAnim_8008D648.lists_14[i].count = *src;
        tileAnim_8008D648.lists_14[i].items = ListAlloc_8003FDC0(heap, tileAnim_8008D648.lists_14[i].count * 4);
        frames = (TileAnimFrame*)(src + 1);
        for (j = 0; j < tileAnim_8008D648.lists_14[i].count; j++)
        {
            tileAnim_8008D648.lists_14[i].items[j].set_0 = frames[j].set_0;
            tileAnim_8008D648.lists_14[i].items[j].clut_1 = frames[j].clut_1;
            tileAnim_8008D648.lists_14[i].items[j].time_2 = frames[j].time_2;
        }
    }
    tileAnim_8008D648.pairs_18 = ListAlloc_8003FDC0(heap, tileAnim_8008D648.listCount_10 * 4);
    for (i = 0; i < tileAnim_8008D648.listCount_10; i++)
    {
        timer = (TileAnimTimer*)(i * 4 + (int)tileAnim_8008D648.pairs_18); // integer sum, as the original
        timer->frame_2 = 0;
        timer->timer_0 = 0;
    }
}
// Matched
int* LoadMapMeshes_80027A88(MapMesh** out, unsigned int* count, List* heap, MapMeshFile* hdr)
{
    MapMesh* arr;
    unsigned int i;
    unsigned int j;
    unsigned char* cur;
    MapMeshRec* rec;
    MapTriRec* tri;
    MapMeshFile* hh;
    cur = (unsigned char*)(hdr + 1);
    hh = hdr;
    arr = ListAlloc_8003FDC0(heap, hdr->count_4 * sizeof(MapMesh));
    *count = hdr->count_4;
    if (hdr->count_4 == 0)
    {
        *out = 0;
        return (int*)((unsigned char*)hdr + hdr->size_0);
    }
    for (i = 0; i < hh->count_4; i++)
    {
        rec = (MapMeshRec*)cur;
        arr[i].nTris_0 = rec->nTris_0;
        cur = (unsigned char*)(rec + 1);
        arr[i].tris_4 = ListAlloc_8003FDC0(heap, rec->nTris_0 * sizeof(MapTri));
        for (j = 0; j < rec->nTris_0; j++)
        {
            tri = (MapTriRec*)cur;
            cur += sizeof(int);
            arr[i].tris_4[j].nx_18 = tri->n_8.x_0;
            arr[i].tris_4[j].ny_1A = tri->n_8.y_2;
            arr[i].tris_4[j].nz_1C = tri->n_8.z_4;
            arr[i].tris_4[j].pad_1E = 0;
            arr[i].tris_4[j].v_0[0].x_0 = tri->v_10[0].x_0;
            arr[i].tris_4[j].v_0[0].y_2 = tri->v_10[0].y_2;
            arr[i].tris_4[j].v_0[0].z_4 = tri->v_10[0].z_4;
            arr[i].tris_4[j].v_0[0].pad_6 = 0;
            arr[i].tris_4[j].v_0[1].x_0 = tri->v_10[1].x_0;
            arr[i].tris_4[j].v_0[1].y_2 = tri->v_10[1].y_2;
            arr[i].tris_4[j].v_0[1].z_4 = tri->v_10[1].z_4;
            arr[i].tris_4[j].v_0[1].pad_6 = 0;
            arr[i].tris_4[j].v_0[2].x_0 = tri->v_10[2].x_0;
            arr[i].tris_4[j].v_0[2].y_2 = tri->v_10[2].y_2;
            arr[i].tris_4[j].v_0[2].z_4 = tri->v_10[2].z_4;
            arr[i].tris_4[j].v_0[2].pad_6 = 0;
            cur += sizeof(MapTriRec) - sizeof(int);
        }
    }
    *out = arr;
    return (int*)((unsigned char*)hdr + hh->size_0);
}
// Matched
void InitMapLoaderTask_80027CC0(EventEntry* entry, int* state)
{
    state[0] = 0;
    state[1] = 0;
    MapLoaderTask_80027CF8(entry, state);
    entry->cb_8 = (EventEntryFn)MapLoaderTask_80027CF8;
}
typedef struct
{
    short f0;
    short f2;
    short f4;
    short encounterSet_6; // SelectEncounterSpecies_800A5030 / SetBattleStageForMap_800A52AC argument
    short music_8;        // PlayMusic_800300E0 id (< 0: keep)
    short fA;
    char pad_C[4];
} MapAreaEntry;
extern MapAreaEntry** mapTable_800B0608[];
#define MAP_ENTRY_CF8(i) mapTable_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0][i]
extern int fieldMode_800B0EC0;
extern void SelectMapEntrance_800ADDAC(void);
extern int GetSetReturnEntrance_800A683C(int a0);
extern void ClearEventFlag_800AD124(int a0);
extern int SelectEncounterSpecies_800A5030(int a0, int a1, int a2);
extern void SetBattleStageForMap_800A52AC(int a0);
extern Model* GetLevantModel_800AC38C(void);
extern int GetEventVar_800AD154(int a0);
extern void StartEncounter_800B88A4(int a0);
extern void PlayMusic_800300E0(int a, int b);
// Matched
void MapLoaderTask_80027CF8(void* entry, int* state)
{
    int* st = state;
    short encounterSets[2];
    FileRequestDesc req;
    MapAreaEntry* e;
    int encounter;
    int music;
    int n;
    int k;
    switch (st[0])
    {
    case 0:
        music = fieldMode_800B0EC0;
        if (music == 1 && IsOverlayLoaderIdle_80020D84() == 0)
        {
            eventDispatchHalt_8008B540 = music;
        }
        else if (UpdateLoadFade_80027540() != 0)
        {
            if (forceMapReload_80091C9C != 1 &&
                saveData_8008B570.mapId_2E4[0].field_2 == saveData_8008B570.mapId_2E4[0].field_0 &&
                saveData_8008B570.mapId_2E4[1].field_2 == saveData_8008B570.mapId_2E4[1].field_0 &&
                saveData_8008B570.mapId_2E4[2].field_2 == saveData_8008B570.mapId_2E4[2].field_0)
            {
            }
            else
            {
                if (mapStartMode_80091C54)
                {
                    SelectMapEntrance_800ADDAC();
                }
                if (GetSetReturnEntrance_800A683C(-1) != MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).encounterSet_6)
                {
                    ClearEventFlag_800AD124(0);
                }
                e = mapTable_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0];
                for (mapAreaCount_80091CB0 = 0; e[mapAreaCount_80091CB0].f0 != -1; mapAreaCount_80091CB0++)
                {
                }
                encounterSets[1] = MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_2).encounterSet_6;
                encounterSets[0] = MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).encounterSet_6;
                encounter = SelectEncounterSpecies_800A5030(encounterSets[0], encounterSets[1], dword_80091C90);
                SetBattleStageForMap_800A52AC(encounterSets[0]);
                mapStartMode_80091C54 = 1;
                areaReload_80082670 = 0;
                forceMapReload_80091C9C = 0;
                saveData_8008B570.mapId_2E4[0].field_2 = saveData_8008B570.mapId_2E4[0].field_0;
                saveData_8008B570.mapId_2E4[1].field_2 = saveData_8008B570.mapId_2E4[1].field_0;
                saveData_8008B570.mapId_2E4[2].field_2 = saveData_8008B570.mapId_2E4[2].field_0;
                if ((unsigned short)(saveData_8008B570.mapId_2E4[0].field_0 - 1) < 2)
                {
                    unknownFlags_8008D678 |= 0x1000000;
                }
                else
                {
                    unknownFlags_8008D678 &= ~0x1000000;
                }
                ApplyModelFtgSwaps_80025C38(GetLevantModel_800AC38C(), (((unsigned int)unknownFlags_8008D678 >> 24) ^ 1) & 1);
                freeActorModels_80091CA0 = 0;
                if (dword_80091C90 != 0 || MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).fA != 0 || encounter != 0)
                {
                    freeActorModels_80091CA0 = 1;
                }
                dword_80091C90 = MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).fA;
                UnloadMap_80027118();
                FreeMapArea_8002728C();
                music = MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).music_8;
                if (music >= 0)
                {
                    if (GetEventVar_800AD154(12) == 1 && music == 0xD)
                    {
                        music = 0xF;
                    }
                    else if (GetEventVar_800AD154(12) == 2 && music == 0xD)
                    {
                        music = 0x91;
                    }
                    else if (GetEventVar_800AD154(12) == 3 && music == 0x29)
                    {
                        music = 0x26;
                    }
                    else if (GetEventVar_800AD154(12) == 4 && music == 0x2A)
                    {
                        music = 0x25;
                    }
                    PlayMusic_800300E0(music, 1);
                    SetBattleMusic_800315D8(music);
                    SetLoadFadeFlag_80027478(0x20, 1);
                }
                if (dword_80091C90 == 0 && dword_80091C58 != 0)
                {
                    StartEncounter_800B88A4(encounter);
                    k = st[0];
                    eventDispatchHalt_8008B540 = 1;
                    n = k;
                    st[0] = n + 1;
                    SetLoadFadeFlag_80027478(0x10, 1);
                    break;
                }
                st[0] += 1;
            }
        }
        if (st[0] != 1)
        {
            break;
        }
    case 1:
        req.flags_0 = 0x2C;
        req.fileId_4 = MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).f0;
        req.offset_8 = 0;
        req.size_C = 0;
        req.dest_10 = 0;
        req.params_14 = 0;
        req.paramsSize_18 = 0;
        req.callback_1C = OnMapFileLoaded_80028808;
        st[1] = QueueFileRequest_8003BC84(&req);
        SetLoadFadeFlag_80027478(2, 1);
        {
            int z = st[0];
            eventDispatchHalt_8008B540 = 1;
            st[0] = z + 1;
        }
        break;
    case 2:
        if (IsSoundTaskReady_800306B0() && IsModelLoaderDone_800205D0() && GetFileRequestStatus_8003BE30(st[1]) == 0)
        {
            SetLoadFadeFlag_80027478(0x72, 0);
            st[0] = 0;
        }
        else
        {
            eventDispatchHalt_8008B540 = 1;
        }
        break;
    }
}
// Matched
void ResetMapLoaderTask_8002830C(EventEntry* entry)
{
    saveData_8008B570.mapId_2E4[0].field_2 = -1;
    saveData_8008B570.mapId_2E4[1].field_2 = -1;
    saveData_8008B570.mapId_2E4[2].field_2 = -1;
    saveData_8008B570.mapId_2E4[3].field_2 = -1;
    unknownFlags_8008D678 &= ~0x20000;
    freeActorModels_80091CA0 = 1;
    UnloadMap_80027118();
    FreeMapArea_8002728C();
    entry->cb_8 = (EventEntryFn)InitMapLoaderTask_80027CC0;
}
// Matched
void InitAreaLoaderTask_80028388(EventEntry* entry, int* state)
{
    state[0] = 0;
    state[1] = 0;
    AreaLoaderTask_800283C0(entry, state);
    entry->cb_8 = (EventEntryFn)AreaLoaderTask_800283C0;
}
extern int GetGameMode_800A6D50(int a0);
extern int battleFlags_800B1228;
extern void OnRoomDataLoaded_80028C60();
// Matched
void AreaLoaderTask_800283C0(void* entry, int* state)
{
    int* st = state;
    FileRequestDesc req;
    FileRequestDesc req2;
    FileRequestDesc req3;
    int step;
    int load;
    int wait;
    step = st[0];
    switch (step)
    {
    case 0:
        if (GetGameMode_800A6D50(0) != 1 && areaReload_80082670 == 0)
        {
            break;
        }
        if (battleFlags_800B1228 & 0x4000)
        {
            break;
        }
        if (areaPreload_80091C40[1] != areaPreload_80091C40[0])
        {
            req.flags_0 = 0xC69;
            req.fileId_4 = mapTable_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0][saveData_8008B570.mapId_2E4[2].field_0].f2;
            req.offset_8 = mapAreas_80082674[areaPreload_80091C40[0] * 3];
            req.size_C = mapAreas_80082674[areaPreload_80091C40[0] * 3 + (areaReload_80082670 ? 2 : 1)];
            req.dest_10 = 0;
            req.params_14 = 0;
            req.paramsSize_18 = 0;
            req.callback_1C = OnRoomDataLoaded_80028C60;
            st[1] = QueueFileRequest_8003BC84(&req);
            areaPreloading_80082678 = 1;
            areaPreload_80091C40[1] = areaPreload_80091C40[0];
            break;
        }
        if (saveData_8008B570.mapId_2E4[3].field_2 != saveData_8008B570.mapId_2E4[3].field_0)
        {
            load = 1;
            wait = 2;
            if (areaReload_80082670 == 0)
            {
                FreeMapArea_8002728C();
            }
            if (areaPreloading_80082678)
            {
                if (areaPreload_80091C40[0] == saveData_8008B570.mapId_2E4[3].field_0)
                {
                    load = 0;
                }
                wait = ConsumeFileRequest_8003BFD0(st[1], 1);
                areaPreloading_80082678 = 0;
            }
            if (load)
            {
                req2.flags_0 = 0x46C;
                req2.fileId_4 = mapTable_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0][saveData_8008B570.mapId_2E4[2].field_0].f2;
                req2.offset_8 = mapAreas_80082674[saveData_8008B570.mapId_2E4[3].field_0 * 3];
                req2.size_C = mapAreas_80082674[saveData_8008B570.mapId_2E4[3].field_0 * 3 + (areaReload_80082670 ? 2 : 1)];
                req2.dest_10 = 0;
                req2.params_14 = 0;
                req2.paramsSize_18 = 0;
                req2.callback_1C = OnRoomDataLoaded_80028C60;
                st[1] = QueueFileRequest_8003BC84(&req2);
            }
            areaLoadIds_80091CB8[7] = saveData_8008B570.mapId_2E4[3].field_0;
            areaLoadIds_80091CB8[6] = saveData_8008B570.mapId_2E4[3].field_0;
            saveData_8008B570.mapId_2E4[3].field_2 = saveData_8008B570.mapId_2E4[3].field_0;
            if (wait)
            {
                if (areaReload_80082670 == 0)
                {
                    SetLoadFadeFlag_80027478(4, 1);
                }
                eventDispatchHalt_8008B540 = 1;
                st[0] = 1;
            }
            break;
        }
        if (areaLoadIds_80091CB8[6] != areaLoadIds_80091CB8[7])
        {
            req3.flags_0 = 0x450;
            req3.fileId_4 = mapTable_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0][saveData_8008B570.mapId_2E4[2].field_0].f2;
            req3.offset_8 = mapAreas_80082674[areaLoadIds_80091CB8[6] * 3];
            req3.size_C = 0;
            req3.dest_10 = 0;
            req3.params_14 = 0;
            req3.paramsSize_18 = 0;
            req3.callback_1C = 0;
            areaLoadIds_80091CB8[7] = areaLoadIds_80091CB8[6];
            st[1] = QueueFileRequest_8003BC84(&req3);
            st[0] = 2;
        }
        break;
    case 1:
        if (GetFileRequestStatus_8003BE30(st[1]) == 0)
        {
            areaReload_80082670 = 0;
            mapJustLoaded_80082668 = 0;
            InitRoomCamera_80028DC0();
            SetLoadFadeFlag_80027478(4, 0);
            st[0] = 0;
        }
        else
        {
            eventDispatchHalt_8008B540 = 1;
        }
        break;
    case 2:
        if (GetFileRequestStatus_8003BE30(st[1]) == 0)
        {
            st[0] = 0;
        }
        break;
    }
}
// the 0x104-byte header of a map file (OnMapFileLoaded_80028808)
typedef struct
{
    LevantPos start_0; // where Levant starts
    char pad_14[0xF0];
} MapFileHeader;
typedef struct
{
    char pad_0[0xC];
    int fC;
} MapAreaEntryb;
extern void LoadEventData_800A5628(int a0, int* a1, int a2);
extern void MarkSharedEdges_800B73C0(MapMesh* a0, int a1);
extern int FindTriAtXZ_800B76B8(MapMesh* a0, Vec3i* a1);
extern short savedLevantRot_80091CA8[];
extern EventNode* gameTask_8008B4A4; // the GAME overlay task
// Matched
void OnMapFileLoaded_80028808(void* params, int* data)
{
    MapFileHeader hdr;
    int size;
    int* cur;
    unsigned int cnt;
    unsigned int i;
    unsigned int j;
    int a;
    int c;
    int c2;
    cur = data;
    size = *cur++;
    if (size != 0 && dword_80091C8C == 0)
    {
        MemCopy_800403E8(mapCodeAddr_80073210, cur, size);
        mapCallback_80091CB4 = ((MapAreaEntryb*)mapTable_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0])[saveData_8008B570.mapId_2E4[2].field_0].fC;
    }
    cur = (int*)((char*)cur + size);
    mapJustLoaded_80082668 = 1;
    mapHasCode_8008266C = size != 0;
    cnt = *cur++;
    for (j = 0; j < cnt; j++)
    {
        a = *cur++;
        c = *cur++;
        c2 = *cur++;
        LoadEventData_800A5628(a, cur, c);
        cur = (int*)((char*)cur + c2);
    }
    mapState_8008B500.id_0 = saveData_8008B570.mapId_2E4[2].field_0;
    mapState_8008B500.nMeshes_4 = *cur++;
    mapState_8008B500.f8_8 = *cur++;
    MemCopy_800403E8(&hdr, cur, sizeof(hdr));
    cur = LoadMapMeshes_80027A88(&mapState_8008B500.meshes_C, &mapState_8008B500.nMeshes_4, &mapHeap_80091C68, (char*)cur + 0x104);
    MarkSharedEdges_800B73C0(mapState_8008B500.meshes_C, mapState_8008B500.nMeshes_4);
    cur = LoadMapMeshes_80027A88(&mapState_8008B500.ents_14, &mapState_8008B500.nEnts_10, &mapHeap_80091C68, cur);
    MarkSharedEdges_800B73C0(mapState_8008B500.ents_14, mapState_8008B500.nEnts_10);
    AllocMapWallFlags_800275E8(&mapState_8008B500.entFlags_18, mapState_8008B500.nEnts_10, &mapHeap_80091C68);
    cur = LoadMapMeshes_80027A88(&mapState_8008B500.mesh_28, &mapState_8008B500.nMesh_24, &mapHeap_80091C68, cur);
    MarkSharedEdges_800B73C0(mapState_8008B500.mesh_28, mapState_8008B500.nMesh_24);
    cur = LoadMapMeshes_80027A88(&mapState_8008B500.ents_30, &mapState_8008B500.nEnts_2C, &mapHeap_80091C68, cur);
    MarkSharedEdges_800B73C0(mapState_8008B500.ents_30, mapState_8008B500.nEnts_2C);
    AllocMapWallFlags_800275E8(&mapState_8008B500.entFlags_34, mapState_8008B500.nEnts_2C, &mapHeap_80091C68);
    cur = LoadMapMeshes_80027A88(&mapState_8008B500.meshes20_20, &mapState_8008B500.nMeshes20_1C, &mapHeap_80091C68, cur);
    MarkSharedEdges_800B73C0(mapState_8008B500.meshes20_20, mapState_8008B500.nMeshes20_1C);
    cnt = cur[0];
    LoadMapFtg_80027708(cur, (int)&mapHeap_80091C68);
    cur = (int*)((char*)cur + cnt);
    cnt = *cur++;
    LoadTiy_80028E74(0, 0, 0, (int*)cur, (int)&mapHeap_80091C68);
    cur = LoadMapSpawns_80027650((int*)((char*)cur + cnt), 0, &mapHeap_80091C68);
    mapAreas_80082674 = ListAlloc_8003FDC0(&mapHeap_80091C68, mapState_8008B500.nMeshes_4 * 12);
    MemCopy_800403E8(mapAreas_80082674, cur, mapState_8008B500.nMeshes_4 * 12);
    if (mapHasCode_8008266C && dword_80091C5C && dword_80091C8C == 0 && mapCallback_80091CB4)
    {
        ((void (*)(int))mapCallback_80091CB4)(0);
    }
    if (useSavedLevantPos_80091C98)
    {
        saveData_8008B570.levant_7A8.pos.x = savedLevantPos_80091C78.pos[0];
        saveData_8008B570.levant_7A8.pos.y = savedLevantPos_80091C78.pos[1];
        saveData_8008B570.levant_7A8.pos.z = savedLevantPos_80091C78.pos[2];
        saveData_8008B570.levant_7A8.rot.vx = savedLevantRot_80091CA8[0];
        saveData_8008B570.levant_7A8.rot.vy = savedLevantRot_80091CA8[1];
        saveData_8008B570.levant_7A8.rot.vz = savedLevantRot_80091CA8[2];
    }
    useSavedLevantPos_80091C98 = 0;
    if (useMapStartPos_80091C94)
    {
        saveData_8008B570.levant_7A8.pos.x = hdr.start_0.pos.x;
        saveData_8008B570.levant_7A8.pos.y = hdr.start_0.pos.y;
        saveData_8008B570.levant_7A8.pos.z = hdr.start_0.pos.z;
        saveData_8008B570.levant_7A8.rot.vx = hdr.start_0.rot.vx;
        saveData_8008B570.levant_7A8.rot.vy = hdr.start_0.rot.vy;
        saveData_8008B570.levant_7A8.rot.vz = hdr.start_0.rot.vz;
    }
    useMapStartPos_80091C94 = 0;
    // stays an int* view: savedLevantPos_80091C78.mapIdx addresses the field as sym+12 and changes the code
    if (((int*)&savedLevantPos_80091C78)[3] >= 0)
    {
        saveData_8008B570.mapId_2E4[3].field_0 = *(short*)&((int*)&savedLevantPos_80091C78)[3];
        saveData_8008B570.mapId_2E4[3].field_2 = -1;
        ((int*)&savedLevantPos_80091C78)[3] = -1;
    }
    else
    {
        for (i = 0; i < (int)mapState_8008B500.nMeshes_4; i++)
        {
            if (FindTriAtXZ_800B76B8(&mapState_8008B500.meshes_C[i], &saveData_8008B570.levant_7A8.pos) >= 0)
            {
                saveData_8008B570.mapId_2E4[3].field_0 = i;
                saveData_8008B570.mapId_2E4[3].field_2 = -1;
                break;
            }
        }
    }
    ((GameTaskState*)gameTask_8008B4A4->entry.buffer)->mapPoint_84 = saveData_8008B570.mapId_2E4[3].field_0;
}
