/* PC only: start-up */
#include <stdlib.h>
#include <psyz.h>
#include <psyz/cd.h>
#include <psyz/log.h>
#include "pc/pc.h"

/* the disc image: $JC_DISC, or jade_cocoon.cue in the working directory */
void Pc_Init(void)
{
    const char* disc = getenv("JC_DISC");
    if (!disc)
        disc = "jade_cocoon.cue";
    if (Psyz_CdSetDiskPath(disc) < 0)
        WARNF("cannot open the disc image %s (set JC_DISC)", disc);
    Pc_SaveOverlays();
}
