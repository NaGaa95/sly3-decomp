// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
typedef struct { qword r[4]; } M4;
typedef struct VirtualEntry { short adjustment; short reserved; M4 *(*call)(); } VirtualEntry;
struct Object { unsigned char opaque0[12]; VirtualEntry *vtable; };
struct Self { unsigned char pad0[0x19F4]; struct Object *object; unsigned char pad19F8[0x1E60 - 0x19F8]; qword offset; };
void func_0011C798(M4 *m);
qword func_001AFE60(struct Self *self)
{
    struct Object *object = self->object;
    VirtualEntry *entry = &object->vtable[36];
    M4 m = *((M4 *(*)(void *))entry->call)((char *)object + entry->adjustment);
    U s;
    qword v, r;
    func_0011C798(&m);
    __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(-1.0f));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(v) : "j"(self->offset), "j"(s.q));
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
        : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(v));
    return r;
}
