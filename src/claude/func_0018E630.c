// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int i[4]; } U;
struct Obj { unsigned char pad[0x10C]; int flags; };
struct Self { unsigned char pad[0x3EB8]; int count; struct Obj *objs[4]; };
int func_00167F60(struct Obj *obj, qword pos, qword extent);
static inline qword Copy(qword v) { qword r; __asm__("vmax.xyzw %0,%0,%0" : "=j"(r) : "0"(v)); return r; }
static inline qword Hi(qword v) { qword r; __asm__ __volatile__("pextuw %0,$0,%1" : "=r"(r) : "r"(v)); return r; }
static inline int Wi(qword v) { int r; __asm__("pextuw %0,$0,%1" : "=r"(r) : "r"(Hi(v))); return r; }
// w word (in a GPR) copied into a qword GPR: register-class move helper.
static inline qword QwFromInt(int n) { qword q; __asm__("daddu %0,%1,$0" : "=r"(q) : "r"(n)); return q; }
qword func_0018E630(struct Self *self, qword weights, int mask, qword pos)
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
                U e;
                e.q = QwFromInt(Wi(pos));
                if (func_00167F60(obj, Copy(pos), e.q))
                    out.f[i] = w.f[i];
            }
        }
    }
    return out.q;
}
