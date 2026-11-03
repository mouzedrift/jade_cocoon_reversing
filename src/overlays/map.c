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
#define MAPV ((MapSaveView*)&saveData_8008B570)
typedef struct MapEntry
{
    short id;
    char pad_2[14];
} MapEntry;

extern MapEntry** dword_800B0608[];
extern int dword_800B0624[];
extern char dword_800B6B98[];
extern char dword_800B6BAC[];
extern char dword_800B6BCC[];
extern char* dword_800B9370[];
extern char** dword_800B93E0[];
extern unsigned char dword_800B93F8[];
extern int dword_80091C54;
extern void sub_8003D034(void*, int);
#define SEL dword_800AEBFC[(short)word_800AEBF8[0]]
typedef struct MapSaveView
{
    char pad_0[0x2DC];
    short f2DC;
    short f2DE;
    short f2E0;
    short f2E2;
    short f2E4;
    short f2E6;
    short f2E8;
    short f2EA;
    short f2EC;
    short f2EE;
} MapSaveView;

extern int sub_8003DA54(void*);
extern void sub_800A8DEC();
extern void sub_800A6D30(int);
extern void sub_800AD16C(int, int);
extern int dword_80091C94;
typedef struct MapSel
{
    short s0;
    short s2;
    short s4;
    short s6;
    short s8;
    short sA;
} MapSel;

extern MapSel dword_800AEBFC[];
extern unsigned short padRepeat_800918CC;
extern char dword_800B6BE0[];
extern void sub_8003E91C(int, void*, void*, int);
extern void sub_8003EF74(void*, int, int);
extern int dword_800B9438;
extern unsigned char dword_800B9368[];
extern int dword_800B8CA4;
extern int sub_800AD154(int);
extern void sub_800300E0(int, int);
extern void sub_800B6E5C();
extern int sub_800B81D0(MapPos*);
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
extern void sub_800B8448();
extern short word_800B932C;
extern void sub_8001C19C(int, int);
extern void ResetPadHoldFrames_8001CD04(int);
extern void QueueFileRequest_8003BC84(void*);
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

