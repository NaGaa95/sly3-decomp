// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions

struct DL { void *pvFirst, *pvLast; int ibDle; };
struct DLI;
struct S { char unknown_0[0x18]; void *resource; };
struct CleanupEntry { short delta, reserved; void (*method)(void *); };
struct CleanupChild { char prefix[0x40]; CleanupEntry *operations; };
struct CleanupOwner {
    char prefix[0xC];
    CleanupEntry *table;
    void *settings;
    char reserved14[0x58];
    DL children;
};
extern "C" {
extern DLI *D_0036AE94;
extern DL D_00479C8C;
int func_00203148(void *object);
void func_00202D30(S *object, void *resource);
void func_001FE8C8(void *settings, void *object);
void func_0011B028(DL *list, void *object);
}
struct DLI {
    DL *pdl;
    void **ppv;
    int ibDle;
    DLI *pdliNext;
    DLI(DL *list)
        : pdl(list), ppv((void **)list), ibDle(list->ibDle),
          pdliNext(D_0036AE94)
    {
        D_0036AE94 = this;
    }
    ~DLI()
    {
        D_0036AE94 = pdliNext;
    }
    void *Next()
    {
        void *value = *ppv;
        ppv = (void **)((unsigned int)value + (unsigned int)ibDle);
        return value;
    }
};

extern "C" void func_00203078(void *object)
{
    if (func_00203148(object))
        return;
    func_00202D30((S *)object, 0);
    CleanupOwner *owner = (CleanupOwner *)object;
    DLI iterator(&owner->children);
    void *child;
    while ((child = iterator.Next()) != 0) {
        CleanupEntry *entry = &((CleanupChild *)child)->operations[5];
        entry->method((char *)child + entry->delta);
    }
    func_001FE8C8(owner->settings, object);
    func_0011B028(&D_00479C8C, object);
    CleanupEntry *entry = &owner->table[2];
    entry->method((char *)object + entry->delta);
}
