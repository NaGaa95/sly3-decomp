// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M4 { U r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct HIT { U point[2]; U plane[2]; float parameter[2]; int kind; void *face[2]; int unk54[3]; };
struct Owner { char pad0[0xC]; VTE *pvt; };
struct Reg { char pad0[0x60]; Owner *owner; };
struct Req { Reg *reg; };
struct Shape;
struct Self {
    char pad0[0x70]; qword q70; char pad80[0]; qword q80;
    char pad90[0xE8 - 0x90]; VTE *hooks;
};
extern "C" int func_00164A10(Shape *s, qword a, qword b, int n, HIT *ph);
static inline qword Point(const M4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(r) : "j"(m.r[0].q), "j"(m.r[1].q), "j"(m.r[2].q), "j"(m.r[3].q), "j"(v));
    return r;
}
extern "C" void func_0020C1C0(Self *self, Req *req, int count, Shape **shapes)
{
    qword a = self->q80;
    qword b = self->q70;
    Owner *owner = req->reg->owner;
    if (owner) {
        VTE *e = &owner->pvt[36];
        M4 m = *((M4 *(*)(void *))e->pfn)((char *)owner + e->d);
        a = Point(m, a);
        b = Point(m, b);
    }
    for (int i = 0; i < count; i++) {
        Shape *shape = shapes[i];
        HIT hits[4];
        int n = func_00164A10(shape, a, b, 4, hits);
        for (int j = 0; j < n; j++) {
            HIT *hit = &hits[j];
            if (hit->parameter[0] == 0.0f)
                continue;
            VTE *e = &self->hooks[7];
            if (((int (*)(void *, Shape *, qword, qword, qword))e->pfn)((char *)self + e->d, shape, hit->point[0].q, hit->plane[0].q, b))
                return;
        }
    }
}
