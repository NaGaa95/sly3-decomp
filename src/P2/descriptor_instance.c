// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct SelectedInstance {
    char prefix[0x14];
    void *parent;
    char gap18[0x48];
    void *space;
    char gap64[0x1C];
    struct SelectedInstance *next;
};
struct InstanceProperty {
    char prefix[0xD8];
    int mode;
    char gapDC[0xC];
    struct SelectedInstance *first;
};
void *func_001FE728(void *receiver, int flags);

void *func_001FE840(void *receiver, void *parent, void *space, int flags)
{
    struct InstanceProperty *property = receiver;
    struct SelectedInstance *instance;
    if (property->mode != 0)
        return 0;
    for (instance = property->first; instance; instance = instance->next) {
        if (instance->parent == parent && instance->space == space)
            return instance;
    }
    instance = func_001FE728(receiver, flags);
    instance->parent = parent;
    instance->space = space;
    return instance;
}
