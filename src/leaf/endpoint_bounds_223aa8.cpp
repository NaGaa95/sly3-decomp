// Rebuild the endpoint state of every entry of p and the bounding box that covers them. Each entry has two endpoints; an
// endpoint names an object: a path (shape 9) becomes a moving endpoint with a 1/2/6-segment motion profile (mode 8 / 0 / 16,
// the last a trapezoid accelerate-cruise-decelerate profile), objects of shape 3/0x2F and missing objects become fixed
// points. All points (or the whole transformed path) are accumulated into a min/max box that becomes p's single bound
// (Sly 2 func_001DE5D8).
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
typedef unsigned int uint;

struct VTE { short delta, pad; void *fn; };
struct M4 { qword rows[4]; };
struct PATH {
    char pad0[0xC];
    VTE *vt;
    char pad10[0xD8 - 0x10];
    int count;
    int padDC;
    int padE0;
    qword *points;
};
struct PARAMS { float fraction, speed, duration; int mode; };
struct SEGMENT { float start, speed, accel, duration, elapsed; };
struct MOTION { int count; SEGMENT segments[6]; int current; };
struct TRACK { PATH *path; float cursor; PARAMS params; MOTION motion; };
struct ENDPOINT {
    int id, kind;
    int pad8[2];
    union { qword point; TRACK track; };
};
struct ENTRY { ENDPOINT endpoints[2]; char pad160[0x170 - 0x160]; };
union U { qword q; float f[4]; };
struct GEO { int count; U *points; int planeCount; void *planes; int edgeCount; void *edges; };
struct P;
struct BOUND {
    void *object;
    P *owner;
    float radius;
    int pad0C;
    int tag;
    int pad14;
    ulong flags;
    char pad20[0x88 - 0x20];
    GEO local, world;
    char padB8[0xD0 - 0xB8];
};
struct P {
    char pad0[0xC];
    VTE *vt;
    char pad10[8];
    int id;
    char pad1C[0xC];
    ulong flags28;
    char pad30[0xC];
    uint flags;
    char pad40[0x10];
    void *space;
    char pad54[0xD0 - 0x54];
    int boundCount;
    BOUND *bounds;
    char padD8[0x178 - 0xD8];
    int count;
    ENTRY *entries;
};
struct MSG { int bytes, alignment; };
struct G;
extern G D_00475480;
extern qword D_00317580, D_00317590;
extern "C" {
void func_0023BA40(P *);
void *func_0017E1B8(G *, int, int, P *);
int func_0013B500(void *, int);
float func_0022DFD8(PATH *);
void func_0022E330(PATH *, qword *, qword *, float);
void *func_002333B4(void *, int, int);
qword func_0028E910(void *, void *, qword);
void *func_001D2538(MSG *);
float func_002407D8(GEO *);
void func_0018AFB0(GEO *, const M4 *, GEO *);
void func_0023B9C8(P *);
}

struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
static inline qword Min(VU_VECTOR a, VU_VECTOR b) { qword r; __asm__("vmini.xyz %0, %1, %2" : "=j"(r) : "j"(a.q), "j"(b.q)); return r; }
static inline qword Max(VU_VECTOR a, VU_VECTOR b) { qword r; __asm__("vmax.xyz %0, %1, %2" : "=j"(r) : "j"(a.q), "j"(b.q)); return r; }
static inline qword Transform(const M4 *m, qword p)
{
    qword r;
    __asm__("vmulax.xyz ACC,%1,%5x\n\tvmadday.xyz ACC,%2,%5y\n\tvmaddaz.xyz ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(r) : "j"(m->rows[0]), "j"(m->rows[1]), "j"(m->rows[2]), "j"(m->rows[3]), "j"(p));
    return r;
}
static inline float Clamp(float f, float low, float high) { if (f < low) return low; else if (high < f) return high; else return f; }
template <class T> static inline M4 *GetMatrix(T *obj) { VTE *v = &obj->vt[36]; return ((M4 * (*)(void *))v->fn)((char *)obj + v->delta); }
static inline void SetDirty(P *p) { uint f = p->flags; if ((f ^ 1) & 1) *(uint *)f |= 2; else p->flags = f | 2; }

extern "C" void func_00223AA8(P *p)
{
    int i;
    qword minimum, maximum;
    func_0023BA40(p);
    minimum = D_00317580;
    maximum = D_00317590;
    for (i = 0; i < p->count; i++) {
        ENTRY *entry = &p->entries[i];
        uint j;
        for (j = 0; j < 2; j++) {
            ENDPOINT *endpoint = &entry->endpoints[j];
            endpoint->kind = -1;
            if (endpoint->id != -1) {
                void *object = func_0017E1B8(&D_00475480, 1, endpoint->id, p);
                if (object) {
                    if (func_0013B500(object, 9)) {
                        PATH *path = (PATH *)object;
                        PARAMS *params = &endpoint->track.params;
                        int reverse = 0;
                        params->fraction = Clamp(params->fraction, 0.0f, 1.0f);
                        if (params->speed < 0.0f) { reverse = 1; params->speed = -params->speed; }
                        params->duration = __builtin_fabsf(params->duration);
                        if (params->mode != 8 && params->mode != 16 && params->mode != 0) params->mode = 8;
                        float length = func_0022DFD8(path);
                        if (0.0f < params->duration) params->speed = length / params->duration;
                        else if (0.0f < params->speed) params->duration = length / params->speed;
                        float start = params->fraction * length;
                        if (params->speed == 0.0f || params->duration == 0.0f) {
                            endpoint->kind = 0;
                            func_0022E330(path, &endpoint->point, 0, start);
                        } else {
                            endpoint->track.path = path;
                            endpoint->kind = 1;
                            endpoint->track.cursor = start;
                            SEGMENT *seg;
                            switch (params->mode) {
                            case 8:
                                endpoint->track.motion.count = 1;
                                seg = endpoint->track.motion.segments;
                                if (reverse) {
                                    seg->start = length;
                                    seg->speed = -params->speed;
                                } else {
                                    seg->speed = params->speed;
                                }
                                seg->duration = params->duration;
                                break;
                            case 0:
                                endpoint->track.motion.count = 2;
                                seg = endpoint->track.motion.segments;
                                if (reverse) {
                                    seg->start = length;
                                    seg->speed = -params->speed;
                                } else {
                                    seg->speed = params->speed;
                                }
                                seg->duration = params->duration;
                                seg = &endpoint->track.motion.segments[1];
                                if (reverse) seg->start = 0.0f;
                                else seg->start = length;
                                seg->speed = 0.0f;
                                endpoint->track.motion.segments[1].duration = 100.0f;
                                break;
                            case 16: {
                                struct { float in, out; } ramp;
                                if (300.0f <= length) ramp.in = 100.0f;
                                else ramp.in = length * 0.2f;
                                float twice = ramp.in + ramp.in;
                                ramp.out = length - ramp.in;
                                float rampTime = twice * params->duration / (length + twice);
                                float middleTime = params->duration - (rampTime + rampTime);
                                params->speed = (length - twice) / middleTime;
                                float accel = params->speed * params->speed / twice;
                                endpoint->track.motion.count = 6;
                                seg = endpoint->track.motion.segments;
                                seg->accel = accel;
                                seg->duration = rampTime;
                                seg = &endpoint->track.motion.segments[1];
                                seg->start = ramp.in;
                                seg->speed = params->speed;
                                seg->duration = middleTime;
                                seg = &endpoint->track.motion.segments[2];
                                seg->start = ramp.out;
                                seg->speed = params->speed;
                                seg->accel = -accel;
                                seg->duration = rampTime;
                                seg = &endpoint->track.motion.segments[3];
                                seg->start = length;
                                seg->accel = -accel;
                                seg->duration = rampTime;
                                seg = &endpoint->track.motion.segments[4];
                                seg->start = ramp.out;
                                seg->speed = -params->speed;
                                seg->duration = middleTime;
                                seg = &endpoint->track.motion.segments[5];
                                seg->start = ramp.in;
                                seg->speed = -params->speed;
                                seg->accel = accel;
                                seg->duration = rampTime;
                                break;
                            }
                            }
                            SetDirty(p);
                        }
                    } else if (func_0013B500(object, 3) || func_0013B500(object, 0x2F)) {
                        endpoint->kind = 0;
                        endpoint->point = GetMatrix((PATH *)object)->rows[3];
                    }
                }
            }
            if (endpoint->kind == -1) {
                endpoint->kind = 0;
                endpoint->point = GetMatrix(p)->rows[3];
            }
            switch (endpoint->kind) {
            case 0:
                minimum = Min(minimum, endpoint->point);
                maximum = Max(maximum, endpoint->point);
                endpoint->point = func_0028E910(0, p->space, endpoint->point);
                break;
            case 1: {
                M4 matrix = *GetMatrix(endpoint->track.path);
                int k;
                for (k = 0; k < endpoint->track.path->count; k++) {
                    qword point = Transform(&matrix, endpoint->track.path->points[k]);
                    minimum = Min(minimum, point);
                    maximum = Max(maximum, point);
                }
                break;
            }
            }
        }
    }
    if (p->count) {
        MSG request;
        p->boundCount = 1;
        request.bytes = sizeof(BOUND);
        request.alignment = 16;
        BOUND *bound = (BOUND *)func_001D2538(&request);
        p->bounds = bound;
        bound->object = p->space;
        bound->owner = p;
        bound->tag = p->id;
        bound->flags |= 1UL << 16;
        bound->local.count = 2;
        request.alignment = 16;
        request.bytes = 2 * sizeof(qword);
        bound->local.points = (U *)func_001D2538(&request);
        func_0018AFB0(&bound->local, 0, &bound->world);
        bound->world.points[0].q = minimum;
        bound->world.points[1].q = maximum;
        { U *out = bound->local.points; out[0].q = func_0028E910(0, p->space, minimum); }
        { U *out = bound->local.points; out[1].q = func_0028E910(0, p->space, maximum); }
        bound->flags |= 1UL << 18;
        bound->radius = func_002407D8(&bound->local);
    }
    if ((int)(p->flags28 >> 56) & 1) func_0023B9C8(p);
}
