// Sly 2 counterpart: _sceFsSemInit (decomp src/lib/_sceFsSemInit.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0 
// SLY3_ASM: gnu-reorder-db
struct SemaParam { int currentCount; int maxCount; int initCount; int numWaitThreads; unsigned int attr; unsigned int option; };
extern int D_0034A6A4;
extern char D_0032AA88[];
int func_002936A0(struct SemaParam *);
void func_00296778(void)
{
    struct SemaParam p;
    if (D_0034A6A4 == -1) {
        p.option = (unsigned int)D_0032AA88;
        p.initCount = 1;
        p.maxCount = 1;
        D_0034A6A4 = func_002936A0(&p);
    }
}
