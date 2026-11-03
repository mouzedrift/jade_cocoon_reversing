// LOAD.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

extern int dword_800BE184;
extern int dword_800BE14C;
extern int dword_800BE150;
extern int dword_800BE174;
extern int dword_800BE1E4[];
extern int (*dword_800BE294[])();
extern int dword_800BE254[];
extern char byte_800B7630[];
extern char* dword_800BE188[];
extern int dword_800BE2C4;
extern int dword_800BE2C8;
extern int dword_800BE2CC;
extern int dword_800BE2D0;
extern int dword_800BE2D4;
extern int dword_800BE2D8;
extern int dword_800BE2DC;
extern int dword_800BE2E0;
extern int** dword_8008D480;
extern int StopCARD(void);
extern void InitCARD(void);
extern void StartCARD(void);
extern int _bu_init(void);
extern int MemCardSync(int a, int* b, int* c);
extern void MemCardAccept();
extern void MemCardExist();
extern void sub_800B7674(int a, int b);
typedef struct
{
    int f0_LOAD;
    int f4_LOAD;
    int f8_LOAD;
    int fC_LOAD;
    int f10_LOAD;
    int f14_LOAD;
    int f18_LOAD;
    int f1C_LOAD;
    int f20_LOAD;
    int pad24_LOAD[8];
    int f44_LOAD;
    int f48_LOAD;
    int f4C_LOAD;
    int f50_LOAD;
    int f54_LOAD;
} LoadState_LOAD;
extern LoadState_LOAD dword_800BE1F4;
extern int uiTiyLoaded_8008B4E8;
extern int dword_8008B570[];
extern unsigned char byte_800BDF58;
extern int dword_800BE208;
extern char* dword_800BDECC[];
extern void DrawLoadingIcon_8003CD5C(void);
extern void DrawMenuBackground_8002BE10(void);
extern void sub_800BACBC(char** lines);
extern void sub_800B794C(int* t, int* s);
extern void sub_800B79F8();
extern void sub_800B9A8C();
extern void sub_800B98C4();
extern void sub_800BA234();
extern void sub_800BA968();
extern void sub_800BAAE0();
extern void sub_800BA9AC(int* t);
extern void sub_800BA9F0();
extern void sub_8004F5E8(int a);
typedef struct
{
    unsigned short flags_LOAD;
    short pad2_LOAD;
    int f4_LOAD;
    int f8_LOAD;
    int fC_LOAD;
    short x_LOAD;
    short y_LOAD;
    char pad14_LOAD[8];
} MenuItem_LOAD;
typedef struct
{
    MenuItem_LOAD item_LOAD[2];
} MenuItems2_LOAD;
typedef struct
{
    int f0_LOAD;
    int f4_LOAD;
    int f8_LOAD;
    int fC_LOAD;
    MenuItem_LOAD** items_LOAD;
    int f14_LOAD;
} MenuWin_LOAD;
extern MenuItems2_LOAD dword_800B731C;
extern MenuItems2_LOAD dword_800B7368;
typedef struct DirEntry_LOAD
{
    char name_LOAD[20];
    long attr_LOAD;
    long size_LOAD;
    struct DirEntry_LOAD* next_LOAD;
    long head_LOAD;
    char system_LOAD[4];
} DirEntry_LOAD;
extern long MemCardGetDirentry(long chan, char* name, DirEntry_LOAD* dir, long* files, long ofs, long max);
extern char byte_800B72FC[];
extern char* dword_800BE028[2][15];
extern void FreeActiveOverlay_8002C014(void);
extern int sub_800A6D50(int a);
extern void sub_800A6D30(int a);
extern int dword_80091C54;
extern int MemCardFormat(long chan);
extern void sub_800BAFB0(int a);
extern void VSyncCallbacks(int a, int b);
extern void _card_stop(void);
extern void TestEvent(int a);
extern void UserFuncInit(void);
extern void _card_start(void);
extern void sub_800BD06C(void);
extern void DrawText_8003E91C(int a0, char* a1, void* a2, short a3);
extern char byte_800B682C[];
extern char byte_800B6B9C[];
extern void sub_8003F264(void* p, int a, int b);
extern char byte_800B69FC[];
extern int dword_800BDD64;
extern void DrawMenuWindows_8002A5A4(void* p);
typedef struct
{
    short x_LOAD;
    short y_LOAD;
} Pos_LOAD;
extern unsigned char byte_800BDF68;
extern int dword_800BE2A4;
extern int dword_800BE2A8;
extern int dword_800BE2AC;
extern int dword_800BE2B0;
extern int dword_800BE2B4;
extern int dword_800BE2B8;
extern int dword_800BE2BC;
extern int dword_800BE2C0;
extern int EnterCriticalSection(void);
extern void CloseEvent(int a);
extern void ExitCriticalSection(void);
extern void _clr_card_event(void);
extern int _get_card_event_x(void);
extern void _new_card(void);
extern void _card_write(int a, int b, void* c);
typedef struct
{
    char c_LOAD[8];
} Bytes8_LOAD;
typedef struct
{
    short s_LOAD;
    char c0_LOAD;
    char c1_LOAD;
} Tail4_LOAD;
typedef struct
{
    short f0_LOAD;
    short f2_LOAD;
    short f4_LOAD;
    short f6_LOAD;
} Row8_LOAD;
extern Row8_LOAD dword_800BD998[];
extern Bytes8_LOAD dword_800B6B8C;
extern Bytes8_LOAD dword_800B6A24;
extern Bytes8_LOAD dword_800B69F4;
extern int dword_800BDB64;
extern int dword_800BDBBC;
extern int* dword_800BDBD4[];
extern Bytes8_LOAD dword_800B6BA0;
extern Bytes8_LOAD dword_800B6B94;
extern unsigned short uiColor_8008B590;
extern char* dword_8008D454;
extern void DrawUiTiySprt_8002C06C(void* a, int b, int c);
extern void DrawWindow_80042460(void* a, void* b, void* c, int d);
typedef struct
{
    void* f0_LOAD;
    void* f4_LOAD;
    char pad8_LOAD[0x18];
    int f20_LOAD;
    int f24_LOAD;
    int f28_LOAD;
    char pad2C_LOAD[4];
    short s30_LOAD;
    char pad32_LOAD[0x22];
    unsigned f54_LOAD;
    int f58_LOAD;
    int f5C_LOAD;
} LoadTask_LOAD;
typedef struct
{
    short w_LOAD;
    short h_LOAD;
} Size_LOAD;
typedef struct
{
    short x_LOAD;
    short y_LOAD;
    short w_LOAD;
    short h_LOAD;
} Rect_LOAD;
extern Size_LOAD MeasureTextLines_8003E3B4(int* list);
extern int IsConfirmPressed_8003D288(int a, int b);
extern int IsCancelPressed_8003D3C0(int a, int b);
extern void UserFuncOpen(void* fn, int a);
extern void sub_800BB6F4(void);
extern void sub_800BBA5C(void);
extern char byte_800B73A0[];
extern char byte_800B7544[];
typedef struct
{
    short a_LOAD;
    short b_LOAD;
} Pair_LOAD;
typedef struct
{
    unsigned char pad0_LOAD[6];
    unsigned char f6_LOAD;
    unsigned char f7_LOAD;
    unsigned char f8_LOAD;
    unsigned char pad9_LOAD[2];
    unsigned char fB_LOAD;
    unsigned char fC_LOAD;
    unsigned char fD_LOAD;
    unsigned char padE_LOAD[2];
} Row16_LOAD;
typedef struct
{
    unsigned char pad0_LOAD[0xC];
    unsigned char fC_LOAD;
    unsigned char padD_LOAD[0xF];
    unsigned char f1C_LOAD;
    unsigned char pad1D_LOAD[0xF];
    unsigned char f2C_LOAD;
    unsigned char pad2D_LOAD[0xF];
    unsigned char f3C_LOAD;
    unsigned char f3D_LOAD;
    unsigned char pad3E_LOAD[0xE];
    unsigned char f4C_LOAD;
} Opts_LOAD;
extern Opts_LOAD dword_800BDF4C;
extern Row16_LOAD stru_800BDF4C[];
extern void sub_8002B8DC(Pair_LOAD q, short* a, short* b, int c);
extern void sub_800B8BD4(void* t);
extern void PlaySfx_80031494(int a);
extern void sub_800BADF4(void);
extern char* sub_800BAE4C(int n);
extern int sub_800BAE2C(void);
extern int sub_800BAE3C(void);
typedef struct
{
    char c_LOAD[6];
} Bytes6_LOAD;
extern Bytes6_LOAD dword_800B7624;
extern char byte_800B74C4[];
extern char byte_800B74E8[];
extern char byte_800B7514[];
extern void sub_800BBF88(void);
extern void sub_800BC17C(void);
extern int printf(const char* fmt, ...);

