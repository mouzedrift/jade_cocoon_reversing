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

// per-record sprite groups gathered while loading, merged into FtgObject by MergeFtgSpriteGroups_80022CC4
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
extern FtgObject* publicFtg_8008D4D0; // the public FTG file (LoadPublicTiyAndFtg_800407D0)

// ---------------------------------------------------------------------------------------------
// model loader task (the buffer of the modelLoaderTask_8008B54C event entry)
typedef struct
{
    int loaded_0; // LoadModel_80025200 issued
    int id_4;     // -1: free slot
    int sel_8;
    int arg_C;
    int animSet_10; // < 0: none
} ModelLoadSlot;
typedef struct ModelLoader
{
    int state_0;
    int done_4;
    ModelList* models_8;
    ModelLoadSlot slots_C[4];
} ModelLoader;

// ---------------------------------------------------------------------------------------------
// model files (modelDescs_800824CC, LoadModel_80025200 / OnModelFileLoaded_80025D7C)

typedef struct
{
    unsigned short offset; // sectors into the DATA.001 file
    unsigned short size;   // sectors
} ModelSectorSpan;

// model file description (one per model id); the tables after animFlags_14 are variable length:
// animFlags_14[animCount_12], animation spans[animCount_12], then the animation set and alternate
// FTG tables (a count followed by spans)
typedef struct ModelDesc
{
    unsigned short fileId_0;
    ModelSectorSpan header_2;
    ModelSectorSpan tex_6;
    ModelSectorSpan ftg_A;
    ModelSectorSpan anims_E;
    unsigned short animCount_12;
    unsigned short animFlags_14[1]; // low byte: initially loaded
} ModelDesc;
extern ModelDesc* modelDescs_800824CC[];

// VRAM placement of one model slot (the 16-byte entries of the ModelList.vram_C table)
typedef struct ModelVramSlot
{
    short field_0;
    short id_2; // -1 ends the table
    short reloc_4[6]; // RelocateTPageClut_80022AE8 table
} ModelVramSlot;
extern ModelVramSlot* modelLoaderVram_8007DC70; // the model loader list's slots

typedef struct
{
    int size_0;
    char data_4[1];
} ModelHeaderSection;
typedef struct
{
    int count_0;
    int offsets_4[1]; // from the section start
} ModelAnimSection;
typedef struct
{
    int count_0;
    struct
    {
        int id;
        int offset; // from the section start
    } items_4[1];
} ModelAnimSetSection;

// OnModelFileLoaded_80025D7C parameters (FileRequestDesc.params_14, 0x3C bytes are copied)
typedef struct ModelLoadParams
{
    unsigned int flags_0; // sections present: 1 header, 2 textures, 4 FTG, 8 anims, 0x10 one anim, 0x20 anim set, 0x40 alternate FTG
    ModelDesc* desc_4;
    int sel_8;   // texture slot, -1: none
    int mode_C;  // which animations start loaded (LoadModelAnims_800261C8)
    int animIdx_10;
    Model* model_14;
    ModelVramSlot* vram_18;
    ModelHeaderSection* header_1C;
    int* tim_20;
    int* ftg_24;
    ModelAnimSection* anims_28;
    char* anim_2C;
    ModelAnimSetSection* animSet_30;
    int* ftg2_34;
    unsigned char* extra_38;
    int pad_3C;
} ModelLoadParams;

// model header section (Model.header_4C, copied by LoadModelHeader_80026014)
typedef struct
{
    int offset_0;  // GetModelActorAnims_80024E38: data at offset_0 + 4
    int offset_4;  // GetModelEffectTable_80024E64
    int records_8; // chain of ModelHeaderRecord at records_8 + 8 (GetModelHeaderRecord_80024FA8)
} ModelHeaderData;
typedef struct
{
    int offsets_0[5]; // from the record start (GetModelBaseScale_80024E90..sub_80024F70)
    int size_14;      // to the next record
} ModelHeaderRecord;

