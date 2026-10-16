// SLY3_CFLAGS: -Os -G0
struct S { int a, b, k, c; };
static __inline__ int FX(struct S *p) { return p->c == 9 || p->c == 10; }
int func_001B5DD8(void *context, int ignored_event) {
    struct S *p = (struct S *)context;
    switch (p->k) {
    case 8: if (FX(p)) goto one; break; case 0xC: one: return 1;
    }
    return 0;
}
