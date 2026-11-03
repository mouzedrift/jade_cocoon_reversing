#ifndef _TU_8001EA48_H_
#define _TU_8001EA48_H_

#include "actor.h"

// ---------------------------------------------------------------------------------------------
// FTG model objects (LoadFtgObject_80022458). A file object is a 0x28-byte header of ten
// primitive counts followed by records of a 4-byte primitive header (FtgPrimHeader) and the
// primitive body; the loader converts the bodies to the run-time layouts below.

typedef struct
{
    unsigned char type_0; // 0..7 polygon kinds below, 8 / 9 sprite groups
    unsigned char pad_1[2];
    unsigned char flags_3; // bit 1: semi-transparent; copied to the polygon's code byte
} FtgPrimHeader;

// run-time vertex / normal: position plus a packed u | v << 8 (textured kinds only)
typedef struct
{
    short x;
    short y;
    short z;
    unsigned short uv;
} FtgVert;

// file vertex / normal: the uv pair is two bytes
typedef struct
{
    short x;
    short y;
    short z;
    unsigned char u;
    unsigned char v;
} FtgSrcVert;

// colour + code byte (the code byte holds FtgPrimHeader.flags_3)
typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char code;
} FtgColor;

// texture page / clut words as stored in the file (relocated by RelocateTPageClut_80022AE8)
typedef struct
{
    unsigned short tpage;
    unsigned short clut;
} FtgSrcTex;

// type 0: flat triangle (file and run-time layouts are the same)
typedef struct FtgPolyF3
{
    FtgColor c;
    FtgVert n;
    FtgVert v[3];
} FtgPolyF3;

// type 1: gouraud triangle
typedef struct FtgPolyG3
{
    FtgColor c[3];
    FtgVert n[3];
    FtgVert v[3];
} FtgPolyG3;
typedef struct FtgSrcPolyG3
{
    FtgColor c[3];
    struct
    {
        FtgVert n;
        FtgVert v;
    } p[3];
} FtgSrcPolyG3;

// type 2: flat textured triangle
typedef struct FtgPolyFT3
{
    FtgColor c;
    unsigned char u0, v0;
    unsigned short clut;
    unsigned char u1, v1;
    unsigned short tpage;
    unsigned char u2, v2;
    unsigned short pad;
    FtgVert n;
    FtgVert v[3];
} FtgPolyFT3;
typedef struct FtgSrcPolyFT3
{
    FtgSrcTex tex;
    FtgSrcVert n;
    FtgSrcVert v[3];
} FtgSrcPolyFT3;

// type 3: gouraud textured triangle
typedef struct FtgPolyGT3
{
    FtgColor c[3];
    unsigned char u0, v0;
    unsigned short clut;
    unsigned char u1, v1;
    unsigned short tpage;
    unsigned char u2, v2;
    unsigned short pad;
    FtgVert n[3];
    FtgVert v[3];
} FtgPolyGT3;
typedef struct FtgSrcPolyGT3
{
    FtgSrcTex tex;
    FtgColor c[3];
    struct
    {
        FtgSrcVert n;
        FtgSrcVert v;
    } p[3];
} FtgSrcPolyGT3;

// type 4: flat quad (file and run-time layouts are the same)
typedef struct FtgPolyF4
{
    FtgColor c;
    FtgVert n;
    FtgVert v[4];
} FtgPolyF4;

// type 5: gouraud quad
typedef struct FtgPolyG4
{
    FtgColor c[4];
    FtgVert n[4];
    FtgVert v[4];
} FtgPolyG4;
typedef struct FtgSrcPolyG4
{
    FtgColor c[4];
    struct
    {
        FtgVert n;
        FtgVert v;
    } p[4];
} FtgSrcPolyG4;

// type 6: flat textured quad
typedef struct FtgPolyFT4
{
    FtgColor c;
    unsigned char u0, v0;
    unsigned short clut;
    unsigned char u1, v1;
    unsigned short tpage;
    unsigned char u2, v2;
    unsigned char u3, v3;
    FtgVert n;
    FtgVert v[4];
} FtgPolyFT4;
typedef struct FtgSrcPolyFT4
{
    FtgSrcTex tex;
    FtgSrcVert n;
    FtgSrcVert v[4];
} FtgSrcPolyFT4;

