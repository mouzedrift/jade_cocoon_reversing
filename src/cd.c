#include "common.h"
#include "funcs.h"
#include "sdk.h"
#include "globals.h"
#include "model.h"
#include "cdread.h"
#include "sound.h"
#include "data_decls.h"
#include "cd.h"
#include "cdread.h"
#include "main.h"
#include "gte.h"
#include "util.h"


const char aDataData0011[] = "\\DATA\\DATA.001;1";
const char aAssertionFaile_1[] = "Assertion failed: file \"%s\", line %d\n";
const char aCdC[] = "CD.C";
const int unused_800748DC = 0;

void SetBattleStageId_80039FA4(int id)
{
    battleStageId_80083BD0 = id;
}
int GetBattleStageId_80039FB0(void)
{
    return battleStageId_80083BD0;
}
void FreeStageEffects_80039FC0(void)
{
    FreeEffectFile_80020EE0(&battleEffectFile_80095468);
}
// FtgObject (model.h) seen as its eight polygon lists and two sprite lists
typedef struct
{
    short count_0;
    short pad_2;
    char* prims_4;
} PolyGroup;
typedef struct
{
    PolyGroup g[8];
    int spriteCount_40;
    char* sprites_44;
    int texSpriteCount_48;
    int tpageClut_4C;
    char* texSprites_50;
} PolyGroups;
typedef struct
{
    char pad[4];
    SVECTOR a;
    SVECTOR b;
} EdgeDelta;

#define DIFF_GROUP(k, size, off, nv)                                              \
    if (pb->g[k].count_0 * nv)                                                          \
    {                                                                             \
        int j;                                                                    \
        for (i = 0; i < pb->g[k].count_0; i++)                                          \
        {                                                                         \
            SVECTOR* vo = (SVECTOR*)(po->g[k].prims_4 + i * size + off);                \
            SVECTOR* vb = (SVECTOR*)(pb->g[k].prims_4 + i * size + off);                \
            SVECTOR* va = (SVECTOR*)(pa->g[k].prims_4 + i * size + off);                \
            for (j = 0; j < nv; j++)                                              \
            {                                                                     \
                vo[j].vx = va[j].vx - vb[j].vx;                                   \
                vo[j].vy = va[j].vy - vb[j].vy;                                   \
                vo[j].vz = va[j].vz - vb[j].vz;                                   \
            }                                                                     \
        }                                                                         \
    }

void DiffFtgObjects_80039FE4(struct FtgObject* a, struct FtgObject* b, struct FtgObject* out)
{
    PolyGroups* pa = (PolyGroups*)a;
    PolyGroups* pb = (PolyGroups*)b;
    PolyGroups* po = (PolyGroups*)out;
    int i;

    DIFF_GROUP(0, 0x24, 4, 4);
    DIFF_GROUP(1, 0x3C, 0xC, 6);
    DIFF_GROUP(2, 0x30, 0x10, 4);
    DIFF_GROUP(3, 0x48, 0x18, 6);
    DIFF_GROUP(4, 0x2C, 4, 5);
    DIFF_GROUP(5, 0x50, 0x10, 8);
    DIFF_GROUP(6, 0x38, 0x10, 5);
    DIFF_GROUP(7, 0x5C, 0x1C, 8);
    if (pa->spriteCount_40)
    {
        EdgeDelta* ea;
        EdgeDelta* eb;
        EdgeDelta* eo;
        ea = (EdgeDelta*)pa->sprites_44;
        eb = (EdgeDelta*)pb->sprites_44;
        eo = (EdgeDelta*)po->sprites_44;
        for (i = 0; i < pa->spriteCount_40; i++)
        {
            eo->a.vx = ea->a.vx - eb->a.vx;
            eo->a.vy = ea->a.vy - eb->a.vy;
            eo->a.vz = ea->a.vz - eb->a.vz;
            eo->b.vx = ea->b.vx - eb->b.vx;
            eo->b.vy = ea->b.vy - eb->b.vy;
            eo->b.vz = ea->b.vz - eb->b.vz;
            ea++;
            eb++;
            eo++;
        }
    }
    if (pa->texSpriteCount_48)
    {
        EdgeDelta* ea;
        EdgeDelta* eb;
        EdgeDelta* eo;
        ea = (EdgeDelta*)pa->texSprites_50;
        eb = (EdgeDelta*)pb->texSprites_50;
        eo = (EdgeDelta*)po->texSprites_50;
        for (i = 0; i < pa->texSpriteCount_48; i++)
        {
            eo->a.vx = ea->a.vx - eb->a.vx;
            eo->a.vy = ea->a.vy - eb->a.vy;
            eo->a.vz = ea->a.vz - eb->a.vz;
            eo->b.vx = ea->b.vx - eb->b.vx;
            eo->b.vy = ea->b.vy - eb->b.vy;
            eo->b.vz = ea->b.vz - eb->b.vz;
            ea++;
            eb++;
            eo++;
        }
    }
}
/* o = a + d * t / 4096 */
#define LERP_SV(o, a, d, t)  \
    {                        \
        gte_lddp(0x1000);    \
        gte_ldsv(a);         \
        gte_gpf12();         \
        gte_lddp(t);         \
        gte_ldsv(d);         \
        gte_gpl12();         \
        gte_stsv(o);         \
    }

