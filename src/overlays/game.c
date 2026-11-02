// GAME.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
extern void sub_800A6D30(int a);
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
    struct GameFlagObj_1* f4;
    char data_8[0xe0];
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
extern int sub_800A2CA8(int, int);
extern void sub_8001D600(int** p);
extern char* dword_8008B520;
extern void sub_800A170C(void);
extern int sub_800A2CA8(int, int);
extern int sub_800A7A60(int a);
extern char dword_800B19CC[];
extern int dword_800B1D98;
extern int dword_800AEBF0;
extern int dword_800B0EC0;
typedef struct GameList_1
{
    int count;
    int a[4];
    int b[4];
    int c[4];
} GameList_1;
extern GameList_1 dword_800B0EC4;
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
typedef struct GameSave3_1
{
    char pad_0[0x2e4];
    short f2e4;
    short pad_2e6;
    short f2e8;
    short pad_2ea;
    short f2ec;
    short pad_2ee;
    short f2f0;
} GameSave3_1;
typedef struct GameS3_1
{
    unsigned short a, b, c;
} GameS3_1;
extern void sub_8003B740(int* a, int* b, unsigned int* out);
extern int dword_800AEBE4;
extern void sub_800ADCEC(GameS3_1* out, int a);
extern void sub_800AD0F8(unsigned a);
extern int dword_80091C54;
extern int dword_80091C9C;
extern int dword_80091C8C;
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
extern int sub_800A52EC(short** a, int b, int c);
extern void* sub_80020D1C(int a, int b);
extern void sub_800A76D8();
extern void sub_800B78B8(int a);
extern void sub_800B78D0();
extern int sub_800A7790(void);
extern int sub_800A77F4(int a);
extern short* dword_800AE254[];
typedef struct GameCtx_1
{
    int f0;
    int f4;
    int f8;
    int fc[12];
    int f3c;
    int f40;
    int f44;
    int pad_48;
    int f4c[12];
    int f7c[12];
    char pad_ac[0x76c - 0xac];
    int f76c;
    int f770;
    int f774;
    int f778;
    int f77c;
    int f780;
    int f784;
} GameCtx_1;
extern GameCtx_1 gCtx_800B1260;
typedef struct GameP4470_1
{
    char pad_0[8];
    struct_obj_A* f8;
    char pad_c[0x1c];
    int f28;
    int f2c;
} GameP4470_1;
typedef struct GameJ_1
{
    short h0;
    short h2;
} GameJ_1;
typedef struct GameQ_1
{
    char pad_0[4];
    int f4;
    char pad_8[0x34];
    int f3c;
} GameQ_1;
extern int sub_8001DD44(struct_obj_A* a, int b, int c, int d);
extern int sub_8001DDFC(struct_obj_A* a, GameVec3_1* b, int c);
extern void sub_800A47B8(GameVec3_1* a, GameVec3_1* b, GameVec3_1* out);
extern void sub_800A7654();
extern void sub_800A1314();
extern void sub_8001C19C(int a, int b);
extern void sub_800438F8(int a);
extern void sub_80043A5C(int a);
extern void sub_800A6534(int a, int b);
extern void sub_800A654C(int a, int b);
extern GameVec3_1 dword_8008BD18;
extern int dword_800AEB7C;
typedef struct GameTab_1
{
    int f0;
    void (*fn)();
} GameTab_1;
extern void FreeMdecBuffer_800418CC(void);
extern void sub_800418FC(void);
extern void sub_800B8A34(GameQ_1* q);
extern void sub_800C4118(void* a, void* b, int c, int d);
extern void sub_8001AA50(int a);
extern int sub_800BA9E4(void);
extern void sub_800BA254();
extern short* dword_800AE3D0[];
extern void sub_800A7B00(int a);
extern void sub_800A7BF0(int a);
extern void sub_800A188C(GameHolder_1* p);
extern void sub_800A18C8(GameHolder_1* p);
extern GameTab_1 dword_800B0EB8[];
extern int dword_800AEBD8;
extern int dword_800B199C[];
extern short sinTable_80084540[];
typedef struct GameSave_1
{
    char pad_0[0x2f0];
    short f2f0;
    short f2f2;
} GameSave_1;
typedef struct GameObj5_1
{
    unsigned int flags_0;
    char pad_4[4];
    void (*fn_8)();
    void (*fn_c)();
    int pad_10;
    int* obj_14;
} GameObj5_1;
typedef struct GameNode_1
{
    char pad_0[4];
    struct GameNode_1* next_4;
    char pad_8[4];
    int count_c;
    GameObj5_1 sub_10;
} GameNode_1;
typedef struct GameObjList_1
{
    char pad_0[0xc];
    int count_c;
    char pad_10[4];
} GameObjList_1;
typedef struct GameTabEnt_1
{
    int v;
    int w;
} GameTabEnt_1;
typedef struct GameTable_1
{
    unsigned int count;
    GameTabEnt_1 e[1];
} GameTable_1;
extern GameNode_1* dword_8008D410;
extern void sub_800A8EA4();
extern void sub_800BAE2C(int a, int b);
extern void sub_800B66C4(int a);
extern GameTable_1* sub_800A55B0(int a);
extern int dword_800AEBE8;
extern int dword_800B1228;
extern void sub_800A15FC();
extern void sub_800A167C();
extern void sub_800A7AD8(int a);
typedef struct GameV6_1
{
    int a, b, c, d, e, f;
} GameV6_1;
typedef struct GameP4804_1
{
    char pad_0[8];
    char* f8;
    char pad_c[0x18];
    int f24;
    int f28;
} GameP4804_1;
extern char aAssertionFaile_800A05A4[];
extern char aFile_800A05CC[];
extern void sub_800A895C();
extern void sub_800A1BD0();
extern void sub_800A1E98();
extern void sub_800AC73C();
extern void sub_80020814(void);
extern void sub_80037720(void);
extern void sub_80030D68(char* s);
extern void sub_800300E0(int a, int b);
extern void sub_800A1474();
extern char dword_80091CE0[];
extern int sub_8001DECC(void* a, int b, int c);
extern short* sub_800B322C();
extern unsigned short* sub_800A53CC();
extern int sub_800AD154(int a);
extern int sub_800AD16C(int a, int b);
typedef struct GameRect_1
{
    short x, y, w, h;
} GameRect_1;
extern int GameFn_8003B9E0(int* a, int* b);
extern void sub_800B6BFC();
extern void sub_800B66DC();
extern int sub_800BBB94(void);
extern int dword_800B1DC8[];
extern void sub_800A6968();
extern int sub_800435B4(char* p);
extern char dword_800B0DA4[];
extern void sub_8001E28C(int a);
extern void sub_80026FAC(void);
extern void GameFn_800A094C(void);
extern void sub_8002FEB8(void);
extern void sub_8001A38C(void);
extern void sub_800376A8(void);
extern void sub_800A8140(void);
extern void sub_800A94CC(void);
extern GameNode_1* dword_8008D400;
extern GameRect_1 stru_8008D420;
extern int dword_80091C94;
extern void sub_800A72C8(int* p);
typedef struct GameMapEnt_1
{
    int pad_0;
    short f4;
    char pad_6[10];
} GameMapEnt_1;
typedef struct GameSave2_1
{
    char pad_0[0x2e4];
    short f2e4;
    short pad_2e6;
    short f2e8;
    short pad_2ea;
    short f2ec;
} GameSave2_1;
extern GameMapEnt_1** dword_800B0608[];
extern void sub_800A4940(int a, int b);
extern void sub_800A5B54(int* p);
extern void sub_800A6060();
extern void sub_800A6168();
extern int dword_800AEBDC;
extern void sub_800A0A04();
typedef struct GameVec4_1
{
    int x, y, z, w;
} GameVec4_1;
typedef struct GameSave4_1
{
    char pad_0[0x7a8];
    int f7a8;
    int pad_7ac;
    int f7b0;
} GameSave4_1;
typedef struct GameO_1
{
    char pad_0[0x38];
    int f38;
    int pad_3c;
    int f40;
    char pad_44[0x1a];
    short f5e;
} GameO_1;
extern int sub_800A48F4(int a);
extern void sub_800A46FC(GameP4470_1* p);
typedef struct GameLst_1
{
    int** p0;
    int f4;
} GameLst_1;
extern GameLst_1 dword_800B09FC[];
extern GameLst_1* dword_800B0D74[];
extern void sub_800A6CCC();
extern void sub_80030988(void);
extern void sub_800A6C00();
extern void sub_800A6A48();
extern void sub_800A6B00();
extern void sub_800A73A8(void);
extern void sub_800A7450(GameNode_1* n);

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

// Matched
void sub_800A09D8(GameTask_1* t, short* q)
{
    *q = 0;
    t->next_8 = sub_800A0A04;
    sub_800A0A04(t, q);
}

INCLUDE_OVERLAY_ASM(game, sub_800A0A04);

INCLUDE_OVERLAY_ASM(game, sub_800A0A5C);

extern void sub_800A13B8();
extern int sub_800A19E4();
extern void sub_80036528();
void sub_800A1314(GameTask_1* t)
{
    if (sub_800A19E4() == 1)
        dword_800B1228 |= 0x4000;
    if (dword_800B1228 & 0x4000)
    {
        sub_80036528(0, 10);
        sub_8001C19C(0, 0x20);
        sub_8001C19C(1, 0x20);
        sub_800A6D30(2);
        t->next_8 = sub_800A13B8;
        unknownFlags_8008D678 |= 0x4000000;
    }
}

// Matched
void sub_800A13B8(GameTask_1* t, void** q)
{
    sub_800A895C();
    sub_800A1BD0();
    sub_800A1E98();
    sub_800AC73C();
    sub_80020814();
    sub_80037720();
    *q = sub_80020D1C(1, 6);
    t->next_8 = sub_800A1474;
    sub_80030D68(dword_80091CE0);
    sub_800300E0(0, 1);
}

// Matched
void sub_800A1444(void)
{
    FreeActiveOverlay_8002C014();
    sub_80030664();
    sub_80039FC0();
}

// Matched
void sub_800A1474(GameTask_1* t, GameQ_1* q)
{
    if (sub_8003BE30(*(int*)q) == 0)
    {
        sub_8001AA50(1);
        *(int*)((char*)q + 8) = sub_800BA9E4();
        t->next_8 = sub_800BA254;
    }
    dword_8008B540 = 1;
}

// Matched
void sub_800A14E0(GameTask_1* t, GameQ_1* q)
{
    if (sub_8003BE30(*(int*)q) == 0)
    {
        sub_800A6D30(0xa);
        *(int*)((char*)q + 8) = sub_800BBB94();
        t->next_8 = sub_800A167C;
        unknownFlags_8008D678 &= ~0x4000000;
        dword_800B1228 &= ~0x4000;
    }
    dword_8008B540 = 1;
}

void sub_800A1578(GameTask_1* t, int** q)
{
    if ((*q[2] & 0x8001) != 1)
    {
        GameSave_1* sd;
        FreeActiveOverlay_8002C014();
        sub_8001C19C(0, 0x20);
        sd = (GameSave_1*)&saveData_8008B570;
        if (sd->f2f2 == sd->f2f0)
        {
            sub_80027314();
        }
        sub_80020D68();
        t->next_8 = sub_800A15FC;
    }
}

// Matched
void sub_800A15FC(GameTask_1* t, GameQ_1* q)
{
    if (sub_800272D0() == 0)
    {
        sub_800A6D30(1);
        dword_8008B540 = 1;
        t->next_8 = sub_800A167C;
        q->f4 = 2;
        dword_800B1228 &= ~0x4000;
    }
    dword_8008B540 = 1;
}

// Matched
void sub_800A167C(GameTask_1* t, GameQ_1* q)
{
    q->f4--;
    if (q->f4 <= 0)
    {
        sub_8001C19C(3, 0x20);
        t->next_8 = sub_800A1314;
        unknownFlags_8008D678 &= ~0x4000000;
    }
}

// Matched
void sub_800A16DC(GameV3_1* p)
{
    dword_800ADE78.f0 = p->a;
    dword_800ADE78.f4 = p->b;
    dword_800ADE78.f8 = p->c;
    dword_800ADE78.fc = -1;
    dword_800ADE78.f10 = -1;
}

// Matched
void sub_800A170C(void)
{
    GameV6_1 v;
    int i;
    v.a = 0;
    v.b = 0;
    v.c = 0;
    sub_800A16DC((GameV3_1*)&v);
    gCtx_800B1260.f0 = 0;
    gCtx_800B1260.f8 = 0;
    gCtx_800B1260.f40 = 0;
    gCtx_800B1260.f44 = 0;
    for (i = 11; i >= 0; i--)
    {
        gCtx_800B1260.f7c[i] = 0;
    }
    gCtx_800B1260.f76c = 0;
    gCtx_800B1260.f770 = 0;
    gCtx_800B1260.f774 = 0;
    gCtx_800B1260.f778 = 0;
    gCtx_800B1260.f77c = 0;
    gCtx_800B1260.f780 = 1;
    gCtx_800B1260.f784 = 1;
    gCtx_800B1260.f3c = 0;
}

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

