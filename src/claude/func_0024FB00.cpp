// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from Sly 2 src/hand/func_002057E8.cpp.
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VE { short d; short pad; void *pf; };
struct XF { qword r[3]; qword pos; };
struct S { char pad[0xC]; VE *vt; char pad10[0x230 - 0x10]; float radius; };
extern "C" {
qword func_00250600(S *p);
extern int D_00327270[2][3];
}
static inline XF *Xf(S *p) { return ((XF *(*)(void *))p->vt[36].pf)((char *)p + p->vt[36].d); }
static inline qword MulX(qword v, VU_FLOAT g) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(g.q)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword LoadVf(qword *p) { qword r; __asm__("lqc2 %0, %1" : "=j"(r) : "m"(*p)); return r; }
extern "C" void func_0024FB00(S *p, qword out[2][3])
{
    qword point[5];
    qword origin = func_00250600(p);
    qword right = Xf(p)->r[0];
    qword forward = LoadVf(&Xf(p)->r[1]);
    point[0] = Xf(p)->pos;
    float radius = p->radius;
    point[1] = Add(origin, MulX(right, VU_FLOAT(radius)));
    point[2] = Add(origin, MulX(forward, VU_FLOAT(radius)));
    point[3] = Add(origin, MulX(right, VU_FLOAT(-radius)));
    point[4] = Add(origin, MulX(forward, VU_FLOAT(-radius)));
    for (unsigned i = 0; i < 2; i++) {
        int *indices = D_00327270[i];
        for (unsigned j = 0; j < 3; j++)
            out[i][j] = *(qword *)((indices[j] << 4) + (unsigned int)point);
    }
}
