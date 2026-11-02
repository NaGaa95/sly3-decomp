// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Contact {
    unsigned char pad00[0x10];
    qword position;
    unsigned char pad20[0xA4 - 0x20];
    float time;
    unsigned char padA8[4];
    Contact *next;
};
struct Endpoint { unsigned char pad[0xB0]; };
struct Entry {
    unsigned char pad000[0x168];
    Contact *head;
    unsigned char pad16C[4];
};
struct Detail { unsigned char pad0[0x14]; void **x14; };
struct Request { int x0; Detail *x4; };
struct Hit { qword pos; unsigned char pad[0x50]; };
union Vector { qword q; float f[4]; };
struct Owner {
    unsigned char pad0[0xD4];
    void *shape;
    unsigned char padD8[0x178 - 0xD8];
    int entryCount;
    Entry *entries;
    void Notify() __asm__("func_00224600");
};
typedef void (Owner::*Callback)();
extern unsigned char D_00475480[];
extern "C" {
void func_0023EDD0(Owner *, Request *);
void func_00224338(Owner *, Entry *, qword *, float *);
int func_00164A10(Request *, qword, qword, int, Hit *);
int func_0013B500(void *, int);
int func_0024F9A0(void *, qword, qword, qword *);
void func_0015DCD0(void *, void *, Callback, void *);
void func_001CB8B0(void *, void *, Request *, qword, qword, int, int, int, Contact **, float);
}
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
static inline qword Sub(VU_VECTOR a, VU_VECTOR b)
{
    qword d;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a.q), "j"(b.q));
    return d;
}
static inline qword Dot(VU_VECTOR a, VU_VECTOR b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a.q), "j"(b.q));
    return d;
}
static inline qword Sqrt(VU_VECTOR d)
{
    qword l;
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d.q));
    return l;
}
static inline qword Len(VU_VECTOR v) { return Sqrt(Dot(v, v)); }
static inline qword Div(VU_VECTOR v, VU_VECTOR l)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l.q), "j"(v.q));
    return r;
}
static inline int Scalar(VU_VECTOR v)
{
    int f;
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(v.q));
    __asm__("" : "+r"(f)); /* scheduling order only: no instruction */
    return f;
}
extern "C" void func_00224440(Owner *owner, Request *request)
{
    int i;
    func_0023EDD0(owner, request);
    for (i = 0; i < owner->entryCount; i++) {
        Entry *entry = &owner->entries[i];
        qword seg[2];
        Vector pos;
        Hit hit;
        int found = 0;
        func_00224338(owner, entry, seg, 0);
        if (!func_00164A10(request, seg[0], seg[1], 1, &hit)) {
            void *object = *request->x4->x14;
            if (func_0013B500(object, 0x32))
                found = func_0024F9A0(object, seg[0], seg[1], &pos.q);
        } else {
            found = 1;
            pos.q = hit.pos;
        }
        if (found) {
            qword dir = Sub(seg[1], seg[0]);
            dir = Div(dir, Len(dir));
            func_001CB8B0(D_00475480, owner->shape, request, pos.q, dir, 10, 0, 0, &entry->head, 0.0f);
            register Contact *head __asm__("$2") = entry->head; /* register pin */
            *(volatile int *)&head->time = Scalar(Len(Sub(seg[0], pos.q)));
            func_0015DCD0(D_00475480, owner, &Owner::Notify, 0);
        }
    }
}
