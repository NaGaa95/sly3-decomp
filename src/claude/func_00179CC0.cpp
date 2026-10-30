// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Port of Sly 2 src/hand/func_0015BFD8.cpp (same body, Sly 3 addresses).
typedef int qword __attribute__((mode(TI)));
struct MATRIX4 { qword r[4]; };
struct MATRIX3 { qword r[3]; };
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("" : "=r"(q) : "0"(*(int *)&f)); } };
struct CLOCK { float t; float dt; };
extern "C" CLOCK D_0036BB98;
extern "C" MATRIX4 D_003174C0;
struct X { float x, y, z, w; qword axis; float gRot; float gScale; };
extern "C" void func_0011C8C0(MATRIX3 *pm, float g, qword axis);
MATRIX4 operator*(const MATRIX4 &a, const MATRIX4 &b) __asm__("func_0011D558");
MATRIX4 operator*(const MATRIX4 &m, VU_FLOAT s) __asm__("func_0011D518");
static inline qword Add(qword a, qword b) { qword d; __asm__("vadd.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline MATRIX4 operator+(const MATRIX4 &a, const MATRIX4 &b) return r
{
    for (int i = 0; i < 4; i++)
        r.r[i] = Add(a.r[i], b.r[i]);
}
extern "C" MATRIX4 func_00179CC0(X *p);
MATRIX4 func_00179CC0(X *p)
{
    MATRIX4 mScale = D_003174C0;
    float *pf = (float *)&mScale;
    pf[0] = p->gScale;
    pf[5] = p->gScale;
    pf[10] = p->gScale;
    pf[12] = p->x;
    pf[13] = p->y;
    pf[14] = p->z;
    MATRIX4 mRot = D_003174C0;
    if (p->gRot != 0.0f) {
        MATRIX3 m3;
        MATRIX4 *pmRot = &mRot;
        func_0011C8C0(&m3, p->gRot * D_0036BB98.dt, p->axis);
        *(MATRIX3 *)pmRot = m3;
    }
    MATRIX4 mD = mRot * mScale * VU_FLOAT(D_0036BB98.dt);
    return mRot + mD;
}
