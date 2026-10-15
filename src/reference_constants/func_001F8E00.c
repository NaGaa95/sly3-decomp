// Reference algorithm: src/hand/func_001C6588.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(void *, int); };
struct O { int a[3]; struct VTE *vt; char pad[0x120]; int n150; char pad2[0x74]; float g238; };
struct CLOCK { float t; float dt; };
extern struct CLOCK D_0036BB98;
void func_001F7388(struct O *p);
void func_001F8E00(struct O *p)
{
    func_001F7388(p);
    if (!p->n150) {
        p->g238 -= D_0036BB98.dt;
        if (p->g238 <= 0.0f) { struct VTE *e = &p->vt[80]; e->pfn((char *)p + e->d, 4); }
    }
}
