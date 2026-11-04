// COMBCOM.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "minion_menu.h"
#include "combcom.h"

typedef struct CombComTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombComTask;

// the battle command being chosen (COMBBTL's CombBtlCmd)
// a menu entry / window (0x38 bytes)
// DrawMenuWindows_8002A5A4's argument
extern unsigned char targetSlotLo_800CD83C; // low byte of targetSlot_800CD83C
extern unsigned char actorSlot_800A85BD;
extern unsigned char dword_800A4078[];
extern int dword_800A3A88;
extern int GetSlotMagicBits_800A11BC(int);
extern int CountTeamMinions_800A1AAC(int);
extern int GetMenuCursorIndex_8003DA54(void*);
extern int CountMagicBits_8001AE54(int);
extern int FindNthMagicBit_8001AEC0(int, int);

int dword_800C9E88 SDATA = 34;
const char aUseNormalAttack_800C9E8C[] = "\202t\202\223\202\205\201@\202\216\202\217\202\222\202\215\202\201\202\214\201@\202\201\202\224\202\224\202\201\202\203\202\213"; // Use normal attack
const char aDefendToReduceD_800C9EB0[] = "\202c\202\205\202\206\202\205\202\216\202\204\201@\202\224\202\217\201@\202\222\202\205\202\204\202\225\202\203\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205"; // Defend to reduce damage
const char aUseSpecialAttac_800C9EE0[] = "\202t\202\223\202\205\201@\202\223\202\220\202\205\202\203\202\211\202\201\202\214\201@\202\201\202\224\202\224\202\201\202\203\202\213"; // Use special attack
const char aUseMagicSpell_800C9F08[] = "\202t\202\223\202\205\201@\202\215\202\201\202\207\202\211\202\203\201@\202\223\202\220\202\205\202\214\202\214"; // Use magic spell
const char aChangeCurrentFi_800C9F28[] = "\202b\202\210\202\201\202\216\202\207\202\205\201@\202\203\202\225\202\222\202\222\202\205\202\216\202\224\201@\202\206\202\211\202\207\202\210\202\224\202\205\202\222"; // Change current fighter
const char aCannotSummonInt_800C9F58[] = "\202b\202\201\202\216\202\216\202\217\202\224\201@\202\223\202\225\202\215\202\215\202\217\202\216\201@\202\211\202\216\202\224\202\217\201@\202\203\202\217\202\215\202\202\202\201\202\224"; // Cannot summon into combat
const char aNotEnoughMana_800C9F8C[] = "\202m\202\217\202\224\201@\202\205\202\216\202\217\202\225\202\207\202\210\201@\202l\202\201\202\216\202\201"; // Not enough Mana
const int aBlank_800C9FAC = 0;
const char aNoNeedToUseItem_800C9FB0[] = "\202m\202\217\201@\202\216\202\205\202\205\202\204\201@\202\224\202\217\201@\202\225\202\223\202\205\201@\202\211\202\224\202\205\202\215"; // No need to use item
const char aCannotSelect_800C9FD8[] = "\202b\202\201\202\216\202\216\202\217\202\224\201@\202\223\202\205\202\214\202\205\202\203\202\224"; // Cannot select
const char aNoDivineMinions_800C9FF4[] = "\202m\202\217\201@\202c\202\211\202\226\202\211\202\216\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\202\223\201@\202\224\202\217\201@\202\203\202\210\202\201\202\216\202\207\202\205\201@\202\227\202\211\202\224\202\210"; // No Divine Minions to change with
const char aPause_800CA038[] = "\202o\202\201\202\225\202\223\202\205"; // Pause
const char aDescription_800CA044[] = "\202c\202\205\202\223\202\203\202\222\202\211\202\220\202\224\202\211\202\217\202\216"; // Description
const char aSelect_800CA05C[] = "\202r\202\205\202\214\202\205\202\203\202\224"; // Select
const char aQuit_800CA06C[] = "\202p\202\225\202\211\202\224"; // Quit
const char aEffectivenessOf_800CA078[] = "\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\202\216\202\205\202\223\202\223\201@\202\217\202\206\201@\202\205\202\201\202\222\202\224\202\210\201@\202\206\202\217\202\222\201@\202\204\202\225\202\222\202\201\202\224\202\211\202\217\202\216\201@\202\217\202\206\201@\202\202\202\201\202\224\202\224\202\214\202\205\201D"; // effectiveness of earth for duration of battle.
const char aIncreasesWindAt_800CA0D8[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223\201@\202\227\202\211\202\216\202\204\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\220\202\217\202\227\202\205\202\222\201@\202\201\202\216\202\204\201@\202\204\202\205\202\203\202\222\202\205\202\201\202\223\202\205\202\223"; // Increases wind attack power and decreases
const char aEnhanceWind_800CA12C[] = "\202d\202\216\202\210\202\201\202\216\202\203\202\205\201@\202v\202\211\202\216\202\204"; // Enhance Wind
const char aEffectivenessOf_800CA148[] = "\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\202\216\202\205\202\223\202\223\201@\202\217\202\206\201@\202\227\202\201\202\224\202\205\202\222\201@\202\206\202\217\202\222\201@\202\204\202\225\202\222\202\201\202\224\202\211\202\217\202\216\201@\202\217\202\206\201@\202\202\202\201\202\224\202\224\202\214\202\205\201D"; // effectiveness of water for duration of battle.
const char aIncreasesEarthA_800CA1A8[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223\201@\202\205\202\201\202\222\202\224\202\210\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\220\202\217\202\227\202\205\202\222\201@\202\201\202\216\202\204\201@\202\204\202\205\202\203\202\222\202\205\202\201\202\223\202\205\202\223"; // Increases earth attack power and decreases
const char aEnhanceEarth_800CA200[] = "\202d\202\216\202\210\202\201\202\216\202\203\202\205\201@\202d\202\201\202\222\202\224\202\210"; // Enhance Earth
const char aEffectivenessOf_800CA21C[] = "\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\202\216\202\205\202\223\202\223\201@\202\217\202\206\201@\202\206\202\211\202\222\202\205\201@\202\206\202\217\202\222\201@\202\204\202\225\202\222\202\201\202\224\202\211\202\217\202\216\201@\202\217\202\206\201@\202\202\202\201\202\224\202\224\202\214\202\205\201D"; // effectiveness of fire for duration of battle.
const char aIncreasesWaterA_800CA278[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223\201@\202\227\202\201\202\224\202\205\202\222\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\220\202\217\202\227\202\205\202\222\201@\202\201\202\216\202\204\201@\202\204\202\205\202\203\202\222\202\205\202\201\202\223\202\205\202\223"; // Increases water attack power and decreases
const char aEnhanceWater_800CA2D0[] = "\202d\202\216\202\210\202\201\202\216\202\203\202\205\201@\202v\202\201\202\224\202\205\202\222"; // Enhance Water
const char aEffectivenessOf_800CA2EC[] = "\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\202\216\202\205\202\223\202\223\201@\202\217\202\206\201@\202\227\202\211\202\216\202\204\201@\202\206\202\217\202\222\201@\202\204\202\225\202\222\202\201\202\224\202\211\202\217\202\216\201@\202\217\202\206\201@\202\202\202\201\202\224\202\224\202\214\202\205\201D"; // effectiveness of wind for duration of battle.
const char aIncreasesFireAt_800CA348[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223\201@\202\206\202\211\202\222\202\205\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\220\202\217\202\227\202\205\202\222\201@\202\201\202\216\202\204\201@\202\204\202\205\202\203\202\222\202\205\202\201\202\223\202\205\202\223"; // Increases fire attack power and decreases
const char aEnhanceFire_800CA39C[] = "\202d\202\216\202\210\202\201\202\216\202\203\202\205\201@\202e\202\211\202\222\202\205"; // Enhance Fire
const char aCausesAnEnemyTo_800CA3B8[] = "\202b\202\201\202\225\202\223\202\205\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\224\202\217\201@\202\206\202\201\202\214\202\214\201@\202\204\202\205\202\201\202\204\201@\202\211\202\215\202\215\202\205\202\204\202\211\202\201\202\224\202\205\202\214\202\231\201D"; // Causes an enemy to fall dead immediately.
const char aDeath_800CA40C[] = "\202c\202\205\202\201\202\224\202\210"; // Death
const char aTurnsAnEnemyInt_800CA418[] = "\202s\202\225\202\222\202\216\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\211\202\216\202\224\202\217\201@\202\223\202\224\202\217\202\216\202\205\201D"; // Turns an enemy into stone.
const char aFleshToStone_800CA450[] = "\202e\202\214\202\205\202\223\202\210\201@\202\224\202\217\201@\202r\202\224\202\217\202\216\202\205"; // Flesh to Stone
const char aPutsAnEnemyToSl_800CA470[] = "\202o\202\225\202\224\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\224\202\217\201@\202\223\202\214\202\205\202\205\202\220\201D"; // Puts an enemy to sleep.
const char aSleep_800CA4A0[] = "\202r\202\214\202\205\202\205\202\220"; // Sleep
const char aPoisonsAnEnemy_800CA4AC[] = "\202o\202\217\202\211\202\223\202\217\202\216\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201D"; // Poisons an enemy.
const char aPoison_800CA4D0[] = "\202o\202\217\202\211\202\223\202\217\202\216"; // Poison
const char aEndsOnceItProte_800CA4E0[] = "\202d\202\216\202\204\202\223\201@\202\217\202\216\202\203\202\205\201@\202\211\202\224\201@\202\220\202\222\202\217\202\224\202\205\202\203\202\224\202\223\201@\202\203\202\201\202\223\202\224\202\205\202\222\201@\202\224\202\210\202\222\202\205\202\205\201@\202\224\202\211\202\215\202\205\202\223\201D"; // Ends once it protects caster three times.
const char aProtectsAgainst_800CA534[] = "\202o\202\222\202\217\202\224\202\205\202\203\202\224\202\223\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\220\202\217\202\211\202\223\202\217\202\216\201C\201@\202\223\202\214\202\205\202\205\202\220\201C\201@\202\201\202\216\202\204\201@\202\206\202\214\202\205\202\223\202\210\201@\202\224\202\217\201@\202\223\202\224\202\217\202\216\202\205\201D"; // Protects against poison, sleep, and flesh to stone.
const char aProtection_800CA59C[] = "\202o\202\222\202\217\202\224\202\205\202\203\202\224\202\211\202\217\202\216"; // Protection
const char aCuresPoisonAndT_800CA5B4[] = "\202b\202\225\202\222\202\205\202\223\201@\202\220\202\217\202\211\202\223\202\217\202\216\201@\202\201\202\216\202\204\201@\202\224\202\225\202\222\202\216\202\223\201@\202\223\202\224\202\217\202\216\202\205\201@\202\202\202\201\202\203\202\213\201@\202\224\202\217\201@\202\206\202\214\202\205\202\223\202\210\201D"; // Cures poison and turns stone back to flesh.
const char aReturnToNormal_800CA60C[] = "\202q\202\205\202\224\202\225\202\222\202\216\201@\202\224\202\217\201@\202m\202\217\202\222\202\215\202\201\202\214"; // Return to Normal
const char aRestoresAllHP_800CA630[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\202\223\201@\202\201\202\214\202\214\201@\202g\202o\201D"; // Restores all HP.
const char aRestoreAllHP_800CA654[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\201@\202`\202\214\202\214\201@\202g\202o"; // Restore All HP
const char aRestoresSomeHP_800CA674[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\202\223\201@\202\223\202\217\202\215\202\205\201@\202g\202o\201D"; // Restores some HP.
const char aRestoreHP_800CA698[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\201@\202g\202o"; // Restore HP
const char aCuresPoison_800CA6B0[] = "\202b\202\225\202\222\202\205\202\223\201@\202\220\202\217\202\211\202\223\202\217\202\216\201D"; // Cures poison.
const char aCurePoison_800CA6CC[] = "\202b\202\225\202\222\202\205\201@\202o\202\217\202\211\202\223\202\217\202\216"; // Cure Poison
const char aAdvancedWindAtt_800CA6E4[] = "\202`\202\204\202\226\202\201\202\216\202\203\202\205\202\204\201@\202v\202\211\202\216\202\204\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Advanced Wind Attack
const char aWindAttackAllEn_800CA710[] = "\202v\202\211\202\216\202\204\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201j"; // Wind Attack (All Enemies)
const char aHigherWindEleme_800CA744[] = "\202g\202\211\202\207\202\210\202\205\202\222\201@\202\227\202\211\202\216\202\204\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\201@\202\222\202\201\202\224\202\211\202\217\201@\202\231\202\211\202\205\202\214\202\204\202\223\201@\202\215\202\217\202\222\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205\201D"; // Higher wind element ratio yields more damage.
const char aExtraDamageVsEa_800CA7A0[] = "\202d\202\230\202\224\202\222\202\201\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\226\202\223\201D\201@\202d\202\201\202\222\202\224\202\210"; // Extra damage vs. Earth
const char aWindAttackOneEn_800CA7D0[] = "\202v\202\211\202\216\202\204\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202n\202\216\202\205\201@\202d\202\216\202\205\202\215\202\231\201j"; // Wind Attack (One Enemy)
const char aAdvancedEarthAt_800CA800[] = "\202`\202\204\202\226\202\201\202\216\202\203\202\205\202\204\201@\202d\202\201\202\222\202\224\202\210\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Advanced Earth Attack
const char aEarthAttackAllE_800CA82C[] = "\202d\202\201\202\222\202\224\202\210\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201j"; // Earth Attack (All Enemies)
const char aHigherEarthElem_800CA864[] = "\202g\202\211\202\207\202\210\202\205\202\222\201@\202\205\202\201\202\222\202\224\202\210\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\201@\202\222\202\201\202\224\202\211\202\217\201@\202\231\202\211\202\205\202\214\202\204\202\223\201@\202\215\202\217\202\222\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205\201D"; // Higher earth element ratio yields more damage.
const char aExtraDamageVsWa_800CA8C4[] = "\202d\202\230\202\224\202\222\202\201\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\226\202\223\201D\201@\202v\202\201\202\224\202\205\202\222"; // Extra damage vs. Water
const char aEarthAttackOneE_800CA8F4[] = "\202d\202\201\202\222\202\224\202\210\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202n\202\216\202\205\201@\202d\202\216\202\205\202\215\202\231\201j"; // Earth Attack (One Enemy)
const char aAdvancedWaterAt_800CA928[] = "\202`\202\204\202\226\202\201\202\216\202\203\202\205\202\204\201@\202v\202\201\202\224\202\205\202\222\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Advanced Water Attack
const char aWaterAttackAllE_800CA954[] = "\202v\202\201\202\224\202\205\202\222\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201j"; // Water Attack (All Enemies)
const char aHigherWaterElem_800CA98C[] = "\202g\202\211\202\207\202\210\202\205\202\222\201@\202\227\202\201\202\224\202\205\202\222\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\201@\202\222\202\201\202\224\202\211\202\217\201@\202\231\202\211\202\205\202\214\202\204\202\223\201@\202\215\202\217\202\222\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205\201D"; // Higher water element ratio yields more damage.
const char aExtraDamageVsFi_800CA9EC[] = "\202d\202\230\202\224\202\222\202\201\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\226\202\223\201D\201@\202e\202\211\202\222\202\205"; // Extra damage vs. Fire
const char aWaterAttackOneE_800CAA18[] = "\202v\202\201\202\224\202\205\202\222\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202n\202\216\202\205\201@\202d\202\216\202\205\202\215\202\231\201j"; // Water Attack (One Enemy)
const char aAdvancedFireAtt_800CAA4C[] = "\202`\202\204\202\226\202\201\202\216\202\203\202\205\202\204\201@\202e\202\211\202\222\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Advanced Fire Attack
const char aFireAttackAllEn_800CAA78[] = "\202e\202\211\202\222\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201j"; // Fire Attack (All Enemies)
const char aHigherFireEleme_800CAAAC[] = "\202g\202\211\202\207\202\210\202\205\202\222\201@\202\206\202\211\202\222\202\205\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\201@\202\222\202\201\202\224\202\211\202\217\201@\202\231\202\211\202\205\202\214\202\204\202\223\201@\202\215\202\217\202\222\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205\201D"; // Higher fire element ratio yields more damage.
const char aExtraDamageVsAi_800CAB08[] = "\202d\202\230\202\224\202\222\202\201\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\226\202\223\201D\201@\202`\202\211\202\222"; // Extra damage vs. Air
const char aFireAttackOneEn_800CAB34[] = "\202e\202\211\202\222\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202n\202\216\202\205\201@\202d\202\216\202\205\202\215\202\231\201j"; // Fire Attack (One Enemy)
const char aMakesItEasierTo_800CAB64[] = "\202l\202\201\202\213\202\205\202\223\201@\202\211\202\224\201@\202\205\202\201\202\223\202\211\202\205\202\222\201@\202\224\202\217\201@\202\213\202\211\202\214\202\214\201@\202\227\202\211\202\216\202\207\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\201\202\216\202\204"; // Makes it easier to kill winged enemies and
const char aSpecialAttackBr_800CABBC[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202a\202\222\202\205\202\201\202\213\201@\202v\202\211\202\216\202\207\202\223\201j"; // Special Attack (Break Wings)
const char aSlightlyMoreDif_800CABF8[] = "\202\223\202\214\202\211\202\207\202\210\202\224\202\214\202\231\201@\202\215\202\217\202\222\202\205\201@\202\204\202\211\202\206\202\206\202\211\202\203\202\225\202\214\202\224\201@\202\206\202\217\202\222\201@\202\224\202\210\202\205\202\215\201@\202\224\202\217\201@\202\223\202\203\202\217\202\222\202\205\201@\202\201\201@\202\210\202\211\202\224\201D"; // slightly more difficult for them to score a hit.
const char aMakesItEasierTo_800CAC5C[] = "\202l\202\201\202\213\202\205\202\223\201@\202\211\202\224\201@\202\205\202\201\202\223\202\211\202\205\202\222\201@\202\224\202\217\201@\202\213\202\211\202\214\202\214\201@\202\224\202\227\202\217\201|\202\214\202\205\202\207\202\207\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\201\202\216\202\204"; // Makes it easier to kill two-legged enemies and
const char aSpecialAttackBr_800CACBC[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202a\202\222\202\205\202\201\202\213\201@\202k\202\205\202\207\202\223\201j"; // Special Attack (Break Legs)
const char aItMoreDifficult_800CACF4[] = "\202\211\202\224\201@\202\215\202\217\202\222\202\205\201@\202\204\202\211\202\206\202\206\202\211\202\203\202\225\202\214\202\224\201@\202\206\202\217\202\222\201@\202\224\202\210\202\205\202\215\201@\202\224\202\217\201@\202\223\202\203\202\217\202\222\202\205\201@\202\201\201@\202\210\202\211\202\224\201D"; // it more difficult for them to score a hit.
const char aReducesAnEnemie_800CAD4C[] = "\202q\202\205\202\204\202\225\202\203\202\205\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202g\202o\201@\202\224\202\217\201@\202P\201@\202\201\202\216\202\204\201@\202\215\202\201\202\213\202\205\202\223"; // Reduces an enemies HP to 1 and makes
const char aSpecialAttackCr_800CAD98[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202b\202\222\202\211\202\224\202\211\202\203\202\201\202\214\201@\202g\202\211\202\224\201j"; // Special Attack (Critical Hit)
const char aBringsEnemiesTo_800CADD4[] = "\202a\202\222\202\211\202\216\202\207\202\223\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\224\202\217\201@\202\224\202\210\202\205\201@\202\202\202\222\202\211\202\216\202\213\201@\202\217\202\206\201@\202\204\202\205\202\201\202\224\202\210\201D"; // Brings enemies to the brink of death.
const char aAttacksAllEnemi_800CAE20[] = "\202`\202\224\202\224\202\201\202\203\202\213\202\223\201@\202\201\202\214\202\214\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\201\202\224\201@\202\217\202\216\202\203\202\205\201D"; // Attacks all enemies at once.
const char aSpecialAttackAl_800CAE5C[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201j"; // Special Attack (All Enemies)
const char aUsesItToRestore_800CAE98[] = "\202\225\202\223\202\205\202\223\201@\202\211\202\224\201@\202\224\202\217\201@\202\222\202\205\202\223\202\224\202\217\202\222\202\205\201@\202\201\202\224\202\224\202\201\202\203\202\213\202\205\202\222\201f\202\223\201@\202l\202\201\202\216\202\201\201D"; // uses it to restore attacker's Mana.
const char aStealsSomeManaF_800CAEE0[] = "\202r\202\224\202\205\202\201\202\214\202\223\201@\202\223\202\217\202\215\202\205\201@\202l\202\201\202\216\202\201\201@\202\206\202\222\202\217\202\215\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\201\202\216\202\204"; // Steals some Mana from an enemy and
const char aSpecialAttackAb_800CAF28[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\202\202\223\202\217\202\222\202\202\201@\202l\202\201\202\216\202\201\201j"; // Special Attack (Absorb Mana)
const char aAnEnemyToRestor_800CAF64[] = "\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\224\202\217\201@\202\222\202\205\202\223\202\224\202\217\202\222\202\205\201@\202\224\202\210\202\205\201@\202\201\202\224\202\224\202\201\202\203\202\213\202\205\202\222\201f\202\223\201@\202g\202o\201D"; // an enemy to restore the attacker's HP.
const char aTakesSomeOfTheD_800CAFB4[] = "\202s\202\201\202\213\202\205\202\223\201@\202\223\202\217\202\215\202\205\201@\202\217\202\206\201@\202\224\202\210\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\211\202\216\202\206\202\214\202\211\202\203\202\224\202\205\202\204\201@\202\217\202\216"; // Takes some of the damage inflicted on
const char aSpecialAttackAb_800CB000[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\202\202\223\202\217\202\222\202\202\201@\202g\202o\201j"; // Special Attack (Absorb HP)
const char aMoreDifficultFo_800CB038[] = "\202\215\202\217\202\222\202\205\201@\202\204\202\211\202\206\202\206\202\211\202\203\202\225\202\214\202\224\201@\202\206\202\217\202\222\201@\202\224\202\210\202\205\202\215\201@\202\224\202\217\201@\202\223\202\203\202\217\202\222\202\205\201@\202\201\201@\202\210\202\211\202\224\201D"; // more difficult for them to score a hit.
const char aCausesAnEnemyTo_800CB088[] = "\202b\202\201\202\225\202\223\202\205\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\224\202\217\201@\202\214\202\217\202\223\202\205\201@\202l\202\201\202\216\202\201\201@\202\201\202\216\202\204\201@\202\215\202\201\202\213\202\205\202\223\201@\202\211\202\224\201@\202\223\202\214\202\211\202\207\202\210\202\224\202\214\202\231"; // Causes an enemy to lose Mana and makes it slightly
const char aSpecialAttackDe_800CB0F0[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202c\202\205\202\223\202\224\202\222\202\217\202\231\201@\202l\202\201\202\216\202\201\201j"; // Special Attack (Destroy Mana)
const char aPhysicallyDamag_800CB12C[] = "\202o\202\210\202\231\202\223\202\211\202\203\202\201\202\214\202\214\202\231\201@\202\204\202\201\202\215\202\201\202\207\202\205\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\201\202\216\202\204\201@\202\224\202\225\202\222\202\216\202\223\201@\202\224\202\210\202\205\202\215\201@\202\224\202\217\201@\202\223\202\224\202\217\202\216\202\205\201D"; // Physically damages an enemy and turns them to stone.
const char aSpecialFleshToS_800CB198[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202e\202\214\202\205\202\223\202\210\201|\202\224\202\217\201|\202r\202\224\202\217\202\216\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Flesh-to-Stone Attack
const char aPhysicallyDamag_800CB1D4[] = "\202o\202\210\202\231\202\223\202\211\202\203\202\201\202\214\202\214\202\231\201@\202\204\202\201\202\215\202\201\202\207\202\205\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\201\202\216\202\204\201@\202\220\202\225\202\224\202\223\201@\202\224\202\210\202\205\202\215\201@\202\224\202\217\201@\202\223\202\214\202\205\202\205\202\220\201D"; // Physically damages an enemy and puts them to sleep.
const char aSpecialSleepAtt_800CB23C[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202r\202\214\202\205\202\205\202\220\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Sleep Attack
const char aPhysicallyDamag_800CB268[] = "\202o\202\210\202\231\202\223\202\211\202\203\202\201\202\214\202\214\202\231\201@\202\204\202\201\202\215\202\201\202\207\202\205\202\223\201@\202\201\202\216\202\204\201@\202\220\202\217\202\211\202\223\202\217\202\216\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201D"; // Physically damages and poisons an enemy.
const char aSpecialPoisonAt_800CB2BC[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202o\202\217\202\211\202\223\202\217\202\216\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Poison Attack
const char aVeryEffectiveAg_800CB2E8[] = "\202u\202\205\202\222\202\231\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\205\202\201\202\222\202\224\202\210\201|\202\202\202\201\202\223\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Very effective against earth-based enemies.
const char aSpecialWindAtta_800CB340[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202v\202\211\202\216\202\204\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Wind Attack
const char aVeryEffectiveAg_800CB368[] = "\202u\202\205\202\222\202\231\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\227\202\211\202\216\202\204\201|\202\202\202\201\202\223\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Very effective against wind-based enemies.
const char aSpecialFireAtta_800CB3C0[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202e\202\211\202\222\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Fire Attack
const char aVeryEffectiveAg_800CB3E8[] = "\202u\202\205\202\222\202\231\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\206\202\211\202\222\202\205\201|\202\202\202\201\202\223\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Very effective against fire-based enemies.
const char aSpecialWaterAtt_800CB440[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202v\202\201\202\224\202\205\202\222\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Water Attack
const char aVeryEffectiveAg_800CB46C[] = "\202u\202\205\202\222\202\231\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\227\202\201\202\224\202\205\202\222\201|\202\202\202\201\202\223\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Very effective against water-based enemies.
const char aSpecialEarthAtt_800CB4C4[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202d\202\201\202\222\202\224\202\210\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Earth Attack
const CombComItem pauseTitleItem_800CB4F0 = {
    8,
    1,
    (void *)37,
    (int)&uiTiySprts_8008D620,
    (int)&uiTiyTPages_8008D3F4,
    121,
    79,
    {
        0x18004E, 0x50002, 1, 0, 0, 0, -1, -1,
        -1,
    },
};
const CombComItem pauseItemStart_800CB528 = {
    8,
    1,
    (void *)35,
    (int)&uiTiySprts_8008D620,
    (int)&uiTiyTPages_8008D3F4,
    126,
    104,
    {
        0x140044, 0x40002, 1, 0, 0, 0, -1, -1,
        -1,
    },
};
const CombComItem pauseItemGiveUp_800CB560 = {
    8,
    1,
    (void *)65,
    (int)&uiTiySprts_8008D620,
    (int)&uiTiyTPages_8008D3F4,
    126,
    125,
    {
        0x140044, 0x40002, 1, 0, 0, 0, -1, -1,
        -1,
    },
};
const CombComItem pauseItemReturn_800CB598 = {
    8,
    1,
    (void *)25,
    (int)&uiTiySprts_8008D620,
    (int)&uiTiyTPages_8008D3F4,
    126,
    146,
    {
        0x140044, 0x40002, 1, 0, 0, 0, -1, -1,
        -1,
    },
};
const CombComMenu menuWinTmpl_800CB5D0 = { 2, 0, 8 };
const char aStartFight_800CB5E8[] = "\202r\202\224\202\201\202\222\202\224\201@\202\206\202\211\202\207\202\210\202\224"; // Start fight
const char aGiveUpResultsIn_800CB600[] = "\202f\202\211\202\226\202\205\201@\202\225\202\220\201@\201i\202\222\202\205\202\223\202\225\202\214\202\224\202\223\201@\202\211\202\216\201@\202\201\201@\202\214\202\217\202\223\202\223\201j"; // Give up (results in a loss)
const char aReturnToStartOf_800CB638[] = "\202q\202\205\202\224\202\225\202\222\202\216\201@\202\224\202\217\201@\202\223\202\224\202\201\202\222\202\224\201@\202\217\202\206\201@\202\224\202\217\202\225\202\222\202\216\202\201\202\215\202\205\202\216\202\224"; // Return to start of tournament
const CombComMsgs3 pauseOptionDescs_800CB674 = { { (int)aStartFight_800CB5E8, (int)aGiveUpResultsIn_800CB600, (int)aReturnToStartOf_800CB638 } };
const CombComPos2 skillListPos_800CB680 = { {
        { 101, 104 },
        { 10, 104 },
    } };
const CombComPos2 magicListPos_800CB688 = { {
        { 110, 100 },
        { 90, 100 },
    } };
const int targetItem0_800CB690[14] = {
    0x40010, 0, 0, 0, 0xA30000, 0xC003C, 0x20002, 1,
    0, 0, 0, -1, -1, -1,
};
const int targetItem1_800CB6C8[14] = {
    0x40010, 0, 0, 0, 0xB00000, 0xC003C, 0x20002, 1,
    0, 0, 0, -1, -1, -1,
};
const int targetItem2_800CB700[15] = {
    0x40010, 0, 0, 0, 0xBD0000, 0xC003C, 0x20002, 1,
    0, 0, 0, -1, -1, -1,
};

extern EventNode* dword_8008D614;
extern unsigned char byte_800A38D8;
extern unsigned char battleResult_800A38DC;
extern unsigned short padPressed_8009194C[];
extern void CmdMenuTask_800CD16C();
extern unsigned char byte_800A85BC;
extern short word_800A82D0;
extern short word_800A82D2;
extern // Magic list rows from the number of spells; adds the Change command when minion changing is allowed
void SetupCmdMenu_800CB88C();
extern // Change is greyed out (with a message) when the side has a single minion
void DisableChangeIfAlone_800CB924();

// Versus battle command menu of one side: starts the menu event that fills *cmd (COMBBTL's command)
EventEntry* CombComStart_800CB7AC(int cmd, int side)
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D614);
    if (e)
    {
        e->cb_8 = (EventEntryFn)CmdMenuTask_800CD16C;
        cmd_800CD840 = (CombComCmd*)cmd;
        side_800CD839 = side;
        e->flags = (e->flags | 1) & ~0x8000;
        if (!side)
        {
            padIndex_800CD848 = 0;
        }
        else
        {
            padIndex_800CD848 = byte_800A38D8;
        }
        battleResult_800A38DC = 0;
        menuState_800CD83A = 0;
        prevState_800CD850 = 0;
        msgShown_800CD838 = 0;
        targetFlags_800CD844 = 4;
        byte_800CD845 = 0;
        SetupCmdMenu_800CB88C();
        DisableChangeIfAlone_800CB924();
    }
    return e;
}

void SetupCmdMenu_800CB88C()
{
    if (CountMagicBits_8001AE54(GetSlotMagicBits_800A11BC(side_800CD839)) >= 5)
    {
        magicCursorCount_800CD2A8 = CountMagicBits_8001AE54(GetSlotMagicBits_800A11BC(side_800CD839));
    }
    if (dword_800A3A88 & 2)
    {
        cmdCursor_800CD28C[1] = 3;
        cmdCursor_800CD28C[2] = 5;
        cmdItemSlot4_800CD414 = &cmdItemChange_800CD3CC;
    }
}

void DisableChangeIfAlone_800CB924()
{
    if (CountTeamMinions_800A1AAC(side_800CD839) == 1)
    {
        cmdInfoChangeError_800CD490 = errNoDivineMinions_800CD468;
        cmdItemChange_800CD3CC.flags |= 2;
    }
}


// The menu cursor of a menu state (state 3: target or, for Change, the minion to send in)
short* GetStateCursor_800CB974(int state)
{
    state &= 0xFF;
    if (state == 3)
    {
        if ((targetFlags_800CD844 & 1) == 0)
        {
            if ((targetFlags_800CD844 & 4) == 0)
            {
                if ((short)GetMenuCursorIndex_8003DA54(cmdCursor_800CD28C) == 4)
                {
                    changeCursor_800CD2BC[2] = CountTeamMinions_800A1AAC(side_800CD839) - 1;
                    return changeCursor_800CD2BC;
                }
            }
        }
        return targetCursor_800CD2B0;
    }
    return stateCursors_800CD2D4[state];
}


void UpdateCmdMenuWin_800CBA20(int state)
{
    int i;
    int off;
    state &= 0xFF;
    if (state == 0)
    {
        cmdMenuWin_800CD41C[0] = 2;
    }
    else
    {
        cmdMenuWin_800CD41C[0] = 4;
    }
    cmdMenuWin_800CD41C[1] = GetTime30Hz_8002C64C();
    if (cmdMenuWin_800CD41C[2] < 8)
    {
        cmdMenuWin_800CD41C[2]++;
    }
    off = side_800CD839;
    cmdMenuWin_800CD41C[3] = cmdCursorSel_800CD294;
    for (i = 0; i < 5; i++)
    {
        cmdItems_800CD404[i]->x_10 = cmdItemX_800CD434[i] + off * 192;
    }
}

// Unit the battle camera / marker focuses on: the side's active minion, or the chosen target
void SetFocusedMinion_800CBAD4(int state)
{
    if ((state & 0xFF) != 3)
    {
        actorSlot_800A85BD = dword_800A4078[side_800CD839 * 4];
    }
    else if (targetFlags_800CD844 & 5)
    {
        actorSlot_800A85BD = dword_800A4078[side_800CD839 * 4];
    }
    else
    {
        actorSlot_800A85BD = targetSlotLo_800CD83C;
    }
}

extern int MeasureTextWidth_8003E4C8(int);

// One line message in a box beside the side's command menu
void DrawCmdMessage_800CBB4C(int text)
{
    RECT a;
    short b[2];
    int d;
    int w;
    a.w = w = MeasureTextWidth_8003E4C8(text) + 4;
    a.h = 0x12;
    if (side_800CD839 == 1)
    {
        a.x = 0xDD - w;
    }
    else
    {
        a.x = 0x5F;
    }
    a.y = 0xC1;
    b[1] = 0xC3;
    b[0] = a.x + 2;
    d = text;
    DrawTextBox_8002AFA0((int)&d, (int)b, 0xF, &a, 1);
}

void DrawLargeMessage_800CBBE0(int text)
{
    short v[2] = {0xA, 0x14};
    CombComDlg d;
    d.line0_0 = text;
    d.line1_4 = 0;
    d.line2_8 = 0;
    d.line3_C = 0;
    DrawLargeTextBox_8002AF10((int)&d, (int)v, 0xF);
}

int GetSelectedSkill_800CBC28()
{
    return MenuIndexToSkillSlot_80031BDC((short)GetMenuCursorIndex_8003DA54(skillCursor_800CD298));
}

int GetSelectedMagic_800CBC58()
{
    int r = GetSlotMagicBits_800A11BC(side_800CD839);
    return FindNthMagicBit_8001AEC0(r, (short)GetMenuCursorIndex_8003DA54(magicCursor_800CD2A4));
}

typedef struct CombComColor
{
    unsigned short color;
    unsigned char a;
    unsigned char b;
} CombComColor;
extern unsigned short uiColor_8008B590;
extern void* memset(void* p, int c, unsigned int n);
extern void DrawMenuItemWithWindow_8002ADB4(void* a, void* b, int c, int d);
extern void DrawMenuWindows_8002A5A4(void* p);
void DrawPauseMenu_800CBCA0()
{
    CombComColor col;
    CombComItem a;
    CombComItem b;
    CombComItem c;
    CombComItem d;
    void* list[4];
    CombComMenu m;
    a = pauseTitleItem_800CB4F0;
    b = pauseItemStart_800CB528;
    c = pauseItemGiveUp_800CB560;
    d = pauseItemReturn_800CB598;
    memset(list, 0, 0x10);
    m = menuWinTmpl_800CB5D0;
    list[0] = &b;
    list[1] = &c;
    list[2] = &d;
    col.color = uiColor_8008B590;
    col.a = 0;
    col.b = 1;
    DrawMenuItemWithWindow_8002ADB4(&a, &col, 0, GetTime30Hz_8002C64C());
    m.time_4 = GetTime30Hz_8002C64C();
    m.items_10 = list;
    m.sel_C = pauseCursorSel_800CD2D0;
    DrawMenuWindows_8002A5A4(&m);
}

extern unsigned char exchangeFlags_800A84A8;
extern int DrawAbilityDescription_8002C670();
extern void DrawAbilityList_8002CE28(struct_minion_ref* a0, void* a1);
extern void DrawMagicList_8002CAC8(struct_minion_ref* a0, void* a1);
extern int GetSkillMpCost_80031A04(void* skills, int a);
extern void DrawButtonHelpBar_8002B004(void* p, int a, int b);
extern void PreviewCmdEffect_800CC40C();
// Matched
// Draws the menus of the current state, the circle-held descriptions and the HP/MP preview
void DrawCmdMenu_800CBEA4()
{
    short w[2];
    int shown;
    int k;
    int f;
    shown = 0;
    word_800A82D0 = 0;
    word_800A82D2 = 0;
    if (IsCircleHeld_8003D45C(padIndex_800CD848))
    {
        if (menuState_800CD83A == 0)
        {
            DrawCmdMessage_800CBB4C(*cmdInfo_800CD46C[(short)GetMenuCursorIndex_8003DA54(cmdCursor_800CD28C)].desc_0);
            shown = 1;
        }
        else if (menuState_800CD83A == 1)
        {
            short p[2];
            Minion* m;
            shown = 1;
            m = GetSlotMinion_800A11D8(side_800CD839);
            p[0] = 10;
            p[1] = 0x14;
            DrawAbilityDescription_8002C670(m, p, skillDescs_800CD718, (short)GetMenuCursorIndex_8003DA54(skillCursor_800CD298), 0xF);
        }
        else if (menuState_800CD83A == 2)
        {
            if (GetSelectedMagic_800CBC58() < 0x1E)
            {
                short p[2];
                p[0] = 10;
                p[1] = 0x14;
                DrawLargeTextBox_8002AF10((int)&magicDescs_800CD538[GetSelectedMagic_800CBC58()], (int)p, 0xF);
                shown = 1;
            }
        }
        else if (menuState_800CD83A == 5)
        {
            CombComMsgs3 t;
            t = pauseOptionDescs_800CB674;
            DrawCmdMessage_800CBB4C(t.m[(short)GetMenuCursorIndex_8003DA54(pauseCursor_800CD2C8)]);
            shown = 1;
        }
    }
    if (shown)
    {
        k = 1;
    }
    else
    {
        k = msgShown_800CD838;
    }
    w[0] = cmd_800CD840->arg_4;
    w[1] = side_800CD839;
    if (!(stateDrawFlags_800CD820[menuState_800CD83A][k] & 0x10))
    {
        if (targetFlags_800CD844 & 1)
        {
            f = -1;
        }
        else
        {
            f = (short)GetMenuCursorIndex_8003DA54(activeCursor_800CD854);
        }
        if ((short)GetMenuCursorIndex_8003DA54(cmdCursor_800CD28C) == 3)
        {
            if (targetFlags_800CD844 & 2)
            {
                targetSlot_800CD83C = DrawTargetList_800CC674(w, 1, f, 0xF);
            }
            PreviewCmdEffect_800CC40C();
        }
        else if ((short)GetMenuCursorIndex_8003DA54(cmdCursor_800CD28C) == 6)
        {
            PreviewCmdEffect_800CC40C();
        }
        else if ((short)GetMenuCursorIndex_8003DA54(cmdCursor_800CD28C) == 4)
        {
            targetSlot_800CD83C = DrawTargetList_800CC674(w, 3, f, 0xF);
        }
    }
    if (stateDrawFlags_800CD820[menuState_800CD83A][k] & 1)
    {
        exchangeFlags_800A84A8 |= 0xC;
    }
    else
    {
        exchangeFlags_800A84A8 &= 0xF3;
    }
    if (!(stateDrawFlags_800CD820[menuState_800CD83A][k] & 4))
    {
        DrawMenuWindows_8002A5A4(cmdMenuWin_800CD41C);
    }
    if (!(stateDrawFlags_800CD820[menuState_800CD83A][k] & 0x40))
    {
        struct_minion_ref r;
        CombComPos2 p;
        p = skillListPos_800CB680;
        r.field_4 = 2;
        r.ot_6 = 0xF;
        r.field_8 = -1;
        r.cursor_0 = skillCursor_800CD298[4];
        r.scroll_2 = skillCursor_800CD298[5];
        r.minion_C = GetSlotMinion_800A11D8(side_800CD839);
        r.field_A = 0;
        DrawAbilityList_8002CE28(&r, p.xy[side_800CD839]);
        word_800A82D2 = -GetSkillMpCost_80031A04(&r.minion_C->skills_DE, MenuIndexToSkillSlot_80031BDC((short)GetMenuCursorIndex_8003DA54(skillCursor_800CD298)));
    }
    if (!(stateDrawFlags_800CD820[menuState_800CD83A][k] & 0x80))
    {
        struct_minion_ref r;
        CombComPos2 p;
        p = magicListPos_800CB688;
        r.field_4 = 2;
        r.ot_6 = 0xF;
        r.field_8 = -1;
        r.cursor_0 = magicCursor_800CD2A4[4];
        r.scroll_2 = magicCursor_800CD2A4[5];
        r.minion_C = GetSlotMinion_800A11D8(side_800CD839);
        r.field_A = 0;
        DrawMagicList_8002CAC8(&r, p.xy[side_800CD839]);
        word_800A82D2 = -GetMagicMpCost_8001AC58(FindNthMagicBit_8001AEC0((int)&r.minion_C->magicBits_F4, (short)GetMenuCursorIndex_8003DA54(magicCursor_800CD2A4)));
    }
    if (menuState_800CD83A == 5)
    {
        DrawPauseMenu_800CBCA0();
    }
    DrawButtonHelpBar_8002B004(stateHelpBars_800CD50C[menuState_800CD83A], 0, 0xF);
}

#if 0
// Not matched: scheduling of the three word_800A82D0/2 -= pairs (the original reloads the globals before the third pair) and the 1 constant hoist; masks need separate statements to keep sllv+and

extern int ResolveBattleAction_80012BB0(void* a, void* b, void* c, int* d);
extern int sub_80013228(void* a, void* b, void* c, int* d);
extern int CheckMagicUsable_80034068(short* p);
void PreviewCmdEffect_800CC40C()
{
    short arg[4];
    int out[10];
    unsigned int i;
    UnitStatus* src;
    UnitStatus* t;
    if (menuState_800CD83A == 3)
    {
        word_800A82D0 = 0;
        word_800A82D2 = 0;
        src = GetUnitStatus_80014390((unsigned char)(side_800CD839 + 8));
        for (i = 0; i < 2; i++)
        {
            int bit = 1 << (i + 8);
            if (cmd_800CD840->targets_C & bit)
            {
                t = GetUnitStatus_80014390((unsigned char)(i + 8));
                ResolveBattleAction_80012BB0(src, t, cmd_800CD840, out);
                if (!sub_80013228(src, t, cmd_800CD840, out))
                {
                    bit = 1 << i;
                    if (cmd_800CD840->mask_8 & bit)
                    {
                    word_800A82D0 -= out[3];
                    word_800A82D2 -= out[4];
                    word_800A82D0 -= out[5];
                    word_800A82D2 -= out[6];
                    word_800A82D0 -= out[7];
                    word_800A82D2 -= out[8];
                    if (t->hp_8.max_2 - t->hp_8.cur_0 < word_800A82D0)
                    {
                        word_800A82D0 = t->hp_8.max_2 - t->hp_8.cur_0;
                    }
                    if (t->mp_C.max_2 - t->mp_C.cur_0 < word_800A82D2)
                    {
                        word_800A82D2 = t->mp_C.max_2 - t->mp_C.cur_0;

                    }
                    }
                }
            }
        }
        arg[0] = cmd_800CD840->arg_4;
        arg[1] = side_800CD839 + 8;
        arg[2] = targetSlot_800CD83C;
        arg[3] = 0;
        if ((short)GetMenuCursorIndex_8003DA54(cmdCursor_800CD28C) == 6)
        {
            ((int (*)(short*))CheckUsableStub_80034124)(arg);
        }
        else if ((short)GetMenuCursorIndex_8003DA54(cmdCursor_800CD28C) == 7 && CheckMagicUsable_80034068(arg))
        {
            word_800A82D0 = 0;
        }
    }
}
#endif
// HP/MP change preview of the chosen action on the target (word_800A82D0 / word_800A82D2)
INCLUDE_OVERLAY_ASM(combcom, PreviewCmdEffect_800CC40C);

#if 0
// Not matched: register allocation only (44 words): the original gives the list pointer s1 and mode/k s3, f/i s2
extern CombComItem targetItem0_800CB690;
extern CombComItem targetItem1_800CB6C8;
extern CombComItem targetItem2_800CB700;
extern Minion teams_800A3AA0[][3];
extern int IsMinionSlotEmpty_800A1934(Minion* p);
extern int sub_800A1958(Minion* p);
extern int CheckMagicUsable_80034068(short* p);
int DrawTargetList_800CC674(short* arg, int mode, int sel, int f)
{
    CombComItem w[3];
    CombComItem* list[4];
    CombComItem* items[3];
    CombComMenu m;
    short q[2];
    int res;
    int i;
    int k;
    short x;
    Minion* u;
    CombComItem* p0;
    CombComItem* it;
    CombComItem** pk;
    CombComItem** pi;
    w[0] = targetItem0_800CB690;
    w[1] = targetItem1_800CB6C8;
    w[2] = targetItem2_800CB700;
    pk = list;
    memset(pk, 0, 0x10);
    memset(items, 0, 0xC);
    p0 = &w[0];
    m = menuWinTmpl_800CB5D0;
    items[1] = &w[1];
    items[0] = p0;
    items[2] = &w[2];
    m.ot_14 = f;
    x = side_800CD839 * 62 + 100;
    w[0].x_10 = x;
    w[1].x_10 = x;
    w[2].x_10 = x;
    m.time_4 = GetTime30Hz_8002C64C();
    m.sel_C = sel;
    m.items_10 = pk;
    q[0] = arg[0];
    res = 0;
    if (mode == 1)
    {
        {
            UnitStatus* s = GetUnitStatus_80014390((unsigned char)(((unsigned char*)arg)[2] + 8));
            list[0] = p0;
            p0->text_4 = s->name_10;
        }
        q[1] = arg[1] + 8;
        if (CheckMagicUsable_80034068(q) == 0)
        {
            list[0]->flags &= ~2;
        }
        else
        {
            list[0]->flags |= 2;
        }
        res = ((int*)dword_800A4078)[arg[1]];
    }
    else
    {
        pi = pk;
        for (k = i = 0; i < 3; i++)
        {
            u = &teams_800A3AA0[arg[1]][i];
            if (i != ((int*)dword_800A4078)[side_800CD839] && IsMinionSlotEmpty_800A1934(u) == 0)
            {
                it = items[k];
                *pk = it;
                it->text_4 = u->status_84.name_10;
                if (sub_800A1958(u))
                {
                    (*pk)->flags |= 2;
                }
                else
                {
                    (*pk)->flags &= ~2;
                }
                if (sel == k)
                {
                    res = i;
                }
                pk++;
                k++;
            }
            else
            {
                *pi = 0;
            }
            pi++;
        }
    }
    DrawMenuWindows_8002A5A4(&m);
    return res;
}
#endif
// Target window: mode 1 a single unit (magic on a side), else the side's other minions (for Change); returns the slot
INCLUDE_OVERLAY_ASM(combcom, DrawTargetList_800CC674);

// Stores the chosen target; Defend marks the unit defending, Change has no target unit
void FinishCmd_800CC9FC()
{
    byte_800A85BC = targetSlot_800CD83C;
    if (cmd_800CD840->kind_0 == 0x12)
    {
        cmd_800CD840->targets_C = 0;
        GetUnitStatus_80014390((unsigned char)(side_800CD839 + 8))->status_0 |= 0x8000;
    }
    else
    {
        if (cmd_800CD840->kind_0 == 1 && side_800CD839 != targetSlot_800CD83C)
        {
            return;
        }
        if (cmd_800CD840->kind_0 == 8)
        {
            cmd_800CD840->targets_C = 0;
        }
    }
}


extern Minion teams_800A3AA0[][3];
extern int sub_800A1958(Minion* p);
extern int CheckSkillUsable_80033C98(struct_minion_ref* p);
extern int CheckMagicCastable_80033C08(struct_minion_ref* p);
// 1 when the highlighted entry can be chosen, else 0 with errorMsg_800CD84C set to the reason (or 0)
int CheckCmdSelectable_800CCA94()
{
    struct_minion_ref a;
    short b[4];
    int idx = GetMenuCursorIndex_8003DA54(activeCursor_800CD854);
    int* p;
    a.cursor_0 = activeCursor_800CD854[4];
    errorMsg_800CD84C = 0;
    a.scroll_2 = activeCursor_800CD854[5];
    a.field_A = 0;
    b[3] = 0;
    b[0] = cmd_800CD840->arg_4;
    b[1] = side_800CD839 + 8;
    b[2] = targetSlot_800CD83C;
    switch (menuState_800CD83A)
    {
    case 0:
        p = cmdInfo_800CD46C[(short)idx].error_4;
        if (p == 0)
        {
            return 1;
        }
        errorMsg_800CD84C = *p;
        return 0;
    case 1:
        a.minion_C = GetSlotMinion_800A11D8(side_800CD839);
        switch (CheckSkillUsable_80033C98(&a))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 6:
            return 1;
        case 5:
            errorMsg_800CD84C = errNotEnoughMana_800CD458;
            return 0;
        case 7:
            return 0;
        }
        break;
    case 2:
        a.minion_C = GetSlotMinion_800A11D8(side_800CD839);
        switch (CheckMagicCastable_80033C08(&a))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 7:
            return 1;
        case 5:
            errorMsg_800CD84C = errNotEnoughMana_800CD458;
            return 0;
        case 6:
            return 0;
        }
        break;
    case 3:
        if ((short)GetMenuCursorIndex_8003DA54(cmdCursor_800CD28C) == 2)
        {
            switch ((unsigned int)((int (*)(short*))CheckUsableStub_80034124)(b))
            {
            case 0:
                return 1;
            case 3:
                errorMsg_800CD84C = errNoNeedToUse_800CD460;
                return 0;
            case 4:
                errorMsg_800CD84C = errCannotSummon_800CD454;
                return 0;
            }
            return 0;
        }
        else if ((short)GetMenuCursorIndex_8003DA54(cmdCursor_800CD28C) == 3)
        {
            switch ((unsigned int)CheckMagicUsable_80034068(b))
            {
            case 0:
                return 1;
            case 3:
                errorMsg_800CD84C = errNoNeedToUse_800CD460;
                return 0;
            case 4:
                errorMsg_800CD84C = errCannotSummon_800CD454;
                return 0;
            }
            return 0;
        }
        else if ((short)GetMenuCursorIndex_8003DA54(cmdCursor_800CD28C) == 4)
        {
            if (sub_800A1958(&teams_800A3AA0[side_800CD839][targetSlot_800CD83C]))
            {
                errorMsg_800CD84C = errCannotSummon_800CD454;
                return 0;
            }
        }
        break;
    case 4:
    case 5:
        return 1;
    }
    return 1;
}

// Target unit bit: the side's own unit, or the opponent's for target flag 4
int GetDefaultTargets_800CCD84()
{
    if ((targetFlags_800CD844 & 4) == 0)
    {
        return 1 << (side_800CD839 + 8);
    }
    return 1 << ((side_800CD839 ^ 1) + 8);
}

extern int GetSlotSkills_800A11A0(int);
extern int sub_80031B0C(int, int);
extern int GetMagicTargetFlags_8001ACE4(int);
// Confirm: takes the highlighted entry and moves to the next menu state
void AdvanceCmdMenu_800CCDD0()
{
    int v;
    prevState_800CD850 = menuState_800CD83A;
    switch (menuState_800CD83A)
    {
    case 0:
        targetFlags_800CD844 = cmdTargetFlags_800CD494[(short)GetMenuCursorIndex_8003DA54(cmdCursor_800CD28C)];
        menuState_800CD83A = cmdNextState_800CD49C[(short)GetMenuCursorIndex_8003DA54(cmdCursor_800CD28C)];
        cmd_800CD840->kind_0 = cmdKinds_800CD524[(short)GetMenuCursorIndex_8003DA54(cmdCursor_800CD28C)];
        break;
    case 1:
        v = GetSlotSkills_800A11A0(side_800CD839);
        targetFlags_800CD844 = sub_80031B0C(v, GetSelectedSkill_800CBC28());
        menuState_800CD83A = 4;
        cmd_800CD840->arg_4 = GetSelectedSkill_800CBC28();
        break;
    case 2:
        targetFlags_800CD844 = GetMagicTargetFlags_8001ACE4(GetSelectedMagic_800CBC58());
        if (targetFlags_800CD844 & 2)
        {
            menuState_800CD83A = 3;
        }
        else
        {
            menuState_800CD83A = 4;
        }
        cmd_800CD840->arg_4 = GetSelectedMagic_800CBC58();
        break;
    case 3:
        menuState_800CD83A = 4;
        break;
    case 5:
        switch ((short)GetMenuCursorIndex_8003DA54(pauseCursor_800CD2C8))
        {
        case 0:
            prevState_800CD850 = 0;
            menuState_800CD83A = 0;
            break;
        case 1:
            battleResult_800A38DC = 1;
            break;
        case 2:
            battleResult_800A38DC = 2;
            break;
        }
        break;
    }
    cmd_800CD840->targets_C = GetDefaultTargets_800CCD84();
}

extern int CheckCmdSelectable_800CCA94();
extern void AdvanceCmdMenu_800CCDD0();
void CmdMenuInput_800CCFCC(EventEntry* e)
{
    if (IsConfirmPressed_8003D288(0, padIndex_800CD848))
    {
        if (CheckCmdSelectable_800CCA94())
        {
            PlaySfx_80031494(0x7E);
            AdvanceCmdMenu_800CCDD0();
            if (battleResult_800A38DC)
            {
                e->flags = (e->flags & ~1) | 0x8000;
            }
        }
        else
        {
            PlaySfx_80031494(0x7C);
            if (errorMsg_800CD84C)
            {
                msgTimer_800CD83B = 0x96;
                msgShown_800CD838 = 1;
            }
        }
    }
    else if (IsCancelPressed_8003D3C0(0, padIndex_800CD848))
    {
        if (menuState_800CD83A)
        {
            PlaySfx_80031494(0x7D);
            menuState_800CD83A = prevState_800CD850;
            prevState_800CD850 = 0;
        }
    }
}

// Shows the 'cannot choose' message until it times out or a button is pressed
void CmdMenuMessage_800CD0C8()
{
    if (padPressed_8009194C[padIndex_800CD848])
    {
        msgTimer_800CD83B = 0;
    }
    if (msgTimer_800CD83B == 0)
    {
        msgShown_800CD838 = 0;
    }
    else
    {
        msgTimer_800CD83B--;
    }
    if (errorMsg_800CD84C)
    {
        if (menuState_800CD83A == 0)
        {
            DrawCmdMessage_800CBB4C(errorMsg_800CD84C);
        }
        else
        {
            DrawLargeMessage_800CBBE0(errorMsg_800CD84C);
        }
    }
}

extern unsigned char exchangeFlags_800A84A8;
extern int UpdateMenuCursor_8003D794(void* p, int a1);
extern void DrawCmdMenu_800CBEA4();
// The menu event: state 4 = command complete, Start opens the pause menu (state 5)
void CmdMenuTask_800CD16C(EventEntry* e, void* buf)
{
    short* m = GetStateCursor_800CB974(menuState_800CD83A);
    activeCursor_800CD854 = m;
    UpdateMenuCursor_8003D794(m, padIndex_800CD848);
    if (padPressed_8009194C[padIndex_800CD848] & 0x800)
    {
        menuState_800CD83A = 5;
    }
    UpdateCmdMenuWin_800CBA20(menuState_800CD83A);
    DrawCmdMenu_800CBEA4();
    SetFocusedMinion_800CBAD4(menuState_800CD83A);
    inputHandlers_800CD818[msgShown_800CD838](e, buf);
    if (menuState_800CD83A == 4)
    {
        exchangeFlags_800A84A8 &= 0xF3;
        FinishCmd_800CC9FC();
        word_800A82D0 = 0;
        word_800A82D2 = 0;
        e->flags = (e->flags & ~1) | 0x8000;
    }
}

short cmdCursor_800CD28C[4] = { 2, 2, 4 };
short cmdCursorSel_800CD294 = 0;
short skillCursor_800CD298[6] = { 1, 5, 5 };
short magicCursor_800CD2A4[2] = { 1, 4 };
short magicCursorCount_800CD2A8 = 4;
short magicCursorFlags_800CD2AA = 64;
short magicCursorSel_800CD2AC = 0;
short magicCursorScroll_800CD2AE = 0;
short targetCursor_800CD2B0[6] = { 1, 1, 1 };
short changeCursor_800CD2BC[6] = { 1, 3, 1 };
char pauseCursor_800CD2C8[8] = { 1, 0, 3, 0, 3 };
short pauseCursorSel_800CD2D0 = 0;
short *stateCursors_800CD2D4[6] = { cmdCursor_800CD28C, skillCursor_800CD298, magicCursor_800CD2A4, targetCursor_800CD2B0, cmdCursor_800CD28C, (void *)pauseCursor_800CD2C8 };
CombComItem cmdItemAttack_800CD2EC[1] = { {
        8,
        1,
        (void *)13,
        (int)&uiTiySprts_8008D620,
        (int)&uiTiyTPages_8008D3F4,
        32,
        157,
        {
            0x120020, 0x20002, 1, 0, 0, 0, -1, -1,
            -1,
        },
    } };
CombComItem cmdItemDefend_800CD324[1] = { {
        8,
        1,
        (void *)48,
        (int)&uiTiySprts_8008D620,
        (int)&uiTiyTPages_8008D3F4,
        64,
        157,
        {
            0x120020, 0x20002, 1, 0, 0, 0, -1, -1,
            -1,
        },
    } };
CombComItem cmdItemSpecial_800CD35C[1] = { {
        8,
        1,
        (void *)183,
        (int)&uiTiySprts_8008D620,
        (int)&uiTiyTPages_8008D3F4,
        32,
        176,
        {
            0x120020, 0x20002, 1, 0, 0, 0, -1, -1,
            -1,
        },
    } };
CombComItem cmdItemMagic_800CD394[1] = { {
        8,
        1,
        (void *)108,
        (int)&uiTiySprts_8008D620,
        (int)&uiTiyTPages_8008D3F4,
        64,
        176,
        {
            0x120020, 0x20002, 1, 0, 0, 0, -1, -1,
            -1,
        },
    } };
CombComItem cmdItemChange_800CD3CC = {
    8,
    1,
    (void *)40,
    (int)&uiTiySprts_8008D620,
    (int)&uiTiyTPages_8008D3F4,
    32,
    195,
    {
        0x120040, 0x20002, 1, 0, 0, 0, -1, -1,
        -1,
    },
};
CombComItem *cmdItems_800CD404[4] = { cmdItemAttack_800CD2EC, cmdItemDefend_800CD324, cmdItemSpecial_800CD35C, cmdItemMagic_800CD394 };
void *cmdItemSlot4_800CD414 = 0;
int cmdItemsEnd_800CD418 = 0;
unsigned int cmdMenuWin_800CD41C[6] = { 2, 0, 0, 0, (unsigned int)cmdItems_800CD404 };
short cmdItemX_800CD434[6] = { 32, 64, 32, 64, 32 };
const char *descAttack_800CD440[1] = { aUseNormalAttack_800C9E8C };
const char *descDefend_800CD444[1] = { aDefendToReduceD_800C9EB0 };
const char *descSpecial_800CD448[1] = { aUseSpecialAttac_800C9EE0 };
const char *descMagic_800CD44C[1] = { aUseMagicSpell_800C9F08 };
const char *descChange_800CD450[1] = { aChangeCurrentFi_800C9F28 };
int errCannotSummon_800CD454 = (int)aCannotSummonInt_800C9F58;
int errNotEnoughMana_800CD458 = (int)aNotEnoughMana_800C9F8C;
void *errBlank_800CD45C[1] = { (void *)&aBlank_800C9FAC };
int errNoNeedToUse_800CD460 = (int)aNoNeedToUseItem_800C9FB0;
const char *errCannotSelect_800CD464[1] = { aCannotSelect_800C9FD8 };
char errNoDivineMinions_800CD468[4] = { 244, 159, 12, 128 };
CombComMsg cmdInfo_800CD46C[4] = {
    { (void *)descAttack_800CD440 },
    { (void *)descDefend_800CD444 },
    { (void *)descSpecial_800CD448 },
    { (void *)descMagic_800CD44C },
};
void *cmdInfoChangeDesc_800CD48C[1] = { (void *)descChange_800CD450 };
void *cmdInfoChangeError_800CD490 = 0;
unsigned char cmdTargetFlags_800CD494[8] = { 4, 0, 4, 4, 2 };
unsigned char cmdNextState_800CD49C[8] = { 4, 4, 1, 2, 3 };
int helpBarCmd_800CD4A4[8] = { 16, (int)aSelect_800CA05C, 110, (int)aDescription_800CA044, 186, (int)aPause_800CA038, -1 };
int helpBarList_800CD4C4[10] = {
    16, (int)aSelect_800CA05C, 167, (int)aQuit_800CA06C, 110, (int)aDescription_800CA044, 186, (int)aPause_800CA038,
    -1,
};
int helpBarTarget_800CD4EC[8] = { 16, (int)aSelect_800CA05C, 167, (int)aQuit_800CA06C, 186, (int)aPause_800CA038, -1 };
char *stateHelpBars_800CD50C[6] = { (void *)helpBarCmd_800CD4A4, (void *)helpBarList_800CD4C4, (void *)helpBarList_800CD4C4, (void *)helpBarTarget_800CD4EC, 0, (void *)((char *)&dword_8008267C + 52) };
int cmdKinds_800CD524[5] = { 0, 18, 6, 1, 8 };
CombComDlg magicDescs_800CD538[30] = {
    { (int)aFireAttackOneEn_800CAB34, (int)aExtraDamageVsAi_800CAB08, (int)aHigherFireEleme_800CAAAC },
    { (int)aFireAttackAllEn_800CAA78, (int)aExtraDamageVsAi_800CAB08, (int)aHigherFireEleme_800CAAAC },
    { (int)aAdvancedFireAtt_800CAA4C, (int)aExtraDamageVsAi_800CAB08, (int)aHigherFireEleme_800CAAAC },
    { (int)aWaterAttackOneE_800CAA18, (int)aExtraDamageVsFi_800CA9EC, (int)aHigherWaterElem_800CA98C },
    { (int)aWaterAttackAllE_800CA954, (int)aExtraDamageVsFi_800CA9EC, (int)aHigherWaterElem_800CA98C },
    { (int)aAdvancedWaterAt_800CA928, (int)aExtraDamageVsFi_800CA9EC, (int)aHigherWaterElem_800CA98C },
    { (int)aEarthAttackOneE_800CA8F4, (int)aExtraDamageVsWa_800CA8C4, (int)aHigherEarthElem_800CA864 },
    { (int)aEarthAttackAllE_800CA82C, (int)aExtraDamageVsWa_800CA8C4, (int)aHigherEarthElem_800CA864 },
    { (int)aAdvancedEarthAt_800CA800, (int)aExtraDamageVsWa_800CA8C4, (int)aHigherEarthElem_800CA864 },
    { (int)aWindAttackOneEn_800CA7D0, (int)aExtraDamageVsEa_800CA7A0, (int)aHigherWindEleme_800CA744 },
    { (int)aWindAttackAllEn_800CA710, (int)aExtraDamageVsEa_800CA7A0, (int)aHigherWindEleme_800CA744 },
    { (int)aAdvancedWindAtt_800CA6E4, (int)aExtraDamageVsEa_800CA7A0, (int)aHigherWindEleme_800CA744 },
    { (int)aCurePoison_800CA6CC, (int)aCuresPoison_800CA6B0 },
    { (int)aRestoreHP_800CA698, (int)aRestoresSomeHP_800CA674 },
    { (int)aRestoreAllHP_800CA654, (int)aRestoresAllHP_800CA630 },
    { (int)aReturnToNormal_800CA60C, (int)aCuresPoisonAndT_800CA5B4 },
    { (int)aProtection_800CA59C, (int)aProtectsAgainst_800CA534, (int)aEndsOnceItProte_800CA4E0 },
    { (int)aPoison_800CA4D0, (int)aPoisonsAnEnemy_800CA4AC },
    { (int)aSleep_800CA4A0, (int)aPutsAnEnemyToSl_800CA470 },
    { (int)aFleshToStone_800CA450, (int)aTurnsAnEnemyInt_800CA418 },
    { (int)aDeath_800CA40C, (int)aCausesAnEnemyTo_800CA3B8 },
    { (int)aEnhanceFire_800CA39C, (int)aIncreasesFireAt_800CA348, (int)aEffectivenessOf_800CA2EC },
    { (int)aEnhanceWater_800CA2D0, (int)aIncreasesWaterA_800CA278, (int)aEffectivenessOf_800CA21C },
    { (int)aEnhanceEarth_800CA200, (int)aIncreasesEarthA_800CA1A8, (int)aEffectivenessOf_800CA148 },
    { (int)aEnhanceWind_800CA12C, (int)aIncreasesWindAt_800CA0D8, (int)aEffectivenessOf_800CA078 },
};
char skillDescs_800CD718[256] = { 172, 159, 12, 128, 172, 159, 12, 128, 172, 159, 12, 128, 0, 0, 0, 0, 172, 159, 12, 128, 172, 159, 12, 128, 172, 159, 12, 128, 0, 0, 0, 0, 196, 180, 12, 128, 108, 180, 12, 128, 100, 168, 12, 128, 0, 0, 0, 0, 64, 180, 12, 128, 232, 179, 12, 128, 140, 169, 12, 128, 0, 0, 0, 0, 192, 179, 12, 128, 104, 179, 12, 128, 172, 170, 12, 128, 0, 0, 0, 0, 64, 179, 12, 128, 232, 178, 12, 128, 68, 167, 12, 128, 0, 0, 0, 0, 188, 178, 12, 128, 104, 178, 12, 128, 0, 0, 0, 0, 0, 0, 0, 0, 60, 178, 12, 128, 212, 177, 12, 128, 0, 0, 0, 0, 0, 0, 0, 0, 152, 177, 12, 128, 44, 177, 12, 128, 0, 0, 0, 0, 0, 0, 0, 0, 240, 176, 12, 128, 136, 176, 12, 128, 56, 176, 12, 128, 0, 0, 0, 0, 0, 176, 12, 128, 180, 175, 12, 128, 100, 175, 12, 128, 0, 0, 0, 0, 40, 175, 12, 128, 224, 174, 12, 128, 152, 174, 12, 128, 0, 0, 0, 0, 92, 174, 12, 128, 32, 174, 12, 128, 212, 173, 12, 128, 0, 0, 0, 0, 152, 173, 12, 128, 76, 173, 12, 128, 244, 172, 12, 128, 0, 0, 0, 0, 188, 172, 12, 128, 92, 172, 12, 128, 248, 171, 12, 128, 0, 0, 0, 0, 188, 171, 12, 128, 100, 171, 12, 128, 248, 171, 12, 128 };
void (*inputHandlers_800CD818[2])(EventEntry *, void *) = { (void (*)(EventEntry *, void *))CmdMenuInput_800CCFCC, (void (*)(EventEntry *, void *))CmdMenuMessage_800CD0C8 };
unsigned short stateDrawFlags_800CD820[6][2] = {
    { 0x3D0, 0x2D2 },
    { 0x390, 0x193 },
    { 0x350, 0x153 },
    { 0x3C0, 0x3C3 },
    { 0 },
    { 0x3D6, 0x3D6 },
};
unsigned char msgShown_800CD838 = 0;
unsigned char side_800CD839 = 0;
unsigned char menuState_800CD83A = 0;
unsigned char msgTimer_800CD83B = 0;
int targetSlot_800CD83C = 0;
CombComCmd *cmd_800CD840 = 0;
unsigned char targetFlags_800CD844 = 0;
unsigned char byte_800CD845 = 0;
int padIndex_800CD848 = 0;
int errorMsg_800CD84C = 0;
unsigned char prevState_800CD850 = 0;
short *activeCursor_800CD854 = 0;
