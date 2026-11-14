// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* func_0019EE70: sphere contact generator (Sly 2 func_001823C8 counterpart, Sly 3 layouts).
   After the base contacts (func_0023EDD0), when request flag 0x20000 is set every node of every entry is tested
   against the owner's position: inside the summed radius a planar push-out contact (kind 10) is added, otherwise
   each edge from a transformed vertex to its cached world point is intersected with the node sphere
   (func_00164B08) and the first hit adds a contact on the hit plane.
   func_002BA000 returns its argument (out-of-line default constructor of the dot/one vectors). */
typedef int qword __attribute__((mode(TI)));
typedef union U { qword q; float f[4]; int i[4]; } U;
typedef struct M4 { U r[4]; } M4;
typedef struct NODE { U pos; char pad10[0x50]; struct NODE *next; } NODE;
typedef struct ENTRY { char pad0[0x10]; NODE *first; char pad14[0xC]; float radius; char pad24[0xC]; } ENTRY;
typedef struct OWNER { char pad0[0x70]; qword pos; char pad80[0x24]; int stamp; } OWNER;
typedef struct WORLD { int count; qword *apos; } WORLD;
typedef struct REQUEST {
    OWNER *owner; int pad4; float radius; char padC[0xC]; long flags; int start; char pad24[0xC];
    M4 matrix; char pad70[0x1C]; qword *avertex; char pad90[0x10]; WORLD world; char padA8[0x18]; int stamp;
} REQUEST;
typedef struct CONTACT { char pad[0xD0]; } CONTACT;
typedef struct P { char pad0[0xD0]; int ccontact; CONTACT *acontact; char padD8[0x11C]; int centry; ENTRY aentry[1]; } P;
typedef struct SEGMENT { qword apos[2]; qword anormal[2]; char pad40[0x20]; } SEGMENT;
extern qword D_00317530;
extern char D_00475480[];
extern void func_0023EDD0(P *p, REQUEST *q, int a2, int a3, int a4, CONTACT **ppc);
extern qword *func_002BA000(qword *pq);
extern void func_0018B1E0(REQUEST *q);
extern int func_00164B08(qword posCenter, float sRadius, qword pos0, qword pos1, int csegMax, SEGMENT *aseg);
extern void func_001CB8B0(void *pv, CONTACT *pc, REQUEST *q, qword pos, qword normal, int k, NODE *n, int x, CONTACT **ppc, float s);

static inline qword Sub(qword a, qword b) { __asm__("vsub.xyzw %0,%0,%1" : "+j"(a) : "j"(b)); return a; }
static inline qword Load(qword q) { qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(q)); return r; }
static inline qword VuFloat(float g) { qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(g)); return r; }
/* never-chosen "V" alternative: the word stays a MEM until reload (gcc-made lw) */
static inline qword VuFloatP(const float *pg) { qword r; __asm__("qmtc2.ni %1,%0" : "=j,j"(r) : "r,V"(*(const int *)pg)); return r; }
static inline float GX(qword qw) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(qw)); return x; }
static inline float GFromVf(qword qw) { float g; __asm__("qmfc2.ni %0,%1" : "=r"(g) : "j"(qw)); return g; }
static inline float GFromVfBits(qword qw) { int n; float g; __asm__("qmfc2.ni %0,%1" : "=r"(n) : "j"(qw)); __asm__("mtc1 %1,%0" : "=f"(g) : "r"(n)); return g; }
static inline qword AddScaled(qword a, qword b, qword s) { __asm__("vadda.xyzw ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x" : "+j"(a) : "j"(b), "j"(s)); return a; }
/* a + b * *pg */
static inline qword AddScaledTo(qword a, qword b, const float *pg)
{
    U scale;
    qword r;
    scale.q = VuFloatP(pg);
    __asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(a), "j"(b), "j"(scale.q));
    return r;
}
static inline qword MulPoint(const M4 *m, qword p)
{
    qword r = m->r[0].q;
    __asm__("vmulax.xyz ACC,%0,%4x\n\tvmadday.xyz ACC,%1,%4y\n\tvmaddaz.xyz ACC,%2,%4z\n\tvmaddw.xyz %0,%3,$vf0w"
        : "+j"(r) : "j"(m->r[1].q), "j"(m->r[2].q), "j"(m->r[3].q), "j"(p));
    return r;
}
static inline qword Length(qword v)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=&j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(d) : "j"(d));
    return d;
}
static inline qword Divide(qword v, qword len) { qword r; __asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q" : "=j"(r) : "j"(v), "j"(len)); return r; }
/* normalize *pv in place (fallback when shorter than 0.0001) and return the old length */
static inline float Normalize(U *pv, const qword *pfallback)
{
    qword v = Load(pv->q);
    qword len = Length(v);
    if (GX(len) < 0.0001f)
        pv->q = *pfallback;
    else
        pv->q = Divide(v, len);
    return GFromVf(len);
}
/* signed distance of pos from plane (normal.xyz, offset w) */
static inline float GDistPlane(qword plane, qword pos)
{
    U d, one;
    qword td, tone;
    func_002BA000(&d.q);
    func_002BA000(&one.q);
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddaz.x ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w"
        : "=&j"(td), "=&j"(tone) : "j"(plane), "j"(pos));
    one.q = tone;
    d.q = td;
    return GFromVfBits(td);
}

void func_0019EE70(P *p, REQUEST *q, int a2, int a3, int a4, CONTACT **ppc)
{
    U dir, posNew, posOld;
    SEGMENT aseg[2];
    qword center;
    int i;

    func_0023EDD0(p, q, a2, a3, a4, ppc);
    if (!(q->flags & 0x20000))
        return;
    center = q->owner->pos;
    for (i = 0; i < p->centry; i++) {
        ENTRY *entry = &p->aentry[i];
        NODE *n = entry->first;
        float radius = q->radius + entry->radius;
        for (; n; n = n->next) {
            float s;
            dir.q = Sub(n->pos.q, center);
            dir.i[2] = 0;
            s = Normalize(&dir, &D_00317530);
            if (s < radius) {
                posNew.q = VuFloat(-q->radius); /* the push-out scale lives in posNew's slot (sqc2 to 0x20) */
                func_001CB8B0(D_00475480, &p->acontact[p->ccontact - 1], q, AddScaled(center, dir.q, posNew.q), dir.q, 10, n, 0, ppc, s - radius);
            } else {
                WORLD *world;
                int j;
                if (q->stamp != q->owner->stamp)
                    func_0018B1E0(q);
                world = &q->world;
                for (j = q->start; j < world->count; j++) {
                    posNew.q = MulPoint(&q->matrix, q->avertex[j]);
                    posOld.q = world->apos[j];
                    posNew.f[2] = posOld.f[2] = n->pos.f[2];
                    if (func_00164B08(n->pos.q, radius, posNew.q, posOld.q, 2, aseg) > 0) {
                        qword normal, pos, contact;
                        normal = aseg[0].anormal[0];
                        pos = posOld.q;
                        contact = AddScaledTo(pos, normal, &q->radius);
                        s = GDistPlane(normal, pos) - q->radius;
                        func_001CB8B0(D_00475480, &p->acontact[p->ccontact - 1], q, contact, normal, 10, n, 0, ppc, s);
                        break;
                    }
                }
            }
        }
    }
}
