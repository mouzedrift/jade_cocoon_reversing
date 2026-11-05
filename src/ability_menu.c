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
#include "minion_menu.h"
#include "effect_data.h"
#include "skills.h"
#include "msg_window.h"
#include "util.h"
#include "unit_query.h"
#include "ui_sprites.h"
#include "party.h"
#include "ability_menu.h"
#include "family_tree.h"

// Matched
void DrawAbilityList_8002CE28(ListMenuState* menu, unsigned short* origin)
{
    MenuWindowList args;
    unsigned short pos[2];
    short cursor;
    short openStep;
    short i;
    int name;
    int bonusName;
    MenuWindowItem** row;
    MenuWindowItem** row2;
    int y;
    cursor = menu->cursor_0;
    openStep = 8;
    if (origin)
    {
        pos[0] = origin[0];
        pos[1] = origin[1];
    }
    else
    {
        pos[0] = 0x38;
        pos[1] = 0x2C;
    }
    for (i = 0; i < 5; i++)
    {
        name = abilityNames_800834E4[0];
        bonusName = abilityBonusNames_80083580[0];
        if (menu->minion_C->skills_DE.slot[i].flags_0 & 1)
        {
            if (menu->minion_C->skills_DE.slot[i].id_1)
            {
                name = abilityNames_800834E4[menu->minion_C->skills_DE.slot[i].id_1];
            }
            if (menu->minion_C->skills_DE.slot[i].bonus_2)
            {
                bonusName = abilityBonusNames_80083580[menu->minion_C->skills_DE.slot[i].bonus_2];
            }

            row = &abilityListRows_80082D98[i];
            (*row)[0].flags_0 &= ~2;
            (*row)[1].flags_0 &= ~2;
            (*row)[2].flags_0 &= ~2;
            menu->cursor_0 = i;
            if ((short)CheckSkillUsable_80033C98(menu))
            {
                (*row)[0].flags_0 |= 2;
                (*row)[1].flags_0 |= 2;
                (*row)[2].flags_0 |= 2;
            }
            else
            {
                (*row)[0].flags_0 &= ~2;
                (*row)[1].flags_0 &= ~2;
                (*row)[2].flags_0 &= ~2;
            }
        }
        else
        {
            abilityListRows_80082D98[i][0].flags_0 |= 2;
            abilityListRows_80082D98[i][1].flags_0 |= 2;
            abilityListRows_80082D98[i][2].flags_0 |= 2;
        }
        y = GetAbilityIcon_8002D1A4(GetAbilityAction_800318C8(menu->minion_C->skills_DE.slot[i].id_1)->element_8, i);
        row2 = &abilityListRows_80082D98[i];
        (*row2)[0].text_4 = y;
        (*row2)[1].text_4 = name;
        (*row2)[2].text_4 = bonusName;
        (*row2)[0].sprts_8 = &uiTiySprts_8008D620;
        (*row2)[0].tpages_C = &uiTiyTPages_8008D3F4;
        (*row2)[0].x_10 = pos[0];
        y = i * 22;
        (*row2)[0].y_12 = pos[1] + y;
        (*row2)[1].x_10 = pos[0] + 0x26;
        (*row2)[1].y_12 = pos[1] + y;
        (*row2)[2].x_10 = pos[0] + 0x83;
        (*row2)[2].y_12 = pos[1] + y;
    }
    args.flags_0 = menu->windowFlags_4;
    args.time_4 = frameCount_8008D3FC;
    args.open_8 = openStep;
    args.cursor_C = cursor;
    args.items_10 = abilityListRows_80082D98;
    args.ot_14 = menu->ot_6;
    DrawMenuWindows_8002A5A4(&args);
    SetFontClutOffset_8003F900(2, 0);
}
// Matched
int GetAbilityIcon_8002D1A4(int type, short slot)
{
    int typeIdx = 0;
    switch ((short)type)
    {
    case 0:
        break;
    default:
        typeIdx = 4;
        break;
    case 3:
        typeIdx = 1;
        break;
    case 1:
        typeIdx = 2;
        break;
    case 2:
        typeIdx = 3;
        break;
    }
    type = typeIdx;
    if (type >= 4)
    {
        return abilityIconsNoType_800827F0[slot];
    }
    return abilityIconsByType_8008280C[slot][type];
}
// Matched
int DrawTargetSelectMenu_8002D250(TargetQuery* req, int mode, int cursor, int ot)
{
    MenuWindowItem list0[4] = {
        {8, 4, 0, 0, 0, 0x2E, 0x98, 0x3C, 0xC, 2, 2},
        {8, 0, 0, 0, 0, 0x26, 0x98, 6, 0xC, 2, 2},
        {8, 0, 0, 0, 0, 0x6C, 0x98, 6, 0xC, 2, 2},
        {1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1},
    };
    MenuWindowItem list1[2] = {
        {8, 4, 0, 0, 0, 0x2E, 0xA6, 0x3C, 0xC, 2, 2},
        {1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1},
    };
    MenuWindowItem list2[2] = {
        {8, 4, 0, 0, 0, 0x2E, 0xB3, 0x3C, 0xC, 2, 2},
        {1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1},
    };
    MenuWindowItem list3[2] = {
        {8, 4, 0, 0, 0, 0x2E, 0xC0, 0x3C, 0xC, 2, 2},
        {1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1},
    };
    MenuWindowItem* lists[5] = {0};
    MenuWindowItem* subs[3] = {0};
    int k = 0;
    MenuWindowList args = {2, 0, 8, 0, 0, 0};
    int minionCount;
    int allMask;
    int i;
    int listed;
    int state;
    UnitStatus* status;
    int row;
    MenuWindowItem* item;
    minionCount = CountMinions_80010548(3);
    allMask = GetAllMinionsTargetMask_8002D780();
    args.time_4 = GetTime30Hz_8002C64C();
    args.cursor_C = cursor;
    args.items_10 = lists;
    args.ot_14 = ot;
    subs[0] = list1;
    subs[1] = list2;
    subs[2] = list3;
    if (mode == 0 || mode == 3)
    {
        status = GetUnitStatus_80014390(0);
        lists[k] = list0;
        lists[k][0].text_4 = (int)status->name_10;
        req->target_4 = 0;
        if (mode == 0)
        {
            state = CheckItemOnTarget_80033DF4(req);
        }
        else
        {
            state = 0;
        }
        if (state == 0 || state == 1)
        {
            lists[k][0].flags_0 &= ~2;
            lists[k][1].flags_0 &= ~2;
            lists[k][2].flags_0 &= ~2;
        }
        else
        {
            lists[k][0].flags_0 |= 2;
            lists[k][1].flags_0 |= 2;
            lists[k][2].flags_0 |= 2;
        }
        k++;
    }
    row = 0;
    for (i = 0; i < minionCount; i++)
    {
        listed = IsTargetListed_8002D738(i, req->actor_2, mode);
        if (listed == 1)
        {
            req->target_4 = i + 1;
            status = GetUnitStatus_80014390((unsigned char)req->target_4);
            state = 0;
            item = subs[i];
            lists[k] = item;
            item->text_4 = (int)status->name_10;

            lists[k]->y_12 = 0xA6 + row * 13;
            if (mode == 0)
            {
                state = CheckItemOnTarget_80033DF4(req);
            }
            else if (mode == 1)
            {
                state = CheckMagicUsable_80034068(req);
            }
            else if ((unsigned int)(mode - 2) < 2)
            {
                if (HasStatusFlag_80033548(status, 0x400))
                {
                    state = 4;
                }
            }
            if (state == 0 || state == 2)
            {
                lists[k]->flags_0 &= ~2;
            }
            else
            {
                lists[k]->flags_0 |= 2;
            }
            k++;
            row++;
        }
    }
    DrawMenuWindows_8002A5A4(&args);
    SetFontClutOffset_8003F900(1, 0);
    switch (mode)
    {
    case 0:
        if (cursor < 0)
        {
            return allMask | 1;
        }
        return cursor;
    case 1:
        return req->actor_2;
    case 2:
        return cursor + 1;
    case 3:
        if (cursor < 0)
        {
            return (allMask | 1) & ~(1 << req->actor_2);
        }
        if (cursor < req->actor_2)
        {
            return cursor;
        }
        return cursor + 1;
    }
    return 0;
}
