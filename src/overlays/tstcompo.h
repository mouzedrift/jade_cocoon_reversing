// TSTCOMPO.BIN: declarations shared by its source files
#ifndef _TSTCOMPO_H_
#define _TSTCOMPO_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "model.h"
#include "main.h"
#include "font.h"
#include "util.h"
#include "event.h"
#include "pad_text.h"
#include "cd.h"
#include "engine.h"
#include "minion_init.h"
#include "party.h"
#include "model_ftg.h"
#include "ftg_draw.h"
#include "cursor.h"


// the first 8 bytes of a menu cursor (UpdateMenuCursor_8003D794)
typedef struct TstCompoCursorHead { char b[8]; } TstCompoCursorHead;

typedef struct TstCompoMenu
{
    union
    {
        TstCompoCursorHead blk;
        struct
        {
            short cols_0;
            short count_2;
            short f4;
            short f6;
        } f;
    } head_0;
    short dx_8;
    short dy_A;
    short x_C;
    short y_E;
} TstCompoMenu;

typedef struct TstCompoEnt
{
    unsigned short x_0;
    unsigned short y_2;
    int text_4; // string, 0 ends the list
} TstCompoEnt;

typedef struct TstCompoPage
{
    TstCompoMenu* menu_0;
    TstCompoEnt* texts_4;
    short rect_8[4];
    int f10;
} TstCompoPage;

typedef struct TstCompoPart
{
    int text_0;
    int id_4;
    int angle_8;
    int fC;
    int f10;
} TstCompoPart;

typedef struct TstCompoModelParams
{
    int partCount_0;
    int part_4[3];  // the compounded minions' part ids (TstCompoPart.id_4)
    int ratio_10[3]; // their shares, 0x1000 in all
    int modelId_1C;
    int texPart_20;   // part_4 index of the model the textures come from (ModelTaskState.texPart_24)
    int angle_24;     // 0..359
    int enemyPart_28; // TstCompoPart.id_4 of the ENEMY pick
    int main_2C;      // part_4 index of the model whose animations are kept
    int vram_30;      // ModelVramSlot* (ModelTaskState.vram_34)
} TstCompoModelParams;

extern int dword_800A05A0;
extern const char a9_800A05A4[];
extern const char a8_800A05A8[];
extern const char a7_800A05AC[];
extern const char a6_800A05B0[];
extern const char a5_800A05B4[];
extern const char a4_800A05B8[];
extern const char a3_800A05BC[];
extern const char a2_800A05C0[];
extern const char a1_800A05C4[];
extern const char a0_800A05C8[];
extern const char aPadoruka_800A05CC[];
extern const char aArupataron_800A05D8[];
extern const char aSheriku_800A05E8[];
extern const char aRashababa_800A05F4[];
extern const char aTuingo_800A0600[];
extern const char aEsupu_800A060C[];
extern const char aJiraru_800A0614[];
extern const char aYoruku_800A061C[];
extern const char aUguramu_800A0624[];
extern const char aSurikaata_800A0630[];
extern const char aRigu_800A063C[];
extern const char aOje_800A0644[];
extern const char aNeebui_800A064C[];
extern const char aMuguu_800A0658[];
extern const char aMaayen_800A0660[];
extern const char aGinui_800A066C[];
extern const char aAsha_800A0674[];
extern const char aMutsukishabu_800A067C[];
extern const char aRashabu_800A068C[];
extern const char aNushabu_800A0698[];
extern const char aDoguruchuu_800A06A4[];
extern const char aRadoruchu_800A06B4[];
extern const char aPataruchuu_800A06C0[];
extern const char aRadoimeru_800A06D0[];
extern const char aSukuimeru_800A06DC[];
extern const char aPataimeru_800A06E8[];
extern const char aHirasagu_800A06F4[];
extern const char aMasukohira_800A0700[];
extern const char aHiraruko_800A070C[];
extern const char aTerahanbuu_800A0718[];
extern const char aDoguhanbuu_800A0728[];
extern const char aMukahanbuu_800A0738[];
extern const char aBerabansa_800A0748[];
extern const char aDonguru_800A0754[];
extern const char aRagidoguru_800A0760[];
extern const char aPatadorekku_800A076C[];
extern const char aRadoreggu_800A077C[];
extern const char aMaadoreggu_800A0788[];
extern const char aNAMERATE_800A0798[];
extern const char aTEXHANGL_800A07B8[];
extern const char aENEMY_800A07D8[];
extern TstCompoPart compoParts_800A20EC[48];
extern int compoTexts0_800A24AC[4];
extern int compoTexts1_800A24BC[4];
extern int compoTexts2_800A24CC[4];
extern int compoMenu0_800A24DC[4];
extern int compoMenu1_800A24EC[4];
extern int compoMenu2_800A24FC[4];
extern TstCompoPage compoPages_800A250C[3];
extern int tstCompoTaskDesc_800A2548[6];
extern EventDesc* tstCompoTaskList_800A2560[4];
extern char compoLight_800A2570[24];
extern char compoBonePos_800A2588[480];
extern TstCompoModelParams compoModelParams_800A2768;


