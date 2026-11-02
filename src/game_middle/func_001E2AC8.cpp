// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Per-frame push accumulator of the actor (state 0x16): sums the weighted contact directions of every active contact record the
// actor owns, turns the length into a clamped reach (quadratic falloff), logs the normalized push in an 8-entry ring and then, by
// mode, either snaps the gather vector and picks a near/far reaction, nudges the actor and plays the impact sounds, or accumulates.
// Allocation notes:
// - VU_FLOAT(const float &) loads the weight with lw straight from memory; the by-value VU_FLOAT temp is the dead sqc2 at sp+0.
// - SndRef has a copy constructor so it is BLKmode like the engine's smart pointer; it then reuses the free VU_FLOAT temp slot (sp+0).
// - the count cap goes through an inline helper so the limit 7 stays a register (slt, not slti).
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct VU_FLOAT {
    qword qw;
    VU_FLOAT(const float &f) { __asm__("qmtc2.ni %1, %0" : "=j"(qw) : "r"(*(const int *)&f)); }
};
struct Falloff { float constant, linear, quadratic; };
struct Limits { float minimum, maximum; };
struct Clock { float time, step; };
struct Object { unsigned char prefix[0xC]; struct Method *methods; };
struct Slot { void *owner; unsigned char gap[0x3C]; };
struct Holder { unsigned char gap0[8]; Slot slot[2]; };
struct Contact { int owner; unsigned char gap4[8]; float weight; unsigned char gap10[0x18]; };
struct Pair { qword value; qword extra; };
struct Record { Pair pair[2]; unsigned char gap40[0x10]; Holder *holder; unsigned char gap54[0xC]; };
struct Collection {
    unsigned char gap0[4];
    int count;
    Contact *contacts;
    unsigned char gapC[0x60 - 0xC];
    Record *records;
};
struct Push { qword direction; float time; float reach; unsigned char gap18[8]; };
struct Actor {
    unsigned char prefix0[0xC];
    struct Method *methods;
    unsigned char gap10[0x1520 - 0x10];
    int state;
    unsigned char gap1524[0x1AD4 - 0x1524];
    int mode;
    unsigned char gap1AD8[0x1AF0 - 0x1AD8];
    void *near;
    void *far;
    unsigned char gap1AF8[0x1B30 - 0x1AF8];
    qword gather;
    unsigned char gap1B40[0x1B50 - 0x1B40];
    int count;
    unsigned head;
    unsigned char gap1B58[8];
    Push ring[8];
};
struct SndRef { Object *p; SndRef() { p = 0; } SndRef(const SndRef &o) { p = o.p; } };
extern Collection *D_0036AEAC;
extern Clock D_0036BB98;
extern Falloff D_00324A10;
extern Limits D_00324A20;
extern "C" {
void func_00243F38(Actor *self);
void func_001E2E88(Actor *self, int k);
void func_001E2A20(Actor *self, void *object);
void *func_002459F8(int identifier);
void func_00244F08(void *sound, Actor *owner);
void func_002BBCD8(void *pp, void *p);
void func_00244E08(void *sound, float g);
}
static inline qword QwZero() { qword qw; __asm__("vsub.xyzw %0, $vf0, $vf0" : "=j"(qw)); return qw; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword MulAdd(qword a, VU_FLOAT s, qword b)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.qw));
    return r;
}
static inline qword Scale(qword v, VU_FLOAT s)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(v), "j"(s.qw));
    return r;
}
static inline float Length(qword v)
{
    qword d, one, l;
    float g;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    __asm__("mtc1 %1,%0" : "=f"(g) : "r"(l));
    return g;
}
static inline float GetZ(qword q) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q)); return z; }
static inline float Clamp(float value, const Limits *lim)
{
    float low = lim->minimum;
    float high = lim->maximum;
    if (value < low)
        return low;
    if (high < value)
        return high;
    return value;
}
static inline int GrowCount(int n, int last)
{
    if (n > last)
        return 8;
    return n;
}
extern "C" void func_001E2AC8(Actor *self)
{
    func_00243F38(self);
    if (self->state != 0x16 || self->mode == 2)
        return;
    qword sum = QwZero();
    Collection *collection = D_0036AEAC;
    for (int i = 0; i < collection->count; i++) {
        Contact *contact = &collection->contacts[i];
        if (contact->owner == 0 && contact->weight != 0.0f) {
            Record *record = &collection->records[i];
            qword *position = &record->pair[0].value;
            Slot *slot = record->holder->slot;
            for (int k = 0; k < 2; position += 2, k++, slot++) {
                if (slot->owner == self)
                    sum = MulAdd(sum, VU_FLOAT(contact->weight), *position);
            }
        }
    }
    float length = Length(sum);
    float reach = Clamp(D_00324A10.constant + length * (D_00324A10.linear + length * D_00324A10.quadratic), &D_00324A20);
    if (0.0f < reach) {
        Push *push = &self->ring[self->head];
        self->head++;
        if (self->head >= 8)
            self->head = 0;
        int n = self->count + 1;
        self->count = GrowCount(n, 7);
        push->direction = Scale(sum, VU_FLOAT(length));
        push->time = D_0036BB98.time;
        push->reach = reach;
    }
    switch (self->mode) {
    case 0: {
        float z = GetZ(sum);
        if (500.0f < z) {
            self->gather = sum;
            func_001E2E88(self, 1);
            if (z < 1350.0f)
                func_001E2A20(self, self->near);
            else
                func_001E2A20(self, self->far);
        } else {
            struct Method *get = &self->methods[38];
            qword base = ((qword (*)(void *))get->function)((char *)self + get->adjustment);
            struct Method *set = &self->methods[40];
            ((void (*)(void *, qword))set->function)((char *)self + set->adjustment, MulAdd(base, VU_FLOAT(0.25f), sum));
            if (500.0f < Length(sum)) {
                SndRef sound;
                void *s = func_002459F8(0x8B);
                func_00244F08(s, self);
                func_002BBCD8(&sound, s);
                s = func_002459F8(0x1B);
                func_00244F08(s, self);
                func_002BBCD8(&sound, s);
                func_00244E08(sound.p, 0.8f);
                if (sound.p) {
                    struct Method *stop = &sound.p->methods[2];
                    ((void (*)(void *))stop->function)((char *)sound.p + stop->adjustment);
                }
            }
        }
        break;
    }
    case 1:
        self->gather = Add(self->gather, sum);
        break;
    }
}
