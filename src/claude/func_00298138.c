// Sly 2 counterpart: supplement_crt0 (decomp src/lib/supplement_crt0.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};
extern char D_0032ACF0[];
extern char D_0032AD00[];
extern int D_0034A6D8;
extern int D_0034A6DC;
int func_002936A0(struct SemaParam *);

void func_00298138(void)
{
    struct SemaParam s1;
    struct SemaParam s2;

    s1.option = (unsigned int)D_0032ACF0;
    s1.maxCount = 1;
    s1.initCount = 1;
    s2.maxCount = 1;
    s2.initCount = 1;
    s2.option = (unsigned int)D_0032AD00;
    D_0034A6D8 = func_002936A0(&s1);
    D_0034A6DC = func_002936A0(&s2);
}
