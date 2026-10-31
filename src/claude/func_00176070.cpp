// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00176070: Sly 2 func_00158E20 port (earlier draft build/claude_wip/os_func_00176070.cpp); SO fields at 0xE0/0xF0.
typedef int qword __attribute__((mode(TI)));
struct AL { int cb; int cbAlign; int pad[2]; AL(int c, int a) { cb = c; cbAlign = a; } };
struct SO { char pad[0xE0]; qword xE0; qword xF0; };
struct E40 { int x0, x4; SO *pso; int pad[13]; };
struct B { qword v[2][2]; char pad[0x10]; E40 *ae; char pad1[0x60 - 0x54]; };
struct A { int x0, x4, x8; float g; char pad[0x28 - 0x10]; };
struct S { int x0; int c; A *aa; char pad[0x58 - 0xC]; int cso; SO **apso; B *ab; };
extern "C" {
void func_001D2770(void *p);
void func_001D2798(void *p, int n);
void *func_001D25B0(const AL &al);
qword func_001205F0(qword v, float g);
void func_00176070(S *p, float g1, float g2);
}
struct VUF { qword q; VUF(const float &g) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(*(const int *)&g)); } };
static inline qword AddScale(qword a, qword b, const VUF &t)
{
    __asm__ __volatile__("vadda.xyzw $ACC, %0, $vf0\n\tvmaddx.xyzw %0, %1, %2x" : "+j"(a) : "j"(b), "j"(t.q), "j"(t.q), "j"(b));  /* last two operands: allocation only */
    return a;
}
static inline qword AddScale2(qword a0, qword b, const VUF &t)
{
    register qword a asm("vf2") = a0; /* register pin: first plane accumulates in vf2 like the target */
    __asm__ __volatile__("vadda.xyzw $ACC, %0, $vf0\n\tvmaddx.xyzw %0, %1, %2x" : "+j"(a) : "j"(b), "j"(t.q), "j"(t.q), "j"(b));  /* last two operands: allocation only */
    return a;
}
class FRAME { public: FRAME() { func_001D2770(this); } ~FRAME() { func_001D2798(this, 2); } };
void func_00176070(S *p, float g1, float g2)
{
    FRAME frame;
    int i;
    SO *pso;
    func_001D25B0(AL(p->cso * 32, 0x10));
    for (i = 0; i < p->c; i++) {
        A *pa = &p->aa[i];
        if (pa->g == 0.0f) continue;
        B *pb = &p->ab[i];
        for (int j = 0; j < 2; j++) {
            E40 *pe = &pb->ae[j];
            pso = pe->pso;
            if (!pso) continue;
            qword *pv = pb->v[j];
            pso->xE0 = AddScale2(pso->xE0, pv[0], VUF(pa->g));
            pso->xF0 = AddScale(pso->xF0, pv[1], VUF(pa->g));
        }
    }
    for (int k = 0; k < p->cso; k++) {
        pso = p->apso[k];
        pso->xE0 = func_001205F0(pso->xE0, g1);
        pso->xF0 = func_001205F0(pso->xF0, g2);
    }
}
