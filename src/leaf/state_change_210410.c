// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } UQ;
struct VirtualEntry { short adjustment; short reserved; void *call; };
struct Body { unsigned char pad0[0xC]; struct VirtualEntry *vtable; };
struct Curve { float c0, c1, c2; };
struct Handle { int value; };
struct StateSelf {
    unsigned char pad0[0x210];
    int state;
    unsigned char pad214[4];
    struct Body *body;
    unsigned char pad21C[0x228 - 0x21C];
    int channelId;
    unsigned char pad22C[4];
    float enterTime;
    unsigned char pad234[0x250 - 0x234];
    float baseValue;
    unsigned char pad254[0x260 - 0x254];
    struct Curve curve;
    unsigned char pad26C[0x270 - 0x26C];
    float lower, upper;
    float result;
    unsigned char pad27C[0x280 - 0x27C];
    struct Handle link;
};
struct CLOCK { float now; };
extern struct CLOCK D_0036BB98;
qword func_0023D888(struct StateSelf *self);
qword func_001C9428(void *object, int zero, qword v);
int func_002459F8(int id);
void func_00244F08(int handle, int arg);
void func_00244CA8(int handle, float arg);
void func_002BE970(struct Handle *slot, int value);
static __inline__ float GetX(qword v) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(v)); return f; }
static inline float Eval(const struct Curve *c, float t) { return c->c0 + t * (c->c1 + t * c->c2); }
static inline float GClamp(float g, float lo, float hi)
{
    float r;
    if (g < lo)
        r = lo;
    else if (hi < g)
        r = hi;
    else
        r = g;
    return r;
}
// Change the object's state (like the rumble state setter): leaving state 1 releases the linked handle, entering state 1 repositions the body from a limited curve
// value and starts a new channel.
void func_00210410(struct StateSelf *self, int state)
{
    struct Handle *link;
    if (self->state == state)
        return;
    if (self->state == 1) {
        if (self->body)
            ((void (*)(void *))self->body->vtable[9].call)((char *)self->body + self->body->vtable[9].adjustment);
        link = &self->link;
        if (link) {
            if (self->link.value) {
                func_00244CA8(self->link.value, 0.0f);
                func_002BE970(link, 0);
            }
        }
    }
    self->state = state;
    if (state == 1) {
        if (self->body) {
            UQ offset;
            struct VirtualEntry *entry;
            self->result = GClamp(Eval(&self->curve, GetX(func_0023D888(self))), self->lower, self->upper);
            offset.f[0] = self->baseValue + self->result;
            offset.f[1] = 0.0f;
            offset.f[2] = 0.0f;
            entry = &self->body->vtable[34];
            ((void (*)(void *, qword))entry->call)((char *)self->body + entry->adjustment, func_001C9428(self, 0, offset.q));
            ((void (*)(void *))self->body->vtable[8].call)((char *)self->body + self->body->vtable[8].adjustment);
        }
        self->enterTime = D_0036BB98.now;
        {
            int handle = func_002459F8(self->channelId);
            func_00244F08(handle, 0);
            func_002BE970(&self->link, handle);
        }
    }
}
