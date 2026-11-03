#ifndef _TU_80043AF8_H_
#define _TU_80043AF8_H_

#include "gte.h"

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

#endif
