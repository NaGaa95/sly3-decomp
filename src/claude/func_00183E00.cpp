// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int qword __attribute__((mode(TI)));
struct V4 { float a[4]; } __attribute__((aligned(16)));
struct M3 { qword r[3]; };
struct M4 { qword r[4]; };
struct ALLOCREQ { int cb; int nKind; ALLOCREQ(int c, int k) : cb(c), nKind(k) {} };
class CTX { public: char b; CTX(); ~CTX(); };
struct Sample { float t; int pad[3]; M4 xf; };
struct Self {
    unsigned char pad[0x40]; void *path; int snap; unsigned char pad48[0x50 - 0x48]; float step;
    unsigned char pad54[0x78 - 0x54]; int count; Sample *samples;
};
extern "C" {
extern qword D_00317550;
void func_001C7DC8(Self *self);
float func_0022DFD8(void *path);
void *func_001D2470(const ALLOCREQ &req);
void func_001DC7E0(int *a, int *b);
void func_0022E330(void *path, float t, V4 *pos, V4 *dir);
void func_00184580(Self *self, V4 *pos, V4 *normal, int a, int b, float up, float down);
M3 func_0011CBF0(qword dir, qword up);
M4 func_0011D6D8(qword pos, M3 *m, float g);
}
static inline void *Allocate(int cb) { ALLOCREQ req(cb, 0x10); return func_001D2470(req); }
extern "C" void func_00183E00(Self *self)
{
    int a, b;
    int i;
    float t;
    func_001C7DC8(self);
    self->count = (int)(func_0022DFD8(self->path) / self->step);
    self->samples = (Sample *)Allocate(self->count * sizeof(Sample));
    CTX ctx;
    if (self->snap) func_001DC7E0(&a, &b);
    t = 0.0f;
    for (i = 0; i < self->count; i++) {
        Sample *s = &self->samples[i];
        V4 pos, dir, up;
        s->t = t;
        func_0022E330(self->path, t, &pos, &dir);
        if (self->snap) func_00184580(self, &pos, &up, a, b, 100.0f, -350.0f);
        else *(qword *)&up = D_00317550;
        M3 m;
        m = func_0011CBF0(*(qword *)&dir, *(qword *)&up);
        s->xf = func_0011D6D8(*(qword *)&pos, &m, 1.0f);
        t += self->step;
    }
}
