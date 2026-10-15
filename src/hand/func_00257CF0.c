// Resolve the requested object through its direct owner or the supported parent object.
// Reference algorithm: src/hand/func_00174898.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct O;
struct L { struct O *po; };
struct O { char pad[0x14]; struct L *p14; char pad2[0x1D0]; struct O *p200; };
int func_0013B500(struct O *p, int n);
struct O *func_00257CF0(struct O *p) {
    if (!p) return 0;
    if (func_0013B500(p->p14->po, 0x3A)) return p->p14->po;
    if (func_0013B500(p, 0x59) && func_0013B500(p->p200->p14->po, 0x3A)) return p->p200->p14->po;
    return 0;
}
