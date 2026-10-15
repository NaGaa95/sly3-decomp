// Reference algorithm: src/hand/func_0017CDB8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct T { char pad[0x10F4]; void *pF84; float gF88; int nF8C; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x28]; float g3C; };
float func_0022DFD8(void *p);
float func_0022DFB0(void *p);
void func_001DA630(struct S *p, int n);
void func_001DA6F0(struct S *p, int f) {
    void *pv = p->pt->pF84; if (f) p->g3C = func_0022DFD8(pv); else p->g3C = func_0022DFB0(pv);
    p->pt->nF8C = p->pt->gF88 < p->g3C;
    func_001DA630(p, 0);
}
