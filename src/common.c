#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "STDLIB.H"
#include "STDIO.H"
#include "LIBPAD.H"
#include "LIBSND.H"
#include "LIBMCX.H"
#include "LIBPRESS.H"
#include "LIBETC.H"
#include "LIBMCRD.H"
#include "sound.h"
#include "data_decls.h"
#include "unit.h"
#include "common_tu.h"

const struct_u8x12 dword_80071F58 = { { 0, 0, 100, 0, 255, 115, 0, 0, 10, 0, 3, 0 } };
const char aAssertionFaile_2[] = "Assertion failed: file \"%s\", line %d\n";
const char aCommonC[] = "COMMON.C";
int dword_80079320[10] = {
    1, 0, 1, 0, 5, 7, 11, 13,
    9, 15,
};
unsigned short dword_80079348[0x15] = {
    0x11D, 0x140, 0x163, 0x186, 0x1A9, 0x1CC, 0x1EF, 0x212,
    0x235, 0x258, 0x27B, 0x29E, 0x2C1, 0x2E4, 0x307, 0x32A,
    0x34D, 0x370, 0x393, 0x3B6, 0x3E7,
};
unsigned short word_80079374[40] = {
    190, 19, 180, 18, 170, 17, 160, 16,
    150, 15, 140, 14, 130, 13, 120, 12,
    110, 11, 100, 10, 90, 9, 80, 8,
    70, 7, 60, 6, 50, 5, 40, 4,
    30, 3, 20, 2, 10, 1,
};
unsigned char byte_800793C4[4] = { 2, 3, 5, 10 };
unsigned char dword_800793C8[118][4] = {
    { 0, 0, 4, 16 },
    { 5, 8, 12, 16 },
    { 8, 10, 14, 16 },
    { 14, 16, 16, 16 },
    { 15, 16, 16, 16 },
    { 0, 31, 7, 128 },
    { 240, 30, 7, 128 },
    { 208, 30, 7, 128 },
    { 192, 30, 7, 128 },
    { 172, 30, 7, 128 },
    { 156, 30, 7, 128 },
    { 128, 30, 7, 128 },
    { 104, 30, 7, 128 },
    { 88, 30, 7, 128 },
    { 68, 30, 7, 128 },
    { 44, 30, 7, 128 },
    { 28, 30, 7, 128 },
    { 8, 30, 7, 128 },
    { 244, 29, 7, 128 },
    { 224, 29, 7, 128 },
    { 200, 29, 7, 128 },
    { 172, 29, 7, 128 },
    { 144, 29, 7, 128 },
    { 120, 29, 7, 128 },
    { 92, 29, 7, 128 },
    { 64, 29, 7, 128 },
    { 36, 29, 7, 128 },
    { 8, 29, 7, 128 },
    { 236, 28, 7, 128 },
    { 212, 28, 7, 128 },
    { 192, 28, 7, 128 },
    { 160, 28, 7, 128 },
    { 140, 28, 7, 128 },
    { 116, 28, 7, 128 },
    { 92, 28, 7, 128 },
    { 72, 28, 7, 128 },
    { 48, 28, 7, 128 },
    { 28, 28, 7, 128 },
    { 8, 28, 7, 128 },
    { 236, 27, 7, 128 },
    { 216, 27, 7, 128 },
    { 196, 27, 7, 128 },
    { 168, 27, 7, 128 },
    { 152, 27, 7, 128 },
    { 136, 27, 7, 128 },
    { 120, 27, 7, 128 },
    { 0, 1 },
    { 0, 1 },
    { 0, 1 },
    { 0, 1 },
    { 0, 1 },
    { 0, 1 },
    { 0, 1 },
    { 0, 1 },
    { 0, 1 },
    { 0, 1 },
    { 0, 1 },
    { 0, 1 },
    { 0, 1 },
    { 0, 1 },
    { 0, 1 },
    { 0, 1 },
    { 200 },
    { 69, 1 },
    { 194, 1 },
    { 219, 1 },
    { 244, 1 },
    { 219, 1 },
    { 194, 1 },
    { 119, 1 },
    { 44, 1 },
    { 250 },
    { 200 },
    { 150 },
    { 100 },
    { 80 },
    { 55 },
    { 0 },
    { 206, 255, 255, 255 },
    { 181, 255, 255, 255 },
    { 156, 255, 255, 255 },
    { 186, 255, 255, 255 },
    { 216, 255, 255, 255 },
    { 231, 255, 255, 255 },
    { 246, 255, 255, 255 },
    { 251, 255, 255, 255 },
    { 20 },
    { 30 },
    { 40 },
    { 50 },
    { 59 },
    { 79 },
    { 98 },
    { 128 },
    { 157 },
    { 177 },
    { 197 },
    { 206 },
    { 216 },
    { 226 },
    { 236 },
    { 238 },
    { 236 },
    { 226 },
    { 216 },
    { 206 },
    { 197 },
    { 177 },
    { 157 },
    { 128 },
    { 98 },
    { 79 },
    { 59 },
    { 50 },
    { 40 },
    { 30 },
    { 20 },
    { 10 },
};

