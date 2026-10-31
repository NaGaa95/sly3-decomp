// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
typedef struct VirtualEntry { short adjustment; short reserved; qword (*call)(); } VirtualEntry;
struct Link { unsigned char pad[0xA0]; void *limits; };
struct Self {
    unsigned char opaque0[12]; VirtualEntry *vtable;
    unsigned char pad10[0x4C - 0x10]; struct Link *link;
    unsigned char pad50[0x1F0 - 0x50]; int state;
    unsigned char pad1F4[0x234 - 0x1F4]; float angle; unsigned char pad238[8]; qword target;
    unsigned char pad250[0x3E8 - 0x250]; unsigned char limits[0x3F4 - 0x3E8]; int gain;
};
extern "C" {
extern qword D_00317550;
void func_0019F6D8(struct Self *self);
M3 *func_0011C8C0(M3 *m, float angle, qword axis);
void func_0028EA00(M3 *m, void *limits, int a, M3 *in);
void func_0023EDE8(struct Self *self, M3 m, void *limits);
void func_00244828(struct Self *self, qword v);
}
// VU_FLOAT: a scalar loaded straight into a VU register (lw + qmtc2, as the engine's VU_FLOAT helpers); it lives in memory.
struct VU_FLOAT { qword q; VU_FLOAT(const int &g) { int t; __asm__("lw %1, %2\n\tqmtc2.ni %1, %0" : "=j"(q), "=&r"(t) : "m"(g)); } };
static inline qword Mulx(qword a, const VU_FLOAT &s)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s.q));
    return r;
}
extern "C" void func_0019D898(struct Self *self)
{
    func_0019F6D8(self);
    if ((unsigned int)(self->state - 4) >= 2) {
        M3 copy, matrix;
        M3 *pm = &matrix;
        func_0011C8C0(pm, self->angle, D_00317550);
        copy = matrix;
        if (self->state != 3) {
            func_0028EA00(pm, self->link->limits, 0, &copy);
            copy = matrix;
        }
        func_0023EDE8(self, copy, self->limits);
    }
    if (self->state == 3) {
        qword target = self->target;
        VirtualEntry *entry = &self->vtable[38];
        qword pos = ((qword (*)(void *))entry->call)((char *)self + entry->adjustment);
        qword d;
        __asm__("vsub.xyzw %0,%1,%2" : "=j"(d) : "j"(target), "j"(pos));
        func_00244828(self, Mulx(d, self->gain));
    }
}
