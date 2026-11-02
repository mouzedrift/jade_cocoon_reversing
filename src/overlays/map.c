// MAP.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct MapTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} MapTask;

typedef struct MapElem
{
    char pad_0[0x18];
    int f18;
} MapElem;

typedef struct MapRow
{
    int f0;
    int f4;
    int f8;
    int fc;
    int f10;
    MapElem* f14;
} MapRow;

typedef struct MapPos
{
    short a;
    short b;
} MapPos;

typedef struct MapQuery
{
    short a;
    short b;
    short c;
} MapQuery;

extern unsigned char* dword_800B9348[];
extern unsigned char dword_800B9360[];
extern short word_800B8C98[];
extern int sub_800AD0D4(int);
extern int sub_800ADC1C(MapQuery*);
extern int sub_800B8290(MapPos*);
typedef struct MapSaveView
{
    char pad_0[0x2E4];
    short f2E4;
    short pad_2E6;
    short f2E8;
    short pad_2EA;
    short f2EC;
    short f2EE;
} MapSaveView;

extern int sub_8003DA54(void*);
extern void sub_800A8DEC();
extern void sub_800A6D30(int);
extern void sub_800AD16C(int, int);
extern int dword_80091C94;
typedef struct MapRec12
{
    int a;
    int b;
    int c;
} MapRec12;

extern MapRec12 dword_800AEBFC[];
extern int dword_800B9430;
extern int dword_800B9314;
extern int dword_800B9318;
extern int dword_800B931C;
extern int dword_800B9320;
extern int dword_800B9434;
extern int dword_800B9438;
extern int dword_800B9420[4];
extern int dword_800B9400[];
extern MapRow dword_800B9220[];
extern unsigned short word_800AEBF8[2];
extern unsigned short dword_800B8C94[2];
extern void sub_800B8448(void*);
extern short word_800B932C;
extern void sub_8001C19C(int, int);
extern void sub_8001CD04(int);
extern void sub_8003BC84(void*);
extern void sub_800B6CB4();
extern void sub_800B6C7C();
extern void sub_800B6DE0(MapTask*, int);
extern void sub_800B6E80();
extern void sub_800B6EE8();
extern void sub_800B6FAC(MapTask*);
extern void sub_800B7044();
extern void sub_800B7980();
extern void sub_800B7A90();
extern void sub_800B7A38();
extern void sub_800B860C();
extern void sub_800B8B5C();

INCLUDE_OVERLAY_ASM(map, dword_800B66C0);

// Matched
void sub_800B6BFC(MapTask* t, int a1)
{
    void (*f)();
    dword_800B8C94[0] = word_800AEBF8[0];
    dword_800B8C94[1] = word_800AEBF8[1];
    sub_800B8448(word_800AEBF8);
    f = sub_800B6C7C;
    t->next_8 = f;
    f(t, a1);
    t->flags_0 = (t->flags_0 | 4) & 0xFFFF7FFF;
}

// Matched
void sub_800B6C7C(MapTask* t)
{
    sub_8001C19C(0, 0x20);
    t->next_8 = sub_800B6CB4;
}

INCLUDE_OVERLAY_ASM(map, sub_800B6CB4);

// Matched
void sub_800B6D90(int* p, int a1)
{
    dword_800B9430 = 0;
    p[0] = 0x2C;
    p[1] = a1;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = 0;
    p[6] = 0;
    p[7] = (int)sub_800B6DE0;
    sub_8003BC84(p);
}

// Matched
void sub_800B6DE0(MapTask* t, int a1)
{
    sub_800B6FAC(t);
    if (dword_800B9434 == 1)
    {
        sub_80028E74(&dword_800B931C, 0, &dword_800B9320, a1, 1);
    }
    else
    {
        sub_80028E74(&dword_800B9314, 0, &dword_800B9318, a1, 1);
    }
    dword_800B9430 = 1;
}

// Matched
void sub_800B6E5C(MapTask* t)
{
    if (dword_800B9430)
    {
        t->next_8 = sub_800B6E80;
    }
}

// Matched
void sub_800B6E80(MapTask* t)
{
    dword_800B9434 = 1;
    sub_800B6D90(dword_800B9400, dword_800B9220[(short)word_800AEBF8[0]].f4);
    t->next_8 = sub_800B6EE8;
}

// Matched
void sub_800B6EE8(MapTask* t, int a1)
{
    if (dword_800B9430 && sub_8001C2FC())
    {
        t->next_8 = sub_800B7044;
        sub_8001CD04(0);
        t->next_8(t, a1);
        sub_8001C19C(3, 0x20);
    }
}

// Matched
void sub_800B6F60(MapTask* t)
{
    sub_800B6FAC(t);
    t->flags_0 &= ~4;
    unknownFlags_8008D678 &= 0xFBFFFFFF;
}

// Matched
void sub_800B6FAC(MapTask* t)
{
    if (dword_800B9314)
    {
        free3_8003FC6C((void*)dword_800B9314);
        dword_800B9314 = 0;
    }
    if (dword_800B9318)
    {
        free3_8003FC6C((void*)dword_800B9318);
        dword_800B9318 = 0;
    }
    if (dword_800B931C)
    {
        free3_8003FC6C((void*)dword_800B931C);
        dword_800B931C = 0;
    }
    if (dword_800B9320)
    {
        free3_8003FC6C((void*)dword_800B9320);
        dword_800B9320 = 0;
    }
}

