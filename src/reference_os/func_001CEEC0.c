// Sly 2 reference: src/hand/func_001AAF90.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct PMF { short delta; short pad; int (*pfn)(void *); };
struct S { int x0; int x4; struct PMF pmf; int x10; };
struct ThreadParam { int attr; void *entry; void *stack; int stackSize; void *gpReg; int initPriority; int currentPriority; unsigned int attr2; int option; int waitType; int waitId; int wakeupCount; };
extern char D_00372DF0[], D_00370D00[];
extern int D_00349F90[];
void D_001CEE48(struct S *s);
void func_001CEF70(struct S *s);
void *func_00292034(void *p, int c, unsigned int n);
int func_002934A0(struct ThreadParam *tp);
void func_00294260(int id, void *arg);
void func_001CEEC0(struct S *s, struct PMF pmf)
{
    struct ThreadParam tp;
    func_001CEF70(s);
    s->pmf = pmf;
    s->x10 = 0x21;
    func_00292034(&tp, 0, sizeof(tp));
    tp.entry = D_001CEE48;
    tp.stack = D_00370D00;
    tp.gpReg = D_00372DF0;
    tp.stackSize = 0x4000;
    tp.initPriority = 3;
    s->x4 = func_002934A0(&tp);
    D_00349F90[0] = s->x4;
    func_00294260(s->x4, s);
}
