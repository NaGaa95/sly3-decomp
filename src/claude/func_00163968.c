// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00163968: two-zone trigger state machine, then a distance-driven parameter (cf. Sly 2 func_001BA608).
typedef int qword __attribute__((mode(TI)));
typedef struct M4 { qword r[4]; } M4;
struct LO;
typedef struct LOV { char pad[0x120]; short d; short p; M4 *(*pfnMat)(struct LO *); } LOV;
typedef struct LO { int a[3]; LOV *pvt; } LO;
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
extern char D_0036C700[];
struct POLY { float c0, c1, c2; };
typedef struct O {
    LO lo;
    char pad10[0x29C - 0x10]; char ab29C[0x1174 - 0x29C];
    float dt; char ab1178[0x1184 - 0x1178]; char ab1184[0x11A0 - 0x1184];
    char ab11A0[0x11B0 - 0x11A0]; float gMin, gMax;
} O;
struct Q1 { char pad[0xB4]; float gB4; };
struct Q2 { char pad[0x38]; float g38; };
typedef struct P { char pad[0x10]; O *po; char pad14[0x30 - 0x14]; int x30; float g34; int pad38; LO *plo; } P;
void func_002389A0(P *p);
int func_00238AA8(P *p);
int func_00238AD0(P *p);
void func_00163C10(P *p, int n);
qword func_001C9428(int k, O *po, qword v);
int func_0011FB88(void *pz, qword v);
void func_001854C8(void *p, int n, void *q);
int func_002533C0(O *po, int n);
void func_0011EAD0(void *p, struct POLY *out, float a, float b);
void *func_002387A8(void *p, int n);
static __inline__ M4 *VMat(LO *plo) { return plo->pvt->pfnMat((LO *)((char *)plo + plo->pvt->d)); }
static __inline__ float Dist(qword a, qword b)
{
    qword d;
    register float f __asm__("$f1"); /* register pin: distance in f1 like the target */
    int t;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(d));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %1, %2" : "=j"(d), "=r"(t) : "0"(d));
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(t));
    return f;
}
static __inline__ float GEval(struct POLY *pp, float x) { return pp->c0 + x * (pp->c1 + x * pp->c2); }
static __inline__ float GClamp(float g, float lo, float hi) { float r; if (g < lo) r = lo; else if (hi < g) r = hi; else r = g; return r; }
void func_00163968(P *p)
{
    int s;
    func_002389A0(p);
    for (;;) {
        if (func_00238AA8(p))
            break;
        s = p->x30;
        switch (s) {
        case 0: {
            void *pz = p->po->ab1184;
            if (!func_0011FB88(pz, func_001C9428(0, p->po, VMat(p->plo)->r[3])))
                func_00163C10(p, 1);
            else if (func_00238AD0(p))
                func_00163C10(p, -1);
            break;
        }
        case 1: {
            void *pz = p->po->ab1178;
            if (func_0011FB88(pz, func_001C9428(0, p->po, VMat(p->plo)->r[3])))
                func_00163C10(p, 0);
            else {
                O *po = p->po;
                if (po->dt <= g_clock.t - p->g34) {
                func_001854C8(D_0036C700, 0x52, po);
                func_00163C10(p, -1);
                }
            }
            break;
        }
        }
        if (s == p->x30)
            break;
    }
    if (p->x30 == 0 && func_002533C0(p->po, 0xE)) {
        struct POLY poly;
        O *po = p->po;
        float d, r;
        qword pos;
        struct Q1 *q1;
        struct Q2 *q2;
        func_0011EAD0(po->ab11A0, &poly, 1.0f / *(float *)po->ab1184, 0.0f);
        pos = VMat(&p->po->lo)->r[3];
        d = Dist(pos, VMat(p->plo)->r[3]);
        po = p->po;
        r = GClamp(GEval(&poly, d), po->gMin, po->gMax);
        q1 = func_002387A8(p->po->ab29C, 0xF0);
        q2 = func_002387A8(p->po->ab29C, 0xDF);
        if (q1)
            q1->gB4 = r;
        else if (q2)
            q2->g38 = r;
    }
}
