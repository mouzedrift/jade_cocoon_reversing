#ifndef GLOBALS_H
#define GLOBALS_H

#include "sdk.h"
#include "enums.h"
#include "common.h"

typedef struct
{
    int mode_0; // index into screenModes_8007C728 (the screen width / height)
    int vsyncsPerFrame_4; // Draw waits until vsyncCounter_8008B4B4 reaches it
    short x_8;
    short y_A;
    short w_C; // word_8008B4E4
    short h_E; // word_8008B4E6
} DisplayConfig;

// Event list nodes (event.c / skel_draw.c). The list head has the same layout as a node.
struct EventEntry;
typedef void (*EventEntryFn)(struct EventEntry* entry, void* buffer);
typedef struct EventEntry
{
    unsigned int flags;
    int index_4; // index among its EventDesc's entries; only entry 0 owns (frees) the shared buffer
    EventEntryFn cb_8;
    EventEntryFn cb_C;
    int size;
    void* buffer;
} EventEntry;

// model and model list (defined in model.h)
typedef struct Model Model;
typedef struct ModelList ModelList;

typedef struct EventNode
{
    int prev_0; // the previous node
    struct EventNode* next;
    int index_8; // index in the list
    int count;
    EventEntry entry;
} EventNode;

#include "unit.h" // UnitStatus, UnitStats, Minion


// the settings word (SaveData.settings_1C == saveData_8008B570.settings_1C.word); most code tests it with masks
typedef union Settings
{
    unsigned int word;
    struct
    {
        unsigned int a_0 : 3; // 3 = ... (compared by eventfnc / combbtl / pad_text)
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
    unsigned char bytes[4]; // tested bytewise (msg_window)
} Settings;

typedef struct
{
    int x;
    int y;
    int z;
} Vec3i;

// Levant's position + rotation (SaveData.levant_7A8 == levantPos_8008BD18; rot == saveData_8008B570.levant_7A8.rot)
typedef struct LevantPos
{
    Vec3i pos;
    SVECTOR rot; // rot.vy: facing angle
} LevantPos;

// one inventory slot (SaveData.inv_24.inventory_4; GAME's GetInventoryTable_800AD604 returns a category's table)
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
    int emptyCocoons_284; // saveData_8008B570.inv_24.emptyCocoons_284
    unsigned int flags_288[2]; // valuablesFlags_8008B81C; bits set by GAME's SetValuableFlag_800AD68C
    unsigned char bits_290[0x13]; // bit flags (GAME's TestEventFlag_800AD0D4 / SetEventFlag_800AD0F8)
    unsigned char vars_2A3[0x14]; // GAME's GetEventVar_800AD154 / SetEventVar_800AD16C
} SaveInventory;

// a value saved per map (SaveData.mapVars_2F8, GAME's FindMapVar_800ADBA0 / SetMapVar_800ADC5C), keyed by the map ids
typedef struct
{
    short area_0;
    short map_2;
    short sub_4;
    short value_6;
} SaveMapVar;