// sections of Model.header_4C; what each one holds depends on the model kind
extern void* GetModelActorAnims_80024E38(Model* p);
extern void* GetModelEffectTable_80024E64(Model* p);
extern void* GetModelBaseScale_80024E90(Model* p, int n);
extern void* GetModelBoneScale_80024EC8(Model* p, int n);
extern void* sub_80024F00(Model* p, int n);
extern void* sub_80024F38(Model* p, int n);
extern void* sub_80024F70(Model* p, int n);

// ---------------------------------------------------------------------------------------------
// effect files (LoadEffectFile_80020DDC / OnEffectFileLoaded_80020F5C)

// FTG material list (AllocFtgMatList_80021DF0 / LoadFtgMatList_80021E4C; also Model.mats_5C)
typedef struct FtgMatList
{
    int count_0;
    unsigned short (*items_4)[8];
} FtgMatList;

// ---------------------------------------------------------------------------------------------
// loaded models (InitModelList_80024ADC, LoadModel_80025200, FreeModel_80024C48)

// an FTG object saved by SaveModelFtgs_80024FFC before it gets swapped (Model.saved_64)
typedef struct
{
    int id_0; // index into Model.ftg_50
    FtgObject ftg_4;
} ModelSavedFtg;

// FTG object swap of the alternate set (Model.swaps_6C, ApplyModelFtgSwaps_80025C38)
typedef struct
{
    short dst_0; // index into Model.ftg_50
    short src_2; // < Model.ftgCount_3C: Model.ftg_50 index, else Model.ftg2_68 index + ftgCount_3C
} ModelFtgSwap;

// one model of a ModelList (0x70 bytes). The first 0x30 bytes double as the model's file request
// list (AddFileRequest_80025D00 / AreFileRequestsDone_80024DC4)
struct Model
{
    ModelList* list_0;          // owner
    int requestCount_4;
    int requests_8[10];         // QueueFileRequest_8003BC84 ids
    int slot_30;                // index into the owner's items_8 / vram_C
    int texSel_34;              // texture slot (ModelLoadParams.sel_8)
    unsigned short id_38;       // 0xFFFF: free
    unsigned short refs_3A;     // AcquireModel_80024D70 count
    unsigned short ftgCount_3C;
    unsigned short animCount_3E;
    unsigned short savedCount_40;
    unsigned char ftg2Count_42;
    unsigned char swapCount_43;
    unsigned char* animLoaded_44; // per animation: data loaded
    int headerSize_48;
    ModelHeaderData* header_4C;
    FtgObject* ftg_50;          // ftgCount_3C objects
    ModelAnim* anims_54;        // animCount_3E animations
    int* animSet_58;            // count, then the animation ids it loaded (-1: was already loaded)
    FtgMatList mats_5C;
    ModelSavedFtg* saved_64;    // savedCount_40 entries
    FtgObject* ftg2_68;         // alternate FTG set, ftg2Count_42 objects (LoadModelAltFtgSection_8002651C)
    ModelFtgSwap* swaps_6C;     // swapCount_43 entries
};

struct ModelList
{
    int count_0;
    int heap_4;
    Model* items_8;
    ModelVramSlot* vram_C; // one per model, ended by id_2 == -1
};

// modelAnimRefs_800919A0 entry: users of a model's animations
typedef struct ModelAnimRef
{
    Model* model_0;
    int refs_4;
    unsigned short users_8[0x23]; // per animation: bit per user
} ModelAnimRef;
extern ModelAnimRef modelAnimRefs_800919A0[7];

// effect file index: the item of a kind (0 sprite, 1 model) with a given id (FindEffectIndex_80020F00)
typedef struct
{
    int kind;
    int id;
    int index;
} EffectPoint;

// one 28-byte sprite animation frame record (copied as byte groups)
typedef struct
{
    unsigned char b[4];
} struct_b4;
typedef struct
{
    unsigned char b[8];
} struct_b8;
typedef struct
{
    struct_b4 f0;
    struct_b4 f4;
    struct_b4 f8;
    struct_b4 fC;
    struct_b8 f10;
    struct_b4 f18;
} struct_1c;

