// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Build a screen-space scale/offset transform from a pixel rectangle (640x480).
struct RECT { int x0, y0, x1, y1; };
struct R { char pad[0x150]; struct RECT rc; };
void *func_00292034(void *, int, int);
void func_00262848(void *, float *);
void func_00262770(void *a, struct R *r)
{
    struct RECT *rc = &r->rc;
    float sx = (float)(rc->x1 - rc->x0) * (1.0f / 640.0f);
    float sy = (float)(rc->y1 - rc->y0) * (1.0f / 480.0f);
    float m[8];
    func_00292034(m, 0, sizeof(m));
    m[0] = sx;
    m[3] = sy;
    m[4] = (float)rc->x0;
    m[5] = (float)rc->y0;
    func_00262848(a, m);
}
