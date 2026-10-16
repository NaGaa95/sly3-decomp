// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
#include "heap_frame_api.h"
typedef int RayPacked __attribute__((mode(TI)));
typedef union { RayPacked raw; float scalar; } RayScalarCarrier;
struct RayHit {
    RayPacked point;
    char unaccessed10[0x18];
    float normal_z;
    char unaccessed2C[0x14];
    float fraction;
    char unaccessed44[0x1C];
};
typedef int (*RayFilter)(void *context, void *record);
extern char D_00475480[];
extern RayPacked D_00317550;
int func_0025CEC8(void *context, void *record);
void func_0025CF18(void *game, RayPacked start, RayPacked end,
                  RayFilter filter, void *context, int *count, void ***records);
void *func_00165000(int flags, RayPacked start, RayPacked end,
                   int count, void **records, struct RayHit *output);

static inline RayPacked ray_offset(RayPacked position, RayPacked axis, float scale)
{
    RayScalarCarrier carrier;
    RayPacked result;
    __asm__("qmtc2.ni %1,%0" : "=j"(carrier.raw) : "r"(scale));
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x"
            : "=j"(result) : "j"(position), "j"(axis), "j"(carrier.raw));
    return result;
}

int func_00198D78(RayPacked *position, int flags, RayFilter filter,
                  float upper, float lower)
{
    unsigned char frame[16];
    int count;
    void **records;
    RayPacked start, end;
    func_001D2770(frame);
    start = ray_offset(*position, D_00317550, upper);
    end = ray_offset(*position, D_00317550, lower);
    if (!filter)
        filter = func_0025CEC8;
    {
        struct RayHit hit;
        func_0025CF18(D_00475480, start, end, filter, 0, &count, &records);
        if (!func_00165000(1, start, end, count, records, &hit) ||
            hit.fraction == 0.0f || ((flags & 1) && hit.normal_z < 0.7f)) {
            func_001D2798(frame, 2);
            return 0;
        }
        *position = hit.point;
    }
    func_001D2798(frame, 2);
    return 1;
}
