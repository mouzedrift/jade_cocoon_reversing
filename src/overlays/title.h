// TITLE.BIN: declarations shared by its source files
#ifndef _TITLE_H_
#define _TITLE_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "main.h"
#include "sound.h"
#include "unit_stats.h"
#include "font.h"
#include "engine.h"

typedef struct TitleMenuItem
{
    unsigned short flags_0;
    short pad_2;
    int icon_4; // sprite index (type 1 item)
    void* sprts_8;
    void* tpages_C;
    short x_10;
    short y_12;
    char pad_14[8];
} TitleMenuItem;

typedef struct
{
    TitleMenuItem items[2];
} TitleMenuWindow;

typedef struct
{
    int flags_0, time_4, anim_8, cursor_C; // a DrawMenuWindows_8002A5A4 menu (CombSelMenu)
    TitleMenuWindow** windows_10;
    int ot_14;
} TitleMenuCfg;

typedef struct { char rgb[4]; } TitleColor;

extern int dword_800A05A0;
extern const TitleColor nameCursorPulseColor_800A05A4;
extern const char aCaution_800A05A8[];
extern const char str_800A05BC[];
extern const char str_800A0604[];
extern const char str_800A0640[];
extern const char aThereAreNoFreeB_800A0658[];
extern const char aTheMEMORYCARDIn_800A069C[];
extern const TitleMenuWindow titleMenuWin0_800A06D8;
extern const TitleMenuWindow titleMenuWin1_800A0710;
extern const TitleMenuWindow titleMenuWin2_800A0748;
extern const TitleMenuWindow titleMenuWin3_800A0780;
extern const TitleMenuWindow titleMenuWin4_800A07B8;
extern const TitleMenuWindow titleMenuWin5_800A07F0;
extern const TitleMenuWindow titleMenuWin6_800A0828;
extern const TitleMenuWindow titleMenuWin7_800A0860;
extern const TitleMenuCfg titleMenuCfg_800A0898;
extern const TitleColor logoPulseColor_800A08B0;
extern const char debugLevantName_800A08B4[];
extern const int dword_800A08C0[2];
extern char levantName_800A2718[];
extern int dword_800A2728;
extern int dword_800A272C;
extern EventDesc titleMenuTaskDesc_800A2778;
extern EventDesc newGameTaskDesc_800A2790;
extern EventDesc titleSoundTaskDesc_800A27A8;
extern EventDesc* titleTaskList_800A27C0[10];
extern void (*titleMenuHandlers_800A27E8[8])();
extern int nameOvlRequest_800A2808;
extern int pulseMax_800A280C;
extern int pulseMin_800A2810;
extern unsigned int titleIdleTimer_800A2814;
extern int titleResult_800A2818;

extern UnitStatus levantInitStatus_800A2730;

// frees a heap block and clears the pointer to it
#define FREE_PTR(p) do { if (p) { free3_8003FC6C(p); (p) = 0; } } while (0)

typedef struct TitleTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} TitleTask;
typedef struct NameEntryWork
{
    char pad_0[0x5C];
    int pulseTime_5C;
    int pulsePeak_60;
    int pulseStep_64;
    int timer_68;
    int holding_6C;
    SPRT* sprts_70;      // from LoadTiy_80028E74
    DR_TPAGE* tpages_74; // one per sprite
} NameEntryWork;
typedef struct TitleMenuWork
{
    int frames_0; // menu frame counter, reused as the idle fade-out counter
    int field_4;
    int field_8;
    SPRT* sprts_C;       // from LoadTiy_80028E74
    int field_10;
    DR_TPAGE* tpages_14; // one per sprite
    char pad_18[4];
    short cursor_1C[4]; // UpdateMenuCursor_8003D794 state
    short selected_24;
    short field_26;
} TitleMenuWork;
// window style for DrawWindow_80042460 (CombSelBox)
typedef struct TitleWinStyle
{
    short color_0;
    char colors_2;
    char frame_3;
} TitleWinStyle;
typedef struct
{
    short x, y, w, h;
} TitleRect;

