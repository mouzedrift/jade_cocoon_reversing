// CONFIG.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"
#include "config.h"

typedef struct CfgCtxConfig
{
    char pad_0[2];
    short prev_2;
    short cur_4;
    unsigned short f6;
    unsigned char f8, f9, fa, fb, fc, fd, fe, ff, f10, f11, f12, f13, f14, f15, f16;
    char pad_17[0x30 - 0x17];
    int f30;
    short f34;
    short pad_36;
    int f38;
    Bytes8Config f3c;
    short f44;
    short f46;
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
extern void sub_800C4BDC(int n);
typedef struct CfgSpinConfig
{
    int f0;
    short f4, f6, f8, fA;
} CfgSpinConfig;

typedef struct CfgBoxConfig
{
    short x_0;
    short y_2;
    int pad_4;
    short col_8;
    char c_A;
    char c_B;
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
    char c_2;
    char c_3;
} CfgTailConfig;
extern int frameCount_8008D3FC;
extern void DrawMenuBackground_8002BE10();
extern void DrawButtonHelpBar_8002B004(void*, int, int);
extern void UpdateMenuCursor_8003D794(void*, int);
extern void sub_800C2F70();
extern void sub_800C3060(CfgCtxConfig*);
extern void sub_800C383C(CfgCtxConfig*);
extern void sub_800C450C(CfgCtxConfig*);
extern void sub_800C3540(CfgCtxConfig*);
extern void sub_800C378C(CfgCtxConfig*);
extern void sub_800C38CC(CfgCtxConfig*);
extern void sub_800C39C4(CfgCtxConfig*);
extern void sub_800C3CA4(CfgCtxConfig*);
extern void sub_800C4180(CfgCtxConfig*);
extern void sub_800C4390(CfgCtxConfig*);
extern void sub_800C45E8();
extern void sub_800C4B34(CfgTaskConfig*, CfgCtxConfig*);

int dword_800C29D0 SDATA = 36;
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
void sub_800C2EB4(void)
{
    CfgHolderConfig* h = dword_8008B4B8;
    CfgTaskConfig* t = &h->t_10;
    CfgCtxConfig* c = t->ctx_14;
    h->t_10.flags_0 = (h->t_10.flags_0 | 1) & 0xFFFF7FFF;
    DrawMenuBackground_8002BE10();
    c->cur_4 = 0;
    c->prev_2 = 0;
    c->f3c = dword_800C4CD4[5];
    c->f44 = 0;
    c->f46 = 0;
    c->f38 = 0;
    c->f30 = 0;
    c->f34 = 0;
    sub_800C3060(c);
    sub_800C383C(c);
    dword_800C5944 = 1;
    t->next_8 = sub_800C2F70;
}

#if 0
// Not matched: the original keeps a second copy of the context pointer in another register
void sub_800C2F70(CfgTaskConfig* t, CfgCtxConfig* d)
{
    short old;
    CfgCtxConfig* c;
    DrawMenuBackground_8002BE10();
    sub_800C383C(d);
    sub_800C450C(d);
    DrawButtonHelpBar_8002B004(dword_800C592C, 0, 0xE);
    old = d->f44;
    UpdateMenuCursor_8003D794(&d->f3c, 0);
    c = d;
    if (old != c->f44)
    {
        sub_800C3060(c);
    }
    if (c->f30 == 0)
    {
        sub_800C3540(c);
    }
    if (c->cur_4 != -1)
    {
        if (c->cur_4 != 5)
        {
            sub_800C378C(c);
            if (d->cur_4 != 5)
            {
                return;
            }
        }
    }
    else if (d->cur_4 != 5)
    {
        return;
    }
    dword_800C5944 = 0;
    t->flags_0 = (t->flags_0 & ~1) | 0x8000;
}

#endif
INCLUDE_OVERLAY_ASM(config, sub_800C2F70);

// Matched
void sub_800C3060(CfgCtxConfig* c)
{
    SaveData* s = &saveData_8008B570;
    c->f14 = ((unsigned char*)s)[0x1F] & 1;
    c->f8 = s->settings_1C.bits.a_0;
    c->f9 = s->settings_1C.bits.b_3;
    c->fa = s->settings_1C.bits.c_4;
    c->fb = s->settings_1C.bits.d_5;
    c->fc = s->settings_1C.bits.e_6;
    c->fd = s->settings_1C.bits.bgmVol_7 / 16;
    c->fe = s->settings_1C.bits.sfxVol_14 / 16;
    c->f15 = c->fd;
    c->f16 = c->fe;
    c->ff = s->uiColor_20.b;
    c->f10 = s->settings_1C.bits.h_21;
    c->f11 = s->settings_1C.bits.i_22;
    if (c->f14 == 0)
    {
        c->f11 = 1;
    }
    if (saveData_8008B570.field_0 & 0x40)
    {
        c->f12 = 0;
    }
    else
    {
        c->f12 = 1;
    }
    c->fa = c->f9;
    c->f13 = (settingsFlags_8008B58C.word >> 0x17) & 1;
    if (c->f14 == 0)
    {
        c->f13 = 1;
    }
    if (c->f11 == 0)
    {
        c->f13 = 0;
    }
}

void sub_800C31DC(CfgCtxConfig* c)
{
    switch (c->prev_2)
    {
    case 1:
        if (dword_800C5944 != 0)
        {
            switch (c->f44)
            {
            case 0:
                c->f15 = saveData_8008B570.settings_1C.bits.bgmVol_7 / 16;
                break;
            case 1:
                c->f16 = saveData_8008B570.settings_1C.bits.sfxVol_14 / 16;
                break;
            case 2:
                saveData_8008B570.settings_1C.bits.e_6 = c->fc;
                break;
            }
        }
        break;
    case 2:
        if (dword_800C5944 != 0)
        {
            switch (c->f44)
            {
            case 0:
                {
                SaveData* s = &saveData_8008B570;
                s->settings_1C.bits.a_0 = c->f8;
                }
                break;
            case 1:
                {
                SaveData* s = &saveData_8008B570;
                unsigned char t = c->f9;
                s->settings_1C.bits.b_3 = t;
                s->settings_1C.bits.c_4 = t;
                s->settings_1C.bits.c_4 = c->fa;
                }
                break;
            case 2:
                {
                SaveData* s = &saveData_8008B570;
                s->settings_1C.bits.i_22 = c->f11;
                if (s->settings_1C.bits.i_22 == 0)
                {
                    c->f13 = 0;
                    s->settings_1C.bits.j_23 = 0;
                }
                }
                break;
            case 3:
                {
                SaveData* s = &saveData_8008B570;
                s->settings_1C.bits.j_23 = c->f13;
                }
                break;
            case 4:
                {
                SaveData* s = &saveData_8008B570;
                s->settings_1C.bits.k_24 = c->f14;
                if (s->settings_1C.bits.k_24 == 0)
                {
                    c->f11 = 1;
                    s->settings_1C.bits.i_22 = 1;
                    c->f13 = 1;
                    s->settings_1C.bits.j_23 = 1;
                }
                }
                break;
            case 5:
                {
                SaveData* s = &saveData_8008B570;
                s->settings_1C.bits.d_5 = c->fb;
                }
                break;
            case 6:
                {
                SaveData* s = &saveData_8008B570;
                s->settings_1C.bits.h_21 = c->f10;
                }
                break;
            }
        }
        break;
    case 3:
        if (dword_800C5944 != 0)
        {
            uiColor_8008B590 = c->ff;
        }
        break;
    case 4:
        if (dword_800C5944 != 0)
        {
            if (c->f12 == 0)
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
INCLUDE_OVERLAY_ASM(config, dword_800C2C88);

void sub_800C3540(CfgCtxConfig* c)
{
    switch (c->prev_2)
    {
    case 0:
        if (dword_800C5944 != 0)
        {
            if (IsConfirmPressedP1_8003D380(1))
            {
                c->cur_4 = c->f44 + 1;
                c->f6 = c->f44;
            }
            else if (IsCancelPressedP1_8003D41C(1))
            {
                c->cur_4 = 5;
            }
        }
        break;
    case 1:
        if (dword_800C5944 != 0)
        {
            if (IsConfirmPressedP1_8003D380(1))
            {
                dword_8008B4B8->t_10.next_8 = sub_800C45E8;
                c->f38 = 1;
            }
            else if (IsCancelPressedP1_8003D41C(1))
            {
                sub_800C3060(c);
                c->cur_4 = 0;
                c->f44 = c->f6;
            }
        }
        break;
    case 2:
        if (dword_800C5944 != 0)
        {
            if (IsConfirmPressedP1_8003D380(0))
            {
                if (c->f14 == 0 && (unsigned short)(c->f44 - 2) < 2)
                {
                    dword_8008B4B8->t_10.next_8 = sub_800C4B34;
                    c->f30 = 1;
                    PlaySfx_80031494(0x7C);
                }
                else if (c->f11 == 0 && c->f44 == 3)
                {
                    dword_8008B4B8->t_10.next_8 = sub_800C4B34;
                    c->f30 = 2;
                    PlaySfx_80031494(0x7C);
                }
                else
                {
                    dword_8008B4B8->t_10.next_8 = sub_800C45E8;
                    c->f38 = 1;
                    PlaySfx_80031494(0x7E);
                }
            }
            else if (IsCancelPressedP1_8003D41C(1))
            {
                sub_800C3060(c);
                c->cur_4 = 0;
                c->f44 = c->f6;
            }
        }
        break;
    case 3:
        if (dword_800C5944 != 0)
        {
            c->ff = c->f44;
            if (IsConfirmPressedP1_8003D380(1))
            {
                sub_800C31DC(c);
            }
            else if (IsCancelPressedP1_8003D41C(1))
            {
                sub_800C3060(c);
                c->cur_4 = 0;
                c->f44 = c->f6;
            }
        }
        break;
    case 4:
        if (dword_800C5944 != 0)
        {
            if (IsConfirmPressedP1_8003D380(1))
            {
                dword_8008B4B8->t_10.next_8 = sub_800C45E8;
                c->f38 = 1;
            }
            else if (IsCancelPressedP1_8003D41C(1))
            {
                sub_800C3060(c);
                c->cur_4 = 0;
                c->f44 = c->f6;
            }
        }
        break;
    }
}
INCLUDE_OVERLAY_ASM(config, dword_800C2CA0);

void sub_800C378C(CfgCtxConfig* c)
{
    c->f3c = dword_800C4CD4[c->cur_4];
    switch (c->cur_4)
    {
    case 3:
        if (c->prev_2 == 0)
        {
            c->f44 = uiColor_8008B590;
            c->f46 = 0;
        }
        break;
    case 1:
    case 2:
    case 4:
        if (c->prev_2 == 0)
        {
            c->f44 = 0;
    case 0:
            c->f46 = 0;
        }
        break;
    }
    c->prev_2 = c->cur_4;
    c->cur_4 = -1;
}
INCLUDE_OVERLAY_ASM(config, dword_800C2CB8);

void sub_800C383C(CfgCtxConfig* c)
{
    switch (c->prev_2)
    {
    case 0:
        sub_800C38CC(c);
        break;
    case 1:
        sub_800C39C4(c);
        break;
    case 2:
        sub_800C3CA4(c);
        break;
    case 3:
        sub_800C4180(c);
        break;
    case 4:
        sub_800C4390(c);
        break;
    }
}
const CfgDlgConfig dword_800C2CD0 = { 2, 0, 8, 0, 0, 14 };
const CfgDlgConfig dword_800C2CE8 = { 0, 0, 8, 0, 0, 14 };
const int dword_800C2D00 = 0;

// Matched
void sub_800C38CC(CfgCtxConfig* c)
{
    short rect[4];
    CfgDlgConfig cfg;
    CfgBoxConfig b;
    cfg = dword_800C2CD0;
    cfg.f4 = GetTime30Hz_8002C64C();
    cfg.fC = c->f44;
    cfg.f10 = (int)dword_800C4DDC;
    DrawMenuWindows_8002A5A4(&cfg);
    rect[0] = 0x7D;
    rect[1] = 0x12;
    rect[2] = 0x46;
    rect[3] = 0x12;
    b.c_B = 1;
    b.x_0 = 0x84;
    b.col_8 = uiColor_8008B590;
    b.c_A = 0;
    b.y_2 = 0x15;
    DrawUiTiySprt_8002C06C(&b, 0x4F, 0xE);
    DrawWindow_80042460(rect, &b.col_8, dword_8008D454 + 0x38, 0);
}

// Matched
void sub_800C39C4(CfgCtxConfig* c)
{
    short rect[4];
    CfgDlgConfig a;
    CfgDlgConfig b;
    CfgDlgConfig d;
    CfgDlgConfig e;
    CfgBoxConfig box;
    a = dword_800C2CD0;
    b = dword_800C2CE8;
    d = dword_800C2CE8;
    e = dword_800C2CE8;
    a.f4 = GetTime30Hz_8002C64C();
    a.fC = c->f44;
    a.f10 = (int)dword_800C4E98;
    b.f4 = GetTime30Hz_8002C64C();
    b.fC = saveData_8008B570.settings_1C.bits.bgmVol_7 / 16;
    b.f10 = (int)dword_800C5298;
    d.f4 = GetTime30Hz_8002C64C();
    d.fC = saveData_8008B570.settings_1C.bits.sfxVol_14 / 16;
    d.f10 = (int)dword_800C52BC;
    e.f4 = GetTime30Hz_8002C64C();
    e.fC = c->fc;
    e.f10 = (int)dword_800C52E0;
    ApplyBgmVolume_800309D8(&bgmSound_80091CE0);
    if (c->f38)
    {
        a.f0 = 4;
    }
    else
    {
        a.f0 = 2;
    }
    DrawMenuWindows_8002A5A4(&a);
    if (c->f38)
    {
        b.f0 = 4;
        d.f0 = 4;
        e.f0 = 4;
        switch (c->f44)
        {
        case 0:
            b.f0 = 2;
            break;
        case 1:
            d.f0 = 2;
            break;
        case 2:
            e.f0 = 2;
            break;
        }
    }
    else
    {
        b.f0 = 4;
        d.f0 = 4;
        e.f0 = 4;
    }
    DrawMenuWindows_8002A5A4(&b);
    DrawMenuWindows_8002A5A4(&d);
    DrawMenuWindows_8002A5A4(&e);
    rect[0] = 0x72;
    rect[1] = 0x12;
    rect[2] = 0x5C;
    rect[3] = 0x12;
    box.c_B = 1;
    box.x_0 = 0x93;
    box.y_2 = 0x15;
    box.col_8 = uiColor_8008B590;
    box.c_A = 0;
    box.x_0 = 0x8B;
    DrawUiTiySprt_8002C06C(&box, 0xDD, 0xE);
    DrawWindow_80042460(rect, &box.col_8, dword_8008D454 + 0x38, 0);
}


void sub_800C3CA4(CfgCtxConfig* c)
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
    a = dword_800C2CD0;
    b1 = dword_800C2CE8;
    b2 = dword_800C2CE8;
    b3 = dword_800C2CE8;
    b4 = dword_800C2CE8;
    b5 = dword_800C2CE8;
    b6 = dword_800C2CE8;
    b7 = dword_800C2CE8;
    a.f4 = GetTime30Hz_8002C64C();
    a.fC = c->f44;
    t = dword_800C5474;
    a.f10 = (int)t;
    b1.f4 = GetTime30Hz_8002C64C();
    b1.fC = c->f8;
    b1.f10 = (int)dword_800C5574;
    b2.f4 = GetTime30Hz_8002C64C();
    b2.fC = (*(unsigned int*)&c->f8 & 0xFFFF00) != 0;
    b2.f10 = (int)dword_800C55F8;
    b3.f4 = GetTime30Hz_8002C64C();
    b3.fC = c->f11;
    b3.f10 = (int)dword_800C5674;
    b4.f4 = GetTime30Hz_8002C64C();
    b4.fC = c->fb;
    b4.f10 = (int)dword_800C56F0;
    b5.f4 = GetTime30Hz_8002C64C();
    b5.fC = c->f10;
    b5.f10 = (int)dword_800C576C;
    b6.f4 = GetTime30Hz_8002C64C();
    b6.fC = c->f13;
    b6.f10 = (int)dword_800C57E8;
    b7.f4 = GetTime30Hz_8002C64C();
    b7.fC = c->f14;
    b7.f10 = (int)dword_800C5864;
    if (c->f38)
    {
        a.f0 = 4;
    }
    else
    {
        a.f0 = 2;
        if (c->f14 == 0)
        {
            *t[2] |= 2;
        }
        else
        {
            *t[2] &= ~2;
            *t[3] &= ~2;
            if (c->f11 != 0)
            {
                goto done;
            }
        }
        *t[3] |= 2;
    }
done:
    DrawMenuWindows_8002A5A4(&a);
    if (c->f38)
    {
        b1.f0 = 4;
        b2.f0 = 4;
        b3.f0 = 4;
        b4.f0 = 4;
        b5.f0 = 4;
        b6.f0 = 4;
        b7.f0 = 4;
        switch (c->f44)
        {
        case 0:
            b1.f0 = 2;
            break;
        case 1:
            b2.f0 = 2;
            break;
        case 2:
            b3.f0 = 2;
            break;
        case 3:
            b6.f0 = 2;
            break;
        case 4:
            b7.f0 = 2;
            break;
        case 5:
            b4.f0 = 2;
            break;
        case 6:
            b5.f0 = 2;
            break;
        }
    }
    else
    {
        b1.f0 = 4;
        b2.f0 = 4;
        b3.f0 = 4;
        b4.f0 = 4;
        b5.f0 = 4;
        b6.f0 = 4;
        b7.f0 = 4;
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
    box.c_B = 1;
    box.x_0 = 0x78;
    box.col_8 = uiColor_8008B590;
    box.c_A = 0;
    box.y_2 = 0x15;
    DrawUiTiySprt_8002C06C(&box, 0xE8, 0xE);
    DrawWindow_80042460(rect, &box.col_8, dword_8008D454 + 0x38, 0);
}
INCLUDE_OVERLAY_ASM(config, dword_800C2D20);

#if 0
// Not matched: the original does not keep i*38 in a register across the loop body (uses fewer saved registers)
void sub_800C4180(CfgCtxConfig* c)
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
    box1.c_B = 1;
    box1.x_0 = 0x8C;
    box1.col_8 = uiColor_8008B590;
    box1.c_A = 0;
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
        tail.c_2 = 1;
        if (c->ff == i)
        {
            n = (unsigned int)(frameCount_8008D3FC * display_8008B4D8.vsyncsPerFrame_4) >> 1;
        }
        tail.col_0 = i;
        tail.c_3 = 1;
        DrawWindow_80042460(rect2, &tail, dword_8008D454 + 0x38, n);
        rect3[0] = 0x66;
        rect3[1] = i * 38 + 0x2A;
        rect3[2] = 0x76;
        rect3[3] = 0x24;
        box3.col_8 = i;
        box3.c_A = 0;
        box3.c_B = 1;
        box3.x_0 = 0x74;
        box3.y_2 = i * 38 + 0x2C;
        DrawUiTiySprt_8002C06C(&box3, 0xCA, 0xE);
        box3.x_0 = rect3[0] + 0xE;
        box3.y_2 = rect3[1] + 6;
        DrawWindow_80042460(rect3, &box3.col_8, dword_8008D454 + 0x38, 0);
    }
}
#endif
INCLUDE_OVERLAY_ASM(config, sub_800C4180);

// Matched
void sub_800C4390(CfgCtxConfig* c)
{
    short rect[4];
    CfgDlgConfig a;
    CfgDlgConfig b;
    CfgBoxConfig box;
    a = dword_800C2CE8;
    b = dword_800C2CE8;
    a.f4 = GetTime30Hz_8002C64C();
    a.fC = 0;
    a.f10 = (int)dword_800C58A8;
    b.f4 = GetTime30Hz_8002C64C();
    b.fC = c->f12;
    b.f10 = (int)dword_800C5920;
    if (c->f38)
    {
        a.f0 = 4;
    }
    else
    {
        a.f0 = 2;
    }
    DrawMenuWindows_8002A5A4(&a);
    if (c->f38)
    {
        b.f0 = 2;
    }
    else
    {
        b.f0 = 4;
    }
    DrawMenuWindows_8002A5A4(&b);
    rect[0] = 0x72;
    rect[1] = 0x12;
    rect[2] = 0x5C;
    rect[3] = 0x12;
    box.c_B = 1;
    box.x_0 = 0x85;
    box.col_8 = uiColor_8008B590;
    box.c_A = 0;
    box.y_2 = 0x15;
    DrawUiTiySprt_8002C06C(&box, 0xAB, 0xE);
    box.x_0 = 0x8C;
    box.y_2 = 0x15;
    DrawWindow_80042460(rect, &box.col_8, dword_8008D454 + 0x38, 0);
}

// Matched
void sub_800C450C(CfgCtxConfig* c)
{
    int p;
    short rect[4];
    short pos[2];
    short s = c->prev_2;
    if (s >= 0)
    {
        if (s < 3)
        {
            p = dword_800C4CC0[s][c->f44];
        }
        else if (s < 5)
        {
            p = *dword_800C4CC0[s];
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
int sub_800C45D8(void)
{
    return dword_800C5944;
}

extern void MoveGridCursorP1_8003D630(CfgSpinConfig* p);
extern void sub_800C2F70();

void sub_800C45E8(CfgTaskConfig* t, CfgCtxConfig* c)
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
    sub_800C383C(c);
    sub_800C450C(c);
    DrawButtonHelpBar_8002B004(dword_800C592C, 0, 0xE);
    if (c->prev_2 == 1)
    {
        switch (c->f44)
        {
        case 0:
            v = saveData_8008B570.settings_1C.bits.bgmVol_7 / 16;
            v10.f0 = 0;
            v10.f4 = 0;
            v10.f8 = 8;
            v10.fA = 1;
            v10.f6 = v;
            MoveGridCursorP1_8003D630(&v10);
            if (v != v10.f6)
            {
                PlaySfx_80031494(0x7F);
            }
            v = v10.f6;
            saveData_8008B570.settings_1C.bits.bgmVol_7 = v * 16;
            break;
        case 1:
            v = saveData_8008B570.settings_1C.bits.sfxVol_14 / 16;
            v20.f0 = 0;
            v20.f4 = 0;
            v20.f8 = 8;
            v20.fA = 1;
            v20.f6 = v;
            MoveGridCursorP1_8003D630(&v20);
            if (v != v20.f6)
            {
                PlaySfx_80031494(0x7F);
            }
            v = v20.f6;
            saveData_8008B570.settings_1C.bits.sfxVol_14 = v * 16;
            break;
        case 2:
            v30.f0 = 0;
            v30.f4 = 0;
            v30.f8 = 2;
            v30.fA = 1;
            v30.f6 = c->fc;
            MoveGridCursorP1_8003D630(&v30);
            if (c->fc != v30.f6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->fc = v30.f6;
            break;
        }
    }
    else if (c->prev_2 == 2)
    {
        switch (c->f44)
        {
        case 0:
            {
            v10.f0 = 0;
            v10.f4 = 0;
            v10.f8 = 4;
            v10.fA = 1;
            v10.f6 = c->f8;
            MoveGridCursorP1_8003D630(&v10);
            if (c->f8 != v10.f6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->f8 = v10.f6;
            }
            break;
        case 1:
            {
            v20.f0 = 0;
            v20.f4 = 0;
            v20.f8 = 2;
            v20.fA = 1;
            v20.f6 = c->f9;
            MoveGridCursorP1_8003D630(&v20);
            if (c->f9 != v20.f6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->fa = c->f9 = v20.f6;
            }
            break;
        case 2:
            {
            v40.f0 = 0;
            v40.f4 = 0;
            v40.f8 = 2;
            v40.fA = 1;
            v40.f6 = c->f11;
            MoveGridCursorP1_8003D630(&v40);
            if (c->f11 != v40.f6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->f11 = v40.f6;
            }
            break;
        case 3:
            {
            v50.f0 = 0;
            v50.f4 = 0;
            v50.f8 = 2;
            v50.fA = 1;
            v50.f6 = c->f13;
            MoveGridCursorP1_8003D630(&v50);
            if (c->f13 != v50.f6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->f13 = v50.f6;
            }
            break;
        case 4:
            {
            v60.f0 = 0;
            v60.f4 = 0;
            v60.f8 = 2;
            v60.fA = 1;
            v60.f6 = c->f14;
            MoveGridCursorP1_8003D630(&v60);
            if (c->f14 != v60.f6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->f14 = v60.f6;
            }
            break;
        case 5:
            {
            v70.f0 = 0;
            v70.f4 = 0;
            v70.f8 = 2;
            v70.fA = 1;
            v70.f6 = c->fb;
            MoveGridCursorP1_8003D630(&v70);
            if (c->fb != v70.f6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->fb = v70.f6;
            }
            break;
        case 6:
            {
            v80.f0 = 0;
            v80.f4 = 0;
            v80.f8 = 2;
            v80.fA = 1;
            v80.f6 = c->f10;
            MoveGridCursorP1_8003D630(&v80);
            if (c->f10 != v80.f6)
            {
                PlaySfx_80031494(0x7F);
            }
            c->f10 = v80.f6;
            }
            break;
        }
    }
    else if (c->prev_2 == 4)
    {
        v10.f0 = 0;
        v10.f4 = 0;
        v10.f8 = 2;
        v10.fA = 1;
        v10.f6 = c->f12;
        MoveGridCursorP1_8003D630(&v10);
        if (c->f12 != v10.f6)
        {
            PlaySfx_80031494(0x7F);
        }
        c->f12 = v10.f6;
    }
    if (IsConfirmPressedP1_8003D380(1))
    {
        sub_800C31DC(c);
        t->next_8 = sub_800C2F70;
        c->f38 = 0;
    }
    else if (IsCancelPressedP1_8003D41C(1))
    {
        saveData_8008B570.settings_1C.bits.bgmVol_7 = c->f15 * 16;
        saveData_8008B570.settings_1C.bits.sfxVol_14 = c->f16 * 16;
        sub_800C3060(c);
        t->next_8 = sub_800C2F70;
        c->f38 = 0;
    }
}
const char aOptionNotAvaila_800C2D40[] = "\202n\202\220\202\224\202\211\202\217\202\216\201@\202\216\202\217\202\224\201@\202\201\202\226\202\201\202\211\202\214\202\201\202\202\202\214\202\205\201@\202\227\202\210\202\211\202\214\202\205\201@\202r\202\220\202\205\202\205\202\203\202\210\201@\202\211\202\223\201@\202\223\202\205\202\224\201@\202\224\202\217\201@\202n\202e\202e\201D"; // Option not available while Speech is set to OFF.
const char aSetSpeechToONTo_800C2DA4[] = "\202r\202\205\202\224\201@\202r\202\220\202\205\202\205\202\203\202\210\201@\202\224\202\217\201@\202n\202m\201@\202\224\202\217\201@\202\205\202\216\202\201\202\202\202\214\202\205\201@\202\224\202\210\202\211\202\223\201@\202\217\202\220\202\224\202\211\202\217\202\216\201D"; // Set Speech to ON to enable this option.
const char aOptionNotAvaila_800C2DF4[] = "\202n\202\220\202\224\202\211\202\217\202\216\201@\202\216\202\217\202\224\201@\202\201\202\226\202\201\202\211\202\214\202\201\202\202\202\214\202\205\201@\202\227\202\210\202\211\202\214\202\205\201@\202r\202\225\202\202\202\224\202\211\202\224\202\214\202\205\202\223\201@\202\211\202\223\201@\202\223\202\205\202\224\201@\202\224\202\217\201@\202n\202e\202e\201D"; // Option not available while Subtitles is set to OFF.
const char aSetSubtitlesToO_800C2E5C[] = "\202r\202\205\202\224\201@\202r\202\225\202\202\202\224\202\211\202\224\202\214\202\205\202\223\201@\202\224\202\217\201@\202n\202m\201@\202\224\202\217\201@\202\205\202\216\202\201\202\202\202\214\202\205\201@\202\224\202\210\202\211\202\223\201@\202\217\202\220\202\224\202\211\202\217\202\216\201D"; // Set Subtitles to ON to enable this option.

// Matched
void sub_800C4B34(CfgTaskConfig* t, CfgCtxConfig* c)
{
    DrawMenuBackground_8002BE10();
    sub_800C383C(c);
    sub_800C4BDC((short)c->f30);
    if (c->f34 >= 0x96 || IsConfirmPressedP1_8003D380(0) || IsCancelPressedP1_8003D41C(0))
    {
        PlaySfx_80031494(0x7D);
        t->next_8 = sub_800C2F70;
        c->f30 = 0;
        c->f34 = 0;
    }
    else
    {
        c->f34++;
    }
}

// Matched
void sub_800C4BDC(int n)
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

int dword_800C4C80[4] = { (int)aChangeAudioSett_800C2A54, (int)aChangeSubtitleS_800C2A20, (int)aSetScreenColor_800C29FC, (int)aVibrationSettin_800C29D4 };
int dword_800C4C90[3] = { (int)aSetMusicVolume_800C2AE0, (int)aSetAudioEffects_800C2AAC, (int)aSetOutputFormat_800C2A84 };
int dword_800C4C9C[7] = { (int)aSetDisplaySpeed_800C2C28, (int)aAllowAnimationS_800C2BFC, (int)aSelectVoiceAudi_800C2BC4, (int)aAutoMessage_800C2BA8, (int)aMessageWindowDi_800C2B78, (int)aSetMagicSpecial_800C2B40, (int)aSetCaptureSpeci_800C2B04 };
int dword_800C4CB8[1] = { (int)aSetScreenColor_800C29FC };
int dword_800C4CBC[1] = { (int)aVibrationSettin_800C29D4 };
int *dword_800C4CC0[5] = { dword_800C4C80, dword_800C4C90, dword_800C4C9C, dword_800C4CB8, dword_800C4CBC };
Bytes8Config dword_800C4CD4[5] = {
    { { 1, 0, 4, 0, 4 } },
    { { 1, 0, 3, 0, 3 } },
    { { 1, 0, 7, 0, 7 } },
    { { 1, 0, 4, 0, 4 } },
    { { 1, 0, 1, 0, 1 } },
};
int dword_800C4CFC[14] = {
    0x10008, 221, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x510072, 0x12005C, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C4D34[14] = {
    0x10008, 232, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x650072, 0x12005C, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C4D6C[14] = {
    0x10008, 42, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x790072, 0x12005C, 0x20000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C4DA4[14] = {
    0x10008, 171, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x8D0072, 0x12005C, 0x20000, 1,
    0, 0, 0, -1, -1, -1,
};
char dword_800C4DDC[20] = { 252, 76, 12, 128, 52, 77, 12, 128, 108, 77, 12, 128, 164, 77, 12, 128 };
int dword_800C4DF0[14] = {
    0x10008, 126, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x530024, 0x12004F, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C4E28[14] = {
    0x10008, 168, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x670024, 0x12004F, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C4E60[14] = {
    0x10008, 146, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x7B0024, 0x12004F, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char dword_800C4E98[16] = { 240, 77, 12, 128, 40, 78, 12, 128, 96, 78, 12, 128 };
int dword_800C4EA8[14] = {
    0x10008, 125, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x530076, 0x120022, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C4EE0[14] = {
    0x10008, 133, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x530099, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C4F18[14] = {
    0x10008, 134, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x5300AC, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C4F50[14] = {
    0x10008, 135, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x5300BF, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C4F88[14] = {
    0x10008, 136, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x5300D2, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C4FC0[14] = {
    0x10008, 137, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x5300E5, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C4FF8[14] = {
    0x10008, 138, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x5300F8, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C5030[14] = {
    0x10008, 139, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x53010B, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C5068[14] = {
    0x10008, 125, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x670076, 0x120022, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C50A0[14] = {
    0x10008, 133, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x670099, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C50D8[14] = {
    0x10008, 134, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x6700AC, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C5110[14] = {
    0x10008, 135, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x6700BF, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C5148[14] = {
    0x10008, 136, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x6700D2, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C5180[14] = {
    0x10008, 137, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x6700E5, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C51B8[14] = {
    0x10008, 138, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x6700F8, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C51F0[14] = {
    0x10008, 139, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x67010B, 0x120012, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C5228[14] = {
    0x10008, 188, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x7B0076, 0x120041, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C5260[14] = {
    0x10008, 124, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x7B00B9, 0x120041, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char dword_800C5298[36] = { 168, 78, 12, 128, 224, 78, 12, 128, 24, 79, 12, 128, 80, 79, 12, 128, 136, 79, 12, 128, 192, 79, 12, 128, 248, 79, 12, 128, 48, 80, 12, 128 };
char dword_800C52BC[36] = { 104, 80, 12, 128, 160, 80, 12, 128, 216, 80, 12, 128, 16, 81, 12, 128, 72, 81, 12, 128, 128, 81, 12, 128, 184, 81, 12, 128, 240, 81, 12, 128 };
char dword_800C52E0[12] = { 40, 82, 12, 128, 96, 82, 12, 128 };
unsigned short dword_800C52EC[28] = {
    8, 1, 200, 0, 0xD620, 0x8008, 0xD3F4, 0x8008,
    40, 41, 79, 18, 0, 3, 1, 0,
    0, 0, 0, 0, 0, 0, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};
unsigned short dword_800C5324[28] = {
    8, 1, 4, 0, 0xD620, 0x8008, 0xD3F4, 0x8008,
    40, 72, 79, 18, 0, 3, 1, 0,
    0, 0, 0, 0, 0, 0, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};
unsigned short dword_800C535C[28] = {
    8, 1, 201, 0, 0xD620, 0x8008, 0xD3F4, 0x8008,
    40, 92, 79, 18, 0, 3, 1, 0,
    0, 0, 0, 0, 0, 0, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};
unsigned short dword_800C5394[28] = {
    8, 1, 50, 0, 0xD620, 0x8008, 0xD3F4, 0x8008,
    40, 152, 79, 18, 0, 2, 1, 0,
    0, 0, 0, 0, 0, 0, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};
unsigned short dword_800C53CC[28] = {
    8, 1, 229, 0, 0xD620, 0x8008, 0xD3F4, 0x8008,
    40, 172, 79, 18, 0, 2, 1, 0,
    0, 0, 0, 0, 0, 0, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};
unsigned short dword_800C5404[28] = {
    8, 1, 89, 0, 0xD620, 0x8008, 0xD3F4, 0x8008,
    40, 112, 79, 18, 0, 2, 1, 0,
    0, 0, 0, 0, 0, 0, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};
unsigned short dword_800C543C[28] = {
    8, 1, 191, 0, 0xD620, 0x8008, 0xD3F4, 0x8008,
    40, 132, 79, 18, 0, 2, 1, 0,
    0, 0, 0, 0, 0, 0, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};
unsigned short *dword_800C5474[8] = { dword_800C52EC, dword_800C5324, dword_800C535C, dword_800C5404, dword_800C543C, dword_800C5394, dword_800C53CC };
int dword_800C5494[14] = {
    0x10008, 179, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x29007D, 0x120025, 0x40000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C54CC[14] = {
    0x10008, 131, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x2900A3, 0x120025, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C5504[14] = {
    0x10008, 152, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x2900C9, 0x120025, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C553C[14] = {
    0x10008, 195, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x2900EF, 0x120025, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char dword_800C5574[20] = { 148, 84, 12, 128, 204, 84, 12, 128, 4, 85, 12, 128, 60, 85, 12, 128 };
int dword_800C5588[14] = {
    0x10008, 44, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x48007D, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C55C0[14] = {
    0x10008, 45, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x4800C9, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char dword_800C55F8[12] = { 136, 85, 12, 128, 192, 85, 12, 128 };
int dword_800C5604[14] = {
    0x10008, 175, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x5C007D, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C563C[14] = {
    0x10008, 176, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x5C00C9, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char dword_800C5674[12] = { 4, 86, 12, 128, 60, 86, 12, 128 };
int dword_800C5680[14] = {
    0x10008, 143, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x98007D, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C56B8[14] = {
    0x10008, 144, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x9800C9, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char dword_800C56F0[12] = { 128, 86, 12, 128, 184, 86, 12, 128 };
int dword_800C56FC[14] = {
    0x10008, 143, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0xAC007D, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C5734[14] = {
    0x10008, 144, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0xAC00C9, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char dword_800C576C[12] = { 252, 86, 12, 128, 52, 87, 12, 128 };
int dword_800C5778[14] = {
    0x10008, 90, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x70007D, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C57B0[14] = {
    0x10008, 91, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x7000C9, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char dword_800C57E8[12] = { 120, 87, 12, 128, 176, 87, 12, 128 };
int dword_800C57F4[14] = {
    0x10008, 192, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x84007D, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C582C[14] = {
    0x10008, 193, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x8400C9, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char dword_800C5864[12] = { 244, 87, 12, 128, 44, 88, 12, 128 };
int dword_800C5870[14] = {
    0x10008, 171, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x6C0028, 0x12004F, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char dword_800C58A8[8] = { 112, 88, 12, 128 };
int dword_800C58B0[14] = {
    0x10008, 172, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x6C007D, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int dword_800C58E8[14] = {
    0x10008, 173, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x6C00C9, 0x12004B, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
char dword_800C5920[12] = { 176, 88, 12, 128, 232, 88, 12, 128 };
char dword_800C592C[24] = { 16, 0, 0, 0, 92, 44, 12, 128, 167, 0, 0, 0, 80, 44, 12, 128, 255, 255, 255, 255 };
int dword_800C5944 = 0;
