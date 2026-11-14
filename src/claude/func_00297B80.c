// Sly 2 counterpart: sceSifLoadFileReset (decomp src/lib/sceSifLoadFileReset.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
extern volatile int D_0034A6B8;
extern char D_004CCBE8[];
void *func_00292034(void *, int, int);
int func_00297B80(void)
{
    D_0034A6B8 = -1; func_00292034(D_004CCBE8, 0, 4);
    return 0;
}
