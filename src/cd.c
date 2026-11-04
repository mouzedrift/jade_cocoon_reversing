#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "tu_8001EA48.h"
#include "tu_8003C6C8.h"
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
#include "cd.h"
#include "tu_8003C6C8.h"
#include "main.h"
#include "gte.h"

extern void RemoveFileRequest_8003BF18(FileRequest* n);

const char aDataData0011[] = "\\DATA\\DATA.001;1";
const char aAssertionFaile_1[] = "Assertion failed: file \"%s\", line %d\n";
const char aCdC[] = "CD.C";
const int dword_800748DC = 0;

// Matched
void sub_80039FA4(int a0)
{
    dword_80083BD0 = a0;
}
// Matched
int sub_80039FB0(void)
{
    return dword_80083BD0;
}
// Matched
void sub_80039FC0(void)
{
    FreeEffectFile_80020EE0(&dword_80095468);
}
typedef struct
{
    short n;
    short pad;
    char* p;
} PolyGroup;
typedef struct
{
    PolyGroup g[8];
    int n8;
    char* p8;
    int n9;
    int field_4C;
    char* p9;
} PolyGroups;
typedef struct
{
    char pad[4];
    SVECTOR a;
    SVECTOR b;
} EdgeDelta;

#define DIFF_GROUP(k, size, off, nv)                                              \
    if (pb->g[k].n * nv)                                                          \
    {                                                                             \
        int j;                                                                    \
        for (i = 0; i < pb->g[k].n; i++)                                          \
        {                                                                         \
            SVECTOR* vo = (SVECTOR*)(po->g[k].p + i * size + off);                \
            SVECTOR* vb = (SVECTOR*)(pb->g[k].p + i * size + off);                \
            SVECTOR* va = (SVECTOR*)(pa->g[k].p + i * size + off);                \
            for (j = 0; j < nv; j++)                                              \
            {                                                                     \
                vo[j].vx = va[j].vx - vb[j].vx;                                   \
                vo[j].vy = va[j].vy - vb[j].vy;                                   \
                vo[j].vz = va[j].vz - vb[j].vz;                                   \
            }                                                                     \
        }                                                                         \
    }

