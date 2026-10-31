// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* A26: Dot reads its lane with a qmfc2.ni+mtc1 lane helper so m stays a VU pseudo (fixes the vf4 reload of b). */
/* probe the segment a->b: on a hit return the hit point and its plane, else the plane through b facing a */
typedef int qword __attribute__((mode(TI)));
struct CTX { int a[4]; };
struct HIT { qword pos; qword v10; qword plane; qword v30; qword v40; qword v50; };
extern char D_00475480[];
void func_001D2770(struct CTX *pctx);
void func_001D2798(struct CTX *pctx, int n);
int func_0025CE90();
void func_0025CF18(void *pg, qword a, qword b, int (*pfn)(), int c, int *pn0, int *pn1);
int func_00165000(int n, qword a, qword b, int n0, int n1, struct HIT *phit);
void func_00119ED8(qword *pplane, qword n, float d);
static __inline__ qword Normalize(qword v)
{
    qword m, one, l, r;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(m), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(m));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
static __inline__ float Dot(qword a, qword b)
{
    qword m, one;
    int t;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(m), "=j"(one) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %1, %2\n\tmtc1 %1, %0" : "=f"(g), "=&r"(t) : "j"(m));
    return g;
}
static __inline__ qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
qword func_00134758(qword a, qword b, int c, qword *pplane)
{
    struct CTX ctx;
    struct HIT hit;
    int n0, n1;
    func_001D2770(&ctx);
    func_0025CF18(D_00475480, a, b, func_0025CE90, c, &n0, &n1);
    if (func_00165000(0, a, b, n0, n1, &hit)) {
        b = hit.pos;
        *pplane = hit.plane;
    } else {
        qword n = Normalize(Sub(a, b));
        func_00119ED8(pplane, n, Dot(b, n));
    }
    func_001D2798(&ctx, 2);
    return b;
}
