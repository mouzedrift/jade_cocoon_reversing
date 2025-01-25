#ifndef GLOBALS_H
#define GLOBALS_H

#define _SIZE_T

#include "SYS/TYPES.H"
#include "LIBDS.H"
#include "enums.h"

typedef struct
{
    int field_0;
    int field_4;
    short field_8_x;
    short field_A_y;
} struct_44;

typedef struct
{
    int field_0;
    int field_4;
} struct_46;

extern int dword_800918B0;
extern int dword_80096090[4];
extern enum GameStates currentGameState_8008D4B4;
extern volatile int unknownFlags_8008D678;
extern short word_8008B558[2];
extern DslFILE Data001File_800954A8;
extern int DsReadSyncResult_8008D630;
extern int dword_8008B55C;
extern dword_800918BC;
extern struct_44 stru_8008B4D8;
extern long cdRomEventDescError_8008B490;
extern long vsyncEventDesc_8008B494;
extern int dword_8008B574;
extern volatile int dword_8008B4B4;
extern volatile int gnFrame_8008D610;
extern volatile int dword_8008D450;
extern volatile int dword_8008D404;
extern struct_46 dword_8008B570; // might be part of a bigger save game struct
extern unsigned int allMinionsBitfields_8008BD84[7];

#endif
