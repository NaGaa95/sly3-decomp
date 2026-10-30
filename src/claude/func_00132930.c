// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Q4 { char pad[0x260]; qword a; qword b; };
struct R { char pad[0x48]; struct { char pad[0xA0]; void *pA0; } *p48; };
struct E { char pad[0x20]; qword v; };
struct P { char pad[0x10]; struct R *px; char pad1[0x40 - 0x14]; struct { int x0; void *p4; } *p40;
    char pad2[0xB0 - 0x44]; qword vB0; char pad3[0xD0 - 0xC0]; int state; char pad4[0xE8 - 0xD4]; struct E *pE8;
    char pad5[0x110 - 0xEC]; qword v110; int x120; };
qword func_00259208(void *p, qword v);
qword func_0028E910(int n, void *p, qword v);
void func_0028B1B0(struct R *pr, void *p);
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float Dist(qword a, qword b)
{
    qword d, one, l;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "0"(d));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(l));
    return g;
}
void func_00132930(struct P *p, qword pos)
{
    struct Q4 *pq = (struct Q4 *)p->px;
    qword v = Add(Sub(pos, pq->a), pq->b);
    if (p->x120 && p->p40 && p->p40->p4) {
        qword base = p->v110;
        v = Add(base, func_00259208(p->p40->p4, Sub(v, base)));
    }
    switch (p->state) {
    case 1:
    case 2:
        if (p->pE8) {
            qword r = func_0028E910(0, p->px->p48->pA0, v);
            if (1.0f < Dist(r, p->pE8->v)) {
                p->pE8->v = r;
                func_0028B1B0(p->px, p->px->p48);
            }
        }
        break;
    default:
        p->vB0 = v;
        break;
    }
}
