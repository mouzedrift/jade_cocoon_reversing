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
#include "msgwin.h"
#include "msg_window.h"
#include "effect_data.h"

const char aItSEmpty_8007474C[] = "\202h\202\224\201f\202\223\201@\202\205\202\215\202\220\202\224\202\231\201D"; // It's empty.
const char aItSLocked_80074764[] = "\202h\202\224\201f\202\223\201@\202\214\202\217\202\203\202\213\202\205\202\204\201D"; // It's locked.
const char aNeeded_80074780[] = "\201@\202\216\202\205\202\205\202\204\202\205\202\204\201D"; //  needed.
const char aGiven_80074794[] = "\201@\202\207\202\211\202\226\202\205\202\216\201D"; //  given.
const char aHandedOver_800747A4[] = "\201@\202\210\202\201\202\216\202\204\202\205\202\204\201@\202\217\202\226\202\205\202\222\201D"; //  handed over.
const char aUsed_800747C0[] = "\201@\202\225\202\223\202\205\202\204\201D"; //  used.
const char aReturned_800747D0[] = "\201@\202\222\202\205\202\224\202\225\202\222\202\216\202\205\202\204\201D"; //  returned.
const char aReceived_800747E8[] = "\201@\202\222\202\205\202\203\202\205\202\211\202\226\202\205\202\204\201D"; //  received.
const char aPickedUp_80074800[] = "\201@\202\220\202\211\202\203\202\213\202\205\202\204\201@\202\225\202\220\201D"; //  picked up.
const int dword_80074818 = 0;
// the jump table of UpdateMsgWindowState_80034C18 (asm; its targets are labels of the generated asm, gen_asm.jump_label):
// delete it (and dword_80074818, its alignment) and the externs in msg_window.h when the function is C
void* const jpt_8007481C[13] = { jtgt_80034F88, jtgt_80034C88, jtgt_80034D84, jtgt_80034E50, jtgt_80034F00, jtgt_80034F74, jtgt_80034F80, jtgt_80034F88, jtgt_80035280, jtgt_80034FB8, jtgt_80035000, jtgt_8003516C, jtgt_800351CC };

