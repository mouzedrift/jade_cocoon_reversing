// CHAPTER.BIN: declarations shared by its source files
#ifndef _CHAPTER_H_
#define _CHAPTER_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"

typedef struct ChapterEntry
{
    short field_0;
    short pad_2;
    int field_4;
    int music_8;
    int fadeBgm_C;
    int movie_10;
    int **field_14;     // per minion list (6): the minions the chapter adds
    short *field_18;    // (x, y, z, id) records up to id -1
} ChapterEntry;

extern int dword_800B66C0;
extern int dword_800B6BC4[12];
extern int *dword_800B6BF4[6];
extern short dword_800B6C0C[8];
extern int dword_800B6C1C[12];
extern int dword_800B6C4C[5];
extern int *dword_800B6C60[6];
extern short dword_800B6C78[20];
extern int dword_800B6CA0[12];
extern int dword_800B6CD0[5];
extern int *dword_800B6CE4[6];
extern short dword_800B6CFC[28];
extern int dword_800B6D34[12];
extern int dword_800B6D64[5];
extern int *dword_800B6D78[6];
extern short dword_800B6D90[20];
extern int dword_800B6DB8[12];
extern int dword_800B6DE8[5];
extern int *dword_800B6DFC[6];
extern short dword_800B6E14[32];
extern int dword_800B6E54[12];
extern int dword_800B6E84[5];
extern int *dword_800B6E98[6];
extern short dword_800B6EB0[116];
extern int *dword_800B6F98[6];
extern short dword_800B6FB0[24];
extern ChapterEntry chapterTable_800B6FE0[7];
extern int dword_800B70A4[4];

#endif
