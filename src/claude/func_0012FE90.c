// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from the matched Sly 2 source src/hand/func_0012DA30.c; Sly 3 builds this unit with -Os.
// The duplicate "j"(dv) input on the first vadd emits nothing (allocation-only): it puts dv in the VU class so it is
// spilled to 0(sp) across the calls as in the target.
typedef int qword __attribute__((mode(TI)));
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
int func_0011E9F0(float a, float b, float eps);
void func_0028F260(void *pv, void *px);
struct X { char pad[0x90]; void *p90; char pad2[0xC0 - 0x94]; qword vC0; qword vD0; qword vE0; };
struct P { int x0; void *x4; struct X *x8; int xC; int pad[4]; qword v20; };
extern qword D_00317560;
static __inline__ int FVecsNear(qword a, qword b)
{
    return func_0011E9F0(GetX(a), GetX(b), 1e-4f) && func_0011E9F0(GetY(a), GetY(b), 1e-4f) &&
           func_0011E9F0(GetZ(a), GetZ(b), 1e-4f);
}
void func_0012FE90(struct P *p, qword v)
{
    qword dv;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(dv) : "j"(v), "j"(p->v20));
    p->v20 = v;
    if (p->x8->p90 == p && !FVecsNear(D_00317560, dv)) {
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(p->x8->vC0) : "j"(p->x8->vC0), "j"(dv), "j"(dv));
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(p->x8->vE0) : "j"(p->x8->vE0), "j"(dv));
        func_0028F260(p->x4, p->x8);
    }
}
