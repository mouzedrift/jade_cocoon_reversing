// BATTLE.BIN, source file 3 of 3 from 0x800BE834 (.rdata from 0x800B6774)
#include "battle.h"


void sub_800BE834(int idx, int b)
{
    switch (dword_800C9CBC[idx])
    {
    case 0:
        break;
    case 1:
        sub_800BF3DC(idx, 0, dword_800C9D38[idx], b, 0);
        if (dword_800C9D38[idx] > 0)
        {
            sub_80037BFC(0x1E);
            if (idx == 0)
            {
                StartPadVibration_80036528(0, 0);
            }
            else
            {
                StartPadVibration_80036528(0, 2);
            }
        }
        break;
    case 2:
        sub_800BF3DC(idx, 1, dword_800C9D48[idx], b, 0);
        if (dword_800C9D48[idx] > 0)
        {
            sub_80037BFC(0x1E);
            if (idx == 0)
            {
                StartPadVibration_80036528(0, 0);
            }
            else
            {
                StartPadVibration_80036528(0, 2);
            }
        }
        break;
    case 3:
        sub_800BF3DC(idx, 0, dword_800C9D38[idx], b, 0);
        sub_800BF3DC(idx, 1, dword_800C9D48[idx], b, 0xC);
        if (dword_800C9D38[idx] > 0 || dword_800C9D48[idx] > 0)
        {
            sub_80037BFC(0x1E);
            if (idx == 0)
            {
                StartPadVibration_80036528(0, 0);
            }
            else
            {
                StartPadVibration_80036528(0, 2);
            }
        }
        break;
    case 4:
        sub_800BF3DC(idx, 2, 0, b, 0);
        sub_800BF3DC(idx, 0, dword_800C9D38[idx], b, 0xC);
        sub_800BF3AC();
        sub_80037BFC(0x1E);
        if (idx == 0)
        {
            StartPadVibration_80036528(0, 1);
        }
        else
        {
            StartPadVibration_80036528(0, 2);
        }
        break;
    case 5:
        StartPadVibration_80036528(0, 0x26);
        break;
    case 6:
        break;
    case 7:
        StartPadVibration_80036528(0, dword_800C9134[((BatSlot_a*)dword_800C9CC8)[idx].b]);
        break;
    }
}

#if 0 // Not matched: the shared 'return 1' block sits after the sub_800BEB68 test in the original (here it lands at the end and the last test flips); tried goto/early-return layouts
int sub_800BEA94()
{
    if (!(*(int*)&saveData_8008B570 & 0x20))
    {
        if (sub_800BF47C() == 1)
        {
            return 0;
        }
        if (sub_800BC820(4) == 1)
        {
            if (sub_800BEB50() == 0)
            {
                return 0;
            }
            if (sub_800BEB68() == 0)
            {
                return 0;
            }
        }
        else
        {
            if (dword_800C912C[(unsigned char)dword_800C8B38[dword_800C9C88[0]]] == 0)
            {
                return sub_800BEB50();
            }
            return sub_800BEB68();
        }
    }
    return 1;
}
#endif

INCLUDE_OVERLAY_ASM(battle, sub_800BEA94);

int sub_800BEB50()
{
    return dword_800C9D94 > dword_800C9D9A;
}

int sub_800BEB68()
{
    int i;
    for (i = 0; i < 7; i++)
    {
        if (dword_800C9D94 < dword_800C9DA0[i].b)
        {
            return 0;
        }
    }
    effectOutcomeFlag_8008D780 = 1;
    return 1;
}

void ApplyBattleCommand_800BEBB8()
{
    BatCmd_a cmd;
    BatResult_a res;
    BatUnit_a* actor;
    BatUnit_a* m;
    int flag;
    int r;
    unsigned int i;
    int bit;
    int a;

    sub_800BC7DC(dword_800C9C7C);
    flag = 1;
    actor = (BatUnit_a*)sub_80014390(dword_800C9C7C);
    cmd = *(BatCmd_a*)dword_800C9C88;
    if (dword_800C9C88[0] == 0x12)
    {
        actor = (BatUnit_a*)sub_80014390(dword_800C9C7C);
        actor->flags_0 |= 0x8000;
    }
    for (i = 0; i < 7; i++)
    {
        r = sub_800BC7DC(i);
        bit = 1 << i;
        ((BatSlot_a*)dword_800C9CC8)[i].a = 0x14;
        ((BatSlot_a*)dword_800C9CC8)[i].b = 0;
        ((BatSlot_a*)dword_800C9CC8)[i].c = bit;
        ((BatSlot_a*)dword_800C9CC8)[i].d = 0;
        if (dword_800C9C88[3] & bit)
        {
            m = (BatUnit_a*)sub_80014390(i & 0xFF);
            res.f24 = (signed char)dword_800C9D82;
            res.f26 = (signed char)dword_800C9D83;
            cmd.fC = bit;
            sub_80012BB0(actor, m, &cmd, &res);
            if (dword_800ADE78 == 1)
            {
                sub_800B4390(actor, m, dword_800C9C88, &res, &dword_800ADE78);
            }
            dword_800C9D84 = res.f24;
            dword_800C9D38[i] = res.f1C;
            dword_800C9D48[i] = res.f20;
            if (dword_800C9C7C < 7 && i != dword_800C9C7C)
            {
                dword_800C9D38[dword_800C9C7C] += res.f14;
                dword_800C9D48[dword_800C9C7C] += res.f18;
                if (dword_800C9D38[dword_800C9C7C] != 0)
                {
                    if (dword_800C9D48[dword_800C9C7C] != 0)
                    {
                        dword_800C9CBC[dword_800C9C7C] = 3;
                    }
                    else
                    {
                        dword_800C9CBC[dword_800C9C7C] = 1;
                    }
                }
                else if (dword_800C9D48[dword_800C9C7C] != 0)
                {
                    dword_800C9CBC[dword_800C9C7C] = 2;
                }
            }
            if (dword_800C9D38[i] > 0)
            {
                if (m->hp_8 < dword_800C9D38[i])
                {
                    dword_800C9D38[i] = m->hp_8;
                }
            }
            else if (dword_800C9D38[i] < m->hp_8 - m->hpLoss_A)
            {
                dword_800C9D38[i] = m->hp_8 - m->hpLoss_A;
            }
            if (dword_800C9D48[i] > 0)
            {
                if (m->mp_C < dword_800C9D48[i])
                {
                    dword_800C9D48[i] = m->mp_C;
                }
            }
            else if (dword_800C9D48[i] < m->mp_C - m->mpLoss_E)
            {
                dword_800C9D48[i] = m->mp_C - m->mpLoss_E;
            }
            if (res.fC != 0)
            {
                dword_800C9C7E = res.fC;
            }
            if (res.f10 != 0)
            {
                dword_800C9C80 = res.f10;
            }
            if (sub_800BC784(i) == 1)
            {
                dword_800C9CBC[i] = res.kind_0;
                dword_800C9D58[i] = res.f4;
                dword_800C9CA0[i] = res.f8;
                switch (res.kind_0)
                {
                case 0:
                    ((BatSlot_a*)dword_800C9CC8)[i].b = res.arg_2;
                    if (res.arg_2 != 0)
                    {
                        flag = 0;
                    }
                    break;
                case 1:
                case 2:
                case 3:
                    if (dword_800C9D38[i] > 0 || dword_800C9D48[i] > 0)
                    {
                        ((BatSlot_a*)dword_800C9CC8)[i].a = 9;
                        dword_800C9D78 = 0x72;
                    }
                    break;
                case 4:
                    ((BatSlot_a*)dword_800C9CC8)[i].a = 10;
                    dword_800C9D78 = 0x71;
                    break;
                case 5:
                    a = m->flags_0 & 0x8000;
                    ((BatSlot_a*)dword_800C9CC8)[i].a = a ? 0x14 : 0xC;
                    dword_800C9D78 = 0x70;
                    break;
                case 7:
                    ((BatSlot_a*)dword_800C9CC8)[i].a = 5;
                    ((BatSlot_a*)dword_800C9CC8)[i].b = res.arg_2;
                    dword_800C9C88[1] = res.arg_2;
                    if (sub_80013358(res.arg_2) == 1)
                    {
                        sub_800BF9F0(sub_800A2BE4(i - 4));
                        if (GetCapturedMinionsFromBitfield_8003BA58(sub_800A248C()) == 1)
                        {
                            dword_800C9C88[0] = 0x1A;
                        }
                        sub_800BC838(0x40);
                        if (r == 2)
                        {
                            
                            dword_800B1238[i - 4].c = dword_800C9C7C;
                            dword_800B1238[i - 4].e = dword_800C9C88[0];
                            dword_800B1238[i - 4].a = m->f4;
                            dword_800B1238[i - 4].d = m->f44;
                        }
                    }
                    break;
                }
                if (m->hp_8 <= dword_800C9D38[i] || (dword_800C9CA0[i] & 0x600))
                {
                    dword_800C9D38[i] = m->hp_8;
                    ((BatSlot_a*)dword_800C9CC8)[i].a = 0xB;
                    if (r == 2)
                    {
                        sub_800BC838(0x40);
                        if (sub_800BF9B4(sub_800A2BE4(i - 4)) == 1)
                        {
                            sub_800BC838(0x100000);
                        }
                        else
                        {
                            sub_800BC850(0x100000);
                        }
                        if (sub_800A2AB4() == 2)
                        {
                            sub_800BC838(2);
                        }
                        
                        dword_800B1238[i - 4].b = sub_800A2BE4(i - 4);
                        dword_800B1238[i - 4].c = dword_800C9C7C;
                        dword_800B1238[i - 4].e = dword_800C9C88[0];
                        dword_800B1238[i - 4].a = m->f4;
                        dword_800B1238[i - 4].d = m->f44;
                        if (sub_800BC820(0x100000) == 1)
                        {
                            dword_800C9D80 = 0x1C;
                        }
                        else
                        {
                            dword_800C9D80 = 0x6F;
                        }
                    }
                    else if (r == 0)
                    {
                        sub_800BC838(4);
                        dword_800C9D80 = 0x1C;
                    }
                    else
                    {
                        sub_800BC838(8);
                        dword_800C9D80 = 0x6F;
                    }
                }
            }
            if (i == dword_800C9C7C)
            {
                ((BatSlot_a*)dword_800C9CC8)[i].a = 0x14;
            }
        }
    }
    if (dword_800C9C88[0] == 7)
    {
        if (flag == 1)
        {
            dword_800C9C88[1] = 0;
            if (sub_800BC7DC(dword_800C9C7C) == 0)
            {
                sub_800BC838(0x80);
            }
        }
        else
        {
            dword_800C9C88[1] = 1;
            if (sub_800BC7DC(dword_800C9C7C) == 2)
            {
                dword_800C9C88[0] = 0x14;
            }
        }
    }
}

void sub_800BF2E8()
{
    int v;
    if ((sub_800BC7DC(dword_800C9C7C) == 0 && ((v = dword_800C9C88[0]) == 5 || v == 0x1A || v == 2 || v == 3 || v == 7))
        || (sub_800BC7DC(dword_800C9C7C) == 1 && ((v = dword_800C9C88[0]) - 2 < 2U || v == 8)))
    {
        sub_800BC838(0x8000);
        sub_800BC838(0x10000);
    }
    else
    {
        sub_800BC850(0x8000);
        sub_800BC850(0x10000);
    }
}

void sub_800BF3AC()
{
    unsigned char buf[3];
    buf[0] = 0xFF;
    buf[1] = 0xFF;
    buf[2] = 0xFF;
    StartScreenFlash_8001C02C(buf);
}

void sub_800BF3DC(int a, int b, int c, int d, int e)
{
    EventEntry* p = AllocEventEntry_80043AF8(dword_8008D778);
    if (p)
    {
        int* q = p->buffer;
        p->flags = (p->flags | 1) & 0xFFFF7FFF;
        q[0] = b;
        q[2] = 0;
        q[3] = 0;
        q[1] = c;
        q[4] = d;
        q[5] = e;
        q[6] = a;
        p->cb_8 = (EventEntryFn)sub_800BF4D0;
    }
}

int sub_800BF47C()
{
    EventNode* h = dword_8008D778;
    EventNode* n;
    int i = 0;
    int cnt = h->count;
    for (n = h; i < cnt; i++)
    {
        if ((n->entry.flags & 0x8001) == 1)
        {
            return 1;
        }
        n = n->next;
    }
    return 0;
}

void sub_800BF4D0(EventEntry* t, int* u)
{
    DVECTOR sxy;
    SVECTOR v;
    long p;
    long flag;
    int x;
    v.vx = ((unsigned short*)u[4])[0];
    v.vy = ((unsigned short*)u[4])[2];
    v.vz = ((unsigned short*)u[4])[4];
    v.vx -= dword_8008D600[0].field_0;
    v.vy -= dword_8008D600[1].field_0;
    v.vz -= dword_8008D600[2].field_0;
    RotTransPers(&v, (long*)&sxy, &p, &flag);
    u[2]++;
    if (u[2] > 0x10)
    {
        t->flags = (t->flags & ~1) | 0x8000;
        return;
    }
    if (u[2] > 8)
    {
        u[3] -= 4;
    }
    else
    {
        u[3] += 4;
    }
    x = u[1] / (0x11 - u[2]);
    x = -x;
    u[1] += x;
    if (u[0] == 0)
    {
        sub_800127D0(u[6], 0, x, 0);
        if (*(short*)(sub_80014390((unsigned char)u[6]) + 8) <= 0)
        {
            sub_800127B8((struct_obj_B*)sub_80014390((unsigned char)u[6]));
        }
    }
    if (u[0] == 1)
    {
        sub_800127D0(u[6], 2, x, 0);
    }
}

#if 0 // Not matched: cse keeps 500 in a register for case 2 (original reloads it), which reorders the init stores; tried if-chains, struct, returns, default
void sub_800BF648(short* p, int mode)
{
    p[0] = 500;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = -0x2BC;
    p[6] = -0x578;
    switch (mode)
    {
    case 1:
        p[0] = 1000;
        return;
    case 0:
        return;
    case 2:
        p[0] = 0;
        p[4] = 1000;
        p[5] = 500;
        p[6] = 0x14D;
        return;
    }
}
#endif

INCLUDE_OVERLAY_ASM(battle, sub_800BF648);

#if 0 // Not matched: body matches with a goto inner loop (a for loop gets strength-reduced); prologue saves are not interleaved and a/b take s3/s2 in the original (s2/s3 here)
int sub_800BF6BC(unsigned short* a, int b)
{
    int r;
    unsigned int i;
    r = -1;
    do
    {
        i = 0;
    loop:
        if (i >= 4 || b == i)
        {
            a[i] += sub_800BF784(i);
            if ((short)a[i] >= 1000)
            {
                a[i] = 0;
                r = i;
                continue;
            }
        }
        i++;
        if (i < 7)
        {
            goto loop;
        }
    } while (r < 0);
    return r;
}
#endif

INCLUDE_OVERLAY_ASM(battle, sub_800BF6BC);

void sub_800BF770(short* p, int i)
{
    p[i] = 0x320;
}

int sub_800BF784(int a)
{
    unsigned char buf[0x18];
    int p = sub_80014390(a & 0xFF);
    if (p == 0)
    {
        return 0;
    }
    CalcEquippedStats_80033624(buf, p);
    return buf[4] + 10;
}

#if 0 // Not matched: body close with a goto loop; prologue saves are not interleaved with the arg copies in the original and b/f/table-base get different saved registers
typedef struct BatChance_a
{
    unsigned int mask;
    unsigned int chance;
} BatChance_a;
extern BatChance_a dword_800C9138[];
extern int GetEquipmentId_8003356C(unsigned char* p, unsigned int idx);
extern unsigned int Rand100_80013E30();
void sub_800BF7C4(unsigned char* p, short* a, short* b)
{
    unsigned int f = *(unsigned int*)p;
    unsigned int f0 = f;
    int i;
    BatChance_a* e;
    *a = 0;
    *b = 0;
    f = sub_800BFA34(f);
    if ((GetEquipmentId_8003356C(p, 2) & 0xFF) == 0x10)
    {
        f |= 0x4000;
    }
    if (f0 & 1)
    {
        *a = *(short*)(p + 0xA) / 10;
        f &= ~2;
    }
    else if (f & 0x4000)
    {
        *a = -(short)(*(short*)(p + 0xA) / 20);
    }
    if (f0 & 0x8000)
    {
        *b = -((p[0x44] >> 2) + 3);
        f &= ~0x8000;
    }
    if (f & 0x200)
    {
        *a = *(short*)(p + 8);
    }
    i = 0;
loop:
    e = &dword_800C9138[i];
    if (f0 & e->mask)
    {
        if (Rand100_80013E30() >= e->chance)
        {
            f &= ~e->mask;
        }
    }
    i++;
    if (i < 1)
    {
        goto loop;
    }
    *(unsigned int*)p = f;
}
#endif

