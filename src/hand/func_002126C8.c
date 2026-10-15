// Initialize the base state, two vectors, counters, and scalar defaults.
// Reference algorithm: src/hand/func_001D6A90.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern float D_00325B84;
struct V { float x, y, z; };
struct S { char p0[0x60]; struct V v70; int pad; int n80; float g84; char p1[8]; struct V v90; int pad2; int nA0; float gA4; char p2[8]; float gB0; };
void func_001C7340(struct S *p);
static inline void SetVector(struct V *pv, float x, float y, float z) { pv->x = x; pv->y = y; pv->z = z; }
void func_002126C8(struct S *p) {
    func_001C7340(p);
    SetVector(&p->v70, 0, 0, 0);
    p->n80 = 0;
    p->g84 = D_00325B84;
    SetVector(&p->v90, 0, 1.0f, 0);
    p->gB0 = 0.5f;
    p->gA4 = D_00325B84;
    p->nA0 = 0;
}
