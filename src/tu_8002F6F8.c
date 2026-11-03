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

INCLUDE_DATA(dword_8007442C);
INCLUDE_DATA(dword_80074430);
INCLUDE_DATA(dword_80074434);


typedef struct
{
    int field_0;
    int field_4;
    short field_8;
    short field_A;
} struct_F6F8;
extern void DrawUiWindow_8002A384(struct_F6F8* p);
// Matched
void sub_8002F6F8(int a0, int* st)
{
    unsigned char col[4];
    struct_F6F8 s;
    short v = 20;
    if (st[2])
    {
        (*(short*)st[0])++;
        if (*(short*)st[0] == 40)
        {
            *(short*)st[0] = 0;
        }
        v = *(short*)st[0];
        if (v > 20)
        {
            v = 40 - v;
        }
    }
    col[0] = col[1] = col[2] = v * 8;
    if (!st[1])
    {
        col[0] = col[1] = col[2] = 0xA0;
    }
    s.field_8 = 1;
    s.field_0 = a0;
    s.field_4 = v;
    s.field_A = 0xF;
    DrawUiWindow_8002A384(&s);
}
extern unsigned char levantStatus_8008BD38[];
extern unsigned char dword_80082F04[];
extern unsigned char dword_80082EBC[];
extern void DrawUiTiySprt_8002C06C(void* p, int a1, int a2);
extern void DrawLargeNumber_8002C100(unsigned short* pos, int v, int ot);
// Matched
void sub_8002F7D0(unsigned short* pos, short ot)
{
    unsigned short loc[2];
    unsigned char vals[0x18];
    short i;
    CalcEquippedStats_80033624(vals, (int)levantStatus_8008BD38);
    for (i = 0; i < 5; i++)
    {
        loc[0] = pos[0] + 6;
        loc[1] = pos[1] + dword_80082F04[i] + 1;
        DrawUiTiySprt_8002C06C(loc, dword_80082EBC[i], ot);
        loc[0] = pos[0] + 0x45;
        loc[1] = pos[1] + dword_80082F04[i] + 2;
        DrawLargeNumber_8002C100(loc, vals[i], ot);
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
extern RECT* off_80082E90[];
extern void sub_8002ECE0(int a0, unsigned short* pos, int a2, short ot);
extern void InterpolateWindowRect_8004196C(void* a0, RECT* a1, int a2, int a3, int a4);
extern void AddDrawAreaPrim_8003326C(void* a, unsigned long* ot);
extern void AddClipDrawAreaPrim_80033308(unsigned long* ot);
// Matched
void sub_8002F8E4(int a0, struct_F8E4* p)
{
    unsigned short loc[2];
    char buf[8];
    struct_F6F8 s;
    int v;
    int flag;
    loc[0] = off_80082E90[p->field_2 - 1][p->field_C].x;
    loc[1] = 0x72;
    sub_8002ECE0(a0, loc, p->field_C, p->field_6);
    v = 0;
    flag = v < p->field_10;
    if (p->field_4 == p->field_C)
    {
        v = p->field_8;
    }
    InterpolateWindowRect_8004196C(buf, &off_80082E90[p->field_2 - 1][p->field_C], p->field_0, 8, 0);
    AddDrawAreaPrim_8003326C(buf, &pOT_8008D454[p->field_6]);
    s.field_8 = flag;
    s.field_0 = (int)buf;
    s.field_4 = v;
    s.field_A = p->field_6;
    DrawUiWindow_8002A384(&s);
    AddClipDrawAreaPrim_80033308(&pOT_8008D454[p->field_6]);
}
// Matched
short sub_8002FA0C(short a, short b)
{
    short r = 0;
    int i;
    if (a > 0)
    {
        i = a - 1;
        if (i < 3 && b < 3)
        {
            r = off_80082E90[i][b].x;
        }
    }
    return r;
}
// Matched
short sub_8002FA70(void)
{
    return sub_80033514((Minion*)GetLevantStatus_80033ABC(&saveData_8008B570));
}
typedef struct
{
    unsigned short s[11];
} NameBuf;
extern NameBuf dword_80074434;
extern void DecodeText_8003F748(int a, NameBuf* b);
extern short MeasureTextWidth_8003E4C8(NameBuf* b);
extern void DrawText_8003E91C(int mode, NameBuf* a, unsigned short* b, int c);
extern void sub_8003F89C(NameBuf* b);
extern short MeasureTextWidthFont1_8003E6B0(NameBuf* b);
// Matched
void sub_8002FAA0(int a0, unsigned short* pos, unsigned char* name, int a3)
{
    unsigned short loc[2];
    NameBuf buf = dword_80074434;
    int w;
    CopyPlayerName_8003F860(name, buf.s);
    DecodeText_8003F748(1, &buf);
    sub_8003F89C(&buf);
    if (a0 == 1)
    {
        w = MeasureTextWidthFont1_8003E6B0(&buf);
    }
    else if (a0 == 2)
    {
        w = MeasureTextWidthFont1_8003E6B0(&buf) / 2;
    }
    else
    {
        w = 0;
    }
    loc[0] = pos[0] - w;
    loc[1] = pos[1];
    DrawText_8003E91C(1, &buf, loc, a3);
}
// Matched
void DrawLargeText_8002FBD8(int a0, unsigned short* pos, unsigned char* name, int a3)
{
    unsigned short loc[2];
    NameBuf buf = dword_80074434;
    int w;
    CopyPlayerName_8003F860(name, buf.s);
    DecodeText_8003F748(1, &buf);
    if (a0 == 1)
    {
        w = MeasureTextWidth_8003E4C8(&buf);
    }
    else
    {
        w = 0;
    }
    loc[0] = pos[0] - w;
    loc[1] = pos[1];
    DrawText_8003E91C(2, &buf, loc, a3);
}
extern char* rankNames_80082EC4[];
extern char* off_80082EE4;
// Matched
char* GetRankName_8002FCD8(int idx)
{
    if (idx >= 9)
    {
        return off_80082EE4;
    }
    return rankNames_80082EC4[idx];
}
