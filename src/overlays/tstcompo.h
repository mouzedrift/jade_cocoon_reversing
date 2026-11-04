// TSTCOMPO.BIN: declarations shared by its source files
#ifndef _TSTCOMPO_H_
#define _TSTCOMPO_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "model.h"

typedef struct TstCompoBlk8 { char b[8]; } TstCompoBlk8;

typedef struct TstCompoMenu
{
    union
    {
        TstCompoBlk8 blk;
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
    int f20;
    int angle_24;     // 0..359
    int enemyPart_28; // TstCompoPart.id_4 of the ENEMY pick
    int f2C;
    int f30;
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
extern const char asc_800A05CC[];
extern const char asc_800A05D8[];
extern const char asc_800A05E8[];
extern const char asc_800A05F4[];
extern const char asc_800A0600[];
extern const char asc_800A060C[];
extern const char asc_800A0614[];
extern const char asc_800A061C[];
extern const char asc_800A0624[];
extern const char asc_800A0630[];
extern const char asc_800A063C[];
extern const char asc_800A0644[];
extern const char asc_800A064C[];
extern const char asc_800A0658[];
extern const char asc_800A0660[];
extern const char asc_800A066C[];
extern const char asc_800A0674[];
extern const char asc_800A067C[];
extern const char asc_800A068C[];
extern const char asc_800A0698[];
extern const char asc_800A06A4[];
extern const char asc_800A06B4[];
extern const char asc_800A06C0[];
extern const char asc_800A06D0[];
extern const char asc_800A06DC[];
extern const char asc_800A06E8[];
extern const char asc_800A06F4[];
extern const char asc_800A0700[];
extern const char asc_800A070C[];
extern const char asc_800A0718[];
extern const char asc_800A0728[];
extern const char asc_800A0738[];
extern const char asc_800A0748[];
extern const char asc_800A0754[];
extern const char asc_800A0760[];
extern const char asc_800A076C[];
extern const char asc_800A077C[];
extern const char asc_800A0788[];
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
extern char tstCompoTaskList_800A2560[16];
extern char name_800A2570[24];
extern char name_800A2588[480];
extern TstCompoModelParams compoModelParams_800A2768;

#endif
