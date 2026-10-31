// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VE { short d, pad; void (*pfn)(); };
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } VU_FLOAT(float f, int) { __asm__("mfc1 %0, %1" : "=r"(q) : "f"(f)); } };
struct HIT { qword pos; float x10, x14; int pad18[2]; int kind; int pad24[3]; };
struct XF { float x, y; };
struct JOY { float x, y, z; char padC[0x18 - 0xC]; int grfBtn; char pad1C[0x2C - 0x1C]; VE *pvt; };
struct T300 { char pad[8]; int n; };
struct ACT { char pad[0xC]; VE *pvt; char pad10[0x1A0 - 0x10]; qword v1A0; char pad1B0[0x1BC - 0x1B0]; float x1BC; char pad1C0[0x300 - 0x1C0]; T300 *x300; char pad304[0x1730 - 0x304]; char x1730[0x20]; qword v1750; };
struct S18 { char pad[0x40]; struct { char pad[8]; void *p; } *x40; };
struct S { char pad[0x10]; ACT *pact; char pad14[0x18 - 0x14]; S18 *x18; char pad1C[0x30 - 0x1C]; int state; float t; char pad38[0x40 - 0x38]; int x40; char pad44[0x50 - 0x44]; int x50; };
extern "C" {
extern struct CLOCK { float t; } g_clock;
extern const union QV { float af[4]; qword q; } D_00317530;
float cosf(float);
JOY *func_0015F908(S *);
int func_001A7A80(JOY *, int, float);
int func_002459F8(int);
void func_00244F08(int, int);
ACT *func_001F4A80(ACT *);
void func_00168670(ACT *, int);
int func_002503C8(ACT *, float);
int func_001612D0(S *);
int func_00238AD0(S *);
int func_002502F0(ACT *, float);
int func_00176D40(ACT *, HIT *);
int func_00176960(ACT *, void *);
int func_00238AA8(S *);
void func_00160960(S *, int, HIT *);
float func_00168108(ACT *, float, float, float);
void func_0024E878(ACT *, float);
float func_001611B0(S *);
float func_002A3EE8(float, float);
qword func_0011FD70(float, float, float);
float func_002575C0(ACT *);
qword func_001C94E8(int, ACT *, qword);
float func_0011E3B8(float);
void func_00259678(void *, qword);
void func_0024E8E8(ACT *, qword);
void func_001600F0(S *p);
}
static inline int Btn(JOY *pjoy, int grf, float g) { VE *e = &pjoy->pvt[1]; return ((int (*)(JOY *, int, float))e->pfn)((JOY *)((char *)pjoy + e->d), grf, g); }
static inline void Clear(JOY *pjoy, int grf) { VE *e = &pjoy->pvt[2]; ((void (*)(JOY *, int))e->pfn)((JOY *)((char *)pjoy + e->d), grf); }
static inline XF *Xf(ACT *p) { VE *e = &p->pvt[36]; return ((XF *(*)(ACT *))e->pfn)((ACT *)((char *)p + e->d)); }
static inline qword MulF(qword a, const VU_FLOAT &f) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(f.q)); return r; }
// FMulK/FMulJ: extra "j"(f.q) operands only raise the VU_FLOAT temp's ref count (allocation; no code).
// FMulK: case-11 temp gets caller-saved in vf1; FMulJ: f first so its reload takes vf1.
// FMulE: earlyclobber output so local-alloc does not tie it to w (keeps w spilled, not caller-saved).
static inline qword FMulK(const VU_FLOAT &f, qword a) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(f.q), "j"(f.q), "j"(f.q)); return r; }
static inline qword FMulJ(const VU_FLOAT &f, qword a) { qword r; __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(f.q), "j"(a), "j"(f.q)); return r; }
static inline qword FMulE(const VU_FLOAT &f, qword a) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=&j"(r) : "j"(a), "j"(f.q)); return r; }
static inline qword FMul(const VU_FLOAT &f, qword a) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(f.q)); return r; }

