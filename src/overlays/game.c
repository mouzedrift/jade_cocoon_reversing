// GAME.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
typedef struct GameFlagObj_1
{
    unsigned int* flags_0;
    int pad_4;
    int** f8;
    char pad_c[0x14];
    int f20;
} GameFlagObj_1;
typedef struct GameHolder_1
{
    int f0;
    GameFlagObj_1* f4;
} GameHolder_1;
typedef struct GameRec_1
{
    int f0, f4, f8, fc, f10;
} GameRec_1;
typedef struct GameV3_1
{
    int a, b, c;
} GameV3_1;
typedef struct GameSlot_1
{
    int f0;
    char pad_4[0xe4];
} GameSlot_1;
typedef struct GameEnt_1
{
    char pad_0[0x5c];
    int f5c;
    char pad_60[0x28];
} GameEnt_1;
extern void sub_800A2D28(GameFlagObj_1* p);
extern void sub_800A2EC8(GameFlagObj_1* p);
extern void FreeActiveOverlay_8002C014(void);
extern void sub_80030664(void);
extern GameRec_1 dword_800ADE78;
extern int dword_800AEB6C[];
typedef struct GameR6_1
{
    char pad_0[0x120];
    int f120;
} GameR6_1;
typedef struct GameR5_1
{
    char pad_0[0x14];
    GameR6_1* f14;
} GameR5_1;
extern int* sub_800A59D0(int a);
extern int sub_800B76B8(char* p);
extern int dword_800B1260[];
extern GameEnt_1 dword_800B130C[];
extern GameSlot_1 dword_800B19F0[];
extern void sub_800A2D48(GameFlagObj_1* p);
extern void sub_800A2CA8(int, int);
extern void sub_8001D600(int** p);
extern char* dword_8008B520;
extern void sub_800A170C(void);
extern void sub_800A2CA8(int, int);
extern int sub_800A7A60(void);
extern char dword_800B19CC[];
extern int dword_800B1D98;
extern int dword_800AEBF0;
extern int dword_800B0EC0;
extern int dword_800B0EC4[];
extern int dword_800AEBF4;
extern int sub_800A77F4(int a);
extern int dword_800AEBD8;
extern int dword_800B19E0;
extern int dword_800B1DBC;
extern int dword_800B0698;
extern int dword_800AEBE0;
extern char dword_800B1CB8[];
extern char* dword_8008B518;
extern char* dword_8008B534;
extern int* dword_8008D46C;
extern int* dword_800B1264;
typedef struct GameVec3_1
{
    int x, y, z;
} GameVec3_1;
typedef struct GameTask_1
{
    int f0;
    int f4;
    void (*next_8)();
} GameTask_1;
typedef struct GameCb_1
{
    char pad_0[0xc];
    int (*cb_c)();
    void (*cb_10)();
} GameCb_1;
typedef struct GameSub_1
{
    int f0;
    int f4;
    int f8;
    int fc;
} GameSub_1;
extern int sub_8001E1DC(struct_obj_A* p);
extern void sub_80018EBC(int a, int b);
extern void sub_80018E5C(int a, int b);
extern void sub_8001D760(int** a, int b, int c, int d);
extern int sub_800A52EC(void* a, int b, int c);
extern void* sub_80020D1C(int a, int b);
extern void sub_800A76D8();
extern void sub_800B78B8(int a);
extern void sub_800B78D0();
extern int sub_800A7790(void);
extern int sub_800A77F4(int a);
extern char dword_800AE254[];
extern void sub_800A170C(void);
extern void sub_800A2CA8(int, int);
extern int sub_800A7A60(void);
extern char dword_800B19CC[];
extern int dword_800B1D98;
extern int dword_800AEBF0;
extern int dword_800B0EC0;
extern int dword_800B0EC4[];
extern int dword_800AEBF4;
extern int dword_800AEBD8;
extern int dword_800B19E0;
extern int dword_800B1DBC;
extern int dword_800B0698;
extern int dword_800AEBE0;

INCLUDE_OVERLAY_ASM(game, dword_800A05A0);

// Matched
void sub_800A096C(void)
{
    unknownFlags_8008D678 |= 0x8000;
}

// Matched
void sub_800A0988(void)
{
    *(unsigned short*)(*(int*)(dword_800B1DBC + 0x24)) |= 1;
}

// Matched
void sub_800A09B0(void)
{
    *(unsigned short*)(*(int*)(dword_800B1DBC + 0x24)) &= 0xFFFE;
}

INCLUDE_OVERLAY_ASM(game, sub_800A09D8);

INCLUDE_OVERLAY_ASM(game, sub_800A0A04);

INCLUDE_OVERLAY_ASM(game, sub_800A0A5C);

