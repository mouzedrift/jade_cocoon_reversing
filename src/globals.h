#ifndef GLOBALS_H
#define GLOBALS_H

#include "SYS/TYPES.H"
#include "LIBDS.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "enums.h"
#include "common.h"

typedef struct
{
    int field_0;
    int vsyncsPerFrame_4; // Draw waits until vsyncCounter_8008B4B4 reaches it
    short field_8_x;
    short field_A_y;
    short field_C_w; // word_8008B4E4
    short field_E_h; // word_8008B4E6
} DisplayConfig;

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

// model and model list (defined in tu_8001EA48.h)
typedef struct Model Model;
typedef struct ModelList ModelList;

typedef struct EventNode
{
    int field_0;
    struct EventNode* next;
    int field_8;
    int count;
    EventEntry entry;
} EventNode;

#include "unit.h" // UnitStatus, UnitStats, Minion


// the settings word (SaveData.settings_1C == settingsFlags_8008B58C.word); most code tests it with masks
typedef union Settings
{
    unsigned int word;
    struct
    {
        unsigned int a_0 : 3; // 3 = ... (compared by eventfnc / combbtl / tu_8003D198)
        unsigned int b_3 : 1;
        unsigned int c_4 : 1;
        unsigned int d_5 : 1;
        unsigned int e_6 : 1;
        unsigned int bgmVol_7 : 7;
        unsigned int sfxVol_14 : 7;
        unsigned int h_21 : 1;
        unsigned int i_22 : 1;
        unsigned int j_23 : 1;
        unsigned int k_24 : 1;
        unsigned int l_25 : 7;
    } bits;
    unsigned char bytes[4]; // tested bytewise (tu_80034068)
} Settings;

typedef struct
{
    int x;
    int y;
    int z;
} struct_v3;

// Levant's position + rotation (SaveData.levant_7A8 == levantPos_8008BD18; rot == levantRot_8008BD24)
typedef struct LevantPos
{
    struct_v3 pos;
    SVECTOR rot; // rot.vy: facing angle
} LevantPos;

// one inventory slot (SaveData.inv_24.inventory_4; GAME's sub_800AD604 returns a category's table)
typedef struct
{
    unsigned char id;    // 0xFF = empty
    unsigned char count;
} InvSlot;

// saveData_8008B570.inv_24 == playerYan_8008B594 (code reaches it through either symbol)
typedef struct
{
    int yan_0; // money
    InvSlot inventory_4[5][0x40];
    int emptyCocoons_284; // levantEmptyCocoons_8008B818
    unsigned int flags_288[2]; // valuablesFlags_8008B81C; bits set by GAME's sub_800AD68C
    unsigned char bits_290[0x13]; // bit flags (GAME's sub_800AD0D4 / sub_800AD0F8)
    unsigned char vars_2A3[0x14]; // GAME's sub_800AD154 / sub_800AD16C
} SaveInventory;

// a value saved per map (SaveData.mapVars_2F8, GAME's sub_800ADBA0 / sub_800ADC5C), keyed by the map ids
typedef struct
{
    short area_0;
    short map_2;
    short sub_4;
    short value_6;
} SaveMapVar;

typedef struct
{
    int field_0; // bit 6: config.c
    int playTime_4; // vsyncs, counted by the vsync handler while not paused
    unsigned short buttonConfig_8[10]; // == buttonConfig_8008B578
    Settings settings_1C; // == settingsFlags_8008B58C.word
    union
    {
        int i;            // uiColor_8008B590
        unsigned char b;  // read as a byte by CONFIG
        unsigned short h; // read as a halfword by WPNSHOP
    } uiColor_20;
    SaveInventory inv_24; // == playerYan_8008B594
    short chapter_2DC; // 0x8008B84C (Meos4: currentChapter)
    short chapterNext_2DE; // next chapter to play the intro of (CHAPTER)
    short field_2E0;
    short field_2E2;
    struct
    {
        short field_0;
        short field_2;
    } mapId_2E4[4]; // 0x8008B854: [0..2].field_0 identify the map (Meos4: mapId); [3].field_0 = mesh
    int nMapVars_2F4;
    SaveMapVar mapVars_2F8[150];
    LevantPos levant_7A8; // == levantPos_8008BD18
    char field_7BC[0xC]; // returned by sub_80033AC4
    // Levant's 0x48-byte status block (same layout as a minion's status_84)
    UnitStatus levantStatus_7C8; // levantStatus_8008BD38: name_10 == playerName_8008BD48, field_1C[0..2] the
                                 // equipped weapon / armor / accessory, level_44 the rank (levantCaptureLevel_8008BD7C)
    int field_810; // == dword_8008BD80
    unsigned int allMinionsBitfields_814[7]; // allMinionsBitfields_8008BD84
    int field_830; // model index (GAME's sub_800ACB64)
    short field_834;
    short field_836;
    unsigned short tbl_838[12]; // the tables GAME's sub_800A53CC picks by mapId_2E4[0]/[1] (TITLE fills them with 0x8000)
    unsigned short tbl_850[18];
    unsigned short tbl_874[44];
    unsigned short tbl_8CC[22];
    unsigned short tbl_8F8[10];
    unsigned short tbl_90C[16];
    unsigned short tbl_92C[42];
    int pad_980;
    int field_984;
    Minion minions[15];
    UnitStats items[12]; // stored minion records, species_5C 0xD3 = empty slot
} SaveData;