// Matched
GameSlot_1* sub_800A17F4(unsigned int* src, GameFlagObj_1* b)
{
    GameSlot_1* r = sub_800A17BC();
    r->f0 = 1;
    r->f4 = b;
    sub_800403E8((unsigned int*)r->data_8, src, 0xe0);
    return r;
}

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

// Matched
void sub_800A1904(void)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        if (dword_800B19F0[i].f0)
        {
            GameFlagObj_1* q = dword_800B19F0[i].f4;
            sub_800A2EC8(q);
            sub_8001D6EC((struct_obj_A*)q->f8, 1);
        }
    }
}

// Matched
void sub_800A1974(void)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        if (dword_800B19F0[i].f0)
        {
            GameFlagObj_1* q = dword_800B19F0[i].f4;
            sub_800A2D48(q);
            sub_8001D6EC((struct_obj_A*)q->f8, 0);
        }
    }
}

INCLUDE_OVERLAY_ASM(game, sub_800A19E4);

// Matched
int sub_800A1B2C(void)
{
    int i;
    for (i = 0; i < gCtx_800B1260.f40; i++)
    {
        if (gCtx_800B1260.f4c[i] == 0)
        {
            return 0;
        }
    }
    return 1;
}

// Matched
void sub_800A1B78(void)
{
    int i;
    for (i = 0; i < 12; i++)
    {
        if (gCtx_800B1260.f7c[i])
        {
            sub_8001D600((int**)gCtx_800B1260.f7c[i]);
        }
    }
}

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

// Matched
int sub_800A1E48(void)
{
    return *(int*)(*(int*)(gCtx_800B1260.f4 + 4) + 8) + 0x38;
}

// Matched
int sub_800A1E68(void)
{
    return *(int*)(*(int*)(gCtx_800B1260.f4 + 4) + 8) + 0x5c;
}

// Matched
void sub_800A1E88(void)
{
}

// Matched
int sub_800A1E90(void)
{
    return 1;
}

// Matched
void sub_800A1E98(void)
{
    int i;
    for (i = 0; i < gCtx_800B1260.f8; i++)
    {
        sub_800A188C((GameHolder_1*)gCtx_800B1260.fc[i]);
    }
    sub_800A7B00(-1);
}

// Matched
void sub_800A1F0C(void)
{
    int i;
    for (i = 0; i < gCtx_800B1260.f8; i++)
    {
        sub_800A18C8((GameHolder_1*)gCtx_800B1260.fc[i]);
    }
    sub_800A7BF0(-1);
}

INCLUDE_OVERLAY_ASM(game, sub_800A1F80);

// Matched
int sub_800A248C(void)
{
    int mask = 0;
    int i;
    for (i = 0; i < gCtx_800B1260.f40; i++)
    {
        if (gCtx_800B1260.f7c[i] && gCtx_800B1260.f4c[i] == 0)
        {
            mask |= 1 << (i + 4);
        }
    }
    return mask;
}

// Matched
int sub_800A24F4(int a)
{
    sub_800A2CA8(a, 0);
    if (gCtx_800B1260.f7c[a] != 0)
    {
        if (gCtx_800B1260.f4c[a] == 0)
        {
            return 1;
        }
    }
    return 0;
}

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

// Matched
int sub_800A2618(void* x, int n)
{
    sub_800A2CA8(n, 0);
    sub_800C4118(x, &dword_800B130C[n], n, *(int*)((char*)dword_800B130C + n * 4 + 0x690));
    return 1;
}

INCLUDE_OVERLAY_ASM(game, sub_800A2684);

// Matched
int sub_800A2760(unsigned int* p)
{
    int i;
    if (p[0] == 0x14)
    {
        return 0;
    }
    for (i = 4; i < 7; i++)
    {
        if (p[2] & (1 << i))
        {
            sub_8001E28C(gCtx_800B1260.f7c[i - 4]);
        }
    }
    return 1;
}

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

// Matched
void sub_800A2924(int a)
{
    sub_800A2CA8(a, 0);
    gCtx_800B1260.f4c[a] = 1;
    if (--gCtx_800B1260.f44 == 0)
    {
        int x = *(int*)((char*)&gCtx_800B1260 + 0x48);
        if (x >= 0)
        {
            GameSave2_1* sd = (GameSave2_1*)&saveData_8008B570;
            sub_800A4940(x, dword_800B0608[sd->f2e4][sd->f2e8][sd->f2ec].f4);
        }
    }
}

// Matched
void sub_800A29CC(int a, int* out)
{
    sub_800A2CA8(a, 0);
    {
        char* e = (char*)gCtx_800B1260.f7c[a];
        out[0] = *(int*)(e + 0x14c);
        out[1] = (int)(e + 0x38);
        out[2] = *(int*)(e + 0x1c4);
        out[3] = *(int*)(e + 0x1c8);
        out[0x2c / 4] = *(int*)(e + 0x144);
        out[0x30 / 4] = (int)(e + 0x2c);
    }
}

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

int sub_800A2CA8(int a, int b)
{
    int ok = 0;
    if (a < 0 || a >= gCtx_800B1260.f40 || gCtx_800B1260.f4c[a] != 0)
    {
        ok = 1;
    }
    if (ok)
    {
        if (!b)
        {
            printf(aAssertionFaile_800A05A4, aFile_800A05CC, 0x512);
            exit(1);
        }
    }
    return ok;
}

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

typedef struct GameA2EEC_1
{
    char pad_0[8];
    struct_obj_A* f8;
    int fC;
} GameA2EEC_1;
extern int sub_800A4278();
extern void sub_800A433C();
extern unsigned int sub_8003B860(void* a, void* b);
void sub_800A2EEC(int unused, GameA2EEC_1* p)
{
    if (sub_800A4278(p) == 0)
    {
        switch (p->fC)
        {
        case -1:
            sub_800A433C(p, 5, 2, 0, -1, 1, 2);
            sub_8001DB58(p->f8, 0x3000, 1);
            break;
        case 5:
            sub_800A459C((GameP4470_1*)p);
            if (sub_8003B860((char*)p->f8 + 0x38, &dword_8008BD18) > 0x155CC0)
                p->fC = -1;
            break;
        }
    }
}

INCLUDE_OVERLAY_ASM(game, sub_800A2FB8);

INCLUDE_OVERLAY_ASM(game, sub_800A31DC);

INCLUDE_OVERLAY_ASM(game, sub_800A333C);

INCLUDE_OVERLAY_ASM(game, sub_800A34D8);

INCLUDE_OVERLAY_ASM(game, sub_800A366C);

INCLUDE_OVERLAY_ASM(game, sub_800A3804);

void sub_800A3954(int unused, GameA2EEC_1* p)
{
    GameA2EEC_1* q = p;
    if (sub_800A4278(p) == 0)
    {
        switch (p->fC)
        {
        case -1:
            sub_800A433C(p, 0xf, 2, 0, p->fC, 1, 2);
            break;
        case 0xf:
            sub_800A45F8(p);
            if (sub_8003B860((char*)p->f8 + 0x38, &dword_8008BD18) <= 0xDBB9F)
                sub_800A433C(p, 0xa, 4, 0x46, -1, 1, 2);
            break;
        case 0xa:
            sub_8001DDFC(q->f8, &dword_8008BD18, 0x155);
            if (sub_8003B860((char*)q->f8 + 0x38, &dword_8008BD18) > 0xDBBA0)
                q->fC = -1;
            break;
        }
    }
}

typedef struct GameS3A8C_1
{
    char pad_0[8];
    struct_obj_A* f8;
    int fC;
    char pad_10[0x14];
    int f24;
} GameS3A8C_1;
extern void sub_800A43FC();
void sub_800A3A8C(int unused, GameS3A8C_1* p)
{
    int c;
    GameS3A8C_1* q = p;
    if (sub_800A4278(p) == 0)
    {
        c = p->fC;
        switch (c)
        {
        case -1:
            sub_800A433C(p, 8, 2, 0, c, 1, 2);
            break;
        case 8:
            sub_800A46FC((GameP4470_1*)p);
            if (sub_800A4804((GameP4804_1*)p))
                sub_800A433C(p, 1, 1, (rand() % 16) * 8 + 0x32, -1, 1, 2);
            break;
        case 1:
            if (--p->f24 < 0)
            {
                sub_800A433C(p, 0xe, 1, 0, -1, c, 2);
                sub_800A43FC(p);
            }
            break;
        case 0xe:
            if (sub_800A4470((GameP4470_1*)p) == 0)
                q->fC = -1;
            break;
        }
    }
}

void sub_800A3BEC(int unused, GameA2EEC_1* p)
{
    int c;
    GameA2EEC_1* q = p;
    if (sub_800A4278(p) == 0)
    {
        c = p->fC;
        switch (c)
        {
        case -1:
            sub_800A433C(p, 1, 1, (rand() % 16) * 8 + 0x32, c, 1, 2);
            break;
        case 1:
            if (sub_800A4884(&dword_8008BD18, (short*)(&dword_8008BD18 + 1), (GameVec3_1*)((char*)p->f8 + 0x38)))
                sub_800A433C(p, 0xf, 2, 0, -1, c, 2);
            break;
        case 0xf:
            sub_800A45F8(p);
            if (sub_800A4884(&dword_8008BD18, (short*)(&dword_8008BD18 + 1), (GameVec3_1*)((char*)p->f8 + 0x38)) == 0)
                q->fC = -1;
            break;
        }
    }
}

INCLUDE_OVERLAY_ASM(game, sub_800A3D24);

extern void sub_800A44C0();
void sub_800A3E88(int unused, GameA2EEC_1* p)
{
    GameA2EEC_1* q = p;
    if (sub_800A4278(p) == 0)
    {
        switch (p->fC)
        {
        case -1:
            sub_800A433C(p, 0x10, 0x12, 0, p->fC, 1, 2);
        case 0x10:
            if (sub_8003B860((char*)q->f8 + 0x38, &dword_8008BD18) <= 0xDBB9F)
            {
                sub_800A433C(q, 5, 2, 0, -1, 1, 2);
                sub_8001DB58(q->f8, 0x2000, 1);
            }
            break;
        case 5:
            sub_800A44C0(q);
            if (sub_8003B860((char*)q->f8 + 0x38, &dword_8008BD18) > 0x155CC0)
                q->fC = -1;
            break;
        }
    }
}

INCLUDE_OVERLAY_ASM(game, sub_800A3FC0);

INCLUDE_OVERLAY_ASM(game, sub_800A4124);

INCLUDE_OVERLAY_ASM(game, sub_800A4278);

INCLUDE_OVERLAY_ASM(game, sub_800A433C);

INCLUDE_OVERLAY_ASM(game, sub_800A43FC);

// Matched
int sub_800A4470(GameP4470_1* p)
{
    if (p->f2c)
    {
        p->f2c = sub_8001DD44(p->f8, p->f28, p->f2c, 0x20);
        sub_8001D71C(p->f8);
        return 1;
    }
    return 0;
}

// Matched
void sub_800A44C0(GameP4470_1* p)
{
    GameVec4_1 v;
    GameVec4_1 w;
    int ang;
    int idx;
    sub_800A46FC(p);
    v.x = ((GameSave4_1*)&saveData_8008B570)->f7a8 - ((GameO_1*)p->f8)->f38;
    v.z = ((GameSave4_1*)&saveData_8008B570)->f7b0 - ((GameO_1*)p->f8)->f40;
    ang = ratan2_8003B548(v.x, v.z);
    idx = (ang - ((GameO_1*)p->f8)->f5e) & 0xfff;
    w.x = ((GameO_1*)p->f8)->f38 + (((GameO_1*)p->f8)->f38 - ((GameSave4_1*)&saveData_8008B570)->f7a8);
    w.z = ((GameO_1*)p->f8)->f40 + (((GameO_1*)p->f8)->f40 - ((GameSave4_1*)&saveData_8008B570)->f7b0);
    if (sub_8001DDFC(p->f8, (GameVec3_1*)&w, sub_800A48F4(idx * 3)) == 0)
    {
        sub_8001D71C(p->f8);
    }
}

// Matched
void sub_800A459C(GameP4470_1* p)
{
    GameVec3_1 v;
    sub_800A47B8(&dword_8008BD18, (GameVec3_1*)((char*)p->f8 + 0x38), &v);
    if (sub_8001DDFC(p->f8, &v, 0x155) == 0)
    {
        sub_8001D71C(p->f8);
    }
}

INCLUDE_OVERLAY_ASM(game, sub_800A45F8);

