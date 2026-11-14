// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// SLY3_ASFIX: engine-divfix1
// Sly 2 func_001229B8 port with Sly 3 CRef; the vdiv tail is one inline (DivQ) so both normalize paths share an asm source line and cross-jump.
typedef int qword __attribute__((mode(TI)));
struct CRef {
    short m_tagk; short m_cref; union { int n; float g; void *pv; qword *pq; } u;
    CRef() { m_tagk = -1; }
    CRef(const qword *pq) __asm__("func_0012AF38");
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
};
struct W { char pad[0x4]; qword *pv; };
extern qword D_00317560;
extern "C" CRef func_00124750(void *pbasic, CRef *aref);
static __inline__ qword VLen(qword c)
{
    qword l, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(l), "=&j"(one) : "j"(c));
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(l) : "j"(l));
    return l;
}
static __inline__ qword DivQ(qword c, qword l)
{
    qword rn;
    __asm__("vdiv Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, Q" : "=j"(rn) : "j"(c), "j"(l));
    return rn;
}
static __inline__ void Normalize(qword *pv, qword *pdef)
{
    __asm__("" : "+r"(pdef));
    qword c = *pv;
    qword l = VLen(c);
    float gl;
    __asm__("qmfc2.ni %0, %1" : "=r"(gl) : "j"(l));
    if (gl < 1e-4f) {
        *pv = *pdef;
    } else {
        *pv = DivQ(c, l);
    }
}
static __inline__ void Normalize1(qword *pv, qword *pdef)
{
    qword c;
    __asm__("qmtc2.ni %1, %0" : "=j"(c) : "r"(*pv));
    qword l = VLen(c);
    float gl;
    __asm__("qmfc2.ni %0, %1" : "=r"(gl) : "j"(l));
    if (gl < 1e-4f) {
        *pv = *pdef;
    } else {
        *pv = DivQ(c, l);
    }
}
CRef func_00124750(void *pbasic, CRef *aref) { CRef ref((qword *)aref[0].u.pv); if (aref[1].m_tagk == 0) Normalize1(ref.u.pq, &D_00317560); else Normalize(ref.u.pq, ((W *)aref[1].u.pv)->pv); return ref; }
