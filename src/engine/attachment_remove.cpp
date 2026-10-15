// SLY3_CFLAGS: -Os -G0 -fno-exceptions
class RemovableAttachment {
public:
    char prefix[0xC];
    virtual void Retain();
    virtual void Release();
    virtual void Lifecycle(int flags,void *context,int options,void *callback,void *argument);
    virtual void Message(int kind,void *value);
};
struct AttachmentRemovalList { void *first,*last; int link_offset; };
extern AttachmentRemovalList D_00479C04;
extern "C" int func_00173A98(void *receiver);
extern "C" void func_0011B028(void *list,void *receiver);
class AttachmentRemovalLock {
public:
    RemovableAttachment *value;
    AttachmentRemovalLock(RemovableAttachment *record) : value(record) { record->Retain(); }
    ~AttachmentRemovalLock() { value->Release(); }
};
extern "C" void func_001739A8(void *receiver)
{
    RemovableAttachment *record=(RemovableAttachment *)receiver;
    if(func_00173A98(record))
        return;
    AttachmentRemovalLock lock(record);
    record->Message(0x16,record);
    if(func_00173A98(record))
        return;
    func_0011B028(&D_00479C04,record);
    record->Lifecycle(3,0,0,0,0);
    record->Release();
}
