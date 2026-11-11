#ifndef _TU_80043AF8_H_
#define _TU_80043AF8_H_

#include "gte.h"
#include "engine.h"
#include "model.h"
#include "ftg_draw.h"

// billboard sprite projection (DrawBillboard_80043B8C), in the scratchpad at 0x1F800214
typedef struct
{
    short x_0; // projected centre
    unsigned short y_2;
    SVECTOR rel_4; // position relative to the camera eye
    int otz_C;    // gte_stszotz
    int w_10;      // projected size
    int h_14;
    unsigned char shade_18;
} BillboardScratch;
#define BILLBOARD_SCRATCH ((BillboardScratch*)getScratchAddr(0x85))

// wireframe triangles (DrawWireTris_80045534): edges whose vertex pad is set are drawn grey
typedef struct
{
    SVECTOR v[3]; // pad: edge v[i] -> v[i + 1] is an inner edge
    int pad_18[2];
} WireTri;
typedef struct
{
    short count;
    short pad;
    WireTri* items;
} WireTriList;

// rotated / scaled sprite (DrawRotSprite_80044010), in the scratchpad at 0x1F800214
typedef struct
{
    POLY_FT4 prim_0;
    short x_28; // projected centre
    short y_2A;
    SVECTOR rel_2C;  // position relative to the camera eye
    LVec3 ofs_34;    // sprite offset (model space)
    LVec3 wofs_40;   // sprite offset rotated (returned; ApplyMatrixLV output)
    int otz_4C;
    int pad_50[3];
    int x0_5C; // corner offsets on screen
    int y0_60;
    int x1_64;
    int y1_68;
    int cos_6C;
    int sin_70;
    int pad_74;
    MATRIX rot_78; // the caller's rotation matrix
} RotSpriteScratch;
#define ROT_SPRITE_SCRATCH ((RotSpriteScratch*)getScratchAddr(0x85))

// POLY_GT4 as the sprite-vertex quads build it (colours and uv as words / halves)
typedef struct
{
    O_TAG;
    unsigned int rgbc0;
    short x0, y0;
    unsigned short uv0;
    unsigned short clut;
    unsigned int rgbc1;
    short x1, y1;
    unsigned short uv1;
    unsigned short tpage;
    unsigned int rgbc2;
    short x2, y2;
    unsigned int uv2;
    unsigned int rgbc3;
    short x3, y3;
    unsigned int uv3;
} FtgPrimGT4;
// their state, in the scratchpad at 0x1F800214
typedef struct
{
    int attr_0;   // slot's attribute (SVECTOR pad of the slot table): bit 1 visible, bit 2 opaque, bit 4 semi-trans
    int otz_4;
    int opz_8;
    int opz2_C;
    int slot_10;
    unsigned char* next_14;
    FtgSpriteVtx* v_18[4];
    FtgQuadRef* ref_28;
} FtgQuadCtx;
#define FTG_QUAD_CTX ((FtgQuadCtx*)getScratchAddr(0x85))
// DrawSpriteVtxQuadsG4_80045E48 (untextured quads), same place
typedef struct
{
    int opz_0;
    int opz2_4;
    DR_TPAGE tpage_8;
    int pad_10[8];
    unsigned char* next_30;
    FtgSpriteVtx* v_34[4];
    FtgQuadRef* ref_44;
} FtgQuadG4Ctx;
#define FTG_QUAD_G4_CTX ((FtgQuadG4Ctx*)getScratchAddr(0x85))

// skeletal animation
typedef struct
{
    int pad_0;
    int n_4; // bones; rot holds n + 2 entries per frame ([1] is the root translation)
    int pad_8;
    int pad_C;
    void* cues_10; // as ModelAnim
    short* pos; // x, y, z per bone
    short* rot; // x, y, z per entry
} AnimPose;

typedef struct
{
    short parent; // depth in the hierarchy (its matrix is SKEL_MATS[parent + 2]); < 0 ends the list
    unsigned char idx;
    unsigned char scale_3; // index into AnimSkel.base (used when parent > 0)
    short ftg_4;           // the bone's FTG object (AnimSkel.ftg_0) and DrawFtgObject slot
    short flags_6;         // bit 1: drawn; the rest go to DrawFtgObject's flags
} AnimBone;

// skeleton draw arguments (Actor.draw_164 / ActorDrawArgs)
typedef struct
{
    FtgObject* ftg_0; // one per bone (AnimBone.ftg_4)
    VECTOR* pos_4;
    SVECTOR* rot_8;
    AnimBone* bones;
    SVECTOR* base; // per-bone scale (pad != 0: scale the bone's matrix)
    AnimPose* pose_14;
    int frame_18;
    int drawMode_1C;
    LVec3* bonePos_20; // out: world position per bone
    VECTOR* scale_24;  // optional per-axis scale (rotation matrix diagonal)
    OT_TYPE* ot_28;
    PointLight* light_2C;
} AnimSkel;

// the bone matrices in the scratchpad (0x1F800040): [0] the camera, [1] the model root, [depth + 2] a bone
#define SKEL_MATS ((MATRIX*)getScratchAddr(0x10))

// axis of a rotation matrix (for BasisFromAxis_8004B0A8)
void GetRotationAxis_8004AD44(MATRIX* in, VECTOR* out);

extern MATRIX boneMatrices_80096120[]; // per-bone draw matrices

// draws an FTG object at pos / rot (optional per-axis scale) through DrawFtgObject_8004C7BC
extern void DrawFtgObjectAt_80044D0C(FtgObject* obj, OT_TYPE* ot, VECTOR* pos, SVECTOR* rot, PointLight* light, int flags, VECTOR* scale, int slot);

extern int unused_80096620[2];

// billboard sprite with an RGB tint (DrawBillboardRgb_80043DE0)
int DrawBillboardRgb_80043DE0(POLY_FT4* poly, VECTOR* pos, short* size, unsigned char* rgb);

// rotated / scaled sprite: uv, size and pivot are an EffectSpriteFrame's (u_0, w_4, pivotX_8); returns the
// scratchpad position
VECTOR* DrawRotSprite_80044010(POLY_FT4* src, VECTOR* pos, SVECTOR* rot, short* uv, short* size, short* pivot, short* scale,
                               SVECTOR* ofs, unsigned char* rgb, short flags, int abr, OT_TYPE* ot);

#endif
