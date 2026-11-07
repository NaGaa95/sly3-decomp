// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));
struct COLORS { qword q0; VECTOR v; };
struct SO {
    char pad[0x1B0]; int n1B0; char pad1B4[0x21C - 0x1B4]; float f21C; float f220; float f224;
    char pad228[0x250 - 0x228]; union { qword q250; struct { float x, y, z, w; } v250; }; qword q260; char pad270[0x2C0 - 0x270]; void *p2C0;
};
struct CLOCK { float t, dt; };
extern "C" {
extern CLOCK g_clock;
extern char D_00328B50[], D_00328B60[];
extern COLORS D_00317FC0;
int func_001F43C8(void *self);
int func_001F43F0(void *self);
void func_00261528(void *receiver, int identifier, float numerator, float denominator);
int func_0011E9F0(float, float, float);
float func_0011E598(float gCur, float gTarget, float dt, void *psmp, float *pdgNext);
qword func_00120C80(qword posCur, qword posTarget, float dt, void *psmp, VECTOR *pv);
void func_00262990(void *receiver, int identifier, COLORS *pc);
void func_0026D7B0(SO *p, int fForce);
}
inline float PackedVectorX(qword vector) { float scalar; asm("mtc1 %1,%0" : "=f"(scalar) : "r"(vector)); return scalar; }
inline float PackedVectorY(qword vector) { float scalar; asm("prot3w %0,%1" : "=r"(scalar) : "r"(vector)); return scalar; }
inline float PackedVectorZ(qword vector) { float scalar; asm("pextuw %0,$0,%1" : "=r"(scalar) : "r"(vector)); return scalar; }
static inline int PositionNear(qword first, qword second)
{
    return func_0011E9F0(PackedVectorX(first), PackedVectorX(second), 0.0001f) &&
           func_0011E9F0(PackedVectorY(first), PackedVectorY(second), 0.0001f) &&
           func_0011E9F0(PackedVectorZ(first), PackedVectorZ(second), 0.0001f);
}
static inline float GMin(float a, float b) { return a < b ? a : b; }
void func_0026D7B0(SO *p, int fForce)
{
    if (fForce || p->n1B0 != func_001F43C8(p))
        func_00261528(p->p2C0, 0x3CA, (float)p->n1B0, (float)func_001F43F0(p));
    if (fForce || !func_0011E9F0(p->f220, p->f21C, 0.0001f)) {
        p->f220 = func_0011E598(p->f220, p->f21C, g_clock.dt, D_00328B50, 0);
        func_00261528(p->p2C0, 0x3D2, p->f220, p->f224);
    }
    p->f21C = GMin(p->f21C + g_clock.dt * 25.0f, p->f224);
    COLORS c = D_00317FC0;
    if (fForce || !PositionNear(p->q250, p->q260)) {
        p->q250 = func_00120C80(p->q250, p->q260, g_clock.dt, D_00328B60, 0);
        p->v250.z = 4000.0f;
        c.v.x = p->v250.x * 320.0f + 320.0f;
        c.v.y = p->v250.y * -240.0f + 240.0f;
        func_00262990(p->p2C0, 0x3BC, &c);
    }
}
