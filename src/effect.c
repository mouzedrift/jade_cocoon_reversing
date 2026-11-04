#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "effect.h"
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
#include "effect_obj.h"
#include "effect.h"

const char aAssertionFaile_3[] = "Assertion failed: file \"%s\", line %d\n";
const char aEffectC[] = "EFFECT.C";
const int dword_80072134 = 0x80E8E8;
int dword_800795A0[12] = {
    0x200, 0x200, 0x200, 0x200, 0x200, 0x200, 0x200, 0x200,
    0x400, 0x400, 0x400, 0x400,
};
short dword_800795D0[2] = { 0 };
SVECTOR zeroSvector_800795D4 = { 0 };
int effectColorWhite_800795DC = 0xFFD6D6;
int effectColorRed_800795E0 = 0x6B00FF;
int effectColorBlue_800795E4 = 0xFF0015;
int effectColorGreen_800795E8 = 0x94FF00;
int effectColorYellow_800795EC = 0xFFEB;
short effectFileTable_800795F0[140] = {
    0x404, 0, 0x405, 0, 0x402, 0, 0x40A, 0,
    0x40B, 0, 0x401, 0, 0x400, 0, 0x407, 0,
    0x403, 0, 0x408, 0, 0x406, 0, 0x3FD, 0,
    0x3FE, 0, 0x3FF, 0, 0x40E, 0, 0x40D, 0,
    0x409, 0, 0x40C, 0, 0x433, 0, 0x3CA, 0,
    0x40F, 0, 0x411, 0, 0x419, 0, 0x41C, 0,
    0x421, 0, 0x3F8, -30, 0x3E9, 0, 0x3DF, 0,
    0x3E5, -30, 0x41F, 0, 0x41F, 0, 0x41F, 0,
    0x41F, 0, 0x3E1, 0, 0x3EB, 0, 0x428, 0,
    0x429, 0, 0x424, 0, 0x410, 0, 0x412, 0,
    0x41A, 0, 0x41D, 0, 0x3F5, 0, 0x3EF, 0,
    0x3F9, 0, 0x3EA, 0, 0x3E0, 0, 0x3E6, -10,
    0x3F6, 0, 0x3F4, 0, 0x3F3, 0, 0x3DE, 0,
    0x3EC, 0, 0x3E4, -93, 0x3F0, 0, 0x3E2, 0,
    0x3DD, 0, 0x42A, 0, 0x42B, 0, 0x41B, 0,
    0x418, 0, 0x417, 0, 0x3E7, -48, 0x415, 0,
    0x413, 0, 0x414, 0, 0x416, 0, 0x3F1, 0,
    0x3EE, 0, 0x3F2,
};

