// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef struct { qword row[4]; } Matrix;
struct Method { short delta, reserved; Matrix *(*function)(void *); };
struct Table { unsigned char prefix[0x120]; struct Method frame; };
struct Shape {
    unsigned char prefix0[0xC];
    struct Table *table;
    unsigned char gap10[0xD8 - 0x10];
    int count;
    unsigned char gapDC[0xE4 - 0xDC];
    qword *points;
};
struct Request { int bytes, alignment; };
extern qword D_00317550;
void *func_001D25B0(struct Request *request);
void func_00119EA8(void *plane, qword normal, qword point);
static inline struct Request *request(struct Request *r, int bytes, int alignment)
{
    r->bytes = bytes;
    r->alignment = alignment;
    return r;
}
static inline qword Transform(qword point, qword r0, qword r1, qword r2, qword r3)
{
    qword result;
    __asm__("vmulax.xyz $ACC,%1,%2x\n\tvmadday.xyz $ACC,%3,%2y\n\tvmaddaz.xyz $ACC,%4,%2z\n\tvmaddw.xyz %0,%5,$vf0w"
            : "=j"(result) : "j"(r0), "j"(point), "j"(r1), "j"(r2), "j"(r3));
    return result;
}
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Cross(qword a, qword b)
{
    qword r;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Normalize(qword v)
{
    qword d, one, l, r;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
// Build the shape's world-space outline: transform every point by the object matrix and make one edge plane (normal from edge x up axis) per consecutive pair.
void func_00214A70(struct Shape *self, qword **outPoints, qword **outPlanes)
{
    Matrix matrix;
    struct Request req;
    qword *points, *planes;
    int i, j;
    matrix = *self->table->frame.function((char *)self + self->table->frame.delta);
    points = func_001D25B0(request(&req, self->count * 16, 16));
    planes = func_001D25B0(request(&req, self->count * 16 - 16, 16));
    for (i = 0; i < self->count; i++)
        points[i] = Transform(self->points[i], matrix.row[0], matrix.row[1], matrix.row[2], matrix.row[3]);
    for (j = 0; j < self->count - 1; j++) {
        qword *plane = &planes[j];
        qword *p = &points[j + 1];
        qword normal = Normalize(Cross(Sub(p[0], p[-1]), D_00317550));
        func_00119EA8(plane, normal, p[-1]);
    }
    *outPoints = points;
    *outPlanes = planes;
}
