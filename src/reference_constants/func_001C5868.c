// Complete original function, inputs and emitted data independently reviewed.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
typedef struct {
    float x, y, z;
}
V3;
typedef struct {
    V3 xyz;
    unsigned char nonsemantic_padding[4];
}
__attribute__((aligned(16))) VectorCarrier;
typedef char CheckVectorCarrier[(sizeof(VectorCarrier) == 16) ? 1 : -1];
typedef struct {
    qword basis[3];
    qword position;
}
M4;
struct S;
typedef struct {
    short d;
    short pad;
    M4 *(*pfn)(void *);
}
VTE;
struct S {
    int x0, x4, x8;
    VTE *vt;
    char pad10[0xD0 - 0x10];
    int xD0;
    char padD4[0xE0 - 0xD4];
    char xE0[8];
    float xE8;
    int xEC;
    union {
        qword q;
        struct {
            float x, y, z, w;
        }
        f;
    }
    xF0;
    float x100, x104;
    int pad118[2];
    int x110;
    float x114, x118, x11C;
    float x120, x124, x128, x12C;
    V3 x130;
    float x13C, x140, x144;
    int pad158[3];
    float x154, x158;
};
void func_001C57A8(float a, float b, float c, float d, float *pa, float *pb);
void func_0011F6E8(void *p, V3 *pv);
void func_002369D8(VectorCarrier *pv);
void FitLinearFunction__FffffPfT4(float a, float b, float c, float d, float *pa, float *pb);
void func_001C5A40(struct S *p);
static inline float Max1(float a, float b) {
    return (a > b) ? a : b;
}
void func_001C5868(struct S *p) {
    VectorCarrier v;
    float g;
    float a;
    g = Max1(p->x140, p->xE8);
    a = (p->x144 > 30.0f) ? p->x144 : 30.0f;
    func_001C57A8(a, 0.0f, 0.0f, g, &p->x114, &p->x118);
    func_0011F6E8(p->xE0, &v.xyz);
    func_002369D8(&v);
    p->x120 = v.xyz.x;
    p->x124 = v.xyz.y;
    p->x128 = v.xyz.z;
    p->x12C = p->x140;
    if (0.0f < g) {
        p->x120 = p->x120 / g;
        p->x124 = p->x124 / g;
        p->x128 = p->x128 / g;
        p->x12C = p->x12C / g;
    }
    p->x118 = -p->x118;
    switch (p->x110 = p->xD0) {
        case 0: {
            struct F4 {
                float x, y, z, w;
            }
            *pv = (struct F4 *)&p->xF0;
            pv->z = 0.0f;
            pv->y = 0.0f;
            pv->x = 0.0f;
        }
        p->x100 = 1.0f;
        p->x104 = 0.0f;
        p->x130 = *(V3 *)p->vt[36].pfn((char *)p + p->vt[36].d);
        break;
        case 1: p->xF0.q = p->vt[36].pfn((char *)p + p->vt[36].d)->position;
        p->x130 = *(V3 *)&p->xF0;
        FitLinearFunction__FffffPfT4(p->x154, 1.0f, p->x158, 0.0f, &p->x11C, &p->x13C);
        p->x100 = p->x11C;
        p->x104 = p->x13C;
        break;
    }
    g = Max1(p->xE8, p->x140);
    p->x100 = p->x100 * g;
    p->x104 = p->x104 * g;
    func_001C5A40(p);
}
