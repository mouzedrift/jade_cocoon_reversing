#ifndef EVENT_H
#define EVENT_H

/* how a window is drawn (DrawWindow_80042460) */
typedef struct WindowStyle
{
    short color_0;             // GetWindowColors_8004226C colour index
    unsigned char colorSet_2;  // GetWindowColors_8004226C colour set
    unsigned char semiTrans_3; // DrawWindowFrame_80041ED0: 0 opaque, n: abr n - 1
} WindowStyle;

/* the buffer of the XA streaming task (xaTask_8008B560->entry.buffer) */
typedef struct XaTask
{
    int flags_0; // bit 0: stop requested
    int cmd_4;   // DsCommand / DsControlF id to DsSync on
    short state_8; // 0 idle, 2 playing
    short vol_A;   // fade-out volume
} XaTask;

extern unsigned char windowBgColor0_80086FEC;
extern unsigned char unused_80086FED;
extern unsigned char unused_80086FEE;
extern unsigned char unused_80086FEF;
extern int windowBgColorData_80086FF0[9];
extern int windowPulseColorData_80087014[5];
extern void *windowColorsAlt_8008703C[5];
extern int windowFrameQuadEdges_80087070[][8];
extern int unused_80087110;
extern MATRIX lightMatrix_80087114;
extern MATRIX colorMatrix_80087134;

extern int unused_8009611C;

/* the task buffers are sized for the PSX structures: twice that on PC, where pointers are 8 bytes */
#ifdef __psyz
#define TASK_BUFFER_SIZE(size) ((size) * 2)
#else
#define TASK_BUFFER_SIZE(size) (size)
#endif

/* how CreateEventList_800435B4 makes an event list (eventDescs_80078EB8) */
typedef struct
{
    unsigned int count;
    unsigned int flags;
    int size;
    EventNode** out;
    EventEntryFn cb_8;
    EventEntryFn cb_C;
} EventDesc;

void XaInitTask_80043054();

EventNode* CreateEventList_800435B4(EventDesc** list);
void RunEventList_80043898(EventNode* node);
void RunEventListFreeCallbacks_800438F8(EventNode* node);
int FreeEventList_80043A5C(EventNode* head);
void GetWindowColors_8004226C(int colorSet, unsigned char* out, int time, int colorIdx);
void DrawLine_80042870(DVECTOR* from, DVECTOR* to, unsigned char* rgb, void* ot);
int XaStartRead_800434C4(int pos);
void XaIdleTask_800430E8(EventEntry* entry, XaTask* buffer);
void XaMonitorTask_800432EC(EventEntry* entry, XaTask* task);
void XaSetup_800433FC(XaTask* task);
unsigned int XaNoRequestPending_800435A4(void);
void XaRequestPlay_80043564(short channel, short startSector, short length);
int XaIsIdle_80043584(void);
void DrawWindowBackground_800429F8(RECT* rect, int ot);
void DrawWindowBorder_80042B38(RECT* rect, int ot);
void XaStop_800430B0(void);
void XaStartReadTask_80043204(EventEntry* entry, XaTask* task);
void XaWaitFilterTask_800431C4(EventEntry* entry, XaTask* task);
void DrawWindow_80042460(RECT* rect, WindowStyle* style, u_long* ot, int time);
int IsWindowFrameFit_800429A8(RECT* rect);
void DrawUiColorWindow_800424C0(RECT* rect, short colorSet, u_long* ot, int time);
int XaRequestStop_80043524(void);
void DrawRectOutline_80042750(RECT* rect, unsigned char* rgb, void* ot);
#endif
