#ifndef TU_80010228_H
#define TU_80010228_H

// 0x40-byte state of a model task (StartModelTask_80010850 copies its 0x34-byte parameters to
// +4; StepModelTask_80010AD8 runs state_38: 1 ModelTaskLoad_80010B90, 2 ModelTaskDraw_80010DB0,
// 3 sub_80010CDC, 4 ModelTaskWaitLoad_80010C30, 5 done)
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

/* the buffer of a modelTasks_8008D618 entry */
typedef struct
{
    int key_0; // the entry's field_4, returned by StartModelTask_80010850
    ModelTaskState* state_4;
} ModelTaskBuf;

#endif
