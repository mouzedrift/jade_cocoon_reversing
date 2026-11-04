// CONFIG.BIN: declarations shared by its source files
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"

// the first 8 bytes of a menu cursor (CombSelCursor: cols, rows, count, flags)
typedef struct { char b[8]; } CfgCursorHead;

typedef struct CfgDlgConfig
{
    int mode_0, time_4, anim_8, cursor_C, items_10, ot_14; // a DrawMenuWindows_8002A5A4 menu
} CfgDlgConfig;

extern int configOverlayId_800C29D0;
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
extern const CfgDlgConfig menuHdrActive_800C2CD0;
extern const CfgDlgConfig menuHdrIdle_800C2CE8;
extern const int dword_800C2D00;
extern const char aOptionNotAvaila_800C2D40[];
extern const char aSetSpeechToONTo_800C2DA4[];
extern const char aOptionNotAvaila_800C2DF4[];
extern const char aSetSubtitlesToO_800C2E5C[];
extern int topMenuHelp_800C4C80[4];
extern int audioPageHelp_800C4C90[3];
extern int subtitlePageHelp_800C4C9C[7];
extern int screenColorPageHelp_800C4CB8[1];
extern int vibrationPageHelp_800C4CBC[1];
extern int *pageHelpTexts_800C4CC0[5];
extern CfgCursorHead pageCursors_800C4CD4[5];
extern int topItemAudio_800C4CFC[14];
extern int topItemSubtitle_800C4D34[14];
extern int topItemScreenColor_800C4D6C[14];
extern int topItemVibration_800C4DA4[14];
extern char topMenuItems_800C4DDC[20];
extern int audioItemMusic_800C4DF0[14];
extern int audioItemSfx_800C4E28[14];
extern int audioItemOutput_800C4E60[14];
extern char audioPageItems_800C4E98[16];
extern int musicVolume0_800C4EA8[14];
extern int musicVolume1_800C4EE0[14];
extern int musicVolume2_800C4F18[14];
extern int musicVolume3_800C4F50[14];
extern int musicVolume4_800C4F88[14];
extern int musicVolume5_800C4FC0[14];
extern int musicVolume6_800C4FF8[14];
extern int musicVolume7_800C5030[14];
extern int sfxVolume0_800C5068[14];
extern int sfxVolume1_800C50A0[14];
extern int sfxVolume2_800C50D8[14];
extern int sfxVolume3_800C5110[14];
extern int sfxVolume4_800C5148[14];
extern int sfxVolume5_800C5180[14];
extern int sfxVolume6_800C51B8[14];
extern int sfxVolume7_800C51F0[14];
extern int outputItem0_800C5228[14];
extern int outputItem1_800C5260[14];
extern char musicVolumeItems_800C5298[36];
extern char sfxVolumeItems_800C52BC[36];
extern char outputItems_800C52E0[12];
extern unsigned short subItemDisplaySpeed_800C52EC[28];
extern unsigned short subItemAnimSkip_800C5324[28];
extern unsigned short subItemSpeech_800C535C[28];
extern unsigned short subItemMagicEffects_800C5394[28];
extern unsigned short subItemCaptureEffects_800C53CC[28];
extern unsigned short subItemAutoMessage_800C5404[28];
extern unsigned short subItemSubtitles_800C543C[28];
extern unsigned short *subtitlePageItems_800C5474[8];
extern int displaySpeed0_800C5494[14];
extern int displaySpeed1_800C54CC[14];
extern int displaySpeed2_800C5504[14];
extern int displaySpeed3_800C553C[14];
extern char displaySpeedItems_800C5574[20];
extern int animSkip0_800C5588[14];
extern int animSkip1_800C55C0[14];
extern char animSkipItems_800C55F8[12];
extern int speech0_800C5604[14];
extern int speech1_800C563C[14];
extern char speechItems_800C5674[12];
extern int magicEffects0_800C5680[14];
extern int magicEffects1_800C56B8[14];
extern char magicEffectsItems_800C56F0[12];
extern int captureEffects0_800C56FC[14];
extern int captureEffects1_800C5734[14];
extern char captureEffectsItems_800C576C[12];
extern int autoMessage0_800C5778[14];
extern int autoMessage1_800C57B0[14];
extern char autoMessageItems_800C57E8[12];
extern int subtitles0_800C57F4[14];
extern int subtitles1_800C582C[14];
extern char subtitlesItems_800C5864[12];
extern int vibrationLabel_800C5870[14];
extern char vibrationLabelItems_800C58A8[8];
extern int vibration0_800C58B0[14];
extern int vibration1_800C58E8[14];
extern char vibrationItems_800C5920[12];
extern char helpBar_800C592C[24];
extern int configMenuActive_800C5944;

#endif
