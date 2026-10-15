// Reference algorithm: src/hand/func_00144388.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_0023E178(void *p, void *a);
int func_00272FB0(void *p, void *a, int b);
void func_00208A08(void *p, void *a, int b);
void func_00156948(char *p, void *a)
{
    int x = func_0023E178(p, a);
    x = func_00272FB0(p + 0x1290, a, x);
    func_00208A08(p + 0x940, a, x);
}
