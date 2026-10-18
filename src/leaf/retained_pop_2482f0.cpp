// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct VirtualEntry {
    short delta;
    short unused;
    void (*call)(void *);
};

struct Object {
    char pad[0xC];
    VirtualEntry *vtable;
    char pad10[0x44 - 0x10];
    int state;
    char pad48[0x5C - 0x48];
    unsigned short flags;
    unsigned short count;
};

struct RefArray {
    int count;
    void *entries[8];
};

struct Owner {
    char pad[0x214];
    RefArray refs;
};

struct Ref {
    Object *object;
    ~Ref() {
        if (object)
            object->vtable[2].call((char *)object + object->vtable[2].delta);
    }
};

extern "C" void func_00248458(Ref *, Owner *, int);
extern "C" void func_00244CA8(Object *, float);
extern "C" void func_002BF360(Ref *, void *);

extern "C" void func_002482F0(Owner *owner, int key)
{
    Ref result;
    Object *object;
    func_00248458(&result, owner, key);
    object = result.object;
    if (object) {
        int inactive = 0;
        if (!object->state) {
            inactive = object->count || (object->flags & 1);
            inactive ^= 1;
        }
        if (!inactive) {
            func_00244CA8(object, 0.0f);
            func_002BF360(&result, owner->refs.count > 0 ?
                *(owner->refs.entries + owner->refs.count - 1) : 0);
            if (result.object)
                result.object->vtable[7].call(
                    (char *)result.object + result.object->vtable[7].delta);
        }
    }
}
