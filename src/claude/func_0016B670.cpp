// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta, pad; void *fn; };
struct LO { char pad0[0xC]; VTE *vt; };
struct M3 { qword r[3]; };
union M4 { qword r[4]; float af[4][4]; };
struct CP {
    qword pos;
    qword rot;
    float g20;
    float g24;
    float g28;
    unsigned int flags;
    LO *plo30;
    LO *plo34;
    int pad38[2];
    qword pos40;
};
struct CAM { void *owner; char pad4[0x160 - 4]; CP *pcp; float t0; void *p168; };
struct CLOCK { float t, dt; };
extern "C" {
extern CLOCK D_0036BB98, D_0036BBD8;
extern qword D_00344850, D_00344860, D_00344870;
void func_00169E78(CAM *);
qword func_001C9428(LO *, void *, qword);
qword func_0011D3C0(M3 *);
void func_0011CBA0(M3 *, qword);
float func_0011E3B8(float);
void func_0011C9E8(M3 *, qword);
qword *func_002BA818(qword *, qword);
void func_00166DE8(void *, M4 *);
void func_00167960(void *, float);
void func_0016B670(CAM *);
}
static inline float GetX(qword q) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(q)); return f; }
static inline float GetY(qword q) { float f; __asm__("prot3w %0,%1" : "=r"(f) : "r"(q)); return f; }
static inline float GetZ(qword q) { float f; __asm__("pextuw %0,$0,%1" : "=r"(f) : "r"(q)); return f; }
struct VECTOR {
    qword q;
    VECTOR() {}
    VECTOR(float x, float y, float z)
    {
        qword t;
        __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
                : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    }
};
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); }
};
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline float Dot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(d), "=&j"(one) : "j"(a), "j"(b));
    float f;
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(d));
    return f;
}
// The operands are read as plain qword lvalues (not VECTOR members) so they may alias the VU_FLOAT temp home
// stores, which orders each load after the previous temp store like the target.
static inline qword Lerp(const VECTOR &a, const VECTOR &b, float u)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %1, %2x\n\tvmaddx.xyzw %0, %3, %4x" : "=j"(r) : "j"(*(const qword *)&a), "j"(VU_FLOAT(1.0f - u).q), "j"(*(const qword *)&b), "j"(VU_FLOAT(u).q));
    return r;
}
static inline float Clamp(float value, float low, float high)
{
    if (value < low) return low;
    if (high < value) return high;
    return value;
}
static inline float Now(CAM *self) { return self->p168 ? D_0036BBD8.t : D_0036BB98.t; }
static inline M3 *Mat(LO *p) { VTE *e = &p->vt[36]; return ((M3 *(*)(void *))e->fn)((char *)p + e->delta); }
// Catmull-Rom style tangent of row b (rows a, b, c are the previous / this / next key) over the key durations.
// The rows are formed inside Tangent after its tests: rows other than p[0] then use a non-invariant base in loop.c
// (recomputed t1+4j per block) while p[0] stays the one reduced giv, like the target.
static inline float Slope(CP *pc, float *a, float *b, float *c, int j)
{
    return ((b[j] - a[j]) / pc[-1].g28 + (c[j] - b[j]) / pc->g28) * 0.5f;
}
static inline float Tangent(CP *pc, float (*p)[7], int k, int j)
{
    if (pc[-1].g28 <= 0.0f || pc->g28 <= 0.0f || (pc->flags & 0x100))
        return 0.0f;
    return Slope(pc, p[k - 1], p[k], p[k + 1], j);
}
static inline float Herm(float *a, float *b, int j, float h00, float h01, float m0, float h10, float m1, float h11)
{
    return a[j] * h00 + b[j] * h01 + m0 * h10 + m1 * h11;
}

