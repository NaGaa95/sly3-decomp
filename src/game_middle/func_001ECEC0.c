// Build the default portal/volume record: four vertices (position, neighbour table), two triangles of vertex
// pointers and one plane, then link it into the world. Ported from Sly 2 func_001C0648.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Alloc { int bytes; int align; };
struct Neighbour { struct Vertex *vertex; int pad; };
struct Vertex { qword pos; int count; struct Neighbour *neighbours; int pad[2]; };
struct VertexSource { qword pos; int count; int index[3]; };
struct Triangle { struct Vertex *vertex[3]; };
struct TriangleSource { int index[3]; };
struct Plane { float x, y; int z; unsigned short a, b; };
struct Record {
    char pad[0xD0];
    int vertexCount;
    struct Vertex *vertices;
    int triangleCount;
    struct Triangle *triangles;
    int planeCount;
    struct Plane *planes;
    char pad0E8[0x104 - 0xE8];
    int serial;
};
struct World { char pad[0x450C]; int serial; };
extern struct World D_00475480;
extern struct VertexSource D_00324DB0[];
extern struct TriangleSource D_00324E30[];
static inline float SqrtF(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(r) : "f"(x));
    return r;
}
void *func_001D2538(struct Alloc *request);
void *func_001D2470(struct Alloc *request);
void func_001ED0E0(int *counts);
void func_001ECEC0(struct Record *p)
{
    struct Alloc a;
    int i, j, k, m;
    struct Plane *plane;
    float g;
    p->vertexCount = 4;
    a.bytes = 0x80;
    a.align = 0x10;
    p->vertices = func_001D2538(&a);
    for (i = 0; i < p->vertexCount; i++) {
        struct VertexSource *src = &D_00324DB0[i];
        struct Vertex *dst = &p->vertices[i];
        dst->pos = src->pos;
        dst->count = src->count;
        a.bytes = dst->count * 8 + 8;
        a.align = 0x10;
        dst->neighbours = func_001D2470(&a);
        for (j = 0; j < dst->count; j++) {
            struct Neighbour *n = &dst->neighbours[j];
            n->vertex = &p->vertices[src->index[j]];
        }
    }
    p->triangleCount = 2;
    a.bytes = 0x18;
    a.align = 0x10;
    p->triangles = func_001D2538(&a);
    for (k = 0; k < p->triangleCount; k++) {
        struct TriangleSource *ts = &D_00324E30[k];
        struct Vertex **out = p->triangles[k].vertex;
        int *in = ts->index;
        for (m = 0; m < 3; m++)
            *out++ = &p->vertices[*in++];
    }
    p->planeCount = 1;
    a.bytes = 0x10;
    a.align = 0x10;
    plane = func_001D2538(&a);
    p->planes = plane;
    g = SqrtF(2.0f) * 0.5f;
    plane->a = 0xC001;
    plane->b = 0xC000;
    plane->z = 0;
    plane->x = g;
    plane->y = -g;
    func_001ED0E0(&p->vertexCount);
    p->serial = ++D_00475480.serial;
}
