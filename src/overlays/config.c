// CONFIG.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"
#include "config.h"

int configOverlayId_800C29D0 SDATA = 36;
const char aVibrationSettin_800C29D4[] = "\202u\202\211\202\202\202\222\202\201\202\224\202\211\202\217\202\216\201@\202\223\202\205\202\224\202\224\202\211\202\216\202\207\202\223\201D"; // Vibration settings.
const char aSetScreenColor_800C29FC[] = "\202r\202\205\202\224\201@\202\223\202\203\202\222\202\205\202\205\202\216\201@\202\203\202\217\202\214\202\217\202\222\201D"; // Set screen color.
const char aChangeSubtitleS_800C2A20[] = "\202b\202\210\202\201\202\216\202\207\202\205\201@\202\223\202\225\202\202\202\224\202\211\202\224\202\214\202\205\201@\202\223\202\205\202\224\202\224\202\211\202\216\202\207\202\223\201D"; // Change subtitle settings.
const char aChangeAudioSett_800C2A54[] = "\202b\202\210\202\201\202\216\202\207\202\205\201@\202\201\202\225\202\204\202\211\202\217\201@\202\223\202\205\202\224\202\224\202\211\202\216\202\207\202\223\201D"; // Change audio settings.
const char aSetOutputFormat_800C2A84[] = "\202r\202\205\202\224\201@\202\217\202\225\202\224\202\220\202\225\202\224\201@\202\206\202\217\202\222\202\215\202\201\202\224\201D"; // Set output format.
const char aSetAudioEffects_800C2AAC[] = "\202r\202\205\202\224\201@\202\201\202\225\202\204\202\211\202\217\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\223\201@\202\226\202\217\202\214\202\225\202\215\202\205\201D"; // Set audio effects volume.
const char aSetMusicVolume_800C2AE0[] = "\202r\202\205\202\224\201@\202\215\202\225\202\223\202\211\202\203\201@\202\226\202\217\202\214\202\225\202\215\202\205\201D"; // Set music volume.
const char aSetCaptureSpeci_800C2B04[] = "\202r\202\205\202\224\201@\202\203\202\201\202\220\202\224\202\225\202\222\202\205\201@\202\223\202\220\202\205\202\203\202\211\202\201\202\214\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\223\201D"; // Set capture special effects.
const char aSetMagicSpecial_800C2B40[] = "\202r\202\205\202\224\201@\202\215\202\201\202\207\202\211\202\203\201@\202\223\202\220\202\205\202\203\202\211\202\201\202\214\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\223\201D"; // Set magic special effects.
const char aMessageWindowDi_800C2B78[] = "\202l\202\205\202\223\202\223\202\201\202\207\202\205\201@\202\227\202\211\202\216\202\204\202\217\202\227\201@\202\204\202\211\202\223\202\220\202\214\202\201\202\231\201D"; // Message window display.
const char aAutoMessage_800C2BA8[] = "\202`\202\225\202\224\202\217\201@\202\215\202\205\202\223\202\223\202\201\202\207\202\205\201D"; // Auto message.
const char aSelectVoiceAudi_800C2BC4[] = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202\226\202\217\202\211\202\203\202\205\201@\202\201\202\225\202\204\202\211\202\217\201@\202\217\202\225\202\224\202\220\202\225\202\224\201D"; // Select voice audio output.
const char aAllowAnimationS_800C2BFC[] = "\202`\202\214\202\214\202\217\202\227\201@\202\201\202\216\202\211\202\215\202\201\202\224\202\211\202\217\202\216\201@\202\223\202\213\202\211\202\220\201D"; // Allow animation skip.
const char aSetDisplaySpeed_800C2C28[] = "\202r\202\205\202\224\201@\202\204\202\211\202\223\202\220\202\214\202\201\202\231\201@\202\223\202\220\202\205\202\205\202\204\201D"; // Set display speed.
const char aExit_800C2C50[] = "\202d\202\230\202\211\202\224"; // Exit
const char aSelect_800C2C5C[] = "\202r\202\205\202\214\202\205\202\203\202\224"; // Select