INCLUDE_OVERLAY_ASM(map, sub_800B7044);

// Matched
void sub_800B7948(MapTask* t)
{
    sub_8001C19C(0, 0x20);
    t->next_8 = sub_800B7980;
}

#if 0
// Not matched: register allocation of the table base (v0/v1 swapped)
void sub_800B7980(MapTask* t)
{
    MapPos q;
    MapElem* e;
    short* w = (short*)word_800AEBF8;
    int r = sub_8003DA54(&dword_800AEBFC[w[0]]);
    sub_800B8128((short)r, w[0], &q);
    dword_800B9434 = 0;
    sub_800B6D90(dword_800B9400, dword_800B9220[(short)word_800AEBF8[0]].f14[q.b].f18);
    t->next_8 = sub_800B7A38;
}
#endif
INCLUDE_OVERLAY_ASM(map, sub_800B7980);

// Matched
void sub_800B7A38(MapTask* t)
{
    if (dword_800B9430 && sub_8001C2FC())
    {
        t->next_8 = sub_800B7A90;
        sub_8001C19C(3, 0x20);
        word_800B932C = 0;
    }
}

INCLUDE_OVERLAY_ASM(map, sub_800B7A90);

// Matched
int sub_800B7E54(short a)
{
    int i;
    int cnt = 0;
    MapPos pos;
    pos.a = a;
    for (i = 0; i < word_800B8C98[a]; i++)
    {
        pos.b = i;
        if (sub_800B8290(&pos))
        {
            cnt++;
        }
    }
    return cnt;
}

INCLUDE_OVERLAY_ASM(map, sub_800B7EE0);

// Matched
void sub_800B8128(short a, short b, MapPos* out)
{
    int cnt = 0;
    int i;
    out->a = b;
    for (i = 0; i < word_800B8C98[b]; i++)
    {
        out->b = i;
        if (sub_800B8290(out))
        {
            if (cnt++ == a)
            {
                break;
            }
        }
    }
}

#if 0
// Not matched: s0/s1 swapped for i and cnt
short sub_800B81D0(MapPos* p)
{
    int i;
    int cnt = 0;
    MapPos q;
    q.a = p->a;
    for (i = 0; i < word_800B8C98[p->a]; i++)
    {
        q.b = i;
        if (sub_800B8290(&q))
        {
            cnt++;
            if (q.b == p->b)
            {
                break;
            }
        }
    }
    return cnt;
}
#endif
INCLUDE_OVERLAY_ASM(map, sub_800B81D0);

// Matched
int sub_800B8290(MapPos* p)
{
    int idx = p->a;
    unsigned char c = dword_800B9348[idx][p->b];
    MapQuery q;
    int r;
    if (c == 0xFF)
    {
        return sub_800AD0D4(1) != 0;
    }
    if (c == 0xFE)
    {
        return 1;
    }
    if (c >= 0xF0)
    {
        c += 0x11;
    }
    q.a = dword_800B9360[idx];
    q.b = c;
    q.c = 0;
    r = sub_800ADC1C(&q);
    return r != -1;
}

#if 0
// Not matched: block layout (the original tests 0xFE/0xFF first and has p in a2)
void sub_800B8338(MapPos* p)
{
    unsigned char c = dword_800B9348[p->a][p->b];
    MapSaveView* v;
    if (c >= 0xF0)
    {
        if (c != 0xFE && c != 0xFF)
        {
            sub_800AD16C(4, c - 0xEF);
        }
        v = (MapSaveView*)&saveData_8008B570;
        v->f2E4 = 4;
        v->f2E8 = 0;
        v->f2EC = 0;
        v->f2EE = -1;
    }
    else
    {
        v = (MapSaveView*)&saveData_8008B570;
        v->f2E4 = dword_800B9360[p->a];
        v->f2E8 = dword_800B9348[p->a][p->b];
        v->f2EC = 0;
        v->f2EE = -1;
    }
    sub_800A8DEC();
    sub_8001C19C(0, 0x20);
    sub_800A6D30(1);
    dword_80091C94 = 1;
    dword_8008B540 = 1;
}
#endif
INCLUDE_OVERLAY_ASM(map, sub_800B8338);

INCLUDE_OVERLAY_ASM(map, sub_800B8448);

// Matched
void sub_800B85CC(MapTask* t)
{
    int* p;
    void (*f)() = sub_800B860C;
    dword_800B9420[0] = 0;
    p = dword_800B9420;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    t->next_8 = f;
    f();
}

INCLUDE_OVERLAY_ASM(map, sub_800B860C);

// Matched
void sub_800B8B2C(MapTask* t)
{
    void (*f)() = sub_800B8B5C;
    dword_800B9438 = 0;
    t->next_8 = f;
    f();
}

INCLUDE_OVERLAY_ASM(map, sub_800B8B5C);

INCLUDE_OVERLAY_ASM(map, dword_800B8C94);
