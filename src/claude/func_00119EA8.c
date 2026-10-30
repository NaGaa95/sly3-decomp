// EE hardware intrinsics preserve VU/FPU/COP0 operations; C expresses control flow.
typedef int qword __attribute__((mode(TI)));
typedef struct PLANE { qword normal; } PLANE;
void func_00119EA8(float *pplane, qword vecNormal, qword vecPos)
{
    qword d, one;
    int dist;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(vecNormal), "j"(vecPos));
    *(qword *)pplane = vecNormal;
    __asm__("qmfc2.ni %0, %1" : "=r"(dist) : "j"(d));
    ((volatile int *)pplane)[3] = dist;
}