void sub_800A46FC(GameP4470_1* p)
{
    int r;
    if (p->f2c)
    {
        p->f2c = sub_8001DD44(p->f8, p->f28, p->f2c, 0x20);
    }
    else
    {
        r = sub_8001DECC(p->f8, 0x190, 0);
        p->f28 = r;
        if (r == 3)
        {
            p->f28 = 2;
            p->f2c = 0x745;
        }
        else if ((unsigned)(r - 1) < 2)
        {
            p->f2c = 0x1e1;
        }
        else
        {
            r = *(int*)((char*)p->f8 + 0x80);
            p->f28 = r;
            if (r == 3)
            {
                p->f28 = 2;
                p->f2c = 0x745;
            }
            else if ((unsigned)(r - 1) < 2)
            {
                p->f2c = 0x100;
            }
        }
    }
}

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

// Matched
int sub_800A4804(GameP4804_1* p)
{
    int r = sub_8001DECC(p->f8, 0x190, 0);
    if (r == 0)
    {
        r = *(int*)(p->f8 + 0x80);
    }
    if (r != 0)
    {
        if (r == 1)
        {
            p->f28 = 1;
        }
        else
        {
            p->f28 = 2;
        }
        if (r == 3)
        {
            p->f24 = 0x745;
        }
        else
        {
            p->f24 = 0x1e1;
        }
    }
    return 0;
}

// Matched
int sub_800A4884(GameVec3_1* a, short* q, GameVec3_1* b)
{
    int ang = ratan2_8003B548(a->x - b->x, a->z - b->z);
    return sinTable_80084540[(ang - q[1] + 0x400) & 0xfff] >= 0;
}

// Matched
int sub_800A48F4(int a)
{
    int r = 0x20;
    if (a > 0x800)
    {
        r = 0x100;
    }
    else if (a > 0x400)
    {
        r = 0x80;
    }
    else if (a > 0x200)
    {
        r = 0x40;
    }
    else if (a < 0x101)
    {
        r = 0x10;
    }
    return r;
}

#if 0
// Not matched
void sub_800A4940(int a, int b)
{
    unsigned short* p;
    if (unknownFlags_8008D678 & 0x20000)
    {
        p = (unsigned short*)sub_800B322C();
    }
    else
    {
        p = (unsigned short*)sub_800A53CC();
    }
    if (p)
    {
        p += b;
        if (p)
        {
            *p &= ~(0x1f << (a * 5));
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800A4940);

INCLUDE_OVERLAY_ASM(game, sub_800A49CC);

INCLUDE_OVERLAY_ASM(game, sub_800A4DD0);

INCLUDE_OVERLAY_ASM(game, sub_800A5030);

// Matched
int sub_800A5240(int x, int y)
{
    if (y != -1)
    {
        return sub_800A52EC(dword_800AE3D0, 0x11, x) != sub_800A52EC(dword_800AE3D0, 0x11, y);
    }
    return 1;
}

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

// Matched
int sub_800A52EC(short** tab, int n, int key)
{
    int r = -1;
    int i;
    for (i = 0; i < n; i++)
    {
        short* q = tab[i];
        while (*q != -1)
        {
            if (key == *q)
            {
                r = i;
                goto done;
            }
            q++;
        }
    }
done:
    return r;
}

// Matched
int sub_800A5354(void)
{
    int v = -1;
    switch (sub_80039FB0())
    {
    case 0xf:
        v = 0;
        break;
    case 0x10:
        v = 1;
        break;
    case 0x11:
        v = 2;
        break;
    }
    return v;
}

// Matched
unsigned short* sub_800A53CC(void)
{
    char* b = (char*)&saveData_8008B570;
    unsigned short* r = 0;
    if (((GameSave2_1*)b)->f2e4 == 4)
    {
        if (((GameSave2_1*)b)->f2e8 == 1)
        {
            r = (unsigned short*)(b + 0x838);
        }
        else if (((GameSave2_1*)b)->f2e8 == 2)
        {
            r = (unsigned short*)(b + 0x850);
        }
        else if (((GameSave2_1*)b)->f2e8 == 3)
        {
            r = (unsigned short*)(b + 0x874);
        }
        else if (((GameSave2_1*)b)->f2e8 == 4)
        {
            r = (unsigned short*)(b + 0x8cc);
        }
    }
    else if (((GameSave2_1*)b)->f2e4 == 5)
    {
        if (((GameSave2_1*)b)->f2e8 == 1)
        {
            r = (unsigned short*)(b + 0x8f8);
        }
        else if (((GameSave2_1*)b)->f2e8 == 2)
        {
            r = (unsigned short*)(b + 0x90c);
        }
        else if (((GameSave2_1*)b)->f2e8 == 3)
        {
            r = (unsigned short*)(b + 0x92c);
        }
    }
    return r;
}

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

extern int name_800AEB80[];
extern int name_800AEBBC;
extern int name_800AEBC0[];
extern int name_800AEBC8;
extern int name_800AEBCC[];
extern char name_80091C10[];
extern void sub_80026DE8(void* a, int b, void* c);
void sub_800A54A0(void)
{
    if (dword_800AEB7C != 2)
        sub_800A5854();
    if (name_800AEB80[1])
        sub_8003FEC8(&name_800AEB80[1]);
    if (name_800AEBBC)
    {
        sub_8003FE38(name_80091C10, name_800AEBBC);
        name_800AEBBC = 0;
    }
    if (name_800AEBC0[0])
    {
        sub_8003FE38(name_80091C10, name_800AEBC0[0]);
        name_800AEBC0[0] = 0;
    }
    if (name_800AEBC0[1])
    {
        sub_8003FE38(name_80091C10, name_800AEBC0[1]);
        name_800AEBC0[1] = 0;
    }
    if (name_800AEBC8)
    {
        sub_8003FE38(name_80091C10, name_800AEBC8);
        name_800AEBC8 = 0;
    }
    if (name_800AEBCC[1])
    {
        sub_80026DE8(&name_800AEBCC[1], name_800AEBCC[0], name_80091C10);
        name_800AEBCC[0] = 0;
    }
}

INCLUDE_OVERLAY_ASM(game, sub_800A55B0);

INCLUDE_OVERLAY_ASM(game, sub_800A5628);

INCLUDE_OVERLAY_ASM(game, sub_800A56BC);

// Matched
void sub_800A5804(int a)
{
    if (a == 0)
    {
        AllocMdecVLCBuffer_80041848();
    }
    else if (a == 1)
    {
        sub_8004188C();
    }
    dword_800AEB7C = a;
}

// Matched
int sub_800A5854(void)
{
    int old = dword_800AEB7C;
    if (old == 0)
    {
        FreeMdecBuffer_800418CC();
    }
    else if (old == 1)
    {
        sub_800418FC();
    }
    dword_800AEB7C = 2;
    return old;
}

extern int name_800AEBD4;
extern int name_800AEBEC;
extern unsigned int name_80091C38;
void sub_800A58B4(void)
{
    GameNode_1* n = dword_8008D410;
    int i;
    int cnt = n->count_c;
    GameRect_1* r;
    for (i = 0; i < cnt; i++)
    {
        GameObj5_1* o = &n->sub_10;
        if ((o->flags_0 & 0x8001) == 1)
            sub_800A6168(o, o->obj_14);
        n = n->next_4;
    }
    dword_800AEBD8 = -1;
    dword_800AEBDC = 0;
    name_800AEBD4 = 0;
    sub_80043B40((int*)dword_8008D410);
    sub_80037AC8((int)&dword_8008BD18);
    if (!(name_80091C38 & 0x40))
    {
        r = &stru_8008D420;
        r->x = 0;
        r->w = 0x140;
        r->y = 0;
        r->h = 0xf0;
    }
    sub_8001A9A4();
    dword_800AEBF0 = 0;
    dword_800AEBE8 = 0x8000;
    name_800AEBEC = 0;
    dword_800AEBE0 = 0;
    dword_800AEBF4 = 0;
}

// Matched
int* sub_800A59D0(int v)
{
    GameObj5_1* p = (GameObj5_1*)sub_80043AF8((EventNode*)dword_8008D410);
    if (p)
    {
        int* q = p->obj_14;
        int i;
        p->flags_0 = ((((p->flags_0 | 1) & ~0x8000) | 4) & ~0x8000);
        q[1] = v;
        q[2] = v;
        q[3] = v;
        q[4] = dword_800AEBDC;
        q[0x114 / 4] = 0;
        for (i = 7; i >= 0; i--)
        {
            q[51 + i] = 0;
        }
        sub_800A5B54(q);
        p->fn_8 = sub_800A6060;
        p->fn_c = sub_800A6168;
        dword_800AEBDC++;
        return (int*)p;
    }
    return 0;
}

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

// Matched
int sub_800A5AE4(int a)
{
    GameNode_1* n = dword_8008D410;
    GameObj5_1* o;
    int i;
    int cnt = n->count_c;
    for (i = 0; i < cnt; i++)
    {
        o = &n->sub_10;
        if ((o->flags_0 & 0x8001) == 1)
        {
            if (a == o->obj_14[4])
            {
                return (int)o;
            }
        }
        n = n->next_4;
    }
    return 0;
}

// Matched
void sub_800A5B54(int* p)
{
    int i;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
    p[8] = 0;
    p[0] = 0;
    p[0xb4 / 4] = 0;
    p[0xb8 / 4] = 0;
    p[0xbc / 4] = 0;
    p[0xc0 / 4] = 0;
    p[0xc4 / 4] = 0;
    p[0xc8 / 4] = -1;
    p[0xec / 4] = 0;
    p[0x110 / 4] = 0;
    p[0x118 / 4] = 0;
    ((short*)p)[0x100 / 2] = -1;
    ((short*)p)[0x102 / 2] = -1;
    p[0x104 / 4] = -1;
    p[0x108 / 4] = 0;
    p[0x11c / 4] = 0;
    p[0x120 / 4] = 0;
    p[0xf0 / 4] = 0;
    for (i = 4; i >= 0; i--)
    {
        p[9 + i] = 0;
    }
}

// Matched
void sub_800A5BCC(int a)
{
    GameNode_1* n = dword_8008D410;
    int i;
    int cnt = n->count_c;
    for (i = 0; i < cnt; i++)
    {
        GameObj5_1* o = &n->sub_10;
        if ((o->flags_0 & 0x8001) == 1)
        {
            int* q = o->obj_14;
            int m = 1 << a;
            q[6] &= ~m;
            q[8] &= ~m;
        }
        n = n->next_4;
    }
}

INCLUDE_OVERLAY_ASM(game, sub_800A5C40);

// Matched
int* sub_800A5DDC(int a, int b, int* c)
{
    GameNode_1* n = dword_8008D400;
    int i;
    int cnt = n->count_c;
    for (i = 0; i < cnt; i++)
    {
        GameObj5_1* o = &n->sub_10;
        if ((o->flags_0 & 0x8001) == 1)
        {
            int* q = o->obj_14;
            if (c != q)
            {
                if (b == 0)
                {
                    if (a == q[1])
                    {
                        return q;
                    }
                }
                else
                {
                    if (a == q[4])
                    {
                        return q;
                    }
                }
            }
        }
        n = n->next_4;
    }
    return 0;
}

// Matched
int sub_800A5E68(void)
{
    return dword_800AEBD8 >= 0;
}

int sub_800A5E80(int a)
{
    GameNode_1* n = dword_8008D400;
    int i;
    int cnt = n->count_c;
    for (i = 0; i < cnt; i++)
    {
        GameObj5_1* o = &n->sub_10;
        if ((o->flags_0 & 0x8001) == 1)
        {
            int* q = o->obj_14;
            if (q[0x78 / 4] != 0 && (q[0x84 / 4] & 0xBFFFFFFF) == a)
                return 1;
        }
        n = n->next_4;
    }
    n = dword_8008D410;
    cnt = n->count_c;
    for (i = 0; i < cnt; i++)
    {
        GameObj5_1* o = &n->sub_10;
        if ((o->flags_0 & 0x8001) == 1)
        {
            int* q = o->obj_14;
            if (q[0xc8 / 4] == a)
                return 1;
        }
        n = n->next_4;
    }
    return 0;
}

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

// Matched
void sub_800A5FAC(void)
{
    if (dword_800AEBE4)
    {
        GameSave3_1* sd = (GameSave3_1*)&saveData_8008B570;
        GameS3_1 v;
        sub_800AD16C(4, sd->f2e8 + 4);
        sub_800ADCEC(&v, sub_800A683C(-1));
        sub_800AD0F8(0);
        dword_80091C94 = 1;
        dword_80091C54 = 0;
        sd->f2f0 = 0;
        dword_80091C9C = 1;
        dword_80091C8C = 0;
        sd->f2e4 = v.a;
        sd->f2e8 = v.b;
        sd->f2ec = v.c;
        unknownFlags_8008D678 &= ~0x20000;
    }
}

typedef struct GameRun_1
{
    unsigned int f0;
    int f4;
    int** f8;
    int fC;
} GameRun_1;
extern int (*name_800BCDBC[])(GameRun_1*);
extern void sub_800BC2B4(GameRun_1* q);
void sub_800A6060(GameTask_1* t, GameRun_1* q)
{
    while (1)
    {
        if (dword_800B0EC0 != 1)
            break;
        if (name_800BCDBC[*(int*)q->f8](q) == 0)
            break;
    }
    if (q->f0 & 0x40)
        sub_800BC2B4(q);
    if (q->f0 & 0x10)
    {
        q->f0 &= ~0x10;
        q->f8 = (int**)q->fC;
    }
    if (q->f0 & 1)
    {
        t->f0 &= ~1;
        t->f0 |= 0x8000;
        t->f0 &= ~4;
        t->f0 |= 0x8000;
    }
}

// Matched
void sub_800A6168(GameTask_1* t, GameQ_1* q)
{
    if (dword_800AEBD8 == *(int*)((char*)q + 0x10))
    {
        sub_800B8A34(q);
    }
    t->f0 = (((t->f0 & ~1) | 0x8000) & ~4) | 0x8000;
}

INCLUDE_OVERLAY_ASM(game, sub_800A61CC);

INCLUDE_OVERLAY_ASM(game, sub_800A6308);

INCLUDE_OVERLAY_ASM(game, sub_800A6434);

// Matched
int sub_800A6504(int a)
{
    return sub_800B76B8(dword_8008B520 + (a << 3)) >= 0;
}

// Matched
void sub_800A6534(int a, int b)
{
    dword_8008B518[a] = b;
}

// Matched
void sub_800A654C(int a, int b)
{
    dword_8008B534[a] = b;
}

// Matched
void sub_800A6564(GameJ_1* p, int b)
{
    if (p->h0 >= 0)
    {
        sub_800A6534(p->h0, b);
    }
    if (p->h2 >= 0)
    {
        sub_800A654C(p->h2, b);
    }
}

// Matched
int sub_800A65BC(int a, int b)
{
    return (unsigned int)(sub_8003BA18((short)(a - b)) + 0x198) < 0x331;
}

// Matched
int sub_800A65F0(int* a, int* b, unsigned short* q, int r)
{
    unsigned int u = 0xfff;
    sub_8003B740(b, a, &u);
    if (u < (unsigned int)(r * r))
    {
        int d = GameFn_8003B9E0(b, a);
        if ((unsigned int)(sub_8003BA18((short)(q[1] - d)) + 0x198) < 0x331)
        {
            return 1;
        }
    }
    return 0;
}

#if 0
// Not matched
int sub_800A66A4(int* p, int* x, unsigned short* q)
{
    int v = p[0];
    if (v >= 0 && sub_800A6504(v))
    {
        int d = GameFn_8003B9E0(x, p + 1);
        if ((unsigned int)(sub_8003BA18((short)(q[1] - d)) + 0x198) < 0x331)
        {
            return 1;
        }
    }
    return 0;
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800A66A4);

int sub_800A6738(unsigned int a)
{
    dword_800AEBE8 = 0x8000;
    if (a <= 0xfffe)
    {
        GameTable_1* t;
        dword_800AEBE8 = a;
        t = sub_800A55B0(1);
        if (a < t->count)
        {
            int off = a * 8;
            off += 4;
            return *(int*)((char*)t + off);
        }
        return 0;
    }
    return a;
}

// Matched
int sub_800A67B4(unsigned int* p)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (p[6] & (1 << i))
        {
            if (i == 0)
            {
                sub_800A8EA4();
            }
            else
            {
                sub_800A7AD8(i - 1);
            }
        }
    }
    return 0;
}