// Matched
void sub_80012794(UnitStatus* p, int a1)
{
    if (p->status_0 & 0x3F8)
    {
        a1 &= ~0x3F8;
    }
    p->status_0 |= a1;
}
// Matched
void sub_800127B8(UnitStatus* p)
{
    p->exp_4 = 0;
    p->hp_8 = 0;
    p->status_0 |= 0x400;
}
// Matched
void sub_800127D0(int a0, int a1, int a2, int a3)
{
    UnitStatus* v = sub_80014390(a0 & 0xFF);

    if (v != 0)
    {
        sub_80012614(v, a1, a2, a3);
    }
}
// Matched
void sub_80012828(int* p, UnitStatus* f)
{
    if (f->status_0 & 1)
    {
        p[0] = p[0] * 4 / 5;
        p[2] = p[2] * 4 / 5;
    }
    if (f->status_0 & 2)
    {
        p[1] = p[1] * 2 / 3;
        p[3] = p[3] * 2 / 3;
        p[5] = 0;
    }
    if (f->status_0 & 0x3F8)
    {
        p[4] = p[4] * 3 / 5;
        p[5] = p[5] * 3 / 5;
    }
    if (f->status_0 & 0x8000)
    {
        p[3] = (0x7FFF < p[3] + p[3] * 5) ? 0x7FFF : p[3] + p[3] * 5;
        p[1] = (0x7FFF < p[1] + p[1] * 5) ? 0x7FFF : p[1] + p[1] * 5;
        p[5] = 0;
    }
}
typedef struct
{
    unsigned char c0;
    unsigned char c1;
    short s2;
    unsigned char c4;
    unsigned char c5;
    unsigned char c6;
    unsigned char c7;
    int f8;
} Stats12;

