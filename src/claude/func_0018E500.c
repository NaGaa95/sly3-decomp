// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int i[4]; } U;
struct Obj { unsigned char pad[0x10C]; int flags; };
struct Self { unsigned char pad[0x3EB8]; int count; struct Obj *objs[4]; };
int func_00167F60(struct Obj *obj, qword pos, qword extent);
void func_00168048(struct Obj *obj, qword dir, int *out, float g);
static inline qword Copy(qword v) { qword r; __asm__("vmax.xyzw %0,%0,%0" : "=j"(r) : "0"(v)); return r; }
// Copy of pos issued after the extent word ("r"(after)), with e listed as an output so its
// home store waits for the copy; result pinned to $a1 (the argument register) so the
// copy goes through an in/out VU reload like a combined argument set (the one pin).
static inline qword CopyAfterM(qword v, qword after, U *pe) { register qword r asm("$5"); __asm__("vmax.xyzw %0,%0,%0" : "=j"(r), "=m"(*pe) : "0"(v), "r"(after)); return r; }
static inline qword Hi(qword v) { qword r; __asm__("pextuw %0,$0,%1" : "=r"(r) : "r"(v)); return r; }
static inline int Wi(qword v) { int r; __asm__("pextuw %0,$0,%1" : "=r"(r) : "r"(Hi(v))); return r; }
static inline qword QwFromInt(int n) { qword q; __asm__("daddu %0,%1,$0" : "=r"(q) : "r"(n)); return q; }
static inline qword Min(qword a, qword b) { qword r; __asm__("vmini.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
qword func_0018E500(struct Self *self, qword weights, int mask, qword pos, float g)
{
    U w;
    U out;
    int i;
    out.i[3] = 0;
    out.i[2] = 0;
    out.i[1] = 0;
    out.i[0] = 0;
    w.q = weights;
    for (i = 0; i < self->count; i++) {
        if (w.f[i] != 0.0f) {
            struct Obj *obj = self->objs[i];
            if (obj->flags & mask) {
                U e;
                qword q = QwFromInt(Wi(pos));
                qword c = CopyAfterM(pos, q, &e);
                e.q = q;
                if (func_00167F60(obj, c, e.q))
                    func_00168048(obj, Copy(*(qword *)&pos), &out.i[i], g);
            }
        }
    }
    return Min(out.q, weights);
}
