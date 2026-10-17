// SLY3_CFLAGS: -Os -G0
struct PackRequest { int bytes; int alignment; };
struct PackEntry { unsigned char prefix[0xE4]; int count; void *buffer; unsigned char gapEC[4]; };
struct PackOwner { unsigned char prefix[0x5C]; int count; struct PackEntry *entries; };
void *func_001D2770(void *receiver);
void func_001D2798(void *receiver,int flags);
void *func_001D2670(struct PackRequest *request);
void *func_001D24D0(struct PackRequest *request,void *source);
void func_001C7D98(void *owner,void *stream);
void func_00172608(struct PackOwner *owner,void *stream)
{
    unsigned char frame[16];
    struct PackRequest request;
    struct PackRequest *pointer;
    int i=0;
    func_001D2770(frame);
    pointer=&request;
    request.bytes=0x1E00;
    pointer->alignment=0x10;
    owner->entries=func_001D2670(pointer);
    func_001C7D98(owner,stream);
    request.bytes=owner->count*0xF0;
    pointer->alignment=0x10;
    owner->entries=func_001D24D0(pointer,owner->entries);
    for(i=0;i<owner->count;i++) {
        struct PackEntry *entry=(struct PackEntry *)((char *)owner->entries+i*0xF0);
        int count=entry->count;
        void *source=entry->buffer;
        request.bytes=count*0xC;
        pointer->alignment=0x10;
        entry->buffer=func_001D24D0(pointer,source);
    }
    func_001D2798(frame,2);
}
