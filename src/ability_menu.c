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

typedef struct
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    MenuItem_1C** field_10;
    int field_14;
} struct_A5A4;
extern void DrawMenuWindows_8002A5A4(struct_A5A4* p);
extern int CheckSkillUsable_80033C98(struct_minion_ref* p);
int GetAbilityIcon_8002D1A4(int a, short b);
// Matched
void DrawAbilityList_8002CE28(struct_minion_ref* menu, unsigned short* origin)
{
    struct_A5A4 s;
    unsigned short pos[2];
    short cursor;
    short w;
    short i;
    int name;
    int bonusName;
    MenuItem_1C** row;
    MenuItem_1C** row2;
    int y;
    cursor = menu->cursor_0;
    w = 8;
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
            (*row)[0].flags &= ~2;
            (*row)[1].flags &= ~2;
            (*row)[2].flags &= ~2;
            menu->cursor_0 = i;
            if ((short)CheckSkillUsable_80033C98(menu))
            {
                (*row)[0].flags |= 2;
                (*row)[1].flags |= 2;
                (*row)[2].flags |= 2;
            }
            else
            {
                (*row)[0].flags &= ~2;
                (*row)[1].flags &= ~2;
                (*row)[2].flags &= ~2;
            }
        }
        else
        {
            abilityListRows_80082D98[i][0].flags |= 2;
            abilityListRows_80082D98[i][1].flags |= 2;
            abilityListRows_80082D98[i][2].flags |= 2;
        }
        y = GetAbilityIcon_8002D1A4(GetAbilityAction_800318C8(menu->minion_C->skills_DE.slot[i].id_1)->element_8, i);
        row2 = &abilityListRows_80082D98[i];
        (*row2)[0].f4 = y;
        (*row2)[1].f4 = name;
        (*row2)[2].f4 = bonusName;
        (*row2)[0].sprts_8 = &uiTiySprts_8008D620;
        (*row2)[0].tpages_C = &uiTiyTPages_8008D3F4;
        (*row2)[0].x = pos[0];
        y = i * 22;
        (*row2)[0].y = pos[1] + y;
        (*row2)[1].x = pos[0] + 0x26;
        (*row2)[1].y = pos[1] + y;
        (*row2)[2].x = pos[0] + 0x83;
        (*row2)[2].y = pos[1] + y;
    }
    s.field_0 = menu->field_4;
    s.field_4 = frameCount_8008D3FC;
    s.field_8 = w;
    s.field_C = cursor;
    s.field_10 = abilityListRows_80082D98;
    s.field_14 = menu->ot_6;
    DrawMenuWindows_8002A5A4(&s);
    SetFontClutOffset_8003F900(2, 0);
}
// Matched
int GetAbilityIcon_8002D1A4(int type, short slot)
{
    int r = 0;
    switch ((short)type)
    {
    case 0:
        break;
    default:
        r = 4;
        break;
    case 3:
        r = 1;
        break;
    case 1:
        r = 2;
        break;
    case 2:
        r = 3;
        break;
    }
    type = r;
    if (type >= 4)
    {
        return abilityIconsNoType_800827F0[slot];
    }
    return abilityIconsByType_8008280C[slot][type];
}
typedef struct
{
    unsigned short flags;
    unsigned short type;
    int text;
    SPRT** sprts_8;
    DR_TPAGE** tpages_C;
    short x;
    short y;
    short w;
    short h;
    short mx;
    short my;
} MenuItem_D250;
extern int CheckItemOnTarget_80033DF4(short* p);
extern int CheckMagicUsable_80034068(short* p);
// Matched
int DrawTargetSelectMenu_8002D250(short* p, int mode, int cursor, int ot)
{
    MenuItem_D250 list0[4] = {
        {8, 4, 0, 0, 0, 0x2E, 0x98, 0x3C, 0xC, 2, 2},
        {8, 0, 0, 0, 0, 0x26, 0x98, 6, 0xC, 2, 2},
        {8, 0, 0, 0, 0, 0x6C, 0x98, 6, 0xC, 2, 2},
        {1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1},
    };
    MenuItem_D250 list1[2] = {
        {8, 4, 0, 0, 0, 0x2E, 0xA6, 0x3C, 0xC, 2, 2},
        {1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1},
    };
    MenuItem_D250 list2[2] = {
        {8, 4, 0, 0, 0, 0x2E, 0xB3, 0x3C, 0xC, 2, 2},
        {1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1},
    };
    MenuItem_D250 list3[2] = {
        {8, 4, 0, 0, 0, 0x2E, 0xC0, 0x3C, 0xC, 2, 2},
        {1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1},
    };
    MenuItem_D250* lists[5] = {0};
    MenuItem_D250* subs[3] = {0};
    int k = 0;
    struct_A5A4 s = {2, 0, 8, 0, 0, 0};
    int minionCount;
    int allMask;
    int i;
    int r;
    int state;
    UnitStatus* status;
    int y;
    MenuItem_D250* m;
    minionCount = CountMinions_80010548(3);
    allMask = GetAllMinionsTargetMask_8002D780();
    s.field_4 = GetTime30Hz_8002C64C();
    s.field_C = cursor;
    s.field_10 = (MenuItem_1C**)lists;
    s.field_14 = ot;
    subs[0] = list1;
    subs[1] = list2;
    subs[2] = list3;
    if (mode == 0 || mode == 3)
    {
        status = GetUnitStatus_80014390(0);
        lists[k] = list0;
        lists[k][0].text = (int)status->name_10;
        p[2] = 0;
        if (mode == 0)
        {
            state = CheckItemOnTarget_80033DF4(p);
        }
        else
        {
            state = 0;
        }
        if (state == 0 || state == 1)
        {
            lists[k][0].flags &= ~2;
            lists[k][1].flags &= ~2;
            lists[k][2].flags &= ~2;
        }
        else
        {
            lists[k][0].flags |= 2;
            lists[k][1].flags |= 2;
            lists[k][2].flags |= 2;
        }
        k++;
    }
    y = 0;
    for (i = 0; i < minionCount; i++)
    {
        r = IsTargetListed_8002D738(i, p[1], mode);
        if (r == 1)
        {
            p[2] = i + 1;
            status = GetUnitStatus_80014390(((unsigned char*)p)[4]);
            state = 0;
            m = subs[i];
            lists[k] = m;
            m->text = (int)status->name_10;

            lists[k]->y = 0xA6 + y * 13;
            if (mode == 0)
            {
                state = CheckItemOnTarget_80033DF4(p);
            }
            else if (mode == 1)
            {
                state = CheckMagicUsable_80034068(p);
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
                lists[k]->flags &= ~2;
            }
            else
            {
                lists[k]->flags |= 2;
            }
            k++;
            y++;
        }
    }
    DrawMenuWindows_8002A5A4(&s);
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
        return p[1];
    case 2:
        return cursor + 1;
    case 3:
        if (cursor < 0)
        {
            return (allMask | 1) & ~(1 << p[1]);
        }
        if (cursor < p[1])
        {
            return cursor;
        }
        return cursor + 1;
    }
    return 0;
}
