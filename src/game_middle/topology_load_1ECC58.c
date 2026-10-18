// SLY3_CFLAGS: -Os -G0 -fno-exceptions
typedef int Qword __attribute__((mode(TI)));
struct Allocation { int bytes, alignment; };
struct Vertex;
struct Edge { struct Vertex *vertex; float distance; };
struct Vertex {
    Qword position;
    int count;
    struct Edge *edges;
    int unused[2];
};
struct Triangle { struct Vertex *vertices[3]; };
struct Point { float x, y, z; unsigned short first, second; };
struct Topology {
    int vertexCount;
    struct Vertex *vertices;
    int triangleCount;
    struct Triangle *triangles;
};
struct Resource {
    char prefix[0x18];
    int identifier;
    char gap1C[0xB4];
    struct Topology topology;
    int pointCount;
    struct Point *points;
    char gapE8[0x1C];
    int serial;
};
struct Game {
    char prefix[0x450C];
    int serial;
    char gap4510[0x8E8];
    struct Resource *selected;
};
struct Stream;
extern struct Game D_00475480;
void func_0028FDE0(struct Resource *, struct Stream *);
int func_00119048(struct Stream *);
int func_00118FF8(struct Stream *);
void func_001192D8(struct Stream *, void *);
float func_00119260(struct Stream *);
void *func_001D2538(struct Allocation *);
void *func_001D2470(struct Allocation *);
void func_001ED0E0(struct Topology *);

void func_001ECC58(struct Resource *resource, struct Stream *stream)
{
    struct Allocation allocation;
    int vertexIndex, edgeIndex, triangleIndex, cornerIndex, pointIndex;
    func_0028FDE0(resource, stream);
    resource->topology.vertexCount = func_00119048(stream);
    allocation.bytes = resource->topology.vertexCount * 32;
    allocation.alignment = 16;
    resource->topology.vertices = func_001D2538(&allocation);
    resource->topology.triangleCount = func_00119048(stream);
    allocation.bytes = resource->topology.triangleCount * 12;
    allocation.alignment = 16;
    resource->topology.triangles = func_001D2538(&allocation);
    for (vertexIndex = 0; vertexIndex < resource->topology.vertexCount; vertexIndex++) {
        struct Vertex *vertex = &resource->topology.vertices[vertexIndex];
        func_001192D8(stream, vertex);
        vertex->count = func_00118FF8(stream);
        allocation.bytes = vertex->count * 8 + 8;
        allocation.alignment = 16;
        vertex->edges = func_001D2470(&allocation);
        for (edgeIndex = 0; edgeIndex < vertex->count; edgeIndex++) {
            struct Edge *edge = &vertex->edges[edgeIndex];
            edge->vertex = &resource->topology.vertices[
                func_00119048(stream)];
        }
    }
    for (triangleIndex = 0; triangleIndex < resource->topology.triangleCount; triangleIndex++) {
        struct Vertex **vertices = resource->topology.triangles[triangleIndex].vertices;
        for (cornerIndex = 0; cornerIndex < 3; cornerIndex++)
            *vertices++ = &resource->topology.vertices[
                func_00119048(stream)];
    }
    resource->pointCount = func_00119048(stream);
    allocation.bytes = resource->pointCount * 16;
    allocation.alignment = 16;
    resource->points = func_001D2538(&allocation);
    for (pointIndex = 0; pointIndex < resource->pointCount; pointIndex++) {
        struct Point *point = &resource->points[pointIndex];
        point->x = func_00119260(stream);
        point->y = func_00119260(stream);
        point->z = func_00119260(stream);
        point->first = func_00119048(stream);
        point->second = func_00119048(stream);
    }
    func_001ED0E0(&resource->topology);
    if (resource->identifier == 0x321)
        D_00475480.selected = resource;
    resource->serial = ++D_00475480.serial;
}
