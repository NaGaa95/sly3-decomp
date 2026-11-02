// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Collect the best-ranked objects within a radius of a query position (Sly 2 func_001A3F78 with a radius): walks the world's
// plane tree with an explicit stack (the far child is only pushed when the sphere around the position straddles the plane),
// ORs the 256-bit object masks of the leaves it reaches into a local copy of the world mask, then ranks every object in the
// mask by bias + weight * max(distance - radius, 0) in a capacity-bounded descending insertion list.
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
union U { qword q; float f[4]; U(); };
typedef union { qword q[2]; uint a[8]; } MASK;
struct HOME { qword q; };
inline void *operator new(unsigned, void *destination) { return destination; }
typedef struct NODE {
    qword plane;
    struct NODE *left, *right;
    int leftLeaf, rightLeaf;
} NODE;
struct WORK { MASK mask; NODE *stack[256]; HOME distance, unity; };
struct SPHERE {
    U position;
    float bias, weight;
    float Score(qword pos, float radius);
};
typedef struct OBJ { char pad[0xF0]; SPHERE sphere; } OBJ;
typedef struct { float score; OBJ *object; } RESULT;
typedef struct {
    char pad[0x4988];
    OBJ *objects[256];
    int word4D88, word4D8C;
    NODE *tree;
    int word4D94;
    MASK *leaves;
    MASK mask;
} WORLD;
extern "C" void *func_00292034(void *, int, uint);
extern "C" U *func_002BA000(U *);
inline U::U() { (void)func_002BA000(this); }
static inline float PlaneDistance(HOME *first, HOME *second, qword plane, qword pos)
{
    U *d = new ((void *)first) U;
    U *one = new ((void *)second) U;
    register qword r __asm__("vf2"); /* register pin: the plane distance lives in vf2 like the original */
    qword unit;
    float f;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddaz.x $ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w"
            : "=&j"(r), "=&j"(unit) : "j"(plane), "j"(pos));
    d->q = r;
    one->q = unit;
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(r));
    return f;
}
static inline float Length(qword a, qword b)
{
    qword r, one;
    float f;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "+j"(r), "=&j"(one));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(r));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(r));
    return f;
}
static inline float Max(float a, float b) { float f; __asm__("max.s %0,%1,%2" : "=f"(f) : "f"(a), "f"(b)); return f; }
inline float SPHERE::Score(qword pos, float radius) { return bias + weight * Max(Length(pos, position.q) - radius, 0.0f); }
static inline int BitIndex(uint isolated, int base)
{
    int one = base + 1;
    int result = (isolated & 0xAAAAAAAAU) ? one : base;
    if (isolated & 0xCCCCCCCCU) result += 2;
    if (isolated & 0xF0F0F0F0U) result += 4;
    if (isolated & 0xFF00FF00U) result += 8;
    if (isolated & 0xFFFF0000U) result += 16;
    return result;
}
extern "C" void func_001C5E98(WORLD *p, qword pos, int capacity, RESULT *results, float radius)
{
    WORK w;
    NODE *n;
    MASK *leaf;
    uint i;
    int depth;
    float score;
    func_00292034(results, 0, capacity * sizeof(RESULT));
    w.mask.q[0] = p->mask.q[0];
    w.mask.q[1] = p->mask.q[1];
    if (p->tree) {
        w.stack[0] = p->tree;
        depth = 1;
        do {
            n = w.stack[--depth];
            NODE *next;
            for (;;) {
                score = PlaneDistance(&w.distance, &w.unity, n->plane, pos);
                if (-radius < score) {
                    NODE *right = n->right;
                    if (!right) {
                        leaf = &p->leaves[n->rightLeaf];
                        break;
                    }
                    if (radius <= score)
                        next = right;
                    else
                        w.stack[depth++] = right;
                }
                if (score < radius) {
                    NODE *left = n->left;
                    if (!left) {
                        leaf = &p->leaves[n->leftLeaf];
                        break;
                    }
                    next = left;
                }
                n = next;
            }
            for (i = 0; i < 8; i++)
                w.mask.a[i] |= leaf->a[i];
        } while (depth > 0);
    }
    for (i = 0; i < 8; i++) {
        uint word = w.mask.a[i];
        if (word) {
            do {
                uint remaining = word & (word - 1);
                uint isolated = word & ~remaining;
                OBJ *o = p->objects[BitIndex(isolated, i * 32)];
                score = o->sphere.Score(pos, radius);
                int j = capacity;
                while (j > 0) {
                    if (score < results[j - 1].score)
                        break;
                    if (j < capacity)
                        results[j] = results[j - 1];
                    j--;
                }
                if (j < capacity) {
                    results[j].score = score;
                    results[j].object = o;
                }
                word = remaining;
            } while (word);
        }
    }
}
