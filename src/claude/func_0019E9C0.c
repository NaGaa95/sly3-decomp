// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from the Sly 2 decomp (func_00181F60).
typedef int qword __attribute__((mode(TI)));
struct Q { char pad[0x10]; char x10[0x2C]; float g3c; float g40; float g44; char p1[8]; float g50; float g54; float g58; float g5c; struct Q *next; };
struct E { int a; int b; int c; int d; struct Q *pqFirst; void *pqLast; int ib; int x1c; float g; int oid; float g28; float g2c; };
struct XF { char pad[0x30]; qword q; };
struct VTE { short delta; short pad; struct XF *(*method)(void *); };
struct OBJ { char pad[0xC]; struct VTE *vt; };
struct S { char pad[0x1C8]; struct OBJ *po; int x1cc; char p0[0x1F4 - 0x1D0]; int c; struct E ae[4]; };
struct CLOCK { float t; float dt; };
struct V { float a[4]; };
extern struct CLOCK g_clock;
extern const float D_00322078;
extern char D_00322068[];
void func_0023C660(struct S *p);
struct OBJ *func_0019BC68(struct S *p);
float func_0022DFD8(int oid);
void func_0022EA88(int oid, qword q, int a, int b, struct V *pv, int c, float *pg);
void func_0022EEA0(int oid, qword q, int a, int b, struct V *pv, int c, float *pg, float g);
float func_0011E940(float lo, float hi);
void func_0019E708(struct S *p, struct E *pe);
float func_0011E730(void *pv, float *pg, float a, float b, float c, float dt);
void func_0022E330(int oid, struct Q *q, void *pv, float g);
void func_0019E868(struct S *p, struct Q *q);
#define VCALL(po, n) ((po)->vt[n].method((char *)(po) + (po)->vt[n].delta))
static __inline__ void Integrate(float *px, float *pv, float a, float dt)
{
    float vOld = *pv;
    float vAvg;
    *pv = vOld + dt * a;
    vAvg = (vOld + *pv) * 0.5f;
    *px += dt * vAvg;
}
void func_0019E9C0(struct S *p)
{
    int i;
    struct V v;
    func_0023C660(p);
    if (!p->x1cc) {
        struct OBJ *po = func_0019BC68(p);
        if (po != p->po) {
            int j;
            p->po = po;
            for (j = 0; j < p->c; j++)
                p->ae[j].g2c = D_00322078;
        }
    }
    if (!p->po) return;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        int oid = pe->oid;
        struct Q *q;
        func_0022DFD8(oid);
        if (g_clock.t > pe->g2c) {
            float t;
            func_0022EA88(oid, VCALL(p->po, 0x24)->q, 0, 0, &v, 0, &pe->g28);
            t = g_clock.t;
            pe->g2c = t + func_0011E940(0.5f, 0.75f);
        } else {
            func_0022EEA0(oid, VCALL(p->po, 0x24)->q, 0, 0, &v, 0, &pe->g28, pe->g28);
        }
        func_0019E708(p, pe);
        for (q = pe->pqFirst; q; q = q->next) {
            float a, b;
            q->g3c = func_0011E730(D_00322068, &q->g40, q->g3c, q->g40, q->g44, g_clock.dt);
            func_0022E330(oid, q, q->x10, q->g3c);
            a = -100.0f * q->g50 + -10.0f * q->g58;
            b = -15.0f * q->g54 + -2.5f * q->g5c;
            Integrate(&q->g50, &q->g58, a, g_clock.dt);
            Integrate(&q->g50, &q->g5c, b, g_clock.dt);
            func_0019E868(p, q);
        }
    }
}
