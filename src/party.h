#ifndef TU_80010228_H
#define TU_80010228_H

// 0x40-byte state of a model task (StartModelTask_80010850 copies its 0x34-byte parameters to
// +4; StepModelTask_80010AD8 runs state_38: 1 ModelTaskLoad_80010B90, 2 ModelTaskDraw_80010DB0,
// 3 ModelTaskApplyTextures_80010CDC, 4 ModelTaskWaitLoad_80010C30, 5 done)
typedef struct ModelTaskState
{
    ModelList* models_0;
    int count_4;    // models blended (1..3)
    int ids_8[3];   // model ids
    int weights_14[3];
    int record_20;  // model header record index (GetModelBaseScale_80024E90 ...)
    int texPart_24; // ids_8 index of the model the textures come from
    int texSel_28;  // texture slot (LoadModelListTextures_800255F0)
    int texId_2C;   // >= 0: model id to take the textures from instead
    int main_30;    // ids_8 index of the model whose animations are kept
    struct ModelVramSlot* vram_34;
    int state_38;
    int next_3C;
} ModelTaskState;

/* what StartModelTask_80010850 builds a model from (copied to ModelTaskState.count_4..vram_34) */
typedef struct ModelTaskParams
{
    int count_0;    // models blended (1..3)
    int ids_4[3];   // model ids
    int weights_10[3];
    int record_1C;  // model header record index
    int texPart_20; // ids_4 index of the model the textures come from
    int texSel_24;  // texture slot / hue
    int texId_28;   // >= 0: model id to take the textures from instead
    int main_2C;    // ids_4 index of the model whose animations are kept
    struct ModelVramSlot* vram_30;
} ModelTaskParams;

/* the buffer of a modelTasks_8008D618 entry */
typedef struct
{
    int key_0; // the entry's field_4, returned by StartModelTask_80010850
    ModelTaskState* state_4;
} ModelTaskBuf;

int CountMinions_80010548(int id);
Minion* GetMinion_80010598(int id, int nth);
void ClearMinionsAndItems_80010600(void);
int AddItem_80010650(UnitStats* pItem);
int CountItems_800106B8(void);
unsigned char* GetMinionName_800106F8(int id, int nth);
unsigned char* GetMinionAncestorName_80010724(int id, int nth, int idx);
unsigned char GetMinionAncestorElement_80010768(int id, int nth, int idx);
UnitStatus* GetMinionStatus_800107A0(int id, int nth);
unsigned char* GetMinionStatBlock_800107CC(int id, int nth);
UnitSkills* GetMinionSkills_800107F8(int id, int nth);
unsigned int* GetMinionMagicBits_80010824(int id, int nth);
void ModelTaskUpdateCb_80010A90(int entry, int* buf);
void ModelTaskFreeCb_80010AB4(int entry, int* buf);
int FreeModelTask_8001098C(int key);
int StepModelTask_80010AD8(ModelTaskState* state);
int RunModelTask_80010A10(int key);
Model* GetModelTaskModel_80010A44(int key);
int StartModelTask_80010850(void* params);
#endif
