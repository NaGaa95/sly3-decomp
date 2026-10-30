// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Port of Sly 2 src/hand/func_001997D8.cpp (basis/point now read from a record; per-segment scoped local with dtor).
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { U r[3]; };
struct M4 { M3 m; U pos; };
struct PLANE { qword q; };
struct HIT { U point[2]; U plane[2]; float parameter[2]; int kind; PLANE *face[2]; int unk54[3]; };
struct S0 { char pad[0x18]; long x18; char pad2[0x70 - 0x20]; S0 *x70; };
struct EC2 { char pad[0x34]; S0 *x34; char pad2[0x70 - 0x38]; long x70; };
struct C { char pad[0xDC]; EC2 *xdc; };
struct L { int x0; L *x4; int x8; C *xc; };
struct EC { char pad[0x64]; L *x64; };
struct O { char pad[0xDC]; EC *xdc; };
struct R0 { int x0; };
struct REQ { R0 *x0; int pad[3]; qword x10; qword x20; };
extern "C" {
extern qword D_00317550;
extern qword D_00317540;
void func_0011FEA8(qword a, qword b, qword c, qword *pm);
qword func_0028E910(int a, int b, qword c);
qword *func_002BA818(qword *pq, qword q);
void func_00176578(const M4 *pm, int n, U *apt);
int func_00164A10(S0 *s, qword a, qword b, int n, HIT *ph);
void func_002BC900(void *object, int flags);
}
struct SCOPE {
    qword pad;
    ~SCOPE() { func_002BC900(this, 2); }
};

static inline int HitSegment(S0 *s, const qword *a, const qword *b, HIT *h)
{
    return func_00164A10(s, *a, *b, 1, h);
}

extern "C" int func_00176770(O *p, REQ *preq)
{
    M3 m;
    M4 m4;
    qword apt[22];
    HIT hit;
    L *l;
    int c = 0;
    qword q2 = preq->x20;
    m.r[0].q = q2;
    func_0011FEA8(q2, D_00317550, D_00317540, &m.r[1].q);
    M4 *pm = &m4;
    qword q1 = func_0028E910(preq->x0->x0, 0, preq->x10);
    (void)func_002BA818(&m4.pos.q, q1);
    pm->m = m;
    m4.m.r[0].i[3] = m4.m.r[1].i[3] = m4.m.r[2].i[3] = 0;
    pm->pos.f[3] = 1.0f;
    func_00176578(&m4, 22, (U *)apt);
    for (l = p->xdc->x64; l; l = l->x4) {
        int i;
        if (l->xc->xdc->x70 & 4)
            continue;
        for (i = 0; i < sizeof apt / sizeof *apt; i += 2) {
            SCOPE scope;
            S0 *s;
            for (s = l->xc->xdc->x34; s; s = s->x70) {
                if (s->x18 & 0x10000)
                    continue;
                if (HitSegment(s, &apt[i], &apt[i + 1], &hit) <= 0)
                    continue;
                if (i < 4)
                    return 0;
                if (hit.parameter[0] == 0.0f)
                    return 0;
                if (hit.plane[0].f[2] > 0.7f)
                    c++;
            }
        }
    }
    return c >= 2;
}
