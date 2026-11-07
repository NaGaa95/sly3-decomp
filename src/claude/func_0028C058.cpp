// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct MATRIX3 { float mat[3][4]; } __attribute__((aligned(16)));
struct VU_VECTOR4 { qword qw; };
inline MATRIX3 operator-(const MATRIX3 &a, const MATRIX3 &b) return r
{
    for (int i = 0; i < 3; i++) {
        qword q;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(q) : "j"(*(qword *)a.mat[i]), "j"(*(qword *)b.mat[i]));
        *(qword *)r.mat[i] = q;
    }
}
inline MATRIX3 operator*(const MATRIX3 &matL, const MATRIX3 &matR) return mat
{
    qword qwL0 = *(qword *)matL.mat[0];
    qword qwL1 = *(qword *)matL.mat[1];
    qword qwL2 = *(qword *)matL.mat[2];
    VU_VECTOR4 v0;
    VU_VECTOR4 v1;
    VU_VECTOR4 v2;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v0.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)matR.mat[0])->qw));
    *(VU_VECTOR4 *)mat.mat[0] = v0;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v1.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)matR.mat[1])->qw));
    *(VU_VECTOR4 *)mat.mat[1] = v1;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v2.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)matR.mat[2])->qw));
    *(VU_VECTOR4 *)mat.mat[2] = v2;
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VU_VECTOR3 {
    qword q;
    VU_VECTOR3(float x, float y, float z)
    {
        // Pack x,y,z into a GPR qword and move it to VU0. The y/z scratch is a $v0 clobber rather than a
        // second output: each extra asm output re-counts the float inputs in flow, which changes the local FP
        // allocation priorities (s/z register swap). The zero-insn copy keeps the target's sched2 order.
        qword u; qword q0;
        __asm__("mfc1 %1,%2\n\tmfc1 $2,%3\n\tpextlw %1,$2,%1\n\tmfc1 $2,%4\n\tpcpyld %1,$2,%1\n\tqmtc2.ni %1,%0" : "=j"(q0), "=&r"(u) : "f"(x), "f"(y), "f"(z) : "$2");
        __asm__("" : "=j"(q) : "0"(q0));
    }
};
struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));
inline qword operator*(VU_VECTOR3 v, VU_FLOAT f) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v.q), "j"(f.q)); return r; }
struct XF {
    MATRIX3 mat;
    char pad30[0x9A - 0x30];
    short state;
    char pad9C[0xC0 - 0x9C];
    MATRIX3 matPrev;
    VECTOR4 w;
};
struct ALO { char pad[0x128]; unsigned long grf; };
extern "C" MATRIX3 func_0011C6F8(const MATRIX3 *);
extern "C" void func_0028B188(ALO *, XF *);
extern float D_0036BB9C;
extern "C" void func_0028C058(ALO *palo, XF *pxf, MATRIX3 *pmat)
{
    if (pxf->state == 5 && (palo->grf & 0x100)) {
        MATRIX3 d;
        d = *pmat - pxf->matPrev;
        d = d * func_0011C6F8(&pxf->mat);
        float c = d.mat[2][0];
        float t = D_0036BB9C;
        float s = 0.5f / t;
        float b = d.mat[2][1];
        float a = d.mat[1][2];
        float x = a - b;
        // one pin: e in $f5 (target register)
        float e; { register float ep asm("$f5") = d.mat[0][2]; __asm__("" : "=f"(e) : "0"(ep)); }
        float f = d.mat[0][1];
        float g = d.mat[1][0];
        float z = f - g;
        float y = c - e;
        *(qword *)&pxf->w = VU_VECTOR3(x, y, z) * VU_FLOAT(s);
    } else {
        VECTOR4 *pw = &pxf->w;
        pw->z = 0.0f;
        pw->y = 0.0f;
        pw->x = 0.0f;
    }
    pxf->state = 5;
    MATRIX3 *pm = &pxf->matPrev;
    *pm = *pmat;
    func_0028B188(palo, pxf);
}
