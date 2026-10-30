// EE hardware intrinsics preserve VU/FPU/COP0 operations; C expresses control flow.
typedef int qword __attribute__((mode(TI)));
typedef struct CRef { short m_tagk; short pad; int m_tag; } CRef;
static __inline__ int GLength(qword v)
{
    qword d, one, l;
    int g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
    return g;
}
CRef *func_00124568(CRef *ret, void *pbasic, CRef *aref)
{
    int g = GLength(*(qword *)aref[0].m_tag);
    ret->m_tagk = 0x14;
    *(volatile int *)&ret->m_tag = g;
    return ret;
}
