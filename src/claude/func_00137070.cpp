// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Prototype (px, f, p, g, ...) as in Sly 2 func_001300B8 fixes the f20/f21 choice. The memsets through an inline ClearM4 helper keep &m2/&mB out of gcse; pe at function scope.
typedef int qword __attribute__((mode(TI)));
struct AREQ { int cb; int cbAlign; AREQ(int c, int a) { cb = c; cbAlign = a; } };
class FRAME { public: FRAME(); ~FRAME(); int a[4]; };
struct M4 { qword a[4]; };
struct Y { M4 m; char pad[0x94 - 0x40]; int x94; int pad98[2]; Y *pyNext; };
struct OBJ { virtual void f1(); virtual void f2(); virtual void Eval(float f, float g, qword *pq1, qword *pq2); };
struct ENT { unsigned n : 20; unsigned k : 10; unsigned f30 : 1; unsigned f31 : 1; OBJ *pobj; };
struct X { char pad[0x4C]; int c; ENT *aent; };
extern "C" {
void *func_001D25B0(const AREQ &req);
void *func_00292034(void *pv, int b, int cb);
void func_00136E28(X *px, void *p, ENT *pent, int *pa, Y **ppy);
M4 func_0011D558(M4 *pa, M4 *pb);
M4 func_0028B230(Y *py, qword q);
M4 func_0028B500(Y *py, M4 *pm, qword q1, qword q2);
M4 func_0028B570(Y *py, qword q);
void func_00137070(X *px, float f, void *p, float g, Y *pyFirst, Y *pyLast, M4 *pm1, M4 *pm2);
}
static inline void ClearM4(M4 *pm) { func_00292034(pm, 0, sizeof(M4)); }
static inline M4 AddM4(const M4 &a, const M4 &b) return m
{
    int i;
    for (i = 0; i < 4; i++) {
        qword q;
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(q) : "j"(a.a[i]), "j"(b.a[i]));
        m.a[i] = q;
    }
}
void func_00137070(X *px, float f, void *p, float g, Y *pyFirst, Y *pyLast, M4 *pm1, M4 *pm2)
{
    M4 mA;
    M4 mB;
    M4 m1;
    M4 m2;
    FRAME frame;
    qword aq[2];
    Y **apy;
    int i;
    Y *py;
    ENT *pe;
    ClearM4(&m2);
    {
        float *pg = (float *)&m1;
        func_00292034(pg, 0, sizeof(M4));
        pg[15] = 1.0f; pg[10] = 1.0f; pg[5] = 1.0f; pg[0] = 1.0f;
    }
    apy = (Y **)func_001D25B0(AREQ(px->c * 4, 0x10));
    for (i = 0; i < px->c; i++) {
        pe = &px->aent[i];
        if (pe->f30) {
            apy[i] = 0;
        } else {
            int n;
            func_00136E28(px, p, pe, &n, &apy[i]);
        }
    }
    for (py = pyFirst; py != pyLast; py = py->pyNext) {
        for (i = 0; i < px->c; i++) {
            pe = &px->aent[i];
            if (py == apy[i] && !pe->f31) {
                pe->pobj->Eval(f, g, &aq[0], &aq[1]);
                mA = func_0028B230(py, aq[0]);
                switch (py->x94) {
                case 6: case 7:
                    mB = func_0028B500(py, &mA, aq[0], aq[1]);
                    break;
                default:
                    mB = func_0028B570(py, aq[1]);
                    break;
                }
                goto found;
            }
        }
        mA = py->m;
        ClearM4(&mB);
    found:
        {
            m2 = AddM4(func_0011D558(&mA, &m2), func_0011D558(&mB, &m1));
            m1 = func_0011D558(&mA, &m1);
        }
    }
    if (pm1) *pm1 = m1;
    if (pm2) *pm2 = m2;
}
