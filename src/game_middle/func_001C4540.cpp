// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int i[4]; } U;
struct M3 { qword r[3]; };
struct VE { short d; short pad; void *pfn; };
struct X { char pad[0x80]; U v80; };
struct SMP { float a, b, c, d; };
struct P {
    char pad[0xC]; struct VE *vt;
    char pad1[0xD8 - 0x10]; struct X *xD8;
    char pad2[0x1A0 - 0xDC]; qword v1A0;
    char pad3[0x1C0 - 0x1B0]; struct M3 m1C0;
    char pad4[0x33C - 0x1F0]; int state33C;
    char pad5[0xE44 - 0x340]; int stateE44;
    char pad6[0x1178 - 0xE48]; float height1178, alpha117C;
    struct SMP smp1180;
};
struct CLOCK { float t, dt; };
extern "C" {
extern struct CLOCK g_clock;
int func_001C4408(struct P *p, void *o, qword *pos);
void func_00280598(void *o, qword pos, qword *dir, qword *v);
void func_002812B0(struct P *p, void *o);
float func_0011E730(float pos, float vel, float target, float dt, struct SMP *s, float *result);
void func_00244828(struct P *p, qword v);
}
/* "rV": a single-use load feeding this asm is moved into it by local-alloc, so reload emits the lw right before the qmtc2. */
struct VU_FLOAT { qword q; VU_FLOAT(float g) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "rV"(g)); } };
static inline qword GetVel(struct P *p) { return ((qword (*)(void *))p->vt[38].pfn)((char *)p + p->vt[38].d); }
static inline qword GetPosition(struct P *p) { return *(qword *)(((unsigned char *(*)(void *))p->vt[36].pfn)((char *)p + p->vt[36].d) + 0x30); }
static inline qword Mul(struct M3 *m, const qword *v) { qword r; __asm__("vmulax.xyz ACC,%2,%1x\n\tvmadday.xyz ACC,%3,%1y\n\tvmaddz.xyz %0,%4,%1z" : "=j"(r) : "j"(*v), "j"(m->r[0]), "j"(m->r[1]), "j"(m->r[2])); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Scale(qword v, VU_FLOAT k) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v), "j"(k.q)); return r; }
extern "C" void func_001C4540(struct P *p, void *o)
{
    U origin, vel, pos, local, dir, v50, accel;
    float z, g;
    qword v;
    struct CLOCK *clock;
    if (p->state33C == 7) goto vertical;
    switch (p->stateE44) {
    case 8:
    vertical:
        origin.q = GetVel(p);
        if (origin.f[2] < 0.0f) func_002812B0(p, o);
        break;
    case 3: case 11: {
        if (!func_001C4408(p, o, &pos.q)) break;
        local.q = Mul(&p->m1C0, &p->v1A0);
        func_00280598(o, pos.q, &dir.q, &v50.q);
        v = GetVel(p);
        vel.q = v;
        v = Add(v, local.q);
        v = Sub(v, dir.q);
        accel.q = Scale(v, VU_FLOAT(p->alpha117C));
        origin.q = GetPosition(p);
        clock = &g_clock;
        func_0011E730(origin.f[2] + p->height1178, vel.f[2] - dir.f[2], pos.f[2], clock->dt, &p->smp1180, &z);
        g = (z - vel.f[2]) / clock->dt - p->xD8->v80.f[2];
        accel.f[2] = accel.f[2] > g ? accel.f[2] : g;
        func_00244828(p, accel.q);
        break;
    }
    default:
        func_002812B0(p, o);
        break;
    }
}
