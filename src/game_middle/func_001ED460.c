// Project a point onto the navigation region: take the closest point of the leaf triangle, find the polygon that
// contains it, and for a point outside walk the polygon's edges to find the nearest boundary point.
// Ported from Sly 2 func_001C0B50. The edge-distance helper takes the two hit endpoints as separate pointers, so
// each endpoint address gets its own multiply-add (the original copies the address for the second load).
// -fno-gcse keeps the hit array address out of a saved register.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-gcse
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct Hit { qword pos[2]; char pad[0x40]; };
struct Region {
    char pad[0xD0];
    char bsp[8];
    int count;
    int padDC;
    int padE0;
    qword *vertices;
};
extern float D_00324E48;
void *func_001EB4C8(void *, qword, int);
qword func_001EC188(void *, qword);
int func_001EDFE0(struct Region *, void *, qword, qword, int, void **);
int func_001E6BF0(void *, qword);
qword func_001C9428(void *, void *, qword);
int func_001ED1B0(struct Region *, qword, qword, int, struct Hit *, int);
void func_00120A00(qword, qword, qword, qword *, float *, float *);
int func_001ED190(struct Region *, qword, qword *, int);
static inline float GetZ(qword q) { float z; __asm__("pextuw %0,$zero,%1" : "=r"(z) : "r"(q)); return z; }
static inline void NearestOnEdge(qword point, const qword *start, const qword *end, qword *nearest, float *distance)
{
    func_00120A00(point, *start, *end, nearest, 0, distance);
}
int func_001ED460(struct Region *p, qword point, qword *out)
{
    void *objects[128];
    union U a, b;
    union { qword q; int i[4]; } best;
    struct Hit hits[1];
    union U nearest;
    float distance;
    void *leaf;
    struct Region *poly;
    qword projected;
    int n, i, j, k, c;
    float bestDistance;
    leaf = func_001EB4C8(p->bsp, point, 1);
    if (!leaf)
        return 0;
    projected = func_001EC188(leaf, point);
    poly = 0;
    n = func_001EDFE0(p, 0, projected, projected, 128, objects);
    for (j = 0; j < n; j++) {
        if (func_001E6BF0(objects[j], point)) {
            poly = objects[j];
            break;
        }
    }
    if (!poly) {
        *out = projected;
        return 1;
    }
    best.i[2] = 0;
    best.i[1] = 0;
    best.i[0] = 0;
    bestDistance = D_00324E48;
    a.q = func_001C9428(poly, 0, poly->vertices[0]);
    a.f[2] = GetZ(projected);
    for (i = 1; i < poly->count; i++) {
        b.q = func_001C9428(poly, 0, poly->vertices[i]);
        b.f[2] = GetZ(projected);
        c = func_001ED1B0(p, a.q, b.q, 1, hits, 2);
        for (k = 0; k < c; k++) {
            NearestOnEdge(projected, &hits[k].pos[0], &hits[k].pos[1], &nearest.q, &distance);
            if (distance < bestDistance) {
                bestDistance = distance;
                best.q = nearest.q;
            }
        }
        a = b;
    }
    func_001ED190(p, best.q, out, 0);
    return 1;
}
