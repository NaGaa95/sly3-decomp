// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
struct LO;
struct S { qword v; int k; };
struct E { char pad[0x30]; M3 m; char pad2[0x90 - 0x60]; struct S vector; };
struct B { char pad[0x40]; M3 m; };
struct X { char pad[0x4C]; struct B *pb; char pad2[0xD8 - 0x50]; struct E *pe; };
M3 *func_0011C6F8(M3 *pd, const M3 *ps);
qword func_00244418(const struct S *pv, const struct B *pb, qword v);
static inline qword MulMV(const M3 *pm, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z" : "=j"(r) : "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]), "j"(v));
    return r;
}
static inline void MulMVIn(const M3 *pm, qword *pv)
{
    __asm__("vmulax.xyz $ACC, %1, %0x\n\tvmadday.xyz $ACC, %2, %0y\n\tvmaddz.xyz %0, %3, %0z" : "+j"(*pv) : "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]));
}
qword func_00244690(struct X *p, qword v)
{
    struct B *pb = p->pb;
    M3 m;
    func_0011C6F8(&m, &pb->m);
    MulMVIn(&m, &v);
    MulMVIn(&p->pe->m, &v);
    return func_00244418(&p->pe->vector, p->pb, MulMV(&pb->m, v));
}
