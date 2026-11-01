// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Record the trail of an object: while it is in state 1 and travels far enough from the last recorded point, push
// the previous entries up by one slot and store the new position and orientation; a stalled object is released.
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta, pad; void *fn; };
struct TrailEntry { qword position; qword rows[3]; };
struct Mat3 { qword rows[3]; };
struct Placement { char pad[0x30]; qword position; };
struct Owner {
    char pad00[0xC]; VTE *vt; char pad10[0x380 - 0x10]; int state;
    char pad384[0x458 - 0x384]; int active; int count; TrailEntry latest; TrailEntry history[31];
    float stamp;
};
struct CLOCK { float now, step; };
extern CLOCK D_0036BB98;
extern "C" {
int func_00205920(Owner *);
int func_002047D0(Owner *, int);
void func_00241100(Owner *, int, int, int, Owner *);
int func_00205888(Owner *);
int func_00205A38(Owner *);
void *func_00291F38(void *, const void *, unsigned int);
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Length(qword v)
{
    qword d, one, len;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(len) : "j"(d));
    return len;
}
static inline float X(qword v)
{
    qword t;
    float f;
    __asm__("qmfc2.ni %0,%1" : "=r"(t) : "j"(v));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(t));
    return f;
}
static inline Placement *PlacementOf(Owner *o)
{
    VTE *entry = &o->vt[36];
    return ((Placement *(*)(void *))entry->fn)((char *)o + entry->delta);
}
static inline Mat3 *RotationOf(Owner *o)
{
    VTE *entry = &o->vt[36];
    return ((Mat3 *(*)(void *))entry->fn)((char *)o + entry->delta);
}
extern "C" void func_002045B0(Owner *self)
{
    if (self->state != 1)
        return;
    VTE *query = &self->vt[81];
    if (((int (*)(void *))query->fn)((char *)self + query->delta) == 2)
        return;
    if (func_00205920(self)) {
        if (0.15f < D_0036BB98.now - self->stamp) {
            if (func_002047D0(self, 0))
                return;
            func_00241100(self, 2, 0, 1, self);
        }
        return;
    }
    self->stamp = D_0036BB98.now;
    if (!self->active)
        return;
    if (!func_00205888(self))
        return;
    if (func_00205A38(self) != 4)
        return;
    TrailEntry *latest = &self->latest;
    if (self->count) {
        qword last = latest->position;
        qword now = PlacementOf(self)->position;
        if (X(Length(Sub(last, now))) < 200.0f)
            return;
    }
    int span = 0x1F;
    if (self->count < 0x1F)
        span = self->count;
    func_00291F38(self->history, latest, span << 6);
    latest->position = PlacementOf(self)->position;
    Mat3 *rot = RotationOf(self);
    latest->rows[0] = rot->rows[0];
    latest->rows[1] = rot->rows[1];
    latest->rows[2] = rot->rows[2];
    int next = 0x20;
    int n1 = self->count + 1;
    if (!(n1 > 0x1F))
        next = n1;
    self->count = next;
}
