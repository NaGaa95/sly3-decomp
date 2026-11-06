// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// For each of `count` vertices of mesh A's point table pick the best-ranked contact plane from the vertex's surface list (heads[i], NODEs
// chained through ->next), then emit contacts through func_001CB8B0 (same routine as Sly 2 func_001A87F0, with the lazy point-table refresh added):
//   - kind 1: the vertex itself (position = points.data[indices[i]]) with the best plane's normal and the vertex's own plane distance;
//   - kind 2: every other list vertex of the same chain that lies closer to the best plane than the vertex does.
// A surface is ranked by the smallest signed distance (dot(normal.xyz, p.xyz) - normal.w) from its plane to the vertex (orig) and to the far end of
// every edge in the chain (min); the surface with the largest `min` above -FLT_MAX wins, and bestOrig is its `orig`. SURFACE.flags bit 8 marks
// surfaces already ranked (set while scanning, cleared again before the contacts are emitted).
// Allocation notes: SCALAR/VECTOR default constructors call func_002BA000 / func_002BA008 (they give the dead sqc2 stores of every PlaneDist expansion);
// `d` and `m` live at function scope and are shared by both loops; PlaneDist takes the plane as a VU_VECTOR4 by value; the loop-top loads are
// heads, indices, then the lazily refreshed point table.
typedef int qword __attribute__((mode(TI)));
struct SCALAR;
struct VECTOR;
extern "C" SCALAR *func_002BA000(SCALAR *);
extern "C" VECTOR *func_002BA008(VECTOR *);
struct SCALAR { qword q; SCALAR() { (void)func_002BA000(this); } };
struct VECTOR { qword q; VECTOR() { (void)func_002BA008(this); } };
struct VU_VECTOR4 { qword q; VU_VECTOR4(qword a) { q = a; } };
struct W;
struct B;
struct XP;
struct POINTS { int count; qword *data; };
struct Owner { char pad[0xA4]; int version; };
struct A { Owner *owner; char pad4[0xA0 - 4]; POINTS points; char padA8[0xC0 - 0xA8]; int version; };
struct SURFACE { qword plane; char pad10[8]; int flags; };
struct EDGE { unsigned short ends[2]; };
struct NODE { char pad[0x10]; qword point; char pad20[0x50 - 0x20]; SURFACE *surface; EDGE *edge; int reverse; NODE *next; };
extern "C" {
extern float D_00323928;
void func_001CB8B0(W *, A *, B *, qword, float, qword, int, int, int, XP **);
void func_0018B1E0(A *);
}

/* signed distance of pos from plane: dot(plane.xyz, pos.xyz) - plane.w, via VU0 macro mode */
static inline float PlaneDist(VU_VECTOR4 plane, qword pos)
{
    SCALAR dot, one;
    qword r, unit;
    float f;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddaz.x $ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w"
            : "=j"(r), "=&j"(unit) : "j"(plane.q), "j"(pos));
    dot.q = r;
    one.q = unit;
    /* gcc supplies the qmfc2 for the "r" qword operand; the extra unused "j"(r) is allocation-only: it keeps r's preferred class VU (sqc2 store, not sq). */
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(dot.q), "j"(r));
    return f;
}

/* signed distance of pos from plane: dot(plane.xyz, pos.xyz) - plane.w, via VU0 macro mode */
/* Same as PlaneDist; the single register pin of this function: the first expansion in the original keeps the dot product in $vf2 (the later ones
   are allocated that way by gcc on their own). */
static inline float PlaneDistPinned(VU_VECTOR4 plane, qword pos)
{
    SCALAR dot, one;
    register qword r __asm__("vf2");
    qword unit;
    float f;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddaz.x $ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w"
            : "=j"(r), "=&j"(unit) : "j"(plane.q), "j"(pos));
    dot.q = r;
    one.q = unit;
    /* gcc supplies the qmfc2 for the "r" qword operand; the extra unused "j"(r) is allocation-only: it keeps r's preferred class VU (sqc2 store, not sq). */
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(dot.q), "j"(r));
    return f;
}

static inline POINTS *Points(A *a)
{
    if (a->version != a->owner->version)
        func_0018B1E0(a);
    return &a->points;
}

extern "C" void func_001CC440(W *w, A *a, B *b, int count, int *indices, NODE **heads, XP **out)
{
    float d;
    NODE *m;
    for (int i = 0; i < count; i++) {
        NODE *head = heads[i];
        int index = indices[i];
        POINTS *positions = Points(a);
        qword *data = positions->data;
        SURFACE *best = 0;
        float bestMin = D_00323928;
        float bestOrig;
        qword bestNormal;
        qword position = data[index];
        NODE *n;
        for (n = head; n; n = n->next) {
            SURFACE *s = n->surface;
            qword plane = s->plane;
            if (!(s->flags & 8)) {
                s->flags |= 8;
                float orig = PlaneDistPinned(plane, position);
                float min = orig;
                for (m = head; m; m = m->next) {
                    d = PlaneDist(plane, data[m->edge->ends[1 - m->reverse]]);
                    if (d < min) min = d;
                }
                if (bestMin < min) { bestNormal = plane; best = s; bestMin = min; bestOrig = orig; }
            }
        }
        for (n = head; n; n = n->next) n->surface->flags &= ~8;
        VECTOR normal;
        normal.q = bestNormal;
        func_001CB8B0(w, a, b, position, bestOrig, normal.q, 1, (int)&positions->data[index], (int)best, out);
        for (m = head; m; m = m->next) {
            d = PlaneDist(bestNormal, m->point);
            if (d < bestOrig) {
                qword pt = m->point;
                VECTOR nn;
                nn.q = bestNormal;
                func_001CB8B0(w, a, b, pt, d, nn.q, 2, (int)m->edge, (int)best, out);
            }
        }
    }
}
