// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Recursive BSP-style plane walk: sets bit `bit` in the visibility word of every leaf the sphere (pos, r) reaches.
// Same algorithm as Sly 2 func_001A3B80.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct N { qword plane; struct N *front; struct N *back; int frontLeaf; int backLeaf; };
struct S { char pad[0x4D98]; char *leafBits; };
struct BS { int a[8]; };
void func_002BA000(void *p);
static __inline__ void SetBit(int *a, int bit) { int *pw = &a[bit / 32]; *pw |= 1 << bit; }
void func_001C5A98(struct S *s, struct N *n, qword pos, float r, int bit)
{
    U d, one;
    qword plane;
    float dist;
    plane = n->plane;
    func_002BA000(&d);
    func_002BA000(&one);
    __asm__("vmul.xyz %1, %3, %4\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddaz.x $ACC, %0, %1z\n\tvmsubw.x %1, %0, %3w\n\tqmfc2.ni %2, %1"
            : "=&j"(one.q), "=&j"(d.q), "=r"(dist) : "j"(plane), "j"(pos));
    if (dist < r) {
        if (n->front)
            func_001C5A98(s, n->front, pos, r, bit);
        else
            SetBit(((struct BS *)s->leafBits)[n->frontLeaf].a, bit);
    }
    if (-r < dist) {
        if (n->back)
            func_001C5A98(s, n->back, pos, r, bit);
        else
            SetBit(((struct BS *)s->leafBits)[n->backLeaf].a, bit);
    }
}
