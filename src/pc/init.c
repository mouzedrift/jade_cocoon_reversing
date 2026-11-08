/* PC only: start-up */
#include <stdio.h>
#include <stdlib.h>
#include <psyz.h>
#include <libgpu.h>
#include <psyz/cd.h>
#include <psyz/log.h>
#include "pc/pc.h"

/* debugging:
   JC_DUMP_VRAM=FRAME[,FRAME...]:FILE writes the 1024x512 VRAM (16 bit pixels) to FILE.FRAME at those vertical blanks
   JC_INPUT=FRAME+COUNT:MASK[,...] holds the pad 1 buttons MASK (hex, 0x0800 start, 0x0040 cross, as libetc's
   PadRead bits swapped: high byte select/start/directions, low byte shoulders/shapes) for COUNT vertical blanks */
#define MAX_EVENTS 64
static int dumpFrames[MAX_EVENTS], numDumps;
static const char* dumpFile;
static struct { int frame, count, mask; } inputs[MAX_EVENTS];
static int numInputs;
static int frames;

static void DumpVram(void)
{
    static u_short vram[1024 * 512];
    RECT r = { 0, 0, 1024, 512 };
    char name[300];
    FILE* f;
    StoreImage(&r, (u_long*)vram);
    DrawSync(0);
    snprintf(name, sizeof(name), "%s.%d", dumpFile, frames);
    f = fopen(name, "wb");
    if (f)
    {
        fwrite(vram, sizeof(vram), 1, f);
        fclose(f);
        INFOF("VRAM written to %s", name);
    }
}

static void PressButtons(int mask)
{
    char frame[PSYZ_PAD_BUF_LEN] = { 0 };
    frame[1] = 0x41; /* digital pad */
    frame[2] = ~(mask >> 8);
    frame[3] = ~mask;
    Psyz_PadsSet(0, frame, sizeof(frame));
}

static void FrameHook(void)
{
    int i;
    frames++;
    for (i = 0; i < numDumps; i++)
        if (dumpFrames[i] == frames)
            DumpVram();
    for (i = 0; i < numInputs; i++)
        if (frames >= inputs[i].frame && frames < inputs[i].frame + inputs[i].count)
            PressButtons(inputs[i].mask);
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
        const char* s = getenv("JC_DUMP_VRAM");
        int n;
        while (numDumps < MAX_EVENTS && sscanf(s, "%d%n", &dumpFrames[numDumps], &n) == 1)
        {
            numDumps++;
            s += n;
            if (*s != ',')
                break;
            s++;
        }
        if (*s == ':')
            dumpFile = s + 1;
        else
            numDumps = 0;
    }
    if (getenv("JC_INPUT"))
    {
        const char* s = getenv("JC_INPUT");
        int n;
        while (numInputs < MAX_EVENTS &&
               sscanf(s, "%d+%d:%x%n", &inputs[numInputs].frame, &inputs[numInputs].count, &inputs[numInputs].mask, &n) == 3)
        {
            numInputs++;
            s += n;
            if (*s != ',')
                break;
            s++;
        }
    }
    if (numDumps || numInputs)
        Psyz_SetVSyncCb(FrameHook);
}
