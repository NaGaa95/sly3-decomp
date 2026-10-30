// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* returns, as a CRef vector, the point (g144, 0, 0) of the current object transformed by its matrix and position */
typedef int qword __attribute__((mode(TI)));
typedef struct CRef { int m_tagk; int m_tag; } CRef;
struct M4 { qword r[4]; };
struct O { char pad[0x90]; struct M4 mat; char pad2[0x144 - 0xD0]; float g144; };
extern char D_00475480[];
struct O *func_00165B28(void *pg);
CRef *func_0012AFA0(CRef *pref, qword v);
static __inline__ qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
static __inline__ qword XfPos(struct M4 *pm, qword v)
{
    __asm__("vmulax.xyz $ACC, %1, %0x\n\tvmadday.xyz $ACC, %2, %0y\n\tvmaddaz.xyz $ACC, %3, %0z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "+j"(v) : "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]), "j"(pm->r[3]));
    return v;
}
CRef *func_00127060(CRef *pref)
{
    union { qword q; float f[4]; } u;
    qword q = Make(func_00165B28(D_00475480)->g144, 0.0f, 0.0f);
    u.q = q;
    func_0012AFA0(pref, XfPos(&func_00165B28(D_00475480)->mat, q));
    return pref;
}
