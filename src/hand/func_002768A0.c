// EE hardware intrinsics preserve VU/FPU/COP0 operations; C expresses control flow.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct N { int a[4]; qword plane; };
void func_002BA000(void *p);
float func_002768A0(void *p, qword pos, void *b, struct N *n)
{
    U d, one;
    qword plane;
    float dist;
    plane = n->plane;
    func_002BA000(&d);
    func_002BA000(&one);
    __asm__("vmul.xyz %1, %2, %3\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddaz.x $ACC, %0, %1z\n\tvmsubw.x %1, %0, %2w"
            : "=&j"(one.q), "=&j"(d.q) : "j"(plane), "j"(pos));
    __asm__("qmfc2.ni %0, %1" : "=r"(dist) : "j"(d.q));
    return dist;
}
