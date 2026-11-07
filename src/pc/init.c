/* PC only: start-up */
#include <stdio.h>
#include <stdlib.h>
#include <psyz.h>
#include <libgpu.h>
#include <psyz/cd.h>
#include <psyz/log.h>
#include "pc/pc.h"

/* debugging: JC_DUMP_VRAM=FRAME:FILE writes the 1024x512 VRAM (16 bit pixels) to FILE at vertical blank FRAME */
static int dumpFrame = -1;
static const char* dumpFile;
static int frames;
static void DumpVram(void)
{
    static u_short vram[1024 * 512];
    RECT r = { 0, 0, 1024, 512 };
    FILE* f;
    if (++frames != dumpFrame)
        return;
    StoreImage(&r, (u_long*)vram);
    DrawSync(0);
    f = fopen(dumpFile, "wb");
    if (f)
    {
        fwrite(vram, sizeof(vram), 1, f);
        fclose(f);
        INFOF("VRAM written to %s at frame %d", dumpFile, frames);
    }
}

/* the disc image: $JC_DISC, or jade_cocoon.cue in the working directory */
void Pc_Init(void)
{
    const char* disc = getenv("JC_DISC");
    if (!disc)
        disc = "jade_cocoon.cue";
    if (Psyz_CdSetDiskPath(disc) < 0)
        WARNF("cannot open the disc image %s (set JC_DISC)", disc);
    Pc_SaveOverlays();
    if (getenv("JC_DUMP_VRAM"))
    {
        static char file[256];
        if (sscanf(getenv("JC_DUMP_VRAM"), "%d:%255s", &dumpFrame, file) == 2)
        {
            dumpFile = file;
            Psyz_SetVSyncCb(DumpVram);
        }
    }
}
