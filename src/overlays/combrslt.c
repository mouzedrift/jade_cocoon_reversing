// COMBRSLT.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct CombRsltTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombRsltTask;

typedef struct CombRsltBox
{
    short col_0;
    char c_2;
    char c_3;
} CombRsltBox;

// sub_8002ADB4's text window (0x1C bytes)
typedef struct CombRsltText
{
    unsigned short flags_0;
    short s_2;
    int ptr_4;
    int pad_8[2];
    short x_10;
    short y_12;
    int pad_14[2];
} CombRsltText;

extern CombRsltText dword_800A408C;
extern unsigned short uiColor_8008B590;
extern char dword_80082680[];
extern void sub_8002ADB4(void*, void*, int, int);
extern void DrawButtonHelpBar_8002B004(void*, int, int);
extern void sub_800A41E4();
extern void DrawSmallNumber3_8002C290(void*, int, int);
extern void DrawUiTiySprt_8002C06C(void*, int, int);
extern void sub_800A16FC();
extern void SetFadeMode_8001C19C(int, int);
extern void sub_800A4240(int);
extern void DrawMenuBackground_8002BE10();

INCLUDE_OVERLAY_ASM(combrslt, dword_800A4088);

void sub_800A40E0(CombRsltTask* t)
{
    CombRsltBox box;
    CombRsltText str = dword_800A408C;
    int i;
    box.c_2 = 0;
    box.c_3 = 1;
    box.col_0 = uiColor_8008B590;
    sub_8002ADB4(&str, &box, 0xF, 0);
    for (i = 0; i < 2; i++)
    {
        sub_800A4240(i);
    }
    DrawMenuBackground_8002BE10();
    DrawButtonHelpBar_8002B004(dword_80082680, 0, 0xF);
    if (IsConfirmPressedP1_8003D380(1) || IsCancelPressedP1_8003D41C(1))
    {
        SetFadeMode_8001C19C(1, 0x20);
        t->next_8 = sub_800A41E4;
    }
}

void sub_800A41E4(CombRsltTask* t, int a)
{
    if (IsFadeDone_8001C2FC() == 1)
    {
        SetFadeMode_8001C19C(3, 0x20);
        t->next_8 = sub_800A16FC;
        t->next_8(t, a);
    }
}

extern unsigned char byte_800A3A98[];
extern unsigned char byte_800A3A90[];
extern int* dword_800A4830[];
extern int* dword_800A4870[];
extern unsigned short* dword_800A48B0[];
typedef struct CombRsltEnt
{
    char pad_0[0xA];
    short idx_A;
} CombRsltEnt;
extern CombRsltEnt dword_800A47E8[];
extern void sub_800A444C();
extern void sub_800A4554();

void sub_800A4240(int i)
{
    CombRsltBox box;
    short pos[2];
    int j;
    int u;
    int t = byte_800A3A98[i];
    switch (t)
    {
    case 0:
        dword_800A4870[i][1] = 0xE6;
        box.c_2 = 1;
        break;
    case 1:
        dword_800A4870[i][1] = 0x68;
        box.c_2 = 2;
        break;
    case 2:
        dword_800A4870[i][1] = 0x41;
        box.c_2 = 2;
        break;
    }
    box.col_0 = uiColor_8008B590;
    box.c_3 = 1;
    sub_8002ADB4(dword_800A4830[i], &box, 0xF, GetTime30Hz_8002C64C());
    sub_8002ADB4(dword_800A4870[i], &box, 0xF, GetTime30Hz_8002C64C());
    pos[0] = dword_800A48B0[i][8];
    pos[1] = dword_800A48B0[i][9];
    sub_800A444C(pos, 0xF, byte_800A3A90[i ^ 1], byte_800A3A90[i]);
    sub_8002ADB4(dword_800A48B0[i], &box, 0xF, GetTime30Hz_8002C64C());
    j = 0;
    u = byte_800A3A98[i];
    if (u < 3 && u != 0)
        box.c_2 = 0;
    for (j = 0; j < 3; j++)
        sub_800A4554(i, j + dword_800A47E8[0].idx_A, &box);
}

