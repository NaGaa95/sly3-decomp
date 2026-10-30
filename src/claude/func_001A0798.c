// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Entry { short delta, pad; void *fn; };
struct Obj { unsigned char pad[0x24]; struct Entry *vt; };
void func_001A0798(struct Obj *self, int a, float *out, int c, int d)
{
    float value;
    struct Entry *e = &self->vt[2];
    ((void (*)(void *, int, float *))e->fn)((char *)self + e->delta, a, &value);
    e = &self->vt[3];
    ((void (*)(void *, int, int, int, float))e->fn)((char *)self + e->delta, a, c, d, value);
    if (out) {
        *out = value;
    }
}
