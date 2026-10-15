// Look up an object descriptor by ID in the registered descriptor array using an explicit descriptor pointer.
// Reference algorithm: src/hand/func_001EC820.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0

struct E { int oid; char pad[0x28]; };
extern int D_0046FF38;
extern struct E *D_0046FF3C;
struct E *func_00235E60(int oid)
{
    int i;
    struct E *entry;
    if (oid == -1) return 0;
    for (i = 0; i < D_0046FF38; i++) {
        if ((entry = D_0046FF3C + i)->oid == oid) return entry;
    }
    return 0;
}
