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
#include "tu_80019BF0.h"
#include "tu_800318C8.h"

INCLUDE_DATA(dword_80071F58);
INCLUDE_DATA(dword_80071F5C);
INCLUDE_DATA(dword_80071F60);
INCLUDE_DATA(aAssertionFaile_2);
INCLUDE_DATA(aCommonC);
INCLUDE_DATA(byte_800793C4);
INCLUDE_DATA(dword_800793C8);

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
    p->hp_8.cur_0 = 0;
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

// Matched
ActionData* sub_800129B0(ActionData* out, unsigned char* in, int a2)
{
    int id = 0xD3;
    int kind = in[1];
    Minion* mn;
    UnitStats* u;
    MemCopy_800403E8(out, sub_800318C8(kind), 12);
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
    return out;
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
extern char aAssertionFaile_2[];
extern char aCommonC[];
extern unsigned char byte_800793C4[];
extern unsigned char dword_800793C8[][4];
extern ActionData dword_80071F58; // an empty action
extern int sub_80031B30(int a0);
extern int sub_80031A04(int a0, int a1);
extern void sub_800335D0(UnitStatus* src, UnitStatus* out);
extern void sub_80013EE8(int* out, UnitStatus* f, ActionData* s, int a3);
extern void sub_80013374(ActionData* s, UnitStatus* f0, UnitStatus* f1, int* r0, int* r1, int* p, ActionResult* out);
extern int Rand100_80013E30(void);
// Matched
void sub_80012BB0(UnitStatus* a0, UnitStatus* a1, int* p, ActionResult* out)
{
    int r1[12];
    int r2[12];
    UnitStatus f1;
    UnitStatus f2;
    ActionData local = dword_80071F58;
    ActionData* q;
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
    q = &local;
    switch (p[0])
    {
    case 0:
        if (p[2] == 1)
        {
            MemCopy_800403E8(&local, sub_8001D260(), 12);
        }
        break;
    case 6:
        t = sub_80031B30(b1 & 0xFF);
        q = sub_800129B0(&local, (unsigned char*)(t + p[1] * 4), b2);
        out->field_10 = sub_80031A04(t, p[1]);
        break;
    case 1:
        MemCopy_800403E8(&local, sub_8001AD64(p[1]), 12);
        out->field_10 = GetMagicMpCost_8001AC58(p[1]);
        break;
    case 4:
        MemCopy_800403E8(&local, GetItemData_8001CDF4(p[1]), 12);
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
    if (out->field_24 == q->c8 && q->s2 != 0)
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
    ActionData local = dword_80071F58;
    ActionData* q = &local;
    int b1 = LowestSetBit_80014358(p[2]);
    int b2 = LowestSetBit_80014358(p[3]);
    switch (p[0])
    {
    case 0:
        if (p[2] == 1)
        {
            q = sub_8001D260();
        }
        break;
    case 6:
        q = sub_800129B0(&local, (unsigned char*)(sub_80031B30(b1 & 0xFF) + p[1] * 4), b2);
        break;
    case 1:
        q = sub_8001AD64(p[1]);
        break;
    case 4:
        q = GetItemData_8001CDF4(p[1]);
        break;
    case 26:
        break;
    }
    return q->c8 == 8;
}

// zero word at the end of this TU's .rdata, in front of the jump table of sub_80013C28 (tu_80013358)
INCLUDE_DATA(dword_800720E4);
