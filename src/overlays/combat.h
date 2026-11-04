// COMBAT.BIN: declarations shared by its source files
#ifndef _COMBAT_H_
#define _COMBAT_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "actor.h"
#include "engine.h"
#include "minion_init.h"
#include "main.h"
#include "unit_stats.h"

typedef struct CombatModelParams
{
    int count_0;        // number of different parts
    int parts_4[3];
    int weights_10[3];
    int modelId_1C;
    int f20;
    int angle_24;
    int f28;
    int f2C;
    int f30;
} CombatModelParams;

typedef struct CombatSlotCombat
{
    int task_0;         // StartModelTask_80010850 id, -1 = free
    Minion* minion_4;
    CombatModelParams params_8;
    Actor* actor_3C;
} CombatSlotCombat;

extern int dword_800A05A0;
extern short dword_800A1BBC[4];
extern short word_800A1BC4;
extern Minion dword_800A1BC8[2][15];
extern unsigned char byte_800A38D8;
extern unsigned char byte_800A38D9;
extern unsigned char byte_800A38DA;
extern unsigned char byte_800A38DB;
extern unsigned char byte_800A38DC;
extern int dword_800A38E0;
extern int dword_800A38E4[6];
extern int dword_800A38FC[6];
extern int dword_800A3914[6];
extern int dword_800A392C[6];
extern int dword_800A3944[6];
extern int dword_800A395C[6];
extern int dword_800A3974[6];
extern void *dword_800A398C[25];
extern int dword_800A39F0[6];
extern CombatSlotCombat dword_800A3A08[2];
extern int dword_800A3A88;
extern int dword_800A3A8C;
extern int dword_800A3A90[4];
extern Minion dword_800A3AA0[2][3];
extern int dword_800A4070;
extern int dword_800A4074[3];
extern int dword_800A4080;

#endif
