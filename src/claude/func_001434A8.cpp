// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct P;
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x120]; VTE e120; char pad2[0x140 - 0x128]; VTE e140; };
struct P {
    char pad[0xC]; VT *pvt; char pad1[0x1B0 - 0x10]; float g1B0; char pad2[0x1E0 - 0x1B4]; float g1E0;
    char pad3[0x2C0 - 0x1E4]; int x2C0; int x2C4; float g2C8; int pad2CC; float g2D0; float g2D4; int x2D8;
    char pad4[0x400 - 0x2DC]; float g400;
};
extern "C" {
extern struct CLOCK { float t; } g_clock;
extern qword D_00317560;
void func_001434A8(P *p, int st);
}
/* "=rj": the lw value is VF-class, so it is spilled across the call and reloaded with lqc2 like the target */
struct VU_FLOAT { qword q; VU_FLOAT(const float &f) { __asm__("lw %0, %1" : "=rj"(q) : "m"(f)); } };
static inline qword Scale(VU_FLOAT s, qword a) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s.q)); return r; }
typedef qword *(*PFNV)(void *);
typedef void (*PFNS)(void *, qword);

void func_001434A8(P *p, int st)
{
    if (st == p->x2C0)
        return;
    if (p->x2C0 == 2) {
        VT *vt = p->pvt;
        VTE *e = &vt->e140;
        void *po = (char *)p + e->d;
        ((PFNS)e->pfn)(po, Scale(VU_FLOAT(p->g400), *((PFNV)vt->e120.pfn)((char *)p + vt->e120.d)));
    }
    p->x2C4 = p->x2C0;
    p->x2C0 = st;
    p->g2C8 = g_clock.t;
    p->x2D8 = 0;
    switch (st) {
    case 0: {
        float g = -p->g1E0;
        p->g2D0 = g;
        p->g2D4 = __builtin_fabsf(g) / p->g1B0 * 0.6f;
        break;
    }
    case 1:
        p->g2D4 = __builtin_fabsf(p->g2D0) * 0.135281697f;
        break;
    case 2:
        p->g2D4 = __builtin_fabsf(p->g2D0) * 0.397887349f;
        ((PFNS)p->pvt->e140.pfn)((char *)p + p->pvt->e140.d, D_00317560);
        break;
    }
}
