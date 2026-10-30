// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int i[4]; } U;
struct Obj { unsigned char pad[0x10C]; int flags; };
struct Self { unsigned char pad[0x3EB8]; int count; struct Obj *objs[4]; };
void func_00168048(struct Obj *obj, qword dir, int *out, float g);
static inline qword Copy(qword v) { qword r; __asm__("vmax.xyzw %0,%0,%0" : "=j"(r) : "0"(v)); return r; }
qword func_0018E728(struct Self *self, qword weights, int mask, qword dir, float g)
{
    U w;
    U out;
    int i;
    w.q = weights;
    out.i[3] = 0;
    out.i[2] = 0;
    out.i[1] = 0;
    out.i[0] = 0;
    for (i = 0; i < self->count; i++) {
        if (w.f[i] != 0.0f) {
            struct Obj *obj = self->objs[i];
            if (obj->flags & mask) {
                func_00168048(obj, Copy(*(qword *)&dir), &out.i[i], g);
            }
        }
    }
    return out.q;
}