INCLUDE_OVERLAY_ASM(battle, sub_800BF7C4);

int sub_800BF980(int x)
{
    int r = 0;
    if (x >= 0x29)
    {
        if (x < 0x39)
        {
            r = 1;
        }
        else if (x < 0xD3)
        {
            if (x > 0xC8)
            {
                r = 1;
            }
        }
    }
    return r;
}

int sub_800BF9B4(int x)
{
    int r = 0;
    switch (x)
    {
    case 0x29:
    case 0x2C:
    case 0x2E:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x37:
        r = 1;
        break;
    }
    return r;
}

INCLUDE_OVERLAY_ASM(battle, dword_800B67F0);

#if 0 // Not matched: x is copied to v1 and the mask is built before the load in the original; regalloc/schedule differ in every variant tried
void sub_800BF9F0(int a)
{
    unsigned int x = a;
    unsigned int* p = allMinionsBitfields_8008BD84;
    if (x < 0xE0)
    {
        unsigned int* q = &p[x >> 5];
        int m = 1 << (x & 0x1F);
        *q = m | *q;
    }
}
#endif

INCLUDE_OVERLAY_ASM(battle, sub_800BF9F0);

int sub_800BFA34(int x)
{
    int y = x & 0x3F8;
    return (x & ~0x3F8) | (y << 1);
}

#if 0 // Not matched: only the last test: andi goes to v1 instead of v0 (and branch sense/layout); tried ternary, if/else, r variable, int params
int sub_800BFA4C(unsigned int a, unsigned int b)
{
    if (a & 0x200)
    {
        return 0x13;
    }
    if (a & 2)
    {
        if (!(b & 2))
        {
            return 0x10;
        }
    }
    if (a & 0x8000)
    {
        if (!(b & 0x8000))
        {
            return 0x12;
        }
    }
    if (a & 1)
    {
        return 9;
    }
    if (b & 2)
    {
        if (!(a & 2))
        {
            return 0xF;
        }
    }
    if (b & 0x8000)
    {
        if (!(a & 0x8000))
        {
            return 0x11;
        }
    }
    if (!(a & 0x4000))
    {
        return 0x14;
    }
    return 0x19;
}
#endif

INCLUDE_OVERLAY_ASM(battle, sub_800BFA4C);

void sub_800BFAF8(int x)
{
    int a;
    switch (x)
    {
    case 9:
        a = 1;
        break;
    case 7:
        a = 8;
        break;
    case 11:
        a = 4;
        break;
    case 14:
        a = 0;
        break;
    case 18:
        a = 2;
        break;
    case 2:
        a = 3;
        break;
    case 13:
        a = 5;
        break;
    case 21:
        a = 7;
        break;
    case 22:
    default:
        return;
    }
    sub_80018430(a);
}

void sub_800BFB80()
{
    sub_800BFC10();
    sub_800BFC40();
    sub_800C01D8();
    sub_800C0440();
}

void sub_800BFBB8()
{
    StopAllEventEntries_80043B40(dword_8008B568);
    StopAllEventEntries_80043B40(dword_8008B564);
    StopAllEventEntries_80043B40((int*)dword_8008D4B0);
    StopAllEventEntries_80043B40((int*)dword_8008D63C);
}

void sub_800BFC10()
{
    dword_800C9DFD = 0;
    dword_800C9DFC = 0;
    dword_800C9170 = 0;
    dword_800C9174[0] = 0;
    dword_800C9174[1] = 0;
    dword_800C9174[2] = 0;
}

void sub_800BFC40()
{
    EventEntry* e = AllocEventEntry_80043AF8((EventNode*)dword_8008B568);
    int m;
    int n;
    int i;
    int b;
    if (e)
    {
        m = sub_800A248C();
        n = GetCapturedMinionsFromBitfield_8003BA58(m);
        if (sub_800A2AB4())
        {
            m = 0x10;
        }
        dword_800C9DF8 = 0;
        dword_800C9E24 = 0;
        e->cb_8 = (EventEntryFn)sub_800BFDEC;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        for (i = 0; i < 3; i++)
        {
            b = m & (1 << (i + 4));
            if (b != 0)
            {
                e = AllocEventEntry_80043AF8((EventNode*)dword_8008B564);
                if (e)
                {
                    BatXY_a* pp = (BatXY_a*)((char*)dword_800C9140 + ((n - 1) * 12 + i * 4));
                    short* q;
                    e->flags = (e->flags | 1) & 0xFFFF7FFF;
                    q = e->buffer;
                    *(int*)q = i;
                    *(int*)(q + 2) = 0;
                    q[4] = pp->x;
                    q[5] = pp->y;
                    q[6] = 0x64;
                    q[7] = 0x29;
                    e->cb_8 = (EventEntryFn)sub_800C0074;
                    dword_800C9E28[i] = (char*)q;
                    dword_800C9E18[i].x = pp->x;
                    dword_800C9E18[i].x = pp->x;
                    dword_800C9E18[i].y = pp->y;
                    dword_800C9E08[i] = e;
                }
            }
        }
    }
}

void sub_800BFDEC()
{
    int m;
    int n;
    int diff;
    int i;
    int k;
    int one;
    int bit;
    BatXY_a* pp;
    m = sub_800A248C();
    if (m != 0 && sub_800A2AB4() != 0)
    {
        m = 0x10;
    }
    n = GetCapturedMinionsFromBitfield_8003BA58(m);
    if (dword_800C9E24 != m)
    {
        diff = (dword_800C9E24 | m) ^ m;
        dword_800C9E24 = m;
        one = 1;
        dword_800C9DF8 |= one;
        dword_800C9E00 = 0;
        for (i = 0; i < 3; i++)
        {
            if (diff & (one << (i + 4)))
            {
                if (sub_800A2AB4() != 2)
                {
                    dword_800C9E08[i]->flags &= ~1;
                    dword_800C9E08[i]->flags |= 0x8000;
                }
                else
                {
                    sub_800BC838(0x10000);
                }
            }
            if (m & (one << (i + 4)))
            {
                dword_800C9E18[i].x = ((short*)dword_800C9E28[i])[4];
                dword_800C9E18[i].y = ((short*)dword_800C9E28[i])[5];
            }
        }
    }
    if (dword_800C9DF8 & 1)
    {
        if (dword_800C9E00 < 4)
        {
            dword_800C9E00++;
            k = 0;
            for (i = 0, bit = 1; i < 3; i++)
            {
                if (m & (bit << (i + 4)))
                {
                    pp = (BatXY_a*)((char*)dword_800C9140 + ((n - 1) * 12 + k * 4));
                    ((short*)dword_800C9E28[i])[4] += (pp->x - ((short*)dword_800C9E28[i])[4]) * dword_800C9E00 >> 2;
                    ((short*)dword_800C9E28[i])[5] += (pp->y - ((short*)dword_800C9E28[i])[5]) * dword_800C9E00 >> 2;
                    k++;
                }
            }
        }
        else
        {
            dword_800C9DF8 &= ~1;
        }
    }
}

#if 0 // Not matched: one word: 'k = 1' reuses the compare constant (move s2,v1) instead of li; u must be copied after the early return
typedef struct BatWin_a
{
    int slot_0;
    int frame_4;
    short from_8[4];
    short rect_10[4];
} BatWin_a;
extern void sub_8002F1C8();
extern int dword_800C9164[];
void sub_800C0074(EventEntry* t, void* arg)
{
    int k;
    int m;
    int r;
    BatWin_a* u;
    if (dword_800B1228 & 0x10000)
    {
        return;
    }
    u = arg;
    r = sub_800A2AB4();
    k = 0;
    if (r != 1)
    {
        k = 1;
        if (sub_800A2AB4() != 2)
        {
            k = u->slot_0;
        }
    }
    m = sub_80014390((k + 4) & 0xFF);
    AddClipDrawAreaPrim_80033308((char*)pOT_8008D454 + 0x28);
    SetFontClutOffset_8003F900(1, 0);
    InterpolateWindowRect_8004196C(u->rect_10, u->from_8, u->frame_4, 4, 9);
    if (sub_800BF980(sub_800A2BE4(k)))
    {
        sub_8002F1C8(m, dword_800C9164[k], dword_800C9DFC, dword_800C9174[k], u->rect_10, 10, 1);
    }
    else
    {
        sub_8002F1C8(m, dword_800C9164[k], dword_800C9DFC, dword_800C9174[k], u->rect_10, 10, 0);
    }
    u->frame_4++;
    AddDrawAreaPrim_8003326C(u->rect_10, (char*)pOT_8008D454 + 0x28);
}
#endif

INCLUDE_OVERLAY_ASM(battle, sub_800C0074);

void sub_800C01D8()
{
    struct_cb* r = AllocEventEntry_80043AF8(dword_8008D4B0);
    if (r != 0)
    {
        unsigned char* p = (unsigned char*)r->field_14;
        r->flags_0 = (r->flags_0 | 1) & ~0x8000;
        *(int*)p = 0;
        *(short*)(p + 4) = 0x6E;
        *(short*)(p + 6) = 0xAC;
        *(short*)(p + 8) = 0x64;
        *(short*)(p + 10) = 0x29;
        r->fn_8 = (void (*)(struct_cb*, int*))sub_800C0254;
    }
}

typedef struct BatWin_b
{
    unsigned int frame_0;
    short from_4[4];
    short rect_C[4];
} BatWin_b;
typedef struct BatBox_b
{
    short col_0;
    char c_2;
    char c_3;
} BatBox_b;
extern void sub_8002F120(int a0, short* pos, int a2, int a3);
extern void sub_8002F480(int a0, void* pos, int ot, int reverse);
extern void DrawWindow_80042460(void* rect, BatBox_b* box, void* ot, int a3);
extern unsigned short uiColor_8008B590;

// Matched
void sub_800C0254(EventEntry* t, void* arg)
{
    BatWin_b* u;
    short pos[4];
    BatBox_b box;
    short rect[4];
    int m;
    if (dword_800ADE78 == 1 && dword_800C9C7C == 10)
    {
        return;
    }
    if (dword_800B1228 & 0x8000)
    {
        return;
    }
    u = arg;
    m = sub_80014390(dword_800C9C99);
    AddClipDrawAreaPrim_80033308((char*)pOT_8008D454 + 0x28);
    InterpolateWindowRect_8004196C(u->rect_C, u->from_4, u->frame_0, 4, 9);
    if (dword_800C9C99 == 0)
    {
        sub_8002F1C8(m, dword_800C9180, dword_800C9DFD, dword_800C9170, u->rect_C, 10, 2);
    }
    else
    {
        sub_8002F1C8(m, dword_800C9180, dword_800C9DFD, dword_800C9170, u->rect_C, 10, 0);
    }
    if (dword_800C9C99 != 0)
    {
        pos[0] = 0xD2;
        pos[1] = 0xC0;
        sub_8002F120(m, pos, dword_800C9182, 0xF);
        box.c_3 = 1;
        rect[2] = 0x64;
        rect[3] = 0x15;
        box.col_0 = uiColor_8008B590;
        box.c_2 = 0;
        rect[0] = 0xD2;
        rect[1] = 0xC0;
        DrawWindow_80042460(rect, &box, (char*)pOT_8008D454 + 0x3C, 0);
    }
    u->frame_0++;
    if (u->frame_0 >= 5)
    {
        u->frame_0 = 4;
    }
    sub_8002F480(m, 0, 0xF, 0);
    AddDrawAreaPrim_8003326C(u->rect_C, (char*)pOT_8008D454 + 0x28);
}

void sub_800C0440()
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D63C);
    if (e)
    {
        dword_800C9D74 = 0;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        *(int*)e->buffer = 0;
        e->cb_8 = (EventEntryFn)sub_800C04A4;
    }
}

#if 0 // Not matched: u and w swap saved registers (s1/s0); tried w types, decl order, pre-increment
typedef struct BatHelp_a
{
    unsigned int frame_0;
    short from_4[4];
    short rect_C[4];
} BatHelp_a;
extern unsigned char dword_800793C8[];
extern void DrawText_8003E91C(int mode, void* str, void* pos, int z);
extern void sub_8003F264(void* pos, int val, int ot);
extern void DrawUiColorWindow_800424C0();
void sub_800C04A4(EventEntry* t, BatHelp_a* u)
{
    int w;
    short pos[2];
    unsigned char* g;
    if (padPressed_8009194C & 0x100)
    {
        *(int*)&saveData_8008B570 ^= 0x10;
    }
    if (*(int*)&saveData_8008B570 & 0x10)
    {
        return;
    }
    if (dword_800C9D74 == 0)
    {
        return;
    }
    AddClipDrawAreaPrim_80033308(pOT_8008D454);
    w = MeasureTextWidth_8003E4C8(dword_800C9D74);
    g = dword_800793C8 + 0x14;
    if (*(int*)(g + 0x24) == dword_800C9D74)
    {
        w += 0x10;
    }
    u->from_4[2] = w + 4;
    u->from_4[3] = 0x14;
    u->from_4[0] = 0xA;
    u->from_4[1] = 0x88;
    pos[0] = u->from_4[0] + 2;
    pos[1] = u->from_4[1] + 3;
    DrawText_8003E91C(2, (void*)dword_800C9D74, pos, 0);
    if (*(int*)(g + 0x24) == dword_800C9D74)
    {
        pos[0] += w;
        pos[1] += 3;
        sub_8003F264(pos, sub_800AD8E4(), 0);
    }
    InterpolateWindowRect_8004196C(u->rect_C, u->from_4, u->frame_0, 4, 7);
    DrawUiColorWindow_800424C0(u->rect_C, 0, pOT_8008D454, 0);
    if (++u->frame_0 >= 5)
    {
        u->frame_0 = 4;
    }
    AddDrawAreaPrim_8003326C(u->rect_C, pOT_8008D454);
}
#endif

INCLUDE_OVERLAY_ASM(battle, sub_800C04A4);

void sub_800C064C(unsigned char* m, int* o, int c)
{
    unsigned char ids[8];
    int counts[3];
    int self;
    int t;
    self = *(unsigned short*)sub_80019C70(m[2]);
    o[0] = sub_800338DC(m + 0x4C, ids, counts);
    o[1] = *(unsigned short*)sub_80019C70(ids[0]);
    o[2] = *(unsigned short*)sub_80019C70(ids[1]);
    o[3] = *(unsigned short*)sub_80019C70(ids[2]);
    o[4] = counts[0];
    o[5] = counts[1];
    o[6] = counts[2];
    if (o[1] == o[2])
    {
        if (o[2] == o[3])
        {
            o[4] += o[5];
            o[4] += o[6];
            o[5] = 0;
            o[6] = 0;
            o[0] = 1;
        }
        else
        {
            o[4] += o[5];
            o[2] = o[3];
            o[5] = o[6];
            o[0] = 2;
            o[6] = 0;
        }
    }
    else if (o[1] == o[3])
    {
        o[4] += o[6];
        o[6] = 0;
        o[0] = 2;
    }
    else if (o[2] == o[3])
    {
        o[5] += o[6];
        o[6] = 0;
        o[0] = 2;
    }
    o[11] = 0;
    if (o[1] != self)
    {
        if (o[2] == self)
        {
            o[2] = o[1];
            o[1] = self;
            t = o[5];
            o[5] = o[4];
            o[4] = t;
        }
        else if (o[3] == self)
        {
            o[3] = o[1];
            o[1] = self;
            t = o[6];
            o[6] = o[4];
            o[4] = t;
        }
        else if (o[0] < 2)
        {
            o[2] = o[1];
            o[1] = self;
            o[5] = o[4];
            o[4] = 0;
            o[0] = 2;
        }
        else
        {
            o[3] = o[1];
            o[1] = self;
            o[6] = o[4];
            o[4] = 0;
            o[0] = 3;
        }
    }
    o[7] = sub_80019A80(m[0xC8]);
    o[8] = o[0] - 1;
    o[10] = *(unsigned short*)sub_80019C70(m[3]);
    o[12] = c;
    o[9] = sub_800C0904(m + 0xC2);
    if (o[9] == -1000)
    {
        o[9] = ((unsigned char*)sub_80019C70(m[3]))[2] * 2;
    }
    else
    {
        o[9] -= ((unsigned char*)sub_80019C70(m[3]))[3] * 2;
        if (o[9] < 0)
        {
            o[9] += 360;
        }
    }
}

int sub_800C0904(unsigned char* p)
{
    int n = 0;
    int i;
    int r;
    for (i = 0; i < 4; i++)
    {
        if (p[i])
        {
            n++;
        }
    }
    if (n == 1)
    {
        r = -1000;
    }
    else if (n == 2)
    {
        if (p[3] && p[1])
        {
            if (p[1] < p[3])
            {
                r = 0xF5;
            }
            else
            {
                r = 0x41;
            }
        }
        else if (p[0] && p[2])
        {
            if (p[2] < p[0])
            {
                r = 0x14F;
            }
            else
            {
                r = 0x9B;
            }
        }
        else
        {
            r = sub_800C09D4(p);
        }
    }
    else
    {
        r = sub_800C09D4(p);
    }
    return r;
}

