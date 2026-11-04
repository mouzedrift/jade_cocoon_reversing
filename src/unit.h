#ifndef UNIT_H
#define UNIT_H

/* 0x48-byte status block of Levant (levantStatus_8008BD38 == saveData+0x7C8) and of each minion
   (Minion.status_84, GetMinionStatus_800107A0); also the head of UnitStats.
   Heal_80011CD0 refills hp/mp (Meos4's randomizer calls 0x80011CD0 "healFn"). */
typedef struct UnitStatus
{
    int status_0;          // status effect bits (0x400 survives ClearStatus_80011C30)
    unsigned int exp_4;           // low 26 bits; level_44 holds the high part
    short hp_8;
    short maxHp_A;
    short mp_C;
    short maxMp_E;
    unsigned char name_10[0xC]; // charTables_8008685C encoding, see DecodeNames_8003FBD4
    unsigned char field_1C[4];  // equipped weapon/armor/accessory ids (GetEquipmentId_8003356C)
    unsigned char field_20[0xC]; // ApplyEquipmentModifiers_80033754
    unsigned char stats_2C[6]; // attack, defense, magic attack, magic defense, speed, critical (sub_8001980C)
    unsigned char base_32[6];  // the species' base stats; pick the growth kind (sub_80011D98)
    unsigned char frac_38[6];  // fractional growth (0..99)
    unsigned char element_3E[4];
    short elementMask_42;
    unsigned char level_44;
    unsigned char field_45;
    char pad_46[2];
} UnitStatus;

/* one ability slot (sub_80031954, sub_80031A04, sub_8002CE28) */
typedef struct UnitSkill
{
    unsigned char flags_0; // bit 0: learned
    unsigned char id_1;    // abilityNames_800834E4 / sub_800318C8 index; 2..6 cost MP (sub_80031A04)
    unsigned char bonus_2; // abilityBonusNames_80083580 index
    unsigned char field_3;
} UnitSkill;

/* a unit's five ability slots; species defaults come from sub_80019C28 (copied by sub_800199A0) */
typedef struct
{
    UnitSkill slot[5];
} UnitSkills;

/* the 0x88-byte record of a new minion / an encounter's minion (InitMinionData_8001900C, GameCtx_1.ents_ac);
   sub_800B9E94 packs it into a Minion */
typedef struct
{
    UnitStatus st_0;
    char pad_48[0x14];
    unsigned int species_5C;
    unsigned char name_60[0xC];
    UnitSkills skills_6C;
    unsigned int magicBits_80; // TestMagicBit_8001AE2C
    int field_84;
} UnitStats;

/* a minion as kept in SaveData.minions (0xF8 bytes, filled by sub_800B9E94 from a UnitStats) */
typedef struct
{
    short id; // 2/3 = owned, 4 = empty slot
    unsigned char species_2;
    unsigned char field_3;
    unsigned char ancestors_4[6][0xC]; // names (sub_80010724, sub_80033830)
    unsigned char species_4C[0x30];    // species history (sub_800338B0)
    unsigned char field_7C[6];         // element masks of the ancestors (sub_80010768, sub_80033848)
    char pad_82[2];
    UnitStatus status_84;
    unsigned char field_CC[0x12];
    UnitSkills skills_DE;
    char pad_F2[2];
    unsigned int magicBits_F4; // CountMagicBits_8001AE54
} Minion;

/* 12-byte parameter block of an action: the basic attack (sub_8001D260), a magic (sub_8001AD64), an item
   (GetItemData_8001CDF4) or an ability (sub_800318C8); sub_80012BB0 / sub_800129B0 work on a copy */
typedef struct ActionData
{
    unsigned char c0;
    unsigned char c1;
    short s2;
    unsigned char c4;
    unsigned char c5;
    unsigned char c6;
    unsigned char c7;
    unsigned char c8; // sub_80013228 tests it for 8
    char pad_9[3];
} ActionData;

extern UnitStatus levantStatus_8008BD38; // == saveData_8008B570.levantStatus_7C8

#endif

