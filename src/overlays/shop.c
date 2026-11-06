// SHOP.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "actor.h"
#include "engine.h"
#include "minion_menu.h"
#include "shop.h"








int dword_800B6D00 SDATA = 38;
const char aAssertFmt_800B6D04[] = "Assertion failed: file \"%s\", line %d\n";
const char aCmpactC_800B6D2C[] = "CMPACT.C";
const ShopElementOrder elementOrder_800B6D38 = { { 0, 1, 2, 3 } };
const int dword_800B6D48 = 0;

int CompactStoredMinions_800B97B0()
{
    int moved = 0;
    short i;
    short j;
    for (i = 3; i < shopMinionCount_800B6CE4; i++)
    {
        if (GetShopMinionState_800B9C10(i) == 4)
        {
            j = FindStoredMinion_800B9888(i);
            if (j <= 0)
            {
                break;
            }
            moved = 1;
            SwapMinions_800BAEDC(&shopMinions_800B6CF0[i], &shopMinions_800B6CF0[j]);
        }
    }
    return moved;
}

int FindStoredMinion_800B9888(short i)
{
    for (; i < shopMinionCount_800B6CE4; i++)
    {
        if (GetShopMinionState_800B9C10(i) == 2)
        {
            return i;
        }
    }
    return -1;
}

// the shop works on a copy of the minions: entries 0..2 the party (state 3), then the stored minions and the held
// cocoons (state 2), 4 = empty; CommitShopMinionList_800B9DA8 writes it back
int BuildShopMinionList_800B9920()
{
    int total = 27;
    Minion* items = malloc3_8003FC4C(0x1A28);
    short n = 0;
    int k;
    for (k = 0; k < 15; k++)
    {
        if (saveData_8008B570.minions[k].id == 3)
        {
            MemCopy_800403E8(&items[n], &saveData_8008B570.minions[k], 0xF8);
            n++;
        }
    }
    if (n < 3)
    {
        for (k = n; k < 3; k++)
        {
            items[k].id = 4;
        }
    }
    n = 3;
    for (k = 0; k < 15; k++)
    {
        if (saveData_8008B570.minions[k].id == 2)
        {
            MemCopy_800403E8(&items[n], &saveData_8008B570.minions[k], 0xF8);
            n++;
        }
    }
    for (k = 0; k < 12; k++)
    {
        if (saveData_8008B570.items[k].species_5C != 0xD3)
        {
            UnitStatsToMinion_800B9E94(&saveData_8008B570.items[k], &items[n], 2);
            n++;
        }
    }
    for (k = n; k < total; k++)
    {
        items[k].id = 4;
    }
    ClearMinionsAndItems_80010600();
    shopMinions_800B6CF0 = items;
    shopMinionCount_800B6CE4 = total;
    return total;
}

void ClearShopMinion_800B9B20(int i)
{
    shopMinions_800B6CF0[i].id = 4;
}

void SetMinionEmpty_800B9B44(short* state)
{
    *state = 4;
}

Minion* GetNthShopMinion_800B9B50(int state, int n)
{
    int cnt = 0;
    int i;
    for (i = 0; i < shopMinionCount_800B6CE4; i++)
    {
        if (state == GetShopMinionState_800B9C10(i) || (state == 0 && GetShopMinionState_800B9C10(i) != 4))
        {
            if (cnt == n)
            {
                return GetShopMinion_800B9C5C(i);
            }
            cnt++;
        }
    }
    return 0;
}

int GetShopMinionState_800B9C10(int i)
{
    return shopMinions_800B6CF0[i].id;
}

short* GetShopMinionAncestors_800B9C34(int i)
{
    return &shopMinions_800B6CF0[i].id + 2;
}

char* GetMinionAncestors_800B9C54(char* minion)
{
    return minion + 4;
}

Minion* GetShopMinion_800B9C5C(int i)
{
    return &shopMinions_800B6CF0[i];
}

int CountShopMinionsInState_800B9C78(int state)
{
    int i;
    int n;
    n = 0;
    for (i = 0; i < shopMinionCount_800B6CE4; i++)
    {
        if (state == shopMinions_800B6CF0[i].id)
        {
            n++;
        }
    }
    return n;
}

int SetMinionInParty_800B9CCC(short* state)
{
    *state = 3;
    return 1;
}

int MoveShopMinionToParty_800B9CDC(int i)
{
    if (CountShopMinionsInState_800B9C78(3) < 3)
    {
        if (GetShopMinionState_800B9C10(i) == 2)
        {
            shopMinions_800B6CF0[i].id = 3;
            return 1;
        }
    }
    return 0;
}

int SetMinionStored_800B9D48(short* state)
{
    if (*state == 3)
    {
        *state = 2;
        return 1;
    }
    return 0;
}

int MoveShopMinionToStorage_800B9D6C(int i)
{
    if (shopMinions_800B6CF0[i].id == 3)
    {
        shopMinions_800B6CF0[i].id = 2;
        return 1;
    }
    return 0;
}

int CommitShopMinionList_800B9DA8()
{
    int cnt = shopMinionCount_800B6CE4;
    Minion* items = shopMinions_800B6CF0;
    int n = 0;
    int i;
    for (i = 0; i < cnt; i++)
    {
        if (items[i].id != 4)
        {
            n++;
        }
    }
    if (n < 16)
    {
        n = 0;
        for (i = 0; i < cnt; i++)
        {
            if (items[i].id != 4)
            {
                MemCopy_800403E8(&saveData_8008B570.minions[n], &items[i], 0xF8);
                n++;
            }
        }
        free3_8003FC6C(items);
        return 1;
    }
    return 0;
}

int UnitStatsToMinion_800B9E94(UnitStats* src, Minion* dst, short state)
{
    int i;
    unsigned int j;
    unsigned int r;
    dst->id = state;
    for (i = 0; i < 6; i++)
    {
        CopyName_80019AF4((unsigned int*)dst->ancestors_4[i], (unsigned int*)src->st_0.name_10);
        dst->ancestorElements_7C[i] = src->st_0.elementMask_42;
    }
    r = LowestSetBit_80014358(src->st_0.elementMask_42);
    for (j = 0; j < 4; j++)
    {
        dst->status_84.element_3E[j] = 0;
    }
    if (r >= 4)
    {
        printf(aAssertFmt_800B6D04, aCmpactC_800B6D2C, 0x1AB);
        exit(1);
    }
    dst->status_84.element_3E[r] = 0x20;
    for (i = 0; i < 0x30; i++)
    {
        dst->species_4C[i] = src->species_5C;
    }
    dst->species_2 = src->species_5C;
    dst->field_3 = src->species_5C;
    MemCopy_800403E8(&dst->status_84, &src->st_0, sizeof(UnitStatus));
    MemCopy_800403E8(&dst->skills_DE, &src->skills_6C, sizeof(UnitSkills));
    MemCopy_800403E8(&dst->magicBits_F4, &src->magicBits_80, 4);
    return 1;
}

// merges base and partner into out; person: the skin used (GetPersonMergeInfo_8001CD58), 10: none
int MergeMinions_800B9FC8(Minion* base, Minion* partner, Minion* out, int person)
{
    ShopElementOrder idx;
    UnitStats tmp;
    unsigned char* info;
    int i;
    int odd;
    int t;
    int special;
    MemCopy_800403E8(out, base, sizeof(Minion));
    out->field_3 = partner->field_3;
    info = GetPersonMergeInfo_8001CD58(person);
    if (info[0] != 0xFF)
    {
        out->field_3 = info[0];
    }
    MergeSpeciesHistory_800BAB38(out, partner);
    for (i = 0; i < 4; i++)
    {
        out->status_84.element_3E[i] = (out->status_84.element_3E[i] + partner->status_84.element_3E[i]) >> 1;
    }
    odd = 0;
    idx = elementOrder_800B6D38;
    for (i = 0; i < 4; i++)
    {
        if (out->status_84.element_3E[i] & 1)
        {
            odd++;
        }
    }
restart:
    for (i = 0; i < 3; i++)
    {
        if (out->status_84.element_3E[idx.order[i]] < out->status_84.element_3E[idx.order[i + 1]])
        {
            t = idx.order[i];
            idx.order[i] = idx.order[i + 1];
            idx.order[i + 1] = t;
            goto restart;
        }
    }
    if (odd == 2)
    {
        for (i = 0; i < 4; i++)
        {
            info = (unsigned char*)out + idx.order[i]; // info[0xC2] == status_84.element_3E[idx.order[i]]; the struct form changes the codegen
            t = info[0xC2];
            if (t & 1)
            {
                if (odd >= 2)
                {
                    info[0xC2] = t
 + 1;
                }
                else
                {
                    info[0xC2] = t
 - 1;
                }
                odd--;
            }
        }
    }
    if (odd == 4)
    {
        for (i = 0; i < 4; i++)
        {
            info = (unsigned char*)out + idx.order[i]; // info[0xC2] == status_84.element_3E[idx.order[i]]; the struct form changes the codegen
            t = info[0xC2];
            if (t & 1)
            {
                if (odd >= 3)
                {
                    info[0xC2] = t
 + 1;
                }
                else
                {
                    info[0xC2] = t
 - 1;
                }
                odd--;
            }
        }
    }
    for (i = 3; i >= 0; i--)
    {
    }
    out->status_84.elementMask_42 = 0;
    if (out->status_84.element_3E[0] >= 8)
    {
        out->status_84.elementMask_42 = 1;
    }
    if (out->status_84.element_3E[3] >= 8)
    {
        *(unsigned short*)&out->status_84.elementMask_42 |= 8;
    }
    if (out->status_84.element_3E[2] >= 8)
    {
        *(unsigned short*)&out->status_84.elementMask_42 |= 4;
    }
    if (out->status_84.element_3E[1] >= 8)
    {
        *(unsigned short*)&out->status_84.elementMask_42 |= 2;
    }
    InheritMergeStats_800BA368(out, base);
    MergeBaseStats_800BA3C8(out->status_84.stats_2C.cur_0, base->status_84.stats_2C.cur_0, partner->status_84.stats_2C.cur_0);
    MergeResistances_800BA4CC(out, base, partner);
    ApplyMergeStatBonus_800BA650(out);
    MergeExp_800BA6D0(out, base, partner);
    ApplyLevelUps_80011D98(&out->status_84, 2);
    MergeSkills_800BA72C(out, partner);
    MergeMagic_800BAA0C(out, partner);
    FillHpMp_80011C0C(&out->status_84, &out->status_84);
    special = GetSpecialMergeSpecies_800BACD0(out);
    if (special > 0)
    {
        idx.order[0] = special;
        idx.order[1] = (out->status_84.level_44 << 26) + out->status_84.exp_4;
        InitMinionData_8001900C(&tmp, idx.order);
        UnitStatsToMinion_800B9E94(&tmp, out, out->id);
    }
    return 1;
}

void ClearMinion_800BA340(unsigned int* minion)
{
    MemCopy_800403E8(minion, emptyMinion_800C07F0, 0xF8);
}

void InheritMergeStats_800BA368(Minion* out, Minion* src)
{
    int i;
    for (i = 0; i < 6; i++)
    {
        out->status_84.stats_2C.cur_0[i] = src->status_84.stats_2C.cur_0[i] - src->status_84.stats_2C.base_6[i] / 20;
    }
    out->status_84.hp_8.max_2 = src->status_84.hp_8.max_2;
    out->status_84.mp_C.max_2 = src->status_84.mp_C.max_2;
}

void MergeBaseStats_800BA3C8(unsigned char* out, unsigned char* base, unsigned char* partner)
{
    int i;
    for (i = 5; i >= 0; i--)
    {
    }
    for (i = 5; i >= 0; i--)
    {
    }
    for (i = 0; i < 6; i++)
    {
        (out + i)[6] = MergeBaseStat_800BA46C((base + i)[6], (partner + i)[6]);
    }
    for (i = 5; i >= 0; i--)
    {
    }
}

unsigned char MergeBaseStat_800BA46C(unsigned char base, unsigned char partner)
{
    int avg = (base + partner) >> 1;
    int c = partner - 200;
    int val = avg + (base + c) / 7;
    int out = 0;
    if (val >= 0)
    {
        out = val;
        if (out > 200)
        {
            out = 200;
        }
    }
    return out;
}

void MergeResistances_800BA4CC(Minion* out, Minion* base, Minion* partner)
{
    int tmp[4];
    int j;
    int i;
    int v;
    int y;
    int x;
    int t;
    int r;
    int k;
    for (k = 0; k < 12; k++)
    {
        x = (signed char)base->status_84.modifiers_20[k];
        y = (signed char)partner->status_84.modifiers_20[k];
        if (x < y)
        {
            x = x * 2;
        }
        else
        {
            y = y * 2;
        }
        v = (x + y) / 3;
        if (v >= -128)
        {
            t = v;
            if (t > 127)
            {
                t = 127;
            }
            r = t;
        }
        else
        {
            r = -128;
        }
        out->status_84.modifiers_20[k] = r;
    }
    memset(tmp, 0, 16);
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            tmp[j] += out->status_84.element_3E[i] * elementModifiers_8007BA74[j + i * 4];
        }
    }
    for (i = 0; i < 4; i++)
    {
        out->status_84.modifiers_20[i] = tmp[i] / 32;
    }
    for (i = 11; i >= 0; i--)
    {
    }
    for (i = 11; i >= 0; i--)
    {
    }
    for (i = 11; i >= 0; i--)
    {
    }
}

void ApplyMergeStatBonus_800BA650(Minion* out)
{
    int i;
    int v;
    int r;
    int t;
    unsigned char* p;
    for (i = 0; i < 6; i++)
    {
        // p[0xB0] / p[0xB6] == status_84.stats_2C.cur_0[i] / stats_2C.base_6[i]; indexing the fields lets the compiler strength-reduce the loop
        p = (unsigned char*)out + i;
        v = p[0xB0] + (unsigned char)(p[0xB6] / 20);
        if (v >= 0) { t = v; if (t > 100) t = 100; r = t; } else r = 0; p[0xB0] = r;
    }


    for (i = 5; i >= 0; i--)
    {
    }
}

void MergeExp_800BA6D0(Minion* out, Minion* base, Minion* partner)
{
    out->status_84.level_44 = base->status_84.level_44;
    out->status_84.exp_4 = base->status_84.exp_4;
    out->status_84.exp_4 += CombinedExpDelta_80012204(base->status_84.level_44, base->status_84.exp_4, partner->status_84.level_44, partner->status_84.exp_4);
}

