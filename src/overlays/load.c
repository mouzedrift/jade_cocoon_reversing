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
extern int dword_800BE188[];
extern int dword_800BE2C4;
extern int dword_800BE2C8;
extern int dword_800BE2CC;
extern int dword_800BE2D0;
extern int dword_800BE2D4;
extern int dword_800BE2D8;
extern int dword_800BE2DC;
extern int dword_800BE2E0;
extern int** dword_8008D480;
extern int sub_8004EE8C(void);
extern void sub_8004EDE8(void);
extern void sub_8004EE54(void);
extern int sub_8004EDD8(void);
extern int sub_800BC9DC(int a, int* b, int* c);
extern void sub_800BB9F4();
extern void sub_800BB68C();
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
extern int dword_8008B4E8;
extern int dword_8008B570[];
extern unsigned char byte_800BDF58;
extern int dword_800BE208;
extern char dword_800BDECC[];
extern void sub_8003CD5C(int* t);
extern void sub_8002BE10(void);
extern void sub_800BACBC(void* p);
extern void sub_800B794C(int* t);
extern void sub_800BA9AC(int* t);
extern void sub_800BA9F0(int* t);
extern void sub_8004F5E8(int a);
extern void sub_80056FEC(int a, int b);
extern void sub_800BD558(void);
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
extern int sub_8004DE68(void);
extern void sub_8004DE38(int a);
extern void sub_8004DE78(void);
extern void sub_800BD60C(void);
extern int sub_800BD7EC(void);
extern void sub_8004FA18(void);
extern void sub_8004FA08(int a, int b, void* c);
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
extern Bytes8_LOAD dword_800B6B94;
extern unsigned short word_8008B590;
extern char* dword_8008D454;
extern void sub_8002C06C(void* a, int b, int c);
extern void sub_80042460(void* a, void* b, void* c, int d);
typedef struct
{
    char pad0_LOAD[0x24];
    int f24_LOAD;
    int f28_LOAD;
    char pad2C_LOAD[0x28];
    unsigned f54_LOAD;
} LoadTask_LOAD;
extern int sub_8003D288(int a, int b);
extern int sub_8003D3C0(int a, int b);
extern void sub_800BD18C(void* fn, int a);
extern void sub_800BB6F4(void);
extern void sub_800BBA5C(void);
extern char byte_800B73A0[];
extern char byte_800B7544[];
typedef struct
{
    unsigned char pad0_LOAD[0x1C];
    unsigned char f1C_LOAD;
    unsigned char pad1D_LOAD[0xF];
    unsigned char f2C_LOAD;
} Opts_LOAD;
extern Opts_LOAD dword_800BDF4C;
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
    if (dword_8008B4E8)
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

INCLUDE_OVERLAY_ASM(load, sub_800B794C);

INCLUDE_OVERLAY_ASM(load, sub_800B79F8);

INCLUDE_OVERLAY_ASM(load, sub_800B80F8);

INCLUDE_OVERLAY_ASM(load, sub_800B82FC);

INCLUDE_OVERLAY_ASM(load, sub_800B847C);

INCLUDE_OVERLAY_ASM(load, sub_800B85AC);

INCLUDE_OVERLAY_ASM(load, sub_800B867C);

INCLUDE_OVERLAY_ASM(load, sub_800B877C);

void sub_800B8984(void)
{
    Bytes8_LOAD a;
    Tail4_LOAD b;
    sub_8002C06C(&dword_800BD998[byte_800BDF58], dword_800BD998[byte_800BDF58].f4_LOAD, dword_800BD998[byte_800BDF58].f6_LOAD);
    a = dword_800B6B8C;
    b.c1_LOAD = 1;
    b.c0_LOAD = 0;
    b.s_LOAD = word_8008B590;
    sub_80042460(&a, &b, dword_8008D454 + 0x38, 0);
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
    sub_8002C06C(&p0, 0x27, 1);
    p1.x_LOAD = 0x124;
    p1.y_LOAD = 0x15;
    sub_8002C06C(&p1, (byte_800BDF68 == 1) << 1, 1);
    a = dword_800B6B94;
    b.c1_LOAD = 1;
    b.c0_LOAD = 0;
    b.s_LOAD = word_8008B590;
    sub_80042460(&a, &b, dword_8008D454 + 0x38, 0);
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800B8A20);

