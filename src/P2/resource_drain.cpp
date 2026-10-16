// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "animation_ensure_api.h"

struct DrainMethodRecord {
    short delta;
    short unused;
    void (*method)(void *);
};

struct DrainDurationView {
    unsigned char prefix64[0x64];
    float duration;
};

struct DrainRuntimeView {
    unsigned char prefix14[0x14];
    DrainDurationView *parent;
    unsigned int word18;
    float time;
};

struct DrainResourceView {
    unsigned char prefixC[0xC];
    DrainMethodRecord *methods;
    unsigned char gap10[0x30 - 0x10];
    DrainRuntimeView *current;
};

typedef char DrainMethodMustBe8[sizeof(DrainMethodRecord) == 8 ? 1 : -1];
typedef char DrainRuntimeMustBe32[sizeof(DrainRuntimeView) == 32 ? 1 : -1];
typedef char DrainResourceMustBe52[sizeof(DrainResourceView) == 52 ? 1 : -1];

extern "C" int func_00239CC0(void *resource);
extern "C" void func_00137B00(void *runtime);

class DrainResourceHold {
    DrainResourceView *resource;
public:
    DrainResourceHold(DrainResourceView *value) : resource(value)
    {
        DrainMethodRecord *entry = &resource->methods[1];
        entry->method((char *)resource + entry->delta);
    }
    ~DrainResourceHold()
    {
        DrainMethodRecord *entry = &resource->methods[2];
        entry->method((char *)resource + entry->delta);
    }
};

extern "C" void func_0023A790(DrainResourceView *resource, float remaining)
{
    if (!func_00239CC0(resource)) {
        DrainResourceHold hold(resource);
        DrainRuntimeView *runtime;
        while ((runtime = resource->current) != 0) {
            float difference = runtime->parent->duration - runtime->time;
            if (remaining < difference) {
                func_00137D08((SeekRuntime *)runtime, 1, remaining, 1.0f, 0);
                break;
            }
            remaining -= difference;
            func_00137B00(runtime);
        }
    }
}
