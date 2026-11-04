// CONFIG.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"
#include "config.h"

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
    Bytes8Config cursor_3C; // cursor_3C..scroll_46: an exe MenuCursor (UpdateMenuCursor_8003D794)
    short cursorPos_44;
    short scroll_46;
} CfgCtxConfig;

typedef struct CfgTaskConfig
{
    unsigned int flags_0;
    int pad_4;
    void (*next_8)();
    int pad_C;
    int pad_10;
    CfgCtxConfig* ctx_14;
} CfgTaskConfig;

typedef struct CfgHolderConfig
{
    char pad_0[0x10];
    CfgTaskConfig t_10;
} CfgHolderConfig;
extern CfgHolderConfig* dword_8008B4B8;
extern void DrawTextLinesWindow_8002AE38(void* a0, void* a1, int a2, void* a3, int a4);
extern int IsConfirmPressedP1_8003D380(int a);
extern int IsCancelPressedP1_8003D41C(int a);
extern void PlaySfx_80031494(int a);
extern void DrawOptionUnavailable_800C4BDC(int n);
typedef struct CfgSpinConfig
{
    int flags_0;
    short unused_4, pos_6, cols_8, rows_A;
} CfgSpinConfig;

typedef struct CfgBoxConfig
{
    short x_0;
    short y_2;
    int pad_4;
    short col_8;
    char colors_A;
    char frame_B;
} CfgBoxConfig;

extern char* dword_8008D454;
extern unsigned short uiColor_8008B590;
extern void DrawMenuWindows_8002A5A4(CfgDlgConfig* p);
extern void DrawUiTiySprt_8002C06C(void* p, int a, short b);
extern void DrawWindow_80042460(void* a0, void* a1, void* a2, unsigned int a3);
extern unsigned int GetTime30Hz_8002C64C(void);
extern void ApplyBgmVolume_800309D8(void* p);
typedef struct CfgTailConfig
{
    short col_0;
    char colors_2;
    char frame_3;
} CfgTailConfig;
extern int frameCount_8008D3FC;
extern void DrawMenuBackground_8002BE10();
extern void DrawButtonHelpBar_8002B004(void*, int, int);
extern void UpdateMenuCursor_8003D794(void*, int);
extern void ConfigMenuTask_800C2F70();
extern void LoadConfigSettings_800C3060(CfgCtxConfig*);
extern void DrawConfigPage_800C383C(CfgCtxConfig*);
extern void DrawConfigHelpText_800C450C(CfgCtxConfig*);
extern void HandleConfigPageInput_800C3540(CfgCtxConfig*);
extern void OpenConfigPage_800C378C(CfgCtxConfig*);
extern void DrawConfigTopMenu_800C38CC(CfgCtxConfig*);
extern void DrawAudioPage_800C39C4(CfgCtxConfig*);
extern void DrawSubtitlePage_800C3CA4(CfgCtxConfig*);
extern void DrawScreenColorPage_800C4180(CfgCtxConfig*);
extern void DrawVibrationPage_800C4390(CfgCtxConfig*);
extern void EditConfigSettingTask_800C45E8();
extern void ConfigNoticeTask_800C4B34(CfgTaskConfig*, CfgCtxConfig*);

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

// Matched
void StartConfigMenu_800C2EB4(void)
{
    CfgHolderConfig* h = dword_8008B4B8;
    CfgTaskConfig* t = &h->t_10;
    CfgCtxConfig* c = t->ctx_14;
    h->t_10.flags_0 = (h->t_10.flags_0 | 1) & 0xFFFF7FFF;
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
    t->next_8 = ConfigMenuTask_800C2F70;
}

#if 0
// Not matched: the original keeps a second copy of the context pointer in another register
void ConfigMenuTask_800C2F70(CfgTaskConfig* t, CfgCtxConfig* d)
{
    short old;
    CfgCtxConfig* c;
    DrawMenuBackground_8002BE10();
    DrawConfigPage_800C383C(d);
    DrawConfigHelpText_800C450C(d);
    DrawButtonHelpBar_8002B004(helpBar_800C592C, 0, 0xE);
    old = d->cursorPos_44;
    UpdateMenuCursor_8003D794(&d->cursor_3C, 0);
    c = d;
    if (old != c->cursorPos_44)
    {
        LoadConfigSettings_800C3060(c);
    }
    if (c->notice_30 == 0)
    {
        HandleConfigPageInput_800C3540(c);
    }
    if (c->nextPage_4 != -1)
    {
        if (c->nextPage_4 != 5)
        {
            OpenConfigPage_800C378C(c);
            if (d->nextPage_4 != 5)
            {
                return;
            }
        }
    }
    else if (d->nextPage_4 != 5)
    {
        return;
    }
    configMenuActive_800C5944 = 0;
    t->flags_0 = (t->flags_0 & ~1) | 0x8000;
}

