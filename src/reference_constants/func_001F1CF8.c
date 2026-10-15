// Reference algorithm: src/hand/func_001F1CF8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct X {
    char pad[0x44];
    int n54;
};
struct O {
    char pad[0x1A0];
    struct X *px;
};
struct Ent {
    int a0;
    int a4;
    int a8;
    int aC;
};
struct P {
    char pad[0x414];
    struct Ent a[8];
    int n484;
    int n488;
    int n48C;
    int n490;
    char unknown4A4[8];
    void *owner494;
};
struct G;
extern struct G D_00475480;
struct O *func_0017E1B8(struct G *, int, int, void *);
int func_0013B500(struct O *, int);
int func_001F29A0(void *, struct O *, int, int);
void func_001F18D0(struct P *);
void func_001F1CF8(struct P *p) {
    p->n48C = 0;
    for (; p->n488 < p->n484; p->n488++) {
        struct Ent *pe = &p->a[p->n488];
        struct O *po = func_0017E1B8(&D_00475480, 4, pe->a0, p->owner494);
        int a8, k;
        if (!po) continue;
        a8 = pe->a8;
        k = 0x307;
        if (func_0013B500(po, 0x68)) {
            struct X *px = po->px;
            if (px) {
                int n = px->n54;
                if (n == -1 || n == 0) {
                    p->n48C = 1;
                    break;
                }
                if (n != 1) continue;
            }
            k = 0x308;
        }
        if (func_001F29A0(p->owner494, po, a8, k) == 1) p->n48C = 1;
        break;
    }
    func_001F18D0(p);
}
