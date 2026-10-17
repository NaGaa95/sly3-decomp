// SLY3_CFLAGS: -Os -G0
struct Eight { unsigned char bytes[8]; };
struct ArrayRequest { int size,kind; };
struct ClonedOwner {
    unsigned char prefix[0x1D4];
    void *records;
    int count;
    unsigned char gap1DC[0x378];
    struct Eight preserved;
};
void func_0023F400(struct ClonedOwner *destination,void *source);
void *func_001D24D0(struct ArrayRequest *request,void *source);
void func_00213E90(struct ClonedOwner *owner,void *source)
{
    struct Eight preserved=owner->preserved;
    func_0023F400(owner,source);
    owner->preserved=preserved;
    {
        struct ArrayRequest local;
        struct ArrayRequest *request=&local;
        local.size=owner->count*0x2C;
        request->kind=0x10;
        owner->records=func_001D24D0(request,owner->records);
    }
}