INCLUDE_OVERLAY_ASM(load, dword_800B66C0);

void sub_800B7650(void)
{
    sub_800B7674(4, 0);
}

INCLUDE_OVERLAY_ASM(load, sub_800B7674);

void sub_800B7894(int* t)
{
    if (uiTiyLoaded_8008B4E8)
    {
        t[2] = (int)sub_800B794C;
    }
}

void sub_800B78B8(int v)
{
    dword_8008D480[9][22] = v;
}

void sub_800B78D0(void)
{
    int* t;
    dword_8008B570[516] = -1;
    dword_8008B570[0] |= 0x180;
    t = dword_8008D480[9];
    *(short*)((char*)t + 0x30) = 1;
    byte_800BDF58 = 0;
    t[21] = 0x20;
}

int sub_800B7914(void)
{
    return dword_8008D480[9][2];
}

void sub_800B7934(void)
{
}

int sub_800B793C(void)
{
    return dword_800BE184;
}

void sub_800B794C(int* t, int* s)
{
    switch (s[10])
    {
    case 0:
        sub_800B79F8(s);
        break;
    case 2:
        sub_800B9A8C(s);
        t[2] = (int)sub_800B98C4;
        s[11] = 0;
        break;
    case 3:
        t[2] = (int)sub_800BA234;
        break;
    case 4:
        t[2] = (int)sub_800BA968;
        break;
    case 5:
    case 6:
        t[2] = (int)sub_800BAAE0;
        break;
    }
}
INCLUDE_OVERLAY_ASM(load, dword_800B68E0);

