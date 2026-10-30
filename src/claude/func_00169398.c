// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// EE hardware intrinsics preserve VU/FPU/COP0 operations; C expresses control flow.
typedef int qword __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) VECTOR;
typedef struct { float x, y, z; } V3;
struct P { char pad[0x60]; V3 hsv; float a6C; float a70; float a74; V3 rgb; float a84; };
extern char D_00475480[];
void func_0011F4E0(VECTOR *phsv, VECTOR *pv);
void func_002369D8(VECTOR *pv);
void func_001C5250(void *p);
static inline qword VecMul(qword v, float g)
{
    qword r;
    union { qword q; float f; } s;
    __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(g));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(s.q));
    return r;
}
void func_00169398(struct P *p)
{
    VECTOR hsv;
    union { VECTOR v; qword q; } c;
    const float k = 1.0f / 255.0f;
    hsv.x = p->hsv.x;
    hsv.y = p->hsv.y * k;
    hsv.z = p->hsv.z * k;
    func_0011F4E0(&hsv, &c.v);
    c.q = VecMul(c.q, p->a70 * k);
    func_002369D8(&c.v);
    p->rgb = *(V3 *)&c.v;
    p->a84 = p->a74 * k;
    func_001C5250(D_00475480);

}