INCLUDE_OVERLAY_ASM(game, sub_800A1314);

INCLUDE_OVERLAY_ASM(game, sub_800A13B8);

// Matched
void sub_800A1444(void)
{
    FreeActiveOverlay_8002C014();
    sub_80030664();
    sub_80039FC0();
}

INCLUDE_OVERLAY_ASM(game, sub_800A1474);

INCLUDE_OVERLAY_ASM(game, sub_800A14E0);

INCLUDE_OVERLAY_ASM(game, sub_800A1578);

INCLUDE_OVERLAY_ASM(game, sub_800A15FC);

INCLUDE_OVERLAY_ASM(game, sub_800A167C);

// Matched
void sub_800A16DC(GameV3_1* p)
{
    dword_800ADE78.f0 = p->a;
    dword_800ADE78.f4 = p->b;
    dword_800ADE78.f8 = p->c;
    dword_800ADE78.fc = -1;
    dword_800ADE78.f10 = -1;
}

INCLUDE_OVERLAY_ASM(game, sub_800A170C);

// Matched
void sub_800A1794(void)
{
    int i;
    for (i = 2; i >= 0; i--)
    {
        dword_800B19F0[i].f0 = 0;
    }
}

// Matched
GameSlot_1* sub_800A17BC(void)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        if (dword_800B19F0[i].f0 == 0)
        {
            return &dword_800B19F0[i];
        }
    }
    return 0;
}

INCLUDE_OVERLAY_ASM(game, sub_800A17F4);

// Matched
void sub_800A1850(GameHolder_1* p)
{
    GameFlagObj_1* q = p->f4;
    int** v = q->f8;
    p->f0 = 0;
    sub_800A2D28(q);
    sub_8001D600(v);
}

// Matched
void sub_800A188C(GameHolder_1* p)
{
    GameFlagObj_1* q = p->f4;
    int** v = q->f8;
    sub_800A2EC8(q);
    sub_8001D658(v, 0);
}

// Matched
void sub_800A18C8(GameHolder_1* p)
{
    GameFlagObj_1* q = p->f4;
    int** v = q->f8;
    sub_800A2D48(q);
    sub_8001D658(v, 1);
}

INCLUDE_OVERLAY_ASM(game, sub_800A1904);

INCLUDE_OVERLAY_ASM(game, sub_800A1974);

INCLUDE_OVERLAY_ASM(game, sub_800A19E4);

INCLUDE_OVERLAY_ASM(game, sub_800A1B2C);

INCLUDE_OVERLAY_ASM(game, sub_800A1B78);

INCLUDE_OVERLAY_ASM(game, sub_800A1BD0);

// Matched
void sub_800A1E1C(void)
{
    sub_800A170C();
}

// Matched
char* sub_800A1E3C(void)
{
    return dword_800B19CC;
}

INCLUDE_OVERLAY_ASM(game, sub_800A1E48);

INCLUDE_OVERLAY_ASM(game, sub_800A1E68);

// Matched
void sub_800A1E88(void)
{
}

// Matched
int sub_800A1E90(void)
{
    return 1;
}

INCLUDE_OVERLAY_ASM(game, sub_800A1E98);

INCLUDE_OVERLAY_ASM(game, sub_800A1F0C);

INCLUDE_OVERLAY_ASM(game, sub_800A1F80);

INCLUDE_OVERLAY_ASM(game, sub_800A248C);

INCLUDE_OVERLAY_ASM(game, sub_800A24F4);

// Matched
int sub_800A2550(int a)
{
    sub_800A2CA8(a, 0);
    {
        int* g = dword_800B1260;
        return sub_8001E1C8((struct_obj_A*)g[0x7c / 4 + a]);
    }
}

// Matched
int sub_800A2594(int a)
{
    sub_800A2CA8(a, 0);
    {
        int* g = dword_800B1260;
        return sub_8001E1DC((struct_obj_A*)g[0x7c / 4 + a]);
    }
}

// Matched
int sub_800A25D8(int a)
{
    sub_800A2CA8(a, 0);
    return 0;
}

// Matched
int sub_800A25F8(int a)
{
    sub_800A2CA8(a, 0);
    return 0;
}

INCLUDE_OVERLAY_ASM(game, sub_800A2618);

INCLUDE_OVERLAY_ASM(game, sub_800A2684);

INCLUDE_OVERLAY_ASM(game, sub_800A2760);

// Matched
void sub_800A27FC(int a, int b)
{
    sub_800A2CA8(a, 0);
    {
        int* g = dword_800B1260;
        sub_80018E5C(g[0x7c / 4 + a], b);
    }
}

