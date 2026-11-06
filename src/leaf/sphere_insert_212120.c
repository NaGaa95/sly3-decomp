// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct E { union { qword q; struct { float x, y, z, r; } s; } u; float x10; long k:4; long m:8; struct S *child; struct S *next; };
struct S { struct E ae[4]; };
extern float D_00325B80;
typedef struct { char pad[0x45E0]; struct S *ps; } G;
struct S *func_00212098(G *g);
static inline float Min(float a, float b) { return b < a ? b : a; }
static inline float Dist(qword a, qword b)
{
    qword d, t;
    float f;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z\n\tvsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d), "=&j"(t));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
    return f;
}
struct E *func_00212120(G *g, qword pos, float r, float f, int mask)
{
    struct S *psLevel = g->ps;
    struct S *ps;
    struct S *psChild;
    struct E *peFree;
    float best;
    if (!psLevel)
        return 0;
    for (;;) {
        ps = psLevel;
        best = D_00325B80;
        psChild = 0;
        peFree = 0;
        for (;;) {
            unsigned int i;
            for (i = 0; i < 4; i++) {
                struct E *pe = &ps->ae[i];
                switch (pe->k) {
                case 1: {
                    float dist = Dist(pos, pe->u.q), o;
                    if (dist + r <= pe->u.s.r) {
                        o = pe->x10;
                        if (o == 1e10f || dist + f <= o) {
                            if (!(mask & ~pe->m)) {
                                float v = pe->u.s.r * Min(o, 100000.0f) * Min(o, 100000.0f);
                                if (v < best) {
                                    best = v;
                                    psChild = pe->child;
                                }
                            }
                        }
                    }
                    break;
                }
                case -1:
                case 5:
                    if (!peFree)
                        peFree = pe;
                    break;
                }
            }
            if (!ps->ae[3].next)
                break;
            ps = ps->ae[3].next;
        }
        if (!psChild) {
            if (!peFree) {
                ps->ae[3].next = func_00212098(g);
                peFree = ps->ae[3].next->ae;
            }
            peFree->x10 = f;
            peFree->u.q = pos;
            peFree->u.s.r = r;
            peFree->m = mask;
            break;
        }
        psLevel = psChild;
    }
    return peFree;
}
