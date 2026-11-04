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
#include "tu_80019BF0.h"
#include "tu_800318C8.h"

const ActionData defaultActionData_80071F58 = { 0, 0, 100, 255, 115, 0, 0, 10, { 0, 3 } };
const char aAssertionFaile_2[] = "Assertion failed: file \"%s\", line %d\n";
const char aCommonC[] = "COMMON.C";
int dword_80079320[10] = {
    1, 0, 1, 0, 5, 7, 11, 13,
    9, 15,
};
unsigned short statGrowthTable_80079348[0x15] = {
    0x11D, 0x140, 0x163, 0x186, 0x1A9, 0x1CC, 0x1EF, 0x212,
    0x235, 0x258, 0x27B, 0x29E, 0x2C1, 0x2E4, 0x307, 0x32A,
    0x34D, 0x370, 0x393, 0x3B6, 0x3E7,
};
unsigned short growthKindThresholds_80079374[40] = {
    190, 19, 180, 18, 170, 17, 160, 16,
    150, 15, 140, 14, 130, 13, 120, 12,
    110, 11, 100, 10, 90, 9, 80, 8,
    70, 7, 60, 6, 50, 5, 40, 4,
    30, 3, 20, 2, 10, 1,
};
unsigned char sealRatioThresholds_800793C4[4] = { 2, 3, 5, 10 };
unsigned char sealOutcomeTable_800793C8[118][4] = {
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
void AddStatus_80012794(UnitStatus* status, int bits)
{
    if (status->status_0 & 0x3F8)
    {
        bits &= ~0x3F8;
    }
    status->status_0 |= bits;
}
// Matched
void KillUnit_800127B8(UnitStatus* status)
{
    status->exp_4 = 0;
    status->hp_8 = 0;
    status->status_0 |= 0x400;
}
// Matched
void AdjustUnitStatById_800127D0(int unit, int sel, int delta, int mask)
{
    UnitStatus* status = GetUnitStatus_80014390(unit & 0xFF);

    if (status != 0)
    {
        AdjustUnitStat_80012614(status, sel, delta, mask);
    }
}
// Matched
void ApplyStatusPenalties_80012828(int* stats, UnitStatus* status)
{
    if (status->status_0 & 1)
    {
        stats[0] = stats[0] * 4 / 5;
        stats[2] = stats[2] * 4 / 5;
    }
    if (status->status_0 & 2)
    {
        stats[1] = stats[1] * 2 / 3;
        stats[3] = stats[3] * 2 / 3;
        stats[5] = 0;
    }
    if (status->status_0 & 0x3F8)
    {
        stats[4] = stats[4] * 3 / 5;
        stats[5] = stats[5] * 3 / 5;
    }
    if (status->status_0 & 0x8000)
    {
        stats[3] = (0x7FFF < stats[3] + stats[3] * 5) ? 0x7FFF : stats[3] + stats[3] * 5;
        stats[1] = (0x7FFF < stats[1] + stats[1] * 5) ? 0x7FFF : stats[1] + stats[1] * 5;
        stats[5] = 0;
    }
}

// Matched
ActionData* GetAbilityActionData_800129B0(ActionData* out, unsigned char* in, int unit)
{
    int id = 0xD3;
    int kind = in[1];
    Minion* mn;
    UnitStats* u;
    MemCopy_800403E8(out, sub_800318C8(kind), 12);
    mn = GetUnitMinion_80014444(unit & 0xFF);
    if (mn)
    {
        id = mn->species_2;
    }
    u = GetUnitStats_8001449C(unit & 0xFF);
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
extern const char aAssertionFaile_2[];
extern const char aCommonC[];
extern unsigned char sealRatioThresholds_800793C4[];
extern unsigned char sealOutcomeTable_800793C8[][4];
extern const ActionData defaultActionData_80071F58; // an empty action
extern int sub_80031B30(int a0);
extern int sub_80031A04(int a0, int a1);
extern void sub_800335D0(UnitStatus* src, UnitStatus* out);
extern void CalcBattleStats_80013EE8(int* out, UnitStatus* f, ActionData* s, int a3);
extern void CalcActionDamage_80013374(ActionData* s, UnitStatus* f0, UnitStatus* f1, int* r0, int* r1, int* p, ActionResult* out);
extern int Rand100_80013E30(void);
// Matched
void ResolveBattleAction_80012BB0(UnitStatus* actor, UnitStatus* target, int* cmd, ActionResult* out)
{
    int actorStats[12];
    int targetStats[12];
    UnitStatus actorStatus;
    UnitStatus targetStatus;
    ActionData local = defaultActionData_80071F58;
    ActionData* q;
    int actorUnit;
    int targetUnit;
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

    actorUnit = LowestSetBit_80014358(cmd[2]);
    targetUnit = LowestSetBit_80014358(cmd[3]);
    out->kind_0 = 0;
    out->flags_4 = 0;
    out->field_8 = 0;
    out->field_C = 0;
    out->field_10 = 0;
    out->field_14 = 0;
    out->field_18 = 0;
    out->field_1C = 0;
    out->field_20 = 0;
    sub_800184A0(targetUnit, 0);
    q = &local;
    switch (cmd[0])
    {
    case 0:
        if (cmd[2] == 1)
        {
            MemCopy_800403E8(&local, sub_8001D260(), 12);
        }
        break;
    case 6:
        t = sub_80031B30(actorUnit & 0xFF);
        q = GetAbilityActionData_800129B0(&local, (unsigned char*)(t + cmd[1] * 4), targetUnit);
        out->field_10 = sub_80031A04(t, cmd[1]);
        break;
    case 1:
        MemCopy_800403E8(&local, sub_8001AD64(cmd[1]), 12);
        out->field_10 = GetMagicMpCost_8001AC58(cmd[1]);
        break;
    case 4:
        MemCopy_800403E8(&local, GetItemData_8001CDF4(cmd[1]), 12);
        break;
    case 26:
        break;
    }
    sub_800335D0(actor, &actorStatus);
    sub_800335D0(target, &targetStatus);
    CalcBattleStats_80013EE8(actorStats, &actorStatus, q, cmd[2]);
    CalcBattleStats_80013EE8(targetStats, &targetStatus, q, cmd[3]);
    ApplyStatusPenalties_80012828(actorStats, &actorStatus);
    ApplyStatusPenalties_80012828(targetStats, &targetStatus);
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
    mn = GetUnitMinion_80014444(actorUnit & 0xFF);
    if (mn)
    {
        id = mn->species_2;
    }
    u = GetUnitStats_8001449C(actorUnit & 0xFF);
    if (u)
    {
        id = u->species_5C;
    }
    if (id != 0xD3)
    {
        if ((GetMinionEnhancementBody_80019C0C(id) & 2) && cmd[0] == 1 && q->s2 > 0)
        {
            q->s2 = (0xFFFF < q->s2 + 10) ? -1 : (unsigned short)q->s2 + 10;
        }
        if ((GetMinionEnhancementBody_80019C0C(id) & 1) && cmd[0] == 6 && q->s2 > 0)
        {
            q->s2 = (0xFFFF < q->s2 + 10) ? -1 : (unsigned short)q->s2 + 10;
        }
    }
    switch (cmd[0])
    {
    case 0:
    case 1:
    case 4:
    case 6:
        CalcActionDamage_80013374(q, &actorStatus, &targetStatus, actorStats, targetStats, cmd, out);
        break;
    case 5:
    case 26:
        sa = sub_800334CC(target);
        sb = sub_800334D8(target);
        out->kind_0 = 7;
        v = sa / sb;
        c = sub_80033514(target);
        if (c > 40)
        {
            c = 40;
        }
        d = (sub_80033514(actor) - c) * 10 / 12;
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
        if (sub_80033548(target, 2))
        {
            v <<= 3;
        }
        k = 0;
        while (sealRatioThresholds_800793C4[k] < v && k < 4)
        {
            k++;
        }
        r = rand() % 16;
        j = 0;
        while (sealOutcomeTable_800793C8[k][j] <= r)
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
        if (sub_80033548(target, 2))
        {
            out->field_2 = 0;

        }
        break;
    }
    if (out->kind_0 == 5)
    {
        sub_800184A0(targetUnit, 1);
        sub_800184A0(targetUnit, 2);
    }
}
// Matched
int sub_80013228(int a0, int a1, int* p)
{
    ActionData local = defaultActionData_80071F58;
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
        q = GetAbilityActionData_800129B0(&local, (unsigned char*)(sub_80031B30(b1 & 0xFF) + p[1] * 4), b2);
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

// zero word at the end of this TU's .rdata, in front of the jump table of UseItemOnUnit_80013C28 (tu_80013358)
const int dword_800720E4 = 0;
