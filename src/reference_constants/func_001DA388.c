// Reference algorithm: src/hand/func_0017D110.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct T { char pad[0x10F4]; void *pF84; float gF88; int nF8C; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x24]; float g38; };
float func_0022DFD8(void *p);
float func_0022DFB0(void *p);
void func_001DA2C8(struct S *p, int n);
void func_001DA388(struct S *p, int f) {
    void *pv = p->pt->pF84; if (f) p->g38 = func_0022DFD8(pv); else p->g38 = func_0022DFB0(pv);
    p->pt->nF8C = p->pt->gF88 < p->g38;
    func_001DA2C8(p, 0);
}
