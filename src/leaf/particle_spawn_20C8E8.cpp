// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Spawns one particle object at a world position: size from the emitter polynomial over its lifetime, random roll about the
// emit direction, and (unless the direction is close to the up axis) an initial velocity of -50 along the tilted up axis.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; unsigned u[4]; long l[2]; };
struct M3 { qword r[3]; };
struct POLY { float a, b, c; };
struct EMIT { char pad0[0x14]; float start, duration; char pad1C[4]; POLY size; };
struct LO;
struct VE { short delta, pad; void (*fn)(void *, qword, float); };
struct O {
    char pad0[0x18]; float duration; LO *visual; char pad20[8]; float spin; char pad2C[0x14];
    M3 matrix; char pad70[0x20]; U velocity; char padA0[0x48]; VE *vt; int padEC; LO *space;
};
struct CLOCK { float t, dt; };
extern CLOCK D_0036BB98;
extern char D_00475480[];
extern qword D_00317530, D_00317540, D_00317550;
extern "C" {
O *func_0020B9C0(void *, int, void *);
qword func_0028E910(void *, LO *, qword);
float func_0011E940(float, float);
void func_0011FEA8(qword, qword, qword, qword *);
M3 func_0011C9E8(qword);
M3 func_0011CDC8(qword, qword);
O *func_0020C8E8(EMIT *, LO *, LO *, qword, qword);
}
static inline float Polynomial(POLY *p, float t) { return p->a + t * (p->b + t * p->c); }
static inline float Dot(qword a, qword b)
{
    qword d, one;
    float f;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(a), "j"(b));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(d));
    return f;
}
static inline qword Scale(qword a, float f, U &home)
{
    qword k;
    __asm__("qmtc2.ni %1,%0" : "=j"(k) : "r"(f));
    home.q = k;
    __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(a) : "j"(a), "j"(k));
    return a;
}
static inline qword Transform(M3 &m, qword a)
{
    __asm__("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z" : "+j"(a) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    return a;
}
static inline M3 Mul(const M3 &a, const M3 &b) return r
{
    qword a0 = a.r[0], a1 = a.r[1], a2 = a.r[2];
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[0]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[0]));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[1]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[1]));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[2]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[2]));
}
static inline qword Pack(float x, float y, float z)
{
    qword v, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(v), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return v;
}
/* stores the X word of a packed vector straight from its general register */
static inline void StoreX(int *p, qword q) { __asm__("sw %1,%0" : "=m"(*p) : "r"(q)); }
static inline float Y(qword q) { float f; __asm__("prot3w %0,%1" : "=r"(f) : "r"(q)); return f; }
extern "C" O *func_0020C8E8(EMIT *p, LO *visual, LO *space, qword position, qword direction)
{
    if (!visual)
        return 0;
    {
        O *object = func_0020B9C0(D_00475480, 9, 0);
        if (!object)
            return 0;
        {
            float zero = 0.0f;
            qword local = func_0028E910(0, space, position);
            float size = Polynomial(&p->size, (D_0036BB98.t - p->start) / p->duration);
            size *= func_0011E940(0.8f, 1.4f);
            object->vt[1].fn((char *)object + object->vt[1].delta, local, size);
            object->visual = visual;
            object->duration = 5.0f;
            object->spin = -size;
            object->space = space;
            M3 frame;
            frame.r[2] = direction;
            func_0011FEA8(direction, D_00317530, D_00317540, frame.r);
            U angles;
            angles.q = Pack(zero, zero, func_0011E940(zero, 6.28318548f));
            M3 rotation = func_0011C9E8(angles.q);
            {
                M3 orient = Mul(frame, rotation);
                object->matrix = orient;
            }
            qword *up = &D_00317550;
            if (__builtin_fabsf(Dot(direction, *up)) < 0.7f) {
                angles.f[2] = zero;
                angles.f[1] = Y(direction);
                StoreX(&angles.i[0], direction);
                M3 tilt = func_0011CDC8(angles.q, direction);
                U home;
                object->velocity.q = Transform(tilt, Scale(*up, -50.0f, home));
            }
            return object;
        }
    }
}
