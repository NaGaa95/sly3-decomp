// SLY3_CFLAGS: -Os -G0
struct E { int n0; int n4; int n8; int nC; int n10; int n14; };
struct P { char pad[0x48]; int n58; struct E *ae; };
struct E *func_0023A168(void *p, int n, struct E **ape);
struct E *func_0023A380(struct P *p, int mask, int key)
{
    struct E *ap[64];
    int c;
    int i;
    c = 0;
    for (i = 0; i < p->n58; i++) {
        struct E *pe = &p->ae[i];
        if (!(pe->nC & mask)) continue;
        if (pe->n4 == key) {
            ap[c++] = pe;
            continue;
        }
        if ((pe->nC & 1) && pe->n8 == key)
            ap[c++] = pe;
    }
    if (c == 0) return 0;
    return func_0023A168(p, c, ap);
}
