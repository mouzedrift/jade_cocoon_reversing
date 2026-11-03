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
    void* field_70;
    void* field_74;
} TitleCtxA;

extern int dword_800A280C;
extern int dword_800A2810;
extern void sub_800A093C();
// Matched
void sub_800A08C8(TitleTask* t, TitleCtxA* c)
{
    RECT r;
    unsigned short* s = (unsigned short*)&stru_8008B4D8;
    dword_800A280C = 0x36;
    dword_800A2810 = 0x18;
    c->field_64 = 0x1E;
    c->field_5C = 0;
    c->field_68 = 0;
    c->field_60 = 0x18;
    c->field_6C = 0;
    r.x = 0x20;
    r.y = 0x20;
    r.w = s[6] - 0x20;
    r.h = s[7] - 0x20;
    t->next_8 = sub_800A093C;
}


extern void sub_800A09C0();
// Matched
void sub_800A093C(TitleTask* t, TitleCtxA* c)
{
    void* buf;
    if (GetFileRequestCount_8003BC34() == 0)
    {
        c->field_70 = 0;
        c->field_74 = 0;
        buf = DATA_GetFileBuffer_8003CAA0(0x39);
        sub_80028E74((int*)&c->field_70, 0, (int*)&c->field_74, (int)buf, 1);
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
        sub_8002BF74();
        t->next_8 = sub_800A0A1C;
    }
}


extern int dword_800A2808;
extern unsigned short word_8009194C;
extern void sub_800A0A70();
// Matched
void sub_800A0A1C(TitleTask* t)
{
    if (dword_8008B4E8)
    {
        word_8009194C = 0;
        dword_800A2808 = LoadOverlay_80020BF8(1, 0x11);
        t->next_8 = sub_800A0A70;
    }
}


extern int dword_800A2718;
extern void sub_800B6E4C(void* a0, int a1);
extern void sub_8003F7C8(void* a0, void* a1);
extern void sub_800A0AE8();
// Matched
void sub_800A0A70(TitleTask* t)
{
    if (GetFileRequestStatus_8003BE30(dword_800A2808) == 0)
    {
        if (!(saveData_8008B570.field_0 & 0x80))
        {
            sub_8003F7C8(&dword_800A2718, (char*)&saveData_8008B570 + 0x7D8);
        }
        sub_800B6E4C((char*)&saveData_8008B570 + 0x7D8, 0);
        t->next_8 = sub_800A0AE8;
    }
}


extern void sub_800A0D18();
extern int sub_800B6FC8(void);
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
    sub_800A0D18(c->field_70, c->field_74, 0, c);
    if (sub_800B6FC8() == 0)
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
        FreeSound_80030D00((int)&stru_80091CE0);
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
        if (c->field_70)
        {
            free3_8003FC6C(c->field_70);
            c->field_70 = 0;
        }
        if (c->field_74)
        {
            free3_8003FC6C(c->field_74);
            c->field_74 = 0;
        }
        c->field_68 = 0x3C;
        t->next_8 = sub_800A0BCC;
        ss = &stru_80091CE0;
        if (ss->field_4_seq_num >= 0)
        {
            SsSepSetDecrescendo(*(short*)&ss->field_C_sep_access_num, ss->field_4_seq_num, 0x7F, 0x78);
            ss->field_4_seq_num = -1;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(title, sub_800A0C28);

typedef struct TitleEnt
{
    int field_0;
    int field_4;
    short field_8;
    short field_A;
    int pad_C[2];
} TitleEnt;

typedef struct TitleStr4
{
    char c[4];
} TitleStr4;

extern void sub_80033394(void* a0, void* a1, void* a2, int a3, int a4, int a5);
extern unsigned long* pOT_8008D3EC;
extern int dword_800A05A0;
#if 0
// Not matched: register allocation / scheduling differs
void sub_800A0D18(TitleEnt* p, char* q, int mode, TitleCtxA* c)
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
                p[i].field_8 = ((i % 2) * 5) << 5;
            p[i].field_A = y;
            AddPrimCopy_80040298(pOT_8008D3EC, &p[i], 5);
            AddPrimCopy_80040298(pOT_8008D3EC, q + i * 8, 2);
        }
    }
    else
    {
        memset(zero, 0, 4);
        y = 0x17;
        i = (short)i;
        s4 = *(TitleStr4*)((char*)&dword_800A05A0 + 4);
        p[i].field_8 = 0x6F;
        p[i].field_A = y;
        sub_80033394(&p[i].field_4, zero, &s4, c->field_5C, dword_800A280C, dword_800A2810);
        SetSemiTrans(&p[i], 1);
        AddPrimCopy_80040298(pOT_8008D3EC, &p[i], 5);
        AddPrimCopy_80040298(pOT_8008D3EC, q + i * 8, 2);
    }
}
#endif
INCLUDE_OVERLAY_ASM(title, sub_800A0D18);

