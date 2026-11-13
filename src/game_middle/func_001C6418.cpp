// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Per-frame lighting packets for a query point (Sly 2 func_001A4478). The nearest four objects of the world (func_001C5E98)
// each add a VIF UNPACK of their 12-word payload block (padded to four with the default block). Then a basis PACKET is
// built: from the owner's virtual (limit < 0) or from the weighted centre of the found objects (kind 0: a point 1000
// units back along the object's direction, kind 1: the object's matrix position), clamped to 2.5 * limit; three
// spheres along the basis are tested against every world object and the packet is unpacked behind the payloads.
#include "../P2/vifs.h"
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; uint u[4]; };
struct M4 { U row[4]; };
struct M3 { U row[3]; };
struct BLOCK { uint words[12]; };
struct VTE { short delta; short pad; void *pfn; };
struct OBJ {
    char pad0[0xC]; VTE *vt;
    char pad10[0x90 - 0x10];
    qword direction;              // 0x90
    char padA0[0xD0 - 0xA0];
    int kind;                     // 0xD0
    char padD4[0xE8 - 0xD4];
    float rangeMin;               // 0xE8
    char padEC[0x110 - 0xEC];
    BLOCK payload;                // 0x110
    float rangeMax;               // 0x140
    char pad144[4];
    float weight;                 // 0x148
};
struct RESULT { float score; OBJ *object; };
union SPHERE { qword pos; float f[4]; int i[4]; };
struct PACKET { U row[4]; int kind; float fraction; float spread; float limit; };
struct WORLD { char pad[0x3EB8]; int cobj; OBJ *aobj[1]; };
struct P {
    OBJ *owner;                   // 0x00
    qword *input;                 // 0x04
    int pad8[2];
    float strength;               // 0x10
    int cqwPacket;                // 0x14
    uchar *pbPacket;              // 0x18
    float limit;                  // 0x1C
    float extra;                  // 0x20
    uchar *pbPayload;             // 0x24
    int cqwBasis;                 // 0x28
    uchar *pbBasis;               // 0x2C
};
extern "C" {
extern VIFS D_0036C308;
extern BLOCK D_003457F0;
extern qword D_00317530, D_00317540, D_00317550;
void func_001C5E98(WORLD *world, qword pos, int capacity, RESULT *results, float strength);
void func_0011FEA8(qword a, qword b, qword c, M3 *pm);
qword *func_002BA818(qword *p, qword v);
int func_001C61C8(qword pos, int csphere, SPHERE *asphere);
}
struct VU_FLOAT {
    qword q;
    // "r,m": a float read from memory stays a MEM until reload, so its lw is a reload (as in the target)
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j,!r"(q) : "r,m"(f)); }
    // the GPR form (Sly 2 VU_FLOAT(float)), used for the value kept across the matrix call
    VU_FLOAT(float f, int) { __asm__("mfc1 %0,%1" : "=rj"(q) : "f"(f)); }
    // the GPR form loaded straight from memory
    VU_FLOAT(const float *pf) { __asm__("lw %0,%1" : "=r"(q) : "m"(*pf)); }
};
struct VU_VECTOR {
    qword q;
    VU_VECTOR(float x, float y, float z, float w)
    {
        qword t, s;
        __asm__("mfc1 %0,%3\n\tmfc1 %1,%4\n\tpextlw %0,%1,%0\n\tmfc1 %1,%5\n\tmfc1 %2,%6\n\tpextlw %1,%2,%1\n\tpcpyld %0,%1,%0"
                : "=&r"(q), "=&r"(t), "=&r"(s) : "f"(x), "f"(y), "f"(z), "f"(w));
    }
};
// lanes of a qword held in a GPR
static inline float GetX(qword v) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(v)); return f; }
static inline float GetY(qword v) { float f; __asm__("prot3w %0,%1" : "=r"(f) : "r"(v)); return f; }
static inline float GetZ(qword v) { float f; __asm__("pextuw %0,$0,%1" : "=r"(f) : "r"(v)); return f; }
static inline qword Zero() { qword r; __asm__("vsub.xyzw %0,$vf0,$vf0" : "=j"(r)); return r; }
// m * v (xyz, w = 1)
static inline qword Transform(const M4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(r) : "j"(m.row[0].q), "j"(m.row[1].q), "j"(m.row[2].q), "j"(m.row[3].q), "j"(v));
    return r;
}
// base + v * g
static inline qword AddScaled(qword base, VU_FLOAT g, qword v)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%3,%2x" : "=j"(r) : "j"(base), "j"(g.q), "j"(v));
    return r;
}
// plain dereference: the direction load stays behind the temp store before it
static inline qword QwAt(const qword *p) { return *p; }
static inline qword Scale(qword v, VU_FLOAT g) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v), "j"(g.q)); return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Divide(qword v, VU_FLOAT g) { qword r; __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(r) : "j"(g.q), "j"(v)); return r; }
static inline float Length(qword v)
{
    qword d, one;
    float f;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(d) : "j"(d));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(d));
    return f;
}
static inline M4 *Matrix(OBJ *o) { return ((M4 *(*)(void *))o->vt[36].pfn)((char *)o + o->vt[36].delta); }
static inline float Max(float a, float b) { return (b > a) ? b : a; }
static inline void CopyQws(uint *pwDst, const uint *pwSrc, int cw)
{
    // empty do-while(0) (as left by a statement macro), as in the sibling func_001C6B90
    do
    {
    } while (0);
    for (int k = 0; k < cw; k += 4)
    {
        uint w0 = pwSrc[0];
        uint w1 = pwSrc[1];
        uint w2 = pwSrc[2];
        uint w3 = pwSrc[3];
        pwSrc += 4;
        pwDst[0] = w0;
        pwDst[1] = w1;
        pwDst[2] = w2;
        pwDst[3] = w3;
        pwDst += 4;
    }
}
static inline void AddUnpack(DMAS *dmas, uint tag, int iqw, const void *pv, int cqw)
{
    *(uint *)dmas->m_pb = iqw | tag;
    dmas->m_pb += 4;
    CopyQws((uint *)dmas->m_pb, (const uint *)pv, cqw * 4);
    dmas->m_pb += cqw * 16;
}
static inline void Clear(P *p) { p->cqwBasis = 0; p->pbBasis = 0; p->pbPayload = 0; }
static inline void Align(uint align)
{
    VIFS *dma = &D_0036C308;
    uchar *pb = dma->m_pb;
    while (((uint)pb & 15) != align) {
        *(uint *)pb = 0;
        dma->m_pb += 4;
        pb = dma->m_pb;
    }
}
extern "C" void func_001C6418(WORLD *world, M4 *transform, P *p)
{
    RESULT results[4];
    qword point = *p->input;
    if (transform)
        point = Transform(*transform, point);
    func_001C5E98(world, point, 4, results, p->strength);
    if (p->strength == 0.0f) {
        p->cqwPacket = 0;
        p->pbPacket = 0;
    } else {
        int i = 0;
        uint slot;
        p->pbPacket = D_0036C308.m_pb;
        for (slot = 0; slot < 4; slot++) {
            OBJ *o = results[slot].object;
            if (!o)
                break;
            AddUnpack(&D_0036C308, 0x6C03C000, i * 3 + 0x17, &o->payload, 3);
            i++;
        }
        if (i < 4) {
            int tag = i * 3 + 0x17;
            do {
                AddUnpack(&D_0036C308, 0x6C03C000, tag, &D_003457F0, 3);
                i++;
                tag += 3;
            } while (i < 4);
        }
        Align(0);
        p->cqwPacket = (D_0036C308.m_pb - p->pbPacket) >> 4;
    }
    if (p->limit == 0.0f) {
        Clear(p);
        return;
    }
    PACKET packet;
    if (p->limit < 0.0f) {
        OBJ *owner = p->owner;
        ((void (*)(void *, PACKET *))owner->vt[53].pfn)((char *)owner + owner->vt[53].delta, &packet);
    } else {
        float total = 0.0f;
        qword sum = Zero();
        uint slot;
        for (slot = 0; slot < 4; slot++) {
            OBJ *o = results[slot].object;
            if (!o)
                break;
            float w = o->weight;
            if (w != 0.0f) {
                if (w < 0.0f)
                    w = results[slot].score;
                else {
                    float hi = o->rangeMax;
                    w = results[slot].score * w / Max(o->rangeMin, hi);
                }
                total += w;
                switch (o->kind) {
                case 1: {
                    VU_FLOAT vw(w, 0);
                    sum = AddScaled(sum, vw, Matrix(o)->row[3].q);
                    break;
                }
                case 0: {
                    qword far = AddScaled(point, VU_FLOAT(-1000.0f), QwAt(&o->direction));
                    sum = AddScaled(sum, VU_FLOAT(w), far);
                    break;
                }
                }
            }
        }
        if (total == 0.0f) {
            Clear(p);
            return;
        }
        qword center = Divide(sum, VU_FLOAT(total));
        qword dir = Sub(point, center);
        float dist = Length(dir);
        float limit = p->limit * 2.5f;
        if (dist < limit) {
            if (dist < 1.0f)
                dir = D_00317550;
            else
                dir = Divide(dir, VU_FLOAT(dist));
            center = AddScaled(point, VU_FLOAT(-limit), dir);
            dist = limit;
        } else {
            dir = Divide(dir, VU_FLOAT(dist));
        }
        float extent = dist + p->extra;
        M3 basis;
        func_0011FEA8(dir, D_00317540, D_00317530, &basis);
        basis.row[2].q = Scale(dir, VU_FLOAT(extent));
        U *row = packet.row;
        func_002BA818(&packet.row[3].q, center);
        row[0] = basis.row[0];
        row[1] = basis.row[1];
        row[2] = basis.row[2];
        packet.row[2].u[3] = 0;
        packet.row[1].u[3] = 0;
        packet.row[0].u[3] = 0;
        row[3].f[3] = 1.0f;
        packet.fraction = dist / extent;
        packet.spread = 1.5f;
        packet.limit = p->limit;
        packet.kind = 0;
    }
    SPHERE spheres[3];
    {
        float limit = packet.limit;
        float radius = limit / packet.fraction;
        qword unit = D_00317550;
        qword spread = Scale(unit, VU_FLOAT(packet.spread));
        spheres[1].pos = Transform(*(M4 *)packet.row, unit);
        spheres[2].pos = Transform(*(M4 *)packet.row, spread);
        spheres[0].pos = point;
        spheres[1].f[3] = radius;
        spheres[0].f[3] = limit;
        spheres[2].i[3] = 0;
        for (int s = 0; s < world->cobj; s++) {
            OBJ *o = world->aobj[s];
            qword pos = Matrix(o)->row[3].q;
            VU_FLOAT r(&o->rangeMax);
            if (func_001C61C8(VU_VECTOR(GetX(pos), GetY(pos), GetZ(pos), GetX(r.q)).q, 3, spheres)) {
                packet.kind = 1;
                break;
            }
        }
    }
    {
        uchar *pb = D_0036C308.m_pb;
        p->pbBasis = pb;
        p->pbPayload = pb + 16;
    }
    Align(12);
    AddUnpack(&D_0036C308, 0x6C05C000, 0xE, &packet, 5);
    p->cqwBasis = (D_0036C308.m_pb - p->pbBasis) >> 4;
}
