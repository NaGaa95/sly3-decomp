// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct RECT { int x0, y0, x1, y1; };
struct Q { char pad[0x160]; struct RECT r; };
struct M { float a, b, c, d; float x, y; int pad[2]; };
extern struct { int mode; int w; int h; } D_0036DBE0;
void *memset(void *, int, unsigned int);
void func_00262848(void *p, struct M *m);
static inline float X(qword q) { float f; __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q)); return f; }
static inline float Y(qword q) { float f; __asm__("prot3w %0, %1" : "=r"(f) : "r"(q)); return f; }
static inline int DX(struct RECT *r) { return r->x1 - r->x0; }
static inline int DY(struct RECT *r) { return r->y1 - r->y0; }
void func_002625D8(void *p, struct Q *q, qword v)
{
    struct M m;
    memset(&m, 0, sizeof(m));
    m.d = 1.0f;
    m.a = 1.0f;
    {
        float x = ((float)(q->r.x0 + q->r.x1) + X(v) * (float)DX(&q->r)) * 0.5f;
        float y = ((float)(q->r.y0 + q->r.y1) - Y(v) * (float)DY(&q->r)) * 0.5f;
        m.x = x * 640.0f / D_0036DBE0.w;
        m.y = y * 480.0f / D_0036DBE0.h;
    }
    func_00262848(p, &m);
}
