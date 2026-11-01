// Per-frame render of a "connector" (a chain of links drawn between pairs of points), Sly 2 func_001DF5B0. After the generic
// update (func_0023CC40) and the view test of the connector's bounding sphere (func_0018E500 returns a zero vector when it is
// not visible), each link is queried for its two end points and its length (func_00224338). A link longer than its maximum
// is pulled back toward the first point, then the line object, the stretched middle object and the two end caps are placed
// along the segment, in a basis built from the segment direction (func_0011CBF0).
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int bits[4]; };
struct M3 { U rows[3]; };
struct M4 { U rows[4]; };
struct ENTRY { char pad0[0x164]; float maximumLength; char pad168[8]; };
struct CONFIG { char pad0[0x1C]; float first; char pad20[0x20]; float second; };
struct VENTRY { short delta, pad; void (*fn)(void *, U *, int, float, float); };
struct HOOK { VENTRY *vt; };
struct ENDPOINT { void *object; int unused4; CONFIG *config; HOOK *scale; };
struct BOUND { char pad0[0x20]; U position; float radius; };
struct P {
    char pad0[0x2C]; unsigned char mask; char pad2D[0x34 - 0x2D]; float f34;
    char pad38[0xDC - 0x38]; BOUND *bound; char padE0[0x170 - 0xE0];
    void *line, *stretch; int count; ENTRY *entries; ENDPOINT endpoints[2];
};
extern struct { char pad[0x3ED0]; qword q; } D_00475480;
extern qword D_00317550;
extern "C" {
void func_0023CC40(P *);
qword func_0018E500(void *self, qword weights, int mask, float f, qword dir);
void func_00224338(P *, ENTRY *, qword *, float *);
void func_001C8328(void *, qword, qword, qword, float, float);
M3 func_0011CBF0(qword, qword);
M4 func_0011D660(qword, const M3 *, const U *);
qword *func_002BA818(qword *, qword);
void func_001C8248(void *, qword, const M4 *, float, float);
}
static inline float GetX(qword q) { float x; __asm__("mtc1 %1, %0" : "=f"(x) : "r"(q)); return x; }
static inline float GetY(qword q) { float y; __asm__("prot3w %0, %1" : "=r"(y) : "r"(q)); return y; }
static inline float GetZ(qword q) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q)); return z; }
struct VU_FLOAT { qword q; VU_FLOAT(const float &f) { __asm__("lw %0, %1" : "=rj"(q) : "m"(f)); } };
struct VU_FLOATQ { qword q; VU_FLOATQ(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); } };
static inline qword Pack(float x, float y, float z, float w)
{
    U u; qword q, t, s;
    __asm__("mfc1 %0,%3\n\tmfc1 %1,%4\n\tpextlw %0,%1,%0\n\tmfc1 %1,%5\n\tmfc1 %2,%6\n\tpextlw %1,%2,%1\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t), "=&r"(s) : "f"(x), "f"(y), "f"(z), "f"(w));
    u.q = q;
    return u.q;
}
static inline int IsZero(qword v)
{
    int mac;
    __asm__("vadd.xyzw $vf0, %1, %1\n\tvnop\n\tvnop\n\tvnop\n\tvnop\n\tcfc2.ni %0, $vi17" : "=r"(mac) : "j"(v));
    return (mac & 0xF) == 0xF;
}
static inline qword Subtract(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Add(qword a, qword b)
{
    qword r;
    __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Scale(qword a, VU_FLOATQ b)
{
    qword r;
    __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(a), "j"(b.q));
    return r;
}
static inline float Length(qword value)
{
    qword d, one;
    float r;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
            : "=j"(d), "=&j"(one) : "j"(value), "j"(value));
    __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "+j"(d));
    __asm__("mtc1 %1,%0" : "=f"(r) : "r"(d));
    return r;
}
static inline void Query(P *owner, ENTRY *entry, U *points, float &distance)
{
    func_00224338(owner, entry, &points[0].q, &distance);
}

extern "C" void func_00224B18(P *p)
{
    U view;
    func_0023CC40(p);
    BOUND *bound = p->bound;
    if (!bound) return;
    qword center = bound->position.q;
    qword sphere = Pack(GetX(center), GetY(center), GetZ(center), GetX(VU_FLOAT(bound->radius).q));
    view.q = func_0018E500(&D_00475480, D_00475480.q, p->mask, p->f34, sphere);
    if (IsZero(view.q)) return;
    U points[2];
    M3 basis;
    float dist;
    for (int i = 0; i < p->count; i++) {
        ENTRY *entry = &p->entries[i];
        Query(p, entry, points, dist);
        if (entry->maximumLength < dist) {
            float ratio = entry->maximumLength / dist;
            points[1].q = Add(Scale(points[0].q, VU_FLOATQ(1.0f - ratio)), Scale(points[1].q, VU_FLOATQ(ratio)));
        }
        if (p->line) func_001C8328(p->line, view.q, points[0].q, points[1].q, 1.0f, 1.0f);
        qword dir;
        if (p->stretch || p->endpoints[0].object || p->endpoints[1].object) {
            dir = Subtract(points[1].q, points[0].q);
            basis = func_0011CBF0(dir, D_00317550);
        }
        if (p->stretch) {
            float length = Length(dir);
            if (0.01f < length) {
                U scale;
                scale.f[0] = length * 0.01f;
                U *ps = &scale;
                ps->f[1] = 1.0f;
                ps->f[2] = 1.0f;
                M4 render;
                render = func_0011D660(points[0].q, &basis, &scale);
                func_001C8248(p->stretch, view.q, &render, 1.0f, 1.0f);
            }
        }
        M4 matrix;
        U *pts = points;
        for (unsigned int j = 0; j < 2; j++) {
            ENDPOINT *end = &p->endpoints[j];
            if (end->object) {
                if (end->scale) {
                    U scale;
                    HOOK *hook = end->scale;
                    VENTRY &callback = hook->vt[3];
                    callback.fn((char *)hook + callback.delta, &scale, 0, end->config->first, end->config->second);
                    matrix = func_0011D660(pts[j].q, &basis, &scale);
                } else {
                    M4 *pm = &matrix;
                    func_002BA818(&matrix.rows[3].q, points[j].q);
                    matrix.rows[0] = basis.rows[0]; pm->rows[1] = basis.rows[1]; pm->rows[2] = basis.rows[2];
                    matrix.rows[0].bits[3] = matrix.rows[1].bits[3] = matrix.rows[2].bits[3] = 0;
                    pm->rows[3].f[3] = 1.0f;
                }
                func_001C8248(end->object, view.q, &matrix, 1.0f, 1.0f);
            }
        }
    }
}
