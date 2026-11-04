// CHAPTER.BIN: declarations shared by its source files
#ifndef _CHAPTER_H_
#define _CHAPTER_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"

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

#endif
