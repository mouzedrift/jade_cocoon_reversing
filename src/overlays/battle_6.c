// BATTLE.BIN, source file 6 of 6 from 0x800C4118 (enemy AI; .rdata from 0x800B684C)
#include "battle.h"

int unused_800C8B2C = 0xFFFF;
unsigned char aiCounter_800C8B30[4] = { 0 };
int aiAllyCalled_800C8B34 = 0;
unsigned char commandHandlerIdx_800C8B38[28] = { 0, 0, 1, 2, 0, 3, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 6, 0, 0, 0, 3 };
void (*commandHandlers_800C8B54[7])() = { CmdAction_800BBA24, CmdSummon_800BBBA8, CmdRecall_800BBDB4, CmdSimple_800BC0FC, CmdSwapMinion_800BBBF4, CmdEnemyCall_800BBEFC, CmdEnemySwap_800BBFFC };
unsigned short stage00Sprites_800C8B70[8] = { 40, 41, 42, 43, 44, 45, 46, 0xFFFF };
unsigned short stage01Sprites_800C8B80[8] = { 51, 52, 53, 54, 55, 56, 0xFFFF };
unsigned short stage02Sprites_800C8B90[8] = { 61, 62, 63, 64, 65, 66, 67, 0xFFFF };
unsigned short stage03Sprites_800C8BA0[8] = { 72, 73, 74, 75, 76, 77, 78, 0xFFFF };
unsigned short stage04Sprites_800C8BB0[8] = { 84, 85, 86, 87, 88, 89, 90, 0xFFFF };
unsigned short stage05Sprites_800C8BC0[10] = {
    91, 92, 93, 94, 95, 96, 97, 98,
    0xFFFF,
};
unsigned short stage06Sprites_800C8BD4[10] = {
    99, 100, 101, 102, 103, 104, 105, 106,
    0xFFFF,
};
unsigned short stage07Sprites_800C8BE8[8] = { 108, 109, 110, 111, 112, 113, 0xFFFF };
unsigned short stage08Sprites_800C8BF8[10] = {
    118, 119, 120, 121, 122, 123, 124, 125,
    0xFFFF,
};
unsigned short stage09Sprites_800C8C0C[8] = { 126, 127, 128, 129, 130, 131, 0xFFFF };
unsigned short stage0ASprites_800C8C1C[8] = { 136, 137, 138, 139, 140, 141, 0xFFFF };
unsigned short stage0BSprites_800C8C2C[8] = { 0x11D, 0x11E, 0x11F, 0x120, 0x121, 0x122, 0xFFFF };
unsigned short stage0CSprites_800C8C3C[10] = {
    0x127, 0x128, 0x129, 0x12A, 0x12B, 0x12C, 0x12D, 0x12E,
    0xFFFF,
};
unsigned short stage0DSprites_800C8C50[8] = { 0x12F, 0x130, 0x131, 0x132, 0x133, 0x134, 0xFFFF };
unsigned short stage0ESprites_800C8C60[8] = { 0x139, 0x13A, 0x13B, 0x13C, 0x13D, 0x13E, 0xFFFF };
unsigned short stage0FSprites_800C8C70[6] = { 146, 147, 148, 149, 150, 0xFFFF };
unsigned short stage10Sprites_800C8C7C[6] = { 152, 153, 154, 155, 0xFFFF };
unsigned short stage11Sprites_800C8C88[8] = { 156, 157, 158, 159, 160, 161, 0xFFFF };
unsigned short stage12Sprites_800C8C98[2] = { 0xFFFF };
unsigned short stage13Sprites_800C8C9C[6] = { 166, 167, 168, 169, 0xFFFF };
unsigned short stage14Sprites_800C8CA8[6] = { 171, 172, 173, 174, 175, 0xFFFF };
unsigned short stage15Sprites_800C8CB4[6] = { 176, 177, 178, 179, 180, 0xFFFF };
unsigned short stage16Sprites_800C8CC0[6] = { 182, 183, 184, 185, 186, 0xFFFF };
unsigned short stage17Sprites_800C8CCC[8] = { 187, 188, 189, 190, 191, 192, 193, 0xFFFF };
unsigned short stage18Sprites_800C8CDC[8] = { 198, 199, 200, 201, 202, 203, 0xFFFF };
unsigned short stage19Sprites_800C8CEC[8] = { 208, 209, 210, 211, 212, 213, 214, 0xFFFF };
unsigned short stage1ASprites_800C8CFC[8] = { 219, 220, 221, 222, 223, 224, 225, 0xFFFF };
unsigned short stage1BSprites_800C8D0C[8] = { 0x16F, 0x170, 0x171, 0x172, 0x173, 0x174, 0x175, 0xFFFF };
unsigned short stage1CSprites_800C8D1C[10] = {
    0x10C, 0x10D, 0x10E, 0x10F, 0x110, 0x111, 0x112, 0x113,
    0xFFFF,
};
unsigned short stage1DSprites_800C8D30[10] = {
    0x114, 0x115, 0x116, 0x117, 0x118, 0x119, 0x11A, 0x11B,
    0xFFFF,
};
unsigned short stage1ESprites_800C8D44[8] = { 230, 231, 232, 233, 234, 235, 0xFFFF };
unsigned short stage1FSprites_800C8D54[10] = {
    240, 241, 242, 243, 244, 245, 246, 247,
    0xFFFF,
};
unsigned short stage20Sprites_800C8D68[8] = { 248, 249, 250, 251, 252, 253, 0xFFFF };
unsigned short stage21Sprites_800C8D78[8] = { 0x102, 0x103, 0x104, 0x105, 0x106, 0x107, 0xFFFF };
unsigned short stage22Sprites_800C8D88[8] = { 0x183, 0x184, 0x185, 0x186, 0x187, 0x188, 0xFFFF };
unsigned short stage23Sprites_800C8D98[6] = { 0x197, 0x198, 0x199, 0x19A, 0x19B, 0xFFFF };
unsigned short stage24Sprites_800C8DA4[8] = { 0x18D, 0x18E, 0x18F, 0x190, 0x191, 0x192, 0xFFFF };
unsigned short stage25Sprites_800C8DB4[8] = { 0x1A0, 0x1A1, 0x1A2, 0x1A3, 0x1A4, 0x1A5, 0xFFFF };
unsigned short stage26Sprites_800C8DC4[8] = { 0x179, 0x17A, 0x17B, 0x17C, 0x17D, 0x17E, 0xFFFF };
unsigned short stage10Models_800C8DD4[12] = {
    49, 48, 0, 0, 255, 0, 0, 0,
    255,
};
unsigned short stage12Models_800C8DEC[12] = {
    52, 0, 0, 0, 255, 0, 0, 0,
    255,
};
unsigned short stage13Models_800C8E04[12] = {
    54, 0, 1, 0, 55, 48, 0, 0,
    56, 48,
};
unsigned short stage0AModels_800C8E1C[12] = {
    193, 48, 0, 0, 255, 0, 0, 0,
    255,
};
unsigned short stage0EModels_800C8E34[12] = {
    194, 48, 0, 0, 255, 0, 0, 0,
    255,
};
unsigned short stage21Models_800C8E4C[12] = {
    195, 48, 0, 0, 255, 0, 0, 0,
    255,
};
unsigned short stage14Models_800C8E64[12] = {
    58, 0, 1, 0, 255, 0, 0, 0,
    255,
};
unsigned short stage15Models_800C8E7C[12] = {
    60, 0, 1, 0, 255, 0, 0, 0,
    255,
};
unsigned short stage16Models_800C8E94[12] = {
    62, 0, 1, 0, 255, 0, 0, 0,
    255,
};
BatStage battleStages_800C8EAC[39] = {
    { stage00Sprites_800C8B70, 0x3A6, 37, 0, 7, -1 },
    { stage01Sprites_800C8B80, 0x3A8, 38, 0, 6, -1 },
    { stage02Sprites_800C8B90, 0x3A9, 39, 0, 7, -1 },
    { stage03Sprites_800C8BA0, 0x3AA, 40, 0, 7, -1 },
    { stage04Sprites_800C8BB0, 0x3AB, 41, 0, -1, 83 },
    { stage05Sprites_800C8BC0, 0x3C5, 42, 0, -1, 0x1AA },
    { stage06Sprites_800C8BD4, 0x3C7, 43, 0, -1, 107 },
    { stage07Sprites_800C8BE8, 0x3AC, 44, 0, 6, -1 },
    { stage08Sprites_800C8BF8, 0x3AD, 45, 0, -1, -1 },
    { stage09Sprites_800C8C0C, 0x3B7, 46, 0, -1, -1 },
    { stage0ASprites_800C8C1C, 0x3BA, 47, 0, -1, -1, stage0AModels_800C8E1C },
    { stage0BSprites_800C8C2C, 0x3B3, 74, 0, 6, -1 },
    { stage0CSprites_800C8C3C, 0x3B5, 75, 0, -1, -1 },
    { stage0DSprites_800C8C50, 0x3B8, 76, 0, 6, -1 },
    { stage0ESprites_800C8C60, 0x3BB, 77, 0, 6, -1, stage0EModels_800C8E34 },
    { stage0FSprites_800C8C70, 0x3BD, 48, 0, -1, 151 },
    { stage10Sprites_800C8C7C, 0x3BE, 50, 0, -1, -1, stage10Models_800C8DD4 },
    { stage11Sprites_800C8C88, 0x3BF, 51, 0, -1, -1 },
    { stage12Sprites_800C8C98, 0x3C0, 53, 0, 0, -1, stage12Models_800C8DEC },
    { stage13Sprites_800C8C9C, 0x3C1, 57, 0, -1, 170, stage13Models_800C8E04 },
    { stage14Sprites_800C8CA8, 0x3C2, 59, 0, -1, -1, stage14Models_800C8E64 },
    { stage15Sprites_800C8CB4, 0x3C3, 61, 0, -1, 181, stage15Models_800C8E7C },
    { stage16Sprites_800C8CC0, 0x3C4, 63, 0, -1, -1, stage16Models_800C8E94 },
    { stage17Sprites_800C8CCC, 0x3AE, 64, 0, 7, -1 },
    { stage18Sprites_800C8CDC, 0x3AF, 65, 0, 6, -1 },
    { stage19Sprites_800C8CEC, 0x3B0, 66, 0, 7, -1 },
    { stage1ASprites_800C8CFC, 0x3B1, 67, 0, 7, -1 },
    { stage1BSprites_800C8D0C, 0x3B2, 175, 0, -1, 0x16E },
    { stage1CSprites_800C8D1C, 0x3C6, 72, 0, -1, 0x1AB },
    { stage1DSprites_800C8D30, 0x3C8, 73, 0, -1, 0x11C },
    { stage1ESprites_800C8D44, 0x3B4, 68, 0, 6, -1 },
    { stage1FSprites_800C8D54, 0x3B6, 69, 0, -1, -1 },
    { stage20Sprites_800C8D68, 0x3B9, 70, 0, 6, -1 },
    { stage21Sprites_800C8D78, 0x3BC, 71, 0, 6, -1, stage21Models_800C8E4C },
    { stage22Sprites_800C8D88, 0x434, 187, 0, 6, -1 },
    { stage23Sprites_800C8D98, 0x435, 189, 0, 5, -1 },
    { stage24Sprites_800C8DA4, 0x436, 188, 0, 6, -1 },
    { stage25Sprites_800C8DB4, 0x437, 190, 0, 6, -1 },
    { stage26Sprites_800C8DC4, 0x438, 186, 0, 6, -1 },
};
unsigned char stageAnimPhases_800C911C[8] = { 1, 5, 9, 2, 6, 3, 7, 4 };
SVECTOR stageRot_800C9124 = { 0 };
char handlerWaitsReactions_800C912C[8] = { 0, 0, 0, 1 };
unsigned char captureVibrations_800C9134[4] = { 5, 6, 7, 8 };
BatCureChance statusCureChances_800C9138[1] = { { 2, 77 } };
BatXY enemyWindowLayouts_800C9140[9] = {
    { 110, 20 },
    { -1, -1 },
    { -1, -1 },
    { 60, 20 },
    { 160, 20 },
    { -1, -1 },
    { 10, 20 },
    { 110, 20 },
    { 210, 20 },
};
int enemyGaugePreview_800C9164[3] = { 0 };
int actorHighlightTime_800C9170 = 0;
int enemyHighlightTimes_800C9174[3] = { 0 };
short previewHpChange_800C9180 = 0;
short previewMpChange_800C9182 = 0;
int unused_800C9184 = 0x24639300;
Minion *summonedMinion_800C9188 = 0;
int summonedMinionSlot_800C918C = -1;
BatSummonedActor summonedActor_800C9190 = { 0 };
char defaultBoneSlots_800C91A4[56] = { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2 };
EnemyAiFn enemyAiHigh_800C91DC[10] = {
    EnemyAiC9_800C4328, EnemyAiCA_800C43D8, EnemyAiCB_800C4424, (EnemyAiFn)EnemyAiCC_800C4470,
    EnemyAiCD_800C4494, EnemyAiCE_800C44FC, EnemyAiCF_800C4548, EnemyAiD0_800C45A8,
    (EnemyAiFn)EnemyAiD1_800C46FC, (EnemyAiFn)EnemyAiD2_800C471C,
};
EnemyAiFn enemyAi_800C9204[53] = {
    (EnemyAiFn)EnemyAi00_800C4D38, (EnemyAiFn)EnemyAi00_800C4D38, (EnemyAiFn)EnemyAi02_800C54A4, (EnemyAiFn)EnemyAi03_800C4FE0,
    (EnemyAiFn)EnemyAi04_800C57D8, (EnemyAiFn)EnemyAi05_800C56B8, (EnemyAiFn)EnemyAi06_800C4BE4, (EnemyAiFn)EnemyAi07_800C4E34,
    (EnemyAiFn)EnemyAi08_800C580C, (EnemyAiFn)EnemyAi09_800C4DB8, (EnemyAiFn)EnemyAi0A_800C4EA8, (EnemyAiFn)EnemyAi0B_800C5510,
    (EnemyAiFn)EnemyAi0C_800C4CBC, (EnemyAiFn)EnemyAi0D_800C5424, (EnemyAiFn)EnemyAi0E_800C5034, (EnemyAiFn)EnemyAi0F_800C4B34,
    (EnemyAiFn)EnemyAi10_800C5304, (EnemyAiFn)EnemyAi0F_800C4B34, (EnemyAiFn)EnemyAi12_800C4C74, (EnemyAiFn)EnemyAi13_800C507C,
    (EnemyAiFn)EnemyAi14_800C5594, (EnemyAiFn)EnemyAi15_800C5290, (EnemyAiFn)EnemyAi16_800C5608, (EnemyAiFn)EnemyAi17_800C50B0,
    (EnemyAiFn)EnemyAi18_800C5670, (EnemyAiFn)EnemyAi19_800C576C, (EnemyAiFn)EnemyAi1A_800C4FA8, (EnemyAiFn)EnemyAi1B_800C51D8,
    (EnemyAiFn)EnemyAi1C_800C53B0, (EnemyAiFn)EnemyAi1D_800C5700, (EnemyAiFn)EnemyAi1E_800C5874, (EnemyAiFn)EnemyAi1F_800C5840,
    (EnemyAiFn)EnemyAiDefault_800C473C, (EnemyAiFn)EnemyAiDefault_800C473C, (EnemyAiFn)EnemyAiDefault_800C473C, (EnemyAiFn)EnemyAiDefault_800C473C,
    (EnemyAiFn)EnemyAiDefault_800C473C, (EnemyAiFn)EnemyAiDefault_800C473C, (EnemyAiFn)EnemyAiDefault_800C473C, (EnemyAiFn)EnemyAiDefault_800C473C,
    (EnemyAiFn)EnemyAiDefault_800C473C, (EnemyAiFn)EnemyAiDefault_800C473C, (EnemyAiFn)EnemyAiDefault_800C473C, (EnemyAiFn)EnemyAiDefault_800C473C,
    (EnemyAiFn)EnemyAiDefault_800C473C, (EnemyAiFn)EnemyAiDefault_800C473C, (EnemyAiFn)EnemyAiDefault_800C473C, (EnemyAiFn)EnemyAiDefault_800C473C,
    (EnemyAiFn)EnemyAiDefault_800C473C, (EnemyAiFn)EnemyAiDefault_800C473C, (EnemyAiFn)EnemyAiDefault_800C473C, (EnemyAiFn)EnemyAiDefault_800C473C,
    (EnemyAiFn)EnemyAiDefault_800C473C,
};
MenuCursor commandMenu_800C92D8[1] = { { 2, 3 } };
MenuCursor skillMenu_800C92E4[1] = { { 1, 5, 5 } };
MenuCursor magicMenu_800C92F0[1] = { { 1, 4, 4, 64 } };
int unused_800C92FC[3] = { 0x10001, 1 };
MenuCursor itemMenu_800C9308[1] = { { 1, 4, 4, 64 } };
MenuCursor enemyTargetMenu_800C9314[1] = { { 0, 1 } };
MenuCursor targetMenu_800C9320[1] = { { 1 } };
MenuCursor allTargetsMenu_800C932C[1] = { { 1, 1, 1 } };
MenuCursor *pageMenus_800C9338[6] = { commandMenu_800C92D8, itemMenu_800C9308, skillMenu_800C92E4, magicMenu_800C92F0, targetMenu_800C9320, commandMenu_800C92D8 };
int helpAttack_800C9350[1] = { (int)aAttackWithReadi_800B68AC };
int helpDefend_800C9354[1] = { (int)aDefendToReduceD_800B68E4 };
int helpSummon_800C9358[1] = { (int)aSummonDivineMin_800B6914 };
int helpCapture_800C935C[1] = { (int)aCaptureMinionIn_800B6940 };
int helpItem_800C9360[1] = { (int)aUseItem_800B6984 };
int helpFlee_800C9364[1] = { (int)aFleeFromCombat_800B6998 };
int helpMinionAttack_800C9368[1] = { (int)aUseNormalAttack_800B69BC };
int helpSpecialAttack_800C936C[1] = { (int)aUseSpecialAttac_800B69E0 };
int helpMagic_800C9370[1] = { (int)aUseMagicSpell_800B6A08 };
int helpChangeFighter_800C9374[1] = { (int)aChangeCurrentFi_800B6A28 };
int msgNoDivineMinions_800C9378[1] = { (int)aNoDivineMinions_800B6A58 };
int msgCannotSummon_800C937C = (int)aCannotSummonInt_800B6A88;
int msgNotEnoughMana_800C9380 = (int)aNotEnoughMana_800B6ABC;
int msgCannotCapture_800C9384[1] = { (int)aCannotCapture_800B6ADC };
int msgNoEmptyCocoons_800C9388[1] = { (int)aNoEmptyCocoons_800B6AFC };
int msgCannotEscape_800C938C[1] = { (int)aCannotEscape_800B6B20 };
int msgNoNeedToUseItem_800C9390 = (int)aNoNeedToUseItem_800B6B3C;
int msgCannotSelect_800C9394[1] = { (int)aCannotSelect_800B6B64 };
int msgItemForDivineMinions_800C9398 = (int)aThisItemIsForDi_800B6B80;
int msgDivineMinionsCannot_800C939C = (int)aDivineMinionsCa_800B6BC0;
int msgCannotUseHere_800C93A0 = (int)aCannotUseHere_800B6C08;
BatMenuItem levantMenuItems_800C93A4[6] = {
    { helpAttack_800C9350 },
    { helpDefend_800C9354 },
    { helpSummon_800C9358 },
    { helpCapture_800C935C },
    { helpItem_800C9360 },
    { helpFlee_800C9364 },
};
BatMenuItem minionMenuItems_800C93D4[5] = {
    { helpMinionAttack_800C9368 },
    { helpDefend_800C9354 },
    { helpSpecialAttack_800C936C },
    { helpMagic_800C9370 },
    { helpChangeFighter_800C9374 },
};
MenuWindowItem winAttack_800C93FC[2] = {
    { 8, 1, 13, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 22, 157, 38, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem winDefend_800C9434[2] = {
    { 8, 1, 48, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 60, 157, 38, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem winSummon_800C946C[2] = {
    { 8, 1, 180, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 22, 176, 38, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem winCapture_800C94A4[2] = {
    { 8, 1, 224, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 60, 176, 38, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem winItem_800C94DC[2] = {
    { 8, 1, 88, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 22, 195, 38, 18, 2, 3 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem winFlee_800C9514[2] = {
    { 8, 1, 57, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 60, 195, 38, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem winSpecialAttack_800C954C[2] = {
    { 8, 1, 183, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 22, 176, 38, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem winMagic_800C9584[2] = {
    { 8, 1, 108, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 60, 176, 38, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem winChangeFighter_800C95BC[2] = {
    { 8, 1, 40, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 22, 195, 76, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem *levantMenuWindows_800C95F4[7] = { winAttack_800C93FC, winDefend_800C9434, winSummon_800C946C, winCapture_800C94A4, winItem_800C94DC, winFlee_800C9514 };
MenuWindowItem *minionMenuWindows_800C9610[6] = { winAttack_800C93FC, winDefend_800C9434, winSpecialAttack_800C954C, winMagic_800C9584, winChangeFighter_800C95BC };
MenuWindowItem **menuWindowSets_800C9628[2] = { levantMenuWindows_800C95F4, minionMenuWindows_800C9610 };
MenuWindowList menuWindows_800C9630 = { 2 };
unsigned char commandByCursor_800C9648[12] = { 0, 0, 1, 1, 2, 6, 3, 7, 4, 8, 5, 5 };
unsigned char commandNextPage_800C9654[12] = { 4, 5, 4, 4, 1, 5, 2, 3, 4 };
unsigned char commandTargetFlags_800C9660[12] = { 4, 0, 2, 4, 0, 0, 4, 4, 2 };
void (*menuStateFns_800C966C[2])(EventEntry *task, int buffer) = { (void (*)(EventEntry *, int))MenuInput_800C8768, (void (*)(EventEntry *, int))MenuShowError_800C88E4 };
ButtonHelpEntry* pageButtonHelp_800C9674[6] = { helpBarSelectDesc_80082698, helpBarSelectQuitDesc_800826B0, helpBarSelectQuitDesc_800826B0, helpBarSelectQuitDesc_800826B0, helpBarSelectQuit_80082680 };
unsigned short pageHideFlags_800C968C[6][2] = {
    { 0x1F0, 240 },
    { 0x1D1, 0x1D7 },
    { 0x1B1, 0x1B7 },
    { 0x170, 0x176 },
    { 0x1E0, 246 },
};
int commandKinds_800C96A4[9] = {
    0, 18, 2, 5, 4, 7, 6, 1,
    8,
};
int itemDescriptions_800C96C8[43][4] = {
    { (int)aRestoreHealth_800B8CFC, (int)aGrowsInOpenArea_800B8CB4, (int)aIncreasesHealth_800B8C68, (int)aGrindLeavesInto_800B8C0C },
    { (int)aRestoreHealth_800B8CFC, (int)aATypeOfMugwortB_800B8BCC, (int)aSweeterSmelling_800B8B74, (int)aCuresBleedingAn_800B8B30 },
    { (int)aRestoreHealth_800B8CFC, (int)aATypeOfMugwortW_800B8ACC, (int)aBitterTasteThat_800B8A60 },
    { (int)aIncreaseMaxHeal_800B8A38, (int)aANutPackingEner_800B89D8, (int)aStrengthensTheB_800B8974 },
    { (int)aIncreaseMinionA_800B8938, (int)aOilFromATreeWit_800B88F0, (int)aSharpensMinionS_800B88BC },
    { (int)aIncreasesMinion_800B888C, (int)aOilFromAVeryPot_800B8850, (int)aStrengthensMini_800B8818 },
    { (int)aIncreaseMinionD_800B87D8, (int)aOilFromAPlantWi_800B878C, (int)aHardensMinionSS_800B875C },
    { (int)aIncreaseMinionM_800B8720, (int)aOilFromTreeWith_800B86D8, (int)aStrengthensMini_800B86A0 },
    { (int)aIncreaseMinionM_800B8664, (int)aOilFromAPlantWi_800B861C, (int)aStrengthensMini_800B85E0 },
    { (int)aRestoreMinionHP_800B85A8, (int)aLiquorMadeFromP_800B855C, (int)aRestoresSomeMin_800B8518 },
    { (int)aRestoreMinionHP_800B85A8, (int)aFineLiquorMadeF_800B84C0, (int)aRestoresMinionH_800B845C },
    { (int)aRestoreMinionHP_800B85A8, (int)aExcellentLiquor_800B83FC, (int)aRestoresAGreatD_800B83A0 },
    { (int)aRestoreMinionHP_800B85A8, (int)aSpecialLiquorMa_800B8344, (int)aRestoresAllMini_800B8300 },
    { (int)aTotalRestoratio_800B82DC, (int)aDriedRootOfAGre_800B8274, (int)aAlsoCalledTheIm_800B8230, (int)aAdjustsTheVisce_800B8204 },
    { (int)aPoisonAntidote_800B81E4, (int)aPowderedFormOfD_800B8198, (int)aSoothesTheSpiri_800B8144 },
    { (int)aStoneToFlesh_800B8124, (int)aPowderMadeFromS_800B80C0, (int)aInnerStrengthTo_800B8064 },
    { (int)aSprayPoison_800B8048, (int)aReleasesPoisonM_800B8004, (int)aInstantlyCauses_800B7FBC },
    { (int)aInduceSleep_800B7FA0, (int)aReleasesASleepM_800B7F58, (int)aCausesADeepSlum_800B7EEC },
    { (int)aFleshToStone_800B7ECC, (int)aReleasesAFleshT_800B7E74, (int)aCausesBodyHarde_800B7E18 },
    { (int)aCauseDeath_800B7E00, (int)aReleasesADeathM_800B7DB8, (int)aInstantlyCauses_800B7D5C },
    { (int)aProtectionFromA_800B7D34, (int)aReflectsAllUncl_800B7CD4, (int)aAllAbnormalStat_800B7C6C },
    { (int)aChangeAreaPrope_800B7C3C, (int)aACharmBlessedBy_800B7BDC, (int)aChangesAreaProp_800B7B74 },
    { (int)aChangeAreaPrope_800B7C3C, (int)aACharmBlessedBy_800B7B14, (int)aChangesAreaProp_800B7AAC },
    { (int)aChangeAreaPrope_800B7C3C, (int)aACharmBlessedBy_800B7A4C, (int)aChangesAreaProp_800B79E8 },
    { (int)aChangeAreaPrope_800B7C3C, (int)aACharmBlessedBy_800B7988, (int)aChangesAreaProp_800B7924 },
    { (int)aAttackSingleEne_800B78E4, (int)aSealWithTheMark_800B787C, (int)aInflictsAnEarth_800B7818 },
    { (int)aAttackAllEnemie_800B77DC, (int)aSealWithTheMark_800B787C, (int)aInflictsAnEarth_800B777C },
    { (int)aAttackSingleEne_800B773C, (int)aSealWithTheMark_800B76D4, (int)aInflictsAWaterB_800B7670 },
    { (int)aAttackAllEnemie_800B7634, (int)aSealWithTheMark_800B76D4, (int)aInflictsAWaterB_800B75D8 },
    { (int)aAttackSingleEne_800B759C, (int)aSealWithTheMark_800B7538, (int)aInflictsAFireBa_800B74D8 },
    { (int)aAttackAllEnemie_800B749C, (int)aSealWithTheMark_800B7538, (int)aInflictsAFireBa_800B7440 },
    { (int)aAttackSingleEne_800B7404, (int)aSealWithTheMark_800B739C, (int)aInflictsAWindBa_800B733C },
    { (int)aAttackMultipleE_800B72F8, (int)aSealWithTheMark_800B739C, (int)aInflictsAWindBa_800B7294 },
    { (int)aSilkThreadSpunF_800B7248, (int)aGivesOffAShineT_800B71EC, (int)aSeventhHighestG_800B71AC },
    { (int)aSilkThreadSpunF_800B7248, (int)aEmitsVagueInsta_800B7150, (int)aSixthHighestGra_800B7114 },
    { (int)aSilkThreadSpunF_800B7248, (int)aGivesOffADazzli_800B70DC, (int)aFifthHighestGra_800B70A0 },
    { (int)aSilkThreadSpunF_800B7248, (int)aGivesOffAModera_800B7058, (int)aFourthHighestGr_800B701C },
    { (int)aSilkThreadSpunF_800B7248, (int)aGivesOffAPhosph_800B6FCC, (int)aThirdHighestGra_800B6F90 },
    { (int)aSilkThreadSpunF_800B7248, (int)aGivesOffAnUnear_800B6F40, (int)aSecondHighestGr_800B6F04 },
    { (int)aSilkThreadSpunF_800B7248, (int)aSoftThreadThatG_800B6EB0, (int)aHighestGradeBes_800B6E6C },
    { (int)aKeyToTreasureCh_800B6E3C, (int)aMultipurposeKey_800B6DD8, (int)aBendsAndBecomes_800B6D80 },
    { (int)aTreeSpores_800B6D68, (int)aSweetSmellingSl_800B6D00, (int)aCausesSurroundi_800B6CA8 },
    { (int)aTreeSpores_800B6D68, (int)aTreeSporesWithA_800B6C5C, (int)aAttractsNearbyM_800B6C28 },
};
int magicDescriptions_800C9978[30][4] = {
    { (int)aFireAttackOneEn_800B97B8, (int)aExtraDamageVsAi_800B978C, (int)aHigherFireEleme_800B9730 },
    { (int)aFireAttackAllEn_800B96FC, (int)aExtraDamageVsAi_800B978C, (int)aHigherFireEleme_800B9730 },
    { (int)aAdvancedFireAtt_800B96D0, (int)aExtraDamageVsAi_800B978C, (int)aHigherFireEleme_800B9730 },
    { (int)aWaterAttackOneE_800B969C, (int)aExtraDamageVsFi_800B9670, (int)aHigherWaterElem_800B9610 },
    { (int)aWaterAttackAllE_800B95D8, (int)aExtraDamageVsFi_800B9670, (int)aHigherWaterElem_800B9610 },
    { (int)aAdvancedWaterAt_800B95AC, (int)aExtraDamageVsFi_800B9670, (int)aHigherWaterElem_800B9610 },
    { (int)aEarthAttackOneE_800B9578, (int)aExtraDamageVsWa_800B9548, (int)aHigherEarthElem_800B94E8 },
    { (int)aEarthAttackAllE_800B94B0, (int)aExtraDamageVsWa_800B9548, (int)aHigherEarthElem_800B94E8 },
    { (int)aAdvancedEarthAt_800B9484, (int)aExtraDamageVsWa_800B9548, (int)aHigherEarthElem_800B94E8 },
    { (int)aWindAttackOneEn_800B9454, (int)aExtraDamageVsEa_800B9424, (int)aHigherWindEleme_800B93C8 },
    { (int)aWindAttackAllEn_800B9394, (int)aExtraDamageVsEa_800B9424, (int)aHigherWindEleme_800B93C8 },
    { (int)aAdvancedWindAtt_800B9368, (int)aExtraDamageVsEa_800B9424, (int)aHigherWindEleme_800B93C8 },
    { (int)aCurePoison_800B9350, (int)aCuresPoison_800B9334 },
    { (int)aRestoreHP_800B931C, (int)aRestoresSomeHP_800B92F8 },
    { (int)aRestoreAllHP_800B92D8, (int)aRestoresAllHP_800B92B4 },
    { (int)aReturnToNormal_800B9290, (int)aCuresPoisonAndT_800B9238 },
    { (int)aProtection_800B9220, (int)aProtectsAgainst_800B91B8, (int)aEndsOnceItProte_800B9164 },
    { (int)aPoison_800B9154, (int)aPoisonsAnEnemy_800B9130 },
    { (int)aSleep_800B9124, (int)aPutsAnEnemyToSl_800B90F4 },
    { (int)aFleshToStone_800B7ECC, (int)aTurnsAnEnemyInt_800B90BC },
    { (int)aDeath_800B90B0, (int)aCausesAnEnemyTo_800B905C },
    { (int)aEnhanceFire_800B9040, (int)aIncreasesFireAt_800B8FEC, (int)aEffectivenessOf_800B8F90 },
    { (int)aEnhanceWater_800B8F74, (int)aIncreasesWaterA_800B8F1C, (int)aEffectivenessOf_800B8EC0 },
    { (int)aEnhanceEarth_800B8EA4, (int)aIncreasesEarthA_800B8E4C, (int)aEffectivenessOf_800B8DEC },
    { (int)aEnhanceWind_800B8DD0, (int)aIncreasesWindAt_800B8D7C, (int)aEffectivenessOf_800B8D1C },
};
const char* skillDescriptions_800C9B58[16][4] = {
    { emptyText_800BA174, emptyText_800BA174, emptyText_800BA174, 0 },
    { emptyText_800BA174, emptyText_800BA174, emptyText_800BA174, 0 },
    { aSpecialEarthAtt_800BA148, aVeryEffectiveAg_800BA0F0, aHigherEarthElem_800B94E8, 0 },
    { aSpecialWaterAtt_800BA0C4, aVeryEffectiveAg_800BA06C, aHigherWaterElem_800B9610, 0 },
    { aSpecialFireAtta_800BA044, aVeryEffectiveAg_800B9FEC, aHigherFireEleme_800B9730, 0 },
    { aSpecialWindAtta_800B9FC4, aVeryEffectiveAg_800B9F6C, aHigherWindEleme_800B93C8, 0 },
    { aSpecialPoisonAt_800B9F40, aPhysicallyDamag_800B9EEC, 0, 0 },
    { aSpecialSleepAtt_800B9EC0, aPhysicallyDamag_800B9E58, 0, 0 },
    { aSpecialFleshToS_800B9E1C, aPhysicallyDamag_800B9DB0, 0, 0 },
    { aSpecialAttackDe_800B9D74, aCausesAnEnemyTo_800B9D0C, aMoreDifficultFo_800B9CBC, 0 },
    { aSpecialAttackAb_800B9C84, aTakesSomeOfTheD_800B9C38, aAnEnemyToRestor_800B9BE8, 0 },
    { aSpecialAttackAb_800B9BAC, aStealsSomeManaF_800B9B64, aUsesItToRestore_800B9B1C, 0 },
    { aSpecialAttackAl_800B9AE0, aAttacksAllEnemi_800B9AA4, aBringsEnemiesTo_800B9A58, 0 },
    { aSpecialAttackCr_800B9A1C, aReducesAnEnemie_800B99D0, aItMoreDifficult_800B9978, 0 },
    { aSpecialAttackBr_800B9940, aMakesItEasierTo_800B98E0, aSlightlyMoreDif_800B987C, 0 },
    { aSpecialAttackBr_800B9840, aMakesItEasierTo_800B97E8, aSlightlyMoreDif_800B987C, 0 },
};
int battleLoadState_800C9C58 = 0;
int unused_800C9C5C[3] = { 0 };
short turnGauges_800C9C68[8] = { 0 };
int *chainEntry_800C9C78 = 0;
unsigned char actingUnit_800C9C7C = 0;
short actorHpChange_800C9C7E = 0;
short actorMpChange_800C9C80 = 0;
unsigned char summonedUnit_800C9C82 = 0;
int unused_800C9C84 = 0;
BattleCmd curCommand_800C9C88 = { 0 };
unsigned char commandUnit_800C9C98 = 0;
unsigned char shownUnit_800C9C99 = 0;
int unused_800C9C9C = 0;
int unitStatusInflicted_800C9CA0[7] = { 0 };
char unitHitKinds_800C9CBC[12] = { 0 };
BattleCmd unitReactions_800C9CC8[7] = { { 0 } };
short unitHpDamage_800C9D38[8] = { 0 };
short unitMpDamage_800C9D48[7] = { 0 };
char savedEnemyCursor_800C9D56 = 0;
int unitResultFlags_800C9D58[7] = { 0 };
const char* helpWindowText_800C9D74 = 0;
short hitSfx_800C9D78 = 0;
int btlExecLoad_800C9D7C = 0;
short deathSfx_800C9D80 = 0;
signed char shownAreaElement_800C9D82 = 0;
char fixedStageElement_800C9D83 = 0;
signed char areaElement_800C9D84 = 0;
int unused_800C9D88 = 0;
short stageAnimUv_800C9D8C[2] = { 0 };
int removedEnemyCount_800C9D90 = 0;
short actionFrame_800C9D94 = 0;
short actorTiming_800C9D98[4] = { 0 };
BatActionTiming reactionTimings_800C9DA0[7] = { { 0 } };
short actorHitShift_800C9DBC = 0;
short reactionHitFrames_800C9DC0[8] = { 0 };
int removedEnemies_800C9DD0[10] = { 0 };
int enemyWindowFlags_800C9DF8 = 0;
char enemyWindowsHighlight_800C9DFC = 0;
char actorWindowHighlight_800C9DFD = 0;
unsigned int enemyWindowSlide_800C9E00 = 0;
int unused_800C9E04 = 0;
EventEntry *enemyWindowTasks_800C9E08[4] = { 0 };
BatXY enemyWindowPos_800C9E18[3] = { { 0 } };
int enemyWindowMask_800C9E24 = 0;
BatEnemyWindow *enemyWindows_800C9E28[4] = { 0 };
int cameraFocus_800C9E38 = 0;
int newCameraFocus_800C9E3C = 0;
unsigned char prevMenuPage_800C9E40 = 0;
MenuCursor *pageCursor_800C9E44 = 0;
unsigned char menuState_800C9E48 = 0;
unsigned char menuForMinion_800C9E49 = 0;
unsigned char enemyCount_800C9E4A = 0;
unsigned char partyMinionCount_800C9E4B = 0;
int enemyMask_800C9E4C = 0;
unsigned char menuPage_800C9E50 = 0;
unsigned char menuErrorTimer_800C9E51 = 0;
int menuTarget_800C9E54 = 0;
BattleCmd menuCommand_800C9E58 = { 0 };
unsigned char targetFlags_800C9E68 = 0;
BatMenuItem *menuItems_800C9E6C = 0;
BatEnemyTargets enemyTargets_800C9E70 = { 0 };
int partyMinionMask_800C9E78 = 0;
int menuErrorText_800C9E7C = 0;
unsigned char enemyUnits_800C9E80[4] = { 0 };

void ChooseEnemyCommand_800C4118(BattleCmd* cmd, UnitStats* self, int slot, unsigned int script)
{
    EnemyAi ai;
    unsigned int species;
    int minionSlot;
    species = self->species_5C;
    ai.magicBits_0 = &self->magicBits_80;
    ai.skills_4 = &self->skills_6C;
    ai.cmd_8 = cmd;
    ai.slot_C = slot;
    ai.self_10 = self;
    ai.f1C = 4;
    minionSlot = GetSummonedMinionSlot_800C0D50();
    if (minionSlot >= 0)
    {
        ai.targetMask_18 = 1 << (minionSlot + 1);
        ai.target_14 = GetMinionStatus_800107A0(3, minionSlot);
    }
    else
    {
        ai.targetMask_18 = 1;
        ai.target_14 = &saveData_8008B570.levantStatus_7C8;
    }
    ai.cmd_8->mask_8 = 1 << (slot + 4);
    switch (script)
    {
    case 0:
        if (species < 0x39)
        {
            enemyAi_800C9204[species](&ai);
        }
        else if (species < 0xC9)
        {
            if (species - 0xBD < 4)
            {
                EnemyAiBD_800C4A40(&ai);
            }
            EnemyAiDefault_800C473C(&ai);
            break;
        }
        else
        {
            species -= 0xC9;
            enemyAiHigh_800C91DC[species](&ai);
        }
        break;
    case 2:
        BossAi02_800C5A7C(&ai);
        break;
    case 15:
        BossAi0F_800C66F4(&ai);
        break;
    case 16:
        BossAi10_800C6824(&ai);
        break;
    case 17:
        BossAi11_800C6928(&ai);
        break;
    case 3:
        BossAi03_800C5BC0(&ai);
        break;
    case 4:
        BossAi04_800C59A0(&ai);
        break;
    case 10:
        BossAi0A_800C58BC(&ai);
        break;
    case 11:
        BossAi0B_800C5EB8(&ai);
        break;
    case 12:
        BossAi0C_800C6038(&ai);
        break;
    case 13:
        BossAi0D_800C5D04(&ai);
        break;
    case 14:
        BossAi0E_800C61FC(&ai);
        break;
    case 7:
    case 8:
    case 9:
        EnemyAiFirstSkill_800C6A40(&ai);
        break;
    default:
        EnemyAiDefend_800C58AC(&ai);
        break;
    }
}

void EnemyAiC9_800C4328(EnemyAi* ai)
{
    UnitStatus* status = ai->target_14;
    short hp = GetHp_800334D8(status);
    short maxHp = GetMaxHp_800334CC(status);
    if (hp < (short)(maxHp / 10))
    {
        AiSetCommand_800C6AFC(ai, 6, 0);
    }
    else if (rand() & 1)
    {
        AiSetCommand_800C6AFC(ai, 6, 1);
    }
    else
    {
        AiSetCommand_800C6AFC(ai, 0, 0);
    }
}

void EnemyAiCA_800C43D8(EnemyAi* ai)
{
    if (rand() & 1)
    {
        AiSetCommand_800C6AFC(ai, 1, 8);
    }
    else
    {
        AiSetCommand_800C6AFC(ai, 1, 6);
    }
}

void EnemyAiCB_800C4424(EnemyAi* ai)
{
    if (rand() & 1)
    {
        AiSetCommand_800C6AFC(ai, 6, 2);
    }
    else
    {
        AiSetCommand_800C6AFC(ai, 0, 0);
    }
}

void EnemyAiCC_800C4470(int ai)
{
    AiSetCommand_800C6AFC(ai, 1, 0x14);
}

void EnemyAiCD_800C4494(EnemyAi* ai)
{
    int hp = rand();
    if (hp % 3)
    {
        AiSetCommand_800C6AFC(ai, 6, 3);
    }
    else
    {
        AiSetCommand_800C6AFC(ai, 0, 0);
    }
}

void EnemyAiCE_800C44FC(EnemyAi* ai)
{
    if (rand() & 1)
    {
        AiSetCommand_800C6AFC(ai, 6, 1);
    }
    else
    {
        AiSetCommand_800C6AFC(ai, 6, 2);
    }
}

void EnemyAiCF_800C4548(EnemyAi* ai)
{
    if (AiHealWeakAlly_800C6DF8(ai, 0xD) == 0)
    {
        if (rand() & 1)
        {
            AiDefend_800C6C44(ai);
        }
        else
        {
            AiSetCommand_800C6AFC(ai, 0, 0);
        }
    }
}

void EnemyAiD0_800C45A8(EnemyAi* ai)
{
    if (TargetHasStatus_800C6EC8(ai, 0x3F8) == 0 && rand() % 10 < 7)
    {
        AiSetCommand_800C6AFC(ai, 6, 0);
    }
    else if (TargetHasStatus_800C6EC8(ai, 2) == 0 && rand() % 10 < 7)
    {
        AiSetCommand_800C6AFC(ai, 6, 1);
    }
    else if (TargetHasStatus_800C6EC8(ai, 1) == 0 && rand() % 10 < 7)
    {
        AiSetCommand_800C6AFC(ai, 6, 2);
    }
    else
    {
        AiAttack_800C6A68(ai);
    }
}

void EnemyAiD1_800C46FC()
{
    EnemyAiDefault_800C473C();
}

void EnemyAiD2_800C471C()
{
    EnemyAiDefault_800C473C();
}

int EnemyAiDefault_800C473C(EnemyAi* ai)
{
    UnitStatus* status = &ai->self_10->st_0;
    int chosen;
    int i;
    if ((GetAreaElement_800BC868() == 0 || GetAreaElement_800BC868() == -1) && (chosen = AiCastMagic_800C6BD0(ai, 0x16)))
    {
        return chosen;
    }
    if ((GetAreaElement_800BC868() == 1 || GetAreaElement_800BC868() == -1) && (chosen = AiCastMagic_800C6BD0(ai, 0x15)))
    {
        return chosen;
    }
    if ((GetAreaElement_800BC868() == 2 || GetAreaElement_800BC868() == -1) && (chosen = AiCastMagic_800C6BD0(ai, 0x18)))
    {
        return chosen;
    }
    if ((GetAreaElement_800BC868() == 3 || GetAreaElement_800BC868() == -1) && (chosen = AiCastMagic_800C6BD0(ai, 0x17)))
    {
        return chosen;
    }
    if (TargetHasStatus_800C6EC8(ai, 0x3F8) == 0 && rand() % 10 < 7 && (chosen = AiCastMagic_800C6BD0(ai, 0x13)))
    {
        return chosen;
    }
    if (TargetHasStatus_800C6EC8(ai, 2) == 0 && rand() % 10 < 7 && (chosen = AiCastMagic_800C6BD0(ai, 0x12)))
    {
        return chosen;
    }
    if (TargetHasStatus_800C6EC8(ai, 1) == 0 && rand() % 10 < 7 && (chosen = AiCastMagic_800C6BD0(ai, 0x11)))
    {
        return chosen;
    }
    if ((rand() & 1) && (chosen = AiCastMagic_800C6BD0(ai, 0x14)))
    {
        return chosen;
    }
    if ((chosen = AiHealWeakAlly_800C6DF8(ai, 0xD)))
    {
        return chosen;
    }
    if (status->stats_2C.cur_0[1] > status->stats_2C.cur_0[3])
    {
        if (rand() % 10 < 8 && (chosen = AiUseSkill_800C6A8C(ai)))
        {
            return chosen;
        }
    }
    else
    {
        for (i = 0; i < 12; i++)
        {
            if ((chosen = AiCastMagic_800C6BD0(ai, i)))
            {
                return chosen;
            }
        }
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAiBD_800C4A40(EnemyAi* ai)
{
    int chosen;
    if (rand() & 1)
    {
        if (TargetHasStatus_800C6EC8(ai, 0x3F8) == 0)
        {
            chosen = AiCastMagic_800C6BD0(ai, 0x13);
        }
        else
        {
            chosen = AiUseSkill_800C6A8C(ai);
        }
        if (chosen)
        {
            return chosen;
        }
        if (TargetHasStatus_800C6EC8(ai, 2) == 0)
        {
            chosen = AiCastMagic_800C6BD0(ai, 0x12);
        }
        else
        {
            chosen = AiUseSkill_800C6A8C(ai);
        }
        if (chosen)
        {
            return chosen;
        }
        if (TargetHasStatus_800C6EC8(ai, 1) == 0)
        {
            chosen = AiCastMagic_800C6BD0(ai, 0x11);
        }
        else
        {
            chosen = AiUseSkill_800C6A8C(ai);
        }
        if (chosen)
        {
            return chosen;
        }
        chosen = AiCastMagic_800C6BD0(ai, 0x14);
        if (chosen == 0)
        {
            chosen = AiUseSkill_800C6A8C(ai);
        }
        return chosen;
    }
    return AiFlee_800C6C58(ai);
}

int EnemyAi0F_800C4B34(EnemyAi* ai)
{
    int chosen;
    UnitStatus* status = &ai->self_10->st_0;
    short hp = GetHp_800334D8(status);
    short maxHp = GetMaxHp_800334CC(status);
    if (hp < (short)(maxHp / 3))
    {
        chosen = AiUseSkill_800C6A8C(ai);
        if (chosen)
        {
            return chosen;
        }
        if (rand() & 1)
        {
            chosen = AiDefend_800C6C44(ai);
            if (chosen)
            {
                return chosen;
            }
        }
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi06_800C4BE4(EnemyAi* ai)
{
    int chosen;
    UnitStatus* status = &ai->self_10->st_0;
    chosen = AiHealWeakAlly_800C6DF8(ai, 0xD);
    if (chosen)
    {
        return chosen;
    }
    {
        short hp = GetHp_800334D8(status);
        short maxHp = GetMaxHp_800334CC(status);
        if (hp < maxHp)
        {
            if (rand() & 1)
            {
                chosen = AiDefend_800C6C44(ai);
                if (chosen)
                {
                    return chosen;
                }
            }
        }
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi12_800C4C74(EnemyAi* ai)
{
    int chosen;
    if (TargetHasStatus_800C6EC8(ai, 1) == 0)
    {
        chosen = AiUseSkill_800C6A8C(ai);
        if (chosen)
        {
            return chosen;
        }
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi0C_800C4CBC(EnemyAi* ai)
{
    int chosen;
    int roll = rand() % 100;
    if (roll < 30)
    {
        chosen = AiCastMagic_800C6BD0(ai, 0);
        if (chosen)
        {
            return chosen;
        }
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi00_800C4D38(EnemyAi* ai)
{
    int chosen;
    UnitStatus* status = &ai->self_10->st_0;
    short hp = GetHp_800334D8(status);
    short maxHp = GetMaxHp_800334CC(status);
    if (hp < maxHp / 4)
    {
        chosen = AiUseSkill_800C6A8C(ai);
        if (chosen)
        {
            return chosen;
        }
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi09_800C4DB8(EnemyAi* ai)
{
    int chosen;
    int roll = rand() % 100;
    if (roll < 50)
    {
        chosen = AiCastMagic_800C6BD0(ai, 9);
        if (chosen)
        {
            return chosen;
        }
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi07_800C4E34(EnemyAi* ai)
{
    int chosen;
    if (rand() % 10 < 7)
    {
        chosen = AiUseSkill_800C6A8C(ai);
        if (chosen)
        {
            return chosen;
        }
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi0A_800C4EA8(EnemyAi* ai)
{
    int chosen;
    int roll = rand() % 100;
    if (aiCounter_800C8B30[0] < 2)
    {
        if (TargetHasStatus_800C6EC8(ai, 2) == 0 && roll < 40)
        {
            chosen = AiCastMagic_800C6BD0(ai, 0x12);
            if (chosen)
            {
                return chosen;
            }
            aiCounter_800C8B30[0]++;
        }
        if (TargetHasStatus_800C6EC8(ai, 2) == 0 && roll < 40)
        {
            chosen = AiUseSkill_800C6A8C(ai);
            if (chosen)
            {
                return chosen;
            }
            aiCounter_800C8B30[0]++;
        }
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi1A_800C4FA8(EnemyAi* ai)
{
    int chosen = AiCastMagic_800C6BD0(ai, 4);
    if (chosen == 0)
    {
        chosen = AiAttack_800C6A68(ai);
    }
    return chosen;
}

int EnemyAi03_800C4FE0(EnemyAi* ai)
{
    int chosen;
    if (IsTargetWeakToMagic_800C6EE4(ai))
    {
        chosen = AiCastMagic_800C6BD0(ai, 7);
        if (chosen)
        {
            return chosen;
        }
    }
    chosen = AiUseSkill_800C6A8C(ai);
    if (chosen)
    {
        return chosen;
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi0E_800C5034(EnemyAi* ai)
{
    int chosen;
    if (TargetHasStatus_800C6EC8(ai, 0x3F8) == 0)
    {
        chosen = AiUseSkill_800C6A8C(ai);
        if (chosen)
        {
            return chosen;
        }
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi13_800C507C(EnemyAi* ai)
{
    int chosen = AiUseSkill_800C6A8C(ai);
    if (chosen == 0)
    {
        chosen = AiAttack_800C6A68(ai);
    }
    return chosen;
}

int EnemyAi17_800C50B0(EnemyAi* ai)
{
    int chosen;
    UnitStatus* status = &ai->self_10->st_0;
    short hp;
    short maxHp;
    if (GetAreaElement_800BC868() == 3 || GetAreaElement_800BC868() == -1)
    {
        chosen = AiCastMagic_800C6BD0(ai, 0x17);
        if (chosen)
        {
            return chosen;
        }
    }
    if (rand() % 10 < 6)
    {
        chosen = AiCastMagic_800C6BD0(ai, 6);
        if (chosen)
        {
            return chosen;
        }
    }
    hp = GetHp_800334D8(status);
    maxHp = GetMaxHp_800334CC(status);
    if (hp <= (short)(maxHp / 3) && (rand() & 1))
    {
        chosen = AiFlee_800C6C58(ai);
        if (chosen)
        {
            return chosen;
        }
    }
    return AiDefend_800C6C44(ai);
}

int EnemyAi1B_800C51D8(EnemyAi* ai)
{
    int chosen;
    if (rand() & 1)
    {
        chosen = AiUseSkill_800C6A8C(ai);
    }
    else
    {
        chosen = AiAttack_800C6A68(ai);
    }
    return chosen;
}

int EnemyAiUnused_800C5220(EnemyAi* ai)
{
    UnitStatus* status = ai->target_14;
    int chosen = AiHealWeakAlly_800C6DF8(ai, 0xD);
    if (chosen)
    {
        return chosen;
    }
    if ((short)GetHp_800334D8(status) != 1)
    {
        chosen = AiUseSkill_800C6A8C(ai);
        if (chosen)
        {
            return chosen;
        }
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi15_800C5290(EnemyAi* ai)
{
    int chosen;
    if (rand() % 10 < 6)
    {
        chosen = AiCastMagic_800C6BD0(ai, 2);
        if (chosen)
        {
            return chosen;
        }
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi10_800C5304(EnemyAi* ai)
{
    int chosen;
    if (TargetHasStatus_800C6EC8(ai, 1) == 0 && rand() % 10 < 7)
    {
        chosen = AiCastMagic_800C6BD0(ai, 0x11);
        if (chosen)
        {
            return chosen;
        }
    }
    if (rand() & 1)
    {
        chosen = AiUseSkill_800C6A8C(ai);
        if (chosen)
        {
            return chosen;
        }
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi1C_800C53B0(EnemyAi* ai)
{
    int chosen;
    if (rand() % 10 < 6)
    {
        chosen = AiCastMagic_800C6BD0(ai, 5);
        if (chosen)
        {
            return chosen;
        }
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi0D_800C5424(EnemyAi* ai)
{
    int chosen;
    UnitStatus* status = &ai->self_10->st_0;
    short hp = GetHp_800334D8(status);
    short maxHp = GetMaxHp_800334CC(status);
    if (hp <= maxHp / 2)
    {
        chosen = AiUseSkill_800C6A8C(ai);
        if (chosen)
        {
            return chosen;
        }
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi02_800C54A4(EnemyAi* ai)
{
    int chosen;
    if (GetAreaElement_800BC868() == 1 || GetAreaElement_800BC868() == -1)
    {
        chosen = AiCastMagic_800C6BD0(ai, 0x15);
        if (chosen)
        {
            return chosen;
        }
    }
    chosen = AiUseSkill_800C6A8C(ai);
    if (chosen)
    {
        return chosen;
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi0B_800C5510(EnemyAi* ai)
{
    int chosen;
    if (AiCastMagic_800C6BD0(ai, 8) == 0)
    {
        return AiFlee_800C6C58(ai);
    }
    chosen = rand() & 1;
    if (chosen)
    {
        return chosen;
    }
    if (GetMp_800334F0(ai->target_14) != 0)
    {
        chosen = AiUseSkill_800C6A8C(ai);
        if (chosen)
        {
            return chosen;
        }
    }
    chosen = AiAttack_800C6A68(ai);
    if (chosen)
    {
        return chosen;
    }
    return AiFlee_800C6C58(ai);
}

int EnemyAi14_800C5594(EnemyAi* ai)
{
    int chosen;
    if (rand() % 10 < 7)
    {
        chosen = AiUseSkill_800C6A8C(ai);
        if (chosen)
        {
            return chosen;
        }
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi16_800C5608(EnemyAi* ai)
{
    int chosen;
    if (GetAreaElement_800BC868() == 0 || GetAreaElement_800BC868() == -1)
    {
        chosen = AiCastMagic_800C6BD0(ai, 0x16);
        if (chosen)
        {
            return chosen;
        }
    }
    chosen = AiUseSkill_800C6A8C(ai);
    if (chosen)
    {
        return chosen;
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi18_800C5670(EnemyAi* ai)
{
    int chosen;
    if (TargetHasStatus_800C6EC8(ai, 0x3F8) == 0)
    {
        chosen = AiCastMagic_800C6BD0(ai, 0x13);
        if (chosen)
        {
            return chosen;
        }
    }
    return AiDefend_800C6C44(ai);
}

int EnemyAi05_800C56B8(EnemyAi* ai)
{
    int chosen = AiCastMagic_800C6BD0(ai, 0xB);
    if (chosen)
    {
        return chosen;
    }
    chosen = AiUseSkill_800C6A8C(ai);
    if (chosen)
    {
        return chosen;
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi1D_800C5700(EnemyAi* ai)
{
    int chosen;
    if (GetAreaElement_800BC868() == 2 || GetAreaElement_800BC868() == -1)
    {
        chosen = AiCastMagic_800C6BD0(ai, 0x18);
        if (chosen)
        {
            return chosen;
        }
    }
    chosen = AiUseSkill_800C6A8C(ai);
    if (chosen)
    {
        return chosen;
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi19_800C576C(EnemyAi* ai)
{
    int chosen;
    if (GetAreaElement_800BC868() == 3 || GetAreaElement_800BC868() == -1)
    {
        chosen = AiCastMagic_800C6BD0(ai, 0x17);
        if (chosen)
        {
            return chosen;
        }
    }
    chosen = AiUseSkill_800C6A8C(ai);
    if (chosen)
    {
        return chosen;
    }
    return AiAttack_800C6A68(ai);
}

int EnemyAi04_800C57D8(EnemyAi* ai)
{
    int chosen = AiUseSkill_800C6A8C(ai);
    if (chosen == 0)
    {
        chosen = AiAttack_800C6A68(ai);
    }
    return chosen;
}

int EnemyAi08_800C580C(EnemyAi* ai)
{
    int chosen = AiUseSkill_800C6A8C(ai);
    if (chosen == 0)
    {
        chosen = AiAttack_800C6A68(ai);
    }
    return chosen;
}

int EnemyAi1F_800C5840(EnemyAi* ai)
{
    int chosen = AiUseSkill_800C6A8C(ai);
    if (chosen == 0)
    {
        chosen = AiAttack_800C6A68(ai);
    }
    return chosen;
}

int EnemyAi1E_800C5874(EnemyAi* ai)
{
    int chosen = AiCastMagic_800C6BD0(ai, 0x14);
    if (chosen == 0)
    {
        chosen = AiAttack_800C6A68(ai);
    }
    return chosen;
}

void EnemyAiDefend_800C58AC(EnemyAi* ai)
{
    ai->cmd_8->kind_0 = 0x12;
}

void BossAi0A_800C58BC(EnemyAi* ai)
{
    unsigned char phase = aiCounter_800C8B30[0] % 6;
    switch (phase)
    {
    case 0:
        ai->cmd_8->kind_0 = 6;
        ai->cmd_8->arg_4 = 2;
        ai->cmd_8->targets_C = ai->targetMask_18;
        break;
    case 2:
        ai->cmd_8->kind_0 = 6;
        ai->cmd_8->arg_4 = 3;
        ai->cmd_8->targets_C = ai->targetMask_18;
        break;
    case 4:
        ai->cmd_8->kind_0 = 6;
        ai->cmd_8->arg_4 = 1;
        ai->cmd_8->targets_C = ai->targetMask_18;
        break;
    case 1:
    case 3:
    case 5:
        ai->cmd_8->kind_0 = 0;
        ai->cmd_8->targets_C = ai->targetMask_18;
        break;
    }
    aiCounter_800C8B30[0]++;
}

const char aAttackWithReadi_800B68AC[] = "\202`\202\224\202\224\202\201\202\203\202\213\201@\202\227\202\211\202\224\202\210\201@\202\222\202\205\202\201\202\204\202\211\202\205\202\204\201@\202\227\202\205\202\201\202\220\202\217\202\216"; // Attack with readied weapon
const char aDefendToReduceD_800B68E4[] = "\202c\202\205\202\206\202\205\202\216\202\204\201@\202\224\202\217\201@\202\222\202\205\202\204\202\225\202\203\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205"; // Defend to reduce damage
const char aSummonDivineMin_800B6914[] = "\202r\202\225\202\215\202\215\202\217\202\216\201@\202c\202\211\202\226\202\211\202\216\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216"; // Summon Divine Minion
const char aCaptureMinionIn_800B6940[] = "\202b\202\201\202\220\202\224\202\225\202\222\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202\211\202\216\202\224\202\217\201@\202d\202\215\202\220\202\224\202\231\201@\202b\202\217\202\203\202\217\202\217\202\216\201D"; // Capture Minion into Empty Cocoon.
const char aUseItem_800B6984[] = "\202t\202\223\202\205\201@\202h\202\224\202\205\202\215"; // Use Item
const char aFleeFromCombat_800B6998[] = "\202e\202\214\202\205\202\205\201@\202\206\202\222\202\217\202\215\201@\202\203\202\217\202\215\202\202\202\201\202\224"; // Flee from combat
const char aUseNormalAttack_800B69BC[] = "\202t\202\223\202\205\201@\202\216\202\217\202\222\202\215\202\201\202\214\201@\202\201\202\224\202\224\202\201\202\203\202\213"; // Use normal attack
const char aUseSpecialAttac_800B69E0[] = "\202t\202\223\202\205\201@\202\223\202\220\202\205\202\203\202\211\202\201\202\214\201@\202\201\202\224\202\224\202\201\202\203\202\213"; // Use special attack
const char aUseMagicSpell_800B6A08[] = "\202t\202\223\202\205\201@\202\215\202\201\202\207\202\211\202\203\201@\202\223\202\220\202\205\202\214\202\214"; // Use magic spell
const char aChangeCurrentFi_800B6A28[] = "\202b\202\210\202\201\202\216\202\207\202\205\201@\202\203\202\225\202\222\202\222\202\205\202\216\202\224\201@\202\206\202\211\202\207\202\210\202\224\202\205\202\222"; // Change current fighter
const char aNoDivineMinions_800B6A58[] = "\202m\202\217\201@\202c\202\211\202\226\202\211\202\216\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\202\223\201@\202\222\202\205\202\201\202\204\202\231"; // No Divine Minions ready
const char aCannotSummonInt_800B6A88[] = "\202b\202\201\202\216\202\216\202\217\202\224\201@\202\223\202\225\202\215\202\215\202\217\202\216\201@\202\211\202\216\202\224\202\217\201@\202\203\202\217\202\215\202\202\202\201\202\224"; // Cannot summon into combat
const char aNotEnoughMana_800B6ABC[] = "\202m\202\217\202\224\201@\202\205\202\216\202\217\202\225\202\207\202\210\201@\202l\202\201\202\216\202\201"; // Not enough Mana
const char aCannotCapture_800B6ADC[] = "\202b\202\201\202\216\202\216\202\217\202\224\201@\202\203\202\201\202\220\202\224\202\225\202\222\202\205"; // Cannot capture
const char aNoEmptyCocoons_800B6AFC[] = "\202m\202\217\201@\202\205\202\215\202\220\202\224\202\231\201@\202\203\202\217\202\203\202\217\202\217\202\216\202\223"; // No empty cocoons
const char aCannotEscape_800B6B20[] = "\202b\202\201\202\216\202\216\202\217\202\224\201@\202\205\202\223\202\203\202\201\202\220\202\205"; // Cannot escape
const char aNoNeedToUseItem_800B6B3C[] = "\202m\202\217\201@\202\216\202\205\202\205\202\204\201@\202\224\202\217\201@\202\225\202\223\202\205\201@\202\211\202\224\202\205\202\215"; // No need to use item
const char aCannotSelect_800B6B64[] = "\202b\202\201\202\216\202\216\202\217\202\224\201@\202\223\202\205\202\214\202\205\202\203\202\224"; // Cannot select
const char aThisItemIsForDi_800B6B80[] = "\202s\202\210\202\211\202\223\201@\202\211\202\224\202\205\202\215\201@\202\211\202\223\201@\202\206\202\217\202\222\201@\202c\202\211\202\226\202\211\202\216\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\202\223"; // This item is for Divine Minions
const char aDivineMinionsCa_800B6BC0[] = "\202c\202\211\202\226\202\211\202\216\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\202\223\201@\202\203\202\201\202\216\202\216\202\217\202\224\201@\202\225\202\223\202\205\201@\202\224\202\210\202\211\202\223\201@\202\211\202\224\202\205\202\215"; // Divine Minions cannot use this item
const char aCannotUseHere_800B6C08[] = "\202b\202\201\202\216\202\216\202\217\202\224\201@\202\225\202\223\202\205\201@\202\210\202\205\202\222\202\205"; // Cannot use here
const char aAttractsNearbyM_800B6C28[] = "\202`\202\224\202\224\202\222\202\201\202\203\202\224\202\223\201@\202\216\202\205\202\201\202\222\202\202\202\231\201@\202\215\202\211\202\216\202\211\202\217\202\216\202\223\201D"; // Attracts nearby minions.
const char aTreeSporesWithA_800B6C5C[] = "\202s\202\222\202\205\202\205\201@\202\223\202\220\202\217\202\222\202\205\202\223\201@\202\227\202\211\202\224\202\210\201@\202\201\201@\202\203\202\201\202\220\202\224\202\211\202\226\202\201\202\224\202\211\202\216\202\207\201@\202\223\202\203\202\205\202\216\202\224\201D"; // Tree spores with a captivating scent.
const char aCausesSurroundi_800B6CA8[] = "\202b\202\201\202\225\202\223\202\205\202\223\201@\202\223\202\225\202\222\202\222\202\217\202\225\202\216\202\204\202\211\202\216\202\207\201@\202l\202\211\202\216\202\211\202\217\202\216\202\223\201@\202\224\202\217\201@\202\206\202\201\202\214\202\214\201@\202\201\202\223\202\214\202\205\202\205\202\220\201D"; // Causes surrounding Minions to fall asleep.
const char aSweetSmellingSl_800B6D00[] = "\202r\202\227\202\205\202\205\202\224\201|\202\223\202\215\202\205\202\214\202\214\202\211\202\216\202\207\201C\201@\202\223\202\214\202\205\202\205\202\220\201|\202\211\202\216\202\204\202\225\202\203\202\211\202\216\202\207\201@\202\223\202\220\202\217\202\222\202\205\202\223\201@\202\206\202\222\202\217\202\215\201@\202\201\201@\202\224\202\222\202\205\202\205\201D"; // Sweet-smelling, sleep-inducing spores from a tree.
const char aTreeSpores_800B6D68[] = "\202s\202\222\202\205\202\205\201@\202r\202\220\202\217\202\222\202\205\202\223"; // Tree Spores
const char aBendsAndBecomes_800B6D80[] = "\202a\202\205\202\216\202\204\202\223\201@\202\201\202\216\202\204\201@\202\202\202\205\202\203\202\217\202\215\202\205\202\223\201@\202\227\202\217\202\222\202\224\202\210\202\214\202\205\202\223\202\223\201@\202\201\202\206\202\224\202\205\202\222\201@\202\217\202\216\202\205\201@\202\225\202\223\202\205\201D"; // Bends and becomes worthless after one use.
const char aMultipurposeKey_800B6DD8[] = "\202l\202\225\202\214\202\224\202\211\202\220\202\225\202\222\202\220\202\217\202\223\202\205\201@\202\213\202\205\202\231\201@\202\206\202\217\202\222\201@\202\217\202\220\202\205\202\216\202\211\202\216\202\207\201@\202f\202\205\202\210\202\205\202\216\202\201\201@\202o\202\201\202\214\202\205\201@\202\203\202\210\202\205\202\223\202\224\202\223\201D"; // Multipurpose key for opening Gehena Pale chests.
const char aKeyToTreasureCh_800B6E3C[] = "\202j\202\205\202\231\201@\202\224\202\217\201@\202s\202\222\202\205\202\201\202\223\202\225\202\222\202\205\201@\202b\202\210\202\205\202\223\202\224\202\223"; // Key to Treasure Chests
const char aHighestGradeBes_800B6E6C[] = "\202g\202\211\202\207\202\210\202\205\202\223\202\224\201|\202\207\202\222\202\201\202\204\202\205\201C\201@\202\202\202\205\202\223\202\224\201|\202\221\202\225\202\201\202\214\202\211\202\224\202\231\201@\202\223\202\211\202\214\202\213\201D"; // Highest-grade, best-quality silk.
const char aSoftThreadThatG_800B6EB0[] = "\202r\202\217\202\206\202\224\201@\202\224\202\210\202\222\202\205\202\201\202\204\201@\202\224\202\210\202\201\202\224\201@\202\207\202\211\202\226\202\205\202\223\201@\202\217\202\206\202\206\201@\202\201\201@\202\207\202\217\202\204\202\214\202\231\201@\202\214\202\211\202\207\202\210\202\224\201D"; // Soft thread that gives off a godly light.
const char aSecondHighestGr_800B6F04[] = "\202r\202\205\202\203\202\217\202\216\202\204\201|\202\210\202\211\202\207\202\210\202\205\202\223\202\224\201@\202\207\202\222\202\201\202\204\202\205\201@\202\217\202\206\201@\202\223\202\211\202\214\202\213\201D"; // Second-highest grade of silk.
const char aGivesOffAnUnear_800B6F40[] = "\202f\202\211\202\226\202\205\202\223\201@\202\217\202\206\202\206\201@\202\201\202\216\201@\202\225\202\216\202\205\202\201\202\222\202\224\202\210\202\214\202\231\201@\202\202\202\222\202\211\202\214\202\214\202\211\202\201\202\216\202\224\201@\202\223\202\210\202\211\202\216\202\205\201D"; // Gives off an unearthly brilliant shine.
const char aThirdHighestGra_800B6F90[] = "\202s\202\210\202\211\202\222\202\204\201|\202\210\202\211\202\207\202\210\202\205\202\223\202\224\201@\202\207\202\222\202\201\202\204\202\205\201@\202\217\202\206\201@\202\223\202\211\202\214\202\213\201D"; // Third-highest grade of silk.
const char aGivesOffAPhosph_800B6FCC[] = "\202f\202\211\202\226\202\205\202\223\201@\202\217\202\206\202\206\201@\202\201\201@\202\220\202\210\202\217\202\223\202\220\202\210\202\217\202\222\202\205\202\223\202\203\202\205\202\216\202\224\201@\202\227\202\210\202\211\202\224\202\205\201@\202\223\202\210\202\211\202\216\202\205\201D"; // Gives off a phosphorescent white shine.
const char aFourthHighestGr_800B701C[] = "\202e\202\217\202\225\202\222\202\224\202\210\201|\202\210\202\211\202\207\202\210\202\205\202\223\202\224\201@\202\207\202\222\202\201\202\204\202\205\201@\202\217\202\206\201@\202\223\202\211\202\214\202\213\201D"; // Fourth-highest grade of silk.
const char aGivesOffAModera_800B7058[] = "\202f\202\211\202\226\202\205\202\223\201@\202\217\202\206\202\206\201@\202\201\201@\202\215\202\217\202\204\202\205\202\222\202\201\202\224\202\205\201C\201@\202\203\202\214\202\205\202\201\202\222\201@\202\223\202\210\202\211\202\216\202\205\201D"; // Gives off a moderate, clear shine.
const char aFifthHighestGra_800B70A0[] = "\202e\202\211\202\206\202\224\202\210\201|\202\210\202\211\202\207\202\210\202\205\202\223\202\224\201@\202\207\202\222\202\201\202\204\202\205\201@\202\217\202\206\201@\202\223\202\211\202\214\202\213\201D"; // Fifth-highest grade of silk.
const char aGivesOffADazzli_800B70DC[] = "\202f\202\211\202\226\202\205\202\223\201@\202\217\202\206\202\206\201@\202\201\201@\202\204\202\201\202\232\202\232\202\214\202\211\202\216\202\207\201@\202\223\202\210\202\211\202\216\202\205\201D"; // Gives off a dazzling shine.
const char aSixthHighestGra_800B7114[] = "\202r\202\211\202\230\202\224\202\210\201|\202\210\202\211\202\207\202\210\202\205\202\223\202\224\201@\202\207\202\222\202\201\202\204\202\205\201@\202\217\202\206\201@\202\223\202\211\202\214\202\213\201D"; // Sixth-highest grade of silk.
const char aEmitsVagueInsta_800B7150[] = "\202d\202\215\202\211\202\224\202\223\201@\202\226\202\201\202\207\202\225\202\205\201C\201@\202\211\202\216\202\223\202\224\202\201\202\216\202\224\202\201\202\216\202\205\202\217\202\225\202\223\201@\202\206\202\214\202\201\202\223\202\210\202\205\202\223\201@\202\217\202\206\201@\202\214\202\211\202\207\202\210\202\224\201D"; // Emits vague, instantaneous flashes of light.
const char aSeventhHighestG_800B71AC[] = "\202r\202\205\202\226\202\205\202\216\202\224\202\210\201|\202\210\202\211\202\207\202\210\202\205\202\223\202\224\201@\202\207\202\222\202\201\202\204\202\205\201@\202\217\202\206\201@\202\223\202\211\202\214\202\213\201D"; // Seventh-highest grade of silk.
const char aGivesOffAShineT_800B71EC[] = "\202f\202\211\202\226\202\205\202\223\201@\202\217\202\206\202\206\201@\202\201\201@\202\223\202\210\202\211\202\216\202\205\201@\202\224\202\210\202\201\202\224\201@\202\207\202\222\202\201\202\202\202\223\201@\202\231\202\217\202\225\202\222\201@\202\201\202\224\202\224\202\205\202\216\202\224\202\211\202\217\202\216\201D"; // Gives off a shine that grabs your attention.
const char aSilkThreadSpunF_800B7248[] = "\202r\202\211\202\214\202\213\201@\202\224\202\210\202\222\202\205\202\201\202\204\201@\202\223\202\220\202\225\202\216\201@\202\206\202\222\202\217\202\215\201@\202\201\201@\202\227\202\210\202\211\202\224\202\205\201@\202\203\202\217\202\203\202\217\202\217\202\216\201D"; // Silk thread spun from a white cocoon.
const char aInflictsAWindBa_800B7294[] = "\202h\202\216\202\206\202\214\202\211\202\203\202\224\202\223\201@\202\201\201@\202v\202\211\202\216\202\204\201|\202\202\202\201\202\223\202\205\202\204\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\217\202\216\201@\202\215\202\225\202\214\202\224\202\211\202\220\202\214\202\205\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Inflicts a Wind-based attack on multiple enemies.
const char aAttackMultipleE_800B72F8[] = "\202`\202\224\202\224\202\201\202\203\202\213\201@\202l\202\225\202\214\202\224\202\211\202\220\202\214\202\205\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\227\202\211\202\224\202\210\201@\202v\202\211\202\216\202\204"; // Attack Multiple Enemies with Wind
const char aInflictsAWindBa_800B733C[] = "\202h\202\216\202\206\202\214\202\211\202\203\202\224\202\223\201@\202\201\201@\202v\202\211\202\216\202\204\201|\202\202\202\201\202\223\202\205\202\204\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\217\202\216\201@\202\201\201@\202\223\202\211\202\216\202\207\202\214\202\205\201@\202\205\202\216\202\205\202\215\202\231\201D"; // Inflicts a Wind-based attack on a single enemy.
const char aSealWithTheMark_800B739C[] = "\202r\202\205\202\201\202\214\201@\202\227\202\211\202\224\202\210\201@\202\224\202\210\202\205\201@\202\215\202\201\202\222\202\213\201@\202\217\202\206\201@\202l\202\201\202\214\202\224\202\231\201C\201@\202\224\202\210\202\205\201@\202c\202\211\202\223\202\203\202\211\202\220\202\214\202\205\201@\202\217\202\206\201@\202v\202\211\202\216\202\204\201D"; // Seal with the mark of Malty, the Disciple of Wind.
const char aAttackSingleEne_800B7404[] = "\202`\202\224\202\224\202\201\202\203\202\213\201@\202r\202\211\202\216\202\207\202\214\202\205\201@\202d\202\216\202\205\202\215\202\231\201@\202\227\202\211\202\224\202\210\201@\202v\202\211\202\216\202\204"; // Attack Single Enemy with Wind
const char aInflictsAFireBa_800B7440[] = "\202h\202\216\202\206\202\214\202\211\202\203\202\224\202\223\201@\202\201\201@\202e\202\211\202\222\202\205\201|\202\202\202\201\202\223\202\205\202\204\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\217\202\216\201@\202\201\202\214\202\214\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Inflicts a Fire-based attack on all enemies.
const char aAttackAllEnemie_800B749C[] = "\202`\202\224\202\224\202\201\202\203\202\213\201@\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\227\202\211\202\224\202\210\201@\202e\202\211\202\222\202\205"; // Attack All Enemies with Fire
const char aInflictsAFireBa_800B74D8[] = "\202h\202\216\202\206\202\214\202\211\202\203\202\224\202\223\201@\202\201\201@\202e\202\211\202\222\202\205\201|\202\202\202\201\202\223\202\205\202\204\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\217\202\216\201@\202\201\201@\202\223\202\211\202\216\202\207\202\214\202\205\201@\202\205\202\216\202\205\202\215\202\231\201D"; // Inflicts a Fire-based attack on a single enemy.
const char aSealWithTheMark_800B7538[] = "\202r\202\205\202\201\202\214\201@\202\227\202\211\202\224\202\210\201@\202\224\202\210\202\205\201@\202\215\202\201\202\222\202\213\201@\202\217\202\206\201@\202`\202\207\202\216\202\211\201C\201@\202\224\202\210\202\205\201@\202c\202\211\202\223\202\203\202\211\202\220\202\214\202\205\201@\202\217\202\206\201@\202e\202\211\202\222\202\205\201D"; // Seal with the mark of Agni, the Disciple of Fire.
const char aAttackSingleEne_800B759C[] = "\202`\202\224\202\224\202\201\202\203\202\213\201@\202r\202\211\202\216\202\207\202\214\202\205\201@\202d\202\216\202\205\202\215\202\231\201@\202\227\202\211\202\224\202\210\201@\202e\202\211\202\222\202\205"; // Attack Single Enemy with Fire
const char aInflictsAWaterB_800B75D8[] = "\202h\202\216\202\206\202\214\202\211\202\203\202\224\202\223\201@\202\201\201@\202v\202\201\202\224\202\205\202\222\201|\202\202\202\201\202\223\202\205\202\204\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\217\202\216\201@\202\201\202\214\202\214\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Inflicts a Water-based attack on all enemies.
const char aAttackAllEnemie_800B7634[] = "\202`\202\224\202\224\202\201\202\203\202\213\201@\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\227\202\211\202\224\202\210\201@\202v\202\201\202\224\202\205\202\222"; // Attack All Enemies with Water
const char aInflictsAWaterB_800B7670[] = "\202h\202\216\202\206\202\214\202\211\202\203\202\224\202\223\201@\202\201\201@\202v\202\201\202\224\202\205\202\222\201|\202\202\202\201\202\223\202\205\202\204\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\217\202\216\201@\202\201\201@\202\223\202\211\202\216\202\207\202\214\202\205\201@\202\205\202\216\202\205\202\215\202\231\201D"; // Inflicts a Water-based attack on a single enemy.
const char aSealWithTheMark_800B76D4[] = "\202r\202\205\202\201\202\214\201@\202\227\202\211\202\224\202\210\201@\202\224\202\210\202\205\201@\202\215\202\201\202\222\202\213\201@\202\217\202\206\201@\202u\202\201\202\222\202\231\201C\201@\202\224\202\210\202\205\201@\202c\202\211\202\223\202\203\202\211\202\220\202\214\202\205\201@\202\217\202\206\201@\202v\202\201\202\224\202\205\202\222\201D"; // Seal with the mark of Vary, the Disciple of Water.
const char aAttackSingleEne_800B773C[] = "\202`\202\224\202\224\202\201\202\203\202\213\201@\202r\202\211\202\216\202\207\202\214\202\205\201@\202d\202\216\202\205\202\215\202\231\201@\202\227\202\211\202\224\202\210\201@\202v\202\201\202\224\202\205\202\222"; // Attack Single Enemy with Water
const char aInflictsAnEarth_800B777C[] = "\202h\202\216\202\206\202\214\202\211\202\203\202\224\202\223\201@\202\201\202\216\201@\202d\202\201\202\222\202\224\202\210\201|\202\202\202\201\202\223\202\205\202\204\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\217\202\216\201@\202\201\202\214\202\214\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Inflicts an Earth-based attack on all enemies.
const char aAttackAllEnemie_800B77DC[] = "\202`\202\224\202\224\202\201\202\203\202\213\201@\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\227\202\211\202\224\202\210\201@\202d\202\201\202\222\202\224\202\210"; // Attack All Enemies with Earth
const char aInflictsAnEarth_800B7818[] = "\202h\202\216\202\206\202\214\202\211\202\203\202\224\202\223\201@\202\201\202\216\201@\202d\202\201\202\222\202\224\202\210\201|\202\202\202\201\202\223\202\205\202\204\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\217\202\216\201@\202\201\201@\202\223\202\211\202\216\202\207\202\214\202\205\201@\202\205\202\216\202\205\202\215\202\231\201D"; // Inflicts an Earth-based attack on a single enemy.
const char aSealWithTheMark_800B787C[] = "\202r\202\205\202\201\202\214\201@\202\227\202\211\202\224\202\210\201@\202\224\202\210\202\205\201@\202\215\202\201\202\222\202\213\201@\202\217\202\206\201@\202t\202\222\202\226\202\231\201C\201@\202\224\202\210\202\205\201@\202c\202\211\202\223\202\203\202\211\202\220\202\214\202\205\201@\202\217\202\206\201@\202d\202\201\202\222\202\224\202\210\201D"; // Seal with the mark of Urvy, the Disciple of Earth.
const char aAttackSingleEne_800B78E4[] = "\202`\202\224\202\224\202\201\202\203\202\213\201@\202r\202\211\202\216\202\207\202\214\202\205\201@\202d\202\216\202\205\202\215\202\231\201@\202\227\202\211\202\224\202\210\201@\202d\202\201\202\222\202\224\202\210"; // Attack Single Enemy with Earth
const char aChangesAreaProp_800B7924[] = "\202b\202\210\202\201\202\216\202\207\202\205\202\223\201@\202\201\202\222\202\205\202\201\201@\202\220\202\222\202\217\202\220\202\205\202\222\202\224\202\211\202\205\202\223\201@\202\224\202\217\201@\202\224\202\210\202\205\201@\202\201\202\204\202\226\202\201\202\216\202\224\202\201\202\207\202\205\201@\202\217\202\206\201@\202v\202\211\202\216\202\204\201D"; // Changes area properties to the advantage of Wind.
const char aACharmBlessedBy_800B7988[] = "\202`\201@\202\203\202\210\202\201\202\222\202\215\201@\202\202\202\214\202\205\202\223\202\223\202\205\202\204\201@\202\202\202\231\201@\202l\202\201\202\214\202\224\202\231\201C\201@\202\224\202\210\202\205\201@\202c\202\211\202\223\202\203\202\211\202\220\202\214\202\205\201@\202\217\202\206\201@\202v\202\211\202\216\202\204\201D"; // A charm blessed by Malty, the Disciple of Wind.
const char aChangesAreaProp_800B79E8[] = "\202b\202\210\202\201\202\216\202\207\202\205\202\223\201@\202\201\202\222\202\205\202\201\201@\202\220\202\222\202\217\202\220\202\205\202\222\202\224\202\211\202\205\202\223\201@\202\224\202\217\201@\202\224\202\210\202\205\201@\202\201\202\204\202\226\202\201\202\216\202\224\202\201\202\207\202\205\201@\202\217\202\206\201@\202e\202\211\202\222\202\205\201D"; // Changes area properties to the advantage of Fire.
const char aACharmBlessedBy_800B7A4C[] = "\202`\201@\202\203\202\210\202\201\202\222\202\215\201@\202\202\202\214\202\205\202\223\202\223\202\205\202\204\201@\202\202\202\231\201@\202`\202\207\202\216\202\211\201C\201@\202\224\202\210\202\205\201@\202c\202\211\202\223\202\203\202\211\202\220\202\214\202\205\201@\202\217\202\206\201@\202e\202\211\202\222\202\205\201D"; // A charm blessed by Agni, the Disciple of Fire.
const char aChangesAreaProp_800B7AAC[] = "\202b\202\210\202\201\202\216\202\207\202\205\202\223\201@\202\201\202\222\202\205\202\201\201@\202\220\202\222\202\217\202\220\202\205\202\222\202\224\202\211\202\205\202\223\201@\202\224\202\217\201@\202\224\202\210\202\205\201@\202\201\202\204\202\226\202\201\202\216\202\224\202\201\202\207\202\205\201@\202\217\202\206\201@\202v\202\201\202\224\202\205\202\222\201D"; // Changes area properties to the advantage of Water.
const char aACharmBlessedBy_800B7B14[] = "\202`\201@\202\203\202\210\202\201\202\222\202\215\201@\202\202\202\214\202\205\202\223\202\223\202\205\202\204\201@\202\202\202\231\201@\202u\202\201\202\222\202\231\201C\201@\202\224\202\210\202\205\201@\202c\202\211\202\223\202\203\202\211\202\220\202\214\202\205\201@\202\217\202\206\201@\202v\202\201\202\224\202\205\202\222\201D"; // A charm blessed by Vary, the Disciple of Water.
const char aChangesAreaProp_800B7B74[] = "\202b\202\210\202\201\202\216\202\207\202\205\202\223\201@\202\201\202\222\202\205\202\201\201@\202\220\202\222\202\217\202\220\202\205\202\222\202\224\202\211\202\205\202\223\201@\202\224\202\217\201@\202\224\202\210\202\205\201@\202\201\202\204\202\226\202\201\202\216\202\224\202\201\202\207\202\205\201@\202\217\202\206\201@\202d\202\201\202\222\202\224\202\210\201D"; // Changes area properties to the advantage of Earth.
const char aACharmBlessedBy_800B7BDC[] = "\202`\201@\202\203\202\210\202\201\202\222\202\215\201@\202\202\202\214\202\205\202\223\202\223\202\205\202\204\201@\202\202\202\231\201@\202t\202\222\202\226\202\231\201C\201@\202\224\202\210\202\205\201@\202c\202\211\202\223\202\203\202\211\202\220\202\214\202\205\201@\202\217\202\206\201@\202d\202\201\202\222\202\224\202\210\201D"; // A charm blessed by Urvy, the Disciple of Earth.
const char aChangeAreaPrope_800B7C3C[] = "\202b\202\210\202\201\202\216\202\207\202\205\201@\202`\202\222\202\205\202\201\201@\202o\202\222\202\217\202\220\202\205\202\222\202\224\202\211\202\205\202\223"; // Change Area Properties
const char aAllAbnormalStat_800B7C6C[] = "\202\201\202\214\202\214\201@\202\201\202\202\202\216\202\217\202\222\202\215\202\201\202\214\201@\202\223\202\224\202\201\202\224\202\205\202\223\201C\201@\202\202\202\225\202\224\201@\202\227\202\211\202\214\202\214\201@\202\202\202\222\202\205\202\201\202\213\201@\202\211\202\216\201@\202\224\202\210\202\205\201@\202\220\202\222\202\217\202\203\202\205\202\223\202\223\201D"; // all abnormal states, but will break in the process.
const char aReflectsAllUncl_800B7CD4[] = "\202q\202\205\202\206\202\214\202\205\202\203\202\224\202\223\201@\202\201\202\214\202\214\201@\202\225\202\216\202\203\202\214\202\205\202\201\202\216\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\202\223\201D\201@\202o\202\222\202\217\202\224\202\205\202\203\202\224\202\223\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224"; // Reflects all unclean elements. Protects against
const char aProtectionFromA_800B7D34[] = "\202o\202\222\202\217\202\224\202\205\202\203\202\224\202\211\202\217\202\216\201@\202\206\202\222\202\217\202\215\201@\202`\202\214\202\214"; // Protection from All
const char aInstantlyCauses_800B7D5C[] = "\202h\202\216\202\223\202\224\202\201\202\216\202\224\202\214\202\231\201@\202\203\202\201\202\225\202\223\202\205\202\223\201@\202\204\202\205\202\201\202\224\202\210\201@\202\202\202\231\201@\202\223\202\224\202\217\202\220\202\220\202\211\202\216\202\207\201@\202\224\202\210\202\205\201@\202\210\202\205\202\201\202\222\202\224\201D"; // Instantly causes death by stopping the heart.
const char aReleasesADeathM_800B7DB8[] = "\202q\202\205\202\214\202\205\202\201\202\223\202\205\202\223\201@\202\201\201@\202\204\202\205\202\201\202\224\202\210\201@\202\215\202\211\202\223\202\224\201@\202\227\202\210\202\205\202\216\201@\202\202\202\222\202\217\202\213\202\205\202\216\201D"; // Releases a death mist when broken.
const char aCauseDeath_800B7E00[] = "\202b\202\201\202\225\202\223\202\205\201@\202c\202\205\202\201\202\224\202\210"; // Cause Death
const char aCausesBodyHarde_800B7E18[] = "\202b\202\201\202\225\202\223\202\205\202\223\201@\202\202\202\217\202\204\202\231\201@\202\210\202\201\202\222\202\204\202\205\202\216\202\211\202\216\202\207\201@\202\223\202\224\202\201\202\222\202\224\202\211\202\216\202\207\201@\202\206\202\222\202\217\202\215\201@\202\224\202\210\202\205\201@\202\206\202\205\202\205\202\224\201D"; // Causes body hardening starting from the feet.
const char aReleasesAFleshT_800B7E74[] = "\202q\202\205\202\214\202\205\202\201\202\223\202\205\202\223\201@\202\201\201@\202\206\202\214\202\205\202\223\202\210\201@\202\224\202\217\201@\202\223\202\224\202\217\202\216\202\205\201@\202\215\202\211\202\223\202\224\201@\202\227\202\210\202\205\202\216\201@\202\202\202\222\202\217\202\213\202\205\202\216\201D"; // Releases a flesh to stone mist when broken.
const char aFleshToStone_800B7ECC[] = "\202e\202\214\202\205\202\223\202\210\201@\202\224\202\217\201@\202r\202\224\202\217\202\216\202\205"; // Flesh to Stone
const char aCausesADeepSlum_800B7EEC[] = "\202b\202\201\202\225\202\223\202\205\202\223\201@\202\201\201@\202\204\202\205\202\205\202\220\201@\202\223\202\214\202\225\202\215\202\202\202\205\202\222\201@\202\205\202\221\202\225\202\201\202\214\201@\202\224\202\217\201@\202\224\202\210\202\201\202\224\201@\202\217\202\206\201@\202\223\202\214\202\205\202\205\202\220\201@\202\223\202\220\202\217\202\222\202\205\202\223\201D"; // Causes a deep slumber equal to that of sleep spores.
const char aReleasesASleepM_800B7F58[] = "\202q\202\205\202\214\202\205\202\201\202\223\202\205\202\223\201@\202\201\201@\202\223\202\214\202\205\202\205\202\220\201@\202\215\202\211\202\223\202\224\201@\202\227\202\210\202\205\202\216\201@\202\202\202\222\202\217\202\213\202\205\202\216\201D"; // Releases a sleep mist when broken.
const char aInduceSleep_800B7FA0[] = "\202h\202\216\202\204\202\225\202\203\202\205\201@\202r\202\214\202\205\202\205\202\220"; // Induce Sleep
const char aInstantlyCauses_800B7FBC[] = "\202h\202\216\202\223\202\224\202\201\202\216\202\224\202\214\202\231\201@\202\203\202\201\202\225\202\223\202\205\202\223\201@\202\205\202\230\202\203\202\222\202\225\202\203\202\211\202\201\202\224\202\211\202\216\202\207\201@\202\220\202\201\202\211\202\216\201D"; // Instantly causes excruciating pain.
const char aReleasesPoisonM_800B8004[] = "\202q\202\205\202\214\202\205\202\201\202\223\202\205\202\223\201@\202\220\202\217\202\211\202\223\202\217\202\216\201@\202\215\202\211\202\223\202\224\201@\202\227\202\210\202\205\202\216\201@\202\202\202\222\202\217\202\213\202\205\202\216\201D"; // Releases poison mist when broken.
const char aSprayPoison_800B8048[] = "\202r\202\220\202\222\202\201\202\231\201@\202o\202\217\202\211\202\223\202\217\202\216"; // Spray Poison
const char aInnerStrengthTo_800B8064[] = "\202\211\202\216\202\216\202\205\202\222\201@\202\223\202\224\202\222\202\205\202\216\202\207\202\224\202\210\201@\202\224\202\217\201@\202\224\202\225\202\222\202\216\201@\202\223\202\224\202\217\202\216\202\205\201@\202\202\202\201\202\203\202\213\201@\202\211\202\216\202\224\202\217\201@\202\206\202\214\202\205\202\223\202\210\201D"; // inner strength to turn stone back into flesh.
const char aPowderMadeFromS_800B80C0[] = "\202o\202\217\202\227\202\204\202\205\202\222\201@\202\215\202\201\202\204\202\205\201@\202\206\202\222\202\217\202\215\201@\202\223\202\225\202\216\201|\202\204\202\222\202\211\202\205\202\204\201@\202\211\202\213\202\201\202\222\202\211\201@\202\210\202\205\202\222\202\202\201D\201@\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223"; // Powder made from sun-dried ikari herb. Increases
const char aStoneToFlesh_800B8124[] = "\202r\202\224\202\217\202\216\202\205\201@\202\224\202\217\201@\202e\202\214\202\205\202\223\202\210"; // Stone to Flesh
const char aSoothesTheSpiri_800B8144[] = "\202r\202\217\202\217\202\224\202\210\202\205\202\223\201@\202\224\202\210\202\205\201@\202\223\202\220\202\211\202\222\202\211\202\224\201@\202\201\202\216\202\204\201@\202\204\202\222\202\211\202\226\202\205\202\223\201@\202\217\202\225\202\224\201@\202\220\202\217\202\211\202\223\202\217\202\216\201D"; // Soothes the spirit and drives out poison.
const char aPowderedFormOfD_800B8198[] = "\202o\202\217\202\227\202\204\202\205\202\222\202\205\202\204\201@\202\206\202\217\202\222\202\215\201@\202\217\202\206\201@\202\204\202\222\202\211\202\205\202\204\201@\202\226\202\201\202\214\202\205\202\222\202\211\202\201\202\216\201@\202\222\202\217\202\217\202\224\201D"; // Powdered form of dried valerian root.
const char aPoisonAntidote_800B81E4[] = "\202o\202\217\202\211\202\223\202\217\202\216\201@\202`\202\216\202\224\202\211\202\204\202\217\202\224\202\205"; // Poison Antidote
const char aAdjustsTheVisce_800B8204[] = "\202`\202\204\202\212\202\225\202\223\202\224\202\223\201@\202\224\202\210\202\205\201@\202\226\202\211\202\223\202\203\202\205\202\222\202\201\201D"; // Adjusts the viscera.
const char aAlsoCalledTheIm_800B8230[] = "\202`\202\214\202\223\202\217\201@\202\203\202\201\202\214\202\214\202\205\202\204\201@\202\224\202\210\202\205\201@\202h\202\215\202\215\202\217\202\222\202\224\202\201\202\214\202\211\202\224\202\231\201@\202q\202\217\202\217\202\224\201D"; // Also called the Immortality Root.
const char aDriedRootOfAGre_800B8274[] = "\202c\202\222\202\211\202\205\202\204\201@\202\222\202\217\202\217\202\224\201@\202\217\202\206\201@\202\201\201@\202\207\202\222\202\205\202\201\202\224\201@\202\224\202\222\202\205\202\205\201@\202\206\202\222\202\217\202\215\201@\202\204\202\205\202\205\202\220\201@\202\211\202\216\201@\202\224\202\210\202\205\201@\202\206\202\217\202\222\202\205\202\223\202\224\201D"; // Dried root of a great tree from deep in the forest.
const char aTotalRestoratio_800B82DC[] = "\202s\202\217\202\224\202\201\202\214\201@\202q\202\205\202\223\202\224\202\217\202\222\202\201\202\224\202\211\202\217\202\216"; // Total Restoration
const char aRestoresAllMini_800B8300[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\202\223\201@\202\201\202\214\202\214\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202g\202o\201@\202\201\202\216\202\204\201@\202l\202\201\202\216\202\201\201D"; // Restores all Minion HP and Mana.
const char aSpecialLiquorMa_800B8344[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202\214\202\211\202\221\202\225\202\217\202\222\201@\202\215\202\201\202\204\202\205\201@\202\206\202\222\202\217\202\215\201@\202\220\202\211\202\203\202\213\202\214\202\205\202\204\201@\202r\202\210\202\201\202\202\201@\202l\202\211\202\216\202\211\202\217\202\216\201D"; // Special liquor made from pickled Shab Minion.
const char aRestoresAGreatD_800B83A0[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\202\223\201@\202\201\201@\202\207\202\222\202\205\202\201\202\224\201@\202\204\202\205\202\201\202\214\201@\202\217\202\206\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202g\202o\201@\202\201\202\216\202\204\201@\202l\202\201\202\216\202\201\201D"; // Restores a great deal of Minion HP and Mana.
const char aExcellentLiquor_800B83FC[] = "\202d\202\230\202\203\202\205\202\214\202\214\202\205\202\216\202\224\201@\202\214\202\211\202\221\202\225\202\217\202\222\201@\202\215\202\201\202\204\202\205\201@\202\206\202\222\202\217\202\215\201@\202\220\202\211\202\203\202\213\202\214\202\205\202\204\201@\202r\202\210\202\201\202\202\201@\202l\202\211\202\216\202\211\202\217\202\216\201D"; // Excellent liquor made from pickled Shab Minion.
const char aRestoresMinionH_800B845C[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\202\223\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202g\202o\201@\202\201\202\216\202\204\201@\202l\202\201\202\216\202\201\201@\202\224\202\217\201@\202\201\201@\202\203\202\205\202\222\202\224\202\201\202\211\202\216\201@\202\204\202\205\202\207\202\222\202\205\202\205\201D"; // Restores Minion HP and Mana to a certain degree.
const char aFineLiquorMadeF_800B84C0[] = "\202e\202\211\202\216\202\205\201@\202\214\202\211\202\221\202\225\202\217\202\222\201@\202\215\202\201\202\204\202\205\201@\202\206\202\222\202\217\202\215\201@\202\220\202\211\202\203\202\213\202\214\202\205\202\204\201@\202r\202\210\202\201\202\202\201@\202l\202\211\202\216\202\211\202\217\202\216\201D"; // Fine liquor made from pickled Shab Minion.
const char aRestoresSomeMin_800B8518[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\202\223\201@\202\223\202\217\202\215\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202g\202o\201@\202\201\202\216\202\204\201@\202l\202\201\202\216\202\201\201D"; // Restores some Minion HP and Mana.
const char aLiquorMadeFromP_800B855C[] = "\202k\202\211\202\221\202\225\202\217\202\222\201@\202\215\202\201\202\204\202\205\201@\202\206\202\222\202\217\202\215\201@\202\220\202\211\202\203\202\213\202\214\202\205\202\204\201@\202r\202\210\202\201\202\202\201@\202l\202\211\202\216\202\211\202\217\202\216\201D"; // Liquor made from pickled Shab Minion.
const char aRestoreMinionHP_800B85A8[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202g\202o\201@\202\201\202\216\202\204\201@\202l\202\201\202\216\202\201"; // Restore Minion HP and Mana
const char aStrengthensMini_800B85E0[] = "\202r\202\224\202\222\202\205\202\216\202\207\202\224\202\210\202\205\202\216\202\223\201@\202\215\202\211\202\216\202\211\202\217\202\216\201f\202\223\201@\202\223\202\220\202\211\202\222\202\211\202\224\201D"; // Strengthens minion's spirit.
const char aOilFromAPlantWi_800B861C[] = "\202n\202\211\202\214\201@\202\206\202\222\202\217\202\215\201@\202\201\201@\202\220\202\214\202\201\202\216\202\224\201@\202\227\202\211\202\224\202\210\201@\202\222\202\205\202\204\201@\202\206\202\214\202\217\202\227\202\205\202\222\202\223\201D"; // Oil from a plant with red flowers.
const char aIncreaseMinionM_800B8664[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202l\202\201\202\207\202\211\202\203\201@\202c\202\205\202\206\202\205\202\216\202\223\202\205"; // Increase Minion Magic Defense
const char aStrengthensMini_800B86A0[] = "\202r\202\224\202\222\202\205\202\216\202\207\202\224\202\210\202\205\202\216\202\223\201@\202\215\202\211\202\216\202\211\202\217\202\216\201f\202\223\201@\202\227\202\211\202\214\202\214\201D"; // Strengthens minion's will.
const char aOilFromTreeWith_800B86D8[] = "\202n\202\211\202\214\201@\202\206\202\222\202\217\202\215\201@\202\224\202\222\202\205\202\205\201@\202\227\202\211\202\224\202\210\201@\202\220\202\225\202\222\202\220\202\214\202\205\201@\202\202\202\214\202\217\202\223\202\223\202\217\202\215\202\223\201D"; // Oil from tree with purple blossoms.
const char aIncreaseMinionM_800B8720[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202l\202\201\202\207\202\211\202\203\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Increase Minion Magic Attack
const char aHardensMinionSS_800B875C[] = "\202g\202\201\202\222\202\204\202\205\202\216\202\223\201@\202\215\202\211\202\216\202\211\202\217\202\216\201f\202\223\201@\202\223\202\213\202\211\202\216\201D"; // Hardens minion's skin.
const char aOilFromAPlantWi_800B878C[] = "\202n\202\211\202\214\201@\202\206\202\222\202\217\202\215\201@\202\201\201@\202\220\202\214\202\201\202\216\202\224\201@\202\227\202\211\202\224\202\210\201@\202\227\202\210\202\211\202\224\202\205\201@\202\206\202\214\202\217\202\227\202\205\202\222\202\223\201D"; // Oil from a plant with white flowers.
const char aIncreaseMinionD_800B87D8[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202c\202\205\202\206\202\205\202\216\202\223\202\211\202\226\202\205\201@\202o\202\217\202\227\202\205\202\222"; // Increase Minion Defensive Power
const char aStrengthensMini_800B8818[] = "\202r\202\224\202\222\202\205\202\216\202\207\202\224\202\210\202\205\202\216\202\223\201@\202\215\202\211\202\216\202\211\202\217\202\216\201f\202\223\201@\202\214\202\205\202\207\202\223\201D"; // Strengthens minion's legs.
const char aOilFromAVeryPot_800B8850[] = "\202n\202\211\202\214\201@\202\206\202\222\202\217\202\215\201@\202\201\201@\202\226\202\205\202\222\202\231\201@\202\220\202\217\202\224\202\205\202\216\202\224\201@\202\220\202\214\202\201\202\216\202\224\201D"; // Oil from a very potent plant.
const char aIncreasesMinion_800B888C[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202r\202\220\202\205\202\205\202\204"; // Increases Minion Speed
const char aSharpensMinionS_800B88BC[] = "\202r\202\210\202\201\202\222\202\220\202\205\202\216\202\223\201@\202\215\202\211\202\216\202\211\202\217\202\216\201f\202\223\201@\202\203\202\214\202\201\202\227\202\223\201D"; // Sharpens minion's claws.
const char aOilFromATreeWit_800B88F0[] = "\202n\202\211\202\214\201@\202\206\202\222\202\217\202\215\201@\202\201\201@\202\224\202\222\202\205\202\205\201@\202\227\202\211\202\224\202\210\201@\202\223\202\210\202\201\202\222\202\220\201@\202\224\202\210\202\217\202\222\202\216\202\223\201D"; // Oil from a tree with sharp thorns.
const char aIncreaseMinionA_800B8938[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\202o\202\217\202\227\202\205\202\222"; // Increase Minion Attack Power
const char aStrengthensTheB_800B8974[] = "\202r\202\224\202\222\202\205\202\216\202\207\202\224\202\210\202\205\202\216\202\223\201@\202\224\202\210\202\205\201@\202\202\202\217\202\204\202\231\201@\202\201\202\216\202\204\201@\202\220\202\222\202\217\202\224\202\205\202\203\202\224\202\223\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\201\202\207\202\211\202\216\202\207\201D"; // Strengthens the body and protects against aging.
const char aANutPackingEner_800B89D8[] = "\202`\201@\202\216\202\225\202\224\201@\202\220\202\201\202\203\202\213\202\211\202\216\202\207\201@\202\205\202\216\202\205\202\222\202\207\202\231\201@\202\206\202\217\202\222\201@\202\223\202\220\202\222\202\217\202\225\202\224\202\211\202\216\202\207\201@\202\201\201@\202\216\202\205\202\227\201@\202\224\202\222\202\205\202\205\201D"; // A nut packing energy for sprouting a new tree.
const char aIncreaseMaxHeal_800B8A38[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\201@\202l\202\201\202\230\201@\202g\202\205\202\201\202\214\202\224\202\210"; // Increase Max Health
const char aBitterTasteThat_800B8A60[] = "\202\202\202\211\202\224\202\224\202\205\202\222\201@\202\224\202\201\202\223\202\224\202\205\201@\202\224\202\210\202\201\202\224\201@\202\205\202\214\202\225\202\204\202\205\202\223\201@\202\224\202\217\201@\202\211\202\224\202\223\201@\202\223\202\224\202\222\202\217\202\216\202\207\201@\202\203\202\225\202\222\202\211\202\216\202\207\201@\202\220\202\217\202\227\202\205\202\222\201D"; // bitter taste that eludes to its strong curing power.
const char aATypeOfMugwortW_800B8ACC[] = "\202`\201@\202\224\202\231\202\220\202\205\201@\202\217\202\206\201@\202\215\202\225\202\207\202\227\202\217\202\222\202\224\201@\202\227\202\211\202\224\202\210\201@\202\201\201@\202\222\202\205\202\201\202\214\202\214\202\231\201@\202\223\202\224\202\222\202\217\202\216\202\207\201@\202\223\202\215\202\205\202\214\202\214\201@\202\201\202\216\202\204"; // A type of mugwort with a really strong smell and
const char aCuresBleedingAn_800B8B30[] = "\202b\202\225\202\222\202\205\202\223\201@\202\202\202\214\202\205\202\205\202\204\202\211\202\216\202\207\201@\202\201\202\216\202\204\201@\202\222\202\205\202\204\202\225\202\203\202\205\202\223\201@\202\206\202\205\202\226\202\205\202\222\201D"; // Cures bleeding and reduces fever.
const char aSweeterSmelling_800B8B74[] = "\202\223\202\227\202\205\202\205\202\224\202\205\202\222\201@\202\223\202\215\202\205\202\214\202\214\202\211\202\216\202\207\201C\201@\202\201\202\216\202\204\201@\202\227\202\211\202\224\202\210\201@\202\206\202\225\202\232\202\232\202\211\202\205\202\222\201@\202\214\202\205\202\201\202\226\202\205\202\223\201D"; // sweeter smelling, and with fuzzier leaves.
const char aATypeOfMugwortB_800B8BCC[] = "\202`\201@\202\224\202\231\202\220\202\205\201@\202\217\202\206\201@\202\215\202\225\202\207\202\227\202\217\202\222\202\224\201C\201@\202\202\202\225\202\224\201@\202\223\202\215\202\201\202\214\202\214\202\205\202\222\201C"; // A type of mugwort, but smaller,
const char aGrindLeavesInto_800B8C0C[] = "\202f\202\222\202\211\202\216\202\204\201@\202\214\202\205\202\201\202\226\202\205\202\223\201@\202\211\202\216\202\224\202\217\201@\202\220\202\217\202\227\202\204\202\205\202\222\201@\202\201\202\216\202\204\201@\202\201\202\220\202\220\202\214\202\231\201@\202\224\202\217\201@\202\227\202\217\202\225\202\216\202\204\202\223\201D"; // Grind leaves into powder and apply to wounds.
const char aIncreasesHealth_800B8C68[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223\201@\202\210\202\205\202\201\202\214\202\224\202\210\201@\202\201\202\216\202\204\201@\202\223\202\214\202\217\202\227\202\223\201@\202\202\202\214\202\205\202\205\202\204\202\211\202\216\202\207\201D"; // Increases health and slows bleeding.
const char aGrowsInOpenArea_800B8CB4[] = "\202f\202\222\202\217\202\227\202\223\201@\202\211\202\216\201@\202\217\202\220\202\205\202\216\201@\202\201\202\222\202\205\202\201\202\223\201@\202\217\202\206\201@\202\224\202\210\202\205\201@\202\206\202\217\202\222\202\205\202\223\202\224\201D"; // Grows in open areas of the forest.
const char aRestoreHealth_800B8CFC[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\201@\202g\202\205\202\201\202\214\202\224\202\210"; // Restore Health
const char aEffectivenessOf_800B8D1C[] = "\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\202\216\202\205\202\223\202\223\201@\202\217\202\206\201@\202\205\202\201\202\222\202\224\202\210\201@\202\206\202\217\202\222\201@\202\204\202\225\202\222\202\201\202\224\202\211\202\217\202\216\201@\202\217\202\206\201@\202\202\202\201\202\224\202\224\202\214\202\205\201D"; // effectiveness of earth for duration of battle.
const char aIncreasesWindAt_800B8D7C[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223\201@\202\227\202\211\202\216\202\204\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\220\202\217\202\227\202\205\202\222\201@\202\201\202\216\202\204\201@\202\204\202\205\202\203\202\222\202\205\202\201\202\223\202\205\202\223"; // Increases wind attack power and decreases
const char aEnhanceWind_800B8DD0[] = "\202d\202\216\202\210\202\201\202\216\202\203\202\205\201@\202v\202\211\202\216\202\204"; // Enhance Wind
const char aEffectivenessOf_800B8DEC[] = "\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\202\216\202\205\202\223\202\223\201@\202\217\202\206\201@\202\227\202\201\202\224\202\205\202\222\201@\202\206\202\217\202\222\201@\202\204\202\225\202\222\202\201\202\224\202\211\202\217\202\216\201@\202\217\202\206\201@\202\202\202\201\202\224\202\224\202\214\202\205\201D"; // effectiveness of water for duration of battle.
const char aIncreasesEarthA_800B8E4C[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223\201@\202\205\202\201\202\222\202\224\202\210\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\220\202\217\202\227\202\205\202\222\201@\202\201\202\216\202\204\201@\202\204\202\205\202\203\202\222\202\205\202\201\202\223\202\205\202\223"; // Increases earth attack power and decreases
const char aEnhanceEarth_800B8EA4[] = "\202d\202\216\202\210\202\201\202\216\202\203\202\205\201@\202d\202\201\202\222\202\224\202\210"; // Enhance Earth
const char aEffectivenessOf_800B8EC0[] = "\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\202\216\202\205\202\223\202\223\201@\202\217\202\206\201@\202\206\202\211\202\222\202\205\201@\202\206\202\217\202\222\201@\202\204\202\225\202\222\202\201\202\224\202\211\202\217\202\216\201@\202\217\202\206\201@\202\202\202\201\202\224\202\224\202\214\202\205\201D"; // effectiveness of fire for duration of battle.
const char aIncreasesWaterA_800B8F1C[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223\201@\202\227\202\201\202\224\202\205\202\222\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\220\202\217\202\227\202\205\202\222\201@\202\201\202\216\202\204\201@\202\204\202\205\202\203\202\222\202\205\202\201\202\223\202\205\202\223"; // Increases water attack power and decreases
const char aEnhanceWater_800B8F74[] = "\202d\202\216\202\210\202\201\202\216\202\203\202\205\201@\202v\202\201\202\224\202\205\202\222"; // Enhance Water
const char aEffectivenessOf_800B8F90[] = "\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\202\216\202\205\202\223\202\223\201@\202\217\202\206\201@\202\227\202\211\202\216\202\204\201@\202\206\202\217\202\222\201@\202\204\202\225\202\222\202\201\202\224\202\211\202\217\202\216\201@\202\217\202\206\201@\202\202\202\201\202\224\202\224\202\214\202\205\201D"; // effectiveness of wind for duration of battle.
const char aIncreasesFireAt_800B8FEC[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223\201@\202\206\202\211\202\222\202\205\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\220\202\217\202\227\202\205\202\222\201@\202\201\202\216\202\204\201@\202\204\202\205\202\203\202\222\202\205\202\201\202\223\202\205\202\223"; // Increases fire attack power and decreases
const char aEnhanceFire_800B9040[] = "\202d\202\216\202\210\202\201\202\216\202\203\202\205\201@\202e\202\211\202\222\202\205"; // Enhance Fire
const char aCausesAnEnemyTo_800B905C[] = "\202b\202\201\202\225\202\223\202\205\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\224\202\217\201@\202\206\202\201\202\214\202\214\201@\202\204\202\205\202\201\202\204\201@\202\211\202\215\202\215\202\205\202\204\202\211\202\201\202\224\202\205\202\214\202\231\201D"; // Causes an enemy to fall dead immediately.
const char aDeath_800B90B0[] = "\202c\202\205\202\201\202\224\202\210"; // Death
const char aTurnsAnEnemyInt_800B90BC[] = "\202s\202\225\202\222\202\216\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\211\202\216\202\224\202\217\201@\202\223\202\224\202\217\202\216\202\205\201D"; // Turns an enemy into stone.
const char aPutsAnEnemyToSl_800B90F4[] = "\202o\202\225\202\224\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\224\202\217\201@\202\223\202\214\202\205\202\205\202\220\201D"; // Puts an enemy to sleep.
const char aSleep_800B9124[] = "\202r\202\214\202\205\202\205\202\220"; // Sleep
const char aPoisonsAnEnemy_800B9130[] = "\202o\202\217\202\211\202\223\202\217\202\216\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201D"; // Poisons an enemy.
const char aPoison_800B9154[] = "\202o\202\217\202\211\202\223\202\217\202\216"; // Poison
const char aEndsOnceItProte_800B9164[] = "\202d\202\216\202\204\202\223\201@\202\217\202\216\202\203\202\205\201@\202\211\202\224\201@\202\220\202\222\202\217\202\224\202\205\202\203\202\224\202\223\201@\202\203\202\201\202\223\202\224\202\205\202\222\201@\202\224\202\210\202\222\202\205\202\205\201@\202\224\202\211\202\215\202\205\202\223\201D"; // Ends once it protects caster three times.
const char aProtectsAgainst_800B91B8[] = "\202o\202\222\202\217\202\224\202\205\202\203\202\224\202\223\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\220\202\217\202\211\202\223\202\217\202\216\201C\201@\202\223\202\214\202\205\202\205\202\220\201C\201@\202\201\202\216\202\204\201@\202\206\202\214\202\205\202\223\202\210\201@\202\224\202\217\201@\202\223\202\224\202\217\202\216\202\205\201D"; // Protects against poison, sleep, and flesh to stone.
const char aProtection_800B9220[] = "\202o\202\222\202\217\202\224\202\205\202\203\202\224\202\211\202\217\202\216"; // Protection
const char aCuresPoisonAndT_800B9238[] = "\202b\202\225\202\222\202\205\202\223\201@\202\220\202\217\202\211\202\223\202\217\202\216\201@\202\201\202\216\202\204\201@\202\224\202\225\202\222\202\216\202\223\201@\202\223\202\224\202\217\202\216\202\205\201@\202\202\202\201\202\203\202\213\201@\202\224\202\217\201@\202\206\202\214\202\205\202\223\202\210\201D"; // Cures poison and turns stone back to flesh.
const char aReturnToNormal_800B9290[] = "\202q\202\205\202\224\202\225\202\222\202\216\201@\202\224\202\217\201@\202m\202\217\202\222\202\215\202\201\202\214"; // Return to Normal
const char aRestoresAllHP_800B92B4[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\202\223\201@\202\201\202\214\202\214\201@\202g\202o\201D"; // Restores all HP.
const char aRestoreAllHP_800B92D8[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\201@\202`\202\214\202\214\201@\202g\202o"; // Restore All HP
const char aRestoresSomeHP_800B92F8[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\202\223\201@\202\223\202\217\202\215\202\205\201@\202g\202o\201D"; // Restores some HP.
const char aRestoreHP_800B931C[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\201@\202g\202o"; // Restore HP
const char aCuresPoison_800B9334[] = "\202b\202\225\202\222\202\205\202\223\201@\202\220\202\217\202\211\202\223\202\217\202\216\201D"; // Cures poison.
const char aCurePoison_800B9350[] = "\202b\202\225\202\222\202\205\201@\202o\202\217\202\211\202\223\202\217\202\216"; // Cure Poison
const char aAdvancedWindAtt_800B9368[] = "\202`\202\204\202\226\202\201\202\216\202\203\202\205\202\204\201@\202v\202\211\202\216\202\204\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Advanced Wind Attack
const char aWindAttackAllEn_800B9394[] = "\202v\202\211\202\216\202\204\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201j"; // Wind Attack (All Enemies)
const char aHigherWindEleme_800B93C8[] = "\202g\202\211\202\207\202\210\202\205\202\222\201@\202\227\202\211\202\216\202\204\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\201@\202\222\202\201\202\224\202\211\202\217\201@\202\231\202\211\202\205\202\214\202\204\202\223\201@\202\215\202\217\202\222\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205\201D"; // Higher wind element ratio yields more damage.
const char aExtraDamageVsEa_800B9424[] = "\202d\202\230\202\224\202\222\202\201\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\226\202\223\201D\201@\202d\202\201\202\222\202\224\202\210"; // Extra damage vs. Earth
const char aWindAttackOneEn_800B9454[] = "\202v\202\211\202\216\202\204\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202n\202\216\202\205\201@\202d\202\216\202\205\202\215\202\231\201j"; // Wind Attack (One Enemy)
const char aAdvancedEarthAt_800B9484[] = "\202`\202\204\202\226\202\201\202\216\202\203\202\205\202\204\201@\202d\202\201\202\222\202\224\202\210\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Advanced Earth Attack
const char aEarthAttackAllE_800B94B0[] = "\202d\202\201\202\222\202\224\202\210\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201j"; // Earth Attack (All Enemies)
const char aHigherEarthElem_800B94E8[] = "\202g\202\211\202\207\202\210\202\205\202\222\201@\202\205\202\201\202\222\202\224\202\210\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\201@\202\222\202\201\202\224\202\211\202\217\201@\202\231\202\211\202\205\202\214\202\204\202\223\201@\202\215\202\217\202\222\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205\201D"; // Higher earth element ratio yields more damage.
const char aExtraDamageVsWa_800B9548[] = "\202d\202\230\202\224\202\222\202\201\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\226\202\223\201D\201@\202v\202\201\202\224\202\205\202\222"; // Extra damage vs. Water
const char aEarthAttackOneE_800B9578[] = "\202d\202\201\202\222\202\224\202\210\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202n\202\216\202\205\201@\202d\202\216\202\205\202\215\202\231\201j"; // Earth Attack (One Enemy)
const char aAdvancedWaterAt_800B95AC[] = "\202`\202\204\202\226\202\201\202\216\202\203\202\205\202\204\201@\202v\202\201\202\224\202\205\202\222\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Advanced Water Attack
const char aWaterAttackAllE_800B95D8[] = "\202v\202\201\202\224\202\205\202\222\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201j"; // Water Attack (All Enemies)
const char aHigherWaterElem_800B9610[] = "\202g\202\211\202\207\202\210\202\205\202\222\201@\202\227\202\201\202\224\202\205\202\222\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\201@\202\222\202\201\202\224\202\211\202\217\201@\202\231\202\211\202\205\202\214\202\204\202\223\201@\202\215\202\217\202\222\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205\201D"; // Higher water element ratio yields more damage.
const char aExtraDamageVsFi_800B9670[] = "\202d\202\230\202\224\202\222\202\201\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\226\202\223\201D\201@\202e\202\211\202\222\202\205"; // Extra damage vs. Fire
const char aWaterAttackOneE_800B969C[] = "\202v\202\201\202\224\202\205\202\222\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202n\202\216\202\205\201@\202d\202\216\202\205\202\215\202\231\201j"; // Water Attack (One Enemy)
const char aAdvancedFireAtt_800B96D0[] = "\202`\202\204\202\226\202\201\202\216\202\203\202\205\202\204\201@\202e\202\211\202\222\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Advanced Fire Attack
const char aFireAttackAllEn_800B96FC[] = "\202e\202\211\202\222\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201j"; // Fire Attack (All Enemies)
const char aHigherFireEleme_800B9730[] = "\202g\202\211\202\207\202\210\202\205\202\222\201@\202\206\202\211\202\222\202\205\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\201@\202\222\202\201\202\224\202\211\202\217\201@\202\231\202\211\202\205\202\214\202\204\202\223\201@\202\215\202\217\202\222\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205\201D"; // Higher fire element ratio yields more damage.
const char aExtraDamageVsAi_800B978C[] = "\202d\202\230\202\224\202\222\202\201\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\226\202\223\201D\201@\202`\202\211\202\222"; // Extra damage vs. Air
const char aFireAttackOneEn_800B97B8[] = "\202e\202\211\202\222\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202n\202\216\202\205\201@\202d\202\216\202\205\202\215\202\231\201j"; // Fire Attack (One Enemy)
const char aMakesItEasierTo_800B97E8[] = "\202l\202\201\202\213\202\205\202\223\201@\202\211\202\224\201@\202\205\202\201\202\223\202\211\202\205\202\222\201@\202\224\202\217\201@\202\213\202\211\202\214\202\214\201@\202\227\202\211\202\216\202\207\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\201\202\216\202\204"; // Makes it easier to kill winged enemies and
const char aSpecialAttackBr_800B9840[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202a\202\222\202\205\202\201\202\213\201@\202v\202\211\202\216\202\207\202\223\201j"; // Special Attack (Break Wings)
const char aSlightlyMoreDif_800B987C[] = "\202\223\202\214\202\211\202\207\202\210\202\224\202\214\202\231\201@\202\215\202\217\202\222\202\205\201@\202\204\202\211\202\206\202\206\202\211\202\203\202\225\202\214\202\224\201@\202\206\202\217\202\222\201@\202\224\202\210\202\205\202\215\201@\202\224\202\217\201@\202\223\202\203\202\217\202\222\202\205\201@\202\201\201@\202\210\202\211\202\224\201D"; // slightly more difficult for them to score a hit.
const char aMakesItEasierTo_800B98E0[] = "\202l\202\201\202\213\202\205\202\223\201@\202\211\202\224\201@\202\205\202\201\202\223\202\211\202\205\202\222\201@\202\224\202\217\201@\202\213\202\211\202\214\202\214\201@\202\224\202\227\202\217\201|\202\214\202\205\202\207\202\207\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\201\202\216\202\204"; // Makes it easier to kill two-legged enemies and
const char aSpecialAttackBr_800B9940[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202a\202\222\202\205\202\201\202\213\201@\202k\202\205\202\207\202\223\201j"; // Special Attack (Break Legs)
const char aItMoreDifficult_800B9978[] = "\202\211\202\224\201@\202\215\202\217\202\222\202\205\201@\202\204\202\211\202\206\202\206\202\211\202\203\202\225\202\214\202\224\201@\202\206\202\217\202\222\201@\202\224\202\210\202\205\202\215\201@\202\224\202\217\201@\202\223\202\203\202\217\202\222\202\205\201@\202\201\201@\202\210\202\211\202\224\201D"; // it more difficult for them to score a hit.
const char aReducesAnEnemie_800B99D0[] = "\202q\202\205\202\204\202\225\202\203\202\205\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202g\202o\201@\202\224\202\217\201@\202P\201@\202\201\202\216\202\204\201@\202\215\202\201\202\213\202\205\202\223"; // Reduces an enemies HP to 1 and makes
const char aSpecialAttackCr_800B9A1C[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202b\202\222\202\211\202\224\202\211\202\203\202\201\202\214\201@\202g\202\211\202\224\201j"; // Special Attack (Critical Hit)
const char aBringsEnemiesTo_800B9A58[] = "\202a\202\222\202\211\202\216\202\207\202\223\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\224\202\217\201@\202\224\202\210\202\205\201@\202\202\202\222\202\211\202\216\202\213\201@\202\217\202\206\201@\202\204\202\205\202\201\202\224\202\210\201D"; // Brings enemies to the brink of death.
const char aAttacksAllEnemi_800B9AA4[] = "\202`\202\224\202\224\202\201\202\203\202\213\202\223\201@\202\201\202\214\202\214\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\201\202\224\201@\202\217\202\216\202\203\202\205\201D"; // Attacks all enemies at once.
const char aSpecialAttackAl_800B9AE0[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201j"; // Special Attack (All Enemies)
const char aUsesItToRestore_800B9B1C[] = "\202\225\202\223\202\205\202\223\201@\202\211\202\224\201@\202\224\202\217\201@\202\222\202\205\202\223\202\224\202\217\202\222\202\205\201@\202\201\202\224\202\224\202\201\202\203\202\213\202\205\202\222\201f\202\223\201@\202l\202\201\202\216\202\201\201D"; // uses it to restore attacker's Mana.
const char aStealsSomeManaF_800B9B64[] = "\202r\202\224\202\205\202\201\202\214\202\223\201@\202\223\202\217\202\215\202\205\201@\202l\202\201\202\216\202\201\201@\202\206\202\222\202\217\202\215\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\201\202\216\202\204"; // Steals some Mana from an enemy and
const char aSpecialAttackAb_800B9BAC[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\202\202\223\202\217\202\222\202\202\201@\202l\202\201\202\216\202\201\201j"; // Special Attack (Absorb Mana)
const char aAnEnemyToRestor_800B9BE8[] = "\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\224\202\217\201@\202\222\202\205\202\223\202\224\202\217\202\222\202\205\201@\202\224\202\210\202\205\201@\202\201\202\224\202\224\202\201\202\203\202\213\202\205\202\222\201f\202\223\201@\202g\202o\201D"; // an enemy to restore the attacker's HP.
const char aTakesSomeOfTheD_800B9C38[] = "\202s\202\201\202\213\202\205\202\223\201@\202\223\202\217\202\215\202\205\201@\202\217\202\206\201@\202\224\202\210\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\211\202\216\202\206\202\214\202\211\202\203\202\224\202\205\202\204\201@\202\217\202\216"; // Takes some of the damage inflicted on
const char aSpecialAttackAb_800B9C84[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\202\202\223\202\217\202\222\202\202\201@\202g\202o\201j"; // Special Attack (Absorb HP)
const char aMoreDifficultFo_800B9CBC[] = "\202\215\202\217\202\222\202\205\201@\202\204\202\211\202\206\202\206\202\211\202\203\202\225\202\214\202\224\201@\202\206\202\217\202\222\201@\202\224\202\210\202\205\202\215\201@\202\224\202\217\201@\202\223\202\203\202\217\202\222\202\205\201@\202\201\201@\202\210\202\211\202\224\201D"; // more difficult for them to score a hit.
const char aCausesAnEnemyTo_800B9D0C[] = "\202b\202\201\202\225\202\223\202\205\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\224\202\217\201@\202\214\202\217\202\223\202\205\201@\202l\202\201\202\216\202\201\201@\202\201\202\216\202\204\201@\202\215\202\201\202\213\202\205\202\223\201@\202\211\202\224\201@\202\223\202\214\202\211\202\207\202\210\202\224\202\214\202\231"; // Causes an enemy to lose Mana and makes it slightly
const char aSpecialAttackDe_800B9D74[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202c\202\205\202\223\202\224\202\222\202\217\202\231\201@\202l\202\201\202\216\202\201\201j"; // Special Attack (Destroy Mana)
const char aPhysicallyDamag_800B9DB0[] = "\202o\202\210\202\231\202\223\202\211\202\203\202\201\202\214\202\214\202\231\201@\202\204\202\201\202\215\202\201\202\207\202\205\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\201\202\216\202\204\201@\202\224\202\225\202\222\202\216\202\223\201@\202\224\202\210\202\205\202\215\201@\202\224\202\217\201@\202\223\202\224\202\217\202\216\202\205\201D"; // Physically damages an enemy and turns them to stone.
const char aSpecialFleshToS_800B9E1C[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202e\202\214\202\205\202\223\202\210\201|\202\224\202\217\201|\202r\202\224\202\217\202\216\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Flesh-to-Stone Attack
const char aPhysicallyDamag_800B9E58[] = "\202o\202\210\202\231\202\223\202\211\202\203\202\201\202\214\202\214\202\231\201@\202\204\202\201\202\215\202\201\202\207\202\205\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\201\202\216\202\204\201@\202\220\202\225\202\224\202\223\201@\202\224\202\210\202\205\202\215\201@\202\224\202\217\201@\202\223\202\214\202\205\202\205\202\220\201D"; // Physically damages an enemy and puts them to sleep.
const char aSpecialSleepAtt_800B9EC0[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202r\202\214\202\205\202\205\202\220\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Sleep Attack
const char aPhysicallyDamag_800B9EEC[] = "\202o\202\210\202\231\202\223\202\211\202\203\202\201\202\214\202\214\202\231\201@\202\204\202\201\202\215\202\201\202\207\202\205\202\223\201@\202\201\202\216\202\204\201@\202\220\202\217\202\211\202\223\202\217\202\216\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201D"; // Physically damages and poisons an enemy.
const char aSpecialPoisonAt_800B9F40[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202o\202\217\202\211\202\223\202\217\202\216\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Poison Attack
const char aVeryEffectiveAg_800B9F6C[] = "\202u\202\205\202\222\202\231\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\205\202\201\202\222\202\224\202\210\201|\202\202\202\201\202\223\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Very effective against earth-based enemies.
const char aSpecialWindAtta_800B9FC4[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202v\202\211\202\216\202\204\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Wind Attack
const char aVeryEffectiveAg_800B9FEC[] = "\202u\202\205\202\222\202\231\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\227\202\211\202\216\202\204\201|\202\202\202\201\202\223\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Very effective against wind-based enemies.
const char aSpecialFireAtta_800BA044[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202e\202\211\202\222\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Fire Attack
const char aVeryEffectiveAg_800BA06C[] = "\202u\202\205\202\222\202\231\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\206\202\211\202\222\202\205\201|\202\202\202\201\202\223\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Very effective against fire-based enemies.
const char aSpecialWaterAtt_800BA0C4[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202v\202\201\202\224\202\205\202\222\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Water Attack
const char aVeryEffectiveAg_800BA0F0[] = "\202u\202\205\202\222\202\231\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\227\202\201\202\224\202\205\202\222\201|\202\202\202\201\202\223\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Very effective against water-based enemies.
const char aSpecialEarthAtt_800BA148[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202d\202\201\202\222\202\224\202\210\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Earth Attack
const int emptyText_800BA174[2] = { 0 };

void BossAi04_800C59A0(EnemyAi* ai)
{
    unsigned char phase = aiCounter_800C8B30[0] % 3;
    switch (phase)
    {
    case 0:
        ai->cmd_8->kind_0 = 6;
        ai->cmd_8->arg_4 = 3;
        ai->cmd_8->targets_C = ai->targetMask_18;
        break;
    case 1:
        ai->cmd_8->kind_0 = 6;
        ai->cmd_8->arg_4 = 2;
        ai->cmd_8->targets_C = ai->targetMask_18;
        break;
    case 2:
        ai->cmd_8->kind_0 = 6;
        ai->cmd_8->arg_4 = 1;
        ai->cmd_8->targets_C = ai->targetMask_18;
        break;
    }
    aiCounter_800C8B30[0]++;
}

void BossAi02_800C5A7C(EnemyAi* ai)
{
    if (ai->slot_C == 0)
    {
        if (aiAllyCalled_800C8B34 == 0)
        {
            ai->cmd_8->mask_8 = 0x10;
            ai->cmd_8->kind_0 = 0x15;
            aiAllyCalled_800C8B34 = 1;
            ai->cmd_8->arg_4 = 1;
            ai->cmd_8->targets_C = 2;
        }
        else
        {
            ai->cmd_8->kind_0 = 0;
            ai->cmd_8->targets_C = ai->targetMask_18;
        }
    }
    else if (ai->slot_C == 1)
    {
        unsigned char phase = aiCounter_800C8B30[0] % 3;
        switch (phase)
        {
        case 0:
            ai->cmd_8->kind_0 = 0;
            ai->cmd_8->targets_C = ai->targetMask_18;
            break;
        case 1:
            ai->cmd_8->kind_0 = 6;
            ai->cmd_8->arg_4 = 0;
            ai->cmd_8->targets_C = ai->targetMask_18;
            break;
        case 2:
            ai->cmd_8->kind_0 = 1;
            ai->cmd_8->arg_4 = 2;
            ai->cmd_8->targets_C = ai->targetMask_18;
            break;
        }
        aiCounter_800C8B30[0]++;
    }
}

void BossAi03_800C5BC0(EnemyAi* ai)
{
    if (ai->slot_C == 0)
    {
        if (aiAllyCalled_800C8B34 == 0)
        {
            ai->cmd_8->mask_8 = 0x10;
            ai->cmd_8->kind_0 = 0x15;
            aiAllyCalled_800C8B34 = 1;
            ai->cmd_8->arg_4 = 1;
            ai->cmd_8->targets_C = 2;
        }
        else
        {
            ai->cmd_8->kind_0 = 0;
            ai->cmd_8->targets_C = ai->targetMask_18;
        }
    }
    else if (ai->slot_C == 1)
    {
        unsigned char phase = aiCounter_800C8B30[0] % 3;
        switch (phase)
        {
        case 0:
            ai->cmd_8->kind_0 = 0;
            ai->cmd_8->targets_C = ai->targetMask_18;
            break;
        case 1:
            ai->cmd_8->kind_0 = 6;
            ai->cmd_8->arg_4 = 0;
            ai->cmd_8->targets_C = ai->targetMask_18;
            break;
        case 2:
            ai->cmd_8->kind_0 = 1;
            ai->cmd_8->arg_4 = 2;
            ai->cmd_8->targets_C = ai->targetMask_18;
            break;
        }
        aiCounter_800C8B30[0]++;
    }
}

void BossAi0D_800C5D04(EnemyAi* ai)
{
    if (ai->slot_C == 0)
    {
        if (aiAllyCalled_800C8B34 == 0)
        {
            ai->cmd_8->mask_8 = 0x10;
            ai->cmd_8->kind_0 = 0x15;
            aiAllyCalled_800C8B34 = 1;
            ai->cmd_8->arg_4 = 1;
            ai->cmd_8->targets_C = 2;
        }
        else
        {
            ai->cmd_8->kind_0 = 0;
            ai->cmd_8->targets_C = ai->targetMask_18;
        }
    }
    else
    {
        unsigned char* counters = aiCounter_800C8B30;
        if (counters[1])
        {
            ai->cmd_8->kind_0 = 6;
            ai->cmd_8->arg_4 = 2;
            ai->cmd_8->targets_C = ai->targetMask_18;
            counters[1] = 0;
        }
        else
        {
            switch (rand() % 3)
            {
            case 0:
                ai->cmd_8->kind_0 = 1;
                ai->cmd_8->arg_4 = 0x1B;
                ai->cmd_8->targets_C = ai->targetMask_18;
                SetHitVariant_80018430(2);
                break;
            case 1:
                ai->cmd_8->kind_0 = 6;
                ai->cmd_8->arg_4 = 1;
                ai->cmd_8->targets_C = ai->targetMask_18;
                break;
            default:
                ai->cmd_8->kind_0 = 6;
                ai->cmd_8->arg_4 = 0;
                ai->cmd_8->targets_C = ai->cmd_8->mask_8;
                aiCounter_800C8B30[1] = 1;
                break;
            }
        }
    }
    aiCounter_800C8B30[0]++;
}

void BossAi0B_800C5EB8(EnemyAi* ai)
{
    if (ai->slot_C == 0)
    {
        if (aiAllyCalled_800C8B34 == 0)
        {
            ai->cmd_8->mask_8 = 0x10;
            ai->cmd_8->kind_0 = 0x15;
            aiAllyCalled_800C8B34 = 1;
            ai->cmd_8->arg_4 = 1;
            ai->cmd_8->targets_C = 2;
        }
        else
        {
            ai->cmd_8->kind_0 = 0;
            ai->cmd_8->targets_C = ai->targetMask_18;
        }
    }
    else
    {
        switch (rand() % 3)
        {
        case 0:
            if (GetMp_800334F0(ai->target_14))
            {
                ai->cmd_8->kind_0 = 6;
                ai->cmd_8->arg_4 = 1;
                ai->cmd_8->targets_C = ai->targetMask_18;
                break;
            }
        case 1:
            ai->cmd_8->kind_0 = 1;
            ai->cmd_8->arg_4 = 0x19;
            ai->cmd_8->targets_C = ai->targetMask_18;
            SetHitVariant_80018430(0);
            break;
        case 2:
            ai->cmd_8->kind_0 = 6;
            ai->cmd_8->arg_4 = 3;
            ai->cmd_8->targets_C = ai->targetMask_18;
            break;
        }
    }
    aiCounter_800C8B30[0]++;
}

void BossAi0C_800C6038(EnemyAi* ai)
{
    if (ai->slot_C == 0)
    {
        if (aiAllyCalled_800C8B34 == 0)
        {
            ai->cmd_8->mask_8 = 0x10;
            ai->cmd_8->kind_0 = 0x15;
            aiAllyCalled_800C8B34 = 1;
            ai->cmd_8->arg_4 = 1;
            ai->cmd_8->targets_C = 2;
        }
        else
        {
            ai->cmd_8->kind_0 = 0;
            ai->cmd_8->targets_C = ai->targetMask_18;
        }
    }
    else if (aiCounter_800C8B30[0] != 0 && TargetHasStatus_800C6EC8(ai, 2))
    {
        ai->cmd_8->kind_0 = 6;
        ai->cmd_8->arg_4 = 0;
        ai->cmd_8->targets_C = ai->cmd_8->mask_8;
        aiCounter_800C8B30[0] = 0;
    }
    else
    {
        aiCounter_800C8B30[0]++;
        switch (rand() % 3)
        {
        case 0:
            ai->cmd_8->kind_0 = 1;
            ai->cmd_8->arg_4 = 0x1C;
            ai->cmd_8->targets_C = ai->targetMask_18;
            SetHitVariant_80018430(1);
            break;
        case 1:
            ai->cmd_8->kind_0 = 6;
            ai->cmd_8->arg_4 = 1;
            ai->cmd_8->targets_C = ai->targetMask_18;
            break;
        case 2:
            ai->cmd_8->kind_0 = 6;
            ai->cmd_8->arg_4 = 3;
            ai->cmd_8->targets_C = ai->targetMask_18;
            break;
        }
    }
}

void BossAi0E_800C61FC(EnemyAi* ai)
{
    unsigned short element;
    if (ai->slot_C == 0)
    {
        if (aiAllyCalled_800C8B34 == 0)
        {
            ai->cmd_8->mask_8 = 0x10;
            ai->cmd_8->kind_0 = 0x15;
            aiAllyCalled_800C8B34 = 1;
            ai->cmd_8->arg_4 = 1;
            ai->cmd_8->targets_C = 2;
        }
        else
        {
            ai->self_10->st_0.elementMask_42 = 0;
            SetElementAffinity_800C66B4((unsigned char*)ai->self_10, 0xC);
            ai->cmd_8->kind_0 = 6;
            ai->cmd_8->arg_4 = 1;
            ai->cmd_8->targets_C = ai->targetMask_18;
        }
    }
    else if ((GetAreaElement_800BC868() == 0 && !((unsigned short)ai->self_10->st_0.elementMask_42 & 1)) || (aiCounter_800C8B30[0] >= 3 && GetAreaElement_800BC868() == 0))
    {
        AiSetCommand_800C6AFC(ai, 6, 2);
        ai->skills_4->slot[2].id_1 = 0x25;
        ai->self_10->st_0.elementMask_42 = 8;
        SetHitVariant_80018430(3);
        SetElementAffinity_800C66B4((unsigned char*)ai->self_10, 2);
        aiCounter_800C8B30[0] = 0;
    }
    else if ((GetAreaElement_800BC868() == 1 && !((unsigned short)ai->self_10->st_0.elementMask_42 & 2)) || (aiCounter_800C8B30[0] >= 3 && GetAreaElement_800BC868() == 1))
    {
        AiSetCommand_800C6AFC(ai, 6, 2);
        ai->skills_4->slot[2].id_1 = 0x22;
        ai->self_10->st_0.elementMask_42 = 1;
        SetHitVariant_80018430(0);
        SetElementAffinity_800C66B4((unsigned char*)ai->self_10, 3);
        aiCounter_800C8B30[0] = 0;
    }
    else if ((GetAreaElement_800BC868() == 2 && !((unsigned short)ai->self_10->st_0.elementMask_42 & 4)) || (aiCounter_800C8B30[0] >= 3 && GetAreaElement_800BC868() == 2))
    {
        AiSetCommand_800C6AFC(ai, 6, 2);
        ai->skills_4->slot[2].id_1 = 0x23;
        ai->self_10->st_0.elementMask_42 = 2;
        SetHitVariant_80018430(1);
        SetElementAffinity_800C66B4((unsigned char*)ai->self_10, 0);
        aiCounter_800C8B30[0] = 0;
    }
    else if ((GetAreaElement_800BC868() == 3 && !((unsigned short)ai->self_10->st_0.elementMask_42 & 8)) || (aiCounter_800C8B30[0] >= 4 && GetAreaElement_800BC868() == 3) || GetAreaElement_800BC868() == -1)
    {
        AiSetCommand_800C6AFC(ai, 6, 2);
        ai->skills_4->slot[2].id_1 = 0x24;
        ai->self_10->st_0.elementMask_42 = 4;
        SetHitVariant_80018430(2);
        SetElementAffinity_800C66B4((unsigned char*)ai->self_10, 1);
        aiCounter_800C8B30[0] = 0;
    }
    else
    {
        element = (unsigned short)ai->self_10->st_0.elementMask_42;
        if (element & 8)
        {
            if (aiCounter_800C8B30[0] == 1)
            {
                AiSetCommandOnSelf_800C6B24(ai, 1, 0x1D);
            }
            else
            {
                AiSetCommand_800C6AFC(ai, 6, 0);
            }
        }
        else if (element & 1)
        {
            if (rand() & 1)
            {
                AiSetCommand_800C6AFC(ai, 6, 1);
                ai->skills_4->slot[1].id_1 = 4;
            }
            else
            {
                AiSetCommand_800C6AFC(ai, 1, 0x19);
                SetHitVariant_80018430(0);
            }
        }
        else if (element & 2)
        {
            if (rand() % 3 != 0)
            {
                AiSetCommand_800C6AFC(ai, 1, 0x1C);
                SetHitVariant_80018430(1);
            }
            else
            {
                AiSetCommand_800C6AFC(ai, 6, 1);
                ai->skills_4->slot[1].id_1 = 5;
            }
        }
        else if (element & 4)
        {
            if (rand() % 3 != 0)
            {
                AiSetCommand_800C6AFC(ai, 6, 1);
                ai->skills_4->slot[1].id_1 = 2;
            }
            else
            {
                AiSetCommand_800C6AFC(ai, 1, 0x1B);
                SetHitVariant_80018430(2);
            }
        }
    }
    aiCounter_800C8B30[0] += ((rand() & 3) >> 1) + 1;
}

void SetElementAffinity_800C66B4(unsigned char* buf, unsigned int element)
{
    int i;
    unsigned int value = 0xC;
    unsigned char* p;
    if (element == value)
    {
        value = 0x30;
    }
    for (i = 3, p = buf + 3; i >= 0; i--, p--)
    {
        p[0x20] = value;
    }
    if (element < 0xC)
    {
        (buf + element)[0x20] = 0x18;
    }
}

void BossAi0F_800C66F4(EnemyAi* ai)
{
    if (ai->slot_C == 0)
    {
        if (aiAllyCalled_800C8B34 == 0)
        {
            ai->cmd_8->mask_8 = 0x10;
            ai->cmd_8->kind_0 = 0x15;
            aiAllyCalled_800C8B34 = 1;
            ai->cmd_8->arg_4 = 1;
            ai->cmd_8->targets_C = 2;
            return;
        }
    }
    else if (ai->slot_C == 1)
    {
        if ((rand() & 1) || ((unsigned short)ai->target_14->elementMask_42 & 2) ||
            GetHp_800334D8(&ai->self_10->st_0) < (short)(GetMaxHp_800334CC(&ai->self_10->st_0) / 3))
        {
            if (AiUseSkill_800C6A8C(ai))
            {
                return;
            }
        }
    }
    else
    {
        return;
    }
    ai->cmd_8->kind_0 = 0;
    ai->cmd_8->targets_C = ai->targetMask_18;
}

void BossAi10_800C6824(EnemyAi* ai)
{
    if (ai->slot_C == 0)
    {
        if (aiAllyCalled_800C8B34 == 0)
        {
            ai->cmd_8->mask_8 = 0x10;
            ai->cmd_8->kind_0 = 0x15;
            aiAllyCalled_800C8B34 = 1;
            ai->cmd_8->arg_4 = 1;
            ai->cmd_8->targets_C = 2;
            return;
        }
    }
    else if (ai->slot_C == 1)
    {
        short hp = GetHp_800334D8(&ai->self_10->st_0);
        short maxHp = GetMaxHp_800334CC(&ai->self_10->st_0);
        if (hp < maxHp / 4)
        {
            if (AiUseSkill_800C6A8C(ai))
            {
                return;
            }
        }
        if (AiCastMagic_800C6BD0(ai, 9))
        {
            return;
        }
    }
    else
    {
        return;
    }
    ai->cmd_8->kind_0 = 0;
    ai->cmd_8->targets_C = ai->targetMask_18;
}

void BossAi11_800C6928(EnemyAi* ai)
{
    if (ai->slot_C == 0)
    {
        if (aiAllyCalled_800C8B34 == 0)
        {
            ai->cmd_8->mask_8 = 0x10;
            ai->cmd_8->kind_0 = 0x15;
            aiAllyCalled_800C8B34 = 1;
            ai->cmd_8->arg_4 = 1;
            ai->cmd_8->targets_C = 2;
            return;
        }
    }
    else if (ai->slot_C == 1)
    {
        short hp = GetHp_800334D8(&ai->self_10->st_0);
        short maxHp = GetMaxHp_800334CC(&ai->self_10->st_0);
        if (hp < maxHp / 2)
        {
            if (AiUseSkill_800C6A8C(ai))
            {
                return;
            }
        }
        if (rand() & 1)
        {
            if (AiCastMagic_800C6BD0(ai, 6))
            {
                return;
            }
        }
    }
    else
    {
        return;
    }
    ai->cmd_8->kind_0 = 0;
    ai->cmd_8->targets_C = ai->targetMask_18;
}

void EnemyAiFirstSkill_800C6A40(EnemyAi* ai)
{
    ai->cmd_8->kind_0 = 6;
    ai->cmd_8->arg_4 = 0;
    ai->cmd_8->targets_C = ai->targetMask_18;
}

int AiAttack_800C6A68(EnemyAi* ai)
{
    ai->cmd_8->kind_0 = 0;
    ai->cmd_8->targets_C = ai->targetMask_18;
    return 1;
}

int AiUseSkill_800C6A8C(EnemyAi* ai)
{
    int chosen = FindUsableSkill_800C6D6C(ai->skills_4, ai->self_10);
    if (chosen != 5)
    {
        ai->cmd_8->kind_0 = 6;
        ai->cmd_8->arg_4 = chosen;
        ai->cmd_8->targets_C = ai->targetMask_18;
        return 1;
    }
    return 0;
}

void AiSetCommand_800C6AFC(EnemyAi* ai, int kind, int arg)
{
    ai->cmd_8->kind_0 = kind;
    ai->cmd_8->arg_4 = arg;
    ai->cmd_8->targets_C = ai->targetMask_18;
}

void AiSetCommandOnSelf_800C6B24(EnemyAi* ai, int kind, int arg)
{
    BattleCmd* cmd;
    ai->cmd_8->kind_0 = kind;
    ai->cmd_8->arg_4 = arg;
    cmd = ai->cmd_8;
    cmd->targets_C = cmd->mask_8;
}

int AiCastMagicOnAlly_800C6B50(EnemyAi* ai, int magic, int ally)
{
    if (CanCastMagic_800C6CFC(magic, ai->magicBits_0, ai->self_10) != 0)
    {
        ai->cmd_8->kind_0 = 1;
        ai->cmd_8->arg_4 = magic;
        ai->cmd_8->targets_C = 1 << (ally + 4);
        return 1;
    }
    return 0;
}

int AiCastMagic_800C6BD0(EnemyAi* ai, int magic)
{
    if (CanCastMagic_800C6CFC(magic, ai->magicBits_0, ai->self_10) != 0)
    {
        ai->cmd_8->kind_0 = 1;
        ai->cmd_8->arg_4 = magic;
        ai->cmd_8->targets_C = ai->targetMask_18;
        return 1;
    }
    return 0;
}

int AiDefend_800C6C44(EnemyAi* ai)
{
    ai->cmd_8->kind_0 = 0x12;
    return 1;
}

int AiFlee_800C6C58(EnemyAi* ai)
{
    ai->cmd_8->kind_0 = 7;
    ai->cmd_8->targets_C = ai->targetMask_18;
    return 1;
}

void GetEnemyStatuses_800C6C7C(UnitStatus** out)
{
    int alive = GetEnemyAliveMask_800A248C();
    int i;
    for (i = 0; i < 3; i++)
    {
        int bit = 1 << (i + 4);
        if (alive & bit)
        {
            out[i] = GetEnemyStatus_800A2B60(i);
        }
        else
        {
            out[i] = 0;
        }
    }
}

int CanCastMagic_800C6CFC(unsigned int magic, unsigned int* magicBits, UnitStats* self)
{
    if (TestMagicBit_8001AE2C(magicBits, magic) != 0)
    {
        if (magicData_8007C438[magic].mpCost_4 <= self->st_0.mp_C.cur_0)
        {
            return 1;
        }
    }
    return 0;
}

int FindUsableSkill_800C6D6C(UnitSkills* skills, UnitStats* self)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (skills->slot[i].flags_0 & 1)
        {
            short mp = self->st_0.mp_C.cur_0;
            if (!(mp < GetSkillMpCost_80031A04(skills, i)))
            {
                return i;
            }
        }
    }
    return i;
}

int AiHealWeakAlly_800C6DF8(EnemyAi* ai, int magic)
{
    UnitStatus* allies[3];
    int i;
    GetEnemyStatuses_800C6C7C(allies);
    for (i = 0; i < 3; i++)
    {
        if (allies[i])
        {
            short hp = GetHp_800334D8(allies[i]);
            short maxHp = GetMaxHp_800334CC(allies[i]);
            if (hp <= maxHp / 4)
            {
                if (AiCastMagicOnAlly_800C6B50(ai, magic, i))
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int TargetHasStatus_800C6EC8(EnemyAi* ai, int mask)
{
    return (ai->target_14->status_0 & mask) != 0;
}

int IsTargetWeakToMagic_800C6EE4(EnemyAi* ai)
{
    return ai->target_14->stats_2C.cur_0[1] > ai->target_14->stats_2C.cur_0[3];
}

int StartBattleMenu_800C6EFC()
{
    int i;
    int bit;
    int count = 0;
    EventEntry* entry = AllocEventEntry_80043AF8(battleMenuTask_8008D468);
    if (entry)
    {
        entry->cb_8 = (EventEntryFn)BattleMenuTask_800C8A08;
        entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
        if (actingUnit_800C9C7C == 0)
        {
            menuForMinion_800C9E49 = 0;
        }
        else
        {
            menuForMinion_800C9E49 = 1;
        }
        menuCommand_800C9E58.kind_0 = 0;
        menuCommand_800C9E58.arg_4 = 0;
        menuCommand_800C9E58.targets_C = 0;
        menuCommand_800C9E58.mask_8 = 1 << actingUnit_800C9C7C;
        partyMinionMask_800C9E78 = GetPartyMinionMask_800C0A9C();
        partyMinionCount_800C9E4B = GetCapturedMinionsFromBitfield_8003BA58(partyMinionMask_800C9E78);
        enemyMask_800C9E4C = GetEnemyAliveMask_800A248C();
        enemyCount_800C9E4A = GetCapturedMinionsFromBitfield_8003BA58(enemyMask_800C9E4C);
        for (i = 0; i < 3; i++)
        {
            bit = 1 << (i + 4);
            if (enemyMask_800C9E4C & bit)
            {
                enemyUnits_800C9E80[count] = i + 4;
                *(enemyTargets_800C9E70.bits_2 + count) = bit;
                count++;
            }
        }
        menuPage_800C9E50 = 0;
        prevMenuPage_800C9E40 = 0;
        menuState_800C9E48 = 0;
        targetFlags_800C9E68 = 4;
        enemyTargets_800C9E70.flag_0 = 0;
        InitMenuCursors_800C7088();
        SelectMenuWindows_800C71A0();
        DisableMenuCommands_800C71C8();
        cameraFocus_800C9E38 = -1;
    }
    return (int)entry;
}

void InitMenuCursors_800C7088()
{
    if (menuForMinion_800C9E49 == 0)
    {
        if (GetLastInventorySlot_800AD308(0) + 1 >= 5)
        {
            itemMenu_800C9308->count_4 = GetLastInventorySlot_800AD308(0) + 1;
        }
        itemMenu_800C9308->cursor_8 = 0;
        commandMenu_800C92D8->count_4 = 6;
        commandMenu_800C92D8->cursor_8 = 0;
    }
    else
    {
        if (CountMagicBits_8001AE54(GetMinionMagicBits_80010824(3, actingUnit_800C9C7C - 1)) >= 5)
        {
            magicMenu_800C92F0->count_4 = CountMagicBits_8001AE54(GetMinionMagicBits_80010824(3, actingUnit_800C9C7C - 1));
        }
        magicMenu_800C92F0->cursor_8 = 0;
        skillMenu_800C92E4->cursor_8 = 0;
        commandMenu_800C92D8->count_4 = 5;
        commandMenu_800C92D8->cursor_8 = 0;
    }
    if ((unsigned char)savedEnemyCursor_800C9D56 > enemyCount_800C9E4A - 1)
    {
        savedEnemyCursor_800C9D56 = 0;
    }
    enemyTargetMenu_800C9314->columns_0 = enemyCount_800C9E4A;
    enemyTargetMenu_800C9314->count_4 = enemyCount_800C9E4A;
    enemyTargetMenu_800C9314->cursor_8 = (unsigned char)savedEnemyCursor_800C9D56;
}

void SelectMenuWindows_800C71A0()
{
    menuWindows_800C9630.items_10 = menuWindowSets_800C9628[menuForMinion_800C9E49];
}

void DisableMenuCommands_800C71C8()
{
    if (menuForMinion_800C9E49 == 0)
    {
        if (GetPartyMinionMask_800C0A9C() == 0)
        {
            levantMenuItems_800C93A4[2].data_4 = msgNoDivineMinions_800C9378;
            winSummon_800C946C[0].flags_0 |= 2;
        }
        if (CanCapture_800C7334() == 0)
        {
            levantMenuItems_800C93A4[3].data_4 = msgCannotCapture_800C9384;
            winCapture_800C94A4[0].flags_0 |= 2;
        }
        else if (GetEmptyCocoons_800AD8E4() == 0)
        {
            levantMenuItems_800C93A4[3].data_4 = msgNoEmptyCocoons_800C9388;
            winCapture_800C94A4[0].flags_0 |= 2;
        }
        if (CanFlee_800C72B8() == 0)
        {
            levantMenuItems_800C93A4[5].data_4 = msgCannotEscape_800C938C;
            winFlee_800C9514[0].flags_0 |= 2;
        }
        menuItems_800C9E6C = levantMenuItems_800C93A4;
    }
    else
    {
        menuItems_800C9E6C = minionMenuItems_800C93D4;
    }
}

int CanFlee_800C72B8()
{
    int i;
    int bit;
    for (i = 0; i < 3; i++)
    {
        bit = enemyMask_800C9E4C & (1 << (i + 4));
        if (bit != 0)
        {
            if (CanFleeFromEnemy_800A28FC(i) == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

int CanCapture_800C7334()
{
    int i;
    int bit;
    for (i = 0; i < 3; i++)
    {
        bit = enemyMask_800C9E4C & (1 << (i + 4));
        if (bit != 0)
        {
            if (IsUncapturableSpecies_800BF980(GetEnemySpecies_800A2BE4(i)) == 1)
            {
                return 0;
            }
        }
    }
    return 1;
}

MenuCursor* GetPageCursor_800C73B8(unsigned char page)
{
    if (page == 4)
    {
        if (targetFlags_800C9E68 & 1)
        {
            return allTargetsMenu_800C932C;
        }
        if (targetFlags_800C9E68 & 4)
        {
            return enemyTargetMenu_800C9314;
        }
        return targetMenu_800C9320;
    }
    return pageMenus_800C9338[page];
}

void HighlightTargetWindows_800C7424(unsigned char page)
{
    ResetWindowHighlights_800BFC10();
    if (page == 4)
    {
        if (targetFlags_800C9E68 & 1)
        {
            if (targetFlags_800C9E68 & 4)
            {
                enemyWindowsHighlight_800C9DFC = 1;
                enemyHighlightTimes_800C9174[0] = GetTime30Hz_8002C64C();
                enemyHighlightTimes_800C9174[1] = GetTime30Hz_8002C64C();
                enemyHighlightTimes_800C9174[2] = GetTime30Hz_8002C64C();
            }
            if (targetFlags_800C9E68 & 2)
            {
                actorWindowHighlight_800C9DFD = 1;
                actorHighlightTime_800C9170 = GetTime30Hz_8002C64C();
            }
        }
        else if (targetFlags_800C9E68 & 4)
        {
            short i;
            enemyWindowsHighlight_800C9DFC = 1;
            i = GetMenuCursorIndex_8003DA54(enemyTargetMenu_800C9314);
            enemyHighlightTimes_800C9174[enemyUnits_800C9E80[i] - 4] = GetTime30Hz_8002C64C();
        }
        else
        {
            actorWindowHighlight_800C9DFD = 1;
            actorHighlightTime_800C9170 = GetTime30Hz_8002C64C();
        }
    }
}

int IsMenuSelectionValid_800C7530()
{
    ListMenuState ref;
    TargetQuery query;
    short idx;
    int* error;
    idx = GetMenuCursorIndex_8003DA54(pageCursor_800C9E44);
    ref.cursor_0 = pageCursor_800C9E44->cursor_8;
    ref.scroll_2 = pageCursor_800C9E44->scroll_A;
    ref.fieldMenu_A = 0;
    menuErrorText_800C9E7C = 0;
    switch (menuPage_800C9E50)
    {
    case 0:
        error = menuItems_800C9E6C[idx].data_4;
        if (error == 0)
        {
            return 1;
        }
        menuErrorText_800C9E7C = *error;
        return 0;
    case 1:
        switch (CheckItemUsable_80033AFC(&ref))
        {
        case 0:
            return 1;
        case 1:
            return 0;
        case 2:
        case 4:
            menuErrorText_800C9E7C = msgCannotUseHere_800C93A0;
            return 0;
        case 3:
        case 5:
        case 6:
        case 7:
        default:
            return 1;
        }
    case 2:
        ref.minion_C = GetMinion_80010598(3, actingUnit_800C9C7C - 1);
        switch (CheckSkillUsable_80033C98(&ref))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 6:
        default:
            return 1;
        case 5:
            menuErrorText_800C9E7C = msgNotEnoughMana_800C9380;
            return 0;
        case 7:
            return 0;
        }
    case 3:
        ref.minion_C = GetMinion_80010598(3, actingUnit_800C9C7C - 1);
        switch (CheckMagicCastable_80033C08(&ref))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 7:
        default:
            return 1;
        case 5:
            menuErrorText_800C9E7C = msgNotEnoughMana_800C9380;
            return 0;
        case 6:
            return 0;
        }
    case 4:
        query.id_0 = menuCommand_800C9E58.arg_4;
        query.actor_2 = actingUnit_800C9C7C;
        query.target_4 = menuTarget_800C9E54;
        query.f6 = 0;
        if (GetSelectedCommand_800C78D0() == 4)
        {
            switch (CheckItemOnTarget_80033DF4(&query))
            {
            case 0:
                return 1;
            case 1:
                menuErrorText_800C9E7C = msgDivineMinionsCannot_800C939C;
                return 0;
            case 2:
                menuErrorText_800C9E7C = msgItemForDivineMinions_800C9398;
                return 0;
            case 3:
                menuErrorText_800C9E7C = msgNoNeedToUseItem_800C9390;
                return 0;
            case 4:
                break;
            default:
                return 1;
            }
        }
        else if (GetSelectedCommand_800C78D0() == 6)
        {
            switch (CheckUsableStub_80034124(&query))
            {
            case 0:
                return 1;
            case 1:
                menuErrorText_800C9E7C = msgDivineMinionsCannot_800C939C;
                return 0;
            case 2:
                return 0;
            case 3:
                menuErrorText_800C9E7C = msgNoNeedToUseItem_800C9390;
                return 0;
            case 4:
                break;
            default:
                return 1;
            }
        }
        else if (GetSelectedCommand_800C78D0() == 7)
        {
            switch (CheckMagicUsable_80034068(&query))
            {
            case 0:
                return 1;
            case 1:
                menuErrorText_800C9E7C = msgDivineMinionsCannot_800C939C;
                return 0;
            case 2:
                return 0;
            case 3:
                menuErrorText_800C9E7C = msgNoNeedToUseItem_800C9390;
                return 0;
            case 4:
                break;
            default:
                return 1;
            }
        }
        else if (GetSelectedCommand_800C78D0() == 2 || GetSelectedCommand_800C78D0() == 8)
        {
            if (HasStatusFlag_80033548(GetUnitStatus_80014390((unsigned char)menuTarget_800C9E54), 0x400) == 0)
            {
                return 1;
            }
        }
        else
        {
            return 1;
        }
        menuErrorText_800C9E7C = msgCannotSummon_800C937C;
        return 0;
    case 5:
    default:
        return 1;
    }
}


unsigned char GetSelectedCommand_800C78D0()
{
    return commandByCursor_800C9648[menuForMinion_800C9E49 + (short)GetMenuCursorIndex_8003DA54(commandMenu_800C92D8) * 2];
}

int GetSelectedTargets_800C791C()
{
    int targets = 0;
    unsigned char flags = targetFlags_800C9E68;
    if (flags & 1)
    {
        if (flags & 4)
        {
            targets = enemyMask_800C9E4C;
        }
        if (flags & 2)
        {
            targets |= partyMinionMask_800C9E78 | 1;
        }
    }
    else if (flags & 4)
    {
        short i;
        unsigned char* bits;
        i = GetMenuCursorIndex_8003DA54(enemyTargetMenu_800C9314);
        bits = enemyTargets_800C9E70.bits_2;
        targets = bits[i];
    }
    else
    {
        targets = 1 << menuTarget_800C9E54;
    }
    return targets;
}

int GetSelectedItem_800C79B8()
{
    return GetInventorySlotId_800AD288((short)GetMenuCursorIndex_8003DA54(itemMenu_800C9308), 0);
}

int GetSelectedSkill_800C79EC()
{
    return MenuIndexToSkillSlot_80031BDC((short)GetMenuCursorIndex_8003DA54(skillMenu_800C92E4));
}

int GetSelectedMagic_800C7A1C()
{
    unsigned int* magicBits = GetMinionMagicBits_80010824(3, actingUnit_800C9C7C - 1);
    return FindNthMagicBit_8001AEC0(magicBits, (short)GetMenuCursorIndex_8003DA54(magicMenu_800C92F0));
}

void AdvanceMenuPage_800C7A6C()
{
    int skills;
    char* magicBits;
    prevMenuPage_800C9E40 = menuPage_800C9E50;
    switch (menuPage_800C9E50)
    {
    case 0:
        targetFlags_800C9E68 = commandTargetFlags_800C9660[GetSelectedCommand_800C78D0()];
        menuPage_800C9E50 = commandNextPage_800C9654[GetSelectedCommand_800C78D0()];
        menuCommand_800C9E58.kind_0 = commandKinds_800C96A4[GetSelectedCommand_800C78D0()];
        break;
    case 1:
        targetFlags_800C9E68 = GetItemTargetFlags_8001CE8C(GetSelectedItem_800C79B8());
        menuPage_800C9E50 = 4;
        menuCommand_800C9E58.arg_4 = GetSelectedItem_800C79B8();
        break;
    case 2:
        skills = GetUnitSkills_80031B30(actingUnit_800C9C7C);
        targetFlags_800C9E68 = GetSkillTargetFlags_80031B0C(skills, MenuIndexToSkillSlot_80031BDC((short)GetMenuCursorIndex_8003DA54(skillMenu_800C92E4)));
        menuPage_800C9E50 = 4;
        menuCommand_800C9E58.arg_4 = GetSelectedSkill_800C79EC();
        break;
    case 3:
        magicBits = GetMinionMagicBits_80010824(3, actingUnit_800C9C7C - 1);
        targetFlags_800C9E68 = GetMagicTargetFlags_8001ACE4(FindNthMagicBit_8001AEC0(magicBits, (short)GetMenuCursorIndex_8003DA54(magicMenu_800C92F0)));
        menuPage_800C9E50 = 4;
        menuCommand_800C9E58.arg_4 = GetSelectedMagic_800C7A1C();
        break;
    case 4:
        menuPage_800C9E50 = 5;
        menuCommand_800C9E58.targets_C = GetSelectedTargets_800C791C();
        break;
    case 5:
        break;
    }
    if (menuPage_800C9E50 == 4)
    {
        if (GetSelectedCommand_800C78D0() == 4)
        {
            targetMenu_800C9320[0].rows_2 = partyMinionCount_800C9E4B + 1;
            targetMenu_800C9320[0].count_4 = partyMinionCount_800C9E4B + 1;
        }
        else if (GetSelectedCommand_800C78D0() == 2)
        {
            targetMenu_800C9320[0].rows_2 = partyMinionCount_800C9E4B;
            targetMenu_800C9320[0].count_4 = partyMinionCount_800C9E4B;
        }
        else if (GetSelectedCommand_800C78D0() == 7)
        {
            targetMenu_800C9320[0].rows_2 = 1;
            targetMenu_800C9320[0].count_4 = 1;
        }
        else if (GetSelectedCommand_800C78D0() == 8)
        {
            targetMenu_800C9320[0].rows_2 = partyMinionCount_800C9E4B;
            targetMenu_800C9320[0].count_4 = partyMinionCount_800C9E4B;
        }
        targetMenu_800C9320[0].cursor_8 = 0;
        targetMenu_800C9320[0].scroll_A = 0;
    }
}

void UpdateMenuWindows_800C7CE8(unsigned char page)
{
    unsigned int frame;
    if (page == 0)
    {
        menuWindows_800C9630.flags_0 = 2;
    }
    else
    {
        menuWindows_800C9630.flags_0 = 4;
    }
    menuWindows_800C9630.time_4 = GetTime30Hz_8002C64C();
    frame = menuWindows_800C9630.open_8;
    if (frame < 8)
    {
        menuWindows_800C9630.open_8 = frame + 1;
    }
    menuWindows_800C9630.cursor_C = commandMenu_800C92D8[0].cursor_8;
}

void UpdateShownUnit_800C7D54(unsigned char page)
{
    if (page != 4)
    {
        shownUnit_800C9C99 = actingUnit_800C9C7C;
    }
    else if (targetFlags_800C9E68 & 5)
    {
        shownUnit_800C9C99 = actingUnit_800C9C7C;
    }
    else
    {
        shownUnit_800C9C99 = menuTarget_800C9E54;
    }
}

void BattleMenuDraw_800C7DA8()
{
    int flags = 0;
    int mode = 0;
    int cursor;
    short sel[2];
    previewHpChange_800C9180 = 0;
    previewMpChange_800C9182 = 0;
    if (IsCircleHeldP1_8003D480() == 1 && menuState_800C9E48 != 1)
    {
        if (menuPage_800C9E50 == 0)
        {
            mode = 1;
            DrawMenuHelpText_800C8828(*menuItems_800C9E6C[(short)GetMenuCursorIndex_8003DA54(commandMenu_800C92D8)].text);
        }
        else if (menuPage_800C9E50 == 1)
        {
            if (GetSelectedItem_800C79B8() != 0xFF)
            {
                DrawLargeTextBox_8002AF10(itemDescriptions_800C96C8[GetSelectedItem_800C79B8()], 0, 0xF);
                mode = 1;
            }
        }
        else if (menuPage_800C9E50 == 2)
        {
            Minion* minion = GetMinion_80010598(3, actingUnit_800C9C7C - 1);
            DrawAbilityDescription_8002C670(minion, 0, skillDescriptions_800C9B58, (short)GetMenuCursorIndex_8003DA54(skillMenu_800C92E4), 0xF);
            mode = 1;
        }
        else if (menuPage_800C9E50 == 3)
        {
            if (GetSelectedMagic_800C7A1C() < 0x1E)
            {
                DrawLargeTextBox_8002AF10(magicDescriptions_800C9978[GetSelectedMagic_800C7A1C()], 0, 0xF);
                mode = 1;
            }
        }
    }
    if (mode != 0)
    {
        mode = 1;
    }
    else
    {
        mode = menuState_800C9E48;
    }
    sel[0] = menuCommand_800C9E58.arg_4;
    sel[1] = actingUnit_800C9C7C;
    if (!(pageHideFlags_800C968C[menuPage_800C9E50][mode] & 0x10))
    {
        if (targetFlags_800C9E68 & 1)
        {
            cursor = -1;
        }
        else
        {
            cursor = (short)GetMenuCursorIndex_8003DA54(pageCursor_800C9E44);
        }
        if (GetSelectedCommand_800C78D0() == 4)
        {
            if (targetFlags_800C9E68 & 2)
            {
                menuTarget_800C9E54 = DrawTargetSelectMenu_8002D250(sel, 0, cursor, 0xF);
                flags |= 1;
            }
        }
        else if (GetSelectedCommand_800C78D0() == 6)
        {
        }
        else if (GetSelectedCommand_800C78D0() == 7)
        {
            if (targetFlags_800C9E68 & 2)
            {
                menuTarget_800C9E54 = DrawTargetSelectMenu_8002D250(sel, 1, cursor, 0xF);
                flags |= 1;
            }
        }
        else if (GetSelectedCommand_800C78D0() == 2)
        {
            menuTarget_800C9E54 = DrawTargetSelectMenu_8002D250(sel, 2, cursor, 0xF);
            flags |= 1;
        }
        else if (GetSelectedCommand_800C78D0() == 8)
        {
            menuTarget_800C9E54 = DrawTargetSelectMenu_8002D250(sel, 3, cursor, 0xF);
            flags |= 1;
        }
    }
    if (pageHideFlags_800C968C[menuPage_800C9E50][mode] & 2)
    {
        SetBattleFlag_800BC838(0x8000);
    }
    else
    {
        ClearBattleFlag_800BC850(0x8000);
    }
    if (pageHideFlags_800C968C[menuPage_800C9E50][mode] & 1)
    {
        SetBattleFlag_800BC838(0x10000);
    }
    else
    {
        ClearBattleFlag_800BC850(0x10000);
    }
    if (!(pageHideFlags_800C968C[menuPage_800C9E50][mode] & 4) && !(flags & 1))
    {
        DrawMenuWindows_8002A5A4(&menuWindows_800C9630);
    }
    if (!(pageHideFlags_800C968C[menuPage_800C9E50][mode] & 0x20) && !(flags & 2))
    {
        ListMenuState ref;
        ref.windowFlags_4 = 2;
        ref.ot_6 = 0xF;
        ref.field_8 = -1;
        ref.minion_C = 0;
        ref.fieldMenu_A = 0;
        ref.cursor_0 = itemMenu_800C9308->cursor_8;
        ref.scroll_2 = itemMenu_800C9308->scroll_A;
        DrawItemList_8002C728(&ref);
    }
    if (!(pageHideFlags_800C968C[menuPage_800C9E50][mode] & 0x40) && !(flags & 4))
    {
        ListMenuState ref;
        ref.windowFlags_4 = 2;
        ref.ot_6 = 0xF;
        ref.field_8 = -1;
        ref.cursor_0 = skillMenu_800C92E4->cursor_8;
        ref.scroll_2 = skillMenu_800C92E4->scroll_A;
        ref.minion_C = GetMinion_80010598(3, actingUnit_800C9C7C - 1);
        ref.fieldMenu_A = 0;
        DrawAbilityList_8002CE28(&ref, 0);
        previewMpChange_800C9182 = -GetSkillMpCost_80031A04(ref.minion_C->skills_DE.slot, MenuIndexToSkillSlot_80031BDC((short)GetMenuCursorIndex_8003DA54(skillMenu_800C92E4)));
    }
    if (!(pageHideFlags_800C968C[menuPage_800C9E50][mode] & 0x80) && !(flags & 8))
    {
        ListMenuState ref;
        short sz[2];
        ref.windowFlags_4 = 2;
        ref.ot_6 = 0xF;
        ref.field_8 = -1;
        ref.cursor_0 = magicMenu_800C92F0->cursor_8;
        ref.scroll_2 = magicMenu_800C92F0->scroll_A;
        ref.minion_C = GetMinion_80010598(3, actingUnit_800C9C7C - 1);
        sz[0] = 0x60;
        ref.fieldMenu_A = 0;
        sz[1] = 0x45;
        DrawMagicList_8002CAC8(&ref, sz);
        previewMpChange_800C9182 = -GetMagicMpCost_8001AC58(FindNthMagicBit_8001AEC0(&ref.minion_C->magicBits_F4, (short)GetMenuCursorIndex_8003DA54(magicMenu_800C92F0)));
    }
    DrawButtonHelpBar_8002B004(pageButtonHelp_800C9674[menuPage_800C9E50], 0, 0xF);
}

void PreviewCommandResult_800C83B0()
{
    TargetQuery query;
    BattleCmd cmd;
    ActionResult res;
    unsigned int i;
    int bit;
    UnitStatus* self;
    UnitStatus* target;
    cmd = menuCommand_800C9E58;
    if (menuPage_800C9E50 == 4)
    {
        previewHpChange_800C9180 = 0;
        previewMpChange_800C9182 = 0;
        self = GetUnitStatus_80014390(actingUnit_800C9C7C);
        for (i = 0; i < 4; i++)
        {
            bit = 1 << i;
            if ((menuCommand_800C9E58.targets_C & bit) && i == shownUnit_800C9C99)
            {
                target = GetUnitStatus_80014390(i & 0xFF);

                res.areaElement_24 = shownAreaElement_800C9D82;
                res.fixedElement_26 = (signed char)fixedStageElement_800C9D83;
                cmd.targets_C = bit;
                ResolveBattleAction_80012BB0(self, target, &cmd, &res);
                if (IsDrainAction_80013228(self, target, &cmd, &res) == 0 && (menuCommand_800C9E58.mask_8 & bit))
                {
                    previewHpChange_800C9180 -= res.actorHpCost_C;
                    previewMpChange_800C9182 -= res.actorMpCost_10;
                    previewHpChange_800C9180 -= res.actorHpDamage_14;
                    previewMpChange_800C9182 -= res.actorMpDamage_18;
                }
                previewHpChange_800C9180 -= res.hpDamage_1C;
                previewMpChange_800C9182 -= res.mpDamage_20;
                if (previewHpChange_800C9180 > target->hp_8.max_2 - target->hp_8.cur_0)
                {
                    previewHpChange_800C9180 = target->hp_8.max_2 - target->hp_8.cur_0;
                }
                if (previewMpChange_800C9182 > target->mp_C.max_2 - target->mp_C.cur_0)
                {
                    previewMpChange_800C9182 = target->mp_C.max_2 - target->mp_C.cur_0;
                }
            }
        }
        query.id_0 = menuCommand_800C9E58.arg_4;
        query.actor_2 = actingUnit_800C9C7C;
        query.target_4 = menuTarget_800C9E54;
        query.f6 = 0;
        if (GetSelectedCommand_800C78D0() == 4)
        {
            if (CheckItemOnTarget_80033DF4(&query))
            {
                previewHpChange_800C9180 = 0;
                previewMpChange_800C9182 = 0;
            }
        }
        else if (GetSelectedCommand_800C78D0() == 6)
        {
            if (CheckUsableStub_80034124(&query))
            {
                previewHpChange_800C9180 = 0;
            }
        }
        else if (GetSelectedCommand_800C78D0() == 7)
        {
            if (CheckMagicUsable_80034068(&query))
            {
                previewHpChange_800C9180 = 0;
            }
        }
    }
}

void SetCameraFocusTargets_800C8694(unsigned char page)
{
    if (page == 4 && (targetFlags_800C9E68 & 5) == 4)
    {
        unsigned char* bits = enemyTargets_800C9E70.bits_2;
        newCameraFocus_800C9E3C = bits[(short)GetMenuCursorIndex_8003DA54(enemyTargetMenu_800C9314)];
    }
    else
    {
        newCameraFocus_800C9E3C = enemyMask_800C9E4C;
    }
}

void UpdateTargetCamera_800C8710()
{
    if (cameraFocus_800C9E38 != newCameraFocus_800C9E3C)
    {
        cameraFocus_800C9E38 = newCameraFocus_800C9E3C;
        FocusBattleCamera_80037AE0((unsigned short)newCameraFocus_800C9E3C);
        TurnUnitsToward_800BC468(newCameraFocus_800C9E3C, 1 << actingUnit_800C9C7C);
    }
}

void MenuInput_800C8768()
{
    if (IsConfirmPressedP1_8003D380(0))
    {
        if (IsMenuSelectionValid_800C7530())
        {
            PlaySfx_80031494(0x7E);
            AdvanceMenuPage_800C7A6C();
        }
        else
        {
            PlaySfx_80031494(0x7C);
            if (menuErrorText_800C9E7C)
            {
                menuErrorTimer_800C9E51 = 0x96;
                menuState_800C9E48 = 1;
            }
        }
    }
    else if (IsCancelPressedP1_8003D41C(0))
    {
        if (menuPage_800C9E50)
        {
            unsigned char page;
            PlaySfx_80031494(0x7D);
            page = prevMenuPage_800C9E40;
            prevMenuPage_800C9E40 = 0;
            menuPage_800C9E50 = page;
        }
    }
}

void DrawMenuHelpText_800C8828(int text)
{
    short rect[4];
    short origin[4];
    short pos[2];
    int lines[1];
    rect[0] = 0x19;
    rect[1] = 0x8A;
    rect[2] = MeasureTextWidth_8003E4C8(text) + 4;
    rect[3] = 0x12;
    lines[0] = text;
    origin[0] = rect[0];
    origin[1] = rect[1];
    pos[0] = rect[0] + 2;
    pos[1] = rect[1] + 4;
    DrawTextLinesWindow_8002AE38(lines, pos, 0xF, rect, 1);
}

void DrawMenuMessage_800C88AC(int text)
{
    int lines[4];
    lines[0] = text;
    lines[1] = 0;
    lines[2] = 0;
    lines[3] = 0;
    DrawLargeTextBox_8002AF10(lines, 0, 0xF);
}

void MenuShowError_800C88E4()
{
    if (padPressed_8009194C[0])
    {
        menuErrorTimer_800C9E51 = 0;
    }
    if (menuErrorTimer_800C9E51 == 0)
    {
        menuState_800C9E48 = 0;
    }
    else
    {
        menuErrorTimer_800C9E51--;
    }
    if (menuErrorText_800C9E7C)
    {
        if (menuPage_800C9E50 == 0)
        {
            DrawMenuHelpText_800C8828(menuErrorText_800C9E7C);
        }
        else
        {
            DrawMenuMessage_800C88AC(menuErrorText_800C9E7C);
        }
    }
}

void CommitMenuCommand_800C8970()
{
    int kind;
    curCommand_800C9C88.kind_0 = menuCommand_800C9E58.kind_0;
    curCommand_800C9C88.arg_4 = menuCommand_800C9E58.arg_4;
    curCommand_800C9C88.mask_8 = menuCommand_800C9E58.mask_8;
    kind = menuCommand_800C9E58.kind_0;
    if (kind == 7 || kind == 0x12)
    {
        curCommand_800C9C88.targets_C = enemyMask_800C9E4C;
    }
    else if (kind == 8)
    {
        curCommand_800C9C88.targets_C = 0;
    }
    else
    {
        curCommand_800C9C88.targets_C = menuCommand_800C9E58.targets_C;
    }
    commandUnit_800C9C98 = LowestSetBit_80014358(menuCommand_800C9E58.targets_C);
}

void BattleMenuTask_800C8A08(EventEntry* task, int buffer)
{
    pageCursor_800C9E44 = GetPageCursor_800C73B8(menuPage_800C9E50);
    HighlightTargetWindows_800C7424(menuPage_800C9E50);
    UpdateMenuCursor_8003D794(pageCursor_800C9E44, 0);
    UpdateMenuWindows_800C7CE8(menuPage_800C9E50);
    BattleMenuDraw_800C7DA8();
    menuCommand_800C9E58.targets_C = GetSelectedTargets_800C791C();
    UpdateShownUnit_800C7D54(menuPage_800C9E50);
    PreviewCommandResult_800C83B0();
    SetCameraFocusTargets_800C8694(menuPage_800C9E50);
    UpdateTargetCamera_800C8710();
    menuStateFns_800C966C[menuState_800C9E48](task, buffer);
    if (menuPage_800C9E50 == 5)
    {
        savedEnemyCursor_800C9D56 = enemyTargetMenu_800C9314->cursor_8;
        ResetWindowHighlights_800BFC10();
        CommitMenuCommand_800C8970();
        previewHpChange_800C9180 = 0;
        previewMpChange_800C9182 = 0;
        task->flags = (task->flags & ~1) | 0x8000;
    }
}
