// SHOP.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "actor.h"
#include "engine.h"
#include "minion_menu.h"
#include "shop.h"



extern int name_8007DC74;
extern int StartModelTask_80010850(void* p);
extern int CombinedExpDelta_80012204(int a, int b, int c, int d);
extern void BuildFormModelDesc_800BF02C();
extern void SetShopHelpText_800BBB54();
extern void ShowFormActor_800BF704();
extern int RunFormModelTask_800BF520();
extern int IsSceneFadeDone_8001AB94();
extern void StopSceneDarken_8001AAF4();
extern void StartSceneBrighten_8001AB1C(int a);
extern void PlaySfx_80031494(int a);
extern void ResetFormModel_800BF474();
extern void LoadFormModel_800BF4B8();
extern EventNode* shopMenuTask_8008D670; // the shop menu task list
// work area of the shop menu task (EventEntry.buffer)
typedef struct ShopMenu
{
    short state_0; // 0 main menu, 1 merge base, 2 merge partner, 3 merge confirm, 4 merge again, 5 spin select,
                   // 6 spin confirm, 7 party, 8 view, 9 rename, 10 exchange, 11 quit, 12 storage full, 13 skin ask,
                   // 14 skin pick, 15 stats
    short prevState_2;
    short storedCount_4; // minions/cocoons in storage (state 2)
    short partyCount_6;  // state 3
    short errorId_8;     // CheckShopSelection_800BCF74 result shown by SetShopHelpText_800BBB54(u, 1)
    short pad_A;
    short openTimer_C;   // window open animation, 0..8
    short pad_E;
    int confirm_10;
    int cancel_14;
    int messageShown_18; // ShopWaitMessage_800BBA3C
    unsigned int windows_1C;     // stateWindows_800BF8B4 bits
    unsigned int windowsOpen_20; // windows that finished opening
    int flags_24; // 1 recount, 2 prompt shown, 4 quitting, 8 party + stored lists, 0x10 party list active,
                  // 0x20 form view, 0x40/0x80/0x100 ability/magic/family tree page, 0x200 skin chosen,
                  // 0x400 stats view, 0x800 fading, 0x1000 description shown
    // MenuCursor (UpdateMenuCursor_8003D794) of the minion lists
    short listCols_28;
    short listRows_2A;
    short listCount_2C;
    short listFlags_2E;
    short listIndex_30;
    short listScroll_32;
    // MenuCursor of the merge preview (0 base, 1 partner, 2 result)
    short tabCols_34;
    short tabRows_36;
    short tabCount_38;
    short tabFlags_3A;
    short tabIndex_3C;
    short tabScroll_3E;
    // MenuCursor of the ability / magic page
    short pageCols_40;
    short pageRows_42;
    short pageCount_44;
    short pageFlags_46;
    short pageIndex_48;
    short pageScroll_4A;
    Minion* base_4C;    // the chosen minion (merge base, ...)
    Minion* partner_50; // the second minion (merge partner, exchange)
    Minion* shown_54;   // the minion the status panel shows
    unsigned short partyIndex_58;
    unsigned short storedIndex_5A;
    unsigned short storedScroll_5C;
    short savedIndex_5E[10]; // per stateIndexSlots_800BFD1C
    short savedScroll_72[4]; // per stateScrollSlots_800BFD3C
    short savedList_7A[2];   // per stateListSlots_800BFD5C
    short list_7E; // 0 party list, 1 stored list
    short markCount_80;
    short pad_82;
    int marks_84;       // marked entries: party 0..2, stored from 3
    int partyMarks_88;
    int storedMarks_8C;
    int field_90;
    short fadeAction_94; // 1 merge, 2 spin
    short shopId_96;     // 4: the first shopkeeper's texts (stateTextsA_800BFAB4), else stateTextsB_800BFAF4
    short messageTimer_98;
} ShopMenu;


extern char name_80082680[];
extern void DrawButtonHelpBar_8002B004(void* p, int a, int b);
extern int MergeMinions_800B9FC8(Minion* base, Minion* partner, Minion* out, int person);
extern int GetInventorySlotId_800AD288(int a, int b);
extern void DrawMenuWindows_8002A5A4(void* p);
extern void InitShopMenu_800BB148();
extern void SuspendFieldMinions_800A7B00(int a);
extern void LoadUiTiy_8002BF74();
extern int IsMinionListState_800BD678();
extern void SetupShopCursor_800BD854();
extern void SetShopWindows_800BD7A8();
extern int ElementMixAngle_800BF3B4();
extern void SwapMinions_800BAEDC();
extern int FindStoredMinion_800B9888(short i);
extern Minion* GetShopMinion_800B9C5C(int i);
extern int GetShopMinionState_800B9C10(int i);
extern Minion name_8008EF18[];
extern void ClearMagicBit_8001AE00(unsigned int* b, int i);
extern int GetMagicElement_8001AD30(int i);
extern int CountMagicBits_8001AE54(unsigned int* b);
extern int GetLastInventorySlot_800AD308(int a);
extern void EndFormView_800BF750();
typedef struct ShopBigShop
{
    char pad_0[0x5C6];
    short field_5C6;
    char pad_5C8[0x800 - 0x5C8];
} ShopBigShop;
extern ShopBigShop name_80084540[];
typedef struct ShopSetupShop
{
    int w0;
    int w4;
    int w8;
    int wC;
    int w10;
    short s14;
    short s16;
    short s18;
    short pad_1A;
    int w1C;
    int w20;
    int w24;
    int w28;
    int w2C;
    int w30;
    int w34;
    int w38;
    int w3C;
    int w40;
    int w44;
    int w48;
} ShopSetupShop;
extern int fn_80010A44(int a);
extern int fn_80024E90(int a, int b);
extern int fn_80024EC8(int a, int b);
extern int fn_80024E38(int a);
extern int fn_80024E64(int a);
extern void* fn_8001D45C(void* p);
extern int fn_80024F00(int a, int b);
extern int fn_80024F38(int a, int b);
extern void fn_80019B14(int a, int b, int c);
extern void fn_8001D68C(void* p, int on);
extern char defaultBones_80079140[];
extern signed char name_8007BA74[];
extern int UnitStatsToMinion_800B9E94(UnitStats* src, Minion* dst, short c);

extern int fn_800272D0();
extern void ResumeFieldMinions_800A7BF0(int a);
extern void ExchangeEventResult_800A5F9C(int a);
extern void ShopCtrlRequestNameEntry_800B6C6C(void* p, int a);
extern void ShopCtrlRequestResume_800B6CC8();
extern void fn_80027478(int a, int b);
extern void RequestGameMode_800A6D30(int a);
extern int eventDispatchHalt_8008B540;
extern void fn_8002C014();
extern void fn_8001ABEC(int a);
extern int GetInventorySlotId_800AD288(int a, int b);
extern void RemoveInventory_800AD1E0(int a, int b, int c);
extern void CompactInventory_800AD3F0(int a);
extern void SetMinionEmpty_800B9B44(short* p);
extern void ShopResumeAfterNameEntry_800BE128();
extern void ShopResumeAfterSpin_800BE07C();
extern void fn_80011CD0(UnitStatus* p);
extern int GetFreeCocoonSlots_800AD888();
extern void AddEmptyCocoons_800AD8F4(int a);

extern int shopMinionCount_800B6CE4; // SHOPCTRL data: the shop's minion list (BuildShopMinionList_800B9920)
extern Minion* shopMinions_800B6CF0;
Actor* GetFormActor_800BF780();
extern void SetFadeMode_8001C19C(int a, int b);
extern void DestroyActor_8001D600(void* p);
extern void DrawMenuBackground_8002BE10();
extern void* memset(void* p, int c, unsigned int n);
extern void DrawShopMenu_800BC380();
extern void SpawnFormActor_800BF574();

int dword_800B6D00 SDATA = 38;
const char aAssertFmt_800B6D04[] = "Assertion failed: file \"%s\", line %d\n";
const char aCmpactC_800B6D2C[] = "CMPACT.C";
const ShopElementOrder elementOrder_800B6D38 = { { 0, 1, 2, 3 } };
const int dword_800B6D48 = 0;

int CompactStoredMinions_800B97B0()
{
    int r = 0;
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
            r = 1;
            SwapMinions_800BAEDC(&shopMinions_800B6CF0[i], &shopMinions_800B6CF0[j]);
        }
    }
    return r;
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

