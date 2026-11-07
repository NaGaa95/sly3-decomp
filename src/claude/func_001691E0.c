// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// A17/A22 drafts; A70: the x lane goes through the A65 lane-store helper (plain sw of the qword arg), z/y order per target.
typedef int qword __attribute__((mode(TI)));
typedef struct { unsigned char r, g, b, a; } RGBA;
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) VECTOR;
struct O;
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static __inline__ void StoreX(float *d, qword q) { __asm__("sw %1, %0" : "=m"(*d) : "r"(q)); } /* lane-store helper (A65) */
void func_0011F4E0(VECTOR *phsv, VECTOR *pv);
void func_0011F288(VECTOR *pv, int a, RGBA *prgba);
void func_001691B0(struct O *p, RGBA *prgba);
void func_001691E0(struct O *p, qword v)
{
    RGBA rgba;
    VECTOR c;
    VECTOR hsv;
    {
        float z = GetZ(v);
        float y = GetY(v);
        StoreX(&hsv.x, v);
        hsv.y = y * (1.0f / 255.0f);
        hsv.z = z * (1.0f / 255.0f);
    }

    func_0011F4E0(&hsv, &c);
    func_0011F288(&c, 0x80, &rgba);
    {
        RGBA t = rgba;
        func_001691B0(p, &t);
    }
}
