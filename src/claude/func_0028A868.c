// SLY3_CFLAGS: -Os -G0
struct F { float x0; float x4; };
void func_00292540(void *base, int n, int size, int (*cmp)(struct F *, struct F *));
int func_0028A838(struct F *a, struct F *b);
int func_0028A868(int n, struct F *a)
{
    struct F *end, *p, *out;
    if (!n)
        return 0;
    func_00292540(a, n, 8, func_0028A838);
    end = &a[n];
    out = a;
    for (p = &a[1]; p < end; p++) {
        if (p->x0 > out->x4) {
            out++;
            *out = *p;
        } else {
            out->x4 = p->x4;
        }
    }
    out++;
    return out - a;
}