// Matched
void sub_800A284C(int a)
{
    sub_800A2CA8(a, 0);
    {
        int v = sub_800A2B60(a);
        int* g = dword_800B1260;
        sub_80018EBC(g[0x7c / 4 + a], v);
    }
}

// Matched
int sub_800A2898(int a)
{
    sub_800A2CA8(a, 0);
    return sub_80010650((Item*)&dword_800B130C[a]);
}

// Matched
int sub_800A28DC(int a)
{
    sub_800A2CA8(a, 0);
    return 0;
}

// Matched
int sub_800A28FC(int a)
{
    sub_800A2CA8(a, 0);
    return dword_800B19E0;
}

INCLUDE_OVERLAY_ASM(game, sub_800A2924);

INCLUDE_OVERLAY_ASM(game, sub_800A29CC);

// Matched
int sub_800A2A50(int a)
{
    sub_800A2CA8(a, 0);
    return 0;
}

// Matched
int sub_800A2A70(int a)
{
    sub_800A2CA8(a, 0);
    {
        GameEnt_1* e = &dword_800B130C[a];
        return (int)e + 0x80;
    }
}

#if 0
// Not matched
int sub_800A2AB4(void)
{
    int r;
    if (dword_800B1260[0x774 / 4] == 0)
    {
        r = 0;
    }
    else if (dword_800B1260[0x3c / 4] == 0)
    {
        r = 1;
    }
    else
    {
        r = 2;
    }
    return r;
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800A2AB4);

// Matched
void sub_800A2AE8(void)
{
    if (dword_800B1260[0x3c / 4] == 0)
    {
        dword_800B1260[0x4c / 4] = 1;
        dword_800B1260[0x50 / 4] = 0;
        dword_800B1260[0x3c / 4] = 1;
    }
    else
    {
        dword_800B1260[0x4c / 4] = 0;
        dword_800B1260[0x50 / 4] = 1;
        dword_800B1260[0x3c / 4] = 0;
    }
}

// Matched
int sub_800A2B20(int a)
{
    sub_800A2CA8(a, 0);
    return (int)&dword_800B130C[a];
}

// Matched
int sub_800A2B60(int a)
{
    sub_800A2CA8(a, 0);
    return (int)&dword_800B130C[a];
}

// Matched
int sub_800A2BA0(int a)
{
    sub_800A2CA8(a, 0);
    {
        GameEnt_1* e = &dword_800B130C[a];
        return (int)e + 0x6c;
    }
}

// Matched
int sub_800A2BE4(int a)
{
    sub_800A2CA8(a, 0);
    {
        GameEnt_1* e = &dword_800B130C[a];
        return e->f5c;
    }
}

// Matched
int sub_800A2C28(int a)
{
    sub_800A2CA8(a, 0);
    {
        int* g = dword_800B1260;
        return g[0x7c / 4 + a] + 0x38;
    }
}

// Matched
int sub_800A2C68(int a)
{
    sub_800A2CA8(a, 0);
    {
        int* g = dword_800B1260;
        return *(int*)(g[0x7c / 4 + a] + 0x1c4);
    }
}

INCLUDE_OVERLAY_ASM(game, sub_800A2CA8);

// Matched
void sub_800A2D28(GameFlagObj_1* p)
{
    *p->flags_0 = (*p->flags_0 & ~1) | 0x8000;
}

// Matched
void sub_800A2D48(GameFlagObj_1* p)
{
    *p->flags_0 &= ~0x8000;
    sub_8001D760(p->f8, p->f20, -1, 0);
}

INCLUDE_OVERLAY_ASM(game, sub_800A2D90);

// Matched
void sub_800A2EC8(GameFlagObj_1* p)
{
    *p->flags_0 |= 0x8000;
}

// Matched
void sub_800A2EE4(void)
{
}

INCLUDE_OVERLAY_ASM(game, sub_800A2EEC);

INCLUDE_OVERLAY_ASM(game, sub_800A2FB8);

INCLUDE_OVERLAY_ASM(game, sub_800A31DC);

INCLUDE_OVERLAY_ASM(game, sub_800A333C);

INCLUDE_OVERLAY_ASM(game, sub_800A34D8);

INCLUDE_OVERLAY_ASM(game, sub_800A366C);

INCLUDE_OVERLAY_ASM(game, sub_800A3804);

INCLUDE_OVERLAY_ASM(game, sub_800A3954);

INCLUDE_OVERLAY_ASM(game, sub_800A3A8C);

INCLUDE_OVERLAY_ASM(game, sub_800A3BEC);

INCLUDE_OVERLAY_ASM(game, sub_800A3D24);

INCLUDE_OVERLAY_ASM(game, sub_800A3E88);

INCLUDE_OVERLAY_ASM(game, sub_800A3FC0);

INCLUDE_OVERLAY_ASM(game, sub_800A4124);

