// TITLE.BIN - title screen, loaded at 0x800A05A0
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"


INCLUDE_OVERLAY_ASM(title, dword_800A05A0);

typedef struct TitleTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} TitleTask;

typedef struct TitleCtxA
{
    char pad_0[0x5C];
    int field_5C;
    int field_60;
    int field_64;
    int field_68;
    int field_6C;
    SPRT* sprts_70;      // from LoadTiy_80028E74
    DR_TPAGE* tpages_74; // one per sprite
} TitleCtxA;

extern int dword_800A280C;
extern int dword_800A2810;
extern void sub_800A093C();
// Matched
void sub_800A08C8(TitleTask* t, TitleCtxA* c)
{
    RECT r;
    dword_800A280C = 0x36;
    dword_800A2810 = 0x18;
    c->field_64 = 0x1E;
    c->field_5C = 0;
    c->field_68 = 0;
    c->field_60 = 0x18;
    c->field_6C = 0;
    r.x = 0x20;
    r.y = 0x20;
    r.w = display_8008B4D8.field_C_w - 0x20;
    r.h = display_8008B4D8.field_E_h - 0x20;
    t->next_8 = sub_800A093C;
}


extern void sub_800A09C0();
// Matched
void sub_800A093C(TitleTask* t, TitleCtxA* c)
{
    void* buf;
    if (GetFileRequestCount_8003BC34() == 0)
    {
        c->sprts_70 = 0;
        c->tpages_74 = 0;
        buf = DATA_GetFileBuffer_8003CAA0(0x39);
        LoadTiy_80028E74(&c->sprts_70, 0, &c->tpages_74, buf, 1);
        free3_8003FC6C(buf);
        t->next_8 = sub_800A09C0;
    }
}


extern void sub_800A0A1C();
// Matched
void sub_800A09C0(TitleTask* t)
{
    int r;
    if (saveData_8008B570.field_0 & 0x80)
    {
        r = PlayMovie_80040EB4(8);
    }
    else
    {
        r = PlayMovie_80040EB4(6);
    }
    if (r)
    {
        LoadUiTiy_8002BF74();
        t->next_8 = sub_800A0A1C;
    }
}


extern int dword_800A2808;
extern unsigned short padPressed_8009194C;
extern void sub_800A0A70();
// Matched
void sub_800A0A1C(TitleTask* t)
{
    if (uiTiyLoaded_8008B4E8)
    {
        padPressed_8009194C = 0;
        dword_800A2808 = LoadOverlay_80020BF8(1, 0x11);
        t->next_8 = sub_800A0A70;
    }
}


extern int dword_800A2718;
extern void StartNameEntry_800B6E4C(void* a0, int a1);
extern void EncodeName_8003F7C8(void* a0, void* a1);
extern void sub_800A0AE8();
// Matched
void sub_800A0A70(TitleTask* t)
{
    if (GetFileRequestStatus_8003BE30(dword_800A2808) == 0)
    {
        if (!(saveData_8008B570.field_0 & 0x80))
        {
            EncodeName_8003F7C8(&dword_800A2718, saveData_8008B570.levantStatus_7C8.name_10);
        }
        StartNameEntry_800B6E4C(saveData_8008B570.levantStatus_7C8.name_10, 0);
        t->next_8 = sub_800A0AE8;
    }
}


extern void sub_800A0D18();
extern int IsNameEntryActive_800B6FC8(void);
extern void sub_800A0C28();
// Matched
void sub_800A0AE8(TitleTask* t, TitleCtxA* c)
{
    if (c->field_6C == 0)
    {
        c->field_5C++;
        if (c->field_60 == c->field_5C)
        {
            c->field_6C = 1;
        }
    }
    else if (c->field_68 < 0x18)
    {
        c->field_68++;
    }
    else
    {
        c->field_68 = 0;
        c->field_6C = 0;
        c->field_60 += c->field_64;
        if (c->field_64 == dword_800A280C - dword_800A2810)
        {
            c->field_64 = dword_800A2810;
        }
        else
        {
            c->field_64 = dword_800A280C - dword_800A2810;
        }
    }
    sub_800A0D18(c->sprts_70, c->tpages_74, 0, c);
    if (IsNameEntryActive_800B6FC8() == 0)
    {
        FreeActiveOverlay_8002C014();
        t->next_8 = sub_800A0C28;
    }
}


