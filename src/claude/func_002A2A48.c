// Sly 2 counterpart: sceMcSync (decomp src/lib/sceMcSync.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
// (Claude agent) matches with ee-gcc 2.9 (old 2.95.3-114 near miss)
extern int _mc_errno;
extern int D_0034DF94;
extern int D_0034DF98;
extern int D_004D27C0;
int func_002936F0(int);
int func_002936E0(int);
int func_002936C0(int);
int func_002A2A48(int mode, int *cmd, int *result)
{
    int r;
    if (!_mc_errno) return -1;
    if (func_002936F0(D_0034DF98) < 0) r = 1; else r = 0;
    if (mode == 0 && r) {
        func_002936E0(D_0034DF98);
        r = 0;
    }
    r = !r;
    if (cmd) *cmd = _mc_errno;
    if (r) {
        _mc_errno = 0;
        if (result) *result = D_004D27C0;
        func_002936C0(D_0034DF94);
    }
    return r;
}
