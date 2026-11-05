#ifndef _UI_GAUGE_H_
#define _UI_GAUGE_H_

#include "globals.h"

typedef struct
{
    unsigned short kind;
    unsigned short dir;
} ScrollArrow;

typedef struct
{
    int state;
    int delta_4; // pending change, drawn blinking
    int cur_8;
    int max_C;
} Gauge;

void DrawScrollArrows_8002B8DC(ScrollArrow arrow, short* list, short* pos, int ot);
void DrawScrollArrow_8002B3DC(ScrollArrow arrow, int time, short* pos, int ot);
void DrawGauge_8002BA54(Gauge* gauge, int time, short* origin, int ot);
unsigned int ScaleGaugeLength_8002BC60(unsigned int value, unsigned int max, unsigned int length);
void DrawGaugeBar_8002BCAC(int idx, int scale, short* pos, unsigned int time, int ot);
#endif
