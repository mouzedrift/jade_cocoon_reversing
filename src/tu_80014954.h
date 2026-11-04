#ifndef _TU_80014954_H_
#define _TU_80014954_H_

// the files the overlays are loaded from, and where their addresses go
typedef struct
{
    int fileIdx;
    unsigned int** ppDest;
} OverlayEntry;
extern OverlayEntry overlays_8007D9E8[];

// an item of a menu window (the tables of tu_8002BE10 / tu_8002CE28)
typedef struct
{
    unsigned short flags;
    short pad_2;
    int f4;
    SPRT** sprts_8;
    DR_TPAGE** tpages_C;
    short x;
    short y;
    char pad_14[8];
} MenuItem_1C;

// camera offsets (tu_80036528)
typedef struct
{
    short x0;
    short y0;
    short z0;
    short pad_6;
    int field_8;
    short x1;
    short y1;
    short z1;
    short pad_12;
} CamOffset;

// a step of a pad vibration pattern (vibrationPatterns_80083B30, tu_80036528)
typedef struct
{
    unsigned short field_0;
    unsigned char field_2;
    unsigned char field_3;
} PadVibEntry;

typedef struct
{
    unsigned short x;
    unsigned short y;
} Pos16;

#endif
