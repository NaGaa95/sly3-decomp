// Reference algorithm: src/hand/func_00210678.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void *func_0017E1B8(void *pv, int k, int id, void *owner);
void *func_00235F80(int id);
int func_0013B500(void *p, int cid);
void func_00241928(void *p, float f);
void func_00237B70(void *p, float f);
void func_0025DA70(void *pv, int id1, int id2, void *owner, float f) {
    void *p1 = 0;
    void *p2 = 0;
    if (id1 != -1) {
        void *q = func_0017E1B8(pv, 4, id1, owner);
        if (q && func_0013B500(q, 0x2F)) p1 = q;
    }
    if (id2 != -1) {
        p2 = func_00235F80(id2);
        if (p2 && !func_0013B500(p2, 0xB2)) p2 = 0;
    }
    if (p1) func_00241928(p1, f);
    if (p2) func_00237B70(p2, f);
}
