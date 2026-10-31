// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct Frame { unsigned char prefix[0x30]; qword position; };
struct Clock { float time; };
struct Context { unsigned char prefix[0xC]; struct Method *methods; };
struct Slot { unsigned char data[0x20]; };
struct Owner {
    unsigned char prefix0[0x50];
    struct Slot slots[1];
};
struct OwnerMode { unsigned char prefix[0x110]; int mode; };
struct Marker {
    unsigned char prefix0[0xC];
    struct Method *methods;
    unsigned char gap10[0x38 - 0x10];
    int state;
    unsigned char gap3C[4];
    union { qword position; struct { float pad[1]; float strength; } f; } at40;
};
struct Phase {
    unsigned char prefix0[0x10];
    struct Context *context;
    unsigned char gap14[0x18 - 0x14];
    unsigned char resource[0x30 - 0x18];
    struct Owner *owner;
    int slot;
    int state;
    float changed;
    float deadline;
};
extern struct Clock D_0036BB98;
void func_00238AE8(void *resource);
void func_00238AB8(void *phase);
void *func_00238690(void *table, int id);
qword func_001EE788(void *slot, qword point);
void *func_001EF038(qword a, qword b, void *c);
void func_001D8B40(void *marker, void *target);
void func_001D99E8(struct Phase *phase);
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword LengthXY(qword v) { qword r; __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(r) : "j"(v)); return r; }
static inline qword SqrtX(qword v) { qword r; __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(r) : "j"(v)); return r; }
static inline float Low(qword v) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(v)); return x; }
static inline struct Frame *FrameOf(struct Context *context)
{
    struct Method *method = &context->methods[36];
    return ((struct Frame *(*)(void *))method->function)((char *)context + method->adjustment);
}

void func_001D9A88(struct Phase *self, int state)
{
    if (state == self->state)
        return;
    func_00238AE8(self->resource);
    self->state = state;
    self->changed = D_0036BB98.time;
    switch (state) {
    case 0:
        switch (((struct OwnerMode *)self->owner)->mode) {
        case 0: {
            qword position = FrameOf(self->context)->position;
            qword target = func_001EE788(&self->owner->slots[self->slot], position);
            struct Marker *marker;
            void *nearest;
            float reach = Low(SqrtX(LengthXY(Sub(position, target)))) / 75.0f;
            self->deadline = D_0036BB98.time + (reach > 2.0f ? reach : 2.0f);
            marker = func_00238690((char *)self->context + 0x29C, 0xF0);
            nearest = func_001EF038(position, target, 0);
            marker->state = 1;
            marker->at40.f.strength = 10.0f;
            func_001D8B40(marker, nearest);
            ((void (*)(void *))marker->methods[8].function)((char *)marker + marker->methods[8].adjustment);
            break;
        }
        case 1:
            func_001D99E8(self);
            break;
        }
        break;
    case 1: {
        struct Marker *marker = func_00238690((char *)self->context + 0x29C, 0xE5);
        marker->at40.position = func_001EE788(&self->owner->slots[self->slot], FrameOf(self->context)->position);
        ((void (*)(void *))marker->methods[8].function)((char *)marker + marker->methods[8].adjustment);
        break;
    }
    case -1:
        func_00238AB8(self);
        break;
    }
}
