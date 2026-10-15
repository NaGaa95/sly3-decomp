// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
// Three isolated hardware vector operations; ACC.xyz is overwritten and consumed within one cross-product block.
// The compiler exposes no VU ACC clobber; no ACC value is live across operations.
typedef int QWORD __attribute__((mode(TI)));
struct Owner {char prefix[0x70];QWORD position;};
struct S {char prefix[0x4C];struct Owner *owner;};
struct Motion {QWORD linear;QWORD angular;};
// Point velocity: linear velocity plus angular velocity crossed with the
// point's displacement from the stored owner position. Each operation keeps
// all original vector lanes; the cross product retains angular velocity W.
QWORD func_00244740(struct S *p, const struct Motion *motion, QWORD point)
{
    QWORD offset, linear, cross, result;
    __asm__("vsub.xyzw %0,%1,%2"
            : "=j"(offset) : "j"(point), "j"(p->owner->position));
    linear = motion->linear;
    cross = motion->angular;
    __asm__("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1"
            : "=j"(cross) : "0"(cross), "j"(offset));
    __asm__("vadd.xyzw %0,%1,%2"
            : "=j"(result) : "j"(linear), "j"(cross));
    return result;
}
