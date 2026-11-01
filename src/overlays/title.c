// TITLE.BIN - loaded at 0x800A05A0
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"



INCLUDE_OVERLAY_ASM(title, dword_800A05A0);

INCLUDE_OVERLAY_ASM(title, sub_800A08C8);

INCLUDE_OVERLAY_ASM(title, sub_800A093C);

INCLUDE_OVERLAY_ASM(title, sub_800A09C0);

INCLUDE_OVERLAY_ASM(title, sub_800A0A1C);

INCLUDE_OVERLAY_ASM(title, sub_800A0A70);

INCLUDE_OVERLAY_ASM(title, sub_800A0AE8);

INCLUDE_OVERLAY_ASM(title, sub_800A0BCC);

INCLUDE_OVERLAY_ASM(title, sub_800A0C28);

INCLUDE_OVERLAY_ASM(title, sub_800A0D18);

INCLUDE_OVERLAY_ASM(title, sub_800A0EF0);

INCLUDE_OVERLAY_ASM(title, sub_800A0F6C);

INCLUDE_OVERLAY_ASM(title, sub_800A1070);

INCLUDE_OVERLAY_ASM(title, sub_800A10D0);

INCLUDE_OVERLAY_ASM(title, sub_800A1174);

INCLUDE_OVERLAY_ASM(title, sub_800A1310);

INCLUDE_OVERLAY_ASM(title, sub_800A14A8);

INCLUDE_OVERLAY_ASM(title, sub_800A158C);

typedef struct TitleTaskM
{
    unsigned int flags_0;
    int pad_4;
    void (*fn_8)();
    int field_C;
    int field_10;
    int field_14;
} TitleTaskM;
typedef struct
{
    short x, y, w, h;
} TitleRectM;
typedef struct
{
    int w[14];
} TitleBlk38M;
extern char dword_800A05A8[];
extern char dword_800A0658[];
extern char dword_800A069C[];
extern int dword_800A2818;
extern void sub_800BB64C(void);
extern void sub_8003E91C(int mode, void* buf, void* rect, int c);
extern void sub_800A1310(TitleTaskM* t);
extern void sub_800A1B74(TitleTaskM* t);

// Matched
void sub_800A166C(TitleTaskM* t)
{
    TitleRectM r1, r2, r3;
    sub_800BB64C();
    r1.x = 0x10;
    r1.y = 0x5A;
    sub_8003E91C(2, dword_800A05A8, &r1, 0);
    r2.x = 0x10;
    r2.y = 0x6A;
    sub_8003E91C(2, dword_800A0658, &r2, 0);
    r3.x = 0x10;
    r3.y = 0x7A;
    sub_8003E91C(2, dword_800A069C, &r3, 0);
    if (sub_8003D380(1))
    {
        t->fn_8 = sub_800A1310;
        sub_800A1B74(t);
    }
}

// Matched
void sub_800A1728(TitleTaskM* t)
{
    sub_800BB64C();
    t->fn_8 = sub_800A1310;
    sub_800A1B74(t);
}

extern void sub_800A1780(TitleTaskM* t, int x);

// Matched
void sub_800A1760(void* p, int x, int y)
{
    sub_800A1780((TitleTaskM*)p, x);
}

typedef struct
{
    int f0, f4, f8, fC, f10, f14;
} TitleCfgM;
extern TitleBlk38M dword_800A06D8, dword_800A0710, dword_800A0748, dword_800A0780;
extern TitleBlk38M dword_800A07B8, dword_800A07F0, dword_800A0828, dword_800A0860;
extern TitleCfgM dword_800A0898;
extern void sub_8002A5A4(TitleCfgM* cfg);

// Matched
void sub_800A1780(TitleTaskM* t, int x)
{
    TitleBlk38M b0, b1, b2, b3, b4, b5, b6, b7;
    void* ptrs[5];
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
    b0.w[2] = (int)&t->field_C;
    b0.w[3] = (int)&t->field_14;
    b1.w[2] = (int)&t->field_C;
    b1.w[3] = (int)&t->field_14;
    b2.w[2] = (int)&t->field_C;
    b2.w[3] = (int)&t->field_14;
    b3.w[2] = (int)&t->field_C;
    b3.w[3] = (int)&t->field_14;
    ptrs[0] = &b0;
    ptrs[1] = &b1;
    ptrs[2] = &b2;
    ptrs[3] = &b3;
    cfg.f4 = sub_8002C64C();
    cfg.fC = x;
    cfg.f10 = (int)ptrs;
    sub_8002A5A4(&cfg);
}

