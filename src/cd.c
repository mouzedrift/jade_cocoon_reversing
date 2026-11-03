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

extern void sub_80070E30(int a, int* b);
extern int sub_8006F0E0(int a, int* b, int* c);

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
INCLUDE_ASM(sub_80039FE4);
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
// Not matched (8 words): s1/s2 register assignment swapped
int VectorToAngles_8003B5D4(int* v, short* out)
{
    int len = ISqrt_8003B918(((int (*)(int*))LengthSquared3D_8003B8DC)(v));
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
#if 0
// Not matched (33 words): register assignment of the abs() temporaries
int sub_8003B740(int* a, int* b, unsigned int* c)
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
INCLUDE_ASM(sub_8003B740);
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
    sub_80070E30(a0, &dword_8008D4D8);
    while (!sub_8006F0E0(0, &out[0], &out[1]))
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
#if 0
// Not matched (6 words): load of list[0] scheduled before the field_10 store
void RemoveFileRequest_8003BF18(FileRequest* n)
{
    // n->next (offset 0) is the previous node, n->field_4 the next one
    int* list = &fileRequestQueue_80086540;
    if (n->next == 0)
    {
        list[2] = n->field_4;
    }
    else
    {
        n->next->field_4 = n->field_4;
    }
    if (n->field_4 == 0)
    {
        list[3] = (int)n->next;
    }
    else
    {
        ((FileRequest*)n->field_4)->next = n->next;
    }
    n->fileId_10 = 0x10000;
    list[0]--;
}

#endif
INCLUDE_ASM(RemoveFileRequest_8003BF18);
// Matched
int IsFileRequestQueueIdle_8003BF88(void)
{
    if (fileRequestQueue_80086540 == 0 && fileBufferInUse_80086564 == 0)
    {
        return 1;
    }
    return 0;
}
// Not matched: no jr after the store, execution falls through into GetFileBuffer_8003BFC0
#if 0
void SetFileBufferInUse_8003BFB8(int arg0)
{
    fileBufferInUse_80086564 = arg0;
}
#endif
INCLUDE_ASM(SetFileBufferInUse_8003BFB8);
// Matched
int GetFileBuffer_8003BFC0(void)
{
    return fileBuffer_8008656C;
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
extern int** dword_8008B544;
// Matched
int sub_8003C0A4(int a0)
{
    int* p = dword_8008B544[0x24 / 4];
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
extern void ProcessFileRequests_8003C184(void);
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
INCLUDE_ASM(ProcessFileRequests_8003C184);
// Matched
void AssertFileRequestQueueEmpty_8003C684(void)
{
    if (fileRequestQueue_80086540)
    {
        printf(aAssertionFaile_1, aCdC, 878);
        exit(1);
    }
}
