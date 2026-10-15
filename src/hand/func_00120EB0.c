// EE hardware intrinsics preserve VU/FPU/COP0 operations; C expresses control flow.
typedef int qword __attribute__((mode(TI)));
extern qword D_00317590;

qword func_00120EB0(int c, qword *p)
{
    qword m = D_00317590;
    int i;
    for (i = 0; i < c; i++) {
        qword v = p[i];
        __asm__("vmax.xyz %0, %1, %2" : "=j"(m) : "j"(v), "0"(m));
    }
    return m;
}
