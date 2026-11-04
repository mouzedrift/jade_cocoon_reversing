// TSTMODEL.BIN: declarations shared by its source files
#ifndef _TSTMODEL_H_
#define _TSTMODEL_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "model.h"

typedef struct TstModelBone
{
    short s0;
    short s2;
    short s4;
    unsigned short flags;
} TstModelBone;

typedef struct TstModelTbl { int modelId_0; TstModelBone* bones_4; int name_8; } TstModelTbl;

typedef struct TstModelMat
{
    int w[8];
} TstModelMat;

extern int dword_800A05A0;
extern const char aMDLOUMG_800A05A4[];
extern const char aMDLZIRA_800A05B0[];
extern const char aMDLTORI_800A05BC[];
extern const char aMDLSHABUC_800A05C8[];
extern const char aMDLSHABUB_800A05D4[];
extern const char aMDLOJE_800A05E0[];
extern const char aMDLNEBUI_800A05E8[];
extern const char aMDLMUGU_800A05F4[];
extern const char aMDLLUCHC_800A0600[];
extern const char aMDLLUCHB_800A060C[];
extern const char aMDLKANI_800A0618[];
extern const char aMDLKAMERE_800A0624[];
extern const char aMDLIMELC_800A0630[];
extern const char aMDLIMELB_800A063C[];
extern const char aMDLHIRAC_800A0648[];
extern const char aMDLHIRAB_800A0654[];
extern const char aMDLHANBC_800A0660[];
extern const char aMDLHANBB_800A066C[];
extern const char aMDLDONGC_800A0678[];
extern const char aMDLDONGB_800A0684[];
extern const char aMDLDLEGC_800A0690[];
extern const char aMDLDLEGB_800A069C[];
extern const char aMDLGINU_800A06A8[];
extern const char aMDLDONG_800A06B4[];
extern const char aMDLHIRA_800A06C0[];
extern const char aMDLTHRE_800A06CC[];
extern const char aMDLMAIE_800A06D8[];
extern const char aMDLIMEL_800A06E4[];
extern const char aMDLHANBA_800A06F0[];
extern const char aMDLDLEG_800A06FC[];
extern const char aMDLSHABU_800A0708[];
extern const char aMDLLUCH_800A0714[];
extern const char aMDLUGURAM_800A0720[];
extern const char aMDLASHA_800A072C[];
extern const char aMDLRIG_800A0738[];
extern const char aMDLYOLK_800A0740[];
extern const char aMDLRIKE_800A074C[];
extern const char aMDLNAGK_800A0758[];
extern const char aMDLBSZZ_800A0764[];
extern const char aMDLBSWE_800A0770[];
extern const char aMDLBSWS_800A077C[];
extern const char aMDLBSFE_800A0788[];
extern const char aMDLBSFS_800A0794[];
extern const char aMDLBSGE_800A07A0[];
extern const char aMDLBSGS_800A07AC[];
extern const char aMDLYMI_800A07B8[];
extern const char aMDLYMKK_800A07C0[];
extern const char aMDLYMTT_800A07CC[];
extern const char aMDLYM_800A07D8[];
extern const char aMDLNCHO_800A07E0[];
extern const char aMDLNMUU_800A07EC[];
extern const char aMDLNRAA_800A07F8[];
extern const char aMDLKIKI_800A0804[];
extern const char aMDLKORI_800A0810[];
extern const char aMDLDMA_800A081C[];
extern const char aMDLDC_800A0824[];
extern const char aMDLDB_800A082C[];
extern const char aMDLDA_800A0834[];
extern const char aMDLYUME_800A083C[];
extern const char aMDLSOUJB_800A0848[];
extern const char aMDLSOUJ_800A0854[];
extern const char aMDLZIB_800A0860[];
extern const char aMDLZOK_800A0868[];
extern const char aMDLMNBN_800A0870[];
extern const char aMDLHJI_800A087C[];
extern const char aMDLMOBC_800A0884[];
extern const char aMDLMOBB_800A0890[];
extern const char aMDLROUBC_800A089C[];
extern const char aMDLROUBB_800A08A8[];
extern const char aMDLROUBA_800A08B4[];
extern const char aMDLMCHO_800A08C0[];
extern const char aMDLSDOG_800A08CC[];
extern const char aMDLLUIA_800A08D8[];
extern const char aMDLLUI_800A08E4[];
extern const char aMDLMLEB_800A08EC[];
extern const char aMDLMKEL_800A08F8[];
extern const char aMDLFKEL_800A0904[];
extern const char aMDLKEL_800A0910[];
extern const char aMDLMDOG_800A0918[];
extern const char aMDLMOBA_800A0924[];
extern const char aMDLMABF_800A0930[];
extern const char aMDLMABE_800A093C[];
extern const char aMDLMABD_800A0948[];
extern const char aMDLMABC_800A0954[];
extern const char aMDLMABB_800A0960[];
extern const char aMDLMABA_800A096C[];
extern const char aMDLGAR_800A0978[];
extern const char aMDLLEB2_800A0980[];
extern const char aMDLLEBANT_800A098C[];
extern const int dword_800A0998;
extern const TstModelBone dword_800A09B8;
extern MATRIX lightDirs_800A1E84;
extern TstModelMat lightColors_800A1EA4;
extern int tstModelTaskDesc_800A1EC4[6];
extern char tstModelTaskList_800A1EDC[12];
extern char modelLight_800A1EE8[24];
extern int minionBones_800A1F00[52];
extern int humanBones_800A1FD0[46];
extern int roubBones_800A2088[34];
extern int mchoBones_800A2110[48];
extern int mobBones_800A21D0[46];
extern int mnbnBones_800A2288[40];
extern int zibBones_800A2328[40];
extern int soujBones_800A23C8[30];
extern int yumeBones_800A2440[50];
extern int kikiBones_800A2508[54];
extern int bsgsBones_800A25E0[76];
extern int mabdBones_800A2710[34];
extern int mabeBones_800A2798[40];
extern int mabfBones_800A2838[58];
extern int mabcBones_800A2920[54];
extern int luiaBones_800A29F8[46];
extern int nraaBones_800A2AB0[40];
extern int nmuuBones_800A2B50[42];
extern int nchoBones_800A2BF8[48];
extern int ymBones_800A2CB8[32];
extern int bseBones_800A2D38[48];
extern int bsfsBones_800A2DF8[82];
extern int bswsBones_800A2F40[82];
extern int bszzBones_800A3088[72];
extern int rikeBones_800A31A8[48];
extern char boneScales_800A3268[328];
extern TstModelTbl tstModels_800A33B0[90];
extern int levantFtgs_800A37E8[3];
extern short gridWrapMask_800A37F4[4];
extern short gridWrapSign_800A37FC[4];
extern char modelBonePos_800A3804[480];


