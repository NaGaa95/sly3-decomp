// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-thread-jumps
// SLY3_ASFIX: engine-divfix1
// func_0027C2F8 (A62/A66): per-wheel suspension/steer update of the car (4 wheels): ground snap via func_0027AD80,
// GSmooth spin, wheel matrix = rotZ(steer) * rotX(spin) through the Sly 2 NRV MATRIX3 operator* (per-row stores), then
// the wheel actor's teleport/rotation and skid sound. Clamp inline with the divisor as its own local.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int n[4]; };
struct M3 { U r[3]; };
struct M4 { U r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct SMP { float a, b, c; };
struct XFO { M4 m; char pad40[0x70 - 0x40]; qword q70; char pad80[0xA0 - 0x80]; void *pA0; int nA4; };
struct HIT { char pad[0x10]; qword q10; char pad20[0x90 - 0x20]; float g90; };
struct ACT { char pad[0xC]; VTE *pvt; };
struct SND { char pad[0x40]; float g40, g44; };
struct DRV { char pad[0x68]; float g68; };
struct REFO { char pad[0xC]; VTE *pvt; };
struct WHEEL {
    XFO *pxf; int pad4; float g8; float gC; float g10; float g14; char pad18[0x48 - 0x18]; float g48;
    char pad4C[0x50 - 0x4C]; ACT *pact; char pad54[0x60 - 0x54];
};
struct PL { char pad[0x60]; qword q60; };
struct CAR {
    char pad0[0xC]; VTE *pvt; char pad10[0x50 - 0x10]; PL *p50; char pad54[0x190 - 0x54]; WHEEL aw[4];
    char pad310[0x32C - 0x310]; float g32C; float g330; char pad334[0x33C - 0x334]; float g33C;
    char pad340[0x3C4 - 0x340]; float g3C4;
};
struct SW { char pad[0x44F4]; int n44F4; };
struct CLOCK { float t; float dt; };
extern "C" {
extern SW D_00475480;
extern float D_0036BB9C;
extern qword D_00317540, D_00317550;
extern const SMP D_00329428, D_00329438, D_00329448;
qword func_001C94E8(void *, CAR *, qword);
qword func_0028E910(void *, void *, qword);
HIT *func_0027AD80(CAR *, WHEEL *);
float GSmooth(float, float, float, const SMP *, float *) __asm__("GSmooth__FfffP3SMPPf");
float func_0011E3B8(float);
M3 func_0011C8C0(qword, float) __asm__("func_0011C8C0");
qword *func_002BA818(qword *, qword);
DRV *func_001FE9B8(ACT *);
void *func_001FE950(ACT *, int);
void func_002BEBD0(REFO **, void *);
qword func_0028E990(void *, void *, qword);
M3 func_0011CBA0(qword) __asm__("func_0011CBA0");
SND *func_001FD6A0(REFO *, int);
void func_0028E768(CAR *);
void func_0023CC40(CAR *);
void func_0027C2F8(CAR *p);
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
static inline qword Velocity(CAR *p) { VTE *e = &p->pvt[38]; return ((qword (*)(void *))e->pfn)((char *)p + e->d); }
static inline void Teleport(ACT *p, qword v) { VTE *e = &p->pvt[34]; ((void (*)(void *, qword))e->pfn)((char *)p + e->d, v); }
static inline void SetRot(ACT *p, M3 *pm) { VTE *e = &p->pvt[35]; ((void (*)(void *, M3 *))e->pfn)((char *)p + e->d, pm); }
static inline void Release(REFO *p) { VTE *e = &p->pvt[2]; ((void (*)(void *))e->pfn)((char *)p + e->d); }
struct SPREF { REFO *p; char pad[12]; void Clear() { if (p) Release(p); } };
struct VU_VECTOR4 { qword qw; };
inline M3 operator*(const M3 &matL, const M3 &matR) return mat
{
    qword qwL0 = matL.r[0].q;
    qword qwL1 = matL.r[1].q;
    qword qwL2 = matL.r[2].q;
    VU_VECTOR4 v0;
    VU_VECTOR4 v1;
    VU_VECTOR4 v2;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v0.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)&matR.r[0])->qw));
    *(VU_VECTOR4 *)&mat.r[0] = v0;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v1.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)&matR.r[1])->qw));
    *(VU_VECTOR4 *)&mat.r[1] = v1;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v2.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)&matR.r[2])->qw));
    *(VU_VECTOR4 *)&mat.r[2] = v2;
}
static inline float Clamp(float v, float low, float high) { if (v < low) return low; else if (high < v) return high; else return v; }
static inline qword Cross(qword a, qword b)
{
    qword r;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword operator*(qword v, VU_FLOAT f) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(f.q)); return r; }

