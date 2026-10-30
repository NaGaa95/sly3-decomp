// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// EE hardware intrinsics preserve VU/FPU/COP0 operations; C expresses control flow.
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
struct C { char pad[0x30]; qword v; };
struct D { char pad[0x80]; qword v; };
struct B { char pad[0x50]; struct C *pc; char pad2[0x1100 - 0x54]; struct D *pd; };
struct A { char pad[0x10]; struct B *pb; char pad2[0x3C]; M3 mat; qword pad3[3]; qword pos; };
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Mul3(const M3 *m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(r) : "j"(v), "j"(m->r[0]), "j"(m->r[1]), "j"(m->r[2]));
    return r;
}
void func_001327A8(struct A *pa)
{
    struct B *pb = pa->pb;
    qword v = Sub(pa->pos, pb->pc->v);
    qword w = Mul3(&pa->mat, pb->pd->v);
    pa->pos = Sub(v, w);
}
