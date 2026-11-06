// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Port of Sly 2 func_00230A98 (src/hand/func_00230A98.c).
typedef int qword __attribute__((mode(TI)));
typedef struct M4 { qword r[4]; } M4;
typedef struct P { char pad[0xA0]; struct P *xA0; } P;
void *func_00292034(void *, int, int);
void func_0028F3A8(P *, M4 *, M4 *, float);
M4 func_0011D558(M4 *, M4 *);

static inline void AddM4(M4 *d, M4 *a, M4 *b)
{
    int i;
    for (i = 0; i < 4; i++) {
        qword r;
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a->r[i]), "j"(b->r[i]));
        d->r[i] = r;
    }
}

void func_0028F730(P *first, P *end, M4 *pA, M4 *pB, float f)
{
    M4 m1, m2, a, b, s, t1, t2;
    P *p;

    if (pB)
        b = *pB;
    else
        func_00292034(&b, 0, 0x40);
    if (pA)
        a = *pA;
    else {
        float *pf = (float *)&a;
        func_00292034(&a, 0, 0x40);
        pf[0] = pf[5] = pf[10] = pf[15] = 1.0f;
    }
    for (p = first; p != end; p = p->xA0) {
        func_0028F3A8(p, &m1, &m2, f);
        t1 = func_0011D558(&m1, &b);
        t2 = func_0011D558(&m2, &a);
        AddM4(&s, &t1, &t2);
        b = s;
        s = func_0011D558(&m1, &a);
        a = s;
    }
    if (pA)
        *pA = a;
    if (pB)
        *pB = b;
}
