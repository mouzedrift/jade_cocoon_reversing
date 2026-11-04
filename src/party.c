#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "STDLIB.H"
#include "STDIO.H"
#include "LIBPAD.H"
#include "LIBSND.H"
#include "LIBMCX.H"
#include "LIBPRESS.H"
#include "LIBETC.H"
#include "LIBMCRD.H"
#include "sound.h"
#include "data_decls.h"
#include "model.h"
#include "party.h"


extern unsigned long SpuSetTransferStartAddr(unsigned long addr);
extern unsigned long SpuWrite0(unsigned long size);
extern void McxStopCom(void);
extern void MemCardEnd(void);
// hand-written assembly: leaves its jr delay slot empty, which the compiler never does
INCLUDE_ASM(GetHeapStart_80010538);
// Matched
int CountMinions_80010548(int id)
{
    int count;
    int i;

    count = 0;
    for (i = 0; i < 15; i++)
    {
        if (saveData_8008B570.minions[i].id == 4)
        {
            continue;
        }
        if (saveData_8008B570.minions[i].id == id || id == 0)
        {
            count++;
        }
    }
    return count;
}
// Matched
Minion* GetMinion_80010598(int id, int nth)
{
    Minion* result;
    int matches;
    int i;

    result = 0;
    matches = 0;
    for (i = 0; i < 15; i++)
    {
        if (id == saveData_8008B570.minions[i].id || id == 0)
        {
            matches++;
            if (nth < matches)
            {
                result = &saveData_8008B570.minions[i];
                break;
            }
        }
    }
    return result;
}
#if 0
// Not matched: only the order of the two constant loads (4 / 0xE) differs
void ClearMinionsAndItems_80010600(void)
{
    int i;

    for (i = 14; i >= 0; i--)
    {
        saveData_8008B570.minions[i].id = 4;
    }
    for (i = 11; i >= 0; i--)
    {
        saveData_8008B570.items[i].species_5C = 0xD3;
    }
}
#endif
// Matched
void ClearMinionsAndItems_80010600(void)
{
    int i;
    int marker = 4;

    for (i = 14; i >= 0; i--)
    {
        saveData_8008B570.minions[i].id = marker;
    }
    marker = 0xD3;
    for (i = 11; i >= 0; i--)
    {
        saveData_8008B570.items[i].species_5C = marker;
    }
}
// Matched
int AddItem_80010650(UnitStats* pItem)
{
    int i;

    for (i = 0; i < 12; i++)
    {
        if (saveData_8008B570.items[i].species_5C == 0xD3)
        {
            MemCopy_800403E8(&saveData_8008B570.items[i], pItem, sizeof(UnitStats));
            return 1;
        }
    }
    return 0;
}
// Matched
int CountItems_800106B8(void)
{
    int count;
    int i;

    count = 0;
    for (i = 0; i < 12; i++)
    {
        if (saveData_8008B570.items[i].species_5C != 0xD3)
        {
            count++;
        }
    }
    return count;
}
// Matched
unsigned char* GetMinionName_800106F8(int id, int nth)
{
    Minion* m = GetMinion_80010598(id, nth);
    if (m)
    {
        return m->status_84.name_10;
    }
    return 0;
}
// Matched
unsigned char* GetMinionAncestorName_80010724(int id, int nth, int idx)
{
    Minion* m = GetMinion_80010598(id, nth);
    if (m)
    {
        return m->ancestors_4[idx];
    }
    return 0;
}
// Matched
unsigned char GetMinionAncestorElement_80010768(int id, int nth, int idx)
{
    Minion* m = GetMinion_80010598(id, nth);
    if (m)
    {
        return m->ancestorElements_7C[idx];
    }
    return 0;
}
// Matched
UnitStatus* GetMinionStatus_800107A0(int id, int nth)
{
    Minion* m = GetMinion_80010598(id, nth);
    if (m)
    {
        return &m->status_84;
    }
    return 0;
}
// Matched
unsigned char* GetMinionStatBlock_800107CC(int id, int nth)
{
    Minion* m = GetMinion_80010598(id, nth);
    if (m)
    {
        return m->field_CC.cur_0;
    }
    return 0;
}
// Matched
UnitSkills* GetMinionSkills_800107F8(int id, int nth)
{
    Minion* m = GetMinion_80010598(id, nth);
    if (m)
    {
        return &m->skills_DE;
    }
    return 0;
}
// Matched
unsigned int* GetMinionMagicBits_80010824(int id, int nth)
{
    Minion* m = GetMinion_80010598(id, nth);
    if (m)
    {
        return &m->magicBits_F4;

    }
    return 0;
}
extern EventNode* modelTasks_8008D618;
// Matched
int StartModelTask_80010850(void* params)
{
    EventEntry* e = AllocEventEntry_80043AF8(modelTasks_8008D618);
    ModelTaskBuf* buf;
    ModelTaskState* m;
    if (e != 0)
    {
        e->cb_8 = (EventEntryFn)ModelTaskUpdateCb_80010A90;
        buf = e->buffer;
        e->cb_C = (EventEntryFn)ModelTaskFreeCb_80010AB4;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        e->flags = (e->flags | 4) & 0xFFFF7FFF;
        buf->key_0 = e->index_4;
        m = malloc3_8003FC4C(0x40);
        buf->state_4 = m;
        MemCopy_800403E8(&m->count_4, params, 0x34);
        m->models_0 = 0;
        m->state_38 = 1;
        m->next_3C = 1;
        StepModelTask_80010AD8(m);
        return buf->key_0;
    }
    return -1;
}
// Matched
EventEntry* FindModelTask_8001091C(key)
int key;
{
    EventNode* n = modelTasks_8008D618;
    int count = n->count;
    EventEntry* e;
    int i;
    for (i = 0; i < count; i++)
    {
        e = &n->entry;
        if ((e->flags & 0x8001) == 1)
        {
            if (((ModelTaskBuf*)e->buffer)->key_0 == key)
            {
                return e;
            }
        }
        n = n->next;
    }
    return 0;
}
// Matched
int FreeModelTask_8001098C(int key)
{
    EventEntry* e = FindModelTask_8001091C();
    ModelTaskBuf* buf = e->buffer;
    ModelTaskState* state = buf->state_4;
    if (state->state_38 == 5)
    {
        FreeModelList_80024BB0(&buf->state_4->models_0);
        free3_8003FC6C(buf->state_4);
        e->flags = (e->flags & ~1) | 0x8000;
        e->flags = (e->flags & ~4) | 0x8000;
        return 1;
    }
    return 0;
}
// Matched
void RunModelTask_80010A10(int key)
{
    EventEntry* entry = FindModelTask_8001091C();
    StepModelTask_80010AD8(((ModelTaskBuf*)entry->buffer)->state_4);
}
// Matched
Model* GetModelTaskModel_80010A44(int key)
{
    ModelTaskBuf* buf = FindModelTask_8001091C()->buffer;
    ModelTaskState* state = buf->state_4;
    if (state->state_38 == 5)
    {
        return state->models_0->items_8;
    }
    return 0;
}
// Matched
void ModelTaskUpdateCb_80010A90(int entry, int* buf)
{
    RunModelTask_80010A10(*buf);
}
// Matched
void ModelTaskFreeCb_80010AB4(int entry, int* buf)
{
    FreeModelTask_8001098C(*buf);
}
// Matched
int StepModelTask_80010AD8(ModelTaskState* state)
{
    int cont = 1;
    int done = 0;
    do
    {
        switch (state->state_38)
        {
        case 0:
            break;
        case 1:
            cont = ModelTaskLoad_80010B90(state);
            break;
        case 2:
            cont = ModelTaskDraw_80010DB0(state);
            break;
        case 3:
            cont = ModelTaskApplyTextures_80010CDC(state);
            break;
        case 4:
            cont = ModelTaskWaitLoad_80010C30(state);
            break;
        case 5:
            cont = 0;
            done = 1;
            break;
        }
    } while (cont);
    return done;
}
