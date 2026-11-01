// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Nearest visible object in the global object list whose line of sight to the origin is clear; writes its position.
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x120]; struct VTE e120; };
struct SO {
    unsigned char pad0[0xC];
    struct VT *pvt;
    unsigned char pad10[0xD0 - 0x10];
    struct SO *pnext;
    int pad2;
    int grf;
};
struct Probe {
    unsigned char pad0[0xC];
    struct VT *pvt;
    unsigned char pad10[0x3E0 - 0x10];
    void *region;
};
struct Hit { int a; int id; };
extern "C" void func_002BC490(void *p, int n);
class CFrame { public: CFrame(); ~CFrame(); };
class Scope { public: ~Scope() { func_002BC490(this, 2); } };
extern "C" {
extern char D_00475480[];
extern struct { struct SO *p; } D_00479AD8;
extern float D_0032577C;
int func_0027F258(void *region, qword pos);
int func_0025CEC8();
void func_0025CF18(void *pg, qword a, qword b, int (*pfn)(), int c, int *pn0, int *pn1);
struct Hit *func_00165000(int n, qword a, qword b, int n0, int n1, void *phit);
int func_001C8F20(struct SO *pso, int id);
}
static __inline__ struct M4 *Matrix(void *pv)
{
    struct SO *p = (struct SO *)pv;
    struct VTE *e = &p->pvt->e120;
    return ((struct M4 *(*)(void *))e->pfn)((char *)p + e->d);
}
static inline float Dist2(qword a, qword b)
{
    qword d, one;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(d), "=&j"(one));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
extern "C" int func_00205590(struct Probe *self, qword origin, qword *outPos)
{
    int found = 0;
    if (self->region) {
        Scope scope;
        struct SO *pso;
        float best = D_0032577C;
        for (pso = D_00479AD8.p; pso; pso = pso->pnext) {
            qword pos;
            float d;
            if (!(pso->grf & 0x100))
                continue;
            pos = Matrix(pso)->r[3];
            d = Dist2(Matrix(self)->r[3], pos);
            if (best < d)
                continue;
            if (func_0027F258(self->region, pos)) {
                CFrame frame;
                int n0, n1;
                struct Hit *hit;
                func_0025CF18(D_00475480, origin, pos, func_0025CEC8, 0, &n0, &n1);
                hit = func_00165000(0, origin, pos, n0, n1, 0);
                if (hit && !func_001C8F20(pso, hit->id))
                    continue;
                best = d;
                found = 1;
                *outPos = pos;
            }
        }
    }
    return found;
}
