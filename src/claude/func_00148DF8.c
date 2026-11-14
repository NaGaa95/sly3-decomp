// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* Sly 2 src/hand/func_00138970.c counterpart (Sly 3 offsets). */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
extern qword D_00317560;
struct VTE { short d; short pad; void *pfn; };
struct O { struct VTE *vt; };
struct SEG { float g0; float g4; };
struct CL { char pad[0x64]; float x64; };
struct E { union { float w; int iw; } u; struct CL *p4; };
struct A { char pad[0x64]; float x64; char pad2[0xB0 - 0x68]; int xB0; int xB4; char *xB8; };
struct B { int x0; void *x4; struct SEG *x8; };
struct P { int pad; struct A *p4; struct B *x8; struct O **xC; qword x10; };
int func_00148810(void *, struct SEG *, float *, float, float);
static __inline__ qword ToVf(int g)
{
    qword s;
    __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(g));
    return s;
}
/* same as Madd; the two extra allocation-only "j"(v) operands raise v's local-alloc priority (VF numbering) */
static __inline__ qword MaddV(qword a, qword v, qword s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(v), "j"(s), "j"(v), "j"(v));
    return r;
}
static __inline__ qword Madd(qword a, qword v, qword s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(v), "j"(s));
    return r;
}

void func_00148DF8(struct P *p, qword *ppos, qword *prot, float t, float rate)
{
    float u;
    int iSeg;
    struct SEG *pseg;
    VU a, b;
    VU v20, v30, w;
    int i;
    if (p->x8 == 0) {
        u = t / p->p4->x64;
    } else {
        float tLocal;
        iSeg = func_00148810(p->x8->x4, p->x8->x8, &tLocal, t, p->p4->x64);
        pseg = &p->x8->x8[iSeg];
        u = tLocal / pseg->g4;
    }
    a.q = D_00317560;
    b.q = a.q;
    for (i = 0; i < p->p4->xB4; i++) {
        struct A *pa = p->p4;
        struct E *pe = (struct E *)(pa->xB8 + i * pa->xB0);
        struct O *po;
        if (pe->u.w == 0.0f)
            continue;
        po = p->xC[i];
        if (!po) {
            v20.q = p->x10;
            v30.f[2] = 0.0f;
            v30.f[1] = 0.0f;
            v30.f[0] = 0.0f;
        } else {
            float g0, g1;
            if (!p->x8) {
                g1 = rate * pe->p4->x64 / pa->x64;
                g0 = u * pe->p4->x64;
            } else {
                struct SEG *ps = (struct SEG *)((char *)pe + p->x8->x0) + iSeg;
                float gMax = pe->p4->x64;
                g0 = ps->g0 + u * ps->g4;
                g1 = rate * ps->g4 / pseg->g4;
                if (gMax < g0)
                    g0 -= gMax;
            }
            {
                struct VTE *e = &po->vt[3];
                ((void (*)(void *, float, float, VU *, VU *))e->pfn)((char *)po + e->d, g0, g1, &v20, &v30);
            }
        }
        {
            qword s1, s2;
            s1 = ToVf(pe->u.iw);
            a.q = Madd(a.q, v20.q, s1);
            {
                register int iw2 __asm__("$17") = pe->u.iw; /* register pin: target reloads pe->w into pe's dying s1 */
                __asm__("qmtc2.ni %1, %0" : "=j"(s2) : "r"(iw2));
            }
            w.q = s1;
            b.q = MaddV(b.q, v30.q, s2);
            w.q = s2;
        }
    }
    if (ppos)
        *ppos = a.q;
    if (prot)
        *prot = b.q;
}