extern void NewGameLoadSprites_800A093C(TitleTask* t, NameEntryWork* c);
extern void NewGameOpeningMovie_800A09C0(TitleTask* t);
extern void NewGameLoadNameOvl_800A0A1C(TitleTask* t);
extern void NewGameStartNameEntry_800A0A70(TitleTask* t);
extern void NewGameNameEntry_800A0AE8(TitleTask* t, NameEntryWork* c);
extern void DrawNameEntrySprites_800A0D18(SPRT* sprts, DR_TPAGE* tpages, int mode, NameEntryWork* c);
extern void NewGameAfterNameMovie_800A0C28(TitleTask* t, NameEntryWork* c);
extern void TitleExit_800A1AFC(TitleTask* t, int result);
extern void NewGameFadeOut_800A0BCC(TitleTask* t, NameEntryWork* c);
extern void SetNewGameStartMap_800A2650(void);
extern void StartNewGameTask_800A1B74(TitleTask* t);
extern void TitleEnterScreen_800A1070(TitleTask* t, TitleMenuWork* c);
extern void TitlePressStart_800A1174(TitleTask* t, TitleMenuWork* c);
extern void TitleMenu_800A1310(TitleTask* t, TitleMenuWork* c);
extern void DrawTitleBackground_800A1F98(SPRT* sprts, DR_TPAGE* tpages, TitleMenuWork* work); // work unused, but every caller passes it
extern void TitleIdleFadeOut_800A1AC0(TitleTask* t, int* cnt);
extern void DrawTitleMenu_800A1760(TitleMenuWork* work, int sel, int frames);
extern void NewGameCheckMemCards_800A14A8(TitleTask* t);
extern void NoMemCardWarning_800A158C(TitleTask* t);
extern void NoFreeBlocksWarning_800A166C(TitleTask* t);
extern void NewGameMemCardOk_800A1728(TitleTask* t);
extern void StartNewGameTask_800A1B74(TitleTask* t);
extern void DrawTitleMenuWindows_800A1780(TitleMenuWork* work, int sel);
extern void InitSaveData_800A211C(void);
extern void ClearCapturedMinions_800A2214(void);
extern void ClearMinionSlots_800A2450(void);
extern void ResetMapIds_800A242C(void);
extern void LoadGameWait_800A1CC0(TitleTask* t);
extern void SetNewGameStartMap_800A2650(void);
extern void ConfigWaitUiTiy_800A1DD8(TitleTask* t);
extern void ConfigWait_800A1E24(TitleTask* t, TitleMenuWork* u);
extern void ConfigReturn_800A1E9C(TitleTask* t, TitleMenuWork* u);
extern void ClearInventory_800A2358(void);
extern void GiveDebugStartItems_800A22FC(void);
extern void InitStub_800A2424(void);
extern void InitLevantEquipment_800A20F4(void);
extern void ClearMapVars_800A2110(void);
extern void InitFlagTables_800A2540(void);
extern Vec3i dword_800B069C; // Levant's start position
extern SVECTOR dword_800B06A8; // Levant's start rotation

/* other overlays resident with TITLE: LOAD (and its LIBMCRD modules), NAME, CONFIG */
extern void LoadMenuInit_800B7674(int mode, int b);
extern int IsLoadMenuActive_800B793C(void);
extern int GetLoadMenuLoaded_800B7914(void);
extern void ScanCardSaves_800BAFB0(int slot);
extern int GetCardFreeBlocks_800BAE2C(void);
extern int GetCardSaveCount_800BAE3C(void);
extern void sub_800BB5DC(void); // LOAD's MemCardStart (PSY-Q LIBMCRD)
extern void sub_800BB64C(void); // LOAD's MemCardStop
extern void sub_800BB9F4(int chan); // LOAD's MemCardAccept
extern void sub_800BC9DC(int mode, int* cmd, int* result); // LOAD's MemCardSync
extern void StartNameEntry_800B6E4C(void* a0, int a1);
extern int IsNameEntryActive_800B6FC8(void);
extern void StartConfigMenu_800C2EB4(void);
extern int IsConfigMenuActive_800C45D8(void);

/* exe-side, to move to an exe header */
extern void EncodeName_8003F7C8(void* text, void* out);
extern void SsSepSetDecrescendo(short, short, short, long);
extern void PulseColor_80033394(void* out, void* c0, void* c1, int t, int period, int half);
extern void PlayMusicSeq_80031260(void* a0, int a1, int a2);
extern void DrawWindow_80042460(void* rect, void* box, void* ot, unsigned int a3);
extern void srand(unsigned int seed); // PSY-Q LIBC
extern void UpdateMenuCursor_8003D794(void* a0, int a1);
extern void CheckMemCards_8003BB1C(void);
extern unsigned short word_8008B55A;
extern int dword_8008BD80;

#endif