INCLUDE_OVERLAY_ASM(load, sub_800B79F8);

INCLUDE_OVERLAY_ASM(load, sub_800B80F8);

INCLUDE_OVERLAY_ASM(load, sub_800B82FC);

void sub_800B847C(void)
{
    int i;
    Row8_LOAD* p;
    Bytes8_LOAD a;
    Tail4_LOAD b;
    for (i = 0; i < 2; i++)
    {
        if (i == stru_800BDF4C[1].fC_LOAD)
        {
            *dword_800BDBD4[i] = 4;
        }
        else
        {
            *dword_800BDBD4[i] = 1;
        }
    }
    DrawMenuWindows_8002A5A4(&dword_800BDB64);
    DrawMenuWindows_8002A5A4(&dword_800BDBBC);
    for (p = &dword_800BD998[2]; p->f4_LOAD >= 0; p++)
    {
        DrawUiTiySprt_8002C06C(p, p->f4_LOAD, p->f6_LOAD);
    }
    a = dword_800B69F4;
    b.c1_LOAD = 1;
    b.c0_LOAD = 0;
    b.s_LOAD = uiColor_8008B590;
    DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
}

void sub_800B85AC(void)
{
    Pos_LOAD p0;
    Pos_LOAD p1;
    Bytes8_LOAD a;
    Tail4_LOAD b;
    p0.x_LOAD = 0x13;
    p0.y_LOAD = 0x49;
    DrawText_8003E91C(2, byte_800B682C, &p0, 5);
    p1.x_LOAD = 0x13;
    p1.y_LOAD = 0x57;
    DrawText_8003E91C(2, byte_800B69FC, &p1, 5);
    a = dword_800B6A24;
    b.c1_LOAD = 1;
    b.c0_LOAD = 0;
    b.s_LOAD = uiColor_8008B590;
    DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
    DrawMenuWindows_8002A5A4(&dword_800BDD64);
}

void sub_800B867C(LoadTask_LOAD* t)
{
    Pair_LOAD q;
    short r0[4];
    short r1[6];
    sub_800B8BD4(t);
    r1[0] = stru_800BDF4C[t->s30_LOAD].f6_LOAD;
    r1[1] = stru_800BDF4C[t->s30_LOAD].f7_LOAD;
    r1[2] = stru_800BDF4C[t->s30_LOAD].f8_LOAD;
    r1[3] = stru_800BDF4C[t->s30_LOAD].fB_LOAD;
    r1[4] = stru_800BDF4C[t->s30_LOAD].fC_LOAD;
    r1[5] = stru_800BDF4C[t->s30_LOAD].fD_LOAD;
    q.a_LOAD = 2;
    q.b_LOAD = 1;
    r0[0] = 0x9A;
    r0[1] = 0x2C;
    r0[2] = 0x9A;
    r0[3] = 0xB7;
    sub_8002B8DC(q, r1, r0, 1);
}

