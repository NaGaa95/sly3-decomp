// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
#include "scene.h"
#include "input_mask.h"
struct S;
typedef struct { short d; short pad; SCENE_OBJECT *(*pfn)(void *); } VT;
struct S { char pad[0x24]; VT *vt; };
typedef struct E { SCENE_OBJECT *x0; struct S *x4; int x8; float xc; float x10; int pad[3]; } __attribute__((aligned(16))) E;
struct P { int x0; int c; int pad[2]; E ae[32]; };

extern "C" void *func_00291F38(void *dst, void *src, int cb);
extern "C" void *func_00292034(void *p, int v, int cb);
extern "C" void func_001C0DA8(struct P *p, struct S *s, float g)
{
    int i;
    E *e;
    for (i = 1; i < p->c; i++) {
        e = &p->ae[i];
        if (s == e->x4 && __builtin_fabsf(g - e->x10) < 50.0f) {
            if (i != 1) {
                E t = *e;
                func_00291F38(&p->ae[2], &p->ae[1], (i - 1) * sizeof(E));
                p->ae[1] = t;
            }
            break;
        }
    }
    if (i >= p->c) {
        if ((unsigned int)p->c < 32)
            p->c++;
        func_00291F38(&p->ae[1], &p->ae[0], p->c * sizeof(E) - sizeof(E));
    }
    e = &p->ae[0];
    func_00292034(e, 0, sizeof(E));
    p->ae[0].x0 = s->vt[6].pfn((char *)s + s->vt[6].d);
    e->x4 = s;
    e->x10 = g;
    e->xc = D_0036BB98.now;
    p->ae[0].x0->flags.value |= 1UL << 55;
}