// one of the 30 spells (magicData_8007C438, names in magicNames_8007C348)
typedef struct
{
    int field_0;           // flags (0x40 checked by CheckMagicUsable_80034068; 0x04/0x40/0x80 mapped by GetMagicTargetFlags_8001ACE4)
    unsigned char field_4; // MP cost (GetMagicMpCost_8001AC58; Agni 10, Agnis 15, Agnia 25)
    unsigned char field_5;
    unsigned char field_6;
    unsigned char field_7;
    short field_8;         // enum Element (GetMagicElement_8001AD30)
    short pad_A;
} MagicData;

// base stats per minion species (Meos4's randomizer: "minionStats", StatsStruct)
typedef struct
{
    unsigned char attack;
    unsigned char magicAttack;
    unsigned char defense;
    unsigned char magicDefense;
    unsigned char speed;
    unsigned char critical;
    signed char element; // enum Element
    unsigned char enhancementBody; // bit 0: special, bit 1: magic
} MinionBaseStats;

// per-port vibration state; motor_2 is the actuator data sent with PadSetAct
typedef struct
{
    unsigned short flags_0; // bit 0: actuators aligned
    unsigned char motor_2[2];
} PadVibration;

// XA audio request (event.c): played from DATA.001 file 0x439
typedef struct
{
    short field_0;
    short channel_2;     // CdlSetfilter channel
    short startSector_4; // in units of 32 sectors from the file start
    short length_6;      // in units of 32 sectors
} XaRequest;

// font (InitFonts copies a SPRT from the public TIY into the first 0x14 bytes)
typedef struct
{
    char pad_0[4];
    unsigned char r_4;
    unsigned char g_5;
    unsigned char b_6;
    unsigned char code_7;
    short x0_8;
    short y0_A;
    unsigned char u_C;
    unsigned char v_D;
    unsigned short clut_E;
    short w_10;
    short h_12;
    unsigned short* tpage_14;
    short field_18;
    short field_1A;
    short field_1C;
    unsigned short firstChar_1E;
    short clutX_20;
    short clutY_22;
    unsigned char* widths_24;
    short field_28;
    short field_2A;
} Font;


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
    int field_10;
    int field_14;
} struct_24;

// weapon / armor / accessory table entry (weaponData_8007D04C, armorData_8007D420, accessoryData_8007D6B0)
typedef struct
{
    short icon_0;               // index into equipmentIcons_8007D938
    short field_2;
    signed char statBonus_4[6]; // added to the six base stats by CalcEquippedStats_80033624
    char pad_A[0xA];
    int field_14;               // CalcEquippedStats_80033624 returns the largest one of the equipped items
} EquipmentData;

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


