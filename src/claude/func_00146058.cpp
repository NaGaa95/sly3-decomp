// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// The first func_0011EE68 call is written in each arm (target cross-jumps the shared div/call tail, leaving lui a0 in both arms).
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x120]; VTE e120; };
struct ANIM { char pad[0x64]; float g64; };
struct AS { char pad[0x14]; ANIM *panim; };
struct SO {
    char pad[0xC]; VT *pvt; char pad1[0x90 - 0x10]; float g90; char pad2[0x194 - 0x94]; int x194;
    char pad3[0x41C - 0x198]; SO *pnext;
};
struct CAM { char pad[0x70]; qword q70; char pad1[0xA0 - 0x80]; int xA0; };
struct TGT { char pad[0x8]; CAM *pcam; char pad1[0x50 - 0xC]; float lm50[2]; float lm58[2]; float g60; char pad2[0x70 - 0x64]; SO *p70; };
struct P {
    char pad[0xC]; VT *pvt; char pad1[0x194 - 0x10]; int x194; char pad2[0x1AC - 0x198]; float g1AC; float g1B0;
    char pad3[0x1E0 - 0x1B4]; float g1E0; float g1E4; char pad4[0x214 - 0x1E8]; void *p214; ANIM *a218; ANIM *a21C;
    ANIM *a220; ANIM *a224; AS *p228; char pad5[0x2B0 - 0x22C]; int x2B0; char pad6[0x3FC - 0x2B4]; float t3FC;
};
struct Scope { unsigned char unused_storage[16]; };
struct VU_FLOAT { qword q; VU_FLOAT(const float &f) { __asm__("lw %0, %1" : "=rj"(q) : "m"(f)); } };
extern "C" {
extern struct CLOCK { float t; } g_clock;
extern char D_00341FF8[], D_00341FF0[];
extern SO *D_00479BD4;
void func_00137588(ANIM *, void *, int, AS **, float, float);
float func_0011EE68(void *, float);
void func_00137D08(AS *, int, int, float, float);
TGT *func_0023FBE8(void *, int);
void *func_001F4A80(P *);
int func_00167F60(void *, qword, VU_FLOAT);
qword func_0028E990(int, int, qword);
void func_00120BA8(qword, float *, float *, float *);
int func_0011EE30(float *, float);
void func_002BC350(void *, int);
void func_00146058(P *p);
}
static inline M4 *Matrix(void *pv) { SO *p = (SO *)pv; VTE *e = &p->pvt->e120; return ((M4 *(*)(void *))e->pfn)((char *)p + e->d); }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }

void func_00146058(P *p)
{
    ANIM *pcur, *pnew;
    int flags;
    float gx, gy;
    if (!p->p214)
        return;
    pcur = p->p228 ? p->p228->panim : 0;
    gx = __builtin_fabsf(p->g1E0);
    flags = 1;
    gy = __builtin_fabsf(p->g1E4);
    if (p->x2B0 == 3) {
        pnew = p->a224;
        flags = 9;
    } else if (gx < 0.2f && gy < 0.2f) {
        pnew = p->a218;
        flags = 9;
    } else if (gx < gy) {
        pnew = p->a220;
    } else {
        pnew = p->a21C;
    }
    if (pnew != pcur)
        func_00137588(pnew, p->p214, flags, &p->p228, 0.0f, 1.0f);
    if (p->p228) {
        float u;
        if (p->p228->panim == p->a220) {
            u = func_0011EE68(D_00341FF8, p->g1E4 / p->g1AC);
        } else {
            if (p->p228->panim != p->a21C)
                goto skip;
            u = func_0011EE68(D_00341FF8, p->g1E0 / p->g1B0);
        }
        u = func_0011EE68(D_00341FF0, (u + 1.0f) * 0.5f);
        func_00137D08(p->p228, 0, 0, u * p->p228->panim->g64, 0.0f);
    }
skip:
    if (g_clock.t - p->t3FC < 1.0f)
        return;
    p->t3FC = g_clock.t;
    TGT *pt = func_0023FBE8(p->p214, 0x2E);
    if (!pt)
        return;
    {
        Scope scope;
        float zBest = 3.40282347e+38f;
        void *pv = func_001F4A80(p);
        SO *psoBest = 0;
        SO *pso;
        for (pso = D_00479BD4; pso; pso = pso->pnext) {
            float x, y, z;
            if (pso->x194 == p->x194)
                continue;
            if (!func_00167F60(pv, Matrix(pso)->r[3], VU_FLOAT(pso->g90)))
                continue;
            qword d = Sub(Matrix(pso)->r[3], pt->pcam->q70);
            func_00120BA8(func_0028E990(0, pt->pcam->xA0, d), &x, &y, &z);
            if (z > pt->g60)
                continue;
            if (!func_0011EE30(pt->lm50, x))
                continue;
            if (!func_0011EE30(pt->lm58, y))
                continue;
            if (z < zBest) {
                zBest = z;
                psoBest = pso;
            }
        }
        pt->p70 = psoBest;
        func_002BC350(&scope, 2);
    }
}
