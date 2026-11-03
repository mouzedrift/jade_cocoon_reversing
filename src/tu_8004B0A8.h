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
    unsigned long clutAdd_1C; // added to the textured kinds' u0 / v0 / clut word (CLUT row offset)
    int flags_20; // bit 0: lit (normal + ncds), bit 4: semi-transparent, bits 5-6: blend mode for textured kinds
} FtgDrawCtx;

// a projected FTG sprite vertex (sub_8004C4F0), three per sprite triple
typedef struct FtgSpriteVtx
{
    long sxy_0;
    long sz_4;
    unsigned short uv_8;
    unsigned short pad_A;
    unsigned long rgbc_C;
    long pad_10;
} FtgSpriteVtx;
extern FtgSpriteVtx* dword_80098180;        // next free sprite vertex
extern FtgSpriteVtx* dword_800987D8[][56];  // per slot: the projected vertices, three per triple
extern unsigned long dword_8009AAD8;        // tpage / clut word of the textured sprites

// draws an FTG object with the current GTE matrices (flags: see FtgDrawCtx.flags_20, bits 8-15 CLUT
// row offset, bit 7 + bits 16-31 depth cue); slot indexes dword_800987D8
extern void sub_8004C7BC(FtgObject* obj, unsigned long* ot, int flags, int slot);

// polygon templates built in the scratchpad at 0x1F8001E0 before being copied to next_18
#define FTG_PRIM_SCRATCH getScratchAddr(0x78)
#define FTG_DRAW_CTX ((FtgDrawCtx*)getScratchAddr(0x85))

#endif
