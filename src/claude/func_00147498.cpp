// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00147498 (A30): camera-mode update, written from the target. Stick/state picks gx/gy, the 3x3 tent weights
// (max(0,-g), 1-|g|, max(0,g)) blend the D_00342D20 offset table into acc (spilled at 0xF0), optional D_00317530 term,
// stiffness lerped by a CLQ/LM of the XY distance, spring step func_00147410, then either a look-dir M4 or a look-at.
// Keys: AddScaled takes the table vector as const qword & (load after the VU_FLOAT home store); M4 built through an
// explicit pm4 pointer (16C280 style; pm4 assigned after the M3 call in the else block); mtc1-only GetX after the vsqrt
// asm (reload emits the qmfc2); 'if (x2B8 == 0) {...} else zero'; k0 computed before k1.
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
union M4 { struct { qword r[4]; } q; M3 m3; float af[4][4]; };
struct V4 { float x, y, z, w; } __attribute__((aligned(16)));
struct CLQ { float g0, g1, g2, gUnused; };
struct LM { float gMin, gMax; };
struct VTE { short d; short pad; void *pfn; };
struct CM;
struct H { float g0, g4, g8, gC, g10; };
struct S { char pad[0x134]; H *p134; };
struct Q {
    char pad0[0xC]; VTE *pvt; char pad10[0x134 - 0x10]; H *p134; char pad138[0x2A8 - 0x138];
    float g2A8; float g2AC; char pad2B0[0x2B8 - 0x2B0]; int x2B8; int pad2BC; int x2C0; char pad2C4[0x2D8 - 0x2C4];
    int x2D8; char pad2DC[0x2F4 - 0x2DC]; int x2F4; char pad2F8[0x410 - 0x2F8]; int x410; int pad414; int x418;
    char pad41C[0x4BC - 0x41C]; S *p4BC;
};
struct P { CM *pcm; char pad4[0x20 - 4]; Q *pq; char pad24[0x30 - 0x24]; qword v30; qword v40; };
extern "C" {
extern struct CLOCK { float t; float dt; } g_clock;
extern qword D_00342D20[3][3];
extern qword D_00317530;
extern qword D_00317550;
extern qword D_00317560;
extern LM D_00341FF0;
void func_00169E78(P *p);
float GLimitAbs(float g, float gMax) __asm__("GLimitAbs__Fff");
qword func_001678C8(CM *pcm, qword v);
void func_00147410(qword posGoal, qword velGoal, qword *ppos, qword *pvel, float k1, float k0, float dt);
qword func_001C9428(Q *q, int n, qword v);
qword func_00142D20(Q *q);
M3 func_0011CBF0(qword a, qword b);
qword *func_002BA818(qword *p, qword v);
void func_00166DE8(CM *p, M4 *pm);
qword func_001C9828(M4 *pm, int n, qword v);
void func_00166E48(CM *p, qword pos, qword tgt, float da, float db);
void func_00147498(P *p);
}
static const CLQ s_clq = { 2.0f, -4.0f, 0.0f, 0.0f };
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); }
    VU_FLOAT(const float *pg) { __asm__("qmtc2.ni %1, %0" : "=j,j"(q) : "r,V"(*(const int *)pg)); }
};
static inline qword AddScaled(qword a, const qword &b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
static inline qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword Zero() { qword q; __asm__("vsub.xyzw %0, $vf0, $vf0" : "=j"(q)); return q; }
static inline float LenXY(qword v)
{
    qword d; float f;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(d) : "j"(d));
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(d));
    return f;
}
static inline M4 *Matrix(Q *p) { VTE *e = &p->pvt[36]; return ((M4 *(*)(void *))e->pfn)((char *)p + e->d); }
static inline float GMax(float a, float b) { return a > b ? a : b; }
static inline float GEvalClq(const CLQ *pclq, float g) { return pclq->g0 + g * (pclq->g1 + g * pclq->g2); }
static inline float GLimit(const LM *plm, float g)
{
    float lo = plm->gMin, hi = plm->gMax;
    if (g < lo) return lo;
    if (hi < g) return hi;
    return g;
}

