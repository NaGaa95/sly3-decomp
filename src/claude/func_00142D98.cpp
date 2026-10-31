// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VTE { short d; short pad; M4 *(*pfn)(void *); };
struct VT { char pad[0x120]; VTE e120; };
struct P { char pad[0xC]; VT *pvt; char pad1[0x280 - 0x10]; float g280; };
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("mfc1 %0, %1" : "=rj"(q) : "f"(f)); } };
static inline M4 *Matrix(P *p) { VTE *e = &p->pvt->e120; return e->pfn((char *)p + e->d); }
static inline qword AddScale(qword a, VU_FLOAT s, qword b)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
extern "C" qword func_00142D98(P *p)
{
    qword pos = Matrix(p)->r[3];
    return AddScale(pos, VU_FLOAT(-p->g280), Matrix(p)->r[0]);
}
