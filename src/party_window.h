#ifndef _TU_8002F6F8_H_
#define _TU_8002F6F8_H_

typedef struct
{
    unsigned short s[11];
} NameBuf;
extern const NameBuf emptyNameBuf_80074434;

typedef struct
{
    short open_0;      // open animation step, 8: open
    short partySize_2; // partyWindowRects_80082E90 row + 1
    short cursor_4;    // the selected slot
    short ot_6;
    int time_8;        // window pulse time of the selected slot
    short slot_C;
    short pad_E;
    unsigned int highlight_10;
} PartySlotWindow;

void DrawSmallText_8002FAA0(int align, unsigned short* pos, unsigned char* text, int ot);
short GetLevantLevel_8002FA70(void);
void DrawLargeText_8002FBD8(int align, unsigned short* pos, unsigned char* text, int ot);
/* DrawPulsingWindow_8002F6F8's state */
typedef struct PulseState
{
    short* time_0; /* counts 0 - 39 (the pulse) */
    int on_4;      /* 0: dim */
    int pulse_8;   /* 0: no pulse */
} PulseState;
void DrawPulsingWindow_8002F6F8(RECT* rect, PulseState* st, int unused);
void DrawLevantStats_8002F7D0(unsigned short* pos, short ot);
void DrawPartySlotWindow_8002F8E4(UnitStatus* unit, PartySlotWindow* win);
short GetPartyWindowX_8002FA0C(short partySize, short slot);
char* GetRankName_8002FCD8(int idx);
#endif
