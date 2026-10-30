// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
struct Obj { unsigned char pad[0x28]; unsigned long fl28; unsigned char pad30[0x360 - 0x30]; int n360; unsigned char pad364[0x1154 - 0x364]; float f1154; };
struct Ref { int pad[2]; struct Obj *obj; };
struct Slot { struct Obj *obj; float last; float time; struct Ref *ref; int state; int pad[3]; qword pos; };
struct Self { unsigned char pad[0x4C]; int count; struct Slot *slots; };
void func_00199118(struct Self *self, struct Slot *slot, int a, int b);
static inline int IsFlagged(struct Obj *o) { return (int)(o->fl28 >> 56) & 1; }
static inline float GMax(float a, float b) { return a < b ? b : a; }
static inline float Dist2D(qword a, qword b)
{
    qword d; float r;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y\n\tvsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(d) : "0"(d));
    __asm__("qmfc2.ni %0,%1" : "=r"(r) : "j"(d));
    return r;
}
void func_001995B8(struct Self *self, qword target)
{
    int i;
    for (i = 0; i < self->count; i++) {
        struct Slot *slot = &self->slots[i];
        struct Obj *obj = slot->obj;
        if (!obj) {
            if (slot->state == 1 && 3500.0f < Dist2D(slot->pos, target)) {
                slot->state = 0;
                slot->time = g_clock.t;
            }
        } else if (obj->n360) {
            func_00199118(self, slot, 1, 0);
        } else if (!IsFlagged(obj) || !IsFlagged(slot->ref->obj)) {
            func_00199118(self, slot, 0, 0);
        } else {
            float t = GMax(obj->f1154, slot->last);
            slot->last = t;
            if (8.0f < g_clock.t - t) {
                func_00199118(self, slot, 0, 0);
            }
        }
    }
}
