// CONFIG.BIN: declarations shared by its source files
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"
#include "main.h"
#include "menu_window.h"
#include "event.h"
#include "pad_text.h"
#include "sound_seq.h"
#include "ui_sprites.h"

// the first 8 bytes of a menu cursor (CombSelCursor: cols, rows, count, flags)
typedef struct { char b[8]; } CfgCursorHead;


/* the types of config.c */
typedef struct CfgCtxConfig
{
    char pad_0[2];
    short page_2;     // 0 top menu, 1 audio, 2 subtitles, 3 screen color, 4 vibration (5 exits)
    short nextPage_4; // -1: stay
    unsigned short topCursor_6;
    // working copies of the settings (LoadConfigSettings_800C3060)
    unsigned char displaySpeed_8, animSkip_9, animSkip_A, magicEffects_B, outputFormat_C, bgmVolume_D, sfxVolume_E,
        uiColor_F, captureEffects_10, speech_11, vibration_12, autoMessage_13, subtitles_14, savedBgmVolume_15,
        savedSfxVolume_16;
    char pad_17[0x30 - 0x17];
    int notice_30; // DrawOptionUnavailable_800C4BDC message: 1 subtitles off, 2 speech off
    short noticeTimer_34;
    short pad_36;
    int editing_38; // EditConfigSettingTask_800C45E8 runs
    CfgCursorHead cursor_3C; // cursor_3C..scroll_46: an exe MenuCursor (UpdateMenuCursor_8003D794)
    short cursorPos_44;
    short scroll_46;
} CfgCtxConfig;


typedef struct CfgBoxConfig
{
    short x_0;
    short y_2;
    int pad_4;
    short col_8;
    char colors_A;
    char frame_B;
} CfgBoxConfig;


/* CONFIG functions */
extern void ConfigMenuTask_800C2F70(EventEntry* t, CfgCtxConfig* ctx);
extern void LoadConfigSettings_800C3060(CfgCtxConfig* c);
extern void HandleConfigPageInput_800C3540(CfgCtxConfig* c);
extern void OpenConfigPage_800C378C(CfgCtxConfig* c);
extern void DrawConfigPage_800C383C(CfgCtxConfig* c);
extern void DrawConfigTopMenu_800C38CC(CfgCtxConfig* c);
extern void DrawAudioPage_800C39C4(CfgCtxConfig* c);
extern void DrawSubtitlePage_800C3CA4(CfgCtxConfig* c);
extern void DrawScreenColorPage_800C4180(CfgCtxConfig* c);
extern void DrawVibrationPage_800C4390(CfgCtxConfig* c);
extern void DrawConfigHelpText_800C450C(CfgCtxConfig* c);
extern void EditConfigSettingTask_800C45E8(EventEntry* t, CfgCtxConfig* c);
extern void ConfigNoticeTask_800C4B34(EventEntry* t, CfgCtxConfig* c);
extern void DrawOptionUnavailable_800C4BDC(int notice);

