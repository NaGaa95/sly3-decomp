// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword r[4]; float m[4][4]; } M4;
struct SW { char pad[0x3ED0]; qword q3ED0; };
struct S { char pad[0x2C]; unsigned char b2C; char pad2d[0x34 - 0x2D]; float g34; char pad38[0x104 - 0x38]; float g104;
           char pad108[0x134 - 0x108]; int c; qword *apos; };
extern "C" {
extern SW D_00475480;
qword func_0018E500(SW *psw, qword q, int k, qword v, float g);
void *func_00292034(void *, int, int);
qword *func_002BA818(qword *, qword);
void func_001C8248(S *p, qword q, M4 *pm, float a, float b);
}
union U { qword q; float f[4]; };
struct VU_FLOATC { qword q; VU_FLOATC(float f) { __asm__("mfc1 %0, %1" : "=rj"(q) : "f"(f)); } };
static inline float GetX(qword v) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(v)); return f; }
static inline float GetY(qword v) { float f; __asm__("prot3w %0,%1" : "=r"(f) : "r"(v)); return f; }
static inline float GetZ(qword v) { float f; __asm__("pextuw %0,$0,%1" : "=r"(f) : "r"(v)); return f; }
struct VU_VECTOR {
    qword q;
    VU_VECTOR(float x, float y, float z, float w)
    {
        qword t, s;
        __asm__("mfc1 %0,%3\n\tmfc1 %1,%4\n\tpextlw %0,%1,%0\n\tmfc1 %1,%5\n\tmfc1 %2,%6\n\tpextlw %1,%2,%1\n\tpcpyld %0,%1,%0"
                : "=&r"(q), "=&r"(t), "=&r"(s) : "f"(x), "f"(y), "f"(z), "f"(w));
    }
};
static inline int FZero(qword v)
{
    int f;
    __asm__("vadd.xyzw $vf0, %1, %1\n\tvnop\n\tvnop\n\tvnop\n\tvnop\n\tcfc2.ni %0, $vi17" : "=r"(f) : "j"(v));
    return ((f & 0xF) ^ 0xF) == 0;
}
static inline void Identity(M4 *pm)
{
    func_00292034(pm, 0, 0x40);
    pm->m[3][3] = 1.0f;
    pm->m[2][2] = 1.0f;
    pm->m[1][1] = 1.0f;
    pm->m[0][0] = 1.0f;
}
static inline void SetPos(M4 *pm, qword pos)
{
    func_002BA818(&pm->r[3], pos);
    pm->m[3][3] = 1.0f;
}
extern "C" void func_002797F0(S *p)
{
    for (int i = 0; i < p->c; i++) {
        U w;
        qword v = VU_VECTOR(GetX(p->apos[i]), GetY(p->apos[i]), GetZ(p->apos[i]), GetX(VU_FLOATC(50.0f).q)).q;
        w.q = func_0018E500(&D_00475480, D_00475480.q3ED0, p->b2C, v, p->g34);
        if (FZero(w.q))
            continue;
        M4 m;
        Identity(&m);
        SetPos(&m, p->apos[i]);
        func_001C8248(p, D_00475480.q3ED0, &m, p->g104, p->g104);
    }
}