// Matched
unsigned char* sub_800129B0(Stats12* out, unsigned char* in, int a2)
{
    int id = 0xD3;
    int kind = in[1];
    Minion* mn;
    UnitStats* u;
    MemCopy_800403E8((unsigned int*)out, (unsigned int*)sub_800318C8(kind), 12);
    mn = sub_80014444(a2 & 0xFF);
    if (mn)
    {
        id = mn->species_2;
    }
    u = sub_8001449C(a2 & 0xFF);
    if (u)
    {
        id = u->species_5C;
    }
    if (id != 0xD3)
    {
        if (kind == 0xF)
        {
            if (GetMinionEnhancementBody_80019C0C(id) & 2)
            {
                out->c7 = ((signed char)out->c7 + 60 < 126) ? out->c7 + 60 : 125;
            }
        }
        else if (kind == 0xE)
        {
            if (GetMinionEnhancementBody_80019C0C(id) & 1)
            {
                out->c7 = ((signed char)out->c7 + 60 < 126) ? out->c7 + 60 : 125;
            }
        }
        else if (kind == 0xC)
        {
            if (GetMinionEnhancementBody_80019C0C(id) & 2)
            {
                out->s2 = 0;
            }
        }
    }
    switch (in[2])
    {
    case 2:
        out->s2 = ((short)out->s2 + 30 < 256) ? (unsigned short)out->s2 + 30 : 255;
        break;
    case 3:
        out->c5 = (out->c5 + 30 > 255) ? 255 : out->c5 + 30;
        out->c6 = (out->c6 + 20 > 255) ? 255 : out->c6 + 20;
        break;
    case 4:
        out->c7 = ((signed char)out->c7 + 50 < 126) ? out->c7 + 50 : 125;
        break;
    }
    return (unsigned char*)out;
}
typedef struct
{
    unsigned short kind_0;
    short field_2;
    int flags_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    short field_24;
    short field_26;
} ActionResult;
extern const char aAssertionFaile_2[];
extern const char aCommonC[];
extern unsigned char byte_800793C4[];
extern unsigned char dword_800793C8[][4];
extern const struct_u8x12 dword_80071F58;
extern int sub_80031B30(int a0);
extern int sub_80031A04(int a0, int a1);
extern struct_12* sub_8001AD64(unsigned int idx);
extern struct_12* sub_8001D260(void);
extern void sub_800335D0(UnitStatus* src, UnitStatus* out);
extern void sub_80013EE8(int* out, UnitStatus* f, Stats12* s, int a3);
extern void sub_80013374(Stats12* s, UnitStatus* f0, UnitStatus* f1, int* r0, int* r1, int* p, ActionResult* out);
extern int Rand100_80013E30(void);
// Matched
void sub_80012BB0(UnitStatus* a0, UnitStatus* a1, int* p, ActionResult* out)
{
    int r1[12];
    int r2[12];
    UnitStatus f1;
    UnitStatus f2;
    struct_u8x12 local = dword_80071F58;
    Stats12* q;
    int b1;
    int b2;
    int t;
    int id;
    Minion* mn;
    UnitStats* u;
    int c;
    short sa;
    short sb;
    int e;
    int v;
    int d;
    int k;
    int j;
    int r;

    b1 = LowestSetBit_80014358(p[2]);
    b2 = LowestSetBit_80014358(p[3]);
    out->kind_0 = 0;
    out->flags_4 = 0;
    out->field_8 = 0;
    out->field_C = 0;
    out->field_10 = 0;
    out->field_14 = 0;
    out->field_18 = 0;
    out->field_1C = 0;
    out->field_20 = 0;
    sub_800184A0(b2, 0);
    q = (Stats12*)&local;
    switch (p[0])
    {
    case 0:
        if (p[2] == 1)
        {
            MemCopy_800403E8((unsigned int*)&local, (unsigned int*)sub_8001D260(), 12);
        }
        break;
    case 6:
        t = sub_80031B30(b1 & 0xFF);
        q = (Stats12*)sub_800129B0((Stats12*)&local, (unsigned char*)(t + p[1] * 4), b2);
        out->field_10 = sub_80031A04(t, p[1]);
        break;
    case 1:
        MemCopy_800403E8((unsigned int*)&local, (unsigned int*)sub_8001AD64(p[1]), 12);
        out->field_10 = GetMagicMpCost_8001AC58(p[1]);
        break;
    case 4:
        MemCopy_800403E8((unsigned int*)&local, (unsigned int*)GetItemData_8001CDF4(p[1]), 12);
        break;
    case 26:
        break;
    }
    sub_800335D0(a0, &f1);
    sub_800335D0(a1, &f2);
    sub_80013EE8(r1, &f1, q, p[2]);
    sub_80013EE8(r2, &f2, q, p[3]);
    sub_80012828(r1, &f1);
    sub_80012828(r2, &f2);
    if (out->field_24 == ((unsigned char*)q)[8] && q->s2 != 0)
    {
        q->s2 = (0xFFFF < q->s2 + 60) ? -1 : (unsigned short)q->s2 + 60;
    }
    if (out->field_26 == -1)
    {
        e = (signed char)q->c4;
        if (e != -1)
        {
            if ((e == 0 && out->field_24 == 1) || (e == 3 && out->field_24 == 0) || (e == 2 && out->field_24 == 3) ||
                (e == 1 && out->field_24 == 2) || out->field_24 == -1)
            {
                out->field_24 = (signed char)q->c4;
            }
        }
    }
    id = 0xD3;
    mn = sub_80014444(b1 & 0xFF);
    if (mn)
    {
        id = mn->species_2;
    }
    u = sub_8001449C(b1 & 0xFF);
    if (u)
    {
        id = u->species_5C;
    }
    if (id != 0xD3)
    {
        if ((GetMinionEnhancementBody_80019C0C(id) & 2) && p[0] == 1 && q->s2 > 0)
        {
            q->s2 = (0xFFFF < q->s2 + 10) ? -1 : (unsigned short)q->s2 + 10;
        }
        if ((GetMinionEnhancementBody_80019C0C(id) & 1) && p[0] == 6 && q->s2 > 0)
        {
            q->s2 = (0xFFFF < q->s2 + 10) ? -1 : (unsigned short)q->s2 + 10;
        }
    }
    switch (p[0])
    {
    case 0:
    case 1:
    case 4:
    case 6:
        sub_80013374(q, &f1, &f2, r1, r2, p, out);
        break;
    case 5:
    case 26:
        sa = sub_800334CC(a1);
        sb = sub_800334D8(a1);
        out->kind_0 = 7;
        v = sa / sb;
        c = sub_80033514(a1);
        if (c > 40)
        {
            c = 40;
        }
        d = (sub_80033514(a0) - c) * 10 / 12;
        if (d > 0)
        {
            if (d > 5)
            {
                d = 5;
            }
            v <<= d;
        }
        else if (d < 0)
        {
            d = -d;
            if (d > 5)
            {
                d = 5;
            }
            v /= 1 << d;
        }
        if (sub_80033548(a1, 2))
        {
            v <<= 3;
        }
        k = 0;
        while (byte_800793C4[k] < v && k < 4)
        {
            k++;
        }
        r = rand() % 16;
        j = 0;
        while (dword_800793C8[k][j] <= r)
        {
            j++;
            if (j >= 4)
            {
                printf(aAssertionFaile_2, aCommonC, 0x41C);
                exit(1);
            }
        }
        out->field_2 = j;
        out->flags_4 |= 2;
        break;
    case 7:
        v = Rand100_80013E30();
        out->kind_0 = 0;
        if (v < 81)
        {
            out->field_2 = 0;
        }
        else
        {
            out->field_2 = 1;
        }
        if (sub_80033548(a1, 2))
        {
            out->field_2 = 0;

        }
        break;
    }
    if (out->kind_0 == 5)
    {
        sub_800184A0(b2, 1);
        sub_800184A0(b2, 2);
    }
}
// Matched
int sub_80013228(int a0, int a1, int* p)
{
    struct_u8x12 local = dword_80071F58;
    unsigned char* q = local.c;
    int b1 = LowestSetBit_80014358(p[2]);
    int b2 = LowestSetBit_80014358(p[3]);
    switch (p[0])
    {
    case 0:
        if (p[2] == 1)
        {
            q = (unsigned char*)sub_8001D260();
        }
        break;
    case 6:
        q = sub_800129B0((Stats12*)&local, (unsigned char*)(sub_80031B30(b1 & 0xFF) + p[1] * 4), b2);
        break;
    case 1:
        q = (unsigned char*)sub_8001AD64(p[1]);
        break;
    case 4:
        q = (unsigned char*)GetItemData_8001CDF4(p[1]);
        break;
    case 26:
        break;
    }
    return q[8] == 8;
}

// zero word at the end of this TU's .rdata, in front of the jump table of sub_80013C28 (tu_80013358)
const int dword_800720E4 = 0;
