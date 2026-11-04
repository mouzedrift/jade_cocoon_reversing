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
// Matched
EventEntry* OpenMessageWindow_8003422C(MsgWindowCfg* cfg)
{
    EventEntry* e;
    MsgWindow* w;
    int** list;
    int* p;
    int n;
    int i;
    TextSize sz;
    int c;

    e = AllocEventEntry_80043AF8(messageWindowTask_8008D640);
    if (!e)
    {
        return 0;
    }
    w = (MsgWindow*)e->buffer;
    w->self_0 = (int)e;
    w->flags_4 = 0;
    w->mask_14 = 0;
    w->res_18.count_18 = 0;
    w->res_18.sel_1A = 0;
    w->res_18.pageCount_1C = 0;
    w->res_18.advances_1E = 0;
    w->res_18.result_20 = 0;
    w->res_18.field_24 = 0;
    w->field_34 = 0;
    w->x_38 = 0;
    w->y_3A = 0;
    w->w_3C = 0;
    w->h_3E = 0;
    w->field_48 = 0;
    w->x_4C = 0;
    w->y_4E = 0;
    w->w_50 = 0;
    w->h_52 = 0;
    w->ot_54 = 0;
    w->page_78 = 0;
    w->count_7C = 0;
    w->choiceCount_B0 = 0;
    w->choice_B2 = 0;
    w->lines_1B4 = 0;
    if (cfg->style_28 == 0 && cfg->field_2C != 0)
    {
        w->portraitFlip_68 = 1;
    }
    else
    {
        w->portraitFlip_68 = 0;
    }
    w->pulse_6C = 0;
    w->field_2C = cfg->field_3C;
    w->field_30 = cfg->field_38;
    n = cfg->voiced_44;
    w->voiced_2A4 = n;
    if (!(saveData_8008B570.settings_1C.bytes[3] & 1) && n == 1)
    {
        w->flags_4 |= 0x40000;
    }
    w->mask_14 = cfg->mask_18;
    w->cancelable_28 = cfg->cancelable_14;
    w->mode_8 = 0;
    w->field_C = 1;
    w->field_10 = 0;
    w->title_74 = cfg->title_C;
    w->portraitKind_84 = cfg->portraitKind_20;
    if (cfg->portraitKind_20 == 1)
    {
        GetPortraitPoly_800A6308(cfg->portraitId_24, &w->prim_88);
    }
    else if (cfg->portraitKind_20 == 7)
    {
        GetCombatPortraitPoly_800A1B2C(cfg->portraitId_24, &w->prim_88);
        w->portraitKind_84 = 1;
    }
    list = (int**)cfg->text_8;
    if (list)
    {
        list = (int**)FindTextResumePage_80034900((short**)list);
        while (*list)
        {
            w->res_18.pageCount_1C++;
            w->list_B4[w->count_7C++] = (int*)list;
            sz = MeasureTextLines_8003E3B4((int*)list);
            if (w->w_3C < sz.w)
            {
                w->w_3C = sz.w;
            }
            if (w->h_3E < sz.h)
            {
                w->h_3E = sz.h;
            }
            while (*list++)
            {
            }
        }
        w->list_B4[w->count_7C] = 0;
    }
    p = cfg->lines_1C;
    if (p)
    {
        if (IsTextMarkerLine_8003E484(*p) == 1)
        {
            w->lines_1B4 = (unsigned short**)(p + 1);
        }
        else
        {
            w->lines_1B4 = (unsigned short**)p;
        }
        sz = MeasureTextLinesMasked_8003E2A8((int*)w->lines_1B4, w->mask_14);
        w->res_18.count_18 = CountUntilZero_80034B14((int*)w->lines_1B4);
        w->w_50 = sz.w;
        w->h_52 = sz.h;
        w->choiceCount_B0 = CountMaskedUntilZero_80034B40((int*)w->lines_1B4, w->mask_14);
    }
    c = -1;
    w->clip_1B8.x = 0;
    w->clip_1B8.y = 0;
    w->clip_1B8.w = 0;
    w->clip_1B8.h = 0;
    w->field_1C8 = 0;
    w->field_1D4 = 0;
    w->field_1D8 = 0;
    w->field_1DC = 0;
    w->field_1E0 = 1;
    for (i = 0; i < 0x30; i++)
    {
        w->marks_1E4[i] = c;
    }
    w->field_1CC = cfg->field_10;
    w->field_1C4 = (int)w->list_B4[w->page_78];
    w->field_1D0 = cfg->field_38;
    w->h_3E = 0x38;
    w->w_3C = 0xDB;
    w->field_46 = 0x43;
    w->field_44 = 0x46;
    w->w_50 += 0x11;
    w->h_52 += 7;
    if (cfg->style_28 == 1)
    {
        if (cfg->pos_4)
        {
            w->field_40 = cfg->pos_4[0];
            w->field_42 = cfg->pos_4[0] + cfg->pos_4[1];
            w->x_38 = w->field_40 + 0x45;
            w->y_3A = w->field_42 + 0xE;
            w->titleX_6E = w->x_38 + w->w_3C - MeasureTextWidth_8003E4C8((int)w->title_74) - 0x10;
            w->titleY_70 = w->y_3A - 0xC;
        }
        else
        {
            switch ((unsigned int)cfg->posMode_0)
            {
            case 0:
                w->field_42 = w->field_40 = 0x10;
                w->x_38 = w->field_40 + 0x44;
                w->y_3A = w->field_42 + 0xD;
                w->titleX_6E = w->x_38 + w->w_3C - MeasureTextWidth_8003E4C8((int)w->title_74) - 0x10;
                w->titleY_70 = w->y_3A + w->h_3E - 2;
                break;
            case 1:
                w->field_40 = 0x10;
                w->field_42 = 0x74;
                w->x_38 = w->field_40 + 0x44;
                w->y_3A = w->field_42 + 0xD;
                w->titleX_6E = w->x_38 + w->w_3C - MeasureTextWidth_8003E4C8((int)w->title_74) - 0x10;
                w->titleY_70 = w->y_3A - 0x10;
                break;
            case 2:
                w->field_40 = 0x10;
                w->field_42 = 0xA1;
                w->x_38 = w->field_40 + 0x44;
                w->y_3A = w->field_42 + 0xD;
                w->titleX_6E = w->x_38 + w->w_3C - MeasureTextWidth_8003E4C8((int)w->title_74) - 0x10;
                w->titleY_70 = w->y_3A - 0x10;
                break;
            }
        }
        w->x_4C = w->field_40 + 0xA;
        w->y_4E = w->y_3A + w->h_3E + 3;
    }
    else
    {
        if (cfg->pos_4)
        {
            w->field_40 = cfg->pos_4[0];
            w->field_42 = cfg->pos_4[0] + cfg->pos_4[1];
            w->x_38 = w->field_40 + 0x45;
            w->y_3A = w->field_42 + 0xD;
            w->titleX_6E = w->x_38 + w->w_3C - MeasureTextWidth_8003E4C8((int)w->title_74) - 0x10;
            w->titleY_70 = w->y_3A - 0xC;
        }
        else
        {
            switch ((unsigned int)cfg->posMode_0)
            {
            case 0:
                w->field_42 = w->x_38 = 0x10;
                w->field_40 = w->x_38 + 0xDA;
                w->y_3A = w->field_42 + 0xD;
                w->titleX_6E = w->field_40 + w->field_44 - MeasureTextWidth_8003E4C8((int)w->title_74) - 0x10;
                w->titleY_70 = w->field_42 + w->field_46 - 2;
                break;
            case 1:
                w->field_42 = 0x60;
                w->x_38 = 0x10;
                w->y_3A = w->field_42 + 0xD;
                w->field_40 = w->x_38 + 0xDA;
                w->titleX_6E = w->x_38;
                w->titleY_70 = w->y_3A - 0x10;
                break;
            case 2:
                w->field_42 = 0xA1;
                w->x_38 = 0x10;
                w->y_3A = w->field_42 + 0xD;
                w->field_40 = w->x_38 + 0xDA;
                w->titleX_6E = w->x_38;
                w->titleY_70 = w->y_3A - 0x10;
                break;
            }
        }
        w->x_4C = w->x_38 + 0xA;
        w->y_4E = w->y_3A + w->h_3E + 3;
    }
    w->titleY_70 -= 2;
    w->y_3A -= 2;
    w->x_64 = w->field_40 + 3;
    w->y_66 = w->field_42 + 2;
    w->clip_1B8.promptX_0 = w->x_38 + 7;
    w->clip_1B8.promptY_2 = w->y_3A + 4;
    e->cb_8 = (EventEntryFn)UpdateMessageWindow_80034BB8;
    e->flags = (e->flags | 1) & ~0x8000;
    return e;
}
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
// Matched
void UpdateMsgWindowState_80034C18(MsgWindow* w)
{
    short r[4];
    int i;
    int j;
    int c;
    int v;

    if (w->flags_4 & 0x80000)
    {
        w->flags_4 &= ~0x40000;
        w->flags_4 &= ~0x80000;
    }
    switch (w->mode_8)
    {
    case 0:
        break;
    case 1:
        if (w->field_2C == 1 || (w->flags_4 & 0x800))
        {
            if (!(w->flags_4 & 0x8000))
            {
                w->flags_4 |= 0x8000;
            }
            if (!(w->flags_4 & 0x40000))
            {
                DrawMsgWindowNextPrompt_8003E268((unsigned short*)&w->clip_1B8);
            }
        }
        if (w->flags_4 & 0x200)
        {
            if (!(w->flags_4 & 0x20000))
            {
                PlaySfx_80031494(0x7F);
            }
            w->flags_4 &= ~0x20000;
            w->flags_4 &= ~0x8000;
            w->flags_4 &= ~0x200;
            c = -1;
            w->field_1C4 = (int)w->list_B4[w->page_78];
            w->field_1C8 = 0;
            w->field_1D4 = 0;
            w->field_1D8 = 0;
            w->field_1DC = 0;
            w->field_1E0 = 1;
            for (i = 0; i < 0x30; i++)
            {
                w->marks_1E4[i] = c;
            }
            w->mode_8 = 0;
            w->field_C = 2;
        }
        break;
    case 2:
        if (w->field_2C == 1 || (w->flags_4 & 0x800))
        {
            if (!(w->flags_4 & 0x8000))
            {
                w->flags_4 |= 0x8000;
            }
            if (!(w->flags_4 & 0x40000))
            {
                DrawMsgWindowNextPrompt_8003E268((unsigned short*)&w->clip_1B8);
            }
        }
        if (w->flags_4 & 0x200)
        {
            if (!(w->flags_4 & 0x20000))
            {
                PlaySfx_80031494(0x7F);
            }
            w->flags_4 &= ~0x20000;
            w->flags_4 &= ~0x8000;
            w->flags_4 &= ~0x200;
        }
        if (w->flags_4 & 0x4000)
        {
            w->flags_4 &= ~0x8000;
            w->flags_4 &= ~0x4000;
            w->mode_8 = 6;
        }
        break;
    case 3:
        if (w->flags_4 & 0x200)
        {
            if (!(w->flags_4 & 0x20000))
            {
                PlaySfx_80031494(0x7F);
            }
            w->mode_8 = 5;
            w->flags_4 &= ~0x20000;
            w->flags_4 &= ~0x200;
        }
        else if (w->flags_4 & 0x10000)
        {
            if (!(w->flags_4 & 0x20000))
            {
                PlaySfx_80031494(0x7D);
            }
            w->flags_4 &= ~0x20000;
            w->flags_4 &= ~0x10000;
        }
        if (w->flags_4 & 0x4000)
        {
            w->flags_4 &= ~0x4000;
            w->mode_8 = 6;
        }
        break;
    case 4:
        if (w->flags_4 & 0x200)
        {
            if (!(w->flags_4 & 0x20000))
            {
                PlaySfx_80031494(0x7F);
            }
            w->mode_8 = 0;
            w->field_10 = 1;
            w->flags_4 &= ~0x20000;
            w->flags_4 &= ~0x200;
        }
        if (!(w->flags_4 & 0x40000))
        {
            DrawMsgWindowNextPrompt_8003E268((unsigned short*)&w->clip_1B8);
        }
        break;
    case 5:
        w->field_10 = 3;
        break;
    case 6:
        w->field_C = 4;
        break;
    case 7:
        break;
    }
    switch (w->field_C)
    {
    case 0:
        break;
    case 1:
        w->field_34++;
        if (w->field_34 >= 8)
        {
            w->field_34 = 8;
            w->field_C = 2;
        }
        InterpolateWindowRect_8004196C(r, &w->x_38, w->field_34, 8, 0);
        DrawMsgWindowBackground_80035898(w, (int)r, 2);
        DrawMsgWindowBorder_800358CC(w, (int)r, 0);
        InterpolateWindowRect_8004196C(r, &w->field_40, w->field_34, 8, 0);
        DrawMsgWindowBackground_80035898(w, (int)r, 2);
        DrawMsgWindowBorder_800358CC(w, (int)r, 0);
        break;
    case 2:
        DrawMsgWindowTitle_800359F8(w);
        DrawMsgWindowPortrait_80035900(w);
        v = DrawMsgWindowText_8003580C(w, &w->x_38);
        if (v == 1)
        {
            w->field_C = 3;
            w->page_78++;
            if (w->list_B4[w->page_78])
            {
                w->mode_8 = v;
                if (w->flags_4 & 0x40000)
                {
                    if (w->list_B4[w->page_78 + 1] == 0 && w->lines_1B4)
                    {
                        c = -1;
                        w->field_1C4 = (int)w->list_B4[w->page_78];
                        w->field_1C8 = 0;
                        w->field_1D4 = 0;
                        w->field_1D8 = 0;
                        w->field_1DC = 0;
                        w->field_1E0 = v;
                        for (j = 0; j < 0x30; j++)
                        {
                            w->marks_1E4[j] = c;
                        }
                        w->field_C = 1;
                        w->field_34 = 0;
                        w->mode_8 = 0;
                        w->field_10 = 0;
                        w->flags_4 |= 0x80000;
                    }
                }
            }
            else if (w->lines_1B4)
            {
                w->mode_8 = 4;
            }
            else
            {
                w->mode_8 = 2;
                w->res_18.field_24 = v;
            }
        }
        DrawMsgWindowBackground_80035898(w, (int)&w->x_38, 2);
        DrawMsgWindowBorder_800358CC(w, (int)&w->x_38, 0);
        DrawMsgWindowBackground_80035898(w, (int)&w->field_40, 2);
        DrawMsgWindowBorder_800358CC(w, (int)&w->field_40, 0);
        break;
    case 3:
        DrawMsgWindowTitle_800359F8(w);
        DrawMsgWindowPortrait_80035900(w);
        DrawMsgWindowText_8003580C(w, &w->x_38);
        DrawMsgWindowBackground_80035898(w, (int)&w->x_38, 2);
        DrawMsgWindowBorder_800358CC(w, (int)&w->x_38, 0);
        DrawMsgWindowBackground_80035898(w, (int)&w->field_40, 2);
        DrawMsgWindowBorder_800358CC(w, (int)&w->field_40, 0);
        break;
    case 4:
        w->field_34--;
        if (w->field_34 <= 0)
        {
            w->field_34 = 0;
            w->field_C = 0;
            w->mode_8 = 7;
        }
        InterpolateWindowRect_8004196C(r, &w->x_38, w->field_34, 8, 0);
        if (IsWindowFrameFit_800429A8(r) == 1)
        {
            DrawMsgWindowText_8003580C(w, r);
            DrawMsgWindowBackground_80035898(w, (int)r, 2);
            DrawMsgWindowBorder_800358CC(w, (int)r, 0);
        }
        InterpolateWindowRect_8004196C(r, &w->field_40, w->field_34, 8, 0);
        DrawMsgWindowBackground_80035898(w, (int)r, 2);
        DrawMsgWindowBorder_800358CC(w, (int)r, 0);
        break;
    }
    switch ((unsigned int)w->field_10)
    {
    case 0:
        break;
    case 1:
        w->field_48++;
        if (w->field_48 >= 8)
        {
            w->field_48 = 8;
            w->field_10 = 2;
            w->mode_8 = 3;
            w->res_18.field_24 = 1;
        }
        InterpolateWindowRect_8004196C(r, &w->x_4C, w->field_48, 8, 5);
        if (IsWindowFrameFit_800429A8(r) == 1)
        {
            DrawMsgWindowChoices_800355EC(w, r);
            DrawMsgWindowBackground_80035898(w, (int)r, 2);
            DrawMsgWindowBorder_800358CC(w, (int)r, 0);
        }
        break;
    case 2:
        DrawMsgWindowChoices_800355EC(w, &w->x_4C);
        DrawMsgWindowBackground_80035898(w, (int)&w->x_4C, 2);
        DrawMsgWindowBorder_800358CC(w, (int)&w->x_4C, 0);
        break;
    case 3:
        w->field_48--;
        if (w->field_48 <= 0)
        {
            w->field_48 = 0;
            w->field_10 = 0;
            w->mode_8 = 6;
        }
        InterpolateWindowRect_8004196C(r, &w->x_4C, w->field_48, 8, 5);
        if (IsWindowFrameFit_800429A8(r) == 1)
        {
            DrawMsgWindowChoices_800355EC(w, r);
            DrawMsgWindowBackground_80035898(w, (int)r, 2);
            DrawMsgWindowBorder_800358CC(w, (int)r, 0);
        }
        break;
    }
}

const int aMoney_80074850[3] = { 0x8F826C82, 0x85828E82, 0x9982 };
const int aEmptyCocoon_8007485C[2] = { 0x9A96F38B };
const int aTimesSign_80074864[2] = { 0x7782 };

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
// Matched
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
            line++;
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
            line++;
        }
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
// Matched
void InitPadVibration_800364E4(int* entry)
{
    padVibration_80095460[entry[1]].flags_0 = 0;
    padVibration_80095460[entry[1]].motor_2[0] = 0;
    padVibration_80095460[entry[1]].motor_2[1] = 0;
}
