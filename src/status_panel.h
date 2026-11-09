#ifndef TU_8002DA3C_H
#define TU_8002DA3C_H

/* DrawLevantSummary_8002E334's second argument */
typedef struct
{
    short ot_0;
    short open_2;      // open animation step (DrawAnimatedWindow_8002BEC8)
    int highlight_4;
    int time_8;
} MenuDrawArgs;

typedef struct
{
    unsigned char c[4];
} StatGridColor;
extern const StatGridColor statGridLineColor_800743D0;

void CalcStatsWithEquip_8002E288(UnitStatus* src, int itemId, int slot, unsigned char* outStats);
void DrawStatCompare_8002E188(unsigned char* oldStats, unsigned char* newStats, unsigned short* pos, short ot);
void DrawLevantSummary_8002E334(UnitStatus* st, MenuDrawArgs* args);
void DrawUnitStatusPanel_8002DB48(UnitStatus* unit, int ot, void* unused, unsigned short* pos, Minion* minion, UnitStatus* cmp);
void DrawStatIcons_8002E0D8(unsigned short* origin, short ot);
void DrawStatDelta_8002E004(unsigned short* origin, int delta, int ot);
void DrawElementChart_8002E730(unsigned short* pos, unsigned char* levels, short ot);
void DrawStatGrid_8002EACC(UnitStatus* st, unsigned short* pos, unsigned char* unused, short ot);
void SetElementChartTri_8002E944(POLY_F3* tri, unsigned short* pos, short level, short quadrant);
#endif
