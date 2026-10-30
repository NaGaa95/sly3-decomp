// EE hardware intrinsics preserve VU/FPU/COP0 operations; C expresses control flow.
typedef int qword __attribute__((mode(TI)));
typedef struct CRef { short m_tagk; short pad; int m_tag; } CRef;
static __inline__ int GDot(qword a, qword b)
{
    qword d, one;
    int g;
    __asm__("vmul.xyz %0, %2, %1\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "1"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
CRef *func_001244C8(CRef *ret, void *pbasic, CRef *aref)
{
    int g = GDot(*(qword *)aref[0].m_tag, *(qword *)aref[1].m_tag);
    ret->m_tagk = 0x14;
    *(volatile int *)&ret->m_tag = g;
    return ret;
}
