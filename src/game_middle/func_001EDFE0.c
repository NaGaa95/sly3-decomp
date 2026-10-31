// Collect the objects whose bounding range overlaps the box spanned by two points: per-axis range tables give two
// bit masks, their intersection selects the objects. The cached range lives in the optional context record.
// Ported from Sly 2 func_001C1700.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
union U { qword q; unsigned int words[4]; };
struct Cache { qword x, z; int version; int xmin, xmax, zmin, zmax; };
struct Index {
    char pad[0xEC];
    int count, active;
    void *xs, *zs;
    void **objects;
    int pad100, version;
};
void func_001EDD18(struct Index *, struct Cache *);
void func_001EDED8(void *, int *, int *, qword *, float, float);
static inline qword Max(qword a, qword b) { qword r; __asm__("vmax.xyz %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Min(qword a, qword b) { qword r; __asm__("vmini.xyz %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float X(qword q) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(q)); return f; }
static inline float Z(qword q) { float f; __asm__("prot3w %0,%1" : "=r"(f) : "r"(q)); return f; }
static inline qword And(qword a, qword b) { qword r; __asm__("pand %0,%1,%2" : "=r"(r) : "r"(a), "r"(b)); return r; }
int func_001EDFE0(struct Index *p, struct Cache *c, qword a, qword b, int max, void **out)
{
    struct Cache local;
    union U mask, copy;
    qword hi, lo;
    int i, n;
    if (!p->active)
        return 0;
    if (!c) {
        c = &local;
        c->version = -1;
    }
    if (c->version != p->version)
        func_001EDD18(p, c);
    lo = Min(a, b);
    hi = Max(a, b);
    func_001EDED8(p->xs, &c->xmin, &c->xmax, &c->x, X(lo), X(hi));
    func_001EDED8(p->zs, &c->zmin, &c->zmax, &c->z, Z(lo), Z(hi));
    copy.q = And(c->x, c->z);
    mask = copy;
    {
        void **cursor = out;
        for (n = 0, i = 0; i < p->count; i++) {
            if (mask.words[i / 32] & (1 << (i % 32))) {
                if (max < n)
                    break;
                *cursor++ = p->objects[i];
                n++;
            }
        }
    }
    c->version = p->version;
    return n;
}
