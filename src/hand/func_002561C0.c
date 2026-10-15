// When the selection changes, clear the result fields, resolve its object, and apply the reset and restore requests through a 16-byte request structure.
// Reference algorithm: src/hand/func_0020A540.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct O { char pad[0x30]; int n30; };
struct L { int k; int rest[3]; };
struct S { char pad[0x29C]; char x26C[0x318 - 0x29C]; int a2DC[3]; int n2E8; };
void *func_00292034(void *p, int c, int n);
struct O *func_002387A8(void *p, int n);
void func_0019A2D0(struct O *po, struct L *pl);
void func_002561C0(struct S *p, int n)
{
    if (p->n2E8 != n) {
        struct O *po;
        p->n2E8 = n;
        func_00292034(p->a2DC, 0, 0xC);
        po = func_002387A8(p->x26C, 0xC8);
        if (po) {
            int k = po->n30;
            if (k == 1) {
                struct L l;
                func_00292034(&l, 0, sizeof(l));
                l.k = -1;
                func_0019A2D0(po, &l);
                func_00292034(p->a2DC, 0, 0xC);
                l.k = k;
                func_0019A2D0(po, &l);
            }
        }
    }
}
