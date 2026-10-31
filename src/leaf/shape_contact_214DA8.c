// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M4 { float m[4][4]; };
struct VTE { short d; short pad; void *pfn; };
struct VT { unsigned char pad[0x120]; struct VTE e120; };
struct Shape {
    unsigned char pad0[0xC];
    struct VT *pvt;
    unsigned char pad10[0xD8 - 0x10];
    int count;
};
struct CTX { int a[4]; };
extern char D_00475480[];
void func_001D2770(struct CTX *ctx);
void func_001D2798(struct CTX *ctx, int n);
void func_00214A70(struct Shape *shape, qword **points, qword **planes);
void func_00214C40(int pointCount, qword *points, int planeCount, qword *planes, float *outDepth, qword *outPoint, qword *outPlane);
void func_001CB8B0(void *world, void *a, void *b, qword point, qword plane, int kind, int x, int y, void **out, float depth);
static __inline__ struct M4 *Matrix(struct Shape *p)
{
    struct VTE *e = &p->pvt->e120;
    return ((struct M4 *(*)(void *))e->pfn)((char *)p + e->d);
}
// Test two convex shapes against each other (support-point search in both directions); when they overlap, report the deepest contact through func_001CB8B0.
void func_00214DA8(void *objA, struct Shape *shapeA, void *objB, struct Shape *shapeB, void **out)
{
    struct CTX ctx;
    qword hit[4];
    qword *pointsA, *planesA, *pointsB, *planesB;
    float depthA, depthB;
    if (Matrix(shapeA)->m[2][2] < 0.5f)
        return;
    if (Matrix(shapeB)->m[2][2] < 0.5f)
        return;
    func_001D2770(&ctx);
    func_00214A70(shapeA, &pointsA, &planesA);
    func_00214A70(shapeB, &pointsB, &planesB);
    func_00214C40(shapeA->count - 1, pointsA, shapeB->count - 1, planesB, &depthA, &hit[0], &hit[1]);
    func_00214C40(shapeB->count - 1, pointsB, shapeA->count - 1, planesA, &depthB, &hit[2], &hit[3]);
    if (depthA >= 0.0f && depthB >= 0.0f) {
        func_001D2798(&ctx, 2);
        return;
    }
    if (depthA < depthB)
        func_001CB8B0(D_00475480, objA, objB, hit[0], hit[1], 10, 0, 0, out, depthA);
    else
        func_001CB8B0(D_00475480, objB, objA, hit[2], hit[3], 10, 0, 0, out, depthB);
    func_001D2798(&ctx, 2);
}
