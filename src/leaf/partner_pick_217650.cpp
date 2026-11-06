// For each of the two slot groups find the first idle (state 1) slot, then scan the tracker list for the nearest eligible item on each side of this object (squared XY distance within range, ranked by an angle test) and restart the slots of the groups that got a partner (func_002183F8).
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct Method { short delta, reserved; void *(*call)(void *); };
struct Matrix { unsigned char opaque00[0x30]; qword position; };
struct Slot { unsigned char data00[0x10]; int state; float timer; float delay; };
struct Self;
struct Tracker {
    unsigned char opaque00[0x44];
    Self *items[5];
    int count;
};
struct Self {
    unsigned char opaque00[0xC];
    Method *methods;
    unsigned char opaque10[0x1C8 - 0x10];
    int group;
    unsigned char opaque1CC[0x220 - 0x1CC];
    float extent;
    unsigned char opaque224[0x270 - 0x224];
    Slot slots[2][6];
    int counts[2];
    unsigned char opaque3C8[0x3D0 - 0x3C8];
    float range;
    unsigned char opaque3D4[0x3F0 - 0x3D4];
    float radius;
    unsigned char opaque3F4[0x518 - 0x3F4];
    int busy;
};
struct Candidate { Self *item; Slot *slot; float distance; };
extern "C" {
extern Tracker *D_00468D24;
extern const float D_00325C70;
qword func_001C9428(int a, void *self, qword position);
float func_002A36E8(float value);
float func_002A3160(float value);
void func_002183F8(Self *self, Slot *slot, int group);
}
#define MATRIX(o) ((Matrix *)(o)->methods[36].call((unsigned char *)(o) + (o)->methods[36].delta))
static inline qword ToVF(qword v) { qword r; __asm__("qmtc2.ni %1, %0" : "=j"(r) : "r"(v)); return r; }
static inline qword LengthXY(qword v)
{
    qword d;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    return d;
}
static inline float GetX(qword v) { float g; __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(v)); return g; }
extern "C" void func_00217650(Self *self)
{
    Candidate candidates[2];
    int any = 0;
    int g;
    {
    int h;
    for (h = 0; h < 2; h++) {
        Slot *found = 0;
        int count = self->counts[h];
        int j;
        for (j = 0; j < count; j++) {
            Slot *slot = &self->slots[h][j];
            if (slot->state == 1) {
                found = slot;
                break;
            }
        }
        Candidate *c = &candidates[h];
        c->item = 0;
        c->slot = found;
        c->distance = D_00325C70;
        if (found) any = 1;
    }
    }
    if (any) {
        int k;
        for (k = 0; k < D_00468D24->count; k++) {
            Self *item = D_00468D24->items[k];
            U position;
            int side;
            Candidate *c;
            float distance;
            if (item == self) continue;
            if (self->group == item->group && self->group != 0) continue;
            if (item->busy) continue;
            position.q = ToVF(func_001C9428(0, self, MATRIX(item)->position));
            side = position.f[1] <= 0.0f;
            c = &candidates[side];
            if (!c->slot) continue;
            distance = GetX(LengthXY(position.q));
            if (self->range < distance) continue;
            if (c->distance < distance) continue;
            {
                float root = func_002A36E8(self->radius);
                float bias = self->extent / (root + root);
                float a = func_002A3160(__builtin_fabsf(position.f[0]) / (__builtin_fabsf(position.f[1]) + bias));
                float b = func_002A3160((self->range * root + item->extent) / (self->range + bias));
                if (a < b) {
                    c->item = item;
                    c->distance = distance;
                }
            }
        }
        for (g = 0; g < 2; g++) {
            Candidate *c = &candidates[g];
            register Self *picked __asm__("$7") = c->item; /* register pin: the picked item stays in a3 like the target */
            if (picked && c->slot)
                func_002183F8(self, c->slot, g);
        }
    }
}