// per-element/status minimums applied by ApplyEquipmentModifiers_80033754
extern unsigned char accessoryModifiers_8007D848[17][12];
extern unsigned char armorModifiers_8007D598[15][12];
extern unsigned char itemEffects_8007CC24[0x2b];
extern unsigned short itemFlags_8007CC50[];
extern ActionData itemData_8007CCA8[0x2b];
extern int itemNames_8007CB78[0x2b];
extern EquipmentData weaponData_8007D04C[0x17];
extern int weaponNames_8007CFF0[0x17];
extern int weaponPrices_8007D388[0x17];
extern EquipmentData armorData_8007D420[0xf];
extern int armorNames_8007D3E4[0xf];
extern unsigned short armorPrices_8007D64C[0xf];
extern EquipmentData accessoryData_8007D6B0[0x11];
extern int accessoryNames_8007D66C[0x11];
extern unsigned short accessoryPrices_8007D914[0x11];
extern unsigned int xaRequestPending_80096118;
extern int battleMusic_80091CFC;
extern int battleStageId_80083BD0;
extern int fileRequestQueue_80086540;
extern void* fileBuffer_8008656C;
extern int dword_80079320[];
extern MinionBaseStats minionBaseStats_8007A4B4[];
extern ActionData abilityActions_80083594[];
extern PadVibration padVibration_80095460[];
extern int personNames_8007CB20[];
extern unsigned char personMergeInfo_8007CB4C[][4]; // per person (GetPersonMergeInfo_8001CD58); [0] != 0xFF: what a merge turns the minion into (MergeMinions_800B9FC8)
extern int bStopDrawingMovie_8008D45C;
extern int eventDispatchHalt_8008B540;
extern int dword_80091CA0;
extern int frozenFrames_800918B8;
extern int fileBufferInUse_80086564;
extern int dword_80098688;
extern MagicData magicData_8007C438[];
extern ActionData magicActions_8007C5A0[];
extern int areaHeap_80091C20;
extern int loadFade_80091C30[];
extern unsigned short itemPrices_8007CED8[];
extern unsigned char keyItemIcons_8007CFC8[0x26];
extern short seqSlotSepAccessNum_80091D0C;
typedef struct
{
    int field_0;
    int field_4;
} struct_833E4;
extern struct_833E4 seqSlots_800833E4[];
extern unsigned char drawEnvRed_8008D448[3];
extern char copyright_80086948[];
extern char genkiMovie_80086968[];
extern char craveEntertainmentMovie_80086988[];
extern char demoDisclaimer_800869A8[];
extern char introAnime_800869C8[];
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

// file load request (cd.c queue); fileId_10 == 0x10000 marks a free pool entry
typedef struct FileRequest
{
    struct FileRequest* next;
    int field_4;
    int key;
    unsigned int flags_C; // 0x100 / 0x1000: GetFileRequestStatus returns 2 / 3
    int fileId_10;        // DATA.001 file id
    int offset_14;        // from FileRequestDesc.offset_8
    int size_18;          // from FileRequestDesc.size_C
    void* dest_1C;        // destination buffer
    void* params_20;      // copy of the request parameters (fileRequestParams_800954C0)
    void (*callback_24)(void* params, void* data);
} FileRequest;

// what QueueFileRequest_8003BC84 takes; copied into a FileRequest (params_14 into fileRequestParams_800954C0)
typedef struct FileRequestDesc
{
    unsigned int flags_0;  // -> FileRequest.flags_C; bit 2: StartFileRequestTask_8003C6C8 waits for it
    int fileId_4;          // DATA.001 file id
    int offset_8;          // offset into the file (AddFileRequest_80025D00 converts sectors to bytes)
    int size_C;            // bytes to read (likewise converted from sectors)
    void* dest_10;         // destination buffer, 0 = the loader's own
    void* params_14;       // paramsSize_18 bytes, copied and passed to callback_1C
    int paramsSize_18;
    void* callback_1C;     // void (*)(void* params, void* data)
} FileRequestDesc;
extern FileRequest fileRequests_80095C90[0x14];

