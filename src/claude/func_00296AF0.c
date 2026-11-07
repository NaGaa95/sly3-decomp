// Sly 2 counterpart: sceFsReset (decomp src/lib/sceFsReset.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
// 4/13 with gnu-reorder: the `sw $zero,D_0034A69C` is scheduled last (into the jal slot); target issues it right after `sd ra`.
// Scheduler difference (all 2.95 builds, -mcpu=*, sched flags, volatile, 2.96 tried). Same as sceSifLoadFileReset.
extern int D_0034A69C; extern char D_004CC728[];
void *func_00292034(void *p, int c, unsigned int n);
int func_00296AF0(void)
{
    D_0034A69C = 0;
    func_00292034(D_004CC728, 0, 4);
    return 0;
}