INCLUDE_OVERLAY_ASM(game, sub_800A4278);

INCLUDE_OVERLAY_ASM(game, sub_800A433C);

INCLUDE_OVERLAY_ASM(game, sub_800A43FC);

INCLUDE_OVERLAY_ASM(game, sub_800A4470);

INCLUDE_OVERLAY_ASM(game, sub_800A44C0);

INCLUDE_OVERLAY_ASM(game, sub_800A459C);

INCLUDE_OVERLAY_ASM(game, sub_800A45F8);

INCLUDE_OVERLAY_ASM(game, sub_800A46FC);

#if 0
// Not matched
void sub_800A47B8(GameVec3_1* a, GameVec3_1* b, GameVec3_1* out)
{
    int t, d;
    t = b->x;
    d = t - a->x;
    out->x = d + t;
    t = b->y;
    d = t - a->y;
    out->y = d + t;
    t = b->z;
    d = t - a->z;
    out->z = d + t;
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800A47B8);

INCLUDE_OVERLAY_ASM(game, sub_800A4804);

INCLUDE_OVERLAY_ASM(game, sub_800A4884);

INCLUDE_OVERLAY_ASM(game, sub_800A48F4);

INCLUDE_OVERLAY_ASM(game, sub_800A4940);

INCLUDE_OVERLAY_ASM(game, sub_800A49CC);

INCLUDE_OVERLAY_ASM(game, sub_800A4DD0);

INCLUDE_OVERLAY_ASM(game, sub_800A5030);

INCLUDE_OVERLAY_ASM(game, sub_800A5240);

// Matched
void sub_800A52AC(int a)
{
    int r = sub_800A52EC(dword_800AE254, 0x27, a);
    if (r < 0)
    {
        r = 0;
    }
    sub_80039FA4(r);
}

INCLUDE_OVERLAY_ASM(game, sub_800A52EC);

INCLUDE_OVERLAY_ASM(game, sub_800A5354);

INCLUDE_OVERLAY_ASM(game, sub_800A53CC);

// Matched
void sub_800A5474(void)
{
    int i;
    int v = 0xd3;
    for (i = 3; i >= 0; i--)
    {
        dword_800AEB6C[i] = v;
    }
}

INCLUDE_OVERLAY_ASM(game, sub_800A54A0);

INCLUDE_OVERLAY_ASM(game, sub_800A55B0);

INCLUDE_OVERLAY_ASM(game, sub_800A5628);

INCLUDE_OVERLAY_ASM(game, sub_800A56BC);

INCLUDE_OVERLAY_ASM(game, sub_800A5804);

INCLUDE_OVERLAY_ASM(game, sub_800A5854);

INCLUDE_OVERLAY_ASM(game, sub_800A58B4);

INCLUDE_OVERLAY_ASM(game, sub_800A59D0);

// Matched
GameR5_1* sub_800A5AA0(int a, int b)
{
    GameR5_1* r = (GameR5_1*)sub_800A59D0(a);
    GameR6_1* t = r->f14;
    t->f120 = b;
    return r;
}

// Matched
int sub_800A5AD0(int* p)
{
    return *(int*)(p[5] + 0x10);
}

INCLUDE_OVERLAY_ASM(game, sub_800A5AE4);

INCLUDE_OVERLAY_ASM(game, sub_800A5B54);

INCLUDE_OVERLAY_ASM(game, sub_800A5BCC);

INCLUDE_OVERLAY_ASM(game, sub_800A5C40);

INCLUDE_OVERLAY_ASM(game, sub_800A5DDC);

// Matched
int sub_800A5E68(void)
{
    return dword_800AEBD8 >= 0;
}

INCLUDE_OVERLAY_ASM(game, sub_800A5E80);

// Matched
char* sub_800A5F6C(void)
{
    if (dword_800AEBE0)
    {
        return dword_800B1CB8;
    }
    return 0;
}

// Matched
void sub_800A5F90(int a)
{
    dword_800B1D98 = a;
}

// Matched
int sub_800A5F9C(int a)
{
    int old = dword_800AEBF4;
    dword_800AEBF4 = a;
    return old;
}

INCLUDE_OVERLAY_ASM(game, sub_800A5FAC);

INCLUDE_OVERLAY_ASM(game, sub_800A6060);

INCLUDE_OVERLAY_ASM(game, sub_800A6168);

INCLUDE_OVERLAY_ASM(game, sub_800A61CC);

INCLUDE_OVERLAY_ASM(game, sub_800A6308);

INCLUDE_OVERLAY_ASM(game, sub_800A6434);

// Matched
int sub_800A6504(int a)
{
    return sub_800B76B8(dword_8008B520 + (a << 3)) >= 0;
}

