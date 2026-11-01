#ifndef GLOBALS_H
#define GLOBALS_H

#include "SYS/TYPES.H"
#include "LIBDS.H"
#include "enums.h"
#include "common.h"

typedef struct
{
    int field_0;
    int field_4;
    short field_8_x;
    short field_A_y;
} struct_44;

typedef struct
{
    short id; // 4 = empty slot
    char pad_2[0x7A];
    unsigned char field_7C[8];
    char field_84[0x10];
    char field_94[0x38];
    char field_CC[0x12];
    char field_DE[0x16];
    char field_F4[4];
} Minion;

typedef struct
{
    char pad_0[0x5C];
    int id; // 0xD3 = empty slot
    char pad_60[0x28];
} Item;

typedef struct
{
    int field_0;
    int field_4;
    char pad_8[0x980];
    Minion minions[15];
    Item items[12];
} SaveData;

typedef struct
{
    int field_0;
    int field_4;
    void (*field_8)(void);
} struct_obj_D;

typedef struct
{
    char pad_0[0x2A];
    short field_2A;
} struct_2C;


typedef struct
{
    int field_0;
    int field_4;
    int field_8;
} struct_12;

typedef struct
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
} struct_16;

typedef struct
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
} struct_24;

// object with a flags word at +4 and two halfwords at +0x20
typedef struct
{
    int field_0;
    unsigned int flags_4;
    char pad_8[0x18];
    short field_20;
    short field_22;
} struct_obj_A;

// object with a flags word at +0
typedef struct
{
    unsigned int flags_0;
    int field_4;
    short field_8;
    short field_A;
} struct_obj_B;

typedef struct
{
    int field_0;
    int field_4;
    short field_8[0x23];
} struct_obj_C;

extern struct_12 stru_8007D848[17];
extern struct_12 stru_8007D598[15];
extern unsigned char byte_8007CC24[0x2b];
extern struct_12 stru_8007CCA8[0x2b];
extern int dword_8007CB78[0x2b];
extern struct_24 stru_8007D04C[0x17];
extern int dword_8007CFF0[0x17];
extern int dword_8007D388[0x17];
extern struct_24 stru_8007D420[0xf];
extern int dword_8007D3E4[0xf];
extern unsigned short word_8007D64C[0xf];
extern struct_24 stru_8007D6B0[0x11];
extern int dword_8007D66C[0x11];
extern unsigned short word_8007D914[0x11];
extern int frameCount_8008D3FC;
extern unsigned short** dword_8008D4A4;
extern unsigned short word_800918D0[];
extern void* mdecVLCBuffer_80086F94;
extern int dword_80095468[0x10];
extern int dword_80091990[4];
extern struct_2C dword_80095FB0[];
extern unsigned char dword_8007C708[0x1E];
extern unsigned char byte_8007CEAC[0x2B];
extern int off_8007CF30[0x26];
extern int off_8007C348[0x1E * 2];
extern unsigned short dword_80079348[0x15];
extern int dword_800918B0;
extern unsigned int dword_80096118;
extern int dword_80091C88;
extern int dword_80091C44;
extern int* dword_80091C00;
extern int dword_800918B4;
extern unsigned char byte_8007D588[16];
extern int** dword_8008D4A0;
extern int** dword_8008D464;
extern int** dword_8008B54C;
extern int dword_80096090[4];
extern enum GameStates currentGameState_8008D4B4;
extern volatile int unknownFlags_8008D678;
extern short word_8008B558[2];
extern DslFILE Data001File_800954A8;
extern int DsReadSyncResult_8008D630;
extern int dword_8008B55C;
extern int dword_800918BC;
extern struct_44 stru_8008B4D8;
extern long cdRomEventDescError_8008B490;
extern long vsyncEventDesc_8008B494;
extern int dword_8008B574;
extern volatile int dword_8008B4B4;
extern volatile int gnFrame_8008D610;
extern volatile int dword_8008D450;
extern volatile int dword_8008D404;
extern SaveData saveData_8008B570;
extern unsigned int allMinionsBitfields_8008BD84[7];
extern unsigned char playerName_8008BD48[MAX_PLAYER_NAME_LENGTH];
extern unsigned long bDoubleBuffer_8008D428;
extern unsigned long OT_8008D798[2][8];
extern unsigned long OT_8008D7D8[2][1024];
extern unsigned long OT_8008F7D8[2][1024];
extern unsigned long OT_800917D8[2][16];
extern unsigned long OT_80091858[2][1];
extern unsigned long OT_80091868[2][4];
extern unsigned long OT_80091888[2][4];
extern unsigned long OT_800918A8[2][1];

extern unsigned long* pOT_8008D788;
extern unsigned long* pOT_8008D4AC;
extern unsigned long* pOT_8008D454;
extern unsigned long* pOT_8008D690;
extern unsigned long* pOT_8008D78C;
extern unsigned long* pOT_8008D5F4;
extern unsigned long* pOT_8008B4C8;
extern unsigned long* pOT_8008D3EC;

extern unsigned int settingsFlags_8008B58C;
extern int numFilesInsideTiy_8008B4BC;

#endif