extern int** mapLoaderTask_800B1DC4;
extern int** areaLoaderTask_800B1DB8;
extern short equipmentIcons_8007D938[];
extern int areaReload_80082670;
extern short word_8008B862;
extern int areaPreloading_80082678;
extern short areaPreload_80091C40[];
extern FileRequest* fileRequestTail_8008654C;
extern SPRT* uiTiySprts_8008D620;        // the UI TIY (OnUiTiyLoaded_8002BFCC)
extern DR_TPAGE* uiTiyTPages_8008D3F4;
extern int uiTiyLoaded_8008B4E8;
extern int frameCount_8008D3FC;
extern int geomScreenDistance_8008B548;
extern int cameraZoom_8008B4F8;
extern int motionBlurOn_800918C4;
extern unsigned short padHeld_800918D0[];
extern void* mdecVLCBuffer_80086F94;
extern int actorHeap_80091990[4];
extern Font fonts_80095FB0[];
extern unsigned char magicIcons_8007C708[0x1E];
extern unsigned char itemIcons_8007CEAC[0x2B];
extern char* keyItemNames_8007CF30[0x26];
extern int magicNames_8007C348[0x1E * 2];
extern unsigned short statGrowthTable_80079348[0x15];
extern int fadeFlags_800918B0;
extern XaRequest xaRequest_80096110;
extern int currentAreaMap_80091C88;
extern int currentArea_80091C44;
extern int* mdecEffectSchedule_80091C00;
extern int fadeFrame_800918B4;
extern unsigned char armorOutfits_8007D588[16];
extern int dword_8008B550;
extern int primBufferStart_800960A0[2];
extern int primAllocPtr_800960A8[2];
extern unsigned long* decodedImageData_8008B4A0;
extern int defaultAllocList_80096090[4];
extern enum GameStates currentGameState_8008D4B4;
extern volatile int unknownFlags_8008D678;
extern short word_8008B558[2];
extern DslFILE Data001File_800954A8;
extern int DsReadSyncResult_8008D630;
extern int dword_8008B55C;
extern int displayStartFrames_800918BC;
extern int ODEIsEvenAddressDrawn_800918C0;
extern DisplayConfig display_8008B4D8;
extern long cdRomEventDescError_8008B490;
extern long vsyncEventDesc_8008B494;
extern int dword_8008B574;
extern volatile int vsyncCounter_8008B4B4;
extern volatile int gnFrame_8008D610;
extern volatile int xaTimer_8008D450;
extern volatile int unpausedFrames_8008D404;
extern SaveData saveData_8008B570;
extern SaveInventory playerYan_8008B594; // == saveData_8008B570.inv_24
extern LevantPos levantPos_8008BD18; // == saveData_8008B570.levant_7A8
extern SVECTOR levantRot_8008BD24;   // == saveData_8008B570.levant_7A8.rot
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

extern Settings settingsFlags_8008B58C;
extern int numFilesInsideTiy_8008B4BC;


extern ActionData weaponActions_8007D274[0x17];
extern unsigned short growthKindThresholds_80079374[];
int FindModelIndex_80026630(ModelList* p, unsigned int id);
void ClearModel_800266CC(Model* p);
int FindFreeModelIndex_8002667C(ModelList* p);
void FreeModel_80024C48(Model* p);
void ApplyModelFtgSwaps_80025C38(Model* p, int flag);
int AddFileRequest_80025D00(Model* p, FileRequestDesc* q);
void OnModelFileLoaded_80025D7C(int* a0, int b);


extern unsigned short padButtonBits_8007CAD8[0xe];
extern unsigned short defaultButtonConfig_8007CAF4[0xa];
extern int minionVariantSeed_8008D4DC;
extern int weaponEffectIds_80079708[];
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

extern int speciesMagicBits_8007A6AC[];
extern int sceneBrightness_8008D40C;

typedef struct
{
    short field_0;
    short field_2;
} struct_4s;

typedef struct
{
    int field_0;
    unsigned int flags_4;
    int field_8;
    int field_C;
    char pad_10[0x120];
    int field_130;
} struct_obj_F;

extern unsigned short buttonConfig_8008B578[];
extern EventNode* modelTasks_8008D618;
extern EventNode* effectObjects_8008B4A8;
extern EventNode* dword_8008D60C;
extern EventNode* cameraTask_8008D4A0;
extern EventNode* effectTask_8008D3F8;
extern EventNode* xaTask_8008B560;
extern EventNode* sporeTask_8008D464;
extern EventNode* soundTask_8008D4A4;
extern EventNode* modelLoaderTask_8008B54C;
extern EventNode* overlayLoaderTask_8008D4C0;
extern EventNode* fadeTask_8008D628;
extern EventNode* actorTasks_8008D43C;
extern EventNode* screenFlashTasks_8008D61C;

typedef struct
{
    int x;
    int y;
    int z;
} Vec3i;

extern int memCardInfo_8008D4D8;
extern short effectOutcomeFlag_8008D780;
extern unsigned long* mdecEffectVlcBuffer_8008D42C;


extern int dword_80091CA0;

extern int loadFade_80091C30[];


extern short pendingArea_8008B860;
extern MATRIX boneMatrices_80098188[];

#endif