void func_0016B670(CAM *self)
{
    func_00169E78(self);
    CP *pcp = self->pcp;
    unsigned int flags1 = pcp[1].flags;
    unsigned int flags = pcp->flags;
    float u;
    if (flags & 0x10) {
        u = 0.0f;
    } else if (Now(self) - self->t0 < pcp->g24 || pcp->g28 <= 0.0f) {
        u = 0.0f;
    } else {
        u = Clamp((Now(self) - (self->t0 + self->pcp->g24)) / self->pcp->g28, 0.0f, 1.0f);
        if (flags & 0xE) {
            VECTOR v(u * u * u, u * u, u);
            qword *pc;
            if (flags & 2)
                pc = &D_00344850;
            else if (flags & 4)
                pc = &D_00344860;
            else
                pc = &D_00344870;
            u = Clamp(Dot(v.q, *pc), 0.0f, 1.0f);
        }
    }
    VECTOR aPos[4];
    VECTOR aRot[4];
    VECTOR *pq = &aPos[1];
    VECTOR *pp = &aRot[1];
    int i;
    for (i = -1; i < 3; i++) {
        CP *pc = &self->pcp[i];
        LO *plo = pc->plo30;
        LO *ploAim = pc->plo34;
        if (plo) {
            pq[i].q = func_001C9428(plo, 0, pc->pos);
            pp[i].q = func_0011D3C0(Mat(plo));
        } else {
            pq[i].q = pc->pos;
            pp[i].q = pc->rot;
        }
        if (ploAim) {
            M3 m;
            qword aim = func_001C9428(ploAim, 0, pc->pos40);
            func_0011CBA0(&m, Sub(aim, pq[i].q));
            qword e = func_0011D3C0(&m);
            pp[i] = VECTOR(GetX(pp[i].q), GetY(e), GetZ(e));
        }
    }
    int j;
    for (i = -1; i < 2; i = j) {
        j = i + 1;
        float x = GetX(pp[i].q);
        x += func_0011E3B8(GetX(pp[j].q) - x);
        float y = GetY(pp[i].q);
        y += func_0011E3B8(GetY(pp[j].q) - y);
        float z = GetZ(pp[i].q);
        z += func_0011E3B8(GetZ(pp[j].q) - z);
        pp[j] = VECTOR(x, y, z);
    }
    qword pos, rot;
    float fov;
    if ((flags & 0x80) && (flags1 & 0x80) && !(flags & 0xF)) {
        float res[7];
        float rec[4][7];
        float (*pr)[7] = &rec[1];
        for (i = -1; i < 3; i++) {
            __asm__("sw %1,%0" : "=m"(pr[i][0]) : "r"(pq[i].q));
            pr[i][1] = GetY(pq[i].q);
            pr[i][2] = GetZ(pq[i].q);
            __asm__("sw %1,%0" : "=m"(pr[i][3]) : "r"(pp[i].q));
            pr[i][4] = GetY(pp[i].q);
            pr[i][5] = GetZ(pp[i].q);
            pr[i][6] = self->pcp[i].g20;
        }
        float u2 = u * u;
        float u3 = u2 * u;
        CP *pc = self->pcp;
        float h00 = u3 + u3 - u2 * 3.0f + 1.0f;
        float h10 = (u3 - (u2 + u2) + u) * pc[0].g28;
        float h01 = u2 * 3.0f - (u3 + u3);
        float h11 = (u3 - u2) * pc[1].g28;
        for (j = 0; j < sizeof(res) / sizeof(res[0]); j++) {
            CP *pcj = self->pcp;
            float m0 = Tangent(pcj, pr, 0, j);
            float m1 = Tangent(pcj + 1, pr, 1, j);
            res[j] = Herm(pr[0], pr[1], j, h00, h01, m0, h10, m1, h11);
        }
        pos = VECTOR(res[0], res[1], res[2]).q;
        fov = res[6];
        rot = VECTOR(res[3], res[4], res[5]).q;
    } else {
        fov = (1.0f - u) * self->pcp[0].g20 + u * self->pcp[1].g20;
        pos = Lerp(pq[0], pq[1], u);
        rot = Lerp(pp[0], pp[1], u);
    }
    M4 m4;
    M3 m;
    func_0011C9E8(&m, rot);
    {
        M4 *pm4 = &m4;
        func_002BA818(&pm4->r[3], pos);
        pm4->r[0] = m.r[0];
        pm4->r[1] = m.r[1];
        pm4->r[2] = m.r[2];
        m4.af[2][3] = 0.0f;
        m4.af[1][3] = 0.0f;
        m4.af[0][3] = 0.0f;
        pm4->af[3][3] = 1.0f;
        func_00166DE8(self->owner, pm4);
        func_00167960(self->owner, fov);
    }
}