#if 0 // Not matched: temp register numbering of the eight products (same function as SHOP sub_800BF3B4)
extern short word_80084540[];
int sub_800C09D4(unsigned char* p)
{
    int t1 = word_80084540[0x2E3] * p[0];
    int t2 = word_80084540[0xEE3] * p[0];
    int t3 = word_80084540[0xEE3] * p[3];
    int t4 = word_80084540[0xAE3] * p[3];
    int t5 = word_80084540[0xAE3] * p[2];
    int t6 = word_80084540[0x6E3] * p[2];
    int t7 = word_80084540[0x6E3] * p[1];
    int t8 = word_80084540[0x2E3] * p[1];
    return ratan2Degrees_8003B56C(t1 + t3 + t5 + t7, t2 + t4 + t6 + t8);
}
#endif

INCLUDE_OVERLAY_ASM(battle, sub_800C09D4);

void sub_800C0A94()
{
}

int sub_800C0A9C()
{
    int n = CountMinions_80010548(3);
    int r = 0;
    int i;
    for (i = 0; i < n; i++)
    {
        r |= 1 << (i + 1);
    }
    return r;
}

int sub_800C0AEC(int a, int* b, int c)
{
    char buf[0x38];
    int h;
    if (sub_800C0D50() != -1)
    {
        return 0;
    }
    h = (int)GetMinion_80010598(3, a);
    if (h == 0)
    {
        return 0;
    }
    dword_800C9188 = h;
    sub_800C064C(h, buf, dword_8007DC74);
    StartModelTask_80010850(buf);
    dword_800C9190.f4 = b[0];
    dword_800C9190.f8 = b[1];
    dword_800C9190.fc = b[2];
    dword_800C918C = a;
    dword_800C9190.f10 = c;
    return 1;
}

int sub_800C0BA0()
{
    if (sub_800C0D50() >= 0)
    {
        FreeModelTask_8001098C(0);
        DestroyActor_8001D600(dword_800C9190.obj);
        dword_800C918C = -1;
        return 1;
    }
    return 0;
}

int sub_800C0BF0()
{
    struct
    {
        int field_0;
        int field_4;
        int pos[3];
        short rot[3];
        short pad_1A;
        int field_1C;
        int field_20;
        int field_24;
        int field_28;
        int field_2C;
        int field_30;
        int* field_34;
        int field_38;
        int field_3C;
        int field_40;
        int field_44;
        int field_48;
        int field_4C;
    } s;
    void* m;
    int k;
    int x;
    // RunModelTask_80010A10 is declared void in funcs.h, but its result is used here
    if (((int (*)(int))RunModelTask_80010A10)(0) != 0)
    {
    m = (void*)sub_80010A44(0);
    k = sub_80019A80(((unsigned char*)dword_800C9188)[0xC8]);
    s.field_0 = -1;
    s.field_4 = 2;
    s.pos[0] = dword_800C9190.f4;
    s.pos[1] = dword_800C9190.f8;
    s.pos[2] = dword_800C9190.fc;
    s.rot[0] = 0;
    s.rot[1] = dword_800C9190.f10;
    s.rot[2] = 0;
    s.field_1C = 3;
    s.field_20 = 4;
    s.field_24 = -1;
    s.field_28 = 0x1000;
    s.field_2C = 4;
    s.field_30 = 0;
    s.field_48 = (int)m;
    s.field_34 = &dword_80079140;
    s.field_38 = (int)sub_80024E90(m, k);
    s.field_3C = (int)sub_80024EC8(m, k);
    s.field_40 = (int)sub_80024E38(m);
    s.field_44 = (int)sub_80024E64(m);
    s.field_4C = 1;
    dword_800C9190.obj = (char*)CreateActor_8001D45C((int)&s);
    sub_8001D68C((struct_obj_A*)dword_800C9190.obj, 0);
    x = (int)sub_80024F00(m, k);
    sub_80019B14(*(int*)(dword_800C9190.obj + 0x134), x, (int)sub_80024F38(m, k));
        return 1;
    }
    return 0;
}

int sub_800C0D50()
{
    return dword_800C918C;
}

int sub_800C0D60()
{
    return sub_8001E1C8((void*)dword_800C9190.obj);
}

int sub_800C0D88()
{
    return sub_8001E1DC(dword_800C9190.obj);
}

void sub_800C0DB0(int a)
{
    sub_8001DB00(dword_800C9190.obj, a, 0x55);
}

#if 0 // Not matched: struct-return copy: 'move v0,s1' is scheduled before the lwl/lwr copy (original: after); tried explicit out-pointer form
BatCol_a* sub_800C0DDC(BatCol_a* out, int* p, int c)
{
    BatCol_a buf;
    int mask;
    memset(&buf, 0, 4);
    if (p[0] != 0x14 && (p[2] & (mask = 1 << (dword_800C918C + 1))))
    {
        sub_80018A4C(&buf, dword_800C9190.obj, p, 0, c);
    }
    *out = buf;
    return out;
}
#endif

INCLUDE_OVERLAY_ASM(battle, sub_800C0DDC);

int sub_800C0E84(int* p)
{
    int mask;
    if (p[0] == 0x14)
    {
        return 0;
    }
    mask = 1 << (dword_800C918C + 1);
    if (p[2] & mask)
    {
        sub_8001E28C(dword_800C9190.obj);
    }
    return 1;
}

void sub_800C0EE8(int a)
{
    sub_80018E5C(dword_800C9190.obj, a);
}

int sub_800C0F14()
{
    return 0;
}

void sub_800C0F1C()
{
    sub_80018EBC(dword_800C9190.obj, sub_800C0F78(dword_800C918C));
}

void sub_800C0F54(int a)
{
    GetMinionName_800106F8(3, a);
}

int sub_800C0F78(int a)
{
    GetMinionStatus_800107A0(3, a);
}

char* sub_800C0F9C()
{
    return dword_800C9190.obj + 0x38;
}

int sub_800C0FAC()
{
    return *(int*)(dword_800C9190.obj + 0x1C4);
}

void sub_800C0FC4(int* p)
{
    char* q = dword_800C9190.obj;
    p[0] = *(int*)(q + 0x14C);
    p[1] = (int)(q + 0x38);
    p[2] = *(int*)(q + 0x1C4);
    p[3] = *(int*)(q + 0x1C8);
    p[11] = *(int*)(q + 0x144);
    p[12] = (int)(q + 0x2C);
}

int sub_800C100C(int a)
{
    int h = (int)GetMinion_80010598(3, a);
    if (h)
    {
        return h + 0xDE;
    }
    return 0;
}

int sub_800C103C(int a)
{
    int h = (int)GetMinion_80010598(3, a);
    if (h)
    {
        return h + 0xF4;
    }
    return 0;
}

void sub_800C106C(unsigned int* a, int* b)
{
    if (--b[1] < 0)
    {
        *a = (*a & ~1) | 0x8000;
        StopSeqSlot_80031334(b[0]);
    }
}

void sub_800C10B8(int a, int b)
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D60C);
    if (a > 0 && e)
    {
        int* q;
        PlaySeqSlot_80031160(b, 1);
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        q = e->buffer;
        q[0] = b;
        q[1] = a;
        e->cb_8 = (EventEntryFn)sub_800C106C;
    }
}

void sub_800C1140(unsigned int* a, short* b)
{
    if (--*(int*)(b + 2) < 0)
    {
        *a = (*a & ~1) | 0x8000;
        SfxKeyOff_80031574(b[4], b[0]);
    }
}

void sub_800C1190(int a, int b)
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D60C);
    if (a > 0 && e)
    {
        int* q;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        q = e->buffer;
        q[1] = a;
        *(short*)(q + 2) = SfxKeyOn_800314F4(b);
        q[0] = b;
        e->cb_8 = (EventEntryFn)sub_800C1140;
    }
}

typedef struct BatDrop_a
{
    int f0;
    int f4;
    short size_8;
    short padA;
    int padC;
    int pos_10[3];
    char pad1C[0xC];
    int vel_28[3];
    short rot_34[4];
    int pad3C;
    int* anim_40;
} BatDrop_a;

// Matched
void sub_800C1220(EventEntry* t, BatDrop_a* u)
{
    int v[3];
    short s[4];
    short w[4];
    int* d;
    char* e;
    u->vel_28[0] = u->vel_28[0] * 15 / 16;
    u->vel_28[1] = u->vel_28[1] * 15 / 16 + u->size_8 / 8;
    u->vel_28[2] = u->vel_28[2] * 15 / 16;
    u->pos_10[0] += u->vel_28[0];
    u->pos_10[1] += u->vel_28[1];
    u->pos_10[2] += u->vel_28[2];
    d = u->anim_40;
    e = ((char**)d[2])[0];
    v[0] = u->pos_10[0];
    v[1] = u->pos_10[1];
    v[2] = u->pos_10[2];
    v[0] /= 1024;
    v[1] /= 1024;
    v[2] /= 1024;
    if (((int*)levantPos_8008BD18)[1] < v[1] || u->size_8 < 0x800)
    {
        t->flags = (t->flags & ~1) | 0x8000;
    }
    u->size_8 -= 0x40;
    s[0] = *(short*)(e + 0xC) * u->size_8 / 4096;
    s[1] = *(short*)(e + 0xE) * u->size_8 / 4096;
    w[0] = 0x14;
    w[1] = 0;
    w[2] = 0;
    u->rot_34[1] += 0x80;
    sub_80044010(&d[3], v, u->rot_34, e, e + 4, e + 8, s, w, e + 0x18, 0, 0x30, pOT_8008D690);
}

INCLUDE_OVERLAY_ASM(battle, sub_800C1450);

void sub_800C1654(int* p, short* q, int c, int d, int e, int f)
{
    int i;
    for (i = 0; i < 30; i++)
    {
        EventEntry* ev = AllocEventEntry_80043AF8(dword_8008D60C);
        if (ev)
        {
            char* b = ev->buffer;
            ev->flags = (ev->flags | 1) & 0xFFFF7FFF;
            *(int*)(b + 0x1C) = p[0];
            *(int*)(b + 0x20) = p[1];
            *(int*)(b + 0x24) = p[2];
            *(int*)(b + 0x10) = p[0];
            *(int*)(b + 0x14) = p[1];
            *(int*)(b + 0x18) = p[2];
            *(short*)(b + 0x34) = q[0];
            *(short*)(b + 0x36) = q[1];
            *(short*)(b + 0x38) = q[2];
            *(int*)(b + 0x3C) = c;
            *(int*)(b + 0x28) = ((rand() & 0x7F) - 0x3F) << 10;
            *(int*)(b + 0x2C) = -(rand() & 0x3F) << 10;
            *(int*)(b + 0x30) = ((rand() & 0x7F) - 0x3F) << 10;
            *(short*)(b + 0x34) = 0;
            *(short*)(b + 0x36) = 0;
            *(short*)(b + 0x38) = 0;
            *(int*)b = 0;
            *(short*)(b + 8) = ((rand() & 0xFFF) >> 1) + 0x800;
            *(int*)(b + 0x40) = e;
            *(int*)(b + 0x44) = f;
            ev->cb_8 = (EventEntryFn)sub_800C17EC;
        }
    }
}

void sub_800C17EC(EventEntry* t, BatSpark_a* u)
{
    int s[3];
    int* d;
    int i;
    char* e;
    int* a = u->target_40;
    int* b = u->offset_44;
    u->vel_28[0] = u->vel_28[0] * 31 / 32 + ((a[0] + b[0] - u->pos_10[0]) << 5);
    u->vel_28[1] = u->vel_28[1] * 31 / 32 + ((a[1] + b[1] - u->pos_10[1]) << 5);
    u->vel_28[2] = u->vel_28[2] * 31 / 32 + ((a[2] + b[2] - u->pos_10[2]) << 5);
    s[0] = u->vel_28[0] / 1024;
    s[1] = u->vel_28[1] / 1024;
    s[2] = u->vel_28[2] / 1024;
    u->pos_10[0] += s[0];
    u->pos_10[1] += s[1];
    u->pos_10[2] += s[2];
    d = u->anim_3C;
    if (u->frame_0 / 4096 < d[0])
    {
        for (i = 0; i < ((unsigned char*)d[1])[u->frame_0 / 4096]; i++)
        {
            e = ((char**)d[2])[u->frame_0 / 4096] + i * 0x1C;
            sub_80044010(&d[3], u->pos_10, u->rot_34, e, e + 4, e + 8, e + 0xC, (int*)dword_800795D4, e + 0x18, 0, 0x30, pOT_8008D690);
        }
        u->frame_0 += u->speed_8;
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
    }
}

void sub_800C1A5C(int* p, short* q, int c, int d)
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D60C);
    if (e)
    {
        char* b;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        b = e->buffer;
        *(int*)(b + 0x10) = p[0];
        *(int*)(b + 0x14) = p[1];
        *(int*)(b + 0x18) = p[2];
        *(short*)(b + 0x34) = q[0];
        *(short*)(b + 0x36) = q[1];
        *(short*)(b + 0x38) = q[2];
        *(int*)(b + 0x3C) = c;
        *(int*)b = 0;
        *(short*)(b + 8) = d;
        e->cb_8 = (EventEntryFn)sub_800C1B2C;
    }
}

#if 0 // Not matched: register permutation only (u/d/offset get s2/s0/s1, original s0/s1/s2); tried decl order and an explicit offset counter
typedef struct BatFx_a
{
    int frame_0;
    int f4;
    short speed_8;
    short padA;
    int padC;
    int pos_10[3];
    char pad1C[0x18];
    short rot_34[4];
    int* anim_3C;
} BatFx_a;
extern void sub_80044010();
void sub_800C1B2C(EventEntry* t, BatFx_a* u)
{
    int* d = u->anim_3C;
    int i;
    char* e;
    if (u->frame_0 / 4096 < d[0])
    {
        for (i = 0; i < ((unsigned char*)d[1])[u->frame_0 / 4096]; i++)
        {
            e = ((char**)d[2])[u->frame_0 / 4096] + i * 0x1C;
            sub_80044010(&d[3], u->pos_10, u->rot_34, e, e + 4, e + 8, e + 0xC, e + 0x10, e + 0x18, 0, 0x30, pOT_8008D690);
        }
        u->frame_0 += u->speed_8;
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
    }
}
#endif

INCLUDE_OVERLAY_ASM(battle, sub_800C1B2C);

void sub_800C1C5C(int* p, short* q, int c)
{
    int i;
    for (i = 0; i < 16; i++)
    {
        EventEntry* e = AllocEventEntry_80043AF8(dword_8008D60C);
        if (e)
        {
            char* b = e->buffer;
            e->flags = (e->flags | 1) & 0xFFFF7FFF;
            *(int*)(b + 0x10) = p[0];
            *(int*)(b + 0x14) = p[1];
            *(int*)(b + 0x18) = p[2];
            *(short*)(b + 0x34) = q[0];
            *(short*)(b + 0x36) = q[1];
            *(short*)(b + 0x38) = q[2];
            *(int*)(b + 0x3C) = c;
            *(int*)(b + 0x28) = ((rand() & 0x3F) - 0x1F) << 10;
            *(int*)(b + 0x2C) = ((rand() & 0x3F) - 0x1F) << 10;
            *(int*)(b + 0x30) = ((rand() & 0x3F) - 0x1F) << 10;
            *(int*)b = 0;
            *(short*)(b + 8) = ((rand() & 0xFFF) >> 1) + 0x800;
            e->cb_8 = (EventEntryFn)sub_800C1DA4;
        }
    }
}

void sub_800C1DA4(EventEntry* t, BatSpark_a* u)
{
    int s[3];
    int* d;
    int i;
    char* e;
    int* sd;
    u->vel_28[0] = u->vel_28[0] * 15 / 16;
    u->vel_28[1] = u->vel_28[1] * 15 / 16 + 0x200;
    u->vel_28[2] = u->vel_28[2] * 15 / 16;
    s[0] = u->vel_28[0] / 1024;
    s[1] = u->vel_28[1] / 1024;
    s[2] = u->vel_28[2] / 1024;
    u->pos_10[0] += s[0];
    u->pos_10[1] += s[1];
    u->pos_10[2] += s[2];
    sd = (int*)&saveData_8008B570;
    if (u->pos_10[1] > sd[0x7AC / 4])
    {
        u->vel_28[1] = -u->vel_28[1];
        u->pos_10[1] = sd[0x7AC / 4];
    }
    d = u->anim_3C;
    if (u->frame_0 / 4096 < d[0])
    {
        for (i = 0; i < ((unsigned char*)d[1])[u->frame_0 / 4096]; i++)
        {
            e = ((char**)d[2])[u->frame_0 / 4096] + i * 0x1C;
            sub_80044010(&d[3], u->pos_10, u->rot_34, e, e + 4, e + 8, e + 0xC, e + 0x10, e + 0x18, 0, 0x30, pOT_8008D690);
        }
        u->frame_0 += u->speed_8;
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
    }
}