extern void sub_800A1AFC(TitleTaskM* t, int a);

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
    SoundStruct* s = &stru_80091CE0;
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
    e = sub_80043AF8(dword_8008D638);
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
    sub_80040658(1);
    dword_8008BD80 = -2;
    sub_800B7674(1, 0);
    t->fn_8 = sub_800A1CC0;
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
            t->fn_8 = sub_800A1310;
            sub_80040658(1);
        }
    }
}

// Matched
void sub_800A1D6C(void)
{
    sub_800A1BCC();
}

extern void sub_8001C19C(int a, int b);
extern void sub_800A1DD8(TitleTaskM* t);

// Matched
void sub_800A1D8C(TitleTaskM* t)
{
    LoadOverlay_80020BF8(2, 0xF);
    sub_8001C19C(0, 0x20);
    sub_8002BF74();
    t->fn_8 = sub_800A1DD8;
}

extern void sub_800C2EB4(void);
extern void sub_800A1E24();

// Matched
void sub_800A1DD8(TitleTaskM* t)
{
    if (dword_8008B4E8)
    {
        sub_8001C19C(3, 0x20);
        sub_800C2EB4();
        t->fn_8 = sub_800A1E24;
    }
}

typedef struct
{
    int field_0;
    int pad_4[2];
    int field_C;
    int pad_10;
    int field_14;
    char pad_18[0xC];
    short field_24;
} TitleObjM;
extern int sub_800C45D8(void);
extern void sub_800A1F98(int a, int b, TitleObjM* u);
extern void sub_800A1E9C();

// Matched
void sub_800A1E24(TitleTaskM* t, TitleObjM* u)
{
    if (!sub_800C45D8())
    {
        u->field_0 = 0;
        FreeActiveOverlay_8002C014();
        sub_800A1F98(u->field_C, u->field_14, u);
        sub_800A1760(u, u->field_24, u->field_0);
        sub_8001C19C(0, 0x20);
        t->fn_8 = sub_800A1E9C;
    }
}

// Matched
void sub_800A1E9C(TitleTaskM* t, TitleObjM* u)
{
    sub_8001C19C(3, 0x20);
    sub_800A1F98(u->field_C, u->field_14, u);
    sub_800A1760(u, u->field_24, u->field_0);
    t->fn_8 = sub_800A1310;
}

// Matched
void sub_800A1F00(TitleTaskM* t)
{
    unknownFlags_8008D678 |= 0x40000000;
    sub_800A1AFC(t, 0xC);
}

INCLUDE_OVERLAY_ASM(title, sub_800A1F38);

INCLUDE_OVERLAY_ASM(title, sub_800A1F58);

INCLUDE_OVERLAY_ASM(title, sub_800A1F78);

INCLUDE_OVERLAY_ASM(title, sub_800A1F98);

INCLUDE_OVERLAY_ASM(title, sub_800A20F4);

INCLUDE_OVERLAY_ASM(title, sub_800A2110);

INCLUDE_OVERLAY_ASM(title, sub_800A211C);

INCLUDE_OVERLAY_ASM(title, sub_800A2214);

INCLUDE_OVERLAY_ASM(title, sub_800A223C);

INCLUDE_OVERLAY_ASM(title, sub_800A22FC);

INCLUDE_OVERLAY_ASM(title, sub_800A2358);

INCLUDE_OVERLAY_ASM(title, sub_800A2424);

INCLUDE_OVERLAY_ASM(title, sub_800A242C);

INCLUDE_OVERLAY_ASM(title, sub_800A2450);

INCLUDE_OVERLAY_ASM(title, sub_800A24E0);

INCLUDE_OVERLAY_ASM(title, sub_800A2540);

INCLUDE_OVERLAY_ASM(title, sub_800A2650);

INCLUDE_OVERLAY_ASM(title, dword_800A2718);
