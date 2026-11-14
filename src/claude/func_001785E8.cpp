// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001785E8: EMITB choose emit position/direction.
// Notes: the unused case-1 VU_VECTOR[3] frees the stack slot that case 3's an[] reuses; VLen = one length-squared asm
// plus a separate vsqrt asm; Normalize returns its VU_VECTOR by value (gives dir its stack slot).
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VU_VECTOR { qword q; };
static inline VU_VECTOR V(qword q) { VU_VECTOR v; v.q = q; return v; }
struct MATRIX3 { qword r[3]; };
extern qword D_00317530;
struct TRI { int aipos[3]; float sArea; };
struct EMITMESH { int cpos; qword *apos; int ctri; TRI *atri; qword *anormal; float sArea; };
struct BOXE { float xMin, yMin, zMin, pad; float xMax, yMax, zMax; };
struct MESHO { char pad[0xD8]; int cs; int padEC; float *as; };
struct LO;
struct LOV { char pad[0x120]; short d; short p; MATRIX3 *(*pfnMat)(LO *); };
struct LO { int a[3]; LOV *pvt; };
static inline MATRIX3 *VMat(LO *plo) { return plo->pvt->pfnMat((LO *)((char *)plo + plo->pvt->d)); }
struct EMITO { LO *palo; MESHO *pmesh; };
struct LM { float gMin, gMax; };
struct EP {
    int kind;
    int kindDir;
    int pad18[3];
    LM lm;
    int pad2C;
    void *pv30;
    int pad34[3];
    qword v40;
};
struct EMITB {
    int pad0, pad4;
    EMITO *pemito;
    int padC;
    struct EP ep;
};
extern "C" {
float func_0011E940(float gMin, float gMax);
void func_0022E330(MESHO *pmesh, float g, qword *ppos, qword *pnormal);
LO *func_00165B28(void *p);
extern char D_00475480[];
}
static inline qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword Add(qword a, qword b) { qword d; __asm__("vadd.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword Cross(qword a, qword b)
{
    qword d;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(d) : "j"(a), "j"(b));
    return d;
}
static inline qword Combo3(VU_FLOAT f0, VU_VECTOR v0, VU_FLOAT f1, VU_VECTOR v1, VU_FLOAT f2, VU_VECTOR v2)
{
    qword d;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddax.xyzw $ACC, %4, %3x\n\tvmaddx.xyzw %0, %6, %5x"
            : "=j"(d) : "j"(f0.q), "j"(v0.q), "j"(f1.q), "j"(v1.q), "j"(f2.q), "j"(v2.q));
    return d;
}
static inline qword MulMat(const MATRIX3 &m, qword v)
{
    qword d;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(d) : "j"(v), "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    return d;
}
static inline qword MulTMat(const MATRIX3 &m, qword v)
{
    qword d, one, t0, t1, t2;
    __asm__ __volatile__("vmul.xyzw %2, %5, %8\n\tvmaxw.xyzw %1, $vf0, $vf0w\n\tvmul.xyzw %3, %6, %8\n\tvmul.xyzw %4, %7, %8\n\t"
            "vadday.x $ACC, %2, %2y\n\tvmaddz.x %0, %1, %2z\n\tvaddax.y $ACC, %3, %3x\n\tvmaddz.y %0, %1, %3z\n\tvaddax.z $ACC, %4, %4x\n\tvmaddy.z %0, %1, %4y"
            : "=j"(d), "=&j"(one), "=&j"(t0), "=&j"(t1), "=&j"(t2) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(v));
    return d;
}
static __inline__ qword VLen(qword c)
{
    qword l, one;
    __asm__("vmul.xyz %1, %2, %2\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddz.x %1, %0, %1z" : "=j"(one), "=&j"(l) : "j"(c) : "memory");
    {
    qword r;
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "j"(l));
    return r;
    }
}
static inline qword Scale(VU_FLOAT f, VU_VECTOR v) { qword r; __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(f.q), "j"(v.q)); return r; }

