// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Build the transform from the two basis vectors of a record (third axis = their cross product), store its inverse
// in the object (+0x60) after the common record init (func_00236FE0).
#include "../P2/mat.h"
typedef int qword __attribute__((mode(TI)));
struct Basis { char prefix[0xC]; float a[3]; float b[3]; };
struct BasisBody { char prefix[0x60]; MATRIX3 inverse; };
extern "C" void func_00236FE0(BasisBody *, const Basis *);
extern "C" void func_0011C6F8(MATRIX3 *, MATRIX3 *);
static inline qword Cross3(qword first, qword second)
{
    qword result;
    __asm__("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1" : "=j"(result) : "j"(first), "j"(second));
    return result;
}
extern "C" void func_00237F10(BasisBody *body, const Basis *basis)
{
    MATRIX3 matrix;
    MATRIX3 inverse;
    func_00236FE0(body, basis);
    matrix.mat[0][0] = basis->a[0];
    matrix.mat[0][1] = basis->a[1];
    matrix.mat[0][2] = basis->a[2];
    matrix.mat[1][0] = basis->b[0];
    matrix.mat[1][1] = basis->b[1];
    matrix.mat[1][2] = basis->b[2];
    *(qword *)matrix.mat[2] = Cross3(*(qword *)matrix.mat[0], *(qword *)matrix.mat[1]);
    func_0011C6F8(&inverse, &matrix);
    body->inverse = inverse;
}
