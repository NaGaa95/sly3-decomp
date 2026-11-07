// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef int S64 __attribute__((mode(DI)));
struct O;
struct VTE { short d; short pad; void *(*pf)(void *, ...); };
struct XF { char pad[0x30]; qword pos; };
struct ITEMX { int x0; char pad4[0x18]; int x1C; };
struct HALF { ITEMX *x0; int x4; O *owner; struct OBJ *list; qword pos; char pad20[0x20]; };
struct EDGE { HALF h[2]; char pad80[0x2C]; EDGE *next; };
struct OBJ { char pad[0x10]; OBJ *next; };
struct COLL { char pad[0x18]; S64 flags; char pad20[0x64]; void *x84; char pad88[0x48]; };
struct LO { char pad[0xD0]; int count; COLL *colls; };
struct LINK { EDGE *first; LINK *next; int pad8; LO *lo; };
struct STATE { char pad[0x64]; LINK *first; };
struct O {
    char pad[0xC]; VTE *vt; char pad10[0xDC - 0x10]; STATE *state; char padE0[0x130 - 0xE0];
    OBJ *list130; ITEMX *x134; int x138; char pad13C[0x160 - 0x13C]; int x160; O *x164;
};
struct CL { void Follow() __asm__("func_00288098"); };
extern "C" {
extern qword D_00317550;
extern char D_00475480[];
void func_0023E068(O *);
int func_0013B500(OBJ *, int);
int func_00240E10(OBJ *, int);
int func_001E4FC8(OBJ *, int, O *);
int func_00119BE8(void *, int, qword, qword, int, void *);
void func_00287AF8(O *);
void func_00288098(O *);
void func_0015DCD0(void *, O *, void (CL::*)(), int);
extern const int D_00329760[4];
const int D_00329760[4] = { 0x32, 0x71, 0x59, 0x74 };
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
static inline XF *Xf(O *o) { VTE *v = &o->vt[36]; return (XF *)v->pf((char *)o + v->d); }
static inline float Dist(qword a, qword b)
{
    qword d, one, l;
    float f;
    int t;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "0"(a), "j"(b));
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(l), "=&j"(one) : "j"(d));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(l));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(l));
    return f;
}
static inline qword AddScaled(qword a, VU_FLOAT k, qword v) { qword r; __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(v), "j"(k.q)); return r; }
extern "C" void func_00287B40(O *p)
{
    func_0023E068(p);
    __asm__("" : : "r"(p));
    if (p->x160)
        return;
    if (p->list130)
        return;
    LO *lo;
    qword a, b;
    int i;
    COLL *c;
    float best = 3.402823466e+38f;
    EDGE *pbest = 0;
    for (LINK *link = p->state->first; link; link = link->next) {
        for (EDGE *e = link->first; e; e = e->next) {
            qword pos = e->h[0].pos;
            float dist = Dist(pos, Xf(p->x164)->pos);
            int k = p != e->h[0].owner;
            HALF *ph = &e->h[k];
            for (OBJ *o = e->h[1 - k].list; o; o = o->next) {
                for (unsigned i = 0; i < 4; i++)
                    if (func_0013B500(o, D_00329760[i]))
                        goto found;
                if (func_0013B500(o, 0x6F) && func_001E4FC8(o, func_00240E10(o, ph->x0->x1C), p))
                    goto found;
            }
            if (dist < best) {
                best = dist;
                pbest = e;
            }
        }
        if (func_0013B500((OBJ *)link->lo, 0x65)) {
            lo = link->lo;
            a = AddScaled(Xf(p)->pos, VU_FLOAT(15.0f), D_00317550);
            { qword pp = Xf(p)->pos; b = AddScaled(pp, VU_FLOAT(-15.0f), D_00317550); }
            char hit[0x60];
            for (i = 0; i < lo->count; i++) {
                c = &lo->colls[i];
                if (c->flags & 0x80000)
                    continue;
                if (func_00119BE8(c->x84, 0x7FFFFFFF, a, b, 1, hit)) {
                found:
                    func_00287AF8(p);
                    return;
                }
            }
        }
    }
    if (pbest) {
        int k = p == pbest->h[0].owner;
        HALF *ph = &pbest->h[k];
        p->list130 = ph->list;
        ITEMX *px = ph->x0;
        p->x134 = px;
        p->x138 = px->x0;
        func_0015DCD0(D_00475480, p, &CL::Follow, 0);
    }
}
