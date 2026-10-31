// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001681B0: rotate a direction into the object's frame, take (-y, z, 0) and normalize it (fallback D_00317540).
// Adapted from Sly 2 func_001C4768.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct M3 { qword row[3]; };
struct LO;
struct LOV { char pad[0x120]; short d; short p; struct M3 *(*pfnMat)(struct LO *); };
struct LO { int a[3]; struct LOV *pvt; };
extern qword D_00317540;
static inline qword Local(const struct M3 *m, qword v)
{
    qword q, one, a, b, c;
    q = m->row[0];
    __asm__("vmul.xyzw %2,%0,%7\n\tvmaxw.xyzw %1,$vf0,$vf0w\n\tvmul.xyzw %3,%5,%7\n\tvmul.xyzw %4,%6,%7\n\tvadday.x $ACC,%2,%2y\n\tvmaddz.x %0,%1,%2z\n\tvaddax.y $ACC,%3,%3x\n\tvmaddz.y %0,%1,%3z\n\tvaddax.z $ACC,%4,%4x\n\tvmaddy.z %0,%1,%4y"
            : "+j"(q), "=&j"(one), "=&j"(a), "=&j"(b), "=&j"(c) : "j"(m->row[1]), "j"(m->row[2]), "j"(v));
    return q;
}
static inline qword Norm(qword v, qword fallback)
{
    qword d;
    qword one, r; float f;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(d));
    { register int t __asm__("$3"); /* register pin: length bits in v1 like the target */ __asm__("qmfc2.ni %0,%1" : "=r"(t) : "j"(d)); __asm__("mtc1 %1,%0" : "=f"(f) : "r"(t)); }
    if (f < 0.0001f) { __asm__("" : : "j"(one), "j"(one), "j"(one)); d = fallback; } /* zero-instruction: keeps one global with enough refs that global-alloc puts d in vf1 and one in vf2 */
    else __asm__("vdiv $Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "+j"(d) : "j"(v));
    __asm__("qmfc2.ni %0,%1" : "=r"(r) : "j"(d));
    return r;
}
qword func_001681B0(struct LO *p, qword dir)
{
    union U v;
    struct M3 *pm = p->pvt->pfnMat((struct LO *)((char *)p + p->pvt->d));
    v.q = Local(pm, dir);
    v.f[0] = -v.f[1];
    v.f[1] = v.f[2];
    v.f[2] = 0.0f;
    return Norm(v.q, D_00317540);
}
