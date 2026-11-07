// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// A74: dot and vsqrt in separate asms + lengths stored with a "sw" lane-store helper (gcc emits the qmfc2 itself, and the
// asm store keeps the jal delay slot a nop); zero-insn "=j"/"0" copies on pb (caller-save in vf1) and d1 fix VF numbering.
typedef int qword __attribute__((mode(TI)));
struct Xf { qword r[4]; unsigned char pad[0xA0 - 0x40]; int nA0; };
struct Self {
    int pad0; struct Xf *p4; int pad8[2]; qword q10; int pad20[4];
    struct Xf *p30; int f34, f38; float f3C; qword q40; qword rows[3]; struct Xf *p80; int pad84[3]; qword q90;
    int padA0[4]; qword axes[3];
};
extern qword D_00317560;
qword func_0028E910(struct Xf *xf, int n, qword v);
float func_00120080(qword a, qword b, qword *out);
qword func_0028E990(int a, int b, qword v);
static inline qword VSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Len(qword v)
{
    qword l, t;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=&j"(l), "=&j"(t) : "j"(v));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(l));
    return l;
}
static inline void StoreX(int *pd, qword q) { __asm__("sw %1,%0" : "=m"(*pd) : "r"(q)); }
void func_001A5EA8(struct Self *self)
{
    struct Xf *a = self->p4;
    struct Xf *b = self->p30;
    qword pa, pb, pc, d0, d1;
    self->q10 = a->r[3];
    self->axes[0] = a->r[0];
    self->axes[1] = a->r[1];
    self->axes[2] = a->r[2];
    self->rows[0] = b->r[0];
    self->rows[1] = b->r[1];
    self->rows[2] = b->r[2];
    pa = func_0028E910(a, a->nA0, D_00317560);
    pb = func_0028E910(self->p30, self->p4->nA0, D_00317560);
    pc = func_0028E910(self->p80, self->p4->nA0, self->q90);
    __asm__("" : "=j"(pb) : "0"(pb)); /* zero-insn: refs for allocation order */
    d0 = VSub(pb, pa);
    d1 = VSub(pc, pb);
    __asm__("" : "=j"(d1) : "0"(d1));
    StoreX(&self->f34, Len(d0));
    StoreX(&self->f38, Len(d1));
    self->f3C = func_00120080(d0, d1, &self->q40);
    self->q40 = func_0028E990(self->p4->nA0, self->p30->nA0, self->q40);
}
