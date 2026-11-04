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
    int f4;
    void* f8;
    void* fC;
    short x_10;
    short y_12;
    char pad_14[8];
} TitleMenuItem;

typedef struct
{
    TitleMenuItem items[2];
} TitleBlk38M;

typedef struct
{
    int f0, f4, f8, fC;
    TitleBlk38M** windows_10;
    int f14;
} TitleCfgM;

typedef struct { char c[4]; } Blk4_;

extern int dword_800A05A0;
extern const char asc_800A05A4[];
extern const char aCaution_800A05A8[];
extern const char str_800A05BC[];
extern const char str_800A0604[];
extern const char str_800A0640[];
extern const char aThereAreNoFreeB_800A0658[];
extern const char aTheMEMORYCARDIn_800A069C[];
extern const TitleBlk38M dword_800A06D8;
extern const TitleBlk38M dword_800A0710;
extern const TitleBlk38M dword_800A0748;
extern const TitleBlk38M dword_800A0780;
extern const TitleBlk38M dword_800A07B8;
extern const TitleBlk38M dword_800A07F0;
extern const TitleBlk38M dword_800A0828;
extern const TitleBlk38M dword_800A0860;
extern const TitleCfgM dword_800A0898;
extern const Blk4_ dword_800A08B0;
extern const char byte_800A08B4[];
extern const int dword_800A08C0[2];
extern char levantName_800A2718[];
extern int dword_800A2728;
extern int dword_800A272C;
extern int dword_800A2778[6];
extern int dword_800A2790[6];
extern int dword_800A27A8[6];
extern int dword_800A27C0;
extern void *dword_800A27C4[9];
extern void (*off_800A27E8[8])();
extern int dword_800A2808;
extern int dword_800A280C;
extern int dword_800A2810;
extern unsigned int dword_800A2814;
extern int dword_800A2818;

extern UnitStatus dword_800A2730;

#endif
