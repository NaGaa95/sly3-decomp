// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
// Per-frame update of the actor's current state (state values 0..23): runs the common updates, dispatches the
// state-specific one, then keeps the pending hit/pickup record alive. Sly 2 relative: func_001B50B0.
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct Input { unsigned char prefix[8]; float strength; };
struct Clock { float time, step; };
struct Record { unsigned char prefix[0xDC]; void *owner; };
struct Actor {
    unsigned char prefix0[0xC];
    struct Method *methods;
    unsigned char gap10[0x28 - 0x10];
    unsigned long flags;
    unsigned char gap30[0xDC - 0x30];
    void *owner;
    unsigned char gapE0[0x134 - 0xE0];
    struct Input *input;
    unsigned char gap138[0x1A0 - 0x138];
    qword direction;
    unsigned char gap1B0[0x320 - 0x1B0];
    unsigned char context320[0x500 - 0x320];
    unsigned char context500[0xE40 - 0x500];
    unsigned char contextE40[0x1108 - 0xE40];
    void *slot1108;
    float heading;
    unsigned char gap1110[0x1470 - 0x1110];
    unsigned char context1470[0x1520 - 0x1470];
    int state;
    unsigned char gap1524[0x156C - 0x1524];
    struct Record *pending;
    float pendingTime;
    unsigned char gap1574[0x1680 - 0x1574];
    unsigned char context1680[0x18DC - 0x1680];
    void *resource;
};
extern struct Clock D_0036BB98;
extern char D_00475480[];
void func_00152A48(struct Actor *self);
int func_00138AC8(void *resource);
void func_00137688(void *resource);
void func_001DD520(struct Actor *self);
void func_001DCEA8(struct Actor *self);
void func_001B9C48(void *context);
void func_001B30E8(void *context);
void func_001E1530(struct Actor *self);
void func_001E19F0(struct Actor *self);
void func_001C2B48(void *context);
void func_001E3488(struct Actor *self);
void func_001E49B8(struct Actor *self);
void func_0024E878(struct Actor *self, float angle);
void func_00258CF0(void *context, float value);
void func_00258DA0(void *context);
int func_00173428(void *slot);
void *func_00173408(void *slot);
struct Pusher { unsigned char prefix[0x1C]; float scale; };
struct Pusher *func_00156AB0(struct Actor *self);
qword func_0024F278(struct Actor *self, struct Pusher *pusher, float scale);
void func_00138B68(struct Pusher *pusher, float value);
void func_001E0B48(struct Actor *self);
int func_0013C658(void *world, void *a, void *b);
void func_0013CD10(void *world, struct Actor *self);
void func_001DD858(struct Actor *self);
static inline qword BlendScalar(float value)
{
    qword scalar;
    __asm__("qmtc2.ni %1,%0" : "=j"(scalar) : "r"(value));
    return scalar;
}
static inline qword BlendScale(qword vector, qword scalar)
{
    qword result;
    __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(result) : "j"(vector), "j"(scalar));
    return result;
}
static inline int IsActive(void *slot)
{
    return slot && func_00173428(slot) != 0;
}
void func_001DD590(struct Actor *self)
{
    union { qword q; float f[4]; } factor;
    func_00152A48(self);
    if (!((int)(self->flags >> 56) & 1))
        return;
    if (self->resource) {
        if (func_00138AC8(self->resource))
            func_00137688(&self->resource);
    }
    func_001DD520(self);
    func_001DCEA8(self);
    switch (self->state) {
    default:
        break;
    case 0:
        ((void (*)(void *))self->methods[110].function)((char *)self + self->methods[110].adjustment);
        break;
    case 1:
        func_0024E878(self, self->heading);
        func_00258CF0(self->context1470, 1.0f);
        func_00258DA0(self->context1470);
        break;
    case 11: {
        void *context = 0;
        func_0024E878(self, self->heading);
        if (IsActive(self->slot1108))
            context = func_00173408(self->slot1108);
        if (!context)
            context = self->context1680;
        func_00258CF0(context, self->input->strength);
        func_00258DA0(context);
        break;
    }
    case 2:
        func_001B9C48(self->context320);
        break;
    case 14:
        func_001B30E8(self->context500);
        break;
    case 12:
        func_001E1530(self);
        break;
    case 13:
        func_001E19F0(self);
        break;
    case 18: {
        struct Pusher *pusher = func_00156AB0(self);
        qword pushed = func_0024F278(self, pusher, pusher->scale);
        factor.q = BlendScalar(-1.0f);
        self->direction = BlendScale(pushed, factor.q);
        break;
    }
    case 19: {
        struct Pusher *pusher = func_00156AB0(self);
        qword pushed = func_0024F278(self, pusher, pusher->scale);
        factor.q = BlendScalar(-1.0f);
        self->direction = BlendScale(pushed, factor.q);
        func_00138B68(pusher, self->input->strength);
        func_0024E878(self, self->heading);
        break;
    }
    case 22:
        func_001E3488(self);
        break;
    case 15:
        func_001C2B48(self->contextE40);
        break;
    case 23:
        func_001E49B8(self);
        break;
    }
    func_001E0B48(self);
    if (self->pending && self->pendingTime + 0.1f < D_0036BB98.time) {
        void *other = self->pending->owner;
        if (!other || !func_0013C658(D_00475480, self->owner, other))
            self->pending = 0;
        if (!self->pending)
            func_0013CD10(D_00475480, self);
    }
    func_001DD858(self);
}
