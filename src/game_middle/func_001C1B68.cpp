// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sample the vertical extent of up to eight tracked entries: for each entry with an attached actor, query two
// positions of its path object and store (v0 - v1) / radius; then run the shared multi-entry resolve.
// Same routine as Sly 2 func_001A0300 (offsets and callees differ in Sly 3).
#include "../P2/state_position_ops.h"

typedef union WORD { unsigned int bits; float value; } WORD;
typedef union U { qword q; float f[4]; } U;
struct ACTOR; struct MULTI;
struct A;
typedef struct { short d; short pad; void (*pfn)(struct A *, float, float, qword *, void *); } VT;
struct A { VT *vt; };
struct O { int x0; struct A *x4; };
struct K { char pad[0x64]; WORD radius; };
struct E { float x0; struct K *x4; int pad[2]; qword x10; };
extern "C" {
struct O *func_00136EE0(struct K *k, struct ACTOR *p, void *a, int b);
void func_00147E08(struct ACTOR *p, int cb, int c, struct E *ae, int count, int *keys, int *counts, struct MULTI **pn);
}
// value / radius: the radius word goes to a VU register, VDIV forms Q = 1 / radius and VMULQ scales the value.
static inline qword DivideByRadius(qword value, unsigned int radiusBits, qword &radius)
{
    qword result, scalar;
    asm("qmtc2.ni %2,%1\n\tvdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%3,$Q"
        : "=j"(result), "=j"(scalar) : "r"(radiusBits), "j"(value));
    radius = scalar;
    return result;
}
extern "C" void func_001C1B68(struct ACTOR *p, struct E *ae, struct MULTI **pn)
{
    struct E *e = ae;
    int i;
    U v0, v1, t;
    struct MULTI *n;
    for (i = 0; i < 8; i++, e++) {
        if (e->x4) {
            struct O *o = func_00136EE0(e->x4, p, (void *)1, 1);
            if (o) {
                o->x4->vt[3].pfn((struct A *)((char *)o->x4 + o->x4->vt[3].d), 0.0f, 1.0f, &v0.q, 0);
                o->x4->vt[3].pfn((struct A *)((char *)o->x4 + o->x4->vt[3].d), e->x4->radius.value, 1.0f, &v1.q, 0);
                qword b = v1.q;
                qword a = v0.q;
                e->x10 = DivideByRadius(PackedDifference(a, b), e->x4->radius.bits, t.q);
            }
        }
    }
    func_00147E08(p, 0x20, 8, ae, 0, 0, 0, &n);
    *pn = n;
}
