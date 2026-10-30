// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct CM { char pad[0x138]; float sx, sy; };
qword func_001C9428(int k, struct CM *p, qword v);
qword func_001678C8(struct CM *p, qword v)
{
    union { qword q; float f[4]; } r;
    float x, y, z;
    r.q = func_001C9428(0, p, v);
    y = -r.f[1] / p->sx;
    z = r.f[2] / p->sy;
    x = r.f[0];
    r.f[2] = x;
    r.f[1] = z;
    r.f[0] = y;
    if (x > 1e-4f) {
        r.f[0] = y / x;
        r.f[1] = z / x;
    }

    return r.q;
}