void func_00147498(P *p)
{
    float gx, gy;
    func_00169E78(p);
    switch (p->pq->x2F4) {
    case 0:
    case 1:
        gx = 0.0f;
        gy = -0.75f;
        break;
    case 2:
        gx = 0.0f;
        gy = 0.75f;
        break;
    default:
        if (p->pq->x2B8 == 0) {
            if (p->pq->p4BC && p->pq->p4BC->p134) {
                gx = GLimitAbs(p->pq->p4BC->p134->gC, 1.0f);
                gy = GLimitAbs(p->pq->p4BC->p134->g10, 1.0f);
            } else {
                gx = GLimitAbs(p->pq->p134->g0, 1.0f);
                gy = GLimitAbs(p->pq->p134->g4, 1.0f);
            }
        } else {
            gx = gy = 0.0f;
        }
        break;
    }
    float ax[3], ay[3];
    ax[0] = GMax(-gx, 0.0f);
    ax[1] = 1.0f - __builtin_fabsf(gx);
    ax[2] = GMax(gx, 0.0f);
    ay[0] = GMax(-gy, 0.0f);
    ay[1] = 1.0f - __builtin_fabsf(gy);
    ay[2] = GMax(gy, 0.0f);
    qword acc = Zero();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            acc = AddScaled(acc, D_00342D20[i][j], VU_FLOAT(ax[i] * ay[j]));
    if (p->pq->x410)
        acc = AddScaled(acc, D_00317530, VU_FLOAT(&p->pq->g2A8));
    else if (p->pq->x418)
        acc = AddScaled(acc, D_00317530, VU_FLOAT(&p->pq->g2AC));
    qword v = func_001678C8(p->pcm, Matrix(p->pq)->q.r[3]);
    float t = GLimit(&D_00341FF0, GEvalClq(&s_clq, LenXY(v)));
    float u = 1.0f - t;
    float k0 = u * 8.0f + t * 20.0f;
    float k1 = u * 4.0f + t * 6.0f;
    func_00147410(acc, D_00317560, &p->v30, &p->v40, k1, k0, g_clock.dt);
    Q *q = p->pq;
    if ((unsigned)(q->x2B8 - 3) < 3 && q->x2C0 && !q->x2D8) {
        V4 v, w;
        *(qword *)&v = func_001C9428(q, 0, p->v30);
        *(qword *)&w = func_00142D20(p->pq);
        M3 m3;
        V4 d;
        *(qword *)&d = Sub(*(qword *)&w, *(qword *)&v);
        m3 = func_0011CBF0(*(qword *)&d, Matrix(p->pq)->q.r[2]);
        M4 m4;
        M4 *pm4 = &m4;
        func_002BA818(&pm4->q.r[3], *(qword *)&v);
        pm4->q.r[0] = m3.r[0];
        pm4->q.r[1] = m3.r[1];
        pm4->q.r[2] = m3.r[2];
        m4.af[2][3] = 0.0f;
        m4.af[1][3] = 0.0f;
        m4.af[0][3] = 0.0f;
        pm4->af[3][3] = 1.0f;
        func_00166DE8(p->pcm, pm4);
    } else {
        M4 m4;
        M4 *pm4;
        {
            M3 m3 = func_0011CBF0(Matrix(q)->q.r[0], D_00317550);
            pm4 = &m4;
            qword pos = Matrix(p->pq)->q.r[3];
            func_002BA818(&pm4->q.r[3], pos);
            pm4->q.r[0] = m3.r[0];
            pm4->q.r[1] = m3.r[1];
            pm4->q.r[2] = m3.r[2];
            m4.af[2][3] = 0.0f;
            m4.af[1][3] = 0.0f;
            m4.af[0][3] = 0.0f;
            pm4->af[3][3] = 1.0f;
        }
        V4 v, w;
        *(qword *)&v = func_001C9828(pm4, 0, p->v30);
        *(qword *)&w = func_00142D20(p->pq);
        func_00166E48(p->pcm, *(qword *)&v, *(qword *)&w, 0.0f, 0.0f);
    }
}
