// SLY3_CFLAGS: -Os -G0
/* Consumed sound-object prefix. The native completion record carries a
   64-bit opaque argument; these two callbacks recover its signed low32
   receiver address, just as the original DSLL32/DSRA32 pair does. */
typedef int CALLBACK_ARGUMENT __attribute__((mode(DI)));
typedef void (*REQUEST_CALLBACK)(int result, CALLBACK_ARGUMENT argument);
typedef struct RECEIVER_ENTRY {
    short delta, padding;
    void (*call)(void *receiver);
} RECEIVER_ENTRY;
typedef struct SOUND_QUEUE_VIEW {
    char opaque0[12]; RECEIVER_ENTRY *vtable;
    char opaque10[0x44-0x10]; int requestId;
    char opaque48[0x5A-0x48]; short activeCount;
    unsigned short flags, pendingCount;
    char opaque60[0x68-0x60]; CALLBACK_ARGUMENT elapsedTicks;
} SOUND_QUEUE_VIEW;
typedef struct SOUND_CLOCK_VIEW {
    char opaque0[0x200]; CALLBACK_ARGUMENT currentTicks, previousTicks;
} SOUND_CLOCK_VIEW;
typedef char SoundQueuePrefix[(sizeof(SOUND_QUEUE_VIEW)==0x70)?1:-1];
typedef char NativeCallbackArgument[(sizeof(CALLBACK_ARGUMENT)==8)?1:-1];
extern SOUND_CLOCK_VIEW D_00474FF0;
void func_00246AC8(int result, CALLBACK_ARGUMENT argument);
void func_00245998(int result, CALLBACK_ARGUMENT argument);
/* Complete dispatcher packs seven32-bit request words, then stores the
   callback and64-bit argument in a real16-byte completion record. The
   incidental dispatcher result is ignored by this original caller. */
int func_00291D30(int package, int command, int id, int a, int b, int c,
                  int d, REQUEST_CALLBACK callback, CALLBACK_ARGUMENT argument);
void func_00245320(void *receiver, unsigned short mask, unsigned short value);

void func_00246708(SOUND_QUEUE_VIEW *p)
{
    if (p->flags & 0x1000) {
        p->vtable[1].call((char *)p + p->vtable[1].delta);
        func_00291D30(0x524B5553, 7, p->requestId, 0, 0, 0, 0,
                      func_00246AC8, (CALLBACK_ARGUMENT)p);
        func_00245320(p, 0x1000, 0);
    }
    if (p->pendingCount) return;
    if (p->flags & 0x400) {
        p->vtable[1].call((char *)p + p->vtable[1].delta);
        func_00291D30(0x524B5553, 8, p->requestId, 0, 0, 0, 0,
                      func_00245998, (CALLBACK_ARGUMENT)p);
        func_00245320(p, 0x400, 0);
    }
    if ((p->flags & 0x800) && p->activeCount <= 0)
        p->elapsedTicks += D_00474FF0.currentTicks - D_00474FF0.previousTicks;
}