void sub_800C1FFC(int* p, short* q, int c, int d, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        EventEntry* e = AllocEventEntry_80043AF8(dword_8008D60C);
        if (e)
        {
            char* b = e->buffer;
            e->flags = (e->flags | 1) & 0xFFFF7FFF;
            *(int*)(b + 0x1C) = p[0];
            *(int*)(b + 0x20) = p[1];
            *(int*)(b + 0x24) = p[2];
            *(short*)(b + 0x34) = q[0];
            *(short*)(b + 0x36) = q[1];
            *(short*)(b + 0x38) = q[2];
            *(int*)(b + 0x3C) = c;
            *(int*)(b + 0x28) = ((rand() & 0x3F) - 0x1F) << 10;
            *(int*)(b + 0x2C) = -(rand() & 0x1F) << 10;
            *(int*)(b + 0x30) = ((rand() & 0x3F) - 0x1F) << 10;
            *(int*)(b + 0x10) = 0;
            *(int*)(b + 0x14) = 0;
            *(int*)(b + 0x18) = 0;
            *(int*)b = 0;
            *(short*)(b + 8) = d + ((rand() & 0xFFF) >> 1) + 0x800;
            e->cb_8 = (EventEntryFn)sub_800C2170;
        }
    }
}

void sub_800C2170(EventEntry* t, BatSpark_a* u)
{
    int* d;
    int i;
    char* e;
    u->rot_34[1] += 0x40;
    u->vel_28[0] = u->vel_28[0] * 12 / 13;
    u->vel_28[1] = u->vel_28[1] * 12 / 13 - 0x400;
    u->vel_28[2] = u->vel_28[2] * 12 / 13;
    {
        int s[3];
        s[0] = u->vel_28[0] / 1024;
        s[1] = u->vel_28[1] / 1024;
        s[2] = u->vel_28[2] / 1024;
        u->pos_10[0] += s[0];
        u->pos_10[1] += s[1];
        u->pos_10[2] += s[2];
    }
    d = u->anim_3C;
    if (u->frame_0 / 4096 < d[0])
    {
        for (i = 0; i < ((unsigned char*)d[1])[u->frame_0 / 4096]; i++)
        {
            short c[3];
            e = ((char**)d[2])[u->frame_0 / 4096] + i * 0x1C;
            c[0] = u->pos_10[0];
            c[1] = u->pos_10[1];
            c[2] = u->pos_10[2];
            sub_80044010(&d[3], u->base_1C, u->rot_34, e, e + 4, e + 8, e + 0xC, c, e + 0x18, 0, 0x30, pOT_8008D690);
        }
        u->frame_0 += u->speed_8;
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
    }
}

#if 0 // Not matched: only u and the hoisted sinTable base swap saved registers (s5/s6); tried decl order, explicit table pointer, early return, temp for the first lookup
void sub_800C23D0(EventEntry* t, BatSpark_a* u)
{
    int i;
    int a;
    int k;
    int n;
    EventEntry* e;
    BatShard_a* b;
    if (++u->frame_0 >= 30)
    {
        PlaySfx_80031494(0x4F);
        sub_800C1A5C(u->pos_10, (short*)dword_800795D4, effectFile_80091BD0[0x20 / 4] + sub_80020F00(effectFile_80091BD0, 0, 0x21) * 52, 0x1000);
        for (i = 0; i < 24; i++)
        {
            e = AllocEventEntry_80043AF8(dword_8008D60C);
            if (e)
            {
                b = e->buffer;
                b->base_1C[0] = u->pos_10[0];
                b->base_1C[1] = u->pos_10[1];
                b->base_1C[2] = u->pos_10[2];
                b->frame_0 = 0;
                b->scale_C = (rand() & 0x7FF) + 0x800;
                b->pos_10[0] = 0;
                b->pos_10[1] = 0;
                b->pos_10[2] = 0;
                a = (i << 12) / 24;
                b->vel_28[0] = ((rand() & 0x1F) + 0x28) * sinTable_80084540[a & 0xFFF] / 4096;
                b->vel_28[2] = ((rand() & 0x1F) + 0x28) * sinTable_80084540[(a + 0x400) & 0xFFF] / 4096;
                k = rand() & 0x1FF;
                a = k + 0x200;
                b->vel_28[1] = -((rand() & 0x1F) + 0x28) * sinTable_80084540[a] / 4096;
                b->vel_28[0] = b->vel_28[0] * sinTable_80084540[k | 0x600] / 4096;
                b->vel_28[2] = b->vel_28[2] * sinTable_80084540[k | 0x600] / 4096;
                b->vel_28[0] <<= 10;
                b->vel_28[1] <<= 10;
                b->vel_28[2] <<= 10;
                b->rot_34[0] = rand() & 0x1000;
                b->rot_34[1] = rand() & 0x1000;
                b->rot_34[2] = rand() & 0x1000;
                b->rot_34[3] = (rand() & 0x1FF) + 0x100;
                n = sub_80020F00(effectFile_80091BD0, 1, 0x19);
                e->flags = (e->flags | 1) & 0xFFFF7FFF;
                {
                    int* ent = (int*)(effectFile_80091BD0[0x28 / 4] + n * 28);
                    b->anim_3C = (int*)(ent[1] + (i % 8) * 84);
                }
                e->cb_8 = (EventEntryFn)sub_800C273C;
            }
        }
        t->flags = (t->flags & ~1) | 0x8000;
    }
}
#endif

INCLUDE_OVERLAY_ASM(battle, sub_800C23D0);

void sub_800C273C(EventEntry* t, BatShard_a* u)
{
    int v[4];
    int s[3];
    u->vel_28[1] += 0x1000;
    u->vel_28[0] = u->vel_28[0] * 31 / 32;
    u->vel_28[1] = u->vel_28[1] * 31 / 32;
    u->vel_28[2] = u->vel_28[2] * 31 / 32;
    u->pos_10[0] += u->vel_28[0];
    u->pos_10[1] += u->vel_28[1];
    u->pos_10[2] += u->vel_28[2];
    if (u->pos_10[1] > 0)
    {
        u->vel_28[1] = -u->vel_28[1] * 3 / 4;
        u->pos_10[1] = 0;
        if (u->vel_28[1] >= -0xFFF)
        {
            t->flags = (t->flags & ~1) | 0x8000;
        }
    }
    u->rot_34[2] += u->rot_34[3];
    s[0] = s[1] = s[2] = u->scale_C;
    v[0] = u->base_1C[0] + u->pos_10[0] / 1024;
    v[1] = u->base_1C[1] + u->pos_10[1] / 1024;
    v[2] = u->base_1C[2] + u->pos_10[2] / 1024;
    sub_8004D1EC((int)u->anim_3C, (int)pOT_8008D690, (int)v, (int)u->rot_34, (int)stru_8008D534, 0x30, (int)s);
    u->frame_0++;
}

void sub_800C2914(BatSrc_a* p, int id)
{
    EventEntry* e;
    BatShard_a* b;
    int i;
    int a;
    int n;
    int s[3];
    e = AllocEventEntry_80043AF8(dword_8008D60C);
    if (e)
    {
        b = e->buffer;
        b->pos_10[0] = p->pos_1C[0];
        b->pos_10[1] = p->pos_1C[1];
        b->pos_10[2] = p->pos_1C[2];
        b->frame_0 = 0;
        n = sub_80020F00(effectFile_80091BD0, 1, id);
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        b->anim_3C = (int*)(effectFile_80091BD0[0x28 / 4] + n * 28);
        e->cb_8 = (EventEntryFn)sub_800C23D0;
    }
    for (i = 0; i < 8; i++)
    {
        e = AllocEventEntry_80043AF8(dword_8008D60C);
        if (e)
        {
            b = e->buffer;
            b->base_1C[0] = p->pos_1C[0];
            b->base_1C[1] = p->pos_1C[1];
            b->base_1C[2] = p->pos_1C[2];
            b->frame_0 = 0;
            b->scale_C = (rand() & 0x7FF) + 0x800;
            a = i << 9;
            b->pos_10[0] = sinTable_80084540[a & 0xFFF] * 300 / 4096;
            b->pos_10[2] = sinTable_80084540[(a + 0x400) & 0xFFF] * 300 / 4096;
            a = rand() & 0x3FF;
            b->pos_10[1] = -(sinTable_80084540[a] * 300) / 4096;
            b->pos_10[0] = b->pos_10[0] * sinTable_80084540[(a + 0x400) & 0xFFF] / 4096;
            b->pos_10[2] = b->pos_10[2] * sinTable_80084540[(a + 0x400) & 0xFFF] / 4096;
            b->pos_10[0] <<= 10;
            b->pos_10[1] <<= 10;
            b->pos_10[2] <<= 10;
            b->vel_28[0] = -b->pos_10[0] / 4;
            b->vel_28[1] = -b->pos_10[1] / 4;
            b->vel_28[2] = -b->pos_10[2] / 4;
            s[0] = b->vel_28[0] / 1024;
            s[1] = b->vel_28[1] / 1024;
            s[2] = b->vel_28[2] / 1024;
            VectorToAngles_8003B5D4(s, b->rot_34);
            b->rot_34[2] = rand() & 0x1000;
            n = sub_80020F00(effectFile_80091BD0, 1, id);
            e->flags = (e->flags | 1) & 0xFFFF7FFF;
            b->anim_3C = (int*)(effectFile_80091BD0[0x28 / 4] + n * 28);
            e->cb_8 = (EventEntryFn)sub_800C2CD8;
        }
    }
}

void sub_800C2CD8(EventEntry* t, BatShard_a* u)
{
    int* d = u->anim_3C;
    int v[4];
    int s[3];
    if (u->frame_0 >= 0x1A)
    {
        if (u->frame_0 < 0x1E)
        {
            u->pos_10[0] += u->vel_28[0];
            u->pos_10[1] += u->vel_28[1];
            u->pos_10[2] += u->vel_28[2];
        }
        else
        {
            t->flags = (t->flags & ~1) | 0x8000;
        }
    }
    u->rot_34[2] += 0xAA;
    s[0] = s[1] = s[2] = u->scale_C;
    v[0] = u->base_1C[0] + u->pos_10[0] / 1024;
    v[1] = u->base_1C[1] + u->pos_10[1] / 1024;
    v[2] = u->base_1C[2] + u->pos_10[2] / 1024;
    sub_8004D1EC(d[1], (int)pOT_8008D690, (int)v, (int)u->rot_34, (int)stru_8008D534, 0x30, (int)s);
    u->frame_0++;
}

void sub_800C2E28(int* p, short* q, int c, int d, int e, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        EventEntry* ev = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
        if (ev)
        {
            char* b;
            ev->flags = (ev->flags | 1) & 0xFFFF7FFF;
            b = ev->buffer;
            *(int*)(b + 0x44) = p[0];
            *(int*)(b + 0x48) = p[1];
            *(int*)(b + 0x4C) = p[2];
            *(int*)(b + 0x50) = p[0];
            *(int*)(b + 0x54) = p[1];
            *(int*)(b + 0x58) = p[2];
            *(int*)(b + 0x5C) = p[0];
            *(int*)(b + 0x60) = p[1];
            *(int*)(b + 0x64) = p[2];
            *(int*)(b + 0x68) = p[0];
            *(int*)(b + 0x6C) = p[1];
            *(int*)(b + 0x70) = p[2];
            *(short*)(b + 0x80) = q[0];
            *(short*)(b + 0x82) = q[1];
            *(short*)(b + 0x84) = q[2];
            *(int*)(b + 0x88) = c;
            *(int*)(b + 0x8C) = d;
            *(short*)(b + 0x80) = 0;
            *(short*)(b + 0x84) = 0;
            *(int*)b = 0;
            *(int*)(b + 4) = 0;
            *(short*)(b + 8) = e;
            *(short*)(b + 0x82) = (i << 12) / n;
            ev->cb_8 = (EventEntryFn)sub_800C2FC8;
        }
    }
}

void sub_800C2FC8(EventEntry* t, BatTrail_a* u)
{
    int* d = u->anim_88;
    int i;
    int* r;
    char* e;
    if (u->frame_0 / 4096 < d[0])
    {
        r = 0;
        for (i = 0; i < ((unsigned char*)d[1])[u->frame_0 / 4096]; i++)
        {
            e = ((char**)d[2])[u->frame_0 / 4096] + i * 0x1C;
            r = sub_80044010(&d[3], u->pos_44, u->rot_80, e, e + 4, e + 8, e + 0xC, e + 0x10, e + 0x18, 0, 0x30, pOT_8008D690);
        }
        u->trail_50[0].x = u->pos_44[0] + r[0];
        u->trail_50[0].y = u->pos_44[1] + r[1];
        u->trail_50[0].z = u->pos_44[2] + r[2];
        if (u->count_4 == 0)
        {
            u->trail_50[3].x = u->trail_50[0].x;
            u->trail_50[3].y = u->trail_50[0].y;
            u->trail_50[3].z = u->trail_50[0].z;
            u->trail_50[2].x = u->trail_50[0].x;
            u->trail_50[2].y = u->trail_50[0].y;
            u->trail_50[2].z = u->trail_50[0].z;
            u->trail_50[1].x = u->trail_50[0].x;
            u->trail_50[1].y = u->trail_50[0].y;
            u->trail_50[1].z = u->trail_50[0].z;
        }
        u->frame_0 += u->speed_8;
        sub_80044D0C(u->model_8C[1], pOT_8008D690, &u->trail_50[0], u->rot_80, stru_8008D534, 0x30, 0, 0);
        sub_80044D0C(u->model_8C[1] + 0x54, pOT_8008D690, &u->trail_50[1], u->rot_80, stru_8008D534, 0x30, 0, 1);
        sub_80044D0C(u->model_8C[1] + 0xA8, pOT_8008D690, &u->trail_50[2], u->rot_80, stru_8008D534, 0x30, 0, 2);
        sub_80044D0C(u->model_8C[1] + 0xFC, pOT_8008D690, &u->trail_50[3], u->rot_80, stru_8008D534, 0x30, 0, 3);
        sub_800459E4(dword_800C91A4, u->model_8C + 2, pOT_8008D690, 0x30);
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
    }
    if (++u->count_4 & 1)
    {
        u->trail_50[3].x = u->trail_50[2].x;
        u->trail_50[3].y = u->trail_50[2].y;
        u->trail_50[3].z = u->trail_50[2].z;
        u->trail_50[2].x = u->trail_50[1].x;
        u->trail_50[2].y = u->trail_50[1].y;
        u->trail_50[2].z = u->trail_50[1].z;
        u->trail_50[1].x = u->trail_50[0].x;
        u->trail_50[1].y = u->trail_50[0].y;
        u->trail_50[1].z = u->trail_50[0].z;
    }
}

int sub_800C32DC(int a0, int a1, int a2, int a3)
{
    int* pos = (int*)a0;
    EventEntry* e = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    char* b;
    int idx;
    int t;
    if (e != 0)
    {
    b = e->buffer;
    *(int*)(b + 0x44) = pos[0];
    *(int*)(b + 0x48) = pos[1];
    *(int*)(b + 0x4C) = pos[2];
    *(int*)b = 0;
    *(short*)(b + 8) = 0;
    *(short*)(b + 0x82) = a3;
    idx = sub_80020F00(effectFile_80091BD0, 1, a1);
    e->flags = (e->flags | 1) & 0xFFFF7FFF;
    t = effectFile_80091BD0[0x28 / 4] + idx * 28;
    *(int*)(b + 0x88) = t + a2 * 28;
    e->cb_8 = (EventEntryFn)sub_800C33E4;
    return *(int*)(t + 0x14);
    }
    return -1;
}

#if 0 // Not matched: only u and c swap saved registers (s1/s2); tried decl/init order, early return, tail shapes, pointer arithmetic
void sub_800C33E4(EventEntry* t, BatAnim_a* u)
{
    BatClip_a* c = u->clip_88;
    int any;
    int i;
    BatKey_a* k;
    int v[3];
    short r[3];
    any = 0;
    if (u->frame_0 < c->frames_14)
    {
        for (i = 0; i < c->count_10; i++)
        {
            k = &c->keys_18[i + u->frame_0 * c->count_10];
            if (k->model_0 >= 0)
            {
                r[0] = k->rot_10[0];
                r[1] = k->rot_10[1];
                r[2] = k->rot_10[2];
                r[1] += u->rot_82;
                v[0] = u->pos_44[0] + k->x_4 * sinTable_80084540[(u->rot_82 + 0x400) & 0xFFF] / 4096 + k->z_C * sinTable_80084540[u->rot_82 & 0xFFF] / 4096;
                v[1] = u->pos_44[1] + k->y_8;
                v[2] = u->pos_44[2] - k->x_4 * sinTable_80084540[u->rot_82 & 0xFFF] / 4096 + k->z_C * sinTable_80084540[(u->rot_82 + 0x400) & 0xFFF] / 4096;
                sub_80044D0C(c->models_4 + k->model_0 * 84, pOT_8008D690, v, r, stru_8008D534, (0x1000 - k->alpha_2) << 16 | 0x80 | k->mode_24, k->f18, i);
                if (*(int*)(c->models_4 + k->model_0 * 84 + 0x48))
                {
                    any = 1;
                }
            }
        }
        u->frame_0++;
        if (any)
        {
            if (c->f8)
            {
                sub_800459E4(dword_800C91A4, &c->f8, pOT_8008D690, 0x30);
            }
        }
        else if (c->f8)
        {
            sub_80045E48(&c->f8, pOT_8008D690, 0x30);
        }
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
    }
}
#endif