// Matched
int CheckMagicUsable_80034068(short* cmd)
{
    UnitStatus* target = GetUnitStatus_80014390(((unsigned char*)cmd)[2]);
    if (magicData_8007C438[cmd[0]].flags_0 & 0x40)
    {
        switch (magicData_8007C438[cmd[0]].kind_7)
        {
        case 0:
            if (target->hp_8.cur_0 == target->hp_8.max_2)
            {
                return 3;
            }
            break;
        case 1:
            if (cmd[0] != 0x10 && !(target->status_0 & 0x7FB))
            {
                return 3;
            }
            break;
        }
    }
    return 0;
}
// Matched
int CheckUsableStub_80034124(void)
{
    return 0;
}
// Matched
int GetUnitElementMask_8003412C(UnitStatus* unit)
{
    if (unit)
    {
        return unit->elementMask_42;
    }
    return 0;
}
// Matched
int IsCurrentMapListed_80034140(void)
{
    unsigned char*** table = mapListTable_80083800;
    SaveData* save = &saveData_8008B570;
    unsigned char** tbl = table[save->mapId_2E4[0].field_0];
    unsigned char* list;
    short target;
    short i;
    if (tbl)
    {
        list = tbl[save->mapId_2E4[1].field_0];
        if (list)
        {
            i = 0;
            if (list == mapLists4_800837D8)
            {
                target = save->mapId_2E4[3].field_0;
            }
            else
            {
                target = save->mapId_2E4[2].field_0;
            }
            while (list[i] != 0xFF)
            {
                if (list[i] == 200 || target == list[i])
                {
                    goto found;
                }
                i++;
            }
        }
        return 0;
    found:
        return 1;
    }
    return 0;
}
extern EventNode* messageWindowTask_8008D640;
typedef struct
{
    short w;
    short h;
} TextSize;
extern TextSize MeasureTextLines_8003E3B4(int* list);
extern TextSize MeasureTextLinesMasked_8003E2A8(int* list, unsigned int mask);
extern int MeasureTextWidth_8003E4C8(int str);
extern void GetPortraitPoly_800A6308(int a, void* b);
extern void GetCombatPortraitPoly_800A1B2C(int a, void* b);
extern short** FindTextResumePage_80034900(short** list);
extern void UpdateMessageWindow_80034BB8(int* a0, MsgWindow* a1);
typedef struct
{
    char pad_0[0xB4];
    int* list_B4[1];
} MsgWindowLists;
typedef struct
{
    char pad_0[0x1E4];
    signed char marks_1E4[0x30];
} MsgWindowMarks;
#define WL(n) (((MsgWindowLists*)w)->list_B4[n])
#define WS(off) (*(short*)((char*)w + (off)))
#define WI(off) (*(int*)((char*)w + (off)))
#if 0
// Not matched: 41 lines; scheduling of the 0x14 store vs the 0x8/0xC/0x10 stores, and the shared tail (x+0xA) lands in a0 instead of v0
EventEntry* OpenMessageWindow_8003422C(int* cfg)
{
    unsigned short x;
    EventEntry* e;
    int* w;
    int** list;
    int* p;
    int n;
    int i;
    TextSize sz;
    int c;
    signed char* q;

    e = AllocEventEntry_80043AF8(messageWindowTask_8008D640);
    if (!e)
    {
        return 0;
    }
    w = (int*)e->buffer;
    WI(0x0) = (int)e;
    WI(0x4) = 0;
    WI(0x14) = 0;
    WS(0x18) = 0;
    WS(0x1A) = 0;
    WS(0x1C) = 0;
    WS(0x1E) = 0;
    WI(0x20) = 0;
    WI(0x24) = 0;
    WI(0x34) = 0;
    WS(0x38) = 0;
    WS(0x3A) = 0;
    WS(0x3C) = 0;
    WS(0x3E) = 0;
    WI(0x48) = 0;
    WS(0x4C) = 0;
    WS(0x4E) = 0;
    WS(0x50) = 0;
    WS(0x52) = 0;
    WI(0x54) = 0;
    WI(0x78) = 0;
    WI(0x7C) = 0;
    WS(0xB0) = 0;
    WS(0xB2) = 0;
    WI(0x1B4) = 0;
    if (cfg[0x28 / 4] == 0 && cfg[0x2C / 4] != 0)
    {
        WI(0x68) = 1;
    }
    else
    {
        WI(0x68) = 0;
    }
    WS(0x6C) = 0;
    WI(0x2C) = cfg[0x3C / 4];
    WI(0x30) = cfg[0x38 / 4];
    n = cfg[0x44 / 4];
    WI(0x2A4) = n;
    if (!(saveData_8008B570.settings_1C.bytes[3] & 1) && n == 1)
    {
        WI(0x4) |= 0x40000;
    }
    WI(0x14) = cfg[0x18 / 4];
    WI(0x8) = 0;
    WI(0xC) = 1;
    WI(0x10) = 0;
    WI(0x28) = cfg[0x14 / 4];
    WI(0x74) = cfg[0xC / 4];
    WI(0x84) = cfg[0x20 / 4];
    if (cfg[0x20 / 4] == 1)
    {
        GetPortraitPoly_800A6308(cfg[0x24 / 4], (char*)w + 0x88);
    }
    else if (cfg[0x20 / 4] == 7)
    {
        GetCombatPortraitPoly_800A1B2C(cfg[0x24 / 4], (char*)w + 0x88);
        WI(0x84) = 1;
    }
    list = (int**)cfg[0x8 / 4];
    if (list)
    {
        list = (int**)FindTextResumePage_80034900((short**)list);
        while (*list)
        {
            WS(0x1C)++;
            WL(WI(0x7C)++) = (int*)list;
            sz = MeasureTextLines_8003E3B4((int*)list);
            if (WS(0x3C) < sz.w)
            {
                WS(0x3C) = sz.w;
            }
            if (WS(0x3E) < sz.h)
            {
                WS(0x3E) = sz.h;
            }
            while (*list++)
            {
            }
        }
        WL(WI(0x7C)) = 0;
    }
    p = (int*)cfg[0x1C / 4];
    if (p)
    {
        if (IsTextMarkerLine_8003E484(*p) == 1)
        {
            WI(0x1B4) = (int)(p + 1);
        }
        else
        {
            WI(0x1B4) = (int)p;
        }
        sz = MeasureTextLinesMasked_8003E2A8((int*)WI(0x1B4), WI(0x14));
        WS(0x18) = CountUntilZero_80034B14((int*)WI(0x1B4));
        WS(0x50) = sz.w;
        WS(0x52) = sz.h;
        WS(0xB0) = CountMaskedUntilZero_80034B40((int*)WI(0x1B4), WI(0x14));
    }
    c = -1;
    WS(0x1BC) = 0;
    WS(0x1BE) = 0;
    WS(0x1C0) = 0;
    WS(0x1C2) = 0;
    WI(0x1C8) = 0;
    WI(0x1D4) = 0;
    WI(0x1D8) = 0;
    WI(0x1DC) = 0;
    WI(0x1E0) = 1;
    for (i = 0x2F, q = (signed char*)w + i; i >= 0; i--, q--)
    {
        q[0x1E4] = c;
    }
    WI(0x1CC) = cfg[0x10 / 4];
    WI(0x1C4) = (int)WL(WI(0x78));
    WI(0x1D0) = cfg[0x38 / 4];
    WS(0x3E) = 0x38;
    WS(0x3C) = 0xDB;
    WS(0x46) = 0x43;
    WS(0x44) = 0x46;
    WS(0x50) += 0x11;
    WS(0x52) += 7;
    if (cfg[0x28 / 4] == 1)
    {
        if (cfg[0x4 / 4])
        {
            WS(0x40) = ((short*)cfg[0x4 / 4])[0];
            WS(0x42) = ((short*)cfg[0x4 / 4])[0] + ((short*)cfg[0x4 / 4])[1];
            WS(0x38) = WS(0x40) + 0x45;
            WS(0x3A) = WS(0x42) + 0xE;
            WS(0x6E) = WS(0x38) + WS(0x3C) - MeasureTextWidth_8003E4C8(WI(0x74)) - 0x10;
            WS(0x70) = WS(0x3A) - 0xC;
        }
        else
        {
            switch ((unsigned int)cfg[0])
            {
            case 0:
                WS(0x42) = WS(0x40) = 0x10;
                WS(0x38) = WS(0x40) + 0x44;
                WS(0x3A) = WS(0x42) + 0xD;
                WS(0x6E) = WS(0x38) + WS(0x3C) - MeasureTextWidth_8003E4C8(WI(0x74)) - 0x10;
                WS(0x70) = WS(0x3A) + WS(0x3E) - 2;
                break;
            case 1:
                WS(0x40) = 0x10;
                WS(0x42) = 0x74;
                WS(0x38) = WS(0x40) + 0x44;
                WS(0x3A) = WS(0x42) + 0xD;
                WS(0x6E) = WS(0x38) + WS(0x3C) - MeasureTextWidth_8003E4C8(WI(0x74)) - 0x10;
                WS(0x70) = WS(0x3A) - 0x10;
                break;
            case 2:
                WS(0x40) = 0x10;
                WS(0x42) = 0xA1;
                WS(0x38) = WS(0x40) + 0x44;
                WS(0x3A) = WS(0x42) + 0xD;
                WS(0x6E) = WS(0x38) + WS(0x3C) - MeasureTextWidth_8003E4C8(WI(0x74)) - 0x10;
                WS(0x70) = WS(0x3A) - 0x10;
                break;
            }
        }
        x = WS(0x40);
    }
    else
    {
        if (cfg[0x4 / 4])
        {
            WS(0x40) = ((short*)cfg[0x4 / 4])[0];
            WS(0x42) = ((short*)cfg[0x4 / 4])[0] + ((short*)cfg[0x4 / 4])[1];
            WS(0x38) = WS(0x40) + 0x45;
            WS(0x3A) = WS(0x42) + 0xD;
            WS(0x6E) = WS(0x38) + WS(0x3C) - MeasureTextWidth_8003E4C8(WI(0x74)) - 0x10;
            WS(0x70) = WS(0x3A) - 0xC;
        }
        else
        {
            switch ((unsigned int)cfg[0])
            {
            case 0:
                WS(0x42) = WS(0x38) = 0x10;
                WS(0x40) = WS(0x38) + 0xDA;
                WS(0x3A) = WS(0x42) + 0xD;
                WS(0x6E) = WS(0x40) + WS(0x44) - MeasureTextWidth_8003E4C8(WI(0x74)) - 0x10;
                WS(0x70) = WS(0x42) + WS(0x46) - 2;
                break;
            case 1:
                WS(0x42) = 0x60;
                WS(0x38) = 0x10;
                WS(0x3A) = WS(0x42) + 0xD;
                WS(0x40) = WS(0x38) + 0xDA;
                WS(0x6E) = WS(0x38);
                WS(0x70) = WS(0x3A) - 0x10;
                break;
            case 2:
                WS(0x42) = 0xA1;
                WS(0x38) = 0x10;
                WS(0x3A) = WS(0x42) + 0xD;
                WS(0x40) = WS(0x38) + 0xDA;
                WS(0x6E) = WS(0x38);
                WS(0x70) = WS(0x3A) - 0x10;
                break;
            }
        }
        x = WS(0x38);
    }
    WS(0x4C) = x + 0xA;
    WS(0x4E) = WS(0x3A) + WS(0x3E) + 3;
    WS(0x70) -= 2;
    WS(0x3A) -= 2;
    WS(0x64) = WS(0x40) + 3;
    WS(0x66) = WS(0x42) + 2;
    WS(0x1B8) = WS(0x38) + 7;
    WS(0x1BA) = WS(0x3A) + 4;
    e->cb_8 = (EventEntryFn)UpdateMessageWindow_80034BB8;
    e->flags = (e->flags | 1) & ~0x8000;
    return e;
}
#endif
INCLUDE_ASM(OpenMessageWindow_8003422C);
extern unsigned short* EncodeText_8003F684(int mode, unsigned short* s);
// Matched
short** FindTextResumePage_80034900(short** list)
{
    short** cur = list;
    short* text;
    while (*cur)
    {
        text = (short*)EncodeText_8003F684(2, (unsigned short*)*cur);
        if (*text == 0xC1)
        {
            *text = 0xC2;
            return list;
        }
        if (*text == 0xC2)
        {
            return cur;
        }
        cur++;
        if (!*cur)
        {
            cur++;
        }
    }
    return list;
}
// Matched
int GetMsgWindowResultIfDone_800349B4(MsgWindowEntry* entry, MsgResult* out)
{
    MsgWindow* win = entry->win_14;
    if (win->flags_4 & 0x200)
    {
        *out = win->res_18;
        return 1;
    }
    return 0;
}
// Matched
void GetMsgWindowResult_80034A00(MsgWindowEntry* entry, MsgResult* out)
{
    *out = entry->win_14->res_18;
}
// Matched
int IsMsgWindowWaiting_80034A30(MsgWindowEntry* entry)
{
    MsgWindow* win = entry->win_14;
    if (win->field_C == 3 || win->field_10 == 2)
    {
        return 1;
    }
    return 0;
}
// Matched
void EnableMsgWindowAdvance_80034A68(MsgWindowEntry* entry)
{
    entry->win_14->flags_4 |= 0x800;
}
// Matched
void CloseMsgWindow_80034A84(MsgWindowEntry* entry)
{
    entry->win_14->flags_4 |= 0x4000;
}
// Matched
void KillMsgWindow_80034AA0(MsgWindowEntry* entry)
{
    entry->flags_0 = (entry->flags_0 & ~1) | 0x8000;
}
// Matched
int IsMsgWindowAlive_80034AB8(MsgWindowEntry* entry)
{
    return (entry->flags_0 & 0x8001) == 1;
}
// Matched
void SetMsgWindowChoiceMask_80034AD0(MsgWindowEntry* entry, int mask)
{
    entry->win_14->mask_14 = mask;
}
// Matched
int ConsumeMsgWindowMark_80034ADC(MsgWindowEntry* entry, int idx)
{
    MsgWindow* win = entry->win_14;
    if (win->marks_1E4[idx] == -2 || win->marks_1E4[idx] >= 0)
    {
        win->marks_1E4[idx] = -2;
        return 1;
    }
    return 0;
}
// Matched
int CountUntilZero_80034B14(int* list)
{
    int count = 0;
    while (*list)
    {
        list++;
        count++;
    }
    return count;
}
// Matched
int CountMaskedUntilZero_80034B40(int* list, unsigned int mask)
{
    int count = 0;
    int i = 0;
    if (*list)
    {
        do
        {
            if (mask & (1 << i))
            {
                count++;
            }
            list++;
            i++;
        } while (*list);
    }
    return count;
}
// Matched
int NthMaskedIndex_80034B88(int n, unsigned int mask)
{
    int i = 0;
    if (n >= 0)
    {
        do
        {
            if (mask & (1 << i))
            {
                n--;
            }
            i++;
        } while (n >= 0);
    }
    return i - 1;
}
extern void UpdateMsgWindowState_80034C18(MsgWindow* a);
extern void HandleMsgWindowInput_800353A0(MsgWindow* o);
// Matched
void UpdateMessageWindow_80034BB8(int* entry, MsgWindow* win)
{
    UpdateMsgWindowState_80034C18(win);
    HandleMsgWindowInput_800353A0(win);
    if (win->mode_8 == 7)
    {
        entry[0] = (entry[0] & ~1) | 0x8000;
    }
}
extern void PlaySfx_80031494(int id);
extern void InterpolateWindowRect_8004196C(void* a0, void* a1, int a2, int a3, int a4);
extern int IsWindowFrameFit_800429A8(void* r);
/* defined below (their parameter types are declared there) */
extern int DrawMsgWindowText_8003580C();
extern void DrawMsgWindowTitle_800359F8();
extern void DrawMsgWindowPortrait_80035900();
extern void DrawMsgWindowChoices_800355EC();
#define PI(off) (*(int*)((char*)p + (off)))
#if 0
// Not matched (30 lines, same length): control flow and jump tables right (needs the C table jpt_8007481C and dword_80074818 removed).
// Left: the flags temporaries get $v1 where the original has $a0 (first block) / $v0 (case 4), the DrawMsgWindowText
// result v is in $a0 instead of $a1, and the reset block reloads page_78 (the original keeps it in $v1, with the fill
// loop counter in another register; i = page_78 plus a separate counter fixes that but loses an instruction elsewhere).
// Got closer with: unsigned switch on field_10, c = -1 after the flag clears, f1 = p[1] & ~0x40000 in the first block
void UpdateMsgWindowState_80034C18(MsgWindow* w)
{
    int* p = (int*)w;
    short r[4];
    int c;
    int i;
    signed char* q;
    int v;
    int f1;
    int f2;
    int f3;
    int f4;
    int f5;
    int f6;
    int f7;

    if (p[1] & 0x80000)
    {
        f1 = p[1] & ~0x40000;
        f1 &= ~0x80000;
        p[1] = f1;
    }
    switch (p[2])
    {
    case 0:
        break;
    case 1:
        if (p[0x2C / 4] == 1 || (p[1] & 0x800))
        {
            if (!(p[1] & 0x8000))
            {
                p[1] |= 0x8000;
            }
            if (!(p[1] & 0x40000))
            {
                DrawMsgWindowNextPrompt_8003E268((unsigned short*)(p + 0x1B8 / 4));
            }
        }
        if (p[1] & 0x200)
        {
            if (!(p[1] & 0x20000))
            {
                PlaySfx_80031494(0x7F);
            }
            f2 = p[1];
            f2 &= ~0x20000;
            f2 &= ~0x8000;
            f2 &= ~0x200;
            p[1] = f2;
            c = -1;
            PI(0x1C4) = (int)((MsgWindowLists*)p)->list_B4[PI(0x78)];
            PI(0x1C8) = 0;
            PI(0x1D4) = 0;
            PI(0x1D8) = 0;
            PI(0x1DC) = 0;
            PI(0x1E0) = 1;
            for (i = 0x2F, q = (signed char*)p + i; i >= 0; i--, q--)
            {
                q[0x1E4] = c;
            }
            p[2] = 0;
            p[3] = 2;
        }
        break;
    case 2:
        if (p[0x2C / 4] == 1 || (p[1] & 0x800))
        {
            if (!(p[1] & 0x8000))
            {
                p[1] |= 0x8000;
            }
            if (!(p[1] & 0x40000))
            {
                DrawMsgWindowNextPrompt_8003E268((unsigned short*)(p + 0x1B8 / 4));
            }
        }
        if (p[1] & 0x200)
        {
            if (!(p[1] & 0x20000))
            {
                PlaySfx_80031494(0x7F);
            }
            f3 = p[1];
            f3 &= ~0x20000;
            f3 &= ~0x8000;
            f3 &= ~0x200;
            p[1] = f3;
        }
        if (p[1] & 0x4000)
        {
            f4 = p[1];
            f4 &= ~0x8000;
            f4 &= ~0x4000;
            p[1] = f4;
            p[2] = 6;
        }
        break;
    case 3:
        if (p[1] & 0x200)
        {
            if (!(p[1] & 0x20000))
            {
                PlaySfx_80031494(0x7F);
            }
            p[2] = 5;
            f5 = p[1];
            f5 &= ~0x20000;
            f5 &= ~0x200;
            p[1] = f5;
        }
        else if (p[1] & 0x10000)
        {
            if (!(p[1] & 0x20000))
            {
                PlaySfx_80031494(0x7D);
            }
            f6 = p[1];
            f6 &= ~0x20000;
            f6 &= ~0x10000;
            p[1] = f6;
        }
        if (p[1] & 0x4000)
        {
            p[1] &= ~0x4000;
            p[2] = 6;
        }
        break;
    case 4:
        if (p[1] & 0x200)
        {
            if (!(p[1] & 0x20000))
            {
                PlaySfx_80031494(0x7F);
            }
            f7 = p[1];
            p[4] = 1;
            p[2] = 0;
            f7 &= ~0x20000;
            f7 &= ~0x200;
            p[1] = f7;
        }
        if (!(p[1] & 0x40000))
        {
            DrawMsgWindowNextPrompt_8003E268((unsigned short*)(p + 0x1B8 / 4));
        }
        break;
    case 5:
        p[4] = 3;
        break;
    case 6:
        p[3] = 4;
        break;
    case 7:
        break;
    }
    switch (p[3])
    {
    case 0:
        break;
    case 1:
        p[0x34 / 4]++;
        if (p[0x34 / 4] >= 8)
        {
            p[0x34 / 4] = 8;
            p[3] = 2;
        }
        InterpolateWindowRect_8004196C(r, p + 0x38 / 4, p[0x34 / 4], 8, 0);
        DrawMsgWindowBackground_80035898(p, (int)r, 2);
        DrawMsgWindowBorder_800358CC(p, (int)r, 0);
        InterpolateWindowRect_8004196C(r, p + 0x40 / 4, p[0x34 / 4], 8, 0);
        DrawMsgWindowBackground_80035898(p, (int)r, 2);
        DrawMsgWindowBorder_800358CC(p, (int)r, 0);
        break;
    case 2:
        DrawMsgWindowTitle_800359F8(p);
        DrawMsgWindowPortrait_80035900(p);
        v = DrawMsgWindowText_8003580C(p, p + 0x38 / 4);
        if (v == 1)
        {
            p[3] = 3;
            PI(0x78)++;
            if ((int)((MsgWindowLists*)p)->list_B4[PI(0x78)])
            {
                p[2] = v;
                if (p[1] & 0x40000)
                {
                    if (((MsgWindowLists*)p)->list_B4[PI(0x78) + 1] == 0 && PI(0x1B4))
                    {
                        c = -1;
                        PI(0x1C8) = 0;
                        PI(0x1D4) = 0;
                        PI(0x1D8) = 0;
                        PI(0x1DC) = 0;
                        PI(0x1E0) = v;
                        PI(0x1C4) = (int)((MsgWindowLists*)p)->list_B4[PI(0x78)];
                        for (i = 0x2F, q = (signed char*)p + i; i >= 0; i--, q--)
                        {
                            q[0x1E4] = c;
                        }
                        p[3] = 1;
                        p[0x34 / 4] = 0;
                        p[2] = 0;
                        p[4] = 0;
                        p[1] |= 0x80000;
                    }
                }
            }
            else if (PI(0x1B4))
            {
                p[2] = 4;
            }
            else
            {
                p[2] = 2;
                p[9] = v;
            }
        }
        DrawMsgWindowBackground_80035898(p, (int)(p + 0x38 / 4), 2);
        DrawMsgWindowBorder_800358CC(p, (int)(p + 0x38 / 4), 0);
        DrawMsgWindowBackground_80035898(p, (int)(p + 0x40 / 4), 2);
        DrawMsgWindowBorder_800358CC(p, (int)(p + 0x40 / 4), 0);
        break;
    case 3:
        DrawMsgWindowTitle_800359F8(p);
        DrawMsgWindowPortrait_80035900(p);
        DrawMsgWindowText_8003580C(p, p + 0x38 / 4);
        DrawMsgWindowBackground_80035898(p, (int)(p + 0x38 / 4), 2);
        DrawMsgWindowBorder_800358CC(p, (int)(p + 0x38 / 4), 0);
        DrawMsgWindowBackground_80035898(p, (int)(p + 0x40 / 4), 2);
        DrawMsgWindowBorder_800358CC(p, (int)(p + 0x40 / 4), 0);
        break;
    case 4:
        p[0x34 / 4]--;
        if (p[0x34 / 4] <= 0)
        {
            p[0x34 / 4] = 0;
            p[3] = 0;
            p[2] = 7;
        }
        InterpolateWindowRect_8004196C(r, p + 0x38 / 4, p[0x34 / 4], 8, 0);
        if (IsWindowFrameFit_800429A8(r) == 1)
        {
            DrawMsgWindowText_8003580C(p, (int*)r);
            DrawMsgWindowBackground_80035898(p, (int)r, 2);
            DrawMsgWindowBorder_800358CC(p, (int)r, 0);
        }
        InterpolateWindowRect_8004196C(r, p + 0x40 / 4, p[0x34 / 4], 8, 0);
        DrawMsgWindowBackground_80035898(p, (int)r, 2);
        DrawMsgWindowBorder_800358CC(p, (int)r, 0);
        break;
    }
    switch ((unsigned int)p[4])
    {
    case 0:
        break;
    case 1:
        p[0x48 / 4]++;
        if (p[0x48 / 4] >= 8)
        {
            p[0x48 / 4] = 8;
            p[4] = 2;
            p[2] = 3;
            p[9] = 1;
        }
        InterpolateWindowRect_8004196C(r, p + 0x4C / 4, p[0x48 / 4], 8, 5);
        if (IsWindowFrameFit_800429A8(r) == 1)
        {
            DrawMsgWindowChoices_800355EC(p, (int*)r);
            DrawMsgWindowBackground_80035898(p, (int)r, 2);
            DrawMsgWindowBorder_800358CC(p, (int)r, 0);
        }
        break;
    case 2:
        DrawMsgWindowChoices_800355EC(p, p + 0x4C / 4);
        DrawMsgWindowBackground_80035898(p, (int)(p + 0x4C / 4), 2);
        DrawMsgWindowBorder_800358CC(p, (int)(p + 0x4C / 4), 0);
        break;
    case 3:
        p[0x48 / 4]--;
        if (p[0x48 / 4] <= 0)
        {
            p[0x48 / 4] = 0;
            p[4] = 0;
            p[2] = 6;
        }
        InterpolateWindowRect_8004196C(r, p + 0x4C / 4, p[0x48 / 4], 8, 5);
        if (IsWindowFrameFit_800429A8(r) == 1)
        {
            DrawMsgWindowChoices_800355EC(p, (int*)r);
            DrawMsgWindowBackground_80035898(p, (int)r, 2);
            DrawMsgWindowBorder_800358CC(p, (int)r, 0);
        }
        break;
    }
}
#endif
INCLUDE_ASM(UpdateMsgWindowState_80034C18);

