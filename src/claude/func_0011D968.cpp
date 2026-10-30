// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Gauss-Jordan inverse with column pivoting (Sly 2 FInvertMatrix__FiPfT1 port): (stride c, size n, src, dst).
struct ALLOCREQ { int cb; int cbAlign; };
void *PvAllocSlot(ALLOCREQ *);
extern "C" void CopyAb(void *pvDst, void *pvSrc, int cb);
class CTX { public: CTX(); ~CTX(); int a[4]; };
static inline void *PvAllocMsg(ALLOCREQ *pmsg, int cb, int nKind) { pmsg->cb = cb; pmsg->cbAlign = nKind; return PvAllocSlot(pmsg); }
static inline float GAbs(float g) { return __builtin_fabsf(g); }

extern "C" int func_0011D968(int c, int n, float *pgSrc, float *pgDst)
{
    int fRet = 0;
    CTX frame;
    int i, j, k;
    int cb = n * c * 4;
    ALLOCREQ msg;
    float *a = (float *)PvAllocMsg(&msg, cb, 0x10);
    float gMax, g, f, t;
    CopyAb(a, pgSrc, cb);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            pgDst[i * c + j] = (i == j) ? 1.0f : 0.0f;
    for (i = 0; i < n; i++) {
        j = i;
        gMax = GAbs(a[i * c + i]);
        for (k = i + 1; k < n; k++) {
            f = GAbs(a[i * c + k]);
            if (gMax < f) {
                gMax = f;
                j = k;
            }
        }
        if (gMax < 1e-4f)
            goto LDone;
        if (j != i) {
            for (k = 0; k < n; k++) {
                g = a[k * c + i]; a[k * c + i] = a[k * c + j]; a[k * c + j] = g;
                t = pgDst[k * c + i]; pgDst[k * c + i] = pgDst[k * c + j]; pgDst[k * c + j] = t;
            }
        }
        for (j = i + 1; j < n; j++) {
            f = a[i * c + j] / a[i * c + i];
            for (k = 0; k < n; k++) {
                a[k * c + j] -= f * a[k * c + i];
                pgDst[k * c + j] -= f * pgDst[k * c + i];
            }
        }
    }
    for (i = n - 1; i >= 0; i--) {
        for (j = 0; j < i; j++) {
            f = a[i * c + j] / a[i * c + i];
            for (k = 0; k < n; k++) {
                a[k * c + j] -= f * a[k * c + i];
                pgDst[k * c + j] -= f * pgDst[k * c + i];
            }
        }
    }
    for (i = 0; i < n; i++) {
        f = a[i * c + i];
        for (j = 0; j < n; j++)
            pgDst[j * c + i] /= f;
    }
    fRet = 1;
LDone:
    return fRet;
}
