// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Cf. Sly 2 src/hand/func_0020BAD8.c: weighted sum of two blend entries.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
extern qword D_00317560;
struct C { int pad; float g; };
struct B { int pad[2]; struct C *pc; };
struct A { char pad[0xC0]; struct B *pb; };
struct E { float w; int pad[3]; qword v; int pad2; float t; char pad3[0x40 - 0x28]; };
struct S { int pad; struct A *pa; int pad2[2]; struct E ae[2]; };
qword func_00258C70(struct S *p)
{
    struct B *pb = p->pa->pb;
    struct C *pc = pb->pc;
    qword acc = D_00317560;
    struct E *pe = p->ae;
    unsigned int i;
    for (i = 0; i < 2; i++) {
        U u;
        __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(pe->w * (pe->t / pc->g)));
        __asm__("vadda.xyzw $ACC, %0, $vf0\n\tvmaddx.xyzw %0, %1, %2x" : "+j"(acc) : "j"(pe->v), "j"(u.q));
        pe++;
    }
    return acc;
}
