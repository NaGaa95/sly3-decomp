// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001B0CC0: paired-response solver (method of the body p, Sly 2 analog func_0018F958).
// For each world axis (D_00317490 rows) and each of the two bodies (p, other; side 1 uses the reversed axis) it asks
// func_002445E8 / func_00244630 for the linear and angular effect of a unit impulse, then lets p's virtual slot 73 turn
// that pair into a velocity response. The differences of the two responses form a 3x3 matrix that func_0011A278 /
// func_0011A608 (Crout decomposition / solve) solve against the three input floats; out[side] are the weighted sums.
// No register pins and no volatile. What the match depends on:
//  - SET_X is the "sw" lane store also used by func_001B4430 (SetX): the qword is an "r" operand, so the qmfc2 is gcc's
//    own reload move and the asm is only the store. That keeps the qmfc2 independent of the address sum in the
//    scheduler, puts it in a reload register (which also sets the reload rotation for the weights in the last loop)
//    and keeps the store out of the branch delay slot (reorg never moves an asm insn).
//  - p is const, so its spill slot does not depend on the effect stores (call 3's argument setup order).
//  - The two effect stores go through Addr() pointer locals; plain stores change the loop givs.
//  - Sum3 lists the three scalars first (original VU register numbering).
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct DELTA { U first, second; };
struct P;
struct OBJ { P *p; };
struct VE { short delta, pad; void (*fn)(P *, DELTA *, qword, U *); };
struct M4 { U r[4]; };
struct P { char pad[12]; VE *vt; };
extern "C" {
qword func_002445E8(P *, qword);
qword func_00244630(P *, qword, qword);
extern U D_00317490[3];
void func_0011A278(int, float *, float *);
void func_0011A608(int, float *, float *, float *);
}
struct VU_FLOAT { qword q; VU_FLOAT() {} explicit VU_FLOAT(qword a) { q = a; } inline VU_FLOAT(const float &f); };
struct VU_VECTOR { qword q; VU_VECTOR() {} VU_VECTOR(qword a) { q = a; } };
static inline qword Position(P *p)
{
    VE *e = &p->vt[36];
    return ((M4 *(*)(void *))e->fn)((char *)p + e->delta)->r[3].q;
}
static inline VU_FLOAT Scalar(float value) { qword q; __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(value)); return VU_FLOAT(q); }
static inline VU_FLOAT VuFloatFromMemWord(int n) { qword q; __asm__("qmtc2.ni %1,%0" : "=j"(q) : "rV"(n)); return VU_FLOAT(q); }
inline VU_FLOAT::VU_FLOAT(const float &f) { *this = VuFloatFromMemWord(*(int *)&f); }
static inline VU_VECTOR operator*(VU_VECTOR value, VU_FLOAT amount)
{
    qword q;
    __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(q) : "j"(value.q), "j"(amount.q));
    return VU_VECTOR(q);
}
static inline qword Sub(VU_VECTOR first, VU_VECTOR second)
{
    qword q;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(q) : "j"(first.q), "j"(second.q));
    return q;
}
static inline qword Dot(const qword &a, const qword &b)
{
    qword r, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(r), "=j"(one) : "j"(a), "j"(b));
    return r;
}
/* x lane of a VU qword stored to a float slot (see the header). A macro: the slot must be the direct
   matrix[row][column] lvalue, a pointer or reference parameter folds its address to the constant-last form. */
#define SET_X(slot, q) __asm__("sw %1,%0" : "=m"(slot) : "r"(q))
/* weighted sum a*x + b*y + c*z; the scalar operands are listed first (original VU register numbering) */
static inline VU_VECTOR Sum3(const U *a, const U *b, const U *c, VU_FLOAT x, VU_FLOAT y, VU_FLOAT z, U *scalar)
{
    scalar->q = x.q;
    qword va = a->q;
    scalar->q = y.q;
    qword vb = b->q;
    scalar->q = z.q;
    qword vc = c->q;
    qword r;
    __asm__("vmulax.xyzw $ACC,%4,%1x\n\tvmaddax.xyzw $ACC,%5,%2x\n\tvmaddx.xyzw %0,%6,%3x" : "=j"(r) : "j"(x.q), "j"(y.q), "j"(z.q), "j"(va), "j"(vb), "j"(vc));
    return VU_VECTOR(r);
}
static inline void StoreQ(U *d, VU_VECTOR v) { d->q = v.q; }
static inline U *Addr(U *p) { return p; }
static inline qword Load(const U *p) { return p->q; }
extern "C" void func_001B0CC0(P *const p, P *other, qword *point, float *input, DELTA *out)
{
    int axisIndex = 0, side;
    OBJ objects[2];
    U points[2];
    U axis;
    DELTA effects[2][3];
    U velocity[2];
    U relative[3];
    float matrix[3][3], decomposed[3][3], rhs[3], weights[3];
    U scalar;
    objects[0].p = p;
    objects[1].p = other;
    StoreQ(&points[0], Position(p));
    StoreQ(&points[1], *point);
    for (; axisIndex < 3; axisIndex++) {
        for (side = 0; side < 2; side++) {
            P *object = objects[side].p;
            axis.q = D_00317490[axisIndex].q;
            if (side == 1) {
                VU_FLOAT minus = Scalar(-1.0f);
                axis.q = (VU_VECTOR(axis.q) * minus).q;
                scalar.q = minus.q;
            }
            U *first = Addr(&effects[side][axisIndex].first);
            first->q = func_002445E8(object, axis.q);
            U *second = Addr(&effects[side][axisIndex].second);
            second->q = func_00244630(object, Load(&points[side]), axis.q);
            DELTA *effect = &effects[side][axisIndex];
            VE *method = &p->vt[73];
            method->fn((P *)((char *)p + method->delta), effect, *point, &velocity[side]);
        }
        StoreQ(&relative[axisIndex], Sub(velocity[0].q, velocity[1].q));
    }
    for (axisIndex = 0; axisIndex < 3; axisIndex++) {
        for (int column = 0; column < 3; column++)
            SET_X(matrix[axisIndex][column], Dot(D_00317490[column].q, relative[axisIndex].q));
        rhs[axisIndex] = input[axisIndex];
    }
    func_0011A278(3, &matrix[0][0], &decomposed[0][0]);
    func_0011A608(3, &decomposed[0][0], rhs, weights);
    for (side = 0; side < 2; side++) {
        VU_FLOAT x(weights[0]), y(weights[1]), z(weights[2]);
        StoreQ(&out[side].first, Sum3(&effects[side][0].first, &effects[side][1].first, &effects[side][2].first, x, y, z, &scalar));
        StoreQ(&out[side].second, Sum3(&effects[side][0].second, &effects[side][1].second, &effects[side][2].second, x, y, z, &scalar));
    }
}