// Matched
void sub_800A6534(int a, char b)
{
    dword_8008B518[a] = b;
}

// Matched
void sub_800A654C(int a, char b)
{
    dword_8008B534[a] = b;
}

INCLUDE_OVERLAY_ASM(game, sub_800A6564);

// Matched
int sub_800A65BC(int a, int b)
{
    return (unsigned int)(sub_8003BA18((short)(a - b)) + 0x198) < 0x331;
}

INCLUDE_OVERLAY_ASM(game, sub_800A65F0);

INCLUDE_OVERLAY_ASM(game, sub_800A66A4);

INCLUDE_OVERLAY_ASM(game, sub_800A6738);

INCLUDE_OVERLAY_ASM(game, sub_800A67B4);

// Matched
void sub_800A6830(int a)
{
    dword_800AEBF0 = a;
}

INCLUDE_OVERLAY_ASM(game, sub_800A683C);

INCLUDE_OVERLAY_ASM(game, sub_800A68CC);

INCLUDE_OVERLAY_ASM(game, sub_800A6968);

INCLUDE_OVERLAY_ASM(game, sub_800A6A48);

INCLUDE_OVERLAY_ASM(game, sub_800A6B00);

INCLUDE_OVERLAY_ASM(game, sub_800A6C00);

INCLUDE_OVERLAY_ASM(game, sub_800A6CCC);

INCLUDE_OVERLAY_ASM(game, sub_800A6D30);

INCLUDE_OVERLAY_ASM(game, sub_800A6D50);

INCLUDE_OVERLAY_ASM(game, sub_800A6DAC);

INCLUDE_OVERLAY_ASM(game, sub_800A70F8);

INCLUDE_OVERLAY_ASM(game, sub_800A7204);

// Matched
void sub_800A7280(GameSub_1* p)
{
    sub_800B78B8(p->f8);
    if (p->fc)
    {
        sub_800B78D0();
    }
    p->f0 = 0;
}

INCLUDE_OVERLAY_ASM(game, sub_800A72C8);

INCLUDE_OVERLAY_ASM(game, sub_800A73A8);

INCLUDE_OVERLAY_ASM(game, sub_800A7450);

INCLUDE_OVERLAY_ASM(game, sub_800A74F0);

INCLUDE_OVERLAY_ASM(game, sub_800A7574);

INCLUDE_OVERLAY_ASM(game, sub_800A75F8);

INCLUDE_OVERLAY_ASM(game, sub_800A7654);

// Matched
void sub_800A7690(GameTask_1* t, void** q)
{
    *q = sub_80020D1C(1, 0x14);
    t->next_8 = sub_800A76D8;
}

INCLUDE_OVERLAY_ASM(game, sub_800A76D8);

// Matched
void sub_800A7714(int a)
{
    dword_800B0EC0 = a;
}

INCLUDE_OVERLAY_ASM(game, sub_800A7720);

// Matched
void sub_800A7784(void)
{
    dword_800B0EC4[0] = 0;
}

// Matched
int sub_800A7790(void)
{
    return dword_800B0EC4[0];
}

INCLUDE_OVERLAY_ASM(game, sub_800A77A0);

#if 0
// Not matched
int sub_800A77F4(int a)
{
    int* p = dword_800B0EC4 + a;
    p++;
    return *p;
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800A77F4);

// Matched
int sub_800A7810(int a)
{
    if (a < sub_800A7790())
    {
        GameCb_1* p = (GameCb_1*)(sub_800A77F4(a) + 0x14);
        return p->cb_c(p);
    }
    return 0;
}

// Matched
void sub_800A785C(int a)
{
    if (a < sub_800A7790())
    {
        GameCb_1* p = (GameCb_1*)(sub_800A77F4(a) + 0x14);
        p->cb_10(p);
    }
}

INCLUDE_OVERLAY_ASM(game, sub_800A78A8);

INCLUDE_OVERLAY_ASM(game, sub_800A78F4);

// Matched
int sub_800A7940(int a)
{
    if (a < sub_800A7790())
    {
        return *(int*)(sub_800A77F4(a) + 0x18) + 0x38;
    }
    return 0;
}

// Matched
int sub_800A7984(int a)
{
    if (a < sub_800A7790())
    {
        return *(int*)(sub_800A77F4(a) + 0x18) + 0x5c;
    }
    return 0;
}

INCLUDE_OVERLAY_ASM(game, sub_800A79C8);

// Matched
int sub_800A7A1C(int a)
{
    if (a < sub_800A7790())
    {
        return *(int*)(*(int*)(sub_800A77F4(a) + 0x18) + 0x15c);
    }
    return 0;
}

INCLUDE_OVERLAY_ASM(game, sub_800A7A60);