// type 7: gouraud textured quad
typedef struct FtgPolyGT4
{
    FtgColor c[4];
    unsigned char u0, v0;
    unsigned short clut;
    unsigned char u1, v1;
    unsigned short tpage;
    unsigned char u2, v2;
    unsigned char u3, v3;
    FtgVert n[4];
    FtgVert v[4];
} FtgPolyGT4;
typedef struct FtgSrcPolyGT4
{
    FtgSrcTex tex;
    FtgColor c[4];
    struct
    {
        FtgSrcVert n;
        FtgSrcVert v;
    } p[4];
} FtgSrcPolyGT4;

typedef struct FtgPolyF3List { short count; short pad; FtgPolyF3* items; } FtgPolyF3List;
typedef struct FtgPolyG3List { short count; short pad; FtgPolyG3* items; } FtgPolyG3List;
typedef struct FtgPolyFT3List { short count; short pad; FtgPolyFT3* items; } FtgPolyFT3List;
typedef struct FtgPolyGT3List { short count; short pad; FtgPolyGT3* items; } FtgPolyGT3List;
typedef struct FtgPolyF4List { short count; short pad; FtgPolyF4* items; } FtgPolyF4List;
typedef struct FtgPolyG4List { short count; short pad; FtgPolyG4* items; } FtgPolyG4List;
typedef struct FtgPolyFT4List { short count; short pad; FtgPolyFT4* items; } FtgPolyFT4List;
typedef struct FtgPolyGT4List { short count; short pad; FtgPolyGT4* items; } FtgPolyGT4List;

// sprite / point record (types 8 and 9, 0x14 bytes at run time)
typedef struct FtgSprite
{
    FtgColor c;  // code: 0 (type 8) or the primitive's flags (type 9)
    FtgVert p0;  // uv unused
    FtgVert p1;  // uv: 0 (type 8) or the file's u | v << 8 (type 9)
} FtgSprite;
// file records: type 8 drops h[3] / h[7], type 9 carries the uv in p1
typedef struct
{
    FtgVert p0;
    FtgVert p1;
    FtgColor c;
} FtgSrcSprite8;
typedef struct
{
    FtgVert p0;
    FtgSrcVert p1;
    FtgColor c;
} FtgSrcSprite9;
// type 8 / 9 file bodies: a count and the records (type 9 has a texture page / clut first)
typedef struct FtgSrcSprites8
{
    int count_0;
    FtgSrcSprite8 items_4[1];
} FtgSrcSprites8;
typedef struct FtgSrcSprites9
{
    int count_0;
    unsigned short tpage_4;
    unsigned short clut_6;
    FtgSrcSprite9 items_8[1];
} FtgSrcSprites9;

// per-record sprite groups gathered while loading, merged into FtgObject by sub_80022CC4
typedef struct
{
    int count;
    FtgSprite* items;
} FtgSpriteGroup8;
typedef struct
{
    int count;
    unsigned short tpage;
    unsigned short clut;
    FtgSprite* items;
} FtgSpriteGroup9;
typedef struct
{
    short count;
    FtgSpriteGroup8* groups;
} FtgSpriteGroups8;
typedef struct
{
    short count;
    FtgSpriteGroup9* groups;
} FtgSpriteGroups9;

// file object header: primitive counts by type (sizes above), then the records
typedef struct
{
    int counts_0[10];
} FtgSrcObjectHeader;

// loaded FTG object (0x54 bytes): one allocation (at f3_0.items) holds all the lists
typedef struct FtgObject
{
    FtgPolyF3List f3_0;
    FtgPolyG3List g3_8;
    FtgPolyFT3List ft3_10;
    FtgPolyGT3List gt3_18;
    FtgPolyF4List f4_20;
    FtgPolyG4List g4_28;
    FtgPolyFT4List ft4_30;
    FtgPolyGT4List gt4_38;
    int spriteCount_40;
    FtgSprite* sprites_44;
    int texSpriteCount_48;
    unsigned short tpage_4C;
    unsigned short clut_4E;
    FtgSprite* texSprites_50;
} FtgObject;

#endif
