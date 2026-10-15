// Sly 2 reference: src/hand/func_001C18B8.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct E { int x0; unsigned short x4; unsigned short x6; };
void func_001D2898(void *dst, void *src, int cb);
void func_001EE170(int n, struct E *a, int key)
{
    int i, iFirst, iLast;
    struct E *pe;
    i = 0;
    pe = a;
    goto test;
    for (;;) {
        pe++;
        i++;
    test:
        if (i >= n) break;
        if (pe->x6 == key) {
            if (pe->x4 != 0) {
                iFirst = i;
                continue;
            }
            iLast = i;
            break;
        }
    }
    func_001D2898(&a[iFirst], &a[iFirst] + 1, (iLast - iFirst - 1) * sizeof(struct E));
    func_001D2898(&a[iLast] - 1, &a[iLast] + 1, (n - iLast - 1) * sizeof(struct E));
}
