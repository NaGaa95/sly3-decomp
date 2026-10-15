// Update the alternate attached transform through the conversion routine, refresh dependent resources, and clear the final state flag.
// Reference algorithm: src/hand/func_001F4898.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct O { char pad[0x98]; short k; char pad2[0xA0 - 0x9A]; int nA0; char pad3[0xB0 - 0xA4]; qword q; };
struct P { char pad[0x4C]; struct O *po; };
struct Q { char pad[0x50]; int n60; };
int func_0028EFD8(int);
void func_0028F068(void *, struct O *, int);
qword func_0028E990(int, int, qword);
void func_0028F260(void *, struct O *);
void func_0023DD40(void *);
void func_0023E228(void *);
void func_00241F00(void *, int);
void func_0023D9D0(struct P *p, qword v)
{
    struct O *po;
    if (!func_0028EFD8(p->po->k)) func_0028F068(p, p->po, 1);
    po = p->po;
    po->q = func_0028E990(((struct Q *)p)->n60, po->nA0, v);
    func_0028F260(p, p->po);
    func_0023DD40(p);
    func_0023E228(p);
    func_00241F00(p, 0);
}
