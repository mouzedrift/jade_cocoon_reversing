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
    short pad_2[3];
    short field_8;
    short field_A;
    short field_C;
    short field_E;
    char pad_10[0x1C];
    unsigned char field_2C[0x16];
    short field_42;
    unsigned char field_44;
    char pad_45[0x37];
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
    char pad_8[0x14];
    unsigned int field_1C_settings; // == settingsFlags_8008B58C
    char pad_20[0x968];
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
    int field_0;
    unsigned char field_4;
    unsigned char field_5;
    unsigned char field_6;
    unsigned char field_7;
    short field_8;
    short pad_A;
} struct_12_b;

typedef struct
{
    int field_0;
    short field_4;
    signed char field_6;
    unsigned char field_7;
} struct_8;

typedef struct
{
    char pad_0[2];
    unsigned char field_2;
    unsigned char field_3;
} struct_4;

typedef struct
{
    short field_0;
    short field_2;
    short field_4;
    short field_6;
} struct_10;

typedef struct
{
    char pad_0[2];
    short field_2;
    char pad_4[0xC];
} struct_16_b;

typedef struct
{
    char data[0x54];
} struct_54;

// object with a header at +0x4C and tables of struct_54 at +0x50 and +0x68
typedef struct
{
    char pad_0[0x4C];
    int* field_4C;
    struct_54* field_50;
    char pad_54[0x14];
    struct_54* field_68;
} struct_obj_E;

typedef struct
{
    char pad_0[4];
    unsigned char field_4;
    unsigned char field_5;
    unsigned char field_6;
    char pad_7[5];
    unsigned char field_C;
    unsigned char field_D;
    unsigned short field_E;
    short field_10;
    short field_12;
    unsigned short* field_14;
    short field_18;
    short field_1A;
    short field_1C;
    unsigned short field_1E;
    short field_20;
    short field_22;
    unsigned char* field_24;
    short field_28;
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

// object with a flags word at +4
typedef struct
{
    int field_0;
    unsigned int flags_4;
    char pad_8[0x12];
    short field_1A;
    short field_1C;
    short pad_1E;
    short field_20;
    short field_22;
    char pad_24[0x68];
    int field_8C;
    int field_90;
    char pad_94[0x40];
    unsigned int field_D4;
} struct_obj_A;

// object with a flags word at +0
typedef struct
{
    unsigned int flags_0;
    int field_4;
    short field_8;
    short field_A;
} struct_obj_B;

// flags word at +0 and two (current, target) short pairs
typedef struct
{
    unsigned int flags_0;
    int field_4;
    short field_8;
    short field_A;
    short field_C;
    short field_E;
} struct_pair_obj;

// 0x70-byte element with an id at +0x38 (0xFFFF = unused)
typedef struct
{
    char pad_0[0x38];
    unsigned short id_38;
    char pad_3A[0x36];
} struct_elem_70;

// 0x40-byte state object driven by sub_80010AD8 (state_38 indexes its jump table)
typedef struct
{
    int* field_0;
    int field_4;
    int arr_8[7];
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int state_38;
    int next_3C;
} struct_state_obj;

typedef struct
{
    int field_0;
    int field_4;
    short field_8[0x23];
} struct_obj_C;

extern struct_12 stru_8007D848[17];
extern struct_12 stru_8007D598[15];
extern unsigned char byte_8007CC24[0x2b];
extern unsigned short aKkkiqqqqqssssZ[];
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
extern unsigned int dword_80096118;
extern int dword_80091CFC;
extern int dword_80083BD0;
extern int dword_80086540;
extern int dword_8008656C;
extern int dword_80086550[5];
extern int dword_80079320[];
extern struct_8 dword_8007A4B4[];
extern int** dword_8008D4C0;
extern struct_12 stru_80083594[];
extern struct_4 byte_80095460[];
extern int** dword_8008B560;
extern int off_8007CB20[];
extern int dword_8007CB4C[];
extern int bStopDrawingMovie_8008D45C;
extern int dword_8008B540;
extern int dword_800918B8;
extern int dword_80086564;
extern int dword_80098688;
extern int off_800824CC[];
extern struct_12_b dword_8007C438[];
extern struct_12 dword_8007C5A0[];
extern int dword_80091C20;
extern unsigned short word_8007CED8[];
typedef struct
{
    char pad_0[0x10];
    int field_10;
    char pad_14[0x14];
} struct_obj_Q;

extern unsigned char byte_8007CFC8[0x26];
extern struct_obj_Q dword_80095C90[0x14];
extern short word_80091D0C;
extern struct_8 dword_800833E4[];
extern int** dword_8008D3F8;
extern unsigned char drawEnvRed_8008D448[3];
extern char copyright_80086948[];
extern char genkiMovie_80086968[];
extern char craveEntertainmentMovie_80086988[];
extern char demoDisclaimer_800869A8[];
extern char introAnime_800869C8[];
typedef struct
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
} struct_20;
typedef struct
{
    int m[3];
} struct_int3;
typedef struct
{
    unsigned char c[4];
} struct_u8x4;
// 0x14 bytes copied without alignment
typedef struct
{
    unsigned char data[0x14];
} struct_20_u8;

