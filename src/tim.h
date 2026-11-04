#ifndef TU_80028C60_H
#define TU_80028C60_H

/* ParseTim_80029708 output */
typedef struct TimInfo
{
    int mode_valid;
    int mode;
    int clut_len;
    RECT crect;
    u_long* caddr;
    int pix_len;
    RECT prect;
    u_long* paddr;
} TimInfo;

#endif
