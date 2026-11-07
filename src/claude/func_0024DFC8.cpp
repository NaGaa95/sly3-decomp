// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VEC { float x, y, z, w; } __attribute__((aligned(16)));
struct LO { char pad[0x40]; M4 matrix; };
struct VEL { int n0; VEC *a4; };
struct G { LO *p0; char pad4[0x14 - 4]; VEL *p14; char pad18[0x20 - 0x18]; int n20; char pad24[0x8C - 0x24]; VEC *a8C; };
struct SO { char pad[0x288]; G *p288; G *p28C; };
extern "C" {
extern float D_0036BB9C;
extern qword D_00317560;
extern char D_00327218[];
int func_0024DB68(SO *p);
M4 *func_0011D768(M4 *out, const M4 *in);
M4 *func_0011D558(M4 *out, const M4 *a, const M4 *b);
float func_0011E598(float gCur, float gTarget, float dt, void *psmp, float *pdgNext);
void func_0024DB88(SO *p);
void func_0024DFC8(SO *p, int fSnap);
}
static inline qword Mul(const M4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz ACC, %1, %5x\n\tvmadday.xyz ACC, %2, %5y\n\tvmaddaz.xyz ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(v));
    return r;
}
void func_0024DFC8(SO *p, int fSnap)
{
    M4 m, mInv;
    int i, k;
    VEC *pvSrc, *pv, *pvel;
    float dt;
    if (!func_0024DB68(p)) return;
    {
        G *d = p->p288;
        pvSrc = p->p28C->a8C;
        pvel = d->p14->a4;
        pv = d->a8C;
        func_0011D768(&mInv, &d->p0->matrix);
        func_0011D558(&m, &mInv, &p->p28C->p0->matrix);
    }
    int fDone = 1;
    i = p->p28C->n20;
    dt = D_0036BB9C;
    for (; --i >= 0; pvSrc++, pv++, pvel++) {
        VEC *pt = (VEC *)&mInv;
        *(qword *)pt = Mul(m, *(qword *)&*pvSrc);
        if (fSnap) {
            *(qword *)&*pv = *(qword *)pt;
            *(qword *)&*pvel = D_00317560;
        } else {
            for (k = 0; k < 3; k++) {
                float g = func_0011E598((&pv->x)[k], (&pt->x)[k], dt, D_00327218, 0);
                if (g != (&pt->x)[k]) fDone = 0;
                (&pvel->x)[k] = (g - (&pv->x)[k]) / dt;
            }
        }
    }
    if (fDone) func_0024DB88(p);
}
