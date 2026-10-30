// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct M4 { qword rows[4]; };
struct F4 { float m[4][4]; };
void func_0011D558(struct M4 *out, struct M4 *a, struct M4 *b);

void func_0014B9F8(int n, struct M4 *a, struct M4 *b, struct M4 *out)
{
    int count = n / 4;
    int i, j, k;
    struct M4 acc, t;
    for (k = 0; k < count; k++) {
        struct F4 *f = (struct F4 *)&a[k];
        f->m[0][3] = 1.0f;
        f->m[1][3] = 1.0f;
        f->m[2][3] = 1.0f;
        f->m[3][3] = 1.0f;
    }
    func_0011D558(&acc, a, b);
    *out = acc;
    for (i = 1; i < count; i++) {
        func_0011D558(&t, &a[i], &b[i]);
        {
            qword *pt = t.rows, *pd = acc.rows, *po = out->rows;
            for (j = 0; j < 4; j++) {
                qword r;
                __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(*po), "j"(*pt));
                *pd = r;
                pt++; po++; pd++;
            }
        }
        *out = acc;
    }
}
