#ifndef _TU_800174F8_H_
#define _TU_800174F8_H_

extern const int off_80072278[0];

// effect is unused (the GAME caller passes the effect id)
HitTimes* RepeatHitTimes_80018200(HitTimes* src, unsigned short loopStart, unsigned short loopEnd, short loops, int effect);

#endif