INCLUDE_OVERLAY_ASM(load, sub_800B877C);

void sub_800B8984(void)
{
    Bytes8_LOAD a;
    Tail4_LOAD b;
    DrawUiTiySprt_8002C06C(&dword_800BD998[byte_800BDF58], dword_800BD998[byte_800BDF58].f4_LOAD, dword_800BD998[byte_800BDF58].f6_LOAD);
    a = dword_800B6B8C;
    b.c1_LOAD = 1;
    b.c0_LOAD = 0;
    b.s_LOAD = uiColor_8008B590;
    DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
}

#if 0
// Not matched: only the order of the prologue stores differs ($ra/$s0 vs argument set-up)
void sub_800B8A20(void)
{
    Pos_LOAD p0;
    Pos_LOAD p1;
    Bytes8_LOAD a;
    Tail4_LOAD b;
    p0.x_LOAD = 0xBF;
    p0.y_LOAD = 0x15;
    DrawUiTiySprt_8002C06C(&p0, 0x27, 1);
    p1.x_LOAD = 0x124;
    p1.y_LOAD = 0x15;
    DrawUiTiySprt_8002C06C(&p1, (byte_800BDF68 == 1) << 1, 1);
    a = dword_800B6B94;
    b.c1_LOAD = 1;
    b.c0_LOAD = 0;
    b.s_LOAD = uiColor_8008B590;
    DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800B8A20);

void sub_800B8AE4(void)
{
    Pos_LOAD p0;
    Pos_LOAD p1;
    Pos_LOAD p2;
    Bytes8_LOAD a;
    Tail4_LOAD b;
    p0.x_LOAD = 0x1C;
    p0.y_LOAD = 0x24;
    sub_8003F264(&p0, dword_800BDF4C.f3D_LOAD + dword_800BDF4C.f3C_LOAD + 1, 5);
    p1.x_LOAD = 0x1C;
    p1.y_LOAD = 0x24;
    DrawText_8003E91C(1, byte_800B6B9C, &p1, 5);
    p2.x_LOAD = 0x32;
    p2.y_LOAD = 0x24;
    sub_8003F264(&p2, 0xF, 5);
    a = dword_800B6BA0;
    b.c1_LOAD = 1;
    b.c0_LOAD = 0;
    b.s_LOAD = uiColor_8008B590;
    DrawWindow_80042460(&a, &b, dword_8008D454 + 0x38, 0);
}

INCLUDE_OVERLAY_ASM(load, sub_800B8BD4);

void sub_800B9220(LoadTask_LOAD* t)
{
    if (IsConfirmPressed_8003D288(1, (t->f54_LOAD >> 6) & 1))
    {
        switch (byte_800BDF58)
        {
        case 0:
        case 1:
            t->f24_LOAD = 1;
            break;
        case 2:
            t->f28_LOAD = 5;
            break;
        case 3:
            t->f24_LOAD = 5;
            break;
        }
    }
    else if (IsCancelPressed_8003D3C0(1, (t->f54_LOAD >> 6) & 1))
    {
        t->f28_LOAD = 5;
    }
}

