// Rebuild the mover path between two positions: a straight two-point route when no path object or the path query is trivial, otherwise the path-planner result; then drop every point to the mover height.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VEntry { short delta; short pad; M4 *(*method)(void *); };
struct PathResult { unsigned char pad0[0x40]; float x, y; unsigned char pad48[0x180 - 0x48]; } __attribute__((aligned(16)));
struct Points { unsigned char pad0[0xD8]; int count; unsigned char padDC[8]; qword *items; };
struct Mover {
    unsigned char pad00[0xC];
    VEntry *table;
    unsigned char pad10[0x250 - 0x10];
    void *path;
    unsigned char pad254[4];
    Points *points;
    float settle;
};
extern "C" int func_001ED1B0(void *path, qword position, qword reference, int a, PathResult *result, int b);
extern "C" int func_001EC688(void *path, qword position, qword reference, Points *points);
extern "C" void func_0022DB08(Points *points);
static inline M4 *Matrix(Mover *object)
{
    VEntry *entry = &object->table[36];
    return entry->method((char *)object + entry->delta);
}
static inline float PackedZ(qword q)
{
    float z;
    asm("pextuw %0,$0,%1" : "=r"(z) : "r"(q));
    return z;
}
extern "C" void func_00217328(Mover *self, qword position, qword reference)
{
    PathResult result;
    int r;
    if (!self->path || (r = func_001ED1B0(self->path, position, reference, 4, &result, 2), !self->path) ||
        (r == 1 && result.x == 0.0f && result.y == 1.0f)) {
        self->points->items[0] = position;
        self->points->items[1] = reference;
        self->points->count = 2;
        func_0022DB08(self->points);
    } else {
        func_001EC688(self->path, position, reference, self->points);
    }
    self->settle = 0.0f;
    {
        qword row = Matrix(self)->r[3];
        for (int i = 0; i < self->points->count; i++) {
            ((float *)&self->points->items[i])[2] = PackedZ(row);
        }
    }
}
