// GAME.BIN, source file 3 of 3 from 0x800A5804 (.rdata from 0x800A0660)
#include "game.h"

const char aAssertionFaile_800A0660[] = "Assertion failed: file \"%s\", line %d\n";
const char aEventcomC_800A0688[] = "EVENTCOM.C";
const int dword_800A0694 = 0;

GameBattleChain encounterRecord_800ADE78 = { 0 };
short formation1_800ADE8C[2] = { 0 };
short formation2_800ADE90[2] = { -0x11C, 0x11C };
short formation3_800ADE94[4] = { -0x200, 0, 0x200 };
short *encounterFormations_800ADE9C[7] = { formation1_800ADE8C, formation2_800ADE90, formation3_800ADE94, (short *)0x61A80, (short *)0xDBBA0, (short *)0x155CC0, (short *)0x1CFDE0 };
void (*enemyAiBySpecies_800ADEB8[53][2])() = {
    { EnemyAiSleepChase_800A333C, EnemyAiHideFlee_800A3E88 },
    { EnemyAiSleepChase_800A333C, EnemyAiHideFlee_800A3E88 },
    { EnemyAiSleepChase_800A333C, EnemyAiHideFlee_800A3E88 },
    { EnemyAiAlertChase_800A3804, EnemyAiHideFlee_800A3E88 },
    { EnemyAiAlertChase_800A3804, EnemyAiHideFlee_800A3E88 },
    { EnemyAiAlertChase_800A3804, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWatchFlee_800A31DC, EnemyAiWatchFlee_800A31DC },
    { EnemyAiWanderMid_800A3FC0, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderMid_800A3FC0, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWander_800A34D8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderBump_800A3A8C, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiChaseAlert_800A3954, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiChaseBehind_800A3BEC, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWander_800A34D8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWander2_800A366C, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderShort_800A3D24, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiFlee_800A2EEC, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
    { EnemyAiWanderChase_800A2FB8, EnemyAiHideFlee_800A3E88 },
};
short battleStage00Maps_800AE060[8] = { 106, 107, 109, 111, 112, 114, -1 };
short battleStage01Maps_800AE070[10] = {
    118, 119, 120, 121, 122, 124, 132, 133,
    -1,
};
short battleStage02Maps_800AE084[4] = { 125, 126, -1 };
short battleStage03Maps_800AE08C[4] = { 123, 128, 131, -1 };
short battleStage04Maps_800AE094[2] = { 129, -1 };
short battleStage05Maps_800AE098[2] = { 110, -1 };
short battleStage06Maps_800AE09C[2] = { 108, -1 };
short battleStage07Maps_800AE0A0[14] = {
    143, 144, 145, 146, 147, 148, 149, 151,
    153, 155, 157, 160, 162, -1,
};
short battleStage08Maps_800AE0BC[8] = { 137, 138, 139, 140, 141, 142, -1 };
short battleStage09Maps_800AE0CC[4] = { 158, 159, -1 };
short battleStage10Maps_800AE0D4[2] = { 161, -1 };
short battleStage11Maps_800AE0D8[14] = {
    168, 169, 170, 171, 172, 173, 174, 175,
    176, 177, 178, 181, 183, -1,
};
short battleStage12Maps_800AE0F4[6] = { 163, 164, 165, 166, 167, -1 };
short battleStage13Maps_800AE100[4] = { 179, 180, -1 };
short battleStage14Maps_800AE108[2] = { 182, -1 };
short battleStage15Maps_800AE10C[2] = { 217, -1 };
short battleStage16Maps_800AE110[2] = { 228, -1 };
short battleStage17Maps_800AE114[2] = { 0x104, -1 };
short battleStage18Maps_800AE118[2] = { 0x105, -1 };
short battleStage19Maps_800AE11C[2] = { 0x107, -1 };
short battleStage20Maps_800AE120[6] = { 186, 187, 188, 189, 190, -1 };
short battleStage21Maps_800AE12C[4] = { 195, 196, -1 };
short battleStage22Maps_800AE134[6] = { 191, 192, 193, 194, -1 };
short battleStage23Maps_800AE140[8] = { 210, 211, 213, 215, 216, 217, -1 };
short battleStage24Maps_800AE150[8] = { 221, 222, 223, 224, 225, 227, 234, -1 };
short battleStage25Maps_800AE160[2] = { 228, -1 };
short battleStage26Maps_800AE164[4] = { 226, 230, 233, -1 };
short battleStage27Maps_800AE16C[2] = { 231, -1 };
short battleStage28Maps_800AE170[2] = { 214, -1 };
short battleStage29Maps_800AE174[2] = { 212, -1 };
short battleStage30Maps_800AE178[18] = {
    242, 243, 244, 245, 246, 247, 248, 249,
    250, 251, 252, 253, 254, 255, 0x102, 0x104,
    -1,
};
short battleStage31Maps_800AE19C[6] = { 237, 238, 239, 240, 241, -1 };
short battleStage32Maps_800AE1A8[4] = { 0x100, 0x101, -1 };
short battleStage33Maps_800AE1B0[2] = { 0x103, -1 };
short battleStage34Maps_800AE1B4[16] = {
    0x117, 0x118, 0x119, 0x11A, 0x11B, 0x11C, 0x11D, 0x11E,
    0x11F, 0x120, 0x121, 0x122, 0x123, 0x124, 0x125, -1,
};
short battleStage35Maps_800AE1D4[16] = {
    0x126, 0x127, 0x128, 0x129, 0x12A, 0x12B, 0x12C, 0x12D,
    0x12E, 0x12F, 0x130, 0x131, 0x132, 0x133, 0x134, -1,
};
short battleStage36Maps_800AE1F4[16] = {
    0x135, 0x136, 0x137, 0x138, 0x139, 0x13A, 0x13B, 0x13C,
    0x13D, 0x13E, 0x13F, 0x140, 0x141, 0x142, 0x143, -1,
};
short battleStage37Maps_800AE214[16] = {
    0x144, 0x145, 0x146, 0x147, 0x148, 0x149, 0x14A, 0x14B,
    0x14C, 0x14D, 0x14E, 0x14F, 0x150, 0x151, 0x152, -1,
};
short battleStage38Maps_800AE234[16] = {
    0x108, 0x109, 0x10A, 0x10B, 0x10C, 0x10D, 0x10E, 0x10F,
    0x110, 0x111, 0x112, 0x113, 0x114, 0x115, 0x116, -1,
};
short *battleStageMaps_800AE254[39] = {
    battleStage00Maps_800AE060, battleStage01Maps_800AE070, battleStage02Maps_800AE084, battleStage03Maps_800AE08C,
    battleStage04Maps_800AE094, battleStage05Maps_800AE098, battleStage06Maps_800AE09C, battleStage07Maps_800AE0A0,
    battleStage08Maps_800AE0BC, battleStage09Maps_800AE0CC, battleStage10Maps_800AE0D4, battleStage11Maps_800AE0D8,
    battleStage12Maps_800AE0F4, battleStage13Maps_800AE100, battleStage14Maps_800AE108, battleStage15Maps_800AE10C,
    battleStage16Maps_800AE110, battleStage17Maps_800AE114, battleStage18Maps_800AE118, battleStage19Maps_800AE11C,
    battleStage20Maps_800AE120, battleStage21Maps_800AE12C, battleStage22Maps_800AE134, battleStage23Maps_800AE140,
    battleStage24Maps_800AE150, battleStage25Maps_800AE160, battleStage26Maps_800AE164, battleStage27Maps_800AE16C,
    battleStage28Maps_800AE170, battleStage29Maps_800AE174, battleStage30Maps_800AE178, battleStage31Maps_800AE19C,
    battleStage32Maps_800AE1A8, battleStage33Maps_800AE1B0, battleStage34Maps_800AE1B4, battleStage35Maps_800AE1D4,
    battleStage36Maps_800AE1F4, battleStage37Maps_800AE214, battleStage38Maps_800AE234,
};
short encounterArea00Maps_800AE2F0[6] = { 106, 107, 108, 109, 112, -1 };
short encounterArea01Maps_800AE2FC[4] = { 110, 111, 114, -1 };
short encounterArea02Maps_800AE304[2] = { -1 };
short encounterArea03Maps_800AE308[8] = { 118, 119, 120, 121, 122, 124, 132, -1 };
short encounterArea04Maps_800AE318[6] = { 123, 128, 129, 131, -1 };
short encounterArea05Maps_800AE324[6] = { 137, 138, 139, 143, 144, -1 };
short encounterArea06Maps_800AE330[6] = { 140, 142, 145, 146, 147, -1 };
short encounterArea07Maps_800AE33C[6] = { 158, 159, 160, 161, -1 };
short encounterArea08Maps_800AE348[16] = {
    163, 164, 165, 166, 167, 168, 169, 170,
    171, 172, 179, 180, 181, 182, -1,
};
short encounterArea09Maps_800AE368[10] = {
    186, 187, 188, 189, 191, 192, 193, 194,
    195, -1,
};
short encounterArea10Maps_800AE37C[4] = { 210, 211, 212, -1 };
short encounterArea11Maps_800AE384[6] = { 213, 214, 215, 216, 217, -1 };
short encounterArea12Maps_800AE390[8] = { 221, 222, 223, 224, 225, 227, 234, -1 };
short encounterArea13Maps_800AE3A0[6] = { 226, 230, 231, 233, -1 };
short encounterArea14Maps_800AE3AC[6] = { 237, 238, 239, 242, 243, -1 };
short encounterArea15Maps_800AE3B8[6] = { 240, 241, 244, 245, 246, -1 };
short encounterArea16Maps_800AE3C4[6] = { 0x100, 0x101, 0x102, 0x103, -1 };
short *encounterAreaMaps_800AE3D0[17] = {
    encounterArea00Maps_800AE2F0, encounterArea01Maps_800AE2FC, encounterArea02Maps_800AE304, encounterArea03Maps_800AE308,
    encounterArea04Maps_800AE318, encounterArea05Maps_800AE324, encounterArea06Maps_800AE330, encounterArea07Maps_800AE33C,
    encounterArea08Maps_800AE348, encounterArea09Maps_800AE368, encounterArea10Maps_800AE37C, encounterArea11Maps_800AE384,
    encounterArea12Maps_800AE390, encounterArea13Maps_800AE3A0, encounterArea14Maps_800AE3AC, encounterArea15Maps_800AE3B8,
    encounterArea16Maps_800AE3C4,
};
int encounterArea00Species_800AE414[3] = { 15, 12, 6 };
int encounterArea01Species_800AE420[3] = { 18, 0, 6 };
int encounterArea02Species_800AE42C[3] = { 12, 15, 6 };
int encounterArea03Species_800AE438[3] = { 0, 9, 27 };
int encounterArea04Species_800AE444[3] = { 27, 10, 26 };
int encounterArea05Species_800AE450[3] = { 3, 14, 17 };
int encounterArea06Species_800AE45C[3] = { 17, 7, 14 };
int encounterArea07Species_800AE468[3] = { 19, 23, 17 };
int encounterArea08Species_800AE474[3] = { 30, 30, 30 };
int encounterArea09Species_800AE480[3] = { 1, 21, 16 };
int encounterArea10Species_800AE48C[3] = { 13, 2, 28 };
int encounterArea11Species_800AE498[3] = { 13, 2, 28 };
int encounterArea12Species_800AE4A4[3] = { 11, 4, 24 };
int encounterArea13Species_800AE4B0[3] = { 24, 22, 4 };
int encounterArea14Species_800AE4BC[3] = { 5, 29, 31 };
int encounterArea15Species_800AE4C8[3] = { 25, 8, 20 };
int encounterArea16Species_800AE4D4[3] = { 31, 5, 8 };
int *encounterAreaSpecies_800AE4E0[17] = {
    encounterArea00Species_800AE414, encounterArea01Species_800AE420, encounterArea02Species_800AE42C, encounterArea03Species_800AE438,
    encounterArea04Species_800AE444, encounterArea05Species_800AE450, encounterArea06Species_800AE45C, encounterArea07Species_800AE468,
    encounterArea08Species_800AE474, encounterArea09Species_800AE480, encounterArea10Species_800AE48C, encounterArea11Species_800AE498,
    encounterArea12Species_800AE4A4, encounterArea13Species_800AE4B0, encounterArea14Species_800AE4BC, encounterArea15Species_800AE4C8,
    encounterArea16Species_800AE4D4,
};
GameSpawnEntry encounterTables_800AE524[73][3] = {
    { { 16, 1, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 0, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 2, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 1, 0, 3, 0, 3, 0 }, { 8, 0, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 2, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 0, 0, 0, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 0, 0, 2, 0, 3, 0 }, { 8, 1, 0, 2, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 1, 2, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 0, 2, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 0, 2, 3, 0, 3, 0 }, { 8, 1, 3, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 0, 2, 3, 0, 3, 0 }, { 8, 1, 3, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 0, 2, 3, 0, 3, 0 }, { 8, 0, 2, 1, 3, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 1, 3, 1, 3, 3, 0 }, { 8, 0, 2, 3, 3, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 0, 3, 0, 3, 3, 0 }, { 8, 0, 3, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 0, 2, 0, 2, 3, 0 }, { 8, 1, 3, 1, 3, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 1, 4, 1, 4, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 2, 4, 2, 4, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 0, 3, 0, 3, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 0, 2, 0, 2, 0, 2 }, { 8, 1, 3, 1, 3, 1, 3 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 0, 6, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 10, 1, 6, 3, 0, 3, 0 }, { 6, 0, 6, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 14, 2, 6, 3, 0, 3, 0 }, { 2, 2, 6, 0, 6, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 0, 6, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 14, 0, 6, 3, 0, 3, 0 }, { 2, 0, 6, 1, 6, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 0, 6, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 1, 6, 0, 6, 3, 0 }, { 8, 1, 6, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 14, 0, 6, 3, 0, 3, 0 }, { 2, 0, 6, 1, 6, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 1, 6, 1, 6, 3, 0 }, { 8, 2, 6, 1, 6, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 2, 6, 1, 6, 0, 6 }, { 8, 2, 6, 1, 6, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 0, 7, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 0, 7, 2, 7, 3, 0 }, { 8, 0, 7, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 0, 7, 2, 7, 3, 0 }, { 8, 0, 7, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 1, 7, 1, 7, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 0, 8, 0, 8, 3, 0 }, { 8, 0, 8, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 2, 9, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 1, 9, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 0, 9, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 0, 9, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 10, 2, 9, 3, 0, 3, 0 }, { 6, 1, 9, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 0, 9, 2, 9, 3, 0 }, { 8, 2, 9, 0, 9, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 7, 0, 9, 3, 0, 3, 0 }, { 7, 1, 9, 3, 0, 3, 0 }, { 2, 1, 9, 0, 9, 3, 0 } },
    { { 7, 2, 9, 3, 0, 3, 0 }, { 7, 1, 9, 3, 0, 3, 0 }, { 2, 2, 9, 1, 9, 0, 9 } },
    { { 8, 0, 9, 3, 0, 3, 0 }, { 8, 2, 9, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 2, 10, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 1, 11, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 0, 11, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 2, 10, 3, 0, 3, 0 }, { 8, 1, 11, 1, 11, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 0, 11, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 2, 10, 3, 0, 3, 0 }, { 8, 2, 10, 2, 10, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 0, 11, 3, 0, 3, 0 }, { 8, 1, 11, 0, 11, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 6, 0, 11, 0, 0, 3, 0 }, { 5, 2, 10, 3, 0, 3, 0 }, { 5, 1, 11, 2, 10, 3, 0 } },
    { { 16, 0, 12, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 0, 12, 3, 0, 3, 0 }, { 8, 1, 13, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 0, 12, 3, 0, 3, 0 }, { 8, 1, 13, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 1, 13, 3, 0, 3, 0 }, { 8, 1, 13, 1, 13, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 2, 14, 3, 0, 3, 0 }, { 8, 1, 13, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 0, 14, 0, 14, 3, 0 }, { 8, 0, 14, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 8, 0, 12, 1, 13, 3, 0 }, { 8, 2, 14, 1, 13, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 0, 14, 0, 14, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 1, 14, 2, 14, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 0, 14, 0, 14, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 0, 12, 1, 13, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 0, 15, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 1, 16, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 2, 17, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 0, 17, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 0, 17, 0, 17, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 1, 16, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 1, 16, 0, 15, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 2, 17, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 2, 17, 1, 17, 3, 0 }, { 0, 1, 17, 2, 17, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 16, 0, 17, 0, 17, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 }, { 0, 3, 0, 3, 0, 3, 0 } },
    { { 1, 2, 17, 1, 15, 0, 17 }, { 7, 1, 15, 2, 17, 3, 0 }, { 8, 0, 17, 1, 15, 3, 0 } },
};
short encounterTable00Maps_800AE890[2] = { 106, -1 };
short encounterTable01Maps_800AE894[2] = { 107, -1 };
short encounterTable02Maps_800AE898[2] = { 108, -1 };
short encounterTable03Maps_800AE89C[2] = { 109, -1 };
short encounterTable04Maps_800AE8A0[2] = { 110, -1 };
short encounterTable05Maps_800AE8A4[2] = { 111, -1 };
short encounterTable06Maps_800AE8A8[2] = { 112, -1 };
short encounterTable07Maps_800AE8AC[2] = { 114, -1 };
short encounterTable08Maps_800AE8B0[2] = { 118, -1 };
short encounterTable09Maps_800AE8B4[2] = { 119, -1 };
short encounterTable10Maps_800AE8B8[2] = { 120, -1 };
short encounterTable11Maps_800AE8BC[2] = { 121, -1 };
short encounterTable12Maps_800AE8C0[2] = { 122, -1 };
short encounterTable13Maps_800AE8C4[2] = { 123, -1 };
short encounterTable14Maps_800AE8C8[2] = { 124, -1 };
short encounterTable15Maps_800AE8CC[2] = { 128, -1 };
short encounterTable16Maps_800AE8D0[2] = { 129, -1 };
short encounterTable17Maps_800AE8D4[2] = { 131, -1 };
short encounterTable18Maps_800AE8D8[2] = { 132, -1 };
short encounterTable19Maps_800AE8DC[2] = { 137, -1 };
short encounterTable20Maps_800AE8E0[2] = { 138, -1 };
short encounterTable21Maps_800AE8E4[2] = { 139, -1 };
short encounterTable22Maps_800AE8E8[2] = { 140, -1 };
short encounterTable23Maps_800AE8EC[2] = { 142, -1 };
short encounterTable24Maps_800AE8F0[2] = { 143, -1 };
short encounterTable25Maps_800AE8F4[2] = { 144, -1 };
short encounterTable26Maps_800AE8F8[2] = { 145, -1 };
short encounterTable27Maps_800AE8FC[2] = { 146, -1 };
short encounterTable28Maps_800AE900[2] = { 147, -1 };
short encounterTable29Maps_800AE904[2] = { 158, -1 };
short encounterTable30Maps_800AE908[2] = { 159, -1 };
short encounterTable31Maps_800AE90C[2] = { 160, -1 };
short encounterTable32Maps_800AE910[2] = { 161, -1 };
short encounterTable33Maps_800AE914[16] = { 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 179, 180, 181, 182, -1, 0 };
short encounterTable34Maps_800AE934[2] = { 187, -1 };
short encounterTable35Maps_800AE938[4] = { 188, 186, -1, 0 };
short encounterTable36Maps_800AE940[2] = { 189, -1 };
short encounterTable37Maps_800AE944[2] = { -1, 0 };
short encounterTable38Maps_800AE948[2] = { 191, -1 };
short encounterTable39Maps_800AE94C[2] = { 192, -1 };
short encounterTable40Maps_800AE950[2] = { 193, -1 };
short encounterTable41Maps_800AE954[2] = { 194, -1 };
short encounterTable42Maps_800AE958[2] = { 195, -1 };
short encounterTable43Maps_800AE95C[2] = { 210, -1 };
short encounterTable44Maps_800AE960[2] = { 211, -1 };
short encounterTable45Maps_800AE964[2] = { 212, -1 };
short encounterTable46Maps_800AE968[2] = { 213, -1 };
short encounterTable47Maps_800AE96C[2] = { 214, -1 };
short encounterTable48Maps_800AE970[2] = { 215, -1 };
short encounterTable49Maps_800AE974[2] = { 216, -1 };
short encounterTable50Maps_800AE978[2] = { 217, -1 };
short encounterTable51Maps_800AE97C[2] = { 221, -1 };
short encounterTable52Maps_800AE980[2] = { 222, -1 };
short encounterTable53Maps_800AE984[2] = { 223, -1 };
short encounterTable54Maps_800AE988[2] = { 224, -1 };
short encounterTable55Maps_800AE98C[2] = { 225, -1 };
short encounterTable56Maps_800AE990[2] = { 226, -1 };
short encounterTable57Maps_800AE994[2] = { 227, -1 };
short encounterTable58Maps_800AE998[2] = { 228, -1 };
short encounterTable59Maps_800AE99C[2] = { 231, -1 };
short encounterTable60Maps_800AE9A0[2] = { 233, -1 };
short encounterTable61Maps_800AE9A4[2] = { 234, -1 };
short encounterTable62Maps_800AE9A8[2] = { 237, -1 };
short encounterTable63Maps_800AE9AC[2] = { 238, -1 };
short encounterTable64Maps_800AE9B0[2] = { 239, -1 };
short encounterTable65Maps_800AE9B4[2] = { 240, -1 };
short encounterTable66Maps_800AE9B8[2] = { 241, -1 };
short encounterTable67Maps_800AE9BC[2] = { 242, -1 };
short encounterTable68Maps_800AE9C0[2] = { 243, -1 };
short encounterTable69Maps_800AE9C4[2] = { 244, -1 };
short encounterTable70Maps_800AE9C8[2] = { 245, -1 };
short encounterTable71Maps_800AE9CC[2] = { 246, -1 };
short encounterTable72Maps_800AE9D0[5] = { 256, 257, 258, 259, -1 };
short *encounterMapLists_800AE9DC[73] = {
    encounterTable00Maps_800AE890, encounterTable01Maps_800AE894, encounterTable02Maps_800AE898, encounterTable03Maps_800AE89C,
    encounterTable04Maps_800AE8A0, encounterTable05Maps_800AE8A4, encounterTable06Maps_800AE8A8, encounterTable07Maps_800AE8AC,
    encounterTable08Maps_800AE8B0, encounterTable09Maps_800AE8B4, encounterTable10Maps_800AE8B8, encounterTable11Maps_800AE8BC,
    encounterTable12Maps_800AE8C0, encounterTable13Maps_800AE8C4, encounterTable14Maps_800AE8C8, encounterTable15Maps_800AE8CC,
    encounterTable16Maps_800AE8D0, encounterTable17Maps_800AE8D4, encounterTable18Maps_800AE8D8, encounterTable19Maps_800AE8DC,
    encounterTable20Maps_800AE8E0, encounterTable21Maps_800AE8E4, encounterTable22Maps_800AE8E8, encounterTable23Maps_800AE8EC,
    encounterTable24Maps_800AE8F0, encounterTable25Maps_800AE8F4, encounterTable26Maps_800AE8F8, encounterTable27Maps_800AE8FC,
    encounterTable28Maps_800AE900, encounterTable29Maps_800AE904, encounterTable30Maps_800AE908, encounterTable31Maps_800AE90C,
    encounterTable32Maps_800AE910, encounterTable33Maps_800AE914, encounterTable34Maps_800AE934, encounterTable35Maps_800AE938,
    encounterTable36Maps_800AE940, encounterTable37Maps_800AE944, encounterTable38Maps_800AE948, encounterTable39Maps_800AE94C,
    encounterTable40Maps_800AE950, encounterTable41Maps_800AE954, encounterTable42Maps_800AE958, encounterTable43Maps_800AE95C,
    encounterTable44Maps_800AE960, encounterTable45Maps_800AE964, encounterTable46Maps_800AE968, encounterTable47Maps_800AE96C,
    encounterTable48Maps_800AE970, encounterTable49Maps_800AE974, encounterTable50Maps_800AE978, encounterTable51Maps_800AE97C,
    encounterTable52Maps_800AE980, encounterTable53Maps_800AE984, encounterTable54Maps_800AE988, encounterTable55Maps_800AE98C,
    encounterTable56Maps_800AE990, encounterTable57Maps_800AE994, encounterTable58Maps_800AE998, encounterTable59Maps_800AE99C,
    encounterTable60Maps_800AE9A0, encounterTable61Maps_800AE9A4, encounterTable62Maps_800AE9A8, encounterTable63Maps_800AE9AC,
    encounterTable64Maps_800AE9B0, encounterTable65Maps_800AE9B4, encounterTable66Maps_800AE9B8, encounterTable67Maps_800AE9BC,
    encounterTable68Maps_800AE9C0, encounterTable69Maps_800AE9C4, encounterTable70Maps_800AE9C8, encounterTable71Maps_800AE9CC,
    encounterTable72Maps_800AE9D0,
};
GameSpawnMember encounterGroups_800AEB00[3][3] = {
    { { 0, 0, 0 }, { 3, 0, 0 }, { 3, 0, 0 } },
    { { 0, 0, 0 }, { 3, 0, 0 }, { 3, 0, 0 } },
    { { 0, 0, 0 }, { 3, 0, 0 }, { 3, 0, 0 } },
};
int encounterSpecies_800AEB6C[4] = { 211, 211, 211, 211 };
int mdecBufferMode_800AEB7C = 2;
EffectFile eventEffects_800AEB80 = { 0 };
int *eventReloc_800AEBBC = 0;
void *eventTiy_800AEBC0[2] = { 0 };
void *eventDataBuf_800AEBC8 = 0;
int eventRecords_800AEBCC[2] = { 0 };
int eventTempFlags_800AEBD4 = 0;
int sceneScriptId_800AEBD8 = -1;
int nextScriptId_800AEBDC = 0;
int eventBattlePending_800AEBE0 = 0;
int eventBattleLoseWarp_800AEBE4 = 1;
int currentMessageId_800AEBE8 = 0x8000;
int currentVoice_800AEBEC = 0;
int voiceTable_800AEBF0 = 0;
int eventResult_800AEBF4 = 0;
GameMapSelect mapSelect_800AEBF8 = {
    -1, -1,
    {
        { 1, 3, 0, 0x40, 0, 0 },
        { 1, 3, 0, 0x40, 0, 0 },
        { 1, 3, 0, 0x40, 0, 0 },
        { 1, 3, 0, 0x40, 0, 0 },
        { 1, 3, 0, 0x40, 0, 0 },
        { 1, 3, 0, 0x40, 0, 0 },
    },
};
int mapArea0Map00Entrances_800AEC44[20] = {
    0x1D70067, 0xFFFF0000, 0x10019, 0, 0x1D80068, 0xFFFF0001, 0x10019, 0,
    0x1D90069, 0xFFFF0002, 0x10019, 0, 0x1DA006A, 0xFFFF0003, 0x10019, 0,
    -1,
};
int mapArea0Map01Entrances_800AEC94[20] = {
    0x1DB006B, 0xFFFF0000, 0x10019, 0, 0x1DC006C, 0xFFFF0001, 0x10019, 0,
    0x1DD006D, 0xFFFF0002, 0x10019, 0, 0x1DE006E, 0xFFFF0003, 0x10019, 0,
    -1,
};
int mapArea0Map02Entrances_800AECE4[16] = {
    0x1DF006F, 0, 0x10022, 0x800B276C, 0x1DF0071, 0x10000, 0x10022, 0x800B2768,
    0x1E00070, 0xFFFF0001, 0x10019, 0x800B2618, -1,
};
int mapArea0Map03Entrances_800AED24[304] = {
    0x1E10072, 0x1080000, 143, 0x800B3128, 0x1E20073, 0x1090001, 143, 0,
    0x1E30074, 0x10A0002, 143, 0, 0x1E40075, 0x10B0003, 143, 0,
    0x1E50076, 0x10C0004, 143, 0, 0x1E60077, 0x10D0005, 143, 0,
    0x1E70078, 0x10E0006, 143, 0, 0x1E80079, 0x10F0007, 143, 0,
    0x1E9007A, 0x1100008, 143, 0, 0x1EA007B, 0x1110009, 143, 0,
    0x1EB007C, 0x112000A, 143, 0, 0x1EC007D, 0x113000B, 143, 0,
    0x1ED007E, 0x114000C, 143, 0, 0x1EE007F, 0x115000D, 143, 0,
    0x1EF0080, 0x116000E, 143, 0, 0x1F00081, 0x117000F, 143, 0,
    0x1F10082, 0x1180010, 143, 0, 0x1F20083, 0x1190011, 143, 0,
    0x1F30084, 0x11A0012, 143, 0, 0x1F40085, 0x11B0013, 143, 0,
    0x1F50086, 0x11C0014, 143, 0, 0x1F60087, 0x11D0015, 143, 0,
    0x1F70088, 0x11E0016, 143, 0, 0x1F80089, 0x11F0017, 143, 0,
    0x1F9008A, 0x1200018, 143, 0, 0x1FA008B, 0x1210019, 143, 0,
    0x1FB008C, 0x122001A, 143, 0, 0x1FC008D, 0x123001B, 143, 0,
    0x1FD008E, 0x124001C, 143, 0, 0x1FE008F, 0x125001D, 143, 0,
    0x1FF0090, 0x126001E, 143, 0, 0x2000091, 0x127001F, 143, 0,
    0x2010092, 0x1280020, 143, 0, 0x2020093, 0x1290021, 143, 0,
    0x2030094, 0x12A0022, 143, 0, 0x2040095, 0x12B0023, 143, 0,
    0x2050096, 0x12C0024, 143, 0, 0x2060097, 0x12D0025, 143, 0,
    0x2070098, 0x12E0026, 143, 0, 0x2080099, 0x12F0027, 143, 0,
    0x209009A, 0x1300028, 143, 0, 0x20A009B, 0x1310029, 143, 0,
    0x20B009C, 0x132002A, 143, 0, 0x20C009D, 0x133002B, 143, 0,
    0x20D009E, 0x134002C, 143, 0, 0x20E009F, 0x135002D, 143, 0,
    0x20F00A0, 0x136002E, 143, 0, 0x21000A1, 0x137002F, 143, 0,
    0x21100A2, 0x1380030, 143, 0, 0x21200A3, 0x1390031, 143, 0,
    0x21300A4, 0x13A0032, 143, 0, 0x21400A5, 0x13B0033, 143, 0,
    0x21500A6, 0x13C0034, 143, 0, 0x21600A7, 0x13D0035, 143, 0,
    0x21700A8, 0x13E0036, 143, 0, 0x21800A9, 0x13F0037, 143, 0,
    0x21900AA, 0x1400038, 143, 0, 0x21A00AB, 0x1410039, 143, 0,
    0x21B00AC, 0x142003A, 143, 0, 0x21C00AD, 0x143003B, 143, 0,
    0x21D00AE, 0x144003C, 143, 0, 0x21E00AF, 0x145003D, 143, 0,
    0x21F00B0, 0x146003E, 143, 0, 0x22000B1, 0x147003F, 143, 0,
    0x22100B2, 0x1480040, 143, 0, 0x22200B3, 0x1490041, 143, 0,
    0x22300B4, 0x14A0042, 143, 0, 0x22400B5, 0x14B0043, 143, 0,
    0x22500B6, 0x14C0044, 143, 0, 0x22600B7, 0x14D0045, 143, 0,
    0x22700B8, 0x14E0046, 143, 0, 0x22800B9, 0x14F0047, 143, 0,
    0x22900BA, 0x1500048, 143, 0, 0x22A00BB, 0x1510049, 143, 0,
    0x22B00BC, 0x152004A, 143, 0, -1,
};
int mapArea0Map04Entrances_800AF1E4[32] = {
    0x22C00BD, 0x1530000, 0x10021, 0x800B260C, 0x22D00BE, 0x1540001, 0x10021, 0x800B2DB0,
    0x22E00BF, 0x1550002, 0x10021, 0x800B23E8, 0x22F00C0, 0x1560003, 0x10021, 0x800B2728,
    0x23000C1, 0x1570004, 0x10021, 0x800B2ADC, 0x23100C2, 0x1580005, 0x10021, 0,
    0x22C00BD, 0x1590000, 0x10021, 0x800B260C, -1,
};
int mapArea1Map00Entrances_800AF264[36] = {
    0x23200C3, 0x20000, 0x1000E, 0x800B2920, 0x23200C7, 0x30000, 0x1000E, 0x800B2D98,
    0x23200C8, 0x40000, 0x1000E, 0x800B2A54, 0x23200C9, 0x50000, 0x1000E, 0x800B2D98,
    0x23200CA, 0x60000, 0x1000E, 0x800B2D98, 0x23300C4, 0x70001, 0x10010, 0x800B22C4,
    0x23400C5, 0x80002, 0x10010, 0x800B2DC8, 0x23500C6, 0x90003, 0x1000E, 0x800B22C4,
    -1,
};
int mapArea1Map01Entrances_800AF2F4[32] = {
    0x23600CB, 0xA0000, 0x1000E, 0x800B2BCC, 0x23700CC, 0xB0000, 0x1000E, 0x800B2E5C,
    0x23700D0, 0xC0000, 0x1000E, 0x800B2E5C, 0x23700D1, 0xD0000, 0x1000E, 0x800B2E5C,
    0x23700D2, 0xE0000, 0x1000E, 0x800B2E5C, 0x23800CD, 0xFFFF0000, 0x1000E, 0,
    0x23900CE, 0xF0003, 0x1000E, 0x800B2910, -1,
};
int mapArea1Map02Entrances_800AF374[20] = {
    0x23B00D3, 0x100000, 0x1000E, 0x800B2A34, 0x23B00D4, 0x110000, 0x1000E, 0x800B2A2C,
    0x23B00D5, 0x120000, 0x1000E, 0x800B2A34, 0x23B00D6, 0x130000, 0x1000E, 0x800B2A3C,
    -1,
};
int mapArea1Map03Entrances_800AF3C4[20] = {
    0x23C00D7, 0x140000, 0x1000E, 0x800B2688, 0x23C00D8, 0x150000, 0x1000E, 0x800B2684,
    0x23C00D9, 0x160000, 0x1000E, 0x800B2690, 0x23C00DA, 0x170000, 0x1000E, 0x800B2688,
    -1,
};
int mapArea1Map04Entrances_800AF414[36] = {
    0x23D00DB, 0x180000, 0x1000E, 0x800B2A58, 0x23D00DD, 0x190000, 0x1000E, 0x800B2A58,
    0x23D00DE, 0x1A0000, 0x1000E, 0x800B2A58, 0x23D00DF, 0x1B0000, 0x1000E, 0x800B2A58,
    0x23E00DC, 0x1C0001, 0x1000E, 0x800B2BCC, 0x23E00E0, 0x1D0001, 0x1000E, 0x800B2BCC,
    0x23E00E1, 0x1E0001, 0x1000E, 0x800B2BCC, 0x23E00E2, 0x1F0001, 0x1000E, 0x800B2BCC,
    -1,
};
int mapArea1Map05Entrances_800AF4A4[24] = {
    0x23F00E3, 0x200000, 0x1000E, 0x800B2614, 0x23F00E5, 0x210000, 0x1000E, 0x800B2690,
    0x23F00E6, 0x220000, 0x1000E, 0x800B2690, 0x23F00E7, 0x230000, 0x1000E, 0x800B2680,
    0x24000E4, 0x240001, 0x1001E, 0x800B2608, -1,
};
int mapArea1Map06Entrances_800AF504[56] = {
    0x24100E8, 0x250000, 0x1000E, 0x800B23E8, 0x24200E9, 0x260001, 0x1000C, 0x800B29F0,
    0x24200EE, 0x270001, 0x1000C, 0x800B29E4, 0x24300EA, 0x280000, 0x1000E, 0x800B22C4,
    0x24400EB, 0x290003, 0x1000E, 0x800B272C, 0x24400EF, 0x2A0003, 0x1000E, 0x800B272C,
    0x24400F0, 0x2B0003, 0x1000E, 0x800B272C, 0x24400F1, 0x2C0003, 0x1000E, 0x800B272C,
    0x24500EC, 0x2D0004, 0x1000E, 0x800B2728, 0x24500F2, 0x2E0004, 0x1000E, 0x800B2734,
    0x24500F3, 0x2F0004, 0x1000E, 0x800B2728, 0x24500F4, 0x300004, 0x1000E, 0x800B2728,
    0x24600ED, 0x310005, 0x10017, 0x800B29EC, -1,
};
int mapArea1Map07Entrances_800AF5E4[20] = {
    0x24700F5, 0x320000, 0x1000E, 0x800B291C, 0x24700F6, 0x330000, 0x1000E, 0x800B291C,
    0x24700F7, 0x340000, 0x1000E, 0x800B2924, 0x24700F8, 0x350000, 0x1000E, 0x800B291C,
    -1,
};
int mapArea1Map08Entrances_800AF634[20] = {
    0x24800F9, 0x360000, 0x1000E, 0x800B268C, 0x24800FA, 0x370000, 0x1000E, 0x800B268C,
    0x24800FB, 0x380000, 0x1000E, 0x800B268C, 0x24800FC, 0x390000, 0x1000E, 0x800B268C,
    -1,
};
int mapArea1Map09Entrances_800AF684[20] = {
    0x24900FD, 0x3A0000, 0x1000E, 0x800B2604, 0x24900FE, 0x3B0000, 0x1000E, 0x800B2604,
    0x24900FF, 0x3C0000, 0x1000E, 0x800B2604, 0x2490100, 0x3D0000, 0x1000E, 0x800B2604,
    -1,
};
int mapArea1Map10Entrances_800AF6D4[20] = {
    0x24A0101, 0x3E0000, 0x1000E, 0x800B2608, 0x24A0102, 0x3F0000, 0x1000E, 0x800B2608,
    0x24A0103, 0x400000, 0x1000E, 0x800B2608, 0x24A0104, 0x410000, 0x1000E, 0x800B2608,
    -1,
};
int mapArea1Map11Entrances_800AF724[8] = { 0x24B0105, 0x420000, 0x1000E, 0x800B22C4, -1 };
int mapArea2Map00Entrances_800AF744[16] = {
    0x24C0106, 0x430000, 0x1000D, 0x800B2D98, 0x24C0107, 0x440000, 0x1000F, 0x800B2D98,
    0x24D0108, 0x450002, 0x1009A, 0x800B25CC, -1,
};
int mapArea2Map01Entrances_800AF784[24] = {
    0x24E0109, 0x460000, 0x10091, 0x800B2E50, 0x24E010A, 0x470001, 0x1000F, 0x800B22C4,
    0x24F010B, 0xFFFF0001, 0x1000D, 0, 0x250010C, 0x480000, 0x1000F, 0x800B2A38,
    0x251010D, 0x490001, 0x1007C, 0x800B2928, -1,
};
int mapArea2Map02Entrances_800AF7E4[12] = {
    0x252010E, 0x4A0000, 0x10091, 0x800B2A3C, 0x252010F, 0x4B0000, 0x1000F, 0x800B2AC0,
    -1,
};
int mapArea2Map03Entrances_800AF814[12] = {
    0x2530110, 0x4C0000, 0x10091, 0x800B2688, 0x2530111, 0x4D0000, 0x1000F, 0x800B2728,
    -1,
};
int mapArea2Map04Entrances_800AF844[20] = {
    0x2540112, 0x4E0000, 0x1000D, 0x800B2A3C, 0x2540113, 0x4F0000, 0x1000F, 0x800B2A34,
    0x2550114, 0x500001, 0x1000D, 0x800B2BC0, 0x2550115, 0x510001, 0x1000F, 0x800B2BC0,
    -1,
};
int mapArea2Map05Entrances_800AF894[20] = {
    0x2560116, 0x520000, 0x1000F, 0x800B2714, 0x2560117, 0x530000, 0x1000D, 0x800B2680,
    0x2570118, 0x540001, 0x1007E, 0x800B3008, 0x2570119, 0x550001, 0x1001E, 0x800B2910,
    -1,
};
int mapArea2Map06Entrances_800AF8E4[28] = {
    0x258011A, 0x560000, 0x1000D, 0x800B23E8, 0x259011B, 0x570001, 0x10091, 0x800B272C,
    0x259011C, 0x580001, 0x1000F, 0x800B272C, 0x25A011D, 0x590002, 0x1000D, 0x800B23E8,
    0x25B011E, 0x5A0003, 0x10015, 0x800B29D8, 0x25C011F, 0x5B0002, 0x10091, 0x800B23E8,
    -1,
};
int mapArea2Map07Entrances_800AF954[8] = { 0x25D0120, 0x5C0000, 0x1000F, 0x800B2758, -1 };
int mapArea2Map08Entrances_800AF974[8] = { 0x25E0121, 0x5D0000, 0x1000F, 0x800B2338, -1 };
int mapArea2Map09Entrances_800AF994[16] = {
    0x25F0122, 0x5E0000, 0x1000D, 0x800B260C, 0x2600123, 0xFFFF0001, 0x1000D, 0,
    0x2610124, 0x5F0000, 0x1000F, 0x800B260C, -1,
};
int mapArea2Map10Entrances_800AF9D4[16] = {
    0x2620125, 0x600000, 0x1000D, 0x800B2620, 0x2630126, 0xFFFF0001, 0x1000D, 0,
    0x2640127, 0x610000, 0x1000F, 0x800B2608, -1,
};
int mapArea2Map11Entrances_800AFA14[16] = {
    0x2650128, 0x620000, 0x1000D, 0x800B2618, 0x2660129, 0xFFFF0001, 0x1000D, 0,
    0x267012A, 0x630000, 0x1000F, 0x800B2610, -1,
};
int mapArea4Map00Entrances_800AFA54[28] = {
    0x268012B, 0x640000, 0x1FFFF, 0x800B2EE0, 0x2680131, 0x650000, 0x1FFFF, 0x800B3244,
    0x2680132, 0x660000, 0x1FFFF, 0x800B3054, 0x2680133, 0x670000, 0x1FFFF, 0x800B39D0,
    0x26D0130, 0x680000, 0x1FFFF, 0x800B39D0, 0x269012C, 0x690000, 0x10019, 0x800B2604,
    -1,
};
int mapArea4Map01Entrances_800AFAC4[56] = {
    0x26E0134, 0x6A0000, 17, 0x800B298C, 0x26F0135, 0x6B0001, 17, 0x800B2B10,
    0x2700136, 0x6C0002, 17, 0x800B2924, 0x2710137, 0x6D0003, 17, 0x800B2994,
    0x2720138, 0x6E0004, 17, 0x800B29D4, 0x2730139, 0x6F0005, 17, 0x800B296C,
    0x274013A, 0x700006, 17, 0x800B298C, 0x274013B, 0x710006, 0x10011, 0x800B2CDC,
    0x275013C, 0x720007, 17, 0x800B23E8, 0x276013D, 0x730008, 17, 0x800B3684,
    0x277013E, 0x740009, 0x10019, 0x800B272C, 0x277013F, 0x750009, 0x10019, 0x800B23E8,
    0x2780140, 0xFFFF000A, 0x10011, 0x800B30CC, -1,
};
int mapArea4Map02Entrances_800AFBA4[80] = {
    0x2790141, 0x760000, 32, 0x800B29AC, 0x27A0142, 0x770001, 32, 0x800B2984,
    0x27B0143, 0x780002, 32, 0x800B23E8, 0x27C0144, 0x790003, 32, 0x800B29AC,
    0x27D0145, 0x7A0004, 32, 0x800B2984, 0x27E0146, 0x7B0005, 32, 0x800B2924,
    0x27F0147, 0x7C0006, 32, 0x800B2AEC, 0x2800148, 0x7D0007, 0x10020, 0x800B3184,
    0x2800149, 0x7E0007, 0x10020, 0x800B2E5C, 0x281014A, 0x7F0008, 32, 0x800B3684,
    0x282014B, 0x800009, 32, 0x800B23E8, 0x283014C, 0x81000A, 32, 0x800B2AF0,
    0x284014D, 0x82000B, 32, 0x800B2C44, 0x285014E, 0x83000C, 32, 0x800B2924,
    0x286014F, 0x84000D, 32, 0x800B298C, 0x2860150, 0x85000D, 0x10020, 0x800B2CE4,
    0x2870151, 0x86000E, 32, 0x800B2878, 0x2870152, 0x87000E, 0x10020, 0x800B314C,
    0x28A0155, 0x880011, 32, 0x800B23E8, -1,
};
int mapArea4Map03Entrances_800AFCE4[200] = {
    0x28B0156, 0x890000, 26, 0x800B23E8, 0x28C0157, 0x8A0001, 26, 0x800B29CC,
    0x28D0158, 0x8B0002, 26, 0x800B23E8, 0x28E0159, 0x8C0003, 26, 0x800B296C,
    0x28E015A, 0x8D0003, 0x1001A, 0x800B2CBC, 0x28F015B, 0x8E0004, 26, 0x800B23E8,
    0x290015C, 0x8F0005, 26, 0x800B2924, 0x291015D, 0x900006, 26, 0x800B29AC,
    0x292015E, 0x910007, 26, 0x800B2994, 0x293015F, 0x920008, 26, 0x800B23E8,
    0x2940160, 0x930009, 26, 0x800B297C, 0x2950161, 0x94000A, 26, 0x800B3674,
    0x2960162, 0x95000B, 0x10012, 0x800B2CDC, 0x2960163, 0x96000B, 0x10012, 0x800B2CDC,
    0x2970164, 0x97000C, 0x10012, 0x800B2BC0, 0x2970165, 0x98000C, 0x10012, 0x800B2BC0,
    0x2980166, 0x99000D, 0x10012, 0x800B2CFC, 0x2980167, 0x9A000D, 0x10012, 0x800B2CFC,
    0x2990168, 0x9B000E, 0x10012, 0x800B2CDC, 0x2990169, 0x9C000E, 0x10012, 0x800B2CDC,
    0x29A016A, 0x9D000F, 26, 0x800B2F0C, 0x29B016B, 0x9E0010, 26, 0x800B298C,
    0x29C016C, 0x9F0011, 26, 0x800B2DB4, 0x29D016D, 0xA00012, 26, 0x800B29DC,
    0x29E016E, 0xA10013, 26, 0x800B23E8, 0x29F016F, 0xA20014, 0x1001C, 0x800B29D8,
    0x2A00170, 0xA30000, 26, 0x800B23E8, 0x2A10171, 0xA40001, 26, 0x800B29CC,
    0x2A20172, 0xA50002, 26, 0x800B23E8, 0x2A30173, 0xA60003, 26, 0x800B296C,
    0x2A40174, 0xA70004, 26, 0x800B23E8, 0x2A50175, 0xA80005, 26, 0x800B2924,
    0x2A60176, 0xA90006, 26, 0x800B29AC, 0x2A70177, 0xAA0007, 26, 0x800B2994,
    0x2A80178, 0xAB0008, 26, 0x800B23E8, 0x2A90179, 0xAC0009, 26, 0x800B297C,
    0x2AA017A, 0xAD000A, 26, 0x800B31E4, 0x2AB017B, 0xAE000B, 0x10012, 0x800B2CDC,
    0x2AC017C, 0xAF000C, 0x10012, 0x800B2734, 0x2AD017D, 0xB0000D, 0x10012, 0x800B2CFC,
    0x2AE017E, 0xB1000E, 0x10012, 0x800B2994, 0x2AF017F, 0xB2000F, 26, 0x800B2A80,
    0x2B00180, 0xB30010, 26, 0x800B298C, 0x2B10181, 0xB40011, 26, 0x800B2924,
    0x2B20182, 0xB50012, 26, 0x800B29DC, 0x2B30183, 0xB60013, 26, 0x800B23E8,
    0x2B40184, 0xB70014, 26, 0x800B23E8, 0x2B50185, 0xB80015, 26, 0x800B30CC,
    0x2B60186, 0xB90015, 26, 0x800B30CC, -1,
};
int mapArea4Map04Entrances_800B0004[100] = {
    0x2B70187, 0xBA0000, 31, 0x800B29B4, 0x2B80188, 0xBB0001, 31, 0x800B2924,
    0x2B90189, 0xBC0002, 31, 0x800B23E8, 0x2BA018A, 0xBD0003, 31, 0x800B2924,
    0x2BB018B, 0xBE0004, 31, 0x800B2E1C, 0x2BC018C, 0xBF0005, 31, 0x800B298C,
    0x2BD018D, 0xC00006, 31, 0x800B2974, 0x2BE018E, 0xC10007, 31, 0x800B2AEC,
    0x2BF018F, 0xC20008, 31, 0x800B2924, 0x2C00190, 0xC30009, 31, 0x800B296C,
    0x2C00191, 0xC40009, 0x1001F, 0x800B2CC4, 0x2C10192, 0xC5000A, 31, 0x800B2984,
    0x2C20193, 0xC6000B, 31, 0x800B2870, 0x2C30194, 0xC7000C, 0x10021, 0x800B30EC,
    0x2C40195, 0xC8000D, 0x10021, 0x800B23E8, 0x2C50196, 0xC9000E, 0x10021, 0x800B2728,
    0x2C60197, 0xCA000F, 0x10021, 0x800B2ADC, 0x2C70198, 0xCB0010, 0x10021, 0x800B30F0,
    0x2C70199, 0xCC0010, 0x10021, 0x800B30F0, 0x2C7019A, 0xCD0010, 0x10021, 0x800B30F0,
    0x2C8019B, 0xCE0011, 0x10021, 0x800B2908, 0x2C9019C, 0xCF0012, 0x1007A, 0x800B2B50,
    0x2CA019D, 0xD00013, 0x1007A, 0x800B2B50, 0x2CB019E, 0xD10014, 0x10097, 0x800B2678,
    -1,
};
int mapArea5Map01Entrances_800B0194[48] = {
    0x2CC019F, 0xD20000, 41, 0x800B23E8, 0x2CD01A0, 0xD30001, 41, 0x800B23E8,
    0x2CE01A1, 0xD40002, 41, 0x800B2924, 0x2CF01A2, 0xD50003, 41, 0x800B23E8,
    0x2D001A3, 0xD60004, 41, 0x800B23E8, 0x2D101A4, 0xD70005, 41, 0x800B23E8,
    0x2D201A5, 0xD80006, 41, 0x800B299C, 0x2D301A6, 0xD90007, 0x10029, 0x800B2C88,
    0x2D401A7, 0xDA0008, 0x10029, 0x800B30D4, 0x2D501A8, 0xDB0009, 0x10029, 0x800B23E8,
    0x2D601A9, 0xDC000A, 0x10029, 0x800B30D4, -1,
};
int mapArea5Map02Entrances_800B0254[68] = {
    0x2D701AA, 0xDD0000, 42, 0x800B23E8, 0x2D801AB, 0xDE0001, 42, 0x800B23E8,
    0x2D901AC, 0xDF0002, 42, 0x800B23E8, 0x2DA01AD, 0xE00003, 42, 0x800B23E8,
    0x2DB01AE, 0xE10004, 42, 0x800B23E8, 0x2DC01AF, 0xE20005, 42, 0x800B23E8,
    0x2DD01B0, 0xE30006, 42, 0x800B2924, 0x2DE01B1, 0xE40007, 0x1002A, 0x800B312C,
    0x2DF01B2, 0xE50008, 42, 0x800B30D4, 0x2E001B3, 0xE60009, 42, 0x800B23E8,
    0x2E101B4, 0xE7000A, 42, 0x800B23E8, 0x2E201B5, 0xE8000B, 42, 0x800B2C44,
    0x2E301B6, 0xE9000C, 42, 0x800B23E8, 0x2E401B7, 0xEA000D, 42, 0x800B296C,
    0x2E501B8, 0xEB000E, 42, 0x800B2E34, 0x2E801BB, 0xEC0011, 42, 0x800B23E8,
    -1,
};
int mapArea5Map03Entrances_800B0364[112] = {
    0x2E901BC, 0xED0000, 39, 0x800B23E8, 0x2EA01BD, 0xEE0001, 39, 0x800B23E8,
    0x2EB01BE, 0xEF0002, 39, 0x800B23E8, 0x2EC01BF, 0xF00003, 39, 0x800B23E8,
    0x2ED01C0, 0xF10004, 39, 0x800B23E8, 0x2EE01C1, 0xF20005, 39, 0x800B23E8,
    0x2EF01C2, 0xF30006, 39, 0x800B23E8, 0x2F001C3, 0xF40007, 39, 0x800B29A4,
    0x2F101C4, 0xF50008, 39, 0x800B23E8, 0x2F201C5, 0xF60009, 39, 0x800B23E8,
    0x2F301C6, 0xF7000A, 39, 0x800B30D4, 0x2F401C7, 0xF8000B, 0x1002B, 0x800B23E8,
    0x2F401C8, 0xF9000B, 0x1002B, 0x800B2AF8, 0x2F501C9, 0xFA000C, 0x1002B, 0x800B2878,
    0x2F501CA, 0xFB000C, 0x1002B, 0x800B2B00, 0x2F601CB, 0xFC000D, 0x1002B, 0x800B23E8,
    0x2F601CC, 0xFD000D, 0x1002B, 0x800B2AF8, 0x2F701CD, 0xFE000E, 0x10027, 0x800B23E8,
    0x2F801CE, 0xFF000F, 39, 0x800B2F10, 0x2F901CF, 0x1000010, 39, 0x800B2924,
    0x2FA01D0, 0x1010011, 39, 0x800B2878, 0x2FB01D1, 0x1020012, 39, 0x800B2924,
    0x2FC01D2, 0x1030013, 39, 0x800B23E8, 0x2FD01D3, 0x1040014, 0x10028, 0x800B2B9C,
    0x2FE01D4, 0x1050015, 39, 0x800B30D4, 0x2FF01D5, 0x1060014, 0x10028, 0x800B2800,
    0x2FF01D6, 0x1070014, 0x10028, 0x800B2CA4, -1,
};
void *mapArea0Maps_800B0524[6] = { (void *)mapArea0Map00Entrances_800AEC44, (void *)mapArea0Map01Entrances_800AEC94, (void *)mapArea0Map02Entrances_800AECE4, (void *)mapArea0Map03Entrances_800AED24, (void *)mapArea0Map04Entrances_800AF1E4 };
void *mapArea1Maps_800B053C[13] = {
    (void *)mapArea1Map00Entrances_800AF264, (void *)mapArea1Map01Entrances_800AF2F4, (void *)mapArea1Map02Entrances_800AF374, (void *)mapArea1Map03Entrances_800AF3C4,
    (void *)mapArea1Map04Entrances_800AF414, (void *)mapArea1Map05Entrances_800AF4A4, (void *)mapArea1Map06Entrances_800AF504, (void *)mapArea1Map07Entrances_800AF5E4,
    (void *)mapArea1Map08Entrances_800AF634, (void *)mapArea1Map09Entrances_800AF684, (void *)mapArea1Map10Entrances_800AF6D4, (void *)mapArea1Map11Entrances_800AF724,
};
void *mapArea2Maps_800B0570[13] = {
    (void *)mapArea2Map00Entrances_800AF744, (void *)mapArea2Map01Entrances_800AF784, (void *)mapArea2Map02Entrances_800AF7E4, (void *)mapArea2Map03Entrances_800AF814,
    (void *)mapArea2Map04Entrances_800AF844, (void *)mapArea2Map05Entrances_800AF894, (void *)mapArea2Map06Entrances_800AF8E4, (void *)mapArea2Map07Entrances_800AF954,
    (void *)mapArea2Map08Entrances_800AF974, (void *)mapArea2Map09Entrances_800AF994, (void *)mapArea2Map10Entrances_800AF9D4, (void *)mapArea2Map11Entrances_800AFA14,
};
void *mapArea3Maps_800B05A4[13] = {
    (void *)mapArea1Map00Entrances_800AF264, (void *)mapArea1Map01Entrances_800AF2F4, (void *)mapArea1Map02Entrances_800AF374, (void *)mapArea1Map03Entrances_800AF3C4,
    (void *)mapArea1Map04Entrances_800AF414, (void *)mapArea1Map05Entrances_800AF4A4, (void *)mapArea1Map06Entrances_800AF504, (void *)mapArea1Map07Entrances_800AF5E4,
    (void *)mapArea1Map08Entrances_800AF634,
};
void *mapArea4Maps_800B05D8[6] = { (void *)mapArea4Map00Entrances_800AFA54, (void *)mapArea4Map01Entrances_800AFAC4, (void *)mapArea4Map02Entrances_800AFBA4, (void *)mapArea4Map03Entrances_800AFCE4, (void *)mapArea4Map04Entrances_800B0004 };
void *mapArea5Maps_800B05F0[6] = { (void *)mapArea4Map00Entrances_800AFA54, (void *)mapArea5Map01Entrances_800B0194, (void *)mapArea5Map02Entrances_800B0254, (void *)mapArea5Map03Entrances_800B0364, (void *)mapArea4Map04Entrances_800B0004 };
GameMapEntrance **mapTable_800B0608[36] = {
    (void *)mapArea0Maps_800B0524, (void *)mapArea1Maps_800B053C, (void *)mapArea2Maps_800B0570, (void *)mapArea3Maps_800B05A4,
    (void *)mapArea4Maps_800B05D8, (void *)mapArea5Maps_800B05F0, 0, (GameMapEntrance **)5,
    (GameMapEntrance **)12, (GameMapEntrance **)12, (GameMapEntrance **)12, (GameMapEntrance **)5,
    (GameMapEntrance **)5, (GameMapEntrance **)1, (GameMapEntrance **)2, (GameMapEntrance **)3,
    (GameMapEntrance **)4, (GameMapEntrance **)5, 0, (GameMapEntrance **)1,
    (GameMapEntrance **)1, (GameMapEntrance **)1, (GameMapEntrance **)4, (GameMapEntrance **)4,
    0, (GameMapEntrance **)2, (GameMapEntrance **)2, (GameMapEntrance **)2,
    (GameMapEntrance **)4, (GameMapEntrance **)4, 0, (GameMapEntrance **)3,
    (GameMapEntrance **)3, (GameMapEntrance **)3, (GameMapEntrance **)5, (GameMapEntrance **)5,
};
int gameModeChanged_800B0698 = 0;
int levantStartPos_800B069C[5] = { 0x462, -0x2B2, 0x772, 0xFC000000 };
int shopRequest_800B06B0[3] = { 0 };
int saveRequest_800B06BC = 0;
int dword_800B06C0[3] = { 0 };
EventDesc mapLoaderTaskDef_800B06CC = { 1, 5, 8, (void *)&mapLoaderTask_800B1DC4, (EventEntryFn)InitMapLoaderTask_80027CC0, (EventEntryFn)ResetMapLoaderTask_8002830C };
EventDesc areaLoaderTaskDef_800B06E4 = { 1, 1, 8, (void *)&areaLoaderTask_800B1DB8, (EventEntryFn)InitAreaLoaderTask_80028388 };
EventDesc levantModelTaskDef_800B06FC = { 1, 5, 40, (void *)levantModelTask_800B1DA0, (EventEntryFn)LevantModelTaskInit_800ACAA4, (EventEntryFn)LevantModelTaskExit_800ACF0C };
EventDesc modelLoaderTaskDef_800B0714 = { 1, 0x8000, 92, (void *)&modelLoaderTask_8008B54C, (EventEntryFn)ModelLoaderTask_800209AC };
EventDesc actorTasksDef_800B072C = { 7, 0x8000, 0x1CC, (void *)&actorTasks_8008D43C };
EventDesc tileAnimTaskDef_800B0744 = { 1, 1, 4, (void *)&tileAnimTask_800B1DBC, (EventEntryFn)TileAnimTaskInit_800A09D8 };
EventDesc eventScriptsDef_800B075C = { 10, 0x8000, 0x124, (void *)&eventScripts_8008D410 };
EventDesc encounterWatchTaskDef_800B0774 = { 1, 5, 16, (void *)&encounterWatchTask_8008B4D0, (EventEntryFn)EncounterWatchTask_800A1314, (EventEntryFn)FreeBattleResources_800A1444 };
EventDesc battleTaskDef_800B078C = { 1, 0x8000, 16, (void *)&battleTask_8008D624 };
EventDesc battleMenuTaskDef_800B07A4 = { 1, 0x8000, 12, (void *)&battleMenuTask_8008D468 };
EventDesc dword_800B07BC = { 1, 0x8000, 0, (void *)&dword_8008D444 };
EventDesc enemyWindowsTaskDef_800B07D4 = { 1, 0x8000, 48, (void *)&enemyWindowsLayoutTask_8008B568 };
EventDesc enemyWindowTaskDef_800B07EC = { 3, 0x8000, 24, (void *)&enemyWindowTasks_8008B564 };
EventDesc actorWindowTaskDef_800B0804 = { 1, 0x8000, 20, (void *)&actorWindowTask_8008D4B0 };
EventDesc helpWindowTaskDef_800B081C = { 1, 0x8000, 20, (void *)&helpWindowTask_8008D63C };
EventDesc levantControlTaskDef_800B0834 = { 1, 1, 0x9D0, (void *)&levantControlTask_8008B4CC, (EventEntryFn)LevantControlTask_800A818C };
EventDesc dword_800B084C = { 1, 0x8000, 0x2E0, (void *)0x8008D490 };
EventDesc levantActorTaskDef_800B0864 = { 1, 5, 0x7C0, (void *)&gameTask_8008B4A4, (EventEntryFn)LevantActorTask_800A9564, (EventEntryFn)LevantActorTaskExit_800A955C };
EventDesc encounterTaskDef_800B087C = { 1, 0x8000, 24, (void *)&encounterTask_8008D674 };
EventDesc enemyAiTasksDef_800B0894 = { 3, 0x8000, 48, (void *)&enemyAiTasks_8008D49C };
EventDesc dword_800B08AC = { 1, 0x8000, 12, (void *)dword_800B1DA8 };
EventDesc eventEntitiesDef_800B08C4 = { 25, 0x8000, 148, (void *)&eventEntities_8008D400 };
EventDesc prevModeTaskDef_800B08DC = { 1, 1, 4, (void *)prevModeTask_800B1DC0, (EventEntryFn)ReturnToPrevGameMode_800A8108 };
EventDesc mapOverlayTaskDef_800B08F4 = { 1, 1, 0x100, (void *)mapOverlayTask_800B1DA4, (EventEntryFn)StartMapOverlay_800A75F8, (EventEntryFn)0x800B6F60 };
EventDesc fieldMenuTaskDef_800B090C = { 1, 0x8000, 124, (void *)&fieldMenuTask_8008D498, (EventEntryFn)0x800BD40C };
EventDesc shopCtrlTaskDef_800B0924 = { 1, 0x8000, 0, (void *)&shopCtrlTask_8008D438, (EventEntryFn)0x800B67C0 };
EventDesc shopMenuTaskDef_800B093C = { 1, 0x8000, 156, (void *)&shopMenuTask_8008D670, (EventEntryFn)0x800BB444 };
EventDesc shelfMenuTaskDef_800B0954 = { 1, 0x8000, 24, (void *)&shelfMenuTask_8008D4A8, (EventEntryFn)0x800B7000 };
EventDesc storeTaskDef_800B096C = { 1, 0x8000, 84, (void *)&storeTask_8008D3E0, (EventEntryFn)0x800BB1F4 };
EventDesc dword_800B0984 = { 1, 0x8000, 0, (void *)0x8008D478 };
EventDesc chapterOverlayTaskDef_800B099C = { 1, 1, 8, (void *)chapterOverlayTask_800B1DB0, (EventEntryFn)StartChapterOverlay_800A7690 };
EventDesc sporeTaskDef_800B09B4 = { 1, 1, 8, (void *)&sporeTask_8008D464, (EventEntryFn)InitSporeTask_80011ADC };
EventDesc fieldModeTaskDef_800B09CC = { 1, 0x8000, 80, (void *)&fieldModeTask_800B1DAC, (EventEntryFn)FieldModeTask_800A7720 };
EventDesc subOverlayTaskDef_800B09E4 = { 1, 1, 32, (void *)subOverlayTask_800B1DB4, (EventEntryFn)CheckSubOverlayRequests_800A6DAC };
GameTaskListDef globalTaskLists_800B09FC[2] = { { levantModelTask_800B1DA0 } };
GameTaskListDef gameModeChapterTasks_800B0A0C[4] = {
    { &overlayLoaderTask_8008D4C0 },
    { &soundTask_8008D4A4, 0x1000 },
    { chapterOverlayTask_800B1DB0 },
};
GameTaskListDef gameModeFieldTasks_800B0A2C[26] = {
    { &overlayLoaderTask_8008D4C0 },
    { levantModelTask_800B1DA0 },
    { &modelLoaderTask_8008B54C },
    { &soundTask_8008D4A4 },
    { (void *)&mapLoaderTask_800B1DC4, 0x100 },
    { (void *)&areaLoaderTask_800B1DB8, 0x100 },
    { &modelTasks_8008D618 },
    { (void *)&dword_8008D470 },
    { &eventScripts_8008D410 },
    { dword_800B1DA8 },
    { subOverlayTask_800B1DB4 },
    { &fieldModeTask_800B1DAC },
    { &fadeTask_8008D628 },
    { &tileAnimTask_800B1DBC },
    { &cameraTask_8008D4A0 },
    { (void *)&encounterWatchTask_8008B4D0 },
    { &eventEntities_8008D400 },
    { (void *)&levantControlTask_8008B4CC },
    { (void *)&gameTask_8008B4A4 },
    { (void *)&encounterTask_8008D674 },
    { &enemyAiTasks_8008D49C },
    { &actorTasks_8008D43C },
    { (void *)&messageWindowTask_8008D640 },
    { (void *)&vibrationTasks_8008D4B8 },
    { &sporeTask_8008D464 },
};
GameTaskListDef gameModeBattleTasks_800B0AFC[35] = {
    { (void *)&areaLoaderTask_800B1DB8, 0x100 },
    { &soundTask_8008D4A4 },
    { &overlayLoaderTask_8008D4C0 },
    { (void *)&dword_8008D470 },
    { &fadeTask_8008D628 },
    { (void *)&encounterWatchTask_8008B4D0 },
    { subOverlayTask_800B1DB4 },
    { &modelTasks_8008D618 },
    { &tileAnimTask_800B1DBC },
    { &cameraTask_8008D4A0 },
    { (void *)&battleTask_8008D624 },
    { (void *)&actionTask_8008B4C0 },
    { (void *)&battleMenuTask_8008D468 },
    { (void *)&dword_8008D444 },
    { (void *)&cmdMenuTask_8008D614 },
    { (void *)&messageWindowTask_8008D640 },
    { (void *)((char *)&dword_8008B4AC + 4) },
    { &screenFlashTasks_8008D61C },
    { (void *)&enemyWindowsLayoutTask_8008B568 },
    { (void *)&enemyWindowTasks_8008B564 },
    { (void *)&actorWindowTask_8008D4B0 },
    { (void *)&helpWindowTask_8008D63C },
    { (void *)&dword_8008B4AC },
    { (void *)&hitNumberTasks_8008D778 },
    { (void *)&vibrationTasks_8008D4B8 },
    { (void *)&levantControlTask_8008B4CC },
    { (void *)&gameTask_8008B4A4 },
    { &enemyAiTasks_8008D49C },
    { &actorTasks_8008D43C },
    { &effectTask_8008D3F8 },
    { (void *)&dword_8008D5F8 },
    { &effectObjects_8008B4A8 },
    { &miscTasks_8008D60C },
    { (void *)((char *)&dword_8008D48C + 4) },
};
GameTaskListDef gameModeBattleEndTasks_800B0C14[4] = {
    { (void *)&areaLoaderTask_800B1DB8, 0x100 },
    { &overlayLoaderTask_8008D4C0 },
    { (void *)((char *)&dword_8008D48C + 4) },
    { (void *)&messageWindowTask_8008D640 },
};
GameTaskListDef gameModeEquipTasks_800B0C34[3] = {
    { &overlayLoaderTask_8008D4C0 },
    { (void *)&equipTask_8008D4C4 },
};
GameTaskListDef gameModeMenuTasks_800B0C4C[7] = {
    { (void *)&areaLoaderTask_800B1DB8, 0x100 },
    { &overlayLoaderTask_8008D4C0 },
    { (void *)&fieldMenuTask_8008D498 },
    { (void *)&equipTask_8008D4C4 },
    { (void *)&configTask_8008B4B8 },
    { (void *)&messageWindowTask_8008D640 },
};
GameTaskListDef gameModeShopTasks_800B0C84[12] = {
    { (void *)&dword_8008D470 },
    { (void *)&areaLoaderTask_800B1DB8, 0x100 },
    { &overlayLoaderTask_8008D4C0 },
    { (void *)&shopCtrlTask_8008D438 },
    { (void *)&shopMenuTask_8008D670 },
    { (void *)&nameEntryTask_8008D484 },
    { &modelTasks_8008D618 },
    { (void *)&storeTask_8008D3E0 },
    { &actorTasks_8008D43C },
    { (void *)&shelfMenuTask_8008D4A8 },
    { &fadeTask_8008D628 },
};
GameTaskListDef gameModeSaveTasks_800B0CE4[4] = {
    { (void *)&dword_8008D62C },
    { &overlayLoaderTask_8008D4C0 },
    { &loadMenuTask_8008D480 },
};
GameTaskListDef gameModeReturnTasks_800B0D04[2] = { { prevModeTask_800B1DC0 } };
GameTaskListDef gameModeMapTasks_800B0D14[6] = {
    { &soundTask_8008D4A4 },
    { levantModelTask_800B1DA0 },
    { (void *)&dword_8008D470 },
    { &overlayLoaderTask_8008D4C0 },
    { mapOverlayTask_800B1DA4 },
};
GameTaskListDef dword_800B0D44[3] = {
    { &overlayLoaderTask_8008D4C0 },
    { (void *)((char *)&screenOffset_8008D474 + 4) },
};
GameTaskListDef gameModeLoadingTasks_800B0D5C[3] = {
    { &overlayLoaderTask_8008D4C0 },
    { subOverlayTask_800B1DB4 },
};
GameTaskListDef *gameModeTaskLists_800B0D74[12] = {
    gameModeChapterTasks_800B0A0C, gameModeFieldTasks_800B0A2C, gameModeBattleTasks_800B0AFC, gameModeEquipTasks_800B0C34,
    gameModeMenuTasks_800B0C4C, gameModeShopTasks_800B0C84, gameModeSaveTasks_800B0CE4, gameModeReturnTasks_800B0D04,
    gameModeMapTasks_800B0D14, dword_800B0D44, gameModeBattleEndTasks_800B0C14, gameModeLoadingTasks_800B0D5C,
};
EventDesc* gameEventListDefs_800B0DA4[58] = {
    &mapLoaderTaskDef_800B06CC, &eventDescs_80078EB8[3], &eventDescs_80078EB8[4], &areaLoaderTaskDef_800B06E4,
    &levantModelTaskDef_800B06FC, &modelLoaderTaskDef_800B0714, &actorTasksDef_800B072C, &eventDescs_80078EB8[20],
    &eventDescs_80078EB8[6], &tileAnimTaskDef_800B0744, &eventDescs_80078EB8[7], &encounterWatchTaskDef_800B0774,
    &battleTaskDef_800B078C, &eventDescs_80078EB8[26], &battleMenuTaskDef_800B07A4, &dword_800B07BC,
    &eventDescs_80078EB8[25], &eventDescs_80078EB8[17], &eventDescs_80078EB8[18], &enemyWindowsTaskDef_800B07D4,
    &enemyWindowTaskDef_800B07EC, &actorWindowTaskDef_800B0804, &helpWindowTaskDef_800B081C, &dword_800B084C,
    &eventDescs_80078EB8[15], &eventDescs_80078EB8[16], &eventDescs_80078EB8[10], &levantControlTaskDef_800B0834,
    &levantActorTaskDef_800B0864, &eventDescs_80078EB8[21], &eventDescs_80078EB8[22], &eventDescs_80078EB8[23],
    &eventDescs_80078EB8[24], &eventDescs_80078EB8[19], &dword_800B08AC, &eventEntitiesDef_800B08C4,
    &eventDescs_80078EB8[14], &eventDescs_80078EB8[8], &fieldMenuTaskDef_800B090C, &eventDescs_80078EB8[11],
    &eventDescs_80078EB8[12], &eventDescs_80078EB8[13], &prevModeTaskDef_800B08DC, &mapOverlayTaskDef_800B08F4,
    &eventScriptsDef_800B075C, &eventDescs_80078EB8[9], &shopCtrlTaskDef_800B0924, &shopMenuTaskDef_800B093C,
    &shelfMenuTaskDef_800B0954, &storeTaskDef_800B096C, &dword_800B0984, &chapterOverlayTaskDef_800B099C,
    &sporeTaskDef_800B09B4, &encounterTaskDef_800B087C, &enemyAiTasksDef_800B0894, &fieldModeTaskDef_800B09CC,
    &subOverlayTaskDef_800B09E4,
};
EventDesc gameMainTaskDef_800B0E8C = { 1, 1, 64, (void *)&gameMainTask_8008D46C, (EventEntryFn)GameMainInit_800A68CC };
char endMovie_800B0EA4[20] = { 184, 142, 7, 128, 208, 142, 7, 128, 48, 143, 7, 128, 140, 14, 11, 128 };
GameFieldModeHandler fieldModeHandlers_800B0EB8[1] = { { 52, (void (*)())name_800BCB00 } };
int fieldMode_800B0EC0 = 1;
GameFieldMinions fieldMinions_800B0EC4 = { 0 };
char levantBones_800B0EF8 = 0;
int dword_800B0EFC[45] = {
    0x460000, 0x10001, 1, 0x1020002, 0xB0002, 0x2030003, 0xB0003, 0x3040004,
    0xB0004, 0x4050005, 0xB0005, 0x5060005, 0xB0006, 0x6070006, 0xB0007, 0x2080003,
    0xB0008, 0x8090004, 0xB0009, 0x90A0005, 0xB000A, 0xA0B0005, 0xB000B, 0xB0C0006,
    0xB000C, 0x20D0003, 13, 0xD0E0004, 0xB000E, 0x10F0002, 0xB000F, 0xF100003,
    0xB0010, 0x10110004, 0xB0011, 0x11120005, 0xB0012, 0xF130003, 0xB0013, 0x13140004,
    0xB0014, 0x14150005, 0xB0015, -1, -1,
};
SVECTOR levantBoneScale_800B0FB0[22] = {
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
};
int dword_800B1060[9] = { 0, 0, 0, 0, 0, -0x10000, 0, 0, 0 };
// control state (0x10: StartLevantAction_800A8A30 starts nothing) and animation of each Levant battle command
GameLevantBattleAction levantBattleActions_800B1084[28] = {
    { 2, 0x10 },
    { 2, 0x19 },
    { 2, 0x1A },
    { 2, 0x1C },
    { 2, 0x1D },
    { 2, 8 },
    { 2, 0x10 },
    { 2, 0xD },
    { 2, 0x13 },
    { 2, 0x11 },
    { 2, 0x12 },
    { 2, 0x13 },
    { 2, 0x14 },
    { 2, 0x15 },
    { 2, 0x14 },
    { 2, 0x17 },
    { 2, 0x16 },
    { 2, 0x15 },
    { 2, 0x14 },
    { 2, 0x18 },
    { 0x10, 0x10 },
    { 2, 6 },
    { 2, 0xC },
    { 2, 0x11 },
    { 2, 4 },
    { 0x10, 0x10 },
    { 2, 8 },
    { 0x1A0000, 0 },
};
// model id of Levant per saveData_8008B570.field_830 (LevantModelTask_800ACB64)
int levantModelIds_800B1164[2] = { 0x28, 0x27 };
int levantBaseModels_800B116C[19] = {
    5, 6, 4, 1, 3, 2, 0, 12,
    10, 13, 11, 9, 7, 8, 18, 17,
    15, 16, 14,
};
unsigned char levantOutfitModelOffsets_800B11B8[20] = { 45, 54, 36, 9, 27, 18, 0, 108, 90, 117, 99, 81, 63, 72, 162, 153, 135, 144, 126 };
int levantSavedFtgIds_800B11CC[4] = { 12, 2, 7, -1 };
int levantAnimSets_800B11DC[19] = {
    0, 0, 0, 1, 1, 1, 1, 2,
    2, 2, 2, 2, 3, 2, 4, 4,
    4, 4, 2,
};
int battleFlags_800B1228 = 0;
unsigned int battleHitEnemies_800B122C = 0;
int battleResult_800B1230 = 0;
int dword_800B1234 = 0;
GameEnemyResult battleEnemyResults_800B1238[3] = { 0 };
int dword_800B125C = 0xB00;
GameEncounter gCtx_800B1260 = { 0 };
int dword_800B1CA8[4] = { 0 };
GameEnemy eventEnemy_800B1CB8 = { 0 };
int eventHook_800B1D98 = 0;
int dword_800B1D9C = 0;
EventNode *levantModelTask_800B1DA0[1] = { 0 };
EventNode *mapOverlayTask_800B1DA4[1] = { 0 };
EventNode *dword_800B1DA8[1] = { 0 };
EventNode *fieldModeTask_800B1DAC = 0;
EventNode *chapterOverlayTask_800B1DB0[1] = { 0 };
EventNode *subOverlayTask_800B1DB4[1] = { 0 };
int** areaLoaderTask_800B1DB8 = 0;
EventNode *tileAnimTask_800B1DBC = 0;
EventNode *prevModeTask_800B1DC0[1] = { 0 };
int** mapLoaderTask_800B1DC4 = 0;
int gameStartMode_800B1DC8[2] = { 0 };
char levantPool_800B1DD0 = 0;
int dword_800B1DD4[9] = { 0 };
char dword_800B1DF8 = 0;
int dword_800B1DFC[304] = { 0 };

// Matched
void AllocMdecBuffer_800A5804(int mode)
{
    if (mode == 0)
    {
        AllocMdecVLCBuffer_80041848();
    }
    else if (mode == 1)
    {
        AllocMdecVLCBufferInFileBuffer_8004188C();
    }
    mdecBufferMode_800AEB7C = mode;
}

// Matched
int FreeMdecBuffer_800A5854(void)
{
    int old = mdecBufferMode_800AEB7C;
    if (old == 0)
    {
        FreeMdecBuffer_800418CC();
    }
    else if (old == 1)
    {
        ReleaseMdecVLCFileBuffer_800418FC();
    }
    mdecBufferMode_800AEB7C = 2;
    return old;
}

void StopAllEventScripts_800A58B4(void)
{
    EventNode* node = eventScripts_8008D410;
    int i;
    int count = node->count;
    GameViewRect* view;
    for (i = 0; i < count; i++)
    {
        EventEntry* entry = &node->entry;
        if ((entry->flags & 0x8001) == 1)
            EndEventScript_800A6168(entry, entry->buffer);
        node = node->next;
    }
    sceneScriptId_800AEBD8 = -1;
    nextScriptId_800AEBDC = 0;
    eventTempFlags_800AEBD4 = 0;
    StopAllEventEntries_80043B40(eventScripts_8008D410);
    SetCameraTarget_80037AC8((int)&levantPos_8008BD18);
    if (!(name_80091C38 & 0x40))
    {
        view = &viewport_8008D420;
        view->x = 0;
        view->w = 0x140;
        view->y = 0;
        view->h = 0xf0;
    }
    ResetSceneFade_8001A9A4();
    voiceTable_800AEBF0 = 0;
    currentMessageId_800AEBE8 = 0x8000;
    currentVoice_800AEBEC = 0;
    eventBattlePending_800AEBE0 = 0;
    eventResult_800AEBF4 = 0;
}

// Matched
EventEntry* StartEventScript_800A59D0(int script)
{
    EventEntry* entry = AllocEventEntry_80043AF8(eventScripts_8008D410);
    if (entry)
    {
        GameEvCtx* ctx = entry->buffer;
        int i;
        entry->flags = ((((entry->flags | 1) & ~0x8000) | 4) & ~0x8000);
        ctx->start_4 = script;
        ctx->pc_8 = script;
        ctx->ret_C = script;
        ctx->id_10 = nextScriptId_800AEBDC;
        ctx->choiceMask_114 = 0;
        for (i = 7; i >= 0; i--)
        {
            ctx->vars_CC[i] = 0;
        }
        ResetEventCtx_800A5B54(ctx);
        entry->cb_8 = RunEventScript_800A6060;
        entry->cb_C = EndEventScript_800A6168;
        nextScriptId_800AEBDC++;
        return entry;
    }
    return 0;
}

// Matched
EventEntry* StartEventScriptForEntity_800A5AA0(int script, int ent)
{
    EventEntry* entry = StartEventScript_800A59D0(script);
    GameEvCtx* ctx = entry->buffer;
    ctx->ent_120 = ent;
    return entry;
}

// Matched
int GetEventScriptId_800A5AD0(EventEntry* entry)
{
    return ((GameEvCtx*)entry->buffer)->id_10;
}

// Matched
int FindEventScript_800A5AE4(int id)
{
    EventNode* node = eventScripts_8008D410;
    EventEntry* entry;
    int i;
    int count = node->count;
    for (i = 0; i < count; i++)
    {
        entry = &node->entry;
        if ((entry->flags & 0x8001) == 1)
        {
            if (id == ((GameEvCtx*)entry->buffer)->id_10)
            {
                return (int)entry;
            }
        }
        node = node->next;
    }
    return 0;
}

// Matched
void ResetEventCtx_800A5B54(GameEvCtx* ctx)
{
    int i;
    ctx->heldActors_14 = 0;
    ctx->busyActors_18 = 0;
    ctx->animActors_1C = 0;
    ctx->f20 = 0;
    ctx->flags_0 = 0;
    ctx->msgStep_B4 = 0;
    ctx->step_B8 = 0;
    ctx->maskStep_BC = 0;
    ctx->cmdStep_C0 = 0;
    ctx->waitCount_C4 = 0;
    ctx->trigger_C8 = -1;
    ctx->branch_EC = 0;
    ctx->lastMsg_110 = 0;
    ctx->msgOpen_118 = 0;
    ctx->msgX_100 = -1;
    ctx->msgY_102 = -1;
    ctx->msgPosMode_104 = -1;
    ctx->msgOptions_108 = 0;
    ctx->msgWindow_11C = 0;
    ctx->ent_120 = 0;
    ctx->callArg_F0 = 0;
    for (i = 4; i >= 0; i--)
    {
        ctx->idleAnims_24[i] = 0;
    }
}

// Matched
void ClearScriptActorBusy_800A5BCC(int actor)
{
    EventNode* node = eventScripts_8008D410;
    int i;
    int count = node->count;
    for (i = 0; i < count; i++)
    {
        EventEntry* entry = &node->entry;
        if ((entry->flags & 0x8001) == 1)
        {
            GameEvCtx* ctx = entry->buffer;
            int mask = 1 << actor;
            ctx->busyActors_18 &= ~mask;
            ctx->f20 &= ~mask;
        }
        node = node->next;
    }
}

int FireEventTrigger_800A5C40(int trigger)
{
    int fired = IsSceneHeld_800A5E68();
    EventNode* node = eventScripts_8008D410;
    int count = node->count;
    int i;
    GameEvCtx* ctx;
    GameEvEnt* ent;
    int want;
    int match;
    EventEntry* entry;
    for (i = 0; i < count; i++)
    {
        entry = &node->entry;
        if ((entry->flags & 0x8001) == 1)
        {
            ctx = entry->buffer;
            if (fired == 0 && (ctx->flags_0 & 8) && ctx->trigger_C8 == trigger)
            {
                ctx->flags_0 |= 4;
                fired = 1;
                break;
            }
        }
        node = node->next;
    }
    node = eventEntities_8008D400;
    count = node->count;
    for (i = 0; i < count; i++)
    {
        entry = &node->entry;
        if ((entry->flags & 0x8001) == 1)
        {
            ent = entry->buffer;
            if (fired)
            {
                ent->armed_78 = 0;
            }
            else if (ent->armed_78)
            {
                match = 1;
                want = ent->trigger_84;
                if (want != -1 && (want & 0x40000000))
                {
                    match = (unsigned)((want & ~0x40000000) ^ trigger) < match;
                }
                if (match)
                {
                    ent->f7C = 0;
                    if (ent->script_88)
                    {
                        StartEventScript_800A59D0(ent->script_88);
                        sceneScriptId_800AEBD8 = nextScriptId_800AEBDC - 1;
                        fired = 1;
                    }
                }
            }
        }
        node = node->next;
    }
    return fired;
}

// Matched
GameEvEnt* FindEventEntity_800A5DDC(int key, int byId, GameEvEnt* skip)
{
    EventNode* node = eventEntities_8008D400;
    int i;
    int count = node->count;
    for (i = 0; i < count; i++)
    {
        EventEntry* entry = &node->entry;
        if ((entry->flags & 0x8001) == 1)
        {
            GameEvEnt* ent = entry->buffer;
            if (skip != ent)
            {
                if (byId == 0)
                {
                    if (key == ent->f4)
                    {
                        return ent;
                    }
                }
                else
                {
                    if (key == ent->id_10)
                    {
                        return ent;
                    }
                }
            }
        }
        node = node->next;
    }
    return 0;
}

// Matched
int IsSceneHeld_800A5E68(void)
{
    return sceneScriptId_800AEBD8 >= 0;
}

int IsTriggerWaited_800A5E80(int trigger)
{
    EventNode* node = eventEntities_8008D400;
    int i;
    int count = node->count;
    for (i = 0; i < count; i++)
    {
        EventEntry* entry = &node->entry;
        if ((entry->flags & 0x8001) == 1)
        {
            GameEvEnt* obj = entry->buffer;
            if (obj->armed_78 != 0 && (obj->trigger_84 & 0xBFFFFFFF) == trigger)
                return 1;
        }
        node = node->next;
    }
    node = eventScripts_8008D410;
    count = node->count;
    for (i = 0; i < count; i++)
    {
        EventEntry* entry = &node->entry;
        if ((entry->flags & 0x8001) == 1)
        {
            GameEvCtx* obj = entry->buffer;
            if (obj->trigger_C8 == trigger)
                return 1;
        }
        node = node->next;
    }
    return 0;
}

// Matched
GameEnemy* GetEventEnemy_800A5F6C(void)
{
    if (eventBattlePending_800AEBE0)
    {
        return &eventEnemy_800B1CB8;
    }
    return 0;
}

// Matched
void SetEventHook_800A5F90(int hook)
{
    eventHook_800B1D98 = hook;
}

// Matched
int ExchangeEventResult_800A5F9C(int result)
{
    int old = eventResult_800AEBF4;
    eventResult_800AEBF4 = result;
    return old;
}

// Matched
void WarpAfterLostBattle_800A5FAC(void)
{
    if (eventBattleLoseWarp_800AEBE4)
    {
        SaveData* sd = &saveData_8008B570;
        GameMapLoc loc;
        SetEventVar_800AD16C(4, sd->mapId_2E4[1].field_0 + 4);
        FindMapEntrance_800ADCEC(&loc, GetSetReturnEntrance_800A683C(-1));
        SetEventFlag_800AD0F8(0);
        useMapStartPos_80091C94 = 1;
        mapStartMode_80091C54 = 0;
        sd->mapId_2E4[3].field_0 = 0;
        forceMapReload_80091C9C = 1;
        dword_80091C8C = 0;
        sd->mapId_2E4[0].field_0 = loc.area;
        sd->mapId_2E4[1].field_0 = loc.map;
        sd->mapId_2E4[2].field_0 = loc.entrance;
        unknownFlags_8008D678 &= ~0x20000;
    }
}

void RunEventScript_800A6060(GameTask* task, GameEvCtx* ctx)
{
    while (1)
    {
        if (fieldMode_800B0EC0 != 1)
            break;
        if (eventFuncs_800BCDBC[*(int*)ctx->pc_8](ctx) == 0)
            break;
    }
    if (ctx->flags_0 & 0x40)
        UpdateEventMessage_800BC2B4(ctx);
    if (ctx->flags_0 & 0x10)
    {
        ctx->flags_0 &= ~0x10;
        ctx->pc_8 = ctx->ret_C;
    }
    if (ctx->flags_0 & 1)
    {
        task->flags_0 &= ~1;
        task->flags_0 |= 0x8000;
        task->flags_0 &= ~4;
        task->flags_0 |= 0x8000;
    }
}

// Matched
void EndEventScript_800A6168(GameTask* task, GameEvCtx* ctx)
{
    if (sceneScriptId_800AEBD8 == ctx->id_10)
    {
        EvCmdEndScene_800B8A34(ctx);
    }
    task->flags_0 = (((task->flags_0 & ~1) | 0x8000) & ~4) | 0x8000;
}

void GetPortraitSprt_800A61CC(int who, void* sprt, void* sprtArg)
{
    GameTimImage tim;
    GameActorDesc* desc;
    if (who == 0)
    {
        tim.mode_valid = 1;
        tim.mode = 1;
        tim.prect.x = name_8007DCA4.x;
        tim.prect.y = name_8007DCA4.y;
        tim.prect.w = 0x20;
        tim.prect.h = 0x40;
        tim.crect.x = name_8007DCA8.x;
        tim.crect.y = name_8007DCA8.y;
        tim.crect.w = 0x100;
        tim.crect.h = 1;
    }
    else
    {
        desc = GetFieldMinionModelDesc_800A7A1C(who - 1);
        tim.mode_valid = 1;
        tim.mode = 1;
        tim.prect.x = name_8007DCAC[desc->clut_30].x;
        tim.prect.y = name_8007DCAC[desc->clut_30].y;
        tim.prect.w = 0x20;
        tim.prect.h = 0x40;
        tim.crect.x = name_8007DCBC[desc->clut_30].x;
        tim.crect.y = name_8007DCBC[desc->clut_30].y;
        tim.crect.w = 0x100;
        tim.crect.h = 1;
    }
    InitSprtFromTim_800298AC((int)sprt, (int)sprtArg, &tim);
}

void GetPortraitPoly_800A6308(int who, void* poly)
{
    GameTimImage tim;
    GameActorDesc* desc;
    if (who == 0)
    {
        tim.mode_valid = 1;
        tim.mode = 1;
        tim.prect.x = name_8007DCA4.x;
        tim.prect.y = name_8007DCA4.y;
        tim.prect.w = 0x20;
        tim.prect.h = 0x40;
        tim.crect.x = name_8007DCA8.x;
        tim.crect.y = name_8007DCA8.y;
        tim.crect.w = 0x100;
        tim.crect.h = 1;
    }
    else
    {
        desc = GetFieldMinionModelDesc_800A7A1C(who - 1);
        tim.mode_valid = 1;
        tim.mode = 1;
        tim.prect.x = name_8007DCAC[desc->clut_30].x;
        tim.prect.y = name_8007DCAC[desc->clut_30].y;
        tim.prect.w = 0x20;
        tim.prect.h = 0x40;
        tim.crect.x = name_8007DCBC[desc->clut_30].x;
        tim.crect.y = name_8007DCBC[desc->clut_30].y;
        tim.crect.w = 0x100;
        tim.crect.h = 1;
    }
    InitPolyFT4_80029A10(poly, &tim);
}

void GetIconSprtByKind_800A6434(int kind, int id, void* sprt, void* sprtArg)
{
    int icon;
    switch (kind)
    {
    case 0:
        break;
    case 1:
        GetPortraitSprt_800A61CC(id, sprt, sprtArg);
        break;
    case 2:
        icon = GetItemIcon_8001D2AC(id);
        goto draw;
    case 3:
        icon = GetKeyItemIcon_8001D344(id);
        goto draw;
    case 4:
    case 5:
    case 6:
        icon = GetEquipmentIcon_8001D2D4(id, kind - 4);
    draw:
        GetPublicTiySprt_80032470(icon, sprt, sprtArg);
        break;
    case 7:
        printf(aAssertionFaile_800A0660, aEventcomC_800A0688, 0x2de);
        exit(1);
        break;
    }
}

// Matched
int IsEventPointValid_800A6504(int point, int* pos)
{
    return sub_800B76B8(dword_8008B520 + (point << 3), pos) >= 0;
}

// Matched
void SetLevantWallEnabled_800A6534(int wall, int on)
{
    dword_8008B518[wall] = on;
}

// Matched
void SetActorWallEnabled_800A654C(int wall, int on)
{
    dword_8008B534[wall] = on;
}

// Matched
void SetWallsEnabled_800A6564(GameWallPair* walls, int on)
{
    if (walls->levantWall_0 >= 0)
    {
        SetLevantWallEnabled_800A6534(walls->levantWall_0, on);
    }
    if (walls->actorWall_2 >= 0)
    {
        SetActorWallEnabled_800A654C(walls->actorWall_2, on);
    }
}

// Matched
int IsAngleWithin36_800A65BC(int angleA, int angleB)
{
    return (unsigned int)(WrapAngle_8003BA18((short)(angleA - angleB)) + 0x198) < 0x331;
}

// Matched
int IsPointInViewCone_800A65F0(int* point, int* eye, unsigned short* rot, int range)
{
    unsigned int dist = 0xfff;
    IsWithinDistance_8003B740(eye, point, &dist);
    if (dist < (unsigned int)(range * range))
    {
        int angle = GameFn_8003B9E0(eye, point);
        if ((unsigned int)(WrapAngle_8003BA18((short)(rot[1] - angle)) + 0x198) < 0x331)
        {
            return 1;
        }
    }
    return 0;
}

// Matched
int IsEventPointInView_800A66A4(int* point, int* eye, unsigned short* rot)
{
    if (point[0] >= 0 && IsEventPointValid_800A6504(point[0], eye))
    {
        int angle = GameFn_8003B9E0(eye, point + 1);
        if ((unsigned int)((short)WrapAngle_8003BA18((short)(rot[1] - angle)) + 0x198) < 0x331)
        {
            return 1;
        }
    }
    return 0;
}

int GetEventString_800A6738(unsigned int id)
{
    currentMessageId_800AEBE8 = 0x8000;
    if (id <= 0xfffe)
    {
        GameMsgTable* tbl;
        currentMessageId_800AEBE8 = id;
        tbl = GetEventDataSlot_800A55B0(1);
        if (id < tbl->count)
        {
            int off = id * 8;
            off += 4;
            return *(int*)((char*)tbl + off);
        }
        return 0;
    }
    return id;
}

// Matched
int SkipActorAnims_800A67B4(unsigned int* args)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (args[6] & (1 << i))
        {
            if (i == 0)
            {
                SkipLevantAnim_800A8EA4();
            }
            else
            {
                SkipFieldMinionAnim_800A7AD8(i - 1);
            }
        }
    }
    return 0;
}