// Matched
void sub_800A6830(int a)
{
    dword_800AEBF0 = a;
}

// Matched
int sub_800A683C(int x)
{
    int v = sub_800AD154(5) << 8;
    v += sub_800AD154(6);
    if (v == 0)
    {
        v = 0x66;
        sub_800AD16C(5, 0);
        sub_800AD16C(6, v);
    }
    if (x >= 0)
    {
        int hi = x >> 8;
        sub_800AD16C(5, hi);
        sub_800AD16C(6, x - (hi << 8));
    }
    return v;
}

#if 0
// Not matched
void sub_800A68CC(GameTask_1* t, int* q)
{
    int i;
    int v;
    int v2;
    int* p;
    sub_800A72C8(dword_800B1DC8);
    v = dword_800B1DC8[1];
    q[0] = v;
    v2 = v;
    q[1] = v;
    q[2] = v2;
    p = q + 11;
    for (i = 11; i >= 0; i--)
    {
        p[3] = 0;
        p--;
    }
    q[0xf] = sub_800435B4(dword_800B0DA4);
    dword_8008B540 = 0;
    dword_800B0698 = 0;
    t->next_8 = sub_800A6968;
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800A68CC);

#if 0
// Not matched
void sub_800A6968(GameTask_1* t, GameQ_1* q)
{
    if (dword_800B09FC[0].p0 != 0)
    {
        GameLst_1* l = dword_800B09FC;
        do
        {
            sub_800A7450((GameNode_1*)*l->p0);
            if (dword_8008B540)
            {
                goto end;
            }
            l++;
        } while (l->p0 != 0);
    }
    if (dword_8008B540)
    {
        goto end;
    }
    sub_80030988();
    sub_800A73A8();
    sub_800A6C00(t, q);
    sub_800A6A48(t, q);
    t->next_8 = sub_800A6B00;
end:
    dword_8008B540 = 0;
    dword_800B0698 = 0;
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800A6968);

INCLUDE_OVERLAY_ASM(game, sub_800A6A48);

#if 0
// Not matched
void sub_800A6B00(GameTask_1* t, GameQ_1* q)
{
    GameLst_1* l0 = dword_800B0D74[*(int*)q];
    if (l0->p0 != 0)
    {
        GameLst_1* l = l0;
        do
        {
            sub_800A7450((GameNode_1*)*l->p0);
            if (dword_8008B540)
            {
                goto end;
            }
            l++;
        } while (l->p0 != 0);
    }
    if (unknownFlags_8008D678 & 0x8000000)
    {
        t->next_8 = sub_800A6CCC;
        goto end;
    }
    if (dword_800B0698 != 0)
    {
        sub_800A6C00(t, q);
        sub_800A6A48(t, q);
    }
end:
    dword_8008B540 = 0;
    dword_800B0698 = 0;
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800A6B00);

void sub_800A6C00(GameTask_1* t, int* q)
{
    GameLst_1* l0 = dword_800B0D74[q[0]];
    GameLst_1* l;
    int one = 1;
    if (l0->p0 != 0)
    {
        l = l0;
        do
        {
            if (l->f4 & (one << q[2]))
                sub_800A74F0((GameNode_1*)*l->p0);
            l++;
        } while (l->p0 != 0);
    }
    if (q[0] == 11)
        q[0] = q[1];
    q[1] = q[0];
    q[0] = q[2];
}

// Matched
void sub_800A6CCC(GameTask_1* t, GameQ_1* q)
{
    sub_800438F8(q->f3c);
    sub_80043A5C(q->f3c);
    bStopDrawingMovie_8008D45C = 1;
    t->f0 = (t->f0 & ~1) | 0x8000;
}

// Matched
void sub_800A6D30(int a)
{
    int* w = (int*)dword_8008D46C[9];
    dword_800B0698 = 1;
    w[2] = a;
}

int sub_800A6D50(int a)
{
    int* p = (int*)dword_8008D46C[9];
    int r = 0;
    switch ((unsigned)a)
    {
    case 0:
        r = p[0];
        break;
    case 1:
        r = p[1];
        break;
    case 2:
        r = p[2];
        break;
    }
    return r;
}

INCLUDE_OVERLAY_ASM(game, sub_800A6DAC);

typedef struct GameD_1
{
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    void (*f1C)(int);
} GameD_1;
extern int sub_8003BE30();
extern void sub_8001C224();
extern void sub_8001C290();
extern void sub_8001C260();
extern void sub_800A6DAC();
void sub_800A70F8(GameTask_1* t, GameD_1* q)
{
    int c = 0;
    GameD_1* r = q;
    if (q->f8)
        c = (unsigned)sub_8003BE30(q->f4) > 0;
    if (c == 0)
    {
        if (q->f1C)
            q->f1C(q->f18);
        sub_800A6D30(q->f0);
        t->next_8 = sub_800A6DAC;
        if (q->fC)
            sub_8001C224();
        else
            sub_8001C290();
        dword_8008B540 = r->f10;
    }
    else
    {
        if (q->f14 == 0)
        {
            sub_8001C260();
            q->f14 = 1;
            sub_800A6D30(0xb);
            t->next_8 = sub_800A70F8;
        }
        dword_8008B540 = 1;
    }
}

// Matched
void sub_800A7204(GameSub_1* p)
{
    if (p->f4 == 0)
    {
        sub_800BAE2C(0, *(short*)&p->f8);
        p->f0 = 0;
    }
    else if (p->f4 == 1)
    {
        sub_800BAE2C(1, *(short*)&p->f8);
        p->f0 = 0;
    }
    else
    {
        if (p->f4 == 2)
        {
            sub_800B66C4(*(short*)&p->f8);
        }
        p->f0 = 0;
    }
}

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

void sub_800A73A8(void)
{
    GameRect_1* r = &stru_8008D420;
    dword_8008D40C = 0x1000;
    dword_8008D404 = 0;
    r->x = 0;
    r->w = 0x140;
    r->y = 0;
    r->h = 0xf0;
    unknownFlags_8008D678 &= ~0x8000000;
    sub_80026FAC();
    GameFn_800A094C();
    sub_8002FEB8();
    sub_8001A38C();
    sub_800376A8();
    sub_800A8140();
    sub_800A94CC();
    dword_80091C94 = dword_800B1DC8[0];
}

// Matched
void sub_800A7450(GameNode_1* n)
{
    int i;
    int cnt = n->count_c;
    for (i = 0; i < cnt; i++)
    {
        if (dword_8008B540)
        {
            break;
        }
        if ((n->sub_10.flags_0 & 0x8001) == 1)
        {
            GameObj5_1* o = &n->sub_10;
            o->fn_8(o, o->obj_14);
        }
        n = n->next_4;
    }
}

// Matched
void sub_800A74F0(GameNode_1* n)
{
    int i;
    int cnt = n->count_c;
    for (i = 0; i < cnt; i++)
    {
        if ((n->sub_10.flags_0 & 0x8004) == 4)
        {
            GameObj5_1* o = &n->sub_10;
            o->fn_c(o, o->obj_14);
        }
        n = n->next_4;
    }
}

extern void sub_8001AF64(void* p);
extern void sub_80066E38(int a);
extern char name_800B0EA4[];
extern char name_80096090[];
int sub_800A7574(void)
{
    sub_8001AF64(name_800B0EA4);
    sub_8003FEC8(name_80096090);
    sub_80066E38(0);
    if (unknownFlags_8008D678 & 0x40000000)
    {
        unknownFlags_8008D678 &= 0xBFFFFFFF;
        return 8;
    }
    if (unknownFlags_8008D678 & 0x10000000)
        return 7;
    return 0xd;
}

// Matched
void sub_800A75F8(GameTask_1* t, void** q)
{
    *q = sub_80020D1C(1, 0xa);
    t->next_8 = sub_800A7654;
    unknownFlags_8008D678 |= 0x4000000;
}

// Matched
void sub_800A7654(GameTask_1* t, int* q)
{
    if (sub_8003BE30(q[0]) == 0)
    {
        t->next_8 = sub_800B6BFC;
    }
}

// Matched
void sub_800A7690(GameTask_1* t, void** q)
{
    *q = sub_80020D1C(1, 0x14);
    t->next_8 = sub_800A76D8;
}

// Matched
void sub_800A76D8(GameTask_1* t, int* q)
{
    if (sub_8003BE30(q[0]) == 0)
    {
        t->next_8 = sub_800B66DC;
    }
}

// Matched
void sub_800A7714(int a)
{
    dword_800B0EC0 = a;
}

// Matched
void sub_800A7720(GameTask_1* t)
{
    int n = dword_800B0EC0;
    if (n != 1)
    {
        void (*f)() = dword_800B0EB8[n].fn;
        t->next_8 = f;
        f(t);
    }
    else
    {
        t->f0 = (t->f0 & ~1) | 0x8000;
    }
}

// Matched
void sub_800A7784(void)
{
    dword_800B0EC4.count = 0;
}

// Matched
int sub_800A7790(void)
{
    return dword_800B0EC4.count;
}

#if 0
// Not matched
void sub_800A77A0(int a)
{
    GameList_1* l = &dword_800B0EC4;
    l->a[l->count] = a;
    l->b[l->count] = 0;
    l->c[l->count] = 0;
    l->count++;
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800A77A0);

// Matched
int sub_800A77F4(int a)
{
    return dword_800B0EC4.a[a];
}

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

// Matched
int sub_800A78A8(int a)
{
    if (a < sub_800A7790())
    {
        return ***(int***)(sub_800A77F4(a) + 0x10);
    }
    return 0;
}

