// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct VEntry { short delta; short pad; qword *(*call)(void *); };
struct Body {
    unsigned char pad00[0xC];
    VEntry *table;
    unsigned char pad10[0x220 - 0x10];
    float radius;
    unsigned char pad224[0x250 - 0x224];
    void *path;
};
struct Mover {
    unsigned char pad00[0x40];
    Body *body;
};
struct Target {
    unsigned char pad00[0xC];
    VEntry *table;
};
extern "C" {
extern qword D_00325D70[8];
extern float D_00325DF0;
int func_001ED170(void *path, qword position, int flag);
void func_002159D8(Body *body, int mode);
}
static inline qword *Matrix(void *object, VEntry *table)
{
    VEntry *entry = &table[36];
    return entry->call((char *)object + entry->delta);
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
static inline qword MulAdd(const qword &base, const qword &dir, const VU_FLOAT &s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0
	vmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(base), "j"(dir), "j"(s.q));
    return r;
}
static inline qword Distance(qword a, qword b)
{
    qword d;
    __asm__("vsub.xyzw %0, %2, %1\n\tvmul.xy %0, %0, %0\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(a), "j"(b));
    return d;
}
static inline float ToFloat(qword q)
{
    float f;
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q), "j"(q));
    return f;
}
extern "C" void func_0021A570(Mover *self, Target *target)
{
    U origin, best;
    qword cand;
    int found = 0;
    float scale = 2.0f;
    register float radius asm("$f21") = self->body->radius; /* preserve the original radius register across calls */
    origin.q = Matrix(self->body, self->body->table)[3];
    float bestDistance = D_00325DF0;
    void *path = self->body->path;
    for (int pass = 0; pass < 3; pass++) {
        for (unsigned int i = 0; i < 8; i++) {
            qword pos = Matrix(target, target->table)[3];
            cand = MulAdd(pos, D_00325D70[i], VU_FLOAT(scale * radius));
            __asm__ volatile(""); /* scheduling barrier: emits no instructions */
            if (path && !func_001ED170(path, cand, 0))
                continue;
            float d = ToFloat(Distance(origin.q, cand));
            if (bestDistance < d)
                continue;
            bestDistance = d;
            best.q = cand;
            found = 1;
        }
        if (found)
            break;
        scale += scale;
    }
    if (found) {
        VEntry *entry = &self->body->table[34];
        ((void (*)(void *, qword))entry->call)((char *)self->body + entry->delta, best.q);
    }
    func_002159D8(self->body, 6);
}



