// Reference: Sly 2 src/lib/func_002309E8.c; target Sly 3 0x0028F680.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31
void *func_00292034(void *, int, int); void func_0028F730(void *, void *, float, float *, float *);
void func_0028F680(void *a, void *b, float *m, float *n, float f)
{
    if (m) {
        func_00292034(m, 0, 0x40);
        m[0] = m[5] = m[10] = m[15] = 1.0f;
    }
    if (n) func_00292034(n, 0, 0x40);
    func_0028F730(a, b, f, m, n);
}
