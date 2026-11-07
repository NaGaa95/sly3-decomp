// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// func_00289D68: per-entry phase update (sin/cos of angle along a cached direction) then sum of transformed points.
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VECTOR { union { qword q; float f[4]; }; VECTOR(const VECTOR &v) __asm__("func_002BC400"); };
union U { qword q; float f[4]; };
struct ENT { VECTOR pos; qword a10[1]; };
struct E { int k; int x4; int x8; int xC; char pad10[0x10]; qword q20; char pad30[0x40]; float g70; char pad74[0xC]; };
struct VTE { short d; short pad; void (*pfn)(void *, int); };
struct P { char pad[0xC]; VTE *vt; char pad10[0x44 - 0x10]; int n44; int n48; int x4C; char pad50[0x10]; E ae[1]; char padE0[0x470 - 0xE0]; M4 am[1]; };
extern "C" {
qword func_0011D598(const M4 *m, qword v);
float func_0011E3B8(float g);
void func_0011EB28(float g, float *ps, float *pc);
qword func_00289D68(P *p, ENT *pe);
}
static inline qword Normalize(qword v)
{
    qword r, one, l;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(l), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(l));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
static inline float Dot(qword a, qword b)
{
    qword r, one;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(r), "=&j"(one) : "j"(a), "j"(b));
    int t;
    __asm__("qmfc2.ni %1, %2\n\tmtc1 %1, %0" : "=f"(g), "=&r"(t) : "j"(r));
    return g;
}
static inline qword Zero() { qword r; __asm__("vsub.xyzw %0, $vf0, $vf0" : "=j"(r)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
qword func_00289D68(P *p, ENT *pe)
{
    int i;
    int j;
    if (*(int *)&pe->pos.f[3] != p->x4C) {
        VECTOR v = pe->pos;
        qword dir = v.q;
        for (i = 0; i < p->n44; i++) {
            E *e = &p->ae[i];
            if (e->k == -1 || e->xC < *(int *)&pe->pos.f[3])
                continue;
            U *pf = (U *)&pe->a10[e->x4];
            switch (e->k) {
            case 0: {
                float s, c;
                float f = e->g70 * 6.2831855f;
                func_0011EB28(func_0011E3B8(Dot(dir, Normalize(e->q20)) * f), &s, &c);
                pf->f[e->x8] = c;
                pf->f[e->x8 + 1] = s;
                break;
            }
            case 1:
                pf->f[e->x8] = 1.0f;
                break;
            }
        }
        *(int *)&pe->pos.f[3] = p->x4C;
    }
    qword sum = Zero();
    j = 0;
    p->vt[53].pfn((char *)p + p->vt[53].d, 0);
    if (j < p->n48) {
        qword *pv = pe->a10;
        M4 *pm = p->am;
        do {
            sum = Add(sum, func_0011D598(pm, *pv));
            pv++;
            pm++;
        } while (++j < p->n48);
    }
    return sum;
}
