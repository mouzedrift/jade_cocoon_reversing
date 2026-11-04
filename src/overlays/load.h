// LOAD.BIN: declarations shared by its source files
#ifndef _LOAD_H_
#define _LOAD_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct
{
    char c_LOAD[5];
} Bytes5_LOAD;

typedef struct
{
    int poly_LOAD;
    short clutX_LOAD;
    short clutY_LOAD;
} IconSrc_LOAD;

typedef struct
{
    unsigned short flags_LOAD;
    short pad2_LOAD;
    int f4_LOAD;
    int f8_LOAD;
    int fC_LOAD;
    short x_LOAD;
    short y_LOAD;
    char pad14_LOAD[8];
} MenuItem_LOAD;

typedef struct
{
    MenuItem_LOAD item_LOAD[2];
} MenuItems2_LOAD;

typedef struct
{
    int f0_LOAD;
    int f4_LOAD;
    int f8_LOAD;
    int fC_LOAD;
    MenuItem_LOAD** items_LOAD;
    int f14_LOAD;
} MenuWin_LOAD;

typedef struct
{
    short x_LOAD;
    short y_LOAD;
} Pos_LOAD;

typedef struct
{
    char c_LOAD[8];
} Bytes8_LOAD;

typedef struct
{
    short f0_LOAD;
    short f2_LOAD;
    short f4_LOAD;
    short f6_LOAD;
} Row8_LOAD;

typedef struct
{
    unsigned char pad0_LOAD[6];
    unsigned char f6_LOAD;
    unsigned char f7_LOAD;
    unsigned char f8_LOAD;
    unsigned char f9_LOAD;
    unsigned char fA_LOAD;
    unsigned char fB_LOAD;
    unsigned char fC_LOAD;
    unsigned char fD_LOAD;
    unsigned char padE_LOAD[2];
} Row16_LOAD;

typedef union
{
    char str[0x42];
    struct
    {
        unsigned short text_0[0x12];
        unsigned char level_24[4]; // the two level digits
        unsigned short slash_28;
        unsigned short place_2A[0xC];
    } f;
} SaveTitle_LOAD;

