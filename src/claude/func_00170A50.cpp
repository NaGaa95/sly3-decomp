// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Port of Sly 2 src/hand/func_001545F0.cpp (early flag-0x10 exit added; flag word moved to 0x3D8).
typedef int qword __attribute__((mode(TI)));
struct T { char pad[0x3D8]; int x3D8; };
struct SO;
struct AL { int cb; int cbAlign; AL(int c, int a) { cb = c; cbAlign = a; } };
extern "C" {
void func_001D2770(void *p);
void func_001D2798(void *p, int n);
qword func_0016FD78(T *p);
void *func_001D25B0(AL *pal);
qword func_001C9428(SO *pso, int z, qword v);
void func_0025CF18(void *g, qword a, qword b, void *pfn, void *o, int *pi, int *pj);
int func_00165000(int z, qword a, qword b, int i, int j, int k);
void func_001709A8(void);
void func_00170968(void);
extern char D_00475480[];
int func_00170A50(T *p, SO *pso);
}
union VQ { float ag[4]; qword q; };
/* rodata at 0x003210D0 (not in symbol_addrs): one zero point */
static const VQ D_003210D0[1] = { { { 0.0f, 0.0f, 0.0f, 0.0f } } };
class FRAME { public: FRAME() { func_001D2770(this); } ~FRAME() { func_001D2798(this, 2); } };

int func_00170A50(T *p, SO *pso)
{
    if (p->x3D8 & 0x10)
        return 1;
    FRAME frame;
    int i;
    const VQ *ppos = D_003210D0;
    qword q = func_0016FD78(p);
    AL al(0x10, 0x10);
    qword *apos = (qword *)func_001D25B0(&al);
    int ii, jj;
    qword vmin, vmax;
    vmax = q;
    vmin = q;
    for (i = 0; i < 1; i++) {
        qword t = func_001C9428(pso, 0, ppos[i].q);
        apos[i] = t;
        __asm__("vmini.xyz %0, %0, %1" : "+j"(vmin) : "j"(t));
        __asm__("vmax.xyz %0, %0, %1" : "+j"(vmax) : "j"(t));
    }
    void *pfn = (void *)func_001709A8;
    if (p->x3D8 & 4) pfn = (void *)func_00170968;
    func_0025CF18(D_00475480, vmin, vmax, pfn, p, &ii, &jj);
    bool f;
    for (i = 0; (f = i < 1); i++)
        if (!func_00165000(0, q, apos[i], ii, jj, 0)) break;
    return !f;
}
