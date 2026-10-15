// Apply range-triggered state transitions using the explicit third input as the state threshold and the original Sly 3 state IDs.
// Reference algorithm: src/hand/func_0022DD00.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(); };
struct O { char pad[0x18]; struct VTE *vt; };
struct S { char pad[0x80]; float gMin; float gMax; float *pg; int pad1; struct O *po; int pad2; short k; short state; };
void func_0028B188(void *pa, struct S *p);
void func_0028F068(void *pa, struct S *p, int state);
void func_0028C8F0(void *pa, struct S *p, int maximum_state)
{
    float g = *p->pg;
    if (g < p->gMin || p->gMax < g || p->state >= maximum_state) {
        if (p->po) {
            p->po->vt[4].pfn((char *)p->po + p->po->vt[4].d);
            switch (p->k) {
            case 11:
                if (p->state == 3 || p->state == 4) func_0028F068(pa, p, 8);
                else if (p->state != 2) func_0028F068(pa, p, 7);
                break;
            case 7:
                if (p->state == 3 || p->state == 4) func_0028F068(pa, p, 8);
                break;
            case 20:
                if (p->state != 2) func_0028F068(pa, p, 0x13);
                break;
            case 13:
                if (p->state != 2) func_0028F068(pa, p, 0xC);
                break;
            }
        } else {
            p->state = 0;
            func_0028B188(pa, p);
            func_0028F068(pa, p, 0);
        }
    }
}