// Matched
void SetVoiceTable_800A6830(int tbl)
{
    voiceTable_800AEBF0 = tbl;
}

// Matched
int GetSetReturnEntrance_800A683C(int entrance)
{
    int old = GetEventVar_800AD154(5) << 8;
    old += GetEventVar_800AD154(6);
    if (old == 0)
    {
        old = 0x66;
        SetEventVar_800AD16C(5, 0);
        SetEventVar_800AD16C(6, old);
    }
    if (entrance >= 0)
    {
        int hi = entrance >> 8;
        SetEventVar_800AD16C(5, hi);
        SetEventVar_800AD16C(6, entrance - (hi << 8));
    }
    return old;
}

void GameMainInit_800A68CC(GameTask* task, GameMainWork* work)
{
    int i;
    int* startMode = gameStartMode_800B1DC8;
    GetGameStartMode_800A72C8((GameStartMode*)startMode);
    work->mode_0 = startMode[1];
    work->prevMode_4 = work->mode_0;
    work->nextMode_8 = work->mode_0;
    for (i = 11; i >= 0; i--)
    {
        work->modeInited_C[i] = 0;
    }
    work->eventList_3C = CreateEventList_800435B4(gameEventListDefs_800B0DA4);
    eventDispatchHalt_8008B540 = 0;
    gameModeChanged_800B0698 = 0;
    task->next_8 = GameMainStart_800A6968;
}

