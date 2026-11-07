// Sly 2 counterpart: _doMC (decomp src/lib/_doMC.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct {
    char d[0x1C];
} MCB;
typedef struct {
    int base;
    int x4;
    char pad8[0x28 - 0x8];
    void (*fnA[4])(MCB *);
    void (*fnB[4])(MCB *);
    MCB a[4];
    MCB b[4];
    int x128;
    int n;
    int flag;
    int pad134;
    int enable;
    int flag2;
} REFS;
typedef struct {
    char pad0[0x5A0];
    REFS refs[2];
    char pad820[0x830 - 0x820];
    int x830;
} MP;
extern char D_0032C758[];
void _sceMpegError(MP *, char *);
void func_002B0F78(int, int);
void func_002B0E88(int, int, int);
void func_002AF468(MP *mp, int idx)
{
    int i;
    if (mp->refs[idx].enable) {
        for (i = 0; i < mp->refs[idx].n; i++) {
            mp->refs[idx].fnA[i](&mp->refs[idx].a[i]);
            mp->refs[idx].fnB[i](&mp->refs[idx].b[i]);
        }
    }
    if (mp->refs[idx].flag && mp->refs[idx].flag2)
        _sceMpegError(mp, D_0032C758);
    if (mp->refs[idx].flag)
        func_002B0F78(mp->refs[idx].x128, mp->refs[idx].x4);
    else if (mp->refs[idx].flag2)
        func_002B0F78(mp->refs[idx].x128, mp->x830);
    else
        func_002B0E88(mp->refs[idx].x128, mp->x830, mp->refs[idx].x4);
}
