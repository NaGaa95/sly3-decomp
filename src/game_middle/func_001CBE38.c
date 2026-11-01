// SLY3_CFLAGS: -Os -G0 -fno-gcse
// Clip the edges of the selected surfaces against the body's hull and record the originating edge in each hit
// (same routine as Sly 2 func_001A81F8, with the lazy version refresh of the geometry and body added).
typedef int qword __attribute__((mode(TI)));
struct Owner { unsigned char prefix[0xA4]; int version; };
struct Edge { unsigned short ipos[2]; unsigned short pad; unsigned short ivtx; struct Edge *next; };
struct Hit { unsigned char prefix[0x54]; struct Edge *edge; unsigned char rest[0x60 - 0x58]; };
struct Vertex { unsigned char prefix[0x18]; int flags; int pad; } __attribute__((aligned(32)));
struct Surface { unsigned char prefix[0x10]; struct Edge *edges; int pad; int flags; };
struct Entry { int word0; int word4; struct Surface *surface; };
struct GeomSet { int word0; qword *points; int word8; struct Vertex *vertices; };
struct Geometry {
    struct Owner *owner;
    unsigned char prefix[0xA0 - 4];
    struct GeomSet set;
    unsigned char gap[0xC0 - 0xB0];
    int version;
};
struct Hull { int w0, w4, w8; void *context; };
struct Body {
    struct Owner *owner;
    unsigned char prefix[0x78 - 4];
    struct Hull hull;
    unsigned char gap[0xC0 - 0x88];
    int version;
};
void func_0018B1E0(void *object);
int func_00119BE8(void *context, int limit, qword origin, qword direction, int capacity, struct Hit *output);
int func_001CBE38(void *unused, struct Body *body, struct Geometry *geom, int count, struct Entry *entries, int capacity, struct Hit *hits)
{
    int done, total, i;
    struct GeomSet *set;
    qword *points;
    struct Vertex *vertices;
    struct Surface *surface;
    if (geom->version != geom->owner->version)
        func_0018B1E0(geom);
    set = &geom->set;
    done = 0;
    total = 0;
    points = set->points;
    vertices = set->vertices;
    for (i = count - 1; i >= 0; i--)
        entries[i].surface->flags |= 1;
    for (i = count - 1; i >= 0; i--) {
        struct Edge *edge;
        struct Hull *hull;
        surface = entries[i].surface;
        if (!(surface->flags & 1))
            continue;
        if (surface->flags & 2)
            continue;
        surface->flags |= 2;
        if (body->version != body->owner->version)
            func_0018B1E0(body);
        hull = &body->hull;
        for (edge = surface->edges; edge; edge = edge->next) {
            {
                struct Vertex *vertex = vertices + edge->ivtx;
                if ((vertex->flags ^ 1) & 1)
                    continue;
            }
            total += func_00119BE8(hull->context, 0x7FFFFFFF, points[edge->ipos[0]], points[edge->ipos[1]], capacity - total, &hits[total]);
            for (; done < total; done++)
                hits[done].edge = edge;
        }
    }
    for (i = count - 1; i >= 0; i--) {
        surface = entries[i].surface;
        surface->flags &= ~3;
    }
    return total;
}