void GameMainStart_800A6968(GameTask* task, GameMainWork* work)
{
    GameTaskListDef* lists = globalTaskLists_800B09FC;
    int i;
    if (lists->list_0 != 0)
    {
        i = 0;
        do
        {
            RunEventListUpdate_800A7450(*lists[i].list_0);
            if (eventDispatchHalt_8008B540)
            {
                break;
            }
            i++;
        } while (lists[i].list_0 != 0);
    }
    if (eventDispatchHalt_8008B540)
    {
        goto end;
    }
    ApplyAudioOutputFormat_80030988();
    ResetFieldState_800A73A8();
    SwitchGameMode_800A6C00(task, work);
    InitGameModeTasks_800A6A48(task, work);
    task->next_8 = GameMainUpdate_800A6B00;
end:
    eventDispatchHalt_8008B540 = 0;
    gameModeChanged_800B0698 = 0;
}

void InitGameModeTasks_800A6A48(GameTask* task, GameMainWork* work)
{
    GameTaskListDef* lists;
    GameTaskListDef* list;
    if (work->modeInited_C[work->mode_0] == 0)
    {
        lists = gameModeTaskLists_800B0D74[work->mode_0];
        if (lists->list_0 != 0)
        {
            list = lists;
            do
            {
                if (list->modes_4 & 0x1000)
                {
                    RunEventListUpdate_800A7450(*list->list_0);
                }
                list++;
            } while (list->list_0 != 0);
        }
        work->modeInited_C[work->mode_0] = 1;
    }
}

