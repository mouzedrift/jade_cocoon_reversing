#ifndef DATA_DECLS_H
#define DATA_DECLS_H

/* data that is still defined by the original asm (asm/d); see scripts/split.py */

extern char heapStart_800CD858[2*1024];
extern unsigned char pads_800918E8[2][9];
extern char SEQDataAttributeTable_80091D60[SS_SEQ_TABSIZ * 5 * 16];
extern char* off_80086570;
extern Data001File Data001Files_80075AA0[1108];
extern SoundInfo soundFiles_80082F0C[155];
extern enum GameStates currentGameState_8008D4B4;

extern char aAssertionFaile[];
extern char aAssertionFaile_0[];
extern char aAssertionFaile_1[];
extern char aCdC[];
extern char aMainC[];
extern char aSoundC[];
extern char name[];

extern char aAssertionFaile_3[];
extern char aEffectC[];
extern unsigned char dword_8007C2E4[];
extern short word_80084540[]; // sine table (0x1000 = 1.0), inside asc_80084350
extern int stru_8008D534[4];
extern struct_int3 dword_8007303C; // three bit masks (0x8007303C..0x80073047)

#endif