INCLUDE_OVERLAY_ASM(battle, sub_800C33E4);

void sub_800C371C(EventEntry* t, void* arg)
{
    unsigned char col[4] = { 0xE8, 0xE8, 0x80, 0 };
    BatGlow_a* u = arg;
    int* m = u->f88;
    if (u->frame_0 < u->end_4 && effectOutcomeFlag_8008D780 == 0)
    {
        int s[4];
        int v[4];
        int a;
        u->f30 += 0x100;
        if (u->f30 > 0x1000)
        {
            u->f30 = 0x1000;
        }
        s[0] = u->scale_A0[0] * 3 / 2;
        s[1] = u->scale_A0[1] * 3 / 2;
        s[2] = u->scale_A0[2] * 3 / 2;
        a = u->f30;
        v[0] = u->path_20[u->idx_98 * 3 + 0] + u->base_1C[0];
        v[1] = u->path_20[u->idx_98 * 3 + 1] + u->base_1C[1];
        v[2] = u->path_20[u->idx_98 * 3 + 2] + u->base_1C[2];
        sub_8003A6C4(a, m[1], m[1] + 0x54, u->f94);
        sub_8004D1EC(m[1], (int)pOT_8008D690, (int)v, (int)dword_800795D4, (int)stru_8008D534, ((0x1000 - a) << 16) | 0xB0, (int)s);
        sub_800C4090((int)u->f44, (int)col, 0x5DC, u->f30);
        u->frame_0++;
    }
    else
    {
        int s[4];
        int v[4];
        int a;
        s[0] = u->scale_A0[0] * 3 / 2;
        s[1] = u->scale_A0[1] * 3 / 2;
        s[2] = u->scale_A0[2] * 3 / 2;
        a = u->f30;
        v[0] = u->path_20[u->idx_98 * 3 + 0] + u->base_1C[0];
        v[1] = u->path_20[u->idx_98 * 3 + 1] + u->base_1C[1];
        v[2] = u->path_20[u->idx_98 * 3 + 2] + u->base_1C[2];
        sub_8003A6C4(a, m[1], m[1] + 0x54, u->f94);
        sub_8004D1EC(m[1], (int)pOT_8008D690, (int)v, (int)dword_800795D4, (int)stru_8008D534, ((0x1000 - a) << 16) | 0xB0, (int)s);
        if (u->f30 == 0x1000)
        {
            sub_800C3B50(v, 0x25);
        }
        sub_800C4090((int)u->f44, (int)col, 0x5DC, u->f30);
        if (u->f30 <= 0)
        {
            sub_800C410C();
            sub_80021804(u->f94, 1);
            free3_8003FC6C(u->f94);
            t->flags = (t->flags & ~1) | 0x8000;
        }
        u->f30 -= 0x100;
    }
}


#if 0 // Not matched: regalloc only: the 0xFFFF7FFF mask and the effect-file base swap saved registers (orig s0/s3); body and schedule otherwise match
extern char* dword_8008B4A4;
extern void PlaySfx_80031494(int id);
extern void sub_800C3DF8();
extern void sub_800C3D34();
void sub_800C3B50(int* p, int id)
{
    EventEntry* e = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    char* b;
    int* ent;
    int* q;
    int f;
    int idx;
    if (e == 0)
    {
        return;
    }
    b = e->buffer;
    *(int*)(b + 0x44) = p[0];
    *(int*)(b + 0x48) = p[1];
    *(int*)(b + 0x4C) = p[2];
    *(int*)b = 0;
    *(short*)(b + 0xE) = sub_80020F00(effectFile_80091BD0, 0, id);
    *(int*)(b + 0x30) = 0x1000;
    *(int*)(b + 0x34) = 0;
    *(short*)(b + 0x84) = 0;
    *(short*)(b + 0x82) = 0;
    *(short*)(b + 0x80) = 0;
    *(int*)(b + 0x38) = 0;
    *(int*)(b + 0x3C) = -0xC8;
    *(int*)(b + 0x40) = 0;
    f = (&effectOutcomeFlag_8008D780)[1];
    e->flags = (e->flags | 1) & 0xFFFF7FFF;
    if (f == 0)
    {
    idx = sub_80020F00(effectFile_80091BD0, 1, 0x1F);
    e->flags = (e->flags | 1) & 0xFFFF7FFF;
    ent = (int*)(effectFile_80091BD0[0x28 / 4] + idx * 28);
    *(int**)(b + 0x88) = ent;
    *(void**)(b + 0x94) = malloc3_8003FC4C(0x54);
    sub_800218A8(ent[1], *(void**)(b + 0x94), 1);
    sub_80039FE4(ent[1], ent[1] + 0x54, *(int*)(b + 0x94));
    q = *(int**)(dword_8008B4A4 + 0x24);
    *(int*)(b + 0x44) = q[0x5E4 / 4];
    *(int*)(b + 0x48) = q[0x5E8 / 4];
    *(int*)(b + 0x4C) = q[0x5EC / 4];
    *(int*)(b + 0x44) += ((int*)levantPos_8008BD18)[0];
    *(int*)(b + 0x48) += ((int*)levantPos_8008BD18)[1];
    *(int*)(b + 0x4C) += ((int*)levantPos_8008BD18)[2];
    e->cb_8 = (EventEntryFn)sub_800C3D34;
    PlaySfx_80031494(0x3F);
    }
    else
    {
        PlaySfx_80031494(0x47);
        e->cb_8 = (EventEntryFn)sub_800C3DF8;
    }
}
#endif

INCLUDE_OVERLAY_ASM(battle, sub_800C3B50);

void sub_800C3D34(EventEntry* t, BatFade_a* u)
{
    int* m = u->f88;
    int v = u->f30 - 0x100;
    u->f30 = v;
    if (v > 0)
    {
        sub_8003A6C4(v, m[1], m[1] + 0x54, u->f94);
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
        sub_80021804(u->f94, 1);
        free3_8003FC6C(u->f94);
    }
    sub_8004D1EC(m[1], (int)pOT_8008D690, (int)u->f44, (int)u->f80, (int)stru_8008D534, ((0x1000 - u->f30) << 16) | 0xB0, 0);
}

void sub_800C3DF8(EventEntry* t, BatOrb_a* u)
{
    int v[3];
    int* q;
    BatOrb_a* w;
    w = u;
    sub_800C1A5C(u->pos_44, (short*)dword_800795D4, effectFile_80091BD0[0x20 / 4] + u->fx_E * 52, 0x1000);
    q = *(int**)(dword_8008B4A4 + 0x24);
    v[0] = q[0x5E4 / 4];
    v[1] = q[0x5E8 / 4];
    v[2] = q[0x5EC / 4];
    v[0] += ((int*)levantPos_8008BD18)[0];
    v[1] += ((int*)levantPos_8008BD18)[1];
    v[2] += ((int*)levantPos_8008BD18)[2];
    if (DistanceSquared3D_8003B80C(v, u->pos_44) >= 0x57E5)
    {
        u->vel_38[0] += ((v[0] - u->pos_44[0]) << 10) / 70;
        u->vel_38[1] += ((v[1] - u->pos_44[1]) << 10) / 70;
        u->vel_38[2] += ((v[2] - u->pos_44[2]) << 10) / 70;
        u->vel_38[0] = u->vel_38[0] * 31 / 32;
        u->vel_38[1] = u->vel_38[1] * 31 / 32;
        u->vel_38[2] = u->vel_38[2] * 31 / 32;
        u->pos_44[0] += u->vel_38[0] / 1024;
        u->pos_44[1] += u->vel_38[1] / 1024;
        u->pos_44[2] += u->vel_38[2] / 1024;
    }
    else
    {
        ((void (*)())sub_800C1C5C)(v, dword_800795D4, effectFile_80091BD0[0x20 / 4] + w->fx_E * 52, 0x1000);
        t->flags = (t->flags & ~1) | 0x8000;
    }
}

void sub_800C4090(int a0, int a1, int c, int a3)
{
    int* a = (int*)a0;
    unsigned char* b = (unsigned char*)a1;
    unsigned int d = a3;
    dword_8008D680[0] = a[0];
    dword_8008D680[1] = a[1];
    dword_8008D680[2] = a[2];
    dword_8008D3F0 = c;
    dword_8008D418[0] = b[0] * d >> 7;
    dword_8008D418[1] = b[1] * d >> 7;
    dword_8008D418[2] = b[2] * d >> 7;
}

void sub_800C410C()
{
    dword_8008D3F0 = 0;
}

typedef void (*BatFxFn)(BatTask* t);
extern BatFxFn dword_800C91DC[];
extern BatFxFn dword_800C9204[];
extern int sub_800C4A40(BatTask* t);
extern void sub_800C5BC0(BatTask* t);
extern void sub_800C59A0(BatTask* t);
extern void sub_800C58BC(BatTask* t);
extern void sub_800C5EB8(BatTask* t);
extern void sub_800C6038(BatTask* t);
extern void sub_800C5D04(BatTask* t);
extern void sub_800C61FC(BatTask* t);
extern void sub_800C66F4(BatTask* t);
extern void sub_800C6824(BatTask* t);
extern void sub_800C6928(BatTask* t);
extern void sub_800C6A40(BatTask* t);
void sub_800C5A7C(BatTask* t);
void sub_800C58AC(BatTask* t);

// Matched
void sub_800C4118(int* a, char* b, int c, unsigned int d)
{
    BatTask t;
    unsigned int k;
    int r;
    k = *(unsigned int*)(b + 0x5C);
    t.f0 = (int)(b + 0x80);
    t.f4 = (int)(b + 0x6C);
    t.f8 = a;
    t.fC = c;
    t.f10 = (int)b;
    t.f1C = 4;
    r = sub_800C0D50();
    if (r >= 0)
    {
        t.f18 = 1 << (r + 1);
        t.f14 = (unsigned char*)GetMinionStatus_800107A0(3, r);
    }
    else
    {
        t.f18 = 1;
        t.f14 = (unsigned char*)levantStatus_8008BD38;
    }
    t.f8[2] = 1 << (c + 4);
    switch (d)
    {
    case 0:
        if (k < 0x39)
        {
            dword_800C9204[k](&t);
        }
        else if (k < 0xC9)
        {
            if (k - 0xBD < 4)
            {
                sub_800C4A40(&t);
            }
            sub_800C473C(&t);
            break;
        }
        else
        {
            k -= 0xC9;
            dword_800C91DC[k](&t);
        }
        break;
    case 2:
        sub_800C5A7C(&t);
        break;
    case 15:
        sub_800C66F4(&t);
        break;
    case 16:
        sub_800C6824(&t);
        break;
    case 17:
        sub_800C6928(&t);
        break;
    case 3:
        sub_800C5BC0(&t);
        break;
    case 4:
        sub_800C59A0(&t);
        break;
    case 10:
        sub_800C58BC(&t);
        break;
    case 11:
        sub_800C5EB8(&t);
        break;
    case 12:
        sub_800C6038(&t);
        break;
    case 13:
        sub_800C5D04(&t);
        break;
    case 14:
        sub_800C61FC(&t);
        break;
    case 7:
    case 8:
    case 9:
        sub_800C6A40(&t);
        break;
    default:
        sub_800C58AC(&t);
        break;
    }
}

void sub_800C4328(BatTask* t)
{
    Minion* s = (Minion*)t->f14;
    short x = sub_800334D8(s);
    short y = sub_800334CC(s);
    if (x < (short)(y / 10))
    {
        sub_800C6AFC(t, 6, 0);
    }
    else if (rand() & 1)
    {
        sub_800C6AFC(t, 6, 1);
    }
    else
    {
        sub_800C6AFC(t, 0, 0);
    }
}

void sub_800C43D8(BatTask* t)
{
    if (rand(t) & 1)
    {
        sub_800C6AFC(t, 1, 8);
    }
    else
    {
        sub_800C6AFC(t, 1, 6);
    }
}

void sub_800C4424(BatTask* t)
{
    if (rand(t) & 1)
    {
        sub_800C6AFC(t, 6, 2);
    }
    else
    {
        sub_800C6AFC(t, 0, 0);
    }
}

void sub_800C4470(int a)
{
    sub_800C6AFC(a, 1, 0x14);
}

void sub_800C4494(BatTask* t)
{
    int x = rand();
    if (x % 3)
    {
        sub_800C6AFC(t, 6, 3);
    }
    else
    {
        sub_800C6AFC(t, 0, 0);
    }
}

void sub_800C44FC(BatTask* t)
{
    if (rand(t) & 1)
    {
        sub_800C6AFC(t, 6, 1);
    }
    else
    {
        sub_800C6AFC(t, 6, 2);
    }
}

void sub_800C4548(BatTask* t)
{
    if (sub_800C6DF8(t, 0xD) == 0)
    {
        if (rand() & 1)
        {
            sub_800C6C44(t);
        }
        else
        {
            sub_800C6AFC(t, 0, 0);
        }
    }
}

void sub_800C45A8(BatTask* t)
{
    if (sub_800C6EC8(t, 0x3F8) == 0 && rand() % 10 < 7)
    {
        sub_800C6AFC(t, 6, 0);
    }
    else if (sub_800C6EC8(t, 2) == 0 && rand() % 10 < 7)
    {
        sub_800C6AFC(t, 6, 1);
    }
    else if (sub_800C6EC8(t, 1) == 0 && rand() % 10 < 7)
    {
        sub_800C6AFC(t, 6, 2);
    }
    else
    {
        sub_800C6A68(t);
    }
}

void sub_800C46FC()
{
    sub_800C473C();
}

void sub_800C471C()
{
    sub_800C473C();
}

int sub_800C473C(BatTask* t)
{
    unsigned char* s = (unsigned char*)t->f10;
    int r;
    int i;
    if ((sub_800BC868() == 0 || sub_800BC868() == -1) && (r = sub_800C6BD0(t, 0x16)))
    {
        return r;
    }
    if ((sub_800BC868() == 1 || sub_800BC868() == -1) && (r = sub_800C6BD0(t, 0x15)))
    {
        return r;
    }
    if ((sub_800BC868() == 2 || sub_800BC868() == -1) && (r = sub_800C6BD0(t, 0x18)))
    {
        return r;
    }
    if ((sub_800BC868() == 3 || sub_800BC868() == -1) && (r = sub_800C6BD0(t, 0x17)))
    {
        return r;
    }
    if (sub_800C6EC8(t, 0x3F8) == 0 && rand() % 10 < 7 && (r = sub_800C6BD0(t, 0x13)))
    {
        return r;
    }
    if (sub_800C6EC8(t, 2) == 0 && rand() % 10 < 7 && (r = sub_800C6BD0(t, 0x12)))
    {
        return r;
    }
    if (sub_800C6EC8(t, 1) == 0 && rand() % 10 < 7 && (r = sub_800C6BD0(t, 0x11)))
    {
        return r;
    }
    if ((rand() & 1) && (r = sub_800C6BD0(t, 0x14)))
    {
        return r;
    }
    if ((r = sub_800C6DF8(t, 0xD)))
    {
        return r;
    }
    if (s[0x2D] > s[0x2F])
    {
        if (rand() % 10 < 8 && (r = sub_800C6A8C(t)))
        {
            return r;
        }
    }
    else
    {
        for (i = 0; i < 12; i++)
        {
            if ((r = sub_800C6BD0(t, i)))
            {
                return r;
            }
        }
    }
    return sub_800C6A68(t);
}

int sub_800C4A40(BatTask* t)
{
    int r;
    if (rand() & 1)
    {
        if (sub_800C6EC8(t, 0x3F8) == 0)
        {
            r = sub_800C6BD0(t, 0x13);
        }
        else
        {
            r = sub_800C6A8C(t);
        }
        if (r)
        {
            return r;
        }
        if (sub_800C6EC8(t, 2) == 0)
        {
            r = sub_800C6BD0(t, 0x12);
        }
        else
        {
            r = sub_800C6A8C(t);
        }
        if (r)
        {
            return r;
        }
        if (sub_800C6EC8(t, 1) == 0)
        {
            r = sub_800C6BD0(t, 0x11);
        }
        else
        {
            r = sub_800C6A8C(t);
        }
        if (r)
        {
            return r;
        }
        r = sub_800C6BD0(t, 0x14);
        if (r == 0)
        {
            r = sub_800C6A8C(t);
        }
        return r;
    }
    return sub_800C6C58(t);
}

