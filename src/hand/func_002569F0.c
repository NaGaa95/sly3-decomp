// Initialize motion thresholds, scalar defaults, mode and selection identifiers, then bind the embedded state to its associated resource.
// Reference algorithm: src/hand/func_0020AD38.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern float D_00327494;
struct S { char pad[0x40]; int n50; float f54, f58, f5C, f60, f64, f68, f6C; char pad2[0x7C - 0x70]; int n7C; int n80; int n84; char pad3[0xA8 - 0x88]; int nA8; char unknown9C[0xC]; void *pAC; char unknownAC[4]; char eB0[4]; };
void func_001C7340(struct S *p);
void func_00254BB8(void *pe, void *p);
void func_002569F0(struct S *p)
{
    func_001C7340(p);
    p->n50 = 0;
    p->f54 = 300.0f;
    p->f58 = -5000.0f;
    p->f5C = 5000.0f;
    p->f60 = 0.2f;
    p->f64 = 0.5f;
    p->f68 = 0.17453295f;
    p->nA8 = 1;
    p->n7C = -1;
    p->n80 = -1;
    p->n84 = -1;
    p->f6C = D_00327494;
    func_00254BB8(p->eB0, p->pAC);
}
