// SLY3_CFLAGS: -Os -G0
/* Sly2 SeekAsega algorithm with the measured Sly3 update-mode input. Valid seek modes are 0 (absolute), 1 (relative), and 2 (duration-relative). */ struct SeekMethodRecord {
    short delta;
    short unused;
    void (*method)();
};
struct SeekBounds {
    char prefix[0x80];
    float minimum;
    float maximum;
    float *value;
};
struct SeekBinding {
    char unused_prefix[4];
    void *owner;
    struct SeekBounds *bounds;
    unsigned int wordC, word10, word14;
    struct SeekMethodRecord *methods;
    unsigned int word1C, word20, word24;
    struct SeekBinding *next;
};
struct SeekParent {
    char prefix[0x64];
    float duration;
};
struct SeekRuntime {
    char prefix[0x14];
    struct SeekParent *parent;
    unsigned int word18;
    float time, previous_time;
    char gap24[0x34-0x24];
    struct SeekBinding *bindings;
    char gap38[0x40-0x38];
    float scaled_rate, rate, factor48, factor4C;
};
int func_00138AC8(struct SeekRuntime *runtime);
void func_001380E0(struct SeekRuntime *runtime);
int func_00138938(struct SeekRuntime *runtime, float *time, float *rate);
void func_00137EA0(struct SeekRuntime *runtime);
int func_0012F2D0(struct SeekBinding *binding);
void func_0028F260(void *owner, struct SeekBounds *bounds);
void func_0028F978(struct SeekRuntime *runtime, int mode);
/* The EE compiler assigns integer inputs independently of float inputs. Appending update_mode preserves A0/A1/A2 and F12/F13 from the original. Invalid seek integers are outside the 0..2 source contract: the original reads incoming saved F21 without assigning it, and no default is invented. */ typedef char SeekRuntimeViewSize[(sizeof(struct SeekRuntime) == 0x50) ? 1 : -1];
typedef char SeekBindingViewSize[(sizeof(struct SeekBinding) == 0x2C) ? 1 : -1];
typedef char SeekMethodRecordSize[(sizeof(struct SeekMethodRecord) == 8) ? 1 : -1];
void func_00137D08(struct SeekRuntime *runtime, int seek, float time, float rate, int update_mode) {
    float target;
    if (func_00138AC8(runtime)) return;
    runtime->rate = rate;
    runtime->scaled_rate = rate * runtime->factor48 * runtime->factor4C;
    switch (seek) {
        case 0: target = time;
        break;
        case 1: target = runtime->time + time;
        break;
        case 2: target = runtime->parent->duration + time;
        break;
    }
    if (target != runtime->time) {
        struct SeekBinding *binding;
        runtime->time = target;
        if (update_mode) {
            func_001380E0(runtime);
        }
        else {
            func_00138938(runtime, &runtime->time, &runtime->scaled_rate);
            func_00137EA0(runtime);
        }
        for (binding = runtime->bindings; binding; binding = binding->next) {
            if (func_0012F2D0(binding)) {
                struct SeekBounds *bounds = binding->bounds;
                float value = *bounds->value;
                if (value < bounds->minimum || bounds->maximum < value) ((void (*)(void *))binding->methods[4].method) ((char *)binding + binding->methods[4].delta);
                func_0028F260(binding->owner, binding->bounds);
            }
        }
        func_0028F978(runtime, 0);
    }
    runtime->previous_time = runtime->time;
}
