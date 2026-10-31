// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// New code: per-entry lighting/visibility update (func_0018E500 weights, VU MAC-flag zero test, distance falloff).
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct VTE { short d; short pad; unsigned char *(*fn)(void *); };
struct OBJ { int pad[3]; struct VTE *vt; };
struct E { float f0; int pad[3]; qword v10; qword pad20; qword pad30; qword v40; };
extern "C" {
struct S {
    char pad0[0x2C]; unsigned char b2C; char pad2D[0x34 - 0x2D]; float f34;
    char pad38[0x48 - 0x38]; void *p48; void *p4C; float f50; int pad54[2]; struct OBJ *p5C; float f60;
    int pad64[3]; float f70; int pad74[2]; struct E *a7C; int n80; int n84;
};
extern struct { char pad[0x3ED0]; qword q; } D_00475480;
void func_001C8238(struct S *s);
void func_001C8248(void *p, qword w, qword *pv, float a, float b);
qword func_0018E500(void *self, qword weights, int mask, float f, qword dir);
}
static inline qword Position(struct OBJ *o)
{
    struct VTE *e = &o->vt[36];
    return *(qword *)(e->fn((char *)o + e->d) + 0x30);
}
static inline float GetX(qword q) { float x; __asm__("mtc1 %1, %0" : "=f"(x) : "r"(q)); return x; }
static inline float GetY(qword q) { float y; __asm__("prot3w %0, %1" : "=r"(y) : "r"(q)); return y; }
static inline float GetZ(qword q) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q)); return z; }
struct VU_FLOAT { qword q; VU_FLOAT(const float &f) { __asm__("lw %0, %1" : "=rj"(q) : "m"(f)); } };
static inline qword Pack(float x, float y, float z, float w)
{
    U u; qword q, t, s;
    __asm__("mfc1 %0,%3\n\tmfc1 %1,%4\n\tpextlw %0,%1,%0\n\tmfc1 %1,%5\n\tmfc1 %2,%6\n\tpextlw %1,%2,%1\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t), "=&r"(s) : "f"(x), "f"(y), "f"(z), "f"(w));
    u.q = q;
    return u.q;
}
static inline float GMax(float a, float b) { return a > b ? a : b; }
static inline int IsZero(qword v)
{
    int mac;
    __asm__("vadd.xyzw $vf0, %1, %1\n\tvnop\n\tvnop\n\tvnop\n\tvnop\n\tcfc2.ni %0, $vi17" : "=r"(mac) : "j"(v));
    return (mac & 0xF) == 0xF;
}
static inline float Length(qword a, qword b)
{
    qword d, one;
    float f;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(d), "=&j"(one));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
    return f;
}
extern "C" void func_00184350(struct S *s)
{
    U w;
    qword pos;
    float near, range;
    int i;
    func_001C8238(s);
    pos = Position(s->p5C);
    near = s->f60 * 0.7f;
    range = s->f60 - near;
    for (i = s->n80; i <= s->n84; i++) {
        struct E *e = &s->a7C[i];
        qword dir = Pack(GetX(e->v40), GetY(e->v40), GetZ(e->v40), GetX(VU_FLOAT(s->f50).q));
        w.q = func_0018E500(&D_00475480, D_00475480.q, s->b2C, s->f34, dir);
        if (!IsZero(w.q)) {
            void *p = e->f0 < s->f70 ? s->p4C : s->p48;
            float d = Length(pos, e->v40);
            float g;
            if (d < near)
                g = 1.0f;
            else {
                float t = d - near;
                g = 1.0f - t / GMax(range, t);
            }
            func_001C8248(p, w.q, &e->v10, g, g);
        }
    }
}
