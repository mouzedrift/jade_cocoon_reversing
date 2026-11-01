// TITLE.BIN - loaded at 0x800A05A0
#include "common.h"
#include "funcs.h"
#include "globals.h"



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

INCLUDE_OVERLAY_ASM(title, sub_800A166C);

INCLUDE_OVERLAY_ASM(title, sub_800A1728);

INCLUDE_OVERLAY_ASM(title, sub_800A1760);

INCLUDE_OVERLAY_ASM(title, sub_800A1780);

INCLUDE_OVERLAY_ASM(title, sub_800A1AC0);

INCLUDE_OVERLAY_ASM(title, sub_800A1AFC);

INCLUDE_OVERLAY_ASM(title, sub_800A1B74);

INCLUDE_OVERLAY_ASM(title, sub_800A1BCC);

INCLUDE_OVERLAY_ASM(title, sub_800A1C18);

INCLUDE_OVERLAY_ASM(title, sub_800A1C7C);

INCLUDE_OVERLAY_ASM(title, sub_800A1CC0);

INCLUDE_OVERLAY_ASM(title, sub_800A1D6C);

INCLUDE_OVERLAY_ASM(title, sub_800A1D8C);

INCLUDE_OVERLAY_ASM(title, sub_800A1DD8);

INCLUDE_OVERLAY_ASM(title, sub_800A1E24);

INCLUDE_OVERLAY_ASM(title, sub_800A1E9C);

INCLUDE_OVERLAY_ASM(title, sub_800A1F00);

extern void sub_800A1AFC(void* a, int b);
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
#define SDECL char* s = SBASE; __asm__("" : "+r"(s))
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
    sub_80040298((void*)pOT_8008D3EC, e5, 5);
    sub_80040298((void*)pOT_8008D3EC, q + 0x28, 2);
    y = 0;
    for (i = 7; i < 9; i++)
    {
        e = (Sprite20_*)((int)i * 20 + (int)p);
        e->x_8 = (i - 7) * 5 << 5;
        e->y_A = y;
        sub_80040298((void*)pOT_8008D3EC, e, 5);
        sub_80040298((void*)pOT_8008D3EC, q + i * 8, 2);
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
// Not matched: saveData base register is derived from the playerYan base in the original (addiu a0,v0,-0x24) but late
void sub_800A22FC(void)
{
    playerYan_8008B594 = 0x64;
    {
        char* b = (char*)&playerYan_8008B594;
        char* s = SBASE;
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
}
#endif
INCLUDE_OVERLAY_ASM(title, sub_800A22FC);

#if 0
// Not matched: last two loops are not strength reduced to a pointer
void sub_800A2358(void)
{
    char* b = SA(0x8008B594);
    int i;
    *(int*)b = 0;
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
    for (i = 0x12; i >= 0; i--)
    {
        b[0x290 + i] = 0;
    }
    for (i = 0x13; i >= 0; i--)
    {
        b[0x2A3 + i] = 0;
    }
}
#endif
INCLUDE_OVERLAY_ASM(title, sub_800A2358);

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
