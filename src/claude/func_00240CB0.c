// SLY3_CFLAGS: -Os -G0
// Create and set up a 0x60-byte object; hand it back through *pp (after vtable slot 1) or release it.
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta; short pad; void (*pfn)(void *); };
struct O
{
    char pad0[0xC];
    struct VTE *vt;
    char pad10[4];
    void *p14, *p18, *p1C, *p20;
    char pad24[4];
    int n28;
    char pad2C[4];
    qword q30;
    qword q40;
};
void *func_002409E0(int cb);
struct O *func_002BF288(void *pv);
void func_00240C78(struct O *po, int n);
void func_00240A28(struct O *po);
void func_00240CB0(void *p14, void *p18, void *p1C, void *p20, int n, int n28, qword q30, qword q40, struct O **ppo)
{
    struct O *po = func_002BF288(func_002409E0(0x60));
    po->p14 = p14;
    po->p18 = p18;
    po->p1C = p1C;
    po->p20 = p20;
    po->n28 = n28;
    po->q30 = q30;
    po->q40 = q40;
    func_00240C78(po, n);
    if (ppo) {
        po->vt[1].pfn((char *)po + po->vt[1].delta);
        *ppo = po;
    } else {
        func_00240A28(po);
    }
}
