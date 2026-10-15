// Set inverse-duration motion scaling, with the Sly 3 reset flag at bit 52 and cached scale field at 0x104.
// Reference algorithm: src/hand/func_001F7C68.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef unsigned long ulong;
struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { struct VTE a[9]; };
struct P { char pad[0xC]; struct VT *pvt; char pad2[0x28 - 0x10]; ulong fl; char pad3[0x104 - 0x30]; float g12C; };
void func_00241460(struct P *, float);
void func_002413E0(struct P *, float);
void func_00241338(struct P *p, float f)
{
    if (f <= 0.0f) {
        func_00241460(p, 0.0f);
        func_002413E0(p, 1.0f);
    } else {
        if (p->fl & (1L << 52)) {
            p->pvt->a[8].pfn((char *)p + p->pvt->a[8].d);
            p->g12C = 0.0f;
        }
        func_00241460(p, 1.0f / f);
    }
}