// one sprite of an effect frame (0x1C bytes; LoadEffectSprite_80021298 copies it with the struct_1c byte-group view)
typedef struct EffectSpriteFrame
{
    short u_0; // texture position; u_0, w_4 and f8 are passed to DrawRotSprite_80044010 as three pointers
    short v_2;
    short w_4; // texture size
    short h_6;
    short f8;
    short fA;
    short size_C[2]; // w, h
    short pos_10[3]; // offset in BATTLE; tu_80014954 passes it as the colour argument
    short pad_16;
    unsigned char rgb_18[4];
} EffectSpriteFrame;

// 0x34-byte sprite animation of an effect file (EffectFile.sprites_20)
typedef struct EffectSprite
{
    int count_0;                  // frames
    unsigned char* frameCounts_4; // sprites per frame
    EffectSpriteFrame** frames_8;
    POLY_FT4 poly_C; // built by InitPolyFT4_80029A10 from the file
} EffectSprite;

// one key of an effect model animation (40 bytes)
typedef struct EffectKey
{
    short model_0; // index into EffectModel.ftg_4
    short alpha_2;
    int x_4;
    int y_8;
    int z_C;
    short rot_10[3];
    short pad16;
    int f18[3];
    int mode_24;
} EffectKey;

// 28-byte model of an effect file (EffectFile.models_28)
typedef struct EffectModel
{
    int ftgCount_0;
    FtgObject* ftg_4;
    FtgMatList mats_8;
    int keyCount_10;   // keys per frame
    int frameCount_14;
    EffectKey* keys_18; // frameCount_14 * keyCount_10 keys
} EffectModel;

typedef struct
{
    int count_0;
    void** images_4; // MDEC bitstreams
} MdecImageSet;

typedef struct
{
    void* dct_0;  // DecDCTBufSize of the largest image
    void* work_4; // 0x2000 bytes
} EffectMdecBuffers;

typedef struct EffectFile
{
    int request_0;
    int list_4[3]; // ListInit_8003FDB0 heap the file's data lives in
    void* data_10;
    int pointCount_14;
    EffectPoint* points_18;
    int spriteCount_1C;
    EffectSprite* sprites_20;
    int modelCount_24;
    EffectModel* models_28;
    int imageSetCount_2C;
    MdecImageSet* imageSets_30;
    EffectMdecBuffers mdec_34;
} EffectFile;
extern EffectFile effectFile_80091BD0; // effects shared by the field and battle (effect.c)
extern EffectFile battleEffectFile_80095468;      // the battle stage effect file (BATTLE.BIN)

// OnEffectFileLoaded_80020F5C parameters
typedef struct
{
    EffectFile* out_0;
    short reloc_4[6]; // RelocateTPageClut_80022AE8 table
    int sel_10;
} EffectLoadArg;

// overlay loader task state (the overlayLoaderTask_8008D4C0 entry buffer)
typedef struct OverlayLoader
{
    int wanted_0; // enum OverlayIds; 0x1D: none
    int loaded_4;
    int request_8; // LoadOverlay_80020BF8 file request
} OverlayLoader;

// map data block dword_8008D648 (sub_80027778 / sub_800278BC); fields named by offset
typedef struct
{
    int field_0;
    int count;
    unsigned short field_8;
    unsigned short field_A;
    unsigned short* items;
} struct_27778;
typedef struct
{
    unsigned char a;
    unsigned char b;
    unsigned short c;
} struct_4b;
typedef struct
{
    unsigned int count;
    struct_4b* items;
} struct_8_4b;
typedef struct
{
    short a;
    short b;
} struct_2s;
typedef struct
{
    int count_0;
    int field_4;
    int field_8;
    struct_27778* items_C;
    int listCount_10;
    struct_8_4b* lists_14;
    struct_2s* pairs_18;
} struct_8008D648;

// buffer of the GAME overlay task gameTask_8008B4A4 (overlays/game.h has the full view)
typedef struct
{
    char pad_0[0x84];
    int mapPoint_84; // saveData_8008B570.mapId_2E4[3] after a map load
} GameTaskState;