// Near miss: scheduling of the repeated x/y stores
// Matched
void sub_800A444C(unsigned short* p, int a, int b, int c)
{
    short v[2];
    {
        unsigned int x;
        unsigned int y;
        x = p[0];
        v[0] = x + 0x1C;
        y = p[1];
        v[1] = y + 4;
        v[0] = x + 0x12;
        v[1] = y + 7;
        DrawSmallNumber3_8002C290(v, b, a);
    }
    {
        unsigned int x;
        unsigned int y;
        x = p[0];
        v[0] = x + 0x1C;
        y = p[1];
        v[0] = x + 0x14;
        v[1] = y + 5;
        DrawUiTiySprt_8002C06C(v, 0xAE, a);
    }
    {
        unsigned int x;
        unsigned int y;
        x = p[0];
        v[0] = x + 0x43;
        y = p[1];
        v[1] = y + 4;
        v[0] = x + 0x39;
        v[1] = y + 7;
        DrawSmallNumber3_8002C290(v, c, a);
    }
    {
        unsigned int x;
        unsigned int y;
        x = p[0];
        v[0] = x + 0x43;
        y = p[1];
        v[0] = x + 0x3B;
        v[1] = y + 5;
        DrawUiTiySprt_8002C06C(v, 0x4D, a);
    }
}

typedef struct CombRsltPos
{
    unsigned short x;
    unsigned short y;
} CombRsltPos;

extern CombRsltText dword_800A40A8;
extern CombRsltText dword_800A40C4;
extern int* dword_800A48B8[];
extern CombRsltPos dword_800A48C4[];
extern char byte_800A3AA0[];

extern int sub_800A1958();
extern int sub_800A1934();
extern void sub_800A1844();
extern void DrawHpGauge_8002F078();
extern void DrawWindow_80042460();

// Near miss: register allocation of the q / j*4 address computation
#if 0
void sub_800A4554(int i, int j, void* arg)
{
    CombRsltText a = dword_800A40A8;
    CombRsltText b;
    CombRsltPos r1;
    CombRsltPos r2;
    CombRsltPos r3[2];
    CombRsltPos* q;
    char* e;
    int on;
    if (sub_800A1958(byte_800A3AA0 + i * 744 + j * 248))
    {
        a.flags_0 |= 2;
        on = 1;
    }
    else
    {
        on = 0;
        a.flags_0 &= ~2;
    }
    e = byte_800A3AA0 + i * 744 + j * 248;
    if (sub_800A1934(e) != 1)
    {
        a.ptr_4 = (int)dword_800A48B8[j];
        q = dword_800A48C4 + j + i * 3;
        a.x_10 = q->x;
        a.y_12 = q->y;
        sub_8002ADB4(&a, arg, 0xF, GetTime30Hz_8002C64C());
        b = dword_800A40C4;
        b.x_10 = q->x + 0x32;
        b.y_12 = q->y;
        if (!on)
        {
            r1.x = q->x + 0x2F;
            r1.y = q->y;
            DrawHpGauge_8002F078(e + 0x84, &r1, 0, 0xF);
            b.s_2 = 0;
        }
        sub_8002ADB4(&b, arg, 0xF, GetTime30Hz_8002C64C());
        r2.x = q->x;
        r2.y = q->y + 0x14;
        sub_800A1844(e, &r2, a.flags_0);
        r3[0].x = q->x;
        r3[0].y = q->y + 0x14;
        r3[1].x = 0x90;
        r3[1].y = 0x13;
        DrawWindow_80042460(r3, arg, pOT_8008D454 + 15, GetTime30Hz_8002C64C());
    }
}
#endif
INCLUDE_OVERLAY_ASM(combrslt, sub_800A4554);

INCLUDE_OVERLAY_ASM(combrslt, dword_800A47E8);
