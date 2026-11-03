// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Checks whether the actor may start the two-handed grab on its owner (same routine as Sly 2 func_001B70A0): owner kind/flag
// tests, the owner's slot state, then the XY distance to the owner against two ranges (300 / 400) with a height window each.
// Allocation note: GetZ keeps the float result in a GPR ("=r"(float) with the qword as a separate "r" input), the idiom of the
// other pextuw helpers; the compiler then emits the qmfc2 / mtc1 moves itself.
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; int (*pfn)(void *, int, float); };
struct Pad { char pad[0x2C]; struct VTE *vt; };
struct O { char pad[0xC]; struct VTE *vt; char pad2[0x1148 - 0x10]; void *x1148; };
struct S { char pad[0x50]; int x50; char pad2[0x5C - 0x54]; void *x5C; };
struct P { char pad[0xC]; struct VTE *vt; char pad2[0x134 - 0x10]; struct Pad *pl; char pad3[0x11B4 - 0x138]; struct O *owner; char pad4[0x188C - 0x11B8]; int x188C; };
int func_0013B500(struct O *po, int n);
int func_002533C0(struct O *po, int n);
int func_001A7A80(void *pl, int k, float g);
struct S *func_002387A8(void *p, int n);
int func_0011EE30(void *p, float g);
void func_0016E118(struct S *p, int n);
void func_001DF838(struct P *p, void *q);
void func_001DE690(struct P *p, int n);
void func_001E1018(struct P *p, int n);
extern char D_00324668[], D_00324670[];
static inline qword LenXY(qword v) {
    qword d;
    __asm__("vmul.xy %0, %1, %1
	vaddy.x %0, %0, %0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt $Q, %1x
	vwaitq
	vaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    return d;
}
/* same as LenXY; the duplicated "j" input raises the reference count of v (allocation only), as in src/game_middle/func_001E6830.cpp */
static inline qword LenXYV(qword v) {
    qword d;
    __asm__("vmul.xy %0, %1, %2
	vaddy.x %0, %0, %0y" : "=j"(d) : "j"(v), "j"(v));
    __asm__("vsqrt $Q, %1x
	vwaitq
	vaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    return d;
}
static inline float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static inline float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static inline qword QwSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Position(void *o) {
    struct VTE *e = &((struct O *)o)->vt[36];
    return ((qword *(*)(void *))e->pfn)((char *)o + e->d)[3];
}
int func_001DF888(struct P *p)
{
    qword d;
    struct S *ps;
    struct O *owner;
    int f, g;
    if (!p->owner)
        return 0;
    if (!func_0013B500(p->owner, 0x3A) || !func_002533C0(p->owner, 0x2A))
        return 0;
    {
        struct VTE *e = &p->pl->vt[1];
        if (!e->pfn((char *)p->pl + e->d, 0xA0, 0.15f))
            return 0;
    }
    owner = p->owner;
    ps = func_002387A8((char *)owner + 0x29C, 0xDA);
    if (ps->x50 >= 3)
        return 0;
    if (ps->x5C != p) {
    ret0:
        return 0;
    }
    f = 0;
    {
        qword a = Position(owner);
        d = QwSub(a, Position(p));
        if (GetX(LenXYV(d)) < 300.0f && func_0011EE30(D_00324668, GetZ(d)) && owner->x1148)
            f = func_001A7A80(p->pl, 0x20, 0.15f) != 0;
    }
    if (f) {
        func_0016E118(ps, 2);
        func_001DF838(p, owner->x1148);
        return 1;
    }
    g = 0;
    if (GetX(LenXY(d)) < 400.0f && func_0011EE30(D_00324670, GetZ(d)) && p->x188C)
        g = func_001A7A80(p->pl, 0x80, 0.15f) != 0;
    if (!g)
        goto ret0;
    func_001DE690(p, 0xC);
    func_001E1018(p, 4);
    return 1;
}