void GameMainUpdate_800A6B00(GameTask* task, GameMainWork* work)
{
    GameTaskListDef* lists = gameModeTaskLists_800B0D74[work->mode_0];
    int i;
    if (lists->list_0 != 0)
    {
        i = 0;
        do
        {
            RunEventListUpdate_800A7450(*lists[i].list_0);
            if (eventDispatchHalt_8008B540)
            {
                break;
            }
            i++;
        } while (lists[i].list_0 != 0);
    }
    if (unknownFlags_8008D678 & 0x8000000)
    {
        task->next_8 = GameMainExit_800A6CCC;
        goto end;
    }
    if (gameModeChanged_800B0698 != 0)
    {
        SwitchGameMode_800A6C00(task, work);
        InitGameModeTasks_800A6A48(task, work);
    }
end:
    eventDispatchHalt_8008B540 = 0;
    gameModeChanged_800B0698 = 0;
}

void SwitchGameMode_800A6C00(GameTask* task, GameMainWork* work)
{
    GameTaskListDef* lists = gameModeTaskLists_800B0D74[work->mode_0];
    GameTaskListDef* list;
    int one = 1;
    if (lists->list_0 != 0)
    {
        list = lists;
        do
        {
            if (list->modes_4 & (one << work->nextMode_8))
                RunEventListExit_800A74F0(*list->list_0);
            list++;
        } while (list->list_0 != 0);
    }
    if (work->mode_0 == 11)
        work->mode_0 = work->prevMode_4;
    work->prevMode_4 = work->mode_0;
    work->mode_0 = work->nextMode_8;
}

// Matched
void GameMainExit_800A6CCC(GameTask* task, GameMainWork* work)
{
    RunEventListFreeCallbacks_800438F8(work->eventList_3C);
    FreeEventList_80043A5C(work->eventList_3C);
    bStopDrawingMovie_8008D45C = 1;
    task->flags_0 = (task->flags_0 & ~1) | 0x8000;
}

// Matched
void RequestGameMode_800A6D30(int mode)
{
    GameMainWork* work = gameMainTask_8008D46C->entry.buffer;
    gameModeChanged_800B0698 = 1;
    work->nextMode_8 = mode;
}

int GetGameMode_800A6D50(int which)
{
    GameMainWork* work = gameMainTask_8008D46C->entry.buffer;
    int mode = 0;
    switch ((unsigned)which)
    {
    case 0:
        mode = work->mode_0;
        break;
    case 1:
        mode = work->prevMode_4;
        break;
    case 2:
        mode = work->nextMode_8;
        break;
    }
    return mode;
}

void CheckSubOverlayRequests_800A6DAC(GameTask* task, GameSubOverlayWork* work)
{
    GameSubOverlayWork* req;
    int ov;
    EventEntry* entry;
    work->mode_0 = -1;
    unknownFlags_8008D678 &= ~8;
    req = work;
    work->waitReq_8 = 0;
    work->freeze_C = 0;
    work->halt_10 = 0;
    work->fading_14 = 0;
    work->start_1C = 0;
    if (forceMapReload_80091C9C == 1)
        return;
    if (saveData_8008B570.mapId_2E4[0].field_2 != saveData_8008B570.mapId_2E4[0].field_0)
        return;
    if (saveData_8008B570.mapId_2E4[1].field_2 != saveData_8008B570.mapId_2E4[1].field_0)
        return;
    if (saveData_8008B570.mapId_2E4[2].field_2 != saveData_8008B570.mapId_2E4[2].field_0)
        return;
    if (areaPreload_80091C40[1] != areaPreload_80091C40[0])
        return;
    if (saveData_8008B570.mapId_2E4[3].field_2 != saveData_8008B570.mapId_2E4[3].field_0)
        return;
    if (areaLoadIds_80091CB8[6] != areaLoadIds_80091CB8[7])
        return;
    if (IsMapLoading_800272D0())
        return;
    if (IsSceneHeld_800A5E68() == 0 && fieldMode_800B0EC0 == 1 && gCtx_800B1260.active_0 == 0 &&
        !(padPressed_8009194C & saveData_8008B570.buttonConfig_8[6]) && (padPressed_8009194C & saveData_8008B570.buttonConfig_8[4]))
    {
        work->waitReq_8 = fieldMode_800B0EC0;
        work->req_4 = (int)LoadOverlayIfChanged_80020D1C(1, 0xb);
        entry = AllocEventEntry_80043AF8(fieldMenuTask_8008D498);
        entry->flags = (entry->flags | 1) & ~0x8000;
        work->mode_0 = 4;
    }
    else if (IsSceneHeld_800A5E68() == 0 && gCtx_800B1260.active_0 == 0 && fieldMode_800B0EC0 != 1)
    {
        req->waitReq_8 = 1;
        req->req_4 = (int)LoadOverlayIfChanged_80020D1C(1, 0x1d);
        entry = AllocEventEntry_80043AF8(fieldModeTask_800B1DAC);
        entry->flags = (entry->flags | 1) & ~0x8000;
        req->mode_0 = 1;
    }
    else if (shopRequest_800B06B0[0])
    {
        if (shopRequest_800B06B0[1] == 0)
        {
            ov = 0xe;
        }
        else if (shopRequest_800B06B0[1] == 1)
        {
            ov = 0xe;
        }
        else if (shopRequest_800B06B0[1] == 2)
        {
            ov = 0xc;
        }
        else
        {
            ov = 0xd;
        }
        req->waitReq_8 = 1;
        req->req_4 = (int)LoadOverlayIfChanged_80020D1C(1, ov);
        req->mode_0 = 5;
        req->startArg_18 = (int)shopRequest_800B06B0;
        req->start_1C = (void (*)(int))StartShopRequest_800A7204;
    }
    else if (IsSceneHeld_800A5E68() == 0 && gCtx_800B1260.active_0 == 0 && saveRequest_800B06BC)
    {
        req->waitReq_8 = 1;
        req->req_4 = (int)LoadOverlayIfChanged_80020D1C(1, 0x10);
        entry = AllocEventEntry_80043AF8(loadMenuTask_8008D480);
        entry->flags = (entry->flags | 1) & ~0x8000;
        req->mode_0 = 6;
        req->startArg_18 = (int)&saveRequest_800B06BC;
        req->start_1C = (void (*)(int))StartSaveMenuRequest_800A7280;
    }
    if (req->mode_0 >= 0)
    {
        WaitSubOverlayLoad_800A70F8(task, work);
    }
}

void WaitSubOverlayLoad_800A70F8(GameTask* task, GameSubOverlayWork* work)
{
    int busy = 0;
    GameSubOverlayWork* req = work;
    if (work->waitReq_8)
        busy = (unsigned)GetFileRequestStatus_8003BE30(work->req_4) > 0;
    if (busy == 0)
    {
        if (work->start_1C)
            work->start_1C(work->startArg_18);
        RequestGameMode_800A6D30(work->mode_0);
        task->next_8 = CheckSubOverlayRequests_800A6DAC;
        if (work->freeze_C)
            FreezeScreen_8001C224();
        else
            EndFade_8001C290();
        eventDispatchHalt_8008B540 = req->halt_10;
    }
    else
    {
        if (work->fading_14 == 0)
        {
            BeginFade_8001C260();
            work->fading_14 = 1;
            RequestGameMode_800A6D30(0xb);
            task->next_8 = WaitSubOverlayLoad_800A70F8;
        }
        eventDispatchHalt_8008B540 = 1;
    }
}

// Matched
void StartShopRequest_800A7204(GameMenuRequest* req)
{
    if (req->kind_4 == 0)
    {
        StartStore_800BAE2C(0, *(short*)&req->arg_8);
        req->active_0 = 0;
    }
    else if (req->kind_4 == 1)
    {
        StartStore_800BAE2C(1, *(short*)&req->arg_8);
        req->active_0 = 0;
    }
    else
    {
        if (req->kind_4 == 2)
        {
            StartShopCtrl_800B66C4(*(short*)&req->arg_8);
        }
        req->active_0 = 0;
    }
}

// Matched
void StartSaveMenuRequest_800A7280(GameMenuRequest* req)
{
    SetLoadMenuSavePlace_800B78B8(req->arg_8);
    if (req->endOfGame_C)
    {
        LoadMenuSetEndOfGame_800B78D0();
    }
    req->active_0 = 0;
}

GameStartMode* GetGameStartMode_800A72C8(GameStartMode* out)
{
    GameStartMode mode;
    GameMapLoc loc;
    if (unknownFlags_8008D678 & 0x40000000)
    {
        mode.useStartPos_0 = 0;
        mode.mode_4 = 1;
        FindMapEntrance_800ADCEC(&loc, 0x159);
        saveData_8008B570.mapId_2E4[0].field_2 = -1;
        saveData_8008B570.mapId_2E4[1].field_2 = -1;
        saveData_8008B570.mapId_2E4[2].field_2 = -1;
        useMapStartPos_80091C94 = 1;
        saveData_8008B570.mapId_2E4[0].field_0 = loc.area;
        saveData_8008B570.mapId_2E4[1].field_0 = loc.map;
        saveData_8008B570.mapId_2E4[2].field_0 = loc.entrance;
    }
    else if ((unsigned short)titleMenuState_8008B558[1] == 1)
    {
        mode.useStartPos_0 = 0;
        mode.mode_4 = 1;
    }
    else if ((unsigned short)titleMenuState_8008B558[1] == 4)
    {
        mode.useStartPos_0 = 1;
        mode.mode_4 = 1;
    }
    else
    {
        mode.useStartPos_0 = 1;
        mode.mode_4 = 0;
    }
    *out = mode;
    return out;
}

void ResetFieldState_800A73A8(void)
{
    GameViewRect* view = &viewport_8008D420;
    sceneBrightness_8008D40C = 0x1000;
    unpausedFrames_8008D404 = 0;
    view->x = 0;
    view->w = 0x140;
    view->y = 0;
    view->h = 0xf0;
    unknownFlags_8008D678 &= ~0x8000000;
    InitMapState_80026FAC();
    EnableCameraPoints_800A094C();
    ResetSoundTask_8002FEB8();
    InitSceneFade_8001A38C();
    ResetCameraToLevant_800376A8();
    InitLevantControl_800A8140();
    InitLevantActor_800A94CC();
    useMapStartPos_80091C94 = gameStartMode_800B1DC8[0];
}

// Matched
void RunEventListUpdate_800A7450(EventNode* node)
{
    int i;
    int count = node->count;
    for (i = 0; i < count; i++)
    {
        if (eventDispatchHalt_8008B540)
        {
            break;
        }
        if ((node->entry.flags & 0x8001) == 1)
        {
            EventEntry* entry = &node->entry;
            entry->cb_8(entry, entry->buffer);
        }
        node = node->next;
    }
}

// Matched
void RunEventListExit_800A74F0(EventNode* node)
{
    int i;
    int count = node->count;
    for (i = 0; i < count; i++)
    {
        if ((node->entry.flags & 0x8004) == 4)
        {
            EventEntry* entry = &node->entry;
            entry->cb_C(entry, entry->buffer);
        }
        node = node->next;
    }
}

enum GameStates GameShutdown_800A7574(void)
{
    DrawIntroMovie_8001AF64(endMovie_800B0EA4);
    ListFreeAll_8003FEC8(&defaultAllocList_80096090);
    SsUtAllKeyOff(0);
    if (unknownFlags_8008D678 & 0x40000000)
    {
        unknownFlags_8008D678 &= 0xBFFFFFFF;
        return 8;
    }
    if (unknownFlags_8008D678 & 0x10000000)
        return 7;
    return 0xd;
}

// Matched
void StartMapOverlay_800A75F8(GameTask* task, int* work)
{
    *work = LoadOverlayIfChanged_80020D1C(1, 0xa);
    task->next_8 = WaitMapOverlay_800A7654;
    unknownFlags_8008D678 |= 0x4000000;
}

// Matched
void WaitMapOverlay_800A7654(GameTask* task, int* work)
{
    if (GetFileRequestStatus_8003BE30(work[0]) == 0)
    {
        task->next_8 = MapSelectStart_800B6BFC;
    }
}

// Matched
void StartChapterOverlay_800A7690(GameTask* task, int* work)
{
    *work = LoadOverlayIfChanged_80020D1C(1, 0x14);
    task->next_8 = WaitChapterOverlay_800A76D8;
}

// Matched
void WaitChapterOverlay_800A76D8(GameTask* task, int* work)
{
    if (GetFileRequestStatus_8003BE30(work[0]) == 0)
    {
        task->next_8 = sub_800B66DC;
    }
}

// Matched
void SetFieldMode_800A7714(int mode)
{
    fieldMode_800B0EC0 = mode;
}

