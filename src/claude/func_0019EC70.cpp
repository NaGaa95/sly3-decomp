// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Adapted from the Sly 2 decomp (func_001821C0).
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int i[4]; } U;
struct M3 { qword r[3]; };
struct M4 { U r[4]; };
struct N { qword pos, dir; char pad20[0x50 - 0x20]; float lateral, roll; char pad58[8]; N *next; };
struct E { char pad[0x10]; N *first; char pad14[0x1C]; };
struct P { char pad[0x1F0]; void *model; int count; E entries[1]; };
extern "C" {
extern qword D_00317550;
extern qword D_00479350;
void func_0023CC40(P *p);
M3 func_0011CBF0(qword dir, qword up);
M3 func_0011C8C0(qword axis, float g);
qword *func_002BA818(qword *pq, qword pos);
void func_001C8248(void *model, qword q, M4 *pm, float a, float b);
float fabsf(float);
void func_0019EC70(P *p);
}
static inline qword Cross(qword a, qword b)
{
    qword qw;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(qw) : "j"(a), "j"(b));
    return qw;
}
static inline qword AddLateral(qword a, N *n, float f)
{
    qword k;
    U u;
    __asm__("qmtc2.ni %1, %0" : "=j"(k) : "r"(f));
    u.q = k;
    qword b = Cross(D_00317550, n->dir);
    __asm__("vadda.xyzw $ACC, %0, $vf0\n\tvmaddx.xyzw %0, %1, %2x" : "+j"(a) : "j"(b), "j"(k));
    return a;
}
static inline M3 Mul(const M3 &a, const M3 &b) return r
{
    qword a0 = a.r[0], a1 = a.r[1], a2 = a.r[2];
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
        : "=j"(r.r[0]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[0]));
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
        : "=j"(r.r[1]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[1]));
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
        : "=j"(r.r[2]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[2]));
}

void func_0019EC70(P *p)
{
    func_0023CC40(p);
    if (!p->model)
        return;
    for (int i = 0; i < p->count; i++)
    {
        for (N *n = p->entries[i].first; n; n = n->next)
        {
            M3 m;
            M4 mm;
            qword pos = n->pos;
            m = func_0011CBF0(n->dir, D_00317550);
            if (1.0f < fabsf(n->lateral))
                pos = AddLateral(pos, n, n->lateral);
            float roll = n->roll;
            if (0.01f < fabsf(roll))
                m = Mul(m, func_0011C8C0(D_00317550, roll));
            M4 *pm = &mm;
            func_002BA818(&mm.r[3].q, pos);
            pm->r[0].q = m.r[0];
            pm->r[1].q = m.r[1];
            pm->r[2].q = m.r[2];
            mm.r[0].i[3] = mm.r[1].i[3] = mm.r[2].i[3] = 0;
            pm->r[3].f[3] = 1.0f;
            func_001C8248(p->model, D_00479350, pm, 1.0f, 1.0f);
        }
    }
}
