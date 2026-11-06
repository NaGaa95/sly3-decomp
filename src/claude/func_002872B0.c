// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct T { char pad[0x40]; qword pos; int x50; };
struct V { char pad[0x11C0]; };
struct S { char pad[0x130]; int x130; char pad134[0x1F0 - 0x134]; void *x1F0; struct T *x1F4; float g1F8, t1FC; void *x200; };
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
extern qword D_00329740;
extern struct V D_0036E740[];
void *func_001FBE30(void *p, int k);
float func_0011E940(float gLow, float gHigh);
void *func_001F4A80(struct S *p);
qword func_00212FA0(void *o, void *pcm, qword a, qword b, int k);
qword func_001C9428(void *a, void *b, qword q);
void func_00212770(struct T *pt, void *o);
void func_001FE728(void *p, int k);
void func_001A9058(struct V *pv, int k, float g);
void func_00167D38(void *p, int k);
static inline qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
void func_002872B0(struct S *p)
{
    void *o;
    if (g_clock.t < p->t1FC)
        return;
    o = func_001FBE30(p->x1F0, 0);
    if (o) {
        VU v;
        qword r, q;
        struct T *pt;
        float x = func_0011E940(-0.005f, 0.005f);
        float y = func_0011E940(-0.005f, 0.005f);
        q = Make(x, y, 50000.0f);
        v.q = q;
        r = func_00212FA0(o, func_001F4A80(p), D_00329740, q, 0);
        p->x1F4->x50 = 0;
        pt = p->x1F4;
        pt->pos = func_001C9428(0, pt, r);
        func_00212770(p->x1F4, o);
        if (p->x200)
            func_001FE728(p->x200, 1);
        func_001A9058(&D_0036E740[p->x130], 10, 0.05f);
        func_00167D38(func_001F4A80(p), 0);
    }
    p->t1FC = g_clock.t + 1.0f / p->g1F8;
}