INCLUDE_OVERLAY_ASM(game, sub_800A7A9C);

INCLUDE_OVERLAY_ASM(game, sub_800A7AD8);

INCLUDE_OVERLAY_ASM(game, sub_800A7B00);

INCLUDE_OVERLAY_ASM(game, sub_800A7BF0);

INCLUDE_OVERLAY_ASM(game, sub_800A7CB8);

INCLUDE_OVERLAY_ASM(game, sub_800A7CFC);

INCLUDE_OVERLAY_ASM(game, sub_800A7D40);

INCLUDE_OVERLAY_ASM(game, sub_800A80C4);

INCLUDE_OVERLAY_ASM(game, sub_800A8108);

INCLUDE_OVERLAY_ASM(game, sub_800A8138);

INCLUDE_OVERLAY_ASM(game, sub_800A8140);

INCLUDE_OVERLAY_ASM(game, sub_800A818C);

INCLUDE_OVERLAY_ASM(game, sub_800A88A0);

INCLUDE_OVERLAY_ASM(game, sub_800A88E0);

INCLUDE_OVERLAY_ASM(game, sub_800A8930);

INCLUDE_OVERLAY_ASM(game, sub_800A895C);

INCLUDE_OVERLAY_ASM(game, sub_800A8984);

INCLUDE_OVERLAY_ASM(game, sub_800A89C8);

INCLUDE_OVERLAY_ASM(game, sub_800A89F0);

INCLUDE_OVERLAY_ASM(game, sub_800A8A10);

INCLUDE_OVERLAY_ASM(game, sub_800A8A30);

INCLUDE_OVERLAY_ASM(game, sub_800A8BE4);

INCLUDE_OVERLAY_ASM(game, sub_800A8C0C);

INCLUDE_OVERLAY_ASM(game, sub_800A8C34);

INCLUDE_OVERLAY_ASM(game, sub_800A8C40);

INCLUDE_OVERLAY_ASM(game, sub_800A8C4C);

INCLUDE_OVERLAY_ASM(game, sub_800A8CA0);

INCLUDE_OVERLAY_ASM(game, sub_800A8CF4);

INCLUDE_OVERLAY_ASM(game, sub_800A8D0C);

INCLUDE_OVERLAY_ASM(game, sub_800A8D48);

INCLUDE_OVERLAY_ASM(game, sub_800A8D84);

INCLUDE_OVERLAY_ASM(game, sub_800A8DAC);

INCLUDE_OVERLAY_ASM(game, sub_800A8DCC);

INCLUDE_OVERLAY_ASM(game, sub_800A8DEC);

INCLUDE_OVERLAY_ASM(game, sub_800A8E0C);

INCLUDE_OVERLAY_ASM(game, sub_800A8E38);

INCLUDE_OVERLAY_ASM(game, sub_800A8E7C);

INCLUDE_OVERLAY_ASM(game, sub_800A8EA4);

INCLUDE_OVERLAY_ASM(game, sub_800A8EC4);

INCLUDE_OVERLAY_ASM(game, sub_800A8FE0);

INCLUDE_OVERLAY_ASM(game, sub_800A9008);

INCLUDE_OVERLAY_ASM(game, sub_800A911C);

INCLUDE_OVERLAY_ASM(game, sub_800A913C);

INCLUDE_OVERLAY_ASM(game, sub_800A9164);

INCLUDE_OVERLAY_ASM(game, sub_800A926C);

INCLUDE_OVERLAY_ASM(game, sub_800A9364);

INCLUDE_OVERLAY_ASM(game, sub_800A9384);

INCLUDE_OVERLAY_ASM(game, sub_800A93A4);

INCLUDE_OVERLAY_ASM(game, sub_800A9414);

INCLUDE_OVERLAY_ASM(game, sub_800A94CC);

INCLUDE_OVERLAY_ASM(game, sub_800A955C);

INCLUDE_OVERLAY_ASM(game, sub_800A9564);

INCLUDE_OVERLAY_ASM(game, sub_800A9708);

INCLUDE_OVERLAY_ASM(game, sub_800A99DC);

INCLUDE_OVERLAY_ASM(game, sub_800A9A9C);

INCLUDE_OVERLAY_ASM(game, sub_800AA140);

INCLUDE_OVERLAY_ASM(game, sub_800AA1C0);

INCLUDE_OVERLAY_ASM(game, sub_800AA1D4);

INCLUDE_OVERLAY_ASM(game, sub_800AA1E0);

INCLUDE_OVERLAY_ASM(game, sub_800AA220);

INCLUDE_OVERLAY_ASM(game, sub_800AA25C);

INCLUDE_OVERLAY_ASM(game, sub_800AA3F0);

