// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Updates the live objects of an emitter list: expired objects are released (virtual 6), the others are updated (virtual 3)
// and, when a pair was fetched, handed to func_0020C1C0; the loop gathers the bounding box of the remaining objects and stores
// its center and radius in the owner. Returns 1 when the list is empty afterwards.
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta, pad; void *fn; };
struct Vt { unsigned char pad[0x18]; VTE slot3; unsigned char pad20[0x30 - 0x20]; VTE slot6; };
struct List { unsigned char pad0[8]; int stride; };
struct Clock { float time; float delta; };
struct Item {
    unsigned char pad0[0x14]; float birth; float lifetime; unsigned char pad1C[0x70 - 0x1C];
    qword low; qword high; unsigned char pad90[0xE8 - 0x90]; Vt *vt;
};
struct Owner { unsigned char pad0[0x2C]; int radiusBits; qword center; unsigned char pad40[0x10]; List list; };
struct Iter;
extern "C" {
extern Iter *D_0036AE94;
extern Clock D_0036BB98;
int func_0011B0F0(List *);
void func_001D2770(void *);
void func_001D2798(void *, int);
int func_002029E8(Owner *);
void func_001DC7E0(int *, int *);
void func_0020C1C0(Item *, Owner *, int, int);
void func_002BE9D8(Item **, Item *);
void func_0020BDC0(Item *);
}
struct Iter {
    List *list;
    char *cur;
    int stride;
    Iter *prev;
    Iter(List *l) : list(l), cur((char *)l), stride(l->stride), prev(D_0036AE94) { D_0036AE94 = this; }
    ~Iter() { D_0036AE94 = prev; }
};
struct ItemRef {
    Item *item;
    ItemRef() { item = 0; }
    ~ItemRef() { if (item) func_0020BDC0(item); }
};
struct FRAME { int pad[4]; FRAME(); ~FRAME(); };   // out-of-line ctor/dtor 0x1D2770 / 0x1D2798
#define FLT_MAX 3.40282347e+38f
struct VECTOR { union { struct { float x, y, z; } v; qword q; }; };
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); } };
static inline bool Next(Iter &it, Item **out)
{
    Item *node = *(Item **)it.cur;
    it.cur = (char *)node + it.stride;
    func_002BE9D8(out, node);
    return *out != 0;
}
static inline qword Min3(qword a, qword b) { qword r; __asm__("vmini.xyz %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Max3(qword a, qword b) { qword r; __asm__("vmax.xyz %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Midpoint(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
static inline void StoreLength(int *out, qword v)
{
    qword d, one, len;
    register qword bits __asm__("$3"); /* Original vector readback register. */
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(len) : "j"(d));
    __asm__("qmfc2.ni %0,%2\n\tsw %0,%1" : "=&r"(bits), "=m"(*out) : "j"(len));
}
extern "C" int func_002025B8(Owner *self)
{
    List *list = &self->list;
    if (func_0011B0F0(list))
        return 0;
    VECTOR bmin = {{{FLT_MAX, FLT_MAX, FLT_MAX}}};
    VECTOR bmax = {{{-FLT_MAX, -FLT_MAX, -FLT_MAX}}};
    Iter iter(list);
    FRAME frame;
    int pairA = 0;
    int pairB = 0;
    if (func_002029E8(self))
        func_001DC7E0(&pairA, &pairB);
    ItemRef ref;
    while (Next(iter, &ref.item)) {
        float age = D_0036BB98.time - ref.item->birth;
        if (age < 0.0f)
            continue;
        if (ref.item->lifetime < age) {
            VTE *e = &ref.item->vt->slot6;
            ((void (*)(void *))e->fn)((char *)ref.item + e->delta);
            continue;
        }
        VTE *e = &ref.item->vt->slot3;
        ((void (*)(void *))e->fn)((char *)ref.item + e->delta);
        if (pairA)
            func_0020C1C0(ref.item, self, pairA, pairB);
        bmin.q = Min3(bmin.q, Min3(ref.item->low, ref.item->high));
        bmax.q = Max3(bmax.q, Max3(ref.item->low, ref.item->high));
    }
    self->center = Midpoint(bmin.q, bmax.q, VU_FLOAT(0.5f));
    StoreLength(&self->radiusBits, Sub(self->center, bmax.q));
    int empty = func_0011B0F0(list) == 0;
    return empty;
}
