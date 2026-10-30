// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
struct Link { unsigned char pad[0x50]; int id; };
struct Self {
    unsigned char pad0[0x50]; int id;
    unsigned char pad54[0x1AA4 - 0x54]; struct Link *link;
    unsigned char pad1AA8[0x1AC8 - 0x1AA8]; int third;
    unsigned char pad1ACC[0x1AD4 - 0x1ACC]; int second;
    unsigned char pad1AD8[0x1C28 - 0x1AD8]; void *anim;
    int pad1C2C; float time; int pad1C34[3];
    qword pos0; qword pos1; qword pos2; qword dir; qword world;
};
float func_001368E0(void *anim, int id);
void func_00137070(void *anim, struct Self *self, float time, float blend, int id, int owner, M4 *out, int flags);
qword func_0011D3C0(M4 *m);
void func_0011D768(M4 *out, M4 *in);
void func_001ACD28(struct Self *self)
{
    M4 a, b, c, m;
    float zero;
    if (!self->anim) return;
    zero = 0.0f;
    self->time = func_001368E0(self->anim, 0x185);
    func_00137070(self->anim, self, self->time, zero, self->link->id, self->id, &a, 0);
    self->pos0 = a.r[3];
    func_00137070(self->anim, self, self->time, zero, self->second, self->id, &b, 0);
    self->pos1 = b.r[3];
    func_00137070(self->anim, self, self->time, zero, self->third, self->id, &c, 0);
    self->pos2 = c.r[3];
    self->dir = func_0011D3C0(&c);
    func_0011D768(&m, &c);
    __asm__("vmulax.xyz $ACC,%1,%2x\n\tvmadday.xyz $ACC,%3,%2y\n\tvmaddaz.xyz $ACC,%4,%2z\n\tvmaddw.xyz %0,%5,$vf0w"
        : "=j"(self->world) : "j"(m.r[0]), "j"(self->pos0), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]));
}