const int aMoney_80074850[3] = { 0x8F826C82, 0x85828E82, 0x9982 };
const int aEmptyCocoon_8007485C[2] = { 0x9A96F38B };
const int aTimesSign_80074864[2] = { 0x7782 };
// the jump table of UpdateItemMessageWindow_80035BD8 (asm; its targets are labels of the generated asm): delete it and
// its externs in msg_window.h when the function is C
void* const jpt_8007486C[6] = { jtgt_80035F2C, jtgt_80035F54, jtgt_80035F54, jtgt_80035F54, jtgt_80035F6C, jtgt_80035F40 };

extern int NthMaskedIndex_80034B88(int n, unsigned int mask);
// Matched
void HandleMsgWindowInput_800353A0(MsgWindow* win)
{
    switch (win->mode_8)
    {
    case 1:
    case 2:
        if (IsConfirmPressedP1_8003D380(0))
        {
            if (win->flags_4 & 0x800)
            {
                win->flags_4 = (win->flags_4 | 0x200) & ~0x800;
                win->res_18.advances_1E++;
            }
            if (win->field_2C == 1)
            {
                win->flags_4 = (win->flags_4 | 0x200) & ~0x800;
                win->res_18.advances_1E++;
            }
        }
        else if ((settingsFlags_8008B58C.word & 0xC00000) == 0xC00000 && win->voiced_2A4 == 1 &&
                 XaNoRequestPending_800435A4() == 1 && XaIsIdle_80043584() == 1)
        {
            if (win->flags_4 & 0x800)
            {
                win->flags_4 = (win->flags_4 | 0x20200) & ~0x800;
                win->res_18.advances_1E++;
            }
            if (win->field_2C == 1)
            {
                win->flags_4 = (win->flags_4 | 0x20200) & ~0x800;
                win->res_18.advances_1E++;
            }
        }
        break;
    case 4:
        if (IsConfirmPressedP1_8003D380(0))
        {
            win->flags_4 |= 0x200;
        }
        break;
    case 3:
        if (IsConfirmPressedP1_8003D380(0) && (win->flags_4 & 0x800))
        {
            win->flags_4 = (win->flags_4 | 0x200) & ~0x800;
            win->res_18.result_20 = 1;
            win->res_18.advances_1E++;
        }
        else if (win->cancelable_28 == 1 && IsCancelPressedP1_8003D41C(0) && (win->flags_4 & 0x800))
        {
            win->flags_4 |= 0x10000;
            win->res_18.sel_1A = NthMaskedIndex_80034B88(win->choice_B2 = win->choiceCount_B0 - 1, win->mask_14);
        }
        break;
    }
}
extern void AddDrawAreaPrim_8003326C(void* a, unsigned long* ot);
extern void AddClipDrawAreaPrim_80033308(unsigned long* ot);
extern void DrawColorText_8003EC2C(unsigned short* text, unsigned short* pos, int ot);
extern int MoveGridCursorP1_8003D630(short* m);
extern void DrawPulsingWindow_8002F6F8(void* a0, void* st, int a2);
// Matched
void DrawMsgWindowChoices_800355EC(MsgWindow* win, unsigned short* rect)
{
    RECT clip;
    union
    {
        unsigned short loc[2];
        int st[3];
        struct
        {
            int pad[2];
            int f0;
            short m[4];
        } menu;
    } u;
    RECT cursorRect;
    int sel;
    clip.x = rect[0] + 6;
    clip.y = rect[1] + 4;
    clip.w = rect[2] - 6;
    clip.h = rect[3] - 7;
    if (clip.h > 0 && clip.w > 0)
    {
        int i = 0;
        unsigned short x = win->x_4C + 8;
        unsigned short y = win->y_4E + 4;
        unsigned short** line = win->lines_1B4;
        while (*line)
        {
            if (win->mask_14 & (1 << i))
            {
                u.loc[1] = y;
                y += 12;
                u.loc[0] = x;
                AddClipDrawAreaPrim_80033308(&pOT_8008D454[win->ot_54]);
                DrawColorText_8003EC2C(*line, u.loc, win->ot_54);
                AddDrawAreaPrim_8003326C(&clip, &pOT_8008D454[win->ot_54]);
            }
            line++;
            i++;
        }
    }
    if (win->mode_8 == 3)
    {
        u.menu.f0 = 0;
        u.menu.m[0] = 0;
        u.menu.m[2] = 1;
        u.menu.m[3] = win->choiceCount_B0;
        u.menu.m[1] = win->choice_B2;
        MoveGridCursorP1_8003D630((short*)&u.menu.f0);
        if (win->choice_B2 != u.menu.m[1])
        {
            PlaySfx_80031494(0x7F);
        }
        win->choice_B2 = u.menu.m[1];
    }
    sel = win->choice_B2;
    u.st[0] = (int)&win->pulse_6C;
    u.st[1] = 1;
    u.st[2] = 1;
    cursorRect.x = win->x_4C + 4;
    cursorRect.y = win->y_4E + sel * 12 + 3;
    cursorRect.w = rect[2] - 8;
    cursorRect.h = 13;
    DrawPulsingWindow_8002F6F8(&cursorRect, u.st, 0);
    win->res_18.sel_1A = NthMaskedIndex_80034B88(win->choice_B2, win->mask_14);
}
extern int UpdateTextWindow_8003DB74(MsgTextClip* p, int a);
// Matched
int DrawMsgWindowText_8003580C(MsgWindow* win, unsigned short* rect)
{
    win->clip_1B8.x = rect[0] + 6;
    win->clip_1B8.y = rect[1] + 4;
    win->clip_1B8.w = rect[2] - 6;
    win->clip_1B8.h = rect[3] - 7;
    if ((short)win->clip_1B8.h > 0 && (short)win->clip_1B8.w > 0)
    {
        return UpdateTextWindow_8003DB74(&win->clip_1B8, ((win->flags_4 >> 18) ^ 1) & 1);
    }
    return 1;
}
// Matched
void DrawMsgWindowBackground_80035898(MsgWindow* win, int rect, int ot)
{
    if (!(win->flags_4 & 0x40000))
    {
        DrawWindowBackground_800429F8(rect, 2);
    }
}
// Matched
void DrawMsgWindowBorder_800358CC(MsgWindow* win, int rect, int ot)
{
    if (!(win->flags_4 & 0x40000))
    {
        DrawWindowBorder_80042B38(rect, 2);
    }
}
// Matched
void DrawMsgWindowPortrait_80035900(MsgWindow* win)
{
    if (!(win->flags_4 & 0x40000) && win->portraitKind_84 == 1)
    {
        if (win->portraitFlip_68)
        {
            win->prim_88.x1 = win->x_64;
            win->prim_88.y0 = win->y_66;
            win->prim_88.x0 = win->x_64 + 0x3F;
            win->prim_88.y1 = win->y_66;
            win->prim_88.x3 = win->x_64;
            win->prim_88.y2 = win->y_66 + 0x3F;
            win->prim_88.x2 = win->x_64 + 0x3F;
            win->prim_88.y3 = win->y_66 + 0x3F;
        }
        else
        {
            setXY4(&win->prim_88, win->x_64, win->y_66, win->x_64 + 0x3F, win->y_66, win->x_64, win->y_66 + 0x3F, win->x_64 + 0x3F, win->y_66 + 0x3F);
        }
        AddPrimCopy_80040298(pOT_8008D454 + 1, &win->prim_88, 10);
    }
}
extern void DrawText_8003E91C(int mode, void* str, void* pos, int z);

