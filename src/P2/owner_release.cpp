// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct DL { void *pvFirst, *pvLast; int ibDle; };
struct SL;
struct Entry;
struct DLI;
struct SceneDeactivationState;
struct SceneRemoveBinding;
struct SCENE_OBJECT;
extern "C" {
extern DLI *D_0036AE94;
extern unsigned char D_00475480[];
void func_0023BBE0(SceneDeactivationState *object);
void func_0013C138(void *game, SceneRemoveBinding *binding);
void func_001C7848(int receiver_bits);
Entry *func_0017DBD0(char *game, int key);
void func_0011AE28(SL *list, void *value);
void func_001C74B0(SCENE_OBJECT *object);
void func_0011E1F0(void *pool, void *allocation);
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
struct OwnerReleaseMethod {
    short delta, reserved;
    union {
        void (*method)(void *);
        int (*event)(void *, int);
    } call;
};
struct OwnerReleaseChild {
    char prefix[0xE8];
    OwnerReleaseMethod *table;
};
struct OwnerReleaseView {
    char prefix[0xC];
    OwnerReleaseMethod *table;
    SCENE_OBJECT *parent;
    char opaque14[0xDC - 0x14];
    SceneRemoveBinding *binding;
    char opaqueE0[0x134 - 0xE0];
    DL particles;
};
struct OwnerReleaseGame {
    char prefix[0x4818];
    char pool[0x48];
    void *cached;
};
typedef char OwnerReleaseIterator16[sizeof(DLI) == 16 ? 1 : -1];
extern "C" void func_0020B160(void *receiver)
{
    OwnerReleaseView *owner = static_cast<OwnerReleaseView *>(receiver);
    DLI iterator(&owner->particles);
    void *child;
    while ((child = iterator.Next()) != 0) {
        OwnerReleaseMethod *method = &static_cast<OwnerReleaseChild *>(child)->table[6];
        method->call.method(static_cast<char *>(child) + method->delta);
    }
    OwnerReleaseGame *game = reinterpret_cast<OwnerReleaseGame *>(D_00475480);
    if (receiver == game->cached)
        game->cached = 0;
    func_0023BBE0(static_cast<SceneDeactivationState *>(receiver));
    OwnerReleaseMethod *method = &owner->table[30];
    method->call.event(static_cast<char *>(receiver) + method->delta, 0);
    if (owner->binding) {
        func_0013C138(game, owner->binding);
        owner->binding = 0;
    }
    func_001C7848(reinterpret_cast<int>(receiver));
    func_0011AE28(reinterpret_cast<SL *>(func_0017DBD0(reinterpret_cast<char *>(game), 0x63)), receiver);
    if (owner->parent == 0)
        func_001C74B0(static_cast<SCENE_OBJECT *>(receiver));
    func_0011E1F0(game->pool, receiver);
}
