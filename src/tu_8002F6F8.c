#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "STDLIB.H"
#include "STDIO.H"
#include "LIBPAD.H"
#include "LIBSND.H"
#include "LIBMCX.H"
#include "LIBPRESS.H"
#include "LIBETC.H"
#include "LIBMCRD.H"
#include "sound.h"
#include "data_decls.h"
#include "tu_8002F6F8.h"
#include "tu_80014954.h"

const NameBuf emptyNameBuf_80074434 = { { 0xFFFF } };


typedef struct
{
    int field_0;
    int field_4;
    short field_8;
    short field_A;
} struct_F6F8;
extern void DrawUiWindow_8002A384(struct_F6F8* p);
// Matched
void DrawPulsingWindow_8002F6F8(int rect, int* st)
{
    unsigned char col[4];
    struct_F6F8 s;
    short pulse = 20;
    if (st[2])
    {
        (*(short*)st[0])++;
        if (*(short*)st[0] == 40)
        {
            *(short*)st[0] = 0;
        }
        pulse = *(short*)st[0];
        if (pulse > 20)
        {
            pulse = 40 - pulse;
        }
    }
    col[0] = col[1] = col[2] = pulse * 8;
    if (!st[1])
    {
        col[0] = col[1] = col[2] = 0xA0;
    }
    s.field_8 = 1;
    s.field_0 = rect;
    s.field_4 = pulse;
    s.field_A = 0xF;
    DrawUiWindow_8002A384(&s);
}

extern unsigned char statIcons_80082EBC[];
extern void DrawUiTiySprt_8002C06C(void* p, int a1, int a2);
extern void DrawLargeNumber_8002C100(unsigned short* pos, int v, int ot);
// Matched
void DrawLevantStats_8002F7D0(unsigned short* pos, short ot)
{
    unsigned short loc[2];
    unsigned char stats[0x18];
    short i;
    CalcEquippedStats_80033624(stats, &levantStatus_8008BD38);
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
typedef struct
{
    short field_0;
    short field_2;
    short field_4;
    short field_6;
    int field_8;
    short field_C;
    short pad_E;
    unsigned int field_10;
} struct_F8E4;
extern void DrawUnitStatusExp_8002ECE0(int a0, unsigned short* pos, int a2, short ot);
extern void InterpolateWindowRect_8004196C(void* a0, RECT* a1, int a2, int a3, int a4);
extern void AddDrawAreaPrim_8003326C(void* a, unsigned long* ot);
extern void AddClipDrawAreaPrim_80033308(unsigned long* ot);
// Matched
void DrawPartySlotWindow_8002F8E4(int unit, struct_F8E4* p)
{
    unsigned short loc[2];
    char buf[8];
    struct_F6F8 s;
    int v;
    int flag;
    loc[0] = partyWindowRects_80082E90[p->field_2 - 1][p->field_C].x;
    loc[1] = 0x72;
    DrawUnitStatusExp_8002ECE0(unit, loc, p->field_C, p->field_6);
    v = 0;
    flag = v < p->field_10;
    if (p->field_4 == p->field_C)
    {
        v = p->field_8;
    }
    InterpolateWindowRect_8004196C(buf, &partyWindowRects_80082E90[p->field_2 - 1][p->field_C], p->field_0, 8, 0);
    AddDrawAreaPrim_8003326C(buf, &pOT_8008D454[p->field_6]);
    s.field_8 = flag;
    s.field_0 = (int)buf;
    s.field_4 = v;
    s.field_A = p->field_6;
    DrawUiWindow_8002A384(&s);
    AddClipDrawAreaPrim_80033308(&pOT_8008D454[p->field_6]);
}
// Matched
short GetPartyWindowX_8002FA0C(short partySize, short slot)
{
    short r = 0;
    int i;
    if (partySize > 0)
    {
        i = partySize - 1;
        if (i < 3 && slot < 3)
        {
            r = partyWindowRects_80082E90[i][slot].x;
        }
    }
    return r;
}
// Matched
short GetLevantLevel_8002FA70(void)
{
    return GetLevel_80033514(GetLevantStatus_80033ABC(&saveData_8008B570));
}
extern void DecodeText_8003F748(int a, NameBuf* b);
extern short MeasureTextWidth_8003E4C8(NameBuf* b);
extern void DrawText_8003E91C(int mode, NameBuf* a, unsigned short* b, int c);
extern void UppercaseSjisName_8003F89C(NameBuf* b);
extern short MeasureTextWidthFont1_8003E6B0(NameBuf* b);
// Matched
void DrawSmallText_8002FAA0(int align, unsigned short* pos, unsigned char* text, int ot)
{
    unsigned short loc[2];
    NameBuf buf = emptyNameBuf_80074434;
    int w;
    CopyPlayerName_8003F860(text, buf.s);
    DecodeText_8003F748(1, &buf);
    UppercaseSjisName_8003F89C(&buf);
    if (align == 1)
    {
        w = MeasureTextWidthFont1_8003E6B0(&buf);
    }
    else if (align == 2)
    {
        w = MeasureTextWidthFont1_8003E6B0(&buf) / 2;
    }
    else
    {
        w = 0;
    }
    loc[0] = pos[0] - w;
    loc[1] = pos[1];
    DrawText_8003E91C(1, &buf, loc, ot);
}
// Matched
void DrawLargeText_8002FBD8(int align, unsigned short* pos, unsigned char* text, int ot)
{
    unsigned short loc[2];
    NameBuf buf = emptyNameBuf_80074434;
    int w;
    CopyPlayerName_8003F860(text, buf.s);
    DecodeText_8003F748(1, &buf);
    if (align == 1)
    {
        w = MeasureTextWidth_8003E4C8(&buf);
    }
    else
    {
        w = 0;
    }
    loc[0] = pos[0] - w;
    loc[1] = pos[1];
    DrawText_8003E91C(2, &buf, loc, ot);
}
// Matched
char* GetRankName_8002FCD8(int idx)
{
    if (idx >= 9)
    {
        return developerRankName_80082EE4;
    }
    return rankNames_80082EC4[idx];
}