void func_0027C2F8(CAR *p)
{
    U vl;
    vl.q = func_001C94E8(0, p, Velocity(p));
    for (unsigned int i = 0; i < 4; i++) {
        WHEEL *pw = &p->aw[i];
        U pos;
        pos.q = func_0028E910(0, p->p50, pw->pxf->q70);
        HIT *hit = func_0027AD80(p, pw);
        float z;
        if (hit) {
            float h = pw->g48 + hit->g90;
            if (pos.f[2] < h) {
                pos.f[2] = h;
                goto lifted;
            }
            z = h;
        } else {
            z = pw->g48;
        }
        GSmooth(pos.f[2], z, D_0036BB9C, &D_00329428, 0);
        pos.f[2] = z;
    lifted:
        pos.q = func_0028E910(p->p50, pw->pxf->pA0, pos.q);
        float g;
        if ((int)i < 2)
            g = 0.0f;
        else
            g = p->g33C / pw->g14;
        if (hit) {
            float w = vl.f[0] / pw->g14;
            if ((int)i >= 2)
                w += p->g3C4;
            if ((0.0f < g && w < g * 0.25f) || (g < 0.0f && g * 0.25f < w))
                pw->gC = GSmooth(pw->gC, g * 0.25f, D_0036BB9C, &D_00329438, 0);
            else
                pw->gC = w;
        } else {
            float target = g;
            if ((int)i >= 2)
                target += p->g3C4;
            float dt = D_0036BB9C;
            const SMP *psmp = __builtin_fabsf(pw->gC) < __builtin_fabsf(g) ? &D_00329438 : &D_00329448;
            pw->gC = GSmooth(pw->gC, target, dt, psmp, 0);
        }
        pw->g10 = func_0011E3B8(pw->g10 + pw->gC * D_0036BB9C);
        M3 m;
        m = func_0011C8C0(D_00317550, pw->g8) * func_0011C8C0(D_00317540, pw->g10);
        XFO *pxf = pw->pxf;
        func_002BA818(&pxf->m.r[3].q, pos.q);
        pxf->m.r[0] = m.r[0];
        pxf->m.r[1] = m.r[1];
        pxf->m.r[2] = m.r[2];
        pxf->m.r[3].f[3] = 1.0f;
        pxf->m.r[1].n[3] = 0;
        pxf->m.r[0].n[3] = 0;
        pxf->m.r[2].n[3] = 0;
        int stamp = ++D_00475480.n44F4;
        pw->pxf->nA4 = stamp;
        ACT *pact = pw->pact;
        if (pact) {
            SPREF ref;
            ref.p = 0;
            DRV *pdrv = func_001FE9B8(pact);
            void *pv = func_001FE950(pact, 0x774);
            func_002BEBD0(&ref.p, pv);
            if (pdrv && ref.p) {
                if (hit) {
                    M3 mr;
                    Teleport(pact, hit->q10);
                    qword t = func_0028E990(pw->pxf, 0, m.r[1].q);
                    qword d = Cross(p->p50->q60, t);
                    if (pw->gC < 0.0f)
                        d = d * VU_FLOAT(-1.0f);
                    mr = func_0011CBA0(d);
                    SetRot(pact, &mr);
                    float a = __builtin_fabsf(pw->g14 * pw->gC);
                    SND *psnd = func_001FD6A0(ref.p, 1);
                    psnd->g40 = a * 0.9f;
                    psnd->g44 = a * 1.1f;
                    float m = pw->gC < 0.0f ? p->g330 : p->g32C;
                    pdrv->g68 = Clamp(a / m, 0.0f, 1.0f);
                } else {
                    pdrv->g68 = 0.0f;
                }
            }
            ref.Clear();
        }
    }
    func_0028E768(p);
    func_0023CC40(p);
}