// Matched
int sub_800A78F4(int a)
{
    if (a < sub_800A7790())
    {
        return *(short*)(**(int**)(sub_800A77F4(a) + 0x10) + 0x2a);
    }
    return 0;
}

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

// Matched
int sub_800A79C8(int a)
{
    if (a < sub_800A7790())
    {
        return ((*(unsigned int*)(*(int*)(sub_800A77F4(a) + 0x18) + 4) >> 13) ^ 1) & 1;
    }
    return 0;
}

// Matched
int sub_800A7A1C(int a)
{
    if (a < sub_800A7790())
    {
        return *(int*)(*(int*)(sub_800A77F4(a) + 0x18) + 0x15c);
    }
    return 0;
}

// Matched
int sub_800A7A60(int a)
{
    if (a < sub_800A7790())
    {
        return *(int*)(sub_800A77F4(a) + 0x18);
    }
    return 0;
}

// Matched
int sub_800A7A9C(int a)
{
    if (a < sub_800A7790())
    {
        return *(int*)(sub_800A77F4(a) + 0x1c);
    }
    return 0;
}

// Matched
void sub_800A7AD8(int a)
{
    sub_8001D9B0((struct_obj_A*)sub_800A7A60(a));
}

INCLUDE_OVERLAY_ASM(game, sub_800A7B00);

/* ---- GAME second half (G2) ---- */
typedef struct G2Inner
{
    unsigned int f0;
    char pad_4[0x98];
    int f9C;
    int fA0;
    int fA4;
    int fA8;
    int fAC;
    char pad_B0[0x16];
    short fC6;
} G2Inner;

typedef struct G2Ctx
{
    char pad_0[0x24];
    G2Inner* f24;
} G2Ctx;

typedef struct G2Obj
{
    unsigned int f0;
    char pad_4[0x2C];
    int f30;
} G2Obj;

typedef struct G2V12
{
    int a;
    int b;
    int c;
} G2V12;
typedef struct G2Inner2
{
    unsigned int f0;
    int f4;
    int f8;
    int fC;
    char pad_10[0x10];
    short s20;
    short f22;
    short f24;
    char pad_26[2];
    short f28;
    char pad_2A[0xA];
    int f34;
    int f38;
    char pad_3C[4];
    struct_obj_E* f40;
    char pad_44[4];
    G2V12 v48;
    G2V12 v54;
    G2V12 v60;
    char pad_6C[0xC];
    int f78;
    int f7c;
} G2Inner2;

typedef struct G2Ctx2
{
    char pad_0[0x24];
    G2Inner2* f24;
} G2Ctx2;

typedef struct G2Bits
{
    char pad_0[0x290];
    unsigned char b[0x20];
} G2Bits;
typedef struct G2Bits3
{
    char pad_0[0x2A3];
    unsigned char c[0x20];
} G2Bits3;
extern G2Ctx* dword_8008B4CC;
extern G2Ctx2* dword_8008B4A4;
extern char byte_8008BD38;
extern G2V12 levantPos_8008BD18;
extern int dword_8008BDA0;
extern short word_8008BDA4;
extern short word_8008BDA6;
extern char dword_800B1DF8;
extern char dword_800B0FB0;
extern void sub_800AC380(int);
extern int dword_8008B818;
extern int* dword_8007DC60;
extern unsigned char playerYan_8008B594[];
#define G2SAVE ((unsigned char*)&saveData_8008B570)
typedef struct G2Sv
{
    char pad_0[0x2FE];
    short s;
} G2Sv;
typedef struct G2Act
{
    unsigned int f0;
    char pad_4[4];
    int f8;
    int fC;
    int f10;
    int f14;
    char pad_18[4];
    short s1c;
    short s1e;
    short s20;
    unsigned short u22;
    short s24;
    short s26;
    short s28;
    short s2A;
    int f2C;
    char pad_30[4];
    int f34;
    int f38;
    char pad_3C[4];
    int f40;
} G2Act;
extern int sub_800A88E0();
extern void sub_800AB010();
extern int sub_800AC518();
extern void sub_800AC6A8();
extern int sub_800AC4A8();
extern int sub_800ADBA0(short*);
typedef struct G2Rec
{
    unsigned char f0;
    unsigned char f1;
    char pad_2;
    unsigned char f3;
    short s4;
    short s6;
    short s8;
    unsigned short sA;
    short sC;
    char pad_E[0x26];
    int f34;
    char pad_38[8];
} G2Rec;
#define G2REC(a, b) ((G2Rec*)sub_80024E38(dword_8007DC60[2]))
extern int sub_800AC794(int, int);
extern void sub_800A913C();
extern void sub_800ABAD4();
extern void sub_800AB444();
extern void sub_8001450C(int*, void*, int, int);
extern char dword_800795C0;
typedef struct G2Stat
{
    char pad_0[0x7D0];
    unsigned short cur;
    unsigned short max;
    unsigned short cur2;
    unsigned short max2;
} G2Stat;
typedef struct G2P
{
    short s0;
    short s2;
    unsigned short u4;
    unsigned short u6;
} G2P;
typedef struct G2E
{
    char pad_0[0x2F8];
    short a;
    short b;
    short c;
    short d;
} G2E;
typedef struct G2Save2
{
    char pad_0[0x2F4];
    int n;
} G2Save2;
extern unsigned char equippedWeaponId_8008BD54;
extern unsigned char equippedArmor_8008BD55;
extern unsigned char byte_8008BD56;
extern unsigned char* sub_800AD4D8();
extern int sub_800AD8E4();
typedef struct G2Sv4
{
    char pad_0[0x7E4];
    unsigned char b7E4;
    unsigned char b7E5;
    char pad_7E6[0x4A];
    int f830;
    short s834;
} G2Sv4;
extern int dword_800B116C[];
extern unsigned char dword_800B11B8[];
typedef struct G2Ent18
{
    char pad_0[0x18];
    struct_obj_A* f18;
} G2Ent18;
extern int sub_800A7790();
extern G2Ent18* name_800A77F4(int);
extern int sub_8001E1DC(struct_obj_A*);
extern void name_8001E28C(struct_obj_A*);
extern void sub_800ABC78();
extern void sub_800AA25C();
extern void sub_800AA51C();
extern void sub_800AACF8();
extern void sub_800AC02C();
extern int sub_800AD670(int, int);
extern int sub_80025924(int, int);
extern void sub_8003FF1C(void*, unsigned);
extern int sub_800ACB64();
extern void sub_80031494(int);
extern void sub_80031160(int, int);
typedef struct G2Sv5
{
    char pad_0[0x7B6];
    unsigned short u7B6;
} G2Sv5;
typedef struct G2Q
{
    char pad_0[4];
    unsigned int f4;
    char pad_8[0x770];
    int f778;
    unsigned short u77C;
} G2Q;
typedef struct G2Ent16
{
    short id;
    char pad_2[2];
    unsigned short u4;
    short s6;
    char pad_8[8];
} G2Ent16;
extern G2Ent16** name_800B0608[];
extern void sub_80014588(void*, void*, int);
extern void sub_80025C38(void*, int);
extern char dword_800A07E0[];
extern char dword_800A0808[];
extern int sub_8001AC8C(int);
extern void sub_800148F4(int);
extern int sub_800189F8();
extern short word_8008D782;
extern void sub_8004ED78(int);
#define G2LEV ((G2V12*)((char*)&saveData_8008B570 + 0x7A8))
extern int sub_8003B9E0(int*, int*);
typedef struct G2L
{
    char pad_0[0x14];
    int a;
    char pad_18[0xC];
    int b;
} G2L;
extern G2V12 dword_8007A0A4;
extern G2V12 dword_8007A0B0;
extern G2V12 dword_8007A0BC;
extern G2V12 dword_8007A0C8;
extern G2V12 dword_8007A0D4;
extern G2V12 dword_8007A0E0;
extern G2V12 dword_8007A0EC;
extern G2V12 dword_8007A0F8;
extern G2V12 dword_8007A104;
extern G2V12 dword_8007A110;
extern G2V12 dword_8007A11C;
extern G2V12 dword_8007A128;
extern G2V12 dword_8007A134;
extern G2V12 dword_8007A140;
extern G2V12 dword_8007A14C;
extern G2V12 dword_8007A164;
extern char dword_8007DC80;
extern char dword_8007DC88;
extern unsigned int dword_8008BD38;
extern void sub_800292D0();
typedef struct G2L2
{
    int f0;
    int f4;
    int rest[0x48];
} G2L2;
extern int dword_8001D060(int);
extern int sub_800A79C8(int);
extern int* name_800A7940(int);
extern void sub_8003B740();
extern int name_800B0EC4[];
extern int sub_800A6D50(int);
extern void sub_800A6D30(int);
extern int dword_8008B540;
extern void sub_800A9414(void*, int, int);
extern void sub_8002556C(int, int);
extern void sub_8003FF7C(void*);
extern char dword_800B1DD0;
extern int dword_800B11DC[];
extern int sub_80025440(int, int, int);
extern void sub_80025780(int, int, int);
extern int sub_800AC474(int);
extern int sub_800AC3E4();
extern int sub_800AC38C();
extern unsigned char* sub_800AD58C();
extern unsigned char* sub_800AD604(int);
extern int sub_800AD374(int);
extern int sub_800AD308(int);
extern int sub_800AD288(int, int);
extern int sub_800AD2C8(int, int);
extern int sub_800AD67C(int, int);
extern unsigned char* sub_800AC7B4(int);
extern int sub_800AD73C(int);
typedef struct G2Flags
{
    char pad_0[0x288];
    unsigned int w[2];
} G2Flags;
extern int sub_800AD8BC();
typedef struct G2Save
{
    char pad_0[0x24];
    int f24;
} G2Save;
extern void sub_80025884(int);
extern void sub_80024DC4(int);
extern short word_8008D668[2];
extern int sub_800AB304();
extern int sub_800AB354();
extern int sub_800AB85C();
extern void sub_800AB884();
extern void sub_800AB8AC();
extern void sub_800AC318();
extern void sub_800A5C40();
extern void sub_800AB910();
extern void sub_800ABBD8();


void sub_800A7BF0(int a)
{
    int i, end;
    G2L* q;
    struct_obj_A* o;
    if (a < 0)
    {
        i = 0;
        end = sub_800A7790();
    }
    else
    {
        i = a;
        end = a + 1;
    }
    for (; i < end; i++)
    {
        q = (G2L*)&name_800B0EC4[i];
        o = name_800A77F4(i)->f18;
        if (q->a)
        {
            if (q->b)
            {
                sub_8001D6EC(o, 0);
                sub_8001D730(o, 1);
                q->b = 0;
            }
            sub_8001D658((int**)o, 1);
            q->a = 0;
        }
    }
}

int sub_800A7CB8(int a)
{
    if (a < sub_800A7790())
        return sub_8001E1C8(name_800A77F4(a)->f18);
    return 0;
}

int sub_800A7CFC(int a)
{
    if (a < sub_800A7790())
        return sub_8001E1DC(name_800A77F4(a)->f18);
    return 0;
}

INCLUDE_OVERLAY_ASM(game, sub_800A7D40);

void sub_800A80C4(int a)
{
    if (a < sub_800A7790())
        name_8001E28C(name_800A77F4(a)->f18);
}

void sub_800A8108()
{
    sub_800A6D30(sub_800A6D50(1));
    dword_8008B540 = 1;
}

void sub_800A8138()
{
}

void sub_800A8140()
{
    G2Inner* p = dword_8008B4CC->f24;
    sub_8001450C((int*)((char*)p + 0x5C), (char*)p + 0x4C, (int)&dword_800795C0, 4);
    p->f0 = 0;
    p->f9C = 0;
    p->fC6 = 0;
}

INCLUDE_OVERLAY_ASM(game, sub_800A818C);

void sub_800A88A0(int a, int b)
{
    sub_800A88E0(a, b, sub_800A8930());
}

int sub_800A88E0(G2P* p, int a, int b)
{
    int x = b ^ a;
    if (x & 1)
        p->s0 = 0x130 - p->u4;
    else
        p->s0 = 0x10;
    if (x & 2)
        p->s2 = 0xE0 - p->u6;
    else
        p->s2 = 0x10;
    return x;
}

int sub_800A8930()
{
    int r = word_8008D668[0] > 0xA0;
    if (word_8008D668[1] >= 0x79)
        r += 2;
    return r;
}

void sub_800A895C()
{
    dword_8008B4CC->f24->f0 |= 0x41;
}

void sub_800A8984(int a)
{
    G2Inner* p = dword_8008B4CC->f24;
    p->f0 &= ~1;
    p->f0 &= ~0x10;
    sub_800AB444(a, p);
}

void sub_800A89C8()
{
    dword_8008B4CC->f24->f0 &= ~0x40;
}

void sub_800A89F0()
{
    sub_800AB304();
}

void sub_800A8A10()
{
    sub_800AB354();
}

INCLUDE_OVERLAY_ASM(game, sub_800A8A30);

int sub_800A8BE4()
{
    return dword_8008B4CC->f24->fC6 == 4;
}

