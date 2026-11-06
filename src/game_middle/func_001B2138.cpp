// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Two-bone aim: rotate the base bone about its joint so the tip points at `pos`, express the rotation in the parent's
// frame (parent^-1 * rot * parent), then slide the tip bone by the remaining offset, refresh both world matrices and
// hand over to the IK solver (func_001A5FF0) and the owner's refresh method.
// Matrix products use the Lilly-style M3 operator* (named return value); Rot lists its operands vector-first, which
// decides the VU register numbering of the rotated vector.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { U r[3]; M3() {} M3(const M3 &m) { r[0] = m.r[0]; r[1] = m.r[1]; r[2] = m.r[2]; } M3 &operator=(const M3 &m) { r[0] = m.r[0]; r[1] = m.r[1]; r[2] = m.r[2]; return *this; } };
struct M4 { U r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct Bone { M4 local; M4 world; unsigned char pad80[0x20]; Bone *parent; int stamp; };
struct Node { unsigned char pad0[0xC]; VTE *vt; };
struct Aux { unsigned char pad0[0xA8]; void *ik; };
struct Self {
    unsigned char pad0[0xC]; VTE *vt; unsigned char pad10[0x1AA4 - 0x10]; Node *source;
    unsigned char pad1AA8[0x1AC8 - 0x1AA8]; Bone *base; Bone *tip; unsigned char pad1AD0[0x1AD4 - 0x1AD0]; Aux *aux;
};
struct G { unsigned char pad[0x44F4]; int stamp; };
extern "C" {
extern G D_00475480;
M3 func_0011CDC8(qword a, qword b);
M3 func_0011C6F8(M3 *pm);
void func_0011D558(M4 *out, M4 *a, M4 *b);
qword func_0028E990(int n, Bone *b, qword v);
qword *func_002BA818(qword *p, qword v);
void func_001A5FF0(void *ik);
}
static inline qword Sub(const qword &a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword SubV(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword ToVf(qword v) { qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(v)); return r; }
static inline qword Rot(const M3 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %2, %1x
	vmadday.xyz $ACC, %3, %1y
	vmaddz.xyz %0, %4, %1z"
            : "=j"(r) : "j"(v), "j"(m.r[0].q), "j"(m.r[1].q), "j"(m.r[2].q));
    return r;
}
struct VU_VECTOR4 { qword qw; };
inline M3 operator*(const M3 &matL, const M3 &matR) return mat
{
    qword qwL0 = matL.r[0].q;
    qword qwL1 = matL.r[1].q;
    qword qwL2 = matL.r[2].q;
    VU_VECTOR4 v0;
    VU_VECTOR4 v1;
    VU_VECTOR4 v2;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v0.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(matR.r[0].q));
    *(VU_VECTOR4 *)&mat.r[0] = v0;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v1.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(matR.r[1].q));
    *(VU_VECTOR4 *)&mat.r[1] = v1;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v2.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(matR.r[2].q));
    *(VU_VECTOR4 *)&mat.r[2] = v2;
}
static inline void SetMat3(Bone *plo, const M3 &m)
{
    plo->local.r[0].q = m.r[0].q; plo->local.r[1].q = m.r[1].q; plo->local.r[2].q = m.r[2].q;
    plo->local.r[0].i[3] = 0; plo->local.r[1].i[3] = 0; plo->local.r[2].i[3] = 0;
}
static inline qword AddTo(qword a, qword b) { __asm__("vadd.xyzw %0,%1,%0" : "+j"(a) : "j"(b)); return a; }
extern "C" void func_001B2138(Self *self, qword pos)
{
    VTE &e = self->source->vt[36];
    M4 *m = ((M4 *(*)(void *))e.pfn)((char *)self->source + e.d);
    qword ref = self->base->world.r[3].q;
    qword d1 = SubV(m->r[3].q, ref);
    M3 rot = func_0011CDC8(d1, Sub(pos, ref));
    qword p2 = Add(ref, Rot(rot, d1));
    M3 mm;
    M3 pw = *(M3 *)&self->base->parent->world;
    rot = func_0011C6F8(&pw) * rot * pw;
    mm = rot * *(M3 *)&self->base->local;
    SetMat3(self->base, mm);
    qword off = func_0028E990(0, self->tip->parent, SubV(pos, p2));
    Bone *t = self->tip;
    func_002BA818(&t->local.r[3].q, AddTo(ToVf(off), t->local.r[3].q));
    t->local.r[3].f[3] = 1.0f;
    M4 tmp;
    Bone *p = self->tip;
    func_0011D558(&tmp, &p->parent->world, &p->local);
    p->world = tmp;
    p = self->base;
    func_0011D558(&tmp, &p->parent->world, &p->local);
    p->world = tmp;
    int n = ++D_00475480.stamp;
    Bone *b0 = self->base, *b1 = self->tip;
    b0->stamp = n;
    b1->stamp = n;
    func_001A5FF0(self->aux->ik);
    VTE &f = self->vt[20];
    ((void (*)(void *))f.pfn)((char *)self + f.d);
}
