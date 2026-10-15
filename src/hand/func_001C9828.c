// Affine packed-point conversion between optional source/destination matrices.
// Each VU operation consumes the real vector and four real matrix columns.
// The tied output replaces XYZ and retains the actual input W word. VF0.w is
// architectural one. ACC.xyz is overwritten before use; ACC.w is untouched.
// No ACC value crosses operations. This compiler exposes no VU ACC clobber;
// scalar accum/accum1 names are not substitutes for the VU accumulator.
// Control flow and both inverse inputs are ordinary C.
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
void func_0011D768(M4 *output, const M4 *input);
qword func_001C9828(M4 *pm, const M4 *destination, qword v)
{
    if (pm) {
        __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddaz.xyz $ACC, %4, %1z\n\tvmaddw.xyz %0, %5, $vf0w"
                : "=j"(v) : "0"(v), "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]), "j"(pm->r[3]));
    }
    if (destination) {
        M4 m;
        func_0011D768(&m,destination);
        __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddaz.xyz $ACC, %4, %1z\n\tvmaddw.xyz %0, %5, $vf0w"
                : "=j"(v) : "0"(v), "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]));
    }
    return v;
}