void sub_800A8C0C()
{
    dword_8008B4CC->f24->f0 |= 4;
}

char* sub_800A8C34()
{
    return &byte_8008BD38;
}

char* sub_800A8C40()
{
    return (char*)&levantPos_8008BD18;
}

void sub_800A8C4C(int a)
{
    G2Stat* s = (G2Stat*)&saveData_8008B570;
    s->cur -= a;
    if ((short)s->cur < 0)
    {
        s->cur = 0;
        return;
    }
    if ((short)s->max < (short)s->cur)
        s->cur = s->max;
}

void sub_800A8CA0(int a)
{
    G2Stat* s = (G2Stat*)&saveData_8008B570;
    s->cur2 -= a;
    if ((short)s->cur2 < 0)
    {
        s->cur2 = 0;
        return;
    }
    if ((short)s->max2 < (short)s->cur2)
        s->cur2 = s->max2;
}

void sub_800A8CF4()
{
    dword_8008B4CC->f24->fC6 = 0;
}

void sub_800A8D0C(int* a)
{
    G2Inner* p = dword_8008B4CC->f24;
    p->fC6 = 7;
    p->fA4 = a[0];
    p->fA8 = a[1];
    p->fAC = a[2];
}

void sub_800A8D48(int* a)
{
    G2Inner* p = dword_8008B4CC->f24;
    p->fC6 = 8;
    p->fA4 = a[0];
    p->fA8 = a[1];
    p->fAC = a[2];
}

int sub_800A8D84()
{
    return dword_8008B4CC->f24->fC6 == 1;
}

void sub_800A8DAC()
{
    sub_800AB85C();
}

void sub_800A8DCC()
{
    sub_800AB884();
}

void sub_800A8DEC()
{
    sub_800AB8AC();
}

void sub_800A8E0C()
{
    G2Inner* p = dword_8008B4CC->f24;
    p->fC6 = 9;
    p->f0 |= 0x20;
}

void sub_800A8E38()
{
    G2Inner* p = dword_8008B4CC->f24;
    p->f0 &= ~0x20;
    sub_800A913C();
    sub_800ABAD4();
}

int sub_800A8E7C()
{
    return dword_8008B4CC->f24->fC6 == 9;
}

void sub_800A8EA4()
{
    sub_800AC318();
}

INCLUDE_OVERLAY_ASM(game, sub_800A8EC4);

int sub_800A8FE0()
{
    return dword_8008B4CC->f24->fC6 == 9;
}

INCLUDE_OVERLAY_ASM(game, sub_800A9008);

void sub_800A911C()
{
    sub_800A5C40();
}

void sub_800A913C()
{
    dword_8008B4CC->f24->f0 |= 0x80;
}

int sub_800A9164(int* out)
{
    int best = 0x7FFFFFFF;
    int n = sub_800A7790();
    int i;
    int* v;
    short y;
    for (i = 0; i < n; i++)
    {
        if (sub_800A79C8(i))
        {
            v = name_800A7940(i);
            sub_8003B740(G2LEV, v, &best);
            if (best <= 0x9C3F)
            {
                y = sub_8003BA18((short)(((G2Sv5*)&saveData_8008B570)->u7B6 - sub_8003B9E0((int*)G2LEV, v)));
                *out = y;
                if ((unsigned)(y + 0x3FF) < 0x7FF)
                    return 1;
            }
        }
    }
    return 0;
}

int sub_800A926C()
{
    int best = 0x7FFFFFFF;
    int n = sub_800A7790();
    int i;
    int* v;
    short y;
    for (i = 0; i < n; i++)
    {
        if (sub_800A79C8(i))
        {
            v = name_800A7940(i);
            sub_8003B740(G2LEV, v, &best);
            if (best <= 0x9C3F)
            {
                y = sub_8003BA18((short)(((G2Sv5*)&saveData_8008B570)->u7B6 - sub_8003B9E0((int*)G2LEV, v)));
                if (!((unsigned)(y + 0x400) < 0x801))
                    return 1;
            }
        }
    }
    return 0;
}

void sub_800A9364()
{
    sub_800AB910();
}

void sub_800A9384()
{
    sub_800ABBD8();
}

void sub_800A93A4(int* a)
{
    G2Inner2* p = dword_8008B4A4->f24;
    a[0] = (int)sub_80024E64(p->f40);
    a[1] = (int)&levantPos_8008BD18;
    a[2] = (int)p + 0x590;
    a[3] = (int)p + 0x90;
    a[11] = (int)&dword_800B0FB0;
    a[12] = 0;
}

void sub_800A9414(void* pv, int b, int c)
{
    G2Act* p = (G2Act*)pv;
    sub_80025C38(p->f40, (((unsigned)unknownFlags_8008D678 >> 24) ^ 1) & 1);
    sub_8001450C((int*)((char*)p + 0x780), (char*)p + 0x770, (int)&dword_800795C0, 4);
    sub_800AB010(p, b, c, 0);
    p->fC = 0;
    if (sub_800AAFD8(p->s1e) != 1)
        p->f0 &= ~0x10;
    sub_800ABAD4();
    sub_800AA140(p);
}

typedef struct G2Init_1
{
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    char pad_14[4];
    short s18;
    short s1a;
    short s1c;
    short s1e;
    char pad_20[6];
    short s26;
    char pad_28[8];
    int f30;
    char pad_34[8];
    int f3C;
} G2Init_1;
extern void sub_800B80C8(void* p);
void sub_800A94CC(void)
{
    G2Init_1* p = (G2Init_1*)dword_8008B4A4->f24;
    p->s1c = 3;
    p->s1e = 3;
    p->fC = 0;
    p->f8 = 0;
    p->f10 = 0;
    p->s26 = 0;
    p->f0 = 0;
    p->f30 = 0;
    p->s1a = 0;
    p->s18 = 0x1000;
    p->f4 = 0;
    sub_800AB8DC();
    sub_800A9414(p, 0, 3);
    sub_800AB150((G2Obj*)p);
    sub_800B80C8(p);
    p->f3C = dword_8008BD38;
    sub_800ABECC(dword_8008BD38);
}

void sub_800A955C()
{
}

INCLUDE_OVERLAY_ASM(game, sub_800A9564);

INCLUDE_OVERLAY_ASM(game, sub_800A9708);

void sub_800A99DC(G2Q* p)
{
    if (p->f4 & 0x10000000)
        p->f778 = -0x40;
    if (p->f4 & 0x20000000)
        p->f778 = 0x40;
    if (p->f4 & 0x40000000)
        p->f778 /= 2;
    p->f4 &= ~0x30000000;
    sub_80014588((char*)p + 0x780, (char*)p + 0x770, frameCount_8008D3FC);
    ((G2Sv5*)&saveData_8008B570)->u7B6 += p->u77C;
}

INCLUDE_OVERLAY_ASM(game, sub_800A9A9C);

INCLUDE_OVERLAY_ASM(game, sub_800AA140);

int sub_800AA1C0(int* p)
{
    return p[1] & 0xFFFFFFF;
}

int sub_800AA1D4(unsigned char* p)
{
    return p[1] & 1;
}

void sub_800AA1E0(G2Act* a)
{
    a->s20 = a->u22;
    sub_800AB010(a, 0x17, 3, 0);
    a->fC = 3;
}

void sub_800AA220(G2Act* a)
{
    sub_8001C440(a->f40, sub_800AC4A8(a->s1c), a->f10);
}

INCLUDE_OVERLAY_ASM(game, sub_800AA25C);

void sub_800AA3F0(G2Act* a)
{
    sub_800AB010(a, 0, 3, 0);
    a->fC = 0;
    a->f0 |= 0x2000;
}

#if 0
void sub_800AA430(G2Act* p)
{
    G2L2 L;
    int v19;
    short* r17;
    unsigned short r16;
    if (p->f2C != 0x46)
    {
        v19 = 4;
        if (!((unsigned short)(p->s1c - 7) < 2))
            v19 = p->s2A;
        L.f0 = p->f2C;
        r17 = sub_800AC9CC(p->s20);
        r16 = sub_800AC834(p->s1c, sub_800AC474(p->s1c));
        L.f4 = sub_80018200(r17, r16, (unsigned short)sub_800AC878(p->s1c, sub_800AC474(p->s1c)), v19, p->f2C);
        sub_800A93A4(L.rest);
        sub_800182B8(&L, p->f38);
        sub_800184DC((int)&L, 0);
    }
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800AA430);

INCLUDE_OVERLAY_ASM(game, sub_800AA51C);

INCLUDE_OVERLAY_ASM(game, sub_800AACF8);

void sub_800AAF58(G2Act* a)
{
    switch ((unsigned)a->fC)
    {
    case 0:
        sub_800AA25C(a);
        break;
    case 1:
        sub_800AA51C(a);
        break;
    case 2:
        sub_800AACF8(a);
        break;
    case 3:
        sub_800AC02C(a);
        break;
    default:
        break;
    }
}

int sub_800AAFD8(int a)
{
    if (sub_800AC518(a))
        return 1;
    sub_800AC6A8(a);
    return 0;
}

#if 0
void sub_800AB010(G2Act* p, int a, int b, int c)
{
    unsigned short t;
    int t3;
    if (c == 0)
        c = (short)sub_800AC7F0(b, sub_800AC474(b));
    if (p->f8 == a && p->s1c == b)
        return;
    p->s28 = 0;
    if (b < 0)
    {
        p->f8 = a;
    }
    else
    {
        if (a < 0)
        {
            t3 = p->f10;
            t = p->s1c;
            p->s1c = b;
        }
        else
        {
            t3 = p->f10;
            t = p->s1c;
            p->f8 = a;
            p->s1c = b;
        }
        p->f10 = c;
        p->s26 = 0;
        p->s1e = t;
        p->f14 = t3;
    }
    if (p->s1e != p->s1c)
    {
        p->f0 |= 8;
        if (sub_800AAFD8(p->s1e) == 1)
            p->f0 |= 0x10;
    }
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800AB010);

void sub_800AB114(G2Obj* p)
{
    p->f30 = 0x1000;
    p->f0 = (p->f0 | 4) & ~2;
}

void sub_800AB134(G2Obj* p)
{
    p->f30 = 0;
    p->f0 = (p->f0 | 2) & ~4;
}

void sub_800AB150(G2Obj* p)
{
    p->f30 = 0;
    p->f0 &= ~4;
    p->f0 &= ~2;
}

unsigned short sub_800AB170(int a)
{
    return sub_800AC944(a, sub_800AC474(a));
}

void sub_800AB1A4(int a)
{
    G2Inner2* p = dword_8008B4A4->f24;
    p->f0 |= 0x20;
    if (a == 1)
    {
        p->f0 |= 0x800;
        p->f0 &= ~0x8000;
    }
}

int sub_800AB1EC(int a, int b, int c, int d)
{
    G2Inner2* p = dword_8008B4A4->f24;
    if (!(p->f0 & 1))
    {
        if (b == 1)
            p->f0 |= 0x200;
        else
            p->f0 &= ~0x200;
        p->s20 = a;
        p->f38 = c;
        p->f34 = d;
        p->f0 &= ~0x2000;
        p->f0 |= 1;
        p->f0 &= ~0x20;
        return 1;
    }
    return 0;
}

void sub_800AB264()
{
    dword_8008B4A4->f24->f0 |= 0x400;
}

void sub_800AB28C()
{
    dword_8008B4A4->f24->f0 &= ~0x400;
}

void sub_800AB2B4()
{
    dword_8008B4A4->f24->f0 |= 0x10000;
}

void sub_800AB2DC()
{
    dword_8008B4A4->f24->f0 &= ~0x10000;
}

int sub_800AB304()
{
    return (dword_8008B4A4->f24->f0 & 1) ^ 1;
}

int sub_800AB32C()
{
    return dword_8008B4A4->f24->f8 == 0xD;
}

int sub_800AB354()
{
    unsigned t = dword_8008B4A4->f24->f0 & 0x400;
    return t != 0;
}

int sub_800AB37C(int v)
{
    dword_8008B4A4->f24->f4 = v;
    return 1;
}

int sub_800AB39C()
{
    return dword_8008B4A4->f24->f4;
}

void sub_800AB3BC()
{
    dword_8008B4A4->f24->f28 = 0;
}

void sub_800AB3D4()
{
    G2Inner2* p = dword_8008B4A4->f24;
    if (!(p->f0 & 0x100))
    {
        p->f0 |= 0x4100;
        p->v60.a = levantPos_8008BD18.a;
        p->v60.b = levantPos_8008BD18.b;
        p->v60.c = levantPos_8008BD18.c;
        p->v54.a = p->v48.a;
        p->v54.b = p->v48.b;
        p->v54.c = p->v48.c;
    }
}

