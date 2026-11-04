// SHOPENTR.BIN: declarations shared by its source files
#ifndef _SHOPENTR_H_
#define _SHOPENTR_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"

typedef struct
{
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
} RectShopentr;

typedef struct
{
    short next_0;
    short next_2;
    short rect_4;
    short pad_6;
    int pad_8;
    int pad_C;
    int field_10;
} EntryShopentr;

extern int dword_800B6D00;
extern const char asc_800B6D04[];
extern const char asc_800B6D14[];
extern const char asc_800B6D24[];
extern const char asc_800B6D30[];
extern const char asc_800B6D48[];
extern const char asc_800B6D5C[];
extern const char asc_800B6D6C[];
extern const char asc_800B6D84[];
extern const char asc_800B6DA0[];
extern const char asc_800B6DB4[];
extern const char asc_800B6DCC[];
extern const char asc_800B6DEC[];
extern const char asc_800B6E10[];
extern const char asc_800B6E24[];
extern const char asc_800B6E34[];
extern const int dword_800B6E48;
extern const char str_800B6E74[];
extern const char str_800B6E90[];
extern const char str_800B6EA4[];
extern const char str_800B6EB0[];
extern const char str_800B6EBC[];
extern const char str_800B6EC8[];
extern const char str_800B6ED0[];
extern const char str_800B6EDC[];
extern const char str_800B6EE4[];
extern const char str_800B6EEC[];
extern const char str_800B6EF4[];
extern const char str_800B6EFC[];
extern const char str_800B6F04[];
extern const char str_800B6F08[];
extern int sub_800B6F0C(void);
extern int dword_800B7CC0[2];
extern unsigned short word_800B7CC8[2];
extern int dword_800B7CCC;
extern unsigned short word_800B7CD0[2];
extern int dword_800B7CD4;
extern unsigned short word_800B7CD8[2];
extern int dword_800B7CDC;
extern unsigned short word_800B7CE0[2];
extern int dword_800B7CE4;
extern RectShopentr rects_800B7CE8[4];
extern EntryShopentr entries_800B7D08[15];
extern unsigned int masks_800B7E34[30];
extern int dword_800B7EAC;

#endif
