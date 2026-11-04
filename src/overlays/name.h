// NAME.BIN: declarations shared by its source files
#ifndef _NAME_H_
#define _NAME_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct
{
    short s0;
    short s2;
    short s4;
    short s6;
    short s8;
    short sA;
    short sC;
    short sE;
    short s10;
    short s12;
} NameGrid;

typedef struct
{
    DVECTOR pos;
    char* chars_4;
} NameCharRow;

typedef struct
{
    int f0;
    int f4;
    int f8;
    int fC;
} NameSprite;

typedef struct NameBuf
{
    short s[11];
} NameBuf;

typedef struct
{
    int mask;
    int result;
} NameCursorTbl;

extern int dword_800B6D00;
extern const char asc_800B6D04[28];
extern const char asc_800B6D20[28];
extern const char asc_800B6D3C[28];
extern const char aYz_800B6D58[28];
extern const char aMnopqrstuvwx_800B6D74[28];
extern const char aAbcdefghijkl_800B6D90[28];
extern const char aYZ_800B6DAC[28];
extern const char aMNOPQRSTUVWX_800B6DC8[28];
extern const char aABCDEFGHIJKL_800B6DE4[28];
extern const char aABC_800B6E00[];
extern const char a123_800B6E08[];
extern const char aCancel_800B6E10[];
extern const char aSelect_800B6E20[];
extern const NameBuf name_800B6E30;
extern const char name_800B6E48[];
extern NameCharRow dword_800B8190[2][7];
extern NameGrid name_800B8200[3];
extern int dword_800B823C[14];
extern int dword_800B8274[14];
extern int dword_800B82AC[14];
extern void *dword_800B82E4[4];
extern NameSprite name_800B82F4;
extern void *dword_800B8304[2];
extern int dword_800B830C[14];
extern int dword_800B8344[14];
extern void *dword_800B837C[3];
extern NameSprite name_800B8388;
extern void *dword_800B8398[2];
extern char name_800B83A0[24];
extern char defaultName_800B83B8[0x14];
extern int dword_800B83CC;
extern short name_800B83D0[4];
extern NameCursorTbl name_800B83D8[4];
extern int nameEntryActive_800B83F8;

#endif
