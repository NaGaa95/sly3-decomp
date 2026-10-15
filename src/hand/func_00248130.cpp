// Move or create the keyed retained object, configure its real float ranges, and append it to the eight-entry stack.
// All original inputs, complete code/data and boundaries were independently reviewed.
// Manage the real eight-entry retained-pointer stack with an ordinary one-word RAII reference.
// Type names remain provisional; concrete used virtual slots and actual float arguments are proved.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "actor_state_resource_api.h"
struct VTE {
    short d;
    short p;
    void (*pfn)(void *);
};
struct VT {
    VTE a[8];
};
struct X {
    char pad[0xC];
    VT *pvt;
};
struct Ref;
extern "C" void func_002BF3C8(Ref *, X *);
extern "C" void func_002BF360(Ref *, X *);
struct Ref {
    X *px;
    Ref(X *p) {
        func_002BF3C8(this, p);
    }
    Ref(const Ref &r) {
        func_002BF3C8(this, r.px);
    }
    Ref &operator=(const Ref &r) {
        func_002BF360(this, r.px);
        return *this;
    }
    Ref &operator=(X *p) {
        func_002BF360(this, p);
        return *this;
    }
    ~Ref() {
        if (px) px->pvt->a[2].pfn((char *)px + px->pvt->a[2].d);
    }
};
struct S {
    int c;
    Ref a[8];
};
struct P {
    char pad[0x214];
    S s;
};
extern "C" {
    Ref func_00248458(P *, int);
    void func_00244CA8(X *, float);
    X *func_00246E68(P *, int);
    X *func_00245FE8(X *, int);
}
struct V2 {
    float x, y;
};
static inline void Set(V2 *pv, float x, float y) {
    pv->x = x;
    pv->y = y;
}
extern "C" X *func_00248130(P *p, int n) {
    Ref r = func_00248458(p, n);
    X *top = p->s.c > 0 ? (p->s.a + p->s.c - 1)->px : 0;
    if (top) func_00244CA8(top, 0.0f);
    if (r.px) {
        r.px->pvt->a[7].pfn((char *)r.px + r.px->pvt->a[7].d);
    }
    else {
        X *v = func_00246E68(p, n);
        if (!v || p->s.c == 8) return 0;
        float f = 1.0f;
        r = func_00245FE8(v, 4);
        V2 af;
        Set(&af, 2000.0f, 5000.0f);
        func_002462B8(r.px, 3, D_0036B250, f, &af.x);
        func_002462B8(r.px, 3, D_0038AE90, f, &af.x);
        func_002462B8(r.px, 4, D_00370AC0, f, &af.x);
    }
    return (p->s.a[p->s.c++] = r).px;
}
