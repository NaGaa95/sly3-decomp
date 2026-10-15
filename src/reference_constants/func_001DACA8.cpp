// Complete original function, inputs and emitted data independently reviewed.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CTX {
    int a[4];
    CTX();
    ~CTX();
};
struct AREQ {
    int cb;
    int align;
    AREQ(int c, int a) {
        cb = c;
        align = a;
    }
};
struct S {
    int x0;
    int x4;
    int x8;
    int xC;
    int x10;
};
extern "C" {
    char *func_001D25B0(const AREQ &r);
    void func_001D2898(void *dst, void *src, int cb);
}
static inline char *Alloc(int cb, int align) {
    return func_001D25B0(AREQ(cb, align));
}
extern "C" void func_001DACA8(S *p, int cb, char *pb) {
    int ch = p->x4;
    if (ch != 0x10) return;
    if (p->xC == 1) return;
    CTX ctx;
    char *pbCur = pb;
    int chunk = p->xC << 10;
    char *tmp = Alloc(chunk, 0x10);
    int cbCur = cb;
    while (cbCur) {
        int i = 0, k = 0, off;
        for (off = 0; off < chunk; off += p->x10) {
            func_001D2898(tmp + ((i << 10) + k * p->x10), pbCur + off, p->x10);
            i++;
            if (i >= p->xC) {
                k++;
                i = 0;
            }
        }
        func_001D2898(pbCur, tmp, chunk);
        cbCur -= chunk;
        pbCur += chunk;
    }
}
