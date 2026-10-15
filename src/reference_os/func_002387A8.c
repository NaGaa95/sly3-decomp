// Sly 2 reference: src/hand/func_001EEEE0.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// Actual scalar class selectorA1; signed count is reread after each query.
// GCC zero-length tail expresses the original unknown inline array capacity.
// SLY3_CFLAGS: -Os -G0
struct L { int x; int c; void *a[0]; };
int func_0013B500(void *p, int key);
void *func_002387A8(struct L *pl, int key)
{
    int i;
    for (i = 0; i < pl->c; i++) {
        void *p = pl->a[i];
        if (func_0013B500(p, key)) return p;
    }
    return 0;
}