// Matched
void FieldModeTask_800A7720(GameTask* task)
{
    int mode = fieldMode_800B0EC0;
    if (mode != 1)
    {
        void (*handler)() = fieldModeHandlers_800B0EB8[mode].fn;
        task->next_8 = handler;
        handler(task);
    }
    else
    {
        task->flags_0 = (task->flags_0 & ~1) | 0x8000;
    }
}

// Matched
void ClearFieldMinions_800A7784(void)
{
    fieldMinions_800B0EC4.count = 0;
}

// Matched
int GetFieldMinionCount_800A7790(void)
{
    return fieldMinions_800B0EC4.count;
}

int AddFieldMinion_800A77A0(GameMember* member)
{
    GameFieldMinions* list = &fieldMinions_800B0EC4;
    int i = list->count;
    list->members[i] = member;
    list->suspended[list->count] = 0;
    list->hidden[list->count] = 0;
    list->count++;
    return i;
}

// Matched
GameMember* GetFieldMinion_800A77F4(int idx)
{
    return fieldMinions_800B0EC4.members[idx];
}

// Matched
int HoldFieldMinion_800A7810(int idx)
{
    if (idx < GetFieldMinionCount_800A7790())
    {
        GameMemberCb* cb = &GetFieldMinion_800A77F4(idx)->cb_14;
        return cb->hold_C(cb);
    }
    return 0;
}

// Matched
void ReleaseFieldMinion_800A785C(int idx)
{
    if (idx < GetFieldMinionCount_800A7790())
    {
        GameMemberCb* cb = &GetFieldMinion_800A77F4(idx)->cb_14;
        cb->release_10(cb);
    }
}

// Matched
int GetFieldMinionModelId_800A78A8(int idx)
{
    if (idx < GetFieldMinionCount_800A7790())
    {
        return (*GetFieldMinion_800A77F4(idx)->hdr_10)->id_0;
    }
    return 0;
}

// Matched
int sub_800A78F4(int idx)
{
    if (idx < GetFieldMinionCount_800A7790())
    {
        return (*GetFieldMinion_800A77F4(idx)->hdr_10)->f2A;
    }
    return 0;
}

// Matched
int* GetFieldMinionPos_800A7940(int idx)
{
    if (idx < GetFieldMinionCount_800A7790())
    {
        return GetFieldMinion_800A77F4(idx)->cb_14.actor_4->pos_38;
    }
    return 0;
}

// Matched
short* GetFieldMinionRot_800A7984(int idx)
{
    if (idx < GetFieldMinionCount_800A7790())
    {
        return GetFieldMinion_800A77F4(idx)->cb_14.actor_4->rot_5C;
    }
    return 0;
}

// Matched
int IsFieldMinionVisible_800A79C8(int idx)
{
    if (idx < GetFieldMinionCount_800A7790())
    {
        return ((GetFieldMinion_800A77F4(idx)->cb_14.actor_4->flags_4 >> 13) ^ 1) & 1;
    }
    return 0;
}

// Matched
GameActorDesc* GetFieldMinionModelDesc_800A7A1C(int idx)
{
    if (idx < GetFieldMinionCount_800A7790())
    {
        return (GameActorDesc*)GetFieldMinion_800A77F4(idx)->cb_14.actor_4->model_15C;
    }
    return 0;
}

// Matched
int GetFieldMinionActor_800A7A60(int idx)
{
    if (idx < GetFieldMinionCount_800A7790())
    {
        return (int)GetFieldMinion_800A77F4(idx)->cb_14.actor_4;
    }
    return 0;
}

// Matched
int GetFieldMinionAnims_800A7A9C(int idx)
{
    if (idx < GetFieldMinionCount_800A7790())
    {
        return (int)GetFieldMinion_800A77F4(idx)->cb_14.anims_8;
    }
    return 0;
}

// Matched
void SkipFieldMinionAnim_800A7AD8(int idx)
{
    SkipActorAnimToEnd_8001D9B0(GetFieldMinionActor_800A7A60(idx));
}

void SuspendFieldMinions_800A7B00(int idx)
{
    int i;
    int end;
    Actor* actor;
    if (idx < 0)
    {
        i = 0;
        end = GetFieldMinionCount_800A7790();
    }
    else
    {
        i = idx;
        end = idx + 1;
    }
    for (; i < end; i++)
    {
        actor = GetFieldMinion_800A77F4(i)->cb_14.actor_4;
        if (fieldMinions_800B0EC4.suspended[i] == 0)
        {
            if (!(actor->flags_4 & 0x2000))
            {
                SetActorAnimPaused_8001D6EC(actor, 1);
                SetActorVisible_8001D730(actor, 0);
                fieldMinions_800B0EC4.hidden[i] = 1;
            }
            if (!(actor->task_0->flags & 0x8000))
            {
                SetActorActive_8001D658(actor, 0);
                fieldMinions_800B0EC4.suspended[i] = 1;
            }
        }
    }
}

void ResumeFieldMinions_800A7BF0(int idx)
{
    int i, end;
    Actor* actor;
    if (idx < 0)
    {
        i = 0;
        end = GetFieldMinionCount_800A7790();
    }
    else
    {
        i = idx;
        end = idx + 1;
    }
    for (; i < end; i++)
    {
        actor = GetFieldMinion_800A77F4(i)->cb_14.actor_4;
        if (fieldMinions_800B0EC4.suspended[i])
        {
            if (fieldMinions_800B0EC4.hidden[i])
            {
                SetActorAnimPaused_8001D6EC(actor, 0);
                SetActorVisible_8001D730(actor, 1);
                fieldMinions_800B0EC4.hidden[i] = 0;
            }
            SetActorActive_8001D658(actor, 1);
            fieldMinions_800B0EC4.suspended[i] = 0;
        }
    }
}

int IsFieldMinionIdle_800A7CB8(int idx)
{
    if (idx < GetFieldMinionCount_800A7790())
        return IsActorIdle_8001E1C8(GetFieldMinion_800A77F4(idx)->cb_14.actor_4);
    return 0;
}

int IsFieldMinionReady_800A7CFC(int idx)
{
    if (idx < GetFieldMinionCount_800A7790())
        return IsActorActionReady_8001E1DC(GetFieldMinion_800A77F4(idx)->cb_14.actor_4);
    return 0;
}

// Matched
void FieldMinionCommand_800A7D40(int idx, GameActorCmd* cmd)
{
    ActorActionDesc desc;
    GameModelHdr** hdr;
    GameMemberCb* cb;
    Actor* actor;
    int start;
    int flags;
    int flags2;
    int flags3;
    if (idx < GetFieldMinionCount_800A7790())
    {
        hdr = GetFieldMinion_800A77F4(idx)->hdr_10;
        cb = &GetFieldMinion_800A77F4(idx)->cb_14;
        actor = cb->actor_4;
        desc.flags_0 = 0;
        desc.script_4 = 0;
        desc.target_8 = 0;
        desc.turnStep_C = 0;
        desc.hitAnim_E = -1;
        desc.effect_10 = -1;
        desc.effectKinds_18 = 0;
        desc.loopCount_20 = 0;
        desc.scaleTarget_22 = 0;
        desc.field_1C = 1;
        desc.nextAnim_24 = -1;
        desc.nextAnim_26 = -1;
        desc.anim_28 = -1;
        desc.queuedAnim_2A = -1;
        desc.field_2C = 0;
        desc.path_30 = 0;
        desc.field_1C = cmd->wait_8;
        start = 0;
        switch (cmd->kind_4)
        {
        case 0:
            if (cmd->opts_14 != -1)
                desc.nextAnim_24 = cmd->opts_14;
            else
                desc.nextAnim_24 = (*hdr)->walkAnim_20;
            desc.target_8 = &cmd->x_18;
            desc.turnStep_C = (*hdr)->turnStep_26;
            start = 1;
            break;
        case 1:
            if (cmd->opts_14 != -1)
                desc.nextAnim_24 = cmd->opts_14;
            else
                desc.nextAnim_24 = (*hdr)->runAnim_22;
            desc.target_8 = &cmd->x_18;
            desc.turnStep_C = (*hdr)->turnStep_26;
            start = 1;
            break;
        case 2:
            if (cmd->opts_14 != -1)
                desc.nextAnim_26 = cmd->opts_14;
            else
                desc.nextAnim_26 = (*hdr)->turnAnim_24;
            desc.target_8 = &cmd->x_18;
            desc.turnStep_C = (*hdr)->turnStep_26;
            start = 1;
            break;
        case 3:
        case 4:
            desc.script_4 = (ActorScriptCmd*)cb->anims_8[cmd->arg_C];
            start = 1;
            break;
        case 5:
            desc.script_4 = (ActorScriptCmd*)cmd->data_24;
            start = 1;
            break;
        case 6:
            SetActorVisible_8001D730(actor, cmd->arg_C);
            start = 0;
            break;
        case 7:
            SetActorGroundMove_8001D68C(actor, cmd->arg_C);
            start = 0;
            break;
        case 8:
            SetActorRootMotion_8001D6BC(actor, cmd->arg_C);
            start = 0;
            break;
        case 9:
        case 10:
            desc.anim_28 = cmd->arg_C;
            desc.queuedAnim_2A = (cmd->kind_4 == 10) ? cmd->arg2_10 : -1;
            desc.turnStep_C = (cmd->opts_14 & 1) ? -1 : -2;
            desc.field_2C = (cmd->opts_14 >> 3) & 1;
            desc.flags_0 = (cmd->opts_14 >> 2) & 1;
            flags3 = desc.flags_0;
            if (cmd->opts_14 & 0x10)
                flags3 |= 2;
            desc.flags_0 = flags3;
            start = 1;
            break;
        case 11:
            desc.anim_28 = cmd->arg_C;
            if (cmd->arg2_10 >= 0)
                desc.queuedAnim_2A = cmd->arg2_10;
            else
                desc.queuedAnim_2A = actor->animIdx_C2;
            desc.turnStep_C = (cmd->opts_14 & 1) ? -1 : -2;
            desc.field_2C = (cmd->opts_14 >> 3) & 1;
            desc.flags_0 = (cmd->opts_14 >> 2) & 1;
            flags = desc.flags_0;
            if (cmd->opts_14 & 0x10)
                flags |= 2;
            desc.flags_0 = flags;
            flags2 = flags;
            if (cmd->opts_14 & 0x20)
                flags2 |= 4;
            desc.flags_0 = flags2;
            desc.path_30 = (ActorPath*)cmd->data_24;
            start = 1;
            break;
        case 13:
            break;
        }
        if (start)
        {
            StartActorAction_8001E254(actor, &desc);
        }
        else if (cmd->wait_8)
        {
            ClearScriptActorBusy_800A5BCC(idx + 3);
        }
    }
}

// the jump table of LevantControlTask_800A818C (asm; its targets are labels of the generated asm, gen_asm.jump_label):
// delete it and its externs in game.h when the function is C, the switch emits it then
// (the zero word behind it in the original is the next jump table's .align 3, which the compiler adds)

void TriggerFieldMinionEffect_800A80C4(int idx)
{
    if (idx < GetFieldMinionCount_800A7790())
        TriggerActorEffect_8001E28C(GetFieldMinion_800A77F4(idx)->cb_14.actor_4);
}

void ReturnToPrevGameMode_800A8108()
{
    RequestGameMode_800A6D30(GetGameMode_800A6D50(1));
    eventDispatchHalt_8008B540 = 1;
}

void EmptyCallback_800A8138()
{
}

void InitLevantControl_800A8140()
{
    GameLevantCtl* ctl = levantControlTask_8008B4CC->buffer_24;
    FirFilterInit_8001450C(ctl->turnBuf_5C, &ctl->turn_4C, dword_800795C0, 4);
    ctl->flags_0 = 0;
    ctl->f9C = 0;
    ctl->state_C6 = 0;
}

// Levant's movement command for this frame (SetLevantMoveCmd_800AB37C): 1 / 4 / 2 move, 0x10000000 / 0x20000000 turn
// (or-ed onto a move), 0x50000000 / 0x60000000 turn on the spot
// Matched
void LevantControlTask_800A818C(EventEntry* entry, GameLevantCtl* ctl)
{
    int cmd;
    short angle;
    ctl->pos_10.x = levantPos_8008BD18.pos.x;
    ctl->pos_10.y = levantPos_8008BD18.pos.y;
    ctl->pos_10.z = levantPos_8008BD18.pos.z;
    switch (ctl->state_C6)
    {
    case 0:
        if (ctl->flags_0 & 0x20)
        {
            ctl->state_C6 = 9;
            break;
        }
        if ((padHeld_800918D0[0] & saveData_8008B570.buttonConfig_8[0]) &&
                (padHeld_800918D0[0] & saveData_8008B570.buttonConfig_8[5]) ||
            (padHeld_800918D0[0] & saveData_8008B570.buttonConfig_8[8]) || pads_800918E8[0][8] == 4)
        {
            int dir;
            cmd = 0;
            if (FindFacingFieldMinion_800A9164(&dir) == 1)
            {
                if (dir >= 0)
                {
                    cmd |= 0x60000000;
                }
                else
                {
                    cmd |= 0x50000000;
                }
            }
            else
            {
                cmd = 1;
            }
        }
        else if ((padHeld_800918D0[0] & saveData_8008B570.buttonConfig_8[0]) &&
                 !(padHeld_800918D0[0] & saveData_8008B570.buttonConfig_8[5]))
        {
            int dir;
            if (FindFacingFieldMinion_800A9164(&dir) == 1)
            {
                cmd = 0x40000000;
                if (dir < 0)
                {
                    cmd |= 0x10000000;
                }
                else
                {
                    cmd |= 0x20000000;
                }
            }
            else
            {
                cmd = 4;
            }
        }
        else if (padHeld_800918D0[0] & saveData_8008B570.buttonConfig_8[1])
        {
            cmd = IsFieldMinionBehind_800A926C() == 1 ? 0 : 2;
        }
        else
        {
            cmd = 0;
        }
        if (padHeld_800918D0[0] & saveData_8008B570.buttonConfig_8[2])
        {
            cmd |= 0x10000000;
        }
        else if (padHeld_800918D0[0] & saveData_8008B570.buttonConfig_8[3])
        {
            cmd |= 0x20000000;
        }
        if (IsConfirmPressedP1_8003D380(0) && FireEventTrigger_800A5C40(-1) == 1)
        {
            cmd = 0;
        }
        if (ctl->flags_0 & 0x40)
        {
            cmd = 0;
        }
        SetLevantMoveCmd_800AB37C(cmd);
        break;
    case 1:
        if (!(ctl->flags_0 & 1))
        {
            ctl->state_C6 = 0;
        }
        break;
    case 2:
        if (StartLevantActorAction_800AB1EC(ctl->anim_CC, (ctl->flags_0 >> 3) & 1, ctl->targets_34, ctl->arg_38) == 1)
        {
            ctl->state_C6 = 3;
        }
        break;
    case 3:
        cmd = 0;
        angle = WrapAngle_8003BA18(
            (short)(levantPos_8008BD18.rot.vy - ratan2Difference_8003B9E0(&levantPos_8008BD18.pos.x, &ctl->targetX_A4)));
        if ((unsigned short)(angle + 0x60) <= 0xC0)
        {
            if (IsLevantActionReady_800AB32C() == 1 && (ctl->flags_0 & 2))
            {
                ctl->flags_0 &= ~2;
                ctl->state_C6 = 4;
            }
        }
        else if (angle < 0)
        {
            cmd |= 0x20000000;
        }
        else
        {
            cmd |= 0x10000000;
        }
        SetLevantMoveCmd_800AB37C(cmd);
        break;
    case 5:
        cmd = 0;
        angle = WrapAngle_8003BA18(
            (short)(levantPos_8008BD18.rot.vy - ratan2Difference_8003B9E0(&levantPos_8008BD18.pos.x, &ctl->targetX_A4)));
        if ((unsigned short)(angle + 0x60) <= 0xC0)
        {
            ctl->state_C6 = 4;
        }
        else if (angle < 0)
        {
            cmd |= 0x20000000;
        }
        else
        {
            cmd |= 0x10000000;
        }
        SetLevantMoveCmd_800AB37C(cmd);
        break;
    case 4:
        if (ctl->flags_0 & 4)
        {
            ContinueLevantAnim_800AB1A4(0);
            ctl->state_C6 = 6;
            ctl->flags_0 &= ~4;
        }
        break;
    case 6:
        if (!(ctl->flags_0 & 8))
        {
            ctl->state_C6 = 1;
        }
        else if (IsLevantActorIdle_800AB304() == 1)
        {
            ctl->state_C6 = 1;
            ctl->flags_0 &= ~8;
        }
        break;
    case 7:
        ctl->flags_0 &= ~0x10;
        ctl->state_C6 = 1;
        ctl->flags_0 |= 0x10;
        EnterLevantActorBattle_800AB3D4();
        SetLevantMoveCmd_800AB37C(0);
    case 8:
        cmd = 0;
        angle = WrapAngle_8003BA18(
            (short)(levantPos_8008BD18.rot.vy - ratan2Difference_8003B9E0(&levantPos_8008BD18.pos.x, &ctl->targetX_A4)));
        if ((unsigned short)(angle + 0x40) <= 0x80)
        {
            ctl->state_C6 = 1;
        }
        else if (angle < 0)
        {
            cmd |= 0x20000000;
        }
        else
        {
            cmd |= 0x10000000;
        }
        SetLevantMoveCmd_800AB37C(cmd);
        break;
    case 9:
        if (!(ctl->flags_0 & 0x20) && IsLevantIdleAnim_800AB958() == 1)
        {
            SetLevantMapCollision_800ABC34(1);
            ctl->state_C6 = 0;
        }
        SetLevantMoveCmd_800AB37C(0);
        ResetLevantIdleTimer_800AB3BC();
        break;
    case 10:
    {
        int* target = &ctl->targetX_A4;
        int dist = 30000;
        int walk;
        IsWithinDistance_8003B740(&levantPos_8008BD18.pos.x, target, &dist);
        if (dist < 400 || (ctl->flags_0 & 0x80))
        {
            if (IsLevantIdleAnim_800AB958() == 1)
            {
                ctl->state_C6 = 9;
                ClearScriptActorBusy_800A5BCC(0);
            }
            walk = 0;
        }
        else
        {
            walk = 4;
        }
        angle = WrapAngle_8003BA18(
            (short)(levantPos_8008BD18.rot.vy - ratan2Difference_8003B9E0(&levantPos_8008BD18.pos.x, target)));
        if ((unsigned short)(angle + 0x40) > 0x80)
        {
            if (angle < 0)
            {
                walk |= 0x20000000;
            }
            else
            {
                walk |= 0x10000000;
            }
        }
        SetLevantMoveCmd_800AB37C(walk);
        break;
    }
    case 11:
    {
        int* target = &ctl->targetX_A4;
        int dist = 30000;
        int walk;
        IsWithinDistance_8003B740(&levantPos_8008BD18.pos.x, target, &dist);
        if (dist < 400 || (ctl->flags_0 & 0x80))
        {
            if (IsLevantIdleAnim_800AB958() == 1)
            {
                ctl->state_C6 = 9;
                ClearScriptActorBusy_800A5BCC(0);
            }
            walk = 0;
        }
        else
        {
            walk = 1;
        }
        angle = WrapAngle_8003BA18(
            (short)(levantPos_8008BD18.rot.vy - ratan2Difference_8003B9E0(&levantPos_8008BD18.pos.x, target)));
        if ((unsigned short)(angle + 0x40) > 0x80)
        {
            if (angle < 0)
            {
                walk |= 0x20000000;
            }
            else
            {
                walk |= 0x10000000;
            }
        }
        SetLevantMoveCmd_800AB37C(walk);
        break;
    }
    case 12:
        cmd = 0;
        angle = WrapAngle_8003BA18(
            (short)(levantPos_8008BD18.rot.vy - ratan2Difference_8003B9E0(&levantPos_8008BD18.pos.x, &ctl->targetX_A4)));
        if ((unsigned short)(angle + 0x40) <= 0x80 || (ctl->flags_0 & 0x80))
        {
            ctl->state_C6 = 9;
            ClearScriptActorBusy_800A5BCC(0);
        }
        else if (angle < 0)
        {
            cmd |= 0x20000000;
        }
        else
        {
            cmd |= 0x10000000;
        }
        SetLevantMoveCmd_800AB37C(cmd);
        break;
    case 13:
        if (IsLevantAnimLooped_800AB938() == 1)
        {
            ctl->state_C6 = 9;
            ClearScriptActorBusy_800A5BCC(0);
        }
        break;
    case 14:
        if (IsLevantIdleAnim_800AB958() == 1)
        {
            ctl->state_C6 = 9;
            ClearScriptActorBusy_800A5BCC(0);
            SetLevantMoveCmd_800AB37C(0);
        }
        break;
    case 15:
        if (IsLevantScriptAnimWaiting_800ABB70() == 1)
        {
            ctl->state_C6 = 9;
        }
        break;
    case 16:
        break;
    }
}


void PlaceWindowAwayFromTarget_800A88A0(int win, int flip)
{
    PlaceWindowAwayFromQuadrant_800A88E0(win, flip, GetCameraTargetQuadrant_800A8930());
}

int PlaceWindowAwayFromQuadrant_800A88E0(GameWinRect* win, int flip, int quadrant)
{
    int side = quadrant ^ flip;
    if (side & 1)
        win->x_0 = 0x130 - win->w_4;
    else
        win->x_0 = 0x10;
    if (side & 2)
        win->y_2 = 0xE0 - win->h_6;
    else
        win->y_2 = 0x10;
    return side;
}

int GetCameraTargetQuadrant_800A8930()
{
    int quadrant = cameraTargetScreenPos_8008D668[0] > 0xA0;
    if (cameraTargetScreenPos_8008D668[1] >= 0x79)
        quadrant += 2;
    return quadrant;
}

void EnterLevantBattleMode_800A895C()
{
    levantControlTask_8008B4CC->buffer_24->flags_0 |= 0x41;
}

void ExitLevantBattleMode_800A8984(int victoryPose)
{
    GameLevantCtl* ctl = levantControlTask_8008B4CC->buffer_24;
    ctl->flags_0 &= ~1;
    ctl->flags_0 &= ~0x10;
    ExitLevantActorBattle_800AB444(victoryPose, ctl);
}

void UnlockLevantMovement_800A89C8()
{
    levantControlTask_8008B4CC->buffer_24->flags_0 &= ~0x40;
}

int IsLevantIdle_800A89F0()
{
    return IsLevantActorIdle_800AB304();
}

int IsLevantDefending_800A8A10()
{
    return IsLevantDefending_800AB354();
}

GameActionFrames StartLevantAction_800A8A30(int* cmd, int isReaction)
{
    GameActionFrames frames;
    unsigned int flags;
    GameLevantCtl* ctl = levantControlTask_8008B4CC->buffer_24;
    if (levantBattleActions_800B1084[cmd[0]].state_0 == 0x10)
    {
        ctl->state_C6 = 5;
        frames.hit = 0;
        frames.end = 0;
        return frames;
    }
    ctl->state_C6 = levantBattleActions_800B1084[cmd[0]].state_0;
    ctl->anim_CC = levantBattleActions_800B1084[cmd[0]].anim_4;
    if (ctl->anim_CC == 8 && (int)((settingsFlags_8008B58C.word >> 21) & 1) == 1)
    {
        ctl->anim_CC = 7;
    }
    SetLevantLastCapture_800AC340(cmd[0] == 0x1a);
    flags = (ctl->flags_0 | 2) & ~4;
    ctl->arg_38 = cmd[1];
    ctl->targets_34 = cmd[3];
    ctl->flags_0 = flags;
    switch (isReaction)
    {
    case 0:
        ctl->flags_0 = flags | 8;
        break;
    case 1:
        ctl->flags_0 = flags & ~8;
        break;
    }
    if (cmd[0] == 0x12)
    {
        SetLevantDefending_800AB264();
    }
    else
    {
        ClearLevantDefending_800AB28C();
    }
    if (cmd[0] == 0x10)
    {
        sub_800AB2B4();
    }
    else
    {
        sub_800AB2DC();
    }
    frames.hit = GetLevantActionHitFrame_800AB750(ctl->anim_CC);
    frames.end = GetLevantActionEndFrame_800AB4D8(ctl->anim_CC);
    return frames;
}

int IsLevantReady_800A8BE4()
{
    return levantControlTask_8008B4CC->buffer_24->state_C6 == 4;
}

void TriggerLevantAction_800A8C0C()
{
    levantControlTask_8008B4CC->buffer_24->flags_0 |= 4;
}

UnitStatus* GetLevantStatus_800A8C34()
{
    return &levantStatus_8008BD38;
}

char* GetLevantPos_800A8C40()
{
    return (char*)&levantPos_8008BD18;
}

void DamageLevantHp_800A8C4C(int dmg)
{
    SaveData* sd = &saveData_8008B570;
    sd->levantStatus_7C8.hp_8.cur_0 -= dmg;
    if ((short)sd->levantStatus_7C8.hp_8.cur_0 < 0)
    {
        sd->levantStatus_7C8.hp_8.cur_0 = 0;
        return;
    }
    if ((short)sd->levantStatus_7C8.hp_8.max_2 < (short)sd->levantStatus_7C8.hp_8.cur_0)
        sd->levantStatus_7C8.hp_8.cur_0 = sd->levantStatus_7C8.hp_8.max_2;
}

void DamageLevantMp_800A8CA0(int dmg)
{
    SaveData* sd = &saveData_8008B570;
    sd->levantStatus_7C8.mp_C.cur_0 -= dmg;
    if ((short)sd->levantStatus_7C8.mp_C.cur_0 < 0)
    {
        sd->levantStatus_7C8.mp_C.cur_0 = 0;
        return;
    }
    if ((short)sd->levantStatus_7C8.mp_C.max_2 < (short)sd->levantStatus_7C8.mp_C.cur_0)
        sd->levantStatus_7C8.mp_C.cur_0 = sd->levantStatus_7C8.mp_C.max_2;
}

void ResetLevantControlState_800A8CF4()
{
    levantControlTask_8008B4CC->buffer_24->state_C6 = 0;
}

void StartLevantBattle_800A8D0C(int* pos)
{
    GameLevantCtl* ctl = levantControlTask_8008B4CC->buffer_24;
    ctl->state_C6 = 7;
    ctl->targetX_A4 = pos[0];
    ctl->targetY_A8 = pos[1];
    ctl->targetZ_AC = pos[2];
}

void TurnLevantToward_800A8D48(int* pos)
{
    GameLevantCtl* ctl = levantControlTask_8008B4CC->buffer_24;
    ctl->state_C6 = 8;
    ctl->targetX_A4 = pos[0];
    ctl->targetY_A8 = pos[1];
    ctl->targetZ_AC = pos[2];
}

int IsLevantBattleIdle_800A8D84()
{
    return levantControlTask_8008B4CC->buffer_24->state_C6 == 1;
}

int IsLevantActionFinished_800A8DAC()
{
    return IsLevantActionFinished_800AB85C();
}

void ClearLevantBattleStance_800A8DCC()
{
    ClearLevantBattleStance_800AB884();
}

void ResetLevantActorToIdle_800A8DEC()
{
    ResetLevantActorToIdle_800AB8AC();
}

void HoldLevantControl_800A8E0C()
{
    GameLevantCtl* ctl = levantControlTask_8008B4CC->buffer_24;
    ctl->state_C6 = 9;
    ctl->flags_0 |= 0x20;
}

void ReleaseLevantControl_800A8E38()
{
    GameLevantCtl* ctl = levantControlTask_8008B4CC->buffer_24;
    ctl->flags_0 &= ~0x20;
    StopLevantScriptMove_800A913C();
    EndLevantPath_800ABAD4();
}

