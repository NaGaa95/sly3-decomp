// Apply the scalar setting to matching objects in the collected range, then recurse through matching child objects.
// Reference algorithm: src/hand/func_001F80D0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct L { char pad[0x24]; struct L *next; char pad2[0x54 - 0x28]; struct L *first; char pad3[0x60 - 0x58]; struct L *end; char pad4[0xA4 - 0x74]; int c; void **ap; };
int func_0013B500(void *, int);
void func_00237B70(void *, float);
void func_00241928(struct L *p, float f)
{
    int i;
    struct L *q;
    for (i = 0; i < p->c; i++) {
        void *pv = p->ap[i];
        if (func_0013B500(pv, 0xB2)) func_00237B70(pv, f);
    }
    for (q = p->first; q != p->end; q = q->next)
        if (func_0013B500(q, 0x2F)) func_00241928(q, f);
}
