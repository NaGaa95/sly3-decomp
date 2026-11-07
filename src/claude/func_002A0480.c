// Sly 2 counterpart: sceCdSync (decomp src/lib/sceCdSync.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
extern int D_0034C390;
extern volatile int D_0034C3B4;
extern char D_0032B660[];
extern char D_0034D550[];
int func_002955E0(const char *, ...);
int func_00294198(int);
int func_00296108(void *);
int func_002A0480(int mode)
{
    if (mode == 0) {
        if (D_0034C390 > 0) func_002955E0(D_0032B660);
        while (D_0034C3B4 || func_00296108(D_0034D550)) func_00294198(0xFA0);
        return 0;
    }
    if (D_0034C3B4 || func_00296108(D_0034D550)) return 1;
    return 0;
}
