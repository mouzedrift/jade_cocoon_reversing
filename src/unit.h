#ifndef UNIT_H
#define UNIT_H

/* the stats record of Levant / a minion (InitMinionData_8001900C, sub_80014390).
   Starts with the EntityStatus block; the offsets match the first 0x84 bytes of Minion (globals.h). */

/* 20 bytes copied from sub_80019C28 by sub_800199A0 */
typedef struct
{
    unsigned char e[4][4];
    unsigned char field_10[4];
} UnitSkills;

typedef struct
{
    int status_0;          // EntityStatus.status_0
    int exp_4;             // low 26 bits
    unsigned short hp_8;
    unsigned short maxHp_A;
    unsigned short mp_C;
    unsigned short maxMp_E;
    unsigned char name_10[0xC];
    unsigned char field_1C[4];
    unsigned char field_20[0xC];
    unsigned char stats_2C[0x12]; // sub_8001980C
    unsigned char element_3E[4];
    short elementMask_42;
    unsigned char level_44;
    unsigned char field_45;
    char pad_46[0x16];
    unsigned int species_5C;
    unsigned char name_60[0xC];
    UnitSkills skills_6C;
    int field_80;
} UnitStats;

#endif