typedef struct
{
    int flags_0; // option bits; bit 6: no pad vibration (config.c, StartPadVibration_80036528)
    int playTime_4; // vsyncs, counted by the vsync handler while not paused
    unsigned short buttonConfig_8[10]; // == saveData_8008B570.buttonConfig_8
    Settings settings_1C; // == saveData_8008B570.settings_1C.word
    union
    {
        int i;
        unsigned char b;  // read as a byte by CONFIG
        unsigned short h; // the colour as most of the menus read it
        short s;          // ... and as the field windows read it
        struct UiColorBytes
        {
            unsigned char b_0[4];
        } w; // kept whole by LOAD over a loaded save
    } uiColor_20;
    SaveInventory inv_24; // == playerYan_8008B594
    short chapter_2DC; // 0x8008B84C (Meos4: currentChapter)
    short chapterNext_2DE; // next chapter to play the intro of (CHAPTER)
    short mapVariant_2E0; // picks the destination-map set of MAP (destMaps_800B9348); set per chapter (CHAPTER) and by EvCmdSetMapVariant_800BA880
    short field_2E2;
    struct
    {
        short cur_0;  // [0] area, [1] map, [2] entrance (Meos4: mapId); [3] mesh
        short prev_2; // the same before the last map change (-1: none)
    } mapId_2E4[4]; // 0x8008B854
    int nMapVars_2F4;
    SaveMapVar mapVars_2F8[150];
    LevantPos levant_7A8; // == levantPos_8008BD18
    char field_7BC[0xC]; // returned by GetSaveDataField7BC_80033AC4
    // Levant's 0x48-byte status block (same layout as a minion's status_84)
    UnitStatus levantStatus_7C8; // saveData_8008B570.levantStatus_7C8: name_10 == saveData_8008B570.levantStatus_7C8.name_10, field_1C[0..2] the
                                 // equipped weapon / armor / accessory, level_44 the rank (saveData_8008B570.levantStatus_7C8.level_44)
    int field_810; // == dword_8008BD80
    unsigned int allMinionsBitfields_814[7]; // bits counted by GetCapturedMinionsCount_800125B8
    int hasArmor_830; // SetLevantHasArmor_800AC380 (GAME), picks the model
    short weaponKind_834; // GAME: SetLevantWeaponKind_800AC3A4
    short outfit_836;     // GAME: SetLevantOutfit_800AC3B0
    unsigned short tbl_838[12]; // the tables GAME's GetMapEncounterFlags_800A53CC picks by mapId_2E4[0]/[1] (TITLE fills them with 0x8000)
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
    int flags_0;           // 0x40 checked by CheckMagicUsable_80034068; 0x04/0x40/0x80 mapped by GetMagicTargetFlags_8001ACE4
    unsigned char mpCost_4; // GetMagicMpCost_8001AC58 (Agni 10, Agnis 15, Agnia 25)
    unsigned char field_5;
    unsigned char effect_6; // GetMagicEffect_8001AC8C
    unsigned char kind_7;   // with flags_0 & 0x40: 0 restores hp, 1 cures status (CheckMagicUsable_80034068)
    short element_8;        // enum Element (GetMagicElement_8001AD30)
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

// font (InitFonts copies a SPRT from the public TIY into its head, which is laid out as one)
typedef struct
{
    O_TAG;
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
    short u0_18;      // the glyph sheet's top-left texel (the TIY sprite's u / v)
    short v0_1A;
    short columns_1C; // glyphs per sheet row
    unsigned short firstChar_1E;
    short clutX_20;
    short clutY_22;
    unsigned char* widths_24;
    short charsPerClut_28; // glyphs per CLUT row (the glyph index / this picks the CLUT row)
    short clutOffset_2A;   // added CLUT row (text colour, SetFontClutOffset_8003F900)
} Font;


// a record table (AllocRecordTables_80026D78 / LoadRecordTable_80026EF8, model.c): count_0 records of 8 bytes
typedef struct
{
    int count_0;
    int field_4;
    unsigned short* records_8; // count_0 records of 4 halfwords, heap allocated
} RecordTable;


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
    short kind_2;               // weapons: the weapon kind (GAME SetLevantWeaponKind_800AC3A4; weaponEffectIds_80079708 index)
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
    short pad_E;
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
extern const char* itemNames_8007CB78[0x2b];
extern EquipmentData weaponData_8007D04C[0x17];
extern const char* weaponNames_8007CFF0[0x17];
extern int weaponPrices_8007D388[0x17];
extern EquipmentData armorData_8007D420[0xf];
extern const char* armorNames_8007D3E4[0xf];
extern unsigned short armorPrices_8007D64C[0xf];
extern EquipmentData accessoryData_8007D6B0[0x11];
extern const char* accessoryNames_8007D66C[0x11];
extern unsigned short accessoryPrices_8007D914[0x11];
extern unsigned int xaRequestPending_80096118;
extern int battleMusic_80091CFC;
extern int battleStageId_80083BD0;
extern int fileRequestQueue_80086540;
extern void* fileBuffer_8008656C;
extern int sealResultFlags_80079320[];
extern MinionBaseStats minionBaseStats_8007A4B4[];
extern ActionData abilityActions_80083594[39];
extern PadVibration padVibration_80095460[];
extern const char* personNames_8007CB20[];
extern unsigned char personMergeInfo_8007CB4C[][4]; // per person (GetPersonMergeInfo_8001CD58); [0] != 0xFF: what a merge turns the minion into (MergeMinions_800B9FC8)
extern int bStopDrawingMovie_8008D45C;
extern int eventDispatchHalt_8008B540;
extern int freeActorModels_80091CA0;
extern int frozenFrames_800918B8;
extern int fileBufferInUse_80086564;
extern int unusedWord_80098688;
extern MagicData magicData_8007C438[];
extern ActionData magicActions_8007C5A0[];
extern int loadFade_80091C30[];
extern unsigned short itemPrices_8007CED8[];
extern unsigned char keyItemIcons_8007CFC8[0x26];
// a sequence slot (seqSlots_800833E4, PlaySeqSlot_80031160)
typedef struct
{
    int sep_0; // 1: the slot sound's second SEP (sepAccessNum_14), else the first
    int seq_4; // sequence number in the SEP
} SeqSlot;
extern SeqSlot seqSlots_800833E4[];
extern unsigned char drawEnvRed_8008D448[3];
typedef struct
{
    int m[3];
} struct_int3;
// an RGB colour (+ pad / code byte) passed as 4 bytes
typedef struct
{
    unsigned char c[4];
} ColorRGBA;
// 0x14 bytes copied without alignment
typedef struct
{
    unsigned char data[0x14];
} struct_20_u8;

// file load request (cd.c queue); fileId_10 == 0x10000 marks a free pool entry
typedef struct FileRequest
{
    struct FileRequest* next; // the older neighbour (toward the queue head that is processed first)
    int newer_4;              // FileRequest*: the newer neighbour, processed after this one
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
extern Font fonts_80095FB0[];
extern unsigned char magicIcons_8007C708[0x1E];
extern unsigned char itemIcons_8007CEAC[0x2B];
extern char* keyItemNames_8007CF30[0x26];
extern const char* magicNames_8007C348[0x1E * 2];
extern unsigned short statGrowthTable_80079348[0x15];
extern int fadeFlags_800918B0;
extern XaRequest xaRequest_80096110;
extern int currentAreaMap_80091C88;
extern int currentArea_80091C44;
extern int fadeFrame_800918B4;
extern unsigned char armorOutfits_8007D588[16];
extern int primBufferOffset_8008B550;
extern int primBufferStart_800960A0[2];
extern int primAllocPtr_800960A8[2];
extern unsigned long* decodedImageData_8008B4A0;
extern enum GameStates currentGameState_8008D4B4;
extern volatile int unknownFlags_8008D678;
extern short titleMenuState_8008B558[2]; // [0]: title screen entry (0 press start, 1 menu); [1]: title menu selection (GAME GetGameStartMode_800A72C8)
extern DslFILE Data001File_800954A8;
extern int DsReadSyncResult_8008D630;
extern int cdReadFlags_8008B55C; // 0x10: no LoadFileIntoBuffer_8003CB7C in progress
extern int displayStartFrames_800918BC;
extern int ODEIsEvenAddressDrawn_800918C0;
extern DisplayConfig display_8008B4D8;
extern long cdRomEventDescError_8008B490;
extern long vsyncEventDesc_8008B494;
extern volatile int vsyncCounter_8008B4B4;
extern volatile int gnFrame_8008D610;
extern volatile int xaTimer_8008D450;
extern volatile int unpausedFrames_8008D404;
extern SaveData saveData_8008B570;
#ifdef __psyz /* an alias (config/aliases.txt), on PC the place itself */
#define playerYan_8008B594 (saveData_8008B570.inv_24)
#else
extern SaveInventory playerYan_8008B594; // == saveData_8008B570.inv_24
#endif
#ifdef __psyz /* an alias (config/aliases.txt), on PC the place itself */
#define levantPos_8008BD18 (saveData_8008B570.levant_7A8)
#else
extern LevantPos levantPos_8008BD18; // == saveData_8008B570.levant_7A8
#endif
extern unsigned long bDoubleBuffer_8008D428;
extern OT_TYPE OT_8008D798[2][8];
extern OT_TYPE OT_8008D7D8[2][1024];
extern OT_TYPE OT_8008F7D8[2][1024];
extern OT_TYPE OT_800917D8[2][16];
extern OT_TYPE OT_80091858[2][1];
extern OT_TYPE OT_80091868[2][4];
extern OT_TYPE OT_80091888[2][4];
extern OT_TYPE OT_800918A8[2][1];

extern OT_TYPE* pOT_8008D788;
extern OT_TYPE* pOT_8008D4AC;
extern OT_TYPE* pOT_8008D454;
extern OT_TYPE* pOT_8008D690;
extern OT_TYPE* pOT_8008D78C;
extern OT_TYPE* pOT_8008D5F4;
extern OT_TYPE* pOT_8008B4C8;
extern OT_TYPE* pOT_8008D3EC;

extern int numFilesInsideTiy_8008B4BC;


extern ActionData weaponActions_8007D274[0x17];
extern unsigned short growthKindThresholds_80079374[];


extern unsigned short padButtonBits_8007CAD8[0xe];
extern unsigned short defaultButtonConfig_8007CAF4[0xa];
extern int minionVariantSeed_8008D4DC;
extern int weaponEffectIds_80079708[];
typedef struct
{
    short id;
    short field_2;
    int field_4;
} IdEntry;
typedef struct
{
    char pad_0[0xC];
    int count;
    IdEntry* items;
} IdEntryList;

extern int speciesMagicBits_8007A6AC[];
extern int sceneBrightness_8008D40C;

// a hit window of an attack animation / effect, in frames (-1: none)
typedef struct
{
    short start_0;
    short end_2;
} HitTimes;

typedef struct
{
    int field_0;
    unsigned int flags_4;
    int field_8;
    int field_C;
    char pad_10[0x120];
    int pad_130;
} struct_obj_F;

extern EventNode* modelTasks_8008D618;
extern EventNode* effectObjects_8008B4A8;
extern EventNode* miscTasks_8008D60C;
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


extern int memCardInfo_8008D4D8;
extern short effectOutcomeFlag_8008D780[2];
extern unsigned long* mdecEffectVlcBuffer_8008D42C;


extern int freeActorModels_80091CA0;

extern int loadFade_80091C30[];


extern MATRIX boneMatrices_80098188[];

#endif
