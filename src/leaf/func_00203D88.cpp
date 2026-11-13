// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Initializes four transformed hull points and creates the associated handle.
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword q; VU_FLOAT(int f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "rV"(f)); } /* Allow the compiler to reload the scalar at the VU transfer. */ };
struct Entry {
    void *object;
    unsigned char pad4[0x18 - 4];
    int offsetB;
    int offsetA;
    qword position;
    qword pointA;
    qword pointB;
    unsigned char pad50[0x10];
};
struct Hull {
    unsigned char pad0[0x190];
    Entry entries[4];
    unsigned char pad310[0x348 - 0x310];
    void *source;
    void *handle;
    qword block[3];
};
extern "C" {
extern int D_003256E8[];
extern qword D_00317550;
void func_001F3BF8(Hull *);
void func_001F4670(Hull *, int);
void *func_0023DDA0(Hull *, int, int);
qword func_001C9428(int, Hull *, qword);
qword func_0011D3C0(qword *);
void *func_00130078(Hull *, void *, int, int, int, qword);
}
static inline qword AddScaled(qword a, const qword &b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
extern "C" void func_00203D88(Hull *self)
{
    unsigned i;
    func_001F3BF8(self);
    func_001F4670(self, 1);
    for (i = 0; i < 4; i++) {
        int ea = (int)self + 0x190 + i * 0x60;
        Entry *e = (Entry *)ea;
        e->object = func_0023DDA0(self, D_003256E8[i], 0xD);
        qword pos = func_001C9428(0, self, *(qword *)((char *)e->object + 0x70));
        e->position = pos;
        int oa = e->offsetA;
        e->pointA = AddScaled(pos, D_00317550, VU_FLOAT(oa));
        int ob = e->offsetB;
        e->pointB = AddScaled(pos, D_00317550, VU_FLOAT(ob));
    }
    self->source = func_0023DDA0(self, 0x22, 6);
    if (self->source) {
        self->block[0] = *(qword *)self->source;
        self->block[1] = *((qword *)self->source + 1);
        self->block[2] = *((qword *)self->source + 2);
        self->handle = func_00130078(self, self->source, 0, 0x13, 3, func_0011D3C0(self->block));
    }
}