int IsLevantControlHeld_800A8E7C()
{
    return levantControlTask_8008B4CC->buffer_24->state_C6 == 9;
}

void SkipLevantAnim_800A8EA4()
{
    SkipLevantAnim_800AC318();
}

void LevantCommand_800A8EC4(GameActorCmd* cmd)
{
    GameLevantCtl* ctl = levantControlTask_8008B4CC->buffer_24;
    int nextAnim;
    switch (cmd->kind_4)
    {
    case 0:
    case 1:
    case 2:
        ctl->targetX_A4 = cmd->x_18;
        ctl->targetY_A8 = cmd->y_1C;
        ctl->targetZ_AC = cmd->z_20;
        break;
    case 9:
    case 10:
        if (cmd->opts_14 & 1)
        {
            sub_800ABB98(0);
        }
        else
        {
            sub_800ABB98(1);
        }
        nextAnim = -1;
        if (cmd->kind_4 == 10)
        {
            nextAnim = cmd->arg2_10;
        }
        if (cmd->opts_14 & 4)
        {
            PlayLevantScriptAnim_800AB9A8(cmd->arg_C, nextAnim, 0);
        }
        else
        {
            PlayLevantScriptAnim_800AB9A8(cmd->arg_C, nextAnim, 1);
        }
        goto set;
    case 11:
        SetLevantRootMotionMode_800ABC78(1);
        SetLevantPath_800ABAA4(cmd->data_24);
        sub_800ABB98(1);
        PlayLevantScriptAnim_800AB9A8(cmd->arg_C, -1, 1);
    set:
        ctl->state_C6 = 9;
        ctl->cmdKind_B0 = cmd->kind_4;
        break;
    case 13:
        break;
    }
}

int IsLevantCmdDone_800A8FE0()
{
    return levantControlTask_8008B4CC->buffer_24->state_C6 == 9;
}

void FinishLevantCommand_800A9008(GameActorCmd* cmd)
{
    GameLevantCtl* ctl = levantControlTask_8008B4CC->buffer_24;
    ctl->flags_0 &= ~0x80;
    switch (cmd->kind_4)
    {
    case 0:
        ctl->state_C6 = 10;
        break;
    case 1:
        ctl->state_C6 = 11;
        break;
    case 2:
        ctl->state_C6 = 12;
        break;
    case 4:
        ctl->state_C6 = 14;
        StopLevantAnimLoop_800AB910();
        break;
    case 6:
        SetLevantVisible_800ABBD8(cmd->arg_C);
        break;
    case 7:
        SetLevantMapCollision_800ABC34(cmd->arg_C);
        break;
    case 8:
        SetLevantRootMotionMode_800ABC78(cmd->arg_C);
        break;
    case 9:
    case 10:
    case 11:
        if (cmd->opts_14 & 8)
        {
            ctl->state_C6 = 9;
            ClearScriptActorBusy_800A5BCC(0);
        }
        else
        {
            ctl->state_C6 = 13;
        }
        ContinueLevantAnim_800AB1A4(1);
        break;
    case 13:
        break;
    }
}

void FireEventTriggerById_800A911C(int id)
{
    FireEventTrigger_800A5C40(id);
}

void StopLevantScriptMove_800A913C()
{
    levantControlTask_8008B4CC->buffer_24->flags_0 |= 0x80;
}

int FindFacingFieldMinion_800A9164(int* out)
{
    int dist = 0x7FFFFFFF;
    int n = GetFieldMinionCount_800A7790();
    int i;
    int* pos;
    short angle;
    for (i = 0; i < n; i++)
    {
        if (IsFieldMinionVisible_800A79C8(i))
        {
            pos = GetFieldMinionPos_800A7940(i);
            IsWithinDistance_8003B740(&saveData_8008B570.levant_7A8.pos, pos, &dist);
            if (dist <= 0x9C3F)
            {
                angle = WrapAngle_8003BA18((short)((unsigned short)saveData_8008B570.levant_7A8.rot.vy - sub_8003B9E0(&saveData_8008B570.levant_7A8.pos.x, pos)));
                *out = angle;
                if ((unsigned)(angle + 0x3FF) < 0x7FF)
                    return 1;
            }
        }
    }
    return 0;
}

int IsFieldMinionBehind_800A926C()
{
    int dist = 0x7FFFFFFF;
    int n = GetFieldMinionCount_800A7790();
    int i;
    int* pos;
    short angle;
    for (i = 0; i < n; i++)
    {
        if (IsFieldMinionVisible_800A79C8(i))
        {
            pos = GetFieldMinionPos_800A7940(i);
            IsWithinDistance_8003B740(&saveData_8008B570.levant_7A8.pos, pos, &dist);
            if (dist <= 0x9C3F)
            {
                angle = WrapAngle_8003BA18((short)((unsigned short)saveData_8008B570.levant_7A8.rot.vy - sub_8003B9E0(&saveData_8008B570.levant_7A8.pos.x, pos)));
                if (!((unsigned)(angle + 0x400) < 0x801))
                    return 1;
            }
        }
    }
    return 0;
}

void StopLevantAnimLoop_800A9364()
{
    StopLevantAnimLoop_800AB910();
}

void SetLevantVisible_800A9384()
{
    SetLevantVisible_800ABBD8();
}

void GetLevantEffectTarget_800A93A4(EffectTarget* out)
{
    GameLevantActor* lev = gameTask_8008B4A4->buffer_24;
    out->tbl_0 = GetModelEffectTable_80024E64(lev->model_40);
    out->pos_4 = &levantPos_8008BD18.pos.x;
    out->bonePos_8 = lev->bonePos_590[0];
    out->boneMatrices_C = lev->mats_90;
    out->boneScale_2C = levantBoneScale_800B0FB0;
    out->scale_30 = 0;
}

void ResetLevantActor_800A9414(void* buf, int action, int anim)
{
    GameLevantActor* lev = (GameLevantActor*)buf;
    ApplyModelFtgSwaps_80025C38(lev->model_40, (((unsigned)unknownFlags_8008D678 >> 24) ^ 1) & 1);
    FirFilterInit_8001450C(lev->turnBuf_780, &lev->turn_770, dword_800795C0, 4);
    SetLevantAnim_800AB010(lev, action, anim, 0);
    lev->mode_C = 0;
    if (IsLevantAnimLoadedOrFree_800AAFD8(lev->prevAnim_1E) != 1)
        lev->flags_0 &= ~0x10;
    EndLevantPath_800ABAD4();
    SetLevantRootMotion_800AA140(lev);
}

void InitLevantActor_800A94CC(void)
{
    GameLevantActorInit* lev = (GameLevantActorInit*)gameTask_8008B4A4->buffer_24;
    lev->anim_1C = 3;
    lev->prevAnim_1E = 3;
    lev->mode_C = 0;
    lev->action_8 = 0;
    lev->frame_10 = 0;
    lev->blend_26 = 0;
    lev->flags_0 = 0;
    lev->fade_30 = 0;
    lev->frameFrac_1A = 0;
    lev->frameStep_18 = 0x1000;
    lev->moveCmd_4 = 0;
    UpdateLevantActorModel_800AB8DC();
    ResetLevantActor_800A9414(lev, 0, 3);
    ClearLevantFade_800AB150((GameLevantFade*)lev);
    sub_800B80C8(lev);
    lev->status_3C = dword_8008BD38;
    SetLevantStatusTint_800ABECC(dword_8008BD38);
}

void LevantActorTaskExit_800A955C()
{
}

void LevantActorTask_800A9564(int entry, GameLevantActor* lev)
{
    int i;
    lev->turn_770.input_8 = 0;
    lev->pos_48.a = levantPos_8008BD18.pos.x;
    lev->pos_48.b = levantPos_8008BD18.pos.y;
    lev->pos_48.c = levantPos_8008BD18.pos.z;
    if (lev->blend_26 >= 0x1000)
    {
        lev->flags_0 &= ~0x10;
    }
    else
    {
        lev->blend_26 += 0x400;
    }
    lev->frameFrac_1A += lev->frameStep_18;
    if (lev->frameFrac_1A >= 0x1000)
    {
        lev->frameFrac_1A -= 0x1000;
        lev->frame_10++;
    }
    if (lev->flags_0 & 0x800)
    {
        if (lev->frame_10 == (unsigned short)GetLevantAnimLoopEnd_800AC878(lev->anim_1C, GetLevantAnimSet_800AC474(lev->anim_1C)))
        {
            lev->flags_0 |= 0x8000;
            lev->frame_10 = (unsigned short)GetLevantAnimLoopStart_800AC834(lev->anim_1C, GetLevantAnimSet_800AC474(lev->anim_1C));
            SetLevantRootMotion_800AA140(lev);
        }
    }
    UpdateLevantActionState_800AAF58(lev);
    UpdateLevantMove_800A9A9C(lev);
    UpdateLevantTurn_800A99DC(lev);
    DrawLevantModel_800A9708(lev);
    RunLevantAnimCues_800AA220(lev);
    for (i = 0; i < 40; i++)
    {
        lev->mats_90[i] = boneMatrices_80098188[i];
    }
}

void DrawLevantModel_800A9708(GameLevantActor* lev)
{
    GameSkelDraw sk;
    int light;
    ModelAnim* anim;
    int flags;
    int st;
    char* sd; // read as a scalar: through SaveData* gcc reloads the status after the p->status_3C store
    light = FindNearestCameraPoint_80019CC4(&saveData_8008B570.levant_7A8);
    sd = (char*)&saveData_8008B570;
    if (lev->status_3C != *(int*)(sd + 0x7c8))
    {
        lev->status_3C = *(int*)(sd + 0x7c8);
        SetLevantStatusTint_800ABECC(*(int*)(sd + 0x7c8));
    }
    anim = &lev->model_40->anims_54[GetLevantAnimFile_800AC4A8(lev->anim_1C)];
    if (*(int*)(sd + 0x7c8) & 0x3fd)
    {
        flags = (word_8007DC8A - word_8007DC82) << 8;
    }
    else
    {
        flags = 0;
    }
    if (lev->flags_0 & 6)
    {
        int t = flags | 0xb0;
        flags = t | (lev->fade_30 << 16);
    }
    if (lev->flags_0 & 2)
    {
        lev->fade_30 += 0x80;
        if (lev->fade_30 >= 0x1000)
        {
            lev->fade_30 = 0x1000;
        }
    }
    else if (lev->flags_0 & 4)
    {
        lev->fade_30 -= 0x80;
        if (lev->fade_30 < 0)
        {
            lev->fade_30 = 0;
            ClearLevantFade_800AB150(lev);
        }
    }
    if (lev->fade_30 == 0x1000)
    {
        return;
    }
    if (lev->flags_0 & 0x20000)
    {
        return;
    }
    sk.ftg_0 = lev->model_40->ftg_50;
    sk.pos_4 = &levantPos_8008BD18.pos;
    sk.rot_8 = &levantPos_8008BD18.rot;
    sk.bones = &levantBones_800B0EF8;
    sk.base = levantBoneScale_800B0FB0;
    sk.scale_24 = 0;
    sk.pose = (char*)anim;
    sk.frame = lev->frame_10 % anim->frameCount_0;
    sk.flags = flags;
    sk.pos = (char*)lev + 0x590;
    sk.ot = pOT_8008D690;
    if (IsLevantAnimLoaded_800AC518(lev->prevAnim_1E) == 0)
    {
        lev->flags_0 &= ~0x10;
    }
    if (!(lev->flags_0 & 0x10))
    {
        DrawAnimSkel_80046A58(&sk, &pointLights_8008D534[light], 0);
    }
    else
    {
        anim = &lev->model_40->anims_54[GetLevantAnimFile_800AC4A8(lev->prevAnim_1E)];
        DrawAnimSkelBlend_80047E28(&sk, levantBoneScale_800B0FB0, (char*)anim, lev->blendFrame_14 % anim->frameCount_0, 0x1000 - lev->blend_26, &pointLights_8008D534[light], 0);
    }
    DrawSpriteVtxQuadsGT4_800459E4(&levantBones_800B0EF8, &lev->model_40->mats_5C, pOT_8008D690, sk.flags);
}

void UpdateLevantTurn_800A99DC(GameLevantActor* lev)
{
    if (lev->moveCmd_4 & 0x10000000)
        lev->turn_770.input_8 = -0x40;
    if (lev->moveCmd_4 & 0x20000000)
        lev->turn_770.input_8 = 0x40;
    if (lev->moveCmd_4 & 0x40000000)
        lev->turn_770.input_8 /= 2;
    lev->moveCmd_4 &= ~0x30000000;
    FirFilterStep_80014588(lev->turnBuf_780, &lev->turn_770, frameCount_8008D3FC);
    saveData_8008B570.levant_7A8.rot.vy += lev->turn_770.output_C.low;
}

// Moves Levant by the animation's root motion: rotated by the facing and scaled by the floor slope, or along a scripted path (0x400000), or offset from basePos_60
// Matched
void UpdateLevantMove_800A9A9C(GameLevantActor* lev)
{
    G2V12 prev;
    int dz;
    int dx;
    int div;
    int k;
    int slope;
    int rot;
    int sn;
    int cs;
    short ang;
    prev.a = lev->rootMotion_6C.a;
    prev.b = lev->rootMotion_6C.b;
    prev.c = lev->rootMotion_6C.c;
    SetLevantRootMotion_800AA140(lev);
    dz = 0;
    if (lev->flags_0 & 8)
    {
        lev->flags_0 &= ~8;
        dx = dz;
    }
    else
    {
        dx = lev->rootMotion_6C.a - prev.a;
        GetLevantAnimFile_800AC4A8(lev->anim_1C);
        lev->rootMotion_6C.c -= (dx & 0x1f) * Sign_8003B664(dx);
        dz = lev->rootMotion_6C.c;
        dz -= prev.c;
        GetLevantAnimFile_800AC4A8(lev->anim_1C);
        lev->rootMotion_6C.c -= (dz & 0x1f) * Sign_8003B664(dz);
    }
    if (lev->frame_10 == (unsigned short)GetLevantAnimLastFrame_800AC8BC(lev->anim_1C, GetLevantAnimSet_800AC474(lev->anim_1C)) ||
        ((lev->flags_0 & 0x800) && lev->frame_10 == (unsigned short)GetLevantAnimLoopEnd_800AC878(lev->anim_1C, GetLevantAnimSet_800AC474(lev->anim_1C))))
    {
        lev->flags_0 |= 0x8000;
        lev->frame_10 = (unsigned short)GetLevantAnimLoopStart_800AC834(lev->anim_1C, GetLevantAnimSet_800AC474(lev->anim_1C));
        SetLevantRootMotion_800AA140(lev);
    }
    if (lev->action_8 == 2 && (lev->flags_0 & 0x200000))
    {
        dx = 0;
        dz = dx;
    }
    if (!(lev->flags_0 & 0x84000))
    {
        div = lev->model_40->anims_54[GetLevantAnimFile_800AC4A8(lev->anim_1C)].divisor_8;
        sub_800B80C8(lev);
        slope = mapState_8008B500.meshes_C[lev->mesh_84].tris_4[lev->tri_80].nx_18 * sinTable_80084540[saveData_8008B570.levant_7A8.rot.vy & 0xfff] / 4096 +
            mapState_8008B500.meshes_C[lev->mesh_84].tris_4[lev->tri_80].nz_1C * sinTable_80084540[(saveData_8008B570.levant_7A8.rot.vy + 0x400) & 0xfff] / 4096;
        slope = 0x1000 - slope * slope / 4096;
        saveData_8008B570.levant_7A8.pos.x += dx * sinTable_80084540[(saveData_8008B570.levant_7A8.rot.vy + 0x400) & 0xfff] / 4096 * slope / 4096 / div;
        saveData_8008B570.levant_7A8.pos.z += -(dx * sinTable_80084540[saveData_8008B570.levant_7A8.rot.vy & 0xfff] / 4096) * slope / 4096 / div;
        saveData_8008B570.levant_7A8.pos.x += dz * sinTable_80084540[saveData_8008B570.levant_7A8.rot.vy & 0xfff] / 4096 * slope / 4096 / div;
        saveData_8008B570.levant_7A8.pos.z += dz * sinTable_80084540[(saveData_8008B570.levant_7A8.rot.vy + 0x400) & 0xfff] / 4096 * slope / 4096 / div;
        if (!(lev->flags_0 & 0x40000))
        {
            slope = CollideLevantWithMap_800B6DD4(lev);
            if (slope < 0)
            {
                lev->turn_770.input_8 = -0x40;
            }
            else if (slope > 0)
            {
                lev->turn_770.input_8 = 0x40;
            }
        }
    }
    else if (lev->flags_0 & 0x400000)
    {
        int d = lev->path_78->div_4;
        lev->rootMotion_6C.a = lev->path_78->steps_8[lev->pathStep_7C].x;
        lev->rootMotion_6C.b = lev->path_78->steps_8[lev->pathStep_7C].y;
        lev->rootMotion_6C.c = lev->path_78->steps_8[lev->pathStep_7C].z;
        rot = lev->path_78->steps_8[lev->pathStep_7C].rotY;
        lev->pathStep_7C++;
        if (lev->pathStep_7C >= lev->path_78->count_0)
        {
            lev->flags_0 &= ~0x400000;
            SetLevantRootMotionMode_800ABC78(0);
            lev->flags_0 = (lev->flags_0 & ~0x800) | 8;
            SetLevantAnim_800AB010(lev, 0, 3, 0);
            lev->mode_C = 0;
        }
        saveData_8008B570.levant_7A8.pos.x = lev->basePos_60.a + lev->rootMotion_6C.a / d;
        saveData_8008B570.levant_7A8.pos.y = lev->basePos_60.b + lev->rootMotion_6C.b / d;
        saveData_8008B570.levant_7A8.pos.z = lev->basePos_60.c + lev->rootMotion_6C.c / d;
        saveData_8008B570.levant_7A8.rot.vy = rot;
    }
    else
    {
        div = lev->model_40->anims_54[GetLevantAnimFile_800AC4A8(lev->anim_1C)].divisor_8;
        SetLevantRootMotion_800AA140(lev);
        sn = sinTable_80084540[saveData_8008B570.levant_7A8.rot.vy & 0xfff];
        cs = sinTable_80084540[(saveData_8008B570.levant_7A8.rot.vy + 0x400) & 0xfff];
        saveData_8008B570.levant_7A8.pos.z = lev->basePos_60.c + (lev->rootMotion_6C.c * cs - lev->rootMotion_6C.a * sn) / 4096 / div;
        saveData_8008B570.levant_7A8.pos.x = lev->basePos_60.a + (lev->rootMotion_6C.c * sn + lev->rootMotion_6C.a * cs) / 4096 / div;
        saveData_8008B570.levant_7A8.pos.y = lev->basePos_60.b + lev->rootMotion_6C.b / 32;
    }
}

void SetLevantRootMotion_800AA140(GameLevantActor* lev)
{
    ModelAnim* anim = &lev->model_40->anims_54[GetLevantAnimFile_800AC4A8(lev->anim_1C)];
    GetAnimRootMotion_8004D288((char*)lev + 0x6c, anim, (unsigned)lev->frame_10 % ((GetLevantAnimLastFrame_800AC8BC(lev->anim_1C, GetLevantAnimSet_800AC474(lev->anim_1C)) & 0xffff) + 1));
}

int GetLevantMoveDir_800AA1C0(GameLevantActor* lev)
{
    return lev->moveCmd_4 & 0xFFFFFFF;
}

int IsLevantInBattle_800AA1D4(unsigned char* lev)
{
    return lev[1] & 1;
}

void StartLevantQueuedAnim_800AA1E0(GameLevantActor* lev)
{
    lev->actionAnim_20 = lev->queuedAnim_22;
    SetLevantAnim_800AB010(lev, 0x17, 3, 0);
    lev->mode_C = 3;
}

void RunLevantAnimCues_800AA220(GameLevantActor* lev)
{
    RunAnimFrameCues_8001C440(lev->model_40, GetLevantAnimFile_800AC4A8(lev->anim_1C), lev->frame_10);
}

void UpdateLevantFieldAnim_800AA25C(GameLevantActor* lev)
{
    if (IsLevantInBattle_800AA1D4(lev) == 1)
    {
        SetLevantAnim_800AB010(lev, 7, 3, 0);
        lev->mode_C = 1;
        return;
    }
    if (lev->flags_0 & 0x4000)
    {
        return;
    }
    if (lev->flags_0 & 0x10)
    {
        return;
    }
    if (GetLevantMoveDir_800AA1C0(lev) == 1)
    {
        SetLevantAnim_800AB010(lev, 5, 2, 0);
        return;
    }
    if (GetLevantMoveDir_800AA1C0(lev) == 2)
    {
        SetLevantAnim_800AB010(lev, 4, 1, 0);
        return;
    }
    if (GetLevantMoveDir_800AA1C0(lev) == 4)
    {
        SetLevantAnim_800AB010(lev, 2, 0, 0);
        lev->flags_0 &= ~0x200000;
        return;
    }
    if (lev->moveCmd_4 & 0x30000000)
    {
        SetLevantAnim_800AB010(lev, 2, 0, 0);
        lev->flags_0 |= 0x200000;
        return;
    }
    if (GetLevantMoveDir_800AA1C0(lev) == 3)
    {
        StartLevantQueuedAnim_800AA1E0(lev);
        return;
    }
    if (++lev->idleTimer_28 > 0x5a)
    {
        SetLevantAnim_800AB010(lev, 1, 4, 0);
        lev->idleTimer_28 = 0x5a;
    }
    else
    {
        SetLevantAnim_800AB010(lev, 0, 3, 0);
    }
}

void ReturnLevantToIdle_800AA3F0(GameLevantActor* lev)
{
    SetLevantAnim_800AB010(lev, 0, 3, 0);
    lev->mode_C = 0;
    lev->flags_0 |= 0x2000;
}

// Matched
void PlayLevantActionEffect_800AA430(GameLevantActor* lev)
{
    ActorEffectReq req;
    int repeat;
    HitTimes* hitFrames;
    int loopStart;
    if (lev->effect_2C != 0x46)
    {
        if ((unsigned short)(lev->anim_1C - 7) < 2)
            repeat = 4;
        else
            repeat = lev->hitRepeat_2A;
        req.effect_0 = lev->effect_2C;
        hitFrames = GetLevantAnimHitFrames_800AC9CC(lev->actionAnim_20);
        loopStart = (unsigned short)GetLevantAnimLoopStart_800AC834(lev->anim_1C, GetLevantAnimSet_800AC474(lev->anim_1C));
        req.hitTimes_4 = RepeatHitTimes_80018200(hitFrames, loopStart, (unsigned short)GetLevantAnimLoopEnd_800AC878(lev->anim_1C, GetLevantAnimSet_800AC474(lev->anim_1C)), repeat, lev->effect_2C);
        GetLevantEffectTarget_800A93A4((EffectTarget*)&req.tbl_8);
        CollectEffectTargets_800182B8(&req, lev->targets_38);
        PlayActorEffect_800184DC(&req, 0);
    }
}