// Matched
void sub_80039FE4(struct FtgObject* a0, struct FtgObject* a1, struct FtgObject* a2)
{
    PolyGroups* pa = (PolyGroups*)a0;
    PolyGroups* pb = (PolyGroups*)a1;
    PolyGroups* po = (PolyGroups*)a2;
    int i;

    DIFF_GROUP(0, 0x24, 4, 4);
    DIFF_GROUP(1, 0x3C, 0xC, 6);
    DIFF_GROUP(2, 0x30, 0x10, 4);
    DIFF_GROUP(3, 0x48, 0x18, 6);
    DIFF_GROUP(4, 0x2C, 4, 5);
    DIFF_GROUP(5, 0x50, 0x10, 8);
    DIFF_GROUP(6, 0x38, 0x10, 5);
    DIFF_GROUP(7, 0x5C, 0x1C, 8);
    if (pa->n8)
    {
        EdgeDelta* ea;
        EdgeDelta* eb;
        EdgeDelta* eo;
        ea = (EdgeDelta*)pa->p8;
        eb = (EdgeDelta*)pb->p8;
        eo = (EdgeDelta*)po->p8;
        for (i = 0; i < pa->n8; i++)
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
    if (pa->n9)
    {
        EdgeDelta* ea;
        EdgeDelta* eb;
        EdgeDelta* eo;
        ea = (EdgeDelta*)pa->p9;
        eb = (EdgeDelta*)pb->p9;
        eo = (EdgeDelta*)po->p9;
        for (i = 0; i < pa->n9; i++)
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
#if 0
// Not matched: size and code right; per group the scheduler orders the three item-pointer setups differently (vo/va/vd: a1,a3,a2 vs a1,a2,a3) and swaps the j / vo-giv registers
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
    if (pa->g[k].n * (nn + nv))                                                   \
    {                                                                             \
        int i;                                                                    \
        int j;                                                                    \
        for (i = 0; i < pa->g[k].n; i++)                                          \
        {                                                                         \
            SVECTOR* vo = (SVECTOR*)(po->g[k].p + i * size + off);                \
            SVECTOR* va = (SVECTOR*)(pa->g[k].p + i * size + off);                \
            SVECTOR* vd = (SVECTOR*)(pd->g[k].p + i * size + off);                \
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

    LERP_GROUP(0, 0x24, 4, 1, 3);
    LERP_GROUP(1, 0x3C, 0xC, 3, 3);
    LERP_GROUP(2, 0x30, 0x10, 1, 3);
    LERP_GROUP(3, 0x48, 0x18, 3, 3);
    LERP_GROUP(4, 0x2C, 4, 1, 4);
    LERP_GROUP(5, 0x50, 0x10, 4, 4);
    LERP_GROUP(6, 0x38, 0x10, 1, 4);
    LERP_GROUP(7, 0x5C, 0x1C, 4, 4);
    if (po->n8)
    {
        EdgeDelta* eo = (EdgeDelta*)po->p8;
        EdgeDelta* ea = (EdgeDelta*)pa->p8;
        EdgeDelta* ed = (EdgeDelta*)pd->p8;
        int i;
        for (i = 0; i < po->n8; i++, eo++, ea++, ed++)
        {
            LERP_SV(&eo->a, &ea->a, &ed->a, t);
            LERP_SV(&eo->b, &ea->b, &ed->b, t);
        }
    }
    if (po->n9)
    {
        EdgeDelta* eo = (EdgeDelta*)po->p9;
        EdgeDelta* ea = (EdgeDelta*)pa->p9;
        EdgeDelta* ed = (EdgeDelta*)pd->p9;
        int i;
        for (i = 0; i < po->n9; i++, eo++, ea++, ed++)
        {
            LERP_SV(&eo->a, &ea->a, &ed->a, t);
            LERP_SV(&eo->b, &ea->b, &ed->b, t);
        }
    }
}
#endif
INCLUDE_ASM(LerpFtgObject_8003A6C4);
// Matched
short ratan2_8003B548(long y, long x)
{
    return ratan2(y, x);
}
// Matched
int ratan2Degrees_8003B56C(int x, int y)
{
    int r = ratan2(y, x);
    int d;
    if (r < 0)
    {
        r += 0x1000;
    }
    d = r * 360 / 4096;
    if ((unsigned int)d >= 360)
    {
        d = 0;
    }
    return d;
}
#if 0
// Not matched: s1/s2 register assignment of out/len swapped (8 words). Also tried: declaration order, unsigned len, direct out[] stores, short a (loses the sext), copy pointer o = out, passing out as the 3D call's 2nd arg, b/a reuse; permuter 1500: nothing
int VectorToAngles_8003B5D4(int* v, short* out)
{
    int len = ISqrt_8003B918(LengthSquared3D_8003B8DC(v));
    short b;
    int a;
    b = ratan2(v[0], v[2]);
    out[1] = b;
    a = (short)ratan2(v[1], ISqrt_8003B918(LengthSquared2D_8003B8BC(v[0], v[2])));
    out[0] = -a;
    out[2] = 0;
    return len;
}
#endif
INCLUDE_ASM(VectorToAngles_8003B5D4);
// Matched
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
// Matched
void sub_8003B684(int* v)
{
    int m = 0x20;
    int t = Lzc(v[0]);
    if (t < m)
    {
        m = t;
    }
    t = Lzc(v[1]);
    if (t < m)
    {
        m = t;
    }
    t = Lzc(v[2]);
    if (t < m)
    {
        m = t;
    }
    if (m < 0x12)
    {
        int sh = 0x12 - m;
        v[0] >>= sh;
        v[1] >>= sh;
        v[2] >>= sh;
    }
}
// Matched
int IsWithinDistance_8003B740(int* a, int* b, unsigned int* c)
{
    unsigned int sum = -1;
    unsigned int r = *c;
    short ok = 0;
    unsigned int dx = abs(a[0] - b[0]);
    if (dx <= r)
    {
        unsigned int dy = abs(a[1] - b[1]);
        if (dy <= r)
        {
            unsigned int dz = abs(a[2] - b[2]);
            if (dz <= r)
            {
                unsigned int rr;
                sum = dx * dx + dy * dy + dz * dz;
                rr = r * r;
                ok = !(rr < sum);
            }
        }
    }
    *c = sum;
    return ok;
}
// Matched
int DistanceSquared3D_8003B80C(int* a, int* b)
{
    int dx = a[0] - b[0];
    int dy = a[1] - b[1];
    int dz = a[2] - b[2];
    return dx * dx + dy * dy + dz * dz;
}
// Matched
int DistanceSquaredXZ_8003B860(int* a, int* b)
{
    int dx = a[0] - b[0];
    int dz = a[2] - b[2];
    return dx * dx + dz * dz;
}
// Matched
int DistanceSquared2D_8003B898(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    return dx * dx + dy * dy;
}
// Matched
int LengthSquared2D_8003B8BC(int x, int y)
{
    return x * x + y * y;
}
// Matched
int LengthSquared3D_8003B8DC(int* p)
{
    return p[0] * p[0] + p[1] * p[1] + p[2] * p[2];
}
// Not matched: C is right but ASPSX expands divu with a divide-by-zero check (3 extra insts); original has a bare divu
// Not matched: C is right but ASPSX expands divu with a divide-by-zero check (3 extra insts); original has a bare divu
// Matched
unsigned int ISqrt_8003B918(unsigned int n)
{
    int x;
    int y;
    if (n != 0)
    {
        x = 1;
        if (n >= 2)
        {
            x = n;
        }
        do
        {
            y = x;
            x = (n / y + y) >> 1;
        } while (x < y);
        return y;
    }
    return 0;
}
// Matched
Vec3i* Midpoint3D_8003B95C(Vec3i* out, Vec3i* a, Vec3i* b)
{
    Vec3i t;
    t.x = (a->x + b->x) / 2;
    t.y = (a->y + b->y) / 2;
    t.z = (a->z + b->z) / 2;
    *out = t;
    return out;
}
// Matched
short ratan2Difference_8003B9E0(int* a, int* b)
{
    return ratan2(b[0] - a[0], b[2] - a[2]);
}
// Matched
short WrapAngle_8003BA18(int v)
{
    short r = v & 0xFFF;
    if (r >= 0x800)
    {
        r |= 0xF000;
    }
    return r;
}
// Matched
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
// Matched
int GetCapturedMinionsFromBitfield_8003BA58(int arg0)
{
    int result;
    int var_v0;
    int i;

    result = 0;
    for (i = 0; i < 32; i++)
    {
        var_v0 = 1 << i;
        if (arg0 & var_v0)
        {
            result += 1;
        }
    }
    return result;
}
// Matched
void DelayLoop_8003BA90(void)
{
    float f = 0;
    while (f < 621.0f)
    {
        f += 1.0f;
    }
}
// Matched
int GetMemCardInfoSync_8003BADC(int a0)
{
    int out[2];
    McxAllInfo(a0, (unsigned char*)&memCardInfo_8008D4D8);
    while (!McxSync(0, (long*)&out[0], (long*)&out[1]))
    {
    }
    return out[1];
}
// Matched
void CheckMemCards_8003BB1C(void)
{
    int i;
    int r;
    for (i = 0; i < 2; i++)
    {
        r = GetMemCardInfoSync_8003BADC(i << 4);
        if (r == 0 || r == 3)
        {
            unknownFlags_8008D678 |= 0x1000;
            return;
        }
        unknownFlags_8008D678 &= ~0x1000;
    }
}
// Matched
long cdRomEventErrorHandler_8003BBAC(void)
{
    unknownFlags_8008D678 |= 0x100u;
    printf(aAssertionFaile_1, aCdC, 79);
    exit(1);
}
// Matched
void InitFileRequestQueue_8003BBE4(void)
{
    int v = 0x10000;
    int i;
    fileRequestQueue_80086540 = 0;
    ((int*)&fileRequestQueue_80086540)[1] = 0;
    ((int*)&fileRequestQueue_80086540)[2] = 0;
    ((int*)&fileRequestQueue_80086540)[3] = 0;
    for (i = 0x13; i >= 0; i--)
    {
        fileRequests_80095C90[i].fileId_10 = v;
    }
    fileBufferInUse_80086564 = 0;
    dword_80086568 = 0;
}
// Matched
int GetFileRequestCount_8003BC34(void)
{
    return fileRequestQueue_80086540;
}
// Matched
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
} struct_head_8003BC84;
// Matched
int QueueFileRequest_8003BC84(FileRequestDesc* req)
{
    struct_head_8003BC84* head = (struct_head_8003BC84*)&fileRequestQueue_80086540;
    int i = FindFreeFileRequest_8003BC44();
    FileRequest* n = (FileRequest*)&fileRequests_80095C90[i];
    FileRequest* t;
    FileRequest* nx;
    n->next = 0;
    n->field_4 = 0;
    n->key = head->nextkey;
    n->flags_C = req->flags_0;
    n->fileId_10 = req->fileId_4;
    n->offset_14 = req->offset_8;
    n->size_18 = req->size_C;
    n->dest_1C = req->dest_10;
    n->callback_24 = req->callback_1C;
    if (req->paramsSize_18 == 0 || req->params_14 == 0)
    {
        n->params_20 = 0;
    }
    else
    {
        n->params_20 = fileRequestParams_800954C0[i];
        MemCopy_800403E8(n->params_20, req->params_14, req->paramsSize_18);
    }
    if (head->count == 0)
    {
        head->first = n;
    }
    else
    {
        t = head->last;
        if (t->flags_C & 0x10)
        {
            do
            {
                t = t->next;
                nx = t->next;
            } while (nx->flags_C & 0x10);
            n->next = nx;
            n->field_4 = (int)t;
            t->next = n;
        }
        else
        {
            n->next = t;
            (head->last)->field_4 = (int)n;
        }
    }
    head->last = n;
    head->count++;
    head->nextkey++;
    return n->key;
}
// Matched
void nullsub_6(void)
{
}
// Matched
int GetFileRequestStatus_8003BE30(int arg0)
{
    FileRequest* n = FindFileRequest_8003BED4(arg0);
    if (n)
    {
        if (n->flags_C & 0x100)
        {
            if (n->flags_C & 0x1000)
            {
                return 3;
            }
            return 2;
        }
        return 1;
    }
    return 0;
}
// Matched
int CancelFileRequest_8003BE88(int key)
{
    FileRequest* n = FindFileRequest_8003BED4(key);
    if (n && !(n->flags_C & 0x100))
    {
        RemoveFileRequest_8003BF18(n);
        return 1;
    }
    return 0;
}
// Matched
FileRequest* FindFileRequest_8003BED4(int key)
{
    FileRequest* p;
    for (p = dword_8008654C; p; p = p->next)
    {
        if (key == p->key)
        {
            return p;
        }
    }
    return 0;
}
// Matched
void RemoveFileRequest_8003BF18(FileRequest* n)
{
    // n->next (offset 0) is the previous node, n->field_4 the next one
    struct_head_8003BC84* list = (struct_head_8003BC84*)&fileRequestQueue_80086540;
    if (n->next == 0)
    {
        list->first = (FileRequest*)n->field_4;
    }
    else
    {
        n->next->field_4 = n->field_4;
    }
    if (n->field_4 == 0)
    {
        list->last = n->next;
    }
    else
    {
        ((FileRequest*)n->field_4)->next = n->next;
    }
    n->fileId_10 = 0x10000;
    list->count--;
}
// Matched
int IsFileRequestQueueIdle_8003BF88(void)
{
    if (fileRequestQueue_80086540 == 0 && fileBufferInUse_80086564 == 0)
    {
        return 1;
    }
    return 0;
}
// Matched
void* SetFileBufferInUse_8003BFB8(int arg0)
{
    fileBufferInUse_80086564 = arg0;
    return fileBuffer_8008656C;
}
// Matched
int ConsumeFileRequest_8003BFD0(int key, int flag)
{
    FileRequest* n = FindFileRequest_8003BED4(key);
    if (n)
    {
        unsigned int f = n->flags_C;
        if (f & 0x1000)
        {
            void (*cb)(void*, void*) = n->callback_24;
            n->flags_C = f | 0x2000;
            if (cb)
            {
                cb(n->params_20, n->dest_1C);
                n->callback_24 = 0;
                return 0;
            }
            return 2;
        }
        if (flag)
        {
            n->flags_C = f | 0x2000;
            return 1;
        }
    }
    return 2;
}
// Matched
int CancelFileRequest_8003C060(int key)
{
    FileRequest* n = FindFileRequest_8003BED4(key);
    if (n)
    {
        n->callback_24 = 0;
        n->flags_C |= 0x2000;
        return 0;
    }
    return 2;
}
typedef struct FileTask FileTask;
struct FileTask
{
    FileRequest* cur;
    Data001File file;
    char pad_10[0xC];
    int state;
    void* buf;
    int sectors;
    int retry;
};
// Matched
int sub_8003C0A4(int a0)
{
    FileTask* p = fileRequestTask_8008B544->entry.buffer;
    if (dword_80086568 != a0)
    {
        if (a0 == 1)
        {
            FileRequest* q = p->cur;
            if (q == 0 || (p->state == 8 && (q->flags_C & 0x1000)))
            {
                dword_80086568 = a0;
            }
        }
        else
        {
            dword_80086568 = 0;
        }
        return dword_80086568 == a0;
    }
    return 0;
}
void ProcessFileRequests_8003C184(int* a0, FileTask* t);
// Matched
void InitFileRequestTask_8003C128(int* a0, FileTask* a1)
{
    InitFileRequestQueue_8003BBE4();
    fileBuffer_8008656C = (void*)0x801B9250;
    a1->cur = 0;
    a1->state = 0;
    a1->buf = 0;
    a1->retry = 0;
    a0[2] = (int)ProcessFileRequests_8003C184;
}
extern FileRequest* dword_80086548;
// Matched
void ProcessFileRequests_8003C184(int* a0, FileTask* t)
{
    int loop;
    FileRequest* r;

    if (fileBufferInUse_80086564 != 0 || dword_80086568 != 0)
    {
        return;
    }
    loop = 1;
    if (t->cur == 0)
    {
        t->state = 0;
        t->cur = dword_80086548;
    }
    while (loop)
    {
        if (t->cur == 0)
        {
            break;
        }
        switch (t->state)
        {
        case 0:
            t->cur->flags_C |= 0x100;
            if (t->cur->flags_C & 4)
            {
                if (t->retry < 2)
                {
                    t->retry++;
                    dword_8008B550 = 0x3D000;
                    unknownFlags_8008D678 |= 0x200;
                    loop = 0;
                    break;
                }
            }
            t->state = 1;
        case 1:
            DATA_GetFile_8003C7CC(&t->file, t->cur->fileId_10);
            if (t->cur->flags_C & 0x40)
            {
                DsIntToPos(DsPosToInt(&t->file.field_0_position) + ((unsigned int)t->cur->offset_14 >> 11), &t->file.field_0_position);
                t->sectors = (unsigned int)t->cur->size_18 >> 11;
            }
            else
            {
                t->sectors = t->file.field_4_sectors;
            }
            if (t->cur->flags_C & 2)
            {
                t->cur->flags_C |= 1;
            }
            if (t->cur->flags_C & 1)
            {
                if (fileBuffer_8008656C != 0 && !((unsigned int)(t->sectors << 11) > 0x1ADB0))
                {
                    t->cur->flags_C |= 0x200;
                    t->buf = fileBuffer_8008656C;
                }
                else
                {
                    t->buf = malloc3_8003FC4C(t->sectors << 11);
                }
            }
            else
            {
                t->buf = (void*)0x801B9250;
            }
            if (t->cur->flags_C & 0x10)
            {
                t->state = 2;
            }
            else if (t->cur->flags_C & 8)
            {
                t->state = 5;
            }
            else
            {
                t->state = 7;
            }
            break;
        case 2:
            if (CdSeekStart_8003C8A0(&t->file.field_0_position))
            {
                t->state = 3;
            }
            else
            {
                loop = 0;
            }
            break;
        case 3:
            if (CdSeekIsComplete_8003C900())
            {
                t->state = 10;
            }
            else
            {
                goto wait;
            }
            break;
        case 5:
            if (CdReadStart_8003C944(&t->file.field_0_position, t->buf, t->sectors))
            {
                t->state = 6;
            }
            else
            {
                loop = 0;
            }
            break;
        case 6:
            if (CdReadIsIdle_8003C9EC())
            {
                if (t->cur->flags_C & 2)
                {
                    MemCopy_800403E8(t->cur->dest_1C, t->buf, DATA_GetFileSize_8003C87C(t->cur->fileId_10));
                }
                t->state = 8;
            }
            else
            {
            wait:
                loop = 0;
                if (!(t->cur->flags_C & 0x400) && !(unknownFlags_8008D678 & 0x4000000))
                {
                    DrawLoadingIcon_8003CD5C();
                }
            }
            break;
        case 7:
            if (CdReadStart_8003C944(&t->file.field_0_position, t->buf, t->sectors))
            {
                while (!CdReadIsIdle_8003C9EC())
                {
                }
                t->state = 8;
            }
            else
            {
                loop = 0;
            }
            break;
        case 8:
            if (t->cur->flags_C & 0x800)
            {
                t->cur->flags_C |= 0x1000;
                t->cur->dest_1C = t->buf;
                if (!(t->cur->flags_C & 0x2000))
                {
                    loop = 0;
                    break;
                }
            }
            t->cur->flags_C &= ~0x1000;
            t->state = 9;
            break;
        case 9:
            if (t->cur->callback_24)
            {
                t->cur->callback_24(t->cur->params_20, t->buf);
            }
            if (t->cur->flags_C & 1)
            {
                if (t->buf)
                {
                    if (!(t->cur->flags_C & 0x200))
                    {
                        free3_8003FC6C(t->buf);
                    }
                    t->buf = 0;
                }
            }
            t->state = 10;
        case 10:
            r = (FileRequest*)t->cur->field_4;
            if ((r == 0 || !(r->flags_C & 4)) && t->retry != 0)
            {
                loop = 0;
                t->retry--;
                dword_8008B550 = 0;
                unknownFlags_8008D678 &= ~0x200;
                break;
            }
            r = t->cur;
            t->cur = (FileRequest*)r->field_4;
            RemoveFileRequest_8003BF18(r);
            t->state = 0;
            break;
        }
    }
}
// Matched
void AssertFileRequestQueueEmpty_8003C684(void)
{
    if (fileRequestQueue_80086540)
    {
        printf(aAssertionFaile_1, aCdC, 878);
        exit(1);
    }
}

int fileRequestQueue_80086540 = 0;
int dword_80086544 = 0;
FileRequest *dword_80086548 = 0;
FileRequest *dword_8008654C = 0;
