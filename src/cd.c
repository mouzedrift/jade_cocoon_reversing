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

extern int dword_80086568;
extern void RemoveFileRequest_8003BF18(FileRequest* n);


INCLUDE_DATA(aDataData0011);
INCLUDE_DATA(aAssertionFaile_1);
INCLUDE_DATA(aCdC);

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
    sub_80020EE0(dword_80095468);
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
void sub_80039FE4(int a0, int a1, int a2)
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
INCLUDE_ASM(sub_8003A6C4);
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
// Not matched: s1/s2 register assignment of out/len swapped (8 words)
int VectorToAngles_8003B5D4(int* v, short* out)
{
    int len;
    int a;
    int x;
    int z;
    len = ISqrt_8003B918(((int (*)(int*))LengthSquared3D_8003B8DC)(v));
    out[1] = ratan2(v[0], v[2]);
    x = v[0];
    z = v[2];
    a = (short)ratan2(v[1], ISqrt_8003B918(LengthSquared2D_8003B8BC(x, z)));
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
#if 0
// Not matched (33 words): register assignment of the abs() temporaries
int IsWithinDistance_8003B740(int* a, int* b, unsigned int* c)
{
    int sum = -1;
    int ok = 0;
    unsigned int r = *c;
    int t;
    int dx;
    int dy;
    int dz;
    t = a[0] - b[0];
    dx = t;
    if (t < 0)
    {
        dx = -dx;
    }
    if (r >= (unsigned int)dx)
    {
        t = a[1] - b[1];
        dy = t;
        if (t < 0)
        {
            dy = -dy;
        }
        if (r >= (unsigned int)dy)
        {
            t = a[2] - b[2];
            dz = t;
            if (t < 0)
            {
                dz = -dz;
            }
            if (r >= (unsigned int)dz)
            {
                sum = dx * dx + dy * dy + dz * dz;
                ok = !(r * r < (unsigned int)sum);
            }
        }
    }
    *c = sum;
    return ok;
}

#endif
INCLUDE_ASM(IsWithinDistance_8003B740);
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
int LengthSquared3D_8003B8DC(int* p, int a1)
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
int sub_8003BADC(int a0)
{
    int out[2];
    McxAllInfo(a0, (unsigned char*)&dword_8008D4D8);
    while (!McxSync(0, (long*)&out[0], (long*)&out[1]))
    {
    }
    return out[1];
}
// Matched
void sub_8003BB1C(void)
{
    int i;
    int r;
    for (i = 0; i < 2; i++)
    {
        r = sub_8003BADC(i << 4);
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
extern unsigned char fileRequestParams_800954C0[][0x64];
typedef struct
{
    int count;
    int nextkey;
    FileRequest* first;
    FileRequest* last;
} struct_head_8003BC84;
// Matched
int QueueFileRequest_8003BC84(int* req)
{
    struct_head_8003BC84* head = (struct_head_8003BC84*)&fileRequestQueue_80086540;
    int i = FindFreeFileRequest_8003BC44();
    FileRequest* n = (FileRequest*)&fileRequests_80095C90[i];
    FileRequest* t;
    FileRequest* nx;
    n->next = 0;
    n->field_4 = 0;
    n->key = head->nextkey;
    n->flags_C = req[0];
    n->fileId_10 = req[1];
    ((int*)n)[0x14 / 4] = req[2];
    ((int*)n)[0x18 / 4] = req[3];
    n->dest_1C = req[4];
    n->callback_24 = req[7];
    if (req[6] == 0 || req[5] == 0)
    {
        n->field_20 = 0;
    }
    else
    {
        n->field_20 = (int)fileRequestParams_800954C0[i];
        MemCopy_800403E8((unsigned int*)n->field_20, (unsigned int*)req[5], req[6]);
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
    return (void*)fileBuffer_8008656C;
}
// Matched
int sub_8003BFD0(int key, int flag)
{
    FileRequest* n = FindFileRequest_8003BED4(key);
    if (n)
    {
        unsigned int f = n->flags_C;
        if (f & 0x1000)
        {
            void (*cb)(int, int) = (void (*)(int, int))n->callback_24;
            n->flags_C = f | 0x2000;
            if (cb)
            {
                cb(n->field_20, n->dest_1C);
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
extern int** fileRequestTask_8008B544;
// Matched
int sub_8003C0A4(int a0)
{
    int* p = fileRequestTask_8008B544[0x24 / 4];
    if (dword_80086568 != a0)
    {
        if (a0 == 1)
        {
            int* q = (int*)p[0];
            if (q == 0 || (p[0x1C / 4] == 8 && (q[0xC / 4] & 0x1000)))
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
typedef struct FileTask FileTask;
void ProcessFileRequests_8003C184(int* a0, FileTask* t);
// Matched
void InitFileRequestTask_8003C128(int* a0, int* a1)
{
    InitFileRequestQueue_8003BBE4();
    fileBuffer_8008656C = 0x801B9250;
    a1[0] = 0;
    a1[7] = 0;
    a1[8] = 0;
    a1[10] = 0;
    a0[2] = (int)ProcessFileRequests_8003C184;
}
struct FileTask
{
    FileRequest* cur;
    Data001File file;
    char pad_10[0xC];
    int state;
    int buf;
    int sectors;
    int retry;
};
extern FileRequest* dword_80086548;
extern int CdSeekStart_8003C8A0(DslLOC* loc);
extern int CdReadStart_8003C944(DslLOC* loc, int buf, int sectors);
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
                DsIntToPos(DsPosToInt(&t->file.field_0_position) + ((unsigned int)((int*)t->cur)[0x14 / 4] >> 11), &t->file.field_0_position);
                t->sectors = (unsigned int)((int*)t->cur)[0x18 / 4] >> 11;
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
                    t->buf = (int)malloc3_8003FC4C(t->sectors << 11);
                }
            }
            else
            {
                t->buf = 0x801B9250;
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
                    MemCopy_800403E8((unsigned int*)t->cur->dest_1C, (unsigned int*)t->buf, DATA_GetFileSize_8003C87C(t->cur->fileId_10));
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
                ((void (*)(int, int))t->cur->callback_24)(t->cur->field_20, t->buf);
            }
            if (t->cur->flags_C & 1)
            {
                if (t->buf)
                {
                    if (!(t->cur->flags_C & 0x200))
                    {
                        free3_8003FC6C((void*)t->buf);
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
