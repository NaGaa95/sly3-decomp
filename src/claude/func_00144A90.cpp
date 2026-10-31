// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct Scope { qword unused_storage; };
struct S {
    char pad00[0xC]; VTE *pvt; char pad10[0x90 - 0x10]; float g90; char pad94[0x194 - 0x94]; int x194; int x198;
    char pad19C[0x20C - 0x19C]; void *p20C; char pad210[0x278 - 0x210]; int x278; char pad27C[0x284 - 0x27C]; float g284;
    char ab288[0x10]; float g298; int x29C; float g2A0; void *p2A4; char pad2A8[0x294 - 0x294];
    char pad2[0x3C0 - 0x2A8]; void *p3C0; char pad3C4[0x41C - 0x3C4]; S *next;
};
struct G { char pad[0x3EB8]; int c; void *ap[1]; };
extern "C" {
extern struct CLOCK { float t; } g_clock;
extern S *D_00479BD4;
extern G D_00475480;
int func_001F4430(S *p);
void *func_002459F8(void *p);
void func_00244F08(void *p, int n);
void func_002261A0(void *p, int n);
int func_0011EE30(void *p, float t);
M4 func_0011D768(M4 *pm);
int func_0027F298(void *p, qword v);
void *func_001F4A80(S *p);
int func_00167F60(void *p, qword pos, qword g);
void func_002BC350(void *p, int n);
int func_00144A90(S *p);
}
struct VU_FLOAT { qword q; VU_FLOAT(const float &f) { __asm__("lw %0, %1" : "=rj"(q) : "m"(f)); } };
static inline M4 *Mat(void *o) { S *s = (S *)o; return ((M4 *(*)(void *))s->pvt[36].pfn)((char *)s + s->pvt[36].d); }
static inline qword Xform4(const M4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(v));
    return r;
}
#define Hit(pv, p, g) func_00167F60(pv, Mat(p)->r[3], (g).q)

int func_00144A90(S *p)
{
    if (g_clock.t < p->g284)
        return 0;
    if (!p->x198) {
        int f = func_001F4430(p) > 0;
        if (!f) {
            if (g_clock.t - p->g2A0 > 0.5f) {
                func_00244F08(func_002459F8(p->p2A4), 0);
                p->g2A0 = g_clock.t;
            }
            if (p->p20C)
                func_002261A0(p->p20C, 0x782);
        }
        return f;
    }
    if (func_0011EE30(p->ab288, g_clock.t))
        return 0;
    if (g_clock.t <= p->g298)
        return p->x29C;
    while (p->g298 < g_clock.t)
        p->g298 += 0.25f;
    p->x29C = 0;
    {
        M4 m0;
        if (*(void **)((char *)p + 0x294))
            m0 = func_0011D768(Mat(*(void **)((char *)p + 0x294)));
        M4 m1;
        if (p->p3C0)
            m1 = func_0011D768(Mat(p->p3C0));
        Scope scope;
        S *o;
        int r;
        for (o = D_00479BD4; o; o = o->next) {
            int f, g;
            if (o->x194 == p->x194)
                continue;
            f = 0;
            if (!o->x198 && p->p3C0) {
                if (func_0027F298(p->p3C0, Xform4(m1, Mat(o)->r[3])))
                    f = Hit(func_001F4A80(o), p, VU_FLOAT(p->g90)) != 0;
            }
            if (f) {
                p->x278 = 1;
                p->x29C = 1;
                goto done;
            }
            g = 0;
            if (*(void **)((char *)p + 0x294)) {
                if (func_0027F298(*(void **)((char *)p + 0x294), Xform4(m0, Mat(o)->r[3])))
                    g = o->x198 != 0;
            }
            if (g) {
                int i;
                for (i = 0; i < D_00475480.c; i++) {
                    void *pv = D_00475480.ap[i];
                    if (Hit(pv, p, VU_FLOAT(p->g90))) {
                        p->x278 = 0;
                        p->x29C = 1;
                        goto done;
                    }
                }
                break;
            }
        }
    done:
        r = p->x29C;
        func_002BC350(&scope, 2);
        return r;
    }
}