#define LERP_GROUP(k, size, off, nn, nv)                                          \
    if (pa->g[k].count_0 * (nn + nv))                                                   \
    {                                                                             \
        int j;                                                                    \
        for (i = 0; i < pa->g[k].count_0; i++)                                          \
        {                                                                         \
            vo = (SVECTOR*)(po->g[k].prims_4 + i * size + off);                \
            va = (SVECTOR*)(pa->g[k].prims_4 + i * size + off);                \
            vd = (SVECTOR*)(pd->g[k].prims_4 + i * size + off);                \
            for (j = 0; j < nn; j++)                                              \
            {                                                                     \
                LERP_SV(&vo[j], &va[j], &vd[j], t);                               \
            }                                                                     \
            for (j = nn; j < nn + nv; j++)                                        \
            {                                                                     \
                LERP_SV(&vo[j], &va[j], &vd[j], t);                               \
            }                                                                     \
        }                                                                         \
    }

void LerpFtgObject_8003A6C4(int t, struct FtgObject* out, struct FtgObject* a, struct FtgObject* d)
{
    PolyGroups* po = (PolyGroups*)out;
    PolyGroups* pa = (PolyGroups*)a;
    PolyGroups* pd = (PolyGroups*)d;
    int i;
    SVECTOR* vo;
    SVECTOR* va;
    SVECTOR* vd;

    LERP_GROUP(0, 0x24, 4, 1, 3);
    LERP_GROUP(1, 0x3C, 0xC, 3, 3);
    LERP_GROUP(2, 0x30, 0x10, 1, 3);
    LERP_GROUP(3, 0x48, 0x18, 3, 3);
    LERP_GROUP(4, 0x2C, 4, 1, 4);
    LERP_GROUP(5, 0x50, 0x10, 4, 4);
    LERP_GROUP(6, 0x38, 0x10, 1, 4);
    LERP_GROUP(7, 0x5C, 0x1C, 4, 4);
    if (po->spriteCount_40)
    {
        EdgeDelta* eo = (EdgeDelta*)po->sprites_44;
        EdgeDelta* ea = (EdgeDelta*)pa->sprites_44;
        EdgeDelta* ed = (EdgeDelta*)pd->sprites_44;
        for (i = 0; i < po->spriteCount_40; i++, eo++, ea++, ed++)
        {
            LERP_SV(&eo->a, &ea->a, &ed->a, t);
            LERP_SV(&eo->b, &ea->b, &ed->b, t);
        }
    }
    if (po->texSpriteCount_48)
    {
        EdgeDelta* eo = (EdgeDelta*)po->texSprites_50;
        EdgeDelta* ea = (EdgeDelta*)pa->texSprites_50;
        EdgeDelta* ed = (EdgeDelta*)pd->texSprites_50;
        for (i = 0; i < po->texSpriteCount_48; i++, eo++, ea++, ed++)
        {
            LERP_SV(&eo->a, &ea->a, &ed->a, t);
            LERP_SV(&eo->b, &ea->b, &ed->b, t);
        }
    }
}
short ratan2_8003B548(long y, long x)
{
    return ratan2(y, x);
}
int ratan2Degrees_8003B56C(int x, int y)
{
    int angle = ratan2(y, x);
    int degrees;
    if (angle < 0)
    {
        angle += 0x1000;
    }
    degrees = angle * 360 / 4096;
    if ((unsigned int)degrees >= 360)
    {
        degrees = 0;
    }
    return degrees;
}
int VectorToAngles_8003B5D4(int* v, short* out)
{
    int len;
    short yaw;
    int pitch;
    len = LengthSquared3D_8003B8DC(v);
    len = ISqrt_8003B918(len);
    yaw = ratan2(v[0], v[2]);
    out[1] = yaw;
    pitch = (short)ratan2(v[1], ISqrt_8003B918(LengthSquared2D_8003B8BC(v[0], v[2])));
    out[0] = -pitch;
    out[2] = 0;
    return len;
}
int Sign_8003B664(int x)
{
    if (x > 0)
    {
        return 1;
    }
    if (x < 0)
    {
        return -1;
    }
    return 0;
}
void ScaleVectorToFit_8003B684(int* v)
{
    int minLzc = 0x20;
    int lzc = Lzc(v[0]);
    if (lzc < minLzc)
    {
        minLzc = lzc;
    }
    lzc = Lzc(v[1]);
    if (lzc < minLzc)
    {
        minLzc = lzc;
    }
    lzc = Lzc(v[2]);
    if (lzc < minLzc)
    {
        minLzc = lzc;
    }
    if (minLzc < 0x12)
    {
        int shift = 0x12 - minLzc;
        v[0] >>= shift;
        v[1] >>= shift;
        v[2] >>= shift;
    }
}
int IsWithinDistance_8003B740(int* a, int* b, unsigned int* dist)
{
    unsigned int sum = -1;
    unsigned int radius = *dist;
    short ok = 0;
    unsigned int dx = abs(a[0] - b[0]);
    if (dx <= radius)
    {
        unsigned int dy = abs(a[1] - b[1]);
        if (dy <= radius)
        {
            unsigned int dz = abs(a[2] - b[2]);
            if (dz <= radius)
            {
                unsigned int radius2;
                sum = dx * dx + dy * dy + dz * dz;
                radius2 = radius * radius;
                ok = !(radius2 < sum);
            }
        }
    }
    *dist = sum;
    return ok;
}
int DistanceSquared3D_8003B80C(int* a, int* b)
{
    int dx = a[0] - b[0];
    int dy = a[1] - b[1];
    int dz = a[2] - b[2];
    return dx * dx + dy * dy + dz * dz;
}
unsigned int DistanceSquaredXZ_8003B860(int* a, int* b)
{
    int dx = a[0] - b[0];
    int dz = a[2] - b[2];
    return dx * dx + dz * dz;
}
int DistanceSquared2D_8003B898(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    return dx * dx + dy * dy;
}
int LengthSquared2D_8003B8BC(int x, int y)
{
    return x * x + y * y;
}
int LengthSquared3D_8003B8DC(int* v)
{
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}
unsigned int ISqrt_8003B918(unsigned int value)
{
    int next;
    int guess;
    if (value != 0)
    {
        next = 1;
        if (value >= 2)
        {
            next = value;
        }
        do
        {
            guess = next;
            next = (value / guess + guess) >> 1;
        } while (next < guess);
        return guess;
    }
    return 0;
}
Vec3i* Midpoint3D_8003B95C(Vec3i* out, Vec3i* a, Vec3i* b)
{
    Vec3i mid;
    mid.x = (a->x + b->x) / 2;
    mid.y = (a->y + b->y) / 2;
    mid.z = (a->z + b->z) / 2;
    *out = mid;
    return out;
}
short ratan2Difference_8003B9E0(int* a, int* b)
{
    return ratan2(b[0] - a[0], b[2] - a[2]);
}
short WrapAngle_8003BA18(int angle)
{
    short wrapped = angle & 0xFFF;
    if (wrapped >= 0x800)
    {
        wrapped |= 0xF000;
    }
    return wrapped;
}
int CompareUInt_8003BA38(unsigned int a, unsigned int b)
{
    if (a > b)
    {
        return -1;
    }
    if (a == b)
    {
        return 0;
    }
    return a < b;
}
int GetCapturedMinionsFromBitfield_8003BA58(int bits)
{
    int result;
    int bit;
    int i;

    result = 0;
    for (i = 0; i < 32; i++)
    {
        bit = 1 << i;
        if (bits & bit)
        {
            result += 1;
        }
    }
    return result;
}
void DelayLoop_8003BA90(void)
{
    float count = 0;
    while (count < 621.0f)
    {
        count += 1.0f;
    }
}
int GetMemCardInfoSync_8003BADC(int port)
{
    int out[2];
    McxAllInfo(port, (unsigned char*)&memCardInfo_8008D4D8);
    while (!McxSync(0, (long*)&out[0], (long*)&out[1]))
    {
    }
    return out[1];
}
void CheckMemCards_8003BB1C(void)
{
    int i;
    int result;
    for (i = 0; i < 2; i++)
    {
        result = GetMemCardInfoSync_8003BADC(i << 4);
        if (result == 0 || result == 3)
        {
            unknownFlags_8008D678 |= 0x1000;
            return;
        }
        unknownFlags_8008D678 &= ~0x1000;
    }
}
long cdRomEventErrorHandler_8003BBAC(void)
{
    unknownFlags_8008D678 |= 0x100u;
    printf(aAssertionFaile_1, aCdC, 79);
    exit(1);
}
void InitFileRequestQueue_8003BBE4(void)
{
    int freeId = 0x10000;
    int i;
    fileRequestQueue_80086540 = 0;
    ((int*)&fileRequestQueue_80086540)[1] = 0;
    ((int*)&fileRequestQueue_80086540)[2] = 0;
    ((int*)&fileRequestQueue_80086540)[3] = 0;
    for (i = 0x13; i >= 0; i--)
    {
        fileRequests_80095C90[i].fileId_10 = freeId;
    }
    fileBufferInUse_80086564 = 0;
    cdXaLock_80086568 = 0;
}
int GetFileRequestCount_8003BC34(void)
{
    return fileRequestQueue_80086540;
}
int FindFreeFileRequest_8003BC44(void)
{
    int i;
    for (i = 0; i < 0x14; i++)
    {
        if (fileRequests_80095C90[i].fileId_10 == 0x10000)
        {
            return i;
        }
    }
    return -1;
}
typedef struct
{
    int count;
    int nextkey;
    FileRequest* first;
    FileRequest* last;
} FileRequestQueue;
int QueueFileRequest_8003BC84(FileRequestDesc* req)
{
    FileRequestQueue* head = (FileRequestQueue*)&fileRequestQueue_80086540;
    int i = FindFreeFileRequest_8003BC44();
    FileRequest* node = (FileRequest*)&fileRequests_80095C90[i];
    FileRequest* prev;
    FileRequest* after;
    node->next = 0;
    node->newer_4 = 0;
    node->key = head->nextkey;
    node->flags_C = req->flags_0;
    node->fileId_10 = req->fileId_4;
    node->offset_14 = req->offset_8;
    node->size_18 = req->size_C;
    node->dest_1C = req->dest_10;
    node->callback_24 = req->callback_1C;
    if (req->paramsSize_18 == 0 || req->params_14 == 0)
    {
        node->params_20 = 0;
    }
    else
    {
        node->params_20 = fileRequestParams_800954C0[i];
        MemCopy_800403E8(node->params_20, req->params_14, req->paramsSize_18);
    }
    if (head->count == 0)
    {
        head->first = node;
    }
    else
    {
        prev = head->last;
        if (prev->flags_C & 0x10)
        {
            do
            {
                prev = prev->next;
                after = prev->next;
            } while (after->flags_C & 0x10);
            node->next = after;
            node->newer_4 = (int)prev;
            prev->next = node;
        }
        else
        {
            node->next = prev;
            (head->last)->newer_4 = (int)node;
        }
    }
    head->last = node;
    head->count++;
    head->nextkey++;
    return node->key;
}
void EmptyCallback_8003BE28(void)
{
}
int GetFileRequestStatus_8003BE30(int key)
{
    FileRequest* node = FindFileRequest_8003BED4(key);
    if (node)
    {
        if (node->flags_C & 0x100)
        {
            if (node->flags_C & 0x1000)
            {
                return 3;
            }
            return 2;
        }
        return 1;
    }
    return 0;
}
int CancelFileRequest_8003BE88(int key)
{
    FileRequest* node = FindFileRequest_8003BED4(key);
    if (node && !(node->flags_C & 0x100))
    {
        RemoveFileRequest_8003BF18(node);
        return 1;
    }
    return 0;
}
FileRequest* FindFileRequest_8003BED4(int key)
{
    FileRequest* node;
    for (node = fileRequestTail_8008654C; node; node = node->next)
    {
        if (key == node->key)
        {
            return node;
        }
    }
    return 0;
}
void RemoveFileRequest_8003BF18(FileRequest* req)
{
    // req->next (offset 0) is the previous node, req->newer_4 the next one
    FileRequestQueue* list = (FileRequestQueue*)&fileRequestQueue_80086540;
    if (req->next == 0)
    {
        list->first = (FileRequest*)req->newer_4;
    }
    else
    {
        req->next->newer_4 = req->newer_4;
    }
    if (req->newer_4 == 0)
    {
        list->last = req->next;
    }
    else
    {
        ((FileRequest*)req->newer_4)->next = req->next;
    }
    req->fileId_10 = 0x10000;
    list->count--;
}
int IsFileRequestQueueIdle_8003BF88(void)
{
    if (fileRequestQueue_80086540 == 0 && fileBufferInUse_80086564 == 0)
    {
        return 1;
    }
    return 0;
}
void* SetFileBufferInUse_8003BFB8(int inUse)
{
    fileBufferInUse_80086564 = inUse;
    return fileBuffer_8008656C;
}
int ConsumeFileRequest_8003BFD0(int key, int flag)
{
    FileRequest* node = FindFileRequest_8003BED4(key);
    if (node)
    {
        unsigned int flags = node->flags_C;
        if (flags & 0x1000)
        {
            void (*cb)(void*, void*) = node->callback_24;
            node->flags_C = flags | 0x2000;
            if (cb)
            {
                cb(node->params_20, node->dest_1C);
                node->callback_24 = 0;
                return 0;
            }
            return 2;
        }
        if (flag)
        {
            node->flags_C = flags | 0x2000;
            return 1;
        }
    }
    return 2;
}
int CancelFileRequest_8003C060(int key)
{
    FileRequest* node = FindFileRequest_8003BED4(key);
    if (node)
    {
        node->callback_24 = 0;
        node->flags_C |= 0x2000;
        return 0;
    }
    return 2;
}
int SetCdXaLock_8003C0A4(int lock)
{
    FileTask* task = fileRequestTask_8008B544->entry.buffer;
    if (cdXaLock_80086568 != lock)
    {
        if (lock == 1)
        {
            FileRequest* cur = task->cur;
            if (cur == 0 || (task->state == 8 && (cur->flags_C & 0x1000)))
            {
                cdXaLock_80086568 = lock;
            }
        }
        else
        {
            cdXaLock_80086568 = 0;
        }
        return cdXaLock_80086568 == lock;
    }
    return 0;
}
void InitFileRequestTask_8003C128(int* entry, FileTask* task)
{
    InitFileRequestQueue_8003BBE4();
    fileBuffer_8008656C = (void*)0x801B9250;
    task->cur = 0;
    task->state = 0;
    task->buf = 0;
    task->retry = 0;
    entry[2] = (int)ProcessFileRequests_8003C184;
}
extern FileRequest* fileRequestHead_80086548;
void ProcessFileRequests_8003C184(int* entry, FileTask* task)
{
    int loop;
    FileRequest* req;

    if (fileBufferInUse_80086564 != 0 || cdXaLock_80086568 != 0)
    {
        return;
    }
    loop = 1;
    if (task->cur == 0)
    {
        task->state = 0;
        task->cur = fileRequestHead_80086548;
    }
    while (loop)
    {
        if (task->cur == 0)
        {
            break;
        }
        switch (task->state)
        {
        case 0:
            task->cur->flags_C |= 0x100;
            if (task->cur->flags_C & 4)
            {
                if (task->retry < 2)
                {
                    task->retry++;
                    primBufferOffset_8008B550 = 0x3D000;
                    unknownFlags_8008D678 |= 0x200;
                    loop = 0;
                    break;
                }
            }
            task->state = 1;
        case 1:
            DATA_GetFile_8003C7CC(&task->file, task->cur->fileId_10);
            if (task->cur->flags_C & 0x40)
            {
                DsIntToPos(DsPosToInt(&task->file.position_0) + ((unsigned int)task->cur->offset_14 >> 11), &task->file.position_0);
                task->sectors = (unsigned int)task->cur->size_18 >> 11;
            }
            else
            {
                task->sectors = task->file.sectors_4;
            }
            if (task->cur->flags_C & 2)
            {
                task->cur->flags_C |= 1;
            }
            if (task->cur->flags_C & 1)
            {
                if (fileBuffer_8008656C != 0 && !((unsigned int)(task->sectors << 11) > 0x1ADB0))
                {
                    task->cur->flags_C |= 0x200;
                    task->buf = fileBuffer_8008656C;
                }
                else
                {
                    task->buf = malloc3_8003FC4C(task->sectors << 11);
                }
            }
            else
            {
                task->buf = (void*)0x801B9250;
            }
            if (task->cur->flags_C & 0x10)
            {
                task->state = 2;
            }
            else if (task->cur->flags_C & 8)
            {
                task->state = 5;
            }
            else
            {
                task->state = 7;
            }
            break;
        case 2:
            if (CdSeekStart_8003C8A0(&task->file.position_0))
            {
                task->state = 3;
            }
            else
            {
                loop = 0;
            }
            break;
        case 3:
            if (CdSeekIsComplete_8003C900())
            {
                task->state = 10;
            }
            else
            {
                loop = 0;
                if (!(task->cur->flags_C & 0x400) && !(unknownFlags_8008D678 & 0x4000000))
                {
                    DrawLoadingIcon_8003CD5C();
                }
            }
            break;
        case 5:
            if (CdReadStart_8003C944(&task->file.position_0, task->buf, task->sectors))
            {
                task->state = 6;
            }
            else
            {
                loop = 0;
            }
            break;
        case 6:
            if (CdReadIsIdle_8003C9EC())
            {
                if (task->cur->flags_C & 2)
                {
                    MemCopy_800403E8(task->cur->dest_1C, task->buf, DATA_GetFileSize_8003C87C(task->cur->fileId_10));
                }
                task->state = 8;
            }
            else
            {
                loop = 0;
                if (!(task->cur->flags_C & 0x400) && !(unknownFlags_8008D678 & 0x4000000))
                {
                    DrawLoadingIcon_8003CD5C();
                }
            }
            break;
        case 7:
            if (CdReadStart_8003C944(&task->file.position_0, task->buf, task->sectors))
            {
                while (!CdReadIsIdle_8003C9EC())
                {
                }
                task->state = 8;
            }
            else
            {
                loop = 0;
            }
            break;
        case 8:
            if (task->cur->flags_C & 0x800)
            {
                task->cur->flags_C |= 0x1000;
                task->cur->dest_1C = task->buf;
                if (!(task->cur->flags_C & 0x2000))
                {
                    loop = 0;
                    break;
                }
            }
            task->cur->flags_C &= ~0x1000;
            task->state = 9;
            break;
        case 9:
            if (task->cur->callback_24)
            {
                task->cur->callback_24(task->cur->params_20, task->buf);
            }
            if (task->cur->flags_C & 1)
            {
                if (task->buf)
                {
                    if (!(task->cur->flags_C & 0x200))
                    {
                        free3_8003FC6C(task->buf);
                    }
                    task->buf = 0;
                }
            }
            task->state = 10;
        case 10:
            req = (FileRequest*)task->cur->newer_4;
            if ((req == 0 || !(req->flags_C & 4)) && task->retry != 0)
            {
                loop = 0;
                task->retry--;
                primBufferOffset_8008B550 = 0;
                unknownFlags_8008D678 &= ~0x200;
                break;
            }
            req = task->cur;
            task->cur = (FileRequest*)req->newer_4;
            RemoveFileRequest_8003BF18(req);
            task->state = 0;
            break;
        }
    }
}
void AssertFileRequestQueueEmpty_8003C684(void)
{
    if (fileRequestQueue_80086540)
    {
        printf(aAssertionFaile_1, aCdC, 878);
        exit(1);
    }
}

int fileRequestQueue_80086540 = 0;
int fileRequestNextKey_80086544 = 0;
FileRequest *fileRequestHead_80086548 = 0;
FileRequest *fileRequestTail_8008654C = 0;
