// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct CLOCK { float t; };
struct VEntry { short delta; short pad; void *(*get)(void *); };
struct OBJ { char pad[0xC]; struct VEntry *table; char pad10[0x28 - 0x10]; unsigned long low : 56; unsigned long bits : 8; };
struct TRI { int a, b, c; };
struct OWNER { char pad[0x1A0]; struct TRI tri; char pad1AC[0x113C - 0x1AC]; char a113C[4]; char a1140[4]; };
struct ST {
    struct OWNER *powner; void *p4; int pad8; int state; float t10; char pad14[0x1C - 0x14];
    void *p1C; void *p20; char a24[4]; void *p28; void *p2C; void *p30; void *p34; struct OBJ *pobj38;
    char pad3C[0x44 - 0x3C]; struct OBJ *pobj44; char pad48[0x80 - 0x48]; qword v80; qword v90; struct TRI triA0;
};
extern struct CLOCK g_clock;
extern struct VQ { qword q; } D_00317550;
void func_0017EAD0(struct ST *p, int n);
void func_0023AC58(void *p);
void func_00137588(void *pv, struct OWNER *powner, float g0, float g1, int n, void *pa);
static __inline__ void ClearTri(struct TRI *pt)
{
    pt->c = 0;
    pt->b = 0;
    pt->a = 0;
}
static __inline__ void *VCall(struct OBJ *p, int i)
{
    return p->table[i].get((char *)p + p->table[i].delta);
}
void func_0017E850(struct ST *p, int state)
{
    void *pa;
    int na;
    void *pb;
    int nb;

    if (state == p->state)
        return;
    p->state = state;
    p->t10 = g_clock.t;
    ClearTri(&p->powner->tri);
    pa = 0;
    na = 1;
    pb = 0;
    nb = 1;
    switch (p->state) {
    case -1:
        if (p->pobj38 && (p->pobj38->bits & 1))
            VCall(p->pobj38, 9);
        func_0017EAD0(p, -1);
        break;
    case 0:
        pa = p->p28;
        if (!p->pobj38)
            break;
        if (!p->pobj44)
            break;
        {
            U s;
            qword pos = ((qword *)VCall(p->pobj44, 36))[3];
            qword rs, rd = D_00317550.q;
            __asm__("qmtc2.ni %1, %0" : "=j"(rs) : "r"(-10.0f));
            __asm__("vadda.xyzw $ACC, %0, $vf0\n\tvmaddx.xyzw %0, %1, %2x" : "+j"(pos) : "j"(rd), "j"(rs));
            p->v80 = pos;
            s.q = rs;
            {
                qword rs2;
                __asm__("qmtc2.ni %1, %0" : "=j"(rs2) : "r"(-1.0f));
                s.q = rs2;
                __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(p->v90) : "j"(D_00317550.q), "j"(rs2));
            }
            ClearTri(&p->triA0);
        }
        func_0017EAD0(p, 0);
        break;
    case 6:
        pa = p->p34;
        func_0017EAD0(p, 0);
        break;
    case 1:
        if (p->pobj38 && !(p->pobj38->bits & 1))
            VCall(p->pobj38, 8);
        pa = p->p4;
        na = 9;
        pb = p->p1C;
        nb = 9;
        break;
    case 4:
        pa = p->p4;
        na = 9;
        pb = p->p20;
        nb = 9;
        break;
    case 2:
    case 5:
        pa = p->p2C;
        na = 9;
        break;
    case 3:
        pa = p->p30;
        break;
    }
    func_0023AC58(p->powner->a1140);
    func_00137588(pa, p->powner, 0.0f, 1.0f, na, p->powner->a113C);
    func_00137588(pb, p->powner, 0.0f, 1.0f, nb, p->a24);
}
