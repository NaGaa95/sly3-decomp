// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -malign-loops=3
// Temporarily re-place an anchored item and sweep it (func_0020C470): the item's basis and position are saved, the
// owner's world matrix (identity without one) and its inverse (func_0011D768) are taken; out of range of the target the
// anchors are re-placed (func_0020E5F0); with an anchor object the position moves by its offset turned into the local
// frame, and in mode 3 the basis is rebuilt from the cross product of the two anchor edges (func_0011CDC8) between the
// inverse and world rotations. Afterwards the saved basis and position are restored.
// Matching notes: save/restore row by row (no M3 operator=, which keeps &basis in an s-register), restore position first;
// the inverse-matrix pointer pB is taken after the first anchor call (lives in s0 across calls); R3() gives the fresh
// `addiu v0,sp,0x30` pointer for the world rows in the second product.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { U r[3]; M3(){} M3(const M3 &m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];} M3 &operator=(const M3 &m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return *this;} };
struct M4 { U r[4]; M4(){} M4(const M4 &m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];r[3]=m.r[3];} M4 &operator=(const M4 &m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];r[3]=m.r[3];return *this;} };
struct VECTOR { union { qword q; float f[4]; }; VECTOR(const VECTOR &v) __asm__("func_002BC400"); };
struct VTE { short d; short pad; M4 *(*pfn)(void *); };
struct LO { char pad[0xC]; VTE *vt; };
struct OWNER { char pad[0x60]; LO *world; };
struct S {
    char pad0[0x10]; OWNER *owner; char pad14[0x40 - 0x14]; U row[3]; U pos;
    char pad80[0xF0 - 0x80]; void *anchor; float radius; int mode; VECTOR *target; void *p100; void *p104;
};
extern qword D_00325AD0[2];
extern qword D_00317550;
extern "C" {
void *func_00292034(void *, int, int);
M4 func_0011D768(const M4 *);
void func_0020E5F0(S *);
qword func_00289D68(void *, void *);
M3 func_0011CDC8(qword, qword);
void func_0020C470(S *, void *, void *);
}
static inline void SetIdent(M4 *pm) { func_00292034(pm, 0, 0x40); pm->r[0].f[0] = pm->r[1].f[1] = pm->r[2].f[2] = pm->r[3].f[3] = 1.0f; }
static inline M3 operator*(const M3 &a,const M3 &b) return r
{
    qword a0=a.r[0].q,a1=a.r[1].q,a2=a.r[2].q;
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[0].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[0].q));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[1].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[1].q));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[2].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[2].q));
}
static inline M3 &R3(M4 &m) { return *(M3 *)&m; }
static inline qword Transform(const M4 &m, qword v) { qword r;
 __asm__("vmulax.xyz ACC,%1,%5x\n\tvmadday.xyz ACC,%2,%5y\n\tvmaddaz.xyz ACC,%3,%5z\n\tvmaddw.xyz %0,%4,vf0w":"=j"(r):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(m.r[3].q),"j"(v));return r;
}
static inline qword Rotate(const M4 &m, qword v) { qword r;
 __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(v));return r;
}
static inline qword Rotate3(const M3 &m, qword v) { qword r;
 __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(v));return r;
}
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Cross(qword a, qword b) { qword r; __asm__("vopmula.xyz ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float Dot(qword a, qword b)
{
    qword r, one;
    float f;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(r), "=j"(one) : "j"(a), "j"(b));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(r));
    return f;
}
extern "C" void func_0020E858(S *s, void *a, void *b)
{
    U saved[3];
    saved[0].q = s->row[0].q;
    saved[1].q = s->row[1].q;
    saved[2].q = s->row[2].q;
    qword pos = s->pos.q;
    M4 matA, matB;
    LO *world = s->owner->world;
    if (world) {
        matA = *world->vt[36].pfn((char *)world + world->vt[36].d);
        matB = func_0011D768(&matA);
    } else {
        SetIdent(&matA);
        SetIdent(&matB);
    }
    if (0.0f <= s->radius) {
        qword posW = Transform(matA, s->pos.q);
        VECTOR target(*s->target);
        int far = s->radius * s->radius < Dot(Sub(posW, target.q), Sub(posW, target.q));
        if (far)
            func_0020E5F0(s);
    }
    if (s->anchor) {
        qword v = func_00289D68(s->anchor, s->target);
        M3 *pB = (M3 *)&matB;
        s->pos.q = Add(s->pos.q, Rotate3(*pB, v));
        if (s->mode == 3) {
            qword p1 = func_00289D68(s->anchor, s->p100);
            qword p2 = func_00289D68(s->anchor, s->p104);
            M3 rot;
            rot = func_0011CDC8(D_00317550, Cross(Add(Sub(p1, v), D_00325AD0[0]), Add(Sub(p2, v), D_00325AD0[1])));
            M3 q = *pB * rot * R3(matA);
            s->row[0].q = q.r[0].q;
            s->row[1].q = q.r[1].q;
            s->row[2].q = q.r[2].q;
        }
    }
    func_0020C470(s, a, b);
    s->pos.q = pos;
    s->row[0].q = saved[0].q;
    s->row[1].q = saved[1].q;
    s->row[2].q = saved[2].q;
}
