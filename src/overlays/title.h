// TITLE.BIN: declarations shared by its source files
#ifndef _TITLE_H_
#define _TITLE_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"
#include "unit_stats.h"

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
extern int titleMenuTaskDesc_800A2778[6];
extern int newGameTaskDesc_800A2790[6];
extern int titleSoundTaskDesc_800A27A8[6];
extern int titleTaskList_800A27C0;
extern void *dword_800A27C4[9];
extern void (*titleMenuHandlers_800A27E8[8])();
extern int nameOvlRequest_800A2808;
extern int pulseMax_800A280C;
extern int pulseMin_800A2810;
extern unsigned int titleIdleTimer_800A2814;
extern int titleResult_800A2818;

extern UnitStatus levantInitStatus_800A2730;

// frees a heap block and clears the pointer to it
#define FREE_PTR(p) do { if (p) { free3_8003FC6C(p); (p) = 0; } } while (0)

#endif
