// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Update the base record, then push the virtual position vector back onto the plane when it lies behind the plane normal.
typedef int qword __attribute__((mode(TI)));
typedef struct VirtualEntry { short adjustment; short reserved; qword (*call)(void *); } VirtualEntry;
struct Plane { unsigned char pad0[0x40]; qword normal; };
struct Self { unsigned char pad0[0xC]; VirtualEntry *vtable; unsigned char pad10[0x40]; struct Plane *plane; };
void func_001F3D48(struct Self *self, void *out);
static inline float Dot(qword a, qword b)
{
    qword d, one;
    float f;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
    return f;
}
static inline qword AddScaled(qword p, qword n, qword s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(p), "j"(n), "j"(s));
    return r;
}
void func_00207F00(struct Self *self, qword *out)
{
    VirtualEntry *entry;
    qword pos, normal;
    float dot;
    func_001F3D48(self, out);
    entry = &self->vtable[38];
    pos = entry->call((char *)self + entry->adjustment);
    normal = self->plane->normal;
    dot = Dot(pos, normal);
    if (dot < 0.0f) {
        union { qword q; float f[4]; } s;
        __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(-dot));
        pos = AddScaled(pos, normal, s.q);
    }
    out[1] = pos;
}
