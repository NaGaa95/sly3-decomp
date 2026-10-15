// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Create a pooled position attachment and retain it through the initialization event.
#include "attachment_creation_api.h"
typedef AttachmentPackedPosition PackedPosition;
struct VEntry {
    short delta;
    short padding;
    void (*call)(void *);
};
struct EventEntry {
    short delta;
    short padding;
    void (*call)(void *,int,void *,int,void *,void *);
};
struct AttachmentTable {
    VEntry first[3];
    EventEntry event;
};
struct Space {
    void *parentReference;
    char pad[0x54-4];
    int ordering;
};
struct Attachment {
    char prefix[0xC];
    AttachmentTable *table;
    int count;
    Space *space;
    int pad18[2];
    PackedPosition firstPosition,secondPosition;
    int attachmentWord,pad44,serial;
    float createdAt;
    int pad50,ordering;
    int pad58[2];
};
struct World {
    char pad[0x4504];
    int attachmentSerial;
    char pad4508[0x4784-0x4508];
    char attachmentList[12];
    char attachmentPool[24];
};
struct Clock {
    float time;
};
typedef char CheckAttachmentSize[(sizeof(Attachment)==96)?1:-1];
extern World D_00475480;
extern Clock D_0036BB98;
extern "C" {
    void *func_0011E118(void *);
    void *func_00292034(void *,int,int);
    void *func_002BC8C0(void *);
    void func_0011AF60(void *,void *);
    void func_002BAA50(void *,void *);
}
struct AttachmentLock {
    Attachment *value;
    AttachmentLock(Attachment *p) {
        value=p;
        p->table->first[1].call((char *)p+p->table->first[1].delta);
    }
    ~AttachmentLock() {
        value->table->first[2].call((char *)value+value->table->first[2].delta);
    }
};
extern "C" void func_00173778(void *spaceInput,PackedPosition position,int attachmentWord,void **out) {
    Space *space=(Space *)spaceInput;
    Attachment *p=(Attachment *)func_0011E118(D_00475480.attachmentPool);
    func_00292034(p,0,0x60);
    func_002BC8C0(p);
    p->space=space;
    p->firstPosition=position;
    p->secondPosition=position;
    p->attachmentWord=attachmentWord;
    p->serial=++D_00475480.attachmentSerial;
    p->createdAt=D_0036BB98.time;
    p->ordering=space->ordering;
    func_0011AF60(D_00475480.attachmentList,p);
    p->table->first[1].call((char *)p+p->table->first[1].delta);
    AttachmentLock lock(p);
    func_002BAA50(p,space->parentReference);
    if(out)*out=p;
    p->table->event.call((char *)p+p->table->event.delta,2,0,0,0,0);
}
