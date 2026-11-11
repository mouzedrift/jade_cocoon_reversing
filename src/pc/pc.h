#ifndef PC_H
#define PC_H

/* PC only (src/pc): what the PlayStation does that the PC build does itself */

void Pc_Init(void);                  /* at start: the disc image, the overlays' data */
void Pc_SaveOverlays(void);
void Pc_OverlayLoaded(int fileId);    /* LoadOverlay_80020BF8: an overlay's data as its file has it */

#endif
