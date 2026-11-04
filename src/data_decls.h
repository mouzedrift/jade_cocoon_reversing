#ifndef DATA_DECLS_H
#define DATA_DECLS_H

/* declarations of game data that is defined in the TU files */

extern char heapStart_800CD858[2*1024];
extern unsigned char pads_800918E8[2][9];
extern char SEQDataAttributeTable_80091D60[SS_SEQ_TABSIZ * 5 * 16];
extern char* data001Path_80086570;
extern Data001File Data001Files_80075AA0[1108];
extern SoundInfo soundFiles_80082F0C[155];
extern enum GameStates currentGameState_8008D4B4;

extern const char aAssertionFaile[];
extern const char aAssertionFaile_0[];
extern const char aAssertionFaile_1[];
extern const char aCdC[];
extern const char aMainC[];
extern const char aSoundC[];
extern const char name[];

extern const char aAssertionFaile_3[];
extern const char aEffectC[];
extern unsigned char rankLevelThresholds_8007C2E4[];
extern short sinTable_80084540[]; // sine table (0x1000 = 1.0), inside asc_80084350
extern const struct_u8x4 orangeGlowColor_80072270;
extern int statusTintLevel1_8007A0A4[];
extern int statusTintLevel2_8007A0B0[];
extern int statusTintLevel3_8007A0BC[];
extern int statusTintLevel4_8007A0C8[];
extern int statusTintLevel5_8007A0D4[];
extern int statusTintLevel6_8007A0E0[];
extern int statusTintLevel7_8007A0EC[];
extern int statusTintPoison_8007A0F8[];
extern int statusTintPoisonLevel1_8007A104[];
extern int statusTintPoisonLevel2_8007A110[];
extern int statusTintPoisonLevel3_8007A11C[];
extern int statusTintPoisonLevel4_8007A128[];
extern int statusTintPoisonLevel5_8007A134[];
extern int statusTintPoisonLevel6_8007A140[];
extern int statusTintPoisonLevel7_8007A14C[];
extern const struct_int3 boneGroupMasks_8007303C; // three bit masks (0x8007303C..0x80073047)

#endif
