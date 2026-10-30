// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from the Sly 2 decomp (func_0018BCE0).
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct VTE { short delta; short pad; void *pfn; };
#define VCALL(o, i, T) ((T)(o)->pvt[i].pfn)((char *)(o) + (o)->pvt[i].delta
struct LO { unsigned char pad0[0xC]; struct VTE *pvt; };
struct X1974 { unsigned char pad0[0xC]; struct VTE *pvt; unsigned char pad10[0x148 - 0x10]; int x148; };
struct BITS { unsigned char pad0[0x28]; unsigned long :56; unsigned long f : 8; };
#define F(T, o) (*(T *)((char *)p + (o)))
#define A(o) ((char *)p + (o))

void func_00152A48(void *p);
void func_001AD1D0(void *p);
void func_0024E878(void *p, float g);
void func_00258CF0(void *p, float g);
void func_00258DA0(void *p);
void func_001C1550(void *p, void *a, void *animation);
void func_001B2430(void *p);
int func_00173428(void *p);
void *func_00173408(void *p);
void func_001AFBE8(void *p);
void func_001AB308(void *pjt, void *paloExtrem, float sRadius, void *paloHip, void *pact5, void *pxmg);
int func_001AB560(void *p, void *pm, void *px);
void func_001B0070(void *p);
void func_00208378(void *p);
int func_0013B500(void *p, int n);
void func_0022EEA0(void *p, qword q, void *metric, qword *point, qword *direction, float *normalized, float *distance, float g);
void func_001ADDD0(void *p, int a, int b);
void func_00120398(qword a, qword b, qword c, qword d, float *parameters, float *distance, qword *direction);
void func_001AACD8(void *p);

static __inline__ qword VMulX(qword a, qword s) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s)); return r; }
static __inline__ qword VuFloat(float g) { qword r; __asm__("qmtc2 %1, %0" : "=j"(r) : "r"(g)); return r; }

void func_001AD7F0(char *p)
{
    VU u;
    qword av[3];
    VU w;
    float ag[4];
    int i;
    struct X1974 *po;

    func_00152A48(p);
    if (!(((struct BITS *)p)->f & 1))
        return;
    if (F(void *, 0x134))
        func_001AD1D0(p);
    switch (F(int, 0x19E0)) {
    case 2: {
        qword s;
        func_0024E878(p, F(float, 0x110C));
        func_00258CF0(A(0x1470), 1.0f);
        func_00258DA0(A(0x1470));
        s = VuFloat(1.3f);
        u.q = s;
        F(qword, 0x1A0) = VMulX(F(qword, 0x1A0), s);
        break;
    }
    case 6:
        if (F(int, 0x19E8) == 5) {
            qword s;
            func_001C1550(p, A(0x1520), F(void *, 0x1620));
            s = VuFloat(0.85f);
            u.q = s;
            F(qword, 0x1A0) = VMulX(F(qword, 0x1A0), s);
            F(float, 0x190) = 1.0f;
        }
        break;
    case 10:
        func_001C1550(p, A(0x1B20), F(void *, 0x1C20));
        break;
    case 0:
        VCALL((struct LO *)p, 0x6E, void (*)(void *)));
        break;
    case 4:
        func_001B2430(p);
        break;
    case 1: {
        void *pv = 0;
        int fOk = F(void *, 0x1108) && func_00173428(F(void *, 0x1108));
        if (fOk)
            pv = func_00173408(F(void *, 0x1108));
        func_00258DA0(pv ? pv : A(0x1C90));
        break;
    }
    case 17:
        func_001AFBE8(p);
        break;
    case 19:
        if (F(void *, 0x1AF8)) {
            func_001AB308(p, F(void *, 0x1AE0), 20.0f, F(void *, 0x1AE8), F(void *, 0x1AF8), A(0x1650));
            func_001AB308(p, F(void *, 0x1ADC), 20.0f, F(void *, 0x1AE4), F(void *, 0x1AFC), A(0x1750));
            (void)func_001AB560(p, A(0x1650), F(void *, 0x1AF8));
            (void)func_001AB560(p, A(0x1750), F(void *, 0x1AFC));
        }
        break;
    case 24:
        func_001B0070(p);
        break;
    }
    func_00208378(A(0x18F0));
    if (F(int, 0x1994) == 0) {
        if (func_0013B500(F(void *, 0x1974), 0xA)) {
            void *po2 = F(void *, 0x1974);
            for (i = 0; i < F(int, 0x19A4); i++)
                func_0022EEA0(po2, ((qword *)A(0x19B0))[i], 0, &av[i], 0, 0, 0, F(float, 0x1978));
            goto loop;
        L16:
            func_001ADDD0(p, 0x11, -1);
            goto end;
        } else {
            qword q;
            if (!func_0013B500(F(void *, 0x1974), 0x26))
                goto end;
            q = *(qword *)((char *)VCALL(F(struct LO *, 0x1974), 0x24, void *(*)(void *))) + 0x30);
            av[2] = q;
            av[1] = q;
            av[0] = q;
        }
    loop:
        i = 1;
        if (i < F(int, 0x19A4)) {
            qword *pav = av;
            qword *paq = (qword *)A(0x19C0);
            do {
                func_00120398(paq[-1], paq[0], pav[0], pav[1], u.f, ag, &w.q);
                if (ag[0] < F(float, 0x1AAC)) {
                    if (func_0013B500(F(void *, 0x1974), 0x26)) {
                        po = F(struct X1974 *, 0x1974);
                        F(struct X1974 *, 0x19F4) = po;
                        if (po->x148 == 3)
                            goto L16;
                        func_001ADDD0(p, 4, 1);
                    } else {
                        F(void *, 0x101C) = F(void *, 0x1974);
                        F(float, 0x1020) = F(float, 0x1978);
                        func_001ADDD0(p, 9, -1);
                    }
                    break;
                }
                i++;
                pav++;
                paq++;
            } while (i < F(int, 0x19A4));
        }
    }
end:
    func_001AACD8(p);
}
