// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Cf. Sly 2 src/hand/func_00204108.c (rewritten without pins).
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
typedef struct { float x, y, z; } VECTOR3;
typedef struct { qword row[3]; } M3;
union FLOATWORD { float value; int bits; };
extern struct { float t; union FLOATWORD delta; } g_clock;
struct O { char pad[0xB0]; qword angularVelocity; char pad2[0x30]; qword angularForce; };
struct S { char pad[0x4C]; struct O *po; char pad2[0x1B8 - 0x50]; int k; char pad3[4]; M3 desired; qword v1F0; float f200, f204, f208, f20C, f210; };
extern "C" {
void func_0024E2B8(struct S *p);
void func_00243738(struct S *p);
void func_0023EDE8(struct S *, M3 *, VECTOR3 *);
}
struct VU_FLOAT { qword q; VU_FLOAT(const float &f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(*(const int *)&f)); } };
static inline qword Div(qword v, VU_FLOAT f) { __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %0, $Q" : "+j"(v) : "j"(f.q)); return v; }
static inline qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword Add(qword a, qword b) { qword d; __asm__("vadd.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
void func_0024E2B8(struct S *p)
{
    func_00243738(p);
    switch (p->k) {
    case 0: {
        VECTOR3 v;
        float s = p->f210;
        v.z = p->f20C;
        v.x = p->f204 * s;
        v.y = p->f208 * s;
        func_0023EDE8(p, &p->desired, &v);
        break;
    }
    case 1: {
        struct O *po = p->po;
        po->angularForce = Add(po->angularForce, Div(Sub(p->v1F0, po->angularVelocity), VU_FLOAT(g_clock.delta.value)));
        break;
    }
    case 2:
        break;
    }
}
