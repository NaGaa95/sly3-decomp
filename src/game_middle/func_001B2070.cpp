// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef unsigned long long qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VirtualEntry { short adjustment; short reserved; M4 *(*call)(); };
struct Object {
    unsigned char opaque0[12]; VirtualEntry *vtable;
    unsigned char pad10[0x158 - 0x10]; int reach;
};
struct Reference { unsigned char pad0[0x70]; qword position; };
struct Self {
    unsigned char pad0[0x19F4]; struct Object *object;
    unsigned char pad19F8[0x1AD4 - 0x19F8]; struct Reference *reference;
};
struct VU_FLOAT { qword qw; };
extern "C" qword D_00317550;
static inline VU_FLOAT VuFloat(int g) { VU_FLOAT v; __asm__("qmtc2.ni %1,%0" : "=j"(v.qw) : "r"(g)); return v; }
static inline qword QwSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float GFromVf(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static inline qword QwDot(qword a, qword b)
{
    qword one, d;
    __asm__("vmul.xyz %0,%2,%3
	vaddw.x %1,$vf0,$vf0w
	vadday.x $ACC,%0,%0y
	vmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword QwLengthDot(qword v)
{
    qword d = QwDot(v, v);
    qword l;
    __asm__("vsqrt $Q,%1x
	vwaitq
	vaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    return l;
}
static inline qword QwScaleRecip(qword v, qword l)
{
    qword r;
    __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
static inline qword QwAddScaled(qword base, qword vec, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(base), "j"(vec), "j"(s.qw));
    return r;
}
static inline qword Normalized(qword diff, qword fallback)
{
    qword length = QwLengthDot(diff);
    if (GFromVf(length) < 0.0001f)
        return fallback;
    return QwScaleRecip(diff, length);
}
extern "C" qword func_001B2070(Self *self)
{
    Object *object = self->object;
    VirtualEntry *entry = &object->vtable[36];
    qword position = ((M4 *(*)(void *))entry->call)((char *)object + entry->adjustment)->r[3];
    qword diff = QwSub(position, self->reference->position);
    qword dir = Normalized(diff, D_00317550);
    return QwAddScaled(position, dir, VuFloat(self->object->reach));
}