void SetMinionEmpty_800B9B44(short* p)
{
    *p = 4;
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

char* GetMinionAncestors_800B9C54(char* p)
{
    return p + 4;
}

Minion* GetShopMinion_800B9C5C(int i)
{
    return &shopMinions_800B6CF0[i];
}

int CountShopMinionsInState_800B9C78(int v)
{
    int i;
    int n;
    n = 0;
    for (i = 0; i < shopMinionCount_800B6CE4; i++)
    {
        if (v == shopMinions_800B6CF0[i].id)
        {
            n++;
        }
    }
    return n;
}

int SetMinionInParty_800B9CCC(short* p)
{
    *p = 3;
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

int SetMinionStored_800B9D48(short* p)
{
    if (*p == 3)
    {
        *p = 2;
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
        dst->field_7C[i] = src->st_0.elementMask_42;
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

extern int ApplyLevelUps_80011D98(UnitStatus* a, int b);
extern void MergeSpeciesHistory_800BAB38(Minion* a, Minion* b);
extern void InheritMergeStats_800BA368(Minion* d, Minion* s);
extern void MergeBaseStats_800BA3C8(unsigned char* d, unsigned char* a, unsigned char* b);
extern void MergeResistances_800BA4CC(Minion* d, Minion* a, Minion* b);
extern void ApplyMergeStatBonus_800BA650(Minion* d);
extern void MergeExp_800BA6D0(Minion* d, Minion* s, Minion* t);
extern void MergeSkills_800BA72C(Minion* a, Minion* b);
extern void MergeMagic_800BAA0C(Minion* a, Minion* b);
extern int GetSpecialMergeSpecies_800BACD0(Minion* d);
// merges base and partner into out; person: the skin used (GetPersonMergeInfo_8001CD58), 10: none
int MergeMinions_800B9FC8(Minion* base, Minion* partner, Minion* out, int person)
{
    ShopElementOrder idx;
    UnitStats tmp;
    unsigned char* p;
    int i;
    int n;
    int t;
    int r;
    MemCopy_800403E8(out, base, sizeof(Minion));
    out->field_3 = partner->field_3;
    p = GetPersonMergeInfo_8001CD58(person);
    if (p[0] != 0xFF)
    {
        out->field_3 = p[0];
    }
    MergeSpeciesHistory_800BAB38(out, partner);
    for (i = 0; i < 4; i++)
    {
        out->status_84.element_3E[i] = (out->status_84.element_3E[i] + partner->status_84.element_3E[i]) >> 1;
    }
    n = 0;
    idx = elementOrder_800B6D38;
    for (i = 0; i < 4; i++)
    {
        if (out->status_84.element_3E[i] & 1)
        {
            n++;
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
    if (n == 2)
    {
        for (i = 0; i < 4; i++)
        {
            p = (unsigned char*)out + idx.order[i]; // p[0xC2] == status_84.element_3E[idx.order[i]]; the struct form changes the codegen
            t = p[0xC2];
            if (t & 1)
            {
                if (n >= 2)
                {
                    p[0xC2] = t
 + 1;
                }
                else
                {
                    p[0xC2] = t
 - 1;
                }
                n--;
            }
        }
    }
    if (n == 4)
    {
        for (i = 0; i < 4; i++)
        {
            p = (unsigned char*)out + idx.order[i]; // p[0xC2] == status_84.element_3E[idx.order[i]]; the struct form changes the codegen
            t = p[0xC2];
            if (t & 1)
            {
                if (n >= 3)
                {
                    p[0xC2] = t
 + 1;
                }
                else
                {
                    p[0xC2] = t
 - 1;
                }
                n--;
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
    r = GetSpecialMergeSpecies_800BACD0(out);
    if (r > 0)
    {
        idx.order[0] = r;
        idx.order[1] = (out->status_84.level_44 << 26) + out->status_84.exp_4;
        InitMinionData_8001900C(&tmp, idx.order);
        UnitStatsToMinion_800B9E94(&tmp, out, out->id);
    }
    return 1;
}

void ClearMinion_800BA340(unsigned int* a)
{
    MemCopy_800403E8(a, emptyMinion_800C07F0, 0xF8);
}

void InheritMergeStats_800BA368(Minion* d, Minion* s)
{
    int i;
    for (i = 0; i < 6; i++)
    {
        d->status_84.stats_2C.cur_0[i] = s->status_84.stats_2C.cur_0[i] - s->status_84.stats_2C.base_6[i] / 20;
    }
    d->status_84.hp_8.max_2 = s->status_84.hp_8.max_2;
    d->status_84.mp_C.max_2 = s->status_84.mp_C.max_2;
}

void MergeBaseStats_800BA3C8(unsigned char* d, unsigned char* a, unsigned char* b)
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
        (d + i)[6] = MergeBaseStat_800BA46C((a + i)[6], (b + i)[6]);
    }
    for (i = 5; i >= 0; i--)
    {
    }
}

unsigned char MergeBaseStat_800BA46C(unsigned char a, unsigned char b)
{
    int s = (a + b) >> 1;
    int c = b - 200;
    int r = s + (a + c) / 7;
    int out = 0;
    if (r >= 0)
    {
        out = r;
        if (out > 200)
        {
            out = 200;
        }
    }
    return out;
}

void MergeResistances_800BA4CC(Minion* d, Minion* a, Minion* b)
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
        x = (signed char)a->status_84.field_20[k];
        y = (signed char)b->status_84.field_20[k];
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
        d->status_84.field_20[k] = r;
    }
    memset(tmp, 0, 16);
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            tmp[j] += d->status_84.element_3E[i] * name_8007BA74[j + i * 4];
        }
    }
    for (i = 0; i < 4; i++)
    {
        d->status_84.field_20[i] = tmp[i] / 32;
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

void ApplyMergeStatBonus_800BA650(Minion* d)
{
    int i;
    int v;
    int r;
    int t;
    unsigned char* p;
    for (i = 0; i < 6; i++)
    {
        // p[0xB0] / p[0xB6] == status_84.stats_2C.cur_0[i] / stats_2C.base_6[i]; indexing the fields lets the compiler strength-reduce the loop
        p = (unsigned char*)d + i;
        v = p[0xB0] + (unsigned char)(p[0xB6] / 20);
        if (v >= 0) { t = v; if (t > 100) t = 100; r = t; } else r = 0; p[0xB0] = r;
    }


    for (i = 5; i >= 0; i--)
    {
    }
}

void MergeExp_800BA6D0(Minion* d, Minion* s, Minion* t)
{
    d->status_84.level_44 = s->status_84.level_44;
    d->status_84.exp_4 = s->status_84.exp_4;
    d->status_84.exp_4 += CombinedExpDelta_80012204(s->status_84.level_44, s->status_84.exp_4, t->status_84.level_44, t->status_84.exp_4);
}

#if 0
// Not matched (25 words): only the registers of &t.slot[i] (a3 in the original) and m (t0) are swapped.
// (When writing this in C, delete the C table jpt_800B6D4C behind the function.)

void MergeSkills_800BA72C(Minion* a, Minion* b)
{
    UnitSkills t;
    UnitSkill* ae;
    UnitSkill* be;
    int i;
    int mask;
    int r;
    int m;
    int v;
    t = a->skills_DE;
    ae = a->skills_DE.slot;
    be = b->skills_DE.slot;
    for (i = 0; i < 5; i++)
    {
        t.slot[i].flags_0 |= (ae[i].flags_0 | be[i].flags_0) & 1;
    }
    mask = a->status_84.elementMask_42;
    for (i = 0; i < 5; i++)
    {
        switch (t.slot[i].id_1)
        {
        case 2:
            if (!(mask & 4))
            {
                t.slot[i].id_1 = 0;
            }
            break;
        case 3:
            if (!(mask & 8))
            {
                t.slot[i].id_1 = 0;
            }
            break;
        case 4:
            if (!(mask & 1))
            {
                t.slot[i].id_1 = 0;
            }
            break;
        case 5:
            if (!(mask & 2))
            {
                t.slot[i].id_1 = 0;
            }
            break;
        }
        if (t.slot[i].flags_0 & 1)
        {
            m = a->status_84.elementMask_42;
            r = -1;
            switch (ae[i].id_1)
            {
            case 0:
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
                t.slot[i].id_1 = r;
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
                if (t.slot[i].id_1 == 0)
                {
                    r = be[i].id_1;
                }
                break;
            }
            if (r >= 0)
            {
                t.slot[i].id_1 = r;
            }
            if (t.slot[i].id_1 == 1)
            {
                t.slot[i].id_1 = 0;
            }
        }
        else
        {
            t.slot[i].id_1 = 0;
        }
        if (t.slot[i].flags_0 & 1)
        {
            v = be[i].bonus_2;
            if (v == 1)
            {
                t.slot[i].bonus_2 = 1;
                t.slot[i].field_3 = 0;
            }
            else if (v != 0 && v < 5)
            {
                t.slot[i].bonus_2 = v;
                t.slot[i].field_3 = 1;
            }
        }
        else
        {
            t.slot[i].bonus_2 = 0;
            t.slot[i].field_3 = 0;
        }
    }
    MemCopy_800403E8(&a->skills_DE, &t, sizeof(UnitSkills));
}
#endif
INCLUDE_OVERLAY_ASM(shop, MergeSkills_800BA72C);
// the jump table of MergeSkills_800BA72C (asm; its targets are labels of the generated asm, gen_asm.jump_label): delete it and
// its externs in shop.h when the function is C, the switch emits it then
void* const jpt_800B6D4C[12] = { jtgt_800BA8C8, jtgt_800BA8C8, jtgt_800BA8A4, jtgt_800BA8AC, jtgt_800BA8B4, jtgt_800BA8BC, jtgt_800BA958, jtgt_800BA958, jtgt_800BA910, jtgt_800BA918, jtgt_800BA920, jtgt_800BA928 };
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

void MergeMagic_800BAA0C(Minion* a, Minion* b)
{
    unsigned int old = a->magicBits_F4;
    unsigned int* p = &a->magicBits_F4;
    int i;
    unsigned int mask;
    if (CanInheritMagic_800BAB30(b))
    {
        old |= b->magicBits_F4;
    }
    mask = a->status_84.elementMask_42;
    a->magicBits_F4 = old;
    for (i = 0; i < 30; i++)
    {
        if (TestMagicBit_8001AE2C(p, i) && (mask & (1 << GetMagicElement_8001AD30(i))) == 0)
        {
            ClearMagicBit_8001AE00(p, i);
        }
    }
    if ((char)a->status_84.element_3E[0] != 0x20)
    {
        ClearMagicBit_8001AE00(p, 0x15);
    }
    if ((char)a->status_84.element_3E[2] != 0x20)
    {
        ClearMagicBit_8001AE00(p, 0x17);
    }
    if ((char)a->status_84.element_3E[1] != 0x20)
    {
        ClearMagicBit_8001AE00(p, 0x18);
    }
    if ((char)a->status_84.element_3E[3] != 0x20)
    {
        ClearMagicBit_8001AE00(p, 0x16);
    }
}

int CanInheritMagic_800BAB30()
{
    return 1;
}

#if 0 // near miss: compiler strength-reduces the first loop to pointer increments (96 of 102 words differ)
void MergeSpeciesHistory_800BAB38(Minion* a, Minion* b)
{
    unsigned char tmp[0x30];
    unsigned int e[18];
    unsigned char g[6];
    int i;
    int j;
    for (i = 0; i < 0x30; i++)
    {
        if (i < 0x20)
        {
            if (i * 2 < 0x30)
            {
                tmp[i] = a->species_4C[i * 2];
            }
            else
            {
                tmp[i] = a->species_4C[i * 6 - 0x8F];
            }
        }
        else
        {
            tmp[i] = b->species_4C[i * 3 - 0x60];
        }
    }
    MemCopy_800403E8(a->species_4C, tmp, 0x30);
    CopyName_80019AF4(e, (unsigned int*)a->status_84.name_10);
    CopyName_80019AF4(e + 3, (unsigned int*)b->status_84.name_10);
    CopyName_80019AF4(e + 6, (unsigned int*)a->ancestors_4[0]);
    CopyName_80019AF4(e + 9, (unsigned int*)a->ancestors_4[1]);
    CopyName_80019AF4(e + 12, (unsigned int*)b->ancestors_4[0]);
    CopyName_80019AF4(e + 15, (unsigned int*)b->ancestors_4[1]);
    for (j = 0; j < 6; j++)
    {
        CopyName_80019AF4((unsigned int*)a->ancestors_4[j], e + j * 3);
    }
    g[0] = a->status_84.elementMask_42;
    g[1] = b->status_84.elementMask_42;
    g[2] = a->field_7C[0];
    g[3] = a->field_7C[1];
    g[4] = b->field_7C[0];
    g[5] = b->field_7C[1];
    for (j = 0; j < 6; j++)
    {
        a->field_7C[j] = g[j];
    }
}
#endif
INCLUDE_OVERLAY_ASM(shop, MergeSpeciesHistory_800BAB38);

int GetSpecialMergeSpecies_800BACD0(Minion* d)
{
    int r = -1;
    int n6 = 0;
    int n5 = n6;
    int n4 = n6;
    int n3 = n6;
    int n2 = n6;
    int n1 = n6;
    int i = n6;
    unsigned char v;
    for (; i < 0x30; i++)
    {
        v = d->species_4C[i];
        if (v == 0x1E || v == 0xB1 || v == 0xB2 || v == 0xB3 || v == 0xB4)
        {
            n1++;
        }
        else if (v == 0xE || v == 0x71 || v == 0x72 || v == 0x73 || v == 0x74)
        {
            n2++;
        }
        else if (v == 0xF || v == 0x75 || v == 0x76 || v == 0x77 || v == 0x78)
        {
            n3++;
        }
        else if (v == 3 || v == 0x45 || v == 0x46 || v == 0x47 || v == 0x48)
        {
            n4++;
        }
        else if (v == 7 || v == 0x55 || v == 0x56 || v == 0x57 || v == 0x58)
        {
            n5++;
        }
        else if (v == 9 || v == 0x5D || v == 0x5E || v == 0x5F || v == 0x60)
        {
            n6++;
        }
    }
    if (n1 >= 3 && n2 >= 3 && n3 >= 3)
    {
        r = 0x22;
    }
    else if (n4 >= 3 && n5 >= 3 && n3 >= 3 && n6 >= 3)
    {
        r = 0x23;
    }
    return r;
}

// the silk thread item a spun minion yields
int GetSilkItemForLevel_800BAE80(Minion* p)
{
    unsigned int v = p->status_84.level_44;
    int r;
    if (v < 4)
    {
        r = 0x21;
    }
    else if (v < 7)
    {
        r = 0x22;
    }
    else if (v < 12)
    {
        r = 0x23;
    }
    else if (v < 18)
    {
        r = 0x24;
    }
    else if (v < 25)
    {
        r = 0x25;
    }
    else if (v < 31)
    {
        r = 0x26;
    }
    else
    {
        r = 0x27;
    }
    return r;
}

void SwapMinions_800BAEDC(unsigned int* a, unsigned int* b)
{
    unsigned int t1[0x3E];
    unsigned int t2[0x3E];
    MemCopy_800403E8(t1, a, 0xF8);
    MemCopy_800403E8(t2, b, 0xF8);
    MemCopy_800403E8(a, t2, 0xF8);
    MemCopy_800403E8(b, t1, 0xF8);
}

#if 0 // near miss: orig jumps from the b==3 case into the b==4 copy of the *a = 3 store (cross-jump)
int ExchangeMinions_800BAF54(short* a, short* b, short c, short d)
{
    if (*a == 3)
    {
        if (*b == 2)
        {
            *a = 2;
            *b = 3;
        }
        else if (*b == 4 && d == 2)
        {
            *a = 2;
        }
    }
    else if (*a == 2)
    {
        if (*b == 3)
        {
            *b = 2;
            *a = 3;
        }
        else if (*b == 4 && d == 3)
        {
            *a = 3;
        }
    }
    else if (*a == 4)
    {
        if (c == 3)
        {
            if (*b == 2 && d == 2)
            {
                *b = 3;
            }
        }
        else if (c == 2)
        {
            if (*b == 3 && d == 3)
            {
                *b = 2;
            }
        }
    }
    else
    {
        goto end;
    }
    SwapMinions_800BAEDC(a, b);
end:
    return 1;
}
#endif
INCLUDE_OVERLAY_ASM(shop, ExchangeMinions_800BAF54);

extern void ShopFadeIn_800BB0F8();
void StartShop_800BB058(int shopId)
{
    EventEntry* t = AllocEventEntry_80043AF8(shopMenuTask_8008D670);
    ShopMenu* u;
    if (t)
    {
        u = t->buffer;
        t->flags = (t->flags | 1) & ~0x8000;
        SetFontClutOffset_8003F900(2, 0);
        SetFontClutOffset_8003F900(1, 0);
        DrawMenuBackground_8002BE10();
        u->shopId_96 = shopId;
        InitShopMenu_800BB148(u);
        DrawShopMenu_800BC380(u);
        t->cb_8 = ShopFadeIn_800BB0F8;
    }
}

extern void ShopMenuTask_800BB444();
void ShopFadeIn_800BB0F8(EventEntry* t, int a)
{
    DrawMenuBackground_8002BE10();
    DrawShopMenu_800BC380(a);
    SetFadeMode_8001C19C(3, 0x20);
    t->cb_8 = ShopMenuTask_800BB444;
}

// Matched
void InitShopMenu_800BB148(ShopMenu* u)
{
    short i;
    void* r;
    Minion* mn;
    u->state_0 = 0;
    u->prevState_2 = -2;
    for (i = 0; i < 10; i++)
    {
        u->savedIndex_5E[i] = 0;
    }
    for (i = 0; i < 4; i++)
    {
        u->savedScroll_72[i] = 0;
    }
    for (i = 0; i < 2; i++)
    {
        u->savedList_7A[i] = 0;
    }
    u->tabCols_34 = 3;
    u->tabRows_36 = 1;
    u->tabCount_38 = 3;
    u->tabFlags_3A = 1;
    u->pageCols_40 = 1;
    u->pageRows_42 = 1;
    u->pageCount_44 = 1;
    u->pageFlags_46 = 0x40;
    u->marks_84 = 0;
    u->partyMarks_88 = 0;
    u->storedMarks_8C = 0;
    u->field_90 = 0;
    u->markCount_80 = 0;
    u->fadeAction_94 = 0;
    u->listScroll_32 = 0;
    u->listIndex_30 = 0;
    u->tabScroll_3E = 0;
    u->tabIndex_3C = 0;
    u->pageScroll_4A = 0;
    u->pageIndex_48 = 0;
    u->base_4C = 0;
    u->partner_50 = 0;
    u->shown_54 = 0;
    u->storedScroll_5C = 0;
    u->storedIndex_5A = 0;
    u->partyIndex_58 = 0;
    u->messageShown_18 = 0;
    u->errorId_8 = 0;
    u->cancel_14 = 0;
    u->confirm_10 = 0;
    u->openTimer_C = 0;
    u->messageTimer_98 = 0;
    u->list_7E = 0;
    u->flags_24 = 1;
    u->windows_1C = 0;
    u->windows_1C = stateWindows_800BF8B4[u->state_0];
    u->windowsOpen_20 = 0;
    SetShopHelpText_800BBB54(u, 0);
    SetupShopCursor_800BD854(u);
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

int CanViewForm_800BB38C(ShopMenu* p)
{
    switch (p->state_0)
    {
    case 5:
        if (p->marks_84)
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

int CanRearrange_800BB3E8(ShopMenu* p)
{
    switch (p->state_0)
    {
    case 5:
        if (p->marks_84 == 0)
        {
    case 1:
    case 7:
            return 1;
        }
    }
    return 0;
}

extern int UpdateMenuCursor_8003D794(void* p, int a);
extern void UpdateSelectedMinions_800BEBC8();
extern void UpdateShownMinion_800BECC8();
extern void UpdateMainMenuHelp_800BBAAC();
extern void ShopWaitMessage_800BBA3C();
extern void ShopMenuInput_800BBE24();
extern void DismissShopPrompt_800BC2DC();
extern void CycleInfoPage_800BC1A8();
extern void HandleShopConfirmCancel_800BD0D4();
extern void StartFormView_800BE2B4();
extern void ShopCtrlRequestExit_800B6CB8();
extern unsigned short padPressed_8009194C;
void ShopMenuTask_800BB444(EventEntry* t, ShopMenu* u)
{
    short old;
    int r;
    DrawMenuBackground_8002BE10();
    if (u->flags_24 & 1)
    {
        u->storedCount_4 = CountShopMinionsInState_800B9C78(2);
        u->partyCount_6 = CountShopMinionsInState_800B9C78(3);
        u->flags_24 &= ~1;
    }
    if (u->state_0 != 15 && !(u->flags_24 & 0x400))
    {
        u->flags_24 &= ~0x1C0;
    }
    if ((u->flags_24 & 2) || u->state_0 == 11 || u->state_0 == 12)
    {
        DrawNextPrompt_8003CF88(0x11E, 0x3C, 0xE);
    }
    if (u->messageShown_18 == 0)
    {
        SaveShopCursor_800BB798(u);
        UpdateSelectedMinions_800BEBC8(u);
        UpdateShownMinion_800BECC8(u);
    }
    DrawShopMenu_800BC380(u);
    if (u->messageShown_18 == 0)
    {
        SaveShopCursor_800BB798(u);
        UpdateMainMenuHelp_800BBAAC(u);
        if (u->confirm_10 || u->cancel_14)
        {
            HandleShopConfirmCancel_800BD0D4(u);
        }
        if (!(u->flags_24 & 4))
        {
            if (u->state_0 == 3 && (u->flags_24 & 2))
            {
                old = u->tabIndex_3C;
                UpdateMenuCursor_8003D794(&u->tabCols_34, 0);
                if (u->tabIndex_3C != old)
                {
                    u->pageCols_40 = 1;
                    u->pageRows_42 = 1;
                    u->pageCount_44 = 1;
                    u->pageFlags_46 = 0;
                    u->pageScroll_4A = 0;
                    u->pageIndex_48 = 0;
                    if (u->flags_24 & 0x40)
                    {
                        u->pageCount_44 = 5;
                        u->pageRows_42 = 5;
                    }
                    else if (u->flags_24 & 0x80)
                    {
                        UpdateShownMinion_800BECC8(u);
                        r = CountMagicBits_8001AE54(&u->shown_54->magicBits_F4);
                        if (r < 4)
                        {
                            r = 4;
                        }
                        u->pageRows_42 = 4;
                        u->pageCols_40 = 1;
                        u->pageCount_44 = r;
                        u->pageFlags_46 = 0x40;
                    }
                }
                if (u->flags_24 & 0x400)
                {
                    UpdateMenuCursor_8003D794(&u->pageCols_40, 0);
                }
            }
            if (!(u->flags_24 & 2))
            {
                ShopMenuInput_800BBE24(u);
                if (u->state_0 == 8 || CanViewForm_800BB38C(u))
                {
                    if (padPressed_8009194C & 0x20)
                    {
                        if (u->base_4C->id != 4)
                        {
                            u->flags_24 = (u->flags_24 | 0x20) & ~0x400;
                            u->flags_24 &= ~0x1C0;
                            StartFormView_800BE2B4(u->shown_54);
                        }
                    }
                }
            }
            else
            {
                DismissShopPrompt_800BC2DC(u);
                if (u->state_0 == 3)
                {
                    if (padPressed_8009194C & 0x20)
                    {
                        if (u->base_4C->id != 4)
                        {
                            u->flags_24 = (u->flags_24 | 0x20) & ~0x400;
                            u->flags_24 &= ~0x1C0;
                            StartFormView_800BE2B4(u->shown_54);
                        }
                    }
                    else if (padPressed_8009194C & 0x80)
                    {
                        u->flags_24 |= 0x400;
                        CycleInfoPage_800BC1A8(u);
                    }
                }
                else if (CanViewForm_800BB38C(u))
                {
                    if (padPressed_8009194C & 0x20)
                    {
                        if (u->base_4C->id != 4)
                        {
                            u->flags_24 = (u->flags_24 | 0x20) & ~0x400;
                            u->flags_24 &= ~0x1C0;
                            StartFormView_800BE2B4(u->shown_54);
                        }
                    }
                }
            }
        }
        else
        {
            t->flags = (t->flags & ~1) | 0x8000;
            ShopCtrlRequestExit_800B6CB8();
        }
    }
    else
    {
        ShopWaitMessage_800BBA3C(u);
    }
    if (u->openTimer_C < 8)
    {
        u->openTimer_C++;
    }
}

void SaveShopCursor_800BB798(ShopMenu* u)
{
    short a;
    unsigned short b;
    unsigned short c;
    a = stateIndexSlots_800BFD1C[u->state_0];
    b = stateScrollSlots_800BFD3C[u->state_0];
    c = stateListSlots_800BFD5C[u->state_0];
    if (a >= 0)
    {
        u->savedIndex_5E[a] = u->listIndex_30;
    }
    if ((short)b >= 0)
    {
        u->savedScroll_72[(short)b] = u->listScroll_32;
    }
    if ((short)c >= 0)
    {
        u->savedList_7A[(short)c] = u->list_7E;
    }
}

void RestoreShopCursor_800BB828(ShopMenu* u)
{
    unsigned short b;
    short a;
    unsigned short c;
    a = stateIndexSlots_800BFD1C[u->state_0];
    b = stateScrollSlots_800BFD3C[u->state_0];
    c = stateListSlots_800BFD5C[u->state_0];
    if (a >= 0)
    {
        u->listIndex_30 = u->savedIndex_5E[a];
    }
    if ((short)b >= 0)
    {
        u->listScroll_32 = u->savedScroll_72[(short)b];
    }
    if ((short)c >= 0)
    {
        u->list_7E = u->savedList_7A[(short)c];
    }
}

void ShopMenuBack_800BB8C4(ShopMenu* u)
{
    short s = u->state_0;
    short t;
    if (s == 0)
    {
        if (u->listIndex_30 != 4)
        {
            u->listIndex_30 = 4;
        }
        else
        {
            if (u->storedCount_4 >= 13)
            {
                u->state_0 = 12;
            }
            else
            {
                u->state_0 = 11;
            }
        }
    }
    else if (s == 3)
    {
        u->state_0 = 2;
        u->prevState_2 = 1;
        u->flags_24 &= ~0x200;
        u->listIndex_30 = u->savedIndex_5E[2];
        u->listScroll_32 = u->savedScroll_72[1];
    }
    else if (s == 4)
    {
        u->state_0 = 0;
        u->listScroll_32 = 0;
        u->listIndex_30 = 0;
    }
    else if (s == 12)
    {
        u->state_0 = 0;
    }
    else if (s == 11)
    {
        u->flags_24 |= 4;
    }
    else if (s == 13)
    {
        PreviewMerge_800BD720(u);
        u->state_0 = 3;
        u->prevState_2 = 2;
    }
    else if (s == 14)
    {
        u->state_0 = 13;
        u->prevState_2 = 2;
    }
    else
    {
        if (s == 2 || s == 10)
        {
            u->list_7E = u->savedList_7A[0];
        }
        t = u->prevState_2;
        u->state_0 = t;
        u->prevState_2 = stateParents_800BF888[t];
        RestoreShopCursor_800BB828(u);
    }
}

extern unsigned short padPressed_8009194C;
void ShopWaitMessage_800BBA3C(ShopMenu* u)
{
    if (u->messageTimer_98 < 0x96)
    {
        u->messageTimer_98 += 1;
    }
    if (padPressed_8009194C != 0 || u->messageTimer_98 >= 0x96)
    {
        SetShopHelpText_800BBB54(u, 0);
        u->messageShown_18 = 0;
        u->messageTimer_98 = 0;
    }
}

void UpdateMainMenuHelp_800BBAAC(ShopMenu* u)
{
    short i;
    if (u->state_0 == 0)
    {
        for (i = 0; i < 3; i++)
        {
            if (u->shopId_96 == 4)
            {
                dialogLines_800BF7C8[i].text_4 = mainHelpTextsA_800BFCF4[u->listIndex_30][i];
            }
            else
            {
                dialogLines_800BF7C8[i].text_4 = mainHelpTextsB_800BFD08[u->listIndex_30][i];
            }
        }
    }
}

void SetShopHelpText_800BBB54(ShopMenu* u, int mode)
{
    switch ((short)mode)
    {
    case 1:
        if (u->shopId_96 == 4)
        {
            dialogLines_800BF7C8[0].text_4 = errorTextsA_800BFC04[u->errorId_8][0];
            dialogLines_800BF7C8[1].text_4 = errorTextsA_800BFC04[u->errorId_8][1];
            dialogLines_800BF7C8[2].text_4 = errorTextsA_800BFC04[u->errorId_8][2];
        }
        else
        {
            dialogLines_800BF7C8[0].text_4 = errorTextsB_800BFC68[u->errorId_8][0];
            dialogLines_800BF7C8[1].text_4 = errorTextsB_800BFC68[u->errorId_8][1];
            dialogLines_800BF7C8[2].text_4 = errorTextsB_800BFC68[u->errorId_8][2];
        }
        break;
    case 3:
        if (u->shopId_96 == 4)
        {
            dialogLines_800BF7C8[0].text_4 = resultTextsA_800BFB34[u->state_0][0];
            dialogLines_800BF7C8[1].text_4 = resultTextsA_800BFB34[u->state_0][1];
            dialogLines_800BF7C8[2].text_4 = resultTextsA_800BFB34[u->state_0][2];
        }
        else
        {
            dialogLines_800BF7C8[0].text_4 = resultTextsB_800BFB74[u->state_0][0];
            dialogLines_800BF7C8[1].text_4 = resultTextsB_800BFB74[u->state_0][1];
            dialogLines_800BF7C8[2].text_4 = resultTextsB_800BFB74[u->state_0][2];
        }
        break;
    case 2:
        if (u->shopId_96 == 4)
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
        if (u->state_0 == 0)
        {
            if (u->shopId_96 == 4)
            {
                dialogLines_800BF7C8[0].text_4 = mainHelpTextsA_800BFCF4[u->listIndex_30][0];
                dialogLines_800BF7C8[1].text_4 = mainHelpTextsA_800BFCF4[u->listIndex_30][1];
                dialogLines_800BF7C8[2].text_4 = mainHelpTextsA_800BFCF4[u->listIndex_30][2];
            }
            else
            {
                dialogLines_800BF7C8[0].text_4 = mainHelpTextsB_800BFD08[u->listIndex_30][0];
                dialogLines_800BF7C8[1].text_4 = mainHelpTextsB_800BFD08[u->listIndex_30][1];
                dialogLines_800BF7C8[2].text_4 = mainHelpTextsB_800BFD08[u->listIndex_30][2];
            }
        }
        else
        {
            if (u->shopId_96 == 4)
            {
                dialogLines_800BF7C8[0].text_4 = stateTextsA_800BFAB4[u->state_0][0];
                dialogLines_800BF7C8[1].text_4 = stateTextsA_800BFAB4[u->state_0][1];
                dialogLines_800BF7C8[2].text_4 = stateTextsA_800BFAB4[u->state_0][2];
            }
            else
            {
                dialogLines_800BF7C8[0].text_4 = stateTextsB_800BFAF4[u->state_0][0];
                dialogLines_800BF7C8[1].text_4 = stateTextsB_800BFAF4[u->state_0][1];
                dialogLines_800BF7C8[2].text_4 = stateTextsB_800BFAF4[u->state_0][2];
            }
        }
        break;
    }
}

#if 0
// Not matched (34 words): only the f24 & 8 block differs. The original passes snd (in s1) to
// UpdateMenuCursor instead of a folded 0 (that needs int snd), keeps r in a1, and stores snd to
// s28/s7E through a copy; with int snd the copies and the r register still differ.
extern int IsNoChosen_800BD6C4();
void ShopMenuInput_800BBE24(ShopMenu* u)
{
    short snd;
    int r;
    int k;
    unsigned int bit;
    if (u->flags_24 & 8)
    {
        UpdateSelectedMinions_800BEBC8(u);
        snd = 0;
        r = (short)UpdateMenuCursor_8003D794(&u->listCols_28, snd);
        if (r == 4)
        {
            snd = 1;
            u->listCount_2C = 0x18;
            u->listFlags_2E = 0x50;
            u->listCols_28 = snd;
            u->list_7E = snd;
            u->listRows_2A = r;
            u->listIndex_30 = 0;
            u->flags_24 &= ~0x10;
            SaveShopCursor_800BB798(u);
        }
        else if (r == 3)
        {
            snd = 1;
            u->listCols_28 = snd;
            u->listFlags_2E = 0x20;
            u->listRows_2A = r;
            u->listCount_2C = r;
            u->listIndex_30 = 2;
            u->list_7E = 0;
            u->flags_24 |= 0x10;
            SaveShopCursor_800BB798(u);
        }
        if (snd)
        {
            PlaySfx_80031494(0x7F);
        }
    }
    else
    {
        UpdateMenuCursor_8003D794(&u->listCols_28, 0);
    }
    if (u->state_0 == 15)
    {
        UpdateMenuCursor_8003D794(&u->pageCols_40, 0);
    }
    if (IsConfirmPressedP1_8003D380(0))
    {
        if (u->state_0 != 5)
        {
            if (IsNoChosen_800BD6C4(u))
            {
                u->cancel_14 = 1;
            }
            else if (u->state_0 == 2 || u->state_0 == 10)
            {
                if (u->base_4C == u->partner_50)
                {
                    u->cancel_14 = 1;
                }
                else
                {
                    u->confirm_10 = 1;
                }
            }
            else
            {
                u->confirm_10 = 1;
            }
        }
        else
        {
            if (u->base_4C->id != 4)
            {
                if (u->flags_24 & 0x10)
                {
                    bit = 1 << (short)(u->listIndex_30 + u->listScroll_32);
                    if (!(u->partyMarks_88 & bit))
                    {
                        u->partyMarks_88 |= bit;
                        u->marks_84 |= bit;
                        u->markCount_80++;
                    }
                    else
                    {
                        u->partyMarks_88 &= ~bit;
                        u->marks_84 &= ~bit;
                        u->markCount_80--;
                    }
                }
                else
                {
                    k = (short)(u->listIndex_30 + u->listScroll_32);
                    bit = 1 << k;
                    if (!(u->storedMarks_8C & bit))
                    {
                        u->storedMarks_8C |= bit;
                        u->marks_84 |= 1 << (k + 3);
                        u->markCount_80++;
                    }
                    else
                    {
                        u->storedMarks_8C &= ~bit;
                        u->marks_84 &= ~(1 << (k + 3));
                        u->markCount_80--;
                    }
                }
                PlaySfx_80031494(0x7E);
            }
        }
    }
    else if (IsCancelPressedP1_8003D41C(0))
    {
        u->cancel_14 = 1;
    }
    else if (padPressed_8009194C & 0x80)
    {
        if (u->state_0 == 8)
        {
            u->pageCols_40 = 1;
            u->pageRows_42 = 1;
            u->pageCount_44 = 1;
            u->pageFlags_46 = 0;
            u->pageScroll_4A = 0;
            u->pageIndex_48 = 0;
            u->confirm_10 = 1;
            u->flags_24 |= 0x400;
        }
        else if (u->state_0 == 15)
        {
            CycleInfoPage_800BC1A8(u);
        }
        else if (CanRearrange_800BB3E8(u) && CompactStoredMinions_800B97B0())
        {
            PlaySfx_80031494(0x7E);
        }
    }
    else if (padPressed_8009194C & 0x20)
    {
        if (u->markCount_80 > 0 && u->state_0 == 5)
        {
            u->confirm_10 = 1;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(shop, ShopMenuInput_800BBE24);

void CycleInfoPage_800BC1A8(ShopMenu* u)
{
    int fl;
    int r;
    int t;
    if (u->shown_54->id != 4)
    {
        fl = u->flags_24;
        u->pageCols_40 = 1;
        u->pageRows_42 = 1;
        u->pageCount_44 = 1;
        u->pageFlags_46 = 0;
        u->pageScroll_4A = 0;
        u->pageIndex_48 = 0;
        if ((fl & 0x1C0) == 0)
        {
            u->flags_24 = fl | 0x40;
            u->pageCount_44 = 5;
            u->pageRows_42 = 5;
        }
        else if (fl & 0x40)
        {
            t = fl & ~0x40;
            t &= ~0x100;
            u->flags_24 = t | 0x80;
            r = CountMagicBits_8001AE54(&u->shown_54->magicBits_F4);
            if (r < 4)
            {
                r = 4;
            }
            u->pageCols_40 = 1;
            u->pageRows_42 = 4;
            u->pageCount_44 = r;
            u->pageFlags_46 = 0x40;
        }
        else if (fl & 0x80)
        {
            int t2 = fl & ~0x40;
            t2 &= ~0x80;
            u->flags_24 = t2 | 0x100;
        }
        else if (fl & 0x100)
        {
            int fl2 = fl & ~0x100;
            u->flags_24 = fl2;
            if (u->state_0 == 3 && (fl & 2))
            {
                u->flags_24 = fl2 & ~0x400;
            }
        }
        PlaySfx_80031494(0x7F);
    }
}

void DismissShopPrompt_800BC2DC(ShopMenu* u)
{
    if (IsConfirmPressedP1_8003D380(0) || IsCancelPressedP1_8003D41C(0))
    {
        int fl = u->flags_24;
        if ((fl & 0x400) && u->state_0 == 3 && (fl & 2))
        {
            PlaySfx_80031494(0x7D);
            u->flags_24 &= ~0x400;
        }
        else
        {
            PlaySfx_80031494(0x7E);
            SetShopHelpText_800BBB54(u, 0);
            u->flags_24 &= ~2;
        }
    }
}

typedef struct ShopPosShop
{
    short x;
    short y;
} ShopPosShop;
// window style for DrawWindow_80042460
typedef struct ShopWinShop
{
    short color;
    unsigned char field_2;
    unsigned char field_3;
} ShopWinShop;
// DrawUiWindow_8002A384's parameter block
typedef struct ShopUiWinShop
{
    ShopRect* rect_0;
    int time_4;
    short field_8;
    short ot_A;
} ShopUiWinShop;
typedef struct ShopPairShop
{
    short a;
    short b;
} ShopPairShop;
extern void DrawScrollArrow_8002B3DC(ShopPairShop p, int b, void* c, int d);
extern int IsCircleHeldP1_8003D480(void);
extern int FindNthMagicBit_8001AEC0(unsigned int* bits, int n);
extern void DrawPortraitWindow_8002A4E4(int a);
extern void DrawTextList_8002A310(void* p, int a);
extern void DrawAbilityDescription_8002C670(Minion* m, ShopPosShop* pos, void* a2, int idx, int ot);
extern void DrawUiTiySprt_8002C06C(void* pos, int idx, int ot);
extern void DrawWindow_80042460(void* rect, ShopWinShop* w, void* ot, int t);
extern void DrawAbilityList_8002CE28(struct_minion_ref* a0, ShopPosShop* a1);
extern void DrawMagicList_8002CAC8(struct_minion_ref* a0, ShopPosShop* a1);
extern void DrawFamilyTree_8002D7D0(Minion* m, int ot, ShopPosShop* base);
extern void InterpolateWindowRect_8004196C(void* a0, void* a1, int a2, int a3, int a4);
extern void DrawUnitStatusPanel_8002DB48(UnitStatus* m, int ot, void* rect, ShopPosShop* pos, Minion* mn, UnitStatus* cmp);
extern void DrawSmallText_8002FAA0(int a0, unsigned short* pos, char* name, int a3);
extern void DrawUiWindow_8002A384(ShopUiWinShop* p);
extern void DrawShopMainMenu_800BCEDC(ShopMenu* u);
extern void DrawShopButtonHelp_800BCCD8(ShopMenu* u);
extern void DrawPartyList_800BE53C(ShopMenu* u);
extern void DrawStoredList_800BE7F0(ShopMenu* u);
extern void DrawSkinList_800BED48();
#if 0
// Not matched: stack layout matches; loop-invariant constant 2 is not hoisted (the original keeps it in a spilled pseudo, rematerialised in $t1), so a few registers differ
void DrawShopMenu_800BC380(ShopMenu* u)
{
    ShopPosShop pos;
    ShopWinShop win;
    short i;
    short j;
    short n;
    int c;
    int t;
    if (u->flags_24 & 0x40)
    {
        c = 0;
        if (u->shown_54->skills_DE.slot[u->pageIndex_48].flags_0 & 1)
        {
            c = 0 < u->shown_54->skills_DE.slot[u->pageIndex_48].id_1;
        }
        if (IsCircleHeldP1_8003D480() && c)
        {
            u->flags_24 |= 0x1000;
        }
        else
        {
            u->flags_24 &= ~0x1000;
        }
    }
    else if (u->flags_24 & 0x80)
    {
        j = u->pageIndex_48 + u->pageScroll_4A;
        c = FindNthMagicBit_8001AEC0(&u->shown_54->magicBits_F4, j) < 0x1E;
        if (IsCircleHeldP1_8003D480() && c)
        {
            u->flags_24 |= 0x1000;
        }
        else
        {
            u->flags_24 &= ~0x1000;
        }
    }
    if (u->state_0 == 3 && (u->flags_24 & 2))
    {
        u->flags_24 &= ~0x1000;
    }
    if (!(u->flags_24 & 0x1000))
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
        if (u->flags_24 & 0x40)
        {
            DrawAbilityDescription_8002C670(u->shown_54, &pos, abilityDescLines_800C044C, u->pageIndex_48, 0xE);
        }
        else if (u->flags_24 & 0x80)
        {
            DrawLargeTextBox_8002AF10((int)magicDescLines_800C026C[FindNthMagicBit_8001AEC0(&u->shown_54->magicBits_F4, u->pageIndex_48 + u->pageScroll_4A)], (int)&pos, 0xE);
        }
    }
    if (u->windows_1C & 2)
    {
        pos.x = partyLabelRect_800BF7A0.x + 5;
        pos.y = partyLabelRect_800BF7A0.y + 3;
        pos.x = partyLabelRect_800BF7A0.x + 3;
        DrawUiTiySprt_8002C06C(&pos, 0xB5, 0xE);
        win.field_3 = 1;
        win.field_2 = 0;
        win.color = saveData_8008B570.uiColor_20.h;
        DrawWindow_80042460(&partyLabelRect_800BF7A0, &win, pOT_8008D454 + 0xE, 0);
        pos.x = storedLabelRect_800BF7A8.x + 5;
        pos.y = storedLabelRect_800BF7A8.y + 3;
        pos.x = storedLabelRect_800BF7A8.x + 4;
        DrawUiTiySprt_8002C06C(&pos, 0xE, 0xE);
        DrawWindow_80042460(&storedLabelRect_800BF7A8, &win, pOT_8008D454 + 0xE, 0);
        DrawPartyList_800BE53C(u);
        DrawStoredList_800BE7F0(u);
    }
    for (i = 0; i < 7; i++)
    {
        if (!((1 << i) & u->windows_1C))
        {
            continue;
        }
        n = 8;
        if (!((1 << i) & u->windowsOpen_20))
        {
            n = u->openTimer_C;
        }
        if (i == 2)
        {
            if (u->shown_54->id != 4 && !(u->flags_24 & 0x20))
            {
                ShopPosShop p28;
                struct_minion_ref r30;
                ShopPosShop p40;
                struct_minion_ref r48;
                ShopPosShop p58;
                ShopPosShop p60;
                ShopRect r68;
                if (u->flags_24 & 0x1C0)
                {
                    if (u->flags_24 & 0x40)
                    {
                        p28.x = 0x5C;
                        p28.y = 0x5E;
                        r30.cursor_0 = u->pageIndex_48;
                        r30.scroll_2 = u->pageScroll_4A;
                        r30.field_4 = 2;
                        r30.ot_6 = 0xE;
                        r30.field_8 = 0;
                        r30.field_A = 1;
                        r30.minion_C = u->shown_54;
                        DrawAbilityList_8002CE28(&r30, &p28);
                    }
                    else if (u->flags_24 & 0x80)
                    {
                        p40.x = 0x7E;
                        p40.y = 0x6D;
                        r48.cursor_0 = u->pageIndex_48;
                        r48.scroll_2 = u->pageScroll_4A;
                        r48.field_4 = 2;
                        r48.ot_6 = 0xE;
                        r48.field_8 = 0;
                        r48.field_A = 1;
                        r48.minion_C = u->shown_54;
                        DrawMagicList_8002CAC8(&r48, &p40);
                    }
                    else if (u->flags_24 & 0x100)
                    {
                        p58.x = 0x28;
                        p58.y = 0x1E;
                        DrawFamilyTree_8002D7D0(u->shown_54, 0xE, &p58);
                    }
                }
                if (!(u->flags_24 & 0x1C0))
                {
                    p60.x = 0x5C;
                    p60.y = 0x5E;
                    InterpolateWindowRect_8004196C(&r68, &statusWindowRect_800BF790, n, 8, 0);
                    if (u->state_0 == 3 && u->tabIndex_3C == 2)
                    {
                        DrawUnitStatusPanel_8002DB48(&mergePreview_800C08E8.status_84, 0xE, &r68, &p60, u->shown_54, &u->base_4C->status_84);
                    }
                    else
                    {
                        DrawUnitStatusPanel_8002DB48(&u->shown_54->status_84, 0xE, &r68, &p60, u->shown_54, 0);
                    }
                }
            }
            if (!(u->flags_24 & 0x1C0))
            {
                ShopWinShop w28;
                w28.field_2 = 0;
                w28.field_3 = 1;
                w28.color = saveData_8008B570.uiColor_20.h;
                DrawWindow_80042460(&statusWindowRect_800BF790, &w28, pOT_8008D454 + 0xE, 0);
            }
        }
        if (!(u->flags_24 & 0x800) && i == 3)
        {
            if (!(u->flags_24 & 2) && u->messageShown_18 == 0)
            {
                ShopRect r28;
                ShopUiWinShop w30;
                r28.x = 0x56;
                r28.y = u->listIndex_30 * 16 + 0x25;
                r28.w = 0x1E;
                r28.h = 0x10;
                w30.rect_0 = &r28;
                w30.ot_A = 0xE;
                w30.time_4 = frameCount_8008D3FC;
                w30.field_8 = 1;
                DrawUiWindow_8002A384(&w30);
            }
        }
        if (i == 0)
        {
            DrawShopMainMenu_800BCEDC(u);
        }
        if (i == 4)
        {
            ShopRect r28;
            ShopPosShop p30;
            p30.x = mergeSlotRects_800BF7B0[0].x + mergeSlotRects_800BF7B0[0].w / 2;
            p30.y = mergeSlotRects_800BF7B0[0].y + 2;
            InterpolateWindowRect_8004196C(&r28, &mergeSlotRects_800BF7B0[0], 8, 8, 0);
            DrawSmallText_8002FAA0(2, (unsigned short*)&p30, u->base_4C->status_84.name_10, 0xE);
            t = 0;
            if (u->tabIndex_3C == 0 && u->state_0 == 3 && (u->flags_24 & 2))
            {
                t = frameCount_8008D3FC;
            }
            {
                ShopWinShop w38;
                w38.field_2 = 1;
                w38.field_3 = 1;
                w38.color = saveData_8008B570.uiColor_20.h;
                DrawWindow_80042460(&r28, &w38, pOT_8008D454 + 0xE, t);
            }
        }
        if (i == 5)
            for (j = 1; j < 3; j++)
            {
                ShopRect r38;
                InterpolateWindowRect_8004196C(&r38, &mergeSlotRects_800BF7B0[j], 8, 8, 0);
                switch (j)
                {
                case 1:
                {
                    ShopPosShop p40;
                    p40.x = mergeSlotRects_800BF7B0[j].x + mergeSlotRects_800BF7B0[j].w / 2;
                    p40.y = mergeSlotRects_800BF7B0[j].y + 2;
                    DrawSmallText_8002FAA0(2, (unsigned short*)&p40, u->partner_50->status_84.name_10, 0xE);
                    break;
                }
                case 2:
                {
                    ShopPosShop p48;
                    p48.x = mergeSlotRects_800BF7B0[j].x + 7;
                    p48.y = mergeSlotRects_800BF7B0[j].y + 1;
                    DrawUiTiySprt_8002C06C(&p48, 0x42, 0xE);
                    break;
                }
                }
                t = 0;
                if (j == u->tabIndex_3C && u->state_0 == 3 && (u->flags_24 & 2))
                {
                    t = frameCount_8008D3FC;
                }
                {
                    ShopWinShop w40;
                    w40.field_2 = 1;
                    w40.field_3 = 1;
                    w40.color = saveData_8008B570.uiColor_20.h;
                    DrawWindow_80042460(&r38, &w40, pOT_8008D454 + 0xE, t);
                }
                if (u->state_0 == 3 && (u->flags_24 & 2))
                {
                    ShopPairShop p48;
                    ShopPosShop p50;
                    p50.x = 0xA5;
                    p48.a = 0;
                    p48.b = 0;
                    p50.y = 0x55;
                    DrawScrollArrow_8002B3DC(p48, frameCount_8008D3FC, &p50, 0xE);
                    p50.x = 0xFA;
                    DrawScrollArrow_8002B3DC(p48, frameCount_8008D3FC, &p50, 0xE);
                }
            }
        if (i == 6)
        {
            struct_minion_ref r40;
            r40.cursor_0 = u->savedIndex_5E[8];
            r40.scroll_2 = u->savedScroll_72[2];
            r40.field_4 = 2;
            r40.ot_6 = 0xE;
            r40.field_8 = 0;
            r40.field_A = 1;
            r40.minion_C = 0;
            DrawSkinList_800BED48(&r40);
        }
        if (u->openTimer_C == 8)
        {
            u->windowsOpen_20 |= 1 << i;
        }
    }
    if (u->state_0 != 11)
    {
        DrawShopButtonHelp_800BCCD8(u);
    }
}
#endif
INCLUDE_OVERLAY_ASM(shop, DrawShopMenu_800BC380);

void DrawShopButtonHelp_800BCCD8(ShopMenu* u)
{
    switch (u->state_0)
    {
    case 1:
        if (u->flags_24 & 0x20)
            DrawButtonHelpBar_8002B004(btnHelpFormView_800BFFE0, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(btnHelpSelect_800C0048, 0, 0xE);
        break;
    case 2:
        if (u->flags_24 & 0x20)
            DrawButtonHelpBar_8002B004(btnHelpFormView_800BFFE0, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(btnHelpPartner_800BFF70, 0, 0xE);
        break;
    case 3:
        if (u->flags_24 & 0x20)
            DrawButtonHelpBar_8002B004(btnHelpFormView_800BFFE0, 0, 0xE);
        else if (u->flags_24 & 2)
            DrawButtonHelpBar_8002B004(btnHelpMergePreview_800BFFB8, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(name_80082680, 0, 0xE);
        break;
    case 5:
        if (u->flags_24 & 0x20)
            DrawButtonHelpBar_8002B004(btnHelpFormView_800BFFE0, 0, 0xE);
        else if (!u->marks_84)
            DrawButtonHelpBar_8002B004(btnHelpSpin_800BFF48, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(btnHelpSpinMarked_800BFF28, 0, 0xE);
        break;
    case 8:
        if (u->flags_24 & 0x20)
            DrawButtonHelpBar_8002B004(btnHelpFormView_800BFFE0, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(btnHelpView_800BFF90, 0, 0xE);
        break;
    case 15:
        if (u->flags_24 & 0xC0)
            DrawButtonHelpBar_8002B004(btnHelpStatsPage_800C0018, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(btnHelpStats_800C0000, 0, 0xE);
        break;
    case 7:
        if (u->flags_24 & 0x20)
            DrawButtonHelpBar_8002B004(btnHelpFormView_800BFFE0, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(btnHelpSelect_800C0048, 0, 0xE);
        break;
    case 10:
        if (u->flags_24 & 0x20)
            DrawButtonHelpBar_8002B004(btnHelpFormView_800BFFE0, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(btnHelpExchange_800C0070, 0, 0xE);
        break;
    default:
        if (u->flags_24 & 2)
            DrawButtonHelpBar_8002B004(btnHelpPrompt_800C0038, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(name_80082680, 0, 0xE);
        break;
    }
}
const ShopMenuWindows mainMenuWindow_800B9608 = { 2, 0, 8, 0, 0, 14 };
const int dword_800B9620 = 0;

void DrawShopMainMenu_800BCEDC(ShopMenu* u)
{
    ShopMenuWindows q = mainMenuWindow_800B9608;
    q.time_4 = GetTime30Hz_8002C64C();
    q.items_10 = (int)mainMenuItems_800C07D4;
    q.flags_0 = (q.flags_0 & ~7) | 2;
    q.cursor_C = u->listIndex_30;
    q.open_8 = 8;
    DrawMenuWindows_8002A5A4(&q);
}

#if 0 // near miss: orig shares the field_30 == 0 block with case 4 and cross-jumps the return-2 tails
int CheckShopSelection_800BCF74(ShopMenu* u)
{
    int s;
    if (u->state_0 == 0)
    {
        s = u->listIndex_30;
        if (s == 0)
        {
            if (u->storedCount_4 + u->partyCount_6 < 2)
            {
                return 1;
            }
        }
        else if (s >= 0 && s < 4)
        {
            if (u->storedCount_4 + u->partyCount_6 == 0)
            {
                return 2;
            }
        }
        return 0;
    }
    switch (u->state_0)
    {
    case 5:
        if (!u->marks_84 && !u->partyMarks_88)
        {
            return 2;
        }
        return 0;
    case 1:
    case 8:
        if (u->base_4C->id == 4)
        {
            return 2;
        }
        return 0;
    case 2:
        if (u->partner_50->id == 4)
        {
            return 2;
        }
        if (u->partner_50 == u->base_4C)
        {
            return 3;
        }
        return 0;
    case 4:
        if (u->storedCount_4 + u->partyCount_6 < 2)
        {
            return 1;
        }
        return 0;
    case 14:
        if (GetInventorySlotId_800AD288(u->savedIndex_5E[8] + u->savedScroll_72[2], 4) == 0xFF)
        {
            return 4;
        }
        u->flags_24 |= 0x200;
        return 0;
    }
    return 0;
}
#endif
INCLUDE_OVERLAY_ASM(shop, CheckShopSelection_800BCF74);
// the jump table of CheckShopSelection_800BCF74 (asm; its targets are labels of the generated asm, gen_asm.jump_label): delete it and
// its externs in shop.h when the function is C, the switch emits it then
void* const jpt_800B9624[14] = { jtgt_800BD01C, jtgt_800BD03C, jtgt_800BD0C0, jtgt_800BD06C, jtgt_800BCFF4, jtgt_800BD0C0, jtgt_800BD0C0, jtgt_800BD01C, jtgt_800BD0C0, jtgt_800BD0C0, jtgt_800BD0C0, jtgt_800BD0C0, jtgt_800BD0C0, jtgt_800BD090 };

extern int IsInventory4NonEmpty_800AD398();
extern void ShopMenuExecute_800BD9DC(ShopMenu* u);
int CheckShopSelection_800BCF74(ShopMenu* u);
int IsMergePreviewState_800BD650(short* p);
int IsMinionListState_800BD678(ShopMenu* p);
void PreviewMerge_800BD720(ShopMenu* u);
// Matched
void HandleShopConfirmCancel_800BD0D4(ShopMenu* u)
{
    short s;
    int changed;
    int f;
    short k;
    s = 0;
    changed = 0;
    if (u->confirm_10)
    {
        s = CheckShopSelection_800BCF74(u);
        if (s == 0)
        {
            f = u->flags_24;
            if (f & 8)
            {
                if (u->list_7E == 0)
                {
                    u->flags_24 = f | 0x10;
                    u->partyIndex_58 = u->listIndex_30;
                    if (u->state_0 != 5)
                    {
                        u->marks_84 |= 1 << u->listIndex_30;
                        u->partyMarks_88 |= 1 << u->listIndex_30;
                    }
                }
                else
                {
                    u->flags_24 = f & ~0x10;
                    u->storedIndex_5A = u->listIndex_30;
                    u->storedScroll_5C = u->listScroll_32;
                    if (u->state_0 != 5)
                    {
                        u->marks_84 |= 1 << (u->listIndex_30 + u->listScroll_32 + 3);
                        u->storedMarks_8C |= 1 << (u->listIndex_30 + u->listScroll_32);
                    }
                }
            }
            if (stateConfirmNext_800BF868[u->state_0] >= 0)
            {
                if (u->state_0 == 1)
                {
                    MemCopy_800403E8(&mergePreview_800C08E8, u->base_4C, sizeof(Minion));
                }
                PlaySfx_80031494(0x7E);
                u->prevState_2 = u->state_0;
                u->state_0 = stateConfirmNext_800BF868[u->state_0];
                changed = 1;
                u->listScroll_32 = 0;
                u->listIndex_30 = 0;
                u->openTimer_C = 0;
            }
            else if (stateConfirmNext_800BF868[u->state_0] == -1)
            {
                u->prevState_2 = u->state_0;
                switch (u->state_0)
                {
                case 0:
                    if (u->listIndex_30 == 4)
                    {
                        PlaySfx_80031494(0x7E);
                        if (u->storedCount_4 < 13)
                        {
                            u->state_0 = 11;
                        }
                        else
                        {
                            u->state_0 = 12;
                        }
                    }
                    else
                    {
                        PlaySfx_80031494(0x7E);
                        u->state_0 = mainMenuStates_800BF8A8[u->listIndex_30];
                    }
                    break;
                case 4:
                    if (u->listIndex_30 == 0)
                    {
                        PlaySfx_80031494(0x7E);
                        u->state_0 = 1;
                        u->prevState_2 = 0;
                    }
                    else if (u->listIndex_30 == 1)
                    {
                        PlaySfx_80031494(0x7D);
                        u->state_0 = 0;
                    }
                    break;
                case 2:
                    PlaySfx_80031494(0x7E);
                    if (IsInventory4NonEmpty_800AD398())
                    {
                        u->state_0 = 13;
                    }
                    else
                    {
                        PreviewMerge_800BD720(u);
                        u->state_0 = 3;
                    }
                    u->prevState_2 = 2;
                    break;
                case 13:
                    if (u->listIndex_30 == 0)
                    {
                        PlaySfx_80031494(0x7E);
                        u->state_0 = 14;
                    }
                    else
                    {
                        PreviewMerge_800BD720(u);
                        u->state_0 = 3;
                    }
                    u->prevState_2 = 2;
                    break;
                case 14:
                    PlaySfx_80031494(0x7E);
                    PreviewMerge_800BD720(u);
                    u->state_0 = 3;
                    u->prevState_2 = 1;
                    break;
                case 8:
                    PlaySfx_80031494(0x7E);
                    u->prevState_2 = u->state_0;
                    if (u->flags_24 & 0x400)
                    {
                        u->state_0 = 15;
                        u->flags_24 &= ~0x400;
                    }
                    else
                    {
                        u->state_0 = 9;
                    }
                    break;
                }
                changed = 1;
                u->listScroll_32 = 0;
                u->listIndex_30 = 0;
                u->openTimer_C = 0;
            }
            else if (stateConfirmNext_800BF868[u->state_0] == -3)
            {
                PlaySfx_80031494(0x7E);
                ShopMenuExecute_800BD9DC(u);
            }
        }
        else
        {
            PlaySfx_80031494(0x7C);
            f = u->flags_24;
            if (f & 8)
            {
                if (u->list_7E == 0)
                {
                    u->flags_24 = f | 0x10;
                    u->partyIndex_58 = u->listIndex_30;
                }
                else
                {
                    u->flags_24 = f & ~0x10;
                    u->storedIndex_5A = u->listIndex_30;
                    u->storedScroll_5C = u->listScroll_32;
                }
            }
            u->errorId_8 = s;
            SetShopHelpText_800BBB54(u, 1);
            u->messageShown_18 = 1;
        }
    }
    else if (u->cancel_14)
    {
        if (u->state_0 != 0 || u->listIndex_30 != 4)
        {
            PlaySfx_80031494(0x7D);
            if (u->state_0 != 13 && u->state_0 != 14)
            {
                u->marks_84 = 0;
                u->partyMarks_88 = 0;
                u->storedMarks_8C = 0;
            }
            if (u->state_0 == 3)
            {
                if (u->savedList_7A[0] == 0)
                {
                    k = u->savedIndex_5E[1];
                    u->marks_84 |= 1 << k;
                    u->partyMarks_88 |= 1 << k;
                }
                else if (u->savedList_7A[0] == 1)
                {
                    k = u->savedIndex_5E[1] + u->savedScroll_72[0];
                    u->marks_84 |= 1 << (k + 3);
                    u->storedMarks_8C |= 1 << k;
                }
            }
            ShopMenuBack_800BB8C4(u);
            changed = 1;
        }
    }
    u->cancel_14 = 0;
    u->confirm_10 = 0;
    if (!(u->flags_24 & 4))
    {
        if (s == 0 && changed)
        {
            if (IsMergePreviewState_800BD650(&u->state_0))
            {
                u->flags_24 |= 2;
                SetShopHelpText_800BBB54(u, 3);
            }
            else
            {
                SetShopHelpText_800BBB54(u, 0);
            }
        }
        SetShopWindows_800BD7A8(u);
        if (IsMinionListState_800BD678(u))
        {
            u->flags_24 |= 8;
        }
        else
        {
            u->flags_24 &= ~8;
        }
        SetupShopCursor_800BD854(u);
    }
}

int IsMergePreviewState_800BD650(short* p)
{
    if (*p == 3 || *p == 13)
    {
        return 1;
    }
    return 0;
}

int IsMinionListState_800BD678(ShopMenu* p)
{
    switch (p->state_0)
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

int IsNoChosen_800BD6C4(ShopMenu* p)
{
    switch (*(short*)p)
    {
    case 3:
    case 4:
    case 6:
    case 9:
    case 13:
        if (p->listIndex_30 == 1)
        {
            return 1;
        }
    }
    return 0;
}
const int dword_800B96F0 = 0; // the alignment of jpt_800B96F4 (delete it with that table)

void PreviewMerge_800BD720(ShopMenu* u)
{
    int d;
    if (u->base_4C && u->partner_50)
    {
        if (u->flags_24 & 0x200)
        {
            d = GetInventorySlotId_800AD288(u->savedIndex_5E[8] + u->savedScroll_72[2], 4);
        }
        else
        {
            d = 10;
        }
        MergeMinions_800B9FC8(u->base_4C, u->partner_50, &mergePreview_800C08E8, d);
    }
}

void SetShopWindows_800BD7A8(ShopMenu* u)
{
    short i;
    unsigned short v;
    int s;
    v = u->windowsOpen_20;
    u->windows_1C = 0;
    s = stateWindows_800BF8B4[u->state_0];
    u->windowsOpen_20 = 0;
    u->windows_1C = s;
    for (i = 0; i < 7; i++)
    {
        if ((v >> i) & 1)
        {
            if ((stateWindows_800BF8B4[u->state_0] >> i) & 1)
            {
                u->windowsOpen_20 |= 1 << i;
            }
        }
    }
}

void SetupShopCursor_800BD854(ShopMenu* u)
{
    unsigned short* e = stateCursors_800BF7E8[u->state_0];
    int r;
    u->listCols_28 = e[0];
    u->listRows_2A = e[1];
    u->listCount_2C = e[2];
    u->listFlags_2E = e[3];
    if (u->windows_1C & 8)
    {
        if (u->state_0 == 4)
        {
            u->listIndex_30 = 0;
        }
        else
        {
            u->listIndex_30 = 1;
        }
    }
    if (u->state_0 == 3)
    {
        u->tabIndex_3C = 2;
    }
    if (u->flags_24 & 8)
    {
        if (u->list_7E == 0)
        {
            u->flags_24 |= 0x10;
            u->listCols_28 = 1;
            u->listFlags_2E = 0x20;
            u->listRows_2A = 3;
            u->listCount_2C = 3;
            if (u->state_0 == 2 || u->state_0 == 10)
            {
                u->listIndex_30 = u->partyIndex_58;
            }
        }
        else
        {
            u->flags_24 &= ~0x10;
            u->listCols_28 = 1;
            u->listRows_2A = 4;
            u->listCount_2C = 0x18;
            u->listFlags_2E = 0x50;
            if (u->state_0 == 2 || u->state_0 == 10)
            {
                u->listIndex_30 = u->storedIndex_5A;
                u->listScroll_32 = u->storedScroll_5C;
            }
        }
    }
    if (u->state_0 == 14)
    {
        r = GetLastInventorySlot_800AD308(4);
        if (r < 3)
        {
            r = 3;
        }
        u->listCount_2C = r + 1;
    }
}

#if 0
// Not matched (8 words): the two blocks that set tk = shopMenuTask_8008D670 + 0x10 before a call load
// shopMenuTask_8008D670 straight into s0 and add 0x10 in place; here the load goes to a temporary.
// (When writing this in C, delete the C table jpt_800B96F4 behind the function.)
extern void ShopWaitAreaReload_800BDD74();
extern void ShopWaitDarken_800BDE44();
extern void RequestAreaReload_80027314();
extern void StartSceneDarken_8001AAA8(int a);
extern void AddInventory_800AD184(int a, int b, int c);
extern int ExchangeMinions_800BAF54(short* a, short* b, short c, short d);
void ShopMenuExecute_800BD9DC(ShopMenu* u)
{
    EventEntry* tk;
    SaveData* sv;
    int* p;
    int any;
    short i;
    switch (u->state_0)
    {
    case 3:
        if (u->listIndex_30 != 0)
        {
            break;
        }
        sv = &saveData_8008B570;
        if (sv->settings_1C.bits.d_5 == 1)
        {
            MemCopy_800403E8(u->base_4C, &mergePreview_800C08E8, sizeof(Minion));
            SetMinionEmpty_800B9B44((short*)u->partner_50);
            if (u->base_4C->species_4C[0] == 0x23)
            {
                p = (int*)sv->allMinionsBitfields_814;
                p[1] |= 8;
            }
            else if (u->base_4C->species_4C[0] == 0x22)
            {
                p = (int*)sv->allMinionsBitfields_814;
                p[1] |= 4;
            }
            if (u->flags_24 & 0x200)
            {
                RemoveInventory_800AD1E0(GetInventorySlotId_800AD288(u->savedIndex_5E[8] + u->savedScroll_72[2], 4), 1, 4);
                CompactInventory_800AD3F0(4);
                u->flags_24 &= ~0x200;
            }
            u->marks_84 = 0;
            u->partyMarks_88 = 0;
            u->storedMarks_8C = 0;
            u->flags_24 |= 1;
            if (saveData_8008B570.settings_1C.bits.d_5 == 1)
            {
                tk = &shopMenuTask_8008D670->entry;
                fn_80027478(0x40, 1);
                fn_8002C014();
                RequestAreaReload_80027314();
                tk->cb_8 = ShopWaitAreaReload_800BDD74;
                break;
            }
        }
        u->fadeAction_94 = 1;
        u->flags_24 |= 0x800;
        tk = &shopMenuTask_8008D670->entry;
        fn_8001ABEC(1);
        tk->cb_8 = ShopWaitDarken_800BDE44;
        StartSceneDarken_8001AAA8(0x20);
        break;
    case 6:
        if (u->listIndex_30 != 0)
        {
            break;
        }
        any = 0;
        for (i = any; i < 27; i++)
        {
            if ((unsigned int)u->marks_84 & (1 << i))
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
        u->marks_84 = 0;
        u->partyMarks_88 = 0;
        u->storedMarks_8C = 0;
        u->flags_24 |= 1;
        if (saveData_8008B570.settings_1C.bits.d_5 == 1)
        {
            tk = &shopMenuTask_8008D670->entry;
            fn_80027478(0x40, 1);
            fn_8002C014();
            RequestAreaReload_80027314();
            tk->cb_8 = ShopWaitAreaReload_800BDD74;
        }
        else
        {
            u->fadeAction_94 = 2;
            u->flags_24 |= 0x800;
            tk = &shopMenuTask_8008D670->entry;
            fn_8001ABEC(1);
            tk->cb_8 = ShopWaitDarken_800BDE44;
            StartSceneDarken_8001AAA8(0x20);
        }
        break;
    case 9:
        ExchangeMinions_800BAF54((short*)u->base_4C, (short*)u->partner_50, u->savedList_7A[0] == 0 ? 3 : 2, u->savedList_7A[1] == 0 ? 3 : 2);
        u->marks_84 = 0;
        u->partyMarks_88 = 0;
        u->storedMarks_8C = 0;
        u->state_0 = 7;
        u->prevState_2 = 0;
        u->flags_24 |= 1;
        SetShopHelpText_800BBB54(u, 0);
        break;
    case 10:
        tk = &shopMenuTask_8008D670->entry;
        tk->cb_8 = ShopResumeAfterNameEntry_800BE128;
        tk->flags = (tk->flags & ~1) | 0x8000;
        ShopCtrlRequestNameEntry_800B6C6C(u->base_4C->status_84.name_10
, 0);
        SetFadeMode_8001C19C(0, 0x20);
        u->marks_84 = 0;
        u->partyMarks_88 = 0;
        u->storedMarks_8C = 0;
        break;
    case 11:
        u->flags_24 |= 4;
        break;
    case 12:
        u->state_0 = 0;
        break;
    }
}
#endif
INCLUDE_OVERLAY_ASM(shop, ShopMenuExecute_800BD9DC);
// the jump table of ShopMenuExecute_800BD9DC (asm; its targets are labels of the generated asm, gen_asm.jump_label): delete it and
// its externs in shop.h when the function is C, the switch emits it then
void* const jpt_800B96F4[10] = { jtgt_800BDA34, jtgt_800BDD58, jtgt_800BDD58, jtgt_800BDB4C, jtgt_800BDD58, jtgt_800BDD58, jtgt_800BDCEC, jtgt_800BDC7C, jtgt_800BDD40, jtgt_800BDD54 };
const ShopMenuWindows minionListWindow_800B971C = { 0, 0, 8, 0, 0, 14 };

void ShopWaitAreaReload_800BDD74(EventEntry* t, void* arg)
{
    ShopMenu* u = (ShopMenu*)arg;
    extern void ShopResumeAfterNameEntry_800BE128();
    extern void ShopResumeAfterSpin_800BE07C();
    if (fn_800272D0() == 0)
    {
        ResumeFieldMinions_800A7BF0(-1);
        if (u->state_0 == 3)
        {
            ExchangeEventResult_800A5F9C(1);
            t->cb_8 = ShopResumeAfterNameEntry_800BE128;
            ShopCtrlRequestNameEntry_800B6C6C(u->base_4C->status_84.name_10
, 1);
        }
        else if (u->state_0 == 6)
        {
            ExchangeEventResult_800A5F9C(2);
            t->cb_8 = ShopResumeAfterSpin_800BE07C;
            ShopCtrlRequestResume_800B6CC8();
        }
        t->flags = (t->flags & ~1) | 0x8000;
        fn_80027478(0x40, 0);
        RequestGameMode_800A6D30(1);
        eventDispatchHalt_8008B540 = 1;
    }
}

extern void ShopWaitBrighten_800BDEA8();
void ShopWaitDarken_800BDE44(EventEntry* t, int a)
{
    DrawMenuBackground_8002BE10();
    DrawShopMenu_800BC380(a);
    if (IsSceneFadeDone_8001AB94())
    {
        StopSceneDarken_8001AAF4();
        StartSceneBrighten_8001AB1C(0x20);
        t->cb_8 = ShopWaitBrighten_800BDEA8;
    }
}

void ShopWaitBrighten_800BDEA8(int dummy, ShopMenu* u)
{
    EventEntry* tk;
    SaveData* sv;
    int* p;
    DrawMenuBackground_8002BE10();
    DrawShopMenu_800BC380(u);
    if (IsSceneFadeDone_8001AB94())
    {
        tk = &shopMenuTask_8008D670->entry;
        if (u->fadeAction_94 == 1)
        {
            tk->cb_8 = ShopResumeAfterNameEntry_800BE128;
        }
        else if (u->fadeAction_94 == 2)
        {
            tk->cb_8 = ShopResumeAfterSpin_800BE07C;
        }
        tk->flags = (tk->flags & ~1) | 0x8000;
        fn_8002C014();
        if (u->fadeAction_94 == 1)
        {
            sv = &saveData_8008B570;
            if (!((sv->settings_1C.word >> 5) & 1))
            {
                MemCopy_800403E8(u->base_4C, &mergePreview_800C08E8, sizeof(Minion));
                SetMinionEmpty_800B9B44((short*)u->partner_50);
                if (u->base_4C->species_4C[0] == 0x23)
                {
                    p = (int*)sv->allMinionsBitfields_814;
                    p[1] |= 8;
                }
                else if (u->base_4C->species_4C[0] == 0x22)
                {
                    p = (int*)sv->allMinionsBitfields_814;
                    p[1] |= 4;
                }
                if (u->flags_24 & 0x200)
                {
                    RemoveInventory_800AD1E0(GetInventorySlotId_800AD288(u->savedIndex_5E[8] + u->savedScroll_72[2], 4), 1, 4);
                    CompactInventory_800AD3F0(4);
                    u->flags_24 &= ~0x200;
                }
                u->marks_84 = 0;
                u->partyMarks_88 = 0;
                u->storedMarks_8C = 0;
                u->flags_24 |= 1;
            }
            ShopCtrlRequestNameEntry_800B6C6C(u->base_4C->status_84.name_10
, 1);
            SetFadeMode_8001C19C(0, 0x20);
        }
        else if (u->fadeAction_94 == 2)
        {
            ShopCtrlRequestResume_800B6CC8();
            SetFadeMode_8001C19C(0, 0x20);
        }
        u->flags_24 &= ~0x800;
        fn_8001ABEC(0);
        u->fadeAction_94 = 0;
    }
}

extern void ShopWaitUiTiy_800BE210();
void ShopResumeAfterSpin_800BE07C(EventEntry* t, ShopMenu* u)
{
    u->state_0 = 5;
    u->prevState_2 = 0;
    SetShopWindows_800BD7A8(u);
    SetShopHelpText_800BBB54(u, 0);
    if (IsMinionListState_800BD678(u))
    {
        u->flags_24 |= 8;
    }
    else
    {
        u->flags_24 &= ~8;
    }
    SetupShopCursor_800BD854(u);
    u->listIndex_30 = u->savedIndex_5E[1];
    u->listScroll_32 = u->savedScroll_72[0];
    SuspendFieldMinions_800A7B00(-1);
    LoadUiTiy_8002BF74();
    t->cb_8 = ShopWaitUiTiy_800BE210;
}

void ShopResumeAfterNameEntry_800BE128(EventEntry* t, ShopMenu* u)
{
    if (u->state_0 == 9)
    {
        u->state_0 = 8;
    }
    else
    {
        u->state_0 = 4;
    }
    u->prevState_2 = 0;
    SetShopWindows_800BD7A8(u);
    SetShopHelpText_800BBB54(u, 0);
    if (IsMinionListState_800BD678(u))
    {
        u->flags_24 |= 8;
    }
    else
    {
        u->flags_24 &= ~8;
    }
    SetupShopCursor_800BD854(u);
    u->listIndex_30 = u->savedIndex_5E[1];
    u->listScroll_32 = u->savedScroll_72[0];
    if (u->state_0 == 4)
    {
        u->listIndex_30 = 0;
    }
    DrawMenuBackground_8002BE10();
    DrawShopMenu_800BC380(u);
    SetFadeMode_8001C19C(3, 0x20);
    SuspendFieldMinions_800A7B00(-1);
    t->cb_8 = ShopMenuTask_800BB444;
}

extern void ShopFadeInMenu_800BE264();
void ShopWaitUiTiy_800BE210(EventEntry* t, int a)
{
    if (uiTiyLoaded_8008B4E8)
    {
        DrawMenuBackground_8002BE10();
        DrawShopMenu_800BC380(a);
        t->cb_8 = ShopFadeInMenu_800BE264;
    }
}

extern void ShopMenuTask_800BB444();
void ShopFadeInMenu_800BE264(EventEntry* t, int a)
{
    DrawMenuBackground_8002BE10();
    DrawShopMenu_800BC380(a);
    SetFadeMode_8001C19C(3, 0x20);
    t->cb_8 = ShopMenuTask_800BB444;
}

extern void FormViewLoadTask_800BE4D0();
void StartFormView_800BE2B4(Minion* m)
{
    EventEntry* g = &shopMenuTask_8008D670->entry;
    PlaySfx_80031494(0x7E);
    ResetFormModel_800BF474();
    unknownFlags_8008D678 |= 0x10000;
    unknownFlags_8008D678 |= 0x4000000;
    LoadFormModel_800BF4B8(m);
    g->cb_8 = FormViewLoadTask_800BE4D0;
}

extern void ShopMenuTask_800BB444();
void FormViewTask_800BE334(EventEntry* t, ShopMenu* u)
{
    Actor* c;
    int v;
    DrawMenuBackground_8002BE10();
    DrawShopMenu_800BC380(u);
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
        if (u->state_0 == 3)
        {
            SetShopHelpText_800BBB54(u, 3);
        }
        else
        {
            SetShopHelpText_800BBB54(u, 0);
        }
        if (u->state_0 == 5)
        {
            u->confirm_10 = 0;
        }
        u->flags_24 &= ~0x20;
        t->cb_8 = ShopMenuTask_800BB444;
    }
}

extern void FormViewTask_800BE334();
void FormViewLoadTask_800BE4D0(EventEntry* t, ShopMenu* a)
{
    DrawMenuBackground_8002BE10();
    DrawShopMenu_800BC380(a);
    if (RunFormModelTask_800BF520() == 1)
    {
        SetShopHelpText_800BBB54(a, 2);
        ShowFormActor_800BF704(a->shopId_96);
        t->cb_8 = FormViewTask_800BE334;
    }
}

extern void InterpolateWindowRect_8004196C(void* a0, void* a1, int a2, int a3, int a4);
extern void DrawSmallText_8002FAA0(int a0, unsigned short* pos, char* name, int a3);
void DrawPartyList_800BE53C(ShopMenu* u)
{
    short r[4];
    short out[4];
    unsigned short p[2];
    ShopMenuWindows q;
    short sel;
    short h;
    int clut;
    short i;
    char* s;
    Minion* e;
    clut = 0;
    if (IsMinionListState_800BD678(u))
    {
        sel = u->listIndex_30;
    }
    else
    {
        sel = -1;
    }
    h = 8;
    if (!(u->windowsOpen_20 & 2))
    {
        h = u->openTimer_C;
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
        if (((unsigned int)u->marks_84 & (1 << i)) && ((unsigned int)u->partyMarks_88 & (1 << i)))
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
    q = minionListWindow_800B971C;
    q.time_4 = GetTime30Hz_8002C64C();
    q.open_8 = (short)h;
    q.items_10 = (int)partyListItems_800BFE24;
    if (u->flags_24 & 0x10)
    {
        q.cursor_C = (short)sel;
    }
    else
    {
        q.cursor_C = -1;
    }
    if (u->state_0 == 6 || u->state_0 == 9 || u->state_0 == 3 || u->state_0 == 15)
    {
        q.flags_0 |= 4;
    }
    else
    {
        q.flags_0 |= 2;
    }
    q.open_8 = 8;
    DrawMenuWindows_8002A5A4(&q);
    SetFontClutOffset_8003F900(1, 0);
}

void DrawStoredList_800BE7F0(ShopMenu* u)
{
    short r[4];
    short out[4];
    ShopPairShop p;
    ShopMenuWindows q;
    ShopPairShop pos1;
    ShopPairShop pos2;
    int base;
    short sel;
    short h;
    int clut;
    short i;
    char* s;
    Minion* e;
    int k;
    base = GetStoredListScroll_800BEB60(u);
    clut = 0;
    if (IsMinionListState_800BD678(u))
    {
        sel = u->listIndex_30;
    }
    else
    {
        sel = -1;
    }
    h = 8;
    if (!(u->windowsOpen_20 & 2))
    {
        h = u->openTimer_C;
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
        if (((unsigned int)u->marks_84 & (1 << (i + (short)base + 3))) && ((unsigned int)u->storedMarks_8C & (1 << (i + (short)base))))
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
    q = minionListWindow_800B971C;
    q.time_4 = GetTime30Hz_8002C64C();
    q.items_10 = (int)storedListItems_800BFF14;
    if (u->flags_24 & 0x10)
    {
        q.cursor_C = -1;
    }
    else
    {
        q.cursor_C = sel;
    }
    if (u->state_0 == 6 || u->state_0 == 9 || u->state_0 == 3 || u->state_0 == 15)
    {
        q.flags_0 |= 4;
    }
    else
    {
        q.flags_0 |= 2;
    }
    q.open_8 = 8;
    DrawMenuWindows_8002A5A4(&q);
    SetFontClutOffset_8003F900(1, 0);
    if (!(u->flags_24 & 0x10))
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

int GetStoredListScroll_800BEB60(ShopMenu* u)
{
    switch (u->state_0)
    {
    case 1:
    case 2:
    case 5:
    case 7:
    case 8:
    case 10:
        return u->listScroll_32;
    case 3:
    case 4:
    case 13:
    case 14:
        return u->savedScroll_72[1];
    case 6:
    case 9:
    case 15:
        return u->savedScroll_72[0];
    }
    return -1;
}

void UpdateSelectedMinions_800BEBC8(ShopMenu* u)
{
    int n;
    int v;
    switch (u->state_0)
    {
    case 1:
    case 5:
    case 7:
    case 8:
    case 15:
        if (u->flags_24 & 0x10)
        {
            n = 0;
            v = (unsigned short)u->savedIndex_5E[1];
        }
        else
        {
            n = 1;
            v = (unsigned short)u->savedIndex_5E[1] + GetStoredListScroll_800BEB60(u) + 3;
        }
        u->base_4C = GetShopMinion_800B9C5C((short)v);
        u->savedList_7A[0] = n;
        break;
    case 2:
    case 10:
        if (u->flags_24 & 0x10)
        {
            n = 0;
            v = (unsigned short)u->savedIndex_5E[2];
        }
        else
        {
            n = 1;
            v = (unsigned short)u->savedIndex_5E[2] + GetStoredListScroll_800BEB60(u) + 3;
        }
        u->partner_50 = GetShopMinion_800B9C5C((short)v);
        u->savedList_7A[1] = n;
        break;
    }
}

void UpdateShownMinion_800BECC8(ShopMenu* u)
{
    if (u->state_0 == 3)
    {
        switch (u->tabIndex_3C)
        {
        case 1:
            u->shown_54 = u->partner_50;
            return;
        case 0:
            goto def;
        case 2:
            u->shown_54 = &mergePreview_800C08E8;
            return;
        }
        return;
    }
    if (u->state_0 == 2 || u->state_0 == 10)
    {
        u->shown_54 = u->partner_50;
        return;
    }
def:
    u->shown_54 = u->base_4C;
}

extern void DrawScrollArrow_8002C6DC(void* p, int a, int b);
void DrawSkinList_800BED48(short* s)
{
    ShopMenuWindows q;
    short h = 8;
    short prev = s[0];
    short i;
    int id;
    int icon;
    int name;
    int cnt;
    int y;
    int n;
    for (i = 0; i < 4; i++)
    {
        id = GetInventorySlotId_800AD288(i + s[1], 4);
        if (id < 11)
        {
            icon = GetPersonIcon_8001CD6C(id);
            name = GetPersonName_8001CD3C(id);
            cnt = GetInventorySlotCount_800AD2C8(i + s[1], 4);
        }
        else
        {
            icon = -1;
            name = (int)aEmpty_800B6D7C;
            cnt = 0;
        }
        skinListRows_800C0258[i][0].val_4 = icon;
        skinListRows_800C0258[i][0].sprts_8 = &publicTiySprts_8008D434;
        skinListRows_800C0258[i][0].tpages_C = &publicTiyTPages_8008D440;
        skinListRows_800C0258[i][1].val_4 = name;
        skinListRows_800C0258[i][2].val_4 = cnt;
        skinListRows_800C0258[i][0].x_10 = 0x7B;
        y = i * 22 + 0x68;
        skinListRows_800C0258[i][0].y_12 = y;
        skinListRows_800C0258[i][1].x_10 = 0x90;
        skinListRows_800C0258[i][1].y_12 = y;
        skinListRows_800C0258[i][2].x_10 = 0xFB;
        skinListRows_800C0258[i][2].y_12 = y;
        s[0] = i;
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
    q.flags_0 = s[2];
    q.time_4 = frameCount_8008D3FC;
    q.open_8 = h;
    q.cursor_C = prev;
    q.items_10 = (int)skinListRows_800C0258;
    q.ot_14 = s[3];
    DrawMenuWindows_8002A5A4(&q);
    SetFontClutOffset_8003F900(2, 0);
    n = GetLastInventorySlot_800AD308(4) + 1;
    if (n < 4)
    {
        n = 4;
    }
    if (s[1] != 0)
    {
        DrawScrollArrow_8002C6DC(skinListUpArrowPos_800C0090, 3, s[3]);
    }
    if (s[1] < n - 4 && n >= 5)
    {
        DrawScrollArrow_8002C6DC(skinListDownArrowPos_800C0094, 1, s[3]);
    }
}

#if 0
// Not matched (17 words): the original cross-jumps the all-equal case into the o[1] == o[3] tail
// (o[4] += o[6]) and reloads o[6] in the o[2] != o[3] case; here the two tails get different registers.
typedef struct ShopLocalShop
{
    unsigned char b[4];
    int pad_4;
    int w[3];
} ShopLocalShop;
extern int GetElementHue_800BF2E4(unsigned char* p);
void BuildFormModelDesc_800BF02C(Minion* a, int* o, int c)
{
    ShopLocalShop l;
    unsigned int h = GetSpeciesModelDesc_80019C70(a->species_2)->modelId_0;
    int t;
    o[0] = GetTopSpecies_800338DC(a->species_4C, l.b, l.w);
    o[1] = GetSpeciesModelDesc_80019C70(l.b[0])->modelId_0;
    o[2] = GetSpeciesModelDesc_80019C70(l.b[1])->modelId_0;
    o[3] = GetSpeciesModelDesc_80019C70(l.b[2])->modelId_0;
    o[4] = l.w[0];
    o[5] = l.w[1];
    o[6] = l.w[2];
    if (o[1] == o[2])
    {
        if (o[2] == o[3])
        {
            o[4] = o[4] + o[5] + o[6];
            o[5] = 0;
            o[6] = 0;
            o[0] = 1;
        }
        else
        {
            t = o[6];
            o[0] = 2;
            o[4] = o[4] + o[5];
            o[6] = 0;
            o[2] = o[3];
            o[5] = t;
        }
    }
    else if (o[1] == o[3])
    {
        o[4] = o[4] + o[6];
        o[6] = 0;
        o[0] = 2;
    }
    else if (o[2] == o[3])
    {
        o[5] = o[5] + o[6];
        o[6] = 0;
        o[0] = 2;
    }
    o[11] = 0;
    if (o[1] != h)
    {
        if (o[2] == h)
        {
            t = o[5];
            o[2] = o[1];
            o[1] = h;
            o[5] = o[4];
            o[4] = t;
        }
        else if (o[3] == h)
        {
            t = o[6];
            o[3] = o[1];
            o[1] = h;
            o[6] = o[4];
            o[4] = t;
        }
        else if (o[0] < 2)
        {
            t = o[4];
            o[2] = o[1];
            o[1] = h;
            o[4] = 0;
            o[0] = 2;
            o[5] = t;
        }
        else
        {
            t = o[4];
            o[3] = o[1];
            o[1] = h;
            o[4] = 0;
            o[0] = 3;
            o[6] = t;
        }
    }
    o[7] = GetRankForLevel_80019A80(a->status_84.level_44);
    o[8] = o[0] - 1;
    o[10] = GetSpeciesModelDesc_80019C70(a->field_3)->modelId_0;
    o[12] = c;
    o[9] = GetElementHue_800BF2E4(a->status_84.element_3E);
    if (o[9] == -1000)
    {
        o[9] = GetSpeciesModelDesc_80019C70(a->field_3)->field_2 << 1;
    }
    else
    {
        o[9] = o[9] - (GetSpeciesModelDesc_80019C70(a->field_3)->field_3 << 1);

        if (o[9] < 0)
        {
            o[9] = o[9] + 0x168;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(shop, BuildFormModelDesc_800BF02C);

int GetElementHue_800BF2E4(unsigned char* p)
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
        goto done;
    }
    if (n == 2)
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
            goto done;
        }
        if (p[0] && p[2])
        {
            if (p[2] < p[0])
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
    r = ElementMixAngle_800BF3B4(p);
done:
    return r;
}

int ElementMixAngle_800BF3B4(unsigned char* p)
{
    int t2, t1, t4, t3, t5, t6, t7, t8;
    t1 = name_80084540[0].field_5C6 * p[0];
    t2 = name_80084540[3].field_5C6 * p[0];
    t3 = name_80084540[3].field_5C6 * p[3];
    t4 = name_80084540[2].field_5C6 * p[3];
    t5 = name_80084540[2].field_5C6 * p[2];
    t6 = name_80084540[1].field_5C6 * p[2];
    t7 = name_80084540[1].field_5C6 * p[1];
    t8 = name_80084540[0].field_5C6 * p[1];
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

void LoadFormModel_800BF4B8(Minion* m)
{
    ShopFormModel* c = &formModel_800C09E0;
    BuildFormModelDesc_800BF02C(m, c->desc_8, name_8007DC74);
    c->minion_4 = m;
    c->task_0 = StartModelTask_80010850(c->desc_8);
    c->actor_3C = 0;
}

// the caller reads the step result RunModelTask_80010A10 leaves in v0 (1: model loaded)
int RunFormModelTask_800BF520()
{
    RunModelTask_80010A10(formModel_800C09E0.task_0);
}

void FreeFormModelTask_800BF548()
{
    int v = formModel_800C09E0.task_0;
    formModel_800C09E0.task_0 = -1;
    FreeModelTask_8001098C(v);
}

#if 0 // near miss: store scheduling / temp registers (17 words)
void SpawnFormActor_800BF574(int* a, unsigned short* b)
{
    ShopSetupShop q;
    ShopFormModel* c = &formModel_800C09E0;
    int r = fn_80010A44(c->task_0);
    int v;
    int x;
    q.w0 = -1;
    q.w4 = 2;
    q.w8 = a[0];
    q.wC = a[1];
    q.w10 = a[2];
    q.s14 = b[0];
    q.s16 = b[1];
    v = c->desc_8[7];
    q.s18 = b[2];
    q.w28 = 0x1000;
    q.w30 = 1;
    q.w1C = 0;
    q.w20 = 4;
    q.w24 = -1;
    q.w2C = 4;
    q.w48 = r;
    q.w34 = (int)defaultBones_80079140;
    q.w38 = fn_80024E90(r, v);
    q.w3C = fn_80024EC8(r, v);
    q.w40 = fn_80024E38(r);
    q.w44 = fn_80024E64(r);
    c->actor_3C = fn_8001D45C(&q);
    x = fn_80024F00(r, v);
    r = fn_80024F38(r, v);
    fn_80019B14(*(int*)((char*)c->actor_3C + 0x134), x, r);
    fn_8001D68C(c->actor_3C, 0);
}
#endif
INCLUDE_OVERLAY_ASM(shop, SpawnFormActor_800BF574);

void DestroyFormActor_800BF6C4()
{
    ShopFormModel* c = &formModel_800C09E0;
    if (c->actor_3C)
    {
        DestroyActor_8001D600(c->actor_3C);
        c->actor_3C = 0;
    }
}

void ShowFormActor_800BF704()
{
    char a[12];
    char b[8];
    memset(a, 0, 12);
    memset(b, 0, 8);
    SpawnFormActor_800BF574(a, b);
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

ShopRect statusWindowRect_800BF790 = { 92, 94, 218, 117 };
ShopRect dialogWindowRect_800BF798 = { 80, 20, 223, 54 };
ShopRect partyLabelRect_800BF7A0 = { 10, 77, 71, 15 };
ShopRect storedLabelRect_800BF7A8 = { 10, 138, 71, 15 };
ShopRect mergeSlotRects_800BF7B0[3] = { { 92, 79, 60, 12 }, { 179, 79, 60, 12 }, { 261, 79, 49, 12 } }; // base, partner, result
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
int textStatsReturnA_800BF9B8[3] = { (int)aYouCanReturnToS_800B74C0, (int)aTheTriButton_800B74A4, (int)aEmpty_800B6D7C };
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
int textStatsReturnB_800BFAA8[3] = { (int)aUseTheTriButtonTo_800B7A60, (int)aReturnToTheStat_800B7A24, (int)aEmpty_800B6D7C };
int *stateTextsA_800BFAB4[16] = {
    (void *)textMainA_800BF8D4, (void *)textMergeBaseA_800BF8E0, (void *)textMergePartnerA_800BF8F8, (void *)textMergeConfirmA_800BF91C,
    (void *)textMergeAgainA_800BF928, (void *)textSpinSelectA_800BF8EC, (void *)textSpinConfirmA_800BF904, (void *)textPartyA_800BF910,
    (void *)textViewA_800BF934, (void *)textRenameA_800BF940, (void *)textExchangeA_800BF94C, (void *)textQuitA_800BF958,
    (void *)textFullA_800BF964, (void *)textSkinAskA_800BF970, (void *)textSkinPickA_800BF97C, (void *)textStatsA_800BF988,
};
int *stateTextsB_800BFAF4[16] = {
    (void *)textMainB_800BF9C4, (void *)textMergeBaseB_800BF9D0, (void *)textMergePartnerB_800BF9E8, (void *)textMergeConfirmB_800BFA0C,
    (void *)textMergeAgainB_800BFA18, (void *)textSpinSelectB_800BF9DC, (void *)textSpinConfirmB_800BF9F4, (void *)textPartyB_800BFA00,
    (void *)textViewB_800BFA24, (void *)textRenameB_800BFA30, (void *)textExchangeB_800BFA3C, (void *)textQuitB_800BFA48,
    (void *)textFullB_800BFA54, (void *)textSkinAskB_800BFA60, (void *)textSkinPickB_800BFA6C, (void *)textStatsB_800BFA78,
};
int *resultTextsA_800BFB34[16] = {
    0, 0, 0, (void *)textMergePreviewA_800BF994,
    0, (void *)textSpunA_800BF9A0, 0, 0,
    0, 0, 0, 0,
    0, (void *)textSkinIntroA_800BF9AC,
};
int *resultTextsB_800BFB74[21] = {
    0, 0, 0, (void *)textMergePreviewB_800BFA84,
    0, (void *)textSpunB_800BFA90, 0, 0,
    0, 0, 0, 0,
    0, (void *)textSkinIntroB_800BFA9C, 0, 0,
    (void *)aEmpty_800B6D7C, (void *)aNeedTwoJp_800B7AC8, (void *)aNoMinionsJp_800B7AB4, (void *)aCantChooseJp_800B7A9C,
    (void *)aNoSkinsJp_800B7A88,
};
const char *errNoneA_800BFBC8[3] = { aEmpty_800B6D7C, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char *errNeedTwoA_800BFBD4[3] = { aICanTMergeUnles_800B7AF8, aMinions_800B7AE4, aEmpty_800B6D7C };
const char *errNoMinionsA_800BFBE0[3] = { aWeDonTHaveAnyMi_800B7B3C, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char *errCantUseA_800BFBEC[3] = { aWeCanTUseThatMi_800B7B74, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char *errNoSkinsA_800BFBF8[3] = { aWeDonTHaveAnyMi_800B7BA8, aEmpty_800B6D7C, aEmpty_800B6D7C };
int *errorTextsA_800BFC04[10] = {
    (void *)errNoneA_800BFBC8, (void *)errNeedTwoA_800BFBD4, (void *)errNoMinionsA_800BFBE0, (void *)errCantUseA_800BFBEC,
    (void *)errNoSkinsA_800BFBF8, (void *)aEmpty_800B6D7C, (void *)aNeedTwoJp2_800B7C30, (void *)aNoMinionsJp2_800B7C18,
    (void *)aCantChooseJp2_800B7C00, (void *)aNoSkinsJp2_800B7BE8,
};
const char *errNoneB_800BFC2C[3] = { aEmpty_800B6D7C, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char *errNeedTwoB_800BFC38[3] = { aICanTMergeUnles_800B7AF8, aMinions_800B7AE4, aEmpty_800B6D7C };
const char *errNoMinionsB_800BFC44[3] = { aThereArenTAnyMi_800B7C50, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char *errCantUseB_800BFC50[3] = { aWeCanTUseThatMi_800B7B74, aEmpty_800B6D7C, aEmpty_800B6D7C };
const char *errNoSkinsB_800BFC5C[3] = { aThereArenTAnyMi_800B7C84, aEmpty_800B6D7C, aEmpty_800B6D7C };
int *errorTextsB_800BFC68[5] = { (void *)errNoneB_800BFC2C, (void *)errNeedTwoB_800BFC38, (void *)errNoMinionsB_800BFC44, (void *)errCantUseB_800BFC50, (void *)errNoSkinsB_800BFC5C };
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
int *mainHelpTextsA_800BFCF4[5] = { (void *)helpMergeA_800BFC7C, (void *)helpSpinA_800BFC88, (void *)helpPartyA_800BFC94, (void *)helpRenameA_800BFCA0, (void *)helpQuitA_800BFCAC };
int *mainHelpTextsB_800BFD08[5] = { (void *)helpMergeB_800BFCB8, (void *)helpSpinB_800BFCC4, (void *)helpPartyB_800BFCD0, (void *)helpRenameB_800BFCDC, (void *)helpQuitB_800BFCE8 };
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
int partyListItem0_800BFD7C[14] = {
    8, 0, 0, 0, 0x5D000D, 0xE0040, 0, 1,
    0, 0, 0, -1, -1, -1,
};
int partyListItem1_800BFDB4[14] = {
    8, 0, 0, 0, 0x6C000D, 0xE0040, 0, 1,
    0, 0, 0, -1, -1, -1,
};
int partyListItem2_800BFDEC[14] = {
    8, 0, 0, 0, 0x7B000D, 0xE0040, 0, 1,
    0, 0, 0, -1, -1, -1,
};
char partyListItems_800BFE24[16] = { 124, 253, 11, 128, 180, 253, 11, 128, 236, 253, 11, 128 };
int storedListItem0_800BFE34[14] = {
    8, 0, 0, 0, 0x9A000D, 0xE0040, 0, 1,
    0, 0, 0, -1, -1, -1,
};
int storedListItem1_800BFE6C[14] = {
    8, 0, 0, 0, 0xA9000D, 0xE0040, 0, 1,
    0, 0, 0, -1, -1, -1,
};
int storedListItem2_800BFEA4[14] = {
    8, 0, 0, 0, 0xB8000D, 0xE0040, 0, 1,
    0, 0, 0, -1, -1, -1,
};
int storedListItem3_800BFEDC[14] = {
    8, 0, 0, 0, 0xC7000D, 0xE0040, 0, 1,
    0, 0, 0, -1, -1, -1,
};
char storedListItems_800BFF14[20] = { 52, 254, 11, 128, 108, 254, 11, 128, 164, 254, 11, 128, 220, 254, 11, 128 };
char btnHelpSpinMarked_800BFF28[32] = { 16, 0, 0, 0, 132, 128, 11, 128, 167, 0, 0, 0, 120, 128, 11, 128, 110, 0, 0, 0, 108, 128, 11, 128, 255, 255, 255, 255 };
char btnHelpSpin_800BFF48[40] = { 16, 0, 0, 0, 132, 128, 11, 128, 167, 0, 0, 0, 120, 128, 11, 128, 94, 0, 0, 0, 168, 128, 11, 128, 110, 0, 0, 0, 148, 128, 11, 128, 255, 255, 255, 255 };
char btnHelpPartner_800BFF70[32] = { 16, 0, 0, 0, 132, 128, 11, 128, 167, 0, 0, 0, 120, 128, 11, 128, 110, 0, 0, 0, 148, 128, 11, 128, 255, 255, 255, 255 };
char btnHelpView_800BFF90[40] = { 16, 0, 0, 0, 232, 128, 11, 128, 167, 0, 0, 0, 120, 128, 11, 128, 110, 0, 0, 0, 148, 128, 11, 128, 94, 0, 0, 0, 188, 128, 11, 128, 255, 255, 255, 255 };
char btnHelpMergePreview_800BFFB8[40] = { 16, 0, 0, 0, 124, 109, 11, 128, 167, 0, 0, 0, 248, 128, 11, 128, 110, 0, 0, 0, 148, 128, 11, 128, 94, 0, 0, 0, 188, 128, 11, 128, 255, 255, 255, 255 };
char btnHelpFormView_800BFFE0[32] = { 167, 0, 0, 0, 120, 128, 11, 128, 153, 0, 0, 0, 124, 109, 11, 128, 154, 0, 0, 0, 8, 129, 11, 128, 255, 255, 255, 255 };
char btnHelpStats_800C0000[24] = { 94, 0, 0, 0, 188, 128, 11, 128, 167, 0, 0, 0, 120, 128, 11, 128, 255, 255, 255, 255 };
char btnHelpStatsPage_800C0018[32] = { 94, 0, 0, 0, 188, 128, 11, 128, 167, 0, 0, 0, 120, 128, 11, 128, 110, 0, 0, 0, 20, 129, 11, 128, 255, 255, 255, 255 };
char btnHelpPrompt_800C0038[16] = { 16, 0, 0, 0, 132, 128, 11, 128, 255, 255, 255, 255 };
char btnHelpSelect_800C0048[40] = { 16, 0, 0, 0, 132, 128, 11, 128, 167, 0, 0, 0, 120, 128, 11, 128, 94, 0, 0, 0, 168, 128, 11, 128, 110, 0, 0, 0, 148, 128, 11, 128, 255, 255, 255, 255 };
char btnHelpExchange_800C0070[32] = { 16, 0, 0, 0, 132, 128, 11, 128, 167, 0, 0, 0, 120, 128, 11, 128, 110, 0, 0, 0, 148, 128, 11, 128, 255, 255, 255, 255 };
char skinListUpArrowPos_800C0090[4] = { 200, 0, 97 };
char skinListDownArrowPos_800C0094[4] = { 200, 0, 198 };
int skinListRow0_800C0098[28] = {
    0x10010, 0, (int)&publicTiySprts_8008D434, (int)&publicTiyTPages_8008D440, 0x680053, 0x150015, 0x30003, 0x30010,
    0, 0, 0, 0x680068, 0x15006B, 0x40004, 0x80004, 0,
    0, 0, 0x6800D3, 0x15001C, 0x30000, 1, 0, 0,
    0, -1, -1, -1,
};
int skinListRow1_800C0108[28] = {
    0x10010, 0, (int)&publicTiySprts_8008D434, (int)&publicTiyTPages_8008D440, 0x680053, 0x150015, 0x30003, 0x30010,
    0, 0, 0, 0x680068, 0x15006B, 0x40004, 0x80004, 0,
    0, 0, 0x6800D3, 0x15001C, 0x30000, 1, 0, 0,
    0, -1, -1, -1,
};
int skinListRow2_800C0178[28] = {
    0x10010, 0, (int)&publicTiySprts_8008D434, (int)&publicTiyTPages_8008D440, 0x680053, 0x150015, 0x30003, 0x30010,
    0, 0, 0, 0x680068, 0x15006B, 0x40004, 0x80004, 0,
    0, 0, 0x6800D3, 0x15001C, 0x30000, 1, 0, 0,
    0, -1, -1, -1,
};
int skinListRow3_800C01E8[28] = {
    0x10010, 0, (int)&publicTiySprts_8008D434, (int)&publicTiyTPages_8008D440, 0x680053, 0x150015, 0x30003, 0x30010,
    0, 0, 0, 0x680068, 0x15006B, 0x40004, 0x80004, 0,
    0, 0, 0x6800D3, 0x15001C, 0x30000, 1, 0, 0,
    0, -1, -1, -1,
};
ShopMenuItem *skinListRows_800C0258[5] = { (void *)skinListRow0_800C0098, (void *)skinListRow1_800C0108, (void *)skinListRow2_800C0178, (void *)skinListRow3_800C01E8 };
char magicDescLines_800C026C[30][16] = {
    { 232, 139, 11, 128, 188, 139, 11, 128, 96, 139, 11, 128 },
    { 44, 139, 11, 128, 188, 139, 11, 128, 96, 139, 11, 128 },
    { 0, 139, 11, 128, 188, 139, 11, 128, 96, 139, 11, 128 },
    { 204, 138, 11, 128, 160, 138, 11, 128, 64, 138, 11, 128 },
    { 8, 138, 11, 128, 160, 138, 11, 128, 64, 138, 11, 128 },
    { 220, 137, 11, 128, 160, 138, 11, 128, 64, 138, 11, 128 },
    { 168, 137, 11, 128, 120, 137, 11, 128, 24, 137, 11, 128 },
    { 224, 136, 11, 128, 120, 137, 11, 128, 24, 137, 11, 128 },
    { 180, 136, 11, 128, 120, 137, 11, 128, 24, 137, 11, 128 },
    { 132, 136, 11, 128, 84, 136, 11, 128, 248, 135, 11, 128 },
    { 196, 135, 11, 128, 84, 136, 11, 128, 248, 135, 11, 128 },
    { 152, 135, 11, 128, 84, 136, 11, 128, 248, 135, 11, 128 },
    { 128, 135, 11, 128, 100, 135, 11, 128 },
    { 76, 135, 11, 128, 40, 135, 11, 128 },
    { 8, 135, 11, 128, 228, 134, 11, 128 },
    { 192, 134, 11, 128, 104, 134, 11, 128 },
    { 80, 134, 11, 128, 232, 133, 11, 128, 148, 133, 11, 128 },
    { 132, 133, 11, 128, 96, 133, 11, 128 },
    { 84, 133, 11, 128, 36, 133, 11, 128 },
    { 4, 133, 11, 128, 204, 132, 11, 128 },
    { 192, 132, 11, 128, 108, 132, 11, 128 },
    { 80, 132, 11, 128, 252, 131, 11, 128, 160, 131, 11, 128 },
    { 132, 131, 11, 128, 44, 131, 11, 128, 208, 130, 11, 128 },
    { 180, 130, 11, 128, 92, 130, 11, 128, 252, 129, 11, 128 },
    { 224, 129, 11, 128, 140, 129, 11, 128, 44, 129, 11, 128 },
};
char abilityDescLines_800C044C[624] = { 124, 109, 11, 128, 124, 109, 11, 128, 124, 109, 11, 128, 0, 0, 0, 0, 124, 109, 11, 128, 124, 109, 11, 128, 124, 109, 11, 128, 0, 0, 0, 0, 120, 149, 11, 128, 32, 149, 11, 128, 24, 137, 11, 128, 0, 0, 0, 0, 244, 148, 11, 128, 156, 148, 11, 128, 64, 138, 11, 128, 0, 0, 0, 0, 116, 148, 11, 128, 28, 148, 11, 128, 96, 139, 11, 128, 0, 0, 0, 0, 244, 147, 11, 128, 156, 147, 11, 128, 248, 135, 11, 128, 0, 0, 0, 0, 112, 147, 11, 128, 28, 147, 11, 128, 0, 0, 0, 0, 0, 0, 0, 0, 240, 146, 11, 128, 136, 146, 11, 128, 0, 0, 0, 0, 0, 0, 0, 0, 76, 146, 11, 128, 224, 145, 11, 128, 0, 0, 0, 0, 0, 0, 0, 0, 164, 145, 11, 128, 60, 145, 11, 128, 236, 144, 11, 128, 0, 0, 0, 0, 180, 144, 11, 128, 104, 144, 11, 128, 24, 144, 11, 128, 0, 0, 0, 0, 220, 143, 11, 128, 148, 143, 11, 128, 76, 143, 11, 128, 0, 0, 0, 0, 16, 143, 11, 128, 212, 142, 11, 128, 136, 142, 11, 128, 0, 0, 0, 0, 76, 142, 11, 128, 0, 142, 11, 128, 168, 141, 11, 128, 0, 0, 0, 0, 112, 141, 11, 128, 16, 141, 11, 128, 172, 140, 11, 128, 0, 0, 0, 0, 112, 140, 11, 128, 24, 140, 11, 128, 172, 140, 11, 128 };
int mainMenuItem0_800C06BC[14] = {
    0x10008, 43, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x4D000F, 0x140038, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int mainMenuItem1_800C06F4[14] = {
    0x10008, 185, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x64000F, 0x140038, 0x50000, 1,
    0, 0, 0, -1, -1, -1,
};
int mainMenuItem2_800C072C[14] = {
    0x10008, 145, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x7B000F, 0x140038, 0x30000, 1,
    0, 0, 0, -1, -1, -1,
};
int mainMenuItem3_800C0764[14] = {
    0x10010, 103, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x92000F, 0x140038, 0x5000E, 1,
    0, 0, 0, -1, -1, -1,
};
int mainMenuItem4_800C079C[14] = {
    0x10008, 53, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0xA9000F, 0x140038, 0x50000, 1,
    0, 0, 0, -1, -1, -1,
};
char mainMenuItems_800C07D4[28] = { 188, 6, 12, 128, 244, 6, 12, 128, 44, 7, 12, 128, 100, 7, 12, 128, 156, 7, 12, 128, 0, 0, 0, 0, 11, 128, 2, 60 };
unsigned int emptyMinion_800C07F0[62] = { 0 };
Minion mergePreview_800C08E8 = { 0 };
ShopFormModel formModel_800C09E0 = { 0 };
