// CHAPTER.BIN: declarations shared by its source files
#ifndef _CHAPTER_H_
#define _CHAPTER_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "main.h"
#include "sound.h"
#include "sound_seq.h"
#include "movie.h"

typedef struct ChapterEntry
{
    short mapVariant_0; // SaveData.mapVariant_2E0 while the chapter plays
    short pad_2;
    int startPoint_4;   // map point key (GAME's FindMapEntrance_800ADCEC) the chapter starts at
    int music_8;
    int fadeBgm_C;
    int movie_10;
    int **areaMapVars_14; // per area (6): map var (area, map, 0) = [map] for each map of the area
    short *mapVars_18;    // (area, map, sub, value) map var records up to value -1
} ChapterEntry;

extern int dword_800B66C0;
extern int chapter0Area2Vars_800B6BC4[12];
extern int *chapter0AreaVars_800B6BF4[6];
extern short chapter0MapVars_800B6C0C[8];
extern int chapter1Area1Vars_800B6C1C[12];
extern int chapter1Area4Vars_800B6C4C[5];
extern int *chapter1AreaVars_800B6C60[6];
extern short chapter1MapVars_800B6C78[20];
extern int chapter2Area1Vars_800B6CA0[12];
extern int chapter2Area4Vars_800B6CD0[5];
extern int *chapter2AreaVars_800B6CE4[6];
extern short chapter2MapVars_800B6CFC[28];
extern int chapter3Area1Vars_800B6D34[12];
extern int chapter3Area4Vars_800B6D64[5];
extern int *chapter3AreaVars_800B6D78[6];
extern short chapter3MapVars_800B6D90[20];
extern int chapter4Area1Vars_800B6DB8[12];
extern int chapter4Area4Vars_800B6DE8[5];
extern int *chapter4AreaVars_800B6DFC[6];
extern short chapter4MapVars_800B6E14[32];
extern int chapter5Area2Vars_800B6E54[12];
extern int chapter5Area4Vars_800B6E84[5];
extern int *chapter5AreaVars_800B6E98[6];
extern short chapter5MapVars_800B6EB0[116];
extern int *chapter6AreaVars_800B6F98[6];
extern short chapter6MapVars_800B6FB0[24];
extern ChapterEntry chapterTable_800B6FE0[7];
extern int chapterClearYanVars_800B70A4[4];

// a map var key / map point: (area, map, sub)
typedef struct ChapterMapKey
{
    short area;
    short map;
    short sub;
} ChapterMapKey;
typedef struct ChapterTask
{
    int flags_0;
    int f4_4;
    void (*next_8)();
} ChapterTask;

extern void SetAreaMapVars_800B69BC(int**);
extern void SetMapVarList_800B6A94(short*);
extern void ClearChapterYanVars_800B68A8();
extern void ApplyChapterMapVars_800B6900();
extern void EnterChapterMap_800B6B18();
void ChapterIntroTask_800B66F4(ChapterTask* task, int* st);

/* GAME overlay (resident below this one), to move to game.h */
extern int dword_800B0624[6];
extern void SetEventVar_800AD16C(int, int);
extern void SetMapVar_800ADC5C(ChapterMapKey*, int);
extern void FindMapEntrance_800ADCEC(ChapterMapKey*, int);
extern void RequestGameMode_800A6D30(int);
extern void StartChapterOverlay_800A7690();

/* exe-side, to move to an exe header */
extern int PlayMusic_800300E0(int idx, int a1);
extern void SsSepSetDecrescendo(short, short, short, long);

#endif