// ---------------------------------------------------------------------------------------------
// collision meshes of the current map (mapState_8008B500, filled by OnRoomDataLoaded_80028C60's loader)

typedef struct MapVtx
{
    short x_0;
    short y_2;
    short z_4;
    short pad_6;
} MapVtx;

typedef struct MapTri
{
    MapVtx v_0[3];
    short nx_18;
    short ny_1A;
    short nz_1C;
    short pad_1E;
} MapTri;

typedef struct MapMesh
{
    short nTris_0;
    short pad_2;
    MapTri* tris_4;
} MapMesh;

// a mesh block of a map file (LoadMapMeshes_80027A88): header, then per mesh a MapMeshRec and its MapTriRecs
typedef struct MapMeshFile
{
    int size_0; // of the whole block
    unsigned int count_4;
    int pad_8[2];
} MapMeshFile;

typedef struct MapMeshRec
{
    unsigned int nTris_0;
    char pad_4[0x24];
} MapMeshRec;

typedef struct MapTriRec
{
    int f0_0;
    int f4_4;
    MapVtx n_8;
    MapVtx v_10[3];
} MapTriRec;

int* LoadMapMeshes_80027A88(MapMesh** out, unsigned int* count, void* heap, MapMeshFile* hdr);

typedef struct MapState
{
    int id_0; // saveData_8008B570.mapId_2E4[2].field_0
    unsigned int nMeshes_4;
    int f8_8;
    MapMesh* meshes_C; // the floor, one mesh per area (saveData mapId_2E4[3])
    int nEnts_10;
    MapMesh* ents_14; // walls
    unsigned char* entFlags_18; // 1 = wall enabled
    int nMeshes20_1C;
    MapMesh* meshes20_20;
    int nMesh_24;
    MapMesh* mesh_28;
    int nEnts_2C;
    MapMesh* ents_30;
    unsigned char* entFlags_34;
    int ftgCount_38;
    FtgObject* ftg_3C;
} MapState;
extern MapState mapState_8008B500;

// 16-byte records loaded with the map (LoadMapSpawns_80027650)
typedef struct
{
    int count_0;
    int (*items_4)[4];
} MapList16;
extern MapList16 mapSpawns_80091C60;


// the loaders / relocators of the primitive kinds of an FTG model (LoadFtgObject_80022458)
typedef void (*FtgPrimRelocFn)(unsigned char* body, int a3);
typedef int (*FtgPrimLoadFn)(FtgPrimHeader* hdr, unsigned char* body, FtgObject* obj, int k, int h);
extern FtgPrimRelocFn ftgPrimRelocators_8007DB08[];
extern FtgPrimLoadFn ftgPrimLoaders_8007DAE0[];

int LoadFtgPolyF3_8002348C(FtgPrimHeader *hdr, FtgPolyF3 *src, FtgObject *obj, int idx);
int LoadFtgPolyG3_80023624(FtgPrimHeader *hdr, FtgSrcPolyG3 *src, FtgObject *obj, int idx);
int LoadFtgPolyFT3_800238AC(FtgPrimHeader *hdr, FtgSrcPolyFT3 *src, FtgObject *obj, int idx);
int LoadFtgPolyGT3_80023B48(FtgPrimHeader *hdr, FtgSrcPolyGT3 *src, FtgObject *obj, int idx);
int LoadFtgPolyF4_80023EA4(FtgPrimHeader *hdr, FtgPolyF4 *src, FtgObject *obj, int idx);
int LoadFtgPolyG4_8002407C(FtgPrimHeader *hdr, FtgSrcPolyG4 *src, FtgObject *obj, int idx);
int LoadFtgPolyFT4_80024394(FtgPrimHeader *hdr, FtgSrcPolyFT4 *src, FtgObject *obj, int idx);
int LoadFtgPolyGT4_800246A0(FtgPrimHeader *hdr, FtgSrcPolyGT4 *src, FtgObject *obj, int idx);

void InitOverlayLoaderTask_80020CB8();

#endif