INCLUDE_OVERLAY_ASM(game, sub_800AA430);

INCLUDE_OVERLAY_ASM(game, sub_800AA51C);

INCLUDE_OVERLAY_ASM(game, sub_800AACF8);

INCLUDE_OVERLAY_ASM(game, sub_800AAF58);

INCLUDE_OVERLAY_ASM(game, sub_800AAFD8);

INCLUDE_OVERLAY_ASM(game, sub_800AB010);

INCLUDE_OVERLAY_ASM(game, sub_800AB114);

INCLUDE_OVERLAY_ASM(game, sub_800AB134);

INCLUDE_OVERLAY_ASM(game, sub_800AB150);

INCLUDE_OVERLAY_ASM(game, sub_800AB170);

INCLUDE_OVERLAY_ASM(game, sub_800AB1A4);

INCLUDE_OVERLAY_ASM(game, sub_800AB1EC);

INCLUDE_OVERLAY_ASM(game, sub_800AB264);

INCLUDE_OVERLAY_ASM(game, sub_800AB28C);

INCLUDE_OVERLAY_ASM(game, sub_800AB2B4);

INCLUDE_OVERLAY_ASM(game, sub_800AB2DC);

INCLUDE_OVERLAY_ASM(game, sub_800AB304);

INCLUDE_OVERLAY_ASM(game, sub_800AB32C);

INCLUDE_OVERLAY_ASM(game, sub_800AB354);

INCLUDE_OVERLAY_ASM(game, sub_800AB37C);

INCLUDE_OVERLAY_ASM(game, sub_800AB39C);

INCLUDE_OVERLAY_ASM(game, sub_800AB3BC);

INCLUDE_OVERLAY_ASM(game, sub_800AB3D4);

INCLUDE_OVERLAY_ASM(game, sub_800AB444);

INCLUDE_OVERLAY_ASM(game, sub_800AB4D8);

INCLUDE_OVERLAY_ASM(game, sub_800AB5F8);

INCLUDE_OVERLAY_ASM(game, sub_800AB630);

INCLUDE_OVERLAY_ASM(game, sub_800AB750);

INCLUDE_OVERLAY_ASM(game, sub_800AB85C);

INCLUDE_OVERLAY_ASM(game, sub_800AB884);

INCLUDE_OVERLAY_ASM(game, sub_800AB8AC);

INCLUDE_OVERLAY_ASM(game, sub_800AB8DC);

INCLUDE_OVERLAY_ASM(game, sub_800AB910);

INCLUDE_OVERLAY_ASM(game, sub_800AB938);

INCLUDE_OVERLAY_ASM(game, sub_800AB958);

INCLUDE_OVERLAY_ASM(game, sub_800AB978);

INCLUDE_OVERLAY_ASM(game, sub_800AB9A8);

INCLUDE_OVERLAY_ASM(game, sub_800ABAA4);

INCLUDE_OVERLAY_ASM(game, sub_800ABAD4);

INCLUDE_OVERLAY_ASM(game, sub_800ABB44);

INCLUDE_OVERLAY_ASM(game, sub_800ABB70);

INCLUDE_OVERLAY_ASM(game, sub_800ABB98);

INCLUDE_OVERLAY_ASM(game, sub_800ABBD8);

INCLUDE_OVERLAY_ASM(game, sub_800ABC34);

INCLUDE_OVERLAY_ASM(game, sub_800ABC78);

INCLUDE_OVERLAY_ASM(game, sub_800ABCF4);

INCLUDE_OVERLAY_ASM(game, sub_800ABDF0);

INCLUDE_OVERLAY_ASM(game, sub_800ABECC);

INCLUDE_OVERLAY_ASM(game, sub_800AC02C);

INCLUDE_OVERLAY_ASM(game, sub_800AC318);

INCLUDE_OVERLAY_ASM(game, sub_800AC340);

INCLUDE_OVERLAY_ASM(game, sub_800AC380);

INCLUDE_OVERLAY_ASM(game, sub_800AC38C);

INCLUDE_OVERLAY_ASM(game, sub_800AC3A4);

INCLUDE_OVERLAY_ASM(game, sub_800AC3B0);

INCLUDE_OVERLAY_ASM(game, sub_800AC3D8);

INCLUDE_OVERLAY_ASM(game, sub_800AC3E4);

INCLUDE_OVERLAY_ASM(game, sub_800AC3F4);

INCLUDE_OVERLAY_ASM(game, sub_800AC464);

INCLUDE_OVERLAY_ASM(game, sub_800AC474);

INCLUDE_OVERLAY_ASM(game, sub_800AC4A8);

INCLUDE_OVERLAY_ASM(game, sub_800AC518);

INCLUDE_OVERLAY_ASM(game, sub_800AC5D0);

