// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// EE hardware intrinsics preserve VU/FPU/COP0 operations; C expresses control flow.
typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; };
extern struct CLOCK g_clock;
struct VEntry { short delta; short pad; void *(*get)(void *); };
struct LO { char pad[0xC]; struct VEntry *table; };
struct W { char pad[0x11B8]; int grf; };
struct S { struct W *pw; char pad[0x14 - 4]; int state; float tState; char pad2[0x44 - 0x1C]; struct LO *plo; char pad3[0x80 - 0x48]; qword v80; char pad4[0xB0 - 0x90]; float dist; };
static __inline__ qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static __inline__ qword Len(qword v)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(d) : "j"(d));
    return d;
}
void func_0017EAD0(struct S *p, int state)
{
    if (state == p->state) return;
    p->state = state;
    p->tState = g_clock.t;
    if (state == 0) {
        qword a = p->v80;
        qword pos = *(qword *)((char *)p->plo->table[36].get((char *)p->plo + p->plo->table[36].delta) + 0x30);
        __asm__("qmfc2.ni %0, %1" : "=r"(*(int *)&p->dist) : "j"(Len(Sub(a, pos))));
    }
    switch (state) {
    case 1:
    case 2:
        p->pw->grf |= 2;
        break;
    default:
        p->pw->grf &= ~2;
        break;
    }

}