extern void sub_8001C19C(int a0, int a1);
extern void sub_80031260(void* a0, int a1, int a2);
extern int dword_800A27C0;
extern int dword_800A2818;
// Matched
int sub_800A0EF0(void)
{
    sub_8001C19C(3, 0x20);
    drawEnvRed_8008D448[0] = 0;
    drawEnvRed_8008D448[1] = 0;
    drawEnvRed_8008D448[2] = 0;
    LoadSound_80030A84(0x1B, &stru_80091CE0);
    sub_80031260(&stru_80091CE0, 0x1B, 1);
    DrawIntroMovie_8001AF64(&dword_800A27C0);
    FreeSound_80030D00((int)&stru_80091CE0);
    return dword_800A2818;
}


typedef struct TitleCtxB
{
    int field_0;
    int field_4;
    int field_8;
    char* field_C;
    int field_10;
    char* field_14;
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
        c->field_C = 0;
        c->field_14 = 0;
        buf = DATA_GetFileBuffer_8003CAA0(0x36);
        sub_80028E74((int*)&c->field_C, 0, (int*)&c->field_14, (int)buf, 1);
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
    if (c->field_C)
    {
        free3_8003FC6C(c->field_C);
        c->field_C = 0;
    }
    if (d->field_14)
    {
        free3_8003FC6C(d->field_14);
        d->field_14 = 0;
    }
}


typedef struct TitleSmall
{
    short a;
    char b;
    char c;
} TitleSmall;

extern void sub_80042460(void* a0, void* a1, void* a2, unsigned int a3);
extern void sub_800A1F98();
extern void sub_800A1AC0();
extern void sub_800A1310();
extern void sub_8004E2C8(int a0);
#define TITLE_TIMEOUT(t, c) \
    if (++dword_800A2814 >= 0x1771) \
    { \
        (c)->field_0 = 0; \
        if (stru_80091CE0.field_4_seq_num >= 0) \
        { \
            SsSepSetDecrescendo(*(short*)&stru_80091CE0.field_C_sep_access_num, stru_80091CE0.field_4_seq_num, 0x7F, 0x78); \
            stru_80091CE0.field_4_seq_num = -1; \
        } \
        sub_8001C19C(0, 0x20); \
        sub_8001C19C(1, 0x20); \
        (t)->next_8 = sub_800A1AC0; \
    }
#if 0
// Not matched: register allocation / scheduling differs
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
    *(short*)(c->field_C + 0x30) = 0x54;
    *(short*)(c->field_C + 0x32) = 0xA7;
    AddPrimCopy_80040298((char*)pOT_8008D454 + 0x38, c->field_C + 0x28, 5);
    AddPrimCopy_80040298((char*)pOT_8008D454 + 0x38, c->field_14 + 0x10, 2);
    sub_80042460(&r, &s, (char*)pOT_8008D454 + 0x38, (unsigned int)frameCount_8008D3FC >> 1);
    sub_800A1F98(c->field_C, c->field_14, c);
    if (word_8009194C & 0x800)
    {
        PlaySfx_80031494(0x7E);
        srand(gnFrame_8008D610);
        c->field_0 = 0;
        t->next_8 = sub_800A1310;
        dword_800A2814 = 0;
    }
    TITLE_TIMEOUT(t, d)
}
#endif
INCLUDE_OVERLAY_ASM(title, sub_800A1174);

