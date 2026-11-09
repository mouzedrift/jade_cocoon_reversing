#include "common.h"
#include "funcs.h"
#include "sdk.h"
#include "globals.h"
#include "sound.h"
#include "data_decls.h"
#include "party_window.h"
#include "effect_data.h"
#include "font.h"
#include "util.h"
#include "unit_query.h"
#include "movie.h"
#include "pad_text.h"
#include "ui_sprites.h"
#include "menu_draw.h"
#include "unit_gauges.h"

const NameBuf emptyNameBuf_80074434 = { { 0xFFFF } };


void DrawPulsingWindow_8002F6F8(RECT* rect, PulseState* st, int unused)
{
    unsigned char col[4];
    UiWindowDesc desc;
    short pulse = 20;
    if (st->pulse_8)
    {
        (*st->time_0)++;
        if (*st->time_0 == 40)
        {
            *st->time_0 = 0;
        }
        pulse = *st->time_0;
        if (pulse > 20)
        {
            pulse = 40 - pulse;
        }
    }
    col[0] = col[1] = col[2] = pulse * 8;
    if (!st->on_4)
    {
        col[0] = col[1] = col[2] = 0xA0;
    }
    desc.colorSet_8 = 1;
    desc.rect_0 = rect;
    desc.time_4 = pulse;
    desc.ot_A = 0xF;
    DrawUiWindow_8002A384(&desc);
}

extern unsigned char statIcons_80082EBC[];
void DrawLevantStats_8002F7D0(unsigned short* pos, short ot)
{
    unsigned short loc[2];
    unsigned char stats[0x18];
    short i;
    CalcEquippedStats_80033624(stats, &saveData_8008B570.levantStatus_7C8);
    for (i = 0; i < 5; i++)
    {
        loc[0] = pos[0] + 6;
        loc[1] = pos[1] + levantStatRowY_80082F04[i] + 1;
        DrawUiTiySprt_8002C06C(loc, statIcons_80082EBC[i], ot);
        loc[0] = pos[0] + 0x45;
        loc[1] = pos[1] + levantStatRowY_80082F04[i] + 2;
        DrawLargeNumber_8002C100(loc, stats[i], ot);
    }
}
void DrawPartySlotWindow_8002F8E4(UnitStatus* unit, PartySlotWindow* win)
{
    unsigned short loc[2];
    RECT buf;
    UiWindowDesc desc;
    int time;
    int highlight;
    loc[0] = partyWindowRects_80082E90[win->partySize_2 - 1][win->slot_C].x;
    loc[1] = 0x72;
    DrawUnitStatusExp_8002ECE0(unit, loc, win->slot_C, win->ot_6);
    time = 0;
    highlight = time < win->highlight_10;
    if (win->cursor_4 == win->slot_C)
    {
        time = win->time_8;
    }
    InterpolateWindowRect_8004196C(&buf, &partyWindowRects_80082E90[win->partySize_2 - 1][win->slot_C], win->open_0, 8, 0);
    AddDrawAreaPrim_8003326C(&buf, &pOT_8008D454[win->ot_6]);
    desc.colorSet_8 = highlight;
    desc.rect_0 = &buf;
    desc.time_4 = time;
    desc.ot_A = win->ot_6;
    DrawUiWindow_8002A384(&desc);
    AddClipDrawAreaPrim_80033308(&pOT_8008D454[win->ot_6]);
}
short GetPartyWindowX_8002FA0C(short partySize, short slot)
{
    short x = 0;
    int i;
    if (partySize > 0)
    {
        i = partySize - 1;
        if (i < 3 && slot < 3)
        {
            x = partyWindowRects_80082E90[i][slot].x;
        }
    }
    return x;
}
short GetLevantLevel_8002FA70(void)
{
    return GetLevel_80033514(GetLevantStatus_80033ABC(&saveData_8008B570));
}
void DrawSmallText_8002FAA0(int align, unsigned short* pos, unsigned char* text, int ot)
{
    unsigned short loc[2];
    NameBuf buf = emptyNameBuf_80074434;
    int offset;
    CopyPlayerName_8003F860(text, buf.s);
    DecodeText_8003F748(1, buf.s);
    UppercaseSjisName_8003F89C(buf.s);
    if (align == 1)
    {
        offset = (short)MeasureTextWidthFont1_8003E6B0((const char*)buf.s); // built against a short-returning prototype
    }
    else if (align == 2)
    {
        offset = (short)MeasureTextWidthFont1_8003E6B0((const char*)buf.s) / 2;
    }
    else
    {
        offset = 0;
    }
    loc[0] = pos[0] - offset;
    loc[1] = pos[1];
    DrawText_8003E91C(1, (const char*)&buf, loc, ot);
}
void DrawLargeText_8002FBD8(int align, unsigned short* pos, unsigned char* text, int ot)
{
    unsigned short loc[2];
    NameBuf buf = emptyNameBuf_80074434;
    int offset;
    CopyPlayerName_8003F860(text, buf.s);
    DecodeText_8003F748(1, buf.s);
    if (align == 1)
    {
        offset = (short)MeasureTextWidth_8003E4C8((const char*)buf.s); // built against a short-returning prototype
    }
    else
    {
        offset = 0;
    }
    loc[0] = pos[0] - offset;
    loc[1] = pos[1];
    DrawText_8003E91C(2, (const char*)&buf, loc, ot);
}
char* GetRankName_8002FCD8(int idx)
{
    if (idx >= 9)
    {
        return (char*)developerRankName_80082EE4;
    }
    return (char*)rankNames_80082EC4[idx];
}
