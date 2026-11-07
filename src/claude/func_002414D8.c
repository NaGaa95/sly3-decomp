// SLY3_CFLAGS: -Os -G0
// Collect the entries (0xD0 bytes each) accepted by an optional filter; returns their count.
struct E { char pad[0xD0]; };
struct S { char pad[0xD0]; int ce; struct E *ae; };
int func_002414D8(struct S *p, int (*pfn)(void *, struct E *), void *pv, struct E **ape)
{
    int c = 0;
    int i;
    for (i = 0; i < p->ce; i++) {
        struct E *pe = &p->ae[i];
        if (!pfn || pfn(pv, pe)) {
            ape[c] = pe;
            c++;
        }
    }
    return c;
}
