// Reference algorithm: src/hand/func_00162250.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct E {
    int n0;
    int oid;
    int n8;
    int id;
    int f10;
    int f14;
};
struct G;
extern struct G D_00475480;
int func_0025E150(void);
int func_0017DE98(struct G *pg, int kind, int oid, void *owner, int c, void **apv);
int func_0013B500(void *pv, int n);
void *func_0023FB68(void *pv, int n);
void func_00239FE0(void *p, int id);
void func_00239CE8(void *p, int id);
void func_00185C30(void *pvUnused, struct E *pe, int n, int k) {
    void *pv;
    void *ps;
    int id;
    if (pe->n0 != -1 && pe->n0 != n) return;
    if (pe->f10 && !k) return;
    if (pe->f14 != -1 && pe->f14 != func_0025E150()) return;
    if (func_0017DE98(&D_00475480, 0x205, pe->oid, 0, 1, &pv) != 1) return;
    if (!func_0013B500(pv, 0x2F)) return;
    ps = func_0023FB68(pv, pe->n8);
    if (!ps) return;
    id = pe->id;
    if (pe->n0 == -1) {
        switch (n) {
            case 0: id = 0x6E3;
            break;
            case 1: id = 0x6E4;
            break;
            case 2: id = 0x6E5;
            break;
            case 3: id = 0x6E6;
            break;
        }
    }
    if (id != -1) {
        if (k == 1 || k == 4) func_00239FE0(ps, id);
        else func_00239CE8(ps, id);
    }
}
