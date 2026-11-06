// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001E7500: queries the objects (up to 0x80) touching the segment from-to and clips each one with func_001E6830
// (convex volume clip, 2 LSG records of 0x60 bytes). Returns the first object whose clip fails or whose first piece
// starts at au[0] != 0, else the object with the smallest au[1] below 1.0f (0 if none).
// Allocation note: `from` and `to` are passed through pointers (Clip); taking their address makes purge_addressof
// renumber them above `i`, which decides the s3/s4 allocation tie (index = s3, from = s4).
typedef int qword __attribute__((mode(TI)));
struct LSG {
    qword apos[2];
    qword anormal[2];
    float au[2];
    char pad[0x60 - 0x48];
};
int func_001EDFE0(void *a, void *b, qword from, qword to, int c, void **buf);
int func_001E6830(void *e, qword from, qword to, int n, struct LSG *r);
static __inline__ int Clip(void *e, const qword *from, const qword *to, struct LSG *r)
{
    return func_001E6830(e, *from, *to, 2, r);
}
void *func_001E7500(void *a, void *b, qword from, qword to)
{
    void *buf[0x80];
    struct LSG r[2];
    void *best = 0;
    float min;
    int i, n;
    n = func_001EDFE0(a, b, from, to, 0x80, buf);
    min = 1.0f;
    for (i = 0; i < n; i++) {
        void *e = buf[i];
        if (!Clip(e, &from, &to, r) || r[0].au[0] != 0.0f) {
            best = e;
            break;
        }
        if (r[0].au[1] >= min) continue;
        min = r[0].au[1];
        best = e;
    }
    return best;
}