/* ---- moved from the .c files: types ---- */
// parameter block of DrawAnimSkel_80046A58
typedef struct TstModelDraw
{
    FtgObject* ftg_0;
    VECTOR* pos_4;
    char* rot_8;
    TstModelBone* bones_C;
    char* base_10;
    ModelAnim* anim_14;
    int frame_18;
    int drawMode_1C;
    char* bonePos_20;
    VECTOR* scale_24;
    unsigned long* ot_28;
} TstModelDraw;

// work area of the TSTMODEL task (TstModelInit_800A09C0)
typedef struct TstModelWork
{
    int state_0;
    int sel_4;       // model list cursor
    int scroll_8;
    int boneSel_C;   // bone list cursor
    int boneScroll_10;
    ModelList* models_14;
    Model* model_18;
    int count_1C;
    int loadSel_20;   // LoadModel_80025200 sel, 0..0xBF
    int modelId_24;
    TstModelBone bones_28[41];
    short yaw_170;
    short holdTimer_172; // frames the bone-edit button is held
    short dist_174;
    short pad_176;
    int eyeX_178;
    int eyeY_17C;
    int eyeZ_180;
    int atX_184;
    int atY_188;
    int atZ_18C;
    int posX_190; // reset with the camera (TstCompoWork.pos_16C)
    int posY_194;
    int posZ_198;
    short s19C;
    short s19E;
    short s1A0;
    short pad_1A2;
    int frame_1A4;
    int anim_1A8;
    int animCount_1AC;
    int nextAnim_1B0;
    int animLoaded_1B4; // nextAnim was loaded here, free it on the next pick
    int paused_1B8;
    int scaleStep_1BC;
    TstModelDraw draw_1C0;
    int pad_1EC;
    SVECTOR rot_1F0;
} TstModelWork;

