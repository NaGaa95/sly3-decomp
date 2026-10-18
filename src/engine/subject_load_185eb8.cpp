// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "heap_frame_api.h"
struct LoadRequest { int bytes,alignment; };
struct LoadAction { int words[5]; };
struct LoadNotification { int words[7]; };
struct SubjectLoad {
    unsigned char prefix[0x44]; int wordCount; int *words;
    unsigned char gap4C[0x98-0x4C]; int actionCount; LoadAction *actions;
    int notificationCount; LoadNotification *notifications;
};
struct BinaryInput;
extern "C" {
void *func_001D25B0(LoadRequest *request);
void *func_001D24D0(LoadRequest *request,void *original);
void func_001C7D98(void *self,void *stream);
void func_00119830(void *stream);
}
class LoadFrame {
public:
    LoadFrame() __asm__("func_001D2770");
    ~LoadFrame() { func_001D2798(this,2); }
};
static inline void *Allocate(LoadRequest *request,int bytes)
{
    request->bytes=bytes;
    request->alignment=16;
    return func_001D25B0(request);
}
static inline void *Resize(LoadRequest *request,int bytes,void *original)
{
    request->bytes=bytes;
    request->alignment=16;
    return func_001D24D0(request,original);
}
extern "C" void func_00185EB8(SubjectLoad *self,BinaryInput *stream)
{
    LoadFrame frame;
    LoadRequest request;
    self->actions=(LoadAction *)Allocate(&request,0x280);
    self->notifications=(LoadNotification *)Allocate(&request,0x380);
    self->words=(int *)Allocate(&request,0x20);
    func_001C7D98(self,stream);
    self->actions=(LoadAction *)Resize(&request,self->actionCount*sizeof(LoadAction),self->actions);
    self->notifications=(LoadNotification *)Resize(&request,self->notificationCount*sizeof(LoadNotification),self->notifications);
    self->words=(int *)Resize(&request,self->wordCount*sizeof(int),self->words);
    func_00119830(stream);
}

#define MEMBER_OFFSET(type,member) ((unsigned int)&(((type *)0)->member))
typedef char PointerSize[(sizeof(void *)==4)?1:-1];
typedef char IntSize[(sizeof(int)==4)?1:-1];
typedef char RequestSize[(sizeof(LoadRequest)==8)?1:-1];
typedef char FrameSize[(sizeof(LoadFrame)==1)?1:-1];
typedef char ActionSize[(sizeof(LoadAction)==20)?1:-1];
typedef char NotificationSize[(sizeof(LoadNotification)==28)?1:-1];
typedef char WordCountOffset[(MEMBER_OFFSET(SubjectLoad,wordCount)==0x44)?1:-1];
typedef char WordsOffset[(MEMBER_OFFSET(SubjectLoad,words)==0x48)?1:-1];
typedef char ActionCountOffset[(MEMBER_OFFSET(SubjectLoad,actionCount)==0x98)?1:-1];
typedef char ActionsOffset[(MEMBER_OFFSET(SubjectLoad,actions)==0x9C)?1:-1];
typedef char NotificationCountOffset[(MEMBER_OFFSET(SubjectLoad,notificationCount)==0xA0)?1:-1];
typedef char NotificationsOffset[(MEMBER_OFFSET(SubjectLoad,notifications)==0xA4)?1:-1];