// Matched
void DrawMsgWindowTitle_800359F8(MsgWindow* win)
{
    short pos[2];
    short rect[4];
    if (!(win->flags_4 & 0x40000))
    {
        if (win->title_74 != 0)
        {
            pos[0] = win->titleX_6E + 7;
            pos[1] = win->titleY_70 + 4;
            DrawText_8003E91C(2, win->title_74, pos, 0);
            rect[0] = win->titleX_6E;
            rect[1] = win->titleY_70;
            rect[2] = MeasureTextWidth_8003E4C8((int)win->title_74) + 0x11;
            rect[3] = 0x12;
            DrawMsgWindowBackground_80035898(win, (int)rect, 2);
            DrawMsgWindowBorder_800358CC(win, (int)rect, 0);
        }
    }
}
extern EventNode* messageWindowTask_8008D640;
extern void PlayMusic_800300E0(int a, int b);
extern void UpdateItemMessageWindow_80035BD8(EventEntry* e, void* buf);
// Matched
EventEntry* OpenItemMessageWindow_80035AC8(int* init)
{
    EventEntry* entry = AllocEventEntry_80043AF8(messageWindowTask_8008D640);
    MsgWindow* win;
    if (entry)
    {
        win = entry->buffer;
        win->self_0 = (int)entry;
        win->flags_4 = 0;
        win->mask_14 = 0;
        win->res_18.count_18 = 0;
        win->res_18.sel_1A = 0;
        win->res_18.pageCount_1C = 0;
        win->res_18.advances_1E = 0;
        win->res_18.result_20 = 0;
        win->res_18.field_24 = 0;
        win->field_34 = 0;
        win->x_38 = 0;
        win->y_3A = 0;
        win->w_3C = 0;
        win->h_3E = 0;
        win->field_48 = 0;
        win->x_4C = 0;
        win->y_4E = 0;
        win->w_50 = 0;
        win->h_52 = 0;
        win->ot_54 = 0;
        win->page_78 = 0;
        win->count_7C = 0;
        win->choiceCount_B0 = 0;
        win->choice_B2 = 0;
        win->lines_1B4 = 0;
        MemCopy_800403E8(&win->item_214, init, 0x50);
        win->res_18.result_20 = 0;
        win->res_18.field_24 = 1;
        if ((unsigned int)win->item_214.mode_48 < 4)
        {
            PlayMusic_800300E0(1, 1);
        }
        entry->cb_8 = UpdateItemMessageWindow_80035BD8;
        entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
        return entry;
    }
    return 0;
}
typedef struct
{
    int field_0;
    unsigned int flags_4;
    int pad_8;
    int field_C;
    char pad_10[0x20C];
    int field_21C;
    ItemMsgEntry entries[3];
    int mode;
    int* text;
} ItemMsgWindow;
typedef struct
{
    short x;
    short y;
} ShortPos;
typedef struct
{
    int a;
    int b;
} TPageWords;
extern const int aMoney_80074850[];
extern const int aEmptyCocoon_8007485C[];
extern const int aTimesSign_80074864[];
extern void DrawNumberRightAlignedFont1_8003F264(void* pos, int val, int ot);
extern void DrawNumber_8003EF74(void* pos, int val, int ot);
extern void GetPublicTiySprt_80032470(int idx, SPRT* spr, TPageWords* tp);
extern void RemoveInventory_800AD1E0(int a, int b, int c);
extern void AddMoney_800AD058(int a);
extern void AddEmptyCocoons_800AD8F4(int a);
extern void SetValuableFlag_800AD68C(int a);
extern void AddInventory_800AD184(int a, int b, int c);
#if 0
// Not matched: only the loop strength-reduction registers for o->entries[i] and the row y (line * 16 + y) are swapped ($s1/$s2).
// Needs the C table jpt_8007486C removed (tu_800353A0 is merged into this TU for it: the jump table sits at
// 0x8007486C, which is 8-aligned only relative to this TU's .rdata start 0x8007474C; psylink packs objects on 4 bytes).
void UpdateItemMessageWindow_80035BD8(EventEntry* e, void* buf)
{
    ItemMsgWindow* o;
    SPRT spr[3];
    TPageWords tp[3];
    RECT r;
    TextSize p70;
    ShortPos p78;
    ShortPos p80;
    ShortPos p88;
    ShortPos p90;
    ShortPos p98;
    ShortPos pA0;
    int flag;
    int n;
    int i;
    int line;
    int y;
    int* text;
    int sfx;

    flag = 0;
    n = 0;
    o = buf;
    for (i = 0; i < 3; i++)
    {
        if (o->entries[i].type != -1)
        {
            n++;
        }
    }
    if (n >= 2 || (o->mode < 0 && n != 0))
    {
        flag = 1;
    }
    if (o->text)
    {
        int* q = o->text;
        while (*q++)
        {
            n++;
        }
        EncodeText_8003F684(2, (unsigned short*)o->text[0]);
        if (*(short*)o->text[0] == 0x91)
        {
            n--;
            o->text++;
        }
    }
    r.h = n * 16 | 8;
    r.w = 0xE3;
    r.x = 0x2F;
    r.y = (3 - n) * 9 + 0x5A;
    if (o->text)
    {
        p70 = MeasureTextLines_8003E3B4(o->text);
        p70.w += 8;
        if (r.w < p70.w)
        {
            r.w = p70.w;
        }
    }
    line = 0;
    y = 7;
    for (i = 0; i < 3; i++)
    {
        if (o->entries[i].type == 7)
        {
            p70.w = r.x + 6;
            p70.h = r.y + (line * 16 + y) + 2;
            AddClipDrawAreaPrim_80033308(pOT_8008D454);
            DrawText_8003E91C(2, aMoney_80074850, &p70, 0);
            AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
            p78.x = r.x + r.w - 4;
            p78.y = r.y + (line * 16 + y) + 2;
            AddClipDrawAreaPrim_80033308(pOT_8008D454);
            DrawNumberRightAlignedFont1_8003F264(&p78, o->entries[i].count, 0);
            AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
            line++;
            continue;
        }
        else if (o->entries[i].type == 6)
        {
            p80.x = r.x + 6;
            p80.y = r.y + (line * 16 + y) + 2;
            AddClipDrawAreaPrim_80033308(pOT_8008D454);
            DrawText_8003E91C(2, aEmptyCocoon_8007485C, &p80, 0);
            AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
            if (flag)
            {
                p88.x = r.x + 0x84;
                p88.y = r.y + (line * 16 + y) + 2;
                AddClipDrawAreaPrim_80033308(pOT_8008D454);
                DrawText_8003E91C(1, aTimesSign_80074864, &p88, 0);
                AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
                p90.x = r.x + 0x8D;
                p90.y = r.y + (line * 16 + y) + 2;
                AddClipDrawAreaPrim_80033308(pOT_8008D454);
                DrawNumber_8003EF74(&p90, o->entries[i].count, 0);
                AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
            }
        }
        else if ((unsigned int)o->entries[i].type < 6)
        {
            spr[i].x0 = 0;
            spr[i].y0 = 0;
            spr[i].w = 0;
            spr[i].h = 0;
            if (o->entries[i].type != -1)
            {
                switch (o->entries[i].type)
                {
                case 0:
                    GetPublicTiySprt_80032470(GetItemIcon_8001D2AC(o->entries[i].id), &spr[i], &tp[i]);
                    break;
                case 5:
                    GetPublicTiySprt_80032470(GetKeyItemIcon_8001D344(o->entries[i].id), &spr[i], &tp[i]);
                    break;
                case 1:
                case 2:
                case 3:
                    GetPublicTiySprt_80032470(GetEquipmentIcon_8001D2D4(o->entries[i].id, o->entries[i].type - 1), &spr[i], &tp[i]);
                    break;
                case 4:
                    GetPublicTiySprt_80032470(GetPersonIcon_8001CD6C(o->entries[i].id), &spr[i], &tp[i]);
                    break;
                }
                spr[i].r0 = 0x80;
                spr[i].g0 = 0x80;
                spr[i].b0 = 0x80;
                spr[i].x0 = r.x + 6;
                spr[i].y0 = r.y + (line * 16 + y) - 2;
                AddPrimCopy_80040298(pOT_8008D454, &spr[i], 5);
                AddPrimCopy_80040298(pOT_8008D454, &tp[i], 2);
            }
            p88.x = spr[i].w + r.x + 9;
            p88.y = r.y + (line * 16 + y) + 2;
            AddClipDrawAreaPrim_80033308(pOT_8008D454);
            DrawText_8003E91C(2, nameGetters_8007CB08[o->entries[i].type](o->entries[i].id), &p88, 0);
            AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
            if (flag)
            {
                p98.x = r.x + 0x84;
                p98.y = r.y + (line * 16 + y) + 2;
                AddClipDrawAreaPrim_80033308(pOT_8008D454);
                DrawText_8003E91C(1, aTimesSign_80074864, &p98, 0);
                AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
                pA0.x = r.x + 0x8D;
                pA0.y = r.y + (line * 16 + y) + 2;
                AddClipDrawAreaPrim_80033308(pOT_8008D454);
                DrawNumber_8003EF74(&pA0, o->entries[i].count, 0);
                AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
            }
        }
        else
        {
            continue;
        }
        line++;
    }
    if ((unsigned int)o->mode < 11 && !flag)
    {
        int w = MeasureTextWidth_8003E4C8(nameGetters_8007CB08[o->entries[0].type](o->entries[0].id)) + 0x19;
        int h = r.y + 9;
        p70.w = r.x + w;
        p70.h = h;
        AddClipDrawAreaPrim_80033308(pOT_8008D454);
        DrawText_8003E91C(2, itemMessageSuffixes_80083818[o->mode], &p70, 0);
        AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
    }
    if (o->entries[0].type != -1 && line == 1 && o->mode < 0 && !flag)
    {
        int w = MeasureTextWidth_8003E4C8(nameGetters_8007CB08[o->entries[0].type](o->entries[0].id)) + 0x19;
        int h = r.y + 9;
        p70.w = r.x + w;
        p70.h = h;
        AddClipDrawAreaPrim_80033308(pOT_8008D454);
        DrawText_8003E91C(2, itemMessageDefaultSuffix_80083820, &p70, 0);
        AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
    }
    if (o->text)
    {
        text = o->text;
        while (*text)
        {
            p70.w = r.x + 6;
            p70.h = r.y + (line * 16 + y) + 2;
            AddClipDrawAreaPrim_80033308(pOT_8008D454);
            DrawText_8003E91C(2, (void*)*text, &p70, 0);
            text++;
            AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
            line++;
        }
    }
    DrawWindowBackground_800429F8((int)&r, 0);
    DrawWindowBorder_80042B38((int)&r, 0);
    o->field_C = 3;
    if (IsConfirmPressedP1_8003D380(0))
    {
        if ((o->flags_4 & 0x800) || o->field_21C == 1)
        {
            o->flags_4 = (o->flags_4 | 0x200) & ~0x800;
        }
    }
    if (o->flags_4 & 0x4000)
    {
        if (o->mode >= 4 && o->mode < 8)
        {
            for (i = 0; i < 3; i++)
            {
                if (o->entries[i].type == 0)
                {
                    sfx = 0x1E;
                    if (o->entries[i].id == 0x28)
                    {
                        sfx = 0x33;
                    }
                }
                else if (o->entries[i].type == 5)
                {
                    if (o->entries[i].id == 2 || o->entries[i].id == 9 || o->entries[i].id == 0x18 || o->entries[i].id == 0x11 || o->entries[i].id == 0x10 || o->entries[i].id == 0x12)
                    {
                        sfx = 0x1E;
                    }
                    else
                    {
                        sfx = 0x33;
                    }
                }
                else
                {
                    continue;
                }
                PlaySfx_80031494(sfx);
                RemoveInventory_800AD1E0(o->entries[i].id, 1, o->entries[i].type);
            }
        }
        if (o->mode >= -1 && o->mode < 4)
        {
            for (i = 0; i < 3; i++)
            {
                if (o->entries[i].type == 7)
                {
                    AddMoney_800AD058(o->entries[i].count);
                }
                else if (o->entries[i].type == 6)
                {
                    AddEmptyCocoons_800AD8F4(o->entries[i].count);
                }
                else if ((unsigned int)o->entries[i].type < 6)
                {
                    if (o->entries[i].type == 5)
                    {
                        SetValuableFlag_800AD68C(o->entries[i].id);
                    }
                    else
                    {
                        AddInventory_800AD184(o->entries[i].id, o->entries[i].count, o->entries[i].type);
                    }
                }
            }
        }
        o->flags_4 &= ~0x4000;
        e->flags = (e->flags & ~1) | 0x8000;
    }
}
#endif
INCLUDE_ASM(UpdateItemMessageWindow_80035BD8);
// Matched
void InitPadVibration_800364E4(int* entry)
{
    padVibration_80095460[entry[1]].flags_0 = 0;
    padVibration_80095460[entry[1]].motor_2[0] = 0;
    padVibration_80095460[entry[1]].motor_2[1] = 0;
}
