// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// SLY3_ASFIX: engine-divfix1
typedef int qword __attribute__((mode(TI)));
struct VEntry { short delta; short pad; qword (*method)(void *); };
struct Owner { unsigned char pad0[4]; float extent; };
struct Light {
    unsigned char pad00[0xC];
    VEntry *table;
    unsigned char pad10[0x1B0 - 0x10];
    int kind;
    unsigned char pad1B4[0x1DC - 0x1B4];
    Owner *owner;
    unsigned char pad1E0[0x548 - 0x1E0];
    void *voice;
    int soundId;
    int enabled;
};
struct Range { float minimum, maximum; };
struct Limit { float minimum, maximum; };
extern float D_00325EAC;
extern Limit D_00325C68;
extern "C" {
void *func_002459F8(int id);
void func_00244F08(void *voice, int mode);
void func_002BBCD8(void *slot, void *voice);
void func_00244ED0(void *voice, float value);
void func_00244CA8(void *voice, float value);
}
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
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
static inline float Scalar(VU_VECTOR v)
{
    float f;
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(v.q));
    return f;
}
static inline float Clamp(float v, float lo, float hi)
{
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}
extern "C" void func_00217040(Light *self)
{
    if (self->kind != 2 && self->kind != 4) return;
    if (self->enabled) {
        int id = self->soundId;
        if (id != -1) {
            void **slot = &self->voice;
            if (!*slot) {
                void *voice = func_002459F8(id);
                func_00244F08(voice, 0);
                func_002BBCD8(slot, voice);
            }
        }
        if (!self->voice) return;
        {
            Range range;
            float fraction, clamped;
            float lo = D_00325EAC;
            float hi = self->owner->extent;
            range.minimum = lo;
            range.maximum = hi;
            VEntry *entry = &self->table[38];
            float length = Scalar(Len(entry->method((char *)self + entry->delta)));
            if (range.minimum == range.maximum) fraction = 0.0f;
            else fraction = (length - range.minimum) / (range.maximum - range.minimum);
            clamped = Clamp(fraction, 0.0f, 1.0f);
            func_00244ED0(self->voice, (1.0f - clamped) * D_00325C68.minimum + clamped * D_00325C68.maximum);
        }
    } else {
        void **slot = &self->voice;
        if (*slot) {
            func_00244CA8(*slot, 0.0f);
            func_002BBCD8(slot, 0);
        }
    }
}