INCLUDE_OVERLAY_ASM(load, sub_800B8AE4);

INCLUDE_OVERLAY_ASM(load, sub_800B8BD4);

void sub_800B9220(LoadTask_LOAD* t)
{
    if (sub_8003D288(1, (t->f54_LOAD >> 6) & 1))
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
    else if (sub_8003D3C0(1, (t->f54_LOAD >> 6) & 1))
    {
        t->f28_LOAD = 5;
    }
}

INCLUDE_OVERLAY_ASM(load, sub_800B92C0);

INCLUDE_OVERLAY_ASM(load, sub_800B9360);

void sub_800B9470(LoadTask_LOAD* t)
{
    int r = sub_800BAE68(dword_800BDF4C.f1C_LOAD);
    if (r < -1 || (r > 0 && r != 4))
    {
        t->f24_LOAD = 1;
    }
    if (sub_8003D3C0(1, (t->f54_LOAD >> 6) & 1))
    {
        t->f24_LOAD = 1;
    }
    if (sub_8003D288(1, (t->f54_LOAD >> 6) & 1))
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

INCLUDE_OVERLAY_ASM(load, sub_800B952C);

INCLUDE_OVERLAY_ASM(load, sub_800B9654);

INCLUDE_OVERLAY_ASM(load, sub_800B9724);

INCLUDE_OVERLAY_ASM(load, sub_800B98C4);

INCLUDE_OVERLAY_ASM(load, sub_800B9A8C);

INCLUDE_OVERLAY_ASM(load, sub_800BA234);

INCLUDE_OVERLAY_ASM(load, sub_800BA3EC);

void sub_800BA968(int* t)
{
    sub_8003CD5C(t);
    sub_800BACBC(dword_800BDECC);
    sub_8002BE10();
    t[2] = (int)sub_800BA9AC;
}

void sub_800BA9AC(int* t)
{
    sub_8003CD5C(t);
    sub_800BACBC(dword_800BDECC);
    sub_8002BE10();
    t[2] = (int)sub_800BA9F0;
}

INCLUDE_OVERLAY_ASM(load, sub_800BA9F0);

INCLUDE_OVERLAY_ASM(load, sub_800BAAE0);

int sub_800BAC14(int n)
{
    return n / 216000 % 60;
}

int sub_800BAC68(int n)
{
    return n / 3600 % 60;
}

INCLUDE_OVERLAY_ASM(load, sub_800BACBC);

void sub_800BADE0(unsigned char* p)
{
    p[12] = p[9];
    p[13] = p[10];
}

void sub_800BADF4(void)
{
    int a = 0;
    int b = 0;
    sub_800BC9DC(0, &b, &a);
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

int sub_800BAE4C(int i)
{
    int* p = dword_800BE188;
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
    r = sub_800BC9DC(1, &x[0], &x[1]);
    switch (r)
    {
    case 0:
        break;
    case -1:
        sub_800BB9F4(off);
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
    r = sub_800BC9DC(1, &x[0], &x[1]);
    switch (r)
    {
    case 0:
        break;
    case -1:
        sub_800BB68C(off);
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

INCLUDE_OVERLAY_ASM(load, sub_800BAFB0);

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

INCLUDE_OVERLAY_ASM(load, sub_800BB4A8);

INCLUDE_OVERLAY_ASM(load, sub_800BB5DC);

#if 0
// Not matched: the original keeps the address of the state field in a register (la); psyq 4.4 folds it into the offsets
void sub_800BB64C(void)
{
    LoadState_LOAD* st = &dword_800BE1F4;
    while (st->f0_LOAD)
    {
    }
    sub_80056FEC(7, 0);
    sub_800BD558();
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BB64C);

#if 0
// Not matched: the original keeps the address of the state struct in a register (la); the compiler folds it
int sub_800BB68C(int a)
{
    if (dword_800BE1F4.f0_LOAD > 0)
    {
        printf(byte_800B73A0);
        return 0;
    }
    dword_800BE1F4.f0_LOAD = 1;
    dword_800BE1F4.f4_LOAD = 0;
    dword_800BE1F4.f8_LOAD = 0;
    dword_800BE1F4.f10_LOAD = a;
    sub_800BD18C(sub_800BB6F4, a);
    return 1;
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BB68C);

INCLUDE_OVERLAY_ASM(load, sub_800BB6F4);

#if 0
// Not matched: same as sub_800BB68C
int sub_800BB9F4(int a)
{
    if (dword_800BE1F4.f0_LOAD > 0)
    {
        printf(byte_800B73A0);
        return 0;
    }
    dword_800BE1F4.f0_LOAD = 2;
    dword_800BE1F4.f4_LOAD = 0;
    dword_800BE1F4.f8_LOAD = 0;
    dword_800BE1F4.f10_LOAD = a;
    sub_800BD18C(sub_800BBA5C, a);
    return 1;
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BB9F4);

INCLUDE_OVERLAY_ASM(load, sub_800BBA5C);

INCLUDE_OVERLAY_ASM(load, sub_800BBD04);

#if 0
// Not matched: same: la of the global kept in $s0
void sub_800BBE8C(void)
{
    int* p = &dword_800BE208;
    if (*p >= 0)
    {
        sub_8004F5E8(*p);
        *p = -1;
    }
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BBE8C);

#if 0
// Not matched: the original addresses the state through a register holding &state.f14 (negative offsets); psyq 4.4 uses &state
int sub_800BBED0(int a, int b, int c)
{
    char* msg;
    if (dword_800BE1F4.f14_LOAD < 0)
    {
        msg = byte_800B74C4;
    }
    else if (dword_800BE1F4.f0_LOAD > 0)
    {
        msg = byte_800B73A0;
    }
    else if (c & 0x7F)
    {
        msg = byte_800B74E8;
    }
    else if (b & 0x7F)
    {
        msg = byte_800B7514;
    }
    else
    {
        dword_800BE1F4.f0_LOAD = 5;
        dword_800BE1F4.f4_LOAD = 0;
        dword_800BE1F4.f8_LOAD = 0;
        dword_800BE1F4.f18_LOAD = b;
        dword_800BE1F4.f20_LOAD = a;
        dword_800BE1F4.f1C_LOAD = c;
        sub_800BD18C(sub_800BBF88, b);
        return 1;
    }
    printf(msg);
    return 0;
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BBED0);

INCLUDE_OVERLAY_ASM(load, sub_800BBF88);

#if 0
// Not matched: same as sub_800BBED0
int sub_800BC0C4(int a, int b, int c)
{
    char* msg;
    if (dword_800BE1F4.f14_LOAD < 0)
    {
        msg = byte_800B74C4;
    }
    else if (dword_800BE1F4.f0_LOAD > 0)
    {
        msg = byte_800B73A0;
    }
    else if (c & 0x7F)
    {
        msg = byte_800B74E8;
    }
    else if (b & 0x7F)
    {
        msg = byte_800B7514;
    }
    else
    {
        dword_800BE1F4.f0_LOAD = 6;
        dword_800BE1F4.f4_LOAD = 0;
        dword_800BE1F4.f8_LOAD = 0;
        dword_800BE1F4.f18_LOAD = b;
        dword_800BE1F4.f20_LOAD = a;
        dword_800BE1F4.f1C_LOAD = c;
        sub_800BD18C(sub_800BC17C, b);
        return 1;
    }
    printf(msg);
    return 0;
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BC0C4);

INCLUDE_OVERLAY_ASM(load, sub_800BC17C);

INCLUDE_OVERLAY_ASM(load, sub_800BC2B8);

INCLUDE_OVERLAY_ASM(load, sub_800BC3D0);

INCLUDE_OVERLAY_ASM(load, sub_800BC510);

INCLUDE_OVERLAY_ASM(load, sub_800BC628);

INCLUDE_OVERLAY_ASM(load, sub_800BC768);

// Not matched: the original keeps &var in a register (lui/addiu) for the load and the store
INCLUDE_OVERLAY_ASM(load, sub_800BC9C8);

INCLUDE_OVERLAY_ASM(load, sub_800BC9DC);

INCLUDE_OVERLAY_ASM(load, sub_800BCAF8);

INCLUDE_OVERLAY_ASM(load, sub_800BCCF4);

INCLUDE_OVERLAY_ASM(load, sub_800BCEA8);

#if 0
// Not matched: the original keeps the address of the state struct in a register (la) and fills the buffer with a decrementing pointer
int sub_800BCF64(int a)
{
    char buf[128];
    int i;
    if (dword_800BE1F4.f0_LOAD)
    {
        printf(byte_800B7544);
        return -1;
    }
    for (i = 127; i >= 0; i--)
    {
        buf[i] = -1;
    }
    for (i = 0; i < 15; i++)
    {
        sub_800BD60C();
        sub_8004FA18();
        sub_8004FA08(a, i, buf);
        if (sub_800BD7EC())
        {
            return 0;
        }
    }
    return 1;
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BCF64);

#if 0
// Not matched: branch order differs
int sub_800BD018(int a)
{
    int r = 0;
    if (a == 1)
    {
        r = 2;
    }
    else if (a < 2)
    {
        if (a != 0)
        {
            r = a | 0x8000;
        }
    }
    else if (a == 2)
    {
        r = 1;
    }
    else if (a == 4)
    {
        r = 3;
    }
    else
    {
        r = a | 0x8000;
    }
    return r;
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BD018);

#if 0
// Not matched: the copied pair and the counters are reloaded separately
void sub_800BD06C(void)
{
    if (!sub_800BD274())
    {
        sub_800BD208();
        if (sub_800BD274())
        {
            dword_800BE1F4.f8_LOAD = 1;
            dword_800BE1E4[0] = dword_800BE1F4.f0_LOAD;
            dword_800BE1E4[1] = dword_800BE1F4.f4_LOAD;
            dword_800BE1F4.f0_LOAD = 0;
            dword_800BE1F4.f4_LOAD = 0;
            if (dword_800BE1F4.f44_LOAD)
            {
                ((void (*)(int, int))dword_800BE1F4.f44_LOAD)(dword_800BE1E4[0], dword_800BE1E4[1]);
            }
        }
    }
    dword_800BE1F4.f50_LOAD++;
    dword_800BE1F4.f54_LOAD++;
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BD06C);

#if 0
// Not matched: the original moves both arguments to $a2/$a3 before the 6 byte block copy
void sub_800BD118(int n, Bytes6_LOAD* out)
{
    *out = dword_800B7624;
    out->c_LOAD[2] = (n / 16) + 0x30;
    out->c_LOAD[3] = (n % 16) + 0x30;
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BD118);

INCLUDE_OVERLAY_ASM(load, sub_800BD174);

// Not decompilable as plain C: the store is "sw $v0,sym" (lui $at) in the delay slot, as hand-written asm does
INCLUDE_OVERLAY_ASM(load, sub_800BD17C);

#if 0
// Not matched: address computation of the clearing loop differs
void sub_800BD18C(void* fn, int a)
{
    int n = dword_800BE174 + 1;
    int i;
    if (n >= 4)
    {
        printf(byte_800B7630);
        return;
    }
    dword_800BE174 = n;
    dword_800BE294[n] = (int (*)())fn;
    for (i = 3; i >= 0; i--)
    {
        dword_800BE254[n * 4 + i] = 0;
    }
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BD18C);

#if 0
// Not matched: the symbol address is reloaded (lui) instead of kept in a saved register
void sub_800BD208(void)
{
    int i = dword_800BE174;
    if (i >= 0)
    {
        if (dword_800BE294[i](dword_800BE254 + i * 16))
        {
            dword_800BE174 = dword_800BE174 - 1;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BD208);

unsigned sub_800BD274(void)
{
    return (unsigned)dword_800BE174 >> 31;
}

INCLUDE_OVERLAY_ASM(load, sub_800BD284);

// Not decompilable as plain C: the store is "sw $v0,sym" (lui $at) in the delay slot, as hand-written asm does
INCLUDE_OVERLAY_ASM(load, sub_800BD2A0);

// Not decompilable as plain C: the store is "sw $v0,sym" (lui $at) in the delay slot, as hand-written asm does
INCLUDE_OVERLAY_ASM(load, sub_800BD2B4);

// Not decompilable as plain C: the store is "sw $v0,sym" (lui $at) in the delay slot, as hand-written asm does
INCLUDE_OVERLAY_ASM(load, sub_800BD2C8);

INCLUDE_OVERLAY_ASM(load, sub_800BD2DC);

INCLUDE_OVERLAY_ASM(load, sub_800BD2F0);

// Not decompilable as plain C: the store is "sw $v0,sym" (lui $at) in the delay slot, as hand-written asm does
INCLUDE_OVERLAY_ASM(load, sub_800BD304);

// Not decompilable as plain C: the store is "sw $v0,sym" (lui $at) in the delay slot, as hand-written asm does
INCLUDE_OVERLAY_ASM(load, sub_800BD318);

#if 0
// Not matched: epilogue order differs (addiu sp before jr, nop in delay slot)
int sub_800BD32C(void)
{
    sub_8004EDE8();
    sub_8004EE54();
    return sub_8004EDD8();
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BD32C);

INCLUDE_OVERLAY_ASM(load, sub_800BD35C);

#if 0
// Not matched: epilogue order differs
int sub_800BD538(void)
{
    return sub_8004EE8C();
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BD538);

#if 0
// Not matched: register allocation of the lui/lw pairs differs ($a0 in the original)
void sub_800BD558(void)
{
    int r = sub_8004DE68();
    sub_8004DE38(dword_800BE2A4);
    sub_8004DE38(dword_800BE2A8);
    sub_8004DE38(dword_800BE2AC);
    sub_8004DE38(dword_800BE2B0);
    sub_8004DE38(dword_800BE2B4);
    sub_8004DE38(dword_800BE2B8);
    sub_8004DE38(dword_800BE2BC);
    sub_8004DE38(dword_800BE2C0);
    if (r == 1)
    {
        sub_8004DE78();
    }
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BD558);

INCLUDE_OVERLAY_ASM(load, sub_800BD60C);

INCLUDE_OVERLAY_ASM(load, sub_800BD714);

INCLUDE_OVERLAY_ASM(load, sub_800BD7EC);

#if 0
// Not matched: load scheduling differs
int sub_800BD8C4(void)
{
    return dword_800BE2C4 + dword_800BE2C8 * 2 + dword_800BE2CC * 4 + dword_800BE2D0 * 8;
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BD8C4);

#if 0
// Not matched: load scheduling differs
int sub_800BD900(void)
{
    return dword_800BE2D4 + dword_800BE2D8 * 2 + dword_800BE2DC * 4 + dword_800BE2E0 * 8;
}
#endif
INCLUDE_OVERLAY_ASM(load, sub_800BD900);

INCLUDE_OVERLAY_ASM(load, dword_800BD93C);
