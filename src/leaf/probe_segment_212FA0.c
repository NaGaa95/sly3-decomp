// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* probe the segment p0->p1 through the world: returns the hit point on a hit, otherwise p1; optionally reports the hit flag */
typedef int qword __attribute__((mode(TI)));
struct CTX { int a[4]; };
struct HIT { qword pos; qword v10; qword plane; qword v30; qword v40; qword v50; };
struct Prober { unsigned char prefix[0xDC]; int mask; };
extern char D_00475480[];
void func_001D2770(struct CTX *pctx);
void func_001D2798(struct CTX *pctx, int n);
int func_0025CDD0();
int func_0025CEC8();
void func_0025CF18(void *pg, qword a, qword b, int (*pfn)(), int c, int *pn0, int *pn1);
int func_00165000(int n, qword a, qword b, int n0, int n1, struct HIT *phit);
qword func_00167838(void *p, qword q);
qword func_00212FA0(struct Prober *self, void *context, qword p0, qword p1, int *phit)
{
    struct CTX ctx;
    struct HIT hit;
    int n0, n1;
    int found, mask;
    int (*pfn)();
    qword a = func_00167838(context, p0);
    qword b = func_00167838(context, p1);
    if (self) {
        pfn = func_0025CDD0;
        mask = self->mask;
    } else {
        pfn = func_0025CEC8;
        mask = 0;
    }
    func_001D2770(&ctx);
    func_0025CF18(D_00475480, a, b, pfn, mask, &n0, &n1);
    found = func_00165000(1, a, b, n0, n1, &hit);
    if (found)
        b = hit.pos;
    func_001D2798(&ctx, 2);
    if (phit)
        *phit = found;
    return b;
}
