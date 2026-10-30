// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef struct { unsigned char r, g, b, a; } RGBA;
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) VECTOR;
typedef union { VECTOR v; qword q; } UV;
struct O { char pad[0x20]; RGBA rgba; };
void func_0011F230(RGBA *prgba, VECTOR *pv);
void func_0011F2E8(VECTOR *pv, VECTOR *phsv);
qword func_00169278(struct O *p)
{
    UV hsv;
    VECTOR v;
    RGBA rgba = p->rgba;
    func_0011F230(&rgba, &v);
    func_0011F2E8(&v, &hsv.v);
    hsv.v.y *= 255.0f;
    hsv.v.z *= 255.0f;
    return hsv.q;
}

