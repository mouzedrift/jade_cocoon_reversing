#ifndef _TU_8004B0A8_H_
#define _TU_8004B0A8_H_

#include "tu_8001EA48.h"

// FTG object renderer state, kept in the scratchpad at 0x1F800214 (sub_8004C7BC)
typedef struct FtgDrawCtx
{
    DR_TPAGE tpage_0; // queued behind every polygon
    long otz_8;       // gte_stotz
    long dq_C;        // depth cue (IR0) for gte_dpcs / gte_ncds
    long opz_10;      // gte_stopz (nclip)
    long opz2_14;     // nclip of the second triangle of a quad
    unsigned char* next_18; // next free primitive
    int pad_1C;
    int flags_20; // bit 0: lit (normal + ncds), bit 4: semi-transparent
} FtgDrawCtx;

// polygon templates built in the scratchpad at 0x1F8001E0 before being copied to next_18
#define FTG_PRIM_SCRATCH getScratchAddr(0x78)
#define FTG_DRAW_CTX ((FtgDrawCtx*)getScratchAddr(0x85))

#endif