extern void sub_800A1760();
extern unsigned short word_800918CC;
extern void sub_800A14A8();
extern void sub_8003D794(void* a0, int a1);
extern void sub_8003BB1C(void);
extern void sub_800BB5DC(void);
extern void (*off_800A27E8[])();
// Matched
void sub_800A1310(TitleTask* t, TitleCtxB* c)
{
    sub_800A1F98(c->field_C, c->field_14, c);
    sub_8003D794(c->field_1C, 0);
    if (word_800918CC & 0x5000)
    {
        c->field_0 = 0;
        dword_800A2814 = 0;
    }
    sub_800A1760(c, c->field_24, c->field_0);
    c->field_0 = c->field_0 + 1;
    if (sub_8003D380(1))
    {
        dword_800A2814 = 0;
        off_800A27E8[c->field_24](t, c);
        if ((unsigned short)c->field_24 < 2)
        {
            sub_8003BB1C();
            if (c->field_24 == 0)
            {
                LoadOverlay_80020BF8(2, 0x10);
                sub_800BB5DC();
                t->next_8 = sub_800A14A8;
            }
        }
    }
    else if (sub_8003D41C(1))
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
extern void sub_8003E91C(int mode, void* str, void* pos, int c);
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
    sub_8003E91C(2, str_800A05A8, &r0, 0);
    r1.x = 0x10;
    r1.y = 0x6A;
    sub_8003E91C(2, str_800A05BC, &r1, 0);
    r2.x = 0x10;
    r2.y = 0x7A;
    sub_8003E91C(2, str_800A0604, &r2, 0);
    r3.x = 0x10;
    r3.y = 0x8A;
    sub_8003E91C(2, str_800A0640, &r3, 0);
    if (sub_8003D380(1))
    {
        t->next_8 = sub_800A1310;
        sub_800A1B74(t);
    }
}


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
extern void sub_800A1310();
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

extern void sub_800A1AFC();

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
extern void sub_800A1F98();
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

extern void sub_800A1AFC();
extern void sub_800A2358(void);
extern void sub_800A22FC(void);
extern void sub_800A2450(void);
extern void sub_800A2424(void);
extern void sub_800A20F4(void);
extern void sub_800A2110(void);
extern void sub_800A2540(void);
extern void sub_80033394(void* a, void* b, void* c, int d, int e, int f);
extern void sub_8003F7C8(void* a, void* b);

typedef struct { int a, b, c; } Blk12_;
extern Blk12_ dword_800B069C;
extern int dword_80091C94;
extern char byte_800A08B4[];
typedef struct { char c[8]; } Blk8_;
extern Blk8_ dword_800B06A8;
typedef struct { int a[18]; } Blk72_;
extern Blk72_ dword_800A2730;
typedef struct { char pad_0[8]; short x_8; short y_A; char pad_C[8]; } Sprite20_;

extern int playerYan_8008B594;
extern int dword_8008B554;
#define SBASE ((char*)&saveData_8008B570)
#define SA(a) ((char*)&saveData_8008B570 + ((a) - 0x8008B570))
#define SDECL char* s = SBASE
#define SB(o) (*(char*)(s + (o)))
#define SH(o) (*(short*)(s + (o)))
#define SW(o) (*(int*)(s + (o)))

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

void sub_800A1F98(char* p, char* q)
{
    char tmp[4];
    Blk4_ loc;
    short i;
    short y;
    Sprite20_* e;
    Sprite20_* e5;

    memset(tmp, 0, 4);
    y = 0x4A;
    e5 = &((Sprite20_*)p)[5];
    loc = dword_800A08B0;
    e5->y_A = y;
    e5->x_8 = 0x55;
    sub_80033394(p + 0x68, tmp, &loc, frameCount_8008D3FC, 0xB4, 0x5A);
    SetSemiTrans(e5, 1);
    AddPrimCopy_80040298((void*)pOT_8008D3EC, e5, 5);
    AddPrimCopy_80040298((void*)pOT_8008D3EC, q + 0x28, 2);
    y = 0;
    for (i = 7; i < 9; i++)
    {
        e = (Sprite20_*)((int)i * 20 + (int)p);
        e->x_8 = (i - 7) * 5 << 5;
        e->y_A = y;
        AddPrimCopy_80040298((void*)pOT_8008D3EC, e, 5);
        AddPrimCopy_80040298((void*)pOT_8008D3EC, q + i * 8, 2);
    }
}

// Matched
void sub_800A20F4(void)
{
    SDECL;
    s[0x7E4] = 0;
    s[0x7E5] = 0xFF;
    s[0x7E6] = 0xFF;
}

// Matched
void sub_800A2110(void)
{
    *(int*)((char*)&saveData_8008B570 + 0x2F4) = 0;
}