// Matched
int RollOilBonus_80013DB0(void)
{
    int v = rand() % 6;
    if (v)
    {
        v = 1;
    }
    else
    {
        v = 2;
    }
    return v;
}
// Matched
int GetStatGrowth_80013E00(unsigned int idx, int add)
{
    int result = 0;
    if (idx < 0x15)
    {
        result = statGrowthTable_80079348[idx] + add;
    }
    return result;
}
// Matched
int Rand100_80013E30(void)
{
    return rand() % 100;
}
// Matched
void CalcUnitEquippedStats_80013E80(unsigned char* p, int unit)
{
    CalcEquippedStats_80033624(p, GetUnitStatus_80014390(unit & 0xFF));
}
// Matched
void CalcMinionEquippedStats_80013EB4(unsigned char* p, int a1, int a2)
{
    CalcEquippedStats_80033624(p, GetMinionStatus_800107A0(a2)); // sic: one argument (GetMinionStatus_800107A0 is unprototyped)
}
int BaseSpeedRatio_80014200(unsigned char* p);
// Matched
void CalcBattleStats_80013EE8(int* out, UnitStatus* status, unsigned char* action, int mode)
{
    int a;
    int b;
    if (mode == 1)
    {
        out[0] = status->stats_2C.cur_0[0];
        out[2] = status->stats_2C.cur_0[2];
        out[4] = CalcHitBonus_80014114(10) + action[5];
        out[6] = CriticalRateTransform_80014164((unsigned char)(status->stats_2C.base_6[5] / 10));
        out[8] = 0;
        a = status->stats_2C.cur_0[1] * (status->stats_2C.cur_0[1] - 20) / 7;
        b = status->stats_2C.cur_0[3] * (status->stats_2C.cur_0[3] - 20) / 7;
        out[1] = (a < 0) ? 0 : ((a < 0x7FFF) ? a : 0x7FFF);
        out[3] = (b < 0) ? 0 : ((b < 0x7FFF) ? b : 0x7FFF);
        out[5] = CalcEvadeBonus_8001413C(10);
        out[7] = 0;
        out[9] = 100;
    }
    else
    {
        out[0] = status->stats_2C.cur_0[0];
        out[2] = status->stats_2C.cur_0[2];
        out[4] = CalcHitBonus_80014114(BaseSpeedRatio_80014200(status->stats_2C.cur_0) / 10) + action[5];
        out[6] = CriticalRateTransform_80014164((unsigned char)(status->stats_2C.base_6[5] / 10));
        out[8] = 0;
        out[1] = status->stats_2C.cur_0[1];
        out[3] = status->stats_2C.cur_0[3];
        out[5] = CalcEvadeBonus_8001413C(BaseSpeedRatio_80014200(status->stats_2C.cur_0) / 10);
        out[7] = 0;
        out[9] = BaseSpeedRatio_80014200(status->stats_2C.cur_0);

    }
}
// Matched
int CalcHitBonus_80014114(int x)
{
    return (x * x) / 10;
}
// Matched
int CalcEvadeBonus_8001413C(int x)
{
    return (x * x) / 5;
}
// Matched
int CriticalRateTransform_80014164(int x)
{
    return (x * x * x) / 400;
}
// Matched
void BaseStatRatios_8001419C(unsigned char* p, short* out)
{
    int a = (p[7] + p[9]) >> 1;
    int x = p[10] * 47 / (p[10] + a);
    int y = p[8] * 47 / (p[8] + p[6]);
    out[0] = x;
    out[1] = y;
}
// Matched
int BaseSpeedRatio_80014200(unsigned char* p)
{
    int a = (p[7] + p[9]) >> 1;
    int v = p[10] * 200 / (p[10] + a);
    if (v > 0)
    {
        if (v > 200)
        {
            v = 200;
        }
    }
    else
    {
        v = 1;
    }
    return v;
}
// Matched
int BaseDefenseRatio_8001425C(unsigned char* p)
{
    int a = (p[7] + p[9]) >> 1;
    int v = a * 200 / (a + p[10]);
    if (v > 0)
    {
        if (v > 200)
        {
            v = 200;
        }
    }
    else
    {
        v = 1;
    }
    return v;
}
// Matched
int BaseMagicRatio_800142B8(unsigned char* p)
{
    int v = p[8] * 200 / (p[8] + p[6]);
    if (v > 0)
    {
        if (v > 200)
        {
            v = 200;
        }
    }
    else
    {
        v = 1;
    }
    return v;
}
// Matched
int BaseAttackRatio_80014308(unsigned char* p)
{
    int v = p[6] * 200 / (p[6] + p[8]);
    if (v > 0)
    {
        if (v > 200)
        {
            v = 200;
        }
    }
    else
    {
        v = 1;
    }
    return v;
}
// Matched
int LowestSetBit_80014358(unsigned int mask)
{
    unsigned int i;
    for (i = 0; i < 32; i++)
    {
        if (mask & (1 << i))
        {
            return i;
        }
    }
    return 0;
}
#if 0
// Not matched (13 words): a0 and r swap saved registers ($s1/$s2), same problem as GetUnitStats_8001449C / GetUnitSkills_80031B30. Writing a0 = a0 - 1 in the last branch fixes them (6 words) but then writes $s1 and the w temps move to $a0; u_char a0 (with funcs.h changed): still swapped; r uninitialised + explicit r = 0: worse
UnitStatus* GetUnitStatus_80014390(int a0)
{
    UnitStatus* r = 0;
    unsigned int v = a0 & 0xFF;
    unsigned int w;
    if (v >= 8)
    {
        w = a0 - 8;
        r = GetSlotStatus_800A10C0(w & 0xFF);
    }
    else if (v >= 4)
    {
        int flags = sub_800A248C();
        int m = 1 << v;
        if (flags & m)
        {
            w = a0 - 4;
            r = sub_800A2B60(w & 0xFF);
        }
    }
    else if (v != 0)
    {
        w = a0 - 1;
        r = GetMinionStatus_800107A0(3, w & 0xFF);
    }
    else
    {
        r = &levantStatus_8008BD38; // == saveData_8008B570.levantStatus_7C8
    }
    return r;
}
#endif
INCLUDE_ASM(GetUnitStatus_80014390);
// Matched
Minion* GetUnitMinion_80014444(int unit)
{
    unsigned int v = unit & 0xFF;
    Minion* r = 0;
    if (v >= 8)
    {
        v = unit - 8;
        r = sub_800A11D8(v & 0xFF);
    }
    else if (v != 0)
    {
        v = unit - 1;
        r = GetMinion_80010598(3, v & 0xFF);
    }
    return r;
}
#if 0
// Not matched (2 words): with an int a0 the saved registers of a0 / r / a0 - 4 are permuted (original $s0/$s2/$s1, 11 words); u_char a0 (here) gets them right but masks a0 on entry (andi instead of move, a0 - 4 taken from the masked copy). a0 = 1 << a0 / a0 = flags & m also fix the registers but write $s0; tried K&R int/u_char, a0 copies, range test a0 >= 4 && a0 < 7, early returns, if/else r = 0; permuter 1500: best is this
UnitStats* GetUnitStats_8001449C(unsigned char a0)
{
    UnitStats* r = 0;
    int v = a0 - 4;
    if ((unsigned char)v < 3)
    {
        int flags = sub_800A248C();
        int m = 1 << a0;
        if (flags & m)
        {
            r = GetEnemyStats_800A2B20(v & 0xFF);
        }
    }
    return r;
}
#endif
INCLUDE_ASM(GetUnitStats_8001449C);
// Matched
void FirFilterInit_8001450C(int* a0, FirFilter* a1, int* a2, int a3)
{
    unsigned int i;
    FirFilterSetup_80014574(a1, a2, a3);
    for (i = 0; i < a1->taps_4; i++)
    {
        a0[i] = 0;
    }
}
// Matched
void FirFilterSetup_80014574(FirFilter* p, int* a1, int a2)
{
    p->coefs_0 = a1;
    p->taps_4 = a2;
    p->input_8 = 0;
    p->output_C.sum = 0;
}
// Matched
void FirFilterStep_80014588(int* a0, FirFilter* a1, unsigned int a2)
{
    unsigned int i;
    a0[a2 % a1->taps_4] = a1->input_8;
    a1->output_C.sum = 0;
    for (i = 0; i < a1->taps_4; i++)
    {
        a1->output_C.sum += a0[(a2 - i) % a1->taps_4] * a1->coefs_0[i];
    }
    a1->output_C.sum >>= 12;
}
void UpdateEffectTask_80014638(EventEntry* p, void* buf);
// Matched
void InitEffectTask_80014618(EventEntry* p, EffectTaskState* q)
{
    q->flags_28 = 2;
    q->timer_3C = 0;
    q->state_2C = 0;
    p->cb_8 = (EventEntryFn)UpdateEffectTask_80014638;
}
extern short dword_800795D0[];
extern short effectFileTable_800795F0[];
int CountActiveEffectObjects_800147FC(void);
// Matched
void UpdateEffectTask_80014638(EventEntry* p, void* buf)
{
    EffectTaskState* q = (EffectTaskState*)buf;
    int r;
    void* vlc;
    void* img;
    if (q->timer_3C > 0)
    {
        q->timer_3C--;
    }
    switch ((unsigned int)q->state_2C)
    {
    case 0:
        if (q->flags_28 & 4)
        {
            q->flags_28 &= ~2;
            q->flags_28 &= ~4;
            if (q->idx_38 >= 0x46)
            {
                q->idx_38 = 0x12;
            }
            LoadEffectFile_80020DDC(effectFileTable_800795F0[q->idx_38 * 2], &effectFile_80091BD0, dword_800795D0, dword_800795D0, 0, 0);
            q->state_2C = 1;
        }
        break;
    case 1:
        r = IsEffectFileLoaded_80020EBC(&effectFile_80091BD0);
        if (r == 1 && IsFileRequestQueueIdle_8003BF88() == r)
        {
            vlc = effectFile_80091BD0.mdec_34.dct_0;
            img = effectFile_80091BD0.mdec_34.work_4;
            q->state_2C = 2;
            mdecEffectVlcBuffer_8008D42C = vlc;
            decodedImageData_8008B4A0 = img;
        }
        break;
    case 2:
        if (q->flags_28 & 1)
        {
            q->flags_28 &= ~1;
            q->state_2C = 3;
        }
        break;
    case 3:
        if (CountActiveEffectObjects_800147FC() == 0 && q->timer_3C == 0 && !(q->flags_28 & 2))
        {
            FreeEffectFile_80020EE0(&effectFile_80091BD0);
            unknownFlags_8008D678 &= ~0x800;
            q->state_2C = 0;
            q->flags_28 |= 2;
        }
        break;
    }
}
// Matched
int CountActiveEffectObjects_800147FC(void)
{
    int i;
    int c;
    EventNode* head;
    EventNode* n;
    int count;
    EventNode* head2;
    EventNode* n2;
    int j;
    i = 0;
    head = effectObjects_8008B4A8;
    c = i;
    count = head->count;
    for (n = head; i < count; i++)
    {
        if ((n->entry.flags & 0x8001) == 1)
        {
            c++;
        }
        n = n->next;
    }
    head2 = dword_8008D60C;
    j = 0;
    count = head2->count;
    for (n2 = head2; j < count; j++)
    {
        if ((n2->entry.flags & 0x8001) == 1)
        {
            c++;
        }
        n2 = n2->next;
    }
    return c;
}
// Matched
void FreeEffectTask_800148A0(void)
{
    FreeEffectFile_80020EE0(&effectFile_80091BD0);
    unknownFlags_8008D678 &= ~0x800;
}
// Matched
int IsEffectTaskIdle_800148D4(void)
{
    return ((EffectTaskState*)effectTask_8008D3F8->entry.buffer)->state_2C == 0;
}
// Matched
void RequestEffect_800148F4(int a0)
{
    EffectTaskState* p = effectTask_8008D3F8->entry.buffer;
    p->flags_28 |= 4;
    p->idx_38 = a0;
    if (p->state_2C != 0)
    {
        printf(aAssertionFaile_3, aEffectC, 0x124);
        exit(1);
    }
}
