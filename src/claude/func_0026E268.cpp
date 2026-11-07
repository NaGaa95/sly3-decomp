// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0026E268: initialize mesh history samples (Sly 2 func_0021BD18 rewritten without its asm hacks). Sly 3 stores positions
// as 28.4 fixed-point ints (scaled by 1/16), has no trailing history-init call and different offsets.
// Matching notes: the first-pass vector is written through a pointer (Set) so it is a memory scalar whose store loop.c
// sinks past the loop (load_mems); the second pass keeps a union temp; `j++, out++` gives the giv/biv increment order;
// the metadata index is added as a byte offset so the base comes first in addu.
typedef int qword __attribute__((mode(TI)));
struct IPOS { int x, y, z, w; };
struct QuadBytes { unsigned char b[4]; };
struct Sample { qword position; float fraction; QuadBytes extra, color; };
struct Batch { int count; int pad[2]; IPOS *positions; int pad10; QuadBytes *color, *extra; Sample *samples; };
struct Record { char pad[0x14]; };
struct Meta { int x0; void *style; char pad8[0x20]; };
struct N { Record *record; int count; Batch *batches; N *next; };
struct MODEL { char unknown0[0x3C]; Record *records; Meta *metadata; char pad44[0x18]; N *nodes; };
struct Ring { char pad[0x50]; };
struct S {
    char pad[0x3C]; unsigned int flags; char pad40[0x30]; MODEL model; char padD0[0x130 - 0xD0];
    float fade; int state; int pad138; int count; Ring *ring; int pad144[2]; float scale; qword axis;
};
struct ALLOC { int bytes, align; };
union REQUEST { ALLOC alloc; qword q; };
extern "C" {
void func_0023C580(S *);
void *func_001D2538(ALLOC *);
void func_001D2898(void *, const void *, unsigned int);
void func_00194F60(MODEL *, int);
extern char D_0034A160[];
}
static inline qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
static inline float Dot(qword a, qword b)
{
    qword r, one; float f;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(r), "=&j"(one) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0,%1" : "=r"(f) : "j"(r));
    return f;
}
static inline void *Allocate(int cb) { REQUEST req; req.alloc.bytes = cb; req.alloc.align = 16; return func_001D2538(&req.alloc); }
static inline void Set(qword *pv, float x, float y, float z)
{
    qword t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(*pv), "=&r"(t) : "f"(x), "f"(y), "f"(z));
}
static inline qword Broadcast(float f) { qword q; __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); return q; }
static inline qword Offset(qword position, qword axis, qword scalar)
{
    __asm__("vadda.xyzw ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x" : "+j"(position) : "j"(axis), "j"(scalar));
    return position;
}
extern "C" void func_0026E268(S *p)
{
    func_0023C580(p);
    if (!p->count && p->fade == 0.0f) p->fade = 0.5f;
    if (p->fade != 0.0f) p->count = (int)(p->fade * 60.0f + 0.5f) + 2;
    else p->fade = (p->count - 2) * 0.016666668f;
    float minimum, maximum;
    N *node;
    p->ring = (Ring *)Allocate(p->count * sizeof(Ring));
    minimum = 3.40282346638528859812e+38f; maximum = -3.40282346638528859812e+38f;
    for (node = p->model.nodes; node; node = node->next) {
        for (int i = 0; i < node->count; i++) {
            IPOS buffer[128];
            Batch *batch = &node->batches[i];
            func_001D2898(buffer, batch->positions, batch->count * 16);
            for (int j = 0; j < batch->count; j++) {
                qword v;
                Set(&v, buffer[j].x * 0.0625f, buffer[j].y * 0.0625f, buffer[j].z * 0.0625f);
                float dot = Dot(v, p->axis);
                if (maximum < dot) maximum = dot;
                if (dot < minimum) minimum = dot;
            }
        }
    }
    for (node = p->model.nodes; node; node = node->next) {
        int index = (node->record - p->model.records);
        int off = index * sizeof(Meta);
        ((Meta *)((char *)p->model.metadata + off))->style = D_0034A160;
        func_00194F60(&p->model, index);
        for (int i = 0; i < node->count; i++) {
            IPOS buffer[128];
            Batch *batch = &node->batches[i];
            func_001D2898(buffer, batch->positions, batch->count * 16);
            Sample *out = (Sample *)Allocate(batch->count * sizeof(Sample));
            batch->samples = out;
            for (int j = 0; j < batch->count; j++, out++) {
                REQUEST v;
                v.q = Make(buffer[j].x * 0.0625f, buffer[j].y * 0.0625f, buffer[j].z * 0.0625f);
                qword position = v.q, axis = p->axis;
                float dot = Dot(position, axis);
                float fraction = (dot - minimum) / (maximum - minimum);
                v.q = Broadcast((p->scale - 1.0f) * dot);
                out->position = Offset(position, axis, v.q);
                out->fraction = fraction;
                if (batch->extra) out->extra = batch->extra[j];
                if (batch->color) out->color = batch->color[j];
            }
        }
    }
    if (!p->state) {
        unsigned int flags = p->flags;
        if ((flags ^ 1) & 1) { *(unsigned int *)flags |= 2; }
        else p->flags = flags | 2;
    }
}
