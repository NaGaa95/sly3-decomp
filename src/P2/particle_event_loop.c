// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Property;
struct P;
struct S;
struct Entry { short adjustment, reserved; void *function; };
struct Frame { unsigned char prefix[0x30]; qword position; };
struct Actor { unsigned char prefix[0xC]; struct Entry *table; };
struct OwnerSettings { unsigned char prefix[0xD8]; int mode; };
struct EventOwner {
    unsigned char prefix[0x10];
    struct OwnerSettings *settings;
    struct Actor *actor;
    unsigned char to_position[0x50 - 0x18];
    qword position;
    unsigned char to_scale[0x68 - 0x60];
    float scale;
};
struct Event {
    int kind;
    union {
        struct { int low, high; } burst;
        struct { float low, high, duration; } rate;
        struct { int identifier; float low, high, volume, pitch; } sound;
        unsigned char bytes[24];
    } value;
};
struct EventDefinition {
    unsigned char prefix[0xA];
    short count;
    struct Event *events;
};
struct PropertyView {
    struct EventOwner *owner;
    struct EventDefinition *definition;
    void *resource, *sound;
    float started;
    int event_index;
    float accumulator, rate;
};
struct VoiceView { unsigned char prefix[0xC]; struct Entry *table; };
struct Clock { float time, delta; };
extern struct Clock D_0036BB98;
float func_0011E940(float, float);
void func_001FF590(struct Property *, int);
void func_001FF3E0(struct Property *);
void *func_002459F8(int);
void func_00244F08(struct P *, int);
void func_00245100(struct S *, float, float);
void func_00244E08(struct P *, float);
void func_00244ED0(void *, float);
void func_00245000(struct P *, qword);
void func_00244CA8(struct S *, float);
void func_002BE970(void **, void *);
static __inline__ void StopReference(void **reference)
{
    if (reference && *reference) {
        func_00244CA8((struct S *)*reference, 0.0f);
        func_002BE970(reference, 0);
    }
}
int func_001FF100(struct Property *property)
{
    struct PropertyView *p = (struct PropertyView *)property;
    for (;;) {
        int previous_index = p->event_index;
        struct Event *event;
        float elapsed;
        if (previous_index >= p->definition->count)
            return 0;
        event = p->definition->events + previous_index;
        elapsed = D_0036BB98.time - p->started;
        switch (event->kind) {
        case 0: {
            float scale = p->owner->scale;
            int count = (int)func_0011E940(scale * (float)event->value.burst.low,
                                         scale * (float)event->value.burst.high);
            func_001FF590(property, count);
            func_001FF3E0(property);
            break;
        }
        case 1: {
            int count;
            p->accumulator += p->owner->scale * p->rate * D_0036BB98.delta;
            count = (int)p->accumulator;
            p->accumulator -= (float)count;
            func_001FF590(property, count);
            if (event->value.rate.duration >= 0.0f &&
                elapsed >= event->value.rate.duration)
                func_001FF3E0(property);
            break;
        }
        case 2: {
            struct Actor *actor = p->owner->actor;
            void *voice = func_002459F8(event->value.sound.identifier);
            struct EventOwner *owner;
            struct VoiceView *view;
            func_00244F08((struct P *)voice, 0);
            func_00245100((struct S *)voice, event->value.sound.low,
                         event->value.sound.high);
            func_00244E08((struct P *)voice, event->value.sound.volume);
            func_00244ED0(voice, event->value.sound.pitch);
            owner = p->owner;
            if (owner->settings->mode == 0) {
                qword position;
                if (actor) {
                    struct Entry *entry = actor->table + 36;
                    struct Frame *frame = ((struct Frame *(*)(void *))entry->function)
                        ((char *)actor + entry->adjustment);
                    position = frame->position;
                } else {
                    position = owner->position;
                }
                func_00245000((struct P *)voice, position);
            } else if (actor) {
                func_00244F08((struct P *)voice, (int)(unsigned int)actor);
            } else {
                func_00245000((struct P *)voice, owner->position);
            }
            view = (struct VoiceView *)voice;
            {
                struct Entry *entry = view->table + 8;
                int status = ((int (*)(void *))entry->function)
                    ((char *)voice + entry->adjustment);
                if (status == 2) {
                    StopReference(&p->sound);
                    func_002BE970(&p->sound, voice);
                }
            }
            func_001FF3E0(property);
            break;
        }
        case 3:
            StopReference(&p->sound);
            func_001FF3E0(property);
            break;
        case 4:
            if (p->accumulator <= elapsed)
                func_001FF3E0(property);
            break;
        }
        if (p->event_index == previous_index)
            return 1;
    }
}