typedef struct struct_node_C
{
    struct struct_node_C* next;
    int field_4;
    int key;
    unsigned int field_C;
    int field_10;
    char pad_14[8];
    int field_1C;
    int field_20;
    int field_24;
} struct_node_C;

extern int** dword_800B1DC4;
extern int** dword_800B1DB8;
extern short dword_8007D938[];
extern int dword_80082670;
extern short word_8008B862;
extern int dword_80082678;
extern short word_80091C40;
extern struct_node_C* dword_8008654C;
extern struct_20 dword_8007A9F8[];
extern struct_obj_C dword_800919A0[7];
extern int loadedOverlayMaybe_8008D620;
extern int dword_8008D3F4;
extern int dword_8008B4E8;
extern int frameCount_8008D3FC;
extern int geomScreenDistance_8008B548;
extern int dword_8008B4F8;
extern int dword_800918C4;
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
extern struct_10 stru_80096110;
extern int dword_80091C88;
extern int dword_80091C44;
extern int* dword_80091C00;
extern int dword_800918B4;
extern unsigned char byte_8007D588[16];
extern int** dword_8008D4A0;
extern int** dword_8008D464;
extern int** dword_8008B54C;
extern int dword_8008B550;
extern int dword_800960A0[2];
extern int dword_800960A8[2];
extern unsigned long* decodedImageData_8008B4A0;
extern int dword_80096090[4];
extern enum GameStates currentGameState_8008D4B4;
extern volatile int unknownFlags_8008D678;
extern short word_8008B558[2];
extern DslFILE Data001File_800954A8;
extern int DsReadSyncResult_8008D630;
extern int dword_8008B55C;
extern int dword_800918BC;
extern int ODEIsEvenAddressDrawn_800918C0;
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

extern int** dword_8008D628;
extern int dword_8008D43C;
extern int dword_8008D61C;
extern struct_12 dword_8007D274[0x17];
extern unsigned short word_80079374[];
typedef struct
{
    int field_0;
    int field_4;
    char pad_8[0x28];
    int field_30;
    int field_34;
    unsigned short id_38;
    unsigned short field_3A;
    unsigned short field_3C;
    unsigned short field_3E;
    unsigned short field_40;
    unsigned char field_42;
    unsigned char field_43;
    int field_44;
    int field_48;
    int field_4C;
    int field_50;
    int field_54;
    int field_58;
    int field_5C;
    int field_60;
    int field_64;
    int field_68;
    int field_6C;
} struct_112;
typedef struct
{
    int count;
    int field_4;
    struct_112* items;
    void* field_C;
} struct_112_list;

extern int dword_8007BD30[];
extern unsigned short dword_8007CAD8[0xe];
extern unsigned short dword_8007CAF4[0xa];
extern int dword_80091BD0[4];
extern int dword_8008D4DC;
extern int dword_80079708[];
typedef struct
{
    short id;
    short field_2;
    int field_4;
} struct_8_id;
typedef struct
{
    char pad_0[0xC];
    int count;
    struct_8_id* items;
} struct_8_list;

extern int dword_8007A6AC[];
extern int dword_8008D40C;
typedef struct
{
    char pad_0[0x14];
    int count;
    struct_12* items;
} struct_list_14;
typedef struct struct_cb
{
    unsigned int flags_0;
    int field_4;
    void (*fn_8)(struct struct_cb*, int*);
    int field_C;
    int field_10;
    int* field_14;
} struct_cb;

typedef struct
{
    short field_0;
    short field_2;
} struct_4s;
extern struct_4s dword_8008D600[3];

typedef struct
{
    char pad_0[0x10];
    int field_10;
    int field_14;
    int field_18;
} struct_28;

typedef struct
{
    int field_0;
    unsigned int flags_4;
    int field_8;
    int field_C;
    char pad_10[0x120];
    int field_130;
} struct_obj_F;

extern unsigned short dword_8008B578[];
// Event list nodes (event.c / tu_80043AF8.c). The list head has the same layout as a node.
struct EventEntry;
typedef void (*EventEntryFn)(struct EventEntry* entry, void* buffer);
typedef struct EventEntry
{
    unsigned int flags;
    int field_4; // nonzero: buffer is not owned
    EventEntryFn cb_8;
    EventEntryFn cb_C;
    int size;
    void* buffer;
} EventEntry;

typedef struct EventNode
{
    int field_0;
    struct EventNode* next;
    int field_8;
    int count;
    EventEntry entry;
} EventNode;
extern EventNode* dword_8008D618;
extern EventNode* dword_8008B4A8;
extern EventNode* dword_8008D60C;

typedef struct
{
    int x;
    int y;
    int z;
} Vec3i;

extern int dword_8008D4D8;
extern short word_8008D780;
extern unsigned char byte_8008BD38;
extern unsigned long* dword_8008D42C;

extern int dword_8008B500[];

extern int dword_80091CA0;

extern int dword_80091C30[];

extern int dword_80091C60[];

extern short word_8008B860;

#endif