/* CONFIG data */
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
extern const MenuWindowList menuHdrActive_800C2CD0;
extern const MenuWindowList menuHdrIdle_800C2CE8;
extern const int unused_800C2D00;
extern int topMenuHelp_800C4C80[4];
extern int audioPageHelp_800C4C90[3];
extern int subtitlePageHelp_800C4C9C[7];
extern int screenColorPageHelp_800C4CB8[1];
extern int vibrationPageHelp_800C4CBC[1];
extern int *pageHelpTexts_800C4CC0[5];
extern CfgCursorHead pageCursors_800C4CD4[5];
extern MenuWindowItem topItemAudio_800C4CFC[2];
extern MenuWindowItem topItemSubtitle_800C4D34[2];
extern MenuWindowItem topItemScreenColor_800C4D6C[2];
extern MenuWindowItem topItemVibration_800C4DA4[2];
extern MenuWindowItem* topMenuItems_800C4DDC[5];
extern MenuWindowItem audioItemMusic_800C4DF0[2];
extern MenuWindowItem audioItemSfx_800C4E28[2];
extern MenuWindowItem audioItemOutput_800C4E60[2];
extern MenuWindowItem* audioPageItems_800C4E98[4];
extern MenuWindowItem musicVolume0_800C4EA8[2];
extern MenuWindowItem musicVolume1_800C4EE0[2];
extern MenuWindowItem musicVolume2_800C4F18[2];
extern MenuWindowItem musicVolume3_800C4F50[2];
extern MenuWindowItem musicVolume4_800C4F88[2];
extern MenuWindowItem musicVolume5_800C4FC0[2];
extern MenuWindowItem musicVolume6_800C4FF8[2];
extern MenuWindowItem musicVolume7_800C5030[2];
extern MenuWindowItem sfxVolume0_800C5068[2];
extern MenuWindowItem sfxVolume1_800C50A0[2];
extern MenuWindowItem sfxVolume2_800C50D8[2];
extern MenuWindowItem sfxVolume3_800C5110[2];
extern MenuWindowItem sfxVolume4_800C5148[2];
extern MenuWindowItem sfxVolume5_800C5180[2];
extern MenuWindowItem sfxVolume6_800C51B8[2];
extern MenuWindowItem sfxVolume7_800C51F0[2];
extern MenuWindowItem outputItem0_800C5228[2];
extern MenuWindowItem outputItem1_800C5260[2];
extern MenuWindowItem* musicVolumeItems_800C5298[9];
extern MenuWindowItem* sfxVolumeItems_800C52BC[9];
extern MenuWindowItem* outputItems_800C52E0[3];
extern MenuWindowItem subItemDisplaySpeed_800C52EC[2];
extern MenuWindowItem subItemAnimSkip_800C5324[2];
extern MenuWindowItem subItemSpeech_800C535C[2];
extern MenuWindowItem subItemMagicEffects_800C5394[2];
extern MenuWindowItem subItemCaptureEffects_800C53CC[2];
extern MenuWindowItem subItemAutoMessage_800C5404[2];
extern MenuWindowItem subItemSubtitles_800C543C[2];
extern MenuWindowItem* subtitlePageItems_800C5474[8];
extern MenuWindowItem displaySpeed0_800C5494[2];
extern MenuWindowItem displaySpeed1_800C54CC[2];
extern MenuWindowItem displaySpeed2_800C5504[2];
extern MenuWindowItem displaySpeed3_800C553C[2];
extern MenuWindowItem* displaySpeedItems_800C5574[5];
extern MenuWindowItem animSkip0_800C5588[2];
extern MenuWindowItem animSkip1_800C55C0[2];
extern MenuWindowItem* animSkipItems_800C55F8[3];
extern MenuWindowItem speech0_800C5604[2];
extern MenuWindowItem speech1_800C563C[2];
extern MenuWindowItem* speechItems_800C5674[3];
extern MenuWindowItem magicEffects0_800C5680[2];
extern MenuWindowItem magicEffects1_800C56B8[2];
extern MenuWindowItem* magicEffectsItems_800C56F0[3];
extern MenuWindowItem captureEffects0_800C56FC[2];
extern MenuWindowItem captureEffects1_800C5734[2];
extern MenuWindowItem* captureEffectsItems_800C576C[3];
extern MenuWindowItem autoMessage0_800C5778[2];
extern MenuWindowItem autoMessage1_800C57B0[2];
extern MenuWindowItem* autoMessageItems_800C57E8[3];
extern MenuWindowItem subtitles0_800C57F4[2];
extern MenuWindowItem subtitles1_800C582C[2];
extern MenuWindowItem* subtitlesItems_800C5864[3];
extern MenuWindowItem vibrationLabel_800C5870[2];
extern MenuWindowItem* vibrationLabelItems_800C58A8[2];
extern MenuWindowItem vibration0_800C58B0[2];
extern MenuWindowItem vibration1_800C58E8[2];
extern MenuWindowItem* vibrationItems_800C5920[3];
extern ButtonHelpEntry helpBar_800C592C[3];
extern int configMenuActive_800C5944;

/* exe-side, to move to <exe header> */

#endif
