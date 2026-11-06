// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Port of the Sly 2 source src/hand/func_0020BB58.c: -Os, one pin; the extra "j"(scalar) operand only raises its allocation priority.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct T { char pad[0x1A0]; qword v; };
union FLOATWORD { float value; int bits; };
struct R { char pad[0x40]; union FLOATWORD scale; };
struct ANIMATION;
struct S { struct T *pt; struct ANIMATION *animation; int pad[2]; float f10; char pad2[0x50 - 0x14]; float f50; int n54; };
void func_00148938(struct ANIMATION *);
struct R *func_00258CE0(struct S *p);
qword func_00258C70(struct S *p);
static inline void InitScalar(U *value,int bits) {
    int word=bits;
    register qword r __asm__("vf2"); /* pin: scale scalar in vf2 */
    __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(word));
    value->q=r;
}
static inline qword Negate(qword v,U *value) {
    qword scalar;
    qword result;
    __asm__("qmtc2.ni %1,%0" : "=j"(scalar) : "r"(-1.0f));
    value->q=scalar;
    __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(result) : "j"(v),"j"(value->q),"j"(scalar));
    return result;
}
void func_00258CF0(struct S *p, float g)
{
    struct T *pt;
    U b, a;
    qword q, r1, r2;
    if (p->n54 == 0) {
        p->f50 = 0.0f;
        p->f10 = 1.0f;
    } else {
        p->f50 = g;
        p->f10 = 1.0f - g;
    }
    func_00148938(p->animation);
    pt = p->pt;
    InitScalar(&a,func_00258CE0(p)->scale.bits);
    b = a;
    q = func_00258C70(p);
    r1=Negate(q,&b);
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r2) : "j"(a.q), "j"(r1));
    pt->v = r2;
}
