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
extern void sub_800AD0F8(int a);
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
extern void sub_800AD16C(int a, int b);
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

INCLUDE_OVERLAY_ASM(game, sub_800A1314);

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

#if 0
// Not matched
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
            sub_80020D68();
        }
        t->next_8 = sub_800A15FC;
    }
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800A1578);

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

#if 0
// Not matched
int sub_800A2CA8(int a, int b)
{
    int ok = 0;
    if (a >= 0 && a < gCtx_800B1260.f40 && gCtx_800B1260.f4c[a] != 0)
    {
        ok = 1;
    }
    if (!ok)
    {
        if (!b)
        {
            printf(aAssertionFaile_800A05A4, aFile_800A05CC, 0x512);
            exit(1);
        }
    }
    return ok;
}
#endif
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

INCLUDE_OVERLAY_ASM(game, sub_800A54A0);

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

INCLUDE_OVERLAY_ASM(game, sub_800A58B4);

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

INCLUDE_OVERLAY_ASM(game, sub_800A6060);

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

#if 0
// Not matched
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
            GameTabEnt_1* e = t->e;
            return e[a].v;
        }
        return 0;
    }
    return a;
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800A6738);

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

INCLUDE_OVERLAY_ASM(game, sub_800A6C00);

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

#if 0
// Not matched
int sub_800A6D50(int a)
{
    int* p = (int*)dword_8008D46C[9];
    int r = 0;
    if (a == 1)
    {
        r = p[1];
        return r;
    }
    if (a == 0)
    {
        r = p[0];
        return r;
    }
    if (a == 2)
    {
        r = p[2];
        return r;
    }
    return r;
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800A6D50);

INCLUDE_OVERLAY_ASM(game, sub_800A6DAC);

INCLUDE_OVERLAY_ASM(game, sub_800A70F8);

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

#if 0
// Not matched
void sub_800A73A8(void)
{
    GameRect_1* r = &stru_8008D420;
    dword_8008D40C = 0x1000;
    r->x = 0;
    dword_8008D404 = 0;
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
#endif
INCLUDE_OVERLAY_ASM(game, sub_800A73A8);

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

INCLUDE_OVERLAY_ASM(game, sub_800A7574);

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
