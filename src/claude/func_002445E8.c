// Ported from the Sly 2 source src/hand/func_001FAA00.c (impulse / mass through the linear constraint).
typedef int qword __attribute__((mode(TI)));
union SCALAR { qword q; float f[4]; };
struct PROJECTION { qword axis; int mode; };
struct LO;
struct B { char pad[0xB0]; struct PROJECTION projection; char pad2[0xD0-0xD0]; int mass; };
struct A { char pad[0x48]; struct LO *space; char pad2[0xD8-0x4C]; struct B *state; };
qword func_00244418(struct PROJECTION *, struct LO *, qword);
static inline qword Get(qword r){qword a; __asm__("qmfc2.ni %0,%1" : "=r"(a) : "j"(r), "j"(r), "j"(r)); return a;}
qword func_002445E8(struct A *input, qword v)
{
    struct A *p = input;
    struct PROJECTION *projection;
    union SCALAR scalar;
    qword vv, t, r;
    __asm__ __volatile__("qmtc2.ni %1,%0" : "=j"(vv) : "r"(v));
    {
        register int m __asm__("$3") = p->state->mass; /* pin: mass word in v1 */
        __asm__ __volatile__("qmtc2.ni %1,%0" : "=j"(t) : "r"(m));
    }
    projection = &p->state->projection;
    __asm__ __volatile__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=&j"(r) : "j"(t), "j"(vv));
    scalar.q = t;
    return func_00244418(projection, p->space, Get(r));
}
