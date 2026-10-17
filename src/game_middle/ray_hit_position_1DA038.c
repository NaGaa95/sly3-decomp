// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
#include "heap_frame_api.h"
typedef int RayPacked __attribute__((mode(TI)));
typedef union { RayPacked raw; float scalar; } RayScalarCarrier;
struct RayHit {
    char unaccessed00[0x10];
    RayPacked point;
    char unaccessed20[0x40];
};
extern RayPacked D_00317550;
void func_001DC7E0(int *count, void ***records);
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

int func_001DA038(RayPacked *position)
{
    unsigned char frame[16];
    int count;
    void **records;
    RayPacked start, end;
    func_001D2770(frame);
    func_001DC7E0(&count, &records);
    start = ray_offset(*position, D_00317550, 0.0f);
    end = ray_offset(*position, D_00317550, 5000.0f);
    {
        struct RayHit hit;
        if (func_00165000(0, start, end, count, records, &hit)) {
            *position = hit.point;
            func_001D2798(frame, 2);
            return 1;
        }
    }
    func_001D2798(frame, 2);
    return 0;
}
