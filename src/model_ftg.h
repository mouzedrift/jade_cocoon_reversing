#ifndef _MODEL_FTG_H_
#define _MODEL_FTG_H_

#include "globals.h"
#include "util.h"

void LoadFtgMatList_80021E4C(int* file, FtgMatList* out, unsigned int count);
int* LoadMapMeshes_80027A88(MapMesh** out, unsigned int* count, List* heap, MapMeshFile* hdr);
void CountFtgSprites_80022B84(unsigned char* cursor, int* sprites, int* texSprites);
int AllocFtgObjectPrims_80022634(FtgObject* out, FtgSrcObjectHeader* hdr, int h);
int LoadFtgSprites_8002300C(FtgPrimHeader* hdr, FtgSrcSprites8* p_in, FtgSpriteGroups8* groups8, int k, int h);
int LoadFtgTexSprites_8002320C(FtgPrimHeader* hdr, FtgSrcSprites9* p_in, FtgSpriteGroups9* groups9, int k, int h);
void MergeFtgSpriteGroups_80022CC4(FtgObject* obj, FtgSpriteGroups8* groups8, FtgSpriteGroups9* groups9, int h);
void OnMapFileLoaded_80028808(void* params, int* data);
int UsePreloadedArea_80027358(int id);
void FreeRecordTables_80026DE8(RecordTable** tables, int count, int h);
void AllocRecordTables_80026D78(RecordTable** out, int count, int heap);
void LoadRecordTables_80026E74(RecordTable* tables, int* file, int heap);
void SetLoadFadeFlag_80027478(int mask, int set);
void InitMapState_80026FAC(void);
void ResetMapLoaderTask_8002830C(EventEntry* entry);
void LoadTileSets_80027778(int* data, List* heap);
void LoadTileAnimLayers_800278BC(int* data, List* heap);
#endif
