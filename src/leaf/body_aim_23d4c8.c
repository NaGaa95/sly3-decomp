// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Re-aim the owner's body at the point `q` (port of Sly 2 func_001F4488): make sure the body is initialised, zero its
// first three direction floats, turn q - position(virtual 38) into the new direction and refresh the dependants.
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short p; void *pfn; };
struct VT { struct VTE a[39]; };
struct Body { char pad[0x94]; int n94; short k; char pad2[0xA0 - 0x9A]; int nA0; char pad3[0xB0 - 0xA4]; union { qword q; int a[4]; } v; };
struct Owner { char pad[0xC]; struct VT *pvt; char pad2[0x48 - 0x10]; struct Body *po; };
int func_0028EFD8(int);
void func_0028F068(struct Owner *, struct Body *, int);
qword func_0028E990(int, int, qword);
void func_0028F260(struct Owner *, struct Body *);
void func_0023DD40(struct Owner *);
void func_0023E228(struct Owner *);
void func_00241F00(struct Owner *, int);
void func_0023D4C8(struct Owner *p, qword q)
{
    struct Body *po = p->po;
    qword cur, d;
    if (!po || po->n94 != 1) return;
    if (!func_0028EFD8(po->k)) func_0028F068(p, po, 1);
    { float *pv = (float *)&po->v; pv[2] = 0.0f; pv[1] = 0.0f; pv[0] = 0.0f; }
    cur = ((qword (*)(void *))p->pvt->a[38].pfn)((char *)p + p->pvt->a[38].d);
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(q), "j"(cur));
    po->v.q = func_0028E990(0, po->nA0, d);
    func_0028F260(p, po);
    func_0023DD40(p);
    func_0023E228(p);
    func_00241F00(p, 0);
}
