#ifndef _TU_80043AF8_H_
#define _TU_80043AF8_H_

#include "gte.h"
#include "tu_8001EA48.h"
#include "tu_8004B0A8.h"

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

// polygons strung between projected sprite vertices (dword_800987D8[slot][idx], sub_800459E4 / sub_80045E48)
typedef struct
{
    unsigned short slot;
    unsigned short idx;
} FtgVtxRef;
typedef struct
{
    FtgVtxRef v[4];
} FtgQuadRef;
typedef struct
{
    unsigned int count;
    FtgQuadRef* items;
} FtgQuadRefList;
// their state, in the scratchpad at 0x1F800214
typedef struct
{
    int attr_0;   // slot's attribute (SVECTOR pad of the slot table): bit 1 visible, bit 2 opaque, bit 4 semi-trans
    long otz_4;
    long opz_8;
    long opz2_C;
    int slot_10;
    unsigned char* next_14;
    FtgSpriteVtx* v_18[4];
    FtgQuadRef* ref_28;
} FtgQuadCtx;
#define FTG_QUAD_CTX ((FtgQuadCtx*)getScratchAddr(0x85))
// sub_80045E48 (untextured quads), same place
typedef struct
{
    long opz_0;
    long opz2_4;
    DR_TPAGE tpage_8;
    int pad_10[8];
    unsigned char* next_30;
    FtgSpriteVtx* v_34[4];
    FtgQuadRef* ref_44;
} FtgQuadG4Ctx;
#define FTG_QUAD_G4_CTX ((FtgQuadG4Ctx*)getScratchAddr(0x85))

// draws an FTG object at pos / rot (optional per-axis scale) through sub_8004C7BC
extern void sub_80044D0C(FtgObject* obj, unsigned long* ot, VECTOR* pos, SVECTOR* rot, void* cam, int flags, VECTOR* scale, int slot);

#endif
