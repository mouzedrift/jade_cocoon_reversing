#ifndef _TU_80043AF8_H_
#define _TU_80043AF8_H_

#include "gte.h"
#include "tu_8001EA48.h"

// billboard sprite projection (sub_80043B8C), in the scratchpad at 0x1F800214
typedef struct
{
    short x_0; // projected centre
    unsigned short y_2;
    SVECTOR rel_4; // position relative to the camera eye
    long otz_C;    // gte_stszotz
    int w_10;      // projected size
    int h_14;
    unsigned char shade_18;
} BillboardScratch;
#define BILLBOARD_SCRATCH ((BillboardScratch*)getScratchAddr(0x85))

// wireframe triangles (sub_80045534): edges whose vertex pad is set are drawn grey
typedef struct
{
    SVECTOR v[3]; // pad: edge v[i] -> v[i + 1] is an inner edge
    long pad_18[2];
} WireTri;
typedef struct
{
    short count;
    short pad;
    WireTri* items;
} WireTriList;

// draws an FTG object at pos / rot (optional per-axis scale) through sub_8004C7BC
extern void sub_80044D0C(FtgObject* obj, unsigned long* ot, VECTOR* pos, SVECTOR* rot, void* cam, int flags, VECTOR* scale, int slot);

#endif
