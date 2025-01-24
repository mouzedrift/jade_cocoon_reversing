#ifndef GLOBALS_H
#define GLOBALS_H

#include "LIBDS.H"
#include "LIBGPU.H"
#include "enums.h"

typedef struct
{
    int field_0;
    int field_4;
    short field_8_x;
    short field_A_y;
} struct_44;

extern int dword_8008BD84[93];
extern int dword_800918B0;
extern int dword_80096090[4];
extern enum GameStates currentGameState_8008D4B4;
extern volatile int unknownFlags_8008D678;
extern short word_8008B558[2];
extern DslFILE Data001File_800954A8;
extern int DsReadSyncResult_8008D630;
extern int dword_8008B55C;
extern dword_800918BC;
extern DRAWENV drawEnv_8008B4E0;
extern struct_44 stru_8008B4D8;

#endif
