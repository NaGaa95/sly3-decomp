// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00176960: adapted from Sly 2 func_001999D0 (contact direction of a shape feature); takes a REQ record.
typedef int qword __attribute__((mode(TI)));
typedef unsigned short ushort;
union U { qword q; float f[4]; int i[4]; };
struct EDGE;
struct NODE;
struct FACE { U plane; EDGE *first, *second; int flags; };
struct EDGE { ushort vertices[2], face, other; EDGE *next, *nextOther; };
struct GEOMETRY { char pad0[4]; U *points; char pad8[4]; FACE *faces; };
struct QUERY { int pad0, count, pad8; NODE *tree; };
struct SX { char pad[0xA4]; int xA4; };
struct EC;
struct LO;
struct SHAPE { SX *psx; LO *owner; char pad8[0x78 - 0x8]; QUERY query; char pad88[0xA0 - 0x88]; GEOMETRY geometry; char padB0[0xC0 - 0xB0]; int xC0; };
struct LO { char pad[0xDC]; EC *ec; char padE0[0x288 - 0xE0]; SHAPE *pshape; };
struct REQ { SHAPE *shape; int kind; void *info; int pad; U pos; U dir; };
struct SPAN { U first, last, firstPlane, lastPlane; float from, to; int flags; FACE *firstFace, *lastFace; };
extern "C" {
extern U D_00317560, D_00317530;   // zero vector, fallback direction
void func_0018B1E0(SHAPE *p);
int func_0018B330(GEOMETRY *, QUERY *, int, int, EDGE **);
int func_00176368(SHAPE *, EDGE *, U *);
int func_00119BE8(NODE *, int, qword, qword, int, SPAN *);
int func_00176770(LO *, REQ *);
int func_00176960(LO *p, REQ *preq);
}

static inline void Refresh(SHAPE *shape)
{
    if (shape->xC0 != shape->psx->xA4)
        func_0018B1E0(shape);
}
static inline qword Add(qword a, qword b)
{
    __asm__("vadd.xyzw %0, %0, %1" : "+j"(a) : "j"(b));
    return a;
}
static inline qword Dot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword Sqrt(qword d)
{
    qword l;
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    return l;
}
static inline qword Len(qword v) { return Sqrt(Dot(v, v)); }
static inline qword Div(qword v, qword l)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
static inline float X(qword q)
{
    float f;
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(q));
    return f;
}
static inline qword Normalize(qword v, qword fallback)
{
    qword l = Len(v);
    if (X(l) < 1.0e-4f)
        return fallback;
    return Div(v, l);
}

int func_00176960(LO *p, REQ *preq)
{
    SHAPE *shape = preq->shape;
    if (!shape->owner->ec)
        return 0;
    switch (preq->kind) {
    case 1: {
        EDGE *edges[64];
        U direction;
        void *info = preq->info;
        Refresh(shape);
        GEOMETRY *geometry = &shape->geometry;
        int index = (U *)info - geometry->points;
        qword sum = D_00317560.q;
        int found = 0;
        Refresh(shape);
        int count = func_0018B330(geometry, &shape->query, index, 64, edges);
        for (int i = 0; i < count; i++) {
            if (func_00176368(shape, edges[i], &direction)) {
                found = 1;
                sum = Add(sum, direction.q);
            }
        }
        if (!found)
            return 0;
        { U *out = &preq->dir; out->q = Normalize(sum, D_00317530.q); }
        break;
    }
    case 3:
        if (!func_00176368(shape, (EDGE *)preq->info, &preq->dir))
            return 0;
        break;
    case 2: {
        FACE *face = (FACE *)preq->info;
        if (face->plane.f[2] < 0.7f)
            return 0;
        Refresh(shape);
        SHAPE *other = p->pshape;
        GEOMETRY *geometry = &shape->geometry;
        Refresh(other);
        QUERY *query = &other->query;
        int found = 0;
        qword sum = D_00317560.q;
        U direction;
        SPAN spans[2];
        EDGE *edge;
        for (edge = face->first; edge; edge = edge->next) {
            if (func_00176368(shape, edge, &preq->dir)) {
                U *points = geometry->points;
                if (func_00119BE8(query->tree, 0x7FFFFFFF, points[edge->vertices[0]].q,
                                  points[edge->vertices[1]].q, 2, spans) > 0) {
                    found = 1;
                    sum = Add(sum, direction.q);
                }
            }
        }
        for (edge = face->second; edge; edge = edge->nextOther) {
            if (func_00176368(shape, edge, &direction)) {
                U *points = geometry->points;
                if (func_00119BE8(query->tree, 0x7FFFFFFF, points[edge->vertices[0]].q,
                                  points[edge->vertices[1]].q, 2, spans) > 0) {
                    found = 1;
                    sum = Add(sum, direction.q);
                }
            }
        }
        if (!found)
            return 0;
        { U *out = &preq->dir; out->q = Normalize(sum, D_00317530.q); }
        break;
    }
    }
    return func_00176770(p, preq);
}