#endif
INCLUDE_OVERLAY_ASM(config, ConfigMenuTask_800C2F70);

// Matched
void LoadConfigSettings_800C3060(CfgCtxConfig* c)
{
    SaveData* s = &saveData_8008B570;
    c->subtitles_14 = ((unsigned char*)s)[0x1F] & 1;
    c->displaySpeed_8 = s->settings_1C.bits.a_0;
    c->animSkip_9 = s->settings_1C.bits.b_3;
    c->animSkip_A = s->settings_1C.bits.c_4;
    c->magicEffects_B = s->settings_1C.bits.d_5;
    c->outputFormat_C = s->settings_1C.bits.e_6;
    c->bgmVolume_D = s->settings_1C.bits.bgmVol_7 / 16;
    c->sfxVolume_E = s->settings_1C.bits.sfxVol_14 / 16;
    c->savedBgmVolume_15 = c->bgmVolume_D;
    c->savedSfxVolume_16 = c->sfxVolume_E;
    c->uiColor_F = s->uiColor_20.b;
    c->captureEffects_10 = s->settings_1C.bits.h_21;
    c->speech_11 = s->settings_1C.bits.i_22;
    if (c->subtitles_14 == 0)
    {
        c->speech_11 = 1;
    }
    if (saveData_8008B570.field_0 & 0x40)
    {
        c->vibration_12 = 0;
    }
    else
    {
        c->vibration_12 = 1;
    }
    c->animSkip_A = c->animSkip_9;
    c->autoMessage_13 = (settingsFlags_8008B58C.word >> 0x17) & 1;
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
                SaveData* s = &saveData_8008B570;
                s->settings_1C.bits.a_0 = c->displaySpeed_8;
                }
                break;
            case 1:
                {
                SaveData* s = &saveData_8008B570;
                unsigned char t = c->animSkip_9;
                s->settings_1C.bits.b_3 = t;
                s->settings_1C.bits.c_4 = t;
                s->settings_1C.bits.c_4 = c->animSkip_A;
                }
                break;
            case 2:
                {
                SaveData* s = &saveData_8008B570;
                s->settings_1C.bits.i_22 = c->speech_11;
                if (s->settings_1C.bits.i_22 == 0)
                {
                    c->autoMessage_13 = 0;
                    s->settings_1C.bits.j_23 = 0;
                }
                }
                break;
            case 3:
                {
                SaveData* s = &saveData_8008B570;
                s->settings_1C.bits.j_23 = c->autoMessage_13;
                }
                break;
            case 4:
                {
                SaveData* s = &saveData_8008B570;
                s->settings_1C.bits.k_24 = c->subtitles_14;
                if (s->settings_1C.bits.k_24 == 0)
                {
                    c->speech_11 = 1;
                    s->settings_1C.bits.i_22 = 1;
                    c->autoMessage_13 = 1;
                    s->settings_1C.bits.j_23 = 1;
                }
                }
                break;
            case 5:
                {
                SaveData* s = &saveData_8008B570;
                s->settings_1C.bits.d_5 = c->magicEffects_B;
                }
                break;
            case 6:
                {
                SaveData* s = &saveData_8008B570;
                s->settings_1C.bits.h_21 = c->captureEffects_10;
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
                saveData_8008B570.field_0 |= 0x40;
            }
            else
            {
                saveData_8008B570.field_0 &= ~0x40;
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
                dword_8008B4B8->t_10.next_8 = EditConfigSettingTask_800C45E8;
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
                    dword_8008B4B8->t_10.next_8 = ConfigNoticeTask_800C4B34;
                    c->notice_30 = 1;
                    PlaySfx_80031494(0x7C);
                }
                else if (c->speech_11 == 0 && c->cursorPos_44 == 3)
                {
                    dword_8008B4B8->t_10.next_8 = ConfigNoticeTask_800C4B34;
                    c->notice_30 = 2;
                    PlaySfx_80031494(0x7C);
                }
                else
                {
                    dword_8008B4B8->t_10.next_8 = EditConfigSettingTask_800C45E8;
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
                dword_8008B4B8->t_10.next_8 = EditConfigSettingTask_800C45E8;
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
const CfgDlgConfig menuHdrActive_800C2CD0 = { 2, 0, 8, 0, 0, 14 };
const CfgDlgConfig menuHdrIdle_800C2CE8 = { 0, 0, 8, 0, 0, 14 };
const int dword_800C2D00 = 0;

// Matched
void DrawConfigTopMenu_800C38CC(CfgCtxConfig* c)
{
    short rect[4];
    CfgDlgConfig cfg;
    CfgBoxConfig b;
    cfg = menuHdrActive_800C2CD0;
    cfg.time_4 = GetTime30Hz_8002C64C();
    cfg.cursor_C = c->cursorPos_44;
    cfg.items_10 = (int)topMenuItems_800C4DDC;
    DrawMenuWindows_8002A5A4(&cfg);
    rect[0] = 0x7D;
    rect[1] = 0x12;
    rect[2] = 0x46;
    rect[3] = 0x12;
    b.frame_B = 1;
    b.x_0 = 0x84;
    b.col_8 = uiColor_8008B590;
    b.colors_A = 0;
    b.y_2 = 0x15;
    DrawUiTiySprt_8002C06C(&b, 0x4F, 0xE);
    DrawWindow_80042460(rect, &b.col_8, dword_8008D454 + 0x38, 0);
}

// Matched
void DrawAudioPage_800C39C4(CfgCtxConfig* c)
{
    short rect[4];
    CfgDlgConfig a;
    CfgDlgConfig b;
    CfgDlgConfig d;
    CfgDlgConfig e;
    CfgBoxConfig box;
    a = menuHdrActive_800C2CD0;
    b = menuHdrIdle_800C2CE8;
    d = menuHdrIdle_800C2CE8;
    e = menuHdrIdle_800C2CE8;
    a.time_4 = GetTime30Hz_8002C64C();
    a.cursor_C = c->cursorPos_44;
    a.items_10 = (int)audioPageItems_800C4E98;
    b.time_4 = GetTime30Hz_8002C64C();
    b.cursor_C = saveData_8008B570.settings_1C.bits.bgmVol_7 / 16;
    b.items_10 = (int)musicVolumeItems_800C5298;
    d.time_4 = GetTime30Hz_8002C64C();
    d.cursor_C = saveData_8008B570.settings_1C.bits.sfxVol_14 / 16;
    d.items_10 = (int)sfxVolumeItems_800C52BC;
    e.time_4 = GetTime30Hz_8002C64C();
    e.cursor_C = c->outputFormat_C;
    e.items_10 = (int)outputItems_800C52E0;
    ApplyBgmVolume_800309D8(&bgmSound_80091CE0);
    if (c->editing_38)
    {
        a.mode_0 = 4;
    }
    else
    {
        a.mode_0 = 2;
    }
    DrawMenuWindows_8002A5A4(&a);
    if (c->editing_38)
    {
        b.mode_0 = 4;
        d.mode_0 = 4;
        e.mode_0 = 4;
        switch (c->cursorPos_44)
        {
        case 0:
            b.mode_0 = 2;
            break;
        case 1:
            d.mode_0 = 2;
            break;
        case 2:
            e.mode_0 = 2;
            break;
        }
    }
    else
    {
        b.mode_0 = 4;
        d.mode_0 = 4;
        e.mode_0 = 4;
    }
    DrawMenuWindows_8002A5A4(&b);
    DrawMenuWindows_8002A5A4(&d);
    DrawMenuWindows_8002A5A4(&e);
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
    DrawWindow_80042460(rect, &box.col_8, dword_8008D454 + 0x38, 0);
}


void DrawSubtitlePage_800C3CA4(CfgCtxConfig* c)
{
    short rect[4];
    CfgDlgConfig a;
    CfgDlgConfig b1;
    CfgDlgConfig b2;
    CfgDlgConfig b3;
    CfgDlgConfig b4;
    CfgDlgConfig b5;
    CfgDlgConfig b6;
    CfgDlgConfig b7;
    CfgBoxConfig box;
    unsigned short** t;
    a = menuHdrActive_800C2CD0;
    b1 = menuHdrIdle_800C2CE8;
    b2 = menuHdrIdle_800C2CE8;
    b3 = menuHdrIdle_800C2CE8;
    b4 = menuHdrIdle_800C2CE8;
    b5 = menuHdrIdle_800C2CE8;
    b6 = menuHdrIdle_800C2CE8;
    b7 = menuHdrIdle_800C2CE8;
    a.time_4 = GetTime30Hz_8002C64C();
    a.cursor_C = c->cursorPos_44;
    t = subtitlePageItems_800C5474;
    a.items_10 = (int)t;
    b1.time_4 = GetTime30Hz_8002C64C();
    b1.cursor_C = c->displaySpeed_8;
    b1.items_10 = (int)displaySpeedItems_800C5574;
    b2.time_4 = GetTime30Hz_8002C64C();
    b2.cursor_C = (*(unsigned int*)&c->displaySpeed_8 & 0xFFFF00) != 0;
    b2.items_10 = (int)animSkipItems_800C55F8;
    b3.time_4 = GetTime30Hz_8002C64C();
    b3.cursor_C = c->speech_11;
    b3.items_10 = (int)speechItems_800C5674;
    b4.time_4 = GetTime30Hz_8002C64C();
    b4.cursor_C = c->magicEffects_B;
    b4.items_10 = (int)magicEffectsItems_800C56F0;
    b5.time_4 = GetTime30Hz_8002C64C();
    b5.cursor_C = c->captureEffects_10;
    b5.items_10 = (int)captureEffectsItems_800C576C;
    b6.time_4 = GetTime30Hz_8002C64C();
    b6.cursor_C = c->autoMessage_13;
    b6.items_10 = (int)autoMessageItems_800C57E8;
    b7.time_4 = GetTime30Hz_8002C64C();
    b7.cursor_C = c->subtitles_14;
    b7.items_10 = (int)subtitlesItems_800C5864;
    if (c->editing_38)
    {
        a.mode_0 = 4;
    }
    else
    {
        a.mode_0 = 2;
        if (c->subtitles_14 == 0)
        {
            *t[2] |= 2;
        }
        else
        {
            *t[2] &= ~2;
            *t[3] &= ~2;
            if (c->speech_11 != 0)
            {
                goto done;
            }
        }
        *t[3] |= 2;
    }
done:
    DrawMenuWindows_8002A5A4(&a);
    if (c->editing_38)
    {
        b1.mode_0 = 4;
        b2.mode_0 = 4;
        b3.mode_0 = 4;
        b4.mode_0 = 4;
        b5.mode_0 = 4;
        b6.mode_0 = 4;
        b7.mode_0 = 4;
        switch (c->cursorPos_44)
        {
        case 0:
            b1.mode_0 = 2;
            break;
        case 1:
            b2.mode_0 = 2;
            break;
        case 2:
            b3.mode_0 = 2;
            break;
        case 3:
            b6.mode_0 = 2;
            break;
        case 4:
            b7.mode_0 = 2;
            break;
        case 5:
            b4.mode_0 = 2;
            break;
        case 6:
            b5.mode_0 = 2;
            break;
        }
    }
    else
    {
        b1.mode_0 = 4;
        b2.mode_0 = 4;
        b3.mode_0 = 4;
        b4.mode_0 = 4;
        b5.mode_0 = 4;
        b6.mode_0 = 4;
        b7.mode_0 = 4;
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
    DrawWindow_80042460(rect, &box.col_8, dword_8008D454 + 0x38, 0);
}

#if 0
// Not matched: the original does not keep i*38 in a register across the loop body (uses fewer saved registers)
void DrawScreenColorPage_800C4180(CfgCtxConfig* c)
{
    short rect[4];
    CfgBoxConfig box1;
    short rect2[4];
    short rect3[4];
    CfgTailConfig tail;
    CfgBoxConfig box3;
    short i;
    rect[0] = 0x72;
    rect[1] = 0x12;
    rect[2] = 0x5C;
    rect[3] = 0x12;
    box1.frame_B = 1;
    box1.x_0 = 0x8C;
    box1.col_8 = uiColor_8008B590;
    box1.colors_A = 0;
    box1.y_2 = 0x14;
    DrawUiTiySprt_8002C06C(&box1, 0x2A, 0xE);
    box1.x_0 = 0x8C;
    box1.y_2 = 0x15;
    DrawWindow_80042460(rect, &box1.col_8, dword_8008D454 + 0x38, 0);
    for (i = 0; i < 4; i++)
    {
        unsigned int n = 0;
        rect2[0] = 0x52;
        rect2[1] = i * 38 + 0x2A;
        rect2[2] = 0x12;
        rect2[3] = 0x24;
        tail.colors_2 = 1;
        if (c->uiColor_F == i)
        {
            n = (unsigned int)(frameCount_8008D3FC * display_8008B4D8.vsyncsPerFrame_4) >> 1;
        }
        tail.col_0 = i;
        tail.frame_3 = 1;
        DrawWindow_80042460(rect2, &tail, dword_8008D454 + 0x38, n);
        rect3[0] = 0x66;
        rect3[1] = i * 38 + 0x2A;
        rect3[2] = 0x76;
        rect3[3] = 0x24;
        box3.col_8 = i;
        box3.colors_A = 0;
        box3.frame_B = 1;
        box3.x_0 = 0x74;
        box3.y_2 = i * 38 + 0x2C;
        DrawUiTiySprt_8002C06C(&box3, 0xCA, 0xE);
        box3.x_0 = rect3[0] + 0xE;
        box3.y_2 = rect3[1] + 6;
        DrawWindow_80042460(rect3, &box3.col_8, dword_8008D454 + 0x38, 0);
    }
}
#endif
INCLUDE_OVERLAY_ASM(config, DrawScreenColorPage_800C4180);

// Matched
void DrawVibrationPage_800C4390(CfgCtxConfig* c)
{
    short rect[4];
    CfgDlgConfig a;
    CfgDlgConfig b;
    CfgBoxConfig box;
    a = menuHdrIdle_800C2CE8;
    b = menuHdrIdle_800C2CE8;
    a.time_4 = GetTime30Hz_8002C64C();
    a.cursor_C = 0;
    a.items_10 = (int)vibrationLabelItems_800C58A8;
    b.time_4 = GetTime30Hz_8002C64C();
    b.cursor_C = c->vibration_12;
    b.items_10 = (int)vibrationItems_800C5920;
    if (c->editing_38)
    {
        a.mode_0 = 4;
    }
    else
    {
        a.mode_0 = 2;
    }
    DrawMenuWindows_8002A5A4(&a);
    if (c->editing_38)
    {
        b.mode_0 = 2;
    }
    else
    {
        b.mode_0 = 4;
    }
    DrawMenuWindows_8002A5A4(&b);
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
    DrawWindow_80042460(rect, &box.col_8, dword_8008D454 + 0x38, 0);
}

// Matched
void DrawConfigHelpText_800C450C(CfgCtxConfig* c)
{
    int p;
    short rect[4];
    short pos[2];
    short s = c->page_2;
    if (s >= 0)
    {
        if (s < 3)
        {
            p = pageHelpTexts_800C4CC0[s][c->cursorPos_44];
        }
        else if (s < 5)
        {
            p = *pageHelpTexts_800C4CC0[s];
        }
        else
        {
            p = 0;
        }
    }
    else
    {
        p = 0;
    }
    rect[0] = 10;
    rect[1] = 0xC2;
    rect[2] = 0x12C;
    rect[3] = 0x12;
    pos[0] = 0xE;
    pos[1] = 0xC5;
    DrawTextLinesWindow_8002AE38(&p, pos, 0xE, rect, 1);
}

// Matched
int IsConfigMenuActive_800C45D8(void)
{
    return configMenuActive_800C5944;
}

extern void MoveGridCursorP1_8003D630(CfgSpinConfig* p);
extern void ConfigMenuTask_800C2F70();

void EditConfigSettingTask_800C45E8(CfgTaskConfig* t, CfgCtxConfig* c)
{
    CfgSpinConfig v10;
    CfgSpinConfig v20;
    CfgSpinConfig v30;
    CfgSpinConfig v40;
    CfgSpinConfig v50;
    CfgSpinConfig v60;
    CfgSpinConfig v70;
    CfgSpinConfig v80;
    int v;
    DrawMenuBackground_8002BE10();
    DrawConfigPage_800C383C(c);
    DrawConfigHelpText_800C450C(c);
    DrawButtonHelpBar_8002B004(helpBar_800C592C, 0, 0xE);
    if (c->page_2 == 1)
    {
        switch (c->cursorPos_44)
        {
        case 0:
            v = saveData_8008B570.settings_1C.bits.bgmVol_7 / 16;
            v10.flags_0 = 0;
            v10.unused_4 = 0;
            v10.cols_8 = 8;
            v10.rows_A = 1;
            v10.pos_6 = v;
            MoveGridCursorP1_8003D630(&v10);
            if (v != v10.pos_6)
            {
                PlaySfx_80031494(0x7F);
            }
            v = v10.pos_6;
            saveData_8008B570.settings_1C.bits.bgmVol_7 = v * 16;
            break;
        case 1:
            v = saveData_8008B570.settings_1C.bits.sfxVol_14 / 16;
            v20.flags_0 = 0;
            v20.unused_4 = 0;
            v20.cols_8 = 8;
            v20.rows_A = 1;
            v20.pos_6 = v;
            MoveGridCursorP1_8003D630(&v20);
            if (v != v20.pos_6)
            {
                PlaySfx_80031494(0x7F);
            }
            v = v20.pos_6;
            saveData_8008B570.settings_1C.bits.sfxVol_14 = v * 16;
            break;
        case 2:
            v30.flags_0 = 0;
            v30.unused_4 = 0;
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
            v10.unused_4 = 0;
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
            v20.unused_4 = 0;
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
            v40.unused_4 = 0;
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
            v50.unused_4 = 0;
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
            v60.unused_4 = 0;
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
            v70.unused_4 = 0;
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
            v80.unused_4 = 0;
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
        v10.unused_4 = 0;
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
        t->next_8 = ConfigMenuTask_800C2F70;
        c->editing_38 = 0;
    }
    else if (IsCancelPressedP1_8003D41C(1))
    {
        saveData_8008B570.settings_1C.bits.bgmVol_7 = c->savedBgmVolume_15 * 16;
        saveData_8008B570.settings_1C.bits.sfxVol_14 = c->savedSfxVolume_16 * 16;
        LoadConfigSettings_800C3060(c);
        t->next_8 = ConfigMenuTask_800C2F70;
        c->editing_38 = 0;
    }
}
const char aOptionNotAvaila_800C2D40[] = "\202n\202\220\202\224\202\211\202\217\202\216\201@\202\216\202\217\202\224\201@\202\201\202\226\202\201\202\211\202\214\202\201\202\202\202\214\202\205\201@\202\227\202\210\202\211\202\214\202\205\201@\202r\202\220\202\205\202\205\202\203\202\210\201@\202\211\202\223\201@\202\223\202\205\202\224\201@\202\224\202\217\201@\202n\202e\202e\201D"; // Option not available while Speech is set to OFF.
const char aSetSpeechToONTo_800C2DA4[] = "\202r\202\205\202\224\201@\202r\202\220\202\205\202\205\202\203\202\210\201@\202\224\202\217\201@\202n\202m\201@\202\224\202\217\201@\202\205\202\216\202\201\202\202\202\214\202\205\201@\202\224\202\210\202\211\202\223\201@\202\217\202\220\202\224\202\211\202\217\202\216\201D"; // Set Speech to ON to enable this option.
const char aOptionNotAvaila_800C2DF4[] = "\202n\202\220\202\224\202\211\202\217\202\216\201@\202\216\202\217\202\224\201@\202\201\202\226\202\201\202\211\202\214\202\201\202\202\202\214\202\205\201@\202\227\202\210\202\211\202\214\202\205\201@\202r\202\225\202\202\202\224\202\211\202\224\202\214\202\205\202\223\201@\202\211\202\223\201@\202\223\202\205\202\224\201@\202\224\202\217\201@\202n\202e\202e\201D"; // Option not available while Subtitles is set to OFF.
const char aSetSubtitlesToO_800C2E5C[] = "\202r\202\205\202\224\201@\202r\202\225\202\202\202\224\202\211\202\224\202\214\202\205\202\223\201@\202\224\202\217\201@\202n\202m\201@\202\224\202\217\201@\202\205\202\216\202\201\202\202\202\214\202\205\201@\202\224\202\210\202\211\202\223\201@\202\217\202\220\202\224\202\211\202\217\202\216\201D"; // Set Subtitles to ON to enable this option.

// Matched
void ConfigNoticeTask_800C4B34(CfgTaskConfig* t, CfgCtxConfig* c)
{
    DrawMenuBackground_8002BE10();
    DrawConfigPage_800C383C(c);
    DrawOptionUnavailable_800C4BDC((short)c->notice_30);
    if (c->noticeTimer_34 >= 0x96 || IsConfirmPressedP1_8003D380(0) || IsCancelPressedP1_8003D41C(0))
    {
        PlaySfx_80031494(0x7D);
        t->next_8 = ConfigMenuTask_800C2F70;
        c->notice_30 = 0;
        c->noticeTimer_34 = 0;
    }
    else
    {
        c->noticeTimer_34++;
    }
}

// Matched
void DrawOptionUnavailable_800C4BDC(int n)
{
    short rect[4];
    short pos[2];
    char* p[2];
    if ((short)n == 2)
    {
        p[0] = aOptionNotAvaila_800C2D40;
        p[1] = aSetSpeechToONTo_800C2DA4;
    }
    else
    {
        p[0] = aOptionNotAvaila_800C2DF4;
        p[1] = aSetSubtitlesToO_800C2E5C;
    }
    rect[0] = 10;
    rect[1] = 0xC2;
    rect[2] = 0x12C;
    rect[3] = 0x22;
    pos[0] = 0xD;
    pos[1] = 0xC4;
    DrawTextLinesWindow_8002AE38(p, pos, 0xE, rect, 2);
}

int topMenuHelp_800C4C80[4] = { (int)aChangeAudioSett_800C2A54, (int)aChangeSubtitleS_800C2A20, (int)aSetScreenColor_800C29FC, (int)aVibrationSettin_800C29D4 };
int audioPageHelp_800C4C90[3] = { (int)aSetMusicVolume_800C2AE0, (int)aSetAudioEffects_800C2AAC, (int)aSetOutputFormat_800C2A84 };
int subtitlePageHelp_800C4C9C[7] = { (int)aSetDisplaySpeed_800C2C28, (int)aAllowAnimationS_800C2BFC, (int)aSelectVoiceAudi_800C2BC4, (int)aAutoMessage_800C2BA8, (int)aMessageWindowDi_800C2B78, (int)aSetMagicSpecial_800C2B40, (int)aSetCaptureSpeci_800C2B04 };
int screenColorPageHelp_800C4CB8[1] = { (int)aSetScreenColor_800C29FC };
int vibrationPageHelp_800C4CBC[1] = { (int)aVibrationSettin_800C29D4 };
int *pageHelpTexts_800C4CC0[5] = { topMenuHelp_800C4C80, audioPageHelp_800C4C90, subtitlePageHelp_800C4C9C, screenColorPageHelp_800C4CB8, vibrationPageHelp_800C4CBC };
Bytes8Config pageCursors_800C4CD4[5] = {
    { { 1, 0, 4, 0, 4 } },
    { { 1, 0, 3, 0, 3 } },
    { { 1, 0, 7, 0, 7 } },
    { { 1, 0, 4, 0, 4 } },
    { { 1, 0, 1, 0, 1 } },
};
int topItemAudio_800C4CFC[14] = {
    0x10008, 221, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x510072, 0x12005C, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int topItemSubtitle_800C4D34[14] = {
    0x10008, 232, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x650072, 0x12005C, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int topItemScreenColor_800C4D6C[14] = {
    0x10008, 42, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x790072, 0x12005C, 0x20000, 1,
    0, 0, 0, -1, -1, -1,
};
int topItemVibration_800C4DA4[14] = {
    0x10008, 171, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x8D0072, 0x12005C, 0x20000, 1,
    0, 0, 0, -1, -1, -1,
};
char topMenuItems_800C4DDC[20] = { 252, 76, 12, 128, 52, 77, 12, 128, 108, 77, 12, 128, 164, 77, 12, 128 };
int audioItemMusic_800C4DF0[14] = {
    0x10008, 126, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x530024, 0x12004F, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int audioItemSfx_800C4E28[14] = {
    0x10008, 168, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x670024, 0x12004F, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int audioItemOutput_800C4E60[14] = {
    0x10008, 146, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x7B0024, 0x12004F, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char audioPageItems_800C4E98[16] = { 240, 77, 12, 128, 40, 78, 12, 128, 96, 78, 12, 128 };
int musicVolume0_800C4EA8[14] = {
    0x10008, 125, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x530076, 0x120022, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int musicVolume1_800C4EE0[14] = {
    0x10008, 133, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x530099, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int musicVolume2_800C4F18[14] = {
    0x10008, 134, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x5300AC, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int musicVolume3_800C4F50[14] = {
    0x10008, 135, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x5300BF, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int musicVolume4_800C4F88[14] = {
    0x10008, 136, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x5300D2, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int musicVolume5_800C4FC0[14] = {
    0x10008, 137, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x5300E5, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int musicVolume6_800C4FF8[14] = {
    0x10008, 138, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x5300F8, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int musicVolume7_800C5030[14] = {
    0x10008, 139, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x53010B, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int sfxVolume0_800C5068[14] = {
    0x10008, 125, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x670076, 0x120022, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int sfxVolume1_800C50A0[14] = {
    0x10008, 133, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x670099, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int sfxVolume2_800C50D8[14] = {
    0x10008, 134, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x6700AC, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int sfxVolume3_800C5110[14] = {
    0x10008, 135, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x6700BF, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int sfxVolume4_800C5148[14] = {
    0x10008, 136, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x6700D2, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int sfxVolume5_800C5180[14] = {
    0x10008, 137, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x6700E5, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int sfxVolume6_800C51B8[14] = {
    0x10008, 138, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x6700F8, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int sfxVolume7_800C51F0[14] = {
    0x10008, 139, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x67010B, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int outputItem0_800C5228[14] = {
    0x10008, 188, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x7B0076, 0x120041, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int outputItem1_800C5260[14] = {
    0x10008, 124, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x7B00B9, 0x120041, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char musicVolumeItems_800C5298[36] = { 168, 78, 12, 128, 224, 78, 12, 128, 24, 79, 12, 128, 80, 79, 12, 128, 136, 79, 12, 128, 192, 79, 12, 128, 248, 79, 12, 128, 48, 80, 12, 128 };
char sfxVolumeItems_800C52BC[36] = { 104, 80, 12, 128, 160, 80, 12, 128, 216, 80, 12, 128, 16, 81, 12, 128, 72, 81, 12, 128, 128, 81, 12, 128, 184, 81, 12, 128, 240, 81, 12, 128 };
char outputItems_800C52E0[12] = { 40, 82, 12, 128, 96, 82, 12, 128 };
unsigned short subItemDisplaySpeed_800C52EC[28] = {
    8, 1, 200, 0, 0xD620, 0x8008, 0xD3F4, 0x8008,
    40, 41, 79, 18, 0, 3, 1, 0,
    0, 0, 0, 0, 0, 0, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};
unsigned short subItemAnimSkip_800C5324[28] = {
    8, 1, 4, 0, 0xD620, 0x8008, 0xD3F4, 0x8008,
    40, 72, 79, 18, 0, 3, 1, 0,
    0, 0, 0, 0, 0, 0, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};
unsigned short subItemSpeech_800C535C[28] = {
    8, 1, 201, 0, 0xD620, 0x8008, 0xD3F4, 0x8008,
    40, 92, 79, 18, 0, 3, 1, 0,
    0, 0, 0, 0, 0, 0, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};
unsigned short subItemMagicEffects_800C5394[28] = {
    8, 1, 50, 0, 0xD620, 0x8008, 0xD3F4, 0x8008,
    40, 152, 79, 18, 0, 2, 1, 0,
    0, 0, 0, 0, 0, 0, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};
unsigned short subItemCaptureEffects_800C53CC[28] = {
    8, 1, 229, 0, 0xD620, 0x8008, 0xD3F4, 0x8008,
    40, 172, 79, 18, 0, 2, 1, 0,
    0, 0, 0, 0, 0, 0, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};
unsigned short subItemAutoMessage_800C5404[28] = {
    8, 1, 89, 0, 0xD620, 0x8008, 0xD3F4, 0x8008,
    40, 112, 79, 18, 0, 2, 1, 0,
    0, 0, 0, 0, 0, 0, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};
unsigned short subItemSubtitles_800C543C[28] = {
    8, 1, 191, 0, 0xD620, 0x8008, 0xD3F4, 0x8008,
    40, 132, 79, 18, 0, 2, 1, 0,
    0, 0, 0, 0, 0, 0, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};
unsigned short *subtitlePageItems_800C5474[8] = { subItemDisplaySpeed_800C52EC, subItemAnimSkip_800C5324, subItemSpeech_800C535C, subItemAutoMessage_800C5404, subItemSubtitles_800C543C, subItemMagicEffects_800C5394, subItemCaptureEffects_800C53CC };
int displaySpeed0_800C5494[14] = {
    0x10008, 179, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x29007D, 0x120025, 0x40000, 1,
    0, 0, 0, -1, -1, -1,
};
int displaySpeed1_800C54CC[14] = {
    0x10008, 131, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x2900A3, 0x120025, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int displaySpeed2_800C5504[14] = {
    0x10008, 152, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x2900C9, 0x120025, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int displaySpeed3_800C553C[14] = {
    0x10008, 195, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x2900EF, 0x120025, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char displaySpeedItems_800C5574[20] = { 148, 84, 12, 128, 204, 84, 12, 128, 4, 85, 12, 128, 60, 85, 12, 128 };
int animSkip0_800C5588[14] = {
    0x10008, 44, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x48007D, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int animSkip1_800C55C0[14] = {
    0x10008, 45, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x4800C9, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char animSkipItems_800C55F8[12] = { 136, 85, 12, 128, 192, 85, 12, 128 };
int speech0_800C5604[14] = {
    0x10008, 175, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x5C007D, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int speech1_800C563C[14] = {
    0x10008, 176, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x5C00C9, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char speechItems_800C5674[12] = { 4, 86, 12, 128, 60, 86, 12, 128 };
int magicEffects0_800C5680[14] = {
    0x10008, 143, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x98007D, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int magicEffects1_800C56B8[14] = {
    0x10008, 144, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x9800C9, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char magicEffectsItems_800C56F0[12] = { 128, 86, 12, 128, 184, 86, 12, 128 };
int captureEffects0_800C56FC[14] = {
    0x10008, 143, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0xAC007D, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int captureEffects1_800C5734[14] = {
    0x10008, 144, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0xAC00C9, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char captureEffectsItems_800C576C[12] = { 252, 86, 12, 128, 52, 87, 12, 128 };
int autoMessage0_800C5778[14] = {
    0x10008, 90, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x70007D, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int autoMessage1_800C57B0[14] = {
    0x10008, 91, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x7000C9, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char autoMessageItems_800C57E8[12] = { 120, 87, 12, 128, 176, 87, 12, 128 };
int subtitles0_800C57F4[14] = {
    0x10008, 192, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x84007D, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int subtitles1_800C582C[14] = {
    0x10008, 193, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x8400C9, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char subtitlesItems_800C5864[12] = { 244, 87, 12, 128, 44, 88, 12, 128 };
int vibrationLabel_800C5870[14] = {
    0x10008, 171, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x6C0028, 0x12004F, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char vibrationLabelItems_800C58A8[8] = { 112, 88, 12, 128 };
int vibration0_800C58B0[14] = {
    0x10008, 172, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x6C007D, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int vibration1_800C58E8[14] = {
    0x10008, 173, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x6C00C9, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char vibrationItems_800C5920[12] = { 176, 88, 12, 128, 232, 88, 12, 128 };
char helpBar_800C592C[24] = { 16, 0, 0, 0, 92, 44, 12, 128, 167, 0, 0, 0, 80, 44, 12, 128, 255, 255, 255, 255 };
int configMenuActive_800C5944 = 0;
