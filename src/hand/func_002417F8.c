// Apply two scalar settings to each collected object matching type identifier 0xB3.
// Reference algorithm: src/hand/func_001F7FA0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct P { char pad[0x94]; int c; void **ap; };
int func_0013B500(void *, int);
void func_00237DD8(void *, float, float);
void func_002417F8(struct P *p, float f, float g)
{
    int i;
    for (i = 0; i < p->c; i++) {
        void *q = p->ap[i];
        if (func_0013B500(q, 0xB3)) func_00237DD8(q, f, g);
    }
}
