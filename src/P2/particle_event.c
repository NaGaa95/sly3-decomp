// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Property;
struct FloatPair { float low, high; };
struct ParticleEvent {
    int kind;
    struct FloatPair range;
    unsigned char remainder[0x1C - 12];
};
struct EventTiming {
    unsigned char prefix[0x50];
    struct FloatPair displacement;
    unsigned char to_lifetime[0x78 - 0x58];
    float lifetime;
    int enabled;
};
struct EventDefinition {
    unsigned char prefix[8];
    short repeats, count;
    struct ParticleEvent *events;
    void *sampling;
    struct EventTiming *timing;
};
struct EventOwner { unsigned char prefix[0x68]; float scale; };
struct EventPropertyView {
    struct EventOwner *owner;
    struct EventDefinition *definition;
    void *unused8, *sound;
    float started;
    int event_index;
    float accumulator, rate;
    int repeats;
};
struct Clock { float time; };
extern struct Clock D_0036BB98;
float func_0011E940(float low, float high);
void func_001FF590(struct Property *, int count);

static __inline__ void SetFloatPair(struct FloatPair *range, float low, float high)
{
    range->low = low;
    range->high = high;
}

void func_001FF3E0(struct Property *property)
{
    struct EventPropertyView *p = (struct EventPropertyView *)property;
    p->event_index = (int)((unsigned int)p->event_index + 1U);
    p->started = D_0036BB98.time;
    if (p->event_index >= p->definition->count) {
        if (p->repeats) {
            if (p->repeats < 0 || --p->repeats > 0)
                p->event_index = 0;
        }
    }
    if (p->event_index < p->definition->count) {
        struct ParticleEvent *event = &p->definition->events[p->event_index];
        switch (event->kind) {
        case 1:
            p->accumulator = 0.0f;
            p->rate = func_0011E940(event->range.low, event->range.high);
            break;
        case 4:
            p->accumulator = func_0011E940(event->range.low, event->range.high);
            break;
        }
    }
}

void func_001FF4D8(struct Property *property)
{
    struct EventPropertyView *p = (struct EventPropertyView *)property;
    struct EventTiming *timing = p->definition->timing;
    if (timing->enabled) {
        struct ParticleEvent *events = p->definition->events;
        int index = p->event_index;
        struct ParticleEvent *event = events + index;
        if (event->kind == 1) {
            float requested = p->owner->scale * p->rate * timing->lifetime;
            struct FloatPair saved = timing->displacement;
            SetFloatPair(&p->definition->timing->displacement,
                         0.0f, p->definition->timing->lifetime);
            func_001FF590(property, (int)requested);
            p->definition->timing->displacement = saved;
        }
    }
}