// Matched
void sub_800B6CB4(MapTask* t)
{
    int a;
    dword_800B8CA4 = sub_800B7E54((short)word_800AEBF8[0]);
    sub_800B7EE0();
    if (sub_800AD154(0xC) == 1)
    {
        a = 0xF;
    }
    else if (sub_800AD154(0xC) == 2)
    {
        a = 0x91;
    }
    else
    {
        a = dword_800B9220[(short)word_800AEBF8[0]].f10;
    }
    sub_800300E0(a, 1);
    dword_800B9434 = 0;
    sub_800B6D90(dword_800B9400, dword_800B9220[(short)word_800AEBF8[0]].f0);
    t->next_8 = sub_800B6E5C;
}

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
    QueueFileRequest_8003BC84(p);
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
    if (dword_800B9430 && IsFadeDone_8001C2FC())
    {
        t->next_8 = sub_800B7044;
        ResetPadHoldFrames_8001CD04(0);
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

// Not matched: register allocation of the table base (v0/v1 swapped)
void sub_800B7980(MapTask* t)
{
    MapPos q;
    MapElem* e;
    short* w = (short*)word_800AEBF8;
    int r = sub_8003DA54(&dword_800AEBFC[w[0]]);
    sub_800B8128((short)r, w[0], &q);
    dword_800B9434 = 0;
    e = dword_800B9220[(short)word_800AEBF8[0]].f14 + q.b;
    sub_800B6D90(dword_800B9400, e->f18);
    t->next_8 = sub_800B7A38;
}

// Matched
void sub_800B7A38(MapTask* t)
{
    if (dword_800B9430 && IsFadeDone_8001C2FC())
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

// Matched
void sub_800B7EE0()
{
    MapPos q;
    int r;
    int n;
    int k;
    if (dword_800B8CA4 < 4)
    {
        SEL.s2 = dword_800B8CA4;
        SEL.s6 = 0;
    }
    else
    {
        SEL.s2 = 3;
        SEL.s6 = 0x40;
    }
    SEL.s4 = dword_800B8CA4;
    if ((short)word_800AEBF8[0] != (short)dword_800B8C94[0] || (short)word_800AEBF8[1] != (short)dword_800B8C94[1])
    {
        SEL.s8 = 0;
        SEL.sA = 0;
    }
    else
    {
        r = sub_8003DA54(&SEL);
        sub_800B8128((short)r, (short)word_800AEBF8[0], &q);
        if (!sub_800B8290(&q))
        {
            SEL.s8 = 0;
            SEL.sA = 0;
        }
        else
        {
            n = sub_800B81D0((MapPos*)word_800AEBF8);
            if (dword_800B8CA4 < 4)
            {
                SEL.s8 = n;
                SEL.sA = 0;
            }
            else
            {
                k = (unsigned short)dword_800B8CA4 - 3;
                if ((short)k < SEL.sA)
                {
                    SEL.s8 = n - k;
                    SEL.sA = k;
                }
            }
        }
    }
}

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

// Matched
void sub_800B8448(MapPos* out)
{
    unsigned short t = MAPV->f2E4;
    MapQuery q;
    unsigned char* tbl;
    unsigned char cnt;
    if ((unsigned short)(t - 4) < 2)
    {
        if (MAPV->f2E8 == 0)
        {
            int f = MAPV->f2E0;
            out->b = 12;
            out->a = f == 1;
            return;
        }
        q.a = t;
        q.c = 0;
        q.b = 1;
        do
        {
            if (sub_800ADC1C(&q) == -1)
            {
                break;
            }
            q.b++;
        } while (q.b < 5);
        if (q.b == 5)
        {
            q.b--;
        }
        out->a = q.b + 1;
    }
    else if ((unsigned short)(t - 1) >= 3)
    {
        int f = MAPV->f2E0;
        out->b = 0;
        out->a = f == 1;
        return;
    }
    else
    {
        out->a = MAPV->f2E0 == 1;
    }
    tbl = dword_800B9348[out->a];
    cnt = dword_800B9368[out->a];
    for (out->b = 0; out->b < cnt; out->b++)
    {
        if (MAPV->f2E8 == tbl[out->b])
        {
            return;
        }
    }
    out->b = 0;
}

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

#if 0
// Not matched: scheduling of the loads in the last case (about 20 words differ)
void sub_800B860C()
{
    int* m = dword_800B9420;
    int a = m[1];
    int b = m[2];
    MapEntry* list = dword_800B0608[a][b];
    RECT r1;
    RECT r2;
    RECT r3;
    int y;
    int i;
    int n;
    int d;
    char* str;
    int v;
    int c;
    switch (m[0])
    {
    case 0:
        if (padRepeat_800918CC & 0x1000)
        {
            m[1] = a - 1;
        }
        else if (padRepeat_800918CC & 0x4000)
        {
            m[1] = a + 1;
        }
        m[1] = m[1] < 0 ? 0 : m[1] < 6 ? m[1] : 5;
        if (sub_8003D380(1) == 1)
        {
            m[0]++;
        }
        r1.x = 0x1E;
        r1.y = 0x14;
        sub_8003E91C(2, dword_800B6B98, &r1, 0);
        for (i = 0; i < 6; i++)
        {
            str = dword_800B9370[i];
            d = i == m[1] ? (frameCount_8008D3FC & 0xF) : 0;
            r2.x = 0x1E + d;
            r2.y = 0x32 + i * 14;
            sub_8003E91C(2, str, &r2, 0);
        }
        if (frameCount_8008D3FC & 3)
        {
            r2.x = 0x1E;
            r2.y = m[1] * 14 + 0x32;
            sub_8003D034(&r2, 0);
        }
        break;
    case 1:
        if (padRepeat_800918CC & 0x1000)
        {
            m[2] = b - 1;
        }
        else if (padRepeat_800918CC & 0x4000)
        {
            m[2] = b + 1;
        }
        m[2] = m[2] < 0 ? 0 : (dword_800B0624[m[1]] - 1 < m[2] ? dword_800B0624[m[1]] - 1 : m[2]);
        if (sub_8003D380(1) == 1)
        {
            m[0]++;
        }
        else if (sub_8003D41C(1) == 1)
        {
            m[2] = 0;
            m[0]--;
        }
        r2.x = 0x1E;
        r2.y = 0x14;
        sub_8003E91C(2, dword_800B6BAC, &r2, 0);
        for (i = 0; i < dword_800B0624[m[1]]; i++)
        {
            str = dword_800B93E0[m[1]][i];
            d = i == m[2] ? (frameCount_8008D3FC & 0xF) : 0;
            r3.x = 0x1E + d;
            r3.y = 0x32 + i * 14;
            sub_8003E91C(2, str, &r3, 0);
        }
        if (frameCount_8008D3FC & 3)
        {
            r3.x = 0x1E;
            r3.y = m[2] * 14 + 0x32;
            sub_8003D034(&r3, 0);
        }
        break;
    case 2:
        if (padRepeat_800918CC & 0x1000)
        {
            m[3]--;
        }
        else if (padRepeat_800918CC & 0x4000)
        {
            m[3]++;
        }
        n = 0;
        if (list->id != -1)
        {
            MapEntry* p = list;
            do
            {
                p++;
                n++;
            } while (p->id != -1);
        }
        m[3] = m[3] < 0 ? 0 : (n - 1 < m[3] ? n - 1 : m[3]);
        if (sub_8003D380(1) == 1)
        {
            MapSaveView* sv = (MapSaveView*)&saveData_8008B570;
            short fl = dword_800B93F8[m[1]];
            sv->f2EC = m[3];
            sv->f2E4 = m[1];
            sv->f2E2 = -1;
            sv->f2E6 = -1;
            sv->f2EA = -1;
            sv->f2EE = -1;
            dword_80091C94 = 1;
            sv->f2E8 = m[2];
            dword_80091C54 = 0;
            sv->f2E0 = fl;
            sub_800A8DEC();
            sub_800A6D30(1);
            sub_8001C19C(0, 0x20);
            dword_8008B540 = 1;
        }
        else
        {
            if (sub_8003D41C(1) == 1)
            {
                m[3] = 0;
                m[0]--;
            }
            r3.x = 0x1E;
            r3.y = 0x14;
            sub_8003E91C(2, dword_800B6BCC, &r3, 0);
        }
        break;
    }
}
#endif
INCLUDE_OVERLAY_ASM(map, sub_800B860C);


// Matched
void sub_800B8B2C(MapTask* t)
{
    void (*f)() = sub_800B8B5C;
    dword_800B9438 = 0;
    t->next_8 = f;
    f();
}

#if 0
// Not matched: the original loads the constant 0x78 twice (no CSE between a.y and b.x)
void sub_800B8B5C()
{
    int* sel = &dword_800B9438;
    unsigned short pad = padRepeat_800918CC;
    RECT a;
    RECT b;
    RECT c;
    int r;
    if (pad & 0x1000)
    {
        dword_800B9438--;
    }
    else if (pad & 0x4000)
    {
        dword_800B9438++;
    }
    *sel = *sel < 0 ? 0 : *sel < 7 ? *sel : 6;
    r = sub_8003D380(1);
    if (r == 1)
    {
        MapSaveView* sv = (MapSaveView*)&saveData_8008B570;
        sv->f2DE = -5;
        sv->f2DC = *sel;
        sub_800A6D30(0);
        dword_8008B540 = r;
    }
    sub_8003D41C(1);
    a.x = 0x6E;
    a.y = 0x78;
    b.x = 0x78;
    b.y = 0x82;
    sub_8003E91C(2, dword_800B6BE0, &b, 0);
    c.x = a.x + 0x50;
    c.y = a.y + 0xA;
    sub_8003EF74(&c, *sel + 1, 0);
}
#endif
INCLUDE_OVERLAY_ASM(map, sub_800B8B5C);

INCLUDE_OVERLAY_ASM(map, dword_800B8C94);