typedef struct GridCursor
{
    int flags_0; // 1: wrap left/right, 2: wrap up/down
    unsigned short unused_4;
    short sel_6;
    short cols_8;
    short rows_A;
    short count_C;
    unsigned short scroll_E;
} GridCursor;

/* TSTMODEL's own functions/data used before their definition or from another of its files */
void TstModelResetCamera_800A0BC0(TstModelWork* work);
extern int UpdateGridCursor_800A1D70();
extern void TstModelTask_800A0A8C();
extern void TstModelSelectModel_800A0C00();
extern void TstModelLoadModel_800A0EC8();
extern void TstModelWaitModel_800A0F20();
extern void TstModelCameraInput_800A104C();
extern void TstModelDrawModel_800A1428();
extern void TstModelAnimSelect_800A17B8();
extern void TstModelBoneEdit_800A1614();
extern void TstModelFrameInput_800A18F4();
extern void TstModelFreeModel_800A19E4();
extern void SetCameraLookAt_800A1A24();
extern int MoveGridCursor_800A1B48();
/* exe-side: declared in main.h (which conflicts with this overlay's types; main.h has scalars for the pad words) */
extern unsigned short padRepeat_800918CC[];
extern unsigned short padPressed_8009194C[];
extern short cameraRot_8008D4C8[];
extern unsigned char backColor_8008D460[];
/* exe-side: camera.h declares it as VECTOR cameraEye_8008D600 */
extern int cameraEye_8008D600[];
/* exe-side, to move to main.h / globals.h */
extern short screenOffset_8008D474[];
/* exe-side: data_decls.h declares it (that header needs LIBSND.H) */
extern short sinTable_80084540[];
/* exe-side: event.h declares them (as MATRIX) */
extern MATRIX lightMatrix_80087114;
extern TstModelMat colorMatrix_80087134;
/* exe-side, to move to ftg_draw.h */
extern MATRIX* RotMatrixZYX_8004D5CC(SVECTOR* r, MATRIX* m);
extern void GetAnimRootMotion_8004D288(VECTOR* out, ModelAnim* anim, int frame);
extern void SetGteLightAndCamera_8004D0E8();
/* exe-side, to move to engine.h */
extern void PlayAnimFrameSfx_8001C364(Model* a0, int idx, int a2);
/* exe-side, to move to skel_draw.h */
extern void DrawAnimSkel_80046A58(void* a, void* b, int c);
extern void DrawSpriteVtxQuadsGT4_800459E4(void* a, void* b, void* c, int d);
/* exe-side, to move to pad_text.h */
extern int AdjustByShoulderButtons_8003D198(int limit, int pos, int step, int idx);
/* exe-side, to move to sound_seq.h */
extern void PlaySfx_80031494(int id); // sound.h declares it too
/* PSY-Q library */
extern MATRIX* MulMatrix0(MATRIX* m0, MATRIX* m1, MATRIX* m2);
extern void* memset(void* p, int c, unsigned int n);

#endif
