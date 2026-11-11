#ifndef PC_MAPCODE_H
#define PC_MAPCODE_H
/* PC only: the maps' code (src/maps, scripts/pc_maps.py) and where the PlayStation had its names */
typedef struct PcMapSym
{
    unsigned int addr; /* PlayStation address */
    unsigned int size; /* 0: a function */
    void* ptr;
} PcMapSym;

typedef struct PcMap
{
    int fileId; /* the map file (src/enums.h SCENE_..._SBH) */
    const char* name;
    const PcMapSym* syms;
    int count;
} PcMap;

extern const PcMap* const pcMaps[];
void Pc_MapCodeLoaded(int fileId);
void* Pc_MapPtr(unsigned int addr);
int Pc_MapCodeCall(unsigned int addr, long arg);
#endif
