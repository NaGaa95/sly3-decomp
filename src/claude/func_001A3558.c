// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } QU;
struct Entry { short delta, pad; unsigned char *(*fn)(void *); };
struct Obj { int pad[3]; struct Entry *vt; };
void func_001A3558(struct Obj *self, int unused, QU *out)
{
    struct Entry *e = &self->vt[36];
    out->q = *(qword *)(e->fn((char *)self + e->delta) + 0x30);
    out->f[2] += -150.0f;
}
