// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
union M4 { struct { qword r[4]; } q; float af[4][4]; };
struct LO;
struct LOV { char pad[0x120]; short d; short p; M4 *(*pfnMat)(LO *); };
struct LO { int a[3]; LOV *pvt; };
struct S : LO { char pad[0x1A0 - 0x10]; M4 m1A0; char pad1[0x410 - 0x1E0]; float g410; float g414; };
static inline M4 *VMat(LO *plo) { return plo->pvt->pfnMat((LO *)((char *)plo + plo->pvt->d)); }
extern "C" {
void *func_00292034(void *p, int c, int cb); /* memset */
M4 func_0011D558(M4 *pa, M4 *pb);
void func_00166580(M4 *pm, M4 *pm2, void *pv);
void func_00167E40(S *p, int k, void *pv);
}
void func_00167E40(S *p, int k, void *pv)
{
    float g = 0.0f;
    switch (k) {
    case 1:
        g = p->g410;
        break;
    case 2:
        g = -p->g410;
        break;
    }
    M4 m = *VMat(p);
    M4 mShear;
    M4 *pm = &mShear;
    func_00292034(pm, 0, sizeof(mShear));
    pm->af[3][3] = 1.0f;
    pm->af[2][2] = 1.0f;
    pm->af[1][1] = 1.0f;
    mShear.af[3][0] = g;
    mShear.af[0][0] = 1.0f;
    mShear.af[2][0] = -g / p->g414;
    M4 mRes;
    mRes = func_0011D558(&p->m1A0, pm);
    func_00166580(&m, &mRes, pv);
}
