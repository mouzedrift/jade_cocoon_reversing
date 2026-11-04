// CONFIG.BIN: declarations shared by its source files
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"

typedef struct { char b[8]; } Bytes8Config;

typedef struct CfgDlgConfig
{
    int f0, f4, f8, fC, f10, f14;
} CfgDlgConfig;

extern int dword_800C29D0;
extern const char aVibrationSettin_800C29D4[];
extern const char aSetScreenColor_800C29FC[];
extern const char aChangeSubtitleS_800C2A20[];
extern const char aChangeAudioSett_800C2A54[];
extern const char aSetOutputFormat_800C2A84[];
extern const char aSetAudioEffects_800C2AAC[];
extern const char aSetMusicVolume_800C2AE0[];
extern const char aSetCaptureSpeci_800C2B04[];
extern const char aSetMagicSpecial_800C2B40[];
extern const char aMessageWindowDi_800C2B78[];
extern const char aAutoMessage_800C2BA8[];
extern const char aSelectVoiceAudi_800C2BC4[];
extern const char aAllowAnimationS_800C2BFC[];
extern const char aSetDisplaySpeed_800C2C28[];
extern const char aExit_800C2C50[];
extern const char aSelect_800C2C5C[];
extern const CfgDlgConfig dword_800C2CD0;
extern const CfgDlgConfig dword_800C2CE8;
extern const int dword_800C2D00;
extern const char aOptionNotAvaila_800C2D40[];
extern const char aSetSpeechToONTo_800C2DA4[];
extern const char aOptionNotAvaila_800C2DF4[];
extern const char aSetSubtitlesToO_800C2E5C[];
extern int dword_800C4C80[4];
extern int dword_800C4C90[3];
extern int dword_800C4C9C[7];
extern int dword_800C4CB8[1];
extern int dword_800C4CBC[1];
extern int *dword_800C4CC0[5];
extern Bytes8Config dword_800C4CD4[5];
extern int dword_800C4CFC[14];
extern int dword_800C4D34[14];
extern int dword_800C4D6C[14];
extern int dword_800C4DA4[14];
extern char dword_800C4DDC[20];
extern int dword_800C4DF0[14];
extern int dword_800C4E28[14];
extern int dword_800C4E60[14];
extern char dword_800C4E98[16];
extern int dword_800C4EA8[14];
extern int dword_800C4EE0[14];
extern int dword_800C4F18[14];
extern int dword_800C4F50[14];
extern int dword_800C4F88[14];
extern int dword_800C4FC0[14];
extern int dword_800C4FF8[14];
extern int dword_800C5030[14];
extern int dword_800C5068[14];
extern int dword_800C50A0[14];
extern int dword_800C50D8[14];
extern int dword_800C5110[14];
extern int dword_800C5148[14];
extern int dword_800C5180[14];
extern int dword_800C51B8[14];
extern int dword_800C51F0[14];
extern int dword_800C5228[14];
extern int dword_800C5260[14];
extern char dword_800C5298[36];
extern char dword_800C52BC[36];
extern char dword_800C52E0[12];
extern unsigned short dword_800C52EC[28];
extern unsigned short dword_800C5324[28];
extern unsigned short dword_800C535C[28];
extern unsigned short dword_800C5394[28];
extern unsigned short dword_800C53CC[28];
extern unsigned short dword_800C5404[28];
extern unsigned short dword_800C543C[28];
extern unsigned short *dword_800C5474[8];
extern int dword_800C5494[14];
extern int dword_800C54CC[14];
extern int dword_800C5504[14];
extern int dword_800C553C[14];
extern char dword_800C5574[20];
extern int dword_800C5588[14];
extern int dword_800C55C0[14];
extern char dword_800C55F8[12];
extern int dword_800C5604[14];
extern int dword_800C563C[14];
extern char dword_800C5674[12];
extern int dword_800C5680[14];
extern int dword_800C56B8[14];
extern char dword_800C56F0[12];
extern int dword_800C56FC[14];
extern int dword_800C5734[14];
extern char dword_800C576C[12];
extern int dword_800C5778[14];
extern int dword_800C57B0[14];
extern char dword_800C57E8[12];
extern int dword_800C57F4[14];
extern int dword_800C582C[14];
extern char dword_800C5864[12];
extern int dword_800C5870[14];
extern char dword_800C58A8[8];
extern int dword_800C58B0[14];
extern int dword_800C58E8[14];
extern char dword_800C5920[12];
extern char dword_800C592C[24];
extern int dword_800C5944;

#endif