int topMenuHelp_800C4C80[4] = { (int)aChangeAudioSett_800C2A54, (int)aChangeSubtitleS_800C2A20, (int)aSetScreenColor_800C29FC, (int)aVibrationSettin_800C29D4 };
int audioPageHelp_800C4C90[3] = { (int)aSetMusicVolume_800C2AE0, (int)aSetAudioEffects_800C2AAC, (int)aSetOutputFormat_800C2A84 };
int subtitlePageHelp_800C4C9C[7] = { (int)aSetDisplaySpeed_800C2C28, (int)aAllowAnimationS_800C2BFC, (int)aSelectVoiceAudi_800C2BC4, (int)aAutoMessage_800C2BA8, (int)aMessageWindowDi_800C2B78, (int)aSetMagicSpecial_800C2B40, (int)aSetCaptureSpeci_800C2B04 };
int screenColorPageHelp_800C4CB8[1] = { (int)aSetScreenColor_800C29FC };
int vibrationPageHelp_800C4CBC[1] = { (int)aVibrationSettin_800C29D4 };
int *pageHelpTexts_800C4CC0[5] = { topMenuHelp_800C4C80, audioPageHelp_800C4C90, subtitlePageHelp_800C4C9C, screenColorPageHelp_800C4CB8, vibrationPageHelp_800C4CBC };
CfgCursorHead pageCursors_800C4CD4[5] = {
    { { 1, 0, 4, 0, 4 } },
    { { 1, 0, 3, 0, 3 } },
    { { 1, 0, 7, 0, 7 } },
    { { 1, 0, 4, 0, 4 } },
    { { 1, 0, 1, 0, 1 } },
};
MenuWindowItem topItemAudio_800C4CFC[2] = {
    { 8, 1, 221, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x72, 0x51, 0x5C, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem topItemSubtitle_800C4D34[2] = {
    { 8, 1, 232, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x72, 0x65, 0x5C, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem topItemScreenColor_800C4D6C[2] = {
    { 8, 1, 42, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x72, 0x79, 0x5C, 0x12, 0, 2 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem topItemVibration_800C4DA4[2] = {
    { 8, 1, 171, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x72, 0x8D, 0x5C, 0x12, 0, 2 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem* topMenuItems_800C4DDC[5] = { topItemAudio_800C4CFC, topItemSubtitle_800C4D34, topItemScreenColor_800C4D6C, topItemVibration_800C4DA4, NULL };
MenuWindowItem audioItemMusic_800C4DF0[2] = {
    { 8, 1, 126, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x24, 0x53, 0x4F, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem audioItemSfx_800C4E28[2] = {
    { 8, 1, 168, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x24, 0x67, 0x4F, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem audioItemOutput_800C4E60[2] = {
    { 8, 1, 146, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x24, 0x7B, 0x4F, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem* audioPageItems_800C4E98[4] = { audioItemMusic_800C4DF0, audioItemSfx_800C4E28, audioItemOutput_800C4E60, NULL };
MenuWindowItem musicVolume0_800C4EA8[2] = {
    { 8, 1, 125, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x76, 0x53, 0x22, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem musicVolume1_800C4EE0[2] = {
    { 8, 1, 133, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x99, 0x53, 0x12, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem musicVolume2_800C4F18[2] = {
    { 8, 1, 134, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xAC, 0x53, 0x12, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem musicVolume3_800C4F50[2] = {
    { 8, 1, 135, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xBF, 0x53, 0x12, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem musicVolume4_800C4F88[2] = {
    { 8, 1, 136, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xD2, 0x53, 0x12, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem musicVolume5_800C4FC0[2] = {
    { 8, 1, 137, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xE5, 0x53, 0x12, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem musicVolume6_800C4FF8[2] = {
    { 8, 1, 138, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xF8, 0x53, 0x12, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem musicVolume7_800C5030[2] = {
    { 8, 1, 139, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x10B, 0x53, 0x12, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem sfxVolume0_800C5068[2] = {
    { 8, 1, 125, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x76, 0x67, 0x22, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem sfxVolume1_800C50A0[2] = {
    { 8, 1, 133, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x99, 0x67, 0x12, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem sfxVolume2_800C50D8[2] = {
    { 8, 1, 134, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xAC, 0x67, 0x12, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem sfxVolume3_800C5110[2] = {
    { 8, 1, 135, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xBF, 0x67, 0x12, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem sfxVolume4_800C5148[2] = {
    { 8, 1, 136, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xD2, 0x67, 0x12, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem sfxVolume5_800C5180[2] = {
    { 8, 1, 137, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xE5, 0x67, 0x12, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem sfxVolume6_800C51B8[2] = {
    { 8, 1, 138, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xF8, 0x67, 0x12, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem sfxVolume7_800C51F0[2] = {
    { 8, 1, 139, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x10B, 0x67, 0x12, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem outputItem0_800C5228[2] = {
    { 8, 1, 188, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x76, 0x7B, 0x41, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem outputItem1_800C5260[2] = {
    { 8, 1, 124, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xB9, 0x7B, 0x41, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem* musicVolumeItems_800C5298[9] = { musicVolume0_800C4EA8, musicVolume1_800C4EE0, musicVolume2_800C4F18, musicVolume3_800C4F50, musicVolume4_800C4F88, musicVolume5_800C4FC0, musicVolume6_800C4FF8, musicVolume7_800C5030, NULL };
MenuWindowItem* sfxVolumeItems_800C52BC[9] = { sfxVolume0_800C5068, sfxVolume1_800C50A0, sfxVolume2_800C50D8, sfxVolume3_800C5110, sfxVolume4_800C5148, sfxVolume5_800C5180, sfxVolume6_800C51B8, sfxVolume7_800C51F0, NULL };
MenuWindowItem* outputItems_800C52E0[3] = { outputItem0_800C5228, outputItem1_800C5260, NULL };
MenuWindowItem subItemDisplaySpeed_800C52EC[2] = {
    { 8, 1, 200, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x28, 0x29, 0x4F, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem subItemAnimSkip_800C5324[2] = {
    { 8, 1, 4, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x28, 0x48, 0x4F, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem subItemSpeech_800C535C[2] = {
    { 8, 1, 201, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x28, 0x5C, 0x4F, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem subItemMagicEffects_800C5394[2] = {
    { 8, 1, 50, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x28, 0x98, 0x4F, 0x12, 0, 2 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem subItemCaptureEffects_800C53CC[2] = {
    { 8, 1, 229, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x28, 0xAC, 0x4F, 0x12, 0, 2 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem subItemAutoMessage_800C5404[2] = {
    { 8, 1, 89, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x28, 0x70, 0x4F, 0x12, 0, 2 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem subItemSubtitles_800C543C[2] = {
    { 8, 1, 191, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x28, 0x84, 0x4F, 0x12, 0, 2 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem* subtitlePageItems_800C5474[8] = { subItemDisplaySpeed_800C52EC, subItemAnimSkip_800C5324, subItemSpeech_800C535C, subItemAutoMessage_800C5404, subItemSubtitles_800C543C, subItemMagicEffects_800C5394, subItemCaptureEffects_800C53CC };
MenuWindowItem displaySpeed0_800C5494[2] = {
    { 8, 1, 179, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x7D, 0x29, 0x25, 0x12, 0, 4 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem displaySpeed1_800C54CC[2] = {
    { 8, 1, 131, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xA3, 0x29, 0x25, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem displaySpeed2_800C5504[2] = {
    { 8, 1, 152, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xC9, 0x29, 0x25, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem displaySpeed3_800C553C[2] = {
    { 8, 1, 195, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xEF, 0x29, 0x25, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem* displaySpeedItems_800C5574[5] = { displaySpeed0_800C5494, displaySpeed1_800C54CC, displaySpeed2_800C5504, displaySpeed3_800C553C, NULL };
MenuWindowItem animSkip0_800C5588[2] = {
    { 8, 1, 44, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x7D, 0x48, 0x4B, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem animSkip1_800C55C0[2] = {
    { 8, 1, 45, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xC9, 0x48, 0x4B, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem* animSkipItems_800C55F8[3] = { animSkip0_800C5588, animSkip1_800C55C0, NULL };
MenuWindowItem speech0_800C5604[2] = {
    { 8, 1, 175, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x7D, 0x5C, 0x4B, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem speech1_800C563C[2] = {
    { 8, 1, 176, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xC9, 0x5C, 0x4B, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem* speechItems_800C5674[3] = { speech0_800C5604, speech1_800C563C, NULL };
MenuWindowItem magicEffects0_800C5680[2] = {
    { 8, 1, 143, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x7D, 0x98, 0x4B, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem magicEffects1_800C56B8[2] = {
    { 8, 1, 144, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xC9, 0x98, 0x4B, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem* magicEffectsItems_800C56F0[3] = { magicEffects0_800C5680, magicEffects1_800C56B8, NULL };
MenuWindowItem captureEffects0_800C56FC[2] = {
    { 8, 1, 143, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x7D, 0xAC, 0x4B, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem captureEffects1_800C5734[2] = {
    { 8, 1, 144, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xC9, 0xAC, 0x4B, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem* captureEffectsItems_800C576C[3] = { captureEffects0_800C56FC, captureEffects1_800C5734, NULL };
MenuWindowItem autoMessage0_800C5778[2] = {
    { 8, 1, 90, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x7D, 0x70, 0x4B, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem autoMessage1_800C57B0[2] = {
    { 8, 1, 91, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xC9, 0x70, 0x4B, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem* autoMessageItems_800C57E8[3] = { autoMessage0_800C5778, autoMessage1_800C57B0, NULL };
MenuWindowItem subtitles0_800C57F4[2] = {
    { 8, 1, 192, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x7D, 0x84, 0x4B, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem subtitles1_800C582C[2] = {
    { 8, 1, 193, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xC9, 0x84, 0x4B, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem* subtitlesItems_800C5864[3] = { subtitles0_800C57F4, subtitles1_800C582C, NULL };
MenuWindowItem vibrationLabel_800C5870[2] = {
    { 8, 1, 171, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x28, 0x6C, 0x4F, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem* vibrationLabelItems_800C58A8[2] = { vibrationLabel_800C5870, NULL };
MenuWindowItem vibration0_800C58B0[2] = {
    { 8, 1, 172, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0x7D, 0x6C, 0x4B, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem vibration1_800C58E8[2] = {
    { 8, 1, 173, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 0xC9, 0x6C, 0x4B, 0x12, 0, 3 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem* vibrationItems_800C5920[3] = { vibration0_800C58B0, vibration1_800C58E8, NULL };
ButtonHelpEntry helpBar_800C592C[3] = { { 16, aSelect_800C2C5C }, { 167, aExit_800C2C50 }, { -1 } };
int configMenuActive_800C5944 = 0;

// Matched
void StartConfigMenu_800C2EB4(void)
{
    EventNode* holder = configTask_8008B4B8;
    EventEntry* task = &holder->entry;
    CfgCtxConfig* c = task->buffer;
    holder->entry.flags = (holder->entry.flags | 1) & 0xFFFF7FFF;
    DrawMenuBackground_8002BE10();
    c->nextPage_4 = 0;
    c->page_2 = 0;
    c->cursor_3C = pageCursors_800C4CD4[5];
    c->cursorPos_44 = 0;
    c->scroll_46 = 0;
    c->editing_38 = 0;
    c->notice_30 = 0;
    c->noticeTimer_34 = 0;
    LoadConfigSettings_800C3060(c);
    DrawConfigPage_800C383C(c);
    configMenuActive_800C5944 = 1;
    task->cb_8 = (EventEntryFn)ConfigMenuTask_800C2F70;
}

// Matched
void ConfigMenuTask_800C2F70(EventEntry* t, CfgCtxConfig* ctx)
{
    short prevPos;
    CfgCtxConfig* c;
    c = ctx;
    DrawMenuBackground_8002BE10();
    DrawConfigPage_800C383C(ctx);
    DrawConfigHelpText_800C450C(ctx);
    DrawButtonHelpBar_8002B004(helpBar_800C592C, 0, 0xE);
    prevPos = ctx->cursorPos_44;
    UpdateMenuCursor_8003D794(&ctx->cursor_3C, 0);
    if (prevPos != ctx->cursorPos_44)
    {
        LoadConfigSettings_800C3060(ctx);
    }
    if (ctx->notice_30 == 0)
    {
        HandleConfigPageInput_800C3540(ctx);
    }
    if (ctx->nextPage_4 != -1)
    {
        if (ctx->nextPage_4 == 5)
            goto done;
        OpenConfigPage_800C378C(ctx);
    }
    if (c->nextPage_4 == 5)
    {
    done:
        configMenuActive_800C5944 = 0;
        t->flags = (t->flags & ~1) | 0x8000;
    }
}

// Matched
void LoadConfigSettings_800C3060(CfgCtxConfig* c)
{
    SaveData* save = &saveData_8008B570;
    c->subtitles_14 = ((unsigned char*)save)[0x1F] & 1;
    c->displaySpeed_8 = save->settings_1C.bits.a_0;
    c->animSkip_9 = save->settings_1C.bits.b_3;
    c->animSkip_A = save->settings_1C.bits.c_4;
    c->magicEffects_B = save->settings_1C.bits.d_5;
    c->outputFormat_C = save->settings_1C.bits.e_6;
    c->bgmVolume_D = save->settings_1C.bits.bgmVol_7 / 16;
    c->sfxVolume_E = save->settings_1C.bits.sfxVol_14 / 16;
    c->savedBgmVolume_15 = c->bgmVolume_D;
    c->savedSfxVolume_16 = c->sfxVolume_E;
    c->uiColor_F = save->uiColor_20.b;
    c->captureEffects_10 = save->settings_1C.bits.h_21;
    c->speech_11 = save->settings_1C.bits.i_22;
    if (c->subtitles_14 == 0)
    {
        c->speech_11 = 1;
    }
    if (saveData_8008B570.flags_0 & 0x40)
    {
        c->vibration_12 = 0;
    }
    else
    {
        c->vibration_12 = 1;
    }
    c->animSkip_A = c->animSkip_9;
    c->autoMessage_13 = (saveData_8008B570.settings_1C.word >> 0x17) & 1;
    if (c->subtitles_14 == 0)
    {
        c->autoMessage_13 = 1;
    }
    if (c->speech_11 == 0)
    {
        c->autoMessage_13 = 0;
    }
}

void ApplyConfigSetting_800C31DC(CfgCtxConfig* c)
{
    switch (c->page_2)
    {
    case 1:
        if (configMenuActive_800C5944 != 0)
        {
            switch (c->cursorPos_44)
            {
            case 0:
                c->savedBgmVolume_15 = saveData_8008B570.settings_1C.bits.bgmVol_7 / 16;
                break;
            case 1:
                c->savedSfxVolume_16 = saveData_8008B570.settings_1C.bits.sfxVol_14 / 16;
                break;
            case 2:
                saveData_8008B570.settings_1C.bits.e_6 = c->outputFormat_C;
                break;
            }
        }
        break;
    case 2:
        if (configMenuActive_800C5944 != 0)
        {
            switch (c->cursorPos_44)
            {
            case 0:
                {
                SaveData* save = &saveData_8008B570;
                save->settings_1C.bits.a_0 = c->displaySpeed_8;
                }
                break;
            case 1:
                {
                SaveData* save = &saveData_8008B570;
                unsigned char skip = c->animSkip_9;
                save->settings_1C.bits.b_3 = skip;
                save->settings_1C.bits.c_4 = skip;
                save->settings_1C.bits.c_4 = c->animSkip_A;
                }
                break;
            case 2:
                {
                SaveData* save = &saveData_8008B570;
                save->settings_1C.bits.i_22 = c->speech_11;
                if (save->settings_1C.bits.i_22 == 0)
                {
                    c->autoMessage_13 = 0;
                    save->settings_1C.bits.j_23 = 0;
                }
                }
                break;
            case 3:
                {
                SaveData* save = &saveData_8008B570;
                save->settings_1C.bits.j_23 = c->autoMessage_13;
                }
                break;
            case 4:
                {
                SaveData* save = &saveData_8008B570;
                save->settings_1C.bits.k_24 = c->subtitles_14;
                if (save->settings_1C.bits.k_24 == 0)
                {
                    c->speech_11 = 1;
                    save->settings_1C.bits.i_22 = 1;
                    c->autoMessage_13 = 1;
                    save->settings_1C.bits.j_23 = 1;
                }
                }
                break;
            case 5:
                {
                SaveData* save = &saveData_8008B570;
                save->settings_1C.bits.d_5 = c->magicEffects_B;
                }
                break;
            case 6:
                {
                SaveData* save = &saveData_8008B570;
                save->settings_1C.bits.h_21 = c->captureEffects_10;
                }
                break;
            }
        }
        break;
    case 3:
        if (configMenuActive_800C5944 != 0)
        {
            uiColor_8008B590 = c->uiColor_F;
        }
        break;
    case 4:
        if (configMenuActive_800C5944 != 0)
        {
            if (c->vibration_12 == 0)
            {
                saveData_8008B570.flags_0 |= 0x40;
            }
            else
            {
                saveData_8008B570.flags_0 &= ~0x40;
            }
        }
        break;
    }
}

void HandleConfigPageInput_800C3540(CfgCtxConfig* c)
{
    switch (c->page_2)
    {
    case 0:
        if (configMenuActive_800C5944 != 0)
        {
            if (IsConfirmPressedP1_8003D380(1))
            {
                c->nextPage_4 = c->cursorPos_44 + 1;
                c->topCursor_6 = c->cursorPos_44;
            }
            else if (IsCancelPressedP1_8003D41C(1))
            {
                c->nextPage_4 = 5;
            }
        }
        break;
    case 1:
        if (configMenuActive_800C5944 != 0)
        {
            if (IsConfirmPressedP1_8003D380(1))
            {
                configTask_8008B4B8->entry.cb_8 = (EventEntryFn)EditConfigSettingTask_800C45E8;
                c->editing_38 = 1;
            }
            else if (IsCancelPressedP1_8003D41C(1))
            {
                LoadConfigSettings_800C3060(c);
                c->nextPage_4 = 0;
                c->cursorPos_44 = c->topCursor_6;
            }
        }
        break;
    case 2:
        if (configMenuActive_800C5944 != 0)
        {
            if (IsConfirmPressedP1_8003D380(0))
            {
                if (c->subtitles_14 == 0 && (unsigned short)(c->cursorPos_44 - 2) < 2)
                {
                    configTask_8008B4B8->entry.cb_8 = (EventEntryFn)ConfigNoticeTask_800C4B34;
                    c->notice_30 = 1;
                    PlaySfx_80031494(0x7C);
                }
                else if (c->speech_11 == 0 && c->cursorPos_44 == 3)
                {
                    configTask_8008B4B8->entry.cb_8 = (EventEntryFn)ConfigNoticeTask_800C4B34;
                    c->notice_30 = 2;
                    PlaySfx_80031494(0x7C);
                }
                else
                {
                    configTask_8008B4B8->entry.cb_8 = (EventEntryFn)EditConfigSettingTask_800C45E8;
                    c->editing_38 = 1;
                    PlaySfx_80031494(0x7E);
                }
            }
            else if (IsCancelPressedP1_8003D41C(1))
            {
                LoadConfigSettings_800C3060(c);
                c->nextPage_4 = 0;
                c->cursorPos_44 = c->topCursor_6;
            }
        }
        break;
    case 3:
        if (configMenuActive_800C5944 != 0)
        {
            c->uiColor_F = c->cursorPos_44;
            if (IsConfirmPressedP1_8003D380(1))
            {
                ApplyConfigSetting_800C31DC(c);
            }
            else if (IsCancelPressedP1_8003D41C(1))
            {
                LoadConfigSettings_800C3060(c);
                c->nextPage_4 = 0;
                c->cursorPos_44 = c->topCursor_6;
            }
        }
        break;
    case 4:
        if (configMenuActive_800C5944 != 0)
        {
            if (IsConfirmPressedP1_8003D380(1))
            {
                configTask_8008B4B8->entry.cb_8 = (EventEntryFn)EditConfigSettingTask_800C45E8;
                c->editing_38 = 1;
            }
            else if (IsCancelPressedP1_8003D41C(1))
            {
                LoadConfigSettings_800C3060(c);
                c->nextPage_4 = 0;
                c->cursorPos_44 = c->topCursor_6;
            }
        }
        break;
    }
}

void OpenConfigPage_800C378C(CfgCtxConfig* c)
{
    c->cursor_3C = pageCursors_800C4CD4[c->nextPage_4];
    switch (c->nextPage_4)
    {
    case 3:
        if (c->page_2 == 0)
        {
            c->cursorPos_44 = uiColor_8008B590;
            c->scroll_46 = 0;
        }
        break;
    case 1:
    case 2:
    case 4:
        if (c->page_2 == 0)
        {
            c->cursorPos_44 = 0;
    case 0:
            c->scroll_46 = 0;
        }
        break;
    }
    c->page_2 = c->nextPage_4;
    c->nextPage_4 = -1;
}

void DrawConfigPage_800C383C(CfgCtxConfig* c)
{
    switch (c->page_2)
    {
    case 0:
        DrawConfigTopMenu_800C38CC(c);
        break;
    case 1:
        DrawAudioPage_800C39C4(c);
        break;
    case 2:
        DrawSubtitlePage_800C3CA4(c);
        break;
    case 3:
        DrawScreenColorPage_800C4180(c);
        break;
    case 4:
        DrawVibrationPage_800C4390(c);
        break;
    }
}
const MenuWindowList menuHdrActive_800C2CD0 = { 2, 0, 8, 0, 0, 14 };
const MenuWindowList menuHdrIdle_800C2CE8 = { 0, 0, 8, 0, 0, 14 };
const int dword_800C2D00 = 0;

// Matched
void DrawConfigTopMenu_800C38CC(CfgCtxConfig* c)
{
    short rect[4];
    MenuWindowList cfg;
    CfgBoxConfig box;
    cfg = menuHdrActive_800C2CD0;
    cfg.time_4 = GetTime30Hz_8002C64C();
    cfg.cursor_C = c->cursorPos_44;
    cfg.items_10 = topMenuItems_800C4DDC;
    DrawMenuWindows_8002A5A4(&cfg);
    rect[0] = 0x7D;
    rect[1] = 0x12;
    rect[2] = 0x46;
    rect[3] = 0x12;
    box.frame_B = 1;
    box.x_0 = 0x84;
    box.col_8 = uiColor_8008B590;
    box.colors_A = 0;
    box.y_2 = 0x15;
    DrawUiTiySprt_8002C06C(&box, 0x4F, 0xE);
    DrawWindow_80042460(rect, &box.col_8, pOT_8008D454 + 14, 0);
}

// Matched
void DrawAudioPage_800C39C4(CfgCtxConfig* c)
{
    short rect[4];
    MenuWindowList top;
    MenuWindowList music;
    MenuWindowList sfx;
    MenuWindowList output;
    CfgBoxConfig box;
    top = menuHdrActive_800C2CD0;
    music = menuHdrIdle_800C2CE8;
    sfx = menuHdrIdle_800C2CE8;
    output = menuHdrIdle_800C2CE8;
    top.time_4 = GetTime30Hz_8002C64C();
    top.cursor_C = c->cursorPos_44;
    top.items_10 = audioPageItems_800C4E98;
    music.time_4 = GetTime30Hz_8002C64C();
    music.cursor_C = saveData_8008B570.settings_1C.bits.bgmVol_7 / 16;
    music.items_10 = musicVolumeItems_800C5298;
    sfx.time_4 = GetTime30Hz_8002C64C();
    sfx.cursor_C = saveData_8008B570.settings_1C.bits.sfxVol_14 / 16;
    sfx.items_10 = sfxVolumeItems_800C52BC;
    output.time_4 = GetTime30Hz_8002C64C();
    output.cursor_C = c->outputFormat_C;
    output.items_10 = outputItems_800C52E0;
    ApplyBgmVolume_800309D8(&bgmSound_80091CE0);
    if (c->editing_38)
    {
        top.flags_0 = 4;
    }
    else
    {
        top.flags_0 = 2;
    }
    DrawMenuWindows_8002A5A4(&top);
    if (c->editing_38)
    {
        music.flags_0 = 4;
        sfx.flags_0 = 4;
        output.flags_0 = 4;
        switch (c->cursorPos_44)
        {
        case 0:
            music.flags_0 = 2;
            break;
        case 1:
            sfx.flags_0 = 2;
            break;
        case 2:
            output.flags_0 = 2;
            break;
        }
    }
    else
    {
        music.flags_0 = 4;
        sfx.flags_0 = 4;
        output.flags_0 = 4;
    }
    DrawMenuWindows_8002A5A4(&music);
    DrawMenuWindows_8002A5A4(&sfx);
    DrawMenuWindows_8002A5A4(&output);
    rect[0] = 0x72;
    rect[1] = 0x12;
    rect[2] = 0x5C;
    rect[3] = 0x12;
    box.frame_B = 1;
    box.x_0 = 0x93;
    box.y_2 = 0x15;
    box.col_8 = uiColor_8008B590;
    box.colors_A = 0;
    box.x_0 = 0x8B;
    DrawUiTiySprt_8002C06C(&box, 0xDD, 0xE);
    DrawWindow_80042460(rect, &box.col_8, pOT_8008D454 + 14, 0);
}

void DrawSubtitlePage_800C3CA4(CfgCtxConfig* c)
{
    short rect[4];
    MenuWindowList top;
    MenuWindowList b1;
    MenuWindowList b2;
    MenuWindowList b3;
    MenuWindowList b4;
    MenuWindowList b5;
    MenuWindowList b6;
    MenuWindowList b7;
    CfgBoxConfig box;
    MenuWindowItem** items;
    top = menuHdrActive_800C2CD0;
    b1 = menuHdrIdle_800C2CE8;
    b2 = menuHdrIdle_800C2CE8;
    b3 = menuHdrIdle_800C2CE8;
    b4 = menuHdrIdle_800C2CE8;
    b5 = menuHdrIdle_800C2CE8;
    b6 = menuHdrIdle_800C2CE8;
    b7 = menuHdrIdle_800C2CE8;
    top.time_4 = GetTime30Hz_8002C64C();
    top.cursor_C = c->cursorPos_44;
    items = subtitlePageItems_800C5474;
    top.items_10 = items;
    b1.time_4 = GetTime30Hz_8002C64C();
    b1.cursor_C = c->displaySpeed_8;
    b1.items_10 = displaySpeedItems_800C5574;
    b2.time_4 = GetTime30Hz_8002C64C();
    b2.cursor_C = (*(unsigned int*)&c->displaySpeed_8 & 0xFFFF00) != 0;
    b2.items_10 = animSkipItems_800C55F8;
    b3.time_4 = GetTime30Hz_8002C64C();
    b3.cursor_C = c->speech_11;
    b3.items_10 = speechItems_800C5674;
    b4.time_4 = GetTime30Hz_8002C64C();
    b4.cursor_C = c->magicEffects_B;
    b4.items_10 = magicEffectsItems_800C56F0;
    b5.time_4 = GetTime30Hz_8002C64C();
    b5.cursor_C = c->captureEffects_10;
    b5.items_10 = captureEffectsItems_800C576C;
    b6.time_4 = GetTime30Hz_8002C64C();
    b6.cursor_C = c->autoMessage_13;
    b6.items_10 = autoMessageItems_800C57E8;
    b7.time_4 = GetTime30Hz_8002C64C();
    b7.cursor_C = c->subtitles_14;
    b7.items_10 = subtitlesItems_800C5864;
    if (c->editing_38)
    {
        top.flags_0 = 4;
    }
    else
    {
        top.flags_0 = 2;
        if (c->subtitles_14 == 0)
        {
            items[2]->flags_0 |= 2;
        }
        else
        {
            items[2]->flags_0 &= ~2;
            items[3]->flags_0 &= ~2;
            if (c->speech_11 != 0)
            {
                goto done;
            }
        }
        items[3]->flags_0 |= 2;
    }
done:
    DrawMenuWindows_8002A5A4(&top);
    if (c->editing_38)
    {
        b1.flags_0 = 4;
        b2.flags_0 = 4;
        b3.flags_0 = 4;
        b4.flags_0 = 4;
        b5.flags_0 = 4;
        b6.flags_0 = 4;
        b7.flags_0 = 4;
        switch (c->cursorPos_44)
        {
        case 0:
            b1.flags_0 = 2;
            break;
        case 1:
            b2.flags_0 = 2;
            break;
        case 2:
            b3.flags_0 = 2;
            break;
        case 3:
            b6.flags_0 = 2;
            break;
        case 4:
            b7.flags_0 = 2;
            break;
        case 5:
            b4.flags_0 = 2;
            break;
        case 6:
            b5.flags_0 = 2;
            break;
        }
    }
    else
    {
        b1.flags_0 = 4;
        b2.flags_0 = 4;
        b3.flags_0 = 4;
        b4.flags_0 = 4;
        b5.flags_0 = 4;
        b6.flags_0 = 4;
        b7.flags_0 = 4;
    }
    DrawMenuWindows_8002A5A4(&b1);
    DrawMenuWindows_8002A5A4(&b2);
    DrawMenuWindows_8002A5A4(&b3);
    DrawMenuWindows_8002A5A4(&b6);
    DrawMenuWindows_8002A5A4(&b7);
    DrawMenuWindows_8002A5A4(&b4);
    DrawMenuWindows_8002A5A4(&b5);
    rect[0] = 0x72;
    rect[1] = 0x12;
    rect[2] = 0x5C;
    rect[3] = 0x12;
    box.frame_B = 1;
    box.x_0 = 0x78;
    box.col_8 = uiColor_8008B590;
    box.colors_A = 0;
    box.y_2 = 0x15;
    DrawUiTiySprt_8002C06C(&box, 0xE8, 0xE);
    DrawWindow_80042460(rect, &box.col_8, pOT_8008D454 + 14, 0);
}

// Matched
void DrawScreenColorPage_800C4180(CfgCtxConfig* c)
{
    short rect[4];
    CfgBoxConfig box1;
    short rect2[4];
    short rect3[4];
    WindowStyle tail;
    CfgBoxConfig box3;
    short i;
    rect[0] = 0x72;
    rect[1] = 0x12;
    rect[2] = 0x5C;
    rect[3] = 0x12;
    box1.frame_B = 1;
    box1.colors_A = 0;
    box1.x_0 = 0x8C;
    box1.col_8 = uiColor_8008B590;
    box1.y_2 = 0x14;
    DrawUiTiySprt_8002C06C(&box1, 0x2A, 0xE);
    box1.x_0 = 0x8C;
    box1.y_2 = 0x15;
    DrawWindow_80042460(rect, &box1.col_8, pOT_8008D454 + 14, 0);
    for (i = 0; i < 4; i++)
    {
        unsigned int blink;
        rect2[0] = 0x52;
        rect2[1] = i * 38 + 0x2A;
        rect2[2] = 0x12;
        rect2[3] = 0x24;
        tail.colorSet_2 = 1;
        if (c->uiColor_F == i)
        {
            blink = (unsigned int)(frameCount_8008D3FC * display_8008B4D8.vsyncsPerFrame_4) >> 1;
        }
        else
        {
            blink = 0;
        }
        tail.color_0 = i;
        tail.semiTrans_3 = 1;
        DrawWindow_80042460(rect2, &tail, pOT_8008D454 + 14, blink);
        rect3[0] = 0x66;
        rect3[1] = i * 38 + 0x2A;
        rect3[2] = 0x76;
        rect3[3] = 0x24;
        box3.colors_A = 0;
        box3.col_8 = i;
        box3.frame_B = 1;
        box3.x_0 = 0x74;
        box3.y_2 = i * 38 + 0x2C;
        DrawUiTiySprt_8002C06C(&box3, 0xCA, 0xE);
        box3.x_0 = rect3[0] + 0xE;
        box3.y_2 = rect3[1] + 6;
        DrawWindow_80042460(rect3, &box3.col_8, pOT_8008D454 + 14, 0);
    }
}

// Matched
void DrawVibrationPage_800C4390(CfgCtxConfig* c)
{
    short rect[4];
    MenuWindowList label;
    MenuWindowList opts;
    CfgBoxConfig box;
    label = menuHdrIdle_800C2CE8;
    opts = menuHdrIdle_800C2CE8;
    label.time_4 = GetTime30Hz_8002C64C();
    label.cursor_C = 0;
    label.items_10 = vibrationLabelItems_800C58A8;
    opts.time_4 = GetTime30Hz_8002C64C();
    opts.cursor_C = c->vibration_12;
    opts.items_10 = vibrationItems_800C5920;
    if (c->editing_38)
    {
        label.flags_0 = 4;
    }
    else
    {
        label.flags_0 = 2;
    }
    DrawMenuWindows_8002A5A4(&label);
    if (c->editing_38)
    {
        opts.flags_0 = 2;
    }
    else
    {
        opts.flags_0 = 4;
    }
    DrawMenuWindows_8002A5A4(&opts);
    rect[0] = 0x72;
    rect[1] = 0x12;
    rect[2] = 0x5C;
    rect[3] = 0x12;
    box.frame_B = 1;
    box.x_0 = 0x85;
    box.col_8 = uiColor_8008B590;
    box.colors_A = 0;
    box.y_2 = 0x15;
    DrawUiTiySprt_8002C06C(&box, 0xAB, 0xE);
    box.x_0 = 0x8C;
    box.y_2 = 0x15;
    DrawWindow_80042460(rect, &box.col_8, pOT_8008D454 + 14, 0);
}

// Matched
void DrawConfigHelpText_800C450C(CfgCtxConfig* c)
{
    int text;
    short rect[4];
    short pos[2];
    short page = c->page_2;
    if (page >= 0)
    {
        if (page < 3)
        {
            text = pageHelpTexts_800C4CC0[page][c->cursorPos_44];
        }
        else if (page < 5)
        {
            text = *pageHelpTexts_800C4CC0[page];
        }
        else
        {
            text = 0;
        }
    }
    else
    {
        text = 0;
    }
    rect[0] = 10;
    rect[1] = 0xC2;
    rect[2] = 0x12C;
    rect[3] = 0x12;
    pos[0] = 0xE;
    pos[1] = 0xC5;
    DrawTextLinesWindow_8002AE38(&text, pos, 0xE, rect, 1);
}

// Matched
int IsConfigMenuActive_800C45D8(void)
{
    return configMenuActive_800C5944;
}

void EditConfigSettingTask_800C45E8(EventEntry* t, CfgCtxConfig* c)
{
    GridCursor v10;
    GridCursor v20;
    GridCursor v30;
    GridCursor v40;
    GridCursor v50;
    GridCursor v60;
    GridCursor v70;
    GridCursor v80;
    int sel;
    DrawMenuBackground_8002BE10();
    DrawConfigPage_800C383C(c);
    DrawConfigHelpText_800C450C(c);
    DrawButtonHelpBar_8002B004(helpBar_800C592C, 0, 0xE);
    if (c->page_2 == 1)
    {
        switch (c->cursorPos_44)
        {
        case 0:
            sel = saveData_8008B570.settings_1C.bits.bgmVol_7 / 16;
            v10.flags_0 = 0;
            v10.field_4 = 0;
            v10.cols_8 = 8;
            v10.rows_A = 1;
            v10.pos_6 = sel;
            MoveGridCursorP1_8003D630(&v10);
            if (sel != v10.pos_6)
            {
                PlaySfx_80031494(0x7F);
            }
            sel = v10.pos_6;
            saveData_8008B570.settings_1C.bits.bgmVol_7 = sel * 16;
            break;
        case 1:
            sel = saveData_8008B570.settings_1C.bits.sfxVol_14 / 16;
            v20.flags_0 = 0;
            v20.field_4 = 0;
            v20.cols_8 = 8;
            v20.rows_A = 1;
            v20.pos_6 = sel;
            MoveGridCursorP1_8003D630(&v20);
            if (sel != v20.pos_6)
            {
                PlaySfx_80031494(0x7F);
            }
            sel = v20.pos_6;
            saveData_8008B570.settings_1C.bits.sfxVol_14 = sel * 16;
            break;
        case 2:
            v30.flags_0 = 0;
            v30.field_4 = 0;
            v30.cols_8 = 2;
            v30.rows_A = 1;
            v30.pos_6 = c->outputFormat_C;
            MoveGridCursorP1_8003D630(&v30);
            if (c->outputFormat_C != v30.pos_6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->outputFormat_C = v30.pos_6;
            break;
        }
    }
    else if (c->page_2 == 2)
    {
        switch (c->cursorPos_44)
        {
        case 0:
            {
            v10.flags_0 = 0;
            v10.field_4 = 0;
            v10.cols_8 = 4;
            v10.rows_A = 1;
            v10.pos_6 = c->displaySpeed_8;
            MoveGridCursorP1_8003D630(&v10);
            if (c->displaySpeed_8 != v10.pos_6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->displaySpeed_8 = v10.pos_6;
            }
            break;
        case 1:
            {
            v20.flags_0 = 0;
            v20.field_4 = 0;
            v20.cols_8 = 2;
            v20.rows_A = 1;
            v20.pos_6 = c->animSkip_9;
            MoveGridCursorP1_8003D630(&v20);
            if (c->animSkip_9 != v20.pos_6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->animSkip_A = c->animSkip_9 = v20.pos_6;
            }
            break;
        case 2:
            {
            v40.flags_0 = 0;
            v40.field_4 = 0;
            v40.cols_8 = 2;
            v40.rows_A = 1;
            v40.pos_6 = c->speech_11;
            MoveGridCursorP1_8003D630(&v40);
            if (c->speech_11 != v40.pos_6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->speech_11 = v40.pos_6;
            }
            break;
        case 3:
            {
            v50.flags_0 = 0;
            v50.field_4 = 0;
            v50.cols_8 = 2;
            v50.rows_A = 1;
            v50.pos_6 = c->autoMessage_13;
            MoveGridCursorP1_8003D630(&v50);
            if (c->autoMessage_13 != v50.pos_6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->autoMessage_13 = v50.pos_6;
            }
            break;
        case 4:
            {
            v60.flags_0 = 0;
            v60.field_4 = 0;
            v60.cols_8 = 2;
            v60.rows_A = 1;
            v60.pos_6 = c->subtitles_14;
            MoveGridCursorP1_8003D630(&v60);
            if (c->subtitles_14 != v60.pos_6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->subtitles_14 = v60.pos_6;
            }
            break;
        case 5:
            {
            v70.flags_0 = 0;
            v70.field_4 = 0;
            v70.cols_8 = 2;
            v70.rows_A = 1;
            v70.pos_6 = c->magicEffects_B;
            MoveGridCursorP1_8003D630(&v70);
            if (c->magicEffects_B != v70.pos_6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->magicEffects_B = v70.pos_6;
            }
            break;
        case 6:
            {
            v80.flags_0 = 0;
            v80.field_4 = 0;
            v80.cols_8 = 2;
            v80.rows_A = 1;
            v80.pos_6 = c->captureEffects_10;
            MoveGridCursorP1_8003D630(&v80);
            if (c->captureEffects_10 != v80.pos_6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->captureEffects_10 = v80.pos_6;
            }
            break;
        }
    }
    else if (c->page_2 == 4)
    {
        v10.flags_0 = 0;
        v10.field_4 = 0;
        v10.cols_8 = 2;
        v10.rows_A = 1;
        v10.pos_6 = c->vibration_12;
        MoveGridCursorP1_8003D630(&v10);
        if (c->vibration_12 != v10.pos_6)
        {
            PlaySfx_80031494(0x7F);
        }
        c->vibration_12 = v10.pos_6;
    }
    if (IsConfirmPressedP1_8003D380(1))
    {
        ApplyConfigSetting_800C31DC(c);
        t->cb_8 = (EventEntryFn)ConfigMenuTask_800C2F70;
        c->editing_38 = 0;
    }
    else if (IsCancelPressedP1_8003D41C(1))
    {
        saveData_8008B570.settings_1C.bits.bgmVol_7 = c->savedBgmVolume_15 * 16;
        saveData_8008B570.settings_1C.bits.sfxVol_14 = c->savedSfxVolume_16 * 16;
        LoadConfigSettings_800C3060(c);
        t->cb_8 = (EventEntryFn)ConfigMenuTask_800C2F70;
        c->editing_38 = 0;
    }
}

// Matched
void ConfigNoticeTask_800C4B34(EventEntry* t, CfgCtxConfig* c)
{
    DrawMenuBackground_8002BE10();
    DrawConfigPage_800C383C(c);
    DrawOptionUnavailable_800C4BDC((short)c->notice_30);
    if (c->noticeTimer_34 >= 0x96 || IsConfirmPressedP1_8003D380(0) || IsCancelPressedP1_8003D41C(0))
    {
        PlaySfx_80031494(0x7D);
        t->cb_8 = (EventEntryFn)ConfigMenuTask_800C2F70;
        c->notice_30 = 0;
        c->noticeTimer_34 = 0;
    }
    else
    {
        c->noticeTimer_34++;
    }
}

// Matched
void DrawOptionUnavailable_800C4BDC(int notice)
{
    short rect[4];
    short pos[2];
    const char* lines[2];
    if ((short)notice == 2)
    {
        lines[0] = "\202n\202\220\202\224\202\211\202\217\202\216\201@\202\216\202\217\202\224\201@\202\201\202\226\202\201\202\211\202\214\202\201\202\202\202\214\202\205\201@\202\227\202\210\202\211\202\214\202\205\201@\202r\202\220\202\205\202\205\202\203\202\210\201@\202\211\202\223\201@\202\223\202\205\202\224\201@\202\224\202\217\201@\202n\202e\202e\201D"; // Option not available while Speech is set to OFF.
        lines[1] = "\202r\202\205\202\224\201@\202r\202\220\202\205\202\205\202\203\202\210\201@\202\224\202\217\201@\202n\202m\201@\202\224\202\217\201@\202\205\202\216\202\201\202\202\202\214\202\205\201@\202\224\202\210\202\211\202\223\201@\202\217\202\220\202\224\202\211\202\217\202\216\201D"; // Set Speech to ON to enable this option.
    }
    else
    {
        lines[0] = "\202n\202\220\202\224\202\211\202\217\202\216\201@\202\216\202\217\202\224\201@\202\201\202\226\202\201\202\211\202\214\202\201\202\202\202\214\202\205\201@\202\227\202\210\202\211\202\214\202\205\201@\202r\202\225\202\202\202\224\202\211\202\224\202\214\202\205\202\223\201@\202\211\202\223\201@\202\223\202\205\202\224\201@\202\224\202\217\201@\202n\202e\202e\201D"; // Option not available while Subtitles is set to OFF.
        lines[1] = "\202r\202\205\202\224\201@\202r\202\225\202\202\202\224\202\211\202\224\202\214\202\205\202\223\201@\202\224\202\217\201@\202n\202m\201@\202\224\202\217\201@\202\205\202\216\202\201\202\202\202\214\202\205\201@\202\224\202\210\202\211\202\223\201@\202\217\202\220\202\224\202\211\202\217\202\216\201D"; // Set Subtitles to ON to enable this option.
    }
    rect[0] = 10;
    rect[1] = 0xC2;
    rect[2] = 0x12C;
    rect[3] = 0x22;
    pos[0] = 0xD;
    pos[1] = 0xC4;
    DrawTextLinesWindow_8002AE38(lines, pos, 0xE, rect, 2);
}
