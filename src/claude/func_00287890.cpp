// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
class CTX { public: CTX(); ~CTX(); int a; };
struct GAME;
extern "C" {
extern struct GAME D_00475480;
extern float D_0032975C;
int func_00287780(void *, void *);
float func_00287828(void *, qword, qword, void *);
void func_0025D0D8(struct GAME *, qword, float, int (*)(void *, void *), void *, int *, void ***);
void *func_00165B28(struct GAME *);
qword func_001672A0(void *, int, void **, int, float (*)(void *, qword, qword, void *), qword, qword, float, float);
}
static inline float Dist(qword a, qword b)
{
    qword d, one;
    float f;
    int n;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "+j"(d), "=&j"(one));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(d));
    __asm__("qmfc2.ni %0,%1" : "=r"(n) : "j"(d));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(n));
    return f;
}
static inline qword ToVF(qword q) { qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(q)); return r; }
extern "C" int func_00287890(void *p, qword pos, qword *out)
{
    int i;
    qword cur = pos;
    for (i = 0; i < 5; i++) {
        CTX ctx; int count; void **list;
        float r = 100.0f;
        qword res;
        qword start;
        start = cur;
        func_0025D0D8(&D_00475480, start, r, func_00287780, p, &count, &list);
        void *g = func_00165B28(&D_00475480);
        // Register pin: start lives in t1 ($9) for the call; the zero-insn keep-alive reads it
        // there so the start reload is scheduled ahead of D_0032975C's lui (sched tie).
        register qword q asm("$9") = start;
        __asm__("" : "+r"(i) : "r"(q));
        res = ToVF(func_001672A0(g, count, list, 0, func_00287828, q, q, 75.0f, D_0032975C));
        cur = res;
        if (r < Dist(res, pos))
            return 0;
        if (Dist(res, start) < 5.0f) {
            *out = res;
            return 1;
        }
    }
    return 0;
}