INCLUDE_OVERLAY_ASM(game, sub_800AC604);

INCLUDE_OVERLAY_ASM(game, sub_800AC678);

INCLUDE_OVERLAY_ASM(game, sub_800AC6A8);

INCLUDE_OVERLAY_ASM(game, sub_800AC708);

INCLUDE_OVERLAY_ASM(game, sub_800AC73C);

INCLUDE_OVERLAY_ASM(game, sub_800AC768);

INCLUDE_OVERLAY_ASM(game, sub_800AC794);

INCLUDE_OVERLAY_ASM(game, sub_800AC7B4);

INCLUDE_OVERLAY_ASM(game, sub_800AC7F0);

INCLUDE_OVERLAY_ASM(game, sub_800AC834);

INCLUDE_OVERLAY_ASM(game, sub_800AC878);

INCLUDE_OVERLAY_ASM(game, sub_800AC8BC);

INCLUDE_OVERLAY_ASM(game, sub_800AC900);

INCLUDE_OVERLAY_ASM(game, sub_800AC944);

INCLUDE_OVERLAY_ASM(game, sub_800AC988);

INCLUDE_OVERLAY_ASM(game, sub_800AC9CC);

INCLUDE_OVERLAY_ASM(game, sub_800ACA38);

INCLUDE_OVERLAY_ASM(game, sub_800ACAA4);

INCLUDE_OVERLAY_ASM(game, sub_800ACB64);

INCLUDE_OVERLAY_ASM(game, sub_800ACF0C);

INCLUDE_OVERLAY_ASM(game, sub_800ACF3C);

INCLUDE_OVERLAY_ASM(game, sub_800ACFB8);

INCLUDE_OVERLAY_ASM(game, sub_800AD02C);

INCLUDE_OVERLAY_ASM(game, sub_800AD058);

INCLUDE_OVERLAY_ASM(game, sub_800AD0A4);

INCLUDE_OVERLAY_ASM(game, sub_800AD0D4);

INCLUDE_OVERLAY_ASM(game, sub_800AD0F8);

INCLUDE_OVERLAY_ASM(game, sub_800AD124);

INCLUDE_OVERLAY_ASM(game, sub_800AD154);

INCLUDE_OVERLAY_ASM(game, sub_800AD16C);

INCLUDE_OVERLAY_ASM(game, sub_800AD184);

INCLUDE_OVERLAY_ASM(game, sub_800AD1E0);

INCLUDE_OVERLAY_ASM(game, sub_800AD254);

INCLUDE_OVERLAY_ASM(game, sub_800AD288);

INCLUDE_OVERLAY_ASM(game, sub_800AD2C8);

INCLUDE_OVERLAY_ASM(game, sub_800AD308);

INCLUDE_OVERLAY_ASM(game, sub_800AD374);

INCLUDE_OVERLAY_ASM(game, sub_800AD398);

INCLUDE_OVERLAY_ASM(game, sub_800AD3F0);

INCLUDE_OVERLAY_ASM(game, sub_800AD4D8);

INCLUDE_OVERLAY_ASM(game, sub_800AD58C);

INCLUDE_OVERLAY_ASM(game, sub_800AD604);

INCLUDE_OVERLAY_ASM(game, sub_800AD670);

INCLUDE_OVERLAY_ASM(game, sub_800AD67C);

INCLUDE_OVERLAY_ASM(game, sub_800AD68C);

INCLUDE_OVERLAY_ASM(game, sub_800AD6E4);

INCLUDE_OVERLAY_ASM(game, sub_800AD73C);

INCLUDE_OVERLAY_ASM(game, sub_800AD79C);

INCLUDE_OVERLAY_ASM(game, sub_800AD7F8);

INCLUDE_OVERLAY_ASM(game, sub_800AD888);

INCLUDE_OVERLAY_ASM(game, sub_800AD8BC);

INCLUDE_OVERLAY_ASM(game, sub_800AD8E4);

INCLUDE_OVERLAY_ASM(game, sub_800AD8F4);

INCLUDE_OVERLAY_ASM(game, sub_800AD944);

INCLUDE_OVERLAY_ASM(game, sub_800AD990);

INCLUDE_OVERLAY_ASM(game, sub_800AD9EC);

INCLUDE_OVERLAY_ASM(game, sub_800ADBA0);

INCLUDE_OVERLAY_ASM(game, sub_800ADC1C);

INCLUDE_OVERLAY_ASM(game, sub_800ADC5C);

INCLUDE_OVERLAY_ASM(game, sub_800ADCEC);

INCLUDE_OVERLAY_ASM(game, sub_800ADDAC);

INCLUDE_OVERLAY_ASM(game, dword_800ADE78);
