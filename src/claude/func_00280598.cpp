// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword r[4]; float m[4][4]; } M4;
typedef struct { qword r[3]; } M3;
typedef union { qword q; float f[4]; } V;
struct E { int x0; void *p4; int pad[2]; qword q10; };
struct P { char pad[0x50]; void *x50; char pad1[0x140 - 0x54]; qword q140; char pad2[0x174 - 0x150]; int n174; E *a178; };
extern M3 D_00317490;
extern "C" {
qword func_001C94E8(void *p, int k, qword q);
int func_0027F258(void *p, qword pos);
qword func_001C9428(void *a, void *b, qword pos);
qword *func_002BA818(qword *out, qword value);
void *memset(void *p, int c, unsigned int n);
void func_0028F958(void *p, int k, M4 *pm, M4 *pm2);
qword func_0011D388(M4 *pm);
}
static inline qword Add(const qword &a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline int GetXi(qword q) { int x; __asm__("" : "=r"(x) : "0"(q)); return x; }
static inline float GetY(const qword &q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static inline float GetZ(const qword &q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static inline void StoreX(float *pf, const qword &q) { __asm__("sw %1, %0" : "=m"(*pf) : "r"(q)); }
static inline void SetTrans(M4 *pm, const qword &v)
{
    memset(pm, 0, 0x40);
    StoreX(&pm->m[3][0], v);
    pm->m[3][1] = GetY(v);
    pm->m[3][2] = GetZ(v);
}
static inline void BuildM4(M4 *pm, const M3 *pr, qword pos)
{
    func_002BA818(&pm->r[3], pos);
    *(M3 *)pm = *pr;
}
extern "C" void func_00280598(P *p, qword pos, qword *pout, qword *pq)
{
    V v;
    M4 m;
    M4 m2;
    qword sum;
    int i;
    sum = func_001C94E8(p, 0, p->q140);
    for (i = 0; i < p->n174; i++) {
        if (p->a178[i].p4 && func_0027F258(p->a178[i].p4, pos))
            sum = Add(sum, func_001C94E8(p->a178[i].p4, 0, p->a178[i].q10));
    }
    v.q = func_001C9428(0, p, pos);
    v.f[2] = 0.0f;
    M4 *pm = &m;
    BuildM4(pm, &D_00317490, v.q);
    m.m[2][3] = 0.0f;
    m.m[1][3] = 0.0f;
    m.m[0][3] = 0.0f;
    pm->m[3][3] = 1.0f;
    SetTrans(&m2, sum);
    func_0028F958(p->x50, 0, pm, &m2);
    if (pout)
        *pout = m2.r[3];
    if (pq)
        *pq = func_0011D388(&m2);
}