static inline VU_VECTOR Normalize(qword d)
{
    VU_VECTOR dir;
    qword l = VLen(d);
    qword k = D_00317530;
    float gl;
    __asm__("qmfc2.ni %0, %1" : "=r"(gl) : "j"(l));
    __asm__("" : "+f"(gl)); // empty asm (no instruction): keeps the length in an FPR before the compare
    if (gl < 1e-4f) {
        dir.q = k;
    } else {
        qword dq;
        __asm__ __volatile__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(dq) : "j"(d), "j"(l));
        dir.q = dq;
    }
    return dir;
}
extern "C" void func_001785E8(EMITB *p, int i, int c, qword *ppos, qword *pv)
{
    EP *pep = &p->ep;
    {
    VU_VECTOR av[3];
    switch (p->ep.kind) {
    case 0:
        *ppos = *(qword *)&pep->pv30;
        break;
    case 1: {
        { VU_VECTOR avUnused[3]; } // unused 48-byte local: frees the slot an[] reuses in case 3
        BOXE *pbox = (BOXE *)pep->pv30;
        float *pf = (float *)ppos;
        pf[0] = func_0011E940(pbox->xMin, pbox->xMax);
        pf[1] = func_0011E940(pbox->yMin, pbox->yMax);
        pf[2] = func_0011E940(pbox->zMin, pbox->zMax);
        break;
    }
    case 2: {
        MESHO *pmesh = p->pemito->pmesh;
        if (!pmesh) {
            float *pf = (float *)ppos;
            pf[2] = 0.0f;
            pf[1] = 0.0f;
            pf[0] = 0.0f;
            return;
        }
        float ds = pmesh->as[pmesh->cs - 1] / (float)c;
        float s = (float)i * ds;
        float g = func_0011E940(s, s + ds);
        switch (pep->kindDir) {
        default:
            func_0022E330(pmesh, g, ppos, 0);
            break;
        case 2:
            func_0022E330(pmesh, g, ppos, pv);
            goto normalize;
        case 3: {
            func_0022E330(pmesh, g, ppos, &av[0].q);
            *pv = Cross(av[0].q, p->ep.v40);
            goto normalize;
        }
        }
        break;
    }
    case 3: {
        EMITMESH *pem = (EMITMESH *)pep->pv30;
        float s = func_0011E940(0.0f, 1.0f) * pem->sArea;
        TRI *ptri;
        int itri;
        for (itri = 0; itri < pem->ctri; itri++) {
            ptri = &pem->atri[itri];
            s -= ptri->sArea;
            if (s <= 0.0f)
                break;
        }
        av[0].q = pem->apos[ptri->aipos[0]];
        av[1].q = pem->apos[ptri->aipos[1]];
        av[2].q = pem->apos[ptri->aipos[2]];
        float u = func_0011E940(0.0f, 1.0f);
        float v = func_0011E940(0.0f, 1.0f - u);
        float w = 1.0f - u - v;
        *ppos = Combo3(u, av[0], v, av[1], w, av[2]);
        if (pep->kindDir == 5) {
            VU_VECTOR an[3];
            an[0].q = pem->anormal[ptri->aipos[0]];
            an[1].q = pem->anormal[ptri->aipos[1]];
            an[2].q = pem->anormal[ptri->aipos[2]];
            *pv = Combo3(u, an[0], v, an[1], w, an[2]);
            goto normalize;
        }
        break;
    }
    }

    switch (pep->kindDir) {
    case 0:
        *pv = pep->v40;
        break;
    case 1:
        *pv = Sub(*ppos, pep->v40);
        break;
    case 4: {
        LO *pcm = func_00165B28(D_00475480);
        LO *palo = p->pemito->palo;
        if (palo) {
            MATRIX3 *pm = VMat(palo);
            *pv = MulTMat(*pm, MulMat(*VMat(pcm), pep->v40));
        } else {
            *pv = MulMat(*VMat(pcm), pep->v40);
        }
        break;
    }
    default:
        *pv = D_00317530;
        break;
    }
    }

normalize:

    {
        VU_VECTOR dir = Normalize(*pv);
        *pv = dir.q;
        qword pos = *ppos;
        *ppos = Add(pos, Scale(VU_FLOAT(func_0011E940(pep->lm.gMin, pep->lm.gMax)), dir));
    }
}
