// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x120]; VTE e120; char pad2[0x130 - 0x128]; VTE e130; };
struct P {
    char pad[0xC]; VT *pvt; char pad1[0x168 - 0x10]; int x168;
    char pad2[0x2E8 - 0x16C]; int x2E8; float g2EC; float g2F0;
};
extern "C" {
extern struct CLOCK { float t; } g_clock;
extern float D_0047A2B0;
int func_00260758(int, int);
void func_00262450(int, int);
void func_00262280(int, int);
int func_002459F8(int);
void func_00244F08(int, int);
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("mfc1 %0, %1" : "=rj"(q) : "f"(f)); } };
static inline M4 *Matrix(P *p) { VTE *e = &p->pvt->e120; return ((M4 *(*)(void *))e->pfn)((char *)p + e->d); }
static inline qword Vel(P *p) { VTE *e = &p->pvt->e130; return ((qword (*)(void *))e->pfn)((char *)p + e->d); }
static inline qword AddScale(qword a, VU_FLOAT s, qword b)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %3, %2x" : "=j"(r) : "j"(a), "j"(s.q), "j"(b));
    return r;
}
extern "C" void func_00146D08(P *p)
{
    qword pos = Matrix(p)->r[3];
    VECTOR v;
    *(qword *)&v = AddScale(pos, VU_FLOAT(3.0f), Vel(p));
    if (D_0047A2B0 < v.z) {
        if (p->x168 && !func_00260758(p->x168, 0x78A)) {
            func_00262450(p->x168, 0x78A);
            p->g2EC = g_clock.t;
        }
        if (g_clock.t - p->g2F0 > 1.0f) {
            func_00244F08(func_002459F8(p->x2E8), 0);
            p->g2F0 = g_clock.t;
        }
    } else {
        if (p->x168 && func_00260758(p->x168, 0x78A)) {
            if (g_clock.t - p->g2EC > 1.0f)
                func_00262280(p->x168, 0x78A);
        }
    }
}