extern int dword_800B66C0;
extern const char aSelectGameToLoa_800B66C4[44];
extern const char aSelectSaveLocat_800B66F0[44];
extern const char aYES_800B671C[];
extern const char aNO_800B6724[];
extern const char aExit_800B672C[];
extern const char aSelect_800B6738[];
extern const char aMEMORYCARDFull_800B6748[36];
extern const char aDoNotRemoveMEMO_800B676C[56];
extern const char aFormattingMEMOR_800B67A4[52];
extern const char aLoading_800B67D8[24];
extern const char aSaving_800B67F0[20];
extern const char aNoSaveGameData_800B6804[40];
extern const char aMEMORYCARDNotFo_800B682C[56];
extern const char aFormattingFaile_800B6864[40];
extern const char aSaveFailed_800B688C[28];
extern const char aLoadFailed_800B68A8[28];
extern const char byte_800B68E0[];
extern const char byte_800B68F8[];
extern const char byte_800B6918[];
extern const Bytes8_LOAD dword_800B6930;
extern const char byte_800B6938[];
extern const Bytes8_LOAD dword_800B6968;
extern const int dword_800B6970;
extern const Bytes8_LOAD dword_800B69F4;
extern const char byte_800B69FC[];
extern const Bytes8_LOAD dword_800B6A24;
extern const char byte_800B6A2C[];
extern const char byte_800B6A54[4];
extern const char byte_800B6A58[];
extern const char byte_800B6AA4[];
extern const char byte_800B6ADC[];
extern const char byte_800B6B0C[];
extern const Bytes8_LOAD dword_800B6B3C;
extern const Bytes8_LOAD dword_800B6B8C;
extern const Bytes8_LOAD dword_800B6B94;
extern const char byte_800B6B9C[];
extern const Bytes8_LOAD dword_800B6BA0;
extern const char byte_800B6BA8[];
extern const char aJadeCocoonLevel_800B6BAC[];
extern const char name_800B6BF0[];
extern const char name_800B6C04[];
extern const int dword_800B6C0C;
extern const int dword_800B6C10;
extern const int dword_800B6C14;
extern const unsigned short name_800B6C18[12];
extern const unsigned short name_800B6C30[12];
extern const char aCorridor_800B6C48[20];
extern const char asc_800B6C5C[28];
extern const char asc_800B6C78[28];
extern const char asc_800B6C94[28];
extern const char asc_800B6CB0[28];
extern const char asc_800B6CCC[28];
extern const char asc_800B6CE8[28];
extern const char asc_800B6D04[28];
extern const char asc_800B6D20[28];
extern const char asc_800B6D3C[28];
extern const char asc_800B6D58[28];
extern const char asc_800B6D74[28];
extern const char asc_800B6D90[28];
extern const char asc_800B6DAC[28];
extern const char asc_800B6DC8[28];
extern const char asc_800B6DE4[28];
extern const char aJadeCocoon15_800B6E00[28];
extern const char aJadeCocoon14_800B6E1C[28];
extern const char aJadeCocoon13_800B6E38[28];
extern const char aJadeCocoon12_800B6E54[28];
extern const char aJadeCocoon11_800B6E70[28];
extern const char aJadeCocoon10_800B6E8C[28];
extern const char aJadeCocoon09_800B6EA8[28];
extern const char aJadeCocoon08_800B6EC4[28];
extern const char aJadeCocoon07_800B6EE0[28];
extern const char aJadeCocoon06_800B6EFC[28];
extern const char aJadeCocoon05_800B6F18[28];
extern const char aJadeCocoon04_800B6F34[28];
extern const char aJadeCocoon03_800B6F50[28];
extern const char aJadeCocoon02_800B6F6C[28];
extern const char aJadeCocoon01_800B6F88[28];
extern const char aBASLUS00854COMB_800B6FA4[];
extern const char aBASLUS00854COMB_800B6FBC[];
extern const char aBASLUS00854COMB_800B6FD4[];
extern const char aBASLUS00854COMB_800B6FEC[];
extern const char aBASLUS00854COMB_800B7004[];
extern const char aBASLUS00854COMB_800B701C[];
extern const char aBASLUS00854COMB_800B7034[];
extern const char aBASLUS00854COMB_800B704C[];
extern const char aBASLUS00854COMB_800B7064[];
extern const char aBASLUS00854COMB_800B707C[];
extern const char aBASLUS00854COMB_800B7094[];
extern const char aBASLUS00854COMB_800B70AC[];
extern const char aBASLUS00854COMB_800B70C4[];
extern const char aBASLUS00854COMB_800B70DC[];
extern const char aBASLUS00854COMB_800B70F4[];
extern const char aBASLUS00854GAME_800B710C[];
extern const char aBASLUS00854GAME_800B7124[];
extern const char aBASLUS00854GAME_800B713C[];
extern const char aBASLUS00854GAME_800B7154[];
extern const char aBASLUS00854GAME_800B716C[];
extern const char aBASLUS00854GAME_800B7184[];
extern const char aBASLUS00854GAME_800B719C[];
extern const char aBASLUS00854GAME_800B71B4[];
extern const char aBASLUS00854GAME_800B71CC[];
extern const char aBASLUS00854GAME_800B71E4[];
extern const char aBASLUS00854GAME_800B71FC[];
extern const char aBASLUS00854GAME_800B7214[];
extern const char aBASLUS00854GAME_800B722C[];
extern const char aBASLUS00854GAME_800B7244[];
extern const char aBASLUS00854GAME_800B725C[];
extern const char asc_800B7274[];
extern const char asc_800B7290[];
extern const char asc_800B72A8[];
extern const char asc_800B72C0[];
extern const char asc_800B72D8[];
extern const char byte_800B72FC[4];
extern const Bytes5_LOAD dword_800B7300;
extern const char asc_800B7308[];
extern const MenuItems2_LOAD dword_800B731C;
extern const char asc_800B7354[];
extern const MenuItems2_LOAD dword_800B7368;
extern Pos_LOAD dword_800BD93C[9];
extern Row8_LOAD dword_800BD960[7];
extern Row8_LOAD dword_800BD998[2];
extern int dword_800BD9A8[16];
extern Row8_LOAD dword_800BD9E8[4];
extern char *dword_800BDA08[2];
extern RECT dword_800BDA10;
extern MenuItem_LOAD dword_800BDA18[2];
extern MenuItem_LOAD dword_800BDA50[2];
extern MenuItem_LOAD dword_800BDA88[2];
extern MenuItem_LOAD dword_800BDAC0[2];
extern MenuItem_LOAD *dword_800BDAF8[5];
extern MenuWin_LOAD dword_800BDB0C;
extern int dword_800BDB24[14];
extern void *dword_800BDB5C[2];
extern int dword_800BDB64;
extern int dword_800BDB68[5];
extern int dword_800BDB7C[14];
extern void *dword_800BDBB4[2];
extern int dword_800BDBBC;
extern int dword_800BDBC0[5];
extern int *dword_800BDBD4[2];
extern MenuItem_LOAD dword_800BDBDC[2];
extern MenuItem_LOAD dword_800BDC14[2];
extern MenuItem_LOAD dword_800BDC4C[2];
extern MenuItem_LOAD dword_800BDC84[2];
extern MenuItem_LOAD *dword_800BDCBC[5];
extern MenuWin_LOAD dword_800BDCD0;
extern MenuItem_LOAD dword_800BDCE8[2];
extern MenuItem_LOAD dword_800BDD20[2];
extern MenuItem_LOAD *dword_800BDD58[3];
extern MenuWin_LOAD dword_800BDD64;
extern MenuItem_LOAD dword_800BDD7C[2];
extern MenuItem_LOAD dword_800BDDB4[2];
extern MenuItem_LOAD *dword_800BDDEC[3];
extern MenuWin_LOAD dword_800BDDF8;
extern MenuItem_LOAD dword_800BDE10[2];
extern MenuItem_LOAD dword_800BDE48[2];
extern MenuItem_LOAD *dword_800BDE80[3];
extern MenuWin_LOAD dword_800BDE8C;
extern char dword_800BDEA4[24];
extern char *dword_800BDEBC[4];
extern char *dword_800BDECC[4];
extern char *dword_800BDEDC[4];
extern char *dword_800BDEEC[4];
extern char *dword_800BDEFC[8];
extern char *dword_800BDF1C[4];
extern char *dword_800BDF2C[4];
extern char *dword_800BDF3C[4];
extern Row16_LOAD stru_800BDF4C[2];
extern int dword_800BDF6C[4];
extern int dword_800BDF7C[4];
extern int dword_800BDF8C[4];
extern int dword_800BDF9C[4];
extern SaveTitle_LOAD *name_800BDFAC;
extern char *dword_800BDFB0[30];
extern char *saveFileNames_800BE028[2][15];
extern IconSrc_LOAD dword_800BE0A0[3];
extern char dword_800BE0B8[148];
extern int cardFreeBlocks_800BE14C;
extern int cardSaveCount_800BE150;
extern int loadMenuActive_800BE184;
extern char *cardSaveNames_800BE188[15];

#endif