unsigned short GetLevantAnimEventFrameCur_800AB170(int anim);
// Levant battle action state machine (per action_8 state)
// Matched
void UpdateLevantBattleAction_800AA51C(GameLevantActor* lev)
{
    unsigned short GetLevantAnimLastFrame_800AC8BC(int a, int b);
    short animFlags;
    switch (lev->action_8)
    {
    case 7:
        if (GetCameraMode_800378F8() == 3)
        {
            SetLevantAnim_800AB010(lev, 9, 0xE, 0);
        }
        break;
    case 9:
        if (IsLevantInBattle_800AA1D4(lev) == 0 && !(lev->flags_0 & 0x1000))
        {
            SetModelFtg_80025B5C(lev->model_40, 2, 0x17);
            SetModelFtg_80025B5C(lev->model_40, 7, 0x19);
            ReturnLevantToIdle_800AA3F0(lev);
            break;
        }
        if (lev->frame_10 == GetLevantAnimEventFrameCur_800AB170(lev->anim_1C))
        {
            SetModelFtg_80025B5C(lev->model_40, 2, 0x18);
            SetModelFtg_80025B5C(lev->model_40, 7, 0x1A);
        }
    case 8:
        if ((unsigned int)lev->frame_10 >= (unsigned short)GetLevantAnimLoopStart_800AC834(lev->anim_1C, GetLevantAnimSet_800AC474(lev->anim_1C)))
        {
            lev->action_8 = 10;
        }
        break;
    case 10:
        lev->flags_0 = (lev->flags_0 | 0x800) & ~0x8000;
        if (IsLevantInBattle_800AA1D4(lev) == 1)
        {
            if (lev->flags_0 & 1)
            {
                lev->action_8 = 11;
            }
            break;
        }
        if (lev->flags_0 & 2)
        {
            SetModelFtg_80025B5C(lev->model_40, 2, 0x17);
            SetModelFtg_80025B5C(lev->model_40, 7, 0x19);
            SetModelFtg_80025B5C(lev->model_40, 0xC, 0xC);
        }
        if (lev->flags_0 & 0x1000)
        {
            LoadLevantAnimById_800AC604(10, 0);
            SetLevantAnim_800AB010(lev, 0x11, -1, -1);
            break;
        }
        if (lev->flags_0 & 2)
        {
            SetLevantAnim_800AB010(lev, 0x12, 3, 0);
        }
        else
        {
            SetLevantAnim_800AB010(lev, 0x12, 0xF, 0);
        }
        lev->flags_0 &= ~0x800;
        break;
    case 11:
        if (lev->flags_0 & 0x1000000)
        {
            LoadLevantAnimById_800AC604(10, 0);
        }
        IsLevantAnimLoaded_800AC518(lev->actionAnim_20);
        LoadLevantAnimById_800AC604(lev->actionAnim_20, 0);
        lev->action_8 = 12;
        lev->effect_2C = 0x46;
        if (lev->flags_0 & 0x200)
        {
            RequestLevantActionEffect_800ABCF4(lev);
        }
        break;
    case 12:
        if (lev->effect_2C == 0x46 || IsEffectReady_80014954() == 1 || lev->effect_2C == 0x46)
        {
            if (AreLevantFilesLoaded_800AC768() == 1)
            {
                lev->action_8 = 13;
            }
        }
        break;
    case 13:
        if (lev->flags_0 & 0x20)
        {
            if (!(GetLevantAnimFlags_800AC900(lev->actionAnim_20, GetLevantAnimSet_800AC474(lev->actionAnim_20)) & 1))
            {
                if (lev->actionAnim_20 == lev->anim_1C)
                {
                    SetLevantAnim_800AB010(lev, 0x10, -1, -1);
                }
                else
                {
                    SetLevantAnim_800AB010(lev, 0x10, lev->actionAnim_20, 0);
                }
            }
            else
            {
                SetLevantAnim_800AB010(lev, 0xE, 0xF, 0);
                lev->flags_0 &= ~0x800;
            }
            lev->flags_0 &= ~0x20;
        }
        if ((unsigned short)(lev->actionAnim_20 - 0x19) < 2 || lev->actionAnim_20 == 0x1C)
        {
            lev->hitRepeat_2A = 2;
        }
        else if ((unsigned short)(lev->actionAnim_20 - 7) < 2)
        {
            lev->hitRepeat_2A = 0x1E;
        }
        else
        {
            lev->hitRepeat_2A = 0;
        }
        break;
    case 14:
        if (lev->frame_10 == GetLevantAnimEventFrameCur_800AB170(lev->anim_1C))
        {
            SetModelFtg_80025B5C(lev->model_40, 2, 0x17);
            SetModelFtg_80025B5C(lev->model_40, 7, 0x19);
        }
        if (lev->frame_10 == GetLevantAnimLastFrame_800AC8BC(lev->anim_1C, GetLevantAnimSet_800AC474(lev->anim_1C)))
        {
            SetLevantAnim_800AB010(lev, 0x10, lev->actionAnim_20, 0);
        }
        break;
    case 16:
        RunLevantActionCues_800ABDF0(lev);
        if (lev->anim_1C == 0x13)
        {
            lev->flags_0 = (lev->flags_0 & ~1) | 0x800;
            SetLevantAnim_800AB010(lev, 0x14, 0x13, 0);
        }
        else if (lev->anim_1C == 0x18)
        {
            lev->flags_0 = (lev->flags_0 & ~1) | 0x800;
            SetLevantAnim_800AB010(lev, 0x14, 0x18, 0);
        }
        else
        {
            lev->action_8 = 0xF;
        }
        PlayLevantActionEffect_800AA430(lev);
        break;
    case 15:
        lev->flags_0 &= ~0x800;
        RunLevantActionCues_800ABDF0(lev);
        if (lev->anim_1C == 0x19 || lev->anim_1C == 7 || lev->anim_1C == 0x1A || lev->anim_1C == 0x1C || lev->anim_1C == 8)
        {
            if ((unsigned int)lev->frame_10 >= (unsigned short)GetLevantAnimLoopEnd_800AC878(lev->anim_1C, GetLevantAnimSet_800AC474(lev->anim_1C)))
            {
                if (effectOutcomeFlag_8008D780[0] == 1)
                {
                    lev->hitRepeat_2A = -1;
                }
                else if (--lev->hitRepeat_2A >= 0)
                {
                    lev->frame_10 = (unsigned short)GetLevantAnimLoopStart_800AC834(lev->anim_1C, GetLevantAnimSet_800AC474(lev->anim_1C));
                }
            }
        }
        if (lev->frame_10 == GetLevantAnimLastFrame_800AC8BC(lev->anim_1C, GetLevantAnimSet_800AC474(lev->anim_1C)))
        {
            animFlags = GetLevantAnimFlags_800AC900(lev->actionAnim_20, GetLevantAnimSet_800AC474(lev->actionAnim_20) & 1);
            if (animFlags == 0)
            {
                if (lev->flags_0 & 0x400)
                {
                    if (lev->anim_1C == 0x14)
                    {
                        SetLevantAnim_800AB010(lev, 10, -1, -1);
                    }
                    else
                    {
                        SetLevantAnim_800AB010(lev, 8, 0x14, 0);
                    }
                }
                else if (lev->flags_0 & 0x10000)
                {
                    if (lev->anim_1C == 0x16)
                    {
                        SetLevantAnim_800AB010(lev, 10, -1, -1);
                    }
                    else
                    {
                        SetLevantAnim_800AB010(lev, 8, 0x16, 0);
                    }
                }
                else
                {
                    SetLevantAnim_800AB010(lev, 10, 0xE, (unsigned short)GetLevantAnimLoopEnd_800AC878(0xE, GetLevantAnimSet_800AC474(0xE)));
                }
            }
            else if (lev->flags_0 & 0x1000000)
            {
                SetLevantAnim_800AB010(lev, 0x13, 10, 0);
            }
            else
            {
                SetLevantAnim_800AB010(lev, 9, 0xE, 0);
            }
            lev->flags_0 &= ~1;
        }
        break;
    case 17:
        if (AreLevantFilesLoaded_800AC768() == 1)
        {
            if (lev->flags_0 & 2)
            {
                SetLevantAnim_800AB010(lev, 0x12, 3, 0);
            }
            else
            {
                SetLevantAnim_800AB010(lev, 0x12, 0xF, 0);
            }
            lev->flags_0 &= ~0x800;
        }
        break;
    case 18:
        if (lev->frame_10 == GetLevantAnimEventFrameCur_800AB170(lev->anim_1C))
        {
            SetModelFtg_80025B5C(lev->model_40, 2, 0x17);
            SetModelFtg_80025B5C(lev->model_40, 7, 0x19);
            SetModelFtg_80025B5C(lev->model_40, 0xC, 0xC);
        }
        if ((unsigned int)lev->frame_10 >= GetLevantAnimLastFrame_800AC8BC(lev->anim_1C, GetLevantAnimSet_800AC474(lev->anim_1C)))
        {
            lev->flags_0 &= ~0x800;
            if (lev->flags_0 & 0x1000)
            {
                SetLevantAnim_800AB010(lev, 0x13, 10, 0);
            }
            else
            {
                ReturnLevantToIdle_800AA3F0(lev);
            }
        }
        break;
    case 19:
        if ((unsigned int)lev->frame_10 >= GetLevantAnimLastFrame_800AC8BC(lev->anim_1C, GetLevantAnimSet_800AC474(lev->anim_1C)))
        {
            ReturnLevantToIdle_800AA3F0(lev);
        }
        break;
    case 20:
        if (!(lev->flags_0 & 0x800))
        {
            ReturnLevantToIdle_800AA3F0(lev);
        }
        break;
    }
}

// PLDISP.C's assertion strings (after the jump table of UpdateLevantBattleAction_800AA51C)
const char aAssertionFailed_800A07E0[] = "Assertion failed: file \"%s\", line %d\n";
const char aPLDISPC_800A0808[] = "PLDISP.C";


void UpdateLevantScriptAnim_800AACF8(GameLevantActor* lev)
{
    switch (lev->action_8)
    {
    case 0x17:
        if (lev->flags_0 & 0x20)
        {
            if (lev->flags_0 & 0x100000)
            {
                SetLevantAnim_800AB010(lev, 0x18, lev->actionAnim_20, (unsigned short)GetLevantAnimLoopStart_800AC834(lev->actionAnim_20, GetLevantAnimSet_800AC474(lev->actionAnim_20)));
            }
            else
            {
                SetLevantAnim_800AB010(lev, 0x18, lev->actionAnim_20, 0);
            }
            lev->flags_0 &= ~0x8000;
            if (lev->nextAnim_24 >= 0)
            {
                lev->flags_0 &= ~0x800;
            }
        }
        break;
    case 0x18:
        if (lev->flags_0 & 0x800000)
        {
            if (lev->flags_0 & 0x800)
            {
                lev->flags_0 &= ~0x800000;
                lev->frame_10 = (unsigned short)GetLevantAnimLoopStart_800AC834(lev->anim_1C, GetLevantAnimSet_800AC474(lev->anim_1C));
                lev->flags_0 &= ~0x8000;
            }
            else
            {
                lev->flags_0 &= ~0x800000;
                lev->frame_10 = (unsigned short)GetLevantAnimLastFrame_800AC8BC(lev->anim_1C, GetLevantAnimSet_800AC474(lev->anim_1C));
            }
        }
        if (lev->frame_10 == (unsigned short)GetLevantAnimLastFrame_800AC8BC(lev->anim_1C, GetLevantAnimSet_800AC474(lev->anim_1C)))
        {
            if (lev->nextAnim_24 < 0)
            {
                SetLevantAnim_800AB010(lev, 0, 3, 0);
                lev->mode_C = 0;
            }
            else
            {
                if (lev->flags_0 & 0x100000)
                {
                    SetLevantAnim_800AB010(lev, -1, lev->nextAnim_24, (unsigned short)GetLevantAnimLoopStart_800AC834(lev->nextAnim_24, GetLevantAnimSet_800AC474(lev->nextAnim_24)));
                }
                else
                {
                    SetLevantAnim_800AB010(lev, -1, lev->nextAnim_24, 0);
                }
                lev->nextAnim_24 = -1;
                lev->actionAnim_20 = lev->queuedAnim_22;
                lev->flags_0 |= 0x800;
            }
        }
        if (lev->actionAnim_20 != (short)lev->queuedAnim_22)
        {
            if (LoadLevantAnimById_800AC604((short)lev->queuedAnim_22, 0) == 0)
            {
                lev->action_8 = 0x17;
                lev->actionAnim_20 = lev->queuedAnim_22;
            }
            else
            {
                printf(aAssertionFailed_800A07E0, aPLDISPC_800A0808, 0x44e);
                exit(1);
            }
        }
        break;
    }
}

void UpdateLevantActionState_800AAF58(GameLevantActor* lev)
{
    switch ((unsigned)lev->mode_C)
    {
    case 0:
        UpdateLevantFieldAnim_800AA25C(lev);
        break;
    case 1:
        UpdateLevantBattleAction_800AA51C(lev);
        break;
    case 2:
        UpdateLevantScriptAnim_800AACF8(lev);
        break;
    case 3:
        UpdateLevantQueuedAnim_800AC02C(lev);
        break;
    default:
        break;
    }
}

int IsLevantAnimLoadedOrFree_800AAFD8(int anim)
{
    if (IsLevantAnimLoaded_800AC518(anim))
        return 1;
    FreeLevantAnimById_800AC6A8(anim);
    return 0;
}

void SetLevantAnim_800AB010(GameLevantActor* lev, int action, int anim, int frame)
{
    if (frame == 0)
        frame = (short)GetLevantAnimStartFrame_800AC7F0(anim, GetLevantAnimSet_800AC474(anim));
    if (lev->action_8 == action && lev->anim_1C == anim)
        return;
    lev->idleTimer_28 = 0;
    if (anim < 0)
    {
        lev->action_8 = action;
    }
    else if (action < 0)
    {
        unsigned short prevAnim = lev->anim_1C;
        int prevFrame = lev->frame_10;
        lev->anim_1C = anim;
        lev->frame_10 = frame;
        lev->blend_26 = 0;
        lev->prevAnim_1E = prevAnim;
        lev->blendFrame_14 = prevFrame;
    }
    else
    {
        unsigned short prevAnim = lev->anim_1C;
        int prevFrame = lev->frame_10;
        lev->action_8 = action;
        lev->anim_1C = anim;
        lev->frame_10 = frame;
        lev->blend_26 = 0;
        lev->prevAnim_1E = prevAnim;
        lev->blendFrame_14 = prevFrame;
    }
    if (lev->prevAnim_1E != lev->anim_1C)
    {
        lev->flags_0 |= 8;
        if (IsLevantAnimLoadedOrFree_800AAFD8(lev->prevAnim_1E) == 1)
            lev->flags_0 |= 0x10;
    }
}

void StartLevantFadeIn_800AB114(GameLevantFade* lev)
{
    lev->fade_30 = 0x1000;
    lev->flags_0 = (lev->flags_0 | 4) & ~2;
}

void StartLevantFadeOut_800AB134(GameLevantFade* lev)
{
    lev->fade_30 = 0;
    lev->flags_0 = (lev->flags_0 | 2) & ~4;
}

void ClearLevantFade_800AB150(GameLevantFade* lev)
{
    lev->fade_30 = 0;
    lev->flags_0 &= ~4;
    lev->flags_0 &= ~2;
}

unsigned short GetLevantAnimEventFrameCur_800AB170(int anim)
{
    return GetLevantAnimEventFrame_800AC944(anim, GetLevantAnimSet_800AC474(anim));
}

void ContinueLevantAnim_800AB1A4(int loop)
{
    GameLevantActor* lev = gameTask_8008B4A4->buffer_24;
    lev->flags_0 |= 0x20;
    if (loop == 1)
    {
        lev->flags_0 |= 0x800;
        lev->flags_0 &= ~0x8000;
    }
}

int StartLevantActorAction_800AB1EC(int anim, int playEffect, int targets, int arg)
{
    GameLevantActor* lev = gameTask_8008B4A4->buffer_24;
    if (!(lev->flags_0 & 1))
    {
        if (playEffect == 1)
            lev->flags_0 |= 0x200;
        else
            lev->flags_0 &= ~0x200;
        lev->actionAnim_20 = anim;
        lev->targets_38 = targets;
        lev->arg_34 = arg;
        lev->flags_0 &= ~0x2000;
        lev->flags_0 |= 1;
        lev->flags_0 &= ~0x20;
        return 1;
    }
    return 0;
}

void SetLevantDefending_800AB264()
{
    gameTask_8008B4A4->buffer_24->flags_0 |= 0x400;
}

void ClearLevantDefending_800AB28C()
{
    gameTask_8008B4A4->buffer_24->flags_0 &= ~0x400;
}

void sub_800AB2B4()
{
    gameTask_8008B4A4->buffer_24->flags_0 |= 0x10000;
}

void sub_800AB2DC()
{
    gameTask_8008B4A4->buffer_24->flags_0 &= ~0x10000;
}

int IsLevantActorIdle_800AB304()
{
    return (gameTask_8008B4A4->buffer_24->flags_0 & 1) ^ 1;
}

int IsLevantActionReady_800AB32C()
{
    return gameTask_8008B4A4->buffer_24->action_8 == 0xD;
}

int IsLevantDefending_800AB354()
{
    unsigned flag = gameTask_8008B4A4->buffer_24->flags_0 & 0x400;
    return flag != 0;
}

int SetLevantMoveCmd_800AB37C(int cmd)
{
    gameTask_8008B4A4->buffer_24->moveCmd_4 = cmd;
    return 1;
}

int GetLevantMoveCmd_800AB39C()
{
    return gameTask_8008B4A4->buffer_24->moveCmd_4;
}

void ResetLevantIdleTimer_800AB3BC()
{
    gameTask_8008B4A4->buffer_24->idleTimer_28 = 0;
}

void EnterLevantActorBattle_800AB3D4()
{
    GameLevantActor* lev = gameTask_8008B4A4->buffer_24;
    if (!(lev->flags_0 & 0x100))
    {
        lev->flags_0 |= 0x4100;
        lev->basePos_60.a = levantPos_8008BD18.pos.x;
        lev->basePos_60.b = levantPos_8008BD18.pos.y;
        lev->basePos_60.c = levantPos_8008BD18.pos.z;
        lev->savedPos_54.a = lev->pos_48.a;
        lev->savedPos_54.b = lev->pos_48.b;
        lev->savedPos_54.c = lev->pos_48.c;
    }
}

void ExitLevantActorBattle_800AB444(int victoryPose)
{
    GameLevantActor* lev = gameTask_8008B4A4->buffer_24;
    if (lev->flags_0 & 0x100)
    {
        if (victoryPose == 1)
            lev->flags_0 |= 0x1000;
        else
            lev->flags_0 &= ~0x1000;
        lev->flags_0 &= ~0x100;
        levantPos_8008BD18.pos.x = lev->basePos_60.a;
        levantPos_8008BD18.pos.y = lev->basePos_60.b;
        levantPos_8008BD18.pos.z = lev->basePos_60.c;
        lev->pos_48.a = lev->basePos_60.a;
        lev->pos_48.b = lev->basePos_60.b;
        lev->pos_48.c = lev->basePos_60.c;
    }
}

short GetLevantActionEndFrame_800AB4D8(int anim)
{
    int loopStart = (unsigned short)GetLevantAnimLoopStart_800AC834(anim, GetLevantAnimSet_800AC474(anim));
    int loopEnd = (unsigned short)GetLevantAnimLoopEnd_800AC878(anim, GetLevantAnimSet_800AC474(anim));
    int stanceEnd;
    switch ((unsigned)anim)
    {
    case 25:
    case 26:
    case 28:
        return GetLevantAnimLastFrame_800AC8BC(anim, GetLevantAnimSet_800AC474(anim)) + (loopEnd - loopStart) * 2;
    case 7:
    case 8:
        stanceEnd = GetLevantAnimLastFrame_800AC8BC(14, GetLevantAnimSet_800AC474(14));
        return stanceEnd + GetLevantAnimLastFrame_800AC8BC(anim, GetLevantAnimSet_800AC474(anim)) + (loopEnd - loopStart) * 30;
    }
    return GetLevantAnimLastFrame_800AC8BC(anim, GetLevantAnimSet_800AC474(anim));
}

short GetLevantAnimLoopStartCur_800AB5F8(int anim)
{
    return GetLevantAnimLoopStart_800AC834(anim, GetLevantAnimSet_800AC474(anim));
}

short GetLevantActionLoopEndFrame_800AB630(int anim)
{
    int loopStart = (unsigned short)GetLevantAnimLoopStart_800AC834(anim, GetLevantAnimSet_800AC474(anim));
    int loopEnd = (unsigned short)GetLevantAnimLoopEnd_800AC878(anim, GetLevantAnimSet_800AC474(anim));
    int stanceEnd;
    switch ((unsigned)anim)
    {
    case 25:
    case 26:
    case 28:
        return GetLevantAnimLoopEnd_800AC878(anim, GetLevantAnimSet_800AC474(anim)) + (loopEnd - loopStart) * 2;
    case 7:
    case 8:
        stanceEnd = GetLevantAnimLastFrame_800AC8BC(14, GetLevantAnimSet_800AC474(14));
        return stanceEnd + GetLevantAnimLoopEnd_800AC878(anim, GetLevantAnimSet_800AC474(anim)) + (loopEnd - loopStart) * 30;
    }
    return GetLevantAnimLoopEnd_800AC878(anim, GetLevantAnimSet_800AC474(anim));
}

short GetLevantActionHitFrame_800AB750(int anim)
{
    int loopStart = (unsigned short)GetLevantAnimLoopStart_800AC834(anim, GetLevantAnimSet_800AC474(anim));
    int loopEnd = (unsigned short)GetLevantAnimLoopEnd_800AC878(anim, GetLevantAnimSet_800AC474(anim));
    short frame;
    switch ((unsigned)anim)
    {
    case 25:
    case 26:
    case 28:
        return GetLevantAnimEventFrameCur_800AB170(anim) + (loopEnd - loopStart) * 2;
    case 7:
        frame = GetLevantAnimLastFrame_800AC8BC(14, GetLevantAnimSet_800AC474(14));
        frame = frame + GetLevantAnimEventFrameCur_800AB170(anim) + 0x4c;
        return frame;
    case 8:
        frame = GetLevantAnimLastFrame_800AC8BC(14, GetLevantAnimSet_800AC474(14));
        frame = frame + GetLevantAnimEventFrameCur_800AB170(anim);
        return frame;
    }
    return GetLevantAnimEventFrameCur_800AB170(anim);
}

int IsLevantActionFinished_800AB85C()
{
    unsigned flag = gameTask_8008B4A4->buffer_24->flags_0 & 0x2000;
    return flag != 0;
}

void ClearLevantBattleStance_800AB884()
{
    gameTask_8008B4A4->buffer_24->flags_0 &= ~0x4000;
}

void ResetLevantActorToIdle_800AB8AC()
{
    ResetLevantActor_800A9414(gameTask_8008B4A4->buffer_24, 0, 3);
}

void UpdateLevantActorModel_800AB8DC()
{
    GameLevantActor* lev = gameTask_8008B4A4->buffer_24;
    lev->model_40 = GetLevantModel_800AC38C();
}

void StopLevantAnimLoop_800AB910()
{
    gameTask_8008B4A4->buffer_24->flags_0 &= ~0x800;
}

int IsLevantAnimLooped_800AB938()
{
    return ((unsigned char*)gameTask_8008B4A4->buffer_24)[1] >> 7;
}

int IsLevantIdleAnim_800AB958()
{
    return (unsigned)gameTask_8008B4A4->buffer_24->action_8 < 2;
}

void QueueLevantAnim_800AB978(short anim)
{
    GameLevantActor* lev = gameTask_8008B4A4->buffer_24;
    lev->nextAnim_24 = -1;
    lev->queuedAnim_22 = anim;
    lev->flags_0 &= ~0x20;
}

void PlayLevantScriptAnim_800AB9A8(int anim, int nextAnim, int blend)
{
    GameLevantActor* lev = gameTask_8008B4A4->buffer_24;
    if (LoadLevantAnimById_800AC604(anim, 0) == 0 && (nextAnim < 0 || LoadLevantAnimById_800AC604(nextAnim, 0) == 0))
    {
        SetLevantAnim_800AB010(lev, 0x17, anim, 0);
        lev->mode_C = 2;
        if (blend)
            lev->flags_0 |= 0x10;
        else
            lev->flags_0 &= ~0x10;
    }
    else
    {
        printf(aAssertionFailed_800A07E0, aPLDISPC_800A0808, 0x6B9);
        exit(1);
    }
    lev->queuedAnim_22 = anim;
    lev->actionAnim_20 = anim;
    lev->nextAnim_24 = nextAnim;
    lev->flags_0 &= ~0x20;
    lev->flags_0 &= ~1;
}

void SetLevantPath_800ABAA4(G2Path* path)
{
    GameLevantActor* lev = gameTask_8008B4A4->buffer_24;
    lev->path_78 = path;
    lev->pathStep_7C = 0;
    lev->flags_0 |= 0x400000;
}

void EndLevantPath_800ABAD4()
{
    GameLevantActor* lev = gameTask_8008B4A4->buffer_24;
    lev->flags_0 &= ~0x400000;
    SetLevantRootMotionMode_800ABC78(0);
    lev->flags_0 = (lev->flags_0 & ~0x800) | 8;
    SetLevantAnim_800AB010(lev, 0, 3, 0);
    lev->mode_C = 0;
}

int IsLevantPathDone_800ABB44()
{
    return ((gameTask_8008B4A4->buffer_24->flags_0 >> 22) ^ 1) & 1;
}

int IsLevantScriptAnimWaiting_800ABB70()
{
    return gameTask_8008B4A4->buffer_24->action_8 == 0x17;
}

void sub_800ABB98(int fromLoop)
{
    GameLevantActor* lev = gameTask_8008B4A4->buffer_24;
    if (fromLoop == 1)
        lev->flags_0 |= 0x100000;
    else
        lev->flags_0 &= ~0x100000;
}

void SetLevantVisible_800ABBD8(int visible)
{
    GameLevantActor* lev = gameTask_8008B4A4->buffer_24;
    if (visible)
    {
        lev->flags_0 &= ~0x20000;
        ClearLevantFade_800AB150((GameLevantFade*)lev);
    }
    else
    {
        lev->flags_0 |= 0x20000;
    }
}

void SetLevantMapCollision_800ABC34(int collide)
{
    GameLevantActor* lev = gameTask_8008B4A4->buffer_24;
    if (collide)
        lev->flags_0 &= ~0x40000;
    else
        lev->flags_0 |= 0x40000;
}

void SetLevantRootMotionMode_800ABC78(int on)
{
    GameLevantActor* lev = gameTask_8008B4A4->buffer_24;
    if (on)
    {
        lev->flags_0 |= 0x80000;
        lev->basePos_60.a = levantPos_8008BD18.pos.x;
        lev->basePos_60.b = levantPos_8008BD18.pos.y;
        lev->basePos_60.c = levantPos_8008BD18.pos.z;
        lev->savedPos_54.a = lev->pos_48.a;
        lev->savedPos_54.b = lev->pos_48.b;
        lev->savedPos_54.c = lev->pos_48.c;
    }
    else
    {
        lev->flags_0 &= ~0x80000;
    }
}

void RequestLevantActionEffect_800ABCF4(GameLevantActor* lev)
{
    if (lev->actionAnim_20 == 0x19)
    {
        lev->effect_2C = GetMagicEffect_8001AC8C(lev->arg_34);
        RequestEffect_800148F4(lev->effect_2C);
    }
    else if ((unsigned short)(lev->actionAnim_20 - 7) < 2)
    {
        lev->effect_2C = 0x25;
        RequestEffect_800148F4(0x25);
        GetSealResultFlags_80013358(lev->arg_34);
        effectOutcomeFlag_8008D780[1] = GetSealResultFlags_80013358(lev->arg_34);
    }
    else if (lev->actionAnim_20 == 0x1A)
    {
        lev->effect_2C = 0x39;
        RequestEffect_800148F4(lev->effect_2C);
    }
    else if (lev->actionAnim_20 == 0x1C)
    {
        lev->effect_2C = 0x3A;
        RequestEffect_800148F4(lev->effect_2C);
    }
    else if (lev->actionAnim_20 == 0x10)
    {
        lev->effect_2C = GetWeaponEffect_800189F8();
        RequestEffect_800148F4(lev->effect_2C);
    }
    else if (lev->actionAnim_20 == 0x1D)
    {
        lev->effect_2C = ((int (*)(int))GetItemEffect_8001CDCC)(lev->arg_34);
        RequestEffect_800148F4(lev->effect_2C);
    }
}

void RunLevantActionCues_800ABDF0(GameLevantActor* lev)
{
    if (lev->anim_1C == 0x1A)
    {
        if (lev->frame_10 == (unsigned short)GetLevantAnimLoopStart_800AC834(lev->anim_1C, GetLevantAnimSet_800AC474(0x1A)))
            StartLevantFadeOut_800AB134((GameLevantFade*)lev);
    }
    if (lev->anim_1C == 0x1D)
    {
        if (lev->frame_10 == (unsigned short)GetLevantAnimEventFrameCur_800AB170(0x1D))
            PlaySfx_80031494(0x44);
        if (lev->frame_10 == (unsigned short)GetLevantAnimEventFrameCur_800AB170(lev->anim_1C) - 10)
            PlaySeqSlot_80031160(0x1D, 1);
    }
    if (lev->anim_1C == 0x1C && lev->frame_10 == 2)
        StartLevantFadeIn_800AB114((GameLevantFade*)lev);
}

void SetLevantStatusTint_800ABECC()
{
    G2V12* tint = &dword_8007A164;
    unsigned int status = dword_8008BD38;
    if (status & 0x200)
    {
        if (status & 1)
            tint = &statusTintPoisonLevel7_8007A14C;
        else
            tint = &statusTintLevel7_8007A0EC;
    }
    else if (status & 0x100)
    {
        if (status & 1)
            tint = &statusTintPoisonLevel6_8007A140;
        else
            tint = &statusTintLevel6_8007A0E0;
    }
    else if (status & 0x80)
    {
        if (status & 1)
            tint = &statusTintPoisonLevel5_8007A134;
        else
            tint = &statusTintLevel5_8007A0D4;
    }
    else if (status & 0x40)
    {
        if (status & 1)
            tint = &statusTintPoisonLevel4_8007A128;
        else
            tint = &statusTintLevel4_8007A0C8;
    }
    else if (status & 0x20)
    {
        if (status & 1)
            tint = &statusTintPoisonLevel3_8007A11C;
        else
            tint = &statusTintLevel3_8007A0BC;
    }
    else if (status & 0x10)
    {
        if (status & 1)
            tint = &statusTintPoisonLevel2_8007A110;
        else
            tint = &statusTintLevel2_8007A0B0;
    }
    else if (status & 8)
    {
        if (status & 1)
            tint = &dword_8007A104;
        else
            tint = &statusTintLevel1_8007A0A4;
    }
    else if (status & 1)
    {
        tint = &statusTintPoison_8007A0F8;
    }
    TintVramImage_800292D0(&dword_8007DC80, &dword_8007DC88, tint);
}

