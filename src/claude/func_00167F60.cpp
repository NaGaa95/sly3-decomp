// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00167F60: is the position inside the object's planes (cf. Sly 2 func_0014F850).
typedef int qword __attribute__((mode(TI)));
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
struct M4 { qword r[4]; };
struct LO;
struct LOV { char pad[0x120]; short d; short p; M4 *(*pfnMat)(LO *); };
struct LO { int a[3]; LOV *pvt; char pad[0x170 - 0x10]; qword r[3]; };
extern "C" int func_00167F60(LO *p, qword pos, qword w)
{
    VU_VECTOR vw(w);
    VU_VECTOR vpos(pos);
    qword one, v;
    int f;
    M4 *pm = p->pvt->pfnMat((LO *)((char *)p + p->pvt->d));
    __asm__("vmaxw.xyzw %0, $vf0, $vf0w" : "=j"(one));
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(v) : "j"(vpos.q), "j"(pm->r[3]));
    __asm__("vmulax.xyzw $ACC, %1, %4x\n\tvmadday.xyzw $ACC, %2, %4y\n\tvmaddaz.xyzw $ACC, %3, %4z\n\tvmsubax.xyzw $ACC, %5, %6x\n\tvnop\n\tvnop\n\tvnop\n\tvnop\n\tcfc2.ni %0, $vi17"
            : "=r"(f) : "j"(p->r[0]), "j"(p->r[1]), "j"(p->r[2]), "j"(v), "j"(one), "j"(vw.q));
    return (f ^ 0xF0) == 0;
}
