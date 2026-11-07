/* PC only: what loading an overlay does to its data. All overlays are linked in (CMakeLists.txt), each with its
   .data and .bss in sections of its own; at start their contents are saved, and when the game loads an overlay
   (LoadOverlay_80020BF8) its .data is put back as the file has it and its .bss cleared. */
#include <stdlib.h>
#include <string.h>
#include "sdk.h"
#include "enums.h"
#include "pc/pc.h"

#define OVERLAY_SECTIONS(X)                                                                                           \
    X(TITLE) X(SOUNDTST) X(TSTMODEL) X(TSTCOMPO) X(GAME) X(COMBAT) X(COMBCOM) X(COMBCHUI) X(COMBSEL) X(COMBLOAD)    \
    X(COMBSTRT) X(COMBBTL) X(COMBRSLT) X(BATTLE) X(MAP) X(MENU) X(SHOPCTRL) X(SHOP) X(SHOPENTR) X(WPNSHOP)          \
    X(CONFIG) X(LOAD) X(NAME) X(EQUIP) X(CHAPTER) X(EVENTFNC)

#define DECLARE(name)                                                                                                 \
    extern char __start_jc_##name##_data[] __attribute__((weak));                                                     \
    extern char __stop_jc_##name##_data[] __attribute__((weak));                                                      \
    extern char __start_jc_##name##_bss[] __attribute__((weak));                                                      \
    extern char __stop_jc_##name##_bss[] __attribute__((weak));
OVERLAY_SECTIONS(DECLARE)

typedef struct
{
    int fileId;
    char* data;
    char* dataEnd;
    char* bss;
    char* bssEnd;
    char* saved;
} PcOverlay;

#define ENTRY(name)                                                                                                   \
    { OVER_##name##_BIN, __start_jc_##name##_data, __stop_jc_##name##_data, __start_jc_##name##_bss,                   \
      __stop_jc_##name##_bss },
static PcOverlay pcOverlays[] = { OVERLAY_SECTIONS(ENTRY) };

void Pc_SaveOverlays(void)
{
    unsigned int i;
    for (i = 0; i < sizeof(pcOverlays) / sizeof(*pcOverlays); i++)
    {
        PcOverlay* o = &pcOverlays[i];
        if (o->data && o->dataEnd > o->data)
        {
            o->saved = malloc(o->dataEnd - o->data);
            memcpy(o->saved, o->data, o->dataEnd - o->data);
        }
    }
}

void Pc_OverlayLoaded(int fileId)
{
    unsigned int i;
    for (i = 0; i < sizeof(pcOverlays) / sizeof(*pcOverlays); i++)
    {
        PcOverlay* o = &pcOverlays[i];
        if (o->fileId != fileId)
            continue;
        if (o->saved)
            memcpy(o->data, o->saved, o->dataEnd - o->data);
        if (o->bss && o->bssEnd > o->bss)
            memset(o->bss, 0, o->bssEnd - o->bss);
    }
}
