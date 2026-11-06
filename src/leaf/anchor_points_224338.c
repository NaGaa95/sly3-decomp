// Resolve the two anchors of a link into world points (mode 0: fixed position mapped through the world, mode 1: point on an object) and optionally return the distance between them (Sly 2 func_001DEF98).
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Anchor {
    unsigned char opaque00[4];
    int mode;
    unsigned char opaque08[8];
    qword position;
    unsigned char opaque20[0xB0 - 0x20];
};
struct Anchors {
    unsigned char opaque000[0x50];
    void *world;
};
qword func_0028E910(void *world, int a, qword position);
void func_0022E330(void *object, qword *out, int a, float b);
static __inline__ qword Len(qword v)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    return d;
}
static __inline__ int GetXBits(qword v) { int g; __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(v)); return g; }

void func_00224338(struct Anchors *owner, struct Anchor *anchors, qword *points, float *distance)
{
    unsigned int i;
    for (i = 0; i < 2; i++) {
        struct Anchor *anchor = &anchors[i];
        switch (anchor->mode) {
        case 0:
            points[i] = func_0028E910(owner->world, 0, anchor->position);
            break;
        case 1:
            func_0022E330(*(void **)&anchor->position, &points[i], 0, *(float *)((unsigned char *)anchor + 0x14));
            break;
        }
    }
    if (distance) {
        qword diff;
        register qword first asm("vf2") = points[0]; /* register pin: first point in vf2 like the target */
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(diff) : "j"(first), "j"(points[1]));
        *(int *)distance = GetXBits(Len(diff));
    }
}