#if 0
// Not matched: only a dead byte load (lbu $v1) of the options struct in the prologue is missing
void sub_800B92C0(LoadTask_LOAD* t)
{
    if (IsConfirmPressed_8003D288(0, (t->f54_LOAD >> 6) & 1))
    {
        PlaySfx_80031494(0x7E);
        sub_800BADF4();
        t->f24_LOAD = 0x12;
    }
    else if (IsCancelPressed_8003D3C0(1, (t->f54_LOAD >> 6) & 1))
    {
        if (t->f54_LOAD & 0x24)
        {
            t->f28_LOAD = 5;
        }
        else
        {
            t->f24_LOAD = 0;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800B92C0);

void sub_800B9360(LoadTask_LOAD* t)
{
    switch (sub_800BAE68(dword_800BDF4C.f1C_LOAD))
    {
    case 0:
    case 3:
        sub_800BAFB0(dword_800BDF4C.f1C_LOAD);
        PlaySfx_80031494(0x7E);
        if (dword_800BDF4C.fC_LOAD == 0)
        {
            if (sub_800BAE2C() || sub_800BAE3C())
            {
                t->f20_LOAD = 0;
                t->f24_LOAD = 3;
            }
            else
            {
                t->f24_LOAD = 7;
            }
        }
        else if (sub_800BAE3C())
        {
            t->f20_LOAD = 0;
            t->f24_LOAD = 3;
        }
        else
        {
            t->f24_LOAD = 8;
        }
        break;
    case 4:
        if (dword_800BDF4C.fC_LOAD == 0)
        {
            t->f24_LOAD = 2;
        }
        else
        {
            t->f24_LOAD = 0xB;
        }
        break;
    case -1:
        break;
    default:
        t->f24_LOAD = 6;
        break;
    }
}

void sub_800B9470(LoadTask_LOAD* t)
{
    int r = sub_800BAE68(dword_800BDF4C.f1C_LOAD);
    if (r < -1 || (r > 0 && r != 4))
    {
        t->f24_LOAD = 1;
    }
    if (IsCancelPressed_8003D3C0(1, (t->f54_LOAD >> 6) & 1))
    {
        t->f24_LOAD = 1;
    }
    if (IsConfirmPressed_8003D288(1, (t->f54_LOAD >> 6) & 1))
    {
        if (dword_800BDF4C.f2C_LOAD == 0)
        {
            t->f28_LOAD = 4;
        }
        if (dword_800BDF4C.f2C_LOAD == 1)
        {
            t->f24_LOAD = 1;
        }
    }
}

void sub_800B952C(LoadTask_LOAD* t)
{
    int n = dword_800BDF4C.f3D_LOAD + dword_800BDF4C.f3C_LOAD;
    if (IsCancelPressed_8003D3C0(1, (t->f54_LOAD >> 6) & 1))
    {
        t->f24_LOAD = 1;
    }
    if (IsConfirmPressed_8003D288(0, (t->f54_LOAD >> 6) & 1))
    {
        if (dword_800BDF4C.fC_LOAD == 1)
        {
            if (n < t->f20_LOAD - 1)
            {
                if (sub_800BAE4C(n))
                {
                    t->f24_LOAD = 4;
                    PlaySfx_80031494(0x7E);
                }
                else
                {
                    PlaySfx_80031494(0x7C);
                }
            }
            else
            {
                PlaySfx_80031494(0x7C);
            }
        }
        else if (dword_800BDF4C.fC_LOAD == 0)
        {
            if (n < t->f20_LOAD - 1)
            {
                if (!sub_800BAE4C(n) && sub_800BAE2C() <= 0)
                {
                    t->f24_LOAD = 9;
                    PlaySfx_80031494(0x7C);
                }
                else
                {
                    t->f24_LOAD = 4;
                    PlaySfx_80031494(0x7E);
                }
            }
            else
            {
                PlaySfx_80031494(0x7C);
            }
        }
    }
}

void sub_800B9654(LoadTask_LOAD* t)
{
    if (IsCancelPressed_8003D3C0(1, (t->f54_LOAD >> 6) & 1))
    {
        t->f24_LOAD = 3;
    }
    if (IsConfirmPressed_8003D288(0, (t->f54_LOAD >> 6) & 1))
    {
        if (dword_800BDF4C.f4C_LOAD == 0)
        {
            PlaySfx_80031494(0x7E);
            if (dword_800BDF4C.fC_LOAD == 1)
            {
                sub_800BADF4();
                t->f28_LOAD = 3;
            }
            else if (dword_800BDF4C.fC_LOAD == 0)
            {
                sub_800BADF4();
                t->f28_LOAD = 2;
            }
        }
        else
        {
            PlaySfx_80031494(0x7D);
            t->f24_LOAD = 3;
        }
    }
}

INCLUDE_OVERLAY_ASM(load, sub_800B9724);

INCLUDE_OVERLAY_ASM(load, sub_800B98C4);

INCLUDE_OVERLAY_ASM(load, sub_800B9A8C);

INCLUDE_OVERLAY_ASM(load, sub_800BA234);

INCLUDE_OVERLAY_ASM(load, sub_800BA3EC);

void sub_800BA968(int* t)
{
    DrawLoadingIcon_8003CD5C();
    sub_800BACBC(dword_800BDECC);
    DrawMenuBackground_8002BE10();
    t[2] = (int)sub_800BA9AC;
}

void sub_800BA9AC(int* t)
{
    DrawLoadingIcon_8003CD5C();
    sub_800BACBC(dword_800BDECC);
    DrawMenuBackground_8002BE10();
    t[2] = (int)sub_800BA9F0;
}

void sub_800BA9F0(int* t, LoadTask_LOAD* s)
{
    switch (MemCardFormat(stru_800BDF4C[1].fC_LOAD << 4))
    {
    case 0:
        t[2] = (int)sub_800B794C;
        s->f28_LOAD = 0;
        s->f24_LOAD = 3;
        s->f20_LOAD = 0;
        sub_800BAFB0(stru_800BDF4C[1].fC_LOAD);
        s->f5C_LOAD = 0;
        break;
    case 1:
        t[2] = (int)sub_800B794C;
        s->f28_LOAD = 0;
        s->f24_LOAD = 1;
        break;
    case 2:
        t[2] = (int)sub_800B794C;
        s->f28_LOAD = 0;
        s->f24_LOAD = 0xD;
        break;
    case -1:
        break;
    }
    sub_800BADF4();
    DrawLoadingIcon_8003CD5C();
    sub_800BACBC(dword_800BDECC);
    DrawMenuBackground_8002BE10();
}

void sub_800BAAE0(int* t, LoadTask_LOAD* s)
{
    free3_8003FC6C(s->f0_LOAD);
    free3_8003FC6C(s->f4_LOAD);
    dword_800BE184 = 0;
    t[0] = (t[0] & ~1) | 0x8000;
    MemCardStop();
    t[2] = (int)sub_800B7650;
    if (!(s->f54_LOAD & 8))
    {
        FreeActiveOverlay_8002C014();
        if (s->f54_LOAD & 0x20)
        {
            sub_80027314();
            sub_800A6D30(sub_800A6D50(1));
        }
        else if (!(s->f54_LOAD & 4))
        {
            sub_80027314();
            sub_800A6D30(sub_800A6D50(1));
        }
        if (s->f54_LOAD & 1)
        {
            short* m = (short*)&saveData_8008B570;
            m[0x2E2 / 2] = -1;
            m[0x2E6 / 2] = -1;
            m[0x2EA / 2] = -1;
            m[0x2EE / 2] = -1;
            m[0x2F2 / 2] = -1;
            dword_80091C54 = 0;
            if (!(s->f54_LOAD & 4))
            {
                unknownFlags_8008D678 |= 0x18000000;
            }
        }
        if (s->f54_LOAD & 0x10)
        {
            sub_80011BCC();
        }
    }
}

int sub_800BAC14(int n)
{
    return n / 216000 % 60;
}

int sub_800BAC68(int n)
{
    return n / 3600 % 60;
}

void sub_800BACBC(char** lines)
{
    Size_LOAD sz;
    Rect_LOAD r;
    int i;
    sz = MeasureTextLines_8003E3B4((int*)lines);
    r.x_LOAD = (0x13A - sz.w_LOAD) / 2;
    r.y_LOAD = (0xEA - sz.h_LOAD) / 2;
    r.w_LOAD = sz.w_LOAD + 6;
    r.h_LOAD = sz.h_LOAD + 3;
    if (sz.h_LOAD >= 0x10)
    {
        r.h_LOAD = sz.h_LOAD + 6;
    }
    for (i = 0; i < 3; i++)
    {
        if (lines[i])
        {
            Pos_LOAD p;
            p.x_LOAD = r.x_LOAD + 3;
            p.y_LOAD = r.y_LOAD + 5 + i * 13;
            DrawText_8003E91C(2, lines[i], &p, 5);
        }
    }
    {
        Tail4_LOAD b;
        b.c1_LOAD = 1;
        b.c0_LOAD = 0;
        b.s_LOAD = uiColor_8008B590;
        DrawWindow_80042460(&r, &b, dword_8008D454 + 0x38, 0);
    }
}

void sub_800BADE0(unsigned char* p)
{
    p[12] = p[9];
    p[13] = p[10];
}

void sub_800BADF4(void)
{
    int a = 0;
    int b = 0;
    MemCardSync(0, &b, &a);
}

int sub_800BAE24(void)
{
    return 1;
}

int sub_800BAE2C(void)
{
    return dword_800BE14C;
}

int sub_800BAE3C(void)
{
    return dword_800BE150;
}

char* sub_800BAE4C(int i)
{
    char** p = dword_800BE188;
    return p[i];
}

int sub_800BAE68(int a)
{
    int x[2];
    int ret = -1;
    int r;
    int off = a << 4;
    x[0] = 0;
    x[1] = 0;
    r = MemCardSync(1, &x[0], &x[1]);
    switch (r)
    {
    case 0:
        break;
    case -1:
        MemCardAccept(off);
        break;
    case 1:
        if (x[0] == 2)
        {
            ret = x[1];
        }
        break;
    }
    return ret;
}

int sub_800BAF0C(int a)
{
    int x[2];
    int ret = -1;
    int r;
    int off = a << 4;
    x[0] = 0;
    x[1] = 0;
    r = MemCardSync(1, &x[0], &x[1]);
    switch (r)
    {
    case 0:
        break;
    case -1:
        MemCardExist(off);
        break;
    case 1:
        if (x[0] == 1)
        {
            ret = x[1];
        }
        break;
    }
    return ret;
}

#if 0
// Not matched: the original tests the first loop's entry as found < files (slt/beqz on the register copy of 0); this folds it to blez files and swaps which of i/found is copied before the call
void sub_800BAFB0(int slot)
{
    DirEntry_LOAD dir[15];
    long files;
    int blocks;
    int found;
    int i;
    i = found = blocks = 0;
    files = 0;
    MemCardGetDirentry(slot << 4, byte_800B72FC, dir, &files, 0, 15);
    for (; i < files; i++)
    {
        int q = dir[i].size_LOAD / 0x2000;
        if (dir[i].size_LOAD & 0x1FFF)
        {
            blocks += q + 1;
        }
        else
        {
            blocks += q;
        }
    }
    for (i = 0; i < 15; i++)
    {
        if (sub_800BB23C(files, dword_800BE028[0][i], dir))
        {
            found++;
            dword_800BE188[i] = dword_800BE028[0][i];
        }
        else
        {
            dword_800BE188[i] = 0;
        }
    }
    dword_800BE14C = 15 - blocks;
    dword_800BE150 = found;
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BAFB0);

#if 0
// Not matched: same as sub_800BAFB0 (first loop entry test found < files is folded to blez files here)
void sub_800BB0E4(int slot)
{
    DirEntry_LOAD dir[15];
    long files;
    int blocks;
    int found;
    int i;
    i = found = blocks = 0;
    files = 0;
    MemCardGetDirentry(slot << 4, byte_800B72FC, dir, &files, 0, 15);
    for (; i < files; i++)
    {
        int q = dir[i].size_LOAD / 0x2000;
        if (dir[i].size_LOAD & 0x1FFF)
        {
            blocks += q + 1;
        }
        else
        {
            blocks += q;
        }
    }
    for (i = 0; i < 15; i++)
    {
        if (sub_800BB23C(files, dword_800BE028[0][i], dir))
        {
            found++;
            dword_800BE188[i] = dword_800BE028[0][i];
        }
        else if (sub_800BB23C(files, dword_800BE028[1][i], dir))
        {
            found++;
            dword_800BE188[i] = dword_800BE028[1][i];
        }
        else
        {
            dword_800BE188[i] = 0;
        }
    }
    dword_800BE14C = 15 - blocks;
    dword_800BE150 = found;
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BB0E4);

int sub_800BB23C(int n, unsigned char* a, unsigned char* b)
{
    int i;
    int j;
    int diff;
    int res = 0;
    for (i = 0; i < n; i++, b += 0x28)
    {
        diff = 0;
        for (j = 0; j < 0x15; j++)
        {
            if (a[j] == 0)
            {
                break;
            }
            if (a[j] != b[j])
            {
                diff++;
                break;
            }
        }
        if (diff == 0)
        {
            res = 1;
            break;
        }
    }
    return res;
}

INCLUDE_OVERLAY_ASM(load, sub_800BB2AC);

void sub_800BB4A8(short sel)
{
    MenuItems2_LOAD a = dword_800B731C;
    MenuItems2_LOAD b = dword_800B7368;
    MenuItem_LOAD* list[3];
    MenuWin_LOAD w;
    int i;
    list[0] = a.item_LOAD;
    list[1] = b.item_LOAD;
    list[2] = 0;
    w.f0_LOAD = 2;
    w.f4_LOAD = 0;
    w.f8_LOAD = 8;
    w.fC_LOAD = 0;
    w.items_LOAD = list;
    w.f14_LOAD = 0;
    for (i = 0; i < 2; i++)
    {
        list[i]->flags_LOAD |= 2;
    }
    w.f4_LOAD = frameCount_8008D3FC;
    w.fC_LOAD = sel;
    DrawMenuWindows_8002A5A4(&w);
}

// 0x800BB5DC..0x800BD93C is PSY-Q 4.4 library code (LIBMCRD.LIB modules LIBMCRD, USERFUNC and BIOS,
// identical code): not decompiled. It could be linked from the library like the exe's lib code.
INCLUDE_OVERLAY_ASM(load, MemCardStart);

INCLUDE_OVERLAY_ASM(load, MemCardStop);

INCLUDE_OVERLAY_ASM(load, MemCardExist);

INCLUDE_OVERLAY_ASM(load, sub_800BB6F4);

INCLUDE_OVERLAY_ASM(load, MemCardAccept);

INCLUDE_OVERLAY_ASM(load, sub_800BBA5C);

INCLUDE_OVERLAY_ASM(load, MemCardOpen);

INCLUDE_OVERLAY_ASM(load, MemCardClose);

INCLUDE_OVERLAY_ASM(load, MemCardReadData);

INCLUDE_OVERLAY_ASM(load, sub_800BBF88);

INCLUDE_OVERLAY_ASM(load, MemCardWriteData);

INCLUDE_OVERLAY_ASM(load, sub_800BC17C);

INCLUDE_OVERLAY_ASM(load, MemCardReadFile);

INCLUDE_OVERLAY_ASM(load, sub_800BC3D0);

INCLUDE_OVERLAY_ASM(load, MemCardWriteFile);

INCLUDE_OVERLAY_ASM(load, sub_800BC628);

INCLUDE_OVERLAY_ASM(load, MemCardGetDirentry);

INCLUDE_OVERLAY_ASM(load, MemCardCallback);

INCLUDE_OVERLAY_ASM(load, MemCardSync);

INCLUDE_OVERLAY_ASM(load, MemCardCreateFile);

INCLUDE_OVERLAY_ASM(load, MemCardDeleteFile);

INCLUDE_OVERLAY_ASM(load, MemCardFormat);

INCLUDE_OVERLAY_ASM(load, MemCardUnformat);

INCLUDE_OVERLAY_ASM(load, sub_800BD018);

INCLUDE_OVERLAY_ASM(load, sub_800BD06C);

INCLUDE_OVERLAY_ASM(load, sub_800BD118);

INCLUDE_OVERLAY_ASM(load, sub_800BD174);

INCLUDE_OVERLAY_ASM(load, UserFuncInit);

INCLUDE_OVERLAY_ASM(load, UserFuncOpen);

INCLUDE_OVERLAY_ASM(load, UserFuncExecute);

unsigned UserFuncComplete(void)
{
    return (unsigned)dword_800BE174 >> 31;
}

INCLUDE_OVERLAY_ASM(load, sub_800BD284);

INCLUDE_OVERLAY_ASM(load, funcEvSpIOE);

INCLUDE_OVERLAY_ASM(load, funcEvSpError);

INCLUDE_OVERLAY_ASM(load, funcEvSpTimeout);

INCLUDE_OVERLAY_ASM(load, funcEvSpNewcard);

INCLUDE_OVERLAY_ASM(load, funcEvSpIOEx);

INCLUDE_OVERLAY_ASM(load, funcEvSpErrorx);

INCLUDE_OVERLAY_ASM(load, funcEvSpTimeoutx);

INCLUDE_OVERLAY_ASM(load, funcEvSpNewcardx);

INCLUDE_OVERLAY_ASM(load, _card_open);

INCLUDE_OVERLAY_ASM(load, _card_start);

INCLUDE_OVERLAY_ASM(load, _card_close);

INCLUDE_OVERLAY_ASM(load, _card_stop);

INCLUDE_OVERLAY_ASM(load, _clr_card_event);

INCLUDE_OVERLAY_ASM(load, _get_card_event);

INCLUDE_OVERLAY_ASM(load, _get_card_event_x);

INCLUDE_OVERLAY_ASM(load, _chk_card_event);

INCLUDE_OVERLAY_ASM(load, _chk_card_event_x);

INCLUDE_OVERLAY_ASM(load, dword_800BD93C);
