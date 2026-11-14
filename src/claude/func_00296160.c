// Sly 2 counterpart: _sceFsIobSemaMK (decomp src/lib/_sceFsIobSemaMK.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
__asm__(".macro sq r, m\n\tsd \\r, \\m\n\t.endm\n\t.macro lq r, m\n\tld \\r, \\m\n\t.endm");
struct SemaParam { int currentCount; int maxCount; int initCount; int numWaitThreads; unsigned int attr; unsigned int option; };
extern int D_0034A6A8;
extern int D_0034A6AC;
extern char D_0032AA00[];
extern char D_0032AA10[];
int func_002936A0(struct SemaParam *);
void func_00296160(void)
{
    struct SemaParam p;
    if (D_0034A6A8 == -1) {
        p.option = (unsigned int)D_0032AA00;
        p.initCount = 1;
        p.maxCount = 1;
        D_0034A6A8 = func_002936A0(&p);
        p.option = (unsigned int)D_0032AA10;
        D_0034A6AC = func_002936A0(&p);
    }
}