void UpdateLevantQueuedAnim_800AC02C(GameLevantActor* lev)
{
    switch (lev->action_8)
    {
    case 0x15:
        if (lev->blend_26 >= 0x1000)
        {
            lev->flags_0 &= ~0x10;
            LoadLevantAnimById_800AC604(lev->actionAnim_20, 0);
            lev->action_8 = 0x16;
        }
        break;
    case 0x16:
        if (AreLevantFilesLoaded_800AC768() == 1)
        {
            lev->action_8 = 0x17;
        }
        break;
    case 0x17:
        if (lev->flags_0 & 0x20)
        {
            if (lev->flags_0 & 0x100000)
            {
                SetLevantAnim_800AB010(lev, 0x18, lev->actionAnim_20, (unsigned short)GetLevantAnimLoopStart_800AC834(lev->actionAnim_20, GetLevantAnimSet_800AC474(lev->actionAnim_20)));
            }
            else
            {
                SetLevantAnim_800AB010(lev, 0x18, lev->actionAnim_20, 0);
            }
            lev->flags_0 &= ~0x8000;
            if (lev->nextAnim_24 >= 0)
            {
                lev->flags_0 &= ~0x800;
            }
        }
        break;
    case 0x18:
        if (lev->frame_10 == (unsigned short)GetLevantAnimLastFrame_800AC8BC(lev->anim_1C, GetLevantAnimSet_800AC474(lev->anim_1C)))
        {
            if (lev->nextAnim_24 < 0)
            {
                SetLevantAnim_800AB010(lev, 0, 3, 0);
                lev->mode_C = 0;
                if (IsLevantAnimLoadedOrFree_800AAFD8(lev->actionAnim_20) == 1)
                {
                    lev->flags_0 |= 0x10;
                }
            }
            else
            {
                if (lev->flags_0 & 0x100000)
                {
                    SetLevantAnim_800AB010(lev, -1, lev->nextAnim_24, 0);
                }
                else
                {
                    SetLevantAnim_800AB010(lev, -1, lev->nextAnim_24, (unsigned short)GetLevantAnimLoopStart_800AC834(lev->nextAnim_24, GetLevantAnimSet_800AC474(lev->nextAnim_24)));
                }
                lev->actionAnim_20 = lev->queuedAnim_22;
                if (IsLevantAnimLoadedOrFree_800AAFD8(lev->actionAnim_20) == 1)
                {
                    lev->flags_0 |= 0x10;
                }
                lev->flags_0 |= 0x800;
            }
        }
        if (lev->actionAnim_20 != (short)lev->queuedAnim_22)
        {
            if (LoadLevantAnimById_800AC604((short)lev->queuedAnim_22, 0) == 0)
            {
                lev->actionAnim_20 = lev->queuedAnim_22;
                lev->action_8 = 0x17;
                if (IsLevantAnimLoadedOrFree_800AAFD8(lev->actionAnim_20) == 1)
                {
                    lev->flags_0 |= 0x10;
                }
            }
            else
            {
                SetLevantAnim_800AB010(lev, 0x19, 3, 0);
                lev->flags_0 |= 0x10;
            }
        }
        break;
    case 0x19:
        if (lev->blend_26 >= 0x1000)
        {
            lev->flags_0 &= ~0x10;
            IsLevantAnimLoadedOrFree_800AAFD8(lev->actionAnim_20);
            lev->actionAnim_20 = lev->queuedAnim_22;
            LoadLevantAnimById_800AC604(lev->actionAnim_20, 0);
            lev->action_8 = 0x16;
        }
        break;
    case 0x1a:
        break;
    }
}

void SkipLevantAnim_800AC318()
{
    gameTask_8008B4A4->buffer_24->flags_0 |= 0x800000;
}

void SetLevantLastCapture_800AC340(int on)
{
    GameLevantActor* lev = gameTask_8008B4A4->buffer_24;
    if (on)
        lev->flags_0 |= 0x1000000;
    else
        lev->flags_0 &= ~0x1000000;
}

void SetLevantHasArmor_800AC380(int has)
{
    dword_8008BDA0 = has;
}

Model* GetLevantModel_800AC38C()
{
    return dword_8007DC60->items_8;
}

void SetLevantWeaponKind_800AC3A4(short kind)
{
    word_8008BDA4 = kind;
}

void SetLevantOutfit_800AC3B0(int outfit)
{
    word_8008BDA6 = outfit;
    SetLevantHasArmor_800AC380(1);
}

char* sub_800AC3D8()
{
    return &dword_800B1DF8;
}

int GetLevantWeaponKind_800AC3E4()
{
    return word_8008BDA4;
}

int GetLevantModelId_800AC3F4()
{
    SaveData* sd = &saveData_8008B570;
    int model;
    if (sd->field_830)
    {
        model = GetArmorOutfit_8001D060(sd->levantStatus_7C8.equipment_1C[1]) + levantOutfitModelOffsets_800B11B8[sd->field_834];
    }
    else
    {
        model = levantBaseModels_800B116C[sd->field_834];
    }
    return model;
}

int GetLevantOutfit_800AC464()
{
    return word_8008BDA6;
}

int GetLevantAnimSet_800AC474(int anim)
{
    return levantAnimSets_800B11DC[GetLevantWeaponKind_800AC3E4()];
}

int GetLevantAnimFile_800AC4A8(int anim)
{
    GameLevantAnim* anims = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    return anims[GetLevantAnimIndex_800AC794(anim, levantAnimSets_800B11DC[GetLevantWeaponKind_800AC3E4()])].fileId_0;
}

int IsLevantAnimLoaded_800AC518(int anim)
{
    GameLevantAnim* anims = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    int idx = GetLevantAnimIndex_800AC794(anim, levantAnimSets_800B11DC[GetLevantWeaponKind_800AC3E4()]);
    if (anims[idx].resident_1)
        return 1;
    return IsAnimInModelAnimSet_80025924(dword_8007DC60->items_8, (short)GetLevantAnimFileId_800AC988(anim, levantAnimSets_800B11DC[GetLevantWeaponKind_800AC3E4()]));
}

int LoadLevantAnim_800AC5D0(int fileId, int resident)
{
    return LoadModelAnim_80025440(dword_8007DC60->items_8, fileId, resident) != 0;
}

int LoadLevantAnimById_800AC604(int anim, int resident)
{
    int set = levantAnimSets_800B11DC[GetLevantWeaponKind_800AC3E4()];
    return LoadModelAnim_80025440(dword_8007DC60->items_8, (short)GetLevantAnimFileId_800AC988(anim, set), resident) != 0;
}

void FreeLevantAnim_800AC678(int fileId)
{
    FreeModelAnim_8002556C(dword_8007DC60->items_8, fileId);
}

void FreeLevantAnimById_800AC6A8(int anim)
{
    int set = levantAnimSets_800B11DC[GetLevantWeaponKind_800AC3E4()];
    FreeModelAnim_8002556C(dword_8007DC60->items_8, (short)GetLevantAnimFileId_800AC988(anim, set));
}

void LoadLevantAnimSet_800AC708(int set, int flag)
{
    LoadModelAnimSet_80025780(dword_8007DC60->items_8, set, flag);
}

void FreeLevantAnimSet_800AC73C()
{
    FreeModelAnimSet_80025884(dword_8007DC60->items_8);
}

int AreLevantFilesLoaded_800AC768()
{
    return AreFileRequestsDone_80024DC4(dword_8007DC60->items_8);
}

int GetLevantAnimIndex_800AC794(int anim, int set)
{
    if ((unsigned)(anim - 0xE) >= 0x60)
        return anim;
    return anim + set * 16;
}

unsigned char* GetLevantAnimSetTable_800AC7B4(int set)
{
    return (unsigned char*)GetModelActorAnims_80024E38(dword_8007DC60->items_8) + ((set << 10) + 0x380);
}

short GetLevantAnimStartFrame_800AC7F0(int anim, int set)
{
    GameLevantAnim* anims;
    int idx = GetLevantAnimIndex_800AC794(anim, set);
    anims = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    return anims[idx].start_4;
}

short GetLevantAnimLoopStart_800AC834(int anim, int set)
{
    GameLevantAnim* anims;
    int idx = GetLevantAnimIndex_800AC794(anim, set);
    anims = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    return anims[idx].loopStart_6;
}

short GetLevantAnimLoopEnd_800AC878(int anim, int set)
{
    GameLevantAnim* anims;
    int idx = GetLevantAnimIndex_800AC794(anim, set);
    anims = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    return anims[idx].loopEnd_8;
}

unsigned short GetLevantAnimLastFrame_800AC8BC(int anim, int set)
{
    GameLevantAnim* anims;
    int idx = GetLevantAnimIndex_800AC794(anim, set);
    anims = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    return anims[idx].lastFrame_A;
}

int GetLevantAnimFlags_800AC900(int anim, int set)
{
    GameLevantAnim* anims;
    int idx = GetLevantAnimIndex_800AC794(anim, set);
    anims = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    return anims[idx].flags_3;
}

short GetLevantAnimEventFrame_800AC944(int anim, int set)
{
    GameLevantAnim* anims;
    int idx = GetLevantAnimIndex_800AC794(anim, set);
    anims = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    return anims[idx].hitTimes_C[0].start_0;
}

unsigned char GetLevantAnimFileId_800AC988(int anim, int set)
{
    GameLevantAnim* anims;
    int idx = GetLevantAnimIndex_800AC794(anim, set);
    anims = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    return anims[idx].fileId_0;
}

HitTimes* GetLevantAnimHitFrames_800AC9CC(int anim)
{
    GameLevantAnim* anims;
    int idx = GetLevantAnimIndex_800AC794(anim, levantAnimSets_800B11DC[GetLevantWeaponKind_800AC3E4()]);
    anims = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    return anims[idx].hitTimes_C;
}

int* sub_800ACA38(int anim)
{
    GameLevantAnim* anims;
    int idx = GetLevantAnimIndex_800AC794(anim, levantAnimSets_800B11DC[GetLevantWeaponKind_800AC3E4()]);
    anims = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    return &anims[idx].f34;
}

void LevantModelTaskInit_800ACAA4(int* task, int* work)
{
    SaveData* sd = &saveData_8008B570;
    work[0] = 0;
    work[1] = 0;
    work[2] = -1;
    work[3] = -1;
    work[4] = -1;
    work[5] = -1;
    work[6] = -1;
    work[7] = -1;
    work[8] = -1;
    work[9] = 0;
    SetLevantHasArmor_800AC380(sd->levantStatus_7C8.equipment_1C[1] != 0xFF);
    SetLevantWeaponKind_800AC3A4(GetWeaponData_8001CF84(sd->levantStatus_7C8.equipment_1C[0])->kind_2);
    PoolInit_8003FF1C(&levantPool_800B1DD0, 0x2BF20);
    LevantModelTask_800ACB64(task, work);
    task[2] = (int)LevantModelTask_800ACB64;
}

// Matched
void LevantModelTask_800ACB64(int* task, void* buf)
{
    int more = 1;
    GameLevantModelWork* work = buf;
    Model* model;
    do
    {
        switch (work->state)
        {
        case 0:
            if (work->model_8 != saveData_8008B570.field_830)
            {
                work->f10 = -1;
                work->flags |= 0xd;
                SetLevantWeaponKind_800AC3A4(saveData_8008B570.field_834);
            }
            if (work->f10 != saveData_8008B570.field_834 || work->f18 != saveData_8008B570.field_836)
            {
                work->flags |= 0x16;
                FreeLevantAnimSetAnims_800ACF3C(work);
            }
            if (work->flags == 0)
            {
                more = 0;
            }
            else
            {
                PoolSetInited_80040148((int*)&levantPool_800B1DD0, 1);
                work->state = 1;
            }
            break;
        case 1:
            if (work->flags & 1)
            {
                if (dword_8007DC60)
                {
                    FreeModelList_80024BB0(&dword_8007DC60);
                }
                InitModelList_80024ADC(&dword_8007DC60, dword_8007DC6C, (int)&levantPool_800B1DD0);
                LoadModel_80025200(dword_8007DC60, levantModelIds_800B1164[saveData_8008B570.field_830], 0, 2, 1);
                work->prevModel_C = work->model_8;
                work->model_8 = saveData_8008B570.field_830;
                work->flags &= ~1;
            }
            else if (work->flags & 2)
            {
                model = AcquireModel_80024D70(dword_8007DC60, levantModelIds_800B1164[saveData_8008B570.field_830]);
                LoadModelAltFtgs_80025974(model, GetLevantModelId_800AC3F4(), 1);
                work->weaponKind_14 = GetLevantWeaponKind_800AC3E4();
                work->f10 = saveData_8008B570.field_834;
                work->outfit_1C = GetLevantOutfit_800AC464();
                work->f18 = saveData_8008B570.field_836;
                work->flags &= ~2;
            }
            else if (work->flags & 4)
            {
                LoadLevantAnimSetAnims_800ACFB8(work);
                work->flags &= ~4;
            }
            BeginFade_8001C260();
            eventDispatchHalt_8008B540 = 1;
            ClearOTagRAll_8001B260();
            work->state = 2;
            break;
        case 2:
            if (AreFileRequestsDone_80024DC4(dword_8007DC60->items_8) == 1)
            {
                work->state = 3;
            }
            else
            {
                more = 0;
                eventDispatchHalt_8008B540 = 1;
            }
            break;
        case 3:
            if ((work->flags & 9) == 8)
            {
                model = AcquireModel_80024D70(dword_8007DC60, levantModelIds_800B1164[saveData_8008B570.field_830]);
                SaveModelFtgs_80024FFC(model, levantSavedFtgIds_800B11CC);
                work->flags &= ~8;
            }
            if ((work->flags & 0x12) == 0x10)
            {
                model = AcquireModel_80024D70(dword_8007DC60, levantModelIds_800B1164[saveData_8008B570.field_830]);
                ApplyModelFtgSwaps_80025C38(model, (((unsigned)unknownFlags_8008D678 >> 24) ^ 1) & 1);
                work->flags &= ~0x10;
            }
            if (work->flags == 0)
            {
                more = 0;
                UpdateLevantActorModel_800AB8DC();
                ClearOTagRAll_8001B260();
                EndFade_8001C290();
            }
            PoolSetInited_80040148((int*)&levantPool_800B1DD0, 0);
            work->state = 0;
            break;
        }
    } while (more);
}

void LevantModelTaskExit_800ACF0C()
{
    FreeModelList_80024BB0(&dword_8007DC60);
    PoolDestroy_8003FF7C(&levantPool_800B1DD0);
}

void FreeLevantAnimSetAnims_800ACF3C(GameLevantModelWork* work)
{
    unsigned char* ent;
    int i;
    if (work->weaponKind_14 >= 0)
    {
        ent = GetLevantAnimSetTable_800AC7B4(levantAnimSets_800B11DC[work->weaponKind_14]);
        for (i = 0; i < 16; i++, ent += 0x40)
        {
            if (ent[1])
                FreeLevantAnim_800AC678(ent[0]);
        }
    }
}

void LoadLevantAnimSetAnims_800ACFB8()
{
    unsigned char* ent = GetLevantAnimSetTable_800AC7B4(levantAnimSets_800B11DC[GetLevantWeaponKind_800AC3E4()]);
    int i;
    for (i = 0; i < 16; i++, ent += 0x40)
    {
        if (ent[1])
            LoadLevantAnim_800AC5D0(ent[0], 1);
    }
}

int GetMoney_800AD02C()
{
    int yan = playerYan_8008B594.yan_0;
    if (yan > 9999999)
        yan = 9999999;
    return yan;
}

int AddMoney_800AD058(int amount)
{
    SaveData* sd = &saveData_8008B570;
    int yan;
    if (sd->inv_24.yan_0 <= 9999998)
    {
        yan = sd->inv_24.yan_0 + amount;
        if (yan <= 9999998)
            sd->inv_24.yan_0 = yan;
        else
            sd->inv_24.yan_0 = 9999999;
        return 1;
    }
    return 0;
}

int SpendMoney_800AD0A4(int amount)
{
    SaveData* sd = &saveData_8008B570;
    if (sd->inv_24.yan_0 >= amount)
    {
        sd->inv_24.yan_0 -= amount;
        return 1;
    }
    return 0;
}

int TestEventFlag_800AD0D4(unsigned flag)
{
    return (playerYan_8008B594.bits_290[flag >> 3] >> (flag & 7)) & 1;
}

void SetEventFlag_800AD0F8(unsigned flag)
{
    playerYan_8008B594.bits_290[flag >> 3] |= 1 << (flag & 7);
}

void ClearEventFlag_800AD124(unsigned flag)
{
    playerYan_8008B594.bits_290[flag >> 3] &= ~(1 << (flag & 7));
}

int GetEventVar_800AD154(int var)
{
    return playerYan_8008B594.vars_2A3[var];
}

int SetEventVar_800AD16C(int var, int value)
{
    playerYan_8008B594.vars_2A3[var] = value;
    return value;
}

int AddInventory_800AD184(int id, int count, int table)
{
    InvSlot* slot = FindInventorySlotForAdd_800AD4D8(id, count, table);
    if (slot && id != 0xFF)
    {
        slot->id = id;
        slot->count += count;
        return 1;
    }
    return 0;
}

int RemoveInventory_800AD1E0(int id, int count, int table)
{
    InvSlot* slot = FindInventorySlot_800AD58C(id, table);
    if (slot)
    {
        if (CanRemoveInventoryCount_800AD67C(slot->count, count))
        {
            slot->count -= count;
            if (slot->count == 0)
                slot->id = 0xFF;
            return 1;
        }
    }
    return 0;
}

int GetInventoryCount_800AD254(int id, int table)
{
    InvSlot* slot = FindInventorySlot_800AD58C(id, table);
    if (slot)
        return slot->count;
    return 0;
}

int GetInventorySlotId_800AD288(int slot, int table)
{
    InvSlot* slots = GetInventoryTable_800AD604(table);
    if (slots)
        return slots[slot].id;
    return 0xFF;
}

int GetInventorySlotCount_800AD2C8(int slot, int table)
{
    InvSlot* slots = GetInventoryTable_800AD604(table);
    if (slots)
        return slots[slot].count;
    return 0;
}

int GetLastInventorySlot_800AD308(int table)
{
    InvSlot* slots = GetInventoryTable_800AD604(table);
    int size = GetInventorySize_800AD374(table);
    int i;
    if (slots)
    {
        for (i = size - 1; i > 0; i--)
        {
            if (slots[i].id != 0xFF)
                return i;
        }
    }
    return 0;
}

int GetInventorySize_800AD374(int table)
{
    int size;
    unsigned idx = table;
    size = 0;
    if (idx < 4)
        goto L;
    if (idx == 4)
    {
    L:
        size = 0x40;
    }
    return size;
}

int IsInventory4NonEmpty_800AD398()
{
    int count;
    if (GetLastInventorySlot_800AD308(4) > 0)
        return 1;
    if (GetInventorySlotId_800AD288(0, 4) != 0xFF)
    {
        count = GetInventorySlotCount_800AD2C8(0, 4);
        if (count)
            return 1;
    }
    return 0;
}

void CompactInventory_800AD3F0(int table)
{
    unsigned char tmp[2];
    int size = GetInventorySize_800AD374(table);
    InvSlot* tbl = GetInventoryTable_800AD604(table);
    short cnt = 0;
    short i;
    InvSlot* slot;
    for (i = 0; i < size; i++)
    {
        slot = FindInventorySlot_800AD58C(i, table);
        if (slot)
        {
            MemCopy_800403E8(tmp, &tbl[cnt], 2);
            MemCopy_800403E8(&tbl[cnt], slot, 2);
            MemCopy_800403E8(slot, tmp, 2);
            cnt++;
        }
    }
}

InvSlot* FindInventorySlotForAdd_800AD4D8(int id, int count, int table)
{
    InvSlot* slot = FindInventorySlot_800AD58C(id, table);
    if (slot)
    {
        if (CanAddInventoryCount_800AD670(slot->count, count))
        {
            if ((unsigned)(table - 1) < 3 && id == GetEquippedId_800AD990(table - 1))
            {
                if (!(slot->count + count < 0x14))
                    return 0;
            }
            return slot;
        }
        return 0;
    }
    return FindInventorySlot_800AD58C(0xFF, table);
}

InvSlot* FindInventorySlot_800AD58C(int id, int table)
{
    int size = GetInventorySize_800AD374(table);
    InvSlot* slots = GetInventoryTable_800AD604(table);
    int i;
    if (slots != 0)
    {
        for (i = 0; i < size; i++)
        {
            if (id == slots[i].id)
                return &slots[i];
        }
    }
    return 0;
}

InvSlot* GetInventoryTable_800AD604(int table)
{
    switch ((unsigned)table)
    {
    case 0:
        return saveData_8008B570.inv_24.inventory_4[0];
    case 1:
        return saveData_8008B570.inv_24.inventory_4[1];
    case 2:
        return saveData_8008B570.inv_24.inventory_4[2];
    case 3:
        return saveData_8008B570.inv_24.inventory_4[3];
    case 4:
        return saveData_8008B570.inv_24.inventory_4[4];
    }
    return 0;
}

int CanAddInventoryCount_800AD670(int have, int count)
{
    return have + count < 0x15;
}

int CanRemoveInventoryCount_800AD67C(int have, int count)
{
    return (have - count) >= 0;
}

int SetValuableFlag_800AD68C(int valuable)
{
    SaveInventory* inv = &playerYan_8008B594;
    if (valuable < 0x40)
    {
        inv->flags_288[valuable / 32] |= 1 << (valuable % 32);
        return 1;
    }
    return 0;
}

void ClearValuableFlag_800AD6E4(int valuable)
{
    SaveInventory* inv = &playerYan_8008B594;
    if (valuable < 0x40)
        inv->flags_288[valuable / 32] &= ~(1 << (valuable % 32));
}

int TestValuableFlag_800AD73C(int valuable)
{
    SaveInventory* inv = &playerYan_8008B594;
    if (valuable < 0x40)
    {
        if (inv->flags_288[valuable / 32] & (1 << (valuable % 32)))
            return 1;
    }
    return 0;
}

int CountValuables_800AD79C()
{
    short i;
    int count = 0;
    for (i = 0; i < 0x26; i++)
    {
        if (TestValuableFlag_800AD73C(i))
            count++;
    }
    return count;
}

int GetNthValuable_800AD7F8(int nth)
{
    short i;
    int count = 0;
    for (i = 0; i < 0x26; i++)
    {
        if (TestValuableFlag_800AD73C(i))
        {
            if (nth == (short)count++)
                return i;
        }
    }
    return 0x26;
}

int GetFreeCocoonSlots_800AD888()
{
    int slots = 12 - CountCocoonsAndMinions_800AD8BC();
    if (slots < 0)
        slots = 0;
    return slots;
}

int CountCocoonsAndMinions_800AD8BC()
{
    return levantEmptyCocoons_8008B818 + CountMinions_80010548(0);
}

int GetEmptyCocoons_800AD8E4()
{
    return levantEmptyCocoons_8008B818;
}

int AddEmptyCocoons_800AD8F4(int count)
{
    int ret = 1;
    int total = GetEmptyCocoons_800AD8E4() + count;
    if (total >= 13)
    {
        total = 12;
        ret = 0;
    }
    levantEmptyCocoons_8008B818 = total;
    return ret;
}

int RemoveEmptyCocoons_800AD944(int count)
{
    int ret = 1;
    int total = GetEmptyCocoons_800AD8E4() - count;
    if (total < 0)
    {
        total = 0;
        ret = total;
    }
    levantEmptyCocoons_8008B818 = total;
    return ret;
}

unsigned int GetEquippedId_800AD990(int slot)
{
    unsigned int id = 0;
    switch ((unsigned)slot)
    {
    case 0:
        id = equippedWeaponId_8008BD54;
        break;
    case 1:
        id = equippedArmor_8008BD55;
        break;
    case 2:
        id = byte_8008BD56;
        break;
    }
    return id;
}

int SetEquipment_800AD9EC(int id, int slot)
{
    unsigned char old = GetEquippedId_800AD990(slot);
    SaveData* sd;
    switch ((unsigned)slot)
    {
    case 0:
        if (old == 0xFF)
        {
            if (id == 0xFF)
                return 1;
        }
        else if (id == 0xFF)
        {
            goto fail;
        }
        sd = &saveData_8008B570;
        sd->levantStatus_7C8.equipment_1C[0] = id;
        RemoveInventory_800AD1E0(id, 1, 1);
        if (old < 0x17)
            AddInventory_800AD184(old, 1, 1);
        SetLevantWeaponKind_800AC3A4(GetWeaponData_8001CF84(id)->kind_2);
        GetArmorData_8001D034(sd->levantStatus_7C8.equipment_1C[1]);
        SetLevantOutfit_800AC3B0(GetArmorOutfit_8001D060(sd->levantStatus_7C8.equipment_1C[1]));
        break;
    case 1:
        if (old == 0xFF)
        {
            if (id == 0xFF)
                return 1;
        }
        else if (id == 0xFF)
        {
            goto fail;
        }
        sd = &saveData_8008B570;
        sd->levantStatus_7C8.equipment_1C[1] = id;
        RemoveInventory_800AD1E0(id, 1, 2);
        if (old < 0xF)
            AddInventory_800AD184(old, 1, 2);
        SetLevantWeaponKind_800AC3A4(GetWeaponData_8001CF84(sd->levantStatus_7C8.equipment_1C[0])->kind_2);
        GetArmorData_8001D034(id);
        SetLevantOutfit_800AC3B0(GetArmorOutfit_8001D060(id));
        break;
    fail:
        return 0;
    case 2:
        byte_8008BD56 = id;
        RemoveInventory_800AD1E0(id, 1, 3);
        if (old != 0xFF)
            AddInventory_800AD184(old, 1, 3);
        break;
    }
    return 1;
}

int FindMapVar_800ADBA0(short* key)
{
    SaveData* sd = &saveData_8008B570;
    int i;
    for (i = 0; i < sd->nMapVars_2F4; i++)
    {
        if (sd->mapVars_2F8[i].area_0 == key[0] && sd->mapVars_2F8[i].map_2 == key[1] && sd->mapVars_2F8[i].sub_4 == key[2])
            return i;
    }
    return -1;
}

int GetMapVar_800ADC1C(short* key)
{
    int value = FindMapVar_800ADBA0(key);
    if (value != -1)
        value = saveData_8008B570.mapVars_2F8[value].value_6;
    return value;
}

void SetMapVar_800ADC5C(unsigned short* key, int value)
{
    int i;
    if (value != -2)
    {
        i = FindMapVar_800ADBA0((short*)key);
        if (i == -1)
            i = saveData_8008B570.nMapVars_2F4++;
        saveData_8008B570.mapVars_2F8[i].area_0 = key[0];
        saveData_8008B570.mapVars_2F8[i].map_2 = key[1];
        saveData_8008B570.mapVars_2F8[i].sub_4 = key[2];
        saveData_8008B570.mapVars_2F8[i].value_6 = value;
    }
}

void FindMapEntrance_800ADCEC(short* out, int key)
{
    int i, j, k;
    GameMapEntrance** row;
    GameMapEntrance* e;
    for (i = 0; mapTable_800B0608[i]; i++)
    {
        row = mapTable_800B0608[i];
        for (j = 0; row[j]; j++)
        {
            e = row[j];
            for (k = 0; e[k].id_0 != -1; k++)
            {
                if (key == e[k].entrance_6)
                {
                    out[0] = i;
                    out[1] = j;
                    out[2] = k;
                    out[3] = e[k].encIndex_4;
                    return;
                }
            }
        }
    }
}

// Matched
void SelectMapEntrance_800ADDAC(void)
{
    GameMapLoc loc;
    int savedEntrance;
    int i;
    int key;
    GameMapEntrance* ents;
    loc.area = saveData_8008B570.mapId_2E4[0].field_0;
    loc.map = saveData_8008B570.mapId_2E4[1].field_0;
    loc.entrance = saveData_8008B570.mapId_2E4[2].field_0;
    savedEntrance = GetMapVar_800ADC1C(&loc);
    ents = mapTable_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0];
    key = saveData_8008B570.mapId_2E4[2].field_0;
    i = 0;
    if (ents->id_0 >= 0)
    {
        do
        {
            if (key == ents[i].encIndex_4)
            {
                if (savedEntrance == -1)
                {
                    saveData_8008B570.mapId_2E4[2].field_0 = i;
                    return;
                }
                if (savedEntrance == ents[i].entrance_6)
                {
                    saveData_8008B570.mapId_2E4[2].field_0 = i;
                    return;
                }
            }
            i++;
        } while (ents[i].id_0 >= 0);
    }
}
