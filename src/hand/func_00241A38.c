// Map a key to the negative index representation used by the state; clear it when the key is absent or -1.
// Reference algorithm: src/hand/func_001F81E0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct A { char pad[0x9C]; int c; int *a; int n; };
void func_00241A38(struct A *p, int n)
{
    int i;
    if (n == -1) {
        p->n = 0;
        return;
    }
    for (i = 0; i < p->c; i++) {
        if (n == p->a[i]) {
            p->n = -(i + 3);
            return;
        }
    }
    p->n = 0;
}
