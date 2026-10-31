// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; };
struct VEntry { short delta; short pad; void *(*get)(void *); };
struct OBJ { char pad[0xC]; struct VEntry *table; };
struct X134 { char pad[0x18]; int grf; };
struct X11B4 { char pad[0x4AC]; struct OBJ *pobj; };
struct OWNER { char pad[0x134]; struct X134 *p134; char pad138[0x320 - 0x138]; char a320[4]; char pad324[0x113C - 0x324]; void *p113C;
    char pad1140[0x11B4 - 0x1140]; struct X11B4 *p11B4; };
struct ST {
    struct OWNER *powner; char pad4[0xC - 4]; int state; char pad10[4]; int state2; float t18; char pad1C[0x44 - 0x1C];
    struct OBJ *pobj44;
};
extern struct CLOCK g_clock;
int func_0017E810(struct ST *p);
void func_0017EAD0(struct ST *p, int n);
void func_0017E850(struct ST *p, int state);
int func_00154798(struct OWNER *p, int n);
int func_002503C8(struct OWNER *p, float g);
int func_00138AC8(void *p);
void func_001B7268(void *p, int n, float g, int a, int b);
#define GETPOS(o) (*(qword *)((char *)(o)->table[36].get((char *)(o) + (o)->table[36].delta) + 0x30))
static __inline__ qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static __inline__ qword Len(qword v)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    return d;
}
static __inline__ float GetX(qword v) { float g; __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(v)); return g; }
#define FREADY(powner) (!(powner)->p113C || func_00138AC8((powner)->p113C))
void func_0017EBA0(struct ST *p)
{
    int state2, state;
    struct X134 *p134;

top:
    {
        state2 = p->state2;
        p134 = p->powner->p134;
        state = p->state;
        switch (state2) {
        case 0:
            if (state == 1 && func_0017E810(p)) {
                qword a = GETPOS(p->powner->p11B4->pobj);
                if (GetX(Len(Sub(a, GETPOS(p->pobj44)))) < 250.0f)
                    func_0017EAD0(p, 1);
            }
            break;
        case 1:
            if (!func_0017E810(p))
                func_0017EAD0(p, 0);
            else if (g_clock.t - p->t18 > 0.35f)
                func_0017EAD0(p, 2);
            break;
        case 2:
            if (state == 4) {
                qword a = GETPOS(p->powner->p11B4->pobj);
                if (400.0f < GetX(Len(Sub(a, GETPOS(p->pobj44)))))
                    func_0017E850(p, 3);
            }
            break;
        }
        switch (p->state) {
        case 1:
        case 2:
            if (!(p134->grf & func_00154798(p->powner, 7)))
                func_0017E850(p, 6);
            else if (func_002503C8(p->powner, 0.1f))
                func_0017E850(p, 2);
            else if (p->state2 == 2)
                func_0017E850(p, 4);
            else
                func_0017E850(p, 1);
            break;
        case 4:
        case 5:
            if (!(p134->grf & func_00154798(p->powner, 7)))
                func_0017E850(p, 6);
            else if (func_002503C8(p->powner, 0.1f))
                func_0017E850(p, 5);
            else
                func_0017E850(p, 4);
            break;
        case 0:
            if (FREADY(p->powner))
                func_0017E850(p, 1);
            break;
        case 6:
            if (FREADY(p->powner))
                func_001B7268(p->powner->a320, 0xB, 1.0f, 0, 0);
            break;
        case 3:
            if (FREADY(p->powner))
                func_0017E850(p, 1);
            break;
        }
        if (p->state == -1)
            return;
        if (p->state != state)
            goto top;
        if (p->state2 != state2)
            goto top;
    }
}