/* ---- moved from the .c files: types ---- */
// a menu layout of the TSTCOMPO pages: the cursor head (copied into the work cursor), then the grid geometry
// a TSTCOMPO page (compoPages_800A250C[3])
// a selectable part / colour of the compound test (compoParts_800A20EC[])
typedef struct TstCompoBone
{
    short s0;
    short s2;
    short s4;
    short s6;
} TstCompoBone;

// parameter block of DrawAnimSkel_80046A58 / DrawAnimSkelBlend_80047E28
typedef struct TstCompoDraw
{
    FtgObject* ftg_0;
    VECTOR* pos_4;
    char* rot_8;
    TstCompoBone* bones_C;
    char* base_10;
    ModelAnim* anim_14;
    int frame_18;
    int drawMode_1C;
    char* bonePos_20;
    VECTOR* scale_24;
    unsigned long* ot_28;
} TstCompoDraw;

// work area of the TSTCOMPO task (TstCompoInit_800A0800)
typedef struct TstCompoWork
{
    int state_0;
    Model* model_4;
    int f8;
    TstCompoBone bones_C[40];
    short yaw_14C;
    short s14E;
    short dist_150;
    short pad_152;
    int eye_154[3];
    int at_160[3];
    int pos_16C[3];
    short s178;
    short s17A;
    short s17C;
    short pad_17E;
    int frame_180;
    int anim_184;
    int animCount_188;
    int nextAnim_18C;
    int animLoaded_190;
    int paused_194;
    int scaleStep_198;
    int scaleId_19C;
    int* scale_1A0;
    char* boneScale_1A4;
    TstCompoDraw draw_1A8;
    int pad_1D4;
    TstCompoCursorHead cursor_1D8;
    short sel_1E0;
    short scroll_1E2;
    int nextPage_1E4;
    int page_1E8;
    int returnPage_1EC;
    int f1F0;
    unsigned int savedSel_1F4;
    int* pickTarget_1F8;
    int blend_1FC;
    int blendFrame_200;
    int blendAnim_204;
    int listScroll_208;
    int listSel_20C;
    int part_210[3];
    int ratio_21C[3];
    int f228;
    int enemy_22C;
} TstCompoWork;



/* TSTCOMPO's own functions/data used before their definition or from another of its files */
void SetDefaultCompoParams_800A0918();
void TstCompoResetCamera_800A1BE0(TstCompoWork* work);
extern void TstCompoTask_800A097C();
extern void TstCompoMenu_800A0AB8();
extern void TstCompoStartModel_800A1320();
extern void TstCompoWaitModel_800A1354();
extern void TstCompoWaitFiles_800A13B8();
extern void TstCompoDrawModel_800A1468();
extern void TstCompoDrawBlend_800A15F4();
extern void TstCompoFrameInput_800A1804();
extern void TstCompoViewInput_800A194C();
extern void TstCompoAnimSelect_800A19A4();
extern void TstCompoFreeModel_800A1AD0();
extern void TstCompoCameraInput_800A1C14();
extern void DrawTextListWindow_800A2030(short* rect, TstCompoEnt* texts, int ot);
extern void TstCompoInitBones_800A1AFC();
extern void SetCameraLookAt_800A1E68();
/* exe-side: declared in main.h (which conflicts with this overlay's types) */
/* exe-side: camera.h declares it as VECTOR cameraEye_8008D600 */
extern LVec3 cameraEye_8008D600;
/* exe-side, to move to main.h / globals.h */
extern short screenOffset_8008D474[];
extern MATRIX defaultLightMatrix_8007C2EC; // effect_data.h
extern MATRIX defaultColorMatrix_8007C30C; // effect_data.h
/* exe-side: effect_data.h declares it as int dword_8007DC74[6] */
extern int dword_8007DC74;
/* exe-side: data_decls.h declares it (that header needs LIBSND.H) */
extern short sinTable_80084540[];
/* exe-side, to move to pad_text.h */
/* exe-side, to move to cursor.h */
/* exe-side, to move to font.h */
/* exe-side, to move to util.h */
/* exe-side, to move to party.h */
/* exe-side, to move to skel_draw.h */
extern void DrawAnimSkel_80046A58(void* a, void* b, void* c);
extern void DrawSpriteVtxQuadsGT4_800459E4(void* a, void* b, void* c, int d);
extern void DrawAnimSkelBlend_80047E28(void* a, void* b, void* c, int d, int e, void* f, void* g);
/* exe-side, to move to unit_stats.h */
extern TstCompoBone defaultBones_80079140[];
/* exe-side, to move to minion_init.h */
/* exe-side, to move to ftg_draw.h */
/* exe-side, to move to event.h */
extern MATRIX lightMatrix_80087114; // event.h
extern MATRIX colorMatrix_80087134; // event.h
/* PSY-Q library */
extern void* memset(void* p, int c, unsigned int n);

#endif