// Matched
void MergeSkills_800BA72C(Minion* out, Minion* partner)
{
    UnitSkills skills;
    UnitSkill* ae;
    UnitSkill* be;
    int i;
    int mask;
    int r;
    int m;
    int v;
    skills = out->skills_DE;
    ae = out->skills_DE.slot;
    be = partner->skills_DE.slot;
    for (i = 0; i < 5; i++)
    {
        skills.slot[i].flags_0 |= (ae[i].flags_0 | be[i].flags_0) & 1;
    }
    mask = out->status_84.elementMask_42;
    for (i = 0; i < 5; i++)
    {
        switch (skills.slot[i].id_1)
        {
        case 2:
            if (!(mask & 4))
            {
                skills.slot[i].id_1 = 0;
            }
            break;
        case 3:
            if (!(mask & 8))
            {
                skills.slot[i].id_1 = 0;
            }
            break;
        case 4:
            if (!(mask & 1))
            {
                skills.slot[i].id_1 = 0;
            }
            break;
        case 5:
            if (!(mask & 2))
            {
                skills.slot[i].id_1 = 0;
            }
            break;
        }
        if (skills.slot[i].flags_0 & 1)
        {
            m = out->status_84.elementMask_42;
            r = -1;
            switch (ae[i].id_1)
            {
            case 0:
                r = ae[i].id_1;
                break;
            case 1:
                r = ae[i].id_1;
                break;
            case 2:
                if (m & 4)
                {
                    r = ae[i].id_1;
                }
                break;
            case 3:
                if (m & 8)
                {
                    r = ae[i].id_1;
                }
                break;
            case 4:
                if (m & 1)
                {
                    r = ae[i].id_1;
                }
                break;
            case 5:
                if (m & 2)
                {
                    r = ae[i].id_1;
                }
                break;
            default:
                r = ae[i].id_1;
                break;
            }
            if (r >= 0)
            {
                skills.slot[i].id_1 = r;
            }
            r = -1;
            switch (be[i].id_1)
            {
            case 0:
            case 1:
                break;
            case 2:
                if (m & 4)
                {
                    r = be[i].id_1;
                }
                break;
            case 3:
                if (m & 8)
                {
                    r = be[i].id_1;
                }
                break;
            case 4:
                if (m & 1)
                {
                    r = be[i].id_1;
                }
                break;
            case 5:
                if (m & 2)
                {
                    r = be[i].id_1;
                }
                break;
            default:
                if (skills.slot[i].id_1 == 0)
                {
                    r = be[i].id_1;
                }
                break;
            }
            if (r >= 0)
            {
                skills.slot[i].id_1 = r;
            }
            if (skills.slot[i].id_1 == 1)
            {
                skills.slot[i].id_1 = 0;
            }
        }
        else
        {
            skills.slot[i].id_1 = 0;
        }
        if (skills.slot[i].flags_0 & 1)
        {
            v = be[i].bonus_2;
            if (v == 1)
            {
                skills.slot[i].bonus_2 = 1;
                skills.slot[i].field_3 = 0;
            }
            else if (v != 0 && v < 5)
            {
                skills.slot[i].bonus_2 = v;
                skills.slot[i].field_3 = 1;
            }
        }
        else
        {
            skills.slot[i].bonus_2 = 0;
            skills.slot[i].field_3 = 0;
        }
    }
    MemCopy_800403E8(&out->skills_DE, &skills, sizeof(UnitSkills));
}
const char aEmpty_800B6D7C[4] = { 0 };
const char aWhatDoYouWantTo_800B6D80[] = "\202v\202\210\202\201\202\224\201@\202\204\202\217\201@\202\231\202\217\202\225\201@\202\227\202\201\202\216\202\224\201@\202\224\202\217\201@\202\204\202\217\201H"; // What do you want to do?
const char aForTheNewMinion_800B6DB0[] = "\202\206\202\217\202\222\201@\202\224\202\210\202\205\201@\202\216\202\205\202\227\201@\202\215\202\211\202\216\202\211\202\217\202\216\201D"; // for the new minion.
const char aPickTheCocoonTo_800B6DD8[] = "\202o\202\211\202\203\202\213\201@\202\224\202\210\202\205\201@\202\203\202\217\202\203\202\217\202\217\202\216\201@\202\224\202\217\201@\202\202\202\205\201@\202\224\202\210\202\205\201@\202\202\202\201\202\223\202\205"; // Pick the cocoon to be the base
const char aIllSpinThemO_800B6E18[] = "\202h\201f\202\214\202\214\201@\202\223\202\220\202\211\202\216\201@\202\224\202\210\202\205\202\215\201@\202\227\202\210\202\205\202\216\201@\202\231\202\217\202\225\201@\202\220\202\222\202\205\202\223\202\223\201@\201\233\201D"; // Ｉ’ｌｌ　ｓｐｉｎ　ｔｈｅｍ　ｗｈｅｎ　ｙｏｕ　ｐｒｅｓｓ　○．
const char aToSpinWithX_800B6E5C[] = "\202\224\202\217\201@\202\223\202\220\202\211\202\216\201@\202\227\202\211\202\224\202\210\201@\201~\201D"; // ｔｏ　ｓｐｉｎ　ｗｉｔｈ　×．
const char aPickTheCocoonsY_800B6E7C[] = "\202o\202\211\202\203\202\213\201@\202\224\202\210\202\205\201@\202\203\202\217\202\203\202\217\202\217\202\216\202\223\201@\202\231\202\217\202\225\201@\202\227\202\201\202\216\202\224\201@\202\215\202\205"; // Pick the cocoons you want me
const char aToMixWithIt_800B6EB8[] = "\202\224\202\217\201@\202\215\202\211\202\230\201@\202\227\202\211\202\224\202\210\201@\202\211\202\224\201D"; // to mix with it.
const char aPickTheMinionYo_800B6ED8[] = "\202o\202\211\202\203\202\213\201@\202\224\202\210\202\205\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\231\202\217\202\225\201@\202\227\202\201\202\216\202\224"; // Pick the minion you want
const char aNo_800B6F0C[] = "\201@\202m\202\217"; //  No
const char aYes_800B6F14[] = "\201@\202x\202\205\202\223"; //  Yes
const char aOKIfISpinThisCo_800B6F20[] = "\202n\202j\201@\202\211\202\206\201@\202h\201@\202\223\202\220\202\211\202\216\201@\202\224\202\210\202\211\202\223\201@\202\203\202\217\202\203\202\217\202\217\202\216\201H"; // OK if I spin this cocoon?
const char aToEquipAndTakeW_800B6F54[] = "\202\224\202\217\201@\202\205\202\221\202\225\202\211\202\220\201@\202\201\202\216\202\204\201@\202\224\202\201\202\213\202\205\201@\202\227\202\211\202\224\202\210\201@\202\231\202\217\202\225\201D"; // to equip and take with you.
const char aChooseTheThreeM_800B6F8C[] = "\202b\202\210\202\217\202\217\202\223\202\205\201@\202\224\202\210\202\205\201@\202\224\202\210\202\222\202\205\202\205\201@\202\215\202\211\202\216\202\211\202\217\202\216\202\223\201@\202\231\202\217\202\225\201@\202\227\202\201\202\216\202\224"; // Choose the three minions you want
const char aOKIfIMergeThem_800B6FD0[] = "\202n\202j\201@\202\211\202\206\201@\202h\201@\202\215\202\205\202\222\202\207\202\205\201@\202\224\202\210\202\205\202\215\201H"; // OK if I merge them?
const char aWannaTryMerging_800B6FF8[] = "\202v\202\201\202\216\202\216\202\201\201@\202\224\202\222\202\231\201@\202\215\202\205\202\222\202\207\202\211\202\216\202\207\201@\202\223\202\217\202\215\202\205\201@\202\215\202\217\202\222\202\205\201H"; // Wanna try merging some more?
const char aSqViewOtherAbilities_800B7034[] = "\201\240\201@\202u\202\211\202\205\202\227\201@\202\217\202\224\202\210\202\205\202\222\201@\202\201\202\202\202\211\202\214\202\211\202\224\202\211\202\205\202\223\201D"; // □　Ｖｉｅｗ　ｏｔｈｅｒ　ａｂｉｌｉｔｉｅｓ．
const char aOViewMinionsForm_800B7064[] = "\201\233\201@\202u\202\211\202\205\202\227\201@\202\215\202\211\202\216\202\211\202\217\202\216\201f\202\223\201@\202\206\202\217\202\222\202\215\201D"; // ○　Ｖｉｅｗ　ｍｉｎｉｏｎ’ｓ　ｆｏｒｍ．
const char aXRenameTriQuit_800B7090[] = "\201~\201@\202q\202\205\202\216\202\201\202\215\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\201D\201@\201\242\201@\202p\202\225\202\211\202\224\201D"; // ×　Ｒｅｎａｍｅ　Ｍｉｎｉｏｎ．　△　Ｑｕｉｔ．
const char aRenameThisMinio_800B70C4[] = "\202q\202\205\202\216\202\201\202\215\202\205\201@\202\224\202\210\202\211\202\223\201@\202\215\202\211\202\216\202\211\202\217\202\216\201H"; // Rename this minion?
const char aPickTheMinionsT_800B70EC[] = "\202o\202\211\202\203\202\213\201@\202\224\202\210\202\205\201@\202\215\202\211\202\216\202\211\202\217\202\216\202\223\201@\202\224\202\217\201@\202\205\202\230\202\203\202\210\202\201\202\216\202\207\202\205\201D"; // Pick the minions to exchange.
const char aSeeYaNextTime_800B7128[] = "\202r\202\205\202\205\201@\202\231\202\201\201@\202\216\202\205\202\230\202\224\201@\202\224\202\211\202\215\202\205\201D"; // See ya next time.
const char aIMAllDoneForNow_800B714C[] = "\202h\201f\202\215\201@\202\201\202\214\202\214\201@\202\204\202\217\202\216\202\205\201@\202\206\202\217\202\222\201@\202\216\202\217\202\227\201D"; // I'm all done for now.
const char aICanSpinToGetRi_800B7178[] = "\202h\201@\202\203\202\201\202\216\201@\202\223\202\220\202\211\202\216\201@\202\224\202\217\201@\202\207\202\205\202\224\201@\202\222\202\211\202\204\201@\202\217\202\206\201@\202\223\202\217\202\215\202\205\201D"; // I can spin to get rid of some.
const char aICanTStoreAnyMo_800B71B8[] = "\202h\201@\202\203\202\201\202\216\201f\202\224\201@\202\223\202\224\202\217\202\222\202\205\201@\202\201\202\216\202\231\201@\202\215\202\217\202\222\202\205\201@\202\203\202\217\202\203\202\217\202\217\202\216\202\223\201D"; // I can't store any more cocoons.
const char aOhIMSorryIMAllO_800B71F8[] = "\202n\202\210\201C\202h\201f\202\215\201@\202\223\202\217\202\222\202\222\202\231\201D\202h\201f\202\215\201@\202\201\202\214\202\214\201@\202\217\202\225\202\224\201@\202\217\202\206\201@\202\223\202\220\202\201\202\203\202\205\201D"; // Oh,I'm sorry.I'm all out of space.
const char aWannaUseTheMini_800B7240[] = "\202v\202\201\202\216\202\216\202\201\201@\202\225\202\223\202\205\201@\202\224\202\210\202\205\201@\202\215\202\211\202\216\202\211\202\217\202\216\202\223\201f\201@\202\223\202\213\202\211\202\216\202\223\201H"; // Wanna use the minions' skins?
const char aPickTheSkinYouW_800B727C[] = "\202o\202\211\202\203\202\213\201@\202\224\202\210\202\205\201@\202\223\202\213\202\211\202\216\201@\202\231\202\217\202\225\201@\202\227\202\201\202\216\202\224\201D"; // Pick the skin you want.
const char aTheSqButton_800B72AC[] = "\202\224\202\210\202\205\201@\201\240\201@\202\202\202\225\202\224\202\224\202\217\202\216\201D"; // ｔｈｅ　□　ｂｕｔｔｏｎ．
const char aYouCanViewOther_800B72C8[] = "\202x\202\217\202\225\201@\202\203\202\201\202\216\201@\202\226\202\211\202\205\202\227\201@\202\217\202\224\202\210\202\205\202\222\201@\202\223\202\224\202\201\202\224\202\223\201@\202\227\202\211\202\224\202\210"; // You can view other stats with
const char aOViewForm_800B7304[] = "\201\233\201@\202u\202\211\202\205\202\227\201@\202\206\202\217\202\222\202\215\201D"; // ○　Ｖｉｅｗ　ｆｏｒｍ．
const char aThisIsWhatItLlL_800B7320[] = "\202s\202\210\202\211\202\223\201@\202\211\202\223\201@\202\227\202\210\202\201\202\224\201@\202\211\202\224\201f\202\214\202\214\201@\202\214\202\217\202\217\202\213\201@\202\214\202\211\202\213\202\205\201D"; // This is what it'll look like.
const char aYouCanSellThisA_800B735C[] = "\202x\202\217\202\225\201@\202\203\202\201\202\216\201@\202\223\202\205\202\214\202\214\201@\202\224\202\210\202\211\202\223\201@\202\201\202\224\201@\202\224\202\210\202\205\201@\202u\202\211\202\214\202\214\202\201\202\207\202\205\201@\202r\202\224\202\217\202\222\202\205\201D"; // You can sell this at the Village Store.
const char aOkayIHaveSpunSo_800B73AC[] = "\202n\202\213\202\201\202\231\201C\201@\202h\201@\202\210\202\201\202\226\202\205\201@\202\223\202\220\202\225\202\216\201@\202\223\202\217\202\215\202\205\201@\202\223\202\210\202\211\202\216\202\231\201@\202\223\202\211\202\214\202\213\201@\202\224\202\210\202\222\202\205\202\201\202\204\201D"; // Okay, I have spun some shiny silk thread.
const char aIfWeUseThem_800B7400[] = "\202\211\202\206\201@\202\227\202\205\201@\202\225\202\223\202\205\201@\202\224\202\210\202\205\202\215\201I"; // if we use them!
const char aSomethingExciti_800B7420[] = "\202r\202\217\202\215\202\205\202\224\202\210\202\211\202\216\202\207\201@\202\205\202\230\202\203\202\211\202\224\202\211\202\216\202\207\201@\202\215\202\211\202\207\202\210\202\224\201@\202\210\202\201\202\220\202\220\202\205\202\216"; // Something exciting might happen
const char aISeeYouHaveSome_800B7460[] = "\202h\201@\202\223\202\205\202\205\201@\202\231\202\217\202\225\201@\202\210\202\201\202\226\202\205\201@\202\223\202\217\202\215\202\205\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\223\202\213\202\211\202\216\202\223\201D"; // I see you have some minion skins.
const char aTheTriButton_800B74A4[] = "\202\224\202\210\202\205\201@\201\242\201@\202\202\202\225\202\224\202\224\202\217\202\216\201D"; // ｔｈｅ　△　ｂｕｔｔｏｎ．
const char aYouCanReturnToS_800B74C0[] = "\202x\202\217\202\225\201@\202\203\202\201\202\216\201@\202\222\202\205\202\224\202\225\202\222\202\216\201@\202\224\202\217\201@\202\223\202\224\202\201\202\224\202\225\202\223\201@\202\223\202\203\202\222\202\205\202\205\202\216\201@\202\227\202\211\202\224\202\210"; // You can return to status screen with
const char aWhatDoYouWishTo_800B750C[] = "\202v\202\210\202\201\202\224\201@\202\204\202\217\201@\202\231\202\217\202\225\201@\202\227\202\211\202\223\202\210\201@\202\224\202\217\201@\202\204\202\217\201H"; // What do you wish to do?
const char aPleasePickTheCo_800B753C[] = "\202o\202\214\202\205\202\201\202\223\202\205\201@\202\220\202\211\202\203\202\213\201@\202\224\202\210\202\205\201@\202\203\202\217\202\203\202\217\202\217\202\216\201@\202\224\202\217\201@\202\202\202\205\201@\202\224\202\210\202\205\201@\202\202\202\201\202\223\202\205"; // Please pick the cocoon to be the base
const char aPleasePickTheCo_800B7588[] = "\202o\202\214\202\205\202\201\202\223\202\205\201@\202\220\202\211\202\203\202\213\201@\202\224\202\210\202\205\201@\202\203\202\217\202\203\202\217\202\217\202\216\202\223\201@\202\231\202\217\202\225\201@\202\227\202\201\202\216\202\224\201@\202\215\202\205"; // Please pick the cocoons you want me
const char aToMixItWith_800B75D0[] = "\202\224\202\217\201@\202\215\202\211\202\230\201@\202\211\202\224\201@\202\227\202\211\202\224\202\210\201D"; // to mix it with.
const char aPleasePickTheMi_800B75F0[] = "\202o\202\214\202\205\202\201\202\223\202\205\201@\202\220\202\211\202\203\202\213\201@\202\224\202\210\202\205\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\231\202\217\202\225\201@\202\227\202\201\202\216\202\224"; // Please pick the minion you want
const char aMayISpinThisMin_800B7630[] = "\202l\202\201\202\231\201@\202h\201@\202\223\202\220\202\211\202\216\201@\202\224\202\210\202\211\202\223\201@\202\215\202\211\202\216\202\211\202\217\202\216\201H"; // May I spin this minion?
const char aTakeWithYou_800B7660[] = "\202\224\202\201\202\213\202\205\201@\202\227\202\211\202\224\202\210\201@\202\231\202\217\202\225\201D"; // take with you.
const char aChooseUpToThree_800B7680[] = "\202b\202\210\202\217\202\217\202\223\202\205\201@\202\225\202\220\201@\202\224\202\217\201@\202\224\202\210\202\222\202\205\202\205\201@\202\215\202\211\202\216\202\211\202\217\202\216\202\223\201@\202\224\202\217"; // Choose up to three minions to
const char aShallIMergeThem_800B76BC[] = "\202r\202\210\202\201\202\214\202\214\201@\202h\201@\202\215\202\205\202\222\202\207\202\205\201@\202\224\202\210\202\205\202\215\201H"; // Shall I merge them?
const char aShallWeMergeSom_800B76E4[] = "\202r\202\210\202\201\202\214\202\214\201@\202\227\202\205\201@\202\215\202\205\202\222\202\207\202\205\201@\202\223\202\217\202\215\202\205\201@\202\215\202\217\202\222\202\205\201@\202\215\202\211\202\216\202\211\202\217\202\216\202\223\201H"; // Shall we merge some more minions?
const char aPleasePickTheMi_800B7728[] = "\202o\202\214\202\205\202\201\202\223\202\205\201@\202\220\202\211\202\203\202\213\201@\202\224\202\210\202\205\201@\202\215\202\211\202\216\202\211\202\217\202\216\202\223\201@\202\224\202\217\201@\202\205\202\230\202\203\202\210\202\201\202\216\202\207\202\205\201D"; // Please pick the minions to exchange.
const char aMyWorkIsComplet_800B7774[] = "\202l\202\231\201@\202\227\202\217\202\222\202\213\201@\202\211\202\223\201@\202\203\202\217\202\215\202\220\202\214\202\205\202\224\202\205\201@\202\206\202\217\202\222\201@\202\216\202\217\202\227\201D"; // My work is complete for now.
const char aCanTStoreAnyMor_800B77B0[] = "\202\203\202\201\202\216\201f\202\224\201@\202\223\202\224\202\217\202\222\202\205\201@\202\201\202\216\202\231\201@\202\215\202\217\202\222\202\205\201@\202\203\202\217\202\203\202\217\202\217\202\216\202\223\201D"; // can't store any more cocoons.
const char aIMAllOutOfSpace_800B77EC[] = "\202h\201f\202\215\201@\202\201\202\214\202\214\201@\202\217\202\225\202\224\201@\202\217\202\206\201@\202\223\202\220\202\201\202\203\202\205\201@\202\201\202\216\202\204"; // I'm all out of space and
const char aDoYouWantToUseT_800B7820[] = "\202c\202\217\201@\202\231\202\217\202\225\201@\202\227\202\201\202\216\202\224\201@\202\224\202\217\201@\202\225\202\223\202\205\201@\202\224\202\210\202\205\201@\202\215\202\211\202\216\202\211\202\217\202\216\202\223\201f\201@\202\223\202\213\202\211\202\216\202\223\201H"; // Do you want to use the minions' skins?
const char aPleasePickTheSk_800B7870[] = "\202o\202\214\202\205\202\201\202\223\202\205\201@\202\220\202\211\202\203\202\213\201@\202\224\202\210\202\205\201@\202\223\202\213\202\211\202\216\201@\202\231\202\217\202\225\201@\202\227\202\201\202\216\202\224\201D"; // Please pick the skin you want.
const char aToViewOtherStat_800B78B0[] = "\202\224\202\217\201@\202\226\202\211\202\205\202\227\201@\202\217\202\224\202\210\202\205\202\222\201@\202\223\202\224\202\201\202\224\202\223\201D"; // to view other stats.
const char aUseTheSqButton_800B78DC[] = "\202t\202\223\202\205\201@\202\224\202\210\202\205\201@\201\240\201@\202\202\202\225\202\224\202\224\202\217\202\216"; // Ｕｓｅ　ｔｈｅ　□　ｂｕｔｔｏｎ
const char aItAtTheVillageS_800B7900[] = "\202\211\202\224\201@\202\201\202\224\201@\202\224\202\210\202\205\201@\202u\202\211\202\214\202\214\202\201\202\207\202\205\201@\202r\202\224\202\217\202\222\202\205\201D"; // it at the Village Store.
const char aYouCanGetMoneyB_800B7934[] = "\202x\202\217\202\225\201@\202\203\202\201\202\216\201@\202\207\202\205\202\224\201@\202\215\202\217\202\216\202\205\202\231\201@\202\202\202\231\201@\202\223\202\205\202\214\202\214\202\211\202\216\202\207"; // You can get money by selling
const char aIHaveSpunSomeSh_800B7970[] = "\202h\201@\202\210\202\201\202\226\202\205\201@\202\223\202\220\202\225\202\216\201@\202\223\202\217\202\215\202\205\201@\202\223\202\210\202\211\202\216\202\231\201@\202\223\202\211\202\214\202\213\201@\202\224\202\210\202\222\202\205\202\201\202\204\201D"; // I have spun some shiny silk thread.
const char aIfWeUseThem_800B79B8[] = "\202\211\202\206\201@\202\227\202\205\201@\202\225\202\223\202\205\201@\202\224\202\210\202\205\202\215\201D"; // if we use them.
const char aSomethingExtrao_800B79D8[] = "\202r\202\217\202\215\202\205\202\224\202\210\202\211\202\216\202\207\201@\202\205\202\230\202\224\202\222\202\201\202\217\202\222\202\204\202\211\202\216\202\201\202\222\202\231\201@\202\215\202\211\202\207\202\210\202\224\201@\202\210\202\201\202\220\202\220\202\205\202\216"; // Something extraordinary might happen
const char aReturnToTheStat_800B7A24[] = "\202\222\202\205\202\224\202\225\202\222\202\216\201@\202\224\202\217\201@\202\224\202\210\202\205\201@\202\223\202\224\202\201\202\224\202\225\202\223\201@\202\223\202\203\202\222\202\205\202\205\202\216\201D"; // return to the status screen.
const char aUseTheTriButtonTo_800B7A60[] = "\202t\202\223\202\205\201@\202\224\202\210\202\205\201@\201\242\201@\202\202\202\225\202\224\202\224\202\217\202\216\201@\202\224\202\217"; // Ｕｓｅ　ｔｈｅ　△　ｂｕｔｔｏｎ　ｔｏ
const char aNoSkinsJp_800B7A88[] = "\202\265\202\340\202\327\202\314\224\347\202\252\202\310\202\242\202\355"; // しもべの皮がないわ
const char aCantChooseJp_800B7A9C[] = "\202\273\202\314\220\271\226\202\202\315\221I\202\327\202\310\202\242\202\355"; // その聖魔は選べないわ
const char aNoMinionsJp_800B7AB4[] = "\220\271\226\202\202\252\202\242\202\310\202\242\202\355\202\346"; // 聖魔がいないわよ
const char aNeedTwoJp_800B7AC8[] = "\202Q\221\314\202\242\202\310\202\242\202\306\215\207\220\254\202\305\202\253\202\310\202\242\202\346"; // ２体いないと合成できないよ
const char aMinions_800B7AE4[] = "\202\215\202\211\202\216\202\211\202\217\202\216\202\223\201D"; // minions.
const char aICanTMergeUnles_800B7AF8[] = "\202h\201@\202\203\202\201\202\216\201f\202\224\201@\202\215\202\205\202\222\202\207\202\205\201@\202\225\202\216\202\214\202\205\202\223\202\223\201@\202\227\202\205\201@\202\210\202\201\202\226\202\205\201@\202\224\202\227\202\217"; // I can't merge unless we have two
const char aWeDonTHaveAnyMi_800B7B3C[] = "\202v\202\205\201@\202\204\202\217\202\216\201f\202\224\201@\202\210\202\201\202\226\202\205\201@\202\201\202\216\202\231\201@\202\215\202\211\202\216\202\211\202\217\202\216\202\223\201D"; // We don't have any minions.
const char aWeCanTUseThatMi_800B7B74[] = "\202v\202\205\201@\202\203\202\201\202\216\201f\202\224\201@\202\225\202\223\202\205\201@\202\224\202\210\202\201\202\224\201@\202\215\202\211\202\216\202\211\202\217\202\216\201D"; // We can't use that minion.
const char aWeDonTHaveAnyMi_800B7BA8[] = "\202v\202\205\201@\202\204\202\217\202\216\201f\202\224\201@\202\210\202\201\202\226\202\205\201@\202\201\202\216\202\231\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\223\202\213\202\211\202\216\202\223\201D"; // We don't have any minion skins.
const char aNoSkinsJp2_800B7BE8[] = "\202\265\202\340\202\327\202\314\224\347\202\252\202\240\202\350\202\334\202\271\202\361"; // しもべの皮がありません
const char aCantChooseJp2_800B7C00[] = "\202\273\202\314\226\202\225\250\202\315\221I\202\327\202\334\202\271\202\361"; // その魔物は選べません
const char aNoMinionsJp2_800B7C18[] = "\226\202\225\250\202\252\202\242\202\310\202\242\202\346\202\244\202\305\202\267"; // 魔物がいないようです
const char aNeedTwoJp2_800B7C30[] = "\202Q\225C\202\242\202\310\202\242\202\306\215\207\220\254\202\252\202\305\202\253\202\334\202\271\202\361"; // ２匹いないと合成ができません
const char aThereArenTAnyMi_800B7C50[] = "\202s\202\210\202\205\202\222\202\205\201@\202\201\202\222\202\205\202\216\201f\202\224\201@\202\201\202\216\202\231\201@\202\215\202\211\202\216\202\211\202\217\202\216\202\223\201D"; // There aren't any minions.
const char aThereArenTAnyMi_800B7C84[] = "\202s\202\210\202\205\202\222\202\205\201@\202\201\202\222\202\205\202\216\201f\202\224\201@\202\201\202\216\202\231\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\223\202\213\202\211\202\216\202\223\201D"; // There aren't any minion skins.
const char aForYou_800B7CC4[] = "\202\206\202\217\202\222\201@\202\231\202\217\202\225\201D"; // for you.
const char aCombineThemAndC_800B7CD8[] = "\202\203\202\217\202\215\202\202\202\211\202\216\202\205\201@\202\224\202\210\202\205\202\215\201@\202\201\202\216\202\204\201@\202\203\202\222\202\205\202\201\202\224\202\205\201@\202\201\201@\202\216\202\205\202\227\201@\202\217\202\216\202\205"; // combine them and create a new one
const char aIfYouSelectTwoM_800B7D1C[] = "\202h\202\206\201@\202\231\202\217\202\225\201@\202\223\202\205\202\214\202\205\202\203\202\224\201@\202\224\202\227\202\217\201@\202\215\202\211\202\216\202\211\202\217\202\216\202\223\201C\201@\202h\201@\202\203\202\201\202\216"; // If you select two minions, I can
const char aYouCanSellItInT_800B7D60[] = "\202\231\202\217\202\225\201@\202\203\202\201\202\216\201@\202\223\202\205\202\214\202\214\201@\202\211\202\224\201@\202\211\202\216\201@\202\224\202\210\202\205\201@\202u\202\211\202\214\202\214\202\201\202\207\202\205\201@\202\223\202\224\202\217\202\222\202\205\201D"; // you can sell it in the Village store.
const char aIfYouSpinTheCoc_800B7DAC[] = "\202h\202\206\201@\202\231\202\217\202\225\201@\202\223\202\220\202\211\202\216\201@\202\224\202\210\202\205\201@\202\203\202\217\202\203\202\217\202\217\202\216\201@\202\211\202\216\202\224\202\217\201@\202\223\202\211\202\214\202\213\201C"; // If you spin the cocoon into silk,
const char aWithUpToThreeCo_800B7DF0[] = "\202\227\202\211\202\224\202\210\201@\202\225\202\220\201@\202\224\202\217\201@\202\224\202\210\202\222\202\205\202\205\201@\202\203\202\217\202\203\202\217\202\217\202\216\202\223\201D"; // with up to three cocoons.
const char aYouCanEquipYour_800B7E24[] = "\202x\202\217\202\225\201@\202\203\202\201\202\216\201@\202\205\202\221\202\225\202\211\202\220\201@\202\231\202\217\202\225\202\222\202\223\202\205\202\214\202\206"; // You can equip yourself
const char aCreaturesYouHav_800B7E54[] = "\202\203\202\222\202\205\202\201\202\224\202\225\202\222\202\205\202\223\201@\202\231\202\217\202\225\201@\202\210\202\201\202\226\202\205\201@\202\203\202\201\202\220\202\224\202\225\202\222\202\205\202\204\201D"; // creatures you have captured.
const char aYouCanRenameAnd_800B7E90[] = "\202x\202\217\202\225\201@\202\203\202\201\202\216\201@\202\222\202\205\202\216\202\201\202\215\202\205\201@\202\201\202\216\202\204\201@\202\226\202\211\202\205\202\227\201@\202\224\202\210\202\205"; // You can rename and view the
const char aStopPerformingD_800B7EC8[] = "\202r\202\224\202\217\202\220\201@\202\220\202\205\202\222\202\206\202\217\202\222\202\215\202\211\202\216\202\207\201@\202\204\202\211\202\226\202\211\202\216\202\205\201@\202\215\202\201\202\207\202\211\202\203\201@\202\206\202\217\202\222\201@\202\216\202\217\202\227\201H"; // Stop performing divine magic for now?
const char aMergeThemAndCre_800B7F14[] = "\202\215\202\205\202\222\202\207\202\205\201@\202\224\202\210\202\205\202\215\201@\202\201\202\216\202\204\201@\202\203\202\222\202\205\202\201\202\224\202\205\201@\202\201\201@\202\216\202\205\202\227\201@\202\217\202\216\202\205"; // merge them and create a new one
const char aCocoonsIntoSilk_800B7F54[] = "\202\203\202\217\202\203\202\217\202\217\202\216\202\223\201@\202\211\202\216\202\224\202\217\201@\202\223\202\211\202\214\202\213\201@\202\224\202\210\202\201\202\224\201@\202\231\202\217\202\225\201@\202\203\202\201\202\216\201@\202\223\202\205\202\214\202\214\201D"; // cocoons into silk that you can sell.
const char aYouCanGetMoneyB_800B7FA0[] = "\202x\202\217\202\225\201@\202\203\202\201\202\216\201@\202\207\202\205\202\224\201@\202\215\202\217\202\216\202\205\202\231\201@\202\202\202\231\201@\202\223\202\220\202\211\202\216\202\216\202\211\202\216\202\207"; // You can get money by spinning
const char aYouCanChangeThe_800B7FDC[] = "\202x\202\217\202\225\201@\202\203\202\201\202\216\201@\202\203\202\210\202\201\202\216\202\207\202\205\201@\202\224\202\210\202\205\201@\202\216\202\201\202\215\202\205\202\223\201@\202\217\202\206\201@\202\224\202\210\202\205"; // You can change the names of the
const char aForNow_800B801C[] = "\202\206\202\217\202\222\201@\202\216\202\217\202\227\201H"; // for now?
const char aStopPerformingD_800B8030[] = "\202r\202\224\202\217\202\220\201@\202\220\202\205\202\222\202\206\202\217\202\222\202\215\202\211\202\216\202\207\201@\202\204\202\211\202\226\202\211\202\216\202\205\201@\202\215\202\201\202\207\202\211\202\203"; // Stop performing divine magic
const char aSpin_800B806C[] = "\202r\202\220\202\211\202\216"; // Spin
const char aQuit_800B8078[] = "\202p\202\225\202\211\202\224"; // Quit
const char aSelect_800B8084[] = "\202r\202\205\202\214\202\205\202\203\202\224"; // Select
const char aViewForm_800B8094[] = "\202u\202\211\202\205\202\227\201@\202\206\202\217\202\222\202\215"; // View form
const char aRearrange_800B80A8[] = "\202q\202\205\202\201\202\222\202\222\202\201\202\216\202\207\202\205"; // Rearrange
const char aViewOtherAbilit_800B80BC[] = "\202u\202\211\202\205\202\227\201@\202\217\202\224\202\210\202\205\202\222\201@\202\201\202\202\202\211\202\214\202\211\202\224\202\211\202\205\202\223"; // View other abilities
const char aRename_800B80E8[] = "\202q\202\205\202\216\202\201\202\215\202\205"; // Rename
const char aCombine_800B80F8[] = "\202b\202\217\202\215\202\202\202\211\202\216\202\205"; // Combine
const char aZoom_800B8108[] = "\201@\202y\202\217\202\217\202\215"; //  Zoom
const char aDescription_800B8114[] = "\202c\202\205\202\223\202\203\202\222\202\211\202\220\202\224\202\211\202\217\202\216"; // Description
const char aEffectivenessOf_800B812C[] = "\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\202\216\202\205\202\223\202\223\201@\202\217\202\206\201@\202\205\202\201\202\222\202\224\202\210\201@\202\206\202\217\202\222\201@\202\204\202\225\202\222\202\201\202\224\202\211\202\217\202\216\201@\202\217\202\206\201@\202\202\202\201\202\224\202\224\202\214\202\205\201D"; // effectiveness of earth for duration of battle.
const char aIncreasesWindAt_800B818C[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223\201@\202\227\202\211\202\216\202\204\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\220\202\217\202\227\202\205\202\222\201@\202\201\202\216\202\204\201@\202\204\202\205\202\203\202\222\202\205\202\201\202\223\202\205\202\223"; // Increases wind attack power and decreases
const char aEnhanceWind_800B81E0[] = "\202d\202\216\202\210\202\201\202\216\202\203\202\205\201@\202v\202\211\202\216\202\204"; // Enhance Wind
const char aEffectivenessOf_800B81FC[] = "\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\202\216\202\205\202\223\202\223\201@\202\217\202\206\201@\202\227\202\201\202\224\202\205\202\222\201@\202\206\202\217\202\222\201@\202\204\202\225\202\222\202\201\202\224\202\211\202\217\202\216\201@\202\217\202\206\201@\202\202\202\201\202\224\202\224\202\214\202\205\201D"; // effectiveness of water for duration of battle.
const char aIncreasesEarthA_800B825C[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223\201@\202\205\202\201\202\222\202\224\202\210\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\220\202\217\202\227\202\205\202\222\201@\202\201\202\216\202\204\201@\202\204\202\205\202\203\202\222\202\205\202\201\202\223\202\205\202\223"; // Increases earth attack power and decreases
const char aEnhanceEarth_800B82B4[] = "\202d\202\216\202\210\202\201\202\216\202\203\202\205\201@\202d\202\201\202\222\202\224\202\210"; // Enhance Earth
const char aEffectivenessOf_800B82D0[] = "\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\202\216\202\205\202\223\202\223\201@\202\217\202\206\201@\202\206\202\211\202\222\202\205\201@\202\206\202\217\202\222\201@\202\204\202\225\202\222\202\201\202\224\202\211\202\217\202\216\201@\202\217\202\206\201@\202\202\202\201\202\224\202\224\202\214\202\205\201D"; // effectiveness of fire for duration of battle.
const char aIncreasesWaterA_800B832C[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223\201@\202\227\202\201\202\224\202\205\202\222\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\220\202\217\202\227\202\205\202\222\201@\202\201\202\216\202\204\201@\202\204\202\205\202\203\202\222\202\205\202\201\202\223\202\205\202\223"; // Increases water attack power and decreases
const char aEnhanceWater_800B8384[] = "\202d\202\216\202\210\202\201\202\216\202\203\202\205\201@\202v\202\201\202\224\202\205\202\222"; // Enhance Water
const char aEffectivenessOf_800B83A0[] = "\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\202\216\202\205\202\223\202\223\201@\202\217\202\206\201@\202\227\202\211\202\216\202\204\201@\202\206\202\217\202\222\201@\202\204\202\225\202\222\202\201\202\224\202\211\202\217\202\216\201@\202\217\202\206\201@\202\202\202\201\202\224\202\224\202\214\202\205\201D"; // effectiveness of wind for duration of battle.
const char aIncreasesFireAt_800B83FC[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223\201@\202\206\202\211\202\222\202\205\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\220\202\217\202\227\202\205\202\222\201@\202\201\202\216\202\204\201@\202\204\202\205\202\203\202\222\202\205\202\201\202\223\202\205\202\223"; // Increases fire attack power and decreases
const char aEnhanceFire_800B8450[] = "\202d\202\216\202\210\202\201\202\216\202\203\202\205\201@\202e\202\211\202\222\202\205"; // Enhance Fire
const char aCausesAnEnemyTo_800B846C[] = "\202b\202\201\202\225\202\223\202\205\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\224\202\217\201@\202\206\202\201\202\214\202\214\201@\202\204\202\205\202\201\202\204\201@\202\211\202\215\202\215\202\205\202\204\202\211\202\201\202\224\202\205\202\214\202\231\201D"; // Causes an enemy to fall dead immediately.
const char aDeath_800B84C0[] = "\202c\202\205\202\201\202\224\202\210"; // Death
const char aTurnsAnEnemyInt_800B84CC[] = "\202s\202\225\202\222\202\216\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\211\202\216\202\224\202\217\201@\202\223\202\224\202\217\202\216\202\205\201D"; // Turns an enemy into stone.
const char aFleshToStone_800B8504[] = "\202e\202\214\202\205\202\223\202\210\201@\202\224\202\217\201@\202r\202\224\202\217\202\216\202\205"; // Flesh to Stone
const char aPutsAnEnemyToSl_800B8524[] = "\202o\202\225\202\224\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\224\202\217\201@\202\223\202\214\202\205\202\205\202\220\201D"; // Puts an enemy to sleep.
const char aSleep_800B8554[] = "\202r\202\214\202\205\202\205\202\220"; // Sleep
const char aPoisonsAnEnemy_800B8560[] = "\202o\202\217\202\211\202\223\202\217\202\216\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201D"; // Poisons an enemy.
const char aPoison_800B8584[] = "\202o\202\217\202\211\202\223\202\217\202\216"; // Poison
const char aEndsOnceItProte_800B8594[] = "\202d\202\216\202\204\202\223\201@\202\217\202\216\202\203\202\205\201@\202\211\202\224\201@\202\220\202\222\202\217\202\224\202\205\202\203\202\224\202\223\201@\202\203\202\201\202\223\202\224\202\205\202\222\201@\202\224\202\210\202\222\202\205\202\205\201@\202\224\202\211\202\215\202\205\202\223\201D"; // Ends once it protects caster three times.
const char aProtectsAgainst_800B85E8[] = "\202o\202\222\202\217\202\224\202\205\202\203\202\224\202\223\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\220\202\217\202\211\202\223\202\217\202\216\201C\201@\202\223\202\214\202\205\202\205\202\220\201C\201@\202\201\202\216\202\204\201@\202\206\202\214\202\205\202\223\202\210\201@\202\224\202\217\201@\202\223\202\224\202\217\202\216\202\205\201D"; // Protects against poison, sleep, and flesh to stone.
const char aProtection_800B8650[] = "\202o\202\222\202\217\202\224\202\205\202\203\202\224\202\211\202\217\202\216"; // Protection
const char aCuresPoisonAndT_800B8668[] = "\202b\202\225\202\222\202\205\202\223\201@\202\220\202\217\202\211\202\223\202\217\202\216\201@\202\201\202\216\202\204\201@\202\224\202\225\202\222\202\216\202\223\201@\202\223\202\224\202\217\202\216\202\205\201@\202\202\202\201\202\203\202\213\201@\202\224\202\217\201@\202\206\202\214\202\205\202\223\202\210\201D"; // Cures poison and turns stone back to flesh.
const char aReturnToNormal_800B86C0[] = "\202q\202\205\202\224\202\225\202\222\202\216\201@\202\224\202\217\201@\202m\202\217\202\222\202\215\202\201\202\214"; // Return to Normal
const char aRestoresAllHP_800B86E4[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\202\223\201@\202\201\202\214\202\214\201@\202g\202o\201D"; // Restores all HP.
const char aRestoreAllHP_800B8708[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\201@\202`\202\214\202\214\201@\202g\202o"; // Restore All HP
const char aRestoresSomeHP_800B8728[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\202\223\201@\202\223\202\217\202\215\202\205\201@\202g\202o\201D"; // Restores some HP.
const char aRestoreHP_800B874C[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\201@\202g\202o"; // Restore HP
const char aCuresPoison_800B8764[] = "\202b\202\225\202\222\202\205\202\223\201@\202\220\202\217\202\211\202\223\202\217\202\216\201D"; // Cures poison.
const char aCurePoison_800B8780[] = "\202b\202\225\202\222\202\205\201@\202o\202\217\202\211\202\223\202\217\202\216"; // Cure Poison
const char aAdvancedWindAtt_800B8798[] = "\202`\202\204\202\226\202\201\202\216\202\203\202\205\202\204\201@\202v\202\211\202\216\202\204\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Advanced Wind Attack
const char aWindAttackAllEn_800B87C4[] = "\202v\202\211\202\216\202\204\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201j"; // Wind Attack (All Enemies)
const char aHigherWindEleme_800B87F8[] = "\202g\202\211\202\207\202\210\202\205\202\222\201@\202\227\202\211\202\216\202\204\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\201@\202\222\202\201\202\224\202\211\202\217\201@\202\231\202\211\202\205\202\214\202\204\202\223\201@\202\215\202\217\202\222\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205\201D"; // Higher wind element ratio yields more damage.
const char aExtraDamageVsEa_800B8854[] = "\202d\202\230\202\224\202\222\202\201\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\226\202\223\201D\201@\202d\202\201\202\222\202\224\202\210"; // Extra damage vs. Earth
const char aWindAttackOneEn_800B8884[] = "\202v\202\211\202\216\202\204\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202n\202\216\202\205\201@\202d\202\216\202\205\202\215\202\231\201j"; // Wind Attack (One Enemy)
const char aAdvancedEarthAt_800B88B4[] = "\202`\202\204\202\226\202\201\202\216\202\203\202\205\202\204\201@\202d\202\201\202\222\202\224\202\210\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Advanced Earth Attack
const char aEarthAttackAllE_800B88E0[] = "\202d\202\201\202\222\202\224\202\210\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201j"; // Earth Attack (All Enemies)
const char aHigherEarthElem_800B8918[] = "\202g\202\211\202\207\202\210\202\205\202\222\201@\202\205\202\201\202\222\202\224\202\210\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\201@\202\222\202\201\202\224\202\211\202\217\201@\202\231\202\211\202\205\202\214\202\204\202\223\201@\202\215\202\217\202\222\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205\201D"; // Higher earth element ratio yields more damage.
const char aExtraDamageVsWa_800B8978[] = "\202d\202\230\202\224\202\222\202\201\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\226\202\223\201D\201@\202v\202\201\202\224\202\205\202\222"; // Extra damage vs. Water
const char aEarthAttackOneE_800B89A8[] = "\202d\202\201\202\222\202\224\202\210\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202n\202\216\202\205\201@\202d\202\216\202\205\202\215\202\231\201j"; // Earth Attack (One Enemy)
const char aAdvancedWaterAt_800B89DC[] = "\202`\202\204\202\226\202\201\202\216\202\203\202\205\202\204\201@\202v\202\201\202\224\202\205\202\222\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Advanced Water Attack
const char aWaterAttackAllE_800B8A08[] = "\202v\202\201\202\224\202\205\202\222\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201j"; // Water Attack (All Enemies)
const char aHigherWaterElem_800B8A40[] = "\202g\202\211\202\207\202\210\202\205\202\222\201@\202\227\202\201\202\224\202\205\202\222\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\201@\202\222\202\201\202\224\202\211\202\217\201@\202\231\202\211\202\205\202\214\202\204\202\223\201@\202\215\202\217\202\222\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205\201D"; // Higher water element ratio yields more damage.
const char aExtraDamageVsFi_800B8AA0[] = "\202d\202\230\202\224\202\222\202\201\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\226\202\223\201D\201@\202e\202\211\202\222\202\205"; // Extra damage vs. Fire
const char aWaterAttackOneE_800B8ACC[] = "\202v\202\201\202\224\202\205\202\222\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202n\202\216\202\205\201@\202d\202\216\202\205\202\215\202\231\201j"; // Water Attack (One Enemy)
const char aAdvancedFireAtt_800B8B00[] = "\202`\202\204\202\226\202\201\202\216\202\203\202\205\202\204\201@\202e\202\211\202\222\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Advanced Fire Attack
const char aFireAttackAllEn_800B8B2C[] = "\202e\202\211\202\222\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201j"; // Fire Attack (All Enemies)
const char aHigherFireEleme_800B8B60[] = "\202g\202\211\202\207\202\210\202\205\202\222\201@\202\206\202\211\202\222\202\205\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\201@\202\222\202\201\202\224\202\211\202\217\201@\202\231\202\211\202\205\202\214\202\204\202\223\201@\202\215\202\217\202\222\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205\201D"; // Higher fire element ratio yields more damage.
const char aExtraDamageVsAi_800B8BBC[] = "\202d\202\230\202\224\202\222\202\201\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\226\202\223\201D\201@\202`\202\211\202\222"; // Extra damage vs. Air
const char aFireAttackOneEn_800B8BE8[] = "\202e\202\211\202\222\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202n\202\216\202\205\201@\202d\202\216\202\205\202\215\202\231\201j"; // Fire Attack (One Enemy)
const char aMakesItEasierTo_800B8C18[] = "\202l\202\201\202\213\202\205\202\223\201@\202\211\202\224\201@\202\205\202\201\202\223\202\211\202\205\202\222\201@\202\224\202\217\201@\202\213\202\211\202\214\202\214\201@\202\227\202\211\202\216\202\207\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\201\202\216\202\204"; // Makes it easier to kill winged enemies and
const char aSpecialAttackBr_800B8C70[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202a\202\222\202\205\202\201\202\213\201@\202v\202\211\202\216\202\207\202\223\201j"; // Special Attack (Break Wings)
const char aSlightlyMoreDif_800B8CAC[] = "\202\223\202\214\202\211\202\207\202\210\202\224\202\214\202\231\201@\202\215\202\217\202\222\202\205\201@\202\204\202\211\202\206\202\206\202\211\202\203\202\225\202\214\202\224\201@\202\206\202\217\202\222\201@\202\224\202\210\202\205\202\215\201@\202\224\202\217\201@\202\223\202\203\202\217\202\222\202\205\201@\202\201\201@\202\210\202\211\202\224\201D"; // slightly more difficult for them to score a hit.
const char aMakesItEasierTo_800B8D10[] = "\202l\202\201\202\213\202\205\202\223\201@\202\211\202\224\201@\202\205\202\201\202\223\202\211\202\205\202\222\201@\202\224\202\217\201@\202\213\202\211\202\214\202\214\201@\202\224\202\227\202\217\201|\202\214\202\205\202\207\202\207\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\201\202\216\202\204"; // Makes it easier to kill two-legged enemies and
const char aSpecialAttackBr_800B8D70[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202a\202\222\202\205\202\201\202\213\201@\202k\202\205\202\207\202\223\201j"; // Special Attack (Break Legs)
const char aItMoreDifficult_800B8DA8[] = "\202\211\202\224\201@\202\215\202\217\202\222\202\205\201@\202\204\202\211\202\206\202\206\202\211\202\203\202\225\202\214\202\224\201@\202\206\202\217\202\222\201@\202\224\202\210\202\205\202\215\201@\202\224\202\217\201@\202\223\202\203\202\217\202\222\202\205\201@\202\201\201@\202\210\202\211\202\224\201D"; // it more difficult for them to score a hit.
const char aReducesAnEnemie_800B8E00[] = "\202q\202\205\202\204\202\225\202\203\202\205\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202g\202o\201@\202\224\202\217\201@\202P\201@\202\201\202\216\202\204\201@\202\215\202\201\202\213\202\205\202\223"; // Reduces an enemies HP to 1 and makes
const char aSpecialAttackCr_800B8E4C[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202b\202\222\202\211\202\224\202\211\202\203\202\201\202\214\201@\202g\202\211\202\224\201j"; // Special Attack (Critical Hit)
const char aBringsEnemiesTo_800B8E88[] = "\202a\202\222\202\211\202\216\202\207\202\223\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\224\202\217\201@\202\224\202\210\202\205\201@\202\202\202\222\202\211\202\216\202\213\201@\202\217\202\206\201@\202\204\202\205\202\201\202\224\202\210\201D"; // Brings enemies to the brink of death.
const char aAttacksAllEnemi_800B8ED4[] = "\202`\202\224\202\224\202\201\202\203\202\213\202\223\201@\202\201\202\214\202\214\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\201\202\224\201@\202\217\202\216\202\203\202\205\201D"; // Attacks all enemies at once.
const char aSpecialAttackAl_800B8F10[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201j"; // Special Attack (All Enemies)
const char aUsesItToRestore_800B8F4C[] = "\202\225\202\223\202\205\202\223\201@\202\211\202\224\201@\202\224\202\217\201@\202\222\202\205\202\223\202\224\202\217\202\222\202\205\201@\202\201\202\224\202\224\202\201\202\203\202\213\202\205\202\222\201f\202\223\201@\202l\202\201\202\216\202\201\201D"; // uses it to restore attacker's Mana.
const char aStealsSomeManaF_800B8F94[] = "\202r\202\224\202\205\202\201\202\214\202\223\201@\202\223\202\217\202\215\202\205\201@\202l\202\201\202\216\202\201\201@\202\206\202\222\202\217\202\215\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\201\202\216\202\204"; // Steals some Mana from an enemy and
const char aSpecialAttackAb_800B8FDC[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\202\202\223\202\217\202\222\202\202\201@\202l\202\201\202\216\202\201\201j"; // Special Attack (Absorb Mana)
const char aAnEnemyToRestor_800B9018[] = "\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\224\202\217\201@\202\222\202\205\202\223\202\224\202\217\202\222\202\205\201@\202\224\202\210\202\205\201@\202\201\202\224\202\224\202\201\202\203\202\213\202\205\202\222\201f\202\223\201@\202g\202o\201D"; // an enemy to restore the attacker's HP.
const char aTakesSomeOfTheD_800B9068[] = "\202s\202\201\202\213\202\205\202\223\201@\202\223\202\217\202\215\202\205\201@\202\217\202\206\201@\202\224\202\210\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\211\202\216\202\206\202\214\202\211\202\203\202\224\202\205\202\204\201@\202\217\202\216"; // Takes some of the damage inflicted on
const char aSpecialAttackAb_800B90B4[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\202\202\223\202\217\202\222\202\202\201@\202g\202o\201j"; // Special Attack (Absorb HP)
const char aMoreDifficultFo_800B90EC[] = "\202\215\202\217\202\222\202\205\201@\202\204\202\211\202\206\202\206\202\211\202\203\202\225\202\214\202\224\201@\202\206\202\217\202\222\201@\202\224\202\210\202\205\202\215\201@\202\224\202\217\201@\202\223\202\203\202\217\202\222\202\205\201@\202\201\201@\202\210\202\211\202\224\201D"; // more difficult for them to score a hit.
const char aCausesAnEnemyTo_800B913C[] = "\202b\202\201\202\225\202\223\202\205\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\224\202\217\201@\202\214\202\217\202\223\202\205\201@\202l\202\201\202\216\202\201\201@\202\201\202\216\202\204\201@\202\215\202\201\202\213\202\205\202\223\201@\202\211\202\224\201@\202\223\202\214\202\211\202\207\202\210\202\224\202\214\202\231"; // Causes an enemy to lose Mana and makes it slightly
const char aSpecialAttackDe_800B91A4[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202c\202\205\202\223\202\224\202\222\202\217\202\231\201@\202l\202\201\202\216\202\201\201j"; // Special Attack (Destroy Mana)
const char aPhysicallyDamag_800B91E0[] = "\202o\202\210\202\231\202\223\202\211\202\203\202\201\202\214\202\214\202\231\201@\202\204\202\201\202\215\202\201\202\207\202\205\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\201\202\216\202\204\201@\202\224\202\225\202\222\202\216\202\223\201@\202\224\202\210\202\205\202\215\201@\202\224\202\217\201@\202\223\202\224\202\217\202\216\202\205\201D"; // Physically damages an enemy and turns them to stone.
const char aSpecialFleshToS_800B924C[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202e\202\214\202\205\202\223\202\210\201|\202\224\202\217\201|\202r\202\224\202\217\202\216\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Flesh-to-Stone Attack
const char aPhysicallyDamag_800B9288[] = "\202o\202\210\202\231\202\223\202\211\202\203\202\201\202\214\202\214\202\231\201@\202\204\202\201\202\215\202\201\202\207\202\205\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\201\202\216\202\204\201@\202\220\202\225\202\224\202\223\201@\202\224\202\210\202\205\202\215\201@\202\224\202\217\201@\202\223\202\214\202\205\202\205\202\220\201D"; // Physically damages an enemy and puts them to sleep.
const char aSpecialSleepAtt_800B92F0[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202r\202\214\202\205\202\205\202\220\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Sleep Attack
const char aPhysicallyDamag_800B931C[] = "\202o\202\210\202\231\202\223\202\211\202\203\202\201\202\214\202\214\202\231\201@\202\204\202\201\202\215\202\201\202\207\202\205\202\223\201@\202\201\202\216\202\204\201@\202\220\202\217\202\211\202\223\202\217\202\216\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201D"; // Physically damages and poisons an enemy.
const char aSpecialPoisonAt_800B9370[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202o\202\217\202\211\202\223\202\217\202\216\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Poison Attack
const char aVeryEffectiveAg_800B939C[] = "\202u\202\205\202\222\202\231\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\205\202\201\202\222\202\224\202\210\201|\202\202\202\201\202\223\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Very effective against earth-based enemies.
const char aSpecialWindAtta_800B93F4[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202v\202\211\202\216\202\204\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Wind Attack
const char aVeryEffectiveAg_800B941C[] = "\202u\202\205\202\222\202\231\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\227\202\211\202\216\202\204\201|\202\202\202\201\202\223\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Very effective against wind-based enemies.
const char aSpecialFireAtta_800B9474[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202e\202\211\202\222\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Fire Attack
const char aVeryEffectiveAg_800B949C[] = "\202u\202\205\202\222\202\231\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\206\202\211\202\222\202\205\201|\202\202\202\201\202\223\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Very effective against fire-based enemies.
const char aSpecialWaterAtt_800B94F4[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202v\202\201\202\224\202\205\202\222\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Water Attack
const char aVeryEffectiveAg_800B9520[] = "\202u\202\205\202\222\202\231\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\227\202\201\202\224\202\205\202\222\201|\202\202\202\201\202\223\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Very effective against water-based enemies.
const char aSpecialEarthAtt_800B9578[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202d\202\201\202\222\202\224\202\210\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Earth Attack

void MergeMagic_800BAA0C(Minion* out, Minion* partner)
{
    unsigned int old = out->magicBits_F4;
    unsigned int* bits = &out->magicBits_F4;
    int i;
    unsigned int mask;
    if (CanInheritMagic_800BAB30(partner))
    {
        old |= partner->magicBits_F4;
    }
    mask = out->status_84.elementMask_42;
    out->magicBits_F4 = old;
    for (i = 0; i < 30; i++)
    {
        if (TestMagicBit_8001AE2C(bits, i) && (mask & (1 << GetMagicElement_8001AD30(i))) == 0)
        {
            ClearMagicBit_8001AE00(bits, i);
        }
    }
    if ((char)out->status_84.element_3E[0] != 0x20)
    {
        ClearMagicBit_8001AE00(bits, 0x15);
    }
    if ((char)out->status_84.element_3E[2] != 0x20)
    {
        ClearMagicBit_8001AE00(bits, 0x17);
    }
    if ((char)out->status_84.element_3E[1] != 0x20)
    {
        ClearMagicBit_8001AE00(bits, 0x18);
    }
    if ((char)out->status_84.element_3E[3] != 0x20)
    {
        ClearMagicBit_8001AE00(bits, 0x16);
    }
}

int CanInheritMagic_800BAB30(Minion* minion)
{
    return 1;
}

// Matched
void MergeSpeciesHistory_800BAB38(Minion* out, Minion* partner)
{
    unsigned char tmp[0x30];
    unsigned int names[18];
    unsigned char elements[6];
    int i;
    int j;
    for (i = 0; i < 0x30; i++)
    {
        if (i < 0x20)
        {
            if (i * 2 < 0x30)
            {
                tmp[i] = out->species_4C[i * 2];
            }
            else
            {
                tmp[i] = out->species_4C[(i - 0x18) * 6 + 1];
            }
        }
        else
        {
            tmp[i] = partner->species_4C[(i - 0x20) * 3];
        }
    }
    MemCopy_800403E8(out->species_4C, tmp, 0x30);
    CopyName_80019AF4(names, (unsigned int*)out->status_84.name_10);
    CopyName_80019AF4(names + 3, (unsigned int*)partner->status_84.name_10);
    CopyName_80019AF4(names + 6, (unsigned int*)out->ancestors_4[0]);
    CopyName_80019AF4(names + 9, (unsigned int*)out->ancestors_4[1]);
    CopyName_80019AF4(names + 12, (unsigned int*)partner->ancestors_4[0]);
    CopyName_80019AF4(names + 15, (unsigned int*)partner->ancestors_4[1]);
    for (j = 0; j < 6; j++)
    {
        CopyName_80019AF4((unsigned int*)out->ancestors_4[j], names + j * 3);
    }
    elements[0] = out->status_84.elementMask_42;
    elements[1] = partner->status_84.elementMask_42;
    elements[2] = out->ancestorElements_7C[0];
    elements[3] = out->ancestorElements_7C[1];
    elements[4] = partner->ancestorElements_7C[0];
    elements[5] = partner->ancestorElements_7C[1];
    for (i = 0; i < 6; i++)
    {
        out->ancestorElements_7C[i] = elements[i];
    }
}

int GetSpecialMergeSpecies_800BACD0(Minion* minion)
{
    int species = -1;
    int n6 = 0;
    int n5 = n6;
    int n4 = n6;
    int n3 = n6;
    int n2 = n6;
    int n1 = n6;
    int i = n6;
    unsigned char ancestor;
    for (; i < 0x30; i++)
    {
        ancestor = minion->species_4C[i];
        if (ancestor == 0x1E || ancestor == 0xB1 || ancestor == 0xB2 || ancestor == 0xB3 || ancestor == 0xB4)
        {
            n1++;
        }
        else if (ancestor == 0xE || ancestor == 0x71 || ancestor == 0x72 || ancestor == 0x73 || ancestor == 0x74)
        {
            n2++;
        }
        else if (ancestor == 0xF || ancestor == 0x75 || ancestor == 0x76 || ancestor == 0x77 || ancestor == 0x78)
        {
            n3++;
        }
        else if (ancestor == 3 || ancestor == 0x45 || ancestor == 0x46 || ancestor == 0x47 || ancestor == 0x48)
        {
            n4++;
        }
        else if (ancestor == 7 || ancestor == 0x55 || ancestor == 0x56 || ancestor == 0x57 || ancestor == 0x58)
        {
            n5++;
        }
        else if (ancestor == 9 || ancestor == 0x5D || ancestor == 0x5E || ancestor == 0x5F || ancestor == 0x60)
        {
            n6++;
        }
    }
    if (n1 >= 3 && n2 >= 3 && n3 >= 3)
    {
        species = 0x22;
    }
    else if (n4 >= 3 && n5 >= 3 && n3 >= 3 && n6 >= 3)
    {
        species = 0x23;
    }
    return species;
}

// the silk thread item a spun minion yields
int GetSilkItemForLevel_800BAE80(Minion* minion)
{
    unsigned int level = minion->status_84.level_44;
    int item;
    if (level < 4)
    {
        item = 0x21;
    }
    else if (level < 7)
    {
        item = 0x22;
    }
    else if (level < 12)
    {
        item = 0x23;
    }
    else if (level < 18)
    {
        item = 0x24;
    }
    else if (level < 25)
    {
        item = 0x25;
    }
    else if (level < 31)
    {
        item = 0x26;
    }
    else
    {
        item = 0x27;
    }
    return item;
}

void SwapMinions_800BAEDC(Minion* first, Minion* second)
{
    unsigned int t1[0x3E];
    unsigned int t2[0x3E];
    MemCopy_800403E8(t1, first, 0xF8);
    MemCopy_800403E8(t2, second, 0xF8);
    MemCopy_800403E8(first, t2, 0xF8);
    MemCopy_800403E8(second, t1, 0xF8);
}

// Exchange two minions between the party/storage lists, fixing up their list kinds (2/3/4) first; each case calls SwapMinions
// itself (the separate calls are what lets jump2 cross-jump the *first = 3 stores)
// Matched
int ExchangeMinions_800BAF54(short* first, short* second, short firstList, short secondList)
{
    if (*first == 3)
    {
        if (*second == 2)
        {
            *first = 2;
            *second = 3;
        }
        else if (*second == 4 && secondList == 2)
        {
            *first = 2;
        }
        SwapMinions_800BAEDC(first, second);
    }
    else if (*first == 2)
    {
        if (*second == 3)
        {
            *second = 2;
            *first = 3;
        }
        else if (*second == 4 && secondList == 3)
        {
            *first = 3;
        }
        SwapMinions_800BAEDC(first, second);
    }
    else if (*first == 4)
    {
        if (firstList == 3)
        {
            if (*second == 2 && secondList == 2)
            {
                *second = 3;
            }
        }
        else if (firstList == 2)
        {
            if (*second == 3 && secondList == 3)
            {
                *second = 2;
            }
        }
        SwapMinions_800BAEDC(first, second);
    }
    return 1;
}

void StartShop_800BB058(int shopId)
{
    EventEntry* task = AllocEventEntry_80043AF8(shopMenuTask_8008D670);
    ShopMenu* menu;
    if (task)
    {
        menu = task->buffer;
        task->flags = (task->flags | 1) & ~0x8000;
        SetFontClutOffset_8003F900(2, 0);
        SetFontClutOffset_8003F900(1, 0);
        DrawMenuBackground_8002BE10();
        menu->shopId_96 = shopId;
        InitShopMenu_800BB148(menu);
        DrawShopMenu_800BC380(menu);
        task->cb_8 = ShopFadeIn_800BB0F8;
    }
}

void ShopFadeIn_800BB0F8(EventEntry* task, void* buffer)
{
    ShopMenu* menu = buffer;
    DrawMenuBackground_8002BE10();
    DrawShopMenu_800BC380(menu);
    SetFadeMode_8001C19C(3, 0x20);
    task->cb_8 = ShopMenuTask_800BB444;
}

// Matched
void InitShopMenu_800BB148(ShopMenu* menu)
{
    short i;
    void* r;
    Minion* mn;
    menu->state_0 = 0;
    menu->prevState_2 = -2;
    for (i = 0; i < 10; i++)
    {
        menu->savedIndex_5E[i] = 0;
    }
    for (i = 0; i < 4; i++)
    {
        menu->savedScroll_72[i] = 0;
    }
    for (i = 0; i < 2; i++)
    {
        menu->savedList_7A[i] = 0;
    }
    menu->tabCols_34 = 3;
    menu->tabRows_36 = 1;
    menu->tabCount_38 = 3;
    menu->tabFlags_3A = 1;
    menu->pageCols_40 = 1;
    menu->pageRows_42 = 1;
    menu->pageCount_44 = 1;
    menu->pageFlags_46 = 0x40;
    menu->marks_84 = 0;
    menu->partyMarks_88 = 0;
    menu->storedMarks_8C = 0;
    menu->field_90 = 0;
    menu->markCount_80 = 0;
    menu->fadeAction_94 = 0;
    menu->listScroll_32 = 0;
    menu->listIndex_30 = 0;
    menu->tabScroll_3E = 0;
    menu->tabIndex_3C = 0;
    menu->pageScroll_4A = 0;
    menu->pageIndex_48 = 0;
    menu->base_4C = 0;
    menu->partner_50 = 0;
    menu->shown_54 = 0;
    menu->storedScroll_5C = 0;
    menu->storedIndex_5A = 0;
    menu->partyIndex_58 = 0;
    menu->messageShown_18 = 0;
    menu->errorId_8 = 0;
    menu->cancel_14 = 0;
    menu->confirm_10 = 0;
    menu->openTimer_C = 0;
    menu->messageTimer_98 = 0;
    menu->list_7E = 0;
    menu->flags_24 = 1;
    menu->windows_1C = 0;
    menu->windows_1C = stateWindows_800BF8B4[menu->state_0];
    menu->windowsOpen_20 = 0;
    SetShopHelpText_800BBB54(menu, 0);
    SetupShopCursor_800BD854(menu);
    fn_80011CD0(&levantStatus_8008BD38);
    for (i = 0; i < 12; i++)
    {
        r = GetSaveItem_80033AE4(&saveData_8008B570, i);
        if (r)
        {
            fn_80011CD0(r);
        }
    }
    for (i = 0; i < 3; i++)
    {
        mn = GetMinion_80010598(3, i);
        if (mn)
        {
            fn_80011CD0(&mn->status_84);
        }
    }
    BuildShopMinionList_800B9920();
    AddEmptyCocoons_800AD8F4(GetFreeCocoonSlots_800AD888());
}

int CanViewForm_800BB38C(ShopMenu* menu)
{
    switch (menu->state_0)
    {
    case 5:
        if (menu->marks_84)
        {
            break;
        }
    case 1:
    case 2:
    case 7:
    case 8:
    case 10:
        return 1;
    }
    return 0;
}

int CanRearrange_800BB3E8(ShopMenu* menu)
{
    switch (menu->state_0)
    {
    case 5:
        if (menu->marks_84 == 0)
        {
    case 1:
    case 7:
            return 1;
        }
    }
    return 0;
}

void ShopMenuTask_800BB444(EventEntry* task, void* buffer)
{
    ShopMenu* menu = buffer;
    short old;
    int r;
    DrawMenuBackground_8002BE10();
    if (menu->flags_24 & 1)
    {
        menu->storedCount_4 = CountShopMinionsInState_800B9C78(2);
        menu->partyCount_6 = CountShopMinionsInState_800B9C78(3);
        menu->flags_24 &= ~1;
    }
    if (menu->state_0 != 15 && !(menu->flags_24 & 0x400))
    {
        menu->flags_24 &= ~0x1C0;
    }
    if ((menu->flags_24 & 2) || menu->state_0 == 11 || menu->state_0 == 12)
    {
        DrawNextPrompt_8003CF88(0x11E, 0x3C, 0xE);
    }
    if (menu->messageShown_18 == 0)
    {
        SaveShopCursor_800BB798(menu);
        UpdateSelectedMinions_800BEBC8(menu);
        UpdateShownMinion_800BECC8(menu);
    }
    DrawShopMenu_800BC380(menu);
    if (menu->messageShown_18 == 0)
    {
        SaveShopCursor_800BB798(menu);
        UpdateMainMenuHelp_800BBAAC(menu);
        if (menu->confirm_10 || menu->cancel_14)
        {
            HandleShopConfirmCancel_800BD0D4(menu);
        }
        if (!(menu->flags_24 & 4))
        {
            if (menu->state_0 == 3 && (menu->flags_24 & 2))
            {
                old = menu->tabIndex_3C;
                UpdateMenuCursor_8003D794(&menu->tabCols_34, 0);
                if (menu->tabIndex_3C != old)
                {
                    menu->pageCols_40 = 1;
                    menu->pageRows_42 = 1;
                    menu->pageCount_44 = 1;
                    menu->pageFlags_46 = 0;
                    menu->pageScroll_4A = 0;
                    menu->pageIndex_48 = 0;
                    if (menu->flags_24 & 0x40)
                    {
                        menu->pageCount_44 = 5;
                        menu->pageRows_42 = 5;
                    }
                    else if (menu->flags_24 & 0x80)
                    {
                        UpdateShownMinion_800BECC8(menu);
                        r = CountMagicBits_8001AE54(&menu->shown_54->magicBits_F4);
                        if (r < 4)
                        {
                            r = 4;
                        }
                        menu->pageRows_42 = 4;
                        menu->pageCols_40 = 1;
                        menu->pageCount_44 = r;
                        menu->pageFlags_46 = 0x40;
                    }
                }
                if (menu->flags_24 & 0x400)
                {
                    UpdateMenuCursor_8003D794(&menu->pageCols_40, 0);
                }
            }
            if (!(menu->flags_24 & 2))
            {
                ShopMenuInput_800BBE24(menu);
                if (menu->state_0 == 8 || CanViewForm_800BB38C(menu))
                {
                    if (padPressed_8009194C[0] & 0x20)
                    {
                        if (menu->base_4C->id != 4)
                        {
                            menu->flags_24 = (menu->flags_24 | 0x20) & ~0x400;
                            menu->flags_24 &= ~0x1C0;
                            StartFormView_800BE2B4(menu->shown_54);
                        }
                    }
                }
            }
            else
            {
                DismissShopPrompt_800BC2DC(menu);
                if (menu->state_0 == 3)
                {
                    if (padPressed_8009194C[0] & 0x20)
                    {
                        if (menu->base_4C->id != 4)
                        {
                            menu->flags_24 = (menu->flags_24 | 0x20) & ~0x400;
                            menu->flags_24 &= ~0x1C0;
                            StartFormView_800BE2B4(menu->shown_54);
                        }
                    }
                    else if (padPressed_8009194C[0] & 0x80)
                    {
                        menu->flags_24 |= 0x400;
                        CycleInfoPage_800BC1A8(menu);
                    }
                }
                else if (CanViewForm_800BB38C(menu))
                {
                    if (padPressed_8009194C[0] & 0x20)
                    {
                        if (menu->base_4C->id != 4)
                        {
                            menu->flags_24 = (menu->flags_24 | 0x20) & ~0x400;
                            menu->flags_24 &= ~0x1C0;
                            StartFormView_800BE2B4(menu->shown_54);
                        }
                    }
                }
            }
        }
        else
        {
            task->flags = (task->flags & ~1) | 0x8000;
            ShopCtrlRequestExit_800B6CB8();
        }
    }
    else
    {
        ShopWaitMessage_800BBA3C(menu);
    }
    if (menu->openTimer_C < 8)
    {
        menu->openTimer_C++;
    }
}

void SaveShopCursor_800BB798(ShopMenu* menu)
{
    short a;
    unsigned short b;
    unsigned short c;
    a = stateIndexSlots_800BFD1C[menu->state_0];
    b = stateScrollSlots_800BFD3C[menu->state_0];
    c = stateListSlots_800BFD5C[menu->state_0];
    if (a >= 0)
    {
        menu->savedIndex_5E[a] = menu->listIndex_30;
    }
    if ((short)b >= 0)
    {
        menu->savedScroll_72[(short)b] = menu->listScroll_32;
    }
    if ((short)c >= 0)
    {
        menu->savedList_7A[(short)c] = menu->list_7E;
    }
}

void RestoreShopCursor_800BB828(ShopMenu* menu)
{
    unsigned short b;
    short a;
    unsigned short c;
    a = stateIndexSlots_800BFD1C[menu->state_0];
    b = stateScrollSlots_800BFD3C[menu->state_0];
    c = stateListSlots_800BFD5C[menu->state_0];
    if (a >= 0)
    {
        menu->listIndex_30 = menu->savedIndex_5E[a];
    }
    if ((short)b >= 0)
    {
        menu->listScroll_32 = menu->savedScroll_72[(short)b];
    }
    if ((short)c >= 0)
    {
        menu->list_7E = menu->savedList_7A[(short)c];
    }
}

void ShopMenuBack_800BB8C4(ShopMenu* menu)
{
    short s = menu->state_0;
    short t;
    if (s == 0)
    {
        if (menu->listIndex_30 != 4)
        {
            menu->listIndex_30 = 4;
        }
        else
        {
            if (menu->storedCount_4 >= 13)
            {
                menu->state_0 = 12;
            }
            else
            {
                menu->state_0 = 11;
            }
        }
    }
    else if (s == 3)
    {
        menu->state_0 = 2;
        menu->prevState_2 = 1;
        menu->flags_24 &= ~0x200;
        menu->listIndex_30 = menu->savedIndex_5E[2];
        menu->listScroll_32 = menu->savedScroll_72[1];
    }
    else if (s == 4)
    {
        menu->state_0 = 0;
        menu->listScroll_32 = 0;
        menu->listIndex_30 = 0;
    }
    else if (s == 12)
    {
        menu->state_0 = 0;
    }
    else if (s == 11)
    {
        menu->flags_24 |= 4;
    }
    else if (s == 13)
    {
        PreviewMerge_800BD720(menu);
        menu->state_0 = 3;
        menu->prevState_2 = 2;
    }
    else if (s == 14)
    {
        menu->state_0 = 13;
        menu->prevState_2 = 2;
    }
    else
    {
        if (s == 2 || s == 10)
        {
            menu->list_7E = menu->savedList_7A[0];
        }
        t = menu->prevState_2;
        menu->state_0 = t;
        menu->prevState_2 = stateParents_800BF888[t];
        RestoreShopCursor_800BB828(menu);
    }
}

void ShopWaitMessage_800BBA3C(ShopMenu* menu)
{
    if (menu->messageTimer_98 < 0x96)
    {
        menu->messageTimer_98 += 1;
    }
    if (padPressed_8009194C[0] != 0 || menu->messageTimer_98 >= 0x96)
    {
        SetShopHelpText_800BBB54(menu, 0);
        menu->messageShown_18 = 0;
        menu->messageTimer_98 = 0;
    }
}

void UpdateMainMenuHelp_800BBAAC(ShopMenu* menu)
{
    short i;
    if (menu->state_0 == 0)
    {
        for (i = 0; i < 3; i++)
        {
            if (menu->shopId_96 == 4)
            {
                dialogLines_800BF7C8[i].text_4 = mainHelpTextsA_800BFCF4[menu->listIndex_30][i];
            }
            else
            {
                dialogLines_800BF7C8[i].text_4 = mainHelpTextsB_800BFD08[menu->listIndex_30][i];
            }
        }
    }
}

void SetShopHelpText_800BBB54(ShopMenu* menu, int mode)
{
    switch ((short)mode)
    {
    case 1:
        if (menu->shopId_96 == 4)
        {
            dialogLines_800BF7C8[0].text_4 = errorTextsA_800BFC04[menu->errorId_8][0];
            dialogLines_800BF7C8[1].text_4 = errorTextsA_800BFC04[menu->errorId_8][1];
            dialogLines_800BF7C8[2].text_4 = errorTextsA_800BFC04[menu->errorId_8][2];
        }
        else
        {
            dialogLines_800BF7C8[0].text_4 = errorTextsB_800BFC68[menu->errorId_8][0];
            dialogLines_800BF7C8[1].text_4 = errorTextsB_800BFC68[menu->errorId_8][1];
            dialogLines_800BF7C8[2].text_4 = errorTextsB_800BFC68[menu->errorId_8][2];
        }
        break;
    case 3:
        if (menu->shopId_96 == 4)
        {
            dialogLines_800BF7C8[0].text_4 = resultTextsA_800BFB34[menu->state_0][0];
            dialogLines_800BF7C8[1].text_4 = resultTextsA_800BFB34[menu->state_0][1];
            dialogLines_800BF7C8[2].text_4 = resultTextsA_800BFB34[menu->state_0][2];
        }
        else
        {
            dialogLines_800BF7C8[0].text_4 = resultTextsB_800BFB74[menu->state_0][0];
            dialogLines_800BF7C8[1].text_4 = resultTextsB_800BFB74[menu->state_0][1];
            dialogLines_800BF7C8[2].text_4 = resultTextsB_800BFB74[menu->state_0][2];
        }
        break;
    case 2:
        if (menu->shopId_96 == 4)
        {
            dialogLines_800BF7C8[0].text_4 = textStatsReturnA_800BF9B8[0];
            dialogLines_800BF7C8[1].text_4 = textStatsReturnA_800BF9B8[1];
            dialogLines_800BF7C8[2].text_4 = textStatsReturnA_800BF9B8[2];
        }
        else
        {
            dialogLines_800BF7C8[0].text_4 = textStatsReturnB_800BFAA8[0];
            dialogLines_800BF7C8[1].text_4 = textStatsReturnB_800BFAA8[1];
            dialogLines_800BF7C8[2].text_4 = textStatsReturnB_800BFAA8[2];
        }
        break;
    default:
        if (menu->state_0 == 0)
        {
            if (menu->shopId_96 == 4)
            {
                dialogLines_800BF7C8[0].text_4 = mainHelpTextsA_800BFCF4[menu->listIndex_30][0];
                dialogLines_800BF7C8[1].text_4 = mainHelpTextsA_800BFCF4[menu->listIndex_30][1];
                dialogLines_800BF7C8[2].text_4 = mainHelpTextsA_800BFCF4[menu->listIndex_30][2];
            }
            else
            {
                dialogLines_800BF7C8[0].text_4 = mainHelpTextsB_800BFD08[menu->listIndex_30][0];
                dialogLines_800BF7C8[1].text_4 = mainHelpTextsB_800BFD08[menu->listIndex_30][1];
                dialogLines_800BF7C8[2].text_4 = mainHelpTextsB_800BFD08[menu->listIndex_30][2];
            }
        }
        else
        {
            if (menu->shopId_96 == 4)
            {
                dialogLines_800BF7C8[0].text_4 = stateTextsA_800BFAB4[menu->state_0][0];
                dialogLines_800BF7C8[1].text_4 = stateTextsA_800BFAB4[menu->state_0][1];
                dialogLines_800BF7C8[2].text_4 = stateTextsA_800BFAB4[menu->state_0][2];
            }
            else
            {
                dialogLines_800BF7C8[0].text_4 = stateTextsB_800BFAF4[menu->state_0][0];
                dialogLines_800BF7C8[1].text_4 = stateTextsB_800BFAF4[menu->state_0][1];
                dialogLines_800BF7C8[2].text_4 = stateTextsB_800BFAF4[menu->state_0][2];
            }
        }
        break;
    }
}

// Matched
void ShopMenuInput_800BBE24(ShopMenu* menu)
{
    int snd;
    int r;
    int k;
    unsigned int bit;
    unsigned int marks;
    if (menu->flags_24 & 8)
    {
        UpdateSelectedMinions_800BEBC8(menu);
        snd = 0;
        r = (short)UpdateMenuCursor_8003D794(&menu->listCols_28, snd);
        if (r == 4)
        {
            menu->listCols_28 = 1;
            menu->listCount_2C = 0x18;
            menu->list_7E = 1;
            menu->flags_24 &= ~0x10;
            menu->listRows_2A = r;
            menu->listFlags_2E = 0x50;
            menu->listIndex_30 = 0;
            SaveShopCursor_800BB798(menu);
            snd = 1;
        }
        else if (r == 3)
        {
            menu->listCols_28 = 1;
            snd = 1;
            menu->listFlags_2E = 0x20;
            menu->listRows_2A = r;
            menu->listCount_2C = r;
            menu->listIndex_30 = 2;
            menu->list_7E = 0;
            menu->flags_24 |= 0x10;
            SaveShopCursor_800BB798(menu);
        }
        if (snd)
        {
            PlaySfx_80031494(0x7F);
        }
    }
    else
    {
        UpdateMenuCursor_8003D794(&menu->listCols_28, 0);
    }
    if (menu->state_0 == 15)
    {
        UpdateMenuCursor_8003D794(&menu->pageCols_40, 0);
    }
    if (IsConfirmPressedP1_8003D380(0))
    {
        if (menu->state_0 != 5)
        {
            if (IsNoChosen_800BD6C4(menu))
            {
                menu->cancel_14 = 1;
            }
            else if (menu->state_0 == 2 || menu->state_0 == 10)
            {
                if (menu->base_4C == menu->partner_50)
                {
                    menu->cancel_14 = 1;
                }
                else
                {
                    menu->confirm_10 = 1;
                }
            }
            else
            {
                menu->confirm_10 = 1;
            }
        }
        else
        {
            if (menu->base_4C->id != 4)
            {
                if (menu->flags_24 & 0x10)
                {
                    bit = 1 << (short)(menu->listIndex_30 + menu->listScroll_32);
                    if (!(menu->partyMarks_88 & bit))
                    {
                        menu->partyMarks_88 |= bit;
                        menu->marks_84 |= bit;
                        menu->markCount_80++;
                    }
                    else
                    {
                        menu->partyMarks_88 &= ~bit;
                        menu->marks_84 &= ~bit;
                        menu->markCount_80--;
                    }
                }
                else
                {
                    k = (short)(menu->listIndex_30 + menu->listScroll_32);
                    bit = 1 << k;
                    marks = menu->storedMarks_8C;
                    if (!(marks & bit))
                    {
                        menu->storedMarks_8C |= bit;
                        menu->marks_84 |= 1 << (k + 3);
                        menu->markCount_80++;
                    }
                    else
                    {
                        menu->storedMarks_8C &= ~bit;
                        menu->marks_84 &= ~(1 << (k + 3));
                        menu->markCount_80--;
                    }
                }
                PlaySfx_80031494(0x7E);
            }
        }
    }
    else if (IsCancelPressedP1_8003D41C(0))
    {
        menu->cancel_14 = 1;
    }
    else if (padPressed_8009194C[0] & 0x80)
    {
        if (menu->state_0 == 8)
        {
            menu->pageCols_40 = 1;
            menu->pageRows_42 = 1;
            menu->pageCount_44 = 1;
            menu->pageFlags_46 = 0;
            menu->pageScroll_4A = 0;
            menu->pageIndex_48 = 0;
            menu->confirm_10 = 1;
            menu->flags_24 |= 0x400;
        }
        else if (menu->state_0 == 15)
        {
            CycleInfoPage_800BC1A8(menu);
        }
        else if (CanRearrange_800BB3E8(menu) && CompactStoredMinions_800B97B0())
        {
            PlaySfx_80031494(0x7E);
        }
    }
    else if (padPressed_8009194C[0] & 0x20)
    {
        if (menu->markCount_80 > 0 && menu->state_0 == 5)
        {
            menu->confirm_10 = 1;
        }
    }
}

void CycleInfoPage_800BC1A8(ShopMenu* menu)
{
    int fl;
    int r;
    int t;
    if (menu->shown_54->id != 4)
    {
        fl = menu->flags_24;
        menu->pageCols_40 = 1;
        menu->pageRows_42 = 1;
        menu->pageCount_44 = 1;
        menu->pageFlags_46 = 0;
        menu->pageScroll_4A = 0;
        menu->pageIndex_48 = 0;
        if ((fl & 0x1C0) == 0)
        {
            menu->flags_24 = fl | 0x40;
            menu->pageCount_44 = 5;
            menu->pageRows_42 = 5;
        }
        else if (fl & 0x40)
        {
            t = fl & ~0x40;
            t &= ~0x100;
            menu->flags_24 = t | 0x80;
            r = CountMagicBits_8001AE54(&menu->shown_54->magicBits_F4);
            if (r < 4)
            {
                r = 4;
            }
            menu->pageCols_40 = 1;
            menu->pageRows_42 = 4;
            menu->pageCount_44 = r;
            menu->pageFlags_46 = 0x40;
        }
        else if (fl & 0x80)
        {
            int t2 = fl & ~0x40;
            t2 &= ~0x80;
            menu->flags_24 = t2 | 0x100;
        }
        else if (fl & 0x100)
        {
            int fl2 = fl & ~0x100;
            menu->flags_24 = fl2;
            if (menu->state_0 == 3 && (fl & 2))
            {
                menu->flags_24 = fl2 & ~0x400;
            }
        }
        PlaySfx_80031494(0x7F);
    }
}

void DismissShopPrompt_800BC2DC(ShopMenu* menu)
{
    if (IsConfirmPressedP1_8003D380(0) || IsCancelPressedP1_8003D41C(0))
    {
        int fl = menu->flags_24;
        if ((fl & 0x400) && menu->state_0 == 3 && (fl & 2))
        {
            PlaySfx_80031494(0x7D);
            menu->flags_24 &= ~0x400;
        }
        else
        {
            PlaySfx_80031494(0x7E);
            SetShopHelpText_800BBB54(menu, 0);
            menu->flags_24 &= ~2;
        }
    }
}

// Matched
void DrawShopMenu_800BC380(ShopMenu* menu)
{
    Pos16 pos;
    WindowStyle win;
    short i;
    short j;
    short openStep;
    int hasDesc;
    int time;
    if (menu->flags_24 & 0x40)
    {
        hasDesc = 0;
        if (menu->shown_54->skills_DE.slot[menu->pageIndex_48].flags_0 & 1)
        {
            hasDesc = 0 < menu->shown_54->skills_DE.slot[menu->pageIndex_48].id_1;
        }
        if (IsCircleHeldP1_8003D480() && hasDesc)
        {
            menu->flags_24 |= 0x1000;
        }
        else
        {
            menu->flags_24 &= ~0x1000;
        }
    }
    else if (menu->flags_24 & 0x80)
    {
        j = menu->pageIndex_48 + menu->pageScroll_4A;
        hasDesc = FindNthMagicBit_8001AEC0(&menu->shown_54->magicBits_F4, j) < 0x1E;
        if (IsCircleHeldP1_8003D480() && hasDesc)
        {
            menu->flags_24 |= 0x1000;
        }
        else
        {
            menu->flags_24 &= ~0x1000;
        }
    }
    if (menu->state_0 == 3 && (menu->flags_24 & 2))
    {
        menu->flags_24 &= ~0x1000;
    }
    if (!(menu->flags_24 & 0x1000))
    {
        DrawPortraitWindow_8002A4E4(0xE);
        DrawTextList_8002A310(dialogLines_800BF7C8, 0xE);
        DrawWindowBackground_800429F8((int)&dialogWindowRect_800BF798, 0xE);
        DrawWindowBorder_80042B38((int)&dialogWindowRect_800BF798, 0xE);
    }
    else
    {
        pos.x = 10;
        pos.y = 0x12;
        if (menu->flags_24 & 0x40)
        {
            DrawAbilityDescription_8002C670(menu->shown_54, &pos, abilityDescLines_800C044C, menu->pageIndex_48, 0xE);
        }
        else if (menu->flags_24 & 0x80)
        {
            DrawLargeTextBox_8002AF10(magicDescLines_800C026C[FindNthMagicBit_8001AEC0(&menu->shown_54->magicBits_F4, menu->pageIndex_48 + menu->pageScroll_4A)], &pos, 0xE);
        }
    }
    if (menu->windows_1C & 2)
    {
        pos.x = partyLabelRect_800BF7A0.x + 5;
        pos.y = partyLabelRect_800BF7A0.y + 3;
        pos.x = partyLabelRect_800BF7A0.x + 3;
        DrawUiTiySprt_8002C06C(&pos, 0xB5, 0xE);
        win.semiTrans_3 = 1;
        win.colorSet_2 = 0;
        win.color_0 = saveData_8008B570.uiColor_20.h;
        DrawWindow_80042460(&partyLabelRect_800BF7A0, &win, pOT_8008D454 + 0xE, 0);
        pos.x = storedLabelRect_800BF7A8.x + 5;
        pos.y = storedLabelRect_800BF7A8.y + 3;
        pos.x = storedLabelRect_800BF7A8.x + 4;
        DrawUiTiySprt_8002C06C(&pos, 0xE, 0xE);
        DrawWindow_80042460(&storedLabelRect_800BF7A8, &win, pOT_8008D454 + 0xE, 0);
        DrawPartyList_800BE53C(menu);
        DrawStoredList_800BE7F0(menu);
    }
    for (i = 0; i < 7; i++)
    {
        if (!((1 << i) & menu->windows_1C))
        {
            continue;
        }
        openStep = 8;
        if (!((1 << i) & menu->windowsOpen_20))
        {
            openStep = menu->openTimer_C;
        }
        if (i == 2)
        {
            if (menu->shown_54->id != 4 && !(menu->flags_24 & 0x20))
            {
                Pos16 abilityPos;
                ListMenuState abilityRef;
                Pos16 p40;
                ListMenuState magicRef;
                Pos16 treePos;
                Pos16 statusPos;
                RECT statusRect;
                if (menu->flags_24 & 0x1C0)
                {
                    if (menu->flags_24 & 0x40)
                    {
                        // do-while(0) block (as from a position macro): its loop notes end cse's extended
                        // basic block, so the 2 stored to abilityRef.windowFlags_4 is not tied to i (known == 2)
                        // and loop.c hoists the shared constant 2 as in the original
                        do
                        {
                            abilityPos.x = 0x5C;
                            abilityPos.y = 0x5E;
                        } while (0);
                        abilityRef.cursor_0 = menu->pageIndex_48;
                        abilityRef.scroll_2 = menu->pageScroll_4A;
                        abilityRef.windowFlags_4 = 2;
                        abilityRef.ot_6 = 0xE;
                        abilityRef.field_8 = 0;
                        abilityRef.fieldMenu_A = 1;
                        abilityRef.minion_C = menu->shown_54;
                        DrawAbilityList_8002CE28(&abilityRef, &abilityPos);
                    }
                    else if (menu->flags_24 & 0x80)
                    {
                        p40.x = 0x7E;
                        p40.y = 0x6D;
                        magicRef.cursor_0 = menu->pageIndex_48;
                        magicRef.scroll_2 = menu->pageScroll_4A;
                        magicRef.windowFlags_4 = 2;
                        magicRef.ot_6 = 0xE;
                        magicRef.field_8 = 0;
                        magicRef.fieldMenu_A = 1;
                        magicRef.minion_C = menu->shown_54;
                        DrawMagicList_8002CAC8(&magicRef, &p40);
                    }
                    else if (menu->flags_24 & 0x100)
                    {
                        treePos.x = 0x28;
                        treePos.y = 0x1E;
                        DrawFamilyTree_8002D7D0(menu->shown_54, 0xE, &treePos);
                    }
                }
                if (!(menu->flags_24 & 0x1C0))
                {
                    statusPos.x = 0x5C;
                    statusPos.y = 0x5E;
                    InterpolateWindowRect_8004196C(&statusRect, &statusWindowRect_800BF790, openStep, 8, 0);
                    if (menu->state_0 == 3 && menu->tabIndex_3C == 2)
                    {
                        DrawUnitStatusPanel_8002DB48(&mergePreview_800C08E8.status_84, 0xE, &statusRect, &statusPos, menu->shown_54, &menu->base_4C->status_84);
                    }
                    else
                    {
                        DrawUnitStatusPanel_8002DB48(&menu->shown_54->status_84, 0xE, &statusRect, &statusPos, menu->shown_54, 0);
                    }
                }
            }
            if (!(menu->flags_24 & 0x1C0))
            {
                WindowStyle statusColor;
                statusColor.colorSet_2 = 0;
                statusColor.semiTrans_3 = 1;
                statusColor.color_0 = saveData_8008B570.uiColor_20.h;
                DrawWindow_80042460(&statusWindowRect_800BF790, &statusColor, pOT_8008D454 + 0xE, 0);
            }
        }
        if (!(menu->flags_24 & 0x800) && i == 3)
        {
            if (!(menu->flags_24 & 2) && menu->messageShown_18 == 0)
            {
                RECT rect;
                UiWindowDesc cursorWin;
                rect.x = 0x56;
                rect.y = menu->listIndex_30 * 16 + 0x25;
                rect.w = 0x1E;
                rect.h = 0x10;
                cursorWin.rect_0 = &rect;
                cursorWin.ot_A = 0xE;
                cursorWin.time_4 = frameCount_8008D3FC;
                cursorWin.colorSet_8 = 1;
                DrawUiWindow_8002A384(&cursorWin);
            }
        }
        if (i == 0)
        {
            DrawShopMainMenu_800BCEDC(menu);
        }
        if (i == 4)
        {
            RECT rect;
            Pos16 baseNamePos;
            baseNamePos.x = mergeSlotRects_800BF7B0[0].x + mergeSlotRects_800BF7B0[0].w / 2;
            baseNamePos.y = mergeSlotRects_800BF7B0[0].y + 2;
            InterpolateWindowRect_8004196C(&rect, &mergeSlotRects_800BF7B0[0], 8, 8, 0);
            DrawSmallText_8002FAA0(2, (unsigned short*)&baseNamePos, menu->base_4C->status_84.name_10, 0xE);
            time = 0;
            if (menu->tabIndex_3C == 0 && menu->state_0 == 3 && (menu->flags_24 & 2))
            {
                time = frameCount_8008D3FC;
            }
            {
                WindowStyle slotColor;
                slotColor.colorSet_2 = 1;
                slotColor.semiTrans_3 = 1;
                slotColor.color_0 = saveData_8008B570.uiColor_20.h;
                DrawWindow_80042460(&rect, &slotColor, pOT_8008D454 + 0xE, time);
            }
        }
        if (i == 5)
            for (j = 1; j < 3; j++)
            {
                RECT slotRect;
                InterpolateWindowRect_8004196C(&slotRect, &mergeSlotRects_800BF7B0[j], 8, 8, 0);
                switch (j)
                {
                case 1:
                {
                    Pos16 p40;
                    p40.x = mergeSlotRects_800BF7B0[j].x + mergeSlotRects_800BF7B0[j].w / 2;
                    p40.y = mergeSlotRects_800BF7B0[j].y + 2;
                    DrawSmallText_8002FAA0(2, (unsigned short*)&p40, menu->partner_50->status_84.name_10, 0xE);
                    break;
                }
                case 2:
                {
                    Pos16 p48;
                    p48.x = mergeSlotRects_800BF7B0[j].x + 7;
                    p48.y = mergeSlotRects_800BF7B0[j].y + 1;
                    DrawUiTiySprt_8002C06C(&p48, 0x42, 0xE);
                    break;
                }
                }
                time = 0;
                if (j == menu->tabIndex_3C && menu->state_0 == 3 && (menu->flags_24 & 2))
                {
                    time = frameCount_8008D3FC;
                }
                {
                    WindowStyle slotColor2;
                    slotColor2.colorSet_2 = 1;
                    slotColor2.semiTrans_3 = 1;
                    slotColor2.color_0 = saveData_8008B570.uiColor_20.h;
                    DrawWindow_80042460(&slotRect, &slotColor2, pOT_8008D454 + 0xE, time);
                }
                if (menu->state_0 == 3 && (menu->flags_24 & 2))
                {
                    ShopPair p48;
                    Pos16 arrowPos;
                    arrowPos.x = 0xA5;
                    p48.a = 0;
                    p48.b = 0;
                    arrowPos.y = 0x55;
                    DrawScrollArrow_8002B3DC(p48, frameCount_8008D3FC, &arrowPos, 0xE);
                    arrowPos.x = 0xFA;
                    DrawScrollArrow_8002B3DC(p48, frameCount_8008D3FC, &arrowPos, 0xE);
                }
            }
        if (i == 6)
        {
            ListMenuState skinRef;
            skinRef.cursor_0 = menu->savedIndex_5E[8];
            skinRef.scroll_2 = menu->savedScroll_72[2];
            skinRef.windowFlags_4 = 2;
            skinRef.ot_6 = 0xE;
            skinRef.field_8 = 0;
            skinRef.fieldMenu_A = 1;
            skinRef.minion_C = 0;
            DrawSkinList_800BED48(&skinRef);
        }
        if (menu->openTimer_C == 8)
        {
            menu->windowsOpen_20 |= 1 << i;
        }
    }
    if (menu->state_0 != 11)
    {
        DrawShopButtonHelp_800BCCD8(menu);
    }
}

void DrawShopButtonHelp_800BCCD8(ShopMenu* menu)
{
    switch (menu->state_0)
    {
    case 1:
        if (menu->flags_24 & 0x20)
            DrawButtonHelpBar_8002B004(btnHelpFormView_800BFFE0, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(btnHelpSelect_800C0048, 0, 0xE);
        break;
    case 2:
        if (menu->flags_24 & 0x20)
            DrawButtonHelpBar_8002B004(btnHelpFormView_800BFFE0, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(btnHelpPartner_800BFF70, 0, 0xE);
        break;
    case 3:
        if (menu->flags_24 & 0x20)
            DrawButtonHelpBar_8002B004(btnHelpFormView_800BFFE0, 0, 0xE);
        else if (menu->flags_24 & 2)
            DrawButtonHelpBar_8002B004(btnHelpMergePreview_800BFFB8, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(helpBarSelectQuit_80082680, 0, 0xE);
        break;
    case 5:
        if (menu->flags_24 & 0x20)
            DrawButtonHelpBar_8002B004(btnHelpFormView_800BFFE0, 0, 0xE);
        else if (!menu->marks_84)
            DrawButtonHelpBar_8002B004(btnHelpSpin_800BFF48, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(btnHelpSpinMarked_800BFF28, 0, 0xE);
        break;
    case 8:
        if (menu->flags_24 & 0x20)
            DrawButtonHelpBar_8002B004(btnHelpFormView_800BFFE0, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(btnHelpView_800BFF90, 0, 0xE);
        break;
    case 15:
        if (menu->flags_24 & 0xC0)
            DrawButtonHelpBar_8002B004(btnHelpStatsPage_800C0018, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(btnHelpStats_800C0000, 0, 0xE);
        break;
    case 7:
        if (menu->flags_24 & 0x20)
            DrawButtonHelpBar_8002B004(btnHelpFormView_800BFFE0, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(btnHelpSelect_800C0048, 0, 0xE);
        break;
    case 10:
        if (menu->flags_24 & 0x20)
            DrawButtonHelpBar_8002B004(btnHelpFormView_800BFFE0, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(btnHelpExchange_800C0070, 0, 0xE);
        break;
    default:
        if (menu->flags_24 & 2)
            DrawButtonHelpBar_8002B004(btnHelpPrompt_800C0038, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(helpBarSelectQuit_80082680, 0, 0xE);
        break;
    }
}
const MenuWindowList mainMenuWindow_800B9608 = { 2, 0, 8, 0, 0, 14 };
const int dword_800B9620 = 0;

void DrawShopMainMenu_800BCEDC(ShopMenu* menu)
{
    MenuWindowList win = mainMenuWindow_800B9608;
    win.time_4 = GetTime30Hz_8002C64C();
    win.items_10 = mainMenuItems_800C07D4;
    win.flags_0 = (win.flags_0 & ~7) | 2;
    win.cursor_C = menu->listIndex_30;
    win.open_8 = 8;
    DrawMenuWindows_8002A5A4(&win);
}

// Matched
int CheckShopSelection_800BCF74(ShopMenu* menu)
{
    if (menu->state_0 == 0)
    {
        switch (menu->listIndex_30)
        {
        case 0:
            if (menu->storedCount_4 + menu->partyCount_6 < 2)
            {
                return 1;
            }
            break;
        case 1:
        case 2:
        case 3:
            if (menu->storedCount_4 + menu->partyCount_6 == 0)
            {
                return 2;
            }
            break;
        }
    }
    else
    {
        switch (menu->state_0)
        {
        case 5:
            if (!menu->marks_84 && !menu->partyMarks_88)
            {
                return 2;
            }
            break;
        case 1:
        case 8:
            if (menu->base_4C->id == 4)
            {
                return 2;
            }
            break;
        case 2:
            if (menu->partner_50->id == 4)
            {
                return 2;
            }
            if (menu->partner_50 == menu->base_4C)
            {
                return 3;
            }
            break;
        case 4:
            if (menu->storedCount_4 + menu->partyCount_6 < 2)
            {
                return 1;
            }
            break;
        case 14:
            if (GetInventorySlotId_800AD288(menu->savedIndex_5E[8] + menu->savedScroll_72[2], 4) == 0xFF)
            {
                return 4;
            }
            menu->flags_24 |= 0x200;
            break;
        }
    }
    return 0;
}

// Matched
void HandleShopConfirmCancel_800BD0D4(ShopMenu* menu)
{
    short s;
    int changed;
    int f;
    short k;
    s = 0;
    changed = 0;
    if (menu->confirm_10)
    {
        s = CheckShopSelection_800BCF74(menu);
        if (s == 0)
        {
            f = menu->flags_24;
            if (f & 8)
            {
                if (menu->list_7E == 0)
                {
                    menu->flags_24 = f | 0x10;
                    menu->partyIndex_58 = menu->listIndex_30;
                    if (menu->state_0 != 5)
                    {
                        menu->marks_84 |= 1 << menu->listIndex_30;
                        menu->partyMarks_88 |= 1 << menu->listIndex_30;
                    }
                }
                else
                {
                    menu->flags_24 = f & ~0x10;
                    menu->storedIndex_5A = menu->listIndex_30;
                    menu->storedScroll_5C = menu->listScroll_32;
                    if (menu->state_0 != 5)
                    {
                        menu->marks_84 |= 1 << (menu->listIndex_30 + menu->listScroll_32 + 3);
                        menu->storedMarks_8C |= 1 << (menu->listIndex_30 + menu->listScroll_32);
                    }
                }
            }
            if (stateConfirmNext_800BF868[menu->state_0] >= 0)
            {
                if (menu->state_0 == 1)
                {
                    MemCopy_800403E8(&mergePreview_800C08E8, menu->base_4C, sizeof(Minion));
                }
                PlaySfx_80031494(0x7E);
                menu->prevState_2 = menu->state_0;
                menu->state_0 = stateConfirmNext_800BF868[menu->state_0];
                changed = 1;
                menu->listScroll_32 = 0;
                menu->listIndex_30 = 0;
                menu->openTimer_C = 0;
            }
            else if (stateConfirmNext_800BF868[menu->state_0] == -1)
            {
                menu->prevState_2 = menu->state_0;
                switch (menu->state_0)
                {
                case 0:
                    if (menu->listIndex_30 == 4)
                    {
                        PlaySfx_80031494(0x7E);
                        if (menu->storedCount_4 < 13)
                        {
                            menu->state_0 = 11;
                        }
                        else
                        {
                            menu->state_0 = 12;
                        }
                    }
                    else
                    {
                        PlaySfx_80031494(0x7E);
                        menu->state_0 = mainMenuStates_800BF8A8[menu->listIndex_30];
                    }
                    break;
                case 4:
                    if (menu->listIndex_30 == 0)
                    {
                        PlaySfx_80031494(0x7E);
                        menu->state_0 = 1;
                        menu->prevState_2 = 0;
                    }
                    else if (menu->listIndex_30 == 1)
                    {
                        PlaySfx_80031494(0x7D);
                        menu->state_0 = 0;
                    }
                    break;
                case 2:
                    PlaySfx_80031494(0x7E);
                    if (IsInventory4NonEmpty_800AD398())
                    {
                        menu->state_0 = 13;
                    }
                    else
                    {
                        PreviewMerge_800BD720(menu);
                        menu->state_0 = 3;
                    }
                    menu->prevState_2 = 2;
                    break;
                case 13:
                    if (menu->listIndex_30 == 0)
                    {
                        PlaySfx_80031494(0x7E);
                        menu->state_0 = 14;
                    }
                    else
                    {
                        PreviewMerge_800BD720(menu);
                        menu->state_0 = 3;
                    }
                    menu->prevState_2 = 2;
                    break;
                case 14:
                    PlaySfx_80031494(0x7E);
                    PreviewMerge_800BD720(menu);
                    menu->state_0 = 3;
                    menu->prevState_2 = 1;
                    break;
                case 8:
                    PlaySfx_80031494(0x7E);
                    menu->prevState_2 = menu->state_0;
                    if (menu->flags_24 & 0x400)
                    {
                        menu->state_0 = 15;
                        menu->flags_24 &= ~0x400;
                    }
                    else
                    {
                        menu->state_0 = 9;
                    }
                    break;
                }
                changed = 1;
                menu->listScroll_32 = 0;
                menu->listIndex_30 = 0;
                menu->openTimer_C = 0;
            }
            else if (stateConfirmNext_800BF868[menu->state_0] == -3)
            {
                PlaySfx_80031494(0x7E);
                ShopMenuExecute_800BD9DC(menu);
            }
        }
        else
        {
            PlaySfx_80031494(0x7C);
            f = menu->flags_24;
            if (f & 8)
            {
                if (menu->list_7E == 0)
                {
                    menu->flags_24 = f | 0x10;
                    menu->partyIndex_58 = menu->listIndex_30;
                }
                else
                {
                    menu->flags_24 = f & ~0x10;
                    menu->storedIndex_5A = menu->listIndex_30;
                    menu->storedScroll_5C = menu->listScroll_32;
                }
            }
            menu->errorId_8 = s;
            SetShopHelpText_800BBB54(menu, 1);
            menu->messageShown_18 = 1;
        }
    }
    else if (menu->cancel_14)
    {
        if (menu->state_0 != 0 || menu->listIndex_30 != 4)
        {
            PlaySfx_80031494(0x7D);
            if (menu->state_0 != 13 && menu->state_0 != 14)
            {
                menu->marks_84 = 0;
                menu->partyMarks_88 = 0;
                menu->storedMarks_8C = 0;
            }
            if (menu->state_0 == 3)
            {
                if (menu->savedList_7A[0] == 0)
                {
                    k = menu->savedIndex_5E[1];
                    menu->marks_84 |= 1 << k;
                    menu->partyMarks_88 |= 1 << k;
                }
                else if (menu->savedList_7A[0] == 1)
                {
                    k = menu->savedIndex_5E[1] + menu->savedScroll_72[0];
                    menu->marks_84 |= 1 << (k + 3);
                    menu->storedMarks_8C |= 1 << k;
                }
            }
            ShopMenuBack_800BB8C4(menu);
            changed = 1;
        }
    }
    menu->cancel_14 = 0;
    menu->confirm_10 = 0;
    if (!(menu->flags_24 & 4))
    {
        if (s == 0 && changed)
        {
            if (IsMergePreviewState_800BD650(&menu->state_0))
            {
                menu->flags_24 |= 2;
                SetShopHelpText_800BBB54(menu, 3);
            }
            else
            {
                SetShopHelpText_800BBB54(menu, 0);
            }
        }
        SetShopWindows_800BD7A8(menu);
        if (IsMinionListState_800BD678(menu))
        {
            menu->flags_24 |= 8;
        }
        else
        {
            menu->flags_24 &= ~8;
        }
        SetupShopCursor_800BD854(menu);
    }
}

int IsMergePreviewState_800BD650(short* state)
{
    if (*state == 3 || *state == 13)
    {
        return 1;
    }
    return 0;
}

int IsMinionListState_800BD678(ShopMenu* menu)
{
    switch (menu->state_0)
    {
    case 1:
    case 2:
    case 5:
    case 7:
    case 8:
    case 10:
        return 1;
    }
    return 0;
}

int IsNoChosen_800BD6C4(ShopMenu* menu)
{
    switch (*(short*)menu)
    {
    case 3:
    case 4:
    case 6:
    case 9:
    case 13:
        if (menu->listIndex_30 == 1)
        {
            return 1;
        }
    }
    return 0;
}
const int dword_800B96F0 = 0; // the alignment of jpt_800B96F4 (delete it with that table)

void PreviewMerge_800BD720(ShopMenu* menu)
{
    int d;
    if (menu->base_4C && menu->partner_50)
    {
        if (menu->flags_24 & 0x200)
        {
            d = GetInventorySlotId_800AD288(menu->savedIndex_5E[8] + menu->savedScroll_72[2], 4);
        }
        else
        {
            d = 10;
        }
        MergeMinions_800B9FC8(menu->base_4C, menu->partner_50, &mergePreview_800C08E8, d);
    }
}

void SetShopWindows_800BD7A8(ShopMenu* menu)
{
    short i;
    unsigned short v;
    int s;
    v = menu->windowsOpen_20;
    menu->windows_1C = 0;
    s = stateWindows_800BF8B4[menu->state_0];
    menu->windowsOpen_20 = 0;
    menu->windows_1C = s;
    for (i = 0; i < 7; i++)
    {
        if ((v >> i) & 1)
        {
            if ((stateWindows_800BF8B4[menu->state_0] >> i) & 1)
            {
                menu->windowsOpen_20 |= 1 << i;
            }
        }
    }
}

void SetupShopCursor_800BD854(ShopMenu* menu)
{
    unsigned short* e = stateCursors_800BF7E8[menu->state_0];
    int r;
    menu->listCols_28 = e[0];
    menu->listRows_2A = e[1];
    menu->listCount_2C = e[2];
    menu->listFlags_2E = e[3];
    if (menu->windows_1C & 8)
    {
        if (menu->state_0 == 4)
        {
            menu->listIndex_30 = 0;
        }
        else
        {
            menu->listIndex_30 = 1;
        }
    }
    if (menu->state_0 == 3)
    {
        menu->tabIndex_3C = 2;
    }
    if (menu->flags_24 & 8)
    {
        if (menu->list_7E == 0)
        {
            menu->flags_24 |= 0x10;
            menu->listCols_28 = 1;
            menu->listFlags_2E = 0x20;
            menu->listRows_2A = 3;
            menu->listCount_2C = 3;
            if (menu->state_0 == 2 || menu->state_0 == 10)
            {
                menu->listIndex_30 = menu->partyIndex_58;
            }
        }
        else
        {
            menu->flags_24 &= ~0x10;
            menu->listCols_28 = 1;
            menu->listRows_2A = 4;
            menu->listCount_2C = 0x18;
            menu->listFlags_2E = 0x50;
            if (menu->state_0 == 2 || menu->state_0 == 10)
            {
                menu->listIndex_30 = menu->storedIndex_5A;
                menu->listScroll_32 = menu->storedScroll_5C;
            }
        }
    }
    if (menu->state_0 == 14)
    {
        r = GetLastInventorySlot_800AD308(4);
        if (r < 3)
        {
            r = 3;
        }
        menu->listCount_2C = r + 1;
    }
}

// Matched
void ShopMenuExecute_800BD9DC(ShopMenu* menu)
{
    EventEntry* tk;
    SaveData* sv;
    int* p;
    int any;
    short i;
    switch (menu->state_0)
    {
    case 3:
        if (menu->listIndex_30 != 0)
        {
            break;
        }
        sv = &saveData_8008B570;
        if (sv->settings_1C.bits.d_5 == 1)
        {
            MemCopy_800403E8(menu->base_4C, &mergePreview_800C08E8, sizeof(Minion));
            SetMinionEmpty_800B9B44((short*)menu->partner_50);
            if (menu->base_4C->species_4C[0] == 0x23)
            {
                p = (int*)sv->allMinionsBitfields_814;
                p[1] |= 8;
            }
            else if (menu->base_4C->species_4C[0] == 0x22)
            {
                p = (int*)sv->allMinionsBitfields_814;
                p[1] |= 4;
            }
            if (menu->flags_24 & 0x200)
            {
                RemoveInventory_800AD1E0(GetInventorySlotId_800AD288(menu->savedIndex_5E[8] + menu->savedScroll_72[2], 4), 1, 4);
                CompactInventory_800AD3F0(4);
                menu->flags_24 &= ~0x200;
            }
            menu->marks_84 = 0;
            menu->partyMarks_88 = 0;
            menu->storedMarks_8C = 0;
            menu->flags_24 |= 1;
            if (saveData_8008B570.settings_1C.bits.d_5 == 1)
            {
                EventEntry* tk = &shopMenuTask_8008D670->entry;
                SetLoadFadeFlag_80027478(0x40, 1);
                FreeActiveOverlay_8002C014();
                RequestAreaReload_80027314();
                tk->cb_8 = ShopWaitAreaReload_800BDD74;
                break;
            }
        }
        menu->fadeAction_94 = 1;
        menu->flags_24 |= 0x800;
        tk = &shopMenuTask_8008D670->entry;
        fn_8001ABEC(1);
        tk->cb_8 = ShopWaitDarken_800BDE44;
        StartSceneDarken_8001AAA8(0x20);
        break;
    case 6:
        if (menu->listIndex_30 != 0)
        {
            break;
        }
        any = 0;
        for (i = any; i < 27; i++)
        {
            if ((unsigned int)menu->marks_84 & (1 << i))
            {
                AddInventory_800AD184(GetSilkItemForLevel_800BAE80(GetShopMinion_800B9C5C(i)), 1, 0);
                ClearShopMinion_800B9B20(i);
                any = 1;
            }
        }
        if (any == 0)
        {
            break;
        }
        menu->marks_84 = 0;
        menu->partyMarks_88 = 0;
        menu->storedMarks_8C = 0;
        menu->flags_24 |= 1;
        if (saveData_8008B570.settings_1C.bits.d_5 == 1)
        {
            EventEntry* tk = &shopMenuTask_8008D670->entry;
            SetLoadFadeFlag_80027478(0x40, 1);
            FreeActiveOverlay_8002C014();
            RequestAreaReload_80027314();
            tk->cb_8 = ShopWaitAreaReload_800BDD74;
        }
        else
        {
            EventEntry* tk;
            menu->fadeAction_94 = 2;
            menu->flags_24 |= 0x800;
            tk = &shopMenuTask_8008D670->entry;
            fn_8001ABEC(1);
            tk->cb_8 = ShopWaitDarken_800BDE44;
            StartSceneDarken_8001AAA8(0x20);
        }
        break;
    case 10:
        ExchangeMinions_800BAF54((short*)menu->base_4C, (short*)menu->partner_50, menu->savedList_7A[0] == 0 ? 3 : 2, menu->savedList_7A[1] == 0 ? 3 : 2);
        menu->marks_84 = 0;
        menu->partyMarks_88 = 0;
        menu->storedMarks_8C = 0;
        menu->state_0 = 7;
        menu->prevState_2 = 0;
        menu->flags_24 |= 1;
        SetShopHelpText_800BBB54(menu, 0);
        break;
    case 9:
        shopMenuTask_8008D670->entry.cb_8 = ShopResumeAfterNameEntry_800BE128;
        shopMenuTask_8008D670->entry.flags = (shopMenuTask_8008D670->entry.flags & ~1) | 0x8000;
        ShopCtrlRequestNameEntry_800B6C6C(menu->base_4C->status_84.name_10
, 0);
        SetFadeMode_8001C19C(0, 0x20);
        menu->marks_84 = 0;
        menu->partyMarks_88 = 0;
        menu->storedMarks_8C = 0;
        break;
    case 11:
        menu->flags_24 |= 4;
        break;
    case 12:
        menu->state_0 = 0;
        break;
    }
}
const MenuWindowList minionListWindow_800B971C = { 0, 0, 8, 0, 0, 14 };

void ShopWaitAreaReload_800BDD74(EventEntry* task, void* arg)
{
    ShopMenu* menu = (ShopMenu*)arg;
    extern void ShopResumeAfterNameEntry_800BE128();
    extern void ShopResumeAfterSpin_800BE07C();
    if (IsMapLoading_800272D0() == 0)
    {
        ResumeFieldMinions_800A7BF0(-1);
        if (menu->state_0 == 3)
        {
            ExchangeEventResult_800A5F9C(1);
            task->cb_8 = ShopResumeAfterNameEntry_800BE128;
            ShopCtrlRequestNameEntry_800B6C6C(menu->base_4C->status_84.name_10
, 1);
        }
        else if (menu->state_0 == 6)
        {
            ExchangeEventResult_800A5F9C(2);
            task->cb_8 = ShopResumeAfterSpin_800BE07C;
            ShopCtrlRequestResume_800B6CC8();
        }
        task->flags = (task->flags & ~1) | 0x8000;
        SetLoadFadeFlag_80027478(0x40, 0);
        RequestGameMode_800A6D30(1);
        eventDispatchHalt_8008B540 = 1;
    }
}

void ShopWaitDarken_800BDE44(EventEntry* task, void* buffer)
{
    ShopMenu* menu = buffer;
    DrawMenuBackground_8002BE10();
    DrawShopMenu_800BC380(menu);
    if (IsSceneFadeDone_8001AB94())
    {
        StopSceneDarken_8001AAF4();
        StartSceneBrighten_8001AB1C(0x20);
        task->cb_8 = ShopWaitBrighten_800BDEA8;
    }
}

void ShopWaitBrighten_800BDEA8(EventEntry* task, void* buffer)
{
    ShopMenu* menu = buffer;
    EventEntry* tk;
    SaveData* sv;
    int* p;
    DrawMenuBackground_8002BE10();
    DrawShopMenu_800BC380(menu);
    if (IsSceneFadeDone_8001AB94())
    {
        tk = &shopMenuTask_8008D670->entry;
        if (menu->fadeAction_94 == 1)
        {
            tk->cb_8 = ShopResumeAfterNameEntry_800BE128;
        }
        else if (menu->fadeAction_94 == 2)
        {
            tk->cb_8 = ShopResumeAfterSpin_800BE07C;
        }
        tk->flags = (tk->flags & ~1) | 0x8000;
        FreeActiveOverlay_8002C014();
        if (menu->fadeAction_94 == 1)
        {
            sv = &saveData_8008B570;
            if (!((sv->settings_1C.word >> 5) & 1))
            {
                MemCopy_800403E8(menu->base_4C, &mergePreview_800C08E8, sizeof(Minion));
                SetMinionEmpty_800B9B44((short*)menu->partner_50);
                if (menu->base_4C->species_4C[0] == 0x23)
                {
                    p = (int*)sv->allMinionsBitfields_814;
                    p[1] |= 8;
                }
                else if (menu->base_4C->species_4C[0] == 0x22)
                {
                    p = (int*)sv->allMinionsBitfields_814;
                    p[1] |= 4;
                }
                if (menu->flags_24 & 0x200)
                {
                    RemoveInventory_800AD1E0(GetInventorySlotId_800AD288(menu->savedIndex_5E[8] + menu->savedScroll_72[2], 4), 1, 4);
                    CompactInventory_800AD3F0(4);
                    menu->flags_24 &= ~0x200;
                }
                menu->marks_84 = 0;
                menu->partyMarks_88 = 0;
                menu->storedMarks_8C = 0;
                menu->flags_24 |= 1;
            }
            ShopCtrlRequestNameEntry_800B6C6C(menu->base_4C->status_84.name_10
, 1);
            SetFadeMode_8001C19C(0, 0x20);
        }
        else if (menu->fadeAction_94 == 2)
        {
            ShopCtrlRequestResume_800B6CC8();
            SetFadeMode_8001C19C(0, 0x20);
        }
        menu->flags_24 &= ~0x800;
        fn_8001ABEC(0);
        menu->fadeAction_94 = 0;
    }
}

void ShopResumeAfterSpin_800BE07C(EventEntry* task, void* buffer)
{
    ShopMenu* menu = buffer;
    menu->state_0 = 5;
    menu->prevState_2 = 0;
    SetShopWindows_800BD7A8(menu);
    SetShopHelpText_800BBB54(menu, 0);
    if (IsMinionListState_800BD678(menu))
    {
        menu->flags_24 |= 8;
    }
    else
    {
        menu->flags_24 &= ~8;
    }
    SetupShopCursor_800BD854(menu);
    menu->listIndex_30 = menu->savedIndex_5E[1];
    menu->listScroll_32 = menu->savedScroll_72[0];
    SuspendFieldMinions_800A7B00(-1);
    LoadUiTiy_8002BF74();
    task->cb_8 = ShopWaitUiTiy_800BE210;
}

void ShopResumeAfterNameEntry_800BE128(EventEntry* task, void* buffer)
{
    ShopMenu* menu = buffer;
    if (menu->state_0 == 9)
    {
        menu->state_0 = 8;
    }
    else
    {
        menu->state_0 = 4;
    }
    menu->prevState_2 = 0;
    SetShopWindows_800BD7A8(menu);
    SetShopHelpText_800BBB54(menu, 0);
    if (IsMinionListState_800BD678(menu))
    {
        menu->flags_24 |= 8;
    }
    else
    {
        menu->flags_24 &= ~8;
    }
    SetupShopCursor_800BD854(menu);
    menu->listIndex_30 = menu->savedIndex_5E[1];
    menu->listScroll_32 = menu->savedScroll_72[0];
    if (menu->state_0 == 4)
    {
        menu->listIndex_30 = 0;
    }
    DrawMenuBackground_8002BE10();
    DrawShopMenu_800BC380(menu);
    SetFadeMode_8001C19C(3, 0x20);
    SuspendFieldMinions_800A7B00(-1);
    task->cb_8 = ShopMenuTask_800BB444;
}

void ShopWaitUiTiy_800BE210(EventEntry* task, void* buffer)
{
    ShopMenu* menu = buffer;
    if (uiTiyLoaded_8008B4E8)
    {
        DrawMenuBackground_8002BE10();
        DrawShopMenu_800BC380(menu);
        task->cb_8 = ShopFadeInMenu_800BE264;
    }
}

void ShopFadeInMenu_800BE264(EventEntry* task, void* buffer)
{
    ShopMenu* menu = buffer;
    DrawMenuBackground_8002BE10();
    DrawShopMenu_800BC380(menu);
    SetFadeMode_8001C19C(3, 0x20);
    task->cb_8 = ShopMenuTask_800BB444;
}

void StartFormView_800BE2B4(Minion* minion)
{
    EventEntry* task = &shopMenuTask_8008D670->entry;
    PlaySfx_80031494(0x7E);
    ResetFormModel_800BF474();
    unknownFlags_8008D678 |= 0x10000;
    unknownFlags_8008D678 |= 0x4000000;
    LoadFormModel_800BF4B8(minion);
    task->cb_8 = FormViewLoadTask_800BE4D0;
}

void FormViewTask_800BE334(EventEntry* task, void* buffer)
{
    ShopMenu* menu = buffer;
    Actor* c;
    int v;
    DrawMenuBackground_8002BE10();
    DrawShopMenu_800BC380(menu);
    c = GetFormActor_800BF780();
    if (padHeld_800918D0[0] & 0x8000)
    {
        *(unsigned short*)&c->rot_5C[1] += 0x88;
    }
    else if (padHeld_800918D0[0] & 0x2000)
    {
        *(unsigned short*)&c->rot_5C[1] -= 0x88;
    }
    if (padHeld_800918D0[0] & 8)
    {
        v = c->baseScale_138[0] + 0x40;
        if (v < 0x1000)
        {
            c->baseScale_138[0] = v;
            c->baseScale_138[1] += 0x40;
            c->baseScale_138[2] += 0x40;
        }
    }
    else if (padHeld_800918D0[0] & 2)
    {
        v = c->baseScale_138[0] - 0x40;
        if (v > 0x400)
        {
            c->baseScale_138[0] = v;
            c->baseScale_138[1] -= 0x40;
            c->baseScale_138[2] -= 0x40;
        }
    }
    if (IsCancelPressedP1_8003D41C(1))
    {
        EndFormView_800BF750();
        unknownFlags_8008D678 &= ~0x10000;
        unknownFlags_8008D678 &= ~0x4000000;
        if (menu->state_0 == 3)
        {
            SetShopHelpText_800BBB54(menu, 3);
        }
        else
        {
            SetShopHelpText_800BBB54(menu, 0);
        }
        if (menu->state_0 == 5)
        {
            menu->confirm_10 = 0;
        }
        menu->flags_24 &= ~0x20;
        task->cb_8 = ShopMenuTask_800BB444;
    }
}

void FormViewLoadTask_800BE4D0(EventEntry* task, void* buffer)
{
    ShopMenu* menu = buffer;
    DrawMenuBackground_8002BE10();
    DrawShopMenu_800BC380(menu);
    if (RunFormModelTask_800BF520() == 1)
    {
        SetShopHelpText_800BBB54(menu, 2);
        ShowFormActor_800BF704(menu->shopId_96);
        task->cb_8 = FormViewTask_800BE334;
    }
}

void DrawPartyList_800BE53C(ShopMenu* menu)
{
    short r[4];
    short out[4];
    unsigned short p[2];
    MenuWindowList win;
    short sel;
    short h;
    int clut;
    short i;
    char* s;
    Minion* e;
    clut = 0;
    if (IsMinionListState_800BD678(menu))
    {
        sel = menu->listIndex_30;
    }
    else
    {
        sel = -1;
    }
    h = 8;
    if (!(menu->windowsOpen_20 & 2))
    {
        h = menu->openTimer_C;
    }
    r[2] = 0x40;
    r[3] = 0xE;
    for (i = 0; i < 3; i++)
    {
        if (GetShopMinionState_800B9C10(i) == 3)
        {
            e = GetShopMinion_800B9C5C(i);
            s = (e->id == 4) ? 0 : e->status_84.name_10
;
        }
        else
        {
            s = 0;
        }
        r[0] = 0xD;
        r[1] = i * 15 + 0x5D;
        if (((unsigned int)menu->marks_84 & (1 << i)) && ((unsigned int)menu->partyMarks_88 & (1 << i)))
        {
            SetFontClutOffset_8003F900(1, 3);
            clut = 1;
        }
        InterpolateWindowRect_8004196C(out, r, (short)h, 8, 0);
        p[0] = r[0] + r[2] / 2;
        p[1] = r[1] + 3;
        if (s)
        {
            DrawSmallText_8002FAA0(2, p, s, 0xE);
        }
        if (clut)
        {
            SetFontClutOffset_8003F900(1, 0);
            clut = 0;
        }
        SetFontClutOffset_8003F900(1, 0);
    }
    win = minionListWindow_800B971C;
    win.time_4 = GetTime30Hz_8002C64C();
    win.open_8 = (short)h;
    win.items_10 = partyListItems_800BFE24;
    if (menu->flags_24 & 0x10)
    {
        win.cursor_C = (short)sel;
    }
    else
    {
        win.cursor_C = -1;
    }
    if (menu->state_0 == 6 || menu->state_0 == 9 || menu->state_0 == 3 || menu->state_0 == 15)
    {
        win.flags_0 |= 4;
    }
    else
    {
        win.flags_0 |= 2;
    }
    win.open_8 = 8;
    DrawMenuWindows_8002A5A4(&win);
    SetFontClutOffset_8003F900(1, 0);
}

void DrawStoredList_800BE7F0(ShopMenu* menu)
{
    short r[4];
    short out[4];
    ShopPair p;
    MenuWindowList win;
    ShopPair pos1;
    ShopPair pos2;
    int base;
    short sel;
    short h;
    int clut;
    short i;
    char* s;
    Minion* e;
    int k;
    base = GetStoredListScroll_800BEB60(menu);
    clut = 0;
    if (IsMinionListState_800BD678(menu))
    {
        sel = menu->listIndex_30;
    }
    else
    {
        sel = -1;
    }
    h = 8;
    if (!(menu->windowsOpen_20 & 2))
    {
        h = menu->openTimer_C;
    }
    r[2] = 0x40;
    r[3] = 0xE;
    for (i = 0; i < 4; i++)
    {
        k = i + (short)base + 3;
        if (GetShopMinionState_800B9C10(k) == 2)
        {
            e = GetShopMinion_800B9C5C(k);
            s = (e->id == 4) ? 0 : e->status_84.name_10
;
        }
        else
        {
            s = 0;
        }
        r[0] = 0xD;
        r[1] = i * 15 + 0x9A;
        if (((unsigned int)menu->marks_84 & (1 << (i + (short)base + 3))) && ((unsigned int)menu->storedMarks_8C & (1 << (i + (short)base))))
        {
            SetFontClutOffset_8003F900(1, 3);
            clut = 1;
        }
        InterpolateWindowRect_8004196C(out, r, h, 8, 0);
        p.a = r[0] + r[2] / 2;
        p.b = r[1] + 3;
        if (s)
        {
            DrawSmallText_8002FAA0(2, (unsigned short*)&p, s, 0xE);
        }
        if (clut)
        {
            SetFontClutOffset_8003F900(1, 0);
            clut = 0;
        }
    }
    win = minionListWindow_800B971C;
    win.time_4 = GetTime30Hz_8002C64C();
    win.items_10 = storedListItems_800BFF14;
    if (menu->flags_24 & 0x10)
    {
        win.cursor_C = -1;
    }
    else
    {
        win.cursor_C = sel;
    }
    if (menu->state_0 == 6 || menu->state_0 == 9 || menu->state_0 == 3 || menu->state_0 == 15)
    {
        win.flags_0 |= 4;
    }
    else
    {
        win.flags_0 |= 2;
    }
    win.open_8 = 8;
    DrawMenuWindows_8002A5A4(&win);
    SetFontClutOffset_8003F900(1, 0);
    if (!(menu->flags_24 & 0x10))
    {
        if ((short)base < 20)
        {
            p.a = 2;
            p.b = 1;
            pos1.a = 0x52;
            pos1.b = 0xCB;
            DrawScrollArrow_8002B3DC(p, frameCount_8008D3FC, &pos1, 0xE);
        }
        if ((short)base != 0)
        {
            p.a = 2;
            p.b = 3;
            pos2.a = 0x52;
            pos2.b = 0xA2;
            DrawScrollArrow_8002B3DC(p, frameCount_8008D3FC, &pos2, 0xE);
        }
    }
}

int GetStoredListScroll_800BEB60(ShopMenu* menu)
{
    switch (menu->state_0)
    {
    case 1:
    case 2:
    case 5:
    case 7:
    case 8:
    case 10:
        return menu->listScroll_32;
    case 3:
    case 4:
    case 13:
    case 14:
        return menu->savedScroll_72[1];
    case 6:
    case 9:
    case 15:
        return menu->savedScroll_72[0];
    }
    return -1;
}

void UpdateSelectedMinions_800BEBC8(ShopMenu* menu)
{
    int n;
    int v;
    switch (menu->state_0)
    {
    case 1:
    case 5:
    case 7:
    case 8:
    case 15:
        if (menu->flags_24 & 0x10)
        {
            n = 0;
            v = (unsigned short)menu->savedIndex_5E[1];
        }
        else
        {
            n = 1;
            v = (unsigned short)menu->savedIndex_5E[1] + GetStoredListScroll_800BEB60(menu) + 3;
        }
        menu->base_4C = GetShopMinion_800B9C5C((short)v);
        menu->savedList_7A[0] = n;
        break;
    case 2:
    case 10:
        if (menu->flags_24 & 0x10)
        {
            n = 0;
            v = (unsigned short)menu->savedIndex_5E[2];
        }
        else
        {
            n = 1;
            v = (unsigned short)menu->savedIndex_5E[2] + GetStoredListScroll_800BEB60(menu) + 3;
        }
        menu->partner_50 = GetShopMinion_800B9C5C((short)v);
        menu->savedList_7A[1] = n;
        break;
    }
}

void UpdateShownMinion_800BECC8(ShopMenu* menu)
{
    if (menu->state_0 == 3)
    {
        switch (menu->tabIndex_3C)
        {
        case 1:
            menu->shown_54 = menu->partner_50;
            return;
        case 0:
            goto def;
        case 2:
            menu->shown_54 = &mergePreview_800C08E8;
            return;
        }
        return;
    }
    if (menu->state_0 == 2 || menu->state_0 == 10)
    {
        menu->shown_54 = menu->partner_50;
        return;
    }
def:
    menu->shown_54 = menu->base_4C;
}

void DrawSkinList_800BED48(short* ref)
{
    MenuWindowList win;
    short h = 8;
    short prev = ref[0];
    short i;
    int id;
    int icon;
    int name;
    int cnt;
    int y;
    int n;
    for (i = 0; i < 4; i++)
    {
        id = GetInventorySlotId_800AD288(i + ref[1], 4);
        if (id < 11)
        {
            icon = GetPersonIcon_8001CD6C(id);
            name = GetPersonName_8001CD3C(id);
            cnt = GetInventorySlotCount_800AD2C8(i + ref[1], 4);
        }
        else
        {
            icon = -1;
            name = (int)aEmpty_800B6D7C;
            cnt = 0;
        }
        skinListRows_800C0258[i][0].text_4 = icon;
        skinListRows_800C0258[i][0].sprts_8 = &publicTiySprts_8008D434;
        skinListRows_800C0258[i][0].tpages_C = &publicTiyTPages_8008D440;
        skinListRows_800C0258[i][1].text_4 = name;
        skinListRows_800C0258[i][2].text_4 = cnt;
        skinListRows_800C0258[i][0].x_10 = 0x7B;
        y = i * 22 + 0x68;
        skinListRows_800C0258[i][0].y_12 = y;
        skinListRows_800C0258[i][1].x_10 = 0x90;
        skinListRows_800C0258[i][1].y_12 = y;
        skinListRows_800C0258[i][2].x_10 = 0xFB;
        skinListRows_800C0258[i][2].y_12 = y;
        ref[0] = i;
        if (cnt == 0)
        {
            skinListRows_800C0258[i][0].flags_0 |= 0x40;
            skinListRows_800C0258[i][1].flags_0 |= 0x40;
            skinListRows_800C0258[i][2].flags_0 |= 0x40;
        }
        else
        {
            skinListRows_800C0258[i][0].flags_0 &= ~0x40;
            skinListRows_800C0258[i][1].flags_0 &= ~0x40;
            skinListRows_800C0258[i][2].flags_0 &= ~0x40;
        }
    }
    win.flags_0 = ref[2];
    win.time_4 = frameCount_8008D3FC;
    win.open_8 = h;
    win.cursor_C = prev;
    win.items_10 = skinListRows_800C0258;
    win.ot_14 = ref[3];
    DrawMenuWindows_8002A5A4(&win);
    SetFontClutOffset_8003F900(2, 0);
    n = GetLastInventorySlot_800AD308(4) + 1;
    if (n < 4)
    {
        n = 4;
    }
    if (ref[1] != 0)
    {
        DrawScrollArrow_8002C6DC(skinListUpArrowPos_800C0090, 3, ref[3]);
    }
    if (ref[1] < n - 4 && n >= 5)
    {
        DrawScrollArrow_8002C6DC(skinListDownArrowPos_800C0094, 1, ref[3]);
    }
}

// Matched
void BuildFormModelDesc_800BF02C(Minion* minion, int* desc, int c)
{
    TopSpeciesBuf top;
    unsigned int h = GetSpeciesModelDesc_80019C70(minion->species_2)->modelId_0;
    desc[0] = GetTopSpecies_800338DC(minion->species_4C, top.b, top.w);
    desc[1] = GetSpeciesModelDesc_80019C70(top.b[0])->modelId_0;
    desc[2] = GetSpeciesModelDesc_80019C70(top.b[1])->modelId_0;
    desc[3] = GetSpeciesModelDesc_80019C70(top.b[2])->modelId_0;
    desc[4] = top.w[0];
    desc[5] = top.w[1];
    desc[6] = top.w[2];
    if (desc[1] == desc[2])
    {
        if (desc[2] == desc[3])
        {
            desc[4] = desc[4] + desc[5];
            desc[4] = desc[4] + desc[6];
            desc[5] = 0;
            desc[6] = 0;
            desc[0] = 1;
        }
        else
        {
            int t;
            desc[0] = 2;
            t = desc[6];
            desc[4] = desc[4] + desc[5];
            desc[6] = 0;
            desc[2] = desc[3];
            desc[5] = t;
        }
    }
    else if (desc[1] == desc[3])
    {
        desc[4] = desc[4] + desc[6];
        desc[6] = 0;
        desc[0] = 2;
    }
    else if (desc[2] == desc[3])
    {
        desc[5] = desc[5] + desc[6];
        desc[6] = 0;
        desc[0] = 2;
    }
    desc[11] = 0;
    if (desc[1] != h)
    {
        if (desc[2] == h)
        {
            int t = desc[5];
            desc[2] = desc[1];
            desc[1] = h;
            desc[5] = desc[4];
            desc[4] = t;
        }
        else if (desc[3] == h)
        {
            int t = desc[6];
            desc[3] = desc[1];
            desc[1] = h;
            desc[6] = desc[4];
            desc[4] = t;
        }
        else if (desc[0] < 2)
        {
            int t = desc[4];
            desc[2] = desc[1];
            desc[1] = h;
            desc[4] = 0;
            desc[0] = 2;
            desc[5] = t;
        }
        else
        {
            int t = desc[4];
            desc[3] = desc[1];
            desc[1] = h;
            desc[4] = 0;
            desc[0] = 3;
            desc[6] = t;
        }
    }
    desc[7] = GetRankForLevel_80019A80(minion->status_84.level_44);
    desc[8] = desc[0] - 1;
    desc[10] = GetSpeciesModelDesc_80019C70(minion->field_3)->modelId_0;
    desc[12] = c;
    desc[9] = GetElementHue_800BF2E4(minion->status_84.element_3E);
    if (desc[9] == -1000)
    {
        desc[9] = GetSpeciesModelDesc_80019C70(minion->field_3)->field_2 << 1;
    }
    else
    {
        desc[9] = desc[9] - (GetSpeciesModelDesc_80019C70(minion->field_3)->field_3 << 1);

        if (desc[9] < 0)
        {
            desc[9] = desc[9] + 0x168;
        }
    }
}

int GetElementHue_800BF2E4(unsigned char* elements)
{
    int n = 0;
    int i;
    int r;
    for (i = 0; i < 4; i++)
    {
        if (elements[i])
        {
            n++;
        }
    }
    if (n == 1)
    {
        r = -1000;
        goto done;
    }
    if (n == 2)
    {
        if (elements[3] && elements[1])
        {
            if (elements[1] < elements[3])
            {
                r = 0xF5;
            }
            else
            {
                r = 0x41;
            }
            goto done;
        }
        if (elements[0] && elements[2])
        {
            if (elements[2] < elements[0])
            {
                r = 0x14F;
            }
            else
            {
                r = 0x9B;
            }
            goto done;
        }
    }
    r = ElementMixAngle_800BF3B4(elements);
done:
    return r;
}

int ElementMixAngle_800BF3B4(unsigned char* elements)
{
    int t2, t1, t4, t3, t5, t6, t7, t8;
    t1 = sinTable_80084540[0x2E3] * elements[0];
    t2 = sinTable_80084540[0xEE3] * elements[0];
    t3 = sinTable_80084540[0xEE3] * elements[3];
    t4 = sinTable_80084540[0xAE3] * elements[3];
    t5 = sinTable_80084540[0xAE3] * elements[2];
    t6 = sinTable_80084540[0x6E3] * elements[2];
    t7 = sinTable_80084540[0x6E3] * elements[1];
    t8 = sinTable_80084540[0x2E3] * elements[1];
    return ratan2Degrees_8003B56C(t1 + t3 + t5 + t7, t2 + t4 + t6 + t8);
}

void ResetFormModel_800BF474()
{
    formModel_800C09E0.task_0 = -1;
}

void FreeFormModel_800BF484()
{
    if (formModel_800C09E0.task_0 >= 0)
    {
        DestroyFormActor_800BF6C4();
        FreeFormModelTask_800BF548();
    }
}

void LoadFormModel_800BF4B8(Minion* minion)
{
    ShopFormModel* form = &formModel_800C09E0;
    BuildFormModelDesc_800BF02C(minion, form->desc_8, dword_8007DC74[0]);
    form->minion_4 = minion;
    form->task_0 = StartModelTask_80010850(form->desc_8);
    form->actor_3C = 0;
}

// the caller reads the step result RunModelTask_80010A10 leaves in v0 (1: model loaded)
int RunFormModelTask_800BF520()
{
    RunModelTask_80010A10(formModel_800C09E0.task_0);
}

void FreeFormModelTask_800BF548()
{
    int task = formModel_800C09E0.task_0;
    formModel_800C09E0.task_0 = -1;
    FreeModelTask_8001098C(task);
}

// Matched
void SpawnFormActor_800BF574(int* pos, unsigned short* rot)
{
    FormActorDesc desc;
    ShopFormModel* form = &formModel_800C09E0;
    int model = fn_80010A44(form->task_0);
    int stage;
    int levels;
    desc.modelId_0 = -1;
    desc.kind_4 = 2;
    desc.posX_8 = pos[0];
    desc.posY_C = pos[1];
    desc.posZ_10 = pos[2];
    desc.rotX_14 = rot[0];
    desc.rotY_16 = rot[1];
    desc.rotZ_18 = rot[2];
    desc.clutRow_1C = 0;
    desc.animIdx_20 = 4;
    desc.frame_24 = -1;
    desc.frameSpeed_28 = 0x1000;
    desc.blendDiv_2C = 4;
    desc.visible_30 = 1;
    desc.model_48 = model;
    desc.bones_34 = (int)defaultBones_80079140;
    stage = form->desc_8[7];
    desc.baseScale_38 = fn_80024E90(model, stage);
    desc.boneScale_3C = fn_80024EC8(model, stage);
    desc.anims_40 = fn_80024E38(model);
    desc.effectTbl_44 = fn_80024E64(model);
    form->actor_3C = fn_8001D45C(&desc);
    levels = fn_80024F00(model, stage);
    model = fn_80024F38(model, stage);
    fn_80019B14((int)form->actor_3C->bones_134, levels, model);
    fn_8001D68C(form->actor_3C, 0);
}

void DestroyFormActor_800BF6C4()
{
    ShopFormModel* form = &formModel_800C09E0;
    if (form->actor_3C)
    {
        DestroyActor_8001D600(form->actor_3C);
        form->actor_3C = 0;
    }
}

void ShowFormActor_800BF704(int shopId)
{
    int pos[3];
    unsigned short rot[4];
    memset(pos, 0, 12);
    memset(rot, 0, 8);
    SpawnFormActor_800BF574(pos, rot);
}

void EndFormView_800BF750()
{
    DestroyFormActor_800BF6C4();
    FreeFormModelTask_800BF548();
    FreeFormModel_800BF484();
}

Actor* GetFormActor_800BF780()
{
    return formModel_800C09E0.actor_3C;
}

RECT statusWindowRect_800BF790 = { 92, 94, 218, 117 };
RECT dialogWindowRect_800BF798 = { 80, 20, 223, 54 };
RECT partyLabelRect_800BF7A0 = { 10, 77, 71, 15 };
RECT storedLabelRect_800BF7A8 = { 10, 138, 71, 15 };
RECT mergeSlotRects_800BF7B0[3] = { { 92, 79, 60, 12 }, { 179, 79, 60, 12 }, { 261, 79, 49, 12 } }; // base, partner, result
ShopTextLine dialogLines_800BF7C8[4] = {
    { 0x180057 },
    { 0x280057 },
    { 0x380057 },
};
unsigned short stateCursors_800BF7E8[16][4] = {
    { 1, 5, 5, 2 },
    { 1, 4, 13, 2 },
    { 1, 4, 13, 2 },
    { 1, 2, 2, 2 },
    { 1, 2, 2, 2 },
    { 1, 4, 13, 2 },
    { 1, 2, 2, 2 },
    { 1, 4, 13, 2 },
    { 1, 4, 13, 2 },
    { 1, 2, 2, 2 },
    { 1, 4, 13, 2 },
    { 1, 1, 1, 2 },
    { 1, 1, 1, 2 },
    { 1, 2, 2, 2 },
    { 1, 4, 4, 64 },
    { 1, 1, 1, 64 },
};
short stateConfirmNext_800BF868[16] = {
    -1, 2, -1, -3, -1, 6, -3, 10,
    -1, -3, -3, -3, -3, -1, -1, -4,
};
unsigned short stateParents_800BF888[16] = {
    0xFFFE, 0, 1, 4, 0, 0, 5, 0,
    0, 8, 7, 0, 0, 2, 3, 8,
};
short mainMenuStates_800BF8A8[6] = { 1, 5, 7, 8, -2 };
short stateWindows_800BF8B4[16] = {
    1, 6, 22, 62, 10, 6, 14, 6,
    6, 14, 6, 0, 1, 58, 114, 6,
};
const char *textMainA_800BF8D4[3] = { aWhatDoYouWantTo_800B6D80, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char *textMergeBaseA_800BF8E0[3] = { aPickTheCocoonTo_800B6DD8, aForTheNewMinion_800B6DB0, aEmpty_800B6D7C };
const char *textSpinSelectA_800BF8EC[3] = { aPickTheCocoonsY_800B6E7C, aToSpinWithX_800B6E5C, aIllSpinThemO_800B6E18 };
const char *textMergePartnerA_800BF8F8[3] = { aPickTheMinionYo_800B6ED8, aToMixWithIt_800B6EB8, aEmpty_800B6D7C };
const char *textSpinConfirmA_800BF904[3] = { aOKIfISpinThisCo_800B6F20, aYes_800B6F14, aNo_800B6F0C };
const char *textPartyA_800BF910[3] = { aChooseTheThreeM_800B6F8C, aToEquipAndTakeW_800B6F54, aEmpty_800B6D7C };
const char *textMergeConfirmA_800BF91C[3] = { aOKIfIMergeThem_800B6FD0, aYes_800B6F14, aNo_800B6F0C };
const char *textMergeAgainA_800BF928[3] = { aWannaTryMerging_800B6FF8, aYes_800B6F14, aNo_800B6F0C };
const char *textViewA_800BF934[3] = { aXRenameTriQuit_800B7090, aOViewMinionsForm_800B7064, aSqViewOtherAbilities_800B7034 };
const char *textRenameA_800BF940[3] = { aRenameThisMinio_800B70C4, aYes_800B6F14, aNo_800B6F0C };
const char *textExchangeA_800BF94C[3] = { aPickTheMinionsT_800B70EC, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char *textQuitA_800BF958[3] = { aIMAllDoneForNow_800B714C, aSeeYaNextTime_800B7128, aEmpty_800B6D7C };
const char *textFullA_800BF964[3] = { aOhIMSorryIMAllO_800B71F8, aICanTStoreAnyMo_800B71B8, aICanSpinToGetRi_800B7178 };
const char *textSkinAskA_800BF970[3] = { aWannaUseTheMini_800B7240, aYes_800B6F14, aNo_800B6F0C };
const char *textSkinPickA_800BF97C[3] = { aPickTheSkinYouW_800B727C, aYes_800B6F14, aNo_800B6F0C };
const char *textStatsA_800BF988[3] = { aYouCanViewOther_800B72C8, aTheSqButton_800B72AC, aEmpty_800B6D7C };
const char *textMergePreviewA_800BF994[3] = { aThisIsWhatItLlL_800B7320, aOViewForm_800B7304, aSqViewOtherAbilities_800B7034 };
const char *textSpunA_800BF9A0[3] = { aOkayIHaveSpunSo_800B73AC, aYouCanSellThisA_800B735C, aEmpty_800B6D7C };
const char *textSkinIntroA_800BF9AC[3] = { aISeeYouHaveSome_800B7460, aSomethingExciti_800B7420, aIfWeUseThem_800B7400 };
const char *textStatsReturnA_800BF9B8[3] = { aYouCanReturnToS_800B74C0, aTheTriButton_800B74A4, aEmpty_800B6D7C };
const char *textMainB_800BF9C4[3] = { aWhatDoYouWishTo_800B750C, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char *textMergeBaseB_800BF9D0[3] = { aPleasePickTheCo_800B753C, aForTheNewMinion_800B6DB0, aEmpty_800B6D7C };
const char *textSpinSelectB_800BF9DC[3] = { aPleasePickTheCo_800B7588, aToSpinWithX_800B6E5C, aIllSpinThemO_800B6E18 };
const char *textMergePartnerB_800BF9E8[3] = { aPleasePickTheMi_800B75F0, aToMixItWith_800B75D0, aEmpty_800B6D7C };
const char *textSpinConfirmB_800BF9F4[3] = { aMayISpinThisMin_800B7630, aYes_800B6F14, aNo_800B6F0C };
const char *textPartyB_800BFA00[3] = { aChooseUpToThree_800B7680, aTakeWithYou_800B7660, aEmpty_800B6D7C };
const char *textMergeConfirmB_800BFA0C[3] = { aShallIMergeThem_800B76BC, aYes_800B6F14, aNo_800B6F0C };
const char *textMergeAgainB_800BFA18[3] = { aShallWeMergeSom_800B76E4, aYes_800B6F14, aNo_800B6F0C };
const char *textViewB_800BFA24[3] = { aXRenameTriQuit_800B7090, aOViewMinionsForm_800B7064, aSqViewOtherAbilities_800B7034 };
const char *textRenameB_800BFA30[3] = { aRenameThisMinio_800B70C4, aYes_800B6F14, aNo_800B6F0C };
const char *textExchangeB_800BFA3C[3] = { aPleasePickTheMi_800B7728, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char *textQuitB_800BFA48[3] = { aMyWorkIsComplet_800B7774, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char *textFullB_800BFA54[3] = { aIMAllOutOfSpace_800B77EC, aCanTStoreAnyMor_800B77B0, aICanSpinToGetRi_800B7178 };
const char *textSkinAskB_800BFA60[3] = { aDoYouWantToUseT_800B7820, aYes_800B6F14, aNo_800B6F0C };
const char *textSkinPickB_800BFA6C[3] = { aPleasePickTheSk_800B7870, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char *textStatsB_800BFA78[3] = { aUseTheSqButton_800B78DC, aToViewOtherStat_800B78B0, aEmpty_800B6D7C };
const char *textMergePreviewB_800BFA84[3] = { aThisIsWhatItLlL_800B7320, aOViewForm_800B7304, aSqViewOtherAbilities_800B7034 };
const char *textSpunB_800BFA90[3] = { aIHaveSpunSomeSh_800B7970, aYouCanGetMoneyB_800B7934, aItAtTheVillageS_800B7900 };
const char *textSkinIntroB_800BFA9C[3] = { aISeeYouHaveSome_800B7460, aSomethingExtrao_800B79D8, aIfWeUseThem_800B79B8 };
const char *textStatsReturnB_800BFAA8[3] = { aUseTheTriButtonTo_800B7A60, aReturnToTheStat_800B7A24, aEmpty_800B6D7C };
const char **stateTextsA_800BFAB4[16] = {
    textMainA_800BF8D4, textMergeBaseA_800BF8E0, textMergePartnerA_800BF8F8, textMergeConfirmA_800BF91C,
    textMergeAgainA_800BF928, textSpinSelectA_800BF8EC, textSpinConfirmA_800BF904, textPartyA_800BF910,
    textViewA_800BF934, textRenameA_800BF940, textExchangeA_800BF94C, textQuitA_800BF958,
    textFullA_800BF964, textSkinAskA_800BF970, textSkinPickA_800BF97C, textStatsA_800BF988,
};
const char **stateTextsB_800BFAF4[16] = {
    textMainB_800BF9C4, textMergeBaseB_800BF9D0, textMergePartnerB_800BF9E8, textMergeConfirmB_800BFA0C,
    textMergeAgainB_800BFA18, textSpinSelectB_800BF9DC, textSpinConfirmB_800BF9F4, textPartyB_800BFA00,
    textViewB_800BFA24, textRenameB_800BFA30, textExchangeB_800BFA3C, textQuitB_800BFA48,
    textFullB_800BFA54, textSkinAskB_800BFA60, textSkinPickB_800BFA6C, textStatsB_800BFA78,
};
const char **resultTextsA_800BFB34[16] = {
    0, 0, 0, textMergePreviewA_800BF994,
    0, textSpunA_800BF9A0, 0, 0,
    0, 0, 0, 0,
    0, textSkinIntroA_800BF9AC,
};
const char **resultTextsB_800BFB74[21] = {
    0, 0, 0, textMergePreviewB_800BFA84,
    0, textSpunB_800BFA90, 0, 0,
    0, 0, 0, 0,
    0, textSkinIntroB_800BFA9C, 0, 0,
    (const char **)aEmpty_800B6D7C, (const char **)aNeedTwoJp_800B7AC8, (const char **)aNoMinionsJp_800B7AB4, (const char **)aCantChooseJp_800B7A9C,
    (const char **)aNoSkinsJp_800B7A88,
};
const char *errNoneA_800BFBC8[3] = { aEmpty_800B6D7C, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char *errNeedTwoA_800BFBD4[3] = { aICanTMergeUnles_800B7AF8, aMinions_800B7AE4, aEmpty_800B6D7C };
const char *errNoMinionsA_800BFBE0[3] = { aWeDonTHaveAnyMi_800B7B3C, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char *errCantUseA_800BFBEC[3] = { aWeCanTUseThatMi_800B7B74, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char *errNoSkinsA_800BFBF8[3] = { aWeDonTHaveAnyMi_800B7BA8, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char **errorTextsA_800BFC04[10] = {
    errNoneA_800BFBC8, errNeedTwoA_800BFBD4, errNoMinionsA_800BFBE0, errCantUseA_800BFBEC,
    errNoSkinsA_800BFBF8, (const char **)aEmpty_800B6D7C, (const char **)aNeedTwoJp2_800B7C30, (const char **)aNoMinionsJp2_800B7C18,
    (const char **)aCantChooseJp2_800B7C00, (const char **)aNoSkinsJp2_800B7BE8,
};
const char *errNoneB_800BFC2C[3] = { aEmpty_800B6D7C, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char *errNeedTwoB_800BFC38[3] = { aICanTMergeUnles_800B7AF8, aMinions_800B7AE4, aEmpty_800B6D7C };
const char *errNoMinionsB_800BFC44[3] = { aThereArenTAnyMi_800B7C50, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char *errCantUseB_800BFC50[3] = { aWeCanTUseThatMi_800B7B74, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char *errNoSkinsB_800BFC5C[3] = { aThereArenTAnyMi_800B7C84, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char **errorTextsB_800BFC68[5] = { errNoneB_800BFC2C, errNeedTwoB_800BFC38, errNoMinionsB_800BFC44, errCantUseB_800BFC50, errNoSkinsB_800BFC5C };
const char *helpMergeA_800BFC7C[3] = { aIfYouSelectTwoM_800B7D1C, aCombineThemAndC_800B7CD8, aForYou_800B7CC4 };
const char *helpSpinA_800BFC88[3] = { aIfYouSpinTheCoc_800B7DAC, aYouCanSellItInT_800B7D60, aEmpty_800B6D7C };
const char *helpPartyA_800BFC94[3] = { aYouCanEquipYour_800B7E24, aWithUpToThreeCo_800B7DF0, aEmpty_800B6D7C };
const char *helpRenameA_800BFCA0[3] = { aYouCanRenameAnd_800B7E90, aCreaturesYouHav_800B7E54, aEmpty_800B6D7C };
const char *helpQuitA_800BFCAC[3] = { aStopPerformingD_800B7EC8, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char *helpMergeB_800BFCB8[3] = { aIfYouSelectTwoM_800B7D1C, aMergeThemAndCre_800B7F14, aForYou_800B7CC4 };
const char *helpSpinB_800BFCC4[3] = { aYouCanGetMoneyB_800B7FA0, aCocoonsIntoSilk_800B7F54, aEmpty_800B6D7C };
const char *helpPartyB_800BFCD0[3] = { aYouCanEquipYour_800B7E24, aWithUpToThreeCo_800B7DF0, aEmpty_800B6D7C };
const char *helpRenameB_800BFCDC[3] = { aYouCanChangeThe_800B7FDC, aCreaturesYouHav_800B7E54, aEmpty_800B6D7C };
const char *helpQuitB_800BFCE8[3] = { aStopPerformingD_800B8030, aForNow_800B801C, aEmpty_800B6D7C };
const char **mainHelpTextsA_800BFCF4[5] = { helpMergeA_800BFC7C, helpSpinA_800BFC88, helpPartyA_800BFC94, helpRenameA_800BFCA0, helpQuitA_800BFCAC };
const char **mainHelpTextsB_800BFD08[5] = { helpMergeB_800BFCB8, helpSpinB_800BFCC4, helpPartyB_800BFCD0, helpRenameB_800BFCDC, helpQuitB_800BFCE8 };
short stateIndexSlots_800BFD1C[16] = {
    0, 1, 2, 3, 4, 1, 5, 1,
    1, 6, 2, 1, 1, 7, 8, 9,
};
unsigned short stateScrollSlots_800BFD3C[16] = {
    0xFFFF, 0, 1, 0xFFFF, 0xFFFF, 0, 0xFFFF, 0,
    0, 0xFFFF, 1, 0xFFFF, 0xFFFF, 0xFFFF, 2, 3,
};
unsigned short stateListSlots_800BFD5C[16] = {
    0xFFFF, 0, 1, 0xFFFF, 0xFFFF, 0, 0xFFFF, 0,
    0, 0xFFFF, 1, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};
MenuWindowItem partyListItem0_800BFD7C[2] = {
    { 0x8, 0, 0, 0, 0, 13, 93, 64, 14, 0, 0 },
    { 0x1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem partyListItem1_800BFDB4[2] = {
    { 0x8, 0, 0, 0, 0, 13, 108, 64, 14, 0, 0 },
    { 0x1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem partyListItem2_800BFDEC[2] = {
    { 0x8, 0, 0, 0, 0, 13, 123, 64, 14, 0, 0 },
    { 0x1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem *partyListItems_800BFE24[4] = { partyListItem0_800BFD7C, partyListItem1_800BFDB4, partyListItem2_800BFDEC, 0 };
MenuWindowItem storedListItem0_800BFE34[2] = {
    { 0x8, 0, 0, 0, 0, 13, 154, 64, 14, 0, 0 },
    { 0x1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem storedListItem1_800BFE6C[2] = {
    { 0x8, 0, 0, 0, 0, 13, 169, 64, 14, 0, 0 },
    { 0x1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem storedListItem2_800BFEA4[2] = {
    { 0x8, 0, 0, 0, 0, 13, 184, 64, 14, 0, 0 },
    { 0x1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem storedListItem3_800BFEDC[2] = {
    { 0x8, 0, 0, 0, 0, 13, 199, 64, 14, 0, 0 },
    { 0x1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem *storedListItems_800BFF14[5] = { storedListItem0_800BFE34, storedListItem1_800BFE6C, storedListItem2_800BFEA4, storedListItem3_800BFEDC, 0 };
ButtonHelpEntry btnHelpSpinMarked_800BFF28[4] = { { 16, aSelect_800B8084 }, { 167, aQuit_800B8078 }, { 110, aSpin_800B806C }, { -1 } };
ButtonHelpEntry btnHelpSpin_800BFF48[5] = { { 16, aSelect_800B8084 }, { 167, aQuit_800B8078 }, { 94, aRearrange_800B80A8 }, { 110, aViewForm_800B8094 }, { -1 } };
ButtonHelpEntry btnHelpPartner_800BFF70[4] = { { 16, aSelect_800B8084 }, { 167, aQuit_800B8078 }, { 110, aViewForm_800B8094 }, { -1 } };
ButtonHelpEntry btnHelpView_800BFF90[5] = { { 16, aRename_800B80E8 }, { 167, aQuit_800B8078 }, { 110, aViewForm_800B8094 }, { 94, aViewOtherAbilit_800B80BC }, { -1 } };
ButtonHelpEntry btnHelpMergePreview_800BFFB8[5] = { { 16, aEmpty_800B6D7C }, { 167, aCombine_800B80F8 }, { 110, aViewForm_800B8094 }, { 94, aViewOtherAbilit_800B80BC }, { -1 } };
ButtonHelpEntry btnHelpFormView_800BFFE0[4] = { { 167, aQuit_800B8078 }, { 153, aEmpty_800B6D7C }, { 154, aZoom_800B8108 }, { -1 } };
ButtonHelpEntry btnHelpStats_800C0000[3] = { { 94, aViewOtherAbilit_800B80BC }, { 167, aQuit_800B8078 }, { -1 } };
ButtonHelpEntry btnHelpStatsPage_800C0018[4] = { { 94, aViewOtherAbilit_800B80BC }, { 167, aQuit_800B8078 }, { 110, aDescription_800B8114 }, { -1 } };
ButtonHelpEntry btnHelpPrompt_800C0038[2] = { { 16, aSelect_800B8084 }, { -1 } };
ButtonHelpEntry btnHelpSelect_800C0048[5] = { { 16, aSelect_800B8084 }, { 167, aQuit_800B8078 }, { 94, aRearrange_800B80A8 }, { 110, aViewForm_800B8094 }, { -1 } };
ButtonHelpEntry btnHelpExchange_800C0070[4] = { { 16, aSelect_800B8084 }, { 167, aQuit_800B8078 }, { 110, aViewForm_800B8094 }, { -1 } };
char skinListUpArrowPos_800C0090[4] = { 200, 0, 97 };
char skinListDownArrowPos_800C0094[4] = { 200, 0, 198 };
MenuWindowItem skinListRow0_800C0098[4] = {
    { 0x10, 1, 0, &publicTiySprts_8008D434, &publicTiyTPages_8008D440, 83, 104, 21, 21, 3, 3 },
    { 0x10, 3, 0, 0, 0, 104, 104, 107, 21, 4, 4 },
    { 0x4, 8, 0, 0, 0, 211, 104, 28, 21, 0, 3 },
    { 0x1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem skinListRow1_800C0108[4] = {
    { 0x10, 1, 0, &publicTiySprts_8008D434, &publicTiyTPages_8008D440, 83, 104, 21, 21, 3, 3 },
    { 0x10, 3, 0, 0, 0, 104, 104, 107, 21, 4, 4 },
    { 0x4, 8, 0, 0, 0, 211, 104, 28, 21, 0, 3 },
    { 0x1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem skinListRow2_800C0178[4] = {
    { 0x10, 1, 0, &publicTiySprts_8008D434, &publicTiyTPages_8008D440, 83, 104, 21, 21, 3, 3 },
    { 0x10, 3, 0, 0, 0, 104, 104, 107, 21, 4, 4 },
    { 0x4, 8, 0, 0, 0, 211, 104, 28, 21, 0, 3 },
    { 0x1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem skinListRow3_800C01E8[4] = {
    { 0x10, 1, 0, &publicTiySprts_8008D434, &publicTiyTPages_8008D440, 83, 104, 21, 21, 3, 3 },
    { 0x10, 3, 0, 0, 0, 104, 104, 107, 21, 4, 4 },
    { 0x4, 8, 0, 0, 0, 211, 104, 28, 21, 0, 3 },
    { 0x1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem *skinListRows_800C0258[5] = { skinListRow0_800C0098, skinListRow1_800C0108, skinListRow2_800C0178, skinListRow3_800C01E8 };
const char *magicDescLines_800C026C[30][4] = {
    { aFireAttackOneEn_800B8BE8, aExtraDamageVsAi_800B8BBC, aHigherFireEleme_800B8B60 },
    { aFireAttackAllEn_800B8B2C, aExtraDamageVsAi_800B8BBC, aHigherFireEleme_800B8B60 },
    { aAdvancedFireAtt_800B8B00, aExtraDamageVsAi_800B8BBC, aHigherFireEleme_800B8B60 },
    { aWaterAttackOneE_800B8ACC, aExtraDamageVsFi_800B8AA0, aHigherWaterElem_800B8A40 },
    { aWaterAttackAllE_800B8A08, aExtraDamageVsFi_800B8AA0, aHigherWaterElem_800B8A40 },
    { aAdvancedWaterAt_800B89DC, aExtraDamageVsFi_800B8AA0, aHigherWaterElem_800B8A40 },
    { aEarthAttackOneE_800B89A8, aExtraDamageVsWa_800B8978, aHigherEarthElem_800B8918 },
    { aEarthAttackAllE_800B88E0, aExtraDamageVsWa_800B8978, aHigherEarthElem_800B8918 },
    { aAdvancedEarthAt_800B88B4, aExtraDamageVsWa_800B8978, aHigherEarthElem_800B8918 },
    { aWindAttackOneEn_800B8884, aExtraDamageVsEa_800B8854, aHigherWindEleme_800B87F8 },
    { aWindAttackAllEn_800B87C4, aExtraDamageVsEa_800B8854, aHigherWindEleme_800B87F8 },
    { aAdvancedWindAtt_800B8798, aExtraDamageVsEa_800B8854, aHigherWindEleme_800B87F8 },
    { aCurePoison_800B8780, aCuresPoison_800B8764 },
    { aRestoreHP_800B874C, aRestoresSomeHP_800B8728 },
    { aRestoreAllHP_800B8708, aRestoresAllHP_800B86E4 },
    { aReturnToNormal_800B86C0, aCuresPoisonAndT_800B8668 },
    { aProtection_800B8650, aProtectsAgainst_800B85E8, aEndsOnceItProte_800B8594 },
    { aPoison_800B8584, aPoisonsAnEnemy_800B8560 },
    { aSleep_800B8554, aPutsAnEnemyToSl_800B8524 },
    { aFleshToStone_800B8504, aTurnsAnEnemyInt_800B84CC },
    { aDeath_800B84C0, aCausesAnEnemyTo_800B846C },
    { aEnhanceFire_800B8450, aIncreasesFireAt_800B83FC, aEffectivenessOf_800B83A0 },
    { aEnhanceWater_800B8384, aIncreasesWaterA_800B832C, aEffectivenessOf_800B82D0 },
    { aEnhanceEarth_800B82B4, aIncreasesEarthA_800B825C, aEffectivenessOf_800B81FC },
    { aEnhanceWind_800B81E0, aIncreasesWindAt_800B818C, aEffectivenessOf_800B812C },
};
const char *abilityDescLines_800C044C[39][4] = {
    { aEmpty_800B6D7C, aEmpty_800B6D7C, aEmpty_800B6D7C },
    { aEmpty_800B6D7C, aEmpty_800B6D7C, aEmpty_800B6D7C },
    { aSpecialEarthAtt_800B9578, aVeryEffectiveAg_800B9520, aHigherEarthElem_800B8918 },
    { aSpecialWaterAtt_800B94F4, aVeryEffectiveAg_800B949C, aHigherWaterElem_800B8A40 },
    { aSpecialFireAtta_800B9474, aVeryEffectiveAg_800B941C, aHigherFireEleme_800B8B60 },
    { aSpecialWindAtta_800B93F4, aVeryEffectiveAg_800B939C, aHigherWindEleme_800B87F8 },
    { aSpecialPoisonAt_800B9370, aPhysicallyDamag_800B931C },
    { aSpecialSleepAtt_800B92F0, aPhysicallyDamag_800B9288 },
    { aSpecialFleshToS_800B924C, aPhysicallyDamag_800B91E0 },
    { aSpecialAttackDe_800B91A4, aCausesAnEnemyTo_800B913C, aMoreDifficultFo_800B90EC },
    { aSpecialAttackAb_800B90B4, aTakesSomeOfTheD_800B9068, aAnEnemyToRestor_800B9018 },
    { aSpecialAttackAb_800B8FDC, aStealsSomeManaF_800B8F94, aUsesItToRestore_800B8F4C },
    { aSpecialAttackAl_800B8F10, aAttacksAllEnemi_800B8ED4, aBringsEnemiesTo_800B8E88 },
    { aSpecialAttackCr_800B8E4C, aReducesAnEnemie_800B8E00, aItMoreDifficult_800B8DA8 },
    { aSpecialAttackBr_800B8D70, aMakesItEasierTo_800B8D10, aSlightlyMoreDif_800B8CAC },
    { aSpecialAttackBr_800B8C70, aMakesItEasierTo_800B8C18, aSlightlyMoreDif_800B8CAC },
};
MenuWindowItem mainMenuItem0_800C06BC[2] = {
    { 0x8, 1, 43, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 15, 77, 56, 20, 0, 3 },
    { 0x1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem mainMenuItem1_800C06F4[2] = {
    { 0x8, 1, 185, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 15, 100, 56, 20, 0, 5 },
    { 0x1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem mainMenuItem2_800C072C[2] = {
    { 0x8, 1, 145, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 15, 123, 56, 20, 0, 3 },
    { 0x1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem mainMenuItem3_800C0764[2] = {
    { 0x10, 1, 103, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 15, 146, 56, 20, 14, 5 },
    { 0x1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
MenuWindowItem mainMenuItem4_800C079C[2] = {
    { 0x8, 1, 53, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 15, 169, 56, 20, 0, 5 },
    { 0x1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
char mainMenuItems_800C07D4[28] = { 188, 6, 12, 128, 244, 6, 12, 128, 44, 7, 12, 128, 100, 7, 12, 128, 156, 7, 12, 128, 0, 0, 0, 0, 11, 128, 2, 60 };
unsigned int emptyMinion_800C07F0[62] = { 0 };
Minion mergePreview_800C08E8 = { 0 };
ShopFormModel formModel_800C09E0 = { 0 };
