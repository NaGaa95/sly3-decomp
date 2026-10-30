// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct MATRIX4 { float mat[4][4]; } __attribute__((aligned(16)));
struct BONE { char pad[0x40]; MATRIX4 mat; };
struct Y { char pad[0xA0]; BONE *pA0; };
struct XX { char pad[4]; void *p4; Y *py; char pad2[0x1C - 0xC]; BONE *p1C; MATRIX4 mat; };
extern "C" {
MATRIX4 func_0011D768(const MATRIX4 &mat);
MATRIX4 func_0011D558(const MATRIX4 &a, const MATRIX4 &b);
qword func_0028B388(Y *py, MATRIX4 mat);
void func_0028BFE8(void *p, Y *py, qword q);
void func_001303E0(XX *x);
}
void func_001303E0(XX *x)
{
    MATRIX4 m;
    if (x->py->pA0)
        m = func_0011D558(func_0011D558(func_0011D768(x->py->pA0->mat), x->p1C->mat), x->mat);
    else
        m = func_0011D558(x->p1C->mat, x->mat);
    func_0028BFE8(x->p4, x->py, func_0028B388(x->py, m));
}
