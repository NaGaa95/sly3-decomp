// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct S;
struct TaskChannelObject {
    unsigned char opaque00[0x130];
    int index;
    unsigned char opaque134[0x30];
    unsigned int value;
    unsigned char opaque168[0x50];
    int active;
    unsigned char opaque1BC[0x11CC - 0x1BC];
    int mode;
};
struct TaskChannelReceiver {
    unsigned char opaque00[0x10];
    TaskChannelObject *owner;
    unsigned char opaque14[0x24];
    TaskChannelObject *subject;
};
extern "C" {
extern char D_00475480[];
void func_001F4B00(void *unused, int index, void *object);
void func_00259D10(struct S *record);
}
extern "C" void func_001F5C58(void *receiver)
{
    TaskChannelReceiver *source = static_cast<TaskChannelReceiver *>(receiver);
    func_001F4B00(D_00475480, source->subject->index, source->owner);
    func_00259D10(reinterpret_cast<S *>(reinterpret_cast<char *>(source->owner) + 0x4B0));
    source->owner->value = source->subject->value;
    if (source->owner->mode == 3) source->owner->active = 1;
}