extern void sub_800A1AFC();
// Matched
void sub_800A0BCC(TitleTask* t, TitleCtxA* c)
{
    if (--c->field_68 <= 0)
    {
        FreeSound_80030D00((int)&bgmSound_80091CE0);
        sub_800A1AFC(t, 0xC);
        t->flags_0 = (t->flags_0 & ~1) | 0x8000;
    }
}


extern void sub_800A0BCC();
extern void SsSepSetDecrescendo(short, short, short, long);
#if 0
// Not matched: register allocation / scheduling differs
void sub_800A0C28(TitleTask* t, TitleCtxA* c)
{
    int r;
    SoundStruct* ss;
    if (saveData_8008B570.field_0 & 0x80)
    {
        r = PlayMovie_80040EB4(9);
        saveData_8008B570.field_0 &= ~0x80;
    }
    else
    {
        r = PlayMovie_80040EB4(7);
    }
    if (r)
    {
        if (c->sprts_70)
        {
            free3_8003FC6C(c->sprts_70);
            c->sprts_70 = 0;
        }
        if (c->tpages_74)
        {
            free3_8003FC6C(c->tpages_74);
            c->tpages_74 = 0;
        }
        c->field_68 = 0x3C;
        t->next_8 = sub_800A0BCC;
        ss = &bgmSound_80091CE0;
        if (ss->field_4_seq_num >= 0)
        {
            SsSepSetDecrescendo(*(short*)&ss->field_C_sep_access_num, ss->field_4_seq_num, 0x7F, 0x78);
            ss->field_4_seq_num = -1;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(title, sub_800A0C28);

typedef struct TitleStr4
{
    char c[4];
} TitleStr4;

extern void PulseColor_80033394(void* a0, void* a1, void* a2, int a3, int a4, int a5);
extern unsigned long* pOT_8008D3EC;
extern int dword_800A05A0;
#if 0
// Not matched: register allocation / scheduling differs
void sub_800A0D18(SPRT* p, DR_TPAGE* q, int mode, TitleCtxA* c)
{
    int y = 0;
    short i = 0;
    int end;
    char zero[4];
    TitleStr4 s4;

    if (mode == 0)
    {
        i = 0;
    }
    else if (mode == 1)
    {
        i = 2;
    }
    if (mode != 1)
    {
        end = i + 2;
        for (; i < end; i++)
        {
            p[i].x0 = ((i % 2) * 5) << 5;
            p[i].y0 = y;
            AddPrimCopy_80040298(pOT_8008D3EC, &p[i], 5);
            AddPrimCopy_80040298(pOT_8008D3EC, &q[i], 2);
        }
    }
    else
    {
        memset(zero, 0, 4);
        y = 0x17;
        i = (short)i;
        s4 = *(TitleStr4*)((char*)&dword_800A05A0 + 4);
        p[i].x0 = 0x6F;
        p[i].y0 = y;
        PulseColor_80033394(&p[i].r0, zero, &s4, c->field_5C, dword_800A280C, dword_800A2810);
        SetSemiTrans(&p[i], 1);
        AddPrimCopy_80040298(pOT_8008D3EC, &p[i], 5);
        AddPrimCopy_80040298(pOT_8008D3EC, &q[i], 2);
    }
}
#endif
INCLUDE_OVERLAY_ASM(title, sub_800A0D18);

extern void SetFadeMode_8001C19C(int a0, int a1);
extern void PlayMusicSeq_80031260(void* a0, int a1, int a2);
extern int dword_800A27C0;
extern int dword_800A2818;
// Matched
int sub_800A0EF0(void)
{
    SetFadeMode_8001C19C(3, 0x20);
    drawEnvRed_8008D448[0] = 0;
    drawEnvRed_8008D448[1] = 0;
    drawEnvRed_8008D448[2] = 0;
    LoadSound_80030A84(0x1B, &bgmSound_80091CE0);
    PlayMusicSeq_80031260(&bgmSound_80091CE0, 0x1B, 1);
    DrawIntroMovie_8001AF64(&dword_800A27C0);
    FreeSound_80030D00((int)&bgmSound_80091CE0);
    return dword_800A2818;
}


typedef struct TitleCtxB
{
    int field_0;
    int field_4;
    int field_8;
    SPRT* sprts_C;       // from LoadTiy_80028E74
    int field_10;
    DR_TPAGE* tpages_14; // one per sprite
    char pad_18[4];
    short field_1C[4];
    short field_24;
    short field_26;
} TitleCtxB;

extern unsigned int dword_800A2814;
extern void sub_800A2650();
extern void sub_800A1B74();
extern void sub_800A1070();
// Matched
void sub_800A0F6C(TitleTask* t, TitleCtxB* c)
{
    void* buf;
    if (unknownFlags_8008D678 & 0x20000000)
    {
        word_8008B558[1] = 4;
        sub_800A2650();
        saveData_8008B570.field_0 |= 0x80;
        sub_800A1B74(t);
    }
    else
    {
        c->field_1C[0] = 1;
        c->field_1C[1] = 4;
        c->field_1C[2] = 4;
        c->field_1C[3] = 2;
        c->field_4 = 0;
        c->field_8 = 0;
        c->field_24 = (unsigned short)word_8008B558[1];
        dword_800A2814 = 0;
        c->field_26 = 0;
        c->sprts_C = 0;
        c->tpages_14 = 0;
        buf = DATA_GetFileBuffer_8003CAA0(0x36);
        LoadTiy_80028E74(&c->sprts_C, 0, &c->tpages_14, buf, 1);
        free3_8003FC6C(buf);
        (t->next_8 = sub_800A1070)(t, c);
    }
}


extern void sub_800A1174();
extern void sub_800A1310();
// Matched
void sub_800A1070(TitleTask* t, TitleCtxB* c)
{
    switch ((unsigned short)word_8008B558[0])
    {
    case 0:
        t->next_8 = sub_800A1174;
        break;
    case 1:
        c->field_0 = 0;
        t->next_8 = sub_800A1310;
        break;
    }
    t->next_8(t, c);
}


// Matched
void sub_800A10D0(TitleTask* t, TitleCtxB* c)
{
    TitleCtxB* d = c;
    word_8008B558[1] = c->field_24;
    if (unknownFlags_8008D678 & 0x20000000)
    {
        word_8008B558[1] = 4;
        unknownFlags_8008D678 &= ~0x20000000;
    }
    if (c->sprts_C)
    {
        free3_8003FC6C(c->sprts_C);
        c->sprts_C = 0;
    }
    if (d->tpages_14)
    {
        free3_8003FC6C(d->tpages_14);
        d->tpages_14 = 0;
    }
}


typedef struct TitleSmall
{
    short a;
    char b;
    char c;
} TitleSmall;

extern void DrawWindow_80042460(void* a0, void* a1, void* a2, unsigned int a3);
extern void sub_800A1F98();
extern void sub_800A1AC0();
extern void sub_8004E2C8(int a0);
#define TITLE_TIMEOUT(t, c) \
    if (++dword_800A2814 >= 0x1771) \
    { \
        (c)->field_0 = 0; \
        if (bgmSound_80091CE0.field_4_seq_num >= 0) \
        { \
            SsSepSetDecrescendo(*(short*)&bgmSound_80091CE0.field_C_sep_access_num, bgmSound_80091CE0.field_4_seq_num, 0x7F, 0x78); \
            bgmSound_80091CE0.field_4_seq_num = -1; \
        } \
        SetFadeMode_8001C19C(0, 0x20); \
        SetFadeMode_8001C19C(1, 0x20); \
        (t)->next_8 = sub_800A1AC0; \
    }
void sub_800A1174(TitleTask* t, TitleCtxB* c)
{
    TitleSmall s;
    RECT r;
    TitleCtxB* d = c;
    r.x = 0x4D;
    r.y = 0xA3;
    r.w = 0xA6;
    r.h = 0x12;
    s.b = 1;
    s.c = 1;
    s.a = 4;
    c->sprts_C[2].x0 = 0x54;
    c->sprts_C[2].y0 = 0xA7;
    AddPrimCopy_80040298(pOT_8008D454 + 14, &c->sprts_C[2], 5);
    AddPrimCopy_80040298(pOT_8008D454 + 14, &c->tpages_14[2], 2);
    DrawWindow_80042460(&r, &s, pOT_8008D454 + 14, (unsigned int)frameCount_8008D3FC >> 1);
    sub_800A1F98(c->sprts_C, c->tpages_14, c);
    if (padPressed_8009194C & 0x800)
    {
        PlaySfx_80031494(0x7E);
        srand(gnFrame_8008D610);
        c->field_0 = 0;
        t->next_8 = sub_800A1310;
        dword_800A2814 = 0;
    }
    TITLE_TIMEOUT(t, d)
}

extern void sub_800A1760();
extern unsigned short padRepeat_800918CC;
extern void sub_800A14A8();
extern void UpdateMenuCursor_8003D794(void* a0, int a1);
extern void CheckMemCards_8003BB1C(void);
extern void sub_800BB5DC(void);
extern void (*off_800A27E8[])();
// Matched
void sub_800A1310(TitleTask* t, TitleCtxB* c)
{
    sub_800A1F98(c->sprts_C, c->tpages_14, c);
    UpdateMenuCursor_8003D794(c->field_1C, 0);
    if (padRepeat_800918CC & 0x5000)
    {
        c->field_0 = 0;
        dword_800A2814 = 0;
    }
    sub_800A1760(c, c->field_24, c->field_0);
    c->field_0 = c->field_0 + 1;
    if (IsConfirmPressedP1_8003D380(1))
    {
        dword_800A2814 = 0;
        off_800A27E8[c->field_24](t, c);
        if ((unsigned short)c->field_24 < 2)
        {
            CheckMemCards_8003BB1C();
            if (c->field_24 == 0)
            {
                LoadOverlay_80020BF8(2, 0x10);
                sub_800BB5DC();
                t->next_8 = sub_800A14A8;
            }
        }
    }
    else if (IsCancelPressedP1_8003D41C(1))
    {
        dword_800A2814 = 0;
        t->next_8 = sub_800A1070;
    }
    TITLE_TIMEOUT(t, c)
}


extern void sub_800A158C();
extern void sub_800A166C();
extern void sub_800A1728();
extern void sub_800BB9F4(int a0);
extern void sub_800BC9DC(int a0, int* a1, int* a2);
extern void sub_800BAFB0(int a0);
extern int sub_800BAE2C(void);
extern int sub_800BAE3C(void);
// Matched
void sub_800A14A8(TitleTask* t)
{
    int i;
    int a;
    int b;
    b = 0;
    a = 0;
    t->next_8 = sub_800A158C;
    for (i = 0; i < 2; i++)
    {
        sub_800BB9F4(i << 4);
        sub_800BC9DC(0, &a, &b);
        if (b != 0)
        {
            if (b < 0)
            {
                continue;
            }
            if (b >= 5)
            {
                continue;
            }
            if (b < 3)
            {
                continue;
            }
        }
        {
            sub_800BAFB0(i);
            if (sub_800BAE2C() || sub_800BAE3C())
            {
                t->next_8 = sub_800A1728;
                return;
            }
            else
            {
                t->next_8 = sub_800A166C;
            }
        }
    }
}


extern void sub_800BB64C(void);
extern char str_800A05A8[];
extern char str_800A05BC[];
extern char str_800A0604[];
extern char str_800A0640[];
extern void DrawText_8003E91C(int mode, void* str, void* pos, int c);
// Matched
void sub_800A158C(TitleTask* t)
{
    RECT r0;
    RECT r1;
    RECT r2;
    RECT r3;
    sub_800BB64C();
    r0.x = 0x10;
    r0.y = 0x5A;
    DrawText_8003E91C(2, str_800A05A8, &r0, 0);
    r1.x = 0x10;
    r1.y = 0x6A;
    DrawText_8003E91C(2, str_800A05BC, &r1, 0);
    r2.x = 0x10;
    r2.y = 0x7A;
    DrawText_8003E91C(2, str_800A0604, &r2, 0);
    r3.x = 0x10;
    r3.y = 0x8A;
    DrawText_8003E91C(2, str_800A0640, &r3, 0);
    if (IsConfirmPressedP1_8003D380(1))
    {
        t->next_8 = sub_800A1310;
        sub_800A1B74(t);
    }
}


typedef TitleTask TitleTaskM;
typedef struct
{
    short x, y, w, h;
} TitleRectM;
// a menu window item of DrawMenuWindows_8002A5A4 (MenuItem_1C in tu_8002CE28.c)
typedef struct TitleMenuItem
{
    unsigned short flags_0;
    short pad_2;
    int f4;
    void* f8;
    void* fC;
    short x_10;
    short y_12;
    char pad_14[8];
} TitleMenuItem;
typedef struct
{
    TitleMenuItem items[2];
} TitleBlk38M;
extern char dword_800A05A8[];
extern char dword_800A0658[];
extern char dword_800A069C[];
extern void DrawText_8003E91C(int mode, void* buf, void* rect, int c);
extern void sub_800A1B74(TitleTaskM* t);

// Matched
void sub_800A166C(TitleTaskM* t)
{
    TitleRectM r1, r2, r3;
    sub_800BB64C();
    r1.x = 0x10;
    r1.y = 0x5A;
    DrawText_8003E91C(2, dword_800A05A8, &r1, 0);
    r2.x = 0x10;
    r2.y = 0x6A;
    DrawText_8003E91C(2, dword_800A0658, &r2, 0);
    r3.x = 0x10;
    r3.y = 0x7A;
    DrawText_8003E91C(2, dword_800A069C, &r3, 0);
    if (IsConfirmPressedP1_8003D380(1))
    {
        t->next_8 = sub_800A1310;
        sub_800A1B74(t);
    }
}

// Matched
void sub_800A1728(TitleTaskM* t)
{
    sub_800BB64C();
    t->next_8 = sub_800A1310;
    sub_800A1B74(t);
}

extern void sub_800A1780(TitleCtxB* c, int x);

// Matched
void sub_800A1760(TitleCtxB* p, int x, int y)
{
    sub_800A1780(p, x);
}

// struct_A5A4 in tu_8002CE28.c
typedef struct
{
    int f0, f4, f8, fC;
    TitleBlk38M** windows_10;
    int f14;
} TitleCfgM;
extern TitleBlk38M dword_800A06D8, dword_800A0710, dword_800A0748, dword_800A0780;
extern TitleBlk38M dword_800A07B8, dword_800A07F0, dword_800A0828, dword_800A0860;
extern TitleCfgM dword_800A0898;
extern void DrawMenuWindows_8002A5A4(TitleCfgM* cfg);

// Matched
void sub_800A1780(TitleCtxB* t, int x)
{
    TitleBlk38M b0, b1, b2, b3, b4, b5, b6, b7;
    TitleBlk38M* ptrs[5];
    TitleCfgM cfg;
    b0 = dword_800A06D8;
    b1 = dword_800A0710;
    b2 = dword_800A0748;
    b3 = dword_800A0780;
    b4 = dword_800A07B8;
    b5 = dword_800A07F0;
    b6 = dword_800A0828;
    b7 = dword_800A0860;
    memset(ptrs, 0, sizeof(ptrs));
    cfg = dword_800A0898;
    b0.items[0].f8 = &t->sprts_C;
    b0.items[0].fC = &t->tpages_14;
    b1.items[0].f8 = &t->sprts_C;
    b1.items[0].fC = &t->tpages_14;
    b2.items[0].f8 = &t->sprts_C;
    b2.items[0].fC = &t->tpages_14;
    b3.items[0].f8 = &t->sprts_C;
    b3.items[0].fC = &t->tpages_14;
    ptrs[0] = &b0;
    ptrs[1] = &b1;
    ptrs[2] = &b2;
    ptrs[3] = &b3;
    cfg.f4 = GetTime30Hz_8002C64C();
    cfg.fC = x;
    cfg.windows_10 = ptrs;
    DrawMenuWindows_8002A5A4(&cfg);
}


// Matched
void sub_800A1AC0(TitleTaskM* t, int* cnt)
{
    if (++*cnt >= 0x5B)
    {
        sub_800A1AFC(t, 5);
    }
}

// Matched
void sub_800A1AFC(TitleTaskM* t, int a)
{
    SoundStruct* s = &bgmSound_80091CE0;
    dword_800A2818 = a;
    if (s->field_4_seq_num >= 0)
    {
        SsSepSetDecrescendo((short)s->field_C_sep_access_num, s->field_4_seq_num, 0x7F, 0x78);
        s->field_4_seq_num = -1;
    }
    bStopDrawingMovie_8008D45C = 1;
    t->flags_0 &= ~1;
}

extern EventNode* dword_8008D638;

// Matched
void sub_800A1B74(TitleTaskM* t)
{
    EventEntry* e;
    t->flags_0 &= ~1;
    e = AllocEventEntry_80043AF8(dword_8008D638);
    if (e)
    {
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
    }
}

extern void sub_800A211C(void);
extern void sub_800A2214(void);
extern void sub_800A2450(void);
extern void sub_800A242C(void);
extern unsigned short word_8008B55A;

// Matched
void sub_800A1BCC(void)
{
    sub_800A211C();
    sub_800A2214();
    sub_800A2450();
    if (word_8008B55A == 1)
    {
        sub_800A242C();
    }
}

extern int dword_8008BD80;
extern void sub_800B7674(int a, int b);
extern void sub_800A1CC0(TitleTaskM* t);

// Matched
void sub_800A1C18(TitleTaskM* t)
{
    word_8008B55A = 1;
    LoadOverlay_80020BF8(2, 0x10);
    SetDisplayMode_80040658(1);
    dword_8008BD80 = -2;
    sub_800B7674(1, 0);
    t->next_8 = sub_800A1CC0;
}

extern void sub_800A2650(void);

// Matched
void sub_800A1C7C(TitleTaskM* t)
{
    word_8008B55A = 4;
    sub_800A1BCC();
    sub_800A2650();
    sub_800A1AFC(t, 0xC);
}

extern int sub_800B793C(void);
extern int sub_800B7914(void);

// Matched
void sub_800A1CC0(TitleTaskM* t)
{
    if (!sub_800B793C())
    {
        if (sub_800B7914() == 1)
        {
            if (saveData_8008B570.field_0 & 0x80)
            {
                word_8008B55A = 4;
                sub_800A2650();
                saveData_8008B570.field_0 |= 0x80;
                sub_800A1B74(t);
            }
            else
            {
                sub_800A1AFC(t, 7);
            }
        }
        else
        {
            t->next_8 = sub_800A1310;
            SetDisplayMode_80040658(1);
        }
    }
}

// Matched
void sub_800A1D6C(void)
{
    sub_800A1BCC();
}

extern void SetFadeMode_8001C19C(int a, int b);
extern void sub_800A1DD8(TitleTaskM* t);

// Matched
void sub_800A1D8C(TitleTaskM* t)
{
    LoadOverlay_80020BF8(2, 0xF);
    SetFadeMode_8001C19C(0, 0x20);
    LoadUiTiy_8002BF74();
    t->next_8 = sub_800A1DD8;
}

extern void sub_800C2EB4(void);
extern void sub_800A1E24();

// Matched
void sub_800A1DD8(TitleTaskM* t)
{
    if (uiTiyLoaded_8008B4E8)
    {
        SetFadeMode_8001C19C(3, 0x20);
        sub_800C2EB4();
        t->next_8 = sub_800A1E24;
    }
}

extern int sub_800C45D8(void);
extern void sub_800A1E9C();

// Matched
void sub_800A1E24(TitleTaskM* t, TitleCtxB* u)
{
    if (!sub_800C45D8())
    {
        u->field_0 = 0;
        FreeActiveOverlay_8002C014();
        sub_800A1F98(u->sprts_C, u->tpages_14, u);
        sub_800A1760(u, u->field_24, u->field_0);
        SetFadeMode_8001C19C(0, 0x20);
        t->next_8 = sub_800A1E9C;
    }
}

// Matched
void sub_800A1E9C(TitleTaskM* t, TitleCtxB* u)
{
    SetFadeMode_8001C19C(3, 0x20);
    sub_800A1F98(u->sprts_C, u->tpages_14, u);
    sub_800A1760(u, u->field_24, u->field_0);
    t->next_8 = sub_800A1310;
}

// Matched
void sub_800A1F00(TitleTaskM* t)
{
    unknownFlags_8008D678 |= 0x40000000;
    sub_800A1AFC(t, 0xC);
}

extern void sub_800A2358(void);
extern void sub_800A22FC(void);
extern void sub_800A2424(void);
extern void sub_800A20F4(void);
extern void sub_800A2110(void);
extern void sub_800A2540(void);
extern void PulseColor_80033394(void* a, void* b, void* c, int d, int e, int f);
extern void EncodeName_8003F7C8(void* a, void* b);

extern struct_v3 dword_800B069C; // Levant's start position
extern int dword_80091C94;
extern char byte_800A08B4[];
extern SVECTOR dword_800B06A8; // Levant's start rotation
extern UnitStatus dword_800A2730; // Levant's initial status block

extern int dword_8008B554;
#define SDECL SaveData* s = &saveData_8008B570

// Matched
void sub_800A1F38(void* a)
{
    sub_800A1AFC(a, 9);
}

// Matched
void sub_800A1F58(void* a)
{
    sub_800A1AFC(a, 10);
}

// Matched
void sub_800A1F78(void* a)
{
    sub_800A1AFC(a, 11);
}

typedef struct { char c[4]; } Blk4_;
extern Blk4_ dword_800A08B0;

void sub_800A1F98(SPRT* p, DR_TPAGE* q)
{
    char tmp[4];
    Blk4_ loc;
    short i;
    short y;
    SPRT* e;
    SPRT* e5;

    memset(tmp, 0, 4);
    y = 0x4A;
    e5 = &p[5];
    loc = dword_800A08B0;
    e5->y0 = y;
    e5->x0 = 0x55;
    PulseColor_80033394(&p[5].r0, tmp, &loc, frameCount_8008D3FC, 0xB4, 0x5A);
    SetSemiTrans(e5, 1);
    AddPrimCopy_80040298((void*)pOT_8008D3EC, e5, 5);
    AddPrimCopy_80040298((void*)pOT_8008D3EC, &q[5], 2);
    y = 0;
    for (i = 7; i < 9; i++)
    {
        e = (SPRT*)((int)i * sizeof(SPRT) + (int)p); // &p[i] does not match
        e->x0 = (i - 7) * 5 << 5;
        e->y0 = y;
        AddPrimCopy_80040298((void*)pOT_8008D3EC, e, 5);
        AddPrimCopy_80040298((void*)pOT_8008D3EC, &q[i], 2);
    }
}

// Matched
void sub_800A20F4(void)
{
    SDECL;
    s->levantStatus_7C8.field_1C[0] = 0;
    s->levantStatus_7C8.field_1C[1] = 0xFF;
    s->levantStatus_7C8.field_1C[2] = 0xFF;
}

// Matched
void sub_800A2110(void)
{
    saveData_8008B570.nMapVars_2F4 = 0;
}

void sub_800A211C(void)
{
    SDECL;
    s->field_984 = 5;
    saveData_8008B570.field_0 = 0;
    s->chapterNext_2DE = -1;
    s->playTime_4 = 0;
    s->chapter_2DC = 0;
    s->levant_7A8.pos = dword_800B069C;
    s->levant_7A8.rot = dword_800B06A8;
    s->levantStatus_7C8 = dword_800A2730;
    saveData_8008B570.field_810 = -2;
    sub_800A2358();
    sub_800A20F4();
    sub_800A2110();
    sub_800A2540();
}

void sub_800A2214(void)
{
    int i;
    SDECL;
    for (i = 6; i >= 0; i--)
    {
        s->allMinionsBitfields_814[i] = 0;
    }
}

void sub_800A223C(void)
{
    {
        SDECL;
        s->levantStatus_7C8 = dword_800A2730;
    }
    {
        int i;
        SDECL;
        for (i = 6; i >= 0; i--)
        {
            s->allMinionsBitfields_814[i] = 0;
        }
    }
    EncodeName_8003F7C8(byte_800A08B4, saveData_8008B570.levantStatus_7C8.name_10);
    sub_800A2358();
    sub_800A22FC();
    sub_800A2450();
    sub_800A2424();
}

// Matched
void sub_800A22FC(void)
{
    SaveInventory* b = &saveData_8008B570.inv_24;
    b->yan_0 = 0x64;
    b->inventory_4[0][0].count = 3;
    b->inventory_4[0][1].id = 0xE;
    b->inventory_4[0][0].id = 0;
    b->inventory_4[0][1].count = 1;
    saveData_8008B570.levantStatus_7C8.field_1C[0] = 1;
    saveData_8008B570.levantStatus_7C8.field_1C[1] = 0;
    saveData_8008B570.levantStatus_7C8.field_1C[2] = 0xFF;
    if ((unsigned int)b->emptyCocoons_284 < 10)
    {
        saveData_8008B570.inv_24.emptyCocoons_284 = 10;
    }
}


void sub_800A2358(void)
{
    SaveInventory* b;
    unsigned char* p;
    int i;
    int j;
    int k;
    playerYan_8008B594.yan_0 = 0;
    b = &playerYan_8008B594;
    for (i = 0; i < 0x40; i++)
    {
        b->inventory_4[0][i].id = 0xFF;
        b->inventory_4[0][i].count = 0;
    }
    for (i = 0; i < 0x40; i++)
    {
        b->inventory_4[4][i].id = 0xFF;
        b->inventory_4[4][i].count = 0;
    }
    for (i = 0; i < 0x40; i++)
    {
        b->inventory_4[3][i].id = 0xFF;
        b->inventory_4[2][i].id = 0xFF;
        b->inventory_4[1][i].id = 0xFF;
        b->inventory_4[3][i].count = 0;
        b->inventory_4[2][i].count = 0;
        b->inventory_4[1][i].count = 0;
    }
    b->emptyCocoons_284 = 0;
    b->flags_288[0] = 0;
    b->flags_288[1] = 0;
    // walked with a byte pointer (p = b + j; indexing bits_290[j] does not get the pointer decrement)
    for (j = 0x12, p = (unsigned char*)b + 0x12; j >= 0; j--, p--)
    {
        p[0x290] = 0;
    }
    for (k = 0x13, p = (unsigned char*)b + 0x13; k >= 0; k--, p--)
    {
        p[0x2A3] = 0;
    }
}

// Matched
void sub_800A2424(void)
{
}

void sub_800A242C(void)
{
    SDECL;
    s->field_2E2 = -1;
    s->mapId_2E4[0].field_2 = -1;
    s->mapId_2E4[1].field_2 = -1;
    s->mapId_2E4[2].field_2 = -1;
    s->mapId_2E4[3].field_2 = -1;
}

void sub_800A2450(void)
{
    short i;
    for (i = 0; i < 15; i++)
    {
        saveData_8008B570.minions[i].id = 4;
    }
    for (i = 0; i < 12; i++)
    {
        saveData_8008B570.items[i].id = 0xD3;
    }
}

void sub_800A24E0(void)
{
    short i;
    for (i = 0; i < 15; i++)
    {
        if (saveData_8008B570.minions[i].id == 3)
        {
            saveData_8008B570.minions[i].id = 2;
        }
    }
}

#define FILL(arr, n) { int i; unsigned short v = 0x8000; SDECL; for (i = (n) - 1; i >= 0; i--) s->arr[i] = v; }

void sub_800A2540(void)
{
    dword_8008B554 = 1;
    FILL(tbl_838, 12)
    FILL(tbl_850, 18)
    FILL(tbl_874, 44)
    FILL(tbl_8CC, 22)
    FILL(tbl_8F8, 10)
    FILL(tbl_90C, 16)
    FILL(tbl_92C, 42)
}

void sub_800A2650(void)
{
    SDECL;
    s->chapterNext_2DE = -1;
    s->field_2E0 = 1;
    s->field_2E2 = -1;
    s->mapId_2E4[0].field_2 = -1;
    s->mapId_2E4[1].field_2 = -1;
    s->mapId_2E4[2].field_2 = -1;
    s->mapId_2E4[3].field_2 = -1;
    s->mapId_2E4[1].field_0 = 4;
    dword_80091C94 = 1;
    s->playTime_4 = 0;
    s->chapter_2DC = 0;
    s->field_810 = 0;
    s->mapId_2E4[0].field_0 = 0;
    s->mapId_2E4[2].field_0 = 0;
    s->mapId_2E4[3].field_0 = 0;
    s->levant_7A8.pos = dword_800B069C;
    s->levant_7A8.rot = dword_800B06A8;
    sub_800A2110();
    sub_800A2540();
}

INCLUDE_OVERLAY_ASM(title, dword_800A2718);