void sub_800AB444(int a)
{
    G2Inner2* p = dword_8008B4A4->f24;
    if (p->f0 & 0x100)
    {
        if (a == 1)
            p->f0 |= 0x1000;
        else
            p->f0 &= ~0x1000;
        p->f0 &= ~0x100;
        dword_8008BD18.x = p->v60.a;
        dword_8008BD18.y = p->v60.b;
        dword_8008BD18.z = p->v60.c;
        p->v48.a = p->v60.a;
        p->v48.b = p->v60.b;
        p->v48.c = p->v60.c;
    }
}

short sub_800AB4D8(int a)
{
    int s = (unsigned short)sub_800AC834(a, sub_800AC474(a));
    int e = (unsigned short)sub_800AC878(a, sub_800AC474(a));
    int t;
    switch ((unsigned)a)
    {
    case 25:
    case 26:
    case 28:
        return sub_800AC8BC(a, sub_800AC474(a)) + (e - s) * 2;
    case 7:
    case 8:
        t = sub_800AC8BC(14, sub_800AC474(14));
        return t + sub_800AC8BC(a, sub_800AC474(a)) + (e - s) * 30;
    }
    return sub_800AC8BC(a, sub_800AC474(a));
}

short sub_800AB5F8(int a)
{
    return sub_800AC834(a, sub_800AC474(a));
}

short sub_800AB630(int a)
{
    int s = (unsigned short)sub_800AC834(a, sub_800AC474(a));
    int e = (unsigned short)sub_800AC878(a, sub_800AC474(a));
    int t;
    switch ((unsigned)a)
    {
    case 25:
    case 26:
    case 28:
        return sub_800AC878(a, sub_800AC474(a)) + (e - s) * 2;
    case 7:
    case 8:
        t = sub_800AC8BC(14, sub_800AC474(14));
        return t + sub_800AC878(a, sub_800AC474(a)) + (e - s) * 30;
    }
    return sub_800AC878(a, sub_800AC474(a));
}
INCLUDE_OVERLAY_ASM(game, dword_800A08C8);

INCLUDE_OVERLAY_ASM(game, sub_800AB750);

int sub_800AB85C()
{
    unsigned t = dword_8008B4A4->f24->f0 & 0x2000;
    return t != 0;
}

void sub_800AB884()
{
    dword_8008B4A4->f24->f0 &= ~0x4000;
}

void sub_800AB8AC()
{
    sub_800A9414(dword_8008B4A4->f24, 0, 3);
}

void sub_800AB8DC()
{
    G2Inner2* p = dword_8008B4A4->f24;
    p->f40 = sub_800AC38C();
}

void sub_800AB910()
{
    dword_8008B4A4->f24->f0 &= ~0x800;
}

int sub_800AB938()
{
    return ((unsigned char*)dword_8008B4A4->f24)[1] >> 7;
}

int sub_800AB958()
{
    return (unsigned)dword_8008B4A4->f24->f8 < 2;
}

void sub_800AB978(short a)
{
    G2Inner2* p = dword_8008B4A4->f24;
    p->f24 = -1;
    p->f22 = a;
    p->f0 &= ~0x20;
}

#if 0
void sub_800AB9A8(int a, int b, int c)
{
    G2Act* p = (G2Act*)dword_8008B4A4->f24;
    if (sub_800AC604(a, 0) == 0 && (b < 0 || sub_800AC604(b, 0) == 0))
    {
        sub_800AB010(p, 0x17, a, 0);
        p->fC = 2;
        if (c)
            p->f0 |= 0x10;
        else
            p->f0 &= ~0x10;
    }
    else
    {
        printf(dword_800A07E0, dword_800A0808, 0x6B9);
        sub_8004ED78(1);
        p->u22 = a;
        p->s20 = a;
        p->s24 = b;
        p->f0 &= ~0x20;
        p->f0 &= ~1;
    }
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800AB9A8);

void sub_800ABAA4(int a)
{
    G2Inner2* p = dword_8008B4A4->f24;
    p->f78 = a;
    p->f7c = 0;
    p->f0 |= 0x400000;
}

void sub_800ABAD4()
{
    G2Inner2* p = dword_8008B4A4->f24;
    p->f0 &= ~0x400000;
    sub_800ABC78(0);
    p->f0 = (p->f0 & ~0x800) | 8;
    sub_800AB010(p, 0, 3, 0);
    p->fC = 0;
}

int sub_800ABB44()
{
    return ((dword_8008B4A4->f24->f0 >> 22) ^ 1) & 1;
}

int sub_800ABB70()
{
    return dword_8008B4A4->f24->f8 == 0x17;
}

void sub_800ABB98(int a)
{
    G2Inner2* p = dword_8008B4A4->f24;
    if (a == 1)
        p->f0 |= 0x100000;
    else
        p->f0 &= ~0x100000;
}

void sub_800ABBD8(int a)
{
    G2Inner2* p = dword_8008B4A4->f24;
    if (a)
    {
        p->f0 &= ~0x20000;
        sub_800AB150((G2Obj*)p);
    }
    else
    {
        p->f0 |= 0x20000;
    }
}

void sub_800ABC34(int a)
{
    G2Inner2* p = dword_8008B4A4->f24;
    if (a)
        p->f0 &= ~0x40000;
    else
        p->f0 |= 0x40000;
}

void sub_800ABC78(int a)
{
    G2Inner2* p = dword_8008B4A4->f24;
    if (a)
    {
        p->f0 |= 0x80000;
        p->v60.a = levantPos_8008BD18.a;
        p->v60.b = levantPos_8008BD18.b;
        p->v60.c = levantPos_8008BD18.c;
        p->v54.a = p->v48.a;
        p->v54.b = p->v48.b;
        p->v54.c = p->v48.c;
    }
    else
    {
        p->f0 &= ~0x80000;
    }
}

void sub_800ABCF4(G2Act* p)
{
    if (p->s20 == 0x19)
    {
        p->f2C = sub_8001AC8C(p->f34);
        sub_800148F4(p->f2C);
    }
    else if ((unsigned short)(p->s20 - 7) < 2)
    {
        p->f2C = 0x25;
        sub_800148F4(0x25);
        sub_80013358(p->f34);
        word_8008D782 = sub_80013358(p->f34);
    }
    else if (p->s20 == 0x1A)
    {
        p->f2C = 0x39;
        sub_800148F4(p->f2C);
    }
    else if (p->s20 == 0x1C)
    {
        p->f2C = 0x3A;
        sub_800148F4(p->f2C);
    }
    else if (p->s20 == 0x10)
    {
        p->f2C = sub_800189F8();
        sub_800148F4(p->f2C);
    }
    else if (p->s20 == 0x1D)
    {
        p->f2C = ((int (*)(int))sub_8001CDCC)(p->f34);
        sub_800148F4(p->f2C);
    }
}

void sub_800ABDF0(G2Act* a)
{
    if (a->s1c == 0x1A)
    {
        if (a->f10 == (unsigned short)sub_800AC834(a->s1c, sub_800AC474(0x1A)))
            sub_800AB134((G2Obj*)a);
    }
    if (a->s1c == 0x1D)
    {
        if (a->f10 == (unsigned short)sub_800AB170(0x1D))
            sub_80031494(0x44);
        if (a->f10 == (unsigned short)sub_800AB170(a->s1c) - 10)
            sub_80031160(0x1D, 1);
    }
    if (a->s1c == 0x1C && a->f10 == 2)
        sub_800AB114((G2Obj*)a);
}

void sub_800ABECC()
{
    G2V12* r = &dword_8007A164;
    unsigned int f = dword_8008BD38;
    if (f & 0x200)
    {
        if (f & 1)
            r = &dword_8007A14C;
        else
            r = &dword_8007A0EC;
    }
    else if (f & 0x100)
    {
        if (f & 1)
            r = &dword_8007A140;
        else
            r = &dword_8007A0E0;
    }
    else if (f & 0x80)
    {
        if (f & 1)
            r = &dword_8007A134;
        else
            r = &dword_8007A0D4;
    }
    else if (f & 0x40)
    {
        if (f & 1)
            r = &dword_8007A128;
        else
            r = &dword_8007A0C8;
    }
    else if (f & 0x20)
    {
        if (f & 1)
            r = &dword_8007A11C;
        else
            r = &dword_8007A0BC;
    }
    else if (f & 0x10)
    {
        if (f & 1)
            r = &dword_8007A110;
        else
            r = &dword_8007A0B0;
    }
    else if (f & 8)
    {
        if (f & 1)
            r = &dword_8007A104;
        else
            r = &dword_8007A0A4;
    }
    else if (f & 1)
    {
        r = &dword_8007A0F8;
    }
    sub_800292D0(&dword_8007DC80, &dword_8007DC88, r);
}

INCLUDE_OVERLAY_ASM(game, sub_800AC02C);

void sub_800AC318()
{
    dword_8008B4A4->f24->f0 |= 0x800000;
}

void sub_800AC340(int a)
{
    G2Inner2* p = dword_8008B4A4->f24;
    if (a)
        p->f0 |= 0x1000000;
    else
        p->f0 &= ~0x1000000;
}

void sub_800AC380(int v)
{
    dword_8008BDA0 = v;
}

int sub_800AC38C()
{
    return dword_8007DC60[2];
}

void sub_800AC3A4(short v)
{
    word_8008BDA4 = v;
}

void sub_800AC3B0(int a)
{
    word_8008BDA6 = a;
    sub_800AC380(1);
}

char* sub_800AC3D8()
{
    return &dword_800B1DF8;
}

int sub_800AC3E4()
{
    return word_8008BDA4;
}

int sub_800AC3F4()
{
    G2Sv4* s = (G2Sv4*)&saveData_8008B570;
    int r;
    if (s->f830)
    {
        r = ((int (*)(int))sub_8001D060)(s->b7E5) + dword_800B11B8[s->s834];
    }
    else
    {
        r = dword_800B116C[s->s834];
    }
    return r;
}

int sub_800AC464()
{
    return word_8008BDA6;
}

int sub_800AC474(int a)
{
    return dword_800B11DC[sub_800AC3E4()];
}

int sub_800AC4A8(int a)
{
    G2Rec* p = (G2Rec*)sub_80024E38(dword_8007DC60[2]);
    return p[sub_800AC794(a, dword_800B11DC[sub_800AC3E4()])].f0;
}

int sub_800AC518(int a)
{
    G2Rec* p = (G2Rec*)sub_80024E38(dword_8007DC60[2]);
    int r = sub_800AC794(a, dword_800B11DC[sub_800AC3E4()]);
    if (p[r].f1)
        return 1;
    return sub_80025924(dword_8007DC60[2], (short)sub_800AC988(a, dword_800B11DC[sub_800AC3E4()]));
}

int sub_800AC5D0(int a, int b)
{
    return sub_80025440(dword_8007DC60[2], a, b) != 0;
}

int sub_800AC604(int a, int b)
{
    int t = dword_800B11DC[sub_800AC3E4()];
    return sub_80025440(dword_8007DC60[2], (short)sub_800AC988(a, t), b) != 0;
}

void sub_800AC678(int a)
{
    sub_8002556C(dword_8007DC60[2], a);
}

void sub_800AC6A8(int a)
{
    int t = dword_800B11DC[sub_800AC3E4()];
    sub_8002556C(dword_8007DC60[2], (short)sub_800AC988(a, t));
}

void sub_800AC708(int a, int b)
{
    sub_80025780(dword_8007DC60[2], a, b);
}

void sub_800AC73C()
{
    sub_80025884(dword_8007DC60[2]);
}

void sub_800AC768()
{
    sub_80024DC4(dword_8007DC60[2]);
}

int sub_800AC794(int a, int b)
{
    if ((unsigned)(a - 0xE) >= 0x60)
        return a;
    return a + b * 16;
}

unsigned char* sub_800AC7B4(int a)
{
    return (unsigned char*)sub_80024E38(dword_8007DC60[2]) + ((a << 10) + 0x380);
}

short sub_800AC7F0(int a, int b)
{
    int r = sub_800AC794(a, b);
    return G2REC(a, b)[r].s4;
}

short sub_800AC834(int a, int b)
{
    int r = sub_800AC794(a, b);
    return G2REC(a, b)[r].s6;
}

short sub_800AC878(int a, int b)
{
    int r = sub_800AC794(a, b);
    return G2REC(a, b)[r].s8;
}

unsigned short sub_800AC8BC(int a, int b)
{
    int r = sub_800AC794(a, b);
    return G2REC(a, b)[r].sA;
}

unsigned char sub_800AC900(int a, int b)
{
    int r = sub_800AC794(a, b);
    return G2REC(a, b)[r].f3;
}

short sub_800AC944(int a, int b)
{
    int r = sub_800AC794(a, b);
    return G2REC(a, b)[r].sC;
}

unsigned char sub_800AC988(int a, int b)
{
    int r = sub_800AC794(a, b);
    return G2REC(a, b)[r].f0;
}

short* sub_800AC9CC(int a)
{
    int r = sub_800AC794(a, dword_800B11DC[sub_800AC3E4()]);
    return &((G2Rec*)sub_80024E38(dword_8007DC60[2]))[r].sC;
}

