#ifndef _CD_H_
#define _CD_H_

extern const char aDataData0011[];
extern const int unused_800748DC;

/* the pending file requests, oldest (processed first) to newest. Four variables on PSX: code reads them both
   through the structure and as plain variables, which the compiler schedules differently */
typedef struct
{
    int count;
    int nextkey;
    FileRequest* first;
    FileRequest* last;
} FileRequestQueue;
#ifdef __psyz
extern FileRequestQueue fileRequestQueue;
#define fileRequestQueue_80086540 (fileRequestQueue.count)
#define fileRequestNextKey_80086544 (fileRequestQueue.nextkey)
#define fileRequestHead_80086548 (fileRequestQueue.first)
#define fileRequestTail_8008654C (fileRequestQueue.last)
#define FILE_REQUEST_QUEUE (&fileRequestQueue)
#else
extern int fileRequestQueue_80086540;
extern int fileRequestNextKey_80086544;
extern FileRequest* fileRequestHead_80086548;
extern FileRequest* fileRequestTail_8008654C;
#define FILE_REQUEST_QUEUE ((FileRequestQueue*)&fileRequestQueue_80086540)
#endif

/* the file request task's buffer (fileRequestTask_8008B544) */
typedef struct FileTask
{
    FileRequest* cur;
    Data001File file;
    char pad_10[0xC];
    int state;
    void* buf;
    int sectors;
    int retry;
} FileTask;

void InitFileRequestTask_8003C128(EventEntry* entry, FileTask* task);

unsigned int DistanceSquaredXZ_8003B860(int* a, int* b);
int DistanceSquared3D_8003B80C(int* a, int* b);
void RemoveFileRequest_8003BF18(FileRequest* req);
void ProcessFileRequests_8003C184(EventEntry* entry, FileTask* task);
int QueueFileRequest_8003BC84(FileRequestDesc* req);
int SetCdXaLock_8003C0A4(int lock);
int GetCapturedMinionsFromBitfield_8003BA58(int bits);
long cdRomEventErrorHandler_8003BBAC(void);
void FreeStageEffects_80039FC0(void);
int GetFileRequestStatus_8003BE30(int key);
void* SetFileBufferInUse_8003BFB8(int inUse);
void SetBattleStageId_80039FA4(int id);
int GetBattleStageId_80039FB0(void);
int GetFileRequestCount_8003BC34(void);
int Sign_8003B664(int x);
int LengthSquared2D_8003B8BC(int x, int y);
short ratan2_8003B548(long y, long x);
int IsFileRequestQueueIdle_8003BF88(void);
int LengthSquared3D_8003B8DC(int* v);
int FindFreeFileRequest_8003BC44(void);
void EmptyCallback_8003BE28(void);
short ratan2Difference_8003B9E0(int* a, int* b);
short WrapAngle_8003BA18(int angle);
int CompareUInt_8003BA38(unsigned int a, unsigned int b);
unsigned int ISqrt_8003B918(unsigned int value);
FileRequest* FindFileRequest_8003BED4(int key);
int CancelFileRequest_8003C060(int key);
void AssertFileRequestQueueEmpty_8003C684(void);
void DiffFtgObjects_80039FE4(struct FtgObject* a, struct FtgObject* b, struct FtgObject* out);
void LerpFtgObject_8003A6C4(int t, struct FtgObject* out, struct FtgObject* a, struct FtgObject* d);
int ConsumeFileRequest_8003BFD0(int key, int flag);
Vec3i* Midpoint3D_8003B95C(Vec3i* out, Vec3i* a, Vec3i* b);
int VectorToAngles_8003B5D4(int* v, short* out);
int ratan2Degrees_8003B56C(int x, int y);
int IsWithinDistance_8003B740(int* a, int* b, unsigned int* dist);
void CheckMemCards_8003BB1C(void);
#endif
