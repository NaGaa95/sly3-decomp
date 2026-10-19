// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "state_position_ops.h"
union ProbeWord { qword q; float f[4]; };
struct ProbePath { unsigned char prefix[0xD4]; int wraps; };
struct ProbeSelf {
    unsigned char prefix0[0x514];
    ProbePath *path;
    unsigned char gap518[0x520 - 0x518];
    float position;
    int reverse;
};
struct ProbeRequest {
    unsigned char prefix0[4];
    int valid;
    float amount;
    unsigned char gap0C[4];
    ProbeWord start;
    qword end;
};
struct ProbeHit { qword first; qword point; unsigned char rest[0x40]; };
extern "C" {
extern qword D_00317560;
void func_0012FE90(void *output, qword value);
float func_0022DFB0(ProbePath *path);
float func_0022DFD8(ProbePath *path);
float func_0011EDB8(float dividend, float divisor);
void func_0022E330(ProbePath *path, void *point, void *direction, float parameter);
qword func_001C9428(void *source, void *destination, qword point);
int func_00164B08(qword base, float amount, qword origin, qword direction, int flags, void *output);
}
extern "C" void func_001B55A0(ProbeSelf *self, ProbeRequest *request, void *output)
{
    qword point[1];
    ProbeHit hit;
    ProbePath *path;
    float delta, first, last, value;
    if (!request->valid) {
        func_0012FE90(output, D_00317560);
        return;
    }
    path = self->path;
    delta = request->start.f[0];
    if (self->reverse)
        delta = -delta;
    first = func_0022DFB0(path);
    last = func_0022DFD8(path);
    if (path->wraps) {
        value = func_0011EDB8(self->position + delta, last);
    } else {
        value = self->position + delta;
        if (value < first)
            value = first;
        else if (last < value)
            value = last;
    }
    func_0022E330(path, point, 0, value);
    point[0] = func_001C9428(0, self, point[0]);
    if (func_00164B08(request->end, request->amount, request->start.q, point[0], 1, &hit) > 0)
        func_0012FE90(output, PackedDifference(hit.point, request->start.q));
}
