// PIERCE.BIN: declarations shared by its source files
#ifndef _PIERCE_H_
#define _PIERCE_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"

extern int dword_800C6F40;

typedef struct PierceTask
{
    int pad_0[2];
    void (*next_8)();
} PierceTask;
typedef struct PierceMsg
{
    int a_0;
    int b_4;
    int c_8;
    int d_C;
    int e_10;
    int f_14;
    int pad_18[4];
} PierceMsg;
typedef struct PierceCam
{
    char pad_0[0x31C];
    short x_31C;
    short pad_31E;
    short y_320;
    short pad_322;
    short z_324;
    short pad_326;
    short f_328;
} PierceCam;


/* PIERCE was linked against an older executable/GAME build: these addresses land inside other functions of the
   current ones (see pierce.c), so they stay here under their raw names */
extern void fn_800AD070();

extern void fn_800B7C04();
extern void fn_800B7DD8();
extern void IsUnitOnField_800BC570(int a, int b);
extern int fn_800BC484();
extern int fn_800B7C74();
extern int fn_800B7C9C();
extern void fn_800B76AC(PierceMsg* m);
extern void fn_80027724(int a);
extern int fn_800277E8();
extern void fn_800BC604(int a);
extern void aNeedTwoJp2_800B7C30();
extern void fn_800BD348(int a, int b);
extern void fn_800BD734(short* v, int b);
extern void fn_80028E04();
extern void fn_800B60FC();
extern PierceCam cam_80092F30;
extern int dword_8009DCAC;
extern int dword_8009DC7C;
extern int dword_80092F00;
extern int dword_800C124C;

#endif
