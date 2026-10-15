// Sly 2 reference: src/hand/func_001AAF18.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct PMF { short delta; short pad; int (*pfn)(void *); };
struct S { int x0; int x4; struct PMF pmf; int x10; };
extern char D_00375290[];
extern int D_00349F90[];
void func_002936E0(int);
void func_002936C0(int);
void func_002934E0(void);
void *func_00292034(void *, int, unsigned int);
void func_001CEE48(struct S *s)
{
    func_002936E0(s->x0);
    s->x10 = s->pmf.pfn(D_00375290 + s->pmf.delta);
    func_00292034(&s->pmf, 0, sizeof(s->pmf));
    s->x4 = -1;
    D_00349F90[0] = -1;
    func_002936C0(s->x0);
    func_002934E0();
}
