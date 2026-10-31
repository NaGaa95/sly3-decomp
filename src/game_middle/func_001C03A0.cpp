// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Resolve a placement point: either from the actor's mount (virtual call chain, through a transform) or from the
// stored position, optionally rotated by the owner's matrix scaled by g, then offset by the camera origin.
#include "../P2/state_position_ops.h"

typedef union { qword q; float f; } U;
typedef struct { qword r[4]; } M4;
struct P;
typedef struct { short d; short pad; void (*pfn)(void *, struct P *, U *, int, float); } VT1;
typedef struct { short d; short pad; void *(*pfn)(void *, int); } VT2;
struct S { char pad[0x24]; VT1 *vt; };
struct O { char pad[0xC]; VT2 *vt; };
struct R { void *x0; };
struct Q { struct O *x0; struct S *x4; struct R *x8; int xc; U x10; };
struct P { char pad[0x260]; qword x260; };

extern "C" qword func_0028E910(void *a, void *b, qword q);
extern "C" void func_0028F680(void *o, float g, int n, M4 *pm, int m);

// Transform the XYZ part of v by the four packed matrix columns (the translation column last).
static inline qword TransformPoint(const M4 &m, qword v)
{
    qword result;
    asm("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
        : "=j"(result) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(v));
    return result;
}

extern "C" qword func_001C03A0(struct P *p, struct Q *q, float g)
{
    U t;
    M4 m;
    void *o;
    qword v;
    qword r;
    if (q->x4) {
        struct S *s = q->x4;
        s->vt[3].pfn((char *)s + s->vt[3].d, p, &t, 0, q->x10.f);
        o = q->x0->vt[37].pfn((char *)q->x0 + q->x0->vt[37].d, 0);
        v = func_0028E910(0, o, t.q);
    } else {
        o = q->x8 ? q->x8->x0 : 0;
        v = q->x10.q;
    }
    if (o && 0.0f < g) {
        func_0028F680(o, g, 0, &m, 0);
        r = TransformPoint(m, v);
    } else {
        r = func_0028E910(o, 0, v);
    }
    if (!q->x4)
        r = PackedDifference(r, p->x260);
    return r;
}