int* sub_800ACA38(int a)
{
    int r = sub_800AC794(a, dword_800B11DC[sub_800AC3E4()]);
    return &((G2Rec*)sub_80024E38(dword_8007DC60[2]))[r].f34;
}

void sub_800ACAA4(int* a, int* b)
{
    G2Sv4* s = (G2Sv4*)&saveData_8008B570;
    b[0] = 0;
    b[1] = 0;
    b[2] = -1;
    b[3] = -1;
    b[4] = -1;
    b[5] = -1;
    b[6] = -1;
    b[7] = -1;
    b[8] = -1;
    b[9] = 0;
    sub_800AC380(s->b7E5 != 0xFF);
    sub_800AC3A4(*(short*)((char*)sub_8001CF84(s->b7E4) + 2));
    sub_8003FF1C(&dword_800B1DD0, 0x2BF20);
    sub_800ACB64(a, b);
    a[2] = (int)sub_800ACB64;
}

INCLUDE_OVERLAY_ASM(game, sub_800ACB64);

void sub_800ACF0C()
{
    sub_80024BB0((int*)&dword_8007DC60);
    sub_8003FF7C(&dword_800B1DD0);
}

void sub_800ACF3C(G2Act* p)
{
    unsigned char* q;
    int i;
    if (p->f14 >= 0)
    {
        q = sub_800AC7B4(dword_800B11DC[p->f14]);
        for (i = 0; i < 16; i++, q += 0x40)
        {
            if (q[1])
                sub_800AC678(q[0]);
        }
    }
}

void sub_800ACFB8()
{
    unsigned char* p = sub_800AC7B4(dword_800B11DC[sub_800AC3E4()]);
    int i;
    for (i = 0; i < 16; i++, p += 0x40)
    {
        if (p[1])
            sub_800AC5D0(p[0], 1);
    }
}

int sub_800AD02C()
{
    int v = *(int*)playerYan_8008B594;
    if (v > 9999999)
        v = 9999999;
    return v;
}

int sub_800AD058(int a)
{
    G2Save* s = (G2Save*)&saveData_8008B570;
    int v;
    if (s->f24 <= 9999998)
    {
        v = s->f24 + a;
        if (v <= 9999998)
            s->f24 = v;
        else
            s->f24 = 9999999;
        return 1;
    }
    return 0;
}

int sub_800AD0A4(int a)
{
    G2Save* s = (G2Save*)&saveData_8008B570;
    if (s->f24 >= a)
    {
        s->f24 -= a;
        return 1;
    }
    return 0;
}

int sub_800AD0D4(unsigned a)
{
    return (playerYan_8008B594[0x290 + (a >> 3)] >> (a & 7)) & 1;
}

void sub_800AD0F8(unsigned a)
{
    ((G2Bits*)playerYan_8008B594)->b[a >> 3] |= 1 << (a & 7);
}

void sub_800AD124(unsigned a)
{
    ((G2Bits*)playerYan_8008B594)->b[a >> 3] &= ~(1 << (a & 7));
}

int sub_800AD154(int a)
{
    return playerYan_8008B594[a + 0x2A3];
}

int sub_800AD16C(int a, int b)
{
    ((G2Bits3*)playerYan_8008B594)->c[a] = b;
    return b;
}

int sub_800AD184(int a, int b, int c)
{
    unsigned char* r = sub_800AD4D8(a, b, c);
    if (r && a != 0xFF)
    {
        r[0] = a;
        r[1] += b;
        return 1;
    }
    return 0;
}

int sub_800AD1E0(int a, int b, int c)
{
    unsigned char* r = sub_800AD58C(a, c);
    if (r)
    {
        if (sub_800AD67C(r[1], b))
        {
            r[1] -= b;
            if (r[1] == 0)
                r[0] = 0xFF;
            return 1;
        }
    }
    return 0;
}

int sub_800AD254()
{
    unsigned char* r = sub_800AD58C();
    if (r)
        return r[1];
    return 0;
}

int sub_800AD288(int a, int b)
{
    unsigned char* p = sub_800AD604(b);
    if (p)
        return p[a * 2];
    return 0xFF;
}

int sub_800AD2C8(int a, int b)
{
    unsigned char* p = sub_800AD604(b);
    if (p)
        return p[a * 2 + 1];
    return 0;
}

int sub_800AD308(int a)
{
    unsigned char* p = sub_800AD604(a);
    int n = sub_800AD374(a);
    int i;
    if (p)
    {
        for (i = n - 1; i > 0; i--)
        {
            if (p[i * 2] != 0xFF)
                return i;
        }
    }
    return 0;
}

int sub_800AD374(int a)
{
    int r;
    unsigned u = a;
    r = 0;
    if (u < 4)
        goto L;
    if (u == 4)
    {
    L:
        r = 0x40;
    }
    return r;
}

int sub_800AD398()
{
    int x;
    if (sub_800AD308(4) > 0)
        return 1;
    if (sub_800AD288(0, 4) != 0xFF)
    {
        x = sub_800AD2C8(0, 4);
        if (x)
            return 1;
    }
    return 0;
}

void sub_800AD3F0(int a)
{
    unsigned char tmp[2];
    int n = sub_800AD374(a);
    unsigned char* tbl = sub_800AD604(a);
    short cnt = 0;
    short i;
    unsigned char* r;
    for (i = 0; i < n; i++)
    {
        r = sub_800AD58C(i, a);
        if (r)
        {
            sub_800403E8((unsigned*)tmp, (unsigned*)(tbl + cnt * 2), 2);
            sub_800403E8((unsigned*)(tbl + cnt * 2), (unsigned*)r, 2);
            sub_800403E8((unsigned*)r, (unsigned*)tmp, 2);
            cnt++;
        }
    }
}

unsigned char* sub_800AD4D8(int a, int b, int c)
{
    unsigned char* r = sub_800AD58C(a, c);
    if (r)
    {
        if (sub_800AD670(r[1], b))
        {
            if ((unsigned)(c - 1) < 3 && a == sub_800AD990(c - 1))
            {
                if (!(r[1] + b < 0x14))
                    return 0;
            }
            return r;
        }
        return 0;
    }
    return sub_800AD58C(0xFF, c);
}

#if 0
unsigned char* sub_800AD58C(int a, int b)
{
    int n = sub_800AD374(b);
    unsigned char* p = sub_800AD604(b);
    unsigned char* q = 0;
    int i;
    if (p && n > 0)
    {
        i = 0;
        do
        {
            if (a == p[0])
                return p;
            i++;
            p += 2;
        } while (i < n);
    }
    return q;
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800AD58C);

unsigned char* sub_800AD604(int n)
{
    switch ((unsigned)n)
    {
    case 0:
        return (unsigned char*)&saveData_8008B570 + 0x28;
    case 1:
        return (unsigned char*)&saveData_8008B570 + 0xA8;
    case 2:
        return (unsigned char*)&saveData_8008B570 + 0x128;
    case 3:
        return (unsigned char*)&saveData_8008B570 + 0x1A8;
    case 4:
        return (unsigned char*)&saveData_8008B570 + 0x228;
    }
    return 0;
}
INCLUDE_OVERLAY_ASM(game, dword_800A094C);

int sub_800AD670(int a, int b)
{
    return a + b < 0x15;
}

int sub_800AD67C(int a, int b)
{
    return (a - b) >= 0;
}

int sub_800AD68C(int n)
{
    G2Flags* f = (G2Flags*)playerYan_8008B594;
    if (n < 0x40)
    {
        f->w[n / 32] |= 1 << (n % 32);
        return 1;
    }
    return 0;
}

void sub_800AD6E4(int n)
{
    G2Flags* f = (G2Flags*)playerYan_8008B594;
    if (n < 0x40)
        f->w[n / 32] &= ~(1 << (n % 32));
}

int sub_800AD73C(int n)
{
    G2Flags* f = (G2Flags*)playerYan_8008B594;
    if (n < 0x40)
    {
        if (f->w[n / 32] & (1 << (n % 32)))
            return 1;
    }
    return 0;
}

int sub_800AD79C()
{
    short i;
    int c = 0;
    for (i = 0; i < 0x26; i++)
    {
        if (sub_800AD73C(i))
            c++;
    }
    return c;
}

int sub_800AD7F8(int a)
{
    short i;
    int c = 0;
    for (i = 0; i < 0x26; i++)
    {
        if (sub_800AD73C(i))
        {
            if (a == (short)c++)
                return i;
        }
    }
    return 0x26;
}

int sub_800AD888()
{
    int v = 12 - sub_800AD8BC();
    if (v < 0)
        v = 0;
    return v;
}

int sub_800AD8BC()
{
    return dword_8008B818 + sub_80010548(0);
}

int sub_800AD8E4()
{
    return dword_8008B818;
}

int sub_800AD8F4(int a)
{
    int ret = 1;
    int v = sub_800AD8E4() + a;
    if (v >= 13)
    {
        v = 12;
        ret = 0;
    }
    dword_8008B818 = v;
    return ret;
}

int sub_800AD944(int a)
{
    int ret = 1;
    int v = sub_800AD8E4() - a;
    if (v < 0)
    {
        v = 0;
        ret = v;
    }
    dword_8008B818 = v;
    return ret;
}

unsigned int sub_800AD990(int a)
{
    unsigned int r = 0;
    switch ((unsigned)a)
    {
    case 0:
        r = equippedWeaponId_8008BD54;
        break;
    case 1:
        r = equippedArmor_8008BD55;
        break;
    case 2:
        r = byte_8008BD56;
        break;
    }
    return r;
}

#if 0
int sub_800AD9EC(int a, int b)
{
    unsigned char old = sub_800AD990(b);
    G2Sv4* s;
    switch ((unsigned)b)
    {
    case 0:
        if (old == 0xFF)
        {
            if (a == 0xFF)
                return 1;
        }
        else if (a == 0xFF)
        {
            return 0;
        }
        s = (G2Sv4*)&saveData_8008B570;
        s->b7E4 = a;
        sub_800AD1E0(a, 1, 1);
        if (old < 0x17)
            sub_800AD184(old, 1, 1);
        sub_800AC3A4(*(short*)((char*)sub_8001CF84(a) + 2));
        sub_8001D034(s->b7E5);
        sub_800AC3B0(dword_8001D060(s->b7E5));
        return 1;
    case 1:
        if (old == 0xFF)
        {
            if (a == 0xFF)
                return 1;
        }
        else if (a == 0xFF)
        {
            return 0;
        }
        s = (G2Sv4*)&saveData_8008B570;
        s->b7E5 = a;
        sub_800AD1E0(a, 1, 2);
        if (old < 0xF)
            sub_800AD184(old, 1, 2);
        sub_800AC3A4(*(short*)((char*)sub_8001CF84(s->b7E4) + 2));
        sub_8001D034(a);
        sub_800AC3B0(dword_8001D060(a));
        return 1;
    case 2:
        byte_8008BD56 = a;
        sub_800AD1E0(a, 1, 3);
        if (old != 0xFF)
            sub_800AD184(old, 1, 3);
        return 1;
    }
    return 1;
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800AD9EC);

#if 0
int sub_800ADBA0(short* p)
{
    int n = ((G2Save2*)&saveData_8008B570)->n;
    char* q = (char*)&saveData_8008B570;
    int i;
    for (i = 0; i < n; i++, q += 8)
    {
        if (((G2E*)q)->a == p[0] && ((G2E*)q)->b == p[1] && ((G2E*)q)->c == p[2])
            return i;
    }
    return -1;
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800ADBA0);

int sub_800ADC1C(short* p)
{
    int r = sub_800ADBA0(p);
    if (r != -1)
        r = ((G2Sv*)((char*)&saveData_8008B570 + r * 8))->s;
    return r;
}

void sub_800ADC5C(unsigned short* p, int b)
{
    int i;
    if (b != -2)
    {
        i = sub_800ADBA0((short*)p);
        if (i == -1)
            i = ((G2Save2*)&saveData_8008B570)->n++;
#define G2EN ((G2E*)((char*)&saveData_8008B570 + i * 8))
        G2EN->a = p[0];
        G2EN->b = p[1];
        G2EN->c = p[2];
        G2EN->d = b;
    }
}

#if 0
void sub_800ADCEC(short* out, int key)
{
    int i, j, k;
    G2Ent16** row;
    G2Ent16* e;
    for (i = 0; name_800B0608[i]; i++)
    {
        row = name_800B0608[i];
        for (j = 0; row[j]; j++)
        {
            e = row[j];
            k = 0;
            if (e->id != -1)
            {
                do
                {
                    if (key == e[k].s6)
                    {
                        out[0] = i;
                        out[1] = j;
                        out[2] = k;
                        out[3] = e[k].u4;
                        return;
                    }
                    k++;
                } while (e[k].id != -1);
            }
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800ADCEC);

INCLUDE_OVERLAY_ASM(game, sub_800ADDAC);

INCLUDE_OVERLAY_ASM(game, dword_800ADE78);