void func_001600F0(S *p)
{
    JOY *pjoy = func_0015F908(p);
    if (func_001A7A80(pjoy, 0x200, 0.15f)) {
        func_00244F08(func_002459F8(0x2A), 0);
        func_00168670(func_001F4A80(p->pact), 0);
    }
    int old;
    do {
        old = p->state;
        switch (old) {
        case 0: case 1: case 2: case 3: case 4: {
            if (func_002503C8(p->pact, 0.1f)) { func_00160960(p, 10, 0); break; }
            if (func_001612D0(p)) { func_00160960(p, 16, 0); break; }
            float g = 0.15f;
            if (func_001A7A80(pjoy, 0x40, g)) { func_00160960(p, 5, 0); break; }
            if (func_001A7A80(pjoy, 0x80, g)) { func_00160960(p, 11, 0); break; }
            if (func_001A7A80(pjoy, 0x20, g)) { func_00160960(p, 18, 0); break; }
            if (0.0f < pjoy->z) {
                switch (p->x40) {
                case 1: func_00160960(p, 1, 0); break;
                case 0:
                    if (0.7f < pjoy->z) func_00160960(p, 4, 0);
                    else func_00160960(p, 3, 0);
                    break;
                }
            } else {
                switch (p->x40) {
                case 1: func_00160960(p, 0, 0); break;
                case 0: func_00160960(p, 2, 0); break;
                }
            }
            break;
        }
        case 5: case 6: case 7: case 8: case 9: case 10: case 19: {
            if (func_00238AD0(p)) { func_00160960(p, 0, 0); break; }
            if (p->state != 7 && Btn(pjoy, 0x40, 0.0f) && !func_002502F0(p->pact, 0.075f)) {
                Clear(pjoy, 0x40);
                func_00160960(p, 7, 0);
                break;
            }
            if (func_001A7A80(pjoy, 0x80, 0.15f)) { func_00160960(p, 11, 0); break; }
            HIT hit;
            if (func_00176D40(p->pact, &hit))
                func_00160960(p, 15, &hit);
            break;
        }
        case 11:
            if (!func_002503C8(p->pact, 0.1f) && func_001A7A80(pjoy, 0x40, 0.15f)) { func_00160960(p, 5, 0); break; }
            if (func_00238AD0(p)) func_00160960(p, 0, 0);
            break;
        case 12:
            if (func_00238AD0(p)) func_00160960(p, 0, 0);
            break;
        case 14:
            func_00238AD0(p);
            break;
        case 15:
            if (func_001A7A80(pjoy, 0x40, 0.15f)) { func_00160960(p, 6, 0); break; }
            if (!func_00176960(p->pact, p->pact->x1730)) func_00160960(p, 10, 0);
            break;
        case 16:
            if (!func_001612D0(p)) { func_00160960(p, 0, 0); break; }
            if (func_002503C8(p->pact, 0.1f)) func_00160960(p, 10, 0);
            break;
        case 17:
            if (func_00238AD0(p)) func_00160960(p, 0, 0);
            break;
        case 20:
            if (0.5f < g_clock.t - p->t) func_00160960(p, 0, 0);
            break;
        case 13:
            if (func_00238AD0(p)) func_00160960(p, 0, 0);
            break;
        case 18:
            if (func_002503C8(p->pact, 0.1f)) { func_00160960(p, 10, 0); break; }
            if (func_001612D0(p)) { func_00160960(p, 16, 0); break; }
            if (!func_00238AA8(p) && p->x50) func_00160960(p, 19, 0);
            break;
        }
    } while (p->state != old);
    ACT *ptarget = func_001F4A80(p->pact);
    switch (p->state) {
    case 3: {
        func_0024E878(p->pact, func_00168108(ptarget, pjoy->x, pjoy->y, p->pact->x1BC));
        p->pact->v1A0 = FMul(VU_FLOAT(-300.0f), D_00317530.q);
        break;
    }
    case 4: {
        func_0024E878(p->pact, func_00168108(ptarget, pjoy->x, pjoy->y, p->pact->x1BC));
        p->pact->v1A0 = FMul(VU_FLOAT(-func_001611B0(p)), D_00317530.q);
        break;
    }
    case 0: case 5: case 6: case 7: case 8: case 9: case 10: case 12: case 19:
        if (p->x40 == 1 && ptarget->x300->n == 2) {
            XF *pxf = Xf(ptarget);
            func_0024E878(p->pact, func_002A3EE8(pxf->y, pxf->x));
        }
        break;
    case 11:
        switch (p->x40) {
        case 1: {
            XF *pxf = Xf(ptarget);
            func_0024E878(p->pact, func_002A3EE8(pxf->y, pxf->x));
            qword v = func_0011FD70(func_00168108(ptarget, pjoy->x, pjoy->y, p->pact->x1BC), pjoy->z * 800.0f, 0.0f);
            ACT *pact = p->pact;
            pact->v1A0 = FMulK(VU_FLOAT(-func_002575C0(pact)), func_001C94E8(0, p->pact, v));
            break;
        }
        case 0:
            func_0024E878(p->pact, func_00168108(ptarget, pjoy->x, pjoy->y, p->pact->x1BC));
            p->pact->v1A0 = MulF(D_00317530.q, VU_FLOAT(pjoy->z * -800.0f));
            break;
        }
        break;
    case 1: {
        XF *pxf = Xf(ptarget);
        float a = func_002A3EE8(pxf->y, pxf->x);
        func_0024E878(p->pact, a);
        float g = func_00168108(ptarget, pjoy->x, pjoy->y, p->pact->x1BC);
        void *pv = p->x18->x40->p;
        float speed = func_001611B0(p);
        float d = func_0011E3B8(g - a);
        if (__builtin_fabsf(d) > 1.5707964f) {
            speed *= 0.8f;
        } else {
            float c = cosf(d);
            speed *= c + (1.0f - c) * 0.8f;
        }
        qword v = func_0011FD70(g, speed, 0.0f);
        qword w = FMulJ(VU_FLOAT(func_002575C0(p->pact), 0), func_001C94E8(0, p->pact, v));
        func_00259678(pv, w);
        p->pact->v1A0 = FMulE(VU_FLOAT(-1.0f), w);
        break;
    }
    case 15:
        func_0024E8E8(p->pact, FMul(VU_FLOAT(-1.0f), p->pact->v1750));
        break;
    case 18:
        if (!p->x50 && !(pjoy->grfBtn & 0x20))
            p->x50 = 1;
        break;
    }
}
