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
#include "family_tree.h"
#include "effect_data.h"
#include "unit_query.h"
#include "event.h"
#include "menu_draw.h"
#include "unit_gauges.h"
#include "party_window.h"

const char aDeveloper_80074320[] = "\202c\202\205\202\226\202\205\202\214\202\217\202\220\202\205\202\222"; // Developer
const char aConqueror_80074334[] = "\202b\202\217\202\216\202\221\202\225\202\205\202\222\202\217\202\222"; // Conqueror
const char aVindicator_80074348[] = "\202u\202\211\202\216\202\204\202\211\202\203\202\201\202\224\202\217\202\222"; // Vindicator
const char aChampion_80074360[] = "\202b\202\210\202\201\202\215\202\220\202\211\202\217\202\216"; // Champion
const char aHero_80074374[] = "\202g\202\205\202\222\202\217"; // Hero
const char aImmaculate_80074380[] = "\202h\202\215\202\215\202\201\202\203\202\225\202\214\202\201\202\224\202\205"; // Immaculate
const char aAdept_80074398[] = "\202`\202\204\202\205\202\220\202\224"; // Adept
const char aNovice_800743A4[] = "\202m\202\217\202\226\202\211\202\203\202\205"; // Novice
const char aApprentice_800743B4[] = "\202`\202\220\202\220\202\222\202\205\202\216\202\224\202\211\202\203\202\205"; // Apprentice
const CVECTOR familyTreeLineColor_800743CC = { 128, 128, 128 };

// Matched
int IsTargetListed_8002D738(int idx, int self, int mode)
{
    if (mode == 0 || mode == 2)
    {
        return 1;
    }
    if (mode == 3 && idx + 1 != self)
    {
        return 1;
    }
    if (mode == 1 && idx + 1 == self)
    {
        return 1;
    }
    return 0;
}
// Matched
int GetAllMinionsTargetMask_8002D780(void)
{
    int n = CountMinions_80010548(3);
    int i;
    int mask = 0;
    for (i = 0; i < n; i++)
    {
        mask |= 1 << (i + 1);
    }
    return mask;
}
extern const CVECTOR familyTreeLineColor_800743CC;
extern void DrawElementIconsRow_8002B1B0(short mask, int pos, int ot);
// Matched
void DrawFamilyTree_8002D7D0(Minion* m, int ot, Pos16* base)
{
    RECT rect;
    Pos16 pos;
    Pos16 lineFrom;
    Pos16 lineTo;
    CVECTOR color;
    unsigned char levels[4];
    UiWindowDesc win;
    unsigned char* name;
    Pos16* pPos;
    int i;
    int k;
    color = familyTreeLineColor_800743CC;
    pPos = &pos;
    for (i = 0; i < 7; i++)
    {
        pos.x = familyTreeBoxPos_80082DCC[i]->x + base->x;
        pos.y = familyTreeBoxPos_80082DCC[i]->y + base->y;
        rect.x = pos.x;
        rect.y = pos.y;
        rect.w = 0x40;
        rect.h = 0xF;
        if (i == 0)
        {
            name = m->status_84.name_10;
        }
        else
        {
            name = GetAncestorName_80033830(m, i - 1);
        }
        pos.x = familyTreeBoxPos_80082DCC[i]->x + base->x + 3;
        pos.y = familyTreeBoxPos_80082DCC[i]->y + base->y + 4;
        DrawSmallText_8002FAA0(0, (unsigned short*)pPos, name, ot);
        pos.x = (unsigned short)(base->x + 4) + familyTreeBoxPos_80082DCC[i]->x;
        pos.y = (unsigned short)(base->y + 0x10) + familyTreeBoxPos_80082DCC[i]->y;
        if (i == 0)
        {
            GetElementLevels_80033864(m, levels);
            DrawElementIconsRow_8002B1B0(ElementLevelsToMask_8002F424(levels), (int)pPos, ot);
        }
        else
        {
            DrawElementIconsRow_8002B1B0(GetAncestorElementMask_80033848(m, i - 1), (int)pPos, ot);
        }
        win.colorSet_8 = 0;
        win.rect_0 = &rect;
        win.ot_A = ot;
        win.time_4 = frameCount_8008D3FC;
        DrawUiWindow_8002A384(&win);
    }
    for (k = 0; k < 12; k++)
    {
        lineFrom.x = familyTreeLineFrom_80082DE8[k].x + base->x;
        lineFrom.y = familyTreeLineFrom_80082DE8[k].y + base->y;
        lineTo.x = familyTreeLineTo_80082E18[k].x + base->x;
        lineTo.y = familyTreeLineTo_80082E18[k].y + base->y;
        DrawLine_80042870((DVECTOR*)&lineFrom, (DVECTOR*)&lineTo, (unsigned char*)&color, &pOT_8008D454[ot]);
    }
}
