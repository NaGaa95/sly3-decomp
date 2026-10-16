// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct POOLSTATE
{
    int cb;
    int c;
    int cbAlign;
    void *pv;
    int cAlloc;
    void *pvBlock;
    void *PvAlloc();
    void Reset();
    void Free(void *p);
    void WarmUp();
    POOLSTATE(int cb, int c, int cbAlign);
};
typedef struct DL { void *pvFirst; void *pvLast; int ibDle; } DL;
struct InitEntry { short delta, pad; void (*callback)(void *); };
struct FactoryInstance { char prefix[0xC]; InitEntry *table; };
struct FactoryProperty {
    char prefix[0xD8];
    int mode;
    char gapDC[0xC];
    union { void *pointer; DL list; } storage;
};
extern "C" {
extern char D_00479C74[];
void *func_00202A88(void *storage, void *property, int flags);
void func_0011AF60(DL *list, void *instance);

void *func_001FE728(void *receiver, int flags)
{
    FactoryProperty *property = (FactoryProperty *)receiver;
    switch (property->mode) {
    case 1:
    case 3:
        if (property->storage.pointer)
            return property->storage.pointer;
        break;
    case 2:
        if (*(void **)property->storage.pointer)
            return *(void **)property->storage.pointer;
        break;
    }

    FactoryInstance *instance = (FactoryInstance *)func_00202A88(
        ((POOLSTATE *)D_00479C74)->PvAlloc(), receiver, flags);
    InitEntry *entry = &instance->table[1];
    entry->callback((char *)instance + entry->delta);

    switch (property->mode) {
    case 1:
    case 3:
        property->storage.pointer = instance;
        break;
    case 2:
        *(void **)property->storage.pointer = instance;
        break;
    case 0:
        func_0011AF60(&property->storage.list, instance);
        break;
    }
    return instance;
}
}
