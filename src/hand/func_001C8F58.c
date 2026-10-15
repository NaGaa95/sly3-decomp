// Reconstructed from matching Sly 2 code with Sly 3 calls and data addresses.
struct M { float a[16]; };
extern struct M D_0034A160;
void func_00292034(void *p, int c, int n);
struct M *func_001C8F58(void *unused, struct M *pm)
{
    if (pm) {
        func_00292034(pm, 0, 0x40);
        pm->a[0] = pm->a[5] = pm->a[10] = pm->a[15] = 1.0f;
    }
    return &D_0034A160;
}