void sub_800A211C(void)
{
    SDECL;
    SW(0x984) = 5;
    saveData_8008B570.field_0 = 0;
    SH(0x2DE) = -1;
    SW(4) = 0;
    SH(0x2DC) = 0;
    *(Blk12_*)(s + 0x7A8) = dword_800B069C;
    *(Blk8_*)(s + 0x7B4) = dword_800B06A8;
    *(Blk72_*)(s + 0x7C8) = dword_800A2730;
    *(int*)SA(0x8008BD80) = -2;
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
        ((int*)(s + 0x814))[i] = 0;
    }
}

void sub_800A223C(void)
{
    {
        SDECL;
        *(Blk72_*)(s + 0x7C8) = dword_800A2730;
    }
    {
        int i;
        SDECL;
        for (i = 6; i >= 0; i--)
        {
            ((int*)(s + 0x814))[i] = 0;
        }
    }
    sub_8003F7C8(byte_800A08B4, SA(0x8008BD48));
    sub_800A2358();
    sub_800A22FC();
    sub_800A2450();
    sub_800A2424();
}

#if 0
// Not matched: gcc computes the base registers before the first store (original: store, then addiu of the base, saveData base = base - 0x24)
void sub_800A22FC(void)
{
    char* b;
    char* s;
    playerYan_8008B594 = 0x64;
    b = (char*)&playerYan_8008B594;
    s = SBASE;
    b[5] = 3;
    b[6] = 0xE;
    b[4] = 0;
    b[7] = 1;
    s[0x7E4] = 1;
    s[0x7E5] = 0;
    s[0x7E6] = 0xFF;
    if (*(unsigned int*)(b + 0x284) < 10)
    {
        *(int*)(s + 0x2A8) = 10;
    }
}
#endif
INCLUDE_OVERLAY_ASM(title, sub_800A22FC);

void sub_800A2358(void)
{
    char* b;
    char* p;
    int i;
    int j;
    int k;
    playerYan_8008B594 = 0;
    b = (char*)&playerYan_8008B594;
    for (i = 0; i < 0x40; i++)
    {
        b[4 + i * 2] = 0xFF;
        b[5 + i * 2] = 0;
    }
    for (i = 0; i < 0x40; i++)
    {
        b[0x204 + i * 2] = 0xFF;
        b[0x205 + i * 2] = 0;
    }
    for (i = 0; i < 0x40; i++)
    {
        b[0x184 + i * 2] = 0xFF;
        b[0x104 + i * 2] = 0xFF;
        b[0x84 + i * 2] = 0xFF;
        b[0x185 + i * 2] = 0;
        b[0x105 + i * 2] = 0;
        b[0x85 + i * 2] = 0;
    }
    *(int*)(b + 0x284) = 0;
    *(int*)(b + 0x288) = 0;
    *(int*)(b + 0x28C) = 0;
    for (j = 0x12, p = b + 0x12; j >= 0; j--, p--)
    {
        p[0x290] = 0;
    }
    for (k = 0x13, p = b + 0x13; k >= 0; k--, p--)
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
    SH(0x2E2) = -1;
    SH(0x2E6) = -1;
    SH(0x2EA) = -1;
    SH(0x2EE) = -1;
    SH(0x2F2) = -1;
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

#define FILL(off, n) { int i; unsigned short v = 0x8000; SDECL; for (i = (n) - 1; i >= 0; i--) ((unsigned short*)(s + (off)))[i] = v; }

void sub_800A2540(void)
{
    dword_8008B554 = 1;
    FILL(0x838, 12)
    FILL(0x850, 18)
    FILL(0x874, 44)
    FILL(0x8CC, 22)
    FILL(0x8F8, 10)
    FILL(0x90C, 16)
    FILL(0x92C, 42)
}

void sub_800A2650(void)
{
    SDECL;
    SH(0x2DE) = -1;
    SH(0x2E0) = 1;
    SH(0x2E2) = -1;
    SH(0x2E6) = -1;
    SH(0x2EA) = -1;
    SH(0x2EE) = -1;
    SH(0x2F2) = -1;
    SH(0x2E8) = 4;
    dword_80091C94 = 1;
    SW(4) = 0;
    SH(0x2DC) = 0;
    SW(0x810) = 0;
    SH(0x2E4) = 0;
    SH(0x2EC) = 0;
    SH(0x2F0) = 0;
    *(Blk12_*)(s + 0x7A8) = dword_800B069C;
    *(Blk8_*)(s + 0x7B4) = dword_800B06A8;
    sub_800A2110();
    sub_800A2540();
}

INCLUDE_OVERLAY_ASM(title, dword_800A2718);