int sub_800C4B34(BatTask* t)
{
    int r;
    Minion* s = (Minion*)t->f10;
    short x = sub_800334D8(s);
    short y = sub_800334CC(s);
    if (x < (short)(y / 3))
    {
        r = sub_800C6A8C(t);
        if (r)
        {
            return r;
        }
        if (rand() & 1)
        {
            r = sub_800C6C44(t);
            if (r)
            {
                return r;
            }
        }
    }
    return sub_800C6A68(t);
}

int sub_800C4BE4(BatTask* t)
{
    int r;
    Minion* s = (Minion*)t->f10;
    r = sub_800C6DF8(t, 0xD);
    if (r)
    {
        return r;
    }
    {
        short x = sub_800334D8(s);
        short y = sub_800334CC(s);
        if (x < y)
        {
            if (rand() & 1)
            {
                r = sub_800C6C44(t);
                if (r)
                {
                    return r;
                }
            }
        }
    }
    return sub_800C6A68(t);
}

int sub_800C4C74(BatTask* t)
{
    int r;
    if (sub_800C6EC8(t, 1) == 0)
    {
        r = sub_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C4CBC(BatTask* t)
{
    int r;
    int m = rand() % 100;
    if (m < 30)
    {
        r = sub_800C6BD0(t, 0);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C4D38(BatTask* t)
{
    int r;
    Minion* s = (Minion*)t->f10;
    short x = sub_800334D8(s);
    short y = sub_800334CC(s);
    if (x < y / 4)
    {
        r = sub_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C4DB8(BatTask* t)
{
    int r;
    int m = rand() % 100;
    if (m < 50)
    {
        r = sub_800C6BD0(t, 9);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C4E34(BatTask* t)
{
    int r;
    if (rand() % 10 < 7)
    {
        r = sub_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C4EA8(BatTask* t)
{
    int r;
    int m = rand() % 100;
    if (dword_800C8B30 < 2)
    {
        if (sub_800C6EC8(t, 2) == 0 && m < 40)
        {
            r = sub_800C6BD0(t, 0x12);
            if (r)
            {
                return r;
            }
            dword_800C8B30++;
        }
        if (sub_800C6EC8(t, 2) == 0 && m < 40)
        {
            r = sub_800C6A8C(t);
            if (r)
            {
                return r;
            }
            dword_800C8B30++;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C4FA8(BatTask* t)
{
    int r = sub_800C6BD0(t, 4);
    if (r == 0)
    {
        r = sub_800C6A68(t);
    }
    return r;
}

int sub_800C4FE0(BatTask* t)
{
    int r;
    if (sub_800C6EE4(t))
    {
        r = sub_800C6BD0(t, 7);
        if (r)
        {
            return r;
        }
    }
    r = sub_800C6A8C(t);
    if (r)
    {
        return r;
    }
    return sub_800C6A68(t);
}

int sub_800C5034(BatTask* t)
{
    int r;
    if (sub_800C6EC8(t, 0x3F8) == 0)
    {
        r = sub_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C507C(BatTask* t)
{
    int r = sub_800C6A8C(t);
    if (r == 0)
    {
        r = sub_800C6A68(t);
    }
    return r;
}

int sub_800C50B0(BatTask* t)
{
    int r;
    Minion* s = (Minion*)t->f10;
    short x;
    short y;
    if (sub_800BC868() == 3 || sub_800BC868() == -1)
    {
        r = sub_800C6BD0(t, 0x17);
        if (r)
        {
            return r;
        }
    }
    if (rand() % 10 < 6)
    {
        r = sub_800C6BD0(t, 6);
        if (r)
        {
            return r;
        }
    }
    x = sub_800334D8(s);
    y = sub_800334CC(s);
    if (x <= (short)(y / 3) && (rand() & 1))
    {
        r = sub_800C6C58(t);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6C44(t);
}

int sub_800C51D8(BatTask* t)
{
    int r;
    if (rand(t) & 1)
    {
        r = sub_800C6A8C(t);
    }
    else
    {
        r = sub_800C6A68(t);
    }
    return r;
}

int sub_800C5220(BatTask* t)
{
    unsigned char* s = t->f14;
    int r = sub_800C6DF8(t, 0xD);
    if (r)
    {
        return r;
    }
    if ((short)sub_800334D8(s) != 1)
    {
        r = sub_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C5290(BatTask* t)
{
    int r;
    if (rand() % 10 < 6)
    {
        r = sub_800C6BD0(t, 2);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C5304(BatTask* t)
{
    int r;
    if (sub_800C6EC8(t, 1) == 0 && rand() % 10 < 7)
    {
        r = sub_800C6BD0(t, 0x11);
        if (r)
        {
            return r;
        }
    }
    if (rand() & 1)
    {
        r = sub_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C53B0(BatTask* t)
{
    int r;
    if (rand() % 10 < 6)
    {
        r = sub_800C6BD0(t, 5);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C5424(BatTask* t)
{
    int r;
    Minion* s = (Minion*)t->f10;
    short x = sub_800334D8(s);
    short y = sub_800334CC(s);
    if (x <= y / 2)
    {
        r = sub_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C54A4(BatTask* t)
{
    int r;
    if (sub_800BC868() == 1 || sub_800BC868() == -1)
    {
        r = sub_800C6BD0(t, 0x15);
        if (r)
        {
            return r;
        }
    }
    r = sub_800C6A8C(t);
    if (r)
    {
        return r;
    }
    return sub_800C6A68(t);
}

int sub_800C5510(BatTask* t)
{
    int r;
    if (sub_800C6BD0(t, 8) == 0)
    {
        return sub_800C6C58(t);
    }
    r = rand() & 1;
    if (r)
    {
        return r;
    }
    if (sub_800334F0((Minion*)t->f14) != 0)
    {
        r = sub_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    r = sub_800C6A68(t);
    if (r)
    {
        return r;
    }
    return sub_800C6C58(t);
}

int sub_800C5594(BatTask* t)
{
    int r;
    if (rand() % 10 < 7)
    {
        r = sub_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C5608(BatTask* t)
{
    int r;
    if (sub_800BC868() == 0 || sub_800BC868() == -1)
    {
        r = sub_800C6BD0(t, 0x16);
        if (r)
        {
            return r;
        }
    }
    r = sub_800C6A8C(t);
    if (r)
    {
        return r;
    }
    return sub_800C6A68(t);
}

int sub_800C5670(BatTask* t)
{
    int r;
    if (sub_800C6EC8(t, 0x3F8) == 0)
    {
        r = sub_800C6BD0(t, 0x13);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6C44(t);
}

int sub_800C56B8(BatTask* t)
{
    int r = sub_800C6BD0(t, 0xB);
    if (r)
    {
        return r;
    }
    r = sub_800C6A8C(t);
    if (r)
    {
        return r;
    }
    return sub_800C6A68(t);
}

int sub_800C5700(BatTask* t)
{
    int r;
    if (sub_800BC868() == 2 || sub_800BC868() == -1)
    {
        r = sub_800C6BD0(t, 0x18);
        if (r)
        {
            return r;
        }
    }
    r = sub_800C6A8C(t);
    if (r)
    {
        return r;
    }
    return sub_800C6A68(t);
}

int sub_800C576C(BatTask* t)
{
    int r;
    if (sub_800BC868() == 3 || sub_800BC868() == -1)
    {
        r = sub_800C6BD0(t, 0x17);
        if (r)
        {
            return r;
        }
    }
    r = sub_800C6A8C(t);
    if (r)
    {
        return r;
    }
    return sub_800C6A68(t);
}

int sub_800C57D8(BatTask* t)
{
    int r = sub_800C6A8C(t);
    if (r == 0)
    {
        r = sub_800C6A68(t);
    }
    return r;
}

int sub_800C580C(BatTask* t)
{
    int r = sub_800C6A8C(t);
    if (r == 0)
    {
        r = sub_800C6A68(t);
    }
    return r;
}

int sub_800C5840(BatTask* t)
{
    int r = sub_800C6A8C(t);
    if (r == 0)
    {
        r = sub_800C6A68(t);
    }
    return r;
}

int sub_800C5874(BatTask* t)
{
    int r = sub_800C6BD0(t, 0x14);
    if (r == 0)
    {
        r = sub_800C6A68(t);
    }
    return r;
}

void sub_800C58AC(BatTask* t)
{
    *t->f8 = 0x12;
}

void sub_800C58BC(BatTask* t)
{
    unsigned char k = dword_800C8B30 % 6;
    switch (k)
    {
    case 0:
        t->f8[0] = 6;
        t->f8[1] = 2;
        t->f8[3] = t->f18;
        break;
    case 2:
        t->f8[0] = 6;
        t->f8[1] = 3;
        t->f8[3] = t->f18;
        break;
    case 4:
        t->f8[0] = 6;
        t->f8[1] = 1;
        t->f8[3] = t->f18;
        break;
    case 1:
    case 3:
    case 5:
        t->f8[0] = 0;
        t->f8[3] = t->f18;
        break;
    }
    dword_800C8B30++;
}

INCLUDE_OVERLAY_ASM(battle, dword_800B68AC);

void sub_800C59A0(BatTask* t)
{
    unsigned char k = dword_800C8B30 % 3;
    switch (k)
    {
    case 0:
        t->f8[0] = 6;
        t->f8[1] = 3;
        t->f8[3] = t->f18;
        break;
    case 1:
        t->f8[0] = 6;
        t->f8[1] = 2;
        t->f8[3] = t->f18;
        break;
    case 2:
        t->f8[0] = 6;
        t->f8[1] = 1;
        t->f8[3] = t->f18;
        break;
    }
    dword_800C8B30++;
}

void sub_800C5A7C(BatTask* t)
{
    if (t->fC == 0)
    {
        if (dword_800C8B34 == 0)
        {
            t->f8[2] = 0x10;
            t->f8[0] = 0x15;
            dword_800C8B34 = 1;
            t->f8[1] = 1;
            t->f8[3] = 2;
        }
        else
        {
            t->f8[0] = 0;
            t->f8[3] = t->f18;
        }
    }
    else if (t->fC == 1)
    {
        unsigned char k = dword_800C8B30 % 3;
        switch (k)
        {
        case 0:
            t->f8[0] = 0;
            t->f8[3] = t->f18;
            break;
        case 1:
            t->f8[0] = 6;
            t->f8[1] = 0;
            t->f8[3] = t->f18;
            break;
        case 2:
            t->f8[0] = 1;
            t->f8[1] = 2;
            t->f8[3] = t->f18;
            break;
        }
        dword_800C8B30++;
    }
}

void sub_800C5BC0(BatTask* t)
{
    if (t->fC == 0)
    {
        if (dword_800C8B34 == 0)
        {
            t->f8[2] = 0x10;
            t->f8[0] = 0x15;
            dword_800C8B34 = 1;
            t->f8[1] = 1;
            t->f8[3] = 2;
        }
        else
        {
            t->f8[0] = 0;
            t->f8[3] = t->f18;
        }
    }
    else if (t->fC == 1)
    {
        unsigned char k = dword_800C8B30 % 3;
        switch (k)
        {
        case 0:
            t->f8[0] = 0;
            t->f8[3] = t->f18;
            break;
        case 1:
            t->f8[0] = 6;
            t->f8[1] = 0;
            t->f8[3] = t->f18;
            break;
        case 2:
            t->f8[0] = 1;
            t->f8[1] = 2;
            t->f8[3] = t->f18;
            break;
        }
        dword_800C8B30++;
    }
}

void sub_800C5D04(BatTask* t)
{
    if (t->fC == 0)
    {
        if (dword_800C8B34 == 0)
        {
            t->f8[2] = 0x10;
            t->f8[0] = 0x15;
            dword_800C8B34 = 1;
            t->f8[1] = 1;
            t->f8[3] = 2;
        }
        else
        {
            t->f8[0] = 0;
            t->f8[3] = t->f18;
        }
    }
    else
    {
        unsigned char* p = &dword_800C8B30;
        if (p[1])
        {
            t->f8[0] = 6;
            t->f8[1] = 2;
            t->f8[3] = t->f18;
            p[1] = 0;
        }
        else
        {
            switch (rand() % 3)
            {
            case 0:
                t->f8[0] = 1;
                t->f8[1] = 0x1B;
                t->f8[3] = t->f18;
                sub_80018430(2);
                break;
            case 1:
                t->f8[0] = 6;
                t->f8[1] = 1;
                t->f8[3] = t->f18;
                break;
            default:
                t->f8[0] = 6;
                t->f8[1] = 0;
                t->f8[3] = t->f8[2];
                (&dword_800C8B30)[1] = 1;
                break;
            }
        }
    }
    dword_800C8B30++;
}

void sub_800C5EB8(BatTask* t)
{
    if (t->fC == 0)
    {
        if (dword_800C8B34 == 0)
        {
            t->f8[2] = 0x10;
            t->f8[0] = 0x15;
            dword_800C8B34 = 1;
            t->f8[1] = 1;
            t->f8[3] = 2;
        }
        else
        {
            t->f8[0] = 0;
            t->f8[3] = t->f18;
        }
    }
    else
    {
        switch (rand() % 3)
        {
        case 0:
            if (sub_800334F0((Minion*)t->f14))
            {
                t->f8[0] = 6;
                t->f8[1] = 1;
                t->f8[3] = t->f18;
                break;
            }
        case 1:
            t->f8[0] = 1;
            t->f8[1] = 0x19;
            t->f8[3] = t->f18;
            sub_80018430(0);
            break;
        case 2:
            t->f8[0] = 6;
            t->f8[1] = 3;
            t->f8[3] = t->f18;
            break;
        }
    }
    dword_800C8B30++;
}

#if 0 // Not matched: one spot: in the 'f8[3] = f8[2]; dword_800C8B30 = 0' arm the byte store is scheduled above the word store (original keeps it in the j delay slot), which also swaps v0/v1
void sub_800C6038(BatTask* t)
{
    if (t->fC == 0)
    {
        if (dword_800C8B34 == 0)
        {
            t->f8[2] = 0x10;
            t->f8[0] = 0x15;
            dword_800C8B34 = 1;
            t->f8[1] = 1;
            t->f8[3] = 2;
        }
        else
        {
            t->f8[0] = 0;
            t->f8[3] = t->f18;
        }
    }
    else if (dword_800C8B30 != 0 && sub_800C6EC8(t, 2))
    {
        t->f8[0] = 6;
        t->f8[1] = 0;
        t->f8[3] = t->f8[2];
        dword_800C8B30 = 0;
    }
    else
    {
        dword_800C8B30++;
        switch (rand() % 3)
        {
        case 0:
            t->f8[0] = 1;
            t->f8[1] = 0x1C;
            t->f8[3] = t->f18;
            sub_80018430(1);
            break;
        case 1:
            t->f8[0] = 6;
            t->f8[1] = 1;
            t->f8[3] = t->f18;
            break;
        case 2:
            t->f8[0] = 6;
            t->f8[1] = 3;
            t->f8[3] = t->f18;
            break;
        }
    }
}
#endif

INCLUDE_OVERLAY_ASM(battle, sub_800C6038);

void sub_800C61FC(BatTask* t)
{
    unsigned short f;
    if (t->fC == 0)
    {
        if (dword_800C8B34 == 0)
        {
            t->f8[2] = 0x10;
            t->f8[0] = 0x15;
            dword_800C8B34 = 1;
            t->f8[1] = 1;
            t->f8[3] = 2;
        }
        else
        {
            *(short*)(t->f10 + 0x42) = 0;
            sub_800C66B4((unsigned char*)t->f10, 0xC);
            t->f8[0] = 6;
            t->f8[1] = 1;
            t->f8[3] = t->f18;
        }
    }
    else if ((sub_800BC868() == 0 && !(*(unsigned short*)(t->f10 + 0x42) & 1)) || (dword_800C8B30 >= 3 && sub_800BC868() == 0))
    {
        sub_800C6AFC(t, 6, 2);
        ((unsigned char*)t->f4)[9] = 0x25;
        *(short*)(t->f10 + 0x42) = 8;
        sub_80018430(3);
        sub_800C66B4((unsigned char*)t->f10, 2);
        dword_800C8B30 = 0;
    }
    else if ((sub_800BC868() == 1 && !(*(unsigned short*)(t->f10 + 0x42) & 2)) || (dword_800C8B30 >= 3 && sub_800BC868() == 1))
    {
        sub_800C6AFC(t, 6, 2);
        ((unsigned char*)t->f4)[9] = 0x22;
        *(short*)(t->f10 + 0x42) = 1;
        sub_80018430(0);
        sub_800C66B4((unsigned char*)t->f10, 3);
        dword_800C8B30 = 0;
    }
    else if ((sub_800BC868() == 2 && !(*(unsigned short*)(t->f10 + 0x42) & 4)) || (dword_800C8B30 >= 3 && sub_800BC868() == 2))
    {
        sub_800C6AFC(t, 6, 2);
        ((unsigned char*)t->f4)[9] = 0x23;
        *(short*)(t->f10 + 0x42) = 2;
        sub_80018430(1);
        sub_800C66B4((unsigned char*)t->f10, 0);
        dword_800C8B30 = 0;
    }
    else if ((sub_800BC868() == 3 && !(*(unsigned short*)(t->f10 + 0x42) & 8)) || (dword_800C8B30 >= 4 && sub_800BC868() == 3) || sub_800BC868() == -1)
    {
        sub_800C6AFC(t, 6, 2);
        ((unsigned char*)t->f4)[9] = 0x24;
        *(short*)(t->f10 + 0x42) = 4;
        sub_80018430(2);
        sub_800C66B4((unsigned char*)t->f10, 1);
        dword_800C8B30 = 0;
    }
    else
    {
        f = *(unsigned short*)(t->f10 + 0x42);
        if (f & 8)
        {
            if (dword_800C8B30 == 1)
            {
                sub_800C6B24(t, 1, 0x1D);
            }
            else
            {
                sub_800C6AFC(t, 6, 0);
            }
        }
        else if (f & 1)
        {
            if (rand() & 1)
            {
                sub_800C6AFC(t, 6, 1);
                ((unsigned char*)t->f4)[5] = 4;
            }
            else
            {
                sub_800C6AFC(t, 1, 0x19);
                sub_80018430(0);
            }
        }
        else if (f & 2)
        {
            if (rand() % 3 != 0)
            {
                sub_800C6AFC(t, 1, 0x1C);
                sub_80018430(1);
            }
            else
            {
                sub_800C6AFC(t, 6, 1);
                ((unsigned char*)t->f4)[5] = 5;
            }
        }
        else if (f & 4)
        {
            if (rand() % 3 != 0)
            {
                sub_800C6AFC(t, 6, 1);
                ((unsigned char*)t->f4)[5] = 2;
            }
            else
            {
                sub_800C6AFC(t, 1, 0x1B);
                sub_80018430(2);
            }
        }
    }
    dword_800C8B30 += ((rand() & 3) >> 1) + 1;
}

void sub_800C66B4(unsigned char* buf, unsigned int b)
{
    int i;
    unsigned int c = 0xC;
    unsigned char* p;
    if (b == c)
    {
        c = 0x30;
    }
    for (i = 3, p = buf + 3; i >= 0; i--, p--)
    {
        p[0x20] = c;
    }
    if (b < 0xC)
    {
        (buf + b)[0x20] = 0x18;
    }
}

void sub_800C66F4(BatTask* t)
{
    if (t->fC == 0)
    {
        if (dword_800C8B34 == 0)
        {
            t->f8[2] = 0x10;
            t->f8[0] = 0x15;
            dword_800C8B34 = 1;
            t->f8[1] = 1;
            t->f8[3] = 2;
            return;
        }
    }
    else if (t->fC == 1)
    {
        if ((rand() & 1) || (*(unsigned short*)(t->f14 + 0x42) & 2))
        {
            goto act;
        }
        else
        {
            short x = sub_800334D8((Minion*)t->f10);
            short y = sub_800334CC((Minion*)t->f10);
            if (x < (short)(y / 3))
            {
            act:
                if (sub_800C6A8C(t))
                {
                    return;
                }
            }
        }
    }
    else
    {
        return;
    }
    t->f8[0] = 0;
    t->f8[3] = t->f18;
}

void sub_800C6824(BatTask* t)
{
    if (t->fC == 0)
    {
        if (dword_800C8B34 == 0)
        {
            t->f8[2] = 0x10;
            t->f8[0] = 0x15;
            dword_800C8B34 = 1;
            t->f8[1] = 1;
            t->f8[3] = 2;
            return;
        }
    }
    else if (t->fC == 1)
    {
        short x = sub_800334D8((Minion*)t->f10);
        short y = sub_800334CC((Minion*)t->f10);
        if (x < y / 4)
        {
            if (sub_800C6A8C(t))
            {
                return;
            }
        }
        if (sub_800C6BD0(t, 9))
        {
            return;
        }
    }
    else
    {
        return;
    }
    t->f8[0] = 0;
    t->f8[3] = t->f18;
}

void sub_800C6928(BatTask* t)
{
    if (t->fC == 0)
    {
        if (dword_800C8B34 == 0)
        {
            t->f8[2] = 0x10;
            t->f8[0] = 0x15;
            dword_800C8B34 = 1;
            t->f8[1] = 1;
            t->f8[3] = 2;
            return;
        }
    }
    else if (t->fC == 1)
    {
        short x = sub_800334D8((Minion*)t->f10);
        short y = sub_800334CC((Minion*)t->f10);
        if (x < y / 2)
        {
            if (sub_800C6A8C(t))
            {
                return;
            }
        }
        if (rand() & 1)
        {
            if (sub_800C6BD0(t, 6))
            {
                return;
            }
        }
    }
    else
    {
        return;
    }
    t->f8[0] = 0;
    t->f8[3] = t->f18;
}

void sub_800C6A40(BatTask* t)
{
    *t->f8 = 6;
    t->f8[1] = 0;
    t->f8[3] = t->f18;
}

int sub_800C6A68(BatTask* t)
{
    *t->f8 = 0;
    t->f8[3] = t->f18;
    return 1;
}

int sub_800C6A8C(BatTask* t)
{
    int r = sub_800C6D6C(t->f4, t->f10);
    if (r != 5)
    {
        t->f8[0] = 6;
        t->f8[1] = r;
        t->f8[3] = t->f18;
        return 1;
    }
    return 0;
}

void sub_800C6AFC(BatTask* t, int a, int b)
{
    t->f8[0] = a;
    t->f8[1] = b;
    t->f8[3] = t->f18;
}

void sub_800C6B24(BatTask* t, int a, int b)
{
    int* p;
    t->f8[0] = a;
    t->f8[1] = b;
    p = t->f8;
    p[3] = p[2];
}

int sub_800C6B50(BatTask* t, int a, int b)
{
    if (sub_800C6CFC(a, t->f0, t->f10) != 0)
    {
        t->f8[0] = 1;
        t->f8[1] = a;
        t->f8[3] = 1 << (b + 4);
        return 1;
    }
    return 0;
}

int sub_800C6BD0(BatTask* t, int a)
{
    if (sub_800C6CFC(a, t->f0, t->f10) != 0)
    {
        t->f8[0] = 1;
        t->f8[1] = a;
        t->f8[3] = t->f18;
        return 1;
    }
    return 0;
}

int sub_800C6C44(BatTask* t)
{
    *t->f8 = 0x12;
    return 1;
}

int sub_800C6C58(BatTask* t)
{
    *t->f8 = 7;
    t->f8[3] = t->f18;
    return 1;
}

void sub_800C6C7C(int* out)
{
    int bits = sub_800A248C();
    int i;
    for (i = 0; i < 3; i++)
    {
        int m = 1 << (i + 4);
        if (bits & m)
        {
            out[i] = sub_800A2B60(i);
        }
        else
        {
            out[i] = 0;
        }
    }
}

int sub_800C6CFC(unsigned int a, unsigned int* b, short* c)
{
    if (TestMagicBit_8001AE2C(b, a) != 0)
    {
        if (magicData_8007C438[a].field_4 <= c[6])
        {
            return 1;
        }
    }
    return 0;
}

int sub_800C6D6C(unsigned char* a, short* b)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (a[i * 4] & 1)
        {
            short h = b[6];
            if (!(h < sub_80031A04(a, i)))
            {
                return i;
            }
        }
    }
    return i;
}

int sub_800C6DF8(BatTask* t, int a)
{
    Minion* out[3];
    int i;
    sub_800C6C7C(out);
    for (i = 0; i < 3; i++)
    {
        if (out[i])
        {
            short x = sub_800334D8(out[i]);
            short y = sub_800334CC(out[i]);
            if (x <= y / 4)
            {
                if (sub_800C6B50(t, a, i))
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int sub_800C6EC8(BatTask* t, int m)
{
    return (*(int*)t->f14 & m) != 0;
}

int sub_800C6EE4(BatTask* t)
{
    return t->f14[0x2d] > t->f14[0x2f];
}

int StartBattleMenu_800C6EFC()
{
    int i;
    int m;
    int n = 0;
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D468);
    if (e)
    {
        e->cb_8 = (EventEntryFn)BattleMenuTask_800C8A08;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        if (dword_800C9C7C == 0)
        {
            dword_800C9E49 = 0;
        }
        else
        {
            dword_800C9E49 = 1;
        }
        dword_800C9E58[0] = 0;
        dword_800C9E58[1] = 0;
        dword_800C9E58[3] = 0;
        dword_800C9E58[2] = 1 << dword_800C9C7C;
        dword_800C9E78 = sub_800C0A9C();
        dword_800C9E4B = GetCapturedMinionsFromBitfield_8003BA58(dword_800C9E78);
        dword_800C9E4C = sub_800A248C();
        dword_800C9E4A = GetCapturedMinionsFromBitfield_8003BA58(dword_800C9E4C);
        for (i = 0; i < 3; i++)
        {
            m = 1 << (i + 4);
            if (dword_800C9E4C & m)
            {
                dword_800C9E80[n] = i + 4;
                dword_800C9E72[n] = m;
                n++;
            }
        }
        dword_800C9E50 = 0;
        dword_800C9E40 = 0;
        dword_800C9E48 = 0;
        dword_800C9E68 = 4;
        dword_800C9E70 = 0;
        sub_800C7088();
        sub_800C71A0();
        sub_800C71C8();
        dword_800C9E38 = -1;
    }
    return (int)e;
}

void sub_800C7088()
{
    if (dword_800C9E49 == 0)
    {
        if (sub_800AD308(0) + 1 >= 5)
        {
            dword_800C9308->count_4 = sub_800AD308(0) + 1;
        }
        dword_800C9308->cursor_8 = 0;
        dword_800C92D8->count_4 = 6;
        dword_800C92D8->cursor_8 = 0;
    }
    else
    {
        if (CountMagicBits_8001AE54(sub_80010824(3, dword_800C9C7C - 1)) >= 5)
        {
            dword_800C92F0->count_4 = CountMagicBits_8001AE54(sub_80010824(3, dword_800C9C7C - 1));
        }
        dword_800C92F0->cursor_8 = 0;
        dword_800C92E4->cursor_8 = 0;
        dword_800C92D8->count_4 = 5;
        dword_800C92D8->cursor_8 = 0;
    }
    if ((unsigned char)dword_800C9D56 > dword_800C9E4A - 1)
    {
        dword_800C9D56 = 0;
    }
    dword_800C9314->f0 = dword_800C9E4A;
    dword_800C9314->count_4 = dword_800C9E4A;
    dword_800C9314->cursor_8 = (unsigned char)dword_800C9D56;
}

void sub_800C71A0()
{
    dword_800C9640 = dword_800C9628[dword_800C9E49];
}

void sub_800C71C8()
{
    if (dword_800C9E49 == 0)
    {
        if (sub_800C0A9C() == 0)
        {
            dword_800C93B8[0] = dword_800C9378;
            dword_800C946C |= 2;
        }
        if (sub_800C7334() == 0)
        {
            dword_800C93B8[2] = dword_800C9384;
            dword_800C94A4 |= 2;
        }
        else if (sub_800AD8E4() == 0)
        {
            dword_800C93B8[2] = dword_800C9388;
            dword_800C94A4 |= 2;
        }
        if (sub_800C72B8() == 0)
        {
            dword_800C93B8[6] = dword_800C938C;
            dword_800C9514 |= 2;
        }
        dword_800C9E6C = dword_800C93A4;
    }
    else
    {
        dword_800C9E6C = dword_800C93D4;
    }
}

int sub_800C72B8()
{
    int i;
    int m;
    for (i = 0; i < 3; i++)
    {
        m = dword_800C9E4C & (1 << (i + 4));
        if (m != 0)
        {
            if (sub_800A28FC(i) == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

int sub_800C7334()
{
    int i;
    int m;
    for (i = 0; i < 3; i++)
    {
        m = dword_800C9E4C & (1 << (i + 4));
        if (m != 0)
        {
            if (sub_800BF980(sub_800A2BE4(i)) == 1)
            {
                return 0;
            }
        }
    }
    return 1;
}

char* sub_800C73B8(unsigned char a)
{
    if (a == 4)
    {
        if (dword_800C9E68 & 1)
        {
            return dword_800C932C;
        }
        if (dword_800C9E68 & 4)
        {
            return dword_800C9314;
        }
        return dword_800C9320;
    }
    return dword_800C9338[a];
}

void sub_800C7424(unsigned char a)
{
    sub_800BFC10();
    if (a == 4)
    {
        if (dword_800C9E68 & 1)
        {
            if (dword_800C9E68 & 4)
            {
                dword_800C9DFC = 1;
                dword_800C9174[0] = GetTime30Hz_8002C64C();
                dword_800C9174[1] = GetTime30Hz_8002C64C();
                dword_800C9174[2] = GetTime30Hz_8002C64C();
            }
            if (dword_800C9E68 & 2)
            {
                dword_800C9DFD = 1;
                dword_800C9170 = GetTime30Hz_8002C64C();
            }
        }
        else if (dword_800C9E68 & 4)
        {
            short i;
            dword_800C9DFC = 1;
            i = GetMenuCursorIndex_8003DA54(dword_800C9314);
            dword_800C9174[dword_800C9E80[i] - 4] = GetTime30Hz_8002C64C();
        }
        else
        {
            dword_800C9DFD = 1;
            dword_800C9170 = GetTime30Hz_8002C64C();
        }
    }
}

int sub_800C7530()
{
    BatUseQ_a q;
    BatTgtQ_a b;
    short idx;
    int* p;
    idx = GetMenuCursorIndex_8003DA54(dword_800C9E44);
    q.f0 = ((short*)dword_800C9E44)[4];
    q.f2 = ((short*)dword_800C9E44)[5];
    q.fA = 0;
    dword_800C9E7C = 0;
    switch (dword_800C9E50)
    {
    case 0:
        p = *(int**)(dword_800C9E6C + idx * 8 + 4);
        if (p == 0)
        {
            return 1;
        }
        dword_800C9E7C = *p;
        return 0;
    case 1:
        switch (CheckItemUsable_80033AFC(&q))
        {
        case 0:
            return 1;
        case 1:
            return 0;
        case 2:
        case 4:
            dword_800C9E7C = dword_800C93A0;
            return 0;
        case 3:
        case 5:
        case 6:
        case 7:
        default:
            return 1;
        }
    case 2:
        q.minion_C = (int)GetMinion_80010598(3, dword_800C9C7C - 1);
        switch (sub_80033C98(&q))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 6:
        default:
            return 1;
        case 5:
            dword_800C9E7C = dword_800C9380;
            return 0;
        case 7:
            return 0;
        }
    case 3:
        q.minion_C = (int)GetMinion_80010598(3, dword_800C9C7C - 1);
        switch (CheckMagicCastable_80033C08(&q))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 7:
        default:
            return 1;
        case 5:
            dword_800C9E7C = dword_800C9380;
            return 0;
        case 6:
            return 0;
        }
    case 4:
        b.f0 = dword_800C9E5C;
        b.f2 = dword_800C9C7C;
        b.f4 = *(unsigned short*)&dword_800C9E54;
        b.f6 = 0;
        if (sub_800C78D0() == 4)
        {
            switch (sub_80033DF4(&b))
            {
            case 0:
                return 1;
            case 1:
                dword_800C9E7C = dword_800C939C;
                return 0;
            case 2:
                dword_800C9E7C = dword_800C9398;
                return 0;
            case 3:
                dword_800C9E7C = dword_800C9390;
                return 0;
            case 4:
                break;
            default:
                return 1;
            }
        }
        else if (sub_800C78D0() == 6)
        {
            switch (((int (*)(BatTgtQ_a*))sub_80034124)(&b))
            {
            case 0:
                return 1;
            case 1:
                dword_800C9E7C = dword_800C939C;
                return 0;
            case 2:
                return 0;
            case 3:
                dword_800C9E7C = dword_800C9390;
                return 0;
            case 4:
                break;
            default:
                return 1;
            }
        }
        else if (sub_800C78D0() == 7)
        {
            switch (sub_80034068(&b))
            {
            case 0:
                return 1;
            case 1:
                dword_800C9E7C = dword_800C939C;
                return 0;
            case 2:
                return 0;
            case 3:
                dword_800C9E7C = dword_800C9390;
                return 0;
            case 4:
                break;
            default:
                return 1;
            }
        }
        else if (sub_800C78D0() == 2 || sub_800C78D0() == 8)
        {
            if (sub_80033548((int*)sub_80014390(dword_800C9E54), 0x400) == 0)
            {
                return 1;
            }
        }
        else
        {
            return 1;
        }
        dword_800C9E7C = dword_800C937C;
        return 0;
    case 5:
    default:
        return 1;
    }
}

INCLUDE_OVERLAY_ASM(battle, dword_800BA238);

unsigned char sub_800C78D0()
{
    return dword_800C9648[dword_800C9E49 + (short)GetMenuCursorIndex_8003DA54(dword_800C92D8) * 2];
}

#if 0 // Not matched: b and r swap registers (v1/a0); tried declaration order, int b, re-reading the global, early returns
int sub_800C791C()
{
    unsigned char b = dword_800C9E68;
    int r = 0;
    if (b & 1)
    {
        if (b & 4)
        {
            r = dword_800C9E4C;
        }
        if (b & 2)
        {
            r |= 1;
            r |= dword_800C9E78;
        }
    }
    else if (b & 4)
    {
        short i = GetMenuCursorIndex_8003DA54(dword_800C9314);
        r = dword_800C9E72[i];
    }
    else
    {
        r = 1 << *(int*)&dword_800C9E54;
    }
    return r;
}
#endif

INCLUDE_OVERLAY_ASM(battle, sub_800C791C);

int sub_800C79B8()
{
    return sub_800AD288((short)GetMenuCursorIndex_8003DA54(dword_800C9308), 0);
}

void sub_800C79EC()
{
    sub_80031BDC((short)GetMenuCursorIndex_8003DA54(dword_800C92E4));
}

int sub_800C7A1C()
{
    char* h = sub_80010824(3, dword_800C9C7C - 1);
    return FindNthMagicBit_8001AEC0(h, (short)GetMenuCursorIndex_8003DA54(dword_800C92F0));
}

void sub_800C7A6C()
{
    int h;
    char* m;
    dword_800C9E40 = dword_800C9E50;
    switch (dword_800C9E50)
    {
    case 0:
        dword_800C9E68 = dword_800C9660[sub_800C78D0()];
        dword_800C9E50 = dword_800C9654[sub_800C78D0()];
        dword_800C9E58[0] = dword_800C96A4[sub_800C78D0()];
        break;
    case 1:
        dword_800C9E68 = sub_8001CE8C(((int (*)())sub_800C79B8)());
        dword_800C9E50 = 4;
        *(int*)&dword_800C9E5C = ((int (*)())sub_800C79B8)();
        break;
    case 2:
        h = sub_80031B30(dword_800C9C7C);
        dword_800C9E68 = sub_80031B0C(h, sub_80031BDC((short)GetMenuCursorIndex_8003DA54(dword_800C92E4)));
        dword_800C9E50 = 4;
        *(int*)&dword_800C9E5C = ((int (*)())sub_800C79EC)();
        break;
    case 3:
        m = sub_80010824(3, dword_800C9C7C - 1);
        dword_800C9E68 = sub_8001ACE4(FindNthMagicBit_8001AEC0(m, (short)GetMenuCursorIndex_8003DA54(dword_800C92F0)));
        dword_800C9E50 = 4;
        *(int*)&dword_800C9E5C = ((int (*)())sub_800C7A1C)();
        break;
    case 4:
        dword_800C9E50 = 5;
        dword_800C9E64 = sub_800C791C();
        break;
    case 5:
        break;
    }
    if (dword_800C9E50 == 4)
    {
        if (sub_800C78D0() == 4)
        {
            dword_800C9320[0].f2 = dword_800C9E4B + 1;
            dword_800C9320[0].count_4 = dword_800C9E4B + 1;
        }
        else if (sub_800C78D0() == 2)
        {
            dword_800C9320[0].f2 = dword_800C9E4B;
            dword_800C9320[0].count_4 = dword_800C9E4B;
        }
        else if (sub_800C78D0() == 7)
        {
            dword_800C9320[0].f2 = 1;
            dword_800C9320[0].count_4 = 1;
        }
        else if (sub_800C78D0() == 8)
        {
            dword_800C9320[0].f2 = dword_800C9E4B;
            dword_800C9320[0].count_4 = dword_800C9E4B;
        }
        dword_800C9320[0].cursor_8 = 0;
        dword_800C9320[0].scroll_A = 0;
    }
}

void sub_800C7CE8(unsigned char a)
{
    unsigned int n;
    if (a == 0)
    {
        dword_800C9630.f0 = 2;
    }
    else
    {
        dword_800C9630.f0 = 4;
    }
    dword_800C9630.f4 = GetTime30Hz_8002C64C();
    n = dword_800C9630.f8;
    if (n < 8)
    {
        dword_800C9630.f8 = n + 1;
    }
    dword_800C9630.fC = dword_800C92E0;
}

void sub_800C7D54(unsigned char a)
{
    if (a != 4)
    {
        dword_800C9C99 = dword_800C9C7C;
    }
    else if (dword_800C9E68 & 5)
    {
        dword_800C9C99 = dword_800C9C7C;
    }
    else
    {
        dword_800C9C99 = dword_800C9E54;
    }
}

void BattleMenuDraw_800C7DA8()
{
    int flags = 0;
    int k = 0;
    int c;
    short sel[2];
    dword_800C9180 = 0;
    dword_800C9182 = 0;
    if (IsCircleHeldP1_8003D480() == 1 && dword_800C9E48 != 1)
    {
        if (dword_800C9E50 == 0)
        {
            k = 1;
            sub_800C8828(*((BatMenuItem_a*)dword_800C9E6C)[(short)GetMenuCursorIndex_8003DA54(dword_800C92D8)].text);
        }
        else if (dword_800C9E50 == 1)
        {
            if (sub_800C79B8() != 0xFF)
            {
                DrawLargeTextBox_8002AF10((int)dword_800C96C8[sub_800C79B8()], 0, 0xF);
                k = 1;
            }
        }
        else if (dword_800C9E50 == 2)
        {
            Minion* m = GetMinion_80010598(3, dword_800C9C7C - 1);
            sub_8002C670(m, 0, dword_800C9B58, (short)GetMenuCursorIndex_8003DA54(dword_800C92E4), 0xF);
            k = 1;
        }
        else if (dword_800C9E50 == 3)
        {
            if (sub_800C7A1C() < 0x1E)
            {
                DrawLargeTextBox_8002AF10((int)dword_800C9978[sub_800C7A1C()], 0, 0xF);
                k = 1;
            }
        }
    }
    if (k != 0)
    {
        k = 1;
    }
    else
    {
        k = dword_800C9E48;
    }
    sel[0] = dword_800C9E5C;
    sel[1] = dword_800C9C7C;
    if (!(dword_800C968C[dword_800C9E50][k] & 0x10))
    {
        if (dword_800C9E68 & 1)
        {
            c = -1;
        }
        else
        {
            c = (short)GetMenuCursorIndex_8003DA54(dword_800C9E44);
        }
        if (sub_800C78D0() == 4)
        {
            if (dword_800C9E68 & 2)
            {
                *(int*)&dword_800C9E54 = sub_8002D250(sel, 0, c, 0xF);
                flags |= 1;
            }
        }
        else if (sub_800C78D0() == 6)
        {
        }
        else if (sub_800C78D0() == 7)
        {
            if (dword_800C9E68 & 2)
            {
                *(int*)&dword_800C9E54 = sub_8002D250(sel, 1, c, 0xF);
                flags |= 1;
            }
        }
        else if (sub_800C78D0() == 2)
        {
            *(int*)&dword_800C9E54 = sub_8002D250(sel, 2, c, 0xF);
            flags |= 1;
        }
        else if (sub_800C78D0() == 8)
        {
            *(int*)&dword_800C9E54 = sub_8002D250(sel, 3, c, 0xF);
            flags |= 1;
        }
    }
    if (dword_800C968C[dword_800C9E50][k] & 2)
    {
        sub_800BC838(0x8000);
    }
    else
    {
        sub_800BC850(0x8000);
    }
    if (dword_800C968C[dword_800C9E50][k] & 1)
    {
        sub_800BC838(0x10000);
    }
    else
    {
        sub_800BC850(0x10000);
    }
    if (!(dword_800C968C[dword_800C9E50][k] & 4) && !(flags & 1))
    {
        DrawMenuWindows_8002A5A4(&dword_800C9630);
    }
    if (!(dword_800C968C[dword_800C9E50][k] & 0x20) && !(flags & 2))
    {
        BatWin_a w;
        w.w = 2;
        w.h = 0xF;
        w.c = -1;
        w.p = 0;
        w.d = 0;
        w.x = dword_800C9308->cursor_8;
        w.y = dword_800C9308->scroll_A;
        sub_8002C728(&w);
    }
    if (!(dword_800C968C[dword_800C9E50][k] & 0x40) && !(flags & 4))
    {
        BatWin_a w;
        w.w = 2;
        w.h = 0xF;
        w.c = -1;
        w.x = dword_800C92E4->cursor_8;
        w.y = dword_800C92E4->scroll_A;
        w.p = (int)GetMinion_80010598(3, dword_800C9C7C - 1);
        w.d = 0;
        sub_8002CE28(&w, 0);
        dword_800C9182 = -sub_80031A04(w.p + 0xDE, sub_80031BDC((short)GetMenuCursorIndex_8003DA54(dword_800C92E4)));
    }
    if (!(dword_800C968C[dword_800C9E50][k] & 0x80) && !(flags & 8))
    {
        BatWin_a w;
        short sz[2];
        w.w = 2;
        w.h = 0xF;
        w.c = -1;
        w.x = dword_800C92F0->cursor_8;
        w.y = dword_800C92F0->scroll_A;
        w.p = (int)GetMinion_80010598(3, dword_800C9C7C - 1);
        sz[0] = 0x60;
        w.d = 0;
        sz[1] = 0x45;
        sub_8002CAC8(&w, sz);
        dword_800C9182 = -GetMagicMpCost_8001AC58(FindNthMagicBit_8001AEC0(w.p + 0xF4, (short)GetMenuCursorIndex_8003DA54(dword_800C92F0)));
    }
    DrawButtonHelpBar_8002B004(dword_800C9674[dword_800C9E50], 0, 0xF);
}

void sub_800C83B0()
{
    BatTgtQ_a b;
    BatCmd_a a;
    BatResult_a d;
    unsigned int i;
    int bit;
    BatUnit_a* self;
    BatUnit_a* m;
    a = *(BatCmd_a*)dword_800C9E58;
    if (dword_800C9E50 == 4)
    {
        dword_800C9180 = 0;
        dword_800C9182 = 0;
        self = (BatUnit_a*)sub_80014390(dword_800C9C7C);
        for (i = 0; i < 4; i++)
        {
            bit = 1 << i;
            if ((((BatCmd_a*)dword_800C9E58)->fC & bit) && i == dword_800C9C99)
            {
                m = (BatUnit_a*)sub_80014390(i & 0xFF);
                d.f24 = (signed char)dword_800C9D82;
                d.f26 = (signed char)dword_800C9D83;
                a.fC = bit;
                sub_80012BB0(self, m, &a, &d);
                if (sub_80013228(self, m, &a, &d) == 0 && (((BatCmd_a*)dword_800C9E58)->f8 & bit))
                {
                    dword_800C9180 -= d.fC;
                    dword_800C9182 -= d.f10;
                    dword_800C9180 -= d.f14;
                    dword_800C9182 -= d.f18;
                }
                dword_800C9180 -= d.f1C;
                dword_800C9182 -= d.f20;
                if (dword_800C9180 > m->hpLoss_A - m->hp_8)
                {
                    dword_800C9180 = m->hpLoss_A - m->hp_8;
                }
                if (dword_800C9182 > m->mpLoss_E - m->mp_C)
                {
                    dword_800C9182 = m->mpLoss_E - m->mp_C;
                }
            }
        }
        b.f0 = dword_800C9E5C;
        b.f2 = dword_800C9C7C;
        b.f4 = *(unsigned short*)&dword_800C9E54;
        b.f6 = 0;
        if (sub_800C78D0() == 4)
        {
            if (sub_80033DF4(&b))
            {
                dword_800C9180 = 0;
                dword_800C9182 = 0;
            }
        }
        else if (sub_800C78D0() == 6)
        {
            if (((int (*)(BatTgtQ_a*))sub_80034124)(&b))
            {
                dword_800C9180 = 0;
            }
        }
        else if (sub_800C78D0() == 7)
        {
            if (sub_80034068(&b))
            {
                dword_800C9180 = 0;
            }
        }
    }
}

void sub_800C8694(unsigned char a)
{
    if (a == 4 && (dword_800C9E68 & 5) == 4)
    {
        dword_800C9E3C = dword_800C9E72[(short)GetMenuCursorIndex_8003DA54(dword_800C9314)];
    }
    else
    {
        dword_800C9E3C = dword_800C9E4C;
    }
}

void sub_800C8710()
{
    if (dword_800C9E38 != dword_800C9E3C)
    {
        dword_800C9E38 = dword_800C9E3C;
        sub_80037AE0((unsigned short)dword_800C9E3C);
        sub_800BC468(dword_800C9E3C, 1 << dword_800C9C7C);
    }
}

void sub_800C8768()
{
    if (IsConfirmPressedP1_8003D380(0))
    {
        if (sub_800C7530())
        {
            PlaySfx_80031494(0x7E);
            sub_800C7A6C();
        }
        else
        {
            PlaySfx_80031494(0x7C);
            if (dword_800C9E7C)
            {
                dword_800C9E51 = 0x96;
                dword_800C9E48 = 1;
            }
        }
    }
    else if (IsCancelPressedP1_8003D41C(0))
    {
        if (dword_800C9E50)
        {
            unsigned char c;
            PlaySfx_80031494(0x7D);
            c = dword_800C9E40;
            dword_800C9E40 = 0;
            dword_800C9E50 = c;
        }
    }
}

#if 0 // Not matched: arg setup order only (original computes &s first and &pos last); tried prototypes, separate arrays, &a, statement order
extern void DrawTextLinesWindow_8002AE38(void* a0, void* a1, int a2, void* a3, int a4);
void sub_800C8828(int a)
{
    short rect[4];
    short p[4];
    short pos[2];
    int s[1];
    rect[0] = 0x19;
    rect[1] = 0x8A;
    rect[2] = MeasureTextWidth_8003E4C8() + 4;
    rect[3] = 0x12;
    s[0] = a;
    p[0] = rect[0];
    p[1] = rect[1];
    pos[0] = rect[0] + 2;
    pos[1] = rect[1] + 4;
    DrawTextLinesWindow_8002AE38(s, pos, 0xF, rect, 1);
}
#endif

INCLUDE_OVERLAY_ASM(battle, sub_800C8828);

void sub_800C88AC(int a)
{
    int s[4];
    s[0] = a;
    s[1] = 0;
    s[2] = 0;
    s[3] = 0;
    DrawLargeTextBox_8002AF10((int)s, 0, 0xF);
}

void sub_800C88E4()
{
    if (padPressed_8009194C)
    {
        dword_800C9E51 = 0;
    }
    if (dword_800C9E51 == 0)
    {
        dword_800C9E48 = 0;
    }
    else
    {
        dword_800C9E51--;
    }
    if (dword_800C9E7C)
    {
        if (dword_800C9E50 == 0)
        {
            sub_800C8828(dword_800C9E7C);
        }
        else
        {
            sub_800C88AC(dword_800C9E7C);
        }
    }
}

void sub_800C8970()
{
    int v;
    dword_800C9C88[0] = dword_800C9E58[0];
    dword_800C9C88[1] = dword_800C9E58[1];
    dword_800C9C88[2] = dword_800C9E58[2];
    v = dword_800C9E58[0];
    if (v == 7 || v == 0x12)
    {
        dword_800C9C88[3] = dword_800C9E4C;
    }
    else if (v == 8)
    {
        dword_800C9C88[3] = 0;
    }
    else
    {
        dword_800C9C88[3] = dword_800C9E58[3];
    }
    dword_800C9C98 = LowestSetBit_80014358(dword_800C9E64);
}

void BattleMenuTask_800C8A08(EventEntry* t, int a)
{
    dword_800C9E44 = sub_800C73B8(dword_800C9E50);
    sub_800C7424(dword_800C9E50);
    UpdateMenuCursor_8003D794(dword_800C9E44, 0);
    sub_800C7CE8(dword_800C9E50);
    BattleMenuDraw_800C7DA8();
    dword_800C9E64 = sub_800C791C();
    sub_800C7D54(dword_800C9E50);
    sub_800C83B0();
    sub_800C8694(dword_800C9E50);
    sub_800C8710();
    dword_800C966C[dword_800C9E48](t, a);
    if (dword_800C9E50 == 5)
    {
        dword_800C9D56 = dword_800C9314->cursor_8;
        sub_800BFC10();
        sub_800C8970();
        dword_800C9180 = 0;
        dword_800C9182 = 0;
        t->flags = (t->flags & ~1) | 0x8000;
    }
}

INCLUDE_OVERLAY_ASM(battle, dword_800C8B2C);
