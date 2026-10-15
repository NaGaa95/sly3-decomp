// Collect shortest next-edge candidates matching the path mask and current endpoints, then choose among them.
// Reference algorithm: src/hand/func_001F0B80.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct E { int n0; int n4; int n8; int nC; int n10; int n14; };
struct P { char pad[0x48]; int n58; struct E *ae; };
int func_00239B20(struct P *, int, int, int);
int func_0023A168(struct P *, int, struct E **);
int func_0023A210(struct P *p, int mask, int a, int b)
{
    struct E *ap[64];
    int c;
    int i;
    int n;
    if (a == b) n = 1;
    else n = func_00239B20(p, mask, a, b);
    c = 0;
    for (i = 0; i < p->n58; i++) {
        struct E *pe = &p->ae[i];
        if (!(pe->nC & mask)) continue;
        if (pe->n4 == a && func_00239B20(p, mask, pe->n8, b) == n - 1) {
            ap[c++] = pe;
            continue;
        }
        if ((pe->nC & 1) && pe->n8 == a && func_00239B20(p, mask, pe->n4, b) == n - 1)
            ap[c++] = pe;
    }
    if (c == 0) return 0;
    return func_0023A168(p, c, ap);
}
