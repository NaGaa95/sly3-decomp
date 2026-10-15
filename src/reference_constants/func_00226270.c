// Reference algorithm: src/hand/FWipingAseg__FP4ASEG.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct ASEG { char pad[0x64]; int c; int a[1]; };
int func_00226270(struct ASEG *paseg, int n)
{
    int i;
    for (i = 0; i < paseg->c; i++) {
        if (paseg->a[i] == n) return 1;
    }
    return 0;
}
